/* ======================================================================= */
/* DSPF_sp_minval_cn.c -- Min Value                                        */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_minval_cn, ".text:ansi");
#endif

#include <float.h>
#include "DSPF_sp_minval_cn.h"

float DSPF_sp_minval_cn(const float *x, int nx)
{
    int i;
    float min;

    min = FLT_MAX;
    for (i = 0; i < nx; i++)
        if (x[i] < min)
            min = x[i];

    return min;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_minval_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

