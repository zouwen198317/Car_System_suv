
#include "mtype.h"
#include "basedef.h"
#include "alErrorCode.h"
#include "alFM_v2_1.h"
#include "alMANUALK/alMANUALK.h"
#include "EagleK3.h"

#ifdef WIN32
// #include <wchar.h>
#include <direct.h> //  for _mkdir
#include <locale.h> // add by ancre for char to wchar_t
#include <time.h>
#endif
#include <stdio.h>
#include <math.h>
#include <assert.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL EAGLEK3_InitialBuffer()
{
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
alERROR_ERROR_CODE EAGLEK3_ReadErrorCode()
{
    return g_alERROR_ucErrorCode;
}

#ifdef WIN32
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EAGLEK3_ReadErrorDescription(wchar_t * a_pwcDescription, UINT8 a_ucBufferLen)
{
    alERROR_ReadDescriptionByErrorCodeW(EAGLEK3_ReadErrorCode(), a_pwcDescription, a_ucBufferLen);
}

///////////////////////


void EAGLEK3_SetPath(wchar_t * a_pwcWorkingPath, wchar_t * a_pwcSrcPath, wchar_t * a_pwcOutPath)
{
	wcscpy_s(g_EAGLEK3_awcWorkingPath, MAX_PATH, a_pwcWorkingPath);
	setlocale(LC_ALL, "cht");

	wcstombs(g_acalBVCAM_FACAUTOK_WorkingFolder, a_pwcWorkingPath, MAX_PATH);
	wcstombs(g_acalBVCAM_FACAUTOK_SourceFolder, a_pwcSrcPath, MAX_PATH);
	wcstombs(g_acalBVCAM_FACAUTOK_OutputFolder, a_pwcOutPath, MAX_PATH);
    sprintf(g_acalBVCAM_FACAUTOK_OutputFolder, "%sAutoK/", g_acalBVCAM_FACAUTOK_OutputFolder);
    _mkdir(g_acalBVCAM_FACAUTOK_OutputFolder);

	setlocale(LC_ALL, "C");
}

//////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EAGLEK3_SetWorkingPath(wchar_t * a_pwcWorkingPath)
{
    wcscpy_s(g_EAGLEK3_awcWorkingPath, MAX_PATH, a_pwcWorkingPath);
	alBVCAM_FACAUTOK_SetWorkingPath(a_pwcWorkingPath);
}
const wchar_t * EAGLEK3_GetWorkingPath()
{
    return g_EAGLEK3_awcWorkingPath;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EAGLEK3_InitialByConfigData(
    alFM_v2_1_Model * a_ptFM_v2_Model, alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_FieldData *a_ptFeildData, EAGLEK3_Cfg *a_ptCfg, EAGLEK3_Param *a_ptParams, 
    EAGLEK3_Data *a_ptCalibrateData, UINT8 *a_pucWorkingBuffer
    )
{
	alPointINT32 tLeftTireCenter;
    INT32 alCameraPosX[COMMONK_NUM_BV_CHANNEL] = { 0 }, alCameraPosY[COMMONK_NUM_BV_CHANNEL] = { 0 }, lCnt = 0, alOriImgYLimit[COMMONK_NUM_BV_CHANNEL] = { 0 };

    // 設定 BV 影像大小
    a_ptParams->tBVImgSize.lX = a_ptAVM2DCfg->tDestImageBufferSize.lX;
    a_ptParams->tBVImgSize.lY = a_ptAVM2DCfg->tDestImageBufferSize.lY;

    // 複製 default 校正數據到 data
    memcpy(a_ptCalibrateData->atCameraExtrinsicParams, a_ptCfg->atCameraExtrinsicParams, sizeof(alCAMERAINFO_ExtrinsicParams)*EAGLEK3_NUM_BV_CHANNEL);
    memcpy(a_ptCalibrateData->atCalibrationParams, a_ptCfg->atCalibrationParams, sizeof(alCOMMONK_CalibrationParams)*EAGLEK3_NUM_BV_CHANNEL);

    // 檢查FM size等等的資訊 ??
   

    // 初始化 Manual K 校正參數
    MANUALK_InitialByConfigData(
        a_ptFM_v2_Model,
        a_ptCfg->atCameraExtrinsicParams,
        a_ptCfg->atCalibrationParams,
        a_ptFeildData->atBVFPOffsetFineTuned, 
        &a_ptFeildData->tManualKFieldData, 
        a_ptCfg->atMANUALK_Cfg, 
        a_ptAVM2DCfg->tDestImageBufferSize,
        a_ptAVM2DParams->fMMPP,
        a_ptCommonCfg,
        &a_ptParams->tMANUALK_Params
    );

#if 1 	// 初始化 alBVCAM_FACAUTOK 校正參數
	{
        tLeftTireCenter.lX = -((INT32)(a_ptCommonCfg->ulCarWidth >> 1));
        tLeftTireCenter.lY = a_ptCommonCfg->ulFrontWheelAxle2Head - (a_ptCommonCfg->ulCarLength >> 1);
        for (lCnt = 0; lCnt < COMMONK_NUM_BV_CHANNEL ; lCnt++)
		{
            alCameraPosX[lCnt] = a_ptCalibrateData->atCameraExtrinsicParams[lCnt].lCameraPosX;
            alCameraPosY[lCnt] = a_ptCalibrateData->atCameraExtrinsicParams[lCnt].lCameraPosY;
		}
		
		alBVCAM_FACAUTOK_InitialByCFG(
            &a_ptParams->tBVImgSize,
            a_pucWorkingBuffer,
            &a_ptCalibrateData->tBV_BV_FAC_AutoK_Data,
            a_ptFM_v2_Model, a_ptAVM2DParams,
            tLeftTireCenter, alCameraPosX, alCameraPosY, alOriImgYLimit,
            &a_ptFeildData->tAutoKFieldData, a_ptAVM2DParams->fMMPP,
            a_ptCommonCfg,
            &a_ptCfg->tAutoK_Cfg,
            &a_ptParams->tAutoK_Params
		);
	}
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EAGLEK3_SetCfgInfoByDataID(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 *a_puCDataBuffer, EAGLEK3_Cfg *a_ptCfg)
{
    switch ((a_ulDataID >> 16) & 0xFFFF)
    {
    case 0x0001:    // Comon Cfg
    {
        /*COMMONK_CommonCfgImportByHexData(
            a_ulDataID, a_ulDataLength,
            a_puCDataBuffer, &a_ptCfg->tCommonCfg
        );*/
    }
    break;
 
    default:
        DEBUG_Printf("Invalid Section ID: 0x%X\n - EAGLEK3_CfgDataImport\n", a_ulDataID);
        break;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// add by chinson: for File Import
// modify API by chinson - 20130827: 微調 ulFileLength 的定義，改為傳入 pucFileBuffer 的 byte size，pucFileBuffer 也改為 UINT8 指標
void EAGLEK3_SetCfgInfoByHexFile(UINT32 a_ulFileLength, UINT8 * a_pucFileBuffer, EAGLEK3_Cfg *a_ptCfg)
{
    UINT32 ulDataID;            // Single Data ID
    UINT32 ulDataLength;        // Single Data Length
    UINT8 * pucDataBuffer;     // Single Data Buffer
    UINT32 ulUINT32BufferLength = (a_ulFileLength>>2);    // 以 4 個 byte 為單位的長度(即 pulFileBuffer 的長度)
    UINT32 * pucUINT8Buffer = (UINT32*)a_pucFileBuffer;  // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 * pulPtr = pucUINT8Buffer;

    // BYTE_OF_DATA_ITEM

    while (pulPtr - pucUINT8Buffer < (INT32)(ulUINT32BufferLength))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8*)(pulPtr + 2);

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_SetCfgInfoByDataID(ulDataID, ulDataLength, pucDataBuffer, a_ptCfg);

        // 3. 累進指標
        pulPtr += (2 + ulDataLength);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EAGLEK3_FreeBuffer(alFM_v2_1_Model *a_ptCameraFisheyeModel)
{
    UINT8 ucCameraIndex;
    INT32 i = 0, lCnt = 0;

    // free fish-eye model v2
    for (ucCameraIndex = 0; ucCameraIndex < EAGLEK3_NUM_BV_CHANNEL; ucCameraIndex++)
    {
        alFM_v2_1_FreeBuffer(a_ptCameraFisheyeModel + ucCameraIndex);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EAGLEK3_GetParams(EAGLEK3_Param * a_ptParams)
{
	UINT8 ucViewIndex = 0;
}


UINT32  EAGLEK3_QueryFM_BV_WorkingBufferSizeTotal(UINT8 a_ucCamNum, alFM_v2_1_ModelCfg *a_ptFMCfg)
{
    UINT32 ulSizeTmp = 0, ulSizeTotal = 0, i = 0, ulPixelTableSize = 0, ulAngleTableSize = 0;

    for (i = 0; i < a_ucCamNum; i++)
    {
        ulSizeTmp = 0;
        ulPixelTableSize = 0;
        ulAngleTableSize = 0;


        // real height 的 pixel table
        ulPixelTableSize = (UINT16)ceil(sqrt((a_ptFMCfg[i].ulImageHeight >> 1) * (a_ptFMCfg[i].ulImageHeight >> 1) +
            (a_ptFMCfg[i].uwSrcSensorWidth >> 1) * (a_ptFMCfg[i].uwSrcSensorWidth >> 1)));
        ulPixelTableSize *= sizeof(UINT16);

        // degree 的 table
        ulAngleTableSize = ((UINT16)ceil(a_ptFMCfg[i].aeAngleDegree[a_ptFMCfg[i].uwLengthOfDistortionCurve - 1])) * a_ptFMCfg[i].uwAngleTableScale;
        ulAngleTableSize *= sizeof(UINT16);

        ulSizeTmp = ulPixelTableSize + ulAngleTableSize;

        ulSizeTotal += ulSizeTmp;
    }
    return ulSizeTotal;
}

void  EAGLEK3_QueryFM_BV_WorkingBufferSizeForEachFM(alFM_v2_1_ModelCfg *a_ptFMCfg, UINT32 a_aulSize[COMMONK_NUM_BV_CHANNEL])
{
    UINT8 ucCnt = 0;
    for (ucCnt = 0; ucCnt < COMMONK_NUM_BV_CHANNEL; ucCnt++)
    {
        a_aulSize[ucCnt] = alFM_v2_1_QueryFM_WorkingBufferSizeSingle(&a_ptFMCfg[ucCnt]);
    }
}


void EAGLEK3_InitialBV_FM_ByCfg(alFM_v2_1_ModelCfg a_atFM_v2_Cfg[COMMONK_NUM_BV_CHANNEL], alFM_v2_1_Model a_atFM_v2_Model[COMMONK_NUM_BV_CHANNEL], UINT8 *a_apucFMBuffer[COMMONK_NUM_BV_CHANNEL])
{
    alFM_v2_1_InitialByCfgDataExternalBuffer(&a_atFM_v2_Cfg[EAGLEK3_BV_LEFT], &a_atFM_v2_Model[EAGLEK3_BV_LEFT], a_apucFMBuffer[EAGLEK3_BV_LEFT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&a_atFM_v2_Cfg[EAGLEK3_BV_RIGHT], &a_atFM_v2_Model[EAGLEK3_BV_RIGHT], a_apucFMBuffer[EAGLEK3_BV_RIGHT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&a_atFM_v2_Cfg[EAGLEK3_BV_FRONT], &a_atFM_v2_Model[EAGLEK3_BV_FRONT], a_apucFMBuffer[EAGLEK3_BV_FRONT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&a_atFM_v2_Cfg[EAGLEK3_BV_BACK], &a_atFM_v2_Model[EAGLEK3_BV_BACK], a_apucFMBuffer[EAGLEK3_BV_BACK]);
}

UINT32  EAGLEK3_QueryEagleK3_WorkingBufferSizeSingle(EAGLEK3_Cfg *a_ptEagleK3Cfg)
{
    // 目前只有AutoK 需要記憶體空間
    alPointINT32 tImgSize = { 0 };
    INT32 lSBV_WorkingBufferSize = 0;
    INT32 lElse_WorkingBufferSize = 0;
    INT32 lTotal_WorkingBufferSize = 0, lCnt = 0;

    for (lCnt = 0; lCnt < COMMONK_NUM_BV_CHANNEL; lCnt++)
    {
        tImgSize.lX = ((INT32)(a_ptEagleK3Cfg->atMANUALK_Cfg[lCnt].ulImageWidth) > tImgSize.lX) ? a_ptEagleK3Cfg->atMANUALK_Cfg[lCnt].ulImageWidth : tImgSize.lX;
        tImgSize.lY = ((INT32)(a_ptEagleK3Cfg->atMANUALK_Cfg[lCnt].ulImageWidth) > tImgSize.lY) ? a_ptEagleK3Cfg->atMANUALK_Cfg[lCnt].ulImageWidth : tImgSize.lY;
    }
    lSBV_WorkingBufferSize = tImgSize.lX*tImgSize.lY;
    lElse_WorkingBufferSize = lSBV_WorkingBufferSize << 3;
    lTotal_WorkingBufferSize = lElse_WorkingBufferSize + lElse_WorkingBufferSize;
#if 0 // by defined
    return alBVCAM_FACAUTOK_Total_WorkingBufferSize;
#else
    return lTotal_WorkingBufferSize;
#endif
}

UINT32  EAGLEK3_QueryFM_BV_WorkingBufferSizeSingle(alFM_v2_1_ModelCfg *a_ptFMCfg)
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



void EAGLEK3_SingleViewForManualCalibration(
    UINT8 a_ucBVCameraIndx,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData,
    UINT8 * a_pucSrcImage,
    UINT8 * a_pucDestImage
    )
{
    INT32 lSrcWidth = 0, lSrcHeight = 0;
    INT32 lDestWidth = 0, lDestHeight = 0;

    lSrcWidth = a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].ulImageWidth;
    lSrcHeight = a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].ulImageHeight;
    lDestWidth = a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lImageWidth;
    lDestHeight = a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lImageHeight;


    COMMONK_SBVGenerate_YUYV_FULL(
        a_pucSrcImage, lSrcWidth, lSrcHeight,
        a_pucDestImage, lDestWidth, lDestHeight,
        a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[0],
        a_ptParams->tMANUALK_Params.alOriImgYLimit[a_ucBVCameraIndx],
        a_ptParams->tMANUALK_Params.alCamAngle[a_ucBVCameraIndx],
        a_ptData->atCameraExtrinsicParams[a_ucBVCameraIndx].lCameraPosX,
        a_ptData->atCameraExtrinsicParams[a_ucBVCameraIndx].lCameraPosY,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lDisplayOffset_X,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lDisplayOffset_Y,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.fScaleFactor,
        a_ptParams->tMANUALK_Params.fMMPP,
        a_ptParams->tMANUALK_Params.a_aptFM_v2_Model[a_ucBVCameraIndx]
        );
}

void EAGLEK3_SrcDistorted2SBV_ForManualK(
    UINT8 a_ucBVCameraIndx,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData,
    FLOAT64 a_peSrcX, FLOAT64 a_peSrcY,
    FLOAT64 *a_peSBVX, FLOAT64 *a_peSBVY
    )
{
    FLOAT64 eUDX = 0, eUDY = 0, eBVX = 0, eBVY = 0, *peM33 = NULL;
    alFM_v2_1_Model *ptCameraFisheyeModel = NULL;

    ptCameraFisheyeModel = a_ptParams->tMANUALK_Params.a_aptFM_v2_Model[a_ucBVCameraIndx];
    peM33 = a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[1];

    alFM_v2_1_Distorted2Undistorted_PlanarPixel(ptCameraFisheyeModel, a_peSrcX, a_peSrcY, &eUDX, &eUDY);

    COMMONK_PerformCoordinatesTransform(peM33, eUDX, eUDY, &eBVX, &eBVY);

    COMMONK_Birdview2SBV(
        a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lImageWidth,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lImageHeight, 1,
        a_ptParams->tMANUALK_Params.alCamAngle[a_ucBVCameraIndx],
        a_ptData->atCameraExtrinsicParams[a_ucBVCameraIndx].lCameraPosX,
        a_ptData->atCameraExtrinsicParams[a_ucBVCameraIndx].lCameraPosY,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lDisplayOffset_X,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lDisplayOffset_Y,
        (FLOAT64)a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.fScaleFactor,
        (FLOAT64)a_ptParams->tMANUALK_Params.fMMPP,
        &eBVX, &eBVY, a_peSBVX, a_peSBVY
    );
}

void EAGLEK3_ReGenerateM33_ForManualK(
    UINT8 a_ucBVCameraIndx,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData,
    FLOAT64 *a_peSelectSBVX, FLOAT64 *a_peSelectSBVY
    )
{
    FLOAT64 aeUDX[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeUDY[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeBVX[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeBVY[alMANUALK_CAMERA_FP_NUM] = { 0 }, *peM33 = NULL;
    INT32 i = 0, lFlag = 0, lIndex = 0;
    alFM_v2_1_Model *ptCameraFisheyeModel = NULL;

    peM33 = a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[0];

    COMMONK_SBV2Birdview(
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lImageWidth,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lImageHeight,
        a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
        alMANUALK_CAMERA_FP_NUM,
        a_ptParams->tMANUALK_Params.alCamAngle[a_ucBVCameraIndx],
        a_ptData->atCameraExtrinsicParams[a_ucBVCameraIndx].lCameraPosX,
        a_ptData->atCameraExtrinsicParams[a_ucBVCameraIndx].lCameraPosY,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lDisplayOffset_X,
        a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.lDisplayOffset_Y,
        (FLOAT64)a_ptCfg->atMANUALK_Cfg[a_ucBVCameraIndx].tSBV_Setting.fScaleFactor,
        (FLOAT64)a_ptParams->tMANUALK_Params.fMMPP,
        a_peSelectSBVX, a_peSelectSBVY, aeBVX, aeBVY
        );

    for (lIndex = 0; lIndex < alMANUALK_CAMERA_FP_NUM; lIndex++)
    {
        COMMONK_PerformCoordinatesTransform(peM33, aeBVX[lIndex], aeBVY[lIndex], &aeUDX[lIndex], &aeUDY[lIndex]);
    }

    

    // generate M33
    lFlag = COMMONK_GenerateM3x3(
        aeUDX, aeUDY,
        a_ptParams->tMANUALK_Params.aeBVIdealFP_X[a_ucBVCameraIndx],
        a_ptParams->tMANUALK_Params.aeBVIdealFP_Y[a_ucBVCameraIndx],
        alMANUALK_CAMERA_FP_NUM,
        a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[0]
     );

    if (!lFlag)
    {
        assert(0);
    }

    memcpy(a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[1], a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[0], sizeof(FLOAT64) * 9);
    alMATRIX_InverseNbyN(a_ptData->atCalibrationParams[a_ucBVCameraIndx].aeHomographyMatrix[1], 3); 
}








UINT32 EAGLEK3_FatoryAutoK(
    UINT8 *a_pucSrcBufferFront,
    UINT8 *a_pucSrcBufferBack,
    UINT8 *a_pucSrcBufferLeft,
    UINT8 *a_pucSrcBufferRight,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData
    )
{
    UINT32 ulPASS_FLAG = 0;
    UINT8 ucPASS_FineTune = 0, ucPASS_Calibrate = 0, ucBitIndex = 0;

    // Error code set to NULL
    alERROR_ClearErrorCode();

    if (a_ptCfg->ucFactoryAutoKSwitch == 0)
    { // alBVCAM FACAUTOK AutoK 被設定為不能開啟但上層程式依然呼叫
        printf("\n");
        printf("/***********************************************/\n");
        printf("\talBVCAM_FACAUTOK_AutoK is OFF\n");
        printf("\tPlease open the switch in Configure file 1\n");
        alERROR_SetErrorCode(EAGLEK3_ERROR_CAMK_K_BVCAM_FACAUTOK_DISABLE);
        printf("/***********************************************/\n");
        printf("\n");
        return 1;
    }

    ulPASS_FLAG = alBVCAM_FACAUTOK_AutoK(
        a_pucSrcBufferFront, a_pucSrcBufferBack, a_pucSrcBufferLeft, a_pucSrcBufferRight,
        a_ptData->atCalibrationParams[alCAMERAINFO_BV_LEFT].aeHomographyMatrix,
        a_ptData->atCalibrationParams[alCAMERAINFO_BV_RIGHT].aeHomographyMatrix,
        a_ptData->atCalibrationParams[alCAMERAINFO_BV_FRONT].aeHomographyMatrix,
        a_ptData->atCalibrationParams[alCAMERAINFO_BV_BACK].aeHomographyMatrix,
        &a_ptCfg->tAutoK_Cfg,
        &a_ptParams->tAutoK_Params,
        &a_ptData->tBV_BV_FAC_AutoK_Data
    );


    if (!(ulPASS_FLAG & 0x01))
    { // pass >> modify M33
        // LEFT
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_LEFT].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_LEFT][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_LEFT].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_LEFT][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));

        // RIGHT
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_RIGHT].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_RIGHT][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_RIGHT].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_RIGHT][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));

        // FRONT
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_FRONT].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_FRONT][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_FRONT].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_FRONT][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));

        // BACK
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_BACK].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_BACK][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        memcpy(a_ptData->atCalibrationParams[alCAMERAINFO_BV_BACK].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_BACK][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
    }
    else
    {	// fail
        // 有單獨成功的view 就修正它
        ucBitIndex = 5;

        ucPASS_Calibrate = (ulPASS_FLAG >> ucBitIndex) & 1;
        ucPASS_FineTune = (ulPASS_FLAG >> (ucBitIndex + 4)) & 1;

        if (!ucPASS_Calibrate && !ucPASS_FineTune)
        { // LEFT
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_LEFT].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_LEFT][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_LEFT].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_LEFT][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        }
        ucBitIndex++;

        ucPASS_Calibrate = (ulPASS_FLAG >> ucBitIndex) & 1;
        ucPASS_FineTune = (ulPASS_FLAG >> (ucBitIndex + 4)) & 1;

        if (!ucPASS_Calibrate && !ucPASS_FineTune)
        { // RIGHT
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_RIGHT].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_RIGHT][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_RIGHT].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_RIGHT][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        }
        ucBitIndex++;

        ucPASS_Calibrate = (ulPASS_FLAG >> ucBitIndex) & 1;
        ucPASS_FineTune = (ulPASS_FLAG >> (ucBitIndex + 4)) & 1;

        if (!ucPASS_Calibrate && !ucPASS_FineTune)
        { // FRONT
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_FRONT].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_FRONT][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_FRONT].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_FRONT][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        }
        ucBitIndex++;

        ucPASS_Calibrate = (ulPASS_FLAG >> ucBitIndex) & 1;
        ucPASS_FineTune = (ulPASS_FLAG >> (ucBitIndex + 4)) & 1;

        if (!ucPASS_Calibrate && !ucPASS_FineTune)
        { // BACK
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_BACK].aeHomographyMatrix[0], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_BACK][0], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
            memcpy(a_ptCfg->atCalibrationParams[alCAMERAINFO_BV_BACK].aeHomographyMatrix[1], a_ptData->tBV_BV_FAC_AutoK_Data.aeFineTuneKM33[EAGLEK3_BV_BACK][1], EAGLEK3_M33_ELEMENT_CNT*sizeof(FLOAT64));
        }

        alERROR_SetErrorCode(EAGLEK3_ERROR_CAMK_K_BVCAM_FACAUTOK_FAIL);
    }
    return ulPASS_FLAG;
}

