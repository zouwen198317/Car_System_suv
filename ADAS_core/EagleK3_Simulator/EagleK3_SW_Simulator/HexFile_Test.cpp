
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>
#include <locale.h> // add by ancre for char to wchar_t


#include "alLUT_v2.h"
#include "basedef.h"
#include "EagleK3_SimulateMain.h"
#include "AVM3DK.h"

#include "alHexCoder.h"

#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#define TEST_HEX_BUFFER_SIZE 10000

char g_acCfgFileOutputFolder[MAX_PATH] = { 0 };
FILE *g_ptCfgFilePtr = NULL;

void Test_HexFile_Tmp_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucEagleK3WorkingBuffer = NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0, ulAVM2D_LUT_Size = 0;
    UINT32 ulHexFileSize = 0;
    UINT8 aucHexBufferTmp[TEST_HEX_BUFFER_SIZE] = { 0 };
    UINT8 aucHexBufferTmp_1[TEST_HEX_BUFFER_SIZE] = { 0 };

    alFM_v2_1_ModelCfg atFM_BV_Cfg[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, atFM_BV_CfgHex[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    EAGLEK3_FieldData tEAGLEK3_FeildData = { 0 }, tEAGLEK3_FeildDataHex = { 0 };
    EAGLEK3_Cfg tEAGLEK3_Cfg = { 0 }, tEAGLEK3_CfgHex = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 }, tAVM2D_CfgHex = { 0 };
    alCOMMONK_CommonCfg tCommonCfg = { 0 }, tCommonCfgHex = {0};
    alALLEYVIEW_Cfg tSAV_Cfg = { 0 }, tFAV_Cfg = {0};
    alALLEYVIEW_Cfg tSAV_CfgHex = { 0 }, tFAV_CfgHex = { 0 };
    alTRAILLINE_Cfg tTL_Cfg = { 0 }, tTL_CfgHex = { 0 };
    
    UINT32 ulDataID;                                // Single Data ID
    UINT32 ulDataLength;                            // Single Data Length
    UINT8 *pucDataBuffer;                           // Single Data Buffer
    UINT32 ulBufferLength = (ulHexFileSize);
    UINT32 *pucBuffer = (UINT32*)aucHexBufferTmp;   // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 *pulPtr = pucBuffer;
    int lCompare = 0, lCnt = 0;

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

#if 1 // test AV CFG
    // Load conifg data from INI file
    alALLEYVIEW_CfgImportByINI(&tSAV_Cfg, &tFAV_Cfg, awcConfigFilePath);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = AV_CfgExportHex(0x0003, &tSAV_Cfg, &tFAV_Cfg, aucHexBufferTmp);


    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        AV_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &tSAV_CfgHex, &tFAV_CfgHex);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    lCompare = memcmp(&tSAV_CfgHex, &tSAV_Cfg, sizeof(alALLEYVIEW_Cfg));
    lCompare = memcmp(&tFAV_CfgHex, &tFAV_Cfg, sizeof(alALLEYVIEW_Cfg));
#endif

#if 1 // test FM CFG
    memset(atFM_BV_Cfg, 0, sizeof(alFM_v2_1_ModelCfg)*EAGLEK3_NUM_BV_CHANNEL);
    memset(atFM_BV_CfgHex, 0, sizeof(alFM_v2_1_ModelCfg)*EAGLEK3_NUM_BV_CHANNEL);

    // Load conifg data from INI file
    EAGLEK3_LoadFM_BV_CfgByINI(awcConfigFilePath, EAGLEK3_NUM_BV_CHANNEL, atFM_BV_Cfg);

    for (lCnt = 0; lCnt < EAGLEK3_NUM_BV_CHANNEL; lCnt++)
    {
        // export
        memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
        ulHexFileSize = alFM_v2_1_SingleFisheyeModelCfgExport(
            0x0100,
            &atFM_BV_Cfg[lCnt],
            aucHexBufferTmp
        );


        ulBufferLength = (ulHexFileSize);
        pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
        pulPtr = pucBuffer;
        lCompare = 0;

        // import
        while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
        {
            // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
            ulDataID = *pulPtr;
            ulDataLength = *(pulPtr + 1);
            pucDataBuffer = (UINT8 *)(pulPtr + 2);

            ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

            // 2. 將 Single Data 資訊匯入
            alFM_v2_1_CfgImportHex(
                ulDataID,
                ulDataLength,
                pucDataBuffer,
                &atFM_BV_CfgHex[lCnt]
                );

            // 3. 累進指標
            pulPtr += (2 + (ulDataLength >> 2));
        }

        lCompare = memcmp(&atFM_BV_CfgHex[lCnt], &atFM_BV_Cfg[lCnt], sizeof(alFM_v2_1_ModelCfg));
    }
#endif

#if 1 // test Trail Line CFG
    memset(&tTL_Cfg, 0, sizeof(alTRAILLINE_Cfg));
    memset(&tTL_CfgHex, 0, sizeof(alTRAILLINE_Cfg));

    // Load conifg data from INI file
    alTRAILLINE_CfgImportByINI(awcConfigFilePath, &tTL_Cfg);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = alTRAILLINE_CfgExportHex(
        0x0004,
        &tTL_Cfg,
        aucHexBufferTmp
        );


    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alTRAILLINE_CfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tTL_CfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    lCompare = memcmp(&tTL_CfgHex.atSTLCfg[0], &tTL_Cfg.atSTLCfg[0], sizeof(alTRAILLINE_StaticTrailLineInfo));
    lCompare = memcmp(&tTL_CfgHex.atSTLCfg[1], &tTL_Cfg.atSTLCfg[1], sizeof(alTRAILLINE_StaticTrailLineInfo));
    lCompare = memcmp(&tTL_CfgHex.atDTLCfg[0], &tTL_Cfg.atDTLCfg[0], sizeof(alTRAILLINE_DynamicTrailLineInfo));
    lCompare = memcmp(&tTL_CfgHex.atDTLCfg[1], &tTL_Cfg.atDTLCfg[1], sizeof(alTRAILLINE_DynamicTrailLineInfo));

    lCompare = memcmp(&tTL_CfgHex.atWLCfg[0], &tTL_Cfg.atWLCfg[0], sizeof(alTRAILLINE_WarningLineInfo));
    lCompare = memcmp(&tTL_CfgHex.atWLCfg[1], &tTL_Cfg.atWLCfg[1], sizeof(alTRAILLINE_WarningLineInfo));
    lCompare = memcmp(&tTL_CfgHex.atWLCfg[2], &tTL_Cfg.atWLCfg[2], sizeof(alTRAILLINE_WarningLineInfo));
    lCompare = memcmp(&tTL_CfgHex.atWLCfg[3], &tTL_Cfg.atWLCfg[3], sizeof(alTRAILLINE_WarningLineInfo));
    lCompare = memcmp(&tTL_CfgHex, &tTL_Cfg, sizeof(alTRAILLINE_Cfg));
