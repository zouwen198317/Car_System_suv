#include <math.h>
#include <assert.h>
#include "CommonK.h"
#include "alMatrix.h"


#if COMMONK_VERIFY_CALIBRATION_LM
#include "levmar.h"

#ifndef LM_DBL_PREC	// for LM
#error Demo program assumes that levmar has been compiled with double precision, see LM_DBL_PREC!
#endif
#endif

#ifndef MAX_PATH
#define MAX_PATH          260
#endif

#define COMMONK_SBV_Y_LIMIT 0 // 1:on 0:off

#if 1
char g_acalBVCAM_FACAUTOK_WorkingFolder[MAX_PATH];
char g_acalBVCAM_FACAUTOK_SourceFolder[MAX_PATH];
char g_acalBVCAM_FACAUTOK_OutputFolder[MAX_PATH];
#endif

#if COMMONK_VERIFY_CALIBRATION_LM
static void COMMONK_JacobianK(FLOAT64 *a_peParameter, FLOAT64 *a_peJac, INT32 a_lParaNum, INT32 a_lDataNum, void *data);
static void COMMONK_GetHomographyByParameter(FLOAT64 *a_paParameter, FLOAT64 a_aeDesignIntrinsicMatrix[9], FLOAT64 a_aeHMatrix[9], UINT8 a_ucMode, INT32 a_lViewNum);
static void COMMONK_PointTrabform(FLOAT64 *a_peParameter, FLOAT64 *a_peResult, INT32 a_lParaNum, INT32 a_lDataNum, void *data);

void COMMONK_JacobianK(FLOAT64 *a_peParameter, FLOAT64 *a_peJac, INT32 a_lParaNum, INT32 a_lDataNum, void *data)
{
    INT32 i, j, lCntX = 0, lCntY = 0, lPointCnt = 0;
    FLOAT64 aeGap[6], aeParaTmp[6];
    FLOAT64 aeH[9], aeHTmp[9], aeImg[3], aeWord[3], eOutX, eOutY, eCurrX, eCurrY;
    alCOMMONK_LM_Struct tLMInfoIn;

    FLOAT64 JacobianOut[48]; // 8*6

    for (i = 0; i < 6; i++)
    {
        aeGap[i] = 0.25;
    }
    aeGap[0] = 0.5;
    aeGap[1] = 0.5;
    aeGap[2] = 0.5;
    aeGap[3] = 1.0;
    aeGap[4] = 1.0;
    aeGap[5] = 1.0;

    memcpy(&tLMInfoIn, data, sizeof(alCOMMONK_LM_Struct));

    COMMONK_GetHomographyByParameter(a_peParameter, tLMInfoIn.aeIntrinsic, aeH, 1, tLMInfoIn.lViewNum);

    for (i = 0; i < a_lDataNum; i += 2)
    {
        lPointCnt = i >> 1;
        aeImg[0] = tLMInfoIn.aeCameraPosX[lPointCnt];
        aeImg[1] = tLMInfoIn.aeCameraPosY[lPointCnt];
        aeImg[2] = 1;
        alMATRIX_Multiplaction(aeH, aeImg, 3, 3, 1, aeWord);

        // 以當下Parameter 算出當下位置的x y
        eOutX = aeWord[0] / aeWord[2];
        eOutY = aeWord[1] / aeWord[2];
        for (j = 0; j < a_lParaNum; j++)
        {
            memcpy(aeParaTmp, a_peParameter, 6 * sizeof(FLOAT64));
            aeParaTmp[j] += aeGap[j];
            COMMONK_GetHomographyByParameter(aeParaTmp, tLMInfoIn.aeIntrinsic, aeHTmp, 1, tLMInfoIn.lViewNum);

            alMATRIX_Multiplaction(aeHTmp, aeImg, 3, 3, 1, aeWord);

            // 對第j個 Parameter 加上delta 後算出的位置
            eCurrX = aeWord[0] / aeWord[2];
            eCurrY = aeWord[1] / aeWord[2];

            // 微分直 = 相減 >>  dF/dx = F(x) - F(x + Deltax)
            lCntX = a_lParaNum*i + j;
            lCntY = a_lParaNum*(i + 1) + j;

            if (lCntX >= 48 || lCntY >= 48)
            {	// error
                lCntX = lCntX;
            }

            a_peJac[lCntX] = eCurrX - eOutX;
            a_peJac[lCntY] = eCurrY - eOutY;

        }
    }

    memcpy(JacobianOut, a_peJac, sizeof(FLOAT64) * 48);
}

void COMMONK_GetHomographyByParameter(FLOAT64 *a_paParameter, FLOAT64 a_aeDesignIntrinsicMatrix[9], FLOAT64 a_aeHMatrix[9], UINT8 a_ucMode, INT32 a_lViewNum)
{
    FLOAT64 aeHMatrix[16];
    FLOAT64 aeRx[9], aeRy[9], aeRz[9], aeRroll[9], aeT[3], aeOffset[3], aeRT[12], aeTmp1[9], aeTmp2[9];
    FLOAT64 eRollAngle = 0, eAngleX = 0, eAngleY = 0, eAngleZ = 0;

    memset(aeHMatrix, 0, 16 * sizeof(FLOAT64));
    memset(aeRx, 0, 9 * sizeof(FLOAT64));
    memset(aeRy, 0, 9 * sizeof(FLOAT64));
    memset(aeRz, 0, 9 * sizeof(FLOAT64));
    memset(aeRroll, 0, 9 * sizeof(FLOAT64));
    memset(aeT, 0, 3 * sizeof(FLOAT64));
    memset(aeOffset, 0, 3 * sizeof(FLOAT64));
    memset(aeRT, 0, 12 * sizeof(FLOAT64));

    // define the roll angle
    switch (a_lViewNum)
    {
    case alCAMERAINFO_BV_LEFT:
        eRollAngle = 90 * alPI / 180;
        break;
    case alCAMERAINFO_BV_RIGHT:
        eRollAngle = -90 * alPI / 180;
        break;
    case alCAMERAINFO_BV_FRONT:
        eRollAngle = 0 * alPI / 180;
        break;
    case alCAMERAINFO_BV_BACK:
        eRollAngle = 180 * alPI / 180;
        break;
    default:
        // do nothing
        break;
    }

    aeOffset[0] = -a_paParameter[3]; aeOffset[1] = -a_paParameter[4]; aeOffset[2] = -a_paParameter[5];
    eAngleX = a_paParameter[0] * alPI / 180; eAngleY = a_paParameter[1] * alPI / 180; eAngleZ = a_paParameter[2] * alPI / 180;

    aeRx[0] = 1; aeRx[4] = cos(eAngleX); aeRx[5] = -sin(eAngleX); aeRx[7] = sin(eAngleX); aeRx[8] = cos(eAngleX);

    aeRy[0] = cos(eAngleY); aeRy[2] = sin(eAngleY); aeRy[4] = 1; aeRy[6] = -sin(eAngleY); aeRy[8] = cos(eAngleY);

    aeRz[0] = cos(eAngleZ); aeRz[1] = -sin(eAngleZ); aeRz[3] = sin(eAngleZ); aeRz[4] = cos(eAngleZ); aeRz[8] = 1;

    aeRroll[0] = cos(eRollAngle); aeRroll[1] = -sin(eRollAngle); aeRroll[3] = sin(eRollAngle); aeRroll[4] = cos(eRollAngle); aeRroll[8] = 1;

    alMATRIX_Multiplaction(aeRx, aeRroll, 3, 3, 3, aeTmp1);
    alMATRIX_Multiplaction(aeRy, aeTmp1, 3, 3, 3, aeTmp2);
    alMATRIX_Multiplaction(aeRz, aeTmp2, 3, 3, 3, aeTmp1);	// R = Rz*Ry*Rx*Rroll;

    alMATRIX_Multiplaction(aeTmp1, aeOffset, 3, 3, 1, aeT);	// T = R*offset;

    // get 3x3 aeHMatrix
    aeRT[0] = aeTmp1[0];	aeRT[1] = aeTmp1[1];	aeRT[2] = aeT[0];
    aeRT[3] = aeTmp1[3];	aeRT[4] = aeTmp1[4];	aeRT[5] = aeT[1];
    aeRT[6] = aeTmp1[6];	aeRT[7] = aeTmp1[7];	aeRT[8] = aeT[2];
    alMATRIX_Multiplaction(a_aeDesignIntrinsicMatrix, aeRT, 3, 3, 3, aeHMatrix);

    memcpy(a_aeHMatrix, aeHMatrix, 9 * sizeof(FLOAT64));

    if (a_ucMode)	// get inverse Homography camera to word
    {
        alMATRIX_InverseNbyN(a_aeHMatrix, 3);
    }
}

