
#include "alAVM2DKOverlaping.h"
#include "alFM_v2_1.h"
#include "alLUT_v2.h"
#include <math.h>       /* sqrt */
#include <assert.h>
#include "basedef.h"
#define MM_DOMAIN 0

static UINT8 SetViewIndex(FLOAT64 a_eX, FLOAT64 a_eY, UINT8 a_aucViewIndex[2], alAVM2D_Cfg  *a_ptAVMCfg);
static UINT8 CheckCurveB(UINT8 a_ucRegion, UINT8 a_ucMode, FLOAT64 a_eX, FLOAT64 a_eY, alAVM2D_OverLap *a_tOverLapCfg);
static UINT8 CheckCurveA(UINT8 a_ucRegion, UINT8 a_ucMode, FLOAT64 a_eX, FLOAT64 a_eY, alAVM2D_OverLap *a_tOverLapCfg);
static UINT8 CheckCurve(UINT8 a_ucRegion, FLOAT64 a_eX, FLOAT64 a_eY, alAVM2D_Cfg  *a_ptAVMCfg, UINT8 a_aucFlag[2], alAVM2D_OverLap *a_tOverLapCfg);
static UINT8 ViewWeightingCal(FLOAT64 a_eX, FLOAT64 a_eY, UINT8 a_ucWeightMode, alAVM2D_Cfg  *a_ptAVMCfg, FLOAT32 a_afWeight[2], alAVM2D_OverLap *a_tOverLapCfg);

static UINT8 FindStitchRegionAndCalWeight(FLOAT64 a_eX, FLOAT64 a_eY, const alAVM2D_StitchLineCfg *a_ptStitchLine, FLOAT32 a_afWeight[2])
{

    UINT8 ucIndex, ucStitchIndex = 0, ucPosIndex;
    // eAngle1: 與較大角度的向量的夾角, eAngle2: 與較小角度的向量的夾角
    FLOAT64 eAngle1, eAngle2;

    // 點座標位於車身盲區內者，直接回傳
    {
        if(a_eX > a_ptStitchLine->tStitchLine[0].fStartPointX
            && a_eX < a_ptStitchLine->tStitchLine[3].fStartPointX
            && a_eY > a_ptStitchLine->tStitchLine[0].fStartPointY
            && a_eY < a_ptStitchLine->tStitchLine[6].fStartPointY)
        {
            a_afWeight[0] = 0;
            a_afWeight[1] = 0;
            return alAVM2D_STITCH_REGION_BLOCK;
        }
    }

    {
        // (1) 先求與4個端點的最近距離
        FLOAT32 fDistance2StartPt[4];
        for(ucIndex = 0; ucIndex < 4; ucIndex++)
        {
            fDistance2StartPt[ucIndex] = (FLOAT32) ((a_eX - a_ptStitchLine->tStitchLine[ucIndex*3].fStartPointX) * (a_eX - a_ptStitchLine->tStitchLine[ucIndex*3].fStartPointX)
                + (a_eY - a_ptStitchLine->tStitchLine[ucIndex*3].fStartPointY) * (a_eY - a_ptStitchLine->tStitchLine[ucIndex*3].fStartPointY));
            if(fDistance2StartPt[ucIndex] < fDistance2StartPt[ucStitchIndex])
            {
                ucStitchIndex = ucIndex;
            }
        }
    }
    // (2) 算出點座標位於兩向量的哪一側, 較小角度的外側為0, 兩向量內側為 1, 較大角度的外側為 2.
    {
        FLOAT32 fVx, fVy, fL;
        fVx = (FLOAT32)(a_eX - a_ptStitchLine->tStitchLine[ucStitchIndex * 3].fStartPointX);
        fVy = (FLOAT32)(a_eY - a_ptStitchLine->tStitchLine[ucStitchIndex * 3].fStartPointY);
        fL = (FLOAT32)sqrt(fVx * fVx + fVy * fVy);
        fVx = fVx / fL;
        fVy = fVy / fL;

        eAngle1 = fVx * a_ptStitchLine->tStitchLine[ucStitchIndex * 3].fVx + fVy * a_ptStitchLine->tStitchLine[ucStitchIndex * 3].fVy;
        if(eAngle1 >= 1.0) eAngle1 = 1.0;
        eAngle1 = acos(eAngle1);
        eAngle2 = fVx * a_ptStitchLine->tStitchLine[ucStitchIndex * 3 + 1].fVx + fVy * a_ptStitchLine->tStitchLine[ucStitchIndex * 3 + 1].fVy;
        if(eAngle2 >= 1.0) eAngle2 = 1.0;
        eAngle2 = acos(eAngle2);

        if(eAngle1 <= a_ptStitchLine->fStitchRegionAngel[ucStitchIndex] && eAngle2 <= a_ptStitchLine->fStitchRegionAngel[ucStitchIndex]) // 兩向量內側 => 1
        {
            ucPosIndex = 1;
        }
        else if(eAngle1 > eAngle2) // 較小角度的外側 => 0
        {
            ucPosIndex = 0;
        }
        else // 較大角度的外側 => 0
        {
            ucPosIndex = 2;
        }
    }

    // (3) 指定區域
    {
        if(ucStitchIndex == 0) // 左上區域
        {
            if(ucPosIndex == 0) //  較小角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_LEFT;
            }
            else if(ucPosIndex == 1) // 兩向量內側
            {
                a_afWeight[0] = (FLOAT32)(eAngle2 / (eAngle1 + eAngle2));
                a_afWeight[1] = 1.0f - a_afWeight[0];
                return alAVM2D_STITCH_REGION_FRONTLEFT;
            }
            else if(ucPosIndex == 2) // 較大角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_FRONT;
            }
        }
        else if(ucStitchIndex == 1) // 右上區域
        {
            if(ucPosIndex == 0) //  較小角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_FRONT;
            }
            else if(ucPosIndex == 1) // 兩向量內側
            {
                a_afWeight[0] = (FLOAT32)(eAngle1 / (eAngle1 + eAngle2));
                a_afWeight[1] = 1.0f - a_afWeight[0];
                return alAVM2D_STITCH_REGION_FRONTRIGHT;
            }
            else if(ucPosIndex == 2) // 較大角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_RIGHT;
            }
        }
        else if(ucStitchIndex == 2) // 左下區域
        {
            if(ucPosIndex == 0) //  較小角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_BACK;
            }
            else if(ucPosIndex == 1) // 兩向量內側
            {
                a_afWeight[0] = (FLOAT32)(eAngle2 / (eAngle1 + eAngle2));
                a_afWeight[1] = 1.0f - a_afWeight[0];
                return alAVM2D_STITCH_REGION_LEFTBACK;
            }
            else if(ucPosIndex == 2) // 較大角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_LEFT;
            }
        }
        else if(ucStitchIndex == 3) // 右下區域
        {
            if(ucPosIndex == 0) //  較小角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_RIGHT;
            }
            else if(ucPosIndex == 1) // 兩向量內側
            {
                a_afWeight[0] = (FLOAT32)(eAngle1 / (eAngle1 + eAngle2));
                a_afWeight[1] = 1.0f - a_afWeight[0];
                return alAVM2D_STITCH_REGION_RIGHTBACK;
            }
            else if(ucPosIndex == 2) // 較大角度的外側
            {
                a_afWeight[0] = 1.0f;
                a_afWeight[1] = 0.0f;
                return alAVM2D_STITCH_REGION_BACK;
            }
        }
    }

    return alAVM2D_STITCH_REGION_ERROR;


}


