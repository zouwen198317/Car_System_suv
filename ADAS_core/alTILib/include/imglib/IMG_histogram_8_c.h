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
/*                                                                            */
/* histogram -  This file contains the golden C model code.                   */
/*                                                                            */
/*============================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                                */
/*                                                                            */
/*     NAME                                                                   */
/*           histogram                                                        */
/*                                                                            */
/*     REVISION HISTORY                                                       */
/*        Date ...Original version obtained .........................D.Hoyle  */
/*        Date ...Last modified Neatened Code .......................D.Hoyle  */
/*                                                                            */
/*     USAGE                                                                  */
/*        This routine is C-callable and can be called as:                    */
/*                                                                            */
/*        void histogram_cn(unsigned char * image, int  n, int  accumulate,   */
/*                          unsigned short * t_hist, unsigned short * hist)   */
/*                                                                            */
/*            image      =  input image data                                  */
/*            n          =  number of points                                  */
/*            accumulate =  defines addition/subtract from existing           */
/*                          histogram: 1, -1                                  */
/*            t_hist     =  temporary histogram bins (1024)                   */
/*            hist       =  running histogram bins (256)                      */
/*                                                                            */
/*           (See the C compiler reference guide.)                            */
/*                                                                            */
/*     DESCRIPTION                                                            */
/*        This code takes a histogram of an array of n, 8 bit inputs. It      */
/*        returns the histogram of 256 bins at 16 bit precision. It can       */
/*        either add or subtract to an existing histogram, using the          */
/*        'accumulate' control. I requires some temporary storage for 4       */
/*        temporary histograms, which are later summed together.              */
/*        void histogram_cn(unsigned char * image, int n, int accumulate,     */
/*                          unsigned short * t_hist, unsigned short * hist)   */
/*        {                                                                   */
/*            int pixel, j;                                                   */
/*            for (j = 0; j < n; j++)                                         */
/*            {                                                               */
/*                pixel = (int) image[j];                                     */
/*                hist[pixel] += accumulate;                                  */
/*            }                                                               */
/*        }                                                                   */
/*     ASSUMPTIONS                                                            */
/*        It is assumed that the array of data, t_hist is initialised         */
/*        to zero. The input array of image data must be aligned to an 8      */
/*        byte boundary and n must be a multiple of 8. The maximum number of  */
/*        pixels that can be profiled in each bin is 65535 in the main        */
/*        histogram and the maximum n is 262143.                              */
/*                                                                            */
/*     BIBLIOGRAPHY                                                           */
/*        Internal TI-IP, logbook reference.                                  */
/*                                                                            */
/*============================================================================*/
/*      Copyright (C) 1997-1999 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/

void IMG_histogram_8_cn
(
    const unsigned char *restrict image,
    int   n, 
    short accumulate,
    short *restrict t_hist,
    short *restrict hist
);

/*============================================================================*/
/*      Copyright (C) 1997-1999 Texas Instruments Incorporated.               */
/*                      All Rights Reserved                                   */
/*============================================================================*/
