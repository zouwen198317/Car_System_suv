
#pragma once

#include "mtype.h"
#include "alAVM2DDef.h"
#include "alFM_v2_1.h"
#include "alLUT_v2_Def.h"
  
/**
*  \addtogroup alAVM2D
*  @{
*/

 /** \brief Define the line parameter of the 2D around view monitor . */
typedef struct
{
	/** \brief The Start point X on BV domain(mm). */
    FLOAT32        fStartPointX;
	/** \brief The Start point Y on BV domain(mm). */
    FLOAT32        fStartPointY;
	/** \brief The ratio of line. */
    FLOAT32        fRatio;
	/** \brief The degree of line. */
    FLOAT32        fdegree;
	/** \brief The fOffset of line. >> y = fRatio * x + fOffset and fRatio = tan(fdegree)*/
    FLOAT32        fOffset; // y = fRatio * x + fOffset and fRatio = tan(fdegree)
	/** \brief The x direction vector of line.)*/
    FLOAT32        fVx; // 直線向量 - x
	/** \brief The y direction vector of line.)*/
    FLOAT32        fVy; // 直線向量  - y
} alAVM2D_Line;


typedef struct
{
	INT32 lCornerIndex;
	alAVM2D_Line tLawLine; // 法線 

    alAVM2D_Line atStitchLineA[2]; // 0: 水平 1: 斜線
	alAVM2D_Line atStitchLineB[2]; // 0: 垂直 1: 斜線

	alAVM2D_Line tLineBezierA;
	alAVM2D_Line tLineBezierB;

	alPointINT32 tBezierPointA;
	alPointINT32 tBezierPointB;

	FLOAT64 eBezierTA;
	FLOAT64 eBezierTB;

	FLOAT64 eCurveDistanceA;
	FLOAT64 eCurveDistanceB;

	//FLOAT32 fBezierWeightA;
	//FLOAT32 fBezierWeightB;

	FLOAT32 fAngleA;
	FLOAT32 fAngleB;
	FLOAT32 fAngleStitch;

	alPointINT32 atPointA[3];
	alPointINT32 atPointB[3];
	alPointINT32 tStitchStart;

} alAVM2D_OverLap;

 /** \brief Define the line config of the 2D around view monitor . */
typedef struct
{
	/** \brief The information of line. */
    alAVM2D_Line tStitchLine[12];
	/** \brief The angle range of line. */
    FLOAT32    fStitchRegionAngel[4];
} alAVM2D_StitchLineCfg;


typedef enum 
{
    alAVM2D_WEIGHT_MODE_BLOCK			= 0,
    alAVM2D_WEIGHT_MODE_VIEW_0		= 1,
    alAVM2D_WEIGHT_MODE_VIEW_1		= 2,
    alAVM2D_WEIGHT_MODE_SINGLEVIEW	= 3,
    alAVM2D_WEIGHT_MODE_OVERLAP       = 4,
	alAVM2D_WEIGHT_MODE_ERROR			= 99
} alAVM2D_WEIGHT_MODE;

 /** \brief Define the overlapping region. */
typedef enum 
{
    alAVM2D_STITCH_REGION_BLOCK       = 0,
    alAVM2D_STITCH_REGION_FRONTLEFT   = 1,
    alAVM2D_STITCH_REGION_LEFT        = 2,
    alAVM2D_STITCH_REGION_LEFTBACK    = 3,
    alAVM2D_STITCH_REGION_BACK        = 4,
    alAVM2D_STITCH_REGION_RIGHTBACK   = 5,
    alAVM2D_STITCH_REGION_RIGHT       = 6,
    alAVM2D_STITCH_REGION_FRONTRIGHT  = 7,
    alAVM2D_STITCH_REGION_FRONT       = 8,

    alAVM2D_STITCH_REGION_ERROR       = 99,
} alAVM2D_STITCH_REGION;

/** 
	\brief set stitch line information of alAVM2D.
	\param a_ptAVMCfg [IN] alAVM2D config.
    \param a_ptalAVM2DParams [IN] alAVM2D parameter.
	\param a_ptStitchLine [OUT] stitch line information.
*/
void alAVM2D_SetStitchLineInfo(alAVM2D_Params *a_ptalAVM2DParams, alAVM2D_Cfg * a_ptAVMCfg, alAVM2D_StitchLineCfg *a_ptStitchLine);

/** 
	\brief calculate the weighting of alAVM2D for stitching region.
	\param a_ptAVMCfg [IN] Cfg information
	\param a_eX [IN] coordinate of x on Top view.
	\param a_eY [IN] coordinate of y on Top view.
	\param a_ptStitchLine [IN] Stitch Line's information.
	\param afWeight [OUT] The weighting in top view for alAVM2D. 
	\param a_aucViewIndex [OUT] The View Index in top view for alAVM2D. 
*/
void alAVM2D_OverlapWeightCal(alAVM2D_Cfg * a_ptAVMCfg, FLOAT64 a_eX, FLOAT64 a_eY, const alAVM2D_StitchLineCfg *a_ptStitchLine, FLOAT32 afWeight[2], UINT8 a_aucViewIndex[2]);

#if 0
void AVM3D_TestOverlapWeightCal(void);
#endif

/**
  *  @}
  */
