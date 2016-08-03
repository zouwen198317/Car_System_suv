
/**
  *  \addtogroup TILib
  *  @{
  */


#pragma once

#include "alTILibDef.h"

#ifndef WIN32
    #include "dsplib674x.h"
#else

#ifdef __cplusplus
extern "C" {
#endif

    #include "dsplib/DSPF_util.h"
    #include "dsplib/DSPF_blk_eswap16_cn.h"
    #include "dsplib/DSPF_blk_eswap32_cn.h"
    #include "dsplib/DSPF_blk_eswap64_cn.h"
    #include "dsplib/DSPF_fltoq15_cn.h"
    #include "dsplib/DSPF_q15tofl_cn.h"
    #include "dsplib/DSPF_sp_autocor_cn.h"
    #include "dsplib/DSPF_sp_biquad_cn.h"
    #include "dsplib/DSPF_sp_bitrev_cplx_cn.h"
    #include "dsplib/DSPF_sp_blk_move_cn.h"
    #include "dsplib/DSPF_sp_cfftr2_dit_cn.h"
    #include "dsplib/DSPF_sp_cfftr4_dif_cn.h"
    #include "dsplib/DSPF_sp_convol_cn.h"
    #include "dsplib/DSPF_sp_dotp_cplx_cn.h"
    #include "dsplib/DSPF_sp_dotprod_cn.h
    #include "dsplib/DSPF_sp_fftSPxSP_cn.h"
    #include "dsplib/DSPF_sp_fir_cplx_cn.h"
    #include "dsplib/DSPF_sp_fir_gen_cn.h"
    #include "dsplib/DSPF_sp_fir_r2_cn.h"
    #include "dsplib/DSPF_sp_fircirc_cn.h"
    #include "dsplib/DSPF_sp_icfftr2_dif_cn.h"
    #include "dsplib/DSPF_sp_ifftSPxSP_cn.h"
    #include "dsplib/DSPF_sp_iir_cn.h"
    #include "dsplib/DSPF_sp_iirlat_cn.h"
    #include "dsplib/DSPF_sp_lms_cn.h"
    #include "dsplib/DSPF_sp_mat_mul_cn.h"
    #include "dsplib/DSPF_sp_mat_mul_cplx_cn.h"
    #include "dsplib/DSPF_sp_mat_trans_cn.h"
    #include "dsplib/DSPF_sp_maxidx_cn.h"
    #include "dsplib/DSPF_sp_maxval_cn.h"
    #include "dsplib/DSPF_sp_minerr_cn.h"
    #include "dsplib/DSPF_sp_minval_cn.h"
    #include "dsplib/DSPF_sp_vecmul_cn.h"
    #include "dsplib/DSPF_sp_vecrecip_cn.h"
    #include "dsplib/DSPF_sp_vecsum_sq_cn.h"
    #include "dsplib/DSPF_sp_w_vec_cn.h"


#ifdef __cplusplus
}
#endif

#define     DSPF_blk_eswap16                        DSPF_blk_eswap16_cn
#define     DSPF_blk_eswap32                        DSPF_blk_eswap32_cn
#define     DSPF_blk_eswap64                        DSPF_blk_eswap64_cn
#define     DSPF_fltoq15                            DSPF_fltoq15_cn
#define     DSPF_q15tofl                            DSPF_q15tofl_cn
#define     DSPF_sp_autocor                         DSPF_sp_autocor_cn
#define     DSPF_sp_biquad                          DSPF_sp_biquad_cn
#define     DSPF_sp_bitrev_cplx                     DSPF_sp_bitrev_cplx_cn
#define     DSPF_sp_blk_move                        DSPF_sp_blk_move_cn
#define     DSPF_sp_cfftr2_dit                      DSPF_sp_cfftr2_dit_cn
#define     DSPF_sp_cfftr4_dif                      DSPF_sp_cfftr4_dif_cn
#define     DSPF_sp_convol                          DSPF_sp_convol_cn
#define     DSPF_sp_dotp_cplx                       DSPF_sp_dotp_cplx_cn
#define     DSPF_sp_dotprod                         DSPF_sp_dotprod_cn
#define     DSPF_sp_fftSPxSP                        DSPF_sp_fftSPxSP_cn
#define     DSPF_sp_fir_cplx                        DSPF_sp_fir_cplx_cn
#define     DSPF_sp_fir_gen                         DSPF_sp_fir_gen_cn
#define     DSPF_sp_fir_r2                          DSPF_sp_fir_r2_cn
#define     DSPF_sp_fircirc                         DSPF_sp_fircirc_cn
#define     DSPF_sp_icfftr2_dif                     DSPF_sp_icfftr2_dif_cn
#define     DSPF_sp_ifftSPxSP                       DSPF_sp_ifftSPxSP_cn
#define     DSPF_sp_iir                             DSPF_sp_iir_cn
#define     DSPF_sp_iirlat                          DSPF_sp_iirlat_cn
#define     DSPF_sp_lms                             DSPF_sp_lms_cn
#define     DSPF_sp_mat_mul                         DSPF_sp_mat_mul_cn
#define     DSPF_sp_mat_mul_cplx                    DSPF_sp_mat_mul_cplx_cn
#define     DSPF_sp_mat_trans                       DSPF_sp_mat_trans_cn
#define     DSPF_sp_maxidx                          DSPF_sp_maxidx_cn
#define     DSPF_sp_maxval                          DSPF_sp_maxval_cn
#define     DSPF_sp_minerr                          DSPF_sp_minerr_cn
#define     DSPF_sp_minval                          DSPF_sp_minval_cn
#define     DSPF_sp_vecmul                          DSPF_sp_vecmul_cn
#define     DSPF_sp_vecrecip                        DSPF_sp_vecrecip_cn
#define     DSPF_sp_vecsum_sq                       DSPF_sp_vecsum_sq_cn
#define     DSPF_sp_w_vec                           DSPF_sp_w_vec_cn

#endif

/**
  *  @}
  */