#include "BVCAM_FACAUTOK/CRSMRKDET.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "basedef.h"

#if alCRSMRKDET_DEBUG > 0
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_DeBug.h"
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_Def.h" // FOR DEBUG
#endif

/* ----------------ROI-----------------------

(Start_X,Start_Y)
.__________________
|                  | ┐
|                  |
|                  |
|        .         |
|(Input_X,Input_Y) |	ROI_height   *Scaling
|                  |
|                  |
|__________________|	┘

└  ROI_width   ┘        *Scaling
*/

/**
*  \addtogroup alCRSMRKDET
*  @{
*/

static FLOAT64	GetAverage(INT32* Nums, INT32 Count);
static FLOAT64	GetVariance_(FLOAT64* Nums, INT32 Count);
static FLOAT64	GetVariance(INT32 *Nums, INT32 Count);
static INT32	GetMedian(INT32 n, INT32 *x);
static INT32	PointsGrouping(UINT8 *a_pucMarkMap, INT32 buf_width, INT32 buf_height, INT32* median_X, INT32* median_Y);
static void	MaskEvaluateGray(INT32 x, INT32 y, INT32 d, UINT8 *src_buf, INT32 buf_width, INT32 buf_height, FLOAT64* MeanIn, FLOAT64* MeanOut, FLOAT64* eVarIn, FLOAT64* eVarOut, FLOAT64* a_peVar);

/**
*  @}
*/

// FLOAT64 g_eScaling;

/*----------------------Serching Size-----------------------------
PattenDis: The size of cross which attempted to mark.
{Size_1,Size_2,...,Size_NumOfSeachingSize}
={FirstSize + 1*IntervalOfSerarchingSize,
FirstSize + 2*IntervalOfSerarchingSize,
...
FirstSize + NumOfSeachingSize * IntervalOfSerarchingSize}

o: internal
x: outer
			 _________
			|         |
	  x	    |    o    |    x
			|         |
			|         |
   _________|         |_________
  |                             |
  |    o         o<------->o    |
  |               PattenDis     |
  |_________           _________|
			|         |
			|         |
       x    |    o    |    x
			|         |
			|_________|
*/

#define NumOfSeachingSize 5
#define FirstSize 5
#define IntervalOfSerarchingSize 3
#define NumOfInter 5
#define NumOfOuter 4



/*                 Further Searching
o:十字內點
			 _________
			|         |
			|    o    |
			|    o    |
			|    o    |
   _________|    o    |_________
  |              o              |
  |    ooooooooooooooooooooo    |
  |              o              |
  |_________     o     _________|
			|    o    |
			|    o    |
			|    o    |
			|         |
			|_________|

Calculate eVarInace of (o)
*/
//最低可行點數量,ex 低於兩個合理點 即宣告PointsGrouping fail
#define NumOfCandiate_LowerBound 2 

