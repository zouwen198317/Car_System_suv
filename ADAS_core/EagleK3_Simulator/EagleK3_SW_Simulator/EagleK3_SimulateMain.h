
#pragma once

#include "mtype.h"
#include "EagleK3.h"
#include "alAVM2DK.h"
#include "alAlleyViewK.h"
#include "alTRAILLINE.h"
#include "alTILibDef.h"
#include "AVM3DK.h"
#include "alINI.h"


#define alEAGLEK3_SIMULATOR_OPENCV_TEST 1
#define MAGA_IMAGE 1

#if MAGA_IMAGE
#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 720
#else
#define IMAGE_WIDTH 720
#define IMAGE_HEIGHT 480
#endif

void Test_Memory2FileW(wchar_t * a_pwcFileName, UINT8 * a_pucBuf, INT32 a_lSize);

BOOL Test_ImportOtherHexFiles(const wchar_t * a_pwcHexFilePath, UINT8 ** a_ppucBuffer, UINT32 * a_plBufferLength);

void Test_ManualK(
    UINT8 *a_apucSrcImage[4],
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data
    );

void Test_AV_Generate(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    );

void Test_alAVM2D_Generate(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    );

void Test_alAVM3D_Generate(
    alAVM3D_Cfg *a_ptCfg,
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    );

void TEST_ExportUndistortedImage(
    wchar_t * a_pwcSrcImageFolder, 
    wchar_t * a_pwcOutImageFolder, 
    FLOAT32 a_fScale, 
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL]
);


void Test_SET_BV_FM(
    wchar_t a_awcConfigFilePath[MAX_PATH],
    alFM_v2_1_ModelCfg a_atFM_BV[EAGLEK3_NUM_BV_CHANNEL],
    UINT32 a_aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL],
    UINT8 *a_apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL],
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL]
    );

void Test_SET_BV_FM_Default(
    alFM_v2_1_ModelCfg a_atFM_BV[EAGLEK3_NUM_BV_CHANNEL],
    UINT32 a_aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL],
    UINT8 *a_apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL],
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL]
    );

void Test_BV_FM(wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder
    );

void Test_SBV_GeneratingAllView(
    wchar_t * a_pwcOutImageFolder,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data,
    UINT8 *a_apucSrcImage[4]
    );

void Test_SBV_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder
);

void Test_SET_EAGLEK3_PARAMS(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL],
    alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data,
    EAGLEK3_FieldData *a_ptEAGLEK3_FeildData,
    UINT32 *a_pulEagleK3BufferSize,
    UINT8 **a_pucEagleK3WorkingBuffer
    );

void Test_SET_EAGLEK3_PARAMS_Default(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    alFM_v2_1_Model a_atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL],
    alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Cfg *a_ptAVM2DCfg, alAVM2D_Params *a_ptAVM2DParams,
    EAGLEK3_Cfg *a_ptEAGLEK3_Cfg,
    EAGLEK3_Param *a_ptEAGLEK3_Params,
    EAGLEK3_Data *a_ptEAGLEK3_Data,
    EAGLEK3_FieldData *a_ptEAGLEK3_FeildData,
    UINT32 *a_pulEagleK3BufferSize,
    UINT8 *a_pucEagleK3WorkingBuffer
    );

void Test_ManualK_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
);

void Test_Only_BV_ManualK_By_Default();

void Test_BV_FACTORY_AUTOKK_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
);

void Test_BV_FACTORY_AUTOKK_By_Default(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_alAVM2D_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_AV_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_TrailLine_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_GAE_By_Load_LUT(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_LDC(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder
    );

void Test_test();

void Test_alAVM3D_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_HexFile_Tmp_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_HexFile_Export_TMP_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_HexFile_Export_CFG1_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_HexFile_Export_CFG2_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_HexFile_Export_CFG4_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    );

void Test_LineSegDetectTmp();

