
#pragma once

#include "mtype.h"
// #include "alMANUALK/alMANUALK_Def.h"
#include "CommonK.h"
#include "AVM3DDef.h"
#include "alFM_v2_1.h"
#include "AVM3DM33Generation.h"

/**
  *  \addtogroup AVM3D
  *  @{
  */

#ifdef __cplusplus
extern "C"
{
#endif

/** 
    \brief Initialize buffer needed by AVM3D calibration. This is to generate LUT for AVM3D display. 
    \param a_ptAVM3DLUT [OUT] AVM3D LUT Buffer in BV partition format
    \param a_ptAVM3D_PartLUT [IN] AVM3D Partition LUT Buffer in BV partition format
*/
BOOL AVM3D_InitializeBuffer(alLUT_v2_Def * a_ptAVM3DLUT, alPartLUT_v2_Def ** a_ptAVM3D_PartLUT);

/** 
    \brief Generate a AVM3D RT Matrix for specified view.
    \param a_lViewIndex [IN] View index of AVM3D, this is not used in the function, only for debug. Set to 99 to indicate Morpging operation.
    \param a_ptAVM3DParam [IN] NormalView parameter data.
    \param a_ptAVM3DCfg [IN] NormalView configuration data.
*/
void AVM3D_GenerateM33(INT32 a_lViewIndex,
                        alAVM3D_ParamsSingle *a_ptAVM3DParam,
                        alAVM3D_CfgSingleView * a_ptAVM3DCfg
                        );

/** 
    \brief Generate a AVM3D LUT for specified view.
    \param a_lViewIndex [IN] View index of AVM3D, this is not used in the function, only for debug. Set to 99 to indicate Morpging operation.
    \param a_ptAVMPara [IN] AVM3D Parameter data.
    \param a_ptAVMCfg [IN] AVM3D configuration data.
    \param a_ptFisheyeModel [IN] Fisheye model data of Bird view camera.
    \param a_ptCalibrationData [IN] RT matrix of Bird view camera.
    \param a_ptAVM_LUT [OUT] The LUT for AVM3D. 
*/
void AVM3D_GenerateLUT( INT32 a_lViewIndex,
                        alAVM3D_ParamsSingle *a_ptAVMPara,
                        alAVM3D_CfgSingleView * a_ptAVMCfg,
                        alFM_v2_1_Model *a_ptFisheyeModel,
                        alCOMMONK_CalibrationParams *a_ptCalibrationData,
                        alLUT_v2_Def *a_ptAVM_LUT
                        );

/** 
    \brief Free buffers which is allocated by NV_InitializeBuffer.
    \param a_ptAVM3DLUT [IN] AVM3D LUT Buffer in BV partition format
    \param a_ptAVM3D_PartLUT [IN] AVM3D Partition LUT Buffer in BV partition format
*/
void AVM3D_FreeBuffer(alLUT_v2_Def * a_ptAVM3DLUT, alPartLUT_v2_Def ** a_ptAVM3D_PartLUT);

/** 
    \brief Calculate the AVM3D virtual camera data for log.
    \param a_lVirtualViewNo [IN] View Number
    \param a_ptAVM3DParam [IN] AVM3D Parameter
    \param a_ptAVM3DCfg [IN] AVM3D Cfg
    \param a_ptFisheyeModel [IN] Virtual fish eye model
*/
void AVM3D_VIewAnalyzing(INT32 a_lVirtualViewNo,  
                         alAVM3D_ParamsSingle *a_ptAVM3DParam,
                         alAVM3D_CfgSingleView * a_ptAVM3DCfg,
                         alFM_v2_1_Model * a_ptFisheyeModel);

/** 
    \brief Export the virtual camera log data of AVM3D to cvs file. This is only for single specified virtual camera.
    \param a_pcWorkFolder [IN] Work folder for output
    \param a_lVirtualViewNo [IN] Indicate the index of the specified virtual camera.
    \param a_ptAVM3DParam [IN] Calculated AVM3D parameters for the specified virtual camera.
    \param a_ptAVM3DCfg [IN] The conifg data of the specified virtual camera.
*/
void AVM3D_LogFUNC(char *a_pcWorkFolder,
                   INT32 a_lVirtualViewNo,
                   alAVM3D_ParamsSingle * a_ptAVM3DParam,
                   alAVM3D_CfgSingleView * a_ptAVM3DCfg);



/** 
    \brief Transform coordinate from world(mm) to Dest Image(pixel) 
    \param a_lViewIndex [IN] AVM3D lViewIndex
    \param a_ptAVMPara [IN] AVM3D Parameter data.
    \param a_ptAVMCfg [IN] AVM3D configuration data.
    \param a_eSrcX [IN] World coordinate X (mm)
    \param a_eSrcY [IN] World coordinate Y (mm)
    \param a_eSrcZ [IN] World coordinate Z (mm)
    \param a_peDestX [IN] DestImage coordinate X (pixel)
    \param a_peDestY [IN] DestImage coordinate X (pixel)

*/
void AVM3D_World2DestImage(
	INT32 a_lViewIndex,
    alAVM3D_ParamsSingle *a_ptAVMPara,
    alAVM3D_Cfg *a_ptAVMCfg,
    FLOAT64 a_eSrcX,
    FLOAT64 a_eSrcY,
    FLOAT64 a_eSrcZ,
    FLOAT64 *a_peDestX,
    FLOAT64 *a_peDestY
);


/** 
    \brief generate Morphing by Src and Dest view parameter.
    \param a_ptAVM3D_tCfg [IN] The structure to store the main config data.
    \param a_ptSrcViewPara [IN] The structure to store the src view config data.
	\param a_ptDestViewPara [IN] The structure to store the dest view config data.
	\param a_lMorphingLUTFlag [IN] The Flag of Morphing LUT.
	\param a_lMorphingLUTNum [IN] The Number of Morphing LUT.
	\param a_lMorphingType [IN] The Type of Morphing LUT.
    \param a_ptMorphingInfo [IN] AVM3D Morphing LUT Index Sruct
    \param a_ptFisheyeModel [IN] Fisheye model data of Bird view camera.
    \param a_ptCalibrationData [IN] RT matrix of Bird view camera.
	\param a_ptMorphingLUT [OUT] The structure to store the Morphing LUT
	\return TRUE : ok  FALSE : fail
*/
UINT8 AVM3D_MorphingLUTGenerating(
    alAVM3D_Cfg *a_ptAVM3D_tCfg,
	alAVM3D_CfgSingleView *a_ptSrcViewPara, 
	alAVM3D_CfgSingleView *a_ptDestViewPara, 
	INT32 a_lMorphingLUTFlag,
	INT32 a_lMorphingLUTNum,
	INT32 a_lMorphingType,
    alAVM3D_MorphingStruct *a_ptMorphingInfo,
    alFM_v2_1_Model *a_ptFisheyeModel,
    alCOMMONK_CalibrationParams *ptCalibrationData,
	AVM3D_MorphingLUT *a_ptMorphingLUT
);

/** 
    \brief Get Morphing LUT Infomation (Flag and frame number)
    \param a_acSrcName [IN] The src view name.
	\param a_acDestName [IN] The dest view name.
	\param a_plMorphingFlag [OUT] The Morphing LUT Flag
	\param a_plFrameNum [OUT] The Morphing LUT number
*/
UINT8 AVM3D_GetMorphingLUTInfo(
	CHAR a_acSrcName[32],
	CHAR a_acDestName[32],
	INT32 *a_plMorphingFlag,
	INT32 *a_plFrameNum
);

/** 
    \brief generate Morphing image by LUT's flag and frame index.
    \param a_lMorphingFlag [IN] The LUT Flag.
	\param a_lFrameIndex [IN] The Frame Index.
	\param a_ucInverse [IN] The inverse flag 0:FORWARD 1:INVERSE
	\param a_plMorphingFlag [IN] The Src Image Buffer
	\param a_plFrameNum [OUT] The Dest Image Buffer
*/
UINT8 AVM3D_MorphingImageGenerating(
	INT32 a_lMorphingFlag,
	INT32 a_lFrameIndex,
	UINT8 a_ucInverse,
	UINT8 *a_pucSrcImageBuffer,
	UINT8 *a_pucDestImageBuffer
);

void AVM3D_RT_Verify(
    const FLOAT32 a_fBirdsViewMMPP,
    alCOMMONK_CalibrationParams *a_ptCalibrationData,
    alAVM3D_ParamsSingle *a_ptAVMPara,
    alAVM3D_CfgSingleView * a_ptAVMCfg,
    alFM_v2_1_Model * a_ptFisheyeModel,
    alLUT_v2_Def * a_ptAVM3D_LUT,
    UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage
    );

/**
\brief generate Morphing image by LUT's flag and frame index.
*/
void AVM3D_InitialByCfg(alAVM3D_Params *a_ptParams, alAVM3D_Cfg *a_ptCfg, alFM_v2_1_Model a_atFishEyeModel[AVM3D_MAX_VIEW_ANGLE_CNT]);

/**
\brief generate Morphing image by LUT's flag and frame index.
*/
void AVM3D_LogDataForAnalyzing(alFM_v2_1_Model a_atCameraFM[4], alAVM3D_Params *a_ptParams, alAVM3D_Cfg *a_ptCfg);

#ifdef __cplusplus
}
#endif

/**
  *  @}
  */
