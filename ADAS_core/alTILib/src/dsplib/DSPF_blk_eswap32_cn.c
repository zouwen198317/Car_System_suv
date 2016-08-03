/* ======================================================================= */
/* DSPF_blk_eswap32_cn.c -- Endian Swap (32-bit)                           */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_blk_eswap32_cn, ".text:ansi");
#endif

#include "DSPF_blk_eswap32_cn.h"

void DSPF_blk_eswap32_cn(void *x, void *y, const int n)
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
        char t0, t1, t2, t3;

        t0 = _src[i * 4 + 3];
        t1 = _src[i * 4 + 2];
        t2 = _src[i * 4 + 1];
        t3 = _src[i * 4 + 0];
        _dst[i * 4 + 0] = t0;
        _dst[i * 4 + 1] = t1;
        _dst[i * 4 + 2] = t2;
        _dst[i * 4 + 3] = t3;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_blk_eswap32_cn.c                                    */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

