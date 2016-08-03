
//#include "c6x.h"			// ADD BY ANCRE AT 2013 07 01 for clock tick on board
#include "alGAE_AVM.h"
#include <math.h>
#include <assert.h>

#ifdef WIN32    // Visual C++ platform
#include "dat_copy.h"
#else           // Eagle2 platform
  #include <csl_dat.h>
  #include "ioutil.h"		// add by ancre hsieh at 2013 07 19 for IOprintf~~~
  #include "c6x.h"	        // ADD BY ANCRE AT 2013 03 08 for estimate the performance
#endif

// #include "alTILIBDef.h" // for g_ucL2_SRAM size: DSP_L2_SIZE : g_ulL2Size

#ifdef WIN32
static UINT8 g_ucL2_SRAM[192 * 1024];  // g_ucL2_SRAM[192 * 1024];
  static UINT8 * g_L2_SRAM_ROI_DSP = &(g_ucL2_SRAM[0]);
  static UINT8 * g_L2_SRAM_ROI_DMA = &(g_ucL2_SRAM[0]);

  // 4(view) * 2(ROI per View) * 2(YUV422) * MAX_ROI_SIZE
  static UINT16 * g_puwL2_SRAM_Hist_DSP = (UINT16 *)(g_ucL2_SRAM + (4 * 2 * 2 * MAX_ROI_SIZE*MAX_ROI_SIZE));
  static UINT16 * g_puwL2_SRAM_Hist_DMA = (UINT16 *)(g_ucL2_SRAM + (4 * 2 * 2 * MAX_ROI_SIZE*MAX_ROI_SIZE));
#else
  static UINT8 * g_L2_SRAM_ROI_DSP = (UINT8 *) 0x10800000;
  static UINT8 * g_L2_SRAM_ROI_DMA = (UINT8 *) 0x40800000;

  // 4(view) * 2(ROI per View) * 2(YUV422) * MAX_ROI_SIZE
  static UINT16 * g_puwL2_SRAM_Hist_DSP = (UINT16 *)(0x10800000 + (4 * 2 * 2 * MAX_ROI_SIZE*MAX_ROI_SIZE));
  static UINT16 * g_puwL2_SRAM_Hist_DMA = (UINT16 *)(0x40800000 + (4 * 2 * 2 * MAX_ROI_SIZE*MAX_ROI_SIZE));
#endif

#ifdef WIN32    // Visual C++ platform
 
#else           // Eagle2 platform
  #define min _min2
  #define max _max2	
#endif

enum VIEW_INDEX{
    VIEW_LEFT = 0,
    VIEW_RIGHT = 1,
    VIEW_FRONT = 2,
    VIEW_REAR = 3,
    VIEW_TOTAL_CNT = 4
};

enum CORRELATION{
    BIN_NUM = 128,
    CROSS_OFFSET = 64,
    CROSS_ROUGH_STEP = 8,
    CROSS_DETAIL_STEP = 1,
    //Normalize = 900,
    BIN_GAP = 1,
};

/*************************global variable for testing*************************/
#if  alGAE_AVM_LOG
UINT32 g_ulalGAE_AVM_MeanOSD_Debug[8];
#endif
/*************************global variable for testing*************************/

void alGAE_AVM_InitData(alGAE_AVM_Data *a_ptData){
    memset(a_ptData, 0, sizeof(alGAE_AVM_Data));
}

static void TableGenerator(INT32 *a_pCOMPENSATE_MAX_VIEW_TABLE){
    INT32 lGapY,i;
    INT32 lGapX;
    FLOAT64 eSlope;
    for(i = 0 ; i < 100 ; i++){
        a_pCOMPENSATE_MAX_VIEW_TABLE[i] = COMPENSATE_MAX_VIEW_LOW;
    }
    lGapY = COMPENSATE_MAX_VIEW - COMPENSATE_MAX_VIEW_LOW;
    lGapX = NOISE_TH_HIGH - NOISE_TH_LOW;
    eSlope = (FLOAT64)lGapY / (FLOAT64)lGapX;
    for(i = 0 ; i < lGapX ; i++){
        a_pCOMPENSATE_MAX_VIEW_TABLE[i] = COMPENSATE_MAX_VIEW - (INT32)(eSlope*i);
    }
}

