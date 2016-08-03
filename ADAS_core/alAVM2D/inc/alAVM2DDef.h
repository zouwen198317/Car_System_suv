#pragma once

#include "mtype.h"    
#include "atype.h"   
#include "alCameraInfo.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \addtogroup alAVM2D
*  @{
*/
  
  
/* alAVM2D Configuration */
/** \brief alAVM2D - 啟用/禁用 - 0: Disabled,  1: Enabled */
#define SIM_DEFAULT_alAVM2D_FUNCTION_ENABLED                          1      
    /** \brief alAVM2D - 最大可視範圍距離 */
#define SIM_DEFAULT_alAVM2D_MAXIMUM_DISTANCE                          2500
    /** \brief alAVM2D - 前方延伸遮蔽區(軟體盲區)(mm) */
#define SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_FRONT         100 // 250        
    /** \brief alAVM2D - 後方延伸遮蔽區(軟體盲區)(mm) */
#define SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_BACK          200        
    /** \brief alAVM2D - 左方延伸遮蔽區(軟體盲區)(mm) */
#define SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_LEFT          50 // 0           
    /** \brief alAVM2D - 右方延伸遮蔽區(軟體盲區)(mm) */
#define SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_RIGHT         50     // 0      
    /** \brief alAVM2D - Start Point on destination buffer - X */
#define SIM_DEFAULT_alAVM2D_DEST_START_POINT_X                        0
    /** \brief alAVM2D - Start Point on destination buffer - Y */
#define SIM_DEFAULT_alAVM2D_DEST_START_POINT_Y                        0
    /** \brief alAVM2D - Destination Buffer Size - X */
#define SIM_DEFAULT_alAVM2D_DEST_IMAGE_BUFFER_SIZE_X                  720   
    /** \brief alAVM2D - Destination Buffer Size - X */
#define SIM_DEFAULT_alAVM2D_DEST_IMAGE_BUFFER_SIZE_Y                  480

    /** \brief alAVM2D - Stitch Line Start Point #0 - X */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_0_X                     -1016 // -1020
    /** \brief alAVM2D - Stitch Line Start Point #0 - Y */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_0_Y                     -2230 // -2731
    /** \brief alAVM2D - Stitch Line Start Point #1 - X */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_1_X                     1016
    /** \brief alAVM2D - Stitch Line Start Point #1 - Y */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_1_Y                     -2230
    /** \brief alAVM2D - Stitch Line Start Point #2 - X */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_2_X                     -1016
    /** \brief AVM2 - Stitch Line Start Point #2 - Y */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_2_Y                     2230
    /** \brief alAVM2D - Stitch Line Start Point #3 - X */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_3_X                     1016
    /** \brief alAVM2D - Stitch Line Start Point #3 - Y */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_3_Y                     2230

    /** \brief alAVM2D - Stitch Line Angle #0 */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_0                      200 //  225
    /** \brief alAVM2D - Stitch Line Angle #1 */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_1                       340 // 315
    /** \brief alAVM2D - Stitch Line Angle #2 */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_2                       155
    /** \brief alAVM2D - Stitch Line Angle #3 */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_3                       25
    /** \brief alAVM2D - Overlapping Angle of the stitching area - 從 Stitch Line 角度，再往兩側各延伸此一角度範圍，因此重疊區為此角度的兩倍 */
#define SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_RANGE                   10

    /** \brief alAVM2D - ROI pixel width for Global AE - Must be even value */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_NUMBER_X                    46 // 30          
    /** \brief alAVM2D - ROI pixel height for Global AE - Must be even value */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_NUMBER_Y                    46 // 30
    /** \brief alAVM2D - ROI pixel offset for Global AE - X */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_OFFSET_X                    1
    /** \brief alAVM2D - ROI pixel offset for Global AE - Y */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_OFFSET_Y                    1
    /** \brief alAVM2D - ROI position offset from front-left corner of car picture - X */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_X    -5
    /** \brief alAVM2D - ROI position offset from front-left corner of car picture - Y */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_Y    0
    /** \brief alAVM2D - ROI position offset from front-right corner of car picture - X */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_X   5
    /** \brief alAVM2D - ROI position offset from front-right corner of car picture - Y */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_Y   0
    /** \brief alAVM2D - ROI position offset from rear-left corner of car picture - X */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_X     -5
    /** \brief alAVM2D - ROI position offset from rear-left corner of car picture - Y */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_Y     0
    /** \brief alAVM2D - ROI position offset from rear-right corner of car picture - X */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_X    5
    /** \brief alAVM2D - ROI position offset from rear-right corner of car picture - Y */
#define SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_Y    0
    /** \brief alAVM2D - ROI position offset from rear-right corner of car picture - Y */
#define SIM_DEFAULT_alAVM2D_BLOCK_SET_DISTANCE    150

/** \brief Define the config data for each view of the 2D around view overlap region . */
typedef struct
{
	/** \brief alDistanceCurveA[0]~[3] : FrontLeft FrontRight BacktLeft BackRight*/
	INT32 alDistanceCurveA[4][2];

	/** \brief alDistanceCurveB[0]~[3] : FrontLeft FrontRight BacktLeft BackRight*/
	INT32 alDistanceCurveB[4][2];

	/** \brief The degree offset range of the curveA's line. 由該區水平線的張角*/
	FLOAT32 afCurveALineAngleOffset[4];
	/** \brief The degree offset range of the curveB's line. 由該區垂直線的張角*/
	FLOAT32 afCurveBLineAngleOffset[4];

} alAVM2D_OverlapLoadCfg;

/** \brief Define the config data of the 2D around view monitor . */
typedef struct
{
    /** \brief Indicate if this function is enabled. (Should we genreate the LUT?) */
    UINT8               ucFunctionEnabled;

    /** \brief The maximum viewing distance of the birdview. (最大可視距離, default: 3500 m) */
    UINT32              ulBVMaxDistance;
    /** \brief The front blind distance of BV. (前方軟體盲區距離) */
    UINT32              ulBVBlindDistanceFront;
    /** \brief The rear blind distance of BV. (後方軟體盲區距離) */
    UINT32              ulBVBlindDistanceBack;
    /** \brief The left blind distance of BV. (左方軟體盲區距離) */
    UINT32              ulBVBlindDistanceLeft;
    /** \brief The right blind distance of BV. (右方軟體盲區距離) */
    UINT32              ulBVBlindDistanceRight;

	/** \brief The start point of the DestImage in the buffer area. */
    alPointINT32       tDestStartPoint;
    /** \brief The calculated DestImage area size. Height = Height of tDisplayAreaSize, Width is calculated by display height and car length, DestImage viewing range.  */
    alPointINT32       tDestImageBufferSize;

    /** \brief The type of stitch line. */
    UINT8               ucStitchLineType;

#if 0  // 先拿掉alAVM2D導R角參數
	/** \brief The DISTANCE setting of block region (黑區導角內縮長度) */
    INT32   lBlockDistance;
#endif

	/** \brief The Cfg for new overlap region algorithm*/
	alAVM2D_OverlapLoadCfg tOverlapLoadCfg;

	/** \brief The start point of the four stitch line. */
    alPointINT32       atStitchLineStart[4];
    /** \brief The angle of the four stitch line. 0 度為正右方，往下為正角度 */
    FLOAT32             afStitchLineAngle[4];
    /** \brief The degree range of the overlapped image. */
    FLOAT32             fStitchAngleRange;

    /** \brief The ROI pixel size for Global AE. */
    alPointINT32       tBVGAE_ROIPixelNumber;
    /** \brief The ROI pixel offset for Global AE. */
    alPointINT32       tBVGAE_ROIPixelOffset;
    /** \brief The offset between Global AE ROI and Car Pic - Front-Left */
    alPointINT32       tBVGAE_ROIFrontLeftOffse2CarPict;
    /** \brief The offset between Global AE ROI and Car Pic - Front-Right */
    alPointINT32       tBVGAE_ROIFrontRightOffse2CarPict;
    /** \brief The offset between Global AE ROI and Car Pic - Rear-Left */
    alPointINT32       tBVGAE_ROIRearLeftOffse2CarPict;
    /** \brief The offset between Global AE ROI and Car Pic - Rear-Right */
    alPointINT32       tBVGAE_ROIRearRightOffse2CarPict;

} alAVM2D_Cfg;

/** \brief Define the parameter data of the 2D around view monitor . */
typedef struct
{
	/** \brief The micro-meter per-pixel of the bird view image. */
    FLOAT32             fMMPP;
    /** \brief The start point of the birdview image in the buffer area. */
    alPointINT32       tBirdViewStartPoint;
    /** \brief The calculated birdview area size. Height = Height of tDisplayAreaSize, Width is calculated by display height and car length, birdview viewing range.  */
    alPointINT32       tBirdViewAreaSize;
	/** \brief The start points of central car picture. */
	alPointINT32       tCarPicCornerPos;
    /** \brief The area size of central car picture.  */
	alPointINT32       tCarPicAreaSize;
    /** \brief The top-left point of car on birdview image. (in pixel) */
	alPointINT32       tCarTopLeft;
    /** \brief The bottom-right point of car on birdview image. (in pixel) */
	alPointINT32       tCarBottomRight;
    /** \brief The corner points of front-left stitching line. (in pixel), 0 為近端, 1 為遠端  */
    alPointINT32       atStitchPoint_FrontLeft[2];           
    /** \brief The corner points of front-right stitching line. (in pixel), 0 為近端, 1 為遠端  */
    alPointINT32       atStitchPoint_FrontRight[2];          
    /** \brief The corner points of rear-left stitching line. (in pixel), 0 為近端, 1 為遠端  */
    alPointINT32       atStitchPoint_BackLeft[2];       
    /** \brief The corner points of rear-right stitching line. (in pixel), 0 為近端, 1 為遠端  */
    alPointINT32       atStitchPoint_BackRight[2];

} alAVM2D_Params;


/** \brief Load default confg for alAVM2D */
void alAVM2D_LoadDefault(alAVM2D_Cfg    *a_ptalAVM2D_Cfg);


/** \brief Load confg from INI for alAVM2D */
void alAVM2D_CfgImportByINIFile(wchar_t * a_pwcConfigFilePath, alAVM2D_Cfg *a_ptCfg);

/** \brief Load confg from hex data for alAVM2D */
void alAVM2D_CfgImportByHexData(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 *a_pucBuffer, alAVM2D_Cfg  *a_ptalAVM2D_Cfg);


/**
\brief Export AVM2D Cfg data.
\param a_ulDataID [IN] ID of the current data.
\param a_ulDataLength [IN] Data length of the current data.
\param a_pucDataBuf [IN] Buffer array of the current data.
\param a_ptCfg [INOUT] Configure data.
\return Total Size.
*/
UINT32 alAVM2D_CfgExportByHexData(
    UINT32 a_ulSectionID,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg,
    UINT8 *a_pucDataSectionBuffer
    );

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
