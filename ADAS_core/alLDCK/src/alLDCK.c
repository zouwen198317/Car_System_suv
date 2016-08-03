
#include <assert.h>
#include "alLDCK.h"
#include "alMatrix.h"
#include "VLib.h"
#include "IMGLib.h"
#include <math.h>

#if alLDCK_TEST
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#if alLDCK_TEST // alLDCK_TEST // hard code 190 LDC ploy parameter
INT32 g_lIterCnt = 0;
alPointFLOAT64 g_atCornerRectified[alLDCK_CORNER_NUM] = { 0 };
#endif

static FLOAT64 alLDCK_ErrorEstimateDistance(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerRectified[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]);

static UINT8 Check(UINT8 *a_pucY, INT32 a_lWidth, INT32 a_lHeight, INT32 a_lX, INT32 a_lY);

static GetMean(UINT8 *a_pucY, INT32 a_lWidth, INT32 a_lHeight, INT32 a_lX, INT32 a_lY, alPointFLOAT64 *a_ptPoint);

static GetMean(UINT8 *a_pucY, INT32 a_lWidth, INT32 a_lHeight, INT32 a_lX, INT32 a_lY, alPointFLOAT64 *a_ptPoint)
{
    INT32 lCnt = 0;

    INT32 lV = 0, lH = 0, lX = 0, lY = 0, lSize = 0;

    lSize = 10;

    a_ptPoint->eX = 0;
    a_ptPoint->eY = 0;

    for (lV = -lSize; lV <= lSize; lV++)
    {
        for (lH = -lSize; lH <= lSize; lH++)
        {
            lX = a_lX + lH;
            lY = a_lY + lV;
            if (a_pucY[lY*a_lWidth + lX])
            {
                lCnt++;
                a_ptPoint->eX += lX;
                a_ptPoint->eY += lY;
            }
        }
    }
    a_ptPoint->eX /= lCnt;
    a_ptPoint->eY /= lCnt;
}

static UINT8 Check(UINT8 *a_pucY, INT32 a_lWidth, INT32 a_lHeight, INT32 a_lX, INT32 a_lY)
{
    UINT8 ucCnt = 0;

    INT32 lV = 0, lH = 0, lX = 0, lY = 0;

    for (lV = -1; lV <= 1; lV++)
    {
        for (lH = -1; lH <= 1; lH++)
        {
            lX = a_lX + lH;
            lY = a_lY + lV;
            if (a_pucY[lY*a_lWidth + lX])
            {
                ucCnt++;
            }
        }
    }

    if (ucCnt > alLDCK_CORNER_CHECK_TH)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }


}

static FLOAT64 alLDCK_ErrorEstimateDistance(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerRectified[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    )
{
    FLOAT64 eError = 0, eTmpX = 0, eTmpY = 0, eErrorMax = 0;
    INT32 lCnt = 0, lCntEnable = 0;

    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        if (!a_aucCornerFlag[lCnt])
        { // 有偵測到的位置才計算誤差
            eTmpX = (a_atCornerIdeal[lCnt].eX - a_atCornerRectified[lCnt].eX)*(a_atCornerIdeal[lCnt].eX - a_atCornerRectified[lCnt].eX);
            eTmpY = (a_atCornerIdeal[lCnt].eY - a_atCornerRectified[lCnt].eY)*(a_atCornerIdeal[lCnt].eY - a_atCornerRectified[lCnt].eY);
            eError += sqrt(eTmpX + eTmpY);

            lCntEnable++;
        }
    }
    eError = eError / lCntEnable;

    return eError;
}

