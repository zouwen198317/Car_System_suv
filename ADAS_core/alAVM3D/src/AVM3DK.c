
#include "AVM3DK.h"
#include "basedef.h"  // add by ancre 2014 07 18
#include "AVM3DM33Generation.h"
#include "alFM_v2_1.h"
#include "alFM_v2_1_Default.h"
#include "alLUT_v2.h"
#include <math.h>       /* sqrt */
#include <assert.h>
#include "AVM3DKOverlaping.h"
#include "AVM3DKProjection.h"
#include "alCameraInfo.h"
#include "alMatrix.h"

#if AVM3D_DEBUG_FALG // FOR rt  TEST
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#define VC_FM_SCALE 0

void AVM3D_MorphingGAPCal(alAVM3D_CfgSingleView *a_ptSrcViewPara, alAVM3D_CfgSingleView *a_ptDestViewPara, alAVM3D_CfgSingleView *a_ptParaGap);

/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL AVM3D_InitializeBuffer(alLUT_v2_Def * a_ptAVM3D_LUT, alPartLUT_v2_Def ** a_ptAVM3D_PartLUT)
{
    memset(a_ptAVM3D_LUT, 0x0, sizeof(alLUT_v2_Def));

#if 0
    if(a_ptAVM3D_PartLUT != NULL)
    {
        (*a_ptAVM3D_PartLUT) = (alPartLUT_v2_Def*) malloc(sizeof(alPartLUT_v2_Def));
        memset((*a_ptAVM3D_PartLUT), 0x0, sizeof(alPartLUT_v2_Def));

	    (*a_ptAVM3D_PartLUT)->lut_data = (UINT8*)malloc(MAX_L2_BLOCK_LUT_NUM*sizeof(UINT8)*8);  //Allocate the partitioned LUT memory.
	    if((*a_ptAVM3D_PartLUT)->lut_data == NULL) 
	    {
		    DEBUG_Printf("Memory Allocation Failed: AVM2D_InitializeBuffer::(*a_ptAVM3D_PartLUT)->lut_data");
		    // alERROR_SetErrorCode(EAGLEK3_ERROR_MEMORY_ALLOCATION_FAILED);
		    return FALSE;
	    }	
    }
#endif
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void AVM3D_LogFUNC(
    char *a_pcWorkFolder,
    INT32 a_lVirtualViewNo,
    alAVM3D_ParamsSingle *a_ptAVM3DParam,
    alAVM3D_CfgSingleView * a_ptAVM3DCfg
                          )
{
    char acLogFileName[100] = {0};
    char acName[20] = "_LogView";
    char acSubName[20] = ".csv";
    FILE *pfPtr = NULL;
    INT32 i = 0;

#if 0 // by number   
    sprintf(acLogFileName, "%s%s%d%s", a_pcWorkFolder, acName, a_lVirtualViewNo, acSubName);
    pfPtr = fopen(acLogFileName, "w+");
#else // by view's name
    sprintf(acLogFileName, "%s%s%s%s", a_pcWorkFolder, a_ptAVM3DCfg->acName, acName, acSubName);
    pfPtr = fopen(acLogFileName, "w+");
#endif

    // size offset VC center
    fprintf(pfPtr ,",size,offset,VC center\n");
    fprintf(pfPtr ,"X,%d,%d,%d\n", a_ptAVM3DCfg->tDestAreaSize.lX, a_ptAVM3DCfg->lOffsetX, a_ptAVM3DParam->tVC_CenterCoordinate.lX);
    fprintf(pfPtr ,"Y,%d,%d,%d\n\n", a_ptAVM3DCfg->tDestAreaSize.lY, a_ptAVM3DCfg->lOffsetY, a_ptAVM3DParam->tVC_CenterCoordinate.lY);

    // position
    fprintf(pfPtr ,",VC Posituin\n");
    fprintf(pfPtr ,"X,%d\n", a_ptAVM3DCfg->lVirtualCameraPosX);
    fprintf(pfPtr ,"Y,%d\n", a_ptAVM3DCfg->lVirtualCameraPosY);
    fprintf(pfPtr ,"Z,%d\n\n", a_ptAVM3DCfg->lVirtualCameraPosZ);

    // pitch yaw roll
    fprintf(pfPtr ,"pitch,yaw,roll\n");
    fprintf(pfPtr ,"%f,%f,%f\n\n", a_ptAVM3DCfg->fVirtualCameraPitch, a_ptAVM3DCfg->fVirtualCameraYaw, a_ptAVM3DCfg->fVirtualCameraRoll);



    // Phi
    for(i = 0 ; i < 9 ; i++)
    {
        fprintf(pfPtr ,"Phi%d,", i);
    }
    fprintf(pfPtr ,"\n");
    for(i = 0 ; i < 9 ; i++)
    {
        fprintf(pfPtr ,"%f,", a_ptAVM3DParam->ePhi[i]);
    }
    fprintf(pfPtr ,"\n\n");

    // Theta
    for(i = 0 ; i < 9 ; i++)
    {
        fprintf(pfPtr ,"Theta%d,", i);
    }
    fprintf(pfPtr ,"\n");
    for(i = 0 ; i < 9 ; i++)
    {
        fprintf(pfPtr ,"%f,", a_ptAVM3DParam->eTheta[i]);
    }
    fprintf(pfPtr ,"\n\n");

    // Curve Paremeter
    fprintf(pfPtr ,"Curve Paremeter\n");
    fprintf(pfPtr ,"A,B,C,D,E,F\n");
    fprintf(pfPtr ,"%f,%f,%f,%f,%f,%f\n\n", a_ptAVM3DCfg->eCurveSurfaceA, a_ptAVM3DCfg->eCurveSurfaceB, a_ptAVM3DCfg->eCurveSurfaceC, a_ptAVM3DCfg->eCurveSurfaceD, a_ptAVM3DCfg->eCurveSurfaceE, a_ptAVM3DCfg->eCurveSurfaceF);
   
    // Curve Center
    fprintf(pfPtr ,"Curve Center\n");
    fprintf(pfPtr ,"X,Y,Z\n");
    fprintf(pfPtr ,"%f,%f,%f\n\n", a_ptAVM3DCfg->fCurveCenterX, a_ptAVM3DCfg->fCurveCenterY, a_ptAVM3DCfg->fCurveCenterZ);

    // Curve Meet Point
    fprintf(pfPtr ,"Curve Meet Point\n");
    fprintf(pfPtr ,"Point,X,Y,Z\n");
    for(i = 0 ; i < 9 ; i++)
    {
        fprintf(pfPtr ,"P%d,%f,%f,%f\n", i, a_ptAVM3DParam->tCurveMeetPoint[i][0], a_ptAVM3DParam->tCurveMeetPoint[i][1], a_ptAVM3DParam->tCurveMeetPoint[i][2]);
    }

    fclose(pfPtr);

    

}

void AVM3D_VIewAnalyzing(
    INT32 a_lVirtualViewNo,
    alAVM3D_ParamsSingle *a_ptAVM3DParam,
    alAVM3D_CfgSingleView * a_ptAVM3DCfg,
    alFM_v2_1_Model * a_ptFisheyeModel
    )
{
    alPointINT32 atPoint[9]; // 0~7: P0~P7   8:VC point
    INT32 i = 0;
    FLOAT64 aeUnDistX[9], aeUnDistY[9], aeDistance[3] , eSIN, eAngle, aeFixX[9], aeFixY[9];
    FLOAT64 eScaledX, eScaledY;
    FLOAT64 eVCUnDistX, eVCUnDistY, eVCUnDistZ;
    FLOAT64 eBVCX1, eBVCY1, eBVCZ1;
    FLOAT64 eBVPosX, eBVPosY, eBVPosZ;
	FLOAT64 aeVCtoBV[10][2][16];
    INT32 lVCCenterX, lVCCenterY;
    AVM3D_Projection3DCfg tCurveModel;
    
    AVM3D_Projection3DCfg tCurveModelTmp;
    FLOAT64 aeCurvePara[9];
    FLOAT64 aeP1[3];

    AVM3D_Set3DCurveProjectionInfo(a_ptAVM3DCfg, &tCurveModel);

    // 曲面2 的設定
    aeCurvePara[0] = a_ptAVM3DCfg->eCurve2SurfaceA;
    aeCurvePara[1] = a_ptAVM3DCfg->eCurve2SurfaceB;
    aeCurvePara[2] = a_ptAVM3DCfg->eCurve2SurfaceC;
    aeCurvePara[3] = a_ptAVM3DCfg->eCurve2SurfaceD;
    aeCurvePara[4] = a_ptAVM3DCfg->eCurve2SurfaceE;
    aeCurvePara[5] = a_ptAVM3DCfg->eCurve2SurfaceF;
    aeCurvePara[6] = a_ptAVM3DCfg->fCurve2CenterX;
    aeCurvePara[7] = a_ptAVM3DCfg->fCurve2CenterY;
    aeCurvePara[8] = a_ptAVM3DCfg->fCurve2CenterZ;
    AVM3D_Set3DCurveProjectionInfoByArray(aeCurvePara, &tCurveModelTmp);

	// Copy VC RT Information to AVM 3D parameter
    {
        // VCtoBV
        aeVCtoBV[a_lVirtualViewNo][1][0] = a_ptAVM3DParam->aeRotationMatrixVC[1][0];
        aeVCtoBV[a_lVirtualViewNo][1][1] = a_ptAVM3DParam->aeRotationMatrixVC[1][1];
        aeVCtoBV[a_lVirtualViewNo][1][2] = a_ptAVM3DParam->aeRotationMatrixVC[1][2];
        aeVCtoBV[a_lVirtualViewNo][1][4] = a_ptAVM3DParam->aeRotationMatrixVC[1][3];
        aeVCtoBV[a_lVirtualViewNo][1][5] = a_ptAVM3DParam->aeRotationMatrixVC[1][4];
        aeVCtoBV[a_lVirtualViewNo][1][6] = a_ptAVM3DParam->aeRotationMatrixVC[1][5];
        aeVCtoBV[a_lVirtualViewNo][1][8] = a_ptAVM3DParam->aeRotationMatrixVC[1][6];
        aeVCtoBV[a_lVirtualViewNo][1][9] = a_ptAVM3DParam->aeRotationMatrixVC[1][7];
        aeVCtoBV[a_lVirtualViewNo][1][10] = a_ptAVM3DParam->aeRotationMatrixVC[1][8];

        aeVCtoBV[a_lVirtualViewNo][1][3] = a_ptAVM3DParam->aeTranslationMatrixVC[1][0];
        aeVCtoBV[a_lVirtualViewNo][1][7] = a_ptAVM3DParam->aeTranslationMatrixVC[1][1];
        aeVCtoBV[a_lVirtualViewNo][1][11] = a_ptAVM3DParam->aeTranslationMatrixVC[1][2];
        aeVCtoBV[a_lVirtualViewNo][1][12] = 0.0;
        aeVCtoBV[a_lVirtualViewNo][1][13] = 0.0;
        aeVCtoBV[a_lVirtualViewNo][1][14] = 0.0;
        aeVCtoBV[a_lVirtualViewNo][1][15] = 1.0;

        // BVtoVC
        aeVCtoBV[a_lVirtualViewNo][0][0] = a_ptAVM3DParam->aeRotationMatrixVC[0][0];
        aeVCtoBV[a_lVirtualViewNo][0][1] = a_ptAVM3DParam->aeRotationMatrixVC[0][1];
        aeVCtoBV[a_lVirtualViewNo][0][2] = a_ptAVM3DParam->aeRotationMatrixVC[0][2];
        aeVCtoBV[a_lVirtualViewNo][0][4] = a_ptAVM3DParam->aeRotationMatrixVC[0][3];
        aeVCtoBV[a_lVirtualViewNo][0][5] = a_ptAVM3DParam->aeRotationMatrixVC[0][4];
        aeVCtoBV[a_lVirtualViewNo][0][6] = a_ptAVM3DParam->aeRotationMatrixVC[0][5];
        aeVCtoBV[a_lVirtualViewNo][0][8] = a_ptAVM3DParam->aeRotationMatrixVC[0][6];
        aeVCtoBV[a_lVirtualViewNo][0][9] = a_ptAVM3DParam->aeRotationMatrixVC[0][7];
        aeVCtoBV[a_lVirtualViewNo][0][10] = a_ptAVM3DParam->aeRotationMatrixVC[0][8];
    }

    lVCCenterX = (a_ptAVM3DParam->ptFisheyeModelVC->uwSrcWidth >> 1);
    lVCCenterY = (a_ptAVM3DParam->ptFisheyeModelVC->uwSrcHeight >> 1);
    
    atPoint[0].lX = 0;
    atPoint[0].lY = 0;

    atPoint[1].lX = a_ptAVM3DParam->tVC_CenterCoordinate.lX;
    atPoint[1].lY = 0;

    atPoint[2].lX = a_ptAVM3DCfg->tDestAreaSize.lX-1;
    atPoint[2].lY = 0;

    atPoint[3].lX = 0;
    atPoint[3].lY = a_ptAVM3DParam->tVC_CenterCoordinate.lY;

    atPoint[4].lX = a_ptAVM3DCfg->tDestAreaSize.lX-1;
    atPoint[4].lY = a_ptAVM3DParam->tVC_CenterCoordinate.lY;

    atPoint[5].lX = 0;
    atPoint[5].lY = a_ptAVM3DCfg->tDestAreaSize.lY-1;

    atPoint[6].lX = a_ptAVM3DParam->tVC_CenterCoordinate.lX;
    atPoint[6].lY = a_ptAVM3DCfg->tDestAreaSize.lY-1;

    atPoint[7].lX = a_ptAVM3DCfg->tDestAreaSize.lX-1;
    atPoint[7].lY = a_ptAVM3DCfg->tDestAreaSize.lY-1;

    atPoint[8].lX = a_ptAVM3DParam->tVC_CenterCoordinate.lX;
    atPoint[8].lY = a_ptAVM3DParam->tVC_CenterCoordinate.lY;


    // Scale & Offset to VC Model
    for(i = 0 ; i < 9 ; i ++)
    {
        aeFixX[i] = a_ptAVM3DCfg->tDestStartPoint.lX + ((atPoint[i].lX - lVCCenterX + a_ptAVM3DCfg->lOffsetX) / a_ptAVM3DCfg->eScalingX + lVCCenterX);
        aeFixY[i] = a_ptAVM3DCfg->tDestStartPoint.lY + (( atPoint[i].lY - lVCCenterY + a_ptAVM3DCfg->lOffsetY) / a_ptAVM3DCfg->eScalingY + lVCCenterY);
    }



    // Transfer to Undistor Image
    for(i = 0 ; i < 9 ; i ++)
    {
        alFM_v2_1_Distorted2Undistorted_Planar(a_ptAVM3DParam->ptFisheyeModelVC, aeFixX[i], aeFixY[i], &aeUnDistX[i], &aeUnDistY[i]);
    }



    // Get Teta and Phi
    for(i = 0 ; i < 8 ; i ++)
    {
        aeDistance[0] = a_ptAVM3DParam->ptFisheyeModelVC->eFocalLength;
        aeDistance[1] = sqrt((aeUnDistX[i]-aeUnDistX[8])*(aeUnDistX[i]-aeUnDistX[8]) + (aeUnDistY[i]-aeUnDistY[8])*(aeUnDistY[i]-aeUnDistY[8]));
        aeDistance[2] = sqrt( (aeDistance[0]*aeDistance[0]) + (aeDistance[1]*aeDistance[1]) );

        eSIN = aeDistance[1] / aeDistance[2];
        eAngle = asin (eSIN) * 180.0 / alPI;
        a_ptAVM3DParam->eTheta[i] = eAngle;

        aeDistance[0] = sqrt((aeUnDistX[4]-aeUnDistX[8])*(aeUnDistX[4]-aeUnDistX[8]) + (aeUnDistY[4]-aeUnDistY[8])*(aeUnDistY[4]-aeUnDistY[8]));
        aeDistance[1] = sqrt((aeUnDistX[i]-aeUnDistX[8])*(aeUnDistX[i]-aeUnDistX[8]) + (aeUnDistY[i]-aeUnDistY[8])*(aeUnDistY[i]-aeUnDistY[8]));
        aeDistance[2] = sqrt((aeUnDistX[i]-aeUnDistX[4])*(aeUnDistX[i]-aeUnDistX[4]) + (aeUnDistY[i]-aeUnDistY[4])*(aeUnDistY[i]-aeUnDistY[4]));

        eAngle = AVM3D_AngleCalByLength(aeDistance);

        a_ptAVM3DParam->ePhi[i] = eAngle;

        if(i < 3)
        {
            a_ptAVM3DParam->ePhi[i] = 360 - a_ptAVM3DParam->ePhi[i];
        }

    }

    lVCCenterX = (a_ptAVM3DParam->ptFisheyeModelVC->uwSrcWidth >> 1);
    lVCCenterY = (a_ptAVM3DParam->ptFisheyeModelVC->uwSrcHeight >> 1);


    // Get curve meet point
    for(i = 0 ; i < 9 ; i ++)
    {
        if(a_ptAVM3DCfg->lMirror == 1)
        {
            eScaledX = a_ptAVM3DCfg->tDestAreaSize.lX - atPoint[i].lX - 1;
        }
        else
        {
            eScaledX = atPoint[i].lX;
        }

        eScaledX = eScaledX + a_ptAVM3DCfg->tDestStartPoint.lX;
        eScaledY = atPoint[i].lY + a_ptAVM3DCfg->tDestStartPoint.lY;

        eScaledX = (eScaledX - lVCCenterX + a_ptAVM3DCfg->lOffsetX) / a_ptAVM3DCfg->eScalingX + lVCCenterX; 
        eScaledY = (eScaledY - lVCCenterY + a_ptAVM3DCfg->lOffsetY) / a_ptAVM3DCfg->eScalingY + lVCCenterY; 

        // 將虛擬平面的 2D 座標，投影到虛擬相機 3D 球面座標 (mm)
        alFM_v2_1_Distorted2Undistorted_Sphere(a_ptAVM3DParam->ptFisheyeModelVC, eScaledX, eScaledY, &eVCUnDistX, &eVCUnDistY, &eVCUnDistZ);

        // (1) 旋轉到鏡頭向下的座標，且 BV Camera 位於 (X, Y ,Z) = (0, 0, 0);
        AVM3D_CoordinatesTransform3D(aeVCtoBV[a_lVirtualViewNo][1], eVCUnDistX, eVCUnDistY, eVCUnDistZ, &eBVCX1, &eBVCY1, &eBVCZ1);

        if (a_ptAVM3DCfg->lCURVE2_FLAG)
        {
            // (2.1) 將(1)得到的座標，重新投影到曲面的座標
            AVM3D_Projection3DModelCal(&(tCurveModelTmp), a_ptAVM3DCfg->lVirtualCameraPosX, a_ptAVM3DCfg->lVirtualCameraPosY, a_ptAVM3DCfg->lVirtualCameraPosZ,
                eBVCX1, eBVCY1, eBVCZ1, &aeP1[0], &aeP1[1], &aeP1[2]);

            // (2.2) project again 
            AVM3D_Projection3DModelCal(&(tCurveModel), 0, 0, a_ptAVM3DCfg->lCurve2ProjCenZ,
                aeP1[0], aeP1[1], aeP1[2], &eBVPosX, &eBVPosY, &eBVPosZ);
        }
        else
        {	// 只對碗公curve 做投影

            // (2) 將(1)得到的座標，重新投影到曲面的座標
            AVM3D_Projection3DModelCal(&(tCurveModel), a_ptAVM3DCfg->lVirtualCameraPosX, a_ptAVM3DCfg->lVirtualCameraPosY, a_ptAVM3DCfg->lVirtualCameraPosZ,
                eBVCX1, eBVCY1, eBVCZ1, &eBVPosX, &eBVPosY, &eBVPosZ);

        }

        a_ptAVM3DParam->tCurveMeetPoint[i][0] = eBVPosX;
        a_ptAVM3DParam->tCurveMeetPoint[i][1] = eBVPosY;
        a_ptAVM3DParam->tCurveMeetPoint[i][2] = eBVPosZ;
    }
}



void AVM3D_GenerateM33(INT32 a_lViewIndex,
                        alAVM3D_ParamsSingle *a_ptAVM3DParam,
                        alAVM3D_CfgSingleView * a_ptAVM3DCfg
                        )
{
    AVM3DGenerateParams tAVM3DTranfromSetting;
    // CAMK_CameraCfg * ptCameraCfg = 0;
    alFM_v2_1_Model * ptCameraFisheyeModel = 0;
    FLOAT64 * peM33_WtoI = 0;
    FLOAT64 * peM33_ItoW = 0;
	FLOAT64 aeVCtoBV[2][16]; // [0][1]
    UINT8 ucBVCameraIndx = 0;

    // Real plane and destination plane width & height
    tAVM3DTranfromSetting.ulCameraPlaneWidth = a_ptAVM3DCfg->tDestAreaSize.lX;
    tAVM3DTranfromSetting.ulCameraPlaneHeight = a_ptAVM3DCfg->tDestAreaSize.lY;
    tAVM3DTranfromSetting.ulDestPlaneWidth = a_ptAVM3DCfg->tDestAreaSize.lX;
    tAVM3DTranfromSetting.ulDestPlaneHeight = a_ptAVM3DCfg->tDestAreaSize.lY;

    // Real Camera Angle
    tAVM3DTranfromSetting.eCameraPitchAngle = 0;
    tAVM3DTranfromSetting.eCameraYawAngle = 0;
    tAVM3DTranfromSetting.eCameraRollAngle = 0;
    
    // Virtual Camera Angle
    tAVM3DTranfromSetting.eDestPitchAngle = a_ptAVM3DCfg->fVirtualCameraPitch;
    tAVM3DTranfromSetting.eDestYawAngle = a_ptAVM3DCfg->fVirtualCameraYaw;
    tAVM3DTranfromSetting.eDestRollAngle = a_ptAVM3DCfg->fVirtualCameraRoll;

    // Virtual Camera Roll
    tAVM3DTranfromSetting.eCameraCustomRoll = a_ptAVM3DCfg->fVirtualCameraCustomRoll;


    // Camera Position
    tAVM3DTranfromSetting.lRealCameraX = 0; // 向右為 X 正方向
    tAVM3DTranfromSetting.lRealCameraY = 0; // 向車尾為 Y 正方向
    tAVM3DTranfromSetting.lRealCameraZ = 0; // 向地下為 Z 正方向

    /* Calculate Position offset of the destination virtual canera
       => The origin coordinates of ptCameraCfg->lCameraPosX, Y, Z is center position of vehicle.
        

          ________
        _|        |_
       |_          _|
         |   ．   |       向右為 X 正方向
         |(origin)|       向下為 Y 正方向     
         |________|

            CAR

    */

    // Virtual Camera Position
    tAVM3DTranfromSetting.lVitrualCameraX = a_ptAVM3DCfg->lVirtualCameraPosX; // 向右為 X 正方向
    tAVM3DTranfromSetting.lVitrualCameraY = a_ptAVM3DCfg->lVirtualCameraPosY; //2000; // 向車尾為 Y 正方向
    tAVM3DTranfromSetting.lVitrualCameraZ = a_ptAVM3DCfg->lVirtualCameraPosZ; // 向車尾為 Y 正方向


    // Generate perspective transformation matrix : VC2BV
    AVM3D_MatrixGeneratorStep1(&tAVM3DTranfromSetting, aeVCtoBV[1]);
    
    memcpy(aeVCtoBV[0], aeVCtoBV[1], sizeof(FLOAT64) * 16);

    // Generate perspective transformation matrix : BV2VC
    alMATRIX_InverseNbyN(aeVCtoBV[0], 4);

    // Copy VC RT Information to AVM 3D parameter
    {
    a_ptAVM3DParam->aeRotationMatrixVC[1][0] = aeVCtoBV[1][0];
    a_ptAVM3DParam->aeRotationMatrixVC[1][1] = aeVCtoBV[1][1];
    a_ptAVM3DParam->aeRotationMatrixVC[1][2] = aeVCtoBV[1][2];
    a_ptAVM3DParam->aeRotationMatrixVC[1][3] = aeVCtoBV[1][4];
    a_ptAVM3DParam->aeRotationMatrixVC[1][4] = aeVCtoBV[1][5];
    a_ptAVM3DParam->aeRotationMatrixVC[1][5] = aeVCtoBV[1][6];
    a_ptAVM3DParam->aeRotationMatrixVC[1][6] = aeVCtoBV[1][8];
    a_ptAVM3DParam->aeRotationMatrixVC[1][7] = aeVCtoBV[1][9];
    a_ptAVM3DParam->aeRotationMatrixVC[1][8] = aeVCtoBV[1][10];

    memcpy(a_ptAVM3DParam->aeRotationMatrixVC[0], a_ptAVM3DParam->aeRotationMatrixVC[1], sizeof(FLOAT64)*9);
    alMATRIX_InverseNbyN(a_ptAVM3DParam->aeRotationMatrixVC[0], 3);

#if 1	 // 環場測試
	a_ptAVM3DParam->aeTranslationMatrixVC[1][0] = aeVCtoBV[1][3];
    a_ptAVM3DParam->aeTranslationMatrixVC[1][1] = aeVCtoBV[1][7];
    a_ptAVM3DParam->aeTranslationMatrixVC[1][2] = aeVCtoBV[1][11];
#else	 // 原本
    a_ptAVM3DParam->aeTranslationMatrixVC[1][0] = a_ptAVM3DCfg->lVirtualCameraPosX;
    a_ptAVM3DParam->aeTranslationMatrixVC[1][1] = a_ptAVM3DCfg->lVirtualCameraPosY;
    a_ptAVM3DParam->aeTranslationMatrixVC[1][2] = a_ptAVM3DCfg->lVirtualCameraPosZ;
#endif

    alMATRIX_Multiplaction(a_ptAVM3DParam->aeRotationMatrixVC[0], a_ptAVM3DParam->aeTranslationMatrixVC[1], 3, 3, 1, a_ptAVM3DParam->aeTranslationMatrixVC[0]);

    // translation = Rotation* offset >> offset = -1*position
    a_ptAVM3DParam->aeTranslationMatrixVC[0][0] *= -1;
    a_ptAVM3DParam->aeTranslationMatrixVC[0][1] *= -1;
    a_ptAVM3DParam->aeTranslationMatrixVC[0][2] *= -1;
   
    // assign VC center >>> just for 光機log
    a_ptAVM3DParam->tVC_CenterCoordinate.lX = (a_ptAVM3DCfg->tDestAreaSize.lX >>1) + ((a_ptAVM3DCfg->tDestImageBufferSize.lX>>1)-(a_ptAVM3DCfg->tDestAreaSize.lX >>1)) - a_ptAVM3DCfg->lOffsetX;
    a_ptAVM3DParam->tVC_CenterCoordinate.lY = (a_ptAVM3DCfg->tDestAreaSize.lY >>1) + ((a_ptAVM3DCfg->tDestImageBufferSize.lY>>1)-(a_ptAVM3DCfg->tDestAreaSize.lY >>1)) - a_ptAVM3DCfg->lOffsetY;
    }
}



void AVM3D_CoordinatesTransformVCtoBV(FLOAT64 a_aeM33[16], alFM_v2_1_Model * a_ptFisheyeModelSrc, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    FLOAT64 eUnDistSrcX, eUnDistSrcY, eUnDistSrcZ;

    // 將虛擬平面的 2D 座標，投影到虛擬相機 3D 球面座標
    alFM_v2_1_Distorted2Undistorted_Sphere(a_ptFisheyeModelSrc, a_eSrcX, a_eSrcY, &eUnDistSrcX, &eUnDistSrcY, &eUnDistSrcZ);

    // 將虛擬相機 3D 球面座標經由 M33 轉換到實體相機 3D 球面座標
    AVM3D_CoordinatesTransform3D(a_aeM33, eUnDistSrcX, eUnDistSrcY, eUnDistSrcZ, a_peDestX, a_peDestY, a_peDestZ);
}

void AVM3D_CoordinatesTransformBVtoRC(FLOAT64 a_aeM33[16], alFM_v2_1_Model * a_ptFisheyeModelDest, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY)
{
    FLOAT64 eUnDistDestX, eUnDistDestY, eUnDistDestZ;

    // 將虛擬相機 3D 球面座標經由 M33 轉換到實體相機 3D 球面座標
    AVM3D_CoordinatesTransform3D(a_aeM33, a_eSrcX, a_eSrcY, a_eSrcZ, &eUnDistDestX, &eUnDistDestY, &eUnDistDestZ);
    
    // 將實體相機 3D 球面座標投影到實體相機 2D 平面
    alFM_v2_1_Undistorted2Distorted_Sphere(a_ptFisheyeModelDest, eUnDistDestX, eUnDistDestY, eUnDistDestZ, a_peDestX, a_peDestY);
}

void AVM3D_CoordinatesTransform2D(FLOAT64 a_aeM33[9], alFM_v2_1_Model * a_ptFisheyeModelSrc, alFM_v2_1_Model * a_ptFisheyeModelDest, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY)
{

    FLOAT64 eUnDistSrcX, eUnDistSrcY, eUnDistSrcZ;
    FLOAT64 eUnDistDestX, eUnDistDestY, eUnDistDestZ;

    // 將虛擬平面的 2D 座標，投影到虛擬相機 3D 球面座標
    alFM_v2_1_Distorted2Undistorted_Sphere(a_ptFisheyeModelSrc, a_eSrcX, a_eSrcY, &eUnDistSrcX, &eUnDistSrcY, &eUnDistSrcZ);

    // 將虛擬相機 3D 球面座標經由 M33 轉換到實體相機 3D 球面座標
    AVM3D_CoordinatesTransform3D(a_aeM33, eUnDistSrcX, eUnDistSrcY, eUnDistSrcZ, &eUnDistDestX, &eUnDistDestY, &eUnDistDestZ);

    // 將實體相機 3D 球面座標投影到實體相機 2D 平面
    alFM_v2_1_Undistorted2Distorted_Sphere(a_ptFisheyeModelDest, eUnDistDestX, eUnDistDestY, eUnDistDestZ, a_peDestX, a_peDestY);

}

BOOL AVM3D_BVCoordinatesProject_GroundPlane(FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, 
                                            FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, 
                                            FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    FLOAT64 eM1 = a_eBVC_X;
    FLOAT64 eM2 = a_eBVC_Y;
    FLOAT64 eM3 = a_eBVC_Z;

    FLOAT64 eV1 = (a_eSrcX - a_eBVC_X);
    FLOAT64 eV2 = (a_eSrcY - a_eBVC_Y);
    FLOAT64 eV3 = (a_eSrcZ - a_eBVC_Z);

    FLOAT64 eN1 = 0;
    FLOAT64 eN2 = 0;
    FLOAT64 eN3 = 0;
    FLOAT64 eVP1 = 0;
    FLOAT64 eVP2 = 0;
    FLOAT64 eVP3 = -1;

    FLOAT64 eT, eT1;

    eT1 = (eVP1 * eV1+ eVP2 * eV2+ eVP3 * eV3);
    if(eT1 != 0)
    {
        eT = ((eN1 - eM1) * eVP1 + (eN2 - eM2) * eVP2 + (eN3 - eM3) * eVP3) / eT1;

        if(eT >= 0) 
        {
            (*a_peDestX) = eM1 + eV1 * eT;
            (*a_peDestY) = eM2 + eV2 * eT;
            (*a_peDestZ) = eM3 + eV3 * eT;

            return TRUE;
        }
    }

    return FALSE;
}

#if 1
// 找最近的交點
BOOL AVM3D_BVCoordinatesProject_CurveSurface_Nearest(alAVM3D_CfgSingleView * a_ptAVMCfg, UINT8 a_ucCurveIndex, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    //FLOAT64 eCurveOffsetF = 4000;

    {
        FLOAT64 eM1 = a_eBVC_X;
        FLOAT64 eM2 = a_eBVC_Y;
        FLOAT64 eM3 = a_eBVC_Z;

        FLOAT64 eV1 = (a_eSrcX - a_eBVC_X);
        FLOAT64 eV2 = (a_eSrcY - a_eBVC_Y);
        FLOAT64 eV3 = (a_eSrcZ - a_eBVC_Z);

        // Cruve: A * X^2 + B * X + C * Y^2 + D * Y + E * Z + F = 0
        FLOAT64 eCurveA, eCurveB, eCurveC, eCurveD, eCurveE, eCurveF;
        FLOAT64 eParamA, eParamB, eParamC;
        FLOAT64 eT, eTs, eT2;

        eCurveA = a_ptAVMCfg->eCurveSurfaceA;
        eCurveB = a_ptAVMCfg->eCurveSurfaceB;
        eCurveC = a_ptAVMCfg->eCurveSurfaceC; 
        eCurveD = a_ptAVMCfg->eCurveSurfaceD;
        eCurveE = a_ptAVMCfg->eCurveSurfaceE; 
        eCurveF = a_ptAVMCfg->eCurveSurfaceF;

        eParamA = eCurveA * eV1 * eV1 + eCurveC * eV2 * eV2;
        eParamB = 2 * eCurveA * eM1 * eV1 + eCurveB * eV1 + 2 * eCurveC * eM2 * eV2 + eCurveD * eV2 + eCurveE * eV3;
        eParamC = eCurveA * eM1 * eM1 + eCurveB * eM1 + eCurveC * eM2 * eM2 + eCurveD * eM2 + eCurveE * eM3 + eCurveF;

        if(eCurveA == 0 && eCurveC == 0)
        {
            AVM3D_BVCoordinatesProject_GroundPlane(a_eBVC_X, a_eBVC_Y, a_eBVC_Z, a_eSrcX, a_eSrcY, a_eSrcZ, a_peDestX, a_peDestY, a_peDestZ);
        }
        else if(eParamA == 0) 
        {
            (*a_peDestX) = a_eBVC_X ;
            (*a_peDestY) = a_eBVC_Y;
            (*a_peDestZ) = - (eCurveA * eM1 * eM1 + eCurveB * eM1 + eCurveC * eM2 * eM2 + eCurveD * eM2 + eCurveF) / eCurveE;
        }
        else
        {
            assert(eParamA != 0);

            eTs = eParamB * eParamB - 4 * eParamA * eParamC;

            if(eTs < 0) return FALSE;
            assert(eTs >= 0);

            eT = (- eParamB + sqrt(eTs)) / (2.0 * eParamA);
            eT2 = (- eParamB - sqrt(eTs)) / (2.0 * eParamA);

            if(fabs(eT2) < fabs(eT))
            {
                eT = eT2;
            }

#if 0
            if(eT < 0)
            {
                eT = (- eParamB - sqrt(eTs)) / (2.0 * eParamA);
            }

            if(eT < 0) return FALSE;
#endif

            (*a_peDestX) = eM1 + eV1 * eT;
            (*a_peDestY) = eM2 + eV2 * eT;
            (*a_peDestZ) = eM3 + eV3 * eT;
        }

        return TRUE;
    }
}

// 找向量正向的交點
BOOL AVM3D_BVCoordinatesProject_CurveSurface_Positive(alAVM3D_CfgSingleView * a_ptAVMCfg, UINT8 a_ucCurveIndex, FLOAT64 a_eBVC_X, FLOAT64 a_eBVC_Y, FLOAT64 a_eBVC_Z, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    //FLOAT64 eCurveOffsetF = 4000;

    {
        FLOAT64 eM1 = a_eBVC_X;
        FLOAT64 eM2 = a_eBVC_Y;
        FLOAT64 eM3 = a_eBVC_Z;

        FLOAT64 eV1 = (a_eSrcX - a_eBVC_X);
        FLOAT64 eV2 = (a_eSrcY - a_eBVC_Y);
        FLOAT64 eV3 = (a_eSrcZ - a_eBVC_Z);

        // Cruve: A * X^2 + B * X + C * Y^2 + D * Y + E * Z + F = 0
        FLOAT64 eCurveA, eCurveB, eCurveC, eCurveD, eCurveE, eCurveF;
        FLOAT64 eParamA, eParamB, eParamC;
        FLOAT64 eT, eTs, eT2;

        eCurveA = a_ptAVMCfg->eCurveSurfaceA;
        eCurveB = a_ptAVMCfg->eCurveSurfaceB;
        eCurveC = a_ptAVMCfg->eCurveSurfaceC; 
        eCurveD = a_ptAVMCfg->eCurveSurfaceD;
        eCurveE = a_ptAVMCfg->eCurveSurfaceE; 
        eCurveF = a_ptAVMCfg->eCurveSurfaceF;

        eParamA = eCurveA * eV1 * eV1 + eCurveC * eV2 * eV2;
        eParamB = 2 * eCurveA * eM1 * eV1 + eCurveB * eM1 + 2 * eCurveC * eM2 * eV2 + eCurveD * eV2 + eCurveE * eV3;
        eParamC = eCurveA * eM1 * eM1 + eCurveB * eM1 + eCurveC * eM2 * eM2 + eCurveD * eM2 + eCurveE * eM3 + eCurveF;

        if(eCurveA == 0 && eCurveC == 0)
        {
            AVM3D_BVCoordinatesProject_GroundPlane(a_eBVC_X, a_eBVC_Y, a_eBVC_Z, a_eSrcX, a_eSrcY, a_eSrcZ, a_peDestX, a_peDestY, a_peDestZ);
        }
        else if(eParamA == 0) 
        {
            (*a_peDestX) = a_eBVC_X ;
            (*a_peDestY) = a_eBVC_Y;
            (*a_peDestZ) = - (eCurveA * eM1 * eM1 + eCurveB * eM1 + eCurveC * eM2 * eM2 + eCurveD * eM2 + eCurveF) / eCurveE;
        }
        else
        {
            assert(eParamA != 0);

            eTs = eParamB * eParamB - 4 * eParamA * eParamC;

            if(eTs < 0) return FALSE;
            assert(eTs >= 0);

            eT = (- eParamB + sqrt(eTs)) / (2.0 * eParamA);
            eT2 = (- eParamB - sqrt(eTs)) / (2.0 * eParamA);

            if(eT < 0)
            {
                eT = eT2;
            }

            if(eT < 0) return FALSE;

            (*a_peDestX) = eM1 + eV1 * eT;
            (*a_peDestY) = eM2 + eV2 * eT;
            (*a_peDestZ) = eM3 + eV3 * eT;
        }

        return TRUE;
    }
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_GenerateLUT(INT32 a_lViewIndex,
                       alAVM3D_ParamsSingle *a_ptAVMPara,
                       alAVM3D_CfgSingleView * a_ptAVMCfg,
                       alFM_v2_1_Model * a_ptFisheyeModel,
                       alCOMMONK_CalibrationParams *a_ptCalibrationData,
                       alLUT_v2_Def * a_ptAVM3D_LUT
                       )
{
	//UINT64 TableTmpBug;
    UINT8 a_ucViewIndex1, a_ucViewIndex2, ucViewIndexBuff = 0;
    UINT8 ucCameraIndex = 0;
    FLOAT64 aeVCtoBV[2][16];


    AVM3D_StitchLineCfg tStitchLineCfg;
    AVM3D_Projection3DCfg tCurveModel;
	AVM3D_Projection3DCfg tCurveModelTmp;
	FLOAT64  aeCurvePara[9];
	FLOAT64 aeCenter[3], aeP1[3];
	FLOAT64 eBVX_Tmp, eBVY_Tmp, eBVZ_Tmp, RT44Tmp[16];
    FLOAT64 aeBVtoRC[COMMONK_NUM_BV_CHANNEL][2][16];
    FLOAT64 *peM33_WtoI = 0;
    FLOAT64 *peM33_ItoW = 0;
    FLOAT64* paeM33[4];

    INT32 lX = 0, lY = 0;
    FLOAT64 eScaledX = 0, eScaledY = 0;
    UINT32 ulPixelIndex = 0;
    UINT32 ulVCCenterX = 0, ulVCCenterY = 0, ulFMCenterX = 0, ulFMCenterY = 0;

    FLOAT64 eDestX1 = 0, eDestY1 = 0;
    FLOAT64 eDestX2 = 0, eDestY2 = 0;

    paeM33[alCAMERAINFO_BV_LEFT] = aeBVtoRC[alCAMERAINFO_BV_LEFT][0];
    paeM33[alCAMERAINFO_BV_RIGHT] = aeBVtoRC[alCAMERAINFO_BV_RIGHT][0];
    paeM33[alCAMERAINFO_BV_FRONT] = aeBVtoRC[alCAMERAINFO_BV_FRONT][0];
    paeM33[alCAMERAINFO_BV_BACK] = aeBVtoRC[alCAMERAINFO_BV_BACK][0];

    AVM3D_SetStitchLineInfo(a_ptAVMCfg, &tStitchLineCfg);
    AVM3D_Set3DCurveProjectionInfo(a_ptAVMCfg, &tCurveModel);

	// 曲面2 的設定
	aeCurvePara[0] = a_ptAVMCfg->eCurve2SurfaceA;
	aeCurvePara[1] = a_ptAVMCfg->eCurve2SurfaceB;
	aeCurvePara[2] = a_ptAVMCfg->eCurve2SurfaceC;
	aeCurvePara[3] = a_ptAVMCfg->eCurve2SurfaceD;
	aeCurvePara[4] = a_ptAVMCfg->eCurve2SurfaceE;
	aeCurvePara[5] = a_ptAVMCfg->eCurve2SurfaceF;
	aeCurvePara[6] = a_ptAVMCfg->fCurve2CenterX;
	aeCurvePara[7] = a_ptAVMCfg->fCurve2CenterY;
	aeCurvePara[8] = a_ptAVMCfg->fCurve2CenterZ;
	AVM3D_Set3DCurveProjectionInfoByArray(aeCurvePara, &tCurveModelTmp);

    a_ptAVM3D_LUT->tDestAreaSize = a_ptAVMCfg->tDestAreaSize;
    a_ptAVM3D_LUT->tDestStartPoint = a_ptAVMCfg->tDestStartPoint;
    a_ptAVM3D_LUT->tDestImageBufferSize = a_ptAVMCfg->tDestImageBufferSize;

    // set VC FM by Cfg
    {
    
    }

    // Copy VC RT Information to AVM 3D parameter
    {
        // VCtoBV
        aeVCtoBV[1][0] = a_ptAVMPara->aeRotationMatrixVC[1][0];
        aeVCtoBV[1][1] = a_ptAVMPara->aeRotationMatrixVC[1][1];
        aeVCtoBV[1][2] = a_ptAVMPara->aeRotationMatrixVC[1][2];
        aeVCtoBV[1][4] = a_ptAVMPara->aeRotationMatrixVC[1][3];
        aeVCtoBV[1][5] = a_ptAVMPara->aeRotationMatrixVC[1][4];
        aeVCtoBV[1][6] = a_ptAVMPara->aeRotationMatrixVC[1][5];
        aeVCtoBV[1][8] = a_ptAVMPara->aeRotationMatrixVC[1][6];
        aeVCtoBV[1][9] = a_ptAVMPara->aeRotationMatrixVC[1][7];
        aeVCtoBV[1][10] = a_ptAVMPara->aeRotationMatrixVC[1][8];

        aeVCtoBV[1][3] = a_ptAVMPara->aeTranslationMatrixVC[1][0];
        aeVCtoBV[1][7] = a_ptAVMPara->aeTranslationMatrixVC[1][1];
        aeVCtoBV[1][11] = a_ptAVMPara->aeTranslationMatrixVC[1][2];
        aeVCtoBV[1][12] = 0.0;
        aeVCtoBV[1][13] = 0.0;
        aeVCtoBV[1][14] = 0.0;
        aeVCtoBV[1][15] = 1.0;

        // BVtoVC
        aeVCtoBV[0][0] = a_ptAVMPara->aeRotationMatrixVC[0][0];
        aeVCtoBV[0][1] = a_ptAVMPara->aeRotationMatrixVC[0][1];
        aeVCtoBV[0][2] = a_ptAVMPara->aeRotationMatrixVC[0][2];
        aeVCtoBV[0][4] = a_ptAVMPara->aeRotationMatrixVC[0][3];
        aeVCtoBV[0][5] = a_ptAVMPara->aeRotationMatrixVC[0][4];
        aeVCtoBV[0][6] = a_ptAVMPara->aeRotationMatrixVC[0][5];
        aeVCtoBV[0][8] = a_ptAVMPara->aeRotationMatrixVC[0][6];
        aeVCtoBV[0][9] = a_ptAVMPara->aeRotationMatrixVC[0][7];
        aeVCtoBV[0][10] = a_ptAVMPara->aeRotationMatrixVC[0][8];
    }


    for(ucCameraIndex = 0; ucCameraIndex < 4; ucCameraIndex++)
    {
        a_ptAVM3D_LUT->atSrcImageSize[ucCameraIndex].lX = a_ptFisheyeModel[ucCameraIndex].uwSrcWidth;
        a_ptAVM3D_LUT->atSrcImageSize[ucCameraIndex].lY = a_ptFisheyeModel[ucCameraIndex].uwSrcHeight;
    }

    a_ptAVM3D_LUT->ulLUTDataSize = a_ptAVM3D_LUT->tDestAreaSize.lX * a_ptAVM3D_LUT->tDestAreaSize.lY * sizeof(UINT64);
	if(a_ptAVM3D_LUT->pullTable != NULL)
	{
		free(a_ptAVM3D_LUT->pullTable);
	}
    a_ptAVM3D_LUT->pullTable = (UINT64*) malloc(a_ptAVM3D_LUT->ulLUTDataSize);

    {
        register INT32 lDestIntX1, lDestIntY1;
        register INT32 lDestDecX1, lDestDecY1;
        register INT32 lDestIntX2, lDestIntY2;
        register INT32 lDestDecX2, lDestDecY2;

        FLOAT64 eBVPosX = 0, eBVPosY = 0, eBVPosZ = 0;
        FLOAT64 eVCUnDistX, eVCUnDistY, eVCUnDistZ;
        FLOAT64 eBVCX1, eBVCY1, eBVCZ1; 
        FLOAT64 eBVX_Around, eBVY_Around, eBVZ_Around;
        BOOL bView1Enabled = 0;
        BOOL bView2Enabled = 0;

        FLOAT64 eScalingX = a_ptAVMCfg->eScalingX;
        FLOAT64 eScalingY = a_ptAVMCfg->eScalingY;
        INT32 lOffsetX = a_ptAVMCfg->lOffsetX;
        INT32 lOffsetY = a_ptAVMCfg->lOffsetY;

        FLOAT32 afWeighting[2];
        UINT8 aucViewIndex[2];
        UINT8 aucView1Weighting = 0;

        //FLOAT64 eFocalLength, eTheta, ePhi;

        memset(a_ptAVM3D_LUT->pullTable, 0, a_ptAVM3D_LUT->ulLUTDataSize);

        ulPixelIndex = 0;
  
        
        ulFMCenterX = (a_ptAVMPara->ptFisheyeModelVC->uwSrcWidth >> 1);
        ulFMCenterY = (a_ptAVMPara->ptFisheyeModelVC->uwSrcHeight >> 1);


        ulVCCenterX = (a_ptAVMCfg->tDestImageBufferSize.lX >> 1);
        ulVCCenterY = (a_ptAVMCfg->tDestImageBufferSize.lY >> 1);

        //eVC_Focal = 2500;
        for(lY = 0; lY < a_ptAVMCfg->tDestAreaSize.lY; lY++)
        {
            ulPixelIndex = lY * a_ptAVMCfg->tDestAreaSize.lX;
            for(lX = 0; lX < a_ptAVMCfg->tDestAreaSize.lX; lX++, ulPixelIndex++)
            {  
#if 0 // for debug test
                if (lX == 648 && lY == 134 && a_lViewIndex == 2)
                { // for test
                    lY = lY;
                }
#endif

                if(a_ptAVMCfg->lMirror == 1)
                {
                    eScaledX = a_ptAVMCfg->tDestAreaSize.lX - lX - 1;
                }
                else
                {
                    eScaledX = lX;
                }

                eScaledX = eScaledX + a_ptAVMCfg->tDestStartPoint.lX;
                eScaledY = lY + a_ptAVMCfg->tDestStartPoint.lY;

                eScaledX = (eScaledX - ulVCCenterX + lOffsetX) / eScalingX + ulVCCenterX; 
                eScaledY = (eScaledY - ulVCCenterY + lOffsetY) / eScalingY + ulVCCenterY; 

                // 轉換到魚眼模型的解析度 (從AVM3D DEST圖片轉成 魚眼模型格式)
                if (ulFMCenterX != ulVCCenterX || ulFMCenterY != ulVCCenterY)
                {
#if VC_FM_SCALE == 1
                    eScaledX = (eScaledX - ulVCCenterX) / ulVCCenterX * (ulFMCenterX) + (ulFMCenterX);
                    eScaledY = (eScaledY - ulVCCenterY) / ulVCCenterY * (ulFMCenterY) + (ulFMCenterY);
#else
                    eScaledX = (eScaledX - ulVCCenterX) + (ulFMCenterX);
                    eScaledY = (eScaledY - ulVCCenterY) + (ulFMCenterY);
#endif
                }

                // 將虛擬平面的 2D 座標，投影到虛擬相機 3D 球面座標 (mm)
                alFM_v2_1_Distorted2Undistorted_Sphere(a_ptAVMPara->ptFisheyeModelVC, eScaledX, eScaledY, &eVCUnDistX, &eVCUnDistY, &eVCUnDistZ);

                // (1) 旋轉到鏡頭向下的座標，且 BV Camera 位於 (X, Y ,Z) = (0, 0, 0);
                AVM3D_CoordinatesTransform3D(aeVCtoBV[1], eVCUnDistX, eVCUnDistY, eVCUnDistZ, &eBVCX1, &eBVCY1, &eBVCZ1);


				if(a_ptAVMCfg->lCURVE2_FLAG)
				{
					// (2.1) 將(1)得到的座標，重新投影到曲面的座標
					AVM3D_Projection3DModelCal(&(tCurveModelTmp), a_ptAVMCfg->lVirtualCameraPosX, a_ptAVMCfg->lVirtualCameraPosY, a_ptAVMCfg->lVirtualCameraPosZ, 
						eBVCX1, eBVCY1, eBVCZ1, &aeP1[0], &aeP1[1], &aeP1[2]);

					aeCenter[0] = 0; aeCenter[1] = 0;
					
                    aeCenter[2] = a_ptAVMCfg->lCurve2ProjCenZ; //(a_ptAVMCfg->lHeightLimit) ? -a_ptAVMCfg->lHeightLimit : a_ptAVMCfg->lVirtualCameraPosZ;

					// (2.2) project again 
					AVM3D_Projection3DModelCal(&(tCurveModel), aeCenter[0], aeCenter[1], aeCenter[2], 
						aeP1[0], aeP1[1], aeP1[2], &eBVPosX, &eBVPosY, &eBVPosZ);
				}
				else
				{	// 只對碗公curve 做投影

					// (2) 將(1)得到的座標，重新投影到曲面的座標
					AVM3D_Projection3DModelCal(&(tCurveModel), a_ptAVMCfg->lVirtualCameraPosX, a_ptAVMCfg->lVirtualCameraPosY, a_ptAVMCfg->lVirtualCameraPosZ, 
						eBVCX1, eBVCY1, eBVCZ1, &eBVPosX, &eBVPosY, &eBVPosZ);
				
				}

                // for 環形高度限制效果
				if(eBVPosZ + a_ptAVMCfg->lHeightLimit < 0 && a_ptAVMCfg->lHeightLimit)
                {
                    a_ptAVM3D_LUT->pullTable[ulPixelIndex] += ((UINT64)1<<alLUT_v2_SHIFT_ENABLE);
                    continue; // for 環形效果
                }

				// (2.5) 在BV系統上坐旋轉平移 (環場會用到)

				// 取得BV系統上的座標點
				eBVX_Tmp = eBVPosX;
				eBVY_Tmp = eBVPosY;
				eBVZ_Tmp = eBVPosZ;

				// 藉由設定角度及位移算出 在BV座標系上的特製旋轉矩陣(這裡的矩陣也可以在 AVM3D_GenerateM33 算好再讀出來)
				AVM3D_MatrixGeneratorBVTransform(a_ptAVMCfg, RT44Tmp);

				// 特製旋轉矩陣對BV曲面上的點做旋轉平移
				AVM3D_CoordinatesTransform3D(RT44Tmp, eBVX_Tmp, eBVY_Tmp, eBVZ_Tmp, &eBVX_Around, &eBVY_Around, &eBVZ_Around);

				// 取代原本BV曲面座標
				eBVPosX = eBVX_Around;
				eBVPosY = eBVY_Around;
				eBVPosZ = eBVZ_Around;
	
				// (2.5) 在BV系統上坐旋轉平移 (環場會用到)

				// (3) 計算在重疊處的權重
                AVM3D_OverlapWeightCal(eBVPosX, eBVPosY, &tStitchLineCfg, afWeighting, aucViewIndex, a_ptAVMCfg);

                a_ucViewIndex1 = aucViewIndex[0];
                a_ucViewIndex2 = aucViewIndex[1];
#if 1	// 如果a_ucViewIndex1 權重為0 則兩view互換 for FW team 2014 12 23		
				if(afWeighting[0] == 0 &&  afWeighting[1] == 1)
				{
					ucViewIndexBuff = a_ucViewIndex1;
					a_ucViewIndex1 = a_ucViewIndex2;
					a_ucViewIndex2 = ucViewIndexBuff;
					afWeighting[0] = 1;
					afWeighting[1] = 0;
				}
#endif
                aucView1Weighting = (UINT8)(afWeighting[0] * alLUT_v2_AND_WEIGHT);

				/// assign RT44 for BV <> RC
				if(a_ucViewIndex1 != 255 && afWeighting[0] != 0)
				{
					// FOR View 1
					peM33_WtoI = aeBVtoRC[a_ucViewIndex1][0];
					peM33_ItoW = aeBVtoRC[a_ucViewIndex1][1];

					peM33_WtoI[0] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][0];
					peM33_WtoI[1] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][1];
					peM33_WtoI[2] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][2];
					peM33_WtoI[3] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[0][0];

					peM33_WtoI[4] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][3];
					peM33_WtoI[5] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][4];
					peM33_WtoI[6] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][5];
					peM33_WtoI[7] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[0][1];

					peM33_WtoI[8] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][6];
					peM33_WtoI[9] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][7];
					peM33_WtoI[10] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][8];
					peM33_WtoI[11] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[0][2];

					peM33_WtoI[12] = 0;
					peM33_WtoI[13] = 0;
					peM33_WtoI[14] = 0;
					peM33_WtoI[15] = 1;

					peM33_ItoW[0] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][0];
					peM33_ItoW[1] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][1];
					peM33_ItoW[2] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][2];
					peM33_ItoW[3] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[1][0];

					peM33_ItoW[4] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][3];
					peM33_ItoW[5] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][4];
					peM33_ItoW[6] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][5];
					peM33_ItoW[7] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[1][1];

					peM33_ItoW[8] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][6];
					peM33_ItoW[9] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][7];
					peM33_ItoW[10] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][8];
					peM33_ItoW[11] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[1][2];

					peM33_ItoW[12] = 0;
					peM33_ItoW[13] = 0;
					peM33_ItoW[14] = 0;
					peM33_ItoW[15] = 1;
				}

				if(a_ucViewIndex2 != 255 && afWeighting[1] != 0)
				{
					// FOR View 2
					peM33_WtoI = aeBVtoRC[a_ucViewIndex2][0];
					peM33_ItoW = aeBVtoRC[a_ucViewIndex2][1];

					peM33_WtoI[0] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][0];
					peM33_WtoI[1] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][1];
					peM33_WtoI[2] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][2];
					peM33_WtoI[3] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[0][0];

					peM33_WtoI[4] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][3];
					peM33_WtoI[5] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][4];
					peM33_WtoI[6] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][5];
					peM33_WtoI[7] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[0][1];

					peM33_WtoI[8] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][6];
					peM33_WtoI[9] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][7];
					peM33_WtoI[10] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][8];
					peM33_WtoI[11] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[0][2];

					peM33_WtoI[12] = 0;
					peM33_WtoI[13] = 0;
					peM33_WtoI[14] = 0;
					peM33_WtoI[15] = 1;

					peM33_ItoW[0] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][0];
					peM33_ItoW[1] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][1];
					peM33_ItoW[2] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][2];
					peM33_ItoW[3] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[1][0];

					peM33_ItoW[4] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][3];
					peM33_ItoW[5] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][4];
					peM33_ItoW[6] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][5];
					peM33_ItoW[7] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[1][1];

					peM33_ItoW[8] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][6];
					peM33_ItoW[9] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][7];
					peM33_ItoW[10] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][8];
					peM33_ItoW[11] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[1][2];

					peM33_ItoW[12] = 0;
					peM33_ItoW[13] = 0;
					peM33_ItoW[14] = 0;
					peM33_ItoW[15] = 1;
				}
                /// assign RT44

                if(a_ucViewIndex1 != 255 && afWeighting[0] != 0)
                {
                    // AVM3D tansformation BV曲面到RC
                    AVM3D_CoordinatesTransformBVtoRC(paeM33[a_ucViewIndex1], a_ptFisheyeModel + a_ucViewIndex1, eBVPosX, eBVPosY, eBVPosZ, &eDestX1, &eDestY1);

                    //取整數位
                    lDestIntX1 = (INT32)(eDestX1);
                    lDestIntY1 = (INT32)(eDestY1);

                    //取小數位，以3bit儲存
                    lDestDecX1 = (INT32)((eDestX1 - lDestIntX1)*8);
                    lDestDecY1 = (INT32)((eDestY1 - lDestIntY1)*8);

                    assert(lDestDecX1 < (1<<3) && lDestDecY1 < (1<<3));

                    // 避免超出原影像邊界
                    if(lDestIntX1 > 0 && lDestIntY1 > 0 && lDestIntX1 < a_ptAVM3D_LUT->atSrcImageSize[a_ucViewIndex1].lX - 1 && lDestIntY1 < a_ptAVM3D_LUT->atSrcImageSize[a_ucViewIndex1].lY - 1)
                    {
                        a_ptAVM3D_LUT->pullTable[ulPixelIndex] = (a_ucViewIndex1<<alLUT_v2_SHIFT_CAM_1) + ((lDestIntY1 * a_ptAVM3D_LUT->atSrcImageSize[a_ucViewIndex1].lX + lDestIntX1)<<alLUT_v2_SHIFT_OFFSET_1) + (lDestDecX1<<alLUT_v2_SHIFT_DECX_1) + (lDestDecY1<<alLUT_v2_SHIFT_DECY_1);
                        bView1Enabled = TRUE;
                    }
                    else
                    {
                        bView1Enabled = FALSE;
                    }
                }
                else
                {
                    bView1Enabled = FALSE;
                }
                    
                if(a_ucViewIndex2 != 255 && afWeighting[1] != 0)
                {

	                // AVM3D tansformation BV曲面到RC
                    AVM3D_CoordinatesTransformBVtoRC(paeM33[a_ucViewIndex2], a_ptFisheyeModel + a_ucViewIndex2, eBVPosX, eBVPosY, eBVPosZ, &eDestX2, &eDestY2);

                    //取整數位
                    lDestIntX2 = (INT32)(eDestX2);
                    lDestIntY2 = (INT32)(eDestY2);

                    //取小數位，以3bit儲存
                    lDestDecX2 = (INT32)((eDestX2 - lDestIntX2)*8);
                    lDestDecY2 = (INT32)((eDestY2 - lDestIntY2)*8);

                    assert(lDestDecX2 < (1<<3) && lDestDecY2 < (1<<3));

                    // 避免超出原影像邊界
                    if(lDestIntX2 > 0 && lDestIntY2 > 0 && lDestIntX2 < a_ptAVM3D_LUT->atSrcImageSize[a_ucViewIndex2].lX - 1 && lDestIntY2 < a_ptAVM3D_LUT->atSrcImageSize[a_ucViewIndex2].lY - 1)
                    {
                        a_ptAVM3D_LUT->pullTable[ulPixelIndex] += ((UINT64)a_ucViewIndex2<<alLUT_v2_SHIFT_CAM_2) 
                            + ((UINT64)(lDestIntY2 * a_ptAVM3D_LUT->atSrcImageSize[a_ucViewIndex2].lX + lDestIntX2)<<alLUT_v2_SHIFT_OFFSET_2) 
                            + ((UINT64)lDestDecX2<<alLUT_v2_SHIFT_DECX_2) + ((UINT64)lDestDecY2<<alLUT_v2_SHIFT_DECY_2);
                        bView2Enabled = TRUE;
                    }
                    else
                    {
                        bView2Enabled = FALSE;
                    }
                }
                else
                {
                    bView2Enabled = FALSE;
                }
                

                if(bView1Enabled && bView2Enabled)
                {
                    a_ptAVM3D_LUT->pullTable[ulPixelIndex] += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(aucView1Weighting)<<alLUT_v2_SHIFT_WEIGHT);
                }
                else if(bView1Enabled && !bView2Enabled)
                {
                    a_ptAVM3D_LUT->pullTable[ulPixelIndex] += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(alLUT_v2_AND_WEIGHT)<<alLUT_v2_SHIFT_WEIGHT);
                }
                else if(!bView1Enabled && bView2Enabled)
                {
                    a_ptAVM3D_LUT->pullTable[ulPixelIndex] += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(0)<<alLUT_v2_SHIFT_WEIGHT);
                }
                else 
                {
                    a_ptAVM3D_LUT->pullTable[ulPixelIndex] += ((UINT64)1<<alLUT_v2_SHIFT_ENABLE);
                }

