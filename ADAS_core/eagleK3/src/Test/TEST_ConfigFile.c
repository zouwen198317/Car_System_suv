
#include "EagleK3.h"

#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC

#include <assert.h>
#include <sys/stat.h>
#include <locale.h>

#include "Core/EAGLEK3_Def.h"
#include "Camera/CameraDef.h"
#include "TableLU/PartitionLUT.h"
#include "AlleyView/AlleyViewDef.h"
#include "FrontSideView/FrontSideViewDef.h"
#include "FisheyeModel/FisheyeModel_v1.h"
#include "FisheyeModel/FisheyeModel_v2.h"
#include "TrailLine/TraillineDef.h"
#include "MOD/MODDef.h"
#include "NormalView/NormalViewDef.h"
#include "TopView/TopViewDef.h"
#include "AVM2D/AVM2DDef.h"
#include "AVM3D/AVM3DDef.h"
#include "Statistic/Statistic_Def.h"
#include "DataOperation/FileOperation.h"
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_Def.h" // add by ancre for autoK

void TEST_ConfigFileFactoryAutoK()
{
	char acWorkingFolder[MAX_PATH];
	char acConfigFile[MAX_PATH];
	struct stat st;
	UINT8 * pucDataBuffer = NULL;
	UINT8 ucCameraIndex = 0;
	BVCAM_FACAUTOK_CFG				tBVCAM_FACAUTOK_Cfg;
    INT32 i = 0;

	setlocale(LC_ALL, "cht");
	wcstombs(acWorkingFolder, g_EAGLEK3_awcWorkingPath, MAX_PATH);
	setlocale(LC_ALL, "C");

	printf("\n Do Data Import test: Factory AutoK Config File ....");

	memcpy(&tBVCAM_FACAUTOK_Cfg, &g_tBVCAM_FACAUTOK_Cfg, sizeof(BVCAM_FACAUTOK_CFG));
	

	memset(&g_tBVCAM_FACAUTOK_Cfg, 0, sizeof(BVCAM_FACAUTOK_CFG));

	strcpy(acConfigFile, acWorkingFolder);
	strcat(acConfigFile, "EagleK_FactoryAutoK_ConfigFile.hex");

	stat(acConfigFile, &st);

	pucDataBuffer = (UINT8*)malloc(st.st_size);

	//std::ifstream ifile(acConfigFile, std::ios::binary);
	//ifile.read((char*)pucDataBuffer, st.st_size);
	//ifile.close();
	EAGLEK3_File2Memory(acConfigFile, pucDataBuffer, st.st_size);

	// 3. Add data to eagleK library
	EAGLEK3_SetCfgInfoByFile(st.st_size, pucDataBuffer);
    
    if (g_tBVCAM_FACAUTOK_Cfg.lCammeraNum != 0)
    { // 不等於玲才需要檢查
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[0], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[0], sizeof(alRECK_Cfg)) == 0);
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[1], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[1], sizeof(alRECK_Cfg)) == 0);
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[2], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[2], sizeof(alRECK_Cfg)) == 0);
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[3], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[3], sizeof(alRECK_Cfg)) == 0);

        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0], sizeof(alCROSSMARKK_Cfg)) == 0);
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1], sizeof(alCROSSMARKK_Cfg)) == 0);
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2], sizeof(alCROSSMARKK_Cfg)) == 0);
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3], sizeof(alCROSSMARKK_Cfg)) == 0);

        assert(memcmp(&tBVCAM_FACAUTOK_Cfg, &g_tBVCAM_FACAUTOK_Cfg, sizeof(BVCAM_FACAUTOK_CFG)) == 0);

    }

	free(pucDataBuffer);

	////
