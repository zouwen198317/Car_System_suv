
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basedef.h"
#include "alPartLUT_v1.h"
#include "alErrorCode.h"


#define _ENABLE_OUTPUT_PARITITION_IMG_    (0)   // set 1 to enable, 0 to diable file output


#define RunTimeError(msg) DEBUG_Printf("Run Time Error, %s(%d): %s", __FILE__,  __LINE__, msg)

#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
// for marking referenced position and drawing referenced area.
UINT8  g_color[8][3] = { {0, 0, 0}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {128, 128, 128}, { 128, 0, 0}, {0, 128, 0}, {0, 0, 128}};
int g_color_num = 8;
int g_color_idx;
#endif // #ifdef WIN32

//------------------------------------------------------------------------
//#define IMAGE_WIDTH  720
//#define IMAGE_HEIGHT 480

#define IMAGE_WIDTH  1280
#define IMAGE_HEIGHT 720

static const unsigned int WeightAND=(1<<8)-1;
static unsigned int DecimalWeightBilinear[8][8] = {
{2147483648, 1828721152, 1526735872, 1224750592, 905988352, 604003072, 302017792, 32768 },
{1829896192, 1578045186, 1309482757, 1040854791, 789003786, 520441357, 251813391, 27922 },
{1529085952, 1310657797, 1092229642, 873735951, 655307796, 436879642, 218451487, 23332 },
{1228275712, 1043270151, 874976271, 689905431, 521611551, 336540711, 168246831, 18742 },
{910753792, 792594186, 657723156, 522786591, 387915561, 252978996, 118107966, 13897 },
{609943552, 525206797, 440470042, 338956071, 254219316, 169482817, 84746062, 9307 },
{309133312, 257819151, 223216927, 171837231, 120523326, 85921102, 34541406, 4717 },
{8388608, 7143442, 5963812, 4784182, 3539017, 2359387, 1179757, 128 }};
static unsigned int WeightBITshift[4] = {24,16,8,0};


//////////////////////////////////////////////////////////////////////////
static void BufferSwap(UINT32 *pA, UINT32 *pB)
{
    UINT32 tmp;

    tmp = *pA;
    *pA = *pB;
    *pB = tmp;
}


///////////////////////////////////////////////////////////////////////
#if 1 //def WIN32    // Visual C++ platform
static void GetSourceRange(alPartLUT_v1_LUTStruct *p_header, unsigned int *pMLUT_YUV, int bMultipleSrc, 
                          alPartLUT_v1_Area2_t *pDstArea, int anSrcChannel[], alPartLUT_v1_Area2_t anSrcArea[], 
                          UINT32 *pL2_blk_LUT, UINT32 blk_LUT_offset, UINT32 *blk_num)
{
    alPartLUT_v1_Range_t range[4];
    int bRangeInit[4];
    unsigned int *srcPTR;
    unsigned int srcValue;
    unsigned int offset;

	unsigned int decimaloffset;
	int count;
    int switchInfo;        
    int row, col;
	int srcblk;
    int src_row, src_col;
    UINT32 num;        // number of entries in L2_blk_LUT
    int L2_offset[4], tmp_offset;
    alPartLUT_v1_Area2_t *pArea;
    UINT32 bSplitBar;       // flag to indicte to draw split bar in BV stitched image
    UINT32 value;
    int i, j;
        
    memset(bRangeInit, 0x0, sizeof(bRangeInit));
    memset(range, 0x0, sizeof(range));
    
    *blk_num = 0;

    // 1st pass, to get minimal anSrcArea
    for (i=0,row=pDstArea->start_row; i<pDstArea->height; i++,row++)
    {
    	for(j=0,col=pDstArea->start_col; j<pDstArea->width; j++,col++)
    	{      
            srcPTR = pMLUT_YUV + p_header->LUToffset      
                              + (row - p_header->startY) * (p_header->endX - p_header->startX + 1)
    	                      + (col - p_header->startX);
    	    
    	    srcValue = *srcPTR;
    	        			    
    	    if (0 == bMultipleSrc)  // single source channel
            {            
                switchInfo = p_header->ch[0].switchInfo;
            }
            else // multiple source channel            
            {
                switchInfo = srcValue >> SWITCH_BIT_SHIFT;
                
                if (NULL_IDX_NUM == switchInfo) // skip the separation symbol pixel which is drawed on dst image only
                    continue;                

            } // END else-if (0 == bMultipleSrc)
                
            offset = (srcValue >> 6) & 0x7FFFF;                               
			decimaloffset = (srcValue) &0x3F;

            if (0 == offset)    // offset == 0 means to draw separation bar on BV image, so skip
                continue;                        
    		    
            src_row = offset / 720;
            src_col = offset % 720;
            
            // update the referenced area embraced by (min_row, min_col) and (max_row, max_col)
            if (0 == bRangeInit[switchInfo])
    		{
    		    range[switchInfo].min_row = src_row;
                range[switchInfo].max_row = src_row;
    		    range[switchInfo].min_col = src_col;
                range[switchInfo].max_col = src_col;
    		    
    		    bRangeInit[switchInfo] = 1;
            }
            else 
            {
                if (src_row < range[switchInfo].min_row)
                    range[switchInfo].min_row = src_row;
                else if (src_row > range[switchInfo].max_row)
                    range[switchInfo].max_row = src_row;
    
                if (src_col < range[switchInfo].min_col)
                    range[switchInfo].min_col = src_col;
                else if (src_col > range[switchInfo].max_col)
                    range[switchInfo].max_col = src_col;
            } // END else-if if (0 == bRangeInit[switchInfo])                                            
    	} // END for(j=0,col=pDstArea->start_col; i<pDst->height; j++,col++)
    } // END for (i=0,row=pDstArea->start_row; i<pDstArea->height; i++,row++)
    
	//extend src block range    
	for(j=0;j<4;j++)
	{
		if(range[j].min_row == 0 && range[j].min_col == 0 && range[j].max_row ==0 && range[j].max_col == 0){
			continue;
		}
		if(range[j].min_row == 0 && range[j].min_col == 0){
			range[j].max_row += 1;
			range[j].max_col += 1;
		}
		else if(range[j].min_row == 0 && range[j].max_col == IMAGE_WIDTH-1){	
			range[j].max_row += 1;
			range[j].min_col -= 1;
		}
		else if(range[j].max_row == IMAGE_HEIGHT-1 && range[j].min_col == 0){	
			range[j].min_row -= 1;
			range[j].max_col += 1;
		}
		else if(range[j].max_row == IMAGE_HEIGHT-1 && range[j].max_col == IMAGE_WIDTH-1){
			range[j].min_row -= 1;
			range[j].min_col -= 1;	
		}
		else if (range[j].min_row == 0){
			range[j].max_row += 1;
			range[j].min_col -= 1;
			range[j].max_col += 1;		
		}
		else if(range[j].min_col == 0){
			range[j].min_row -= 1;
			range[j].max_row += 1;
			range[j].max_col += 1;
		}
		else if(range[j].max_row == IMAGE_HEIGHT-1){
			range[j].min_row -= 1;
			range[j].min_col -= 1;
			range[j].max_col += 1;	
		}
		else if(range[j].max_col == IMAGE_WIDTH-1){
			range[j].min_row -= 1;
			range[j].max_row += 1;
			range[j].min_col -= 1;
		}
		else{
			range[j].min_row -= 1;
			range[j].min_col -= 1;
			range[j].max_row += 1;
			range[j].max_col += 1;
		}
	}

    memset(anSrcArea, 0x0, 4*sizeof(alPartLUT_v1_Area2_t));
    
    memset(L2_offset, 0x0, sizeof(L2_offset));
    tmp_offset =0;        
	count =0;
    for (j=0; j<4; j++)		
    {
        anSrcChannel[j] = bRangeInit[j];
        
        if (0 == bRangeInit[j]) 
            continue;

        // floor to even number            
        if (range[j].min_col % 2)    
            range[j].min_col--;
        // ceil to odd number
        if (0 == range[j].max_col % 2)    
            range[j].max_col++;            

        anSrcArea[j].start_row = range[j].min_row;
        anSrcArea[j].start_col = range[j].min_col;
        anSrcArea[j].height = range[j].max_row - range[j].min_row + 1;
        anSrcArea[j].width  = range[j].max_col - range[j].min_col + 1;
        
        L2_offset[j] = tmp_offset;
        tmp_offset += anSrcArea[j].width * anSrcArea[j].height;
		count++;
    } // END for (j=0; j<4; j++)    
    
    // 2nd pass, to translate L2 block LUT
    num = 0;
    for (i=0,row=pDstArea->start_row; i<pDstArea->height; i++,row++)
    {
    	for(j=0,col=pDstArea->start_col; j<pDstArea->width; j++,col++)
    	{      
            bSplitBar = 0;
            srcPTR = pMLUT_YUV + p_header->LUToffset      
                               + (row - p_header->startY) * (p_header->endX - p_header->startX + 1)
     	                       + (col - p_header->startX);
     	    
    	    srcValue = *srcPTR;

            offset = (srcValue >> 6) & 0x7FFFF;
			decimaloffset = (srcValue) &0x3F;
    	        			    
    	    if (0 == bMultipleSrc)  // single source channel
            {            
                switchInfo = p_header->ch[0].switchInfo;
            }
            else // multiple source channel            
            {
                switchInfo = srcValue >> SWITCH_BIT_SHIFT;
                
                if (NULL_IDX_NUM == switchInfo) // skip the separation symbol pixel which is drawed on dst image only
                {
                    bSplitBar = 1;                
                }

            } // END else-if (0 == bMultipleSrc)
                            
			if(count==1)
				srcblk=0;
			else
			{
				if(switchInfo == 0 || switchInfo == 1)
					srcblk=0;
				else
					srcblk=1;
			}
            
            if (0 == offset)    // offset == 0 means to draw separation bar on BV image, so skip
                bSplitBar = 1;
            src_row = offset / 720;
            src_col = offset % 720;
            
            pArea = &(anSrcArea[switchInfo]);
            
            // check if out of buffer space
            if (blk_LUT_offset + num > MAX_L2_BLOCK_LUT_NUM) {
                RunTimeError("access outside the allocated buffer size");
                return;
            }                        
                
            if (bSplitBar)
                *(pL2_blk_LUT + blk_LUT_offset + num) = bSplitBar << 31;
            else {
                value = (src_row - pArea->start_row) * pArea->width + (src_col - pArea->start_col);                
                *(pL2_blk_LUT + blk_LUT_offset + num) = ((L2_offset[switchInfo] + value)<<6 )+ decimaloffset + (srcblk<<30);
            }
            num++;                            
    	} // END for(j=0,col=pDstArea->start_col; i<pDst->height; j++,col++)
    } // END for (i=0,row=pDstArea->start_row; i<pDstArea->height; i++,row++)
    
    *blk_num = num;
}                          
#endif  // #ifdef WIN32