UINT32 EAGLEK3_Gen_RT_Matrix(
    EAGLEK3_Cfg *a_ptCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData
    )
{
    INT32 lCamID = 0, lBVCenter_X = 0, lBVCenter_Y = 0;
    FLOAT32 afLM_Offset[6] = { 0 };

    lBVCenter_X = a_ptAVM2DCfg->tDestImageBufferSize.lX >> 1;
    lBVCenter_Y = a_ptAVM2DCfg->tDestImageBufferSize.lY >> 1;

    for (lCamID = 0; lCamID < COMMONK_NUM_BV_CHANNEL; lCamID++)
    {   // 目前 select FP 先等於 Ideal FP 
        afLM_Offset[0] = a_ptCfg->afPitchOffset[lCamID];
        afLM_Offset[1] = a_ptCfg->afYawOffset[lCamID];
        afLM_Offset[2] = a_ptCfg->afRollOffset[lCamID];
        afLM_Offset[3] = (FLOAT32)(a_ptCfg->alCameraPosXOffset)[lCamID];
        afLM_Offset[4] = (FLOAT32)(a_ptCfg->alCameraPosYOffset)[lCamID];
        afLM_Offset[5] = (FLOAT32)(a_ptCfg->alCameraPosZOffset)[lCamID];
        COMMONK_RT_Calculation(
            lCamID, lBVCenter_X, lBVCenter_Y,
            a_ptParams->tMANUALK_Params.aeBVIdealFP_X[lCamID],
            a_ptParams->tMANUALK_Params.aeBVIdealFP_Y[lCamID],
            a_ptParams->tMANUALK_Params.aeBVIdealFP_X[lCamID],
            a_ptParams->tMANUALK_Params.aeBVIdealFP_Y[lCamID],
            COMMONK_MANUALK_CAMERA_FP_NUM,
            a_ptData->atCalibrationParams[lCamID].aeHomographyMatrix[0], // 0 : BV to Undistorted Src
            a_ptParams->tMANUALK_Params.a_aptFM_v2_Model[lCamID],
            a_ptAVM2DParams->fMMPP,
            afLM_Offset,
            a_ptCfg->alLMBoundarySwitch[lCamID],
            &a_ptData->atCameraExtrinsicParams[lCamID],
            &a_ptData->atCalibrationParams[lCamID]
            );
    }
    return TRUE;
}


