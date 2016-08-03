/* ======================================================================= */
/* DSPF_sp_iirlat_cn.c -- Lattice IIR Filter                               */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_iirlat_cn, ".text:ansi");
#endif

#include "DSPF_sp_iirlat_cn.h"

void DSPF_sp_iirlat_cn(const float *x, const int nx,
    const float *k, const int nk, float *b,
    float *y)
{
    float yt; // output //
    int i, j;

    for (j = 0; j < nx; j++)
    {
        yt = x[j];

        for (i = nk - 1; i >= 0; i--)
        {
            yt = yt - b[i] * k[i];
            b[i + 1] = b[i] + yt * k[i];
        }

        b[0] = yt;
        y[j] = yt;
    }
}                                                       

/* ======================================================================= */
/*  End of file:  DSPF_sp_iirlat_cn.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

