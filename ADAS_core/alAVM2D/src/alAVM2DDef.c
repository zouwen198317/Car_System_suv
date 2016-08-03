
#include "alAVM2DDef.h"
#include "alHexData.h"
#include "basedef.h"
#ifdef WIN32 // FW 裡不允許讀INI檔
#include "alINI.h"
#endif
#include <assert.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
void alAVM2D_LoadDefault(alAVM2D_Cfg    *a_ptAVM2D_Cfg)
{
    a_ptAVM2D_Cfg->ucFunctionEnabled = SIM_DEFAULT_alAVM2D_FUNCTION_ENABLED;
    a_ptAVM2D_Cfg->ulBVMaxDistance = SIM_DEFAULT_alAVM2D_MAXIMUM_DISTANCE;

    a_ptAVM2D_Cfg->ulBVBlindDistanceFront = SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_FRONT;
    a_ptAVM2D_Cfg->ulBVBlindDistanceBack = SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_BACK;
    a_ptAVM2D_Cfg->ulBVBlindDistanceLeft = SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_LEFT;
    a_ptAVM2D_Cfg->ulBVBlindDistanceRight = SIM_DEFAULT_alAVM2D_BLIND_DISTANCE_RIGHT;

    a_ptAVM2D_Cfg->tDestStartPoint.lX = SIM_DEFAULT_alAVM2D_DEST_START_POINT_X;
	a_ptAVM2D_Cfg->tDestStartPoint.lY = SIM_DEFAULT_alAVM2D_DEST_START_POINT_Y;
	a_ptAVM2D_Cfg->tDestImageBufferSize.lX = SIM_DEFAULT_alAVM2D_DEST_IMAGE_BUFFER_SIZE_X;
	a_ptAVM2D_Cfg->tDestImageBufferSize.lY = SIM_DEFAULT_alAVM2D_DEST_IMAGE_BUFFER_SIZE_Y;

    a_ptAVM2D_Cfg->ucStitchLineType = 0;
    a_ptAVM2D_Cfg->atStitchLineStart[0].lX = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_0_X;
    a_ptAVM2D_Cfg->atStitchLineStart[0].lY = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_0_Y;
    a_ptAVM2D_Cfg->atStitchLineStart[1].lX = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_1_X;
    a_ptAVM2D_Cfg->atStitchLineStart[1].lY = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_1_Y;
    a_ptAVM2D_Cfg->atStitchLineStart[2].lX = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_2_X;
    a_ptAVM2D_Cfg->atStitchLineStart[2].lY = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_2_Y;
    a_ptAVM2D_Cfg->atStitchLineStart[3].lX = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_3_X;
    a_ptAVM2D_Cfg->atStitchLineStart[3].lY = SIM_DEFAULT_alAVM2D_STITCH_LINE_STRAT_3_Y;

    a_ptAVM2D_Cfg->afStitchLineAngle[0] = SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_0;
    a_ptAVM2D_Cfg->afStitchLineAngle[1] = SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_1;
    a_ptAVM2D_Cfg->afStitchLineAngle[2] = SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_2;
    a_ptAVM2D_Cfg->afStitchLineAngle[3] = SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_3;
    a_ptAVM2D_Cfg->fStitchAngleRange = SIM_DEFAULT_alAVM2D_STITCH_LINE_ANGLE_RANGE; 

    a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lX = SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_NUMBER_X;
    a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lY = SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_NUMBER_Y;
    a_ptAVM2D_Cfg->tBVGAE_ROIPixelOffset.lX = SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_OFFSET_X;
    a_ptAVM2D_Cfg->tBVGAE_ROIPixelOffset.lY = SIM_DEFAULT_alAVM2D_GAE_ROI_PIXEL_OFFSET_Y;
    a_ptAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lX = SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_X;
    a_ptAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lY = SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_Y;
    a_ptAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lX = SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_X;
    a_ptAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lY = SIM_DEFAULT_alAVM2D_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_Y;
    a_ptAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lX = SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_X;
    a_ptAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lY = SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_Y;
    a_ptAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lX = SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_X;
    a_ptAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lY = SIM_DEFAULT_alAVM2D_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_Y;

#if 0  // 先拿掉alAVM2D導R角參數
	a_ptAVM2D_Cfg->lBlockDistance = SIM_DEFAULT_alAVM2D_BLOCK_SET_DISTANCE;
#endif
}

