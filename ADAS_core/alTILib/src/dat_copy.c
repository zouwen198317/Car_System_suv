
#ifdef WIN32

#include <string.h>
#include "dat_copy.h"

//////////////////////////////////////////////////////////////////////////
Uint32 DAT_copy(void *a_pSrc , void *a_pDst , Uint16 a_uwByteCnt)
{
        
    memcpy((Uint8 *)a_pDst, (Uint8 *)a_pSrc, a_uwByteCnt);
    
    return 0;
}

Uint32 DAT_copy2d(Uint32 ulType, void *a_pSrc, void *a_pDst, Uint16 uwLineLen, Uint16 uwLineCnt, Uint16 uwLinePitch)
{
    int i;
    
    switch (ulType) 
    {
        case DAT_1D2D:
            for (i=0; i<uwLineCnt; i++)
                memcpy((Uint8 *)a_pDst + i*uwLinePitch, (Uint8 *)a_pSrc + i*uwLineLen, uwLineLen);        
            break;
            
        case DAT_2D1D:
            for (i=0; i<uwLineCnt; i++)
                memcpy((Uint8 *)a_pDst + i*uwLineLen, (Uint8 *)a_pSrc + i*uwLinePitch, uwLineLen);
            break;
            
        case DAT_2D2D:
            for (i=0; i<uwLineCnt; i++)
                memcpy((Uint8 *)a_pDst + i*uwLinePitch, (Uint8 *)a_pSrc + i*uwLinePitch, uwLineLen);
            break;                        
    }
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////
Uint32 DAT_copy2d2d(void *src, void *dst, Uint16 lineLen,
        Uint16 lineCnt, Uint16 linePitch_src, Uint16 linePitch_dst)
{
    int i;
    for (i=0; i<lineCnt; i++)
        memcpy((Uint8 *)dst + i*linePitch_dst, (Uint8 *)src + i*linePitch_src, lineLen);

    return 0;
}

//////////////////////////////////////////////////////////////////////////
Uint32 DAT_copy2d_lut(Uint32 type, void const * src, void * dst, Uint16 lineLen, Uint16 lineCnt, Uint16 linePitch, Uint16 PixelDepth)
{
#ifdef WIN32
    int i;
#endif

    switch (type) 
    {
        case DAT_1D2D:
#ifndef WIN32
            //source
            stSrcInfo.pBuf         = (uint8_t*) src;
            stSrcInfo.ucPixelDepth = PixelDepth;
            stSrcInfo.uwBufWidth   = lineLen;
            stSrcInfo.uwBufHeight  = lineCnt;
            stSrcInfo.uwStartX     = 0;
            stSrcInfo.uwStartY     = 0;
            stSrcInfo.uwSelWidth   = lineLen;
            stSrcInfo.uwSelHeight  = lineCnt;
            //destination
            stDstInfo.pBuf         = dst;
            stDstInfo.ucPixelDepth = PixelDepth;
            stDstInfo.uwBufWidth   = linePitch;
            stDstInfo.uwBufHeight  = lineCnt;
            stDstInfo.uwStartX     = 0;
            stDstInfo.uwStartY     = 0;
            stDstInfo.uwSelWidth   = linePitch;
            stDstInfo.uwSelHeight  = lineCnt;
    
            DMADRV_Copy2D(&stDstInfo, &stSrcInfo);
#else            
            for (i=0; i<lineCnt; i++)
                memcpy((Uint8 *)dst + i*linePitch*PixelDepth, (Uint8 *)src + i*lineLen*PixelDepth, lineLen*PixelDepth);        
#endif    
            break;
            
        case DAT_2D1D:
#ifndef WIN32
            //source
            stSrcInfo.pBuf         = (uint8_t*) src;
            stSrcInfo.uwBufWidth   = linePitch;
            stSrcInfo.uwBufHeight  = 0;
            stSrcInfo.uwStartX     = 0;
            stSrcInfo.uwStartY     = 0;
            stSrcInfo.ucPixelDepth = PixelDepth;
            stSrcInfo.uwSelWidth   = linePitch;
            stSrcInfo.uwSelHeight  = lineCnt; //BCnt
            //destination
            stDstInfo.pBuf         = dst;
            stDstInfo.uwBufWidth   = lineLen;
            stDstInfo.uwBufHeight  = lineCnt;
            stDstInfo.uwStartX     = 0;
            stDstInfo.uwStartY     = 0;
            stDstInfo.ucPixelDepth = PixelDepth;
            stDstInfo.uwSelWidth   = lineLen;
            stDstInfo.uwSelHeight  = lineCnt;
    
            DMADRV_Copy2D(&stDstInfo, &stSrcInfo);
#else            
            for (i=0; i<lineCnt; i++)
                memcpy((Uint8 *)dst + i*lineLen*PixelDepth, (Uint8 *)src + i*linePitch*PixelDepth, lineLen*PixelDepth);
#endif     
            break;
            
        case DAT_2D2D:

#ifndef WIN32
            //source
            stSrcInfo.pBuf         = (uint8_t*) src;
            stSrcInfo.uwBufWidth   = linePitch;
            stSrcInfo.uwBufHeight  = 0;
            stSrcInfo.uwStartX     = 0;
            stSrcInfo.uwStartY     = 0;
            stSrcInfo.ucPixelDepth = PixelDepth;
            stSrcInfo.uwSelWidth   = lineLen;
            stSrcInfo.uwSelHeight  = lineCnt;
            //destination
            stDstInfo.pBuf         = dst;
            stDstInfo.uwBufWidth   = linePitch;
            stDstInfo.uwBufHeight  = 0;
            stDstInfo.uwStartX     = 0;
            stDstInfo.uwStartY     = 0;
            stDstInfo.ucPixelDepth = PixelDepth;
            stDstInfo.uwSelWidth   = lineLen;
            stDstInfo.uwSelHeight  = lineCnt;
            
            DMADRV_Copy2D(&stDstInfo, &stSrcInfo);            
#else                        
            for (i=0; i<lineCnt; i++)
                memcpy((Uint8 *)dst + i*linePitch*PixelDepth, (Uint8 *)src + i*linePitch*PixelDepth, lineLen*PixelDepth);
#endif     
            break;                        
    }
    
    return 0;
}
//////////////////////////////////////////////////////////////////////////
Uint32 DAT_fill(void *a_pDst , Uint16 a_uwByteCnt, Uint32 *ulValue)
{
    memset(a_pDst, *ulValue, a_uwByteCnt);
    
    return 0;
}


//////////////////////////////////////////////////////////////////////////
void DAT_wait(Uint32 id)
{
}

#endif