void COMMONK_PointTrabform(FLOAT64 *a_peParameter, FLOAT64 *a_peResult, INT32 a_lParaNum, INT32 a_lDataNum, void *data)
{

    FLOAT64 aeDesignIntrinsicMatrix[9] = { 0 }, aeH[9], aeImg[3], aeWord[3], eOutX, eOutY;
    alCOMMONK_LM_Struct tLMInfoIn;
    INT32 lCnt = 0, lPointCnt = 0;

    memcpy(&tLMInfoIn, data, sizeof(alCOMMONK_LM_Struct));

    COMMONK_GetHomographyByParameter(a_peParameter, tLMInfoIn.aeIntrinsic, aeH, 1, tLMInfoIn.lViewNum);

    for (lCnt = 0; lCnt < a_lDataNum; lCnt += 2)
    {
        lPointCnt = lCnt >> 1;
        aeImg[0] = tLMInfoIn.aeCameraPosX[lPointCnt];
        aeImg[1] = tLMInfoIn.aeCameraPosY[lPointCnt];
        aeImg[2] = 1;
        alMATRIX_Multiplaction(aeH, aeImg, 3, 3, 1, aeWord);
        eOutX = aeWord[0] / aeWord[2];
        eOutY = aeWord[1] / aeWord[2];
        a_peResult[lCnt] = eOutX;
        a_peResult[lCnt + 1] = eOutY;
    }
}

#endif

void COMMONK_EnhanceImage(
	INT32 a_lWidth, INT32 a_lHeight,
	UINT8 *a_pucSrcBuffer,
	UINT8 *a_pucOutBuffer
	)
{
	INT32 max = 0, min = 255, i, j, lpixelTmp = 0;
	FLOAT32 afTmp[4] = { 0 };

    if (a_pucOutBuffer != a_pucSrcBuffer)
    { // 如果輸出入圖片非同一塊記憶體
        memcpy(a_pucOutBuffer, a_pucSrcBuffer, a_lWidth * a_lHeight * sizeof(UINT8));
    }
	
	// find max and min
	for (i = 0; i < a_lHeight; i++)
	{
		for (j = 0; j < a_lWidth; j++){

			lpixelTmp = a_pucOutBuffer[j + i*a_lWidth];
			if (lpixelTmp > max)max = lpixelTmp;
			if (lpixelTmp < min)min = lpixelTmp;
		}
	}

	// modify image
	for (i = 0; i < a_lHeight; i++)
	{
		for (j = 0; j < a_lWidth; j++){
			lpixelTmp = a_pucOutBuffer[j + i*a_lWidth];
			afTmp[0] = (FLOAT32)lpixelTmp - min;
			afTmp[1] = (FLOAT32)max - min;
			afTmp[2] = afTmp[0] / afTmp[1] * 255;
			lpixelTmp = (INT32)(afTmp[2]);
			a_pucOutBuffer[j + i*a_lWidth] = (UINT8)lpixelTmp;
		}
	}
}

void COMMONK_PerformCoordinatesTransform(
	const FLOAT64 * a_peM33, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, 
	FLOAT64 * a_peDestX, FLOAT64 * a_peDestY
	)
{
	FLOAT64 eS;

	eS = a_peM33[6] * a_eSrcX + a_peM33[7] * a_eSrcY + a_peM33[8] * 1;
	if (eS == 0.) eS = 1;
	(*a_peDestX) = (a_peM33[0] * a_eSrcX + a_peM33[1] * a_eSrcY + a_peM33[2] * 1) / eS;
	(*a_peDestY) = (a_peM33[3] * a_eSrcX + a_peM33[4] * a_eSrcY + a_peM33[5] * 1) / eS;
}

void COMMONK_SBV2Birdview(
    INT32 a_lSBV_Width, INT32 a_lSBV_Height, INT32 a_lBV_Width, INT32 a_lBV_Height,
	UINT8 a_ucNumPts, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
	INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
	FLOAT64 * a_peSPP_X, FLOAT64 * a_peSPP_Y,
	FLOAT64 * a_peBVP_X, FLOAT64 * a_peBVP_Y
	)
{
	UINT8 ucPtIdx;
	INT32 lOffsetX = 0, lOffsetY = 0;
	FLOAT64 eTmpX, eTmpY, eSBVScale = 0;
	FLOAT32 fMMPP = 0;

	fMMPP = (FLOAT32)a_eMMPP;
	lOffsetX = a_lOffsetX;
	lOffsetY = a_lOffsetY;
	eSBVScale = a_eSBVScale;

	for (ucPtIdx = 0; ucPtIdx < a_ucNumPts; ucPtIdx++)
	{
		// 先將座標旋轉 for Left or Right View
		switch (a_lCamAngle)
		{
		case alBVCAM_FACAUTOK_BV_LEFT: // -90 degree
            eTmpX = (a_peSPP_Y[ucPtIdx] - (a_lSBV_Height >> 1));
            eTmpY = -(a_peSPP_X[ucPtIdx] - (a_lSBV_Width >> 1));
			break;
		case alBVCAM_FACAUTOK_BV_RIGHT: // +90 degree
            eTmpX = -(a_peSPP_Y[ucPtIdx] - (a_lSBV_Height >> 1));
            eTmpY = (a_peSPP_X[ucPtIdx] - (a_lSBV_Width >> 1));
			break;
		case alBVCAM_FACAUTOK_BV_BACK: // 180 degree
            eTmpX = -(a_peSPP_X[ucPtIdx] - (a_lSBV_Width >> 1));
            eTmpY = -(a_peSPP_Y[ucPtIdx] - (a_lSBV_Height >> 1));
			break;
		case alBVCAM_FACAUTOK_BV_FRONT:  // 0 degree
            eTmpX = (a_peSPP_X[ucPtIdx] - (a_lSBV_Width >> 1));
            eTmpY = (a_peSPP_Y[ucPtIdx] - (a_lSBV_Height >> 1));
			break;
		default:
			assert(0);
		}

		// 將座標重設為 bird view 上的位置
		// 1. 計算 Scale Down 的位置(以影像中心為原點) 
		// 2. 計算 Offset 回 VC 中心的位置
		// 3. 計算 Birdview 左上角為原點的影像位置
		a_peBVP_X[ucPtIdx] = ((eTmpX + lOffsetX) / eSBVScale)
            + (a_lCamPosX / fMMPP) + ((a_lBV_Width) >> 1);
		a_peBVP_Y[ucPtIdx] = ((eTmpY + lOffsetY) / eSBVScale)
            + (a_lCamPosY / fMMPP) + ((a_lBV_Height) >> 1);
	}
}

void COMMONK_Birdview2SBV(
    INT32 a_lBV_Width, INT32 a_lBV_Height, INT32 a_lSBV_Width, INT32 a_lSBV_Height,
	UINT8 a_ucNumPts, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
	INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
	FLOAT64 * a_peBVP_X, FLOAT64 * a_peBVP_Y,
	FLOAT64 * a_peSPP_X, FLOAT64 * a_peSPP_Y
	)
{
	UINT8 ucPtIdx;
	INT32 lOffsetX = 0, lOffsetY = 0, lFPNum;
	FLOAT64 eTmpX, eTmpY, eSBVScale = 0;
	FLOAT32 fMMPP = 0;

	fMMPP = (FLOAT32)a_eMMPP;
	lOffsetX = a_lOffsetX;
	lOffsetY = a_lOffsetY;
	eSBVScale = a_eSBVScale;

	lFPNum = a_ucNumPts;

	for (ucPtIdx = 0; ucPtIdx < lFPNum; ucPtIdx++)
	{
		// 將座標重設為 旋轉前 Single BV 上的位置
		// 1. 計算 Birdview VC 中心的影像位置
		// 2. 計算 Scale Up 後的位置
		// 3. 計算 Scale Up 後影像左上為原點的位置 
        eTmpX = ((a_peBVP_X[ucPtIdx] - ((a_lBV_Width) >> 1) - (a_lCamPosX / fMMPP))
			* eSBVScale) - lOffsetX;
        eTmpY = ((a_peBVP_Y[ucPtIdx] - ((a_lBV_Height) >> 1) - (a_lCamPosY / fMMPP))
			* eSBVScale) - lOffsetY;

		// 再將座標旋轉 for Left or Right View
		switch (a_lCamAngle)
		{
		case alBVCAM_FACAUTOK_BV_LEFT: // +90 degree
            a_peSPP_X[ucPtIdx] = -eTmpY + (a_lSBV_Width >> 1);
            a_peSPP_Y[ucPtIdx] = eTmpX + (a_lSBV_Height >> 1);
			break;
		case alBVCAM_FACAUTOK_BV_RIGHT: // -90 degree
            a_peSPP_X[ucPtIdx] = eTmpY + (a_lSBV_Width >> 1);
            a_peSPP_Y[ucPtIdx] = -eTmpX + (a_lSBV_Height >> 1);
			break;
		case alBVCAM_FACAUTOK_BV_BACK:  // 180 degree
            a_peSPP_X[ucPtIdx] = -eTmpX + (a_lSBV_Width >> 1);
            a_peSPP_Y[ucPtIdx] = -eTmpY + (a_lSBV_Height >> 1);
			break;
		case alBVCAM_FACAUTOK_BV_FRONT:  // 0 degree
            a_peSPP_X[ucPtIdx] = eTmpX + (a_lSBV_Width >> 1);
            a_peSPP_Y[ucPtIdx] = eTmpY + (a_lSBV_Height >> 1);
			break;
		default:  // not defined
			assert(0);
		}
	}
}