#if 0 // 測試預設值是否跟 ini / Cfg檔一樣
	alBVCAM_FACAUTOK_LoadDefault();
	{
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[0], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[0], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[1], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[1], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[2], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[2], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[3], &g_tBVCAM_FACAUTOK_Cfg.atRecKCfg[3], sizeof(alRECK_Cfg)) == 0);

        for (i = 0; i < 8;i++)
        {
            assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0].atCrossMarkDetCfg[i], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0].atCrossMarkDetCfg[i], sizeof(alCRSMRKDET_Cfg)) == 0);
        }

        for (i = 0; i < 8; i++)
        {
            assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0].atROICfg[i].tROISize, &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0].atROICfg[i].tROISize, sizeof(alPointINT32)) == 0);
            assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0].atROICfg[i], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0].atROICfg[i], sizeof(alCROSSMARKK_ROICfg)) == 0);
        }

		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0], sizeof(alCROSSMARKK_Cfg)) == 0);
		
        for (i = 0; i < 8; i++)
        {
            assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1].atCrossMarkDetCfg[i], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1].atCrossMarkDetCfg[i], sizeof(alCRSMRKDET_Cfg)) == 0);
        }
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1], sizeof(alCROSSMARKK_Cfg)) == 0);
		
        for (i = 0; i < 8; i++)
        {
            assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2].atCrossMarkDetCfg[i], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2].atCrossMarkDetCfg[i], sizeof(alCRSMRKDET_Cfg)) == 0);
        }
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2], sizeof(alCROSSMARKK_Cfg)) == 0);
		
        for (i = 0; i < 8; i++)
        {
            assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3].atCrossMarkDetCfg[i], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3].atCrossMarkDetCfg[i], sizeof(alCRSMRKDET_Cfg)) == 0);
        }
        assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3], &g_tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3], sizeof(alCROSSMARKK_Cfg)) == 0);
	}
	assert(memcmp(&tBVCAM_FACAUTOK_Cfg, &g_tBVCAM_FACAUTOK_Cfg, sizeof(BVCAM_FACAUTOK_CFG)) == 0);
#endif
	////

	printf("OK \n");

}