BOOL alCRSMRKDET_CrossMarkDetect(
	alCRSMRKDET_Cfg *a_ptCfg,
	alRectINT32 a_tROI, UINT8 *a_pucSrcBuf, INT32 a_lWidth, INT32 a_lHeight,
	INT32 a_In_X, INT32 a_In_Y, INT32* a_plOut_X, INT32* a_plOut_Y
	)
{
	UINT8* pucMarkMap = NULL;
	INT32 PattenDis[NumOfSeachingSize];

	//--------------Tempt Var--------------------
	INT32 d = 0, lX = 0, lY = 0, i, lPixelCnt = 0;
	FLOAT64 eVarOut, eVarIn, eAveIn, eAveOut, eVar = 0, *pePixelBuff = NULL, eMean = 0;
	BOOL bResult;

	pucMarkMap = (UINT8*)malloc(a_lWidth*a_lHeight);
	memset(pucMarkMap, 0x0, a_lWidth*a_lHeight);

	//--------------Scaling Factor---------------
	/*g_eScaling = 2.0;
	pePixelBuff = (FLOAT64*)malloc((INT32)(alCRSMRKDET_ROI_W*g_eScaling*alCRSMRKDET_ROI_H*g_eScaling*sizeof(FLOAT64)));*/

	pePixelBuff = (FLOAT64*)malloc((INT32)(alCRSMRKDET_MAX_MARK_SIZE*4*sizeof(FLOAT64)));
	//alCRSMRKDET_MAX_MARK_SIZE

	//--------------Initial size----------------- 
	for (i = 0; i < NumOfSeachingSize; i++)
	{
		PattenDis[i] = FirstSize + i*IntervalOfSerarchingSize;
	}

#if alCRSMRKDET_DEBUG > 0
	if (g_lCAMID_AutoKDebug == 0 && g_lROIID_AutoKDebug == 2)
	{
		g_lROIID_AutoKDebug = g_lROIID_AutoKDebug;
	}
#endif 
	for (lY = 0 ; lY < a_lHeight; lY++)
	{
		for (lX = 0 ; lX < a_lWidth; lX++)
		{
#if alCRSMRKDET_DEBUG > 0
			if (lX == 27 && lY == 32)
			{
				lX = lX;
			}
#endif 
			for (d = 0; d < NumOfSeachingSize ; d++)
			{
				//--------------Mask mathing--------------------
				MaskEvaluateGray(lX, lY, PattenDis[d], a_pucSrcBuf, a_lWidth, a_lHeight, &eAveIn, &eAveOut, &eVarIn, &eVarOut, &eVar);

				if ((eAveOut - eAveIn) > a_ptCfg->eDifferenceTH && eVarOut < a_ptCfg->eVarianceOutTH && eVar > a_ptCfg->eVarianceTH && eVarIn < a_ptCfg->eVarianceInTH)
				{
					//------------------Further search----------------------
					lPixelCnt = 0;
					eMean = 0;

					for (i = alMAX(lX - PattenDis[d], 0); i<alMIN(lX + PattenDis[d], a_lWidth); i++)
					{
						pePixelBuff[lPixelCnt] = a_pucSrcBuf[i + lY*a_lWidth];
						eMean += pePixelBuff[lPixelCnt];
						lPixelCnt++;
						
					}

					

					// 清楚的 >> ex 左前
					for (i = alMAX(lY - PattenDis[d], 0); i < alMIN(lY + PattenDis[d], a_lHeight); i++)
					{
						pePixelBuff[lPixelCnt] = a_pucSrcBuf[lX + i*a_lWidth];
						eMean += pePixelBuff[lPixelCnt];
						lPixelCnt++;
					}

					eMean /= lPixelCnt;
					
					if (GetVariance_(pePixelBuff, lPixelCnt) < a_ptCfg->eVarianceInDetailTH && (eAveOut - eMean >  a_ptCfg->eDifferenceTH))
					{
						pucMarkMap[lX + lY*a_lWidth] = TRUE;
					}
				}
			}
		}
	}

	if (PointsGrouping(pucMarkMap, a_lWidth, a_lHeight, a_plOut_X, a_plOut_Y) == TRUE)
	{
		bResult = TRUE;
	}
	else
	{
		*a_plOut_X = a_In_X;
		*a_plOut_Y = a_In_Y;
		bResult = FALSE;
	}

	if (pucMarkMap)
	{
		free(pucMarkMap);
	}

	free(pePixelBuff);

	return bResult;
}


//input box ::符合in5out4規則保留下來的點
static void   MaskEvaluateGray(INT32 x, INT32 y, INT32 d, UINT8 *src_buf, INT32 buf_width, INT32 buf_height, FLOAT64* MeanIn, FLOAT64* MeanOut, FLOAT64* eVarIn, FLOAT64* eVarOut, FLOAT64* a_peVar)
{
	INT32 i, j, InNum = 0, OutNum = 0, eAveIn[NumOfInter], eAveOut[NumOfOuter], Ave[1300] = { 0 }, lNum = 0;
	//Inter 5
	for (i = y - d; i <= y + d; i = i + d)
	{
		if (i >= 0 && i < buf_height && x >= 0 && x < buf_width)
		{
			eAveIn[InNum] = (INT32)src_buf[x + i*buf_width];
			InNum++;
		}
	}

	if ((x - d) >= 0 && (x - d)<buf_width)
	{
		eAveIn[InNum] = (INT32)src_buf[(x - d) + y*buf_width];//左內
		InNum++;
	}
	if ((x + d) >= 0 && (x + d)<buf_width)
	{
		eAveIn[InNum] = (INT32)src_buf[(x + d) + y*buf_width];//右內
		InNum++;
	}

	//Outer 4
	for (i = x - d; i <= x + d; i += d * 2)
	{
		for (j = y - d; j <= y + d; j += d * 2)
		{
			if (i >= 0 && i<buf_width&&j >= 0 && j<buf_height)
			{
				eAveOut[OutNum] = (INT32)src_buf[i + j*buf_width];

				OutNum++;
			}
		}
	}

	for (i = x - d; i <= x + d; i++)
	{
		for (j = y - d; j <= y + d; j++)
		{
			if (i >= 0 && i<buf_width&&j >= 0 && j<buf_height)
			{
				Ave[lNum] = (INT32)src_buf[i + j*buf_width];
				lNum++;
			}
		}
	}

	if (lNum)
	{
		*a_peVar = GetAverage(Ave, lNum);
		*a_peVar = GetVariance(Ave, lNum);
	}

	//-------算平均值&變異數--------
	// if (InNum != FALSE && OutNum != FALSE)
	if (InNum > 4 && OutNum != FALSE)
	{
		*MeanIn = GetAverage(eAveIn, InNum);
		*MeanOut = GetAverage(eAveOut, OutNum);
		*eVarIn = GetVariance(eAveIn, InNum);
		*eVarOut = GetVariance(eAveOut, OutNum);
	}
}