void	COMMONK_SBVGeneratingK(
    alPointINT32 *a_ptBVImgSize,
	alRectINT32 a_tROI,
	UINT8 *a_pucSrcBuffer,
    alFM_v2_1_Model *a_ptFisheyeModel,
	FLOAT64 *a_ptM33,
	INT32 a_lOriImgYLimit, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
	INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
	UINT8 *a_pucSBVBuffer
	)
{
	INT32 lDestX, lDestY, lSrcX, lSrcY, lYLimit = 0, lWidth = 0;
	FLOAT64 eBVP_X, eBVP_Y, eSPP_X, eSPP_Y, eUDX, eUDY, eSrcX, eSrcY;
	FLOAT64 eAlpha, eBeta, *peM33 = NULL;
	UINT8 *pucDest, *pucSrc1, *pucSrc2, *pucSrc3, *pucSrc4;
    alFM_v2_1_Model *ptCameraFisheyeModel = NULL;
    alPointINT32 tImgSize = { 0 };

	lYLimit = a_lOriImgYLimit;
	ptCameraFisheyeModel = a_ptFisheyeModel;
	peM33 = a_ptM33;

    tImgSize.lX = ptCameraFisheyeModel->uwSrcWidth;
    tImgSize.lY = ptCameraFisheyeModel->uwSrcHeight;

	lWidth = a_tROI.lRight + 1 - a_tROI.lLeft;

	for (lDestY = a_tROI.lTop; lDestY < a_tROI.lBottom+1 ; lDestY++)
	{
		for (lDestX = a_tROI.lLeft; lDestX < a_tROI.lRight+1; lDestX++)
		{
			pucDest = a_pucSBVBuffer + ((lDestX - a_tROI.lLeft) + (lDestY - a_tROI.lTop) * lWidth);
			eSPP_X = lDestX;
			eSPP_Y = lDestY;

			// 將座標重設為 bird view 上的位置
			COMMONK_SBV2Birdview(
                tImgSize.lX, tImgSize.lY, a_ptBVImgSize->lX, a_ptBVImgSize->lY,
				1, a_lCamAngle, a_lCamPosX, a_lCamPosY,
				a_lOffsetX, a_lOffsetY, a_eSBVScale, a_eMMPP,
				&eSPP_X, &eSPP_Y,
				&eBVP_X, &eBVP_Y
			);

			// 計算反魚眼座標
			COMMONK_PerformCoordinatesTransform(peM33, eBVP_X, eBVP_Y, &eUDX, &eUDY);

			// 超過設定之 FOV 的座標點不列入計算
			if (eUDY >= lYLimit)
			{
				// 計算魚眼座標
                alFM_v2_1_Undistorted2Distorted_PlanarPixel(ptCameraFisheyeModel, eUDX, eUDY, &eSrcX, &eSrcY);

				lSrcX = (INT32)(eSrcX);
				lSrcY = (INT32)(eSrcY);
				eAlpha = eSrcX - lSrcX;
				eBeta = eSrcY - lSrcY;

                if (lSrcX >= 0 && (lSrcX + 1) < tImgSize.lX && lSrcY >= 0 && (lSrcY + 1) < tImgSize.lY)
				{
					// Y 
                    pucSrc1 = a_pucSrcBuffer + ((lSrcX + lSrcY * tImgSize.lX));
					pucSrc2 = pucSrc1 + 1;
                    pucSrc3 = pucSrc1 + (tImgSize.lX);
					pucSrc4 = pucSrc3 + 1;

					// Y 
					*pucDest = (INT32)((1.0 - eAlpha) * (1.0 - eBeta) * (*pucSrc1) + eAlpha * (1.0 - eBeta) * (*pucSrc2)
						+ (1.0 - eAlpha) * eBeta * (*pucSrc3) + eAlpha * eBeta * (*pucSrc4));
				}
				else
				{
					// 超出範圍的座點，該位置的像素值填黑色
					*pucDest = 0;
				}
			}
			else
			{
				// 超出範圍的座點，該位置的像素值填黑色
				*pucDest = 0;
			}
		}
	}
}

void	COMMONK_SBVGeneratingK_YUYV2Y(
    alPointINT32 *a_ptBVImgSize,
    alRectINT32 a_tROI,
    UINT8 *a_pucSrcBuffer,
    alFM_v2_1_Model *a_ptFisheyeModel,
    FLOAT64 *a_ptM33,
    INT32 a_lOriImgYLimit, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
    INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
    UINT8 *a_pucSBVBuffer
    )
{
    INT32 lDestX, lDestY, lSrcX, lSrcY, lYLimit = 0, lWidth = 0;
    FLOAT64 eBVP_X, eBVP_Y, eSPP_X, eSPP_Y, eUDX, eUDY, eSrcX, eSrcY;
    FLOAT64 eAlpha, eBeta, *peM33 = NULL;
    UINT8 *pucDest, *pucSrc1, *pucSrc2, *pucSrc3, *pucSrc4;
    alFM_v2_1_Model *ptCameraFisheyeModel = NULL;
    alPointINT32 tImgSize = { 0 };

    lYLimit = a_lOriImgYLimit;
    ptCameraFisheyeModel = a_ptFisheyeModel;
    peM33 = a_ptM33;

    tImgSize.lX = ptCameraFisheyeModel->uwSrcWidth;
    tImgSize.lY = ptCameraFisheyeModel->uwSrcHeight;

    lWidth = a_tROI.lRight + 1 - a_tROI.lLeft;

    for (lDestY = a_tROI.lTop; lDestY < a_tROI.lBottom + 1; lDestY++)
    {
        for (lDestX = a_tROI.lLeft; lDestX < a_tROI.lRight + 1; lDestX++)
        {
            pucDest = a_pucSBVBuffer + ((lDestX - a_tROI.lLeft) + (lDestY - a_tROI.lTop) * lWidth);
            eSPP_X = lDestX;
            eSPP_Y = lDestY;

            // 將座標重設為 bird view 上的位置
            COMMONK_SBV2Birdview(
                tImgSize.lX, tImgSize.lY, a_ptBVImgSize->lX, a_ptBVImgSize->lY,
                1, a_lCamAngle, a_lCamPosX, a_lCamPosY,
                a_lOffsetX, a_lOffsetY, a_eSBVScale, a_eMMPP,
                &eSPP_X, &eSPP_Y,
                &eBVP_X, &eBVP_Y
                );

            // 計算反魚眼座標
            COMMONK_PerformCoordinatesTransform(peM33, eBVP_X, eBVP_Y, &eUDX, &eUDY);

            // 超過設定之 FOV 的座標點不列入計算
            if (eUDY >= lYLimit)
            {
                // 計算魚眼座標
                alFM_v2_1_Undistorted2Distorted_PlanarPixel(ptCameraFisheyeModel, eUDX, eUDY, &eSrcX, &eSrcY);

                lSrcX = (INT32)(eSrcX);
                lSrcY = (INT32)(eSrcY);
                eAlpha = eSrcX - lSrcX;
                eBeta = eSrcY - lSrcY;

                if (lSrcX >= 0 && (lSrcX + 1) < tImgSize.lX && lSrcY >= 0 && (lSrcY + 1) < tImgSize.lY)
                {
                    // Y 
                    pucSrc1 = a_pucSrcBuffer + ((lSrcX + lSrcY * tImgSize.lX) << 1);
                    pucSrc2 = pucSrc1 + 2;
                    pucSrc3 = pucSrc1 + (tImgSize.lX << 1);
                    pucSrc4 = pucSrc3 + 2;

                    // Y 
                    *pucDest = (INT32)((1.0 - eAlpha) * (1.0 - eBeta) * (*pucSrc1) + eAlpha * (1.0 - eBeta) * (*pucSrc2)
                        + (1.0 - eAlpha) * eBeta * (*pucSrc3) + eAlpha * eBeta * (*pucSrc4));
                }
                else
                {
                    // 超出範圍的座點，該位置的像素值填黑色
                    *pucDest = 0;
                }
            }
            else
            {
                // 超出範圍的座點，該位置的像素值填黑色
                *pucDest = 0;
            }
        }
    }
}

