#include "AVM3DKProjection.h"
#include "AVM3DK.h"
#include "AVM3DM33Generation.h"
#include "alFM_v2_1.h"
#include "alLUT_v2.h"
#include "basedef.h"
#include <math.h>       /* sqrt */
#include <assert.h>

#define ZERO          (0.001)

//#define TEST_3D   1

static BOOL CoordinatesProject_GroundPlane(FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, 
                                            FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, 
                                            FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    FLOAT64 eM1 = a_eBVC_X;
    FLOAT64 eM2 = a_eBVC_Y;
    FLOAT64 eM3 = a_eBVC_Z;

    FLOAT64 eV1 = (a_eSrcX - a_eBVC_X);
    FLOAT64 eV2 = (a_eSrcY - a_eBVC_Y);
    FLOAT64 eV3 = (a_eSrcZ - a_eBVC_Z);

    FLOAT64 eN1 = 0;
    FLOAT64 eN2 = 0;
    FLOAT64 eN3 = 0;
    FLOAT64 eVP1 = 0;
    FLOAT64 eVP2 = 0;
    FLOAT64 eVP3 = -1;

    FLOAT64 eT, eT1;

    eT1 = (eVP1 * eV1+ eVP2 * eV2+ eVP3 * eV3);
    if(eT1 != 0)
    {
        eT = ((eN1 - eM1) * eVP1 + (eN2 - eM2) * eVP2 + (eN3 - eM3) * eVP3) / eT1;

        if(eT >= 0) 
        {
            (*a_peDestX) = eM1 + eV1 * eT;
            (*a_peDestY) = eM2 + eV2 * eT;
            (*a_peDestZ) = eM3 + eV3 * eT;

            return TRUE;
        }
    }

    return FALSE;
}

// 找向量正向的交點
static BOOL CoordinatesProject_CurveSurface_Positive(AVM3D_Projection3DCfg * a_ptAVMCfg, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    FLOAT64 eM1 = a_eBVC_X;
    FLOAT64 eM2 = a_eBVC_Y;
    FLOAT64 eM3 = a_eBVC_Z;

    FLOAT64 eV1 = (a_eSrcX - a_eBVC_X);
    FLOAT64 eV2 = (a_eSrcY - a_eBVC_Y);
    FLOAT64 eV3 = (a_eSrcZ - a_eBVC_Z);

    // Cruve: A * X^2 + B * X + C * Y^2 + D * Y + E * Z + F = 0
    FLOAT64 eCurveA, eCurveB, eCurveC, eCurveD, eCurveE, eCurveF;
    FLOAT64 eParamA, eParamB, eParamC;
    FLOAT64 eT, eTs, eT2;

    eCurveA = a_ptAVMCfg->eCurveA;
    eCurveB = a_ptAVMCfg->eCurveB;
    eCurveC = a_ptAVMCfg->eCurveC; 
    eCurveD = a_ptAVMCfg->eCurveD;
    eCurveE = a_ptAVMCfg->eCurveE;    // 面向 Z 負方向的曲面
    eCurveF = a_ptAVMCfg->eCurveF;

    eParamA = eCurveA * eV1 * eV1 + eCurveC * eV2 * eV2;
    eParamB = 2 * eCurveA * eM1 * eV1 + eCurveB * eM1 + 2 * eCurveC * eM2 * eV2 + eCurveD * eV2 + eCurveE * eV3;
    eParamC = eCurveA * eM1 * eM1 + eCurveB * eM1 + eCurveC * eM2 * eM2 + eCurveD * eM2 + eCurveE * eM3 + eCurveF;

    if(eParamA == 0) 
    {
        (*a_peDestX) = a_eBVC_X ;
        (*a_peDestY) = a_eBVC_Y;
        (*a_peDestZ) = - (eCurveA * eM1 * eM1 + eCurveB * eM1 + eCurveC * eM2 * eM2 + eCurveD * eM2 + eCurveF) / eCurveE;
    }
    else
    {
        assert(eParamA != 0);

        eTs = eParamB * eParamB - 4 * eParamA * eParamC;

        if(eTs < 0) return FALSE;
        assert(eTs >= 0);

        eT = (- eParamB + sqrt(eTs)) / (2.0 * eParamA);
        eT2 = (- eParamB - sqrt(eTs)) / (2.0 * eParamA);

        if(eT < 0)
        {
            eT = eT2;
        }

        if(eT < 0) return FALSE;

        (*a_peDestX) = eM1 + eV1 * eT;
        (*a_peDestY) = eM2 + eV2 * eT;
        (*a_peDestZ) = eM3 + eV3 * eT;
    }

    return TRUE;
}