#if 0	// for debug
				if(a_ucViewIndex1 == 3 && a_lViewIndex == 3 && afWeighting[0] == 1)
				{
					TableTmpBug = 0;
					TableTmpBug = a_ptAVM3D_LUT->pullTable[ulPixelIndex] << 6;
					TableTmpBug = TableTmpBug >> 35;
					if(TableTmpBug !=0)
					{
						TableTmpBug = TableTmpBug;
					}
					TableTmpBug = 0;
				}

				if(a_lViewIndex == 3 && lY < 181)
				{
					TableTmpBug = 0;
					if(a_ucViewIndex2 != 255 || afWeighting[0] != 1 || a_ucViewIndex1 != 3)
					{
						TableTmpBug = TableTmpBug;
					}
					TableTmpBug = 0;
				}
#endif
            }
        }
    }
}

////////////////////////////////////////////////////

void AVM3D_World2DestImage(
	INT32 a_lViewIndex,
    alAVM3D_ParamsSingle *a_ptAVMPara,
    alAVM3D_Cfg *a_ptAVMCfg,
    FLOAT64 a_eSrcX,
    FLOAT64 a_eSrcY,
    FLOAT64 a_eSrcZ,
    FLOAT64 *a_peDestX,
    FLOAT64 *a_peDestY
)
{
    FLOAT64 aeBVtoVC[16] = {0};
	FLOAT64 eVCWorldX, eVCWorldY, eVCWorldZ, eDestX, eDestY, eScaledX = 0, eScaledY = 0;
	FLOAT64 eScalingX = 0, eScalingY = 0;
	INT32 lVCCenterX = 0, lVCCenterY = 0, lFMCenterX = 0, lFMCenterY = 0;
	alAVM3D_ParamsSingle *ptAVMParaCurr = NULL;
	alAVM3D_CfgSingleView *a_ptAVMCfgCurr = NULL;
	
    // a_ptAVMPara[a_lViewIndex].ptFisheyeModelVC->

    lFMCenterX = (a_ptAVMPara[a_lViewIndex].ptFisheyeModelVC->uwSrcWidth >> 1);
    lFMCenterY = (a_ptAVMPara[a_lViewIndex].ptFisheyeModelVC->uwSrcHeight >> 1);
	ptAVMParaCurr = &a_ptAVMPara[a_lViewIndex];
	a_ptAVMCfgCurr = &a_ptAVMCfg->atViewCfg[a_lViewIndex];
	
	eScalingX = a_ptAVMCfgCurr->eScalingX;
    eScalingY = a_ptAVMCfgCurr->eScalingY;
	lVCCenterX = a_ptAVMCfgCurr->tDestImageBufferSize.lX>>1;
	lVCCenterY = a_ptAVMCfgCurr->tDestImageBufferSize.lY>>1;
	
	// Copy BV2VC RT Information form AVM 3D parameter to aeBVtoVC Matrix
    {
        // BVtoVC
#if 1   // by assign
		// rotation
        aeBVtoVC[0] = ptAVMParaCurr->aeRotationMatrixVC[0][0];
        aeBVtoVC[1] = ptAVMParaCurr->aeRotationMatrixVC[0][1];
        aeBVtoVC[2] = ptAVMParaCurr->aeRotationMatrixVC[0][2];
        aeBVtoVC[4] = ptAVMParaCurr->aeRotationMatrixVC[0][3];
        aeBVtoVC[5] = ptAVMParaCurr->aeRotationMatrixVC[0][4];
        aeBVtoVC[6] = ptAVMParaCurr->aeRotationMatrixVC[0][5];
        aeBVtoVC[8] = ptAVMParaCurr->aeRotationMatrixVC[0][6];
        aeBVtoVC[9] = ptAVMParaCurr->aeRotationMatrixVC[0][7];
        aeBVtoVC[10] = ptAVMParaCurr->aeRotationMatrixVC[0][8];
		
		// translation
		aeBVtoVC[3] = ptAVMParaCurr->aeTranslationMatrixVC[0][0];
        aeBVtoVC[7] = ptAVMParaCurr->aeTranslationMatrixVC[0][1];
        aeBVtoVC[11] = ptAVMParaCurr->aeTranslationMatrixVC[0][2];
        
		aeBVtoVC[12] = 0.0;
        aeBVtoVC[13] = 0.0;
        aeBVtoVC[14] = 0.0;
        aeBVtoVC[15] = 1.0;

#else // by inverse
        // rotation
        aeVCtoBV[0] = ptAVMParaCurr->aeRotationMatrixVC[1][0];
        aeVCtoBV[1] = ptAVMParaCurr->aeRotationMatrixVC[1][1];
        aeVCtoBV[2] = ptAVMParaCurr->aeRotationMatrixVC[1][2];
        aeVCtoBV[4] = ptAVMParaCurr->aeRotationMatrixVC[1][3];
        aeVCtoBV[5] = ptAVMParaCurr->aeRotationMatrixVC[1][4];
        aeVCtoBV[6] = ptAVMParaCurr->aeRotationMatrixVC[1][5];
        aeVCtoBV[8] = ptAVMParaCurr->aeRotationMatrixVC[1][6];
        aeVCtoBV[9] = ptAVMParaCurr->aeRotationMatrixVC[1][7];
        aeVCtoBV[10] = ptAVMParaCurr->aeRotationMatrixVC[1][8];
		
		// translation
		aeVCtoBV[3] = ptAVMParaCurr->aeTranslationMatrixVC[1][0];
        aeVCtoBV[7] = ptAVMParaCurr->aeTranslationMatrixVC[1][1];
        aeVCtoBV[11] = ptAVMParaCurr->aeTranslationMatrixVC[1][2];
        
		aeVCtoBV[12] = 0.0;
        aeVCtoBV[13] = 0.0;
        aeVCtoBV[14] = 0.0;
        aeVCtoBV[15] = 1.0;

        memcpy(aeBVtoVC, aeVCtoBV, sizeof(FLOAT64)*16);
        alMATRIX_InverseNbyN(aeBVtoVC, 4);
#endif
    }
	
	// (1) 由BV鏡頭旋轉到VC鏡頭的座標   BV Camera 位於 (X, Y ,Z) = (0, 0, 0)
    AVM3D_CoordinatesTransform3D(aeBVtoVC, a_eSrcX, a_eSrcY, a_eSrcZ, &eVCWorldX, &eVCWorldY, &eVCWorldZ);
	
	// (2) 將VC的 3D 座標，轉換到VC 2D 平面座標 (Pixel)
    alFM_v2_1_Undistorted2Distorted_Sphere(a_ptAVMPara[a_lViewIndex].ptFisheyeModelVC, eVCWorldX, eVCWorldY, eVCWorldZ, &eDestX, &eDestY);
	
	// (3) remove offset, scale and mirror effect
    // 轉換到AVM3D DEST圖片的解析度 (從魚眼模型轉成 AVM3D DEST圖片格式)
    if (lFMCenterX != lVCCenterX || lFMCenterY != lVCCenterY)
    {
#if VC_FM_SCALE == 1
        eDestX = (eDestX - lFMCenterX) / lFMCenterX * (lVCCenterX)+(lVCCenterX);
        eDestY = (eDestY - lFMCenterY) / lFMCenterY * (lVCCenterY)+(lVCCenterY);
#else
        eDestX = (eDestX - lFMCenterX) + (lVCCenterX);
        eDestY = (eDestY - lFMCenterY) + (lVCCenterY);
#endif
    }

	*a_peDestX = (eDestX - lVCCenterX)*eScalingX + lVCCenterX - a_ptAVMCfgCurr->lOffsetX;
	*a_peDestY = (eDestY - lVCCenterY)*eScalingY + lVCCenterY - a_ptAVMCfgCurr->lOffsetY;
	
	if(a_ptAVMCfgCurr->lMirror == 1)
	{
		*a_peDestX = a_ptAVMCfgCurr->tDestAreaSize.lX - *a_peDestX - 1;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_FreeBuffer(alLUT_v2_Def * a_ptAVM3D_LUT, alPartLUT_v2_Def ** a_ptAVM3D_PartLUT)
{
    if(a_ptAVM3D_LUT != NULL)
    {
        if(a_ptAVM3D_LUT->pullTable != NULL)
            free(a_ptAVM3D_LUT->pullTable);
        memset(a_ptAVM3D_LUT, 0x0, sizeof(alLUT_v2_Def));
    }

    if(a_ptAVM3D_PartLUT != NULL)
    {
	    if((*a_ptAVM3D_PartLUT)->lut_data != NULL) 
            free((*a_ptAVM3D_PartLUT)->lut_data);

        free(*a_ptAVM3D_PartLUT);
        (*a_ptAVM3D_PartLUT) = NULL;
    }
}

void DecideParaOfLUT_Linear(alAVM3D_MorphingStruct *a_ptMorphingInfo, alAVM3D_CfgSingleView *a_ptSrcViewPara, alAVM3D_CfgSingleView a_atViewParaMorphing[AVM3D_MAX_VIEW_MORPHING_CNT], alAVM3D_CfgSingleView *a_ptViewParaGap, AVM3D_MorphingLUT *a_ptMorphingLUT)
{
	INT32 lFrameIndex = 0, lCnt;
	FLOAT64 eRatio = 0;

	for(lFrameIndex = 0 ; lFrameIndex < a_ptMorphingLUT->lFrameNum ; lFrameIndex++)
	{
		// static
		a_atViewParaMorphing[lFrameIndex].ucVCFisheyeModel = a_ptSrcViewPara->ucVCFisheyeModel;
		a_atViewParaMorphing[lFrameIndex].lMirror = a_ptSrcViewPara->lMirror;
		a_atViewParaMorphing[lFrameIndex].lStitchLineType = a_ptSrcViewPara->lStitchLineType;
		a_atViewParaMorphing[lFrameIndex].tDestImageBufferSize.lX = a_ptSrcViewPara->tDestImageBufferSize.lX;
		a_atViewParaMorphing[lFrameIndex].tDestImageBufferSize.lY = a_ptSrcViewPara->tDestImageBufferSize.lY;
		a_atViewParaMorphing[lFrameIndex].tDestStartPoint.lX = a_ptSrcViewPara->tDestStartPoint.lX;
		a_atViewParaMorphing[lFrameIndex].tDestStartPoint.lY = a_ptSrcViewPara->tDestStartPoint.lY;
		a_atViewParaMorphing[lFrameIndex].tDestAreaSize.lX = a_ptSrcViewPara->tDestAreaSize.lX;
		a_atViewParaMorphing[lFrameIndex].tDestAreaSize.lY = a_ptSrcViewPara->tDestAreaSize.lY;
		a_atViewParaMorphing[lFrameIndex].lHeightLimit = a_ptSrcViewPara->lHeightLimit;

		a_atViewParaMorphing[lFrameIndex].lLUTGenFlag = a_ptSrcViewPara->lLUTGenFlag;
		a_atViewParaMorphing[lFrameIndex].lCURVE2_FLAG = a_ptSrcViewPara->lCURVE2_FLAG;

		//a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceA = a_ptSrcViewPara->eCurve2SurfaceA;
		//a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceB = a_ptSrcViewPara->eCurve2SurfaceB;
		//a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceC = a_ptSrcViewPara->eCurve2SurfaceC;
		//a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceD = a_ptSrcViewPara->eCurve2SurfaceD;
		//a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceE = a_ptSrcViewPara->eCurve2SurfaceE;
		//a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceF = a_ptSrcViewPara->eCurve2SurfaceF;

		//a_atViewParaMorphing[lFrameIndex].fCurve2CenterX = (FLOAT32)a_ptSrcViewPara->fCurve2CenterX;
		//a_atViewParaMorphing[lFrameIndex].fCurve2CenterY = (FLOAT32)a_ptSrcViewPara->fCurve2CenterY;
		//a_atViewParaMorphing[lFrameIndex].fCurve2CenterZ = (FLOAT32)a_ptSrcViewPara->fCurve2CenterZ;



		eRatio = (FLOAT64)(lFrameIndex+1) / (a_ptMorphingLUT->lFrameNum + 1);
		
		//////
		a_atViewParaMorphing[lFrameIndex].lBlockDistance = (INT32)(a_ptSrcViewPara->lBlockDistance + a_ptViewParaGap->lBlockDistance*eRatio);

		a_atViewParaMorphing[lFrameIndex].lTopViewPosX = (INT32)(a_ptSrcViewPara->lTopViewPosX + a_ptViewParaGap->lTopViewPosX*eRatio);
		a_atViewParaMorphing[lFrameIndex].lTopViewPosY = (INT32)(a_ptSrcViewPara->lTopViewPosY + a_ptViewParaGap->lTopViewPosY*eRatio);
		a_atViewParaMorphing[lFrameIndex].lTopViewPosZ = (INT32)(a_ptSrcViewPara->lTopViewPosZ + a_ptViewParaGap->lTopViewPosZ*eRatio);

		a_atViewParaMorphing[lFrameIndex].fTopViewCustomRoll = (FLOAT32)(a_ptSrcViewPara->fTopViewCustomRoll + a_ptViewParaGap->fTopViewCustomRoll*eRatio);
		a_atViewParaMorphing[lFrameIndex].fTopViewPitch = (FLOAT32)(a_ptSrcViewPara->fTopViewPitch + a_ptViewParaGap->fTopViewPitch*eRatio);
		a_atViewParaMorphing[lFrameIndex].fTopViewYaw = (FLOAT32)(a_ptSrcViewPara->fTopViewYaw + a_ptViewParaGap->fTopViewYaw*eRatio);
		a_atViewParaMorphing[lFrameIndex].fTopViewRoll = (FLOAT32)(a_ptSrcViewPara->fTopViewRoll + a_ptViewParaGap->fTopViewRoll*eRatio);

		a_atViewParaMorphing[lFrameIndex].lVirtualCameraPosX = (INT32)(a_ptSrcViewPara->lVirtualCameraPosX + a_ptViewParaGap->lVirtualCameraPosX*eRatio);
		a_atViewParaMorphing[lFrameIndex].lVirtualCameraPosY = (INT32)(a_ptSrcViewPara->lVirtualCameraPosY + a_ptViewParaGap->lVirtualCameraPosY*eRatio);
		a_atViewParaMorphing[lFrameIndex].lVirtualCameraPosZ = (INT32)(a_ptSrcViewPara->lVirtualCameraPosZ + a_ptViewParaGap->lVirtualCameraPosZ*eRatio);

		a_atViewParaMorphing[lFrameIndex].fVirtualCameraCustomRoll = (FLOAT32)(a_ptSrcViewPara->fVirtualCameraCustomRoll + a_ptViewParaGap->fVirtualCameraCustomRoll*eRatio);
		a_atViewParaMorphing[lFrameIndex].fVirtualCameraPitch = (FLOAT32)(a_ptSrcViewPara->fVirtualCameraPitch + a_ptViewParaGap->fVirtualCameraPitch*eRatio);
		a_atViewParaMorphing[lFrameIndex].fVirtualCameraYaw = (FLOAT32)(a_ptSrcViewPara->fVirtualCameraYaw + a_ptViewParaGap->fVirtualCameraYaw*eRatio);
		a_atViewParaMorphing[lFrameIndex].fVirtualCameraRoll = (FLOAT32)(a_ptSrcViewPara->fVirtualCameraRoll + a_ptViewParaGap->fVirtualCameraRoll*eRatio);

		a_atViewParaMorphing[lFrameIndex].eScalingX = a_ptSrcViewPara->eScalingX + a_ptViewParaGap->eScalingX*eRatio;
		a_atViewParaMorphing[lFrameIndex].eScalingY = a_ptSrcViewPara->eScalingY + a_ptViewParaGap->eScalingY*eRatio;
		a_atViewParaMorphing[lFrameIndex].lOffsetX = (INT32)(a_ptSrcViewPara->lOffsetX + a_ptViewParaGap->lOffsetX*eRatio);
		a_atViewParaMorphing[lFrameIndex].lOffsetY = (INT32)(a_ptSrcViewPara->lOffsetY + a_ptViewParaGap->lOffsetY*eRatio);

		a_atViewParaMorphing[lFrameIndex].fStitchAngleRange = (FLOAT32)(a_ptSrcViewPara->fStitchAngleRange + a_ptViewParaGap->fStitchAngleRange*eRatio);
		a_atViewParaMorphing[lFrameIndex].eCurveSurfaceA = a_ptSrcViewPara->eCurveSurfaceA + a_ptViewParaGap->eCurveSurfaceA*eRatio;
		a_atViewParaMorphing[lFrameIndex].eCurveSurfaceB = a_ptSrcViewPara->eCurveSurfaceB + a_ptViewParaGap->eCurveSurfaceB*eRatio;
		a_atViewParaMorphing[lFrameIndex].eCurveSurfaceC = a_ptSrcViewPara->eCurveSurfaceC + a_ptViewParaGap->eCurveSurfaceC*eRatio;
		a_atViewParaMorphing[lFrameIndex].eCurveSurfaceD = a_ptSrcViewPara->eCurveSurfaceD + a_ptViewParaGap->eCurveSurfaceD*eRatio;
		a_atViewParaMorphing[lFrameIndex].eCurveSurfaceE = a_ptSrcViewPara->eCurveSurfaceE + a_ptViewParaGap->eCurveSurfaceE*eRatio;
		a_atViewParaMorphing[lFrameIndex].eCurveSurfaceF = a_ptSrcViewPara->eCurveSurfaceF + a_ptViewParaGap->eCurveSurfaceF*eRatio;

		a_atViewParaMorphing[lFrameIndex].fCurveCenterX = (FLOAT32)(a_ptSrcViewPara->fCurveCenterX + a_ptViewParaGap->fCurveCenterX*eRatio);
		a_atViewParaMorphing[lFrameIndex].fCurveCenterY = (FLOAT32)(a_ptSrcViewPara->fCurveCenterY + a_ptViewParaGap->fCurveCenterY*eRatio);
		a_atViewParaMorphing[lFrameIndex].fCurveCenterZ = (FLOAT32)(a_ptSrcViewPara->fCurveCenterZ + a_ptViewParaGap->fCurveCenterZ*eRatio);

        a_atViewParaMorphing[lFrameIndex].lCurve2ProjCenZ = alROUND(a_ptSrcViewPara->lCurve2ProjCenZ + a_ptViewParaGap->lCurve2ProjCenZ*eRatio);
        a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceA = a_ptSrcViewPara->eCurve2SurfaceA + a_ptViewParaGap->eCurve2SurfaceA*eRatio;
        a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceB = a_ptSrcViewPara->eCurve2SurfaceB + a_ptViewParaGap->eCurve2SurfaceB*eRatio;
        a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceC = a_ptSrcViewPara->eCurve2SurfaceC + a_ptViewParaGap->eCurve2SurfaceC*eRatio;
        a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceD = a_ptSrcViewPara->eCurve2SurfaceD + a_ptViewParaGap->eCurve2SurfaceD*eRatio;
        a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceE = a_ptSrcViewPara->eCurve2SurfaceE + a_ptViewParaGap->eCurve2SurfaceE*eRatio;
        a_atViewParaMorphing[lFrameIndex].eCurve2SurfaceF = a_ptSrcViewPara->eCurve2SurfaceF + a_ptViewParaGap->eCurve2SurfaceF*eRatio;

        a_atViewParaMorphing[lFrameIndex].fCurve2CenterX = (FLOAT32)(a_ptSrcViewPara->fCurve2CenterX + a_ptViewParaGap->fCurve2CenterX*eRatio);
        a_atViewParaMorphing[lFrameIndex].fCurve2CenterY = (FLOAT32)(a_ptSrcViewPara->fCurve2CenterY + a_ptViewParaGap->fCurve2CenterY*eRatio);
        a_atViewParaMorphing[lFrameIndex].fCurve2CenterZ = (FLOAT32)(a_ptSrcViewPara->fCurve2CenterZ + a_ptViewParaGap->fCurve2CenterZ*eRatio);

        //a_atViewParaMorphing[lFrameIndex].lHeightLimit = (INT32)(a_ptSrcViewPara->lHeightLimit + a_ptViewParaGap->lHeightLimit*eRatio);

		for(lCnt = 0 ; lCnt < 4 ; lCnt++)
		{
			a_atViewParaMorphing[lFrameIndex].atStitchLineStart[lCnt].lX = (INT32)(a_ptSrcViewPara->atStitchLineStart[lCnt].lX + a_ptViewParaGap->atStitchLineStart[lCnt].lX*eRatio);
			a_atViewParaMorphing[lFrameIndex].atStitchLineStart[lCnt].lY = (INT32)(a_ptSrcViewPara->atStitchLineStart[lCnt].lY + a_ptViewParaGap->atStitchLineStart[lCnt].lY*eRatio);
			
			a_atViewParaMorphing[lFrameIndex].afStitchLineAngle[lCnt] = (FLOAT32)(a_ptSrcViewPara->afStitchLineAngle[lCnt] + a_ptViewParaGap->afStitchLineAngle[lCnt]*eRatio);

			a_atViewParaMorphing[lFrameIndex].atCornerPoint[lCnt].lX = (INT32)(a_ptSrcViewPara->atCornerPoint[lCnt].lX + a_ptViewParaGap->atCornerPoint[lCnt].lX*eRatio);
			a_atViewParaMorphing[lFrameIndex].atCornerPoint[lCnt].lY = (INT32)(a_ptSrcViewPara->atCornerPoint[lCnt].lY + a_ptViewParaGap->atCornerPoint[lCnt].lY*eRatio);

			// for overlap rgion
			a_atViewParaMorphing[lFrameIndex].tOverlapLoadCfg.alDistanceCurveA[lCnt][0] = (INT32)(a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveA[lCnt][0] + a_ptViewParaGap->tOverlapLoadCfg.alDistanceCurveA[lCnt][0]*eRatio);
			a_atViewParaMorphing[lFrameIndex].tOverlapLoadCfg.alDistanceCurveA[lCnt][1] = (INT32)(a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveA[lCnt][1] + a_ptViewParaGap->tOverlapLoadCfg.alDistanceCurveA[lCnt][1]*eRatio);

			a_atViewParaMorphing[lFrameIndex].tOverlapLoadCfg.alDistanceCurveB[lCnt][0] = (INT32)(a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveB[lCnt][0] + a_ptViewParaGap->tOverlapLoadCfg.alDistanceCurveB[lCnt][0]*eRatio);
			a_atViewParaMorphing[lFrameIndex].tOverlapLoadCfg.alDistanceCurveB[lCnt][1] = (INT32)(a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveB[lCnt][1] + a_ptViewParaGap->tOverlapLoadCfg.alDistanceCurveB[lCnt][1]*eRatio);

			a_atViewParaMorphing[lFrameIndex].tOverlapLoadCfg.afCurveALineAngleOffset[lCnt] = (FLOAT32)(a_ptSrcViewPara->tOverlapLoadCfg.afCurveALineAngleOffset[lCnt] + a_ptViewParaGap->tOverlapLoadCfg.afCurveALineAngleOffset[lCnt]*eRatio);
			a_atViewParaMorphing[lFrameIndex].tOverlapLoadCfg.afCurveBLineAngleOffset[lCnt] = (FLOAT32)(a_ptSrcViewPara->tOverlapLoadCfg.afCurveBLineAngleOffset[lCnt] + a_ptViewParaGap->tOverlapLoadCfg.afCurveBLineAngleOffset[lCnt]*eRatio);

		}
		//////
        a_ptMorphingInfo->alMorphingFlagTable[a_ptMorphingLUT->alRefViewIndex[0] * AVM3D_MAX_VIEW_ANGLE_CNT + a_ptMorphingLUT->alRefViewIndex[1]] = a_ptMorphingLUT->lFlag;
        a_ptMorphingInfo->alMorphingFlagTable[a_ptMorphingLUT->alRefViewIndex[1] * AVM3D_MAX_VIEW_ANGLE_CNT + a_ptMorphingLUT->alRefViewIndex[0]] = a_ptMorphingLUT->lFlag;
	}
}

void DecideParaOfLUT(alAVM3D_MorphingStruct *a_ptMorphingInfo, alAVM3D_CfgSingleView *a_ptSrcViewPara, alAVM3D_CfgSingleView a_atViewParaMorphing[AVM3D_MAX_VIEW_MORPHING_CNT], alAVM3D_CfgSingleView *a_ptViewParaGap, INT32 a_lMorphingType, AVM3D_MorphingLUT *a_ptMorphingLUT)
{
	switch(a_lMorphingType)
	{
	case MORPHING_LINEAR: // LINEAR
        DecideParaOfLUT_Linear(a_ptMorphingInfo, a_ptSrcViewPara, a_atViewParaMorphing, a_ptViewParaGap, a_ptMorphingLUT);
	break;

    case MORPHING_CIRCLE: // CIRCLE
		assert(1);	
	break;

    case MORPHING_BEZIER: // BEZIER
		assert(1);	
	break;

	default:
		assert(1);
	break;
	}
}

DoMorphingLUTGenerating(
    alFM_v2_1_Model *a_ptFisheyeModel,
    alCOMMONK_CalibrationParams *a_ptCalibrationData,
    AVM3D_MorphingLUT *a_ptMorphingLUT, 
    alAVM3D_CfgSingleView a_atViewParaMorphing[AVM3D_MAX_VIEW_MORPHING_CNT]
    )
{
	INT32 lIndex = -1;
	alAVM3D_ParamsSingle tAVM3DPara;

	for(lIndex = 0 ; lIndex < a_ptMorphingLUT->lFrameNum ; lIndex++)
	{
		// 設定RT Matrix  >>>> step 1
		AVM3D_GenerateM33(
			99,	// View Index 沒有任何作用
			&tAVM3DPara, 
			&a_atViewParaMorphing[lIndex]
		);

		// 產生兩視角間的每個過場LUT	>>>> step 2
		AVM3D_GenerateLUT(
			99,	// View Index 沒有任何作用
			&tAVM3DPara,
			&a_atViewParaMorphing[lIndex],
            a_ptFisheyeModel,
            a_ptCalibrationData,
			a_ptMorphingLUT->a_atMorphing_LUT[lIndex]
		);
	}
}


void AVM3D_MorphingGAPCal(
	alAVM3D_CfgSingleView *a_ptSrcViewPara, 
	alAVM3D_CfgSingleView *a_ptDestViewPara, 
	alAVM3D_CfgSingleView *a_ptParaGap
	)
{
	INT32 lCnt = 0;

	// CALCULATE GAP
	a_ptParaGap->lVirtualCameraPosX = a_ptDestViewPara->lVirtualCameraPosX - a_ptSrcViewPara->lVirtualCameraPosX;
	a_ptParaGap->lVirtualCameraPosY = a_ptDestViewPara->lVirtualCameraPosY - a_ptSrcViewPara->lVirtualCameraPosY;
	a_ptParaGap->lVirtualCameraPosZ = a_ptDestViewPara->lVirtualCameraPosZ - a_ptSrcViewPara->lVirtualCameraPosZ;

	a_ptParaGap->fVirtualCameraCustomRoll = a_ptDestViewPara->fVirtualCameraCustomRoll - a_ptSrcViewPara->fVirtualCameraCustomRoll;
	a_ptParaGap->fVirtualCameraPitch = a_ptDestViewPara->fVirtualCameraPitch - a_ptSrcViewPara->fVirtualCameraPitch;
	a_ptParaGap->fVirtualCameraYaw = a_ptDestViewPara->fVirtualCameraYaw - a_ptSrcViewPara->fVirtualCameraYaw;
	a_ptParaGap->fVirtualCameraRoll = a_ptDestViewPara->fVirtualCameraRoll - a_ptSrcViewPara->fVirtualCameraRoll;

	a_ptParaGap->eScalingX = a_ptDestViewPara->eScalingX - a_ptSrcViewPara->eScalingX;
	a_ptParaGap->eScalingY = a_ptDestViewPara->eScalingY - a_ptSrcViewPara->eScalingY;
	a_ptParaGap->lOffsetX = a_ptDestViewPara->lOffsetX - a_ptSrcViewPara->lOffsetX;
	a_ptParaGap->lOffsetY = a_ptDestViewPara->lOffsetY - a_ptSrcViewPara->lOffsetY;

	a_ptParaGap->fStitchAngleRange = a_ptDestViewPara->fStitchAngleRange - a_ptSrcViewPara->fStitchAngleRange;
	a_ptParaGap->eCurveSurfaceA = a_ptDestViewPara->eCurveSurfaceA - a_ptSrcViewPara->eCurveSurfaceA;
	a_ptParaGap->eCurveSurfaceB = a_ptDestViewPara->eCurveSurfaceB - a_ptSrcViewPara->eCurveSurfaceB;
	a_ptParaGap->eCurveSurfaceC = a_ptDestViewPara->eCurveSurfaceC - a_ptSrcViewPara->eCurveSurfaceC;
	a_ptParaGap->eCurveSurfaceD = a_ptDestViewPara->eCurveSurfaceD - a_ptSrcViewPara->eCurveSurfaceD;
	a_ptParaGap->eCurveSurfaceE = a_ptDestViewPara->eCurveSurfaceE - a_ptSrcViewPara->eCurveSurfaceE;
	a_ptParaGap->eCurveSurfaceF = a_ptDestViewPara->eCurveSurfaceF - a_ptSrcViewPara->eCurveSurfaceF;

	a_ptParaGap->fCurveCenterX = a_ptDestViewPara->fCurveCenterX - a_ptSrcViewPara->fCurveCenterX;
	a_ptParaGap->fCurveCenterY = a_ptDestViewPara->fCurveCenterY - a_ptSrcViewPara->fCurveCenterY;
	a_ptParaGap->fCurveCenterZ = a_ptDestViewPara->fCurveCenterZ - a_ptSrcViewPara->fCurveCenterZ;

    a_ptParaGap->lCurve2ProjCenZ = a_ptDestViewPara->lCurve2ProjCenZ - a_ptSrcViewPara->lCurve2ProjCenZ;
    a_ptParaGap->eCurve2SurfaceA = a_ptDestViewPara->eCurve2SurfaceA - a_ptSrcViewPara->eCurve2SurfaceA;
    a_ptParaGap->eCurve2SurfaceB = a_ptDestViewPara->eCurve2SurfaceB - a_ptSrcViewPara->eCurve2SurfaceB;
    a_ptParaGap->eCurve2SurfaceC = a_ptDestViewPara->eCurve2SurfaceC - a_ptSrcViewPara->eCurve2SurfaceC;
    a_ptParaGap->eCurve2SurfaceD = a_ptDestViewPara->eCurve2SurfaceD - a_ptSrcViewPara->eCurve2SurfaceD;
    a_ptParaGap->eCurve2SurfaceE = a_ptDestViewPara->eCurve2SurfaceE - a_ptSrcViewPara->eCurve2SurfaceE;
    a_ptParaGap->eCurve2SurfaceF = a_ptDestViewPara->eCurve2SurfaceF - a_ptSrcViewPara->eCurve2SurfaceF;

    a_ptParaGap->fCurve2CenterX = a_ptDestViewPara->fCurve2CenterX - a_ptSrcViewPara->fCurve2CenterX;
    a_ptParaGap->fCurve2CenterY = a_ptDestViewPara->fCurve2CenterY - a_ptSrcViewPara->fCurve2CenterY;
    a_ptParaGap->fCurve2CenterZ = a_ptDestViewPara->fCurve2CenterZ - a_ptSrcViewPara->fCurve2CenterZ;

    a_ptParaGap->lHeightLimit = a_ptDestViewPara->lHeightLimit - a_ptSrcViewPara->lHeightLimit;

	a_ptParaGap->lTopViewPosX = a_ptDestViewPara->lTopViewPosX - a_ptSrcViewPara->lTopViewPosX;
	a_ptParaGap->lTopViewPosY = a_ptDestViewPara->lTopViewPosY - a_ptSrcViewPara->lTopViewPosY;
	a_ptParaGap->lTopViewPosZ = a_ptDestViewPara->lTopViewPosZ - a_ptSrcViewPara->lTopViewPosZ;

	a_ptParaGap->fTopViewCustomRoll = a_ptDestViewPara->fTopViewCustomRoll - a_ptSrcViewPara->fTopViewCustomRoll;
	a_ptParaGap->fTopViewPitch = a_ptDestViewPara->fTopViewPitch - a_ptSrcViewPara->fTopViewPitch;
	a_ptParaGap->fTopViewYaw = a_ptDestViewPara->fTopViewYaw - a_ptSrcViewPara->fTopViewYaw;
	a_ptParaGap->fTopViewRoll = a_ptDestViewPara->fTopViewRoll - a_ptSrcViewPara->fTopViewRoll;
	a_ptParaGap->lBlockDistance = a_ptDestViewPara->lBlockDistance - a_ptSrcViewPara->lBlockDistance;

	for(lCnt = 0 ; lCnt < 4 ; lCnt++)
	{
		a_ptParaGap->atStitchLineStart[lCnt].lX = a_ptDestViewPara->atStitchLineStart[lCnt].lX - a_ptSrcViewPara->atStitchLineStart[lCnt].lX;
		a_ptParaGap->atStitchLineStart[lCnt].lY = a_ptDestViewPara->atStitchLineStart[lCnt].lY - a_ptSrcViewPara->atStitchLineStart[lCnt].lY;
		
		a_ptParaGap->afStitchLineAngle[lCnt] = a_ptDestViewPara->afStitchLineAngle[lCnt] - a_ptSrcViewPara->afStitchLineAngle[lCnt];

		a_ptParaGap->atCornerPoint[lCnt].lX = a_ptDestViewPara->atCornerPoint[lCnt].lX - a_ptSrcViewPara->atCornerPoint[lCnt].lX;
		a_ptParaGap->atCornerPoint[lCnt].lY = a_ptDestViewPara->atCornerPoint[lCnt].lY - a_ptSrcViewPara->atCornerPoint[lCnt].lY;

		// for overlap rgion
		a_ptParaGap->tOverlapLoadCfg.alDistanceCurveA[lCnt][0] = a_ptDestViewPara->tOverlapLoadCfg.alDistanceCurveA[lCnt][0] - a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveA[lCnt][0];
		a_ptParaGap->tOverlapLoadCfg.alDistanceCurveA[lCnt][1] = a_ptDestViewPara->tOverlapLoadCfg.alDistanceCurveA[lCnt][1] - a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveA[lCnt][1];

		a_ptParaGap->tOverlapLoadCfg.alDistanceCurveB[lCnt][0] = a_ptDestViewPara->tOverlapLoadCfg.alDistanceCurveB[lCnt][0] - a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveB[lCnt][0];
		a_ptParaGap->tOverlapLoadCfg.alDistanceCurveB[lCnt][1] = a_ptDestViewPara->tOverlapLoadCfg.alDistanceCurveB[lCnt][1] - a_ptSrcViewPara->tOverlapLoadCfg.alDistanceCurveB[lCnt][1];

		a_ptParaGap->tOverlapLoadCfg.afCurveALineAngleOffset[lCnt] = a_ptDestViewPara->tOverlapLoadCfg.afCurveALineAngleOffset[lCnt] - a_ptSrcViewPara->tOverlapLoadCfg.afCurveALineAngleOffset[lCnt];
		a_ptParaGap->tOverlapLoadCfg.afCurveBLineAngleOffset[lCnt] = a_ptDestViewPara->tOverlapLoadCfg.afCurveBLineAngleOffset[lCnt] - a_ptSrcViewPara->tOverlapLoadCfg.afCurveBLineAngleOffset[lCnt];
	}
}


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
)
{
	INT32 lSrcIndex = -1, lDestIndex = -1, lAVM3DViewCnt = -1, lCnt, lEqual;
	alAVM3D_CfgSingleView tParameterGap;
	alAVM3D_CfgSingleView atViewParaMorphing[AVM3D_MAX_VIEW_MORPHING_CNT];

	a_ptMorphingLUT->lFlag = a_lMorphingLUTFlag;
	a_ptMorphingLUT->lFrameNum = a_lMorphingLUTNum;
	
    lAVM3DViewCnt = a_ptAVM3D_tCfg->lViewCnt;

	// get src and dest view index
	for(lCnt = 0 ; lCnt < lAVM3DViewCnt ; lCnt++)
	{
        lEqual = memcmp(a_ptSrcViewPara->acName, a_ptAVM3D_tCfg->atViewCfg[lCnt].acName, sizeof(a_ptSrcViewPara->acName));
		if(!lEqual)
		{
			lSrcIndex = lCnt;
		}

        lEqual = memcmp(a_ptDestViewPara->acName, a_ptAVM3D_tCfg->atViewCfg[lCnt].acName, sizeof(a_ptDestViewPara->acName));
		if(!lEqual)
		{
			lDestIndex = lCnt;
		}
	}

	assert(lSrcIndex >= 0 && lDestIndex >= 0);	

	if(lDestIndex > lSrcIndex)
	{	// forward

		a_ptMorphingLUT->alRefViewIndex[0] = lSrcIndex;
		a_ptMorphingLUT->alRefViewIndex[1] = lDestIndex;

#if	0 // 環場 hard code test
		if(lDestIndex ==6)
		{
			a_ptDestViewPara->fTopViewCustomRoll = 360;
		}
#endif

		// CALCULATE GAP
		AVM3D_MorphingGAPCal(a_ptSrcViewPara, a_ptDestViewPara, &tParameterGap);

		// decide each parameter of transform LUT by its type
        DecideParaOfLUT(a_ptMorphingInfo, a_ptSrcViewPara, atViewParaMorphing, &tParameterGap, a_lMorphingType, a_ptMorphingLUT);

		// generate each transform LUT by its parameter
        DoMorphingLUTGenerating(a_ptFisheyeModel, ptCalibrationData, a_ptMorphingLUT, atViewParaMorphing);
	}
	else
	{	// inverse
		// do nothing
		return FALSE;
	}
	return TRUE;
}

void AVM3D_RT_Verify(
    const FLOAT32 a_fBirdsViewMMPP,
    alCOMMONK_CalibrationParams *a_ptCalibrationData,
    alAVM3D_ParamsSingle *a_ptAVMPara,
    alAVM3D_CfgSingleView * a_ptAVMCfg,
    alFM_v2_1_Model * a_ptFisheyeModel,
    alLUT_v2_Def * a_ptAVM3D_LUT,
    UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage
    )
{
    UINT8 a_ucViewIndex1, a_ucViewIndex2, ucViewIndexBuff = 0;
    UINT8 ucCameraIndex = 0;
    AVM3D_StitchLineCfg tStitchLineCfg;
    FLOAT64 aeBVtoRC[COMMONK_NUM_BV_CHANNEL][2][16];
    FLOAT64 *peM33_WtoI = NULL, *peM33_ItoW = NULL;
    INT32 lX = 0, lY = 0;
    FLOAT64 eScaledX, eScaledY;
    UINT32 ulPixelIndex = 0, ulVCCenterX = 0, ulVCCenterY = 0;
    INT32 lImgW = 720, lImgH = 480, aPiclIndex[2] = {0};
    INT32 lSrcImgW = 1280, lSrcImgH = 720;
    FLOAT64 eDestX1, eDestY1;
    FLOAT64 eDestX2, eDestY2;
    register INT32 lDestIntX1, lDestIntY1;
    register INT32 lDestDecX1, lDestDecY1;
    register INT32 lDestIntX2, lDestIntY2;
    register INT32 lDestDecX2, lDestDecY2;
    FLOAT64 eBVPosX = 0, eBVPosY = 0, eBVPosZ = 0;
    FLOAT64 eBVX_Around = 0, eBVY_Around = 0, eBVZ_Around = 0;
    BOOL bView1Enabled = 0, bView2Enabled = 0;
    FLOAT64 eScalingX = 0, eScalingY = 0;
    INT32 lOffsetX = 0, lOffsetY = 0;
    FLOAT32 afWeighting[2], fMMPP = 0;
    UINT8 aucViewIndex[2], aucView1Weighting = 0;
    FLOAT64* paeM33[4], aeY[3] = { 0 };
    IplImage *ptPicGray = NULL;
    UINT8 *pucBVImg = NULL;

    pucBVImg = (UINT8 *)malloc(a_ptAVM3D_LUT->tDestImageBufferSize.lX * a_ptAVM3D_LUT->tDestImageBufferSize.lY * sizeof(UINT8));
    ptPicGray = cvCreateImage(cvSize(lImgW, lImgH), IPL_DEPTH_8U, 1);

    paeM33[alCAMERAINFO_BV_LEFT] = aeBVtoRC[alCAMERAINFO_BV_LEFT][0];
    paeM33[alCAMERAINFO_BV_RIGHT] = aeBVtoRC[alCAMERAINFO_BV_RIGHT][0];
    paeM33[alCAMERAINFO_BV_FRONT] = aeBVtoRC[alCAMERAINFO_BV_FRONT][0];
    paeM33[alCAMERAINFO_BV_BACK] = aeBVtoRC[alCAMERAINFO_BV_BACK][0];

    AVM3D_SetStitchLineInfo(a_ptAVMCfg, &tStitchLineCfg);

#if 0
    eScalingX = 1;
    eScalingY = 1;
    lOffsetX = -640;
    lOffsetY = -360;
#else
    eScalingX = 1;
    eScalingY = 1;
    lOffsetX = 0;
    lOffsetY = 0;
#endif

    ulPixelIndex = 0;
    
#if 0   // 魚眼 影像中心
    ulVCCenterX = (a_ptAVMPara->ptFisheyeModelVC->uwSrcWidth >> 1);
    ulVCCenterY = (a_ptAVMPara->ptFisheyeModelVC->uwSrcHeight >> 1);
#else // dest 影像中心
    ulVCCenterX = (a_ptAVMCfg->tDestImageBufferSize.lX >> 1);
    ulVCCenterY = (a_ptAVMCfg->tDestImageBufferSize.lY >> 1);
#endif

#if 1 // read AVM2D mmpp
    fMMPP = a_fBirdsViewMMPP;
#else // hard code mmpp
    fMMPP = 20.5459995;
#endif
    for (lY = 0; lY < lImgH; lY++)
    {
        ulPixelIndex = lY * lImgW;
        for (lX = 0; lX < lImgW; lX++, ulPixelIndex++)
        {
            if (lX == 460 && lY == 240)
            { // for test
                lY = lY;
            }

            eScaledX = lX;
            eScaledY = lY;

#if 0  // 原點在 dest 影像左上角
            eScaledX = (eScaledX - ulVCCenterX + lOffsetX) / eScalingX + ulVCCenterX;
            eScaledY = (eScaledY - ulVCCenterY + lOffsetY) / eScalingY + ulVCCenterY;
#else // 原點在 dest 影像中心
            eScaledX = (eScaledX - ulVCCenterX + lOffsetX) / eScalingX;
            eScaledY = (eScaledY - ulVCCenterY + lOffsetY) / eScalingY;
#endif

            // 地面z = 0
            eBVPosX = fMMPP*eScaledX;
            eBVPosY = fMMPP*eScaledY;
            eBVPosZ = 0;

            // (3) 計算在重疊處的權重
            AVM3D_OverlapWeightCal(eBVPosX, eBVPosY, &tStitchLineCfg, afWeighting, aucViewIndex, a_ptAVMCfg);

            a_ucViewIndex1 = aucViewIndex[0];
            a_ucViewIndex2 = aucViewIndex[1];

#if 1	// 如果a_ucViewIndex1 權重為0 則兩view互換 for FW team 2014 12 23		
            if (afWeighting[0] == 0 && afWeighting[1] == 1)
            {
                ucViewIndexBuff = a_ucViewIndex1;
                a_ucViewIndex1 = a_ucViewIndex2;
                a_ucViewIndex2 = ucViewIndexBuff;
                afWeighting[0] = 1;
                afWeighting[1] = 0;
            }
#endif
            aucView1Weighting = (UINT8)(afWeighting[0] * alLUT_v2_AND_WEIGHT);

            /// assign RT44 for BV <> RC
            if (a_ucViewIndex1 != 255 && afWeighting[0] != 0)
            {
                // FOR View 1
                peM33_WtoI = aeBVtoRC[a_ucViewIndex1][0];
                peM33_ItoW = aeBVtoRC[a_ucViewIndex1][1];

                peM33_WtoI[0] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][0];
                peM33_WtoI[1] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][1];
                peM33_WtoI[2] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][2];
                peM33_WtoI[3] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[0][0];

                peM33_WtoI[4] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][3];
                peM33_WtoI[5] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][4];
                peM33_WtoI[6] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][5];
                peM33_WtoI[7] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[0][1];

                peM33_WtoI[8] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][6];
                peM33_WtoI[9] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][7];
                peM33_WtoI[10] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[0][8];
                peM33_WtoI[11] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[0][2];

                peM33_WtoI[12] = 0;
                peM33_WtoI[13] = 0;
                peM33_WtoI[14] = 0;
                peM33_WtoI[15] = 1;

                peM33_ItoW[0] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][0];
                peM33_ItoW[1] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][1];
                peM33_ItoW[2] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][2];
                peM33_ItoW[3] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[1][0];

                peM33_ItoW[4] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][3];
                peM33_ItoW[5] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][4];
                peM33_ItoW[6] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][5];
                peM33_ItoW[7] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[1][1];

                peM33_ItoW[8] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][6];
                peM33_ItoW[9] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][7];
                peM33_ItoW[10] = a_ptCalibrationData[a_ucViewIndex1].aeRotationMatrix[1][8];
                peM33_ItoW[11] = a_ptCalibrationData[a_ucViewIndex1].aeTranslationMatrix[1][2];

                peM33_ItoW[12] = 0;
                peM33_ItoW[13] = 0;
                peM33_ItoW[14] = 0;
                peM33_ItoW[15] = 1;
            }

            if (a_ucViewIndex2 != 255 && afWeighting[1] != 0)
            {
                // FOR View 2
                peM33_WtoI = aeBVtoRC[a_ucViewIndex2][0];
                peM33_ItoW = aeBVtoRC[a_ucViewIndex2][1];

                peM33_WtoI[0] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][0];
                peM33_WtoI[1] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][1];
                peM33_WtoI[2] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][2];
                peM33_WtoI[3] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[0][0];

                peM33_WtoI[4] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][3];
                peM33_WtoI[5] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][4];
                peM33_WtoI[6] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][5];
                peM33_WtoI[7] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[0][1];

                peM33_WtoI[8] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][6];
                peM33_WtoI[9] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][7];
                peM33_WtoI[10] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[0][8];
                peM33_WtoI[11] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[0][2];

                peM33_WtoI[12] = 0;
                peM33_WtoI[13] = 0;
                peM33_WtoI[14] = 0;
                peM33_WtoI[15] = 1;

                peM33_ItoW[0] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][0];
                peM33_ItoW[1] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][1];
                peM33_ItoW[2] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][2];
                peM33_ItoW[3] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[1][0];

                peM33_ItoW[4] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][3];
                peM33_ItoW[5] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][4];
                peM33_ItoW[6] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][5];
                peM33_ItoW[7] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[1][1];

                peM33_ItoW[8] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][6];
                peM33_ItoW[9] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][7];
                peM33_ItoW[10] = a_ptCalibrationData[a_ucViewIndex2].aeRotationMatrix[1][8];
                peM33_ItoW[11] = a_ptCalibrationData[a_ucViewIndex2].aeTranslationMatrix[1][2];

                peM33_ItoW[12] = 0;
                peM33_ItoW[13] = 0;
                peM33_ItoW[14] = 0;
                peM33_ItoW[15] = 1;
            }
            /// assign RT44

            if (a_ucViewIndex1 != 255 && afWeighting[0] != 0)
            {
                // AVM3D tansformation BV曲面到RC
                AVM3D_CoordinatesTransformBVtoRC(paeM33[a_ucViewIndex1], a_ptFisheyeModel + a_ucViewIndex1, eBVPosX, eBVPosY, eBVPosZ, &eDestX1, &eDestY1);

                //取整數位
                lDestIntX1 = (INT32)(eDestX1);
                lDestIntY1 = (INT32)(eDestY1);

                //取小數位，以3bit儲存
                lDestDecX1 = (INT32)((eDestX1 - lDestIntX1) * 8);
                lDestDecY1 = (INT32)((eDestY1 - lDestIntY1) * 8);

                assert(lDestDecX1 < (1 << 3) && lDestDecY1 < (1 << 3));

                // 避免超出原影像邊界
                if (lDestIntX1 > 0 && lDestIntY1 > 0 && lDestIntX1 < lSrcImgW && lDestIntY1 < lSrcImgH)
                {
                    bView1Enabled = TRUE;
                }
                else
                {
                    bView1Enabled = FALSE;
                }
            }
            else
            {
                bView1Enabled = FALSE;
            }

            if (a_ucViewIndex2 != 255 && afWeighting[1] != 0)
            {

                // AVM3D tansformation BV曲面到RC
                AVM3D_CoordinatesTransformBVtoRC(paeM33[a_ucViewIndex2], a_ptFisheyeModel + a_ucViewIndex2, eBVPosX, eBVPosY, eBVPosZ, &eDestX2, &eDestY2);

                //取整數位
                lDestIntX2 = (INT32)(eDestX2);
                lDestIntY2 = (INT32)(eDestY2);

                //取小數位，以3bit儲存
                lDestDecX2 = (INT32)((eDestX2 - lDestIntX2) * 8);
                lDestDecY2 = (INT32)((eDestY2 - lDestIntY2) * 8);

                assert(lDestDecX2 < (1 << 3) && lDestDecY2 < (1 << 3));

                // 避免超出原影像邊界
                if (lDestIntX2 > 0 && lDestIntY2 > 0 && lDestIntX2 < lSrcImgW && lDestIntY2 < lSrcImgH)
                {
                    bView2Enabled = TRUE;
                }
                else
                {
                    bView2Enabled = FALSE;
                }
            }
            else
            {
                bView2Enabled = FALSE;
            }

            // set dest image Y value
            aPiclIndex[0] = lDestIntY1*lSrcImgW + lDestIntX1;
            aPiclIndex[1] = lDestIntY2*lSrcImgW + lDestIntX2;
            if (bView1Enabled && bView2Enabled)
            {
                aeY[0] = a_pucSrcImage[a_ucViewIndex1][aPiclIndex[0] * 2];
                aeY[1] = a_pucSrcImage[a_ucViewIndex2][aPiclIndex[1] * 2];
                aeY[2] = aeY[0] * afWeighting[0] + aeY[1] * afWeighting[1];
            }
            else if (bView1Enabled)
            {
                aeY[2] = a_pucSrcImage[a_ucViewIndex1][aPiclIndex[0]*2];
            }
            else
            {
                aeY[2] = 0;
            }
            pucBVImg[ulPixelIndex] = (UINT8)aeY[2];
              

        }
    }

    // LOG IMAGE
    memcpy(ptPicGray->imageData, pucBVImg, sizeof(UINT8)*ptPicGray->imageSize);
    cvSaveImage("AVM3D_RT_TEST.bmp", ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
    free(pucBVImg);
}

