
#include "alFM_v2_1_Def.h"
#include "alFM_v2_1_Default.h"
#include "alHexData.h"
#include <assert.h>
#include "basedef.h"

/** \cond DOXYGEN_EXCLUDE */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_LoadDefault(alFM_v2_1_DefaultCameraModel a_ucDefaultCameraModel, alFM_v2_1_ModelCfg * a_ptCameraFMCfg)
{
    alFM_v2_1_LoadDefaultModedCfg(a_ucDefaultCameraModel, a_ptCameraFMCfg);
}


void alFM_v2_1_CfgImportHex(
    UINT32 a_ulDataID,
    UINT32 a_ulDataLength, UINT8 * a_pucBuffer,
    alFM_v2_1_ModelCfg *a_ptFMCfg
    )
{
    UINT32 ulSubDataID = 0;

    ulSubDataID = a_ulDataID & 0xFFFF;

    switch (ulSubDataID)
    {
    case 0x0000:    // ulImageWidth
    {
        a_ptFMCfg->ulImageWidth = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0001:    // ulImageHeight
    {
        a_ptFMCfg->ulImageHeight = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0002:    // uwCOD_X
    {
        a_ptFMCfg->uwCOD_X = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0003:    // uwCOD_Y
    {
        a_ptFMCfg->uwCOD_Y = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0004:    // uwSrcSensorWidth
    {
        a_ptFMCfg->uwSrcSensorWidth = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0005:    // uwSrcSensorHeight
    {
        a_ptFMCfg->uwSrcSensorHeight = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0006:    // ulSensorPixelSize
    {
        a_ptFMCfg->ulSensorPixelSize = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0007:    // eFOV_H
    {
        a_ptFMCfg->eFOV_H = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0008:    // eFocalLength
    {
        a_ptFMCfg->eFocalLength = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0009:    // eUD_FOV_H
    {
        a_ptFMCfg->eUD_FOV_H = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000A:    // eHResizeRatio
    {
        a_ptFMCfg->eHResizeRatio = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000B:    // uwLengthOfDistortionCurve
    {
        a_ptFMCfg->uwLengthOfDistortionCurve = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000C:    // uwAngleTableScale
    {
        a_ptFMCfg->uwAngleTableScale = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000D:    // aeAngleDegree
    {
        memcpy(a_ptFMCfg->aeAngleDegree, a_pucBuffer, a_ulDataLength);
    }
    break;
    case 0x000E:    // aeRealHeight
    {
        memcpy(a_ptFMCfg->aeRealHeight, a_pucBuffer, a_ulDataLength);
    }
    break;

    default:    // default
    {
        DEBUG_Printf("Invalid Data ID: 0x%X\n - alFM_v2_1_CfgImport\n", a_ulDataID);
    }
    break;
    }
}

UINT32 alFM_v2_1_SingleFisheyeModelCfgExport(
    UINT32 a_ulSectionID,
    alFM_v2_1_ModelCfg *a_ptFMCfg,
    UINT8 * a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0, lCnt = 0;

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    ulItemID = 0x0000;


    // ulImageWidth
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptFMCfg->ulImageWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // ulImageHeight
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptFMCfg->ulImageHeight, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // uwCOD_X
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFMCfg->uwCOD_X, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // uwCOD_Y
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFMCfg->uwCOD_Y, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // uwSrcSensorWidth
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFMCfg->uwSrcSensorWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // uwSrcSensorHeight
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFMCfg->uwSrcSensorHeight, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // ulSensorPixelSize
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptFMCfg->ulSensorPixelSize, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // eFOV_H
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptFMCfg->eFOV_H, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // eFocalLength
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptFMCfg->eFocalLength, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // eUD_FOV_H
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptFMCfg->eUD_FOV_H, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // eHResizeRatio
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptFMCfg->eHResizeRatio, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // uwLengthOfDistortionCurve
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFMCfg->uwLengthOfDistortionCurve, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // uwAngleTableScale
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFMCfg->uwAngleTableScale, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // aeAngleDegree
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_DataPack(ulDataID, a_ptFMCfg->uwLengthOfDistortionCurve*sizeof(FLOAT64), (UINT8*)(a_ptFMCfg->aeAngleDegree), a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // aeRealHeight
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_DataPack(ulDataID, a_ptFMCfg->uwLengthOfDistortionCurve*sizeof(FLOAT64), (UINT8*)(a_ptFMCfg->aeRealHeight), a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    return ulSectionBufLen;
}



#ifdef WIN32
#include <stdio.h>
#include "alINI.h"
#include <sys/stat.h>

/**
\brief Load distortion cruve from specified file.
\param a_pwcDistortionCurveFilePath [IN] The specified file path.
\param a_ptFisheyeModelCfg [OUT] The buffer to store data.
*/
static void SingleDistortionCurve_v2_Import(const wchar_t * a_pwcDistortionCurveFilePath, alFM_v2_1_ModelCfg * a_ptFisheyeModelCfg)
{
    FILE * ptFile = 0;
    char acFirstLine[255];
    INT32 lIndex = 0;

    _wfopen_s(&ptFile, a_pwcDistortionCurveFilePath, L"r");

    if (!ptFile)
    {
        DEBUG_PrintfW(L"SingleDistortionCurve_v2_Import: Can not load file: \"%s\"\n", a_pwcDistortionCurveFilePath);
        return;
    }

    // 菠筁材︽
    fgets(acFirstLine, 255, ptFile);

    lIndex = 0;
    while (lIndex < a_ptFisheyeModelCfg->uwLengthOfDistortionCurve
        && fscanf_s(ptFile, "%lf%lf%*lf%*lf", &(a_ptFisheyeModelCfg->aeAngleDegree[lIndex]),
        &(a_ptFisheyeModelCfg->aeRealHeight[lIndex])))
    {
        lIndex++;
    }

    fclose(ptFile);

    assert(lIndex == a_ptFisheyeModelCfg->uwLengthOfDistortionCurve);

}

/**
\brief Load distortion cruve from specified file.
\param a_pwcConfigFilePath [IN] The specified config INI file path.
\param a_ptFisheyeModelCfg [OUT] The buffer to store data.
*/
static void SingleFisheyeModel_v2_Import(const wchar_t * a_pwcConfigFilePath, alFM_v2_1_ModelCfg * a_ptFisheyeModelCfg)
{
    wchar_t * pwcSectionName = L"CameraFisheyeModelCfg";
    UINT8 ucIndex = 0;

    wchar_t awcDistortionCurveFileName[MAX_PATH];
    wchar_t awcDistortionCurveFilePath[MAX_PATH];
    wchar_t awcDrive[10];
    wchar_t awcDir[MAX_PATH];
    wchar_t awcFile[MAX_PATH];
    wchar_t awcExt[MAX_PATH];

    struct _stat tFileState;
    if (_wstat(a_pwcConfigFilePath, &tFileState) != 0)
    {
        DEBUG_PrintfW(L"SingleFisheyeModel_v2_Import: Can not load file: \"%s\"\n", a_pwcConfigFilePath);
        return;
    }

    _wsplitpath_s(a_pwcConfigFilePath, awcDrive, 10, awcDir, MAX_PATH, awcFile, MAX_PATH, awcExt, MAX_PATH);

    // Image 把计
    a_ptFisheyeModelCfg->ulImageWidth = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_SRC_IMAGE_WIDTH", a_ptFisheyeModelCfg->ulImageWidth);
    a_ptFisheyeModelCfg->ulImageHeight = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_SRC_IMAGE_HEIGHT", a_ptFisheyeModelCfg->ulImageHeight);

    // Lensいみ竚(COD) 把计
    a_ptFisheyeModelCfg->uwCOD_X = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_COD_X", a_ptFisheyeModelCfg->uwCOD_X);
    a_ptFisheyeModelCfg->uwCOD_Y = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_COD_Y", a_ptFisheyeModelCfg->uwCOD_Y);

    // Sensor 把计 - 
    a_ptFisheyeModelCfg->uwSrcSensorWidth = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_SRC_SENSOR_WIDTH", a_ptFisheyeModelCfg->uwSrcSensorWidth);
    a_ptFisheyeModelCfg->uwSrcSensorHeight = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_SRC_SENSOR_HEIGHT", a_ptFisheyeModelCfg->uwSrcSensorWidth);
    a_ptFisheyeModelCfg->ulSensorPixelSize = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_SENSOR_PIXEL_SIZE", a_ptFisheyeModelCfg->ulSensorPixelSize);

    // Lens+Sensor 把计
    a_ptFisheyeModelCfg->eFOV_H = alINI_GetKeyValueWithDefault_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM_FOV_H", a_ptFisheyeModelCfg->eFOV_H);
    a_ptFisheyeModelCfg->eUD_FOV_H = alINI_GetKeyValueWithDefault_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM_FOV_H_UD", a_ptFisheyeModelCfg->eUD_FOV_H);
    a_ptFisheyeModelCfg->eFocalLength = alINI_GetKeyValueWithDefault_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM_FOCAL_LENGTH", a_ptFisheyeModelCfg->eFocalLength);

    // Resize Ratio
    a_ptFisheyeModelCfg->eHResizeRatio = alINI_GetKeyValueWithDefault_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM_HORIZONTAL_RESIZE_RATIO", a_ptFisheyeModelCfg->eHResizeRatio);

    // Distortion Curve 把计
    a_ptFisheyeModelCfg->uwAngleTableScale = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_ANGLE_TABLE_SCALE", a_ptFisheyeModelCfg->uwAngleTableScale);
    a_ptFisheyeModelCfg->uwLengthOfDistortionCurve = alINI_GetKeyValueWithDefault_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_LENGTH_DISTORTION_CURVE", a_ptFisheyeModelCfg->uwLengthOfDistortionCurve);

    // Curveぃ禬筁程
    assert(a_ptFisheyeModelCfg->uwLengthOfDistortionCurve <= alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH);

    // Distortion Curve File
    alINI_GetKeyValue_CW(a_pwcConfigFilePath, pwcSectionName, L"FM_DISTORTION_CURVE_FILE", awcDistortionCurveFileName, MAX_PATH);

    _wmakepath_s(awcDistortionCurveFilePath, MAX_PATH, awcDrive, awcDir, awcDistortionCurveFileName, L"");

    // Load distortion curve from specified file.
    SingleDistortionCurve_v2_Import(awcDistortionCurveFilePath, a_ptFisheyeModelCfg);
}

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_LoadUserCfgByINI(const wchar_t * a_pwcFileName, alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg) // 疭﹚ Camera Confg INI File, ex. CameraFisheyeParam_v2-Sparrow190.ini
{
    SingleFisheyeModel_v2_Import(a_pwcFileName, a_ptFM_v2_Cfg);
    //DEBUG_Printf("FM_v2: The code to load user config by INI is not ready.\n");
}
#endif // #ifdef WIN32

/** \endcond DOXYGEN_EXCLUDE */
