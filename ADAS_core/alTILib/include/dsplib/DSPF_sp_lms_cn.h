/* ======================================================================= */
/* DSPF_sp_lms.h -- LMS Adaptive Filter                                    */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef _DSPF_SP_LMS_CN_H_
#define _DSPF_SP_LMS_CN_H_

float DSPF_sp_lms_cn(const float *x, float *h, const float *y_i,
    float *y_o, const float ar, float error, const int nh, const int ny);

#endif /* _DSPF_SP_LMS_CN_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_lms_cn.h                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

