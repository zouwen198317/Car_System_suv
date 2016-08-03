
#include "IMGLib.h"

#ifdef WIN32
#include "VisionMeIntrinsic.h"
#endif

#if 0
void IMG_conv_3x3_i8_c16s_altek_cn
(
    const unsigned char *restrict  imgin_ptr,
    short               *restrict imgout_ptr,
    short                              width,
    short                              pitch,
    const char          *restrict   mask_ptr,
    short                              shift
)
{
  int     i,      j,      k;
  int     sum;

  /* Point to the end of the mask to account for rotation */
  const char *mask_rot = &mask_ptr[3*3 - 1];

  for (i=0; i<width; i++) {
    sum = 0;

    for (j=0; j<3; j++) {
      for (k=0; k<3; k++) {
        sum += imgin_ptr[j * pitch + i + k] * mask_rot[-(j * 3 + k)];
      }
    }

    sum           = sum >> shift;     
    imgout_ptr[i] = (sum > 32767) ? 32767 : ((sum < -37267) ? -32767 : sum);
  }
}

#else

#ifndef WIN32
#pragma CODE_SECTION(IMG_conv_3x3_i8_c16s_altek,   ".text:optimized");
#endif

void IMG_conv_3x3_i8_c16s_altek
(
    const unsigned char *restrict  imgin_ptr,
    short               *restrict imgout_ptr,
    short                              width,
    short                              pitch,
    const char          *restrict   mask_ptr,
    short                              shift
)
{
  int                 i;
  int                 sum0,           sum1,           sum2;
  int                 sum3;
                                      
  unsigned int        mask1_0,        mask2_0,        mask3_0;
  unsigned int        mask1_1,        mask2_1,        mask3_1;
  unsigned int        mask_tmp;

  unsigned int        r1_7654,        r1_3210;
  unsigned int        r2_7654,        r2_3210;
  unsigned int        r3_7654,        r3_3210;
  unsigned int        r1_5432,        r2_5432,        r3_5432;

  unsigned int        sum32,          sum10;
  unsigned int        minVal,         maxVal;

#ifdef WIN32
    __int64           r1_76543210,  r2_76543210, r3_76543210;
#else  
    double            r1_76543210,  r2_76543210, r3_76543210;
#endif

  const unsigned char	*in0,           *in1,           *in2;

  
#ifdef WIN32
		unsigned int            *pulOUT;
		pulOUT     =   (unsigned int *)imgout_ptr; //output buffer
#endif 


  /* -------------------------------------------------------------------- */
  /*  Inform the compiler by _nasserts the following:                     */
  /*      a) The output array is word aligned                             */
  /*      b) Filter Mask array is double word aligned                     */
  /*      c) The width is greater than or equal to 6                      */
  /*      d) The width is a multiple of 4.                                */
  /* -------------------------------------------------------------------- */
#ifndef WIN32
  _nassert((int)imgout_ptr % 4 == 0);    /* word aligned                  */
  _nassert(width               >= 4);    /* width greater or equal to 4   */
  _nassert(width           % 4 == 0);    /* width is a multiple of 4      */
#endif

  minVal = 0x80018001;                   /* - 32767 Min                   */
  maxVal = 0x7FFF7FFF;                   /*   32767 Max                   */

  /*----------------------------------------------------------------------*/
  /*  Read mask values and prepare registers for convolution              */
  /*  Read in reverse to account for mask rotation                        */
  /*----------------------------------------------------------------------*/
  mask_tmp = _mem4_const(&mask_ptr[6]);
  mask1_1  = _packlh2(_swap4(mask_tmp),_swap4(mask_tmp)) & 0xffffff00;

  mask_tmp = _mem4_const(&mask_ptr[3]);
  mask2_1  = _packlh2(_swap4(mask_tmp),_swap4(mask_tmp)) & 0xffffff00;

  mask_tmp = _mem4_const(&mask_ptr[0]);
  mask3_1  = _packlh2(_swap4(mask_tmp),_swap4(mask_tmp)) & 0xffffff00;

  mask1_0 = _extu(mask1_1, 0, 8);
  mask2_0 = _extu(mask2_1, 0, 8);
  mask3_0 = _extu(mask3_1, 0, 8);

  /* -------------------------------------------------------------------- */
  /*  Initialise pointers to the start of each row                        */
  /* -------------------------------------------------------------------- */
  in0     = imgin_ptr;
  in1     = in0 + pitch;
  in2     = in1 + pitch;

  /* -------------------------------------------------------------------- */
  /*  Loop is manually unrolled by 4                                      */
  /* -------------------------------------------------------------------- */

#ifdef WIN32
  for (i=0; i<width; i+=4, pulOUT+=2) 
  {
#else
  #pragma MUST_ITERATE(1, ,1)
  for (i=0; i<width; i+=4) 
  {
#endif    
    /* ------------------------------------------------------------------ */
    /*  Load 8 values from each row (only use 6)                          */
    /* ------------------------------------------------------------------ */
#if 0           
    _memd8_const(in0);
    r1_76543210 = g_read8Result;
    _memd8_const(in1);
    r2_76543210 = g_read8Result;
    _memd8_const(in2); 
    r3_76543210 = g_read8Result;
#else     
    r1_76543210 = _memd8_const(in0);
    r2_76543210 = _memd8_const(in1);
    r3_76543210 = _memd8_const(in2);
#endif
    /* ------------------------------------------------------------------ */
    /*  Update pointers for next iteration                                */
    /* ------------------------------------------------------------------ */
    in0 += 4;
    in1 += 4;
    in2 += 4;

    /* ------------------------------------------------------------------ */
    /*  Extract lower four values for 1st set of convolution sums         */
    /* ------------------------------------------------------------------ */
    r1_3210 = _lo(r1_76543210);
    r2_3210 = _lo(r2_76543210);
    r3_3210 = _lo(r3_76543210);
    r1_7654 = _hi(r1_76543210);
    r2_7654 = _hi(r2_76543210);
    r3_7654 = _hi(r3_76543210);

    /* ------------------------------------------------------------------ */
    /*  Calculate 1st pair of sums and pack                               */
    /* ------------------------------------------------------------------ */
    sum0 = (_dotpsu4(mask1_0, r1_3210) +                        //
            _dotpsu4(mask2_0, r2_3210) + 
            _dotpsu4(mask3_0, r3_3210)) >> shift;
    

    sum1 = (_dotpsu4(mask1_1, r1_3210) + 
            _dotpsu4(mask2_1, r2_3210) + 
            _dotpsu4(mask3_1, r3_3210)) >> shift;

    
    sum10 = _spack2(sum1,sum0); //saturate into 16bit ((sum1 & 0x0000FFFF)<<16 | (sum0 & 0x0000FFFF))

    
    /* ------------------------------------------------------------------ */
    /*  Combine middle four values for 2nd set of convolutions sums       */
    /* ------------------------------------------------------------------ */
    r1_5432 = _packlh2(r1_7654, r1_3210);
    r2_5432 = _packlh2(r2_7654, r2_3210);
    r3_5432 = _packlh2(r3_7654, r3_3210);

    /* ------------------------------------------------------------------ */
    /*  Calculate 2nd pair of sums and pack                               */
    /* ------------------------------------------------------------------ */
    sum2 = (_dotpsu4(mask1_0, r1_5432) + 
            _dotpsu4(mask2_0, r2_5432) + 
            _dotpsu4(mask3_0, r3_5432)) >> shift;

    sum3 = (_dotpsu4(mask1_1, r1_5432) + 
            _dotpsu4(mask2_1, r2_5432) + 
            _dotpsu4(mask3_1, r3_5432)) >> shift;

    sum32 = _spack2(sum3,sum2);

//    DSPPrinfString(sum2, sum3, sum32);
    /* ------------------------------------------------------------------ */
    /* Clamp the values to -256 < x < 256 then store using amem4          */
    /* ------------------------------------------------------------------*/ 
    sum10 = _max2(sum10, minVal);
    sum32 = _max2(sum32, minVal);
    sum10 = _min2(sum10, maxVal);
    sum32 = _min2(sum32, maxVal);

#ifdef WIN32
	*pulOUT = sum10;
	*(pulOUT+1)  = sum32;
#else            
    _amem4((void*) &imgout_ptr[i])   = sum10;
    _amem4((void*) &imgout_ptr[i+2]) = sum32;
#endif
				

  }
}

#endif

/* ======================================================================== */
/*  End of file:  IMG_conv_3x3_i8_c16s_altek.c                                  */
/* ======================================================================== */
