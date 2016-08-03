
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK.h"
#include <math.h>       /* sqrt */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "alMatrix.h"

#if	alBVCAM_FACAUTOK_DEBUG
#include <direct.h> // for folder create
#include "alAVM2DK.h"   // add by ancre for debug log
alAVM2D_Params g_talAVM2D_ParamsTest;
alAVM2D_Cfg g_talAVM2D_CfgTest;
#endif

/**
*  \addtogroup alBVCAM_FACAUTOK
*  @{
*/

/** \brief Buffer for Y image*/
UINT8 *g_pucYBuffer = NULL;
UINT8 *g_apucYBufferView[COMMONK_NUM_BV_CHANNEL] = {0};

#if	alBVCAM_FACAUTOK_DEBUG
INT32 g_alBVCAM_FACAUTOKCnt = 0;
#endif


/** \brief BVCAM_FACAUTOK module Data*/
BVCAM_FACAUTOK_Data g_tBVCAM_FACAUTOK_Data;

/** \brief BVCAM_FACAUTOK module Cfg*/
BVCAM_FACAUTOK_CFG g_tBVCAM_FACAUTOK_Cfg;

/** \brief BVCAM_FACAUTOK module Parameter*/
BVCAM_FACAUTOK_Parameter g_tBVCAM_FACAUTOK_Parameter;

void alBVCAM_FACAUTOK_GenIdealFPofCrossMarkK(
    BVCAM_FACAUTOK_ChartCrossPointSet *a_ptFeildData,
    alCOMMONK_CommonCfg *a_ptCommonCfg, FLOAT32    a_fMMPP,
    FLOAT64 a_aeBVAutoKIdealFP_X[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK],
    FLOAT64 a_aeBVAutoKIdealFP_Y[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK]
    );



/**
\brief Auto Calibration by Rectangle Board (view by view) (2200).
\param a_pucBuffer [IN] Working Buffer
\param a_lBVCameraIndx [IN] camera index
\param a_pucSrcBuffer [IN] source Buffer of camera
\param a_aeOriginalM33 [IN] Original M33
\param a_aeM33RecK [OUT] RecK M33
\param a_aeFPRecKX [OUT] FP's X detected in this function
\param a_aeFPRecKY [OUT] FP's Y detected in this function
\param a_pucRecKFlag [OUT] RecTangleK Success Flag
*/
void	RectangleK(
    UINT8 *a_pucBuffer,
	INT32 a_lBVCameraIndx,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeM33RecK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeFPRecKX[BVCAM_FACAUTOK_MAX_POINT],
	FLOAT64 a_aeFPRecKY[BVCAM_FACAUTOK_MAX_POINT],
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
	UINT8  *a_pucRecKFlag
	);

/**
\brief Set ROI Refine Flag (2300).
\param a_ptData [IN] BV autoK data
\param a_lBVCameraIndx [IN] camera index
*/
void	SetROIRefineFlag(
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Data *a_ptData,
	INT32 a_lBVCameraIndx
	);

/**
\brief Auto Calibration by Cross mark (2400).
\param a_pucBuffer [IN] Working Buffer
\param a_lBVCameraIndx [IN] camera index
\param a_pucSrcBuffer [IN] source Buffer of camera
\param a_aeOriginalM33 [IN] Original M33
\param a_aeM33CrossMarkK [OUT] RecK M33
\param a_aeFPCrossMarkKX [OUT] FP's X detected in this function
\param a_aeFPCrossMarkKY [OUT] FP's Y detected in this function
\param a_pucCrossMarkKFlag [OUT] CrossMarkK Success Flag
*/
void	CrossMarkK(
    UINT8 *a_pucBuffer,
	INT32 a_lBVCameraIndx,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeM33CrossMarkK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeFPCrossMarkKX[BVCAM_FACAUTOK_MAX_POINT],
	FLOAT64 a_aeFPCrossMarkKY[BVCAM_FACAUTOK_MAX_POINT],
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    UINT8 a_aucROIRefineFlag[COMMONK_NUM_BV_CHANNEL],
	UINT8 *a_pucCrossMarkKFlag
	);

/**
\brief Auto Calibration Quality FineTune (2500).
\param a_pucWorkBuffer [IN] working Buffer for SBV etc....
\param a_pucSrcBufferFront [IN] source Buffer of Front camera
\param a_pucSrcBufferBack [IN] source Buffer of Back camera
\param a_pucSrcBufferLeft [IN] source Buffer of Left camera
\param a_pucSrcBufferRight [IN] source Buffer of Right camera
*/
void	QualityFineTune(
    UINT8 *a_pucWorkBuffer,
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    BVCAM_FACAUTOK_Data *a_ptData
	);

/**
\brief Quilty Index Calculation (2510 & 2530).
\param a_ucAnalyzingMode [IN] 0: first time 1: final
\param a_pucSrcBufferFront [IN] source Buffer of Front camera
\param a_pucSrcBufferBack [IN] source Buffer of Back camera
\param a_pucSrcBufferLeft [IN] source Buffer of Left camera
\param a_pucSrcBufferRight [IN] source Buffer of Right camera
*/
void QualityAnalyzing(
    UINT8 *a_pucBuffer,
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    BVCAM_FACAUTOK_Data *a_ptData
	);

/**
\brief FineTune By Quilty Index Calculation result(2520).
*/
void FineTuneM33(BVCAM_FACAUTOK_CFG *a_ptCfg, BVCAM_FACAUTOK_Parameter *a_ptParams, BVCAM_FACAUTOK_Data *a_ptData);

/**
\brief Set BVCAM_FACAUTOK Success Flag (2600).
\return a_pucAutoKSuccessFlag [OUT] else: faill 0: pass
*/
UINT32	SetAutoKSuccessFlag(BVCAM_FACAUTOK_Data *a_ptData);


/**
\brief Line Segment Detection for Rectangle K(2212).
\param a_pucYBuffer [IN] Y image buffer
\param a_pucLineSegBuffer [IN] Line Segment buffer
\param a_tROI [IN] Detect ROI
\param a_plNum [OUT] line number
\param a_peResult [OUT] Line Segment result
*/
void	LineSegDetectionQualityFineTune(
	UINT8 *a_pucYBuffer,
    UINT8 *a_pucLineSegBuffer,
	alRectINT32 a_tROI,
	INT32 *a_plNum,
	FLOAT64 **a_peResult
	);

/**
\brief Line extract
\param a_lCamId [IN] camera id
\param a_lROIId [IN] ROI id
\param a_peResult [OUT] line segment detection result
\param a_tROI [OUT] image ROI
\return 0: FAIL 1:SUCCESS
*/
INT32 LinePick_QualityFineTune(INT32 a_lCamId, INT32 a_lROIId, FLOAT64 *a_peResult, alRectINT32 a_tROI);

/**
\brief AutoK Result Log
*/
// void AutoKResultLog();

/**
*  @}
*/

static void AutoK_FPLog(BVCAM_FACAUTOK_Data *a_ptData)
{
    FILE *ptAutoK_FPLog = NULL;
    INT32 lViewCnt = 0, lCnt = 0;
    char acFile[MAX_PATH] = { 0 };

    sprintf(acFile, "FactoryAutoK_FP_log.txt", g_acalBVCAM_FACAUTOK_WorkingFolder);
    ptAutoK_FPLog = fopen(acFile, "w");


    fprintf(ptAutoK_FPLog, "RecK:\n");
    for (lViewCnt = 0; lViewCnt < BVCAM_FACAUTOK_MAX_CAM; lViewCnt++)
    {
        fprintf(ptAutoK_FPLog, "View%d:\n", lViewCnt);
        for (lCnt = 0; lCnt < alRECK_MAX_POINT_VIEW; lCnt++)
        {
            fprintf(ptAutoK_FPLog, "Point%d: (%.2f\t%.2f)\n", lViewCnt, a_ptData->aeFPRecKX[lViewCnt][lCnt], a_ptData->aeFPRecKY[lViewCnt][lCnt]);
        }
    }

    fprintf(ptAutoK_FPLog, "\n");
    fprintf(ptAutoK_FPLog, "CrossMarkK:\n");
    for (lViewCnt = 0; lViewCnt < BVCAM_FACAUTOK_MAX_CAM; lViewCnt++)
    {
        fprintf(ptAutoK_FPLog, "View%d:\n", lViewCnt);
        for (lCnt = 0; lCnt < BVCAM_FACAUTOK_MAX_POINT; lCnt++)
        {
            fprintf(ptAutoK_FPLog, "Point%d: (%.2f\t%.2f)\n", lViewCnt, a_ptData->aeFPCrossMarkKX[lViewCnt][lCnt], a_ptData->aeFPCrossMarkKY[lViewCnt][lCnt]);
        }
    }

    fclose(ptAutoK_FPLog);
}

void AutoKResultLog(UINT32 a_ulReturnFlag)
{
	FILE *ptAutoKResult = NULL;
	char acFile[MAX_PATH] = { 0 };
	INT32 i = 0, lIndex = 0;
	UINT32 ulTmp = 0;

    sprintf(acFile, "Factory AutoK Result.txt", g_acalBVCAM_FACAUTOK_WorkingFolder);
	ptAutoKResult = fopen(acFile, "w");

	// AutoK
	ulTmp = (a_ulReturnFlag & (1 << lIndex)) >> lIndex;
	if (ulTmp)
	{
		fprintf(ptAutoKResult, "FactoryAutoK: Fail\n");
	}
	else
	{
		fprintf(ptAutoKResult, "FactoryAutoK: Success\n");
	}
	lIndex++;

	// RecK
	for (i = 0; i < 4; i++)
	{
		ulTmp = (a_ulReturnFlag & (1 << lIndex)) >> lIndex;
		if (ulTmp)
		{
			fprintf(ptAutoKResult, "\tRecK_View%d: Fail\n", i);
		}
		else
		{
			fprintf(ptAutoKResult, "\tRecK_View%d: Success\n", i);
		}
		lIndex++;
	}

	// Cross Mark K
	for (i = 0; i < 4; i++)
	{
		ulTmp = (a_ulReturnFlag & (1 << lIndex)) >> lIndex;
		if (ulTmp)
		{
			fprintf(ptAutoKResult, "\tCrossMark_View%d: Fail\n", i);
		}
		else
		{
			fprintf(ptAutoKResult, "\tCrossMark_View%d: Success\n", i);
		}
		lIndex++;
	}
	// Quality FineTune
	for (i = 0; i < 4; i++)
	{
		ulTmp = (a_ulReturnFlag & (1 << lIndex)) >> lIndex;
		if (ulTmp)
		{
			fprintf(ptAutoKResult, "\t\tQuality FineTune_View%d: Fail\n", i);
		}
		else
		{
			fprintf(ptAutoKResult, "\t\tQuality FineTune_View%d: Success\n", i);
		}
		lIndex++;
	}


	fclose(ptAutoKResult);

}