///////////////////////////////////////////////////////////////////////
void alPartLUT_v1_DoPartition(alPartLUT_v1_HeaderStruct *pMLUT, unsigned int *pMLUT_YUV, int mem_budget, alPartLUT_v1_LUTSet_t *pSet)
{
    //char filename[32];
    FILE *pf[4] = { NULL, NULL, NULL, NULL };

#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
    UINT8 *ch_img[4] = { NULL, NULL, NULL, NULL };
#endif

    alPartLUT_v1_Area2_t dst_area;
    alPartLUT_v1_Area2_t src_area[4];
    int bSrcChannel[4];     // flag to indicate which source channel is referenced by LUT
    int ch_num;             // number of referenced source channel(s)
    int bMultipleSrc;       // flag to indicate if LUT reference to multiple(more than 1) source channel images
    
    int divide_count;           // parition counter
    int divide_x, divide_y;     // 
    
    unsigned int total_num, last_total_num;
    alPartLUT_v1_LUTStruct *p_header;
    unsigned int lut_width, lut_height; // 
    unsigned int blk_width, blk_height; // witth and height of parition block
    unsigned int blk_x_num, blk_y_num;  // number of partitioned blocks, in x, y direction respectively
    unsigned int x_idx, y_idx;          // block index, in x, y direction respectively
        
    UINT32 L2_lut_num, last_L2_lut_num;
    UINT32 blk_size;
    BOOL bSkipParition;
    //BOOL bBlockGAEEnable = FALSE;
    
    int mem_size;
    int i, j;
    int cnt;
    
    //DEBUG_Printf("g_LutSet size = %d\n", sizeof(alPartLUT_v1_LUTSet_t));    
    
    if (NULL == pSet->lut_data) {
        RunTimeError("invalid pointer value");
        //alERROR_SetErrorCode(EAGLEK3_ERROR_BV_PARTITION_INVALID_POINTER);
        goto exit_1;
    }
    
#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
    // memory allocation for 4 channel image
    ch_img[0] = (UINT8 *) malloc(4*720*480*3);
    if (NULL == ch_img[0]) 
    {
        RunTimeError("not enough memory");
        //alERROR_SetErrorCode(EAGLEK3_ERROR_BV_PARTITION_NOT_ENOUGH_MEMORY);
        goto exit_1;
    }
        
    for(i=1; i<4; i++)
        ch_img[i] = ch_img[0] + i*720*480*3;    
     
    memset(ch_img[0], 0xFF, 4*720*480*3);    
#endif

    L2_lut_num = 0;
    total_num = 0;
    for (i=0; i<=(int)(pMLUT->LUTIdx); i++) //for all block.
    {
        last_L2_lut_num = L2_lut_num;
        last_total_num = total_num;
                
		p_header = &(pMLUT->header[i]);
		
		lut_width  = p_header->endX - p_header->startX + 1;
		lut_height = p_header->endY - p_header->startY + 1;
						
		//if (i <= (int)(pMLUT->singleChIdx))//if single channel or not
        if(p_header->singleChIdx == 1)
		    bMultipleSrc = 0;
        else
            bMultipleSrc = 1;        		    
			
		divide_x = 1;
		divide_y = 1;
        bSkipParition = FALSE;

		for (divide_count=0; bSkipParition == FALSE; divide_count++)   //start to partition, will go the loop iteratively till the block size is small enough.
		{
#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
		    memset(ch_img[0], 0xFF, 4*720*480*3);         // reset the source position image
#endif

		    if (divide_x < divide_y)
		        divide_x++;
            else 
                divide_y++;	
            		    
		    // partitioned block width and height		    
            blk_width  = (lut_width + divide_x/2) / divide_x;
            // force blk_width even number
            if (blk_width%2)
                blk_width++;    
            blk_height = (lut_height + divide_y/2) / divide_y;

            // number of partitioned blocks in x direction            		    
		    blk_x_num = lut_width / blk_width;	        
		    if (lut_width % blk_width)
		        blk_x_num++;
		    
		    // number of partitioned blocks in y direction            		    
		    blk_y_num = lut_height / blk_height;
		    if (lut_height % blk_height)
		        blk_y_num++;		    		                

            for (y_idx=0; y_idx<blk_y_num; y_idx++)		    //for all divided block.
		    {
		        for (x_idx=0; x_idx<blk_x_num; x_idx++)
		        {
		            dst_area.start_row = p_header->startY + y_idx * blk_height;
		            dst_area.start_col = p_header->startX + x_idx * blk_width;		            
		            if ((lut_height - y_idx*blk_height) >= blk_height)
		                dst_area.height = blk_height;
                    else
                        dst_area.height = lut_height - y_idx*blk_height;

                    if ((lut_width - x_idx*blk_width) >= blk_width)                        
                        dst_area.width = blk_width;
                    else
                        dst_area.width = lut_width - x_idx*blk_width;
		            		            		            
		            GetSourceRange(p_header, pMLUT_YUV, bMultipleSrc, &dst_area, bSrcChannel, src_area, pSet->lut_data, L2_lut_num, &blk_size);//find the relative source block.
#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
		            MarkSourcePixel(p_header, pMLUT_YUV, bMultipleSrc, &dst_area, x_idx, y_idx, ch_img);//No use.
#endif		            		            
		            
		            // calculate neccesary bytes to store LUT, source image block and destination BV image block
		            mem_size = blk_width*blk_height*(4 + 2);    // size of LUT + size of dstination BV image block

                    // get number of referenced source channel and the referenced area
                    ch_num = 0;
		            for (j=0; j<4; j++) 
		            {		     
		                if (0 == bSrcChannel[j])
		                    continue;
		                mem_size += (src_area[j].width * src_area[j].height * 2);
                        ch_num++;
                    }
                                                
                    if (mem_size > mem_budget)
                        goto Next_Partition;    // exceed memory budget, need to be divided into more blocks

                    if (total_num >= MAX_BV_BLOCK_INFO_NUM) { // array overflow

                        RunTimeError("array overflow.");                        
                        //alERROR_SetErrorCode(EAGLEK3_ERROR_BV_PARTITION_ARRAY_OVERFLOW);
                        goto exit_1;

                    }

                    //if((total_num - last_total_num) >= (MAX_BV_BLOCK_INFO_NUM/((MLUT->LUTIdx+1))) // added by chinson(201307??): for (MAX_BV_BLOCK_INFO_NUM=1024) 
                    if((total_num - last_total_num) >= (MAX_BV_BLOCK_INFO_NUM>>2)) // added by chinson(20130723): for (MAX_BV_BLOCK_INFO_NUM=256) 
                    {

                        RunTimeError("too much parrition for single large block.");
                        //alERROR_SetErrorCode(EAGLEK3_ERROR_BV_PARTITION_ARRAY_OVERFLOW_SINGLE);
                        goto Skip_Partition;

                    }
                    
                    // fill in output structure                    
                    pSet->BInfo[total_num].lut_offset = L2_lut_num;
                    pSet->BInfo[total_num].lut_num = blk_size;
                    L2_lut_num += blk_size;
                    
                    pSet->BInfo[total_num].dst_area = dst_area;
                    pSet->BInfo[total_num].ch_num = ch_num;    
                    pSet->BInfo[total_num].bEnableGAE = pMLUT->header[i].bEnableGAE;
                    for(j=0, cnt=0; j<4; j++) 
                    {
                        if (0 == bSrcChannel[j])
                            continue;

                        if (cnt >= 2) { // arrary overflow, should never happen
                            RunTimeError("array overflow.");
                            return;
                        }
                        pSet->BInfo[total_num].ch_area[cnt].ch_idx = j;
                        pSet->BInfo[total_num].ch_area[cnt].start_row = src_area[j].start_row;
                        pSet->BInfo[total_num].ch_area[cnt].start_col = src_area[j].start_col;
                        pSet->BInfo[total_num].ch_area[cnt].width  = src_area[j].width;
                        pSet->BInfo[total_num].ch_area[cnt].height = src_area[j].height;
                        cnt++;                        
                    } // END for(j=0; j<4; j++) {
                    
                    total_num++;
                                                            
                                        
		        } // END for (x_idx=0; x_idx<blk_x_num; x_idx++);		        		        		        
		    } // END for (y_idx=0; y_idx<blk_y_num; y_idx++)

			break;	// (mem_size <= mem_budget) for all blocks in this iteration. Partition is successful, so leave loop.

Skip_Partition:
            bSkipParition = TRUE;

Next_Partition://keep partitioning
            if(L2_lut_num > last_L2_lut_num)
                memset(pSet->lut_data+last_L2_lut_num, 0x0, (L2_lut_num - last_L2_lut_num)*sizeof(UINT32));
            L2_lut_num = last_L2_lut_num;               

            if(total_num > last_total_num)
                memset(&(pSet->BInfo[last_total_num]), 0x0, (total_num - last_total_num)*sizeof(alPartLUT_v1_BlockInfo_t));

            total_num = last_total_num;     // back-track the block numbers when parition is not successful at this iteration
        } //  END for (divide_count=0; ; divide_count++)
        
        pSet->lut_data_size = L2_lut_num;
        pSet->blk_num = total_num;  // total number of partitioned blocks
                
#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
        // save 4-channel position mark image to file 
        for(j=0; j<4; j++)
        {
            sprintf(filename, "Lut_%d_src_%d.raw", i, j);
            pf[j] = fopen(filename, "wb");
            if (NULL == pf[j])
            {
                DEBUG_Printf("can not create file %s.", filename);
                goto exit_1;
            }
            
            fwrite(ch_img[j], sizeof(unsigned char), 720*480*3, pf[j]);
            fclose(pf[j]);
            pf[j] = NULL;
            
        }                       
#endif  // END #if _ENABLE_OUTPUT_PARITITION_IMG__
    } // END for (i=0; i<=pMLUT->LUTIdx; i++)  
                          		
exit_1:

    // close opened file
    for (i=0; i<4; i++) 
    {
        if (NULL != pf[i])
            fclose(pf[i]);
    }

#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
    // free allocated memory
    if (NULL != ch_img[0])
        free(ch_img[0]);    
#endif
}



