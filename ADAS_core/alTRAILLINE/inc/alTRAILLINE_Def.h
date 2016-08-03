
#pragma once

#include "mtype.h"


/**
*  \addtogroup TrailLine
*  @{
*/

//// for default setting ///
#define SIM_DEFAULT_CAR_LEN_TRAILLINE  		                4862        // 車輛長度(mm)		
#define SIM_DEFAULT_CAR_MAX_STEER_ANGLE_TRAILLINE             720	        // 方向盤最大舵角(mm)

/* Default Config for Trailline */
#define SIM_DEFAULT_TL_STEER_ANGLE_INTERVAL     30          // in degree
#define SIM_DEFAULT_TL_LINE_WIDTH               4           // in pixel
#define SIM_DEFAULT_CAR_STEER_PARA_A            (0.0588f)	// 方向盤舵角與車輛轉向角關係式 φ= a * θ + b
#define SIM_DEFAULT_CAR_STEER_PARA_B            (-0.532f)	// 方向盤舵角與車輛轉向角關係式 φ= a * θ + b
//#define SIM_DEFAULT_CAR_CEN2LEFTMIRROR_DISTANCE 300         // 車幅線縱線從左、右後視鏡外緣向外延伸距離 in mm

/* static trail line - front */
#define SIM_DEFAULT_STL_F_ENABLE                 1
#define SIM_DEFAULT_STL_F_STYLE                  0       // (0: line, 1: hook, 2: linked)
#define SIM_DEFAULT_STL_F_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_STL_F_HORI_COUNT             4       
#define SIM_DEFAULT_STL_F_HORI_POS_1             (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 250))       // in mm
#define SIM_DEFAULT_STL_F_HORI_POS_2             (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 500))       // in mm
#define SIM_DEFAULT_STL_F_HORI_POS_3             (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 1000))      // in mm 
#define SIM_DEFAULT_STL_F_HORI_POS_4             (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 2000))      // in mm 
#define SIM_DEFAULT_STL_F_HORI_POS_5             0
#define SIM_DEFAULT_STL_F_COLOR_IDX_1            3      // Red
#define SIM_DEFAULT_STL_F_COLOR_IDX_2            6      // Yellow
#define SIM_DEFAULT_STL_F_COLOR_IDX_3            4      // Green
#define SIM_DEFAULT_STL_F_COLOR_IDX_4            0
#define SIM_DEFAULT_STL_F_COLOR_IDX_5            0
#define SIM_DEFAULT_STL_F_VERT_STYLE             0
#define SIM_DEFAULT_STL_F_VERT_COUNT             2
#define SIM_DEFAULT_STL_F_VERT_POS_1             (-920-100)//(-1105-50)   // in mm
#define SIM_DEFAULT_STL_F_VERT_POS_2             (920+100)//(1081+50)     // in mm 
#define SIM_DEFAULT_STL_F_DASH_LENGTH_HORI       (200)         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_1     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_2     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_3     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_4     0         // in mm
#define SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_5     0         // in mm

/* static trail line - back */
#define SIM_DEFAULT_STL_B_ENABLE                 1
#define SIM_DEFAULT_STL_B_STYLE                  2       // (0: line, 1: hook, 2: linked)
#define SIM_DEFAULT_STL_B_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_STL_B_HORI_COUNT             4       
#define SIM_DEFAULT_STL_B_HORI_POS_1             ((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 250)       // in mm
#define SIM_DEFAULT_STL_B_HORI_POS_2             ((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 500)       // in mm
#define SIM_DEFAULT_STL_B_HORI_POS_3             ((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 1000)      // in mm 
#define SIM_DEFAULT_STL_B_HORI_POS_4             ((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 2000)      // in mm 
#define SIM_DEFAULT_STL_B_HORI_POS_5             0
#define SIM_DEFAULT_STL_B_COLOR_IDX_1            3      // Red
#define SIM_DEFAULT_STL_B_COLOR_IDX_2            6      // Yellow
#define SIM_DEFAULT_STL_B_COLOR_IDX_3            4      // Green
#define SIM_DEFAULT_STL_B_COLOR_IDX_4            0
#define SIM_DEFAULT_STL_B_COLOR_IDX_5            0
#define SIM_DEFAULT_STL_B_VERT_STYLE             0
#define SIM_DEFAULT_STL_B_VERT_COUNT             2
#define SIM_DEFAULT_STL_B_VERT_POS_1             (-920-100)//(-1105-50)   // in mm
#define SIM_DEFAULT_STL_B_VERT_POS_2             (920+100)//(1081+50)     // in mm 
#define SIM_DEFAULT_STL_B_DASH_LENGTH_HORI       (200)          // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_1     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_2     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_3     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_4     0         // in mm
#define SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_5     0         // in mm

/* dynamic trail line - front */
#define SIM_DEFAULT_DTL_F_ENABLE                 1
#define SIM_DEFAULT_DTL_F_STYLE                  0       // (0: without hori line, 1: with hori line)
#define SIM_DEFAULT_DTL_F_VERT_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_F_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_F_HORI_START_POS         (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 250))     // in mm: 車頭往前 250 mm
#define SIM_DEFAULT_DTL_F_HORI_END_POS           (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 2000))    // in mm: 車頭往前 2250 mm
#define SIM_DEFAULT_DTL_F_VERT_POS_1             (-920-100)//(-1105-50)   // in mm
#define SIM_DEFAULT_DTL_F_VERT_POS_2             (920+100)//(1081+50)     // in mm 
#define SIM_DEFAULT_DTL_F_COLOR_IDX_1            9       // Orange
#define SIM_DEFAULT_DTL_F_COLOR_IDX_2            9       // Orange      
#define SIM_DEFAULT_DTL_F_SHORT_LINE_DISABLE_ANGLE         720     // 正負一定角度後，不顯示短邊的動態車幅線

/* dynamic trail line - back */
#define SIM_DEFAULT_DTL_B_ENABLE                 1
#define SIM_DEFAULT_DTL_B_STYLE                  1       // (0: without hori line, 1: with hori line)
#define SIM_DEFAULT_DTL_B_VERT_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_B_HORI_STYLE             0       // (0: solid, 1: dash)
#define SIM_DEFAULT_DTL_B_HORI_START_POS         (((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 250))     // in mm: 車尾往後 250 mm
#define SIM_DEFAULT_DTL_B_HORI_END_POS           (((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 2000))    // in mm: 車尾往後 2250 mm
#define SIM_DEFAULT_DTL_B_VERT_POS_1             (-920-100)//(-1105-50)   // in mm
#define SIM_DEFAULT_DTL_B_VERT_POS_2             (920+100)//(1081+50)     // in mm 
#define SIM_DEFAULT_DTL_B_COLOR_IDX_1            9       // Orange
#define SIM_DEFAULT_DTL_B_COLOR_IDX_2            9       // Orange
#define SIM_DEFAULT_DTL_B_SHORT_LINE_DISABLE_ANGLE         (SIM_DEFAULT_CAR_MAX_STEER_ANGLE_TRAILLINE)     // 正負一定角度後，不顯示短邊的動態車幅線

/* warning trail line - front */
#define SIM_DEFAULT_WTL_F_ENABLE                 0
#define SIM_DEFAULT_WTL_F_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_F_LINE_1_COLOR           3       // Red       
#define SIM_DEFAULT_WTL_F_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_F_LINE_1_POS_1_X         (-1105)
#define SIM_DEFAULT_WTL_F_LINE_1_POS_1_Y         (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 400))       // in mm   // in mm
#define SIM_DEFAULT_WTL_F_LINE_1_POS_2_X         (1081)
#define SIM_DEFAULT_WTL_F_LINE_1_POS_2_Y         (-((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 400))       // in mm   // in mm
#define SIM_DEFAULT_WTL_F_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_F_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_2_PIECE           0	     // (number of dash line)	
#define SIM_DEFAULT_WTL_F_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_F_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_F_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_F_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_F_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_F_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_3_PIECE           0	     // (number of dash line)	
#define SIM_DEFAULT_WTL_F_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_F_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_F_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_F_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_F_LINE_4_COLOR           0       
#define SIM_DEFAULT_WTL_F_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_F_LINE_4_PIECE           0	     // (number of dash line)	
#define SIM_DEFAULT_WTL_F_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_F_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_F_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_F_LINE_4_POS_2_Y         0

/* warning trail line - back */
#define SIM_DEFAULT_WTL_B_ENABLE                 0
#define SIM_DEFAULT_WTL_B_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_B_LINE_1_COLOR           3       // Red        
#define SIM_DEFAULT_WTL_B_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_1_POS_1_X         (-1105)
#define SIM_DEFAULT_WTL_B_LINE_1_POS_1_Y         ((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 200)       // in mm
#define SIM_DEFAULT_WTL_B_LINE_1_POS_2_X         (1081)
#define SIM_DEFAULT_WTL_B_LINE_1_POS_2_Y         ((SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 200)       // in mm
#define SIM_DEFAULT_WTL_B_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_B_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_2_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_B_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_B_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_B_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_B_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_B_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_3_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_B_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_B_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_B_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_B_LINE_4_COLOR           0       
#define SIM_DEFAULT_WTL_B_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_B_LINE_4_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_B_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_B_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_B_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_B_LINE_4_POS_2_Y         0

/* warning trail line - left */
#define SIM_DEFAULT_WTL_L_ENABLE                 0
#define SIM_DEFAULT_WTL_L_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_L_LINE_1_COLOR           0       
#define SIM_DEFAULT_WTL_L_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_1_POS_1_X         (-1105)
#define SIM_DEFAULT_WTL_L_LINE_1_POS_1_Y         (-(SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) - 400)       // in mm
#define SIM_DEFAULT_WTL_L_LINE_1_POS_2_X         (-1105)
#define SIM_DEFAULT_WTL_L_LINE_1_POS_2_Y         ( (SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 200)       // in mm
#define SIM_DEFAULT_WTL_L_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_L_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_2_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_L_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_L_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_L_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_L_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_L_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_3_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_L_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_L_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_L_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_L_LINE_4_COLOR           0      
#define SIM_DEFAULT_WTL_L_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_L_LINE_4_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_L_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_L_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_L_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_L_LINE_4_POS_2_Y         0

/* warning trail line - right */
#define SIM_DEFAULT_WTL_R_ENABLE                 0
#define SIM_DEFAULT_WTL_R_LINE_COUNT             1       
#define SIM_DEFAULT_WTL_R_LINE_1_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_1_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_1_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_1_POS_1_X         (1081)
#define SIM_DEFAULT_WTL_R_LINE_1_POS_1_Y         (-(SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) - 400)       // in mm
#define SIM_DEFAULT_WTL_R_LINE_1_POS_2_X         (1081)
#define SIM_DEFAULT_WTL_R_LINE_1_POS_2_Y         ( (SIM_DEFAULT_CAR_LEN_TRAILLINE>>1) + 200)       // in mm
#define SIM_DEFAULT_WTL_R_LINE_2_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_2_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_2_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_2_POS_1_X         0
#define SIM_DEFAULT_WTL_R_LINE_2_POS_1_Y         0
#define SIM_DEFAULT_WTL_R_LINE_2_POS_2_X         0
#define SIM_DEFAULT_WTL_R_LINE_2_POS_2_Y         0
#define SIM_DEFAULT_WTL_R_LINE_3_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_3_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_3_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_3_POS_1_X         0
#define SIM_DEFAULT_WTL_R_LINE_3_POS_1_Y         0
#define SIM_DEFAULT_WTL_R_LINE_3_POS_2_X         0
#define SIM_DEFAULT_WTL_R_LINE_3_POS_2_Y         0
#define SIM_DEFAULT_WTL_R_LINE_4_COLOR           0       
#define SIM_DEFAULT_WTL_R_LINE_4_STYLE           0       // (0: solid, 1: dash)
#define SIM_DEFAULT_WTL_R_LINE_4_PIECE           0	     // (number of dash line)
#define SIM_DEFAULT_WTL_R_LINE_4_POS_1_X         0
#define SIM_DEFAULT_WTL_R_LINE_4_POS_1_Y         0
#define SIM_DEFAULT_WTL_R_LINE_4_POS_2_X         0
#define SIM_DEFAULT_WTL_R_LINE_4_POS_2_Y         0
//// for default setting ///


#define MAX_VERTICAL_POS_NUM        2
#define MAX_HORIZONTAL_POS_NUM      5
#define MAX_WAR_LINE_NUM            4
#define MAX_DYNAMIC_NUM             2