BOOL COMMONK_GenerateM3x3(FLOAT64 * peSrcX, FLOAT64 * peSrcY, FLOAT64 * peDestX, FLOAT64 * peDestY, UINT8 ucNumPts, FLOAT64 * pePTMatrix)
{
	unsigned char n;
	unsigned short offset;
	FLOAT64 *PosA, *PosAT, *PosH;
	FLOAT64 *PosATA, *PosATAAT, *Mtx;

	if (ucNumPts > 20)//限制點數不可太多,  in fact, NumPts=4
		return FALSE;

	PosA = (FLOAT64*)malloc(8 * 2 * ucNumPts * sizeof(FLOAT64));
	PosAT = (FLOAT64*)malloc(8 * 2 * ucNumPts * sizeof(FLOAT64));
	PosATA = (FLOAT64*)malloc(8 * 8 * sizeof(FLOAT64));
	PosATAAT = (FLOAT64*)malloc(8 * 2 * ucNumPts * sizeof(FLOAT64));
	PosH = (FLOAT64*)malloc(2 * ucNumPts * sizeof(FLOAT64));
	Mtx = (FLOAT64*)malloc(9 * sizeof(FLOAT64));

	for (n = 0; n < ucNumPts; n++)
	{
		offset = n * 8 * 2;

		PosA[0 + offset] = ((FLOAT64)(peSrcX[n]));
		PosA[1 + offset] = ((FLOAT64)(peSrcY[n]));
		PosA[2 + offset] = 1.0f;
		PosA[3 + offset] = 0;
		PosA[4 + offset] = 0;
		PosA[5 + offset] = 0;
		PosA[6 + offset] = -((FLOAT64)(peDestX[n] * (peSrcX[n])));
		PosA[7 + offset] = -((FLOAT64)(peDestX[n] * (peSrcY[n])));
		PosA[8 + offset] = 0;
		PosA[9 + offset] = 0;
		PosA[10 + offset] = 0;
		PosA[11 + offset] = ((FLOAT64)(peSrcX[n]));
		PosA[12 + offset] = ((FLOAT64)(peSrcY[n]));
		PosA[13 + offset] = 1.0f;
		PosA[14 + offset] = -((FLOAT64)(peDestY[n] * (peSrcX[n])));
		PosA[15 + offset] = -((FLOAT64)(peDestY[n] * (peSrcY[n])));
	}
	for (n = 0; n < ucNumPts; n++)
	{
		PosH[(int)(n << 1)] = ((FLOAT64)(peDestX[n]));
		PosH[(int)(n << 1) + 1] = ((FLOAT64)(peDestY[n]));
	}
    alMATRIX_Transpose(PosA, 2 * ucNumPts, 8, PosAT);                        //Transport matrix
	alMATRIX_Multiplaction(PosAT, PosA, 8, 2 * ucNumPts, 8, PosATA);       //AT*A=ATA
	alMATRIX_InverseNbyN(PosATA, 8);                                       //inv(ATA)
	alMATRIX_Multiplaction(PosATA, PosAT, 8, 8, 2 * ucNumPts, PosATAAT);   //inv(ATA)*AT
	alMATRIX_Multiplaction(PosATAAT, PosH, 8, 2 * ucNumPts, 1, Mtx);       //0~7 element
	Mtx[8] = 1;
	alMATRIX_InverseNbyN(Mtx, 3);

	for (n = 0; n < 9; n++)
		pePTMatrix[n] = Mtx[n];

	free(PosA);
	free(PosAT);
	free(PosATA);
	free(PosATAAT);
	free(PosH);
	free(Mtx);

	return TRUE;
}

void	COMMONK_InterceptPointCal_ByVector(
	FLOAT64 a_eSX0, FLOAT64 a_eSY0, FLOAT64 a_eEX0, FLOAT64 a_eEY0,
	FLOAT64 a_eSX1, FLOAT64 a_eSY1, FLOAT64 a_eEX1, FLOAT64 a_eEY1,
	FLOAT64 *a_pePx, FLOAT64 *a_pePy
	)
{
	INT32 i = 0;
	FLOAT64 eSX0, eSY0, eSX1, eSY1, eVX0, eVY0, eVX1, eVY1, eT, aeP[2];
	FLOAT64 eEX0, eEY0, eEX1, eEY1;

	for (i = 0; i < 4; i++)
	{
		eSX0 = a_eSX0;
		eSY0 = a_eSY0;
		eEX0 = a_eEX0;
		eEY0 = a_eEY0;
		eVX0 = eEX0 - eSX0;
		eVY0 = eEY0 - eSY0;

		eSX1 = a_eSX1;
		eSY1 = a_eSY1;
		eEX1 = a_eEX1;
		eEY1 = a_eEY1;
		eVX1 = eEX1 - eSX1;
		eVY1 = eEY1 - eSY1;

		eT = (eVY1*(eSX1 - eSX0) - eVX1*(eSY1 - eSY0)) / (eVX0*eVY1 - eVY0*eVX1);

		aeP[0] = eSX0 + eVX0*eT;
		aeP[1] = eSY0 + eVY0*eT;

		*a_pePx = aeP[0];
		*a_pePy = aeP[1];
	}
}

/* Perform planar transform for YUYV image */
void COMMONK_SBVGenerate_YUYV_FULL(
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    FLOAT64 a_peM33[9],
    INT32 a_lOriImgYLimit, INT32 a_lCamAngle, INT32 a_lCamPosX, INT32 a_lCamPosY,
    INT32 a_lOffsetX, INT32 a_lOffsetY, FLOAT64 a_eSBVScale, FLOAT64 a_eMMPP,
    alFM_v2_1_Model *a_ptCameraFisheyeModel
    )
{
    INT32 lDestX, lDestY, lSrcX, lSrcY;
    FLOAT64 eBVP_X, eBVP_Y, eSPP_X, eSPP_Y, eUDX, eUDY, eSrcX, eSrcY;
    INT32 lRowIndex;
    UINT8 * pucDest;
    UINT8 *pucSrc1, *pucSrc2, *pucSrc3, *pucSrc4;
    FLOAT64 eAlpha, eBeta;
    INT32 lYLimit = a_lOriImgYLimit;

    alFM_v2_1_Model * ptCameraFisheyeModel = a_ptCameraFisheyeModel;

    for (lDestY = 0, lRowIndex = 0; lDestY < a_lDestHeight; lDestY++, lRowIndex += a_lDestWidth)
    {
        for (lDestX = 0; lDestX < a_lDestWidth; lDestX++)
        {
            pucDest = a_pucDestImage + (lDestX + lDestY * a_lDestWidth) * 2;

            eSPP_X = lDestX;
            eSPP_Y = lDestY;

            // 將座標重設為 bird view 上的位置
            COMMONK_SBV2Birdview(
                a_lSrcWidth, a_lSrcHeight, a_lDestWidth, a_lDestHeight,
                1, a_lCamAngle, a_lCamPosX, a_lCamPosY,
                a_lOffsetX, a_lOffsetY, a_eSBVScale, a_eMMPP,
                &eSPP_X, &eSPP_Y,
                &eBVP_X, &eBVP_Y
                );

            // 計算反魚眼座標
            COMMONK_PerformCoordinatesTransform(a_peM33, eBVP_X, eBVP_Y, &eUDX, &eUDY);

            // 超過Y設定的座標點不列入計算
#if COMMONK_SBV_Y_LIMIT
            if (eUDY >= lYLimit)
#else
            if (1)
#endif
            {

                // 計算魚眼座標
                alFM_v2_1_Undistorted2Distorted_PlanarPixel(ptCameraFisheyeModel, eUDX, eUDY, &eSrcX, &eSrcY);

                lSrcX = (INT32)(eSrcX);
                lSrcY = (INT32)(eSrcY);
                eAlpha = eSrcX - lSrcX;
                eBeta = eSrcY - lSrcY;

                if (lSrcX >= 0 && (lSrcX + 1) < a_lSrcWidth && lSrcY >= 0 && (lSrcY + 1) < a_lSrcHeight)
                {
                    pucSrc1 = a_pucSrcImage + ((lSrcX + lSrcY * a_lSrcWidth) << 1);
                    pucSrc2 = pucSrc1 + 2;
                    pucSrc3 = pucSrc1 + (a_lSrcWidth << 1);
                    pucSrc4 = pucSrc3 + 2;

                    //f(p) = (1-alpha)*(1-beta)*f(a) + alpha*(1-beta)*f(b)+ (1-alpha)*beta*f(c)+ alpha*beta*f(d)

                    // Y 
                    *pucDest = (INT32)((1.0 - eAlpha) * (1.0 - eBeta) * (*pucSrc1) + eAlpha * (1.0 - eBeta) * (*pucSrc2)
                        + (1.0 - eAlpha) * eBeta * (*pucSrc3) + eAlpha * eBeta * (*pucSrc4));

                    // U 
                    if (lDestX % 2 == 0) // even
                    {
                        if (lSrcX % 2 == 0) // even
                        {
                            *(pucDest + 1) = *(pucSrc1 + 1);
                        }
                        else    // odd
                        {
                            *(pucDest + 1) = *(pucSrc1 - 1);
                        }
                    }
                    // V 
                    else // odd
                    {
                        if (lSrcX % 2 == 0) // even
                        {
                            *(pucDest + 1) = *(pucSrc1 - 1);
                        }
                        else    // odd
                        {
                            *(pucDest + 1) = *(pucSrc1 + 1);
                        }
                    }
                    continue;
                }
            }

            // 超出範圍的座點，該位置的像素值填黑色
            *pucDest = 0;
            if (lDestX % 2 == 0) // even
            {
                *(pucDest + 1) = 128;
                *(pucDest + 3) = 128;
            }

        }
    }
}