FLOAT64 alLDCK_EstimateErrorByParams(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alLDCK_LDC_Params *a_ptParams_Current,
    alPointFLOAT64 a_atCorner[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    )
{
    alLDCK_LDC_Params tParamsTmp;
    alPointFLOAT64 atCornerUndistorted[alLDCK_CORNER_NUM] = { 0 };
    alPointFLOAT64 atCornerRectified[alLDCK_CORNER_NUM] = { 0 };
    FLOAT64 aeH[COMMONK_M33_ELEMENT_CNT] = { 0 }, aeH_Inverse[COMMONK_M33_ELEMENT_CNT] = { 0 }, eError = 0;
#if alLDCK_TEST // hard code 190 LDC ploy parameter
    IplImage *ptLogImg = NULL;
    FLOAT64 eErrorInit = 0;
    FLOAT64 eErrorFinal = 0;
    FLOAT64 eErrorDiff = 0;
    FLOAT64 eErrorDistance = 0;
    INT32 lCnt = 0;
#endif

    memcpy(&tParamsTmp, a_ptParams_Current, sizeof(alLDCK_LDC_Params));

    alLDCK_DistortionCorrectionByParameter(&tParamsTmp, a_atCorner, atCornerUndistorted);
#if alLDCK_TEST // alLDCK_TEST // hard code 190 LDC ploy parameter
    if (g_lIterCnt == 0)
    {
        ptLogImg = cvLoadImage("./Undistorted_Left.bmp", CV_LOAD_IMAGE_COLOR);
        for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
        {
            if (!a_aucCornerFlag[lCnt])
            {
                cvCircle(ptLogImg, cvPoint((INT32)atCornerUndistorted[lCnt].eX, (INT32)atCornerUndistorted[lCnt].eY), 3, CV_RGB(255, 0, 0), 2, CV_AA, 0);
            }
        }
        cvSaveImage("Corner_In_Undostorted.jpg", ptLogImg, 0);
        cvReleaseImage(&ptLogImg);
    }
#endif
    alLDCK_GenHomographyMatrix(
        a_aucCornerFlag, a_aucCornerFlag_H_Matrix,
        atCornerUndistorted,
        a_atCornerIdeal,
        aeH, aeH_Inverse
        );

    alLDCK_CornerRectify(atCornerUndistorted, aeH, atCornerRectified);

#if alLDCK_TEST // alLDCK_TEST 
    if (g_lIterCnt == 0)
    {
        ptLogImg = cvLoadImage("./pattern2.jpg", CV_LOAD_IMAGE_COLOR);
        for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
        {
            if (!a_aucCornerFlag[lCnt])
            {
                cvCircle(ptLogImg, cvPoint((INT32)a_atCornerIdeal[lCnt].eX, (INT32)a_atCornerIdeal[lCnt].eY), 3, CV_RGB(0, 255, 0), 2, CV_AA, 0);
                cvCircle(ptLogImg, cvPoint((INT32)atCornerRectified[lCnt].eX, (INT32)atCornerRectified[lCnt].eY), 3, CV_RGB(255, 0, 0), 2, CV_AA, 0);
            }
        }
        cvSaveImage("Corner_LDC_No_K.jpg", ptLogImg, 0);
        cvReleaseImage(&ptLogImg);
    }
    memcpy(g_atCornerRectified, atCornerRectified, sizeof(alPointFLOAT64)*alLDCK_CORNER_NUM);
#endif

    eError = alLDCK_ErrorEstimate(a_aucCornerFlag, atCornerRectified, a_atCornerIdeal);

#if alLDCK_TEST // alLDCK_TEST 
    if (g_lIterCnt == 0)
    {
        eErrorDistance = alLDCK_ErrorEstimateDistance(a_aucCornerFlag, atCornerRectified, a_atCornerIdeal);
        printf("Init eErrorDistance: %f\n", eErrorDistance);
    }
    g_lIterCnt++; //
#endif

    return eError;
}

void alLDCK_Main(UINT8 *a_pucSrcY, alFM_v2_1_Model *a_ptFM_v2_Model, alLDCK_Data *a_ptData)
{
    INT32 lCnt = 0, lIterCnt = 0;
    FLOAT64 aeH[COMMONK_M33_ELEMENT_CNT] = { 0 }, aeH_Inverse[COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 eError = 0;
#if alLDCK_TEST // hard code 190 LDC ploy parameter
    IplImage *ptLogImg = NULL;
    FLOAT64 eErrorInit = 0;
    FLOAT64 eErrorFinal = 0;
    FLOAT64 eErrorDiff = 0;
    FLOAT64 eErrorDistance = 0;
#endif

    a_ptData->tParams_Default.eFocalLength = a_ptFM_v2_Model->eFocalLength;
    a_ptData->tParams_Default.tResizeRatio.eX = a_ptFM_v2_Model->eResizeRatio;
    a_ptData->tParams_Default.tResizeRatio.eY = 1; // tbd
    a_ptData->tParams_Default.ulSensorPixelSize = a_ptFM_v2_Model->ulSensorPixelSize;
    a_ptData->tParams_Default.tCenter.eX = a_ptFM_v2_Model->uwCOD_X;
    a_ptData->tParams_Default.tCenter.eY = a_ptFM_v2_Model->uwCOD_Y;
#if alLDCK_TEST // hard code 190 LDC ploy parameter
    a_ptData->tParams_Default.aeCoe[5] = 10.69595524;
    a_ptData->tParams_Default.aeCoe[4] = -43.2251274248814;
    a_ptData->tParams_Default.aeCoe[3] = 71.8741295693077;
    a_ptData->tParams_Default.aeCoe[2] = -72.0248849704767;
    a_ptData->tParams_Default.aeCoe[1] = 90.5009314970432;
    a_ptData->tParams_Default.aeCoe[0] = -0.558060816130617;
#endif
    memcpy(&a_ptData->tParams_Current, &a_ptData->tParams_Default, sizeof(alLDCK_LDC_Params));

    alLDCK_CoenerDetect(a_pucSrcY, a_ptFM_v2_Model, a_ptData);

    while (lIterCnt < alLDCK_MAX_ITER_TIME)
    {
#if alLDCK_TEST // hard code 190 LDC ploy parameter
        g_lIterCnt = lIterCnt;
#endif   
        eError = alLDCK_EstimateErrorByParams(
            a_ptData->aucCornerFlag,
            a_ptData->aucCornerFlag_H_Matrix,
            &a_ptData->tParams_Current,
            a_ptData->atCorner,
            a_ptData->atCornerIdeal
        );      

#if alLDCK_TEST // hard code 190 LDC ploy parameter
        eErrorDiff = eErrorFinal - eError;
        eErrorInit = (lIterCnt == 0) ? eError : eErrorInit;
        eErrorFinal = eError;    
#endif
        if (eError < alLDCK_ERROR_TH)
        { // break
            break;
        }
        else
        { // update parameter
            lIterCnt++;
            alLDCK_UpdateParameter(
                lIterCnt,
                a_ptData->aucCornerFlag,
                a_ptData->aucCornerFlag_H_Matrix,
                &a_ptData ->tParams_Default,
                &a_ptData->tParams_Current,
                a_ptData->atCorner, a_ptData->atCornerIdeal
            );
        }
    }

#if alLDCK_TEST // hard code 190 LDC ploy parameter
    ptLogImg = cvLoadImage("./pattern2.jpg", CV_LOAD_IMAGE_COLOR);
    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        if (!a_ptData->aucCornerFlag[lCnt])
        {
            cvCircle(ptLogImg, cvPoint((INT32)a_ptData->atCornerIdeal[lCnt].eX, (INT32)a_ptData->atCornerIdeal[lCnt].eY), 3, CV_RGB(0, 255, 0), 2, CV_AA, 0);
            cvCircle(ptLogImg, cvPoint((INT32)g_atCornerRectified[lCnt].eX, (INT32)g_atCornerRectified[lCnt].eY), 3, CV_RGB(255, 0, 0), 2, CV_AA, 0);
        }
    }
    cvSaveImage("Corner_LDCK.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);

    printf("eErrorInit: %f eErrorFinal: %f \n", eErrorInit, eErrorFinal);

    eErrorDistance = alLDCK_ErrorEstimateDistance(a_ptData->aucCornerFlag, g_atCornerRectified, a_ptData->atCornerIdeal);

    printf("eErrorDistance: %f\n", eErrorDistance);

    for (lCnt = 0; lCnt < 6; lCnt++)
    {
        printf("Coe[%d]: %f \n", lCnt, a_ptData->tParams_Current.aeCoe[lCnt]);
    }
    printf("Cx: %f Cy: %f \n", a_ptData->tParams_Current.tCenter.eX, a_ptData->tParams_Current.tCenter.eY);
#endif
}

void alLDCK_GenHomographyMatrix(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM],
    FLOAT64 a_peH[COMMONK_M33_ELEMENT_CNT],
    FLOAT64 a_peH_Inv[COMMONK_M33_ELEMENT_CNT]
    )
{
    INT32 lCnt = 0, lCntEnable = 0;
    FLOAT64 aeSrcX[alLDCK_CORNER_NUM] = { 0 }, aeSrcY[alLDCK_CORNER_NUM] = { 0 }, aeDestX[alLDCK_CORNER_NUM] = { 0 }, aeDestY[alLDCK_CORNER_NUM] = { 0 };

    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        if (!a_aucCornerFlag_H_Matrix[lCnt] && !a_aucCornerFlag[lCnt])
        {
            aeSrcX[lCntEnable] = a_atCornerIdeal[lCnt].eX;
            aeSrcY[lCntEnable] = a_atCornerIdeal[lCnt].eY;

            aeDestX[lCntEnable] = a_atCornerUndistorted[lCnt].eX;
            aeDestY[lCntEnable] = a_atCornerUndistorted[lCnt].eY;

            lCntEnable++;
        }
    }
    if (!COMMONK_GenerateM3x3(aeSrcX, aeSrcY, aeDestX, aeDestY, lCntEnable, a_peH)) // dest to src
    {
        assert(0);
    }
    memcpy(a_peH_Inv, a_peH, sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
    alMATRIX_InverseNbyN(a_peH_Inv, 3);
}

void alLDCK_GenHomographyMatrix_(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM],
    FLOAT64 a_peH[COMMONK_M33_ELEMENT_CNT],
    FLOAT64 a_peH_Inv[COMMONK_M33_ELEMENT_CNT]
    )
{
    INT32 lCnt = 0, lCntEnable = 0;
    FLOAT64 aeSrcX[alLDCK_CORNER_NUM] = { 0 }, aeSrcY[alLDCK_CORNER_NUM] = { 0 }, aeDestX[alLDCK_CORNER_NUM] = { 0 }, aeDestY[alLDCK_CORNER_NUM] = { 0 };

    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        aeSrcX[lCnt] = a_atCornerIdeal[lCnt].eX;
        aeSrcY[lCnt] = a_atCornerIdeal[lCnt].eY;

        aeDestX[lCnt] = a_atCornerUndistorted[lCnt].eX;
        aeDestY[lCnt] = a_atCornerUndistorted[lCnt].eY;
    }
    if (!COMMONK_GenerateM3x3(aeSrcX, aeSrcY, aeDestX, aeDestY, alLDCK_CORNER_NUM, a_peH)) // dest to src
    {
        assert(0);
    }
    memcpy(a_peH_Inv, a_peH, sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
    alMATRIX_InverseNbyN(a_peH_Inv, 3);
}