static int Global_AE_MaxOffsetDecision(alCARINFO_Set *a_ptCarInputInfo, INT32 a_lNoise)
{
    INT32 lNoiseMax = 0/*, i*/;
    INT32 COMPENSATE_MAX_VIEW_TABLE[100];
    TableGenerator(COMPENSATE_MAX_VIEW_TABLE);
    
#ifdef WIN32
    if (a_ptCarInputInfo->ucBrake == alCARINFO_BRAKE_ACTIVE) // 20131230 - Chinson: This constrain is for demo only, should be disable in FW release.
    {
        return 0;
    }
#endif
    if (a_ptCarInputInfo->ucLowHeadLight == alCARINFO_HEADLIGHT_ON)
    {
        return COMPENSATE_MAX_VIEW_LOW;
    }
    else
    {
        if(a_lNoise <= NOISE_TH_LOW){                   // no noise
            return COMPENSATE_MAX_VIEW;
        }else if(a_lNoise >= NOISE_TH_HIGH){          // no noise
            return COMPENSATE_MAX_VIEW_LOW;
        }else{                                                                   // with weighting
            return COMPENSATE_MAX_VIEW_TABLE[a_lNoise - NOISE_TH_LOW - 1];
        }
    }
}



static void Sorting(int *aulROIYMeanSorting,int ulCnt_Peak){
	int k = 0,p = 0;
	int ulROISorting_Buff = 0;
	for( k = 0; k < ulCnt_Peak; k++) 
	{	// 排序
		for( p = k+1; p < ulCnt_Peak; p++) 
		{
			if( aulROIYMeanSorting[p] < aulROIYMeanSorting[k] ) 
			{
				ulROISorting_Buff = aulROIYMeanSorting[k];
				aulROIYMeanSorting[k] = aulROIYMeanSorting[p];
				aulROIYMeanSorting[p] = ulROISorting_Buff;
			}
		}
	}
}



/** \brief Calculate semi-variance : only do (X-Mean)^2 without divided by N-1 */
#ifdef WIN32
static INT32 CalVariance(UINT16 *a_puwHistogram, INT16 a_wBinCount, INT32 a_lMean)
#else
static INT32 CalVariance(UINT16 * restrict a_puwHistogram, INT16 a_wBinCount, INT32 a_lMean)
#endif
{
    INT16 wBinIndex;
    register INT32 lDiff;
    register INT32 lVariance = 0;

#ifndef WIN32
    #pragma MUST_ITERATE(1, ,1)
#endif
    for(wBinIndex = 0 ; wBinIndex < BIN_NUM ; wBinIndex++)
    {
        lDiff = a_puwHistogram[wBinIndex] - a_lMean;
        lVariance += lDiff * lDiff;
    }
    return lVariance;
}

#ifdef WIN32
static FLOAT32 Cross_Correlation(UINT16 *a_puwHistogram1, UINT16 *a_puwHistogram2, INT16 a_wBinCount, INT32 a_lMean1, INT32 a_lMean2, INT32 a_lVariance1, INT32 a_lVariance2)
#else
static FLOAT32 Cross_Correlation(UINT16 * restrict a_puwHistogram1, UINT16 * restrict a_puwHistogram2, INT16 a_wBinCount, INT32 a_lMean1, INT32 a_lMean2, INT32 a_lVariance1, INT32 a_lVariance2)
#endif
{
    INT16    wTouIndex, wBinIndex;
    register INT32 lCrossValue = 0;

    INT32    lMaxCorrRough = 0;
    INT32    lMaxCorrDetail = 0;
    INT16    wBinStart, wBinEnd;
    INT32    lOptimalBinPosRougn = 0;
    INT32    lOptimalBinPosDetail = 0;


    // check Y, check U and check V      >> find offset
#ifndef WIN32
    #pragma MUST_ITERATE(1, ,1)
#endif
    for(wTouIndex = -CROSS_OFFSET ; wTouIndex <= CROSS_OFFSET ; wTouIndex += CROSS_ROUGH_STEP)
    {

        lCrossValue = 0;

        wBinStart = max(0, wTouIndex);
        wBinEnd = min(a_wBinCount, wTouIndex + a_wBinCount);
    
#ifndef WIN32
        #pragma MUST_ITERATE(1, ,1)
#endif
        for(wBinIndex = wBinStart ; wBinIndex < wBinEnd ; wBinIndex++)
        {
            lCrossValue += (a_puwHistogram1[wBinIndex] - a_lMean1) * (a_puwHistogram2[wBinIndex - wTouIndex] - a_lMean2);
        }

        if(lMaxCorrRough < lCrossValue)
        {
            lMaxCorrRough = lCrossValue;
            lOptimalBinPosRougn = wTouIndex;
        }

   }

    lMaxCorrDetail = lMaxCorrRough;
    lOptimalBinPosDetail = lOptimalBinPosRougn;

    // check Y, check U and check V      >> find offset
#ifndef WIN32
    #pragma MUST_ITERATE(1, ,1)
#endif
    for(wTouIndex = lOptimalBinPosRougn-(CROSS_ROUGH_STEP>>1) ; wTouIndex <= lOptimalBinPosRougn+(CROSS_ROUGH_STEP>>1) ; wTouIndex += CROSS_DETAIL_STEP)
    {

        lCrossValue = 0;

        wBinStart = max(0, wTouIndex);
        wBinEnd = min(a_wBinCount, wTouIndex + a_wBinCount);

#ifndef WIN32
        #pragma MUST_ITERATE(1, ,1)
#endif
        for(wBinIndex = wBinStart ; wBinIndex < wBinEnd ; wBinIndex++)
        {
            lCrossValue += (a_puwHistogram1[wBinIndex] - a_lMean1) * (a_puwHistogram2[wBinIndex - wTouIndex] - a_lMean2);
        }

        if(lMaxCorrDetail < lCrossValue)
        {
            lMaxCorrDetail = lCrossValue;
            lOptimalBinPosDetail = wTouIndex;
        }

    }

    // 避免除以 0
    if(a_lVariance1 == 0) a_lVariance1 = 1;
    if(a_lVariance2 == 0) a_lVariance2 = 1;

    return ((FLOAT32) lMaxCorrDetail / (FLOAT32)(sqrt((FLOAT32)a_lVariance1*(FLOAT32)a_lVariance2)));

}