// 將 3D 座標轉成 2D 座標 : 以 Z 軸及 Source X, Y 形成的 2D 平面之座標
static void CoordinatesTransform_3D2D(FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_pePhiAngle)
{
    // Z_3D 直接 assign 給 Y_2D
    (*a_peDestY) = a_eSrcZ;
    // X_2D 為 (0, 0, 0) 到 (X_3D, Y_3D, 0) 之直線距離
    (*a_peDestX) = sqrt(a_eSrcX * a_eSrcX + a_eSrcY * a_eSrcY);
    // 計算 Phi Angle
    (*a_pePhiAngle) = atan2(a_eSrcY, a_eSrcX);
}

// 將 2D 座標轉成 3D 座標 : 以 Z 軸及 Source X, Y 形成的 2D 平面之座標
static void CoordinatesTransform_2D3D(FLOAT64 a_ePhiAngle, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    // Y_2D 直接 assign 給 Z_3D
    (*a_peDestZ) = a_eSrcY;
    // X_3D, Y_3D 為 (0, 0, 0) 到 (X_3D, Y_3D, 0) 之直接距離
    (*a_peDestX) = a_eSrcX * cos(a_ePhiAngle);
    (*a_peDestY) = a_eSrcX * sin(a_ePhiAngle);
}

// 找向量正向的交點
static BOOL CoordinatesProject_Curve_Positive(AVM3D_Projection3DCfg * a_ptAVMCfg, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY)
{
    FLOAT64 eM1 = a_eBVC_X;
    FLOAT64 eM2 = a_eBVC_Y;

    FLOAT64 eV1 = (a_eSrcX - a_eBVC_X);
    FLOAT64 eV2 = (a_eSrcY - a_eBVC_Y);

    FLOAT64 eV1V2Ratio = 0.0; 
    FLOAT64 ePlaneRatio = 0.0;

    // Cruve: y = a * (x - b)^2
    FLOAT64 eCurveA, eCurveB;
    // Cruve: a * t^2 + b * t + c = 0
    FLOAT64 eParamA, eParamB, eParamC;
    FLOAT64 eT, eTs, eT2;

    assert(a_eBVC_X == 0.0);

    if (eV1 < 0.000001)
    {
        (*a_peDestX) = 0.0;
        (*a_peDestY) = 0.0;
    }

    eCurveA = a_ptAVMCfg->eCurveA;
    eCurveB = a_ptAVMCfg->eCurveB;

    // (1) 計算投影向量投影到平坦區或曲線區，若位於平坦區，則以平坦區做投影
    // 1.1 x < eCurveB 者為平坦區， x > eCurveB 者為曲線區
    eV1V2Ratio = eV2 / eV1;
    ePlaneRatio = (0 - a_eBVC_Y) / (eCurveB - a_eBVC_X);

    if (eCurveB != 0.0 && eV1V2Ratio <= ePlaneRatio)
    {   // 平坦區
        assert(eCurveB != 0.0 && eV2 != 0.0);
        (*a_peDestX) = (0.0 - a_eBVC_Y) / eV1V2Ratio;
    }
    else
    {   // 曲線區 : y = a * (x - b)^2
        eParamA = eCurveA * eV1 * eV1;
        eParamB = 2 * eCurveA * eV1 * (eM1 - eCurveB) - eV2;
        eParamC = eCurveA * (eM1 - eCurveB) * (eM1 - eCurveB) - eM2;

        assert(eParamA != 0);

        eTs = eParamB * eParamB - 4 * eParamA * eParamC;

        if (eTs < 0) return FALSE;
        assert(eTs >= 0);

        eT = (-eParamB + sqrt(eTs)) / (2.0 * eParamA);
        eT2 = (-eParamB - sqrt(eTs)) / (2.0 * eParamA);

        if (eT < 0)
        {
            eT = eT2;
        }

        if (eT < 0) return FALSE;

        (*a_peDestX) = eM1 + eV1 * eT;
        (*a_peDestY) = eM2 + eV2 * eT;
    }

    return TRUE;
}

