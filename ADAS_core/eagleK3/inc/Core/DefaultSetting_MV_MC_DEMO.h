
#pragma once

/**
  *  \addtogroup Common
  *  @{
  */


/** \brief Camera Configuration */

/** \brief Front Top View 是否啟用 */
#define SIM_DEFAULT_TOP_VIEW_FRONT_FUNCTUIN_ENABLED             0
/** \brief Front Top View 顯示結果的旋轉角度 */
#define SIM_DEFAULT_TOP_VIEW_FRONT_ROTATION_DEGREE              0
/** \brief Front Top View 顯示結果是否要做 Mirror */
#define SIM_DEFAULT_TOP_VIEW_FRONT_MIRROR                       0
/** \brief Front Top View 顯示在 Buffer 上的起始位置- X */
#define SIM_DEFAULT_TOP_VIEW_FRONT_DISPLAY_START_POX_X          0
/** \brief Front Top View 顯示在 Buffer 上的起始位置- Y */
#define SIM_DEFAULT_TOP_VIEW_FRONT_DISPLAY_START_POX_Y          0
/** \brief Front Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_FRONT_DISPLAY_AREA_SIZE_X          392
/** \brief Front Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_FRONT_DISPLAY_AREA_SIZE_Y          334
/** \brief Front Top View 顯示的最近距離 (盲區距離) */
#define SIM_DEFAULT_TOP_VIEW_FRONT_DISPLAY_MIN_DISTANCE         150
/** \brief Front Top View 顯示的最遠距離 */
#define SIM_DEFAULT_TOP_VIEW_FRONT_DISPLAY_MAX_DISTANCE         2500

/** \brief Back Top View 是否啟用 */
#define SIM_DEFAULT_TOP_VIEW_BACK_FUNCTUIN_ENABLED             0
/** \brief Back Top View 顯示結果的旋轉角度 */
#define SIM_DEFAULT_TOP_VIEW_BACK_ROTATION_DEGREE              0
/** \brief Back Top View 顯示結果是否要做 Mirror */
#define SIM_DEFAULT_TOP_VIEW_BACK_MIRROR                       0
/** \brief Back Top View 顯示在 Buffer 上的起始位置- X */
#define SIM_DEFAULT_TOP_VIEW_BACK_DISPLAY_START_POX_X          0
/** \brief Back Top View 顯示在 Buffer 上的起始位置- Y */
#define SIM_DEFAULT_TOP_VIEW_BACK_DISPLAY_START_POX_Y          0
/** \brief Back Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_BACK_DISPLAY_AREA_SIZE_X          392
/** \brief Back Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_BACK_DISPLAY_AREA_SIZE_Y          334
/** \brief Back Top View 顯示的最近距離 (盲區距離) */
#define SIM_DEFAULT_TOP_VIEW_BACK_DISPLAY_MIN_DISTANCE         250
/** \brief Back Top View 顯示的最遠距離 */
#define SIM_DEFAULT_TOP_VIEW_BACK_DISPLAY_MAX_DISTANCE         2500

/** \brief Left Top View 是否啟用 */
#define SIM_DEFAULT_TOP_VIEW_LEFT_FUNCTUIN_ENABLED             0
/** \brief Left Top View 顯示結果的旋轉角度 */
#define SIM_DEFAULT_TOP_VIEW_LEFT_ROTATION_DEGREE              0
/** \brief Left Top View 顯示結果是否要做 Mirror */
#define SIM_DEFAULT_TOP_VIEW_LEFT_MIRROR                       0
/** \brief Left Top View 顯示在 Buffer 上的起始位置- X */
#define SIM_DEFAULT_TOP_VIEW_LEFT_DISPLAY_START_POX_X          0
/** \brief Left Top View 顯示在 Buffer 上的起始位置- Y */
#define SIM_DEFAULT_TOP_VIEW_LEFT_DISPLAY_START_POX_Y          0
/** \brief Left Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_LEFT_DISPLAY_AREA_SIZE_X          720
/** \brief Left Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_LEFT_DISPLAY_AREA_SIZE_Y          480
/** \brief Left Top View 顯示的最近距離 (盲區距離) */
#define SIM_DEFAULT_TOP_VIEW_LEFT_DISPLAY_MIN_DISTANCE         0
/** \brief Left Top View 顯示的最遠距離 */
#define SIM_DEFAULT_TOP_VIEW_LEFT_DISPLAY_MAX_DISTANCE         5000