//////////////////////////////////////////////////////////////////////////
#if defined(WIN32) && (_ENABLE_OUTPUT_PARITITION_IMG_)    // Visual C++ platform
//////////////////////////////////////////////////////////////////////////
static void Draw_Area(UINT8 *img, UINT16 img_width, UINT16 img_height, alPartLUT_v1_Area2_t *pArea, UINT8 R_value, UINT8 G_value, UINT8 B_value)
{
    //int pen_width = 2;
    int pen_width = 1;
    int row, col;
    int i, j;

    // draw the rectangle outside of the specified area

    // draw top horizontal line
    for(i=0; i<pen_width; i++) {                            
        row = (int) pArea->start_row - pen_width + i;
        if (row < 0)   // outside of the image
            continue;
        
        for(j=0; j<(pArea->width+2*pen_width); j++) {                        
            
            col = (int)pArea->start_col - pen_width + j;
            if (col < 0 || col >= img_width) // outside of the image
                continue;

            *(img + (row*img_width + col)*3    ) = R_value;
            *(img + (row*img_width + col)*3 + 1) = G_value;
            *(img + (row*img_width + col)*3 + 2) = B_value;
        } // END for(j=0; j<(pArea->width+2*pen_width); j++) {
    }

    // draw botom horizontal line
    for(i=0; i<pen_width; i++) {                            
        row = (int)pArea->start_row + (int) pArea->height + i;
        if (row >= img_height)   // outside of the image
            continue;

        for(j=0; j<(pArea->width+2*pen_width); j++) {                        
            col = (int)pArea->start_col - pen_width + j;
            if (col < 0 || col >= img_width) // outside of the image
                continue;

            *(img + (row*img_width + col)*3    ) = R_value;
            *(img + (row*img_width + col)*3 + 1) = G_value;
            *(img + (row*img_width + col)*3 + 2) = B_value;
        } // END for(j=0; j<(pArea->width+2*pen_width); j++) {
    } // END for(i=0, i<pen_width; i++) {
    
    // draw left vertical line
    for(j=0; j<pen_width; j++) {
        
        // draw left vertical line            
        col = (int) pArea->start_col - pen_width + j;
        if (col < 0) // outisde of the image
            continue;

        for(i=0; i<(pArea->height+2*pen_width); i++) {
            row = (int) pArea->start_row - pen_width + i;
            if (row < 0 || row >= img_height)   // outside of the image
                continue;
            
            *(img + (row*img_width + col)*3    ) = R_value;
            *(img + (row*img_width + col)*3 + 1) = G_value;
            *(img + (row*img_width + col)*3 + 2) = B_value;
        } // END for(i=0; i<(pArea->height+2*pen_width); i++) {
    }

    // draw right vertical line
    for(j=0; j<pen_width; j++) {
        col = pArea->start_col + pArea->width + j;
        if (col >= img_width) // outisde of the image
            continue;

        for(i=0; i<(pArea->height+2*pen_width); i++) {
            row = pArea->start_row - pen_width + i;
            if (row < 0  || row >= img_height)   // outside of the image
                continue;
                        
            *(img + (row*img_width + col)*3    ) = R_value;
            *(img + (row*img_width + col)*3 + 1) = G_value;
            *(img + (row*img_width + col)*3 + 2) = B_value;
        } // END for(i=0; i<(pArea->height+2*pen_width); i++) {
    } // END for(j=0; j<pen_width; j++) {    
}

