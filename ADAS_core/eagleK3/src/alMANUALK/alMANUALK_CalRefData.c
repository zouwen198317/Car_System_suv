
#include "alMANUALK/alMANUALK.h"
#include "alMANUALK/alMANUALK_CalRefData.h"
#ifdef WIN32
#include "alINI.h"
#endif
#include <stdio.h>

#ifdef WIN32
#include <sys/stat.h>
#endif

#ifdef WIN32
BOOL MANUALK_LoadFeildDataByINIFile(wchar_t * pwcIniFileName, alMANUALK_ChartCrossPointSet *a_ptFeildData)
{
    wchar_t pwcIniFilePath[MAX_PATH];
    struct _stat64i32 tFileStat;

    wcscpy_s(pwcIniFilePath, MAX_PATH, pwcIniFileName);

    if (_wstat(pwcIniFilePath, &tFileStat) != 0) return FALSE;

    a_ptFeildData->uwFWheeltoFChart = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"F_WHEEL_TO_HEAD_DIST");
    a_ptFeildData->uwChartHoriDistance = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"CHART_HORI_DIST");
    a_ptFeildData->uwCharVertDistance = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"CHART_VERT_DIST");

    a_ptFeildData->FW1 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FW1");
    a_ptFeildData->FH1 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FH1");;
    a_ptFeildData->FW2 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FW2");;
    a_ptFeildData->FH2 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FH2");;
    a_ptFeildData->FW3 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FW3");;
    a_ptFeildData->FH3 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FH3");;
    a_ptFeildData->FW4 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FW4");;
    a_ptFeildData->FH4 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FH4");;
    a_ptFeildData->FW5 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FW5");;
    a_ptFeildData->FH5 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FH5");;
    a_ptFeildData->FW6 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FW6");;
    a_ptFeildData->FH6 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"FH6");;
    a_ptFeildData->BW1 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW1");;
    a_ptFeildData->BH1 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH1");;
    a_ptFeildData->BW2 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW2");;
    a_ptFeildData->BH2 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH2");;
    a_ptFeildData->BW3 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW3");;
    a_ptFeildData->BH3 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH3");;
    a_ptFeildData->BW4 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW4");;
    a_ptFeildData->BH4 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH4");;
    a_ptFeildData->BW5 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW5");;
    a_ptFeildData->BH5 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH5");;
    a_ptFeildData->BW6 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW6");;
    a_ptFeildData->BH6 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH6");;

    a_ptFeildData->BW7 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW7");
    a_ptFeildData->BH7 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH7");
    a_ptFeildData->BW8 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BW8");
    a_ptFeildData->BH8 = alINI_GetKeyValue_INT32W(pwcIniFilePath,L"Field_Data", L"BH8");

    return TRUE;
}
#endif

BOOL MANUALK_LoadFeildDataByDefault(alMANUALK_ChartCrossPointSet *a_ptFeildData)
{
    // Load Default Calibration Field Parameters
    a_ptFeildData->uwFWheeltoFChart = SIM_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST;
    a_ptFeildData->uwChartHoriDistance = SIM_DEFAULT_CHART_HORI_DIST;
    a_ptFeildData->uwCharVertDistance = SIM_DEFAULT_CHART_VERT_DIST;
    a_ptFeildData->FW1 = SIM_DEFAULT_FW1;
    a_ptFeildData->FH1 = SIM_DEFAULT_FH1;
    a_ptFeildData->FW2 = SIM_DEFAULT_FW2;
    a_ptFeildData->FH2 = SIM_DEFAULT_FH2;
    a_ptFeildData->FW3 = SIM_DEFAULT_FW3;
    a_ptFeildData->FH3 = SIM_DEFAULT_FH3;
    a_ptFeildData->FW4 = SIM_DEFAULT_FW4;
    a_ptFeildData->FH4 = SIM_DEFAULT_FH4;
    a_ptFeildData->FW5 = SIM_DEFAULT_FW5;
    a_ptFeildData->FH5 = SIM_DEFAULT_FH5;
    a_ptFeildData->FW6 = SIM_DEFAULT_FW6;
    a_ptFeildData->FH6 = SIM_DEFAULT_FH6;
    a_ptFeildData->BW1 = SIM_DEFAULT_BW1;
    a_ptFeildData->BH1 = SIM_DEFAULT_BH1;
    a_ptFeildData->BW2 = SIM_DEFAULT_BW2;
    a_ptFeildData->BH2 = SIM_DEFAULT_BH2;
    a_ptFeildData->BW3 = SIM_DEFAULT_BW3;
    a_ptFeildData->BH3 = SIM_DEFAULT_BH3;
    a_ptFeildData->BW4 = SIM_DEFAULT_BW4;
    a_ptFeildData->BH4 = SIM_DEFAULT_BH4;
    a_ptFeildData->BW5 = SIM_DEFAULT_BW5;
    a_ptFeildData->BH5 = SIM_DEFAULT_BH5;
    a_ptFeildData->BW6 = SIM_DEFAULT_BW6;
    a_ptFeildData->BH6 = SIM_DEFAULT_BH6;

    a_ptFeildData->BW7 = SIM_DEFAULT_BW7;
    a_ptFeildData->BH7 = SIM_DEFAULT_BH7;
    a_ptFeildData->BW8 = SIM_DEFAULT_BW8;
    a_ptFeildData->BH8 = SIM_DEFAULT_BH8;

    return TRUE;
}