#define MAX_LINEDATA_NUM            500         // 每一個 Output Data 最多可以記錄的點數
#define DTL_PIECE_NUM               41          // 動態車幅線 - 直接切 41 段(縱線)
#define MAX_PIECE_LENGTH            10          // 靜態車幅線至少 0.8 pixel (BV 座標) 要有一個點
#define MAX_SUPPORT_STEERING_ANGLE  900         // 方向盤最大舵角支援 : 900 deg
#define MIN_SUPPORT_STEERING_ANGLE_PERIOD  5   // 方向盤最小舵角間隔 : 15 deg
#define MAX_DYNAMIC_TRAIL_LINE_NUM  ((MAX_SUPPORT_STEERING_ANGLE/MIN_SUPPORT_STEERING_ANGLE_PERIOD)*2+1)          // 假設單邊最大 900 deg, 間隔 30 deg, 總共 (900/30) * 2 + 1 = 61

#define TRAIL_HEADER_RESERVED       22         

#ifdef __cplusplus
extern "C"
{
#endif


/** \brief Define index of type for Trail Line. */
typedef enum 
{

    alTRAILLINE_STL_LEFT     = 0,   // 0 for Static Left View
    alTRAILLINE_STL_RIGHT    = 1,   // 1 for Static Right View
    alTRAILLINE_STL_FRONT    = 2,   // 2 for Static Front View
    alTRAILLINE_STL_BACK      = 3,   // 3 for Static Back View
    alTRAILLINE_DTL_FRONT    = 4,   // 4 for Dynamic Front View
    alTRAILLINE_DTL_BACK     = 5,   // 5 for Dynamic Back View

} alTRAILLINE_TL_INDX;

/** \brief Define color index for Trail Line. */
typedef enum 
{

    alTRAILLINE_TL_C_NULL       = 0, //0 for NULL
    alTRAILLINE_TL_C_WHITE      = 1, // 1 for white (255,255,255)
    alTRAILLINE_TL_C_BLACK      = 2, // 2 for black (0,0,0)
    alTRAILLINE_TL_C_RED        = 3, // 3 for red  (255,0,0)
    alTRAILLINE_TL_C_GREEN      = 4, // 4 for green (0,255,0)
    alTRAILLINE_TL_C_BLUE       = 5, // 5 for blue (0,0,255)
    alTRAILLINE_TL_C_YELLOW     = 6, // 6 for yellow (255,255,0)
    alTRAILLINE_TL_C_CYAN       = 7, // 7 for cyan (0,255,255)
    alTRAILLINE_TL_C_PINK       = 8, // 8 for pink (255,0,255)
    alTRAILLINE_TL_C_ORANGE     = 9, // 9 for orange (255,128,0)
	alTRAILLINE_TL_C_GL_RED     = 10, // 10 for Geely scarlet (136,40,38)
	alTRAILLINE_TL_C_GL_YELLOW  = 11, // 11 for Geely yellow (252,255,160)
	alTRAILLINE_TL_C_GL_GREEN   = 12, // 12 for Gelly green (99,195,96)
	alTRAILLINE_TL_C_MVEV_GREEN   = 13, // 13 for YL_MVEV green (0,206,0)
	alTRAILLINE_TL_C_MVEV_ORANGE   = 14, // 14 for YL_MVEV orange (255,131,0)

} alTRAILLINE_TL_COLOR;

/** \brief A struct to record general setting information for Trail Line. */
typedef struct
{
    /** \brief 汽車寬度(mm) */
    UINT16 uwCarWidth_mm;            
    /** \brief 汽車長度(mm) */
    UINT16 uwCarLength_mm;          
    /** \brief BirdView在畫面中起始座標of720X480 */
    INT32  lBV_StartX;               
    /** \brief BirdView在畫面中起始座標of720X480 */
    INT32  lBV_StartY;               
    /** \brief Car 中心在畫面中的座標 X */
    INT32  lBV_CAR_CenterX;          
    /** \brief Car 中心在畫面中的座標 Y */
    INT32  lBV_CAR_CenterY;          
    /** \brief Birdbiew上要看到多遠 預設三公尺 = 3000mm */
    INT32  lBirdViewRange;           
    /** \brief 後(前)輪軸寬(mm) */
    UINT16 uwTrackWidth_mm;          
    /** \brief 前後輪軸距離 */
    UINT16 uwWheelBase_mm;           
    /** \brief 後輪軸心到車尾距離(cm) */
    UINT16 uwAxisToBack_mm;          
    /** \brief 方向盤可轉最大角度 */
    UINT16 uwMax_Wheel_Angle;        
    /** \brief 動態車軸線描繪的角度間隔  */
    UINT16 uwSteeringAngleInterval;    
    /** \brief mmpp of alAVM2D */
    FLOAT32 fMMPP;                 
    /** \brief 車幅線預設寬度, pixel */
    UINT8 ucLineThickness;              
    /** \brief 方向盤舵角與車輛轉向角關係式 φ= a * θ + b */
    FLOAT32 fSteerParamA;           
    /** \brief 方向盤舵角與車輛轉向角關係式 φ= a * θ + b */
    FLOAT32 fSteerParamB;        
} alTRAILLINE_Params;

/** \brief A struct to record setting information for Static Trail Line. */
typedef struct
{

    /* \breif Indicate is the warning line enable in the current view. */
    UINT8 ucIsEnable;
    UINT8 ucTrailStyle;//0: line 1:hook 2:linked, style,
    UINT8 ucHoriLineStyle;
    UINT8 ucHorizonCount;
    INT16 wHorizonLinePosition[MAX_HORIZONTAL_POS_NUM];//座標:車身中心為原點,往後為正(為同影像座標)
    UINT8 ucHoriLineColorIndex[MAX_HORIZONTAL_POS_NUM];
    UINT8 ucVertLineStyle;
    UINT8 ucVerticalCount;
    INT16 wVerticalLinePosition[MAX_VERTICAL_POS_NUM];//座標:車身中心為原點,往右為正
    UINT16 uwDashLengthHori;//勾狀時水平方向的短線線長, in mm
	INT16 wDashLengthVert[MAX_HORIZONTAL_POS_NUM];//勾狀時垂直方向的短線線長, in mm

} alTRAILLINE_StaticTrailLineInfo;

/** \brief Config data for the warning lines of a single view. */
typedef struct //Warning
{
    /* \brief Indicate is the warning line enable in the current view. */
    UINT8 ucIsEnable;
    /* \brief Warning line count in the current view. */
    UINT8 ucLineCount;
	/* \breif Number of dash line in Warning line in the current view. */
    UINT8 ucPieceCount[MAX_WAR_LINE_NUM];
    /* \brief Indicate if the warning line enable in the current view. */
    UINT8 ucWarningLineColor[MAX_WAR_LINE_NUM];
    /* \brief Record the start and end points of warning lines. */
    INT16 wWarningLinePos[MAX_WAR_LINE_NUM][4];//兩點座標
    /* \brief Indicate the style of warning lines. */
    UINT8 ucWarningLineStyle[MAX_WAR_LINE_NUM];

} alTRAILLINE_WarningLineInfo;

/** \brief A struct to record setting information for dynamic Trail Line. */
typedef struct
{

    /* \brief Indicate is the warning line enable in the current view. */
    UINT8 ucIsEnable;
    UINT8 ucTrailStyle;//0: no horiLine, 1 :with
    UINT8 ucLineStyle[2];//([0]:vertical, [1]: horizontal)
    INT16 wHoriStartPos;
    INT16 wHoriEndPos;
    UINT8 ucType;//only 4 or 5/ dynamic Front or dynamic Rear.
    INT16 wVerticalLinePos[MAX_DYNAMIC_NUM];
    UINT8 ucColorIndex[MAX_DYNAMIC_NUM];
    INT16 wShortLineDisableAngle;

} alTRAILLINE_DynamicTrailLineInfo;

/** \brief A struct to record the config data for trail lines. */
typedef struct
{
    /** \brief The steering angle interval for dynamic trial line. */
    UINT16 uwSteeringAngleInterval;
    /** \brief The thickness of trail line, pixel. */
    UINT8 ucLineThickness;

    /** \brief The config data for static trail line. */
    alTRAILLINE_StaticTrailLineInfo atSTLCfg[2];
    /** \brief The config data for dynamic trail line. */
    alTRAILLINE_DynamicTrailLineInfo atDTLCfg[2];
    /** \brief The config data for warning trail line. */
    alTRAILLINE_WarningLineInfo atWLCfg[4];

} alTRAILLINE_Cfg;

//#pragma pack(1) // 使用 BYTE 的記憶體對齊

/** \brief A struct to record one point pair for line drawing. Reserve total 16 bytes for each line. */
typedef struct
{

    UINT8 cThickness;    // unit by pixel
    UINT8 cColor;       
    
    UINT16 cLineType;    // 0 for solid
		                 // 1 for dashed
    UINT16 wStartX;
    UINT16 wStartY;
    UINT16 wEndX;
    UINT16 wEndY;
    UINT8 ucReserve[4];  // reserve 4 bytes

} alTRAILLINE_PairData;

/** \brief The header of trail line for single view.  */
typedef struct
{
    /* 
       \brief Type of the current trail line: static/dynamic?, which view? 
       \see alTRAILLINE_TL_INDX
    */
    UINT16 wType;
    /*  \brief Number of the points pair (start/end points). This indicates size of drawData. */
    UINT16 wNumOfPairs;
    /*  \brief Total size of this line data. (16 byte * wNumOfPairs) */
    UINT32 wLineDataSize;
    /** \brief The degree of steer angle for dynamic trail line only. */
    INT16 wRot_degree;// using only when type == 4 or 5
    /** \brief Reserve TRAIL_HEADER_RESERVED bytes. */
    UINT8 ucReserve[TRAIL_HEADER_RESERVED - sizeof(alTRAILLINE_PairData*)];
    /*  \brief Record all line point pairs. */
    alTRAILLINE_PairData * pDrawLineData;

} alTRAILLINE_LineHeader;


/** \brief A struct to store all the trail line runtime data. */
typedef struct
{

    /** \brief working buffer */
    UINT8   *pucTLWorkingBuffer;

} alTRAILLINE_Data;

/** \brief A struct to store all the trail line data. */
typedef struct
{

    /** \brief Number of frames for dynamic trail line. This is counted by:  1 + 2 * (maximun steer angle) / (steer angle interval) */
    UINT16                       uwDTLCount;
    /** \brief Store static trail line for 4 views (Left/Right/Front/Rear). Warning lines are included in static trail line. */
    alTRAILLINE_LineHeader         aStaticTrailLine[4];
    /** \brief Store dynamic trail line for 2 views (Front/Rear). */
    alTRAILLINE_LineHeader         aDynamicTrailLine[2][MAX_DYNAMIC_TRAIL_LINE_NUM];

} alTRAILLINE_LineSet;



/** 
\brief To load the Trail Line default setting from .h files. 
\param a_ptCfg [INOUT] configure
*/
void alTRAILLINE_LoadDefault(alTRAILLINE_Cfg *a_ptCfg);

/** 
\brief To load the Trail Line configure setting from INI files. 
\param a_pwcConfigFilePath [IN] The file path
\param a_ptCfg [INOUT] configure
*/
void alTRAILLINE_CfgImportByINI(wchar_t * a_pwcConfigFilePath, alTRAILLINE_Cfg *a_ptCfg);


/**
\brief Cfg Export to Hex file
\param a_ulSectionID [IN] Section ID
\param a_ptCfg [IN] trail line Config data
\param a_pucDataSectionBuffer [OUT] Data Section Buffer for output
*/
UINT32 alTRAILLINE_CfgExportHex(
    UINT32 a_ulSectionID,
    alTRAILLINE_Cfg *a_ptCfg,
    UINT8 *a_pucDataSectionBuffer
    );

/**
\brief Cfg Import by Hex file (1300-2)
\param a_ulDataID [IN] Data ID
\param a_ulDataLength [IN] Data Length
\param a_pulBuffer [IN] Data Section Buffer for reading
*/
void alTRAILLINE_CfgImportHex(
    UINT32 a_ulDataID,
    UINT32 a_ulDataLength, UINT8 * a_pucBuffer,
    alTRAILLINE_Cfg *a_ptCfg
    );


/**
  *  @}
  */

//#pragma pack()  // 使用預設的記憶體對齊

#ifdef __cplusplus
}
#endif
