#pragma once

#include "BVCAM_FACAUTOK/CrossMarkK_Def.h"
#include "BVCAM_FACAUTOK/RectK_Def.h"
#include "alHexData.h" // for cfg %parameter import and export


/**
*  \addtogroup alBVCAM_FACAUTOK
*  @{
*/

#ifndef MAX_PATH
#define MAX_PATH          260
#endif

#define alBVCAM_FACAUTOK_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST       920     // 預設前輪中心至車頭距離
#define alBVCAM_FACAUTOK_DEFAULT_CHART_HORI_DIST                 1860    // 左右 Chart 內側間距
#define alBVCAM_FACAUTOK_DEFAULT_CHART_VERT_DIST                 4840    // 前後 Chart 內側間距

////////////// for default crossmark setting ////////////////
/*

alBVCAM_FACAUTOK_DEFAULT_CHART_HORI_DIST
______ ←───→ ______
FW5|＋ ＋ |FW3    FW4| ＋ ＋| FW6
|   ＋ |          | ＋   |
|______|(左前)    |______|(右前)
↑ FW1 ↑          FW2
alBVCAM_FACAUTOK_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST    ↓     ∣
----------------------∣
(車輪中心)                 ∣alBVCAM_FACAUTOK_DEFAULT_CHART_VERT_DIST
∣
BW2 ∣          BW1
______ ↓         ______
|   ＋ |(左後)    | ＋   |(右後)
BW6|＋ ＋ |BW4    BW3| ＋ ＋|BW5
|______|          |______|

*/
#define alBVCAM_FACAUTOK_DEFAULT_FW1                   600
#define alBVCAM_FACAUTOK_DEFAULT_FH1                   450
#define alBVCAM_FACAUTOK_DEFAULT_FW2                   600
#define alBVCAM_FACAUTOK_DEFAULT_FH2                   450
#define alBVCAM_FACAUTOK_DEFAULT_FW3                   600
#define alBVCAM_FACAUTOK_DEFAULT_FH3                   1350
#define alBVCAM_FACAUTOK_DEFAULT_FW4                   600
#define alBVCAM_FACAUTOK_DEFAULT_FH4                   1350
#define alBVCAM_FACAUTOK_DEFAULT_FW5                   1500 // 1600
#define alBVCAM_FACAUTOK_DEFAULT_FH5                   1200
#define alBVCAM_FACAUTOK_DEFAULT_FW6                   1500 // 1600
#define alBVCAM_FACAUTOK_DEFAULT_FH6                   1200
#define alBVCAM_FACAUTOK_DEFAULT_BW1                   750
#define alBVCAM_FACAUTOK_DEFAULT_BH1                   450
#define alBVCAM_FACAUTOK_DEFAULT_BW2                   750
#define alBVCAM_FACAUTOK_DEFAULT_BH2                   450
#define alBVCAM_FACAUTOK_DEFAULT_BW3                   750
#define alBVCAM_FACAUTOK_DEFAULT_BH3                   1350
#define alBVCAM_FACAUTOK_DEFAULT_BW4                   750
#define alBVCAM_FACAUTOK_DEFAULT_BH4                   1350
#define alBVCAM_FACAUTOK_DEFAULT_BW5                   1500
#define alBVCAM_FACAUTOK_DEFAULT_BH5                   900
#define alBVCAM_FACAUTOK_DEFAULT_BW6                   1500
#define alBVCAM_FACAUTOK_DEFAULT_BH6                   900

#define alBVCAM_FACAUTOK_DEFAULT_BW7                   1500
#define alBVCAM_FACAUTOK_DEFAULT_BH7                   0
#define alBVCAM_FACAUTOK_DEFAULT_BW8                   1500
#define alBVCAM_FACAUTOK_DEFAULT_BH8                   0
////////////// for default crossmark setting ////////////////





#define alBVCAM_FACAUTOK_Q_Width 40
#define alBVCAM_FACAUTOK_Q_Height 15
#define BVCAM_FACAUTOK_MAX_CAM 4
#define BVCAM_FACAUTOK_MAX_POINT 8
#define BVCAM_FACAUTOK_MAX_POINT_FINETUNE 2

#define alBVCAM_FACAUTOK_Q_LineBufferSize ((alBVCAM_FACAUTOK_Q_Width<<1+1)*(alBVCAM_FACAUTOK_Q_Height<<1+1))

#define alBVCAM_FACAUTOK_SBV_WorkingBufferSize (COMMONK_MAX_DISPLAY_AREA_SIZE_X*COMMONK_MAX_DISPLAY_AREA_SIZE_Y) // SBV size
#define alBVCAM_FACAUTOK_Else_WorkingBufferSize COMMONK_Else_WorkingBufferSize // 400(x)*400(y)*8(byte)  for line segment
#define alBVCAM_FACAUTOK_Total_WorkingBufferSize (alBVCAM_FACAUTOK_SBV_WorkingBufferSize+alBVCAM_FACAUTOK_Else_WorkingBufferSize)

/** \brief Define the number of fine tune feature points for each camera (For AutoK). */
#define     BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK_FINETUNE              6

/** \brief Define the number of feature points for each camera (For AutoK). */
#define     BVCAM_FACAUTOK_CAMERA_FP_NUM_AUTOK              8

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief Define the BVCAM_FACAUTOK configure data struct . */
// #pragma pack (1)
typedef struct
{
	/** \brief cammera number K*/
	INT32 lCammeraNum;

	/** \brief RectK CFG data K*/
	alRECK_Cfg atRecKCfg[COMMONK_NUM_BV_CHANNEL];

	/** \brief CrossMarkK CFG data K*/
	alCROSSMARKK_Cfg atCrossMarkKCfg[COMMONK_NUM_BV_CHANNEL];

} BVCAM_FACAUTOK_CFG;
// #pragma pack ()

/** \brief The cross point position of chart. */
typedef struct
{
    /** \brief 校正場前輪定位點至前方Chart距離 */
    UINT16 uwFWheeltoFChart;
    /** \brief 校正場左右校正Chart的間隔 */
    UINT16 uwChartHoriDistance;
    /** \brief 校正場前後校正Chart的間隔 */
    UINT16 uwCharVertDistance;

    UINT16 FW1;
    UINT16 FH1;
    UINT16 FW2;
    UINT16 FH2;
    UINT16 FW3;
    UINT16 FH3;
    UINT16 FW4;
    UINT16 FH4;
    UINT16 FW5;
    UINT16 FH5;
    UINT16 FW6;
    UINT16 FH6;
    UINT16 BW1;
    UINT16 BH1;
    UINT16 BW2;
    UINT16 BH2;
    UINT16 BW3;
    UINT16 BH3;
    UINT16 BW4;
    UINT16 BH4;
    UINT16 BW5;
    UINT16 BH5;
    UINT16 BW6;
    UINT16 BH6;
    UINT16 BW7;
    UINT16 BH7;
    UINT16 BW8;
    UINT16 BH8;

} BVCAM_FACAUTOK_ChartCrossPointSet;

/** \brief The Calibration Feild Data. */
typedef struct
{
    /** \brief Calibration Feild Data of RectK*/
    alRECK_CalCfg tRECK_FeildData;

    /** \brief Calibration Feild Data of Crossmark K*/
    BVCAM_FACAUTOK_ChartCrossPointSet tCrossmarkFeildData;

} BVCAM_FACAUTOK_CalibrationFeildData;

