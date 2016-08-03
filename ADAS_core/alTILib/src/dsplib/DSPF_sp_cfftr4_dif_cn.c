/* ======================================================================= */
/* DSPF_sp_cfftr4_dif_cn.c -- Forward FFT with Radix 4 and DIF             */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_cfftr4_dif_cn, ".text:natural");
#endif

#include "DSPF_sp_cfftr4_dif_cn.h"

void DSPF_sp_cfftr4_dif_cn(float* x, float* w, unsigned short n)
{
    unsigned short n1, n2, ie, ia1, ia2, ia3, i0,
        i1, i2, i3, j, k;
    float r1, r2, r3, r4, s1, s2, s3, s4,
        co1, co2, co3, si1,    si2, si3;

    n2 = n;
    ie = 1;

    for(k=n; k>1; k>>=2)
    {
        n1 = n2;
        n2 >>= 2;
        ia1 = 0;

        for(j=0; j<n2; j++)
        {
            ia2 = ia1 + ia1;
            ia3 = ia1 + ia2;
            co1 = w[ia1*2];
            si1 = w[ia1*2 + 1];
            co2 = w[ia2*2];
            si2 = w[ia2*2 + 1];
            co3 = w[ia3*2];
            si3 = w[ia3*2 + 1];
            ia1 += ie;

            for(i0=j; i0<n; i0+=n1)
            {
                i1 = i0 + n2;
                i2 = i1 + n2;
                i3 = i2 + n2;

                r1 = x[i0*2] + x[i2*2];
                r3 = x[i0*2] - x[i2*2];
                s1 = x[i0*2+1] + x[i2*2+1];
                s3 = x[i0*2+1] - x[i2*2+1];
                r2 = x[i1*2] + x[i3*2];
                r4 = x[i1*2] - x[i3*2];
                s2 = x[i1*2+1] + x[i3*2+1];
                s4 = x[i1*2+1] - x[i3*2+1];
                x[i0*2] = r1 + r2;

                r2 = r1 - r2;
                r1 = r3 - s4;
                r3 = r3 + s4;
                x[i0*2+1] = s1 + s2;

                s2 = s1 - s2;
                s1 = s3 + r4;
                s3 = s3 - r4;
                x[i1*2] = co1*r3 + si1*s3;
                x[i1*2+1] = co1*s3 - si1*r3;
                x[i2*2] = co2*r2 + si2*s2;
                x[i2*2+1] = co2*s2 - si2*r2;
                x[i3*2] = co3*r1 + si3*s1;
                x[i3*2+1] = co3*s1 - si3*r1;
            }
        }

        ie <<= 2;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_cfftr4_dif_cn.c                                  */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
