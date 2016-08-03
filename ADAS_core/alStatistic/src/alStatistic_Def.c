
#include "alStatistic_Def.h"

#include <assert.h>

/** \brief Define the function of mean calculation is enabled or not (left view). */
#define BIRDVIEWMEANCAL_FUNCTIONENABLED_LEFT   1
/** \brief Define the function of mean calculation is enabled or not (right view). */
#define BIRDVIEWMEANCAL_FUNCTIONENABLED_RIGHT  1
/** \brief Define the function of mean calculation is enabled or not (front view). */
#define BIRDVIEWMEANCAL_FUNCTIONENABLED_FRONT  1
/** \brief Define the function of mean calculation is enabled or not (back view). */
#define BIRDVIEWMEANCAL_FUNCTIONENABLED_BACK   1

#define BIRDVIEWMEANCAL_ROICNT_LEFT   10
#define BIRDVIEWMEANCAL_ROICNT_RIGHT  10
#define BIRDVIEWMEANCAL_ROICNT_FRONT  10
#define BIRDVIEWMEANCAL_ROICNT_BACK   10

#define SINGLEVIEWNOISECAL_ROICNT_1  2
#define SINGLEVIEWNOISECAL_ROICNT_2   2
#define SINGLEVIEWNOISECAL_ROICNT_3   2
#define SINGLEVIEWNOISECAL_ROICNT_4   2
#define SINGLEVIEWNOISECAL_ROICNT_5  2
#define SINGLEVIEWNOISECAL_ROICNT_6   2
#define SINGLEVIEWNOISECAL_ROICNT_7   2

#define BIRDVIEWMEANCAL_STARTPOINTS_1_X_LEFT    32
#define BIRDVIEWMEANCAL_STARTPOINTS_1_Y_LEFT   111 
#define BIRDVIEWMEANCAL_STARTPOINTS_2_X_LEFT    32
#define BIRDVIEWMEANCAL_STARTPOINTS_2_Y_LEFT   176
#define BIRDVIEWMEANCAL_STARTPOINTS_3_X_LEFT    32
#define BIRDVIEWMEANCAL_STARTPOINTS_3_Y_LEFT   241
#define BIRDVIEWMEANCAL_STARTPOINTS_4_X_LEFT    32
#define BIRDVIEWMEANCAL_STARTPOINTS_4_Y_LEFT   306
#define BIRDVIEWMEANCAL_STARTPOINTS_5_X_LEFT    62
#define BIRDVIEWMEANCAL_STARTPOINTS_5_Y_LEFT   111 
#define BIRDVIEWMEANCAL_STARTPOINTS_6_X_LEFT    62
#define BIRDVIEWMEANCAL_STARTPOINTS_6_Y_LEFT   176
#define BIRDVIEWMEANCAL_STARTPOINTS_7_X_LEFT    62
#define BIRDVIEWMEANCAL_STARTPOINTS_7_Y_LEFT   241
#define BIRDVIEWMEANCAL_STARTPOINTS_8_X_LEFT    62
#define BIRDVIEWMEANCAL_STARTPOINTS_8_Y_LEFT   306
#define BIRDVIEWMEANCAL_STARTPOINTS_9_X_LEFT    94
#define BIRDVIEWMEANCAL_STARTPOINTS_9_Y_LEFT   111
#define BIRDVIEWMEANCAL_STARTPOINTS_10_X_LEFT   94
#define BIRDVIEWMEANCAL_STARTPOINTS_10_Y_LEFT  232