static INT32 PointsGrouping(UINT8 *a_pucMarkMap, INT32 buf_width, INT32 buf_height, INT32* median_X, INT32* median_Y)
{
#if alCRSMRKDET_DEBUG > 0
	IplImage * ptPicGray = NULL;
	char text[MAX_PATH];
#endif
	INT32 RedNum = 0;
	INT32 Xmean, Ymean, x, y;
	INT32* NumsX = (INT32*)malloc(buf_width*buf_height*sizeof(INT32));
	INT32* NumsY = (INT32*)malloc(buf_width*buf_height*sizeof(INT32));

#if alCRSMRKDET_DEBUG == 1 // log Result
	sprintf_s(text, MAX_PATH, "%salCROSSMARKK_SBV_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, g_lCAMID_AutoKDebug, g_lROIID_AutoKDebug);
	ptPicGray = cvLoadImage(text, CV_LOAD_IMAGE_COLOR);
#endif

	//掃ROI pixels
	for (y = 0; y< buf_height; y++)
	{
		for (x = 0; x< buf_width; x++)
		{
			if (a_pucMarkMap[x + y*buf_width] == TRUE)
			{
				NumsX[RedNum] = x;
				NumsY[RedNum] = y;
				RedNum++;
#if alCRSMRKDET_DEBUG == 1 // log Result
				cvSet2D(ptPicGray, y, x, CV_RGB(255, 0, 0));//特別注意 給值是 (y,x)
#endif
			}
		}
	}
	Xmean = GetMedian(RedNum, NumsX);
	Ymean = GetMedian(RedNum, NumsY);
#if alCRSMRKDET_DEBUG == 1 // log Result
	cvLine(ptPicGray, cvPoint(Xmean - 3, Ymean), cvPoint(Xmean + 3, Ymean), CV_RGB(255, 0, 0), 1, CV_AA, 0);
	cvLine(ptPicGray, cvPoint(Xmean, Ymean - 3), cvPoint(Xmean, Ymean + 3), CV_RGB(255, 0, 0), 1, CV_AA, 0);
	sprintf_s(text, MAX_PATH, "%salCROSSMARKK_FP_LOG_%d_%d.jpg", g_acalBVCAM_FACAUTOK_OutputFolder, g_lCAMID_AutoKDebug, g_lROIID_AutoKDebug);
	cvSaveImage(text, ptPicGray, 0);
	cvReleaseImage(&ptPicGray);
#endif

    free(NumsX);
    free(NumsY);

	if (RedNum >= NumOfCandiate_LowerBound)
	{
		*median_X = Xmean;
		*median_Y = Ymean;
		return TRUE;
	}
	
    return FALSE;
}

static FLOAT64 GetAverage(INT32* Nums, INT32 Count)
{
	FLOAT64 sum = 0;
	INT32 i;

	for (i = 0; i < Count; i++)
	{
		sum += Nums[i];
	}

	return sum / (FLOAT64)Count;
}

static FLOAT64 GetVariance_(FLOAT64* Nums, INT32 Count)
{
	FLOAT64 sum, mean;
	INT32 i;
	sum = 0;
	for (i = 0; i < Count; i++)
	{
		sum = sum + Nums[i];
	}
	mean = sum / (FLOAT64)Count;
	sum = 0;
	for (i = 0; i < Count; i++)
	{
		sum += (Nums[i] - mean)*(Nums[i] - mean);
	}

	return sum / (FLOAT64)Count;
}
static FLOAT64 GetVariance(INT32* Nums, INT32 Count)
{
	FLOAT64 sum, mean;
	INT32 i;

	sum = 0;
	for (i = 0; i < Count; i++)
	{
		sum += Nums[i];
	}

	mean = sum / (FLOAT64)Count;
	sum = 0;
	for (i = 0; i < Count; i++)
	{
		sum += (Nums[i] - mean)*(Nums[i] - mean);
	}

	return sum / (FLOAT64)Count;
}


static INT32 GetMedian(INT32 n, INT32* x)
{
	INT32 temp;
	INT32 i, j;
	// the following two loops sort the array x in ascending order
	for (i = 0; i<n - 1; i++) {
		for (j = i + 1; j<n; j++) {
			if (x[j] < x[i]) {
				// swap elements
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
		}
	}

	if (n % 2 == 0)
	{
		// if there is an even number of elements, return mean of the two elements in the middle
		return(x[n / 2 - 1]);
	}
	else {
		// else return the element in the middle
		return x[n / 2];
	}
}



