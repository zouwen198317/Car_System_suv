#include "BVCAM_FACAUTOK/RectK_Def.h"


BOOL alRECK_LoadRefData(wchar_t * pwcIniFileName, alRECK_CalCfg *a_ptFeildData)
{
#ifdef WIN32
	INT32 i = 0;
	wchar_t pwcIniFilePath[MAX_PATH];
	// struct _stat64i32 tFileStat;

    wcscpy_s(pwcIniFilePath, MAX_PATH, pwcIniFileName);

	// if (_wstat(pwcIniFilePath, &tFileStat) != 0) return FALSE;

#if 0 // for debug test
	alRECK_CalCfg tFeildData;
	memcpy(&tFeildData, a_ptFeildData, sizeof(alRECK_CalCfg));
	memset(a_ptFeildData, 0, sizeof(alRECK_CalCfg));
#endif

    // a_ptCfg->atRecKCfg[i].atROICfg[j].lSBVOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

	// LEFT
	a_ptFeildData->atIdealFPRecK[0].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW1", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[0].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH1", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[1].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW2", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[1].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH2", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[2].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW3", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[2].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH3", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[3].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW4", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[3].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH4", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[4].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW5", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[4].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH5", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[5].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW6", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[5].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH6", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[6].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW7", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[6].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH7", 0, pwcIniFilePath);
	
	a_ptFeildData->atIdealFPRecK[7].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LW8", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[7].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"LH8", 0, pwcIniFilePath);


	// RIGHT
	a_ptFeildData->atIdealFPRecK[8].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW1", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[8].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH1", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[9].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW2", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[9].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH2", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[10].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW3", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[10].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH3", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[11].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW4", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[11].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH4", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[12].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW5", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[12].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH5", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[13].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW6", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[13].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH6", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[14].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW7", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[14].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH7", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[15].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RW8", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[15].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"RH8", 0, pwcIniFilePath);


	// FRONT
	a_ptFeildData->atIdealFPRecK[16].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW1", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[16].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH1", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[17].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW2", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[17].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH2", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[18].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW3", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[18].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH3", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[19].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW4", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[19].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH4", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[20].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW5", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[20].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH5", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[21].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW6", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[21].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH6", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[22].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW7", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[22].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH7", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[23].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW8", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[23].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH8", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[24].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW9", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[24].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH9", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[25].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW10", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[25].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH10", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[26].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW11", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[26].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH11", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[27].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW12", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[27].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH12", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[28].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW13", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[28].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH13", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[29].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW14", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[29].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH14", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[30].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW15", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[30].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH15", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[31].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FW16", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[31].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"FH16", 0, pwcIniFilePath);

	// BACK
	a_ptFeildData->atIdealFPRecK[32].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW1", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[32].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH1", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[33].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW2", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[33].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH2", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[34].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW3", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[34].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH3", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[35].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW4", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[35].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH4", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[36].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW5", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[36].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH5", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[37].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW6", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[37].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH6", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[38].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW7", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[38].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH7", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[39].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW8", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[39].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH8", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[40].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW9", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[40].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH9", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[41].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW10", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[41].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH10", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[42].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW11", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[42].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH11", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[43].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW12", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[43].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH12", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[44].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW13", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[44].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH13", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[45].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW14", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[45].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH14", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[46].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW15", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[46].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH15", 0, pwcIniFilePath);

	a_ptFeildData->atIdealFPRecK[47].lX = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BW16", 0, pwcIniFilePath);
	a_ptFeildData->atIdealFPRecK[47].lY = GetPrivateProfileIntW(L"Retangle_Field_Data", L"BH16", 0, pwcIniFilePath);
#if 0 // for debug test
	for (i = 0; i < 50;i++)
	{
		assert(memcmp(&tFeildData.atIdealFPRecK[i], &a_ptFeildData->atIdealFPRecK[i], sizeof(alPointINT32)) == 0);
	}
	assert(memcmp(&tFeildData, a_ptFeildData, sizeof(alRECK_CalCfg)) == 0);
