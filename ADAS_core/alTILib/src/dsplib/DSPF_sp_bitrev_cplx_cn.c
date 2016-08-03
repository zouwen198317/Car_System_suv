/* ======================================================================= */
/* DSPF_sp_bitrev_cplx_cn.c -- Complex Bit Reversal                        */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_bitrev_cplx_cn, ".text:natural");
#endif

#include "DSPF_sp_bitrev_cplx_cn.h"

void DSPF_sp_bitrev_cplx_cn(double* x, short* index, const int nx)
{
    int i;
    short i0, i1, /*i2,*/ i3;
    short j0, j1, /*j2,*/ j3;
    double xi0, xi1, /*xi2,*/ xi3;
    double xj0, xj1, /*xj2,*/ xj3;
    short t;
    int a, b, ia, ib, ibs;
    int mask;
    int nbits, nbot, ntop, ndiff, n2, halfn;

    nbits = 0;
    i = nx;

    while (i > 1)
    {
        i = i >> 1;
        nbits++;
    }

    nbot = nbits >> 1;
    ndiff = nbits & 1;
    ntop = nbot + ndiff;
    n2 = 1 << ntop;
    mask = n2 - 1;
    halfn = nx >> 1;

    for (i0 = 0; i0 < halfn; i0 += 2)
    {
        b = i0 & mask;
        a = i0 >> nbot;

        if (!b) ia = index[a];
        ib = index[b];
        ibs = ib << nbot;
        j0 = ibs + ia;
        t = i0 < j0;
        xi0 = x[i0];
        xj0 = x[j0];
        if (t)
        {
            x[i0] = xj0;
            x[j0] = xi0;
        }

        i1 = i0 + 1;
        j1 = j0 + halfn;

        xi1 = x[i1];
        xj1 = x[j1];
        x[i1] = xj1;
        x[j1] = xi1;

        i3 = i1 + halfn;
        j3 = j1 + 1;

        xi3 = x[i3];
        xj3 = x[j3];

        if (t)
        {
            x[i3] = xj3;
            x[j3] = xi3;
        }
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_bitrev_cplx_cn.c                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
