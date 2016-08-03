#pragma once

#include "mtype.h"    
#include "CommonK.h"

/**
*  \addtogroup alCRSMRKDET
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif



#define alCRSMRKDET_ROI_W	80// 50
#define alCRSMRKDET_ROI_H	60 // 30 
#define alCRSMRKDET_MAX_MARK_SIZE	17 



/** \brief Define the alCRSMRKDET configure data struct . */
typedef struct
{
	/** \brief Difference Threshold*/
	FLOAT64 eDifferenceTH;

	/** \brief Variance Out Threshold*/
	FLOAT64 eVarianceOutTH;

	/** \brief Variance In Threshold*/
	FLOAT64 eVarianceInTH;

	/** \brief Variance Threshold*/
	FLOAT64 eVarianceTH;

	/** \brief Variance In for detail check Threshold*/
	FLOAT64 eVarianceInDetailTH;

} alCRSMRKDET_Cfg;

#if 0
	/** \brief Define the alCRSMRKDET Parameter data struct . */
	typedef struct
	{
		

	} alCRSMRKDET_Parameter;
#endif

extern	INT32 g_lCAMID_AutoKDebug;
extern	INT32 g_lROIID_AutoKDebug;

#ifdef __cplusplus
}
#endif

/**
*  @}
*/
