#include <math.h>
#include "BVCAM_FACAUTOK/RectK.h"
#include "alFM_v2_1.h"
#include "alMatrix.h"

#ifndef WIN32
#include <ti/sysbios/hal/Cache.h>
#endif


/**
*  \addtogroup alRECK
*  @{
*/

#if	(alRECK_DEBUG || BVCAM_FACAUTOK_FAIL_LOG)
INT32 g_CamId = 0, g_ROIId = 0;
#endif

#define EAGLE_DEBUG 0

/**
\brief FP Detect of RectangleK(2210).
\param alPointINT32 [IN] BV Img Size,
\param a_pucBuffer [IN] Working Buffer
\param a_lROIId [IN] ROI index
\param a_ptCfg [IN] config data
\param a_ptParameter [IN] Parameter data
\param a_pucSrcBuffer [IN] source Buffer of camera
\param a_peM33 [IN] transform matrix
\param a_peSBVX [OUT] x of fp
\param a_peSBVY [OUT] y of fp
\return 0: fail 1: success
*/
UINT8 FPDetect(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucBuffer,
	INT32 a_lROIId,
	alRECK_Cfg *a_ptCfg,
	alRECK_Parameter *a_ptParameter,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 *a_peM33,
	FLOAT64 *a_peSBVX, FLOAT64 *a_peSBVY
	);

/**
\brief SBV Generating by CFG(2211).
\param a_tROI [IN] Detect ROI
\param a_pucSrcBuffer [IN] source Buffer of camera
\param a_ptFisheyeModel [IN] Fisheye Model
\param a_ptM33 [IN] transform matrix (BV to Src >> [0])
\param a_lOriImgYLimit [IN] Define the y position limitation to avoid the overflow
\param a_lOffsetX [IN] SBV X offset
\param a_lOffsetY [IN] SBV Y offset
\param a_eSBVScale [IN] source Buffer of camera
\param a_pucSBVBuffer [OUT] Single BirdView Buffer
*/
void	SBVGenerating(
	alRectINT32 a_tROI,
	UINT8 *a_pucSrcBuffer,
	alFM_v2_1_Model *a_ptFisheyeModel,
	FLOAT64 *a_ptM33,
	INT32 a_lOriImgYLimit,
	INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale,
	UINT8 *a_pucSBVBuffer
	);



/**
\brief Rectangle Corner ExtractING (2213~2214).
\param a_pttImgSize [IN] Img Size
\param a_pucBuffer [IN] Working buffer
\param a_tROI [IN] Detect ROI
\param a_peIdealSBVX [IN] Ideal x in SBV
\param a_peIdealSBVY [IN] Ideal y in SBV
\param a_lLineNum [IN] detected line number
\param a_peLineDetectResult [IN] line detection result
\param a_pucSBVBuffer [IN] SBV Buffer
\param a_peFPX [IN] FP x
\param a_peFPY [IN] FP y
\return 0: fail 1: success
*/
UINT8 RectangleCornerExtract(
    alPointINT32 *a_pttImgSize,
    UINT8 *a_pucBuffer,
	alRectINT32 a_tROI,
	FLOAT64 *a_peIdealSBVX, FLOAT64 *a_peIdealSBVY,
	INT32 a_lLineNum, FLOAT64 *a_peLineDetectResult,
	UINT8 *a_pucSBVBuffer,
	FLOAT64 *a_peFPX, FLOAT64 *a_peFPY
);

/**
\brief Intercept Point Calculation_by Line Infomation
\param a_peLineDetectResult [IN] line segment result
\param a_alLinrId [IN] line Id
\param a_alPx [OUT] Intercept Point x
\param a_alPy [OUT] Intercept Point y
*/
void	InterceptPointCal_ByLineInfo(
	FLOAT64 *a_peLineDetectResult,
	INT32 a_alLinrId[4], INT32 a_alPx[4], INT32 a_alPy[4]
	);

/**
\brief Line type Classify
\param a_peResult [IN] line segment result
\param a_plLineType [OUT] line type
*/
void LineClassify(FLOAT64 *a_peResult, INT32 *a_plLineType);

/**
\brief Line type Classify
\param a_peResult [IN] line segment result
\param a_peIdealSBVX [IN] ideal coordinate x in SBV
\param a_peIdealSBVY [IN] ideal coordinate Y in SBV
\param a_plLineType [OUT] line type
\param a_pucSBVBuffer [IN] Image buffer (Y)
\param a_tROI [IN] ROI coordinate
*/
UINT8 LineSegVerify(
	FLOAT64 *a_peResult, FLOAT64 *a_peIdealSBVX, FLOAT64 *a_peIdealSBVY, INT32 a_lLineType,
	UINT8 *a_pucSBVBuffer, alRectINT32 a_tROI
	);

/**
\brief Get Variance
\param Nums [IN] data buffer
\param Count [IN] data number
\return Variance
*/
static double GetVariance(FLOAT64 *Nums, INT32 Count);

/**
\brief Check Rectangle Point
\param alPointINT32 Img Size
\param a_pucBuffer [IN] working buffer
\param a_alPx [IN] Intercept Point x
\param a_alPy [IN] Intercept Point y
\param a_alLinrId [IN] line Id
\param a_peLineDetectResult [IN] line segment result
\param a_pucSBVBuffer [IN] Image buffer (Y)
\param a_tROI [IN] ROI coordinate
\return 0: fail 1: success
*/
UINT8 CheckRectanglePoint(
    alPointINT32 *a_pttImgSize,
    UINT8 *a_pucBuffer,
	INT32 *a_plFPX, INT32 *a_plFPY,
	INT32 a_alLinrId[4], FLOAT64 *a_peLineDetectResult,
	UINT8 *a_pucSBVBuffer, alRectINT32 a_tROI
	);

/**
*  @}
*/

static double GetVariance(FLOAT64 *Nums, INT32 Count)
{
	double sum, mean;
	int i;
	sum = 0;
	for (i = 0; i < Count; i++)
	{
		sum = sum + Nums[i];
	}
	mean = sum / (double)Count;
	sum = 0;
	for (i = 0; i < Count; i++)
	{
		sum += (Nums[i] - mean)*(Nums[i] - mean);
	}

	return sum / (double)Count;
}