#endif


    // for disable flag
    // LEFT
    a_ptFeildData->aucFlag[0] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L1", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[1] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L2", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[2] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L3", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[3] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L4", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[4] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L5", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[5] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L6", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[6] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L7", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[7] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"L8", 0, pwcIniFilePath);

    // RIGHT
    a_ptFeildData->aucFlag[8] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R1", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[9] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R2", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[10] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R3", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[11] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R4", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[12] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R5", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[13] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R6", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[14] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R7", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[15] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"R8", 0, pwcIniFilePath);

    // FRONT
    a_ptFeildData->aucFlag[16] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F1", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[17] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F2", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[18] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F3", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[19] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F4", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[20] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F5", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[21] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F6", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[22] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F7", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[23] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F8", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[24] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F9", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[25] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F10", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[26] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F11", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[27] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F12", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[28] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F13", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[29] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F14", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[30] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F15", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[31] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"F16", 0, pwcIniFilePath);

    // BACK
    a_ptFeildData->aucFlag[32] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B1", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[33] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B2", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[34] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B3", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[35] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B4", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[36] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B5", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[37] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B6", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[38] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B7", 0, pwcIniFilePath);
    a_ptFeildData->aucFlag[39] = GetPrivateProfileIntW(L"Retangle_Disable_Flag", L"B8", 0, pwcIniFilePath);
#endif
	return TRUE;
}