#endif

#if 1 // test Common CFG
    // set Common Cfg
    COMMONK_LoadDefault(&tCommonCfg);
    COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = COMMONK_CommonCfgExportByHexData(
        0x0000,
        &tCommonCfg,
        aucHexBufferTmp
        );


    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        COMMONK_CommonCfgImportByHexData(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tCommonCfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength>>2));
    }

    lCompare = memcmp(&tCommonCfgHex, &tCommonCfg, sizeof(alCOMMONK_CommonCfg));
#endif

#if 1 // test ManualK CFG
    memset(&tEAGLEK3_Cfg, 0, sizeof(EAGLEK3_Cfg));
    memset(&tEAGLEK3_CfgHex, 0, sizeof(EAGLEK3_Cfg));

    // load MANUALK Cfg
    MANUALK_CfgImport(awcConfigFilePath, tEAGLEK3_Cfg.atMANUALK_Cfg);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = MANUALK_CfgExportHex(
        0x0001,
        tEAGLEK3_Cfg.atMANUALK_Cfg,
        aucHexBufferTmp
        );

    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        MANUALK_CfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            tEAGLEK3_CfgHex.atMANUALK_Cfg
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    lCompare = memcmp(tEAGLEK3_CfgHex.atMANUALK_Cfg, tEAGLEK3_Cfg.atMANUALK_Cfg, sizeof(alMANUALK_CameraCfg) * 4);
#endif

#if 1 // test Field Data CFG
    memset(&tEAGLEK3_FeildData, 0, sizeof(EAGLEK3_FieldData));
    memset(&tEAGLEK3_FeildDataHex, 0, sizeof(EAGLEK3_FieldData));

    wcscpy_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, L"CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, L"FACAUTOK_CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, L"CalSettingFineTune_MV_MC.ini");

    // Load feild data from INI file
    EAGLEK3_LoadFieldDataByINI(
        awcFeildDataINIFilePath_ManualK,
        awcFeildDataINIFilePath_AutoK,
        awcFeildDataINIFilePath_FineTune,
        &tEAGLEK3_FeildData
        );

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = EAGLEK3_FieldDataExportHex(
        0x0300,
        &tEAGLEK3_FeildData,
        aucHexBufferTmp
        );

    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_FieldDataImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tEAGLEK3_FeildDataHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    lCompare = memcmp(&tEAGLEK3_FeildDataHex, &tEAGLEK3_FeildData, sizeof(EAGLEK3_FieldData));
#endif

#if 1 // test AutoK CFG
    memset(&tEAGLEK3_Cfg, 0, sizeof(EAGLEK3_Cfg));
    memset(&tEAGLEK3_CfgHex, 0, sizeof(EAGLEK3_Cfg));

    // Load alBVCAM FACAUTOK Cfg
    alBVCAM_FACAUTOK_CfgImportINI(awcConfigFilePath, &tEAGLEK3_Cfg.tAutoK_Cfg);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = alBVCAM_FACAUTOK_CfgExport(
        0x0001,
        &tEAGLEK3_Cfg.tAutoK_Cfg,
        aucHexBufferTmp
    );

    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alBVCAM_FACAUTOK_CfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tEAGLEK3_CfgHex.tAutoK_Cfg
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    lCompare = memcmp(&tEAGLEK3_CfgHex.tAutoK_Cfg, &tEAGLEK3_Cfg.tAutoK_Cfg, sizeof(BVCAM_FACAUTOK_CFG));
#endif

#if 1 // test EagleK3 CFG
    memset(&tEAGLEK3_Cfg, 0, sizeof(EAGLEK3_Cfg));
    memset(&tEAGLEK3_CfgHex, 0, sizeof(EAGLEK3_Cfg));

    // Load EagleK3 Cfg
    EAGLEK3_LoadUserCfgByINI(awcConfigFilePath, &tEAGLEK3_Cfg);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = EAGLEK3_CfgExportHex(
        0x0001,
        &tEAGLEK3_Cfg,
        aucHexBufferTmp
        );

    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_CfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tEAGLEK3_CfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // export 
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = EAGLEK3_ExtrinsicCfgExportHex(
        0x0005,
        tEAGLEK3_Cfg.atCameraExtrinsicParams,
        aucHexBufferTmp
        );

    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_ExtrinsicCfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            tEAGLEK3_CfgHex.atCameraExtrinsicParams
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // export 
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = EAGLEK3_CalibrationCfgExportHex(
        0x0005,
        tEAGLEK3_Cfg.atCalibrationParams,
        aucHexBufferTmp
        );

    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_CalibrationCfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            tEAGLEK3_CfgHex.atCalibrationParams
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }



    lCompare = memcmp(tEAGLEK3_CfgHex.atMANUALK_Cfg, tEAGLEK3_Cfg.atMANUALK_Cfg, sizeof(alMANUALK_CameraCfg) * 4);
    lCompare = memcmp(&tEAGLEK3_CfgHex.tAutoK_Cfg, &tEAGLEK3_Cfg.tAutoK_Cfg, sizeof(BVCAM_FACAUTOK_CFG));
    lCompare = memcmp(tEAGLEK3_CfgHex.atCameraExtrinsicParams, tEAGLEK3_Cfg.atCameraExtrinsicParams, sizeof(alCAMERAINFO_ExtrinsicParams) * 4);
    lCompare = memcmp(tEAGLEK3_CfgHex.atCalibrationParams, tEAGLEK3_Cfg.atCalibrationParams, sizeof(alCOMMONK_CalibrationParams) * 4);
    lCompare = memcmp(&tEAGLEK3_CfgHex, &tEAGLEK3_Cfg, sizeof(EAGLEK3_Cfg));
