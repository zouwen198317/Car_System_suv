/* ======================================================================= */
/* DSPF_sp_vecsum_sq_cn.c -- Vector Sum Squared                            */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_vecsum_sq_cn, ".text:ansi");
#endif

#include "DSPF_sp_vecsum_sq_cn.h"

float DSPF_sp_vecsum_sq_cn(const float *x, const int n)
{
    int i;
    float sum = 0;

    for(i = 0; i < n; i++ )
        sum += x[i] * x[i];

    return sum;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_vecsum_sq_cn.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

