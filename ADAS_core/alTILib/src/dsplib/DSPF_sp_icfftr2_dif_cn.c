/* ======================================================================= */
/* DSPF_sp_icfftr2_dif_cn.c -- Inverse FFT with Radix 2 and DIF            */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_icfftr2_dif_cn, ".text:natural");
#endif

#include "DSPF_sp_icfftr2_dif_cn.h"

void DSPF_sp_icfftr2_dif_cn(float* x, float* w, unsigned short n)
{
    unsigned short n2, ie, ia, i, j, k, m;
    float rtemp, itemp, c, s;

    n2 = 1;
    ie = n;

    for(k=n; k > 1; k >>= 1)
    {
        ie >>= 1;
        ia = 0;

        for(j=0; j < ie; j++)
        {
            c = w[2*j];
            s = w[2*j+1];

            for(i=0; i < n2; i++)
            {
                m = ia + n2;
                rtemp = x[2*ia] - x[2*m];
                x[2*ia] = x[2*ia] + x[2*m];
                itemp = x[2*ia+1] - x[2*m+1];
                x[2*ia+1] = x[2*ia+1] + x[2*m+1];
                x[2*m] = c*rtemp - s*itemp;
                x[2*m+1] = c*itemp + s*rtemp;
                ia++;
            }

            ia += n2;
        }

        n2 <<= 1;
    }
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_icfftr2_dif_cn.c                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
