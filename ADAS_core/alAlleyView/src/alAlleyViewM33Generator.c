
#include "alAlleyViewM33Generator.h"

#include <math.h>
#include <string.h>
#include <assert.h>

#include "basedef.h"
#include "alMatrix.h"

// Added by Chinson - 20130531: 增加是否啟用 Yaw 修正的 Flag
#define YawKOnOff 1

/** 
    \brief To generate the alley view perspective matrix according to the input parameters (a_ptAVParams). The output type of matrix is FLOAT64. 
           The input for M3x3 is in pixel on real camera and output is in pixel on destination plane.
    \param a_ptAVParams [IN] Define the space relation between real camera and virtual camera.
    \param a_peM33 [OUT] Output the generated matrix.
*/
void alAlleyViewM33Generator(alAlleyViewParams * a_ptAVParams, FLOAT64 * a_peM33)
{

    /*
        World Coordinator : pPTParams->eDestPlaneOriginX, Y, Z 定義之位置為原點，向camera右方為正X，向camera後方為正Y，向camera下方為正Z
        Virtual Camera Coordinator = World Coordinator

    */

    UINT16 uwCenterRC_X, uwCenterRC_Y;
    INT32 lCenterVC_X, lCenterVC_Y;
    FLOAT64 peMvi2vc[9];
    FLOAT64 eFocalLength_VirtualCamera_H, eFocalLength_RealCamera;
#if 0
    FLOAT64 eCameraPitchAngle, eCameraYawAngle, eCameraRollAngle;
    FLOAT64 peRotatCorrectX[9], peRotatCorrectY[9], peRotatCorrectZ[9];
#endif
    FLOAT64 peRotatAntiCorrectY[9];
    FLOAT64 eDestPitchAngle, eDestYawAngle, eDestRollAngle;
    FLOAT64 peRotatCustomX[9], peRotatCustomY[9], peRotatCustomZ[9]; 
    FLOAT64 peMc2i[9];
    FLOAT64 peTmpMtx1[9];
    FLOAT64 peTmpMtx2[9];


    // 實體相機中心在影像平面座標的位置
    uwCenterRC_X = ((a_ptAVParams->ulCameraPlaneWidth)>>1);
    uwCenterRC_Y = ((a_ptAVParams->ulCameraPlaneHeight)>>1);

    // 虛擬相機中心在虛擬影像平面上的位置
    lCenterVC_X = ((a_ptAVParams->ulDestPlaneWidth)>>1) + a_ptAVParams->lDestPlaneOriginOffsetX;
    lCenterVC_Y = ((a_ptAVParams->ulDestPlaneHeight)>>1) + a_ptAVParams->lDestPlaneOriginOffsetY;

    // 將 virtual camera 座標系統(3D) 轉換到 真實影像座標系統(2D)
    eFocalLength_VirtualCamera_H = (a_ptAVParams->ulDestPlaneWidth) 
        / (2 * tan(a_ptAVParams->eDestFOV_H * alPI / 180 / 2)); 

    peMvi2vc[0] = 1;            peMvi2vc[1] = 0;                peMvi2vc[2] = - lCenterVC_X;
    peMvi2vc[3] = 0;            peMvi2vc[4] = 1;                peMvi2vc[5] = - lCenterVC_Y;
    peMvi2vc[6] = 0;            peMvi2vc[7] = 0;                peMvi2vc[8] = eFocalLength_VirtualCamera_H;

#if 0
    // 將 camera 視角旋轉至向前方正視的狀況
    eCameraPitchAngle = - a_ptAVParams->eCameraPitchAngle * alPI / 180;
    eCameraYawAngle = - a_ptAVParams->eCameraYawAngle * alPI / 180;
    eCameraRollAngle = - a_ptAVParams->eCameraRollAngle * alPI / 180;
    peRotatCorrectX[0] = 1;                                  peRotatCorrectX[1] = 0;                                  peRotatCorrectX[2] = 0;
    peRotatCorrectX[3] = 0;                                  peRotatCorrectX[4] = cos(eCameraPitchAngle);             peRotatCorrectX[5] = - sin(eCameraPitchAngle);
    peRotatCorrectX[6] = 0;                                  peRotatCorrectX[7] = sin(eCameraPitchAngle);             peRotatCorrectX[8] = cos(eCameraPitchAngle);

    peRotatCorrectY[0] = cos(eCameraYawAngle);               peRotatCorrectY[1] = 0;                                  peRotatCorrectY[2] = sin(eCameraYawAngle);
    peRotatCorrectY[3] = 0;                                  peRotatCorrectY[4] = 1;                                  peRotatCorrectY[5] = 0;
    peRotatCorrectY[6] = -sin(eCameraYawAngle);              peRotatCorrectY[7] = 0;                                  peRotatCorrectY[8] = cos(eCameraYawAngle);

    peRotatCorrectZ[0] = cos(eCameraRollAngle);              peRotatCorrectZ[1] = -sin(eCameraRollAngle);             peRotatCorrectZ[2] = 0;
    peRotatCorrectZ[3] = sin(eCameraRollAngle);              peRotatCorrectZ[4] = cos(eCameraRollAngle);              peRotatCorrectZ[5] = 0;
    peRotatCorrectZ[6] = 0;                                  peRotatCorrectZ[7] = 0;                                  peRotatCorrectZ[8] = 1;
#endif

    // 將 camera 視角從正視前方的狀態再旋轉至任意角度
    eDestPitchAngle = a_ptAVParams->eDestPitchAngle * alPI / 180;
    eDestYawAngle = a_ptAVParams->eDestYawAngle * alPI / 180;
    eDestRollAngle = a_ptAVParams->eDestRollAngle * alPI / 180;
    peRotatCustomX[0] = 1;                                   peRotatCustomX[1] = 0;                                   peRotatCustomX[2] = 0;
    peRotatCustomX[3] = 0;                                   peRotatCustomX[4] = cos(eDestPitchAngle);               peRotatCustomX[5] = - sin(eDestPitchAngle);
    peRotatCustomX[6] = 0;                                   peRotatCustomX[7] = sin(eDestPitchAngle);               peRotatCustomX[8] = cos(eDestPitchAngle);

    peRotatCustomY[0] = cos(eDestYawAngle);                  peRotatCustomY[1] = 0;                                   peRotatCustomY[2] = sin(eDestYawAngle);
    peRotatCustomY[3] = 0;                                   peRotatCustomY[4] = 1;                                   peRotatCustomY[5] = 0;
    peRotatCustomY[6] = -sin(eDestYawAngle);                 peRotatCustomY[7] = 0;                                   peRotatCustomY[8] = cos(eDestYawAngle);

    peRotatCustomZ[0] = cos(eDestRollAngle);                peRotatCustomZ[1] = -sin(eDestRollAngle);               peRotatCustomZ[2] = 0;
    peRotatCustomZ[3] = sin(eDestRollAngle);                peRotatCustomZ[4] = cos(eDestRollAngle);                peRotatCustomZ[5] = 0;
    peRotatCustomZ[6] = 0;                                   peRotatCustomZ[7] = 0;                                   peRotatCustomZ[8] = 1;

    // Added by Chinson - 20130531: Yaw 的逆向補償 - 不希望修正 Yaw ，以避免過度增加黑邊
#if (YawKOnOff == 1)
    peRotatAntiCorrectY[0] = 1;              peRotatAntiCorrectY[1] = 0;                                  peRotatAntiCorrectY[2] = 0;
    peRotatAntiCorrectY[3] = 0;              peRotatAntiCorrectY[4] = 1;                                  peRotatAntiCorrectY[5] = 0;
    peRotatAntiCorrectY[6] = 0;              peRotatAntiCorrectY[7] = 0;                                  peRotatAntiCorrectY[8] = 1;
#else
    peRotatAntiCorrectY[0] = cos(-eCameraYawAngle);               peRotatAntiCorrectY[1] = 0;                                  peRotatAntiCorrectY[2] = sin(-eCameraYawAngle);
    peRotatAntiCorrectY[3] = 0;                                  peRotatAntiCorrectY[4] = 1;                                  peRotatAntiCorrectY[5] = 0;
    peRotatAntiCorrectY[6] = -sin(-eCameraYawAngle);              peRotatAntiCorrectY[7] = 0;                                  peRotatAntiCorrectY[8] = cos(-eCameraYawAngle);
#endif

    // 將 real camera 座標系統(3D) 轉換到 真實影像座標系統(Only for 2D system)
    // Calculate the focal length of real camera (under de-fisheye plane) => sensor width / 2 = f * tan(FOV_H/2)
    eFocalLength_RealCamera = (a_ptAVParams->ulCameraPlaneWidth) 
        / (2 * tan(a_ptAVParams->eCameraFOV_H * alPI / 180 / 2)); 

    peMc2i[0] = eFocalLength_RealCamera;                     peMc2i[1] = 0;                                           peMc2i[2] = uwCenterRC_X;
    peMc2i[3] = 0;                                           peMc2i[4] = eFocalLength_RealCamera;                     peMc2i[5] = uwCenterRC_Y;
    peMc2i[6] = 0;                                           peMc2i[7] = 0;                                           peMc2i[8] = 1;

    // Custom Rotation 
    alMATRIX_Multiplaction(peRotatCustomZ, peMvi2vc, 3, 3, 3, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCustomY, peTmpMtx1, 3, 3, 3, peTmpMtx2);
    alMATRIX_Multiplaction(peRotatCustomX, peTmpMtx2, 3, 3, 3, peTmpMtx1);

#if 0
    // Camera Rotation
    alMATRIX_Multiplaction(peRotatCorrectX, peTmpMtx1, 3, 3, 3, peTmpMtx2);
    alMATRIX_Multiplaction(peRotatCorrectY, peTmpMtx2, 3, 3, 3, peTmpMtx1);
    alMATRIX_Multiplaction(peRotatCorrectZ, peTmpMtx1, 3, 3, 3, peTmpMtx2);
#else
    alMATRIX_Multiplaction(a_ptAVParams->aeRotationMatrix, peTmpMtx1, 3, 3, 3, peTmpMtx2);
#endif
    
    // Added by Chinson - 20130531: Yaw 的逆向補償 - 不希望修正 Yaw ，以避免過度增加黑邊
    alMATRIX_Multiplaction(peRotatAntiCorrectY, peTmpMtx2, 3, 3, 3, peTmpMtx1);

    if(a_ptAVParams->ucFisheyeModelMode == 0)
    {
        // real camera to original plane
        alMATRIX_Multiplaction(peMc2i, peTmpMtx1, 3, 3, 3, peTmpMtx2);
        memcpy(a_peM33, peTmpMtx2, 9 * sizeof(FLOAT64));
    }
    else if(a_ptAVParams->ucFisheyeModelMode == 1)
    {
        // 3D coordinates
        memcpy(a_peM33, peTmpMtx1, 9 * sizeof(FLOAT64));
    }
    else
    {
        assert(FALSE);
    }

}

