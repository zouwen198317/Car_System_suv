
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>

#include "basedef.h"
#include "alLDCK.h"
#include "VLib.h"
#include "IMGLib.h"
#include "EagleK3_SimulateMain.h"

#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;
#endif

#define SOBEL_TH 30
#define FP_NUM 5
#define STEP 0.1

/////
// structure of the image data (test chart)
typedef struct {
    UINT8 *buf;             // pointer to the image buffer
    UINT16 width;           // image width
    UINT16 height;          // image height
    UINT16 stripe_len;      // length of stripe, note that (stripe_len >= width)
} Image_t;

// structure of measurement area
typedef struct {
    UINT16 start_row;   // start row of the area
    UINT16 start_col;   // start column of the area
    UINT16 width;       // area width, 0 means this area is not available
    UINT16 height;      // area height, 0 means this area is not available
    UINT16 Center_x;    // 對位Debug用
    UINT16 Center_y;
} Area_t;

/////

#define UP 1
#define DOWN -1
#define ICV_PUSH( Y, L, R, PREV_L, PREV_R, DIR )            \
{                                                           \
    ptBufferTail->uwCurrentRow = (UINT16)(Y);               \
    ptBufferTail->uwCurrentLeftColumn = (UINT16)(L);        \
    ptBufferTail->uwCurrentRightColumn = (UINT16)(R);       \
    ptBufferTail->uwPreviousLeftColumn = (UINT16)(PREV_L);  \
    ptBufferTail->uwPreviousRightColumn = (UINT16)(PREV_R); \
    ptBufferTail->wMovingDirection = (INT16)(DIR);          \
    if( ++ptBufferTail >= ptBufferEnd )                     \
        ptBufferTail = g_ptMOGTempRowSegmentBuffer;   \
}
#define ICV_POP( Y, L, R, PREV_L, PREV_R, DIR )             \
{                                                           \
    Y = ptBufferHead->uwCurrentRow;                         \
    L = ptBufferHead->uwCurrentLeftColumn;                  \
    R = ptBufferHead->uwCurrentRightColumn;                 \
    PREV_L = ptBufferHead->uwPreviousLeftColumn;            \
    PREV_R = ptBufferHead->uwPreviousRightColumn;           \
    DIR = ptBufferHead->wMovingDirection;                   \
    if( ++ptBufferHead >= ptBufferEnd )                     \
        ptBufferHead = g_ptMOGTempRowSegmentBuffer;   \
}
#define DenoiseBufSize 50
#define alBSD_MOG_MAX_COMPONENT_NUM		100

/** \brief Declare structure of row segment in flood fill. */
typedef struct
{
    /**  \brief The current row index for the row segment. */
    UINT16 uwCurrentRow;
    /**  \brief The current left column index for the row segment. */
    UINT16 uwCurrentLeftColumn;
    /**  \brief The current right column index for the row segment. */
    UINT16 uwCurrentRightColumn;
    /**  \brief The previous row index for the row segment. */
    UINT16 uwPreviousLeftColumn;
    /**  \brief The previous row index for the row segment. */
    UINT16 uwPreviousRightColumn;
    /**  \brief The moving direction for the row segment. */
    INT16 wMovingDirection;
} alBSD_MOG_FloodFillRowSegment;

/** \brief Declare structure of bottom analysis for each labeled component. */
typedef struct
{
    /**  \brief The bottom region for histogram analysis. */
    alRectINT32 tHistAnalysisRect;
    /**  \brief The left point for the located object under layer 0 source image coordinate. */
    alPointINT32 tObjectBottomLeftPtSrcL0;
    /**  \brief The right point for the located object under layer 0 source image coordinate. */
    alPointINT32 tObjectBottomRightPtSrcL0;
    /**  \brief The world coordinate for object bottom. */
    alPointINT32 tObjectBottomWorldPt;
    /**  \brief The left point for the located object under layer n. */
    alPointINT32 tObjectBottomLeftPtLn;
    /**  \brief The right point for the located object under layer n. */
    alPointINT32 tObjectBottomRightPtLn;

} alBSD_MOG_BottomAnalysis;

/** \brief Declare structure of labelel component. */
typedef struct
{
    /**  \brief The flag indicate whether the component is valid. */
    BOOL bValidObject;
    /**  \brief The flag indicate whether the object flow is valid. */
    BOOL bValidFlow;
    /**  \brief The layer index of the label map. */
    UINT8 ucLayerIndex;
    /**  \brief The seed point of the label. */
    alPointINT32 tSeedPoint;
    /**  \brief The label index of the component. */
    UINT32 ulLabelIndex;
    /**  \brief The number of points in the connected component. */
    UINT32 ulPointNum;
    ///**  \brief The component points structure. */
    //alPointINT32 *ptComponentPoints;
    /**  \brief The component rectangle structure. */
    alRectINT32 tComponentRect;
    /**  \brief The bottom analysis structure. */
    alBSD_MOG_BottomAnalysis tBottomAnalysis;

} alBSD_MOG_OneLabeledObject;


/** \brief Declare structure of all detected data. */
typedef struct
{
    /**  \brief The number of connected component in the image. */
    UINT32 ulComponentNum;
    /**  \brief The number of valid connected component in the image. */
    UINT32 ulValidComponentNum;
    /**  \brief The component points structure. */
    alBSD_MOG_OneLabeledObject atAllLabeledObjects[alBSD_MOG_MAX_COMPONENT_NUM];

} alBSD_MOG_AllDetectedObject;

alBSD_MOG_FloodFillRowSegment atBufferLabel[720 * 4];

/** \brief The temporary working buffer for alBSD_MOG flood fill row segment. */
static alBSD_MOG_FloodFillRowSegment *g_ptMOGTempRowSegmentBuffer = NULL;
/////

/// Global variables
Mat src, src_gray;
int thresh = 120;
int max_thresh = 255;
char* source_window = "Source image";
char* corners_window = "Corners detected";
Mat Result, Result1;

void cornerHarris_demo(int, void*);

