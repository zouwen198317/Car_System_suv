
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>
// #include <assert.h>

// #include "TableLU/TableLU.h"
// #include "TableLU/PartitionLUT.h"
#include "basedef.h"
#include "EagleK3_SimulateMain.h"
#include <direct.h> //  for _mkdir


#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif


/** \brief Store the color map for trail line. */
UINT8 g_TRAILLINE_aucColorDef_Test[255][3] = {
    { 0, 0, 0 },
    { 255, 255, 255 },
    { 0, 0, 0 },
    { 255, 0, 0 },
    { 0, 255, 0 },
    { 0, 0, 255 },
    { 255, 255, 0 },
    { 0, 255, 255 },
    { 255, 0, 255 },
    { 255, 128, 0 },
    { 136, 40, 38 },
    { 252, 255, 160 },
    { 99, 195, 96 },
    { 0, 206, 0 },
    { 255, 131, 0 },
    { 217, 106, 106 },
    { 255, 231, 104 },
    { 195, 255, 196 },
    { 255, 243, 179 }
};

#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1

static void DrawTrailLine(IplImage* a_ptImg, alTRAILLINE_LineHeader * a_ptTrailHeader)
{
    // CV_RGB(255,0,0), // 
    UINT8 ucColorIndex = 0;
    INT32 lIndex = 0;

    for (lIndex = 0; lIndex < a_ptTrailHeader->wNumOfPairs; lIndex++)
    {
        ucColorIndex = a_ptTrailHeader->pDrawLineData[lIndex].cColor;
        cvLine(a_ptImg,
            cvPoint(a_ptTrailHeader->pDrawLineData[lIndex].wStartX, a_ptTrailHeader->pDrawLineData[lIndex].wStartY),
            cvPoint(a_ptTrailHeader->pDrawLineData[lIndex].wEndX, a_ptTrailHeader->pDrawLineData[lIndex].wEndY),
            CV_RGB(g_TRAILLINE_aucColorDef_Test[ucColorIndex][0], g_TRAILLINE_aucColorDef_Test[ucColorIndex][1], g_TRAILLINE_aucColorDef_Test[ucColorIndex][2]),
            a_ptTrailHeader->pDrawLineData[lIndex].cThickness,
            a_ptTrailHeader->pDrawLineData[lIndex].cLineType, 0);
    }
}

static void MirrorImage(IplImage* a_ptImg, IplImage* a_ptMirroedImg)
{
    cvFlip(a_ptImg, a_ptMirroedImg, 1);
}

#endif