#endif

#if 1 // test AVM2D CFG
    // set AVM2D
    alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);

    // export
    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    ulHexFileSize = alAVM2D_CfgExportByHexData(
        0x0002,
        &tAVM2D_Cfg,
        aucHexBufferTmp
        );


    ulBufferLength = (ulHexFileSize);
    pucBuffer = (UINT32*)aucHexBufferTmp;  // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;
    lCompare = 0;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alAVM2D_CfgImportByHexData(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tAVM2D_CfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    lCompare = memcmp(&tAVM2D_CfgHex, &tAVM2D_Cfg, sizeof(alAVM2D_Cfg));
#endif

}


void Test_HexFile_Export_TMP_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    alFM_v2_1_ModelCfg atFM_BV_Cfg[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, atFM_BV_CfgHex[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    EAGLEK3_FieldData tEAGLEK3_FeildData = { 0 }, tEAGLEK3_FeildDataHex = { 0 };
    EAGLEK3_Cfg tEAGLEK3_Cfg = { 0 }, tEAGLEK3_CfgHex = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 }, tAVM2D_CfgHex = { 0 };
    alCOMMONK_CommonCfg tCommonCfg = { 0 }, tCommonCfgHex = { 0 };
    alALLEYVIEW_Cfg tSAV_Cfg = { 0 }, tFAV_Cfg = { 0 };
    alALLEYVIEW_Cfg tSAV_CfgHex = { 0 }, tFAV_CfgHex = { 0 };
    alTRAILLINE_Cfg tTL_Cfg = { 0 }, tTL_CfgHex = { 0 };

    UINT32 ulHexFileSize = 0, ulHexFileSizeHeader = 0, ulSizeTotal = 0, ulSizeTmp = 0;
    UINT32 ulCommonKSize = 0, ulEagleK3Size = 0, ulAVSize = 0;
    UINT8 aucHexBufferTmp[TEST_HEX_BUFFER_SIZE] = { 0 };
    UINT8 aucHexBufferTmp_1[TEST_HEX_BUFFER_SIZE] = { 0 };

    UINT8 *pucCfgPointer = NULL;
    UINT32 *pulPointerTmp = NULL;
    UINT32 *pulPointerTmp_1 = NULL;
    UINT32 ulDataID;                                // Single Data ID
    UINT32 ulDataLength;                            // Single Data Length
    UINT8 *pucDataBuffer;                           // Single Data Buffer
    UINT32 ulBufferLength = (ulHexFileSize);
    UINT32 *pucBuffer = (UINT32*)aucHexBufferTmp;   // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 *pulPtr = pucBuffer;
    int lCompare = 0, lCnt = 0;

    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);


#if 1
    FILE *pFileSrc = NULL;
    UINT8 *apucCfgFileBuffer[4] = { 0 };
    UINT32 aulCfgFileSize[4] = { 14652, 4928, 3664, 3320 }, ulIndex = 0;
    UINT32 *pulBuffer = NULL;
    UINT32 *pulPtrTmp = NULL;
    UINT32 *pulPtrTmp1 = NULL;

    apucCfgFileBuffer[0] = (UINT8*)malloc(aulCfgFileSize[0]);
    pFileSrc = fopen("EAGLE3_CFG_1_t.hex", "rb");
    fread(apucCfgFileBuffer[0], aulCfgFileSize[0], 1, pFileSrc);
    fclose(pFileSrc);


    // import EagleK3 Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_EAGLEK3, apucCfgFileBuffer[0], aulCfgFileSize[0], &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        if (*pulPtr == 0x00011213)
        {
            pulPtrTmp = pulBuffer + ulIndex + 2;
            pulPtrTmp1 = pulBuffer + ulIndex + 2 + 1;
        }

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &tEAGLEK3_CfgHex);

        // tEAGLEK3_CfgHex.tAutoK_Cfg.atCrossMarkKCfg[1].atROICfg

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
        ulIndex += (2 + (ulDataLength >> 2));
    }
    free(apucCfgFileBuffer[0]);
#endif


    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);


    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);

    // set Commonk Cfg
    COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

    // set AVM2D Cfg
    alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);

    // export Commonk Cfg
    ulHexFileSizeHeader = COMMONK_CommonCfgExportByHexData(alHEXCODER_COMMONK, &tCommonCfg, NULL);
    ulSizeTotal += ulHexFileSizeHeader + 8;

    *pulPtr = alHEXCODER_COMMONK;
    *(pulPtr + 1) = ulHexFileSizeHeader >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulHexFileSizeHeader >> 2));

    ulHexFileSize = COMMONK_CommonCfgExportByHexData(alHEXCODER_COMMONK, &tCommonCfg, pucDataBuffer);

