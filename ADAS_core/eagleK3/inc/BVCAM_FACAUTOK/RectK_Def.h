#pragma once

#include "mtype.h"    
#include "CommonK.h"
#include "alFM_v2_1.h"
#include <assert.h>

/**
  *  \addtogroup alRECK
  *  @{
  */



#define alRECK_NISSAN_CHART 1

#define alRECK_RECTANGLE_POINT_NUM 4

#define alRECK_MAX_LINE_NUM 50

/** \brief For default CFG setting. */
#define alRECK_ROI_NUM_LEFT 2
#define alRECK_ROI_NUM_RIGHT 2
#define alRECK_ROI_NUM_FRONT 4
#define alRECK_ROI_NUM_BACK 2

#define alRECK_SBV_SCALE_LEFT_1 2.0
#define alRECK_SBV_SCALE_LEFT_2 2.0
#define alRECK_SBV_SCALE_RIGHT_1 2.0
#define alRECK_SBV_SCALE_RIGHT_2 2.0
#define alRECK_SBV_SCALE_FRONT_1 2.5
#define alRECK_SBV_SCALE_FRONT_2 2.5
#define alRECK_SBV_SCALE_FRONT_3 2.5
#define alRECK_SBV_SCALE_FRONT_4 2.5
#define alRECK_SBV_SCALE_BACK_1 2.5
#define alRECK_SBV_SCALE_BACK_2 2.5
#define alRECK_SBV_SCALE_BACK_3 2.5
#define alRECK_SBV_SCALE_BACK_4 2.5

#define alRECK_SBV_OFFSETX_LEFT_1 -100
#define alRECK_SBV_OFFSETX_LEFT_2 -100
#define alRECK_SBV_OFFSETX_RIGHT_1 100
#define alRECK_SBV_OFFSETX_RIGHT_2 100

#if alRECK_NISSAN_CHART
#define alRECK_SBV_OFFSETX_FRONT_1 50
#define alRECK_SBV_OFFSETX_FRONT_2 50
#define alRECK_SBV_OFFSETX_FRONT_3 50
#define alRECK_SBV_OFFSETX_FRONT_4 50
#define alRECK_SBV_OFFSETX_BACK_1 300
#define alRECK_SBV_OFFSETX_BACK_2 -300
#define alRECK_SBV_OFFSETX_BACK_3 -300
#define alRECK_SBV_OFFSETX_BACK_4 -300
#else
#define alRECK_SBV_OFFSETX_FRONT_1 -300
#define alRECK_SBV_OFFSETX_FRONT_2 300
#define alRECK_SBV_OFFSETX_BACK_1 300
#define alRECK_SBV_OFFSETX_BACK_2 -300
#endif

#define alRECK_SBV_OFFSETY_LEFT_1 -300
#define alRECK_SBV_OFFSETY_LEFT_2 360
#define alRECK_SBV_OFFSETY_RIGHT_1 -300
#define alRECK_SBV_OFFSETY_RIGHT_2 360

#if alRECK_NISSAN_CHART
#define alRECK_SBV_OFFSETY_FRONT_1 -200
#define alRECK_SBV_OFFSETY_FRONT_2 -200
#define alRECK_SBV_OFFSETY_FRONT_3 -200
#define alRECK_SBV_OFFSETY_FRONT_4 -200
#define alRECK_SBV_OFFSETY_BACK_1 100
#define alRECK_SBV_OFFSETY_BACK_2 100
#define alRECK_SBV_OFFSETY_BACK_3 100
#define alRECK_SBV_OFFSETY_BACK_4 100
#else
#define alRECK_SBV_OFFSETY_FRONT_1 -100
#define alRECK_SBV_OFFSETY_FRONT_2 -100
#define alRECK_SBV_OFFSETY_BACK_1 100
#define alRECK_SBV_OFFSETY_BACK_2 100
#endif

/** \brief For default ideal point setting. */
#if 0 // 以車中心為Based
// LEFT RECTANGLE_0 (BACK)
#define alRECK_RECTANGLE_LEFT_1_0_X -1670
#define alRECK_RECTANGLE_LEFT_1_0_Y 1425

#define alRECK_RECTANGLE_LEFT_1_1_X -2670
#define alRECK_RECTANGLE_LEFT_1_1_Y 1425

#define alRECK_RECTANGLE_LEFT_1_2_X -2670
#define alRECK_RECTANGLE_LEFT_1_2_Y 825

#define alRECK_RECTANGLE_LEFT_1_3_X -1670
#define alRECK_RECTANGLE_LEFT_1_3_Y 825 

// LEFT RECTANGLE_1 (FRONT)
#define alRECK_RECTANGLE_LEFT_0_0_X -1520
#define alRECK_RECTANGLE_LEFT_0_0_Y -1815

#define alRECK_RECTANGLE_LEFT_0_1_X -2520
#define alRECK_RECTANGLE_LEFT_0_1_Y -1815

#define alRECK_RECTANGLE_LEFT_0_2_X -2520
#define alRECK_RECTANGLE_LEFT_0_2_Y -2415

#define alRECK_RECTANGLE_LEFT_0_3_X -1520
#define alRECK_RECTANGLE_LEFT_0_3_Y -2415

// RIGHT RECTANGLE_1 (BACK)
#define alRECK_RECTANGLE_RIGHT_1_0_X 1690
#define alRECK_RECTANGLE_RIGHT_1_0_Y 825

#define alRECK_RECTANGLE_RIGHT_1_1_X 2690
#define alRECK_RECTANGLE_RIGHT_1_1_Y 825

#define alRECK_RECTANGLE_RIGHT_1_2_X 2690
#define alRECK_RECTANGLE_RIGHT_1_2_Y 1425

#define alRECK_RECTANGLE_RIGHT_1_3_X 1690
#define alRECK_RECTANGLE_RIGHT_1_3_Y 1425

// RIGHT RECTANGLE_0 (FRONT)
#define alRECK_RECTANGLE_RIGHT_0_0_X 1540
#define alRECK_RECTANGLE_RIGHT_0_0_Y -2415

#define alRECK_RECTANGLE_RIGHT_0_1_X 2540
#define alRECK_RECTANGLE_RIGHT_0_1_Y -2415

#define alRECK_RECTANGLE_RIGHT_0_2_X 2540
#define alRECK_RECTANGLE_RIGHT_0_2_Y -1815

#define alRECK_RECTANGLE_RIGHT_0_3_X 1540
#define alRECK_RECTANGLE_RIGHT_0_3_Y -1815


// FRONT RECTANGLE_0 (LEFT)
#if 1 // for 自己的長方形版
#define alRECK_RECTANGLE_FRONT_0_0_X -320
#define alRECK_RECTANGLE_FRONT_0_0_Y -2865

#define alRECK_RECTANGLE_FRONT_0_1_X -320
#define alRECK_RECTANGLE_FRONT_0_1_Y -3865

#define alRECK_RECTANGLE_FRONT_0_2_X 280
#define alRECK_RECTANGLE_FRONT_0_2_Y -3865

#define alRECK_RECTANGLE_FRONT_0_3_X 280
#define alRECK_RECTANGLE_FRONT_0_3_Y -2865
#else // for Nissan 板子

#endif

// BACK RECTANGLE_0 (LEFT)
#if 1 // for 自己的長方形版
#define alRECK_RECTANGLE_BACK_0_0_X 330
#define alRECK_RECTANGLE_BACK_0_0_Y 2875

#define alRECK_RECTANGLE_BACK_0_1_X 330
#define alRECK_RECTANGLE_BACK_0_1_Y 3875

#define alRECK_RECTANGLE_BACK_0_2_X -270
#define alRECK_RECTANGLE_BACK_0_2_Y 3875

#define alRECK_RECTANGLE_BACK_0_3_X -270
#define alRECK_RECTANGLE_BACK_0_3_Y 2875
#else // for Nissan 板子

#endif

#else // 以左前輪中心為based
// LEFT RECTANGLE_0 (BACK)
#define alRECK_RECTANGLE_LEFT_1_0_X -750 // -1670
#define alRECK_RECTANGLE_LEFT_1_0_Y 3520 // 2920 // 1425

#define alRECK_RECTANGLE_LEFT_1_1_X -1350 // -2670
#define alRECK_RECTANGLE_LEFT_1_1_Y 3520 // 2920 // 1425

