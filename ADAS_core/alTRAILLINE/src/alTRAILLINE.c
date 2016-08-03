
#include "alTRAILLINE.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define ancre_test 0 // for test 0: off 1: on

typedef struct
{
	FLOAT64 x;
	FLOAT64 y;
} Point;

typedef struct
{
	Point startPoint;
	Point endPoint;
	UINT8 cColor;
	UINT8 cLineType;
} PointPair;

static INT32 g_lIndex = 0;//global index, 為了算暫存quene中有幾個點.

/** \brief Store the color map for trail line. */
UINT8 g_TRAILLINE_aucColorDef[255][3] = { 
	{0, 0, 0}, 
	{255, 255, 255}, 
	{0, 0, 0}, 
	{255, 0, 0}, 
	{0, 255, 0}, 
	{0, 0, 255},
	{255, 255, 0},
	{0, 255, 255},
	{255, 0, 255},
	{255, 128, 0},
	{136, 40, 38},
	{252, 255, 160},
	{99, 195, 96},
	{0, 206, 0},
	{255, 131, 0},
	{217, 106, 106},
	{255, 231, 104},
	{195, 255, 196},
	{255, 243, 179}
};

static void PushPointPair(Point tStartPoint, Point EndPoint, PointPair* pairArr, int* pIndexRecord, UINT8 colorIndex, UINT8 cLineType)
{
    //pairCounter傳進去是為了記現在有幾個點,改用return index也行,但怕忘記接..
	if(g_lIndex < MAX_LINEDATA_NUM)
	{
		pairArr[g_lIndex].startPoint.x = tStartPoint.x;
		pairArr[g_lIndex].startPoint.y = tStartPoint.y;
		pairArr[g_lIndex].endPoint.x = EndPoint.x;
		pairArr[g_lIndex].endPoint.y = EndPoint.y;
		pairArr[g_lIndex].cColor = colorIndex;
		pairArr[g_lIndex].cLineType = cLineType;
		g_lIndex ++;
	}
    else
        assert(0);
	*pIndexRecord = g_lIndex;
}

static void PieceCake(Point begin, Point target, PointPair* pairArr, INT32 * pPairCounter, UINT8 colorIndex, UINT8 cLineType)
{//原線段起始和終點切成小線段Start和End
	FLOAT64 tempX, tempY;
	Point tempStart, tempEnd;
	INT32 pieceNum;
	INT32 j;
	pieceNum = (INT32)(1 + ((int) sqrt((target.x - begin.x) * (target.x - begin.x) + (target.y - begin.y) * (target.y - begin.y)))
				/ MAX_PIECE_LENGTH);
	for(j = 0; j < pieceNum; j ++)
	{	
		tempX = (FLOAT64) (target.x - begin.x) / pieceNum;//切段後差距
		tempY = (FLOAT64) (target.y - begin.y) / pieceNum;//切段後差距
		tempStart.x = begin.x + j * tempX;//起點
		tempStart.y = begin.y + j * tempY;//起點
		tempEnd.x = tempStart.x + tempX;//終點比起點多跑一段
		tempEnd.y = tempStart.y + tempY;//終點比起點多跑一段
		PushPointPair(tempStart, tempEnd, pairArr, pPairCounter, colorIndex, cLineType);//弄完push進暫存列
	}
}

static void rotating(FLOAT64 * ePointX, FLOAT64 * ePointY, FLOAT64 eCenterX, FLOAT64 eCenterY, FLOAT64 eAlpha)
{

	FLOAT64 eX = *ePointX;
    FLOAT64 eY = *ePointY;
    *ePointX = (FLOAT64)(cos(eAlpha) * (eX - eCenterX) - sin(eAlpha) * (eY - eCenterY) + eCenterX);
    *ePointY = (FLOAT64)(sin(eAlpha) * (eX - eCenterX) + cos(eAlpha) * (eY - eCenterY) + eCenterY);
}

static void ToBirdViewCoordinate(FLOAT64 * x, FLOAT64 * y, const alTRAILLINE_Params* a_ptGenInfo)
{
    FLOAT64 ppmm = 1.0 / a_ptGenInfo->fMMPP;
	*x = (FLOAT64)((*x * ppmm) + a_ptGenInfo->lBV_CAR_CenterX);
	*y = (FLOAT64)((*y * ppmm) + a_ptGenInfo->lBV_CAR_CenterY);
}

static void PointMirror(FLOAT64 eSrcX, FLOAT64 * peDestX, FLOAT64 peCenterX)
{
    (*peDestX) = peCenterX - (eSrcX - peCenterX);
}

static void PointFlip(FLOAT64 eSrcY, FLOAT64 * peDestY, FLOAT64 peCenterY)
{
    (*peDestY) = peCenterY - (eSrcY - peCenterY);
}

static void PointRotation(FLOAT64 eSrcX, FLOAT64 eSrcY, FLOAT64 * peDestX, FLOAT64 * peDestY, FLOAT64 peCenterX, FLOAT64 peCenterY, INT32 lDegree)
{
	(*peDestX) = cos(lDegree*alPI/180) * (eSrcX-peCenterX) - sin(lDegree*alPI/180) * (eSrcY-peCenterY) + peCenterX + (peCenterY*2-peCenterX*2)/2;
	(*peDestY) = sin(lDegree*alPI/180) * (eSrcX-peCenterX) + cos(lDegree*alPI/180) * (eSrcY-peCenterY) + peCenterY + (peCenterX*2-peCenterY*2)/2;
}

static void PieceRotate(Point oStartPoint, 
				 FLOAT64 eMaxAngle, 
				 PointPair * pairArr,
				 alTRAILLINE_Params* a_ptGenInfo,
				 INT32 * pPairCounter, 
				 UINT8 ucColorIndex, 
				 UINT8 ucLineType, 
				 FLOAT64 eSteerCenterX,
				 FLOAT64 eSteerCenterY)
{
	//雖然有許多地方跟piececake很像,
	//但考慮到動態車幅線為連續,且其中節點要旋轉問題,仍然設計一新的函數較為直觀
	//注意差別:
    //動態pieceRotat設計:前點會接後點,即下一段的start為前一段的end, 和piececake設計不同
	//float tempX, tempY;
	Point tempStart, tempEnd;
	INT32 lPieceNum;
    FLOAT64 ePieceAngle;
	INT32 j;

    lPieceNum = DTL_PIECE_NUM;
	//lPieceNum = (int)(1 + fabs(eMaxAngle)/(DTL_MAX_PIECE_DEGREE * alPI / 180.0));
	ePieceAngle = eMaxAngle / lPieceNum;

	tempStart.x = oStartPoint.x;//最一開始起點
	tempStart.y = oStartPoint.y;//最一開始起點
	for(j = 1; j <= lPieceNum; j ++)
	{	
		tempEnd = tempStart;

        // 每次旋轉 PIECE 角度
		rotating(&tempEnd.x,&tempEnd.y, eSteerCenterX, eSteerCenterY, ePieceAngle);
        // 將計算結果存進陣列
		PushPointPair(tempStart, tempEnd, pairArr, pPairCounter, ucColorIndex, ucLineType);//弄完push進暫存列

		tempStart = tempEnd;
	}
}

