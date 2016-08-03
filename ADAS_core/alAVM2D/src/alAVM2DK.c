
#include "alAVM2DK.h"
#include "basedef.h"
#include "alLUT_v2.h"
#include <math.h>       /* sqrt */
#include <assert.h>
#include "alAVM2DKOverlaping.h"
#include "CommonK.h"
#include "alCameraInfo.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

// Parameters for alAVM2D Location Weighting LUT
#define SIZE_WEIGHTING_CURVE_LUT		512
#define MAX_CURVE_VALUE		            255
static const UINT8 g_aucWeightingCurveLUT[SIZE_WEIGHTING_CURVE_LUT*4] = 
{	// row 1 = view0, row 2 = view1, ...
0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,8,9,9,10,10,10,11,11,12,12,13,13,13,14,14,15,15,16,16,17,17,18,18,19,20,20,21,21,22,23,23,24,24,25,26,26,27,28,28,29,30,30,31,32,32,33,34,35,35,36,37,38,38,39,40,41,42,42,43,44,45,46,47,48,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,80,81,82,83,84,85,86,88,89,90,91,92,94,95,96,97,99,100,101,102,104,105,106,108,109,110,112,113,114,116,117,118,120,121,123,124,125,127,128,130,131,132,134,135,137,138,140,141,143,144,146,147,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,7,7,7,8,8,8,9,9,10,10,10,11,11,12,12,13,13,13,14,14,15,15,16,16,17,17,18,18,19,20,20,21,21,22,23,23,24,24,25,26,26,27,28,28,29,30,30,31,32,32,33,34,35,35,36,37,38,38,39,40,41,42,42,43,44,45,46,47,48,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,80,81,82,83,84,85,86,88,89,90,91,92,94,95,96,97,99,100,101,102,104,105,106,108,109,110,112,113,114,116,117,118,120,121,123,124,125,127,128,130,131,132,134,135,137,138,140,141,143,144,146,147,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,
20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,25,25,26,26,26,26,26,27,27,27,27,28,28,28,28,29,29,29,30,30,30,30,31,31,31,32,32,32,32,33,33,33,34,34,34,35,35,35,36,36,37,37,37,38,38,38,39,39,40,40,40,41,41,42,42,42,43,43,44,44,45,45,46,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,58,58,59,59,60,60,61,61,62,63,63,64,64,65,66,66,67,67,68,69,69,70,71,71,72,72,73,74,74,75,76,76,77,78,78,79,80,81,81,82,83,83,84,85,86,86,87,88,88,89,90,91,91,92,93,94,94,95,96,97,98,98,99,100,101,102,102,103,104,105,106,107,107,108,109,110,111,112,112,113,114,115,116,117,118,119,119,120,121,122,123,124,125,126,127,128,129,130,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,
40,40,40,40,40,40,40,40,40,41,41,41,41,41,41,42,42,42,42,43,43,43,43,44,44,44,45,45,45,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,54,54,55,55,56,57,58,58,59,60,60,61,62,63,64,64,65,66,67,68,69,70,70,71,72,73,74,75,76,77,78,79,80,82,83,84,85,86,87,88,89,91,92,93,94,95,97,98,99,101,102,103,105,106,107,109,110,111,113,114,116,117,119,120,122,123,125,126,128,129,131,133,134,136,137,139,141,142,144,146,148,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150
};

 
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alAVM2D_InitializeBuffer(alLUT_v2_Def * a_ptalAVM2D_LUT)
{
    if(a_ptalAVM2D_LUT != NULL)
    {
    	memset(a_ptalAVM2D_LUT, 0x0, sizeof(alLUT_v2_Def));
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void alAVM2D_FreeBuffer(alLUT_v2_Def * a_ptalAVM2D_LUT, alPartLUT_v2_Def ** a_ptalAVM2D_PartLUT)
{
    if(a_ptalAVM2D_LUT != NULL)
    {
        if(a_ptalAVM2D_LUT->pullTable != NULL)
            free(a_ptalAVM2D_LUT->pullTable);
    	memset(a_ptalAVM2D_LUT, 0x0, sizeof(alLUT_v2_Def));
    }

    /*if(a_ptalAVM2D_PartLUT != NULL)
    {
	    if((*a_ptalAVM2D_PartLUT)->lut_data != NULL) 
            free((*a_ptalAVM2D_PartLUT)->lut_data);

        free(*a_ptalAVM2D_PartLUT);
        (*a_ptalAVM2D_PartLUT) = NULL;
    }*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void alAVM2D_InitialByConfigData(alAVM2D_Cfg * a_ptalAVM2DCfg, alCOMMONK_CommonCfg *a_ptCommonCfg, alAVM2D_Params *a_ptalAVM2DParams)
{
    FLOAT64 eVectorX = 0, eVectorY = 0, eTime[3];

    a_ptalAVM2DParams->tBirdViewAreaSize.lY = a_ptalAVM2DCfg->tDestImageBufferSize.lY;
	a_ptalAVM2DParams->fMMPP = alROUND(((FLOAT32)(a_ptCommonCfg->ulCarLength + a_ptalAVM2DCfg->ulBVMaxDistance * 2) / a_ptalAVM2DParams->tBirdViewAreaSize.lY) * 1000) / 1000.0f; //Calculate the minimeter per pixel value, RealHeight/PixelHeight.
	a_ptalAVM2DParams->tBirdViewAreaSize.lX = alROUND_EVEN( a_ptalAVM2DParams->tBirdViewAreaSize.lY * (a_ptCommonCfg->ulCarWidth + a_ptalAVM2DCfg->ulBVMaxDistance * 2) / (a_ptCommonCfg->ulCarLength + a_ptalAVM2DCfg->ulBVMaxDistance * 2));  //birdview width = alROUND_EVEN ( displayWidth * (carWidth + viewRange*2) / (carLength + viewRange*2) * ratio)

#if GAE_LUT_GEN == 1
    assert(a_ptalAVM2DParams->tBirdViewAreaSize.lX + a_ptalAVM2DCfg->tBVGAE_ROIPixelNumber.lX <= a_ptalAVM2DCfg->tDestImageBufferSize.lX);
#else
    assert(a_ptalAVM2DParams->tBirdViewAreaSize.lX <= a_ptalAVM2DCfg->tDestImageBufferSize.lX);
#endif
    assert(a_ptalAVM2DCfg->tBVGAE_ROIPixelNumber.lY*8 <= a_ptalAVM2DCfg->tDestImageBufferSize.lY);

    a_ptalAVM2DParams->tBirdViewStartPoint.lX = alROUND_EVEN((a_ptalAVM2DCfg->tDestImageBufferSize.lX - a_ptalAVM2DParams->tBirdViewAreaSize.lX) / 2); //The BV position paramters are center-aligned, and the start point should be even for YUV422.
    a_ptalAVM2DParams->tBirdViewStartPoint.lY = alROUND((a_ptalAVM2DCfg->tDestImageBufferSize.lY - a_ptalAVM2DParams->tBirdViewAreaSize.lY) / 2);

    // Generate stitch line pixel coordinate /// 

    // 0 NEAR
    a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lX = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[0].lX / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1));
    a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lY = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[0].lY / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1));
   
    // 1 NEAR
    a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lX = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[1].lX / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1));
    a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lY = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[1].lY / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1));

    // 2 NEAR
    a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lX = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[2].lX / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1));
    a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lY = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[2].lY / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1));

     // 3 NEAR
    a_ptalAVM2DParams->atStitchPoint_BackRight[0].lX = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[3].lX / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1));
    a_ptalAVM2DParams->atStitchPoint_BackRight[0].lY = (INT32)(a_ptalAVM2DCfg->atStitchLineStart[3].lY / a_ptalAVM2DParams->fMMPP + (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1));
    
    // 0 FAR
    eVectorX = cos(a_ptalAVM2DCfg->afStitchLineAngle[0] * alPI / 180);
    eVectorY = sin(a_ptalAVM2DCfg->afStitchLineAngle[0] * alPI / 180); 
    eTime[0] = (a_ptalAVM2DParams->tBirdViewStartPoint.lX - a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lX) / eVectorX;
    eTime[1] = (a_ptalAVM2DParams->tBirdViewStartPoint.lY - a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lY) / eVectorY;
    eTime[2] = (eTime[1] > eTime[0]) ? eTime[0] : eTime[1];
    a_ptalAVM2DParams->atStitchPoint_FrontLeft[1].lX = (INT32)(a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lX + eVectorX*eTime[2]);
    a_ptalAVM2DParams->atStitchPoint_FrontLeft[1].lY = (INT32)(a_ptalAVM2DParams->atStitchPoint_FrontLeft[0].lY + eVectorY*eTime[2]);

    // 1 FAR
    eVectorX = cos(a_ptalAVM2DCfg->afStitchLineAngle[1] * alPI / 180);
    eVectorY = sin(a_ptalAVM2DCfg->afStitchLineAngle[1] * alPI / 180); 
    eTime[0] = (a_ptalAVM2DParams->tBirdViewStartPoint.lX + a_ptalAVM2DParams->tBirdViewAreaSize.lX - a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lX) / eVectorX;
    eTime[1] = (a_ptalAVM2DParams->tBirdViewStartPoint.lY - a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lY) / eVectorY;
    eTime[2] = (eTime[1] > eTime[0]) ? eTime[0] : eTime[1];
    a_ptalAVM2DParams->atStitchPoint_FrontRight[1].lX = (INT32)(a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lX + eVectorX*eTime[2]);
    a_ptalAVM2DParams->atStitchPoint_FrontRight[1].lY = (INT32)(a_ptalAVM2DParams->atStitchPoint_FrontRight[0].lY + eVectorY*eTime[2]);

    // 2 FAR
    eVectorX = cos(a_ptalAVM2DCfg->afStitchLineAngle[2] * alPI / 180);
    eVectorY = sin(a_ptalAVM2DCfg->afStitchLineAngle[2] * alPI / 180); 
    eTime[0] = (a_ptalAVM2DParams->tBirdViewStartPoint.lX - a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lX) / eVectorX;
    eTime[1] = (a_ptalAVM2DParams->tBirdViewStartPoint.lY + a_ptalAVM2DParams->tBirdViewAreaSize.lY - a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lY) / eVectorY;
    eTime[2] = (eTime[1] > eTime[0]) ? eTime[0] : eTime[1];
    a_ptalAVM2DParams->atStitchPoint_BackLeft[1].lX = (INT32)(a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lX + eVectorX*eTime[2]);
    a_ptalAVM2DParams->atStitchPoint_BackLeft[1].lY = (INT32)(a_ptalAVM2DParams->atStitchPoint_BackLeft[0].lY + eVectorY*eTime[2]);

    // 3 FAR
    eVectorX = cos(a_ptalAVM2DCfg->afStitchLineAngle[3] * alPI / 180);
    eVectorY = sin(a_ptalAVM2DCfg->afStitchLineAngle[3] * alPI / 180); 
    eTime[0] = (a_ptalAVM2DParams->tBirdViewStartPoint.lX + a_ptalAVM2DParams->tBirdViewAreaSize.lX - a_ptalAVM2DParams->atStitchPoint_BackRight[0].lX) / eVectorX;
    eTime[1] = (a_ptalAVM2DParams->tBirdViewStartPoint.lY + a_ptalAVM2DParams->tBirdViewAreaSize.lY - a_ptalAVM2DParams->atStitchPoint_BackRight[0].lY) / eVectorY;
    eTime[2] = (eTime[1] > eTime[0]) ? eTime[0] : eTime[1];
    a_ptalAVM2DParams->atStitchPoint_BackRight[1].lX = (INT32)(a_ptalAVM2DParams->atStitchPoint_BackRight[0].lX + eVectorX*eTime[2]);
    a_ptalAVM2DParams->atStitchPoint_BackRight[1].lY = (INT32)(a_ptalAVM2DParams->atStitchPoint_BackRight[0].lY + eVectorY*eTime[2]);
    ///generate stitch line pixel coordinate ///
    
	//The Center Car Pic Position, the car pic include blind area. => fix by chinson (2014/10/22): 修正計算公式
    a_ptalAVM2DParams->tCarPicCornerPos.lX = (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1) - alROUND_EVEN( ((a_ptCommonCfg->ulCarWidth>>1) + a_ptalAVM2DCfg->ulBVBlindDistanceLeft) / a_ptalAVM2DParams->fMMPP );
	a_ptalAVM2DParams->tCarPicCornerPos.lY = (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1) - alROUND( ((a_ptCommonCfg->ulCarLength>>1) + a_ptalAVM2DCfg->ulBVBlindDistanceFront) / a_ptalAVM2DParams->fMMPP );
	a_ptalAVM2DParams->tCarPicAreaSize.lX = (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1) + alROUND_EVEN( ((a_ptCommonCfg->ulCarWidth>>1) + a_ptalAVM2DCfg->ulBVBlindDistanceRight) / a_ptalAVM2DParams->fMMPP ) - a_ptalAVM2DParams->tCarPicCornerPos.lX;
	a_ptalAVM2DParams->tCarPicAreaSize.lY = (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1) + alROUND( ((a_ptCommonCfg->ulCarLength>>1) + a_ptalAVM2DCfg->ulBVBlindDistanceBack) / a_ptalAVM2DParams->fMMPP ) - a_ptalAVM2DParams->tCarPicCornerPos.lY;


    a_ptalAVM2DParams->tCarTopLeft.lX = (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1) - alROUND_EVEN((a_ptCommonCfg->ulCarWidth>>1) / a_ptalAVM2DParams->fMMPP );
	a_ptalAVM2DParams->tCarTopLeft.lY = (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1) - alROUND( (a_ptCommonCfg->ulCarLength>>1) / a_ptalAVM2DParams->fMMPP );
	a_ptalAVM2DParams->tCarBottomRight.lX = (a_ptalAVM2DCfg->tDestImageBufferSize.lX>>1) + alROUND_EVEN( (a_ptCommonCfg->ulCarWidth>>1) / a_ptalAVM2DParams->fMMPP );
	a_ptalAVM2DParams->tCarBottomRight.lY = (a_ptalAVM2DCfg->tDestImageBufferSize.lY>>1) + alROUND( (a_ptCommonCfg->ulCarLength>>1) / a_ptalAVM2DParams->fMMPP );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
INT8 alAVM2D_BlindRegionDecide(
                        INT32 a_lX,
                        INT32 a_lY,
                        alAVM2D_Params *a_ptalAVM2DParams
                        )
{
    // chinson - 20141027: 將 <= 改為 < ，以修正 Car Pic 寬度與黑區寬度的落差
    if(a_lX >= a_ptalAVM2DParams->tCarPicCornerPos.lX && a_lX < a_ptalAVM2DParams->tCarPicCornerPos.lX+a_ptalAVM2DParams->tCarPicAreaSize.lX &&
       a_lY >= a_ptalAVM2DParams->tCarPicCornerPos.lY && a_lY < a_ptalAVM2DParams->tCarPicCornerPos.lY+a_ptalAVM2DParams->tCarPicAreaSize.lY)
    { // 黑區
        return 0;
    }
    else
    { // 非黑區
        return 1;
    }
}


UINT32 alAVM2D_QurryLUTSize(
    alAVM2D_Cfg * a_ptAVMCfg,
    alAVM2D_Params *a_ptalAVM2DParams
    )
{
    UINT32 ulSize = 0;
    alPointINT32 tlLUT_Size = { 0 };
    tlLUT_Size = a_ptalAVM2DParams->tBirdViewAreaSize;
#if GAE_LUT_GEN == 1
    tlLUT_Size.lX += a_ptAVMCfg->tBVGAE_ROIPixelNumber.lX;
#endif
    ulSize = (UINT32)(tlLUT_Size.lX * tlLUT_Size.lY * sizeof(UINT64));

    return ulSize;
}

void alAVM2D_GenerateLUT2DBirdView(   alAVM2D_Cfg *a_ptalAVM2DCfg,
                                    alAVM2D_Params *a_ptalAVM2DParams,
                                    alFM_v2_1_Model *a_ptFisheyeModel,
                                    FLOAT64 a_aeM33_BV_RC_Left[2][9],
                                    FLOAT64 a_aeM33_BV_RC_Right[2][9],
                                    FLOAT64 a_aeM33_BV_RC_Front[2][9],
                                    FLOAT64 a_aeM33_BV_RC_Back[2][9],
                                    alLUT_v2_Def * a_ptalAVM2D_LUT
                                    )
{
    UINT8 a_ucViewIndex1, a_ucViewIndex2;
    UINT8 ucCameraIndex = 0;
    INT8 cBlindFlag = 0;
    INT32 i = 0, lX = 0, lY = 0;
    FLOAT64 eBVX_Pixel, eBVY_Pixel;
    UINT32 ulPixelIndex = 0;
    UINT32 ulVCCenterX, ulVCCenterY;

    FLOAT64 eUndistX, eUndistY;
    FLOAT64 eDestX1, eDestY1;
    FLOAT64 eDestX2, eDestY2;
    FLOAT64 eBVPosX, eBVPosY;
    register INT32 lDestIntX1, lDestIntY1;
    register INT32 lDestDecX1, lDestDecY1;
    register INT32 lDestIntX2, lDestIntY2;
    register INT32 lDestDecX2, lDestDecY2;
    BOOL a_bView1Enabled = 0, a_bView2Enabled = 0;
    FLOAT32 afWeighting[2];
    UINT8 aucViewIndex[2], ucViewIndexBuff = 0, aucView1Weighting = 0;
    alAVM2D_StitchLineCfg tStitchLineCfg_2D;

    FLOAT64* paeM33[4];
    paeM33[alCAMERAINFO_BV_LEFT] = a_aeM33_BV_RC_Left[0];
    paeM33[alCAMERAINFO_BV_RIGHT] = a_aeM33_BV_RC_Right[0];
    paeM33[alCAMERAINFO_BV_FRONT] = a_aeM33_BV_RC_Front[0];
    paeM33[alCAMERAINFO_BV_BACK] = a_aeM33_BV_RC_Back[0];
    
    alAVM2D_SetStitchLineInfo(a_ptalAVM2DParams, a_ptalAVM2DCfg, &tStitchLineCfg_2D);

    a_ptalAVM2D_LUT->tDestAreaSize = a_ptalAVM2DParams->tBirdViewAreaSize;
	a_ptalAVM2D_LUT->tDestStartPoint.lX = a_ptalAVM2DCfg->tDestStartPoint.lX;
	a_ptalAVM2D_LUT->tDestStartPoint.lY = a_ptalAVM2DCfg->tDestStartPoint.lY;
	a_ptalAVM2D_LUT->tDestImageBufferSize.lX = a_ptalAVM2DCfg->tDestImageBufferSize.lX;
	a_ptalAVM2D_LUT->tDestImageBufferSize.lY = a_ptalAVM2DCfg->tDestImageBufferSize.lY;
    
    for(ucCameraIndex = 0; ucCameraIndex < 4; ucCameraIndex++)
    {
        a_ptalAVM2D_LUT->atSrcImageSize[ucCameraIndex].lX = a_ptFisheyeModel[ucCameraIndex].uwSrcWidth;
        a_ptalAVM2D_LUT->atSrcImageSize[ucCameraIndex].lY = a_ptFisheyeModel[ucCameraIndex].uwSrcHeight;
    }

#if GAE_LUT_GEN == 1
    a_ptalAVM2D_LUT->tDestAreaSize.lX += a_ptalAVM2DCfg->tBVGAE_ROIPixelNumber.lX;
    a_ptalAVM2D_LUT->ulLUTDataSize = (a_ptalAVM2D_LUT->tDestAreaSize.lX) * a_ptalAVM2D_LUT->tDestAreaSize.lY * sizeof(UINT64);
#else
    a_ptalAVM2D_LUT->ulLUTDataSize = a_ptalAVM2D_LUT->tDestAreaSize.lX * a_ptalAVM2D_LUT->tDestAreaSize.lY * sizeof(UINT64);
#endif
    if (a_ptalAVM2D_LUT->pullTable == NULL)
    { // 如果外部沒配置記憶體才配置
        a_ptalAVM2D_LUT->pullTable = (UINT64*)malloc(a_ptalAVM2D_LUT->ulLUTDataSize);
    }

    {
        memset(a_ptalAVM2D_LUT->pullTable, 0, a_ptalAVM2D_LUT->ulLUTDataSize);
        ulPixelIndex = 0;
        ulVCCenterX = (a_ptalAVM2DCfg->tDestImageBufferSize.lX >> 1);
        ulVCCenterY = (a_ptalAVM2DCfg->tDestImageBufferSize.lY >> 1);

        //eVC_Focal = 2500;
        for(lY = 0; lY < a_ptalAVM2DParams->tBirdViewAreaSize.lY; lY++)
        {
#if GAE_LUT_GEN == 1
            ulPixelIndex = lY * a_ptalAVM2D_LUT->tDestAreaSize.lX;
#else
            ulPixelIndex = lY * a_ptalAVM2DParams->tBirdViewAreaSize.lX;
#endif
            for(lX = 0; lX < a_ptalAVM2DParams->tBirdViewAreaSize.lX; lX++, ulPixelIndex++)
            {   

				if (lX == 160 && lY == 45) // for test
                {
                    lX = lX;
                }

                eBVX_Pixel = lX + a_ptalAVM2DParams->tBirdViewStartPoint.lX;
                eBVY_Pixel = lY + a_ptalAVM2DParams->tBirdViewStartPoint.lY;
                
                // 判斷是否為黑區
                cBlindFlag = alAVM2D_BlindRegionDecide((INT32)eBVX_Pixel, (INT32)eBVY_Pixel, a_ptalAVM2DParams);

                if(cBlindFlag)
                {   // 非黑區

                eBVPosX = (eBVX_Pixel - ulVCCenterX) * a_ptalAVM2DParams->fMMPP;
                eBVPosY = (eBVY_Pixel - ulVCCenterY) * a_ptalAVM2DParams->fMMPP;
				
				if(a_ptalAVM2DCfg->ucStitchLineType)
				{	// new overlap (mm domain)
					alAVM2D_OverlapWeightCal(a_ptalAVM2DCfg, eBVPosX, eBVPosY, &tStitchLineCfg_2D, afWeighting, aucViewIndex);
				}
				else
				{	// old overlap (pixel domain)
					alAVM2D_OverlapWeightCal(a_ptalAVM2DCfg, eBVX_Pixel, eBVY_Pixel, &tStitchLineCfg_2D, afWeighting, aucViewIndex);
				}

                a_ucViewIndex1 = aucViewIndex[0];
                a_ucViewIndex2 = aucViewIndex[1];
	
				if(afWeighting[0] == 0 &&  afWeighting[1] == 1)
				{ // 如果a_ucViewIndex1 權重為0 則兩view互換 for FW team 2014 12 23	
					ucViewIndexBuff = a_ucViewIndex1;
					a_ucViewIndex1 = a_ucViewIndex2;
					a_ucViewIndex2 = ucViewIndexBuff;
					afWeighting[0] = 1;
					afWeighting[1] = 0;
				}

                aucView1Weighting = (UINT8)(afWeighting[0] * alLUT_v2_AND_WEIGHT);

                if(a_ucViewIndex1 != 255)
                {
                    COMMONK_PerformCoordinatesTransform(paeM33[a_ucViewIndex1], eBVX_Pixel, eBVY_Pixel, &eUndistX, &eUndistY);
                    alFM_v2_1_Undistorted2Distorted_PlanarPixel(a_ptFisheyeModel + a_ucViewIndex1, eUndistX, eUndistY, &eDestX1, &eDestY1);

                    //取整數位
                    lDestIntX1 = (INT32)(eDestX1);
                    lDestIntY1 = (INT32)(eDestY1);

                    //取小數位，以3bit儲存
                    lDestDecX1 = (INT32)((eDestX1 - lDestIntX1)*8);
                    lDestDecY1 = (INT32)((eDestY1 - lDestIntY1)*8);

                    assert(lDestDecX1 < (1<<3) && lDestDecY1 < (1<<3));

                    // 避免超出原影像邊界
                    if(lDestIntX1 > 0 && lDestIntY1 > 0 && lDestIntX1 < a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex1].lX - 1 && lDestIntY1 < a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex1].lY - 1)
                    {
                        a_ptalAVM2D_LUT->pullTable[ulPixelIndex] = (a_ucViewIndex1<<alLUT_v2_SHIFT_CAM_1) + ((lDestIntY1 * a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex1].lX + lDestIntX1)<<alLUT_v2_SHIFT_OFFSET_1) + (lDestDecX1<<alLUT_v2_SHIFT_DECX_1) + (lDestDecY1<<alLUT_v2_SHIFT_DECY_1);
                        a_bView1Enabled = TRUE;
                    }
                    else
                    {
                        a_bView1Enabled = FALSE;
                    }
                }
                else
                {
                    a_bView1Enabled = FALSE;
                }
                    
                if(a_ucViewIndex2 != 255)
                {
                    COMMONK_PerformCoordinatesTransform(paeM33[a_ucViewIndex2], eBVX_Pixel, eBVY_Pixel, &eUndistX, &eUndistY);
                    alFM_v2_1_Undistorted2Distorted_PlanarPixel(a_ptFisheyeModel + a_ucViewIndex2, eUndistX, eUndistY, &eDestX2, &eDestY2);

                    //取整數位
                    lDestIntX2 = (INT32)(eDestX2);
                    lDestIntY2 = (INT32)(eDestY2);

                    //取小數位，以3bit儲存
                    lDestDecX2 = (INT32)((eDestX2 - lDestIntX2)*8);
                    lDestDecY2 = (INT32)((eDestY2 - lDestIntY2)*8);

                    assert(lDestDecX2 < (1<<3) && lDestDecY2 < (1<<3));

                    // 避免超出原影像邊界
                    if(lDestIntX2 > 0 && lDestIntY2 > 0 && lDestIntX2 < a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex2].lX - 1 && lDestIntY2 < a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex2].lY - 1)
                    {
                        a_ptalAVM2D_LUT->pullTable[ulPixelIndex] += ((UINT64)a_ucViewIndex2<<alLUT_v2_SHIFT_CAM_2) 
                            + ((UINT64)(lDestIntY2 * a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex2].lX + lDestIntX2)<<alLUT_v2_SHIFT_OFFSET_2) 
                            + ((UINT64)lDestDecX2<<alLUT_v2_SHIFT_DECX_2) + ((UINT64)lDestDecY2<<alLUT_v2_SHIFT_DECY_2);
                        a_bView2Enabled = TRUE;
                    }
                    else
                    {
                        a_bView2Enabled = FALSE;
                    }
                }
                else
                {
                    a_bView2Enabled = FALSE;
                }

                }
                else
                {
                    a_bView1Enabled = FALSE;
                    a_bView2Enabled = FALSE;
                }
        

                if(a_bView1Enabled && a_bView2Enabled)
                {
                    a_ptalAVM2D_LUT->pullTable[ulPixelIndex] += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(aucView1Weighting)<<alLUT_v2_SHIFT_WEIGHT);
                }
                else if(a_bView1Enabled && !a_bView2Enabled)
                {
                    a_ptalAVM2D_LUT->pullTable[ulPixelIndex] += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(alLUT_v2_AND_WEIGHT)<<alLUT_v2_SHIFT_WEIGHT);
                }
                else if(!a_bView1Enabled && a_bView2Enabled)
                {
                    a_ptalAVM2D_LUT->pullTable[ulPixelIndex] += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(0)<<alLUT_v2_SHIFT_WEIGHT);
                }
                else 
                {
                    a_ptalAVM2D_LUT->pullTable[ulPixelIndex] += ((UINT64)1<<alLUT_v2_SHIFT_ENABLE);
                }

            }

        }
    }
#if GAE_LUT_GEN == 1
    GeneratealAVM2D_GAELUT(
      a_ptalAVM2DCfg, 
      a_ptalAVM2DParams,
      a_ptFisheyeModel, 
      a_ptalAVM2D_LUT,
      a_aeM33_BV_RC_Left,
      a_aeM33_BV_RC_Right,
      a_aeM33_BV_RC_Front,
      a_aeM33_BV_RC_Back
    );    
#endif
}

void BV2SrcImage(FLOAT64 a_eSX, FLOAT64 a_eSY, UINT8 a_ucLensIndex, FLOAT64 *a_eDX, FLOAT64 *a_eDY, FLOAT64 *peM33, alFM_v2_1_Model a_ptCameraFisheyeModel[])
{
	FLOAT64 eDis_X, eDis_Y = 0;
    COMMONK_PerformCoordinatesTransform(peM33, a_eSX, a_eSY, &eDis_X, &eDis_Y);
	switch(a_ucLensIndex)
	{
	case 0: // left lens 
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_LEFT], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
    case 1: // right lens
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_RIGHT], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
    case 2: // front lens	
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_FRONT], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
	case 3: // back lens
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_BACK], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
	default:
		DEBUG_Printf("BV2SrcImage index error~~~~\n");
	break;
	}
}

#if 0 // 有用到eagleK的模組  先拿掉
void Dest2Src(FLOAT64 a_eSX, FLOAT64 a_eSY, UINT8 a_ucLensIndex, FLOAT64 *a_eDX, FLOAT64 *a_eDY, EAGLEK3_M33_Set * pM33, alFM_v2_1_Model a_ptCameraFisheyeModel[])
{
	FLOAT64 eDis_X, eDis_Y = 0;
	switch(a_ucLensIndex)
	{
	case 0: // left lens
        COMMONK_PerformCoordinatesTransform(pM33->aeBVL[0], a_eSX, a_eSY, &eDis_X, &eDis_Y);
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_LEFT], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
    case 1: // right lens
        COMMONK_PerformCoordinatesTransform(pM33->aeBVR[0], a_eSX, a_eSY, &eDis_X, &eDis_Y);
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_RIGHT], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
    case 2: // front lens
        COMMONK_PerformCoordinatesTransform(pM33->aeBVF[0], a_eSX, a_eSY, &eDis_X, &eDis_Y);
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_FRONT], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
	case 3: // back lens
        COMMONK_PerformCoordinatesTransform(pM33->aeBVB[0], a_eSX, a_eSY, &eDis_X, &eDis_Y);
        alFM_v2_1_Undistorted2Distorted_PlanarPixel(&a_ptCameraFisheyeModel[alCAMERAINFO_BV_BACK], eDis_X, eDis_Y, a_eDX, a_eDY);
	break;
	default:
		DEBUG_Printf("W2I index error~~~~\n");
	break;
	}
}
#endif

UINT64  PACK_LUTDATA_alAVM2D_GAE(FLOAT64 a_eDisX, FLOAT64 a_eDisY, UINT8 a_ucViewIndex, alLUT_v2_Def *a_ptalAVM2D_LUT)
{  // 這裡只有一個view 所以塞到view 1 weighting 設1 (32)
    UINT64 ullLUTValue;
    INT32 lDestIntX1, lDestIntY1, lDestDecX1, lDestDecY1;
    
    //取整數位
    lDestIntX1 = (INT32)(a_eDisX);
    lDestIntY1 = (INT32)(a_eDisY);

    //取小數位，以3bit儲存
    lDestDecX1 = (INT32)((a_eDisX - lDestIntX1)*8);
    lDestDecY1 = (INT32)((a_eDisY - lDestIntY1)*8);

    assert(lDestDecX1 < (1<<3) && lDestDecY1 < (1<<3));

    // ViewIndex, Int, Dec
    ullLUTValue = (a_ucViewIndex<<alLUT_v2_SHIFT_CAM_1) + ((lDestIntY1 * a_ptalAVM2D_LUT->atSrcImageSize[a_ucViewIndex].lX + lDestIntX1)<<alLUT_v2_SHIFT_OFFSET_1) + (lDestDecX1<<alLUT_v2_SHIFT_DECX_1) + (lDestDecY1<<alLUT_v2_SHIFT_DECY_1);

    // Weighting, Pixel Enable
    ullLUTValue += ((UINT64)0<<alLUT_v2_SHIFT_ENABLE) + ((UINT64)(alLUT_v2_AND_WEIGHT)<<alLUT_v2_SHIFT_WEIGHT);

    return ullLUTValue;
}

void GeneratealAVM2D_GAELUT(alAVM2D_Cfg * a_ptalAVM2DCfg, 
                          alAVM2D_Params * a_ptalAVM2DParams,
                          alFM_v2_1_Model a_ptCameraFisheyeModel[],
                          alLUT_v2_Def * a_ptalAVM2D_LUT,
                          FLOAT64 a_aeM33_BV_RC_Left[2][9],
                          FLOAT64 a_aeM33_BV_RC_Right[2][9],
                          FLOAT64 a_aeM33_BV_RC_Front[2][9],
                          FLOAT64 a_aeM33_BV_RC_Back[2][9]
                          )
{
    alPointINT32 alROIPosition[4];
    FLOAT64 eSX,eSY, eDisX, eDisY;
    UINT64 ullLUTValue;
    UINT32 ulYindex, ulXindex, i, ulWidth,ulHeight;
    UINT32 ulLUTIndex = 0;
    UINT8 ucROIWidth, ucROIHeight;

    ucROIWidth = a_ptalAVM2DCfg->tBVGAE_ROIPixelNumber.lX;
    ucROIHeight = a_ptalAVM2DCfg->tBVGAE_ROIPixelNumber.lY;
    
    alROIPosition[0].lX = a_ptalAVM2DParams->tCarPicCornerPos.lX - ucROIWidth + a_ptalAVM2DCfg->tBVGAE_ROIFrontLeftOffse2CarPict.lX;
    alROIPosition[0].lY = a_ptalAVM2DParams->tCarPicCornerPos.lY - ucROIHeight + a_ptalAVM2DCfg->tBVGAE_ROIFrontLeftOffse2CarPict.lY;

    alROIPosition[1].lX = a_ptalAVM2DParams->tCarPicCornerPos.lX  + a_ptalAVM2DCfg->tBVGAE_ROIFrontRightOffse2CarPict.lX + a_ptalAVM2DParams->tCarPicAreaSize.lX;
    alROIPosition[1].lY = a_ptalAVM2DParams->tCarPicCornerPos.lY - ucROIHeight + a_ptalAVM2DCfg->tBVGAE_ROIFrontRightOffse2CarPict.lY;

    alROIPosition[2].lX = a_ptalAVM2DParams->tCarPicCornerPos.lX - ucROIWidth + a_ptalAVM2DCfg->tBVGAE_ROIRearLeftOffse2CarPict.lX;
    alROIPosition[2].lY = a_ptalAVM2DParams->tCarPicCornerPos.lY  + a_ptalAVM2DCfg->tBVGAE_ROIRearLeftOffse2CarPict.lY + a_ptalAVM2DParams->tCarPicAreaSize.lY;

    alROIPosition[3].lX = a_ptalAVM2DParams->tCarPicCornerPos.lX  + a_ptalAVM2DCfg->tBVGAE_ROIRearRightOffse2CarPict.lX + a_ptalAVM2DParams->tCarPicAreaSize.lX;
    alROIPosition[3].lY = a_ptalAVM2DParams->tCarPicCornerPos.lY  + a_ptalAVM2DCfg->tBVGAE_ROIRearRightOffse2CarPict.lY  + a_ptalAVM2DParams->tCarPicAreaSize.lY;
    
    for(i = 0 ; i < 4 ; i ++){
        for(ulYindex = 0 ; ulYindex < ucROIHeight ; ulYindex ++){
            for(ulXindex = 0 ; ulXindex < ucROIWidth  ; ulXindex ++){
                eSX = alROIPosition[i].lX + ulXindex;
                eSY = alROIPosition[i].lY + ulYindex;

#if GAE_LUT_GEN == 1
                ulWidth = ulXindex + a_ptalAVM2DParams->tBirdViewAreaSize.lX;
                ulHeight = ulYindex + ucROIHeight * (2 * i);
                ulLUTIndex = (a_ptalAVM2D_LUT->tDestAreaSize.lX)*ulHeight + ulWidth;
#else
                ulWidth = eSX - a_ptalAVM2DParams->tBirdViewStartPoint.lX;
                ulHeight = eSY - a_ptalAVM2DParams->tBirdViewStartPoint.lY;
                ulLUTIndex = a_ptalAVM2DParams->tBirdViewAreaSize.lX*ulHeight + ulWidth;
#endif

                switch(i)
                {
                case 0: // left front
                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_LEFT, &eDisX, &eDisY, a_aeM33_BV_RC_Left[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_LEFT, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                    
                    ulHeight  += ucROIHeight;
                    ulLUTIndex = (a_ptalAVM2D_LUT->tDestAreaSize.lX)*ulHeight + ulWidth;

                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_FRONT, &eDisX, &eDisY, a_aeM33_BV_RC_Front[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_FRONT, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                break;
                case 1: // right front
                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_LEFT, &eDisX, &eDisY, a_aeM33_BV_RC_Right[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_RIGHT, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                    
                    ulHeight  += ucROIHeight;
                    ulLUTIndex = (a_ptalAVM2D_LUT->tDestAreaSize.lX)*ulHeight + ulWidth;

                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_FRONT, &eDisX, &eDisY, a_aeM33_BV_RC_Front[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_FRONT, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue; 
                break;
                case 2: // left back
                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_LEFT, &eDisX, &eDisY, a_aeM33_BV_RC_Left[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_LEFT, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                    
                    ulHeight  += ucROIHeight;
                    ulLUTIndex = (a_ptalAVM2D_LUT->tDestAreaSize.lX)*ulHeight + ulWidth;


                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_BACK, &eDisX, &eDisY, a_aeM33_BV_RC_Back[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_BACK, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                break;
                case 3: // right back
                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_RIGHT, &eDisX, &eDisY, a_aeM33_BV_RC_Right[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_RIGHT, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                    
                    ulHeight  += ucROIHeight;
                    ulLUTIndex = (a_ptalAVM2D_LUT->tDestAreaSize.lX)*ulHeight + ulWidth;

                    BV2SrcImage(eSX, eSY, alCAMERAINFO_BV_BACK, &eDisX, &eDisY, a_aeM33_BV_RC_Back[0], a_ptCameraFisheyeModel);
                    ullLUTValue = PACK_LUTDATA_alAVM2D_GAE((int)eDisX,(int)eDisY,alCAMERAINFO_BV_BACK, a_ptalAVM2D_LUT);
                    a_ptalAVM2D_LUT->pullTable[ulLUTIndex] = ullLUTValue;
                break;
                default:
                    DEBUG_Printf("W2I index error~~~~\n");
                break;
                }
            }
        }
    }
}


////#define SIZE_WEIGHTING_CURVE_LUT		512
////#define MAX_CURVE_VALUE		255
////#define NO_VIEW_INDEX		7
////const UINT8 g_aucWeightingCurveLUT_alAVM2D[SIZE_WEIGHTING_CURVE_LUT*4] = 
////{
////0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,5,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,14,14,15,15,16,17,18,18,19,20,20,21,22,23,24,24,25,26,27,28,29,30,30,31,32,33,34,35,36,37,38,39,40,42,43,44,45,46,47,48,49,51,52,53,54,55,57,58,59,61,62,63,65,66,67,69,70,71,73,74,76,77,79,80,82,83,85,86,88,89,91,93,94,96,97,99,101,102,104,106,108,109,111,113,115,116,118,120,122,124,126,128,129,131,133,135,137,139,141,143,145,147,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,
////0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,5,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,14,14,15,15,16,17,18,18,19,20,20,21,22,23,24,24,25,26,27,28,29,30,30,31,32,33,34,35,36,37,38,39,40,42,43,44,45,46,47,48,49,51,52,53,54,55,57,58,59,61,62,63,65,66,67,69,70,71,73,74,76,77,79,80,82,83,85,86,88,89,91,93,94,96,97,99,101,102,104,106,108,109,111,113,115,116,118,120,122,124,126,128,129,131,133,135,137,139,141,143,145,147,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,
////20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,25,25,26,26,26,26,26,27,27,27,27,28,28,28,28,29,29,29,30,30,30,30,31,31,31,32,32,32,32,33,33,33,34,34,34,35,35,35,36,36,37,37,37,38,38,38,39,39,40,40,40,41,41,42,42,42,43,43,44,44,45,45,46,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,58,58,59,59,60,60,61,61,62,63,63,64,64,65,66,66,67,67,68,69,69,70,71,71,72,72,73,74,74,75,76,76,77,78,78,79,80,81,81,82,83,83,84,85,86,86,87,88,88,89,90,91,91,92,93,94,94,95,96,97,98,98,99,100,101,102,102,103,104,105,106,107,107,108,109,110,111,112,112,113,114,115,116,117,118,119,119,120,121,122,123,124,125,126,127,128,129,130,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,
////0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,11,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14,15,15,15,15,16,16,16,16,17,17,17,17,18,18,18,19,19,19,19,20,20,20,21,21,21,22,22,22,22,23,23,23,24,24,24,25,25,25,26,26,26,27,27,27,28,28,29,29,29,30,30,30,31,31,31,32,32,33,33,33,34,34,34,35,35,36,36,36,37,37,38,38,38,39,39,40,40,41,41,41,42,42,43,43,44,44,44,45,45,46,46,47,47,48,48,49,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,64,65,65,66,67,67,68,68,69,69,70,70,71,72,72,73,73,74,74,75,76,76,77,77,78,78,79,80,80,81,81,82,83,83,84,84,85,86,86,87,87,88,89,89,90,91,91,92,93,93,94,94,95,96,96,97,98,98,99,100,100,101,102,102,103,104,104,105,106,106,107,108,108,109,110,111,111,112,113,113,114,115,115,116,117,118,118,119,120,121,121,122,123,123,124,125,126,126,127,128,129,129,130,131,132,132,133,134,135,136,136,137,138,139,139,140,141,142,143,143,144,145,146,147,147,148,149,150,151,151,152,153,154,155,156,156,157,158,159,160,161,161,162,163,164,165,166,166,167,168,169,170,171,172,172,173,174,175,176,177,178,179,180,180,181,182,183,184,185,186,187,188,189,189,190,191,192,193,194,195,196,197,198,199,200,201,202,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
////};
void alAVM2D_GeneratealAVM2DLocWeightingTable(UINT8 *a_aucalAVM2DLocWeightingTable, alCOMMONK_CommonCfg * pCommonCfg, alCAMERAINFO_ExtrinsicParams a_atCameraDesignParameters[], alAVM2D_Cfg *a_ptalAVM2D_Cfg, alAVM2D_Params *a_ptalAVM2D_Params)
{
	INT32 x,y/*,count,i,j*/;//loop controlling
    INT32 view = 0, view2 = 0;
    INT32 alCameraPosX[4], alCameraPosY[4];
    INT32 lDis2Cam, lDis2Cam2, lLocLevel;
    UINT8 ulLUTValue, ulLUTValue1, ulLUTValue2;
    alPointINT32 tBVImgSize = { 0 };
	FLOAT32 afViewWeight[2] = {0.0};
	UINT8 aucViewIndex[2] = {0};
	//FLOAT32 fWorldX, fWorldY;

	// Stitch line information
	alAVM2D_StitchLineCfg tStitchLineCfg_2D;
    alAVM2D_SetStitchLineInfo(a_ptalAVM2D_Params, a_ptalAVM2D_Cfg, &tStitchLineCfg_2D);
	

    // Set 0 for location weighting LUT
	memset(a_aucalAVM2DLocWeightingTable, MAX_CURVE_VALUE, sizeof(UINT8)*a_ptalAVM2D_Params->tBirdViewAreaSize.lX*a_ptalAVM2D_Params->tBirdViewAreaSize.lY);
	
    tBVImgSize.lX = a_ptalAVM2D_Cfg->tDestImageBufferSize.lX;
    tBVImgSize.lY = a_ptalAVM2D_Cfg->tDestImageBufferSize.lY;


//pBirdViewParams->tCarPicCornerPos
    // Calculate for camera position
    alCameraPosX[0] = (INT32)((FLOAT32)a_atCameraDesignParameters[0].lCameraPosX / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lX / 2);
    alCameraPosX[1] = (INT32)((FLOAT32)a_atCameraDesignParameters[1].lCameraPosX / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lX / 2);
    alCameraPosX[2] = (INT32)((FLOAT32)a_atCameraDesignParameters[2].lCameraPosX / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lX / 2);
    alCameraPosX[3] = (INT32)((FLOAT32)a_atCameraDesignParameters[3].lCameraPosX / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lX / 2);
    alCameraPosY[0] = (INT32)((FLOAT32)a_atCameraDesignParameters[0].lCameraPosY / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lY / 2);
    alCameraPosY[1] = (INT32)((FLOAT32)a_atCameraDesignParameters[1].lCameraPosY / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lY / 2);
    alCameraPosY[2] = (INT32)((FLOAT32)a_atCameraDesignParameters[2].lCameraPosY / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lY / 2);
    alCameraPosY[3] = (INT32)((FLOAT32)a_atCameraDesignParameters[3].lCameraPosY / a_ptalAVM2D_Params->fMMPP + tBVImgSize.lY / 2);


    // Create LUT, For every pixel in BV.
    for (y = a_ptalAVM2D_Params->tBirdViewStartPoint.lY; y < a_ptalAVM2D_Params->tBirdViewStartPoint.lY + a_ptalAVM2D_Params->tBirdViewAreaSize.lY; y++)
    {
        for (x = a_ptalAVM2D_Params->tBirdViewStartPoint.lX; x < a_ptalAVM2D_Params->tBirdViewAreaSize.lX+a_ptalAVM2D_Params->tBirdViewStartPoint.lX; x++)
        {
			alAVM2D_OverlapWeightCal(a_ptalAVM2D_Cfg, x, y, &tStitchLineCfg_2D, afViewWeight, aucViewIndex);
			if (aucViewIndex[0]==255 && aucViewIndex[1]==255)		// Don't consider the pixel in Central Car Pic.
			{
				a_aucalAVM2DLocWeightingTable[x-a_ptalAVM2D_Params->tBirdViewStartPoint.lX+y*a_ptalAVM2D_Params->tBirdViewAreaSize.lX] = 0;
                continue;
			}
			else
			{
				if (aucViewIndex[1]==255)		// Non-overlapping view
				{
					// Calculate the distance between each pixel and the camera, then assign the LUT
					view = aucViewIndex[0];
					lDis2Cam = (INT32) sqrt( pow(x-alCameraPosX[view], 2) + pow(y-alCameraPosY[view], 2) );
					if (lDis2Cam < SIZE_WEIGHTING_CURVE_LUT)
						ulLUTValue = g_aucWeightingCurveLUT[lDis2Cam + view*SIZE_WEIGHTING_CURVE_LUT];
					else
					{
						lLocLevel = MAX_CURVE_VALUE;
						ulLUTValue = lLocLevel;
					}

					
				}
				else		// Overlapping view
				{
					view = aucViewIndex[0];
					view2 = aucViewIndex[1];
					lDis2Cam = (INT32) sqrt( pow(x-alCameraPosX[view], 2) + pow(y-alCameraPosY[view], 2) );
					lDis2Cam2 = (INT32) sqrt( pow(x-alCameraPosX[view2], 2) + pow(y-alCameraPosY[view2], 2) );
					if (lDis2Cam > SIZE_WEIGHTING_CURVE_LUT)
						ulLUTValue1 = MAX_CURVE_VALUE;
					else
						ulLUTValue1 = g_aucWeightingCurveLUT[lDis2Cam + view*SIZE_WEIGHTING_CURVE_LUT];

					if (lDis2Cam2 > SIZE_WEIGHTING_CURVE_LUT)
						ulLUTValue2 = MAX_CURVE_VALUE;
					else
						ulLUTValue2 = g_aucWeightingCurveLUT[lDis2Cam2 + view2*SIZE_WEIGHTING_CURVE_LUT];
					ulLUTValue = (UINT8) (ulLUTValue1*afViewWeight[0] + ulLUTValue2*afViewWeight[1]);
				}

			}

			// Set location weighting LUT value
			a_aucalAVM2DLocWeightingTable[x-a_ptalAVM2D_Params->tBirdViewStartPoint.lX+y*a_ptalAVM2D_Params->tBirdViewAreaSize.lX] = ulLUTValue;
            
			


        }
    }

}

void	alAVM2D_alAVM2DGeneratingByM33_GrayLevel(
	UINT8 *a_pucSrcBufferFront,
	UINT8 *a_pucSrcBufferBack,
	UINT8 *a_pucSrcBufferLeft,
	UINT8 *a_pucSrcBufferRight,
	FLOAT64 *a_paeM33LeftW2I,
	FLOAT64 *a_paeM33RightW2I,
	FLOAT64 *a_paeM33FrontW2I,
	FLOAT64 *a_paeM33BackW2I,
	UINT8 *a_pucBirdViewBuffer,
    alAVM2D_Params *a_ptalAVM2D_Params,
    alAVM2D_Cfg *a_ptalAVM2D_Cfg,
    alFM_v2_1_Model *a_ptFisheyeModel
	)
{
	UINT8 *pucSrc1 = NULL, *pucSrc2 = NULL, *pucSrc3 = NULL, *pucSrc4 = NULL;
	UINT8 a_ucViewIndex1, a_ucViewIndex2;
	UINT8 *a_apucSrcBuffer[4];
    UINT8 ucVCFisheyeIndex = alCAMERAINFO_SV_LEFT;//alCAMERAINFO_BV_BACK;//alCAMERAINFO_BV_FRONT;//
	UINT8 ucCameraIndex = 0;
	INT8 cBlindFlag = 0;
	INT32 i = 0;
	alAVM2D_StitchLineCfg tStitchLineCfg_2D;
	FLOAT64* paeM33[4];
	alAVM2D_Cfg *ptalAVM2DCfg = NULL;
	alAVM2D_Params *ptalAVM2DParams = NULL;
    alPointINT32 tBVImgSize = { 0 };
    alPointINT32 atSrcImgSize[COMMONK_NUM_BV_CHANNEL] = { 0 };

    for (i = 0; i < COMMONK_NUM_BV_CHANNEL; i++)
    {
        atSrcImgSize[i].lX = a_ptFisheyeModel[i].uwSrcWidth;
        atSrcImgSize[i].lY = a_ptFisheyeModel[i].uwSrcHeight;
    }
    

    tBVImgSize.lX = a_ptalAVM2D_Cfg->tDestImageBufferSize.lX;
    tBVImgSize.lY = a_ptalAVM2D_Cfg->tDestImageBufferSize.lY;

    ptalAVM2DCfg = a_ptalAVM2D_Cfg;
    ptalAVM2DParams = a_ptalAVM2D_Params;

	a_apucSrcBuffer[0] = a_pucSrcBufferLeft;
	a_apucSrcBuffer[1] = a_pucSrcBufferRight;
	a_apucSrcBuffer[2] = a_pucSrcBufferFront;
	a_apucSrcBuffer[3] = a_pucSrcBufferBack;

	paeM33[alCAMERAINFO_BV_LEFT] = a_paeM33LeftW2I;
	paeM33[alCAMERAINFO_BV_RIGHT] = a_paeM33RightW2I;
	paeM33[alCAMERAINFO_BV_FRONT] = a_paeM33FrontW2I;
	paeM33[alCAMERAINFO_BV_BACK] = a_paeM33BackW2I;

	alAVM2D_SetStitchLineInfo(ptalAVM2DParams, ptalAVM2DCfg, &tStitchLineCfg_2D);

	{
        UINT8 aucViewIndex[2], ucViewIndexBuff = 0, aucView1Weighting = 0;
        BOOL a_bView1Enabled = 0, a_bView2Enabled = 0;
		INT32 lX, lY;
        register INT32 lDestIntX1, lDestIntY1;
        UINT32 ulPixelIndex = 0;
        UINT32 ulVCCenterX, ulVCCenterY;
        FLOAT32 afWeighting[2];
        register FLOAT64 eDestDecX1, eDestDecY1;
        FLOAT64 eBVPosX, eBVPosY;
		FLOAT64 eBVX_Pixel, eBVY_Pixel;
        FLOAT64 eUndistX, eUndistY;
        FLOAT64 eDestX1, eDestY1;
		
		ulPixelIndex = 0;
        ulVCCenterX = (ptalAVM2DCfg->tDestImageBufferSize.lX >> 1);
        ulVCCenterY = (ptalAVM2DCfg->tDestImageBufferSize.lY >> 1);

		// START TO GEN alAVM2D
		for (lY = 0; lY < ptalAVM2DParams->tBirdViewAreaSize.lY; lY++)
		{
            ulPixelIndex = lY * tBVImgSize.lX;
			for (lX = 0; lX < ptalAVM2DParams->tBirdViewAreaSize.lX; lX++, ulPixelIndex++)
			{

				eBVX_Pixel = lX + ptalAVM2DParams->tBirdViewStartPoint.lX;
				eBVY_Pixel = lY + ptalAVM2DParams->tBirdViewStartPoint.lY;

				if (lX == 248 && lY == 423) // for test
				{
					lX = lX;

				}

				// 判斷是否為黑區
				cBlindFlag = alAVM2D_BlindRegionDecide((INT32)eBVX_Pixel, (INT32)eBVY_Pixel, ptalAVM2DParams);

				if (cBlindFlag)
				{

					eBVPosX = (eBVX_Pixel - ulVCCenterX) * ptalAVM2DParams->fMMPP;
					eBVPosY = (eBVY_Pixel - ulVCCenterY) * ptalAVM2DParams->fMMPP;


					if (ptalAVM2DCfg->ucStitchLineType)
					{	// new overlap
						alAVM2D_OverlapWeightCal(ptalAVM2DCfg, eBVPosX, eBVPosY, &tStitchLineCfg_2D, afWeighting, aucViewIndex);
					}
					else
					{	// old overlap
						alAVM2D_OverlapWeightCal(ptalAVM2DCfg, eBVX_Pixel, eBVY_Pixel, &tStitchLineCfg_2D, afWeighting, aucViewIndex);
					}

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
					// ADD BY ANCRE 2015 02 25
					ucViewIndexBuff = (afWeighting[0] >= afWeighting[1]) ? a_ucViewIndex1 : a_ucViewIndex2;
					if (ucViewIndexBuff != 255)
					{
                        COMMONK_PerformCoordinatesTransform(paeM33[ucViewIndexBuff], eBVX_Pixel, eBVY_Pixel, &eUndistX, &eUndistY);
                        alFM_v2_1_Undistorted2Distorted_PlanarPixel(a_ptFisheyeModel + ucViewIndexBuff, eUndistX, eUndistY, &eDestX1, &eDestY1);

						//取整數位
						lDestIntX1 = (INT32)(eDestX1);
						lDestIntY1 = (INT32)(eDestY1);

						//取小數位
						eDestDecX1 = eDestX1 - lDestIntX1;
						eDestDecY1 = eDestY1 - lDestIntY1;

						// 避免超出原影像邊界
                        if (lDestIntX1 > 0 && lDestIntY1 > 0 && (lDestIntX1 + 1) < atSrcImgSize[ucViewIndexBuff].lX && (lDestIntY1 + 1) < atSrcImgSize[ucViewIndexBuff].lY)
						{
							a_bView1Enabled = TRUE;
						}
						else
						{
							a_bView1Enabled = FALSE;
						}

					}
					else
					{
						a_bView1Enabled = FALSE;
					}
					// ADD BY ANCRE 2015 02 25

				}
				else
				{
					a_bView1Enabled = FALSE;
				}


				if (a_bView1Enabled)
				{	// ok
                    pucSrc1 = a_apucSrcBuffer[ucViewIndexBuff] + ((lDestIntX1 + lDestIntY1 * atSrcImgSize[ucViewIndexBuff].lX) << 1);
					pucSrc2 = pucSrc1 + 2;
                    pucSrc3 = pucSrc1 + (atSrcImgSize[ucViewIndexBuff].lX << 1);
					pucSrc4 = pucSrc3 + 2;
#if 0 //  內插
					// a_pucBirdViewBuffer[ulPixelIndex] = (UINT8)(((*pucSrc1) + (*pucSrc2) + (*pucSrc3) + (*pucSrc4)) / 4);
					a_pucBirdViewBuffer[ulPixelIndex] = (UINT8)((1.0 - eDestDecX1) * (1.0 - eDestDecY1) * (*pucSrc1) + eDestDecX1 * (1.0 - eDestDecY1) * (*pucSrc2)
						+ (1.0 - eDestDecX1) * eDestDecY1 * (*pucSrc3) + eDestDecX1 * eDestDecY1 * (*pucSrc4));
#else	//不內插
                    a_pucBirdViewBuffer[ulPixelIndex] = 255;
#if 0 // YUYV input
                    // a_pucBirdViewBuffer[ulPixelIndex] = a_apucSrcBuffer[ucViewIndexBuff][lDestIntY1*atSrcImgSize[ucViewIndexBuff].lX * 2 + lDestIntX1 * 2];
#else // Y input
                    a_pucBirdViewBuffer[ulPixelIndex] = a_apucSrcBuffer[ucViewIndexBuff][lDestIntY1*atSrcImgSize[ucViewIndexBuff].lX + lDestIntX1];
#endif
#endif
				}
				else
				{	// fail
					a_pucBirdViewBuffer[ulPixelIndex] = 0;
				}

			}

		}
	}
}


#undef SIZE_WEIGHTING_CURVE_LUT
#undef MAX_CURVE_VALUE