FLOAT64 AVM3D_AngleCalByVector(FLOAT64 a_aeD[3], FLOAT64 a_aeZ[3])
{
    // 0: src 1: p1 2:p2
    FLOAT64 eVectorA[2], eVectorB[2], eProductValue, eVectorAVal, eVectorBVal, eCosValue, eAngle;

    eVectorA[0] = a_aeD[1] - a_aeD[0];
    eVectorA[1] = a_aeZ[1] - a_aeZ[0];

    eVectorB[0] = a_aeD[2] - a_aeD[0];
    eVectorB[1] = a_aeZ[2] - a_aeZ[0];

    eProductValue = (eVectorA[0] * eVectorB[0]) + (eVectorA[1] * eVectorB[1]);  // 向量的乘積
    eVectorAVal = sqrt(eVectorA[0] * eVectorA[0] + eVectorA[1] * eVectorA[1]);  // 向量A的大小
    eVectorBVal = sqrt(eVectorB[0] * eVectorB[0] + eVectorB[1] * eVectorB[1]);  // 向量B的大小

    eCosValue = eProductValue / (eVectorAVal * eVectorBVal);      // 餘弦公式

    // acos的輸入參數範圍必須在[-1, 1]之間，否則會"domain error"
    // 對輸入參數作校驗和處理
    if(eCosValue < -1 && eCosValue > -2)
        eCosValue = -1;
    else if(eCosValue > 1 && eCosValue < 2)
        eCosValue = 1;
    
    // acos返回的是弧度值，轉換成角度值
    eAngle = acos(eCosValue) * 180 / alPI; 
    return eAngle;
}

UINT8 AVM3D_ProjectionRegionDecide(FLOAT32 a_fCurrentAngle, AVM3D_ProjectionCfg *a_ptProjMod)
{
    if(a_fCurrentAngle > a_ptProjMod->fLimitAngle)
    {  // AVM3D_PROJECT_REGION_NOT_BV
        return AVM3D_PROJECT_REGION_NOT_BV;
    }
    else
    {  // AVM3D_PROJECT_REGION_BV
        return AVM3D_PROJECT_REGION_BV;
    }
}

AVM3D_FindMeetPoint(FLOAT64 a_ePo[2], FLOAT64 a_eP1[2], FLOAT64 a_eP2[2], FLOAT64 a_ePvc[2])
{
    FLOAT64 eRatio = 0, eOffset = 0;

    eRatio = (a_eP2[1] - a_eP1[1]) / (a_eP2[0] - a_eP1[0]); 
    eOffset = a_eP1[1] - eRatio*a_eP1[0];

    a_ePvc[0] = a_ePo[0];
    a_ePvc[1] = eRatio*a_ePo[0] + eOffset;
}

FLOAT32 AVM3D_AngleCalByLength(FLOAT64 a_aeDistance[3])
{
    FLOAT64 eCosValue = 0;
    FLOAT32 fAnlgle = 0;

    eCosValue = a_aeDistance[0]*a_aeDistance[0] + a_aeDistance[1]*a_aeDistance[1] - a_aeDistance[2]*a_aeDistance[2];
    eCosValue = eCosValue / (2*a_aeDistance[0]*a_aeDistance[1]);

    // acos的輸入參數範圍必須在[-1, 1]之間，否則會"domain error"
    // 對輸入參數作校驗和處理
    if(eCosValue < -1 && eCosValue > -2)
        eCosValue = -1;
    else if(eCosValue > 1 && eCosValue < 2)
        eCosValue = 1;

    // acos返回的是弧度值，轉換成角度值
    fAnlgle = (FLOAT32)(acos(eCosValue) * 180 / alPI); 
    
    return fAnlgle;
}

