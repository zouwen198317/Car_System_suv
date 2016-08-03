
#if 0//def WIN32 // already defined in VLIB_prototypes.h & vlib.lib

INT32 VLIB_convertUYVYsemipl_to_YUVpl(  const UINT8 * a_pucCrCb,
                                        INT32 a_lWidth,      
                                        INT32 a_lPitch,
                                        INT32 a_lHeight,                
                                        UINT8 *restrict a_pucCr,
                                        UINT8 *restrict a_pucCb)
{

    INT32 lX, lY;
    UINT32 ulRowIndex, ulPixelIndex;

    for(lY = 0, ulRowIndex = 0; lY < a_lHeight; lY++, ulRowIndex+=a_lPitch)
    {
        for(lX = 0; lX < a_lWidth; lX++)
        {
            ulPixelIndex = ulRowIndex + lX;
            a_pucCr[ulPixelIndex] = a_pucCrCb[(ulPixelIndex<<1) + 0];
            a_pucCb[ulPixelIndex] = a_pucCrCb[(ulPixelIndex<<1) + 1];
        }
    }

    return 1;
}

#endif