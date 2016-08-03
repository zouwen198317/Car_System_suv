
#include "AVM3DM33Generation.h"
#include <math.h>
#include <string.h>
#include <assert.h>
#include "basedef.h"
#include "alMatrix.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_MatrixGeneratorStep1(AVM3DGenerateParams * a_ptAVM3DParam, FLOAT64 * a_peM33)
{

    /*
        World Coordinator : a_ptAVM3DParam->eDestPlaneOriginX, Y, Z 定義之位置為原點，向camera右方為正X，向camera後方為正Y，向camera下方為正Z
        Virtual Camera Coordinator = World Coordinator

    */

    FLOAT64 eDestCustomRollAngle;
    FLOAT64 peRotatCustomRoll[16]; 
    FLOAT64 eDestPitchAngle, eDestYawAngle, eDestRollAngle;
    FLOAT64 peRotatCustomX[16], peRotatCustomY[16], peRotatCustomZ[16]; 
    FLOAT64 peTranslationCustom[16];
    FLOAT64 peTmpMtx1[16];
    FLOAT64 peTmpMtx2[16];

    // 將虛擬相機旋轉一個角度
    eDestCustomRollAngle = a_ptAVM3DParam->eCameraCustomRoll * alPI / 180;
    peRotatCustomRoll[0] = cos(eDestCustomRollAngle);                 peRotatCustomRoll[1] = -sin(eDestCustomRollAngle);                peRotatCustomRoll[2] = 0;                            peRotatCustomRoll[3] = 0;
    peRotatCustomRoll[4] = sin(eDestCustomRollAngle);                 peRotatCustomRoll[5] = cos(eDestCustomRollAngle);                 peRotatCustomRoll[6] = 0;                            peRotatCustomRoll[7] = 0;
    peRotatCustomRoll[8] = 0;                                   peRotatCustomRoll[9] = 0;                                   peRotatCustomRoll[10] = 1;                           peRotatCustomRoll[11] = 0;
    peRotatCustomRoll[12] = 0;                                  peRotatCustomRoll[13] = 0;                                  peRotatCustomRoll[14] = 0;                           peRotatCustomRoll[15] = 1;

    // 將虛擬相機視角從 設定角度 旋轉 至 BV 角度
    eDestPitchAngle = a_ptAVM3DParam->eDestPitchAngle * alPI / 180;
    eDestYawAngle = a_ptAVM3DParam->eDestYawAngle * alPI / 180;
    eDestRollAngle = a_ptAVM3DParam->eDestRollAngle * alPI / 180;
    peRotatCustomX[0] = 1;                                   peRotatCustomX[1] = 0;                                   peRotatCustomX[2] = 0;                            peRotatCustomX[3] = 0;
    peRotatCustomX[4] = 0;                                   peRotatCustomX[5] = cos(eDestPitchAngle);                peRotatCustomX[6] = - sin(eDestPitchAngle);       peRotatCustomX[7] = 0;
    peRotatCustomX[8] = 0;                                   peRotatCustomX[9] = sin(eDestPitchAngle);                peRotatCustomX[10] = cos(eDestPitchAngle);        peRotatCustomX[11] = 0;
    peRotatCustomX[12] = 0;                                  peRotatCustomX[13] = 0;                                  peRotatCustomX[14] = 0;                           peRotatCustomX[15] = 1;

    peRotatCustomY[0] = cos(eDestYawAngle);                  peRotatCustomY[1] = 0;                                   peRotatCustomY[2] = sin(eDestYawAngle);           peRotatCustomY[3] = 0;
    peRotatCustomY[4] = 0;                                   peRotatCustomY[5] = 1;                                   peRotatCustomY[6] = 0;                            peRotatCustomY[7] = 0;
    peRotatCustomY[8] = -sin(eDestYawAngle);                 peRotatCustomY[9] = 0;                                   peRotatCustomY[10] = cos(eDestYawAngle);          peRotatCustomY[11] = 0;
    peRotatCustomY[12] = 0;                                   peRotatCustomY[13] = 0;                                  peRotatCustomY[14] = 0;                          peRotatCustomY[15] = 1;

    peRotatCustomZ[0] = cos(eDestRollAngle);                 peRotatCustomZ[1] = -sin(eDestRollAngle);                peRotatCustomZ[2] = 0;                            peRotatCustomZ[3] = 0;
    peRotatCustomZ[4] = sin(eDestRollAngle);                 peRotatCustomZ[5] = cos(eDestRollAngle);                 peRotatCustomZ[6] = 0;                            peRotatCustomZ[7] = 0;
    peRotatCustomZ[8] = 0;                                   peRotatCustomZ[9] = 0;                                   peRotatCustomZ[10] = 1;                           peRotatCustomZ[11] = 0;
    peRotatCustomZ[12] = 0;                                  peRotatCustomZ[13] = 0;                                  peRotatCustomZ[14] = 0;                           peRotatCustomZ[15] = 1;

    alMATRIX_Multiplaction(peRotatCustomZ, peRotatCustomRoll, 4, 4, 4, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCustomY, peTmpMtx1, 4, 4, 4, peTmpMtx2);
    alMATRIX_Multiplaction(peRotatCustomX, peTmpMtx2, 4, 4, 4, peTmpMtx1);

    // 將虛擬相機由設計位置移到車中心位置
    peTranslationCustom[0] = 1;     peTranslationCustom[1] = 0;     peTranslationCustom[2] = 0;     peTranslationCustom[3] = - a_ptAVM3DParam->lRealCameraX + a_ptAVM3DParam->lVitrualCameraX;                    
    peTranslationCustom[4] = 0;     peTranslationCustom[5] = 1;     peTranslationCustom[6] = 0;     peTranslationCustom[7] = - a_ptAVM3DParam->lRealCameraY + a_ptAVM3DParam->lVitrualCameraY;                    
    peTranslationCustom[8] = 0;     peTranslationCustom[9] = 0;     peTranslationCustom[10] = 1;    peTranslationCustom[11] = - a_ptAVM3DParam->lRealCameraZ + a_ptAVM3DParam->lVitrualCameraZ;
    peTranslationCustom[12] = 0;    peTranslationCustom[13] = 0;    peTranslationCustom[14] = 0;    peTranslationCustom[15] = 1;

    alMATRIX_Multiplaction(peTranslationCustom, peTmpMtx1, 4, 4, 4, peTmpMtx2);

    memcpy(a_peM33, peTmpMtx2, 16 * sizeof(FLOAT64));
}