INT8 AVM3D_ProjectionCal(FLOAT64 a_eP1X, FLOAT64 a_eP1Y, FLOAT64 a_eP1Z, FLOAT64 a_eP2X, FLOAT64 a_eP2Y, FLOAT64 a_eP2Z,AVM3D_ProjectionCfg *a_ptProjMod, FLOAT64 *a_peResultX, FLOAT64 *a_peResultY, FLOAT64 *a_peResultZ)
{
    UINT8 ucRegion = 0, ucQuadrant;
    FLOAT64 ePo[2], eP1[2], eP2[2], ePr[2], ePvc[2], ePmeet[2];
    FLOAT64 aeDistance[3] = {0};
    FLOAT32 fCurrentAngle = 0;
    FLOAT64 eRatio = 0, eOffset = 0, eFinalCoe[3] = {0}, eJuge = 0, eTimeOfX = 0;

    if(a_eP1X)
    {
        eTimeOfX = a_eP1Y / a_eP1X;
    }
    else if(a_eP2X)
    {    
        eTimeOfX = a_eP2Y / a_eP2X;
    }
    else
    {
        /*a_eP1X and a_eP2X are both empty fail*/
        return 0;
    }

    if(a_eP1X > 0)
    {  // 1 or 4 象限(Quadrant)
        ucQuadrant = 0;     
    }
    else
    {  // 2 or 3 象限(Quadrant)
        ucQuadrant = 1;
    }

    // step 0.3 : transform to d,z domain
    ePo[0] = sqrt(a_ptProjMod->fCenterX*a_ptProjMod->fCenterX + a_ptProjMod->fCenterY*a_ptProjMod->fCenterY);
    ePo[1] = a_ptProjMod->fCenterZ;
    eP1[0] = sqrt(a_eP1X*a_eP1X + a_eP1Y*a_eP1Y);
    eP1[1] = a_eP1Z;
    eP2[0] = sqrt(a_eP2X*a_eP2X + a_eP2Y*a_eP2Y);
    eP2[1] = a_eP2Z;
    ePr[0] = ePo[0] + a_ptProjMod->fRadius;
    ePr[1] = ePo[1];
    AVM3D_FindMeetPoint(ePo, eP1, eP2, ePvc);

    // step 1 : get and set AngleTh
    aeDistance[0] = fabs(ePo[1] - ePvc[1]);
    aeDistance[1] = sqrt((ePr[1] - ePvc[1])*(ePr[1] - ePvc[1]) + (ePr[0] - ePvc[0])*(ePr[0] - ePvc[0]));
    aeDistance[2] = a_ptProjMod->fRadius;
    a_ptProjMod->fLimitAngle = AVM3D_AngleCalByLength(aeDistance);

    // step 2 : get Current Angle
    aeDistance[1] = sqrt((eP1[1] - ePvc[1])*(eP1[1] - ePvc[1]) + (eP1[0] - ePvc[0])*(eP1[0] - ePvc[0]));
    aeDistance[2] = sqrt((eP1[1] - ePo[1])*(eP1[1] - ePo[1]) + (eP1[0] - ePo[0])*(eP1[0] - ePo[0]));
    fCurrentAngle = AVM3D_AngleCalByLength(aeDistance);
    ucRegion = AVM3D_ProjectionRegionDecide(fCurrentAngle, a_ptProjMod);

    // step 3: find meet point Pm
    eRatio = (eP2[1] - eP1[1]) / (eP2[0] - eP1[0]);
    eOffset = eP1[1] - eRatio*eP1[0];
    switch(ucRegion)
    {
        case AVM3D_PROJECT_REGION_BV:
            ePmeet[1] = a_ptProjMod->fCenterZ;
            ePmeet[0] = (ePmeet[1] - eOffset) / eRatio;
            *a_peResultZ = ePmeet[1];
            *a_peResultX = sqrt(ePmeet[0]*ePmeet[0] / (eTimeOfX*eTimeOfX + 1));
            if(ucQuadrant)
            {
                *a_peResultX = -(*a_peResultX);
            }
            *a_peResultY = eTimeOfX*(*a_peResultX);
            return 1;
        break;
        case AVM3D_PROJECT_REGION_NOT_BV:
            eFinalCoe[0] = a_ptProjMod->fLineNonBVCoe[0];
            eFinalCoe[1] = a_ptProjMod->fLineNonBVCoe[1] - eRatio;
            eFinalCoe[2] = a_ptProjMod->fLineNonBVCoe[2] - eOffset;
            eJuge = eFinalCoe[1]*eFinalCoe[1] - 4*eFinalCoe[0]*eFinalCoe[2]; // b^2 - 4ac
            if(eJuge > ZERO)
            {
                if(eJuge > 0)
                {  // has 2 roots
                    ePmeet[0] = (-eFinalCoe[1] - sqrt(eJuge)) / (2*eFinalCoe[0]); // (-b - sqrt(b^2 - 4ac)) / 2a  >> a < 0 so choose (-b - sqrt(b^2 - 4ac)) / 2a
                    ePmeet[1] = eRatio*ePmeet[0] + eOffset;
                    *a_peResultZ = ePmeet[1];
                    *a_peResultX = sqrt(ePmeet[0]*ePmeet[0] / (eTimeOfX*eTimeOfX + 1));
                    if(ucQuadrant)
                    {
                        *a_peResultX = -(*a_peResultX);
                    }
                    *a_peResultY = eTimeOfX*(*a_peResultX);
                    return 1;
                }
                else
                {  // has virtual root
                    return 0;
                }
            }
            else
            {  // Only one root
                return 0;
            }
        break;
        default:
            return 0;
        break;
    }
}


