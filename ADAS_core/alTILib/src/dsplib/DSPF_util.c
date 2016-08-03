/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSPF_util -- General purpose utility module for C674x DSPLIB        */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include "DSPF_util.h"

// local macros
#define UTIL_start        (i < 4)
#define UTIL_middle       (i >= (N >> 1) - 2 && i < (N >> 1) + 2)
#define UTIL_end          (i >= N - 4)

// local functions
static void LOCAL_printTableHeader();
static void LOCAL_printTableFooter();
static void LOCAL_reportStrict(int diff);

void UTIL_fillRandSP(float *ptr_x, int N, float factor)
{
    float rand_midpoint = RAND_MAX / 2.0;
    int i;

    // fill array with floats in the range (-factor, factor)
    for (i = 0; i < N; i++)
        ptr_x[i] = ((rand() - rand_midpoint) / rand_midpoint) * factor;
}

void UTIL_fillRandUint(void *ptr_x, int N)
{
    unsigned short *ptr_xs = ptr_x;
    int i;

    // fill array with 32-bit uints, 16 bits at a time (assumes RAND_MAX = 0x7FFF)
    for (i = 0; i < 2 * N; i++)
    {
        // one rand() call only generates 15 bits; two calls are required
        ptr_xs[i] = ( (unsigned short)(rand() & 0x00007FFF) << 1 ) +
            (unsigned short)(rand() & 0x01);
    }
}

void UTIL_fillRandFilterSP(float *ptr_h, int N)
{
    float frand_max = RAND_MAX, pair_sum = 2.0f / N;
    int i;

    // create a moving average filter of length N
    // filter taps must be non-negative and sum to 1
    // N must be an even number
    for (i = 0; i < N / 2; i++)
    {
        ptr_h[i] = (rand() / frand_max) * pair_sum;
        ptr_h[N - 1 - i] = pair_sum - ptr_h[i];
    }
}

void UTIL_compareResultsSP(float *ptr_y_cn, float *ptr_y_lib, float *ptr_y_ex, int N, int strict, int verbose)
{
    float pct_diff, max_pct_diff = 0;
    int strict_diff = 0, ellipses = 1, i;

    // verbose mode: print table header
    if (verbose) LOCAL_printTableHeader();

    for (i = 0; i < N; i++)
    {
        // compare words strictly
        if (ptr_y_cn[i] != ptr_y_lib[i])
            strict_diff = 1;

        // compute percent difference and track max difference
        pct_diff = (ptr_y_cn[i] - ptr_y_lib[i]) / ptr_y_cn[i] * 100.0f;
        if (pct_diff < 0) pct_diff *= -1;
        if (pct_diff > max_pct_diff) max_pct_diff = pct_diff;

        // verbose mode: print data table with words from start, middle, and end of array
        if (verbose)
            if (UTIL_start || UTIL_middle || UTIL_end)
            {
                printf("%5u  % 15.4f  % 15.4f", i, ptr_y_cn[i], ptr_y_lib[i]);
                if (ptr_y_ex != 0)
                    printf("  % 15.4f\n", ptr_y_ex[i]);
                else
                    printf("               --\n");
                ellipses = 1;
            }
            else if (ellipses)
            {
                printf("  ...              ...              ...              ...\n");
                ellipses = 0;
            }
    }

    // verbose mode: print table footer
    if (verbose) LOCAL_printTableFooter();

    // report strict result
    if (strict) LOCAL_reportStrict(strict_diff);

    // report max percent difference
    printf("\nMax Difference:\t(%.3e)%%\n", max_pct_diff);
}

void UTIL_compareResultsUint(unsigned int *ptr_y_cn, unsigned int *ptr_y_lib,
    unsigned int *ptr_y_ex, int N, int strict, int verbose)
{
    unsigned int abs_diff, max_abs_diff = 0;
    int strict_diff = 0, ellipses = 1, i;

    // verbose mode: print table header
    if (verbose) LOCAL_printTableHeader();

    for (i = 0; i < N; i++)
    {
        // compare words strictly
        if (ptr_y_cn[i] != ptr_y_lib[i])
            strict_diff = 1;

        // compute absolute difference and track max difference
        abs_diff = (ptr_y_cn[i] > ptr_y_lib[i]) ? 
            ptr_y_cn[i] - ptr_y_lib[i] :
            ptr_y_lib[i] - ptr_y_cn[i];
        if (abs_diff > max_abs_diff) max_abs_diff = abs_diff;

        // verbose mode: print data table with words from start, middle, and end of array
        if (verbose)
            if (UTIL_start || UTIL_middle || UTIL_end)
            {
                printf("%5u       0x%08X       0x%08X", i, ptr_y_cn[i], ptr_y_lib[i]);
                if (ptr_y_ex != 0)
                    printf("       0x%08X\n", ptr_y_ex[i]);
                else
                    printf("               --\n");
                ellipses = 1;
            }
            else if (ellipses)
            {
                printf("  ...              ...              ...              ...\n");
                ellipses = 0;
            }
    }

    // verbose mode: print table footer
    if (verbose) LOCAL_printTableFooter();

    // report strict result
    if (strict) LOCAL_reportStrict(strict_diff);

    // report max absolute difference
    printf("\nMax Difference:\t0x%02X\n", max_abs_diff);
}

static void LOCAL_printTableHeader()
{
    printf("\n---------------------------------------------------------\n");
    printf("    i          y_cn[i]         y_lib[i]          y_ex[i]\n");
    printf("---------------------------------------------------------\n");
}

static void LOCAL_printTableFooter()
{
    printf("---------------------------------------------------------\n");
}

static void LOCAL_reportStrict(int diff)
{
    if (diff)
        printf("\nResult:\t\tFAIL\n");
    else
        printf("\nResult:\t\tPASS\n");
}

/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
