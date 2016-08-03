
#pragma once

#include "BVCAM_FACAUTOK/CRSMRKDET_Def.h"

#define alCRSMRKDET_DEBUG 1



/**
*  \addtogroup alCRSMRKDET
*  @{
*/


#ifdef __cplusplus
extern "C"
{
#endif



/**
\brief MarkSearching(2423).
\param a_ptCfg [IN] Cfg in Detect ROI
\param a_tROI [IN] Detect ROI
\param a_pucSrcBuf [IN] src Buffer
\param a_lWidth [IN] width
\param a_lHeight [IN] height
\param a_In_X [IN] Input_X
\param a_In_Y [IN] Input_Y
\param a_plOut_X [OUT] Output_X
\param a_plOut_Y [OUT] Output_Y
\return 0: fail  1:success
*/
BOOL alCRSMRKDET_CrossMarkDetect(
	alCRSMRKDET_Cfg *a_ptCfg,
	alRectINT32 a_tROI, UINT8 *a_pucSrcBuf, INT32 a_lWidth, INT32 a_lHeight,
	INT32 a_In_X, INT32 a_In_Y, INT32* a_plOut_X, INT32* a_plOut_Y
);


#ifdef __cplusplus
}
#endif

/**
*  @}
*/