void alAlleyViewCoordinatesTransform2D_Batch(FLOAT64 a_aeM33[9], FLOAT64 * a_peSrcX, FLOAT64 * a_peSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, UINT32 a_ulCount)
{
    FLOAT64 eS;
    UINT32 ulIndex;
    for(ulIndex = 0; ulIndex < a_ulCount; ulIndex++, a_peSrcX++, a_peSrcY++, a_peDestX++, a_peDestY++)
    {
        eS  = a_aeM33[6] * (*a_peSrcX) + a_aeM33[7] * (*a_peSrcY) + a_aeM33[8] * 1;
        eS = eS + (eS == 0.);
        //if(eS == 0.) eS = 1;
        (*a_peDestX) = (a_aeM33[0] * (*a_peSrcX) + a_aeM33[1] * (*a_peSrcY) + a_aeM33[2] * 1) / eS;
        (*a_peDestY) = (a_aeM33[3] * (*a_peSrcX) + a_aeM33[4] * (*a_peSrcY) + a_aeM33[5] * 1) / eS;
    }
}

void alAlleyViewCoordinatesTransform2D(FLOAT64 a_aeM33[9], FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY)
{
    FLOAT64 eS;
    eS  = a_aeM33[6] * a_eSrcX + a_aeM33[7] * a_eSrcY + a_aeM33[8] * 1;
    eS = eS + (eS == 0.);
    (*a_peDestX) = (a_aeM33[0] * a_eSrcX + a_aeM33[1] * a_eSrcY + a_aeM33[2] * 1) / eS;
    (*a_peDestY) = (a_aeM33[3] * a_eSrcX + a_aeM33[4] * a_eSrcY + a_aeM33[5] * 1) / eS;
}

