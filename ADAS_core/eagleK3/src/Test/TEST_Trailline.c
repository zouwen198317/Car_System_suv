
// This file includes functions to test the trail line.

#include "EagleK3.h"

//#define EXPORT_TRAIL_BAT

#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC

#include <sys/stat.h>
#include <direct.h>
#include <locale.h>
#include <stdlib.h>     /* wcstombs, wchar_t(C) */

#include "Camera/CameraDef.h"
#include "Trailline/TraillineDef.h"
#include "NormalView/NormalViewDef.h"
#include "DataOperation/FileOperation.h"

#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

#include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#endif // #if EAGLEK3_INCLUDE_OPENCV_TEST == 1

extern UINT8 g_TRAILLINE_aucColorDef[15][3];

static void ImportTraillineHexFiles(wchar_t * a_pwcHexFilePath, UINT8 ** a_ppucBuffer, UINT32 * a_plBufferLength)
{
    // Import Hex
    struct _stat st;
    if(_wstat(a_pwcHexFilePath, &st) != 0)
    {
        wprintf(L"Can not load hex file: \"%S\"", a_pwcHexFilePath);
        return;
    }

    (*a_ppucBuffer) = (UINT8*) malloc(st.st_size);

    EAGLEK3_File2MemoryW(a_pwcHexFilePath, (*a_ppucBuffer), st.st_size);

    *a_plBufferLength = st.st_size;
}

#if EAGLEK3_INCLUDE_OPENCV_TEST == 1
static void DrawTrailLine(IplImage* a_ptImg, TRAILLINE_LineHeader * a_ptTrailHeader)
{
    UINT8 ucColorIndex = 0;
    INT32 lIndex = 0;

    for(lIndex = 0; lIndex < a_ptTrailHeader->wNumOfPairs; lIndex++)
    {
        ucColorIndex = a_ptTrailHeader->pDrawLineData[lIndex].cColor;
        cvLine(a_ptImg, 
            cvPoint(a_ptTrailHeader->pDrawLineData[lIndex].wStartX, a_ptTrailHeader->pDrawLineData[lIndex].wStartY),
            cvPoint(a_ptTrailHeader->pDrawLineData[lIndex].wEndX, a_ptTrailHeader->pDrawLineData[lIndex].wEndY), 
            CV_RGB(g_TRAILLINE_aucColorDef[ucColorIndex][0], g_TRAILLINE_aucColorDef[ucColorIndex][1], g_TRAILLINE_aucColorDef[ucColorIndex][2]), 
            a_ptTrailHeader->pDrawLineData[lIndex].cThickness, 
            a_ptTrailHeader->pDrawLineData[lIndex].cLineType, 0);
    }
}

static void MirrorImage(IplImage* a_ptImg, IplImage* a_ptMirroedImg)
{
#if 0
    char *pcSrc = 0, *pcDest = 0;
    INT32 lMirrorX = 0;
    INT32 x, y;

    // Mirror the image
    for(y = 0; y < a_ptImg->height; y++)
    {
        for(x = 0; x < a_ptImg->width; x++)
        {
            lMirrorX = a_ptImg->width - x - 1;
            pcSrc = a_ptImg->imageData + (x + y * a_ptImg->width) * a_ptImg->nChannels;                
            pcDest = a_ptMirroedImg->imageData + (lMirrorX + y * a_ptMirroedImg->width) * a_ptMirroedImg->nChannels;

            memcpy(pcDest, pcSrc, a_ptImg->nChannels * sizeof(UINT8));
        }
    }
#else
    cvFlip(a_ptImg, a_ptMirroedImg, 1);
#endif

}
#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

void TEST_ExportTrailLineImage(wchar_t * a_pwcSrcImageFolder, wchar_t * a_pwcOutImageFolder)
{
#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

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
    CvScalar tColor_R = CV_RGB(255,0,0);
    IplImage* ptMirrirImg = 0;
#endif

    IplImage* ptCropImg = 0;
    TRAILLINE_PairData * ptTmpLineAddress = 0;

    IplImage* ptSrcImg_STL_Front = 0;
    IplImage* ptSrcImg_STL_Back = 0;
    IplImage* ptSrcImg_STL_Left = 0;
    IplImage* ptSrcImg_STL_Right = 0;
    IplImage* aptSrcImg_DTL_Front[MAX_DYNAMIC_TRAIL_LINE_NUM] = {0};
    IplImage* aptSrcImg_DTL_Back[MAX_DYNAMIC_TRAIL_LINE_NUM] = {0};

    UINT8 * apucSrcImage_STL_Front = 0;
    UINT8 * apucSrcImage_STL_Back = 0;
    UINT8 * apucSrcImage_STL_Left = 0;
    UINT8 * apucSrcImage_STL_Right = 0;
    UINT8 * apucSrcImage_DTL_Front[MAX_DYNAMIC_TRAIL_LINE_NUM] = {0};
    UINT8 * apucSrcImage_DTL_Back[MAX_DYNAMIC_TRAIL_LINE_NUM] = {0};
    
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
        if(g_TRAILLINE_tCfg.atSTLCfg[1].ucIsEnable == 1 || g_TRAILLINE_tCfg.atWLCfg[EAGLEK3_STL_FRONT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Front, &(g_TRAILLINE_tLineDataSet.aStaticTrailLine[EAGLEK3_STL_FRONT]));
        }

#ifndef EXPORT_TRAIL_BAT
        // (4) Show Crop Area
        cvRectangle(ptSrcImg_STL_Front, cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.Y),
            cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.X + g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropAreaSize.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.Y + g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropAreaSize.Y),
            tColor_R, 1, 8, 0);
