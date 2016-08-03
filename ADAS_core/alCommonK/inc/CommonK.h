
#pragma once
#include "alFM_v2_1.h"
#include "atype.h"
#include <stdio.h>
#include <stdlib.h>
#include "basedef.h"
#include "CommonK_Def.h"


/**
*  \addtogroup alCOMMONK
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/**
\brief Enhance Image(2422).
\param a_pucSrcBuffer [IN] source Buffer of camera
\param  a_pucOutBuffer [OUT] Out Buffer for enhance image
*/
void COMMONK_EnhanceImage(
	INT32 a_lWidth, INT32 a_lHeight,
	UINT8 *a_pucSrcBuffer,
	UINT8 *a_pucOutBuffer
);

/** \brief The index to indicate the current used camera. */
typedef enum
{
	alBVCAM_FACAUTOK_BV_LEFT = -90,
	alBVCAM_FACAUTOK_BV_RIGHT = 90,
	alBVCAM_FACAUTOK_BV_FRONT = 0,
	alBVCAM_FACAUTOK_BV_BACK = 180
} alBVCAM_FACAUTOK_CAM_ANGLE;

/**
\brief To perform the coordinates transform by perspective matrix.
\param peM33 [IN] Input the perspective matrix.
\param eSrcX [IN] Input the source coordinates of X.
\param eSrcY [IN] Input the source coordinates of Y.
\param eDestX [OUT] Output the destination coordinates of X.
\param eDestX [OUT] Output the destination coordinates of Y.
*/
void COMMONK_PerformCoordinatesTransform(
	const FLOAT64 * a_peM33, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, 
	FLOAT64 * a_peDestX, FLOAT64 * a_peDestY
);

/**
\brief coordinate transform from SBV to BV 
\param a_lSBV_Width [IN] SBV Width
\param a_lSBV_Height [IN] SBV Height
\param a_lBV_Width [IN] BV Width
\param a_lBV_Height [IN] BV Height
\param a_ucNumPts [IN] point number
\param a_lCamAngle [IN] rotation angle
\param a_lCamPosX [IN] camera position X
\param a_lCamPosY [IN] camera position Y
\param a_lOffsetX [IN] sbv offset x
\param a_lOffsetY [IN] sbv offset y
\param a_eSBVScale [IN] sbv scale
\param a_eMMPP [IN] mm per pixel
\param a_peSPP_X [IN] SBV X
\param a_peSPP_Y [IN] SBV Y
\param a_peBVP_X [OUT] X coordinate in BV
\param a_peBVP_Y [OUT] y coordinaye in BV
*/
void COMMONK_SBV2Birdview(
INT32 a_lSBV_Width, INT32 a_lSBV_Height, INT32 a_lBV_Width, INT32 a_lBV_Height,
UINT8 a_ucNumPts, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
FLOAT64 * a_peSPP_X, FLOAT64 * a_peSPP_Y,
FLOAT64 * a_peBVP_X, FLOAT64 * a_peBVP_Y
);

/**
\brief coordinate transform from SBV to BV
\param a_lBV_Width [IN] BV Width
\param a_lBV_Height [IN] BV Height
\param a_lSBV_Width [IN] SBV Width
\param a_lSBV_Height [IN] SBV Height
\param a_ucNumPts [IN] Detect ROI
\param a_lCamAngle [IN] source Buffer of camera
\param a_lCamPosX [IN] Fisheye Model
\param a_lCamPosY [IN] transform matrix (BV to Src >> [0])
\param a_lOffsetX [IN] Define the y position limitation to avoid the overflow
\param a_lOffsetY [IN] Define the y position limitation to avoid the overflow
\param a_eSBVScale [IN] Define the y position limitation to avoid the overflow
\param a_eMMPP [IN] Define the y position limitation to avoid the overflow
\param a_peBVP_X [IN] X coordinate in BV
\param a_peBVP_Y [IN] y coordinate in BV
\param a_peSPP_X [OUT] SBV X 
\param a_peSPP_Y [OUT] SBV Y 

*/
void COMMONK_Birdview2SBV(
    INT32 a_lBV_Width, INT32 a_lBV_Height, INT32 a_lSBV_Width, INT32 a_lSBV_Height,
	UINT8 a_ucNumPts, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
	INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
	FLOAT64 * a_peBVP_X, FLOAT64 * a_peBVP_Y,
	FLOAT64 * a_peSPP_X, FLOAT64 * a_peSPP_Y
);

