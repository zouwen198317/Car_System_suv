
/* ######################################################################## */
/* #  TI Disclaimer: This kernel is obsolete. It is provided here for     # */
/* #  backward compatibility.                                             # */
/* ######################################################################## */

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
/*  NAME                                                                    */
/*      IMG_mad_8x8 -- Minimum Absolute Difference motion search            */
/*                                                                          */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable and has the following C prototype.       */
/*                                                                          */
/*      void IMG_mad_8x8                                                    */
/*      (                                                                   */
/*          const unsigned char *refImg,    // Ref. image to search //      */
/*          const unsigned char *srcImg,    // Source 8x8 block     //      */
/*          int                 pitch,      // Width of ref image   //      */
/*          int sx, int sy,                 // Search window size   //      */
/*          unsigned int        *motvec     // Motion vector result //      */
/*      );                                                                  */
/*                                                                          */
/*      This routine accepts an 8x8 source block and a pointer to           */
/*      a window to search within a bitmap.  The pointer "refImg"           */
/*      points to the upper left corner of the search window.  The          */
/*      parameters "sx" and "sy" describe the dimensions of the search      */
/*      area.  The bitmap itself may be wider than the search window.       */
/*      It's width is described by the "pitch" argument.                    */
/*                                                                          */
/*      The search area dimensions specify the range of positions that      */
/*      the 8x8 source block is compared to.  This means that the           */
/*      actual bitmap area examined extends 7 pixels beyond the right       */
/*      and bottom edges of the search area within the reference image.     */
/*                                                                          */
/*      The best match position and its absolute difference are returned    */
/*      in motvec, packed as follows:                                       */
/*                                                                          */
/*                     31             16 15             0                   */
/*                     +----------------+----------------+                  */
/*          motvec[0]: |    X offset    |    Y offset    |                  */
/*                     +----------------+----------------+                  */
/*                                                                          */
/*                     31                               0                   */
/*                     +---------------------------------+                  */
/*          motvec[1]: |   Sum of absolute differences   |                  */
/*                     +---------------------------------+                  */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The IMG_mad_8x8 function performs a full search for an 8x8 block    */
/*      within a specified search window.  It finds the position within     */
/*      the search window that has the Minimum Absolute Difference with     */
/*      respect to the given source block.                                  */
/*                                                                          */
/*      This type of search is useful for video algorithms which use        */
/*      motion compensation.  The search performed by this routine is a     */
/*      full search, meaning that all possible starting positions from      */
/*      [0, 0] to [sx-1, sy-1] are checked for potential matches.           */
/*                                                                          */
/*      The Absolute Difference metric is calculated by summing the         */
/*      absolute values of the differences between pixels in the            */
/*      source block and their corresponding pixels for the match           */
/*      point being evaluated in the reference image.  Smaller sums         */
/*      denote better matches--that is, less overall difference between     */
/*      the source block and match point in the reference block.            */
/*                                                                          */
/*      The algorithm returns the X and Y offsets of the best match         */
/*      point, as well as the calculated Absolute Difference for that       */
/*      position.  If two match points have equal Absolute Differences,     */
/*      the earlier block in the search sequence is returned.  The          */
/*      search presently checks in vertical stripes from top to bottom,     */
/*      moving from 1 column to the right after each stripe.                */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      The input pointers do not alias the output pointer for motvec.      */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef MAD_8X8_C_H_
#define MAD_8X8_C_H_ 1

void IMG_mad_8x8_cn
(
    const unsigned char *restrict refImg,
    const unsigned char *restrict srcImg,
    int pitch, int sx, int sy,
    unsigned int *restrict motvec
);

#endif
/* ======================================================================== */
/*  End of file:  IMG_mad_8x8_c.h                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