/** 
    \brief Perform the coordinates transform from world coordinates to camera coordinates.
    \param a_peRT [IN] The RT matrix
    \param a_eSrcX [IN] The source X coordinates.
    \param a_eSrcY [IN] The source Y coordinates.
    \param a_eSrcZ [IN] The source Z coordinates.
    \param a_eDestX [IN] The destination X coordinates.
    \param a_eDestY [IN] The destination Y coordinates.
    \param a_eDestZ [IN] The destination Z coordinates.
*/
static void PerformCoordinatesTransform_3D(FLOAT64 * a_peRT, FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ)
{
    FLOAT64 eS = (a_peRT[12] * a_eSrcX + a_peRT[13] * a_eSrcY + a_peRT[14] * a_eSrcZ + a_peRT[15] * 1);
    assert(eS == 1.0);

    (*a_peDestX) = (a_peRT[0] * a_eSrcX + a_peRT[1] * a_eSrcY + a_peRT[2] * a_eSrcZ + a_peRT[3] * 1);
    (*a_peDestY) = (a_peRT[4] * a_eSrcX + a_peRT[5] * a_eSrcY + a_peRT[6] * a_eSrcZ + a_peRT[7] * 1);
    (*a_peDestZ) = (a_peRT[8] * a_eSrcX + a_peRT[9] * a_eSrcY + a_peRT[10] * a_eSrcZ + a_peRT[11] * 1);
}