void TEST_ConfigFile1()
{
    char acWorkingFolder[MAX_PATH];
    char acConfigFile[MAX_PATH];
    struct stat st;
    UINT8 * pucDataBuffer = NULL;

    UINT8 ucCameraIndex = 0;

	AVM3D_MorphingCfgStruct			tPreMorphingCfg;
    EAGLEK3_CommonCfg               tPreCommonCfg;
    AVM2D_Cfg                       tPreAVM2DCfg;
    AVM3D_Cfg                       tPreAVM3DCfg;
    NORMALVIEW_Cfg                  atPreNormalViewCfg[EAGLEK3_CAMERA_NUM];
    TOPVIEW_Cfg                     tPreTopViewCfg[TOPVIEW_NUM_CHANNEL];
    ALLEYVIEW_Cfg                   tPreSAVCfg;
    ALLEYVIEW_Cfg                   tPreFAVCfg;
    CAMK_CameraCfg                  atPreCameraDesignParameters[EAGLEK3_CAMERA_NUM];
    CAMK_SPPvsBVPPParam             atPreSPPvsBVPParam[EAGLEK3_CAMERA_NUM];
    MOD_SMODCfg                     tPreSMODCfg;
    TRAILLINE_Cfg                   tPreTraillineCfg;
    FSV_Cfg                         tPreFrontSideViewCfg[2];
    STATISTIC_Cfg                   tPreStatisticCfg;

    setlocale(LC_ALL, "cht");
    wcstombs(acWorkingFolder, g_EAGLEK3_awcWorkingPath, MAX_PATH);
    setlocale(LC_ALL, "C");

    printf("\n Do Data Import test: Config File #1....");

	memcpy(&tPreMorphingCfg, &g_tMorphingCfg, sizeof(AVM3D_MorphingCfgStruct));
    memcpy(&tPreCommonCfg, &g_EAGLEK3_tCommonCfg, sizeof(EAGLEK3_CommonCfg));
    memcpy(&tPreAVM2DCfg, &g_AVM2D_tCfg, sizeof(AVM2D_Cfg));
    memcpy(&tPreAVM3DCfg, &g_AVM3D_tCfg, sizeof(AVM3D_Cfg));
    memcpy(&atPreNormalViewCfg, &g_NORMALVIEW_atCfg, sizeof(NORMALVIEW_Cfg) * EAGLEK3_CAMERA_NUM);
    memcpy(&tPreTopViewCfg, &g_TOPVIEW_atCfg, sizeof(TOPVIEW_Cfg) * TOPVIEW_NUM_CHANNEL);
    memcpy(&tPreSAVCfg, &g_ALLEYVIEW_tSAVCfg, sizeof(ALLEYVIEW_Cfg));
    memcpy(&tPreFAVCfg, &g_ALLEYVIEW_tFAVCfg, sizeof(ALLEYVIEW_Cfg));
    memcpy(&atPreCameraDesignParameters, &g_CAMK_atCameraDefaultParam, sizeof(CAMK_CameraCfg) * EAGLEK3_CAMERA_NUM);
    memcpy(&atPreSPPvsBVPParam, &g_CAMK_atSPPvsBVPParam, sizeof(CAMK_SPPvsBVPPParam) * EAGLEK3_CAMERA_NUM);
    memcpy(&tPreSMODCfg, &g_MOD_tSMODCfg, sizeof(MOD_SMODCfg));
    memcpy(&tPreTraillineCfg, &g_TRAILLINE_tCfg, sizeof(TRAILLINE_Cfg));
    memcpy(&tPreFrontSideViewCfg, &g_FSV_atCfg, sizeof(FSV_Cfg) * 2);
    memcpy(&tPreStatisticCfg, &g_STATISTIC_tCfg, sizeof(STATISTIC_Cfg));

	memset(&g_tBVCAM_FACAUTOK_Cfg, 0, sizeof(BVCAM_FACAUTOK_CFG));
	memset(&g_tMorphingCfg, 0, sizeof(AVM3D_MorphingCfgStruct));
    memset(&g_EAGLEK3_tCommonCfg, 0, sizeof(EAGLEK3_CommonCfg));
    memset(&g_AVM2D_tCfg, 0, sizeof(AVM2D_Cfg));
    memset(&g_AVM2D_tParams, 0, sizeof(AVM2D_Params));
    memset(&g_AVM3D_tCfg, 0, sizeof(AVM3D_Cfg));
    memset(&g_AVM3D_atParams, 0, sizeof(g_AVM3D_atParams));
    memset(&g_NORMALVIEW_atCfg, 0, sizeof(NORMALVIEW_Cfg) * EAGLEK3_CAMERA_NUM);
    memset(&g_ALLEYVIEW_tSAVCfg, 0, sizeof(ALLEYVIEW_Cfg));
    memset(&g_ALLEYVIEW_tFAVCfg, 0, sizeof(ALLEYVIEW_Cfg));
    memset(&g_CAMK_atCameraDefaultParam, 0, sizeof(CAMK_CameraCfg) * EAGLEK3_CAMERA_NUM);
    memset(&g_CAMK_atSPPvsBVPParam, 0, sizeof(CAMK_SPPvsBVPPParam) * EAGLEK3_CAMERA_NUM);
    memset(&g_MOD_tSMODCfg, 0, sizeof(MOD_SMODCfg));
    memset(&g_TRAILLINE_tCfg, 0, sizeof(TRAILLINE_Cfg));
    memset(&g_FSV_atCfg, 0, sizeof(FSV_Cfg) * 2);
    memset(&g_STATISTIC_tCfg, 0, sizeof(STATISTIC_Cfg));

    strcpy(acConfigFile, acWorkingFolder);
    strcat(acConfigFile, "EagleK_ConfigFile1.hex");

    stat(acConfigFile, &st);

    pucDataBuffer = (UINT8*) malloc(st.st_size);

    //std::ifstream ifile(acConfigFile, std::ios::binary);
    //ifile.read((char*)pucDataBuffer, st.st_size);
    //ifile.close();
    EAGLEK3_File2Memory(acConfigFile, pucDataBuffer, st.st_size);

    // 3. Add data to eagleK library
	EAGLEK3_SetCfgInfoByFile(st.st_size, pucDataBuffer);

	assert(memcmp(&tPreMorphingCfg, &g_tMorphingCfg, sizeof(AVM3D_MorphingCfgStruct)) == 0);
    assert(memcmp(&tPreCommonCfg, &g_EAGLEK3_tCommonCfg, sizeof(EAGLEK3_CommonCfg)) == 0);
    assert(memcmp(&tPreAVM2DCfg, &g_AVM2D_tCfg, sizeof(AVM2D_Cfg)) == 0);

    if (g_AVM3D_tCfg.lViewCnt != 0)
    { // 不等於玲才需要檢查
        assert(memcmp(&tPreAVM3DCfg, &g_AVM3D_tCfg, sizeof(AVM3D_Cfg)) == 0);
    }
    

    for(ucCameraIndex = 0; ucCameraIndex < EAGLEK3_CAMERA_NUM; ucCameraIndex++)
    {
        assert(memcmp(atPreNormalViewCfg + ucCameraIndex, g_NORMALVIEW_atCfg + ucCameraIndex, sizeof(NORMALVIEW_Cfg)) == 0);
        assert(memcmp(atPreCameraDesignParameters + ucCameraIndex, g_CAMK_atCameraDefaultParam + ucCameraIndex, sizeof(CAMK_CameraCfg)) == 0);
        assert(memcmp(atPreSPPvsBVPParam + ucCameraIndex, g_CAMK_atSPPvsBVPParam + ucCameraIndex, sizeof(CAMK_SPPvsBVPPParam)) == 0);
    }

    assert(memcmp(&tPreTopViewCfg, &g_TOPVIEW_atCfg, sizeof(TOPVIEW_Cfg) * TOPVIEW_NUM_CHANNEL) == 0);
    assert(memcmp(&tPreSAVCfg, &g_ALLEYVIEW_tSAVCfg, sizeof(ALLEYVIEW_Cfg)) == 0);
    assert(memcmp(&tPreFAVCfg, &g_ALLEYVIEW_tFAVCfg, sizeof(ALLEYVIEW_Cfg)) == 0);
    assert(memcmp(&tPreSMODCfg, &g_MOD_tSMODCfg, sizeof(MOD_SMODCfg)) == 0);

    assert(memcmp(tPreTraillineCfg.atSTLCfg, g_TRAILLINE_tCfg.atSTLCfg, sizeof(TRAILLINE_StaticTrailLineInfo) * 2) == 0);
    assert(memcmp(tPreTraillineCfg.atDTLCfg, g_TRAILLINE_tCfg.atDTLCfg, sizeof(TRAILLINE_DynamicTrailLineInfo) * 2) == 0);
    assert(memcmp(tPreTraillineCfg.atWLCfg, g_TRAILLINE_tCfg.atWLCfg, sizeof(TRAILLINE_WarningLineInfo) * 4) == 0);

    assert(memcmp(&tPreTraillineCfg, &g_TRAILLINE_tCfg, sizeof(TRAILLINE_Cfg)) == 0);
    assert(memcmp(&tPreFrontSideViewCfg, &g_FSV_atCfg, sizeof(FSV_Cfg) * 2) == 0);
    assert(memcmp(&(tPreStatisticCfg.atBirdViewMeanCalInfo), &(g_STATISTIC_tCfg.atBirdViewMeanCalInfo), sizeof(STATISTIC_BirdViewMeanCalInfo)) == 0);
    assert(memcmp(&(tPreStatisticCfg.atSingleViewNoiseCalInfo), &(g_STATISTIC_tCfg.atSingleViewNoiseCalInfo), sizeof(STATISTIC_SingleViewNoiseCalInfo)) == 0);

    free(pucDataBuffer);

    printf("OK \n");

}