#if 0
    // import Commonk Cfg
    pucBuffer = (UINT32*)(aucHexBufferTmp+8);
    pulPtr = pucBuffer;
    ulBufferLength = ulHexFileSize;

    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        COMMONK_CommonCfgImportByHexData(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tCommonCfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    lCompare = memcmp(&tCommonCfgHex, &tCommonCfg, sizeof(alCOMMONK_CommonCfg));
#endif

    pulPointerTmp = (UINT32*)(aucHexBufferTmp + 236);

    // export AVM2D Cfg
    ulHexFileSizeHeader = alAVM2D_CfgExportByHexData(alHEXCODER_AVM2D, &tAVM2D_Cfg, NULL);
    ulSizeTotal += ulHexFileSizeHeader + 8;

    *pulPtr = alHEXCODER_AVM2D;
    *(pulPtr + 1) = ulHexFileSizeHeader>>2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulHexFileSizeHeader >> 2));

    ulHexFileSize = alAVM2D_CfgExportByHexData(alHEXCODER_AVM2D, &tAVM2D_Cfg, pucDataBuffer);


    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_AVM2D, aucHexBufferTmp, ulSizeTotal, &ulBufferLength);
    pulPointerTmp_1 = (UINT32*)aucHexBufferTmp;

    // import AVM2D Cfg
    pucBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pucBuffer;

    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alAVM2D_CfgImportByHexData(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tAVM2D_CfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    lCompare = memcmp(&tAVM2D_CfgHex, &tAVM2D_Cfg, sizeof(alAVM2D_Cfg));

}