void AVM3D_Set3DCurveProjectionInfo(alAVM3D_CfgSingleView * a_ptAVMCfg, AVM3D_Projection3DCfg *a_ptAVMSurfaceCfg)
{
    FLOAT64 eOffsetHorz = 0.0;
    FLOAT32 fCenterX = 0.0, fCenterY = 0.0, fCenterZ = 0.0;
    FLOAT64 ea = 0.0, eb = 0.0, ec = 0.0, ed = 0.0, ee = 0.0, ef = 0.0;
    /* fa*(x - fCenterX)^2 + fb*(x - fCenterX) + fc*(y - fCenterY)^2 + fd*(y - fCenterY) + fe*(z - fCenterZ) + ff = 0 */
    fCenterX = a_ptAVMCfg->fCurveCenterX;
    fCenterY = a_ptAVMCfg->fCurveCenterY;
    fCenterZ = a_ptAVMCfg->fCurveCenterZ;
    ea = a_ptAVMCfg->eCurveSurfaceA;
    eb = a_ptAVMCfg->eCurveSurfaceB;
    ec = a_ptAVMCfg->eCurveSurfaceC;
    ed = a_ptAVMCfg->eCurveSurfaceD;
    ee = a_ptAVMCfg->eCurveSurfaceE;
    ef = a_ptAVMCfg->eCurveSurfaceF;

    a_ptAVMSurfaceCfg->eCurveA = ea;
    a_ptAVMSurfaceCfg->eCurveB = eb - 2*ea*fCenterX;
    a_ptAVMSurfaceCfg->eCurveC = ec;
    a_ptAVMSurfaceCfg->eCurveD = ed - 2*ec*fCenterY;
    a_ptAVMSurfaceCfg->eCurveE = ee;
    a_ptAVMSurfaceCfg->eCurveF = fCenterX*fCenterX - eb*fCenterX + fCenterY*fCenterY - ed*fCenterY - ee*fCenterZ + ef;
}