#endif

#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Front, ptSrcImg_STL_Front, CV_BGR2YCrCb);
        apucSrcImage_STL_Front = (UINT8*) ptSrcImg_STL_Front->imageData;
#endif
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
        if(g_TRAILLINE_tCfg.atSTLCfg[0].ucIsEnable == 1 || g_TRAILLINE_tCfg.atWLCfg[EAGLEK3_STL_LEFT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Back, &(g_TRAILLINE_tLineDataSet.aStaticTrailLine[EAGLEK3_STL_BACK]));
        }

#ifndef EXPORT_TRAIL_BAT
        // (4) Show Crop Area
        cvRectangle(ptSrcImg_STL_Back, cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.Y),
            cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.X + g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropAreaSize.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.Y + g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropAreaSize.Y),
            tColor_R, 1, 8, 0);
#endif

#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Back, ptSrcImg_STL_Back, CV_BGR2YCrCb);
        apucSrcImage_STL_Back = (UINT8*) ptSrcImg_STL_Front->imageData;
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
        if(g_TRAILLINE_tCfg.atWLCfg[EAGLEK3_STL_LEFT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Left, &(g_TRAILLINE_tLineDataSet.aStaticTrailLine[EAGLEK3_STL_LEFT]));
        }

#ifndef EXPORT_TRAIL_BAT
        // (4) Show Crop Area
        cvRectangle(ptSrcImg_STL_Left, cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_LEFT].tCropStartPoint.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_LEFT].tCropStartPoint.Y),
            cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_LEFT].tCropStartPoint.X + g_NORMALVIEW_atCfg[EAGLEK3_BV_LEFT].tCropAreaSize.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_LEFT].tCropStartPoint.Y + g_NORMALVIEW_atCfg[EAGLEK3_BV_LEFT].tCropAreaSize.Y),
            tColor_R, 1, 8, 0);
#endif

#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Left, ptSrcImg_STL_Left, CV_BGR2YCrCb);
        apucSrcImage_STL_Left = (UINT8*) ptSrcImg_STL_Left->imageData;
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
        if(g_TRAILLINE_tCfg.atWLCfg[EAGLEK3_STL_RIGHT].ucIsEnable == 1)
        {
            DrawTrailLine(ptSrcImg_STL_Right, &(g_TRAILLINE_tLineDataSet.aStaticTrailLine[EAGLEK3_STL_RIGHT]));
        }

#ifndef EXPORT_TRAIL_BAT
        // (4) Show Crop Area
        cvRectangle(ptSrcImg_STL_Right, cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_RIGHT].tCropStartPoint.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_RIGHT].tCropStartPoint.Y),
            cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_RIGHT].tCropStartPoint.X + g_NORMALVIEW_atCfg[EAGLEK3_BV_RIGHT].tCropAreaSize.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_RIGHT].tCropStartPoint.Y + g_NORMALVIEW_atCfg[EAGLEK3_BV_RIGHT].tCropAreaSize.Y),
            tColor_R, 1, 8, 0);
#endif

#ifdef EXPORT_TRAIL_BAT
        cvCvtColor(ptSrcImg_STL_Right, ptSrcImg_STL_Right, CV_BGR2YCrCb);
        apucSrcImage_STL_Right = (UINT8*) ptSrcImg_STL_Front->imageData;
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
        INT16 wHalfDTLCnt = g_TRAILLINE_tLineDataSet.uwDTLCount / 2;
        char acOutImage_DTLFront[MAX_PATH];
        INT16 wDTLDegree = 0;
        TRAILLINE_LineHeader * ptTrailHeader = 0;
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

        for(wDTLIndex = 0; wDTLIndex < g_TRAILLINE_tLineDataSet.uwDTLCount; wDTLIndex++)
        {
            aptSrcImg_DTL_Front[wDTLIndex] = cvCreateImage(cvSize(ptFrontSrcImg->width, ptFrontSrcImg->height), ptFrontSrcImg->depth, ptFrontSrcImg->nChannels);
            cvCopy(ptFrontSrcImg, aptSrcImg_DTL_Front[wDTLIndex], 0);
            ptTrailHeader = &(g_TRAILLINE_tLineDataSet.aDynamicTrailLine[EAGLEK3_DTL_FRONT - EAGLEK3_DTL_FRONT][wDTLIndex]);

            // (3) Draw Trail Line
            if(g_TRAILLINE_tCfg.atDTLCfg[0].ucIsEnable == 1)
            {
                DrawTrailLine(aptSrcImg_DTL_Front[wDTLIndex], ptTrailHeader);
            }

#ifndef EXPORT_TRAIL_BAT
            // (4) Show Crop Area
            cvRectangle(aptSrcImg_DTL_Front[wDTLIndex], cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.Y),
                cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.X + g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropAreaSize.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropStartPoint.Y + g_NORMALVIEW_atCfg[EAGLEK3_BV_FRONT].tCropAreaSize.Y),
                tColor_R, 1, 8, 0);
