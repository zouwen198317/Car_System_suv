
#include "EAGLEK3_Def.h"
#include "alMANUALK/alMANUALK_CalRefData.h"
#include "alErrorCode.h"


#ifdef WIN32
/** \brief Record the Working Folder Path. */
wchar_t g_EAGLEK3_awcWorkingPath[MAX_PATH];
#endif

#ifdef WIN32
#include "alINI.h"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void  EAGLEK3_LoadFM_BV_CfgByDefault(UINT8 a_ucCamNum, alFM_v2_1_ModelCfg *a_ptFMCfg)
{
    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_190, &a_ptFMCfg[EAGLEK3_BV_LEFT]);

    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_190, &a_ptFMCfg[EAGLEK3_BV_RIGHT]);

    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_190, &a_ptFMCfg[EAGLEK3_BV_FRONT]);

    alFM_v2_1_LoadDefault(alFM_v2_1_SPARROW_144, &a_ptFMCfg[EAGLEK3_BV_BACK]);
}

void EAGLEK3_LoadDefaultExtrinsicData(alCAMERAINFO_ExtrinsicParams a_atCameraExtrinsicParams[EAGLEK3_NUM_BV_CHANNEL])
{
    // FRONT
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].fPitchAngle = SIM_DEFAULT_CAM_PITCH_BV_FRONT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].fYawAngle = SIM_DEFAULT_CAM_YAW_BV_FRONT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].fRollAngle = SIM_DEFAULT_CAM_ROLL_BV_FRONT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].lCameraPosX = SIM_DEFAULT_CAM_POS_X_BV_FRONT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].lCameraPosY = SIM_DEFAULT_CAM_POS_Y_BV_FRONT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].lCameraPosZ = SIM_DEFAULT_CAM_POS_Z_BV_FRONT;

    // BACK
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].fPitchAngle = SIM_DEFAULT_CAM_PITCH_BV_BACK;
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].fYawAngle = SIM_DEFAULT_CAM_YAW_BV_BACK;
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].fRollAngle = SIM_DEFAULT_CAM_ROLL_BV_BACK;
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].lCameraPosX = SIM_DEFAULT_CAM_POS_X_BV_BACK;
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].lCameraPosY = SIM_DEFAULT_CAM_POS_Y_BV_BACK;
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].lCameraPosZ = SIM_DEFAULT_CAM_POS_Z_BV_BACK;


    // LEFT
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].fYawAngle = SIM_DEFAULT_CAM_YAW_BV_LEFT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].fRollAngle = SIM_DEFAULT_CAM_ROLL_BV_LEFT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].lCameraPosX = SIM_DEFAULT_CAM_POS_X_BV_LEFT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].lCameraPosY = SIM_DEFAULT_CAM_POS_Y_BV_LEFT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].lCameraPosZ = SIM_DEFAULT_CAM_POS_Z_BV_LEFT;

    // RIGHT
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].fPitchAngle = SIM_DEFAULT_CAM_PITCH_BV_RIGHT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].fYawAngle = SIM_DEFAULT_CAM_YAW_BV_RIGHT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].fRollAngle = SIM_DEFAULT_CAM_ROLL_BV_RIGHT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].lCameraPosX = SIM_DEFAULT_CAM_POS_X_BV_RIGHT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].lCameraPosY = SIM_DEFAULT_CAM_POS_Y_BV_RIGHT;
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].lCameraPosZ = SIM_DEFAULT_CAM_POS_Z_BV_RIGHT;
}


void EAGLEK3_LoadDefaultCalibrationData(alCOMMONK_CalibrationParams a_atCalibrationParams[EAGLEK3_NUM_BV_CHANNEL])
{
    // FRONT

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][0] = SIM_DEFAULT_FM11_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][1] = SIM_DEFAULT_FM12_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][2] = SIM_DEFAULT_FM13_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][3] = SIM_DEFAULT_FM21_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][4] = SIM_DEFAULT_FM22_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][5] = SIM_DEFAULT_FM23_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][6] = SIM_DEFAULT_FM31_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][7] = SIM_DEFAULT_FM32_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][8] = SIM_DEFAULT_FM33_W2I;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][0] = SIM_DEFAULT_FM11_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][1] = SIM_DEFAULT_FM12_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][2] = SIM_DEFAULT_FM13_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][3] = SIM_DEFAULT_FM21_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][4] = SIM_DEFAULT_FM22_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][5] = SIM_DEFAULT_FM23_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][6] = SIM_DEFAULT_FM31_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][7] = SIM_DEFAULT_FM32_I2W;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][8] = SIM_DEFAULT_FM33_I2W;

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][0] = SIM_DEFAULT_CAM_RMATRIX11_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][1] = SIM_DEFAULT_CAM_RMATRIX12_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][2] = SIM_DEFAULT_CAM_RMATRIX13_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][3] = SIM_DEFAULT_CAM_RMATRIX21_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][4] = SIM_DEFAULT_CAM_RMATRIX22_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][5] = SIM_DEFAULT_CAM_RMATRIX23_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][6] = SIM_DEFAULT_CAM_RMATRIX31_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][7] = SIM_DEFAULT_CAM_RMATRIX32_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][8] = SIM_DEFAULT_CAM_RMATRIX33_BV2RC_FRONT;

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][0] = SIM_DEFAULT_CAM_RMATRIX11_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][1] = SIM_DEFAULT_CAM_RMATRIX12_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][2] = SIM_DEFAULT_CAM_RMATRIX13_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][3] = SIM_DEFAULT_CAM_RMATRIX21_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][4] = SIM_DEFAULT_CAM_RMATRIX22_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][5] = SIM_DEFAULT_CAM_RMATRIX23_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][6] = SIM_DEFAULT_CAM_RMATRIX31_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][7] = SIM_DEFAULT_CAM_RMATRIX32_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][8] = SIM_DEFAULT_CAM_RMATRIX33_RC2BV_FRONT;

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[0][0] = SIM_DEFAULT_CAM_TMATRIX1_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[0][1] = SIM_DEFAULT_CAM_TMATRIX2_BV2RC_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[0][2] = SIM_DEFAULT_CAM_TMATRIX3_BV2RC_FRONT;

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[1][0] = SIM_DEFAULT_CAM_TMATRIX1_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[1][1] = SIM_DEFAULT_CAM_TMATRIX2_RC2BV_FRONT;
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[1][2] = SIM_DEFAULT_CAM_TMATRIX3_RC2BV_FRONT;

    // BACK

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][0] = SIM_DEFAULT_BM11_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][1] = SIM_DEFAULT_BM12_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][2] = SIM_DEFAULT_BM13_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][3] = SIM_DEFAULT_BM21_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][4] = SIM_DEFAULT_BM22_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][5] = SIM_DEFAULT_BM23_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][6] = SIM_DEFAULT_BM31_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][7] = SIM_DEFAULT_BM32_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][8] = SIM_DEFAULT_BM33_W2I;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][0] = SIM_DEFAULT_BM11_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][1] = SIM_DEFAULT_BM12_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][2] = SIM_DEFAULT_BM13_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][3] = SIM_DEFAULT_BM21_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][4] = SIM_DEFAULT_BM22_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][5] = SIM_DEFAULT_BM23_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][6] = SIM_DEFAULT_BM31_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][7] = SIM_DEFAULT_BM32_I2W;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][8] = SIM_DEFAULT_BM33_I2W;

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][0] = SIM_DEFAULT_CAM_RMATRIX11_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][1] = SIM_DEFAULT_CAM_RMATRIX12_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][2] = SIM_DEFAULT_CAM_RMATRIX13_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][3] = SIM_DEFAULT_CAM_RMATRIX21_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][4] = SIM_DEFAULT_CAM_RMATRIX22_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][5] = SIM_DEFAULT_CAM_RMATRIX23_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][6] = SIM_DEFAULT_CAM_RMATRIX31_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][7] = SIM_DEFAULT_CAM_RMATRIX32_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][8] = SIM_DEFAULT_CAM_RMATRIX33_BV2RC_BACK;

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][0] = SIM_DEFAULT_CAM_RMATRIX11_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][1] = SIM_DEFAULT_CAM_RMATRIX12_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][2] = SIM_DEFAULT_CAM_RMATRIX13_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][3] = SIM_DEFAULT_CAM_RMATRIX21_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][4] = SIM_DEFAULT_CAM_RMATRIX22_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][5] = SIM_DEFAULT_CAM_RMATRIX23_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][6] = SIM_DEFAULT_CAM_RMATRIX31_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][7] = SIM_DEFAULT_CAM_RMATRIX32_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][8] = SIM_DEFAULT_CAM_RMATRIX33_RC2BV_BACK;

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[0][0] = SIM_DEFAULT_CAM_TMATRIX1_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[0][1] = SIM_DEFAULT_CAM_TMATRIX2_BV2RC_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[0][2] = SIM_DEFAULT_CAM_TMATRIX3_BV2RC_BACK;

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[1][0] = SIM_DEFAULT_CAM_TMATRIX1_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[1][1] = SIM_DEFAULT_CAM_TMATRIX2_RC2BV_BACK;
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[1][2] = SIM_DEFAULT_CAM_TMATRIX3_RC2BV_BACK;

    // LEFT

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][0] = SIM_DEFAULT_LM11_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][1] = SIM_DEFAULT_LM12_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][2] = SIM_DEFAULT_LM13_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][3] = SIM_DEFAULT_LM21_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][4] = SIM_DEFAULT_LM22_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][5] = SIM_DEFAULT_LM23_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][6] = SIM_DEFAULT_LM31_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][7] = SIM_DEFAULT_LM32_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][8] = SIM_DEFAULT_LM33_W2I;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][0] = SIM_DEFAULT_LM11_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][1] = SIM_DEFAULT_LM12_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][2] = SIM_DEFAULT_LM13_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][3] = SIM_DEFAULT_LM21_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][4] = SIM_DEFAULT_LM22_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][5] = SIM_DEFAULT_LM23_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][6] = SIM_DEFAULT_LM31_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][7] = SIM_DEFAULT_LM32_I2W;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][8] = SIM_DEFAULT_LM33_I2W;

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][0] = SIM_DEFAULT_CAM_RMATRIX11_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][1] = SIM_DEFAULT_CAM_RMATRIX12_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][2] = SIM_DEFAULT_CAM_RMATRIX13_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][3] = SIM_DEFAULT_CAM_RMATRIX21_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][4] = SIM_DEFAULT_CAM_RMATRIX22_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][5] = SIM_DEFAULT_CAM_RMATRIX23_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][6] = SIM_DEFAULT_CAM_RMATRIX31_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][7] = SIM_DEFAULT_CAM_RMATRIX32_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][8] = SIM_DEFAULT_CAM_RMATRIX33_BV2RC_LEFT;

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][0] = SIM_DEFAULT_CAM_RMATRIX11_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][1] = SIM_DEFAULT_CAM_RMATRIX12_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][2] = SIM_DEFAULT_CAM_RMATRIX13_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][3] = SIM_DEFAULT_CAM_RMATRIX21_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][4] = SIM_DEFAULT_CAM_RMATRIX22_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][5] = SIM_DEFAULT_CAM_RMATRIX23_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][6] = SIM_DEFAULT_CAM_RMATRIX31_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][7] = SIM_DEFAULT_CAM_RMATRIX32_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][8] = SIM_DEFAULT_CAM_RMATRIX33_RC2BV_LEFT;

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[0][0] = SIM_DEFAULT_CAM_TMATRIX1_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[0][1] = SIM_DEFAULT_CAM_TMATRIX2_BV2RC_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[0][2] = SIM_DEFAULT_CAM_TMATRIX3_BV2RC_LEFT;

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[1][0] = SIM_DEFAULT_CAM_TMATRIX1_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[1][1] = SIM_DEFAULT_CAM_TMATRIX2_RC2BV_LEFT;
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[1][2] = SIM_DEFAULT_CAM_TMATRIX3_RC2BV_LEFT;

    // RIGHT

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][0] = SIM_DEFAULT_RM11_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][1] = SIM_DEFAULT_RM12_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][2] = SIM_DEFAULT_RM13_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][3] = SIM_DEFAULT_RM21_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][4] = SIM_DEFAULT_RM22_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][5] = SIM_DEFAULT_RM23_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][6] = SIM_DEFAULT_RM31_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][7] = SIM_DEFAULT_RM32_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][8] = SIM_DEFAULT_RM33_W2I;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][0] = SIM_DEFAULT_RM11_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][1] = SIM_DEFAULT_RM12_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][2] = SIM_DEFAULT_RM13_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][3] = SIM_DEFAULT_RM21_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][4] = SIM_DEFAULT_RM22_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][5] = SIM_DEFAULT_RM23_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][6] = SIM_DEFAULT_RM31_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][7] = SIM_DEFAULT_RM32_I2W;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][8] = SIM_DEFAULT_RM33_I2W;

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][0] = SIM_DEFAULT_CAM_RMATRIX11_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][1] = SIM_DEFAULT_CAM_RMATRIX12_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][2] = SIM_DEFAULT_CAM_RMATRIX13_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][3] = SIM_DEFAULT_CAM_RMATRIX21_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][4] = SIM_DEFAULT_CAM_RMATRIX22_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][5] = SIM_DEFAULT_CAM_RMATRIX23_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][6] = SIM_DEFAULT_CAM_RMATRIX31_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][7] = SIM_DEFAULT_CAM_RMATRIX32_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][8] = SIM_DEFAULT_CAM_RMATRIX33_BV2RC_RIGHT;

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][0] = SIM_DEFAULT_CAM_RMATRIX11_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][1] = SIM_DEFAULT_CAM_RMATRIX12_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][2] = SIM_DEFAULT_CAM_RMATRIX13_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][3] = SIM_DEFAULT_CAM_RMATRIX21_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][4] = SIM_DEFAULT_CAM_RMATRIX22_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][5] = SIM_DEFAULT_CAM_RMATRIX23_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][6] = SIM_DEFAULT_CAM_RMATRIX31_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][7] = SIM_DEFAULT_CAM_RMATRIX32_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][8] = SIM_DEFAULT_CAM_RMATRIX33_RC2BV_RIGHT;

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[0][0] = SIM_DEFAULT_CAM_TMATRIX1_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[0][1] = SIM_DEFAULT_CAM_TMATRIX2_BV2RC_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[0][2] = SIM_DEFAULT_CAM_TMATRIX3_BV2RC_RIGHT;

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[1][0] = SIM_DEFAULT_CAM_TMATRIX1_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[1][1] = SIM_DEFAULT_CAM_TMATRIX2_RC2BV_RIGHT;
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[1][2] = SIM_DEFAULT_CAM_TMATRIX3_RC2BV_RIGHT;
}

