
// This file includes functions to test the trail line.

#include "Core/ModeDefine.h"
#include "basedef.h"

//#define EXPORT_TRAIL_BAT

#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC

#include <sys/stat.h>
#include <direct.h>
#include <locale.h>

#include "Camera/CameraDef.h"
#include "FisheyeModel/FisheyeModel_v2.h"

#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

#include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

void TEST_ExportUndistortedImage(wchar_t * a_pwcSrcImageFolder, wchar_t * a_pwcOutImageFolder, FLOAT32 a_fScale)
{
#if EAGLEK3_INCLUDE_OPENCV_TEST == 1

    char acSrcImageFolder[MAX_PATH];
    char acOutputImageFolder[MAX_PATH];
    char acFilePath_SrcImage[EAGLEK3_NUM_BV_CHANNEL][MAX_PATH];
    char acFilePath_OutImage[EAGLEK3_NUM_BV_CHANNEL][MAX_PATH];
    UINT8 ucCamIndx = 0;


    IplImage* ptSrcImg = 0;
    IplImage* ptDstImg = 0;

    INT32 lX, lY, lUndistX, lUnDistY, lDistX, lDistY;
    FLOAT64 eDistX, eDistY, eUnDistX, eUnDistY;

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

    ptDstImg = cvCreateImage(cvSize(EAGLEK3_MAX_DISPLAY_AREA_SIZE_X, EAGLEK3_MAX_DISPLAY_AREA_SIZE_Y), 8, 3);

    for(ucCamIndx = 0; ucCamIndx < EAGLEK3_NUM_BV_CHANNEL; ucCamIndx++)
    {
        ptSrcImg = cvLoadImage(acFilePath_SrcImage[ucCamIndx], CV_LOAD_IMAGE_COLOR);

        cvZero(ptDstImg);

        for(lY = 0; lY < g_EAGLEK3_tCommonCfg.tDisplayAreaSize.Y; lY++)
        {
            for(lX = 0; lX < g_EAGLEK3_tCommonCfg.tDisplayAreaSize.X; lX++)
            {
                if (lX == 640 && lY == 300 && ucCamIndx == 0)
                {
                    ucCamIndx = ucCamIndx;
                }
                eUnDistX = g_EAGLEK3_tCommonCfg.tDisplayStartPoint.X + alROUND((lX - (g_EAGLEK3_tCommonCfg.tDisplayAreaSize.X>>1)) / a_fScale + (g_EAGLEK3_tCommonCfg.tDisplayAreaSize.X>>1));
                eUnDistY = g_EAGLEK3_tCommonCfg.tDisplayStartPoint.Y + alROUND((lY - (g_EAGLEK3_tCommonCfg.tDisplayAreaSize.Y>>1)) / a_fScale + (g_EAGLEK3_tCommonCfg.tDisplayAreaSize.Y>>1));

                lUndistX = g_EAGLEK3_tCommonCfg.tDisplayStartPoint.X + lX;
                lUnDistY = g_EAGLEK3_tCommonCfg.tDisplayStartPoint.Y + lY;
                FM_v2_Undistorted2Distorted_PlanarPixel(&(g_FM_v2_atCameraFM[ucCamIndx]), eUnDistX, eUnDistY, &eDistX, &eDistY);
                lDistX = alROUND(eDistX);
                lDistY = alROUND(eDistY);

                if(lDistX >= 0 && lDistX < ptSrcImg->width && lDistY >= 0 && lDistY < ptSrcImg->height)
                {
                    memcpy(ptDstImg->imageData + (lUndistX*3) + lUnDistY * ptDstImg->widthStep,
                        ptSrcImg->imageData + (lDistX*3) + lDistY * ptSrcImg->widthStep,
                        3);
                }
            }
        }

        cvSaveImage(acFilePath_OutImage[ucCamIndx], ptDstImg, 0);
        cvReleaseImage(&ptSrcImg);
        ptSrcImg = 0;
    }

    cvReleaseImage(&ptDstImg);

    setlocale(LC_ALL, "C");

#endif //#if EAGLEK3_INCLUDE_OPENCV_TEST == 1
}

#endif //#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC
