/* ======================================================================= */
/* DSP_dotprod_cn.c -- Dot Product                                         */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_dotprod_cn, ".text:ansi");
#endif

#include "DSPF_sp_dotprod_cn.h"

float DSPF_sp_dotprod_cn(const float *x, const float *y, const int n)
{
    int i;
    float sum = 0;

    for (i = 0; i < n; i++)
        sum += x[i] * y[i];

    return sum;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_dotprod_cn.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

