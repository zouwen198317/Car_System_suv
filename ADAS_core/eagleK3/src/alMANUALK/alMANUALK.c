
#include <stdlib.h>
#include <math.h>
#include <assert.h>
// #include <string.h>
#include <time.h>
#include <stdio.h>
// #include <float.h>

#include "CommonK.h"
#include "alErrorCode.h"
#include "alMatrix.h"
#include "alMANUALK/alMANUALK.h"
#include "alMANUALK/alMANUALK_CalRefData.h"
#include "basedef.h"


#ifndef alROUND 
#define alROUND(a)    (INT32)(a > 0 ? (a+0.5) : (a-0.5))
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CAMK_VERIFY_CALIBRATION_LM 1
#define CAMK_VERIFY_CALIBRATION_FUNCTION 0
#define CAMK_MAX_FEATURE_NUMBER 20




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void BVFPTransform( FLOAT64 * peSrcFP_X, FLOAT64 * peSrcFP_Y, 
                           UINT8 ucNumPts, FLOAT64 * peM33, 
                           FLOAT64 * peDestFP_X, FLOAT64 * peDestFP_Y)
{
    UINT8 n;
	for ( n = 0 ; n < ucNumPts ; n++ )//count undistorted positions of feature points
	{
        COMMONK_PerformCoordinatesTransform(peM33, peSrcFP_X[n], peSrcFP_Y[n], peDestFP_X + n, peDestFP_Y + n);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Perform planar transform for RGB image */
void CAMK_GenerateSingleViewPlanarImage_RGB(UINT8 a_ucBVCameraIndx,
                                            UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
                                            UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
                                            FLOAT64 a_peM33[9],
                                            alFM_v2_1_Model *a_ptCameraFisheyeModel
                                            )
{
#if 0
    INT32 lSrcX, lSrcY, lDestX, lDestY;
    FLOAT64 eBVP_X, eBVP_Y, eSPP_X, eSPP_Y, eUDX, eUDY, eSrcX, eSrcY;
    //INT32 lRowIndex;
    UINT8 * pucDest;
    UINT8 * pucSrc;
    INT32 lYLimit = g_MANUALK_alOriImgYLimit[a_ucBVCameraIndx];

    alMANUALK_CameraCfg * ptCameraCfg = g_MANUALK_atCameraCurrentParam + a_ucBVCameraIndx;
    alFM_v2_1_Model * ptCameraFisheyeModel = a_ptCameraFisheyeModel + a_ucBVCameraIndx;

    for(lDestY = 0; lDestY < a_lDestHeight; lDestY++)
    {
        for(lDestX = 0; lDestX < a_lDestWidth; lDestX++)
        {
            pucDest = a_pucDestImage + (lDestX + lDestY * a_lDestWidth) * 3;

            eSPP_X = lDestX;
            eSPP_Y = lDestY;

            // 將座標重設為 bird view 上的位置
            //CAMK_SinglePlanarPoint2BirdViewPoint(a_ucBVCameraIndx, 1, &eSPP_X, &eSPP_Y, &eBVP_X, &eBVP_Y);
            eBVP_X = eSPP_X;
            eBVP_Y = eSPP_Y;
            // 計算反魚眼座標
            COMMONK_PerformCoordinatesTransform(a_peM33, eBVP_X, eBVP_Y, &eUDX, &eUDY);

            // 超過設定之 FOV 的座標點不列入計算
            //if(eUDX >= 0 && eUDX <= ptCameraFisheyeModel->uwDestWidth - 1 && eUDY >= 0 && eUDY <= ptCameraFisheyeModel->uwDestHeight - 1)
            if(eUDY >= lYLimit)
            {

                // 計算魚眼座標
                alFM_v2_1_Undistorted2Distorted_PlanarPixel(ptCameraFisheyeModel, eUDX, eUDY, &eSrcX, &eSrcY);

                lSrcX = alROUND(eSrcX);
                lSrcY = alROUND(eSrcY);
                
                if(lSrcX >= 0 && lSrcX < a_lSrcWidth && lSrcY >= 0 && lSrcY < a_lSrcHeight)
                {
                    pucSrc = a_pucSrcImage + (lSrcX + lSrcY * a_lSrcWidth) * 3;

                    memcpy(pucDest, pucSrc, 3 * sizeof(UINT8));

                    continue;
                }

            }

            // 超出範圍的座點，該位置的像素值填黑色
            memset(pucDest, 0, 3 * sizeof(UINT8));

        }
    }
#endif
}

void MANUALK_ResetYCoordinatesLimit(UINT8 a_ucCameraIndx, alCOMMONK_CommonCfg *a_ptCommonCfg, FLOAT32 a_fMMPP, FLOAT64 a_aeHomographyMatrix[2][9], INT32 *a_plOriImgYLimit)
{
    FLOAT64 eBVLimitX, eBVLimitY;
    FLOAT64 eOVLimitX, eOVLimitY;
    FLOAT64 eOVLimitY_0;
    INT32 lBVIndex;
    FLOAT32 fMMPP = a_fMMPP;


    ////
    // Calculate the Farest Point on Original Image
    for (lBVIndex = alMANUALK_FAREST_DISTANCE_SEARCH_FROM; lBVIndex < alMANUALK_FAREST_DISTANCE_SEARCH_END; lBVIndex += alMANUALK_FAREST_DISTANCE_SEARCH_STEP)
    {
        eBVLimitX = ( a_ptCommonCfg->tDisplayAreaSize.lX >> 1);
        eBVLimitY = ( a_ptCommonCfg->tDisplayAreaSize.lY >> 1) - (lBVIndex / fMMPP);
        COMMONK_PerformCoordinatesTransform(a_aeHomographyMatrix[0], eBVLimitX, eBVLimitY, &eOVLimitX, &eOVLimitY);
        if (lBVIndex == alMANUALK_FAREST_DISTANCE_SEARCH_FROM)
        {
            eOVLimitY_0 = eOVLimitY;
        }
        else
        {
            if (eOVLimitY < 0 || eOVLimitY > eOVLimitY_0)
            {
                eOVLimitY = 0;
                break;
            }
        }
    }
    *a_plOriImgYLimit = alMAX(0, (INT32)eOVLimitY);
    ////
}


void MANUALK_InitialByConfigData(
    alFM_v2_1_Model *a_ptFM_v2_Model,
    alCAMERAINFO_ExtrinsicParams a_atCameraExtrinsicParams[alMANUALK_NUM_BV_CHANNEL],
    alCOMMONK_CalibrationParams a_atCalibrationParams[alMANUALK_NUM_BV_CHANNEL],
    alPointINT32  a_atBVFPOffsetFineTuned[alMANUALK_NUM_BV_CHANNEL][alMANUALK_CAMERA_FP_NUM_AUTOK],
    alMANUALK_ChartCrossPointSet *a_ptManualKFieldData,
    alMANUALK_CameraCfg   a_atMANUALK_Cfg[alMANUALK_NUM_BV_CHANNEL],
    alPointINT32 a_talAVM2D_DestImageBufferSize,
    FLOAT32    a_fMMPP,
    alCOMMONK_CommonCfg *a_ptCommonCfg,
    alMANUALK_Params *a_ptParams
    )
{
    alMANUALK_ChartCrossPointSet tCurrentCrossPointSet;
    FLOAT32 fPPMM = 1.0f / a_fMMPP;

    // 以下四個參數以車輛左上角為原點，左負右正，上負下正。
    INT32 lCar_OffsetY_F = a_ptManualKFieldData->uwFWheeltoFChart - a_ptCommonCfg->ulFrontFixedPoint2Head;
    INT32 lCar_OffsetY_B = a_ptManualKFieldData->uwCharVertDistance - lCar_OffsetY_F;
    INT32 lCar_OffsetX_L = 0;
    INT32 lCar_OffsetX_R = a_ptManualKFieldData->uwChartHoriDistance - lCar_OffsetX_L;

    INT32 lBirdViewCenterPosX = (a_talAVM2D_DestImageBufferSize.lX >> 1);
    INT32 lBirdViewCenterPosY = (a_talAVM2D_DestImageBufferSize.lY >> 1);

    FLOAT64 eCarTopLeftPosX = lBirdViewCenterPosX - (a_ptCommonCfg->ulCarWidth >> 1) * fPPMM;
    FLOAT64 eCarTopLeftPosY = lBirdViewCenterPosY - (a_ptCommonCfg->ulCarLength >> 1) * fPPMM;


    // copy mmpp from alAVM2D modele
    a_ptParams->fMMPP = a_fMMPP;

    /*
    (左前)                      (右前)
    ______    lCar_OffsetX_R    ______
    |＋ ＋ |     ←─────→ | ＋ ＋|
    |   ＋ |                    | ＋   |
    |______| lCar_OffsetX_L     |______|
    ↑     ←→
    lCar_OffsetY_F ↓      (Top-left)
    ---------  ┌────┐
    ↑     ▕        ▕
    ∣     ▕        ▕
    ∣     ▕        ▕
    lCar_OffsetY_B ∣     ▕  CAR   ▕
    ∣     ▕        ▕
    ∣     ▕        ▕
    ∣     ▕        ▕
    -----∣---  └────┘
    ∣            (Bottom-right)
    ___↓_                     ______
    |   ＋ |(左後)             | ＋   |(右後)
    |＋ ＋ |                   | ＋ ＋|
    |______|                   |______|

    */

    /* Assumption : 車輛停放都是靠左側導軌，以及靠前輪定位點對齊， */
    tCurrentCrossPointSet.FW1 = a_ptManualKFieldData->FW1 + lCar_OffsetX_L;
    tCurrentCrossPointSet.FH1 = a_ptManualKFieldData->FH1 + lCar_OffsetY_F;
    tCurrentCrossPointSet.FW2 = a_ptManualKFieldData->FW2 + lCar_OffsetX_R;
    tCurrentCrossPointSet.FH2 = a_ptManualKFieldData->FH2 + lCar_OffsetY_F;
    tCurrentCrossPointSet.FW3 = a_ptManualKFieldData->FW3 + lCar_OffsetX_L;
    tCurrentCrossPointSet.FH3 = a_ptManualKFieldData->FH3 + lCar_OffsetY_F;
    tCurrentCrossPointSet.FW4 = a_ptManualKFieldData->FW4 + lCar_OffsetX_R;
    tCurrentCrossPointSet.FH4 = a_ptManualKFieldData->FH4 + lCar_OffsetY_F;
    tCurrentCrossPointSet.FW5 = a_ptManualKFieldData->FW5 + lCar_OffsetX_L;
    tCurrentCrossPointSet.FH5 = a_ptManualKFieldData->FH5 + lCar_OffsetY_F;
    tCurrentCrossPointSet.FW6 = a_ptManualKFieldData->FW6 + lCar_OffsetX_R;
    tCurrentCrossPointSet.FH6 = a_ptManualKFieldData->FH6 + lCar_OffsetY_F;
    tCurrentCrossPointSet.BW1 = a_ptManualKFieldData->BW1 + lCar_OffsetX_R;
    tCurrentCrossPointSet.BH1 = a_ptManualKFieldData->BH1 + lCar_OffsetY_B;
    tCurrentCrossPointSet.BW2 = a_ptManualKFieldData->BW2 + lCar_OffsetX_L;
    tCurrentCrossPointSet.BH2 = a_ptManualKFieldData->BH2 + lCar_OffsetY_B;
    tCurrentCrossPointSet.BW3 = a_ptManualKFieldData->BW3 + lCar_OffsetX_R;
    tCurrentCrossPointSet.BH3 = a_ptManualKFieldData->BH3 + lCar_OffsetY_B;
    tCurrentCrossPointSet.BW4 = a_ptManualKFieldData->BW4 + lCar_OffsetX_L;
    tCurrentCrossPointSet.BH4 = a_ptManualKFieldData->BH4 + lCar_OffsetY_B;
    tCurrentCrossPointSet.BW5 = a_ptManualKFieldData->BW5 + lCar_OffsetX_R;
    tCurrentCrossPointSet.BH5 = a_ptManualKFieldData->BH5 + lCar_OffsetY_B;
    tCurrentCrossPointSet.BW6 = a_ptManualKFieldData->BW6 + lCar_OffsetX_L;
    tCurrentCrossPointSet.BH6 = a_ptManualKFieldData->BH6 + lCar_OffsetY_B;

    tCurrentCrossPointSet.BW7 = a_ptManualKFieldData->BW7 + lCar_OffsetX_R;
    tCurrentCrossPointSet.BH7 = a_ptManualKFieldData->BH7 + lCar_OffsetY_B;
    tCurrentCrossPointSet.BW8 = a_ptManualKFieldData->BW8 + lCar_OffsetX_L;
    tCurrentCrossPointSet.BH8 = a_ptManualKFieldData->BH8 + lCar_OffsetY_B;

    // Front View
    /*

    ＋             ＋
    (2)            (3)

    ＋             ＋
    (0)            (1)

    */
    // a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_FRONT]
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_FRONT][0] = eCarTopLeftPosX - tCurrentCrossPointSet.FW1 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_FRONT][1] = eCarTopLeftPosX + tCurrentCrossPointSet.FW2 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_FRONT][2] = eCarTopLeftPosX - tCurrentCrossPointSet.FW3 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_FRONT][3] = eCarTopLeftPosX + tCurrentCrossPointSet.FW4 * fPPMM;

    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_FRONT][0] = eCarTopLeftPosY - tCurrentCrossPointSet.FH1 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_FRONT][1] = eCarTopLeftPosY - tCurrentCrossPointSet.FH2 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_FRONT][2] = eCarTopLeftPosY - tCurrentCrossPointSet.FH3 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_FRONT][3] = eCarTopLeftPosY - tCurrentCrossPointSet.FH4 * fPPMM;

    // Back View
    /*

    ＋             ＋
    (1)            (0)

    ＋             ＋
    (3)            (2)

    */
    // a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_BACK]
    // a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_BACK]
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_BACK][0] = eCarTopLeftPosX + tCurrentCrossPointSet.BW1 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_BACK][1] = eCarTopLeftPosX - tCurrentCrossPointSet.BW2 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_BACK][2] = eCarTopLeftPosX + tCurrentCrossPointSet.BW3 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_BACK][3] = eCarTopLeftPosX - tCurrentCrossPointSet.BW4 * fPPMM;

    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_BACK][0] = eCarTopLeftPosY + tCurrentCrossPointSet.BH1 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_BACK][1] = eCarTopLeftPosY + tCurrentCrossPointSet.BH2 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_BACK][2] = eCarTopLeftPosY + tCurrentCrossPointSet.BH3 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_BACK][3] = eCarTopLeftPosY + tCurrentCrossPointSet.BH4 * fPPMM;


    // Left View
    /*

    ＋
    (3)     ＋
    (1)

    ＋
    ＋      (0)
    (2)

    */
    // a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT]
    // a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT]