void Test_HexFile_Export_CFG1_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    alFM_v2_1_ModelCfg atFM_BV_Cfg[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, atFM_BV_CfgHex[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    EAGLEK3_FieldData tEAGLEK3_FeildData = { 0 }, tEAGLEK3_FeildDataHex = { 0 };
    EAGLEK3_Cfg tEAGLEK3_Cfg = { 0 }, tEAGLEK3_CfgHex = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 }, tAVM2D_CfgHex = { 0 };
    alCOMMONK_CommonCfg tCommonCfg = { 0 }, tCommonCfgHex = { 0 };
    alALLEYVIEW_Cfg tSAV_Cfg = { 0 }, tFAV_Cfg = { 0 };
    alALLEYVIEW_Cfg tSAV_CfgHex = { 0 }, tFAV_CfgHex = { 0 };
    alTRAILLINE_Cfg tTL_Cfg = { 0 }, tTL_CfgHex = { 0 };

    UINT32 ulHexFileSize = 0, ulHexFileSizeHeader = 0, ulSizeTotal = 0, ulSizeTmp = 0;
    UINT32 ulCommonKSize = 0, ulEagleK3Size = 0, ulAVM2DSize = 0, ulAVSize = 0;
    UINT32 ulTLSize = 0, ulExtrinsicSize = 0, ulCalibrateSize = 0, ulCFG1_Size = 0;
    UINT8 aucHexBufferTmp[TEST_HEX_BUFFER_SIZE] = { 0 };
    UINT8 aucHexBufferTmp_1[TEST_HEX_BUFFER_SIZE] = { 0 };

    UINT8 *pucCfgPointer = NULL;
    UINT8 *pucCfgPointerOut = NULL;
    UINT32 ulDataID;                                // Single Data ID
    UINT32 ulDataLength;                            // Single Data Length
    UINT8 *pucDataBuffer;                           // Single Data Buffer
    UINT32 ulBufferLength = (ulHexFileSize);
    UINT32 *pulBuffer = (UINT32*)aucHexBufferTmp;   // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 *pulPtr = pulBuffer;
    int lCompare = 0, lCnt = 0;

    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);


    memset(aucHexBufferTmp, 0, TEST_HEX_BUFFER_SIZE);
    memset(&tEAGLEK3_Cfg, 0, sizeof(EAGLEK3_Cfg));
    memset(&tEAGLEK3_CfgHex, 0, sizeof(EAGLEK3_Cfg));

    // set Commonk Cfg
    COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

    // set EagleK3 Cfg
    EAGLEK3_LoadUserCfgByINI(awcConfigFilePath, &tEAGLEK3_Cfg);

    // set AVM2D Cfg
    alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);

    // set Alley View Cfg
    alALLEYVIEW_CfgImportByINI(&tSAV_Cfg, &tFAV_Cfg, awcConfigFilePath);

    // set Trail Line Cfg
    alTRAILLINE_CfgImportByINI(awcConfigFilePath, &tTL_Cfg);

    // point 可以為null 但 cfg要有正確的值 不然會出錯  ex: autoK 的 view number...
    ulCommonKSize = COMMONK_CommonCfgExportByHexData(alHEXCODER_COMMONK, &tCommonCfg, NULL);
    ulEagleK3Size = EAGLEK3_CfgExportHex(alHEXCODER_EAGLEK3, &tEAGLEK3_Cfg, NULL);
    ulAVM2DSize = alAVM2D_CfgExportByHexData(alHEXCODER_AVM2D, &tAVM2D_Cfg, NULL);
    ulAVSize = AV_CfgExportHex(alHEXCODER_ALLEYVIEW, &tSAV_Cfg, &tFAV_Cfg, NULL);
    ulTLSize = alTRAILLINE_CfgExportHex(alHEXCODER_TRAILLINE, &tTL_Cfg, NULL);
    ulExtrinsicSize = EAGLEK3_ExtrinsicCfgExportHex(alHEXCODER_EXTRINSIC_CFG, tEAGLEK3_Cfg.atCameraExtrinsicParams, NULL);
    ulCalibrateSize = EAGLEK3_CalibrationCfgExportHex(alHEXCODER_CALIBRATE_CFG, tEAGLEK3_Cfg.atCalibrationParams, NULL);
    ulCFG1_Size = ulCommonKSize + ulEagleK3Size + ulAVM2DSize + ulAVSize + ulTLSize + ulExtrinsicSize + ulCalibrateSize;


    ulSizeTotal = ulCFG1_Size + 8 * 7;
    pucCfgPointerOut = (UINT8*)malloc(ulSizeTotal);
    pulPtr = (UINT32*)pucCfgPointerOut;


    // export Commonk Cfg
    *pulPtr = alHEXCODER_COMMONK;
    *(pulPtr + 1) = ulCommonKSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulCommonKSize >> 2));
    ulHexFileSize = COMMONK_CommonCfgExportByHexData(alHEXCODER_COMMONK, &tCommonCfg, pucDataBuffer);


    // tEAGLEK3_Cfg.tAutoK_Cfg.atCrossMarkKCfg[1].atROICfg[0].aeSBVScale = 10.0;
    // export Eaglek3
    *pulPtr = alHEXCODER_EAGLEK3;
    *(pulPtr + 1) = ulEagleK3Size >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulEagleK3Size >> 2));
    ulHexFileSize = EAGLEK3_CfgExportHex(alHEXCODER_EAGLEK3, &tEAGLEK3_Cfg, pucDataBuffer);


    // export AVM2D Cfg
    *pulPtr = alHEXCODER_AVM2D;
    *(pulPtr + 1) = ulAVM2DSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulAVM2DSize >> 2));
    ulHexFileSize = alAVM2D_CfgExportByHexData(alHEXCODER_AVM2D, &tAVM2D_Cfg, pucDataBuffer);

    // export AV Cfg
    *pulPtr = alHEXCODER_ALLEYVIEW;
    *(pulPtr + 1) = ulAVSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulAVSize >> 2));
    ulHexFileSize = AV_CfgExportHex(alHEXCODER_ALLEYVIEW, &tSAV_Cfg, &tFAV_Cfg, pucDataBuffer);

    // export TL Cfg
    *pulPtr = alHEXCODER_TRAILLINE;
    *(pulPtr + 1) = ulTLSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulTLSize >> 2));
    ulHexFileSize = alTRAILLINE_CfgExportHex(alHEXCODER_TRAILLINE, &tTL_Cfg, pucDataBuffer);

    // export Extrinsic Params Cfg
    *pulPtr = alHEXCODER_EXTRINSIC_CFG;
    *(pulPtr + 1) = ulExtrinsicSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulExtrinsicSize >> 2));
    ulHexFileSize = EAGLEK3_ExtrinsicCfgExportHex(alHEXCODER_EXTRINSIC_CFG, tEAGLEK3_Cfg.atCameraExtrinsicParams, pucDataBuffer);

    // export Calibrate Params Cfg
    *pulPtr = alHEXCODER_CALIBRATE_CFG;
    *(pulPtr + 1) = ulCalibrateSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulCalibrateSize >> 2));
    ulHexFileSize = EAGLEK3_CalibrationCfgExportHex(alHEXCODER_CALIBRATE_CFG, tEAGLEK3_Cfg.atCalibrationParams, pucDataBuffer);


    // import CommonK Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_COMMONK, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        COMMONK_CommonCfgImportByHexData(ulDataID, ulDataLength, pucDataBuffer, &tCommonCfgHex);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import EagleK3 Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_EAGLEK3, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_CfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tEAGLEK3_CfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }
    

    // import AVM2D Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_AVM2D, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alAVM2D_CfgImportByHexData(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            &tAVM2D_CfgHex
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import AV Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_ALLEYVIEW, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        AV_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &tSAV_CfgHex, &tFAV_CfgHex);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import TL Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_TRAILLINE, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alTRAILLINE_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &tTL_CfgHex);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import Extrinsic Params Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_EXTRINSIC_CFG, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_ExtrinsicCfgImportHex(
            ulDataID,
            ulDataLength,
            pucDataBuffer,
            tEAGLEK3_CfgHex.atCameraExtrinsicParams
            );

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import Calibrate Params Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_CALIBRATE_CFG, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_CalibrationCfgImportHex(ulDataID, ulDataLength, pucDataBuffer, tEAGLEK3_CfgHex.atCalibrationParams);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }


    // Compare
    lCompare = memcmp(&tCommonCfgHex, &tCommonCfg, sizeof(alCOMMONK_CommonCfg));
    lCompare = memcmp(&tAVM2D_CfgHex, &tAVM2D_Cfg, sizeof(alAVM2D_Cfg));
    lCompare = memcmp(&tSAV_CfgHex, &tSAV_Cfg, sizeof(alALLEYVIEW_Cfg));
    lCompare = memcmp(&tFAV_CfgHex, &tFAV_Cfg, sizeof(alALLEYVIEW_Cfg));
    lCompare = memcmp(&tTL_CfgHex, &tTL_Cfg, sizeof(alTRAILLINE_Cfg));
    lCompare = memcmp(tEAGLEK3_CfgHex.atCameraExtrinsicParams, tEAGLEK3_Cfg.atCameraExtrinsicParams, sizeof(alCAMERAINFO_ExtrinsicParams) * 4);
    lCompare = memcmp(tEAGLEK3_CfgHex.atCalibrationParams, tEAGLEK3_Cfg.atCalibrationParams, sizeof(alCOMMONK_CalibrationParams) * 4);
    lCompare = memcmp(tEAGLEK3_CfgHex.atMANUALK_Cfg, tEAGLEK3_Cfg.atMANUALK_Cfg, sizeof(alMANUALK_CameraCfg) * 4);
    lCompare = memcmp(&tEAGLEK3_CfgHex.tAutoK_Cfg, &tEAGLEK3_Cfg.tAutoK_Cfg, sizeof(BVCAM_FACAUTOK_CFG));
    lCompare = memcmp(&tEAGLEK3_CfgHex, &tEAGLEK3_Cfg, sizeof(EAGLEK3_Cfg));

    // output configure file 1
    wcstombs(g_acCfgFileOutputFolder, a_pwcOutImageFolder, MAX_PATH);
    sprintf(g_acCfgFileOutputFolder, "%sEAGLE3_CFG_1.hex", g_acCfgFileOutputFolder);

    g_ptCfgFilePtr = fopen(g_acCfgFileOutputFolder, "wb");
    fwrite(pucCfgPointerOut, ulSizeTotal, 1, g_ptCfgFilePtr);
    fclose(g_ptCfgFilePtr);


    free(pucCfgPointerOut);