/** \brief Right Top View 是否啟用 */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_FUNCTUIN_ENABLED             0
/** \brief Right Top View 顯示結果的旋轉角度 */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_ROTATION_DEGREE              0
/** \brief Right Top View 顯示結果是否要做 Mirror */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_MIRROR                       0
/** \brief Right Top View 顯示在 Buffer 上的起始位置- X */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_DISPLAY_START_POX_X          0
/** \brief Right Top View 顯示在 Buffer 上的起始位置- Y */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_DISPLAY_START_POX_Y          0
/** \brief Right Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_DISPLAY_AREA_SIZE_X          720
/** \brief Right Top View 顯示在 Buffer 上的寬度範圍 */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_DISPLAY_AREA_SIZE_Y          480
/** \brief Right Top View 顯示的最近距離 (盲區距離) */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_DISPLAY_MIN_DISTANCE         0
/** \brief Right Top View 顯示的最遠距離 */
#define SIM_DEFAULT_TOP_VIEW_RIGHT_DISPLAY_MAX_DISTANCE         5000

/* Normal Vew Configuration */
/** \brief Normal Vew Front - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_NV_FRONT_FUNCTION_ENABLED                   0      
/** \brief Normal Vew Front - 顯示型式 - 0: Crop Only,  1: Do-defisheye Only, 2: Do View Angle Correction */
#define SIM_DEFAULT_NV_FRONT_TYPE                               2       
/** \brief Normal Vew Front - 裁切的起始位置 - X */
#define SIM_DEFAULT_NV_FRONT_CROP_START_POS_X                   58       
/** \brief Normal Vew Front - 裁切的起始位置 - Y */
#define SIM_DEFAULT_NV_FRONT_CROP_START_POS_Y                   60        
/** \brief Normal Vew Front - 裁切的範圍大小 - X */
#define SIM_DEFAULT_NV_FRONT_CROP_AREA_SIZE_X                   604     
/** \brief Normal Vew Front - 裁切的範圍大小 - Y */
#define SIM_DEFAULT_NV_FRONT_CROP_AREA_SIZE_Y                   392       
/** \brief Normal Vew Front - 顯示的起始位置 - X */
#define SIM_DEFAULT_NV_FRONT_DISPLAY_START_POS_X                0         
/** \brief Normal Vew Front - 顯示的起始位置 - Y */
#define SIM_DEFAULT_NV_FRONT_DISPLAY_START_POS_Y                0         
/** \brief Normal Vew Front - 顯示的範圍大小 - X */
#define SIM_DEFAULT_NV_FRONT_DISPLAY_AREA_SIZE_X                392       
/** \brief Normal Vew Front - 顯示的範圍大小 - Y */
#define SIM_DEFAULT_NV_FRONT_DISPLAY_AREA_SIZE_Y                334       
/** \brief Normal Vew Front - 顯示圖的旋轉角度*/
#define SIM_DEFAULT_NV_FRONT_ROTATION_DEGREE                    0       
/** \brief Normal Vew Front - 顯示時是否做 mirror */
#define SIM_DEFAULT_NV_FRONT_MORRIR                             0         
/** \brief Normal Vew Front - 目標平面的原點位置 - X */
#define SIM_DEFAULT_NV_FRONT_PT_DEST_ORIGIN_POS_X               196         
/** \brief Normal Vew Front - 目標平面的原點位置 - Y */
#define SIM_DEFAULT_NV_FRONT_PT_DEST_ORIGIN_POS_Y               135         
/** \brief Normal Vew Front - 目標平面的 FOV (H) */
#define SIM_DEFAULT_NV_FRONT_PT_DEST_FOV_H                      135         
/** \brief Normal Vew Front - 目標平面的 Pitch Angle*/
#define SIM_DEFAULT_NV_FRONT_PT_DEST_PITCH                      (-10)         
/** \brief Normal Vew Front - 目標平面的 Yaw Angle*/
#define SIM_DEFAULT_NV_FRONT_PT_DEST_YAW                        0         
/** \brief Normal Vew Front - 目標平面的 Roll Angle*/
#define SIM_DEFAULT_NV_FRONT_PT_DEST_ROLL                       0         

