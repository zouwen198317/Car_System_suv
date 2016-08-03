
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdlib.h>
#include "mtype.h"
#include "atype.h"

/** \brief LDC corner point number */
#define alLDCK_CORNER_NUM 63 // 16

/** \brief LDC feature point number */
#define alLDCK_FP_NUM 4

/** \brief LDC Coefficient number */
#define alLDCK_COE_NUM 6

/** \brief error threshold */
#define alLDCK_ERROR_TH 0.04

/** \brief gradient descent learning rate */
#define alLDCK_LERAN_RATE 0.02 // 0.2

/** \brief gradient descent learning rate */
#define alLDCK_LERAN_RATE_MIN 0.00001

/** \brief delta of poly coefficient*/
#define alLDCK_DELTA_COE 0.0001 // 0.001

/** \brief delta of image center*/
#define alLDCK_DELTA_CENTER 1

/** \brief max iteration time */
#define alLDCK_MAX_ITER_TIME 10000 // 2000

/** \brief max CENTER OFFSET */
#define alLDCK_MAX_CENTER_OFFSET 15

/** \brief error weighting mode : 1 = ON   0 = OFF */
#define alLDCK_ERROR_WEIGHTING_MODE 1

/** \brief calibration chart size */
#define alLDCK_CHART_BLOCK_SIZE 68

/** \brief error weighting mode : 1 = ON   0 = OFF */
#define alLDCK_ADAPTIVE_LEARN_RATE_MODE 0

/******************************************************************************\
 *  Data Structure
\******************************************************************************/


/** \brief parameter of LDC */
typedef struct
{
    /** \brief the Coefficient of LDC */
    FLOAT64 aeCoe[alLDCK_COE_NUM];

    /** \brief the center points */
    alPointFLOAT64 tCenter;

    /** \brief ResizeRatio */
    alPointFLOAT64 tResizeRatio;

    /** \brief The real pixel size of the sensor. in nano-meter. */
    UINT32 ulSensorPixelSize;

    /** \brief Focal length of the camera in mm. */
    FLOAT64 eFocalLength;

} alLDCK_LDC_Params;


/** \brief alLDCK Data */
typedef struct
{
    /** \brief the Ideal corner points */
    alPointFLOAT64 atCornerIdeal[alLDCK_CORNER_NUM];

    /** \brief the feature points */
    alPointFLOAT64 atFP[alLDCK_FP_NUM];

    /** \brief the Ideal feature points */
    alPointFLOAT64 atFPIdeal[alLDCK_FP_NUM];

    /** \brief default parameter */
    alLDCK_LDC_Params tParams_Default;
} alLDCK_Cfg;

/** \brief alLDCK Data */
typedef struct
{
    /** \brief the corner enable flag 0: on  1: off */
    UINT8 aucCornerFlag[alLDCK_CORNER_NUM];

    /** \brief the corner enable flag 0: on  1: off */
    UINT8 aucCornerFlag_H_Matrix[alLDCK_CORNER_NUM];

    /** \brief the corner number */
    INT32 lCornerCnt;

    /** \brief the corner points: postion in original image */
    alPointFLOAT64 atCorner[alLDCK_CORNER_NUM];

    /** \brief the Ideal corner points */
    alPointFLOAT64 atCornerIdeal[alLDCK_CORNER_NUM];

    /** \brief the feature points */
    alPointFLOAT64 atFP[alLDCK_FP_NUM];

    /** \brief the Ideal feature points */
    alPointFLOAT64 atFPIdeal[alLDCK_FP_NUM];

    /** \brief default parameter */
    alLDCK_LDC_Params tParams_Default;

    /** \brief default parameter */
    alLDCK_LDC_Params tParams_Current;

} alLDCK_Data;


/**
\brief alLDCK_LoadIdealCornerByINI : Load ideal corner position
\param pcINIFile [IN] INI file path
\param a_ptData [INOUT] alLDCK Data
*/
void alLDCK_LoadIdealCornerByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData);


/**
\brief alLDCK_LoadCornerByINI : Load real corner position
\param pcINIFile [IN] INI file path
\param a_ptData [INOUT] alLDCK Data
*/
void alLDCK_LoadCornerByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData);

/**
\brief alLDCK_LoadMatrixFlagByINI : Load Matrix Flag By INI
\param pcINIFile [IN] INI file path
\param a_ptData [INOUT] alLDCK Data
*/
void alLDCK_LoadMatrixFlagByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData);

/**
\brief alLDCK_LoadCornerFlagByINI : Load corner Flag By INI >> only used during Debug
\param pcINIFile [IN] INI file path
\param a_ptData [INOUT] alLDCK Data
*/
void alLDCK_LoadCornerFlagByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData);


#ifdef __cplusplus
}
#endif