#if 0 // do ManualK and export configure file 3
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };

    UINT8 * apucSrcImage[4];
    UINT8 * pucSrcBufferFront = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRear = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferLeft = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRight = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];

    apucSrcImage[0] = pucSrcBufferLeft;
    apucSrcImage[1] = pucSrcBufferRight;
    apucSrcImage[2] = pucSrcBufferFront;
    apucSrcImage[3] = pucSrcBufferRear;

    std::wstring sImageLeft = std::wstring(a_pwcSrcImageFolder).append(L"Source_0.raw");
    std::wstring sImageRight = std::wstring(a_pwcSrcImageFolder).append(L"Source_1.raw");
    std::wstring sImageFront = std::wstring(a_pwcSrcImageFolder).append(L"Source_2.raw");
    std::wstring sImageRear = std::wstring(a_pwcSrcImageFolder).append(L"Source_3.raw");

    std::ifstream ifile;
    ifile.open(sImageFront.c_str(), std::ios::binary);
    ifile.read((char*)pucSrcBufferFront, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ifile.close();
    ifile.open(sImageRear.c_str(), std::ios::binary);
    ifile.read((char*)pucSrcBufferRear, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ifile.close();
    ifile.open(sImageLeft.c_str(), std::ios::binary);
    ifile.read((char*)pucSrcBufferLeft, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ifile.close();
    ifile.open(sImageRight.c_str(), std::ios::binary);
    ifile.read((char*)pucSrcBufferRight, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ifile.close();

    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucEagleK3WorkingBuffer = NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0, ulCFG3_Size = 0;
    alAVM2D_Params tAVM2D_Params = { 0 };
    EAGLEK3_Data tEAGLEK3_Data = {0};
    EAGLEK3_Data tEAGLEK3_DataHex = { 0 };
    EAGLEK3_Param tEAGLEK3_Params = {0};
    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL];
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL];

    memset(&tEAGLEK3_Data, 0, sizeof(EAGLEK3_Data));
    memset(&tEAGLEK3_DataHex, 0, sizeof(EAGLEK3_Data));

    // Set_Bird-View_Fisheye Model (Test_SET_BV_FM will malloc for apucFMBuffer >> need to free)
    Test_SET_BV_FM(awcConfigFilePath, atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

    // Test DeFishEye Image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, 1.0, atFM_v2_Model);

    // Initialize for EagleK3
    wcscpy_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, L"CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, L"FACAUTOK_CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, L"CalSettingFineTune_MV_MC.ini");

    // Load feild data from INI file
    EAGLEK3_LoadFieldDataByINI(
        awcFeildDataINIFilePath_ManualK,
        awcFeildDataINIFilePath_AutoK,
        awcFeildDataINIFilePath_FineTune,
        &tEAGLEK3_FeildData
        );

    alAVM2D_InitialByConfigData(&tAVM2D_Cfg, &tCommonCfg, &tAVM2D_Params);

    // Initial By Cfg Data
    ulEagleK3BufferSize = EAGLEK3_QueryEagleK3_WorkingBufferSizeSingle(&tEAGLEK3_Cfg);
    pucEagleK3WorkingBuffer = (UINT8*)malloc(ulEagleK3BufferSize);
    EAGLEK3_InitialByConfigData(
        atFM_v2_Model, &tCommonCfg, &tAVM2D_Cfg, &tAVM2D_Params,
        &tEAGLEK3_FeildData, &tEAGLEK3_Cfg, &tEAGLEK3_Params,
        &tEAGLEK3_Data, pucEagleK3WorkingBuffer
        );


    // TEST ManualK
    Test_ManualK(apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data);


    ulExtrinsicSize = EAGLEK3_ExtrinsicCfgExportHex(alHEXCODER_EXTRINSIC_RESULT, tEAGLEK3_Data.atCameraExtrinsicParams, NULL);
    ulCalibrateSize = EAGLEK3_CalibrationCfgExportHex(alHEXCODER_CALIBRATE_RESULT, tEAGLEK3_Data.atCalibrationParams, NULL);

    ulCFG3_Size = ulExtrinsicSize + ulCalibrateSize;

    ulSizeTotal = ulCFG3_Size + 8 * 2;
    pucCfgPointerOut = (UINT8*)malloc(ulSizeTotal);
    pulPtr = (UINT32*)pucCfgPointerOut;

    // export Extrinsic Params Result
    *pulPtr = alHEXCODER_EXTRINSIC_RESULT;
    *(pulPtr + 1) = ulExtrinsicSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulExtrinsicSize >> 2));
    ulHexFileSize = EAGLEK3_ExtrinsicCfgExportHex(alHEXCODER_EXTRINSIC_RESULT, tEAGLEK3_Data.atCameraExtrinsicParams, pucDataBuffer);

    // export Calibrate Params Result
    *pulPtr = alHEXCODER_CALIBRATE_RESULT;
    *(pulPtr + 1) = ulCalibrateSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulCalibrateSize >> 2));
    ulHexFileSize = EAGLEK3_CalibrationCfgExportHex(alHEXCODER_CALIBRATE_RESULT, tEAGLEK3_Data.atCalibrationParams, pucDataBuffer);


    // import Extrinsic Params Result
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_EXTRINSIC_RESULT, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_ExtrinsicCfgImportHex(ulDataID, ulDataLength, pucDataBuffer, tEAGLEK3_DataHex.atCameraExtrinsicParams);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import Calibrate Params Result
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_CALIBRATE_RESULT, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_CalibrationCfgImportHex(ulDataID, ulDataLength, pucDataBuffer, tEAGLEK3_DataHex.atCalibrationParams);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    lCompare = memcmp(tEAGLEK3_DataHex.atCameraExtrinsicParams, tEAGLEK3_Data.atCameraExtrinsicParams, sizeof(alCAMERAINFO_ExtrinsicParams) * 4);
    lCompare = memcmp(tEAGLEK3_DataHex.atCalibrationParams, tEAGLEK3_Data.atCalibrationParams, sizeof(alCOMMONK_CalibrationParams) * 4);

    // output configure file 3
    wcstombs(g_acCfgFileOutputFolder, a_pwcOutImageFolder, MAX_PATH);
    sprintf(g_acCfgFileOutputFolder, "%sEAGLE3_CFG_3.hex", g_acCfgFileOutputFolder);

    g_ptCfgFilePtr = fopen(g_acCfgFileOutputFolder, "wb");
    fwrite(pucCfgPointerOut, ulSizeTotal, 1, g_ptCfgFilePtr);
    fclose(g_ptCfgFilePtr);

    free(pucCfgPointerOut);

    // free Eaglek3 Buffer
    free(pucEagleK3WorkingBuffer);

    // free FM Buffer
    free(apucFMBuffer[EAGLEK3_BV_LEFT]);
    free(apucFMBuffer[EAGLEK3_BV_RIGHT]);
    free(apucFMBuffer[EAGLEK3_BV_FRONT]);
    free(apucFMBuffer[EAGLEK3_BV_BACK]);

    delete[] pucSrcBufferFront;
    delete[] pucSrcBufferRear;
    delete[] pucSrcBufferLeft;
    delete[] pucSrcBufferRight;
    delete[] pucDestBuffer;