static INT16 OffsetAverageFlow(UINT16 index, INT8 cOffset){
    INT32 i = 0;
    INT16 SumTemp = 0, wAverageOut;
    static INT16 awViewOffsetBuffer[4][16] = { 0 };						// 紀錄每個view 的offset buffer

    memmove(awViewOffsetBuffer[index] + 1, awViewOffsetBuffer[index], 15 * sizeof(INT16));
    awViewOffsetBuffer[index][0] = cOffset;
    for (i = 0; i < 16; i++)
    {
        SumTemp += awViewOffsetBuffer[index][i];
    }
    wAverageOut = SumTemp >> 4;

    return wAverageOut;
}

static void OffsetModify(UINT16 a_index, alSTATISTIC_StatistcalMean a_atSingleViewROIMean[COMMONK_NUM_BV_CHANNEL], INT8 a_acOffset[COMMONK_NUM_BV_CHANNEL])
{
    FLOAT64 ePercentage[2] = {0}; // 0: Low 1: High
    FLOAT64 ePercentageTmp[2] = {0};
    INT32 lMean[2];
    INT32 lGap;
#if  alGAE_AVM_LOG
    INT32 la, lb;
#endif

    lGap = 100 / (MEAN_PERCENTAGE_HIGH_TH - MEAN_PERCENTAGE_LOW_TH);
    ePercentage[0] = (FLOAT64)a_atSingleViewROIMean[a_index].ulLowMeanPixelCnt / (FLOAT64)(a_atSingleViewROIMean[a_index].ulLowMeanPixelCnt + a_atSingleViewROIMean[a_index].ulHighMeanPixelCnt);
    ePercentage[1] = (FLOAT64)a_atSingleViewROIMean[a_index].ulHighMeanPixelCnt / (FLOAT64)(a_atSingleViewROIMean[a_index].ulLowMeanPixelCnt + a_atSingleViewROIMean[a_index].ulHighMeanPixelCnt);
    ePercentage[0] *= 100;
    ePercentage[1]  *= 100;
    // lMean[0]  = (ePercentage[0] > MEAN_PERCENTAGE_LOW_TH) ? a_atSingleViewROIMean[a_index].ucLowMean : a_atSingleViewROIMean[a_index].ucHighMean;
    // lMean[1]  = (ePercentage[1] > MEAN_PERCENTAGE_LOW_TH) ? a_atSingleViewROIMean[a_index].ucHighMean : a_atSingleViewROIMean[a_index].ucLowMean;
    
    if(ePercentage[0] <= MEAN_PERCENTAGE_LOW_TH){
        lMean[0] = a_atSingleViewROIMean[a_index].ucHighMean;
    }else if(ePercentage[0] > MEAN_PERCENTAGE_HIGH_TH){
        lMean[0] = a_atSingleViewROIMean[a_index].ucLowMean;
    }else{
       /* ePercentageTmp[0] = (ePercentage[0]-MEAN_PERCENTAGE_LOW_TH) * lGap;
        ePercentageTmp[1] = 100 - ePercentageTmp[0];
        lMean[0] = (INT32) (ePercentageTmp[0]*a_atSingleViewROIMean[a_index].ucLowMean + ePercentageTmp[1]*a_atSingleViewROIMean[a_index].ucHighMean);
        lMean[0] /= 100;*/

        lMean[0] = (a_atSingleViewROIMean[a_index].ucLowMean + a_atSingleViewROIMean[a_index].ucHighMean) / 2;
    }

    if(ePercentage[1] <= MEAN_PERCENTAGE_LOW_TH){
        lMean[1] = a_atSingleViewROIMean[a_index].ucLowMean;
    }else if(ePercentage[1] > MEAN_PERCENTAGE_HIGH_TH){
        lMean[1] = a_atSingleViewROIMean[a_index].ucHighMean;
    }else{
        /*ePercentageTmp[0] = (ePercentage[1]-MEAN_PERCENTAGE_LOW_TH) * lGap;
        ePercentageTmp[1] = 100 - ePercentageTmp[0];
        lMean[1] = (INT32)( ePercentageTmp[0]*a_atSingleViewROIMean[a_index].ucHighMean + ePercentageTmp[1]*a_atSingleViewROIMean[a_index].ucLowMean);
        lMean[1] /= 100;*/

        lMean[1] = (a_atSingleViewROIMean[a_index].ucLowMean + a_atSingleViewROIMean[a_index].ucHighMean) / 2;
    }

#if  alGAE_AVM_LOG
    // for OSD display
    g_ulalGAE_AVM_MeanOSD_Debug[a_index * 2] = lMean[0];
    g_ulalGAE_AVM_MeanOSD_Debug[a_index * 2 + 1] = lMean[1];
    // for OSD display
    la = LOW_TH;
    lb = HIGH_TH;
#endif
    
    if(a_acOffset[a_index] < 0){
        a_acOffset[a_index] = (a_acOffset[a_index] + lMean[0] > LOW_TH) ? a_acOffset[a_index] : LOW_TH - (INT32)lMean[0];
    }else{
        a_acOffset[a_index] = (a_acOffset[a_index] + lMean[1] < HIGH_TH) ? a_acOffset[a_index] : HIGH_TH - (INT32)lMean[1];
    }
}