void alRECK_LoadDefaultRefData(alRECK_CalCfg *a_ptFeildData)
{
    // FP Flag
    memset(a_ptFeildData->aucFlag, 0, alRECK_MAX_POINT_TOTAL*sizeof(UINT8));

	// LEFT
	a_ptFeildData->atIdealFPRecK[0].lX = alRECK_RECTANGLE_LEFT_0_0_X;
	a_ptFeildData->atIdealFPRecK[0].lY = alRECK_RECTANGLE_LEFT_0_0_Y;
	a_ptFeildData->atIdealFPRecK[1].lX = alRECK_RECTANGLE_LEFT_0_1_X;
	a_ptFeildData->atIdealFPRecK[1].lY = alRECK_RECTANGLE_LEFT_0_1_Y;
	a_ptFeildData->atIdealFPRecK[2].lX = alRECK_RECTANGLE_LEFT_0_2_X;
	a_ptFeildData->atIdealFPRecK[2].lY = alRECK_RECTANGLE_LEFT_0_2_Y;
	a_ptFeildData->atIdealFPRecK[3].lX = alRECK_RECTANGLE_LEFT_0_3_X;
	a_ptFeildData->atIdealFPRecK[3].lY = alRECK_RECTANGLE_LEFT_0_3_Y;

	a_ptFeildData->atIdealFPRecK[4].lX = alRECK_RECTANGLE_LEFT_1_0_X;
	a_ptFeildData->atIdealFPRecK[4].lY = alRECK_RECTANGLE_LEFT_1_0_Y;
	a_ptFeildData->atIdealFPRecK[5].lX = alRECK_RECTANGLE_LEFT_1_1_X;
	a_ptFeildData->atIdealFPRecK[5].lY = alRECK_RECTANGLE_LEFT_1_1_Y;
	a_ptFeildData->atIdealFPRecK[6].lX = alRECK_RECTANGLE_LEFT_1_2_X;
	a_ptFeildData->atIdealFPRecK[6].lY = alRECK_RECTANGLE_LEFT_1_2_Y;
	a_ptFeildData->atIdealFPRecK[7].lX = alRECK_RECTANGLE_LEFT_1_3_X;
	a_ptFeildData->atIdealFPRecK[7].lY = alRECK_RECTANGLE_LEFT_1_3_Y;

	// RIGHT
	a_ptFeildData->atIdealFPRecK[8].lX = alRECK_RECTANGLE_RIGHT_0_0_X;
	a_ptFeildData->atIdealFPRecK[8].lY = alRECK_RECTANGLE_RIGHT_0_0_Y;
	a_ptFeildData->atIdealFPRecK[9].lX = alRECK_RECTANGLE_RIGHT_0_1_X;
	a_ptFeildData->atIdealFPRecK[9].lY = alRECK_RECTANGLE_RIGHT_0_1_Y;
	a_ptFeildData->atIdealFPRecK[10].lX = alRECK_RECTANGLE_RIGHT_0_2_X;
	a_ptFeildData->atIdealFPRecK[10].lY = alRECK_RECTANGLE_RIGHT_0_2_Y;
	a_ptFeildData->atIdealFPRecK[11].lX = alRECK_RECTANGLE_RIGHT_0_3_X;
	a_ptFeildData->atIdealFPRecK[11].lY = alRECK_RECTANGLE_RIGHT_0_3_Y;

	a_ptFeildData->atIdealFPRecK[12].lX = alRECK_RECTANGLE_RIGHT_1_0_X;
	a_ptFeildData->atIdealFPRecK[12].lY = alRECK_RECTANGLE_RIGHT_1_0_Y;
	a_ptFeildData->atIdealFPRecK[13].lX = alRECK_RECTANGLE_RIGHT_1_1_X;
	a_ptFeildData->atIdealFPRecK[13].lY = alRECK_RECTANGLE_RIGHT_1_1_Y;
	a_ptFeildData->atIdealFPRecK[14].lX = alRECK_RECTANGLE_RIGHT_1_2_X;
	a_ptFeildData->atIdealFPRecK[14].lY = alRECK_RECTANGLE_RIGHT_1_2_Y;
	a_ptFeildData->atIdealFPRecK[15].lX = alRECK_RECTANGLE_RIGHT_1_3_X;
	a_ptFeildData->atIdealFPRecK[15].lY = alRECK_RECTANGLE_RIGHT_1_3_Y;

#if alRECK_NISSAN_CHART == 0 // for 自己的長方形版
	// FRONT
	a_ptFeildData->atIdealFPRecK[16].lX = alRECK_RECTANGLE_FRONT_0_0_X;
	a_ptFeildData->atIdealFPRecK[16].lY = alRECK_RECTANGLE_FRONT_0_0_Y;
	a_ptFeildData->atIdealFPRecK[17].lX = alRECK_RECTANGLE_FRONT_0_1_X;
	a_ptFeildData->atIdealFPRecK[17].lY = alRECK_RECTANGLE_FRONT_0_1_Y;
	a_ptFeildData->atIdealFPRecK[18].lX = alRECK_RECTANGLE_FRONT_0_2_X;
	a_ptFeildData->atIdealFPRecK[18].lY = alRECK_RECTANGLE_FRONT_0_2_Y;
	a_ptFeildData->atIdealFPRecK[19].lX = alRECK_RECTANGLE_FRONT_0_3_X;
	a_ptFeildData->atIdealFPRecK[19].lY = alRECK_RECTANGLE_FRONT_0_3_Y;

	// BACK
	a_ptFeildData->atIdealFPRecK[20].lX = alRECK_RECTANGLE_BACK_0_0_X;
	a_ptFeildData->atIdealFPRecK[20].lY = alRECK_RECTANGLE_BACK_0_0_Y;
	a_ptFeildData->atIdealFPRecK[21].lX = alRECK_RECTANGLE_BACK_0_1_X;
	a_ptFeildData->atIdealFPRecK[21].lY = alRECK_RECTANGLE_BACK_0_1_Y;
	a_ptFeildData->atIdealFPRecK[22].lX = alRECK_RECTANGLE_BACK_0_2_X;
	a_ptFeildData->atIdealFPRecK[22].lY = alRECK_RECTANGLE_BACK_0_2_Y;
	a_ptFeildData->atIdealFPRecK[23].lX = alRECK_RECTANGLE_BACK_0_3_X;
	a_ptFeildData->atIdealFPRecK[23].lY = alRECK_RECTANGLE_BACK_0_3_Y;
#else // for Nissan 板子
	// FRONT
	a_ptFeildData->atIdealFPRecK[16].lX = alRECK_RECTANGLE_FRONT_0_0_X;
	a_ptFeildData->atIdealFPRecK[16].lY = alRECK_RECTANGLE_FRONT_0_0_Y;
	a_ptFeildData->atIdealFPRecK[17].lX = alRECK_RECTANGLE_FRONT_0_1_X;
	a_ptFeildData->atIdealFPRecK[17].lY = alRECK_RECTANGLE_FRONT_0_1_Y;
	a_ptFeildData->atIdealFPRecK[18].lX = alRECK_RECTANGLE_FRONT_0_2_X;
	a_ptFeildData->atIdealFPRecK[18].lY = alRECK_RECTANGLE_FRONT_0_2_Y;
	a_ptFeildData->atIdealFPRecK[19].lX = alRECK_RECTANGLE_FRONT_0_3_X;
	a_ptFeildData->atIdealFPRecK[19].lY = alRECK_RECTANGLE_FRONT_0_3_Y;

	a_ptFeildData->atIdealFPRecK[20].lX = alRECK_RECTANGLE_FRONT_1_0_X;
	a_ptFeildData->atIdealFPRecK[20].lY = alRECK_RECTANGLE_FRONT_1_0_Y;
	a_ptFeildData->atIdealFPRecK[21].lX = alRECK_RECTANGLE_FRONT_1_1_X;
	a_ptFeildData->atIdealFPRecK[21].lY = alRECK_RECTANGLE_FRONT_1_1_Y;
	a_ptFeildData->atIdealFPRecK[22].lX = alRECK_RECTANGLE_FRONT_1_2_X;
	a_ptFeildData->atIdealFPRecK[22].lY = alRECK_RECTANGLE_FRONT_1_2_Y;
	a_ptFeildData->atIdealFPRecK[23].lX = alRECK_RECTANGLE_FRONT_1_3_X;
	a_ptFeildData->atIdealFPRecK[23].lY = alRECK_RECTANGLE_FRONT_1_3_Y;

	a_ptFeildData->atIdealFPRecK[24].lX = alRECK_RECTANGLE_FRONT_2_0_X;
	a_ptFeildData->atIdealFPRecK[24].lY = alRECK_RECTANGLE_FRONT_2_0_Y;
	a_ptFeildData->atIdealFPRecK[25].lX = alRECK_RECTANGLE_FRONT_2_1_X;
	a_ptFeildData->atIdealFPRecK[25].lY = alRECK_RECTANGLE_FRONT_2_1_Y;
	a_ptFeildData->atIdealFPRecK[26].lX = alRECK_RECTANGLE_FRONT_2_2_X;
	a_ptFeildData->atIdealFPRecK[26].lY = alRECK_RECTANGLE_FRONT_2_2_Y;
	a_ptFeildData->atIdealFPRecK[27].lX = alRECK_RECTANGLE_FRONT_2_3_X;
	a_ptFeildData->atIdealFPRecK[27].lY = alRECK_RECTANGLE_FRONT_2_3_Y;

	a_ptFeildData->atIdealFPRecK[28].lX = alRECK_RECTANGLE_FRONT_3_0_X;
	a_ptFeildData->atIdealFPRecK[28].lY = alRECK_RECTANGLE_FRONT_3_0_Y;
	a_ptFeildData->atIdealFPRecK[29].lX = alRECK_RECTANGLE_FRONT_3_1_X;
	a_ptFeildData->atIdealFPRecK[29].lY = alRECK_RECTANGLE_FRONT_3_1_Y;
	a_ptFeildData->atIdealFPRecK[30].lX = alRECK_RECTANGLE_FRONT_3_2_X;
	a_ptFeildData->atIdealFPRecK[30].lY = alRECK_RECTANGLE_FRONT_3_2_Y;
	a_ptFeildData->atIdealFPRecK[31].lX = alRECK_RECTANGLE_FRONT_3_3_X;
	a_ptFeildData->atIdealFPRecK[31].lY = alRECK_RECTANGLE_FRONT_3_3_Y;

	// BACK
	a_ptFeildData->atIdealFPRecK[32].lX = alRECK_RECTANGLE_BACK_0_0_X;
	a_ptFeildData->atIdealFPRecK[32].lY = alRECK_RECTANGLE_BACK_0_0_Y;
	a_ptFeildData->atIdealFPRecK[33].lX = alRECK_RECTANGLE_BACK_0_1_X;
	a_ptFeildData->atIdealFPRecK[33].lY = alRECK_RECTANGLE_BACK_0_1_Y;
	a_ptFeildData->atIdealFPRecK[34].lX = alRECK_RECTANGLE_BACK_0_2_X;
	a_ptFeildData->atIdealFPRecK[34].lY = alRECK_RECTANGLE_BACK_0_2_Y;
	a_ptFeildData->atIdealFPRecK[35].lX = alRECK_RECTANGLE_BACK_0_3_X;
	a_ptFeildData->atIdealFPRecK[35].lY = alRECK_RECTANGLE_BACK_0_3_Y;

	a_ptFeildData->atIdealFPRecK[36].lX = alRECK_RECTANGLE_BACK_1_0_X;
	a_ptFeildData->atIdealFPRecK[36].lY = alRECK_RECTANGLE_BACK_1_0_Y;
	a_ptFeildData->atIdealFPRecK[37].lX = alRECK_RECTANGLE_BACK_1_1_X;
	a_ptFeildData->atIdealFPRecK[37].lY = alRECK_RECTANGLE_BACK_1_1_Y;
	a_ptFeildData->atIdealFPRecK[38].lX = alRECK_RECTANGLE_BACK_1_2_X;
	a_ptFeildData->atIdealFPRecK[38].lY = alRECK_RECTANGLE_BACK_1_2_Y;
	a_ptFeildData->atIdealFPRecK[39].lX = alRECK_RECTANGLE_BACK_1_3_X;
	a_ptFeildData->atIdealFPRecK[39].lY = alRECK_RECTANGLE_BACK_1_3_Y;

#endif
}