#endif
}

void Test_HexFile_Export_CFG2_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    alFM_v2_1_ModelCfg atFM_BV_Cfg[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, atFM_BV_CfgHex[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    EAGLEK3_FieldData tEAGLEK3_FeildData = { 0 }, tEAGLEK3_FeildDataHex = { 0 };

    UINT32 aulFM_Size[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    UINT32 ulCFG2_Size = 0, ulSizeTotal = 0, ulHexFileSize = 0;

    UINT8 *pucCfgPointer = NULL;
    UINT8 *pucCfgPointerOut = NULL;
    UINT32 *pulPointerTmp = NULL;
    UINT32 *pulPointerTmp_1 = NULL;
    UINT32 ulDataID;                                // Single Data ID
    UINT32 ulDataLength;                            // Single Data Length
    UINT8 *pucDataBuffer;                           // Single Data Buffer
    UINT32 ulBufferLength = 0;
    UINT32 *pulBuffer = NULL;   // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 *pulPtr = pulBuffer;
    int lCompare = 0, lCnt = 0;

    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Load conifg data from INI file
    EAGLEK3_LoadFM_BV_CfgByINI(awcConfigFilePath, EAGLEK3_NUM_BV_CHANNEL, atFM_BV_Cfg);

    aulFM_Size[0] = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_LEFT, &atFM_BV_Cfg[0], NULL);
    aulFM_Size[1] = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_RIGHT, &atFM_BV_Cfg[1], NULL);
    aulFM_Size[2] = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_FRONT, &atFM_BV_Cfg[2], NULL);
    aulFM_Size[3] = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_BACK, &atFM_BV_Cfg[3], NULL);
    
    ulCFG2_Size = aulFM_Size[0] + aulFM_Size[1] + aulFM_Size[2] + aulFM_Size[3];

    ulSizeTotal = ulCFG2_Size + 8 * 4;
    pucCfgPointerOut = (UINT8*)malloc(ulSizeTotal);
    pulPtr = (UINT32*)pucCfgPointerOut;

    // export BV 0
    *pulPtr = alHEXCODER_FM_LEFT;
    *(pulPtr + 1) = aulFM_Size[0] >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (aulFM_Size[0] >> 2));
    ulHexFileSize = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_LEFT, &atFM_BV_Cfg[0], pucDataBuffer);

    // export BV 1
    *pulPtr = alHEXCODER_FM_RIGHT;
    *(pulPtr + 1) = aulFM_Size[1] >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (aulFM_Size[1] >> 2));
    ulHexFileSize = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_RIGHT, &atFM_BV_Cfg[1], pucDataBuffer);

    // export BV 2
    *pulPtr = alHEXCODER_FM_FRONT;
    *(pulPtr + 1) = aulFM_Size[2] >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (aulFM_Size[2] >> 2));
    ulHexFileSize = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_FRONT, &atFM_BV_Cfg[2], pucDataBuffer);

    // export BV 0
    *pulPtr = alHEXCODER_FM_BACK;
    *(pulPtr + 1) = aulFM_Size[3] >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (aulFM_Size[3] >> 2));
    ulHexFileSize = alFM_v2_1_SingleFisheyeModelCfgExport(alHEXCODER_FM_BACK, &atFM_BV_Cfg[3], pucDataBuffer);

   

    // import BV 0 Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_FM_LEFT, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alFM_v2_1_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &atFM_BV_CfgHex[0]);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import BV 1 Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_FM_RIGHT, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alFM_v2_1_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &atFM_BV_CfgHex[1]);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import BV 2 Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_FM_FRONT, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alFM_v2_1_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &atFM_BV_CfgHex[2]);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // import BV 3 Cfg
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_FM_BACK, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        alFM_v2_1_CfgImportHex(ulDataID, ulDataLength, pucDataBuffer, &atFM_BV_CfgHex[3]);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    // Compare
    lCompare = memcmp(&atFM_BV_CfgHex[0], &atFM_BV_Cfg[0], sizeof(alFM_v2_1_ModelCfg));
    lCompare = memcmp(&atFM_BV_CfgHex[1], &atFM_BV_Cfg[1], sizeof(alFM_v2_1_ModelCfg));
    lCompare = memcmp(&atFM_BV_CfgHex[2], &atFM_BV_Cfg[2], sizeof(alFM_v2_1_ModelCfg));
    lCompare = memcmp(&atFM_BV_CfgHex[3], &atFM_BV_Cfg[3], sizeof(alFM_v2_1_ModelCfg));

    // output configure file 2
    wcstombs(g_acCfgFileOutputFolder, a_pwcOutImageFolder, MAX_PATH);
    sprintf(g_acCfgFileOutputFolder, "%sEAGLE3_CFG_2.hex", g_acCfgFileOutputFolder);

    g_ptCfgFilePtr = fopen(g_acCfgFileOutputFolder, "wb");
    fwrite(pucCfgPointerOut, ulSizeTotal, 1, g_ptCfgFilePtr);
    fclose(g_ptCfgFilePtr);


    free(pucCfgPointerOut);
}