void AVM3D_MatrixGeneratorBVTransform(alAVM3D_CfgSingleView * a_ptAVMCfg, FLOAT64 *a_peRT4x4)
{
	FLOAT64 eCameraPitchAngle, eCameraYawAngle, eCameraRollAngle;
    FLOAT64 eCameraCustomRoll;
    FLOAT64 peRotatCorrect[16]; 
    FLOAT64 peRotatCorrectX[16], peRotatCorrectY[16], peRotatCorrectZ[16]; 
    FLOAT64 peRotatCameraRoll[16];
    FLOAT64 peTranslationCustom[16];
    FLOAT64 peTmpMtx1[16];
    FLOAT64 peTmpMtx2[16];

    // 將虛擬相機由車中央的位置移到實體相機位置
	peTranslationCustom[0] = 1;     peTranslationCustom[1] = 0;     peTranslationCustom[2] = 0;     peTranslationCustom[3] = -a_ptAVMCfg->lTopViewPosX;                    
	peTranslationCustom[4] = 0;     peTranslationCustom[5] = 1;     peTranslationCustom[6] = 0;     peTranslationCustom[7] = -a_ptAVMCfg->lTopViewPosY;                    
	peTranslationCustom[8] = 0;     peTranslationCustom[9] = 0;     peTranslationCustom[10] = 1;    peTranslationCustom[11] = -a_ptAVMCfg->lTopViewPosZ;
    peTranslationCustom[12] = 0;     peTranslationCustom[13] = 0;   peTranslationCustom[14] = 0;    peTranslationCustom[15] = 1;
  
    // 將虛擬相機的 Roll 角度旋轉至實體相機的 Roll 角度
	eCameraCustomRoll = a_ptAVMCfg->fTopViewCustomRoll * alPI / 180;
    peRotatCameraRoll[0] = cos(eCameraCustomRoll);           peRotatCameraRoll[1] = -sin(eCameraCustomRoll);          peRotatCameraRoll[2] = 0;         peRotatCameraRoll[3] = 0;
    peRotatCameraRoll[4] = sin(eCameraCustomRoll);           peRotatCameraRoll[5] = cos(eCameraCustomRoll);           peRotatCameraRoll[6] = 0;         peRotatCameraRoll[7] = 0;
    peRotatCameraRoll[8] = 0;                                peRotatCameraRoll[9] = 0;                                peRotatCameraRoll[10] = 1;        peRotatCameraRoll[11] = 0;
    peRotatCameraRoll[12] = 0;                               peRotatCameraRoll[13] = 0;                               peRotatCameraRoll[14] = 0;        peRotatCameraRoll[15] = 1;

    // 將虛擬相機視角從 BV 角度旋轉至 實體相機角度
	eCameraPitchAngle = a_ptAVMCfg->fTopViewPitch * alPI / 180;
	eCameraYawAngle = a_ptAVMCfg->fTopViewYaw * alPI / 180;
	eCameraRollAngle = a_ptAVMCfg->fTopViewRoll * alPI / 180;

    peRotatCorrectX[0] = 1;                                  peRotatCorrectX[1] = 0;                                  peRotatCorrectX[2] = 0;                               peRotatCorrectX[3] = 0;
    peRotatCorrectX[4] = 0;                                  peRotatCorrectX[5] = cos(eCameraPitchAngle);             peRotatCorrectX[6] = - sin(eCameraPitchAngle);        peRotatCorrectX[7] = 0;
    peRotatCorrectX[8] = 0;                                  peRotatCorrectX[9] = sin(eCameraPitchAngle);             peRotatCorrectX[10] = cos(eCameraPitchAngle);         peRotatCorrectX[11] = 0;
    peRotatCorrectX[12] = 0;                                 peRotatCorrectX[13] = 0;                                 peRotatCorrectX[14] = 0;                              peRotatCorrectX[15] = 1;

    peRotatCorrectY[0] = cos(eCameraYawAngle);               peRotatCorrectY[1] = 0;                                  peRotatCorrectY[2] = sin(eCameraYawAngle);            peRotatCorrectY[3] = 0;
    peRotatCorrectY[4] = 0;                                  peRotatCorrectY[5] = 1;                                  peRotatCorrectY[6] = 0;                               peRotatCorrectY[7] = 0;
    peRotatCorrectY[8] = -sin(eCameraYawAngle);              peRotatCorrectY[9] = 0;                                  peRotatCorrectY[10] = cos(eCameraYawAngle);           peRotatCorrectY[11] = 0;
    peRotatCorrectY[12] = 0;                                 peRotatCorrectY[13] = 0;                                 peRotatCorrectY[14] = 0;                              peRotatCorrectY[15] = 1;

    peRotatCorrectZ[0] = cos(eCameraRollAngle);              peRotatCorrectZ[1] = -sin(eCameraRollAngle);             peRotatCorrectZ[2] = 0;                               peRotatCorrectZ[3] = 0;
    peRotatCorrectZ[4] = sin(eCameraRollAngle);              peRotatCorrectZ[5] = cos(eCameraRollAngle);              peRotatCorrectZ[6] = 0;                               peRotatCorrectZ[7] = 0;
    peRotatCorrectZ[8] = 0;                                  peRotatCorrectZ[9] = 0;                                  peRotatCorrectZ[10] = 1;                              peRotatCorrectZ[11] = 0;
    peRotatCorrectZ[12] = 0;                                 peRotatCorrectZ[13] = 0;                                 peRotatCorrectZ[14] = 0;                              peRotatCorrectZ[15] = 1;

    alMATRIX_Multiplaction(peRotatCorrectY, peRotatCorrectX, 4, 4, 4, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCorrectZ, peTmpMtx1, 4, 4, 4, peRotatCorrect);

    // Camera Custom Roll
    alMATRIX_Multiplaction(peRotatCameraRoll, peTranslationCustom, 4, 4, 4, peTmpMtx1);

    // Camera Correct
    alMATRIX_Multiplaction(peRotatCorrect, peTmpMtx1, 4, 4, 4, peTmpMtx2);

    memcpy(a_peRT4x4, peTmpMtx2, 16 * sizeof(FLOAT64));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_MatrixGeneratorStep2(AVM3DGenerateParams * a_ptAVM3DParam, FLOAT64 * a_peM33)
{

    /*
        World Coordinator : a_ptAVM3DParam->eDestPlaneOriginX, Y, Z 定義之位置為原點，向camera右方為正X，向camera後方為正Y，向camera下方為正Z
        Virtual Camera Coordinator = World Coordinator

    */

    FLOAT64 eCameraPitchAngle, eCameraYawAngle, eCameraRollAngle;
    FLOAT64 eCameraCustomRoll;
    FLOAT64 peRotatCorrect[16]; 
    FLOAT64 peRotatCorrectX[16], peRotatCorrectY[16], peRotatCorrectZ[16]; 
    FLOAT64 peRotatCameraRoll[16];
    FLOAT64 peTranslationCustom[16];
    //FLOAT64 peMc2i[9];
    FLOAT64 peTmpMtx1[16];
    FLOAT64 peTmpMtx2[16];

    // 將虛擬相機由車中央的位置移到實體相機位置
    peTranslationCustom[0] = 1;     peTranslationCustom[1] = 0;     peTranslationCustom[2] = 0;     peTranslationCustom[3] = - a_ptAVM3DParam->lRealCameraX + a_ptAVM3DParam->lVitrualCameraX;                    
    peTranslationCustom[4] = 0;     peTranslationCustom[5] = 1;     peTranslationCustom[6] = 0;     peTranslationCustom[7] = - a_ptAVM3DParam->lRealCameraY + a_ptAVM3DParam->lVitrualCameraY;                    
    peTranslationCustom[8] = 0;     peTranslationCustom[9] = 0;     peTranslationCustom[10] = 1;     peTranslationCustom[11] = - a_ptAVM3DParam->lRealCameraZ + a_ptAVM3DParam->lVitrualCameraZ;
    peTranslationCustom[12] = 0;     peTranslationCustom[13] = 0;     peTranslationCustom[14] = 0;     peTranslationCustom[15] = 1;
  
    // 將虛擬相機的 Roll 角度旋轉至實體相機的 Roll 角度
    eCameraCustomRoll = - a_ptAVM3DParam->eCameraCustomRoll * alPI / 180;
    peRotatCameraRoll[0] = cos(eCameraCustomRoll);           peRotatCameraRoll[1] = -sin(eCameraCustomRoll);          peRotatCameraRoll[2] = 0;         peRotatCameraRoll[3] = 0;
    peRotatCameraRoll[4] = sin(eCameraCustomRoll);           peRotatCameraRoll[5] = cos(eCameraCustomRoll);           peRotatCameraRoll[6] = 0;         peRotatCameraRoll[7] = 0;
    peRotatCameraRoll[8] = 0;                                peRotatCameraRoll[9] = 0;                                peRotatCameraRoll[10] = 1;        peRotatCameraRoll[11] = 0;
    peRotatCameraRoll[12] = 0;                               peRotatCameraRoll[13] = 0;                               peRotatCameraRoll[14] = 0;        peRotatCameraRoll[15] = 1;

    // 將虛擬相機視角從 BV 角度旋轉至 實體相機角度
    eCameraPitchAngle = - a_ptAVM3DParam->eCameraPitchAngle * alPI / 180;
    eCameraYawAngle = - a_ptAVM3DParam->eCameraYawAngle * alPI / 180;
    eCameraRollAngle = - a_ptAVM3DParam->eCameraRollAngle * alPI / 180;

    peRotatCorrectX[0] = 1;                                  peRotatCorrectX[1] = 0;                                  peRotatCorrectX[2] = 0;                               peRotatCorrectX[3] = 0;
    peRotatCorrectX[4] = 0;                                  peRotatCorrectX[5] = cos(eCameraPitchAngle);             peRotatCorrectX[6] = - sin(eCameraPitchAngle);        peRotatCorrectX[7] = 0;
    peRotatCorrectX[8] = 0;                                  peRotatCorrectX[9] = sin(eCameraPitchAngle);             peRotatCorrectX[10] = cos(eCameraPitchAngle);         peRotatCorrectX[11] = 0;
    peRotatCorrectX[12] = 0;                                 peRotatCorrectX[13] = 0;                                 peRotatCorrectX[14] = 0;                              peRotatCorrectX[15] = 1;

    peRotatCorrectY[0] = cos(eCameraYawAngle);               peRotatCorrectY[1] = 0;                                  peRotatCorrectY[2] = sin(eCameraYawAngle);            peRotatCorrectY[3] = 0;
    peRotatCorrectY[4] = 0;                                  peRotatCorrectY[5] = 1;                                  peRotatCorrectY[6] = 0;                               peRotatCorrectY[7] = 0;
    peRotatCorrectY[8] = -sin(eCameraYawAngle);              peRotatCorrectY[9] = 0;                                  peRotatCorrectY[10] = cos(eCameraYawAngle);           peRotatCorrectY[11] = 0;
    peRotatCorrectY[12] = 0;                                 peRotatCorrectY[13] = 0;                                 peRotatCorrectY[14] = 0;                              peRotatCorrectY[15] = 1;

    peRotatCorrectZ[0] = cos(eCameraRollAngle);              peRotatCorrectZ[1] = -sin(eCameraRollAngle);             peRotatCorrectZ[2] = 0;                               peRotatCorrectZ[3] = 0;
    peRotatCorrectZ[4] = sin(eCameraRollAngle);              peRotatCorrectZ[5] = cos(eCameraRollAngle);              peRotatCorrectZ[6] = 0;                               peRotatCorrectZ[7] = 0;
    peRotatCorrectZ[8] = 0;                                  peRotatCorrectZ[9] = 0;                                  peRotatCorrectZ[10] = 1;                              peRotatCorrectZ[11] = 0;
    peRotatCorrectZ[12] = 0;                                 peRotatCorrectZ[13] = 0;                                 peRotatCorrectZ[14] = 0;                              peRotatCorrectZ[15] = 1;

    alMATRIX_Multiplaction(peRotatCorrectY, peRotatCorrectX, 4, 4, 4, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCorrectZ, peTmpMtx1, 4, 4, 4, peRotatCorrect);

#if 0
    // Custom Rotation 
    alMATRIX_Multiplaction(peRotatCustom, peMvi2vc, 3, 3, 3, peTmpMtx1);
#endif

    // Camera Custom Roll
    alMATRIX_Multiplaction(peRotatCameraRoll, peTranslationCustom, 4, 4, 4, peTmpMtx1);

    // Camera Correct
    alMATRIX_Multiplaction(peRotatCorrect, peTmpMtx1, 4, 4, 4, peTmpMtx2);

    memcpy(a_peM33, peTmpMtx2, 16 * sizeof(FLOAT64));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_MatrixGenerator(AVM3DGenerateParams * a_ptAVM3DParam, FLOAT64 * a_peM33)
{

    /*
        World Coordinator : a_ptAVM3DParam->eDestPlaneOriginX, Y, Z 定義之位置為原點，向camera右方為正X，向camera後方為正Y，向camera下方為正Z
        Virtual Camera Coordinator = World Coordinator

    */

    //UINT16 uwCenterRC_X, uwCenterRC_Y;
    //FLOAT64 eCenterVC_X, eCenterVC_Y;
    FLOAT64 eCameraPitchAngle, eCameraYawAngle, eCameraRollAngle;
    FLOAT64 eDestPitchAngle, eDestYawAngle, eDestRollAngle;
    FLOAT64 eCameraCustomRoll;
    //FLOAT64 peMvi2vc[12];
    FLOAT64 peRotatCustomX[9], peRotatCustomY[9], peRotatCustomZ[9]; 
    FLOAT64 peRotatCustom[12], peRotatCorrect[9]; 
    FLOAT64 peMbv2bvi[9], peMbvi2bv[12];
    FLOAT64 peRotatCorrectX[9], peRotatCorrectY[9], peRotatCorrectZ[9]; 
    FLOAT64 peRotatCameraRoll[9];
    FLOAT64 peTranslationCustom[12];
    //FLOAT64 peMc2i[9];
    FLOAT64 peTmpMtx1[12];
    FLOAT64 peTmpMtx2[12];

    //FLOAT64 eFocalLength_VirtualCamera_H, eFocalLength_RealCamera;
#if 0
    // 實體相機中心在影像平面座標的位置
    uwCenterRC_X = ((a_ptAVM3DParam->ulCameraPlaneWidth)>>1);
    uwCenterRC_Y = ((a_ptAVM3DParam->ulCameraPlaneHeight)>>1);

    // 虛擬相機中心的位置
    eCenterVC_X = ((a_ptAVM3DParam->ulDestPlaneWidth)>>1);
    eCenterVC_Y = ((a_ptAVM3DParam->ulDestPlaneHeight)>>1);

    // 將 virtual camera 座標系統(3D) 轉換到 真實影像座標系統(2D)
    eFocalLength_VirtualCamera_H = (a_ptAVM3DParam->ulDestPlaneWidth) 
        / (2 * tan(a_ptAVM3DParam->eVCCameraFOV_H * alPI / 180 / 2)); 

    // 將 virtual camera 座標系統(3D) 轉換到 真實影像座標系統(2D) : 透視矩陣 + 平移矩陣(加在最後一個 column)
    peMvi2vc[0] = a_ptAVM3DParam->eMilimeterPerPixel_X;  peMvi2vc[1] = 0;                                     peMvi2vc[2] = - eCenterVC_X * a_ptAVM3DParam->eMilimeterPerPixel_X;                    
    peMvi2vc[3] = 0;                                   peMvi2vc[4] = a_ptAVM3DParam->eMilimeterPerPixel_Y;    peMvi2vc[5] = - eCenterVC_Y * a_ptAVM3DParam->eMilimeterPerPixel_Y;                    
    peMvi2vc[6] = 0;                                   peMvi2vc[7] = 0;                                     peMvi2vc[8] = eFocalLength_VirtualCamera_H * a_ptAVM3DParam->eMilimeterPerPixel_Y;
    //peMvi2vc[9] = 0;                                   peMvi2vc[10] = 0;                                    peMvi2vc[11] = 1;
#endif

    // 將虛擬相機視角從 設定角度 旋轉 至 BV 角度
    eDestPitchAngle = a_ptAVM3DParam->eDestPitchAngle * alPI / 180;
    eDestYawAngle = a_ptAVM3DParam->eDestYawAngle * alPI / 180;
    eDestRollAngle = a_ptAVM3DParam->eDestRollAngle * alPI / 180;
    peRotatCustomX[0] = 1;                                   peRotatCustomX[1] = 0;                                   peRotatCustomX[2] = 0;
    peRotatCustomX[3] = 0;                                   peRotatCustomX[4] = cos(eDestPitchAngle);                peRotatCustomX[5] = - sin(eDestPitchAngle);
    peRotatCustomX[6] = 0;                                   peRotatCustomX[7] = sin(eDestPitchAngle);                peRotatCustomX[8] = cos(eDestPitchAngle);

    peRotatCustomY[0] = cos(eDestYawAngle);                  peRotatCustomY[1] = 0;                                   peRotatCustomY[2] = sin(eDestYawAngle);
    peRotatCustomY[3] = 0;                                   peRotatCustomY[4] = 1;                                   peRotatCustomY[5] = 0;
    peRotatCustomY[6] = -sin(eDestYawAngle);                 peRotatCustomY[7] = 0;                                   peRotatCustomY[8] = cos(eDestYawAngle);

    peRotatCustomZ[0] = cos(eDestRollAngle);                 peRotatCustomZ[1] = -sin(eDestRollAngle);                peRotatCustomZ[2] = 0;
    peRotatCustomZ[3] = sin(eDestRollAngle);                 peRotatCustomZ[4] = cos(eDestRollAngle);                 peRotatCustomZ[5] = 0;
    peRotatCustomZ[6] = 0;                                   peRotatCustomZ[7] = 0;                                   peRotatCustomZ[8] = 1;

    alMATRIX_Multiplaction(peRotatCustomY, peRotatCustomZ, 3, 3, 3, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCustomX, peTmpMtx1, 3, 3, 3, peRotatCustom);

    // 世界座標系統 (3D, mm) => BV 平面 (2D, mm)
    peMbv2bvi[0] = - a_ptAVM3DParam->lVitrualCameraZ;       peMbv2bvi[1] = 0;                                       peMbv2bvi[2] = 0;
    peMbv2bvi[3] = 0;                                       peMbv2bvi[4] = - a_ptAVM3DParam->lVitrualCameraZ;       peMbv2bvi[5] = 0;
    peMbv2bvi[6] = 0;                                       peMbv2bvi[7] = 0;                                       peMbv2bvi[8] = 1;

    // BV 平面 (2D, mm) => 世界座標系統 (3D, mm), (3D座標被移動到BV平面位置)
    peMbvi2bv[0] = 1;               peMbvi2bv[1] = 0;               peMbvi2bv[2] = 0;                    
    peMbvi2bv[3] = 0;               peMbvi2bv[4] = 1;               peMbvi2bv[5] = 0;                    
    peMbvi2bv[6] = 0;               peMbvi2bv[7] = 0;               peMbvi2bv[8] = - a_ptAVM3DParam->lVitrualCameraZ;
    peMbvi2bv[9] = 0;               peMbvi2bv[10] = 0;              peMbvi2bv[11] = 1;

    // 將虛擬相機由車中央的位置移到實體相機位置
    peTranslationCustom[0] = 1;     peTranslationCustom[1] = 0;     peTranslationCustom[2] = 0;     peTranslationCustom[3] = - a_ptAVM3DParam->lRealCameraX + a_ptAVM3DParam->lVitrualCameraX;                    
    peTranslationCustom[4] = 0;     peTranslationCustom[5] = 1;     peTranslationCustom[6] = 0;     peTranslationCustom[7] = - a_ptAVM3DParam->lRealCameraY + a_ptAVM3DParam->lVitrualCameraY;                    
    peTranslationCustom[8] = 0;     peTranslationCustom[9] = 0;     peTranslationCustom[10] = 1;     peTranslationCustom[11] = - a_ptAVM3DParam->lRealCameraZ + a_ptAVM3DParam->lVitrualCameraZ;
    
    // 將虛擬相機的 Roll 角度旋轉至實體相機的 Roll 角度
    eCameraCustomRoll = - a_ptAVM3DParam->eCameraCustomRoll * alPI / 180;
    peRotatCameraRoll[0] = cos(eCameraCustomRoll);           peRotatCameraRoll[1] = -sin(eCameraCustomRoll);          peRotatCameraRoll[2] = 0;
    peRotatCameraRoll[3] = sin(eCameraCustomRoll);           peRotatCameraRoll[4] = cos(eCameraCustomRoll);           peRotatCameraRoll[5] = 0;
    peRotatCameraRoll[6] = 0;                                peRotatCameraRoll[7] = 0;                                peRotatCameraRoll[8] = 1;

    // 將虛擬相機視角從 BV 角度旋轉至 實體相機角度
    eCameraPitchAngle = - a_ptAVM3DParam->eCameraPitchAngle * alPI / 180;
    eCameraYawAngle = - a_ptAVM3DParam->eCameraYawAngle * alPI / 180;
    eCameraRollAngle = - a_ptAVM3DParam->eCameraRollAngle * alPI / 180;

    peRotatCorrectX[0] = 1;                                  peRotatCorrectX[1] = 0;                                  peRotatCorrectX[2] = 0;
    peRotatCorrectX[3] = 0;                                  peRotatCorrectX[4] = cos(eCameraPitchAngle);             peRotatCorrectX[5] = - sin(eCameraPitchAngle);
    peRotatCorrectX[6] = 0;                                  peRotatCorrectX[7] = sin(eCameraPitchAngle);             peRotatCorrectX[8] = cos(eCameraPitchAngle);

    peRotatCorrectY[0] = cos(eCameraYawAngle);               peRotatCorrectY[1] = 0;                                  peRotatCorrectY[2] = sin(eCameraYawAngle);
    peRotatCorrectY[3] = 0;                                  peRotatCorrectY[4] = 1;                                  peRotatCorrectY[5] = 0;
    peRotatCorrectY[6] = -sin(eCameraYawAngle);              peRotatCorrectY[7] = 0;                                  peRotatCorrectY[8] = cos(eCameraYawAngle);

    peRotatCorrectZ[0] = cos(eCameraRollAngle);              peRotatCorrectZ[1] = -sin(eCameraRollAngle);             peRotatCorrectZ[2] = 0;
    peRotatCorrectZ[3] = sin(eCameraRollAngle);              peRotatCorrectZ[4] = cos(eCameraRollAngle);              peRotatCorrectZ[5] = 0;
    peRotatCorrectZ[6] = 0;                                  peRotatCorrectZ[7] = 0;                                  peRotatCorrectZ[8] = 1;

    alMATRIX_Multiplaction(peRotatCorrectY, peRotatCorrectX, 3, 3, 3, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCorrectZ, peTmpMtx1, 3, 3, 3, peRotatCorrect);

    // 將 real camera 座標系統(3D) 轉換到 真實影像座標系統(2D)
#if 0
    // Calculate the focal length of real camera (under de-fisheye plane) => sensor width / 2 = f * tan(FOV_H/2)
    eFocalLength_RealCamera = (a_ptAVM3DParam->ulCameraPlaneWidth>>1) 
        / tan(a_ptAVM3DParam->eCameraFOV_H * alPI / 180 / 2); 

    peMc2i[0] = eFocalLength_RealCamera;     peMc2i[1] = 0;                           peMc2i[2] = uwCenterRC_X;
    peMc2i[3] = 0;                           peMc2i[4] = eFocalLength_RealCamera;     peMc2i[5] = uwCenterRC_Y;
    peMc2i[6] = 0;                           peMc2i[7] = 0;                           peMc2i[8] = 1;
#endif

#if 0
    // Custom Rotation 
    alMATRIX_Multiplaction(peRotatCustom, peMvi2vc, 3, 3, 3, peTmpMtx1);
#endif

    // BV 平面投影
    alMATRIX_Multiplaction(peMbv2bvi, peRotatCustom, 3, 3, 3, peTmpMtx2);
    alMATRIX_Multiplaction(peMbvi2bv, peTmpMtx2, 4, 3, 3, peTmpMtx1);

    // Translation
    alMATRIX_Multiplaction(peTranslationCustom, peTmpMtx1, 3, 4, 3, peTmpMtx2);

    // Camera Custom Roll
    alMATRIX_Multiplaction(peRotatCameraRoll, peTmpMtx2, 3, 3, 3, peTmpMtx1);

    // Camera Correct
    alMATRIX_Multiplaction(peRotatCorrect, peTmpMtx1, 3, 3, 3, peTmpMtx2);

#if 0
    // real camera to original plane
    alMATRIX_Multiplaction(peMc2i, peTmpMtx2, 3, 3, 3, peTmpMtx1);
#endif

    memcpy(a_peM33, peTmpMtx2, 9 * sizeof(FLOAT64));
}

void AVM3D_CoordinatesTransform3D_Batch(FLOAT64 a_aeM33[9], FLOAT64 * a_peSrcX, FLOAT64 * a_peSrcY, FLOAT64 * a_peSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ, UINT32 a_ulCount)
{
    UINT32 ulIndex;
    for(ulIndex = 0; ulIndex < a_ulCount; ulIndex++, a_peSrcX++, a_peSrcY++, a_peDestX++, a_peDestY++, a_peSrcZ++)
    {
        (*a_peDestX) = (a_aeM33[0] * (*a_peSrcX) + a_aeM33[1] * (*a_peSrcY) + a_aeM33[2] * (*a_peSrcZ));
        (*a_peDestY) = (a_aeM33[3] * (*a_peSrcX) + a_aeM33[4] * (*a_peSrcY) + a_aeM33[5] * (*a_peSrcZ));
        (*a_peDestZ) = (a_aeM33[6] * (*a_peSrcX) + a_aeM33[7] * (*a_peSrcY) + a_aeM33[8] * (*a_peSrcZ));
    }
}

void AVM3D_CoordinatesTransform3D(FLOAT64 a_aeM33[16], FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    FLOAT64 eS = (a_aeM33[12] * a_eSrcX + a_aeM33[13] * a_eSrcY + a_aeM33[14] * a_eSrcZ + a_aeM33[15] * 1);
    assert(eS == 1.0);

    (*a_peDestX) = (a_aeM33[0] * a_eSrcX + a_aeM33[1] * a_eSrcY + a_aeM33[2] * a_eSrcZ + a_aeM33[3] * 1);
    (*a_peDestY) = (a_aeM33[4] * a_eSrcX + a_aeM33[5] * a_eSrcY + a_aeM33[6] * a_eSrcZ + a_aeM33[7] * 1);
    (*a_peDestZ) = (a_aeM33[8] * a_eSrcX + a_aeM33[9] * a_eSrcY + a_aeM33[10] * a_eSrcZ + a_aeM33[11] * 1);
}
