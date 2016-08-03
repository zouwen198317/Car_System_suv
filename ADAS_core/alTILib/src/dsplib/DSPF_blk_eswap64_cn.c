/* ======================================================================= */
/* DSPF_blk_eswap64_cn.c -- Endian Swap (64-bit)                           */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_blk_eswap64_cn, ".text:ansi");
#endif

#include "DSPF_blk_eswap64_cn.h"

void DSPF_blk_eswap64_cn(void *x, void *y, const int n)
{
    int i;
    char *_src, *_dst;

    // swap endianness in place if y == NULL
    _src = (char *)x;
    if (y)
        _dst = (char *)y;
    else
        _dst = (char *)x;

    for (i = 0; i < n; i++)
    {
        char t0, t1, t2, t3, t4, t5, t6, t7;

        t0 = _src[i*8 + 7];
        t1 = _src[i*8 + 6];
        t2 = _src[i*8 + 5];
        t3 = _src[i*8 + 4];
        t4 = _src[i*8 + 3];
        t5 = _src[i*8 + 2];
        t6 = _src[i*8 + 1];
        t7 = _src[i*8 + 0];

        _dst[i*8 + 0] = t0;
        _dst[i*8 + 1] = t1;
        _dst[i*8 + 2] = t2;
        _dst[i*8 + 3] = t3;
        _dst[i*8 + 4] = t4;
        _dst[i*8 + 5] = t5;
        _dst[i*8 + 6] = t6;
        _dst[i*8 + 7] = t7;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_blk_eswap64_cn.c                                    */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

