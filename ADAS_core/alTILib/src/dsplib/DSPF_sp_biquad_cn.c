/* ======================================================================= */
/* DSPF_sp_biquad_cn.c -- Biquad Filter                                    */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_biquad_cn, ".text:ansi");
#endif

#include "DSPF_sp_biquad_cn.h"

void DSPF_sp_biquad_cn(float *x, float *b, float *a,
    float *delay, float *y, const int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        y[i] = b[0] * x[i] + delay[0];
        delay[0] = b[1] * x[i] - a[1] * y[i] + delay[1];
        delay[1] = b[2] * x[i] - a[2] * y[i]; 
    }
}                                                   

/* ======================================================================= */
/*  End of file:  DSPF_sp_biquad_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

