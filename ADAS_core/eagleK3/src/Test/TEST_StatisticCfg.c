
#include "Core/ModeDefine.h"

#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC

#include <assert.h>
#include <sys/stat.h>
#include <locale.h>

#include "AVM2D/AVM2DDef.h"
#include "Statistic/Statistic_Def.h"
#include "DataOperation/FileOperation.h"
#include "Camera/CameraDef.h"

#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

#include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

void TEST_ExportBVMeanROIImage(wchar_t * a_pwcOutImageFolder)
{
#if EAGLEK3_INCLUDE_OPENCV_TEST == 1
    INT32 i, j;

	char acOutputImageFolder[MAX_PATH];
    char acOutputImageFile[MAX_PATH];
    CvScalar color_R= CV_RGB(255,0,0), color_B= CV_RGB(0,0,255);
	UINT16 wPt1_x = 0, wPt1_y = 0, wPt2_x = 0, wPt2_y = 0;

    IplImage* ptOutputImg = cvCreateImage(cvSize( g_AVM2D_tParams.tBirdViewAreaSize.X, g_AVM2D_tParams.tBirdViewAreaSize.Y), IPL_DEPTH_8U,  3);

    wprintf(L"\nGenerate test images for Statistic ROIs .\n\n");

	memset(ptOutputImg->imageData,0, g_AVM2D_tParams.tBirdViewAreaSize.X* g_AVM2D_tParams.tBirdViewAreaSize.Y*3);


	wPt1_x = g_AVM2D_tParams.tCarPicCornerPos.X - g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt1_y = g_AVM2D_tParams.tCarPicCornerPos.Y  - g_AVM2D_tParams.tBirdViewStartPoint.Y;
	wPt2_x = wPt1_x  + g_AVM2D_tParams.tCarPicAreaSize.X ;
	wPt2_y = wPt1_y  + g_AVM2D_tParams.tCarPicAreaSize.Y;
	cvRectangle(ptOutputImg,cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_B, 1, 8, 0);

	wPt1_x = g_AVM2D_tParams.atStitchPoint_FrontLeft[0].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt1_y = g_AVM2D_tParams.atStitchPoint_FrontLeft[0].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	wPt2_x = g_AVM2D_tParams.atStitchPoint_FrontLeft[1].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt2_y = g_AVM2D_tParams.atStitchPoint_FrontLeft[1].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	cvLine(ptOutputImg, cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_B, 1, 8, 0);

	wPt1_x = g_AVM2D_tParams.atStitchPoint_FrontRight[0].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt1_y = g_AVM2D_tParams.atStitchPoint_FrontRight[0].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	wPt2_x = g_AVM2D_tParams.atStitchPoint_FrontRight[1].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt2_y = g_AVM2D_tParams.atStitchPoint_FrontRight[1].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	cvLine(ptOutputImg, cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_B, 1, 8, 0);

	wPt1_x = g_AVM2D_tParams.atStitchPoint_BackLeft[0].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt1_y = g_AVM2D_tParams.atStitchPoint_BackLeft[0].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	wPt2_x = g_AVM2D_tParams.atStitchPoint_BackLeft[1].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt2_y = g_AVM2D_tParams.atStitchPoint_BackLeft[1].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	cvLine(ptOutputImg, cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_B, 1, 8, 0);

	wPt1_x = g_AVM2D_tParams.atStitchPoint_BackRight[0].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt1_y = g_AVM2D_tParams.atStitchPoint_BackRight[0].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	wPt2_x = g_AVM2D_tParams.atStitchPoint_BackRight[1].X- g_AVM2D_tParams.tBirdViewStartPoint.X;
	wPt2_y = g_AVM2D_tParams.atStitchPoint_BackRight[1].Y - g_AVM2D_tParams.tBirdViewStartPoint.Y ;
	cvLine(ptOutputImg, cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_B, 1, 8, 0);

	for (i = 0; i < EAGLEK3_NUM_BV_CHANNEL; i++)
	{

		if (g_STATISTIC_tCfg.atBirdViewMeanCalInfo[i].ucFunctionEnabled == 1)
		{
			UINT8 ucMeanCalROICnt= g_STATISTIC_tCfg.atBirdViewMeanCalInfo[i].ucROICnt_MeanCal;

			for (j = 0; j< ucMeanCalROICnt ;j++)
			{


				wPt1_x = g_STATISTIC_tCfg.atBirdViewMeanCalInfo[i].atROIStartPoints_MeanCal[j].X;
				wPt1_y = g_STATISTIC_tCfg.atBirdViewMeanCalInfo[i].atROIStartPoints_MeanCal[j].Y;
				wPt2_x = wPt1_x  + g_STATISTIC_tCfg.atBirdViewMeanCalInfo[i].atROIAreaSize_MeanCal[j].X ;
				wPt2_y = wPt1_y  + g_STATISTIC_tCfg.atBirdViewMeanCalInfo[i].atROIAreaSize_MeanCal[j].Y;
				cvRectangle(ptOutputImg,cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_R, 1, 8, 0);	
            }
		}
	
	}

    setlocale(LC_ALL, "cht");
    wcstombs(acOutputImageFolder, a_pwcOutImageFolder, MAX_PATH);
    setlocale(LC_ALL, "C");

    sprintf(acOutputImageFile, "%sStatistic_BVMeanROI.bmp", acOutputImageFolder);

	cvSaveImage(acOutputImageFile, ptOutputImg, 0);
#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1
}