static void PV_FloodFill(
    INT16 *a_pwDenoiseCount,
    UINT8 *a_pucLabelMap,
    UINT16 a_uwMapWidth,
    UINT16 a_uwMapHeight,
    alPointINT32 *a_ptSeedPoint,
    INT32 a_ulLabelIndex,
    UINT16 a_Connectivity,
    INT32 a_lRowSegmentBufferSize,
    alRectINT32 *a_ptComponentRect)
{
    UINT8 *pucImgPtr = (UINT8*)(a_pucLabelMap + a_ptSeedPoint->lY * a_uwMapWidth);
    INT32 lSearchPixelIndex;
    INT32 lCurrentLeft = a_ptSeedPoint->lX, lCurrentRight = a_ptSeedPoint->lX;
    INT32 lXMin = a_ptSeedPoint->lX, lXMax = a_ptSeedPoint->lX, lYMin = a_ptSeedPoint->lY, lYMax = a_ptSeedPoint->lY;
    INT32 l8Connectivity = (a_Connectivity & 255) == 8;
    INT32 lXMaxRightDiff, lXMinLeftDiff, YMaxCurrenRowDiff, YMinCurrentDiff;

    alPointINT32 atDenoiseXY[DenoiseBufSize];

    alBSD_MOG_FloodFillRowSegment *ptBufferEnd = atBufferLabel + a_lRowSegmentBufferSize;
    alBSD_MOG_FloodFillRowSegment *ptBufferHead = atBufferLabel, *ptBufferTail = atBufferLabel;

    *a_pwDenoiseCount = 0;

    UINT8 ucCurrentPixelValue = pucImgPtr[lCurrentLeft];
    pucImgPtr[lCurrentLeft] = a_ulLabelIndex;
    atDenoiseXY[*a_pwDenoiseCount].lX = lCurrentLeft;
    atDenoiseXY[*a_pwDenoiseCount++].lY = a_ptSeedPoint->lY;

    while (++lCurrentRight < a_uwMapWidth && pucImgPtr[lCurrentRight] == ucCurrentPixelValue)
    {
        pucImgPtr[lCurrentRight] = a_ulLabelIndex;
        // Record the first DenoiseBufSize pixels' coordinates for denoise
        if (*a_pwDenoiseCount < DenoiseBufSize)
        {
            atDenoiseXY[*a_pwDenoiseCount].lX = lCurrentRight;
            atDenoiseXY[*a_pwDenoiseCount++].lY = a_ptSeedPoint->lY;
        }
    }
    while (--lCurrentLeft >= 0 && pucImgPtr[lCurrentLeft] == ucCurrentPixelValue)
    {
        pucImgPtr[lCurrentLeft] = a_ulLabelIndex;
        // Record the first DenoiseBufSize pixels' coordinates for denoise
        if (*a_pwDenoiseCount < DenoiseBufSize)
        {
            atDenoiseXY[*a_pwDenoiseCount].lX = lCurrentLeft;
            atDenoiseXY[*a_pwDenoiseCount++].lY = a_ptSeedPoint->lY;
        }
    }

    //----------------------------------------
    lXMax = --lCurrentRight;
    lXMin = ++lCurrentLeft;
    ICV_PUSH(a_ptSeedPoint->lY, lCurrentLeft, lCurrentRight, lCurrentRight + 1, lCurrentRight, UP);

    while (ptBufferHead != ptBufferTail)
    {
        INT32 lSearchRangeIndex, lCurrentRow, lPrevLeft, lPrevRight, lDirection;
        ICV_POP(lCurrentRow, lCurrentLeft, lCurrentRight, lPrevLeft, lPrevRight, lDirection);

        INT32 alSearchRange[][3] =
        {
            { -lDirection, lCurrentLeft - l8Connectivity, lCurrentRight + l8Connectivity },
            { lDirection, lCurrentLeft - l8Connectivity, lPrevLeft - 1 },
            { lDirection, lPrevRight + 1, lCurrentRight + l8Connectivity }
        };

        lXMaxRightDiff = lXMax - lCurrentRight;
        lXMinLeftDiff = lCurrentLeft - lXMin;
        YMaxCurrenRowDiff = lYMax - lCurrentRow;
        YMinCurrentDiff = lCurrentRow - lYMin;
        lXMax = lXMax - ((lXMaxRightDiff & 0x8FFFFFFF) >> 31)*lXMaxRightDiff;	// if (lXMax < lCurrentRight) lXMax = lCurrentRight;
        lXMin = lXMin + ((lXMinLeftDiff & 0x8FFFFFFF) >> 31)*lXMinLeftDiff;		// if (lXMin > lCurrentLeft) lXMin = lCurrentLeft;
        lYMax = lYMax - ((YMaxCurrenRowDiff & 0x8FFFFFFF) >> 31)*YMaxCurrenRowDiff;	// if (lYMax < lCurrentRow) lYMax = lCurrentRow;
        lYMin = lYMin + ((YMinCurrentDiff & 0x8FFFFFFF) >> 31)*YMinCurrentDiff;	// if (lYMin > lCurrentRow) lYMin = lCurrentRow;

        for (lSearchRangeIndex = 0; lSearchRangeIndex < 3; lSearchRangeIndex++)
        {
            INT32 lSearchRangeLeft, lSearchRangeRight;
            lDirection = alSearchRange[lSearchRangeIndex][0];
            pucImgPtr = (UINT8*)(a_pucLabelMap + (lCurrentRow + lDirection) * a_uwMapWidth);
            lSearchRangeLeft = alSearchRange[lSearchRangeIndex][1];
            lSearchRangeRight = alSearchRange[lSearchRangeIndex][2];

            if ((unsigned)(lCurrentRow + lDirection) >= (unsigned)a_uwMapHeight || lCurrentRow + lDirection > a_ptSeedPoint->lY)
                continue;

            for (lSearchPixelIndex = lSearchRangeLeft; lSearchPixelIndex <= lSearchRangeRight; lSearchPixelIndex++)
            {
                if ((unsigned)lSearchPixelIndex < (unsigned)a_uwMapWidth && pucImgPtr[lSearchPixelIndex] == ucCurrentPixelValue)
                {
                    int j = lSearchPixelIndex;
                    pucImgPtr[lSearchPixelIndex] = a_ulLabelIndex;
                    // Record the first DenoiseBufSize pixels' coordinates for denoise
                    if (*a_pwDenoiseCount < DenoiseBufSize)
                    {
                        atDenoiseXY[*a_pwDenoiseCount].lX = lSearchPixelIndex;
                        atDenoiseXY[*a_pwDenoiseCount++].lY = lCurrentRow + lDirection;
                    }

                    while (--j >= 0 && pucImgPtr[j] == ucCurrentPixelValue)
                    {
                        pucImgPtr[j] = a_ulLabelIndex;
                        // Record the first DenoiseBufSize pixels' coordinates for denoise
                        if (*a_pwDenoiseCount < DenoiseBufSize)
                        {
                            atDenoiseXY[*a_pwDenoiseCount].lX = j;
                            atDenoiseXY[*a_pwDenoiseCount++].lY = lCurrentRow + lDirection;
                        }
                    }

                    while (++lSearchPixelIndex < a_uwMapWidth && pucImgPtr[lSearchPixelIndex] == ucCurrentPixelValue)
                    {
                        pucImgPtr[lSearchPixelIndex] = a_ulLabelIndex;
                        // Record the first DenoiseBufSize pixels' coordinates for denoise
                        if (*a_pwDenoiseCount < DenoiseBufSize)
                        {
                            atDenoiseXY[*a_pwDenoiseCount].lX = lSearchPixelIndex;
                            atDenoiseXY[*a_pwDenoiseCount++].lY = lCurrentRow + lDirection;
                        }
                    }

                    ICV_PUSH(lCurrentRow + lDirection, j + 1, lSearchPixelIndex - 1, lCurrentLeft, lCurrentRight, -lDirection);
                }
            }
        }
    }

    a_ptComponentRect->lLeft = lXMin;
    a_ptComponentRect->lTop = lYMin;
    a_ptComponentRect->lRight = lXMax;
    a_ptComponentRect->lBottom = lYMax;
}