#define alRECK_RECTANGLE_LEFT_1_2_X -1350 // -2670
#define alRECK_RECTANGLE_LEFT_1_2_Y 3120 // 2520 // 825

#define alRECK_RECTANGLE_LEFT_1_3_X -750 // -1670
#define alRECK_RECTANGLE_LEFT_1_3_Y 3120 // 2520 // 825

// LEFT RECTANGLE_1 (FRONT)
#define alRECK_RECTANGLE_LEFT_0_0_X -600 // -1520
#define alRECK_RECTANGLE_LEFT_0_0_Y -520 // -1815

#define alRECK_RECTANGLE_LEFT_0_1_X -1200 // -2520
#define alRECK_RECTANGLE_LEFT_0_1_Y -520 // -1815

#define alRECK_RECTANGLE_LEFT_0_2_X -1200 // -2520
#define alRECK_RECTANGLE_LEFT_0_2_Y -920 // -2415

#define alRECK_RECTANGLE_LEFT_0_3_X -600 // -1520
#define alRECK_RECTANGLE_LEFT_0_3_Y -920 // -2415

// RIGHT RECTANGLE_1 (BACK)
#define alRECK_RECTANGLE_RIGHT_1_0_X 2610 // 1690
#define alRECK_RECTANGLE_RIGHT_1_0_Y 3120 // 2520 // 825

#define alRECK_RECTANGLE_RIGHT_1_1_X 3210 // 2690
#define alRECK_RECTANGLE_RIGHT_1_1_Y 3120 // 2520 // 825

#define alRECK_RECTANGLE_RIGHT_1_2_X 3210 // 2690
#define alRECK_RECTANGLE_RIGHT_1_2_Y 3520 // 2920 // 1425

#define alRECK_RECTANGLE_RIGHT_1_3_X 2610 // 1690
#define alRECK_RECTANGLE_RIGHT_1_3_Y 3520 // 2920 // 1425

// RIGHT RECTANGLE_0 (FRONT)
#define alRECK_RECTANGLE_RIGHT_0_0_X 2460 // 1540
#define alRECK_RECTANGLE_RIGHT_0_0_Y -920 // -2415

#define alRECK_RECTANGLE_RIGHT_0_1_X 3060 // 2540
#define alRECK_RECTANGLE_RIGHT_0_1_Y -920 // -2415

#define alRECK_RECTANGLE_RIGHT_0_2_X 3060 // 2540
#define alRECK_RECTANGLE_RIGHT_0_2_Y -520 // -1815

#define alRECK_RECTANGLE_RIGHT_0_3_X 2460 // 1540
#define alRECK_RECTANGLE_RIGHT_0_3_Y -520 // -1815



#if alRECK_NISSAN_CHART == 0 // for 自己的長方形版

// FRONT RECTANGLE_0 (LEFT)
#define alRECK_RECTANGLE_FRONT_0_0_X 600 // -320
#define alRECK_RECTANGLE_FRONT_0_0_Y -1370 // -2865

#define alRECK_RECTANGLE_FRONT_0_1_X 600 // -320
#define alRECK_RECTANGLE_FRONT_0_1_Y -2370 // -3865

#define alRECK_RECTANGLE_FRONT_0_2_X 1200 // 280
#define alRECK_RECTANGLE_FRONT_0_2_Y -2370 // -3865

#define alRECK_RECTANGLE_FRONT_0_3_X 1200 // 280
#define alRECK_RECTANGLE_FRONT_0_3_Y -1370 // -2865
#else // for Nissan 板子

// FRONT RECTANGLE_0 (LEFT-DOWN)
#define alRECK_RECTANGLE_FRONT_0_0_X 0 // 430
#define alRECK_RECTANGLE_FRONT_0_0_Y -1920 // -1870

#define alRECK_RECTANGLE_FRONT_0_1_X 0 // 430
#define alRECK_RECTANGLE_FRONT_0_1_Y -2520 // -2270

#define alRECK_RECTANGLE_FRONT_0_2_X 400 // 830
#define alRECK_RECTANGLE_FRONT_0_2_Y -2520 // -2270

#define alRECK_RECTANGLE_FRONT_0_3_X 400 // 830
#define alRECK_RECTANGLE_FRONT_0_3_Y -1920 // -1870 