#if EAGLEK3_MANUALK_FP_MODE
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][0] = eCarTopLeftPosX - tCurrentCrossPointSet.BW2 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][1] = eCarTopLeftPosX - tCurrentCrossPointSet.FW1 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][2] = eCarTopLeftPosX - tCurrentCrossPointSet.BW8 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][3] = eCarTopLeftPosX - tCurrentCrossPointSet.FW5 * fPPMM;

    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][0] = eCarTopLeftPosY + tCurrentCrossPointSet.BH2 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][1] = eCarTopLeftPosY - tCurrentCrossPointSet.FH1 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][2] = eCarTopLeftPosY + tCurrentCrossPointSet.BH8 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][3] = eCarTopLeftPosY - tCurrentCrossPointSet.FH5 * fPPMM;
#else
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][0] = eCarTopLeftPosX - tCurrentCrossPointSet.BW2 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][1] = eCarTopLeftPosX - tCurrentCrossPointSet.FW1 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][2] = eCarTopLeftPosX - tCurrentCrossPointSet.BW6 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_LEFT][3] = eCarTopLeftPosX - tCurrentCrossPointSet.FW5 * fPPMM;

    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][0] = eCarTopLeftPosY + tCurrentCrossPointSet.BH2 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][1] = eCarTopLeftPosY - tCurrentCrossPointSet.FH1 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][2] = eCarTopLeftPosY + tCurrentCrossPointSet.BH6 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_LEFT][3] = eCarTopLeftPosY - tCurrentCrossPointSet.FH5 * fPPMM;
