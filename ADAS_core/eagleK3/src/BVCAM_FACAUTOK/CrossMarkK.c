#include "BVCAM_FACAUTOK/CrossMarkK.h"
#include <assert.h>
#include "alMatrix.h"

/**
*  \addtogroup alCROSSMARKK
*  @{
*/

#if (alCROSSMARKK_DEBUG||BVCAM_FACAUTOK_FAIL_LOG)
INT32 g_lCAMID_AutoKDebug = 0, g_lROIID_AutoKDebug = 0;
#endif

/**
*  @}
*/

void	alCrossMarkK_Calibration(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucBuffer,
	alCROSSMARKK_Cfg *a_ptCfg,
	alCROSSMARKK_Parameter *a_ptParameter,
	UINT8 a_ucRefineFlag,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeM33CrossMarkK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 *a_peFPCrossMarkKX,
	FLOAT64 *a_peFPCrossMarkKY,
	UINT8 *a_pucCrossMarkKFlag
	)
{
	INT32 lPointIndex = 0, lImagW = 0, lImagH = 0, lIdealX = 0, lIdealY = 0, lDetectX = 0, lDetectY = 0;
	UINT8 *pucSBVBuffer = NULL, ucPassFlag = 1;
	BOOL abCrossMarkFlag[alCROSSMARKK_MAX_ROI] = { 0 };
    alRectINT32 tCurrentROI = {0};
	FLOAT64 eXTmp = 0, eYTmp = 0, eXSBV = 0, eYSBV = 0;
	FLOAT64 aeIdealX[alCROSSMARKK_MAX_ROI] = { 0 }, aeIdealY[alCROSSMARKK_MAX_ROI] = { 0 };
	FLOAT64 aeSBVX[alCROSSMARKK_MAX_ROI] = { 0 }, aeSBVY[alCROSSMARKK_MAX_ROI] = { 0 };
	FLOAT64 aeBVX[alCROSSMARKK_MAX_ROI] = { 0 }, aeBVY[alCROSSMARKK_MAX_ROI] = { 0 };
	FLOAT64 aeKX[alCROSSMARKK_MAX_ROI] = { 0 }, aeKY[alCROSSMARKK_MAX_ROI] = { 0 };
    alPointINT32 tImgSize = { 0 };
#if	(alCROSSMARKK_DEBUG || BVCAM_FACAUTOK_FAIL_LOG)&&alBVCAM_FACAUTOK_PC_DeBug
	FLOAT64 aeX[alCROSSMARKK_MAX_ROI] = { 0 }, aeY[alCROSSMARKK_MAX_ROI] = { 0 };
	FLOAT64 aeX1[alCROSSMARKK_MAX_ROI] = { 0 }, aeY1[alCROSSMARKK_MAX_ROI] = { 0 }, eScale = 0;
	INT32 lCamId = 0, lOffsetX = 0, lOffsetY = 0;
	UINT8 *pucSBV = NULL;
	IplImage * ptPicGray = NULL;
	IplImage * ptPicColor = NULL;
	char cText[MAX_PATH] = { 0 };
    alRectINT32 tCurrentROI_Bug = { 0 };
    IplImage * ptPicGrayBug = NULL;
#endif

    tImgSize.lX = a_ptParameter->ptFisheyeModel->uwSrcWidth;
    tImgSize.lY = a_ptParameter->ptFisheyeModel->uwSrcHeight;

	memset(abCrossMarkFlag, 0, sizeof(BOOL));

    if (a_pucBuffer == NULL)
    {
        pucSBVBuffer = (UINT8 *)malloc(tImgSize.lX * tImgSize.lY * sizeof(UINT8));
    }
    else
    {
        pucSBVBuffer = a_pucBuffer;
    }
    
	
    for (lPointIndex = 0; lPointIndex < a_ptCfg->lROINum ; lPointIndex++)
	{
        memset(pucSBVBuffer, 0, tImgSize.lX * tImgSize.lY * sizeof(UINT8));
		tCurrentROI = a_ptParameter->atCrossMarkROI[lPointIndex];

		if (a_ucRefineFlag) // PreK success
		{
			
			tCurrentROI.lLeft += a_ptCfg->atROICfg[lPointIndex].lSBVDetectOffsetX;
			tCurrentROI.lRight += a_ptCfg->atROICfg[lPointIndex].lSBVDetectOffsetX;
			tCurrentROI.lTop += a_ptCfg->atROICfg[lPointIndex].lSBVDetectOffsetY;
			tCurrentROI.lBottom += a_ptCfg->atROICfg[lPointIndex].lSBVDetectOffsetY;
		}

        COMMONK_SBVGeneratingK_YUYV2Y(
            a_ptBVImgSize,
			tCurrentROI, a_pucSrcBuffer,
			a_ptParameter->ptFisheyeModel, a_aeOriginalM33[0],
			a_ptParameter->lOriImgYLimit, a_ptParameter->lAngleCAM, a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
			a_ptCfg->atROICfg[lPointIndex].alSBVOffsetX, a_ptCfg->atROICfg[lPointIndex].alSBVOffsetY,
			a_ptCfg->atROICfg[lPointIndex].aeSBVScale, a_ptParameter->eMMPP,
			pucSBVBuffer
		);

		lImagW = tCurrentROI.lRight - tCurrentROI.lLeft + 1;
		lImagH = tCurrentROI.lBottom - tCurrentROI.lTop + 1;

        COMMONK_EnhanceImage(lImagW, lImagH, pucSBVBuffer, pucSBVBuffer);

#if	alCROSSMARKK_DEBUG
		switch (a_ptParameter->lAngleCAM)
		{
		case alBVCAM_FACAUTOK_BV_LEFT: // -90 degree
			lCamId = alCAMERAINFO_BV_LEFT;
			break;
		case alBVCAM_FACAUTOK_BV_RIGHT: // +90 degree
			lCamId = alCAMERAINFO_BV_RIGHT;
			break;
		case alBVCAM_FACAUTOK_BV_BACK: // 180 degree
			lCamId = alCAMERAINFO_BV_BACK;
			break;
		case alBVCAM_FACAUTOK_BV_FRONT:  // 0 degree
			lCamId = alCAMERAINFO_BV_FRONT;
			break;
		default:
			assert(0);
		}

#if 1
        if (lCamId == 0 && lPointIndex == 2)
        {
            tCurrentROI_Bug.lLeft = 0;
            tCurrentROI_Bug.lTop = 0;
            tCurrentROI_Bug.lRight = 719;
            tCurrentROI_Bug.lBottom = 479;
            ptPicGrayBug = cvCreateImage(cvSize(720, 480), IPL_DEPTH_8U, 1);
            COMMONK_SBVGeneratingK_YUYV2Y(
                a_ptBVImgSize,
                tCurrentROI_Bug, a_pucSrcBuffer,
                a_ptParameter->ptFisheyeModel, a_aeOriginalM33[0],
                a_ptParameter->lOriImgYLimit, a_ptParameter->lAngleCAM, a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
                a_ptCfg->atROICfg[lPointIndex].alSBVOffsetX, a_ptCfg->atROICfg[lPointIndex].alSBVOffsetY,
                a_ptCfg->atROICfg[lPointIndex].aeSBVScale, a_ptParameter->eMMPP,
                (UINT8*)ptPicGrayBug->imageData
                );
            sprintf_s(cText, MAX_PATH, "%salCROSSMARKK_SBV_debug_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, lPointIndex);
            cvSaveImage(cText, ptPicGrayBug, 0);
            cvReleaseImage(&ptPicGrayBug);
        }
#endif
		ptPicGray = cvCreateImage(cvSize(lImagW, lImagH), IPL_DEPTH_8U, 1);
        memcpy(ptPicGray->imageData, pucSBVBuffer, sizeof(UINT8)*ptPicGray->imageSize);

		sprintf_s(cText, MAX_PATH, "%salCROSSMARKK_SBV_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, lPointIndex);
		cvSaveImage(cText, ptPicGray, 0);
		cvReleaseImage(&ptPicGray);

		g_lCAMID_AutoKDebug = lCamId;
		g_lROIID_AutoKDebug = lPointIndex;
#endif

#if	(alBVCAM_FACAUTOK_PC_DeBug && BVCAM_FACAUTOK_FAIL_LOG)
		switch (a_ptParameter->lAngleCAM)
		{
		case alBVCAM_FACAUTOK_BV_LEFT: // -90 degree
            lCamId = alCAMERAINFO_BV_LEFT;
			break;
		case alBVCAM_FACAUTOK_BV_RIGHT: // +90 degree
            lCamId = alCAMERAINFO_BV_RIGHT;
			break;
		case alBVCAM_FACAUTOK_BV_BACK: // 180 degree
            lCamId = alCAMERAINFO_BV_BACK;
			break;
		case alBVCAM_FACAUTOK_BV_FRONT:  // 0 degree
            lCamId = alCAMERAINFO_BV_FRONT;
			break;
		default:
			assert(0);
		}
		g_lCAMID_AutoKDebug = lCamId;
		g_lROIID_AutoKDebug = lPointIndex;
#endif

		eXTmp = a_ptParameter->atIdealPointCrossMark[lPointIndex].lX;
		eYTmp = a_ptParameter->atIdealPointCrossMark[lPointIndex].lY;
		aeIdealX[lPointIndex] = a_ptParameter->atIdealPointCrossMark[lPointIndex].lX;
		aeIdealY[lPointIndex] = a_ptParameter->atIdealPointCrossMark[lPointIndex].lY;
		COMMONK_Birdview2SBV(
            a_ptBVImgSize->lX, a_ptBVImgSize->lY,
            tImgSize.lX, tImgSize.lY,
			1, a_ptParameter->lAngleCAM,
			a_ptParameter->lCamPosX,
			a_ptParameter->lCamPosY,
			a_ptCfg->atROICfg[lPointIndex].alSBVOffsetX,
			a_ptCfg->atROICfg[lPointIndex].alSBVOffsetY,
			a_ptCfg->atROICfg[lPointIndex].aeSBVScale,
			a_ptParameter->eMMPP,
			&eXTmp, &eYTmp,
			&eXSBV, &eYSBV
		);

		lIdealX = alROUND(eXSBV - tCurrentROI.lLeft);
		lIdealY = alROUND(eYSBV - tCurrentROI.lTop);

		abCrossMarkFlag[lPointIndex] = alCRSMRKDET_CrossMarkDetect(
            &a_ptCfg->atCrossMarkDetCfg[lPointIndex],
            tCurrentROI, pucSBVBuffer, lImagW, lImagH,
			lIdealX, lIdealY, &lDetectX, &lDetectY
			);
		aeSBVX[lPointIndex] = lDetectX + tCurrentROI.lLeft;
		aeSBVY[lPointIndex] = lDetectY + tCurrentROI.lTop;
		ucPassFlag *= abCrossMarkFlag[lPointIndex];

#if	alCROSSMARKK_DEBUG
		switch (a_ptParameter->lAngleCAM)
		{
		case alBVCAM_FACAUTOK_BV_LEFT: // -90 degree
			lCamId = alCAMERAINFO_BV_LEFT;
			break;
		case alBVCAM_FACAUTOK_BV_RIGHT: // +90 degree
			lCamId = alCAMERAINFO_BV_RIGHT;
			break;
		case alBVCAM_FACAUTOK_BV_BACK: // 180 degree
			lCamId = alCAMERAINFO_BV_BACK;
			break;
		case alBVCAM_FACAUTOK_BV_FRONT:  // 0 degree
			lCamId = alCAMERAINFO_BV_FRONT;
			break;
		default:
			assert(0);
		}
		sprintf_s(cText, MAX_PATH, "%salCROSSMARKK_SBV_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, lPointIndex);
		ptPicGray = cvLoadImage(cText, CV_LOAD_IMAGE_COLOR);

		cvLine(ptPicGray, cvPoint(lIdealX - 3, lIdealY), cvPoint(lIdealX + 3, lIdealY), CV_RGB(0, 255, 0), 1, CV_AA, 0);
		cvLine(ptPicGray, cvPoint(lIdealX, lIdealY - 3), cvPoint(lIdealX, lIdealY + 3), CV_RGB(0, 255, 0), 1, CV_AA, 0);

		if (abCrossMarkFlag[lPointIndex])
		{
			cvLine(ptPicGray, cvPoint(lDetectX - 3, lDetectY), cvPoint(lDetectX + 3, lDetectY), CV_RGB(255, 255, 0), 1, CV_AA, 0);
			cvLine(ptPicGray, cvPoint(lDetectX, lDetectY - 3), cvPoint(lDetectX, lDetectY + 3), CV_RGB(255, 255, 0), 1, CV_AA, 0);
		}
		sprintf_s(cText, MAX_PATH, "%salCROSSMARKK_Detect_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, lPointIndex);
		cvSaveImage(cText, ptPicGray, 0);
		cvReleaseImage(&ptPicGray);
#endif

	}


	if (ucPassFlag)
	{ // 每個點都偵測到 generate M33
		*a_pucCrossMarkKFlag = TRUE;
		for (lPointIndex = 0; lPointIndex < a_ptCfg->lROINum; lPointIndex++)
		{
			// SBV to BV
			COMMONK_SBV2Birdview(
                tImgSize.lX, tImgSize.lY, a_ptBVImgSize->lX, a_ptBVImgSize->lY,
				1, a_ptParameter->lAngleCAM, a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
				a_ptCfg->atROICfg[lPointIndex].alSBVOffsetX, a_ptCfg->atROICfg[lPointIndex].alSBVOffsetY, a_ptCfg->atROICfg[lPointIndex].aeSBVScale,
				a_ptParameter->eMMPP,
				aeSBVX + lPointIndex, aeSBVY + lPointIndex, aeBVX + lPointIndex, aeBVY + lPointIndex
			);

			// 計算反魚眼座標 >> BV to DeFishEye domain
			COMMONK_PerformCoordinatesTransform(
				a_aeOriginalM33[0], aeBVX[lPointIndex], aeBVY[lPointIndex],
				&aeKX[lPointIndex], &aeKY[lPointIndex]
			);
		}
		
		// generate M33
		if (!COMMONK_GenerateM3x3(aeKX, aeKY, aeIdealX, aeIdealY, a_ptCfg->lROINum, a_aeM33CrossMarkK[0]))
		{
			assert(0);
		}
		memcpy(a_aeM33CrossMarkK[1], a_aeM33CrossMarkK[0], sizeof(FLOAT64) * 9);
        alMATRIX_InverseNbyN(a_aeM33CrossMarkK[1], 3);

		memcpy(a_peFPCrossMarkKX, aeKX, alCROSSMARKK_MAX_ROI * sizeof(FLOAT64));
		memcpy(a_peFPCrossMarkKY, aeKY, alCROSSMARKK_MAX_ROI * sizeof(FLOAT64));

	}
	else
	{ // fail >> use Original M33
		*a_pucCrossMarkKFlag = FALSE;
		memcpy(a_aeM33CrossMarkK[0], a_aeOriginalM33[0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
		memcpy(a_aeM33CrossMarkK[1], a_aeOriginalM33[1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
	}

    if (a_pucBuffer == NULL)
    {
        free(pucSBVBuffer);
    }
}
