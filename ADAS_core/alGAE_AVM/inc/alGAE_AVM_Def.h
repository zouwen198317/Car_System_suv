
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include "mtype.h"


/**
*  \addtogroup alGAE_AVM
*  @{
*/

/** \brief Total view number */
#define alGAE_ViewNum 4

/** \brief 計算GAE 區塊的大小 (正方形) */
#define MAX_ROI_SIZE 60

/** \brief 計算GAE 區塊的面積 (正方形) */
#define MAX_ROI_AREA MAX_ROI_SIZE*MAX_ROI_SIZE

/** \brief ROI數量: 4(view number) x 2(ROI per view) x 3(YUV) = 24 */
#define NUM_ROI 24

/** \brief 最高補償上限: 無其他條件限制時 */
#define COMPENSATE_MAX_VIEW 100

/** \brief 最高補償上限: 無雜訊等條件限制時 */
#define COMPENSATE_MAX_VIEW_LOW 10

/** \brief 低雜訊的閥值: 雜訊低可盡量補償 */
#define NOISE_TH_LOW 20

/** \brief 高雜訊的閥值: 雜訊高不能補償過多 */
#define NOISE_TH_HIGH 80

/** \brief 打算在幾張frame內補償完畢 (避免急遽變化或雜訊) */
#define FRAME_GAP 5

/** \brief 每個view在每個frame能補償的上限(不包含收斂值) */
#define COMPENSATE_LIMIT COMPENSATE_MAX_VIEW / FRAME_GAP

/** \brief 補償的目標: 用於方別亮或暗的依據 */
#define YMEAN_TARGET	70

/** \brief 過曝下限 */
#define BRIGHT_LIMIT	245

/** \brief 過暗下限 */
#define DARK_LIMIT	40

/** \brief 亮區亮度閥值 */
#define HIGH_TH	(YMEAN_TARGET+((BRIGHT_LIMIT-YMEAN_TARGET)/2))

/** \brief 暗區亮度閥值 */
#define LOW_TH	    (YMEAN_TARGET-((YMEAN_TARGET-DARK_LIMIT)/2))

/** \brief 低亮度區域的百分比閥值 */
#define MEAN_PERCENTAGE_LOW_TH 5

/** \brief 高亮度區域的百分比閥值 */
#define MEAN_PERCENTAGE_HIGH_TH 55

/** \brief 1: 啟動Debug功能 0:off*/
#define alGAE_AVM_LOG 1

/** \brief 判斷障礙物的相似度閥值 */
#define TH_Obstacle_Y	0.51	

/** \brief 判斷非障礙物的相似度閥值 */
#define TH_Non_Obstacle_Y	0.60

/** \brief Target view 需補償的下限: 低於它就要補到 TargetOffsetLow_TH */
#define TargetOffsetLow_TH	90

    /** \brief Target view 需補償的上限: 高於它就要補到 TargetOffsetHigh_TH */
#define TargetOffsetHigh_TH	155



/******************************************************************************\
 *  Data Structure
\******************************************************************************/


/** \brief Global_AE_histogram struct for 10 bins */
typedef struct Global_AE_histogram
{
    /** \brief 該ROI的mean值 */
    UINT16 mean;
    /** \brief peak個數 */
    UINT8 PeakCnt;
    /** \brief bin的計數 */
    UINT16 bin[256];
    /** \brief bin的加總值 */
    UINT32 sum[10];
    /** \brief 得到mean值的case */
    UINT8 mode;
    /** \brief Peak的位置 */
    UINT8 PositionofPeak[5];
    /** \brief bin的百分比 */
    FLOAT32 percentage[10];
    /** \brief roi 類型計數用 */
    UINT8 ROIPeakTypeCnt[4];
} Global_AE_Hist;

/** \brief Global_AE Data */
typedef struct
{
    /** \brief the Offset need to add to LCD for Firmware read */
    INT8 acOffset_Ymean_Firmware[4];

    /** \brief the Offset need for target view depend on gear */
    INT16 wOffset_Ymean_TargetView;

    /** \brief the Compensate offset limit */
    INT32 lLimitView;

    /** \brief the Compensate offset limit of each frame */
    INT32 lLimitFrame;

    /** \brief Y mean value of each GAE ROI */
    UINT32 aulMean[8];

    /** \brief Y mean difference of each GAE ROI */
    INT32 alGap[4];

    /** \brief ROI histogram correlation result for obstacle juge 3(YUV) x 4(view num) = 12  */
    FLOAT32 afCorrelationResult[12];

    /** \brief Obstacle flag >> 0: on obstacle 1: obstacle  [0]: 左前  [1]: 右前  [2]: 左後  [3]: 右後 */
    UINT8 aucObstacle[4];

} alGAE_AVM_Data;


/**
*  @}
*/
#ifdef __cplusplus
}
#endif
