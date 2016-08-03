
#include "ImageProc.h"
#include "mtype.h"
#include "CommonK_Def.h"
#include <assert.h>
#include "IMGLib.h"
#include "Vlib.h"
#include "dat_copy.h"
#include "VisionMeIntrinsic.h"

#ifdef WIN32
#include <stdio.h>
//#include "Debug/FileOperation.h"
#endif

static INT8 g_acHFWeightingCurveTable[6][128] = {
/* Standard Alpha = 8 */                { 0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 },
/* New Alpha = 0.5(0~7), 8.5(8~) */     { 0,1,1,2,2,3,3,4,12,21,29,38,46,55,63,72,80,89,97,106,114,123,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 },
/* New Alpha = 2(0~3), 8.5(4~) */       { 0,2,4,6,15,23,32,40,49,57,66,74,83,91,100,108,117,125,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 },
/* Standard Alpha = 2 */                { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 },
/* New Alpha = 0.5(0~3), 2.5(4~) */     { 0,1,1,2,4,7,9,12,14,17,19,22,24,27,29,32,34,37,39,42,44,47,49,52,54,57,59,62,64,67,69,72,74,77,79,82,84,87,89,92,94,97,99,102,104,107,109,112,114,117,119,122,124,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 },
/* New Alpha = 0.5(0~7), 2.0(8~) */     { 0,1,1,2,2,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99,101,103,105,107,109,111,113,115,117,119,121,123,125,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 },
};
static INT16 g_wHFWeightingCurveShift[6] = { 0, 0, 0, 0, 0, 0 };

/** \brief The 8 bits Y buffer for Y only image. */
//static UINT8 g_aucImgYBufer[EAGLEK2_MAX_DISPLAY_AREA_SIZE_X*EAGLEK2_MAX_DISPLAY_AREA_SIZE_Y];
/** \brief The 8 bits INT8 Temp buffer for temperally generated high-frequency image. */
//static INT8 g_acTempHFBufer[EAGLEK2_MAX_DISPLAY_AREA_SIZE_X*EAGLEK2_MAX_DISPLAY_AREA_SIZE_Y];

#ifdef WIN32
static UINT8 g_ucL2_SRAM[192*1024];
static UINT8 * g_L2_SRAM_ROI_DSP = &(g_ucL2_SRAM[0]);
static UINT8 * g_L2_SRAM_ROI_DMA = &(g_ucL2_SRAM[0]);
#else
static UINT8 * g_L2_SRAM_ROI_DSP = (UINT8 *) 0x10800000;
static UINT8 * g_L2_SRAM_ROI_DMA = (UINT8 *) 0x40800000;
#endif


#ifndef WIN32 //Joey++ Performance Fine Tune
#pragma CODE_SECTION(SharpenByUnSharpMask,   ".text:optimized");
#else
//extern __int64 g_read8Result;
#endif

