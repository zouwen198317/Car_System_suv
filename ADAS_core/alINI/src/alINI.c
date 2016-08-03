/*********************************************************************
*
* INI 檔的讀、寫處理工具 - c version
*
*********************************************************************/

#ifndef WIN32
#error alINI only support WIN32 platform
#endif

#include "alINI.h"

#include <stdio.h>
#include <sys/stat.h>
#include "basedef.h"

/** \cond DOXYGEN_EXCLUDE */

#define		alINI_FLOATING_FORMAT_W		    L"%.16f"
#define		alINI_FLOATING_FORMAT_A		    "%.16f"
#define     TEMP_STRING_BUFFER_SIZE         1000

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static BOOL PV_CheckIfFileExistW(const WCHAR * a_pwcFilePath)
{
    struct _stat st;
    if(_wstat(a_pwcFilePath, &st) != 0)
    {
        DEBUG_PrintfW(L"PV_CheckIfFileExistW: Can not load file: \"%s\"\n\n", a_pwcFilePath);
        return FALSE;
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static BOOL PV_CheckIfFileExistA(const CHAR * a_psFilePath)
{
    struct stat st;
    if(stat(a_psFilePath, &st) != 0)
    {
        DEBUG_Printf("CheckIfFileExistA: Can not load file: \"%s\"\n", a_psFilePath);
        return FALSE;
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_CreateSectionW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Create Section \"%s\" failed.\n", a_pwsSectionName);
        return FALSE;
    }

    // 建立一個 Section 並指定一個暫時的 Key (tmp)
    if(WritePrivateProfileStringW(a_pwsSectionName, L"tmp", L"", a_pwsINTIFilePath))
    {
        // 將該暫時的 Key (tmp) 刪除
        if(WritePrivateProfileStringW(a_pwsSectionName, L"tmp", NULL, a_pwsINTIFilePath))
            return TRUE;
    }
    return FALSE;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_CreateSectionA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Create Section \"%s\" failed.\n", a_psSectionName);
        return FALSE;
    }

    // 建立一個 Section 並指定一個暫時的 Key (tmp)
    if (WritePrivateProfileStringA(a_psSectionName, "tmp", "", a_psINTIFilePath))
    {
        // 將該暫時的 Key (tmp) 刪除
        if (WritePrivateProfileStringA(a_psSectionName, "tmp", NULL, a_psINTIFilePath))
            return TRUE;
    }
    return FALSE;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_CreateKeyW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, const WCHAR * a_pwsDefaultString)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Create Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    if(WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, a_pwsDefaultString, a_pwsINTIFilePath))
        return TRUE;
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_CreateKeyA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, const CHAR * a_psDefaultString)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Create Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, a_psDefaultString, a_psINTIFilePath))
        return TRUE;
    return FALSE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_CW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, const WCHAR * a_pwsDefaultString)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Write C String to Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    if(WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, a_pwsDefaultString, a_pwsINTIFilePath))
        return TRUE;

    return FALSE;
}

