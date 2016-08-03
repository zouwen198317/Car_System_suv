
#pragma once

#include "mtype.h"
#include "atype.h"
#include "alPartLUT_v1_Def.h"
#include "alFM_v2_1.h"


/**
*  \defgroup alALLEYVIEW    alAlleyView
*  This module provides data structure and function for alley view look-up table construction.
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

    /** Full Alley View Configuration
    Alley Window__Crop 8 points = {X1 X2 X3 X4 Y1 Y2 Y3 Y4 X5 X6 X7 X8 Y5 Y6 Y7 Y8}
    依序是 Left Window 左上左下右上右下 -> Right Window 左上左下右上右下
    (0,0) ->  ________________________________
    |                                |
    |  1---------3    5----------7   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |       __4    6__        |   |
    |  |  ////            \\\\   |   |
    |  8                         8   |
    |                                |
    |________________________________|                                     */

    /** \brief FAV - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_FAV_FUNCTION_ENABLED          1      
    /** \brief FAV 顯示區在 Buffer 的起始位置 - X */
#define SIM_DEFAULT_FAV_START_POINT_X                   0 
    /** \brief FAV 顯示區在 Buffer 的起始位置 - Y */
#define SIM_DEFAULT_FAV_START_POINT_Y                   0
    /** \brief FAV 顯示區的寬度 */
#define SIM_DEFAULT_FAV_AREA_SIZE_WIDTH                 720
    /** \brief FAV 顯示區的高度 */
#define SIM_DEFAULT_FAV_AREA_SIZE_HEIGHT                480
    /** \brief FAV 水平視角 : 右側，左側為對稱 (負值) */
#define SIM_DEFAULT_FAV_VIEWING_ANGLE                   60
    /** \brief FAV 畫面水平 FOV : 單側 */
#define SIM_DEFAULT_FAV_HORI_FOV                        56
    /** \brief FAV 畫面偏移 X */
#define SIM_DEFAULT_FAV_DISPLAY_OFFSET_X                0
    /** \brief FAV 畫面偏移 Y */
#define SIM_DEFAULT_FAV_DISPLAY_OFFSET_Y                -85 
    /** \brief FAV 潤邊像素 (pixel) */
#define SIM_DEFAULT_FAV_DISPLAY_SMOOTH                  6 
    /** \brief FAV 裁接點座標 (#0) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_0_X               0 
    /** \brief FAV 裁接點座標 (#0) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_0_Y               0 
    /** \brief FAV 裁接點座標 (#1) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_1_X               0
    /** \brief FAV 裁接點座標 (#1) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_1_Y               374 
    /** \brief FAV 裁接點座標 (#2) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_2_X               342
    /** \brief FAV 裁接點座標 (#2) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_2_Y               0 
    /** \brief FAV 裁接點座標 (#3) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_3_X               342
    /** \brief FAV 裁接點座標 (#3) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_3_Y               326 
    /** \brief FAV 裁接點座標 (#4) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_4_X               378
    /** \brief FAV 裁接點座標 (#4) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_4_Y               0 
    /** \brief FAV 裁接點座標 (#5) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_5_X               378
    /** \brief FAV 裁接點座標 (#5) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_5_Y               326 
    /** \brief FAV 裁接點座標 (#6) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_6_X               720 
    /** \brief FAV 裁接點座標 (#6) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_6_Y               0 
    /** \brief FAV 裁接點座標 (#7) - X */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_7_X               720
    /** \brief FAV 裁接點座標 (#7) - Y */
#define SIM_DEFAULT_FAV_DISPLAY_POINT_7_Y               374 

    /** Front Side View Parameters: FLV (front-left), FRV (front-right) */
    /** \brief FLV - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_FLV_FUNCTION_ENABLED          1      
    /** \brief FLV Start Point (影像在 Buffer 的啟始位置) - X */
#define SIM_DEFAULT_FLV_START_POINT_X                   0          
    /** \brief FLV Start Point (影像在 Buffer 的啟始位置) - Y */
#define SIM_DEFAULT_FLV_START_POINT_Y                   0          
    /** \brief FLV Area Size - X */
#define SIM_DEFAULT_FLV_AREA_SIZE_X                     310         
    /** \brief FLV Area Size - Y */
#define SIM_DEFAULT_FLV_AREA_SIZE_Y                     334        
    /** \brief FLV Center Point (中心在原影像的位置) - X */
#define SIM_DEFAULT_FLV_CENTER_X                        510
    /** \brief FLV Center Point (中心在原影像的位置) - Y */
