#include  "alStatistic_BirdView.h"

#include "ImageProc.h"
#include "alGAE_AVM.h"



void alStatistic_MeanEstimateForTopView_3ROIsPerView(UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer, alSTATISTIC_Data *a_ptalSTATISTIC_Data)
{
    UINT32 ulCnt[3];
    UINT32 ulMean[2];
    INT16 wCameraIndex, /*x, y, wPosX, wPosY, wPos,*/ wCnt;
    INT16 wSize[24] ={
        // left
        20,258,
        20,258,
        20,238,
        // right
        20,258,
        20,258,
        20,238,
        // front
        266,20,
        266,20,
        156,20,
        // rear
        266,20,
        266,20,
        156,20
    };
    INT16 wStartPoint[24] ={
        // left
        32,111,
        62,111,
        94,121,
        // right
        280,111,
        250,111,
        218,121,
        // front
        33,8,
        33,40,
        88,80,
        // rear
        33,452,
        33,420,
        88,380
    };
    for(wCameraIndex = 0 ; wCameraIndex < 4 ; wCameraIndex++){
        for(wCnt = 0 ; wCnt < 3; wCnt++){
            a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIArea.lX = wSize[2*(3*wCameraIndex+wCnt)];
            a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIArea.lY = wSize[2*(3*wCameraIndex+wCnt)+1];
            a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIStartPoint.lX = wStartPoint[2*(3*wCameraIndex+wCnt)];
            a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIStartPoint.lY = wStartPoint[2*(3*wCameraIndex+wCnt)+1];
             ImgProc_ROISeperateMean(
                a_pucBuffer, 
                a_ulWidth, 
                a_ulHeight, 
                a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIStartPoint.lX, 
                a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIStartPoint.lY, 
                a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIArea.lX, 
                a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].tROIArea.lY, 
                YMEAN_TARGET, 
                &(a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ucGeneralMean),
                &(a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ucLowMean),
                &(a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ulLowMeanPixelCnt),
                &(a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ucHighMean),
                &(a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ulHighMeanPixelCnt)
            );
        }
    }
    for(wCameraIndex = 0 ; wCameraIndex < 4 ; wCameraIndex++){
        
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucHighMean = 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucLowMean = 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucGeneralMean = 0;
         ulCnt[0] = 0;
         ulCnt[1] =0;
         ulCnt[2] = 0;
         ulMean[0] = 0;
         ulMean[1] = 0;
        for(wCnt = 0 ; wCnt < 3; wCnt++){
            ulMean[0] += a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ucLowMean * a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ulLowMeanPixelCnt; 
            ulMean[1] += a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ucHighMean * a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ulHighMeanPixelCnt;
            ulCnt[0] += a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ulLowMeanPixelCnt;
            ulCnt[1] += a_ptalSTATISTIC_Data->atBirdViewROIMean_3ROIsPerView[3*wCameraIndex + wCnt].ulHighMeanPixelCnt;
        }
        ulCnt[2] = ulCnt[0] + ulCnt[1];
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucGeneralMean = (ulMean[0] + ulMean[1]) / ulCnt[2];
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucHighMean = (ulCnt[1]) ? ulMean[1] / ulCnt[1] : 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucLowMean = (ulCnt[0]) ? ulMean[0] / ulCnt[0] : 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ulHighMeanPixelCnt = ulCnt[1];
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ulLowMeanPixelCnt = ulCnt[0];
    }
}



void alStatistic_MeanEstimateForTopView_10ROIsPerView(alSTATISTIC_Cfg   *a_ptCfg, UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer, alSTATISTIC_Data *a_ptalSTATISTIC_Data)
{
    UINT32 ulCnt[3];
    UINT32 ulMean[2];
    INT16 wCameraIndex, /*x, y, wPosX, wPosY, wPos,*/ wCnt;
	UINT8 ucCountPerCamera = 10;
	UINT16 ulTmpIdx = 0;
    for(wCameraIndex = 0 ; wCameraIndex < COMMONK_NUM_BV_CHANNEL ; wCameraIndex++)
    {   //總共有4個CAMERA VIEW (left/right/front/rear)
		if (a_ptCfg->atBirdViewMeanCalInfo[wCameraIndex].ucFunctionEnabled == 1)
		{
			ucCountPerCamera = a_ptCfg->atBirdViewMeanCalInfo[wCameraIndex].ucROICnt_MeanCal;
			for(wCnt = 0 ; wCnt < ucCountPerCamera; wCnt++)
			{  //每個VIEW分為4,4,2

				ulTmpIdx = ucCountPerCamera*wCameraIndex + wCnt;

				//Tina Tsai, 2014/10/28, Modify the statistic ROI configure data from EagleK2 setting 
				a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIArea.lX = a_ptCfg->atBirdViewMeanCalInfo[wCameraIndex].atROIAreaSize_MeanCal[wCnt].lX;
				a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIArea.lY = a_ptCfg->atBirdViewMeanCalInfo[wCameraIndex].atROIAreaSize_MeanCal[wCnt].lY;
				a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIStartPoint.lX = a_ptCfg->atBirdViewMeanCalInfo[wCameraIndex].atROIStartPoints_MeanCal[wCnt].lX;
				a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIStartPoint.lY = a_ptCfg->atBirdViewMeanCalInfo[wCameraIndex].atROIStartPoints_MeanCal[wCnt].lY;

				 ImgProc_ROISeperateMean(
					a_pucBuffer, 
					a_ulWidth, 
					a_ulHeight, 
					a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIStartPoint.lX, 
					a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIStartPoint.lY, 
					a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIArea.lX, 
					a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].tROIArea.lY, 
					YMEAN_TARGET, 
					&(a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ucGeneralMean),
					&(a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ucLowMean),
					&(a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ulLowMeanPixelCnt),
					&(a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ucHighMean),
					&(a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ulHighMeanPixelCnt)
				);
			}
		}
    }

    for(wCameraIndex = 0 ; wCameraIndex < COMMONK_NUM_BV_CHANNEL ; wCameraIndex++)
    {
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucHighMean = 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucLowMean = 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucGeneralMean = 0;
		ulCnt[0] = ulCnt[1] = ulCnt[2] = 0;
		ulMean[0] = ulMean[1] = 0;
        for(wCnt = 0 ; wCnt < ucCountPerCamera; wCnt++)
        {
			ulTmpIdx = ucCountPerCamera*wCameraIndex + wCnt;

            ulMean[0] += a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ucLowMean * a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ulLowMeanPixelCnt; 
            ulMean[1] += a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ucHighMean * a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ulHighMeanPixelCnt;
            ulCnt[0] += a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ulLowMeanPixelCnt;
            ulCnt[1] += a_ptalSTATISTIC_Data->atBirdViewROIMean_10ROIsPerView[ulTmpIdx].ulHighMeanPixelCnt;
        }
        ulCnt[2] = ulCnt[0] + ulCnt[1];
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucGeneralMean = (ulMean[0] + ulMean[1]) / ulCnt[2];
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucHighMean = (ulCnt[1]) ? ulMean[1] / ulCnt[1] : 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ucLowMean = (ulCnt[0]) ? ulMean[0] / ulCnt[0] : 0;
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ulHighMeanPixelCnt = ulCnt[1];
        a_ptalSTATISTIC_Data->atSingleViewROIMean[wCameraIndex].ulLowMeanPixelCnt = ulCnt[0];
    }
}
