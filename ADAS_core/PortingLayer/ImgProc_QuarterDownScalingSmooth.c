
#include <assert.h>
#include "ImageProc.h"
#include "dat_copy.h"
#include "IMGLib.h"
#include "VisionMeIntrinsic.h"

#ifdef WIN32
  static UINT8 L2_SRAM_DSP[192*1024];
  static UINT8 *L2_addr_DSP = &(L2_SRAM_DSP[0]);
  static UINT8 *L2_addr_DMA = &(L2_SRAM_DSP[0]);
#else
  static UINT8 *L2_addr_DSP = (UINT8 *) 0x10800000;
  static UINT8 *L2_addr_DMA = (UINT8 *) 0x40800000;
#endif

#if (defined(WIN32) && (PC_USE_INTRINSIC_CODE == 0))

void ImgProc_QuarterDownScalingWithSmooth(UINT8 * a_pucSrc,
                                          UINT8 * a_pucTemp, 
                                          UINT8 * a_pucDst, 
                                          INT32 a_lSrcWidth, 
                                          INT32 a_lDstWidth, 
                                          INT32 a_lBlkWidth, 
                                          INT32 a_lBlkHeight,
                                          INT32 DSRATE)
{
	int x,y,i,j,sum = 0;
	int filter[3][3] = {{1,2,1},{2,4,2},{1,2,1}};

	ImgProc_QuarterDownScaling(a_pucSrc-DSRATE-a_lSrcWidth*DSRATE,a_pucTemp,a_lSrcWidth,a_lDstWidth+2,a_lBlkWidth+DSRATE*2,a_lBlkHeight+DSRATE*2);

	for(y = 1;y < a_lBlkHeight/DSRATE+1;y++)
	{
		for(x = 1;x < a_lBlkWidth/DSRATE+1;x++)
		{
			sum = 0;
			for(j = -1;j <= 1;j++)
            {
				for(i = -1;i <= 1;i++)
                {
					sum += *(a_pucTemp+i+x+(y+j)*(a_lDstWidth+2)) * filter[i+1][j+1];
                }
            }

            sum = (sum>>4);
			*(a_pucDst+x-1+(y-1)*a_lDstWidth) = (sum & 0x80000000)?0:((sum & 0x7fffff00)?255:sum);

		}
	}

}

#else

void ImgProc_QuarterDownScalingWithSmooth(UINT8 * a_pucSrc,
                                          UINT8 * a_pucTemp, 
                                          UINT8 * a_pucDst, 
                                          INT32 a_lSrcWidth, 
                                          INT32 a_lDstWidth, 
                                          INT32 a_lBlkWidth, 
                                          INT32 a_lBlkHeight,
                                          INT32 rate)
{

	int y;
    int dma_id;
    unsigned int DestAddr; 
    unsigned char *DEST; 
    unsigned int SRCTmpAddr; 
    unsigned char *SRC_TMP;
    unsigned int SRCBaseAddr; 
    unsigned char *SRC; 
    unsigned int DelegateBaseAddr;
    unsigned char *DeleSRC;
    unsigned int DelegateDestAddr;
    unsigned char *DeleDestbuf;
 
	                       
	const char filter[9] = 
	{
	    1,2,1,
	    2,4,2,
	    1,2,1
	};

    unsigned char *InBuf = (unsigned char *)a_pucSrc-rate-a_lSrcWidth*rate;

    //Buf 0

    SRCBaseAddr = (unsigned int)L2_addr_DSP; //168K length for outbuf (16/18)
    SRC = (unsigned char *)SRCBaseAddr;
            
 
    SRCTmpAddr = (unsigned int)(L2_addr_DSP + (172032)); //12K, length for outbuf (1/16) 
    SRC_TMP = (unsigned char *)SRCTmpAddr;


    DestAddr = (unsigned int)(L2_addr_DSP + (184320)); //12K, length for outbuf (1/16) 
    DEST = (unsigned char *)DestAddr;
 
		
    //DMA 0

    DelegateBaseAddr = (unsigned int)L2_addr_DMA;  
    DeleSRC = (unsigned char *)DelegateBaseAddr;
    

    DelegateDestAddr = (unsigned int)(L2_addr_DMA + (184320)); 
    DeleDestbuf = (unsigned char *)DelegateDestAddr;
    
    //make sure the down scaling out buffer is enough
    assert((rate) == 4); 
    //make sure input buffer size is enough 
    assert(((a_lBlkWidth+rate*2) * (a_lBlkHeight+rate*2)) <= 172032); 
    
    dma_id = DAT_copy2d(DAT_2D1D, InBuf, DeleSRC, a_lBlkWidth+rate*2, a_lBlkHeight+rate*2, a_lSrcWidth);
    
	DAT_wait(dma_id);

    ImgProc_QuarterDownScaling(SRC, SRC_TMP, a_lBlkWidth+rate*2, a_lDstWidth+2, a_lBlkWidth+rate*2,a_lBlkHeight+rate*2);

	for(y = 0;y < a_lBlkHeight>>2 ;y++)
	    IMG_conv_3x3_i8_c8_altek(SRC_TMP+(y*(a_lDstWidth+2)), DEST+(y*a_lDstWidth), a_lBlkWidth>>2, a_lDstWidth+2, filter, 4); 
    
	dma_id = DAT_copy( DeleDestbuf, a_pucDst, (a_lBlkWidth/rate)*(a_lBlkHeight/rate));
	
	DAT_wait(dma_id);
	
}

#endif
