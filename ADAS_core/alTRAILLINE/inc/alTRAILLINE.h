#pragma once
#include "mtype.h"
#include "alTRAILLINE_Def.h"
#include "CommonK.h"
#include "alFM_v2_1.h"
#include "alAVM2DDef.h" // 車幅線 需要2D 的某些結構

#ifdef __cplusplus
extern "C"
{
#endif

/**
  *  \addtogroup TrailLine
  *  @{
  */

/**
\brief return working buffer size
\return working buffer size
*/
UINT32 alTRAILLINE_QurryTrailLineWorkingBufferSize();

/**
\brief return line data buffer size
\return line data buffer size
*/
UINT32 alTRAILLINE_QurryTrailLineDataBufferSize();

/** 
\brief To initial buffer for tail line calculation and record. 
\param a_ptTRAILLINE_tLineDataSet [INOUT] trail line data
*/
BOOL alTRAILLINE_InitialBuffer(alTRAILLINE_LineSet *a_ptTRAILLINE_tLineDataSet);

/** 
\brief Initail trail line parameter data.
\param a_pucTLWorkingBuffer [IN] working buffer
\param a_ptData [IN]  run time data
\param a_ptAVM2D_Cfg [IN] alAVM2D configure
\param a_ptalAVM2DParams [IN] alAVM2D parameter
\param a_ptCommonCfg [IN] commom configure
\param a_ptCfg [IN] configure
\param a_ptParams [INOUT] parameter
\param a_ptLineData [INOUT] trail line data
*/
void alTRAILLINE_InitialByCfg(
    UINT8   *a_pucTLWorkingBuffer, alTRAILLINE_Data *a_ptData,
    alAVM2D_Cfg *a_ptAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2DParams, alCOMMONK_CommonCfg * a_ptCommonCfg, 
    alTRAILLINE_Cfg *a_ptCfg, alTRAILLINE_Params  *a_ptParams, alTRAILLINE_LineSet *a_ptLineData
);

/** 
\brief The main function to generate trail line.
\param a_ptData [IN] runtime data
\param a_atCalibrationParams [IN] calibration data (RT Matrix etc....)
\param a_ptFisheyeModel_v2 [IN] fish eye model
\param a_ptCfg [IN] trail line configure
\param a_ptParams [IN] trail line parameter
\param a_ptLineData [IN] trail line data
*/
void alTRAILLINE_GenerateLineData(
    alTRAILLINE_Data *a_ptData,
    alCOMMONK_CalibrationParams a_atCalibrationParams[4], alFM_v2_1_Model *a_ptFisheyeModel_v2, 
    alTRAILLINE_Cfg *a_ptCfg, alTRAILLINE_Params  *a_ptParams, alTRAILLINE_LineSet *a_ptLineData);

/** 
    \brief To get the buffer size required for the specified trail line type. 
    \param pucTraillineType [IN] The type of trail line
    \param pulSize [OUT] The required size for the trail line buffer.
*/
void alTRAILLINE_GetBufferSize(UINT8 pucTraillineType, UINT32 * pulSize, alTRAILLINE_LineSet *a_ptLineDataSet);

/* 
    \brief To get the trail line data for the specified trail line type. 
    \param pucTraillineType [IN] Indicate the specific type of trail line. See alTRAILLINE_TL_INDX.
    \param ulSize [IN] The length of the input buffer - pucTrailDataBuffer.
    \param pucTrailDataBuffer [OUT] The buffer address.
    \return Trail line data pointer, case to UIN8*. This return pointer is a internal array pointer and maybe changed after this function is called. And also this pointer cannot be free by other function.
    \see alTRAILLINE_GetBufferSize, alTRAILLINE_GenerateLineData, alTRAILLINE_TL_INDX
*/
void alTRAILLINE_GetLineData(UINT8 pucTraillineType, UINT32 ulSize, UINT8 * pucTrailDataBuffer, alTRAILLINE_LineSet *a_ptLineDataSet);

/** 
\brief Free all allocated trail line buffer. 
\param a_ptLineData [IN] trail line data
*/
void alTRAILLINE_FreeBuffer(alTRAILLINE_LineSet *a_ptLineData);

#ifdef WIN32

/*
    \brief To export the calculated trail line data to a txt file. This is used for trail line test of FW team.
    \param pLineData [IN] The data array to export the trail line data.
    \param lPairNum [IN] The pair count in the data array, pLineData.
    \param pwcFileName [IN] The filename to write the data.
    \param pcPrefix [IN] A prefix string to indiate which kind of trial line of the file.
    \return None.
*/
void alTRAILLINE_SaveLineDataToText(alTRAILLINE_PairData * pLineData, UINT32 lPairNum, wchar_t * pwcFileName, char * pcPrefix);

#endif
/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