static void MarkSourcePixel(alPartLUT_v1_LUTStruct *p_header, unsigned int *pMLUT_YUV, int bMultipleSrc, alPartLUT_v1_Area2_t *pDstArea, int x_idx, int y_idx, UINT8 *anImg[])
{
    alPartLUT_v1_Range_t range[4];
    int bRangeInit[4];
    alPartLUT_v1_Area2_t  src_area;
    unsigned int *srcPTR;
    unsigned int srcValue;
    unsigned int offset;
    int switchInfo;        
    int src_num;
    int row, col;
    int src_row, src_col;
    int i, j;
    
    src_num = 0;    
    
    memset(bRangeInit, 0x0, sizeof(bRangeInit));
    memset(range, 0x0, sizeof(range));

    for (i=0,row=pDstArea->start_row; i<pDstArea->height; i++,row++)    
    {
    	for(j=0,col=pDstArea->start_col; j<pDstArea->width; j++,col++)
    	{            
    	    srcPTR = pMLUT_YUV + p_header->LUToffset
    	                      + (row - p_header->startY) * (p_header->endX - p_header->startX + 1)
    	                      + (col - p_header->startX);
    	    
    	    srcValue = *srcPTR;
    	        			    
    	    if (0 == bMultipleSrc)  // single source channel
            {            
                switchInfo = p_header->ch[0].switchInfo;
            }
            else // multiple source channel            
            {
                //switchInfo= srcValue >> 27;
                //switchInfo= srcValue >> 29;
                switchInfo = srcValue >> SWITCH_BIT_SHIFT;
                if (NULL_IDX_NUM == switchInfo) // skip the separation symbol pixel which is drawed on dst image only
                    continue;                

                //switchInfo = switchInfo & 0x3;
            } // END else-if (0 == bMultipleSrc)
                
            offset = (srcValue >> 6) & 0x7FFFF;                               
            if (0 == offset)    // offset == 0 means to draw separation bar on BV image, so skip
                continue;                        
    		    
            src_row = offset / 720;
            src_col = offset % 720;
            
            // mark the referenced position 
            *(anImg[switchInfo] + (src_row * 720 + src_col)* 3    ) = g_color[g_color_idx][0];
            *(anImg[switchInfo] + (src_row * 720 + src_col)* 3 + 1) = g_color[g_color_idx][1];
            *(anImg[switchInfo] + (src_row * 720 + src_col)* 3 + 2) = g_color[g_color_idx][2];                            

            // update the referenced area embraced by (min_row, min_col) and (max_row, max_col)
            if (0 == bRangeInit[switchInfo])
    		{
    		    range[switchInfo].min_row = src_row;
                range[switchInfo].max_row = src_row;
    		    range[switchInfo].min_col = src_col;
                range[switchInfo].max_col = src_col;
    		    
    		    bRangeInit[switchInfo] = 1;
            }
            else 
            {
                if (src_row < range[switchInfo].min_row)
                    range[switchInfo].min_row = src_row;
                else if (src_row > range[switchInfo].max_row)
                    range[switchInfo].max_row = src_row;
    
                if (src_col < range[switchInfo].min_col)
                    range[switchInfo].min_col = src_col;
                else if (src_col > range[switchInfo].max_col)
                    range[switchInfo].max_col = src_col;
            } // END else-if if (0 == bRangeInit[switchInfo])                                            
                
    	} // END for(j=0,col=pDstArea->start_col; i<pDst->height; j++,col++)
    } // END for (i=0,row=pDstArea->start_row; i<pDstArea->height; i++,row++)
              
    for (j=0; j<4; j++)		
    {                
        if (0 == bRangeInit[j]) 
            continue;

        src_area.start_row = range[j].min_row;
        src_area.start_col = range[j].min_col;
        src_area.height = range[j].max_row - range[j].min_row;
        src_area.width  = range[j].max_col - range[j].min_col;
        
        Draw_Area(anImg[j], 720, 480, &src_area, g_color[g_color_idx][0], g_color[g_color_idx][1], g_color[g_color_idx][2]);                
    } // END for (j=0; j<4; j++)
    
    g_color_idx = (g_color_idx + 1) % 8;    // use the new color index for the next time
}                             
#endif // #ifdef WIN32