#define BIRDVIEWMEANCAL_STARTPOINTS_1_X_RIGHT   280
#define BIRDVIEWMEANCAL_STARTPOINTS_1_Y_RIGHT   111 
#define BIRDVIEWMEANCAL_STARTPOINTS_2_X_RIGHT   280
#define BIRDVIEWMEANCAL_STARTPOINTS_2_Y_RIGHT   176
#define BIRDVIEWMEANCAL_STARTPOINTS_3_X_RIGHT   280
#define BIRDVIEWMEANCAL_STARTPOINTS_3_Y_RIGHT   241
#define BIRDVIEWMEANCAL_STARTPOINTS_4_X_RIGHT   280
#define BIRDVIEWMEANCAL_STARTPOINTS_4_Y_RIGHT   306
#define BIRDVIEWMEANCAL_STARTPOINTS_5_X_RIGHT   250
#define BIRDVIEWMEANCAL_STARTPOINTS_5_Y_RIGHT   111 
#define BIRDVIEWMEANCAL_STARTPOINTS_6_X_RIGHT   250
#define BIRDVIEWMEANCAL_STARTPOINTS_6_Y_RIGHT   176
#define BIRDVIEWMEANCAL_STARTPOINTS_7_X_RIGHT   250
#define BIRDVIEWMEANCAL_STARTPOINTS_7_Y_RIGHT   241
#define BIRDVIEWMEANCAL_STARTPOINTS_8_X_RIGHT   250
#define BIRDVIEWMEANCAL_STARTPOINTS_8_Y_RIGHT   306
#define BIRDVIEWMEANCAL_STARTPOINTS_9_X_RIGHT   218
#define BIRDVIEWMEANCAL_STARTPOINTS_9_Y_RIGHT   111
#define BIRDVIEWMEANCAL_STARTPOINTS_10_X_RIGHT  218
#define BIRDVIEWMEANCAL_STARTPOINTS_10_Y_RIGHT  232

#define BIRDVIEWMEANCAL_STARTPOINTS_1_X_FRONT   33
#define BIRDVIEWMEANCAL_STARTPOINTS_1_Y_FRONT    8
#define BIRDVIEWMEANCAL_STARTPOINTS_2_X_FRONT   103
#define BIRDVIEWMEANCAL_STARTPOINTS_2_Y_FRONT    8 
#define BIRDVIEWMEANCAL_STARTPOINTS_3_X_FRONT  171
#define BIRDVIEWMEANCAL_STARTPOINTS_3_Y_FRONT    8
#define BIRDVIEWMEANCAL_STARTPOINTS_4_X_FRONT  240
#define BIRDVIEWMEANCAL_STARTPOINTS_4_Y_FRONT    8
#define BIRDVIEWMEANCAL_STARTPOINTS_5_X_FRONT   33
#define BIRDVIEWMEANCAL_STARTPOINTS_5_Y_FRONT   40
#define BIRDVIEWMEANCAL_STARTPOINTS_6_X_FRONT   103
#define BIRDVIEWMEANCAL_STARTPOINTS_6_Y_FRONT   40
#define BIRDVIEWMEANCAL_STARTPOINTS_7_X_FRONT  171
#define BIRDVIEWMEANCAL_STARTPOINTS_7_Y_FRONT   40
#define BIRDVIEWMEANCAL_STARTPOINTS_8_X_FRONT  240
#define BIRDVIEWMEANCAL_STARTPOINTS_8_Y_FRONT   40
#define BIRDVIEWMEANCAL_STARTPOINTS_9_X_FRONT   88
#define BIRDVIEWMEANCAL_STARTPOINTS_9_Y_FRONT   80
#define BIRDVIEWMEANCAL_STARTPOINTS_10_X_FRONT 169
#define BIRDVIEWMEANCAL_STARTPOINTS_10_Y_FRONT  80

