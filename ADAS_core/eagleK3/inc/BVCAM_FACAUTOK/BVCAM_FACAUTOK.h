#pragma once

#include "BVCAM_FACAUTOK_Def.h"
#include "BVCAM_FACAUTOK/CrossMarkK.h"
#include "BVCAM_FACAUTOK/RectK.h"
#include "alAVM2DDef.h" // for parameter about stitch line
#include "alFM_v2_1.h"

#define alBVCAM_FACAUTOK_DEBUG 0

#define alBVCAM_FACAUTOK_DEBUG_FW 1

#if alBVCAM_FACAUTOK_DEBUG > 0
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_DeBug.h"
#endif

/**
*  \addtogroup alBVCAM_FACAUTOK
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif


/**
\brief Extract Y Channel from source image YUV422 (2100).
\param a_lWidth [IN] source image Width
\param a_lHeight [IN] source image Height
\param a_pucSrcBuffer [IN] source Buffer
\param a_pucYBuffer [OUT] image Buffer of Y Channel
*/
void	GetYChannel(
    INT32 a_lWidth,
    INT32 a_lHeight,
    UINT8 *a_pucSrcBuffer,
    UINT8 *a_pucYBuffer
    );

/**
\brief Auto Calibration for transform matrix and qulity analyzing and FineTune  (2000).
\param a_pucSrcBufferFront [IN] source Buffer of Front camera
\param a_pucSrcBufferBack [IN] source Buffer of Back camera
\param a_pucSrcBufferLeft [IN] source Buffer of Left camera
\param a_pucSrcBufferRight [IN] source Buffer of Right camera
\param a_aeOriginalM33Left [IN] left current transform matrix
\param a_aeOriginalM33Right [IN] right current transform matrix
\param a_aeOriginalM33Front [IN] front current transform matrix
\param a_aeOriginalM33Back [IN] back current transform matrix
\param a_ptCfg [IN] AutoK's configure
\param a_ptParams [IN] AutoK's parameter
\param a_ptData [OUT] AutoK's Result data
\return AutoKSuccessFlag [OUT] 0: faill 1: pass
*/
UINT32	alBVCAM_FACAUTOK_AutoK(
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
	FLOAT64 a_aeOriginalM33Left[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeOriginalM33Right[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeOriginalM33Front[2][COMMONK_M33_ELEMENT_CNT],
	FLOAT64 a_aeOriginalM33Back[2][COMMONK_M33_ELEMENT_CNT],
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams,
    BVCAM_FACAUTOK_Data *a_ptData
);

/**
\brief Initial buffer function for Factory Calibration (1100)
*/
void alBVCAM_FACAUTOK_InitialBuffer();

/**
\brief Free buffer function for Factory Calibration (7000)
*/
void alBVCAM_FACAUTOK_FreeBuffer();

/**
\brief Initial function for Factory Calibration by CFG (1400)
\param a_ptalAVM2D_Params [IN] alAVM2D Params data for stitch line data and MMPP value
*/
void alBVCAM_FACAUTOK_InitialByCFG(
    alPointINT32 *a_ptBVImgSize,
    UINT8 *a_pucWorkingBuffer,
    BVCAM_FACAUTOK_Data *a_ptData,
    alFM_v2_1_Model *a_ptFisheyeModel,
	alAVM2D_Params *a_ptalAVM2D_Params,
	alPointINT32 a_tLeftTireCenter,
	INT32 *a_plCameraPosX, INT32 *a_plCameraPosY, INT32 *a_plOriImgYLimit,
    BVCAM_FACAUTOK_CalibrationFeildData *a_ptFeildData,
    FLOAT32    a_fMMPP,
    alCOMMONK_CommonCfg *a_ptCommonCfg,
    BVCAM_FACAUTOK_CFG *a_ptCfg,
    BVCAM_FACAUTOK_Parameter *a_ptParams
);

#if alBVCAM_FACAUTOK_DEBUG
void alBVCAM_GetalAVM2DInfo(
    alAVM2D_Params *a_ptalAVM2D_Params,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg
    );
#endif

#ifdef __cplusplus
}
#endif

/**
*  @}
*/
