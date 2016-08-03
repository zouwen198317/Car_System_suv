
#include "alTRAILLINE_Def.h"
#include "alHexData.h"
#include "basedef.h"
#ifdef WIN32
#include "alINI.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alTRAILLINE_LoadDefault(alTRAILLINE_Cfg *a_ptCfg)
{

    a_ptCfg->uwSteeringAngleInterval = SIM_DEFAULT_TL_STEER_ANGLE_INTERVAL;
    a_ptCfg->ucLineThickness = SIM_DEFAULT_TL_LINE_WIDTH;

    /* Static trail line - front */
    a_ptCfg->atSTLCfg[0].ucIsEnable = SIM_DEFAULT_STL_F_ENABLE;
    a_ptCfg->atSTLCfg[0].ucTrailStyle = SIM_DEFAULT_STL_F_STYLE;
    a_ptCfg->atSTLCfg[0].ucHoriLineStyle = SIM_DEFAULT_STL_F_HORI_STYLE;
    a_ptCfg->atSTLCfg[0].ucHorizonCount = SIM_DEFAULT_STL_F_HORI_COUNT;
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[0] = SIM_DEFAULT_STL_F_HORI_POS_1;
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[1] = SIM_DEFAULT_STL_F_HORI_POS_2;
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[2] = SIM_DEFAULT_STL_F_HORI_POS_3;
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[3] = SIM_DEFAULT_STL_F_HORI_POS_4;
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[4] = SIM_DEFAULT_STL_F_HORI_POS_5;
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[0] = SIM_DEFAULT_STL_F_COLOR_IDX_1;
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[1] = SIM_DEFAULT_STL_F_COLOR_IDX_2;
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[2] = SIM_DEFAULT_STL_F_COLOR_IDX_3;
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[3] = SIM_DEFAULT_STL_F_COLOR_IDX_4;
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[4] = SIM_DEFAULT_STL_F_COLOR_IDX_5;
    a_ptCfg->atSTLCfg[0].ucVertLineStyle = SIM_DEFAULT_STL_F_VERT_STYLE;
    a_ptCfg->atSTLCfg[0].ucVerticalCount = SIM_DEFAULT_STL_F_VERT_COUNT;
    a_ptCfg->atSTLCfg[0].wVerticalLinePosition[0] = SIM_DEFAULT_STL_F_VERT_POS_1;
    a_ptCfg->atSTLCfg[0].wVerticalLinePosition[1] = SIM_DEFAULT_STL_F_VERT_POS_2;
    a_ptCfg->atSTLCfg[0].uwDashLengthHori = SIM_DEFAULT_STL_F_DASH_LENGTH_HORI;
	a_ptCfg->atSTLCfg[0].wDashLengthVert[0] = SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_1;
	a_ptCfg->atSTLCfg[0].wDashLengthVert[1] = SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_2; 
	a_ptCfg->atSTLCfg[0].wDashLengthVert[2] = SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_3; 
	a_ptCfg->atSTLCfg[0].wDashLengthVert[3] = SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_4; 
	a_ptCfg->atSTLCfg[0].wDashLengthVert[4] = SIM_DEFAULT_STL_F_DASH_LENGTH_VERT_5; 

    /* Static trail line - back */
    a_ptCfg->atSTLCfg[1].ucIsEnable = SIM_DEFAULT_STL_B_ENABLE;
    a_ptCfg->atSTLCfg[1].ucTrailStyle = SIM_DEFAULT_STL_B_STYLE;
    a_ptCfg->atSTLCfg[1].ucHoriLineStyle = SIM_DEFAULT_STL_B_HORI_STYLE;
    a_ptCfg->atSTLCfg[1].ucHorizonCount = SIM_DEFAULT_STL_B_HORI_COUNT;
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[0] = SIM_DEFAULT_STL_B_HORI_POS_1;
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[1] = SIM_DEFAULT_STL_B_HORI_POS_2;
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[2] = SIM_DEFAULT_STL_B_HORI_POS_3;
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[3] = SIM_DEFAULT_STL_B_HORI_POS_4;
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[4] = SIM_DEFAULT_STL_B_HORI_POS_5;
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[0] = SIM_DEFAULT_STL_B_COLOR_IDX_1;
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[1] = SIM_DEFAULT_STL_B_COLOR_IDX_2;
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[2] = SIM_DEFAULT_STL_B_COLOR_IDX_3;
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[3] = SIM_DEFAULT_STL_B_COLOR_IDX_4;
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[4] = SIM_DEFAULT_STL_B_COLOR_IDX_5;
    a_ptCfg->atSTLCfg[1].ucVertLineStyle = SIM_DEFAULT_STL_B_VERT_STYLE;
    a_ptCfg->atSTLCfg[1].ucVerticalCount = SIM_DEFAULT_STL_B_VERT_COUNT;
    a_ptCfg->atSTLCfg[1].wVerticalLinePosition[0] = SIM_DEFAULT_STL_B_VERT_POS_1;
    a_ptCfg->atSTLCfg[1].wVerticalLinePosition[1] = SIM_DEFAULT_STL_B_VERT_POS_2;
	a_ptCfg->atSTLCfg[1].uwDashLengthHori = SIM_DEFAULT_STL_B_DASH_LENGTH_HORI;
	a_ptCfg->atSTLCfg[1].wDashLengthVert[0] = SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_1;
	a_ptCfg->atSTLCfg[1].wDashLengthVert[1] = SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_2; 
	a_ptCfg->atSTLCfg[1].wDashLengthVert[2] = SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_3; 
	a_ptCfg->atSTLCfg[1].wDashLengthVert[3] = SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_4; 
	a_ptCfg->atSTLCfg[1].wDashLengthVert[4] = SIM_DEFAULT_STL_B_DASH_LENGTH_VERT_5; 

    /* Dynamic trail line - front */
    a_ptCfg->atDTLCfg[0].ucIsEnable = SIM_DEFAULT_DTL_F_ENABLE;
    a_ptCfg->atDTLCfg[0].ucTrailStyle = SIM_DEFAULT_DTL_F_STYLE;
    a_ptCfg->atDTLCfg[0].ucLineStyle[0] = SIM_DEFAULT_DTL_F_VERT_STYLE;
    a_ptCfg->atDTLCfg[0].ucLineStyle[1] = SIM_DEFAULT_DTL_F_HORI_STYLE;
    a_ptCfg->atDTLCfg[0].wHoriStartPos = SIM_DEFAULT_DTL_F_HORI_START_POS;
    a_ptCfg->atDTLCfg[0].wHoriEndPos = SIM_DEFAULT_DTL_F_HORI_END_POS;
    a_ptCfg->atDTLCfg[0].wVerticalLinePos[0] = SIM_DEFAULT_DTL_F_VERT_POS_1;
    a_ptCfg->atDTLCfg[0].wVerticalLinePos[1] = SIM_DEFAULT_DTL_F_VERT_POS_2;
    a_ptCfg->atDTLCfg[0].ucColorIndex[0] = SIM_DEFAULT_DTL_F_COLOR_IDX_1;
    a_ptCfg->atDTLCfg[0].ucColorIndex[1] = SIM_DEFAULT_DTL_F_COLOR_IDX_2;
    a_ptCfg->atDTLCfg[0].wShortLineDisableAngle = SIM_DEFAULT_DTL_F_SHORT_LINE_DISABLE_ANGLE;

    /* Dynamic trail line - back */
    a_ptCfg->atDTLCfg[1].ucIsEnable = SIM_DEFAULT_DTL_B_ENABLE;
    a_ptCfg->atDTLCfg[1].ucTrailStyle = SIM_DEFAULT_DTL_B_STYLE;
    a_ptCfg->atDTLCfg[1].ucLineStyle[0] = SIM_DEFAULT_DTL_B_VERT_STYLE;
    a_ptCfg->atDTLCfg[1].ucLineStyle[1] = SIM_DEFAULT_DTL_B_HORI_STYLE;
    a_ptCfg->atDTLCfg[1].wHoriStartPos = SIM_DEFAULT_DTL_B_HORI_START_POS;
    a_ptCfg->atDTLCfg[1].wHoriEndPos = SIM_DEFAULT_DTL_B_HORI_END_POS;
    a_ptCfg->atDTLCfg[1].wVerticalLinePos[0] = SIM_DEFAULT_DTL_B_VERT_POS_1;
    a_ptCfg->atDTLCfg[1].wVerticalLinePos[1] = SIM_DEFAULT_DTL_B_VERT_POS_2;
    a_ptCfg->atDTLCfg[1].ucColorIndex[0] = SIM_DEFAULT_DTL_B_COLOR_IDX_1;
    a_ptCfg->atDTLCfg[1].ucColorIndex[1] = SIM_DEFAULT_DTL_B_COLOR_IDX_2;
    a_ptCfg->atDTLCfg[1].wShortLineDisableAngle = SIM_DEFAULT_DTL_B_SHORT_LINE_DISABLE_ANGLE;

    /* Warning trail line - left */
    a_ptCfg->atWLCfg[0].ucIsEnable = SIM_DEFAULT_WTL_L_ENABLE;
    a_ptCfg->atWLCfg[0].ucLineCount = SIM_DEFAULT_WTL_L_LINE_COUNT;
    a_ptCfg->atWLCfg[0].ucWarningLineColor[0] = SIM_DEFAULT_WTL_L_LINE_1_COLOR;
    a_ptCfg->atWLCfg[0].ucWarningLineStyle[0] = SIM_DEFAULT_WTL_L_LINE_1_STYLE;
	a_ptCfg->atWLCfg[0].ucPieceCount[0] = SIM_DEFAULT_WTL_L_LINE_1_PIECE;
    a_ptCfg->atWLCfg[0].wWarningLinePos[0][0] = SIM_DEFAULT_WTL_L_LINE_1_POS_1_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[0][1] = SIM_DEFAULT_WTL_L_LINE_1_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[0].wWarningLinePos[0][2] = SIM_DEFAULT_WTL_L_LINE_1_POS_2_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[0][3] = SIM_DEFAULT_WTL_L_LINE_1_POS_2_Y;  // Y
    a_ptCfg->atWLCfg[0].ucWarningLineColor[1] = SIM_DEFAULT_WTL_L_LINE_2_COLOR;
    a_ptCfg->atWLCfg[0].ucWarningLineStyle[1] = SIM_DEFAULT_WTL_L_LINE_2_STYLE;
	a_ptCfg->atWLCfg[0].ucPieceCount[1] = SIM_DEFAULT_WTL_L_LINE_2_PIECE;
    a_ptCfg->atWLCfg[0].wWarningLinePos[1][0] = SIM_DEFAULT_WTL_L_LINE_2_POS_1_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[1][1] = SIM_DEFAULT_WTL_L_LINE_2_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[0].wWarningLinePos[1][2] = SIM_DEFAULT_WTL_L_LINE_2_POS_2_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[1][3] = SIM_DEFAULT_WTL_L_LINE_2_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[0].ucWarningLineColor[2] = SIM_DEFAULT_WTL_L_LINE_3_COLOR;
    a_ptCfg->atWLCfg[0].ucWarningLineStyle[2] = SIM_DEFAULT_WTL_L_LINE_3_STYLE;
	a_ptCfg->atWLCfg[0].ucPieceCount[2] = SIM_DEFAULT_WTL_L_LINE_3_PIECE;
    a_ptCfg->atWLCfg[0].wWarningLinePos[2][0] = SIM_DEFAULT_WTL_L_LINE_3_POS_1_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[2][1] = SIM_DEFAULT_WTL_L_LINE_3_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[0].wWarningLinePos[2][2] = SIM_DEFAULT_WTL_L_LINE_3_POS_2_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[2][3] = SIM_DEFAULT_WTL_L_LINE_3_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[0].ucWarningLineColor[3] = SIM_DEFAULT_WTL_L_LINE_4_COLOR;
    a_ptCfg->atWLCfg[0].ucWarningLineStyle[3] = SIM_DEFAULT_WTL_L_LINE_4_STYLE;
	a_ptCfg->atWLCfg[0].ucPieceCount[3] = SIM_DEFAULT_WTL_L_LINE_4_PIECE;
    a_ptCfg->atWLCfg[0].wWarningLinePos[3][0] = SIM_DEFAULT_WTL_L_LINE_4_POS_1_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[3][1] = SIM_DEFAULT_WTL_L_LINE_4_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[0].wWarningLinePos[3][2] = SIM_DEFAULT_WTL_L_LINE_4_POS_2_X;  // X
    a_ptCfg->atWLCfg[0].wWarningLinePos[3][3] = SIM_DEFAULT_WTL_L_LINE_4_POS_2_Y;  // Y

    /* Warning trail line - right */
    a_ptCfg->atWLCfg[1].ucIsEnable = SIM_DEFAULT_WTL_R_ENABLE;
    a_ptCfg->atWLCfg[1].ucLineCount = SIM_DEFAULT_WTL_R_LINE_COUNT;
    a_ptCfg->atWLCfg[1].ucWarningLineColor[0] = SIM_DEFAULT_WTL_R_LINE_1_COLOR;
    a_ptCfg->atWLCfg[1].ucWarningLineStyle[0] = SIM_DEFAULT_WTL_R_LINE_1_STYLE;
	a_ptCfg->atWLCfg[1].ucPieceCount[0] = SIM_DEFAULT_WTL_R_LINE_1_PIECE;
    a_ptCfg->atWLCfg[1].wWarningLinePos[0][0] = SIM_DEFAULT_WTL_R_LINE_1_POS_1_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[0][1] = SIM_DEFAULT_WTL_R_LINE_1_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[1].wWarningLinePos[0][2] = SIM_DEFAULT_WTL_R_LINE_1_POS_2_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[0][3] = SIM_DEFAULT_WTL_R_LINE_1_POS_2_Y;  // Y
    a_ptCfg->atWLCfg[1].ucWarningLineColor[1] = SIM_DEFAULT_WTL_R_LINE_2_COLOR;
    a_ptCfg->atWLCfg[1].ucWarningLineStyle[1] = SIM_DEFAULT_WTL_R_LINE_2_STYLE;
	a_ptCfg->atWLCfg[1].ucPieceCount[1] = SIM_DEFAULT_WTL_R_LINE_2_PIECE;
    a_ptCfg->atWLCfg[1].wWarningLinePos[1][0] = SIM_DEFAULT_WTL_R_LINE_2_POS_1_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[1][1] = SIM_DEFAULT_WTL_R_LINE_2_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[1].wWarningLinePos[1][2] = SIM_DEFAULT_WTL_R_LINE_2_POS_2_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[1][3] = SIM_DEFAULT_WTL_R_LINE_2_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[1].ucWarningLineColor[2] = SIM_DEFAULT_WTL_R_LINE_3_COLOR;
    a_ptCfg->atWLCfg[1].ucWarningLineStyle[2] = SIM_DEFAULT_WTL_R_LINE_3_STYLE;
	a_ptCfg->atWLCfg[1].ucPieceCount[2] = SIM_DEFAULT_WTL_R_LINE_3_PIECE;
    a_ptCfg->atWLCfg[1].wWarningLinePos[2][0] = SIM_DEFAULT_WTL_R_LINE_3_POS_1_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[2][1] = SIM_DEFAULT_WTL_R_LINE_3_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[1].wWarningLinePos[2][2] = SIM_DEFAULT_WTL_R_LINE_3_POS_2_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[2][3] = SIM_DEFAULT_WTL_R_LINE_3_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[1].ucWarningLineColor[3] = SIM_DEFAULT_WTL_R_LINE_4_COLOR;
    a_ptCfg->atWLCfg[1].ucWarningLineStyle[3] = SIM_DEFAULT_WTL_R_LINE_4_STYLE;
	a_ptCfg->atWLCfg[1].ucPieceCount[3] = SIM_DEFAULT_WTL_R_LINE_4_PIECE;
    a_ptCfg->atWLCfg[1].wWarningLinePos[3][0] = SIM_DEFAULT_WTL_R_LINE_4_POS_1_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[3][1] = SIM_DEFAULT_WTL_R_LINE_4_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[1].wWarningLinePos[3][2] = SIM_DEFAULT_WTL_R_LINE_4_POS_2_X;  // X
    a_ptCfg->atWLCfg[1].wWarningLinePos[3][3] = SIM_DEFAULT_WTL_R_LINE_4_POS_2_Y;  // Y

    /* Warning trail line - front */
    a_ptCfg->atWLCfg[2].ucIsEnable = SIM_DEFAULT_WTL_F_ENABLE;
    a_ptCfg->atWLCfg[2].ucLineCount = SIM_DEFAULT_WTL_F_LINE_COUNT;
    a_ptCfg->atWLCfg[2].ucWarningLineColor[0] = SIM_DEFAULT_WTL_F_LINE_1_COLOR;
    a_ptCfg->atWLCfg[2].ucWarningLineStyle[0] = SIM_DEFAULT_WTL_F_LINE_1_STYLE;
	a_ptCfg->atWLCfg[2].ucPieceCount[0] = SIM_DEFAULT_WTL_F_LINE_1_PIECE;
    a_ptCfg->atWLCfg[2].wWarningLinePos[0][0] = SIM_DEFAULT_WTL_F_LINE_1_POS_1_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[0][1] = SIM_DEFAULT_WTL_F_LINE_1_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[2].wWarningLinePos[0][2] = SIM_DEFAULT_WTL_F_LINE_1_POS_2_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[0][3] = SIM_DEFAULT_WTL_F_LINE_1_POS_2_Y;  // Y
    a_ptCfg->atWLCfg[2].ucWarningLineColor[1] = SIM_DEFAULT_WTL_F_LINE_2_COLOR;
    a_ptCfg->atWLCfg[2].ucWarningLineStyle[1] = SIM_DEFAULT_WTL_F_LINE_2_STYLE;
	a_ptCfg->atWLCfg[2].ucPieceCount[1] = SIM_DEFAULT_WTL_F_LINE_2_PIECE;
    a_ptCfg->atWLCfg[2].wWarningLinePos[1][0] = SIM_DEFAULT_WTL_F_LINE_2_POS_1_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[1][1] = SIM_DEFAULT_WTL_F_LINE_2_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[2].wWarningLinePos[1][2] = SIM_DEFAULT_WTL_F_LINE_2_POS_2_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[1][3] = SIM_DEFAULT_WTL_F_LINE_2_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[2].ucWarningLineColor[2] = SIM_DEFAULT_WTL_F_LINE_3_COLOR;
    a_ptCfg->atWLCfg[2].ucWarningLineStyle[2] = SIM_DEFAULT_WTL_F_LINE_3_STYLE;
	a_ptCfg->atWLCfg[2].ucPieceCount[2] = SIM_DEFAULT_WTL_F_LINE_3_PIECE;
    a_ptCfg->atWLCfg[2].wWarningLinePos[2][0] = SIM_DEFAULT_WTL_F_LINE_3_POS_1_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[2][1] = SIM_DEFAULT_WTL_F_LINE_3_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[2].wWarningLinePos[2][2] = SIM_DEFAULT_WTL_F_LINE_3_POS_2_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[2][3] = SIM_DEFAULT_WTL_F_LINE_3_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[2].ucWarningLineColor[3] = SIM_DEFAULT_WTL_F_LINE_4_COLOR;
    a_ptCfg->atWLCfg[2].ucWarningLineStyle[3] = SIM_DEFAULT_WTL_F_LINE_4_STYLE;
	a_ptCfg->atWLCfg[2].ucPieceCount[3] = SIM_DEFAULT_WTL_F_LINE_4_PIECE;
    a_ptCfg->atWLCfg[2].wWarningLinePos[3][0] = SIM_DEFAULT_WTL_F_LINE_4_POS_1_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[3][1] = SIM_DEFAULT_WTL_F_LINE_4_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[2].wWarningLinePos[3][2] = SIM_DEFAULT_WTL_F_LINE_4_POS_2_X;  // X
    a_ptCfg->atWLCfg[2].wWarningLinePos[3][3] = SIM_DEFAULT_WTL_F_LINE_4_POS_2_Y;  // Y

    /* Warning trail line - back */
    a_ptCfg->atWLCfg[3].ucIsEnable = SIM_DEFAULT_WTL_B_ENABLE;
    a_ptCfg->atWLCfg[3].ucLineCount = SIM_DEFAULT_WTL_B_LINE_COUNT;
    a_ptCfg->atWLCfg[3].ucWarningLineColor[0] = SIM_DEFAULT_WTL_B_LINE_1_COLOR;
    a_ptCfg->atWLCfg[3].ucWarningLineStyle[0] = SIM_DEFAULT_WTL_B_LINE_1_STYLE;
	a_ptCfg->atWLCfg[3].ucPieceCount[0] = SIM_DEFAULT_WTL_B_LINE_1_PIECE;
    a_ptCfg->atWLCfg[3].wWarningLinePos[0][0] = SIM_DEFAULT_WTL_B_LINE_1_POS_1_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[0][1] = SIM_DEFAULT_WTL_B_LINE_1_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[3].wWarningLinePos[0][2] = SIM_DEFAULT_WTL_B_LINE_1_POS_2_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[0][3] = SIM_DEFAULT_WTL_B_LINE_1_POS_2_Y;  // Y
    a_ptCfg->atWLCfg[3].ucWarningLineColor[1] = SIM_DEFAULT_WTL_B_LINE_2_COLOR;
    a_ptCfg->atWLCfg[3].ucWarningLineStyle[1] = SIM_DEFAULT_WTL_B_LINE_2_STYLE;
	a_ptCfg->atWLCfg[3].ucPieceCount[1] = SIM_DEFAULT_WTL_B_LINE_2_PIECE;
    a_ptCfg->atWLCfg[3].wWarningLinePos[1][0] = SIM_DEFAULT_WTL_B_LINE_2_POS_1_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[1][1] = SIM_DEFAULT_WTL_B_LINE_2_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[3].wWarningLinePos[1][2] = SIM_DEFAULT_WTL_B_LINE_2_POS_2_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[1][3] = SIM_DEFAULT_WTL_B_LINE_2_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[3].ucWarningLineColor[2] = SIM_DEFAULT_WTL_B_LINE_3_COLOR;
    a_ptCfg->atWLCfg[3].ucWarningLineStyle[2] = SIM_DEFAULT_WTL_B_LINE_3_STYLE;
	a_ptCfg->atWLCfg[3].ucPieceCount[2] = SIM_DEFAULT_WTL_B_LINE_3_PIECE;
    a_ptCfg->atWLCfg[3].wWarningLinePos[2][0] = SIM_DEFAULT_WTL_B_LINE_3_POS_1_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[2][1] = SIM_DEFAULT_WTL_B_LINE_3_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[3].wWarningLinePos[2][2] = SIM_DEFAULT_WTL_B_LINE_3_POS_2_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[2][3] = SIM_DEFAULT_WTL_B_LINE_3_POS_2_Y;  // Y
	a_ptCfg->atWLCfg[3].ucWarningLineColor[3] = SIM_DEFAULT_WTL_B_LINE_4_COLOR;
    a_ptCfg->atWLCfg[3].ucWarningLineStyle[3] = SIM_DEFAULT_WTL_B_LINE_4_STYLE;
	a_ptCfg->atWLCfg[3].ucPieceCount[3] = SIM_DEFAULT_WTL_B_LINE_4_PIECE;
    a_ptCfg->atWLCfg[3].wWarningLinePos[3][0] = SIM_DEFAULT_WTL_B_LINE_4_POS_1_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[3][1] = SIM_DEFAULT_WTL_B_LINE_4_POS_1_Y;  // Y
    a_ptCfg->atWLCfg[3].wWarningLinePos[3][2] = SIM_DEFAULT_WTL_B_LINE_4_POS_2_X;  // X
    a_ptCfg->atWLCfg[3].wWarningLinePos[3][3] = SIM_DEFAULT_WTL_B_LINE_4_POS_2_Y;  // Y

}

