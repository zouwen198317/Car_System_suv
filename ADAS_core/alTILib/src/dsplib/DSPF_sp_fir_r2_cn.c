/* ======================================================================= */
/* DSPF_sp_fir_r2_cn.c -- FIR Filter                                       */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_fir_r2_cn, ".text:ansi");
#endif

#include "DSPF_sp_fir_r2_cn.h"

void DSPF_sp_fir_r2_cn(const float *x, const float *h,
    float *y, const int nh, const int ny)
{
    int i, j;
    float sum;

    for (j = 0; j < ny; j++)
    {
        sum = 0;

        // note: h coeffs given in reverse order: { h[nh-1], h[nh-2], ..., h[0] }
        for (i = 0; i < nh; i++)
            sum += x[i + j] * h[i];
        
        y[j] = sum;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_fir_r2_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

