
#include "mtype.h"
#include "alFM_v2_1_Def.h"

/** \cond DOXYGEN_EXCLUDE */

#define alFM_v2_1_DISTORTION_CURVE_LENGTH    51

static UINT32    g_alFM_v2_1_ulImageWidth = 720;
static UINT32    g_alFM_v2_1_ulImageHeight = 480;
static UINT16    g_alFM_v2_1_uwCODX = 360;
static UINT16    g_alFM_v2_1_uwCODY = 240;

static FLOAT64   g_alFM_v2_1_eFOV_V_VCCamera = 121.629654;          // in degree
static FLOAT64   g_alFM_v2_1_eFOV_H_VCCamera = 139.100207;          // in degree
static FLOAT64   g_alFM_v2_1_eUD_FOV_H_VCCamera = 139.100207;       // in degree, for 2D 反魚眼使用
static FLOAT64   g_alFM_v2_1_eFocalLength_VCCamera = 0.74965516;    // in mm
static UINT32    g_alFM_v2_1_ulSensorPixelWidth_VCCamera = 640;     // in pixel
static UINT32    g_alFM_v2_1_ulSensorPixelHeight_VCCamera = 480;    // in pixel
static UINT32    g_alFM_v2_1_ulSensorPixelSize_VCCamera = 5600;     // in nm
static FLOAT64   g_alFM_v2_1_eHResizeRatio_VCCamera = 1.0;          // in degree

static UINT32    g_alFM_v2_1_ulAngleTableScale_VCCamera = 1;
static UINT32    g_alFM_v2_1_ulCurveLength_VCCamera = alFM_v2_1_DISTORTION_CURVE_LENGTH;

static FLOAT64 g_alFM_v2_1_aeAngleDegree_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{
    0,              2.14,           4.28,           6.42,           8.56,           10.7,           12.84,          14.98,          17.12,          19.26,
    21.4,           23.54,          25.68,          27.82,          29.96,          32.1,           34.24,          36.38,          38.52,          40.66,
    42.8,           44.94,          47.08,          49.22,          51.36,          53.5,           55.64,          57.78,          59.92,          62.06,
    64.2,           66.34,          68.48,          70.62,          72.76,          74.9,           77.04,          79.18,          81.32,          83.46,
    85.6,           87.74,          89.8,           92.02,          94.16,          96.3,           98.44,          100.58,         102.72,         104.86,
    107,
};

static FLOAT64 g_alFM_v2_1_aeRealHeight_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{
    0,              0.02801045,     0.05609923,     0.08434555,     0.11283041,     0.14163751,     0.1708543,      0.20057305,     0.2308921,      0.26191721, 
    0.29376321,     0.32655578,     0.36043367,     0.39555125,     0.43208161,     0.47022028,     0.51018985,     0.55224558,     0.5966824,      0.64384378, 
    0.69413291,     0.74802705,     0.80609621,     0.86902767,     0.93765855,     1.01301998,     1.0963976,      1.18941626,     1.29416081,     1.41335239, 
    1.55061247,     1.71087015,     1.90101242,     2.13096531,     2.41558016,     2.77812389,     3.25722718,     3.92207792,     4.91008992,     6.53852636,
    9.74186105,     18.99397071,    214.7423788,    -21.25289813,   -10.30604675,   -6.78974979,    -5.0518427,     -4.01317446,    -3.32081156,    -2.82512224, 
    -2.45181593,
};

static FLOAT64 g_alFM_v2_1_aeRefHeight_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{
    0,              0.02801045,     0.05609923,     0.08434555,     0.11283041,     0.14163751,     0.1708543,      0.20057305,     0.2308921,      0.26191721, 
    0.29376321,     0.32655578,     0.36043367,     0.39555125,     0.43208161,     0.47022028,     0.51018985,     0.55224558,     0.5966824,      0.64384378, 
    0.69413291,     0.74802705,     0.80609621,     0.86902767,     0.93765855,     1.01301998,     1.0963976,      1.18941626,     1.29416081,     1.41335239, 
    1.55061247,     1.71087015,     1.90101242,     2.13096531,     2.41558016,     2.77812389,     3.25722718,     3.92207792,     4.91008992,     6.53852636,
    9.74186105,     18.99397071,    214.7423788,    -21.25289813,   -10.30604675,   -6.78974979,    -5.0518427,     -4.01317446,    -3.32081156,    -2.82512224, 
    -2.45181593,
};