void alRECK_LoadDefault(INT32 a_lMode, alRECK_Cfg *a_ptCFGData)
{
	switch (a_lMode)
	{
	case 0: // -90 degree L
		a_ptCFGData->lROINum = alRECK_ROI_NUM_LEFT;
		a_ptCFGData->atROICfg[0].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[1].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[0].eSBVScale = alRECK_SBV_SCALE_LEFT_1;
		a_ptCFGData->atROICfg[1].eSBVScale = alRECK_SBV_SCALE_LEFT_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetX = alRECK_SBV_OFFSETX_LEFT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetX = alRECK_SBV_OFFSETX_LEFT_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetY = alRECK_SBV_OFFSETY_LEFT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetY = alRECK_SBV_OFFSETY_LEFT_2;
		break;
	case 1: // +90 degree R
		a_ptCFGData->lROINum = alRECK_ROI_NUM_RIGHT;
		a_ptCFGData->atROICfg[0].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[1].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[0].eSBVScale = alRECK_SBV_SCALE_RIGHT_1;
		a_ptCFGData->atROICfg[1].eSBVScale = alRECK_SBV_SCALE_RIGHT_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetX = alRECK_SBV_OFFSETX_RIGHT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetX = alRECK_SBV_OFFSETX_RIGHT_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetY = alRECK_SBV_OFFSETY_RIGHT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetY = alRECK_SBV_OFFSETY_RIGHT_2;
		break;
	case 2: // 180 degree F

#if alRECK_NISSAN_CHART == 1 // for Nissan 板子
		a_ptCFGData->lROINum = alRECK_ROI_NUM_FRONT;
		a_ptCFGData->atROICfg[0].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[1].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[2].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[3].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[0].eSBVScale = alRECK_SBV_SCALE_FRONT_1;
		a_ptCFGData->atROICfg[1].eSBVScale = alRECK_SBV_SCALE_FRONT_2;
		a_ptCFGData->atROICfg[2].eSBVScale = alRECK_SBV_SCALE_FRONT_3;
		a_ptCFGData->atROICfg[3].eSBVScale = alRECK_SBV_SCALE_FRONT_4;
		a_ptCFGData->atROICfg[0].lSBVOffsetX = alRECK_SBV_OFFSETX_FRONT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetX = alRECK_SBV_OFFSETX_FRONT_2;
		a_ptCFGData->atROICfg[2].lSBVOffsetX = alRECK_SBV_OFFSETX_FRONT_3;
		a_ptCFGData->atROICfg[3].lSBVOffsetX = alRECK_SBV_OFFSETX_FRONT_4;
		a_ptCFGData->atROICfg[0].lSBVOffsetY = alRECK_SBV_OFFSETY_FRONT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetY = alRECK_SBV_OFFSETY_FRONT_2;
		a_ptCFGData->atROICfg[2].lSBVOffsetY = alRECK_SBV_OFFSETY_FRONT_3;
		a_ptCFGData->atROICfg[3].lSBVOffsetY = alRECK_SBV_OFFSETY_FRONT_4;
#else
		a_ptCFGData->lROINum = 1;
		a_ptCFGData->atROICfg[0].lPointNum = 4;
		a_ptCFGData->atROICfg[1].lPointNum = 0;
		a_ptCFGData->atROICfg[0].eSBVScale = alRECK_SBV_SCALE_FRONT_1;
		a_ptCFGData->atROICfg[1].eSBVScale = alRECK_SBV_SCALE_FRONT_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetX = alRECK_SBV_OFFSETX_FRONT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetX = alRECK_SBV_OFFSETX_FRONT_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetY = alRECK_SBV_OFFSETY_FRONT_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetY = alRECK_SBV_OFFSETY_FRONT_2;
#endif
		break;
	case 3:  // 0 degree B
#if alRECK_NISSAN_CHART == 1 // for Nissan 板子
		a_ptCFGData->lROINum = alRECK_ROI_NUM_BACK;
		a_ptCFGData->atROICfg[0].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[1].lPointNum = alRECK_RECTANGLE_POINT_NUM;
		a_ptCFGData->atROICfg[0].eSBVScale = alRECK_SBV_SCALE_BACK_1;
		a_ptCFGData->atROICfg[1].eSBVScale = alRECK_SBV_SCALE_BACK_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetX = alRECK_SBV_OFFSETX_BACK_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetX = alRECK_SBV_OFFSETX_BACK_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetY = alRECK_SBV_OFFSETY_BACK_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetY = alRECK_SBV_OFFSETY_BACK_2;
#else
		a_ptCFGData->lROINum = 1;
		a_ptCFGData->atROICfg[0].lPointNum = 4;
		a_ptCFGData->atROICfg[1].lPointNum = 0;
		a_ptCFGData->atROICfg[0].eSBVScale = alRECK_SBV_SCALE_BACK_1;
		a_ptCFGData->atROICfg[1].eSBVScale = alRECK_SBV_SCALE_BACK_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetX = alRECK_SBV_OFFSETX_BACK_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetX = alRECK_SBV_OFFSETX_BACK_2;
		a_ptCFGData->atROICfg[0].lSBVOffsetY = alRECK_SBV_OFFSETY_BACK_1;
		a_ptCFGData->atROICfg[1].lSBVOffsetY = alRECK_SBV_OFFSETY_BACK_2;
#endif
		break;
	default:
		assert(0);
		break;
	}
}