void AVM3D_LogDataForAnalyzing(
    alFM_v2_1_Model a_atCameraFM[4],
    alAVM3D_Params *a_ptParams, alAVM3D_Cfg *a_ptCfg
    )
{
    UINT8 ucViewIndex = 0;

    for (ucViewIndex = 0; ucViewIndex < a_ptCfg->lViewCnt; ucViewIndex++)
    {
        // 分析光機要的數據
        AVM3D_VIewAnalyzing(
            ucViewIndex,
            &a_ptParams->atViewParams[ucViewIndex],
            &a_ptCfg->atViewCfg[ucViewIndex],
            a_atCameraFM
            );
    }
}

void AVM3D_InitialByCfg(alAVM3D_Params *a_ptParams, alAVM3D_Cfg *a_ptCfg, alFM_v2_1_Model a_atFishEyeModel[AVM3D_MAX_VIEW_ANGLE_CNT])
{
    UINT8 ucViewIndex = 0;

    for (ucViewIndex = 0; ucViewIndex < a_ptCfg->lViewCnt; ucViewIndex++)
    {
        // 設定虛擬相機魚眼模型指標
        a_ptParams->atViewParams[ucViewIndex].ptFisheyeModelVC = &a_atFishEyeModel[ucViewIndex];

        // 設定部分parameter(RT Matrix)  
        AVM3D_GenerateM33(
            ucViewIndex,
            &a_ptParams->atViewParams[ucViewIndex],
            &a_ptCfg->atViewCfg[ucViewIndex]
        );
    }
}

/**
  *  @}
  */
