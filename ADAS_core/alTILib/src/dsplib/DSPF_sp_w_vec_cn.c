/* ======================================================================= */
/* DSPF_sp_w_vec_cn.c -- Vector Weighted Add                               */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_w_vec_cn, ".text:ansi");
#endif

#include "DSPF_sp_w_vec_cn.h"

void DSPF_sp_w_vec_cn(const float *x1, const float *x2, const float m,
    float *y, const int n)
{
    int i;

    for (i = 0; i < n; i++)
        y[i] = (m * x1[i]) + x2[i];
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_w_vec_cn.c                                       */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

