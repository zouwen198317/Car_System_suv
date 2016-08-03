
#include "mtype.h"
#include "alFM_v2_1_Def.h"

/** \cond DOXYGEN_EXCLUDE */

#define alFM_v2_1_DISTORTION_CURVE_LENGTH    85

static UINT32    g_alFM_v2_1_ulImageWidth = 720;
static UINT32    g_alFM_v2_1_ulImageHeight = 480;
static UINT16    g_alFM_v2_1_uwCODX = 360;
static UINT16    g_alFM_v2_1_uwCODY = 240;

static FLOAT64   g_alFM_v2_1_eFOV_V_VCCamera = 143.068971;          // in degree
static FLOAT64   g_alFM_v2_1_eFOV_H_VCCamera = 190.075527;          // in degree
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
    107,            109.14,         111.28,         113.42,         115.56,         117.7,          119.84,         121.98,         124.12,         126.26, 
    128.4,          130.54,         132.68,         134.82,         136.96,         139.1,          141.24,         143.38,         145.52,         147.66,
    149.8,          151.94,         154.08,         156.22,         158.36,         160.5,          162.64,         164.78,         166.92,         169.06, 
    171.2,          173.34,         175.48,         177.62,         179.76,
};

static FLOAT64 g_alFM_v2_1_aeRealHeight_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{

    0,              0.032197034,    0.064394068,    0.096591103,    0.128788137,    0.160985171,    0.193182205,    0.225379239,    0.257576274,    0.289773308, 
    0.321970342,    0.354167376,    0.38636441,     0.418561445,    0.450758479,    0.482955513,    0.515152547,    0.547349581,    0.579546616,    0.61174365, 
    0.643940684,    0.676137718,    0.708334752,    0.740531787,    0.772728821,    0.804925855,    0.837122889,    0.869319924,    0.901516958,    0.932672316, 
    0.971182325,    1.009055673,    1.04632293,     1.083012295,    1.119149846,    1.154759757,    1.189864485,    1.224484941,    1.25864063,     1.292349781, 
    1.325629464,    1.358495687,    1.389756737,    1.423047011,    1.454759591,    1.486113802,    1.517121526,    1.547794001,    1.578141873,    1.608175233, 
    1.637903663,    1.667336265,    1.696481699,    1.72534821,     1.753943656,    1.782275533,    1.810350997,    1.838176887,    1.865759741,    1.89310582, 
    1.920221118,    1.947111381,    1.97378212,     2.000238627,    2.026485981,    2.052529066,    2.078372578,    2.104021037,    2.129478793,    2.154750038, 
    2.179838812,    2.204749011,    2.229484395,    2.254048594,    2.278445113,    2.302677341,    2.326748551,    2.350661913,    2.37442049,     2.398027251, 
    2.421485069,    2.444796728,    2.467964927,    2.490992281,    2.51388133, 

};

static FLOAT64 g_alFM_v2_1_aeRefHeight_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{
    0,              0.02801045,     0.05609923,     0.08434555,     0.11283041,     0.14163751,     0.1708543,      0.20057305,     0.2308921,      0.26191721, 
    0.29376321,     0.32655578,     0.36043367,     0.39555125,     0.43208161,     0.47022028,     0.51018985,     0.55224558,     0.5966824,      0.64384378, 
    0.69413291,     0.74802705,     0.80609621,     0.86902767,     0.93765855,     1.01301998,     1.0963976,      1.18941626,     1.29416081,     1.41335239, 
    1.55061247,     1.71087015,     1.90101242,     2.13096531,     2.41558016,     2.77812389,     3.25722718,     3.92207792,     4.91008992,     6.53852636,
    9.74186105,     18.99397071,    214.7423788,    -21.25289813,   -10.30604675,   -6.78974979,    -5.0518427,     -4.01317446,    -3.32081156,    -2.82512224, 
    -2.45181593,    -2.159824529,   -1.924597435,   -1.730555065,   -1.567333298,   -1.427768759,   -1.306751021,   -1.200535636,   -1.106315676,   -1.021944986,   
    -0.945753966,   -0.876423687,   -0.812897868,   -0.754320062,   -0.699988,      -0.649319867,   -0.60182901,    -0.557104723,   -0.514797454,   -0.474607293,   
    -0.436274916,   -0.399574381,   -0.364307356,   -0.330298435,   -0.297391315,   -0.265445638,   -0.234334361,   -0.203941551,   -0.174160498,   -0.144892109,   
    -0.116043492,   -0.087526722,   -0.05925772,    -0.03115524,    -0.003139916,
};

static FLOAT64 g_alFM_v2_1_aeDistortionCurve_VCCamera[alFM_v2_1_DISTORTION_CURVE_LENGTH] = 
{
    0,              0.0001,         0.0003,         0.0007,         0.0013,         0.002,          0.0028,         0.0036,         0.0045,         0.0054, 
    0.0061,         0.0067,         0.0071,         0.007,          0.0065,         0.0052,         0.0031,         -0.0001,        -0.0045,        -0.0104, 
    -0.0182,        -0.0279,        -0.0399,        -0.0544,        -0.0717,        -0.0919,        -0.1153,        -0.1421,        -0.1723,        -0.2061, 
    -0.2436,        -0.2849,        -0.33,          -0.3791,        -0.432,         -0.4889,        -0.5497,        -0.6144,        -0.683,         -0.7555, 
    -0.8317,        -0.9116,        -0.992,         -1.0823,        -1.1728,        -1.2664,        -1.3629,        -1.4621,        -1.5635,        -1.6668, 
    -1.7713,        -1.8790,        -1.9903,        -2.1056,        -2.2255,        -2.3505,        -2.4812,        -2.6185,        -2.7630,        -2.9158,
    -3.0780,        -3.2508,        -3.4359,        -3.6348,        -3.8500,        -4.0838,        -4.3394,        -4.6208,        -4.9328,        -5.2814,
    -5.6746,        -6.1225,        -6.6388,        -7.2418,        -7.9574,        -8.8226,        -9.8928,        -11.2545,       -13.0505,       -15.5359,
    -19.2135,       -25.2322,       -36.9174,       -69.5533,       -683.5687,
};

void alFM_v2_1_LoadModedCfg_VC_Curve1(alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg)
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
