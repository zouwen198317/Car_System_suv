#pragma once
#include "BVCAM_FACAUTOK/RectK_Def.h"
#include "lsd.h"
#include "alCameraInfo.h"
#include "CommonK.h"
#include "basedef.h"


#define alRECK_DEBUG 0

#if alRECK_DEBUG
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_DeBug.h"
#endif


#define     alRECK_VAR_TH (750)

/**
*  \addtogroup alRECK
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif


/**
\brief Line Segment Detection for Rectangle K(2212).
\param a_pucBuffer [IN] Working buffer
\param a_pucYBuffer [IN] Y image buffer
\param a_tROI [IN] Detect ROI
\param a_plNum [OUT] line number
\param a_peResult [OUT] Line Segment result
*/
void	LineSegDetectionRec(
    UINT8 *a_pucBuffer,
    UINT8 *a_pucYBuffer,
    alRectINT32 a_tROI,
    INT32 *a_plNum,
    FLOAT64 **a_peResult
    );

/**
\brief Auto Calibration by Rectangle Board (view by view) (2200).
\param a_ptBVImgSize [IN] The BV Buffer size
\param a_pucBuffer [IN] a_Working Buffer
\param a_ptCfg [IN] config data
\param a_ptParameter [IN] parameter
\param a_pucSrcBuffer [IN] source Buffer of camera
\param a_aeOriginalM33 [IN] Pure M33
\param a_aeM33RecK [OUT] RecK M33
\param a_peFPRecKX [OUT] FP's X detected in this function
\param a_peFPRecKY [OUT] FP's Y detected in this function
\param a_pucRecKFlag [OUT] RecTangleK Success Flag
*/
void	alRECK_Calibration(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucBuffer,
	alRECK_Cfg *a_ptCfg,
	alRECK_Parameter *a_ptParameter,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeM33RecK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 *a_peFPRecKX,
	FLOAT64 *a_peFPRecKY,
	UINT8  *a_pucRecKFlag
	);

#ifdef __cplusplus
}
#endif

/**
*  @}
*/