void COMMONK_UndistortedImageGenerate_YUYV_FULL(
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    alFM_v2_1_Model *a_ptCameraFisheyeModel
    )
{
    INT32 lDestX, lDestY, lSrcX, lSrcY;
    FLOAT64 eSPP_X, eSPP_Y, eSrcX, eSrcY;
    INT32 lRowIndex;
    UINT8 *pucDest;
    UINT8 *pucSrc1, *pucSrc2, *pucSrc3, *pucSrc4;
    FLOAT64 eAlpha, eBeta;

    alFM_v2_1_Model * ptCameraFisheyeModel = a_ptCameraFisheyeModel;

    for (lDestY = 0, lRowIndex = 0; lDestY < a_lDestHeight; lDestY++, lRowIndex += a_lDestWidth)
    {
        for (lDestX = 0; lDestX < a_lDestWidth; lDestX++)
        {
            pucDest = a_pucDestImage + (lDestX + lDestY * a_lDestWidth) * 2;

            eSPP_X = lDestX;
            eSPP_Y = lDestY;

            // 超過Y設定的座標點不列入計算
            {
                // 計算魚眼座標
                alFM_v2_1_Undistorted2Distorted_PlanarPixel(ptCameraFisheyeModel, eSPP_X, eSPP_Y, &eSrcX, &eSrcY);

                lSrcX = (INT32)(eSrcX);
                lSrcY = (INT32)(eSrcY);
                eAlpha = eSrcX - lSrcX;
                eBeta = eSrcY - lSrcY;

                if (lSrcX >= 0 && (lSrcX + 1) < a_lSrcWidth && lSrcY >= 0 && (lSrcY + 1) < a_lSrcHeight)
                {
                    pucSrc1 = a_pucSrcImage + ((lSrcX + lSrcY * a_lSrcWidth) << 1);
                    pucSrc2 = pucSrc1 + 2;
                    pucSrc3 = pucSrc1 + (a_lSrcWidth << 1);
                    pucSrc4 = pucSrc3 + 2;

                    //f(p) = (1-alpha)*(1-beta)*f(a) + alpha*(1-beta)*f(b)+ (1-alpha)*beta*f(c)+ alpha*beta*f(d)

                    // Y 
                    *pucDest = (INT32)((1.0 - eAlpha) * (1.0 - eBeta) * (*pucSrc1) + eAlpha * (1.0 - eBeta) * (*pucSrc2)
                        + (1.0 - eAlpha) * eBeta * (*pucSrc3) + eAlpha * eBeta * (*pucSrc4));

                    // U 
                    if (lDestX % 2 == 0) // even
                    {
                        if (lSrcX % 2 == 0) // even
                        {
                            *(pucDest + 1) = *(pucSrc1 + 1);
                        }
                        else    // odd
                        {
                            *(pucDest + 1) = *(pucSrc1 - 1);
                        }
                    }
                    // V 
                    else // odd
                    {
                        if (lSrcX % 2 == 0) // even
                        {
                            *(pucDest + 1) = *(pucSrc1 - 1);
                        }
                        else    // odd
                        {
                            *(pucDest + 1) = *(pucSrc1 + 1);
                        }
                    }
                    continue;
                }
            }

            // 超出範圍的座點，該位置的像素值填黑色
            *pucDest = 0;
            if (lDestX % 2 == 0) // even
            {
                *(pucDest + 1) = 128;
                *(pucDest + 3) = 128;
            }

        }
    }
}

void COMMONK_DistortedImageGenerate_YUYV_FULL(
    UINT8 * a_pucSrcImage, INT32 a_lSrcWidth, INT32 a_lSrcHeight,
    UINT8 * a_pucDestImage, INT32 a_lDestWidth, INT32 a_lDestHeight,
    alFM_v2_1_Model *a_ptCameraFisheyeModel
    )
{
    INT32 lDestX, lDestY, lSrcX, lSrcY;
    FLOAT64 eSPP_X, eSPP_Y, eSrcX, eSrcY;
    INT32 lRowIndex;
    UINT8 *pucDest;
    UINT8 *pucSrc1, *pucSrc2, *pucSrc3, *pucSrc4;
    FLOAT64 eAlpha, eBeta;

    alFM_v2_1_Model * ptCameraFisheyeModel = a_ptCameraFisheyeModel;

    for (lDestY = 0, lRowIndex = 0; lDestY < a_lDestHeight; lDestY++, lRowIndex += a_lDestWidth)
    {
        for (lDestX = 0; lDestX < a_lDestWidth; lDestX++)
        {
            pucDest = a_pucDestImage + (lDestX + lDestY * a_lDestWidth) * 2;

            eSPP_X = lDestX;
            eSPP_Y = lDestY;

            {
                // 計算反魚眼座標
                alFM_v2_1_Distorted2Undistorted_PlanarPixel(ptCameraFisheyeModel, eSPP_X, eSPP_Y, &eSrcX, &eSrcY);

                lSrcX = (INT32)(eSrcX);
                lSrcY = (INT32)(eSrcY);
                eAlpha = eSrcX - lSrcX;
                eBeta = eSrcY - lSrcY;

                if (lSrcX >= 0 && (lSrcX + 1) < a_lSrcWidth && lSrcY >= 0 && (lSrcY + 1) < a_lSrcHeight)
                {
                    pucSrc1 = a_pucSrcImage + ((lSrcX + lSrcY * a_lSrcWidth) << 1);
                    pucSrc2 = pucSrc1 + 2;
                    pucSrc3 = pucSrc1 + (a_lSrcWidth << 1);
                    pucSrc4 = pucSrc3 + 2;

                    // Y 
                    *pucDest = (INT32)((1.0 - eAlpha) * (1.0 - eBeta) * (*pucSrc1) + eAlpha * (1.0 - eBeta) * (*pucSrc2)
                        + (1.0 - eAlpha) * eBeta * (*pucSrc3) + eAlpha * eBeta * (*pucSrc4));

                    // U 
                    if (lDestX % 2 == 0) // even
                    {
                        if (lSrcX % 2 == 0) // even
                        {
                            *(pucDest + 1) = *(pucSrc1 + 1);
                        }
                        else    // odd
                        {
                            *(pucDest + 1) = *(pucSrc1 - 1);
                        }
                    }
                    // V 
                    else // odd
                    {
                        if (lSrcX % 2 == 0) // even
                        {
                            *(pucDest + 1) = *(pucSrc1 - 1);
                        }
                        else    // odd
                        {
                            *(pucDest + 1) = *(pucSrc1 + 1);
                        }
                    }
                    continue;
                }
            }

            // 超出範圍的座點，該位置的像素值填黑色
            *pucDest = 0;
            if (lDestX % 2 == 0) // even
            {
                *(pucDest + 1) = 128;
                *(pucDest + 3) = 128;
            }

        }
    }
}

BOOL COMMONK_TransferFPFromPixel2mm(
    const INT32 a_lBVCenter_X, const INT32 a_lBVCenter_Y,
    const FLOAT64 *a_peFPIdealCoordOnImage_X, const FLOAT64 *a_peFPIdealCoordOnImage_Y,
    const UINT8 a_ucNumPts, const FLOAT32 a_fBirdViewMMPP,
    FLOAT64 *a_peFPIdealCoordInWorld_X, FLOAT64 *a_peFPIdealCoordInWorld_Y
    )
{
    INT32 i = 0;
    /*FLOAT64 aeWP_X[4], aeWP_Y[4];*/

    for (i = 0; i < a_ucNumPts; i++)
    {
        a_peFPIdealCoordInWorld_X[i] = a_peFPIdealCoordOnImage_X[i] - a_lBVCenter_X;
        a_peFPIdealCoordInWorld_Y[i] = a_peFPIdealCoordOnImage_Y[i] - a_lBVCenter_Y;
        a_peFPIdealCoordInWorld_X[i] = a_peFPIdealCoordInWorld_X[i] * a_fBirdViewMMPP;
        a_peFPIdealCoordInWorld_Y[i] = a_peFPIdealCoordInWorld_Y[i] * a_fBirdViewMMPP;

        /*aeWP_X[i] = a_peFPIdealCoordInWorld_X[i];
        aeWP_Y[i] = a_peFPIdealCoordInWorld_Y[i];*/
    }
    return 1;
}