///////////////////////////////////////////////////////////////////////////////
//void BV_Stitch_YUV422I(UINT8 *ch_img[], UINT16 img_width, UINT16 img_height, alPartLUT_v1_HeaderStruct *pMLUT, unsigned int *pMLUT_YUV, UINT8 *dst_buf)
//{
//    int mode = 0;
//    
//    int switchInfo;    
//    //unsigned int Im_Width = 720;
//    unsigned int destStart;
//    //unsigned int destOffset;
//    //unsigned int destInterval;
//    unsigned int *srcPTR;
//    unsigned int srcValue;
//    //unsigned int destUV;
//    //unsigned int dstOffset;
//    //unsigned int dstUV;
//    unsigned int src_row, src_col;
//    unsigned int dst_row, dst_col;
//    unsigned int x, y;
//    unsigned int offset;
//    int i;
// 
//    // fill dst buf with black color (Y = 0, U/V = 128)
//    for(i=0; i<720*480*2/4; i++)
//        *((unsigned int *)dst_buf + i) = 0x80008000;
//
//    // to get src_x, src_y from LUT entry
//    for (i=pMLUT->singleChIdx; i>=0; i--)
//	{        
//		//destInterval = 0;
//		switchInfo = pMLUT->header[i].ch[0].switchInfo;
//				
//		destStart = pMLUT->header[i].OSDoffset[mode];
//		// destStart = 0;
//		
//		srcPTR = pMLUT_YUV + pMLUT->header[i].LUToffset;
//		//destOffset = destStart;
//		//for (y=pMLUT->header[i].startY; y<=pMLUT->header[i].endY; y++,destInterval+=Im_Width,destOffset=destStart+destInterval)
//		for (y=pMLUT->header[i].startY; y<=pMLUT->header[i].endY; y++)
//		{
//			//for(x=pMLUT->header[i].startX; x<=pMLUT->header[i].endX; x++,destOffset++,srcPTR++)
//			for(x=pMLUT->header[i].startX; x<=pMLUT->header[i].endX; x++,srcPTR++)
//			{				
//				srcValue = *srcPTR;				
//				
//				//destUV = destOffset>>1;
//				//YSrc = DecimalInterpolation_Y(pYIn[switchInfo],srcValue);
//                offset = (srcValue >> 6) & 0x7FFFF;                
//
//                if (0 == offset)    // offset == 0 means to draw separation bar on BV image, so skip
//                    continue;                        
//				
//				src_row = offset / 720;
//				src_col = offset % 720;				
//				dst_row = y;
//				dst_col = x;
//				
//				// Y
//                *(dst_buf + (dst_row*720 + dst_col)*2  ) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2);
//                
//                if (x % 2) {
//                    if (0 == src_col % 2) {
//                        // U
//                        *(dst_buf + (dst_row*720 + dst_col)*2 - 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 + 1);
//                        // V
//                        *(dst_buf + (dst_row*720 + dst_col)*2 + 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 + 3);
//                    }
//                    else {
//                        // U
//                        *(dst_buf + (dst_row*720 + dst_col)*2 - 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 - 1);
//                        // V
//                        *(dst_buf + (dst_row*720 + dst_col)*2 + 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 + 1);
//                    }
//                } // END if (x % 2) {
//                
//			} // END for(x=pMLUT->header[i].startX; x<=pMLUT->header[i].endX; x++,destOffset++,srcPTR++)							
//		} // for (y=pMLUT->header[i].startY; y<=pMLUT->header[i].endY; y++,destInterval+=Im_Width,destOffset=destStart+destInterval)
//		
//	} // for (i=pMLUT->singleChIdx; i>=0; i--)
//
//    // for 4 corners(multi-channel)	
//	for (i=pMLUT->LUTIdx; i>(int)(pMLUT->singleChIdx); i--)
//	{	
//		//destInterval=0;        
//
//		//destStart = pMLUT->header[i].OSDoffset[mode];
////        destStart = 0;
//		srcPTR = pMLUT_YUV + pMLUT->header[i].LUToffset;
//		//destOffset = destStart;
//		//for (y=pMLUT->header[i].startY; y<=pMLUT->header[i].endY; y++,destInterval+=Im_Width,destOffset=destStart+destInterval)
//		for (y=pMLUT->header[i].startY; y<=pMLUT->header[i].endY; y++)
//		{		  
//			//for(x=pMLUT->header[i].startX; x<=pMLUT->header[i].endX; x++,destOffset++,srcPTR++)
//			for(x=pMLUT->header[i].startX; x<=pMLUT->header[i].endX; x++,srcPTR++)
//			{
//				srcValue = *srcPTR;
//				//destUV = destOffset >> 1;
//
//				//switchInfo=_extu(srcValue,SwitchBITcsta,SwitchBITcstb);
//                
//                //switchInfo= (srcValue >> 27) & 0x3;
//                //switchInfo= srcValue >> 29;
//                switchInfo = srcValue >> SWITCH_BIT_SHIFT;
//
//				if (switchInfo == NULL_IDX_NUM)//the black line pixel is located by SwitchLUT here
//				    continue;
//
//                //YSrc = DecimalInterpolation_Y(pYIn[switchInfo],srcValue);                    
//                offset = (srcValue >> 6) & 0x7FFFF;                
//                if (0 == offset)    // offset == 0 means to draw separation bar on BV image, so skip
//                    continue;                        
//                
//                src_row = offset / 720;
//                src_col = offset % 720;                
//                dst_row = y;
//                dst_col = x;
//                    
//                // Y
//                *(dst_buf + (dst_row*720 + dst_col)*2  ) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2  );
//                
//                if (x % 2) {
//                    if (0 == src_col % 2) {
//                        // U
//                        *(dst_buf + (dst_row*720 + dst_col)*2 - 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 + 1);
//                        // V
//                        *(dst_buf + (dst_row*720 + dst_col)*2 + 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 + 3);
//                    }
//                    else {
//                        // U
//                        *(dst_buf + (dst_row*720 + dst_col)*2 - 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 - 1);
//                        // V
//                        *(dst_buf + (dst_row*720 + dst_col)*2 + 1) = *(ch_img[switchInfo] + (src_row*720 + src_col)*2 + 1);
//                    }
//                } // END if (x % 2) {
//			} // END for(x=pMLUT->header[i].startX; x<=pMLUT->header[i].endX; x++,destOffset++,srcPTR++)
//		} // END for (y=pMLUT->header[i].startY; y<=pMLUT->header[i].endY; y++,destInterval+=Im_Width,destOffset=destStart+destInterval)
//	} // END for (i=pMLUT->LUTIdx; i>pMLUT->singleChIdx; i--)			    		            
//}

//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
  UINT8 L2_SRAM[192*1024];
  UINT8 *L2_addr_DSP = &(L2_SRAM[0]);
  UINT8 *L2_addr_DMA = &(L2_SRAM[0]);