// FRONT RECTANGLE_0 (LEFT-TOP)
#define alRECK_RECTANGLE_FRONT_1_0_X 1460 // 430
#define alRECK_RECTANGLE_FRONT_1_0_Y -1920 // -2470

#define alRECK_RECTANGLE_FRONT_1_1_X 1460 // 430
#define alRECK_RECTANGLE_FRONT_1_1_Y -2520 // -2870

#define alRECK_RECTANGLE_FRONT_1_2_X 1860 // 830
#define alRECK_RECTANGLE_FRONT_1_2_Y -2520 // -2870

#define alRECK_RECTANGLE_FRONT_1_3_X 1860 // 830
#define alRECK_RECTANGLE_FRONT_1_3_Y -1920 // -2470 

// FRONT RECTANGLE_0 (RIGHT-DOWN)
#define alRECK_RECTANGLE_FRONT_2_0_X 0 // 1030
#define alRECK_RECTANGLE_FRONT_2_0_Y -1920 // -1870

#define alRECK_RECTANGLE_FRONT_2_1_X 0 // 1030
#define alRECK_RECTANGLE_FRONT_2_1_Y -2520 // -2270

#define alRECK_RECTANGLE_FRONT_2_2_X 400 // 1430
#define alRECK_RECTANGLE_FRONT_2_2_Y -2520 // -2270

#define alRECK_RECTANGLE_FRONT_2_3_X 400 // 1430
#define alRECK_RECTANGLE_FRONT_2_3_Y -1920 // -1870

// FRONT RECTANGLE_0 (RIGHT-TOP)
#define alRECK_RECTANGLE_FRONT_3_0_X 1460 // 1030
#define alRECK_RECTANGLE_FRONT_3_0_Y -1920 // -2470

#define alRECK_RECTANGLE_FRONT_3_1_X 1460 // 1030
#define alRECK_RECTANGLE_FRONT_3_1_Y -2520 // -2870

#define alRECK_RECTANGLE_FRONT_3_2_X 1860 // 1430
#define alRECK_RECTANGLE_FRONT_3_2_Y -2520 // -2870

#define alRECK_RECTANGLE_FRONT_3_3_X 1860 // 1430
#define alRECK_RECTANGLE_FRONT_3_3_Y -1920 // -2470 

#endif

// BACK RECTANGLE_0 (LEFT)
#if alRECK_NISSAN_CHART == 0 // for 自己的長方形版
#define alRECK_RECTANGLE_BACK_0_0_X 1250 // 330
#define alRECK_RECTANGLE_BACK_0_0_Y 4370 // 2875

#define alRECK_RECTANGLE_BACK_0_1_X 1250 // 330
#define alRECK_RECTANGLE_BACK_0_1_Y 5370 // 3875

#define alRECK_RECTANGLE_BACK_0_2_X 650 // -270
#define alRECK_RECTANGLE_BACK_0_2_Y 5370 // 3875

#define alRECK_RECTANGLE_BACK_0_3_X 650 // -270
#define alRECK_RECTANGLE_BACK_0_3_Y 4370 // 2875
#else // for Nissan 板子

#define alRECK_RECTANGLE_BACK_0_0_X 1860 // 1430
#define alRECK_RECTANGLE_BACK_0_0_Y 4920 // 5020

#define alRECK_RECTANGLE_BACK_0_1_X 1860 // 1430
#define alRECK_RECTANGLE_BACK_0_1_Y 5520 // 5420

#define alRECK_RECTANGLE_BACK_0_2_X 1460 // 1030
#define alRECK_RECTANGLE_BACK_0_2_Y 5520 // 5420

#define alRECK_RECTANGLE_BACK_0_3_X 1460 // 1030
#define alRECK_RECTANGLE_BACK_0_3_Y 4920 // 5020

#define alRECK_RECTANGLE_BACK_1_0_X 400 // 830
#define alRECK_RECTANGLE_BACK_1_0_Y 4920 // 5020

#define alRECK_RECTANGLE_BACK_1_1_X 400 // 830
#define alRECK_RECTANGLE_BACK_1_1_Y 5520 // 5420

#define alRECK_RECTANGLE_BACK_1_2_X 0 // 430
#define alRECK_RECTANGLE_BACK_1_2_Y 5520 // 5420

