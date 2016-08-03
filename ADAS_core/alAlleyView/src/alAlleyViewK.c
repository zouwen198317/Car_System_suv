
#include "alAlleyViewK.h"
#include <math.h>
#include <stdlib.h>

#include "alMatrix.h"
#include "basedef.h"

#if alALLEYVIEWDebug // for test and debug
#include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

static void Test_AV_Mask_Local(INT32 a_lWidth, INT32 a_lHeight, UINT8 *a_pucAV_mask)
{

    INT32 lWidth = 0, lHeight = 0;
    INT32 x, y;
    UINT32 ulRawIndex = 0, ulPixelIndex = 0;
    UINT32 ulByteIndex = 0;
    UINT8 ucBitIndex = 0;
#if alALLEYVIEWDebug // FOR DEBUG TEST
    IplImage * ptPicGray = NULL;
    char text[MAX_PATH] = { 0 };
    
#endif 
    UINT8 *pucAVTest = NULL;

    lWidth = a_lWidth;
    lHeight = a_lHeight;
    pucAVTest = (UINT8 *)malloc(lWidth * lHeight * sizeof(UINT8));

    ///
    // AV LEFT
    for (y = 0; y < lHeight; y++)
    {
        ulRawIndex = y * lWidth;
        for (x = 0; x < (lWidth >> 1); x++)
        {
            ulPixelIndex = ulRawIndex + x;
            ulByteIndex = (ulPixelIndex >> 3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            //apply alley view mask 
            if ((a_pucAV_mask[ulByteIndex] & (1 << ucBitIndex)) >> ucBitIndex)
            {
                pucAVTest[ulPixelIndex] = 255;

            }
            else
            {
                pucAVTest[ulPixelIndex] = 0;
            }

        }
    }

    // AV RIGHT
    for (y = 0; y < lHeight; y++)
    {
        ulRawIndex = y * lWidth + (lWidth >> 1);

        for (x = 0; x < (lWidth >> 1); x++)
        {
            ulPixelIndex = ulRawIndex + x;
            ulByteIndex = (ulPixelIndex >> 3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            //apply alley view mask 
            if ((a_pucAV_mask[ulByteIndex] & (1 << ucBitIndex)) >> ucBitIndex)
            {
                pucAVTest[ulPixelIndex] = 255;
            }
            else
            {
                pucAVTest[ulPixelIndex] = 0;
            }
        }
    }
    ///

#if alALLEYVIEWDebug // FOR DEBUG TEST
    ptPicGray = cvCreateImage(cvSize(lWidth, lHeight), IPL_DEPTH_8U, 1);
    memcpy(ptPicGray->imageData, pucAVTest, sizeof(UINT8)*ptPicGray->imageSize);
    sprintf_s(text, MAX_PATH, "MaskTest_Local.jpg");
    cvSaveImage(text, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
    free(pucAVTest);
#endif 
}

/** 
    \brief Generate an alley view display mask with two windows depends on 8 crop points [CropPos], and 
           alley view width and height. (without softcorner)	
    \param Width [IN] Image Width
    \param Height [IN] Image Height
	\param CropPos [IN] define display window layout
	\param Crop_bool [OUT] Alley view mask without softcorner (腳邊是尖的，像用刀切下來一樣)
	\return None
*/
static void DefineCropArea(INT32 a_lWidth, INT32 a_lHeight, INT16 * a_pwCropPos, UINT8 * a_pucAVMask)
{
    int x,y;
    float fThreshold1=-1, fThreshold2=-1, fThreshold3=-1, fThreshold4=-1;
    //float fThreshold5=-1, fThreshold6=-1, fThreshold7=-1, fThreshold8=-1;

    UINT32 ulPixelIndex = 0;
    UINT32 ulByteIndex = 0;
    UINT8 ucBitIndex = 0;
#if alALLEYVIEWDebug // FOR DEBUG TEST
    IplImage * ptPicGray = NULL;
    char text[MAX_PATH] = { 0 };
    UINT8 *pucAVTest = NULL;
    pucAVTest = (UINT8 *)malloc(a_lWidth * a_lHeight * sizeof(UINT8));
#endif 

    //Defaut Crop Area: a_pwCropPos = {X0,X1,...,X7,Y0,Y1...,Y7}
    for(y = 0; y < a_lHeight; y++)
    {
        for(x = 0; x < a_lWidth; x++, ulPixelIndex++)
        {
            ulByteIndex = (ulPixelIndex>>3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            //flag
            fThreshold1=-1, fThreshold2=-1, fThreshold3=-1, fThreshold4=-1;
            //fThreshold5=-1, fThreshold6=-1, fThreshold7=-1, fThreshold8=-1;
            //YUYV(四格)處理一次, UV平均掉
            //-----------------------------------Window Crop----------------------------------

            /*mask

            (0,0) ->  ______________
            |              | 
            |  0---------2 |
            |  |         | |
            |  |         | |
            |  |         | |
            |  |         | |
            |  |         | |
            |  |         | |
            |  |       __3 |
            |  |  ////     |
            |  1           |
            |              |
            |______________|  
            */
            //Crop Line1(0 to 1)
            if(a_pwCropPos[1]!=a_pwCropPos[0])
            {
	            //           (   Y1      -   Y0     )/(   X1     -    X0    ) *(x-   X1     )-(y-    Y1)
                fThreshold1 = ((float)(a_pwCropPos[5]-a_pwCropPos[4])/(float)(a_pwCropPos[1]-a_pwCropPos[0]))*(x-a_pwCropPos[1])-(y-a_pwCropPos[5]);
                if((float)(a_pwCropPos[5]-a_pwCropPos[4])/(float)(a_pwCropPos[1]-a_pwCropPos[0])<=0)
                    fThreshold1 = -fThreshold1;//斜率負值 需變換
            }
            else
            {
                if(x>=(float)a_pwCropPos[0])
                    fThreshold1 = 1;
            }
            //Crop Line2 (1 to 3)

            if(a_pwCropPos[1]!=a_pwCropPos[3])
            {  
                //                    (   Y3      -   Y1     )/(   X3     -    X1    ) *(x-   X1     )-(y-    Y1)
                fThreshold2 = ((float)(a_pwCropPos[7]-a_pwCropPos[5])/(float)(a_pwCropPos[3]-a_pwCropPos[1]))*(x-a_pwCropPos[1])-(y-a_pwCropPos[5]);
            }
            else
            {
                if(x<=(float)a_pwCropPos[1])
                    fThreshold2 = 1;
            }
            //Crop Line3 (2 to 3)
            if(a_pwCropPos[2]!=a_pwCropPos[3])
            {
                //                    (   Y2      -   Y3     )/(   X2     -    X3    ) *(x-   X3     )-(y-    Y3)
                fThreshold3 = ((float)(a_pwCropPos[6]-a_pwCropPos[7])/(float)(a_pwCropPos[2]-a_pwCropPos[3]))*(x-a_pwCropPos[3])-(y-a_pwCropPos[7]);
                if((float)(a_pwCropPos[6]-a_pwCropPos[7])/(float)(a_pwCropPos[2]-a_pwCropPos[3])>=0)
                    fThreshold3 = -fThreshold3;
            }
            else
            {
                if(x<=a_pwCropPos[2])
                    fThreshold3 = 1;
            }
            //Crop Line4 (2 to 0)
            if(a_pwCropPos[2]!=a_pwCropPos[0])
            {
                //    (   Y2      -   Y0     )/(   X2     -    X0    ) *(x-   X2     )-(y-    Y2)
                fThreshold4 =-(((float)(a_pwCropPos[6]-a_pwCropPos[4])/(float)(a_pwCropPos[2]-a_pwCropPos[0]))*(x-a_pwCropPos[2])-(y-a_pwCropPos[6]));
            }
            else
            {
                if(x<=(float)a_pwCropPos[2])
                    fThreshold4 = 1;
            }

            if(fThreshold1 >= -0.01 && fThreshold2 >= -0.01 && fThreshold3 >= -0.01 && fThreshold4 >= -0.01)
            {
                //表示落在四切線之內，即為mask內
                a_pucAVMask[ulByteIndex] |= (1<<ucBitIndex);
#if alALLEYVIEWDebug // FOR DEBUG TEST
                pucAVTest[ulPixelIndex] = 255;
#endif 
            }
            //else
            //{
            //    //表示落在四切線之外，即為mask外
            //    a_pucAVMask[y*a_lWidth+x  ] = -1;
            //}
        }
    }
#if alALLEYVIEWDebug // FOR DEBUG TEST
    ptPicGray = cvCreateImage(cvSize(a_lWidth, a_lHeight), IPL_DEPTH_8U, 1);
    memcpy(ptPicGray->imageData, pucAVTest, sizeof(UINT8)*ptPicGray->imageSize);
    sprintf_s(text, MAX_PATH, "MaskTest.jpg");
    cvSaveImage(text, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
    free(pucAVTest);
#endif 
}

static void SoftCorner(UINT8 * a_pucSrcMask, UINT8 * a_puDestMask, INT32 a_lWidth, INT32 a_lHeight, 
                       INT32 a_lProcStartX, INT32 a_lProcStartY,
                       INT32 a_lProcWidth, INT32 a_lProcHeight)
{
    register UINT8 ucHalfKernelSize = 6;
    INT16 wCount = 0;
	INT32 x, y;
	INT32 i, j;
	//double Percentage;
	//掃過src_bool內每一個pixel

    INT16 wCntTh = ((((ucHalfKernelSize<<1) + 1) * ((ucHalfKernelSize<<1) + 1))>>1);
    UINT32 ulCorePixelIndex = 0;
    register UINT32 ulPixelIndex = 0;
    register UINT32 ulByteIndex = 0;
    register UINT8 ucBitIndex = 0;
    INT32 lBinWidth = (a_lWidth>>3) + ((a_lWidth&0x7)!=0);

	memcpy(a_puDestMask, a_pucSrcMask, sizeof(UINT8) * lBinWidth * a_lHeight);

    for(y = ucHalfKernelSize; y < a_lProcHeight - ucHalfKernelSize; y++)
    {
        ulPixelIndex = a_lProcStartX + ucHalfKernelSize + a_lWidth * (a_lProcStartY + y);

        for(x = ucHalfKernelSize;x < a_lProcWidth - ucHalfKernelSize; x++, ulPixelIndex ++)
        {
            ulByteIndex = (ulPixelIndex>>3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            if(((a_pucSrcMask[ulByteIndex] & (1<<ucBitIndex))>>ucBitIndex) == 0) continue;

            wCount = 0;
            // Blocks 內符合 mask內資格之數量
            for(j = y - ucHalfKernelSize; j <= y + ucHalfKernelSize; j++)
            {
                for(i = x - ucHalfKernelSize; i <= x + ucHalfKernelSize; i++)
                {
                    ulCorePixelIndex = (j + a_lProcStartY) *a_lWidth + (i + a_lProcStartX);
                    ulByteIndex = (ulCorePixelIndex>>3);
                    ucBitIndex = (7 - (ulCorePixelIndex & 0x7));

                    //防呆
                    if(i >= 0 && j >= 0 && i < a_lProcWidth && j < a_lProcHeight)
                    {
                        //CountY++;
                        wCount += ((a_pucSrcMask[ulByteIndex] & (1<<ucBitIndex))>>ucBitIndex);
                    }
                    else
                    {
                        wCount++;
                    }
                }  
            }

            ulByteIndex = (ulPixelIndex>>3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            ////當比例少於一半
            if(wCount < wCntTh)
            {
                // block中央填黑
                a_puDestMask[ulByteIndex] &= (~(1<<ucBitIndex));
            }
            //else
            //{
            //    //不動
            //    dst_bool[ulByteIndex] = src_bool[ulByteIndex];
            //}
        }
	}

}

/** 
    \brief Generate an alley view display mask with two windows depends on 8 crop points [CropPos], and 
           alley view width and height. (with softcorner)	
    \param a_lAVWidth [IN] Image Width
    \param a_lAVHeight [IN] Image Height
	\param a_pwCropPosLeft [IN] define display window layout for left 
	\param a_pwCropPosRight [IN] define display window layout for right
	\param a_lSoftPixels [IN] define the number of pixels to (潤邊) softCorner
	\param a_pucMask [OUT] Output the mask.
*/
static void GetMask(INT32 a_lAVWidth, INT32 a_lAVHeight, INT16 * a_pwCropPosLeft, INT16 * a_pwCropPosRight, INT32 a_lSoftPixels, UINT8 * a_pucMask)
{
    INT32 i;
    UINT8 * pucTempMask = NULL;
    UINT8 * pucSrcMask = NULL;
    UINT8 * pucDestMask = NULL;
    UINT8 * pucTempPtr = NULL;

    UINT8 ucSoftCropPosIndex_L = 3;
    UINT8 ucSoftCropPosIndex_R = 1;

    INT16 wProcStartX = 0;
    INT16 wProcStartY = 0;
    INT16 wProcEndX = 0;
    INT16 wProcEndY = 0;
    const INT16 wProcHalfPixel = 48;

    INT32 lBinWidth = (a_lAVWidth>>3) + ((a_lAVWidth&0x7)!=0);

    memset(a_pucMask, 0, sizeof(UINT8) * lBinWidth * a_lAVHeight);

	//取得由8點所裁切結果之mask
    DefineCropArea(a_lAVWidth, a_lAVHeight, a_pwCropPosLeft, a_pucMask);
    DefineCropArea(a_lAVWidth, a_lAVHeight, a_pwCropPosRight, a_pucMask);

#if 1  // 潤邊程式
    pucTempMask = (UINT8*) malloc(sizeof(UINT8) * lBinWidth * a_lAVHeight);
    if(pucTempMask == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: GetMask::pucTempMask");
        return;
    }

    pucSrcMask = a_pucMask;
    pucDestMask = pucTempMask;

    // Process for Left
    wProcStartX = alMAX(a_pwCropPosLeft[ucSoftCropPosIndex_L] - wProcHalfPixel, 0);
    wProcStartY = alMAX(a_pwCropPosLeft[ucSoftCropPosIndex_L+4] - wProcHalfPixel, 0);
    wProcEndX = alMIN(a_pwCropPosLeft[ucSoftCropPosIndex_L] + wProcHalfPixel, a_lAVWidth);
    wProcEndY = alMIN(a_pwCropPosLeft[ucSoftCropPosIndex_L+4] + wProcHalfPixel, a_lAVHeight);

	//潤邊次數=潤邊數量
    for(i = 0; i < a_lSoftPixels; i++)
    {
        SoftCorner(pucSrcMask, pucDestMask, a_lAVWidth, a_lAVHeight, 
            wProcStartX, wProcStartY, wProcEndX - wProcStartX, wProcEndY - wProcStartY);

        pucTempPtr = pucDestMask;
        pucDestMask = pucSrcMask;
        pucSrcMask = pucTempPtr;
    }
    
    // Process for Right
    wProcStartX = alMAX(a_pwCropPosRight[ucSoftCropPosIndex_R] - wProcHalfPixel, 0);
    wProcStartY = alMAX(a_pwCropPosRight[ucSoftCropPosIndex_R+4] - wProcHalfPixel, 0);
    wProcEndX = alMIN(a_pwCropPosRight[ucSoftCropPosIndex_R] + wProcHalfPixel, a_lAVWidth);
    wProcEndY = alMIN(a_pwCropPosRight[ucSoftCropPosIndex_R+4] + wProcHalfPixel, a_lAVHeight);

	//潤邊次數=潤邊數量
    for(i = 0; i < a_lSoftPixels; i++)
    {
        SoftCorner(pucSrcMask, pucDestMask, a_lAVWidth, a_lAVHeight, 
            wProcStartX, wProcStartY, wProcEndX - wProcStartX, wProcEndY - wProcStartY);

        pucTempPtr = pucDestMask;
        pucDestMask = pucSrcMask;
        pucSrcMask = pucTempPtr;
    }

    if(pucSrcMask != a_pucMask)
    {
        memcpy(a_pucMask, pucSrcMask, sizeof(UINT8) * lBinWidth * a_lAVHeight);
    }

    free(pucTempMask);
#endif
}

INT32 alALLEYVIEW_GetMaskSize(alALLEYVIEW_Cfg * a_ptCfg)
{
    INT32 ulMaskSize = 0;
    INT32 lBinWidth = (a_ptCfg->tAreaSize.lX >> 3) + ((a_ptCfg->tAreaSize.lX & 0x7) != 0);

    return (sizeof(UINT8) * lBinWidth * a_ptCfg->tAreaSize.lY);
}

void alALLEYVIEW_GenMask(alALLEYVIEW_Cfg * a_ptCfg, UINT8 *a_pucMask)
{
    INT16 awWindowLeftCropPoints[8] = { 0 }, awWindowRightCropPoints[8] = {0};

    //Crop 8 points for left view fill in
    awWindowLeftCropPoints[0] = a_ptCfg->aApexPoints[0].lX;
    awWindowLeftCropPoints[1] = a_ptCfg->aApexPoints[1].lX;
    awWindowLeftCropPoints[2] = a_ptCfg->aApexPoints[2].lX;
    awWindowLeftCropPoints[3] = a_ptCfg->aApexPoints[3].lX;
    awWindowLeftCropPoints[4] = a_ptCfg->aApexPoints[0].lY;
    awWindowLeftCropPoints[5] = a_ptCfg->aApexPoints[1].lY;
    awWindowLeftCropPoints[6] = a_ptCfg->aApexPoints[2].lY;
    awWindowLeftCropPoints[7] = a_ptCfg->aApexPoints[3].lY;
    //Crop 8 points for right view fill in
    awWindowRightCropPoints[0] = a_ptCfg->aApexPoints[4].lX;
    awWindowRightCropPoints[1] = a_ptCfg->aApexPoints[5].lX;
    awWindowRightCropPoints[2] = a_ptCfg->aApexPoints[6].lX;
    awWindowRightCropPoints[3] = a_ptCfg->aApexPoints[7].lX;
    awWindowRightCropPoints[4] = a_ptCfg->aApexPoints[4].lY;
    awWindowRightCropPoints[5] = a_ptCfg->aApexPoints[5].lY;
    awWindowRightCropPoints[6] = a_ptCfg->aApexPoints[6].lY;
    awWindowRightCropPoints[7] = a_ptCfg->aApexPoints[7].lY;

    GetMask(
        a_ptCfg->tAreaSize.lX, a_ptCfg->tAreaSize.lY,
        awWindowLeftCropPoints, awWindowRightCropPoints,
        a_ptCfg->ulSoftPixels, a_pucMask
    );
}

/**
   \brief Generate Alley left view LUT by 3D Fisheye Model
   \param a_pucMask [IN] display mask
   \param a_aeM33AVL [IN] Alley left view transformation 3x3 matrix
   \param a_aeM33AVR [IN] Alley right view transformation 3x3 matrix
   \param a_ptFisheyeModel [IN] Fisheye model
   \param a_pulAVLUT_YUV [OUT] To store the generated LUT.
   \param a_lAVWidth [IN] alley left view display width
   \param a_lAVHeight [IN] alley left view display height
   \param a_lDisplayWidth [IN] The display buffer with where the alAlleyView will be draw.
   \param a_pwCropPointsLeft [IN] The crop points for left side.
   \param a_pwCropPointsRight [IN] The crop points for right side.
   \param a_lSoftPixels [IN] The soft pixels for crop area.
   \return None
*/
static void GenAVLUT_3D( 
    UINT8 *a_pucMask,
    FLOAT64 a_aeM33AVL[9],
    FLOAT64 a_aeM33AVR[9],
    alFM_v2_1_Model * a_ptFisheyeModel, 
    UINT32 *a_pulAVLUT_YUV, 
    INT32 a_lAVWidth, INT32 a_lAVHeight, 
    INT32 a_lDisplayWidth,
    INT16 *a_pwCropPointsLeft, 
    INT16 *a_pwCropPointsRight, 
    INT32 a_lSoftPixels
    )
{

    FLOAT64 ox, oy, dx, dy, dz;
    INT16 wIntX, wIntY, wDecX, wDecY;
    INT32 x, y, lBinWidth = 0;
    UINT8 *pucAV_mask = NULL, ucInputMask = 0;
    UINT32 ulRawIndex = 0, ulPixelIndex = 0, ulByteIndex = 0;
    UINT8 ucBitIndex = 0;
    UINT32 ulImgWidth = 0, ulImgHeight = 0;
#if alALLEYVIEWDebug // for test and debug
    UINT32 ulTableData = 0;
    UINT32 ulOffset = 0;
    char text[MAX_PATH] = { 0 };
    IplImage *ptPicGray = NULL;
    IplImage *ptPicGraySrc = NULL;
    UINT8 *pucTestImg = NULL;
    UINT8 *pucTestImg1 = NULL;
    pucTestImg = (UINT8*)malloc(a_lAVWidth * a_lAVHeight);
    memset(pucTestImg, 0, a_lAVWidth * a_lAVHeight);

    ptPicGraySrc = cvLoadImage("./SourceImage/AVM_AM_TEST_VGA/Source_2.bmp", CV_LOAD_IMAGE_GRAYSCALE);
    cvSaveImage("Front.jpg", ptPicGraySrc, 0);
    pucTestImg1 = (UINT8 *)ptPicGraySrc->imageData;
#endif

    ulImgWidth = a_ptFisheyeModel->uwSrcWidth;
    ulImgHeight = a_ptFisheyeModel->uwSrcHeight;

    if (a_pucMask == NULL)
    { // 沒事先建好mask
        ucInputMask = 0;
        lBinWidth = (a_lAVWidth >> 3) + ((a_lAVWidth & 0x7) != 0);
        pucAV_mask = (UINT8*)malloc(sizeof(UINT8) * lBinWidth * a_lAVHeight); // ==> 每一個Byte代表 8 pixels

        if (pucAV_mask == NULL)
        {
            DEBUG_Printf("Memory Allocation Failed: GenAVLUT::pucAV_mask");
            return;
        }

        //generate Alley View mask   
        GetMask(a_lAVWidth, a_lAVHeight, a_pwCropPointsLeft, a_pwCropPointsRight, a_lSoftPixels, pucAV_mask);
    }
    else
    { // 使用事先建好的mask
        ucInputMask = 1;
        pucAV_mask = a_pucMask;
    }
	
#if alALLEYVIEWDebug // for test and debug
    Test_AV_Mask_Local(a_lAVWidth, a_lAVHeight, pucAV_mask);
#endif

    memset(a_pulAVLUT_YUV, 0, sizeof(UINT32) * a_lAVHeight * a_lAVWidth);

	//LUT emtry fill in

    // AV LEFT
    for(y = 0; y < a_lAVHeight; y++)
    {
        ulRawIndex = y * a_lAVWidth;
        for(x = 0; x < (a_lAVWidth>>1); x++)
        {
            ulPixelIndex = ulRawIndex + x;
            ulByteIndex = (ulPixelIndex>>3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

            //apply alley view mask 
            if((pucAV_mask[ulByteIndex] & (1<<ucBitIndex))>>ucBitIndex)
            {
#if alALLEYVIEWDebug
                if (x == 0 && y == 0)
                {
                    y = y;
                }
                pucTestImg[ulPixelIndex] = 255;
#endif
			    //alley view tansformation
                alAlleyViewCoordinatesTransform3D(a_aeM33AVL, (FLOAT64)x, (FLOAT64)y, &dx, &dy, &dz);

			    //transformation, undistorted alley view position to distorted source front image
                alFM_v2_1_Undistorted2Distorted_Sphere(a_ptFisheyeModel, dx, dy, dz, &ox, &oy);

			    //取整數位
                wIntX = (INT16)(ox);
                wIntY = (INT16)(oy);
#if alALLEYVIEWDebug
                pucTestImg[ulPixelIndex] = pucTestImg1[wIntY * 720 + wIntX];
#endif
                //取小數位，以3bit儲存
                wDecX = (INT16)((ox - wIntX)*8);
                wDecY = (INT16)((oy - wIntY)*8);

                //prevent to out of range
                if(ox >= 0 && oy >= 0 && ox < (ulImgWidth>>1) && oy < ulImgHeight)
                {

                    a_pulAVLUT_YUV[ulPixelIndex] = ((wIntY * a_lDisplayWidth + wIntX)<<6) + (wDecX<<3) + wDecY;

                    continue;
                }
            }

            a_pulAVLUT_YUV[ulPixelIndex] = 0;

        }
    }

    // AV RIGHT
    for(y = 0; y < a_lAVHeight; y++)
    {
        ulRawIndex = y * a_lAVWidth + (a_lAVWidth>>1);

        for(x = 0; x < (a_lAVWidth>>1); x++)
        {
            ulPixelIndex = ulRawIndex + x;
            ulByteIndex = (ulPixelIndex>>3);
            ucBitIndex = (7 - (ulPixelIndex & 0x7));

			//apply alley view mask 
            if((pucAV_mask[ulByteIndex] & (1<<ucBitIndex))>>ucBitIndex)
            {
#if alALLEYVIEWDebug
                pucTestImg[ulPixelIndex] = 255;
#endif
			    //alley view tansformation
                alAlleyViewCoordinatesTransform3D(a_aeM33AVR, (FLOAT64)x, (FLOAT64)y, &dx, &dy, &dz);

			    //transformation, undistorted alley view position to distorted source front image
                alFM_v2_1_Undistorted2Distorted_Sphere(a_ptFisheyeModel, dx, dy, dz, &ox, &oy);

			    //取整數位
                wIntX = (INT16)(ox);
                wIntY = (INT16)(oy);
#if alALLEYVIEWDebug
                pucTestImg[ulPixelIndex] = pucTestImg1[wIntY * 720 + wIntX];
#endif

                //取小數位，以3bit儲存
                wDecX = (INT16)((ox - wIntX)*8);
                wDecY = (INT16)((oy - wIntY)*8);

                //prevent to out of range
                if(ox >= (ulImgWidth>>1) && oy >= 0 && ox < ulImgWidth && oy < ulImgHeight)
                {
				    //前 29bit 存整數,後 3bit 存小數
                    a_pulAVLUT_YUV[ulPixelIndex] = ((wIntY * a_lDisplayWidth + wIntX)<<6) + (wDecX<<3) + wDecY;

                    continue;
                }

                a_pulAVLUT_YUV[ulPixelIndex] = 0;

            }
        }
    }


#if alALLEYVIEWDebug // for test and debug
    ptPicGray = cvCreateImage(cvSize(a_lAVWidth, a_lAVHeight), IPL_DEPTH_8U, 1);
    memcpy(ptPicGray->imageData, pucTestImg, sizeof(UINT8)*ptPicGray->imageSize);
    sprintf_s(text, MAX_PATH, "AV_MASK.jpg");
    cvSaveImage(text, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);
    free(pucTestImg);

    
#endif

#if alALLEYVIEWDebug // for test and debug
    ptPicGray = cvCreateImage(cvSize(a_lAVWidth, a_lAVHeight), IPL_DEPTH_8U, 1);
    for (y = 0; y < a_lAVHeight; y++)
    {
        ulRawIndex = y * a_lAVWidth;

        for (x = 0; x < a_lAVWidth ; x++)
        {
            if (x == 87 && y == 195)
            {
                y = y;
            }
            ulPixelIndex = ulRawIndex + x;

            ulTableData = a_pulAVLUT_YUV[ulPixelIndex];
            if (ulTableData)
            {
                ulOffset = (ulTableData << 7) >> 13;
                cvSet2D(ptPicGray, y, x, CV_RGB(pucTestImg1[ulOffset], pucTestImg1[ulOffset], pucTestImg1[ulOffset]));
            }
            else
            {
                cvSet2D(ptPicGray, y, x, CV_RGB(0, 0, 0));
            }
        }
    }
    sprintf_s(text, MAX_PATH, "AV_MASK_full_LUT.jpg");
    cvSaveImage(text, ptPicGray, 0);
    cvReleaseImage(&ptPicGray);

    cvReleaseImage(&ptPicGraySrc);
#endif

    if (!ucInputMask)
    {
        free(pucAV_mask);
    }
}


/** 
    \brief To generate YUV422 Look Up Table according to input parameters(LUT_X,LUT_Y).
    \param LUT_X [IN] define the X-coordinate relation between source and alley view image
	\param LUT_Y [IN] define the Y-coordinate relation between source and alley view image
    \param width [IN] define the Alley View display width
	\param height [IN] define the Alley View display height 
	\AV_LUTset [OUT] YUYV422 LUT in BV partition format
    \see alPartLUT_v1_DoPartition
*/
static void GenAVLUT_XY2YUV(UINT32 * a_pulAVLUT_YUV, int width, int height, alPartLUT_v1_LUTSet_t * a_ptAV_LUTset)
{
#if 1
	//unsigned int *pAVLUT_YUV = NULL;
	int mem_budget_KBytes; 

	alPartLUT_v1_HeaderStruct * ptAVLUT = (alPartLUT_v1_HeaderStruct*) malloc(sizeof(alPartLUT_v1_HeaderStruct));
    if(ptAVLUT == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: GenAVLUT_XY2YUV::ptAVLUT");
        return;
    }

	ptAVLUT->LUTIdx = 0;
	ptAVLUT->header = (alPartLUT_v1_LUTStruct *) malloc((ptAVLUT->LUTIdx + 1) * sizeof(alPartLUT_v1_LUTStruct));

    if(ptAVLUT->header == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: GenAVLUT_XY2YUV::ptAVLUT->header");
        return;
    }

    ptAVLUT->header->singleChIdx = 1;
    ptAVLUT->header->bEnableGAE = FALSE;
	ptAVLUT->header->LUToffset = 0;
	ptAVLUT->header->OSDoffset[0] = 0;
	ptAVLUT->header->OSDoffset[1] = 0;
	ptAVLUT->header->chIdx = 0;
	ptAVLUT->header->startX = 0;
	ptAVLUT->header->startY = 0;
	ptAVLUT->header->endX = width-1;
	ptAVLUT->header->endY = height-1;
	ptAVLUT->header->size = width*height;
	ptAVLUT->header->ch = (alPartLUT_v1_SourceStruct *) malloc((ptAVLUT->header->chIdx + 1) * sizeof(alPartLUT_v1_SourceStruct));

    if(ptAVLUT->header->ch == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: GenAVLUT_XY2YUV::ptAVLUT->header->ch");
        return;
    }

    ptAVLUT->header->ch->IMoffset = 0;
	ptAVLUT->header->ch->size =  height * width;
	ptAVLUT->header->ch->startX = 0; 
	ptAVLUT->header->ch->startY = 0;
	ptAVLUT->header->ch->endX = width -1;
	ptAVLUT->header->ch->endY = height -1;
	ptAVLUT->header->ch->width =  width;
	ptAVLUT->header->ch->height = height;
	ptAVLUT->header->ch->switchInfo = 2;  
	
	mem_budget_KBytes = 50;	
	//EagleII_alAlleyView_Gen_BV_Like_LUT(LUT_X,LUT_Y, pAVLUT_YUV, width ,height); 
	alPartLUT_v1_DoPartition(ptAVLUT, a_pulAVLUT_YUV, mem_budget_KBytes*1024, a_ptAV_LUTset);
	

	free(ptAVLUT->header->ch);
	free(ptAVLUT->header);
	free(ptAVLUT);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alALLEYVIEW_InitialByCfg(
    alALLEYVIEW_Cfg * a_ptalAlleyViewCfg, 
    alCAMERAINFO_ExtrinsicParams *a_ptCamExtrinsicParams,
    alCOMMONK_CalibrationParams *a_ptCamCalibrationParams,
    alFM_v2_1_Model * a_ptFisheyeModel_v2,
    alAlleyViewParams *a_ptParams
    )
{
    UINT32 ulWidth, ulHeight;
    ulWidth  = a_ptalAlleyViewCfg->tAreaSize.lX; 
    ulHeight = a_ptalAlleyViewCfg->tAreaSize.lY;

    a_ptParams[0].ptFM_v2_Model = a_ptFisheyeModel_v2;
    a_ptParams[1].ptFM_v2_Model = a_ptFisheyeModel_v2;

    //Left alley calibration info.
	//src size
    a_ptParams[0].ulCameraPlaneHeight = a_ptCamExtrinsicParams->ulImageHeight;
    a_ptParams[0].ulCameraPlaneWidth = a_ptCamExtrinsicParams->ulImageWidth;
	//display size
    a_ptParams[0].ulDestPlaneWidth = ulWidth>>1;//left alley view is the half of display size
    a_ptParams[0].ulDestPlaneHeight = ulHeight;
    a_ptParams[0].eCameraFOV_H = a_ptFisheyeModel_v2->eFOV_H;
    a_ptParams[0].ucFisheyeModelMode = 1;

    //Right alley calibration info.
    a_ptParams[1].ulCameraPlaneHeight = a_ptCamExtrinsicParams->ulImageHeight;
    a_ptParams[1].ulCameraPlaneWidth = a_ptCamExtrinsicParams->ulImageWidth;

    a_ptParams[1].ulDestPlaneWidth = ulWidth>>1;//right alley view is the half of display size
    a_ptParams[1].ulDestPlaneHeight = ulHeight;
    a_ptParams[1].eCameraFOV_H = a_ptFisheyeModel_v2->eFOV_H;
    a_ptParams[1].ucFisheyeModelMode = 1;

    //Left
    //Crop FOV (可視範圍) (偏差修正)
    a_ptParams[0].eDestFOV_H        = a_ptalAlleyViewCfg->ulFOV;
    //viewing angle
    a_ptParams[0].eDestPitchAngle    = 90;//defult = 0
    a_ptParams[0].eDestYawAngle      = - a_ptalAlleyViewCfg->fViewingAngle;
    a_ptParams[0].eDestRollAngle     = 0;//defult = 0
    //alAlleyView 畫面偏移
    a_ptParams[0].lDestPlaneOriginOffsetX      =  a_ptalAlleyViewCfg->lVCOffsetX;//-AV_Window_Shift_X;//向右
    a_ptParams[0].lDestPlaneOriginOffsetY      =  a_ptalAlleyViewCfg->lVCOffsetY;//向下

    //Right
    //Crop FOV (可視範圍) (偏差修正)
    a_ptParams[1].eDestFOV_H        = a_ptalAlleyViewCfg->ulFOV;
    //viewing angle
    a_ptParams[1].eDestPitchAngle    = 90;//defult = 0
    a_ptParams[1].eDestYawAngle      = a_ptalAlleyViewCfg->fViewingAngle;
    a_ptParams[1].eDestRollAngle     = 0;//defult = 0
    //alAlleyView 畫面偏移
    a_ptParams[1].lDestPlaneOriginOffsetX      =  a_ptalAlleyViewCfg->lVCOffsetX;//向左
    a_ptParams[1].lDestPlaneOriginOffsetY      =  a_ptalAlleyViewCfg->lVCOffsetY;//向下

    // Current installed angle of the camera - estimated by bird view calibration.
    a_ptParams[0].eCameraPitchAngle = a_ptCamExtrinsicParams->fPitchAngle;
    a_ptParams[0].eCameraYawAngle = a_ptCamExtrinsicParams->fYawAngle;
    a_ptParams[0].eCameraRollAngle = a_ptCamExtrinsicParams->fRollAngle;
    a_ptParams[1].eCameraPitchAngle = a_ptCamExtrinsicParams->fPitchAngle;
    a_ptParams[1].eCameraYawAngle = a_ptCamExtrinsicParams->fYawAngle;
    a_ptParams[1].eCameraRollAngle = a_ptCamExtrinsicParams->fRollAngle;

    memcpy(a_ptParams[0].aeRotationMatrix, a_ptCamCalibrationParams->aeRotationMatrix[0], sizeof(a_ptCamCalibrationParams->aeRotationMatrix[0]));
    memcpy(a_ptParams[1].aeRotationMatrix, a_ptCamCalibrationParams->aeRotationMatrix[0], sizeof(a_ptCamCalibrationParams->aeRotationMatrix[0]));


	//Gen alley view transformation M3x3
    alAlleyViewM33Generator(&a_ptParams[0], a_ptParams[0].aeAV[0]);
    memcpy(a_ptParams[0].aeAV[1], a_ptParams[0].aeAV[0], sizeof(FLOAT64) * 9);
    alMATRIX_InverseNbyN(a_ptParams[0].aeAV[1], 3);

    alAlleyViewM33Generator(&a_ptParams[1], a_ptParams[1].aeAV[0]);
    memcpy(a_ptParams[1].aeAV[1], a_ptParams[1].aeAV[0], sizeof(FLOAT64) * 9);
    alMATRIX_InverseNbyN(a_ptParams[1].aeAV[1], 3);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alALLEYVIEW_GenerateLUT(
    UINT8  *a_pucAV_WorkingBuffer,
    alALLEYVIEW_Cfg * a_ptalAlleyViewCfg, 
    alAlleyViewParams *a_ptParams,
    INT32 a_lDisplayWidth, 
    UINT8 *a_pucMask,
    alPartLUT_v1_LUTSet_t * a_ptAV_LUTset
    )
{
	/*-----------Block Diagram 5. @Start---------*/
	//AV Single window display size
    UINT32 ulWidth  = a_ptalAlleyViewCfg->tAreaSize.lX; 
	UINT32 ulHeight = a_ptalAlleyViewCfg->tAreaSize.lY;
	//Crop 8 points for left and right view
	INT16 awWindowLeftCropPoints[8];
	INT16 awWindowRightCropPoints[8];
	UINT32 *pulAVLUT_YUV = NULL;

    pulAVLUT_YUV = (UINT32*)a_pucAV_WorkingBuffer;

    if(pulAVLUT_YUV == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: alALLEYVIEW_GenerateLUT::pulAVLUT_YUV");
        return;
    }

	//Crop 8 points for left view fill in
	awWindowLeftCropPoints[0] = a_ptalAlleyViewCfg->aApexPoints[0].lX;
	awWindowLeftCropPoints[1] = a_ptalAlleyViewCfg->aApexPoints[1].lX;
	awWindowLeftCropPoints[2] = a_ptalAlleyViewCfg->aApexPoints[2].lX;
	awWindowLeftCropPoints[3] = a_ptalAlleyViewCfg->aApexPoints[3].lX;
	awWindowLeftCropPoints[4] = a_ptalAlleyViewCfg->aApexPoints[0].lY;
	awWindowLeftCropPoints[5] = a_ptalAlleyViewCfg->aApexPoints[1].lY;
	awWindowLeftCropPoints[6] = a_ptalAlleyViewCfg->aApexPoints[2].lY;
	awWindowLeftCropPoints[7] = a_ptalAlleyViewCfg->aApexPoints[3].lY;
	//Crop 8 points for right view fill in
	awWindowRightCropPoints[0] = a_ptalAlleyViewCfg->aApexPoints[4].lX;
	awWindowRightCropPoints[1] = a_ptalAlleyViewCfg->aApexPoints[5].lX;
	awWindowRightCropPoints[2] = a_ptalAlleyViewCfg->aApexPoints[6].lX;
	awWindowRightCropPoints[3] = a_ptalAlleyViewCfg->aApexPoints[7].lX;
	awWindowRightCropPoints[4] = a_ptalAlleyViewCfg->aApexPoints[4].lY;
	awWindowRightCropPoints[5] = a_ptalAlleyViewCfg->aApexPoints[5].lY;
	awWindowRightCropPoints[6] = a_ptalAlleyViewCfg->aApexPoints[6].lY;
	awWindowRightCropPoints[7] = a_ptalAlleyViewCfg->aApexPoints[7].lY;

   

#if 0 // depend on 2d fish eye model
    if(a_ptalAlleyViewCfg->ucFisheyeModelMode == 0)
    {
        GenAVLUT_2D(a_aeAVL[0], a_aeAVR[0], a_ptFisheyeModel_2D, a_pCameraCfg, pulAVLUT_YUV, ulWidth, ulHeight, a_lDisplayWidth, awWindowLeftCropPoints, awWindowRightCropPoints, a_ptalAlleyViewCfg->ulSoftPixels);
    }
    else
#else
    { // depend on 3d fish eye model
        GenAVLUT_3D(
            a_pucMask,
            a_ptParams[0].aeAV[0], a_ptParams[1].aeAV[0], 
            a_ptParams[0].ptFM_v2_Model, 
            pulAVLUT_YUV, 
            ulWidth, ulHeight, 
            a_lDisplayWidth, 
            awWindowLeftCropPoints, awWindowRightCropPoints, 
            a_ptalAlleyViewCfg->ulSoftPixels
        );
    }
#endif

	//Generate LUT in BV partition format
	GenAVLUT_XY2YUV(pulAVLUT_YUV ,ulWidth, ulHeight, a_ptAV_LUTset);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alALLEYVIEW_FineTune(alALLEYVIEW_Cfg * a_ptalAlleyViewCfg, alALLEYVIEW_FineTuneParams * a_ptAV_Fine_Tune_Params, alAlleyViewParams *a_ptParams)
{
	//yaw offsets 
	a_ptParams[0].eDestYawAngle  = - a_ptalAlleyViewCfg->fViewingAngle  + a_ptAV_Fine_Tune_Params->alley_yaw_offset;
	a_ptParams[1].eDestYawAngle = a_ptalAlleyViewCfg->fViewingAngle + a_ptAV_Fine_Tune_Params->alley_yaw_offset;
	//pitch offsets
	a_ptParams[0].eDestPitchAngle  = a_ptAV_Fine_Tune_Params->alley_pitch_offset;
	a_ptParams[1].eDestPitchAngle = a_ptAV_Fine_Tune_Params->alley_pitch_offset;
	//roll offsets
	a_ptParams[0].eDestRollAngle  = a_ptAV_Fine_Tune_Params->alley_roll_offset;
	a_ptParams[1].eDestRollAngle = a_ptAV_Fine_Tune_Params->alley_roll_offset;
	//dispaly shift
	a_ptParams[0].lDestPlaneOriginOffsetY  = a_ptAV_Fine_Tune_Params->Y_shift;
	a_ptParams[1].lDestPlaneOriginOffsetY = a_ptAV_Fine_Tune_Params->Y_shift;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alALLEYVIEW_InitializeLUT(alPartLUT_v1_LUTSet_t * p_tLutSet, UINT32 ulDisplayWidth, UINT32 ulDisplayHeight)
{
	memset(p_tLutSet, 0x0, sizeof(alPartLUT_v1_LUTSet_t));
	p_tLutSet->lut_data = (UINT32 *)malloc(ulDisplayWidth * ulDisplayHeight * sizeof(UINT32));
    if(p_tLutSet->lut_data == NULL)
    {
        DEBUG_Printf("Memory Allocation Failed: alALLEYVIEW_InitializeLUT::p_tLutSet->lut_data");
        return FALSE;
    }

    return TRUE;
}

UINT32 alALLEYVIEW_QurryLUTSize()
{
    return (SIM_DEFAULT_FAV_AREA_SIZE_WIDTH*SIM_DEFAULT_FAV_AREA_SIZE_HEIGHT* sizeof(UINT32));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alALLEYVIEW_FreeLUT(alPartLUT_v1_LUTSet_t * p_tLutSet)
{
    if(p_tLutSet->lut_data != NULL)
        free(p_tLutSet->lut_data);

}