/** \brief Define the FBVCAM_FACAUTOK Parameter data struct . */
typedef struct
{
	/** \brief RectK Parameter data K*/
	alRECK_Parameter atRecKParameter[COMMONK_NUM_BV_CHANNEL];

	/** \brief CrossMarkK Parameter data K*/
	alCROSSMARKK_Parameter atCrossMarkKParameter[COMMONK_NUM_BV_CHANNEL];

	/** \brief FineTune Point of each view*/
	alCROSSMARKK_Point atFineTuneFP[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_MAX_POINT_FINETUNE];

	/** \brief FineTune Stitch Line of each viw*/
	alCROSSMARKK_Vector atStitchLine[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_MAX_POINT_FINETUNE];

    /** \brief The BV Buffer size */
    alPointINT32 tBVImgSize;

} BVCAM_FACAUTOK_Parameter;

/** \brief Define the FBVCAM_FACAUTOK result data struct . */
typedef struct
{
	/** \brief RecTangleK flag 1: ok  0: fail */
	UINT8 aucRecKFlag[COMMONK_NUM_BV_CHANNEL];

	/** \brief Feature points flag 1: refine  0: fail, remove refine offset */
	UINT8 aucROIRefineFlag[COMMONK_NUM_BV_CHANNEL];

	/** \brief CrossMarkK flag 1: ok  0: fail */
	UINT8 aucCrossMarkKFlag[COMMONK_NUM_BV_CHANNEL];

	/** \brief Quality flag 1: ok  0: fail */
	UINT8 aucQualityFineTuneFlag[COMMONK_NUM_BV_CHANNEL];

	/** \brief Feature points X by RecK in undistortion image*/
	FLOAT64 aeFPRecKX[COMMONK_NUM_BV_CHANNEL][alRECK_MAX_POINT_VIEW];

	/** \brief Feature points Y by RecK in undistortion image*/
	FLOAT64 aeFPRecKY[COMMONK_NUM_BV_CHANNEL][alRECK_MAX_POINT_VIEW];

	/** \brief Feature points X by CrossMarkK in undistortion image*/
	FLOAT64 aeFPCrossMarkKX[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_MAX_POINT];

	/** \brief Feature points Y by CrossMarkK in undistortion image*/
	FLOAT64 aeFPCrossMarkKY[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_MAX_POINT];

	/** \brief Feature points X by FineTune in undistortion image*/
	FLOAT64 aeFPFineTuneX[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_MAX_POINT];

	/** \brief Feature points Y by FineTune in undistortion image*/
	FLOAT64 aeFPFineTuneY[COMMONK_NUM_BV_CHANNEL][BVCAM_FACAUTOK_MAX_POINT];

	/** \brief Fatory AutoK Result */
	FLOAT64 aeOriginalM33[BVCAM_FACAUTOK_MAX_CAM][2][COMMONK_M33_ELEMENT_CNT];

	/** \brief Fatory AutoK Result */
	FLOAT64 aeRecKM33[BVCAM_FACAUTOK_MAX_CAM][2][COMMONK_M33_ELEMENT_CNT];

	/** \brief Fatory AutoK Result */
	FLOAT64 aeCrossMarkKM33[BVCAM_FACAUTOK_MAX_CAM][2][COMMONK_M33_ELEMENT_CNT];

	/** \brief FineTune M33 Result */
	FLOAT64 aeFineTuneKM33[BVCAM_FACAUTOK_MAX_CAM][2][COMMONK_M33_ELEMENT_CNT];

	/** \brief Error of Quality Analyzing*/
	FLOAT64 aeCompareError[COMMONK_NUM_BV_CHANNEL];

	/** \brief Error of Quality Analyzing compare to Ideal value*/
	FLOAT64 aeAbsluteError[8];

    /** \brief Working Buffer*/
    UINT8 *pucWorkingBuffer;
} BVCAM_FACAUTOK_Data;


/** 
\brief Initial function for BVCAM_FACAUTOK Calibration (1200)
*/
void alBVCAM_FACAUTOK_LoadDefault(BVCAM_FACAUTOK_CFG *a_ptCfg);


