
/**
  *  \addtogroup TILib
  *  @{
  */

#pragma once

#include "alTILibDef.h"

#ifdef WIN32
#pragma comment(lib, "imglib2_host.lib")
#endif

#ifndef WIN32

#include "imglib64plus.h"

#else

#ifdef __cplusplus
extern "C" {
#endif

// The following c model code is only used to check the result between intrinsic code. 
// Please do not use these code in our algorithm for FW run-time.
// In PC Simulator (WIN32), those TI imglib function will be linked to these c model functions.
// All functions/files with "_altek" is modified by altek.

#include "imglib/IMG_boundary_8_c.h"
#include "imglib/IMG_boundary_16s_c.h"
#include "imglib/IMG_clipping_16s_c.h"

#include "imglib/IMG_conv_3x3_i8_c8s_c.h"
#include "imglib/IMG_conv_3x3_i8_c8_altek_c.h"
#include "imglib/IMG_conv_3x3_i8_c16s_altek_c.h"
#include "imglib/IMG_conv_3x3_i16_c16s_c.h"
#include "imglib/IMG_conv_3x3_i16s_c16s_c.h"

#include "imglib/IMG_conv_5x5_i8_c8s_c.h"
#include "imglib/IMG_conv_5x5_i8_c16s_c.h"
#include "imglib/IMG_conv_5x5_i16s_c16s_c.h"

#include "imglib/IMG_conv_7x7_i8_c8s_c.h"
#include "imglib/IMG_conv_7x7_i8_c16s_c.h"
#include "imglib/IMG_conv_7x7_i16s_c16s_c.h"

#include "imglib/IMG_conv_11x11_i8_c8s_c.h"
#include "imglib/IMG_conv_11x11_i16s_c16s_c.h"

#include "imglib/IMG_corr_3x3_i8_c8_c.h"
#include "imglib/IMG_corr_3x3_i8_c16s_c.h"
#include "imglib/IMG_corr_3x3_i16_c16s_c.h"
#include "imglib/IMG_corr_3x3_i16s_c16s_c.h"

#include "imglib/IMG_corr_5x5_i16s_c16s_c.h"

#include "imglib/IMG_corr_11x11_i8_c16s_c.h"
#include "imglib/IMG_corr_11x11_i16s_c16s_c.h"

#include "imglib/IMG_corr_gen_i16s_c16s_c.h"
#include "imglib/IMG_corr_gen_iq_c.h"

#include "imglib/IMG_dilate_bin_c.h"

#include "imglib/IMG_erode_bin_c.h"

#include "imglib/IMG_errdif_bin_8_c.h"
#include "imglib/IMG_errdif_bin_16_c.h"

#include "imglib/IMG_fdct_8x8_c.h"

#include "imglib/IMG_histogram_8_c.h"
#include "imglib/IMG_histogram_16_c.h"

#include "imglib/IMG_idct_8x8_12q4_c.h"

#include "imglib/IMG_mad_8x8_c.h"
#include "imglib/IMG_mad_16x16_c.h"

#include "imglib/IMG_median_3x3_8_c.h"
#include "imglib/IMG_median_3x3_16_c.h"
#include "imglib/IMG_median_3x3_16s_c.h"

#include "imglib/IMG_mpeg2_vld_inter_c.h"
#include "imglib/IMG_mpeg2_vld_intra_c.h"

#include "imglib/IMG_perimeter_8_c.h"
#include "imglib/IMG_perimeter_16_c.h"

#include "imglib/IMG_pix_expand_c.h"
#include "imglib/IMG_pix_sat_c.h"

#include "imglib/IMG_quantize_c.h"

#include "imglib/IMG_sad_8x8_c.h"
#include "imglib/IMG_sad_16x16_c.h"

#include "imglib/IMG_sobel_3x3_8_c.h"
#include "imglib/IMG_sobel_3x3_i8_c16_c.h"
#include "imglib/IMG_sobel_3x3_16_c.h"
#include "imglib/IMG_sobel_3x3_16s_c.h"
#include "imglib/IMG_sobel_5x5_16s_c.h"
#include "imglib/IMG_sobel_7x7_16s_c.h"

#include "imglib/IMG_thr_gt2max_8_c.h"
#include "imglib/IMG_thr_gt2max_16_c.h"

#include "imglib/IMG_thr_gt2thr_8_c.h"
#include "imglib/IMG_thr_gt2thr_16_c.h"

#include "imglib/IMG_thr_le2min_8_c.h"
#include "imglib/IMG_thr_le2min_16_c.h"

#include "imglib/IMG_thr_le2thr_8_c.h"
#include "imglib/IMG_thr_le2thr_16_c.h"

#include "imglib/IMG_wave_horz_c.h"
#include "imglib/IMG_wave_vert_c.h"

#include "imglib/IMG_yc_demux_be16_8_c.h"
#include "imglib/IMG_yc_demux_be16_16_c.h"
#include "imglib/IMG_yc_demux_le16_8_c.h"
#include "imglib/IMG_yc_demux_le16_16_c.h"

#include "imglib/IMG_ycbcr422pl_to_rgb565_c.h"

#ifdef __cplusplus
}
#endif

#define     boundary                        boundary_cn

#define     IMG_boundary_16s                IMG_boundary_16s_cn
#define     IMG_clipping_16s                IMG_clipping_16s_cn

