
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>

#include "alLUT_v2.h"
#include "alPartLUT_v1.h"
#include "basedef.h"
#include "EagleK3_SimulateMain.h"


#define AV_PRE_GEN_MASK 1

#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif





void Test_AV_Mask(alALLEYVIEW_Cfg *a_pTCfg, UINT8 *a_pucAV_mask)
{

    INT32 lWidth = 0, lHeight = 0;
    INT32 x, y;
    UINT32 ulRawIndex = 0, ulPixelIndex = 0;
    UINT32 ulByteIndex = 0;
    UINT8 ucBitIndex = 0;
#if 1 // alALLEYVIEWDebug // FOR DEBUG TEST
    IplImage * ptPicGray = NULL;
    char text[MAX_PATH] = { 0 };
    UINT8 *pucAVTest = NULL;
#endif 
    lWidth = a_pTCfg->tAreaSize.lX;
    lHeight = a_pTCfg->tAreaSize.lY;
    pucAVTest = (UINT8 *)malloc(lWidth * lHeight * sizeof(UINT8));

    ///
    // AV LEFT
    for (y = 0; y < lHeight; y++)
    {
        ulRawIndex = y * lWidth;
        for (x = 0; x < (lWidth >> 1); x++)
        {
            ulPixelIndex = ulRawIndex + x;
            ulByteIndex = (ulPixelIndex >> 3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            //apply alley view mask 
            if ( (a_pucAV_mask[ulByteIndex] & (1 << ucBitIndex)) >> ucBitIndex)
            {
                pucAVTest[ulPixelIndex] = 255;
            
            }
            else
            {
                pucAVTest[ulPixelIndex] = 0;
            }

        }
    }

    // AV RIGHT
    for (y = 0; y < lHeight; y++)
    {
        ulRawIndex = y * lWidth + (lWidth >> 1);

        for (x = 0; x < (lWidth >> 1); x++)
        {
            ulPixelIndex = ulRawIndex + x;
            ulByteIndex = (ulPixelIndex >> 3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            //apply alley view mask 
            if ((a_pucAV_mask[ulByteIndex] & (1 << ucBitIndex)) >> ucBitIndex)
            {
                pucAVTest[ulPixelIndex] = 255;
            }
            else
            {
                pucAVTest[ulPixelIndex] = 0;
            }
        }
    }
    ///

#if alALLEYVIEWDebug // FOR DEBUG TEST
    ptPicGray = cvCreateImage(cvSize(lWidth, lHeight), IPL_DEPTH_8U, 1);
    memcpy(ptPicGray->imageData, pucAVTest, sizeof(UINT8)*ptPicGray->imageSize);
    sprintf_s(text, MAX_PATH, "MaskTest_Sim.jpg");
    cvSaveImage(text, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
    
#endif 
    free(pucAVTest);
}

void Test_AV_Generate(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    )
{
    std::wstring sAVLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_AVLUT_set.hex");
    std::wstring sAVLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_AVLUT_data.hex");
    std::wstring sFAVLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_FAVLUT_set.hex");
    std::wstring sFAVLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_FAVLUT_data.hex");
    std::wstring sOutputImgeFile;
    UINT8 * pucBuffer = NULL;
    UINT8 * pucBuffer2 = NULL;
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT32 ulBufferLength = 0, ulBufferLength2 = 0;
    alPartLUT_v1_LUTSet_t tSAV_LUT, tFAV_LUT;

#if 1
    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"Front_test.raw");
    std::ofstream ofile_Test(sOutputImgeFile.c_str(), std::ios::binary);
    ofile_Test.write((char*)a_apucSrcImage[2], IMAGE_WIDTH * IMAGE_HEIGHT * 2);
    ofile_Test.close();
#endif

    // Import AV LUT Set
    if (Test_ImportOtherHexFiles(sAVLUTSetFilePath.c_str(), &pucBuffer, &ulBufferLength))
    {
        if (!Test_ImportOtherHexFiles(sAVLUTDataFilePath.c_str(), &pucBuffer2, &ulBufferLength2))
        {
            assert(0);
        }
            
        memcpy(&tSAV_LUT, pucBuffer, sizeof(alPartLUT_v1_LUTSet_t));
        tSAV_LUT.lut_data = (UINT32*)malloc(tSAV_LUT.lut_data_size*sizeof(UINT32));
        memcpy(tSAV_LUT.lut_data, pucBuffer2, tSAV_LUT.lut_data_size*sizeof(UINT32));

        delete[] pucBuffer;
        delete[] pucBuffer2;

        // Gen AV Image
        memset(pucDestBuffer, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 2);
        alPartLUT_v1_DoTableLookup(a_apucSrcImage, IMAGE_WIDTH, IMAGE_HEIGHT, &tSAV_LUT, pucDestBuffer);

        // Free LUT buffer
        alALLEYVIEW_FreeLUT(&tSAV_LUT);
        
        sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"AV_YUV_ByHex.raw");
        std::ofstream ofile_AV(sOutputImgeFile.c_str(), std::ios::binary);
        ofile_AV.write((char*)pucDestBuffer, IMAGE_WIDTH * IMAGE_HEIGHT * 2);
        ofile_AV.close();       
    }

    // Import FAV LUT Set
    if (Test_ImportOtherHexFiles(sFAVLUTSetFilePath.c_str(), &pucBuffer, &ulBufferLength))
    {
        if (!Test_ImportOtherHexFiles(sFAVLUTDataFilePath.c_str(), &pucBuffer2, &ulBufferLength2))
        {
            assert(0);
        }

        memcpy(&tFAV_LUT, pucBuffer, sizeof(alPartLUT_v1_LUTSet_t));
        tFAV_LUT.lut_data = (UINT32*)malloc(tFAV_LUT.lut_data_size*sizeof(UINT32));
        memcpy(tFAV_LUT.lut_data, pucBuffer2, tFAV_LUT.lut_data_size*sizeof(UINT32));

        delete[] pucBuffer;
        delete[] pucBuffer2;

        // Gen AV Image
        memset(pucDestBuffer, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 2);
        alPartLUT_v1_DoTableLookup(a_apucSrcImage, IMAGE_WIDTH, IMAGE_HEIGHT, &tFAV_LUT, pucDestBuffer);

        // Free LUT buffer
        alALLEYVIEW_FreeLUT(&tFAV_LUT);

        sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"FAV_YUV_ByHex.raw");
        std::ofstream ofile_AV(sOutputImgeFile.c_str(), std::ios::binary);
        ofile_AV.write((char*)pucDestBuffer, IMAGE_WIDTH * IMAGE_HEIGHT * 2);
        ofile_AV.close();
    }

    delete[] pucDestBuffer;
}


