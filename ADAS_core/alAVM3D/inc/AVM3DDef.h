#pragma once

#include "mtype.h"
#include "atype.h"   
#include "alFM_v2_1_Default.h" 
#include "alLUT_v2_Def.h"
#include "alPartLUT_v2.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \addtogroup AVM3D
*  @{
*/

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


/** \brief 1:ON  0:OFF */
#define 	AVM3D_DEBUG_FALG 1 // 1:ON  0:OFF

/** \brief max virtual view number  */
#define 	AVM3D_MAX_VIEW_ANGLE_CNT   20

/** \brief max virtual view number during morphing  */
#define 	AVM3D_MAX_VIEW_MORPHING_CNT  36

/** \brief The index to indicate the current used camera. */
typedef enum 
{
    MORPHING_LINEAR    = 0,
    MORPHING_CIRCLE    = 1,
    MORPHING_BEZIER    = 2
} MORPHING_TYPE;

/** \brief Define the config data for each view of the 3D around view overlap region . */
typedef struct
{
	/// for new overlap region algorithm ///
	/** \brief alDistanceCurveA[0]~[3] : FrontLeft FrontRight BacktLeft BackRight*/
	INT32 alDistanceCurveA[4][2];

	/** \brief alDistanceCurveB[0]~[3] : FrontLeft FrontRight BacktLeft BackRight*/
	INT32 alDistanceCurveB[4][2];

	/** \brief afBezierWeight[0]~[3] : FrontLeft FrontRight BacktLeft BackRight*/
	FLOAT32 afBezierWeight[4][2];

	/** \brief The degree offset range of the curveA's line. パ赣跋キ絬眎à*/
	FLOAT32 afCurveALineAngleOffset[4];
	/** \brief The degree offset range of the curveB's line. パ赣跋絬眎à*/
	FLOAT32 afCurveBLineAngleOffset[4];
	/// for new overlap region algorithm ///
} alAVM3D_OverlapLoadCfg;

typedef struct 
{
    /** \brief The Rotation Matrix of the virtual camera. (0:BV2VC 1:VC2BV)  */
    FLOAT64 aeRotationMatrixVC[2][9];

    /** \brief The Translation Matrix of the virtual camera. (0:BV2VC 1:VC2BV)  */
    FLOAT64 aeTranslationMatrixVC[2][3];

    /** \brief The fish eye model of Virtual camera  */
    alFM_v2_1_Model *ptFisheyeModelVC;

    /** \brief The meet point of curve  0:X 1:Y 2:Z, world coordinates. (mm) */
    FLOAT64 tCurveMeetPoint[9][3];
    
    /** \brief The VC image center with offset, based on AVM3D area size. (pixel) */
    alPointINT32 tVC_CenterCoordinate;

    /** \brief The Theta angle (degree) */
    FLOAT64 eTheta[8];

    /** \brief The Phi angle (degree) */
    FLOAT64 ePhi[8];

} alAVM3D_ParamsSingle;


typedef struct
{
    /** \brief Define the params for each view. */
    alAVM3D_ParamsSingle atViewParams[AVM3D_MAX_VIEW_ANGLE_CNT];
} alAVM3D_Params;

/** \brief Define the config data for each view of the 3D around view monitor . */
typedef struct
{
    /** \brief Name of view. INT32 x 8 */
    CHAR acName[32];

    /** \brief Buffer size of the destination image. */
    alPointINT32   tDestImageBufferSize;

    /** \brief Start point of the output AVM image on the destination buffer. */
    alPointINT32   tDestStartPoint;
    /** \brief Area size of the output AVM image. */
    alPointINT32   tDestAreaSize;
    
    /** \brief Position of virtual camera - X. */
    INT32           lVirtualCameraPosX;
    /** \brief Position of virtual camera - Y. */
    INT32           lVirtualCameraPosY;
    /** \brief Position of virtual camera - Z. */
    INT32           lVirtualCameraPosZ;

    /** \brief Custom Roll Angle of virtual camera - for rear 3D view angle. */
    FLOAT32         fVirtualCameraCustomRoll;

    /** \brief Pitch Angle of virtual camera. */
    FLOAT32         fVirtualCameraPitch;
    /** \brief Yaw Angle of virtual camera. */
    FLOAT32         fVirtualCameraYaw;
    /** \brief Roll Angle of virtual camera. */
    FLOAT32         fVirtualCameraRoll;

#if 1 // for around view morphing
	 /** \brief Position of TopView (for around view mirphing) - X. */
    INT32           lTopViewPosX;
    /** \brief Position of TopView (for around view mirphing)- Y. */
    INT32           lTopViewPosY;
    /** \brief Position of TopView (for around view mirphing)- Z. */
    INT32           lTopViewPosZ;

	/** \brief Custom Roll Angle of TopView (for around view mirphing)*/
    FLOAT32         fTopViewCustomRoll;

    /** \brief Pitch Angle of TopView. (for around view mirphing)*/
    FLOAT32         fTopViewPitch;
    /** \brief Yaw Angle of TopView(for around view mirphing) */
    FLOAT32         fTopViewYaw;
    /** \brief Roll Angle of TopView (for around view mirphing)*/
    FLOAT32         fTopViewRoll;

	/** \brief flag of table generate 0:enable 1:disable */
    INT32           lLUTGenFlag;

	/** \brief height limit of vittual camera 0:disable else: limit with that height */
    INT32           lHeightLimit;
#endif

    /** \brief The flag of the fisheye 3D model for this virtual camera. */
    alFM_v2_1_DefaultCameraModel ucVCFisheyeModel;

    /** \brief Is the output image should be mirrored. */
    INT32           lMirror;

    /** \brief The scaling of X on destination image. */
    FLOAT64         eScalingX;
    /** \brief The scaling of Y on destination image. */
    FLOAT64         eScalingY;
    /** \brief The offset of X on destination image. */
    INT32           lOffsetX; // mm
    /** \brief The offset of X on destination image. */
    INT32           lOffsetY; // mm

    /** \brief The start point of the four stitch line. 0:LeftFront 1:RightFront 2:LeftBack 3:RightBack*/
    alPointINT32   atStitchLineStart[4];
    /** \brief The angle of the four stitch line.(0:LeftFront 1:RightFront 2:LeftBack 3:RightBack) 0 タよ┕タà ヘ玡 狦à筁熬┪熬オ穦岿*/
    FLOAT32         afStitchLineAngle[4];
    /** \brief The degree range of the overlapped image. パStitchLineAngle眎秨AngleRangeà*/
    FLOAT32         fStitchAngleRange;


	/// for new overlap region algorithm ///
	/** \brief The Gfg for new overlap region algorithm*/
	alAVM3D_OverlapLoadCfg tOverlapLoadCfg;
	/// for new overlap region algorithm ///


	/** \brief The parameter A of projection Surface. */
    FLOAT64           eCurveSurfaceA;  // Ρ把计 A
	/** \brief The parameter B of projection Surface. */
    FLOAT64           eCurveSurfaceB;  // Ρ把计 B
	/** \brief The parameter C of projection Surface. */
    FLOAT64           eCurveSurfaceC;  // Ρ把计 C
	/** \brief The parameter D of projection Surface. */
    FLOAT64           eCurveSurfaceD;  // Ρ把计 D
	/** \brief The parameter E of projection Surface. */
    FLOAT64           eCurveSurfaceE;  // Ρ把计 E
	/** \brief The parameter F of projection Surface. */
    FLOAT64           eCurveSurfaceF;  // Ρ把计 F

    /** \brief The origin point of the curve surface - X. */
    FLOAT32         fCurveCenterX;    // Ρいみ竚 - X
    /** \brief The origin point of the curve surface - Y. */
    FLOAT32         fCurveCenterY;    // Ρいみ竚 - Y
    /** \brief The origin point of the curve surface - Z. */
    FLOAT32         fCurveCenterZ;    // Ρいみ竚 - Z

    /** \brief The parameter A of CURVE2 FLAG. */
    INT32           lCURVE2_FLAG;
    /** \brief The z position of the project center. Close to zero will cause more distortion. (璽) */
    INT32           lCurve2ProjCenZ;
    /** \brief The parameter A of projection 2th Surface. */
    FLOAT64         eCurve2SurfaceA;  // Ρ把计 A
    /** \brief The parameter B of projection 2th Surface. */
    FLOAT64         eCurve2SurfaceB;  // Ρ把计 B
    /** \brief The parameter C of projection 2th Surface. */
    FLOAT64         eCurve2SurfaceC;  // Ρ把计 C
    /** \brief The parameter D of projection 2th Surface. */
    FLOAT64         eCurve2SurfaceD;  // Ρ把计 D
    /** \brief The parameter E of projection 2th Surface. */
    FLOAT64         eCurve2SurfaceE;  // Ρ把计 E
    /** \brief The parameter F of projection 2th Surface. */
    FLOAT64         eCurve2SurfaceF;  // Ρ把计 F

    /** \brief The origin point of the curve 2th surface - X. */
    FLOAT32         fCurve2CenterX;    // Ρいみ竚 - X
    /** \brief The origin point of the curve 2th surface - Y. */
    FLOAT32         fCurve2CenterY;    // Ρいみ竚 - Y
    /** \brief The origin point of the curve 2th surface - Z. */
    FLOAT32         fCurve2CenterZ;    // Ρいみ竚 - Z


    /** \brief The corner point of car. 0:LeftFront 1:RightFront 2:LeftBack 3:RightBack*/
    alPointINT32    atCornerPoint[4];

    /** \brief The Stitch line Type */
    INT32           lStitchLineType;

	/** \brief The DISTANCE setting of block region (堵跋旧àず罽) */
    INT32           lBlockDistance;
} alAVM3D_CfgSingleView;

/** \brief Define the config set for whole AVM3D. */
typedef struct
{

    /** \brief Indicate the count of enabled AVM3D views. */
    INT32 lViewCnt;

    /** 
        \brief Specified the warning line position in AVM3DBack_s if exists. 
               alWarningLineOfAVM3DBack_s[0][0] : distance to car bumper of 1st line
               alWarningLineOfAVM3DBack_s[0][1] : distance to car side of 1st line
               alWarningLineOfAVM3DBack_s[1][0] : distance to car bumper of 2nd line
               alWarningLineOfAVM3DBack_s[1][1] : distance to car side of 2nd line
    */
    INT32 alWarningLineOfAVM3DBack_s[2][2];

    /** 
        \brief Specified the warning line position in AVM3DBack_s if exists. 
               alWarningLineOfAVM3DBack_f[0][0] : distance to car bumper of 1st line
               alWarningLineOfAVM3DBack_f[0][1] : distance to car side of 1st line
               alWarningLineOfAVM3DBack_f[1][0] : distance to car bumper of 2nd line
               alWarningLineOfAVM3DBack_f[1][1] : distance to car side of 2nd line
    */
    INT32 alWarningLineOfAVM3DBack_f[2][2];

    /** \brief Define the config for each view. */
    alAVM3D_CfgSingleView atViewCfg[AVM3D_MAX_VIEW_ANGLE_CNT];  

} alAVM3D_Cfg;

/** \brief Define the TABLE set for whole AVM3D Morphing. */
typedef struct 
{
	/** \brief The Morphing flag  */
    INT32 lFlag;

    /** \brief The Morphing frame number  */
    INT32 lFrameNum;

	/** \brief The source view index of Morphing. (0:src 1:dest)  */
    INT32 alRefViewIndex[2];
	
	/** \brief The AVM3D LUT of Morphing */
#ifdef WIN32    
    alLUT_v2_Def *a_atMorphing_LUT[AVM3D_MAX_VIEW_MORPHING_CNT];
#else
    PartLUT_v2_Def *a_atMorphing_LUT[AVM3D_MAX_VIEW_MORPHING_CNT];
#endif
} AVM3D_MorphingLUT;


/** \brief Define the TABLE set for whole AVM3D Morphing. */
typedef struct 
{
	/** \brief The Morphing Number  */
    INT32 lMorphingNum;
	
	/** \brief The AVM3D LUT index array of Morphing */
	UINT8 alMorphingFlagTable[AVM3D_MAX_VIEW_ANGLE_CNT*AVM3D_MAX_VIEW_ANGLE_CNT]; // local table

	/** \brief AVM3D Morphing LUT Array */
	AVM3D_MorphingLUT atMorphingLUTArray[AVM3D_MAX_VIEW_ANGLE_CNT];
} alAVM3D_MorphingStruct;

/** \brief Define the setting for AVM3D Morphing. (in INI and hex) */
typedef struct 
{
	/** \brief The Morphing Src view index  */
    INT32 lSrcIndex;
	
	/** \brief The Morphing Src view index  */
    INT32 lDestIndex;

	/** \brief The Morphing Frame number  */
    INT32 lFrameNumber;

	/** \brief The Morphing Table index  */
    INT32 lTableIndex;

	/** \brief The Morphing type  */
    INT32 lMorphingType;
} alAVM3D_MorphingSet;

/** \brief Define the main setting for AVM3D Morphing. (in INI and hex) */
typedef struct 
{
	/** \brief The Morphing Number  */
    INT32 lMorphingNum;
	
	/** \brief Each AVM3D Morphing setting */
	alAVM3D_MorphingSet atMorphingSet[AVM3D_MAX_VIEW_ANGLE_CNT];
} alAVM3D_MorphingCfgStruct;



/**
\brief Load default confg for AVM3D Parameters for Type 1 Stitch Line.
\param a_ptOverlapCfg [OUT] The structure to store the config data.
*/
void AVM3D_OverlapLoadCfgLoadDefault(alAVM3D_OverlapLoadCfg * a_ptOverlapCfg);

/** \brief Load default confg for AVM3D */
void AVM3D_LoadDefault(alAVM3D_Cfg *a_ptAVM3D_tCfg, alAVM3D_MorphingCfgStruct *a_ptMorphingCfg);

/** \brief Load confg from INI for alAVM3D */
void alAVM3D_CfgImportByINIFile(wchar_t * a_pwcConfigFilePath, alAVM3D_Cfg *a_ptCfg);


/** \brief Load confg from INI for alAVM3D morphing */
void alAVM3D_MORPHING_CfgImportByINI(wchar_t * a_pwcConfigFilePath, alAVM3D_MorphingCfgStruct *a_ptMorphingCfg);




/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