#endif

    // Right View
    /*

    ＋
    ＋     (2)
    (0)

    ＋
    (1)     ＋
    (3)

    */
#if EAGLEK3_MANUALK_FP_MODE
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][0] = eCarTopLeftPosX + tCurrentCrossPointSet.FW2 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][1] = eCarTopLeftPosX + tCurrentCrossPointSet.BW1 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][2] = eCarTopLeftPosX + tCurrentCrossPointSet.FW6 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][3] = eCarTopLeftPosX + tCurrentCrossPointSet.BW7 * fPPMM;

    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][0] = eCarTopLeftPosY - tCurrentCrossPointSet.FH2 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][1] = eCarTopLeftPosY + tCurrentCrossPointSet.BH1 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][2] = eCarTopLeftPosY - tCurrentCrossPointSet.FH6 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][3] = eCarTopLeftPosY + tCurrentCrossPointSet.BH7 * fPPMM;
#else
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][0] = eCarTopLeftPosX + tCurrentCrossPointSet.FW2 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][1] = eCarTopLeftPosX + tCurrentCrossPointSet.BW1 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][2] = eCarTopLeftPosX + tCurrentCrossPointSet.FW6 * fPPMM;
    a_ptParams->aeBVIdealFP_X[alCAMERAINFO_BV_RIGHT][3] = eCarTopLeftPosX + tCurrentCrossPointSet.BW5 * fPPMM;

    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][0] = eCarTopLeftPosY - tCurrentCrossPointSet.FH2 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][1] = eCarTopLeftPosY + tCurrentCrossPointSet.BH1 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][2] = eCarTopLeftPosY - tCurrentCrossPointSet.FH6 * fPPMM;
    a_ptParams->aeBVIdealFP_Y[alCAMERAINFO_BV_RIGHT][3] = eCarTopLeftPosY + tCurrentCrossPointSet.BH5 * fPPMM;
