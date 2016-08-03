
#include "alMANUALK/alMANUALK_Def.h"
#include "alHexData.h" // for cfg %parameter import and export
#include "alCameraInfo.h"


#ifdef WIN32
#include "alINI.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MANUALK_LoadDefault(alMANUALK_CameraCfg  a_atMANUALK_Cfg[alMANUALK_NUM_BV_CHANNEL])
{
    // Camera Params
    // 1. Camera Params - BV Front
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].ulImageWidth = SIM_DEFAULT_CAM_WIDTH_BV_FRONT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].ulImageHeight = SIM_DEFAULT_CAM_HEIGHT_BV_FRONT;
   

    // 2. Camera Params - BV Back
    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].ulImageWidth = SIM_DEFAULT_CAM_WIDTH_BV_BACK;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].ulImageHeight = SIM_DEFAULT_CAM_HEIGHT_BV_BACK;
 

    // 3. Camera Params - BV Left
    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].ulImageWidth = SIM_DEFAULT_CAM_WIDTH_BV_LEFT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].ulImageHeight = SIM_DEFAULT_CAM_HEIGHT_BV_LEFT;
  

    // 4. Camera Params - BV Right
    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].ulImageWidth = SIM_DEFAULT_CAM_WIDTH_BV_RIGHT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].ulImageHeight = SIM_DEFAULT_CAM_HEIGHT_BV_RIGHT;
   

    // ﹍て single planar points vs. bird view points 锣传把计
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lImageWidth = SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_FRONT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lImageHeight = SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_FRONT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.fScaleFactor = SIM_DEFAULT_SINGLE_VIEW_SCALAR_FRONT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lDisplayOffset_X = SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_FRONT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lDisplayOffset_Y = SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_FRONT;
    

    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lImageWidth = SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_BACK;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lImageHeight = SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_BACK;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].tSBV_Setting.fScaleFactor = SIM_DEFAULT_SINGLE_VIEW_SCALAR_BACK;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lDisplayOffset_X = SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_BACK;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lDisplayOffset_Y = SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_BACK;

    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lImageWidth = SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_LEFT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lImageHeight = SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_LEFT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.fScaleFactor = SIM_DEFAULT_SINGLE_VIEW_SCALAR_LEFT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lDisplayOffset_X = SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_LEFT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lDisplayOffset_Y = SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_LEFT;

    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lImageWidth = SIM_DEFAULT_SINGLE_VIEW_IMG_WIDTH_RIGHT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lImageHeight = SIM_DEFAULT_SINGLE_VIEW_IMG_HEIGHT_RIGHT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.fScaleFactor = SIM_DEFAULT_SINGLE_VIEW_SCALAR_RIGHT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lDisplayOffset_X = SIM_DEFAULT_SINGLE_VIEW_OFFSET_X_RIGHT;
    a_atMANUALK_Cfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lDisplayOffset_Y = SIM_DEFAULT_SINGLE_VIEW_OFFSET_Y_RIGHT;

}

void MANUALK_CfgImport(wchar_t * a_pwcConfigFilePath, alMANUALK_CameraCfg *a_ptMANUALKCfg)
{
#ifdef WIN32
    wchar_t * pwcSectionName = L"CameraCfg";


    // BV Left
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_LEFT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_LEFT");

    

    // BV Right
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_RIGHT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_RIGHT");


    // BV Front
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_FRONT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_FRONT");


    // BV Back
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_BACK");
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_BACK");


    // Single Planar 陪ボ把计 - BV Left
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_LEFT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_LEFT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.fScaleFactor = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"SBV_SCALAR_LEFT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lDisplayOffset_X = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_X_LEFT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_LEFT].tSBV_Setting.lDisplayOffset_Y = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_Y_LEFT");

    // Single Planar 陪ボ把计 - BV Right
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_RIGHT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_RIGHT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.fScaleFactor = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"SBV_SCALAR_RIGHT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lDisplayOffset_X = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_X_RIGHT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_RIGHT].tSBV_Setting.lDisplayOffset_Y = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_Y_RIGHT");

    // Single Planar 陪ボ把计 - BV Front
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_FRONT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_FRONT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.fScaleFactor = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"SBV_SCALAR_FRONT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lDisplayOffset_X = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_X_FRONT");
    a_ptMANUALKCfg[alCAMERAINFO_BV_FRONT].tSBV_Setting.lDisplayOffset_Y = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_Y_FRONT");

    // Single Planar 陪ボ把计 - BV Back
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_BACK");
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_BACK");
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].tSBV_Setting.fScaleFactor = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"SBV_SCALAR_BACK");
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lDisplayOffset_X = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_X_BACK");
    a_ptMANUALKCfg[alCAMERAINFO_BV_BACK].tSBV_Setting.lDisplayOffset_Y = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SBV_OFFSET_Y_BACK");
