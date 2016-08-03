/*********************************************************************
*
* INI 檔的讀、寫處理工具 - c version
*
*********************************************************************/

#pragma once

#ifndef WIN32
#error alINI only support WIN32 platform
#endif

#include <windows.h>

#include "mtype.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    *  \defgroup alINI   alINI
    *  The module to do INI read/write operation.
    *  @{
    */

    /**
    \brief Create a new section name - for unicode string.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    */
    BOOL alINI_CreateSectionW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName);
    /**
    \brief Create a new section name - for multibytes string.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    */
    BOOL alINI_CreateSectionA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName);

    /**
    \brief Create a new key name - for unicode string.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_pwsDefaultString [IN] The defualt value for the key.
    */
    BOOL alINI_CreateKeyW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, const wchar_t * a_pwsDefaultString);
    /**
    \brief Create a new key name - for multibytes string.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_psDefaultString [IN] The defualt value for the key.
    */
    BOOL alINI_CreateKeyA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, const CHAR * a_psDefaultString);

    /**
    \brief Write a string to the specified key - for unicode string. If the section or key name is not exist, it will be created.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_pwsDefaultString [IN] The defualt value for the key.
    */
    BOOL alINI_WriteKeyValue_CW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, const wchar_t * a_pwsDefaultString);
    /**
    \brief Write a string to the specified key - for multibytes string. If the section or key name is not exist, it will be created.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_psDefaultString [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_CA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, const CHAR * a_psDefaultString);

    /**
    \brief Write a INT32 value to the specified key - for unicode string. If the section or key name is not exist, it will be created.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_lInput [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_INT32W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, INT32 a_lInput);
    /**
    \brief Write a INT32 value to the specified key - for multibytes string. If the section or key name is not exist, it will be created.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_lInput [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_INT32A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT32 a_lInput);

    /**
    \brief Write a INT64 value to the specified key - for unicode string. If the section or key name is not exist, it will be created.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_llInput [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_INT64W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, INT64 a_llInput);
    /**
    \brief Write a INT64 value to the specified key - for multibytes string. If the section or key name is not exist, it will be created.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_llInput [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_INT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT64 a_llInput);


    /**
    \brief Write a FLOAT64 value to the specified key - for unicode string. If the section or key name is not exist, it will be created.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_eInput [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_FLOAT64W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, FLOAT64 a_eInput);
    /**
    \brief Write a FLOAT64 value to the specified key - for multibytes string. If the section or key name is not exist, it will be created.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_eInput [IN] The value for the key.
    */
    BOOL alINI_WriteKeyValue_FLOAT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, FLOAT64 a_eInput);


    /**
    \brief Get a string from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_pwsDefaultString [IN] The default value for the key.
    \param a_pwsStringBuffer [OUT] The buffer to store the string.
    \param lStringBufferSize [IN] The size of the buffer "a_psStringBuffer".
    */
    BOOL alINI_GetKeyValueWithDefault_CW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, const wchar_t * const a_pwsDefaultString, wchar_t * const a_pwsStringBuffer, const INT32 lStringBufferSize);
    /**
    \brief Get a string from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_psDefaultString [IN] The default value for the key.
    \param a_psStringBuffer [OUT] The buffer to store the string.
    \param lStringBufferSize [IN] The size of the buffer "a_psStringBuffer".
    \return FALSE if data not exists.
    */
    BOOL alINI_GetKeyValueWithDefault_CA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, const CHAR * const a_psDefaultString, CHAR * const a_psStringBuffer, const INT32 lStringBufferSize);

    /**
    \brief Get a INT32 value from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_lDefaultValue [IN] The default value for the key.
    \return The INT32 value which is got from INI file. Return 0 if data no exists.
    */
    INT32 alINI_GetKeyValueWithDefault_INT32W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, INT32 a_lDefaultValue);
    /**
    \brief Get a INT32 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_lDefaultValue [IN] The default value for the key.
    \return The INT32 value which is got from INI file. Return 0 if data no exists.
    */
    INT32 alINI_GetKeyValueWithDefault_INT32A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT32 a_lDefaultValue);

    /**
    \brief Get a INT64 value from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_llDefaultValue [IN] The default value for the key.
    \return The INT64 value which is got from INI file. Return 0 if data no exists.
    */
    INT64 alINI_GetKeyValueWithDefault_INT64W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, INT64 a_llDefaultValue);
    /**
    \brief Get a INT64 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_llDefaultValue [IN] The default value for the key.
    \return The INT64 value which is got from INI file. Return 0 if data no exists.
    */
    INT64 alINI_GetKeyValueWithDefault_INT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, INT64 a_llDefaultValue);

    /**
    \brief Get a FLOAT64 value from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_eDefaultValue [IN] The default value for the key.
    \return The FLOAT64 value which is got from INI file. Return 0 if data no exists.
    */
    FLOAT64 alINI_GetKeyValueWithDefault_FLOAT64W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, FLOAT64 a_eDefaultValue);
    /**
    \brief Get a FLOAT64 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_eDefaultValue [IN] The default value for the key.
    \return The FLOAT64 value which is got from INI file. Return 0 if data no exists.
    */
    FLOAT64 alINI_GetKeyValueWithDefault_FLOAT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, FLOAT64 a_eDefaultValue);

    /**
    \brief Get a string from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \param a_pwsStringBuffer [OUT] The buffer to store the string.
    \param lStringBufferSize [IN] The size of the buffer "a_psStringBuffer".
    \return FALSE if data not exists.
    */
    BOOL alINI_GetKeyValue_CW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName, wchar_t * a_pwsStringBuffer, const INT32 lStringBufferSize);
    /**
    \brief Get a FLOAT64 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \param a_psStringBuffer [OUT] The buffer to store the string.
    \param lStringBufferSize [IN] The size of the buffer "a_psStringBuffer".
    \return FALSE if data not exists.
    */
    BOOL alINI_GetKeyValue_CA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName, CHAR * a_psStringBuffer, const INT32 lStringBufferSize);

    /**
    \brief Get a INT32 value from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \return The INT32 value which is got from INI file. Return 0 if data no exists.
    */
    INT32 alINI_GetKeyValue_INT32W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName);
    /**
    \brief Get a INT32 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \return The INT32 value which is got from INI file. Return 0 if data no exists.
    */
    INT32 alINI_GetKeyValue_INT32A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName);


    /**
    \brief Get a INT64 value from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \return The INT64 value which is got from INI file. Return 0 if data no exists.
    */
    INT64 alINI_GetKeyValue_INT64W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName);
    /**
    \brief Get a INT64 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \return The INT64 value which is got from INI file. Return 0 if data no exists.
    */
    INT64 alINI_GetKeyValue_INT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName);

    /**
    \brief Get a FLOAT64 value from the specified key - for unicode string. If the section or key name is not exist, they default value will be filled in.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \return The FLOAT64 value which is got from INI file. Return 0 if data no exists.
    */
    FLOAT64 alINI_GetKeyValue_FLOAT64W(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName);
    /**
    \brief Get a FLOAT64 value from the specified key - for multibytes string. If the section or key name is not exist, they default value will be filled in.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \return The FLOAT64 value which is got from INI file. Return 0 if data no exists.
    */
    FLOAT64 alINI_GetKeyValue_FLOAT64A(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName);

    /**
    \brief Delete a section including all key value in the section - for unicode string.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \return FALSE if any error occurs.
    */
    BOOL alINI_DeleteSectionW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName);
    /**
    \brief Delete a section including all key value in the section - for multibytes string.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \return FALSE if any error occurs.
    */
    BOOL alINI_DeleteSectionA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName);

    /**
    \brief Delete a key name in the specified section - for unicode string.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \return FALSE if any error occurs.
    */
    BOOL alINI_DeleteKeyW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName);
    /**
    \brief Delete a key name in the specified section - for multibytes string.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \return FALSE if any error occurs.
    */
    BOOL alINI_DeleteKeyA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName);

    /**
    \brief Delete a key value in the specified section and key name - for multibytes string.
    \param a_pwsINTIFilePath [IN] Path of the INI file.
    \param a_pwsSectionName [IN] The specified section name.
    \param a_pwsKeyName [IN] The specified key name.
    \return FALSE if any error occurs.
    */
    BOOL alINI_DeleteStringW(const wchar_t * a_pwsINTIFilePath, const wchar_t * a_pwsSectionName, const wchar_t * a_pwsKeyName);
    /**
    \brief Delete a key value in the specified section and key name - for multibytes string.
    \param a_psINTIFilePath [IN] Path of the INI file.
    \param a_psSectionName [IN] The specified section name.
    \param a_psKeyName [IN] The specified key name.
    \return FALSE if any error occurs.
    */
    BOOL alINI_DeleteStringA(const CHAR * a_psINTIFilePath, const CHAR * a_psSectionName, const CHAR * a_psKeyName);

    /**
    *  @}
    */

#ifdef __cplusplus
}
#endif
