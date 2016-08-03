
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
/*      IMG_idct_8x8_12q4 -- IEEE-1180/1990 Compliant IDCT, Little Endian.  */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C callable, and has the following C prototype:      */
/*                                                                          */
/*          void IMG_idct_8x8_12q4(short idct_data[], unsigned num_idcts)   */
/*                                                                          */
/*      The IMG_idct_8x8_12q4 routine accepts a list of 8x8 DCT coeffient   */
/*      blocks and performs IDCTs on each.  The array should be laid out    */
/*      equivalently to the C array idct_data[num_idcts][8][8].  The        */
/*      input data should be in 12Q4 format.                                */
/*                                                                          */
/*      The routine operates entirely in-place, requiring no additional     */
/*      storage for intermediate results.                                   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      The idct_8x8 algorithm performs an IEEE-1180 compliant IDCT,        */
/*      complete with rounding and saturation to signed 9-bit quantities.   */
/*      The input coefficients are assumed to be signed 16-bit DCT          */
/*      coefficients in 12Q4 format.                                        */
/*                                                                          */
/*      Note:  This code guarantees correct operation, even in the case     */
/*      that 'num_idcts == 0'.                                              */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      This is a LITTLE ENDIAN implementation.                             */
/*                                                                          */
/*  NOTES                                                                   */
/*      The cosine terms have all been scaled by sqrt(2), so that the       */
/*      "c4" term is basically an even power of 2.                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#ifndef IDCT_8X8_12Q4_C_H_
#define IDCT_8X8_12Q4_C_H_ 1

void IMG_idct_8x8_12q4_cn(short *idct_data, unsigned num_idcts);

#endif
/* ======================================================================== */
/*  End of file:  IMG_idct_8x8_12q4_c.h                                     */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