#endif

    // Get fine-tuned ideal FP
    {
        UINT8 ucCameraIndex = 0, ucFPIndex = 0;
        for (ucCameraIndex = 0; ucCameraIndex < alMANUALK_NUM_BV_CHANNEL; ucCameraIndex++)
        {
            for (ucFPIndex = 0; ucFPIndex < alMANUALK_CAMERA_FP_NUM; ucFPIndex++)
            {
                a_ptParams->aeBVFineTunedIdealFP_X[ucCameraIndex][ucFPIndex] = a_ptParams->aeBVIdealFP_X[ucCameraIndex][ucFPIndex] + a_atBVFPOffsetFineTuned[ucCameraIndex][ucFPIndex].lX * fPPMM;
                a_ptParams->aeBVFineTunedIdealFP_Y[ucCameraIndex][ucFPIndex] = a_ptParams->aeBVIdealFP_Y[ucCameraIndex][ucFPIndex] + a_atBVFPOffsetFineTuned[ucCameraIndex][ucFPIndex].lY * fPPMM;
            }
        }

    }
    
    // 重設 YLimit 數值
    MANUALK_ResetYCoordinatesLimit(
        alCAMERAINFO_BV_LEFT, a_ptCommonCfg, a_fMMPP,
        a_atCalibrationParams[alCAMERAINFO_BV_LEFT].aeHomographyMatrix,
        &a_ptParams->alOriImgYLimit[alCAMERAINFO_BV_LEFT]
    );

    MANUALK_ResetYCoordinatesLimit(
        alCAMERAINFO_BV_RIGHT, a_ptCommonCfg, a_fMMPP,
        a_atCalibrationParams[alCAMERAINFO_BV_RIGHT].aeHomographyMatrix,
        &a_ptParams->alOriImgYLimit[alCAMERAINFO_BV_RIGHT]
        );

    MANUALK_ResetYCoordinatesLimit(
        alCAMERAINFO_BV_FRONT, a_ptCommonCfg, a_fMMPP,
        a_atCalibrationParams[alCAMERAINFO_BV_FRONT].aeHomographyMatrix,
        &a_ptParams->alOriImgYLimit[alCAMERAINFO_BV_FRONT]
        );

    MANUALK_ResetYCoordinatesLimit(
        alCAMERAINFO_BV_BACK, a_ptCommonCfg, a_fMMPP,
        a_atCalibrationParams[alCAMERAINFO_BV_BACK].aeHomographyMatrix,
        &a_ptParams->alOriImgYLimit[alCAMERAINFO_BV_BACK]
        );

    // FM
    a_ptParams->a_aptFM_v2_Model[alCAMERAINFO_BV_LEFT] = &a_ptFM_v2_Model[alCAMERAINFO_BV_LEFT];
    a_ptParams->a_aptFM_v2_Model[alCAMERAINFO_BV_RIGHT] = &a_ptFM_v2_Model[alCAMERAINFO_BV_RIGHT];
    a_ptParams->a_aptFM_v2_Model[alCAMERAINFO_BV_FRONT] = &a_ptFM_v2_Model[alCAMERAINFO_BV_FRONT];
    a_ptParams->a_aptFM_v2_Model[alCAMERAINFO_BV_BACK] = &a_ptFM_v2_Model[alCAMERAINFO_BV_BACK];
    

    // 指定在BV上的旋轉角度
    a_ptParams->alCamAngle[alCAMERAINFO_BV_LEFT] = alBVCAM_FACAUTOK_BV_LEFT;
    a_ptParams->alCamAngle[alCAMERAINFO_BV_RIGHT] = alBVCAM_FACAUTOK_BV_RIGHT;
    a_ptParams->alCamAngle[alCAMERAINFO_BV_FRONT] = alBVCAM_FACAUTOK_BV_FRONT;
    a_ptParams->alCamAngle[alCAMERAINFO_BV_BACK] = alBVCAM_FACAUTOK_BV_BACK;

}