UINT8 CheckRectanglePoint(
    alPointINT32 *a_pttImgSize,
    UINT8 *a_pucBuffer,
	INT32 *a_plFPX, INT32 *a_plFPY, 
	INT32 a_alLinrId[4], FLOAT64 *a_peLineDetectResult,
	UINT8 *a_pucSBVBuffer, alRectINT32 a_tROI
	)
{
	INT32 i = 0, lX = 0, lY = 0, lCnt = 0;
	INT32 lImagW = 0, lImagH = 0;
	FLOAT64 eCenterX[4] = { 0 }, eCenterY[4] = { 0 }, eVariance = 0;
	FLOAT64 eSX = 0, eSY = 0, eEX = 0, eEY = 0, *peData = NULL;
	alRectINT32 tROITmp;

	lImagW = a_tROI.lRight - a_tROI.lLeft + 1;
	lImagH = a_tROI.lBottom - a_tROI.lTop + 1;

	for (i = 0; i < 4; i++)
	{
		eSX = a_peLineDetectResult[7 * a_alLinrId[i]];
		eSY = a_peLineDetectResult[7 * a_alLinrId[i] + 1];
		eEX = a_peLineDetectResult[7 * a_alLinrId[i] + 2];
		eEY = a_peLineDetectResult[7 * a_alLinrId[i] + 3];

		eCenterX[i] = (eSX + eEX) / 2;
		eCenterY[i] = (eSY + eEY) / 2;
	}

	// 邊界檢查
	for (i = 0; i < 4; i++)
	{
        if (a_plFPY[i] < 0 || a_plFPY[i] >= a_pttImgSize->lY)
		{
			return FALSE;
		}

        if (a_plFPX[i] < 0 || a_plFPX[i] >= a_pttImgSize->lX)
		{
			return FALSE;
		}
	}

	// 檢查交點相對位置是否合理 
	if (a_plFPY[3] < a_plFPY[0] || a_plFPY[3] < a_plFPY[1])
	{
		return FALSE;
	}

	if (a_plFPY[2] < a_plFPY[0] || a_plFPY[2] < a_plFPY[1])
	{
		return FALSE;
	}

	if (a_plFPX[3] > a_plFPX[1] || a_plFPX[3] > a_plFPX[2])
	{
		return FALSE;
	}

	if (a_plFPX[0] > a_plFPX[1] || a_plFPX[0] > a_plFPX[2])
	{
		return FALSE;
	}

	// Center Check
	if (eCenterX[1] < a_plFPX[0] ||  eCenterX[1] > a_plFPX[1])
	{
		return FALSE;
	}

	if (eCenterX[3] < a_plFPX[3] || eCenterX[3] > a_plFPX[2])
	{
		return FALSE;
	}

	if (eCenterY[0] < a_plFPY[0] || eCenterY[0] > a_plFPY[3])
	{
		return FALSE;
	}

	if (eCenterY[2] < a_plFPY[1] || eCenterY[2] > a_plFPY[2])
	{
		return FALSE;
	}

	// 校正版檢查
	tROITmp.lLeft = alMAX(a_plFPX[0], a_plFPX[3]);
	tROITmp.lLeft -= a_tROI.lLeft;

	tROITmp.lRight = alMIN(a_plFPX[1], a_plFPX[2]);
	tROITmp.lRight -= a_tROI.lLeft;

	tROITmp.lTop = alMAX(a_plFPY[0], a_plFPY[1]);
	tROITmp.lTop -= a_tROI.lTop;

	tROITmp.lBottom = alMIN(a_plFPY[2], a_plFPY[3]);
	tROITmp.lBottom -= a_tROI.lTop;

    if (a_pucBuffer == NULL)
    {
        peData = (FLOAT64*)malloc((tROITmp.lRight - tROITmp.lLeft) * (tROITmp.lBottom - tROITmp.lTop) * sizeof(FLOAT64));
    }
    else
    {
        if ( (tROITmp.lRight - tROITmp.lLeft) * (tROITmp.lBottom - tROITmp.lTop) * sizeof(FLOAT64) > COMMONK_Else_WorkingBufferSize)
        {
            assert(0);
        }

        peData = (FLOAT64 *)a_pucBuffer;
    }
    for (lY = tROITmp.lTop +1; lY < tROITmp.lBottom-1; lY++)
	{
		for (lX = tROITmp.lLeft+1; lX < tROITmp.lRight-1; lX++)
		{
			peData[lCnt] = 0;
			peData[lCnt] = a_pucSBVBuffer[lY*lImagW + lX];
			lCnt++;
		}
	}

	eVariance = GetVariance(peData, lCnt);
    if (a_pucBuffer == NULL)
    {
        free(peData);
    }
    if (eVariance > alRECK_VAR_TH)
	{
		return FALSE;
	}

	return TRUE;
}