void alLDCK_UpdateParameter(
    INT32 a_lIterCnt,
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    UINT8 a_aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM],
    alLDCK_LDC_Params *a_ptParams_Default,
    alLDCK_LDC_Params *a_ptParams_Current,
    alPointFLOAT64 a_atCorner[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    )
{
    INT32 lCnt = 0;
    alLDCK_LDC_Params tParamsTmp = {0};
    alLDCK_LDC_Params atParamsGradient[8] = {0}; // 
    alPointFLOAT64 atCornerUndistorted[alLDCK_CORNER_NUM] = { 0 };
    alPointFLOAT64 atCornerRectified[alLDCK_CORNER_NUM] = { 0 };
    alPointFLOAT64 tDiff = { 0 };
    FLOAT64 aeH[COMMONK_M33_ELEMENT_CNT] = { 0 }, aeH_Inverse[COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 eError = 0, aeErrorGradient[8] = { 0 }, aeGradient[8] = { 0 }, eLearnRate = 0;
#if alLDCK_TEST
    FLOAT64 eErrorTest = 0;
    FLOAT64 eErrorDiff = 0;
#endif

    memcpy(&tParamsTmp, a_ptParams_Current, sizeof(alLDCK_LDC_Params));

    for (lCnt = 0; lCnt < 8 ; lCnt++)
    {
        memcpy(&atParamsGradient[lCnt], a_ptParams_Current, sizeof(alLDCK_LDC_Params));
    }

    atParamsGradient[0].aeCoe[0] += alLDCK_DELTA_COE; // x^0
    atParamsGradient[1].aeCoe[1] += alLDCK_DELTA_COE; // x^1
    atParamsGradient[2].aeCoe[2] += alLDCK_DELTA_COE; // x^2
    atParamsGradient[3].aeCoe[3] += alLDCK_DELTA_COE; // x^3
    atParamsGradient[4].aeCoe[4] += alLDCK_DELTA_COE; // x^4
    atParamsGradient[5].aeCoe[5] += alLDCK_DELTA_COE; // x^5
    atParamsGradient[6].tCenter.eX += alLDCK_DELTA_CENTER; // Cx
    atParamsGradient[7].tCenter.eY += alLDCK_DELTA_CENTER; // Cy

    eError = alLDCK_EstimateErrorByParams(
        a_aucCornerFlag, a_aucCornerFlag_H_Matrix, &tParamsTmp, a_atCorner, a_atCornerIdeal);

    for (lCnt = 0; lCnt < 8; lCnt++)
    {
        aeErrorGradient[lCnt] = alLDCK_EstimateErrorByParams(
            a_aucCornerFlag, a_aucCornerFlag_H_Matrix, &atParamsGradient[lCnt], a_atCorner, a_atCornerIdeal);
        aeGradient[lCnt] = aeErrorGradient[lCnt] - eError;
    }

#if alLDCK_ADAPTIVE_LEARN_RATE_MODE // 學習率遞減
    eLearnRate = (alLDCK_LERAN_RATE / a_lIterCnt) + alLDCK_LERAN_RATE_MIN;
#else // 固定學習率
    eLearnRate = alLDCK_LERAN_RATE;
#endif

    for (lCnt = 0; lCnt < 6; lCnt++)
    {
        a_ptParams_Current->aeCoe[lCnt] -= eLearnRate*aeGradient[lCnt];
    }
    a_ptParams_Current->tCenter.eX -= eLearnRate*aeGradient[6];
    a_ptParams_Current->tCenter.eY -= eLearnRate*aeGradient[7];

#if 0 // alLDCK_TEST
    eErrorTest = alLDCK_EstimateErrorByParams(
        a_aucCornerFlag, a_aucCornerFlag_H_Matrix,
        a_ptParams_Current, a_atCorner, a_atCornerIdeal);

    eErrorDiff = eError - eErrorTest;
#endif

    tDiff.eX = a_ptParams_Current->tCenter.eX - a_ptParams_Default->tCenter.eX;
    tDiff.eY = a_ptParams_Current->tCenter.eY - a_ptParams_Default->tCenter.eY;

    if (tDiff.eX > alLDCK_MAX_CENTER_OFFSET)
    {
        a_ptParams_Current->tCenter.eX = a_ptParams_Default->tCenter.eX + alLDCK_MAX_CENTER_OFFSET;
    }
    if (tDiff.eX < -alLDCK_MAX_CENTER_OFFSET)
    {
        a_ptParams_Current->tCenter.eX = a_ptParams_Default->tCenter.eX - alLDCK_MAX_CENTER_OFFSET;
    }
    
    if (tDiff.eY > alLDCK_MAX_CENTER_OFFSET)
    {
        a_ptParams_Current->tCenter.eY = a_ptParams_Default->tCenter.eY + alLDCK_MAX_CENTER_OFFSET;
    }
    if (tDiff.eY < -alLDCK_MAX_CENTER_OFFSET)
    {
        a_ptParams_Current->tCenter.eY = a_ptParams_Default->tCenter.eY - alLDCK_MAX_CENTER_OFFSET;
    }
}

void alLDCK_CornerRectify(
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM],
    FLOAT64 aeH[COMMONK_M33_ELEMENT_CNT],
    alPointFLOAT64 a_atCornerRectified[alLDCK_CORNER_NUM]
    )
{
    INT32 lCnt = 0;
    
    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        COMMONK_PerformCoordinatesTransform(
            aeH, a_atCornerUndistorted[lCnt].eX, a_atCornerUndistorted[lCnt].eY,
            &a_atCornerRectified[lCnt].eX, &a_atCornerRectified[lCnt].eY
        );
    }
}

