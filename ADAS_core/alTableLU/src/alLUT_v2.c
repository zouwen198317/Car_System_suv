
#include "alLUT_v2.h"
#include "basedef.h"

/** \brief The AND value for interpolation weighting. */
static const UINT32 g_ulWeightAND=(1<<8)-1;
/** \brief The look-up table for interpolation weighting. */
static const UINT32 g_ulDecimalWeightBilinear[8][8] = 
{
    {2147483648, 1828721152, 1526735872, 1224750592, 905988352, 604003072, 302017792, 32768 },
    {1829896192, 1578045186, 1309482757, 1040854791, 789003786, 520441357, 251813391, 27922 },
    {1529085952, 1310657797, 1092229642, 873735951, 655307796, 436879642, 218451487, 23332 },
    {1228275712, 1043270151, 874976271, 689905431, 521611551, 336540711, 168246831, 18742 },
    {910753792, 792594186, 657723156, 522786591, 387915561, 252978996, 118107966, 13897 },
    {609943552, 525206797, 440470042, 338956071, 254219316, 169482817, 84746062, 9307 },
    {309133312, 257819151, 223216927, 171837231, 120523326, 85921102, 34541406, 4717 },
    {8388608, 7143442, 5963812, 4784182, 3539017, 2359387, 1179757, 128 }
};
/** \brief The bit shift for look-up table of interpolation weighting. */
static const UINT32 g_ulWeightBITshift[4] = {24,16,8,0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alLUT_v2_ProcessFullLU(alLUT_v2_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage)
{
    INT32 lX, lY;

    UINT8 * pucDstPtr = 0;
    UINT64 * pullLUTPtr = 0;

    UINT8 ucCameraIndex1, ucCameraIndex2 = 0;
    UINT32 ulOffset1, ulOffset2;
    UINT8 ucDecX1, ucDecY1, ucDecX2, ucDecY2;
    UINT8 ucWeight1, ucWeight2;
    UINT8 ucBlack;
    UINT8 ucY1, ucY2, ucY3, ucY4;
    UINT8 ucY, ucIntpoY1 = 0, ucIntpoY2 = 0;
    UINT8 ucU, ucV, ucU1 = 0, ucV1 = 0, ucU2 = 0, ucV2 = 0;

    for(lY = 0; lY < a_ptTable->tDestAreaSize.lY; lY++)
    {
        pucDstPtr = a_pucDstImage + (a_ptTable->tDestStartPoint.lX<<1) + (a_ptTable->tDestStartPoint.lY + lY) * (a_ptTable->tDestImageBufferSize.lX<<1);
        pullLUTPtr = a_ptTable->pullTable + lY * a_ptTable->tDestAreaSize.lX;

        for(lX = 0; lX < a_ptTable->tDestAreaSize.lX; lX+=2, pucDstPtr += 4)
        {
            if (lX == 160 && lY == 45) // for test
            {
                lX = lX;
            }

            // Even Pixel
            ucBlack = ((*pullLUTPtr)>>alLUT_v2_SHIFT_ENABLE)&alLUT_v2_AND_ENABLE;
            if(ucBlack == 0)
            {
                // 解出第一組Pixel的Weight值
                ucWeight1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_WEIGHT)&alLUT_v2_AND_WEIGHT;

                if(ucWeight1 > 0) // Weight值為0時，就不用做查表
                {

                    // 解出第一組Pixel的Dec,Offset,Camera值
                    ucDecY1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_1)&alLUT_v2_AND_DECY_1;
                    ucDecX1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_1)&alLUT_v2_AND_DECX_1;
                    ulOffset1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_1)&alLUT_v2_AND_OFFSET_1;
                    ucCameraIndex1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_1)&alLUT_v2_AND_CAM_1;

                    // 根據Dec做內插
			        ucY1 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX + 1)<<1));

			        ucIntpoY1 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;

                    // 取出 U1, V1 值
                    if(ulOffset1 % 2 == 0)
                    {
                        // Even
                        ucU1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 1];
                        ucV1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 3];
                    }
                    else
                    {
                        // Odd
                        ucU1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) - 1];
                        ucV1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 1];
                   }
                }

                // 解出第二組Pixel的Weight值
                ucWeight2 = alLUT_v2_AND_WEIGHT - ucWeight1;

                if(ucWeight2 > 0) // Weight值為0時，就不用做查表
                {
                    // 解出第二組Pixel的Dec,Offset,Camera值
                    ucDecY2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_2)&alLUT_v2_AND_DECY_2;
                    ucDecX2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_2)&alLUT_v2_AND_DECX_2;
                    ulOffset2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_2)&alLUT_v2_AND_OFFSET_2;
                    ucCameraIndex2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_2)&alLUT_v2_AND_CAM_2;

			        ucY1 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX + 1)<<1));

			        ucIntpoY2 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;

                    // U2, V2
                    if(ulOffset2 % 2 == 0)
                    {
                        // Even
                        ucU2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 1];
                        ucV2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 3];
                    }
                    else
                    {
                        // Odd
                        ucU2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) - 1];
                        ucV2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 1];
                   }
                }

                // 將兩組Pixel的數值做weighting
                ucY = (INT32)(ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)/alLUT_v2_AND_WEIGHT;
                ucU = (INT32)(ucWeight1 * ucU1 + ucWeight2 * ucU2)/alLUT_v2_AND_WEIGHT;
                ucV = (INT32)(ucWeight1 * ucV1 + ucWeight2 * ucV2)/alLUT_v2_AND_WEIGHT;

                *(pucDstPtr    ) = ucY;
                *(pucDstPtr + 1) = ucU;
                *(pucDstPtr + 3) = ucV;
            }
            else
            {
                *(pucDstPtr    ) = 0;
                *(pucDstPtr + 1) = 128;
                *(pucDstPtr + 3) = 128;
            }

            // To next pixel - Odd Pixel
            pullLUTPtr++;

            // Odd Pixel
            ucBlack = ((*pullLUTPtr)>>alLUT_v2_SHIFT_ENABLE)&alLUT_v2_AND_ENABLE;
            if(ucBlack == 0)
            {

                ucWeight1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_WEIGHT)&alLUT_v2_AND_WEIGHT;

                if(ucWeight1 > 0)
                {
                    ucDecY1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_1)&alLUT_v2_AND_DECY_1;
                    ucDecX1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_1)&alLUT_v2_AND_DECX_1;
                    ulOffset1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_1)&alLUT_v2_AND_OFFSET_1;
                    ucCameraIndex1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_1)&alLUT_v2_AND_CAM_1;

			        ucY1 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX + 1)<<1));

			        ucIntpoY1 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;
                }
                
                ucWeight2 = alLUT_v2_AND_WEIGHT - ucWeight1;
                if(ucWeight2 > 0)
                {
                    ucDecY2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_2)&alLUT_v2_AND_DECY_2;
                    ucDecX2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_2)&alLUT_v2_AND_DECX_2;
                    ulOffset2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_2)&alLUT_v2_AND_OFFSET_2;
                    ucCameraIndex2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_2)&alLUT_v2_AND_CAM_2;

			        ucY1 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX + 1)<<1));

			        ucIntpoY2 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;
                }

                // 將兩組Pixel的數值做weighting
                ucY = (ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)/alLUT_v2_AND_WEIGHT;

                *(pucDstPtr + 2) = ucY;
            }
            else
            {
                *(pucDstPtr + 2) = 0;
            }

            pullLUTPtr++;

        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alLUT_v2_ProcessFullLU_ApplyGAE(INT8 * a_pcGAE_YOffset, alLUT_v2_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage)
{
    INT32 lX, lY;

    UINT8 * pucDstPtr = 0;
    UINT64 * pullLUTPtr = 0;

    UINT8 ucCameraIndex1, ucCameraIndex2 = 0;
    UINT32 ulOffset1, ulOffset2;
    UINT8 ucDecX1, ucDecY1, ucDecX2, ucDecY2;
    UINT8 ucWeight1, ucWeight2;
    UINT8 ucBlack;
    UINT8 ucY1, ucY2, ucY3, ucY4;
    UINT8 ucY;
    register INT32 lIntpoY1 = 0, lIntpoY2 = 0;
    UINT8 ucU, ucV, ucU1 = 0, ucV1 = 0, ucU2 = 0, ucV2 = 0;

    for(lY = 0; lY < a_ptTable->tDestAreaSize.lY; lY++)
    {
        pucDstPtr = a_pucDstImage + (a_ptTable->tDestStartPoint.lX<<1) + (a_ptTable->tDestStartPoint.lY + lY) * (a_ptTable->tDestImageBufferSize.lX<<1);
        pullLUTPtr = a_ptTable->pullTable + lY * a_ptTable->tDestAreaSize.lX;

        for(lX = 0; lX < a_ptTable->tDestAreaSize.lX; lX+=2, pucDstPtr += 4)
        {
            // Even Pixel
            ucBlack = ((*pullLUTPtr)>>alLUT_v2_SHIFT_ENABLE)&alLUT_v2_AND_ENABLE;
            if(ucBlack == 0)
            {
                // 解出第一組Pixel的Weight值
                ucWeight1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_WEIGHT)&alLUT_v2_AND_WEIGHT;

                if(ucWeight1 > 0) // Weight值為0時，就不用做查表
                {

                    // 解出第一組Pixel的Dec,Offset,Camera值
                    ucDecY1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_1)&alLUT_v2_AND_DECY_1;
                    ucDecX1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_1)&alLUT_v2_AND_DECX_1;
                    ulOffset1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_1)&alLUT_v2_AND_OFFSET_1;
                    ucCameraIndex1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_1)&alLUT_v2_AND_CAM_1;

                    // 根據Dec做內插
			        ucY1 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX + 1)<<1));

			        lIntpoY1 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;

                    lIntpoY1 = lIntpoY1 + a_pcGAE_YOffset[ucCameraIndex1];
                    lIntpoY1 = alMIN(alMAX(lIntpoY1, 0), 255);

                    // 取出 U1, V1 值
                    if(ulOffset1 % 2 == 0)
                    {
                        // Even
                        ucU1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 1];
                        ucV1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 3];
                    }
                    else
                    {
                        // Odd
                        ucU1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) - 1];
                        ucV1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 1];
                   }
                }

                // 解出第二組Pixel的Weight值
                ucWeight2 = alLUT_v2_AND_WEIGHT - ucWeight1;

                if(ucWeight2 > 0) // Weight值為0時，就不用做查表
                {
                    // 解出第二組Pixel的Dec,Offset,Camera值
                    ucDecY2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_2)&alLUT_v2_AND_DECY_2;
                    ucDecX2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_2)&alLUT_v2_AND_DECX_2;
                    ulOffset2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_2)&alLUT_v2_AND_OFFSET_2;
                    ucCameraIndex2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_2)&alLUT_v2_AND_CAM_2;

			        ucY1 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX + 1)<<1));

			        lIntpoY2 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;

                    lIntpoY2 = lIntpoY2 + a_pcGAE_YOffset[ucCameraIndex2];
                    lIntpoY2 = alMIN(alMAX(lIntpoY2, 0), 255);

                    // U2, V2
                    if(ulOffset2 % 2 == 0)
                    {
                        // Even
                        ucU2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 1];
                        ucV2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 3];
                    }
                    else
                    {
                        // Odd
                        ucU2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) - 1];
                        ucV2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 1];
                   }
                }

                // 將兩組Pixel的數值做weighting
                ucY = (INT32)(ucWeight1 * lIntpoY1 + ucWeight2 * lIntpoY2)/alLUT_v2_AND_WEIGHT;
                ucU = (INT32)(ucWeight1 * ucU1 + ucWeight2 * ucU2)/alLUT_v2_AND_WEIGHT;
                ucV = (INT32)(ucWeight1 * ucV1 + ucWeight2 * ucV2)/alLUT_v2_AND_WEIGHT;

                *(pucDstPtr    ) = ucY;
                *(pucDstPtr + 1) = ucU;
                *(pucDstPtr + 3) = ucV;
            }
            else
            {
                *(pucDstPtr    ) = 0;
                *(pucDstPtr + 1) = 128;
                *(pucDstPtr + 3) = 128;
            }

            // To next pixel - Odd Pixel
            pullLUTPtr++;

            // Odd Pixel
            ucBlack = ((*pullLUTPtr)>>alLUT_v2_SHIFT_ENABLE)&alLUT_v2_AND_ENABLE;
            if(ucBlack == 0)
            {

                ucWeight1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_WEIGHT)&alLUT_v2_AND_WEIGHT;

                if(ucWeight1 > 0)
                {
                    ucDecY1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_1)&alLUT_v2_AND_DECY_1;
                    ucDecX1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_1)&alLUT_v2_AND_DECX_1;
                    ulOffset1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_1)&alLUT_v2_AND_OFFSET_1;
                    ucCameraIndex1 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_1)&alLUT_v2_AND_CAM_1;

			        ucY1 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].lX + 1)<<1));

			        lIntpoY1 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;

                    lIntpoY1 = lIntpoY1 + a_pcGAE_YOffset[ucCameraIndex1];
                    lIntpoY1 = alMIN(alMAX(lIntpoY1, 0), 255);

                }
                
                ucWeight2 = alLUT_v2_AND_WEIGHT - ucWeight1;
                if(ucWeight2 > 0)
                {
                    ucDecY2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECY_2)&alLUT_v2_AND_DECY_2;
                    ucDecX2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_DECX_2)&alLUT_v2_AND_DECX_2;
                    ulOffset2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_OFFSET_2)&alLUT_v2_AND_OFFSET_2;
                    ucCameraIndex2 = ((*pullLUTPtr)>>alLUT_v2_SHIFT_CAM_2)&alLUT_v2_AND_CAM_2;

			        ucY1 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2)<<1));
			        ucY2 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + 1)<<1));
                    ucY3 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX)<<1));
			        ucY4 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].lX + 1)<<1));

			        lIntpoY2 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;

                    lIntpoY2 = lIntpoY2 + a_pcGAE_YOffset[ucCameraIndex2];
                    lIntpoY2 = alMIN(alMAX(lIntpoY2, 0), 255);

                }

                // 將兩組Pixel的數值做weighting
                ucY = (ucWeight1 * lIntpoY1 + ucWeight2 * lIntpoY2)/alLUT_v2_AND_WEIGHT;

                *(pucDstPtr + 2) = ucY;
            }
            else
            {
                *(pucDstPtr + 2) = 0;
            }

            pullLUTPtr++;

        }
    }
}
