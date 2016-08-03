
#include "alAlleyViewDef.h"
#include "alHexData.h"
#include "basedef.h"
#ifdef WIN32
#include "alINI.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alALLEYVIEW_LoadDefault(alALLEYVIEW_Cfg *a_tSAV_Cfg, alALLEYVIEW_Cfg *a_tFAV_Cfg)
{
	//Load Alley View Cfg
	a_tSAV_Cfg->ucFunctionEnabled= SIM_DEFAULT_SAV_FUNCTION_ENABLED;
	a_tSAV_Cfg->tStartPoint.lX    = SIM_DEFAULT_SAV_START_POINT_X;
	a_tSAV_Cfg->tStartPoint.lY    = SIM_DEFAULT_SAV_START_POINT_Y;
	a_tSAV_Cfg->tAreaSize.lX      = SIM_DEFAULT_SAV_AREA_SIZE_WIDTH;
	a_tSAV_Cfg->tAreaSize.lY      = SIM_DEFAULT_SAV_AREA_SIZE_HEIGHT;
	a_tSAV_Cfg->fViewingAngle    = SIM_DEFAULT_SAV_VIEWING_ANGLE;
	a_tSAV_Cfg->ulFOV            = SIM_DEFAULT_SAV_HORI_FOV;
	a_tSAV_Cfg->lVCOffsetX       = SIM_DEFAULT_SAV_DISPLAY_OFFSET_X;
	a_tSAV_Cfg->lVCOffsetY       = SIM_DEFAULT_SAV_DISPLAY_OFFSET_Y;
	a_tSAV_Cfg->ulSoftPixels     = SIM_DEFAULT_SAV_DISPLAY_SMOOTH;
	a_tSAV_Cfg->aApexPoints[0].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_0_X;
	a_tSAV_Cfg->aApexPoints[0].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_0_Y;
	a_tSAV_Cfg->aApexPoints[1].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_1_X;
	a_tSAV_Cfg->aApexPoints[1].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_1_Y;
	a_tSAV_Cfg->aApexPoints[2].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_2_X;
	a_tSAV_Cfg->aApexPoints[2].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_2_Y;
	a_tSAV_Cfg->aApexPoints[3].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_3_X;
	a_tSAV_Cfg->aApexPoints[3].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_3_Y;
	a_tSAV_Cfg->aApexPoints[4].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_4_X;
	a_tSAV_Cfg->aApexPoints[4].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_4_Y;
	a_tSAV_Cfg->aApexPoints[5].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_5_X;
	a_tSAV_Cfg->aApexPoints[5].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_5_Y;
	a_tSAV_Cfg->aApexPoints[6].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_6_X;
	a_tSAV_Cfg->aApexPoints[6].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_6_Y;
	a_tSAV_Cfg->aApexPoints[7].lX = SIM_DEFAULT_SAV_DISPLAY_POINT_7_X;
	a_tSAV_Cfg->aApexPoints[7].lY = SIM_DEFAULT_SAV_DISPLAY_POINT_7_Y;

    //Full
	a_tFAV_Cfg->ucFunctionEnabled= SIM_DEFAULT_FAV_FUNCTION_ENABLED;
	a_tFAV_Cfg->tStartPoint.lX    = SIM_DEFAULT_FAV_START_POINT_X;
	a_tFAV_Cfg->tStartPoint.lY    = SIM_DEFAULT_FAV_START_POINT_Y;
	a_tFAV_Cfg->tAreaSize.lX      = SIM_DEFAULT_FAV_AREA_SIZE_WIDTH;
	a_tFAV_Cfg->tAreaSize.lY      = SIM_DEFAULT_FAV_AREA_SIZE_HEIGHT;
	a_tFAV_Cfg->fViewingAngle    = SIM_DEFAULT_FAV_VIEWING_ANGLE;
	a_tFAV_Cfg->ulFOV            = SIM_DEFAULT_FAV_HORI_FOV ;
	a_tFAV_Cfg->lVCOffsetX       = SIM_DEFAULT_FAV_DISPLAY_OFFSET_X  ;
	a_tFAV_Cfg->lVCOffsetY       = SIM_DEFAULT_FAV_DISPLAY_OFFSET_Y  ;
	a_tFAV_Cfg->ulSoftPixels     = SIM_DEFAULT_FAV_DISPLAY_SMOOTH;
	a_tFAV_Cfg->aApexPoints[0].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_0_X;
	a_tFAV_Cfg->aApexPoints[0].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_0_Y;
	a_tFAV_Cfg->aApexPoints[1].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_1_X;
	a_tFAV_Cfg->aApexPoints[1].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_1_Y;
	a_tFAV_Cfg->aApexPoints[2].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_2_X;
	a_tFAV_Cfg->aApexPoints[2].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_2_Y;
	a_tFAV_Cfg->aApexPoints[3].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_3_X;
	a_tFAV_Cfg->aApexPoints[3].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_3_Y;
	a_tFAV_Cfg->aApexPoints[4].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_4_X;
	a_tFAV_Cfg->aApexPoints[4].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_4_Y;
	a_tFAV_Cfg->aApexPoints[5].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_5_X;
	a_tFAV_Cfg->aApexPoints[5].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_5_Y;
	a_tFAV_Cfg->aApexPoints[6].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_6_X;
	a_tFAV_Cfg->aApexPoints[6].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_6_Y;
	a_tFAV_Cfg->aApexPoints[7].lX = SIM_DEFAULT_FAV_DISPLAY_POINT_7_X;
	a_tFAV_Cfg->aApexPoints[7].lY = SIM_DEFAULT_FAV_DISPLAY_POINT_7_Y;
}   

