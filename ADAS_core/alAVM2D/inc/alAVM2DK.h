#pragma once

#include "mtype.h"
#include "CommonK.h"
#include "alAVM2DDef.h"
#include "alLUT_v2_Def.h"
#include "alFM_v2_1.h"
#include "alPartLUT_v2.h"


/**
  *  \addtogroup alAVM2D
  *  @{
  */

#ifdef __cplusplus
extern "C"
{
#endif

#define GAE_LUT_GEN 1

/** 
    \brief Initialize buffer needed by AVM3D calibration. This is to generate LUT for AVM3D display. 
    \param a_ptalAVM2DLUT [OUT] alAVM2D LUT Buffer in BV partition format
    \return 0: fail 1: success
*/
BOOL alAVM2D_InitializeBuffer(alLUT_v2_Def * a_ptalAVM2DLUT);

/** 
	\brief Generate a alAVM2D LUT for top view.
	\param a_ptAVMCfg [IN] alAVM2D configuration data.
	\param a_ptalAVM2DParams [IN] alAVM2D parameters.
	\param a_ptFisheyeModel [IN] Fisheye configuration data.
	\param a_aeM33_BV_RC_Left [IN] The calibrated M33 of front camera for alAVM2D. 
	\param a_aeM33_BV_RC_Right [IN] The calibrated M33 of front camera for alAVM2D. 
	\param a_aeM33_BV_RC_Front [IN] The calibrated M33 of front camera for alAVM2D. 
	\param a_aeM33_BV_RC_Back [IN] The calibrated M33 of front camera for alAVM2D. 
	\param a_ptalAVM2D_LUT [OUT] alAVM2D LUT.
*/
void alAVM2D_GenerateLUT2DBirdView(
                        alAVM2D_Cfg * a_ptAVMCfg,
                        alAVM2D_Params *a_ptalAVM2DParams,
                        alFM_v2_1_Model * a_ptFisheyeModel,
                        FLOAT64 a_aeM33_BV_RC_Left[2][9],
                        FLOAT64 a_aeM33_BV_RC_Right[2][9],
                        FLOAT64 a_aeM33_BV_RC_Front[2][9],
                        FLOAT64 a_aeM33_BV_RC_Back[2][9],
                        alLUT_v2_Def * a_ptalAVM2D_LUT
                        );

/** 
	\brief Generate a Global AE LUT on alAVM2D LUT for top view.
	\param pBirdViewCfg [IN] Bird view configuration data.
	\param a_ptalAVM2DParams [IN] alAVM2D parameters.
	\param aCameraFisheyeModel [IN] Fisheye configuration data.
	\param EAGLEK3_M33_Set [IN] The calibrated M33 of camera for alAVM2D. 
	\param a_ptalAVM2D_LUT [OUT] alAVM2D LUT.
*/
void GeneratealAVM2D_GAELUT(
                          alAVM2D_Cfg * a_ptalAVM2DCfg, 
                          alAVM2D_Params *a_ptalAVM2DParams,
                          alFM_v2_1_Model a_tCameraFisheyeModel[],
                          alLUT_v2_Def * a_ptalAVM2D_LUT,
                          FLOAT64 a_aeM33_BV_RC_Left[2][9],
                          FLOAT64 a_aeM33_BV_RC_Right[2][9],
                          FLOAT64 a_aeM33_BV_RC_Front[2][9],
                          FLOAT64 a_aeM33_BV_RC_Back[2][9]
                          );

/** 
    \brief Initialize the alAVM2D parameter.
*/
void alAVM2D_InitialByConfigData(alAVM2D_Cfg * a_ptalAVM2DCfg, alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Params *a_ptalAVM2DParams);

/** 
    \brief Free buffers which is allocated by alAVM2D_GenerateLUT2DBirdView().
    \param a_ptalAVM2D_LUT [IN] alAVM2D LUT Buffer
    \param a_ptalAVM2D_PartLUT [IN] alAVM2D Partition LUT Buffer in BV partition format
*/
void alAVM2D_FreeBuffer(alLUT_v2_Def * a_ptalAVM2D_LUT, alPartLUT_v2_Def ** a_ptalAVM2D_PartLUT);


/** 
    \brief Generate alAVM2D location weighting Table from birdview data.
    \param a_aucalAVM2DLocWeightingTable [OUT] pointer to the location weighting LUT
	 \param pCommonCfg [IN] Common cfg data from ECU.
    \param aCameraDesignParameters [IN] structure of camera configuration
    \param pBirdViewCfg [IN] structure of BirdView configuration
    \param pBirdViewParams [IN] BirdView calcilated parameters.
*/
void alAVM2D_GeneratealAVM2DLocWeightingTable(
    UINT8 *a_aucalAVM2DLocWeightingTable, alCOMMONK_CommonCfg * pCommonCfg, 
    alCAMERAINFO_ExtrinsicParams a_atCameraDesignParameters[], alAVM2D_Cfg *a_ptalAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2D_Params
    );


INT8 alAVM2D_BlindRegionDecide(
	INT32 a_lX,
	INT32 a_lY,
	alAVM2D_Params *a_ptalAVM2DParams
	);

void	alAVM2D_alAVM2DGeneratingByM33_GrayLevel(
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
	FLOAT64 *a_paeM33LeftW2I,
	FLOAT64 *a_paeM33RightW2I,
	FLOAT64 *a_paeM33FrontW2I,
	FLOAT64 *a_paeM33BackW2I,
	UINT8 *a_pucBirdViewBuffer,
    alAVM2D_Params *a_ptalAVM2D_Params,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg,
    alFM_v2_1_Model *a_ptFisheyeModel
);


/** 
\brief Qurry LUT data Size
\param a_ptAVMCfg [IN] alAVM2D configuration data.
\param a_ptalAVM2DParams [IN] alAVM2D parameters.
\return LUT data's size
*/
UINT32 alAVM2D_QurryLUTSize(
    alAVM2D_Cfg * a_ptAVMCfg,
    alAVM2D_Params *a_ptalAVM2DParams
    );

#ifdef __cplusplus
}
#endif

/**
  *  @}
  */