BOOL COMMONK_TransferBVFPtoUndistorRealCam(
    const FLOAT64 *a_peSelectedFP_X, const FLOAT64 *a_peSelectedFP_Y,
    const UINT8 a_ucNumPts, const FLOAT64 a_aeCurrentHomographyMatrix[9],
    const alFM_v2_1_Model *a_ptFisheyeModel_v2,
    FLOAT64 *a_peFP_RealCamUndistorX, FLOAT64 *a_peFP_RealCamUndistorY
    )
{
    INT32 i = 0;
#if 0 // 轉回原影像驗證座標而已  for test
    // TEST
    FLOAT64 aeRC[2] = {0};
#endif

    for (i = 0; i < a_ucNumPts; i++)
    {
        //將座標點 從top view轉至無魚眼效應的Image fisheye v1 by currentM33
        COMMONK_PerformCoordinatesTransform(
            a_aeCurrentHomographyMatrix,
            a_peSelectedFP_X[i],
            a_peSelectedFP_Y[i],
            &a_peFP_RealCamUndistorX[i],
            &a_peFP_RealCamUndistorY[i]
            );

#if 0 // 轉回原影像驗證座標而已  for test
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(
            a_ptFisheyeModel_v2,
            a_peFP_RealCamUndistorX[i],
            a_peFP_RealCamUndistorY[i], &aeRC[0], &aeRC[1]
            );
#endif

        a_peFP_RealCamUndistorX[i] = (a_peFP_RealCamUndistorX[i] - (a_ptFisheyeModel_v2->uwDestWidth >> 1));

        a_peFP_RealCamUndistorX[i] = a_peFP_RealCamUndistorX[i] * a_ptFisheyeModel_v2->ulSensorPixelSize;
        a_peFP_RealCamUndistorX[i] = a_peFP_RealCamUndistorX[i] / 1000000.0;


        a_peFP_RealCamUndistorY[i] = (a_peFP_RealCamUndistorY[i] - (a_ptFisheyeModel_v2->uwDestHeight >> 1)) * a_ptFisheyeModel_v2->ulSensorPixelSize / 1000000.0;

    }
    return 1;
}


BOOL COMMONK_DetermineExtrinsicParameter(
    const INT32 a_lCAMID,
    const FLOAT64 a_aeRTMatrix_RealCamtoBV[16],
    const FLOAT64 a_aeRTMatrix_BVtoRealCam[16],
    alCAMERAINFO_ExtrinsicParams *a_ptExtrinsicParameter
    ){
    FLOAT64 eAngleY = 0, eAngleX = 0, eAngleZ = 0, eRollAngle = 0, eCameraCustomRoll = 0;
    FLOAT64 aeRotationInv[9], aeRotation[9];
    FLOAT64 aeRroll[9] = { 0 };
    FLOAT64 aePosition[3], aeT[3], aePositionTmp[3] = { 0 };


    // get rotation angle
    switch (a_lCAMID)
    {
    case alCAMERAINFO_BV_LEFT:
        eRollAngle = -90;
        break;
    case alCAMERAINFO_BV_RIGHT:
        eRollAngle = 90;
        break;
    case alCAMERAINFO_BV_FRONT:
        eRollAngle = 0;
        break;
    case alCAMERAINFO_BV_BACK:
        eRollAngle = 180;
        break;
    }

    eCameraCustomRoll = -eRollAngle * alPI / 180;

    aeRroll[0] = cos(eCameraCustomRoll);
    aeRroll[1] = -sin(eCameraCustomRoll);
    aeRroll[3] = sin(eCameraCustomRoll);
    aeRroll[4] = cos(eCameraCustomRoll);
    aeRroll[8] = 1;

    alMATRIX_InverseNbyN(aeRroll, 3);

    aeRotation[0] = a_aeRTMatrix_BVtoRealCam[0];
    aeRotation[1] = a_aeRTMatrix_BVtoRealCam[1];
    aeRotation[2] = a_aeRTMatrix_BVtoRealCam[2];
    aeRotation[3] = a_aeRTMatrix_BVtoRealCam[4];
    aeRotation[4] = a_aeRTMatrix_BVtoRealCam[5];
    aeRotation[5] = a_aeRTMatrix_BVtoRealCam[6];
    aeRotation[6] = a_aeRTMatrix_BVtoRealCam[8];
    aeRotation[7] = a_aeRTMatrix_BVtoRealCam[9];
    aeRotation[8] = a_aeRTMatrix_BVtoRealCam[10];

    alMATRIX_Multiplaction(aeRotation, aeRroll, 3, 3, 3, aeRotationInv);
    eAngleY = asin(-aeRotationInv[6]) * 180.0 / alPI;
    eAngleX = asin(aeRotationInv[7] / cos(eAngleY*alPI / 180)) * 180.0 / alPI;
    eAngleZ = asin(aeRotationInv[3] / cos(eAngleY*alPI / 180)) * 180.0 / alPI;

    alMATRIX_InverseNbyN(aeRotationInv, 3);


    // get camera position
    aeT[0] = a_aeRTMatrix_BVtoRealCam[3];
    aeT[1] = a_aeRTMatrix_BVtoRealCam[7];
    aeT[2] = a_aeRTMatrix_BVtoRealCam[11];

    alMATRIX_Multiplaction(aeRotationInv, aeT, 3, 3, 1, aePositionTmp);
    alMATRIX_Multiplaction(aeRroll, aePositionTmp, 3, 3, 1, aePosition);

    a_ptExtrinsicParameter->fPitchAngle = (FLOAT32)(eAngleX);
    a_ptExtrinsicParameter->fYawAngle = (FLOAT32)(eAngleY);
    a_ptExtrinsicParameter->fRollAngle = (FLOAT32)(eAngleZ);
    a_ptExtrinsicParameter->lCameraPosX = (INT32)(-aePosition[0]);
    a_ptExtrinsicParameter->lCameraPosY = (INT32)(-aePosition[1]);
    a_ptExtrinsicParameter->lCameraPosZ = (INT32)(-aePosition[2]);
    return 1;
}

BOOL COMMONK_DetermineRTMatrix(
    const FLOAT64 a_aeDesignIntrinsicMatrix[9], const FLOAT64 *a_peHomographyMatrix,
    FLOAT64 a_aeRTMatrix_RealCamtoBV[16], FLOAT64 a_aeRTMatrix_BVtoRealCam[16]
    )
{
    FLOAT64 aeInverseIntrinsicMatrix[9] = { 0 };
    FLOAT64 aeR1[3] = { 0 }, aeR2[3] = { 0 }, aeR3[3] = { 0 }, aeT[3] = { 0 };
    FLOAT64 aeH1[3] = { 0 }, aeH2[3] = { 0 }, aeH3[3] = { 0 };
    FLOAT64 eR1Length = 0, eR2Length = 0, eNormalLength = 0;
    INT32 lCnt = 0;

    for (lCnt = 0; lCnt < 9; lCnt++)
    {
        aeInverseIntrinsicMatrix[lCnt] = a_aeDesignIntrinsicMatrix[lCnt];
    }

    alMATRIX_InverseNbyN(aeInverseIntrinsicMatrix, 3);

    for (lCnt = 0; lCnt < 3; lCnt++)
    {
        aeH1[lCnt] = a_peHomographyMatrix[lCnt * 3];
        aeH2[lCnt] = a_peHomographyMatrix[lCnt * 3 + 1];
        aeH3[lCnt] = a_peHomographyMatrix[lCnt * 3 + 2];
    }


    alMATRIX_Multiplaction(aeInverseIntrinsicMatrix, aeH1, 3, 3, 1, aeR1);
    alMATRIX_Multiplaction(aeInverseIntrinsicMatrix, aeH2, 3, 3, 1, aeR2);
    alMATRIX_Multiplaction(aeInverseIntrinsicMatrix, aeH3, 3, 3, 1, aeT);


    // length of vector
    eR1Length = sqrt(aeR1[0] * aeR1[0] + aeR1[1] * aeR1[1] + aeR1[2] * aeR1[2]);
    eR2Length = sqrt(aeR2[0] * aeR2[0] + aeR2[1] * aeR2[1] + aeR2[2] * aeR2[2]);
    eNormalLength = (eR1Length + eR2Length) / 2;

    // normalize
    for (lCnt = 0; lCnt < 3; lCnt++)
    {
        aeR1[lCnt] = aeR1[lCnt] / eNormalLength;
        aeR2[lCnt] = aeR2[lCnt] / eNormalLength;
        aeT[lCnt] = aeT[lCnt] / eNormalLength;
    }

    aeR3[0] = aeR1[1] * aeR2[2] - aeR1[2] * aeR2[1];
    aeR3[1] = -(aeR1[0] * aeR2[2] - aeR1[2] * aeR2[0]);
    aeR3[2] = aeR1[0] * aeR2[1] - aeR1[1] * aeR2[0];

    a_aeRTMatrix_BVtoRealCam[0] = aeR1[0];
    a_aeRTMatrix_BVtoRealCam[1] = aeR2[0];
    a_aeRTMatrix_BVtoRealCam[2] = aeR3[0];
    a_aeRTMatrix_BVtoRealCam[3] = aeT[0];

    a_aeRTMatrix_BVtoRealCam[4] = aeR1[1];
    a_aeRTMatrix_BVtoRealCam[5] = aeR2[1];
    a_aeRTMatrix_BVtoRealCam[6] = aeR3[1];
    a_aeRTMatrix_BVtoRealCam[7] = aeT[1];

    a_aeRTMatrix_BVtoRealCam[8] = aeR1[2];
    a_aeRTMatrix_BVtoRealCam[9] = aeR2[2];
    a_aeRTMatrix_BVtoRealCam[10] = aeR3[2];
    a_aeRTMatrix_BVtoRealCam[11] = aeT[2];

    a_aeRTMatrix_BVtoRealCam[12] = 0;
    a_aeRTMatrix_BVtoRealCam[13] = 0;
    a_aeRTMatrix_BVtoRealCam[14] = 0;
    a_aeRTMatrix_BVtoRealCam[15] = 1;

    for (lCnt = 0; lCnt < 16; lCnt++)
    {
        a_aeRTMatrix_RealCamtoBV[lCnt] = a_aeRTMatrix_BVtoRealCam[lCnt];
    }
    alMATRIX_InverseNbyN(a_aeRTMatrix_RealCamtoBV, 4);

    return 1;
}