/**
\brief SBV Generating by CFG(2211).
\param a_ptBVImgSize [IN] BV Img Size
\param a_tROI [IN] Detect ROI
\param a_pucSrcBuffer [IN] source Buffer of camera (only Y Channal)
\param a_ptFisheyeModel [IN] Fisheye Model
\param a_ptM33 [IN] transform matrix (BV to Src >> [0])
\param a_lOriImgYLimit [IN] Define the y position limitation to avoid the overflow
\param a_lCamAngle [IN] Define the y position limitation to avoid the overflow
\param a_lCamPosX [IN] Define the y position limitation to avoid the overflow
\param a_lCamPosY [IN] Define the y position limitation to avoid the overflow
\param a_lOffsetX [IN] SBV X offset
\param a_lOffsetY [IN] SBV Y offset
\param a_eSBVScale [IN] source Buffer of camera
\param a_eMMPP [IN] mmpp
\param a_pucSBVBuffer [OUT] Single BirdView Buffer (only Y Channal)
*/

void	COMMONK_SBVGeneratingK(
alPointINT32 *a_ptBVImgSize,
alRectINT32 a_tROI,
UINT8 *a_pucSrcBuffer,
alFM_v2_1_Model *a_ptFisheyeModel,
FLOAT64 *a_ptM33,
INT32 a_lOriImgYLimit, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
UINT8 *a_pucSBVBuffer
);

/* 
\brief Calculate perspective transform of the current camera by feature points (校正十字定位點).  
This function will generate a matrix map dest to src
\param  peSrcX [IN] The feature points on source image - X (in pixel).
\param  peSrcY [IN] The feature points on source image - Y (in pixel).
\param  peDestX [IN] The feature points on destination image - X (in pixel).
\param  peDestY [IN] The feature points on destination image - Y (in pixel).
\param  ucNumPts [IN] The number of feature points.
\param  pePTMatrix [OUT] The buffer to store the generated planar transform matrix.
*/
BOOL COMMONK_GenerateM3x3(
	FLOAT64 * peSrcX, FLOAT64 * peSrcY, 
	FLOAT64 * peDestX, FLOAT64 * peDestY, 
	UINT8 ucNumPts, 
	FLOAT64 * pePTMatrix
);


/**
\brief SBV Generating by CFG(2211).
\param a_ptBVImgSize [IN] BV Img Size
\param a_tROI [IN] Detect ROI
\param a_pucSrcBuffer [IN] source Buffer of camera (YUYV INPUT)
\param a_ptFisheyeModel [IN] Fisheye Model
\param a_ptM33 [IN] transform matrix (BV to Src >> [0])
\param a_lOriImgYLimit [IN] Define the y position limitation to avoid the overflow
\param a_lCamAngle [IN] Define the y position limitation to avoid the overflow
\param a_lCamPosX [IN] Define the y position limitation to avoid the overflow
\param a_lCamPosY [IN] Define the y position limitation to avoid the overflow
\param a_lOffsetX [IN] SBV X offset
\param a_lOffsetY [IN] SBV Y offset
\param a_eSBVScale [IN] source Buffer of camera
\param a_eMMPP [IN] mmpp
\param a_pucSBVBuffer [OUT] Single BirdView Buffer (only Y Channal)
*/
void	COMMONK_SBVGeneratingK_YUYV2Y(
    alPointINT32 *a_ptBVImgSize,
	alRectINT32 a_tROI,
	UINT8 *a_pucSrcBuffer,
    alFM_v2_1_Model *a_ptFisheyeModel,
	FLOAT64 *a_ptM33,
	INT32 a_lOriImgYLimit, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
	INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
	UINT8 *a_pucSBVBuffer
	);

