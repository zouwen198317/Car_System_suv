
#pragma once

#include "mtype.h"
#include "atype.h"

/**
*   \defgroup alLANEINFO    alLaneInfo
*   The module define the struct and some enum data whiche inclues lane mark information.
*   @{
*/

/** \brief Enum index flag of lane postion. */
typedef enum 
{

    /** \brief Indicate the lane the same as ego-vehicle. */
    alLANEINFO_LANEINDEX_CENTER = 0,
    /** \brief Indicate the left lane. (指左側單一車道) */
    alLANEINFO_LANEINDEX_LEFT,
    /** \brief Indicate the right lane. (指右側單一車道) */
    alLANEINFO_LANEINDEX_RIGHT,
    /** \brief Indicate the left position far than the left lane. (泛指超過左側車道的位置) */
    alLANEINFO_LANEINDEX_LEFT_FAR,
    /** \brief Indicate the right position far than the right lane. (泛指超過右側車道的位置) */
    alLANEINFO_LANEINDEX_RIGHT_FAR

} alLANEINFO_LANEINDEX;

/** \brief Define the input struct of lane information from lane detection. */
typedef struct
{

    /** \brief Indicate if the left lane marking is valid. (LDWS 是否正確偵測到左側車道標線) */
    BOOL    m_bIsLaneValid_L;
    /** \brief Indicate if the right lane marking is valid. (LDWS 是否正確偵測到右側車道標線) */
    BOOL    m_bIsLaneValid_R;
    /** \brief Record the kmb parameters of left lane. (LDWS 所計算得到左側車道標線的 kmb) */
    alKMBSet  m_kmbLane_L;
    /** \brief Record the kmb parameters of right lane. (LDWS 所計算得到右側車道標線的 kmb) */
    alKMBSet  m_kmbLane_R;
    /** \brief Record the lane width calculated by the distance between left and right lane marking. (LDWS 計算所得之車道寬度) */
    INT32   m_lLaneWidth;

} alLANEINFO_Set;

/**
*   @}
*/