void Test_AV_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;
    alPartLUT_v1_LUTSet_t tSAV_LUT, tFAV_LUT;


    UINT8 * apucSrcImage[4];
    UINT8 * pucSrcBufferFront = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRear = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferLeft = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRight = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];

    INT32 alSFPX[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 alSFPY[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };

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

    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL];
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL];
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucEagleK3WorkingBuffer = NULL;
    UINT8  *pucAV_WorkingBuffer = NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0, ulAV_BufferSize = 0;

    EAGLEK3_Cfg tEAGLEK3_Cfg;
    EAGLEK3_FieldData tEAGLEK3_FeildData;
    EAGLEK3_Param tEAGLEK3_Params;
    EAGLEK3_Data tEAGLEK3_Data;
    alCOMMONK_CommonCfg tCommonCfg = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 };
    alAVM2D_Params tAVM2D_Params = { 0 };

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Set_Bird-View_Fisheye Model (Test_SET_BV_FM will malloc for apucFMBuffer >> need to free)
    Test_SET_BV_FM(awcConfigFilePath, atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

    // Test DeFishEye Image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, 1.0, atFM_v2_Model);

    // set Common Cfg
    COMMONK_LoadDefault(&tCommonCfg);
    COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

    // set AVM2D Cfg, params
    alAVM2D_LoadDefault(&tAVM2D_Cfg);
    alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);
    alAVM2D_InitialByConfigData(&tAVM2D_Cfg, &tCommonCfg, &tAVM2D_Params);

    // Initialize for EagleK3 (Test_SET_EAGLEK3_PARAMS will malloc working buffer >> need to free)
    Test_SET_EAGLEK3_PARAMS(
        a_pwcEagleKWorkingFolder, a_pwcConfigFileName,
        atFM_v2_Model, &tCommonCfg, &tAVM2D_Cfg, &tAVM2D_Params,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params,
        &tEAGLEK3_Data, &tEAGLEK3_FeildData,
        &ulEagleK3BufferSize, &pucEagleK3WorkingBuffer
        );

    // Do ManualK
    Test_ManualK(
        apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data
    );