UINT8 LineSegVerify(
	FLOAT64 *a_peResult, FLOAT64 *a_peIdealSBVX, FLOAT64 *a_peIdealSBVY, INT32 a_lLineType, 
	UINT8 *a_pucSBVBuffer, alRectINT32 a_tROI
	)
{
	INT32 lStart[2], lEnd[2], lWidth = 0, lHeight = 0, lShift = 0, alCenter[2] = { 0 }, alROI[4] = { 0 };
	INT32 lX, lY, lCnt = 0, alROIWhite[4] = { 0 }, lCntHight = 0, lShiftWhite = 0, lFailCnt = 0, lImagW = 0, lImagH =0;
	UINT8 ucPixel = 0;
	FLOAT64 aeRectangleTmp[10] = {0}, eMean = 0, eMeanHight = 0, eDistance = 0, eDistanceTH = 0;


	lStart[0] = alROUND(a_peResult[0]);
	lStart[1] = alROUND(a_peResult[1]);
	lEnd[0] = alROUND(a_peResult[2]);
	lEnd[1] = alROUND(a_peResult[3]);

	lStart[0] -= a_tROI.lLeft;
	lStart[1] -= a_tROI.lTop;
	lEnd[0] -= a_tROI.lLeft;
	lEnd[1] -= a_tROI.lTop;

	lImagW = a_tROI.lRight - a_tROI.lLeft + 1;
	lImagH = a_tROI.lBottom - a_tROI.lTop +1;

	alCenter[0] = alROUND((a_peResult[0] + a_peResult[2]) / 2); // x center
	alCenter[1] = alROUND((a_peResult[1] + a_peResult[3]) / 2); // y center
	alCenter[0] -= a_tROI.lLeft;
	alCenter[1] -= a_tROI.lTop;

	lShift = 10;

	switch (a_lLineType)
	{
	case 1:		// LEFT
		if (alCenter[0] + lShift > lImagW || alCenter[0] - lShift < 0)
		{
			return FALSE;
		}
		lY = alCenter[1];
		for (lX = 0; lX < lShift; lX++)
		{
			ucPixel = a_pucSBVBuffer[lY*lImagW + alCenter[0] + lX];
			eMean = eMean + ucPixel;

			ucPixel = a_pucSBVBuffer[lY*lImagW + alCenter[0] - lX - 1];
			eMeanHight = eMeanHight + ucPixel;

			lCnt++;
		}
		eMean /= lCnt;
		eMeanHight /= lCnt;
		break;
	case 2:		// TOP
		if (alCenter[1] + lShift > lImagH || alCenter[1] - lShift < 0)
		{
			return FALSE;
		}
		lX = alCenter[0];
		for (lY = 0; lY < lShift; lY++)
		{
			ucPixel = a_pucSBVBuffer[(alCenter[1]+lY)*lImagW + lX];
			eMean = eMean + ucPixel;

			ucPixel = a_pucSBVBuffer[(alCenter[1] - lY-1)*lImagW + lX];
			eMeanHight = eMeanHight + ucPixel;

			lCnt++;
		}
		eMean /= lCnt;
		eMeanHight /= lCnt;
		break;
	case 3:		// RIGHT
		if (alCenter[0] + lShift > lImagW || alCenter[0] - lShift < 0)
		{
			return FALSE;
		}
		lY = alCenter[1];
		for (lX = 0; lX < lShift; lX++)
		{
			ucPixel = a_pucSBVBuffer[lY*lImagW + alCenter[0] + lX];
			eMeanHight = eMeanHight + ucPixel;

			ucPixel = a_pucSBVBuffer[lY*lImagW + alCenter[0] - lX - 1];
			eMean = eMean + ucPixel;

			lCnt++;
		}
		eMean /= lCnt;
		eMeanHight /= lCnt;
		break;
	case  4:	// DOWN
		if (alCenter[1] + lShift > lImagH || alCenter[1] - lShift < 0)
		{
			return FALSE;
		}
		lX = alCenter[0];
		for (lY = 0; lY < lShift; lY++)
		{
			ucPixel = a_pucSBVBuffer[(alCenter[1] + lY)*lImagW + lX];
			eMeanHight = eMeanHight + ucPixel;

			ucPixel = a_pucSBVBuffer[(alCenter[1] - lY-1)*lImagW + lX];
			eMean = eMean + ucPixel;

			lCnt++;
		}
		eMean /= lCnt;
		eMeanHight /= lCnt;
		break;
	default:
		assert(0);
		break;
	}

	if (eMeanHight - eMean < 30)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void LineClassify(FLOAT64 *a_peResult, INT32 *a_plLineType)
{
	INT32 lStart[2], lEnd[2];
	FLOAT64 aeRectangleTmp[10], eLength, eAngle, aeLengthTH[2], aeAngleTH[2];

	aeLengthTH[0] = 20; // 45;
	aeLengthTH[1] = 15;
	aeAngleTH[0] = 45; // 55;
	aeAngleTH[1] = 20;
	lStart[0] = alROUND(a_peResult[0]);
	lStart[1] = alROUND(a_peResult[1]);
	lEnd[0] = alROUND(a_peResult[2]);
	lEnd[1] = alROUND(a_peResult[3]);

	aeRectangleTmp[0] = lEnd[0] - lStart[0]; // x gap
	aeRectangleTmp[1] = lEnd[1] - lStart[1]; // y gap

	eLength = sqrt(aeRectangleTmp[0] * aeRectangleTmp[0] + aeRectangleTmp[1] * aeRectangleTmp[1]);	// length
	eAngle = (aeRectangleTmp[0]) ? fabs(atan(aeRectangleTmp[1] / aeRectangleTmp[0]) * 180 / alPI) : 90; // angle


	if (eAngle > aeAngleTH[0] && eLength > aeLengthTH[0])
	{	// vertical
		if (lEnd[1] < lStart[1])
		{ // LEFT
			*a_plLineType = 1;
		}
		else
		{	// RIGHT
			*a_plLineType = 3;
		}
	}
	else if (eAngle < aeAngleTH[1] && eLength > aeLengthTH[1])
	{	// hori
		if (lEnd[0] > lStart[0])
		{ // UP
			*a_plLineType = 2;
		}
		else
		{	// DOWN
			*a_plLineType = 4;
		}
	}
	else
	{
		*a_plLineType = 0;
	}
}

void	InterceptPointCal_ByLineInfo(
	FLOAT64 *a_peLineDetectResult,
	INT32 a_alLinrId[4], INT32 a_alPx[4], INT32 a_alPy[4]
	)
{
	INT32 i = 0, alId[2];
	FLOAT64 eSX0, eSY0, eSX1, eSY1, eVX0, eVY0, eVX1, eVY1, eT, aeP[2];
	FLOAT64 eEX0, eEY0, eEX1, eEY1;

	for (i = 0; i < 4; i++)
	{
		alId[0] = a_alLinrId[i];

		alId[1] = (i + 1 >= 4) ? a_alLinrId[0] : a_alLinrId[i + 1];

		eSX0 = a_peLineDetectResult[7 * alId[0]];
		eSY0 = a_peLineDetectResult[7 * alId[0] + 1];
		eEX0 = a_peLineDetectResult[7 * alId[0] + 2];
		eEY0 = a_peLineDetectResult[7 * alId[0] + 3];
		eVX0 = eEX0 - eSX0;
		eVY0 = eEY0 - eSY0;

		eSX1 = a_peLineDetectResult[7 * alId[1]];
		eSY1 = a_peLineDetectResult[7 * alId[1] + 1];
		eEX1 = a_peLineDetectResult[7 * alId[1] + 2];
		eEY1 = a_peLineDetectResult[7 * alId[1] + 3];
		eVX1 = eEX1 - eSX1;
		eVY1 = eEY1 - eSY1;

		eT = (eVY1*(eSX1 - eSX0) - eVX1*(eSY1 - eSY0)) / (eVX0*eVY1 - eVY0*eVX1);

		aeP[0] = eSX0 + eVX0*eT;
		aeP[1] = eSY0 + eVY0*eT;

		a_alPx[i] = alROUND(aeP[0]);
		a_alPy[i] = alROUND(aeP[1]);
	}
}

void	LineSegDetectionRec(
    UINT8 *a_pucBuffer,
	UINT8 *a_pucYBuffer,
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
    FILE *ptFile =NULL;

	aeLineParameter[0] = 0.8;	// image scale (0.8)
	aeLineParameter[1] = 0.6;	// sigma_scale (0.6)
	aeLineParameter[2] = 6.0;	// Bound to the quantization error on the gradient norm. (2.0)
	aeLineParameter[3] = 30;	//  22.5;	// Gradient angle tolerance in degrees. (22.5)
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
    if (a_pucBuffer == NULL)
    {
        peLineSegImg = (FLOAT64 *)malloc(lWidth * lHeight * sizeof(FLOAT64));
    }
    else
    {
        if (lWidth * lHeight * sizeof(FLOAT64) > COMMONK_Else_WorkingBufferSize)
        {
            assert(0);
        }
        peLineSegImg = (FLOAT64 *)a_pucBuffer;
    }
    if (peLineSegImg == NULL)
	{
		fprintf(stderr, "error: not enough memory\n");
		exit(EXIT_FAILURE);
	}

    memset(peLineSegImg, 0, lWidth * lHeight * sizeof(FLOAT64));

	// copy  Y channel data to peLineSegImg buffer
	for (x = 0; x < lWidth; x++)
	{
		for (y = 0; y < lHeight ; y++)
		{
			lIndexImg = x + y*lWidth;
			llIndexROI = x + y*lWidth;

			ucPixel = a_pucYBuffer[lIndexImg];

            peLineSegImg[llIndexROI] = (FLOAT64)ucPixel;
		}
	}

#ifndef WIN32
    Cache_wbInv((Ptr)peLineSegImg, lWidth*lHeight*sizeof(FLOAT64), Cache_Type_ALL, TRUE);
#endif
    
#if EAGLE_DEBUG // for debug
    ptFile = fopen("sbv_test_FLAT64.hex", "wb");
    fwrite(peLineSegImg, lWidth * lHeight * sizeof(FLOAT64), 1, ptFile);
    fclose(ptFile);

    ptFile = fopen("sbv_test.raw", "wb");
    fwrite(a_pucYBuffer, lWidth*lHeight, 1, ptFile);
    fclose(ptFile);

#endif
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

#if EAGLE_DEBUG // for debug
    ptFile = fopen("tmp.txt", "w+");
    for (lCnt = 0; lCnt < lLineNum; lCnt++)
    {
        fprintf(ptFile, "No.%d: Sx: %.1f\tSy: %.1f\tEx: %.1f\tEy: %.1f\n", lCnt, a_peResultTmp[7 * lCnt], a_peResultTmp[7 * lCnt + 1], a_peResultTmp[7 * lCnt + 2], a_peResultTmp[7 * lCnt + 3]);
    }
    fclose(ptFile);
#endif
#endif
    if (a_pucBuffer == NULL)
    {
        free((void *)peLineSegImg);	// buffer must be free !!!!!!!
    }
}

UINT8 RectangleCornerExtract(
    alPointINT32 *a_pttImgSize,
    UINT8 *a_pucBuffer,
	alRectINT32 a_tROI,
	FLOAT64 *a_peIdealSBVX, FLOAT64 *a_peIdealSBVY,
	INT32 a_lLineNum, FLOAT64 *a_peLineDetectResult,
	UINT8 *a_pucSBVBuffer,
	FLOAT64 *a_peFPX, FLOAT64 *a_peFPY
	)
{
	INT32 i = 0, lFalg = 0, alCnt[4] = { 0 }, lFindFlag = 0, lLineType = 0;
	INT32 alLineId[4][alRECK_MAX_LINE_NUM] = { 0 }, alPx[4] = { 0 }, alPy[4] = { 0 }, alLineNum[4] = { 0 }, alLineIdFinal[4] = { 0 };
	FLOAT64 *a_peDetectResultTmp = NULL;
#if	((alRECK_DEBUG || BVCAM_FACAUTOK_FAIL_LOG) && alBVCAM_FACAUTOK_PC_DeBug)
	IplImage * ptPicGray = NULL;
	char cText[MAX_PATH] = {0};
    INT32 k = 0;
	INT32 id = 0, start[2] = { 0 }, end[2] = { 0 }, lCenterX = 0, lCenterY = 0;
#endif

#if	alRECK_DEBUG
	if (g_CamId == 2 && g_ROIId == 3)
	{
		i = i;
	}
#endif

	for (i = 0; i < a_lLineNum; i++)
	{
		a_peDetectResultTmp = a_peLineDetectResult + 7 * i;

		// 分類是哪種線
		LineClassify(a_peDetectResultTmp, &lLineType);

		if (lLineType)
		{
#if	alRECK_DEBUG
			if (g_CamId == 2 && g_ROIId == 3 && lLineType == 1)
			{
				i = i;
			}
#endif
			lFalg =  LineSegVerify(
				a_peDetectResultTmp, a_peIdealSBVX, a_peIdealSBVY, lLineType,
				a_pucSBVBuffer, a_tROI
			);

			if (lFalg)
			{
				alLineId[lLineType - 1][alLineNum[lLineType - 1]] = i;
				if (alLineNum[lLineType - 1] < alRECK_MAX_LINE_NUM)
				{	// buffer 夠就紀錄	
					alLineNum[lLineType - 1]++;
				}
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (alLineNum[i] <= 0)
		{ // 長方形有一邊沒偵測到
			return FALSE;
		}
	}

	if (alLineNum[0] == 1 && alLineNum[1] == 1 && alLineNum[2] == 1 && alLineNum[3] == 1)
	{	// 每邊剛好一條 >> 直接算交點 >> alLinrId alPx alPy
		alLineIdFinal[0] = alLineId[0][0];
		alLineIdFinal[1] = alLineId[1][0];
		alLineIdFinal[2] = alLineId[2][0];
		alLineIdFinal[3] = alLineId[3][0];
		InterceptPointCal_ByLineInfo(
			a_peLineDetectResult,
			alLineIdFinal, alPx, alPy
		);
	}
	else
	{	// 有偵測到2條以上的狀況 >> TBD 
#if 0 
		// 目前暫時用第一條
		alLineIdFinal[0] = alLineId[0][0];
		alLineIdFinal[1] = alLineId[1][0];
		alLineIdFinal[2] = alLineId[2][0];
		alLineIdFinal[3] = alLineId[3][0];
		InterceptPointCal_ByLineInfo(
			a_peLineDetectResult,
			alLineIdFinal, alPx, alPy
		);
#else
		// >> 暴力法 找到一組 相對角落對 面積也正常的 就break
		lFindFlag = 0;
		for (alCnt[0] = 0; alCnt[0] < alLineNum[0]; alCnt[0]++)
		{
			for (alCnt[1] = 0; alCnt[1] < alLineNum[1]; alCnt[1]++)
			{
				for (alCnt[2] = 0; alCnt[2] < alLineNum[2]; alCnt[2]++)
				{
					for (alCnt[3] = 0; alCnt[3] < alLineNum[3]; alCnt[3]++)
					{
						alLineIdFinal[0] = alLineId[0][alCnt[0]];
						alLineIdFinal[1] = alLineId[1][alCnt[1]];
						alLineIdFinal[2] = alLineId[2][alCnt[2]];
						alLineIdFinal[3] = alLineId[3][alCnt[3]];
						InterceptPointCal_ByLineInfo(
							a_peLineDetectResult,
							alLineIdFinal, alPx, alPy
						);
                        if (CheckRectanglePoint(a_pttImgSize, a_pucBuffer, alPx, alPy, alLineIdFinal, a_peLineDetectResult, a_pucSBVBuffer, a_tROI))
						{
							lFindFlag = 1;
							alCnt[0] = alLineNum[0];
							alCnt[1] = alLineNum[1];
							alCnt[2] = alLineNum[2];
							alCnt[3] = alLineNum[3];
							break;
						}
					}
				}
			}
		}
#endif
	}

#if	alRECK_DEBUG
	sprintf_s(cText, MAX_PATH, "%salRECK_SBV_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, g_CamId, g_ROIId);

	ptPicGray = cvLoadImage(cText, CV_LOAD_IMAGE_COLOR);

	for (i = 0; i < 4; i++)
	{
		for (k = 0; k < alLineNum[i]; k++)
		{

			id = alLineId[i][k];
			start[0] = alROUND(a_peLineDetectResult[7 * id]);
			start[1] = alROUND(a_peLineDetectResult[7 * id + 1]);
			end[0] = alROUND(a_peLineDetectResult[7 * id + 2]);
			end[1] = alROUND(a_peLineDetectResult[7 * id + 3]);

			start[0] -= a_tROI.lLeft;
			start[1] -= a_tROI.lTop;
			end[0] -= a_tROI.lLeft;
			end[1] -= a_tROI.lTop;

			switch (i)
			{
			case 0: // left
				cvLine(ptPicGray, cvPoint(start[0], start[1]), cvPoint(end[0], end[1]), CV_RGB(255, 0, 0), 2, CV_AA, 0);
				break;
			case 1: // top
				cvLine(ptPicGray, cvPoint(start[0], start[1]), cvPoint(end[0], end[1]), CV_RGB(0, 255, 0), 2, CV_AA, 0);
				break;
			case 2: // right
				cvLine(ptPicGray, cvPoint(start[0], start[1]), cvPoint(end[0], end[1]), CV_RGB(0, 0, 255), 2, CV_AA, 0);
				break;
			case 3:  // down
				cvLine(ptPicGray, cvPoint(start[0], start[1]), cvPoint(end[0], end[1]), CV_RGB(255, 255, 0), 2, CV_AA, 0);
				break;
			default:
				assert(0);
			}
		}
	}

	// log 交點
	for (i = 0; i < 4; i++)
	{
		cvLine(ptPicGray, cvPoint(alPx[i] - 3 - a_tROI.lLeft, alPy[i] - a_tROI.lTop), cvPoint(alPx[i] + 3 - a_tROI.lLeft, alPy[i] - a_tROI.lTop), CV_RGB(255, 128, 20), 2, CV_AA, 0);

		cvLine(ptPicGray, cvPoint(alPx[i] - a_tROI.lLeft, alPy[i] - 3 - a_tROI.lTop), cvPoint(alPx[i] - a_tROI.lLeft, alPy[i] + 3 - a_tROI.lTop), CV_RGB(255, 128, 20), 2, CV_AA, 0);
	}

	sprintf_s(cText, MAX_PATH, "%salRECK_Rectangle_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, g_CamId, g_ROIId);
	cvSaveImage(cText, ptPicGray, 0);
	cvReleaseImage(&ptPicGray);
#endif



	for (i = 0; i < 4; i++)
	{
		if (i)
		{
			a_peFPX[i] = alPx[i - 1];
			a_peFPY[i] = alPy[i - 1];
		}
		else
		{
			a_peFPX[i] = alPx[3];
			a_peFPY[i] = alPy[3];
		}
	}

	// 檢查交點相對位置是否合理 
	if (a_peFPY[0] < a_peFPY[1] || a_peFPY[0] < a_peFPY[2])
	{
		return FALSE;
	}

	if (a_peFPY[3] < a_peFPY[1] || a_peFPY[3] < a_peFPY[2])
	{
		return FALSE;
	}

	if (a_peFPX[0] > a_peFPX[2] || a_peFPX[0] > a_peFPX[3])
	{
		return FALSE;
	}

	if (a_peFPX[1] > a_peFPX[2] || a_peFPX[1] > a_peFPX[3])
	{
		return FALSE;
	}


	return TRUE;
}

UINT8 FPDetect(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucBuffer,
	INT32 a_lROIId,
	alRECK_Cfg *a_ptCfg,
	alRECK_Parameter *a_ptParameter,
	UINT8 *a_pucSrcBuffer,
	FLOAT64 *a_peM33,
	FLOAT64 *a_peSBVX, FLOAT64 *a_peSBVY
	)
{

	alRectINT32 tCurrentROI;
	INT32 lLineNum = 0, i = 0, lPointIndex = 0, lWidth = 0, lHeight = 0;
	FLOAT64 *peLineDetectResult = NULL;
	FLOAT64 aeXTmp[4] = { 0 }, aeYTmp[4] = { 0 }, aeXSBV[4] = { 0 }, aeYSBV[4] = { 0 };
    UINT8 *pucSBVBuffer = NULL, *pucLineSegBuffer = NULL, ucDetectFlag = 0;
    alPointINT32 tImgSize = { 0 };
#if	((alRECK_DEBUG || BVCAM_FACAUTOK_FAIL_LOG) && alBVCAM_FACAUTOK_PC_DeBug)
	IplImage * ptPicGray = NULL;
	IplImage * ptPicColor = NULL;
	char cText[MAX_PATH];
	INT32 lCamId = 0, x = 0, y = 0, start[2], end[2];
#endif
#if	alRECK_DEBUG && alBVCAM_FACAUTOK_PC_DeBug
	alRectINT32 tCurrentROITest;
#endif

    tImgSize.lX = a_ptParameter->ptFisheyeModel->uwSrcWidth;
    tImgSize.lY = a_ptParameter->ptFisheyeModel->uwSrcHeight;

    if (a_pucBuffer == NULL)
    {
        pucSBVBuffer = (UINT8 *)malloc(tImgSize.lX * tImgSize.lY * sizeof(UINT8));
        pucLineSegBuffer = NULL;
    }
    else
    {
        pucSBVBuffer = a_pucBuffer;
        pucLineSegBuffer = a_pucBuffer + (tImgSize.lX * tImgSize.lY);
    }
    tCurrentROI = a_ptParameter->atRecKROI[a_lROIId];

#if	alRECK_DEBUG
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
	tCurrentROITest.lRight = 719;
	tCurrentROITest.lBottom = 479;
	tCurrentROITest.lTop = 0;
	tCurrentROITest.lLeft = 0;
    COMMONK_SBVGeneratingK_YUYV2Y(
        a_ptBVImgSize,
		tCurrentROITest, a_pucSrcBuffer,
		a_ptParameter->ptFisheyeModel, a_peM33,
		a_ptParameter->lOriImgYLimit, a_ptParameter->lAngleCAM, a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
		a_ptCfg->atROICfg[a_lROIId].lSBVOffsetX, a_ptCfg->atROICfg[a_lROIId].lSBVOffsetY,
		a_ptCfg->atROICfg[a_lROIId].eSBVScale, a_ptParameter->eMMPP,
		pucSBVBuffer
	);
	ptPicGray = cvCreateImage(cvSize(tCurrentROITest.lRight - tCurrentROITest.lLeft + 1, tCurrentROITest.lBottom - tCurrentROITest.lTop + 1), IPL_DEPTH_8U, 1);
	memcpy(ptPicGray->imageData, pucSBVBuffer, sizeof(UINT8)*ptPicGray->imageSize);
	sprintf_s(cText, MAX_PATH, "%salRECK_SBVFULL_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, a_lROIId);
	cvSaveImage(cText, ptPicGray, 0);
	cvReleaseImage(&ptPicGray);
#endif


    COMMONK_SBVGeneratingK_YUYV2Y(
        a_ptBVImgSize,
		tCurrentROI, a_pucSrcBuffer,
		a_ptParameter->ptFisheyeModel, a_peM33,
		a_ptParameter->lOriImgYLimit, a_ptParameter->lAngleCAM, a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
		a_ptCfg->atROICfg[a_lROIId].lSBVOffsetX, a_ptCfg->atROICfg[a_lROIId].lSBVOffsetY,
		a_ptCfg->atROICfg[a_lROIId].eSBVScale, a_ptParameter->eMMPP,
		pucSBVBuffer
	);

    lWidth = tCurrentROI.lRight - tCurrentROI.lLeft + 1;
    lHeight = tCurrentROI.lBottom - tCurrentROI.lTop + 1;

#ifndef WIN32
    Cache_wbInv((Ptr)pucSBVBuffer, lWidth*lHeight*sizeof(UINT8), Cache_Type_ALL, TRUE);
#endif


#if 1 // for image enhance
    COMMONK_EnhanceImage(
        tCurrentROI.lRight - tCurrentROI.lLeft + 1,
        tCurrentROI.lBottom - tCurrentROI.lTop + 1,
        pucSBVBuffer,
        pucSBVBuffer
        );

#ifndef WIN32
    Cache_wbInv((Ptr)pucSBVBuffer, lWidth*lHeight*sizeof(UINT8), Cache_Type_ALL, TRUE);
#endif
#endif

#if	alRECK_DEBUG
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
 
	ptPicGray = cvCreateImage(cvSize(tCurrentROI.lRight - tCurrentROI.lLeft + 1, tCurrentROI.lBottom - tCurrentROI.lTop + 1), IPL_DEPTH_8U, 1);
	memcpy(ptPicGray->imageData, pucSBVBuffer, sizeof(UINT8)*ptPicGray->imageSize);
	sprintf_s(cText, MAX_PATH, "%salRECK_SBV_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, a_lROIId);
	cvSaveImage(cText, ptPicGray, 0);
	cvReleaseImage(&ptPicGray);
#endif



	LineSegDetectionRec(
        pucLineSegBuffer,
		pucSBVBuffer,
		tCurrentROI,
		&lLineNum,
		&peLineDetectResult
	);

#if	alRECK_DEBUG
	sprintf_s(cText, MAX_PATH, "%salRECK_SBV_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, a_lROIId);
	ptPicGray = cvLoadImage(cText, CV_LOAD_IMAGE_COLOR);
	for (i = 0; i < lLineNum; i++)
	{
		start[0] = alROUND(peLineDetectResult[7 * i]);
		start[1] = alROUND(peLineDetectResult[7 * i + 1]);
		end[0] = alROUND(peLineDetectResult[7 * i + 2]);
		end[1] = alROUND(peLineDetectResult[7 * i + 3]);

		start[0] -= tCurrentROI.lLeft;
		start[1] -= tCurrentROI.lTop;
		end[0] -= tCurrentROI.lLeft;
		end[1] -= tCurrentROI.lTop;
		cvLine(ptPicGray, cvPoint(start[0], start[1]), cvPoint(end[0], end[1]), CV_RGB(255, 255, 0), 1, CV_AA, 0);
	}

	sprintf_s(cText, MAX_PATH, "%salRECK_LineDetect_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId, a_lROIId);
	cvSaveImage(cText, ptPicGray, 0);
	cvReleaseImage(&ptPicGray);
#endif


	lPointIndex = 0;
	if (a_lROIId)
	{
		for (i = 0; i < a_lROIId; i++)
		{
			lPointIndex += a_ptCfg->atROICfg[i].lPointNum;
		}
	}

	/// 計算SBV上 理想的 點座標
	aeXTmp[0] = a_ptParameter->atIdealPointRectK[lPointIndex].eX;
	aeXTmp[1] = a_ptParameter->atIdealPointRectK[lPointIndex + 1].eX;
	aeXTmp[2] = a_ptParameter->atIdealPointRectK[lPointIndex + 2].eX;
	aeXTmp[3] = a_ptParameter->atIdealPointRectK[lPointIndex + 3].eX;

	aeYTmp[0] = a_ptParameter->atIdealPointRectK[lPointIndex].eY;
	aeYTmp[1] = a_ptParameter->atIdealPointRectK[lPointIndex + 1].eY;
	aeYTmp[2] = a_ptParameter->atIdealPointRectK[lPointIndex + 2].eY;
	aeYTmp[3] = a_ptParameter->atIdealPointRectK[lPointIndex + 3].eY;

	COMMONK_Birdview2SBV(
        a_ptBVImgSize->lX, a_ptBVImgSize->lY,
        tImgSize.lX, tImgSize.lY,
		a_ptCfg->atROICfg[a_lROIId].lPointNum, a_ptParameter->lAngleCAM,
		a_ptParameter->lCamPosX,
		a_ptParameter->lCamPosY,
		a_ptCfg->atROICfg[a_lROIId].lSBVOffsetX,
		a_ptCfg->atROICfg[a_lROIId].lSBVOffsetY,
		a_ptCfg->atROICfg[a_lROIId].eSBVScale,
		a_ptParameter->eMMPP,
		aeXTmp, aeYTmp,
		aeXSBV, aeYSBV
	);
	/// 計算SBV上 理想的 點座標

#if	(alRECK_DEBUG || BVCAM_FACAUTOK_FAIL_LOG)
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

	g_CamId = lCamId;
	g_ROIId = a_lROIId;
#endif


	ucDetectFlag = RectangleCornerExtract(
        &tImgSize,
        pucLineSegBuffer,
		tCurrentROI, aeXSBV, aeYSBV,
		lLineNum, peLineDetectResult,
		pucSBVBuffer,
		a_peSBVX + lPointIndex, a_peSBVY + lPointIndex
		);

	free(peLineDetectResult);
    if (a_pucBuffer == NULL)
    {
        free(pucSBVBuffer);
    }

	return ucDetectFlag;
}

void	alRECK_Calibration(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucBuffer,
	alRECK_Cfg *a_ptCfg,
	alRECK_Parameter *a_ptParameter,
	UINT8 *a_pucSrcBuffer,
    FLOAT64 a_aeOriginalM33[2][COMMONK_M33_ELEMENT_CNT],
    FLOAT64 a_aeM33RecK[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 *a_peFPRecKX,
	FLOAT64 *a_peFPRecKY,
	UINT8  *a_pucRecKFlag
	)
{
    INT32 lROIIndex = 0, lPointNum = 0, lPointIndex = 0, lCntEnable = 0, i = 0;
	UINT8 aucROIDetectFlag[alRECK_MAX_ROI] = { 0 }, aucROIDetectFlagView = 0;
	FLOAT64 aeFPRecKX[alRECK_MAX_POINT_VIEW] = { 0 }, aeFPRecKY[alRECK_MAX_POINT_VIEW] = { 0 };
	FLOAT64 aeKX[alRECK_MAX_POINT_VIEW] = { 0 }, aeKY[alRECK_MAX_POINT_VIEW] = { 0 };
    FLOAT64 aeKXM33[alRECK_MAX_POINT_VIEW] = { 0 }, aeKYM33[alRECK_MAX_POINT_VIEW] = { 0 };
	FLOAT64 aeIdealX[alRECK_MAX_POINT_VIEW] = { 0 }, aeIdealY[alRECK_MAX_POINT_VIEW] = { 0 };
    FLOAT64 aeIdealXM33[alRECK_MAX_POINT_VIEW] = { 0 }, aeIdealYM33[alRECK_MAX_POINT_VIEW] = { 0 };
	FLOAT64 aeBVX[alRECK_MAX_POINT_VIEW] = { 0 }, aeBVY[alRECK_MAX_POINT_VIEW] = { 0 };
    alPointINT32 tImgSize = { 0 };
#if	alRECK_DEBUG
	FLOAT64 aeX[alRECK_MAX_POINT_VIEW] = { 0 }, aeY[alRECK_MAX_POINT_VIEW] = { 0 };
	FLOAT64 aeX1[alRECK_MAX_POINT_VIEW] = { 0 }, aeY1[alRECK_MAX_POINT_VIEW] = { 0 }, eScale = 0;
	alRectINT32 tROI;
	INT32 lCamId = 0, lOffsetX = 0, lOffsetY = 0;
	UINT8 *pucSBV = NULL;
	IplImage * ptPicGray = NULL;
	char cText[MAX_PATH] = { 0 };
#endif

    tImgSize.lX = a_ptParameter->ptFisheyeModel->uwSrcWidth;
    tImgSize.lY = a_ptParameter->ptFisheyeModel->uwSrcHeight;

	aucROIDetectFlagView = 1;
	for (lROIIndex = 0; lROIIndex < a_ptCfg->lROINum; lROIIndex++)
	{
        // FP (Rectangle corner detection)
		aucROIDetectFlag[lROIIndex] = FPDetect(
            a_ptBVImgSize,
            a_pucBuffer, lROIIndex,
			a_ptCfg, a_ptParameter,
			a_pucSrcBuffer, a_aeOriginalM33[0],
			aeFPRecKX, aeFPRecKY
		);
		aucROIDetectFlagView = aucROIDetectFlagView*aucROIDetectFlag[lROIIndex];

		// set ideal point
		for (lPointIndex = 0; lPointIndex < a_ptCfg->atROICfg[lROIIndex].lPointNum; lPointIndex++)
		{
			aeIdealX[lPointNum + lPointIndex] = a_ptParameter->atIdealPointRectK[lPointNum + lPointIndex].eX;
			aeIdealY[lPointNum + lPointIndex] = a_ptParameter->atIdealPointRectK[lPointNum + lPointIndex].eY;
		}

		// SBV to BV
		COMMONK_SBV2Birdview(
            tImgSize.lX, tImgSize.lY, a_ptBVImgSize->lX, a_ptBVImgSize->lY,
			a_ptCfg->atROICfg[lROIIndex].lPointNum, 
			a_ptParameter->lAngleCAM, a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
			a_ptCfg->atROICfg[lROIIndex].lSBVOffsetX, a_ptCfg->atROICfg[lROIIndex].lSBVOffsetY, a_ptCfg->atROICfg[lROIIndex].eSBVScale,
			a_ptParameter->eMMPP,
			aeFPRecKX + lPointNum, aeFPRecKY + lPointNum, aeBVX + lPointNum, aeBVY + lPointNum
		);

		// BV to DeFishEye domain
		for (lPointIndex = 0; lPointIndex < a_ptCfg->atROICfg[lROIIndex].lPointNum; lPointIndex++)
		{
			// 計算反魚眼座標
			COMMONK_PerformCoordinatesTransform(
				a_aeOriginalM33[0], aeBVX[lPointNum + lPointIndex], aeBVY[lPointNum + lPointIndex],
				&aeKX[lPointNum + lPointIndex], &aeKY[lPointNum + lPointIndex]
			);
		}

		lPointNum += a_ptCfg->atROICfg[lROIIndex].lPointNum;
		/*if (aucROIDetectFlagView == 0)
		{
			break;
		}*/
	}

	if(aucROIDetectFlagView)
	{ // generate M33 by FP
		*a_pucRecKFlag = TRUE;

        // only use the enable FP to generate M33
        lCntEnable = 0;
        for (i = 0; i < lPointNum; i++)
        {
            if (a_ptParameter->aucPointFlag[i] == 0)
            {
                aeKXM33[lCntEnable] = aeKX[i];
                aeKYM33[lCntEnable] = aeKY[i];
                aeIdealXM33[lCntEnable] = aeIdealX[i];
                aeIdealYM33[lCntEnable] = aeIdealY[i];
                lCntEnable++;
            }
        }

        // generate M33
#if 0 // 所有特徵點都用
        if (!COMMONK_GenerateM3x3(aeKX, aeKY, aeIdealX, aeIdealY, lPointNum, a_aeM33RecK[0]))
        {
            assert(0);
        }
#else // 只有被開啟的特徵點
        if (!COMMONK_GenerateM3x3(aeKXM33, aeKYM33, aeIdealXM33, aeIdealYM33, lCntEnable, a_aeM33RecK[0]))
        {
            assert(0);
        }
#endif

        memcpy(a_aeM33RecK[1], a_aeM33RecK[0], sizeof(FLOAT64) * 9);
        alMATRIX_InverseNbyN(a_aeM33RecK[1], 3);

#if	alRECK_DEBUG
        memset(aeX, 0, sizeof(FLOAT64) * 16);
        memset(aeY, 0, sizeof(FLOAT64) * 16);
		for (lPointIndex = 0; lPointIndex < lPointNum; lPointIndex++)
		{
			COMMONK_PerformCoordinatesTransform(
				a_aeM33RecK[1], aeKX[lPointIndex], aeKY[lPointIndex],
				aeX + lPointIndex, aeY + lPointIndex
			);
		}

		for (lPointIndex = 0; lPointIndex < lPointNum; lPointIndex++)
		{
			COMMONK_PerformCoordinatesTransform(
				a_aeM33RecK[0], aeIdealX[lPointIndex], aeIdealY[lPointIndex],
				aeX1 + lPointIndex, aeY1 + lPointIndex
				);
		}

		tROI.lLeft = 0;
		tROI.lTop = 0;
        tROI.lRight = tImgSize.lX - 1;
        tROI.lBottom = tImgSize.lY - 1;
		switch (a_ptParameter->lAngleCAM)
		{
		case alBVCAM_FACAUTOK_BV_LEFT: // -90 degree
            lCamId = alCAMERAINFO_BV_LEFT;
			eScale = 1.6;
			lOffsetX = -100;
			lOffsetY = 60;
			break;
		case alBVCAM_FACAUTOK_BV_RIGHT: // +90 degree
            lCamId = alCAMERAINFO_BV_RIGHT;
			eScale = 1.6;
			lOffsetX = 100;
			lOffsetY = 60;
			break;
		case alBVCAM_FACAUTOK_BV_BACK: // 180 degree
            lCamId = alCAMERAINFO_BV_BACK;
			eScale = 2.5;
			lOffsetX = 0;
			lOffsetY = 100;
			break;
		case alBVCAM_FACAUTOK_BV_FRONT:  // 0 degree
            lCamId = alCAMERAINFO_BV_FRONT;
			eScale = 2.5;
			lOffsetX = 0;
			lOffsetY = -100;
			break;
		default:
			assert(0);
		}

        pucSBV = (UINT8 *)malloc(tImgSize.lX * tImgSize.lY * sizeof(UINT8));
        COMMONK_SBVGeneratingK_YUYV2Y(
            a_ptBVImgSize,
			tROI, a_pucSrcBuffer, a_ptParameter->ptFisheyeModel, a_aeM33RecK[0],
			a_ptParameter->lOriImgYLimit, a_ptParameter->lAngleCAM, 
			a_ptParameter->lCamPosX, a_ptParameter->lCamPosY,
			lOffsetX, lOffsetY, eScale, a_ptParameter->eMMPP,
			pucSBV
		);
        ptPicGray = cvCreateImage(cvSize(tImgSize.lX, tImgSize.lY), IPL_DEPTH_8U, 1);
		memcpy(ptPicGray->imageData, pucSBV, sizeof(UINT8)*ptPicGray->imageSize);
		sprintf_s(cText, MAX_PATH, "%salRECK_SBV_PreK_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, lCamId);
		cvSaveImage(cText, ptPicGray, 0);
		cvReleaseImage(&ptPicGray);
		free(pucSBV);
#endif
	
	}
	else
	{ // use original M33
		*a_pucRecKFlag = FALSE;
        memcpy(a_aeM33RecK[0], a_aeOriginalM33[0], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
        memcpy(a_aeM33RecK[1], a_aeOriginalM33[1], sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
	}
	memcpy(a_peFPRecKX, aeKX, sizeof(FLOAT64) * lPointNum);
	memcpy(a_peFPRecKY, aeKY, sizeof(FLOAT64) * lPointNum);
}