INT32 LinePick_QualityFineTune(INT32 a_lCamId, INT32 a_lROIId, FLOAT64 *a_peResult, alRectINT32 a_tROI)
{
	INT32 lStart[2], lEnd[2];
	FLOAT64 aeRectangleTmp[10], eLength, eAngle, aeLengthTH[2], aeAngleTH[2];

	aeLengthTH[0] = 25;
	aeAngleTH[0] = 20;
	aeAngleTH[1] = 55;

	lStart[0] = alROUND(a_peResult[0]);
	lStart[1] = alROUND(a_peResult[1]);
	lEnd[0] = alROUND(a_peResult[2]);
	lEnd[1] = alROUND(a_peResult[3]);

	aeRectangleTmp[0] = lEnd[0] - lStart[0]; // x gap
	aeRectangleTmp[1] = lEnd[1] - lStart[1]; // y gap
	eLength = sqrt(aeRectangleTmp[0] * aeRectangleTmp[0] + aeRectangleTmp[1] * aeRectangleTmp[1]);	// length

	aeRectangleTmp[2] = atan2(aeRectangleTmp[1], aeRectangleTmp[0]);
	aeRectangleTmp[3] = aeRectangleTmp[2] * 180 / alPI;
	eAngle = (aeRectangleTmp[0]) ? (aeRectangleTmp[1]) ? fabs(atan(aeRectangleTmp[1] / aeRectangleTmp[0]) * 180 / alPI) : 0 : 90; // angle


	if (a_lCamId > 1)
	{	// vertical
		if (a_lROIId)
		{ // RIGHT
			if (lStart[1] > lEnd[1] && eLength > aeLengthTH[0] && eAngle > aeAngleTH[1] && a_tROI.lRight- lStart[0] > 5)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{	// LEFT
			if (lEnd[1] > lStart[1] && eLength > aeLengthTH[0] && eAngle > aeAngleTH[1] && lStart[0] - a_tROI.lLeft > 5)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
	else
	{
		if (lStart[0] > lEnd[0] && eLength > aeLengthTH[0] && eAngle < aeAngleTH[0] && lStart[1] - a_tROI.lTop > 5)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

void	LineSegDetectionQualityFineTune(
	UINT8 *a_pucYBuffer,
    UINT8 *a_pucLineSegBuffer,
	alRectINT32 a_tROI,
	INT32 *a_plNum,
	FLOAT64 **a_peResult
	)
{
	FLOAT64 *a_peResultTmp = NULL;
	FLOAT64 aeLineParameter[7] = { 0 };
	FLOAT64 *peLineSegImg = NULL;
	FLOAT64 eScale, eSigmaScale, eQuant, eAngleTH, eDetectTH, eDensity;
	INT32 lBinNum, x, y, llIndexROI, lIndexImg, lCnt = 0, lLineNum = 0, lWidth = 0, lHeight = 0;
	INT32 *lIMGbuffer = NULL;
	UINT8 ucPixel;

	aeLineParameter[0] = 0.5;	// image scale (0.8)
	aeLineParameter[1] = 0.8;	// sigma_scale (0.6)
	aeLineParameter[2] = 8.5;	// Bound to the quantization error on the gradient norm. (2.0)
	aeLineParameter[3] = 22.5;	//  22.5;	// Gradient angle tolerance in degrees. (22.5)
	aeLineParameter[4] = 0.0;	// Detection threshold: -log10(NFA) > log_eps (0.0)
	aeLineParameter[5] = 0.7;	// Minimal density of region points in rectangle. (0.7)
	aeLineParameter[6] = 1024;	// Number of bins in pseudo-ordering of gradient modulus. (1024)

	eScale = aeLineParameter[0];
	eSigmaScale = aeLineParameter[1];
	eQuant = aeLineParameter[2];
	eAngleTH = aeLineParameter[3];
	eDetectTH = aeLineParameter[4];
	eDensity = aeLineParameter[5];
	lBinNum = (INT32)aeLineParameter[6];

	lWidth = a_tROI.lRight + 1 - a_tROI.lLeft;
	lHeight = a_tROI.lBottom + 1 - a_tROI.lTop;

	/* create a double image buffer */
    if (a_pucLineSegBuffer == NULL)
    {
        peLineSegImg = (FLOAT64 *)malloc(lWidth * lHeight * sizeof(FLOAT64));
    }
    else
    {
        if (lWidth * lHeight * sizeof(FLOAT64) > alBVCAM_FACAUTOK_Else_WorkingBufferSize)
        {
            assert(0); //  區塊過大 原本只給400*400*8
        }
        else
        {
            peLineSegImg = (FLOAT64 *)a_pucLineSegBuffer;
        }
    }
    if (peLineSegImg == NULL)
	{
		fprintf(stderr, "error: not enough memory\n");
		exit(EXIT_FAILURE);
	}

	// copy  Y channel data to peLineSegImg buffer
	for (x = 0; x < lWidth; x++)
	{
		for (y = 0; y < lHeight; y++)
		{
			lIndexImg = x + y*lWidth;
			llIndexROI = x + y*lWidth;

			ucPixel = a_pucYBuffer[lIndexImg];

			peLineSegImg[llIndexROI] = (double)ucPixel;
		}
	}

	*a_peResult = LineSegmentDetection(
		a_plNum, peLineSegImg, lWidth, lHeight, eScale, eSigmaScale, eQuant,
		eAngleTH, eDetectTH, eDensity, lBinNum,
		NULL, NULL, NULL
		);

#if 1 // 換算回整張SBV的座標
	lLineNum = *a_plNum;
	a_peResultTmp = *a_peResult;
	for (lCnt = 0; lCnt < lLineNum; lCnt++)
	{
		a_peResultTmp[7 * lCnt] = a_peResultTmp[7 * lCnt] + a_tROI.lLeft;
		a_peResultTmp[7 * lCnt + 1] = a_peResultTmp[7 * lCnt + 1] + a_tROI.lTop;
		a_peResultTmp[7 * lCnt + 2] = a_peResultTmp[7 * lCnt + 2] + a_tROI.lLeft;
		a_peResultTmp[7 * lCnt + 3] = a_peResultTmp[7 * lCnt + 3] + a_tROI.lTop;
	}
#endif
    if (a_pucLineSegBuffer == NULL)
    {
        free((void *)peLineSegImg);	// buffer must be free !!!!!!!
    }
}

void GetYChannel(
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

void	RectangleK(
    UINT8 *a_pucBuffer,
	INT32 a_lBVCameraIndx,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeM33RecK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeFPRecKX[alRECK_MAX_POINT_VIEW],
	FLOAT64 a_aeFPRecKY[alRECK_MAX_POINT_VIEW],
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
	UINT8  *a_pucRecKFlag
	)
{
	alRECK_Calibration(
        &a_ptParams->tBVImgSize,
        a_pucBuffer,
        &a_ptCfg->atRecKCfg[a_lBVCameraIndx],				// alRECK_Cfg a_ptCfg,
        &a_ptParams->atRecKParameter[a_lBVCameraIndx],	// alRECK_Parameter a_ptParameter,
		a_pucSrcBuffer,
		a_aeOriginalM33,
		a_aeM33RecK,
		a_aeFPRecKX,
		a_aeFPRecKY,
		a_pucRecKFlag
	);
}

void	SetROIRefineFlag(
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Data *a_ptData,
	INT32 a_lBVCameraIndx
	)
{
	FLOAT64 aeX[4] = { 0 }, aeY[4] = { 0 };
	INT32 i = 0, lIndex = 0, j = 0, lROINum = 0;

	if (a_lBVCameraIndx > alCAMERAINFO_BV_RIGHT && a_ptData->aucRecKFlag[a_lBVCameraIndx])
	{ // 校正版太近 容易出錯
		lROINum = a_ptCfg->atRecKCfg[a_lBVCameraIndx].lROINum;
		for (j = 0; j < lROINum; j++)
		{
			for (i = 0; i < 4; i++)
			{
				aeX[lIndex >> 2] += a_ptData->aeFPRecKX[a_lBVCameraIndx][lIndex + i];
				aeY[lIndex >> 2] += a_ptData->aeFPRecKY[a_lBVCameraIndx][lIndex + i];
			}

			aeX[lIndex >> 2] /= 4;
			aeY[lIndex >> 2] /= 4;
			lIndex += 4;
		}

		if (a_lBVCameraIndx == alCAMERAINFO_BV_BACK)
		{
#if 1 // switch by ancre
			if (aeX[1] < aeX[0])
			{ // fail
				a_ptData->aucRecKFlag[a_lBVCameraIndx] = FALSE;
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][0], a_ptData->aeOriginalM33[a_lBVCameraIndx][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][1], a_ptData->aeOriginalM33[a_lBVCameraIndx][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
			}
#endif 
		}
		else if (a_lBVCameraIndx == alCAMERAINFO_BV_FRONT)
		{
#if 1 // switch by ancre

#if 0 //Nissan Chart
			if (aeY[0] < aeY[1] || aeY[0] < aeY[3] || aeX[0] > aeX[2] || aeX[0] > aeX[3])
			{ // 0 fail
				a_ptData->aucRecKFlag[a_lBVCameraIndx] = FALSE;
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][0], a_ptData->aeOriginalM33[a_lBVCameraIndx][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][1], a_ptData->aeOriginalM33[a_lBVCameraIndx][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
			}

			if (aeY[1] > aeY[0] || aeY[1] > aeY[2] || aeX[1] > aeX[2] || aeX[1] > aeX[3])
			{ // 1 fail
				a_ptData->aucRecKFlag[a_lBVCameraIndx] = FALSE;
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][0], a_ptData->aeOriginalM33[a_lBVCameraIndx][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][1], a_ptData->aeOriginalM33[a_lBVCameraIndx][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
			}

			if (aeY[2] < aeY[1] || aeY[2] < aeY[3] || aeX[2] < aeX[0] || aeX[2] < aeX[1])
			{ // 2 fail
				a_ptData->aucRecKFlag[a_lBVCameraIndx] = FALSE;
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][0], a_ptData->aeOriginalM33[a_lBVCameraIndx][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][1], a_ptData->aeOriginalM33[a_lBVCameraIndx][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
			}

			if (aeY[3] > aeY[0] || aeY[3] > aeY[2] || aeX[3] < aeX[0] || aeX[3] < aeX[1])
			{ // 3 fail
				a_ptData->aucRecKFlag[a_lBVCameraIndx] = FALSE;
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][0], a_ptData->aeOriginalM33[a_lBVCameraIndx][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
				memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][1], a_ptData->aeOriginalM33[a_lBVCameraIndx][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
			}
#else // AM AVM
            if (aeX[1] < aeX[0])
            { // fail
                a_ptData->aucRecKFlag[a_lBVCameraIndx] = FALSE;
                memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][0], a_ptData->aeOriginalM33[a_lBVCameraIndx][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
                memcpy(a_ptData->aeRecKM33[a_lBVCameraIndx][1], a_ptData->aeOriginalM33[a_lBVCameraIndx][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
            }
#endif

#endif 
		}
		else
		{
			assert(0);
		}
	}

	a_ptData->aucROIRefineFlag[a_lBVCameraIndx] = a_ptData->aucRecKFlag[a_lBVCameraIndx];
}

void	CrossMarkK(
    UINT8 *a_pucBuffer,
	INT32 a_lBVCameraIndx,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeM33CrossMarkK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeFPCrossMarkKX[BVCAM_FACAUTOK_MAX_POINT],
	FLOAT64 a_aeFPCrossMarkKY[BVCAM_FACAUTOK_MAX_POINT],
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    UINT8 a_aucROIRefineFlag[COMMONK_NUM_BV_CHANNEL],
	UINT8 *a_pucCrossMarkKFlag
	)
{
	alCrossMarkK_Calibration(
        &a_ptParams->tBVImgSize,
        a_pucBuffer,
        &a_ptCfg->atCrossMarkKCfg[a_lBVCameraIndx],
        &a_ptParams->atCrossMarkKParameter[a_lBVCameraIndx],
        a_aucROIRefineFlag[a_lBVCameraIndx],
		a_pucSrcBuffer,
		a_aeOriginalM33,
		a_aeM33CrossMarkK,
		a_aeFPCrossMarkKX,
		a_aeFPCrossMarkKY,
		a_pucCrossMarkKFlag
	);
}


void QualityAnalyzing(
    UINT8 *a_pucBuffer,
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    BVCAM_FACAUTOK_Data *a_ptData
	)
{
	UINT8 *pucYImageSBV = NULL, ucBVCameraIndx = 0, *apucSrcImage[4], *pucYImage = NULL, ucRegionIndx = 0;
	INT32 i = 0, alROI[8] = { 0 }, lLineNum = 0, j, alStart[2], alEnd[2], lLineType = 0, lROICnt = 0, lLineCnt = 0, lLineIndex = 0;
	INT32 alCntPassLine[8] = { 0 }, lPointIndx = 0, lImgW = 0, lImgH = 0, lMod = 0;
	FLOAT64 aeBVP_X[2], aeBVP_Y[2], aeSPP_X[2], aeSPP_Y[2], *peM33 = NULL;
	FLOAT64 *peLineDetectResult = NULL, aeTmpX[2], aeTmpY[2];
	FLOAT64 aeCalX[8], aeCalY[8], aeIdealX[8], aeIdealY[8];
	FLOAT64 aeCalXBV[8], aeCalYBV[8], aeIdealXBV[8], aeIdealYBV[8], aeAbsError[8] = { 0 }, aeCompareError[4] = { 0 };
	FLOAT32 fPPMM = 0;
	alCROSSMARKK_Point atStitchPoint[4], atStitchPointSBV[4], atIdealLine[4], atCallLine[4];
	alRectINT32 tROILine;
	alFM_v2_1_Model *ptFisheyeModel = NULL;
	INT32 lCamAngle = 0, lCamPosX = 0, lCamPosY = 0, lOffsetX = 0, lOffsetY = 0, lOriImgYLimit = 0;
	FLOAT64 eSBVScale = 0, eMMPP = 0;
    UINT8 aucCrossMarkFlag[4] = { 0 }, *pucSBVBuffer = NULL, *pucLineSegBuffer = NULL;
    alPointINT32 tImgSize = { 0 };
#if (alBVCAM_FACAUTOK_DEBUG || BVCAM_FACAUTOK_FAIL_LOG) && alBVCAM_FACAUTOK_PC_DeBug
	IplImage * ptPicGray = NULL;
	IplImage * ptPicGrayLine = NULL;
	FILE *file_t = NULL;
	char text1[MAX_PATH];
	FILE *pFile = NULL;
	UINT8 *pucYImageSBVTest = NULL;
#endif
#if alBVCAM_FACAUTOK_DEBUG  && alBVCAM_FACAUTOK_PC_DeBug
	alRectINT32 tROI;
    char text[MAX_PATH] = {0};
    char textCSV[MAX_PATH] = {0};
#endif
	
    // set working buffer
    if (a_pucBuffer != NULL)
    {
        pucSBVBuffer = a_pucBuffer;
        pucLineSegBuffer = a_pucBuffer + alBVCAM_FACAUTOK_SBV_WorkingBufferSize;
    }

	aucCrossMarkFlag[0] = a_ptData->aucCrossMarkKFlag[0];
	aucCrossMarkFlag[1] = a_ptData->aucCrossMarkKFlag[1];
	aucCrossMarkFlag[2] = a_ptData->aucCrossMarkKFlag[2];
	aucCrossMarkFlag[3] = a_ptData->aucCrossMarkKFlag[3];

	fPPMM = (FLOAT32)(1.0f / (a_ptParams->atCrossMarkKParameter[0].eMMPP)); // mmpp 4顆鏡頭都一樣
	
	apucSrcImage[0] = a_pucSrcBufferLeft;
	apucSrcImage[1] = a_pucSrcBufferRight;
	apucSrcImage[2] = a_pucSrcBufferFront;
	apucSrcImage[3] = a_pucSrcBufferBack;

	for (ucBVCameraIndx = 0; ucBVCameraIndx < COMMONK_NUM_BV_CHANNEL ; ucBVCameraIndx++)
	{
        tImgSize.lX = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].ptFisheyeModel->uwSrcWidth;
        tImgSize.lY = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].ptFisheyeModel->uwSrcHeight;
#if 1 
		if (aucCrossMarkFlag[ucBVCameraIndx] == 0)
		{ // 根本沒找到十字標 (Cross Mark K fail) >>  不分析
			a_ptData->aucQualityFineTuneFlag[ucBVCameraIndx] = 0;
			continue;
		}
#endif
		ptFisheyeModel = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].ptFisheyeModel;
		peM33 = a_ptData->aeCrossMarkKM33[ucBVCameraIndx][0];

		// assign ideal position for line etc.
		aeBVP_X[0] = a_ptParams->atFineTuneFP[ucBVCameraIndx][0].eX;
		aeBVP_Y[0] = a_ptParams->atFineTuneFP[ucBVCameraIndx][0].eY;
		aeBVP_X[1] = a_ptParams->atFineTuneFP[ucBVCameraIndx][1].eX;
		aeBVP_Y[1] = a_ptParams->atFineTuneFP[ucBVCameraIndx][1].eY;

		atStitchPoint[0].eX = a_ptParams->atStitchLine[ucBVCameraIndx][0].tStart.eX;
		atStitchPoint[0].eY = a_ptParams->atStitchLine[ucBVCameraIndx][0].tStart.eY;
		atStitchPoint[1].eX = a_ptParams->atStitchLine[ucBVCameraIndx][0].tEnd.eX;
		atStitchPoint[1].eY = a_ptParams->atStitchLine[ucBVCameraIndx][0].tEnd.eY;
		atStitchPoint[2].eX = a_ptParams->atStitchLine[ucBVCameraIndx][1].tStart.eX;
		atStitchPoint[2].eY = a_ptParams->atStitchLine[ucBVCameraIndx][1].tStart.eY;
		atStitchPoint[3].eX = a_ptParams->atStitchLine[ucBVCameraIndx][1].tEnd.eX;
		atStitchPoint[3].eY = a_ptParams->atStitchLine[ucBVCameraIndx][1].tEnd.eY;

        if (pucSBVBuffer == NULL)
        {
            pucYImageSBV = (UINT8 *)malloc(tImgSize.lX * tImgSize.lY * sizeof(UINT8));
        }
        else
        {
            pucYImageSBV = pucSBVBuffer;
        }

		// cal ideal and real line and Intercept Point with stitch line
		for (ucRegionIndx = 0; ucRegionIndx < BVCAM_FACAUTOK_MAX_POINT_FINETUNE; ucRegionIndx++)
		{
            memset(pucYImageSBV, 0, tImgSize.lX * tImgSize.lY * sizeof(UINT8));
			
			lPointIndx = ucRegionIndx * (a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].lROINum/2);
			lOriImgYLimit = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lOriImgYLimit;
			lCamAngle = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lAngleCAM;
			lCamPosX = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lCamPosX;
			lCamPosY = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lCamPosY;
			lOffsetX = a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].atROICfg[lPointIndx].alSBVOffsetX;
			lOffsetY = a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].atROICfg[lPointIndx].alSBVOffsetY;
			eSBVScale = a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].atROICfg[lPointIndx].aeSBVScale;
			eMMPP = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].eMMPP;

			COMMONK_Birdview2SBV(
                a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
                tImgSize.lX, tImgSize.lY, 1,
				lCamAngle, lCamPosX, lCamPosY,
				lOffsetX, lOffsetY, eSBVScale, eMMPP,
				&aeBVP_X[ucRegionIndx], &aeBVP_Y[ucRegionIndx],
				&aeSPP_X[ucRegionIndx], &aeSPP_Y[ucRegionIndx]
			);

			// set start and end point of stitch line
			for (j = 0; j < 2; j++)
			{
				aeTmpX[0] = atStitchPoint[ucRegionIndx * 2 + j].eX;
				aeTmpY[0] = atStitchPoint[ucRegionIndx * 2 + j].eY;

				COMMONK_Birdview2SBV(
                    a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
                    tImgSize.lX, tImgSize.lY, 1,
					lCamAngle, lCamPosX, lCamPosY,
					lOffsetX, lOffsetY, eSBVScale, eMMPP,
					&aeTmpX[0], &aeTmpY[0], &aeTmpX[1], &aeTmpY[1]
				);

				atStitchPointSBV[ucRegionIndx * 2 + j].eX = aeTmpX[1];
				atStitchPointSBV[ucRegionIndx * 2 + j].eY = aeTmpY[1];
			}

			// Set ideal line and ROI
			if (ucBVCameraIndx > 1)
			{
				atIdealLine[ucRegionIndx * 2].eX = aeSPP_X[ucRegionIndx];
				atIdealLine[ucRegionIndx * 2].eY = aeSPP_Y[ucRegionIndx] - alBVCAM_FACAUTOK_Q_Width;
				atIdealLine[ucRegionIndx * 2 + 1].eX = aeSPP_X[ucRegionIndx];
				atIdealLine[ucRegionIndx * 2 + 1].eY = aeSPP_Y[ucRegionIndx] + alBVCAM_FACAUTOK_Q_Width;

				tROILine.lLeft = alROUND(aeSPP_X[ucRegionIndx] - alBVCAM_FACAUTOK_Q_Height);
				tROILine.lTop = alROUND(aeSPP_Y[ucRegionIndx] - alBVCAM_FACAUTOK_Q_Width);
				tROILine.lRight = tROILine.lLeft + alBVCAM_FACAUTOK_Q_Height * 2;
				tROILine.lBottom = tROILine.lTop + alBVCAM_FACAUTOK_Q_Width * 2;
			}
			else
			{
				atIdealLine[ucRegionIndx * 2].eX = aeSPP_X[ucRegionIndx] - alBVCAM_FACAUTOK_Q_Width;
				atIdealLine[ucRegionIndx * 2].eY = aeSPP_Y[ucRegionIndx];
				atIdealLine[ucRegionIndx * 2 + 1].eX = aeSPP_X[ucRegionIndx] + alBVCAM_FACAUTOK_Q_Width;
				atIdealLine[ucRegionIndx * 2 + 1].eY = aeSPP_Y[ucRegionIndx];

				tROILine.lLeft = alROUND(aeSPP_X[ucRegionIndx] - alBVCAM_FACAUTOK_Q_Width);
				tROILine.lTop = alROUND(aeSPP_Y[ucRegionIndx] - alBVCAM_FACAUTOK_Q_Height);
				tROILine.lRight = tROILine.lLeft + alBVCAM_FACAUTOK_Q_Width * 2;
				tROILine.lBottom = tROILine.lTop + alBVCAM_FACAUTOK_Q_Height * 2;
			}
			lImgW = tROILine.lRight + 1 - tROILine.lLeft;
			lImgH = tROILine.lBottom + 1 - tROILine.lTop;
			lMod = lImgW % 4;

			if (lMod != 0)
			{ // ROI 寬不是4的倍數 輸出圖會有問題 >> 縮小
				tROILine.lRight -= lMod;
			}

			// Calculate Intercept Point of ideal line and stitch line
			COMMONK_InterceptPointCal_ByVector(
				atStitchPointSBV[ucRegionIndx * 2].eX, atStitchPointSBV[ucRegionIndx * 2].eY, atStitchPointSBV[ucRegionIndx * 2 + 1].eX, atStitchPointSBV[ucRegionIndx * 2 + 1].eY,
				atIdealLine[ucRegionIndx * 2].eX, atIdealLine[ucRegionIndx * 2].eY, atIdealLine[ucRegionIndx * 2 + 1].eX, atIdealLine[ucRegionIndx * 2 + 1].eY,
				&aeIdealX[ucBVCameraIndx * 2 + ucRegionIndx], &aeIdealY[ucBVCameraIndx * 2 + ucRegionIndx]
			);

#if alBVCAM_FACAUTOK_DEBUG > 0	// log Y image and line information
			tROI.lLeft = 0;
			tROI.lTop = 0;
            tROI.lRight = tImgSize.lX - 1;
            tROI.lBottom = tImgSize.lY - 1;

            pucYImageSBVTest = (UINT8 *)malloc(tImgSize.lX * tImgSize.lY * sizeof(UINT8));
            COMMONK_SBVGeneratingK_YUYV2Y(
                &a_ptParams->tBVImgSize,
				tROI, apucSrcImage[ucBVCameraIndx], ptFisheyeModel, peM33,
				lOriImgYLimit, lCamAngle, lCamPosX, lCamPosY,
				lOffsetX, lOffsetY, eSBVScale, eMMPP,
				pucYImageSBVTest
				);

            ptPicGray = cvCreateImage(cvSize(tImgSize.lX, tImgSize.lY), IPL_DEPTH_8U, 1);
			memcpy(ptPicGray->imageData, pucYImageSBVTest, sizeof(UINT8)*ptPicGray->imageSize);
			sprintf(text, "%salBVCAM_FACAUTOK_SBVQ_FULL_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, ucBVCameraIndx, ucRegionIndx);
			cvSaveImage(text, ptPicGray, 0);
			cvReleaseImage(&ptPicGray);
			free(pucYImageSBVTest);
#endif

			// SBV Generating By M33
            COMMONK_SBVGeneratingK_YUYV2Y(
                &a_ptParams->tBVImgSize,
				tROILine, apucSrcImage[ucBVCameraIndx], ptFisheyeModel, peM33,
				lOriImgYLimit, lCamAngle, lCamPosX, lCamPosY,
				lOffsetX, lOffsetY, eSBVScale, eMMPP,
				pucYImageSBV
			);
			
			lImgW = tROILine.lRight + 1 - tROILine.lLeft;
			lImgH = tROILine.lBottom + 1 - tROILine.lTop;

            //  for image enhance
            COMMONK_EnhanceImage(lImgW, lImgH, pucYImageSBV, pucYImageSBV);

			// Line Segment Detection in ROI for Quality analyzing
			lLineNum = 0;
			peLineDetectResult = NULL;
			LineSegDetectionQualityFineTune(
                pucYImageSBV, pucLineSegBuffer,
				tROILine, &lLineNum, &peLineDetectResult
			);

			atCallLine[ucRegionIndx * 2].eX = 0;
			atCallLine[ucRegionIndx * 2].eY = 0;
			atCallLine[ucRegionIndx * 2 + 1].eX = 0;
			atCallLine[ucRegionIndx * 2 + 1].eY = 0;
			aeCalX[ucBVCameraIndx * 2 + ucRegionIndx] = 0;
			aeCalY[ucBVCameraIndx * 2 + ucRegionIndx] = 0;

			for (lLineCnt = 0; lLineCnt < lLineNum; lLineCnt++)
			{
				lLineIndex = 7 * lLineCnt;
				alStart[0] = alROUND(peLineDetectResult[lLineIndex]);
				alStart[1] = alROUND(peLineDetectResult[lLineIndex + 1]);
				alEnd[0] = alROUND(peLineDetectResult[lLineIndex + 2]);
				alEnd[1] = alROUND(peLineDetectResult[lLineIndex + 3]);

				lLineType = LinePick_QualityFineTune(ucBVCameraIndx, ucRegionIndx, &peLineDetectResult[lLineIndex], tROILine);
				
				if (lLineType)
				{ // pass
					alCntPassLine[ucBVCameraIndx * 2 + ucRegionIndx]++;
					atCallLine[ucRegionIndx * 2].eX = peLineDetectResult[lLineIndex];
					atCallLine[ucRegionIndx * 2].eY = peLineDetectResult[lLineIndex + 1];
					atCallLine[ucRegionIndx * 2 + 1].eX = peLineDetectResult[lLineIndex + 2];
					atCallLine[ucRegionIndx * 2 + 1].eY = peLineDetectResult[lLineIndex + 3];

					// Set Intercept Point of real line and stitch line
					COMMONK_InterceptPointCal_ByVector(
						atStitchPointSBV[ucRegionIndx * 2].eX, atStitchPointSBV[ucRegionIndx * 2].eY, atStitchPointSBV[ucRegionIndx * 2 + 1].eX, atStitchPointSBV[ucRegionIndx * 2 + 1].eY,
						atCallLine[ucRegionIndx * 2].eX, atCallLine[ucRegionIndx * 2].eY, atCallLine[ucRegionIndx * 2 + 1].eX, atCallLine[ucRegionIndx * 2 + 1].eY,
						&aeCalX[ucBVCameraIndx * 2 + ucRegionIndx], &aeCalY[ucBVCameraIndx * 2 + ucRegionIndx]
					);
				}
			}

			
#if alBVCAM_FACAUTOK_DEBUG > 0	// log Y image and line information
			ptPicGray = cvCreateImage(cvSize(lImgW, lImgH), IPL_DEPTH_8U, 1);
			memcpy(ptPicGray->imageData, pucYImageSBV, sizeof(UINT8)*ptPicGray->imageSize);
			sprintf(text, "%salBVCAM_FACAUTOK_SBVQ_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, ucBVCameraIndx, ucRegionIndx);
			cvSaveImage(text, ptPicGray, 0);
			cvReleaseImage(&ptPicGray);

			// log real line result
			sprintf(text1, "%salBVCAM_FACAUTOK_SBVQ_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, ucBVCameraIndx, ucRegionIndx);
			ptPicGrayLine = cvLoadImage(text, CV_LOAD_IMAGE_COLOR);

			// draw real line
			alStart[0] = alROUND(atCallLine[ucRegionIndx * 2].eX) - tROILine.lLeft;
			alStart[1] = alROUND(atCallLine[ucRegionIndx * 2].eY) - tROILine.lTop;
			alEnd[0] = alROUND(atCallLine[ucRegionIndx * 2 + 1].eX) - tROILine.lLeft;
			alEnd[1] = alROUND(atCallLine[ucRegionIndx * 2 + 1].eY) - tROILine.lTop;
			cvLine(ptPicGrayLine, cvPoint(alStart[0], alStart[1]), cvPoint(alEnd[0], alEnd[1]), CV_RGB(255, 0, 0), 1, CV_AA, 0);

			sprintf(text1, "%salBVCAM_FACAUTOK_SBV_QLine_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, ucBVCameraIndx, ucRegionIndx);
			cvSaveImage(text1, ptPicGrayLine, 0);
			cvReleaseImage(&ptPicGrayLine);
#endif
			free(peLineDetectResult);
		}
		
        if (pucSBVBuffer == NULL)
        {
            free(pucYImageSBV);
        }
	}

#if 1
	// Tansfer Coordinate from SBV to BV 
	for (j = 0; j < 8; j++)
	{
		ucBVCameraIndx = j >> 1;
		ucRegionIndx = j % 2;
		lPointIndx = ucRegionIndx * (a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].lROINum / 2);
		lOriImgYLimit = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lOriImgYLimit;
		lCamAngle = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lAngleCAM;
		lCamPosX = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lCamPosX;
		lCamPosY = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].lCamPosY;
		lOffsetX = a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].atROICfg[lPointIndx].alSBVOffsetX;
		lOffsetY = a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].atROICfg[lPointIndx].alSBVOffsetY;
		eSBVScale = a_ptCfg->atCrossMarkKCfg[ucBVCameraIndx].atROICfg[lPointIndx].aeSBVScale;
		eMMPP = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].eMMPP;
        tImgSize.lX = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].ptFisheyeModel->uwSrcWidth;
        tImgSize.lY = a_ptParams->atCrossMarkKParameter[ucBVCameraIndx].ptFisheyeModel->uwSrcHeight;

		// Ideal
		COMMONK_SBV2Birdview(
            tImgSize.lX, tImgSize.lY, a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
			1, lCamAngle, lCamPosX, lCamPosY,
			lOffsetX, lOffsetY, eSBVScale, eMMPP,
			&aeIdealX[j], &aeIdealY[j],
			&aeIdealXBV[j], &aeIdealYBV[j]
		);

		// Real
		COMMONK_SBV2Birdview(
            tImgSize.lX, tImgSize.lY, a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
			1, lCamAngle, lCamPosX, lCamPosY,
			lOffsetX, lOffsetY, eSBVScale, eMMPP,
			&aeCalX[j], &aeCalY[j],
			&aeCalXBV[j], &aeCalYBV[j]
		);

		aeAbsError[j] = (alCntPassLine[j]) ? aeIdealXBV[j] - aeCalXBV[j] : 999;
		a_ptData->aeAbsluteError[j] = aeAbsError[j];
	}

	aeCompareError[0] = (alCntPassLine[4] && alCntPassLine[0]) ? aeCalXBV[4] - aeCalXBV[0] : 999;
	aeCompareError[1] = (alCntPassLine[5] && alCntPassLine[2]) ? aeCalXBV[5] - aeCalXBV[2] : 999;
	aeCompareError[2] = (alCntPassLine[7] && alCntPassLine[1]) ? aeCalXBV[7] - aeCalXBV[1] : 999;
	aeCompareError[3] = (alCntPassLine[6] && alCntPassLine[3]) ? aeCalXBV[6] - aeCalXBV[3] : 999;

	a_ptData->aucQualityFineTuneFlag[0] = (alCntPassLine[0] && alCntPassLine[1]) ? TRUE : FALSE;
	a_ptData->aucQualityFineTuneFlag[1] = (alCntPassLine[2] && alCntPassLine[3]) ? TRUE : FALSE;
	a_ptData->aucQualityFineTuneFlag[2] = (alCntPassLine[4] && alCntPassLine[5]) ? TRUE : FALSE;
	a_ptData->aucQualityFineTuneFlag[3] = (alCntPassLine[6] && alCntPassLine[7]) ? TRUE : FALSE;

	a_ptData->aeCompareError[0] = aeCompareError[0];
	a_ptData->aeCompareError[1] = aeCompareError[1];
	a_ptData->aeCompareError[2] = aeCompareError[2];
	a_ptData->aeCompareError[3] = aeCompareError[3];
