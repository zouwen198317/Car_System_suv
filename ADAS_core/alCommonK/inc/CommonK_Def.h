
#pragma once

#include "mtype.h"
#include "atype.h"
#include "alCameraInfo.h"
#include "basedef.h"


////
/** \brief This default setting is used for MV_MC demo car - for sanyi calibration field. These setting are not included in ECU config files. */
#define SIM_DEFAULT_CAR_MODEL                       1 // EAGLEK3_CAR_MODEL_MV_MC_DEMO = 1
#define SIM_DEFAULT_CAR_MODEL_NAME                  "MV_MC"

/** \brief Common Configuration */
#define SIM_DEFAULT_DISPLAY_START_POINT_X 	        0				   
#define SIM_DEFAULT_DISPLAY_START_POINT_Y 	        0				   
#define SIM_DEFAULT_DISPLAY_IMAGE_WIDTH   	        720				   
#define SIM_DEFAULT_DISPLAY_IMAGE_HEIGHT  	        480				   
#define SIM_DEFAULT_DISPLAY_RATIO                   1.777778f   //(16.f/9.f)
#define SIM_DEFAULT_FM_MODEL_VERSION                1           // 1: ver.1, 2: ver.2
#define SIM_DEFAULT_FACTORY_AUTOK_SWITCH            0           // 1: ON	0: OFF

/* The following car parameters are retrieve from customers. */
#define SIM_DEFAULT_CAR_LEN  		                4862        // 車輛長度(mm)				   
#define SIM_DEFAULT_CAR_WID  		                1840    	// 車輛寬度(mm) - 車輪外側距離
#define SIM_DEFAULT_CAR_MAX_STEER_ANGLE             720	        // 方向盤最大舵角(mm)				   
#define SIM_DEFAULT_CAR_FWLE2HEAD_DISTANCE          567         // 前輪前緣到車頭距離
#define SIM_DEFAULT_CAR_FW2HEAD_DISTANCE            936         // 前輪軸心到車頭距離
#define SIM_DEFAULT_CAR_BW2TAIL_DISTANCE            1016        // 後輪軸心到車尾距離
#define SIM_DEFAULT_CAR_FW_AXLE_WIDTH               1605        // 前輪軸寬
#define SIM_DEFAULT_CAR_BW_AXLE_WIDTH               1605        // 後輪軸寬
#define SIM_DEFAULT_CAR_FBW_AXLE_DISTANCE           2910        // 前後輪軸距
#define SIM_DEFAULT_CAR_FFP2HEAD_DISTANCE           (SIM_DEFAULT_CAR_FW2HEAD_DISTANCE)         // 前輪兩定位點中線到車頭距離
//#define SIM_DEFAULT_CAR_CEN2LEFTMIRROR_DISTANCE     1105      // 車輛中心線到左後視鏡距離
//#define SIM_DEFAULT_CAR_CEN2RIGHTMIRROR_DISTANCE    1081      // 車輛中心線到右後視鏡距離

/////

#define COMMONK_Else_WorkingBufferSize (1280000) // 400*400*8

/** \brief Define the maximum buffer area size (X) of image (birdview/alleyview) output. */
#define     COMMONK_MAX_DISPLAY_AREA_SIZE_X        1280 // (720)
/** \brief Define the maximum buffer area size (Y) of image (birdview/alleyview) output. */
#define     COMMONK_MAX_DISPLAY_AREA_SIZE_Y         720 //(480)

/** \brief M33 element number. */
#define     COMMONK_M33_ELEMENT_CNT         (9)

/** \brief bird view channel number */
#define     COMMONK_NUM_BV_CHANNEL         (4)

/** \brief MAX camera number number */
#define     COMMONK_MAX_CAMERA_NUM         (7)

/** \brief bird view channel number */
#define     COMMONK_MAX_FEATURE_NUMBER         (20)

/** \brief Manual K FP number for each view */
#define COMMONK_MANUALK_CAMERA_FP_NUM (4)

/** \brief LM Switch 0: OFF 1: ON */
#define COMMONK_VERIFY_CALIBRATION_LM 0

/**
*  \addtogroup alCOMMONK
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif


/** \brief Define data element of LM. */
typedef struct
{
    /** \brief point number */
    INT32           lPointNum;

    /** \brief point number */
    INT32           lParameterNum;

    /** \brief Camera Position X (data input)  */
    FLOAT64           aeCameraPosX[COMMONK_MANUALK_CAMERA_FP_NUM];

    /** \brief Camera Position Y (data input)  */
    FLOAT64           aeCameraPosY[COMMONK_MANUALK_CAMERA_FP_NUM];

    /** \brief Word Position X (data input)  */
    FLOAT64           aeWordPosX[COMMONK_MANUALK_CAMERA_FP_NUM];

    /** \brief Word Position Y (data input)  */
    FLOAT64           aeWordPosY[COMMONK_MANUALK_CAMERA_FP_NUM];

    /** \brief Error  */
    FLOAT64           aeError[COMMONK_MANUALK_CAMERA_FP_NUM];

    /** \brief Intrinsic matrix  */
    FLOAT64           aeIntrinsic[9];

    /** \brief Intrinsic matrix  */
    INT32           lViewNum;
} alCOMMONK_LM_Struct;

