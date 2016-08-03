/* ======================================================================= */
/* DSP_mat_mul_cplx_cn.c -- Complex Matrix Multiply                        */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_mat_mul_cplx_cn, ".text:ansi");
#endif

#include "DSPF_sp_mat_mul_cplx_cn.h"

void DSPF_sp_mat_mul_cplx_cn(const float *x1, const int r1, const int c1,
    const float *x2, const int c2, float *y)
{
    float real, imag;
    int i, j, k;

    for(i = 0; i < r1; i++)
        for(j = 0; j < c2; j++)
        {
            real = 0;
            imag = 0;

            for(k = 0; k < c1; k++)
            {
                real += (x1[i * 2 * c1 + 2 * k] * x2[k * 2 * c2 + 2 * j]
                        - x1[i * 2 * c1 + 2 * k + 1] * x2[k * 2 * c2 + 2 * j + 1]);
                imag += (x1[i * 2 * c1 + 2 * k] * x2[k * 2 * c2 + 2 * j + 1]
                        + x1[i * 2 * c1 + 2 * k + 1] * x2[k * 2 * c2 + 2 * j]);
            }

            y[i * 2 * c2 + 2 * j] = real;
            y[i * 2 * c2 + 2 * j + 1] = imag;
        }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_mat_mul_cplx_cn.c                                */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