/* 
    \brief To generate dynamic trail line for specific view and degree. 
    \param a_ucType[IN] for Front or Rear view
    \param a_ptGenInfo[IN] General Trail line information.
    \param a_ptDyTrailInfo[IN] Dynamic Trail line information for specific view.
    \param a_peM33[IN] M3x3 for current view.
    \param a_ptFishEyeModel_v2[IN] M3x3 for current camera.
    \param a_wDegree[IN] Steering Angle.
    \param pTrailHeader[OUT] Trail line data for output.
    \return None.
    \See alTRAILLINE_Params, alTRAILLINE_DynamicTrailLineInfo, alTRAILLINE_LineHeader
*/
static void CalDynamicTrail(
    UINT8 *pubBuffer,
    alTRAILLINE_TL_INDX a_ucType,
    alTRAILLINE_Params* a_ptGenInfo,
    alTRAILLINE_DynamicTrailLineInfo* a_ptDyTrailInfo,
    FLOAT64* a_peR33,
    FLOAT64* a_peT31,
    alFM_v2_1_Model* a_ptFishEyeModel_v2, 
	INT16 a_wDegree,
    alTRAILLINE_LineHeader * a_ptAnsHeader
    )
{
	INT32 pairCounter;
	INT32 i, lOutputCnt;
	FLOAT64 tempStartX, tempStartY, tempStartZ, tempEndX, tempEndY, tempEndZ;
	FLOAT64 tempStartXA, tempStartYA, tempStartZA, tempEndXA, tempEndYA, tempEndZA;


    Point   oLeftCarEdge;
    Point   oRightCarEdge;
    Point   oLeftStartPoint;
    Point   oRightStartPoint;
    Point   oLeftEndPoint;
    Point   oRightEndPoint;
    FLOAT64 eCarTurnAngle;      // 車輛轉向角       (in rad)
    FLOAT64 eRadius;            // 車輛迴轉半徑
    FLOAT64 eSteeringCenterX;   // 車輛迴轉中心座標
    FLOAT64 eSteeringCenterY;   // 車輛迴轉中心座標
    FLOAT64 eLarc;              // 車輛前進最大距離
    FLOAT64 eMaxMovingAngle;    // 車輛前進最大角度 (in rad)
    FLOAT64 eStartPosAngle;     // 車幅線起始位置的角度 (in rad)

    PointPair * ptPairOfPoints = NULL;

    FLOAT64 aeRT_W2I[16];
    // Assing the R & T to RT matrix
    aeRT_W2I[0] = a_peR33[0];
    aeRT_W2I[1] = a_peR33[1];
    aeRT_W2I[2] = a_peR33[2];
    aeRT_W2I[3] = a_peT31[0];

    aeRT_W2I[4] = a_peR33[3];
    aeRT_W2I[5] = a_peR33[4];
    aeRT_W2I[6] = a_peR33[5];
    aeRT_W2I[7] = a_peT31[1];

    aeRT_W2I[8] = a_peR33[6];
    aeRT_W2I[9] = a_peR33[7];
    aeRT_W2I[10] = a_peR33[8];
    aeRT_W2I[11] = a_peT31[2];

    aeRT_W2I[12] = 0;
    aeRT_W2I[13] = 0;
    aeRT_W2I[14] = 0;
    aeRT_W2I[15] = 1;

    if (pubBuffer != NULL)
    {
        ptPairOfPoints = (PointPair*)pubBuffer;
    }
    else
    {
        assert(0); // 沒buffer可用
        // ptPairOfPoints = (PointPair*)malloc(MAX_LINEDATA_NUM * sizeof(PointPair));
    }
    memset(ptPairOfPoints, 0, MAX_LINEDATA_NUM * sizeof(PointPair));

    if(ptPairOfPoints == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: CalDynamicTrail::ptPairOfPoints");
        return;
    }

	g_lIndex = 0;//重要,每個view要從0開始算現在有多少點, 利用global變數或許不甚佳, 僅從權

    // 初始化 Header
	a_ptAnsHeader->wType = a_ucType;
    a_ptAnsHeader->wNumOfPairs = 0;
	a_ptAnsHeader->wRot_degree = a_wDegree;

    // 1. 計算 Rc : by a_wDegree: 方向盤舵角
    // 1.1 計算車輛轉向角 φ
    eCarTurnAngle = (a_ptGenInfo->fSteerParamA * a_wDegree + a_ptGenInfo->fSteerParamB) * alPI / 180;

    // 1.2 計算車輛迴轉半徑 Rc
    if(fabs(eCarTurnAngle) < 0.000001) // added by chinson - 20131022: 避免 tan(φ) = 0
    {
        eCarTurnAngle = 0.00001;
    }
    eRadius = a_ptGenInfo->uwWheelBase_mm / (tan(eCarTurnAngle));

    // 1.3 求得圓心位置(on BV)
    eSteeringCenterX = eRadius;
    eSteeringCenterY = (a_ptGenInfo->uwCarLength_mm>>1) - a_ptGenInfo->uwAxisToBack_mm;
	//ToBirdViewCoordinate(&eSteeringCenterX, &eSteeringCenterY, a_ptGenInfo); 

    // 2. 計算從車頭到起始位置一共前進多少角度
    // 2.1 計算車頭位置
    switch(a_ucType)
    {
    case alTRAILLINE_DTL_FRONT:
        oLeftCarEdge.y = - (a_ptGenInfo->uwCarLength_mm>>1);
        oRightCarEdge.y = - (a_ptGenInfo->uwCarLength_mm>>1);
        break;
    case alTRAILLINE_DTL_BACK:
        oLeftCarEdge.y = (a_ptGenInfo->uwCarLength_mm>>1);
        oRightCarEdge.y = (a_ptGenInfo->uwCarLength_mm>>1);
        break;
    default:
        assert(0);
    }
    oLeftCarEdge.x = a_ptDyTrailInfo->wVerticalLinePos[0];
    oRightCarEdge.x = a_ptDyTrailInfo->wVerticalLinePos[1];

    // 2.2 計算車頭位置到起始位置的旋轉角度
    eLarc = fabs(a_ptDyTrailInfo->wHoriStartPos - oLeftCarEdge.y);
    eStartPosAngle = eLarc / eRadius;
    if(a_ucType == alTRAILLINE_DTL_BACK) eStartPosAngle = -eStartPosAngle;

    // 3. 計算從 起始位置 到 結束位置，一共前進多少角度
    // 3.1 計算前進距離
    eLarc = abs(a_ptDyTrailInfo->wHoriEndPos - a_ptDyTrailInfo->wHoriStartPos);
    // 3.2 計算前進角度
    eMaxMovingAngle = eLarc / eRadius;

    if(a_ucType == alTRAILLINE_DTL_BACK) eMaxMovingAngle = -eMaxMovingAngle;

    // 4. 畫出左側車幅線
	// 4.1 定義起始及結束座標
    if(a_wDegree >= - a_ptDyTrailInfo->wShortLineDisableAngle)
    {
	    oLeftStartPoint = oLeftCarEdge;
        //ToBirdViewCoordinate(&oLeftStartPoint.x, &oLeftStartPoint.y, a_ptGenInfo);
        rotating(&oLeftStartPoint.x, &oLeftStartPoint.y, eSteeringCenterX, eSteeringCenterY, eStartPosAngle);

	    // 4.2 切出座標點
	    PieceRotate(oLeftStartPoint, eMaxMovingAngle, ptPairOfPoints, a_ptGenInfo, &pairCounter, a_ptDyTrailInfo->ucColorIndex[0], a_ptDyTrailInfo->ucLineStyle[0], eSteeringCenterX, eSteeringCenterY);
    }

    if(a_wDegree <= a_ptDyTrailInfo->wShortLineDisableAngle)
    {
        // 5. 畫出右側車幅線
	    // 5.1 定義起始及結束座標
	    oRightStartPoint = oRightCarEdge;
        //ToBirdViewCoordinate(&oRightStartPoint.x, &oRightStartPoint.y, a_ptGenInfo);
        rotating(&oRightStartPoint.x, &oRightStartPoint.y, eSteeringCenterX, eSteeringCenterY, eStartPosAngle);

        // 5.2 切出座標點
	    PieceRotate(oRightStartPoint, eMaxMovingAngle, ptPairOfPoints, a_ptGenInfo, &pairCounter, a_ptDyTrailInfo->ucColorIndex[0], a_ptDyTrailInfo->ucLineStyle[0], eSteeringCenterX, eSteeringCenterY);
    }

    // 6. 計算尾端的橫線段
	if( a_ptDyTrailInfo->ucTrailStyle == 1)
	{
        // 計算左側終點
        oLeftEndPoint = oLeftStartPoint;
		rotating(&oLeftEndPoint.x,&oLeftEndPoint.y, eSteeringCenterX, eSteeringCenterY, eMaxMovingAngle);

        // 計算右側終點
        oRightEndPoint = oRightStartPoint;
		rotating(&oRightEndPoint.x,&oRightEndPoint.y, eSteeringCenterX, eSteeringCenterY, eMaxMovingAngle);

        // 切段輸出
        PieceCake(oLeftEndPoint, oRightEndPoint, ptPairOfPoints, &pairCounter, a_ptDyTrailInfo->ucColorIndex[1], a_ptDyTrailInfo->ucLineStyle[1]);
	}
	
    if(pairCounter != 0)
    {
        

	    for (i = 0, lOutputCnt = 0; i < pairCounter; i++)
	    {
            // Modified by chinson: 改用 R+T 矩陣做座標轉換，以提供超過 180度 鏡頭區域的對應。
		    PerformCoordinatesTransform_3D(aeRT_W2I, ptPairOfPoints[i].startPoint.x , ptPairOfPoints[i].startPoint.y, 0,
									    &tempStartX, &tempStartY, &tempStartZ);
		    PerformCoordinatesTransform_3D(aeRT_W2I, ptPairOfPoints[i].endPoint.x , ptPairOfPoints[i].endPoint.y, 0,
									    &tempEndX, &tempEndY, &tempEndZ);
    		
    #if (SIM_DEFAULT_EAGLE_GP_TRANS == 1)
		    tempStartX += (a_ptFishEyeModel_v2->m_uwDestWidth)/2;
		    tempStartY += (a_ptFishEyeModel_v2->m_uwDestHeight)/2;
		    tempEndX += (a_ptFishEyeModel_v2->m_uwDestWidth)/2;
		    tempEndY += (a_ptFishEyeModel_v2->m_uwDestHeight)/2;
    #endif

		    tempStartXA = tempStartX;
		    tempStartYA = tempStartY;
		    tempStartZA = tempStartZ;
		    tempEndXA = tempEndX;
		    tempEndYA = tempEndY;
 		    tempEndZA = tempEndZ;
   		
            alFM_v2_1_Undistorted2Distorted_Sphere(
								    a_ptFishEyeModel_v2,
                                    tempStartXA, 
								    tempStartYA,                                    
								    tempStartZA,                                    
								    &(tempStartX),
								    &(tempStartY)
                );
            alFM_v2_1_Undistorted2Distorted_Sphere(
								    a_ptFishEyeModel_v2,
                                    tempEndXA, 
								    tempEndYA,                                    
								    tempEndZA,                                    
								    &(tempEndX),
								    &(tempEndY)
                );

    		
            if(a_ucType == alTRAILLINE_DTL_BACK)
            {
                // 對 Back View 做 Mirror
#if ancre_test == 0
                PointMirror(tempStartX, &tempStartX, (a_ptFishEyeModel_v2->uwSrcWidth >> 1));
                PointMirror(tempEndX, &tempEndX, (a_ptFishEyeModel_v2->uwSrcWidth >> 1));
#endif
            }

		    a_ptAnsHeader->pDrawLineData[lOutputCnt].wStartX = (UINT16) tempStartX;
		    a_ptAnsHeader->pDrawLineData[lOutputCnt].wStartY = (UINT16) tempStartY;
		    a_ptAnsHeader->pDrawLineData[lOutputCnt].wEndX = (UINT16) tempEndX;
		    a_ptAnsHeader->pDrawLineData[lOutputCnt].wEndY = (UINT16) tempEndY;
		    a_ptAnsHeader->pDrawLineData[lOutputCnt].cLineType = ptPairOfPoints[i].cLineType;
		    a_ptAnsHeader->pDrawLineData[lOutputCnt].cColor = ptPairOfPoints[i].cColor;
		    a_ptAnsHeader->pDrawLineData[lOutputCnt].cThickness = a_ptGenInfo->ucLineThickness;
    		
            lOutputCnt++;
	    }
	    a_ptAnsHeader->wNumOfPairs = lOutputCnt;
        a_ptAnsHeader->wLineDataSize = lOutputCnt * sizeof(alTRAILLINE_PairData);

    }

    // free(ptPairOfPoints);

}	