#define BIRDVIEWMEANCAL_STARTPOINTS_1_X_BACK   33
#define BIRDVIEWMEANCAL_STARTPOINTS_1_Y_BACK    452
#define BIRDVIEWMEANCAL_STARTPOINTS_2_X_BACK  103
#define BIRDVIEWMEANCAL_STARTPOINTS_2_Y_BACK    452
#define BIRDVIEWMEANCAL_STARTPOINTS_3_X_BACK  171
#define BIRDVIEWMEANCAL_STARTPOINTS_3_Y_BACK    452
#define BIRDVIEWMEANCAL_STARTPOINTS_4_X_BACK  240
#define BIRDVIEWMEANCAL_STARTPOINTS_4_Y_BACK    452
#define BIRDVIEWMEANCAL_STARTPOINTS_5_X_BACK   33
#define BIRDVIEWMEANCAL_STARTPOINTS_5_Y_BACK   420
#define BIRDVIEWMEANCAL_STARTPOINTS_6_X_BACK   103
#define BIRDVIEWMEANCAL_STARTPOINTS_6_Y_BACK   420
#define BIRDVIEWMEANCAL_STARTPOINTS_7_X_BACK  171
#define BIRDVIEWMEANCAL_STARTPOINTS_7_Y_BACK   420
#define BIRDVIEWMEANCAL_STARTPOINTS_8_X_BACK  240
#define BIRDVIEWMEANCAL_STARTPOINTS_8_Y_BACK   420
#define BIRDVIEWMEANCAL_STARTPOINTS_9_X_BACK   88
#define BIRDVIEWMEANCAL_STARTPOINTS_9_Y_BACK   380
#define BIRDVIEWMEANCAL_STARTPOINTS_10_X_BACK 169
#define BIRDVIEWMEANCAL_STARTPOINTS_10_Y_BACK  380

#define BIRDVIEWMEANCAL_SIZE_X_LINE1_LEFT       20
#define BIRDVIEWMEANCAL_SIZE_X_LINE2_LEFT       20
#define BIRDVIEWMEANCAL_SIZE_X_LINE3_LEFT       20
#define BIRDVIEWMEANCAL_SIZE_Y_LINE1_LEFT       64
#define BIRDVIEWMEANCAL_SIZE_Y_LINE2_LEFT       64
#define BIRDVIEWMEANCAL_SIZE_Y_LINE3_LEFT      120

#define BIRDVIEWMEANCAL_SIZE_X_LINE1_RIGHT       20
#define BIRDVIEWMEANCAL_SIZE_X_LINE2_RIGHT       20
#define BIRDVIEWMEANCAL_SIZE_X_LINE3_RIGHT       20
#define BIRDVIEWMEANCAL_SIZE_Y_LINE1_RIGHT       64
#define BIRDVIEWMEANCAL_SIZE_Y_LINE2_RIGHT       64
#define BIRDVIEWMEANCAL_SIZE_Y_LINE3_RIGHT      120

#define BIRDVIEWMEANCAL_SIZE_X_LINE1_FRONT       60
#define BIRDVIEWMEANCAL_SIZE_X_LINE2_FRONT       60
#define BIRDVIEWMEANCAL_SIZE_X_LINE3_FRONT       80
#define BIRDVIEWMEANCAL_SIZE_Y_LINE1_FRONT       20
#define BIRDVIEWMEANCAL_SIZE_Y_LINE2_FRONT       20
#define BIRDVIEWMEANCAL_SIZE_Y_LINE3_FRONT       20

#define BIRDVIEWMEANCAL_SIZE_X_LINE1_BACK       60
#define BIRDVIEWMEANCAL_SIZE_X_LINE2_BACK       60
#define BIRDVIEWMEANCAL_SIZE_X_LINE3_BACK       80
#define BIRDVIEWMEANCAL_SIZE_Y_LINE1_BACK       20
#define BIRDVIEWMEANCAL_SIZE_Y_LINE2_BACK       20
#define BIRDVIEWMEANCAL_SIZE_Y_LINE3_BACK       20

#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_1   1
#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_2   1
#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_3   1
#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_4   1
#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_5   1
#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_6   1
#define SINGLEVIEWNOISECAL_FUNCTIONENABLED_7   1

#define SINGLEVIEWNOISECAL_SIZE_X               24      
#define SINGLEVIEWNOISECAL_SIZE_Y               24      