UINT8 CheckCurveB(UINT8 a_ucRegion, UINT8 a_ucMode, FLOAT64 a_eX, FLOAT64 a_eY, alAVM2D_OverLap *a_tOverLapCfg)
{
	FLOAT64 eOffsetTmp, eTmpX, eTmpY, eCosTmp, eVy, eVx, eThetaTmp, eD, aeDistTmp[2];
	FLOAT64 eAbsX = 0, eR, eRx, eRy, eTheta, eDshort, eThreshold, eThetaCircle;
	INT8 cCurveType = 99;
	alAVM2D_Line tLawLine;

	// set information
	if(a_tOverLapCfg->atStitchLineB[1].fdegree < 331)
	{
		tLawLine.fdegree = a_tOverLapCfg->atStitchLineB[1].fdegree + 90;
	}
	else
	{
		tLawLine.fdegree = a_tOverLapCfg->atStitchLineB[1].fdegree - 90;
	}
	tLawLine.fRatio = (FLOAT32)tan(tLawLine.fdegree * alPI / 180);
	tLawLine.fOffset = (FLOAT32)(a_tOverLapCfg->atPointB[2].lY - tLawLine.fRatio*a_tOverLapCfg->atPointB[2].lX);
	tLawLine.fStartPointX = (FLOAT32)a_tOverLapCfg->atPointB[2].lX;
	tLawLine.fStartPointY = (FLOAT32)a_tOverLapCfg->atPointB[2].lY;
	tLawLine.fVx = (FLOAT32)cos(tLawLine.fdegree * alPI / 180);
	tLawLine.fVy = (FLOAT32)sin(tLawLine.fdegree * alPI / 180);

	eR = (a_tOverLapCfg->atPointB[0].lY - tLawLine.fOffset) / tLawLine.fRatio - a_tOverLapCfg->tStitchStart.lX;
	eR = fabs(eR);
	eRy = a_tOverLapCfg->atPointB[0].lY;
	if(a_tOverLapCfg->atPointB[2].lX >= a_tOverLapCfg->atPointB[0].lX)
	{
		eRx = a_tOverLapCfg->atPointB[0].lX + eR;
	}
	else
	{
		eRx = a_tOverLapCfg->atPointB[0].lX - eR;
	}
	eDshort = fabs(a_tOverLapCfg->atPointB[1].lY - a_tOverLapCfg->atPointB[0].lY);
	eTheta = 2*atan(eDshort/eR) * 180.0 / alPI;

	// set Curve Region
	eThreshold = a_tOverLapCfg->atStitchLineB[1].fRatio*a_eX + a_tOverLapCfg->atStitchLineB[1].fOffset;
	if(fabs(a_eX) > fabs(eRx))
	{	// curve 上半部
		if(fabs(a_eY) < fabs(eRy))
		{	// 垂直區
			cCurveType = 0;
		}
		else
		{	
			if(fabs(a_eY) < fabs(eThreshold))
			{	// 斜線區
				cCurveType = 1;	
			}
			else
			{	// 不在Curve B 範圍內
				cCurveType = -1;
			}
		}
	}
	else if(fabs(a_eY) < fabs(eRy))
	{	// 垂直區
		cCurveType = 0;
	}
	else
	{
		eVx = a_eX - eRx;
		eVy = a_eY - eRy;
		if(eRx > 0)
		{	// (-1,0)的角度
			eCosTmp = -eVx / (sqrt(eVx*eVx + eVy*eVy));
		}
		else
		{	// (1,0)的角度
			eCosTmp = eVx / (sqrt(eVx*eVx + eVy*eVy));
		}
		eThetaTmp = acos(eCosTmp) * 180.0 / alPI;
		if(eThetaTmp > eTheta)
		{
			if(fabs(a_eY) < fabs(eThreshold))
			{	// 斜線區
				cCurveType = 1;	
			}
			else
			{	// 不在Curve B 範圍內
				cCurveType = -1;
			}
		}
		else
		{
			eD = sqrt(eVx*eVx + eVy*eVy);
			if(eD < eR) 
			{	// 扇形區
				cCurveType = 2;	
			}
			else
			{	// 不在Curve B 範圍內
				cCurveType = -1;
			}
		}
	}

	// 依照cCurveType 決定Distance
	if(cCurveType == 0 || cCurveType == 1)
	{	// 斜線或垂直區
		aeDistTmp[0] = a_eX - a_tOverLapCfg->tStitchStart.lX;
		aeDistTmp[0] = fabs(aeDistTmp[0]);
		eOffsetTmp = a_eY - tLawLine.fRatio*a_eX;
		eTmpX = (eOffsetTmp-a_tOverLapCfg->atStitchLineB[1].fOffset) / (a_tOverLapCfg->atStitchLineB[1].fRatio - tLawLine.fRatio);
		eTmpY = tLawLine.fRatio*eTmpX + eOffsetTmp;
		aeDistTmp[1] = sqrt((a_eX-eTmpX)*(a_eX-eTmpX) + (a_eY-eTmpY)*(a_eY-eTmpY));

		if(aeDistTmp[0] < aeDistTmp[1])
		{
			a_tOverLapCfg->eCurveDistanceB = aeDistTmp[0];
		}
		else
		{
			a_tOverLapCfg->eCurveDistanceB = aeDistTmp[1];
		}

		return TRUE;
	}
	else if(cCurveType == 2)
	{	// 扇形區 
		eVx = a_eX - eRx;
		eVy = a_eY - eRy;
		if(eVx == 0)
		{
			eThetaCircle = (eVy < 0) ? 270 : 90;
		}
		else if(eVy == 0)
		{
			eThetaCircle = (eVx < 0) ? 180 : 0;
		}
		else
		{
			eThetaCircle = atan(eVy/eVx) * 180.0 / alPI;
		}
		if(eVx < 0)
		{
			if(eVy < 0)
			{
				eThetaCircle = (eThetaCircle > 0) ? eThetaCircle + 180 : eThetaCircle;
			}
			else
			{
				eThetaCircle = (eThetaCircle < 0) ? eThetaCircle + 180 : eThetaCircle;
			}
			// eThetaCircle = (eThetaCircle < 0) ? eThetaCircle + 180 : eThetaCircle;
		}
		// eThetaCircle = (eThetaCircle < 0) ? eThetaCircle + 180 : eThetaCircle;
		eTmpX = eRx + eR*cos(eThetaCircle * alPI / 180);
		eTmpY = eRy + eR*sin(eThetaCircle * alPI / 180);
		a_tOverLapCfg->eCurveDistanceB = sqrt((a_eX-eTmpX)*(a_eX-eTmpX) + (a_eY-eTmpY)*(a_eY-eTmpY));
		return TRUE;
	}
	else
	{	// 不在Curve B 範圍內
		a_tOverLapCfg->eCurveDistanceB = -1;
		return FALSE;
	}
}