void TEST_ConfigFile2()
{
    char acWorkingFolder[MAX_PATH];
    char acConfigFile[MAX_PATH];
    UINT8 * pucDataBuffer = NULL;
    struct stat st;

    setlocale(LC_ALL, "cht");
    wcstombs(acWorkingFolder, g_EAGLEK3_awcWorkingPath, MAX_PATH);
    setlocale(LC_ALL, "C");

    printf("\n Do Data Import test: Config File #2....");

    // 1. Open file

    strcpy(acConfigFile, acWorkingFolder);
    strcat(acConfigFile, "EagleK_ConfigFile2.hex");

    stat(acConfigFile, &st);

    pucDataBuffer = (UINT8*) malloc(st.st_size);

    //std::ifstream ifile(acConfigFile, std::ios::binary);
    //ifile.read((char*)pucDataBuffer, st.st_size);
    //ifile.close();
    EAGLEK3_File2Memory(acConfigFile, pucDataBuffer, st.st_size);

    // 3. Add data to eagleK library
    EAGLEK3_SetCfgInfoByFile(st.st_size, pucDataBuffer);


    free(pucDataBuffer);

    printf("OK \n");
}

void TEST_ConfigFile3()
{
    char acWorkingFolder[MAX_PATH];
    char acConfigFile[MAX_PATH];
    UINT8 * pucDataBuffer = NULL;
    UINT8 ucCameraIndex = 0;
    struct stat st;
	INT32 i = 0;

    // Config File #3
    CAMK_CameraCfg              tCameraInstalledParameters[EAGLEK3_CAMERA_NUM];
#if (EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC)
    CAMK_ChartCrossPointSet     tChartCrossPointSet;
    // alPointINT32               atBVFPOffset[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM];
	alPointINT32               atBVFPOffset[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM_AUTOK];
	// CAMK_FeaturePointPos        atCaemraFeaturePoints[EAGLEK3_CAMERA_FP_NUM_AUTOK];
	CAMK_FeaturePointPos        atCaemraFeaturePoints[7];
#endif
    EAGLEK3_M33_Set             atPreCameraCurrentM33;
    FLOAT64                     aeZeroM33[2][9] = { 0.0 };

    ALLEYVIEW_RMtxSet           tSAV_RMtxSet;//g_ALLEYVIEW_tSAV_RMtxSet;
    ALLEYVIEW_RMtxSet           tFAV_RMtxSet;

    AVM2D_Params                tPreAVM2DParams;
    AVM3D_Params                atPreAVM3DParams[AVM3D_MAX_VIEW_ANGLE_CNT];


    setlocale(LC_ALL, "cht");
    wcstombs(acWorkingFolder, g_EAGLEK3_awcWorkingPath, MAX_PATH);
    setlocale(LC_ALL, "C");

    printf("\n Do Data Import test: Config File #3....");

    memcpy(&tCameraInstalledParameters, &g_CAMK_atCameraCurrentParam, sizeof(tCameraInstalledParameters));
    memcpy(&tPreAVM2DParams, &g_AVM2D_tParams, sizeof(AVM2D_Params));
    memcpy(&atPreAVM3DParams, &g_AVM3D_atParams, sizeof(g_AVM3D_atParams));

#if (EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC)
    memcpy(&tChartCrossPointSet, &g_CAMK_tChartCorssPointSet, sizeof(CAMK_ChartCrossPointSet));
    memcpy(&atBVFPOffset, &g_CAMK_atBVFPOffset, sizeof(g_CAMK_atBVFPOffset));
    memcpy(&atCaemraFeaturePoints, &g_CAMK_atCameraFeaturePoints, sizeof(g_CAMK_atCameraFeaturePoints));
#endif

    memcpy(&atPreCameraCurrentM33, &g_CAMK_tCameraCurrentM33Set, sizeof(EAGLEK3_M33_Set));

    memcpy(&tSAV_RMtxSet, &g_ALLEYVIEW_tSAV_RMtxSet, sizeof(g_ALLEYVIEW_tSAV_RMtxSet));
    memcpy(&tFAV_RMtxSet, &g_ALLEYVIEW_tFAV_RMtxSet, sizeof(g_ALLEYVIEW_tFAV_RMtxSet));

    for(ucCameraIndex = 0; ucCameraIndex < EAGLEK3_CAMERA_NUM; ucCameraIndex++)
    {
        g_CAMK_atCameraCurrentParam[ucCameraIndex].fPitchAngle = 0.0;
        g_CAMK_atCameraCurrentParam[ucCameraIndex].fYawAngle = 0.0;
        g_CAMK_atCameraCurrentParam[ucCameraIndex].fRollAngle = 0.0;
    }

    memset(&tPreAVM2DParams, 0, sizeof(g_AVM2D_tParams));
    memset(&atPreAVM3DParams, 0, sizeof(g_AVM3D_atParams));

#if (EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC)
    memset(&g_CAMK_tChartCorssPointSet, 0, sizeof(CAMK_ChartCrossPointSet));
    memset(&g_CAMK_atBVFPOffset, 0, sizeof(g_CAMK_atBVFPOffset));
    memset(&g_CAMK_atCameraFeaturePoints, 0, sizeof(g_CAMK_atCameraFeaturePoints));
#endif

    assert(memcmp(&tPreAVM2DParams, &g_AVM2D_tParams, sizeof(g_AVM2D_tParams)) == 0);
    assert(memcmp(&atPreAVM3DParams, &g_AVM3D_atParams, sizeof(g_AVM3D_atParams)) == 0);

    // memset(&g_CAMK_atCameraCurrentParam, 0, sizeof(g_CAMK_atCameraCurrentParam));
    memset(&g_CAMK_tCameraCurrentM33Set, 0, sizeof(EAGLEK3_M33_Set));
    memset(&g_ALLEYVIEW_tSAV_RMtxSet, 0, sizeof(g_ALLEYVIEW_tSAV_RMtxSet));
    memset(&g_ALLEYVIEW_tFAV_RMtxSet, 0, sizeof(g_ALLEYVIEW_tFAV_RMtxSet));


    // 1. Open file

    strcpy(acConfigFile, acWorkingFolder);
    strcat(acConfigFile, "EagleK_ConfigFile3.hex");

    stat(acConfigFile, &st);

    pucDataBuffer = (UINT8*) malloc(st.st_size);

    //std::ifstream ifile(acConfigFile, std::ios::binary);
    //ifile.read((char*)pucDataBuffer, st.st_size);
    //ifile.close();
    EAGLEK3_File2Memory(acConfigFile, pucDataBuffer, st.st_size);

    // 3. Add data to eagleK library
	EAGLEK3_SetCfgInfoByFile(st.st_size, pucDataBuffer);   

#if (EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC)
    assert(memcmp(&tChartCrossPointSet, &g_CAMK_tChartCorssPointSet, sizeof(CAMK_ChartCrossPointSet)) == 0);
    assert(memcmp(&atBVFPOffset, &g_CAMK_atBVFPOffset, sizeof(g_CAMK_atBVFPOffset)) == 0);
    assert(memcmp(&atCaemraFeaturePoints, &g_CAMK_atCameraFeaturePoints, sizeof(g_CAMK_atCameraFeaturePoints)) == 0);
#endif

	for (ucCameraIndex = 0; ucCameraIndex < EAGLEK3_CAMERA_NUM; ucCameraIndex++)
	{
		assert(memcmp(&(tCameraInstalledParameters[ucCameraIndex]), &(g_CAMK_atCameraCurrentParam[ucCameraIndex]), sizeof(CAMK_CameraCfg)) == 0);
	}
	assert(memcmp(&tCameraInstalledParameters, &g_CAMK_atCameraCurrentParam, sizeof(tCameraInstalledParameters)) == 0);

    assert(memcmp(atPreCameraCurrentM33.aeBVL, g_CAMK_tCameraCurrentM33Set.aeBVL, sizeof(g_CAMK_tCameraCurrentM33Set.aeBVL)) == 0);
    assert(memcmp(atPreCameraCurrentM33.aeBVR, g_CAMK_tCameraCurrentM33Set.aeBVR, sizeof(g_CAMK_tCameraCurrentM33Set.aeBVR)) == 0);
    assert(memcmp(atPreCameraCurrentM33.aeBVF, g_CAMK_tCameraCurrentM33Set.aeBVF, sizeof(g_CAMK_tCameraCurrentM33Set.aeBVF)) == 0);
    assert(memcmp(atPreCameraCurrentM33.aeBVB, g_CAMK_tCameraCurrentM33Set.aeBVB, sizeof(g_CAMK_tCameraCurrentM33Set.aeBVB)) == 0);
    assert(memcmp(atPreCameraCurrentM33.aeSVL, g_CAMK_tCameraCurrentM33Set.aeSVL, sizeof(g_CAMK_tCameraCurrentM33Set.aeSVL)) == 0);
    assert(memcmp(atPreCameraCurrentM33.aeSVR, g_CAMK_tCameraCurrentM33Set.aeSVR, sizeof(g_CAMK_tCameraCurrentM33Set.aeSVR)) == 0);
    assert(memcmp(atPreCameraCurrentM33.aeLVDSF, g_CAMK_tCameraCurrentM33Set.aeLVDSF, sizeof(g_CAMK_tCameraCurrentM33Set.aeLVDSF)) == 0);

    assert(memcmp(tSAV_RMtxSet.aeAVL, g_ALLEYVIEW_tSAV_RMtxSet.aeAVL, sizeof(g_ALLEYVIEW_tSAV_RMtxSet.aeAVL)) == 0);
    assert(memcmp(tSAV_RMtxSet.aeAVR, g_ALLEYVIEW_tSAV_RMtxSet.aeAVR, sizeof(g_ALLEYVIEW_tSAV_RMtxSet.aeAVR)) == 0);
    assert(memcmp(tFAV_RMtxSet.aeAVL, g_ALLEYVIEW_tFAV_RMtxSet.aeAVL, sizeof(g_ALLEYVIEW_tFAV_RMtxSet.aeAVL)) == 0);
    assert(memcmp(tFAV_RMtxSet.aeAVR, g_ALLEYVIEW_tFAV_RMtxSet.aeAVR, sizeof(g_ALLEYVIEW_tFAV_RMtxSet.aeAVR)) == 0);

    free(pucDataBuffer);

    printf("OK \n");
  
}

