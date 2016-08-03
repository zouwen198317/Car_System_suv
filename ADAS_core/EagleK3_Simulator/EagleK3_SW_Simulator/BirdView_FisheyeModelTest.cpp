
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>
// #include <assert.h>

#include "alLUT_v2.h"

#include "basedef.h"
#include "EagleK3_SimulateMain.h"


#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif


static void Test_GetYChannel(INT32 a_lWidth, INT32 a_lHeight, UINT8 *a_pucSrcBuffer, UINT8 *a_pucYBuffer);

static void Test_GetYChannel(
    INT32 a_lWidth,
    INT32 a_lHeight,
    UINT8 *a_pucSrcBuffer,
    UINT8 *a_pucYBuffer
    )
{
    INT32 i = 0, j = 0;

    for (i = 0; i < a_lWidth*a_lHeight; i++)
    {
        a_pucYBuffer[i] = a_pucSrcBuffer[i << 1];
    }
}


void TEST_ExportUndistortedImage(wchar_t * a_pwcSrcImageFolder, wchar_t * a_pwcOutImageFolder, FLOAT32 a_fScale, alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL])
{
#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1

    char acSrcImageFolder[MAX_PATH];
    char acOutputImageFolder[MAX_PATH];
    char acFilePath_SrcImage[EAGLEK3_NUM_BV_CHANNEL][MAX_PATH];
    char acFilePath_OutImage[EAGLEK3_NUM_BV_CHANNEL][MAX_PATH];
    UINT8 ucCamIndx = 0;

    IplImage* ptSrcImg = 0;
    IplImage* ptDstImg = 0;

    INT32 lX, lY, lUndistX, lUnDistY, lDistX, lDistY;
    FLOAT64 eDistX, eDistY, eUnDistX, eUnDistY;

    INT32 lWidth = 0, lHeight = 0;

    lWidth = a_atFM_v2_Model[0].uwDestWidth;
    lHeight = a_atFM_v2_Model[0].uwDestHeight;

    wprintf(L"\nGenerate test images for FMv2.\n\n");

    setlocale(LC_ALL, "cht");

    wcstombs(acSrcImageFolder, a_pwcSrcImageFolder, MAX_PATH);

    sprintf(acFilePath_SrcImage[EAGLEK3_BV_LEFT], "%sSource_0.bmp", acSrcImageFolder);
    sprintf(acFilePath_SrcImage[EAGLEK3_BV_RIGHT], "%sSource_1.bmp", acSrcImageFolder);
    sprintf(acFilePath_SrcImage[EAGLEK3_BV_FRONT], "%sSource_2.bmp", acSrcImageFolder);
    sprintf(acFilePath_SrcImage[EAGLEK3_BV_BACK], "%sSource_3.bmp", acSrcImageFolder);

    wcstombs(acOutputImageFolder, a_pwcOutImageFolder, MAX_PATH);

    sprintf(acFilePath_OutImage[EAGLEK3_BV_LEFT], "%sUndistorted_Left.bmp", acOutputImageFolder);
    sprintf(acFilePath_OutImage[EAGLEK3_BV_RIGHT], "%sUndistorted_Right.bmp", acOutputImageFolder);
    sprintf(acFilePath_OutImage[EAGLEK3_BV_FRONT], "%sUndistorted_Front.bmp", acOutputImageFolder);
    sprintf(acFilePath_OutImage[EAGLEK3_BV_BACK], "%sUndistorted_Back.bmp", acOutputImageFolder);

    for (ucCamIndx = 0; ucCamIndx < EAGLEK3_NUM_BV_CHANNEL; ucCamIndx++)
    {
        ptSrcImg = cvLoadImage(acFilePath_SrcImage[ucCamIndx], CV_LOAD_IMAGE_COLOR);
		ptDstImg = cvCreateImage(cvSize(a_atFM_v2_Model[ucCamIndx].uwDestWidth, a_atFM_v2_Model[ucCamIndx].uwDestHeight), 8, 3);

        cvZero(ptDstImg);

        for (lY = 0; lY < lHeight ; lY++)
        {
            for (lX = 0; lX < lWidth ; lX++)
            {
                if (lX == 40 && lY == 40 && ucCamIndx == 0)
                {
                    ucCamIndx = ucCamIndx;
                }
                eUnDistX = 0 + alROUND((lX - (lWidth >> 1)) / a_fScale + (lWidth >> 1));
                eUnDistY = 0 + alROUND((lY - (lHeight >> 1)) / a_fScale + (lHeight >> 1));

                lUndistX = 0 + lX;
                lUnDistY = 0 + lY;
                alFM_v2_1_Undistorted2Distorted_PlanarPixel(&(a_atFM_v2_Model[ucCamIndx]), eUnDistX, eUnDistY, &eDistX, &eDistY);
                lDistX = alROUND(eDistX);
                lDistY = alROUND(eDistY);

                if (lDistX >= 0 && lDistX < ptSrcImg->width && lDistY >= 0 && lDistY < ptSrcImg->height)
                {
                    memcpy(ptDstImg->imageData + (lUndistX * 3) + lUnDistY * ptDstImg->widthStep,
                        ptSrcImg->imageData + (lDistX * 3) + lDistY * ptSrcImg->widthStep,
                        3);
                }
            }
        }

        cvSaveImage(acFilePath_OutImage[ucCamIndx], ptDstImg, 0);
        cvReleaseImage(&ptSrcImg);
		cvReleaseImage(&ptDstImg);
        ptSrcImg = 0;
    }

    

    setlocale(LC_ALL, "C");

#endif
}


void Test_SET_BV_FM(
    wchar_t a_awcConfigFilePath[MAX_PATH],
    alFM_v2_1_ModelCfg a_atFM_BV[EAGLEK3_NUM_BV_CHANNEL],
    UINT32 a_aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL],
    UINT8 *a_apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL],
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL]
    )
{
    // Load Default
    EAGLEK3_LoadFM_BV_CfgByDefault(EAGLEK3_NUM_BV_CHANNEL, a_atFM_BV);

    // Load conifg data from INI file
    EAGLEK3_LoadFM_BV_CfgByINI(a_awcConfigFilePath, EAGLEK3_NUM_BV_CHANNEL, a_atFM_BV);

    // Query FM BV Working Buffer Size For Each FM
    EAGLEK3_QueryFM_BV_WorkingBufferSizeForEachFM(a_atFM_BV, a_aulFMBufferSize);

    // alloc FM  Buffer (必須在之後被free掉)
    a_apucFMBuffer[EAGLEK3_BV_LEFT] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_LEFT] * sizeof(UINT8));
    a_apucFMBuffer[EAGLEK3_BV_RIGHT] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_RIGHT] * sizeof(UINT8));
    a_apucFMBuffer[EAGLEK3_BV_FRONT] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_FRONT] * sizeof(UINT8));
    a_apucFMBuffer[EAGLEK3_BV_BACK] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_BACK] * sizeof(UINT8));

    // Initial By Cfg Data
    EAGLEK3_InitialBV_FM_ByCfg(a_atFM_BV, a_atFM_v2_Model, a_apucFMBuffer);
}

void Test_SET_BV_FM_Default(
    alFM_v2_1_ModelCfg a_atFM_BV[EAGLEK3_NUM_BV_CHANNEL],
    UINT32 a_aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL],
    UINT8 *a_apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL],
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL]
    )
{
    // Load Default
    EAGLEK3_LoadFM_BV_CfgByDefault(EAGLEK3_NUM_BV_CHANNEL, a_atFM_BV);

    // Query FM BV Working Buffer Size For Each FM
    EAGLEK3_QueryFM_BV_WorkingBufferSizeForEachFM(a_atFM_BV, a_aulFMBufferSize);

    // alloc FM  Buffer (必須在之後被free掉)
    a_apucFMBuffer[EAGLEK3_BV_LEFT] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_LEFT] * sizeof(UINT8));
    a_apucFMBuffer[EAGLEK3_BV_RIGHT] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_RIGHT] * sizeof(UINT8));
    a_apucFMBuffer[EAGLEK3_BV_FRONT] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_FRONT] * sizeof(UINT8));
    a_apucFMBuffer[EAGLEK3_BV_BACK] = (UINT8*)malloc(a_aulFMBufferSize[EAGLEK3_BV_BACK] * sizeof(UINT8));

    // Initial By Cfg Data
    EAGLEK3_InitialBV_FM_ByCfg(a_atFM_BV, a_atFM_v2_Model, a_apucFMBuffer);
}


void Test_BV_FM(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder
    )
{
    std::wstring sOutputImgeFile;
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

    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL];
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL];
    wchar_t awcConfigFilePath[MAX_PATH] = {0};
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = {0};
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 };

    // ▼ ================== Generate Config Files & Calibration Images ================== ▼

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);


    // Test_SET_BV_FM (Test_SET_BV_FM will malloc for apucFMBuffer >> need to free)
    Test_SET_BV_FM(awcConfigFilePath, atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

    // generate undistorted image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, 1.0, atFM_v2_Model);

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

void Test_SBV_GeneratingAllView(
    wchar_t * a_pwcOutImageFolder,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data,
    UINT8 *a_apucSrcImage[4]
    )
{
    std::wstring sOutputImgeFile;
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];

    // Gen Single-BV Image - left
    memset(pucDestBuffer, 0, IMAGE_WIDTH*IMAGE_HEIGHT * 2);

#if 1 // test
    COMMONK_UndistortedImageGenerate_YUYV_FULL(
        a_apucSrcImage[0], 720, 480,
        pucDestBuffer, 720, 480,
        a_ptEAGLEK3_Params->tMANUALK_Params.a_aptFM_v2_Model[0]
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"Undisdorted_LEFT_YUV.raw");
    std::ofstream ofile_UndisL(sOutputImgeFile.c_str(), std::ios::binary);
    ofile_UndisL.write((char*)pucDestBuffer, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ofile_UndisL.close();
#endif

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_LEFT, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[0],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV_LEFT_YUV.raw");
    std::ofstream ofile_SBVL(sOutputImgeFile.c_str(), std::ios::binary);
    ofile_SBVL.write((char*)pucDestBuffer, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ofile_SBVL.close();

    // Gen Single-BV Image - right
    memset(pucDestBuffer, 0, IMAGE_WIDTH*IMAGE_HEIGHT * 2);

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_RIGHT, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[1],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV_RIGHT_YUV.raw");
    std::ofstream ofile_SBVR(sOutputImgeFile.c_str(), std::ios::binary);
    ofile_SBVR.write((char*)pucDestBuffer, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ofile_SBVR.close();

    // Gen Single-BV Image - front
    memset(pucDestBuffer, 0, IMAGE_WIDTH*IMAGE_HEIGHT * 2);

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_FRONT, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[2],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV_FRONT_YUV.raw");
    std::ofstream ofile_SBVF(sOutputImgeFile.c_str(), std::ios::binary);
    ofile_SBVF.write((char*)pucDestBuffer, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ofile_SBVF.close();

    // Gen Single-BV Image - back
    memset(pucDestBuffer, 0, IMAGE_WIDTH*IMAGE_HEIGHT * 2);

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_BACK, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[3],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV_BACK_YUV.raw");
    std::ofstream ofile_SBVB(sOutputImgeFile.c_str(), std::ios::binary);
    ofile_SBVB.write((char*)pucDestBuffer, IMAGE_WIDTH*IMAGE_HEIGHT * 2);
    ofile_SBVB.close();

    delete[] pucDestBuffer;
}


void Test_SET_EAGLEK3_PARAMS(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL],
    alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data,
    EAGLEK3_FieldData *a_ptEAGLEK3_FeildData,
    UINT32 *a_pulEagleK3BufferSize,
    UINT8 **a_pucEagleK3WorkingBuffer
    )
{
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    


    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // Initialize for EagleK3
    wcscpy_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_ManualK, MAX_PATH, L"CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_AutoK, MAX_PATH, L"FACAUTOK_CalSettingFile.ini");

    wcscpy_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcFeildDataINIFilePath_FineTune, MAX_PATH, L"CalSettingFineTune_MV_MC.ini");

    // Load Default 
    EAGLEK3_LoadDefault(a_ptEAGLEK3_Cfg);

    // Load conifg data from INI file
    EAGLEK3_LoadUserCfgByINI(awcConfigFilePath, a_ptEAGLEK3_Cfg);

    // Load feild data from Default setting
    EAGLEK3_LoadFieldDataByDefault(a_ptEAGLEK3_FeildData);

    // Load feild data from INI file
    EAGLEK3_LoadFieldDataByINI(
        awcFeildDataINIFilePath_ManualK,
        awcFeildDataINIFilePath_AutoK,
        awcFeildDataINIFilePath_FineTune,
        a_ptEAGLEK3_FeildData
        );

    // Initial By Cfg Data
    *a_pulEagleK3BufferSize = EAGLEK3_QueryEagleK3_WorkingBufferSizeSingle(a_ptEAGLEK3_Cfg);
    *a_pucEagleK3WorkingBuffer = (UINT8*)malloc((*a_pulEagleK3BufferSize) * sizeof(UINT8));
    EAGLEK3_InitialByConfigData(
        a_atFM_v2_Model, a_ptCommonCfg, a_ptAVM2DCfg, a_ptAVM2DParams,
        a_ptEAGLEK3_FeildData, a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params,
        a_ptEAGLEK3_Data, *a_pucEagleK3WorkingBuffer
    );
}

void Test_SET_EAGLEK3_PARAMS_Default(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL],
    alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data,
    EAGLEK3_FieldData *a_ptEAGLEK3_FeildData,
    UINT32 *a_pulEagleK3BufferSize,
    UINT8 *a_pucEagleK3WorkingBuffer
    )
{
    // Load Default 
    EAGLEK3_LoadDefault(a_ptEAGLEK3_Cfg);

    // Load feild data from Default setting
    EAGLEK3_LoadFieldDataByDefault(a_ptEAGLEK3_FeildData);

    // Initial By Cfg Data
    *a_pulEagleK3BufferSize = EAGLEK3_QueryEagleK3_WorkingBufferSizeSingle(a_ptEAGLEK3_Cfg);
    a_pucEagleK3WorkingBuffer = (UINT8*)malloc((*a_pulEagleK3BufferSize) * sizeof(UINT8));
    EAGLEK3_InitialByConfigData(
        a_atFM_v2_Model, a_ptCommonCfg, a_ptAVM2DCfg, a_ptAVM2DParams,
        a_ptEAGLEK3_FeildData, a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, 
        a_ptEAGLEK3_Data, a_pucEagleK3WorkingBuffer
    );
}


void Test_SBV_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder
    )
{
    std::wstring sOutputImgeFile;

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
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0;

    EAGLEK3_Cfg tEAGLEK3_Cfg;
    EAGLEK3_FieldData tEAGLEK3_FeildData;
    EAGLEK3_Param tEAGLEK3_Params;
    EAGLEK3_Data tEAGLEK3_Data;
    alCOMMONK_CommonCfg tCommonCfg = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 };
    alAVM2D_Params tAVM2D_Params = { 0 };

    // ▼ ================== Generate Config Files & Calibration Images ================== ▼
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
   
    // TEST SBV
    Test_SBV_GeneratingAllView(a_pwcOutImageFolder, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data, apucSrcImage);

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

//// TEST ManualK ////
void Test_ManualK(
    UINT8 *a_apucSrcImage[4],
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data
    )
{
    FLOAT64 aeFPX[4] = { 0 };
    FLOAT64 aeFPY[4] = { 0 };
    FLOAT64 aeFPSBVX[4] = { 0 };
    FLOAT64 aeFPSBVY[4] = { 0 };
    // UINT8 *pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
	UINT8 *pucDestBuffer = NULL;
    std::wstring sOutputImgeFile;

	INT32 lSBV_W = 0, lSBV_H = 0;


    // Front
    aeFPX[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP1_X");
    aeFPX[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP2_X");
    aeFPX[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP3_X");
    aeFPX[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP4_X");
    aeFPY[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP1_Y");
    aeFPY[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP2_Y");
    aeFPY[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP3_Y");
    aeFPY[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"FRONT", L"FP4_Y");

    for (int i = 0; i < 4; i++)
    {
        EAGLEK3_SrcDistorted2SBV_ForManualK(
            EAGLEK3_BV_FRONT, a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
            aeFPX[i], aeFPY[i],
            &aeFPSBVX[i], &aeFPSBVY[i]
            );
    }

    EAGLEK3_ReGenerateM33_ForManualK(
        EAGLEK3_BV_FRONT,
        a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        aeFPSBVX, aeFPSBVY
        );

    // Gen Single-BV Image - front
	lSBV_W = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_FRONT].tSBV_Setting.lImageWidth;
	lSBV_H = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_FRONT].tSBV_Setting.lImageHeight;
	pucDestBuffer = new UINT8[lSBV_W*lSBV_H * 2];
	memset(pucDestBuffer, 0, lSBV_W*lSBV_H * 2);

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_FRONT, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[EAGLEK3_BV_FRONT],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV2_FRONT_YUV.raw");
    std::ofstream ofile_SBVF(sOutputImgeFile.c_str(), std::ios::binary);
	ofile_SBVF.write((char*)pucDestBuffer, lSBV_W*lSBV_H * 2);
    ofile_SBVF.close();

	delete[] pucDestBuffer;

    // Back
    aeFPX[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP1_X");
    aeFPX[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP2_X");
    aeFPX[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP3_X");
    aeFPX[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP4_X");
    aeFPY[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP1_Y");
    aeFPY[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP2_Y");
    aeFPY[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP3_Y");
    aeFPY[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"BACK", L"FP4_Y");

    for (int i = 0; i < 4; i++)
    {
        EAGLEK3_SrcDistorted2SBV_ForManualK(
            EAGLEK3_BV_BACK, a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
            aeFPX[i], aeFPY[i],
            &aeFPSBVX[i], &aeFPSBVY[i]
            );
    }

    EAGLEK3_ReGenerateM33_ForManualK(
        EAGLEK3_BV_BACK,
        a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        aeFPSBVX, aeFPSBVY
        );

    // Gen Single-BV Image - back
	lSBV_W = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_BACK].tSBV_Setting.lImageWidth;
	lSBV_H = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_BACK].tSBV_Setting.lImageHeight;
	pucDestBuffer = new UINT8[lSBV_W*lSBV_H * 2];
	memset(pucDestBuffer, 0, lSBV_W*lSBV_H * 2);

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_BACK, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[EAGLEK3_BV_BACK],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV2_BACK_YUV.raw");
    std::ofstream ofile_SBVB(sOutputImgeFile.c_str(), std::ios::binary);
	ofile_SBVB.write((char*)pucDestBuffer, lSBV_W*lSBV_H * 2);
    ofile_SBVB.close();

	delete[] pucDestBuffer;

    // Left
    aeFPX[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP1_X");
    aeFPX[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP2_X");
    aeFPX[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP3_X");
    aeFPX[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP4_X");
    aeFPY[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP1_Y");
    aeFPY[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP2_Y");
    aeFPY[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP3_Y");
    aeFPY[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"LEFT", L"FP4_Y");

    for (int i = 0; i < 4; i++)
    {
        EAGLEK3_SrcDistorted2SBV_ForManualK(
            EAGLEK3_BV_LEFT, a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
            aeFPX[i], aeFPY[i],
            &aeFPSBVX[i], &aeFPSBVY[i]
            );
    }

    EAGLEK3_ReGenerateM33_ForManualK(
        EAGLEK3_BV_LEFT,
        a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        aeFPSBVX, aeFPSBVY
        );

    // Gen Single-BV Image - left
	lSBV_W = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_LEFT].tSBV_Setting.lImageWidth;
	lSBV_H = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_LEFT].tSBV_Setting.lImageHeight;
	pucDestBuffer = new UINT8[lSBV_W*lSBV_H * 2];
	memset(pucDestBuffer, 0, lSBV_W*lSBV_H * 2);

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_LEFT, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[EAGLEK3_BV_LEFT],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV2_LEFT_YUV.raw");
    std::ofstream ofile_SBVL(sOutputImgeFile.c_str(), std::ios::binary);
	ofile_SBVL.write((char*)pucDestBuffer, lSBV_W*lSBV_H * 2);
    ofile_SBVL.close();
	delete[] pucDestBuffer;

    // Right
    aeFPX[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP1_X");
    aeFPX[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP2_X");
    aeFPX[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP3_X");
    aeFPX[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP4_X");
    aeFPY[0] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP1_Y");
    aeFPY[1] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP2_Y");
    aeFPY[2] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP3_Y");
    aeFPY[3] = alINI_GetKeyValue_FLOAT64W(a_pwcFPFileName, L"RIGHT", L"FP4_Y");

    for (int i = 0; i < 4; i++)
    {
        EAGLEK3_SrcDistorted2SBV_ForManualK(
            EAGLEK3_BV_RIGHT, a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
            aeFPX[i], aeFPY[i],
            &aeFPSBVX[i], &aeFPSBVY[i]
            );
    }

    EAGLEK3_ReGenerateM33_ForManualK(
        EAGLEK3_BV_RIGHT,
        a_ptEAGLEK3_Cfg, a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        aeFPSBVX, aeFPSBVY
        );

    // Gen Single-BV Image - right
	lSBV_W = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_LEFT].tSBV_Setting.lImageWidth;
	lSBV_H = a_ptEAGLEK3_Cfg->atMANUALK_Cfg[EAGLEK3_BV_LEFT].tSBV_Setting.lImageHeight;
	pucDestBuffer = new UINT8[lSBV_W*lSBV_H * 2];
	memset(pucDestBuffer, 0, lSBV_W*lSBV_H * 2);

#if 1 // for debug
    FLOAT64 eX = 0, eY = 0;
    FLOAT64 eBVX = 0, eBVY = 0;
    FLOAT64 eSBVX = 0, eSBVY = 0;
#endif

    EAGLEK3_SingleViewForManualCalibration(
        EAGLEK3_BV_RIGHT, a_ptEAGLEK3_Cfg,
        a_ptEAGLEK3_Params, a_ptEAGLEK3_Data,
        a_apucSrcImage[EAGLEK3_BV_RIGHT],
        pucDestBuffer
        );

    sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"SBV2_RIGHT_YUV.raw");
    std::ofstream ofile_SBVR(sOutputImgeFile.c_str(), std::ios::binary);
	ofile_SBVR.write((char*)pucDestBuffer, lSBV_W*lSBV_H * 2);
    ofile_SBVR.close();

    delete[] pucDestBuffer;

}
//// TEST ManualK ////

void Test_ManualK_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;

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
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0;

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

    // TEST SBV
    Test_SBV_GeneratingAllView(a_pwcOutImageFolder, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data, apucSrcImage);

    // TEST ManualK
    Test_ManualK(apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data);


#if 1 // for memory ldebug 
    FILE *pFileM33 = NULL;

    pFileM33 = fopen("AVM2D_Params.hex", "wb");
    fwrite(&tAVM2D_Params, sizeof(alAVM2D_Params), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("ExtrinsicParams.hex", "wb");
    fwrite(tEAGLEK3_Cfg.atCameraExtrinsicParams, sizeof(alCAMERAINFO_ExtrinsicParams), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("CalibrationParams.hex", "wb");
    fwrite(tEAGLEK3_Cfg.atCalibrationParams, sizeof(alCOMMONK_CalibrationParams), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("CommonK.hex", "wb");
    fwrite(&tCommonCfg, sizeof(alCOMMONK_CommonCfg), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("M33_L.hex", "wb");
    fwrite(&tEAGLEK3_Data.atCalibrationParams[0].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[0].aeHomographyMatrix), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("M33_R.hex", "wb");
    fwrite(&tEAGLEK3_Data.atCalibrationParams[1].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[1].aeHomographyMatrix), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("M33_F.hex", "wb");
    fwrite(&tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("M33_B.hex", "wb");
    fwrite(&tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix), 1, pFileM33);
    fclose(pFileM33);

    FLOAT64         aeH_Matrix[2][9] = { 0 };
    pFileM33 = fopen("M33_L.hex", "rb");
    fread(aeH_Matrix, sizeof(aeH_Matrix), 1, pFileM33);
    fclose(pFileM33);

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


void Test_BV_FACTORY_AUTOKK_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;

    UINT8 * apucSrcImage[EAGLEK3_NUM_BV_CHANNEL];
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
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0, alAVM2D_LUT_Size = 0;

    EAGLEK3_Cfg tEAGLEK3_Cfg;
    EAGLEK3_FieldData tEAGLEK3_FeildData;
    EAGLEK3_Param tEAGLEK3_Params;
    EAGLEK3_Data tEAGLEK3_Data = {0};
    alCOMMONK_CommonCfg tCommonCfg = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 };
    alAVM2D_Params tAVM2D_Params = { 0 };
    UINT32 ulPASS_FLAG = 1;

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

#if 1 
    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Set_Bird-View_Fisheye Model (Test_SET_BV_FM will malloc for apucFMBuffer >> need to free)
    Test_SET_BV_FM(awcConfigFilePath, atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

    // Test DeFishEye Image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, 1.0, atFM_v2_Model);
#endif


#if 1
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

#endif

#if 1
    // TEST SBV
    Test_SBV_GeneratingAllView(a_pwcOutImageFolder, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data, apucSrcImage);

    // TEST ManualK
    Test_ManualK(
        apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data
    );


    ///// TEST BV FACTORY AUTOK /////
    EAGLEK3_SetPath(a_pwcEagleKWorkingFolder, a_pwcSrcImageFolder, a_pwcOutImageFolder);

#endif

#if alBVCAM_FACAUTOK_DEBUG // for test : Gen alAVM2D By M33 during AutoK
    alBVCAM_GetalAVM2DInfo(
        &tAVM2D_Params,
        &tAVM2D_Cfg
        );
#endif

    /** \brief Do the test for FatoryAutoK. */
    // input YUYV
#if 1
    ulPASS_FLAG =  EAGLEK3_FatoryAutoK(
        apucSrcImage[EAGLEK3_BV_FRONT],
        apucSrcImage[EAGLEK3_BV_BACK],
        apucSrcImage[EAGLEK3_BV_LEFT],
        apucSrcImage[EAGLEK3_BV_RIGHT],
        &tEAGLEK3_Cfg,
        &tEAGLEK3_Params,
        &tEAGLEK3_Data
    );
#endif

	// ulPASS_FLAG = 1; // for test

    if (!ulPASS_FLAG)
    {
        printf("AutoK Success ^____^\n");
        alLUT_v2_Def talAVM2D_LUT = { 0 };

        // Init LUT buffer
        alAVM2D_InitializeBuffer(&talAVM2D_LUT);

        // Qurry LUT data Size
        alAVM2D_LUT_Size = alAVM2D_QurryLUTSize(&tAVM2D_Cfg, &tAVM2D_Params);

        // malloc LUT memory and assign pointer
        talAVM2D_LUT.pullTable = (UINT64*)malloc(alAVM2D_LUT_Size);

        UINT8 *pucBVImage = NULL;

        alPointINT32 tImgSize = { 0 };

        tImgSize.lX = tAVM2D_Cfg.tDestImageBufferSize.lX;
        tImgSize.lY = tAVM2D_Cfg.tDestImageBufferSize.lY;

        pucBVImage = (UINT8*)malloc(tImgSize.lX * tImgSize.lY * 2);
        memset(pucBVImage, 0, tImgSize.lX * tImgSize.lY * 2);

        alAVM2D_GenerateLUT2DBirdView(
            &tAVM2D_Cfg,
            &tAVM2D_Params,
            atFM_v2_Model,
            tEAGLEK3_Data.atCalibrationParams[0].aeHomographyMatrix,
            tEAGLEK3_Data.atCalibrationParams[1].aeHomographyMatrix,
            tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix,
            tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix,
            &talAVM2D_LUT
            );

        alLUT_v2_ProcessFullLU(&talAVM2D_LUT, apucSrcImage, pucBVImage);

        FILE *pFileM33 = NULL;
        char acAVM2DPath[MAX_PATH] = { 0 };
        sprintf(acAVM2DPath, "%sAVM2D_Autok.raw", g_acalBVCAM_FACAUTOK_OutputFolder);
        printf("The AVM2D pic is [%s]\n", acAVM2DPath);
        pFileM33 = fopen(acAVM2DPath, "wb");
        fwrite(pucBVImage, tImgSize.lX * tImgSize.lY * 2, 1, pFileM33);
        fclose(pFileM33);

        free(pucBVImage);
        free(talAVM2D_LUT.pullTable);
    }
    else
    {
        printf("AutoK Fail Q_Q...\n");
    }


    ///// TEST BV FACTORY AUTOK /////

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

void Test_BV_FACTORY_AUTOKK_By_Default(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;

    UINT8 * apucSrcImage[EAGLEK3_NUM_BV_CHANNEL];
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
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0;

    EAGLEK3_Cfg tEAGLEK3_Cfg = {0};
    EAGLEK3_FieldData tEAGLEK3_FeildData = {0};
    EAGLEK3_Param tEAGLEK3_Params = {0};
    EAGLEK3_Data tEAGLEK3_Data = { 0 };
    alCOMMONK_CommonCfg tCommonCfg = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 };
    alAVM2D_Params tAVM2D_Params = { 0 };
    UINT32 ulPASS_FLAG = 0;

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Set_Bird-View_Fisheye Model (Test_SET_BV_FM will malloc for apucFMBuffer >> need to free)
    Test_SET_BV_FM_Default(atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

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
    Test_SET_EAGLEK3_PARAMS_Default(
        a_pwcEagleKWorkingFolder, a_pwcConfigFileName,
        atFM_v2_Model, &tCommonCfg, &tAVM2D_Cfg, &tAVM2D_Params,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params,
        &tEAGLEK3_Data, &tEAGLEK3_FeildData,
        &ulEagleK3BufferSize, pucEagleK3WorkingBuffer
    );

#if 1
    BVCAM_FACAUTOK_CFG TestCfg = {0};
    BVCAM_FACAUTOK_Parameter TestParams = {0};
    BVCAM_FACAUTOK_Data TestData = { 0 };
    FILE *pFileSrc = NULL;

    pFileSrc = fopen("AutoK_Cfg.hex", "rb");
    fread(&TestCfg, sizeof(BVCAM_FACAUTOK_CFG), 1, pFileSrc);
    fclose(pFileSrc);

    pFileSrc = fopen("AutoK_Params.hex", "rb");
    fread(&TestParams, sizeof(BVCAM_FACAUTOK_Parameter), 1, pFileSrc);
    fclose(pFileSrc);

    pFileSrc = fopen("AutoK_Data.hex", "rb");
    fread(&TestData, sizeof(BVCAM_FACAUTOK_Data), 1, pFileSrc);
    fclose(pFileSrc);

    int cmp[10] = { 0 }, lCnt = 0;
    for (lCnt = 0; lCnt < 4; lCnt++)
    {
        cmp[0] = memcmp(&tEAGLEK3_Cfg.tAutoK_Cfg.atRecKCfg[lCnt], &TestCfg.atRecKCfg[lCnt], sizeof(alRECK_Cfg));
        cmp[0] = memcmp(&tEAGLEK3_Cfg.tAutoK_Cfg.atCrossMarkKCfg[lCnt], &TestCfg.atCrossMarkKCfg[lCnt], sizeof(alCROSSMARKK_Cfg));
    }
    for (lCnt = 0; lCnt < 4; lCnt++)
    {
        cmp[1] = memcmp(tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].atIdealPointRectK, TestParams.atRecKParameter[lCnt].atIdealPointRectK, sizeof(alRECK_Point)*16);
        cmp[1] = memcmp(tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].aucPointFlag, TestParams.atRecKParameter[lCnt].aucPointFlag, sizeof(UINT8) * 16);
        cmp[1] = memcmp(tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].atRecKROI, TestParams.atRecKParameter[lCnt].atRecKROI, sizeof(alRectINT32) * 4);

        cmp[1] = memcmp(&tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].eMMPP, &TestParams.atRecKParameter[lCnt].eMMPP, sizeof(FLOAT64));
        cmp[1] = memcmp(&tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].lOriImgYLimit, &TestParams.atRecKParameter[lCnt].lOriImgYLimit, sizeof(INT32));
        cmp[1] = memcmp(&tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].lAngleCAM, &TestParams.atRecKParameter[lCnt].lAngleCAM, sizeof(INT32));
        cmp[1] = memcmp(&tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].lCamPosX, &TestParams.atRecKParameter[lCnt].lCamPosX, sizeof(INT32));
        cmp[1] = memcmp(&tEAGLEK3_Params.tAutoK_Params.atRecKParameter[lCnt].lCamPosY, &TestParams.atRecKParameter[lCnt].lCamPosY, sizeof(INT32));
    }
    cmp[0] = memcmp(&tEAGLEK3_Cfg.tAutoK_Cfg, &TestCfg, sizeof(BVCAM_FACAUTOK_CFG));
    cmp[1] = memcmp(&tEAGLEK3_Params.tAutoK_Params, &TestParams, sizeof(BVCAM_FACAUTOK_Parameter));
    cmp[2] = memcmp(&tEAGLEK3_Data.tBV_BV_FAC_AutoK_Data, &TestData, sizeof(BVCAM_FACAUTOK_Parameter));
#endif

#if 0 // for test & debug
    *pucEagleK3WorkingBufferTest = NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0;

    Test_SET_EAGLEK3_PARAMS(
        a_pwcEagleKWorkingFolder, a_pwcConfigFileName,
        atFM_v2_Model, &tEAGLEK3_Cfg, &tEAGLEK3_Params,
        &tEAGLEK3_Data, &tEAGLEK3_FeildData,
        &ulEagleK3BufferSize, pucEagleK3WorkingBuffer
        );
#endif

    // TEST ManualK
    Test_ManualK(
        apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data
        );

#if 1 // for test
    FILE *pFileM33 = NULL;
    pFileM33 = fopen("M33_B.hex", "wb");
    fwrite(&tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix), 1, pFileM33);
    fclose(pFileM33);
#endif

    // TEST SBV
    Test_SBV_GeneratingAllView(a_pwcOutImageFolder, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data, apucSrcImage);

    ///// TEST BV FACTORY AUTOK /////
    EAGLEK3_SetPath(a_pwcEagleKWorkingFolder, a_pwcSrcImageFolder, a_pwcOutImageFolder);

#if alBVCAM_FACAUTOK_DEBUG // for test : Gen alAVM2D By M33 during AutoK
    alBVCAM_GetalAVM2DInfo(
        &tAVM2D_Params,
        &tAVM2D_Cfg
        );
#endif

    /** \brief Do the test for FatoryAutoK. */
    // input YUYV
    ulPASS_FLAG = EAGLEK3_FatoryAutoK(
        apucSrcImage[EAGLEK3_BV_FRONT],
        apucSrcImage[EAGLEK3_BV_BACK],
        apucSrcImage[EAGLEK3_BV_LEFT],
        apucSrcImage[EAGLEK3_BV_RIGHT],
        &tEAGLEK3_Cfg,
        &tEAGLEK3_Params,
        &tEAGLEK3_Data
        );
    ///// TEST BV FACTORY AUTOK /////

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


void Test_Only_BV_ManualK_By_Default()
{
    FILE *pFileSrc = NULL, *pFileData = NULL;
    UINT8 * apucSrcImage[EAGLEK3_NUM_BV_CHANNEL];
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucAutoKWorkingBuffer = NULL;
    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL];
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL];
    alPointINT32    atBVFPOffsetFineTuned[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM_AUTOK] = { 0 };
    alCAMERAINFO_ExtrinsicParams atCameraExtrinsicParams[EAGLEK3_NUM_BV_CHANNEL];
    alCOMMONK_CalibrationParams atCalibrationParams[EAGLEK3_NUM_BV_CHANNEL];
    alMANUALK_CameraCfg          atMANUALK_Cfg[EAGLEK3_NUM_BV_CHANNEL];
    alMANUALK_Params tMANUALK_Params;
    alMANUALK_ChartCrossPointSet tManualKFieldData;
    alPointINT32 tAVM2D_DestImageBufferSize = {0};
    alAVM2D_Params talAVM2D_Params = { 0 };
    alCOMMONK_CommonCfg tCommonKCfg = { 0 };
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0;
    FLOAT64 aeOriginalM33Left[2][COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 aeOriginalM33Right[2][COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 aeOriginalM33Front[2][COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 aeOriginalM33Back[2][COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 aeFPX[4];
    FLOAT64 aeFPY[4];
    FLOAT64 aeFPSBVX[4];
    FLOAT64 aeFPSBVY[4];
    UINT8 * pucDestBuffer = NULL;
    UINT8 ucBVCameraIndx = 0;
    int lk = 0;
    FLOAT64 eUDX = 0, eUDY = 0, eBVX = 0, eBVY = 0, *peM33 = NULL;
    alFM_v2_1_Model *ptCameraFisheyeModel = NULL;
    FLOAT64 aeUDX[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeUDY[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeBVX[alMANUALK_CAMERA_FP_NUM] = { 0 }, aeBVY[alMANUALK_CAMERA_FP_NUM] = { 0 };
    INT32 lFlag = 0, lIndex = 0;

    apucSrcImage[0] = (UINT8*)malloc(IMAGE_WIDTH*IMAGE_HEIGHT * 2 * sizeof(UINT8));
    apucSrcImage[1] = (UINT8*)malloc(IMAGE_WIDTH*IMAGE_HEIGHT * 2 * sizeof(UINT8));
    apucSrcImage[2] = (UINT8*)malloc(IMAGE_WIDTH*IMAGE_HEIGHT * 2* sizeof(UINT8));
    apucSrcImage[3] = (UINT8*)malloc(IMAGE_WIDTH*IMAGE_HEIGHT * 2* sizeof(UINT8));
    pucDestBuffer = (UINT8*)malloc(IMAGE_WIDTH*IMAGE_HEIGHT * 2* sizeof(UINT8));

#if 1 // load pic
    pFileSrc = fopen("Source_2.raw", "rb");
    fread(apucSrcImage[2], IMAGE_WIDTH*IMAGE_HEIGHT * 2, 1, pFileSrc);
    fclose(pFileSrc);
#endif

#if 1 //    load data
    pFileData = fopen("AVM2D_Params.hex", "rb");
    fread(&talAVM2D_Params, sizeof(talAVM2D_Params), 1, pFileData);
    fclose(pFileData);

    pFileData = fopen("CalibrationParams.hex", "rb");
    fread(atCalibrationParams, sizeof(atCalibrationParams), 1, pFileData);
    fclose(pFileData);

    pFileData = fopen("ExtrinsicParams.hex", "rb");
    fread(atCameraExtrinsicParams, sizeof(atCameraExtrinsicParams), 1, pFileData);
    fclose(pFileData);

    pFileData = fopen("CommonK.hex", "rb");
    fread(&tCommonKCfg, sizeof(tCommonKCfg), 1, pFileData);
    fclose(pFileData);
#endif

#if 1 // set FM
    // Load Default
    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_190, &atFM_BV[EAGLEK3_BV_LEFT]);
    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_190, &atFM_BV[EAGLEK3_BV_RIGHT]);
    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_190, &atFM_BV[EAGLEK3_BV_FRONT]);
    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_144, &atFM_BV[EAGLEK3_BV_BACK]);

    // Load information of calibration field.
    aulFMBufferSize[EAGLEK3_BV_LEFT] = alFM_v2_1_QueryFM_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_LEFT]);
    aulFMBufferSize[EAGLEK3_BV_RIGHT] = alFM_v2_1_QueryFM_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_RIGHT]);
    aulFMBufferSize[EAGLEK3_BV_FRONT] = alFM_v2_1_QueryFM_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_FRONT]);
    aulFMBufferSize[EAGLEK3_BV_BACK] = alFM_v2_1_QueryFM_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_BACK]);

    // alloc FM  Buffer
#if 1
    apucFMBuffer[EAGLEK3_BV_LEFT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_LEFT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_RIGHT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_RIGHT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_FRONT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_FRONT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_BACK] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_BACK] * sizeof(UINT8));
#else
    apucFMBuffer[EAGLEK3_BV_LEFT] = (UINT8*)sharedMemAlloc(SHARED_FRAME_BUFFER_REGION_IDX, ROUNDUP_SIZE(aulFMBufferSize[EAGLEK3_BV_LEFT], 128));
    apucFMBuffer[EAGLEK3_BV_RIGHT] = (UINT8*)sharedMemAlloc(SHARED_FRAME_BUFFER_REGION_IDX, ROUNDUP_SIZE(aulFMBufferSize[EAGLEK3_BV_RIGHT], 128));
    apucFMBuffer[EAGLEK3_BV_FRONT] = (UINT8*)sharedMemAlloc(SHARED_FRAME_BUFFER_REGION_IDX, ROUNDUP_SIZE(aulFMBufferSize[EAGLEK3_BV_FRONT], 128));
    apucFMBuffer[EAGLEK3_BV_BACK] = (UINT8*)sharedMemAlloc(SHARED_FRAME_BUFFER_REGION_IDX, ROUNDUP_SIZE(aulFMBufferSize[EAGLEK3_BV_BACK], 128));
#endif
    // Initial By Cfg Data
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_LEFT], &atFM_v2_Model[EAGLEK3_BV_LEFT], apucFMBuffer[EAGLEK3_BV_LEFT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_RIGHT], &atFM_v2_Model[EAGLEK3_BV_RIGHT], apucFMBuffer[EAGLEK3_BV_RIGHT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_FRONT], &atFM_v2_Model[EAGLEK3_BV_FRONT], apucFMBuffer[EAGLEK3_BV_FRONT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_BACK], &atFM_v2_Model[EAGLEK3_BV_BACK], apucFMBuffer[EAGLEK3_BV_BACK]);
#endif


#if 1 // set ManualK
    // Default Setting for CamK Config 
    MANUALK_LoadDefault(atMANUALK_Cfg);

    // feild data for  MANUALK
    MANUALK_LoadFeildDataByDefault(&tManualKFieldData);

    tAVM2D_DestImageBufferSize.lX = 720;
    tAVM2D_DestImageBufferSize.lY = 480;

    // 初始化 Manual K 校正參數
    MANUALK_InitialByConfigData(
        atFM_v2_Model,
        atCameraExtrinsicParams,
        atCalibrationParams,
        atBVFPOffsetFineTuned,
        &tManualKFieldData,
        atMANUALK_Cfg,
        tAVM2D_DestImageBufferSize,
        talAVM2D_Params.fMMPP,
        &tCommonKCfg,
        &tMANUALK_Params
    );
#endif

    //// TEST ManualK ////
#if 1 // TEST ManualK
    {
        // Front
        ucBVCameraIndx = 2;
        aeFPX[0] = 174;
        aeFPX[1] = 565;
        aeFPX[2] = 237;
        aeFPX[3] = 498;
        aeFPY[0] = 321;
        aeFPY[1] = 322;
        aeFPY[2] = 258;
        aeFPY[3] = 256;

        for (lk = 0; lk < 4; lk++)
        {
            /*EAGLEK3_SrcDistorted2SBV_ForManualK(
                EAGLEK3_BV_FRONT, &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data,
                aeFPX[lk], aeFPY[lk],
                &aeFPSBVX[lk], &aeFPSBVY[lk]
                );    */

            ptCameraFisheyeModel = tMANUALK_Params.a_aptFM_v2_Model[ucBVCameraIndx];
            peM33 = atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[1];

            alFM_v2_1_Distorted2Undistorted_PlanarPixel(ptCameraFisheyeModel, aeFPX[lk], aeFPY[lk], &eUDX, &eUDY);

            COMMONK_PerformCoordinatesTransform(peM33, eUDX, eUDY, &eBVX, &eBVY);

            COMMONK_Birdview2SBV(
                tAVM2D_DestImageBufferSize.lX, tAVM2D_DestImageBufferSize.lY,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lImageHeight,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lImageWidth,
                1,
                tMANUALK_Params.alCamAngle[ucBVCameraIndx],
                atCameraExtrinsicParams[ucBVCameraIndx].lCameraPosX,
                atCameraExtrinsicParams[ucBVCameraIndx].lCameraPosY,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lDisplayOffset_X,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lDisplayOffset_Y,
                (FLOAT64)atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.fScaleFactor,
                (FLOAT64)tMANUALK_Params.fMMPP,
                &eBVX, &eBVY, &aeFPSBVX[lk], &aeFPSBVY[lk]
                );
        }

       /* EAGLEK3_ReGenerateM33_ForManualK(
            EAGLEK3_BV_FRONT,
            &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data,
            aeFPSBVX, aeFPSBVY
            );*/
        {
            

            peM33 = atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[0];

            COMMONK_SBV2Birdview(
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lImageHeight,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lImageWidth,
                tAVM2D_DestImageBufferSize.lX, tAVM2D_DestImageBufferSize.lY,
                alMANUALK_CAMERA_FP_NUM,
                tMANUALK_Params.alCamAngle[ucBVCameraIndx],
                atCameraExtrinsicParams[ucBVCameraIndx].lCameraPosX,
                atCameraExtrinsicParams[ucBVCameraIndx].lCameraPosY,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lDisplayOffset_X,
                atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lDisplayOffset_Y,
                (FLOAT64)atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.fScaleFactor,
                (FLOAT64)tMANUALK_Params.fMMPP,
                aeFPSBVX, aeFPSBVY, aeBVX, aeBVY
                );

            for (lIndex = 0; lIndex < alMANUALK_CAMERA_FP_NUM; lIndex++)
            {
                COMMONK_PerformCoordinatesTransform(peM33, aeBVX[lIndex], aeBVY[lIndex], &aeUDX[lIndex], &aeUDY[lIndex]);
            }

            // generate M33
            lFlag = COMMONK_GenerateM3x3(
                aeUDX, aeUDY,
                tMANUALK_Params.aeBVIdealFP_X[ucBVCameraIndx],
                tMANUALK_Params.aeBVIdealFP_Y[ucBVCameraIndx],
                alMANUALK_CAMERA_FP_NUM,
                aeOriginalM33Front[0] // atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[0]
                );

            if (!lFlag)
            {
                assert(0);
            }
#if 0
            memcpy(atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[1], atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[0], sizeof(FLOAT64) * 9);
            alMATRIX_InverseNbyN(atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[1], 3);
#else
            memcpy(aeOriginalM33Front[1], aeOriginalM33Front[0], sizeof(FLOAT64) * 9);
            alMATRIX_InverseNbyN(aeOriginalM33Front[1], 3);
#endif
        }

        // Gen Single-BV Image - front
        memset(pucDestBuffer, 0, IMAGE_WIDTH*IMAGE_HEIGHT * 2);

        COMMONK_SBVGenerate_YUYV_FULL(
            apucSrcImage[ucBVCameraIndx], 720, 480,
            pucDestBuffer, 720, 480,
            aeOriginalM33Front[0], //atCalibrationParams[ucBVCameraIndx].aeHomographyMatrix[0],
            tMANUALK_Params.alOriImgYLimit[ucBVCameraIndx],
            tMANUALK_Params.alCamAngle[ucBVCameraIndx],
            atCameraExtrinsicParams[ucBVCameraIndx].lCameraPosX,
            atCameraExtrinsicParams[ucBVCameraIndx].lCameraPosY,
            atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lDisplayOffset_X,
            atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.lDisplayOffset_Y,
            atMANUALK_Cfg[ucBVCameraIndx].tSBV_Setting.fScaleFactor,
            tMANUALK_Params.fMMPP,
            tMANUALK_Params.a_aptFM_v2_Model[ucBVCameraIndx]
            );

        pFileSrc = fopen("SBV2_Front.raw", "wb");
        fwrite(pucDestBuffer, IMAGE_WIDTH*IMAGE_HEIGHT*2, 1, pFileSrc);
        fclose(pFileSrc);
    }
#endif
    //// TEST ManualK ////

    // free Y buffer
    for (lk = 0; lk < 4; lk++)
    {
        free(apucSrcImage[lk]);
    }

    free(pucDestBuffer);
    
    // free FM Buffer
    free(apucFMBuffer[EAGLEK3_BV_LEFT]);
    free(apucFMBuffer[EAGLEK3_BV_RIGHT]);
    free(apucFMBuffer[EAGLEK3_BV_FRONT]);
    free(apucFMBuffer[EAGLEK3_BV_BACK]);
}