static void PV_LabelingOneMap(UINT8 a_ucLayerIndex,
    UINT8 *a_pucLabelMap,
    UINT16 a_uwMapWidth,
    UINT16 a_uwMapHeight,
    UINT8 ucLabelConnectivity,
    UINT32 *a_pulLabelIndex,
    UINT32 *a_pulComponentNum,
    alBSD_MOG_AllDetectedObject *a_ptAllConnectedComponent)
{
    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    INT32 lRowIdx = 0, lColIdx = 0;
    UINT32 ulComponentIndex;
    UINT32 ulPixelRowIndex = 0, ulPixelIndex = 0;
    UINT32 ulRectRowIdx = 0, ulRectColIdx = 0, ulRectLeft = 0, ulRectTop = 0, ulRectRight = 0, ulRectBottom = 0;
    UINT32 ulRectPixelRowIndex = 0, ulRectPixelIndex = 0;
    alRectINT32 tComponentRect;
    alPointINT32 tSeedPoint;
    UINT32 ulConnectedPointNum = 0;
    alBSD_MOG_OneLabeledObject *ptOneLabeledComponent;
    INT32 lComponentWidth = 0, lComponentHeight = 0;
    INT32 lTempComponentWidth = 0, lTempComponentHeight = 0, lTempComponentArea = 0, lMinComponentArea = 1000000000;
    UINT32 ulMinComponentIndex = 0;
    // INT32 *plObjWidthTHTable = a_ptLabelingParam->plObjectWidthTHTable;
    INT16 wDenoiseCount = 0;
    
    for (lRowIdx = a_uwMapHeight - 1; lRowIdx >= 0; lRowIdx--)
    {
        ulPixelRowIndex = lRowIdx * a_uwMapWidth;

        for (lColIdx = a_uwMapWidth - 1 ; lColIdx >= 0 ; lColIdx--)
        {
            ulPixelIndex = ulPixelRowIndex + lColIdx;
            if (a_pucLabelMap[ulPixelIndex] != 1)
                continue;
            tSeedPoint.lX = lColIdx;
            tSeedPoint.lY = lRowIdx;
            ulConnectedPointNum = 0;

            // flood fill algorithm
            PV_FloodFill(
                &wDenoiseCount,
                a_pucLabelMap,
                a_uwMapWidth,
                a_uwMapHeight,
                &tSeedPoint,
                *a_pulLabelIndex,
                ucLabelConnectivity,
                a_uwMapWidth*4,
                &tComponentRect
            );

            ulRectLeft = tComponentRect.lLeft;
            ulRectTop = tComponentRect.lTop;
            ulRectRight = tComponentRect.lRight;
            ulRectBottom = tComponentRect.lBottom;
            for (ulRectRowIdx = ulRectTop; ulRectRowIdx < ulRectBottom; ulRectRowIdx++)
            {
                ulRectPixelRowIndex = ulRectRowIdx * a_uwMapWidth;
                for (ulRectColIdx = ulRectLeft; ulRectColIdx < ulRectRight; ulRectColIdx++)
                {
                    ulRectPixelIndex = ulRectPixelRowIndex + ulRectColIdx;
                    if (a_pucLabelMap[ulRectPixelIndex] != *a_pulLabelIndex)
                        continue;

                    ulConnectedPointNum++;
                }
            }

            // 6500(c) Check for component size
            lComponentWidth = ulRectRight - ulRectLeft + 1;
            lComponentHeight = ulRectBottom - ulRectTop + 1;
            ////if (lComponentWidth > plObjWidthTHTable[ulRectBottom] && lComponentHeight > plObjWidthTHTable[ulRectBottom])
            ////{

            //(210-c) Denoise small size groups
            if (wDenoiseCount > DenoiseBufSize - 1)
            {
                // 6500(d) Check component number
                if (*a_pulComponentNum < alBSD_MOG_MAX_COMPONENT_NUM)
                {
                    // (6540) Update the component to the list
                    ptOneLabeledComponent = &(a_ptAllConnectedComponent->atAllLabeledObjects[*a_pulComponentNum]);
                    ptOneLabeledComponent->bValidObject = TRUE;
                    ptOneLabeledComponent->bValidFlow = TRUE;
                    ptOneLabeledComponent->ucLayerIndex = a_ucLayerIndex;
                    ptOneLabeledComponent->tSeedPoint.lX = tSeedPoint.lX;
                    ptOneLabeledComponent->tSeedPoint.lY = tSeedPoint.lY;
                    ptOneLabeledComponent->ulLabelIndex = *a_pulLabelIndex;
                    ptOneLabeledComponent->ulPointNum = ulConnectedPointNum;
                    ptOneLabeledComponent->tComponentRect.lLeft = ulRectLeft;
                    ptOneLabeledComponent->tComponentRect.lTop = ulRectTop;
                    ptOneLabeledComponent->tComponentRect.lRight = ulRectRight;
                    ptOneLabeledComponent->tComponentRect.lBottom = ulRectBottom;
                    (*a_pulLabelIndex)++;
                    (*a_pulComponentNum)++;
                }
                else
                {
                    // (6530) Find the smallest component and replace with the new one
                    for (ulComponentIndex = 0; ulComponentIndex < alBSD_MOG_MAX_COMPONENT_NUM; ulComponentIndex++)
                    {
                        lTempComponentWidth = a_ptAllConnectedComponent->atAllLabeledObjects[ulComponentIndex].tComponentRect.lRight - a_ptAllConnectedComponent->atAllLabeledObjects[ulComponentIndex].tComponentRect.lLeft + 1;
                        lTempComponentHeight = a_ptAllConnectedComponent->atAllLabeledObjects[ulComponentIndex].tComponentRect.lBottom - a_ptAllConnectedComponent->atAllLabeledObjects[ulComponentIndex].tComponentRect.lTop + 1;
                        lTempComponentWidth = lTempComponentWidth << a_ptAllConnectedComponent->atAllLabeledObjects[ulComponentIndex].ucLayerIndex;
                        lTempComponentHeight = lTempComponentHeight << a_ptAllConnectedComponent->atAllLabeledObjects[ulComponentIndex].ucLayerIndex;
                        lTempComponentArea = lTempComponentWidth * lTempComponentHeight;
                        if (lTempComponentArea < lMinComponentArea)
                        {
                            lMinComponentArea = lTempComponentArea;
                            ulMinComponentIndex = ulComponentIndex;
                        }
                    }
                    // If current component is larger than the minimum component, replace it
                    if ((lComponentWidth << a_ucLayerIndex) * (lComponentHeight << a_ucLayerIndex) > lMinComponentArea)
                    {
                        // Update the component
                        ptOneLabeledComponent = &(a_ptAllConnectedComponent->atAllLabeledObjects[ulMinComponentIndex]);
                        ptOneLabeledComponent->bValidObject = TRUE;
                        ptOneLabeledComponent->bValidFlow = TRUE;
                        ptOneLabeledComponent->ucLayerIndex = a_ucLayerIndex;
                        ptOneLabeledComponent->tSeedPoint.lX = tSeedPoint.lX;
                        ptOneLabeledComponent->tSeedPoint.lY = tSeedPoint.lY;
                        ptOneLabeledComponent->ulLabelIndex = *a_pulLabelIndex;
                        ptOneLabeledComponent->ulPointNum = ulConnectedPointNum;
                        ptOneLabeledComponent->tComponentRect.lLeft = ulRectLeft;
                        ptOneLabeledComponent->tComponentRect.lTop = ulRectTop;
                        ptOneLabeledComponent->tComponentRect.lRight = ulRectRight;
                        ptOneLabeledComponent->tComponentRect.lBottom = ulRectBottom;
                    }
                    (*a_pulLabelIndex)++;

                    if (*a_pulComponentNum >= alBSD_MOG_MAX_COMPONENT_NUM)
                    {
                        DEBUG_Printf("Number of labeled components exceed the maximun value (%d).\n", alBSD_MOG_MAX_COMPONENT_NUM);
                        return;
                    }
                    assert(*a_pulComponentNum < alBSD_MOG_MAX_COMPONENT_NUM);
                }
            }
            ////}
            else
            {
                //(212) Clear labeled pixels in Foreground Map
                /*for (INT16 i = 0; i <= wDenoiseCount; i++)
                *(a_pucLabelMap + atDenoiseXY[i].lY*a_uwMapWidth + atDenoiseXY[i].lX) = 0;*/
                (*a_pulLabelIndex)++;
            }
        }
    }
}

