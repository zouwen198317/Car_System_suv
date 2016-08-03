/* ======================================================================= */
/* DSP_mat_trans_cn.c -- Matrix Transpose                                  */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_mat_trans_cn, ".text:ansi");
#endif

#include "DSPF_sp_mat_trans_cn.h"

void DSPF_sp_mat_trans_cn(const float *x, const int rows,
    const int cols, float *y)
{
    int i, j;

    for(i = 0; i < cols; i++)
        for(j = 0; j < rows; j++)
            y[i * rows + j] = x[i + cols * j];
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_mat_trans_cn.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