void	COMMONK_InterceptPointCal_ByVector(
	FLOAT64 a_eSX0, FLOAT64 a_eSY0, FLOAT64 a_eEX0, FLOAT64 a_eEY0,
	FLOAT64 a_eSX1, FLOAT64 a_eSY1, FLOAT64 a_eEX1, FLOAT64 a_eEY1,
	FLOAT64 *a_pePx, FLOAT64 *a_pePy
	);


/**
\brief To Generate Single View Planar Image for YUYV format.
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
void COMMONK_SBVGenerate_YUYV_FULL(
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    FLOAT64 a_peM33[9],
    INT32 a_lOriImgYLimit, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
    INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
    alFM_v2_1_Model *a_ptCameraFisheyeModel
    );

void COMMONK_UndistortedImageGenerate_YUYV_FULL(
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    alFM_v2_1_Model *a_ptCameraFisheyeModel
    );

void COMMONK_DistortedImageGenerate_YUYV_FULL(
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    alFM_v2_1_Model *a_ptCameraFisheyeModel
    );



/** 
\brief Transfer Feature Point ideal coordinate From Pixel to mm
\param a_lBVCenter_X [IN] Bird View Center X
\param a_lBVCenter_Y [IN] Bird View Center X
\param a_peFPIdealCoordOnImage_X [IN] Feature Point ideal coordinate x(pixel)
\param a_peFPIdealCoordOnImage_Y [IN] Feature Point ideal coordinate y(pixel)
\param a_ucNumPts [IN] number of point
\param a_fBirdViewMMPP [IN] mm per pixel on world model(BV)
\param a_peFPIdealCoordInWorld_X [OUT] Feature Point Ideal coordinate x in the real world(mm)
\param a_peFPIdealCoordInWorld_Y [OUT] Feature Point Ideal coordinate y in the real world(mm)
\return Function return false if the initialization is failed.
*/
BOOL COMMONK_TransferFPFromPixel2mm(
    const INT32 a_lBVCenter_X,
    const INT32 a_lBVCenter_Y,
    const FLOAT64 *a_peFPIdealCoordOnImage_X,
    const FLOAT64 *a_peFPIdealCoordOnImage_Y,
    const UINT8 a_ucNumPts,
    const FLOAT32 a_fBirdViewMMPP,
    FLOAT64 *a_peFPIdealCoordInWorld_X,
    FLOAT64 *a_peFPIdealCoordInWorld_Y
    );

/**
\brief Transfer Selected Feature Point of TopView to Undistorted Real Cam's point
\param a_peSelectedFP_X [IN] Feature Point's x in top view
\param a_peSelectedFP_Y [IN] Feature Point's y in top view
\param a_ucNumPts [IN] number of point
\param a_aeCurrentHomographyMatrix [IN] Current Homography Matrix
\param a_ptFisheyeModel_v2 [IN] Fisheye Model version 2(sphere) it include FocalLength and u0 v0
\param a_peFP_RealCamUndistorX [OUT] Undistorted Feature Point's x of real cam(mm)
\param a_peFP_RealCamUndistorY [OUT] Undistorted Feature Point's y of real cam(mm)
\return Function return false if the initialization is failed.
*/
BOOL COMMONK_TransferBVFPtoUndistorRealCam(
    const FLOAT64 *a_peSelectedFP_X,
    const FLOAT64 *a_peSelectedFP_Y,
    const UINT8 a_ucNumPts,
    const FLOAT64 a_aeCurrentHomographyMatrix[9],
    const alFM_v2_1_Model *a_ptFisheyeModel_v2,
    FLOAT64 *a_peFP_RealCamUndistorX,
    FLOAT64 *a_peFP_RealCamUndistorY
    );

