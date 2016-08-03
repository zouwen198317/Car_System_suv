
#pragma once

#include "alLUT_v2_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** 
    \brief To process the table LU according to original full look-up table. 
    \param a_ptTable [IN] The image LUT.
    \param a_pucSrcImage [IN] Source image buffers, 0 ~ 6
    \param a_pucDstImage [OUT] Destination image buffer.
*/
void alLUT_v2_ProcessFullLU(alLUT_v2_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage);

/** 
    \brief To process the table LU according to original full look-up table, with GAE. 
    \param a_pcGAE_YOffset [IN] The Y offset for each source image.
    \param a_ptTable [IN] The image LUT.
    \param a_pucSrcImage [IN] Source image buffers, 0 ~ 6
    \param a_pucDstImage [OUT] Destination image buffer.
*/
void alLUT_v2_ProcessFullLU_ApplyGAE(INT8 * a_pcGAE_YOffset, alLUT_v2_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage);

#ifdef __cplusplus
}
#endif