void TEST_ExportTrailLineImage(wchar_t * a_pwcSrcImageFolder, wchar_t * a_pwcOutImageFolder, alTRAILLINE_Cfg *a_ptCfg, alTRAILLINE_LineSet *a_ptLineDataSet)
{
#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1

    char acSrcImageFolder[MAX_PATH];
    char acOutputImageFolder[MAX_PATH];

    char acFilePath_SrcImageLeft[MAX_PATH];
    char acFilePath_SrcImageRight[MAX_PATH];
    char acFilePath_SrcImageFront[MAX_PATH];
    char acFilePath_SrcImageBack[MAX_PATH];

    char acFilePath_OutImageLeft[MAX_PATH];
    char acFilePath_OutImageRight[MAX_PATH];
    char acFilePath_OutImageFront[MAX_PATH];
    char acFilePath_OutImageBack[MAX_PATH];
#ifndef EXPORT_TRAIL_BAT
    CvScalar tColor_R = CV_RGB(255, 0, 0);
    IplImage* ptMirrirImg = 0;
#endif

    IplImage* ptCropImg = 0;
    alTRAILLINE_PairData * ptTmpLineAddress = 0;

    IplImage* ptSrcImg_STL_Front = 0;
    IplImage* ptSrcImg_STL_Back = 0;
    IplImage* ptSrcImg_STL_Left = 0;
    IplImage* ptSrcImg_STL_Right = 0;
    IplImage* aptSrcImg_DTL_Front[MAX_DYNAMIC_TRAIL_LINE_NUM] = { 0 };
    IplImage* aptSrcImg_DTL_Back[MAX_DYNAMIC_TRAIL_LINE_NUM] = { 0 };

    UINT8 * apucSrcImage_STL_Front = 0;
    UINT8 * apucSrcImage_STL_Back = 0;
    UINT8 * apucSrcImage_STL_Left = 0;
    UINT8 * apucSrcImage_STL_Right = 0;
    UINT8 * apucSrcImage_DTL_Front[MAX_DYNAMIC_TRAIL_LINE_NUM] = { 0 };
    UINT8 * apucSrcImage_DTL_Back[MAX_DYNAMIC_TRAIL_LINE_NUM] = { 0 };

    INT16 wDTLIndex = 0;

    wprintf(L"\nGenerate test images for trail lines.\n\n");

    setlocale(LC_ALL, "cht");

    wcstombs(acSrcImageFolder, a_pwcSrcImageFolder, MAX_PATH);

    sprintf(acFilePath_SrcImageLeft, "%sSource_0.bmp", acSrcImageFolder);
    sprintf(acFilePath_SrcImageRight, "%sSource_1.bmp", acSrcImageFolder);
    sprintf(acFilePath_SrcImageFront, "%sSource_2.bmp", acSrcImageFolder);
    sprintf(acFilePath_SrcImageBack, "%sSource_3.bmp", acSrcImageFolder);

    wcstombs(acOutputImageFolder, a_pwcOutImageFolder, MAX_PATH);

    sprintf(acFilePath_OutImageLeft, "%sSTL_Left.bmp", acOutputImageFolder);
    sprintf(acFilePath_OutImageRight, "%sSTL_Right.bmp", acOutputImageFolder);
    sprintf(acFilePath_OutImageFront, "%sSTL_Front.bmp", acOutputImageFolder);
    sprintf(acFilePath_OutImageBack, "%sSTL_Back.bmp", acOutputImageFolder);

    // Test Static - Front View
    {
#ifdef EXPORT_TRAIL_BAT
        // (1) Create Empty Image
        ptSrcImg_STL_Front = cvCreateImage(cvSize(g_CAMK_atCameraCurrentParam[EAGLEK3_BV_FRONT].ulImageWidth, g_CAMK_atCameraCurrentParam[EAGLEK3_BV_FRONT].ulImageHeight), 8, 3);
        cvSet(ptSrcImg_STL_Front, CV_RGB(255, 255, 255), 0);
#else
        // (1) Load Image
        ptSrcImg_STL_Front = cvLoadImage(acFilePath_SrcImageFront, CV_LOAD_IMAGE_COLOR);
#endif

        // (3) Draw Trail Line
        if (a_ptCfg->atSTLCfg[1].ucIsEnable == 1 || a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Front, &(a_ptLineDataSet->aStaticTrailLine[alTRAILLINE_STL_FRONT]));
        }

        cvSaveImage(acFilePath_OutImageFront, ptSrcImg_STL_Front, 0);
    }

    // Test Static - Back View
    {

#ifdef EXPORT_TRAIL_BAT
        // (1) Create Empty Image
        ptSrcImg_STL_Back = cvCreateImage(cvSize(g_CAMK_atCameraCurrentParam[EAGLEK3_BV_BACK].ulImageWidth, g_CAMK_atCameraCurrentParam[EAGLEK3_BV_BACK].ulImageHeight), 8, 3);
        cvSet(ptSrcImg_STL_Back, CV_RGB(255, 255, 255), 0);
#else
        // (1) Load Image
        ptSrcImg_STL_Back = cvLoadImage(acFilePath_SrcImageBack, CV_LOAD_IMAGE_COLOR);
        ptMirrirImg = cvCreateImage(cvSize(ptSrcImg_STL_Back->width, ptSrcImg_STL_Back->height), ptSrcImg_STL_Back->depth, ptSrcImg_STL_Back->nChannels);
        MirrorImage(ptSrcImg_STL_Back, ptMirrirImg);
        cvCopy(ptMirrirImg, ptSrcImg_STL_Back, 0);
        cvReleaseImage(&ptMirrirImg);
#endif

        // (3) Draw Trail Line
        if (a_ptCfg->atSTLCfg[0].ucIsEnable == 1 || a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Back, &(a_ptLineDataSet->aStaticTrailLine[alTRAILLINE_STL_BACK ]));
        }



#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Back, ptSrcImg_STL_Back, CV_BGR2YCrCb);
        apucSrcImage_STL_Back = (UINT8*)ptSrcImg_STL_Front->imageData;