void fast(void)
{
    Mat source, source_gray;

    source = imread("./Noline1_enhance.jpg", 1);
    cvtColor(source, source_gray, CV_BGR2GRAY);

    int threshold = 60;
    vector<KeyPoint> keypoints;


    FAST(source_gray, keypoints, threshold, true);

    drawKeypoints(source_gray, keypoints, source_gray, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imwrite("./CornerRectifiedImage_enhance.jpg", source_gray);

}

void fast2(char *a_pcIN, char *a_pcOUT)
{
    Mat source, source_gray;
    int threshold = 50;
    vector<KeyPoint> keypoints;

    source = imread(a_pcIN, 1);
#if 0
    cvtColor(source, source_gray, CV_BGR2GRAY);
    FAST(source_gray, keypoints, threshold, true);
    drawKeypoints(source_gray, keypoints, source_gray, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imwrite(a_pcOUT, source_gray);
#else
    FAST(source, keypoints, threshold, true);
    drawKeypoints(source, keypoints, source, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imwrite(a_pcOUT, source);
#endif
}

void fast3(Mat source, char *a_pcOUT)
{
    Mat source_gray;
    int threshold = 50;
    vector<KeyPoint> keypoints;


    FAST(source, keypoints, threshold, true);
    drawKeypoints(source, keypoints, source, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imwrite(a_pcOUT, source);

}

/** @function cornerHarris_demo */
void cornerHarris_demo(int, void*)
{

    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros(src.size(), CV_32FC1);

    /// Detector parameters
    int blockSize = 5;
    int apertureSize = 3;
    double k = 0.04;

    /// Detecting corners
    cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

    /// Normalizing
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    /// Drawing a circle around corners
    for (int j = 0; j < dst_norm.rows; j++)
    {
        for (int i = 0; i < dst_norm.cols; i++)
        {
            if ((int)dst_norm.at<float>(j, i) > thresh)
            {
                // circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
                // circle(src, Point(i, j), 5, Scalar(0), 2, 8, 0);
            }
        }
    }
    /// Showing the result
    // namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
    // imshow(corners_window, dst_norm_scaled);

    dst_norm_scaled.copyTo(Result);
    dst_norm.copyTo(Result1);
}

int harris_test(void)
{
    /// Load source image and convert it to gray
    // src = imread("./chart.png", 1);
    // src = imread("./testLDC.BMP", 1);
    src = imread("./Noline1_enhance.jpg", 1);
    cvtColor(src, src_gray, CV_BGR2GRAY);


    /// Create a window and a trackbar
    // namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    // createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);

    cornerHarris_demo(0, 0);

    // 
    /// Drawing a circle around corners
    for (int j = 0; j < Result.rows; j++)
    {
        for (int i = 0; i < Result.cols; i++)
        {
            if ((int)Result1.at<float>(j, i) > thresh)
            {
                circle(src, Point(i, j), 5, Scalar(255, 0, 0), 2, 8, 0);
            }
        }
    }
    //

    // imshow(source_window, src);
    imwrite("./HarrisCorner.jpg", src);

    // waitKey(0);
    return(0);
}


void Test_HoughTransform_2(IplImage *a_ptImgIN, IplImage *a_ptImgHough)
{
    INT32 lRow = 0, lColumn = 0;
    INT32 lR = 0, lAngle = 0;
    INT32 lx = 0, ly = 0, lCnt = 0, lSampleCnt = 0;
    FLOAT32 fRmax = 0;
    FLOAT64 eAngle = 0;
    UINT32 *pulHoughTmp = NULL;
    Mat tHoughOut;
    alPointINT32 atFP[FP_NUM] = { 0 };

    harris_test();

    lColumn = a_ptImgIN->width;
    lRow = a_ptImgIN->height;
    fRmax = (FLOAT32)sqrt(lRow*lRow + lColumn*lColumn);

    tHoughOut = Mat::zeros(Size(180, alROUND(fRmax * 2 + 1)), CV_32SC1);

#if 1

#if 1
    atFP[0].lX = 96;
    atFP[1].lX = 96;
    atFP[2].lX = 96;
    atFP[3].lX = 96;
    atFP[4].lX = 96;

    atFP[0].lY = 97;
    atFP[1].lY = 193;
    atFP[2].lY = 288;
    atFP[3].lY = 385;
    atFP[4].lY = 480;
#else
    atFP[0].lX = 96;
    atFP[1].lX = 193;
    atFP[2].lX = 288;
    atFP[3].lX = 385;
    atFP[4].lX = 480;

    atFP[0].lY = 97;
    atFP[1].lY = 97;
    atFP[2].lY = 97;
    atFP[3].lY = 97;
    atFP[4].lY = 97;
#endif
    
    for (lCnt = 0; lCnt < FP_NUM; lCnt++)
    {
        for (lAngle = 0; lAngle < 180; lAngle++) // for each theta
        {
            eAngle = lAngle;
            while (eAngle < lAngle + 1)
            {
                lR = (INT32)(atFP[lCnt].lY * sin(eAngle*alPI / 180) + atFP[lCnt].lX * cos(eAngle*alPI / 180));    // compute r
                lR = alROUND_N(lR + fRmax);                                             // shift r to positive value
                tHoughOut.at<INT32>(lR, alROUND(lAngle)) = 255;                                      // accumulation
                eAngle = eAngle + STEP;
            }
        }
    }
    imwrite("./HoughImage_test.jpg", tHoughOut);
#endif

#if 0
    for (ly = 0; ly < lRow; ly++)
    {
        for (lx = 0; lx < lColumn; lx++)
        {
            if (a_ptImgIN->imageData[ly*lColumn + lx] > SOBEL_TH)
            { // EDGE POINTS
                for (lAngle = 0; lAngle < 180; lAngle++) // for each theta
                {
                    lR = (INT32)(ly*sin(lAngle*alPI / 180) + lx*cos(lAngle*alPI / 180));    // compute r
                    lR = alROUND_N(lR + fRmax);                                             // shift r to positive value
                    tHoughOut.at<INT32>(lR, lAngle)++;                                      // accumulation
                }
            }
        }
    }

    normalize(tHoughOut, tHoughOut, 255.0, 0.0, NORM_MINMAX);
    imwrite("./HoughImage.jpg", tHoughOut);
#endif

}

void Test_LDC(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder
    )
{
    IplImage *ptImgIN = NULL;
    IplImage *ptImgHough = NULL;
    IplImage *ptSobelImg_16S_X = NULL;
    IplImage *ptSobelImg_8U_X = NULL;
    IplImage *ptSobelImg_16S_Y = NULL;
    IplImage *ptSobelImg_8U_Y = NULL;
    IplImage *ptSobelImg = NULL;

    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucTEST =NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL];
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL];
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    char acFP_FilePath[MAX_PATH] = { 0 };
    alLDCK_Data tData;

    int lVlibOot = 0, lX = 0, lY = 0, lCnt =0;
    ///
    unsigned short width = 0;
    unsigned short height = 0;
    ///

    wcstombs(acFP_FilePath, a_pwcSrcImageFolder, MAX_PATH);

    // fast();
    // fast2("./Noline1_enhance.jpg", "./CornerRectifiedImage_enhance.jpg");
    
    //
    ptImgIN = cvLoadImage("./Noline1.BMP", CV_LOAD_IMAGE_GRAYSCALE);
    pucTEST = (UINT8*)ptImgIN->imageData;
    COMMONK_EnhanceImage(ptImgIN->width, ptImgIN->height, pucTEST, pucTEST);
    cvSaveImage("IN_enhance.jpg", ptImgIN, 0);
    cvReleaseImage(&ptImgIN);
    //

    // ptImgIN = cvLoadImage("./Noline1_enhance.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    ptImgIN = cvLoadImage("./IN_enhance.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    cvSaveImage("IN.jpg", ptImgIN, 0);

    

    ptSobelImg_16S_X = cvCreateImage(cvGetSize(ptImgIN), IPL_DEPTH_16S, 1);
    ptSobelImg_8U_X = cvCreateImage(cvGetSize(ptImgIN), IPL_DEPTH_8U, 1);

    ptSobelImg_16S_Y = cvCreateImage(cvGetSize(ptImgIN), IPL_DEPTH_16S, 1);
    ptSobelImg_8U_Y = cvCreateImage(cvGetSize(ptImgIN), IPL_DEPTH_8U, 1);

    ptSobelImg = cvCreateImage(cvGetSize(ptImgIN), IPL_DEPTH_8U, 1);


    IplImage *ptLogImg =NULL;
#if 0 // test VLIB
    char acmaskX[9] = {-1,0,1,-2,0,2,-1,0,1};
    char acmaskY[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

    width = ptImgIN->width;
    height = ptImgIN->height;
    UINT8 *pucInBlk = NULL;
    pucInBlk = (UINT8*)ptImgIN->imageData;
    short wk = 1310; // 0.04 * 2^15
    FLOAT32 fK = 0.04, fT = 0;

    short *pBufGradX = (short*)malloc(width*height * sizeof(short));
    short *pBufGradY = (short*)malloc(width*height * sizeof(short));
    short *pBufMag = (short*)malloc(width*height * sizeof(short));
    short *pHarrisScore = (short*)malloc(width*height * sizeof(short));
    UINT8 *pucScratchBuffer = (UINT8*)malloc(width*100 * sizeof(UINT8));
    UINT8 *pucTestBuffer = (UINT8*)malloc(width * height * sizeof(UINT8));

    
#if 0 // 1x3 mask
    lVlibOot =  VLIB_xyGradientsAndMagnitude(
        pucInBlk, pBufGradX, pBufGradY, pBufMag,
        width, height
    );
#else // 3x3 mask 

    for(lCnt = 0 ; lCnt < height-2 ; lCnt++)
    {
        IMG_conv_3x3_i8_c16s_altek
            (
            pucInBlk + lCnt*width, // const unsigned char *restrict  imgin_ptr,
            pBufGradX + lCnt*width + width + 1, // short               *restrict imgout_ptr,
            width,
            width,
            acmaskX,
            2
        );
    }

    for (lCnt = 0; lCnt < height - 2; lCnt++)
    {
        IMG_conv_3x3_i8_c16s_altek
            (
            pucInBlk + lCnt*width, // const unsigned char *restrict  imgin_ptr,
            pBufGradY + lCnt*width + width + 1, // short               *restrict imgout_ptr,
            width,
            width,
            acmaskY,
            2
            );
    }
    
#endif
    for (lY = 0; lY < height; lY++)
    {
        for (lX = 0; lX < width; lX++)
        {
            pucTestBuffer[lY*width + lX] = (UINT8)abs(pBufGradX[lY*width + lX]);
        }
    }

    memcpy(ptSobelImg_8U_X->imageData, pucTestBuffer, sizeof(UINT8)*ptSobelImg_8U_X->imageSize);
    cvSaveImage("SobelX_Vlib.jpg", ptSobelImg_8U_X, 0);

    for (lY = 0; lY < height; lY++)
    {
        for (lX = 0; lX < width; lX++)
        {
            pucTestBuffer[lY*width + lX] = (UINT8)abs(pBufGradY[lY*width + lX]);
        }
    }

    memcpy(ptSobelImg_8U_X->imageData, pucTestBuffer, sizeof(UINT8)*ptSobelImg_8U_X->imageSize);
    cvSaveImage("SobelY_Vlib.jpg", ptSobelImg_8U_X, 0);

#if 0
    for (lY = 0; lY < height; lY++)
    {
        for (lX = 0; lX < width; lX++)
        {
            pucTestBuffer[lY*width + lX] = (UINT8)abs(pBufMag[lY*width + lX]);
        }
    }

    memcpy(ptSobelImg_8U_X->imageData, pucTestBuffer, sizeof(UINT8)*ptSobelImg_8U_X->imageSize);
    cvSaveImage("Mag_Vlib.jpg", ptSobelImg_8U_X, 0);
#endif

    wk = 3000; // 0.04 * 2^15
    lVlibOot = VLIB_harrisScore_7x7(
        pBufGradX, pBufGradY,
        width, height,
        pHarrisScore,
        wk, pucScratchBuffer
    );

    for (lY = 0; lY < height; lY++)
    {
        for (lX = 0; lX < width; lX++)
        {
            pucTestBuffer[lY*width + lX] = (pHarrisScore[lY*width + lX] > 24000) ? 255 : 0;
        }
    }

    memcpy(ptSobelImg_8U_X->imageData, pucTestBuffer, sizeof(UINT8)*ptSobelImg_8U_X->imageSize);
    cvSaveImage("Hariss_Raw_Vlib.jpg", ptSobelImg_8U_X, 0);

#if 1 // log corner
    ptLogImg = cvLoadImage("./Noline1_enhance.jpg", CV_LOAD_IMAGE_COLOR);
    for (lY = 0; lY < height; lY++)
    {
        for (lX = 0; lX < width; lX++)
        {
            if (pucTestBuffer[lY*width + lX])
            {
                cvSet2D(ptLogImg, lY, lX, cvScalar(0, 0, 255));
            }
        }
    }
    cvSaveImage("Hariss_RawLOG_Vlib.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);
#endif

#if 0
    lVlibOot = VLIB_nonMaxSuppress_7x7_S16(
        pHarrisScore,
        width, height,
        30000,
        pucTestBuffer
    );

    memcpy(ptSobelImg_8U_X->imageData, pucTestBuffer, sizeof(UINT8)*ptSobelImg_8U_X->imageSize);
    cvSaveImage("Hariss_Vlib.jpg", ptSobelImg_8U_X, 0);
#else // 侵蝕
    /*UINT8 *pucTestBuffer1 = (UINT8*)malloc(width * height * sizeof(UINT8));
    VLIB_erode_bin_square(
        pucTestBuffer,
        pucTestBuffer1,
        height,
        width
    );
    memcpy(ptSobelImg_8U_X->imageData, pucTestBuffer1, sizeof(UINT8)*ptSobelImg_8U_X->imageSize);*/

    cvErode(ptSobelImg_8U_X, ptSobelImg_8U_X, 0, 1);//腐蝕(IplImage*,IplImage*,0,腐蝕次數)
    cvSaveImage("Hariss_erode.jpg", ptSobelImg_8U_X, 0);
    // free(pucTestBuffer1);
#endif
    free(pBufGradX);
    free(pBufGradY);
    free(pBufMag);
    free(pHarrisScore);
    free(pucScratchBuffer);
    free(pucTestBuffer);

#endif

#if 0
    vector<KeyPoint> keypoints;
    Mat mat(ptImgIN);

    FAST(mat, keypoints, 50, true);
    drawKeypoints(mat, keypoints, mat, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imwrite("./test_fast.jpg", mat);

#endif

    

    
#if 1
    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // Load Default
    EAGLEK3_LoadFM_BV_CfgByDefault(EAGLEK3_NUM_BV_CHANNEL, atFM_BV);

    // Load conifg data from INI file
    EAGLEK3_LoadFM_BV_CfgByINI(awcConfigFilePath, EAGLEK3_NUM_BV_CHANNEL, atFM_BV);

    // Load information of calibration field.
    aulFMBufferSize[EAGLEK3_BV_LEFT] = EAGLEK3_QueryFM_BV_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_LEFT]);
    aulFMBufferSize[EAGLEK3_BV_RIGHT] = EAGLEK3_QueryFM_BV_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_RIGHT]);
    aulFMBufferSize[EAGLEK3_BV_FRONT] = EAGLEK3_QueryFM_BV_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_FRONT]);
    aulFMBufferSize[EAGLEK3_BV_BACK] = EAGLEK3_QueryFM_BV_WorkingBufferSizeSingle(&atFM_BV[EAGLEK3_BV_BACK]);

    // alloc FM  Buffer
    apucFMBuffer[EAGLEK3_BV_LEFT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_LEFT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_RIGHT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_RIGHT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_FRONT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_FRONT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_BACK] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_BACK] * sizeof(UINT8));

    // Initial By Cfg Data
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_LEFT], &atFM_v2_Model[EAGLEK3_BV_LEFT], apucFMBuffer[EAGLEK3_BV_LEFT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_RIGHT], &atFM_v2_Model[EAGLEK3_BV_RIGHT], apucFMBuffer[EAGLEK3_BV_RIGHT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_FRONT], &atFM_v2_Model[EAGLEK3_BV_FRONT], apucFMBuffer[EAGLEK3_BV_FRONT]);
    alFM_v2_1_InitialByCfgDataExternalBuffer(&atFM_BV[EAGLEK3_BV_BACK], &atFM_v2_Model[EAGLEK3_BV_BACK], apucFMBuffer[EAGLEK3_BV_BACK]);

    // Test DeFishEye Image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, (FLOAT32)0.4, atFM_v2_Model);

    memset(&tData, 0, sizeof(alLDCK_Data));
    alLDCK_LoadIdealCornerByINI("./alFP_LDC.ini", &tData);

    alLDCK_LoadCornerByINI("./alFP_LDC.ini", &tData);

    alLDCK_LoadMatrixFlagByINI("./alFP_LDC.ini", &tData);

    alLDCK_LoadCornerFlagByINI("./alFP_LDC.ini", &tData);

