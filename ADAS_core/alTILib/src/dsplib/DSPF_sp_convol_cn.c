/* ======================================================================= */
/* DSP_convol_cn.c -- Convolution                                          */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_convol_cn, ".text:ansi");
#endif

#include "DSPF_sp_convol_cn.h"

void DSPF_sp_convol_cn(const float *x, const float *h,
    float *y, const short nh, const short ny)
{
    short i, j;
    float sum;

    for (i = ny; i > 0; i--)
    {
        sum = 0;

        for (j = nh; j > 0; j--)
            sum += x[ny - i + nh - j] * h[j - 1];

        y[ny - i] = sum;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_convol_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

