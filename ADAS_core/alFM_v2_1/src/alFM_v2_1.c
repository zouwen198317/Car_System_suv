
#include "alFM_v2_1.h"
#include "alFM_v2_1_Default.h"

#include "mtype.h"
#include "basedef.h"

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

/** \cond DOXYGEN_EXCLUDE */


UINT32  alFM_v2_1_QueryFM_WorkingBufferSizeSingle(alFM_v2_1_ModelCfg *a_ptFMCfg)
{
    UINT32 ulSizeTmp = 0, ulSizeTotal = 0, i = 0, ulPixelTableSize = 0, ulAngleTableSize = 0;

    // real height 的 pixel table
    ulPixelTableSize = (UINT16)ceil(sqrt((a_ptFMCfg->ulImageHeight >> 1) * (a_ptFMCfg->ulImageHeight >> 1) +
        (a_ptFMCfg->uwSrcSensorWidth >> 1) * (a_ptFMCfg->uwSrcSensorWidth >> 1)));
    ulPixelTableSize *= sizeof(UINT16);

    // degree 的 table
    ulAngleTableSize = ((UINT16)ceil(a_ptFMCfg->aeAngleDegree[a_ptFMCfg->uwLengthOfDistortionCurve - 1])) * a_ptFMCfg->uwAngleTableScale;
    ulAngleTableSize *= sizeof(UINT16);

    ulSizeTmp = ulPixelTableSize + ulAngleTableSize;

    ulSizeTotal += ulSizeTmp;
    return ulSizeTotal;
}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_InitialBuffer(alFM_v2_1_Model * a_ptFM_v2_Model)
{
    memset(a_ptFM_v2_Model, 0, sizeof(alFM_v2_1_Model));
}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_LoadCfgInfoByHexData(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT32 * a_pulDataBuffer, alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg) // 特定的 Camera Confg INI File, ex. CameraFisheyeParam_v2-Sparrow190.ini
{
    DEBUG_Printf("FM_v2: The code to load user config by HEX is not ready.\n");
}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_InitialByCfgDataExternalBuffer(alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg, alFM_v2_1_Model * a_ptFM_v2_Model, UINT8 *a_pucBuffer)
{

    UINT16 uwDistCurveIndex = 0, uwDI = 0, uwDegree = 0;
    UINT8 *pucBufferTmp = NULL;

    pucBufferTmp = a_pucBuffer;

    a_ptFM_v2_Model->uwSrcWidth = a_ptFM_v2_Cfg->ulImageWidth;
    a_ptFM_v2_Model->uwSrcHeight = a_ptFM_v2_Cfg->ulImageHeight;
    a_ptFM_v2_Model->uwDestWidth = a_ptFM_v2_Cfg->ulImageWidth;
    a_ptFM_v2_Model->uwDestHeight = a_ptFM_v2_Cfg->ulImageHeight;

    a_ptFM_v2_Model->uwSrcSensorWidth = a_ptFM_v2_Cfg->uwSrcSensorWidth;
    a_ptFM_v2_Model->ulSensorPixelSize = a_ptFM_v2_Cfg->ulSensorPixelSize;
    a_ptFM_v2_Model->uwLengthOfDistortionCurve = a_ptFM_v2_Cfg->uwLengthOfDistortionCurve;

    a_ptFM_v2_Model->uwCOD_X = a_ptFM_v2_Cfg->uwCOD_X;
    a_ptFM_v2_Model->uwCOD_Y = a_ptFM_v2_Cfg->uwCOD_Y;

    a_ptFM_v2_Model->eFOV_H = a_ptFM_v2_Cfg->eFOV_H;
    a_ptFM_v2_Model->eFocalLength = a_ptFM_v2_Cfg->eFocalLength;
    a_ptFM_v2_Model->eUD_FOV_H = a_ptFM_v2_Cfg->eUD_FOV_H;

    a_ptFM_v2_Model->uwAngleTableScale = a_ptFM_v2_Cfg->uwAngleTableScale;

    // Calculate resize ratio.
    a_ptFM_v2_Model->eResizeRatio = a_ptFM_v2_Cfg->eHResizeRatio; //(FLOAT64)a_ptFM_v2_Model->uwSrcWidth / a_ptFM_v2_Model->uwSrcSensorWidth;
    //a_ptFM_v2_Model->eResizeRatio = (FLOAT64)a_ptFM_v2_Model->uwSrcWidth / a_ptFM_v2_Model->uwSrcSensorWidth;

    // 更新 Curve 資訊
    for (uwDI = 0; uwDI < a_ptFM_v2_Cfg->uwLengthOfDistortionCurve; uwDI++)
    {
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eAngleDegree = a_ptFM_v2_Cfg->aeAngleDegree[uwDI];
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRealHeight = a_ptFM_v2_Cfg->aeRealHeight[uwDI];

        a_ptFM_v2_Model->atDistortionCurve[uwDI].eAngleInterval =
            a_ptFM_v2_Cfg->aeAngleDegree[uwDI + 1] - a_ptFM_v2_Cfg->aeAngleDegree[uwDI];

        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRealHeightInterval =
            a_ptFM_v2_Cfg->aeRealHeight[uwDI + 1] - a_ptFM_v2_Cfg->aeRealHeight[uwDI];

#if 0
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRefHeight = a_ptFM_v2_Cfg->aeRefHeight[uwDI];
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eDistortion = a_ptFM_v2_Cfg->aeDistortion[uwDI];
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRefHeightInterval =
            a_ptFM_v2_Cfg->aeRefHeight[uwDI + 1] - a_ptFM_v2_Cfg->aeRefHeight[uwDI];

        a_ptFM_v2_Model->atDistortionCurve[uwDI].eDistortionInterval =
            a_ptFM_v2_Cfg->aeDistortion[uwDI + 1] - a_ptFM_v2_Cfg->aeDistortion[uwDI];
#endif
    }
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eAngleInterval = 0.0;
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eRealHeightInterval = 0.0;
#if 0
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eRefHeightInterval = 1.0;
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eDistortionInterval = 1.0;
#endif

    // 建立 real height 的 pixel table

    // Calculate the needed table points.
    a_ptFM_v2_Model->uwLengthOfDistortPixelTable = (UINT16)ceil(sqrt((a_ptFM_v2_Model->uwSrcHeight >> 1) * (a_ptFM_v2_Model->uwSrcHeight >> 1) +
        (a_ptFM_v2_Model->uwSrcSensorWidth >> 1) * (a_ptFM_v2_Model->uwSrcSensorWidth >> 1)));

    // Allocate curve points buffer.
    // a_ptFM_v2_Model->puwDistortPixelTable = (UINT16*)malloc(a_ptFM_v2_Model->uwLengthOfDistortPixelTable * sizeof(UINT16));
    a_ptFM_v2_Model->puwDistortPixelTable = (UINT16*)pucBufferTmp;
    pucBufferTmp += a_ptFM_v2_Model->uwLengthOfDistortPixelTable * sizeof(UINT16);

    for (uwDI = 0, uwDistCurveIndex = 0; uwDI < a_ptFM_v2_Model->uwLengthOfDistortPixelTable; uwDI++)
    {
        if (uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1)
        {
            // 在 atDistortionCurve 中找到 uwDI 剛好大於的數值之位置
            while (uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve
                && (uwDI * a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0) >= a_ptFM_v2_Model->atDistortionCurve[uwDistCurveIndex].eRealHeight)
            {
                uwDistCurveIndex++;
            }

            a_ptFM_v2_Model->puwDistortPixelTable[uwDI] = uwDistCurveIndex - 1;
        }
        else
        {
            a_ptFM_v2_Model->puwDistortPixelTable[uwDI] = a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1;
        }

    }

    // 建立 degree 的 table
    a_ptFM_v2_Model->uwLengthOfAngleTable = ((UINT16)ceil(a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1].eAngleDegree)) * a_ptFM_v2_Model->uwAngleTableScale;
    // a_ptFM_v2_Model->puwAngleTable = (UINT16*)malloc(a_ptFM_v2_Model->uwLengthOfAngleTable * sizeof(UINT16));
    a_ptFM_v2_Model->puwAngleTable = (UINT16*)pucBufferTmp;

    for (uwDegree = 0, uwDistCurveIndex = 0; uwDegree < a_ptFM_v2_Model->uwLengthOfAngleTable; uwDegree++)
    {
        if (uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve)
        {
            // 在 atDistortionCurve 中找到 uwDegree 剛好大於的數值之位置
            while (uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve
                && (uwDegree / (FLOAT64)a_ptFM_v2_Model->uwAngleTableScale) >= a_ptFM_v2_Model->atDistortionCurve[uwDistCurveIndex].eAngleDegree)
            {
                uwDistCurveIndex++;
            }

            a_ptFM_v2_Model->puwAngleTable[uwDegree] = uwDistCurveIndex - 1;
        }
        else
        {
            a_ptFM_v2_Model->uwLengthOfAngleTable = uwDegree - 1;
            a_ptFM_v2_Model->puwAngleTable[uwDegree] = a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1;
            break;
        }

        assert(uwDegree < a_ptFM_v2_Model->uwLengthOfAngleTable);

    }

}
//////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_InitialByCfgData(alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg, alFM_v2_1_Model * a_ptFM_v2_Model)
{

    UINT16 uwDistCurveIndex = 0, uwDI = 0, uwDegree = 0;

    a_ptFM_v2_Model->uwSrcWidth = a_ptFM_v2_Cfg->ulImageWidth;
    a_ptFM_v2_Model->uwSrcHeight = a_ptFM_v2_Cfg->ulImageHeight;
    a_ptFM_v2_Model->uwDestWidth = a_ptFM_v2_Cfg->ulImageWidth;
    a_ptFM_v2_Model->uwDestHeight = a_ptFM_v2_Cfg->ulImageHeight;

    a_ptFM_v2_Model->uwSrcSensorWidth = a_ptFM_v2_Cfg->uwSrcSensorWidth;
    a_ptFM_v2_Model->ulSensorPixelSize = a_ptFM_v2_Cfg->ulSensorPixelSize;
    a_ptFM_v2_Model->uwLengthOfDistortionCurve = a_ptFM_v2_Cfg->uwLengthOfDistortionCurve;

    a_ptFM_v2_Model->uwCOD_X = a_ptFM_v2_Cfg->uwCOD_X;
    a_ptFM_v2_Model->uwCOD_Y = a_ptFM_v2_Cfg->uwCOD_Y;
   
    a_ptFM_v2_Model->eFOV_H = a_ptFM_v2_Cfg->eFOV_H;
    a_ptFM_v2_Model->eFocalLength = a_ptFM_v2_Cfg->eFocalLength;
    a_ptFM_v2_Model->eUD_FOV_H = a_ptFM_v2_Cfg->eUD_FOV_H;

    a_ptFM_v2_Model->uwAngleTableScale = a_ptFM_v2_Cfg->uwAngleTableScale;

    // Calculate resize ratio.
    a_ptFM_v2_Model->eResizeRatio = a_ptFM_v2_Cfg->eHResizeRatio; //(FLOAT64)a_ptFM_v2_Model->uwSrcWidth / a_ptFM_v2_Model->uwSrcSensorWidth;
    //a_ptFM_v2_Model->eResizeRatio = (FLOAT64)a_ptFM_v2_Model->uwSrcWidth / a_ptFM_v2_Model->uwSrcSensorWidth;

    // 更新 Curve 資訊
    for(uwDI = 0; uwDI < a_ptFM_v2_Cfg->uwLengthOfDistortionCurve; uwDI++)
    {
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eAngleDegree = a_ptFM_v2_Cfg->aeAngleDegree[uwDI];
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRealHeight = a_ptFM_v2_Cfg->aeRealHeight[uwDI];

        a_ptFM_v2_Model->atDistortionCurve[uwDI].eAngleInterval = 
            a_ptFM_v2_Cfg->aeAngleDegree[uwDI + 1]- a_ptFM_v2_Cfg->aeAngleDegree[uwDI];

        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRealHeightInterval = 
            a_ptFM_v2_Cfg->aeRealHeight[uwDI + 1]- a_ptFM_v2_Cfg->aeRealHeight[uwDI];

#if 0
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRefHeight = a_ptFM_v2_Cfg->aeRefHeight[uwDI];
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eDistortion = a_ptFM_v2_Cfg->aeDistortion[uwDI];
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eRefHeightInterval = 
            a_ptFM_v2_Cfg->aeRefHeight[uwDI + 1] - a_ptFM_v2_Cfg->aeRefHeight[uwDI];
        
        a_ptFM_v2_Model->atDistortionCurve[uwDI].eDistortionInterval = 
            a_ptFM_v2_Cfg->aeDistortion[uwDI + 1] - a_ptFM_v2_Cfg->aeDistortion[uwDI];
#endif
    }
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eAngleInterval = 0.0;
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eRealHeightInterval = 0.0;
#if 0
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eRefHeightInterval = 1.0;
    a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Cfg->uwLengthOfDistortionCurve - 1].eDistortionInterval = 1.0;
