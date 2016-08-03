#pragma once

#include "BVCAM_FACAUTOK/CrossMarkK_Def.h"
#include "BVCAM_FACAUTOK/CRSMRKDET.h"
#include "CommonK.h"
#include "alCameraInfo.h"
#include "basedef.h"


#define alCROSSMARKK_DEBUG 1

#if alCROSSMARKK_DEBUG
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_DeBug.h"
#endif




/**
*  \addtogroup alCROSSMARKK
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif


/**
\brief Auto Calibration by Cross mark (2400).
\param alPointINT32 [IN] BV Img Size,
\param a_pucBuffer [IN] a_Working Buffer
\param a_ptCfg [IN] config data
\param a_ptParameter [IN] parameter
\param a_ucRefineFlag [IN] ROI Refine Flag
\param a_pucSrcBuffer [IN] source Buffer of camera
\param a_aeOriginalM33 [IN] Original M33
\param a_aeM33CrossMarkK [OUT] CrossMarkK M33
\param a_peFPCrossMarkKX [OUT] FP's X detected in this function
\param a_peFPCrossMarkKY [OUT] FP's Y detected in this function
\param a_pucCrossMarkKFlag [OUT] CrossMarkK Success Flag
*/
void	alCrossMarkK_Calibration(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucBuffer,
	alCROSSMARKK_Cfg *a_ptCfg,
	alCROSSMARKK_Parameter *a_ptParameter,
	UINT8 a_ucRefineFlag,
	UINT8 *a_pucSrcBuffer,
    FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
    FLOAT64 a_aeM33CrossMarkK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 *a_peFPCrossMarkKX,
	FLOAT64 *a_peFPCrossMarkKY,
	UINT8 *a_pucCrossMarkKFlag
);




#ifdef __cplusplus
}
#endif

/**
*  @}
*/
