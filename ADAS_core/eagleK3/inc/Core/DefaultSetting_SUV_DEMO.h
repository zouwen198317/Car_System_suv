
#pragma once

/**
  *  \addtogroup Common
  *  @{
  */

/** \brief This default setting is used for SUV demo car */
#define SIM_DEFAULT_CAR_MODEL                       EAGLEK3_CAR_MODEL_SUV_DEMO
#define SIM_DEFAULT_CAR_MODEL_NAME                  "SUV_DEMO"

/** \brief Common Configuration */
#define SIM_DEFAULT_DISPLAY_START_POINT_X 	        0				   
#define SIM_DEFAULT_DISPLAY_START_POINT_Y 	        0				   
#define SIM_DEFAULT_DISPLAY_IMAGE_WIDTH   	        720				   
#define SIM_DEFAULT_DISPLAY_IMAGE_HEIGHT  	        480				   
#define SIM_DEFAULT_DISPLAY_RATIO                   (16.f/9.f)

#define SIM_DEFAULT_CAR_LEN  		                4816        // 車輛長度(mm)				   
#define SIM_DEFAULT_CAR_WID  		                1860    	// 車輛寬度(mm)				   
#define SIM_DEFAULT_CAR_MAX_STEER_ANGLE             720	        // 方向盤最大舵角(mm)				   
#define SIM_DEFAULT_CAR_FWLE2HEAD_DISTANCE          567         // 前輪前緣到車頭距離
#define SIM_DEFAULT_CAR_FW2HEAD_DISTANCE            920         // 前輪軸心到車頭距離
#define SIM_DEFAULT_CAR_BW2TAIL_DISTANCE            986        // 後輪軸心到車尾距離
#define SIM_DEFAULT_CAR_FW_AXLE_WIDTH               1605        // 前輪軸寬
#define SIM_DEFAULT_CAR_BW_AXLE_WIDTH               1605        // 後輪軸寬
#define SIM_DEFAULT_CAR_FBW_AXLE_DISTANCE           2910        // 前後輪軸距
#define SIM_DEFAULT_CAR_FFP2HEAD_DISTANCE           (SIM_DEFAULT_CAR_FW2HEAD_DISTANCE)         // 前輪兩定位點中線到車頭距離
//#define SIM_DEFAULT_CAR_CEN2LEFTMIRROR_DISTANCE     1105      // 車輛中心線到左後視鏡距離
//#define SIM_DEFAULT_CAR_CEN2RIGHTMIRROR_DISTANCE    1081      // 車輛中心線到右後視鏡距離

/** \brief Camera Configuration */
#define SIM_DEFAULT_CAM_PITCH_BV_FRONT              (-20)
#define SIM_DEFAULT_CAM_YAW_BV_FRONT                3
#define SIM_DEFAULT_CAM_ROLL_BV_FRONT               0
#define SIM_DEFAULT_CAM_POS_X_BV_FRONT              0           // 車寬中央為 0
#define SIM_DEFAULT_CAM_POS_Y_BV_FRONT              (-2408)     // 車長中央為 0
#define SIM_DEFAULT_CAM_POS_Z_BV_FRONT              758         // 地平線為 0
#define SIM_DEFAULT_CAM_WIDTH_BV_FRONT              720
#define SIM_DEFAULT_CAM_HEIGHT_BV_FRONT             480

#define SIM_DEFAULT_CAM_PITCH_BV_BACK               (-45)
#define SIM_DEFAULT_CAM_YAW_BV_BACK                 (1)
#define SIM_DEFAULT_CAM_ROLL_BV_BACK                0
#define SIM_DEFAULT_CAM_POS_X_BV_BACK               5           // 車寬中央為 0
#define SIM_DEFAULT_CAM_POS_Y_BV_BACK               (2392)      // 車長中央為 0
#define SIM_DEFAULT_CAM_POS_Z_BV_BACK               1035//1055         // 地平線為 0
#define SIM_DEFAULT_CAM_WIDTH_BV_BACK               720
#define SIM_DEFAULT_CAM_HEIGHT_BV_BACK              480

#define SIM_DEFAULT_CAM_PITCH_BV_LEFT               (-70)
#define SIM_DEFAULT_CAM_YAW_BV_LEFT                 (-2)
#define SIM_DEFAULT_CAM_ROLL_BV_LEFT                (0)
#define SIM_DEFAULT_CAM_POS_X_BV_LEFT               (-990)     // 車寬中央為 0
#define SIM_DEFAULT_CAM_POS_Y_BV_LEFT               (-734)      // 車長中央為 0
#define SIM_DEFAULT_CAM_POS_Z_BV_LEFT               (1077)      // 地平線為 0
#define SIM_DEFAULT_CAM_WIDTH_BV_LEFT               720
#define SIM_DEFAULT_CAM_HEIGHT_BV_LEFT              480

#define SIM_DEFAULT_CAM_PITCH_BV_RIGHT              (-70)
#define SIM_DEFAULT_CAM_YAW_BV_RIGHT                (-2)
#define SIM_DEFAULT_CAM_ROLL_BV_RIGHT               (0)
#define SIM_DEFAULT_CAM_POS_X_BV_RIGHT              990        // 車寬中央為 0
#define SIM_DEFAULT_CAM_POS_Y_BV_RIGHT              (-734)      // 車長中央為 0
#define SIM_DEFAULT_CAM_POS_Z_BV_RIGHT              1077        // 地平線為 0
#define SIM_DEFAULT_CAM_WIDTH_BV_RIGHT              720
#define SIM_DEFAULT_CAM_HEIGHT_BV_RIGHT             480

/* SV Left/Right & LVDS Front is currently not ready & used. */
#define SIM_DEFAULT_CAM_PITCH_SV_LEFT               (0)
#define SIM_DEFAULT_CAM_YAW_SV_LEFT                 (20)
#define SIM_DEFAULT_CAM_ROLL_SV_LEFT                0
#define SIM_DEFAULT_CAM_POS_X_SV_LEFT               (-1045)
#define SIM_DEFAULT_CAM_POS_Y_SV_LEFT               (-570)
#define SIM_DEFAULT_CAM_POS_Z_SV_LEFT               (1069)
#define SIM_DEFAULT_CAM_WIDTH_SV_LEFT               720
#define SIM_DEFAULT_CAM_HEIGHT_SV_LEFT              480

#define SIM_DEFAULT_CAM_PITCH_SV_RIGHT              (0)
#define SIM_DEFAULT_CAM_YAW_SV_RIGHT                (-20)
#define SIM_DEFAULT_CAM_ROLL_SV_RIGHT               0
#define SIM_DEFAULT_CAM_POS_X_SV_RIGHT              1017
#define SIM_DEFAULT_CAM_POS_Y_SV_RIGHT              (-543)
#define SIM_DEFAULT_CAM_POS_Z_SV_RIGHT              1068
#define SIM_DEFAULT_CAM_WIDTH_SV_RIGHT              720
#define SIM_DEFAULT_CAM_HEIGHT_SV_RIGHT             480

#define SIM_DEFAULT_CAM_PITCH_LVDS_FRONT            (-10)
#define SIM_DEFAULT_CAM_YAW_LVDS_FRONT              (0)
#define SIM_DEFAULT_CAM_ROLL_LVDS_FRONT             0
#define SIM_DEFAULT_CAM_POS_X_LVDS_FRONT            0
#define SIM_DEFAULT_CAM_POS_Y_LVDS_FRONT            0
#define SIM_DEFAULT_CAM_POS_Z_LVDS_FRONT            1250
#define SIM_DEFAULT_CAM_WIDTH_LVDS_FRONT            1280
#define SIM_DEFAULT_CAM_HEIGHT_LVDS_FRONT           800

/* 
    \brief   The display scale & offset factors of single planar view. When the calibration UI called CAMK_GenerateSingleViewPlanarImage_YUYV
             or CAMK_GenerateSingleViewPlanarImage_RGB function, the planar image y position will be scale & offset by this value. Thus 
             the coordinates of selected feature points should be offset back too. (in pixel)
*/
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_FRONT        2.5f // 3.0f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_FRONT      0
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_FRONT      -100
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_BACK         2.5f // 3.0f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_BACK       0
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_BACK       (100)
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_LEFT         1.6f // 1.7f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_LEFT       -100
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_LEFT       60
#define SIM_DEFAULT_SINGLE_VIEW_SCALAR_RIGHT        1.6f // 1.7f
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_RIGHT      100
#define SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_RIGHT      60

/** TopView Configuration */

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
#define SIM_DEFAULT_NV_LEFT_PT_DEST_PITCH                       (-70)         
/** \brief Normal Vew Left - 目標平面的 Yaw Angle*/
#define SIM_DEFAULT_NV_LEFT_PT_DEST_YAW                         0         
/** \brief Normal Vew Left - 目標平面的 Roll Angle*/
#define SIM_DEFAULT_NV_LEFT_PT_DEST_ROLL                        0         

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