void alGAE_AVM_TargetViewOffsetEstimation(UINT8 a_ucIndex, alSTATISTIC_StatistcalMean a_atSingleViewROIMean[COMMONK_NUM_BV_CHANNEL], INT16 *a_pwOffset_TargetView)
{
    if (a_atSingleViewROIMean[a_ucIndex].ucGeneralMean < TargetOffsetLow_TH){
        *a_pwOffset_TargetView = TargetOffsetLow_TH - a_atSingleViewROIMean[a_ucIndex].ucGeneralMean;
    }
    else if (a_atSingleViewROIMean[a_ucIndex].ucGeneralMean > TargetOffsetHigh_TH)
    {
        *a_pwOffset_TargetView = TargetOffsetHigh_TH - a_atSingleViewROIMean[a_ucIndex].ucGeneralMean;
    }
}



void alGAE_AVM(UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer,
    alCARINFO_Set *a_tCarInputInfo, INT32 a_lNoise,
    alAVM2D_Cfg *a_ptAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2D_Params,
    alSTATISTIC_StatistcalMean a_atSingleViewROIMean[COMMONK_NUM_BV_CHANNEL],
    alGAE_AVM_Data *a_ptData
    )
{
    alPointINT32 alROIPosition[4], tAE_BlockSize;
    UINT8 aucObstacleFlagForTargetView[4];
    UINT16 *ppuwHistogram[NUM_ROI];
    INT16 wOffsetTmp = 0;
    INT16 *pwOffset_Ymean_nextFrame[4] = { 0 }; // the pointer of Offset need to add to LCD
    UINT32 aulMean[NUM_ROI], ulIndex, i;
    UINT32 ulDMAID1 = 0, ulDMAID2 = 0, ulZero = 0;
    INT32 alHistVariance[NUM_ROI], lHistMean = 0;
    INT32 alGap[4] = {0}, lViewIdx = 0;
    INT16 awOffset_Y_nextFrame[4] = { 0 };				// the Offset need to add to LCD
    INT8 acOffset_Y_WithLimit[4] = { 0 };			// the current Offset add to LCD
    INT16 awOffsetY_Average[4] = { 0 };			// the Offset after average filter
#if alGAE_AVM_LOG
    FILE *ptFile = NULL;
    char acName[MAX_PATH] = { 0 };
#endif
    
    
    
    tAE_BlockSize.lX = a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lX;
    tAE_BlockSize.lY = a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lY;
  
    alROIPosition[0].lX = a_ptalAVM2D_Params->tCarPicCornerPos.lX - tAE_BlockSize.lX + a_ptAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lX;
    alROIPosition[0].lY = a_ptalAVM2D_Params->tCarPicCornerPos.lY - tAE_BlockSize.lY + a_ptAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lY;

    alROIPosition[1].lX = a_ptalAVM2D_Params->tCarPicCornerPos.lX + a_ptalAVM2D_Params->tCarPicAreaSize.lX + a_ptAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lX;
    alROIPosition[1].lY = a_ptalAVM2D_Params->tCarPicCornerPos.lY - tAE_BlockSize.lY + a_ptAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lY;

    alROIPosition[2].lX = a_ptalAVM2D_Params->tCarPicCornerPos.lX - tAE_BlockSize.lX + a_ptAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lX;
    alROIPosition[2].lY = a_ptalAVM2D_Params->tCarPicCornerPos.lY + a_ptalAVM2D_Params->tCarPicAreaSize.lY + a_ptAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lY;

    alROIPosition[3].lX = a_ptalAVM2D_Params->tCarPicCornerPos.lX + a_ptalAVM2D_Params->tCarPicAreaSize.lX + a_ptAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lX;
    alROIPosition[3].lY = a_ptalAVM2D_Params->tCarPicCornerPos.lY + a_ptalAVM2D_Params->tCarPicAreaSize.lY + a_ptAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lY;
    
    memset(aulMean, 0, 8*sizeof(INT32));

    // 將 Global AE 所有 ROI 影像塞進 SRAM
#ifdef WIN32
    assert((tAE_BlockSize.lX<<1) < 65536);
    assert(tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1) < 65536);
    assert((a_ulWidth<<1) < 65536);
