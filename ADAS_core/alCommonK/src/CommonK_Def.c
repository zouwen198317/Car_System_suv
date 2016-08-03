#include "CommonK_Def.h"
#ifdef WIN32
#include "alINI.h"
#endif
#include "alHexData.h"

void COMMONK_LoadDefault(alCOMMONK_CommonCfg *a_ptalCOMMONK_CommonCfg)
{
    //a_ptalCOMMONK_CommonCfg->ulCarCalibrated = SIM_DEFAULT_CAR_CALIBRATED;
    a_ptalCOMMONK_CommonCfg->ulCarModel = SIM_DEFAULT_CAR_MODEL;
    a_ptalCOMMONK_CommonCfg->tDisplayStartPoint.lX = SIM_DEFAULT_DISPLAY_START_POINT_X;
    a_ptalCOMMONK_CommonCfg->tDisplayStartPoint.lY = SIM_DEFAULT_DISPLAY_START_POINT_X;
    a_ptalCOMMONK_CommonCfg->tDisplayAreaSize.lX = SIM_DEFAULT_DISPLAY_IMAGE_WIDTH;
    a_ptalCOMMONK_CommonCfg->tDisplayAreaSize.lY = SIM_DEFAULT_DISPLAY_IMAGE_HEIGHT;
    a_ptalCOMMONK_CommonCfg->fLCDRatio = SIM_DEFAULT_DISPLAY_RATIO;
    a_ptalCOMMONK_CommonCfg->ulCarLength = SIM_DEFAULT_CAR_LEN;
    a_ptalCOMMONK_CommonCfg->ulCarWidth = SIM_DEFAULT_CAR_WID;
    a_ptalCOMMONK_CommonCfg->ulMaxSteeringAngle = SIM_DEFAULT_CAR_MAX_STEER_ANGLE;
    a_ptalCOMMONK_CommonCfg->ulFrontWheelAxle2Head = SIM_DEFAULT_CAR_FW2HEAD_DISTANCE;
    a_ptalCOMMONK_CommonCfg->ulRearWheelAxle2Tail = SIM_DEFAULT_CAR_BW2TAIL_DISTANCE;
    a_ptalCOMMONK_CommonCfg->ulWheelAxleDistance = SIM_DEFAULT_CAR_FBW_AXLE_DISTANCE;
    a_ptalCOMMONK_CommonCfg->ulFrontWheelAxleWidth = SIM_DEFAULT_CAR_FW_AXLE_WIDTH;
    a_ptalCOMMONK_CommonCfg->ulRearWheelAxleWidth = SIM_DEFAULT_CAR_BW_AXLE_WIDTH;
    a_ptalCOMMONK_CommonCfg->ulFrontFixedPoint2Head = SIM_DEFAULT_CAR_FFP2HEAD_DISTANCE;
    a_ptalCOMMONK_CommonCfg->ulFrontWheelLE2Head = SIM_DEFAULT_CAR_FWLE2HEAD_DISTANCE;
    a_ptalCOMMONK_CommonCfg->ucFisheyeModelVersion = SIM_DEFAULT_FM_MODEL_VERSION;
}

void COMMONK_CfgImportByINI(wchar_t * a_pwcConfigFilePath, alCOMMONK_CommonCfg *a_ptCommonCfg)
{
#ifdef WIN32
    wchar_t * pwcSectionName = L"CommonCfg";

    // Car Model ID
    a_ptCommonCfg->ulCarModel = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_MODEL");

    // Display Start Point
    a_ptCommonCfg->tDisplayStartPoint.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DISPLAY_START_POINT_X");
    a_ptCommonCfg->tDisplayStartPoint.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DISPLAY_START_POINT_Y");

    // Display Area Size 
    a_ptCommonCfg->tDisplayAreaSize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DISPLAY_IMAGE_WIDTH");
    a_ptCommonCfg->tDisplayAreaSize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DISPLAY_IMAGE_HEIGHT");

    // Display Ratio 
    a_ptCommonCfg->fLCDRatio = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"DISPLAY_RATIO");

    // Version number of Fisheye Model.
    a_ptCommonCfg->ucFisheyeModelVersion = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FM_MODEL_VERSION");

    // Car Length 
    a_ptCommonCfg->ulCarLength = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_LEN");

    // Car Width
    a_ptCommonCfg->ulCarWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_WID");

    // Maximum Steering Angle 
    a_ptCommonCfg->ulMaxSteeringAngle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_MAX_STEER_ANGLE");

    // 玡近﹚翴ó繷禯瞒 
    a_ptCommonCfg->ulFrontFixedPoint2Head = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_FFP2HEAD_DISTANCE");

    // 玡近禸みó繷禯瞒
    a_ptCommonCfg->ulFrontWheelAxle2Head = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_FW2HEAD_DISTANCE");

    // 近禸みóЮ禯瞒
    a_ptCommonCfg->ulRearWheelAxle2Tail = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_BW2TAIL_DISTANCE");

    // 玡近禸糴
    a_ptCommonCfg->ulFrontWheelAxleWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_FW_AXLE_WIDTH");

    // 近禸糴
    a_ptCommonCfg->ulRearWheelAxleWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_BW_AXLE_WIDTH");

    // 玡近禸禯
    a_ptCommonCfg->ulWheelAxleDistance = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_FBW_AXLE_DISTANCE");

    // 玡近玡絫ó繷禯瞒
    a_ptCommonCfg->ulFrontWheelLE2Head = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAR_FWLE2HEAD_DISTANCE");

    // 搽àó进锣そΑ把计
    a_ptCommonCfg->fSteerParamA = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAR_STEER_PARA_A");
    a_ptCommonCfg->fSteerParamB = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAR_STEER_PARA_B");