#define SIM_DEFAULT_FLV_CENTER_Y                        256           
    /** \brief FLV Roation Angle (相對於原影像的旋轉角度) */
#define SIM_DEFAULT_FLV_ROTATION                        85            
    /** \brief FLV Scaling Ratio (相對於原影像) - X */
#define SIM_DEFAULT_FLV_SCALING_FACTOR_X                1.0
    /** \brief FLV Scaling Ratio (相對於原影像) - Y */
#define SIM_DEFAULT_FLV_SCALING_FACTOR_Y                1.0

    /** \brief FRV - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_FRV_FUNCTION_ENABLED          1      
    /** \brief FRV Start Point (影像在 Buffer 的啟始位置) - X */
#define SIM_DEFAULT_FRV_START_POINT_X                   0
    /** \brief FRV Start Point (影像在 Buffer 的啟始位置) - Y */
#define SIM_DEFAULT_FRV_START_POINT_Y                   0 
    /** \brief FRV Area Size - X */
#define SIM_DEFAULT_FRV_AREA_SIZE_X                     310
    /** \brief FRV Area Size - Y */
#define SIM_DEFAULT_FRV_AREA_SIZE_Y                     334
    /** \brief FRV Center Point (中心在原影像的位置) - X */
#define SIM_DEFAULT_FRV_CENTER_X                        210
    /** \brief FRV Center Point (中心在原影像的位置) - Y */
#define SIM_DEFAULT_FRV_CENTER_Y                        256
    /** \brief FRV Roation Angle (相對於原影像的旋轉角度) */
#define SIM_DEFAULT_FRV_ROTATION                        -85
    /** \brief FRV Scaling Ratio (相對於原影像) - X */
#define SIM_DEFAULT_FRV_SCALING_FACTOR_X                1.0
    /** \brief FRV Scaling Ratio (相對於原影像) - Y */
#define SIM_DEFAULT_FRV_SCALING_FACTOR_Y                1.0

    /*
    Alley Window__Crop 8 points
    依序是 Left Window 左上左下右上右下 -> Right Window 左上左下右上右下
    (0,0) ->  ________________________________
    |                                |
    |  0---------2    4----------6   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |         |    |          |   |
    |  |       __3    5__        |   |
    |  |  ////            \\\\   |   |
    |  1                         7   |
    |                                |
    |________________________________|                                     */

    /** \brief SAV - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_SAV_FUNCTION_ENABLED           1      
    /** \brief SAV 顯示區在 Buffer 的起始位置 - X */
#define SIM_DEFAULT_SAV_START_POINT_X                    0           
    /** \brief SAV 顯示區在 Buffer 的起始位置 - Y */
#define SIM_DEFAULT_SAV_START_POINT_Y                    0           
    /** \brief SAV 顯示區的寬度 */
#define SIM_DEFAULT_SAV_AREA_SIZE_WIDTH                  392        
    /** \brief SAV 顯示區的高度 */
#define SIM_DEFAULT_SAV_AREA_SIZE_HEIGHT                 334         
    /** \brief SAV 水平視角 : 右側，左側為對稱 (負值) */
#define SIM_DEFAULT_SAV_VIEWING_ANGLE                    60          
    /** \brief SAV 畫面水平 FOV : 單側 */
#define SIM_DEFAULT_SAV_HORI_FOV                         56          
    /** \brief SAV 畫面偏移 X */
#define SIM_DEFAULT_SAV_DISPLAY_OFFSET_X                 0           
    /** \brief SAV 畫面偏移 Y */
#define SIM_DEFAULT_SAV_DISPLAY_OFFSET_Y                 -90           
    /** \brief SAV 潤邊像素 (pixel) */
#define SIM_DEFAULT_SAV_DISPLAY_SMOOTH                   4           
    /** \brief SAV 裁接點座標 (#0) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_0_X                0             
    /** \brief SAV 裁接點座標 (#0) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_0_Y                0 
    /** \brief SAV 裁接點座標 (#1) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_1_X                0             
    /** \brief SAV 裁接點座標 (#1) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_1_Y                261 
    /** \brief SAV 裁接點座標 (#2) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_2_X                186           
    /** \brief SAV 裁接點座標 (#2) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_2_Y                0 
    /** \brief SAV 裁接點座標 (#3) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_3_X                186            
    /** \brief SAV 裁接點座標 (#3) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_3_Y                227 
    /** \brief SAV 裁接點座標 (#4) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_4_X                206 
    /** \brief SAV 裁接點座標 (#4) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_4_Y                0 
    /** \brief SAV 裁接點座標 (#5) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_5_X                206
    /** \brief SAV 裁接點座標 (#5) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_5_Y                227 
    /** \brief SAV 裁接點座標 (#6) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_6_X                392
    /** \brief SAV 裁接點座標 (#6) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_6_Y                0 
    /** \brief SAV 裁接點座標 (#7) - X */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_7_X                392
    /** \brief SAV 裁接點座標 (#7) - Y */