void Test_HexFile_Export_CFG4_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };
    EAGLEK3_FieldData tEAGLEK3_FeildData = { 0 }, tEAGLEK3_FeildDataHex = { 0 };

    UINT32 ulCFG4_Size = 0, ulSizeTotal = 0, ulHexFileSize = 0, ulFieldDataSize = 0;

    UINT8 *pucCfgPointer = NULL;
    UINT8 *pucCfgPointerOut = NULL;
    UINT32 ulDataID;                                // Single Data ID
    UINT32 ulDataLength;                            // Single Data Length
    UINT8 *pucDataBuffer;                           // Single Data Buffer
    UINT32 ulBufferLength = 0;
    UINT32 *pulBuffer = NULL;   // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 *pulPtr = pulBuffer;
    int lCompare = 0, lCnt = 0;

    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    memset(&tEAGLEK3_FeildData, 0, sizeof(EAGLEK3_FieldData));
    memset(&tEAGLEK3_FeildDataHex, 0, sizeof(EAGLEK3_FieldData));

    wcscpy_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, L"CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, L"FACAUTOK_CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, L"CalSettingFineTune_MV_MC.ini");

    ulFieldDataSize = EAGLEK3_FieldDataExportHex(alHEXCODER_EAGLEK3_FIELD_DATA, &tEAGLEK3_FeildData, NULL);
    ulCFG4_Size = ulFieldDataSize;
    ulSizeTotal = ulCFG4_Size + 8;

    pucCfgPointerOut = (UINT8*)malloc(ulSizeTotal);
    pulPtr = (UINT32*)pucCfgPointerOut;


    // Load feild data from INI file
    EAGLEK3_LoadFieldDataByINI(
        awcFeildDataINIFilePath_ManualK,
        awcFeildDataINIFilePath_AutoK,
        awcFeildDataINIFilePath_FineTune,
        &tEAGLEK3_FeildData
        );

    // export
    *pulPtr = alHEXCODER_EAGLEK3_FIELD_DATA;
    *(pulPtr + 1) = ulFieldDataSize >> 2;
    pucDataBuffer = (UINT8 *)(pulPtr + 2);
    pulPtr += (2 + (ulFieldDataSize >> 2));
    ulHexFileSize = EAGLEK3_FieldDataExportHex(alHEXCODER_EAGLEK3_FIELD_DATA, &tEAGLEK3_FeildData, pucDataBuffer);

    // import Field Data
    pucCfgPointer = alHEXCODER_GetCfgBuffer(alHEXCODER_EAGLEK3_FIELD_DATA, pucCfgPointerOut, ulSizeTotal, &ulBufferLength);
    pulBuffer = (UINT32*)pucCfgPointer;
    pulPtr = pulBuffer;
    while ((INT32)(pulPtr - pulBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        ulDataLength = ulDataLength << 2; // 在hex 中是以UINT32 為單位

        // 2. 將 Single Data 資訊匯入
        EAGLEK3_FieldDataImportHex(ulDataID, ulDataLength, pucDataBuffer, &tEAGLEK3_FeildDataHex);

        // 3. 累進指標
        pulPtr += (2 + (ulDataLength >> 2));
    }

    lCompare = memcmp(&tEAGLEK3_FeildDataHex, &tEAGLEK3_FeildData, sizeof(EAGLEK3_FieldData));

    // output configure file 2
    wcstombs(g_acCfgFileOutputFolder, a_pwcOutImageFolder, MAX_PATH);
    sprintf(g_acCfgFileOutputFolder, "%sEAGLE3_CFG_4.hex", g_acCfgFileOutputFolder);

    g_ptCfgFilePtr = fopen(g_acCfgFileOutputFolder, "wb");
    fwrite(pucCfgPointerOut, ulSizeTotal, 1, g_ptCfgFilePtr);
    fclose(g_ptCfgFilePtr);

    free(pucCfgPointerOut);  
}


void Test_LineSegDetectTmp()
{
    FLOAT64 *peLineDetectResult = NULL;
    alRectINT32 tROI = { 0 };
    UINT8 *pucBuffer = NULL;
    UINT8 *pucYBuffer = NULL; // 160*183
    INT32 lLineNum = 0, lWidth = 0, lHeight = 0;
    FILE *pFileSrc = NULL;

    tROI.lTop = 158;
    tROI.lLeft = 181;
    tROI.lBottom = 340;
    tROI.lRight = 340;

    lWidth = tROI.lRight - tROI.lLeft + 1;
    lHeight = tROI.lBottom - tROI.lTop + 1;

    pucYBuffer = (UINT8*)malloc(lWidth*lHeight);
    pucBuffer = (UINT8*)malloc(lWidth*lHeight*sizeof(FLOAT64));

    pFileSrc = fopen("sbv_test_in.raw", "rb");
    fread(pucYBuffer, lWidth*lHeight, 1, pFileSrc);
    fclose(pFileSrc);

    LineSegDetectionRec(
        pucBuffer, pucYBuffer,
        tROI, &lLineNum, &peLineDetectResult
        );


    free(peLineDetectResult);
    free(pucYBuffer);
    free(pucBuffer);

    IplImage * ptPicGray = NULL;
    pFileSrc = fopen("used_done.txt", "r");
    int lCnt = 0, lTmp =0;

    ptPicGray = cvCreateImage(cvSize(128, 147), IPL_DEPTH_8U, 1);
    memset(ptPicGray->imageData, 0, sizeof(UINT8)*ptPicGray->imageSize);
    

    for (lCnt = 0; lCnt < ptPicGray->imageSize; lCnt++)
    {
        fscanf(pFileSrc, "%d", &lTmp);
        if (lTmp)
        {
            ptPicGray->imageData[lCnt] = 255;
        }
    }

    cvSaveImage("used.bmp", ptPicGray, 0);
    cvReleaseImage(&ptPicGray);

    fclose(pFileSrc);
}