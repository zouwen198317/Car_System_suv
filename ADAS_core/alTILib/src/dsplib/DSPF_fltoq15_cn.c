/* ======================================================================= */
/* DSPF_fltoq15_cn.c -- Float to Q15 Conversion                            */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_fltoq15_cn, ".text:ansi");
#endif

#include "DSPF_fltoq15_cn.h"
#include <math.h>

void DSPF_fltoq15_cn(const float *x, short *y, const int n)
{
    int i, a;

    for(i = 0; i < n; i++)
    {
        a = (int)(floor(32768 * x[i]));
        // saturate to 16-bit //
        if (a > 32767) a = 32767;
        if (a < -32768) a = -32768;
        y[i] = (short) a;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_fltoq15_cn.c                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

