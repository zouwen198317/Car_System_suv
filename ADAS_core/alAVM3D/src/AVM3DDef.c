
#include "AVM3DDef.h"
#include <stdio.h>
#ifdef WIN32 // FW 裡不允許讀INI檔
#include <locale.h> // add by ancre for char to wchar_t
#include "alINI.h"
#endif

#ifndef MAX_PATH
#define MAX_PATH          260
#endif


void AVM3D_OverlapLoadCfgLoadDefault(alAVM3D_OverlapLoadCfg * a_ptOverlapCfg)
{
	INT32 j = 0;

	for(j = 0 ; j < 4 ; j ++)
	{
		a_ptOverlapCfg->afBezierWeight[j][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_BEZIERWEIGHT;
		a_ptOverlapCfg->afBezierWeight[j][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_BEZIERWEIGHT;
		a_ptOverlapCfg->afCurveALineAngleOffset[j] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_ANGLEOFFSET;
		a_ptOverlapCfg->afCurveBLineAngleOffset[j] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_ANGLEOFFSET;

	}
	a_ptOverlapCfg->alDistanceCurveA[0][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTLEFT;
	a_ptOverlapCfg->alDistanceCurveA[0][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTLEFT;
	a_ptOverlapCfg->alDistanceCurveA[1][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTRIGHT;
	a_ptOverlapCfg->alDistanceCurveA[1][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTRIGHT;
	a_ptOverlapCfg->alDistanceCurveA[2][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKLEFT;
	a_ptOverlapCfg->alDistanceCurveA[2][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKLEFT;
	a_ptOverlapCfg->alDistanceCurveA[3][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKRIGHT;
	a_ptOverlapCfg->alDistanceCurveA[3][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKRIGHT;

	a_ptOverlapCfg->alDistanceCurveB[0][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTLEFT;
	a_ptOverlapCfg->alDistanceCurveB[0][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTLEFT;
	a_ptOverlapCfg->alDistanceCurveB[1][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTRIGHT;
	a_ptOverlapCfg->alDistanceCurveB[1][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTRIGHT;
	a_ptOverlapCfg->alDistanceCurveB[2][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKLEFT;
	a_ptOverlapCfg->alDistanceCurveB[2][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKLEFT;
	a_ptOverlapCfg->alDistanceCurveB[3][0] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKRIGHT;
	a_ptOverlapCfg->alDistanceCurveB[3][1] = SIM_DEFAULT_AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKRIGHT;

}

void AVM3D_LoadDefault(alAVM3D_Cfg *a_ptAVM3D_tCfg, alAVM3D_MorphingCfgStruct *a_ptMorphingCfg)
{
	// 全設為0  避免錯誤
    memset(a_ptAVM3D_tCfg, 0, sizeof(alAVM3D_Cfg));

    a_ptAVM3D_tCfg->lViewCnt = AVM3D_VIEW_CNT;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_s[0][0] = SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_BUMPER_1;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_s[0][1] = SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_SIDE_1;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_s[1][0] = SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_BUMPER_2;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_s[1][1] = SIM_DEFAULT_AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_SIDE_2;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_f[0][0] = SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_BUMPER_1;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_f[0][1] = SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_SIDE_1;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_f[1][0] = SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_BUMPER_2;
    a_ptAVM3D_tCfg->alWarningLineOfAVM3DBack_f[1][1] = SIM_DEFAULT_AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_SIDE_2;

    // load View 1 (a_ptAVM3D_tCfg->atViewCfg[0])
    sprintf(a_ptAVM3D_tCfg->atViewCfg[0].acName, AVM3D_NAME_1);
    a_ptAVM3D_tCfg->atViewCfg[0].tDestImageBufferSize.lX = AVM3D_DestImageBufferSizeX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].tDestImageBufferSize.lY = AVM3D_DestImageBufferSizeY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].tDestStartPoint.lX = AVM3D_DestStartPointX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].tDestStartPoint.lY = AVM3D_DestStartPointY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].tDestAreaSize.lX = AVM3D_DestAreaSizeX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].tDestAreaSize.lY = AVM3D_DestAreaSizeY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lVirtualCameraPosX = AVM3D_VirtualCameraPosX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lVirtualCameraPosY = AVM3D_VirtualCameraPosY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lVirtualCameraPosZ = AVM3D_VirtualCameraPosZ_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fVirtualCameraCustomRoll = AVM3D_VirtualCameraCustomRoll_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fVirtualCameraPitch = AVM3D_VirtualCameraPitch_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fVirtualCameraYaw = AVM3D_VirtualCameraYaw_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fVirtualCameraRoll = AVM3D_VirtualCameraRoll_1;
    a_ptAVM3D_tCfg->atViewCfg[0].ucVCFisheyeModel = AVM3D_VCFisheyeModel_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lMirror = AVM3D_Mirror_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eScalingX = AVM3D_ScalingX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eScalingY = AVM3D_ScalingY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lOffsetX = AVM3D_OffsetX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lOffsetY = AVM3D_OffsetY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[0].lX = AVM3D_StitchLineStartX0_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[0].lY = AVM3D_StitchLineStartY0_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[1].lX = AVM3D_StitchLineStartX1_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[1].lY = AVM3D_StitchLineStartY1_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[2].lX = AVM3D_StitchLineStartX2_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[2].lY = AVM3D_StitchLineStartY2_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[3].lX = AVM3D_StitchLineStartX3_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atStitchLineStart[3].lY = AVM3D_StitchLineStartY3_1;
    a_ptAVM3D_tCfg->atViewCfg[0].afStitchLineAngle[0] = AVM3D_StitchLineAngle0_1;
    a_ptAVM3D_tCfg->atViewCfg[0].afStitchLineAngle[1] = AVM3D_StitchLineAngle1_1;
    a_ptAVM3D_tCfg->atViewCfg[0].afStitchLineAngle[2] = AVM3D_StitchLineAngle2_1;
    a_ptAVM3D_tCfg->atViewCfg[0].afStitchLineAngle[3] = AVM3D_StitchLineAngle3_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fStitchAngleRange = AVM3D_StitchAngleRange_1;

    a_ptAVM3D_tCfg->atViewCfg[0].eCurveSurfaceA = AVM3D_CurveSurfaceA_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eCurveSurfaceB = AVM3D_CurveSurfaceB_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eCurveSurfaceC = AVM3D_CurveSurfaceC_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eCurveSurfaceD = AVM3D_CurveSurfaceD_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eCurveSurfaceE = AVM3D_CurveSurfaceE_1;
    a_ptAVM3D_tCfg->atViewCfg[0].eCurveSurfaceF = AVM3D_CurveSurfaceF_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fCurveCenterX = AVM3D_CurveCenterX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fCurveCenterY = AVM3D_CurveCenterY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].fCurveCenterZ = AVM3D_CurveCenterZ_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[0].lX = AVM3D_CornerLeftFrontX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[0].lY = AVM3D_CornerLeftFrontY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[1].lX = AVM3D_CornerRightFrontX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[1].lY = AVM3D_CornerRightFrontY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[2].lX = AVM3D_CornerLeftBackX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[2].lY = AVM3D_CornerLeftBackY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[3].lX = AVM3D_CornerRightBackX_1;
    a_ptAVM3D_tCfg->atViewCfg[0].atCornerPoint[3].lY = AVM3D_CornerRightBackY_1;
    a_ptAVM3D_tCfg->atViewCfg[0].lStitchLineType = AVM3D_StichLineType_1;
	a_ptAVM3D_tCfg->atViewCfg[0].lBlockDistance = AVM3D_BLOCK_SET_DISTANCE_1;

    AVM3D_OverlapLoadCfgLoadDefault(&(a_ptAVM3D_tCfg->atViewCfg[0].tOverlapLoadCfg));

	// initial morphing Cfg data
    memset(a_ptMorphingCfg, 0, sizeof(alAVM3D_MorphingCfgStruct));
}

void alAVM3D_MORPHING_CfgImportByINI(wchar_t * a_pwcConfigFilePath, alAVM3D_MorphingCfgStruct *a_ptMorphingCfg)
{
#ifdef WIN32
    INT32 lConvertedChars = 0, i = 0;
    wchar_t * pwcSectionName = L"AVM3D_MORPHING_Cfg";

    char acViewName[MAX_PATH] = { 0 };
    char acViewCnt[30] = { 0 };
    wchar_t pwcViewNo[MAX_PATH];
    wchar_t pwcTmpName[MAX_PATH] = { 0 };
    wchar_t pwcViewName[MAX_PATH] = { 0 };

    // AVM3D_MORPHING Cfg element Name
    wchar_t * AVM3D_MORPHING_SRC_INDEX = L"AVM3D_MORPHING_SRC_INDEX";
    wchar_t * AVM3D_MORPHING_DEST_INDEX = L"AVM3D_MORPHING_DEST_INDEX";
    wchar_t * AVM3D_MORPHING_FRAME_NUMBER = L"AVM3D_MORPHING_FRAME_NUMBER";
    wchar_t * AVM3D_MORPHING_TABLE_INDEX = L"AVM3D_MORPHING_TABLE_INDEX";
    wchar_t * AVM3D_MORPHING_MORPHING_TYPE = L"AVM3D_MORPHING_MORPHING_TYPE";
    // AVM3D_MORPHING Cfg element Name

    // reset 
    memset(a_ptMorphingCfg, 0, sizeof(alAVM3D_MorphingCfgStruct));

    // Global
    a_ptMorphingCfg->lMorphingNum = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_MORPHING_CNT");

    // each morphing cfg
    for (i = 0; i < a_ptMorphingCfg->lMorphingNum; i++)
    {
        sprintf(acViewCnt, "_%d", i + 1);
        // convert char to wchar_t
        setlocale(LC_ALL, "cht");
        mbstowcs(pwcViewNo, acViewCnt, MAX_PATH);
        setlocale(LC_ALL, "C");

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_MORPHING_SRC_INDEX
        wcscat_s(pwcTmpName, MAX_PATH, AVM3D_MORPHING_SRC_INDEX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptMorphingCfg->atMorphingSet[i].lSrcIndex = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_MORPHING_DEST_INDEX
        wcscat_s(pwcTmpName, MAX_PATH, AVM3D_MORPHING_DEST_INDEX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptMorphingCfg->atMorphingSet[i].lDestIndex = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_MORPHING_FRAME_NUMBER
        wcscat_s(pwcTmpName, MAX_PATH, AVM3D_MORPHING_FRAME_NUMBER);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptMorphingCfg->atMorphingSet[i].lFrameNumber = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_MORPHING_TABLE_INDEX
        wcscat_s(pwcTmpName, MAX_PATH, AVM3D_MORPHING_TABLE_INDEX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptMorphingCfg->atMorphingSet[i].lTableIndex = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_MORPHING_MORPHING_TYPE
        wcscat_s(pwcTmpName, MAX_PATH, AVM3D_MORPHING_MORPHING_TYPE);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptMorphingCfg->atMorphingSet[i].lMorphingType = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
    }
#endif
}

void alAVM3D_CfgImportByINIFile(wchar_t * a_pwcConfigFilePath, alAVM3D_Cfg *a_ptCfg)
{
#ifdef WIN32
    // wcstombs_s(
    // alINI_GetKeyValue_CW
    INT32 lConvertedChars = 0, i = 0;
    wchar_t * pwcSectionName = L"AVM3DCfg";

    char acViewName[MAX_PATH] = { 0 };
    char acViewCnt[30] = { 0 };
    wchar_t pwcViewNo[MAX_PATH];
    wchar_t pwcTmpName[MAX_PATH] = { 0 };
    wchar_t pwcViewName[MAX_PATH] = { 0 };

    // AVM3DCfg element Name
    wchar_t * pwcAVM3D_NAME = L"AVM3D_NAME";
    wchar_t * pwcAVM3D_DestImageBufferSizeX = L"AVM3D_DestImageBufferSizeX";
    wchar_t * pwcAVM3D_DestImageBufferSizeY = L"AVM3D_DestImageBufferSizeY";
    wchar_t * pwcAVM3D_DestStartPointX = L"AVM3D_DestStartPointX";
    wchar_t * pwcAVM3D_DestStartPointY = L"AVM3D_DestStartPointY";
    wchar_t * pwcAVM3D_DestAreaSizeX = L"AVM3D_DestAreaSizeX";
    wchar_t * pwcAVM3D_DestAreaSizeY = L"AVM3D_DestAreaSizeY";
    wchar_t * pwcAVM3D_VirtualCameraPosX = L"AVM3D_VirtualCameraPosX";
    wchar_t * pwcAVM3D_VirtualCameraPosY = L"AVM3D_VirtualCameraPosY";
    wchar_t * pwcAVM3D_VirtualCameraPosZ = L"AVM3D_VirtualCameraPosZ";
    wchar_t * pwcAVM3D_VirtualCameraCustomRoll = L"AVM3D_VirtualCameraCustomRoll";
    wchar_t * pwcAVM3D_VirtualCameraPitch = L"AVM3D_VirtualCameraPitch";
    wchar_t * pwcAVM3D_VirtualCameraYaw = L"AVM3D_VirtualCameraYaw";
    wchar_t * pwcAVM3D_VirtualCameraRoll = L"AVM3D_VirtualCameraRoll";
    wchar_t * pwcAVM3D_VCFisheyeModel = L"AVM3D_VCFisheyeModel";
    wchar_t * pwcAVM3D_Mirror = L"AVM3D_Mirror";
    wchar_t * pwcAVM3D_ScalingX = L"AVM3D_ScalingX";
    wchar_t * pwcAVM3D_ScalingY = L"AVM3D_ScalingY";
    wchar_t * pwcAVM3D_OffsetX = L"AVM3D_OffsetX";
    wchar_t * pwcAVM3D_OffsetY = L"AVM3D_OffsetY";
    wchar_t * pwcAVM3D_StitchLineStartX0 = L"AVM3D_StitchLineStartX0";
    wchar_t * pwcAVM3D_StitchLineStartY0 = L"AVM3D_StitchLineStartY0";
    wchar_t * pwcAVM3D_StitchLineStartX1 = L"AVM3D_StitchLineStartX1";
    wchar_t * pwcAVM3D_StitchLineStartY1 = L"AVM3D_StitchLineStartY1";
    wchar_t * pwcAVM3D_StitchLineStartX2 = L"AVM3D_StitchLineStartX2";
    wchar_t * pwcAVM3D_StitchLineStartY2 = L"AVM3D_StitchLineStartY2";
    wchar_t * pwcAVM3D_StitchLineStartX3 = L"AVM3D_StitchLineStartX3";
    wchar_t * pwcAVM3D_StitchLineStartY3 = L"AVM3D_StitchLineStartY3";
    wchar_t * pwcAVM3D_StitchLineAngle0 = L"AVM3D_StitchLineAngle0";
    wchar_t * pwcAVM3D_StitchLineAngle1 = L"AVM3D_StitchLineAngle1";
    wchar_t * pwcAVM3D_StitchLineAngle2 = L"AVM3D_StitchLineAngle2";
    wchar_t * pwcAVM3D_StitchLineAngle3 = L"AVM3D_StitchLineAngle3";
    wchar_t * pwcAVM3D_StitchAngleRange = L"AVM3D_StitchAngleRange";
    wchar_t * pwcAVM3D_CurveSurfaceA = L"AVM3D_CurveSurfaceA";
    wchar_t * pwcAVM3D_CurveSurfaceB = L"AVM3D_CurveSurfaceB";
    wchar_t * pwcAVM3D_CurveSurfaceC = L"AVM3D_CurveSurfaceC";
    wchar_t * pwcAVM3D_CurveSurfaceD = L"AVM3D_CurveSurfaceD";
    wchar_t * pwcAVM3D_CurveSurfaceE = L"AVM3D_CurveSurfaceE";
    wchar_t * pwcAVM3D_CurveSurfaceF = L"AVM3D_CurveSurfaceF";
    wchar_t * pwcAVM3D_CurveCenterX = L"AVM3D_CurveCenterX";
    wchar_t * pwcAVM3D_CurveCenterY = L"AVM3D_CurveCenterY";
    wchar_t * pwcAVM3D_CurveCenterZ = L"AVM3D_CurveCenterZ";
    wchar_t * pwcAVM3D_CornerLeftFrontX = L"AVM3D_CornerLeftFrontX";
    wchar_t * pwcAVM3D_CornerLeftFrontY = L"AVM3D_CornerLeftFrontY";
    wchar_t * pwcAVM3D_CornerRightFrontX = L"AVM3D_CornerRightFrontX";
    wchar_t * pwcAVM3D_CornerRightFrontY = L"AVM3D_CornerRightFrontY";
    wchar_t * pwcAVM3D_CornerLeftBackX = L"AVM3D_CornerLeftBackX";
    wchar_t * pwcAVM3D_CornerLeftBackY = L"AVM3D_CornerLeftBackY";
    wchar_t * pwcAVM3D_CornerRightBackX = L"AVM3D_CornerRightBackX";
    wchar_t * pwcAVM3D_CornerRightBackY = L"AVM3D_CornerRightBackY";
    wchar_t * pwcAVM3D_StichLineType = L"AVM3D_StichLineType";
    wchar_t * pwcAVM3D_BLOCK_SET_DISTANCE = L"AVM3D_BLOCK_SET_DISTANCE";
    wchar_t * pwcAVM3D_TOPVIEW_POSX = L"AVM3D_TOPVIEW_POSX";
    wchar_t * pwcAVM3D_TOPVIEW_POSY = L"AVM3D_TOPVIEW_POSY";
    wchar_t * pwcAVM3D_TOPVIEW_POSZ = L"AVM3D_TOPVIEW_POSZ";
    wchar_t * pwcAVM3D_TOPVIEW_CUSTOMROLL = L"AVM3D_TOPVIEW_CUSTOMROLL";
    wchar_t * pwcAVM3D_TOPVIEW_PITCH = L"AVM3D_TOPVIEW_PITCH";
    wchar_t * pwcAVM3D_TOPVIEW_YAW = L"AVM3D_TOPVIEW_YAW";
    wchar_t * pwcAVM3D_TOPVIEW_ROLL = L"AVM3D_TOPVIEW_ROLL";
    wchar_t * pwcAVM3D_LUT_GENERATE_FLAG = L"AVM3D_LUT_GENERATE_FLAG";
    wchar_t * pwcAVM3D_HEIGHT_LIMIT = L"AVM3D_HEIGHT_LIMIT";

    wchar_t * pwcAVM3D_CURVE2_FLAG = L"AVM3D_CURVE2_FLAG";
    wchar_t * pwcAVM3D_CURVE2_PROJECT_CENTER_Z = L"AVM3D_CURVE2_PROJECT_CENTER_Z";
    wchar_t * pwcAVM3D_Curve2SurfaceA = L"AVM3D_Curve2SurfaceA";
    wchar_t * pwcAVM3D_Curve2SurfaceB = L"AVM3D_Curve2SurfaceB";
    wchar_t * pwcAVM3D_Curve2SurfaceC = L"AVM3D_Curve2SurfaceC";
    wchar_t * pwcAVM3D_Curve2SurfaceD = L"AVM3D_Curve2SurfaceD";
    wchar_t * pwcAVM3D_Curve2SurfaceE = L"AVM3D_Curve2SurfaceE";
    wchar_t * pwcAVM3D_Curve2SurfaceF = L"AVM3D_Curve2SurfaceF";
    wchar_t * pwcAVM3D_Curve2CenterX = L"AVM3D_Curve2CenterX";
    wchar_t * pwcAVM3D_Curve2CenterY = L"AVM3D_Curve2CenterY";
    wchar_t * pwcAVM3D_Curve2CenterZ = L"AVM3D_Curve2CenterZ";

    // NEW
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTLEFT = L"AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTLEFT = L"AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTRIGHT = L"AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTRIGHT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTRIGHT = L"AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTRIGHT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_BACKLEFT = L"AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_BACKLEFT = L"AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_BACKRIGHT = L"AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKRIGHT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_BACKRIGHT = L"AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKRIGHT";

    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTLEFT = L"AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTLEFT = L"AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTRIGHT = L"AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTRIGHT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTRIGHT = L"AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTRIGHT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_BACKLEFT = L"AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_BACKLEFT = L"AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKLEFT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_BACKRIGHT = L"AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKRIGHT";
    wchar_t * pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_BACKRIGHT = L"AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKRIGHT";

    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_A = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_A";
    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_A = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_A";
    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_A = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_A";
    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_A = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_A";

    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_B = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_B";
    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_B = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_B";
    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_B = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_B";
    wchar_t * pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_B = L"AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_B";

    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_A = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_A";
    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_A = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_A";
    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_A = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_A";
    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_A = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_A";

    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_B = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_B";
    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_B = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_B";
    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_B = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_B";
    wchar_t * pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_B = L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_B";


    // NEW

    // AVM3DCfg element Name
    // Global
    a_ptCfg->lViewCnt = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_VIEW_CNT");

    a_ptCfg->alWarningLineOfAVM3DBack_s[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_BUMPER_1");
    a_ptCfg->alWarningLineOfAVM3DBack_s[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_SIDE_1");
    a_ptCfg->alWarningLineOfAVM3DBack_s[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_BUMPER_2");
    a_ptCfg->alWarningLineOfAVM3DBack_s[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_S_WARNING_LINE_TO_CAR_SIDE_2");

    a_ptCfg->alWarningLineOfAVM3DBack_f[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_BUMPER_1");
    a_ptCfg->alWarningLineOfAVM3DBack_f[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_SIDE_1");
    a_ptCfg->alWarningLineOfAVM3DBack_f[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_BUMPER_2");
    a_ptCfg->alWarningLineOfAVM3DBack_f[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_BACK_VEW_F_WARNING_LINE_TO_CAR_SIDE_2");


    // view test
    for (i = 0; i < a_ptCfg->lViewCnt; i++)
    {
        sprintf(acViewCnt, "_%d", i + 1);
        // convert char to wchar_t
        setlocale(LC_ALL, "cht");
        mbstowcs(pwcViewNo, acViewCnt, MAX_PATH);
        setlocale(LC_ALL, "C");

        wcscpy_s(pwcViewName, MAX_PATH, L"");

        // AVM3D_NAME
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_NAME);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        alINI_GetKeyValue_CW(a_pwcConfigFilePath, pwcSectionName, pwcTmpName, pwcViewName, MAX_PATH);
        wcstombs_s(&lConvertedChars, acViewName, MAX_PATH, pwcViewName, MAX_PATH);
        sprintf(a_ptCfg->atViewCfg[i].acName, "%s", acViewName);
        // a_ptCfg->atViewCfg[i].tDestImageBufferSize.X = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        //// NEW
        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTLEFT   >>> 0
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTLEFT	>>>> 1
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTRIGHT	>>>> 2
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_FRONTRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTRIGHT	>>>> 3
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_FRONTRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKLEFT   >>> 4
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_BACKLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKLEFT   >>> 5
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_BACKLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_A_BACKRIGHR   >>> 6
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_A_BACKRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_A_BACKRIGHT   >>> 7
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_A_BACKRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveA[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);


        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTLEFT   >>> 8
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTLEFT	>>>> 9
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTRIGHT	>>>> 10
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_FRONTRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTRIGHT	>>>> 11
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_FRONTRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKLEFT   >>> 12
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_BACKLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKLEFT   >>> 13
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_BACKLEFT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D1_CURVE_B_BACKRIGHR   >>> 14
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D1_CURVE_B_BACKRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_D0_CURVE_B_BACKRIGHT   >>> 15
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_D0_CURVE_B_BACKRIGHT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.alDistanceCurveB[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);


        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_A   >>> 16
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[0][0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_A   >>> 17
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[1][0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_A   >>> 18
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[2][0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_A   >>> 19
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[3][0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_B   >>> 20
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTLEFT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[0][1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_B   >>> 21
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_FRONTRIGHT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[1][1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_B   >>> 22
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKLEFT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[2][1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_B   >>> 23
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_BEZIERWEIGHT_BACKRIGHT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afBezierWeight[3][1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);


        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_A   >>> 24
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveALineAngleOffset[0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_A   >>> 25
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveALineAngleOffset[1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_A   >>> 26
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveALineAngleOffset[2] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_A   >>> 27
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_A);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveALineAngleOffset[3] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);


        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_B   >>> 28
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveBLineAngleOffset[0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_B   >>> 29
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveBLineAngleOffset[1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_B   >>> 30
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveBLineAngleOffset[2] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
        // AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_B   >>> 31
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_B);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tOverlapLoadCfg.afCurveBLineAngleOffset[3] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        //// NEW


        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_DestImageBufferSizeX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_DestImageBufferSizeX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tDestImageBufferSize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_DestImageBufferSizeY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_DestImageBufferSizeY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tDestImageBufferSize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_DestStartPointX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_DestStartPointX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tDestStartPoint.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_DestStartPointY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_DestStartPointY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tDestStartPoint.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_DestAreaSizeX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_DestAreaSizeX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tDestAreaSize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_DestAreaSizeY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_DestAreaSizeY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].tDestAreaSize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraPosX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraPosX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lVirtualCameraPosX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraPosY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraPosY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lVirtualCameraPosY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraPosZ
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraPosZ);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lVirtualCameraPosZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraCustomRoll
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraCustomRoll);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fVirtualCameraCustomRoll = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraPitch
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraPitch);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fVirtualCameraPitch = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraYaw
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraYaw);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fVirtualCameraYaw = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VirtualCameraRoll
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VirtualCameraRoll);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fVirtualCameraRoll = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_VCFisheyeModel
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_VCFisheyeModel);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].ucVCFisheyeModel = (UINT8)alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Mirror
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Mirror);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lMirror = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_ScalingX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_ScalingX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eScalingX = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_ScalingY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_ScalingY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eScalingY = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_OffsetX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OffsetX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_OffsetY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_OffsetY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lOffsetY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");


        // AVM3D_StitchLineStartX0
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartX0);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[0].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartY0
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartY0);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[0].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartX1
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartX1);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[1].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartY1
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartY1);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[1].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartX2
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartX2);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[2].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartY2
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartY2);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[2].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartX3
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartX3);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[3].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineStartY3
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineStartY3);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atStitchLineStart[3].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineAngle0
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineAngle0);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].afStitchLineAngle[0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineAngle1
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineAngle1);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].afStitchLineAngle[1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineAngle2
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineAngle2);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].afStitchLineAngle[2] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchLineAngle3
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchLineAngle3);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].afStitchLineAngle[3] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StitchAngleRange
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StitchAngleRange);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fStitchAngleRange = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveSurfaceA
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveSurfaceA);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurveSurfaceA = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveSurfaceB
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveSurfaceB);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurveSurfaceB = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveSurfaceC
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveSurfaceC);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurveSurfaceC = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveSurfaceD
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveSurfaceD);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurveSurfaceD = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveSurfaceE
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveSurfaceE);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurveSurfaceE = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveSurfaceF
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveSurfaceF);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurveSurfaceF = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveCenterX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveCenterX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fCurveCenterX = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveCenterY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveCenterY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fCurveCenterY = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CurveCenterZ
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CurveCenterZ);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fCurveCenterZ = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerLeftFrontX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerLeftFrontX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[0].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerLeftFrontY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerLeftFrontY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[0].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerRightFrontX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerRightFrontX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[1].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerRightFrontY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerRightFrontY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[1].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerLeftBackX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerLeftBackX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[2].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerLeftBackY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerLeftBackY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[2].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerRightBackX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerRightBackX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[3].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CornerRightBackY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CornerRightBackY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].atCornerPoint[3].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_StichLineType
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_StichLineType);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lStitchLineType = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_BLOCK_SET_DISTANCE
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_BLOCK_SET_DISTANCE);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lBlockDistance = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_TOPVIEW_POSX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_POSX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lTopViewPosX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_TOPVIEW_POSY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_POSY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lTopViewPosY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_TOPVIEW_POSZ
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_POSZ);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lTopViewPosZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");


        // AVM3D_TOPVIEW_CUSTOMROLL
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_CUSTOMROLL);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fTopViewCustomRoll = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_TOPVIEW_PITCH
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_PITCH);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fTopViewPitch = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_TOPVIEW_YAW
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_YAW);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fTopViewYaw = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_TOPVIEW_ROLL
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_TOPVIEW_ROLL);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fTopViewRoll = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_LUT_GENERATE_FLAG
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_LUT_GENERATE_FLAG);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lLUTGenFlag = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_HEIGHT_LIMIT
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_HEIGHT_LIMIT);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lHeightLimit = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CURVE2_FLAG
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CURVE2_FLAG);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lCURVE2_FLAG = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_CURVE2_FLAG
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_CURVE2_PROJECT_CENTER_Z);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].lCurve2ProjCenZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");


        // AVM3D_Curve2SurfaceA
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2SurfaceA);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurve2SurfaceA = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2SurfaceB
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2SurfaceB);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurve2SurfaceB = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2SurfaceC
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2SurfaceC);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurve2SurfaceC = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2SurfaceD
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2SurfaceD);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurve2SurfaceD = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2SurfaceE
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2SurfaceE);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurve2SurfaceE = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2SurfaceF
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2SurfaceF);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].eCurve2SurfaceF = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2CenterX
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2CenterX);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fCurve2CenterX = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2CenterY
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2CenterY);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fCurve2CenterY = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");

        // AVM3D_Curve2CenterZ
        wcscat_s(pwcTmpName, MAX_PATH, pwcAVM3D_Curve2CenterZ);
        wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
        a_ptCfg->atViewCfg[i].fCurve2CenterZ = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

        wcscpy_s(pwcTmpName, MAX_PATH, L"");
    }
#endif
}

