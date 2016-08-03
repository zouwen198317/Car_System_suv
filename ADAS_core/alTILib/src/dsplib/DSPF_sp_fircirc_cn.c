/* ======================================================================= */
/* DSP_fircirc_cn.c -- Circular FIR Filter                                 */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_fircirc_cn, ".text:ansi");
#endif

#include "DSPF_sp_fircirc_cn.h"

void DSPF_sp_fircirc_cn(const float *x, const float *h, float *y,
    const int index, const int csize, const int nh, const int ny)
{
    //Circular Buffer block size = ((2^(csize + 1)) / 4)
    //floating point numbers
    int i, j, mod = (1 << (csize - 1));
    float sum;

    for (i = 0; i < ny; i++)
    {
        sum = 0;

        for (j = 0; j < nh; j++)
        {
            //Operation "% mod" is equivalent to "& (mod -1)"
            //sum += x[(i + j + index) % mod] * h[j];
            sum += x[(i + j + index) & (mod - 1)] * h[j];
        }

        y[i] = sum;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_fircirc_cn.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