BOOL COMMONK_RT_Calculation(
    const INT32 a_lCAMID,
    const INT32 a_lBVCenter_X, const INT32 a_lBVCenter_Y,
    const FLOAT64 *a_peSelectedFP_X, const FLOAT64 *a_peSelectedFP_Y,
    const FLOAT64 *a_peIdealFP_X, const FLOAT64 *a_peIdealFP_Y,
    const UINT8 a_ucNumPts,
    const FLOAT64 a_aeCurrentHomographyMatrix[9],
    const alFM_v2_1_Model *a_ptFisheyeModel_v2,
    const FLOAT32 a_fBirdsViewMMPP,
    FLOAT32 a_afOffset[6],
    INT32 a_lLMBoundarySwitch,
    alCAMERAINFO_ExtrinsicParams *a_ptExtrinsicParameter,
    alCOMMONK_CalibrationParams *a_ptCalibrationParameter
    )
{
    FLOAT64 aeFP_RealCamuUndistorX[COMMONK_MAX_FEATURE_NUMBER] = { 0 }, aeFP_RealCamuUndistorY[COMMONK_MAX_FEATURE_NUMBER] = { 0 };
    FLOAT64 aeFPIdealCoordInWorld_X[COMMONK_MAX_FEATURE_NUMBER] = { 0 }, aeFPIdealCoordInWorld_Y[COMMONK_MAX_FEATURE_NUMBER] = { 0 };
    FLOAT64 aeCalHomography[9] = { 0 }, aeDesignIntrinsicMatrix[9] = { 0 };
    FLOAT64 aeRotation[2][9] = { 0 }, aeTranslation[2][3] = { 0 };
#if COMMONK_VERIFY_CALIBRATION_LM
    FLOAT64 aeInitParameter[6] = { 0 }, aeGroundTruth[8] = { 0 }, aeParaLowBound[6] = { 0 }, aeParaHighBound[6] = { 0 };
    FLOAT64 *peLMwork = NULL, *peLMcovar = NULL;
    double opts[LM_OPTS_SZ] = { 0 }, info[LM_INFO_SZ] = { 0 };
    FLOAT64 aeH[9] = { 0 }, aeFuncOut[8] = { 0 };
    INT32 lLMReturn = 0, lCnt = 0, lLMState = 0;
    alCOMMONK_LM_Struct tLMInfo = { 0 };
#endif
    FLOAT64 aeRTMatrix_RealCamtoBV[16] = { 0 }, aeRTMatrix_BVtoRealCam[16] = {0};
    alCAMERAINFO_ExtrinsicParams tExtrinsicParameterTmp = { 0 };

    COMMONK_TransferBVFPtoUndistorRealCam(
        a_peSelectedFP_X,
        a_peSelectedFP_Y,
        a_ucNumPts,
        a_aeCurrentHomographyMatrix,
        a_ptFisheyeModel_v2,
        aeFP_RealCamuUndistorX,
        aeFP_RealCamuUndistorY
        );

    COMMONK_TransferFPFromPixel2mm(
        a_lBVCenter_X,
        a_lBVCenter_Y,
        a_peIdealFP_X,
        a_peIdealFP_Y,
        a_ucNumPts,
        a_fBirdsViewMMPP,
        aeFPIdealCoordInWorld_X,
        aeFPIdealCoordInWorld_Y
        );


    aeDesignIntrinsicMatrix[0] = a_ptFisheyeModel_v2->eFocalLength;
    aeDesignIntrinsicMatrix[4] = a_ptFisheyeModel_v2->eFocalLength;
    aeDesignIntrinsicMatrix[8] = 1;

    // get Homography Matrix
    COMMONK_GenerateM3x3(
        aeFP_RealCamuUndistorX,
        aeFP_RealCamuUndistorY,
        aeFPIdealCoordInWorld_X,
        aeFPIdealCoordInWorld_Y,
        a_ucNumPts,
        aeCalHomography
        );

    // normailize Homography Matrix
    /* for(lCnt = 0 ; lCnt < 9 ; lCnt++)
    {
    aeCalHomography[lCnt] = aeCalHomography[lCnt] / aeCalHomography[8];
    }*/

    // get RT Matrix
    COMMONK_DetermineRTMatrix(
        aeDesignIntrinsicMatrix,
        aeCalHomography,
        aeRTMatrix_RealCamtoBV,
        aeRTMatrix_BVtoRealCam
        );

#if COMMONK_VERIFY_CALIBRATION_LM == 1
    tLMInfo.lParameterNum = 6;

    for (lCnt = 0; lCnt < a_ucNumPts; lCnt++)
        tLMInfo.aeError[lCnt] = 0.5;

    tLMInfo.lPointNum = a_ucNumPts;
    tLMInfo.lViewNum = a_lCAMID;
    tLMInfo.lParameterNum = 6;
    memcpy(tLMInfo.aeCameraPosX, aeFP_RealCamuUndistorX, tLMInfo.lPointNum*sizeof(FLOAT64));
    memcpy(tLMInfo.aeCameraPosY, aeFP_RealCamuUndistorY, tLMInfo.lPointNum*sizeof(FLOAT64));

    memcpy(tLMInfo.aeWordPosX, aeFPIdealCoordInWorld_X, tLMInfo.lPointNum*sizeof(FLOAT64));
    memcpy(tLMInfo.aeWordPosY, aeFPIdealCoordInWorld_Y, tLMInfo.lPointNum*sizeof(FLOAT64));
    memcpy(tLMInfo.aeIntrinsic, aeDesignIntrinsicMatrix, 9 * sizeof(FLOAT64));

#if 1 // use design value as initial value and boundary
    aeInitParameter[0] = -a_ptExtrinsicParameter->fPitchAngle;
    aeInitParameter[1] = a_ptExtrinsicParameter->fYawAngle;
    aeInitParameter[2] = a_ptExtrinsicParameter->fRollAngle;
    aeInitParameter[3] = a_ptExtrinsicParameter->lCameraPosX;
    aeInitParameter[4] = a_ptExtrinsicParameter->lCameraPosY;
    aeInitParameter[5] = -a_ptExtrinsicParameter->lCameraPosZ;


    aeParaLowBound[0] = aeInitParameter[0] - a_afOffset[0];
    aeParaLowBound[1] = aeInitParameter[1] - a_afOffset[1];
    aeParaLowBound[2] = aeInitParameter[2] - a_afOffset[2];
    aeParaLowBound[3] = aeInitParameter[3] - a_afOffset[3];
    aeParaLowBound[4] = aeInitParameter[4] - a_afOffset[4];
    aeParaLowBound[5] = aeInitParameter[5] - a_afOffset[5];

    aeParaHighBound[0] = aeInitParameter[0] + a_afOffset[0];
    aeParaHighBound[1] = aeInitParameter[1] + a_afOffset[1];
    aeParaHighBound[2] = aeInitParameter[2] + a_afOffset[2];
    aeParaHighBound[3] = aeInitParameter[3] + a_afOffset[3];
    aeParaHighBound[4] = aeInitParameter[4] + a_afOffset[4];
    aeParaHighBound[5] = aeInitParameter[5] + a_afOffset[5];
#endif

    for (lCnt = 0; lCnt < 4; lCnt++)
    {
        aeGroundTruth[lCnt * 2] = aeFPIdealCoordInWorld_X[lCnt];
        aeGroundTruth[lCnt * 2 + 1] = aeFPIdealCoordInWorld_Y[lCnt];
    }

#if 0 // for test (test Homography or Jacobian function)
    // GetHomographyByParameter(aeInitParameter, aeDesignIntrinsicMatrix, aeH, 0, 2);
    COMMONK_PointTrabform(aeInitParameter, aeFuncOut, 6, tLMInfo.lPointNum * 2, &tLMInfo);
#else
    // Do LM Flow
    opts[0] = LM_INIT_MU; opts[1] = 1E-15; opts[2] = 1E-15; opts[3] = 1E-20; opts[4] = LM_DIFF_DELTA;
    peLMwork = malloc((LM_DIF_WORKSZ(tLMInfo.lParameterNum, tLMInfo.lPointNum * 2) + tLMInfo.lParameterNum*tLMInfo.lParameterNum)*sizeof(double));
    if (!peLMwork)
    {	// malloc fail
        assert(0);
    }
    peLMcovar = peLMwork + LM_DIF_WORKSZ(tLMInfo.lParameterNum, tLMInfo.lPointNum * 2);

#if 1	// finite difference approximated Jacobian
    if (a_lLMBoundarySwitch)
    {	// with boundary
        // ret=dlevmar_bc_der(hs01, jachs01, p, x, m, n, lb, ub, NULL, 1000, opts, info, NULL, NULL, NULL);
        lLMReturn = dlevmar_bc_dif(COMMONK_PointTrabform, aeInitParameter, aeGroundTruth, tLMInfo.lParameterNum, tLMInfo.lPointNum * 2, aeParaLowBound, aeParaHighBound, NULL, 1500, opts, info, peLMwork, peLMcovar, &tLMInfo); // with boundary constraint
    }
    else	// no boundary
    {
        lLMReturn = dlevmar_dif(COMMONK_PointTrabform, aeInitParameter, aeGroundTruth, tLMInfo.lParameterNum, tLMInfo.lPointNum * 2, 1000, opts, info, peLMwork, peLMcovar, &tLMInfo); // no Jacobian, caller allocates work memory, covariance estimated
    }
#else	// analytic Jacobian
    lLMReturn = dlevmar_der(COMMONK_PointTrabform, COMMONK_JacobianK, aeInitParameter, aeGroundTruth, tLMInfo.lParameterNum, tLMInfo.lPointNum * 2, 1500, opts, info, peLMwork, peLMcovar, &tLMInfo); // with analytic Jacobian
#endif

    free(peLMwork);
    // to fit INI file format
    a_ptExtrinsicParameter->fPitchAngle = (FLOAT32)(-aeInitParameter[0]);
    a_ptExtrinsicParameter->fYawAngle = (FLOAT32)(aeInitParameter[1]);
    a_ptExtrinsicParameter->fRollAngle = (FLOAT32)(aeInitParameter[2]);
    a_ptExtrinsicParameter->lCameraPosX = (INT32)(aeInitParameter[3]);
    a_ptExtrinsicParameter->lCameraPosY = (INT32)(aeInitParameter[4]);
    a_ptExtrinsicParameter->lCameraPosZ = (INT32)(-aeInitParameter[5]);

    aeRotation[0][0] = aeRTMatrix_BVtoRealCam[0];
    aeRotation[0][1] = aeRTMatrix_BVtoRealCam[1];
    aeRotation[0][2] = aeRTMatrix_BVtoRealCam[2];
    aeRotation[0][3] = aeRTMatrix_BVtoRealCam[4];
    aeRotation[0][4] = aeRTMatrix_BVtoRealCam[5];
    aeRotation[0][5] = aeRTMatrix_BVtoRealCam[6];
    aeRotation[0][6] = aeRTMatrix_BVtoRealCam[8];
    aeRotation[0][7] = aeRTMatrix_BVtoRealCam[9];
    aeRotation[0][8] = aeRTMatrix_BVtoRealCam[10];

    memcpy(aeRotation[1], aeRotation[0], sizeof(FLOAT64) * 9);

    alMATRIX_InverseNbyN(aeRotation[1], 3);

    aeTranslation[0][0] = aeRTMatrix_BVtoRealCam[3];
    aeTranslation[0][1] = aeRTMatrix_BVtoRealCam[7];
    aeTranslation[0][2] = aeRTMatrix_BVtoRealCam[11];

    aeTranslation[1][0] = aeInitParameter[3];
    aeTranslation[1][1] = aeInitParameter[4];
    aeTranslation[1][2] = aeInitParameter[5];

    memcpy(a_ptCalibrationParameter->aeRotationMatrix[0], aeRotation[0], sizeof(FLOAT64) * 9);
    memcpy(a_ptCalibrationParameter->aeRotationMatrix[1], aeRotation[1], sizeof(FLOAT64) * 9);
    memcpy(a_ptCalibrationParameter->aeTranslationMatrix[0], aeTranslation[0], sizeof(FLOAT64) * 3);
    memcpy(a_ptCalibrationParameter->aeTranslationMatrix[1], aeTranslation[1], sizeof(FLOAT64) * 3);
    memcpy(a_ptCalibrationParameter->aeIntrinsicMatrix, aeDesignIntrinsicMatrix, sizeof(FLOAT64) * 9);
#endif

#else // old algorithm (without LM)
    // get Extrinsic Parameter
    COMMONK_DetermineExtrinsicParameter(
        a_lCAMID,
        aeRTMatrix_RealCamtoBV,
        aeRTMatrix_BVtoRealCam,
        &tExtrinsicParameterTmp
        );

    // to fit INI file format
    a_ptExtrinsicParameter->fPitchAngle = -tExtrinsicParameterTmp.fPitchAngle;
    a_ptExtrinsicParameter->fYawAngle = -tExtrinsicParameterTmp.fYawAngle;
    a_ptExtrinsicParameter->fRollAngle = -tExtrinsicParameterTmp.fRollAngle;
    a_ptExtrinsicParameter->lCameraPosX = tExtrinsicParameterTmp.lCameraPosX;
    a_ptExtrinsicParameter->lCameraPosY = tExtrinsicParameterTmp.lCameraPosY;
    a_ptExtrinsicParameter->lCameraPosZ = -tExtrinsicParameterTmp.lCameraPosZ;

    aeRotation[0][0] = aeRTMatrix_BVtoRealCam[0];
    aeRotation[0][1] = aeRTMatrix_BVtoRealCam[1];
    aeRotation[0][2] = aeRTMatrix_BVtoRealCam[2];
    aeRotation[0][3] = aeRTMatrix_BVtoRealCam[4];
    aeRotation[0][4] = aeRTMatrix_BVtoRealCam[5];
    aeRotation[0][5] = aeRTMatrix_BVtoRealCam[6];
    aeRotation[0][6] = aeRTMatrix_BVtoRealCam[8];
    aeRotation[0][7] = aeRTMatrix_BVtoRealCam[9];
    aeRotation[0][8] = aeRTMatrix_BVtoRealCam[10];

    memcpy(aeRotation[1], aeRotation[0], sizeof(FLOAT64) * 9);

    alMATRIX_InverseNbyN(aeRotation[1], 3);

    aeTranslation[0][0] = aeRTMatrix_BVtoRealCam[3];
    aeTranslation[0][1] = aeRTMatrix_BVtoRealCam[7];
    aeTranslation[0][2] = aeRTMatrix_BVtoRealCam[11];

    aeTranslation[1][0] = tExtrinsicParameterTmp.lCameraPosX;
    aeTranslation[1][1] = tExtrinsicParameterTmp.lCameraPosY;
    aeTranslation[1][2] = tExtrinsicParameterTmp.lCameraPosZ;

    memcpy(a_ptCalibrationParameter->aeRotationMatrix[0], aeRotation[0], sizeof(FLOAT64) * 9);
    memcpy(a_ptCalibrationParameter->aeRotationMatrix[1], aeRotation[1], sizeof(FLOAT64) * 9);
    memcpy(a_ptCalibrationParameter->aeTranslationMatrix[0], aeTranslation[0], sizeof(FLOAT64) * 3);
    memcpy(a_ptCalibrationParameter->aeTranslationMatrix[1], aeTranslation[1], sizeof(FLOAT64) * 3);
    memcpy(a_ptCalibrationParameter->aeIntrinsicMatrix, aeDesignIntrinsicMatrix, sizeof(FLOAT64) * 9);
#endif
    return 1;
}
