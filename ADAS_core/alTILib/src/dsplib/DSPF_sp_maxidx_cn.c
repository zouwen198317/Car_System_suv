/* ======================================================================= */
/* DSPF_sp_maxidx_cn.c -- Max Value Index                                  */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_maxidx_cn, ".text:ansi");
#endif

#include <float.h>
#include "DSPF_sp_maxidx_cn.h"

int DSPF_sp_maxidx_cn(const float *x, int n)
{
    int i, index;
    float max;

    max = -(FLT_MAX);
    for (i = 0; i < n; i++)
        if (x[i] > max)
        {
            max = x[i];
            index = i;
        }

    return index;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_maxidx_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

