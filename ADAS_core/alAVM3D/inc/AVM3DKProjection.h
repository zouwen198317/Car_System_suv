
#pragma once

#include "mtype.h"
#include "AVM3DDef.h"
#include "alFM_v2_1.h"
#include "alLUT_v2_Def.h"

/**
*  \addtogroup AVM3D
*  @{
*/

typedef enum 
{
    AVM3D_PROJECT_REGION_BLOCK = 0,
    AVM3D_PROJECT_REGION_BV = 1,
    AVM3D_PROJECT_REGION_NOT_BV = 2,
} AVM3D_PROJECT_REGION;


typedef struct
{
    FLOAT64           eCurveA;
    FLOAT64           eCurveB;
    FLOAT64           eCurveC;
    FLOAT64           eCurveD;
    FLOAT64           eCurveE;
    FLOAT64           eCurveF;
} AVM3D_Projection3DCfg;

typedef struct
{
    /*center of origin (x,y,z)*/
    FLOAT32 fCenterX;
    FLOAT32 fCenterY;
    FLOAT32 fCenterZ;
    /*center of origin Radius of region of bird-view model from center*/
    FLOAT32 fRadius;
    /*coefficent of line => Z = fA*(d - fOffsetHorz)^2 + fB*(d - fOffsetHorz) + fOffsetVert*/
    FLOAT32 fA;
    FLOAT32 fB;
    FLOAT32 fOffsetHorz;
    FLOAT32 fOffsetVert;
    /*coefficent of line => Z = ffLineNonBVCoe[0]*d^2 + ffLineNonBVCoe[1]*d + ffLineNonBVCoe[2]*/
    FLOAT32 fLineNonBVCoe[3];
    /*coefficent of line => Z = fLineBVCoe[0]*d^2 + fLineBVCoe[1]*d + fLineBVCoe[2]*/
    FLOAT32 fLineBVCoe[3];
    FLOAT32 fLimitAngle;
} AVM3D_ProjectionCfg;


/** 
    \brief Set 3D Projection Infomation such as coefficent of line or function by array
    \param a_peParameter [IN] parameter array
	\param a_ptAVMSurfaceCfg [OUT]  Projection Infomation
*/
void AVM3D_Set3DCurveProjectionInfoByArray(FLOAT64 *a_peParameter, AVM3D_Projection3DCfg *a_ptAVMSurfaceCfg);

/*Set 3D Projection Infomation such as coefficent of line or function*/
void AVM3D_Set3DCurveProjectionInfo(alAVM3D_CfgSingleView * a_ptAVMCfg, AVM3D_Projection3DCfg *a_ptAVMSurfaceCfg);

/*Get 3D Projection coordinate*/
BOOL AVM3D_Projection3DModelCal(AVM3D_Projection3DCfg * a_ptAVMCfg, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 *a_peDestX, FLOAT64 *a_peDestY, FLOAT64 *a_peDestZ);

/*Set 2D Projection Infomation such as coefficent of line or function*/
void AVM3D_Set2DCurveProjectionInfo(alAVM3D_CfgSingleView * a_ptAVMCfg, UINT8 ucCurveIndex, AVM3D_ProjectionCfg *a_ptProjMod);

/*calculation the projection point (x,y,z) = (a_aeResult[0],a_aeResult[1],a_aeResult[2])*/
INT8 AVM3D_ProjectionCal(FLOAT64 a_eP1X, FLOAT64 a_eP1Y, FLOAT64 a_eP1Z, FLOAT64 a_eP2X, FLOAT64 a_eP2Y, FLOAT64 a_eP2Z,AVM3D_ProjectionCfg *a_ptProjMod, FLOAT64 *a_peResultX, FLOAT64 *a_peResultY, FLOAT64 *a_peResultZ);

/** 
    \brief calculate the anngle of distancle[2]
    \param a_aeDistance [IN] triangle's distance
*/

FLOAT32 AVM3D_AngleCalByLength(FLOAT64 a_aeDistance[3]);

/**
  *  @}
  */