/** \brief Normal Vew Back - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_NV_BACK_FUNCTION_ENABLED                    0      
/** \brief Normal Vew Back - 顯示型式 - 0: Crop Only,  1: Do-defisheye Only, 2: Do View Angle Correction */
#define SIM_DEFAULT_NV_BACK_TYPE                                2       
/** \brief Normal Vew Back - 裁切的起始位置 - X */
#define SIM_DEFAULT_NV_BACK_CROP_START_POS_X                    6       
/** \brief Normal Vew Back - 裁切的起始位置 - Y */
#define SIM_DEFAULT_NV_BACK_CROP_START_POS_Y                    0        
/** \brief Normal Vew Back - 裁切的範圍大小 - X */
#define SIM_DEFAULT_NV_BACK_CROP_AREA_SIZE_X                    708     
/** \brief Normal Vew Back - 裁切的範圍大小 - Y */
#define SIM_DEFAULT_NV_BACK_CROP_AREA_SIZE_Y                    426       
/** \brief Normal Vew Back - 顯示的起始位置 - X */
#define SIM_DEFAULT_NV_BACK_DISPLAY_START_POS_X                 0         
/** \brief Normal Vew Back - 顯示的起始位置 - Y */
#define SIM_DEFAULT_NV_BACK_DISPLAY_START_POS_Y                 0         
/** \brief Normal Vew Back - 顯示的範圍大小 - X */
#define SIM_DEFAULT_NV_BACK_DISPLAY_AREA_SIZE_X                 392       
/** \brief Normal Vew Back - 顯示的範圍大小 - Y */
#define SIM_DEFAULT_NV_BACK_DISPLAY_AREA_SIZE_Y                 334       
/** \brief Normal Vew Back - 顯示圖的旋轉角度*/
#define SIM_DEFAULT_NV_BACK_ROTATION_DEGREE                     0       
/** \brief Normal Vew Back - 顯示時是否做 mirror */
#define SIM_DEFAULT_NV_BACK_MORRIR                              1         
/** \brief Normal Vew Back - 目標平面的原點位置 - X */
#define SIM_DEFAULT_NV_BACK_PT_DEST_ORIGIN_POS_X                196         
/** \brief Normal Vew Back - 目標平面的原點位置 - Y */
#define SIM_DEFAULT_NV_BACK_PT_DEST_ORIGIN_POS_Y                167         
/** \brief Normal Vew Back - 目標平面的 FOV (H) */
#define SIM_DEFAULT_NV_BACK_PT_DEST_FOV_H                       117         
/** \brief Normal Vew Back - 目標平面的 Pitch Angle*/
#define SIM_DEFAULT_NV_BACK_PT_DEST_PITCH                       (-45)         
/** \brief Normal Vew Back - 目標平面的 Yaw Angle*/
#define SIM_DEFAULT_NV_BACK_PT_DEST_YAW                         0         
/** \brief Normal Vew Back - 目標平面的 Roll Angle*/
#define SIM_DEFAULT_NV_BACK_PT_DEST_ROLL                        0         

