
#pragma once

#include "alMatrix.h"
#include "EagleK3_Def.h"
#include "alMANUALK.h"
#include "alMANUALK_CalRefData.h"
#include "alMANUALK_Def.h"
#include "alCameraInfo.h"
#include "mtype.h"
#include "basedef.h"
#include "alAVM2DDef.h"
// #include "alAVM2DK.h"
#include "alFM_v2_1_Def.h"
#include "BVCAM_FACAUTOK.h"
#include "alErrorCode.h"



/**
  *  \defgroup EAGLEK3
 
  *  @{
  */

#ifdef __cplusplus
extern "C"
{
#endif

// ¡¿ ****************************** Initialization ****************************** ¡¿ //

/** \brief To initialize buffer of EagleK library. This function should only be called once. */
BOOL EAGLEK3_InitialBuffer();

/** \brief To initialize params of EagleK Bird-View Fish-Eye Model */
void EAGLEK3_InitialBV_FM_ByCfg(alFM_v2_1_ModelCfg a_atFM_v2_Cfg[COMMONK_NUM_BV_CHANNEL], alFM_v2_1_Model a_atFM_v2_Model[COMMONK_NUM_BV_CHANNEL], UINT8 *a_apucFMBuffer[COMMONK_NUM_BV_CHANNEL]);

/** \brief To free buffer of EagleK library. This function should only be called if the app ends. */
void EAGLEK3_FreeBuffer(alFM_v2_1_Model *a_ptCameraFisheyeModel);

#ifdef WIN32
/** 
    \brief Set the working path. This path is used to load calibration field file and also to save output files.
    \param pucWorkingPath [IN] Input the working path.
    \return None.
*/
void EAGLEK3_SetWorkingPath(wchar_t * a_pwcWorkingPath); 	

void EAGLEK3_SetPath(wchar_t * a_pwcWorkingPath, wchar_t * a_pwcSrcPath, wchar_t * a_pwcOutPath);
										
/** 
    \brief Get the working path.
    \param pucWorkingPath [IN] Input the working path.
    \return None.
*/
const wchar_t * EAGLEK3_GetWorkingPath(); 											
#endif //#ifdef WIN32



/**
    \brief Set calibration parameters by configuration data, call this function after the configuration data was set. 
    \return None.
*/
void EAGLEK3_InitialByConfigData(
    alFM_v2_1_Model * a_ptFM_v2_Model, alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_FieldData *a_ptFeildData, EAGLEK3_Cfg *a_ptCfg, EAGLEK3_Param *a_ptParams, 
    EAGLEK3_Data *a_ptCalibrateData, UINT8 *a_pucWorkingBuffer
);

// ¡¶ ****************************** Initialization ****************************** ¡¶ //

// ¡¿ ****************************** Error Handling ****************************** ¡¿ //

/** 
    \brief To indicate the error code for BV LUT generation. 
    \return The error code. 0: Successful.
    \see alERROR_ERROR_CODE, EAGLEK3_ReadErrorDescription
*/
alERROR_ERROR_CODE EAGLEK3_ReadErrorCode();

/** 
    \brief To read the description of current error code for BV LUT generation. 
    \see EAGLEK3_ReadErrorCode
*/
void EAGLEK3_ReadErrorDescription(wchar_t * a_pwcDescription, UINT8 a_ucBufferLen);

// ¡¶ ****************************** Error Handling ****************************** ¡¶ //

// ¡¿ ****************************** Import Config Files (Hex) ****************************** ¡¿ //

/**
    \brief Set Config Information (by data id) to EagleK by Data ID
    \param a_ulDataID [IN] ID of the current data.
    \param ulDataLength [IN] Length of the current data.
    \param pulDataBuffer [IN] Data buffer array.
    \param a_ptCfg [INOUT] configure Data.
*/
void EAGLEK3_SetCfgInfoByDataID(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 *a_puCDataBuffer, EAGLEK3_Cfg *a_ptCfg);

/**
    \brief Set Config Information (by file) to EagleK by Data ID. This is used to import a whole file. (like a Config File #1)
    \param ulFileaLength [IN] Length of the data buufer (in byte).
    \param pucFileBuffer [IN] Data buffer array.
    \param a_ptCfg [INOUT] configure Data.
*/
void EAGLEK3_SetCfgInfoByHexFile(UINT32 a_ulFileLength, UINT8 * a_pucFileBuffer, EAGLEK3_Cfg *a_ptCfg);

// ¡¶ ****************************** Import Config Files (Hex) ****************************** ¡¶ //


/**
    \brief Save All Config & Output Data to temp hex files.
    \return None.
*/
void  EAGLEK3_SaveAll();

/**
\brief Query FM_BV_Working Buffer Size
\param a_ucCamNum [IN] The camera number
\param a_ptFMCfg [INOut] The Cfg data
\return None.
*/
UINT32  EAGLEK3_QueryFM_BV_WorkingBufferSizeTotal(UINT8 a_ucCamNum, alFM_v2_1_ModelCfg *a_ptFMCfg);

/**
\brief Query FM_BV_Working Buffer Size
\param a_ptFMCfg [INOut] The Cfg data
\return single FM size.
*/
UINT32  EAGLEK3_QueryFM_BV_WorkingBufferSizeSingle(alFM_v2_1_ModelCfg *a_ptFMCfg);

/**
\brief Query FM_BV_Working Buffer Size for each camera
\param a_ptFMCfg [INOut] The Cfg data
\param a_aulSize [INOut] The FM size.
\return None.
*/
void  EAGLEK3_QueryFM_BV_WorkingBufferSizeForEachFM(alFM_v2_1_ModelCfg *a_ptFMCfg, UINT32 a_aulSize[COMMONK_NUM_BV_CHANNEL]);

/**
\brief Query EagleK3_Working Buffer Size
\param a_ptEagleK3Cfg [INOut] The Cfg data
\return None.
*/
UINT32  EAGLEK3_QueryEagleK3_WorkingBufferSizeSingle(EAGLEK3_Cfg *a_ptEagleK3Cfg);



/** 
    \brief To get required parameters for PC Tool or FW. 
    \param a_ptParams [OUT] Fill and store the required parameters.
*/
void EAGLEK3_GetParams(EAGLEK3_Param * a_ptParams);





void EAGLEK3_SingleViewForManualCalibration(
    UINT8 a_ucBVCameraIndx,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData,
    UINT8 * a_pucSrcImage,
    UINT8 * a_pucDestImage
);

void EAGLEK3_SrcDistorted2SBV_ForManualK(
    UINT8 a_ucBVCameraIndx,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData,
    FLOAT64 a_peSrcX, FLOAT64 a_peSrcY,
    FLOAT64 *a_peSBVX, FLOAT64 *a_peSBVY
    );

void EAGLEK3_ReGenerateM33_ForManualK(
    UINT8 a_ucBVCameraIndx,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData,
    FLOAT64 *a_peSelectSBVX, FLOAT64 *a_peSelectSBVY
    );

/** \brief Do the test for FatoryAutoK. */
UINT32 EAGLEK3_FatoryAutoK(
    UINT8 *a_pucSrcBufferFront,
    UINT8 *a_pucSrcBufferBack,
    UINT8 *a_pucSrcBufferLeft,
    UINT8 *a_pucSrcBufferRight,
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData
);


/** \brief FineTune M33 by FP offset from fine-tune Cfg */
void EAGLEK3_FineTuneHomographyMatrix(
    EAGLEK3_Cfg *a_ptCfg,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData
    );

/** \brief Generate RT Matrix for BV camera */
UINT32 EAGLEK3_Gen_RT_Matrix(
    EAGLEK3_Cfg *a_ptCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_Param *a_ptParams,
    EAGLEK3_Data *a_ptData
    );

// ¡¿ ****************************** Saving Hex Files ****************************** ¡¿ //

/**
\brief Save all config data to hex files, including Config File #1, #2, #3, Fisheye Model v2.
\return None.
*/
void  EAGLEK3_SaveConfigFiles();

// ¡¶ ****************************** Saving Hex Files ****************************** ¡¶ //


// ¡¿ ****************************** Test Functions ****************************** ¡¿ //

/** \brief Do the test for config file #1, #2, #3, FMv2. The config files should be exported 1st. If any error is found, the assert error will be triggered. */
void EAGLEK3_TestConfigFiles();

// ¡¶ ****************************** Test Functions ****************************** ¡¶ //

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