static void PieceWarningLine(alTRAILLINE_Params * a_ptGenInfo, alTRAILLINE_WarningLineInfo* pWarnInfo, PointPair* aPairOfPoints, int* pPairCounter)
{
	Point begin;
	Point target;
	int i;
	INT32 dashNum;
	FLOAT64 tempdashlenX, tempdashlenY;
	FLOAT64 tempstartX, tempstartY;

    for (i = 0; i < pWarnInfo->ucLineCount;i++ )
	{
		if(pWarnInfo->ucWarningLineStyle[i] == 1)
		{
			begin.x = pWarnInfo->wWarningLinePos[i][0];
			begin.y = pWarnInfo->wWarningLinePos[i][1];
			target.x = pWarnInfo->wWarningLinePos[i][2];
			target.y = pWarnInfo->wWarningLinePos[i][3];
#if 0
			ToBirdViewCoordinate(&(begin.x), &(begin.y), a_ptGenInfo);
			ToBirdViewCoordinate(&(target.x), &(target.y), a_ptGenInfo);
#endif
			tempstartX = begin.x;
			tempstartY = begin.y;
			tempdashlenX = ((target.x)-(begin.x))/((pWarnInfo->ucPieceCount[i])*2-1);
			tempdashlenY = ((target.y)-(begin.y))/((pWarnInfo->ucPieceCount[i])*2-1);

			for(dashNum=1; dashNum<=(pWarnInfo->ucPieceCount[i])*2-1; dashNum++)
			{
				if(dashNum%2 == 0)
					continue;
				else
				{
					begin.x = tempstartX + (dashNum-1)*tempdashlenX;
					begin.y = tempstartY + (dashNum-1)*tempdashlenY;
					target.x = begin.x + tempdashlenX;
					target.y = begin.y + tempdashlenY;
					PieceCake(begin, target, aPairOfPoints, pPairCounter, pWarnInfo->ucWarningLineColor[i], pWarnInfo->ucWarningLineStyle[i]);
				}
			}
		}
		else
		{
		    begin.x = pWarnInfo->wWarningLinePos[i][0];
		    begin.y = pWarnInfo->wWarningLinePos[i][1];
		    target.x = pWarnInfo->wWarningLinePos[i][2];
		    target.y = pWarnInfo->wWarningLinePos[i][3];
#if 0
		    ToBirdViewCoordinate(&(begin.x), &(begin.y), a_ptGenInfo);
		    ToBirdViewCoordinate(&(target.x), &(target.y), a_ptGenInfo);
#endif
		    PieceCake(begin, target, aPairOfPoints, pPairCounter, pWarnInfo->ucWarningLineColor[i], pWarnInfo->ucWarningLineStyle[i]);
	    }
    }
}

static Point g_tLeftPoints[MAX_HORIZONTAL_POS_NUM];
static Point g_tRightPoints[MAX_HORIZONTAL_POS_NUM];
static Point g_tLeftDashHoriPoints[MAX_HORIZONTAL_POS_NUM];
static Point g_tLeftDashVertPoints[MAX_HORIZONTAL_POS_NUM];
static Point g_tRightDashHoriPoints[MAX_HORIZONTAL_POS_NUM];
static Point g_tRightDashVertPoints[MAX_HORIZONTAL_POS_NUM];

