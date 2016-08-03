
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mtype.h"
#include "alGAE_AVM_Def.h"
#include "alCarInfo.h"
#include "alCameraInfo.h"
#include "alAVM2DDef.h"
#include "alStatistic_SingleView.h"

/**
*  \addtogroup alGAE_AVM
*  @{
*/

/**
\brief alGAE_AVM_InitData : initail Global AE data at system begin
\param a_ptData [INOUT] global AE Data
*/
void alGAE_AVM_InitData(alGAE_AVM_Data *a_ptData);


/**
\brief alGAE_AVM_Main : Global AE main function
\param a_ulWidth [IN] image width
\param a_ulHeight [IN] image hight
\param a_tCarInputInfo [IN] car information (gear, speed and light etc...)
\param a_lNoise [IN] noise value
\param a_ptalAVM2D_Cfg [IN] alAVM2D configure
\param a_ptalAVM2D_Params [IN] alAVM2D paramter
\param a_atSingleViewROIMean [IN] ROI Mean from single view
\param a_ptData [OUT] global AE Data
*/
void alGAE_AVM_Main(
    UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer,
    alCARINFO_Set *a_tCarInputInfo,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2D_Params,
    alSTATISTIC_Data *a_ptalSTATISTIC_Data,
    alGAE_AVM_Data *a_ptData
    );

/**
\brief alGAE_AVM_TargetViewOffsetEstimation : Eastimate global AE offset for target view
\param a_ucIndex [IN] Camera index
\param a_atSingleViewROIMean [IN] ROI Mean from single view
\param a_pwOffset_TargetView [INOUT] offset for target view
*/
void alGAE_AVM_TargetViewOffsetEstimation(UINT8 a_ucIndex, alSTATISTIC_StatistcalMean a_atSingleViewROIMean[COMMONK_NUM_BV_CHANNEL], INT16 *a_pwOffset_TargetView);

/**
\brief alGAE_AVM : Eastimate global AE offset for each view
\param a_ulWidth [IN] image width
\param a_ulHeight [IN] image hight
\param a_tCarInputInfo [IN] car information (gear, speed and light etc...)
\param a_lNoise [IN] noise value
\param a_ptalAVM2D_Cfg [IN] alAVM2D configure
\param a_ptalAVM2D_Params [IN] alAVM2D paramter
\param a_atSingleViewROIMean [IN] ROI Mean from single view
\param a_ptData [OUT] global AE Data
*/
void alGAE_AVM(
    UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer, 
    alCARINFO_Set *a_tCarInputInfo, INT32 a_lNoise,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2D_Params,
    alSTATISTIC_StatistcalMean a_atSingleViewROIMean[COMMONK_NUM_BV_CHANNEL],
    alGAE_AVM_Data *a_ptData
);

/**
*  @}
*/

#ifdef __cplusplus
}
#endif


