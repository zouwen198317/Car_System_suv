
#pragma once

#include "mtype.h"
#include "alFM_v2_1.h"
#include "alCameraInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief Camera Configuration */
#define SIM_DEFAULT_CAM_WIDTH_BV_FRONT              720
#define SIM_DEFAULT_CAM_HEIGHT_BV_FRONT             480

#define SIM_DEFAULT_CAM_WIDTH_BV_BACK               720
#define SIM_DEFAULT_CAM_HEIGHT_BV_BACK              480

#define SIM_DEFAULT_CAM_WIDTH_BV_LEFT               720
#define SIM_DEFAULT_CAM_HEIGHT_BV_LEFT              480

#define SIM_DEFAULT_CAM_WIDTH_BV_RIGHT              720
#define SIM_DEFAULT_CAM_HEIGHT_BV_RIGHT             480


/*
\brief   The display scale & offset factors of single planar view. When the calibration UI called CAMK_GenerateSingleViewPlanarImage_YUYV
or CAMK_GenerateSingleViewPlanarImage_RGB function, the planar image y position will be scale & offset by this value. Thus
the coordinates of selected feature points should be offset back too. (in pixel)
*/
#define SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_FRONT     720
#define SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_FRONT    480
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_FRONT        2.5f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_FRONT      0
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_FRONT      -150 // -100
#define SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_BACK      720
#define SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_BACK     480
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_BACK         2.5f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_BACK       0
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_BACK       200 // (100)
#define SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_LEFT      720
#define SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_LEFT     480
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_LEFT         1.6f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_LEFT       -100
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_LEFT       0 // 60
#define SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_RIGHT     720
#define SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_RIGHT    480
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_RIGHT        1.6f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_RIGHT      100
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_RIGHT      0 // 60

/**
  *  \defgroup CameraCal Camera Calibration
  *  This module provides data structure and function for bird view camera calibration.
  *  @{
  */

/** \brief Define the mode of feature points for manual K 0: old  1: new. */
#define     EAGLEK3_MANUALK_FP_MODE 1

/** \brief Define the maximum distance to be valided for BV image, in mm. (用於避免查原影像時，因overflow而查到地平線以上的座標) */
#define     alMANUALK_FAREST_DISTANCE_SEARCH_FROM      10000    
#define     alMANUALK_FAREST_DISTANCE_SEARCH_END      100000    
#define     alMANUALK_FAREST_DISTANCE_SEARCH_STEP      10000 

#define alMANUALK_NUM_BV_CHANNEL 4
#define alMANUALK_CAMERA_FP_NUM 4
#define alMANUALK_CAMERA_FP_NUM_AUTOK 8

/** \brief Define configuration params for single planar points and bird view points transform. */
typedef struct
{
    /** \brief The scale factor of single planar image. */
    FLOAT32         fScaleFactor;
    /** \brief The display offset of single planar image - X. */
    INT32           lDisplayOffset_X;
    /** \brief The display offset of single planar image - Y. */
    INT32           lDisplayOffset_Y;
    /** \brief The display area size - Width. */
    INT32           lImageWidth;
    /** \brief The display area size - Height. */
    INT32           lImageHeight;

} alMANUALK_SPPvsBVPPCfg;

/** \brief Define configuration data of a single camera. */
typedef struct 
{

    /** \brief Image Width (in pixel) */
    UINT32          ulImageWidth;       
    /** \brief Image Height (in pixel) */
    UINT32          ulImageHeight;     

    /** \brief SBV Setting */
    alMANUALK_SPPvsBVPPCfg tSBV_Setting;

#if 0
	/** \brief Pitch angle offset (in degree) 相機角度的誤差*/
    FLOAT32         fPitchOffset;        
    /** \brief Yaw angle offset (in degree) 相機角度的誤差*/
    FLOAT32         fYawOffset;            
    /** \brief Roll angle offset (in degree) 相機角度的誤差*/
    FLOAT32         fRollOffset;           
    /** \brief Camera Position X offset (in milimeter) : according to center of car center on the ground 相機位置的誤差*/
    INT32           lCameraPosXOffset;           
    /** \brief Camera Position Y offset (in milimeter) : according to center of car center on the ground  相機位置的誤差*/
    INT32           lCameraPosYOffset;           
    /** \brief Camera Position Z offset (in milimeter) : according to center of car center on the ground 相機位置的誤差*/
    INT32           lCameraPosZOffset;     
	/** \brief LM Switch */
	INT32           lLMBoundarySwitch;
#endif
} alMANUALK_CameraCfg;