void alAlleyViewCoordinatesTransform3D_Batch(FLOAT64 a_aeM33[9], FLOAT64 * a_peSrcX, FLOAT64 * a_peSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ, UINT32 a_ulCount)
{
    UINT32 ulIndex;
    for(ulIndex = 0; ulIndex < a_ulCount; ulIndex++, a_peSrcX++, a_peSrcY++, a_peDestX++, a_peDestY++)
    {
        (*a_peDestX) = (a_aeM33[0] * (*a_peSrcX) + a_aeM33[1] * (*a_peSrcY) + a_aeM33[2] * 1);
        (*a_peDestY) = (a_aeM33[3] * (*a_peSrcX) + a_aeM33[4] * (*a_peSrcY) + a_aeM33[5] * 1);
        (*a_peDestZ) = (a_aeM33[6] * (*a_peSrcX) + a_aeM33[7] * (*a_peSrcY) + a_aeM33[8] * 1);
    }
}

void alAlleyViewCoordinatesTransform3D(FLOAT64 a_aeM33[9], FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    (*a_peDestX) = (a_aeM33[0] * a_eSrcX + a_aeM33[1] * a_eSrcY + a_aeM33[2] * 1);
    (*a_peDestY) = (a_aeM33[3] * a_eSrcX + a_aeM33[4] * a_eSrcY + a_aeM33[5] * 1);
    (*a_peDestZ) = (a_aeM33[6] * a_eSrcX + a_aeM33[7] * a_eSrcY + a_aeM33[8] * 1);
}

