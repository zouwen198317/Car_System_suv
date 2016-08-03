
#include "alStatistic_SingleView.h"
#include "ImageProc.h"



#if 0
/** \brief The predefined ROI position for the statistical mean calculation. */
UINT32  g_ulROIStartPosOfMeanCal[8] = {
    140, 162,
    140, 162,   
    140, 290,   
    140, 220,
};

/** \brief The predefined ROI position for the statistical mean calculation. */
UINT32  g_ulROIAreaSizeOfMeanCal[8] = {
    440,120,
    440,120,
    440,120,
    440,120,
};

void alStatistic_MeanCal(UINT8 ** a_pucSrcBuffer, UINT32 a_ulImageWidth, UINT32 a_ulImageHeight, UINT8 a_ucYMeanTh)
{
    UINT8 ucCameraIndex;
    alSTATISTIC_StatistcalMean * ptSingleViewROIMean = g_atStatistc_SingleViewROIMean;

    for(ucCameraIndex = 0; ucCameraIndex < COMMONK_NUM_BV_CHANNEL; ucCameraIndex++, ptSingleViewROIMean++)
    {
        ptSingleViewROIMean->tROIStartPoint.lX = g_ulROIStartPosOfMeanCal[(ucCameraIndex<<1)];
        ptSingleViewROIMean->tROIStartPoint.lY = g_ulROIStartPosOfMeanCal[(ucCameraIndex<<1)+1];
        ptSingleViewROIMean->tROIArea.lX = g_ulROIAreaSizeOfMeanCal[(ucCameraIndex<<1)];
        ptSingleViewROIMean->tROIArea.lY = g_ulROIAreaSizeOfMeanCal[(ucCameraIndex<<1)+1];
        ptSingleViewROIMean->bEnableLowHightMean = TRUE;

        ImgProc_ROISeperateMean(
            a_pucSrcBuffer[ucCameraIndex], 
            a_ulImageWidth, 
            a_ulImageHeight, 
            ptSingleViewROIMean->tROIStartPoint.lX, 
            ptSingleViewROIMean->tROIStartPoint.lY, 
            ptSingleViewROIMean->tROIArea.lX, 
            ptSingleViewROIMean->tROIArea.lY, 
            a_ucYMeanTh, 
            &(ptSingleViewROIMean->ucGeneralMean),
            &(ptSingleViewROIMean->ucLowMean),
            &(ptSingleViewROIMean->ulLowMeanPixelCnt),
            &(ptSingleViewROIMean->ucHighMean),
            &(ptSingleViewROIMean->ulHighMeanPixelCnt)
            );
    }

}


#define STASTIC_NOISE_ROI_CNT   2
/** \brief The predefined ROI position for the statistical mean calculation. */
UINT32  g_ulROIStartPosOfNoiseCal[8] = {
    14, 426,
    681, 426,   
    0, 0,   
    0, 0,
};

/** \brief The predefined ROI position for the statistical mean calculation. */
UINT32  g_ulROIAreaSizeOfNoiseCal[8] = {
    24, 24,
    24, 24,
    24, 24,
    24, 24,
};
#endif

void alStatistic_NoiseLevelEstimation(
    alSTATISTIC_Cfg    *a_ptCfg, UINT8 ** a_pucSrcBuffer, 
    UINT32 a_ulImageWidth, UINT32 a_ulImageHeight,
    alSTATISTIC_Data *a_ptData
    )
{
    UINT8 ucCameraIndex, ucROIIndex, ucCountPerCamera = 0;
    UINT32 ulPixelCnt = 0;
    alSTATISTIC_StatistcalNoiseLevel * ptSingleViewNoiseLevel = a_ptData->atSingleViewNoiseLevel;
    UINT32 ulNoiseLevel;

    

    a_ptData->ucGlobalNoiseLevel = 0;
    for(ucCameraIndex = 0; ucCameraIndex < COMMONK_NUM_BV_CHANNEL - 1; ucCameraIndex++, ptSingleViewNoiseLevel++) // Rear View ¤£¦C¤J­pºâ
    {
		if (a_ptCfg->atSingleViewNoiseCalInfo[ucCameraIndex].ucFunctionEnabled == 1)
		{
			ulNoiseLevel = 0;
			ulPixelCnt = 0;
			ucCountPerCamera = a_ptCfg->atSingleViewNoiseCalInfo[ucCameraIndex].ucROICnt_NoiseCal;

			for(ucROIIndex = 0; ucROIIndex < ucCountPerCamera; ucROIIndex++) 
			{
				//Tina Tsai, 2014/10/28, Modify the statistic ROI configure data from EagleK2 setting
				ptSingleViewNoiseLevel->tROIStartPoint[ucROIIndex].lX = a_ptCfg->atSingleViewNoiseCalInfo[ucCameraIndex].atROIStartPoints_NoiseCal[ucROIIndex].lX;
				ptSingleViewNoiseLevel->tROIStartPoint[ucROIIndex].lY = a_ptCfg->atSingleViewNoiseCalInfo[ucCameraIndex].atROIStartPoints_NoiseCal[ucROIIndex].lY;
				ptSingleViewNoiseLevel->tROIArea[ucROIIndex].lX = a_ptCfg->atSingleViewNoiseCalInfo[ucCameraIndex].atROIAreaSize_NoiseCal[ucROIIndex].lX;
				ptSingleViewNoiseLevel->tROIArea[ucROIIndex].lY = a_ptCfg->atSingleViewNoiseCalInfo[ucCameraIndex].atROIAreaSize_NoiseCal[ucROIIndex].lY;

				ulPixelCnt += ptSingleViewNoiseLevel->tROIArea[ucROIIndex].lX * (ptSingleViewNoiseLevel->tROIArea[ucROIIndex].lY - 1);

				ImgProc_NoiseEstimation(
					a_pucSrcBuffer[ucCameraIndex], 
					a_ulImageWidth, 
					a_ulImageHeight, 
					ptSingleViewNoiseLevel->tROIStartPoint[ucROIIndex].lX,
					ptSingleViewNoiseLevel->tROIStartPoint[ucROIIndex].lY,
					ptSingleViewNoiseLevel->tROIArea[ucROIIndex].lX,
					ptSingleViewNoiseLevel->tROIArea[ucROIIndex].lY,
					&ulNoiseLevel
					);

			}
			ulNoiseLevel = 20 * ulNoiseLevel / ulPixelCnt;

			if(ulNoiseLevel > 100) ptSingleViewNoiseLevel->ucNoiseLevel = 100;
			else if(ulNoiseLevel == 0) ptSingleViewNoiseLevel->ucNoiseLevel = 1;
			else ptSingleViewNoiseLevel->ucNoiseLevel = ulNoiseLevel;

			if(a_ptData->ucGlobalNoiseLevel < ptSingleViewNoiseLevel->ucNoiseLevel)
				a_ptData->ucGlobalNoiseLevel = ptSingleViewNoiseLevel->ucNoiseLevel;
		}
    }

}