UINT8 CheckCurveA(UINT8 a_ucRegion, UINT8 a_ucMode, FLOAT64 a_eX, FLOAT64 a_eY, alAVM2D_OverLap *a_tOverLapCfg)
{
	FLOAT64 eOffsetTmp, eTmpX, eTmpY, eCosTmp, eVy, eVx, eThetaTmp, eD, aeDistTmp[2];
	FLOAT64 eAbsX = 0, eR, eRx, eRy, eTheta, eDshort, eThreshold, eThetaCircle;
	INT8 cCurveType = 99;
	alAVM2D_Line tLawLine;

	// set information
	if(a_tOverLapCfg->atStitchLineA[1].fdegree < 331)
	{
		tLawLine.fdegree = a_tOverLapCfg->atStitchLineA[1].fdegree + 90;
	}
	else
	{
		tLawLine.fdegree = a_tOverLapCfg->atStitchLineA[1].fdegree - 90;
	}
	tLawLine.fRatio = (FLOAT32)tan(tLawLine.fdegree * alPI / 180);
	tLawLine.fOffset = (FLOAT32)(a_tOverLapCfg->atPointA[2].lY - tLawLine.fRatio*a_tOverLapCfg->atPointA[2].lX);
	tLawLine.fStartPointX = (FLOAT32)a_tOverLapCfg->atPointA[2].lX;
	tLawLine.fStartPointY = (FLOAT32)a_tOverLapCfg->atPointA[2].lY;
	tLawLine.fVx = (FLOAT32)cos(tLawLine.fdegree * alPI / 180);
	tLawLine.fVy = (FLOAT32)sin(tLawLine.fdegree * alPI / 180);

	eR = (tLawLine.fRatio*a_tOverLapCfg->atPointA[0].lX + tLawLine.fOffset) - a_tOverLapCfg->tStitchStart.lY;
	eR = fabs(eR);
	eRx = a_tOverLapCfg->atPointA[0].lX;
	if(a_tOverLapCfg->atPointA[2].lY >= a_tOverLapCfg->atPointA[0].lY)
	{
		eRy = a_tOverLapCfg->atPointA[0].lY + eR;
	}
	else
	{
		eRy = a_tOverLapCfg->atPointA[0].lY - eR;
	}
	eDshort = fabs(a_tOverLapCfg->atPointA[1].lX - a_tOverLapCfg->atPointA[0].lX);
	eTheta = 2*atan(eDshort/eR) * 180.0 / alPI;

	// set Curve Region
	eThreshold = a_tOverLapCfg->atStitchLineA[1].fRatio*a_eX + a_tOverLapCfg->atStitchLineA[1].fOffset;
	if(fabs(a_eY) > fabs(eRy))
	{	// curve 上半部
		if(fabs(a_eX) < fabs(eRx))
		{	// 水平區
			cCurveType = 0;
		}
		else
		{	
			if(fabs(a_eY) > fabs(eThreshold))
			{	// 斜線區
				cCurveType = 1;	
			}
			else
			{	// 不在Curve A 和範圍內
				cCurveType = -1;
			}
		}
	}
	else if(fabs(a_eX) < fabs(eRx))
	{	// 水平區
		cCurveType = 0;
	}
	else
	{
		eVx = a_eX - eRx;
		eVy = a_eY - eRy;
		if(eRy > 0)
		{	// (0,-1)的角度
			eCosTmp = -eVy / (sqrt(eVx*eVx + eVy*eVy));
		}
		else
		{	// (0,1)的角度
			eCosTmp = eVy / (sqrt(eVx*eVx + eVy*eVy));
		}
		eThetaTmp = acos(eCosTmp) * 180.0 / alPI;
		if(eThetaTmp > eTheta)
		{
			if(fabs(a_eY) > fabs(eThreshold))
			{	// 斜線區
				cCurveType = 1;	
			}
			else
			{	// 不在Curve A 和範圍內
				cCurveType = -1;
			}
		}
		else
		{
			eD = sqrt(eVx*eVx + eVy*eVy);
			if(eD < eR) 
			{	// 扇形區
				cCurveType = 2;	
			}
			else
			{	// 不在Curve A 和範圍內
				cCurveType = -1;
			}
		}
	}

	// 依照cCurveType 決定Distance
	if(cCurveType == 0 || cCurveType == 1)
	{	// 斜線或水平區
		aeDistTmp[0] = a_eY - a_tOverLapCfg->tStitchStart.lY;
		aeDistTmp[0] = fabs(aeDistTmp[0]);
		eOffsetTmp = a_eY - tLawLine.fRatio*a_eX;
		eTmpX = (eOffsetTmp-a_tOverLapCfg->atStitchLineA[1].fOffset) / (a_tOverLapCfg->atStitchLineA[1].fRatio - tLawLine.fRatio);
		eTmpY = tLawLine.fRatio*eTmpX + eOffsetTmp;
		aeDistTmp[1] = sqrt((a_eX-eTmpX)*(a_eX-eTmpX) + (a_eY-eTmpY)*(a_eY-eTmpY));

		if(aeDistTmp[0] < aeDistTmp[1])
		{
			a_tOverLapCfg->eCurveDistanceA = aeDistTmp[0];
		}
		else
		{
			a_tOverLapCfg->eCurveDistanceA = aeDistTmp[1];
		}

		return TRUE;
	}
	else if(cCurveType == 2)
	{	// 扇形區 
		eVx = a_eX - eRx;
		eVy = a_eY - eRy;
		if(eVx == 0)
		{
			eThetaCircle = (eVy < 0) ? 270 : 90;
		}
		else if(eVy == 0)
		{
			eThetaCircle = (eVx < 0) ? 180 : 0;
		}
		else
		{
			eThetaCircle = atan(eVy/eVx) * 180.0 / alPI;
		}
		if(eVx < 0)
		{
			if(eVy < 0)
			{
				eThetaCircle = (eThetaCircle > 0) ? eThetaCircle + 180 : eThetaCircle;
			}
			else
			{
				eThetaCircle = (eThetaCircle < 0) ? eThetaCircle + 180 : eThetaCircle;
			}
			// eThetaCircle = (eThetaCircle < 0) ? eThetaCircle + 180 : eThetaCircle;
		}
		eTmpX = eRx + eR*cos(eThetaCircle * alPI / 180);
		eTmpY = eRy + eR*sin(eThetaCircle * alPI / 180);
		a_tOverLapCfg->eCurveDistanceA = sqrt((a_eX-eTmpX)*(a_eX-eTmpX) + (a_eY-eTmpY)*(a_eY-eTmpY));
		return TRUE;
	}
	else
	{	// 不在Curve A 和範圍內
		a_tOverLapCfg->eCurveDistanceA = -1;
		return FALSE;
	}

}