#define     IMG_conv_3x3_i8_c8s             IMG_conv_3x3_i8_c8s_cn
#define     IMG_conv_3x3_i8_c8_altek        IMG_conv_3x3_i8_c8_altek_cn
//#define     IMG_conv_3x3_i8_c16s_altek      IMG_conv_3x3_i8_c16s_altek_cn
#define     IMG_conv_3x3_i16_c16s           IMG_conv_3x3_i16_c16s_cn
#define     IMG_conv_3x3_i16s_c16s          IMG_conv_3x3_i16s_c16s_cn

#define     IMG_conv_5x5_i8_c8s             IMG_conv_5x5_i8_c8s_cn
#define     IMG_conv_5x5_i8_c16s            IMG_conv_5x5_i8_c16s_cn
#define     IMG_conv_5x5_i16s_c16s          IMG_conv_5x5_i16s_c16s_cn

#define     IMG_conv_7x7_i8_c8s             IMG_conv_7x7_i8_c8s_cn
#define     IMG_conv_7x7_i8_c16s            IMG_conv_7x7_i8_c16s_cn
#define     IMG_conv_7x7_i16s_c16s          IMG_conv_7x7_i16s_c16s_cn

#define     IMG_conv_11x11_i8_c8s           IMG_conv_11x11_i8_c8s_cn
#define     IMG_conv_11x11_i16s_c16s        IMG_conv_11x11_i16s_c16s_cn

#define     IMG_corr_3x3_i8_c8              IMG_corr_3x3_i8_c8_cn
#define     IMG_corr_3x3_i8_c16s            IMG_corr_3x3_i8_c16s_cn
#define     IMG_corr_3x3_i16_c16s           IMG_corr_3x3_i16_c16s_cn
#define     IMG_corr_3x3_i16s_c16s          IMG_corr_3x3_i16s_c16s_cn

#define     IMG_corr_5x5_i16s_c16s          IMG_corr_5x5_i16s_c16s_cn

#define     IMG_corr_11x11_i8_c16s          IMG_corr_11x11_i8_c16s_cn
#define     IMG_corr_11x11_i16s_c16s        IMG_corr_11x11_i16s_c16s_cn

#define     IMG_corr_gen_i16s_c16s          IMG_corr_gen_i16s_c16s_cn
#define     IMG_corr_gen_iq                 IMG_corr_gen_iq_cn

#define     IMG_dilate_bin                  IMG_dilate_bin_cn

#define     IMG_erode_bin                   IMG_erode_bin_cn

#define     IMG_errdif_bin_8                IMG_errdif_bin_8_cn
#define     IMG_errdif_bin_16               IMG_errdif_bin_16_cn

#define     IMG_fdct_8x8                    IMG_fdct_8x8_cn

#define     IMG_histogram_8                 IMG_histogram_8_cn
#define     IMG_histogram_16                IMG_histogram_16_cn

#define     IMG_idct_8x8_12q4               IMG_idct_8x8_12q4_cn

#define     IMG_mad_8x8                     IMG_mad_8x8_cn
#define     IMG_mad_16x16                   IMG_mad_16x16_cn

#define     IMG_median_3x3_8                IMG_median_3x3_8_cn
#define     IMG_median_3x3_16               IMG_median_3x3_16_cn
#define     IMG_median_3x3_16s              IMG_median_3x3_16s_cn

#define     IMG_mpeg2_vld_inter             IMG_mpeg2_vld_inter_cn
#define     IMG_mpeg2_vld_intra             IMG_mpeg2_vld_intra_cn

#define     IMG_perimeter_8                 IMG_perimeter_8_cn
#define     IMG_perimeter_16                IMG_perimeter_16_cn

#define     IMG_pix_expand                  IMG_pix_expand_cn
#define     IMG_pix_sat                     IMG_pix_sat_cn

#define     IMG_quantize                    IMG_quantize_cn

#define     IMG_sad_8x8                     IMG_sad_8x8_cn
#define     IMG_sad_16x16                   IMG_sad_16x16_cn

#define     IMG_sobel_3x3_8                 IMG_sobel_3x3_8_cn
#define     IMG_sobel_3x3_i8_c16            IMG_sobel_3x3_i8_c16_cn
#define     IMG_sobel_3x3_16                IMG_sobel_3x3_16_cn
#define     IMG_sobel_3x3_16s               IMG_sobel_3x3_16s_cn
#define     IMG_sobel_5x5_16s               IMG_sobel_5x5_16s_cn
#define     IMG_sobel_7x7_16s               IMG_sobel_7x7_16s_cn

#define     IMG_thr_gt2max_8                IMG_thr_gt2max_8_cn
#define     IMG_thr_gt2max_16               IMG_thr_gt2max_16_cn

#define     IMG_thr_gt2thr_8                IMG_thr_gt2thr_8_cn
#define     IMG_thr_gt2thr_16               IMG_thr_gt2thr_16_cn

#define     IMG_thr_le2min_8                IMG_thr_le2min_8_cn
#define     IMG_thr_le2min_16               IMG_thr_le2min_16_cn

#define     IMG_thr_le2thr_8                IMG_thr_le2thr_8_cn
#define     IMG_thr_le2thr_16               IMG_thr_le2thr_16_cn

#define     IMG_wave_horz                   IMG_wave_horz_cn
#define     IMG_wave_vert                   IMG_wave_vert_cn

#define     IMG_yc_demux_be16_8             IMG_yc_demux_be16_8_cn
#define     IMG_yc_demux_be16_16            IMG_yc_demux_be16_16_cn
#define     IMG_yc_demux_le16_8             IMG_yc_demux_le16_8_cn
#define     IMG_yc_demux_le16_16            IMG_yc_demux_le16_16_cn

#define     IMG_ycbcr422pl_to_rgb565        IMG_ycbcr422pl_to_rgb565_cn
#endif



/**
  *  @}
  */