#if 1 // log corner
    ptLogImg = cvLoadImage("./Noline1.BMP", CV_LOAD_IMAGE_COLOR);
    for (lY = 0; lY < alLDCK_CORNER_NUM; lY++)
    {
        cvCircle(ptLogImg, cvPoint((INT32)tData.atCorner[lY].eX, (INT32)tData.atCorner[lY].eY), 3, CV_RGB(255, 0, 0), 2, CV_AA, 0);
    }
    cvSaveImage("Corner_Real.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);

    ptLogImg = cvLoadImage("./pattern2.JPG", CV_LOAD_IMAGE_COLOR);
    for (lY = 0; lY < alLDCK_CORNER_NUM; lY++)
    {
        cvCircle(ptLogImg, cvPoint((INT32)tData.atCornerIdeal[lY].eX, (INT32)tData.atCornerIdeal[lY].eY), 3, CV_RGB(255, 0, 0), 2, CV_AA, 0);
    }
    cvSaveImage("Corner_Ideal.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);

    ptLogImg = cvLoadImage("./pattern2.JPG", CV_LOAD_IMAGE_COLOR);
    for (lY = 0; lY < alLDCK_CORNER_NUM; lY++)
    {
        if (!tData.aucCornerFlag_H_Matrix[lY])
        {
            cvCircle(ptLogImg, cvPoint((INT32)tData.atCornerIdeal[lY].eX, (INT32)tData.atCornerIdeal[lY].eY), 3, CV_RGB(0, 255, 0), 2, CV_AA, 0);
        }
    }
    cvSaveImage("Corner_ForHMatrix.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);
#endif

    clock_t t; 
    t = clock();
    alLDCK_Main((UINT8 *)ptImgIN->imageData, &atFM_v2_Model[EAGLEK3_BV_FRONT], &tData);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

#if 1
    ptLogImg = cvLoadImage("./RectifiedImage.JPG", CV_LOAD_IMAGE_COLOR);
    for (lY = 0; lY < alLDCK_CORNER_NUM; lY++)
    {
        cvCircle(ptLogImg, cvPoint((INT32)tData.atCornerIdeal[lY].eX, (INT32)tData.atCornerIdeal[lY].eY), 25, CV_RGB(0, 255, 0), 1, CV_AA, 0);
    }
    cvSaveImage("RectifiedImage_DetectTest.jpg", ptLogImg, 0);
    cvReleaseImage(&ptLogImg);
#endif

    // free FM Buffer
    free(apucFMBuffer[EAGLEK3_BV_LEFT]);
    free(apucFMBuffer[EAGLEK3_BV_RIGHT]);
    free(apucFMBuffer[EAGLEK3_BV_FRONT]);
    free(apucFMBuffer[EAGLEK3_BV_BACK]);
#endif
    // fast2("RectifiedImage.jpg", "CornerRectifiedImage.jpg");

#if 0 // Gradient test
    // Gradient X
    cvSobel(ptImgIN, ptSobelImg_16S_X, 1, 0, 3);
    cvConvertScaleAbs(ptSobelImg_16S_X, ptSobelImg_8U_X, 1, 0);
    cvSaveImage("SobelX.jpg", ptSobelImg_8U_X, 0);

    // Gradient Y
    cvSobel(ptImgIN, ptSobelImg_16S_Y, 0, 1, 3);
    cvConvertScaleAbs(ptSobelImg_16S_Y, ptSobelImg_8U_Y, 1, 0);
    cvSaveImage("SobelY.jpg", ptSobelImg_8U_Y, 0);

    // Total Gradient (approximate)
    cvAddWeighted(ptSobelImg_8U_X, 0.5, ptSobelImg_8U_Y, 0.5, 0, ptSobelImg);

    cvSaveImage("Sobel.jpg", ptSobelImg, 0);
#endif

    harris_test();

    // Test_HoughTransform_2(ptSobelImg, NULL);

    cvReleaseImage(&ptImgIN);
    cvReleaseImage(&ptSobelImg);
    cvReleaseImage(&ptSobelImg_16S_X);
    cvReleaseImage(&ptSobelImg_16S_Y);
    cvReleaseImage(&ptSobelImg_8U_X);
    cvReleaseImage(&ptSobelImg_8U_Y);

}

static void Calculate_MTF_withPositionShift(UINT16 *pMTF_value, Image_t *pImg, Area_t *pArea)
{
    UINT8 *pucImage;                 /*Pointer of where area begins*/
    int i;                   /*Loop variable*/
    int row, col;
    int pixel_num;
    int R = 0, G = 0, B = 0;
    int Y_value;
    int Y_histogram[256];     /*Y_Histogram*/
    int sum;                  /*Variable for Y_Histogram statisic*/
    int black = 0, white = 0;         /*Black :25% from Ymean 0 in Y_histogram, White: 25% from Ymean 255 in Y_histogram*/
    //int image[20][20]={0};    /*Blur image structre(Unuse now)*/
    int position_shift[13][2] = { { 0, 0 }, { 1, -1 }, { 1, 1 }, { -1, 1 }, { -1, -1 }, { 0, -2 }, { 2, 2 }, { 2, 0 }, { 2, 2 }, { 0, 2 }, { -2, 2 }, { -2, 0 }, { -2, -2 } }; /*Postion_Shift table*/
    int start_row, start_col;  /*Coordinate area begins in image plane*/
    int min = 100, max = 0, avg = 0;  /*Temp variables for MTF statisic*/
    UINT16 MTF[13] = { 0 };       /*Log MTF in different position*/
    float fMTF_val;           /*Final MTF result*/


    //Get start position in this phase
    for (i = 0; i<13; i++){
        start_col = pArea->start_col + position_shift[i][0];
        start_row = pArea->start_row + position_shift[i][1];

        //Set Y_histogram whole of zero
        memset(Y_histogram, 0x0, 256 * sizeof(int));

        for (row = 0; row < pArea->height; row++)
        {
            pucImage = pImg->buf + ((start_row + row)*pImg->stripe_len + start_col);
            for (col = 1; col < pArea->width; col++)
            {
                /*Calulate Y_mean and log to Y_histogram*/
                Y_value = *(pucImage + col);
                Y_histogram[Y_value]++;
            }
        }
      
        pixel_num = pArea->width * pArea->height;

        int cal_num = (int)(pixel_num*0.25);
        int YB = 0, YW = 0;
        int count = 0;
        /*get the Y value for 'black' 25% from Ymean 0 in Y_histogram*/
        sum = 0;
        int sub = 0;

        for (Y_value = 0; Y_value<256; Y_value++) {
            sum += Y_histogram[Y_value];
            YB += Y_histogram[Y_value] * Y_value;

            if (sum > cal_num) {
                break;
            }
        }
        YB = YB / sum;

        /*get the Y value for 'white' 25% from Ymean 255 in Y_histogram*/
        sum = 0;
        sub = 0;
        for (Y_value = 255; Y_value >= 0; Y_value--) {
            sum += Y_histogram[Y_value];
            YW += Y_histogram[Y_value] * Y_value;

            if (sum > cal_num) {
                break;
            }
        }
        YW = YW / sum;

        if (0 == YW + YB)
            fMTF_val = 0.0;  // avoid 'divide by zero' case
        else
            fMTF_val = ((float)(YW - YB) * 100) / (float)(YW + YB);

        MTF[i] = (UINT16)(fMTF_val + 0.5);

        //For statibility,discard max and min of MTF
        if (MTF[i]<min){
            min = MTF[i];
        }
        if (MTF[i]>max){
            max = MTF[i];
        }
        avg += MTF[i];
    }

    *pMTF_value = (UINT16)((float)(avg - min - max) / (float)11 + 0.5);
}

void Test_test()
{
    UINT16 uwMTF = 0;
    Image_t tImg = { 0 };
    Area_t tArea = { 0 };
    char acFilePath_in[MAX_PATH] = "./Test/H102_200_Side.bmp";
    char acFilePath_out[MAX_PATH] = "./Test/H102_200_Side_Out_V.bmp";

    IplImage *ptLogImg = NULL;
    IplImage *ptLogImg_1 = NULL;
    ptLogImg = cvLoadImage(acFilePath_in, CV_LOAD_IMAGE_GRAYSCALE);
    ptLogImg_1 = cvLoadImage(acFilePath_in, CV_LOAD_IMAGE_COLOR);

    tImg.buf = (UINT8*)ptLogImg->imageData;
    tImg.width = ptLogImg->width;
    tImg.height = ptLogImg->height;
    tImg.stripe_len = ptLogImg->widthStep;

    tArea.Center_x = tImg.width >> 1;
    tArea.Center_y = tImg.height >> 1;
    tArea.height = 20;
    tArea.width = 20;
    tArea.start_col = 30;
    tArea.start_row = 240;

    cvRectangle(
        ptLogImg_1,
        cvPoint(tArea.start_col, tArea.start_row),
        cvPoint(tArea.start_col + tArea.width, tArea.start_row + tArea.height),
        CV_RGB(255, 0, 0), 2, CV_AA, 0
    );

    cvSaveImage(acFilePath_out, ptLogImg_1, 0);

    Calculate_MTF_withPositionShift(&uwMTF, &tImg, &tArea);

    printf("MTF = %d\n", uwMTF);
    cvReleaseImage(&ptLogImg);
    cvReleaseImage(&ptLogImg_1);
}