static void CalStaticTrail( 
    UINT8 *pubBuffer,
    alTRAILLINE_TL_INDX a_ucType,
    alTRAILLINE_Params* a_ptGenInfo,
    alTRAILLINE_StaticTrailLineInfo* pTrailInfo, 
    alTRAILLINE_WarningLineInfo* pWarnInfo, 
    FLOAT64* a_peR33,
    FLOAT64* a_peT31,
    alFM_v2_1_Model* a_ptFishEyeModel_v2, 
    alTRAILLINE_LineHeader * a_ptAnsHeader)
{


	Point begin, target;
	INT32 i = 0/*, j = 0, lineDataIndex = 0*/;
	//FLOAT64 ppmm =  1.0 / a_ptGenInfo->fMMPP;//改umpp 	
	INT32 pairCounter = 0;
	
	FLOAT64 tempStartX; 
	FLOAT64 tempStartY; 
	FLOAT64 tempStartZ; 
	FLOAT64 tempEndX;
	FLOAT64 tempEndY;
	FLOAT64 tempEndZ; 
	
	// PointPair * ptPairOfPoints = (PointPair*) malloc(MAX_LINEDATA_NUM * sizeof(PointPair));
    PointPair * ptPairOfPoints = NULL;

    if (pubBuffer!=NULL)
    {
        ptPairOfPoints = (PointPair*)pubBuffer;
    }
    else
    {
        assert(0); // 沒buffer可用
        // ptPairOfPoints = (PointPair*)malloc(MAX_LINEDATA_NUM * sizeof(PointPair));
    }
    memset(ptPairOfPoints, 0, MAX_LINEDATA_NUM * sizeof(PointPair));

    FLOAT64 aeRT_W2I[16];
    // Assing the R & T to RT matrix
    aeRT_W2I[0] = a_peR33[0];
    aeRT_W2I[1] = a_peR33[1];
    aeRT_W2I[2] = a_peR33[2];
    aeRT_W2I[3] = a_peT31[0];

    aeRT_W2I[4] = a_peR33[3];
    aeRT_W2I[5] = a_peR33[4];
    aeRT_W2I[6] = a_peR33[5];
    aeRT_W2I[7] = a_peT31[1];

    aeRT_W2I[8] = a_peR33[6];
    aeRT_W2I[9] = a_peR33[7];
    aeRT_W2I[10] = a_peR33[8];
    aeRT_W2I[11] = a_peT31[2];

    aeRT_W2I[12] = 0;
    aeRT_W2I[13] = 0;
    aeRT_W2I[14] = 0;
    aeRT_W2I[15] = 1;

    if(ptPairOfPoints == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: CalStaticTrail::ptPairOfPoints");
        return;
    }

	g_lIndex = 0;//每個view從零開始算

    // 初始化 Header
    a_ptAnsHeader->wType = a_ucType;
    a_ptAnsHeader->wNumOfPairs = 0;

	if( pTrailInfo != 0)//有傳入靜態車幅線,(Front/Rear View)
	{
		
		/*以下為定義各特定節點如下圖:
		左邊四點和右邊四(可至N)點 然後各存三橫線的點, Real World coordinate(in mm), 
		from car center.  (Right and down positive)

		3__LeftDash                  __3
		|                              |
		2__LeftDash                  __2
		|                              | 
		1__LeftDash         RightDash__1
		|                              |
		0                              0
		LeftPoints                     RightPoints
		*/
		for (i = 0; i < pTrailInfo->ucHorizonCount; i++)
		{
			g_tLeftPoints[i].x = pTrailInfo->wVerticalLinePosition[0] ;
			g_tLeftPoints[i].y = pTrailInfo->wHorizonLinePosition[i];
			g_tRightPoints[i].x = pTrailInfo->wVerticalLinePosition[1];
			g_tRightPoints[i].y = pTrailInfo->wHorizonLinePosition[i];

			g_tLeftDashHoriPoints[i].x = g_tLeftPoints[i].x + pTrailInfo->uwDashLengthHori;
			g_tLeftDashHoriPoints[i].y = g_tLeftPoints[i].y;
			g_tLeftDashVertPoints[i].x = g_tLeftPoints[i].x;

            if(a_ucType == alTRAILLINE_STL_FRONT)
            {
              
			    g_tLeftDashVertPoints[i].y = g_tLeftPoints[i].y + pTrailInfo->wDashLengthVert[i];		
    			g_tRightDashVertPoints[i].y = g_tRightPoints[i].y + pTrailInfo->wDashLengthVert[i];

            }
            else
            {
              
			    g_tLeftDashVertPoints[i].y = g_tLeftPoints[i].y - pTrailInfo->wDashLengthVert[i];		
    			g_tRightDashVertPoints[i].y = g_tRightPoints[i].y - pTrailInfo->wDashLengthVert[i];
 
            }
  
			g_tRightDashHoriPoints[i].x = g_tRightPoints[i].x - pTrailInfo->uwDashLengthHori;
			g_tRightDashHoriPoints[i].y = g_tRightPoints[i].y;
			g_tRightDashVertPoints[i].x = g_tRightPoints[i].x;

#if 0
			//Change coordinate from real world to Birdview:
			ToBirdViewCoordinate(&(g_tLeftPoints[i].x), &(g_tLeftPoints[i].y), a_ptGenInfo);
 			ToBirdViewCoordinate(&(g_tRightPoints[i].x), &(g_tRightPoints[i].y), a_ptGenInfo);
			ToBirdViewCoordinate(&(g_tLeftDashHoriPoints[i].x), &(g_tLeftDashHoriPoints[i].y), a_ptGenInfo);
			ToBirdViewCoordinate(&(g_tRightDashHoriPoints[i].x), &(g_tRightDashHoriPoints[i].y), a_ptGenInfo);
			ToBirdViewCoordinate(&(g_tLeftDashVertPoints[i].x), &(g_tLeftDashVertPoints[i].y), a_ptGenInfo);
			ToBirdViewCoordinate(&(g_tRightDashVertPoints[i].x), &(g_tRightDashVertPoints[i].y), a_ptGenInfo);
#endif
		}

        // Chinson: 先畫縱線再畫橫線，可避免縱線遮蓋到橫線
        if(pTrailInfo->ucTrailStyle != 0) // type 0 不畫縱線
        {
		    for (i = 1; i < pTrailInfo->ucHorizonCount; i ++ )//Begin from 1 先以終點為主
		    {
			    //切左邊縱線
			    target = g_tLeftPoints[i];
			    if(pTrailInfo->ucTrailStyle == 1) // Type 1 (hook 勾狀front view)則x不變, y為兩端點平均
			    {
					begin = g_tLeftDashVertPoints[i];
				    //begin.x = (g_tLeftPoints[i].x + g_tLeftPoints[i - 1].x) / 2;
				    //begin.y = (g_tLeftPoints[i].y + g_tLeftPoints[i - 1].y) / 2;
			    }
			    else if(pTrailInfo->ucTrailStyle == 2) // Type 2 (linked line:完整線段)則從上一端點畫起
                {
				    begin = g_tLeftPoints[i - 1];
                }
			    PieceCake(begin, target, ptPairOfPoints, &pairCounter,  pTrailInfo->ucHoriLineColorIndex[i-1], pTrailInfo->ucVertLineStyle);

			    //切右邊縱線
			    target = g_tRightPoints[i];
			    if(pTrailInfo->ucTrailStyle == 1) // Type 1 (hook 勾狀front view)則x不變, y為兩端點平均
			    {
					begin = g_tRightDashVertPoints[i];
				    //begin.x = (g_tRightPoints[i].x + g_tRightPoints[i - 1].x) / 2;
				    //begin.y = (g_tRightPoints[i].y + g_tRightPoints[i - 1].y) / 2;
			    }
			    else if(pTrailInfo->ucTrailStyle == 2) // Type 2 (linked line:完整線段)則從上一端點畫起
                {
				    begin = g_tRightPoints[i - 1];
                }
			    PieceCake(begin, target, ptPairOfPoints, &pairCounter,  pTrailInfo->ucHoriLineColorIndex[i-1], pTrailInfo->ucVertLineStyle);
		    }
        }

		/*Generate piecewise horizontal line*/
		for (i = 1; i < pTrailInfo->ucHorizonCount; i++)//Begin from 1 因最近點不畫橫線
		{
			//切左邊橫線
			begin = g_tLeftPoints[i];
			target = g_tLeftDashHoriPoints[i];
			PieceCake(begin, target, ptPairOfPoints, &pairCounter, pTrailInfo->ucHoriLineColorIndex[i-1], pTrailInfo->ucHoriLineStyle);
			//切右邊橫線
			begin = g_tRightPoints[i];
			target = g_tRightDashHoriPoints[i];//原線段起始和終點切成小線段Start和End.
			PieceCake(begin, target, ptPairOfPoints, &pairCounter,  pTrailInfo->ucHoriLineColorIndex[i-1], pTrailInfo->ucHoriLineStyle);
		}
		pairCounter = pairCounter;

	}

	if( (pWarnInfo != 0) && (pWarnInfo->ucIsEnable == 1))//有警戒線
		PieceWarningLine(a_ptGenInfo, pWarnInfo, ptPairOfPoints, &pairCounter);
	
	a_ptAnsHeader->wRot_degree = 0;
	a_ptAnsHeader->wNumOfPairs = pairCounter;
    a_ptAnsHeader->wLineDataSize = pairCounter * sizeof(alTRAILLINE_PairData);
	for (i = 0 ; i < pairCounter; i++)
	{
#if 0
		//Planar transformation: Birdview domain to undistorted domain
		PerformCoordinatesTransform(a_peM33, ptPairOfPoints[i].startPoint.x , ptPairOfPoints[i].startPoint.y, 
									&tempStartX, &tempStartY);
		PerformCoordinatesTransform(a_peM33, ptPairOfPoints[i].endPoint.x , ptPairOfPoints[i].endPoint.y, 
									&tempEndX, &tempEndY);
#else
		PerformCoordinatesTransform_3D(aeRT_W2I, ptPairOfPoints[i].startPoint.x , ptPairOfPoints[i].startPoint.y, 0,
									&tempStartX, &tempStartY, &tempStartZ);

		PerformCoordinatesTransform_3D(aeRT_W2I, ptPairOfPoints[i].endPoint.x , ptPairOfPoints[i].endPoint.y, 0,
									&tempEndX, &tempEndY, &tempEndZ);
#endif

#if (SIM_DEFAULT_EAGLE_GP_TRANS == 1)
		tempStartX += (a_ptFishEyeModel_v2->m_uwDestWidth)/2;
		tempStartY += (a_ptFishEyeModel_v2->m_uwDestHeight)/2;
		tempEndX += (a_ptFishEyeModel_v2->m_uwDestWidth)/2;
		tempEndY += (a_ptFishEyeModel_v2->m_uwDestHeight)/2;
#endif
		

        alFM_v2_1_Undistorted2Distorted_Sphere(
							    a_ptFishEyeModel_v2,
                                tempStartX, 
							    tempStartY,                                    
							    tempStartZ,                                    
							    &(tempStartX),
							    &(tempStartY)
            );
        alFM_v2_1_Undistorted2Distorted_Sphere(
							    a_ptFishEyeModel_v2,
                                tempEndX, 
							    tempEndY,                                    
							    tempEndZ,                                    
							    &(tempEndX),
							    &(tempEndY)
            );

        switch (a_ucType)
        {
        case alTRAILLINE_STL_BACK :
            {
                // 對 Back View 做 Mirror
#if ancre_test == 0
                PointMirror(tempStartX, &tempStartX, (a_ptFishEyeModel_v2->uwSrcWidth >> 1));
                PointMirror(tempEndX, &tempEndX, (a_ptFishEyeModel_v2->uwSrcWidth >> 1));
#endif
            }
            break;
        case alTRAILLINE_STL_LEFT:
			{
				// 對 Left View 做 Rotation -90degree
                PointRotation(tempStartX, tempStartY, &tempStartX, &tempStartY, (a_ptFishEyeModel_v2->uwSrcWidth >> 1), (a_ptFishEyeModel_v2->uwSrcHeight >> 1), -90);
                PointRotation(tempEndX, tempEndY, &tempEndX, &tempEndY, (a_ptFishEyeModel_v2->uwSrcWidth >> 1), (a_ptFishEyeModel_v2->uwSrcHeight >> 1), -90);
			}
            break;
        case alTRAILLINE_STL_RIGHT:
			{
				// 對 Right View 做 Rotation 90degree
                PointRotation(tempStartX, tempStartY, &tempStartX, &tempStartY, (a_ptFishEyeModel_v2->uwSrcWidth >> 1), (a_ptFishEyeModel_v2->uwSrcHeight >> 1), 90);
                PointRotation(tempEndX, tempEndY, &tempEndX, &tempEndY, (a_ptFishEyeModel_v2->uwSrcWidth >> 1), (a_ptFishEyeModel_v2->uwSrcHeight >> 1), 90);
			}
            break;

        }

		a_ptAnsHeader->pDrawLineData[i].wStartX = (UINT16) tempStartX;
		a_ptAnsHeader->pDrawLineData[i].wStartY = (UINT16) tempStartY;
		a_ptAnsHeader->pDrawLineData[i].wEndX = (UINT16) tempEndX;
		a_ptAnsHeader->pDrawLineData[i].wEndY = (UINT16) tempEndY;
		a_ptAnsHeader->pDrawLineData[i].cLineType = ptPairOfPoints[i].cLineType;
		a_ptAnsHeader->pDrawLineData[i].cColor = ptPairOfPoints[i].cColor;
		a_ptAnsHeader->pDrawLineData[i].cThickness = a_ptGenInfo->ucLineThickness;
		
	}

    // free(ptPairOfPoints);
}