/**
\brief Determine the RT Matrix
\param a_aeDesignIntrinsicMatrix [IN] Design Intrinsic Matrix
\param a_peHomographyMatrix [IN] Homography matrix by feature points pair
\param a_aeRTMatrix_RealCamtoBV [OUT] RT Matrix form real cam to bird view.
\param a_aeRTMatrix_BVtoRealCam [OUT] RT Matrix form bird view to real cam.
\return Function return false if the initialization is failed.
*/
BOOL COMMONK_DetermineRTMatrix(
    const FLOAT64 a_aeDesignIntrinsicMatrix[9],
    const FLOAT64 *a_peHomographyMatrix,
    FLOAT64 a_aeRTMatrix_RealCamtoBV[16],
    FLOAT64 a_aeRTMatrix_BVtoRealCam[16]
    );

/**
\brief Determine the yaw roll pitch Angle & camera position
\param a_lCAMID [IN] Camera ID
\param a_aeRTMatrix_RealCamtoBV [IN] RT Matrix form real cam to bird view.
\param a_aeRTMatrix_BVtoRealCam [IN] RT Matrix form bird view to real cam.
\param a_ptExtrinsicParameter [OUT]
yaw roll pitch angle & X Y Z position & image width, height
\return Function return false if the initialization is failed.
*/
BOOL COMMONK_DetermineExtrinsicParameter(
    const INT32 a_lCAMID,
    const FLOAT64 a_aeRTMatrix_RealCamtoBV[16],
    const FLOAT64 a_aeRTMatrix_BVtoRealCam[16],
    alCAMERAINFO_ExtrinsicParams *a_ptExtrinsicParameter
    );

/**
\brief
get Extrinsic Matrix of single camera by Calibration
\param a_lCAMID 
[IN] Camera ID
\param a_lBVCenter_X
[IN] Bird View Center X
\param a_lBVCenter_Y
[IN] Bird View Center X
\param a_peSelectedFP_X
[IN] Feature Point's x in top view
\param a_peSelectedFP_Y
[IN] Feature Point's y in top view
\param a_peIdealFP_X
[IN] Feature Point Ideal x position on birdview image plane(pixel)
\param a_peIdealFP_Y
[IN] Feature Point Ideal y position on birdview image plane(pixel)
\param a_ucNumPts
[IN] number of point
\param a_aeCurrentHomographyMatrix
[IN] Current Homography Matrix
\param a_ptFisheyeModel_v2
[IN] Fisheye Model version 2(sphere) it include FocalLength and u0 v0
\param a_ptFisheyeModel_v1
[IN] Fisheye Model version 1(planar and pixel based)
\param a_fBirdsViewMMPP
[IN] BirdsView's mm per Pixel
\param a_afOffset
[IN] offset of angle and position (0: Pitch 1:Yaw 2:Row 3: X 4: Y 5: Z)
\param a_lLMBoundarySwitch
[IN] LM Boundary Switch  0: OFF 1: ON
\param a_ptExtrinsicParameter
[OUT] yaw roll pitch angle & X Y Z position & image width, height
\param a_ptCalibrationParameter
[OUT] matrix of calibration
\return Function return false if the initialization is failed.
*/
BOOL COMMONK_RT_Calculation(
    const INT32 a_lCAMID,
    const INT32 a_lBVCenter_X,
    const INT32 a_lBVCenter_Y,
    const FLOAT64 *a_peSelectedFP_X,
    const FLOAT64 *a_peSelectedFP_Y,
    const FLOAT64 *a_peIdealFP_X,
    const FLOAT64 *a_peIdealFP_Y,
    const UINT8 a_ucNumPts,
    const FLOAT64 a_aeCurrentHomographyMatrix[9],
    const alFM_v2_1_Model *a_ptFisheyeModel_v2,
    const FLOAT32 a_fBirdsViewMMPP,
    FLOAT32 a_afOffset[6],
    INT32 a_lLMBoundarySwitch,
    alCAMERAINFO_ExtrinsicParams *a_ptExtrinsicParameter,
    alCOMMONK_CalibrationParams *a_ptCalibrationParameter
    );




#ifdef __cplusplus
}
#endif

/**
*  @}
*/