void EAGLEK3_FineTuneHomographyMatrix(
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData
    )
{
    INT32 lView = 0, lPoint = 0, lFlag = 0;
    FLOAT64 *peM33_W2I = NULL;
    FLOAT64 *peM33_I2W = NULL;
    FLOAT64 aeFPX[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeFPY[alMANUALK_CAMERA_FP_NUM] = { 0 };

    for (lView = 0; lView < EAGLEK3_NUM_BV_CHANNEL; lView++)
    {
        peM33_W2I = a_ptData->atCalibrationParams[lView].aeHomographyMatrix[0];
        peM33_I2W = a_ptData->atCalibrationParams[lView].aeHomographyMatrix[1];

        // from ideal points to undistorted points
        for (lPoint = 0; lPoint < alMANUALK_CAMERA_FP_NUM; lPoint++)
        {
            COMMONK_PerformCoordinatesTransform(
                peM33_W2I, 
                a_ptParams->tMANUALK_Params.aeBVIdealFP_X[lView][lPoint], 
                a_ptParams->tMANUALK_Params.aeBVIdealFP_Y[lView][lPoint],
                &aeFPX[lPoint], &aeFPY[lPoint]
            );
        }

        // generate M33
        lFlag = COMMONK_GenerateM3x3(
            aeFPX, aeFPY,
            a_ptParams->tMANUALK_Params.aeBVFineTunedIdealFP_X[lView],
            a_ptParams->tMANUALK_Params.aeBVFineTunedIdealFP_Y[lView],
            alMANUALK_CAMERA_FP_NUM,
            peM33_W2I
            );

        if (!lFlag)
        {
            assert(0);
        }

        memcpy(peM33_I2W, peM33_W2I, sizeof(FLOAT64) * EAGLEK3_M33_ELEMENT_CNT);
        alMATRIX_InverseNbyN(peM33_I2W, 3);
    }
}



void  EAGLEK3_SaveConfigFiles()
{
#if 0
    UINT32 ulSize;
    UINT8 * pucData;
    wchar_t awcFilePath[MAX_PATH];

    // Config File #1
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_ConfigFile1.hex");
    pucData = EAGLEK3_ExportConfigFile1(&ulSize);
    EAGLEK3_Memory2FileW(awcFilePath, pucData, ulSize);

    // Config File #2
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_ConfigFile2.hex");
    pucData = EAGLEK3_ExportConfigFile2(&ulSize);
    EAGLEK3_Memory2FileW(awcFilePath, pucData, ulSize);

    // Config File #3
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_ConfigFile3.hex");
    pucData = EAGLEK3_ExportConfigFile3(&ulSize);
    EAGLEK3_Memory2FileW(awcFilePath, pucData, ulSize);

    // Fisheye Model v2 File
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_FisheyeModel_v2_File.hex");
    pucData = EAGLEK3_ExportFisheyeModel_v2_File(&ulSize);
    EAGLEK3_Memory2FileW(awcFilePath, pucData, ulSize);

    // Config File for AutoK
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_FactoryAutoK_ConfigFile.hex");
    pucData = EAGLEK3_ExportFactoryAutoKConfigFile(&ulSize);
    EAGLEK3_Memory2FileW(awcFilePath, pucData, ulSize);

    // Params File for AutoK
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_FactoryAutoK_ParameterFile.hex");
    pucData = EAGLEK3_ExportFactoryAutoK_ParameterFile(&ulSize);
    EAGLEK3_Memory2FileW(awcFilePath, pucData, ulSize);

#ifdef _DEBUG
    // Text file output:
    // Calibrated M33 file in txt
    wcscpy_s(awcFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcFilePath, MAX_PATH, L"EagleK_M33.txt");
    CAMK_ExportM33toTXT(awcFilePath);
#endif
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EAGLEK3_TestConfigFiles()
{
    /*TEST_ConfigFileFactoryAutoK();
    TEST_ParamsFileFactoryAutoK();
    TEST_ConfigFile1();
    TEST_ConfigFile2();
    TEST_ConfigFile3();
    TEST_ConfigFile_FMv2();*/
}