void AVM3D_Set3DCurveProjectionInfoByArray(FLOAT64 *a_peParameter, AVM3D_Projection3DCfg *a_ptAVMSurfaceCfg)
{
    FLOAT32 fCenterX = 0.0, fCenterY = 0.0, fCenterZ = 0.0;
    FLOAT64 ea = 0.0, eb = 0.0, ec = 0.0, ed = 0.0, ee = 0.0, ef = 0.0;
    /* fa*(x - fCenterX)^2 + fb*(x - fCenterX) + fc*(y - fCenterY)^2 + fd*(y - fCenterY) + fe*(z - fCenterZ) + ff = 0 */
    
    ea = a_peParameter[0];
    eb = a_peParameter[1];
	ec = a_peParameter[2];
	ed = a_peParameter[3];
    ee = a_peParameter[4];
    ef = a_peParameter[5];

	fCenterX = (FLOAT32)a_peParameter[6];
    fCenterY = (FLOAT32)a_peParameter[7];
    fCenterZ = (FLOAT32)a_peParameter[8];

    a_ptAVMSurfaceCfg->eCurveA = ea;
    a_ptAVMSurfaceCfg->eCurveB = eb - 2*ea*fCenterX;
    a_ptAVMSurfaceCfg->eCurveC = ec;
    a_ptAVMSurfaceCfg->eCurveD = ed - 2*ec*fCenterY;
    a_ptAVMSurfaceCfg->eCurveE = ee;
    a_ptAVMSurfaceCfg->eCurveF = fCenterX*fCenterX - eb*fCenterX + fCenterY*fCenterY - ed*fCenterY - ee*fCenterZ + ef;
}

