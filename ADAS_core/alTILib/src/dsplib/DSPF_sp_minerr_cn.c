/* ======================================================================= */
/* DSPF_sp_minerr_cn.c -- Vocoder Codebook Search                          */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_minerr_cn, ".text:ansi");
#endif

#include "DSPF_sp_minerr_cn.h"

#define GSP0_NUM    (256)
#define GSP0_TERMS    (9)

float DSPF_sp_minerr_cn(const float *GSP0_TABLE,
    const float *errCoefs, int *max_index)
{
    float val, maxVal = -50;
    int i, j;

    for (i = 0; i < GSP0_NUM; i++)
    {
        for (val = 0, j = 0; j < GSP0_TERMS; j++)
            val += GSP0_TABLE[i * GSP0_TERMS + j] * errCoefs[j];

        if (val > maxVal)
        {
            maxVal = val;
            *max_index = i * GSP0_TERMS;
        }
    }

    return (maxVal);
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_minerr_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

