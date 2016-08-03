
#include <assert.h>
#include "ImageProc.h"
#include "IMGLib.h"
#include "VisionMeIntrinsic.h"

#ifndef WIN32
#pragma CODE_SECTION(ImgProc_QuarterDownScaling, ".text:intrinsic");
#endif

#if (defined(WIN32) && (PC_USE_INTRINSIC_CODE == 0))

void ImgProc_QuarterDownScaling(
                                const UINT8 *restrict a_pucSrc,
                                UINT8 *restrict a_pucDst, 
                                INT32 a_lSrcWidth, 
                                INT32 a_lDstWidth, 
                                INT32 a_lBlkWidth, 
                                INT32 a_lBlkHeight)
{
	INT32 lX, lY, lXoffset, lYoffset, lSum;

	for(lY = 0;lY < a_lBlkHeight;lY+=4)
	{
		for(lX = 0;lX < a_lBlkWidth;lX+=4)
		{
			lSum = 0;
			for(lYoffset = 0; lYoffset < 4; lYoffset++)
			{
				for(lXoffset = 0; lXoffset < 4; lXoffset++)
				{
					lSum += *(a_pucSrc + (lX + lXoffset) + (lY + lYoffset) * a_lSrcWidth);
				}
			}

            lSum = (lSum>>4);
            // sum 為整數，無小數，無法做四捨五入
            //sum = (INT32)((sum > 0) ? (sum+0.5) : (sum-0.5));
            *(a_pucDst + (lX>>2) + (lY>>2)*a_lDstWidth) = (lSum & 0x80000000)?0:((lSum & 0x7fffff00)?255:lSum);
		}
	}
}

#else

void ImgProc_QuarterDownScaling
(
    const UINT8 *restrict a_pucSrc,
    UINT8 *restrict a_pucDst, 
    INT32 a_lSrcWidth, 
    INT32 a_lDstWidth, 
    INT32 a_lBlkWidth, 
    INT32 a_lBlkHeight
    )
{

    int x,y,/*i ,j,*/sum;
    unsigned int data, data1, data2, data3;
    int mult1   = 0x01010101;
    const   unsigned char   *IN1,    *IN2,    *IN3,  *IN4;
    _nassert(a_lBlkWidth > 4);
    _nassert(a_lBlkWidth % 4 == 0);        

    for(y = 0;y < a_lBlkHeight; y+=4)
    {
        IN1     =   a_pucSrc+ y*a_lSrcWidth;
        IN2     =   IN1+ a_lSrcWidth;
        IN3     =   IN2+ a_lSrcWidth;
        IN4     =   IN3+ a_lSrcWidth;
#ifndef WIN32
        #pragma MUST_ITERATE(1, ,1)  
#endif
        for(x = 0;x < a_lBlkWidth; x+=4)
        {
            data = _mem4_const(IN1 + x);
            data1 = _mem4_const(IN2 + x); 
            data2 = _mem4_const(IN3 + x);
            data3 = _mem4_const(IN4 + x);

            sum = (_dotpsu4( mult1, data) + 
            _dotpsu4( mult1, data1)+  
            _dotpsu4( mult1, data2)+
            _dotpsu4( mult1, data3))>>4;

            sum = (int)((sum > 0) ? (sum+0.5) : (sum-0.5));
            *(a_pucDst + (x>>2) + (y>>2)*a_lDstWidth) = (sum & 0x80000000)?0:((sum & 0x7fffff00)?255:sum);
        }
    }
}

#endif