void alLDCK_DistortionCorrectionByParameter(
    alLDCK_LDC_Params *a_ptParams_Current,
    alPointFLOAT64 a_atCorner[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerUndistorted[alLDCK_CORNER_NUM]
    )
{
    INT32 lCnt = 0;
    FLOAT64 eDu;
    FLOAT64 eDistX_ = 0, eDistY_ = 0;
    FLOAT64 eDi = 0;
    FLOAT64 eTheta = 0, eSinPhi = 0, eCosPhi = 0, eTanTheta = 0;
    

    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        { // 有偵測到角點才計算 ??  (TBD)
            // 計算 X, Y 與 COD 的距離
            eDistX_ = (a_atCorner[lCnt].eX - a_ptParams_Current->tCenter.eX) / a_ptParams_Current->tResizeRatio.eX;
            eDistY_ = (a_atCorner[lCnt].eY - a_ptParams_Current->tCenter.eY) / a_ptParams_Current->tResizeRatio.eY;

            eDistX_ *= a_ptParams_Current->ulSensorPixelSize / 1000000.0;
            eDistY_ *= a_ptParams_Current->ulSensorPixelSize / 1000000.0;

            if (eDistX_ == 0 && eDistY_ == 0)
            {
                // 計算出 反魚眼 座標
                a_atCornerUndistorted[lCnt].eX = 0;
                a_atCornerUndistorted[lCnt].eY = 0;
            }
            else
            {
                // 計算 Pixel Di
                eDi = sqrt(eDistX_ * eDistX_ + eDistY_ * eDistY_);

                // 由多項式係數
                eTheta = a_ptParams_Current->aeCoe[5] * eDi*eDi*eDi*eDi*eDi +
                    a_ptParams_Current->aeCoe[4] * eDi*eDi*eDi*eDi +
                    a_ptParams_Current->aeCoe[3] * eDi*eDi*eDi +
                    a_ptParams_Current->aeCoe[2] * eDi*eDi +
                    a_ptParams_Current->aeCoe[1] * eDi +
                    a_ptParams_Current->aeCoe[0];
                eTheta *= alPI / 180.0;

                // 計算 phi, theta 的 sin , cos
                eSinPhi = eDistY_ / eDi;
                eCosPhi = eDistX_ / eDi;
                eTanTheta = tan(eTheta);

                eDu = a_ptParams_Current->eFocalLength * eTanTheta;

                a_atCornerUndistorted[lCnt].eX = eDu * eCosPhi;
                a_atCornerUndistorted[lCnt].eY = eDu * eSinPhi;
            }
            a_atCornerUndistorted[lCnt].eX = a_atCornerUndistorted[lCnt].eX * 1000000.0 / a_ptParams_Current->ulSensorPixelSize + a_ptParams_Current->tCenter.eX;
            a_atCornerUndistorted[lCnt].eY = a_atCornerUndistorted[lCnt].eY * 1000000.0 / a_ptParams_Current->ulSensorPixelSize + a_ptParams_Current->tCenter.eY;
        }
    }
}