#endif
}


void COMMONK_CommonCfgImportByHexData(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucDataBuf, alCOMMONK_CommonCfg *a_ptCfg)
{
    UINT32 ulDataIndex = 0;

    switch (a_ulDataID & 0xFFFF)
    {
    case 0x0000:    // Car Model ID
    {
        a_ptCfg->ulCarModel = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0001:    // Display Area Size X
    {
        a_ptCfg->tDisplayAreaSize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0002:    // Display Area Size Y
    {
        a_ptCfg->tDisplayAreaSize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0003:     // Display Start Point X
    {
        a_ptCfg->tDisplayStartPoint.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0004:    // Display Start Point Y
    {
        a_ptCfg->tDisplayStartPoint.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0005:     // fLCDRatio 
    {
        a_ptCfg->fLCDRatio = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0006:     // Version number of Fisheye Model.
    {
        a_ptCfg->ucFisheyeModelVersion = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0007:    // Car Length
    {
        a_ptCfg->ulCarLength = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0008:    // Car Width
    {
        a_ptCfg->ulCarWidth = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0009:    // Maximum Steering Angle
    {
        a_ptCfg->ulMaxSteeringAngle = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x000A:    // 玡近禸糴
    {
        a_ptCfg->ulFrontWheelAxleWidth = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x000B:    // 近禸糴
    {
        a_ptCfg->ulRearWheelAxleWidth = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x000C:    // 玡近禸禯
    {
        a_ptCfg->ulWheelAxleDistance = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x000D:    // 玡近禸みó繷禯瞒
    {
        a_ptCfg->ulFrontWheelAxle2Head = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x000E:    // 近禸みóЮ禯瞒
    {
        a_ptCfg->ulRearWheelAxle2Tail = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x000F:    // 玡近﹚翴ó繷禯瞒
    {
        a_ptCfg->ulFrontFixedPoint2Head = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0010:    // 玡近玡絫ó繷禯瞒
    {
        a_ptCfg->ulFrontWheelLE2Head = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    case 0x0011:    // 搽àó进锣そΑ把计 - A
    {
        a_ptCfg->fSteerParamA = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucDataBuf);
    }
    case 0x0012:    // 搽àó进锣そΑ把计 - B
    {
        a_ptCfg->fSteerParamB = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucDataBuf);
    }
    break;
    default:    // Do nothing
        DEBUG_Printf("Invalid Data ID: 0x%X\n - CommonkCfgImport\n", a_ulDataID);
    break;
    }
}

UINT32 COMMONK_CommonCfgExportByHexData(
    UINT32 a_ulSectionID,
    alCOMMONK_CommonCfg *a_ptCommonCfg,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT8 ucNullFlag = 0;


    UINT32 *pulDataSectionBuffer = (UINT32 *)a_pucDataSectionBuffer; // for debug

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    // Common Config
    //  Car Model
    ulDataID = (a_ulSectionID << 16) + 0x0000;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulCarModel, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  Display width
    ulDataID = (a_ulSectionID << 16) + 0x0001;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCommonCfg->tDisplayAreaSize.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  Display height
    ulDataID = (a_ulSectionID << 16) + 0x0002;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCommonCfg->tDisplayAreaSize.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  start point width
    ulDataID = (a_ulSectionID << 16) + 0x0003;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCommonCfg->tDisplayStartPoint.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  start point height
    ulDataID = (a_ulSectionID << 16) + 0x0004;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCommonCfg->tDisplayStartPoint.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  fLCDRatio
    ulDataID = (a_ulSectionID << 16) + 0x0005;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCommonCfg->fLCDRatio, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ucFisheyeModelVersion
    ulDataID = (a_ulSectionID << 16) + 0x0006;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCommonCfg->ucFisheyeModelVersion, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulCarLength
    ulDataID = (a_ulSectionID << 16) + 0x0007;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulCarLength, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulCarWidth
    ulDataID = (a_ulSectionID << 16) + 0x0008;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulCarWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulMaxSteeringAngle
    ulDataID = (a_ulSectionID << 16) + 0x0009;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulMaxSteeringAngle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulFrontWheelAxleWidth
    ulDataID = (a_ulSectionID << 16) + 0x000A;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulFrontWheelAxleWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulRearWheelAxleWidth
    ulDataID = (a_ulSectionID << 16) + 0x000B;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulRearWheelAxleWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulWheelAxleDistance
    ulDataID = (a_ulSectionID << 16) + 0x000C;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulWheelAxleDistance, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulFrontWheelAxle2Head
    ulDataID = (a_ulSectionID << 16) + 0x000D;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulFrontWheelAxle2Head, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulRearWheelAxle2Tail
    ulDataID = (a_ulSectionID << 16) + 0x000E;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulRearWheelAxle2Tail, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulFrontFixedPoint2Head
    ulDataID = (a_ulSectionID << 16) + 0x000F;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulFrontFixedPoint2Head, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  ulFrontWheelLE2Head
    ulDataID = (a_ulSectionID << 16) + 0x0010;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCommonCfg->ulFrontWheelLE2Head, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  fSteerParamA
    ulDataID = (a_ulSectionID << 16) + 0x0011;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCommonCfg->fSteerParamA, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    //  fSteerParamB
    ulDataID = (a_ulSectionID << 16) + 0x0012;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCommonCfg->fSteerParamB, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    

    return ulSectionBufLen;

}
