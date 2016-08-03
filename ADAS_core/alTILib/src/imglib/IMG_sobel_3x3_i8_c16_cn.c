/* ======================================================================== *
 * IMGLIB -- TI Image and Video Processing Library                          *
 *                                                                          *
 *                                                                          *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/   *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

/* ======================================================================== */
/*  NAME                                                                    */
/*      IMG_sobel_3x3_8_cn                                                  */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_sobel_3x3_8_cn                                             */
/*      (                                                                   */
/*          const unsigned char *in_data,      // Input image data  //      */
/*          unsigned char       *out_data,     // Output image data //      */ 
/*          short cols, short rows             // Image dimensions  //      */ 
/*      )                                                                   */
/*                                                                          */
/*      The sobel filter is applied to the input image.  The input image    */ 
/*      dimensions are given by the arguments 'cols' and 'rows'.  The       */
/*      output image is 'cols' pixels wide and 'rows - 2' pixels tall.      */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      To see how the implementation is going to work on the input         */
/*      buffer, lets imagine we have the following input buffer:            */  
/*      lets imagine we have the following input buffer:                    */
/*                                                                          */
/*              yyyyyyyyyyyyyyyy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yxxxxxxxxxxxxxxy                                            */
/*              yyyyyyyyyyyyyyyy                                            */
/*                                                                          */
/*      The output buffer would be:                                         */
/*                                                                          */
/*              tXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXz                                            */
/*              zXXXXXXXXXXXXXXt                                            */  
/*                                                                          */
/*      Where:                                                              */
/*                                                                          */
/*          X = sobel(x)    The algorithm is applied to that pixel.         */
/*                          The correct output is obtained, the data        */ 
/*                          around the pixels we work on is used            */
/*                                                                          */
/*          t               Whatever was in the output buffer in that       */
/*                          position is kept there.                         */
/*                                                                          */
/*          z = sobel(y)    The algorithm is applied to that pixel.         */
/*                          The output is not meaningful, because the       */
/*                          necessary data to process the pixel is not      */
/*                          available.  This is because for each output     */
/*                          pixel we need input pixels from the right and   */
/*                          from the left of the output pixel.  But this    */ 
/*                          data doesn't exist.                             */
/*                                                                          */
/*      This means that we will only process (rows-2) lines.  Then, we      */
/*      will process all the pixels inside each line. Even though the       */
/*      results for the first and last pixels in each line will not         */
/*      be relevant, it makes the control much simpler and ends up          */
/*      saving cycles.                                                      */
/*                                                                          */ 
/*      Also the fist pixel in the first processed line and the             */ 
/*      last pixel in the last processed line will not be computed.         */ 
/*      It is not necessary, since the results would be bogus, and          */ 
/*      not computing them saves some time.                                 */ 
/*                                                                          */
/*      The following horizontal and vertical masks that are                */
/*      applied to the input buffer to obtain one output pixel.             */
/*                                                                          */
/*          Horizontal:                                                     */
/*              -1 -2 -1                                                    */
/*               0  0  0                                                    */
/*               1  2  1                                                    */
/*                                                                          */
/*          Vertical:                                                       */
/*              -1  0  1                                                    */
/*              -2  0  2                                                    */
/*              -1  0  1                                                    */
/*                                                                          */
/*  NOTES                                                                   */
/*      The values of the left-most and right-most pixels on each line      */
/*      of the output are not well-defined.                                 */
/* ======================================================================== */

#include "IMGLib.h"

#include <math.h>

#ifdef WIN32
#include "VisionMeIntrinsic.h"
#include <assert.h>
#endif

#ifndef WIN32
#pragma CODE_SECTION(IMG_sobel_3x3_i8_c16_cn,   ".text:ansi");
#endif

void IMG_sobel_3x3_i8_c16_cn
(
    const unsigned char *restrict in,   /* Input image data   */
    short               *restrict out,  /* Output image data  */
    short                         cols, /* image columns      */
    short                         rows  /* Image rows         */
)
{    
  int H, O, V, i;
  int i00, i01, i02;
  int i10,      i12;
  int i20, i21, i22;
  int w = cols;

#ifndef NOASSUME
  _nassert(cols > 3);
  _nassert(cols % 2 == 0);
  _nassert(rows > 3);
  _nassert(cols * (rows - 2) - 2 >= 8);
#endif

  /* -------------------------------------------------------------------- */
  /*  Iterate over entire image as a single, continuous raster line.      */
  /* -------------------------------------------------------------------- */
#ifndef NOASSUME
#ifndef WIN32
  #pragma MUST_ITERATE(8,,2);
#endif
#endif
  for (i=0; i<cols*(rows-2)-2; i++) {
    /* ---------------------------------------------------------------- */
    /*  Read in the required 3x3 region from the input.                 */
    /* ---------------------------------------------------------------- */
    i00=in[i    ]; i01=in[i    +1]; i02=in[i    +2];
    i10=in[i+  w];                  i12=in[i+  w+2];
    i20=in[i+2*w]; i21=in[i+2*w+1]; i22=in[i+2*w+2];

    /* ---------------------------------------------------------------- */
    /*  Apply horizontal and vertical filter masks.  The final filter   */
    /*  output is the sum of the absolute values of these filters.      */
    /* ---------------------------------------------------------------- */
    H = -   i00 - 2*i01 -   i02 +
        +   i20 + 2*i21 +   i22;

    V = -   i00         +   i02 
        - 2*i10         + 2*i12 
        -   i20         +   i22;    

    O = abs(H) + abs(V);
    /* ---------------------------------------------------------------- */
    /*  Store it.                                                       */
    /* ---------------------------------------------------------------- */
    out[i] = O;
  }
}

/* ======================================================================== */
/*  End of file:  IMG_sobel_3x3_8_cn.c                                      */
/* ======================================================================== */
