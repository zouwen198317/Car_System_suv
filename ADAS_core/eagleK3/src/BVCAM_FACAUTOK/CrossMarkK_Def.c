#include "BVCAM_FACAUTOK/CrossMarkK_Def.h"



void alCROSSMARKK_LoadDefault(INT32 a_lMode, alCROSSMARKK_Cfg *a_ptCFGData)
{
	memset(a_ptCFGData, 0, sizeof(alCROSSMARKK_Cfg));

	switch (a_lMode)
	{
	case 0: // -90 degree Left
		a_ptCFGData->ucMode = alCROSSMARKK_MODE_LEFT;
		a_ptCFGData->lROINum = alCROSSMARKK_ROINUM_LEFT;
		
		a_ptCFGData->atROICfg[0].aeSBVScale = alCROSSMARKK_SBV_SCALE_LEFT_1;
		a_ptCFGData->atROICfg[1].aeSBVScale = alCROSSMARKK_SBV_SCALE_LEFT_2;
		a_ptCFGData->atROICfg[2].aeSBVScale = alCROSSMARKK_SBV_SCALE_LEFT_3;
		a_ptCFGData->atROICfg[3].aeSBVScale = alCROSSMARKK_SBV_SCALE_LEFT_4;

		a_ptCFGData->atROICfg[0].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_LEFT_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_LEFT_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_LEFT_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_LEFT_4;

		a_ptCFGData->atROICfg[0].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_LEFT_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_LEFT_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_LEFT_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_LEFT_4;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_LEFT_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_LEFT_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_LEFT_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_LEFT_4;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_LEFT_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_LEFT_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_LEFT_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_LEFT_4;

        // CrossMark Constraint
        a_ptCFGData->atCrossMarkDetCfg[0].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_LEFT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_LEFT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_LEFT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_LEFT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_LEFT_1;

        a_ptCFGData->atCrossMarkDetCfg[1].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_LEFT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_LEFT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_LEFT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_LEFT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_LEFT_2;

        a_ptCFGData->atCrossMarkDetCfg[2].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_LEFT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_LEFT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_LEFT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_LEFT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_LEFT_3;

        a_ptCFGData->atCrossMarkDetCfg[3].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_LEFT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_LEFT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_LEFT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_LEFT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_LEFT_4;

        // ROI size
        a_ptCFGData->atROICfg[0].tROISize.lX = alCROSSMARKK_DETECT_ROI_LEFT_W_1; 
        a_ptCFGData->atROICfg[0].tROISize.lY = alCROSSMARKK_DETECT_ROI_LEFT_H_1; 
        a_ptCFGData->atROICfg[1].tROISize.lX = alCROSSMARKK_DETECT_ROI_LEFT_W_2; 
        a_ptCFGData->atROICfg[1].tROISize.lY = alCROSSMARKK_DETECT_ROI_LEFT_H_2; 
        a_ptCFGData->atROICfg[2].tROISize.lX = alCROSSMARKK_DETECT_ROI_LEFT_W_3; 
        a_ptCFGData->atROICfg[2].tROISize.lY = alCROSSMARKK_DETECT_ROI_LEFT_H_3; 
        a_ptCFGData->atROICfg[3].tROISize.lX = alCROSSMARKK_DETECT_ROI_LEFT_W_4; 
        a_ptCFGData->atROICfg[3].tROISize.lY = alCROSSMARKK_DETECT_ROI_LEFT_H_4; 
		break;
	case 1: // +90 degree Right
		a_ptCFGData->ucMode = alCROSSMARKK_MODE_RIGHT;
		a_ptCFGData->lROINum = alCROSSMARKK_ROINUM_RIGHT;
		a_ptCFGData->atROICfg[0].aeSBVScale = alCROSSMARKK_SBV_SCALE_RIGHT_1;
		a_ptCFGData->atROICfg[1].aeSBVScale = alCROSSMARKK_SBV_SCALE_RIGHT_2;
		a_ptCFGData->atROICfg[2].aeSBVScale = alCROSSMARKK_SBV_SCALE_RIGHT_3;
		a_ptCFGData->atROICfg[3].aeSBVScale = alCROSSMARKK_SBV_SCALE_RIGHT_4;

		a_ptCFGData->atROICfg[0].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_RIGHT_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_RIGHT_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_RIGHT_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_RIGHT_4;

		a_ptCFGData->atROICfg[0].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_RIGHT_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_RIGHT_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_RIGHT_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_RIGHT_4;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_RIGHT_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_RIGHT_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_RIGHT_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_RIGHT_4;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_RIGHT_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_RIGHT_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_RIGHT_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_RIGHT_4;

        // CrossMark Constraint
        a_ptCFGData->atCrossMarkDetCfg[0].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_RIGHT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_RIGHT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_RIGHT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_RIGHT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_RIGHT_1;

        a_ptCFGData->atCrossMarkDetCfg[1].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_RIGHT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_RIGHT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_RIGHT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_RIGHT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_RIGHT_2;

        a_ptCFGData->atCrossMarkDetCfg[2].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_RIGHT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_RIGHT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_RIGHT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_RIGHT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_RIGHT_3;

        a_ptCFGData->atCrossMarkDetCfg[3].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_RIGHT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_RIGHT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_RIGHT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_RIGHT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_RIGHT_4;

        // ROI size
        a_ptCFGData->atROICfg[0].tROISize.lX = alCROSSMARKK_DETECT_ROI_RIGHT_W_1;
        a_ptCFGData->atROICfg[0].tROISize.lY = alCROSSMARKK_DETECT_ROI_RIGHT_H_1;
        a_ptCFGData->atROICfg[1].tROISize.lX = alCROSSMARKK_DETECT_ROI_RIGHT_W_2;
        a_ptCFGData->atROICfg[1].tROISize.lY = alCROSSMARKK_DETECT_ROI_RIGHT_H_2;
        a_ptCFGData->atROICfg[2].tROISize.lX = alCROSSMARKK_DETECT_ROI_RIGHT_W_3;
        a_ptCFGData->atROICfg[2].tROISize.lY = alCROSSMARKK_DETECT_ROI_RIGHT_H_3;
        a_ptCFGData->atROICfg[3].tROISize.lX = alCROSSMARKK_DETECT_ROI_RIGHT_W_4;
        a_ptCFGData->atROICfg[3].tROISize.lY = alCROSSMARKK_DETECT_ROI_RIGHT_H_4;
		break;
	case 2: // 180 degree Front
		a_ptCFGData->ucMode = alCROSSMARKK_MODE_FRONT;
		a_ptCFGData->lROINum = alCROSSMARKK_ROINUM_FRONT;
		a_ptCFGData->atROICfg[0].aeSBVScale = alCROSSMARKK_SBV_SCALE_FRONT_1;
		a_ptCFGData->atROICfg[1].aeSBVScale = alCROSSMARKK_SBV_SCALE_FRONT_2;
		a_ptCFGData->atROICfg[2].aeSBVScale = alCROSSMARKK_SBV_SCALE_FRONT_3;
		a_ptCFGData->atROICfg[3].aeSBVScale = alCROSSMARKK_SBV_SCALE_FRONT_4;
		a_ptCFGData->atROICfg[4].aeSBVScale = alCROSSMARKK_SBV_SCALE_FRONT_5;
		a_ptCFGData->atROICfg[5].aeSBVScale = alCROSSMARKK_SBV_SCALE_FRONT_6;

		a_ptCFGData->atROICfg[0].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_FRONT_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_FRONT_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_FRONT_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_FRONT_4;
		a_ptCFGData->atROICfg[4].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_FRONT_5;
		a_ptCFGData->atROICfg[5].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_FRONT_6;

		a_ptCFGData->atROICfg[0].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_FRONT_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_FRONT_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_FRONT_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_FRONT_4;
		a_ptCFGData->atROICfg[4].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_FRONT_5;
		a_ptCFGData->atROICfg[5].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_FRONT_6;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_FRONT_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_FRONT_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_FRONT_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_FRONT_4;
		a_ptCFGData->atROICfg[4].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_FRONT_5;
		a_ptCFGData->atROICfg[5].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_FRONT_6;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_FRONT_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_FRONT_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_FRONT_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_FRONT_4;
		a_ptCFGData->atROICfg[4].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_FRONT_5;
		a_ptCFGData->atROICfg[5].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_FRONT_6;

        // CrossMark Constraint
        a_ptCFGData->atCrossMarkDetCfg[0].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_FRONT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_FRONT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_FRONT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_FRONT_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_FRONT_1;

        a_ptCFGData->atCrossMarkDetCfg[1].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_FRONT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_FRONT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_FRONT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_FRONT_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_FRONT_2;

        a_ptCFGData->atCrossMarkDetCfg[2].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_FRONT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_FRONT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_FRONT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_FRONT_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_FRONT_3;

        a_ptCFGData->atCrossMarkDetCfg[3].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_FRONT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_FRONT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_FRONT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_FRONT_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_FRONT_4;

        a_ptCFGData->atCrossMarkDetCfg[4].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_FRONT_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_FRONT_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_FRONT_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_FRONT_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_FRONT_5;

        a_ptCFGData->atCrossMarkDetCfg[5].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_FRONT_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_FRONT_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_FRONT_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_FRONT_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_FRONT_6;

        // ROI size
        a_ptCFGData->atROICfg[0].tROISize.lX = alCROSSMARKK_DETECT_ROI_FRONT_W_1;
        a_ptCFGData->atROICfg[0].tROISize.lY = alCROSSMARKK_DETECT_ROI_FRONT_H_1;
        a_ptCFGData->atROICfg[1].tROISize.lX = alCROSSMARKK_DETECT_ROI_FRONT_W_2;
        a_ptCFGData->atROICfg[1].tROISize.lY = alCROSSMARKK_DETECT_ROI_FRONT_H_2;
        a_ptCFGData->atROICfg[2].tROISize.lX = alCROSSMARKK_DETECT_ROI_FRONT_W_3;
        a_ptCFGData->atROICfg[2].tROISize.lY = alCROSSMARKK_DETECT_ROI_FRONT_H_3;
        a_ptCFGData->atROICfg[3].tROISize.lX = alCROSSMARKK_DETECT_ROI_FRONT_W_4;
        a_ptCFGData->atROICfg[3].tROISize.lY = alCROSSMARKK_DETECT_ROI_FRONT_H_4;
        a_ptCFGData->atROICfg[4].tROISize.lX = alCROSSMARKK_DETECT_ROI_FRONT_W_5;
        a_ptCFGData->atROICfg[4].tROISize.lY = alCROSSMARKK_DETECT_ROI_FRONT_H_5;
        a_ptCFGData->atROICfg[5].tROISize.lX = alCROSSMARKK_DETECT_ROI_FRONT_W_6;
        a_ptCFGData->atROICfg[5].tROISize.lY = alCROSSMARKK_DETECT_ROI_FRONT_H_6;
		break;
	case 3:  // 0 degree Back
		a_ptCFGData->ucMode = alCROSSMARKK_MODE_BACK;
		a_ptCFGData->lROINum = alCROSSMARKK_ROINUM_BACK;
		a_ptCFGData->atROICfg[0].aeSBVScale = alCROSSMARKK_SBV_SCALE_BACK_1;
		a_ptCFGData->atROICfg[1].aeSBVScale = alCROSSMARKK_SBV_SCALE_BACK_2;
		a_ptCFGData->atROICfg[2].aeSBVScale = alCROSSMARKK_SBV_SCALE_BACK_3;
		a_ptCFGData->atROICfg[3].aeSBVScale = alCROSSMARKK_SBV_SCALE_BACK_4;
		a_ptCFGData->atROICfg[4].aeSBVScale = alCROSSMARKK_SBV_SCALE_BACK_5;
		a_ptCFGData->atROICfg[5].aeSBVScale = alCROSSMARKK_SBV_SCALE_BACK_6;

		a_ptCFGData->atROICfg[0].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_BACK_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_BACK_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_BACK_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_BACK_4;
		a_ptCFGData->atROICfg[4].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_BACK_5;
		a_ptCFGData->atROICfg[5].alSBVOffsetX = alCROSSMARKK_SBV_OFFSETX_BACK_6;

		a_ptCFGData->atROICfg[0].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_BACK_1;
		a_ptCFGData->atROICfg[1].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_BACK_2;
		a_ptCFGData->atROICfg[2].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_BACK_3;
		a_ptCFGData->atROICfg[3].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_BACK_4;
		a_ptCFGData->atROICfg[4].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_BACK_5;
		a_ptCFGData->atROICfg[5].alSBVOffsetY = alCROSSMARKK_SBV_OFFSETY_BACK_6;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_BACK_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_BACK_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_BACK_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_BACK_4;
		a_ptCFGData->atROICfg[4].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_BACK_5;
		a_ptCFGData->atROICfg[5].lSBVDetectOffsetX = alCROSSMARKK_CROSSMARK_OFFSETX_BACK_6;

		a_ptCFGData->atROICfg[0].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_BACK_1;
		a_ptCFGData->atROICfg[1].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_BACK_2;
		a_ptCFGData->atROICfg[2].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_BACK_3;
		a_ptCFGData->atROICfg[3].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_BACK_4;
		a_ptCFGData->atROICfg[4].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_BACK_5;
		a_ptCFGData->atROICfg[5].lSBVDetectOffsetY = alCROSSMARKK_CROSSMARK_OFFSETY_BACK_6;

        // CrossMark Constraint
        a_ptCFGData->atCrossMarkDetCfg[0].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_BACK_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_BACK_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_BACK_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_BACK_1;
        a_ptCFGData->atCrossMarkDetCfg[0].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_BACK_1;

        a_ptCFGData->atCrossMarkDetCfg[1].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_BACK_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_BACK_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_BACK_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_BACK_2;
        a_ptCFGData->atCrossMarkDetCfg[1].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_BACK_2;

        a_ptCFGData->atCrossMarkDetCfg[2].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_BACK_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_BACK_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_BACK_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_BACK_3;
        a_ptCFGData->atCrossMarkDetCfg[2].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_BACK_3;

        a_ptCFGData->atCrossMarkDetCfg[3].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_BACK_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_BACK_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_BACK_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_BACK_4;
        a_ptCFGData->atCrossMarkDetCfg[3].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_BACK_4;

        a_ptCFGData->atCrossMarkDetCfg[4].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_BACK_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_BACK_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_BACK_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_BACK_5;
        a_ptCFGData->atCrossMarkDetCfg[4].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_BACK_5;

        a_ptCFGData->atCrossMarkDetCfg[5].eDifferenceTH = alCROSSMARKK_CROSSMARK_DIFF_TH_BACK_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceInDetailTH = alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH_BACK_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceInTH = alCROSSMARKK_CROSSMARK_VARIN_TH_BACK_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceOutTH = alCROSSMARKK_CROSSMARK_VAROUT_TH_BACK_6;
        a_ptCFGData->atCrossMarkDetCfg[5].eVarianceTH = alCROSSMARKK_CROSSMARK_VAR_TH_BACK_6;
        
        // ROI size
        a_ptCFGData->atROICfg[0].tROISize.lX = alCROSSMARKK_DETECT_ROI_BACK_W_1;
        a_ptCFGData->atROICfg[0].tROISize.lY = alCROSSMARKK_DETECT_ROI_BACK_H_1;
        a_ptCFGData->atROICfg[1].tROISize.lX = alCROSSMARKK_DETECT_ROI_BACK_W_2;
        a_ptCFGData->atROICfg[1].tROISize.lY = alCROSSMARKK_DETECT_ROI_BACK_H_2;
        a_ptCFGData->atROICfg[2].tROISize.lX = alCROSSMARKK_DETECT_ROI_BACK_W_3;
        a_ptCFGData->atROICfg[2].tROISize.lY = alCROSSMARKK_DETECT_ROI_BACK_H_3;
        a_ptCFGData->atROICfg[3].tROISize.lX = alCROSSMARKK_DETECT_ROI_BACK_W_4;
        a_ptCFGData->atROICfg[3].tROISize.lY = alCROSSMARKK_DETECT_ROI_BACK_H_4;
        a_ptCFGData->atROICfg[4].tROISize.lX = alCROSSMARKK_DETECT_ROI_BACK_W_5;
        a_ptCFGData->atROICfg[4].tROISize.lY = alCROSSMARKK_DETECT_ROI_BACK_H_5;
        a_ptCFGData->atROICfg[5].tROISize.lX = alCROSSMARKK_DETECT_ROI_BACK_W_6;
        a_ptCFGData->atROICfg[5].tROISize.lY = alCROSSMARKK_DETECT_ROI_BACK_H_6;
		break;
	default:
		assert(0);
		break;
	}
}
