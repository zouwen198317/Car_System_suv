/* ======================================================================= */
/* DSP_mat_mul_cn.c -- Matrix Multiply                                     */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_mat_mul_cn, ".text:ansi");
#endif

#include "DSPF_sp_mat_mul_cn.h"

void DSPF_sp_mat_mul_cn(float *x1, const int r1, const int c1,
    float *x2, const int c2, float *y)
{
    int i, j, k;
    float sum;

    // Multiply each row in x1 by each column in x2.
    // The product of row m in x1 and column n in x2 is placed
    // in position (m,n) in the result.
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
        {
            sum = 0;

            for (k = 0; k < c1; k++)
                sum += x1[k + i * c1] * x2[j + k * c2];

            y[j + i * c2] = sum;
        }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_mat_mul_cn.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