#define SINGLEVIEWNOISECAL_STARTPOINT_X_1   14
#define SINGLEVIEWNOISECAL_STARTPOINT_Y_1    426
#define SINGLEVIEWNOISECAL_STARTPOINT_X_2   681
#define SINGLEVIEWNOISECAL_STARTPOINT_Y_2    426
#define SINGLEVIEWNOISECAL_STARTPOINT_X_3   0
#define SINGLEVIEWNOISECAL_STARTPOINT_Y_3    0
#define SINGLEVIEWNOISECAL_STARTPOINT_X_4   0
#define SINGLEVIEWNOISECAL_STARTPOINT_Y_4    0



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void alSTATISTIC_LoadDefault(alSTATISTIC_Cfg *a_ptCfg)
{
	a_ptCfg->atBirdViewMeanCalInfo[0].ucFunctionEnabled = BIRDVIEWMEANCAL_FUNCTIONENABLED_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].ucROICnt_MeanCal = BIRDVIEWMEANCAL_ROICNT_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[0].lX = BIRDVIEWMEANCAL_STARTPOINTS_1_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[0].lY = BIRDVIEWMEANCAL_STARTPOINTS_1_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[1].lX = BIRDVIEWMEANCAL_STARTPOINTS_2_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[1].lY = BIRDVIEWMEANCAL_STARTPOINTS_2_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[2].lX = BIRDVIEWMEANCAL_STARTPOINTS_3_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[2].lY = BIRDVIEWMEANCAL_STARTPOINTS_3_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[3].lX = BIRDVIEWMEANCAL_STARTPOINTS_4_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[3].lY = BIRDVIEWMEANCAL_STARTPOINTS_4_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[4].lX = BIRDVIEWMEANCAL_STARTPOINTS_5_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[4].lY = BIRDVIEWMEANCAL_STARTPOINTS_5_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[5].lX = BIRDVIEWMEANCAL_STARTPOINTS_6_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[5].lY = BIRDVIEWMEANCAL_STARTPOINTS_6_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[6].lX = BIRDVIEWMEANCAL_STARTPOINTS_7_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[6].lY = BIRDVIEWMEANCAL_STARTPOINTS_7_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[7].lX = BIRDVIEWMEANCAL_STARTPOINTS_8_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[7].lY = BIRDVIEWMEANCAL_STARTPOINTS_8_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[8].lX = BIRDVIEWMEANCAL_STARTPOINTS_9_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[8].lY = BIRDVIEWMEANCAL_STARTPOINTS_9_Y_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[9].lX = BIRDVIEWMEANCAL_STARTPOINTS_10_X_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIStartPoints_MeanCal[9].lY = BIRDVIEWMEANCAL_STARTPOINTS_10_Y_LEFT;

	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[0].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[0].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[1].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[1].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[2].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[2].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[3].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[3].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[4].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[4].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[5].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[5].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[6].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[6].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[7].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[7].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[8].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[8].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[9].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_LEFT;
	a_ptCfg->atBirdViewMeanCalInfo[0].atROIAreaSize_MeanCal[9].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_LEFT;


	a_ptCfg->atBirdViewMeanCalInfo[1].ucFunctionEnabled = BIRDVIEWMEANCAL_FUNCTIONENABLED_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].ucROICnt_MeanCal = BIRDVIEWMEANCAL_ROICNT_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[0].lX = BIRDVIEWMEANCAL_STARTPOINTS_1_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[0].lY = BIRDVIEWMEANCAL_STARTPOINTS_1_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[1].lX = BIRDVIEWMEANCAL_STARTPOINTS_2_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[1].lY = BIRDVIEWMEANCAL_STARTPOINTS_2_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[2].lX = BIRDVIEWMEANCAL_STARTPOINTS_3_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[2].lY = BIRDVIEWMEANCAL_STARTPOINTS_3_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[3].lX = BIRDVIEWMEANCAL_STARTPOINTS_4_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[3].lY = BIRDVIEWMEANCAL_STARTPOINTS_4_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[4].lX = BIRDVIEWMEANCAL_STARTPOINTS_5_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[4].lY = BIRDVIEWMEANCAL_STARTPOINTS_5_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[5].lX = BIRDVIEWMEANCAL_STARTPOINTS_6_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[5].lY = BIRDVIEWMEANCAL_STARTPOINTS_6_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[6].lX = BIRDVIEWMEANCAL_STARTPOINTS_7_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[6].lY = BIRDVIEWMEANCAL_STARTPOINTS_7_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[7].lX = BIRDVIEWMEANCAL_STARTPOINTS_8_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[7].lY = BIRDVIEWMEANCAL_STARTPOINTS_8_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[8].lX = BIRDVIEWMEANCAL_STARTPOINTS_9_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[8].lY = BIRDVIEWMEANCAL_STARTPOINTS_9_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[9].lX = BIRDVIEWMEANCAL_STARTPOINTS_10_X_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIStartPoints_MeanCal[9].lY = BIRDVIEWMEANCAL_STARTPOINTS_10_Y_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[0].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[0].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[1].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[1].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[2].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[2].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[3].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[3].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[4].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[4].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[5].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[5].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[6].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[6].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[7].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[7].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[8].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[8].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[9].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_RIGHT;
	a_ptCfg->atBirdViewMeanCalInfo[1].atROIAreaSize_MeanCal[9].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_RIGHT;

	a_ptCfg->atBirdViewMeanCalInfo[2].ucFunctionEnabled = BIRDVIEWMEANCAL_FUNCTIONENABLED_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].ucROICnt_MeanCal = BIRDVIEWMEANCAL_ROICNT_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[0].lX = BIRDVIEWMEANCAL_STARTPOINTS_1_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[0].lY = BIRDVIEWMEANCAL_STARTPOINTS_1_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[1].lX = BIRDVIEWMEANCAL_STARTPOINTS_2_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[1].lY = BIRDVIEWMEANCAL_STARTPOINTS_2_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[2].lX = BIRDVIEWMEANCAL_STARTPOINTS_3_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[2].lY = BIRDVIEWMEANCAL_STARTPOINTS_3_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[3].lX = BIRDVIEWMEANCAL_STARTPOINTS_4_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[3].lY = BIRDVIEWMEANCAL_STARTPOINTS_4_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[4].lX = BIRDVIEWMEANCAL_STARTPOINTS_5_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[4].lY = BIRDVIEWMEANCAL_STARTPOINTS_5_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[5].lX = BIRDVIEWMEANCAL_STARTPOINTS_6_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[5].lY = BIRDVIEWMEANCAL_STARTPOINTS_6_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[6].lX = BIRDVIEWMEANCAL_STARTPOINTS_7_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[6].lY = BIRDVIEWMEANCAL_STARTPOINTS_7_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[7].lX = BIRDVIEWMEANCAL_STARTPOINTS_8_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[7].lY = BIRDVIEWMEANCAL_STARTPOINTS_8_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[8].lX = BIRDVIEWMEANCAL_STARTPOINTS_9_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[8].lY = BIRDVIEWMEANCAL_STARTPOINTS_9_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[9].lX = BIRDVIEWMEANCAL_STARTPOINTS_10_X_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIStartPoints_MeanCal[9].lY = BIRDVIEWMEANCAL_STARTPOINTS_10_Y_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[0].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[0].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[1].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[1].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[2].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[2].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[3].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[3].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[4].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[4].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[5].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[5].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[6].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[6].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[7].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[7].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[8].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[8].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[9].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_FRONT;
	a_ptCfg->atBirdViewMeanCalInfo[2].atROIAreaSize_MeanCal[9].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_FRONT;

	a_ptCfg->atBirdViewMeanCalInfo[3].ucFunctionEnabled = BIRDVIEWMEANCAL_FUNCTIONENABLED_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].ucROICnt_MeanCal = BIRDVIEWMEANCAL_ROICNT_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[0].lX = BIRDVIEWMEANCAL_STARTPOINTS_1_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[0].lY = BIRDVIEWMEANCAL_STARTPOINTS_1_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[1].lX = BIRDVIEWMEANCAL_STARTPOINTS_2_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[1].lY = BIRDVIEWMEANCAL_STARTPOINTS_2_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[2].lX = BIRDVIEWMEANCAL_STARTPOINTS_3_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[2].lY = BIRDVIEWMEANCAL_STARTPOINTS_3_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[3].lX = BIRDVIEWMEANCAL_STARTPOINTS_4_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[3].lY = BIRDVIEWMEANCAL_STARTPOINTS_4_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[4].lX = BIRDVIEWMEANCAL_STARTPOINTS_5_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[4].lY = BIRDVIEWMEANCAL_STARTPOINTS_5_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[5].lX = BIRDVIEWMEANCAL_STARTPOINTS_6_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[5].lY = BIRDVIEWMEANCAL_STARTPOINTS_6_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[6].lX = BIRDVIEWMEANCAL_STARTPOINTS_7_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[6].lY = BIRDVIEWMEANCAL_STARTPOINTS_7_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[7].lX = BIRDVIEWMEANCAL_STARTPOINTS_8_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[7].lY = BIRDVIEWMEANCAL_STARTPOINTS_8_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[8].lX = BIRDVIEWMEANCAL_STARTPOINTS_9_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[8].lY = BIRDVIEWMEANCAL_STARTPOINTS_9_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[9].lX = BIRDVIEWMEANCAL_STARTPOINTS_10_X_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIStartPoints_MeanCal[9].lY = BIRDVIEWMEANCAL_STARTPOINTS_10_Y_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[0].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[0].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[1].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[1].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[2].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[2].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[3].lX = BIRDVIEWMEANCAL_SIZE_X_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[3].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE1_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[4].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[4].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[5].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[5].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[6].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[6].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[7].lX = BIRDVIEWMEANCAL_SIZE_X_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[7].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE2_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[8].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[8].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[9].lX = BIRDVIEWMEANCAL_SIZE_X_LINE3_BACK;
	a_ptCfg->atBirdViewMeanCalInfo[3].atROIAreaSize_MeanCal[9].lY = BIRDVIEWMEANCAL_SIZE_Y_LINE3_BACK;

	a_ptCfg->atSingleViewNoiseCalInfo[0].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_1;
	a_ptCfg->atSingleViewNoiseCalInfo[0].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_1;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[0].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;

	a_ptCfg->atSingleViewNoiseCalInfo[1].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_2;
	a_ptCfg->atSingleViewNoiseCalInfo[1].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_2;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[1].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;

	a_ptCfg->atSingleViewNoiseCalInfo[2].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_3;
	a_ptCfg->atSingleViewNoiseCalInfo[2].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_3;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[2].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;

	a_ptCfg->atSingleViewNoiseCalInfo[3].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_4;
	a_ptCfg->atSingleViewNoiseCalInfo[3].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_4;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[3].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;

	a_ptCfg->atSingleViewNoiseCalInfo[4].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_5;
	a_ptCfg->atSingleViewNoiseCalInfo[4].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_5;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[4].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;


	a_ptCfg->atSingleViewNoiseCalInfo[5].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_6;
	a_ptCfg->atSingleViewNoiseCalInfo[5].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_6;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[5].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;

	a_ptCfg->atSingleViewNoiseCalInfo[6].ucFunctionEnabled = SINGLEVIEWNOISECAL_FUNCTIONENABLED_7;
	a_ptCfg->atSingleViewNoiseCalInfo[6].ucROICnt_NoiseCal = SINGLEVIEWNOISECAL_ROICNT_7;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[0].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_1;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[0].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_1;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[0].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[0].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[1].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_2;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[1].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_2;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[1].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[1].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[2].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_3;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[2].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_3;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[2].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[2].lY=SINGLEVIEWNOISECAL_SIZE_Y;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[3].lX = SINGLEVIEWNOISECAL_STARTPOINT_X_4;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIStartPoints_NoiseCal[3].lY = SINGLEVIEWNOISECAL_STARTPOINT_Y_4;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[3].lX=SINGLEVIEWNOISECAL_SIZE_X;
	a_ptCfg->atSingleViewNoiseCalInfo[6].atROIAreaSize_NoiseCal[3].lY=SINGLEVIEWNOISECAL_SIZE_Y;
}