/** \brief Define the common cfg data from ECU. */
typedef struct
{
    /** \brief Indicate the car model. */
    UINT32          ulCarModel;
    /** \brief Display width/height of LCD pannel. (in pixel) 顯示器可顯示的長寬尺寸 */
    alPointINT32   tDisplayAreaSize;
    /** \brief Display start point (x, y) on LCD pannel. (in pixel) 顯示器顯示的起始點位置 */
    alPointINT32   tDisplayStartPoint;
    /** \brief Width/Height ratio on LCD pannel 顯示器顯示的長寬比 : ex. = 16/9 for 16:9 的螢幕 */
    FLOAT32         fLCDRatio;
    /** \brief Inidicate the fisheye model version. 1: ver.1, 2: ver.2 */
    UINT8           ucFisheyeModelVersion;
    /** \brief The current car length */
    UINT32          ulCarLength;
    /** \brief The current car width */
    UINT32          ulCarWidth;
    /** \brief The maximum steering angle of this car. */
    UINT32          ulMaxSteeringAngle;
    /** \brief The maximum wheels axle width of this car. 輪軸寬 */
    UINT32          ulFrontWheelAxleWidth;
    /** \brief The maximum wheels axle width of this car. 輪軸寬 */
    UINT32          ulRearWheelAxleWidth;
    /** \brief The wheels axle distance of this car. 輪軸距*/
    UINT32          ulWheelAxleDistance;
    /** \brief The rear wheels axle distance to car head. 前輪軸心至車頭距離 */
    UINT32          ulFrontWheelAxle2Head;
    /** \brief The rear wheels axle distance to car tail. 後輪軸心至車尾距離 */
    UINT32          ulRearWheelAxle2Tail;
    /** \brief The front fixed point (固定校正場地的前輪定位點) distance to car head. 前輪定位點至車頭距離 */
    UINT32          ulFrontFixedPoint2Head;
    /** \brief The front wheel LE to car head. 前輪前緣至車頭距離 */
    UINT32          ulFrontWheelLE2Head;
    /** \brief 方向盤舵角與車輛轉向角關係式 φ= a * θ + b 之參數 a */
    FLOAT32         fSteerParamA;
    /** \brief 方向盤舵角與車輛轉向角關係式 φ= a * θ + b 之參數 b */
    FLOAT32         fSteerParamB;
} alCOMMONK_CommonCfg;

typedef struct
{
    /** \brief Camera Intrinsic Matrix */
    FLOAT64         aeIntrinsicMatrix[9];

    /** \brief Camera Rotation Matrix : (0:BV2CAM  1:CAM2BV) */
    FLOAT64         aeRotationMatrix[2][9];

    /** \brief Camera Translation Matrix : (0:BV2CAM  1:CAM2BV) */
    FLOAT64         aeTranslationMatrix[2][3];

    /** \brief Camera Homography Matrix : (0:BV2CAM  1:CAM2BV) */
    FLOAT64         aeHomographyMatrix[2][9];
} alCOMMONK_CalibrationParams;


/**
\brief Import Common Cfg data  by INI file.
\param a_pwcConfigFilePath [IN] file path
\param a_ptCommonCfg [INOUT] Configure data.
\return None.
*/
void COMMONK_CfgImportByINI(wchar_t * a_pwcConfigFilePath, alCOMMONK_CommonCfg *a_ptCommonCfg);

/** \brief To load the Common default setting from .h files. */
void COMMONK_LoadDefault(alCOMMONK_CommonCfg *a_ptalCOMMONK_CommonCfg);

/**
\brief Import Common Cfg data.
\param a_ulDataID [IN] ID of the current data.
\param a_ulDataLength [IN] Data length of the current data.
\param a_pucDataBuf [IN] Buffer array of the current data.
\param a_ptCfg [INOUT] Configure data.
\return None.
*/
void COMMONK_CommonCfgImportByHexData(
    UINT32 a_ulDataID, UINT32 a_ulDataLength, 
    UINT8 * a_pucDataBuf, alCOMMONK_CommonCfg *a_ptCfg
);

/**
\brief Export Common Cfg data.
\param a_ulDataID [IN] ID of the current data.
\param a_ulDataLength [IN] Data length of the current data.
\param a_pucDataBuf [IN] Buffer array of the current data.
\param a_ptCfg [INOUT] Configure data.
\return Total Size.
*/
UINT32 COMMONK_CommonCfgExportByHexData(
    UINT32 a_ulSectionID,
    alCOMMONK_CommonCfg *a_ptCommonCfg,
    UINT8 *a_pucDataSectionBuffer
);



#ifdef __cplusplus
}
#endif

/**
*  @}
*/