static FLOAT64 g_alFM_v2_1_aeDistortionCurve_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{
    0,              0.0001,         0.0003,         0.0007,         0.0013,         0.002,          0.0028,         0.0036,         0.0045,         0.0054, 
    0.0061,         0.0067,         0.0071,         0.007,          0.0065,         0.0052,         0.0031,         -0.0001,        -0.0045,        -0.0104, 
    -0.0182,        -0.0279,        -0.0399,        -0.0544,        -0.0717,        -0.0919,        -0.1153,        -0.1421,        -0.1723,        -0.2061, 
    -0.2436,        -0.2849,        -0.33,          -0.3791,        -0.432,         -0.4889,        -0.5497,        -0.6144,        -0.683,         -0.7555, 
    -0.8317,        -0.9116,        -0.992,         -1.0823,        -1.1728,        -1.2664,        -1.3629,        -1.4621,        -1.5635,        -1.6668, 
    -1.7713,
};

void alFM_v2_1_LoadModedCfg_VC_NoFisheye(alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg)
{
    UINT16 uwDI;

    a_ptFM_v2_Cfg->ulImageWidth = g_alFM_v2_1_ulImageWidth;
    a_ptFM_v2_Cfg->ulImageHeight = g_alFM_v2_1_ulImageHeight;
    a_ptFM_v2_Cfg->uwCOD_X = g_alFM_v2_1_uwCODX;
    a_ptFM_v2_Cfg->uwCOD_Y = g_alFM_v2_1_uwCODY;

    a_ptFM_v2_Cfg->uwSrcSensorWidth = g_alFM_v2_1_ulSensorPixelWidth_VCCamera;
    a_ptFM_v2_Cfg->ulSensorPixelSize = g_alFM_v2_1_ulSensorPixelSize_VCCamera;
    a_ptFM_v2_Cfg->uwLengthOfDistortionCurve = g_alFM_v2_1_ulCurveLength_VCCamera;
    a_ptFM_v2_Cfg->uwAngleTableScale = g_alFM_v2_1_ulAngleTableScale_VCCamera;
    a_ptFM_v2_Cfg->eFocalLength = g_alFM_v2_1_eFocalLength_VCCamera;
    a_ptFM_v2_Cfg->eFOV_H = g_alFM_v2_1_eFOV_H_VCCamera;
    a_ptFM_v2_Cfg->eUD_FOV_H = g_alFM_v2_1_eUD_FOV_H_VCCamera;
    a_ptFM_v2_Cfg->eHResizeRatio = g_alFM_v2_1_eHResizeRatio_VCCamera;

    for(uwDI = 0; uwDI < g_alFM_v2_1_ulCurveLength_VCCamera; uwDI++)
    {
        a_ptFM_v2_Cfg->aeAngleDegree[uwDI] = g_alFM_v2_1_aeAngleDegree_VCCamera[uwDI];
        a_ptFM_v2_Cfg->aeRealHeight[uwDI] = g_alFM_v2_1_aeRealHeight_VCCamera[uwDI];
#if 0
        a_ptFM_v2_Cfg->aeRefHeight[uwDI] = g_alFM_v2_1_aeRefHeight_VCCamera[uwDI];
        a_ptFM_v2_Cfg->aeDistortion[uwDI] = g_alFM_v2_1_aeDistortionCurve_VCCamera[uwDI];
#endif
    }
}

#undef alFM_v2_1_DISTORTION_CURVE_LENGTH

/** \endcond DOXYGEN_EXCLUDE */