#endif

            // (5) Gen output file name
            wDTLDegree = (wDTLIndex - wHalfDTLCnt) * g_TRAILLINE_tCfg.uwSteeringAngleInterval;
            if(wDTLDegree > 0)
            {
                sprintf(acOutImage_DTLFront, "%sDTL/DTL_Front_degree_+%d.bmp", acOutputImageFolder, wDTLDegree);
            }
            else
            {
                sprintf(acOutImage_DTLFront, "%sDTL/DTL_Front_degree_%d.bmp", acOutputImageFolder, wDTLDegree);
            }

#ifdef EXPORT_TRAIL_BAT
            cvCvtColor(aptSrcImg_DTL_Front[wDTLIndex], aptSrcImg_DTL_Front[wDTLIndex], CV_BGR2YCrCb);
            apucSrcImage_DTL_Front[wDTLIndex] = (UINT8*) aptSrcImg_DTL_Front[wDTLIndex]->imageData;
#endif
            cvSaveImage(acOutImage_DTLFront, aptSrcImg_DTL_Front[wDTLIndex], 0);
        }

        cvReleaseImage(&ptFrontSrcImg);
    }

    // Test Dynamic Trail Line - Back
    {
        INT16 wHalfDTLCnt = g_TRAILLINE_tLineDataSet.uwDTLCount / 2;
        char acOutImage_DTLBack[MAX_PATH];
        char acOutputDegree[10];
        INT16 wDTLDegree = 0;
        TRAILLINE_LineHeader * ptTrailHeader = 0;
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

        for(wDTLIndex = 0; wDTLIndex < g_TRAILLINE_tLineDataSet.uwDTLCount; wDTLIndex++)
        {
            aptSrcImg_DTL_Back[wDTLIndex] = cvCreateImage(cvSize(ptBackSrcImg->width, ptBackSrcImg->height), ptBackSrcImg->depth, ptBackSrcImg->nChannels);
            cvCopy(ptBackSrcImg, aptSrcImg_DTL_Back[wDTLIndex], 0);
            ptTrailHeader = &(g_TRAILLINE_tLineDataSet.aDynamicTrailLine[EAGLEK3_DTL_BACK - EAGLEK3_DTL_FRONT][wDTLIndex]);

            // (3) Draw Trail Line
            if(g_TRAILLINE_tCfg.atDTLCfg[1].ucIsEnable == 1)
            {
                DrawTrailLine(aptSrcImg_DTL_Back[wDTLIndex], ptTrailHeader);
            }

#ifndef EXPORT_TRAIL_BAT
            // (4) Show Crop Area
            cvRectangle(aptSrcImg_DTL_Back[wDTLIndex], cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.Y),
                cvPoint(g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.X + g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropAreaSize.X, g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropStartPoint.Y + g_NORMALVIEW_atCfg[EAGLEK3_BV_BACK].tCropAreaSize.Y),
                tColor_R, 1, 8, 0);
#endif

            // (5) Gen output file name
            wDTLDegree = (wDTLIndex - wHalfDTLCnt) * g_TRAILLINE_tCfg.uwSteeringAngleInterval;
            _itoa_s(wDTLDegree, acOutputDegree, 10, 10);
            if(wDTLDegree > 0)
            {
                sprintf(acOutImage_DTLBack, "%sDTL/DTL_Back_degree_+%d.bmp", acOutputImageFolder, wDTLDegree);
            }
            else
            {
                sprintf(acOutImage_DTLBack, "%sDTL/DTL_Back_degree_%d.bmp", acOutputImageFolder, wDTLDegree);
            }

#ifdef EXPORT_TRAIL_BAT
            cvCvtColor(aptSrcImg_DTL_Back[wDTLIndex], aptSrcImg_DTL_Back[wDTLIndex], CV_BGR2YCrCb);
            apucSrcImage_DTL_Back[wDTLIndex] = (UINT8*) aptSrcImg_DTL_Back[wDTLIndex]->imageData;
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
        720, 480, 3, g_EAGLEK3_tCommonCfg.ulMaxSteeringAngle, g_TRAILLINE_tCfg.uwSteeringAngleInterval);
#endif

    cvReleaseImage(&ptSrcImg_STL_Front);
    cvReleaseImage(&ptSrcImg_STL_Back);
    cvReleaseImage(&ptSrcImg_STL_Left);
    cvReleaseImage(&ptSrcImg_STL_Right);
    for(wDTLIndex = 0; wDTLIndex < g_TRAILLINE_tLineDataSet.uwDTLCount; wDTLIndex++)
    {
        cvReleaseImage(&(aptSrcImg_DTL_Front[wDTLIndex]));
        cvReleaseImage(&(aptSrcImg_DTL_Back[wDTLIndex]));
    }

#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

}

#endif // #if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC
