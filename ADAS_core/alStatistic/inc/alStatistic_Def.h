#pragma once

#include "CommonK_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \defgroup alSTATISTIC
*  @{
*/

/** \brief Define the maximum ROI number for mean calculation. */
#define alSTATISTIC_BIRDVIEWMEANCALINFO_MAX_ROI_NUM 10
/** \brief Define the maximum ROI number for noise calculation. */
#define alSTATISTIC_SINGLEVIEWNOISEALINFO_MAX_ROI_NUM 4


/** \brief Define the structure for the ROI mean calculation. */
typedef struct 
{

    /** \brief The start point of the ROI region in the specific camera image. */
    alPointINT32 tROIStartPoint;
    /** \brief The area size of the ROI region in the specific camera image. */
    alPointINT32 tROIArea;

    /** \brief The general mean value in the ROI region. */
    UINT8 ucGeneralMean;

    /** Indicae if the general mean value should be computed. */
    BOOL bEnableLowHightMean;
    /** \brief The mean value with pixel value lower than threshold in the ROI region. */
    UINT8 ucLowMean;
    /** \brief The mean value with pixel value higher than threshold in the ROI region. */
    UINT8 ucHighMean;
    /** \brief The pixel count with pixel value lower than threshold in the ROI region. */
    UINT32 ulLowMeanPixelCnt;
    /** \brief The pixel count with pixel value higher than threshold in the ROI region. */
    UINT32 ulHighMeanPixelCnt;

} alSTATISTIC_StatistcalMean;

/** \brief Define the structure for the ROI noise level estimation. */
typedef struct 
{

    /** \brief The start point of the ROI region in the specific camera image. */
    alPointINT32 tROIStartPoint[4];
    /** \brief The area size of the ROI region in the specific camera image. */
    alPointINT32 tROIArea[4];

    /** \brief The pixel count with pixel value higher than threshold in the ROI region. 1 ~ 100 */
    UINT8 ucNoiseLevel;

} alSTATISTIC_StatistcalNoiseLevel;

/** \brief Define the structure of ROI information for mean calculation. */
typedef struct
{
    /** \brief Enable or disable the function of mean calculation at current view? */
	UINT8 ucFunctionEnabled;

    /** \brief Define the ROI counts at current view */
	UINT8 ucROICnt_MeanCal;

    /** \brief The start point of the ROI region in the specific camera image. */
	alPointINT32       atROIStartPoints_MeanCal[alSTATISTIC_BIRDVIEWMEANCALINFO_MAX_ROI_NUM];
 
	/** \brief The area size of the ROI region in the specific camera image. */   
	alPointINT32       atROIAreaSize_MeanCal[alSTATISTIC_BIRDVIEWMEANCALINFO_MAX_ROI_NUM];

} alSTATISTIC_BirdViewMeanCalInfo;

/** \brief Define the structureof of ROI information for noise level estimation. */
typedef struct
{
    /** \brief Enable or disable the function of noise level estimation at current camera? */
	UINT8 ucFunctionEnabled;
   
    /** \brief Define the ROI counts at current view */
	UINT8 ucROICnt_NoiseCal;

	/** \brief The start point of the ROI region in the specific camera image. */
	alPointINT32       atROIStartPoints_NoiseCal[alSTATISTIC_SINGLEVIEWNOISEALINFO_MAX_ROI_NUM];

	/** \brief The area size of the ROI region in the specific camera image. */    
	alPointINT32       atROIAreaSize_NoiseCal[alSTATISTIC_SINGLEVIEWNOISEALINFO_MAX_ROI_NUM];

} alSTATISTIC_SingleViewNoiseCalInfo;


	
/** \brief Define the structure for the configure data of statistical calculation. */
typedef struct
{
    /** \brief ROI information for mean calculation*/
    alSTATISTIC_BirdViewMeanCalInfo   atBirdViewMeanCalInfo[COMMONK_NUM_BV_CHANNEL];
    /** \brief ROI information for noise level estimation.*/
    alSTATISTIC_SingleViewNoiseCalInfo  atSingleViewNoiseCalInfo[COMMONK_MAX_CAMERA_NUM];

} alSTATISTIC_Cfg;


/** \brief Define the structure for the configure data of statistical calculation. */
typedef struct
{
    /** \brief Record the statistical mean of the BV cameras. */
    alSTATISTIC_StatistcalMean  atSingleViewROIMean[COMMONK_NUM_BV_CHANNEL];
    
    /** \brief Record the statistical noise level of the BV cameras. */
    alSTATISTIC_StatistcalNoiseLevel    atSingleViewNoiseLevel[COMMONK_NUM_BV_CHANNEL];
    
    /** \brief Record the current averaging noise level. */
    UINT8 ucGlobalNoiseLevel;

    /** \brief Store the mean estimation result for 3 ROIs per-view. */
    alSTATISTIC_StatistcalMean  atBirdViewROIMean_3ROIsPerView[12];

    /** \brief Store the mean estimation result for 10 ROIs per-view. */
    alSTATISTIC_StatistcalMean  atBirdViewROIMean_10ROIsPerView[COMMONK_NUM_BV_CHANNEL * 10];

} alSTATISTIC_Data;


/** \brief To load the statistic default setting by default values. */
void alSTATISTIC_LoadDefault(alSTATISTIC_Cfg *a_ptCfg);

/**
*  @}
*/
#ifdef __cplusplus
}
#endif