#define SIM_DEFAULT_SAV_DISPLAY_POINT_7_Y                261 


#define SIM_DEFAULT_ALM11_W2I                            (304.764629)
#define SIM_DEFAULT_ALM12_W2I                            (123.127528)
#define SIM_DEFAULT_ALM13_W2I                            (-11938.810276)
#define SIM_DEFAULT_ALM21_W2I                            (188.323027)
#define SIM_DEFAULT_ALM22_W2I                            (104.256471)
#define SIM_DEFAULT_ALM23_W2I                            (-6443.721462)
#define SIM_DEFAULT_ALM31_W2I                            (0.813799)
#define SIM_DEFAULT_ALM32_W2I                            (0.342021)
#define SIM_DEFAULT_ALM33_W2I                            (-19.490569)
#define SIM_DEFAULT_ALM11_I2W                            (0.001675)
#define SIM_DEFAULT_ALM12_I2W                            (-0.016408)
#define SIM_DEFAULT_ALM13_I2W                            (4.398420)
#define SIM_DEFAULT_ALM21_I2W                            (-0.015334)
#define SIM_DEFAULT_ALM22_I2W                            (0.036799)
#define SIM_DEFAULT_ALM23_I2W                            (-2.773113)
#define SIM_DEFAULT_ALM31_I2W                            (-0.000199)
#define SIM_DEFAULT_ALM32_I2W                            (-0.000039)
#define SIM_DEFAULT_ALM33_I2W                            (0.083680)

#define SIM_DEFAULT_ARM11_W2I                            (-281.170356)
#define SIM_DEFAULT_ARM12_W2I                            (123.127528)
#define SIM_DEFAULT_ARM13_W2I                            (53014.989977)
#define SIM_DEFAULT_ARM21_W2I                            (-188.323027)
#define SIM_DEFAULT_ARM22_W2I                            (104.256471)
#define SIM_DEFAULT_ARM23_W2I                            (30467.591748)
#define SIM_DEFAULT_ARM31_W2I                            (-0.813799)
#define SIM_DEFAULT_ARM32_W2I                            (0.342021)
#define SIM_DEFAULT_ARM33_W2I                            (140.013954)
#define SIM_DEFAULT_ARM11_I2W                            (0.040708)
#define SIM_DEFAULT_ARM12_I2W                            (0.008700)
#define SIM_DEFAULT_ARM13_I2W                            (-17.306769)
#define SIM_DEFAULT_ARM21_I2W                            (0.015334)
#define SIM_DEFAULT_ARM22_I2W                            (0.036799)
#define SIM_DEFAULT_ARM23_I2W                            (-13.813784)
#define SIM_DEFAULT_ARM31_I2W                            (0.000199)
#define SIM_DEFAULT_ARM32_I2W                            (-0.000039)
#define SIM_DEFAULT_ARM33_I2W                            (-0.059706)

#define SIM_DEFAULT_FALM11_W2I                            (304.764629)
#define SIM_DEFAULT_FALM12_W2I                            (123.127528)
#define SIM_DEFAULT_FALM13_W2I                            (-23599.443485)
#define SIM_DEFAULT_FALM21_W2I                            (188.323027)
#define SIM_DEFAULT_FALM22_W2I                            (104.256471)
#define SIM_DEFAULT_FALM23_W2I                            (-13250.316016)
#define SIM_DEFAULT_FALM31_W2I                            (0.813799)
#define SIM_DEFAULT_FALM32_W2I                            (0.342021)
#define SIM_DEFAULT_FALM33_W2I                            (-40.440717)
#define SIM_DEFAULT_FALM11_I2W                            (0.001675)
#define SIM_DEFAULT_FALM12_I2W                            (-0.016408)
#define SIM_DEFAULT_FALM13_I2W                            (4.398420)
#define SIM_DEFAULT_FALM21_I2W                            (-0.016806)
#define SIM_DEFAULT_FALM22_I2W                            (0.036508)
#define SIM_DEFAULT_FALM23_I2W                            (-2.154812)
#define SIM_DEFAULT_FALM31_I2W                            (-0.000108)
#define SIM_DEFAULT_FALM32_I2W                            (-0.000021)
#define SIM_DEFAULT_FALM33_I2W                            (0.045559)