#endif

    // 建立 real height 的 pixel table

    // Calculate the needed table points.
    a_ptFM_v2_Model->uwLengthOfDistortPixelTable = (UINT16) ceil(sqrt((a_ptFM_v2_Model->uwSrcHeight>>1) * (a_ptFM_v2_Model->uwSrcHeight>>1) + 
        (a_ptFM_v2_Model->uwSrcSensorWidth>>1) * (a_ptFM_v2_Model->uwSrcSensorWidth>>1)));

    // Allocate curve points buffer.
    a_ptFM_v2_Model->puwDistortPixelTable = (UINT16*) malloc(a_ptFM_v2_Model->uwLengthOfDistortPixelTable * sizeof(UINT16));

    for(uwDI = 0, uwDistCurveIndex = 0; uwDI < a_ptFM_v2_Model->uwLengthOfDistortPixelTable; uwDI++)
    {
        if(uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1)
        {
            // 在 atDistortionCurve 中找到 uwDI 剛好大於的數值之位置
            while(uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve
                && (uwDI * a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0) >= a_ptFM_v2_Model->atDistortionCurve[uwDistCurveIndex].eRealHeight)
            {
                uwDistCurveIndex++;
            }

            a_ptFM_v2_Model->puwDistortPixelTable[uwDI] = uwDistCurveIndex - 1;
        }
        else
        {
            a_ptFM_v2_Model->puwDistortPixelTable[uwDI] = a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1;
       }

    }

    // 建立 degree 的 table
    a_ptFM_v2_Model->uwLengthOfAngleTable = ((UINT16) ceil(a_ptFM_v2_Model->atDistortionCurve[a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1].eAngleDegree)) * a_ptFM_v2_Model->uwAngleTableScale;
    a_ptFM_v2_Model->puwAngleTable = (UINT16*) malloc(a_ptFM_v2_Model->uwLengthOfAngleTable * sizeof(UINT16));

    for(uwDegree = 0, uwDistCurveIndex = 0; uwDegree < a_ptFM_v2_Model->uwLengthOfAngleTable; uwDegree++)
    {
        if(uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve)
        {
            // 在 atDistortionCurve 中找到 uwDegree 剛好大於的數值之位置
            while(uwDistCurveIndex < a_ptFM_v2_Model->uwLengthOfDistortionCurve
                && (uwDegree/(FLOAT64)a_ptFM_v2_Model->uwAngleTableScale) >= a_ptFM_v2_Model->atDistortionCurve[uwDistCurveIndex].eAngleDegree)
            {
                uwDistCurveIndex++;
            }

            a_ptFM_v2_Model->puwAngleTable[uwDegree] = uwDistCurveIndex - 1;
        }
        else
        {
            a_ptFM_v2_Model->uwLengthOfAngleTable = uwDegree - 1;
            a_ptFM_v2_Model->puwAngleTable[uwDegree] = a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1;
            break;
        }

        assert(uwDegree < a_ptFM_v2_Model->uwLengthOfAngleTable);

    }

}