UINT32 alTRAILLINE_QurryTrailLineWorkingBufferSize()
{
    return (MAX_LINEDATA_NUM * sizeof(PointPair));
}

UINT32 alTRAILLINE_QurryTrailLineDataBufferSize()
{
    return (MAX_LINEDATA_NUM * sizeof(PointPair));
}

/** \brief To initial buffer for tail line calculation and record. */
BOOL alTRAILLINE_InitialBuffer(alTRAILLINE_LineSet *a_ptTRAILLINE_tLineDataSet)
{
    INT32 index, index2;

    // Initialized static trail line buffer.
    for(index = alTRAILLINE_STL_LEFT; index <= alTRAILLINE_STL_BACK ; index++)
    {
        a_ptTRAILLINE_tLineDataSet->aStaticTrailLine[index].pDrawLineData = (alTRAILLINE_PairData*) malloc(MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData));
        assert(a_ptTRAILLINE_tLineDataSet->aStaticTrailLine[index].pDrawLineData != NULL);
        if(a_ptTRAILLINE_tLineDataSet->aStaticTrailLine[index].pDrawLineData == NULL)
        {
            DEBUG_Printf("Memory Allocation Failed: alTRAILLINE_InitialBuffer::a_ptTRAILLINE_tLineDataSet->aStaticTrailLine[%d].pDrawLineData", index);
            return FALSE;
        }
    }

    // Initialized dynamic trail line buffer.
    for(index = 0; index < 2; index++)
    {
        for(index2 = 0; index2 < MAX_DYNAMIC_TRAIL_LINE_NUM; index2++)
        {
            a_ptTRAILLINE_tLineDataSet->aDynamicTrailLine[index][index2].pDrawLineData = (alTRAILLINE_PairData*) malloc(MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData));
            assert(a_ptTRAILLINE_tLineDataSet->aDynamicTrailLine[index][index2].pDrawLineData != NULL);
            if(a_ptTRAILLINE_tLineDataSet->aDynamicTrailLine[index][index2].pDrawLineData == NULL)
            {
                DEBUG_Printf("Memory Allocation Failed: alTRAILLINE_InitialBuffer::a_ptTRAILLINE_tLineDataSet->aDynamicTrailLine[%d][%d].pDrawLineData", index, index2);
                return FALSE;
            }
        }
    }

    return TRUE;
}


void alTRAILLINE_InitialByCfg(
    UINT8   *a_pucTLWorkingBuffer, alTRAILLINE_Data *a_ptData,
    alAVM2D_Cfg *a_ptAVM2D_Cfg, 
    alAVM2D_Params *a_ptalAVM2DParams, 
    alCOMMONK_CommonCfg * a_ptCommonCfg, 
    alTRAILLINE_Cfg *a_ptCfg, 
    alTRAILLINE_Params  *a_ptParams, 
    alTRAILLINE_LineSet *a_ptLineData)
{
    INT16 wHalfDTLCount = 0;

    // set working buffer
    a_ptData->pucTLWorkingBuffer = a_pucTLWorkingBuffer;

    // Initialize the configuration data for trail line generation.
    a_ptParams->uwSteeringAngleInterval = a_ptCfg->uwSteeringAngleInterval;
    a_ptParams->ucLineThickness = a_ptCfg->ucLineThickness;
    a_ptParams->uwCarWidth_mm = (INT16) a_ptCommonCfg->ulCarWidth;
    a_ptParams->uwCarLength_mm = (INT16) a_ptCommonCfg->ulCarLength;
    a_ptParams->lBV_StartX = a_ptalAVM2DParams->tBirdViewStartPoint.lX;
    a_ptParams->lBV_StartY = a_ptalAVM2DParams->tBirdViewStartPoint.lY;
    a_ptParams->lBV_CAR_CenterX = a_ptalAVM2DParams->tBirdViewStartPoint.lX + (a_ptalAVM2DParams->tBirdViewAreaSize.lX>>1); //;(a_ptCommonCfg->tDisplayAreaSize.lX)>>1;
    a_ptParams->lBV_CAR_CenterY = a_ptalAVM2DParams->tBirdViewStartPoint.lY + (a_ptalAVM2DParams->tBirdViewAreaSize.lY>>1); //(INT16)(g_BIRDVIEW_tCfg.ulBVNormalDistance / a_ptalAVM2DParams->fMMPP);
    a_ptParams->lBirdViewRange = a_ptAVM2D_Cfg->ulBVMaxDistance;
    a_ptParams->uwTrackWidth_mm = a_ptCommonCfg->ulRearWheelAxleWidth;
    a_ptParams->uwWheelBase_mm = a_ptCommonCfg->ulWheelAxleDistance;
    a_ptParams->uwAxisToBack_mm = a_ptCommonCfg->ulRearWheelAxle2Tail;
    a_ptParams->uwMax_Wheel_Angle = a_ptCommonCfg->ulMaxSteeringAngle;
    a_ptParams->fSteerParamA = a_ptCommonCfg->fSteerParamA;
    a_ptParams->fSteerParamB = a_ptCommonCfg->fSteerParamB;
    
    wHalfDTLCount = a_ptParams->uwMax_Wheel_Angle / a_ptParams->uwSteeringAngleInterval;
    a_ptLineData->uwDTLCount = (wHalfDTLCount<<1) + 1;

    // Steering Angle 必須小於支援的數值
    assert(a_ptParams->uwMax_Wheel_Angle <= MAX_SUPPORT_STEERING_ANGLE);

    a_ptParams->fMMPP = a_ptalAVM2DParams->fMMPP;

}