#define SIM_DEFAULT_FARM11_W2I                            (-281.170356)
#define SIM_DEFAULT_FARM12_W2I                            (123.127528)
#define SIM_DEFAULT_FARM13_W2I                            (95703.454939)
#define SIM_DEFAULT_FARM21_W2I                            (-188.323027)
#define SIM_DEFAULT_FARM22_W2I                            (104.256471)
#define SIM_DEFAULT_FARM23_W2I                            (54545.973553)
#define SIM_DEFAULT_FARM31_W2I                            (-0.813799)
#define SIM_DEFAULT_FARM32_W2I                            (0.342021)
#define SIM_DEFAULT_FARM33_W2I                            (252.526775)
#define SIM_DEFAULT_FARM11_I2W                            (0.040708)
#define SIM_DEFAULT_FARM12_I2W                            (0.008700)
#define SIM_DEFAULT_FARM13_I2W                            (-17.306769)
#define SIM_DEFAULT_FARM21_I2W                            (0.016806)
#define SIM_DEFAULT_FARM22_I2W                            (0.036508)
#define SIM_DEFAULT_FARM23_I2W                            (-14.254943)
#define SIM_DEFAULT_FARM31_I2W                            (0.000108)
#define SIM_DEFAULT_FARM32_I2W                            (-0.000021)
#define SIM_DEFAULT_FARM33_I2W                            (-0.032506)



/** \brief Define the parameters structure for matrix generator.

side view:

destination plane
_
/\                                            | |               \ _
\/  real camera                               | |                |_|     virtual camera
______                                   =>              | |               /
\     \                                                  |_|
\     \   camera image plane
\_____\
top view:

destination plane
_
/ /
/ /
/ /
/_/        |

_  /\
\/   virtual camera

Definition:
1. Pitch Angle : 向上為正
2. Yaw Angle : 向右為正
3. Roll Angle : 順時針為正

*/
typedef struct
{
    /** \brief The width of the destination image plane. (in pixel) */
    UINT32  ulDestPlaneWidth;
    /** \brief The height of the destination image plane. (in pixel) */
    UINT32  ulDestPlaneHeight;
    /** \brief The width of the camera image plane. (in pixel) */
    UINT32  ulCameraPlaneWidth;
    /** \brief The height of the camera image plane. (in pixel) */
    UINT32  ulCameraPlaneHeight;

    /** \brief The calibrated rotation matrix of camera to world cooridnates. */
    FLOAT64 aeRotationMatrix[9];

    /** \brief The calibrated translation matrix of camera to world cooridnates. */
    //FLOAT64 aeTranslationMatrix[3];

    /** \brief The current pitch angle of the real camera. (in degree) */
    FLOAT64 eCameraPitchAngle;
    /** \brief The current yaw angle of the real camera. (in degree) */
    FLOAT64 eCameraYawAngle;
    /** \brief The current roll angle of the real camera. (in degree) */
    FLOAT64 eCameraRollAngle;

    /** \brief The horizontal FOV of the real camera. (in degree) */
    FLOAT64 eCameraFOV_H;

    // Define Rotation:
    /** \brief The designed destination pitch angle of the virtual camera. (in degree) */
    FLOAT64 eDestPitchAngle;
    /** \brief The designed destination yaw angle of the virtual camera. (in degree) */
    FLOAT64 eDestYawAngle;
    /** \brief The designed destination roll angle of the virtual camera. (in degree)  */
    FLOAT64 eDestRollAngle;

    // Define the origin offset (X, Y) of virtual camera on destination plane:
    /** \brief To design the origin offset (X) on destination plane. (in pixel)
    The original setting is on the center of the image plane. This value provide the X offset.
    */
    INT32 lDestPlaneOriginOffsetX;
    /** \brief To design the origin offset (Y) on destination plane. (in pixel)
    The original setting is on the center of the image plane. This value provide the Y offset.
    */
    INT32 lDestPlaneOriginOffsetY;

    /** \brief The FOV (H) desinged for destination plane. (in degree) */
    FLOAT64 eDestFOV_H;

    /** \brief The fisheye model mode to be used, 0: old with 2D, 1: new with 3D. */
    UINT8 ucFisheyeModelMode;

    /** \brief FishEye Model. */
    alFM_v2_1_Model *ptFM_v2_Model;

    /** \brief M33 of Alley View - only for small alley view, aeAVL[0] : WtoI, aeAVL[1] : ItoW */
    FLOAT64 aeAV[2][9];
} alAlleyViewParams;


/*
                        Alley View
    (0,0) ->  ________________________________
             |                                |
             |  0---------2    4----------6   |
             |  |         |    |          |   |
             |  |  left   |    |   right  |   |
             |  | alley   |    |   alley  |   |
             |  |  view   |    |    view  |   |
             |  |         |    |          |   |
             |  |         |    |          |   |
             |  |       __3    5__        |   |
             |  |  ////            \\\\   |   |
             |  1                         7   |
             |                                |
             |________________________________|                                     */

/** \brief Define alleyview cfg from ECU. */
typedef struct
{

    /** \brief Indicate if this function is enabled, 0: disabed, 1: enabled. */
    UINT8           ucFunctionEnabled;
    /** \brief Alley View Start Point on Buffer. */
    alPointINT32   tStartPoint;
    /** \brief Alley View Area Size. */
    alPointINT32   tAreaSize;
    /** \brief Viewing Angle of Right View. */
    FLOAT32         fViewingAngle;
    /** \brief FOV of Right View. */
    UINT32          ulFOV;
    /** \brief VC offset , X */
    INT32           lVCOffsetX;
    /** \brief VC offset , Y */
    INT32           lVCOffsetY;
    /** \brief Soft pixel */
    UINT32          ulSoftPixels;
    /** \brief Apex point */
    alPointINT32   aApexPoints[8];

} alALLEYVIEW_Cfg;

/** \brief Define parameters from Alley View fine tune. */
typedef struct
{

    /** \brief Alley View Fine Tune Yaw Offset. */
	FLOAT64 alley_yaw_offset;
	/** \brief Alley View Fine Tune Pitch Offset. */
	FLOAT64 alley_pitch_offset;
	/** \brief Alley View Fine Tune Roll Offset. */
	FLOAT64 alley_roll_offset;
	/** \brief Alley View Fine Tune Vertical Shift. */
	INT32 Y_shift;

} alALLEYVIEW_FineTuneParams;

/** \brief M33 matrix set for all cameras. */
typedef struct
{

    /** \brief M33 of Alley View Left - only for small alley view, aeAVL[0] : WtoI, aeAVL[1] : ItoW */
    FLOAT64 aeAVL[2][9];
    /** \brief M33 of Alley View Right - only for small alley view, aeAVR[0] : WtoI, aeAVR[1] : ItoW */
    FLOAT64 aeAVR[2][9];

} alALLEYVIEW_RMtxSet;

   
/**
\brief Cfg Import by Hex file (1300-2)
\param a_ulDataID [IN] Data ID
\param a_ulDataLength [IN] Data Length
\param a_pulBuffer [IN] Data Section Buffer for reading
*/
void AV_CfgImportHex(
    UINT32 a_ulDataID, 
    UINT32 a_ulDataLength, UINT8 * a_pucBuffer, 
    alALLEYVIEW_Cfg *a_ptCfg_S,
    alALLEYVIEW_Cfg *a_ptCfg_F
    );

/**
\brief Cfg Export to Hex file
\param a_ulSectionID [IN] Section ID
\param a_ptBVCAM_FACAUTOKCfg [IN] Alley View Config data
\param a_pucDataSectionBuffer [OUT] Data Section Buffer for output
*/
UINT32 AV_CfgExportHex(
    UINT32 a_ulSectionID,
    alALLEYVIEW_Cfg *a_ptCfg_S,
    alALLEYVIEW_Cfg *a_ptCfg_F,
    UINT8 *a_pucDataSectionBuffer
    );
	
/** \brief Query Working Buffer Size by configure. */
void AV_QueryWorkingBufferSize(alALLEYVIEW_Cfg * a_tAV_Cfg);
	
/** \brief Load default setting for Alley View. */
void alALLEYVIEW_LoadDefault(alALLEYVIEW_Cfg *a_tSAV_Cfg, alALLEYVIEW_Cfg *a_tFAV_Cfg);

/** \brief Load Cfg setting for Alley View by INI file. */
void alALLEYVIEW_CfgImportByINI(alALLEYVIEW_Cfg *a_tSAV_Cfg, alALLEYVIEW_Cfg *a_tFAV_Cfg, wchar_t *a_pwcConfigFilePath);

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
