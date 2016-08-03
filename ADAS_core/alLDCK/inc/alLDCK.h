
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alLDCK_Def.h"
#include "alFM_v2_1.h"
#include "CommonK.h"


#define alLDCK_TEST 1 // 1: TEST 0: REAL

/** \brief harris K */
#define alLDCK_HARRISS_K 3000 // 0.04 * 2^15

/** \brief harris score threshold */
#define alLDCK_HARRISS_SCORE_TH 24000

/** \brief corner check threshold */
#define alLDCK_CORNER_CHECK_TH 4

/** \brief corner check GAP */
#define alLDCK_CORNER_CHECK_GAP 3



/**
\brief alLDCK_Main : calibration for Len Distortion Curve (LDC)
\param a_pucSrcY [IN] source image (only Y channal)
\param a_ptFM_v2_Model [IN] fish eye model
\param a_ptData [INOUT] alLDCK Data
*/
void alLDCK_Main(UINT8 *a_pucSrcY, alFM_v2_1_Model *a_ptFM_v2_Model, alLDCK_Data *a_ptData);


/**
\brief alLDCK_CoenerDetect : corner detecttion
\param a_pucSrcY [IN] source image (only Y channal)
\param a_ptFM_v2_Model [IN] fish eye model
\param a_ptData [INOUT] alLDCK Data
*/
void alLDCK_CoenerDetect(UINT8 *a_pucSrcY, alFM_v2_1_Model *a_ptFM_v2_Model, alLDCK_Data *a_ptData);

/**
\brief alLDCK_CoenerDetect : corner detecttion
\param a_lWidth [IN] source image Width
\param a_lHeight [IN] source image Height
\param a_pucSrcY [IN] source image (only Y channal)
\param a_pucBuffer [IN] buffer
\param a_atFP [INOUT] FP position
\return 0: fail 1: success
*/
UINT8 alLDCK_FPDetect(INT32 a_lWidth, INT32 a_lHeight, UINT8 *a_pucSrcY, UINT8 *a_pucBuffer, alPointFLOAT64 a_atFP[alLDCK_FP_NUM]);

/**
\brief alLDCK_DistortionCorrection : Distortion Correction by parameter
\param a_ptParams_Current [IN] Current Params
\param a_atCorner [IN] Corner Data
\param a_atCornerUndistorted [OUT] Undistorted Corner Data
*/
void alLDCK_DistortionCorrectionByParameter(
    alLDCK_LDC_Params *a_ptParams_Current,
    alPointFLOAT64 a_atCorner[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM]
);

/**
\brief alLDCK_GenHomographyMatrix : Generate Homography Matrix
\param a_aucCornerFlagthe  [IN] corner enable flag 0: on  1: off
\param a_aucCornerFlag_H_Matrix  [IN] the corner enable flag 0: on  1 : off 
\param a_atCornerRectified [IN] Rectified Corner Data
\param a_atCornerIdeal [IN] Ideal Corner Data
\param a_peH [IN] Homography Matrix (real to ideal)
\param a_peH_Inv [IN] Inverse Homography Matrix (ideal to real)
*/
void alLDCK_GenHomographyMatrix(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM],
    FLOAT64 a_peH[COMMONK_M33_ELEMENT_CNT],
    FLOAT64 a_peH_Inv[COMMONK_M33_ELEMENT_CNT]
    );

/**
\brief alLDCK_CornerRectify : Rectify Corner by Homography matrix
\param a_atCornerUndistorted [IN] Undistorted Corner Data
\param aeH [IN] Homography matrix
\param a_atCornerRectified [OUT] Rectified Corner Data
*/
void alLDCK_CornerRectify(
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM],
    FLOAT64 aeH[COMMONK_M33_ELEMENT_CNT],
    alPointFLOAT64 a_atCornerRectified[alLDCK_CORNER_NUM]
);

/**
\brief alLDCK_ErrorEstimate :Error Estimate
\param a_aucCornerFlagthe  [IN] corner enable flag 0: on  1: off
\param a_atCornerRectified [IN] Rectified Corner Data
\param a_atCornerIdeal [IN] Ideal Corner Data
\return error
*/
FLOAT64 alLDCK_ErrorEstimate(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerRectified[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    );

/**
\brief alLDCK_UpdateParameter : Update Parameter
\param a_lIterCnt  [IN] iteration cnt
\param a_aucCornerFlagthe  [IN] corner enable flag 0: on  1: off
\param a_aucCornerFlag_H_Matrix  [IN] the corner enable flag 0: on  1 : off
\param a_ptParams_Default [INOUT] Default Params
\param a_ptParams_Current [INOUT] Current Params
\param a_atCorner [IN] Corner Data
\param a_atCornerIdeal [IN] Ideal Corner Data
*/
void alLDCK_UpdateParameter(
    INT32 a_lIterCnt,
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alLDCK_LDC_Params *a_ptParams_Default,
    alLDCK_LDC_Params *a_ptParams_Current,
    alPointFLOAT64 a_atCorner[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    );


/**
\brief alLDCK_EstimateErrorByParams : get error value
\param a_aucCornerFlagthe  [IN] corner enable flag 0: on  1: off
\param a_aucCornerFlag_H_Matrix  [IN] the corner enable flag 0: on  1 : off
\param a_ptParams_Current [IN] Current Params
\param a_atCorner [IN] Corner Data
\param a_atCornerIdeal [IN] Ideal Corner Data
*/
FLOAT64 alLDCK_EstimateErrorByParams(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alLDCK_LDC_Params *a_ptParams_Current,
    alPointFLOAT64 a_atCorner[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    );




#ifdef __cplusplus
}
#endif
