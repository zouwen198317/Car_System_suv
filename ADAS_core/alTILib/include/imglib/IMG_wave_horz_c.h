/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB-2  DSP Image/Video Processing Library                            */
/*                                                                          */
/*      Release:        Revision 2.0.1                                      */
/*      Snapshot date:  6-May-2008                                          */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
/*============================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                                */
/*                                                                            */
/*     NAME                                                                   */
/*           wave_horz                                                        */
/*                                                                            */
/*                                                                            */
/*     USAGE                                                                  */
/*           This routine is C-callable and can be called as:                 */
/*                                                                            */
/*          void wave_horz_cn(short *iptr, short *qmf, short *filter,         */
/*                                          short * optr, int  ish_x_dim ) ;  */
/*                                                                            */
/*            iptr =  input row of data                                       */
/*            qmf =  qmf filter-bank for Low-Pass                             */
/*            filter =  Mirror qmf filter bank for High_pass                  */
/*            optr = output row of detailed/reference decimated outputs       */
/*            ish_x_dim = width of the input row                              */
/*                                                                            */
/*           (See the C compiler reference guide.)                            */
/*                                                                            */
/*     DESCRIPTION                                                            */
/*            This kernel performs a 1D Periodic Orthogonal Wavelet decomp-   */
/*     osition. This also performs athe row decomposition in a 2D wavelet     */
/*     transform. An in put signal x[n] is first low pass and high pass       */
/*     filterd and decimated by two. This results in a reference signal       */
/*     r1[n] which is the decimated output obtained by dropping the odd       */
/*     samples of the low pass filtered output and a detail signal d[n]       */
/*     obtained by dropping the odd samples of the high-pass output. A        */
/*     circular convolution algorithm is implemented and hence the wave-      */
/*     let transform is periodic. The reference signal and the detail         */
/*     signal are half the size of the original signal. The reference         */
/*     signal may then be iterated again to perform another scale of          */
/*     multi-resolution analysis.                                             */
/*                                                                            */
/*     ASSUMPTIONS                                                            */
/*        any assumptions                                                     */
/*                                                                            */
/*     BIBLIOGRAPHY                                                           */
/*        A Wavelet Tour of Signal Processing Stephane' Mallat. Academic      */
/*        Press                                                               */
/*                                                                            */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
void IMG_wave_horz_cn
(
    const short *restrict in_data,  /* Row of input pixels  */
    const short *restrict qmf,      /* Low-pass QMF filter  */
    const short *restrict mqmf,     /* High-pass QMF filter */
    short       *restrict out_data, /* Row of output data   */
    int                   cols      /* Length of input.     */
);
/* ======================================================================== */
/*  End of file:  IMG_wave_horz_c.h                                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
