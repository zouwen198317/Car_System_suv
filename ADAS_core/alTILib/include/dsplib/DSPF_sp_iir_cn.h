/* ======================================================================= */
/* DSPF_sp_iir_cn.h -- IIR Filter                                          */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef _DSPF_SP_IIR_CN_H_
#define _DSPF_SP_IIR_CN_H_

void DSPF_sp_iir_cn (float *y1,
    const float *x,
    float *y2,
    const float *hb,
    const float *ha,
    int n);

#endif /* _DSPF_SP_IIR_CN_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_iir_cn.h                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