#endif
        cvSaveImage(acFilePath_OutImageBack, ptSrcImg_STL_Back, 0);
    }

    // Test Static - Left View
    {
#ifdef EXPORT_TRAIL_BAT
        // (1) Create Empty Image
        ptSrcImg_STL_Left = cvCreateImage(cvSize(g_CAMK_atCameraCurrentParam[EAGLEK3_BV_LEFT].ulImageWidth, g_CAMK_atCameraCurrentParam[EAGLEK3_BV_LEFT].ulImageHeight), 8, 3);
        cvSet(ptSrcImg_STL_Left, CV_RGB(255, 255, 255), 0);
#else
        // (1) Load Image
        ptSrcImg_STL_Left = cvLoadImage(acFilePath_SrcImageLeft, CV_LOAD_IMAGE_COLOR);
#endif

        // (3) Draw Trail Line
        if (a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Left, &(a_ptLineDataSet->aStaticTrailLine[alTRAILLINE_STL_LEFT]));
        }


#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Left, ptSrcImg_STL_Left, CV_BGR2YCrCb);
        apucSrcImage_STL_Left = (UINT8*)ptSrcImg_STL_Left->imageData;
#endif
        cvSaveImage(acFilePath_OutImageLeft, ptSrcImg_STL_Left, 0);
    }

    // Test Static - Right View
    {

#ifdef EXPORT_TRAIL_BAT
        // (1) Create Empty Image
        ptSrcImg_STL_Right = cvCreateImage(cvSize(g_CAMK_atCameraCurrentParam[EAGLEK3_BV_RIGHT].ulImageWidth, g_CAMK_atCameraCurrentParam[EAGLEK3_BV_RIGHT].ulImageHeight), 8, 3);
        cvSet(ptSrcImg_STL_Right, CV_RGB(255, 255, 255), 0);
#else
        // (1) Load Image
        ptSrcImg_STL_Right = cvLoadImage(acFilePath_SrcImageRight, CV_LOAD_IMAGE_COLOR);
        ptMirrirImg = cvCreateImage(cvSize(ptSrcImg_STL_Right->width, ptSrcImg_STL_Right->height), ptSrcImg_STL_Right->depth, ptSrcImg_STL_Right->nChannels);
        MirrorImage(ptSrcImg_STL_Right, ptMirrirImg);
        cvCopy(ptMirrirImg, ptSrcImg_STL_Right, 0);
        cvReleaseImage(&ptMirrirImg);
#endif

        // (3) Draw Trail Line
        if (a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Right, &(a_ptLineDataSet->aStaticTrailLine[alTRAILLINE_STL_RIGHT]));
        }


#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Right, ptSrcImg_STL_Right, CV_BGR2YCrCb);
        apucSrcImage_STL_Right = (UINT8*)ptSrcImg_STL_Front->imageData;
