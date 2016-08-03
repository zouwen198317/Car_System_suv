#pragma once
#include "alStatistic_SingleView.h"
#include "mtype.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \defgroup alSTATISTIC
*  @{
*/

/** \brief Do mean estimation on BV image for each view. Each view has 3 ROIs for mean estimation. */
void alStatistic_MeanEstimateForTopView_3ROIsPerView(UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer, alSTATISTIC_Data *a_ptalSTATISTIC_Data);

/** \brief Do mean estimation on BV image for each view. Each view has 10 ROIs for mean estimation. */
void alStatistic_MeanEstimateForTopView_10ROIsPerView(
    alSTATISTIC_Cfg    *a_ptCfg, UINT32 a_ulWidth, UINT32 a_ulHeight, UINT8 *a_pucBuffer, alSTATISTIC_Data *a_ptalSTATISTIC_Data);


/**
*  @}
*/

#ifdef __cplusplus
}
#endif