/** \brief Normal Vew Left - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_NV_LEFT_FUNCTION_ENABLED                    0      
/** \brief Normal Vew Left - 顯示型式 - 0: Crop Only,  1: Do-defisheye Only, 2: Do View Angle Correction */
#define SIM_DEFAULT_NV_LEFT_TYPE                                2       
/** \brief Normal Vew Left - 裁切的起始位置 - X */
#define SIM_DEFAULT_NV_LEFT_CROP_START_POS_X                    0       
/** \brief Normal Vew Left - 裁切的起始位置 - Y */
#define SIM_DEFAULT_NV_LEFT_CROP_START_POS_Y                    0        
/** \brief Normal Vew Left - 裁切的範圍大小 - X */
#define SIM_DEFAULT_NV_LEFT_CROP_AREA_SIZE_X                    720     
/** \brief Normal Vew Left - 裁切的範圍大小 - Y */
#define SIM_DEFAULT_NV_LEFT_CROP_AREA_SIZE_Y                    480       
/** \brief Normal Vew Left - 顯示的起始位置 - X */
#define SIM_DEFAULT_NV_LEFT_DISPLAY_START_POS_X                 0         
/** \brief Normal Vew Left - 顯示的起始位置 - Y */
#define SIM_DEFAULT_NV_LEFT_DISPLAY_START_POS_Y                 0         
/** \brief Normal Vew Left - 顯示的範圍大小 - X */
#define SIM_DEFAULT_NV_LEFT_DISPLAY_AREA_SIZE_X                 720       
/** \brief Normal Vew Left - 顯示的範圍大小 - Y */
#define SIM_DEFAULT_NV_LEFT_DISPLAY_AREA_SIZE_Y                 480       
/** \brief Normal Vew Left - 顯示圖的旋轉角度*/
#define SIM_DEFAULT_NV_LEFT_ROTATION_DEGREE                     0       
/** \brief Normal Vew Left - 顯示時是否做 mirror */
#define SIM_DEFAULT_NV_LEFT_MORRIR                              0         
/** \brief Normal Vew Left - 目標平面的原點位置 - X */
#define SIM_DEFAULT_NV_LEFT_PT_DEST_ORIGIN_POS_X                360         
/** \brief Normal Vew Left - 目標平面的原點位置 - Y */
#define SIM_DEFAULT_NV_LEFT_PT_DEST_ORIGIN_POS_Y                240         
/** \brief Normal Vew Left - 目標平面的 FOV (H) */
#define SIM_DEFAULT_NV_LEFT_PT_DEST_FOV_H                       135         
/** \brief Normal Vew Left - 目標平面的 Pitch Angle*/
#define SIM_DEFAULT_NV_LEFT_PT_DEST_PITCH                       0;//(-70)         
/** \brief Normal Vew Left - 目標平面的 Yaw Angle*/
#define SIM_DEFAULT_NV_LEFT_PT_DEST_YAW                         90         
/** \brief Normal Vew Left - 目標平面的 Roll Angle*/
#define SIM_DEFAULT_NV_LEFT_PT_DEST_ROLL                        0         

/** \brief Normal Vew Right - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_NV_RIGHT_FUNCTION_ENABLED                   0      
/** \brief Normal Vew Right - 顯示型式 - 0: Crop Only,  1: Do-defisheye Only, 2: Do View Angle Correction */
#define SIM_DEFAULT_NV_RIGHT_TYPE                               2       
/** \brief Normal Vew Right - 裁切的起始位置 - X */
#define SIM_DEFAULT_NV_RIGHT_CROP_START_POS_X                   0       
/** \brief Normal Vew Right - 裁切的起始位置 - Y */
#define SIM_DEFAULT_NV_RIGHT_CROP_START_POS_Y                   0        
/** \brief Normal Vew Right - 裁切的範圍大小 - X */
#define SIM_DEFAULT_NV_RIGHT_CROP_AREA_SIZE_X                   720     
/** \brief Normal Vew Right - 裁切的範圍大小 - Y */
#define SIM_DEFAULT_NV_RIGHT_CROP_AREA_SIZE_Y                   480       
/** \brief Normal Vew Right - 顯示的起始位置 - X */
#define SIM_DEFAULT_NV_RIGHT_DISPLAY_START_POS_X                0         
/** \brief Normal Vew Right - 顯示的起始位置 - Y */
#define SIM_DEFAULT_NV_RIGHT_DISPLAY_START_POS_Y                0         
/** \brief Normal Vew Right - 顯示的範圍大小 - X */
#define SIM_DEFAULT_NV_RIGHT_DISPLAY_AREA_SIZE_X                720       
/** \brief Normal Vew Right - 顯示的範圍大小 - Y */
#define SIM_DEFAULT_NV_RIGHT_DISPLAY_AREA_SIZE_Y                480       
/** \brief Normal Vew Right - 顯示圖的旋轉角度*/
#define SIM_DEFAULT_NV_RIGHT_ROTATION_DEGREE                    0       
/** \brief Normal Vew Right - 顯示時是否做 mirror */
#define SIM_DEFAULT_NV_RIGHT_MORRIR                             0         
/** \brief Normal Vew Right - 目標平面的原點位置 - X */
#define SIM_DEFAULT_NV_RIGHT_PT_DEST_ORIGIN_POS_X               360         
/** \brief Normal Vew Right - 目標平面的原點位置 - Y */
#define SIM_DEFAULT_NV_RIGHT_PT_DEST_ORIGIN_POS_Y               240         
/** \brief Normal Vew Right - 目標平面的 FOV (H) */
#define SIM_DEFAULT_NV_RIGHT_PT_DEST_FOV_H                      135         
/** \brief Normal Vew Right - 目標平面的 Pitch Angle*/
#define SIM_DEFAULT_NV_RIGHT_PT_DEST_PITCH                      (-70)         
/** \brief Normal Vew Right - 目標平面的 Yaw Angle*/
#define SIM_DEFAULT_NV_RIGHT_PT_DEST_YAW                        0         
/** \brief Normal Vew Right - 目標平面的 Roll Angle*/
#define SIM_DEFAULT_NV_RIGHT_PT_DEST_ROLL                       0         