/** \brief BirdView Configuration */
#define SIM_DEFAULT_BV_MAXIMUM_DISTANCE                         2500        // 最大可視範圍距離
#define SIM_DEFAULT_BV_NORMAL_DISTANCE                          2500        // 等比例範圍距離
#define SIM_DEFAULT_BV_UNDIST_DISTANCE                          2000        // 標示範圍距離(黃框) : 亦為 SMOD 偵測範圍
#define SIM_DEFAULT_BV_BLIND_DISTANCE_FRONT                     400         // 前方延伸遮蔽區(軟體盲區)(mm)
#define SIM_DEFAULT_BV_BLIND_DISTANCE_REAR                      200         // 後方延伸遮蔽區(軟體盲區)(mm)
#define SIM_DEFAULT_BV_BLIND_DISTANCE_LEFT                      0           // 左方延伸遮蔽區(軟體盲區)(mm)
#define SIM_DEFAULT_BV_BLIND_DISTANCE_RIGHT                     0           // 右方延伸遮蔽區(軟體盲區)(mm)
#define SIM_DEFAULT_BV_LINE_EXT_FRONT                           1000         // 前方裁接線橫向延伸距離 (mm)
#define SIM_DEFAULT_BV_LINE_EXT_REAR                            1000           // 後方裁接線橫向延伸距離 (mm)
#define SIM_DEFAULT_BV_STITCH_BOUND_DISTANCE_FRONT              1000        // BV裁接線在邊界處頂點，與前方最大可視範圍的距離   
#define SIM_DEFAULT_BV_STITCH_BOUND_DISTANCE_REAR               1000        // BV裁接線在邊界處頂點，與後方最大可視範圍的距離
#define SIM_DEFAULT_BV_STITCH_LINE_WIDTH                        2           // BV裁接線寬度 (in pixel)

/////////////////////////////////// 20131121 - Parameters for Global AE LUT ////////////////////////////////////////////////////////////////
#define SIM_DEFAULT_BV_GAE_ROI_PIXEL_NUMBER_X                   30          // ROI pixel width for Global AE - Must be even value
#define SIM_DEFAULT_BV_GAE_ROI_PIXEL_NUMBER_Y                   30          // ROI pixel height for Global AE - Must be even value
#define SIM_DEFAULT_BV_GAE_ROI_PIXEL_OFFSET_X                   1           // ROI pixel offset for Global AE - X
#define SIM_DEFAULT_BV_GAE_ROI_PIXEL_OFFSET_Y                   1           // ROI pixel offset for Global AE - Y
#define SIM_DEFAULT_BV_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_X   -5           // ROI position offset from front-left corner of car picture - X
#define SIM_DEFAULT_BV_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_Y   0           // ROI position offset from front-left corner of car picture - Y
#define SIM_DEFAULT_BV_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_X  5           // ROI position offset from front-right corner of car picture - X
#define SIM_DEFAULT_BV_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_Y  0           // ROI position offset from front-right corner of car picture - Y
#define SIM_DEFAULT_BV_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_X    -5           // ROI position offset from rear-left corner of car picture - X
#define SIM_DEFAULT_BV_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_Y    0           // ROI position offset from rear-left corner of car picture - Y
#define SIM_DEFAULT_BV_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_X   5           // ROI position offset from rear-right corner of car picture - X
#define SIM_DEFAULT_BV_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_Y   0           // ROI position offset from rear-right corner of car picture - Y

/** \brief BirdView Parameters */

// This file is automatically generated.

#define SIM_DEFAULT_BV_UMPP                           20450        // UMPP 
#define SIM_DEFAULT_BV_START_POINT_X                  192        // BirdView 起始座標 X (以BirdView位於影像中央來定義) 
#define SIM_DEFAULT_BV_START_POINT_Y                  0        // BirdView 起始座標 Y (以BirdView位於影像中央來定義) 
#define SIM_DEFAULT_BV_AREA_SIZE_X                    336        // BirdView 範圍 Width 
#define SIM_DEFAULT_BV_AREA_SIZE_Y                    480        // BirdView 範圍 Height 

#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_1_X    314        // BV 左前拼接線位置 第1點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_1_Y    103        // BV 左前拼接線位置 第1點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_2_X    265        // BV 左前拼接線位置 第2點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_2_Y    103        // BV 左前拼接線位置 第2點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_3_X    265        // BV 左前拼接線位置 第3點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_3_Y    103        // BV 左前拼接線位置 第3點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_4_X    192        // BV 左前拼接線位置 第4點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_LEFT_4_Y    49        // BV 左前拼接線位置 第4點 - Y (pixel) 

#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_1_X   406        // BV 右前拼接線位置 第1點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_1_Y   103        // BV 右前拼接線位置 第1點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_2_X   454        // BV 右前拼接線位置 第2點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_2_Y   103        // BV 右前拼接線位置 第2點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_3_X   454        // BV 右前拼接線位置 第3點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_3_Y   103        // BV 右前拼接線位置 第3點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_4_X   527        // BV 右前拼接線位置 第4點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_FRONT_RIGHT_4_Y   49        // BV 右前拼接線位置 第4點 - Y (pixel) 

#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_1_X     314        // BV 左後拼接線位置 第1點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_1_Y     367        // BV 左後拼接線位置 第1點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_2_X     265        // BV 左後拼接線位置 第2點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_2_Y     367        // BV 左後拼接線位置 第2點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_3_X     265        // BV 左後拼接線位置 第3點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_3_Y     367        // BV 左後拼接線位置 第3點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_4_X     192        // BV 左後拼接線位置 第4點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_LEFT_4_Y     431        // BV 左後拼接線位置 第4點 - Y (pixel) 

#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_1_X    406        // BV 右後拼接線位置 第1點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_1_Y    367        // BV 右後拼接線位置 第1點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_2_X    454        // BV 右後拼接線位置 第2點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_2_Y    367        // BV 右後拼接線位置 第2點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_3_X    454        // BV 右後拼接線位置 第3點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_3_Y    367        // BV 右後拼接線位置 第3點 - Y (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_4_X    527        // BV 右後拼接線位置 第4點 - X (pixel) 
#define SIM_DEFAULT_BV_STITCH_POINT_REAR_RIGHT_4_Y    431        // BV 右後拼接線位置 第4點 - Y (pixel) 

#define SIM_DEFAULT_BV_CAR_PICTURE_START_POINT_X      314        // BV 中央車型圖起始點座標 - X (pixel) 
#define SIM_DEFAULT_BV_CAR_PICTURE_START_POINT_Y      103        // BV 中央車型圖起始點座標 - Y (pixel) 
#define SIM_DEFAULT_BV_CAR_PICTURE_AREA_SIZE_X        91        // BV 中央車型圖範圍大小 - X (pixel) 
#define SIM_DEFAULT_BV_CAR_PICTURE_AREA_SIZE_Y        265        // BV 中央車型圖範圍大小 - Y (pixel) 

#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_1_X    192        // BV 未壓縮範圍方框頂點 - 左上 - X (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_1_Y    0        // BV 未壓縮範圍方框頂點 - 左上 - Y (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_2_X    527        // BV 未壓縮範圍方框頂點 - 右上 - X (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_2_Y    0        // BV 未壓縮範圍方框頂點 - 右上 - Y (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_3_X    192        // BV 未壓縮範圍方框頂點 - 左下 - X (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_3_Y    479        // BV 未壓縮範圍方框頂點 - 左下 - Y (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_4_X    527        // BV 未壓縮範圍方框頂點 - 右下 - X (pixel) 
#define SIM_DEFAULT_BV_UNDISTORTED_FRAME_POINT_4_Y    479        // BV 未壓縮範圍方框頂點 - 右下 - Y (pixel) 

#define SIM_DEFAULT_BV_CAR_RECT_LFET_TOP_X            314        // BV 車輛矩形區域左上座標 - X (pixel) 
#define SIM_DEFAULT_BV_CAR_RECT_LFET_TOP_Y            122        // BV 車輛矩形區域左上座標 - Y (pixel) 
#define SIM_DEFAULT_BV_CAR_RECT_RIGHT_BOTTOM_X        405        // BV 車輛矩形區域右下座標 - X (pixel) 
#define SIM_DEFAULT_BV_CAR_RECT_RIGHT_BOTTOM_Y        357        // BV 車輛矩形區域右下座標 - Y (pixel) 

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

/** \brief Alley View Configuration */
#define SIM_DEFAULT_SAV_START_POINT_X                0           // AV 顯示區在 Buffer 的起始位置 - X
#define SIM_DEFAULT_SAV_START_POINT_Y                0           // AV 顯示區在 Buffer 的起始位置 - Y
#define SIM_DEFAULT_SAV_AREA_SIZE_WIDTH              392         // 顯示區的寬度
#define SIM_DEFAULT_SAV_AREA_SIZE_HEIGHT             334         // 顯示區的高度
#define SIM_DEFAULT_SAV_VIEWING_ANGLE                60          // 水平視角 : 右側，左側為對稱 (負值)
#define SIM_DEFAULT_SAV_HORI_FOV                     56          // 畫面水平 FOV : 單側
#define SIM_DEFAULT_SAV_DISPLAY_OFFSET_X             0           // 畫面偏移 X
#define SIM_DEFAULT_SAV_DISPLAY_OFFSET_Y             -90//-85           // 畫面偏移 Y
#define SIM_DEFAULT_SAV_DISPLAY_SMOOTH               4           // 潤邊像素 (pixel)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_0_X              0             // 裁接點座標 (#0)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_0_Y              0 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_1_X              0             // 裁接點座標 (#1)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_1_Y              261 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_2_X              186           // 裁接點座標 (#2)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_2_Y              0 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_3_X              186            // 裁接點座標 (#3)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_3_Y              227 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_4_X              206           // 裁接點座標 (#4)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_4_Y              0 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_5_X              206          // 裁接點座標 (#5)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_5_Y              227 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_6_X              392           // 裁接點座標 (#6)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_6_Y              0 
#define SIM_DEFAULT_SAV_DISPLAY_POINT_7_X              392           // 裁接點座標 (#7)
#define SIM_DEFAULT_SAV_DISPLAY_POINT_7_Y              261 