#endif
}

UINT32 MANUALK_CfgExportHex(
    UINT32 a_ulSectionID,
    alMANUALK_CameraCfg *a_ptCfg,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT32 ulViewID = 0x0000; // 0: view 0 1: view 1 2: view 2  3: view 3
    UINT32 ulViewID_Step = 0x0100;
    UINT32 ulSubFuncID = 0x2000;
    UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0;

    UINT32 *pulDataSectionBuffer = (UINT32 *)a_pucDataSectionBuffer; // for debug

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    // start to export each view
    for (lCAMId = 0; lCAMId < alMANUALK_NUM_BV_CHANNEL; lCAMId++)
    {
        ulItemID = 0x0000;
        // ulImageWidth
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCfg[lCAMId].ulImageWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // ulImageHeight
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptCfg[lCAMId].ulImageHeight, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tSBV_Setting.fScaleFactor
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCfg[lCAMId].tSBV_Setting.fScaleFactor, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tSBV_Setting.lDisplayOffset_X
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg[lCAMId].tSBV_Setting.lDisplayOffset_X, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tSBV_Setting.lDisplayOffset_Y
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg[lCAMId].tSBV_Setting.lDisplayOffset_Y, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tSBV_Setting.lImageWidth
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg[lCAMId].tSBV_Setting.lImageWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tSBV_Setting.lImageHeight
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg[lCAMId].tSBV_Setting.lImageHeight, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        ulViewID += ulViewID_Step;
    }

    return ulSectionBufLen;
}

static void MANUALK_CfgImportHex_SingleCamera(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, alMANUALK_CameraCfg *a_ptCfg)
{
    switch (a_ulDataID)
    {
    case 0x000:    // ulImageWidth
    {
        a_ptCfg->ulImageWidth = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001:    // ulImageHeight
    {
        a_ptCfg->ulImageHeight = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002:    // tSBV_Setting.fScaleFactor
    {
        a_ptCfg->tSBV_Setting.fScaleFactor = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003:    // tSBV_Setting.lDisplayOffset_X
    {
        a_ptCfg->tSBV_Setting.lDisplayOffset_X = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004:    // tSBV_Setting.lDisplayOffset_Y
    {
        a_ptCfg->tSBV_Setting.lDisplayOffset_Y = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005:    // tSBV_Setting.lImageWidth
    {
        a_ptCfg->tSBV_Setting.lImageWidth = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006:    // tSBV_Setting.lImageHeight
    {
        a_ptCfg->tSBV_Setting.lImageHeight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    }
}

void MANUALK_CfgImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, alMANUALK_CameraCfg *a_ptCfg)
{
    UINT32 ulSubDataID = 0;

    ulSubDataID = a_ulDataID & 0x00FF;

    switch (a_ulDataID & 0x0F00)
    {
    case 0x0000:    // View 0
    {
        MANUALK_CfgImportHex_SingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, &a_ptCfg[0]);
    }
    break;

    case 0x0100:    // View 1
    {
        MANUALK_CfgImportHex_SingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, &a_ptCfg[1]);
    }
    break;

    case 0x0200:    // View 2
    {
        MANUALK_CfgImportHex_SingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, &a_ptCfg[2]);
    }
    break;

    case 0x0300:    // View 3
    {
        MANUALK_CfgImportHex_SingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, &a_ptCfg[3]);
    }
    break;

    default:
        // Do nothing
        // printf("Invalid Data ID: 0x%X\n - NanualK_CfgImport\n", a_ulDataID);
    break;
    }
}