#else
  UINT8 *L2_addr_DSP = (UINT8 *) 0x10800000;
  UINT8 *L2_addr_DMA = (UINT8 *) 0x40800000;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alPartLUT_v1_DoTableLookup(UINT8 *ch_img[], UINT16 img_width, UINT16 img_height, alPartLUT_v1_LUTSet_t *pSet,  UINT8 *dst_buf)
{           
    // Ping-pong buffer, accessed by CPU side
    UINT32 CPU_base[2];
    UINT8  *pCPU_dst;    // destination BV image block for CPU access
    UINT32 *pCPU_lut;    // lut for CPU access
    UINT8  *pCPU_src;    // source image block for CPU access       
    // Ping-pong buffer, accessed by DMA side
    UINT32 DMA_base[2];
    UINT8  *pDMA_dst;    // destination BV image block for DMA access;
    UINT32 *pDMA_lut;    // lut for DMA access
    UINT8  *pDMA_src;    // source image block for DMA access    
    int DMA_src_size;    // total size (lut, src, dst) for DMA access
    
    alPartLUT_v1_BlockInfo_t *pBInfo;        
    alPartLUT_v1_Area2_t *p_area;
    alPartLUT_v1_ChannelArea2_t *pch;    
    UINT32 offset, offset1, offset2, offset3, bSplitBar;
    register UINT8  Y, U, V;
	register UINT8  Y1,Y2,Y3,Y4;
    int blk_idx;
    int num;
    int i;    
	//int count = 0;
	int decX,decY;
	
    //BOOL bBlockGAEEnable = FALSE;

    // beware that CPU_base[0] and DMA_base[0] make up the ping-pong buffer, thus
    //             (1) CPU_base[0] and DMA_base[1] point to the same physical buffer in L2 SRAM
    //             (2) CPU_base[1] and DMA_base[0] point to the same physical buffer in L2 SRAM
    CPU_base[0]= (UINT32) L2_addr_DSP;
    CPU_base[1]= (UINT32) L2_addr_DSP + (192/2)*1024;
    
    DMA_base[0] = (UINT32) L2_addr_DMA + (192/2)*1024;
    DMA_base[1] = (UINT32) L2_addr_DMA;    

    pBInfo = &(pSet->BInfo[0]);

    // DMA 0-th buf            
    pDMA_dst = (UINT8 *) DMA_base[0];
    pDMA_lut = (UINT32 *)(DMA_base[0] + pBInfo->lut_num*2);
    pDMA_src = (UINT8 *) (DMA_base[0] + pBInfo->lut_num*2 + pBInfo->lut_num*sizeof(UINT32));

	DAT_copy(pSet->lut_data + pBInfo->lut_offset, pDMA_lut, pBInfo->lut_num*sizeof(UINT32)); 

    
    DMA_src_size = 0;
    for (i=0; i<pBInfo->ch_num; i++) {
        pch = &(pBInfo->ch_area[i]);
        
        // DAT_2D1D
        DAT_copy2d2d(
            ch_img[pch->ch_idx] + (pch->start_row*img_width + pch->start_col)*2,
            pDMA_src + DMA_src_size,
            pch->width, pch->height, img_width << 1, pch->width << 1
            );

        DMA_src_size += (pch->width * pch->height * 2);
        
      #ifndef WIN32                       
        //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
      #endif
    }   
    
    // swap the ping-pong buffer
    BufferSwap(&DMA_base[0], &DMA_base[1]);
    BufferSwap(&CPU_base[0], &CPU_base[1]);
        
    DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish                                       
                
    for (blk_idx=0; blk_idx<pSet->blk_num; blk_idx++) 
    {                
        if (0 != blk_idx) {
            // DMA the generated dst image block from L2 to memory
            p_area = &(pSet->BInfo[blk_idx-1].dst_area);
            
            pDMA_dst = (UINT8 *) DMA_base[0];
            
            // DAT_1D2D
            DAT_copy2d2d(pDMA_dst,
                       dst_buf + (p_area->start_row * img_width + p_area->start_col)*2,
                       p_area->width, p_area->height, p_area->width << 1, img_width << 1);

          #ifndef WIN32                       
            //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
          #endif
        }
        
        if (blk_idx != pSet->blk_num-1) {
            // DMA the next block of lut, src from memory to L2
            pBInfo = &(pSet->BInfo[blk_idx+1]); // next block
            
            pDMA_dst = (UINT8 *) DMA_base[0];              
            pDMA_lut = (UINT32 *)(DMA_base[0] + pBInfo->lut_num*2);  // 2 bytes per pixel for YUV422I
            pDMA_src = (UINT8 *) (DMA_base[0] + pBInfo->lut_num*2 + pBInfo->lut_num*sizeof(UINT32));
                  
            DAT_copy(pSet->lut_data + pBInfo->lut_offset, pDMA_lut, pBInfo->lut_num*sizeof(UINT32));            
    
            DMA_src_size = 0;
            for (i=0; i<pBInfo->ch_num; i++) {
                pch = &(pBInfo->ch_area[i]);

                // DAT_2D1D
                DAT_copy2d2d(
                           ch_img[pch->ch_idx] + (pch->start_row*img_width + pch->start_col)*2,
                           pDMA_src + DMA_src_size,
                           pch->width, pch->height, img_width << 1, pch->width << 1);
                DMA_src_size += (pch->width * pch->height * 2);
                
              #ifndef WIN32                       
                //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
              #endif
            }            
        } // END if (blk_idx != pSet->blk_num-1) {
        
        // CPU process the current buffer
        num = pSet->BInfo[blk_idx].dst_area.width * pSet->BInfo[blk_idx].dst_area.height;
        
        pCPU_dst = (UINT8 *) CPU_base[0];
        pCPU_lut = (UINT32 *) (CPU_base[0] + num*2);
        pCPU_src = (UINT8 *) (CPU_base[0] + num*2 + num*sizeof(UINT32));
        
        // perfrom table lookup
        for(i=0; i<num; i+=2) {
            // even pixel
			decX = (*(pCPU_lut + i)>>3)&0x7;
			decY = *(pCPU_lut + i)&0x7;
            offset = (*(pCPU_lut + i)<<2)>>8;
			offset1 = offset + 1;
			offset2 = offset + pSet->BInfo[blk_idx].ch_area[(*(pCPU_lut + i)>>30)&0x1].width;
			offset3 = offset + 1 + pSet->BInfo[blk_idx].ch_area[(*(pCPU_lut + i)>>30)&0x1].width;

			bSplitBar = offset >> 25;
            if (bSplitBar||(*(pCPU_lut + i))>>31)
                Y = 0x0;
            else
			{
				Y1 = *(pCPU_src + offset*2);
				Y2 = *(pCPU_src + offset1*2);
				Y3 = *(pCPU_src + offset2*2);
				Y4 = *(pCPU_src + offset3*2);

				Y = ( Y1 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[0])&WeightAND)+
			  		  Y2 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[1])&WeightAND)+
					  Y3 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[2])&WeightAND)+
					  Y4 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[3])&WeightAND))>>7;

                //Y = (Y1 + Y2 + Y3 + Y4)>>2;
                //if(pSet->BInfo[blk_idx].bEnableGAE == FALSE) Y = 255;
			}
            
            *(pCPU_dst + i*2) = Y;      // even pixel Y
            
            // odd pixel
			decX = (*(pCPU_lut + i +1)>>3)&0x7;
			decY = *(pCPU_lut + i +1)&0x7;
            offset = (*(pCPU_lut + i + 1)<<2)>>8; 
			offset1 = offset + 1;
			offset2 = offset + pSet->BInfo[blk_idx].ch_area[(*(pCPU_lut + i + 1)>>30)&0x1].width;
			offset3 = offset + 1 + pSet->BInfo[blk_idx].ch_area[(*(pCPU_lut + i + 1)>>30)&0x1].width;

            bSplitBar = offset >> 25;            
            if (bSplitBar||(*(pCPU_lut + i +1))>>31) 
            {
                //Y2 = 0x0;
                Y = 0x0;
                U = 0x80;
                V = 0x80;
            }
            else 
			{
				Y1 = *(pCPU_src + offset*2);
				Y2 = *(pCPU_src + offset1*2);
				Y3 = *(pCPU_src + offset2*2);
				Y4 = *(pCPU_src + offset3*2);

				Y = ( Y1 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[0])&WeightAND)+
					  Y2 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[1])&WeightAND)+
					  Y3 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[2])&WeightAND)+
					  Y4 *((DecimalWeightBilinear[decX][decY]>>WeightBITshift[3])&WeightAND))>>7;
                                
                //Y = (Y1 + Y2 + Y3 + Y4)>>2;
                //if(pSet->BInfo[blk_idx].bEnableGAE == FALSE) Y = 255;

                if (0 == offset % 2) { // even pixel in src
                    U = *(pCPU_src + offset*2 + 1);
                    V = *(pCPU_src + offset*2 + 3);
                }
                else {  // even pixel in src
                    U = *(pCPU_src + offset*2 - 1);
                    V = *(pCPU_src + offset*2 + 1);                
                }                                            
            }
            
            *(pCPU_dst + i*2 + 1) = U;            
            *(pCPU_dst + i*2 + 2) = Y;  // odd pixel Y
            *(pCPU_dst + i*2 + 3) = V;            
        } // END for(i=0; i<num; i++) {
        
        // swap the ping-pong buffer
        BufferSwap(&DMA_base[0], &DMA_base[1]);
        BufferSwap(&CPU_base[0], &CPU_base[1]);
                
        DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
    } // END for (blk_idx=0; blk_idx<pSet->blk_num; blk_idx++)
    
    // DMA the last  dst image block from L2 to memory
    p_area = &(pSet->BInfo[blk_idx-1].dst_area);    
    pDMA_dst = (UINT8 *)DMA_base[0];

    // DAT_1D2D
    DAT_copy2d2d(pDMA_dst,
               dst_buf + (p_area->start_row * img_width + p_area->start_col)*2,
               p_area->width, p_area->height, p_area->width << 1, img_width << 1);
}
/*
void AV_Stitch_YUV422I_L2(UINT8 *a_pucSrcBuffer[], UINT16 a_uwImageWidth, UINT16 a_uwImageHeight, alPartLUT_v1_LUTSet_t *a_pSet, UINT8 *a_pucDestBuffer)
{           
    // Ping-pong buffer, accessed by CPU side
    UINT32 CPU_base[2];
    UINT8  *pCPU_dst;    // destination BV image block for CPU access
    UINT32 *pCPU_lut;    // lut for CPU access
    UINT8  *pCPU_src;    // source image block for CPU access       
    // Ping-pong buffer, accessed by DMA side
    UINT32 DMA_base[2];
    UINT8  *pDMA_dst;    // destination BV image block for DMA access;
    UINT32 *pDMA_lut;    // lut for DMA access
    UINT8  *pDMA_src;    // source image block for DMA access    
    int DMA_src_size;    // total size (lut, src, dst) for DMA access
    
    alPartLUT_v1_BlockInfo_t *pBInfo;        
    alPartLUT_v1_Area2_t *p_area;
    alPartLUT_v1_ChannelArea2_t *pch;    
    UINT32 offset, bSplitBar;
    register UINT8  Y, U, V;
    int blk_idx;
    int num;
    int i;    
        
    // beware that CPU_base[0] and DMA_base[0] make up the ping-pong buffer, thus
    //             (1) CPU_base[0] and DMA_base[1] point to the same physical buffer in L2 SRAM
    //             (2) CPU_base[1] and DMA_base[0] point to the same physical buffer in L2 SRAM
    CPU_base[0]= (UINT32) L2_addr_DSP;
    CPU_base[1]= (UINT32) L2_addr_DSP + 98304; // (192/2)*1024;
    
    DMA_base[0] = (UINT32) L2_addr_DMA + 98304; // (192/2)*1024;
    DMA_base[1] = (UINT32) L2_addr_DMA;    
    
    pBInfo = &(a_pSet->BInfo[0]);
        
    // DMA 0-th buf            
    pDMA_dst = (UINT8 *) DMA_base[0];
    pDMA_lut = (UINT32 *)(DMA_base[0] + (pBInfo->lut_num << 1));
    pDMA_src = (UINT8 *) (DMA_base[0] + (pBInfo->lut_num << 1) + pBInfo->lut_num*sizeof(UINT32));

       
    DAT_copy(a_pSet->lut_data + pBInfo->lut_offset, pDMA_lut, pBInfo->lut_num*sizeof(UINT32)); 
        

    
    DMA_src_size = 0;
    for (i=0; i<pBInfo->ch_num; i++) {
        pch = &(pBInfo->ch_area[i]);

        DAT_copy2d2d( 
                   a_pucSrcBuffer[pch->ch_idx] +((pch->start_row*a_uwImageWidth + pch->start_col) << 1),
                   pDMA_src + DMA_src_size,
                   pch->width, pch->height, a_uwImageWidth<<1, a_uwImageWidth<<1);         
        
        DMA_src_size += (pch->width * pch->height << 1);
        
      #ifndef WIN32                       
        //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
      #endif
    }   
    
    // swap the ping-pong buffer
    BufferSwap(&DMA_base[0], &DMA_base[1]);
    BufferSwap(&CPU_base[0], &CPU_base[1]);
        
    DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish                                       
                
    for (blk_idx=0; blk_idx < a_pSet->blk_num; blk_idx++) 
    {                
        if (0 != blk_idx) {
            // DMA the generated dst image block from L2 to memory
            p_area = &(a_pSet->BInfo[blk_idx-1].dst_area);
            
            pDMA_dst = (UINT8 *) DMA_base[0];

            DAT_copy2d2d(DAT_1D2D, pDMA_dst,
                       a_pucDestBuffer + ((p_area->start_row * a_uwImageWidth + p_area->start_col) << 1),
                       p_area->width, p_area->height, a_uwImageWidth<<1);

          #ifndef WIN32                       
            //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
          #endif
        }
        
        if (blk_idx != a_pSet->blk_num-1) {
            // DMA the next block of lut, src from memory to L2
            pBInfo = &(a_pSet->BInfo[blk_idx+1]); // next block
            
            pDMA_dst = (UINT8 *) DMA_base[0];              
            pDMA_lut = (UINT32 *)(DMA_base[0] + (pBInfo->lut_num << 1));  // 2 bytes per pixel for YUV422I
            pDMA_src = (UINT8 *) (DMA_base[0] + (pBInfo->lut_num << 1) + (pBInfo->lut_num << 2));     //*sizeof(UINT32)    
    
            DAT_copy(a_pSet->lut_data + pBInfo->lut_offset, pDMA_lut, (pBInfo->lut_num << 2));                      
    
            
            DMA_src_size = 0;
            for (i=0; i<pBInfo->ch_num; i++) {
                pch = &(pBInfo->ch_area[i]);


                DAT_copy2d2d(DAT_2D1D, 
                           a_pucSrcBuffer[pch->ch_idx] + ((pch->start_row*a_uwImageWidth + pch->start_col) << 1),
                           pDMA_src + DMA_src_size,
                           pch->width, pch->height, a_uwImageWidth<<1);          

                DMA_src_size += (pch->width * pch->height << 1);
                
              #ifndef WIN32                       
                //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
              #endif
            }            
        } // END if (blk_idx != a_pSet->blk_num-1) {
        
        // CPU process the current buffer
        num = a_pSet->BInfo[blk_idx].dst_area.width * a_pSet->BInfo[blk_idx].dst_area.height;
        
        pCPU_dst = (UINT8 *) CPU_base[0];
        pCPU_lut = (UINT32 *) (CPU_base[0] + (num << 1));
        pCPU_src = (UINT8 *) (CPU_base[0] + (num << 1) + (num << 2));
        
        // perfrom table lookup
        for(i = 0; i < num; i += 2) 
		{
            // even pixel
            offset = (*(pCPU_lut + i)<<2)>>8;            
            bSplitBar = offset >> 25;            
            if (bSplitBar||(*(pCPU_lut + i +1))>>31)
                Y = 0x0;
            else
                Y = *(pCPU_src + (offset << 1));
            
            *(pCPU_dst + (i << 1)) = Y;      // even pixel Y
            
            // odd pixel
            offset = (*(pCPU_lut + i + 1)<<2)>>8;            
            bSplitBar = offset >> 25;            
            if (bSplitBar||(*(pCPU_lut + i +1))>>31) 
            {
                //Y2 = 0x0;
                Y = 0x0;
                U = 0x80;
                V = 0x80;
            }
            else {
                Y = *(pCPU_src + (offset << 1));
                                    
                if (offset & 1) 
				{ // even pixel in src
                    U = *(pCPU_src + (offset << 1) - 1);
                    V = *(pCPU_src + (offset << 1) + 1);  
					
                }
                else 
				{  // even pixel in src
					U = *(pCPU_src + (offset << 1) + 1);
                    V = *(pCPU_src + (offset << 1) + 3);
                }                                            
            }
            
            *(pCPU_dst + (i << 1) + 1) = U;            
            *(pCPU_dst + (i << 1) + 2) = Y;  // odd pixel Y
            *(pCPU_dst + (i << 1) + 3) = V;            
        } // END for(i=0; i<num; i++) {
        
        // swap the ping-pong buffer
        BufferSwap(&DMA_base[0], &DMA_base[1]);
        BufferSwap(&CPU_base[0], &CPU_base[1]);
                
        DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
    } // END for (blk_idx=0; blk_idx<a_pSet->blk_num; blk_idx++)
    
    // DMA the last  dst image block from L2 to memory
    p_area = &(a_pSet->BInfo[blk_idx-1].dst_area);    
    pDMA_dst = (UINT8 *)DMA_base[0];


    DAT_copy2d2d(DAT_1D2D, pDMA_dst,
               a_pucDestBuffer + ((p_area->start_row * a_uwImageWidth + p_area->start_col) << 1),
               p_area->width, p_area->height, a_uwImageWidth<<1);

}
*/

