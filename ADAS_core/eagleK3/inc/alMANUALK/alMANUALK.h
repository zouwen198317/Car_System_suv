
#pragma once

#include "alMANUALK/alMANUALK_Def.h"
#include "alCameraInfo.h"
#include "alFM_v2_1.h"
#include "CommonK.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
  *  \addtogroup CameraCal
  *  @{
  */

/** 
    \brief To calculate the coordinates transform of feature points. 
    \param peSrcFP_X [IN] Source X position of feature points
    \param peSrcFP_Y [IN] Source Y position of feature points
    \param ucNumPts [IN] Number of feature points
    \param uwCoorNorm [IN] The scaling function of feature points coordinates
    \param peM33 [IN] Perspective Transform Matrix from birdview to undistorted image
    \param peDestFP_X [OUT] Destination X position of feature points
    \param peDestFP_Y [OUT] Destination Y position of feature points
*/
/*void EAGLEK3_BVFPTransform(FLOAT64 * peSrcFP_X, FLOAT64 * peSrcFP_Y, 
                           UINT8 ucNumPts, FLOAT64 * peM33, 
                           FLOAT64 * peDestFP_X, FLOAT64 * peDestFP_Y);*/




/** 
    \brief To Generate Single View Planar Image for RGB format. The planar image will be scaled by EAGLEK3_SINGLE_VIEW_SCALAR
           , and y position will be shifted by EAGLEK3_SINGLE_VIEW_OFFSET_Y.
    \param a_ucBVCameraIndx [IN] Indicate camera index.
    \param a_pucSrcImage [IN] Source X position of feature points
    \param a_lSrcWidth [IN] Source Y position of feature points
    \param a_lSrcHeight [IN] Number of feature points
    \param a_pucDestImage [OUT] The scaling function of feature points coordinates
    \param a_lDestWidth [IN] Perspective Transform Matrix from birdview to undistorted image
    \param a_lDestHeight [IN] Destination X position of feature points
    \param a_ptFisheyeModel [IN] Fisheye Model for the current camera.
    \param a_ptCameraCfg [IN] Need the camera install position lCameraPosX, lCameraPosX parameters.
    \param a_peM33 [IN] Destination Y position of feature points
    \see EAGLEK3_SINGLE_VIEW_SCALAR, EAGLEK3_SINGLE_VIEW_OFFSET_Y
*/
void CAMK_GenerateSingleViewPlanarImage_RGB(
    UINT8 a_ucBVCameraIndx,
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    FLOAT64 a_peM33[9],
    alFM_v2_1_Model *a_ptCameraFisheyeModel
);

void MANUALK_InitialByConfigData(
    alFM_v2_1_Model *a_ptFM_v2_Model,
    alCAMERAINFO_ExtrinsicParams a_atCameraExtrinsicParams[alMANUALK_NUM_BV_CHANNEL],
    alCOMMONK_CalibrationParams a_atCalibrationParams[alMANUALK_NUM_BV_CHANNEL],
    alPointINT32  a_atBVFPOffsetFineTuned[alMANUALK_NUM_BV_CHANNEL][alMANUALK_CAMERA_FP_NUM_AUTOK],
    alMANUALK_ChartCrossPointSet *a_ptManualKFieldData,
    alMANUALK_CameraCfg   a_atMANUALK_Cfg[alMANUALK_NUM_BV_CHANNEL],
    alPointINT32 a_talAVM2D_DestImageBufferSize,
    FLOAT32    a_fMMPP,
    alCOMMONK_CommonCfg *a_ptCommonCfg,
    alMANUALK_Params *a_ptParams
);


void MANUALK_ResetYCoordinatesLimit(
    UINT8 a_ucCameraIndx, alCOMMONK_CommonCfg *a_ptCommonCfg, 
    FLOAT32 a_fMMPP, FLOAT64 a_aeHomographyMatrix[2][9], INT32 *a_plOriImgYLimit
);

void MANUALK_SingleViewForCalibration(
    UINT8 a_ucCameraIndex, UINT8 * a_pucSrcBuffer, UINT8 * a_ucDestBuffer,
    alFM_v2_1_Model *a_ptCameraFisheyeModel, alMANUALK_CameraCfg a_atMANUALK_Cfg[alMANUALK_NUM_BV_CHANNEL],
    alMANUALK_Params *a_ptMANUALK_Params, alCAMERAINFO_ExtrinsicParams *a_ptCAMParams,
    alCOMMONK_CalibrationParams *a_ptCalibrationParams
    );

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