/** \brief SMOD - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_SMOD_FUNCTION_ENABLED               1      
/** \brief SMOD Detection Range on alAVM2D birdview image. (偵測距離 (mm) */
#define SIM_DEFAULT_SMOD_DETEC_RANGE                    2000
/** \brief SMOD Sensitivity. */
#define SIM_DEFAULT_SMOD_SENSITIVITY                    5

/** \brief FM_v2 - BV Left Camera Model */
#define SIM_DEFAULT_FM_v2_BV_LEFT_CAMERA_MODEL             FM3D_SPARROW_190       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - BV Left Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_BV_LEFT_COD_X                    360     // NTSC 影像上的位置    
/** \brief FM_v2 - BV Left Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_BV_LEFT_COD_Y                    240     // NTSC 影像上的位置    

/** \brief FM_v2 - BV Right Camera Model */
#define SIM_DEFAULT_FM_v2_BV_RIGHT_CAMERA_MODEL            FM3D_SPARROW_190       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - BV Left Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_BV_RIGHT_COD_X                   360     // NTSC 影像上的位置    
/** \brief FM_v2 - BV Left Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_BV_RIGHT_COD_Y                   240     // NTSC 影像上的位置    

/** \brief FM_v2 - BV Front Camera Model */
#define SIM_DEFAULT_FM_v2_BV_FRONT_CAMERA_MODEL            FM3D_SPARROW_190       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - BV Front Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_BV_FRONT_COD_X                   360     // NTSC 影像上的位置    
/** \brief FM_v2 - BV Front Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_BV_FRONT_COD_Y                   240     // NTSC 影像上的位置    

/** \brief FM_v2 - BV Back Camera Model */
#define SIM_DEFAULT_FM_v2_BV_BACK_CAMERA_MODEL             FM3D_SPARROW_144       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - BV Back Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_BV_BACK_COD_X                    360     // NTSC 影像上的位置    
/** \brief FM_v2 - BV Back Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_BV_BACK_COD_Y                    240     // NTSC 影像上的位置    

/** \brief FM_v2 - SV Left Camera Model */
#define SIM_DEFAULT_FM_v2_SV_LEFT_CAMERA_MODEL             2       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - SV Left Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_SV_LEFT_COD_X                    360     // NTSC 影像上的位置    
/** \brief FM_v2 - SV Left Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_SV_LEFT_COD_Y                    240     // NTSC 影像上的位置    

/** \brief FM_v2 - SV Right Camera Model */
#define SIM_DEFAULT_FM_v2_SV_RIGHT_CAMERA_MODEL            2       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - SV Right Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_SV_RIGHT_COD_X                   360     // NTSC 影像上的位置    
/** \brief FM_v2 - SV Right Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_SV_RIGHT_COD_Y                   240     // NTSC 影像上的位置    

/** \brief FM_v2 - LVDS Front Camera Model */
#define SIM_DEFAULT_FM_v2_LVDS_FRONT_CAMERA_MODEL          98       // 0: Sparrow 144, 1: Sparrow 190, 2: Sparrow 90
/** \brief FM_v2 - LVDS Front  Center of Distortion (COD) - X, pixel */
#define SIM_DEFAULT_FM_v2_LVDS_FRONT_COD_X                 360     // NTSC 影像上的位置    
/** \brief FM_v2 - LVDS Front  Center of Distortion (COD) - Y, pixel */
#define SIM_DEFAULT_FM_v2_LVDS_FRONT_COD_Y                 240     // NTSC 影像上的位置    


