
#include "alTILibDef.h"

#ifdef WIN32
int VLIB_convertYUYVint_to_YUVpl(const unsigned char * a_pucSrcBuf,
                                   int a_lWidth,
                                   int a_lPitch, 
                                   int a_lHeight,
                                   unsigned char * a_pucY,
                                   unsigned char * a_pucCb,
                                   unsigned char * a_pucCr                                        
                                   )
{

    unsigned int h, w;    
    volatile unsigned char *pDWord;   
    volatile unsigned char *YWord;
    volatile unsigned char  *UWord, *VWord; 
    YWord = (volatile unsigned char *)a_pucY;
    UWord = (volatile unsigned char *)a_pucCb;  
    VWord = (volatile unsigned char *)a_pucCr;  
    pDWord = (volatile unsigned char *)a_pucSrcBuf; 
    
	for(h = 0;h < (unsigned int)(a_lHeight); h++)
	{   
	    for(w = 0;w < (unsigned int)(a_lWidth*2); w+=4)   
        {
            *YWord++ = pDWord[(h*a_lPitch*2)+ w];
    
            *UWord++ = pDWord[(h*a_lPitch*2)+w+1];
            
            *YWord++ = pDWord[(h*a_lPitch*2)+w+2];
                     
            *VWord++ = pDWord[(h*a_lPitch*2)+w+3];
        }
        
	} 
	
    return 1;
}
#endif