void EAGLEK3_LoadDefault(EAGLEK3_Cfg *a_ptEAGLEK3_Cfg)
{
    a_ptEAGLEK3_Cfg->ucFactoryAutoKSwitch = SIM_DEFAULT_FACTORY_AUTOK_SWITCH;

    // Default Setting for CamK Config 
    MANUALK_LoadDefault(a_ptEAGLEK3_Cfg->atMANUALK_Cfg);

    // Load Extrinsic data (Angle and possition)
    EAGLEK3_LoadDefaultExtrinsicData(a_ptEAGLEK3_Cfg->atCameraExtrinsicParams);

    // Load RT and M33
    EAGLEK3_LoadDefaultCalibrationData(a_ptEAGLEK3_Cfg->atCalibrationParams);

    // 更BV AUTOK CFG箇砞
    alBVCAM_FACAUTOK_LoadDefault(&a_ptEAGLEK3_Cfg->tAutoK_Cfg);
}

void EAGLEK3_LoadFieldDataFineTuneOffsetByDefault(alPointINT32    a_atBVFPOffsetFineTuned[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM_AUTOK])
{
    // Load Default Fine-tune Setting
    // The positions offset of the fixed points for calibration.
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][0].lX = SIM_DEFAULT_FP_OFFSET_X_FRONT_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][0].lY = SIM_DEFAULT_FP_OFFSET_Y_FRONT_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][1].lX = SIM_DEFAULT_FP_OFFSET_X_FRONT_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][1].lY = SIM_DEFAULT_FP_OFFSET_Y_FRONT_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][2].lX = SIM_DEFAULT_FP_OFFSET_X_FRONT_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][2].lY = SIM_DEFAULT_FP_OFFSET_Y_FRONT_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][3].lX = SIM_DEFAULT_FP_OFFSET_X_FRONT_3;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_FRONT][3].lY = SIM_DEFAULT_FP_OFFSET_Y_FRONT_3;

    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][0].lX = SIM_DEFAULT_FP_OFFSET_X_BACK_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][0].lY = SIM_DEFAULT_FP_OFFSET_Y_BACK_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][1].lX = SIM_DEFAULT_FP_OFFSET_X_BACK_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][1].lY = SIM_DEFAULT_FP_OFFSET_Y_BACK_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][2].lX = SIM_DEFAULT_FP_OFFSET_X_BACK_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][2].lY = SIM_DEFAULT_FP_OFFSET_Y_BACK_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][3].lX = SIM_DEFAULT_FP_OFFSET_X_BACK_3;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_BACK][3].lY = SIM_DEFAULT_FP_OFFSET_Y_BACK_3;

    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][0].lX = SIM_DEFAULT_FP_OFFSET_X_LEFT_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][0].lY = SIM_DEFAULT_FP_OFFSET_Y_LEFT_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][1].lX = SIM_DEFAULT_FP_OFFSET_X_LEFT_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][1].lY = SIM_DEFAULT_FP_OFFSET_Y_LEFT_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][2].lX = SIM_DEFAULT_FP_OFFSET_X_LEFT_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][2].lY = SIM_DEFAULT_FP_OFFSET_Y_LEFT_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][3].lX = SIM_DEFAULT_FP_OFFSET_X_LEFT_3;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_LEFT][3].lY = SIM_DEFAULT_FP_OFFSET_Y_LEFT_3;

    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][0].lX = SIM_DEFAULT_FP_OFFSET_X_RIGHT_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][0].lY = SIM_DEFAULT_FP_OFFSET_Y_RIGHT_0;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][1].lX = SIM_DEFAULT_FP_OFFSET_X_RIGHT_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][1].lY = SIM_DEFAULT_FP_OFFSET_Y_RIGHT_1;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][2].lX = SIM_DEFAULT_FP_OFFSET_X_RIGHT_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][2].lY = SIM_DEFAULT_FP_OFFSET_Y_RIGHT_2;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][3].lX = SIM_DEFAULT_FP_OFFSET_X_RIGHT_3;
    a_atBVFPOffsetFineTuned[EAGLEK3_BV_RIGHT][3].lY = SIM_DEFAULT_FP_OFFSET_Y_RIGHT_3;
}