#endif
    ulDMAID1 = DAT_copy2d(
        DAT_2D1D, 
        a_pucBuffer + (a_ptalAVM2D_Params->tBirdViewAreaSize.lX<<1),
        g_L2_SRAM_ROI_DMA,
        (tAE_BlockSize.lX<<1),
        tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1),
        a_ulWidth<<1
   );

#if alGAE_AVM_LOG
    ptFile = fopen("GAE_ROI.raw", "wb");
    fwrite(g_L2_SRAM_ROI_DMA, 1, (tAE_BlockSize.lX << 1)*tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1), ptFile);
    fclose(ptFile);
#endif
    
    ulDMAID2 = DAT_fill(g_puwL2_SRAM_Hist_DMA, NUM_ROI * BIN_NUM * sizeof(UINT16), &ulZero);

#if alGAE_AVM_LOG
    ptFile = fopen("GAE_ROI_4.raw", "wb");
    fwrite(g_L2_SRAM_ROI_DMA, 1, (tAE_BlockSize.lX << 1)*tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1), ptFile);
    fclose(ptFile);
#endif

#ifndef WIN32
    #pragma MUST_ITERATE(1, NUM_ROI, 1)
#endif
    for(i = 0 ; i < NUM_ROI ; i ++) // NUM_ROI = 24, cus it count the YCbCr 3 channel for each of the 8 ROI
    {
        ppuwHistogram[i] = g_puwL2_SRAM_Hist_DSP + i * BIN_NUM;
    }

    DAT_wait(ulDMAID1);
    DAT_wait(ulDMAID2);


#if alGAE_AVM_LOG
    ptFile = fopen("GAE_ROI_3.raw", "wb");
    fwrite(g_L2_SRAM_ROI_DMA, 1, (tAE_BlockSize.lX << 1)*tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1), ptFile);
    fclose(ptFile);
#endif

    // analyzing ROI
#ifndef WIN32
    #pragma MUST_ITERATE(1, VIEW_TOTAL_CNT, 1)
