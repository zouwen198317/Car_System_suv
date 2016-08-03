
#include "ImageProc.h"
#include "IMGLib.h"

//////////////////////////////////////////////////////////////////////////
void ImgProc_7x7Convolution(const UINT8 * restrict a_pucImgBuf, 
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            const INT8 * restrict a_pcMask,
                            INT16 wShift,
                            UINT8 * restrict a_pucImgOutBuf
                            )
{

    UINT32 ulY, ulRowIndex;

    ulRowIndex = a_ulProcStartY * a_ulBufferWidth;
    for(ulY = 0; ulY < a_ulProcHeight - 3; ulY++, ulRowIndex += a_ulBufferWidth)
    {
        IMG_conv_7x7_i8_c8s(a_pucImgBuf + ulRowIndex + a_ulProcStartX, a_pucImgOutBuf + ulRowIndex + a_ulProcStartX,
            a_ulProcWidth, a_ulBufferWidth, a_pcMask, wShift);
    }

}
