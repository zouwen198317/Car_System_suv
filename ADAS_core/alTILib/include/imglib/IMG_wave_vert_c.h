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
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      wave_vert                                                           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void wave_vert_cn                                               */
/*          (                                                               */
/*              const short *restrict                                       */
/*                    const *restrict in_data,                              */
/*              const short *restrict lp_filt,                              */
/*              const short *restrict hp_filt,                              */
/*              short       *restrict out_ldata,                            */
/*              short       *restrict out_hdata,                            */
/*              int cols                                                    */
/*          )                                                               */
/*                                                                          */
/*          in_data   = Eight pointers to input image rows.                 */
/*          lp_filt   = Low-pass quadrature mirror filter coeffs (8 taps)   */
/*          hp_filt   = High-pass quadrature mirror filter coeffs (8 taps)  */
/*          out_ldata = Outgoing low-pass image data.                       */
/*          out_hdata = Outgoing high-pass image data.                      */
/*          cols      = Total number of colums in row of image.             */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function performs the vertical pass of 2D wavelet              */
/*      transform It performs a vertical filter on 8 rows which are         */
/*      pointed to by the pointers contained in an array of pointers.       */
/*      It produces two lines worth of output, one being the low-pass       */
/*      and the other being the high pass result.  Instead of               */
/*      transposing the input image and re-using the horizontal wavelet     */
/*      function, the vertical filter is applied directly to the image      */
/*      data as-is, producing a single line of high pass and a single       */
/*      line of low pass outputs.                                           */
/*                                                                          */
/*      This function accepts eight row pointers for the eight rows         */
/*      that form the context for the two filters.  It also accepts         */
/*      two output pointers, one for the high-pass filtered output          */
/*      and one for the low-pass filtered output.  Finally, it also         */
/*      accepts two input pointers for the low- and high-pass filters.      */
/*                                                                          */
/*      In a traditional wavelet implementation, for a given pair of        */
/*      output lines, the input context for the low-pass filter is          */
/*      offset by a number of lines from the input context for the          */
/*      high-pass filter.  The amount of offset is determined by the        */
/*      number of filter taps and is generally "num_taps - 2" rows.         */
/*      This implementation is fixed at 8 taps, so the offset would be      */
/*      6 rows.                                                             */
/*                                                                          */
/*      This implementation breaks from the traditional model so that       */
/*      it can reuse the same input context for both low-pass and           */
/*      high-pass filters simultaneously.  The result is that the           */
/*      low-pass and high-pass *outputs* must instead be offset by the      */
/*      calling function.  The following sample pseudo-code illustrates     */
/*      one possible method for producing the desired result.               */
/*                                                                          */
/*          // ------------------------------------------------------ //    */
/*          //  Iterate over whole input image, starting at the top.  //    */
/*          // ------------------------------------------------------ //    */
/*          for (y = 0; y < y_dim; y += 2)                                  */
/*          {                                                               */
/*              // -------------------------------------------------- //    */
/*              //  Set up our eight input pointers, wrapping around  //    */
/*              //  the bottom as necessary.                          //    */
/*              // -------------------------------------------------- //    */
/*              for (y0 = 0; y0 < 8; y0++)                                  */
/*                  in_data[y0] = in_image + ((y + y0) % y_dim) * x_dim;    */
/*                                                                          */
/*              // -------------------------------------------------- //    */
/*              //  Set up our output pointers.  The high-pass data   //    */
/*              //  is three rows ahead of the low-pass data.         //    */
/*              // -------------------------------------------------- //    */
/*              out_ldata = out_image + (y / 2);                            */
/*              out_hdata = out_image + ((y + 6) % y_dim) / 2 + y_dim;      */
/*                                                                          */
/*              // -------------------------------------------------- //    */
/*              //  Perform the wavelet.                              //    */
/*              // -------------------------------------------------- //    */
/*              wave_vert(in_data, lpf, hpf, out_ldata, out_hdata, x_dim);  */
/*          }                                                               */
/*                                                                          */
/*  BIBLIOGRAPHY                                                            */
/*      A Wavelet Tour of Signal Processing Stephane Mallat                 */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef _WAVE_VERT_C_H
#define _WAVE_VERT_C_H 1

void IMG_wave_vert_cn
(
    const short *restrict
    const       *restrict in_data,   /* Array of row pointers */
    const short *restrict lp_filt,   /* Low pass QMF filter   */
    const short *restrict hp_filt,   /* High pass QMF filter  */
    short       *restrict out_ldata, /* Low pass output data  */
    short       *restrict out_hdata, /* High pass output data */
    int cols                     /* Length of rows to process */
);

#endif
/* ======================================================================== */
/*  End of file:  IMG_wave_vert_c.h                                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