/** \brief Full Alley View Configuration 
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
#define SIM_DEFAULT_FAV_START_POINT_X                0           // AV 顯示區在 Buffer 的起始位置 - X
#define SIM_DEFAULT_FAV_START_POINT_Y                0           // AV 顯示區在 Buffer 的起始位置 - Y
#define SIM_DEFAULT_FAV_AREA_SIZE_WIDTH              720         // 顯示區的寬度
#define SIM_DEFAULT_FAV_AREA_SIZE_HEIGHT             480         // 顯示區的高度
#define SIM_DEFAULT_FAV_VIEWING_ANGLE                60          // 水平視角 : 右側，左側為對稱 (負值)
#define SIM_DEFAULT_FAV_HORI_FOV                     56          // 畫面水平 FOV : 單側
#define SIM_DEFAULT_FAV_DISPLAY_OFFSET_X             0           // 畫面偏移 X
#define SIM_DEFAULT_FAV_DISPLAY_OFFSET_Y             -85         // 畫面偏移 Y
#define SIM_DEFAULT_FAV_DISPLAY_SMOOTH               6           // 潤邊像素 (pixel)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_0_X              0             // 裁接點座標 (#0)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_0_Y              0 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_1_X              0             // 裁接點座標 (#1)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_1_Y              374 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_2_X              342           // 裁接點座標 (#2)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_2_Y              0 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_3_X              342           // 裁接點座標 (#3)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_3_Y              326 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_4_X              378           // 裁接點座標 (#4)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_4_Y              0 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_5_X              378           // 裁接點座標 (#5)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_5_Y              326 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_6_X              720           // 裁接點座標 (#6)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_6_Y              0 
#define SIM_DEFAULT_FAV_DISPLAY_POINT_7_X              720           // 裁接點座標 (#7)
#define SIM_DEFAULT_FAV_DISPLAY_POINT_7_Y              374 

/** \brief Front Side View Parameters: FLV (front-left), FRV (front-right) */
#define SIM_DEFAULT_FLV_START_POINT_X                 0          // Front-left View 影像在 Buffer 的啟始位置 X, Currently not used
#define SIM_DEFAULT_FLV_START_POINT_Y                 0          // Front-left View 影像在 Buffer 的啟始位置 Y, Currently not used 
#define SIM_DEFAULT_FLV_AREA_SIZE_X                   336        // Front-left View 影像的寬 
#define SIM_DEFAULT_FLV_AREA_SIZE_Y                   380        // Front-left View 影像的高 

#define SIM_DEFAULT_FRV_START_POINT_X                 0          // Front-right View 影像在 Buffer 的啟始位置 X, Currently not used 
#define SIM_DEFAULT_FRV_START_POINT_Y                 0          // Front-right View 影像在 Buffer 的啟始位置 Y, Currently not used 
#define SIM_DEFAULT_FRV_AREA_SIZE_X                   336        // Front-right View 影像的寬 
#define SIM_DEFAULT_FRV_AREA_SIZE_Y                   380        // Front-right View 影像的高 

/** \brief Front Side View Configuration: FLV (front-left), FRV (front-right) */
#define SIM_DEFAULT_FLV_CENTER_X                       450//550           // Front-left View 中心在原影像的位置 X
#define SIM_DEFAULT_FLV_CENTER_Y                       256           // Front-left View 中心在原影像的位置 Y
#define SIM_DEFAULT_FLV_ROTATION                       85            // Front-left View 的旋轉角度 (相對於原影像)
#define SIM_DEFAULT_FLV_SCALING_FACTOR_X               1.0 // (346.0/202.49)// Front-left View 的X方向放大倍率 (相對於原影像)
#define SIM_DEFAULT_FLV_SCALING_FACTOR_Y               1.0 //(480.0/280.913)// Front-left View 的Y方向放大倍率 (相對於原影像)

#define SIM_DEFAULT_FRV_CENTER_X                       269//169           // Front-right View 中心在原影像的位置 X
#define SIM_DEFAULT_FRV_CENTER_Y                       256           // Front-right View 中心在原影像的位置 Y
#define SIM_DEFAULT_FRV_ROTATION                       -85            // Front-right View 的旋轉角度 (相對於原影像)
#define SIM_DEFAULT_FRV_SCALING_FACTOR_X               1.0//(346.0/202.49)// Front-right View 的X方向放大倍率 (相對於原影像)
#define SIM_DEFAULT_FRV_SCALING_FACTOR_Y               1.0//(480.0/280.913)// Front-right View 的Y方向放大倍率 (相對於原影像)


/** \brief MOD Configuration */
#define SIM_DEFAULT_SMOD_DETEC_RANGE                 2000        // SMOD 偵測距離 (mm)
#define SIM_DEFAULT_SMOD_SENSITIVITY                 5           // SMOD 偵測距離 (mm)