#ifdef WIN32 // FW 裡不允許讀INI檔
void alAVM2D_CfgImportByINIFile(wchar_t * a_pwcConfigFilePath, alAVM2D_Cfg *a_ptCfg)
{
#if 1
    wchar_t * pwcSectionName = L"AVM2DCfg";

    a_ptCfg->ucFunctionEnabled = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_FUNCTION_ENABLED");
    a_ptCfg->ulBVMaxDistance = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_MAXIMUM_DISTANCE");
    a_ptCfg->ulBVBlindDistanceFront = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_BLIND_DISTANCE_FRONT");
    a_ptCfg->ulBVBlindDistanceBack = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_BLIND_DISTANCE_BACK");
    a_ptCfg->ulBVBlindDistanceLeft = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_BLIND_DISTANCE_LEFT");
    a_ptCfg->ulBVBlindDistanceRight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_BLIND_DISTANCE_RIGHT");

    a_ptCfg->tDestStartPoint.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_DestStartPoint_X");
    a_ptCfg->tDestStartPoint.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_DestStartPoint_Y");
    a_ptCfg->tDestImageBufferSize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_DEST_IMAGE_BUFFER_SIZE_X");
    a_ptCfg->tDestImageBufferSize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_DEST_IMAGE_BUFFER_SIZE_Y");

    a_ptCfg->ucStitchLineType = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_TYPE");

#if 0  // 先拿掉alAVM2D導R角參數
    a_ptCfg->lBlockDistance = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_BLOCK_SET_DISTANCE");
#endif

    // CurveA
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_A_FRONTLEFT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_A_FRONTLEFT");

    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_A_FRONTRIGHT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_A_FRONTRIGHT");

    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_A_BACKLEFT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_A_BACKLEFT");

    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_A_BACKRIGHT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveA[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_A_BACKRIGHT");

    a_ptCfg->tOverlapLoadCfg.afCurveALineAngleOffset[0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_A");
    a_ptCfg->tOverlapLoadCfg.afCurveALineAngleOffset[1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_A");
    a_ptCfg->tOverlapLoadCfg.afCurveALineAngleOffset[2] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_A");
    a_ptCfg->tOverlapLoadCfg.afCurveALineAngleOffset[3] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM3D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_A");

    // CurveB
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_B_FRONTLEFT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_B_FRONTLEFT");

    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_B_FRONTRIGHT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_B_FRONTRIGHT");

    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_B_BACKLEFT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_B_BACKLEFT");

    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_LONG_CURVE_B_BACKRIGHT");
    a_ptCfg->tOverlapLoadCfg.alDistanceCurveB[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_D_SHORT_CURVE_B_BACKRIGHT");

    a_ptCfg->tOverlapLoadCfg.afCurveBLineAngleOffset[0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_ANGLEOFFSET_FRONTLEFT_B");
    a_ptCfg->tOverlapLoadCfg.afCurveBLineAngleOffset[1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_ANGLEOFFSET_FRONTRIGHT_B");
    a_ptCfg->tOverlapLoadCfg.afCurveBLineAngleOffset[2] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_ANGLEOFFSET_BACKLEFT_B");
    a_ptCfg->tOverlapLoadCfg.afCurveBLineAngleOffset[3] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_OVERLAP_CFG_ANGLEOFFSET_BACKRIGHT_B");

    a_ptCfg->atStitchLineStart[0].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_0_X");
    a_ptCfg->atStitchLineStart[0].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_0_Y");
    a_ptCfg->atStitchLineStart[1].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_1_X");
    a_ptCfg->atStitchLineStart[1].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_1_Y");
    a_ptCfg->atStitchLineStart[2].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_2_X");
    a_ptCfg->atStitchLineStart[2].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_2_Y");
    a_ptCfg->atStitchLineStart[3].lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_3_X");
    a_ptCfg->atStitchLineStart[3].lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_STRAT_3_Y");


    a_ptCfg->afStitchLineAngle[0] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_ANGLE_0");
    a_ptCfg->afStitchLineAngle[1] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_ANGLE_1");
    a_ptCfg->afStitchLineAngle[2] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_ANGLE_2");
    a_ptCfg->afStitchLineAngle[3] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_ANGLE_3");

    a_ptCfg->fStitchAngleRange = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_STITCH_LINE_ANGLE_RANGE");


    // ROI pixel size for BV Global AE
    a_ptCfg->tBVGAE_ROIPixelNumber.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_PIXEL_NUMBER_X");
    a_ptCfg->tBVGAE_ROIPixelNumber.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_PIXEL_NUMBER_Y");

    // lBVGAE_ROIPixelNumber.lX & lBVGAE_ROIPixelNumber.lY must be even number
    assert((a_ptCfg->tBVGAE_ROIPixelNumber.lX & 0x1) == 0 && (a_ptCfg->tBVGAE_ROIPixelNumber.lY & 0x1) == 0);

    // ROI pixel offset for BV Global AE
    a_ptCfg->tBVGAE_ROIPixelOffset.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_PIXEL_OFFSET_X");
    a_ptCfg->tBVGAE_ROIPixelOffset.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_PIXEL_OFFSET_Y");

    // The offset between Global AE ROI and Car Pic - Front-Left
    a_ptCfg->tBVGAE_ROIFrontLeftOffse2CarPict.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_X");
    a_ptCfg->tBVGAE_ROIFrontLeftOffse2CarPict.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_FRONT_LEFT_OFFSET_TO_CAR_PIC_Y");

    // The offset between Global AE ROI and Car Pic - Front-Right
    a_ptCfg->tBVGAE_ROIFrontRightOffse2CarPict.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_X");
    a_ptCfg->tBVGAE_ROIFrontRightOffse2CarPict.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_FRONT_RIGHT_OFFSET_TO_CAR_PIC_Y");

    // The offset between Global AE ROI and Car Pic - Rear-Left
    a_ptCfg->tBVGAE_ROIRearLeftOffse2CarPict.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_X");
    a_ptCfg->tBVGAE_ROIRearLeftOffse2CarPict.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_REAR_LEFT_OFFSET_TO_CAR_PIC_Y");

    // The offset between Global AE ROI and Car Pic - Rear-Right
    a_ptCfg->tBVGAE_ROIRearRightOffse2CarPict.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_X");
    a_ptCfg->tBVGAE_ROIRearRightOffse2CarPict.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"AVM2D_GAE_ROI_REAR_RIGHT_OFFSET_TO_CAR_PIC_Y");
#endif
}
#endif

void alAVM2D_CfgImportByHexData(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 *a_pucBuffer, alAVM2D_Cfg  *a_ptAVM2D_Cfg)
{
    UINT32 ulDataIndex = 0;

    switch (a_ulDataID & 0xFFFF)
    {
    case 0x0000:    // Function Enabled
    {
        a_ptAVM2D_Cfg->ucFunctionEnabled = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0001:    // ulBVMaxDistance
    {
        a_ptAVM2D_Cfg->ulBVMaxDistance = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0002:    // ulBVBlindDistanceFront
    {
        a_ptAVM2D_Cfg->ulBVBlindDistanceFront = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0003:    // ulBVBlindDistanceBack
    {
        a_ptAVM2D_Cfg->ulBVBlindDistanceBack = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0004:    // ulBVBlindDistanceLeft
    {
        a_ptAVM2D_Cfg->ulBVBlindDistanceLeft = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0005:    // ulBVBlindDistanceRight
    {
        a_ptAVM2D_Cfg->ulBVBlindDistanceRight = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0006:    // tDestStartPoint.X
    {
        a_ptAVM2D_Cfg->tDestStartPoint.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0007:    // tDestStartPoint.Y
    {
        a_ptAVM2D_Cfg->tDestStartPoint.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0008:    // tDestImageBufferSize.lX
    {
        a_ptAVM2D_Cfg->tDestImageBufferSize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0009:    // tDestImageBufferSize.lY
    {
        a_ptAVM2D_Cfg->tDestImageBufferSize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000A:    // ucStitchLineType
    {
        a_ptAVM2D_Cfg->ucStitchLineType = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000B:    // tBVGAE_ROIPixelNumber.lX
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000C:    // tBVGAE_ROIPixelNumber.lY
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIPixelNumber.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000D:    // tBVGAE_ROIPixelOffset.lX
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIPixelOffset.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000E:    // tBVGAE_ROIPixelOffset.lY
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIPixelOffset.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000F:    // tBVGAE_ROIFrontLeftOffse2CarPict.lX
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0010:    // tBVGAE_ROIFrontLeftOffse2CarPict.lY
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0011:    // tBVGAE_ROIFrontRightOffse2CarPict.lX
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0012:    // tBVGAE_ROIFrontRightOffse2CarPict.lY
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0013:    // tBVGAE_ROIRearLeftOffse2CarPict.lX
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0014:    // tBVGAE_ROIRearLeftOffse2CarPict.lY
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0015:    // tBVGAE_ROIRearRightOffse2CarPict.lX
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0016:    // tBVGAE_ROIRearRightOffse2CarPict.lY
    {
        a_ptAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0017:    // fStitchAngleRange
    {
        a_ptAVM2D_Cfg->fStitchAngleRange = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0018:    // afStitchLineAngle[0]
    {
        a_ptAVM2D_Cfg->afStitchLineAngle[0] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0019:    // afStitchLineAngle[1]
    {
        a_ptAVM2D_Cfg->afStitchLineAngle[1] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001A:    // afStitchLineAngle[2]
    {
        a_ptAVM2D_Cfg->afStitchLineAngle[2] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001B:    // afStitchLineAngle[3]
    {
        a_ptAVM2D_Cfg->afStitchLineAngle[3] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001C:    // atStitchLineStart[0].lX
    {
        a_ptAVM2D_Cfg->atStitchLineStart[0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001D:    // atStitchLineStart[0].lY
    {
        a_ptAVM2D_Cfg->atStitchLineStart[0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001E:    // atStitchLineStart[1].lX
    {
        a_ptAVM2D_Cfg->atStitchLineStart[1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001F:    // atStitchLineStart[1].lY
    {
        a_ptAVM2D_Cfg->atStitchLineStart[1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0020:    // atStitchLineStart[2].lX
    {
        a_ptAVM2D_Cfg->atStitchLineStart[2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0021:    // atStitchLineStart[2].lY
    {
        a_ptAVM2D_Cfg->atStitchLineStart[2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0022:    // atStitchLineStart[3].lX
    {
        a_ptAVM2D_Cfg->atStitchLineStart[3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0023:    // atStitchLineStart[3].lY
    {
        a_ptAVM2D_Cfg->atStitchLineStart[3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0024:    // tOverlapLoadCfg.alDistanceCurveA[0][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[0][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0025:    // tOverlapLoadCfg.alDistanceCurveA[0][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[0][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0026:    // tOverlapLoadCfg.alDistanceCurveA[1][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[1][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0027:    // tOverlapLoadCfg.alDistanceCurveA[1][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[1][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0028:    // tOverlapLoadCfg.alDistanceCurveA[2][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[2][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0029:    // tOverlapLoadCfg.alDistanceCurveA[2][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[2][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002A:    // tOverlapLoadCfg.alDistanceCurveA[3][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[3][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002B:    // tOverlapLoadCfg.alDistanceCurveA[3][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[3][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002C:    // tOverlapLoadCfg.afCurveALineAngleOffset[0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveALineAngleOffset[0] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002D:    // tOverlapLoadCfg.afCurveALineAngleOffset[1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveALineAngleOffset[1] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002E:    // tOverlapLoadCfg.afCurveALineAngleOffset[2]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveALineAngleOffset[2] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002F:    // tOverlapLoadCfg.afCurveALineAngleOffset[3]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveALineAngleOffset[3] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0030:    // tOverlapLoadCfg.alDistanceCurveB[0][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[0][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0031:    // tOverlapLoadCfg.alDistanceCurveB[0][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[0][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0032:    // tOverlapLoadCfg.alDistanceCurveB[1][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[1][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0033:    // tOverlapLoadCfg.alDistanceCurveB[1][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[1][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0034:    // tOverlapLoadCfg.alDistanceCurveB[2][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[2][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0035:    // tOverlapLoadCfg.alDistanceCurveB[2][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[2][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0036:    // tOverlapLoadCfg.alDistanceCurveB[3][0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[3][0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0037:    // tOverlapLoadCfg.alDistanceCurveB[3][1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[3][1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0038:    // tOverlapLoadCfg.afCurveBLineAngleOffset[0]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveBLineAngleOffset[0] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0039:    // tOverlapLoadCfg.afCurveBLineAngleOffset[1]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveBLineAngleOffset[1] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003A:    // tOverlapLoadCfg.afCurveBLineAngleOffset[2]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveBLineAngleOffset[2] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003B:    // tOverlapLoadCfg.afCurveBLineAngleOffset[3]
    {
        a_ptAVM2D_Cfg->tOverlapLoadCfg.afCurveBLineAngleOffset[3] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
  
    default:    // Do nothing
        DEBUG_Printf("Invalid Data ID: 0x%X\n - AVM2DCfgImport\n", a_ulDataID);
    break;
    }
}

UINT32 alAVM2D_CfgExportByHexData(
    UINT32 a_ulSectionID,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT8 ucNullFlag = 0;
    UINT32 ulElementID = 0x0000;
    INT32 lView = 0, lIndex = 0;


    UINT32 *pulDataSectionBuffer = (UINT32 *)a_pucDataSectionBuffer;

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    //  ucFunctionEnabled
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptalAVM2D_Cfg->ucFunctionEnabled, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  ulBVMaxDistance
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptalAVM2D_Cfg->ulBVMaxDistance, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  ulBVBlindDistanceFront
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptalAVM2D_Cfg->ulBVBlindDistanceFront, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  ulBVBlindDistanceBack
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptalAVM2D_Cfg->ulBVBlindDistanceBack, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  ulBVBlindDistanceLeft
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptalAVM2D_Cfg->ulBVBlindDistanceLeft, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  ulBVBlindDistanceRight
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptalAVM2D_Cfg->ulBVBlindDistanceRight, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tDestStartPoint.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tDestStartPoint.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tDestStartPoint.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tDestStartPoint.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tDestImageBufferSize.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tDestImageBufferSize.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tDestImageBufferSize.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tDestImageBufferSize.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  ucStitchLineType
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptalAVM2D_Cfg->ucStitchLineType, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIPixelNumber.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIPixelNumber.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIPixelNumber.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIPixelNumber.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIPixelOffset.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIPixelOffset.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIPixelOffset.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIPixelOffset.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIFrontLeftOffse2CarPict.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIFrontLeftOffse2CarPict.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIFrontLeftOffse2CarPict.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIFrontRightOffse2CarPict.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIFrontRightOffse2CarPict.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIFrontRightOffse2CarPict.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIRearLeftOffse2CarPict.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIRearLeftOffse2CarPict.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIRearLeftOffse2CarPict.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIRearRightOffse2CarPict.lX
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  tBVGAE_ROIRearRightOffse2CarPict.lY
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tBVGAE_ROIRearRightOffse2CarPict.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    //  fStitchAngleRange
    ulDataID = (a_ulSectionID << 16) + ulElementID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptalAVM2D_Cfg->fStitchAngleRange, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;
    ulElementID++;

    // afStitchLineAngle
    for (lView = 0; lView < 4; lView++)
    {
        ulDataID = (a_ulSectionID << 16) + ulElementID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptalAVM2D_Cfg->afStitchLineAngle[lView], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;
        ulElementID++;
    }

    // atStitchLineStart
    for (lView = 0; lView < 4; lView++)
    {
        ulDataID = (a_ulSectionID << 16) + ulElementID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->atStitchLineStart[lView].lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;
        ulElementID++;

        ulDataID = (a_ulSectionID << 16) + ulElementID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->atStitchLineStart[lView].lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;
        ulElementID++;
    }

    // tOverlapLoadCfg.alDistanceCurveA
    for (lView = 0; lView < 4; lView++)
    {
        for (lIndex = 0; lIndex < 2; lIndex++)
        {
            ulDataID = (a_ulSectionID << 16) + ulElementID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveA[lView][lIndex], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;
            ulElementID++;
        }
    }

    // tOverlapLoadCfg.afCurveALineAngleOffset
    for (lView = 0; lView < 4; lView++)
    {
        ulDataID = (a_ulSectionID << 16) + ulElementID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptalAVM2D_Cfg->tOverlapLoadCfg.afCurveALineAngleOffset[lView], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;
        ulElementID++;
    }

    // tOverlapLoadCfg.alDistanceCurveB
    for (lView = 0; lView < 4; lView++)
    {
        for (lIndex = 0; lIndex < 2; lIndex++)
        {
            ulDataID = (a_ulSectionID << 16) + ulElementID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptalAVM2D_Cfg->tOverlapLoadCfg.alDistanceCurveB[lView][lIndex], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;
            ulElementID++;
        }
    }
   
    // tOverlapLoadCfg.afCurveBLineAngleOffset
    for (lView = 0; lView < 4; lView++)
    {
        ulDataID = (a_ulSectionID << 16) + ulElementID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptalAVM2D_Cfg->tOverlapLoadCfg.afCurveBLineAngleOffset[lView], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;
        ulElementID++;
    }

    return ulSectionBufLen;
}