#endif
        cvSaveImage(acFilePath_OutImageRight, ptSrcImg_STL_Right, 0);
    }

    {
        char acDTLFolder[MAX_PATH];
        sprintf(acDTLFolder, "%sDTL/", acOutputImageFolder);
        _mkdir(acDTLFolder);
    }

    // Test Dynamic Trail Line - Front
    {
        INT16 wHalfDTLCnt = a_ptLineDataSet->uwDTLCount / 2;
        char acOutImage_DTLFront[MAX_PATH];
        INT16 wDTLDegree = 0;
        alTRAILLINE_LineHeader * ptTrailHeader = 0;
        IplImage *ptFrontSrcImg;

        // (1) Load Image
#ifdef EXPORT_TRAIL_BAT
        // (1) Create Empty Image
        ptFrontSrcImg = cvCreateImage(cvSize(g_CAMK_atCameraCurrentParam[EAGLEK3_BV_FRONT].ulImageWidth, g_CAMK_atCameraCurrentParam[EAGLEK3_BV_FRONT].ulImageHeight), 8, 3);
        cvSet(ptFrontSrcImg, CV_RGB(255, 255, 255), 0);
#else
        // (1) Load Image
        ptFrontSrcImg = cvLoadImage(acFilePath_SrcImageFront, CV_LOAD_IMAGE_COLOR);
#endif

        for (wDTLIndex = 0; wDTLIndex < a_ptLineDataSet->uwDTLCount; wDTLIndex++)
        {
            aptSrcImg_DTL_Front[wDTLIndex] = cvCreateImage(cvSize(ptFrontSrcImg->width, ptFrontSrcImg->height), ptFrontSrcImg->depth, ptFrontSrcImg->nChannels);
            cvCopy(ptFrontSrcImg, aptSrcImg_DTL_Front[wDTLIndex], 0);
            ptTrailHeader = &(a_ptLineDataSet->aDynamicTrailLine[alTRAILLINE_DTL_FRONT - alTRAILLINE_DTL_FRONT][wDTLIndex]);

            // (3) Draw Trail Line
            if (a_ptCfg->atDTLCfg[0].ucIsEnable == 1)
            {
                DrawTrailLine(aptSrcImg_DTL_Front[wDTLIndex], ptTrailHeader);
            }


            // (5) Gen output file name
            wDTLDegree = (wDTLIndex - wHalfDTLCnt) * a_ptCfg->uwSteeringAngleInterval;
            if (wDTLDegree > 0)
            {
                sprintf(acOutImage_DTLFront, "%sDTL/DTL_Front_degree_+%d.bmp", acOutputImageFolder, wDTLDegree);
            }
            else
            {
                sprintf(acOutImage_DTLFront, "%sDTL/DTL_Front_degree_%d.bmp", acOutputImageFolder, wDTLDegree);
            }

#ifdef EXPORT_TRAIL_BAT
            cvCvtColor(aptSrcImg_DTL_Front[wDTLIndex], aptSrcImg_DTL_Front[wDTLIndex], CV_BGR2YCrCb);
            apucSrcImage_DTL_Front[wDTLIndex] = (UINT8*)aptSrcImg_DTL_Front[wDTLIndex]->imageData;
#endif
            cvSaveImage(acOutImage_DTLFront, aptSrcImg_DTL_Front[wDTLIndex], 0);
        }

        cvReleaseImage(&ptFrontSrcImg);
    }

    // Test Dynamic Trail Line - Back
    {
        INT16 wHalfDTLCnt = a_ptLineDataSet->uwDTLCount / 2;
        char acOutImage_DTLBack[MAX_PATH];
        char acOutputDegree[10];
        INT16 wDTLDegree = 0;
        alTRAILLINE_LineHeader * ptTrailHeader = 0;
        IplImage *ptBackSrcImg;

        // (1) Load Image
#ifdef EXPORT_TRAIL_BAT
        // (1) Create Empty Image
        ptBackSrcImg = cvCreateImage(cvSize(g_CAMK_atCameraCurrentParam[EAGLEK3_BV_BACK].ulImageWidth, g_CAMK_atCameraCurrentParam[EAGLEK3_BV_BACK].ulImageHeight), 8, 3);
        cvSet(ptBackSrcImg, CV_RGB(255, 255, 255), 0);
#else
        // (1) Load Image
        ptBackSrcImg = cvLoadImage(acFilePath_SrcImageBack, CV_LOAD_IMAGE_COLOR);
        ptMirrirImg = cvCreateImage(cvSize(ptBackSrcImg->width, ptBackSrcImg->height), ptBackSrcImg->depth, ptBackSrcImg->nChannels);
        MirrorImage(ptBackSrcImg, ptMirrirImg);
        cvCopy(ptMirrirImg, ptBackSrcImg, 0);
        cvReleaseImage(&ptMirrirImg);
#endif

        for (wDTLIndex = 0; wDTLIndex < a_ptLineDataSet->uwDTLCount; wDTLIndex++)
        {
            aptSrcImg_DTL_Back[wDTLIndex] = cvCreateImage(cvSize(ptBackSrcImg->width, ptBackSrcImg->height), ptBackSrcImg->depth, ptBackSrcImg->nChannels);
            cvCopy(ptBackSrcImg, aptSrcImg_DTL_Back[wDTLIndex], 0);
            ptTrailHeader = &(a_ptLineDataSet->aDynamicTrailLine[alTRAILLINE_DTL_BACK - alTRAILLINE_DTL_FRONT][wDTLIndex]);

            // (3) Draw Trail Line
            if (a_ptCfg->atDTLCfg[1].ucIsEnable == 1)
            {
                DrawTrailLine(aptSrcImg_DTL_Back[wDTLIndex], ptTrailHeader);
            }


            // (5) Gen output file name
            wDTLDegree = (wDTLIndex - wHalfDTLCnt) * a_ptCfg->uwSteeringAngleInterval;
            _itoa_s(wDTLDegree, acOutputDegree, 10, 10);
            if (wDTLDegree > 0)
            {
                sprintf(acOutImage_DTLBack, "%sDTL/DTL_Back_degree_+%d.bmp", acOutputImageFolder, wDTLDegree);
            }
            else
            {
                sprintf(acOutImage_DTLBack, "%sDTL/DTL_Back_degree_%d.bmp", acOutputImageFolder, wDTLDegree);
            }

#ifdef EXPORT_TRAIL_BAT
            cvCvtColor(aptSrcImg_DTL_Back[wDTLIndex], aptSrcImg_DTL_Back[wDTLIndex], CV_BGR2YCrCb);
            apucSrcImage_DTL_Back[wDTLIndex] = (UINT8*)aptSrcImg_DTL_Back[wDTLIndex]->imageData;
#endif
            cvSaveImage(acOutImage_DTLBack, aptSrcImg_DTL_Back[wDTLIndex], 0);
        }

        cvReleaseImage(&ptBackSrcImg);
    }