BOOL AVM3D_Projection3DModelCal(AVM3D_Projection3DCfg * a_ptAVMCfg, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 *a_peDestX, FLOAT64 *a_peDestY, FLOAT64 *a_peDestZ)
{
    BOOL bResult = 0, bResultPlane = 0;
    FLOAT64 eDestXTmp = 0, eDestYTmp = 0, eDestZTmp = 0;

    bResult = CoordinatesProject_CurveSurface_Positive(a_ptAVMCfg, a_eBVC_X, a_eBVC_Y, a_eBVC_Z, a_eSrcX, a_eSrcY, a_eSrcZ, &eDestXTmp, &eDestYTmp, &eDestZTmp);

    if(bResult)
    {
        if(eDestZTmp > 0)
        {  // Use 2D BV model
            bResultPlane =  CoordinatesProject_GroundPlane(a_eBVC_X, a_eBVC_Y, a_eBVC_Z, a_eSrcX, a_eSrcY, a_eSrcZ, &eDestXTmp, &eDestYTmp, &eDestZTmp);
            if(bResultPlane)
            {
                *a_peDestX = eDestXTmp;
                *a_peDestY = eDestYTmp;
                *a_peDestZ = eDestZTmp;
            }
            else
            {
                return FALSE;
            }
        }                           
        else
        {  // Use 3D projection model
            *a_peDestX = eDestXTmp;
            *a_peDestY = eDestYTmp;
            *a_peDestZ = eDestZTmp;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// 前提條件︰投影的中心點必須位在Z軸上，使用偏移的二次曲線，繞一圈形成曲面。中心處仍以平面取代
BOOL AVM3D_Projection3DModelCal2(AVM3D_Projection3DCfg * a_ptAVMCfg, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 *a_peDestX, FLOAT64 *a_peDestY, FLOAT64 *a_peDestZ)
{
    BOOL bResult = 0, bResultPlane = 0;
    FLOAT64 eDestXTmp = 0, eDestYTmp = 0, eDestZTmp = 0;
    FLOAT64 eSrcX_2D, eSrcY_2D, eDestX_2D, eDestY_2D;
    FLOAT64 ePhiAngle;

    assert(a_eBVC_X == 0 && a_eBVC_Y == 0);

    CoordinatesTransform_3D2D(a_eSrcX, a_eSrcY, a_eSrcZ, &eSrcX_2D, &eSrcY_2D, &ePhiAngle);

    bResult = CoordinatesProject_Curve_Positive(a_ptAVMCfg, 0.0, a_eBVC_Z, eSrcX_2D, eSrcY_2D, &eDestX_2D, &eDestY_2D);
   
    CoordinatesTransform_2D3D(ePhiAngle, eDestX_2D, eDestY_2D, &eDestXTmp, &eDestYTmp, &eDestZTmp);

    if(bResult)
    {
        if(eDestZTmp > 0)
        {  // Use 2D BV model
            bResultPlane =  CoordinatesProject_GroundPlane(a_eBVC_X, a_eBVC_Y, a_eBVC_Z, a_eSrcX, a_eSrcY, a_eSrcZ, &eDestXTmp, &eDestYTmp, &eDestZTmp);
            if(bResultPlane)
            {
                *a_peDestX = eDestXTmp;
                *a_peDestY = eDestYTmp;
                *a_peDestZ = eDestZTmp;
            }
            else
            {
                return FALSE;
            }
        }                           
        else
        {  // Use 3D projection model
            *a_peDestX = eDestXTmp;
            *a_peDestY = eDestYTmp;
            *a_peDestZ = eDestZTmp;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#if 0
void AVM3D_TestProjectionModelCal(void)
{
    AVM3D_ProjectionCfg tProjMod;
 
    FLOAT64 aeX[2]; // 0 :P1     1 : P2
    FLOAT64 aeY[2];
    FLOAT64 aeZ[2];
    FLOAT64 aeResult[3];
    FLOAT64 eRatioXYTest = 1;
    INT8 cResult = 0;
    UINT8 ucResult = 0;
    AVM3D_Projection3DCfg tAVMSurfaceCfg;
    alAVM3D_CfgSingleView tAVMCfg;
    UINT8 ucCurveIndex = 0;
    
#if TEST_3D 
    aeX[0]  = 0;
    aeY[0]  = 0;
    aeZ[0]  = -3960000;
    aeX[1]  = 1200 / sqrt(1 + eRatioXYTest);
    aeY[1]  = 1200 / sqrt(1 + eRatioXYTest);
    aeX[1]  = 109 / sqrt(1 + eRatioXYTest);
    aeY[1]  = 109 / sqrt(1 + eRatioXYTest);
    aeZ[1]  = -3600000;

    // hard code
    /*tAVMSurfaceCfg.eCurveA = 1;
    tAVMSurfaceCfg.eCurveB = 0;
    tAVMSurfaceCfg.eCurveC = 1;
    tAVMSurfaceCfg.eCurveD = 0;
    tAVMSurfaceCfg.eCurveE = 1;
    tAVMSurfaceCfg.eCurveF = -1500*1500;*/

    tAVMCfg.eCurveSurfaceA[ucCurveIndex] = 1;
    tAVMCfg.eCurveSurfaceB[ucCurveIndex] = 0;
    tAVMCfg.eCurveSurfaceC[ucCurveIndex] = 1;
    tAVMCfg.eCurveSurfaceD[ucCurveIndex] = 0;
    tAVMCfg.eCurveSurfaceE[ucCurveIndex] = 1;
    tAVMCfg.eCurveSurfaceF[ucCurveIndex] = 0;

    tAVMCfg.fCurveCenterX[ucCurveIndex] = 0;
    tAVMCfg.fCurveCenterY[ucCurveIndex] = 0;
    tAVMCfg.fCurveCenterZ[ucCurveIndex] = 1500*1500;

    // set Surface Cfg
    AVM3D_Set3DCurveProjectionInfo(&tAVMCfg, ucCurveIndex, &tAVMSurfaceCfg);

    // get result
    ucResult = AVM3D_Projection3DModelCal(&tAVMSurfaceCfg, aeX[0], aeY[0], aeZ[0], aeX[1], aeY[1], aeZ[1], aeResult, aeResult+1, aeResult+2);
#else
    // step 0.1 : give P1 P2
    // 45 degree of x & y
    aeX[0]  = 1020 / sqrt(1 + eRatioXYTest);
    aeY[0]  = 1020 / sqrt(1 + eRatioXYTest);
    aeZ[0]  = -3960000;
    aeX[1]  = 1200 / sqrt(1 + eRatioXYTest);
    aeY[1]  = 1200 / sqrt(1 + eRatioXYTest);
    aeZ[1]  = -3600000;
    // 45 degree

    // step 0.2 : set R, Center's position and L2's coefficent
    AVM3D_Set2DCurveProjectionInfo(&tProjMod);

    // step 1~4
    cResult = AVM3D_ProjectionCal(aeX[0], aeY[0], aeZ[0], aeX[1], aeY[1], aeZ[1], &tProjMod, &aeResult[0], &aeResult[1], &aeResult[2]);
#endif
}
#endif

/**
  *  @}
  */
