
#include "mtype.h"
#include "alFM_v2_1.h"
#include "alAlleyViewM33Generator.h"
#include "alPartLUT_v1.h"
#include "alAlleyViewDef.h"
#include "alCameraInfo.h"
#include "CommonK.h"

/**
*  \defgroup alALLEYVIEW    alAlleyView
*  @{
*/

#define alALLEYVIEWDebug 0

#define SIM_DEFAULT_EAGLE_GP_TRANS  0   // 0: for Eagle II BirdView 座標轉換, 1: for Eagle-GP BirdView 座標轉換

#ifdef __cplusplus
extern "C" {
#endif 



/**
   \brief Initial LUT data buffer (p_tLutSet->lut_data) for the specified LUT set.
   \param p_tLutSet [IN] The LUT set to be initialized. This should be already a valid pointer. 
          The "p_tLutSet" will be intialized to 0 and only the buffer of "p_tLutSet->lut_data" need to be allocated.
   \param ulDisplayWidth [IN] The destination display width for Alley View.
   \param ulDisplayHeight [IN] The destination display height for Alley View.
   \return Returen "FALSE" if the memory allocation is failed.
*/
BOOL alALLEYVIEW_InitializeLUT(alPartLUT_v1_LUTSet_t * p_tLutSet, UINT32 ulDisplayWidth, UINT32 ulDisplayHeight);

/**
\brief Qurry LUT data Size
\return LUT data's size
*/
UINT32 alALLEYVIEW_QurryLUTSize();

/**
   \brief Initialize alley view parameters
   \param a_ptalAlleyViewCfg [IN] alley view transforamtion setting
   \param a_ptCameraCfg [IN] camera setting angles
   \param a_ptFisheyeModel [IN] fisheye model
   \param a_ptParams [OUT] The Params 0: Left 1: Right
   \return None
   \see alFM_v2_1_Model, CAMK_CameraCfg, alALLEYVIEW_Cfg
*/
void alALLEYVIEW_InitialByCfg( 
    alALLEYVIEW_Cfg * a_ptalAlleyViewCfg, 
    alCAMERAINFO_ExtrinsicParams *a_ptCamExtrinsicParams,
    alCOMMONK_CalibrationParams *a_ptCamCalibrationParams,
    alFM_v2_1_Model * a_ptFisheyeModel_v2,
    alAlleyViewParams *a_ptParams
 );

/**
   \brief Generate Alley View LUT in BV format
   \param a_pucAV_WorkingBuffer [IN] alley view working buffer
   \param a_ptalAlleyViewCfg [IN] alley view transforamtion setting
   \param a_ptParams [IN] camera setting angles
   \param a_ptAV_LUTset [OUT] Alley View LUT in BV partition format
   \param a_aeAVL [IN] The calibrated M33 for left side alAlleyView.
   \param a_aeAVR [IN] The calibrated M33 for right side alAlleyView.
   \param a_pucMask [IN] display mask
   \see alPartLUT_v1_LUTSet_t, GenAVLUT_XY2YUV, alPartLUT_v1_DoPartition
*/
void alALLEYVIEW_GenerateLUT(
    UINT8  *a_pucAV_WorkingBuffer,
    alALLEYVIEW_Cfg * a_ptalAlleyViewCfg,
    alAlleyViewParams *a_ptParams,
    INT32 a_lDisplayWidth, 
    UINT8 *a_pucMask,
    alPartLUT_v1_LUTSet_t * a_ptAV_LUTset
 );

/**
   \brief Revise alley view fine tune configure
   \param a_ptalAlleyViewCfg [IN] alley view transforamtion setting
   \param a_ptAV_Fine_Tune_Params [IN] alley view fine tune configure
   \see alALLEYVIEW_FineTuneParams
   \return None
*/
void alALLEYVIEW_FineTune(alALLEYVIEW_Cfg * a_ptalAlleyViewCfg, alALLEYVIEW_FineTuneParams * a_ptAV_Fine_Tune_Params, alAlleyViewParams *a_ptParams);

/**
   \brief Free the LUT data buffer.
   \param p_tLutSet [IN] The LUT set to be processed. Only the buffer "p_tLutSet->lut_data" will be freed.
   \return None
*/
void alALLEYVIEW_FreeLUT(alPartLUT_v1_LUTSet_t * p_tLutSet);



/**
\brief Generate an alley view display mask
\param a_ptCfg [IN] Configure
\param a_pucMask [OUT] Output the mask.
*/
void alALLEYVIEW_GenMask(alALLEYVIEW_Cfg * a_ptCfg, UINT8 * a_pucMask);

/**
\brief Generate an alley view display mask
\param a_ptCfg [IN] Configure
\return Mask Aize
*/
INT32 alALLEYVIEW_GetMaskSize(alALLEYVIEW_Cfg * a_ptCfg);

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif 