#ifdef EXPORT_TRAIL_BAT
    // Output trail line to bat file.
    EAGLEK3_GenerateTrailLineBat(
        apucSrcImage_STL_Front,
        apucSrcImage_STL_Back,
        apucSrcImage_STL_Left,
        apucSrcImage_STL_Right,
        apucSrcImage_DTL_Front,
        apucSrcImage_DTL_Back,
        720, 480, 3, g_EAGLEK3_tCommonCfg.ulMaxSteeringAngle, a_ptCfg->uwSteeringAngleInterval);
#endif

    cvReleaseImage(&ptSrcImg_STL_Front);
    cvReleaseImage(&ptSrcImg_STL_Back);
    cvReleaseImage(&ptSrcImg_STL_Left);
    cvReleaseImage(&ptSrcImg_STL_Right);
    for (wDTLIndex = 0; wDTLIndex < a_ptLineDataSet->uwDTLCount; wDTLIndex++)
    {
        cvReleaseImage(&(aptSrcImg_DTL_Front[wDTLIndex]));
        cvReleaseImage(&(aptSrcImg_DTL_Back[wDTLIndex]));
    }

#endif

}

void Test_Static_TrailLine_Generate(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    )
{
    std::wstring sAVLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_AVLUT_set.hex");
    std::wstring sAVLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_AVLUT_data.hex");
    std::wstring sOutputImgeFile;
    UINT8 * pucBuffer = NULL;
    UINT8 * pucBuffer2 = NULL;
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT32 ulBufferLength = 0, ulBufferLength2 = 0;
    alPartLUT_v1_LUTSet_t tSAV_LUT;

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

        delete[] pucDestBuffer;        
    }
}