#define alRECK_RECTANGLE_BACK_1_3_X 0 // 430
#define alRECK_RECTANGLE_BACK_1_3_Y 4920 // 5020

#endif

#endif



#define alRECK_MAX_ROI 4 // 2
#define alRECK_MAX_POINT 4
#define alRECK_MAX_POINT_VIEW 16 // 8
#define alRECK_MAX_POINT_TOTAL 50

#define alRECK_DEFAULT_CHART_SETTING_FILE	L"alRECK_CalSettingFile.ini"  // 校正場地設定檔

#ifdef __cplusplus
extern "C"
{
#endif
  
/** \brief The point struct for recording X, Y position of points. */
typedef struct
{
	FLOAT64   eX;
	FLOAT64   eY;
} alRECK_Point;

/** \brief The vector struct for recording start and end points. */
typedef struct
{
	alRECK_Point   tStart;
	alRECK_Point   tEnd;
} alRECK_Vector;


/** \brief Define the RectK ideal feild data struct . */
typedef struct
{
	/** \brief Ideal Point of RecTangle K (mm)*/
	alPointINT32 atIdealFPRecK[alRECK_MAX_POINT_TOTAL];

    /** \brief disable flag of Ideal Point of RecTangle K */
    UINT8 aucFlag[alRECK_MAX_POINT_TOTAL];
} alRECK_CalCfg;

/** \brief Define the RectK configure data struct . */
typedef struct
{
	/** \brief Scale of SBV, 2 set for each view*/
	FLOAT64 eSBVScale;

	/** \brief x offset of SBV, 2 set for each view*/
	INT32 lSBVOffsetX;

	/** \brief y offset of SBV, 2 set for each view*/
	INT32 lSBVOffsetY;

	/** \brief Point Number in ROI*/
	INT32 lPointNum;
} alRECK_ROI_Cfg;

/** \brief Define the RectK configure data struct . */
typedef struct
{
	/** \brief configure data of each ROI*/
	alRECK_ROI_Cfg atROICfg[alRECK_MAX_ROI];

	/** \brief ROI Number in view*/
	INT32 lROINum;

} alRECK_Cfg;

/** \brief Define the alRECK alRECK_Parameter data struct . */
typedef struct
{
	/** \brief Ideal Point of RecTangle K*/
	alRECK_Point atIdealPointRectK[alRECK_MAX_POINT_VIEW];

    /** \brief disable flag of Ideal Point of RecTangle K*/
    UINT8 aucPointFlag[alRECK_MAX_POINT_VIEW];

	/** \brief ROI of RecTangle K*/
	alRectINT32 atRecKROI[alRECK_MAX_ROI];

	/** \brief Fisheye Model of this view*/
	alFM_v2_1_Model *ptFisheyeModel;

	/** \brief mmpp (mm per pixel)*/
	FLOAT64 eMMPP;

	/** \brief Define the y position limitation to avoid the overflow of calculate BV to original image coordinates. */
	INT32 lOriImgYLimit;

	/** \brief camera angle for transfer SBV to BV. */
	INT32 lAngleCAM;

	/** \brief camera positionX. */
	INT32 lCamPosX;

	/** \brief camera positionY. */
	INT32 lCamPosY;

} alRECK_Parameter;
  
/*
\brief To load calibration field data from ini file. If the data loading failed, the hard coded default value will be loaded.
\param pwcIniFilePath [IN] Indicate the ini file.
\param a_ptFeildData [OUT] Feild Data
\return Return TRUE if the data loading is successful, and FALSE vice verse.
*/
BOOL alRECK_LoadRefData(wchar_t * pwcIniFileName, alRECK_CalCfg *a_ptFeildData);

/*
\brief To load default CFG data.
\param a_lMode [IN] mode
\param a_ptCFGData [IN] configure data
*/
void alRECK_LoadDefault(INT32 a_lMode, alRECK_Cfg *a_ptCFGData);


/*
\brief To load default feild data.
\param a_lMode [OUT] Feild Data
*/
void alRECK_LoadDefaultRefData(alRECK_CalCfg *a_ptFeildData);

#ifdef __cplusplus
}
#endif
  
  /**
  *  @}
  */