#endif

#if FACTORYAUTOK_DEBUG > 0	// log quality result >> 絕對誤差
	sprintf(textCSV, "%squality/LOG AutoKQ_%d.txt", g_acalBVCAM_FACAUTOK_WorkingFolder, g_Cnt_Q);
	file_t = fopen(textCSV, "w+");
	for (j = 0; j < 8; j++)
	{
		fprintf(
			file_t, "%.1f\t%.1f\t%.1f\t%.1f\t%.2f\n",
			aeIdealXBV[j], aeIdealYBV[j], aeCalXBV[j], aeCalYBV[j],
			aeAbsError[j]
			);
	}
	fclose(file_t);
#endif

#if FACTORYAUTOK_DEBUG > 0	// log quality result
	sprintf(textCSV, "%squality/LOG AutoKQulity.csv", g_acalBVCAM_FACAUTOK_WorkingFolder);
	file_t = fopen(textCSV, "a+");
	fprintf(file_t, "%s,", g_acSourceImageFolder);
	fprintf(file_t, "%.2f,%.2f,%.2f,%.2f\n", aeCompareError[0], aeCompareError[1], aeCompareError[2], aeCompareError[3]);

	fclose(file_t);
	g_Cnt_Q++;
#endif
}

void FineTuneM33(BVCAM_FACAUTOK_CFG *a_ptCfg, BVCAM_FACAUTOK_Parameter *a_ptParams, BVCAM_FACAUTOK_Data *a_ptData)
{
	INT32 lCamId = 0, lErrorId = 0, lPointId = 0, lM33Flag = 0, i = 0;
	FLOAT64 *peM33_WtoI, *peM33_ItoW, eUndisX = 0, eUndisY, eBVX = 0, eBVY = 0, eUndisFixX = 0, eUndisFixY;
	FLOAT64 aeIdealX[alCROSSMARKK_MAX_ROI] = { 0 }, aeIdealY[alCROSSMARKK_MAX_ROI] = { 0 };
	UINT8 aucFineTuneFlag[4] = { 0 };

	aucFineTuneFlag[0] = a_ptData->aucQualityFineTuneFlag[0];
	aucFineTuneFlag[1] = a_ptData->aucQualityFineTuneFlag[1];
	aucFineTuneFlag[2] = a_ptData->aucQualityFineTuneFlag[2];
	aucFineTuneFlag[3] = a_ptData->aucQualityFineTuneFlag[3];
	
	// by 絕對誤差
	if (aucFineTuneFlag[0] && aucFineTuneFlag[1] && aucFineTuneFlag[2] && aucFineTuneFlag[3])
	{	// quality analyzing success
		for (lCamId = 0; lCamId < COMMONK_NUM_BV_CHANNEL; lCamId++)
		{
#if 0 // just for robust test ancre
			for (i = 0; i < 8; i++)
			{
				aeIdealX[i] = a_ptParams->atCrossMarkKParameter[lCamId].atIdealPointCrossMark[i].eX;
				aeIdealY[i] = a_ptParams->atCrossMarkKParameter[lCamId].atIdealPointCrossMark[i].eY;
			}
			peM33_WtoI = a_ptData->aeCrossMarkKM33[lCamId][0];
			peM33_ItoW = a_ptData->aeCrossMarkKM33[lCamId][1];
			for (i = 0; i < a_ptCfg->atCrossMarkKCfg[lCamId].lROINum; i++)
			{
				COMMONK_PerformCoordinatesTransform(
					peM33_WtoI, aeIdealX[i], aeIdealY[i], 
					&a_ptData->aeFPCrossMarkKX[lCamId][i], 
					&a_ptData->aeFPCrossMarkKY[lCamId][i]
				);
			}
#endif
			memcpy(a_ptData->aeFPFineTuneX[lCamId], a_ptData->aeFPCrossMarkKX[lCamId], alCROSSMARKK_MAX_ROI*sizeof(FLOAT64));
			memcpy(a_ptData->aeFPFineTuneY[lCamId], a_ptData->aeFPCrossMarkKY[lCamId], alCROSSMARKK_MAX_ROI*sizeof(FLOAT64));
		}
		
		for (lErrorId = 0; lErrorId < 8; lErrorId++)
		{
			lCamId = lErrorId >> 1;
			// lPointId = (lErrorId % 2) * 2;
			lPointId = (lErrorId % 2) * (a_ptCfg->atCrossMarkKCfg[lCamId].lROINum / 2);

			peM33_WtoI = a_ptData->aeCrossMarkKM33[lCamId][0];
			peM33_ItoW = a_ptData->aeCrossMarkKM33[lCamId][1];

			if (fabs(a_ptData->aeAbsluteError[lErrorId]))
			{ // 有誤差 >> 微調
				if (lErrorId < 4)
				{ // right or left >> 1次只調整1點
					eUndisX = a_ptData->aeFPCrossMarkKX[lCamId][lPointId];
					eUndisY = a_ptData->aeFPCrossMarkKY[lCamId][lPointId];

					COMMONK_PerformCoordinatesTransform(peM33_ItoW, eUndisX, eUndisY, &eBVX, &eBVY);

					eBVX = eBVX - a_ptData->aeAbsluteError[lErrorId];

					COMMONK_PerformCoordinatesTransform(peM33_WtoI, eBVX, eBVY, &eUndisFixX, &eUndisFixY);

					a_ptData->aeFPFineTuneX[lCamId][lPointId] = eUndisFixX;
					a_ptData->aeFPFineTuneY[lCamId][lPointId] = eUndisFixY;
				}
				else
				{ // 一次調整兩點
					// 第一點
					eUndisX = a_ptData->aeFPCrossMarkKX[lCamId][lPointId];
					eUndisY = a_ptData->aeFPCrossMarkKY[lCamId][lPointId];

					COMMONK_PerformCoordinatesTransform(peM33_ItoW, eUndisX, eUndisY, &eBVX, &eBVY);

					eBVX = eBVX - a_ptData->aeAbsluteError[lErrorId];

					COMMONK_PerformCoordinatesTransform(peM33_WtoI, eBVX, eBVY, &eUndisFixX, &eUndisFixY);

					a_ptData->aeFPFineTuneX[lCamId][lPointId] = eUndisFixX;
					a_ptData->aeFPFineTuneY[lCamId][lPointId] = eUndisFixY;

					// 第2點
					lPointId++;
					eUndisX = a_ptData->aeFPCrossMarkKX[lCamId][lPointId];
					eUndisY = a_ptData->aeFPCrossMarkKY[lCamId][lPointId];

					COMMONK_PerformCoordinatesTransform(peM33_ItoW, eUndisX, eUndisY, &eBVX, &eBVY);

					eBVX = eBVX - a_ptData->aeAbsluteError[lErrorId];

					COMMONK_PerformCoordinatesTransform(peM33_WtoI, eBVX, eBVY, &eUndisFixX, &eUndisFixY);

					a_ptData->aeFPFineTuneX[lCamId][lPointId] = eUndisFixX;
					a_ptData->aeFPFineTuneY[lCamId][lPointId] = eUndisFixY;
				}
			}
		}

		for (lCamId = 0; lCamId < COMMONK_NUM_BV_CHANNEL ; lCamId++)
		{
			peM33_WtoI = a_ptData->aeFineTuneKM33[lCamId][0];
			peM33_ItoW = a_ptData->aeFineTuneKM33[lCamId][1];

			for (i = 0; i < 8; i++)
			{
				aeIdealX[i] = a_ptParams->atCrossMarkKParameter[lCamId].atIdealPointCrossMark[i].lX;
				aeIdealY[i] = a_ptParams->atCrossMarkKParameter[lCamId].atIdealPointCrossMark[i].lY;
			}

			lM33Flag = COMMONK_GenerateM3x3(
				a_ptData->aeFPFineTuneX[lCamId], a_ptData->aeFPFineTuneY[lCamId], 
				aeIdealX, aeIdealY, a_ptCfg->atCrossMarkKCfg[lCamId].lROINum, peM33_WtoI);

			if (!lM33Flag)
			{
				assert(0);
			}

			memcpy(peM33_ItoW, peM33_WtoI, sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
            alMATRIX_InverseNbyN(peM33_ItoW, 3);
		}
	}
	else
	{ // quality analyzing fail
		for (lCamId = 0; lCamId < COMMONK_NUM_BV_CHANNEL; lCamId++)
		{
			memcpy(a_ptData->aeFineTuneKM33[lCamId][0], a_ptData->aeCrossMarkKM33[lCamId][0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
			memcpy(a_ptData->aeFineTuneKM33[lCamId][1], a_ptData->aeCrossMarkKM33[lCamId][1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
		}
	}


}

void	QualityFineTune(
    UINT8 *a_pucWorkBuffer,
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    BVCAM_FACAUTOK_Data *a_ptData
	)
{
	// 輸入影像已為灰階
	QualityAnalyzing(
        a_pucWorkBuffer,
		a_pucSrcBufferFront,
		a_pucSrcBufferBack,
		a_pucSrcBufferLeft,
		a_pucSrcBufferRight,
        a_ptCfg,
        a_ptParams,
        a_ptData
	);

    FineTuneM33(a_ptCfg, a_ptParams, a_ptData);
}

UINT32	SetAutoKSuccessFlag(BVCAM_FACAUTOK_Data *a_ptData)
{
	UINT8 i = 0, ucRecK = 0, ucCrossMark = 0, ucFineTune = 0;
	UINT32 ulReturnFlag = 0;

	for (i = 0; i < COMMONK_NUM_BV_CHANNEL ; i++)
	{
		ucRecK += a_ptData->aucRecKFlag[i];
		ucCrossMark += a_ptData->aucCrossMarkKFlag[i];
		ucFineTune += a_ptData->aucQualityFineTuneFlag[i];
	}


	if (ucFineTune != COMMONK_NUM_BV_CHANNEL)
	{
		ulReturnFlag = ulReturnFlag + 1;
	}
	ulReturnFlag += (!a_ptData->aucRecKFlag[0]) << 1;
	ulReturnFlag += (!a_ptData->aucRecKFlag[1]) << 2;
	ulReturnFlag += (!a_ptData->aucRecKFlag[2]) << 3;
	ulReturnFlag += (!a_ptData->aucRecKFlag[3]) << 4;

	ulReturnFlag += (!a_ptData->aucCrossMarkKFlag[0]) << 5;
	ulReturnFlag += (!a_ptData->aucCrossMarkKFlag[1]) << 6;
	ulReturnFlag += (!a_ptData->aucCrossMarkKFlag[2]) << 7;
	ulReturnFlag += (!a_ptData->aucCrossMarkKFlag[3]) << 8;

	ulReturnFlag += (!a_ptData->aucQualityFineTuneFlag[0]) << 9;
	ulReturnFlag += (!a_ptData->aucQualityFineTuneFlag[1]) << 10;
	ulReturnFlag += (!a_ptData->aucQualityFineTuneFlag[2]) << 11;
	ulReturnFlag += (!a_ptData->aucQualityFineTuneFlag[3]) << 12;

	return ulReturnFlag;
}

UINT32	alBVCAM_FACAUTOK_AutoK(
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
	FLOAT64 a_aeOriginalM33Left[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeOriginalM33Right[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeOriginalM33Front[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeOriginalM33Back[2][COMMONK_M33_ELEMENT_CNT],
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    BVCAM_FACAUTOK_Data *a_ptData
	)
{
	INT32 lCamID = 0;
	UINT32 uLAutoKSuccessFlag = 0;
    UINT8 *apucSrcBuffer[COMMONK_NUM_BV_CHANNEL] = { 0 }, *apucSrcBufferY[COMMONK_NUM_BV_CHANNEL] = { 0 }, ucAutoKSuccessFlag = 0;
	FLOAT64 (*apeInputM33)[2][9] = { 0 };
	FLOAT64 aeInputM33[4][2][9] = { 0 };
	FLOAT64 **apeTTTT = NULL;
    alPointINT32 tImgSize = { 0 };
	
#if	alBVCAM_FACAUTOK_DEBUG
	FILE *file_t = NULL;
	IplImage * ptPicGray = NULL;
    char cText[MAX_PATH] = { 0 }, textCSV[MAX_PATH] = {0};
	INT32 lCamId = 0;
	UINT8 *apucBVImg = NULL;
    alFM_v2_1_Model *aptFisheyeModel[COMMONK_NUM_BV_CHANNEL] = { 0 };
    alFM_v2_1_Model atFisheyeModel[COMMONK_NUM_BV_CHANNEL] = { 0 };
    alPointINT32 tBVImgSize = { 0 };
#endif
    

	apucSrcBuffer[0] = a_pucSrcBufferLeft;
	apucSrcBuffer[1] = a_pucSrcBufferRight;
	apucSrcBuffer[2] = a_pucSrcBufferFront;
	apucSrcBuffer[3] = a_pucSrcBufferBack;

	memcpy(a_ptData->aeOriginalM33[0], a_aeOriginalM33Left, sizeof(a_ptData->aeOriginalM33[0]));
	memcpy(a_ptData->aeOriginalM33[1], a_aeOriginalM33Right, sizeof(a_ptData->aeOriginalM33[1]));
	memcpy(a_ptData->aeOriginalM33[2], a_aeOriginalM33Front, sizeof(a_ptData->aeOriginalM33[2]));
    memcpy(a_ptData->aeOriginalM33[3], a_aeOriginalM33Back, sizeof(a_ptData->aeOriginalM33[3]));

#if	alBVCAM_FACAUTOK_DEBUG // gen BV of Current M33
    tBVImgSize.lX = g_talAVM2D_CfgTest.tDestImageBufferSize.lX;
    tBVImgSize.lY = g_talAVM2D_CfgTest.tDestImageBufferSize.lY;
    apucBVImg = (UINT8 *)malloc(tBVImgSize.lX * tBVImgSize.lY * sizeof(UINT8));
    aptFisheyeModel[0] = a_ptParams->atCrossMarkKParameter[0].ptFisheyeModel;
    aptFisheyeModel[1] = a_ptParams->atCrossMarkKParameter[1].ptFisheyeModel;
    aptFisheyeModel[2] = a_ptParams->atCrossMarkKParameter[2].ptFisheyeModel;
    aptFisheyeModel[3] = a_ptParams->atCrossMarkKParameter[3].ptFisheyeModel;

    memcpy(&atFisheyeModel[0], aptFisheyeModel[0], sizeof(alFM_v2_1_Model));
    memcpy(&atFisheyeModel[1], aptFisheyeModel[1], sizeof(alFM_v2_1_Model));
    memcpy(&atFisheyeModel[2], aptFisheyeModel[2], sizeof(alFM_v2_1_Model));
    memcpy(&atFisheyeModel[3], aptFisheyeModel[3], sizeof(alFM_v2_1_Model));


    alBVCAM_FACAUTOK_InitialBuffer();
    for (lCamID = 0; lCamID < COMMONK_NUM_BV_CHANNEL; lCamID++)
    {
        tImgSize.lX = atFisheyeModel[lCamID].uwSrcWidth;
        tImgSize.lY = atFisheyeModel[lCamID].uwSrcHeight;
        GetYChannel(
            tImgSize.lX, tImgSize.lY,
            apucSrcBuffer[lCamID], g_apucYBufferView[lCamID]
        );
        apucSrcBufferY[lCamID] = g_apucYBufferView[lCamID];

        ptPicGray = cvCreateImage(cvSize(tImgSize.lX, tImgSize.lY), IPL_DEPTH_8U, 1);
        memcpy(ptPicGray->imageData, apucSrcBufferY[lCamID], sizeof(UINT8)*ptPicGray->imageSize);
        sprintf(cText, "%salBVCAM_FACAUTOK_YImg_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamID);
        cvSaveImage(cText, ptPicGray, 0);
        cvReleaseImage(&ptPicGray);
    }

	ptPicGray = cvCreateImage(cvSize(tBVImgSize.lX, tBVImgSize.lY), IPL_DEPTH_8U, 1);
		
	alAVM2D_alAVM2DGeneratingByM33_GrayLevel(
        apucSrcBufferY[2],
        apucSrcBufferY[3],
        apucSrcBufferY[0],
        apucSrcBufferY[1],
		a_ptData->aeOriginalM33[0][0],
		a_ptData->aeOriginalM33[1][0],
		a_ptData->aeOriginalM33[2][0],
		a_ptData->aeOriginalM33[3][0],
		apucBVImg,
        &g_talAVM2D_ParamsTest,
        &g_talAVM2D_CfgTest,
        atFisheyeModel
	);

	memcpy(ptPicGray->imageData, apucBVImg, sizeof(UINT8)*ptPicGray->imageSize);
	sprintf(cText, "%salBVCAM_FACAUTOK_Current_BV.jpg", g_acalBVCAM_FACAUTOK_OutputFolder);
	cvSaveImage(cText, ptPicGray, 0);

	cvReleaseImage(&ptPicGray);
	free(apucBVImg);
    alBVCAM_FACAUTOK_FreeBuffer();
#endif

	for (lCamID = 0; lCamID < COMMONK_NUM_BV_CHANNEL; lCamID++)
	{
		RectangleK(
            a_ptData->pucWorkingBuffer, lCamID,
            apucSrcBuffer[lCamID],
			a_ptData->aeOriginalM33[lCamID], 
			a_ptData->aeRecKM33[lCamID], 
			a_ptData->aeFPRecKX[lCamID],
			a_ptData->aeFPRecKY[lCamID], 
            a_ptCfg,
            a_ptParams,
			&a_ptData->aucRecKFlag[lCamID] 
		);

        SetROIRefineFlag(a_ptCfg, a_ptData, lCamID);

#if 0 // just for robust test
		a_ptData->aucRecKFlag[lCamID] = 0;
		a_ptData->aucROIRefineFlag[lCamID] = 0;
#endif

		CrossMarkK(
            a_ptData->pucWorkingBuffer, lCamID,
            apucSrcBuffer[lCamID],
			a_ptData->aeRecKM33[lCamID],
			a_ptData->aeCrossMarkKM33[lCamID],
			a_ptData->aeFPCrossMarkKX[lCamID],
			a_ptData->aeFPCrossMarkKY[lCamID],
            a_ptCfg, a_ptParams,
            a_ptData->aucROIRefineFlag,
			&a_ptData->aucCrossMarkKFlag[lCamID]
		);
	}

#if	alBVCAM_FACAUTOK_DEBUG
    alBVCAM_FACAUTOK_InitialBuffer();

    for (lCamID = 0; lCamID < COMMONK_NUM_BV_CHANNEL; lCamID++)
    {
        GetYChannel(
            tImgSize.lX, tImgSize.lY,
            apucSrcBuffer[lCamID], g_apucYBufferView[lCamID]
            );
        apucSrcBufferY[lCamID] = g_apucYBufferView[lCamID];
    }

	if (a_ptData->aucRecKFlag[0] && a_ptData->aucRecKFlag[1] && 
		a_ptData->aucRecKFlag[2] && a_ptData->aucRecKFlag[3])
	{
		ptPicGray = cvCreateImage(cvSize(tBVImgSize.lX, tBVImgSize.lY), IPL_DEPTH_8U, 1);

		apucBVImg = (UINT8 *)malloc(tBVImgSize.lX * tBVImgSize.lY * sizeof(UINT8));
		alAVM2D_alAVM2DGeneratingByM33_GrayLevel(
            apucSrcBufferY[2], apucSrcBufferY[3],
            apucSrcBufferY[0], apucSrcBufferY[1],
			a_ptData->aeRecKM33[0][0], a_ptData->aeRecKM33[1][0],
			a_ptData->aeRecKM33[2][0], a_ptData->aeRecKM33[3][0],
			apucBVImg, &g_talAVM2D_ParamsTest,
            &g_talAVM2D_CfgTest, atFisheyeModel
		);

		memcpy(ptPicGray->imageData, apucBVImg, sizeof(UINT8)*ptPicGray->imageSize);
		sprintf(cText, "%salBVCAM_FACAUTOK_PreK_BV.jpg", g_acalBVCAM_FACAUTOK_OutputFolder);
		cvSaveImage(cText, ptPicGray, 0);

		cvReleaseImage(&ptPicGray);
		free(apucBVImg);
	}

	if (a_ptData->aucCrossMarkKFlag[0] && a_ptData->aucCrossMarkKFlag[1] &&
		a_ptData->aucCrossMarkKFlag[2] && a_ptData->aucCrossMarkKFlag[3])
	{
		ptPicGray = cvCreateImage(cvSize(tBVImgSize.lX, tBVImgSize.lY), IPL_DEPTH_8U, 1);

		apucBVImg = (UINT8 *)malloc(tBVImgSize.lX * tBVImgSize.lY * sizeof(UINT8));
		alAVM2D_alAVM2DGeneratingByM33_GrayLevel(
            apucSrcBufferY[2], // apucSrcBuffer[2],
            apucSrcBufferY[3], // apucSrcBuffer[3],
            apucSrcBufferY[0], // apucSrcBuffer[0],
            apucSrcBufferY[1], // apucSrcBuffer[1],
			a_ptData->aeCrossMarkKM33[0][0],
			a_ptData->aeCrossMarkKM33[1][0],
			a_ptData->aeCrossMarkKM33[2][0],
			a_ptData->aeCrossMarkKM33[3][0],
			apucBVImg,
            &g_talAVM2D_ParamsTest,
            &g_talAVM2D_CfgTest,
            atFisheyeModel
			);

		memcpy(ptPicGray->imageData, apucBVImg, sizeof(UINT8)*ptPicGray->imageSize);
		sprintf(cText, "%salBVCAM_FACAUTOK_2ndK_BV.jpg", g_acalBVCAM_FACAUTOK_OutputFolder);
		cvSaveImage(cText, ptPicGray, 0);

		/*sprintf(cText, "%sBV_2ndK/alBVCAM_FACAUTOK_2ndK_BV_%d.jpg", g_acalBVCAM_FACAUTOK_WorkingFolder, g_alBVCAM_FACAUTOKCnt);
		cvSaveImage(cText, ptPicGray, 0);*/

		cvReleaseImage(&ptPicGray);
		free(apucBVImg);
	}
    alBVCAM_FACAUTOK_FreeBuffer();
#endif
	QualityFineTune(
        a_ptData->pucWorkingBuffer,
        apucSrcBuffer[2],
        apucSrcBuffer[3],
        apucSrcBuffer[0],
        apucSrcBuffer[1],
        a_ptCfg,
        a_ptParams,
        a_ptData
	);

#if	alBVCAM_FACAUTOK_DEBUG
    alBVCAM_FACAUTOK_InitialBuffer();

    for (lCamID = 0; lCamID < COMMONK_NUM_BV_CHANNEL; lCamID++)
    {
        GetYChannel(
            tImgSize.lX, tImgSize.lY,
            apucSrcBuffer[lCamID], g_apucYBufferView[lCamID]
            );
        apucSrcBufferY[lCamID] = g_apucYBufferView[lCamID];
    }

	if (a_ptData->aucQualityFineTuneFlag[0] && a_ptData->aucQualityFineTuneFlag[1] &&
		a_ptData->aucQualityFineTuneFlag[2] && a_ptData->aucQualityFineTuneFlag[3])
	{
		ptPicGray = cvCreateImage(cvSize(tBVImgSize.lX, tBVImgSize.lY), IPL_DEPTH_8U, 1);

		apucBVImg = (UINT8 *)malloc(tBVImgSize.lX * tBVImgSize.lY * sizeof(UINT8));
		alAVM2D_alAVM2DGeneratingByM33_GrayLevel(
            apucSrcBufferY[2],
            apucSrcBufferY[3],
            apucSrcBufferY[0],
            apucSrcBufferY[1],
			a_ptData->aeFineTuneKM33[0][0],
			a_ptData->aeFineTuneKM33[1][0],
			a_ptData->aeFineTuneKM33[2][0],
			a_ptData->aeFineTuneKM33[3][0],
			apucBVImg,
            &g_talAVM2D_ParamsTest,
            &g_talAVM2D_CfgTest,
            atFisheyeModel
		);

		memcpy(ptPicGray->imageData, apucBVImg, sizeof(UINT8)*ptPicGray->imageSize);
		sprintf(cText, "%salBVCAM_FACAUTOK_FineTune_BV.jpg", g_acalBVCAM_FACAUTOK_OutputFolder);
		cvSaveImage(cText, ptPicGray, 0);

		cvReleaseImage(&ptPicGray);
		free(apucBVImg);
	}
    alBVCAM_FACAUTOK_FreeBuffer();
#endif

    uLAutoKSuccessFlag = SetAutoKSuccessFlag(a_ptData);

#if	(BVCAM_FACAUTOK_FAIL_LOG || alBVCAM_FACAUTOK_DEBUG_FW)
	// log
	AutoKResultLog(uLAutoKSuccessFlag);

    // log FP point
    AutoK_FPLog(a_ptData);
#endif


#if	alBVCAM_FACAUTOK_DEBUG
#if 0 // for pre k 
	sprintf(textCSV, "%sLOG_BVCAM_FACAUTOK_PreK.csv", g_acalBVCAM_FACAUTOK_WorkingFolder);
	file_t = fopen(textCSV, "a+");
	fprintf(file_t, "%s,", g_acalBVCAM_FACAUTOK_OutputFolder);
	fprintf(file_t, "%d,%d,%d,%d\n", a_ptData->aucRecKFlag[0], a_ptData->aucRecKFlag[1],
									a_ptData->aucRecKFlag[2], a_ptData->aucRecKFlag[3]);
	fclose(file_t);
#endif

#if 0 // for fine tune
	sprintf(textCSV, "%sLOG_BVCAM_FACAUTOK_Tune.csv", g_acalBVCAM_FACAUTOK_WorkingFolder);
	file_t = fopen(textCSV, "a+");
	fprintf(file_t, "%s,", g_acalBVCAM_FACAUTOK_OutputFolder);
	fprintf(file_t, "%d,%d,%d,%d\n", a_ptData->aucQualityFineTuneFlag[0], a_ptData->aucQualityFineTuneFlag[1],
		a_ptData->aucQualityFineTuneFlag[2], a_ptData->aucQualityFineTuneFlag[3]);
	fclose(file_t);
#endif

	g_alBVCAM_FACAUTOKCnt ++;
#endif
	return uLAutoKSuccessFlag;
}

void alBVCAM_FACAUTOK_InitialBuffer()
{
	/*g_apucYBufferView[0] = (UINT8 *)malloc(COMMONK_MAX_DISPLAY_AREA_SIZE_X * COMMONK_MAX_DISPLAY_AREA_SIZE_Y * sizeof(UINT8));
	g_apucYBufferView[1] = (UINT8 *)malloc(COMMONK_MAX_DISPLAY_AREA_SIZE_X * COMMONK_MAX_DISPLAY_AREA_SIZE_Y * sizeof(UINT8));
	g_apucYBufferView[2] = (UINT8 *)malloc(COMMONK_MAX_DISPLAY_AREA_SIZE_X * COMMONK_MAX_DISPLAY_AREA_SIZE_Y * sizeof(UINT8));
	g_apucYBufferView[3] = (UINT8 *)malloc(COMMONK_MAX_DISPLAY_AREA_SIZE_X * COMMONK_MAX_DISPLAY_AREA_SIZE_Y * sizeof(UINT8));*/

    g_apucYBufferView[0] = (UINT8 *)malloc(1280 * 720 * sizeof(UINT8));
    g_apucYBufferView[1] = (UINT8 *)malloc(1280 * 720 * sizeof(UINT8));
    g_apucYBufferView[2] = (UINT8 *)malloc(1280 * 720 * sizeof(UINT8));
    g_apucYBufferView[3] = (UINT8 *)malloc(1280 * 720 * sizeof(UINT8));

    memset(&g_tBVCAM_FACAUTOK_Parameter, 0, sizeof(BVCAM_FACAUTOK_Parameter));
}

void alBVCAM_FACAUTOK_FreeBuffer()
{
	free(g_apucYBufferView[0]);
	free(g_apucYBufferView[1]);
	free(g_apucYBufferView[2]);
	free(g_apucYBufferView[3]);
	g_apucYBufferView[0] = NULL;
	g_apucYBufferView[1] = NULL;
	g_apucYBufferView[2] = NULL;
	g_apucYBufferView[3] = NULL;
}

void alBVCAM_FACAUTOK_InitialByCFG(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucWorkingBuffer,
    BVCAM_FACAUTOK_Data *a_ptData,
	alFM_v2_1_Model *a_ptFisheyeModel, alAVM2D_Params *a_ptalAVM2D_Params,
	alPointINT32 a_tLeftTireCenter,
	INT32 *a_plCameraPosX, INT32 *a_plCameraPosY, INT32 *a_plOriImgYLimit,
    BVCAM_FACAUTOK_CalibrationFeildData *a_ptFeildData,
    FLOAT32    a_fMMPP,
    alCOMMONK_CommonCfg *a_ptCommonCfg,
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams
	)
{
	INT32 lCAMId = 0, lPointIndex = 0, i = 0, lPointNumView = 0, lPointIndexTmp = 0, lMod = 0;

    alPointINT32 tImgSize = { 0 };

	FLOAT64 aeXTmp[4] = { 0 }, aeYTmp[4] = { 0 }, aeXSBV[4] = { 0 }, aeYSBV[4] = { 0 }, eTmp = 0;

    FLOAT64 aeBVAutoKIdealFP_X[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK] = {0};
    FLOAT64 aeBVAutoKIdealFP_Y[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK] = {0};

    // set BV Size
    a_ptParams->tBVImgSize.lX = a_ptBVImgSize->lX;
    a_ptParams->tBVImgSize.lY = a_ptBVImgSize->lY;

    // set working buffer
    a_ptData->pucWorkingBuffer = a_pucWorkingBuffer;

	// for PreK
	for (lCAMId = 0; lCAMId < 4; lCAMId++)
	{
        tImgSize.lX = a_ptFisheyeModel[lCAMId].uwSrcWidth;
        tImgSize.lY = a_ptFisheyeModel[lCAMId].uwSrcHeight;

		a_ptParams->atRecKParameter[lCAMId].eMMPP = a_ptalAVM2D_Params->fMMPP;
		a_ptParams->atRecKParameter[lCAMId].ptFisheyeModel = a_ptFisheyeModel + lCAMId;
		a_ptParams->atRecKParameter[lCAMId].lCamPosX = a_plCameraPosX[lCAMId];
		a_ptParams->atRecKParameter[lCAMId].lCamPosY = a_plCameraPosY[lCAMId];
		a_ptParams->atRecKParameter[lCAMId].lOriImgYLimit = a_plOriImgYLimit[lCAMId];
		switch (lCAMId)
		{
		case alCAMERAINFO_BV_LEFT:
			a_ptParams->atRecKParameter[lCAMId].lAngleCAM = -90;
			break;
		case alCAMERAINFO_BV_RIGHT:
			a_ptParams->atRecKParameter[lCAMId].lAngleCAM = 90;
			break;
		case alCAMERAINFO_BV_FRONT:
			a_ptParams->atRecKParameter[lCAMId].lAngleCAM = 0;
			break;
		case  alCAMERAINFO_BV_BACK:
			a_ptParams->atRecKParameter[lCAMId].lAngleCAM = 180;
			break;
		default:
			assert(0);
			break;
		}

		lPointNumView = 0;
		for (i = 0; i < a_ptCfg->atRecKCfg[lCAMId].lROINum; i++)
		{
			lPointNumView += a_ptCfg->atRecKCfg[lCAMId].atROICfg[i].lPointNum;
		}

        

        // 以左前輪為基準點
		for (i = 0; i < lPointNumView; i++)
		{
			a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[i].eX 
                = (a_ptFeildData->tRECK_FeildData.atIdealFPRecK[lPointIndex + i].lX + a_tLeftTireCenter.lX) / a_ptalAVM2D_Params->fMMPP +
                (tImgSize.lX >> 1);

			a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[i].eY
                = (a_ptFeildData->tRECK_FeildData.atIdealFPRecK[lPointIndex + i].lY + a_tLeftTireCenter.lY) / a_ptalAVM2D_Params->fMMPP +
                (tImgSize.lY >> 1);

            a_ptParams->atRecKParameter[lCAMId].aucPointFlag[i] = a_ptFeildData->tRECK_FeildData.aucFlag[lPointIndex + i];
		}

		lPointIndexTmp = 0;
		for (i = 0; i < a_ptCfg->atRecKCfg[lCAMId].lROINum; i++)
		{
			aeXTmp[0] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp].eX;
			aeXTmp[1] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp + 1].eX;
			aeXTmp[2] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp + 2].eX;
			aeXTmp[3] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp + 3].eX;

			aeYTmp[0] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp].eY;
			aeYTmp[1] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp + 1].eY;
			aeYTmp[2] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp + 2].eY;
			aeYTmp[3] = a_ptParams->atRecKParameter[lCAMId].atIdealPointRectK[lPointIndexTmp + 3].eY;

			COMMONK_Birdview2SBV(
                a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
                tImgSize.lX, tImgSize.lY,
				4, a_ptParams->atRecKParameter[lCAMId].lAngleCAM,
				a_ptParams->atRecKParameter[lCAMId].lCamPosX,
				a_ptParams->atRecKParameter[lCAMId].lCamPosY,
				a_ptCfg->atRecKCfg[lCAMId].atROICfg[i].lSBVOffsetX,
				a_ptCfg->atRecKCfg[lCAMId].atROICfg[i].lSBVOffsetY,
				a_ptCfg->atRecKCfg[lCAMId].atROICfg[i].eSBVScale,
				a_ptParams->atRecKParameter[lCAMId].eMMPP,
				aeXTmp, aeYTmp,
				aeXSBV, aeYSBV
			);
#if 1 // 縮小偵測範圍
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lLeft = alROUND(aeXSBV[0] - 60);
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lTop = alROUND(aeYSBV[1] - 60);
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lRight = alROUND(aeXSBV[2] + 60);
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lBottom = alROUND(aeYSBV[0] + 60);
#else
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lLeft = alROUND(aeXSBV[0] - 80);
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lTop = alROUND(aeYSBV[1] - 60);
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lRight = alROUND(aeXSBV[2] + 80);
			a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lBottom = alROUND(aeYSBV[0] + 60);
#endif

			lMod = 1 + a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lRight - a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lLeft;
			lMod = lMod % 4;

			if (lMod != 0)
			{ // ROI 寬不是4的倍數 輸出圖會有問題 >> 縮小
				a_ptParams->atRecKParameter[lCAMId].atRecKROI[i].lRight -= lMod;
			}

			lPointIndexTmp += a_ptCfg->atRecKCfg[lCAMId].atROICfg[i].lPointNum;
		}
		lPointIndex += lPointNumView;
	}


	// For CrossMarkk
	for (lCAMId = 0; lCAMId < 4; lCAMId++)
	{
		a_ptParams->atCrossMarkKParameter[lCAMId].eMMPP = a_ptalAVM2D_Params->fMMPP;
		a_ptParams->atCrossMarkKParameter[lCAMId].ptFisheyeModel = a_ptFisheyeModel + lCAMId;
		a_ptParams->atCrossMarkKParameter[lCAMId].lCamPosX = a_plCameraPosX[lCAMId];
		a_ptParams->atCrossMarkKParameter[lCAMId].lCamPosY = a_plCameraPosY[lCAMId];
		a_ptParams->atCrossMarkKParameter[lCAMId].lOriImgYLimit = a_plOriImgYLimit[lCAMId];

        tImgSize.lX = a_ptFisheyeModel[lCAMId].uwSrcWidth;
        tImgSize.lY = a_ptFisheyeModel[lCAMId].uwSrcHeight;

		switch (lCAMId)
		{
		case alCAMERAINFO_BV_LEFT:
			a_ptParams->atCrossMarkKParameter[lCAMId].lAngleCAM = -90;
			break;
		case alCAMERAINFO_BV_RIGHT:
			a_ptParams->atCrossMarkKParameter[lCAMId].lAngleCAM = 90;
			break;
		case alCAMERAINFO_BV_FRONT:
			a_ptParams->atCrossMarkKParameter[lCAMId].lAngleCAM = 0;
			break;
		case  alCAMERAINFO_BV_BACK:
			a_ptParams->atCrossMarkKParameter[lCAMId].lAngleCAM = 180;
			break;
		default:
			assert(0);
			break;
		}


#if 0 // old
		
#else // current
        alBVCAM_FACAUTOK_GenIdealFPofCrossMarkK(
            &a_ptFeildData->tCrossmarkFeildData,
            a_ptCommonCfg, a_fMMPP,
            aeBVAutoKIdealFP_X,
            aeBVAutoKIdealFP_Y
        );

        if (lCAMId == alCAMERAINFO_BV_LEFT)
        {
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][1]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][1]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[1].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][3]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[1].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][3]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][0]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lY =
                alROUND(aeBVAutoKIdealFP_Y[lCAMId][0]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][4]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][4]);
        }
        else if (lCAMId == alCAMERAINFO_BV_RIGHT)
        {
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][0]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][0]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[1].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][2]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[1].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][2]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][1]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][1]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][4]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][4]);
        }
        else
        {
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][0]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][0]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[1].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][2]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[1].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][2]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][4]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][4]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][1]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][1]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[4].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][3]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[4].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][3]);

            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[5].lX = alROUND(aeBVAutoKIdealFP_X[lCAMId][5]);
            a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[5].lY = alROUND(aeBVAutoKIdealFP_Y[lCAMId][5]);
        }
#endif
		for (i = 0; i < a_ptCfg->atCrossMarkKCfg[lCAMId].lROINum; i++)
		{
			aeXTmp[0] = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[i].lX;
			aeYTmp[0] = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[i].lY;

			COMMONK_Birdview2SBV(
                a_ptParams->tBVImgSize.lX, a_ptParams->tBVImgSize.lY,
                tImgSize.lX, tImgSize.lY,
				1, a_ptParams->atCrossMarkKParameter[lCAMId].lAngleCAM,
				a_ptParams->atCrossMarkKParameter[lCAMId].lCamPosX,
				a_ptParams->atCrossMarkKParameter[lCAMId].lCamPosY,
				a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].alSBVOffsetX,
				a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].alSBVOffsetY,
				a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].aeSBVScale,
				a_ptParams->atCrossMarkKParameter[lCAMId].eMMPP,
				aeXTmp, aeYTmp,
				aeXSBV, aeYSBV
			);


#if 0 // use degault ROI
			a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lLeft = alROUND(aeXSBV[0] - alCRSMRKDET_ROI_W);
			a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lTop = alROUND(aeYSBV[0] - alCRSMRKDET_ROI_H);
			a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lRight = alROUND(aeXSBV[0] + alCRSMRKDET_ROI_W);
			a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lBottom = alROUND(aeYSBV[0] + alCRSMRKDET_ROI_H);
