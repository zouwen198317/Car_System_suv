/* ======================================================================= */
/* DSPF_sp_lms_cn.c -- LMS Adaptive Filter                                 */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
#ifndef WIN32
#pragma CODE_SECTION(DSPF_sp_lms_cn, ".text:ansi");
#endif

#include "DSPF_sp_lms_cn.h"

float DSPF_sp_lms_cn(const float *x, float *h, const float *y_i,
    float *y_o, const float ar, float error, const int nh, const int ny)
{
    int i, j;
    float sum;

    for (i = 0; i < ny; i++)
    {
        for (j = 0; j < nh; j++)
            h[j] = h[j] + (ar * error * x[i + j - 1]);
        
        sum = 0.0f;

        for (j = 0; j < nh; j++)
            sum += h[j] * x[i + j];
        
        y_o[i] = sum;
        error = y_i[i] - sum;
    }

    return error;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_lms_cn.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