UINT8 alLDCK_FPDetect(INT32 a_lWidth, INT32 a_lHeight, UINT8 *a_pucSrcY, UINT8 *a_pucBuffer, alPointFLOAT64 a_atFP[alLDCK_FP_NUM])
{
    char acmaskX[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
    char acmaskY[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
    short *pwBufGradX = NULL;
    short *pwBufGradY = NULL;
    short *pwHarrisScore = NULL;
    UINT8 *pucScratchBuffer = NULL; // 運算用 buffer 最少需要 96 x a_lWidth (byte)
    UINT8 *pucHarrisBuffer = NULL, ucCornerCheck = 0;
    INT32 lCnt = 0, lVlibOot = 0, lY = 0, lX = 0, lCornerCnt = 0;
#if alLDCK_TEST // log corner
    IplImage *ptLogImg = NULL;
    CvScalar value = { 0 };
#endif

    if (a_pucBuffer)
    {
        pwBufGradX = (short *)a_pucBuffer;
        pwBufGradY = (short *)a_pucBuffer;
        pwHarrisScore = (short *)a_pucBuffer;
        pucScratchBuffer = a_pucBuffer;
        pucHarrisBuffer = a_pucBuffer;
    }
    else
    {
        pwBufGradX = (short*)malloc(a_lWidth*a_lHeight * sizeof(short));
        pwBufGradY = (short*)malloc(a_lWidth*a_lHeight * sizeof(short));
        pwHarrisScore = (short*)malloc(a_lWidth*a_lHeight * sizeof(short));
        pucScratchBuffer = (UINT8*)malloc(a_lWidth * 100 * sizeof(UINT8));
        pucHarrisBuffer = (UINT8*)malloc(a_lWidth * a_lHeight * sizeof(UINT8));
    }


    for (lCnt = 0; lCnt < a_lHeight - 2; lCnt++)
    {
        IMG_conv_3x3_i8_c16s_altek
            (
            a_pucSrcY + lCnt*a_lWidth, // const unsigned char *restrict  imgin_ptr,
            pwBufGradX + lCnt*a_lWidth + a_lWidth + 1, // short               *restrict imgout_ptr,
            a_lWidth, a_lWidth, acmaskX, 2
        );
    }

    for (lCnt = 0; lCnt < a_lHeight - 2; lCnt++)
    {
        IMG_conv_3x3_i8_c16s_altek
            (
            a_pucSrcY + lCnt*a_lWidth, // const unsigned char *restrict  imgin_ptr,
            pwBufGradY + lCnt*a_lWidth + a_lWidth + 1, // short               *restrict imgout_ptr,
            a_lWidth, a_lWidth, acmaskY, 2
        );
    }

    lVlibOot = VLIB_harrisScore_7x7(
        pwBufGradX, pwBufGradY,
        a_lWidth, a_lHeight,
        pwHarrisScore,
        alLDCK_HARRISS_K, pucScratchBuffer
        );

    for (lY = 0; lY < a_lHeight; lY++)
    {
        for (lX = 0; lX < a_lWidth; lX++)
        {
            pucHarrisBuffer[lY*a_lWidth + lX] = (pwHarrisScore[lY*a_lWidth + lX] > alLDCK_HARRISS_SCORE_TH) ? 255 : 0;
        }
    }

#if alLDCK_TEST // log corner
    ptLogImg = cvLoadImage("./Noline1_enhance.jpg", CV_LOAD_IMAGE_COLOR);
    for (lY = 0; lY < a_lHeight; lY++)
    {
        for (lX = 0; lX < a_lWidth; lX++)
        {
            if (pucHarrisBuffer[lY*a_lWidth + lX])
            {
                cvSet2D(ptLogImg, lY, lX, cvScalar(0, 0, 255,0));
            }
        }
    }
    cvSaveImage("Hariss_RawLOG_Vlib.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);
#endif

    //  search FP up
    lCornerCnt = 0;
    lX = a_lWidth >> 1;
    for (lY = a_lHeight >> 1; lY >= 0; lY--)
    {
        if (pucHarrisBuffer[lY*a_lWidth + lX])
        {
            ucCornerCheck = Check(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY);
            if (ucCornerCheck)
            {
                lCornerCnt++;
                if (lCornerCnt == alLDCK_CORNER_CHECK_GAP)
                {
                    GetMean(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY, &a_atFP[0]);
                    break;
                }
                lY -= 20;
            }
        }
    }

    //  search FP right
    lCornerCnt = 0;
    lY = a_lHeight >> 1;
    for (lX = a_lWidth >> 1; lX < a_lWidth; lX++)
    {
        if (pucHarrisBuffer[lY*a_lWidth + lX])
        {
            ucCornerCheck = Check(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY);
            if (ucCornerCheck)
            {
                lCornerCnt++;
                if (lCornerCnt == alLDCK_CORNER_CHECK_GAP)
                {
                    GetMean(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY, &a_atFP[1]);
                    break;
                }
                lX += 20;
            }
        }
    }

    //  search FP down
    lCornerCnt = 0;
    lX = a_lWidth >> 1;
    for (lY = a_lHeight >> 1; lY < a_lHeight; lY++)
    {
        if (pucHarrisBuffer[lY*a_lWidth + lX])
        {
            ucCornerCheck = Check(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY);
            if (ucCornerCheck)
            {
                lCornerCnt++;
                if (lCornerCnt == alLDCK_CORNER_CHECK_GAP)
                {
                    GetMean(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY, &a_atFP[2]);
                    break;
                }
                lY += 20;
            }
        }
    }

    //  search FP left
    lCornerCnt = 0;
    lY = a_lHeight >> 1;
    for (lX = a_lWidth >> 1; lX >= 0; lX--)
    {
        if (pucHarrisBuffer[lY*a_lWidth + lX])
        {

            ucCornerCheck = Check(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY);
            if (ucCornerCheck)
            {
                lCornerCnt++;
                if (lCornerCnt == alLDCK_CORNER_CHECK_GAP)
                {
                    GetMean(pucHarrisBuffer, a_lWidth, a_lHeight, lX, lY, &a_atFP[3]);
                    break;
                }
                lX -= 20;
            }
        }
    }



    if (!a_pucBuffer)
    {
        free(pwBufGradX);
        free(pwBufGradY);
        free(pwHarrisScore);
        free(pucScratchBuffer);
        free(pucHarrisBuffer);
    }

    return 1;
}

void alLDCK_CoenerDetect(UINT8 *a_pucSrcY, alFM_v2_1_Model *a_ptFM_v2_Model, alLDCK_Data *a_ptData)
{
    FLOAT64 aeUndistortX[alLDCK_CORNER_NUM] = { 0 };
    FLOAT64 aeUndistortY[alLDCK_CORNER_NUM] = { 0 };
    FLOAT64 aeIdealX[alLDCK_CORNER_NUM] = { 0 };
    FLOAT64 aeIdealY[alLDCK_CORNER_NUM] = { 0 };
    FLOAT64 aeH[COMMONK_M33_ELEMENT_CNT] = { 0 }, aeH_Inverse[COMMONK_M33_ELEMENT_CNT] = { 0 };
    FLOAT64 eTmpX = 0, eTmpY = 0;
    FLOAT64 eDistX = 0, eDistY = 0;
    INT32 lCnt = 0, lX = 0, lY = 0, lDistX = 0, lDistY = 0;
    UINT8 *pucRecImage = NULL;

#if alLDCK_TEST // for test (opencv log)
    FLOAT64 aeTestX[4] = { 0 };
    FLOAT64 aeTestY[4] = { 0 };
    IplImage * ptPicGray = NULL;
    char cText[MAX_PATH] = { 0 };
    alPointFLOAT64 atFP[alLDCK_FP_NUM] = {0};
#endif

#if alLDCK_TEST // for test (opencv log)
    ptPicGray = cvCreateImage(cvSize(a_ptFM_v2_Model->uwSrcWidth, a_ptFM_v2_Model->uwSrcHeight), IPL_DEPTH_8U, 1);

    memcpy(ptPicGray->imageData, a_pucSrcY, sizeof(UINT8)*ptPicGray->imageSize);
    sprintf_s(cText, MAX_PATH, "SrcImage.jpg");
    cvSaveImage(cText, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
#endif

    // 先在原始影像上 抓到要的特徵點 (最靠近中心的幾個角點)
#if alLDCK_TEST // for hard code test
    alLDCK_FPDetect(
        a_ptFM_v2_Model->uwDestWidth, a_ptFM_v2_Model->uwDestHeight,
        a_pucSrcY, NULL, atFP);
#if 0 // near
    // A
    a_ptData->atFP[0].eX = 295;
    a_ptData->atFP[0].eY = 168;

    // B
    a_ptData->atFP[1].eX = 388;
    a_ptData->atFP[1].eY = 256;

    // C
    a_ptData->atFP[2].eX = 297;
    a_ptData->atFP[2].eY = 330;

    // D
    a_ptData->atFP[3].eX = 211;
    a_ptData->atFP[3].eY = 251;

    // Ideal A
    a_ptData->atFPIdeal[0].eX = 382;
    a_ptData->atFPIdeal[0].eY = 176;

    // Ideal B
    a_ptData->atFPIdeal[1].eX = 425;
    a_ptData->atFPIdeal[1].eY = 218;

    // Ideal C
    a_ptData->atFPIdeal[2].eX = 382;
    a_ptData->atFPIdeal[2].eY = 262;

    // Ideal D
    a_ptData->atFPIdeal[3].eX = 339;
    a_ptData->atFPIdeal[3].eY = 218;
#elif 0 // far
    // A
    a_ptData->atFP[0].eX = 360;
    a_ptData->atFP[0].eY = 78;

    // B
    a_ptData->atFP[1].eX = 526;
    a_ptData->atFP[1].eY = 240;

    // C
    a_ptData->atFP[2].eX = 360;
    a_ptData->atFP[2].eY = 413;

    // D
    a_ptData->atFP[3].eX = 154;
    a_ptData->atFP[3].eY = 239;

    // Ideal A
    a_ptData->atFPIdeal[0].eX = 360;
    a_ptData->atFPIdeal[0].eY = 105;

    // Ideal B
    a_ptData->atFPIdeal[1].eX = 497;
    a_ptData->atFPIdeal[1].eY = 240;

    // Ideal C
    a_ptData->atFPIdeal[2].eX = 360;
    a_ptData->atFPIdeal[2].eY = 376;

    // Ideal D
    a_ptData->atFPIdeal[3].eX = 226;
    a_ptData->atFPIdeal[3].eY = 240;
#else // by read point
    // A
    a_ptData->atFP[0].eX = a_ptData->atCorner[13].eX;
    a_ptData->atFP[0].eY = a_ptData->atCorner[13].eY;

    // B
    a_ptData->atFP[1].eX = a_ptData->atCorner[33].eX;
    a_ptData->atFP[1].eY = a_ptData->atCorner[33].eY;

    // C
    a_ptData->atFP[2].eX = a_ptData->atCorner[49].eX;
    a_ptData->atFP[2].eY = a_ptData->atCorner[49].eY;

    // D
    a_ptData->atFP[3].eX = a_ptData->atCorner[29].eX;
    a_ptData->atFP[3].eY = a_ptData->atCorner[29].eY;

    // Ideal A
    a_ptData->atFPIdeal[0].eX = a_ptData->atCornerIdeal[13].eX;
    a_ptData->atFPIdeal[0].eY = a_ptData->atCornerIdeal[13].eY;

    // Ideal B
    a_ptData->atFPIdeal[1].eX = a_ptData->atCornerIdeal[33].eX;
    a_ptData->atFPIdeal[1].eY = a_ptData->atCornerIdeal[33].eY;

    // Ideal C
    a_ptData->atFPIdeal[2].eX = a_ptData->atCornerIdeal[49].eX;
    a_ptData->atFPIdeal[2].eY = a_ptData->atCornerIdeal[49].eY;

    // Ideal D
    a_ptData->atFPIdeal[3].eX = a_ptData->atCornerIdeal[29].eX;
    a_ptData->atFPIdeal[3].eY = a_ptData->atCornerIdeal[29].eY;
#endif

#else

#endif

    // 魚眼校正
    for (lCnt = 0; lCnt < alLDCK_FP_NUM; lCnt++)
    {
        alFM_v2_1_Distorted2Undistorted_PlanarPixel(
            a_ptFM_v2_Model,
            a_ptData->atFP[lCnt].eX,
            a_ptData->atFP[lCnt].eY,
            &aeUndistortX[lCnt], &aeUndistortY[lCnt]
        );
        aeIdealX[lCnt] = a_ptData->atFPIdeal[lCnt].eX;
        aeIdealY[lCnt] = a_ptData->atFPIdeal[lCnt].eY;
    }

    // 產生 Homography matrix
    if (!COMMONK_GenerateM3x3(aeUndistortX, aeUndistortY, aeIdealX, aeIdealY, alLDCK_FP_NUM, aeH)) // dest to src
    {
        assert(0);
    }
    memcpy(aeH_Inverse, aeH, sizeof(FLOAT64) * COMMONK_M33_ELEMENT_CNT);
    alMATRIX_InverseNbyN(aeH_Inverse, 3);

#if alLDCK_TEST // for test (opencv log)
    for (lCnt = 0; lCnt < alLDCK_FP_NUM; lCnt++)
    {
        COMMONK_PerformCoordinatesTransform(aeH_Inverse, aeUndistortX[lCnt], aeUndistortY[lCnt], &aeTestX[lCnt], &aeTestY[lCnt]);
    }
#endif


    // Rectify Source Image
    pucRecImage = (UINT8*)malloc(a_ptFM_v2_Model->uwDestHeight*a_ptFM_v2_Model->uwDestWidth * sizeof(UINT8));
    for (lY = 0; lY < a_ptFM_v2_Model->uwDestHeight; lY++)
    {
        for (lX = 0; lX < a_ptFM_v2_Model->uwDestWidth; lX++)
        {
#if 1
            COMMONK_PerformCoordinatesTransform(aeH, (FLOAT64)lX, (FLOAT64)lY, &eTmpX, &eTmpY);

            alFM_v2_1_Undistorted2Distorted_PlanarPixel(a_ptFM_v2_Model, eTmpX, eTmpY, &eDistX, &eDistY);
            lDistX = alROUND(eDistX);
            lDistY = alROUND(eDistY);

            if (lDistX >= 0 && lDistX < a_ptFM_v2_Model->uwDestWidth && lDistY >= 0 && lDistY < a_ptFM_v2_Model->uwDestHeight)
            {
                pucRecImage[lY*a_ptFM_v2_Model->uwDestWidth + lX] = a_pucSrcY[lDistY*a_ptFM_v2_Model->uwDestWidth + lDistX];
            }
#else
            pucRecImage[lY*a_ptFM_v2_Model->uwDestWidth + lX] = a_pucSrcY[lY*a_ptFM_v2_Model->uwDestWidth + lX];
#endif
        }
    }
#if alLDCK_TEST // for test (opencv log)
    ptPicGray = cvCreateImage(cvSize(a_ptFM_v2_Model->uwDestWidth, a_ptFM_v2_Model->uwDestHeight), IPL_DEPTH_8U, 1);

    memcpy(ptPicGray->imageData, pucRecImage, sizeof(UINT8)*ptPicGray->imageSize);
    sprintf_s(cText, MAX_PATH, "RectifiedImage.jpg");
    cvSaveImage(cText, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
#endif
    

    // Detect all corners in Rectified Image
#if alLDCK_TEST // for test
   
#endif

    // map corners back to source image domain 
#if alLDCK_TEST // for test

#endif


    free(pucRecImage);
}

FLOAT64 alLDCK_ErrorEstimate(
    UINT8 a_aucCornerFlag[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerRectified[alLDCK_CORNER_NUM],
    alPointFLOAT64 a_atCornerIdeal[alLDCK_CORNER_NUM]
    )
{
    FLOAT64 eError = 0, eTmpX = 0, eTmpY = 0, eErrorMax = 0, eDistance = 0, eSize = 0, eWeight = 0;
    INT32 lCnt = 0, lCntEnable = 0;

    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        if (!a_aucCornerFlag[lCnt])
        { // 有偵測到的位置才計算誤差
            eTmpX = (a_atCornerIdeal[lCnt].eX - a_atCornerRectified[lCnt].eX)*(a_atCornerIdeal[lCnt].eX - a_atCornerRectified[lCnt].eX);
            eTmpY = (a_atCornerIdeal[lCnt].eY - a_atCornerRectified[lCnt].eY)*(a_atCornerIdeal[lCnt].eY - a_atCornerRectified[lCnt].eY);
#if alLDCK_ERROR_WEIGHTING_MODE
            eDistance = sqrt(eTmpX + eTmpY);
            eSize = eDistance / alLDCK_CHART_BLOCK_SIZE; // 以方格大小為單位
            eWeight = eDistance*eDistance + 1; // 計算權重
            eError += eWeight * (eDistance);
#else
            eError += eTmpX + eTmpY;
            eErrorMax = (eTmpX + eTmpY > eErrorMax) ? eTmpX + eTmpY : eErrorMax;
#endif
            lCntEnable++;
        }
    }
    eError = eError / lCntEnable;

    return eError;
    // return eErrorMax;
}