/**
\brief Initial function for BVCAM_FACAUTOK Calibration (1200)
*/
void alBVCAM_FACAUTOK_LoadDefaultFeildData(BVCAM_FACAUTOK_CalibrationFeildData *a_ptFeildData);


/**
\brief Load BVCAM FACAUTOK Feild Data By INI
*/
void alBVCAM_FACAUTOK_LoadFeildDataByINI(wchar_t * pwcIniFileName, BVCAM_FACAUTOK_CalibrationFeildData *a_ptFeildData);

/**
\brief Cfg Import by INI file (1300-1)
\param a_pwcConfigFilePath [IN] Config File Path
*/
void alBVCAM_FACAUTOK_CfgImportINI(wchar_t * a_pwcConfigFilePath, BVCAM_FACAUTOK_CFG *a_ptCfg);

/**
\brief Cfg Export to Hex file
\param a_ulSectionID [IN] Section ID
\param a_ptBVCAM_FACAUTOKCfg [IN] BVCAM_FACAUTOK Config data
\param a_pucDataSectionBuffer [OUT] Data Section Buffer for output
*/
UINT32 alBVCAM_FACAUTOK_CfgExport(
	UINT32 a_ulSectionID,
	BVCAM_FACAUTOK_CFG *a_ptBVCAM_FACAUTOKCfg,
	UINT8 *a_pucDataSectionBuffer
	);

/**
\brief Parameter Export to Hex file
\param a_ulSectionID [IN] Section ID
\param a_ptBVCAM_FACAUTOKCfg [IN] BVCAM_FACAUTOK Config data
\param a_pucDataSectionBuffer [OUT] Data Section Buffer for output
*/
UINT32 alBVCAM_FACAUTOK_ParameterExport(
	UINT32 a_ulSectionID,
	UINT32 a_ulSectionBufLenLimit,
	BVCAM_FACAUTOK_Parameter *a_ptBVCAM_FACAUTOKParams,
	UINT8 *a_pucDataSectionBuffer
);

/**
\brief Cfg Import by Hex file (1300-2)
\param a_ulDataID [IN] Data ID
\param a_ulDataLength [IN] Data Length
\param a_pulBuffer [IN] Data Section Buffer for reading
*/
void alBVCAM_FACAUTOK_CfgImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, BVCAM_FACAUTOK_CFG *a_ptCfg);

/**
\brief Cfg Import by Hex file (1300-2)
\param a_ulDataID [IN] Data ID
\param a_ulDataLength [IN] Data Length
\param a_pulBuffer [IN] Data Section Buffer for reading
*/
void alBVCAM_FACAUTOK_ParamsImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer);


/*
\brief To load calibration field data from ini file. If the data loading failed, the hard coded default value will be loaded.
\param pwcIniFilePath [IN] Indicate the ini file.
\return Return TRUE if the data loading is successful, and FALSE vice verse.
*/
BOOL alBVCAM_FACAUTOK_LoadRECKRefData(wchar_t * pwcIniFileName, alRECK_CalCfg *a_ptRECKFeildData);

void alBVCAM_FACAUTOK_SetWorkingPath(wchar_t * a_pwcWorkingPath);

/** \brief BVCAM_FACAUTOK module Data*/
extern BVCAM_FACAUTOK_Data g_tBVCAM_FACAUTOK_Data;

/** \brief BVCAM_FACAUTOK module Parameter*/
extern BVCAM_FACAUTOK_CFG g_tBVCAM_FACAUTOK_Cfg;

/** \brief BVCAM_FACAUTOK module Parameter*/
extern BVCAM_FACAUTOK_Parameter g_tBVCAM_FACAUTOK_Parameter;

extern char g_acalBVCAM_FACAUTOK_WorkingFolder[MAX_PATH];
extern char g_acalBVCAM_FACAUTOK_SourceFolder[MAX_PATH];
extern char g_acalBVCAM_FACAUTOK_OutputFolder[MAX_PATH];

#ifdef __cplusplus
}
#endif

/**
*  @}
*/