#ifdef WIN32

#include <time.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alPartLUT_v1_SaveLUTDataToHeaderFile(alPartLUT_v1_LUTSet_t * pSet, INT32 entry_num, char * pcPrefix, wchar_t * pwcFileName)
{

    alPartLUT_v1_BlockInfo_t *pInfo;
    int i;
    wchar_t pwcFilePath[MAX_PATH];
    FILE *pf;
    time_t rawtime;
    struct tm timeinfo;
    char acTimeStr[100];

    /*wcscpy_s(pwcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(pwcFilePath, MAX_PATH, pwcFileName);*/

    wcscpy_s(pwcFilePath, MAX_PATH, pwcFileName);
    
    _wfopen_s(&pf, pwcFilePath, L"w");

    if (NULL == pf) {
        printf("can not create file %s.\n", pwcFileName);
        return;
    }    

    time (&rawtime);
    localtime_s(&timeinfo, &rawtime);
    asctime_s(acTimeStr, sizeof(acTimeStr), &timeinfo);

    fprintf(pf, "/*\n %s \n This file is automatically generated by the Program\n */\n", acTimeStr);
    
    fprintf(pf, "#ifndef _%s_LUT_SET_H_\n", pcPrefix);
    fprintf(pf, "#define _%s_LUT_SET_H_\n\n", pcPrefix);        
    fprintf(pf, "#ifdef __cplusplus\n"),
    fprintf(pf, "   extern \"C\" {\n");
    fprintf(pf, "#endif // END #ifdef __cplusplus\n");
    
    fprintf(pf, "#include \"TableLU/PartitionLUT.h\"\n\n");

    // print lut_data
    fprintf(pf, "static unsigned int %s_Lut_data[%d] = {", pcPrefix, entry_num);
    for (i=0; i<entry_num; i++) {
        if (0 == i % 16)    
            fprintf(pf, "\n    ");
        fprintf(pf, "0x%X, ", *(pSet->lut_data + i));        
    }
    fprintf(pf, "   };\n\n");
        
    // g_LutSet
    fprintf(pf, "alPartLUT_v1_LUTSet_t g_LutSet = {\n", pcPrefix);
    fprintf(pf, "   %d,\n", pSet->blk_num);
    fprintf(pf, "   {\n");
    for(i=0; i<MAX_BV_BLOCK_INFO_NUM; i++) {
        pInfo = &(pSet->BInfo[i]);
        
        //                 dst_area           ch_num 
        fprintf(pf, "      { {%3d, %3d, %3d, %3d}, ", pInfo->dst_area.start_row, pInfo->dst_area.start_col, pInfo->dst_area.width, pInfo->dst_area.height);
        fprintf(pf, " %d, ", pInfo->ch_num);
        fprintf(pf, "{{%d, %d, %d, %d, %d}, {%d, %d, %d, %d, %d}}, ", pInfo->ch_area[0].ch_idx, pInfo->ch_area[0].start_row, pInfo->ch_area[0].start_col, pInfo->ch_area[0].width, pInfo->ch_area[0].height,
                                                                      pInfo->ch_area[1].ch_idx, pInfo->ch_area[1].start_row, pInfo->ch_area[1].start_col, pInfo->ch_area[1].width, pInfo->ch_area[1].height);
        fprintf(pf," %d, %d, %d }, \n", pInfo->lut_offset, pInfo->lut_num, pInfo->bEnableGAE);
    }
    fprintf(pf, "   },\n");
        
    fprintf(pf, "   &(%s_Lut_data[0]),\n", pcPrefix);
    fprintf(pf, "   %d,\n", pSet->lut_data_size);
    
    fprintf(pf, "   };\n\n");
    
    fprintf(pf, "#ifdef __cplusplus\n");
    fprintf(pf, "   }\n");
    fprintf(pf, "#endif // END #ifdef __cplusplus\n\n");
    fprintf(pf, "#endif // END #ifndef _%s_LUT_SET_H_\n", pcPrefix);
    
    fclose(pf);
}

#endif

