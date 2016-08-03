/* ======================================================================= */
/* DSPF_sp_iir_cn.c -- IIR Filter                                          */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_iir_cn, ".text:ansi");
#endif

#include "DSPF_sp_iir_cn.h"

void DSPF_sp_iir_cn (float *y1,                
    const float *x,                                     
    float *y2,                                 
    const float *hb,                                    
    const float *ha,                                    
    int n)                                              
{                                                       
    int i, j;                                           
    float sum;                                          
                                                        
    for (i = 0; i < n; i++)                             
    {                                                   
        sum = hb[0] * x[4+i];                           
        for (j = 1; j <= 4; j++)                        
            sum += hb[j] * x[4+i-j] - ha[j] * y1[4+i-j];
                                                        
        y1[4+i] = sum;                                  
        y2[i] = y1[4+i];                                
    }                                                   
}                                                       

/* ======================================================================= */
/*  End of file:  DSPF_sp_iir_cn.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

