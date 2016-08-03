
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
  *  \addtogroup CameraCal
  *  @{
  */


    /*
    \brief Defalut calibration field setting. These setting are not included in ECU config files.
    These data only used when ini file is not existed.
    */
#define SIM_DEFAULT_CHART_SETTING_FILE              L"CalSettingFile.ini"  // 校正場地設定檔
#define SIM_DEFAULT_CHART_SETTING_FINE_TUNE_FILE    L"CalSettingFineTune_MV_MC.ini"  // 校正場地設定檔
#define SIM_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST       920     // 預設前輪中心至車頭距離
#define SIM_DEFAULT_CHART_HORI_DIST                 1860    // 左右 Chart 內側間距
#define SIM_DEFAULT_CHART_VERT_DIST                 4840    // 前後 Chart 內側間距
    /*

    SIM_DEFAULT_CHART_HORI_DIST
    ______ ←───→ ______
    FW5|＋ ＋ |FW3    FW4| ＋ ＋| FW6
    |   ＋ |          | ＋   |
    |______|(左前)    |______|(右前)
    ↑ FW1 ↑          FW2
    SIM_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST    ↓     ∣
    ----------------------∣
    (車輪中心)                 ∣SIM_DEFAULT_CHART_VERT_DIST
    ∣
    BW2 ∣          BW1
    ______ ↓         ______
    |   ＋ |(左後)    | ＋   |(右後)
    BW6|＋ ＋ |BW4    BW3| ＋ ＋|BW5
    |______|          |______|

    */
#define SIM_DEFAULT_FW1                   600
#define SIM_DEFAULT_FH1                   450
#define SIM_DEFAULT_FW2                   600
#define SIM_DEFAULT_FH2                   450
#define SIM_DEFAULT_FW3                   600
#define SIM_DEFAULT_FH3                   1350
#define SIM_DEFAULT_FW4                   600
#define SIM_DEFAULT_FH4                   1350
#define SIM_DEFAULT_FW5                   1500 // 1600
#define SIM_DEFAULT_FH5                   1200
#define SIM_DEFAULT_FW6                   1500 // 1600
#define SIM_DEFAULT_FH6                   1200
#define SIM_DEFAULT_BW1                   750
#define SIM_DEFAULT_BH1                   450
#define SIM_DEFAULT_BW2                   750
#define SIM_DEFAULT_BH2                   450
#define SIM_DEFAULT_BW3                   750
#define SIM_DEFAULT_BH3                   1350
#define SIM_DEFAULT_BW4                   750
#define SIM_DEFAULT_BH4                   1350
#define SIM_DEFAULT_BW5                   1500
#define SIM_DEFAULT_BH5                   900
#define SIM_DEFAULT_BW6                   1500
#define SIM_DEFAULT_BH6                   900

#define SIM_DEFAULT_BW7                   1500
#define SIM_DEFAULT_BH7                   0
#define SIM_DEFAULT_BW8                   1500
#define SIM_DEFAULT_BH8                   0


    /*
    \brief To load calibration field data from ini file. 
    \param pwcIniFilePath [IN] Indicate the ini file.
    \return Return TRUE if the data loading is successful, and FALSE vice verse.
    */
#ifdef WIN32
    BOOL MANUALK_LoadFeildDataByINIFile(wchar_t * pwcIniFileName, alMANUALK_ChartCrossPointSet *a_ptFeildData);
#endif

    /*
    \brief To load calibration field data from Default setting
    \param a_ptFeildData [INOUT] Feild Data
    \return Return TRUE if the data loading is successful, and FALSE vice verse.
    */
    BOOL MANUALK_LoadFeildDataByDefault(alMANUALK_ChartCrossPointSet *a_ptFeildData);



/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