void MANUALK_SingleViewForCalibration(
    UINT8 a_ucCameraIndex, UINT8 * a_pucSrcBuffer, UINT8 * a_ucDestBuffer, 
    alFM_v2_1_Model *a_ptCameraFisheyeModel, alMANUALK_CameraCfg a_atMANUALK_Cfg[alMANUALK_NUM_BV_CHANNEL],
    alMANUALK_Params *a_ptMANUALK_Params, alCAMERAINFO_ExtrinsicParams *a_ptCAMParams,
    alCOMMONK_CalibrationParams *a_ptCalibrationParams
)
{
    INT32 lSrcWidth = 0, lSrcHeight = 0;
    INT32 lDestWidth = 0, lDestHeight = 0;

    lSrcWidth = a_atMANUALK_Cfg[a_ucCameraIndex].ulImageWidth;
    lSrcHeight = a_atMANUALK_Cfg[a_ucCameraIndex].ulImageHeight;
    lDestWidth = a_atMANUALK_Cfg[a_ucCameraIndex].tSBV_Setting.lImageWidth;
    lDestHeight = a_atMANUALK_Cfg[a_ucCameraIndex].tSBV_Setting.lImageHeight;  


    COMMONK_SBVGenerate_YUYV_FULL(
        a_pucSrcBuffer, lSrcWidth, lSrcHeight,
        a_ucDestBuffer, lDestWidth, lDestHeight,
        a_ptCalibrationParams->aeHomographyMatrix[0],
        a_ptMANUALK_Params->alOriImgYLimit[a_ucCameraIndex],
        a_ptMANUALK_Params->alCamAngle[a_ucCameraIndex], a_ptCAMParams->lCameraPosX, a_ptCAMParams->lCameraPosY,
        a_atMANUALK_Cfg[a_ucCameraIndex].tSBV_Setting.lDisplayOffset_X,
        a_atMANUALK_Cfg[a_ucCameraIndex].tSBV_Setting.lDisplayOffset_Y,
        a_atMANUALK_Cfg[a_ucCameraIndex].tSBV_Setting.fScaleFactor,
        a_ptMANUALK_Params->fMMPP,
        a_ptMANUALK_Params->a_aptFM_v2_Model[a_ucCameraIndex]
    );
}

