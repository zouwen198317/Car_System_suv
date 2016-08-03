/* ======================================================================= */
/* DSP_dotp_cplx_cn.c -- Complex Dot Product                               */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_dotp_cplx_cn, ".text:ansi");
#endif

#include "DSPF_sp_dotp_cplx_cn.h"

void DSPF_sp_dotp_cplx_cn(const float* x, const float* y, int n,
    float *re, float *im)
{
    float real = 0, imag = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        real += (x[2 * i] * y[2 * i] - x[2 * i + 1] * y[2 * i + 1]);
        imag += (x[2 * i] * y[2 * i + 1] + x[2 * i + 1] * y[2 * i]);
    }

    *re = real;
    *im = imag;
}                                                 

/* ======================================================================= */
/*  End of file:  DSPF_sp_dotp_cplx_cn.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

