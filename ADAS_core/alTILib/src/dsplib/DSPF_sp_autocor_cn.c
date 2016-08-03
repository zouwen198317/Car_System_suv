/* ======================================================================= */
/* DSP_autocor_cn.c -- Autocorrelation                                     */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_autocor_cn, ".text:ansi");
#endif

#include "DSPF_sp_autocor_cn.h"

void DSPF_sp_autocor_cn(float *r, const float *x, const int nx, const int nr)
{
    int i,k;
    float sum;
    for (i = 0; i < nr; i++)
    {
        sum = 0;
        for (k = nr; k < nx+nr; k++)
            sum += x[k] * x[k-i];
        r[i] = sum ;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_autocor_cn.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