BOOL alINI_WriteKeyValue_CA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, const CHAR * a_psDefaultString)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Write C String to Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, a_psDefaultString, a_psINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_INT32W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, INT32 a_lInput)
{
    WCHAR awsStringBuff[TEMP_STRING_BUFFER_SIZE] = {0};

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Write INT32 Value to Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    swprintf_s(awsStringBuff, TEMP_STRING_BUFFER_SIZE, L"%d", a_lInput);

    if(WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, awsStringBuff, a_pwsINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_INT32A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT32 a_lInput)
{
    CHAR asStringBuff[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Write INT32 Value to Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    sprintf_s(asStringBuff, TEMP_STRING_BUFFER_SIZE, "%d", a_lInput);

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, asStringBuff, a_psINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_INT64W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, INT64 a_llInput)
{
    WCHAR awsStringBuff[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Write INT32 Value to Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    swprintf_s(awsStringBuff, TEMP_STRING_BUFFER_SIZE, L"%d", a_llInput);

    if (WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, awsStringBuff, a_pwsINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_INT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT64 a_llInput)
{
    CHAR asStringBuff[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Write INT32 Value to Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    sprintf_s(asStringBuff, TEMP_STRING_BUFFER_SIZE, "%d", a_llInput);

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, asStringBuff, a_psINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_FLOAT64W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, FLOAT64 a_eInput)
{
    WCHAR awsStringBuff[TEMP_STRING_BUFFER_SIZE] = {0};

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Write FLOAT64 Value to Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    swprintf_s(awsStringBuff, TEMP_STRING_BUFFER_SIZE, alINI_FLOATING_FORMAT_W, a_eInput);

    if(WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, awsStringBuff, a_pwsINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_WriteKeyValue_FLOAT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, FLOAT64 a_eInput)
{
    CHAR asStringBuff[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Write FLOAT64 Value to Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    sprintf_s(asStringBuff, TEMP_STRING_BUFFER_SIZE, alINI_FLOATING_FORMAT_A, a_eInput);

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, asStringBuff, a_psINTIFilePath))
        return TRUE;

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_GetKeyValueWithDefault_CW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, const WCHAR * const a_pwsDefaultString, WCHAR * const a_pwsStringBuffer, const INT32 lStringBufferSize)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get C String from Key \"%s\" failed.\n", a_pwsKeyName);
        wcscpy_s(a_pwsStringBuffer, lStringBufferSize, a_pwsDefaultString);
        return FALSE;
    }

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, a_pwsDefaultString, a_pwsStringBuffer, lStringBufferSize, a_pwsINTIFilePath);

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_GetKeyValueWithDefault_CA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, const CHAR * const a_psDefaultString, CHAR * const a_psStringBuffer, const INT32 lStringBufferSize)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get C String from Key \"%s\" failed.\n", a_psKeyName);
        strcpy_s(a_psStringBuffer, lStringBufferSize, a_psDefaultString);
        return FALSE;
    }

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, a_psDefaultString, a_psStringBuffer, lStringBufferSize, a_psINTIFilePath);

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alINI_GetKeyValueWithDefault_INT32W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, INT32 a_lDefaultValue)
{
    INT32 lReturnValue = 0;
    WCHAR awsStringBuffer[TEMP_STRING_BUFFER_SIZE] = {0};
    WCHAR awcDefaultStringBuffer[TEMP_STRING_BUFFER_SIZE] = {0};

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get INT32 Value from Key \"%s\" failed.\n", a_pwsKeyName);
        return a_lDefaultValue;
    }

    swprintf_s(awcDefaultStringBuffer, TEMP_STRING_BUFFER_SIZE, L"%d", a_lDefaultValue);

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, awcDefaultStringBuffer, awsStringBuffer, TEMP_STRING_BUFFER_SIZE, a_pwsINTIFilePath);
    lReturnValue = _wtoi(awsStringBuffer);

    return lReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alINI_GetKeyValueWithDefault_INT32A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT32 a_lDefaultValue)
{
    INT32 lReturnValue = 0;
    CHAR asStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };
    CHAR asDefaultStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get INT32 Value from Key \"%s\" failed.\n", a_psKeyName);
        return a_lDefaultValue;
    }

    sprintf_s(asDefaultStringBuffer, TEMP_STRING_BUFFER_SIZE, "%d", a_lDefaultValue);

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, asDefaultStringBuffer, asStringBuffer, TEMP_STRING_BUFFER_SIZE, a_psINTIFilePath);
    lReturnValue = atoi(asStringBuffer);

    return lReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT64 alINI_GetKeyValueWithDefault_INT64W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, INT64 a_llDefaultValue)
{
    INT64 llReturnValue = 0;
    WCHAR awsStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };
    WCHAR awcDefaultStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get INT32 Value from Key \"%s\" failed.\n", a_pwsKeyName);
        return a_llDefaultValue;
    }

    swprintf_s(awcDefaultStringBuffer, TEMP_STRING_BUFFER_SIZE, L"%d", a_llDefaultValue);

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, awcDefaultStringBuffer, awsStringBuffer, TEMP_STRING_BUFFER_SIZE, a_pwsINTIFilePath);
    llReturnValue = _wtoi64(awsStringBuffer);

    return llReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT64 alINI_GetKeyValueWithDefault_INT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT64 a_llDefaultValue)
{
    INT64 llReturnValue = 0;
    CHAR asStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };
    CHAR asDefaultStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get INT32 Value from Key \"%s\" failed.\n", a_psKeyName);
        return a_llDefaultValue;
    }

    sprintf_s(asDefaultStringBuffer, TEMP_STRING_BUFFER_SIZE, "%d", a_llDefaultValue);

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, asDefaultStringBuffer, asStringBuffer, TEMP_STRING_BUFFER_SIZE, a_psINTIFilePath);
    llReturnValue = _atoi64(asStringBuffer);

    return llReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FLOAT64 alINI_GetKeyValueWithDefault_FLOAT64W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, FLOAT64 a_eDefaultValue)
{
    FLOAT64 eReturnValue = 0;
    WCHAR awsStringBuffer[TEMP_STRING_BUFFER_SIZE] = {0};
    WCHAR awcDefaultStringBuffer[TEMP_STRING_BUFFER_SIZE] = {0};

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get FLOAT64 Value from Key \"%s\" failed.\n", a_pwsKeyName);
        return a_eDefaultValue;
    }

    swprintf_s(awcDefaultStringBuffer, TEMP_STRING_BUFFER_SIZE, alINI_FLOATING_FORMAT_W, a_eDefaultValue);

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, awcDefaultStringBuffer, awsStringBuffer, TEMP_STRING_BUFFER_SIZE, a_pwsINTIFilePath);
    eReturnValue = _wtof(awsStringBuffer);

    return eReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FLOAT64 alINI_GetKeyValueWithDefault_FLOAT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, FLOAT64 a_eDefaultValue)
{
    FLOAT64 eReturnValue = 0;
    CHAR asStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };
    CHAR asDefaultStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get FLOAT64 Value from Key \"%s\" failed.\n", a_psKeyName);
        return a_eDefaultValue;
    }

    sprintf_s(asDefaultStringBuffer, TEMP_STRING_BUFFER_SIZE, alINI_FLOATING_FORMAT_A, a_eDefaultValue);

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, asDefaultStringBuffer, asStringBuffer, TEMP_STRING_BUFFER_SIZE, a_psINTIFilePath);
    eReturnValue = atof(asStringBuffer);

    return eReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_GetKeyValue_CW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName, WCHAR * a_pwsStringBuffer, const INT32 lStringBufferSize)
{
    WCHAR * pwsDefaultString = L"[KeyBlank]";

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get C String from Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, pwsDefaultString, a_pwsStringBuffer, lStringBufferSize, a_pwsINTIFilePath);

    if(wcscmp(pwsDefaultString, a_pwsStringBuffer) == 0 || wcscmp(a_pwsStringBuffer, L"") == 0) 
        return FALSE;

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_GetKeyValue_CA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, CHAR * a_psStringBuffer, const INT32 lStringBufferSize)
{
    CHAR * psDefaultString = "[KeyBlank]";

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get C String from Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, psDefaultString, a_psStringBuffer, lStringBufferSize, a_psINTIFilePath);

    if (strcmp(psDefaultString, a_psStringBuffer) == 0 || strcmp(a_psStringBuffer, "") == 0)
        return FALSE;

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alINI_GetKeyValue_INT32W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName)
{
    INT32 lReturnValue = 0;
    WCHAR * pwsDefaultString = L"[KeyBlank]";
    WCHAR awsStringBuffer[TEMP_STRING_BUFFER_SIZE] = {0};

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get INT32 Value from Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, pwsDefaultString, awsStringBuffer, TEMP_STRING_BUFFER_SIZE, a_pwsINTIFilePath);
    lReturnValue = _wtoi(awsStringBuffer);

    if(wcscmp(pwsDefaultString, awsStringBuffer) == 0 || wcscmp(awsStringBuffer, L"") == 0) 
        return 0;

    return lReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alINI_GetKeyValue_INT32A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName)
{
    INT32 lReturnValue = 0;
    CHAR * psDefaultString = "[KeyBlank]";
    CHAR asStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get INT32 Value from Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, psDefaultString, asStringBuffer, TEMP_STRING_BUFFER_SIZE, a_psINTIFilePath);
    lReturnValue = atoi(asStringBuffer);

    if (strcmp(psDefaultString, asStringBuffer) == 0 || strcmp(asStringBuffer, "") == 0)
        return 0;

    return lReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT64 alINI_GetKeyValue_INT64W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName)
{
    INT64 llReturnValue = 0;
    WCHAR * pwsDefaultString = L"[KeyBlank]";
    WCHAR awsStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get INT32 Value from Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, pwsDefaultString, awsStringBuffer, TEMP_STRING_BUFFER_SIZE, a_pwsINTIFilePath);
    llReturnValue = _wtoi64(awsStringBuffer);

    if (wcscmp(pwsDefaultString, awsStringBuffer) == 0 || wcscmp(awsStringBuffer, L"") == 0)
        return 0;

    return llReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT64 alINI_GetKeyValue_INT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName)
{
    INT64 llReturnValue = 0;
    CHAR * psDefaultString = "[KeyBlank]";
    CHAR asStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get INT32 Value from Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, psDefaultString, asStringBuffer, TEMP_STRING_BUFFER_SIZE, a_psINTIFilePath);
    llReturnValue = _atoi64(asStringBuffer);

    if (strcmp(psDefaultString, asStringBuffer) == 0 || strcmp(asStringBuffer, "") == 0)
        return 0;

    return llReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FLOAT64 alINI_GetKeyValue_FLOAT64W(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName)
{
    FLOAT64 eReturnValue = 0;
    WCHAR * pwsDefaultString = L"[KeyBlank]";
    WCHAR awsStringBuffer[TEMP_STRING_BUFFER_SIZE] = {0};

    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Get FLOAT64 Value from Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    GetPrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, pwsDefaultString, awsStringBuffer, TEMP_STRING_BUFFER_SIZE, a_pwsINTIFilePath);
    eReturnValue = _wtof(awsStringBuffer);

    if(wcscmp(pwsDefaultString, awsStringBuffer) == 0 || wcscmp(awsStringBuffer, L"") == 0) 
        return 0;

    return eReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FLOAT64 alINI_GetKeyValue_FLOAT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName)
{
    FLOAT64 eReturnValue = 0;
    CHAR * psDefaultString = "[KeyBlank]";
    CHAR asStringBuffer[TEMP_STRING_BUFFER_SIZE] = { 0 };

    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Get FLOAT64 Value from Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    GetPrivateProfileStringA(a_psSectionName, a_psKeyName, psDefaultString, asStringBuffer, TEMP_STRING_BUFFER_SIZE, a_psINTIFilePath);
    eReturnValue = atof(asStringBuffer);

    if (strcmp(psDefaultString, asStringBuffer) == 0 || strcmp(asStringBuffer, "") == 0)
        return 0;

    return eReturnValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_DeleteSectionW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Delete Section \"%s\" failed.\n", a_pwsSectionName);
        return FALSE;
    }

    if(WritePrivateProfileStringW(a_pwsSectionName, NULL, NULL, a_pwsINTIFilePath))
        return TRUE;
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_DeleteSectionA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Delete Section \"%s\" failed.\n", a_psSectionName);
        return FALSE;
    }

    if (WritePrivateProfileStringA(a_psSectionName, NULL, NULL, a_psINTIFilePath))
        return TRUE;
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_DeleteKeyW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Delete Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    if(WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, NULL, a_pwsINTIFilePath))
        return TRUE;
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_DeleteKeyA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Delete Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, NULL, a_psINTIFilePath))
        return TRUE;
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_DeleteStringW(const WCHAR * a_pwsINTIFilePath, const WCHAR * a_pwsSectionName, const WCHAR * a_pwsKeyName)
{
    if(PV_CheckIfFileExistW(a_pwsINTIFilePath) != TRUE)
    {
        DEBUG_PrintfW(L"INI - Delete String from Key \"%s\" failed.\n", a_pwsKeyName);
        return FALSE;
    }

    if(WritePrivateProfileStringW(a_pwsSectionName, a_pwsKeyName, L"", a_pwsINTIFilePath))
        return TRUE;
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL alINI_DeleteStringA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName)
{
    if (PV_CheckIfFileExistA(a_psINTIFilePath) != TRUE)
    {
        DEBUG_Printf("INI - Delete String from Key \"%s\" failed.\n", a_psKeyName);
        return FALSE;
    }

    if (WritePrivateProfileStringA(a_psSectionName, a_psKeyName, "", a_psINTIFilePath))
        return TRUE;
    return FALSE;
}

/** \endcond DOXYGEN_EXCLUDE */