void EAGLEK3_LoadFieldDataByDefault(EAGLEK3_FieldData *a_ptFeildData)
{
    MANUALK_LoadFeildDataByDefault(&a_ptFeildData->tManualKFieldData);

    alBVCAM_FACAUTOK_LoadDefaultFeildData(&a_ptFeildData->tAutoKFieldData);

    EAGLEK3_LoadFieldDataFineTuneOffsetByDefault(a_ptFeildData->atBVFPOffsetFineTuned);
}


static void EAGLEK3_CfgImportHexLocal(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, EAGLEK3_Cfg *a_ptCfg)
{
    UINT32 ulSubDataID = 0;

    ulSubDataID = a_ulDataID & 0x0FFF;

    switch (ulSubDataID)
    {
    case 0x0000:    // ucFactoryAutoKSwitch
    {
        a_ptCfg->ucFactoryAutoKSwitch = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0001:    // afPitchOffset[0]
    {
        a_ptCfg->afPitchOffset[0] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0002:    // afPitchOffset[1]
    {
        a_ptCfg->afPitchOffset[1] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0003:    // afPitchOffset[2]
    {
        a_ptCfg->afPitchOffset[2] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0004:    // afPitchOffset[3]
    {
        a_ptCfg->afPitchOffset[3] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0005:    // afYawOffset[0]
    {
        a_ptCfg->afYawOffset[0] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0006:    // afYawOffset[1]
    {
        a_ptCfg->afYawOffset[1] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0007:    // afYawOffset[2]
    {
        a_ptCfg->afYawOffset[2] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0008:    // afYawOffset[3]
    {
        a_ptCfg->afYawOffset[3] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0009:    // afRollOffset[0]
    {
        a_ptCfg->afRollOffset[0] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000A:    // afRollOffset[1]
    {
        a_ptCfg->afRollOffset[1] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000B:    // afRollOffset[2]
    {
        a_ptCfg->afRollOffset[2] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000C:    // afRollOffset[3]
    {
        a_ptCfg->afRollOffset[3] = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000D:    // alCameraPosXOffset[0]
    {
        a_ptCfg->alCameraPosXOffset[0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000E:    // alCameraPosXOffset[1]
    {
        a_ptCfg->alCameraPosXOffset[1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000F:    // alCameraPosXOffset[2]
    {
        a_ptCfg->alCameraPosXOffset[2] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0010:    // alCameraPosXOffset[3]
    {
        a_ptCfg->alCameraPosXOffset[3] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0011:    // alCameraPosYOffset[0]
    {
        a_ptCfg->alCameraPosYOffset[0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0012:    // alCameraPosYOffset[1]
    {
        a_ptCfg->alCameraPosYOffset[1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0013:    // alCameraPosYOffset[2]
    {
        a_ptCfg->alCameraPosYOffset[2] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0014:    // alCameraPosYOffset[3]
    {
        a_ptCfg->alCameraPosYOffset[3] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0015:    // alCameraPosZOffset[0]
    {
        a_ptCfg->alCameraPosZOffset[0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0016:    // alCameraPosZOffset[1]
    {
        a_ptCfg->alCameraPosZOffset[1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0017:    // alCameraPosZOffset[2]
    {
        a_ptCfg->alCameraPosZOffset[2] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0018:    // alCameraPosZOffset[3]
    {
        a_ptCfg->alCameraPosZOffset[3] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0019:    // alLMBoundarySwitch[0]
    {
        a_ptCfg->alLMBoundarySwitch[0] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001A:    // alLMBoundarySwitch[1]
    {
        a_ptCfg->alLMBoundarySwitch[1] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001B:    // alLMBoundarySwitch[2]
    {
        a_ptCfg->alLMBoundarySwitch[2] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001C:    // alLMBoundarySwitch[3]
    {
        a_ptCfg->alLMBoundarySwitch[3] = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    default:    // default
    {
        DEBUG_Printf("Invalid Data ID: 0x%X\n - EagleK3CfgImport\n", a_ulDataID);
    }
    break;
    }
    
}

void EAGLEK3_CalibrationCfgImportHex(
    UINT32 a_ulDataID, UINT32 a_ulDataLength,
    UINT8 * a_pucBuffer, alCOMMONK_CalibrationParams *a_ptCalibrationParams
    )
{
    UINT32 ulSubDataID = 0;
    INT32 lCamID = 0;

    lCamID = (a_ulDataID >> 12) & 0x000F;

    if (lCamID >= EAGLEK3_NUM_BV_CHANNEL)
    {
        assert(0);
    }

    ulSubDataID = a_ulDataID & 0x0FFF;

    switch (ulSubDataID)
    {
    case 0x0000:    // aeIntrinsicMatrix[0]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0001:    // aeIntrinsicMatrix[1]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0002:    // aeIntrinsicMatrix[2]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0003:    // aeIntrinsicMatrix[3]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[3] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0004:    // aeIntrinsicMatrix[4]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[4] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0005:    // aeIntrinsicMatrix[5]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[5] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0006:    // aeIntrinsicMatrix[6]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[6] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0007:    // aeIntrinsicMatrix[7]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[7] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0008:    // aeIntrinsicMatrix[8]
    {
        a_ptCalibrationParams[lCamID].aeIntrinsicMatrix[8] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0009:    // aeRotationMatrix[0][0]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000A:    // aeRotationMatrix[0][1]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000B:    // aeRotationMatrix[0][2]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000C:    // aeRotationMatrix[0][3]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][3] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000D:    // aeRotationMatrix[0][4]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][4] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000E:    // aeRotationMatrix[0][5]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][5] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x000F:    // aeRotationMatrix[0][6]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][6] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0010:    // aeRotationMatrix[0][7]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][7] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0011:    // aeRotationMatrix[0][8]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[0][8] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0012:    // aeRotationMatrix[1][0]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0013:    // aeRotationMatrix[1][1]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0014:    // aeRotationMatrix[1][2]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0015:    // aeRotationMatrix[1][3]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][3] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0016:    // aeRotationMatrix[1][4]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][4] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0017:    // aeRotationMatrix[1][5]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][5] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0018:    // aeRotationMatrix[1][6]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][6] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0019:    // aeRotationMatrix[1][7]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][7] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001A:    // aeRotationMatrix[1][8]
    {
        a_ptCalibrationParams[lCamID].aeRotationMatrix[1][8] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001B:    // aeTranslationMatrix[0][0]
    {
        a_ptCalibrationParams[lCamID].aeTranslationMatrix[0][0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001C:    // aeTranslationMatrix[0][1]
    {
        a_ptCalibrationParams[lCamID].aeTranslationMatrix[0][1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001D:    // aeTranslationMatrix[0][2]
    {
        a_ptCalibrationParams[lCamID].aeTranslationMatrix[0][2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }

    case 0x001E:    // aeTranslationMatrix[1][0]
    {
        a_ptCalibrationParams[lCamID].aeTranslationMatrix[1][0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x001F:    // aeTranslationMatrix[1][1]
    {
        a_ptCalibrationParams[lCamID].aeTranslationMatrix[1][1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0020:    // aeTranslationMatrix[1][2]
    {
        a_ptCalibrationParams[lCamID].aeTranslationMatrix[1][2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0021:    // aeHomographyMatrix[0][0]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0022:    // aeHomographyMatrix[0][1]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0023:    // aeHomographyMatrix[0][2]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0024:    // aeHomographyMatrix[0][3]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][3] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0025:    // aeHomographyMatrix[0][4]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][4] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0026:    // aeHomographyMatrix[0][5]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][5] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0027:    // aeHomographyMatrix[0][6]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][6] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0028:    // aeHomographyMatrix[0][7]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][7] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0029:    // aeHomographyMatrix[0][8]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[0][8] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002A:    // aeHomographyMatrix[1][0]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][0] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002B:    // aeHomographyMatrix[1][1]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][1] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002C:    // aeHomographyMatrix[1][2]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][2] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002D:    // aeHomographyMatrix[1][3]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][3] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002E:    // aeHomographyMatrix[1][4]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][4] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x002F:    // aeHomographyMatrix[1][5]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][5] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0030:    // aeHomographyMatrix[1][6]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][6] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0031:    // aeHomographyMatrix[1][7]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][7] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0032:    // aeHomographyMatrix[1][8]
    {
        a_ptCalibrationParams[lCamID].aeHomographyMatrix[1][8] = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;
    default:    // default
    {
        // 
        DEBUG_Printf("Invalid Data ID: 0x%X\n - EagleK3CalibrationCfgImport\n", a_ulDataID);
    }
    break;

    }
}

void EAGLEK3_ExtrinsicCfgImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, alCAMERAINFO_ExtrinsicParams *a_ptExtrinsicParams)
{
    UINT32 ulSubDataID = 0;
    INT32 lCamID = 0;

    lCamID = (a_ulDataID >> 12) & 0x000F;

    if (lCamID >= EAGLEK3_NUM_BV_CHANNEL)
    {
        assert(0);
    }

    ulSubDataID = a_ulDataID & 0x0FFF;

    switch (ulSubDataID)
    {
    case 0x0000:    // ulImageWidth
    {
        a_ptExtrinsicParams[lCamID].ulImageWidth = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0001:    // ulImageHeight
    {
        a_ptExtrinsicParams[lCamID].ulImageHeight = alHEXDATA_UnpackUINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0002:    // fPitchAngle
    {
        a_ptExtrinsicParams[lCamID].fPitchAngle = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0003:    // fYawAngle
    {
        a_ptExtrinsicParams[lCamID].fYawAngle = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0004:    // fRollAngle
    {
        a_ptExtrinsicParams[lCamID].fRollAngle = alHEXDATA_UnpackFLOAT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0005:    // lCameraPosX
    {
        a_ptExtrinsicParams[lCamID].lCameraPosX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0006:    // lCameraPosY
    {
        a_ptExtrinsicParams[lCamID].lCameraPosY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0007:    // lCameraPosZ
    {
        a_ptExtrinsicParams[lCamID].lCameraPosZ = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    default:    // default
    {
        //
        DEBUG_Printf("Invalid Data ID: 0x%X\n - EagleK3ExtrinsicCfgImport\n", a_ulDataID);
    }
    break;
    }
}

void EAGLEK3_CfgImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, EAGLEK3_Cfg *a_ptCfg)
{
    UINT32 ulSubFunctionID = 0;

    ulSubFunctionID = a_ulDataID & 0xF000;

    switch (ulSubFunctionID)
    {
    case 0x0000:    // EagleK3 local
    {
        EAGLEK3_CfgImportHexLocal(a_ulDataID, a_ulDataLength, a_pucBuffer, a_ptCfg);
    }
    break;
    case 0x1000:    // AutoK
    {
        alBVCAM_FACAUTOK_CfgImportHex(a_ulDataID, a_ulDataLength, a_pucBuffer, &a_ptCfg->tAutoK_Cfg);
    }
    break;
    case 0x2000:    // ManualK
    {
        MANUALK_CfgImportHex(a_ulDataID, a_ulDataLength, a_pucBuffer, a_ptCfg->atMANUALK_Cfg);
    }
    break;
    default:    // default
    {
        DEBUG_Printf("Invalid Data ID: 0x%X\n - EagleK3CfgImport\n", a_ulDataID);
    }
    break;
    }
}

UINT32 EAGLEK3_ExtrinsicCfgExportHex(
    UINT32 a_ulSectionID,
    alCAMERAINFO_ExtrinsicParams *a_ptExtrinsicParams,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT32 ulViewID = 0x0000; // 0: view 0 1: view 1 2: view 2  3: view 3
    UINT32 ulViewID_Step = 0x1000;
    UINT32 ulSubFuncID = 0x0000;
    UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0;


    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    // start to export each view
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulItemID = 0x0000;
        // ulImageWidth
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptExtrinsicParams[lCAMId].ulImageWidth, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // ulImageHeight
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT32(ulDataID, a_ptExtrinsicParams[lCAMId].ulImageHeight, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // fPitchAngle
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptExtrinsicParams[lCAMId].fPitchAngle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // fYawAngle
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptExtrinsicParams[lCAMId].fYawAngle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // fRollAngle
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptExtrinsicParams[lCAMId].fRollAngle, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // lCameraPosX
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptExtrinsicParams[lCAMId].lCameraPosX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // lCameraPosY
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptExtrinsicParams[lCAMId].lCameraPosY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        // lCameraPosZ
        ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptExtrinsicParams[lCAMId].lCameraPosZ, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        ulViewID += ulViewID_Step;
    }

    return ulSectionBufLen;
}

UINT32 EAGLEK3_CalibrationCfgExportHex(
    UINT32 a_ulSectionID,
    alCOMMONK_CalibrationParams *a_ptCalibrationParams,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT32 ulViewID = 0x0000; // 0: view 0 1: view 1 2: view 2  3: view 3
    UINT32 ulViewID_Step = 0x1000;
    UINT32 ulSubFuncID = 0x0000;
    UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0, lCnt = 0;


    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    // start to export each view
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulItemID = 0x0000;

        // aeIntrinsicMatrix
        for (lCnt = 0; lCnt < EAGLEK3_M33_ELEMENT_CNT; lCnt++)
        {
            ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptCalibrationParams[lCAMId].aeIntrinsicMatrix[lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        // aeRotationMatrix
        for (lIndex = 0; lIndex < 2; lIndex++)
        {
            for (lCnt = 0; lCnt < EAGLEK3_M33_ELEMENT_CNT; lCnt++)
            {
                ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
                ulDataBufLen = 0;
                ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptCalibrationParams[lCAMId].aeRotationMatrix[lIndex][lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
                ulSectionBufLen += ulDataBufLen;

                ulItemID++;
            }
        }

        // aeTranslationMatrix
        for (lIndex = 0; lIndex < 2; lIndex++)
        {
            for (lCnt = 0; lCnt < 3; lCnt++)
            {
                ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
                ulDataBufLen = 0;
                ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptCalibrationParams[lCAMId].aeTranslationMatrix[lIndex][lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
                ulSectionBufLen += ulDataBufLen;

                ulItemID++;
            }
        }

        // aeHomographyMatrix
        for (lIndex = 0; lIndex < 2; lIndex++)
        {
            for (lCnt = 0; lCnt < EAGLEK3_M33_ELEMENT_CNT; lCnt++)
            {
                ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
                ulDataBufLen = 0;
                ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptCalibrationParams[lCAMId].aeHomographyMatrix[lIndex][lCnt], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
                ulSectionBufLen += ulDataBufLen;

                ulItemID++;
            }
        }

        ulViewID += ulViewID_Step;
    }

    return ulSectionBufLen;
}

UINT32 EAGLEK3_CfgExportHex(
    UINT32 a_ulSectionID,
    EAGLEK3_Cfg *a_ptCfg,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT32 ulViewID = 0x0000; // 0: global 1: view 0 2: view 1 3: view 2  4: view 3
    UINT32 ulViewID_Step = 0x0100;
    UINT32 ulSubFuncID = 0x0000;
    UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0;

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    // ucFactoryAutoKSwitch
    ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptCfg->ucFactoryAutoKSwitch, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // afPitchOffset
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCfg->afPitchOffset[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // afYawOffset
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCfg->afYawOffset[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // afRollOffset
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackFLOAT32(ulDataID, a_ptCfg->afRollOffset[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // alCameraPosXOffset
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg->alCameraPosXOffset[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // alCameraPosYOffset
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg->alCameraPosYOffset[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // alCameraPosZOffset
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg->alCameraPosZOffset[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // alLMBoundarySwitch
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptCfg->alLMBoundarySwitch[lCAMId], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    // AutoK
    ulDataBufLen = 0;
    ulDataBufLen += alBVCAM_FACAUTOK_CfgExport(
        a_ulSectionID,
        &a_ptCfg->tAutoK_Cfg,
        a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag
        );
    ulSectionBufLen += ulDataBufLen;


    // ManualK
    ulDataBufLen = 0;
    ulDataBufLen += MANUALK_CfgExportHex(
        a_ulSectionID,
        a_ptCfg->atMANUALK_Cfg,
        a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag
        );
    ulSectionBufLen += ulDataBufLen;

    return ulSectionBufLen;
}




UINT32 EAGLEK3_FieldDataExportHex(
    UINT32 a_ulSectionID,
    EAGLEK3_FieldData *a_ptFieldData,
    UINT8 *a_pucDataSectionBuffer
    )
{
    UINT32 ulSectionBufLen = 0;
    UINT32 ulDataBufLen = 0;
    UINT32 ulDataID = 0;
    UINT32 ulItemID = 0;
    UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
    INT32 lCAMId = 0, lIndex = 0;

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

    // atBVFPOffsetFineTuned
    for (lCAMId = 0; lCAMId < EAGLEK3_NUM_BV_CHANNEL; lCAMId++)
    {
        for (lIndex = 0; lIndex < EAGLEK3_CAMERA_FP_NUM_AUTOK; lIndex++)
        {
            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptFieldData->atBVFPOffsetFineTuned[lCAMId][lIndex].lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            ulDataID = (a_ulSectionID << 16) + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptFieldData->atBVFPOffsetFineTuned[lCAMId][lIndex].lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }
    }

    // tManualKFieldData.uwFWheeltoFChart
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.uwFWheeltoFChart, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.uwChartHoriDistance
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.uwChartHoriDistance, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.uwCharVertDistance
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.uwCharVertDistance, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FW1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FW1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FH1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FH1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FW2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FW2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FH2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FH2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FW3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FW3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FH3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FH3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FW4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FW4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FH4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FH4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FW5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FW5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FH5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FH5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FW6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FW6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.FH6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.FH6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW7
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW7, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH7
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH7, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BW8
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BW8, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tManualKFieldData.BH8
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tManualKFieldData.BH8, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;


    ///// 
    // tAutoKFieldData.tCrossmarkFeildData.uwFWheeltoFChart
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.uwFWheeltoFChart, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.uwChartHoriDistance
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.uwChartHoriDistance, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.uwCharVertDistance
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.uwCharVertDistance, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FW1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FH1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FW2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FH2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FW3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FH3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FW4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FH4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FW5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FH5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FW6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.FH6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH1
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH1, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH2
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH2, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH3
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH3, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH4
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH4, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH5
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH5, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH6
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH6, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW7
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW7, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH7
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH7, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BW8
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW8, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    // tAutoKFieldData.tCrossmarkFeildData.BH8
    ulDataID = (a_ulSectionID << 16) + ulItemID;
    ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackUINT16(ulDataID, a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH8, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulItemID++;

    /////

    // tRECK_FeildData.aucFlag

    for (lIndex = 0; lIndex < alRECK_MAX_POINT_TOTAL; lIndex++)
    {
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[lIndex], a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }

    for (lIndex = 0; lIndex < alRECK_MAX_POINT_TOTAL; lIndex++)
    {
        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[lIndex].lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;

        ulDataID = (a_ulSectionID << 16) + ulItemID;
        ulDataBufLen = 0;
        ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[lIndex].lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
        ulSectionBufLen += ulDataBufLen;

        ulItemID++;
    }
    
    return ulSectionBufLen;
}

#ifdef WIN32 // only PC use INI file
static void EAGLEK3_LoadExtrnsicParamsByINI(wchar_t * a_pwcConfigFilePath, alCAMERAINFO_ExtrinsicParams a_atCameraExtrinsicParams[EAGLEK3_NUM_BV_CHANNEL])
{
    wchar_t * pwcSectionName = L"CameraCfg";

    // BV Left
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].fPitchAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_PITCH_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].fYawAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_YAW_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].fRollAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_ROLL_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].lCameraPosX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_X_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].lCameraPosY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Y_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].lCameraPosZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Z_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_LEFT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_LEFT].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_LEFT");


    // BV Right      
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].fPitchAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_PITCH_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].fYawAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_YAW_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].fRollAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_ROLL_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].lCameraPosX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_X_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].lCameraPosY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Y_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].lCameraPosZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Z_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_RIGHT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_RIGHT].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_RIGHT");


    // BV Front
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].fPitchAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_PITCH_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].fYawAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_YAW_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].fRollAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_ROLL_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].lCameraPosX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_X_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].lCameraPosY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Y_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].lCameraPosZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Z_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_FRONT");
    a_atCameraExtrinsicParams[EAGLEK3_BV_FRONT].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_FRONT");


    // BV Back
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].fPitchAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_PITCH_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].fYawAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_YAW_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].fRollAngle = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_ROLL_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].lCameraPosX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_X_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].lCameraPosY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Y_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].lCameraPosZ = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_POS_Z_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].ulImageWidth = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_WIDTH_BV_BACK");
    a_atCameraExtrinsicParams[EAGLEK3_BV_BACK].ulImageHeight = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"CAM_HEIGHT_BV_BACK");
}


void  EAGLEK3_LoadFM_BV_CfgByINI(wchar_t * a_pwcConfigFilePath, UINT8 a_ucCamNum, alFM_v2_1_ModelCfg *a_ptFMCfg)
{
    wchar_t * pwcSectionName = L"FisheyeModelCfg";
    wchar_t awcFisheyeModelFileName[MAX_PATH];
    wchar_t awcFisheyeModelFilePath[MAX_PATH];
    wchar_t awcDrive[10];
    wchar_t awcDir[MAX_PATH];
    wchar_t awcFile[MAX_PATH];
    wchar_t awcExt[MAX_PATH];

    _wsplitpath_s(a_pwcConfigFilePath, awcDrive, 10, awcDir, MAX_PATH, awcFile, MAX_PATH, awcExt, MAX_PATH);

    // BV Left
    //  - Fisheye Model File
    alINI_GetKeyValue_CW(a_pwcConfigFilePath, pwcSectionName, L"FM_v2_PARAM_FILE_BV_LEFT", awcFisheyeModelFileName, MAX_PATH);
    _wmakepath_s(awcFisheyeModelFilePath, MAX_PATH, awcDrive, awcDir, awcFisheyeModelFileName, L"");

    //  - Import the specified fisheye model to BV left camera
    alFM_v2_1_LoadUserCfgByINI(awcFisheyeModelFilePath, &a_ptFMCfg[EAGLEK3_BV_LEFT]);


    // BV Right
    //  - Fisheye Model File
    alINI_GetKeyValue_CW(a_pwcConfigFilePath, pwcSectionName, L"FM_v2_PARAM_FILE_BV_RIGHT", awcFisheyeModelFileName, MAX_PATH);
    _wmakepath_s(awcFisheyeModelFilePath, MAX_PATH, awcDrive, awcDir, awcFisheyeModelFileName, L"");

    //  - Import the specified fisheye model to BV right camera
    alFM_v2_1_LoadUserCfgByINI(awcFisheyeModelFilePath, &a_ptFMCfg[EAGLEK3_BV_RIGHT]);

    // BV Front
    //  - Fisheye Model File
    alINI_GetKeyValue_CW(a_pwcConfigFilePath, pwcSectionName, L"FM_v2_PARAM_FILE_BV_FRONT", awcFisheyeModelFileName, MAX_PATH);
    _wmakepath_s(awcFisheyeModelFilePath, MAX_PATH, awcDrive, awcDir, awcFisheyeModelFileName, L"");

    //  - Import the specified fisheye model to BV front camera
    alFM_v2_1_LoadUserCfgByINI(awcFisheyeModelFilePath, &a_ptFMCfg[EAGLEK3_BV_FRONT]);

    // BV Back
    //  - Fisheye Model File
    alINI_GetKeyValue_CW(a_pwcConfigFilePath, pwcSectionName, L"FM_v2_PARAM_FILE_BV_BACK", awcFisheyeModelFileName, MAX_PATH);
    _wmakepath_s(awcFisheyeModelFilePath, MAX_PATH, awcDrive, awcDir, awcFisheyeModelFileName, L"");

    //  - Import the specified fisheye model to BV back camera
    alFM_v2_1_LoadUserCfgByINI(awcFisheyeModelFilePath, &a_ptFMCfg[EAGLEK3_BV_BACK]);
}

static void EAGLEK3_LoadCalibrationParamsByINI(wchar_t * a_pwcConfigFilePath, alCOMMONK_CalibrationParams a_atCalibrationParams[EAGLEK3_NUM_BV_CHANNEL])
{
    wchar_t * pwcSectionName = L"DefaultM33Cfg";

    // BV Left
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM11_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM12_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM13_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM21_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM22_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM23_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM31_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM32_W2I");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM33_W2I");

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM11_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM12_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM13_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM21_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM22_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM23_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM31_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM32_I2W");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeHomographyMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"LM33_I2W");

    // BV Right
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM11_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM12_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM13_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM21_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM22_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM23_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM31_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM32_W2I");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM33_W2I");

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM11_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM12_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM13_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM21_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM22_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM23_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM31_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM32_I2W");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeHomographyMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"RM33_I2W");

    // BV Front
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM11_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM12_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM13_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM21_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM22_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM23_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM31_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM32_W2I");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM33_W2I");

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM11_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM12_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM13_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM21_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM22_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM23_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM31_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM32_I2W");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeHomographyMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"FM33_I2W");

    // BV Back
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM11_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM12_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM13_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM21_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM22_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM23_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM31_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM32_W2I");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM33_W2I");

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM11_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM12_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM13_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM21_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM22_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM23_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM31_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM32_I2W");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeHomographyMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"BM33_I2W");


    pwcSectionName = L"CameraCfg";

    // BV Left

    // matrix for bv transform
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_BV2RC_BV_LEFT");

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeRotationMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_RC2BV_BV_LEFT");

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_BV2RC_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_BV2RC_BV_LEFT");

    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_RC2BV_BV_LEFT");
    a_atCalibrationParams[EAGLEK3_BV_LEFT].aeTranslationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_RC2BV_BV_LEFT");

    // BV Right      

    // matrix for bv transform
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_BV2RC_BV_RIGHT");

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeRotationMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_RC2BV_BV_RIGHT");

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_BV2RC_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_BV2RC_BV_RIGHT");

    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_RC2BV_BV_RIGHT");
    a_atCalibrationParams[EAGLEK3_BV_RIGHT].aeTranslationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_RC2BV_BV_RIGHT");

    // BV Front

    // matrix for bv transform
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_BV2RC_BV_FRONT");

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeRotationMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_RC2BV_BV_FRONT");

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_BV2RC_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_BV2RC_BV_FRONT");

    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_RC2BV_BV_FRONT");
    a_atCalibrationParams[EAGLEK3_BV_FRONT].aeTranslationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_RC2BV_BV_FRONT");

    // BV Back

    // matrix for bv transform
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[0][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_BV2RC_BV_BACK");

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX11_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX12_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX13_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][3] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX21_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][4] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX22_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][5] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX23_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][6] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX31_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][7] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX32_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeRotationMatrix[1][8] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_RMATRIX33_RC2BV_BV_BACK");

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[0][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[0][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_BV2RC_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[0][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_BV2RC_BV_BACK");

    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[1][0] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX1_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[1][1] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX2_RC2BV_BV_BACK");
    a_atCalibrationParams[EAGLEK3_BV_BACK].aeTranslationMatrix[1][2] = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, L"CAM_TMATRIX3_RC2BV_BV_BACK");
}


void EAGLEK3_LoadUserCfgByINI(wchar_t * a_pwcConfigFileName, EAGLEK3_Cfg *a_ptCfg)
{
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    wchar_t * pwcSectionName = L"CommonCfg";
#ifdef _DEBUG
    struct _stat64i32 tFileStat;
#endif

    // wcscpy_s(awcConfigFilePath, MAX_PATH, g_EAGLEK3_awcWorkingPath);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 浪琩郎琌
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Factory AutoK Switch 0: OFF 1:ON
    a_ptCfg->ucFactoryAutoKSwitch = (UINT8)alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"FACTORY_AUTOK_SWITCH");

    // for LM LEFT
    a_ptCfg->alLMBoundarySwitch[alCAMERAINFO_BV_LEFT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_BV_LEFT_LM_BOUNDARY");
    a_ptCfg->afPitchOffset[alCAMERAINFO_BV_LEFT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_PITCH_BV_LEFT_OFFSET");
    a_ptCfg->afYawOffset[alCAMERAINFO_BV_LEFT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_YAW_BV_LEFT_OFFSET");
    a_ptCfg->afRollOffset[alCAMERAINFO_BV_LEFT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_ROLL_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosXOffset[alCAMERAINFO_BV_LEFT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_X_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosYOffset[alCAMERAINFO_BV_LEFT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Y_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosZOffset[alCAMERAINFO_BV_LEFT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Z_BV_LEFT_OFFSET");

    // for LM RIGHT
    a_ptCfg->alLMBoundarySwitch[alCAMERAINFO_BV_RIGHT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_BV_LEFT_LM_BOUNDARY");
    a_ptCfg->afPitchOffset[alCAMERAINFO_BV_RIGHT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_PITCH_BV_LEFT_OFFSET");
    a_ptCfg->afYawOffset[alCAMERAINFO_BV_RIGHT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_YAW_BV_LEFT_OFFSET");
    a_ptCfg->afRollOffset[alCAMERAINFO_BV_RIGHT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_ROLL_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosXOffset[alCAMERAINFO_BV_RIGHT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_X_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosYOffset[alCAMERAINFO_BV_RIGHT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Y_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosZOffset[alCAMERAINFO_BV_RIGHT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Z_BV_LEFT_OFFSET");

    // for LM FRONT
    a_ptCfg->alLMBoundarySwitch[alCAMERAINFO_BV_FRONT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_BV_LEFT_LM_BOUNDARY");
    a_ptCfg->afPitchOffset[alCAMERAINFO_BV_FRONT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_PITCH_BV_LEFT_OFFSET");
    a_ptCfg->afYawOffset[alCAMERAINFO_BV_FRONT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_YAW_BV_LEFT_OFFSET");
    a_ptCfg->afRollOffset[alCAMERAINFO_BV_FRONT] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_ROLL_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosXOffset[alCAMERAINFO_BV_FRONT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_X_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosYOffset[alCAMERAINFO_BV_FRONT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Y_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosZOffset[alCAMERAINFO_BV_FRONT] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Z_BV_LEFT_OFFSET");

    // for LM BACK
    a_ptCfg->alLMBoundarySwitch[alCAMERAINFO_BV_BACK] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_BV_LEFT_LM_BOUNDARY");
    a_ptCfg->afPitchOffset[alCAMERAINFO_BV_BACK] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_PITCH_BV_LEFT_OFFSET");
    a_ptCfg->afYawOffset[alCAMERAINFO_BV_BACK] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_YAW_BV_LEFT_OFFSET");
    a_ptCfg->afRollOffset[alCAMERAINFO_BV_BACK] = (FLOAT32)alINI_GetKeyValue_FLOAT64W(a_pwcConfigFileName, pwcSectionName, L"CAM_ROLL_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosXOffset[alCAMERAINFO_BV_BACK] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_X_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosYOffset[alCAMERAINFO_BV_BACK] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Y_BV_LEFT_OFFSET");
    a_ptCfg->alCameraPosZOffset[alCAMERAINFO_BV_BACK] = alINI_GetKeyValue_INT32W(a_pwcConfigFileName, pwcSectionName, L"CAM_POS_Z_BV_LEFT_OFFSET");


    // load MANUALK Cfg
    MANUALK_CfgImport(awcConfigFilePath, a_ptCfg->atMANUALK_Cfg);

    // load Extrnsic Params Cfg
    EAGLEK3_LoadExtrnsicParamsByINI(awcConfigFilePath, a_ptCfg->atCameraExtrinsicParams);

    // Load M33 and RT Matrix Cfg
    EAGLEK3_LoadCalibrationParamsByINI(awcConfigFilePath, a_ptCfg->atCalibrationParams);

    // Load alBVCAM FACAUTOK Cfg
    alBVCAM_FACAUTOK_CfgImportINI(awcConfigFilePath, &a_ptCfg->tAutoK_Cfg);
}


void EAGLEK3_LoadFieldDataByINI(wchar_t * pwcIniFileNameManualK, wchar_t * pwcIniFileNameAutoK, wchar_t * pwcIniFileNameFineTune, EAGLEK3_FieldData *a_ptFeildData)
{
    alERROR_ClearErrorCode();

    // 更 MANUALK タ初把计 : from ini file    
    if (MANUALK_LoadFeildDataByINIFile(pwcIniFileNameManualK, &a_ptFeildData->tManualKFieldData) == FALSE)
    {
         alERROR_SetErrorCode(EAGLEK3_ERROR_CAMK_K_FIELD_FILE_NOT_FOUND);
        assert(0);  // load fail
    }

    // 更 AUTOK タ初把计 : from ini file
    alBVCAM_FACAUTOK_LoadFeildDataByINI(pwcIniFileNameAutoK, &a_ptFeildData->tAutoKFieldData);

    // 更 Fine-tuned 初把计 : from ini file    

}

#endif

void EAGLEK3_FieldDataImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, EAGLEK3_FieldData *a_ptFieldData)
{
    UINT32 ulDataIndex = 0;

    ulDataIndex = a_ulDataID & 0xFFFF;
    switch (ulDataIndex)
    {
    case 0x0000:    // atBVFPOffsetFineTuned[0][0].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0001:    // atBVFPOffsetFineTuned[0][0].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0002:    // atBVFPOffsetFineTuned[0][1].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0003:    // atBVFPOffsetFineTuned[0][1].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0004:    // atBVFPOffsetFineTuned[0][2].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0005:    // atBVFPOffsetFineTuned[0][2].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0006:    // atBVFPOffsetFineTuned[0][3].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0007:    // atBVFPOffsetFineTuned[0][3].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0008:    // atBVFPOffsetFineTuned[0][4].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0009:    // atBVFPOffsetFineTuned[0][4].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000A:    // atBVFPOffsetFineTuned[0][5].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000B:    // atBVFPOffsetFineTuned[0][5].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000C:    // atBVFPOffsetFineTuned[0][6].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000D:    // atBVFPOffsetFineTuned[0][6].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000E:    // atBVFPOffsetFineTuned[0][7].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x000F:    // atBVFPOffsetFineTuned[0][7].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[0][7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0010:    // atBVFPOffsetFineTuned[1][0].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0011:    // atBVFPOffsetFineTuned[1][0].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0012:    // atBVFPOffsetFineTuned[1][1].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0013:    // atBVFPOffsetFineTuned[1][1].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0014:    // atBVFPOffsetFineTuned[1][2].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0015:    // atBVFPOffsetFineTuned[1][2].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0016:    // atBVFPOffsetFineTuned[1][3].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0017:    // atBVFPOffsetFineTuned[1][3].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0018:    // atBVFPOffsetFineTuned[1][4].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0019:    // atBVFPOffsetFineTuned[1][4].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001A:    // atBVFPOffsetFineTuned[1][5].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001B:    // atBVFPOffsetFineTuned[1][5].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001C:    // atBVFPOffsetFineTuned[1][6].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001D:    // atBVFPOffsetFineTuned[1][6].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001E:    // atBVFPOffsetFineTuned[1][7].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x001F:    // atBVFPOffsetFineTuned[1][7].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[1][7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0020:    // atBVFPOffsetFineTuned[2][0].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0021:    // atBVFPOffsetFineTuned[2][0].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0022:    // atBVFPOffsetFineTuned[2][1].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0023:    // atBVFPOffsetFineTuned[2][1].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0024:    // atBVFPOffsetFineTuned[2][2].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0025:    // atBVFPOffsetFineTuned[2][2].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0026:    // atBVFPOffsetFineTuned[2][3].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0027:    // atBVFPOffsetFineTuned[2][3].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0028:    // atBVFPOffsetFineTuned[2][4].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0029:    // atBVFPOffsetFineTuned[2][4].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002A:    // atBVFPOffsetFineTuned[2][5].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002B:    // atBVFPOffsetFineTuned[2][5].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002C:    // atBVFPOffsetFineTuned[2][6].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002D:    // atBVFPOffsetFineTuned[2][6].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002E:    // atBVFPOffsetFineTuned[2][7].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x002F:    // atBVFPOffsetFineTuned[2][7].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[2][7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0030:    // atBVFPOffsetFineTuned[3][0].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0031:    // atBVFPOffsetFineTuned[3][0].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0032:    // atBVFPOffsetFineTuned[3][1].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0033:    // atBVFPOffsetFineTuned[3][1].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0034:    // atBVFPOffsetFineTuned[3][2].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0035:    // atBVFPOffsetFineTuned[3][2].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0036:    // atBVFPOffsetFineTuned[3][3].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0037:    // atBVFPOffsetFineTuned[3][3].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0038:    // atBVFPOffsetFineTuned[3][4].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0039:    // atBVFPOffsetFineTuned[3][4].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003A:    // atBVFPOffsetFineTuned[3][5].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003B:    // atBVFPOffsetFineTuned[3][5].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003C:    // atBVFPOffsetFineTuned[3][6].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003D:    // atBVFPOffsetFineTuned[3][6].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003E:    // atBVFPOffsetFineTuned[3][7].lX
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x003F:    // atBVFPOffsetFineTuned[3][7].lY
    {
        a_ptFieldData->atBVFPOffsetFineTuned[3][7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0040:    // tManualKFieldData.uwFWheeltoFChart
    {
        a_ptFieldData->tManualKFieldData.uwFWheeltoFChart = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0041:    // tManualKFieldData.uwChartHoriDistance
    {
        a_ptFieldData->tManualKFieldData.uwChartHoriDistance = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0042:    // tManualKFieldData.uwCharVertDistance
    {
        a_ptFieldData->tManualKFieldData.uwCharVertDistance = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0043:    // tManualKFieldData.FW1
    {
        a_ptFieldData->tManualKFieldData.FW1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0044:    // tManualKFieldData.FH1
    {
        a_ptFieldData->tManualKFieldData.FH1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0045:    // tManualKFieldData.FW2
    {
        a_ptFieldData->tManualKFieldData.FW2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0046:    // tManualKFieldData.FH2
    {
        a_ptFieldData->tManualKFieldData.FH2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0047:    // tManualKFieldData.FW3
    {
        a_ptFieldData->tManualKFieldData.FW3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0048:    // tManualKFieldData.FH3
    {
        a_ptFieldData->tManualKFieldData.FH3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0049:    // tManualKFieldData.FW4
    {
        a_ptFieldData->tManualKFieldData.FW4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004A:    // tManualKFieldData.FH4
    {
        a_ptFieldData->tManualKFieldData.FH4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004B:    // tManualKFieldData.FW5
    {
        a_ptFieldData->tManualKFieldData.FW5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004C:    // tManualKFieldData.FH5
    {
        a_ptFieldData->tManualKFieldData.FH5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004D:    // tManualKFieldData.FW6
    {
        a_ptFieldData->tManualKFieldData.FW6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004E:    // tManualKFieldData.FH6
    {
        a_ptFieldData->tManualKFieldData.FH6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x004F:    // tManualKFieldData.BW1
    {
        a_ptFieldData->tManualKFieldData.BW1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0050:    // tManualKFieldData.BH1
    {
        a_ptFieldData->tManualKFieldData.BH1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0051:    // tManualKFieldData.BW2
    {
        a_ptFieldData->tManualKFieldData.BW2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0052:    // tManualKFieldData.BH2
    {
        a_ptFieldData->tManualKFieldData.BH2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0053:    // tManualKFieldData.BW3
    {
        a_ptFieldData->tManualKFieldData.BW3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0054:    // tManualKFieldData.BH3
    {
        a_ptFieldData->tManualKFieldData.BH3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0055:    // tManualKFieldData.BW4
    {
        a_ptFieldData->tManualKFieldData.BW4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0056:    // tManualKFieldData.BH4
    {
        a_ptFieldData->tManualKFieldData.BH4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0057:    // tManualKFieldData.BW5
    {
        a_ptFieldData->tManualKFieldData.BW5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0058:    // tManualKFieldData.BH5
    {
        a_ptFieldData->tManualKFieldData.BH5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0059:    // tManualKFieldData.BW6
    {
        a_ptFieldData->tManualKFieldData.BW6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005A:    // tManualKFieldData.BH6
    {
        a_ptFieldData->tManualKFieldData.BH6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005B:    // tManualKFieldData.BW7
    {
        a_ptFieldData->tManualKFieldData.BW7 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005C:    // tManualKFieldData.BH7
    {
        a_ptFieldData->tManualKFieldData.BH7 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005D:    // tManualKFieldData.BW8
    {
        a_ptFieldData->tManualKFieldData.BW8 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x005E:    // tManualKFieldData.BH8
    {
        a_ptFieldData->tManualKFieldData.BH8 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x005F:    // tAutoKFieldData.tCrossmarkFeildData.uwFWheeltoFChart
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.uwFWheeltoFChart = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0060:    // tAutoKFieldData.tCrossmarkFeildData.uwChartHoriDistance
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.uwChartHoriDistance = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0061:    // tAutoKFieldData.tCrossmarkFeildData.uwCharVertDistance
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.uwCharVertDistance = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0062:    // tAutoKFieldData.tCrossmarkFeildData.FW1
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0063:    // tAutoKFieldData.tCrossmarkFeildData.FH1
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0064:    // tAutoKFieldData.tCrossmarkFeildData.FW2
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0065:    // tAutoKFieldData.tCrossmarkFeildData.FH2
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0066:    // tAutoKFieldData.tCrossmarkFeildData.FW3
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0067:    // tAutoKFieldData.tCrossmarkFeildData.FH3
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0068:    // tAutoKFieldData.tCrossmarkFeildData.FW4
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0069:    // tAutoKFieldData.tCrossmarkFeildData.FH4
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006A:    // tAutoKFieldData.tCrossmarkFeildData.FW5
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006B:    // tAutoKFieldData.tCrossmarkFeildData.FH5
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006C:    // tAutoKFieldData.tCrossmarkFeildData.FW6
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FW6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006D:    // tAutoKFieldData.tCrossmarkFeildData.FH6
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.FH6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006E:    // tAutoKFieldData.tCrossmarkFeildData.BW1
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x006F:    // tAutoKFieldData.tCrossmarkFeildData.BH1
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH1 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0070:    // tAutoKFieldData.tCrossmarkFeildData.BW2
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0071:    // tAutoKFieldData.tCrossmarkFeildData.BH2
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH2 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0072:    // tAutoKFieldData.tCrossmarkFeildData.BW3
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0073:    // tAutoKFieldData.tCrossmarkFeildData.BH3
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH3 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0074:    // tAutoKFieldData.tCrossmarkFeildData.BW4
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0075:    // tAutoKFieldData.tCrossmarkFeildData.BH4
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH4 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0076:    // tAutoKFieldData.tCrossmarkFeildData.BW5
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0077:    // tAutoKFieldData.tCrossmarkFeildData.BH5
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH5 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0078:    // tAutoKFieldData.tCrossmarkFeildData.BW6
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0079:    // tAutoKFieldData.tCrossmarkFeildData.BH6
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH6 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007A:    // tAutoKFieldData.tCrossmarkFeildData.BW7
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW7 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007B:    // tAutoKFieldData.tCrossmarkFeildData.BH7
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH7 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007C:    // tAutoKFieldData.tCrossmarkFeildData.BW8
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BW8 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007D:    // tAutoKFieldData.tCrossmarkFeildData.BH8
    {
        a_ptFieldData->tAutoKFieldData.tCrossmarkFeildData.BH8 = alHEXDATA_UnpackUINT16(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007E:    // tRECK_FeildData.aucFlag[0]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x007F:    // tRECK_FeildData.aucFlag[1]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0080:    // tRECK_FeildData.aucFlag[2]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0081:    // tRECK_FeildData.aucFlag[3]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0082:    // tRECK_FeildData.aucFlag[4]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[4] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0083:    // tRECK_FeildData.aucFlag[5]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[5] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0084:    // tRECK_FeildData.aucFlag[6]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[6] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0085:    // tRECK_FeildData.aucFlag[7]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[7] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0086:    // tRECK_FeildData.aucFlag[8]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[8] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0087:    // tRECK_FeildData.aucFlag[9]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[9] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0088:    // tRECK_FeildData.aucFlag[10]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[10] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0089:    // tRECK_FeildData.aucFlag[11]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[11] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x008A:    // tRECK_FeildData.aucFlag[12]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[12] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008B:    // tRECK_FeildData.aucFlag[13]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[13] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x008C:    // tRECK_FeildData.aucFlag[14]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[14] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008D:    // tRECK_FeildData.aucFlag[15]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[15] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x008E:    // tRECK_FeildData.aucFlag[16]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[16] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x008F:    // tRECK_FeildData.aucFlag[17]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[17] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0090:    // tRECK_FeildData.aucFlag[18]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[18] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0091:    // tRECK_FeildData.aucFlag[19]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[19] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0092:    // tRECK_FeildData.aucFlag[20]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[20] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0093:    // tRECK_FeildData.aucFlag[21]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[21] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0094:    // tRECK_FeildData.aucFlag[22]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[22] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0095:    // tRECK_FeildData.aucFlag[23]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[23] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0096:    // tRECK_FeildData.aucFlag[24]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[24] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0097:    // tRECK_FeildData.aucFlag[25]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[25] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x0098:    // tRECK_FeildData.aucFlag[26]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[26] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0099:    // tRECK_FeildData.aucFlag[27]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[27] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x009A:    // tRECK_FeildData.aucFlag[28]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[28] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009B:    // tRECK_FeildData.aucFlag[29]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[29] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x009C:    // tRECK_FeildData.aucFlag[30]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[30] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009D:    // tRECK_FeildData.aucFlag[31]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[31] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x009E:    // tRECK_FeildData.aucFlag[32]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[32] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x009F:    // tRECK_FeildData.aucFlag[33]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[33] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00A0:    // tRECK_FeildData.aucFlag[34]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[34] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A1:    // tRECK_FeildData.aucFlag[35]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[35] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00A2:    // tRECK_FeildData.aucFlag[36]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[36] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A3:    // tRECK_FeildData.aucFlag[37]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[37] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00A4:    // tRECK_FeildData.aucFlag[38]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[38] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A5:    // tRECK_FeildData.aucFlag[39]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[39] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00A6:    // tRECK_FeildData.aucFlag[40]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[40] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A7:    // tRECK_FeildData.aucFlag[41]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[41] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00A8:    // tRECK_FeildData.aucFlag[42]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[42] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00A9:    // tRECK_FeildData.aucFlag[43]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[43] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00AA:    // tRECK_FeildData.aucFlag[44]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[44] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AB:    // tRECK_FeildData.aucFlag[45]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[45] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00AC:    // tRECK_FeildData.aucFlag[46]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[46] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AD:    // tRECK_FeildData.aucFlag[47]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[47] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x00AE:    // tRECK_FeildData.aucFlag[48]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[48] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00AF:    // tRECK_FeildData.aucFlag[49]
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.aucFlag[49] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B0:    // tRECK_FeildData.atIdealFPRecK[0].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B1:    // tRECK_FeildData.atIdealFPRecK[0].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B2:    // tRECK_FeildData.atIdealFPRecK[1].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B3:    // tRECK_FeildData.atIdealFPRecK[1].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B4:    // tRECK_FeildData.atIdealFPRecK[2].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B5:    // tRECK_FeildData.atIdealFPRecK[2].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B6:    // tRECK_FeildData.atIdealFPRecK[3].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B7:    // tRECK_FeildData.atIdealFPRecK[3].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B8:    // tRECK_FeildData.atIdealFPRecK[4].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00B9:    // tRECK_FeildData.atIdealFPRecK[4].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BA:    // tRECK_FeildData.atIdealFPRecK[5].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BB:    // tRECK_FeildData.atIdealFPRecK[5].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BC:    // tRECK_FeildData.atIdealFPRecK[6].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BD:    // tRECK_FeildData.atIdealFPRecK[6].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BE:    // tRECK_FeildData.atIdealFPRecK[7].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00BF:    // tRECK_FeildData.atIdealFPRecK[7].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C0:    // tRECK_FeildData.atIdealFPRecK[8].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[8].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C1:    // tRECK_FeildData.atIdealFPRecK[8].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[8].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C2:    // tRECK_FeildData.atIdealFPRecK[9].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[9].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C3:    // tRECK_FeildData.atIdealFPRecK[9].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[9].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C4:    // tRECK_FeildData.atIdealFPRecK[10].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[10].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C5:    // tRECK_FeildData.atIdealFPRecK[10].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[10].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C6:    // tRECK_FeildData.atIdealFPRecK[11].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[11].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C7:    // tRECK_FeildData.atIdealFPRecK[11].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[11].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C8:    // tRECK_FeildData.atIdealFPRecK[12].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[12].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00C9:    // tRECK_FeildData.atIdealFPRecK[12].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[12].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00CA:    // tRECK_FeildData.atIdealFPRecK[13].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[13].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00CB:    // tRECK_FeildData.atIdealFPRecK[13].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[13].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00CC:    // tRECK_FeildData.atIdealFPRecK[14].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[14].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00CD:    // tRECK_FeildData.atIdealFPRecK[14].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[14].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00CE:    // tRECK_FeildData.atIdealFPRecK[15].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[15].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00CF:    // tRECK_FeildData.atIdealFPRecK[15].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[15].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D0:    // tRECK_FeildData.atIdealFPRecK[16].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[16].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D1:    // tRECK_FeildData.atIdealFPRecK[16].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[16].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D2:    // tRECK_FeildData.atIdealFPRecK[17].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[17].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D3:    // tRECK_FeildData.atIdealFPRecK[17].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[17].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D4:    // tRECK_FeildData.atIdealFPRecK[18].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[18].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D5:    // tRECK_FeildData.atIdealFPRecK[18].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[18].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D6:    // tRECK_FeildData.atIdealFPRecK[19].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[19].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D7:    // tRECK_FeildData.atIdealFPRecK[19].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[19].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D8:    // tRECK_FeildData.atIdealFPRecK[20].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[20].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00D9:    // tRECK_FeildData.atIdealFPRecK[20].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[20].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00DA:    // tRECK_FeildData.atIdealFPRecK[21].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[21].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00DB:    // tRECK_FeildData.atIdealFPRecK[21].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[21].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00DC:    // tRECK_FeildData.atIdealFPRecK[22].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[22].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00DD:    // tRECK_FeildData.atIdealFPRecK[22].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[22].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00DE:    // tRECK_FeildData.atIdealFPRecK[23].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[23].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00DF:    // tRECK_FeildData.atIdealFPRecK[23].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[23].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E0:    // tRECK_FeildData.atIdealFPRecK[24].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[24].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E1:    // tRECK_FeildData.atIdealFPRecK[24].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[24].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E2:    // tRECK_FeildData.atIdealFPRecK[25].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[25].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E3:    // tRECK_FeildData.atIdealFPRecK[25].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[25].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E4:    // tRECK_FeildData.atIdealFPRecK[26].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[26].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E5:    // tRECK_FeildData.atIdealFPRecK[26].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[26].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E6:    // tRECK_FeildData.atIdealFPRecK[27].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[27].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E7:    // tRECK_FeildData.atIdealFPRecK[27].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[27].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E8:    // tRECK_FeildData.atIdealFPRecK[28].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[28].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00E9:    // tRECK_FeildData.atIdealFPRecK[28].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[28].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00EA:    // tRECK_FeildData.atIdealFPRecK[29].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[29].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00EB:    // tRECK_FeildData.atIdealFPRecK[29].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[29].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00EC:    // tRECK_FeildData.atIdealFPRecK[30].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[30].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00ED:    // tRECK_FeildData.atIdealFPRecK[30].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[30].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00EE:    // tRECK_FeildData.atIdealFPRecK[31].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[31].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00EF:    // tRECK_FeildData.atIdealFPRecK[31].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[31].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F0:    // tRECK_FeildData.atIdealFPRecK[32].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[32].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F1:    // tRECK_FeildData.atIdealFPRecK[32].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[32].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F2:    // tRECK_FeildData.atIdealFPRecK[33].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[33].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F3:    // tRECK_FeildData.atIdealFPRecK[33].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[33].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F4:    // tRECK_FeildData.atIdealFPRecK[34].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[34].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F5:    // tRECK_FeildData.atIdealFPRecK[34].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[34].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F6:    // tRECK_FeildData.atIdealFPRecK[35].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[35].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F7:    // tRECK_FeildData.atIdealFPRecK[35].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[35].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F8:    // tRECK_FeildData.atIdealFPRecK[36].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[36].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00F9:    // tRECK_FeildData.atIdealFPRecK[36].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[36].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00FA:    // tRECK_FeildData.atIdealFPRecK[37].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[37].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00FB:    // tRECK_FeildData.atIdealFPRecK[37].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[37].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00FC:    // tRECK_FeildData.atIdealFPRecK[38].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[38].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00FD:    // tRECK_FeildData.atIdealFPRecK[0].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[38].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00FE:    // tRECK_FeildData.atIdealFPRecK[39].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[39].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x00FF:    // tRECK_FeildData.atIdealFPRecK[39].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[39].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0100:    // tRECK_FeildData.atIdealFPRecK[40].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[40].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0101:    // tRECK_FeildData.atIdealFPRecK[40].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[40].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0102:    // tRECK_FeildData.atIdealFPRecK[41].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[41].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0103:    // tRECK_FeildData.atIdealFPRecK[41].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[41].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0104:    // tRECK_FeildData.atIdealFPRecK[42].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[42].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0105:    // tRECK_FeildData.atIdealFPRecK[42].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[42].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0106:    // tRECK_FeildData.atIdealFPRecK[43].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[43].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0107:    // tRECK_FeildData.atIdealFPRecK[43].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[43].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0108:    // tRECK_FeildData.atIdealFPRecK[44].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[44].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0109:    // tRECK_FeildData.atIdealFPRecK[44].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[44].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x010A:    // tRECK_FeildData.atIdealFPRecK[45].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[45].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x010B:    // tRECK_FeildData.atIdealFPRecK[45].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[45].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x010C:    // tRECK_FeildData.atIdealFPRecK[46].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[46].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x010D:    // tRECK_FeildData.atIdealFPRecK[46].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[46].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x010E:    // tRECK_FeildData.atIdealFPRecK[47].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[47].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x010F:    // tRECK_FeildData.atIdealFPRecK[47].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[47].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0110:    // tRECK_FeildData.atIdealFPRecK[48].lX
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[48].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0111:    // tRECK_FeildData.atIdealFPRecK[48].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[48].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0112:    // tRECK_FeildData.atIdealFPRecK[49].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[49].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
    case 0x0113:    // tRECK_FeildData.atIdealFPRecK[49].lY
    {
        a_ptFieldData->tAutoKFieldData.tRECK_FeildData.atIdealFPRecK[49].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;
   
    default:    // default
    {
        // error
    }
    break;
    }
}