/** \brief Define configuration data of a single camera. */
typedef struct
{
    /** \brief mm per pixel */
    FLOAT32                     fMMPP;

    /** \brief Define the world four feature points of each view. These are the ideal position of feature points - X. */
    FLOAT64                     aeBVIdealFP_X[alMANUALK_NUM_BV_CHANNEL][alMANUALK_CAMERA_FP_NUM];
    /** \brief Define the world four feature points of each view. These are the ideal position of feature points - Y. */
    FLOAT64                     aeBVIdealFP_Y[alMANUALK_NUM_BV_CHANNEL][alMANUALK_CAMERA_FP_NUM];

    /** \brief Define the fine-tuned world four feature points of each view. These are the ideal position of feature points - X. */
    FLOAT64                     aeBVFineTunedIdealFP_X[alMANUALK_NUM_BV_CHANNEL][alMANUALK_CAMERA_FP_NUM];
    /** \brief Define the fine-tuned world four feature points of each view. These are the ideal position of feature points - Y. */
    FLOAT64                     aeBVFineTunedIdealFP_Y[alMANUALK_NUM_BV_CHANNEL][alMANUALK_CAMERA_FP_NUM];

    /** \brief Define the y position limitation to avoid the overflow of calculate BV to original image coordinates. */
    INT32                       alOriImgYLimit[alMANUALK_NUM_BV_CHANNEL];

    /** \brief Rotation angle on BV. */
    INT32                       alCamAngle[alMANUALK_NUM_BV_CHANNEL];

    /** \brief FishEye Model for BV. */
    alFM_v2_1_Model *a_aptFM_v2_Model[alMANUALK_NUM_BV_CHANNEL];
} alMANUALK_Params;



/** \brief The cross point position of chart. */
typedef struct
{
    /** \brief 校正場前輪定位點至前方Chart距離 */
    UINT16 uwFWheeltoFChart;
    /** \brief 校正場左右校正Chart的間隔 */
    UINT16 uwChartHoriDistance;
    /** \brief 校正場前後校正Chart的間隔 */
    UINT16 uwCharVertDistance;

    UINT16 FW1;
    UINT16 FH1;
    UINT16 FW2;
    UINT16 FH2;
    UINT16 FW3;
    UINT16 FH3;
    UINT16 FW4;
    UINT16 FH4;
    UINT16 FW5;
    UINT16 FH5;
    UINT16 FW6;
    UINT16 FH6;
    UINT16 BW1;
    UINT16 BH1;
    UINT16 BW2;
    UINT16 BH2;
    UINT16 BW3;
    UINT16 BH3;
    UINT16 BW4;
    UINT16 BH4;
    UINT16 BW5;
    UINT16 BH5;
    UINT16 BW6;
    UINT16 BH6;
	UINT16 BW7;
	UINT16 BH7;
	UINT16 BW8;
	UINT16 BH8;
  
} alMANUALK_ChartCrossPointSet;

/**
  *  \defgroup CameraCal Camera Calibration
  *  This module provides data structure and function for LM Algorithm.
  *  @{
  */

/** \brief Define data element of LM. */
typedef struct 
{
    /** \brief point number */
    INT32           lPointNum;  

	/** \brief point number */
    INT32           lParameterNum;  

    /** \brief Camera Position X (data input)  */
    FLOAT64           aeCameraPosX[alMANUALK_CAMERA_FP_NUM];  

	/** \brief Camera Position Y (data input)  */
    FLOAT64           aeCameraPosY[alMANUALK_CAMERA_FP_NUM];  

	/** \brief Word Position X (data input)  */
    FLOAT64           aeWordPosX[alMANUALK_CAMERA_FP_NUM];

	/** \brief Word Position Y (data input)  */
    FLOAT64           aeWordPosY[alMANUALK_CAMERA_FP_NUM];

	/** \brief Error  */
    FLOAT64           aeError[alMANUALK_CAMERA_FP_NUM];

	/** \brief Intrinsic matrix  */
    FLOAT64           aeIntrinsic[9];

	/** \brief Intrinsic matrix  */
    INT32           lViewNum;
} alMANUALK_LM_Struct;


/** \brief Load Default Setting for CAMK. */
void MANUALK_LoadDefault(alMANUALK_CameraCfg  a_atMANUALK_Cfg[alMANUALK_NUM_BV_CHANNEL]);


void MANUALK_CfgImport(wchar_t * a_pwcConfigFilePath, alMANUALK_CameraCfg *a_ptMANUALKCfg);


UINT32 MANUALK_CfgExportHex(
    UINT32 a_ulSectionID,
    alMANUALK_CameraCfg *a_ptCfg,
    UINT8 *a_pucDataSectionBuffer
    );

/**
\brief Cfg Import by Hex file
\param a_ulDataID [IN] Data ID
\param a_ulDataLength [IN] Data Length
\param a_pulBuffer [IN] Data Section Buffer for reading
*/
void MANUALK_CfgImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, alMANUALK_CameraCfg *a_ptCfg);

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
