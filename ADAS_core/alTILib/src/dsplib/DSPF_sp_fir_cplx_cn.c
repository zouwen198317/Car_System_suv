/* ======================================================================= */
/* DSP_fir_cplx_cn.c -- Complex FIR Filter                                 */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_fir_cplx_cn, ".text:ansi");
#endif

#include "DSPF_sp_fir_cplx_cn.h"

void DSPF_sp_fir_cplx_cn(const float *x, const float *h,
    float *y, int nh, int ny)
{
    int i, j;
    float imag, real;

    for (i = 0; i < 2*ny; i += 2)
    {
        imag = 0;
        real = 0;

        for (j = 0; j < 2*nh; j += 2)
        {
            real += h[j] * x[i-j] - h[j+1] * x[i+1-j];
            imag += h[j] * x[i+1-j] + h[j+1] * x[i-j];
        }

        y[i] = real;
        y[i+1] = imag;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_fir_cplx_cn.c                                    */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