////

void alTRAILLINE_CfgImportByINI(wchar_t * a_pwcConfigFilePath, alTRAILLINE_Cfg *a_ptCfg)
{
#ifdef WIN32 // FW 裡不允許讀INI檔
    wchar_t * pwcSectionName = L"TrailLineCfg";

    // 動態車幅線舵角間隔
    a_ptCfg->uwSteeringAngleInterval = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"TL_STEER_ANGLE_INTERVAL");

    // 車幅線線寬
    a_ptCfg->ucLineThickness = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"TL_LINE_WIDTH");

    // Static Trail Line - Front
    a_ptCfg->atSTLCfg[0].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_ENABLE");
    a_ptCfg->atSTLCfg[0].ucTrailStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_STYLE");
    a_ptCfg->atSTLCfg[0].ucHoriLineStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_STYLE");
    a_ptCfg->atSTLCfg[0].ucHorizonCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_COUNT");
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_POS_1");
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_POS_2");
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_POS_3");
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_POS_4");
    a_ptCfg->atSTLCfg[0].wHorizonLinePosition[4] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_HORI_POS_5");
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_COLOR_IDX_1");
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_COLOR_IDX_2");
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_COLOR_IDX_3");
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_COLOR_IDX_4");
    a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[4] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_COLOR_IDX_5");
    a_ptCfg->atSTLCfg[0].ucVertLineStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_VERT_STYLE");
    a_ptCfg->atSTLCfg[0].ucVerticalCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_VERT_COUNT");
    a_ptCfg->atSTLCfg[0].wVerticalLinePosition[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_VERT_POS_1");
    a_ptCfg->atSTLCfg[0].wVerticalLinePosition[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_VERT_POS_2");
    a_ptCfg->atSTLCfg[0].uwDashLengthHori = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_DASH_LENGTH_HORI");
    a_ptCfg->atSTLCfg[0].wDashLengthVert[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_DASH_LENGTH_VERT_1");
    a_ptCfg->atSTLCfg[0].wDashLengthVert[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_DASH_LENGTH_VERT_2");
    a_ptCfg->atSTLCfg[0].wDashLengthVert[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_DASH_LENGTH_VERT_3");
    a_ptCfg->atSTLCfg[0].wDashLengthVert[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_DASH_LENGTH_VERT_4");
    a_ptCfg->atSTLCfg[0].wDashLengthVert[4] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_F_DASH_LENGTH_VERT_5");

    // Static Trail Line - Back
    a_ptCfg->atSTLCfg[1].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_ENABLE");
    a_ptCfg->atSTLCfg[1].ucTrailStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_STYLE");
    a_ptCfg->atSTLCfg[1].ucHoriLineStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_STYLE");
    a_ptCfg->atSTLCfg[1].ucHorizonCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_COUNT");
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_POS_1");
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_POS_2");
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_POS_3");
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_POS_4");
    a_ptCfg->atSTLCfg[1].wHorizonLinePosition[4] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_HORI_POS_5");
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_COLOR_IDX_1");
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_COLOR_IDX_2");
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_COLOR_IDX_3");
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_COLOR_IDX_4");
    a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[4] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_COLOR_IDX_5");
    a_ptCfg->atSTLCfg[1].ucVertLineStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_VERT_STYLE");
    a_ptCfg->atSTLCfg[1].ucVerticalCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_VERT_COUNT");
    a_ptCfg->atSTLCfg[1].wVerticalLinePosition[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_VERT_POS_1");
    a_ptCfg->atSTLCfg[1].wVerticalLinePosition[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_VERT_POS_2");
    a_ptCfg->atSTLCfg[1].uwDashLengthHori = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_DASH_LENGTH_HORI");
    a_ptCfg->atSTLCfg[1].wDashLengthVert[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_DASH_LENGTH_VERT_1");
    a_ptCfg->atSTLCfg[1].wDashLengthVert[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_DASH_LENGTH_VERT_2");
    a_ptCfg->atSTLCfg[1].wDashLengthVert[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_DASH_LENGTH_VERT_3");
    a_ptCfg->atSTLCfg[1].wDashLengthVert[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_DASH_LENGTH_VERT_4");
    a_ptCfg->atSTLCfg[1].wDashLengthVert[4] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"STL_B_DASH_LENGTH_VERT_5");

    // Dynamic Trail Line - Front   
    a_ptCfg->atDTLCfg[0].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_ENABLE");
    a_ptCfg->atDTLCfg[0].ucTrailStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_STYLE");
    a_ptCfg->atDTLCfg[0].ucLineStyle[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_VERT_STYLE");
    a_ptCfg->atDTLCfg[0].ucLineStyle[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_HORI_STYLE");
    a_ptCfg->atDTLCfg[0].wHoriStartPos = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_HORI_START_POS");
    a_ptCfg->atDTLCfg[0].wHoriEndPos = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_HORI_END_POS");
    a_ptCfg->atDTLCfg[0].wVerticalLinePos[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_VERT_POS_1");
    a_ptCfg->atDTLCfg[0].wVerticalLinePos[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_VERT_POS_2");
    a_ptCfg->atDTLCfg[0].ucColorIndex[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_COLOR_IDX_1");
    a_ptCfg->atDTLCfg[0].ucColorIndex[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_COLOR_IDX_2");
    a_ptCfg->atDTLCfg[0].wShortLineDisableAngle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_F_SHORT_LINE_DISABLE_ANGLE");

    // Dynamic Trail Line - Back        
    a_ptCfg->atDTLCfg[1].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_ENABLE");
    a_ptCfg->atDTLCfg[1].ucTrailStyle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_STYLE");
    a_ptCfg->atDTLCfg[1].ucLineStyle[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_VERT_STYLE");
    a_ptCfg->atDTLCfg[1].ucLineStyle[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_HORI_STYLE");
    a_ptCfg->atDTLCfg[1].wHoriStartPos = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_HORI_START_POS");
    a_ptCfg->atDTLCfg[1].wHoriEndPos = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_HORI_END_POS");
    a_ptCfg->atDTLCfg[1].wVerticalLinePos[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_VERT_POS_1");
    a_ptCfg->atDTLCfg[1].wVerticalLinePos[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_VERT_POS_2");
    a_ptCfg->atDTLCfg[1].ucColorIndex[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_COLOR_IDX_1");
    a_ptCfg->atDTLCfg[1].ucColorIndex[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_COLOR_IDX_2");
    a_ptCfg->atDTLCfg[1].wShortLineDisableAngle = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"DTL_B_SHORT_LINE_DISABLE_ANGLE");

    // Warning Line - Left
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_ENABLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucLineCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_COUNT");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineColor[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineStyle[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucPieceCount[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[0][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[0][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_1_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineColor[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineStyle[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucPieceCount[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[1][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[1][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_2_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineColor[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineStyle[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucPieceCount[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[2][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[2][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_3_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineColor[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucWarningLineStyle[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].ucPieceCount[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[3][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_LEFT].wWarningLinePos[3][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_L_LINE_4_POS_2_Y");

    // Warning Line - Right
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_ENABLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucLineCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_COUNT");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineColor[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineStyle[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucPieceCount[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[0][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[0][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_1_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineColor[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineStyle[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucPieceCount[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[1][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[1][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_2_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineColor[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineStyle[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucPieceCount[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[2][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[2][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_3_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineColor[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucWarningLineStyle[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].ucPieceCount[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[3][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_RIGHT].wWarningLinePos[3][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_R_LINE_4_POS_2_Y");

    // Warning Line - Front
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_ENABLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucLineCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_COUNT");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineColor[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineStyle[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucPieceCount[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[0][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[0][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_1_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineColor[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineStyle[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucPieceCount[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[1][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[1][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_2_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineColor[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineStyle[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucPieceCount[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[2][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[2][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_3_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineColor[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucWarningLineStyle[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].ucPieceCount[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[3][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_FRONT].wWarningLinePos[3][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_F_LINE_4_POS_2_Y");

    // Warning Line - Back
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucIsEnable = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_ENABLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucLineCount = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_COUNT");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineColor[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineStyle[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucPieceCount[0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[0][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[0][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[0][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[0][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_1_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineColor[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineStyle[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucPieceCount[1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[1][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[1][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[1][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[1][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_2_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineColor[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineStyle[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucPieceCount[2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[2][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[2][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[2][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[2][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_3_POS_2_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineColor[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_COLOR");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucWarningLineStyle[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_STYLE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].ucPieceCount[3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_PIECE");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[3][0] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_POS_1_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[3][1] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_POS_1_Y");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[3][2] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_POS_2_X");
    a_ptCfg->atWLCfg[alTRAILLINE_STL_BACK ].wWarningLinePos[3][3] = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"WTL_B_LINE_4_POS_2_Y");
#endif
}

UINT32 alTRAILLINE_CfgExportHex(
    UINT32 a_ulSectionID,
    alTRAILLINE_Cfg *a_ptCfg,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0, lCnt = 0;

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    ulItemID = 0x0000;

    // uwSteeringAngleInterval
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptCfg->uwSteeringAngleInterval, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // ucLineThickness
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->ucLineThickness, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // atSTLCfg
    for (lCAMId = 0; lCAMId < 2; lCAMId++)
    {
        // atSTLCfg[lCAMId].ucIsEnable
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucIsEnable, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].ucTrailStyle
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucTrailStyle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].ucHoriLineStyle
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucHoriLineStyle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].ucHorizonCount
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucHorizonCount, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].wHorizonLinePosition
        for (lCnt = 0; lCnt < 5; lCnt++)
        {
            
            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atSTLCfg[lCAMId].wHorizonLinePosition[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        // atSTLCfg[lCAMId].ucHoriLineColorIndex
        for (lCnt = 0; lCnt < 5; lCnt++)
        {

            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucHoriLineColorIndex[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        // atSTLCfg[lCAMId].ucVertLineStyle
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucVertLineStyle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].ucVerticalCount
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atSTLCfg[lCAMId].ucVerticalCount, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].wVerticalLinePosition[0]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atSTLCfg[lCAMId].wVerticalLinePosition[0], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].wVerticalLinePosition[1]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atSTLCfg[lCAMId].wVerticalLinePosition[1], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].uwDashLengthHori
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptCfg->atSTLCfg[lCAMId].uwDashLengthHori, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atSTLCfg[lCAMId].wDashLengthVert
        for (lCnt = 0; lCnt < 5; lCnt++)
        {
            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atSTLCfg[lCAMId].wDashLengthVert[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }
    }

    // atDTLCfg
    for (lCAMId = 0; lCAMId < 2; lCAMId++)
    {
        // atDTLCfg[lCAMId].ucIsEnable
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucIsEnable, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].ucTrailStyle
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucTrailStyle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].ucLineStyle[0]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucLineStyle[0], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].ucLineStyle[1]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucLineStyle[1], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].wHoriStartPos
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atDTLCfg[lCAMId].wHoriStartPos, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].wHoriEndPos
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atDTLCfg[lCAMId].wHoriEndPos, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].ucType
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucType, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].wVerticalLinePos[0]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atDTLCfg[lCAMId].wVerticalLinePos[0], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].wVerticalLinePos[1]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atDTLCfg[lCAMId].wVerticalLinePos[1], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].ucColorIndex[0]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucColorIndex[0], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].ucColorIndex[1]
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atDTLCfg[lCAMId].ucColorIndex[1], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atDTLCfg[lCAMId].wShortLineDisableAngle
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atDTLCfg[lCAMId].wShortLineDisableAngle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // atWLCfg
    for (lCAMId = 0; lCAMId < 4; lCAMId++)
    {
        // atWLCfg[lCAMId].ucIsEnable
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atWLCfg[lCAMId].ucIsEnable, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atWLCfg[lCAMId].ucLineCount
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atWLCfg[lCAMId].ucLineCount, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // atWLCfg[lCAMId].ucPieceCount
        for (lCnt = 0; lCnt < 4; lCnt++)
        {
            
            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atWLCfg[lCAMId].ucPieceCount[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        // atWLCfg[lCAMId].ucWarningLineColor
        for (lCnt = 0; lCnt < 4; lCnt++)
        {
            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atWLCfg[lCAMId].ucWarningLineColor[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        // atWLCfg[lCAMId].wWarningLinePos
        for (lCnt = 0; lCnt < 4; lCnt++)
        {
            for (lIndex = 0; lIndex < 4; lIndex++)
            {
                ulDataID = (a_ulSectionID << 16) + ulItemID;
                ulDataBufLen = 0;
                ulDataBufLen += alHEXDATA_PackINT16(ulDataID, a_ptCfg->atWLCfg[lCAMId].wWarningLinePos[lCnt][lIndex], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
                ulSectionBufLen += ulDataBufLen;

                ulItemID++;
            }
        }

        // atWLCfg[lCAMId].ucWarningLineStyle
        for (lCnt = 0; lCnt < 4; lCnt++)
        {
            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->atWLCfg[lCAMId].ucWarningLineStyle[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }
    }

    return ulSectionBufLen;
}

void alTRAILLINE_CfgImportHex(
    UINT32 a_ulDataID,
    UINT32 a_ulDataLength, UINT8 * a_pucBuffer,
    alTRAILLINE_Cfg *a_ptCfg
    )
{
    UINT32 ulSubDataID = 0;

    ulSubDataID = a_ulDataID & 0xFFFF;

    switch (ulSubDataID)
    {
    case 0x0000:    // ucFunctionEnabled
    {
        a_ptCfg->uwSteeringAngleInterval = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0001:    // ucLineThickness
    {
        a_ptCfg->ucLineThickness = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0002:    // atSTLCfg[0].ucIsEnable
    {
        a_ptCfg->atSTLCfg[0].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0003:    // atSTLCfg[0].ucTrailStyle
    {
        a_ptCfg->atSTLCfg[0].ucTrailStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0004:    // atSTLCfg[0].ucHoriLineStyle
    {
        a_ptCfg->atSTLCfg[0].ucHoriLineStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0005:    // atSTLCfg[0].ucHorizonCount
    {
        a_ptCfg->atSTLCfg[0].ucHorizonCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0006:    // atSTLCfg[0].wHorizonLinePosition[0]
    {
        a_ptCfg->atSTLCfg[0].wHorizonLinePosition[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0007:    // atSTLCfg[0].wHorizonLinePosition[1]
    {
        a_ptCfg->atSTLCfg[0].wHorizonLinePosition[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0008:    // atSTLCfg[0].wHorizonLinePosition[2]
    {
        a_ptCfg->atSTLCfg[0].wHorizonLinePosition[2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0009:    // atSTLCfg[0].wHorizonLinePosition[3]
    {
        a_ptCfg->atSTLCfg[0].wHorizonLinePosition[3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000A:    // atSTLCfg[0].wHorizonLinePosition[4]
    {
        a_ptCfg->atSTLCfg[0].wHorizonLinePosition[4] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000B:    // atSTLCfg[0].ucHoriLineColorIndex[0]
    {
        a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000C:    // atSTLCfg[0].ucHoriLineColorIndex[1]
    {
        a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000D:    // atSTLCfg[0].ucHoriLineColorIndex[2]
    {
        a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000E:    // atSTLCfg[0].ucHoriLineColorIndex[3]
    {
        a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000F:    // atSTLCfg[0].ucHoriLineColorIndex[4]
    {
        a_ptCfg->atSTLCfg[0].ucHoriLineColorIndex[4] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0010:    // atSTLCfg[0].ucVertLineStyle
    {
        a_ptCfg->atSTLCfg[0].ucVertLineStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0011:    // atSTLCfg[0].ucVerticalCount
    {
        a_ptCfg->atSTLCfg[0].ucVerticalCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0012:    // atSTLCfg[0].wVerticalLinePosition[0]
    {
        a_ptCfg->atSTLCfg[0].wVerticalLinePosition[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0013:    // atSTLCfg[0].wVerticalLinePosition[1]
    {
        a_ptCfg->atSTLCfg[0].wVerticalLinePosition[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0014:    // atSTLCfg[0].uwDashLengthHori
    {
        a_ptCfg->atSTLCfg[0].uwDashLengthHori = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0015:    // atSTLCfg[0].wDashLengthVert[0]
    {
        a_ptCfg->atSTLCfg[0].wDashLengthVert[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0016:    // atSTLCfg[0].wDashLengthVert[1]
    {
        a_ptCfg->atSTLCfg[0].wDashLengthVert[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0017:    // atSTLCfg[0].wDashLengthVert[2]
    {
        a_ptCfg->atSTLCfg[0].wDashLengthVert[2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0018:    // atSTLCfg[0].wDashLengthVert[3]
    {
        a_ptCfg->atSTLCfg[0].wDashLengthVert[3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0019:    // atSTLCfg[0].wDashLengthVert[4]
    {
        a_ptCfg->atSTLCfg[0].wDashLengthVert[4] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001A:    // atSTLCfg[1].ucIsEnable
    {
        a_ptCfg->atSTLCfg[1].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001B:    // atSTLCfg[1].ucTrailStyle
    {
        a_ptCfg->atSTLCfg[1].ucTrailStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001C:    // atSTLCfg[1].ucHoriLineStyle
    {
        a_ptCfg->atSTLCfg[1].ucHoriLineStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001D:    // atSTLCfg[1].ucHorizonCount
    {
        a_ptCfg->atSTLCfg[1].ucHorizonCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001E:    // atSTLCfg[1].wHorizonLinePosition[0]
    {
        a_ptCfg->atSTLCfg[1].wHorizonLinePosition[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001F:    // atSTLCfg[1].wHorizonLinePosition[1]
    {
        a_ptCfg->atSTLCfg[1].wHorizonLinePosition[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0020:    // atSTLCfg[1].wHorizonLinePosition[2]
    {
        a_ptCfg->atSTLCfg[1].wHorizonLinePosition[2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0021:    // atSTLCfg[1].wHorizonLinePosition[3]
    {
        a_ptCfg->atSTLCfg[1].wHorizonLinePosition[3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0022:    // atSTLCfg[1].wHorizonLinePosition[4]
    {
        a_ptCfg->atSTLCfg[1].wHorizonLinePosition[4] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0023:    // atSTLCfg[1].ucHoriLineColorIndex[0]
    {
        a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0024:    // atSTLCfg[1].ucHoriLineColorIndex[1]
    {
        a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0025:    // atSTLCfg[1].ucHoriLineColorIndex[2]
    {
        a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0026:    // atSTLCfg[1].ucHoriLineColorIndex[3]
    {
        a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0027:    // atSTLCfg[1].ucHoriLineColorIndex[4]
    {
        a_ptCfg->atSTLCfg[1].ucHoriLineColorIndex[4] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0028:    // atSTLCfg[1].ucVertLineStyle
    {
        a_ptCfg->atSTLCfg[1].ucVertLineStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0029:    // atSTLCfg[1].ucVerticalCount
    {
        a_ptCfg->atSTLCfg[1].ucVerticalCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002A:    // atSTLCfg[1].wVerticalLinePosition[0]
    {
        a_ptCfg->atSTLCfg[1].wVerticalLinePosition[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002B:    // atSTLCfg[1].wVerticalLinePosition[1]
    {
        a_ptCfg->atSTLCfg[1].wVerticalLinePosition[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002C:    // atSTLCfg[1].uwDashLengthHori
    {
        a_ptCfg->atSTLCfg[1].uwDashLengthHori = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002D:    // atSTLCfg[1].wDashLengthVert[0]
    {
        a_ptCfg->atSTLCfg[1].wDashLengthVert[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002E:    // atSTLCfg[1].wDashLengthVert[1]
    {
        a_ptCfg->atSTLCfg[1].wDashLengthVert[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002F:    // atSTLCfg[1].wDashLengthVert[2]
    {
        a_ptCfg->atSTLCfg[1].wDashLengthVert[2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0030:    // atSTLCfg[1].wDashLengthVert[3]
    {
        a_ptCfg->atSTLCfg[1].wDashLengthVert[3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0031:    // atSTLCfg[1].wDashLengthVert[4]
    {
        a_ptCfg->atSTLCfg[1].wDashLengthVert[4] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0032:    // atDTLCfg[0].ucIsEnable
    {
        a_ptCfg->atDTLCfg[0].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0033:    // atDTLCfg[0].ucTrailStyle
    {
        a_ptCfg->atDTLCfg[0].ucTrailStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0034:    // atDTLCfg[0].ucLineStyle[0]
    {
        a_ptCfg->atDTLCfg[0].ucLineStyle[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0035:    // atDTLCfg[0].ucLineStyle[1]
    {
        a_ptCfg->atDTLCfg[0].ucLineStyle[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0036:    // atDTLCfg[0].wHoriStartPos
    {
        a_ptCfg->atDTLCfg[0].wHoriStartPos = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0037:    // atDTLCfg[0].wHoriEndPos
    {
        a_ptCfg->atDTLCfg[0].wHoriEndPos = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0038:    // atDTLCfg[0].ucType
    {
        a_ptCfg->atDTLCfg[0].ucType = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0039:    // atDTLCfg[0].wVerticalLinePos[0]
    {
        a_ptCfg->atDTLCfg[0].wVerticalLinePos[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003A:    // atDTLCfg[0].wVerticalLinePos[1]
    {
        a_ptCfg->atDTLCfg[0].wVerticalLinePos[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003B:    // atDTLCfg[0].ucColorIndex[0]
    {
        a_ptCfg->atDTLCfg[0].ucColorIndex[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003C:    // atDTLCfg[0].ucColorIndex[1]
    {
        a_ptCfg->atDTLCfg[0].ucColorIndex[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003D:    // atDTLCfg[0].wShortLineDisableAngle
    {
        a_ptCfg->atDTLCfg[0].wShortLineDisableAngle = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003E:    // atDTLCfg[1].ucIsEnable
    {
        a_ptCfg->atDTLCfg[1].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x003F:    // atDTLCfg[1].ucTrailStyle
    {
        a_ptCfg->atDTLCfg[1].ucTrailStyle = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0040:    // atDTLCfg[1].ucLineStyle[0]
    {
        a_ptCfg->atDTLCfg[1].ucLineStyle[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0041:    // atDTLCfg[1].ucLineStyle[1]
    {
        a_ptCfg->atDTLCfg[1].ucLineStyle[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0042:    // atDTLCfg[1].wHoriStartPos
    {
        a_ptCfg->atDTLCfg[1].wHoriStartPos = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0043:    // atDTLCfg[1].wHoriEndPos
    {
        a_ptCfg->atDTLCfg[1].wHoriEndPos = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0044:    // atDTLCfg[1].ucType
    {
        a_ptCfg->atDTLCfg[1].ucType = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0045:    // atDTLCfg[1].wVerticalLinePos[0]
    {
        a_ptCfg->atDTLCfg[1].wVerticalLinePos[0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0046:    // atDTLCfg[1].wVerticalLinePos[1]
    {
        a_ptCfg->atDTLCfg[1].wVerticalLinePos[1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0047:    // atDTLCfg[1].ucColorIndex[0]
    {
        a_ptCfg->atDTLCfg[1].ucColorIndex[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0048:    // atDTLCfg[1].ucColorIndex[1]
    {
        a_ptCfg->atDTLCfg[1].ucColorIndex[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0049:    // atDTLCfg[1].wShortLineDisableAngle
    {
        a_ptCfg->atDTLCfg[1].wShortLineDisableAngle = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x004A:    // atWLCfg[0].ucIsEnable
    {
        a_ptCfg->atWLCfg[0].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004B:    // atWLCfg[0].ucLineCount
    {
        a_ptCfg->atWLCfg[0].ucLineCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004C:    // atWLCfg[0].ucPieceCount[0]
    {
        a_ptCfg->atWLCfg[0].ucPieceCount[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004D:    // atWLCfg[0].ucPieceCount[1]
    {
        a_ptCfg->atWLCfg[0].ucPieceCount[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004E:    // atWLCfg[0].ucPieceCount[2]
    {
        a_ptCfg->atWLCfg[0].ucPieceCount[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004F:    // atWLCfg[0].ucPieceCount[3]
    {
        a_ptCfg->atWLCfg[0].ucPieceCount[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0050:    // atWLCfg[0].ucWarningLineColor[0]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineColor[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0051:    // atWLCfg[0].ucWarningLineColor[1]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineColor[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0052:    // atWLCfg[0].ucWarningLineColor[2]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineColor[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0053:    // atWLCfg[0].ucWarningLineColor[3]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineColor[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0054:    // atWLCfg[0].wWarningLinePos[0][0]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[0][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0055:    // atWLCfg[0].wWarningLinePos[0][1]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[0][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0056:    // atWLCfg[0].wWarningLinePos[0][2]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[0][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0057:    // atWLCfg[0].wWarningLinePos[0][3]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[0][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0058:    // atWLCfg[0].wWarningLinePos[1][0]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[1][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0059:    // atWLCfg[0].wWarningLinePos[1][1]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[1][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005A:    // atWLCfg[0].wWarningLinePos[1][2]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[1][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005B:    // atWLCfg[0].wWarningLinePos[1][3]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[1][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x005C:    // atWLCfg[0].wWarningLinePos[2][0]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[2][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005D:    // atWLCfg[0].wWarningLinePos[2][1]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[2][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005E:    // atWLCfg[0].wWarningLinePos[2][2]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[2][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005F:    // atWLCfg[0].wWarningLinePos[2][3]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[2][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0060:    // atWLCfg[0].wWarningLinePos[3][0]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[3][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0061:    // atWLCfg[0].wWarningLinePos[3][1]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[3][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0062:    // atWLCfg[0].wWarningLinePos[3][2]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[3][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0063:    // atWLCfg[0].wWarningLinePos[3][3]
    {
        a_ptCfg->atWLCfg[0].wWarningLinePos[3][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0064:    // atWLCfg[0].ucWarningLineStyle[0]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineStyle[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0065:    // atWLCfg[0].ucWarningLineStyle[1]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineStyle[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0066:    // atWLCfg[0].ucWarningLineStyle[2]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineStyle[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0067:    // atWLCfg[0].ucWarningLineStyle[3]
    {
        a_ptCfg->atWLCfg[0].ucWarningLineStyle[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0068:    // atWLCfg[1].ucIsEnable
    {
        a_ptCfg->atWLCfg[1].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0069:    // atWLCfg[1].ucLineCount
    {
        a_ptCfg->atWLCfg[1].ucLineCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006A:    // atWLCfg[1].ucPieceCount[0]
    {
        a_ptCfg->atWLCfg[1].ucPieceCount[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006B:    // atWLCfg[1].ucPieceCount[1]
    {
        a_ptCfg->atWLCfg[1].ucPieceCount[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006C:    // atWLCfg[1].ucPieceCount[2]
    {
        a_ptCfg->atWLCfg[1].ucPieceCount[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006D:    // atWLCfg[1].ucPieceCount[3]
    {
        a_ptCfg->atWLCfg[1].ucPieceCount[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006E:    // atWLCfg[1].ucWarningLineColor[0]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineColor[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006F:    // atWLCfg[1].ucWarningLineColor[1]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineColor[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0070:    // atWLCfg[1].ucWarningLineColor[2]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineColor[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0071:    // atWLCfg[1].ucWarningLineColor[3]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineColor[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0072:    // atWLCfg[1].wWarningLinePos[0][0]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[0][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0073:    // atWLCfg[1].wWarningLinePos[0][1]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[0][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0074:    // atWLCfg[1].wWarningLinePos[0][2]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[0][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0075:    // atWLCfg[1].wWarningLinePos[0][3]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[0][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0076:    // atWLCfg[1].wWarningLinePos[1][0]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[1][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0077:    // atWLCfg[1].wWarningLinePos[1][1]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[1][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0078:    // atWLCfg[1].wWarningLinePos[1][2]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[1][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0079:    // atWLCfg[1].wWarningLinePos[1][3]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[1][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x007A:    // atWLCfg[1].wWarningLinePos[2][0]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[2][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007B:    // atWLCfg[1].wWarningLinePos[2][1]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[2][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007C:    // atWLCfg[1].wWarningLinePos[2][2]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[2][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007D:    // atWLCfg[1].wWarningLinePos[2][3]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[2][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x007E:    // atWLCfg[1].wWarningLinePos[3][0]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[3][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007F:    // atWLCfg[1].wWarningLinePos[3][1]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[3][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0080:    // atWLCfg[1].wWarningLinePos[3][2]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[3][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0081:    // atWLCfg[1].wWarningLinePos[3][3]
    {
        a_ptCfg->atWLCfg[1].wWarningLinePos[3][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0082:    // atWLCfg[1].ucWarningLineStyle[0]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineStyle[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0083:    // atWLCfg[1].ucWarningLineStyle[1]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineStyle[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0084:    // atWLCfg[1].ucWarningLineStyle[2]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineStyle[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0085:    // atWLCfg[1].ucWarningLineStyle[3]
    {
        a_ptCfg->atWLCfg[1].ucWarningLineStyle[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0086:    // atWLCfg[2].ucIsEnable
    {
        a_ptCfg->atWLCfg[2].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0087:    // atWLCfg[2].ucLineCount
    {
        a_ptCfg->atWLCfg[2].ucLineCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0088:    // atWLCfg[2].ucPieceCount[0]
    {
        a_ptCfg->atWLCfg[2].ucPieceCount[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0089:    // atWLCfg[2].ucPieceCount[1]
    {
        a_ptCfg->atWLCfg[2].ucPieceCount[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008A:    // atWLCfg[2].ucPieceCount[2]
    {
        a_ptCfg->atWLCfg[2].ucPieceCount[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008B:    // atWLCfg[2].ucPieceCount[3]
    {
        a_ptCfg->atWLCfg[2].ucPieceCount[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008C:    // atWLCfg[2].ucWarningLineColor[0]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineColor[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008D:    // atWLCfg[2].ucWarningLineColor[1]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineColor[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008E:    // atWLCfg[2].ucWarningLineColor[2]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineColor[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008F:    // atWLCfg[2].ucWarningLineColor[3]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineColor[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0090:    // atWLCfg[2].wWarningLinePos[0][0]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[0][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0091:    // atWLCfg[2].wWarningLinePos[0][1]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[0][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0092:    // atWLCfg[2].wWarningLinePos[0][2]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[0][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0093:    // atWLCfg[2].wWarningLinePos[0][3]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[0][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0094:    // atWLCfg[2].wWarningLinePos[1][0]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[1][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0095:    // atWLCfg[2].wWarningLinePos[1][1]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[1][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0096:    // atWLCfg[2].wWarningLinePos[1][2]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[1][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0097:    // atWLCfg[2].wWarningLinePos[1][3]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[1][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0098:    // atWLCfg[2].wWarningLinePos[2][0]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[2][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0099:    // atWLCfg[2].wWarningLinePos[2][1]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[2][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009A:    // atWLCfg[2].wWarningLinePos[2][2]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[2][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009B:    // atWLCfg[2].wWarningLinePos[2][3]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[2][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x009C:    // atWLCfg[2].wWarningLinePos[3][0]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[3][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009D:    // atWLCfg[2].wWarningLinePos[3][1]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[3][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009E:    // atWLCfg[2].wWarningLinePos[3][2]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[3][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009F:    // atWLCfg[2].wWarningLinePos[3][3]
    {
        a_ptCfg->atWLCfg[2].wWarningLinePos[3][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A0:    // atWLCfg[2].ucWarningLineStyle[0]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineStyle[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A1:    // atWLCfg[2].ucWarningLineStyle[1]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineStyle[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A2:    // atWLCfg[2].ucWarningLineStyle[2]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineStyle[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A3:    // atWLCfg[2].ucWarningLineStyle[3]
    {
        a_ptCfg->atWLCfg[2].ucWarningLineStyle[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00A4:    // atWLCfg[3].ucIsEnable
    {
        a_ptCfg->atWLCfg[3].ucIsEnable = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A5:    // atWLCfg[3].ucLineCount
    {
        a_ptCfg->atWLCfg[3].ucLineCount = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A6:    // atWLCfg[3].ucPieceCount[0]
    {
        a_ptCfg->atWLCfg[3].ucPieceCount[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A7:    // atWLCfg[3].ucPieceCount[1]
    {
        a_ptCfg->atWLCfg[3].ucPieceCount[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A8:    // atWLCfg[3].ucPieceCount[2]
    {
        a_ptCfg->atWLCfg[3].ucPieceCount[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A9:    // atWLCfg[3].ucPieceCount[3]
    {
        a_ptCfg->atWLCfg[3].ucPieceCount[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AA:    // atWLCfg[3].ucWarningLineColor[0]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineColor[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AB:    // atWLCfg[3].ucWarningLineColor[1]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineColor[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AC:    // atWLCfg[3].ucWarningLineColor[2]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineColor[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AD:    // atWLCfg[3].ucWarningLineColor[3]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineColor[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AE:    // atWLCfg[3].wWarningLinePos[0][0]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[0][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AF:    // atWLCfg[3].wWarningLinePos[0][1]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[0][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B0:    // atWLCfg[3].wWarningLinePos[0][2]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[0][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B1:    // atWLCfg[3].wWarningLinePos[0][3]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[0][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00B2:    // atWLCfg[3].wWarningLinePos[1][0]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[1][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B3:    // atWLCfg[3].wWarningLinePos[1][1]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[1][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B4:    // atWLCfg[3].wWarningLinePos[1][2]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[1][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B5:    // atWLCfg[3].wWarningLinePos[1][3]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[1][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00B6:    // atWLCfg[3].wWarningLinePos[2][0]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[2][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B7:    // atWLCfg[3].wWarningLinePos[2][1]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[2][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B8:    // atWLCfg[3].wWarningLinePos[2][2]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[2][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B9:    // atWLCfg[3].wWarningLinePos[2][3]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[2][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00BA:    // atWLCfg[3].wWarningLinePos[3][0]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[3][0] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BB:    // atWLCfg[3].wWarningLinePos[3][1]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[3][1] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BC:    // atWLCfg[3].wWarningLinePos[3][2]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[3][2] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BD:    // atWLCfg[3].wWarningLinePos[3][3]
    {
        a_ptCfg->atWLCfg[3].wWarningLinePos[3][3] = alHEXDATA_UnpackINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BE:    // atWLCfg[3].ucWarningLineStyle[0]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineStyle[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BF:    // atWLCfg[3].ucWarningLineStyle[1]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineStyle[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C0:    // atWLCfg[3].ucWarningLineStyle[2]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineStyle[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C1:    // atWLCfg[3].ucWarningLineStyle[3]
    {
        a_ptCfg->atWLCfg[3].ucWarningLineStyle[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    
    default:    // default
    {
        DEBUG_Printf("Invalid Data ID: 0x%X\n - alTRAILLINE_CfgImport\n", a_ulDataID);
    }
    break;
    }
}