#ifdef WIN32
void alALLEYVIEW_CfgImportByINI(alALLEYVIEW_Cfg *a_tSAV_Cfg, alALLEYVIEW_Cfg *a_tFAV_Cfg, wchar_t *a_pwcConfigFilePath)
{
    wchar_t * pwcSectionName = L"AlleyViewCfg";

    // Small Alley View - 啟用/禁用
    a_tSAV_Cfg->ucFunctionEnabled = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_FUNCTION_ENABLED");

    // Small Alley View - 起始座標
    a_tSAV_Cfg->tStartPoint.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_START_POINT_X");
    a_tSAV_Cfg->tStartPoint.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_START_POINT_Y");

    // Small Alley View - Area_Size
    a_tSAV_Cfg->tAreaSize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_AREA_SIZE_WIDTH");
    a_tSAV_Cfg->tAreaSize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_AREA_SIZE_HEIGHT");

    // Small Alley View - 可視範圍
    a_tSAV_Cfg->fViewingAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"SAV_VIEWING_ANGLE");
    a_tSAV_Cfg->ulFOV = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_HORI_FOV");

    // Small Alley View - 畫面偏移
    a_tSAV_Cfg->lVCOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_OFFSET_X");
    a_tSAV_Cfg->lVCOffsetY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_OFFSET_Y");

    // Small Alley View - 潤邊Pixel
    a_tSAV_Cfg->ulSoftPixels = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_SMOOTH");

    // Small Alley View - 裁接點座標#0
    a_tSAV_Cfg->aApexPoints[0].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_0_X");
    a_tSAV_Cfg->aApexPoints[0].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_0_Y");

    // Small Alley View - 裁接點座標#1
    a_tSAV_Cfg->aApexPoints[1].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_1_X");
    a_tSAV_Cfg->aApexPoints[1].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_1_Y");

    // Small Alley View - 裁接點座標#2
    a_tSAV_Cfg->aApexPoints[2].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_2_X");
    a_tSAV_Cfg->aApexPoints[2].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_2_Y");

    // Small Alley View - 裁接點座標#3
    a_tSAV_Cfg->aApexPoints[3].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_3_X");
    a_tSAV_Cfg->aApexPoints[3].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_3_Y");

    // Small Alley View - 裁接點座標#4
    a_tSAV_Cfg->aApexPoints[4].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_4_X");
    a_tSAV_Cfg->aApexPoints[4].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_4_Y");

    // Small Alley View - 裁接點座標#5
    a_tSAV_Cfg->aApexPoints[5].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_5_X");
    a_tSAV_Cfg->aApexPoints[5].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_5_Y");

    // Small Alley View - 裁接點座標#6
    a_tSAV_Cfg->aApexPoints[6].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_6_X");
    a_tSAV_Cfg->aApexPoints[6].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_6_Y");

    // Small Alley View - 裁接點座標#7
    a_tSAV_Cfg->aApexPoints[7].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_7_X");
    a_tSAV_Cfg->aApexPoints[7].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"SAV_DISPLAY_POINT_7_Y");

    // Full Alley View - 啟用/禁用
    a_tFAV_Cfg->ucFunctionEnabled = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_FUNCTION_ENABLED");

    // Full alAlleyView - 起始座標
    a_tFAV_Cfg->tStartPoint.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_START_POINT_X");
    a_tFAV_Cfg->tStartPoint.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_START_POINT_Y");

    // Full alAlleyView - Area_Size
    a_tFAV_Cfg->tAreaSize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_AREA_SIZE_WIDTH");
    a_tFAV_Cfg->tAreaSize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_AREA_SIZE_HEIGHT");

    // Full alAlleyView - 可視範圍
    a_tFAV_Cfg->fViewingAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FAV_VIEWING_ANGLE");
    a_tFAV_Cfg->ulFOV = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_HORI_FOV");

    // Full alAlleyView - 畫面偏移
    a_tFAV_Cfg->lVCOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_OFFSET_X");
    a_tFAV_Cfg->lVCOffsetY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_OFFSET_Y");

    // Full alAlleyView - 潤邊Pixel
    a_tFAV_Cfg->ulSoftPixels = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_SMOOTH");

    // Full alAlleyView - 裁接點座標#0
    a_tFAV_Cfg->aApexPoints[0].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_0_X");
    a_tFAV_Cfg->aApexPoints[0].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_0_Y");

    // Full alAlleyView - 裁接點座標#1
    a_tFAV_Cfg->aApexPoints[1].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_1_X");
    a_tFAV_Cfg->aApexPoints[1].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_1_Y");

    // Full alAlleyView - 裁接點座標#2
    a_tFAV_Cfg->aApexPoints[2].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_2_X");
    a_tFAV_Cfg->aApexPoints[2].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_2_Y");

    // Full alAlleyView - 裁接點座標#3
    a_tFAV_Cfg->aApexPoints[3].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_3_X");
    a_tFAV_Cfg->aApexPoints[3].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_3_Y");

    // Full alAlleyView - 裁接點座標#4
    a_tFAV_Cfg->aApexPoints[4].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_4_X");
    a_tFAV_Cfg->aApexPoints[4].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_4_Y");

    // Full alAlleyView - 裁接點座標#5
    a_tFAV_Cfg->aApexPoints[5].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_5_X");
    a_tFAV_Cfg->aApexPoints[5].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_5_Y");

    // Full alAlleyView - 裁接點座標#6
    a_tFAV_Cfg->aApexPoints[6].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_6_X");
    a_tFAV_Cfg->aApexPoints[6].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_6_Y");

    // Full alAlleyView - 裁接點座標#7
    a_tFAV_Cfg->aApexPoints[7].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_7_X");
    a_tFAV_Cfg->aApexPoints[7].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"FAV_DISPLAY_POINT_7_Y");
}
#endif

