/* ======================================================================= */
/* DSPF_sp_fircirc.h -- Circular FIR Filter                                */
/*                 Natural C Implementation                                */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef _DSPF_SP_FIRCIRC_CN_H_
#define _DSPF_SP_FIRCIRC_CN_H_

void DSPF_sp_fircirc_cn(const float *x, const float *h, float *y,
    const int index, const int csize, const int nh, const int ny);

#endif /* _DSPF_SP_FIRCIRC_CN_H_ */

/* ======================================================================= */
/*  End of file:  DSPF_sp_fircirc_cn.h                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

