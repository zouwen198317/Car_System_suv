
#include "alTILibDef.h"

#ifdef WIN32
int VLIB_extractLumaFromYUYV( const unsigned char * restrict a_pucSrcBuf,
                                int a_lWidth,
                                int a_lPitch,
                                int a_lHeight,
                                unsigned char * restrict a_pucY
                                )
{
    unsigned int h, w;    
    volatile unsigned char *pDWord;   
    volatile unsigned char *YWord;
    YWord = (volatile unsigned char *)a_pucY;
    pDWord = (volatile unsigned char *)a_pucSrcBuf; 
    
	for(h = 0;h < (unsigned int)(a_lHeight); h++)
	{   
	    for(w = 0;w < (unsigned int)(a_lWidth*2); w+=4)   
        {
            *YWord++ = pDWord[(h*a_lPitch*2)+ w];
            *YWord++ = pDWord[(h*a_lPitch*2)+w+2];
        }
        
	} 

    return 1;
}
#endif