void TEST_ExportSingleViewNoiseROIImage(wchar_t * a_pwcOutImageFolder)
{
#if EAGLEK3_INCLUDE_OPENCV_TEST == 1
    INT32 i, j;
	char acOutputImageFolder[MAX_PATH];
    char acOutputImageFile[MAX_PATH];

    CvScalar color_R= CV_RGB(255,0,0)/*, color_B= CV_RGB(0,0,255)*/;

	UINT16 wPt1_x = 0, wPt1_y = 0, wPt2_x = 0, wPt2_y = 0;


	for (i = 0; i < EAGLEK3_CAMERA_NUM; i++)
	{

		IplImage* ptOutputImg = cvCreateImage(cvSize( g_CAMK_atCameraCurrentParam[i].ulImageWidth,g_CAMK_atCameraCurrentParam[i].ulImageHeight), IPL_DEPTH_8U,  3);
		memset(ptOutputImg->imageData,0, g_CAMK_atCameraCurrentParam[i].ulImageWidth*g_CAMK_atCameraCurrentParam[i].ulImageHeight*3);
		
		if (g_STATISTIC_tCfg.atSingleViewNoiseCalInfo[i].ucFunctionEnabled == 1)
		{
			UINT8 ucNoiseCalROICnt= g_STATISTIC_tCfg.atSingleViewNoiseCalInfo[i].ucROICnt_NoiseCal;

			for (j = 0; j< ucNoiseCalROICnt ;j++)
			{
				wPt1_x = g_STATISTIC_tCfg.atSingleViewNoiseCalInfo[i].atROIStartPoints_NoiseCal[j].X;
				wPt1_y = g_STATISTIC_tCfg.atSingleViewNoiseCalInfo[i].atROIStartPoints_NoiseCal[j].Y;
				wPt2_x = wPt1_x  + g_STATISTIC_tCfg.atSingleViewNoiseCalInfo[i].atROIAreaSize_NoiseCal[j].X ;
				wPt2_y = wPt1_y  + g_STATISTIC_tCfg.atSingleViewNoiseCalInfo[i].atROIAreaSize_NoiseCal[j].Y;
				cvRectangle(ptOutputImg,cvPoint(wPt1_x, wPt1_y),cvPoint(wPt2_x, wPt2_y),color_R, 1, 8, 0);
			}

            setlocale(LC_ALL, "cht");
            wcstombs(acOutputImageFolder, a_pwcOutImageFolder, MAX_PATH);
            setlocale(LC_ALL, "C");

            sprintf(acOutputImageFile, "%sStatistic_SingleViewNoiseROI_%d.bmp", acOutputImageFolder, i);
    		
		    cvSaveImage(acOutputImageFile, ptOutputImg, 0);        
        }

	}
#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1
}

#endif // #if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC
