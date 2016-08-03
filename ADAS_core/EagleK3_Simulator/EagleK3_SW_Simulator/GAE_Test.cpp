
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>

#include "alLUT_v2.h"
#include "basedef.h"
#include "EagleK3_SimulateMain.h"

#include "alStatistic_BirdView.h"
#include "alGAE_AVM.h"
#include <direct.h> //  for _mkdir

#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif


void Test_BufferYUV2RGB(unsigned char* src, unsigned char* dst, int width, int height)
{
    short Y0, Y1, U, V;
    short R, G, B;
    int i, j, count = 0;
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width * 2; i += 4)
        {
            Y0 = *(unsigned char*)(src + i + j*width * 2);
            U = *(unsigned char*)(src + i + j*width * 2 + 1) - 128;
            Y1 = *(unsigned char*)(src + i + j*width * 2 + 2);
            V = *(unsigned char*)(src + i + j*width * 2 + 3) - 128;
            R = (short)(Y0 - 0.00093*U + 1.401687*V);
            G = (short)(Y0 - 0.3437*U - 0.71417*V);
            B = (short)(Y0 + 1.77216*U - 0.00099*V);
            *(dst + count) = alMIN(255, alMAX(0, B));
            count++;
            *(dst + count) = alMIN(255, alMAX(0, G));
            count++;
            *(dst + count) = alMIN(255, alMAX(0, R));
            count++;
            R = (short)(Y1 - 0.00093*U + 1.401687*V);
            G = (short)(Y1 - 0.3437*U - 0.71417*V);
            B = (short)(Y1 + 1.77216*U - 0.00099*V);
            *(dst + count) = alMIN(255, alMAX(0, B));
            count++;
            *(dst + count) = alMIN(255, alMAX(0, G));
            count++;
            *(dst + count) = alMIN(255, alMAX(0, R));
            count++;
        }
    }
}


void Test_LogGAE_Data(IplImage *a_ptOutImg, alGAE_AVM_Data *a_ptData, INT32 a_lCnt, alSTATISTIC_Data *a_ptalSTATISTIC_Data)
{
    INT32 view_add[16] = {
        135, 135,
        135, 150,
        135, 165,
        135, 180,
        135, 195,
        135, 210,
        135, 225,
        135, 240
    };
    INT32 lcnt = 0;
    char actext[MAX_PATH];
    CvFont Font1 = cvFont(1, 1);
    cvPutText(a_ptOutImg, "Fixed by Ancre", cvPoint(430, 20), &Font1, CV_RGB(255, 255, 0));

    sprintf_s(actext, MAX_PATH, "Frame No. %d", a_lCnt);
    cvPutText(a_ptOutImg, actext, cvPoint(430, 40), &Font1, CV_RGB(255, 255, 0));

    sprintf_s(actext, MAX_PATH, "noise: %d %d %d %d", a_ptalSTATISTIC_Data->ucGlobalNoiseLevel, a_ptalSTATISTIC_Data->atSingleViewNoiseLevel[0].ucNoiseLevel, a_ptalSTATISTIC_Data->atSingleViewNoiseLevel[1].ucNoiseLevel, a_ptalSTATISTIC_Data->atSingleViewNoiseLevel[2].ucNoiseLevel);
    cvPutText(a_ptOutImg, actext, cvPoint(430, 60), &Font1, CV_RGB(255, 255, 0));

    sprintf_s(actext, MAX_PATH, "MAX : %d", a_ptData->lLimitView);
    cvPutText(a_ptOutImg, actext, cvPoint(430, 80), &Font1, CV_RGB(255, 255, 0));

    sprintf_s(actext, MAX_PATH, "MAX Frame: %d", a_ptData->lLimitFrame);
    cvPutText(a_ptOutImg, actext, cvPoint(430, 100), &Font1, CV_RGB(255, 255, 0));

    // 將view的 gap 畫上
    for (lcnt = 0; lcnt < 4; lcnt++)
    {
        sprintf_s(actext, MAX_PATH, "Gap%d: %d", lcnt, a_ptData->alGap[lcnt]);
        cvPutText(a_ptOutImg, actext, cvPoint(view_add[lcnt * 2]+284, view_add[lcnt * 2 + 1]), &Font1, CV_RGB(255, 255, 0));
    }

    // 將 view 的 obstacle flag 畫上
    for (lcnt = 0; lcnt < 4; lcnt++)
    {
        sprintf_s(actext, MAX_PATH, "obstacle%d: %d", lcnt, a_ptData->aucObstacle[lcnt]);
        cvPutText(a_ptOutImg, actext, cvPoint(view_add[lcnt * 2] + 400, view_add[lcnt * 2 + 1]), &Font1, CV_RGB(255, 255, 0));
    }


    // 將view的mean和compensation畫上
    for (lcnt = 0; lcnt<8; lcnt++){
        sprintf_s(actext, MAX_PATH, "v%d:%d", lcnt, a_ptData->aulMean[lcnt]);
        cvPutText(a_ptOutImg, actext, cvPoint(view_add[lcnt * 2], view_add[lcnt * 2 + 1]), &Font1, CV_RGB(255, 255, 0));
    }
    for (lcnt = 0; lcnt<4; lcnt++){
        sprintf_s(actext, MAX_PATH, "c%d:%d", lcnt, a_ptData->acOffset_Ymean_Firmware[lcnt]);
        cvPutText(a_ptOutImg, actext, cvPoint(view_add[lcnt * 2], view_add[lcnt * 2 + 1] + 120), &Font1, CV_RGB(255, 255, 0));
    }
}


void Test_GAE_By_Load_LUT(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring salAVM2DLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_set.hex");
    std::wstring salAVM2DLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_data.hex");
    std::wstring sOutputImgeFile;
    alLUT_v2_Def talAVM2D_LUT;
    alPartLUT_v2_Def  *ptalAVM2D_LUT_PART = NULL;

    alSTATISTIC_Data alSTATISTIC_Data = { 0 };
    alSTATISTIC_Cfg alSTATISTIC_Cfg = { 0 };

    UINT8 * pucBuffer = NULL;
    UINT8 * pucBuffer2 = NULL;
    UINT32 ulBufferLength = 0, ulBufferLength2 = 0;

    UINT8 **pucSrcImagePtr = NULL;
    UINT8 * apucSrcImage[4];
    UINT8 * pucSrcBufferFront = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRear = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferLeft = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRight = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucDestBuffer_1 = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];

    INT32 alSFPX[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 alSFPY[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };

    INT32 lCnt = 0;
    alGAE_AVM_Data tGAE_Data = {0};
    alCARINFO_Set    tCarInputInfo = {0};
    alAVM2D_Cfg tAVM2D_Cfg;
    alAVM2D_Params talAVM2DParam;
    alCOMMONK_CommonCfg tCommonCfg = { 0 };
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    char cText[MAX_PATH] = { 0 };
    IplImage *ptOutImg = NULL;

    
    apucSrcImage[0] = pucSrcBufferLeft;
    apucSrcImage[1] = pucSrcBufferRight;
    apucSrcImage[2] = pucSrcBufferFront;
    apucSrcImage[3] = pucSrcBufferRear;


    std::wstring sImageLeft = std::wstring(a_pwcSrcImageFolder).append(L"Source_0.raw");
    std::wstring sImageRight = std::wstring(a_pwcSrcImageFolder).append(L"Source_1.raw");
    std::wstring sImageFront = std::wstring(a_pwcSrcImageFolder).append(L"Source_2.raw");
    std::wstring sImageRear = std::wstring(a_pwcSrcImageFolder).append(L"Source_3.raw");

    // read image
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

    // Initialize for alAVM2D
    {
        wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
        wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

        // 檢查檔案是否存在
        struct _stat64i32 tFileStat;
        assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

        // Load Default 
        alAVM2D_LoadDefault(&tAVM2D_Cfg);

        // Load conifg data from INI file
        alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);

        // set Common Cfg
        COMMONK_LoadDefault(&tCommonCfg);
        COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

        // Init By Cfg
        alAVM2D_InitialByConfigData(&tAVM2D_Cfg, &tCommonCfg, &talAVM2DParam);
    }

#if 1   // Save file for porting test
    FILE *pFileM33 = NULL;
   
    pFileM33 = fopen("AVM2D_Cfg.hex", "wb");
    fwrite(&tAVM2D_Cfg, sizeof(tAVM2D_Cfg), 1, pFileM33);
    fclose(pFileM33);

    pFileM33 = fopen("AVM2D_Params.hex", "wb");
    fwrite(&talAVM2DParam, sizeof(talAVM2DParam), 1, pFileM33);
    fclose(pFileM33);
#endif

#if 1 
    // Import AVM 2D (BV) LUT Set
    if (Test_ImportOtherHexFiles(salAVM2DLUTSetFilePath.c_str(), &pucBuffer, &ulBufferLength))
    {
        if (!Test_ImportOtherHexFiles(salAVM2DLUTDataFilePath.c_str(), &pucBuffer2, &ulBufferLength2)) assert(0);

        memcpy(&talAVM2D_LUT, pucBuffer, sizeof(alLUT_v2_Def));
        talAVM2D_LUT.pullTable = (UINT64*)malloc(talAVM2D_LUT.ulLUTDataSize);
        memcpy(talAVM2D_LUT.pullTable, pucBuffer2, talAVM2D_LUT.ulLUTDataSize);

        memset(pucDestBuffer, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 2);
        memset(pucDestBuffer_1, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 2);

        { // test GAE
            // generate GAE output folder
            char acGAEFolder[MAX_PATH];
            char acOutputImageFolder[MAX_PATH];
            wcstombs(acOutputImageFolder, a_pwcOutImageFolder, MAX_PATH);
            sprintf(acGAEFolder, "%sGAE/", acOutputImageFolder);
            _mkdir(acGAEFolder);


            // reset Data
            alGAE_AVM_InitData(&tGAE_Data);
            alSTATISTIC_LoadDefault(&alSTATISTIC_Cfg);
            ptOutImg = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 3);
            for (lCnt = 0; lCnt < 200 ; lCnt++)
            {
                // get noise level
                alStatistic_NoiseLevelEstimation(&alSTATISTIC_Cfg, apucSrcImage, IMAGE_WIDTH, IMAGE_HEIGHT, &alSTATISTIC_Data);

                // Gen alAVM2D (Seamless BV) Image with AE Offset
                alLUT_v2_ProcessFullLU_ApplyGAE(
                    tGAE_Data.acOffset_Ymean_Firmware,
                    &talAVM2D_LUT, apucSrcImage, pucDestBuffer
                );

                sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"alAVM2D_YUV_ByHex_GAE.raw");
                std::ofstream ofile_alAVM2D(sOutputImgeFile.c_str(), std::ios::binary);
                ofile_alAVM2D.write((char*)pucDestBuffer, IMAGE_WIDTH * IMAGE_HEIGHT * 2);
                ofile_alAVM2D.close();

                // get mean estimation value
                alStatistic_MeanEstimateForTopView_10ROIsPerView(&alSTATISTIC_Cfg, IMAGE_WIDTH, IMAGE_HEIGHT, pucDestBuffer, &alSTATISTIC_Data);

                // Global AE Offset estimation
                alGAE_AVM_Main(
                    IMAGE_WIDTH, IMAGE_HEIGHT, pucDestBuffer,
                    &tCarInputInfo,
                    &tAVM2D_Cfg, &talAVM2DParam,
                    &alSTATISTIC_Data,
                    &tGAE_Data
                    );
                DAT_copy2d(DAT_2D2D, pucDestBuffer, pucDestBuffer_1, ((talAVM2DParam.tBirdViewAreaSize.lX + tAVM2D_Cfg.tBVGAE_ROIPixelNumber.lX) << 1), talAVM2DParam.tBirdViewAreaSize.lY, (IMAGE_WIDTH << 1));
                Test_BufferYUV2RGB(pucDestBuffer_1, (UINT8*)ptOutImg->imageData, ptOutImg->width, ptOutImg->height);
                sprintf_s(cText, MAX_PATH, "%sGAE_No_%d.bmp", acGAEFolder, lCnt);

                Test_LogGAE_Data(ptOutImg, &tGAE_Data, lCnt, &alSTATISTIC_Data);
                cvSaveImage(cText, ptOutImg, 0);
            }
            
        }

        cvReleaseImage(&ptOutImg);
        free(talAVM2D_LUT.pullTable);
        delete[] pucBuffer;
        delete[] pucBuffer2;
    }
#endif


    // free image buffer
    delete[] pucSrcBufferFront;
    delete[] pucSrcBufferRear;
    delete[] pucSrcBufferLeft;
    delete[] pucSrcBufferRight;
    delete[] pucDestBuffer;
    delete[] pucDestBuffer_1;

}