#else // use setting ROI
            a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lLeft = alROUND(aeXSBV[0] - a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].tROISize.lX);
            a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lTop = alROUND(aeYSBV[0] - a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].tROISize.lY);
            a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lRight = alROUND(aeXSBV[0] + a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].tROISize.lX);
            a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lBottom = alROUND(aeYSBV[0] + a_ptCfg->atCrossMarkKCfg[lCAMId].atROICfg[i].tROISize.lY);
#endif

			lMod = 1 + a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lRight - a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lLeft;
			lMod = lMod % 4;

			if (lMod != 0)
			{ // ROI 寬不是4的倍數 輸出圖會有問題 >> 縮小
				a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lRight -= lMod;
			}
			
			if (a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lLeft < 0 ||
				a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lTop < 0 || 
                a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lRight > tImgSize.lX ||
                a_ptParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[i].lBottom > tImgSize.lY)
			{
				assert(0);
			}
		}
	}

	// For Quality FineTune
	for (lCAMId = 0; lCAMId < 4; lCAMId++)
	{
		switch (lCAMId)
		{
		case alCAMERAINFO_BV_LEFT:
			a_ptParams->atFineTuneFP[lCAMId][0].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX + alROUND(300 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][0].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY;

			a_ptParams->atFineTuneFP[lCAMId][1].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lX + alROUND(450 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][1].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lY;

			a_ptParams->atStitchLine[lCAMId][0].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[0].lX;
			a_ptParams->atStitchLine[lCAMId][0].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[0].lY;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[1].lX;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[1].lY;

			a_ptParams->atStitchLine[lCAMId][1].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_BackLeft[0].lX;
			a_ptParams->atStitchLine[lCAMId][1].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_BackLeft[0].lY;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_BackLeft[1].lX;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_BackLeft[1].lY;
			break;
		case alCAMERAINFO_BV_RIGHT:
			a_ptParams->atFineTuneFP[lCAMId][0].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX - alROUND(300 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][0].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY;

			a_ptParams->atFineTuneFP[lCAMId][1].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lX - alROUND(450 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][1].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[2].lY;

			a_ptParams->atStitchLine[lCAMId][0].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_FrontRight[0].lX;
			a_ptParams->atStitchLine[lCAMId][0].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_FrontRight[0].lY;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_FrontRight[1].lX;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_FrontRight[1].lY;

			a_ptParams->atStitchLine[lCAMId][1].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_BackRight[0].lX;
			a_ptParams->atStitchLine[lCAMId][1].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_BackRight[0].lY;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_BackRight[1].lX;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_BackRight[1].lY;
			break;
		case alCAMERAINFO_BV_FRONT:
			a_ptParams->atFineTuneFP[lCAMId][0].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX + alROUND(300 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][0].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY;

			a_ptParams->atFineTuneFP[lCAMId][1].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lX - alROUND(300 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][1].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lY;

			a_ptParams->atStitchLine[lCAMId][0].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[0].lX;
			a_ptParams->atStitchLine[lCAMId][0].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[0].lY;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[1].lX;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_FrontLeft[1].lY;

			a_ptParams->atStitchLine[lCAMId][1].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_FrontRight[0].lX;
			a_ptParams->atStitchLine[lCAMId][1].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_FrontRight[0].lY;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_FrontRight[1].lX;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_FrontRight[1].lY;
			break;
		case  alCAMERAINFO_BV_BACK:
			a_ptParams->atFineTuneFP[lCAMId][0].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lX - alROUND(450 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][0].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[0].lY;

			a_ptParams->atFineTuneFP[lCAMId][1].eX = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lX + alROUND(450 / a_ptalAVM2D_Params->fMMPP);
			a_ptParams->atFineTuneFP[lCAMId][1].eY = a_ptParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[3].lY;

			a_ptParams->atStitchLine[lCAMId][0].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_BackRight[0].lX;
			a_ptParams->atStitchLine[lCAMId][0].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_BackRight[0].lY;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_BackRight[1].lX;
			a_ptParams->atStitchLine[lCAMId][0].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_BackRight[1].lY;

			a_ptParams->atStitchLine[lCAMId][1].tStart.eX = a_ptalAVM2D_Params->atStitchPoint_BackLeft[0].lX;
			a_ptParams->atStitchLine[lCAMId][1].tStart.eY = a_ptalAVM2D_Params->atStitchPoint_BackLeft[0].lY;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eX = a_ptalAVM2D_Params->atStitchPoint_BackLeft[1].lX;
			a_ptParams->atStitchLine[lCAMId][1].tEnd.eY = a_ptalAVM2D_Params->atStitchPoint_BackLeft[1].lY;
			break;
		default:
			assert(0);
			break;
		}
		
	}

}

