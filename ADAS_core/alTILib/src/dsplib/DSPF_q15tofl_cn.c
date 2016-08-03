/* ======================================================================= */
/* DSPF_q15tofl_cn.c -- Q15 to Float Conversion                            */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_q15tofl_cn, ".text:ansi");
#endif

#include "DSPF_q15tofl_cn.h"

void DSPF_q15tofl_cn(const short *x, float *y, const int n)
{
    int i;

    for (i = 0; i < n; i++)
        y[i] = (float)x[i] / 0x8000;
}

/* ======================================================================= */
/*  End of file:  DSPF_q15tofl_cn.c                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