/* AVM3D Cfg default setting information */
#define AVM3D_VIEW_CNT 1
#define SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_BUMPER_1   8000
#define SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_SIDE_1     3000
#define SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_BUMPER_2   30000
#define SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_SIDE_2     3000
#define SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_BUMPER_1   8000
#define SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_SIDE_1     3000
#define SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_BUMPER_2   30000
#define SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_SIDE_2     3000

#define AVM3D_NAME_1    "AVM3D_LEFT"
#define AVM3D_DestImageBufferSizeX_1    720
#define AVM3D_DestImageBufferSizeY_1    480
#define AVM3D_DestStartPointX_1 0
#define AVM3D_DestStartPointY_1 0
#define AVM3D_DestAreaSizeX_1   392
#define AVM3D_DestAreaSizeY_1   334
#define AVM3D_VirtualCameraPosX_1   2000
#define AVM3D_VirtualCameraPosY_1   2300
#define AVM3D_VirtualCameraPosZ_1   -2600
#define AVM3D_VirtualCameraCustomRoll_1 0
#define AVM3D_VirtualCameraPitch_1  28
#define AVM3D_VirtualCameraYaw_1    -8
#define AVM3D_VirtualCameraRoll_1   -20
#define AVM3D_VCFisheyeModel_1 0x81
#define AVM3D_Mirror_1  0
#define AVM3D_ScalingX_1    1.35
#define AVM3D_ScalingY_1    1.35
#define AVM3D_OffsetX_1     164
#define AVM3D_OffsetY_1     73
#define AVM3D_StitchLineStartX0_1   -1020
#define AVM3D_StitchLineStartY0_1   -2731
#define AVM3D_StitchLineStartX1_1   1020
#define AVM3D_StitchLineStartY1_1   -2731
#define AVM3D_StitchLineStartX2_1   -1020
#define AVM3D_StitchLineStartY2_1   2731
#define AVM3D_StitchLineStartX3_1   1020
#define AVM3D_StitchLineStartY3_1   2731
#define AVM3D_StitchLineAngle0_1    250
#define AVM3D_StitchLineAngle1_1    280
#define AVM3D_StitchLineAngle2_1    135
#define AVM3D_StitchLineAngle3_1    75
#define AVM3D_StitchAngleRange_1    10
#define AVM3D_CurveSurfaceA_1   0.000008
#define AVM3D_CurveSurfaceB_1   0.000008
#define AVM3D_CurveSurfaceC_1   0.000008
#define AVM3D_CurveSurfaceD_1   0.000008
#define AVM3D_CurveSurfaceE_1   1
#define AVM3D_CurveSurfaceF_1   0
#define AVM3D_CurveCenterX_1    0
#define AVM3D_CurveCenterY_1    0
#define AVM3D_CurveCenterZ_1    1000
#define AVM3D_CURVE2_PROJECT_CENTER_Z   -950
#define AVM3D_CornerLeftFrontX_1    -1020
#define AVM3D_CornerLeftFrontY_1    -2731    
#define AVM3D_CornerRightFrontX_1   1020
#define AVM3D_CornerRightFrontY_1   -2731
#define AVM3D_CornerLeftBackX_1     -1020
#define AVM3D_CornerLeftBackY_1     2731
#define AVM3D_CornerRightBackX_1    1020
#define AVM3D_CornerRightBackY_1    2731
#define AVM3D_StichLineType_1   0
#define AVM3D_BLOCK_SET_DISTANCE_1   150


/* AVM3D Overlap Cfg default setting information */
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTLEFT	-1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTLEFT	-200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTRIGHT	1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTRIGHT	200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKLEFT	-1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKLEFT	-200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKRIGHT	1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKRIGHT	200


#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTLEFT	-1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTLEFT	-200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTRIGHT	-1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTRIGHT	-200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKLEFT	1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKLEFT	200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKRIGHT	1000
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKRIGHT	200

#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_BEZIERWEIGHT	1
#define SIM_DEFAULT_AVM3D_OVERLAP_CFG_ANGLEOFFSET	0


/**
  *  @}
  */