UINT32 AV_CfgExportHex(
    UINT32 a_ulSectionID,
    alALLEYVIEW_Cfg *a_ptCfg_S,
    alALLEYVIEW_Cfg *a_ptCfg_F,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT32 ulViewID = 0x0000; // 0: global 1: view 0 2: view 1 3: view 2  4: view 3
    UINT32 ulViewID_Step = 0x1000;
    UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0, lCnt = 0;

    alALLEYVIEW_Cfg *aptCfg[2] = { 0 };

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    aptCfg[0] = a_ptCfg_S;
    aptCfg[1] = a_ptCfg_F;

    for (lIndex = 0; lIndex < 2; lIndex++)
    {
        ulItemID = 0x0000;
        // ucFunctionEnabled
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, aptCfg[lIndex]->ucFunctionEnabled, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tStartPoint.lX
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->tStartPoint.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tStartPoint.lY
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->tStartPoint.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tAreaSize.lX
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->tAreaSize.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // tAreaSize.lY
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->tAreaSize.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // fViewingAngle
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, aptCfg[lIndex]->fViewingAngle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // ulFOV
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, aptCfg[lIndex]->ulFOV, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // lVCOffsetX
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->lVCOffsetX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // lVCOffsetY
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->lVCOffsetY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // ulSoftPixels
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, aptCfg[lIndex]->ulSoftPixels, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        for (lCnt = 0; lCnt < 8; lCnt++)
        {
            // aApexPoints.lX
            ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->aApexPoints[lCnt].lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            // aApexPoints.lY
            ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, aptCfg[lIndex]->aApexPoints[lCnt].lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        ulViewID += ulViewID_Step;
    }

    return ulSectionBufLen;
}

void AV_CfgImportHex(
    UINT32 a_ulDataID,
    UINT32 a_ulDataLength, UINT8 * a_pucBuffer,
    alALLEYVIEW_Cfg *a_ptCfg_S,
    alALLEYVIEW_Cfg *a_ptCfg_F
    )
{
    UINT32 ulSubDataID = 0;
    alALLEYVIEW_Cfg *aptCfg[2] = { 0 };
    INT32 lCamID = 0;

    lCamID = (a_ulDataID >> 12) & 0x000F;
    if (lCamID >= 2)
    {
        // error
    }
    
    ulSubDataID = a_ulDataID & 0x0FFF;

    aptCfg[0] = a_ptCfg_S;
    aptCfg[1] = a_ptCfg_F;

    switch (ulSubDataID)
    {
    case 0x0000:    // ucFunctionEnabled
    {
        aptCfg[lCamID]->ucFunctionEnabled = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0001:    // tStartPoint.lX
    {
        aptCfg[lCamID]->tStartPoint.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0002:    // tStartPoint.lY
    {
        aptCfg[lCamID]->tStartPoint.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0003:    // tAreaSize.lX
    {
        aptCfg[lCamID]->tAreaSize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0004:    // tAreaSize.lY
    {
        aptCfg[lCamID]->tAreaSize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0005:    // fViewingAngle
    {
        aptCfg[lCamID]->fViewingAngle = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0006:    // ulFOV
    {
        aptCfg[lCamID]->ulFOV = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0007:    // lVCOffsetX
    {
        aptCfg[lCamID]->lVCOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0008:    // lVCOffsetY
    {
        aptCfg[lCamID]->lVCOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0009:    // ulSoftPixels
    {
        aptCfg[lCamID]->ulSoftPixels = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000A:    // aApexPoints[0].lX
    {
        aptCfg[lCamID]->aApexPoints[0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000B:    // aApexPoints[0].lY
    {
        aptCfg[lCamID]->aApexPoints[0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000C:    // aApexPoints[1].lX
    {
        aptCfg[lCamID]->aApexPoints[1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000D:    // aApexPoints[1].lY
    {
        aptCfg[lCamID]->aApexPoints[1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000E:    // aApexPoints[2].lX
    {
        aptCfg[lCamID]->aApexPoints[2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000F:    // aApexPoints[2].lY
    {
        aptCfg[lCamID]->aApexPoints[2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0010:    // aApexPoints[3].lX
    {
        aptCfg[lCamID]->aApexPoints[3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0011:    // aApexPoints[3].lY
    {
        aptCfg[lCamID]->aApexPoints[3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0012:    // aApexPoints[4].lX
    {
        aptCfg[lCamID]->aApexPoints[4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0013:    // aApexPoints[4].lY
    {
        aptCfg[lCamID]->aApexPoints[4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0014:    // aApexPoints[5].lX
    {
        aptCfg[lCamID]->aApexPoints[5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0015:    // aApexPoints[5].lY
    {
        aptCfg[lCamID]->aApexPoints[5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0016:    // aApexPoints[6].lX
    {
        aptCfg[lCamID]->aApexPoints[6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0017:    // aApexPoints[6].lY
    {
        aptCfg[lCamID]->aApexPoints[6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0018:    // aApexPoints[7].lX
    {
        aptCfg[lCamID]->aApexPoints[7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0019:    // aApexPoints[7].lY
    {
        aptCfg[lCamID]->aApexPoints[7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    default:    // default
    {
        // 
        DEBUG_Printf("Invalid Data ID: 0x%X\n - AlleyView_CfgImport\n", a_ulDataID);
    }
    break;

    }

}