#if (defined(WIN32) && (PC_USE_INTRINSIC_CODE == 0))
void SharpenByUnSharpMask(  const UINT8 * restrict a_pucImgYUYVBuf, 
                            const UINT32 a_ulBufferWidth, 
                            const UINT32 a_ulBufferHeight, 
                            const UINT8 a_ucGlobalWeighting, // weighting * 8 : if a_ucGlobalWeighting == 8, then weighting value = 1
                            const INT8 * a_pcWeightingCurve,
						    const UINT8 * a_pucPixelWeightingTable, // 0 ~ 16 each pixel
                            UINT8 * a_pucImgYUYVOutBuf
                            )
{
    UINT32 ulX, ulY;
    INT32 lK, delta, sign;
    register INT32 lSum;
    register INT32 lNewPixel = 0;
    UINT32 ulSrcPitch = (a_ulBufferWidth<<1);
    UINT32 ulDestPitch = ((a_ulBufferWidth-2)<<1);

    const UINT8 * pucSrcRow1 = a_pucImgYUYVBuf;
    const UINT8 * pucSrcRow2 = pucSrcRow1 + ulSrcPitch;
    const UINT8 * pucSrcRow3 = pucSrcRow2 + ulSrcPitch;
    const UINT8 * pucPixelWeightingLine = a_pucPixelWeightingTable + a_ulBufferWidth + 1;
    const UINT8 * pucPixelWeightingPtr = pucPixelWeightingLine;
    const UINT8 * pucSrcLine = a_pucImgYUYVBuf + ulSrcPitch + 2;
    const UINT8 * pucSrcPtr = pucSrcLine;
    UINT8 * pucDestLine = a_pucImgYUYVOutBuf/* + ulDestPitch + 2*/;
    UINT8 * pucDestPtr = pucDestLine;

    /* Unsharp Mask : { 1, 2, 1, 2, 4, 2, 1, 2, 1 } */
    const INT8 acSharpMask[9] = { -1, -2, -1, -2, 12, -2, -1, -2, -1 };
    const short wShiftSharp = 4;      // Use Weighting Table : g_acSharpenTable
    /* Point to the end of the mask to account for rotation */
    const char *mask_rot = &acSharpMask[3*3 - 1];

    // Make 3x3 : smoothing + Sharpen
    for(ulY = 0; ulY < a_ulBufferHeight - 2; ulY++, pucSrcLine += ulSrcPitch, pucDestLine += ulDestPitch, pucPixelWeightingLine += a_ulBufferWidth)
    {
        pucSrcPtr = pucSrcLine;
        pucDestPtr = pucDestLine;
        pucPixelWeightingPtr = pucPixelWeightingLine;

        for (ulX = 0; ulX < a_ulBufferWidth - 2; ulX++, pucSrcPtr+=2, pucDestPtr+=2, pucPixelWeightingPtr++) 
        {           
            lSum = 0;

            for (lK=0; lK<3; lK++) 
            {
                lSum += *(pucSrcRow1 + ((ulX + lK)<<1)) * mask_rot[-(0 + lK)]
                    + *(pucSrcRow2 + ((ulX + lK)<<1)) * mask_rot[-(3 + lK)]
                    + *(pucSrcRow3 + ((ulX + lK)<<1)) * mask_rot[-(6 + lK)];
            }

            delta           = abs(lSum);
            sign            = (lSum & 0x80000000) ? -1 : 1;
            delta           = delta >> wShiftSharp;
            delta           = (delta > 127) ? 127 : delta;

            lNewPixel = (INT32)(*pucSrcPtr) + sign * (((INT32)(*(a_pcWeightingCurve + delta)) * (*(pucPixelWeightingPtr) * (INT32)a_ucGlobalWeighting)) >> (8/*PixelWeighting*/+3/*GlobalWeighting*/));     
            *pucDestPtr = ((lNewPixel > 255) ? 255 : ((lNewPixel < 0) ? 0 : lNewPixel));			
			*(pucDestPtr+1) = *(pucSrcPtr+1);

        }

        pucSrcRow1 += ulSrcPitch;
        pucSrcRow2 += ulSrcPitch;
        pucSrcRow3 += ulSrcPitch;
    }

}
                       
#else                            