#endif
    for (i = 0; i < VIEW_TOTAL_CNT; i++)
    {
        register INT32 lHistIndex = i * 6;
        register UINT8 ucPixelValue;
        register UINT32 ulIndexY1 = (((i<<1) * tAE_BlockSize.lY * tAE_BlockSize.lX)<<1);
        register UINT32 ulIndexY2 = ((((i<<1) + 1) * tAE_BlockSize.lY * tAE_BlockSize.lX)<<1);
        UINT32 ulPixelCount = tAE_BlockSize.lY * tAE_BlockSize.lX;

        assert((ulPixelCount & 0x03) == 0);

#ifndef WIN32
        #pragma MUST_ITERATE(1, , 4)
#endif

#if alGAE_AVM_LOG
        ptFile = fopen("GAE_ROI_1.raw", "wb");
        fwrite(g_L2_SRAM_ROI_DSP, 1, (tAE_BlockSize.lX << 1)*tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1), ptFile);
        fclose(ptFile);

        ptFile = fopen("GAE_ROI_2.raw", "wb");
        fwrite(g_L2_SRAM_ROI_DMA, 1, (tAE_BlockSize.lX << 1)*tAE_BlockSize.lY * (VIEW_TOTAL_CNT << 1), ptFile);
        fclose(ptFile);
#endif
        for(ulIndex = 0 ; ulIndex < ulPixelCount ; ulIndex ++, ulIndexY1+=2, ulIndexY2+=2)
        {

            // 第一個 View
            // 取出 Y 數值
            ucPixelValue = g_L2_SRAM_ROI_DSP[ulIndexY1];

            // 累計 Sum 值
            aulMean[i<<1] += (UINT32) ucPixelValue;
            // 累計 Histogram
            ppuwHistogram[lHistIndex][ucPixelValue>>BIN_GAP]++;

            // 第二個 View
            // 取出 Y, U/V 數值
            ucPixelValue = g_L2_SRAM_ROI_DSP[ulIndexY2];

            // 累計 Sum 值
            aulMean[(i<<1) + 1] += (UINT32) ucPixelValue;

            // 累計 Histogram
            ppuwHistogram[lHistIndex + 3][ucPixelValue>>BIN_GAP]++;

        }
    }

    // get Y mean value
#ifndef WIN32
    #pragma MUST_ITERATE(1, 8, 1)
#endif
    for(i = 0 ; i < 8 ; i ++)
    {
        aulMean[i] /=  tAE_BlockSize.lX * tAE_BlockSize.lY;
    }

    // Calculate 1D-Histogram mean
    lHistMean = tAE_BlockSize.lX*tAE_BlockSize.lY / BIN_NUM;

#ifndef WIN32
    #pragma MUST_ITERATE(1, , 1)
#endif
    for(i = 0 ; i < NUM_ROI ; i += 3)
    {
        alHistVariance[i] = CalVariance(ppuwHistogram[i], BIN_NUM, lHistMean);
    }

    // Calculate Cross-correlation
#ifndef WIN32
    #pragma MUST_ITERATE(1, , 1)