void alTRAILLINE_GetBufferSize(UINT8 a_pucTraillineType, UINT32 * a_pulSize, alTRAILLINE_LineSet *a_ptLineDataSet)
{
    switch(a_pucTraillineType)
    {
    case alTRAILLINE_STL_FRONT:
    case alTRAILLINE_STL_BACK :
    case alTRAILLINE_STL_LEFT:
    case alTRAILLINE_STL_RIGHT:
        {
            (*a_pulSize) = sizeof(alTRAILLINE_LineHeader) + 
                a_ptLineDataSet->aStaticTrailLine[a_pucTraillineType].wLineDataSize;
        }
        break;
    case alTRAILLINE_DTL_FRONT:
    case alTRAILLINE_DTL_BACK:
        {
            UINT16 index = 0;
            (*a_pulSize) = 0;
            for(index = 0; index < a_ptLineDataSet->uwDTLCount; index++)
            {
                (*a_pulSize) += sizeof(alTRAILLINE_LineHeader) + 
                    a_ptLineDataSet->aDynamicTrailLine[a_pucTraillineType-alTRAILLINE_DTL_FRONT][index].wLineDataSize;
            }
        }
        break;
    default:
        assert(0);
    }

}

void alTRAILLINE_GetLineData(UINT8 a_pucTraillineType, UINT32 a_ulSize, UINT8 * a_pucTrailDataBuffer, alTRAILLINE_LineSet *a_ptLineDataSet)
{
    //static UINT8 aTrailDataBuffer[MAX_DYNAMIC_TRAIL_LINE_NUM * sizeof(alTRAILLINE_LineHeader)];
    alTRAILLINE_LineHeader * ptTrailHeader = 0;
    UINT32 ulCurrSize = 0;
    UINT8 * pucBuffPtr = 0;
    UINT16 index;
    //UINT8 * a_pucTrailDataBuffer = NULL; 

    ulCurrSize = 0;

    switch(a_pucTraillineType)
    {
    case alTRAILLINE_STL_FRONT:
    case alTRAILLINE_STL_BACK :
    case alTRAILLINE_STL_LEFT:
    case alTRAILLINE_STL_RIGHT:

        //a_pucTrailDataBuffer = (UINT8*) malloc(sizeof(alTRAILLINE_LineHeader) + MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData));
        // Initialize the array, set default to 0.
        memset(a_pucTrailDataBuffer, 0, a_ulSize);

        pucBuffPtr = a_pucTrailDataBuffer;
        ptTrailHeader = &a_ptLineDataSet->aStaticTrailLine[a_pucTraillineType];

        // 1. Copy Header
        memcpy(pucBuffPtr, ptTrailHeader, sizeof(alTRAILLINE_LineHeader) - TRAIL_HEADER_RESERVED);
        memset(pucBuffPtr + sizeof(alTRAILLINE_LineHeader) - TRAIL_HEADER_RESERVED, 0, TRAIL_HEADER_RESERVED);
        pucBuffPtr += sizeof(alTRAILLINE_LineHeader);
        // 2. Copy Line Data
        memcpy(pucBuffPtr, ptTrailHeader->pDrawLineData, ptTrailHeader->wLineDataSize);

        // 3. Calculate data buffer size
        // chinson: These code are used to output dynamic data buffer.
        pucBuffPtr += ptTrailHeader->wLineDataSize;
        ulCurrSize = pucBuffPtr - a_pucTrailDataBuffer;

        assert(ulCurrSize <= a_ulSize);
        // chinson: These code are used to output maximum data buffer.
        //memset(pucBuffPtr + ptTrailHeader->wLineDataSize, 0, MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData) - ptTrailHeader->wLineDataSize);
        //pucBuffPtr += MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData);
        //(*a_pulSize) = sizeof(alTRAILLINE_LineHeader) + MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData);

        //return a_pucTrailDataBuffer;
        break;

    case alTRAILLINE_DTL_FRONT:
    case alTRAILLINE_DTL_BACK:

        // Initialize the array, set default to 0.
        memset(a_pucTrailDataBuffer, 0, a_ulSize);

        pucBuffPtr = a_pucTrailDataBuffer;
        for(index = 0; index < a_ptLineDataSet->uwDTLCount; index++)
        {
            ptTrailHeader = &a_ptLineDataSet->aDynamicTrailLine[a_pucTraillineType - alTRAILLINE_DTL_FRONT][index];
            
            // 1. Copy Header
            memcpy(pucBuffPtr, ptTrailHeader, sizeof(alTRAILLINE_LineHeader) - TRAIL_HEADER_RESERVED);
            memset(pucBuffPtr + sizeof(alTRAILLINE_LineHeader) - TRAIL_HEADER_RESERVED, 0, TRAIL_HEADER_RESERVED);
            pucBuffPtr += sizeof(alTRAILLINE_LineHeader);
            // 2. Copy Line Data
            memcpy(pucBuffPtr, ptTrailHeader->pDrawLineData, ptTrailHeader->wLineDataSize);

            // 3. Calculate data buffer size
            // chinson: These code are used to output dynamic data buffer.
            pucBuffPtr += ptTrailHeader->wLineDataSize;

            // chinson: These code are used to output maximum data buffer.
            //memset(pucBuffPtr + ptTrailHeader->wLineDataSize, 0, MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData) - ptTrailHeader->wLineDataSize);
            //pucBuffPtr += MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData);
        }

        // chinson: These code are used to output dynamic data buffer.
        ulCurrSize = pucBuffPtr - a_pucTrailDataBuffer;

        assert(ulCurrSize <= a_ulSize);
        // chinson: These code are used to output maximum data buffer.
        //assert((pucBuffPtr - a_pucTrailDataBuffer) == (a_ptLineDataSet->uwDTLCount * (sizeof(alTRAILLINE_LineHeader) + MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData))));
        //(*a_pulSize) = MAX_DYNAMIC_TRAIL_LINE_NUM * (sizeof(alTRAILLINE_LineHeader) + MAX_LINEDATA_NUM * sizeof(alTRAILLINE_PairData));

        //return a_pucTrailDataBuffer;

        break;

    default:
        assert(0);
    }

}

