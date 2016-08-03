
#include <assert.h>
#include "alLDCK_Def.h"
#ifdef WIN32
#include "alINI.h"
#endif


void alLDCK_LoadIdealCornerByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData)
{
    INT32 lFPCnt = 0, lCnt = 0;
    CHAR acTmp[MAX_PATH] = {0};

    lFPCnt = alINI_GetKeyValue_INT32A(a_pcINIFile, "FP_Data_Ideal", "CNT");

    for (lCnt = 0; lCnt < lFPCnt ; lCnt++)
    {
        sprintf_s(acTmp, MAX_PATH, "X%d", lCnt);
        a_ptData->atCornerIdeal[lCnt].eX = alINI_GetKeyValue_FLOAT64A(a_pcINIFile, "FP_Data_Ideal", acTmp);

        sprintf_s(acTmp, MAX_PATH, "Y%d", lCnt);
        a_ptData->atCornerIdeal[lCnt].eY = alINI_GetKeyValue_FLOAT64A(a_pcINIFile, "FP_Data_Ideal", acTmp);
    }

}

void alLDCK_LoadCornerByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData)
{
    INT32 lFPCnt = 0, lCnt = 0;
    CHAR acTmp[MAX_PATH] = { 0 };

    lFPCnt = alINI_GetKeyValue_INT32A(a_pcINIFile, "FP_Data_Real", "CNT");

    for (lCnt = 0; lCnt < lFPCnt; lCnt++)
    {
        sprintf_s(acTmp, MAX_PATH, "X%d", lCnt);
        a_ptData->atCorner[lCnt].eX = alINI_GetKeyValue_FLOAT64A(a_pcINIFile, "FP_Data_Real", acTmp);

        sprintf_s(acTmp, MAX_PATH, "Y%d", lCnt);
        a_ptData->atCorner[lCnt].eY = alINI_GetKeyValue_FLOAT64A(a_pcINIFile, "FP_Data_Real", acTmp);
    }

}

void alLDCK_LoadMatrixFlagByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData)
{
    INT32 lFPCnt = 0, lCnt = 0;
    CHAR acTmp[MAX_PATH] = { 0 };


    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM ; lCnt++)
    {
        sprintf_s(acTmp, MAX_PATH, "F%d", lCnt);
        a_ptData->aucCornerFlag_H_Matrix[lCnt] = (UINT8)alINI_GetKeyValue_INT32A(a_pcINIFile, "FP_Flag_H", acTmp);
    }

}


void alLDCK_LoadCornerFlagByINI(CHAR *a_pcINIFile, alLDCK_Data *a_ptData)
{
    INT32 lFPCnt = 0, lCnt = 0;
    CHAR acTmp[MAX_PATH] = { 0 };


    for (lCnt = 0; lCnt < alLDCK_CORNER_NUM; lCnt++)
    {
        sprintf_s(acTmp, MAX_PATH, "F%d", lCnt);
        a_ptData->aucCornerFlag[lCnt] = (UINT8)alINI_GetKeyValue_INT32A(a_pcINIFile, "FP_Flag", acTmp);
    }

}