#endif
    for(i = 0 ; i < NUM_ROI ; i += 6)
    {
        a_ptData->afCorrelationResult[(i>>1)] = Cross_Correlation(ppuwHistogram[i], ppuwHistogram[i + 3], BIN_NUM, lHistMean, lHistMean, alHistVariance[i], alHistVariance[i + 3]);
    }
    
    // Calculate gap between views & index based on gear
    memset(aucObstacleFlagForTargetView, 0, 4);
    if (a_tCarInputInfo->ucGear == alCARINFO_GEAR_R)
    {   // Back
        alGap[0] = aulMean[5] - aulMean[4];
        alGap[1] = aulMean[7] - aulMean[6];
        alGap[2] = aulMean[0] - aulMean[1];
        alGap[3] = aulMean[2] - aulMean[3];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_LEFT];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_RIGHT];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_FRONT] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_BACK];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_BACK] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_FRONT];
    }
    else
    {   // Front
        alGap[0] = aulMean[1] - aulMean[0];
        alGap[1] = aulMean[3] - aulMean[2];
        alGap[2] = aulMean[4] - aulMean[5];
        alGap[3] = aulMean[6] - aulMean[7];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_LEFT];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_RIGHT];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_FRONT] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_FRONT];
        pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_BACK] = &awOffset_Y_nextFrame[alCAMERAINFO_BV_BACK];
    }
    
     // set mean new
    *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_FRONT] = (a_tCarInputInfo->ucGear == alCARINFO_GEAR_R) ? a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_BACK] : a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_FRONT];
    *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_FRONT] += a_ptData->wOffset_Ymean_TargetView;
    
    // left to target
    if(aucObstacleFlagForTargetView[0]){   
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] = (a_ptData->afCorrelationResult[0] >= TH_Non_Obstacle_Y) ? alGap[0] : a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_LEFT];
        aucObstacleFlagForTargetView[0] = (a_ptData->afCorrelationResult[0] >= TH_Non_Obstacle_Y) ? 0 : 1;
    }else{
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] = (a_ptData->afCorrelationResult[0] < TH_Obstacle_Y) ? a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_LEFT] : alGap[0];
        aucObstacleFlagForTargetView[0] = (a_ptData->afCorrelationResult[0] < TH_Obstacle_Y) ? 1 : 0;
    }
    *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] = (aucObstacleFlagForTargetView[0]) ? *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] : *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] + a_ptData->wOffset_Ymean_TargetView;

    // right to target
    if(aucObstacleFlagForTargetView[1]){   
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] = (a_ptData->afCorrelationResult[3] >= TH_Non_Obstacle_Y) ? alGap[1] : a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_RIGHT];
        aucObstacleFlagForTargetView[1] = (a_ptData->afCorrelationResult[3] >= TH_Non_Obstacle_Y) ? 0 : 1;
    }else{
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] = (a_ptData->afCorrelationResult[3] < TH_Obstacle_Y) ? a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_RIGHT] : alGap[1];
        aucObstacleFlagForTargetView[1] = (a_ptData->afCorrelationResult[3] < TH_Obstacle_Y) ? 1 : 0;
    }
    *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] = (aucObstacleFlagForTargetView[1]) ? *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] : *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT] + a_ptData->wOffset_Ymean_TargetView;

    // back to target
    if(aucObstacleFlagForTargetView[2] && aucObstacleFlagForTargetView[3]){
        aucObstacleFlagForTargetView[2] = (a_ptData->afCorrelationResult[6] >= TH_Non_Obstacle_Y) ? 0 : 1;
        aucObstacleFlagForTargetView[3] = (a_ptData->afCorrelationResult[9] >= TH_Non_Obstacle_Y) ? 0 : 1;
    }else if(aucObstacleFlagForTargetView[2]){
        aucObstacleFlagForTargetView[2] = (a_ptData->afCorrelationResult[6] >= TH_Non_Obstacle_Y) ? 0 : 1;
        aucObstacleFlagForTargetView[3] = (a_ptData->afCorrelationResult[9] < TH_Obstacle_Y) ? 1 : 0;
    }else if(aucObstacleFlagForTargetView[3]){
        aucObstacleFlagForTargetView[2] = (a_ptData->afCorrelationResult[6] < TH_Obstacle_Y) ? 1 : 0;
        aucObstacleFlagForTargetView[3] = (a_ptData->afCorrelationResult[9] >= TH_Non_Obstacle_Y) ? 0 : 1;
    }else{
        aucObstacleFlagForTargetView[2] = (a_ptData->afCorrelationResult[6] < TH_Obstacle_Y) ? 1 : 0;
        aucObstacleFlagForTargetView[3] = (a_ptData->afCorrelationResult[9] < TH_Obstacle_Y) ? 1 : 0;
    }

    if(aucObstacleFlagForTargetView[2] && aucObstacleFlagForTargetView[3]){
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_BACK] = a_ptData->acOffset_Ymean_Firmware[alCAMERAINFO_BV_BACK];
    }else if(aucObstacleFlagForTargetView[2]){
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_BACK] = alGap[3] + *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT];
    }else if(aucObstacleFlagForTargetView[3]){
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_BACK] = (alGap[2] + *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT]);
    }else{
        *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_BACK] = (alGap[2] + *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_LEFT] + alGap[3] + *pwOffset_Ymean_nextFrame[alCAMERAINFO_BV_RIGHT]) / 2;
    }

    // set obstacle flag
    if (a_tCarInputInfo->ucGear == alCARINFO_GEAR_R)
    {   // Back
        a_ptData->aucObstacle[0] = aucObstacleFlagForTargetView[2];
        a_ptData->aucObstacle[1] = aucObstacleFlagForTargetView[3];
        a_ptData->aucObstacle[2] = aucObstacleFlagForTargetView[0];
        a_ptData->aucObstacle[3] = aucObstacleFlagForTargetView[1];
    }
    else
    {   // Front
        a_ptData->aucObstacle[0] = aucObstacleFlagForTargetView[0];
        a_ptData->aucObstacle[1] = aucObstacleFlagForTargetView[1];
        a_ptData->aucObstacle[2] = aucObstacleFlagForTargetView[2];
        a_ptData->aucObstacle[3] = aucObstacleFlagForTargetView[3];
    }
    // set mean new
    a_ptData->lLimitView = Global_AE_MaxOffsetDecision(a_tCarInputInfo, a_lNoise);
    a_ptData->lLimitFrame = a_ptData->lLimitView / FRAME_GAP;

    // get final offset value
    for (lViewIdx = 0; lViewIdx < VIEW_TOTAL_CNT; lViewIdx++){
        // wOffsetTmp = awOffset_Y_nextFrame[lViewIdx] - a_ptData->acOffset_Ymean_Firmware[lViewIdx];
        wOffsetTmp = awOffset_Y_nextFrame[lViewIdx];
        if (abs(wOffsetTmp) > a_ptData->lLimitFrame)
		{
            if (wOffsetTmp > 0)
            {
                wOffsetTmp = a_ptData->lLimitFrame;
			}
            else
            {
                wOffsetTmp = -a_ptData->lLimitFrame;
			}
		}
        wOffsetTmp += a_ptData->acOffset_Ymean_Firmware[lViewIdx];

        if (abs(wOffsetTmp) > a_ptData->lLimitView){ // over max
            if (wOffsetTmp > 0)
            {
                acOffset_Y_WithLimit[lViewIdx] = a_ptData->lLimitView;
			}
            else
            {
                acOffset_Y_WithLimit[lViewIdx] = -a_ptData->lLimitView;
			}
        }else{
            acOffset_Y_WithLimit[lViewIdx] = (INT8)wOffsetTmp;
        }

#if  1 
        // 475 offset modify
        OffsetModify(lViewIdx, a_atSingleViewROIMean, acOffset_Y_WithLimit);
#endif

		// average
#if  0 // alGAE_AVM_LOG // no average
        awOffsetY_Average[lViewIdx] = acOffset_Y_WithLimit[lViewIdx];
        a_ptData->acOffset_Ymean_Firmware[lViewIdx] = acOffset_Y_WithLimit[lViewIdx];
#else
        awOffsetY_Average[lViewIdx] = OffsetAverageFlow(lViewIdx, acOffset_Y_WithLimit[lViewIdx]);
        a_ptData->acOffset_Ymean_Firmware[lViewIdx] = (INT8)awOffsetY_Average[lViewIdx];
#endif
		
    }