#if 1
    {   // GEN AV LUT
        alALLEYVIEW_Cfg tSAV_Cfg, tFAV_Cfg;
        alAlleyViewParams atSAVParam[2] = { 0 }, atFAVParam[2] = { 0 };

        // Init LUT buffer
        ulAV_BufferSize = alALLEYVIEW_QurryLUTSize();
        // alALLEYVIEW_InitializeLUT(&tSAV_LUT, IMAGE_WIDTH, IMAGE_HEIGHT);
        // alALLEYVIEW_InitializeLUT(&tFAV_LUT, IMAGE_WIDTH, IMAGE_HEIGHT);
        tSAV_LUT.lut_data = (UINT32 *)malloc(ulAV_BufferSize);
        tFAV_LUT.lut_data = (UINT32 *)malloc(ulAV_BufferSize);
        pucAV_WorkingBuffer = (UINT8 *)malloc(ulAV_BufferSize);
        
        // Load Default 
        alALLEYVIEW_LoadDefault(&tSAV_Cfg, &tFAV_Cfg);

        // Load conifg data from INI file
        alALLEYVIEW_CfgImportByINI(&tSAV_Cfg, &tFAV_Cfg, awcConfigFilePath);
        
        // Init By Cfg
        alALLEYVIEW_InitialByCfg(
            &tSAV_Cfg,
            &tEAGLEK3_Data.atCameraExtrinsicParams[EAGLEK3_BV_FRONT],
            &tEAGLEK3_Data.atCalibrationParams[EAGLEK3_BV_FRONT],
            &atFM_v2_Model[EAGLEK3_BV_FRONT],
            atSAVParam
        );
        alALLEYVIEW_InitialByCfg(
            &tFAV_Cfg,
            &tEAGLEK3_Data.atCameraExtrinsicParams[EAGLEK3_BV_FRONT],
            &tEAGLEK3_Data.atCalibrationParams[EAGLEK3_BV_FRONT],
            &atFM_v2_Model[EAGLEK3_BV_FRONT],
            atFAVParam
        );
        
        
#if 1 // Gen LUT
        UINT8 *pucMask = NULL, *pucFullMask = NULL;
        INT32 lMaskSize = 0, lFullMaskSIze = 0;
        lMaskSize = alALLEYVIEW_GetMaskSize(&tSAV_Cfg);
        lFullMaskSIze = alALLEYVIEW_GetMaskSize(&tFAV_Cfg);
#if AV_PRE_GEN_MASK
         pucMask = (UINT8*)malloc(lMaskSize * sizeof(UINT8));
         memset(pucMask, 0, lMaskSize);
         alALLEYVIEW_GenMask(&tSAV_Cfg, pucMask);
         Test_AV_Mask(&tSAV_Cfg, pucMask);

         pucFullMask = (UINT8*)malloc(lFullMaskSIze * sizeof(UINT8));
         memset(pucFullMask, 0, lFullMaskSIze);
         alALLEYVIEW_GenMask(&tFAV_Cfg, pucFullMask);
         Test_AV_Mask(&tFAV_Cfg, pucFullMask);
#endif

#if 1 // Gen LUT
       alALLEYVIEW_GenerateLUT(
            pucAV_WorkingBuffer,
            &tSAV_Cfg,
            atSAVParam,
            tCommonCfg.tDisplayAreaSize.lX,
            pucMask,
            &tSAV_LUT
        );

        alALLEYVIEW_GenerateLUT(
            pucAV_WorkingBuffer,
            &tFAV_Cfg,
            atFAVParam,
            tCommonCfg.tDisplayAreaSize.lX,
            pucFullMask,
            &tFAV_LUT
            );
#endif

#if AV_PRE_GEN_MASK
        free(pucMask);
        free(pucFullMask);
#endif

#endif

#if 1   // Save LUT
        wchar_t awcFilePath[MAX_PATH];
        UINT8 *pucData = NULL;
        INT32 lSize = 0;
        if (tSAV_Cfg.ucFunctionEnabled == 1)
        {
            // AV LUT File (Set)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_AVLUT_set.hex");
            lSize = sizeof(alPartLUT_v1_LUTSet_t);
            pucData = (UINT8*)(&tSAV_LUT);
            Test_Memory2FileW(awcFilePath, pucData, lSize);

            // AV LUT File (Data)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_AVLUT_data.hex");
            lSize = tSAV_LUT.lut_data_size*sizeof(UINT32);
            pucData = (UINT8*)(tSAV_LUT.lut_data);
            Test_Memory2FileW(awcFilePath, pucData, lSize);
        }

        pucData = NULL;
        lSize = 0;
        if (tFAV_Cfg.ucFunctionEnabled == 1)
        {
            // FAV LUT File (Set)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_FAVLUT_set.hex");
            lSize = sizeof(alPartLUT_v1_LUTSet_t);
            pucData = (UINT8*)(&tFAV_LUT);
            Test_Memory2FileW(awcFilePath, pucData, lSize);

            // FAV LUT File (Data)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_FAVLUT_data.hex");
            lSize = tFAV_LUT.lut_data_size*sizeof(UINT32);
            pucData = (UINT8*)(tFAV_LUT.lut_data);
            Test_Memory2FileW(awcFilePath, pucData, lSize);
        }
#endif
        // free AV Buffer
        free(pucAV_WorkingBuffer);

        // Free LUT buffer
        alALLEYVIEW_FreeLUT(&tSAV_LUT);
        alALLEYVIEW_FreeLUT(&tFAV_LUT);
    }
#endif

#if 1
    Test_AV_Generate(
        a_pwcEagleKWorkingFolder,
        a_pwcConfigFileName,
        a_pwcSrcImageFolder,
        a_pwcOutImageFolder,
        apucSrcImage
    );
#endif

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

}