////////////////////////////////////////////////////////////////////////////////////////////
static FLOAT64 Di2Angle(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eDi)
{

    const alFM_v2_1_Distortion * ptDistortion = NULL;
    FLOAT64 eRealHeight, eAngle;
    
    INT32 lDiInt = alMIN((INT32)eDi, a_ptFM_v2_Model->uwLengthOfDistortPixelTable - 1);

    // 計算 Real Height
    eRealHeight = eDi * a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0;

    // 找到 Di 在 Curve 的位置
    ptDistortion = a_ptFM_v2_Model->atDistortionCurve + a_ptFM_v2_Model->puwDistortPixelTable[lDiInt];

    // 使用內插計算出 Angle
    if(a_ptFM_v2_Model->puwDistortPixelTable[lDiInt] == a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1)
    {
        eAngle = ptDistortion->eAngleDegree;
    }
    else
    {
        eAngle = ptDistortion->eAngleDegree + (eRealHeight - ptDistortion->eRealHeight) * (ptDistortion->eAngleInterval) / (ptDistortion->eRealHeightInterval);
    }

    return eAngle;

}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Distorted2Undistorted_Sphere(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eDistX, FLOAT64 eDistY, FLOAT64 * peUnDistX, FLOAT64 * peUnDistY, FLOAT64 * peUnDistZ)
{
    FLOAT64 eDi, eTheta, eSinPhi, eCosPhi, eSinTheta, eCosTheta;

    // 計算 X, Y 與 COD 的距離
    eDistX = (eDistX - a_ptFM_v2_Model->uwCOD_X) / a_ptFM_v2_Model->eResizeRatio;
    eDistY = eDistY - a_ptFM_v2_Model->uwCOD_Y;

    if(eDistX == 0 && eDistY == 0)
    {

        // 計算出 反魚眼 座標
        (*peUnDistX) = 0;
        (*peUnDistY) = 0;
        (*peUnDistZ) = a_ptFM_v2_Model->eFocalLength;

    }
    else
    {

        // 計算 Pixel Di
        eDi = sqrt(eDistX * eDistX + eDistY * eDistY);

        // 由內插查表得到 theta angle
        eTheta = Di2Angle(a_ptFM_v2_Model, eDi) * alPI / 180.0;

        // 計算 phi angle
        //FLOAT64 ePhi = atan2(eDistY, eDistX);

        // 計算 phi, theta 的 sin , cos
        eSinPhi = eDistY / eDi;
        eCosPhi = eDistX / eDi;
        eSinTheta = sin(eTheta);
        eCosTheta = cos(eTheta);

        // 計算出 反魚眼 座標
        (*peUnDistX) = a_ptFM_v2_Model->eFocalLength * eSinTheta * eCosPhi;
        (*peUnDistY) = a_ptFM_v2_Model->eFocalLength * eSinTheta * eSinPhi;
        (*peUnDistZ) = a_ptFM_v2_Model->eFocalLength * eCosTheta;

    }
}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Distorted2Undistorted_SpherePixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eDistX, FLOAT64 eDistY, FLOAT64 * peUnDistX, FLOAT64 * peUnDistY)
{
    FLOAT64 eUnDistZ = 0.;

    alFM_v2_1_Distorted2Undistorted_Sphere(a_ptFM_v2_Model, eDistX, eDistY, peUnDistX, peUnDistY, &eUnDistZ);

    // 計算出 反魚眼 座標
    (*peUnDistX) = (*peUnDistX) * 1000000.0 / a_ptFM_v2_Model->ulSensorPixelSize + (a_ptFM_v2_Model->uwDestWidth>>1);
    (*peUnDistY) = (*peUnDistY) * 1000000.0 / a_ptFM_v2_Model->ulSensorPixelSize + (a_ptFM_v2_Model->uwDestHeight>>1);

}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Distorted2Undistorted_Planar(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eDistX, FLOAT64 eDistY, FLOAT64 * peUnDistX, FLOAT64 * peUnDistY)
{

    FLOAT64 eDu;

    // 計算 X, Y 與 COD 的距離
    FLOAT64 eDistX_ = (eDistX - a_ptFM_v2_Model->uwCOD_X) / a_ptFM_v2_Model->eResizeRatio;
    FLOAT64 eDistY_ = eDistY - a_ptFM_v2_Model->uwCOD_Y;

    if(eDistX_ == 0 && eDistY_ == 0)
    {
        // 計算出 反魚眼 座標
        (*peUnDistX) = 0;
        (*peUnDistY) = 0;
    }
    else
    {

        // 計算 Pixel Di
        FLOAT64 eDi = sqrt(eDistX_ * eDistX_ + eDistY_ * eDistY_);

        // 由內插查表得到 theta angle
        FLOAT64 eTheta = Di2Angle(a_ptFM_v2_Model, eDi) * alPI / 180.0;

        // 計算 phi, theta 的 sin , cos
        FLOAT64 eSinPhi = eDistY_ / eDi;
        FLOAT64 eCosPhi = eDistX_ / eDi;
        FLOAT64 eTanTheta = tan(eTheta);

        eDu = a_ptFM_v2_Model->eFocalLength * eTanTheta;
        
        (*peUnDistX) = eDu * eCosPhi;
        (*peUnDistY) = eDu * eSinPhi;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Distorted2Undistorted_PlanarPixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eDistX, FLOAT64 eDistY, FLOAT64 * peUnDistX, FLOAT64 * peUnDistY)
{
    alFM_v2_1_Distorted2Undistorted_Planar(a_ptFM_v2_Model, eDistX, eDistY, peUnDistX, peUnDistY);

    (*peUnDistX) = (*peUnDistX) * 1000000.0 / a_ptFM_v2_Model->ulSensorPixelSize + (a_ptFM_v2_Model->uwDestWidth>>1);
    (*peUnDistY) = (*peUnDistY) * 1000000.0 / a_ptFM_v2_Model->ulSensorPixelSize + (a_ptFM_v2_Model->uwDestHeight>>1);
}

////////////////////////////////////////////////////////////////////////////////////////////
static FLOAT64 Angle2Di(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eAngle)
{

    const alFM_v2_1_Distortion * ptDistortion = NULL;
    FLOAT64 eRealHeight, eDi;
    
    INT32 lAngleInt = alMIN((INT32)(eAngle*(FLOAT64)a_ptFM_v2_Model->uwAngleTableScale), a_ptFM_v2_Model->uwLengthOfAngleTable - 1);

    // 找到 Di 在 Curve 的位置
    ptDistortion = a_ptFM_v2_Model->atDistortionCurve + a_ptFM_v2_Model->puwAngleTable[lAngleInt];

    // 使用內插計算出 Angle
    if(a_ptFM_v2_Model->puwAngleTable[lAngleInt] == a_ptFM_v2_Model->uwLengthOfDistortionCurve - 1)
    {
        eRealHeight = ptDistortion->eRealHeight;
    }
    else
    {
        eRealHeight = ptDistortion->eRealHeight + (eAngle - ptDistortion->eAngleDegree) * (ptDistortion->eRealHeightInterval) / (ptDistortion->eAngleInterval);
    }

    // 計算 Real Height
    eDi = eRealHeight / (a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0);

    return eDi;

}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Undistorted2Distorted_Sphere(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eUnDistX, FLOAT64 eUnDistY, FLOAT64 eUnDistZ, FLOAT64 * peDistX, FLOAT64 * peDistY)
{

    FLOAT64 eR, eTheta, ePhi, eDi, eCosPhi, eSinPhi, eEd;

    if(eUnDistX == 0. && eUnDistY == 0.)
    {
        (*peDistX) = a_ptFM_v2_Model->uwCOD_X;
        (*peDistY) = a_ptFM_v2_Model->uwCOD_Y;
        return;
    }

    eR = sqrt(eUnDistX * eUnDistX + eUnDistY * eUnDistY + eUnDistZ * eUnDistZ);

    eTheta = acos(eUnDistZ / eR);
    ePhi = atan2(eUnDistY, eUnDistX);

    eEd = sqrt(eUnDistX * eUnDistX + eUnDistY * eUnDistY);
    eSinPhi = eUnDistY / eEd;
    eCosPhi = eUnDistX / eEd;

    eDi = Angle2Di(a_ptFM_v2_Model, eTheta * 180.0 / alPI);

    (*peDistX) = (eDi * eCosPhi) * a_ptFM_v2_Model->eResizeRatio + a_ptFM_v2_Model->uwCOD_X;
    (*peDistY) = (eDi * eSinPhi) + a_ptFM_v2_Model->uwCOD_Y;

}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Undistorted2Distorted_SpherePixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eUnDistX, FLOAT64 eUnDistY, FLOAT64 * peDistX, FLOAT64 * peDistY)
{

    FLOAT64 eR, eTheta, ePhi, eDi, eCosPhi, eSinPhi, eEd, eUnDistZ;

    eUnDistX = (eUnDistX - (a_ptFM_v2_Model->uwDestWidth>>1)) * (a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0);
    eUnDistY = (eUnDistY - (a_ptFM_v2_Model->uwDestHeight>>1)) * (a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0);

    eR = a_ptFM_v2_Model->eFocalLength;

    eUnDistZ = eR * eR - eUnDistX * eUnDistX - eUnDistY * eUnDistY;

    if((eUnDistX == 0 && eUnDistY == 0) || eUnDistZ < 0.)
    {
        (*peDistX) = a_ptFM_v2_Model->uwCOD_X;
        (*peDistY) = a_ptFM_v2_Model->uwCOD_Y;
        return;
    }

    eUnDistZ = sqrt(eUnDistZ);

    eTheta = acos(eUnDistZ / eR);
    ePhi = atan2(eUnDistY, eUnDistX);

    eEd = sqrt(eUnDistX * eUnDistX + eUnDistY * eUnDistY);
    eSinPhi = eUnDistY / eEd;
    eCosPhi = eUnDistX / eEd;

    eDi = Angle2Di(a_ptFM_v2_Model, eTheta * 180.0 / alPI);

    (*peDistX) = (eDi * eCosPhi) * a_ptFM_v2_Model->eResizeRatio + a_ptFM_v2_Model->uwCOD_X;
    (*peDistY) = (eDi * eSinPhi) + a_ptFM_v2_Model->uwCOD_Y;

}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_Undistorted2Distorted_PlanarPixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 eUnDistX, FLOAT64 eUnDistY, FLOAT64 * peDistX, FLOAT64 * peDistY)
{

    FLOAT64 eDu, eTheta, ePhi, eDi, eCosPhi, eSinPhi, eEd;

    eUnDistX = (eUnDistX - (a_ptFM_v2_Model->uwDestWidth>>1)) * (a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0);
    eUnDistY = (eUnDistY - (a_ptFM_v2_Model->uwDestHeight>>1)) * (a_ptFM_v2_Model->ulSensorPixelSize / 1000000.0);

    eDu = sqrt(eUnDistX * eUnDistX + eUnDistY * eUnDistY);

    if(eDu == 0)
    {
        (*peDistX) = a_ptFM_v2_Model->uwCOD_X;
        (*peDistY) = a_ptFM_v2_Model->uwCOD_Y;
        return;
    }

    eTheta = atan(eDu / a_ptFM_v2_Model->eFocalLength);
    ePhi = atan2(eUnDistY, eUnDistX);

    eEd = sqrt(eUnDistX * eUnDistX + eUnDistY * eUnDistY);
    eSinPhi = eUnDistY / eEd;
    eCosPhi = eUnDistX / eEd;

    eDi = Angle2Di(a_ptFM_v2_Model, eTheta * 180.0 / alPI);

    (*peDistX) = (eDi * eCosPhi) * a_ptFM_v2_Model->eResizeRatio + a_ptFM_v2_Model->uwCOD_X;
    (*peDistY) = (eDi * eSinPhi) + a_ptFM_v2_Model->uwCOD_Y;

}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_FreeBuffer(alFM_v2_1_Model * a_ptFM_v2_Model)
{
    if(a_ptFM_v2_Model->puwDistortPixelTable != NULL)
        free(a_ptFM_v2_Model->puwDistortPixelTable);
    if(a_ptFM_v2_Model->puwAngleTable != NULL)
        free(a_ptFM_v2_Model->puwAngleTable);
}

/** \endcond DOXYGEN_EXCLUDE */