void Test_TrailLine_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;
    alTRAILLINE_LineSet tTL_LineData = {0};

    UINT8 * apucSrcImage[4];
    UINT8 * pucSrcBufferFront = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRear = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferLeft = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucSrcBufferRight = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];
    UINT8 * pucDestBuffer = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];

    INT32 alSFPX[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 alSFPY[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 lIndex1 = 0, lIndex2 = 0;

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
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucEagleK3WorkingBuffer = NULL, *pucTLWorkingBuffer = NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0, ulTrailLineBufferSize = 0;

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
    // Test_SET_BV_FM_Default(atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

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

    // Gennerate RT Matrix
    EAGLEK3_Gen_RT_Matrix(&tEAGLEK3_Cfg, &tAVM2D_Cfg, &tAVM2D_Params, &tEAGLEK3_Params, &tEAGLEK3_Data);

#if 1
    {   // Generate Trail Line Data
        alTRAILLINE_Cfg tTL_Cfg = {0};

        alTRAILLINE_Cfg tTL_CfgTest = { 0 };

        alTRAILLINE_Params tTL_Params = {0};
        alTRAILLINE_Data tTL_Data = { 0 };
        INT32 lCmp = 0;
     
        // Load Default 
        alTRAILLINE_LoadDefault(&tTL_Cfg);

        // Load conifg data from INI file
        alTRAILLINE_CfgImportByINI(awcConfigFilePath, &tTL_Cfg);

#if 1 // for debug
        alTRAILLINE_LoadDefault(&tTL_CfgTest);

        lCmp = memcmp(&tTL_CfgTest, &tTL_Cfg, sizeof(alTRAILLINE_Cfg));
#endif

        // malloc Line Data buffer
        ulTrailLineBufferSize = alTRAILLINE_QurryTrailLineWorkingBufferSize();

        // Initialized static trail line buffer.
        for (lIndex1 = alTRAILLINE_STL_LEFT; lIndex1 <= alTRAILLINE_STL_BACK; lIndex1++)
        {
            tTL_LineData.aStaticTrailLine[lIndex1].pDrawLineData = (alTRAILLINE_PairData*)malloc(ulTrailLineBufferSize);
            memset(tTL_LineData.aStaticTrailLine[lIndex1].pDrawLineData, 0, ulTrailLineBufferSize);
        }

        // Initialized dynamic trail line buffer.
        for (lIndex1 = 0; lIndex1 < 2; lIndex1++)
        {
            for (lIndex2 = 0; lIndex2 < MAX_DYNAMIC_TRAIL_LINE_NUM; lIndex2++)
            {
                tTL_LineData.aDynamicTrailLine[lIndex1][lIndex2].pDrawLineData = (alTRAILLINE_PairData*)malloc(ulTrailLineBufferSize);
                memset(tTL_LineData.aDynamicTrailLine[lIndex1][lIndex2].pDrawLineData, 0, ulTrailLineBufferSize);
            }
        }

        // malloc working buffer
        ulTrailLineBufferSize = alTRAILLINE_QurryTrailLineWorkingBufferSize();
        pucTLWorkingBuffer = (UINT8*)malloc(ulTrailLineBufferSize);
        
        // Init By Cfg
        alTRAILLINE_InitialByCfg(
            pucTLWorkingBuffer, &tTL_Data,
            &tAVM2D_Cfg, &tAVM2D_Params,
            &tCommonCfg,
            &tTL_Cfg, &tTL_Params, &tTL_LineData
            );
 
#if 1 // for FW PORTING
        FILE *pDataFile = NULL;
        pDataFile = fopen("TL_AVM2D_Cfg.hex", "wb");
        fwrite(&tAVM2D_Cfg, sizeof(alAVM2D_Cfg), 1, pDataFile);
        fclose(pDataFile);

        pDataFile = fopen("TL_AVM2D_Params.hex", "wb");
        fwrite(&tAVM2D_Params, sizeof(alAVM2D_Params), 1, pDataFile);
        fclose(pDataFile);

        pDataFile = fopen("TL_CommonCfg.hex", "wb");
        fwrite(&tCommonCfg, sizeof(alCOMMONK_CommonCfg), 1, pDataFile);
        fclose(pDataFile);

        pDataFile = fopen("TL_CalibrationParams.hex", "wb");
        fwrite(tEAGLEK3_Data.atCalibrationParams, sizeof(alCOMMONK_CalibrationParams) * 4, 1, pDataFile);
        fclose(pDataFile);

        pDataFile = fopen("TL_Cfg.hex", "wb");
        fwrite(&tTL_Cfg, sizeof(alTRAILLINE_Cfg), 1, pDataFile);
        fclose(pDataFile);

        pDataFile = fopen("TL_Params.hex", "wb");
        fwrite(&tTL_Params, sizeof(alTRAILLINE_Params), 1, pDataFile);
        fclose(pDataFile);
#endif

        // Gen LUT
        alTRAILLINE_GenerateLineData(
            &tTL_Data,
            tEAGLEK3_Data.atCalibrationParams,
            atFM_v2_Model,
            &tTL_Cfg, &tTL_Params, &tTL_LineData
        );

#if 1 // test trail line result
        TEST_ExportTrailLineImage(
            a_pwcSrcImageFolder,
            a_pwcOutImageFolder,
            &tTL_Cfg,
            &tTL_LineData
        );
#endif

#if 1   // Save LUT
        wchar_t awcFilePath[MAX_PATH];
        UINT8 *pucData = NULL;
        UINT32 ulSize = 0, ulSizeTmp = 0;
        ulSizeTmp = MAX_DYNAMIC_TRAIL_LINE_NUM * (sizeof(alTRAILLINE_LineHeader) + MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData));
        pucData = (UINT8*)malloc(MAX_DYNAMIC_TRAIL_LINE_NUM * (sizeof(alTRAILLINE_LineHeader) + MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData)));

        memset(pucData, 0, ulSizeTmp);
            

        if (tTL_Cfg.atSTLCfg[0].ucIsEnable == 1 || tTL_Cfg.atWLCfg[0].ucIsEnable == 1)
        {
            // Static Trailline Front File
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_Trail_Output_StaticFront.hex");
            alTRAILLINE_GetBufferSize(alTRAILLINE_STL_FRONT, &ulSize, &tTL_LineData);
            alTRAILLINE_GetLineData(alTRAILLINE_STL_FRONT, ulSize, pucData, &tTL_LineData);
            Test_Memory2FileW(awcFilePath, pucData, ulSize);
        }

        if (tTL_Cfg.atSTLCfg[1].ucIsEnable == 1 || tTL_Cfg.atWLCfg[1].ucIsEnable == 1)
        {
            // Static Trailline Back File
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_Trail_Output_StaticBack.hex");
            alTRAILLINE_GetBufferSize(alTRAILLINE_STL_BACK , &ulSize, &tTL_LineData);
            alTRAILLINE_GetLineData(alTRAILLINE_STL_BACK , ulSize, pucData, &tTL_LineData);
            Test_Memory2FileW(awcFilePath, pucData, ulSize);
        }

        if (tTL_Cfg.atWLCfg[2].ucIsEnable == 1)
        {
            // Static Trailline Left File
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_Trail_Output_StaticLeft.hex");
            alTRAILLINE_GetBufferSize(alTRAILLINE_STL_LEFT, &ulSize, &tTL_LineData);
            alTRAILLINE_GetLineData(alTRAILLINE_STL_LEFT, ulSize, pucData, &tTL_LineData);
            Test_Memory2FileW(awcFilePath, pucData, ulSize);
        }

        if (tTL_Cfg.atWLCfg[3].ucIsEnable == 1)
        {
            // Static Trailline Right File
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_Trail_Output_StaticRight.hex");
            alTRAILLINE_GetBufferSize(alTRAILLINE_STL_RIGHT, &ulSize, &tTL_LineData);
            alTRAILLINE_GetLineData(alTRAILLINE_STL_RIGHT, ulSize, pucData, &tTL_LineData);
            Test_Memory2FileW(awcFilePath, pucData, ulSize);
        }

        if (tTL_Cfg.atDTLCfg[0].ucIsEnable == 1)
        {
            // Dynamic Trailline Front File
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_Trail_Output_DynamicFront.hex");
            alTRAILLINE_GetBufferSize(alTRAILLINE_DTL_FRONT, &ulSize, &tTL_LineData);
            alTRAILLINE_GetLineData(alTRAILLINE_DTL_FRONT, ulSize, pucData, &tTL_LineData);
            Test_Memory2FileW(awcFilePath, pucData, ulSize);
        }

        if (tTL_Cfg.atDTLCfg[1].ucIsEnable == 1)
        {
            // Dynamic Trailline Back File
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_Trail_Output_DynamicBack.hex");
            alTRAILLINE_GetBufferSize(alTRAILLINE_DTL_BACK, &ulSize, &tTL_LineData);
            alTRAILLINE_GetLineData(alTRAILLINE_DTL_BACK, ulSize, pucData, &tTL_LineData);
            Test_Memory2FileW(awcFilePath, pucData, ulSize);
        }

        free(pucData);
#endif
        // Free LUT buffer
        // free static trail line buffer.
        for (lIndex1 = alTRAILLINE_STL_LEFT; lIndex1 <= alTRAILLINE_STL_BACK; lIndex1++)
        {
            free(tTL_LineData.aStaticTrailLine[lIndex1].pDrawLineData);
        }

        // free dynamic trail line buffer.
        for (lIndex1 = 0; lIndex1 < 2; lIndex1++)
        {
            for (lIndex2 = 0; lIndex2 < MAX_DYNAMIC_TRAIL_LINE_NUM; lIndex2++)
            {
                free(tTL_LineData.aDynamicTrailLine[lIndex1][lIndex2].pDrawLineData);
            }
        }

        // free working buffer
        free(pucTLWorkingBuffer);
    }
#endif

#if 0
    Test_Static_TrailLine_Generate(
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