/** \brief Defalut Fisheye Configuration */
/*
2013-06-26 Arsing 
Fisheye Model v0.2
2013-07-08 Arsing
modify Sparrow 180 parameters 
2013-07-09 Arsing
Divide by 8 segments to fitting

dI = a * du^3 + b * du^2 + c * du + d
*/
#define SIM_DEFAULT_FM_RESIZE_RATIO_BV_FRONT           (711.f/640.f)//width =711= 720 - 9(黑邊pixels)
#define SIM_DEFAULT_FM_COD_X_BV_FRONT                  (360)
#define SIM_DEFAULT_FM_COD_Y_BV_FRONT                  (240)
#define SIM_DEFAULT_FM_FOV_H_BV_FRONT                  (172.5)
#define SIM_DEFAULT_FM_SEGMENT_BV_FRONT                (8)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_BV_FRONT      (20)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_BV_FRONT      (40)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_BV_FRONT      (60)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_BV_FRONT      (70)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_BV_FRONT      (80)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_BV_FRONT      (84)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_BV_FRONT      (87.5)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_BV_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_BV_FRONT      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_BV_FRONT              (-0.001634180265152  )//0~20
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_BV_FRONT              (-0.001564989848485  )//20~40
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_BV_FRONT              (-0.000201588400019  )//40~60
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_BV_FRONT              ( 0.000651277716347  )//60~70
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_BV_FRONT              ( 0.000064853706746  )//70~80
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_BV_FRONT              ( 0.000013371583228  )//80~84
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_BV_FRONT              ( 0.000000238405575  )//84~87.5
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_BV_FRONT              ( 0.000000001343166  )//87.5UP
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_BV_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_BV_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_BV_FRONT              ( 0.044251162527058  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_BV_FRONT              ( 0.039846191918081  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_BV_FRONT              (-0.054097800426460  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_BV_FRONT              (-0.134986021478925  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_BV_FRONT              (-0.024889227459107  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_BV_FRONT              (-0.007851336572658  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_BV_FRONT              (-0.000374473803154  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_BV_FRONT              (-0.000008706313984  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_BV_FRONT             (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_BV_FRONT              ( 5.736707843722940  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_BV_FRONT              ( 5.793857219099250  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_BV_FRONT              ( 7.890247255785330  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_BV_FRONT              ( 10.385319991347300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_BV_FRONT              ( 3.473570898086800  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_BV_FRONT              ( 1.639085913921260  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_BV_FRONT              ( 0.212623239515698  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_BV_FRONT              ( 0.019166181098427  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_BV_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_BV_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_BV_FRONT              ( 0.000476772121221  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_BV_FRONT              (-0.209019429100946  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_BV_FRONT              (-15.394517920725300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_BV_FRONT              (-40.258368204572600 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_BV_FRONT              (104.623015205560000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_BV_FRONT              (168.575867907065000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_BV_FRONT              (260.259270891694000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_BV_FRONT              (295.410449204026000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_BV_FRONT              ( 0.000001429266285  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_BV_FRONT              ( 0.000001288098939  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_BV_FRONT              ( 0.000005626226077  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_BV_FRONT              ( 0.000045624996707  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_BV_FRONT              ( 0.000418900794781  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_BV_FRONT              ( 0.004752765847185  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_BV_FRONT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_BV_FRONT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_BV_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_BV_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_BV_FRONT              (-0.000217081780096  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_BV_FRONT              (-0.000203022034368  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_BV_FRONT              (-0.001744673142783  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_BV_FRONT              (-0.024221679592604   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_BV_FRONT              (-0.292628050421520   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_BV_FRONT              (-3.799512019032040  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_BV_FRONT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_BV_FRONT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_BV_FRONT              ( 0.174170543584806  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_BV_FRONT              ( 0.173754910212572  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_BV_FRONT              ( 0.358121127158595  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_BV_FRONT              ( 4.571450399114440    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_BV_FRONT              ( 68.875099257686500   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_BV_FRONT              ( 1014.377388771400000    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_BV_FRONT              ( 31598.260528220600000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_BV_FRONT              ( 31598.260528220600000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_BV_FRONT             (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_BV_FRONT              ( 0.000071353312696   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_BV_FRONT              ( 0.003214847717227  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_BV_FRONT              (-7.396291115997770   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_BV_FRONT              (-270.787984417783000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_BV_FRONT              (-5403.290246798560000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_BV_FRONT              (-90340.644827611600000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_BV_FRONT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_BV_FRONT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_BV_FRONT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_BV_FRONT             (0.0)


#define SIM_DEFAULT_FM_RESIZE_RATIO_BV_BACK           (711.f/640.f)//width =711= 720 - 9(黑邊pixels)
#define SIM_DEFAULT_FM_COD_X_BV_BACK                  (360)
#define SIM_DEFAULT_FM_COD_Y_BV_BACK                  (240)
#define SIM_DEFAULT_FM_FOV_H_BV_BACK                  (144.5)
#define SIM_DEFAULT_FM_SEGMENT_BV_BACK                (6)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_BV_BACK      (20)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_BV_BACK      (40)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_BV_BACK      (60)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_BV_BACK      (66)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_BV_BACK      (71)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_BV_BACK      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_BV_BACK      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_BV_BACK      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_BV_BACK      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_BV_BACK              (-0.0000152092717527  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_BV_BACK              (-0.0000186791230791  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_BV_BACK              ( 0.0000068189519739  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_BV_BACK              ( 0.0000074037646906  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_BV_BACK              ( 0.0000039907570898  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_BV_BACK              ( 0.0000010295437251  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_BV_BACK              ( 0.0000880678021431  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_BV_BACK              ( 0.0003036977841792  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_BV_BACK              (-0.0068489661929545  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_BV_BACK              (-0.0068509366841400  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_BV_BACK              (-0.0044901188509400  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_BV_BACK              (-0.0017164898091813  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_BV_BACK              ( 1.8640483640073200  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_BV_BACK              ( 1.8633941204221300  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_BV_BACK              ( 2.5421860155113400  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_BV_BACK              ( 2.4932596064621700  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_BV_BACK              ( 1.9479994652280100  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_BV_BACK              ( 1.0774208054147500  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_BV_BACK              ( 0.0014118650936193  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_BV_BACK              (-0.0981037147476300  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_BV_BACK              (-21.8334454959897000  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_BV_BACK              (-16.3418986315004000   )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_BV_BACK              (25.7051984266188000   )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_BV_BACK              (117.2011580348240000  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_BV_BACK              (0.0000013490655387  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_BV_BACK              (0.0000039286848462  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_BV_BACK              (0.0000162775813058  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_BV_BACK              (0.0000620456450919  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_BV_BACK              (0.0001474295025155  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_BV_BACK              (0.0005820992142945  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_BV_BACK              (-0.0000187281281348  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_BV_BACK              (-0.0006291483089988  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_BV_BACK              (-0.0068164153608157  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_BV_BACK              (-0.0405703720680226  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_BV_BACK              (-0.1137662423905590  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_BV_BACK              (-0.5317029860986800  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_BV_BACK              ( 0.5365454993477890  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_BV_BACK              ( 0.5861169049585270  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_BV_BACK              ( 1.6285916167463400  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_BV_BACK              ( 9.9451836176761800  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_BV_BACK              ( 30.8665638546747000  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_BV_BACK              ( 164.8327719498060000  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_BV_BACK              ( -0.0009680242955730   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_BV_BACK              (-1.3665360628540900  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_BV_BACK              (-60.2857615028618000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_BV_BACK              (-744.9147926874510000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_BV_BACK              (-2738.7261584755100000    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_BV_BACK              (-17054.0816951200000000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_BV_BACK              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_BV_BACK              (0.0)

#define SIM_DEFAULT_FM_RESIZE_RATIO_BV_LEFT           (711.f/640.f)//width =711= 720 - 9(黑邊pixels)
#define SIM_DEFAULT_FM_COD_X_BV_LEFT                  (360)
#define SIM_DEFAULT_FM_COD_Y_BV_LEFT                  (240)
#define SIM_DEFAULT_FM_FOV_H_BV_LEFT                  (172.5)
#define SIM_DEFAULT_FM_SEGMENT_BV_LEFT                (8)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_BV_LEFT      (20)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_BV_LEFT      (40)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_BV_LEFT      (60)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_BV_LEFT      (70)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_BV_LEFT      (80)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_BV_LEFT      (84)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_BV_LEFT      (87.5)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_BV_LEFT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_BV_LEFT      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_BV_LEFT              (-0.001634180265152  )//0~20
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_BV_LEFT              (-0.001564989848485  )//20~40
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_BV_LEFT              (-0.000201588400019  )//40~60
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_BV_LEFT              ( 0.000651277716347  )//60~70
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_BV_LEFT              ( 0.000064853706746  )//70~80
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_BV_LEFT              ( 0.000013371583228  )//80~84
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_BV_LEFT              ( 0.000000238405575  )//84~87.5
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_BV_LEFT              ( 0.000000001343166  )//87.5UP
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_BV_LEFT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_BV_LEFT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_BV_LEFT              ( 0.044251162527058  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_BV_LEFT              ( 0.039846191918081  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_BV_LEFT              (-0.054097800426460  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_BV_LEFT              (-0.134986021478925  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_BV_LEFT              (-0.024889227459107  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_BV_LEFT              (-0.007851336572658  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_BV_LEFT              (-0.000374473803154  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_BV_LEFT              (-0.000008706313984  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_BV_LEFT             (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_BV_LEFT              ( 5.736707843722940  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_BV_LEFT              ( 5.793857219099250  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_BV_LEFT              ( 7.890247255785330  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_BV_LEFT              ( 10.385319991347300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_BV_LEFT              ( 3.473570898086800  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_BV_LEFT              ( 1.639085913921260  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_BV_LEFT              ( 0.212623239515698  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_BV_LEFT              ( 0.019166181098427  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_BV_LEFT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_BV_LEFT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_BV_LEFT              ( 0.000476772121221  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_BV_LEFT              (-0.209019429100946  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_BV_LEFT              (-15.394517920725300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_BV_LEFT              (-40.258368204572600 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_BV_LEFT              (104.623015205560000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_BV_LEFT              (168.575867907065000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_BV_LEFT              (260.259270891694000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_BV_LEFT              (295.410449204026000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_BV_LEFT              ( 0.000001429266285  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_BV_LEFT              ( 0.000001288098939  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_BV_LEFT              ( 0.000005626226077  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_BV_LEFT              ( 0.000045624996707  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_BV_LEFT              ( 0.000418900794781  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_BV_LEFT              ( 0.004752765847185  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_BV_LEFT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_BV_LEFT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_BV_LEFT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_BV_LEFT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_BV_LEFT              (-0.000217081780096  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_BV_LEFT              (-0.000203022034368  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_BV_LEFT              (-0.001744673142783  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_BV_LEFT              (-0.024221679592604   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_BV_LEFT              (-0.292628050421520   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_BV_LEFT              (-3.799512019032040  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_BV_LEFT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_BV_LEFT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_BV_LEFT              ( 0.174170543584806  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_BV_LEFT              ( 0.173754910212572  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_BV_LEFT              ( 0.358121127158595  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_BV_LEFT              ( 4.571450399114440    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_BV_LEFT              ( 68.875099257686500   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_BV_LEFT              ( 1014.377388771400000    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_BV_LEFT              ( 31598.260528220600000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_BV_LEFT              ( 31598.260528220600000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_BV_LEFT             (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_BV_LEFT              ( 0.000071353312696   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_BV_LEFT              ( 0.003214847717227  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_BV_LEFT              (-7.396291115997770   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_BV_LEFT              (-270.787984417783000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_BV_LEFT              (-5403.290246798560000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_BV_LEFT              (-90340.644827611600000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_BV_LEFT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_BV_LEFT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_BV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_BV_LEFT             (0.0)

#define SIM_DEFAULT_FM_RESIZE_RATIO_BV_RIGHT           (711.f/640.f)//width =711= 720 - 9(黑邊pixels)
#define SIM_DEFAULT_FM_COD_X_BV_RIGHT                  (360)
#define SIM_DEFAULT_FM_COD_Y_BV_RIGHT                  (240)
#define SIM_DEFAULT_FM_FOV_H_BV_RIGHT                  (172.5)
#define SIM_DEFAULT_FM_SEGMENT_BV_RIGHT                (8)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_BV_RIGHT      (20)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_BV_RIGHT      (40)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_BV_RIGHT      (60)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_BV_RIGHT      (70)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_BV_RIGHT      (80)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_BV_RIGHT      (84)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_BV_RIGHT      (87.5)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_BV_RIGHT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_BV_RIGHT      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_BV_RIGHT              (-0.001634180265152  )//0~20
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_BV_RIGHT              (-0.001564989848485  )//20~40
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_BV_RIGHT              (-0.000201588400019  )//40~60
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_BV_RIGHT              ( 0.000651277716347  )//60~70
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_BV_RIGHT              ( 0.000064853706746  )//70~80
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_BV_RIGHT              ( 0.000013371583228  )//80~84
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_BV_RIGHT              ( 0.000000238405575  )//84~87.5
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_BV_RIGHT              ( 0.000000001343166  )//87.5UP
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_BV_RIGHT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_BV_RIGHT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_BV_RIGHT              ( 0.044251162527058  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_BV_RIGHT              ( 0.039846191918081  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_BV_RIGHT              (-0.054097800426460  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_BV_RIGHT              (-0.134986021478925  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_BV_RIGHT              (-0.024889227459107  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_BV_RIGHT              (-0.007851336572658  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_BV_RIGHT              (-0.000374473803154  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_BV_RIGHT              (-0.000008706313984  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_BV_RIGHT             (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_BV_RIGHT              ( 5.736707843722940  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_BV_RIGHT              ( 5.793857219099250  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_BV_RIGHT              ( 7.890247255785330  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_BV_RIGHT              ( 10.385319991347300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_BV_RIGHT              ( 3.473570898086800  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_BV_RIGHT              ( 1.639085913921260  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_BV_RIGHT              ( 0.212623239515698  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_BV_RIGHT              ( 0.019166181098427  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_BV_RIGHT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_BV_RIGHT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_BV_RIGHT              ( 0.000476772121221  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_BV_RIGHT              (-0.209019429100946  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_BV_RIGHT              (-15.394517920725300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_BV_RIGHT              (-40.258368204572600 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_BV_RIGHT              (104.623015205560000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_BV_RIGHT              (168.575867907065000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_BV_RIGHT              (260.259270891694000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_BV_RIGHT              (295.410449204026000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_BV_RIGHT              ( 0.000001429266285  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_BV_RIGHT              ( 0.000001288098939  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_BV_RIGHT              ( 0.000005626226077  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_BV_RIGHT              ( 0.000045624996707  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_BV_RIGHT              ( 0.000418900794781  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_BV_RIGHT              ( 0.004752765847185  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_BV_RIGHT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_BV_RIGHT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_BV_RIGHT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_BV_RIGHT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_BV_RIGHT              (-0.000217081780096  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_BV_RIGHT              (-0.000203022034368  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_BV_RIGHT              (-0.001744673142783  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_BV_RIGHT              (-0.024221679592604   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_BV_RIGHT              (-0.292628050421520   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_BV_RIGHT              (-3.799512019032040  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_BV_RIGHT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_BV_RIGHT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_BV_RIGHT              ( 0.174170543584806  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_BV_RIGHT              ( 0.173754910212572  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_BV_RIGHT              ( 0.358121127158595  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_BV_RIGHT              ( 4.571450399114440    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_BV_RIGHT              ( 68.875099257686500   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_BV_RIGHT              ( 1014.377388771400000    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_BV_RIGHT              ( 31598.260528220600000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_BV_RIGHT              ( 31598.260528220600000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_BV_RIGHT             (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_BV_RIGHT              ( 0.000071353312696   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_BV_RIGHT              ( 0.003214847717227  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_BV_RIGHT              (-7.396291115997770   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_BV_RIGHT              (-270.787984417783000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_BV_RIGHT              (-5403.290246798560000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_BV_RIGHT              (-90340.644827611600000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_BV_RIGHT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_BV_RIGHT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_BV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_BV_RIGHT             (0.0)

/* SV Left/Right & LVDS LEFT is currently not ready & used. */
#define SIM_DEFAULT_FM_RESIZE_RATIO_SV_LEFT           (711.f/640.f)//width =711= 720 - 9(黑邊pixels)
#define SIM_DEFAULT_FM_COD_X_SV_LEFT                  (360)
#define SIM_DEFAULT_FM_COD_Y_SV_LEFT                  (240)
#define SIM_DEFAULT_FM_FOV_H_SV_LEFT                  (172.5)
#define SIM_DEFAULT_FM_SEGMENT_SV_LEFT                (8)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_SV_LEFT      (20)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_SV_LEFT      (40)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_SV_LEFT      (60)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_SV_LEFT      (70)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_SV_LEFT      (80)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_SV_LEFT      (84)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_SV_LEFT      (87.5)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_SV_LEFT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_SV_LEFT      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_SV_LEFT              (-0.001634180265152  )//0~20
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_SV_LEFT              (-0.001564989848485  )//20~40
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_SV_LEFT              (-0.000201588400019  )//40~60
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_SV_LEFT              ( 0.000651277716347  )//60~70
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_SV_LEFT              ( 0.000064853706746  )//70~80
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_SV_LEFT              ( 0.000013371583228  )//80~84
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_SV_LEFT              ( 0.000000238405575  )//84~87.5
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_SV_LEFT              ( 0.000000001343166  )//87.5UP
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_SV_LEFT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_SV_LEFT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_SV_LEFT              ( 0.044251162527058  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_SV_LEFT              ( 0.039846191918081  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_SV_LEFT              (-0.054097800426460  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_SV_LEFT              (-0.134986021478925  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_SV_LEFT              (-0.024889227459107  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_SV_LEFT              (-0.007851336572658  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_SV_LEFT              (-0.000374473803154  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_SV_LEFT              (-0.000008706313984  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_SV_LEFT             (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_SV_LEFT              ( 5.736707843722940  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_SV_LEFT              ( 5.793857219099250  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_SV_LEFT              ( 7.890247255785330  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_SV_LEFT              ( 10.385319991347300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_SV_LEFT              ( 3.473570898086800  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_SV_LEFT              ( 1.639085913921260  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_SV_LEFT              ( 0.212623239515698  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_SV_LEFT              ( 0.019166181098427  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_SV_LEFT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_SV_LEFT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_SV_LEFT              ( 0.000476772121221  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_SV_LEFT              (-0.209019429100946  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_SV_LEFT              (-15.394517920725300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_SV_LEFT              (-40.258368204572600 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_SV_LEFT              (104.623015205560000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_SV_LEFT              (168.575867907065000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_SV_LEFT              (260.259270891694000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_SV_LEFT              (295.410449204026000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_SV_LEFT              ( 0.000001429266285  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_SV_LEFT              ( 0.000001288098939  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_SV_LEFT              ( 0.000005626226077  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_SV_LEFT              ( 0.000045624996707  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_SV_LEFT              ( 0.000418900794781  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_SV_LEFT              ( 0.004752765847185  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_SV_LEFT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_SV_LEFT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_SV_LEFT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_SV_LEFT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_SV_LEFT              (-0.000217081780096  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_SV_LEFT              (-0.000203022034368  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_SV_LEFT              (-0.001744673142783  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_SV_LEFT              (-0.024221679592604   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_SV_LEFT              (-0.292628050421520   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_SV_LEFT              (-3.799512019032040  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_SV_LEFT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_SV_LEFT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_SV_LEFT              ( 0.174170543584806  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_SV_LEFT              ( 0.173754910212572  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_SV_LEFT              ( 0.358121127158595  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_SV_LEFT              ( 4.571450399114440    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_SV_LEFT              ( 68.875099257686500   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_SV_LEFT              ( 1014.377388771400000    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_SV_LEFT              ( 31598.260528220600000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_SV_LEFT              ( 31598.260528220600000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_SV_LEFT             (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_SV_LEFT              ( 0.000071353312696   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_SV_LEFT              ( 0.003214847717227  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_SV_LEFT              (-7.396291115997770   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_SV_LEFT              (-270.787984417783000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_SV_LEFT              (-5403.290246798560000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_SV_LEFT              (-90340.644827611600000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_SV_LEFT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_SV_LEFT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_SV_LEFT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_SV_LEFT             (0.0)

#define SIM_DEFAULT_FM_RESIZE_RATIO_SV_RIGHT           (711.f/640.f)//width =711= 720 - 9(黑邊pixels)
#define SIM_DEFAULT_FM_COD_X_SV_RIGHT                  (360)
#define SIM_DEFAULT_FM_COD_Y_SV_RIGHT                  (240)
#define SIM_DEFAULT_FM_FOV_H_SV_RIGHT                  (172.5)
#define SIM_DEFAULT_FM_SEGMENT_SV_RIGHT                (8)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_SV_RIGHT      (20)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_SV_RIGHT      (40)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_SV_RIGHT      (60)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_SV_RIGHT      (70)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_SV_RIGHT      (80)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_SV_RIGHT      (84)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_SV_RIGHT      (87.5)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_SV_RIGHT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_SV_RIGHT      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_SV_RIGHT              (-0.001634180265152  )//0~20
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_SV_RIGHT              (-0.001564989848485  )//20~40
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_SV_RIGHT              (-0.000201588400019  )//40~60
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_SV_RIGHT              ( 0.000651277716347  )//60~70
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_SV_RIGHT              ( 0.000064853706746  )//70~80
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_SV_RIGHT              ( 0.000013371583228  )//80~84
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_SV_RIGHT              ( 0.000000238405575  )//84~87.5
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_SV_RIGHT              ( 0.000000001343166  )//87.5UP
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_SV_RIGHT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_SV_RIGHT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_SV_RIGHT              ( 0.044251162527058  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_SV_RIGHT              ( 0.039846191918081  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_SV_RIGHT              (-0.054097800426460  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_SV_RIGHT              (-0.134986021478925  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_SV_RIGHT              (-0.024889227459107  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_SV_RIGHT              (-0.007851336572658  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_SV_RIGHT              (-0.000374473803154  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_SV_RIGHT              (-0.000008706313984  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_SV_RIGHT             (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_SV_RIGHT              ( 5.736707843722940  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_SV_RIGHT              ( 5.793857219099250  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_SV_RIGHT              ( 7.890247255785330  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_SV_RIGHT              ( 10.385319991347300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_SV_RIGHT              ( 3.473570898086800  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_SV_RIGHT              ( 1.639085913921260  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_SV_RIGHT              ( 0.212623239515698  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_SV_RIGHT              ( 0.019166181098427  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_SV_RIGHT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_SV_RIGHT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_SV_RIGHT              ( 0.000476772121221  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_SV_RIGHT              (-0.209019429100946  )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_SV_RIGHT              (-15.394517920725300 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_SV_RIGHT              (-40.258368204572600 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_SV_RIGHT              (104.623015205560000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_SV_RIGHT              (168.575867907065000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_SV_RIGHT              (260.259270891694000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_SV_RIGHT              (295.410449204026000 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_SV_RIGHT              ( 0.000001429266285  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_SV_RIGHT              ( 0.000001288098939  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_SV_RIGHT              ( 0.000005626226077  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_SV_RIGHT              ( 0.000045624996707  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_SV_RIGHT              ( 0.000418900794781  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_SV_RIGHT              ( 0.004752765847185  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_SV_RIGHT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_SV_RIGHT              ( 0.123394499726495  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_SV_RIGHT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_SV_RIGHT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_SV_RIGHT              (-0.000217081780096  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_SV_RIGHT              (-0.000203022034368  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_SV_RIGHT              (-0.001744673142783  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_SV_RIGHT              (-0.024221679592604   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_SV_RIGHT              (-0.292628050421520   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_SV_RIGHT              (-3.799512019032040  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_SV_RIGHT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_SV_RIGHT              (-108.134299063813000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_SV_RIGHT              ( 0.174170543584806  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_SV_RIGHT              ( 0.173754910212572  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_SV_RIGHT              ( 0.358121127158595  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_SV_RIGHT              ( 4.571450399114440    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_SV_RIGHT              ( 68.875099257686500   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_SV_RIGHT              ( 1014.377388771400000    )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_SV_RIGHT              ( 31598.260528220600000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_SV_RIGHT              ( 31598.260528220600000)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_SV_RIGHT             (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_SV_RIGHT              ( 0.000071353312696   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_SV_RIGHT              ( 0.003214847717227  )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_SV_RIGHT              (-7.396291115997770   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_SV_RIGHT              (-270.787984417783000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_SV_RIGHT              (-5403.290246798560000     )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_SV_RIGHT              (-90340.644827611600000   )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_SV_RIGHT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_SV_RIGHT              (-3078662.594204360000000 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_SV_RIGHT              (0.0)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_SV_RIGHT             (0.0)

#define SIM_DEFAULT_FM_RESIZE_RATIO_LVDS_FRONT           (1.0)
#define SIM_DEFAULT_FM_COD_X_LVDS_FRONT                  (640)
#define SIM_DEFAULT_FM_COD_Y_LVDS_FRONT                  (400)
#define SIM_DEFAULT_FM_FOV_H_LVDS_FRONT                  (80)
#define SIM_DEFAULT_FM_SEGMENT_LVDS_FRONT                (2)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_1_LVDS_FRONT      (30)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_2_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_3_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_4_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_5_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_6_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_7_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_8_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_ANGLE_THRESHOLD_9_LVDS_FRONT      (0)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_1_LVDS_FRONT              (-2.22208E-07)//(-3.6847E-07)//0~30
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_2_LVDS_FRONT              (3.57213E-10)//(-5.20345E-08)//30~
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_3_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_4_LVDS_FRONT              ( 0.0 )                
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_5_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_6_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_7_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_8_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_9_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_A_10_LVDS_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_1_LVDS_FRONT              (-0.00036319)//(-0.000161701)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_2_LVDS_FRONT              (-0.00056931)//(-0.000446096)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_3_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_4_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_5_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_6_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_7_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_8_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_9_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_B_10_LVDS_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_1_LVDS_FRONT              (1.250049792)//(1.172140208)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_2_LVDS_FRONT              (1.29754564)//(1.234687946)
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_3_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_4_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_5_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_6_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_7_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_8_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_9_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_C_10_LVDS_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_1_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_2_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_3_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_4_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_5_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_6_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_7_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_8_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_9_LVDS_FRONT              ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_UISTORTED2DISTORTED_D_10_LVDS_FRONT             ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_1_LVDS_FRONT            (7.93494E-07)//(7.73317E-07)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_2_LVDS_FRONT            (2.14797E-06)//(1.52119E-06)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_3_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_4_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_5_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_6_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_7_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_8_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_9_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_A_10_LVDS_FRONT           ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_1_LVDS_FRONT            (-0.000100753)//(-0.000143316)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_2_LVDS_FRONT            (-0.001373969)//(-0.000826816)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_3_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_4_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_5_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_6_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_7_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_8_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_9_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_B_10_LVDS_FRONT           ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_1_LVDS_FRONT            (0.834604976)//(0.879575188)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_2_LVDS_FRONT            (1.128601936)//(1.033730822)
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_3_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_4_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_5_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_6_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_7_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_8_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_9_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_C_10_LVDS_FRONT           ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_1_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_2_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_3_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_4_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_5_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_6_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_7_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_8_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_9_LVDS_FRONT            ( 0.0 )
#define SIM_DEFAULT_FM_PARAM_DISTORTED2UNDISTORTED_D_10_LVDS_FRONT           ( 0.0 )

/* Defalut M33 Configuration */
/* Wed Jul 10 16:29:23 2013 This file is automatically generated by the Program */ 
#define SIM_DEFAULT_FM11_W2I                            (-7.008450)
#define SIM_DEFAULT_FM12_W2I                            (105.770425)
#define SIM_DEFAULT_FM13_W2I                            (-12408.312164)
#define SIM_DEFAULT_FM21_W2I                            (-0.136483)
#define SIM_DEFAULT_FM22_W2I                            (68.394923)
#define SIM_DEFAULT_FM23_W2I                            (-9846.168008)
#define SIM_DEFAULT_FM31_W2I                            (-0.000297)
#define SIM_DEFAULT_FM32_W2I                            (0.293567)
#define SIM_DEFAULT_FM33_W2I                            (-41.381801)
#define SIM_DEFAULT_FM11_I2W                            (5.358694)
#define SIM_DEFAULT_FM12_I2W                            (65.361029)
#define SIM_DEFAULT_FM13_I2W                            (-17158.460743)
#define SIM_DEFAULT_FM21_I2W                            (-0.242485)
#define SIM_DEFAULT_FM22_I2W                            (25.487217)
#define SIM_DEFAULT_FM23_I2W                            (-5991.585304)
#define SIM_DEFAULT_FM31_I2W                            (-0.001759)
#define SIM_DEFAULT_FM32_I2W                            (0.180340)
#define SIM_DEFAULT_FM33_I2W                            (-41.381801)

#define SIM_DEFAULT_BM11_W2I                            (2.380371)
#define SIM_DEFAULT_BM12_W2I                            (-7.234356)
#define SIM_DEFAULT_BM13_W2I                            (1363.352862)
#define SIM_DEFAULT_BM21_W2I                            (-0.179590)
#define SIM_DEFAULT_BM22_W2I                            (-2.929772)
#define SIM_DEFAULT_BM23_W2I                            (809.669690)
#define SIM_DEFAULT_BM31_W2I                            (-0.000825)
#define SIM_DEFAULT_BM32_W2I                            (-0.019943)
#define SIM_DEFAULT_BM33_W2I                            (6.421996)
#define SIM_DEFAULT_BM11_I2W                            (2.070780)
#define SIM_DEFAULT_BM12_I2W                            (-14.957895)
#define SIM_DEFAULT_BM13_I2W                            (1446.240456)
#define SIM_DEFAULT_BM21_I2W                            (-0.376589)
#define SIM_DEFAULT_BM22_I2W                            (-12.739604)
#define SIM_DEFAULT_BM23_I2W                            (1686.126081)
#define SIM_DEFAULT_BM31_I2W                            (-0.000903)
#define SIM_DEFAULT_BM32_I2W                            (-0.041484)
#define SIM_DEFAULT_BM33_I2W                            (6.421996)

#define SIM_DEFAULT_LM11_W2I                            (10.332050)
#define SIM_DEFAULT_LM12_W2I                            (-0.666185)
#define SIM_DEFAULT_LM13_W2I                            (-4414.897589)
#define SIM_DEFAULT_LM21_W2I                            (4.986931)
#define SIM_DEFAULT_LM22_W2I                            (-1.734665)
#define SIM_DEFAULT_LM23_W2I                            (-2103.219349)
#define SIM_DEFAULT_LM31_W2I                            (0.028208)
#define SIM_DEFAULT_LM32_W2I                            (-0.007441)
#define SIM_DEFAULT_LM33_W2I                            (-10.943076)
#define SIM_DEFAULT_LM11_I2W                            (2.497089)
#define SIM_DEFAULT_LM12_I2W                            (19.159526)
#define SIM_DEFAULT_LM13_I2W                            (-4689.821989)
#define SIM_DEFAULT_LM21_I2W                            (-3.564027)
#define SIM_DEFAULT_LM22_I2W                            (8.597479)
#define SIM_DEFAULT_LM23_I2W                            (-214.525464)
#define SIM_DEFAULT_LM31_I2W                            (0.008860)
#define SIM_DEFAULT_LM32_I2W                            (0.043541)
#define SIM_DEFAULT_LM33_I2W                            (-10.943076)

#define SIM_DEFAULT_RM11_W2I                            (-3.442468)
#define SIM_DEFAULT_RM12_W2I                            (-1.098450)
#define SIM_DEFAULT_RM13_W2I                            (1028.103916)
#define SIM_DEFAULT_RM21_W2I                            (-1.565939)
#define SIM_DEFAULT_RM22_W2I                            (-0.165143)
#define SIM_DEFAULT_RM23_W2I                            (257.516067)
#define SIM_DEFAULT_RM31_W2I                            (-0.009610)
#define SIM_DEFAULT_RM32_W2I                            (-0.000695)
#define SIM_DEFAULT_RM33_W2I                            (2.380170)
#define SIM_DEFAULT_RM11_I2W                            (0.442607)
#define SIM_DEFAULT_RM12_I2W                            (-3.927337)
#define SIM_DEFAULT_RM13_I2W                            (233.725273)
#define SIM_DEFAULT_RM21_I2W                            (-2.588555)
#define SIM_DEFAULT_RM22_I2W                            (-3.485892)
#define SIM_DEFAULT_RM23_I2W                            (1495.261829)
#define SIM_DEFAULT_RM31_I2W                            (0.001031)
#define SIM_DEFAULT_RM32_I2W                            (-0.016875)
#define SIM_DEFAULT_RM33_I2W                            (2.380170)

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

/*  
    \brief Defalut calibration field setting. These setting are not included in ECU config files.
           These data only used when ini file is not existed. 
*/
#define SIM_DEFAULT_CHART_SETTING_FILE              L"CalSettingFile.ini"  // 校正場地設定檔
#define SIM_DEFAULT_CHART_SETTING_FINE_TUNE_FILE    L"CalSettingFineTune_SUV_DEMO.ini"  // 校正場地設定檔
#define SIM_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST       920     // 預設前輪中心至車頭距離
#define SIM_DEFAULT_CHART_HORI_DIST                 1860    // 左右 Chart 內側間距
#define SIM_DEFAULT_CHART_VERT_DIST                 4840    // 前後 Chart 內側間距
/*

                                                                SIM_DEFAULT_CHART_HORI_DIST
                                                    ______ ←───→ ______
                                                FW6|＋ ＋ |FW4    FW3| ＋ ＋| FW5
                                                   |   ＋ |          | ＋   |
                                                   |______|(左前)    |______|(右前)
                                                    ↑ FW2 ↑          FW1
          SIM_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST    ↓     ∣       
                                     ----------------------∣
                                (車輪中心)                 ∣SIM_DEFAULT_CHART_VERT_DIST
                                                           ∣
                                                       BW1 ∣          BW2
                                                    ______ ↓         ______
                                                   |   ＋ |(左後)    | ＋   |(右後)
                                                BW5|＋ ＋ |BW3    BW4| ＋ ＋|BW6
                                                   |______|          |______|
           
*/
#define SIM_DEFAULT_FW1                   600
#define SIM_DEFAULT_FH1                   450
#define SIM_DEFAULT_FW2                   600
#define SIM_DEFAULT_FH2                   450
#define SIM_DEFAULT_FW3                   600
#define SIM_DEFAULT_FH3                   1350
#define SIM_DEFAULT_FW4                   600
#define SIM_DEFAULT_FH4                   1350
#define SIM_DEFAULT_FW5                   1600
#define SIM_DEFAULT_FH5                   1200
#define SIM_DEFAULT_FW6                   1600
#define SIM_DEFAULT_FH6                   1200
#define SIM_DEFAULT_BW1                   750
#define SIM_DEFAULT_BH1                   450
#define SIM_DEFAULT_BW2                   750
#define SIM_DEFAULT_BH2                   450
#define SIM_DEFAULT_BW3                   750
#define SIM_DEFAULT_BH3                   1350
#define SIM_DEFAULT_BW4                   750
#define SIM_DEFAULT_BH4                   1350
#define SIM_DEFAULT_BW5                   1500
#define SIM_DEFAULT_BH5                   900
#define SIM_DEFAULT_BW6                   1500
#define SIM_DEFAULT_BH6                   900

/*  
    \brief Defalut offset of the fixed points position for calibration field setting. 
           These data only used when ini file is not existed. 
*/
// Front View
/*

               ＋             ＋
               (2)            (3)

               ＋             ＋
               (0)            (1)

*/
#define SIM_DEFAULT_FP_OFFSET_X_FRONT_0    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_FRONT_0    (0)
#define SIM_DEFAULT_FP_OFFSET_X_FRONT_1    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_FRONT_1    (0)
#define SIM_DEFAULT_FP_OFFSET_X_FRONT_2    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_FRONT_2    (0)
#define SIM_DEFAULT_FP_OFFSET_X_FRONT_3    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_FRONT_3    (0)

// Back View
/*

               ＋             ＋
               (1)            (0)

               ＋             ＋
               (3)            (2)

*/
#define SIM_DEFAULT_FP_OFFSET_X_BACK_0     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_BACK_0     (0)
#define SIM_DEFAULT_FP_OFFSET_X_BACK_1     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_BACK_1     (0)
#define SIM_DEFAULT_FP_OFFSET_X_BACK_2     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_BACK_2     (0)
#define SIM_DEFAULT_FP_OFFSET_X_BACK_3     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_BACK_3     (0)

// Left View
/*

               ＋       
               (3)     ＋
                       (1)

                       ＋
               ＋      (0)
               (2)

*/
#define SIM_DEFAULT_FP_OFFSET_X_LEFT_0     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_LEFT_0     (0)
#define SIM_DEFAULT_FP_OFFSET_X_LEFT_1     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_LEFT_1     (0)
#define SIM_DEFAULT_FP_OFFSET_X_LEFT_2     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_LEFT_2     (0)
#define SIM_DEFAULT_FP_OFFSET_X_LEFT_3     (0)
#define SIM_DEFAULT_FP_OFFSET_Y_LEFT_3     (0)

// Right View
/*

                       ＋    
               ＋     (2)
               (0)        

               ＋        
               (1)     ＋ 
                       (3)
                       
*/
#define SIM_DEFAULT_FP_OFFSET_X_RIGHT_0    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_RIGHT_0    (0)
#define SIM_DEFAULT_FP_OFFSET_X_RIGHT_1    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_RIGHT_1    (0)
#define SIM_DEFAULT_FP_OFFSET_X_RIGHT_2    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_RIGHT_2    (0)
#define SIM_DEFAULT_FP_OFFSET_X_RIGHT_3    (0)
#define SIM_DEFAULT_FP_OFFSET_Y_RIGHT_3    (0)

/* Default Config for Trailline */
#define SIM_DEFAULT_TL_STEER_ANGLE_INTERVAL     30          // in degree
#define SIM_DEFAULT_TL_LINE_WIDTH               5           // in pixel
#define SIM_DEFAULT_CAR_STEER_PARA_A            (0.0588f)	// 方向盤舵角與車輛轉向角關係式 φ= a * θ + b
#define SIM_DEFAULT_CAR_STEER_PARA_B            (-0.532f)	// 方向盤舵角與車輛轉向角關係式 φ= a * θ + b
//#define SIM_DEFAULT_CAR_CEN2LEFTMIRROR_DISTANCE 300         // 車幅線縱線從左、右後視鏡外緣向外延伸距離 in mm

/* static trail line - front */
#define SIM_DEFAULT_STL_F_ENABLE                 1
#define SIM_DEFAULT_STL_F_STYLE                  0       // (0: line, 1: hook, 2: linked)
#define SIM_DEFAULT_STL_F_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_STL_F_HORI_COUNT             4       
#define SIM_DEFAULT_STL_F_HORI_POS_1             (-((SIM_DEFAULT_CAR_LEN>>1) + 250))       // in mm
#define SIM_DEFAULT_STL_F_HORI_POS_2             (-((SIM_DEFAULT_CAR_LEN>>1) + 500))       // in mm
#define SIM_DEFAULT_STL_F_HORI_POS_3             (-((SIM_DEFAULT_CAR_LEN>>1) + 1000))      // in mm 
#define SIM_DEFAULT_STL_F_HORI_POS_4             (-((SIM_DEFAULT_CAR_LEN>>1) + 2000))      // in mm 
#define SIM_DEFAULT_STL_F_HORI_POS_5             0
#define SIM_DEFAULT_STL_F_COLOR_IDX_1            3      // Red
#define SIM_DEFAULT_STL_F_COLOR_IDX_2            6      // Yellow
#define SIM_DEFAULT_STL_F_COLOR_IDX_3            4      // Green
#define SIM_DEFAULT_STL_F_COLOR_IDX_4            0
#define SIM_DEFAULT_STL_F_COLOR_IDX_5            0
#define SIM_DEFAULT_STL_F_VERT_STYLE             0
#define SIM_DEFAULT_STL_F_VERT_COUNT             2
#define SIM_DEFAULT_STL_F_VERT_POS_1             (-1405)       // in mm : -(1105 + 300) 
#define SIM_DEFAULT_STL_F_VERT_POS_2             (1381)        // in mm : (1081 + 300)
#define SIM_DEFAULT_STL_F_DASH_LENGTH_HORI            (200)         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_1     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_2     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_3     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_4     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_5     0         // in mm

/* static trail line - back */
#define SIM_DEFAULT_STL_B_ENABLE                 1
#define SIM_DEFAULT_STL_B_STYLE                  2       // (0: line, 1: hook, 2: linked)
#define SIM_DEFAULT_STL_B_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_STL_B_HORI_COUNT             4       
#define SIM_DEFAULT_STL_B_HORI_POS_1             ((SIM_DEFAULT_CAR_LEN>>1) + 250)       // in mm
#define SIM_DEFAULT_STL_B_HORI_POS_2             ((SIM_DEFAULT_CAR_LEN>>1) + 500)       // in mm
#define SIM_DEFAULT_STL_B_HORI_POS_3             ((SIM_DEFAULT_CAR_LEN>>1) + 1000)      // in mm 
#define SIM_DEFAULT_STL_B_HORI_POS_4             ((SIM_DEFAULT_CAR_LEN>>1) + 2000)      // in mm 
#define SIM_DEFAULT_STL_B_HORI_POS_5             0
#define SIM_DEFAULT_STL_B_COLOR_IDX_1            3      // Red
#define SIM_DEFAULT_STL_B_COLOR_IDX_2            6      // Yellow
#define SIM_DEFAULT_STL_B_COLOR_IDX_3            4      // Green
#define SIM_DEFAULT_STL_B_COLOR_IDX_4            0
#define SIM_DEFAULT_STL_B_COLOR_IDX_5            0
#define SIM_DEFAULT_STL_B_VERT_STYLE             0
#define SIM_DEFAULT_STL_B_VERT_COUNT             2
#define SIM_DEFAULT_STL_B_VERT_POS_1             (-1405)        // in mm : -(1105 + 300)
#define SIM_DEFAULT_STL_B_VERT_POS_2             (1381)         // in mm : (1081 + 300)
#define SIM_DEFAULT_STL_B_DASH_LENGTH_HORI            (200)          // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_1     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_2     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_3     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_4     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_5     0         // in mm

/* dynamic trail line - front */
#define SIM_DEFAULT_DTL_F_ENABLE                 1
#define SIM_DEFAULT_DTL_F_STYLE                  0       // (0: without hori line, 1: with hori line)
#define SIM_DEFAULT_DTL_F_VERT_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_F_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_F_HORI_START_POS         (-((SIM_DEFAULT_CAR_LEN>>1) + 250))     // in mm: 車頭往前 250 mm
#define SIM_DEFAULT_DTL_F_HORI_END_POS           (-((SIM_DEFAULT_CAR_LEN>>1) + 2000))    // in mm: 車頭往前 2250 mm
#define SIM_DEFAULT_DTL_F_VERT_POS_1             (-1405) // in mm
#define SIM_DEFAULT_DTL_F_VERT_POS_2             (1381)  // in mm 
#define SIM_DEFAULT_DTL_F_COLOR_IDX_1            9       // Orange
#define SIM_DEFAULT_DTL_F_COLOR_IDX_2            9       // Orange      

/* dynamic trail line - back */
#define SIM_DEFAULT_DTL_B_ENABLE                 1
#define SIM_DEFAULT_DTL_B_STYLE                  1       // (0: without hori line, 1: with hori line)
#define SIM_DEFAULT_DTL_B_VERT_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_B_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_B_HORI_START_POS         (((SIM_DEFAULT_CAR_LEN>>1) + 250))     // in mm: 車尾往後 250 mm
#define SIM_DEFAULT_DTL_B_HORI_END_POS           (((SIM_DEFAULT_CAR_LEN>>1) + 2000))    // in mm: 車尾往後 2250 mm
#define SIM_DEFAULT_DTL_B_VERT_POS_1             (-1405) // in mm
#define SIM_DEFAULT_DTL_B_VERT_POS_2             (1381)  // in mm 
#define SIM_DEFAULT_DTL_B_COLOR_IDX_1            9       // Orange
#define SIM_DEFAULT_DTL_B_COLOR_IDX_2            9       // Orange

/* warning trail line - front */
#define SIM_DEFAULT_WTL_F_ENABLE                 0
#define SIM_DEFAULT_WTL_F_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_F_LINE_1_COLOR           3       // Red       
#define SIM_DEFAULT_WTL_F_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_F_LINE_1_POS_1_X         (-1105)
#define SIM_DEFAULT_WTL_F_LINE_1_POS_1_Y         (-((SIM_DEFAULT_CAR_LEN>>1) + 400))       // in mm   // in mm
#define SIM_DEFAULT_WTL_F_LINE_1_POS_2_X         (1081)
#define SIM_DEFAULT_WTL_F_LINE_1_POS_2_Y         (-((SIM_DEFAULT_CAR_LEN>>1) + 400))       // in mm   // in mm
#define SIM_DEFAULT_WTL_F_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_F_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_2_PIECE           0	     // (number of dash line)	
#define SIM_DEFAULT_WTL_F_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_F_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_F_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_F_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_F_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_F_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_3_PIECE           0	     // (number of dash line)	
#define SIM_DEFAULT_WTL_F_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_F_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_F_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_F_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_F_LINE_4_COLOR           0       
#define SIM_DEFAULT_WTL_F_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_4_PIECE           0	     // (number of dash line)	
#define SIM_DEFAULT_WTL_F_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_F_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_F_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_F_LINE_4_POS_2_Y         0

/* warning trail line - back */
#define SIM_DEFAULT_WTL_B_ENABLE                 0
#define SIM_DEFAULT_WTL_B_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_B_LINE_1_COLOR           3       // Red        
#define SIM_DEFAULT_WTL_B_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_1_POS_1_X         (-1105)
#define SIM_DEFAULT_WTL_B_LINE_1_POS_1_Y         ((SIM_DEFAULT_CAR_LEN>>1) + 200)       // in mm
#define SIM_DEFAULT_WTL_B_LINE_1_POS_2_X         (1081)
#define SIM_DEFAULT_WTL_B_LINE_1_POS_2_Y         ((SIM_DEFAULT_CAR_LEN>>1) + 200)       // in mm
#define SIM_DEFAULT_WTL_B_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_B_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_2_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_B_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_B_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_B_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_B_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_B_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_3_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_B_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_B_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_B_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_B_LINE_4_COLOR           0       
#define SIM_DEFAULT_WTL_B_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_4_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_B_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_B_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_B_LINE_4_POS_2_Y         0

/* warning trail line - left */
#define SIM_DEFAULT_WTL_L_ENABLE                 0
#define SIM_DEFAULT_WTL_L_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_L_LINE_1_COLOR           0       
#define SIM_DEFAULT_WTL_L_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_1_POS_1_X         (-1500)
#define SIM_DEFAULT_WTL_L_LINE_1_POS_1_Y         (-(SIM_DEFAULT_CAR_LEN>>1))       // in mm
#define SIM_DEFAULT_WTL_L_LINE_1_POS_2_X         (-1500)
#define SIM_DEFAULT_WTL_L_LINE_1_POS_2_Y         ( (SIM_DEFAULT_CAR_LEN>>1))       // in mm
#define SIM_DEFAULT_WTL_L_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_L_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_2_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_L_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_L_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_L_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_L_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_L_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_3_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_L_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_L_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_L_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_L_LINE_4_COLOR           0      
#define SIM_DEFAULT_WTL_L_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_4_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_L_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_L_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_L_LINE_4_POS_2_Y         0

/* warning trail line - right */
#define SIM_DEFAULT_WTL_R_ENABLE                 0
#define SIM_DEFAULT_WTL_R_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_R_LINE_1_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_1_POS_1_X         (1500)
#define SIM_DEFAULT_WTL_R_LINE_1_POS_1_Y         (-(SIM_DEFAULT_CAR_LEN>>1))       // in mm
#define SIM_DEFAULT_WTL_R_LINE_1_POS_2_X         (1500)
#define SIM_DEFAULT_WTL_R_LINE_1_POS_2_Y         ( (SIM_DEFAULT_CAR_LEN>>1))       // in mm
#define SIM_DEFAULT_WTL_R_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_2_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_R_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_R_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_R_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_R_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_3_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_R_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_R_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_R_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_R_LINE_4_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_4_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_R_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_R_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_R_LINE_4_POS_2_Y         0


/**
  *  @}
  */