void alBVCAM_FACAUTOK_GenIdealFPofCrossMarkK(
    BVCAM_FACAUTOK_ChartCrossPointSet *a_ptFeildData,
    alCOMMONK_CommonCfg *a_ptCommonCfg, FLOAT32    a_fMMPP,
    FLOAT64 a_aeBVAutoKIdealFP_X[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK],
    FLOAT64 a_aeBVAutoKIdealFP_Y[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK]
    )
{
    BVCAM_FACAUTOK_ChartCrossPointSet tCrossPointSet;
    FLOAT32 fPPMM = 1.0f / a_fMMPP;

    // 以下四個參數以車輛左上角為原點，左負右正，上負下正。
    INT32 lCar_OffsetY_F = a_ptFeildData->uwFWheeltoFChart - a_ptCommonCfg->ulFrontFixedPoint2Head;
    INT32 lCar_OffsetY_B = a_ptFeildData->uwCharVertDistance - lCar_OffsetY_F;
    INT32 lCar_OffsetX_L = 0;
    INT32 lCar_OffsetX_R = a_ptFeildData->uwChartHoriDistance - lCar_OffsetX_L;
    INT32 lBirdViewCenterPosX = (a_ptCommonCfg->tDisplayAreaSize.lX >> 1);
    INT32 lBirdViewCenterPosY = (a_ptCommonCfg->tDisplayAreaSize.lY >> 1);
    FLOAT64 eCarTopLeftPosX = lBirdViewCenterPosX - (a_ptCommonCfg->ulCarWidth >> 1) * fPPMM;
    FLOAT64 eCarTopLeftPosY = lBirdViewCenterPosY - (a_ptCommonCfg->ulCarLength >> 1) * fPPMM;

    /* Assumption : 車輛停放都是靠左側導軌，以及靠前輪定位點對齊， */
    tCrossPointSet.FW1 = a_ptFeildData->FW1 + lCar_OffsetX_L;
    tCrossPointSet.FH1 = a_ptFeildData->FH1 + lCar_OffsetY_F;
    tCrossPointSet.FW2 = a_ptFeildData->FW2 + lCar_OffsetX_R;
    tCrossPointSet.FH2 = a_ptFeildData->FH2 + lCar_OffsetY_F;
    tCrossPointSet.FW3 = a_ptFeildData->FW3 + lCar_OffsetX_L;
    tCrossPointSet.FH3 = a_ptFeildData->FH3 + lCar_OffsetY_F;
    tCrossPointSet.FW4 = a_ptFeildData->FW4 + lCar_OffsetX_R;
    tCrossPointSet.FH4 = a_ptFeildData->FH4 + lCar_OffsetY_F;
    tCrossPointSet.FW5 = a_ptFeildData->FW5 + lCar_OffsetX_L;
    tCrossPointSet.FH5 = a_ptFeildData->FH5 + lCar_OffsetY_F;
    tCrossPointSet.FW6 = a_ptFeildData->FW6 + lCar_OffsetX_R;
    tCrossPointSet.FH6 = a_ptFeildData->FH6 + lCar_OffsetY_F;
    tCrossPointSet.BW1 = a_ptFeildData->BW1 + lCar_OffsetX_R;
    tCrossPointSet.BH1 = a_ptFeildData->BH1 + lCar_OffsetY_B;
    tCrossPointSet.BW2 = a_ptFeildData->BW2 + lCar_OffsetX_L;
    tCrossPointSet.BH2 = a_ptFeildData->BH2 + lCar_OffsetY_B;
    tCrossPointSet.BW3 = a_ptFeildData->BW3 + lCar_OffsetX_R;
    tCrossPointSet.BH3 = a_ptFeildData->BH3 + lCar_OffsetY_B;
    tCrossPointSet.BW4 = a_ptFeildData->BW4 + lCar_OffsetX_L;
    tCrossPointSet.BH4 = a_ptFeildData->BH4 + lCar_OffsetY_B;
    tCrossPointSet.BW5 = a_ptFeildData->BW5 + lCar_OffsetX_R;
    tCrossPointSet.BH5 = a_ptFeildData->BH5 + lCar_OffsetY_B;
    tCrossPointSet.BW6 = a_ptFeildData->BW6 + lCar_OffsetX_L;
    tCrossPointSet.BH6 = a_ptFeildData->BH6 + lCar_OffsetY_B;
    tCrossPointSet.BW7 = a_ptFeildData->BW7 + lCar_OffsetX_R;
    tCrossPointSet.BH7 = a_ptFeildData->BH7 + lCar_OffsetY_B;
    tCrossPointSet.BW8 = a_ptFeildData->BW8 + lCar_OffsetX_L;
    tCrossPointSet.BH8 = a_ptFeildData->BH8 + lCar_OffsetY_B;

    // Front View
    /*

    ＋             ＋
    +		(2)            (3)		+
    (4)								(5)
    ＋             ＋
    (0)            (1)

    */
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_FRONT][0] = eCarTopLeftPosX - tCrossPointSet.FW1 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_FRONT][1] = eCarTopLeftPosX + tCrossPointSet.FW2 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_FRONT][2] = eCarTopLeftPosX - tCrossPointSet.FW3 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_FRONT][3] = eCarTopLeftPosX + tCrossPointSet.FW4 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_FRONT][4] = eCarTopLeftPosX - tCrossPointSet.FW5 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_FRONT][5] = eCarTopLeftPosX + tCrossPointSet.FW6 * fPPMM;

    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_FRONT][0] = eCarTopLeftPosY - tCrossPointSet.FH1 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_FRONT][1] = eCarTopLeftPosY - tCrossPointSet.FH2 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_FRONT][2] = eCarTopLeftPosY - tCrossPointSet.FH3 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_FRONT][3] = eCarTopLeftPosY - tCrossPointSet.FH4 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_FRONT][4] = eCarTopLeftPosY - tCrossPointSet.FH5 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_FRONT][5] = eCarTopLeftPosY - tCrossPointSet.FH6 * fPPMM;

    // Back View
    /*

    ＋             ＋
    (1)            (0)
    +								+
    (5)		＋             ＋		(4)
    (3)            (2)

    */
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_BACK][0] = eCarTopLeftPosX + tCrossPointSet.BW1 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_BACK][1] = eCarTopLeftPosX - tCrossPointSet.BW2 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_BACK][2] = eCarTopLeftPosX + tCrossPointSet.BW3 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_BACK][3] = eCarTopLeftPosX - tCrossPointSet.BW4 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_BACK][4] = eCarTopLeftPosX + tCrossPointSet.BW5 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_BACK][5] = eCarTopLeftPosX - tCrossPointSet.BW6 * fPPMM;

    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_BACK][0] = eCarTopLeftPosY + tCrossPointSet.BH1 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_BACK][1] = eCarTopLeftPosY + tCrossPointSet.BH2 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_BACK][2] = eCarTopLeftPosY + tCrossPointSet.BH3 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_BACK][3] = eCarTopLeftPosY + tCrossPointSet.BH4 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_BACK][4] = eCarTopLeftPosY + tCrossPointSet.BH5 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_BACK][5] = eCarTopLeftPosY + tCrossPointSet.BH6 * fPPMM;

    // Left View
    /*

    ＋
    (3)     ＋
    (1)

    +(4)	＋
    ＋      (0)
    (2)

    */
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_LEFT][0] = eCarTopLeftPosX - tCrossPointSet.BW2 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_LEFT][1] = eCarTopLeftPosX - tCrossPointSet.FW1 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_LEFT][2] = eCarTopLeftPosX - tCrossPointSet.BW6 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_LEFT][3] = eCarTopLeftPosX - tCrossPointSet.FW5 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_LEFT][4] = eCarTopLeftPosX - tCrossPointSet.BW8 * fPPMM;

    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_LEFT][0] = eCarTopLeftPosY + tCrossPointSet.BH2 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_LEFT][1] = eCarTopLeftPosY - tCrossPointSet.FH1 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_LEFT][2] = eCarTopLeftPosY + tCrossPointSet.BH6 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_LEFT][3] = eCarTopLeftPosY - tCrossPointSet.FH5 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_LEFT][4] = eCarTopLeftPosY + tCrossPointSet.BH8 * fPPMM;

    // Right View
    /*

    ＋
    ＋		(2)
    (0)

    ＋		+(4)
    (1)     ＋
    (3)

    */
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_RIGHT][0] = eCarTopLeftPosX + tCrossPointSet.FW2 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_RIGHT][1] = eCarTopLeftPosX + tCrossPointSet.BW1 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_RIGHT][2] = eCarTopLeftPosX + tCrossPointSet.FW6 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_RIGHT][3] = eCarTopLeftPosX + tCrossPointSet.BW5 * fPPMM;
    a_aeBVAutoKIdealFP_X[alCAMERAINFO_BV_RIGHT][4] = eCarTopLeftPosX + tCrossPointSet.BW7 * fPPMM;

    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_RIGHT][0] = eCarTopLeftPosY - tCrossPointSet.FH2 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_RIGHT][1] = eCarTopLeftPosY + tCrossPointSet.BH1 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_RIGHT][2] = eCarTopLeftPosY - tCrossPointSet.FH6 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_RIGHT][3] = eCarTopLeftPosY + tCrossPointSet.BH5 * fPPMM;
    a_aeBVAutoKIdealFP_Y[alCAMERAINFO_BV_RIGHT][4] = eCarTopLeftPosY + tCrossPointSet.BH7 * fPPMM;
}

#if alBVCAM_FACAUTOK_DEBUG
void alBVCAM_GetalAVM2DInfo(
    alAVM2D_Params *a_ptalAVM2D_Params,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg
    )
{
    memcpy(&g_talAVM2D_ParamsTest, a_ptalAVM2D_Params, sizeof(alAVM2D_Params));
    memcpy(&g_talAVM2D_CfgTest, a_ptalAVM2D_Cfg, sizeof(alAVM2D_Cfg));
}
#endif
