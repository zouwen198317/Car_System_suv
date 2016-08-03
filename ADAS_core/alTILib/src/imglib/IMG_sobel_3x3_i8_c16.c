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
/*      IMG_sobel_3x3_8                                                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*      void IMG_sobel_3x3_8                                                */
/*      (                                                                   */
/*          const unsigned char *in,      // Input image data  //           */
/*          unsigned char       *out,     // Output image data //           */ 
/*          short               cols,     // Image cols        //           */ 
/*          short               rows      // Image rows        //           */ 
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
/*      Also the first pixel in the first processed line and the            */ 
/*      last pixel in the last processed line will not be computed.         */ 
/*      It is not necessary, since the results would be bogus.              */
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
/*  ASSUMPTIONS                                                             */
/*      (rows * cols) must be a multiple of 8                               */
/*      The input image width must be even (eg. 'cols' must be even).       */
/*                                                                          */
/*  NOTES                                                                   */
/*      The values of the left-most and right-most pixels on each line      */
/*      of the output are not well-defined.                                 */
/* ======================================================================== */

#pragma CODE_SECTION(IMG_sobel_3x3_i8_c16,   ".text:optimized");

#include <c6x.h>

void IMG_sobel_3x3_i8_c16
(
    const unsigned char *restrict in,   /* Input image data   */
    short               *restrict out,  /* Output image data  */
    short                         cols, /* Image dimensions   */
    short                         rows  /* Image dimensions   */
)
{    
  int i,t9,t10,t11,t12,end,final_pass;
  int w = cols;
  int mult1   = 0x00fffeff;
  int mult2   = 0x00010201;
  int mult1_b = 0xfffeff00;
  int mult2_b = 0x01020100;

  _nassert(cols > 3);
  _nassert(cols % 2 == 0);
  _nassert(rows > 3);
  _nassert(cols * (rows - 2) - 2 >= 8);

  /* -------------------------------------------------------------------- */
  /*  Iterate over entire image as a single, continuous raster line.      */
  /* -------------------------------------------------------------------- */
  
  end        = (cols*(rows-2) - 2);
  final_pass = end - 6;

  for (i=0; i<end; i+=8) {
    double in1_d,in1_d2,in2_d1,in2_d2,in3_d,in3_d2;
    unsigned int in1_l,in1_h,in2_l,in2_h,in3_l,in3_h;
    unsigned int in2_l2,in2_h2;
    unsigned int tmp1,tmp3,tmp2,tmp4;
    unsigned int t1,t2,t3,t4,t5,t6,t7,t8;
    int H, H3, H5, H7;
    unsigned int b1,b2,b3,b4,b5,b6,b7,b8;
    double b10,b11,b12,b13,b14,b15;
    
    /* ---------------------------------------------------------------- */
    /*  Read in the required 3x3 region from the input.                 */
    /* ---------------------------------------------------------------- */
    in1_d   = _memd8_const((void*)&in[i]);
    in1_d2  = _memd8_const((void*)&in[i+2]);
    tmp1    = _lo(in1_d2);
    tmp2    = _hi(in1_d2);
    in1_l   = _lo(in1_d);
    in1_h   = _hi(in1_d);

    in2_d1  = _memd8_const((void*)&in[i+w]);
    in2_d2  = _memd8_const((void*)&in[i+w+2]);
    in2_l   = _lo(in2_d1);
    in2_l2  = _hi(in2_d1);
    in2_h   = _lo(in2_d2);
    in2_h2  = _hi(in2_d2);

    in3_d   = _memd8_const((void*)&in[i+2*w]);
    in3_d2  = _memd8_const((void*)&in[i+2*w+2]);
    tmp3    = _lo(in3_d2);
    tmp4    = _hi(in3_d2);
    in3_l   = _lo(in3_d);
    in3_h   = _hi(in3_d);

    /* ---------------------------------------------------------------- */
    /*  Apply horizontal and vertical filter masks.  The final filter   */
    /*  output is the sum of the absolute values of these filters.      */
    /* ---------------------------------------------------------------- */
    // i00=in[i    ]; i01=in[i    +1]; i02=in[i    +2];
    // i10=in[i+  w];                  i12=in[i+  w+2];
    // i20=in[i+2*w]; i21=in[i+2*w+1]; i22=in[i+2*w+2];
    // H = -i00 - 2*i01 -   i02 +   i20 + 2*i21 + i22;
    // V = -i00 +   i02 - 2*i10 + 2*i12 -   i20 + i22;    

    /* t1, t3, t5, t7 are the horizontal guys, two shorts per word */
    H    = _add2(_pack2(_dotpsu4(mult1_b,in1_l),_dotpsu4(mult1,in1_l)),
                 _pack2(_dotpsu4(mult2_b,in3_l),_dotpsu4(mult2,in3_l)));
    H3   = _add2(_pack2(_dotpsu4(mult1_b,tmp1), _dotpsu4(mult1,tmp1)), 
                 _pack2(_dotpsu4(mult2_b,tmp3), _dotpsu4(mult2,tmp3)));
    H5   = _add2(_pack2(_dotpsu4(mult1_b,in1_h),_dotpsu4(mult1,in1_h)),
                 _pack2(_dotpsu4(mult2_b,in3_h),_dotpsu4(mult2,in3_h)));
    H7   = _add2(_pack2(_dotpsu4(mult1_b,tmp2), _dotpsu4(mult1,tmp2)),
                 _pack2(_dotpsu4(mult2_b,tmp4), _dotpsu4(mult2,tmp4)));

    t1 = _abs2(H);
    t3 = _abs2(H3);
    t5 = _abs2(H5);
    t7 = _abs2(H7);

    /* t2, t4, t6, t8 are the vertical guys, two shorts per word */
    b10= _mpyu4(in2_l2,0x2020202);
    b11= _mpyu4(in1_h, 0x1010101);
    b12= _mpyu4(in2_l, 0x2020202);
    b13= _mpyu4(in2_h, 0x2020202);
    b14= _mpyu4(in2_h2,0x2020202);
    b15= _mpyu4(tmp2,  0x1010101);

    b1 = _add2(_add2(_unpklu4(in1_l),_lo(b12)),_unpklu4(in3_l));
    b2 = _add2(_add2(_unpkhu4(in1_l),_hi(b12)),_unpkhu4(in3_l));
    b3 = _add2(_add2(_unpklu4(tmp1), _lo(b13)),_unpklu4(tmp3));
    b4 = _add2(_add2(_unpkhu4(tmp1), _hi(b13)),_unpkhu4(tmp3));
    b5 = _add2(_add2(_lo(b11),_lo(b10)),_unpklu4(in3_h));
    b6 = _add2(_add2(_hi(b11),_hi(b10)),_unpkhu4(in3_h));
    b7 = _add2(_add2(_lo(b15),_lo(b14)),_unpklu4(tmp4));
    b8 = _add2(_add2(_hi(b15),_hi(b14)),_unpkhu4(tmp4));

    t2 = _abs2(_sub2(b2,b1));
    t4 = _abs2(_sub2(b4,b3));
    t6 = _abs2(_sub2(b6,b5));
    t8 = _abs2(_sub2(b8,b7));
    
    t9 = _add2(t1,t2);
    t10= _add2(t3,t4);
    t11= _add2(t5,t6);
    t12= _add2(t7,t8);

    /* the last 6 outputs must be stored separately */
    if (i != final_pass) {
      _mem8((void *)&out[i]) = _itoll(t10, t9);
      _mem8((void *)&out[i+4]) = _itoll(t12, t11);
    }
  }
  
  /* clean up the last 6 "output" guys */
  _mem8((void *)&out[i-8]) = _itoll(t10, t9);
  out[i-4] = _itoll(t12,t11) & 0xffff;
  out[i-3] = (_itoll(t12,t11)>>16)&0xffff;
}

/* ======================================================================== */
/*  End of file:  IMG_sobel_3x3_8.c                                         */
/* ======================================================================== */
