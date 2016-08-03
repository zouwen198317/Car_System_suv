
#include "alTILibDef.h"

#ifdef WIN32
int VLIB_convertYUYVpl_to_YUVint( const unsigned char *restrict a_pucY, 
                                    const unsigned char *restrict a_pucCb, 
                                    const unsigned char *restrict a_pucCr,
                                    int a_lWidth,
                                    int a_lPitch,
                                    int a_lHeight,
                                    unsigned char *restrict a_pucYC)
{

    unsigned int h, w;    
    volatile unsigned char *pDWord;   
    volatile unsigned char *YWord;
    volatile unsigned char  *UWord, *VWord; 
    YWord = (volatile unsigned char *)a_pucY;
    UWord = (volatile unsigned char *)a_pucCb;  
    VWord = (volatile unsigned char *)a_pucCr;  
    pDWord = (volatile unsigned char *)a_pucYC; 
    
	for(h = 0;h < (unsigned int)(a_lHeight); h++)
	{   
	    for(w = 0;w < (unsigned int)(a_lWidth*2); w+=4)   
        {
            pDWord[(h*a_lPitch*2)+ w] = *YWord++;
    
            pDWord[(h*a_lPitch*2)+w+1] = *UWord++;
            
            pDWord[(h*a_lPitch*2)+w+2] = *YWord++;
                     
            pDWord[(h*a_lPitch*2)+w+3] = *VWord++;
        }
	} 
	
    return 1;
}
#endif