UINT8 CheckCurve(UINT8 a_ucRegion, FLOAT64 a_eX, FLOAT64 a_eY, alAVM2D_Cfg  *a_ptAVMCfg, UINT8 a_aucFlag[2], alAVM2D_OverLap *a_tOverLapCfg)
{
	INT32 alBoundAngle[2], lCornerIndex = 0, alMode[2];
	FLOAT32 afTime[2];
	FLOAT64 aeTmp[3];

	switch(a_ucRegion)
	{
	case alAVM2D_STITCH_REGION_FRONTLEFT:
		alBoundAngle[0] = 180;
		alBoundAngle[1] = 270;
		lCornerIndex = 0;
		alMode[0] = 0;
		alMode[1] = 0;
		a_tOverLapCfg->atStitchLineA[0].fdegree = (FLOAT32)alBoundAngle[0];
		a_tOverLapCfg->atStitchLineB[0].fdegree = (FLOAT32)alBoundAngle[1];
	break;
	case alAVM2D_STITCH_REGION_FRONTRIGHT:
		alBoundAngle[0] = 270;
		alBoundAngle[1] = 360;
		lCornerIndex = 1;
		alMode[0] = 0;
		alMode[1] = 1;
		a_tOverLapCfg->atStitchLineA[0].fdegree = (FLOAT32)alBoundAngle[1];
		a_tOverLapCfg->atStitchLineB[0].fdegree = (FLOAT32)alBoundAngle[0];
	break;
	case alAVM2D_STITCH_REGION_LEFTBACK:
		alBoundAngle[0] = 90;
		alBoundAngle[1] = 180;	
		lCornerIndex = 2;
		alMode[0] = 1;
		alMode[1] = 0;
		a_tOverLapCfg->atStitchLineA[0].fdegree = (FLOAT32)alBoundAngle[1];
		a_tOverLapCfg->atStitchLineB[0].fdegree = (FLOAT32)alBoundAngle[0];
	break;
	case alAVM2D_STITCH_REGION_RIGHTBACK:
		alBoundAngle[0] = 0;
		alBoundAngle[1] = 90;	
		lCornerIndex = 3;
		alMode[0] = 1;
		alMode[1] = 1;
		a_tOverLapCfg->atStitchLineA[0].fdegree = (FLOAT32)alBoundAngle[0];
		a_tOverLapCfg->atStitchLineB[0].fdegree = (FLOAT32)alBoundAngle[1];
	break;
	default:
		lCornerIndex = -1;
		a_aucFlag[0] = 0;
		a_aucFlag[1] = 0;
		return TRUE;
	break;
	}
	
	/////
	// global
	a_tOverLapCfg->lCornerIndex = lCornerIndex;
	a_tOverLapCfg->tStitchStart = a_ptAVMCfg->atStitchLineStart[lCornerIndex];
	a_tOverLapCfg->fAngleStitch = a_ptAVMCfg->afStitchLineAngle[lCornerIndex];

	//  A
	a_tOverLapCfg->atStitchLineA[1].fdegree = a_ptAVMCfg->afStitchLineAngle[lCornerIndex] + a_ptAVMCfg->tOverlapLoadCfg.afCurveALineAngleOffset[lCornerIndex];
	assert(a_tOverLapCfg->atStitchLineA[1].fdegree >= alBoundAngle[0] && a_tOverLapCfg->atStitchLineA[1].fdegree <= alBoundAngle[1]);
	assert(a_tOverLapCfg->atStitchLineA[1].fdegree != 90 && a_tOverLapCfg->atStitchLineA[1].fdegree != 270);
	
	a_tOverLapCfg->atStitchLineA[1].fVx = (FLOAT32)cos(a_tOverLapCfg->atStitchLineA[1].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineA[1].fVy = (FLOAT32)sin(a_tOverLapCfg->atStitchLineA[1].fdegree * alPI / 180);

	a_tOverLapCfg->atStitchLineA[0].fVx = (FLOAT32)cos(a_tOverLapCfg->atStitchLineA[0].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineA[0].fVy = (FLOAT32)sin(a_tOverLapCfg->atStitchLineA[0].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineA[0].fStartPointX = (FLOAT32)a_tOverLapCfg->tStitchStart.lX;
	a_tOverLapCfg->atStitchLineA[0].fStartPointY = (FLOAT32)a_tOverLapCfg->tStitchStart.lY;
	
	a_tOverLapCfg->atPointA[0].lX = a_tOverLapCfg->tStitchStart.lX + a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveA[lCornerIndex][0] - a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveA[lCornerIndex][1];
	a_tOverLapCfg->atPointA[0].lY = a_tOverLapCfg->tStitchStart.lY;

	a_tOverLapCfg->atPointA[1].lX = a_tOverLapCfg->tStitchStart.lX + a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveA[lCornerIndex][0];
	a_tOverLapCfg->atPointA[1].lY = a_tOverLapCfg->tStitchStart.lY;

	a_tOverLapCfg->atStitchLineA[1].fStartPointX = (FLOAT32)a_tOverLapCfg->atPointA[1].lX;
	a_tOverLapCfg->atStitchLineA[1].fStartPointY = (FLOAT32)a_tOverLapCfg->atPointA[1].lY;


	aeTmp[0] = a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveA[lCornerIndex][1]*a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveA[lCornerIndex][1]; // d1^2
	aeTmp[1] = a_tOverLapCfg->atStitchLineA[1].fVx*a_tOverLapCfg->atStitchLineA[1].fVx;						// Vx^2
	aeTmp[2] = a_tOverLapCfg->atStitchLineA[1].fVy*a_tOverLapCfg->atStitchLineA[1].fVy;						// Vy^2
	afTime[0] = (FLOAT32)sqrt(aeTmp[0] / (aeTmp[1] + aeTmp[2]));
	
	a_tOverLapCfg->atPointA[2].lY = (INT32)(a_tOverLapCfg->atPointA[1].lY + a_tOverLapCfg->atStitchLineA[1].fVy*afTime[0]);
	a_tOverLapCfg->atPointA[2].lX = (INT32)(a_tOverLapCfg->atPointA[1].lX + a_tOverLapCfg->atStitchLineA[1].fVx*afTime[0]);

	a_tOverLapCfg->atStitchLineA[1].fRatio = (FLOAT32)tan(a_tOverLapCfg->atStitchLineA[1].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineA[1].fOffset = (FLOAT32)(a_tOverLapCfg->atStitchLineA[1].fStartPointY - a_tOverLapCfg->atStitchLineA[1].fRatio*a_tOverLapCfg->atStitchLineA[1].fStartPointX);

	//  B
	a_tOverLapCfg->atStitchLineB[1].fdegree = a_ptAVMCfg->afStitchLineAngle[lCornerIndex] + a_ptAVMCfg->tOverlapLoadCfg.afCurveBLineAngleOffset[lCornerIndex];
	assert(a_tOverLapCfg->atStitchLineB[1].fdegree >= alBoundAngle[0] && a_tOverLapCfg->atStitchLineB[1].fdegree <= alBoundAngle[1]);
	assert(a_tOverLapCfg->atStitchLineB[1].fdegree != 90 && a_tOverLapCfg->atStitchLineB[1].fdegree != 270);
	
	a_tOverLapCfg->atStitchLineB[1].fVx = (FLOAT32)cos(a_tOverLapCfg->atStitchLineB[1].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineB[1].fVy = (FLOAT32)sin(a_tOverLapCfg->atStitchLineB[1].fdegree * alPI / 180);

	a_tOverLapCfg->atStitchLineB[0].fVx = (FLOAT32)cos(a_tOverLapCfg->atStitchLineB[0].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineB[0].fVy = (FLOAT32)sin(a_tOverLapCfg->atStitchLineB[0].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineB[0].fStartPointX = (FLOAT32)a_tOverLapCfg->tStitchStart.lX;
	a_tOverLapCfg->atStitchLineB[0].fStartPointY = (FLOAT32)a_tOverLapCfg->tStitchStart.lY;
	
	a_tOverLapCfg->atPointB[0].lY = a_tOverLapCfg->tStitchStart.lY + a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveB[lCornerIndex][0] - a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveB[lCornerIndex][1];
	a_tOverLapCfg->atPointB[0].lX = a_tOverLapCfg->tStitchStart.lX;

	a_tOverLapCfg->atPointB[1].lY = a_tOverLapCfg->tStitchStart.lY + a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveB[lCornerIndex][0];
	a_tOverLapCfg->atPointB[1].lX = a_tOverLapCfg->tStitchStart.lX;

	a_tOverLapCfg->atStitchLineB[1].fStartPointX = (FLOAT32)a_tOverLapCfg->atPointB[1].lX;
	a_tOverLapCfg->atStitchLineB[1].fStartPointY = (FLOAT32)a_tOverLapCfg->atPointB[1].lY;


	aeTmp[0] = a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveB[lCornerIndex][1]*a_ptAVMCfg->tOverlapLoadCfg.alDistanceCurveB[lCornerIndex][1]; // d1^2
	aeTmp[1] = a_tOverLapCfg->atStitchLineB[1].fVx*a_tOverLapCfg->atStitchLineB[1].fVx;						// Vx^2
	aeTmp[2] = a_tOverLapCfg->atStitchLineB[1].fVy*a_tOverLapCfg->atStitchLineB[1].fVy;						// Vy^2
	afTime[1] = (FLOAT32)sqrt(aeTmp[0] / (aeTmp[1] + aeTmp[2]));
	
	a_tOverLapCfg->atPointB[2].lY = (INT32)(a_tOverLapCfg->atPointB[1].lY + a_tOverLapCfg->atStitchLineB[1].fVy*afTime[1]);
	a_tOverLapCfg->atPointB[2].lX = (INT32)(a_tOverLapCfg->atPointB[1].lX + a_tOverLapCfg->atStitchLineB[1].fVx*afTime[1]);

	a_tOverLapCfg->atStitchLineB[1].fRatio = (FLOAT32)tan(a_tOverLapCfg->atStitchLineB[1].fdegree * alPI / 180);
	a_tOverLapCfg->atStitchLineB[1].fOffset = (FLOAT32)(a_tOverLapCfg->atStitchLineB[1].fStartPointY - a_tOverLapCfg->atStitchLineB[1].fRatio*a_tOverLapCfg->atStitchLineB[1].fStartPointX);

	/////

	a_aucFlag[0] = CheckCurveA(a_ucRegion, alMode[0], a_eX, a_eY, a_tOverLapCfg);
	a_aucFlag[1] = CheckCurveB(a_ucRegion, alMode[1], a_eX, a_eY, a_tOverLapCfg);

	
	return TRUE;
}

UINT8 SetViewIndex(FLOAT64 a_eX, FLOAT64 a_eY, UINT8 a_aucViewIndex[2], alAVM2D_Cfg * a_ptAVMCfg)
{
	alPointINT32   *atStartPoint;
	// alPointINT32   *patCornerPoint;
	FLOAT64 eDistance = 0;

	

	// patCornerPoint = a_ptAVMCfg->atCornerPoint;
	atStartPoint =  a_ptAVMCfg->atStitchLineStart;

	if(a_eY > atStartPoint[2].lY)
	{	// BACK
		if(a_eX >= atStartPoint[3].lX)
		{	// BACK-右半部
			
			a_aucViewIndex[0] = alCAMERAINFO_BV_RIGHT;
			a_aucViewIndex[1] = alCAMERAINFO_BV_BACK;
			return alAVM2D_STITCH_REGION_RIGHTBACK;
		
		}
		else if(a_eX > atStartPoint[2].lX)
		{ // BACK-中間
			a_aucViewIndex[0] = alCAMERAINFO_BV_BACK;
			a_aucViewIndex[1] = alCAMERAINFO_BV_BACK;
			return alAVM2D_STITCH_REGION_BACK;
		}
		else
		{	// BACK-左半部
			a_aucViewIndex[0] = alCAMERAINFO_BV_LEFT;
			a_aucViewIndex[1] = alCAMERAINFO_BV_BACK;
			return alAVM2D_STITCH_REGION_LEFTBACK;
		}
	}
	else if(a_eY > atStartPoint[0].lY)
	{ // MID
		if(a_eX >= atStartPoint[3].lX)
		{	// MID-右半部
			a_aucViewIndex[0] = alCAMERAINFO_BV_RIGHT;
			a_aucViewIndex[1] = 255;
			return alAVM2D_STITCH_REGION_RIGHT;
		}
		else if(a_eX > atStartPoint[2].lX)
		{ // MID-中間
			a_aucViewIndex[0] = 255;
			a_aucViewIndex[1] = 255;
			return alAVM2D_STITCH_REGION_BLOCK;
		}
		else
		{	// MID-左半部
			a_aucViewIndex[0] = alCAMERAINFO_BV_LEFT;
			a_aucViewIndex[1] = 255;
			return alAVM2D_STITCH_REGION_LEFT;
		}
	}
	else
	{	// FRONT
		if(a_eX >= atStartPoint[3].lX)
		{	// FRONT-右半部
			a_aucViewIndex[0] = alCAMERAINFO_BV_RIGHT;
			a_aucViewIndex[1] = alCAMERAINFO_BV_FRONT;
			return alAVM2D_STITCH_REGION_FRONTRIGHT;
		}
		else if(a_eX > atStartPoint[2].lX)
		{ // FRONT-中間
			a_aucViewIndex[0] = alCAMERAINFO_BV_FRONT;
			a_aucViewIndex[1] = 255;
			return alAVM2D_STITCH_REGION_FRONT;
		}
		else
		{	// FRONT-左半部
			a_aucViewIndex[0] = alCAMERAINFO_BV_LEFT;
			a_aucViewIndex[1] = alCAMERAINFO_BV_FRONT;
			return alAVM2D_STITCH_REGION_FRONTLEFT;
		}
	}
	return alAVM2D_STITCH_REGION_ERROR;
}

UINT8 ViewWeightingCal(FLOAT64 a_eX, FLOAT64 a_eY, UINT8 a_ucWeightMode, alAVM2D_Cfg  *a_ptAVMCfg, FLOAT32 a_afWeight[2], alAVM2D_OverLap *a_tOverLapCfg)
{
	switch(a_ucWeightMode)
		{
			case alAVM2D_WEIGHT_MODE_BLOCK:
				a_afWeight[0] = 0;
				a_afWeight[1] = 0;
				return TRUE;
			break;
			case alAVM2D_WEIGHT_MODE_VIEW_0:
				a_afWeight[0] = 1;
				a_afWeight[1] = 0;
				return TRUE;	
			break;
			case alAVM2D_WEIGHT_MODE_VIEW_1:
				a_afWeight[0] = 0;
				a_afWeight[1] = 1;
				return TRUE;	
			break;
			case alAVM2D_WEIGHT_MODE_SINGLEVIEW:
				a_afWeight[0] = 1;
				a_afWeight[1] = 0;
				return TRUE;	
			break;
			case alAVM2D_WEIGHT_MODE_OVERLAP:
				a_afWeight[0] = (FLOAT32)(a_tOverLapCfg->eCurveDistanceB / (a_tOverLapCfg->eCurveDistanceA + a_tOverLapCfg->eCurveDistanceB));
				
				if(a_afWeight[0] < 0 || a_afWeight[0] >1)
				{
					a_afWeight[1] = 2;
					a_afWeight[0] = 2;
				}
				else
				{
					a_afWeight[1] = 1 - a_afWeight[0];

				}
				return TRUE;	
			break;
			case alAVM2D_WEIGHT_MODE_ERROR:
				a_afWeight[0] = 0;
				a_afWeight[1] = 0;
				return FALSE;
			break;
			default:
				a_afWeight[0] = 0;
				a_afWeight[1] = 0;
				return FALSE;
			break;
		}
	return TRUE;
}

void alAVM2D_OverlapWeightCal(alAVM2D_Cfg * a_ptAVMCfg, FLOAT64 a_eX, FLOAT64 a_eY, const alAVM2D_StitchLineCfg *a_ptStitchLine, FLOAT32 a_afWeight[2], UINT8 a_aucViewIndex[2])
{
    UINT8 ucRegion = 0, ucCurveAFlag = 0, ucCurveBFlag = 0, aucCurveFlag[2], ucWeightMode;
	alAVM2D_OverLap tOverLapCfg;
	INT32 i = 0;

	if(a_ptAVMCfg->ucStitchLineType)
	{
		// 非黑區  >> 做接下來的判斷
		// step 1 : set view index and overlap region
		ucRegion = SetViewIndex(a_eX, a_eY, a_aucViewIndex, a_ptAVMCfg);
		assert(ucRegion != alAVM2D_STITCH_REGION_ERROR);

		// step 2 : CheckCurve
		CheckCurve(ucRegion, a_eX, a_eY, a_ptAVMCfg, aucCurveFlag, &tOverLapCfg);

		// step 3 : Set mode
		if(aucCurveFlag[0] && aucCurveFlag[1])
		{	// overlap
			ucWeightMode = alAVM2D_WEIGHT_MODE_OVERLAP;
		}
		else if(aucCurveFlag[0])
		{	// View 1 (curveA == 1 && curveB ==0)
			ucWeightMode = alAVM2D_WEIGHT_MODE_VIEW_1;
		}
		else if(aucCurveFlag[1])
		{	// View 0 (curveA == 0 && curveB ==1)
			ucWeightMode = alAVM2D_WEIGHT_MODE_VIEW_0;
		}
		else if(ucRegion == alAVM2D_STITCH_REGION_BLOCK || ucRegion == FALSE)
		{	// block
			ucWeightMode = alAVM2D_WEIGHT_MODE_BLOCK;
		}
		else
		{	// single view (View 0)
			ucWeightMode = alAVM2D_WEIGHT_MODE_SINGLEVIEW;
		}
	
		// step 4 : ViewWeightingCal
		ViewWeightingCal(a_eX, a_eY, ucWeightMode, a_ptAVMCfg, a_afWeight, &tOverLapCfg);
	}
	else
	{
		// Step 1 : decide stitch region
		ucRegion = FindStitchRegionAndCalWeight(a_eX, a_eY, a_ptStitchLine, a_afWeight);

		assert(ucRegion != alAVM2D_STITCH_REGION_ERROR);

		// Step 2
		switch(ucRegion)
		{
			case alAVM2D_STITCH_REGION_LEFT:
				a_aucViewIndex[0] = alCAMERAINFO_BV_LEFT;
				a_aucViewIndex[1] = 255;
			break;
			case alAVM2D_STITCH_REGION_RIGHT:
				a_aucViewIndex[0] = alCAMERAINFO_BV_RIGHT;
				a_aucViewIndex[1] = 255;
			break;
			case alAVM2D_STITCH_REGION_BACK:
				a_aucViewIndex[0] = alCAMERAINFO_BV_BACK;
				a_aucViewIndex[1] = 255;
			break;
			case alAVM2D_STITCH_REGION_FRONT:
				a_aucViewIndex[0] = alCAMERAINFO_BV_FRONT;
				a_aucViewIndex[1] = 255;
			break;

			case alAVM2D_STITCH_REGION_FRONTLEFT:
				a_aucViewIndex[0] = alCAMERAINFO_BV_FRONT;
				a_aucViewIndex[1] = alCAMERAINFO_BV_LEFT;
			break;
			case alAVM2D_STITCH_REGION_FRONTRIGHT:
				a_aucViewIndex[0] = alCAMERAINFO_BV_FRONT;
				a_aucViewIndex[1] = alCAMERAINFO_BV_RIGHT;
			break;
			case alAVM2D_STITCH_REGION_LEFTBACK:
				a_aucViewIndex[0] = alCAMERAINFO_BV_LEFT;
				a_aucViewIndex[1] = alCAMERAINFO_BV_BACK;
			break;
			case alAVM2D_STITCH_REGION_RIGHTBACK:
				a_aucViewIndex[0] = alCAMERAINFO_BV_RIGHT;
				a_aucViewIndex[1] = alCAMERAINFO_BV_BACK;
			break;
			case alAVM2D_STITCH_REGION_BLOCK:
				a_aucViewIndex[0] = 255;
				a_aucViewIndex[1] = 255;
			break;
		}
	}
}

void alAVM2D_SetStitchLineInfo(alAVM2D_Params *a_ptalAVM2DParams, alAVM2D_Cfg * a_ptAVMCfg, alAVM2D_StitchLineCfg *a_ptStitchLine)
{
    /*
        if you want to Set Stitch Line Infomation bt INI file, you need input :
        1. degree of  Line 2,5,8 and 11
        2. Degree Gap
    */
    INT32 i = 0;


    // set L0~2
    for(i = 0; i < 3 ; i++)
    {
#if MM_DOMAIN == 1
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptAVMCfg->atStitchLineStart[0].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptAVMCfg->atStitchLineStart[0].lY;
#else
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lY;
#endif
    }
    a_ptStitchLine->tStitchLine[2].fdegree = a_ptAVMCfg->afStitchLineAngle[0];
    a_ptStitchLine->tStitchLine[0].fdegree = a_ptStitchLine->tStitchLine[2].fdegree + a_ptAVMCfg->fStitchAngleRange;
    a_ptStitchLine->tStitchLine[1].fdegree = a_ptStitchLine->tStitchLine[2].fdegree - a_ptAVMCfg->fStitchAngleRange;
    for(i = 0; i < 3 ; i++)
    {
        a_ptStitchLine->tStitchLine[i].fRatio = (FLOAT32)tan(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fOffset = (FLOAT32)(a_ptStitchLine->tStitchLine[i].fStartPointY - a_ptStitchLine->tStitchLine[i].fRatio*a_ptStitchLine->tStitchLine[i].fStartPointX);

        a_ptStitchLine->tStitchLine[i].fVx = (FLOAT32) cos(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fVy = (FLOAT32) sin(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
    }
    a_ptStitchLine->fStitchRegionAngel[0] = (FLOAT32) (2 * a_ptAVMCfg->fStitchAngleRange * alPI / 180);

    // set L3~5
    for(i = 3; i < 6 ; i++)
    {
#if MM_DOMAIN == 1
       a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptAVMCfg->atStitchLineStart[1].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptAVMCfg->atStitchLineStart[1].lY;
#else
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lY;
#endif
    }
    a_ptStitchLine->tStitchLine[5].fdegree = a_ptAVMCfg->afStitchLineAngle[1];
    a_ptStitchLine->tStitchLine[3].fdegree = a_ptStitchLine->tStitchLine[5].fdegree + a_ptAVMCfg->fStitchAngleRange;
    a_ptStitchLine->tStitchLine[4].fdegree = a_ptStitchLine->tStitchLine[5].fdegree - a_ptAVMCfg->fStitchAngleRange;
    for(i = 3; i < 6 ; i++)
    {
        a_ptStitchLine->tStitchLine[i].fRatio = (FLOAT32)tan(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fOffset = (FLOAT32)(a_ptStitchLine->tStitchLine[i].fStartPointY - a_ptStitchLine->tStitchLine[i].fRatio*a_ptStitchLine->tStitchLine[i].fStartPointX);

        a_ptStitchLine->tStitchLine[i].fVx = (FLOAT32) cos(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fVy = (FLOAT32) sin(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
    }
    a_ptStitchLine->fStitchRegionAngel[1] = (FLOAT32) (2 * a_ptAVMCfg->fStitchAngleRange * alPI / 180);

    // set L6~8
    for(i = 6; i < 9 ; i++)
    {
#if MM_DOMAIN == 1
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptAVMCfg->atStitchLineStart[2].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptAVMCfg->atStitchLineStart[2].lY;
#else
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lY;
#endif
    }
    a_ptStitchLine->tStitchLine[8].fdegree = a_ptAVMCfg->afStitchLineAngle[2];
    a_ptStitchLine->tStitchLine[6].fdegree = a_ptStitchLine->tStitchLine[8].fdegree + a_ptAVMCfg->fStitchAngleRange;
    a_ptStitchLine->tStitchLine[7].fdegree = a_ptStitchLine->tStitchLine[8].fdegree - a_ptAVMCfg->fStitchAngleRange;
    for(i = 6; i < 9 ; i++)
    {
        a_ptStitchLine->tStitchLine[i].fRatio = (FLOAT32)tan(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fOffset = (FLOAT32)(a_ptStitchLine->tStitchLine[i].fStartPointY - a_ptStitchLine->tStitchLine[i].fRatio*a_ptStitchLine->tStitchLine[i].fStartPointX);

        a_ptStitchLine->tStitchLine[i].fVx = (FLOAT32) cos(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fVy = (FLOAT32) sin(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
    }
    a_ptStitchLine->fStitchRegionAngel[2] = (FLOAT32) (2 * a_ptAVMCfg->fStitchAngleRange * alPI / 180);

    // set L9~11
    for(i = 9; i < 12 ; i++)
    {
#if MM_DOMAIN == 1
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptAVMCfg->atStitchLineStart[3].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptAVMCfg->atStitchLineStart[3].lY;
#else
        a_ptStitchLine->tStitchLine[i].fStartPointX = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_BackRight[0].lX;
        a_ptStitchLine->tStitchLine[i].fStartPointY = (FLOAT32) a_ptalAVM2DParams->atStitchPoint_BackRight[0].lY;
#endif
    }
    a_ptStitchLine->tStitchLine[11].fdegree = a_ptAVMCfg->afStitchLineAngle[3];
    a_ptStitchLine->tStitchLine[9].fdegree = a_ptStitchLine->tStitchLine[11].fdegree + a_ptAVMCfg->fStitchAngleRange;
    a_ptStitchLine->tStitchLine[10].fdegree = a_ptStitchLine->tStitchLine[11].fdegree - a_ptAVMCfg->fStitchAngleRange;
    for(i = 9; i < 12 ; i++)
    {
        a_ptStitchLine->tStitchLine[i].fRatio = (FLOAT32)tan(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fOffset = (FLOAT32)(a_ptStitchLine->tStitchLine[i].fStartPointY - a_ptStitchLine->tStitchLine[i].fRatio*a_ptStitchLine->tStitchLine[i].fStartPointX);

        a_ptStitchLine->tStitchLine[i].fVx = (FLOAT32) cos(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
        a_ptStitchLine->tStitchLine[i].fVy = (FLOAT32) sin(a_ptStitchLine->tStitchLine[i].fdegree * alPI / 180);
    }
    a_ptStitchLine->fStitchRegionAngel[3] = (FLOAT32) (2 * a_ptAVMCfg->fStitchAngleRange * alPI / 180);

}


/**
  *  @}
  */