void TEST_ParamsFileFactoryAutoK()
{
	char acWorkingFolder[MAX_PATH];
	char acConfigFile[MAX_PATH];
	UINT8 * pucDataBuffer = NULL;
	UINT8 ucCameraIndex = 0;
	struct stat st;
	INT32 i = 0;
	BVCAM_FACAUTOK_Parameter tBVCAM_FACAUTOK_Parameter;

	setlocale(LC_ALL, "cht");
	wcstombs(acWorkingFolder, g_EAGLEK3_awcWorkingPath, MAX_PATH);
	setlocale(LC_ALL, "C");

	printf("\n Do Data Import test: Params File for AutoK....");

	memcpy(&tBVCAM_FACAUTOK_Parameter, &g_tBVCAM_FACAUTOK_Parameter, sizeof(BVCAM_FACAUTOK_Parameter));
	memset(&g_tBVCAM_FACAUTOK_Parameter, 0, sizeof(BVCAM_FACAUTOK_Parameter));

	// 1. Open file
	strcpy(acConfigFile, acWorkingFolder);
	strcat(acConfigFile, "EagleK_FactoryAutoK_ParameterFile.hex");

	stat(acConfigFile, &st);

	pucDataBuffer = (UINT8*)malloc(st.st_size);

	//std::ifstream ifile(acConfigFile, std::ios::binary);
	//ifile.read((char*)pucDataBuffer, st.st_size);
	//ifile.close();
	EAGLEK3_File2Memory(acConfigFile, pucDataBuffer, st.st_size);

	// 3. Add data to eagleK library
	EAGLEK3_SetCfgInfoByFile(st.st_size, pucDataBuffer);

	{
		assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atFineTuneFP, &g_tBVCAM_FACAUTOK_Parameter.atFineTuneFP, sizeof(g_tBVCAM_FACAUTOK_Parameter.atFineTuneFP)) == 0);

		assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atStitchLine, &g_tBVCAM_FACAUTOK_Parameter.atStitchLine, sizeof(g_tBVCAM_FACAUTOK_Parameter.atStitchLine)) == 0);


		for (i = 0; i < 4; i++)
		{
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].eMMPP, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].eMMPP, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].eMMPP)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lAngleCAM, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lAngleCAM, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lAngleCAM)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lCamPosX, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lCamPosX, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lCamPosX)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lCamPosY, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lCamPosY, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lCamPosY)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lOriImgYLimit, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lOriImgYLimit, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].lOriImgYLimit)) == 0);

			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].atIdealPointRectK, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].atIdealPointRectK, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].atIdealPointRectK)) == 0);

			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].atRecKROI, &g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].atRecKROI, sizeof(g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[i].atRecKROI)) == 0);
		}

		for (i = 0; i < 4; i++)
		{
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].eMMPP, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].eMMPP, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].eMMPP)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lAngleCAM, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lAngleCAM, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lAngleCAM)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lCamPosX, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lCamPosX, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lCamPosX)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lCamPosY, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lCamPosY, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lCamPosY)) == 0);
			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lOriImgYLimit, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lOriImgYLimit, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].lOriImgYLimit)) == 0);

			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].atCrossMarkROI, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].atCrossMarkROI, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].atCrossMarkROI)) == 0);

			assert(memcmp(&tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].atIdealPointCrossMark, &g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].atIdealPointCrossMark, sizeof(g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[i].atIdealPointCrossMark)) == 0);
		}
	}
	assert(memcmp(&tBVCAM_FACAUTOK_Parameter, &g_tBVCAM_FACAUTOK_Parameter, sizeof(BVCAM_FACAUTOK_Parameter)) == 0);

	free(pucDataBuffer);

	printf("OK \n");

}

void TEST_ConfigFile_FMv2()
{

}

#endif // #if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC
