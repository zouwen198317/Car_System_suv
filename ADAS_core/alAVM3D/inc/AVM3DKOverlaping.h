
#pragma once

#include "mtype.h"
#include "AVM3DDef.h"
#include "alFM_v2_1.h"
#include "alLUT_v2_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \addtogroup AVM3D
*  @{
*/

typedef struct
{
    FLOAT64        fStartPointX;
    FLOAT64        fStartPointY;
    FLOAT32        fRatio;
    FLOAT32        fdegree;
    FLOAT32        fOffset; // y = fRatio * x + fOffset and fRatio = tan(fdegree)
    FLOAT32        fVx; // 直線向量 - x
    FLOAT32        fVy; // 直線向量  - y
} AVM3D_Line;

typedef struct
{

    AVM3D_Line tStitchLine[12];
    FLOAT64    fStitchRegionAngel[4];

} AVM3D_StitchLineCfg;



typedef struct
{
	INT32 lCornerIndex;
	AVM3D_Line tLawLine; // 法線 

    AVM3D_Line atStitchLineA[2]; // 0: 水平 1: 斜線
	AVM3D_Line atStitchLineB[2]; // 0: 垂直 1: 斜線

	AVM3D_Line tLineBezierA;
	AVM3D_Line tLineBezierB;

	alPointINT32 tBezierPointA;
	alPointINT32 tBezierPointB;

	FLOAT64 eBezierTA;
	FLOAT64 eBezierTB;

	FLOAT64 eCurveDistanceA;
	FLOAT64 eCurveDistanceB;

	FLOAT32 fBezierWeightA;
	FLOAT32 fBezierWeightB;

	FLOAT32 fAngleA;
	FLOAT32 fAngleB;
	FLOAT32 fAngleStitch;

	alPointINT32 atPointA[3];
	alPointINT32 atPointB[3];
	alPointINT32 tStitchStart;

} AVM3D_OverLap;


typedef enum 
{
    AVM3D_STITCH_REGION_BLOCK       = 0,
    AVM3D_STITCH_REGION_FRONTLEFT   = 1,
    AVM3D_STITCH_REGION_LEFT        = 2,
    AVM3D_STITCH_REGION_LEFTBACK    = 3,
    AVM3D_STITCH_REGION_BACK        = 4,
    AVM3D_STITCH_REGION_RIGHTBACK   = 5,
    AVM3D_STITCH_REGION_RIGHT       = 6,
    AVM3D_STITCH_REGION_FRONTRIGHT  = 7,
    AVM3D_STITCH_REGION_FRONT       = 8,

    AVM3D_STITCH_REGION_ERROR       = 99,
} AVM3D_STITCH_REGION;

typedef enum 
{
    AVM3D_WEIGHT_MODE_BLOCK			= 0,
    AVM3D_WEIGHT_MODE_VIEW_0		= 1,
    AVM3D_WEIGHT_MODE_VIEW_1		= 2,
    AVM3D_WEIGHT_MODE_SINGLEVIEW	= 3,
    AVM3D_WEIGHT_MODE_OVERLAP       = 4,
	AVM3D_WEIGHT_MODE_ERROR			= 99
} AVM3D_WEIGHT_MODE;

void AVM3D_SetStitchLineInfo(alAVM3D_CfgSingleView *a_ptAVMCfg, AVM3D_StitchLineCfg *a_ptStitchLine);

void AVM3D_OverlapWeightCal(FLOAT64 a_eX, FLOAT64 a_eY, const AVM3D_StitchLineCfg *a_ptStitchLine, FLOAT32 afWeight[2], UINT8 a_aucViewIndex[2], alAVM3D_CfgSingleView * a_ptAVMCfg);

#if 0
void AVM3D_TestOverlapWeightCal(void);
#endif

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
