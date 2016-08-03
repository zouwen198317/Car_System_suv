
#include "ImageProc.h"
#include "VLib.h"

//////////////////////////////////////////////////////////////////////////
void ImgProc_YUYVint2YUVpl( const UINT8 * restrict a_pucImgYUYVBuf,  
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            UINT8 * restrict a_pucImgYBuf,
                            UINT8 * restrict a_pucImgCbBuf,
                            UINT8 * restrict a_pucImgCrBuf)
{

    VLIB_convertYUYVint_to_YUVpl(a_pucImgYUYVBuf + a_ulProcStartY * a_ulBufferWidth + a_ulProcStartX, 
        a_ulProcWidth, a_ulBufferWidth, a_ulProcHeight, a_pucImgYBuf, a_pucImgCbBuf, a_pucImgCrBuf);

}

//////////////////////////////////////////////////////////////////////////
void ImgProc_YUYVpl2YUVint( const UINT8 * restrict a_pucImgYBuf,
                            const UINT8 * restrict a_pucImgCbBuf,
                            const UINT8 * restrict a_pucImgCrBuf,
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            UINT8 * restrict a_pucImgYUYVBuf 
)
{

    VLIB_convertYUYVpl_to_YUVint( a_pucImgYBuf, a_pucImgCbBuf, a_pucImgCrBuf,
        a_ulProcWidth, a_ulBufferWidth, a_ulProcHeight, 
        a_pucImgYUYVBuf + a_ulProcStartY * a_ulBufferWidth + a_ulProcStartX);

}

//////////////////////////////////////////////////////////////////////////
void ImgProc_YExtractOnly(  UINT8 * restrict a_pucImgYUYVBuf,  
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            UINT8 * restrict a_pucImgYBuf)
{

    VLIB_extractLumaFromYUYV(a_pucImgYUYVBuf + a_ulProcStartY * a_ulBufferWidth + a_ulProcStartX, 
        a_ulProcWidth, a_ulBufferWidth, a_ulProcHeight, a_pucImgYBuf);

}