#ifndef WIN32 
__inline void SharpenByUnSharpMask(  
#else
    void SharpenByUnSharpMask(  
#endif
                            const UINT8 *restrict a_pucImgYUYVBuf, 
                            const UINT32 a_ulBufferWidth, 
                            const UINT32 a_ulBufferHeight, 
                            const UINT8 a_ucGlobalWeighting, // weighting * 8 : if a_ucGlobalWeighting == 8, then weighting value = 1
                            const INT8 *restrict a_pcWeightingCurve,
						    const UINT8 *restrict a_pucPixelWeightingTable, // 0 ~ 16 each pixel
                            UINT8 *restrict a_pucImgYUYVOutBuf
                            )
                            
{

    UINT32 ulX, ulY;
    UINT32 ulSrcPitch = (a_ulBufferWidth<<1);
    UINT32 ulDestPitch = ((a_ulBufferWidth-2)<<1);

    const UINT8 * pucSrcRow1 = a_pucImgYUYVBuf;
    const UINT8 * pucSrcRow2 = pucSrcRow1 + ulSrcPitch;
    const UINT8 * pucSrcRow3 = pucSrcRow2 + ulSrcPitch;
    const UINT8 * pucPixelWeightingLine = a_pucPixelWeightingTable + a_ulBufferWidth + 1;
    const UINT8 * pucPixelWeightingPtr = pucPixelWeightingLine;
    const UINT8 * pucSrcLine = a_pucImgYUYVBuf + ulSrcPitch + 2;
    const UINT8 * pucSrcPtr = pucSrcLine;
    UINT8 * pucDestLine = a_pucImgYUYVOutBuf/* + ulDestPitch + 2*/;
    UINT8 * pucDestPtr = pucDestLine;

#ifdef WIN32
    unsigned int            *pulOUT;
#endif      
    /* Unsharp Mask : { 1, 2, 1, 2, 4, 2, 1, 2, 1 } */
    const INT8 acSharpMask[9] = { -1, -2, -1, -2, 12, -2, -1, -2, -1 };
    const short wShiftSharp = 4;      // Use Weighting Table : g_acSharpenTable
    /* Point to the end of the mask to account for rotation */
    const char *mask_rot = &acSharpMask[3*3 - 1];


    unsigned int        mask1_0,        mask2_0,        mask3_0;
    unsigned int        mask1_1,        mask2_1,        mask3_1;
    unsigned int        mask_tmp;

    unsigned int        r1_7654,        r1_3210;
    unsigned int        r2_7654,        r2_3210;
    unsigned int        r3_7654,        r3_3210;
    
    unsigned r1_6420, r2_6420, r3_6420;

#ifdef WIN32
    int64_d  r1_76543210,    r2_76543210,    r3_76543210;
#else
    double  r1_76543210,    r2_76543210,    r3_76543210;
#endif

    const unsigned char	*in0,           *in1,           *in2;
    int                 sum0,           sum1,           sum2;
    int                 sum3;    
    int        sum32,          sum10;
    int        pixel0, pixel1, pixel2, pixel3;
    unsigned int pixel3210, outpixel;
    unsigned int        maxVal;
    
  /*----------------------------------------------------------------------*/
  /*  Read mask values and prepare registers for convolution              */
  /*  Read in reverse to account for mask rotation                        */
  /*----------------------------------------------------------------------*/

    mask_tmp = _mem4_const(&acSharpMask[6]);
    mask1_1  = _packlh2(_swap4(mask_tmp),_swap4(mask_tmp)) & 0xffffff00;

    mask_tmp = _mem4_const(&acSharpMask[3]);
    mask2_1  = _packlh2(_swap4(mask_tmp),_swap4(mask_tmp)) & 0xffffff00;
    
    mask_tmp = _mem4_const(&acSharpMask[0]);
    mask3_1  = _packlh2(_swap4(mask_tmp),_swap4(mask_tmp)) & 0xffffff00;
    
    mask1_0 = _extu(mask1_1, 0, 8);
    mask2_0 = _extu(mask2_1, 0, 8);
    mask3_0 = _extu(mask3_1, 0, 8);    

    maxVal = 0x007F007F;                   /*  127 Max                      */

    
    // Make 3x3 : smoothing + Sharpen
    for(ulY = 0; ulY < a_ulBufferHeight - 2; ulY++, pucSrcLine += ulSrcPitch, pucDestLine += ulDestPitch, pucPixelWeightingLine += a_ulBufferWidth)
    {
        pucSrcPtr = pucSrcLine;
#ifdef WIN32
        pulOUT = (unsigned int *)pucDestLine;
#else                
        pucDestPtr = pucDestLine;
#endif     
        pucPixelWeightingPtr = pucPixelWeightingLine;

        in0 = pucSrcRow1;
        in1 = pucSrcRow2;
        in2 = pucSrcRow3;

        //loop << 2, 
#ifdef WIN32
        for (ulX = 0; ulX < a_ulBufferWidth - 2; ulX+=4, pucSrcPtr+=8, pulOUT+=2, pucPixelWeightingPtr+=4) 
#else
        #pragma MUST_ITERATE(1, ,1)
        for (ulX = 0; ulX < a_ulBufferWidth - 2; ulX+=4, pucSrcPtr+=8, pucDestPtr+=8, pucPixelWeightingPtr+=4) 
#endif     
        {
            //read double == 8bytes once at a time 
#if 0//def WIN32                
            _memd8_const(in0);
            r1_76543210 = g_read8Result;
            _memd8_const(in1);
            r2_76543210 = g_read8Result;
            _memd8_const(in2); 
            r3_76543210 = g_read8Result;
#else            
     
            r1_76543210 = _memd8_const(in0);
            r2_76543210 = _memd8_const(in1);
            r3_76543210 = _memd8_const(in2);   
#endif     
            r1_3210 = _lo(r1_76543210);
            r2_3210 = _lo(r2_76543210);
            r3_3210 = _lo(r3_76543210);
            r1_7654 = _hi(r1_76543210);
            r2_7654 = _hi(r2_76543210);
            r3_7654 = _hi(r3_76543210);               
            //packing 1, 3, 5, 7 of row1, row2, row3 as y
            r1_6420 = _packl4(r1_7654, r1_3210);
            r2_6420 = _packl4(r2_7654, r2_3210); 
            r3_6420 = _packl4(r3_7654, r3_3210);  
                                    
            //process 1st sum1 of convoultion byte0 * mask0 +...
            sum0 = _dotpsu4(mask1_0, r1_6420);                       
            sum0+= _dotpsu4(mask2_0, r2_6420); 
            sum0+= _dotpsu4(mask3_0, r3_6420);
            
            //Process 2nd sum2 of convoultion byte0 * mask0 +...       
            sum1 = (_dotpsu4(mask1_1, r1_6420) + 
                    _dotpsu4(mask2_1, r2_6420) + 
                    _dotpsu4(mask3_1, r3_6420));
        
            sum10 = _spack2(sum1,sum0); //saturate into 16bit ((sum1 & 0x0000FFFF)<<16 | (sum0 & 0x0000FFFF))  
            sum10 = _abs2 (sum10);
            sum10 = _shr2(sum10, wShiftSharp); //do shift
            /* ------------------------------------------------------------------ */
            /*  Update pointers for next iteration                                */
            /* ------------------------------------------------------------------ */
            in0 += 4;
            in1 += 4;
            in2 += 4;          
                  
            //read double == 8bytes once at a time
#if 0//def WIN32
            _memd8_const(in0);
            r1_76543210 = g_read8Result;
            _memd8_const(in1);
            r2_76543210 = g_read8Result;
            _memd8_const(in2); 
            r3_76543210 = g_read8Result;
#else            
     
            r1_76543210 = _memd8_const(in0);
            r2_76543210 = _memd8_const(in1);
            r3_76543210 = _memd8_const(in2);   
#endif      
            r1_3210 = _lo(r1_76543210);
            r2_3210 = _lo(r2_76543210);
            r3_3210 = _lo(r3_76543210);
            r1_7654 = _hi(r1_76543210);
            r2_7654 = _hi(r2_76543210);
            r3_7654 = _hi(r3_76543210);               
            //packing 1, 3, 5, 7 of row1, row2, row3 as y
            r1_6420 = _packl4(r1_7654, r1_3210);
            r2_6420 = _packl4(r2_7654, r2_3210); 
            r3_6420 = _packl4(r3_7654, r3_3210);  
            //process 3rd sum3 of convoultion byte0 * mask0 +...
            sum2 = (_dotpsu4(mask1_0, r1_6420) +                       
                    _dotpsu4(mask2_0, r2_6420) + 
                    _dotpsu4(mask3_0, r3_6420));
            //Process 4th sum4 of convoultion byte0 * mask0 +...
            sum3 = (_dotpsu4(mask1_1, r1_6420) + 
                    _dotpsu4(mask2_1, r2_6420) + 
                    _dotpsu4(mask3_1, r3_6420));            
            //pack sum1+sum2+sum3+sum4 with satuation 0~255   
                     
            sum32 = _spack2(sum3,sum2);
            sum32 = _abs2 (sum32);            
            sum32 = _shr2(sum32, wShiftSharp); //do shift

            /* ------------------------------------------------------------------ */
            /*  Update pointers for next iteration                                */
            /* ------------------------------------------------------------------ */
            in0 += 4;
            in1 += 4;
            in2 += 4;              
            //calculate weightiing    
            // if((udelta > 127))udelta = 127;  
            sum10 = _min2(sum10, maxVal); 
            sum32 = _min2(sum32, maxVal);
            
            pixel0 = (((INT32)(*(a_pcWeightingCurve + (sum10&0xff))) * (*(pucPixelWeightingPtr) * (INT32)a_ucGlobalWeighting)) >> (8/*PixelWeighting*/+3/*GlobalWeighting*/));     
            pixel0 = (INT32)(sum0 & 0x80000000)? (*pucSrcPtr-pixel0):(*pucSrcPtr+pixel0);                

            pixel1 = (((INT32)(*(a_pcWeightingCurve + (_unpkhu4(sum10)&0xff))) * (*(pucPixelWeightingPtr+1) * (INT32)a_ucGlobalWeighting)) >> (8/*PixelWeighting*/+3/*GlobalWeighting*/));     
            pixel1 = (INT32)(sum1 & 0x80000000)? (*(pucSrcPtr+2)-pixel1):(*(pucSrcPtr+2)+pixel1);   
          
            pixel2 = (((INT32)(*(a_pcWeightingCurve + (sum32&0xff))) * (*(pucPixelWeightingPtr+2) * (INT32)a_ucGlobalWeighting)) >> (8/*PixelWeighting*/+3/*GlobalWeighting*/));     
            pixel2 = (INT32)(sum2 & 0x80000000)? (*(pucSrcPtr+4)-pixel2):(*(pucSrcPtr+4)+pixel2); 
            
            pixel3 = (((INT32)(*(a_pcWeightingCurve + (_unpkhu4(sum32)&0xff))) * (*(pucPixelWeightingPtr+3) * (INT32)a_ucGlobalWeighting)) >> (8/*PixelWeighting*/+3/*GlobalWeighting*/));     
            pixel3 = (INT32)(sum3 & 0x80000000)? (*(pucSrcPtr+6)-pixel3):(*(pucSrcPtr+6)+pixel3);            
            
            sum10 = _spack2(pixel1,pixel0);       
            sum32 = _spack2(pixel3,pixel2); 
            //((lNewPixel > 255) ? 255 : ((lNewPixel < 0) ? 0 : lNewPixel));
            pixel3210 = _spacku4(sum32, sum10); 
            //prepared ouptut data 

            outpixel = _unpklu4 (pixel3210); 
#ifdef WIN32
            *pulOUT = (outpixel|(*(pucSrcPtr+1)&0xff)<<8|(*(pucSrcPtr+3)&0xff)<<24);
#else       
            _mem4 ((void *)pucDestPtr) =  (outpixel|(*(pucSrcPtr+1)&0xff)<<8|(*(pucSrcPtr+3)&0xff)<<24);
#endif     
            outpixel = _unpkhu4(pixel3210);            
#ifdef WIN32
            *(pulOUT + 1) = (outpixel|(*(pucSrcPtr+5)&0xff)<<8|(*(pucSrcPtr+7)&0xff)<<24); 
#else 
            _mem4 ((void *)(pucDestPtr + 4)) = (outpixel|(*(pucSrcPtr+5)&0xff)<<8|(*(pucSrcPtr+7)&0xff)<<24); 
#endif                                                        

        }

        pucSrcRow1 += ulSrcPitch;
        pucSrcRow2 += ulSrcPitch;
        pucSrcRow3 += ulSrcPitch;
    }
  
}     
#endif
//void ImgProc_SharpenByUnSharpMask(  UINT8 * a_pucImgYUYVBuf, 
//                                    const UINT32 a_ulImgWidth, const UINT32 a_ulImgHeight, 
//                                    const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
//                                    const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
//                                    const UINT8 a_ucWeightingCurveIndex,
//									UINT8 * a_pucPixelWeightingTable,
//                                    const UINT8 a_ucSharpnessLevel,
//                                    const UINT32 a_aulBlockRegion[][4],
//                                    const UINT8 a_ucBlockCnt
//                                    )
//{
//
//    SharpenByUnSharpMask(a_pucImgYUYVBuf, a_ulImgWidth, a_ulImgHeight, a_ucSharpnessLevel, g_acHFWeightingCurveTable[a_ucWeightingCurveIndex], a_pucPixelWeightingTable);
//
//}
///////////////////////////////////////////////////////////////////////////////

void ImgProc_SharpenByUnSharpMask(  UINT8 * restrict a_pucImgYUYVBuf, 
                                    const UINT32 a_ulImgWidth, const UINT32 a_ulImgHeight, 
                                    const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                                    const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                                    const UINT8 a_ucWeightingCurveIndex,
									UINT8 * a_pucPixelWeightingTable,
                                    const UINT8 a_ucSharpnessLevel,
                                    const UINT32 a_aulBlockRegion[][4],
                                    const UINT8 a_ucBlockCnt
                                    )
{
#define SRAM_BASE_PIN_PONG_SIZE     (97792) // = (192*1024 - 1024) / 2
#define SRAM_DEST_OFFSET            (39116) // = 97792*2/5
#define SRAM_WT_OFFSET              (78233) // = 97792*4/5
#define SRAM_CURVE_TABLE            (195584)// = 192*1024 - 1024       

    UINT32 ulSectionIndex = 0;
    UINT32 ulSectionCnt = a_ucBlockCnt;

    UINT32 ulSectionID = 0;

    assert((a_ulProcStartX + a_ulProcWidth) <= a_ulImgWidth && (a_ulProcStartY + a_ulProcHeight) <= a_ulProcHeight);
    memcpy((INT8 *)g_L2_SRAM_ROI_DSP+SRAM_CURVE_TABLE, (INT8 *)g_acHFWeightingCurveTable[a_ucWeightingCurveIndex], 128); 

    for(ulSectionIndex = 0; ulSectionIndex < ulSectionCnt + 1; ulSectionIndex++)
    {

        // Copy data of current section
        if(ulSectionIndex < ulSectionCnt) 
        {
            assert(((a_aulBlockRegion[ulSectionIndex][2] * a_aulBlockRegion[ulSectionIndex][3]) << 1) < SRAM_DEST_OFFSET);

            ulSectionID = (ulSectionIndex & 0x1); // 耞琌案计┪琌计 for pin-pong buffer

            assert((a_aulBlockRegion[ulSectionIndex][2]<<1) * a_aulBlockRegion[ulSectionIndex][3] < SRAM_DEST_OFFSET);

            DAT_copy2d(
                DAT_2D1D, 
                a_pucImgYUYVBuf + ((a_ulProcStartX + a_aulBlockRegion[ulSectionIndex][0] + (a_ulProcStartY + a_aulBlockRegion[ulSectionIndex][1]) * a_ulImgWidth)<<1),
                g_L2_SRAM_ROI_DMA + ulSectionID * SRAM_BASE_PIN_PONG_SIZE, 
                (a_aulBlockRegion[ulSectionIndex][2]<<1), 
                a_aulBlockRegion[ulSectionIndex][3], 
                (a_ulImgWidth<<1));

            DAT_copy2d(
                DAT_2D1D, 
                a_pucPixelWeightingTable + (a_ulProcStartX + a_aulBlockRegion[ulSectionIndex][0] + (a_ulProcStartY + a_aulBlockRegion[ulSectionIndex][1]) * a_ulImgWidth),
                g_L2_SRAM_ROI_DMA + ulSectionID * SRAM_BASE_PIN_PONG_SIZE + SRAM_WT_OFFSET, 
                a_aulBlockRegion[ulSectionIndex][2], 
                a_aulBlockRegion[ulSectionIndex][3], 
                a_ulImgWidth);
        }

        // Process the previous section
        if(ulSectionIndex > 0)
        {	
            ulSectionID = ((ulSectionIndex - 1)&0x1); // 耞琌案计┪琌计 for pin-pong buffer

            // Do Sharpness
            SharpenByUnSharpMask(
                g_L2_SRAM_ROI_DSP + ulSectionID * SRAM_BASE_PIN_PONG_SIZE, 
                a_aulBlockRegion[ulSectionIndex - 1][2], 
                a_aulBlockRegion[ulSectionIndex - 1][3], 
                a_ucSharpnessLevel,
                g_L2_SRAM_ROI_DSP + SRAM_CURVE_TABLE,
                g_L2_SRAM_ROI_DSP + ulSectionID * SRAM_BASE_PIN_PONG_SIZE + SRAM_WT_OFFSET,
                g_L2_SRAM_ROI_DSP + ulSectionID * SRAM_BASE_PIN_PONG_SIZE + SRAM_DEST_OFFSET);
 
            DAT_wait(DAT_XFRID_WAITALL);	

            DAT_copy2d(
                DAT_1D2D,
                g_L2_SRAM_ROI_DMA + ulSectionID * SRAM_BASE_PIN_PONG_SIZE + SRAM_DEST_OFFSET, 
                a_pucImgYUYVBuf + ((a_ulProcStartX + a_aulBlockRegion[ulSectionIndex - 1][0] + 1 + (a_ulProcStartY + a_aulBlockRegion[ulSectionIndex - 1][1] + 1) * a_ulImgWidth)<<1),
                ((a_aulBlockRegion[ulSectionIndex - 1][2]-2)<<1), 
                a_aulBlockRegion[ulSectionIndex - 1][3]-2, 
                (a_ulImgWidth<<1)
                );

        }
        else
        {
            DAT_wait(DAT_XFRID_WAITALL);	
        }
    }

#undef SRAM_BASE_PIN_PONG_SIZE
#undef SRAM_DEST_OFFSET
#undef SRAM_WT_OFFSET
#undef SRAM_CURVE_TABLE

}

