#pragma once
#include "alStatistic_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif


/**
*  \defgroup alSTATISTIC
*  @{
*/


/** 
    \brief To calculate the statistical mean on specifiec area of the four single view. The area is defined in "SingleView_Statistic.c". The calculated data is recoreded in the global parameter in g_atStatistc_SingleViewROIMean.
    \param a_ppucSrcBuffer [IN] The buffer of four BV camera images.
    \param a_ulImageWidth [IN] The width of image buffer.
    \param a_ulImageHeight [IN] The height of image buffer.
    \return None.
*/
void alStatistic_MeanCal(UINT8 ** a_pucSrcBuffer, UINT32 a_ulImageWidth, UINT32 a_ulImageHeight, UINT8 a_ucYMeanTh);

/** 
    \brief To do the noise level estimation on specifiec area of the four single view. The area is defined in "SingleView_Statistic.c". The calculated data is recoreded in the global parameter in a_ptData.
    \param a_ppucSrcBuffer [IN] The buffer of four BV camera images.
    \param a_ulImageWidth [IN] The width of image buffer.
    \param a_ulImageHeight [IN] The height of image buffer.
    \return None.
*/
void alStatistic_NoiseLevelEstimation(alSTATISTIC_Cfg    *a_ptCfg, UINT8 ** a_pucSrcBuffer, UINT32 a_ulImageWidth, UINT32 a_ulImageHeight, alSTATISTIC_Data *a_ptData);
/**
*  @}
*/
#ifdef __cplusplus
}
#endif