#if 1 // 複製算完的結果  這裡的數據  僅供觀察用  跟補償直沒直接關係
    memcpy(a_ptData->aulMean, aulMean, 8 * sizeof(UINT32));
    memcpy(a_ptData->alGap, alGap, 4 * sizeof(INT32));
#endif
}


void alGAE_AVM_Main(
    UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer,
    alCARINFO_Set *a_tCarInputInfo,
    alAVM2D_Cfg *a_ptAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2D_Params,
    alSTATISTIC_Data *a_ptalSTATISTIC_Data,
    alGAE_AVM_Data *a_ptData
    )
{
    INT32 lNoise = 0;

    
    if (a_tCarInputInfo->ucGear == alCARINFO_GEAR_R)
    {   // Back View
        alGAE_AVM_TargetViewOffsetEstimation(alCAMERAINFO_BV_BACK, a_ptalSTATISTIC_Data->atSingleViewROIMean, &a_ptData->wOffset_Ymean_TargetView);
    }
    else
    {   // Front View
        alGAE_AVM_TargetViewOffsetEstimation(alCAMERAINFO_BV_FRONT, a_ptalSTATISTIC_Data->atSingleViewROIMean, &a_ptData->wOffset_Ymean_TargetView);
    }

    if (a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lX*a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lY > MAX_ROI_AREA)
    { // ROI 區域超過設定 記憶體可能會不夠
        assert(0);
    }

    lNoise = a_ptalSTATISTIC_Data->ucGlobalNoiseLevel;

    alGAE_AVM(
        a_ulWidth, a_ulHeight, a_pucBuffer, a_tCarInputInfo, lNoise,
        a_ptAVM2D_Cfg, a_ptalAVM2D_Params,
        a_ptalSTATISTIC_Data->atSingleViewROIMean,
        a_ptData
    );
}