void alTRAILLINE_FreeBuffer(alTRAILLINE_LineSet *a_ptLineData)
{

    INT32 index, index2;

    // Free static trail line buffer.
    for(index = alTRAILLINE_STL_LEFT; index <= alTRAILLINE_STL_BACK ; index++)
    {
        free(a_ptLineData->aStaticTrailLine[index].pDrawLineData);
    }

    // Free dynamic trail line buffer.
    for(index = 0; index < 2; index++)
    {
        for(index2 = 0; index2 < MAX_DYNAMIC_TRAIL_LINE_NUM; index2++)
        {
            free(a_ptLineData->aDynamicTrailLine[index][index2].pDrawLineData);
        }
    }

    //// Free the data buffer for trail line data output.
    //free(g_pTrailDataBuffer);

}

void alTRAILLINE_GenerateLineData(alTRAILLINE_Data *a_ptData, alCOMMONK_CalibrationParams a_atCalibrationParams[4], alFM_v2_1_Model *a_ptFisheyeModel_v2, alTRAILLINE_Cfg *a_ptCfg, alTRAILLINE_Params  *a_ptParams, alTRAILLINE_LineSet *a_ptLineData)
{
    INT16 wDegree, wDegIdx, wHalfDTLCount;

    /* static trail line - front */
    CalStaticTrail(
        a_ptData->pucTLWorkingBuffer,
        alTRAILLINE_STL_FRONT, a_ptParams, a_ptCfg->atSTLCfg + 0, a_ptCfg->atWLCfg + alTRAILLINE_STL_FRONT,
        a_atCalibrationParams[alCAMERAINFO_BV_FRONT].aeRotationMatrix[0], 
        a_atCalibrationParams[alCAMERAINFO_BV_FRONT].aeTranslationMatrix[0], 
        a_ptFisheyeModel_v2 + alCAMERAINFO_BV_FRONT, &(a_ptLineData->aStaticTrailLine[alTRAILLINE_STL_FRONT])
    );

    /* static trail line - rear */
    CalStaticTrail(
        a_ptData->pucTLWorkingBuffer,
        alTRAILLINE_STL_BACK , a_ptParams, a_ptCfg->atSTLCfg + 1, a_ptCfg->atWLCfg + alTRAILLINE_STL_BACK ,
        a_atCalibrationParams[alCAMERAINFO_BV_BACK].aeRotationMatrix[0],
        a_atCalibrationParams[alCAMERAINFO_BV_BACK].aeTranslationMatrix[0],
        a_ptFisheyeModel_v2 + alCAMERAINFO_BV_BACK, &(a_ptLineData->aStaticTrailLine[alTRAILLINE_STL_BACK ])
    );

    /* static trail line - left */
    CalStaticTrail(
        a_ptData->pucTLWorkingBuffer,
        alTRAILLINE_STL_LEFT, a_ptParams, 0, a_ptCfg->atWLCfg + alTRAILLINE_STL_LEFT,
        a_atCalibrationParams[alTRAILLINE_STL_LEFT].aeRotationMatrix[0], 
        a_atCalibrationParams[alTRAILLINE_STL_LEFT].aeTranslationMatrix[0], 
        a_ptFisheyeModel_v2 + alCAMERAINFO_BV_LEFT, &(a_ptLineData->aStaticTrailLine[alTRAILLINE_STL_LEFT]));

    /* static trail line - right */
    CalStaticTrail(
        a_ptData->pucTLWorkingBuffer,
        alTRAILLINE_STL_RIGHT, a_ptParams, 0, a_ptCfg->atWLCfg + alTRAILLINE_STL_RIGHT, 
        a_atCalibrationParams[alTRAILLINE_STL_RIGHT].aeRotationMatrix[0], 
        a_atCalibrationParams[alTRAILLINE_STL_RIGHT].aeTranslationMatrix[0], 
        a_ptFisheyeModel_v2 + alCAMERAINFO_BV_RIGHT, &(a_ptLineData->aStaticTrailLine[alTRAILLINE_STL_RIGHT]));

    /* dynamic trail line  */
    wHalfDTLCount = a_ptParams->uwMax_Wheel_Angle / a_ptParams->uwSteeringAngleInterval;

    // 檢查所需要的 Trail Line 是否會大於容許數目
    if((wHalfDTLCount * 2 + 1) > MAX_DYNAMIC_TRAIL_LINE_NUM)
    {
        return;
    }

    for(wDegIdx = - wHalfDTLCount; wDegIdx <= wHalfDTLCount; wDegIdx++)
    {
        wDegree = wDegIdx * a_ptParams->uwSteeringAngleInterval;

        /* front */
        CalDynamicTrail(
            a_ptData->pucTLWorkingBuffer,
            alTRAILLINE_DTL_FRONT,
            a_ptParams, 
            a_ptCfg->atDTLCfg + 0, 
            a_atCalibrationParams[alCAMERAINFO_BV_FRONT].aeRotationMatrix[0], 
            a_atCalibrationParams[alCAMERAINFO_BV_FRONT].aeTranslationMatrix[0], 
            a_ptFisheyeModel_v2 + alCAMERAINFO_BV_FRONT, 
            wDegree, 
            &(a_ptLineData->aDynamicTrailLine[0][wDegIdx + wHalfDTLCount]));

        /* back */
        CalDynamicTrail(
            a_ptData->pucTLWorkingBuffer,
            alTRAILLINE_DTL_BACK,  
            a_ptParams, 
            a_ptCfg->atDTLCfg + 1, 
            a_atCalibrationParams[alCAMERAINFO_BV_BACK].aeRotationMatrix[0], 
            a_atCalibrationParams[alCAMERAINFO_BV_BACK].aeTranslationMatrix[0], 
            a_ptFisheyeModel_v2 + alCAMERAINFO_BV_BACK, 
            wDegree, 
            &(a_ptLineData->aDynamicTrailLine[1][wDegIdx + wHalfDTLCount]));
    }
}

#ifdef WIN32

/*
    \brief To export the calculated trail line data to a txt file. This is used for trail line test of FW team.
    \param a_ptLineData [IN] The data array to export the trail line data.
    \param a_lPairNum [IN] The pair count in the data array, a_ptLineData.
    \param a_pwcFileName [IN] The filename to write the data.
    \param a_pcPrefix [IN] A prefix string to indiate which kind of trial line of the file.
    \return None.
*/
void alTRAILLINE_SaveLineDataToText(alTRAILLINE_PairData * a_ptLineData, UINT32 a_lPairNum, wchar_t * a_pwcFileName, char * a_pcPrefix)
{
    UINT32 index;
    FILE *pf;

    _wfopen_s(&pf, a_pwcFileName, L"wb");

    if (NULL == pf) {
        DEBUG_Printf("can not create file %s.\n", a_pwcFileName);
        return;
    }    

    fprintf(pf, "// [Chinson] This file is automatically generated by the Program\n");    

    fprintf(pf, "static Resrc_Line_t astTLine%s[] = {\n", a_pcPrefix);
    for (index = 0; index < a_lPairNum; index++) 
    {
        fprintf(pf, "\t{ %d, %d, %d, %d, %d, %d, %d }, \n", 
            a_ptLineData[index].cThickness, 
            a_ptLineData[index].cColor,
            a_ptLineData[index].cLineType,
            a_ptLineData[index].wStartX,
            a_ptLineData[index].wStartY,
            a_ptLineData[index].wEndX,
            a_ptLineData[index].wEndY
            );
    }
    fprintf(pf, "};\n\n");

    fclose(pf);

}

#endif
