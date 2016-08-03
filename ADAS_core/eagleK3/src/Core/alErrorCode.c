
#include "alErrorCode.h"
#include <assert.h>
#include <wchar.h>

/** \brief The store the error code. The error code should be clear (set to 0) in the begining of each EAGLEK3_XXX function and can be read after the API is ended. */
alERROR_ERROR_CODE g_alERROR_ucErrorCode;


void alERROR_ClearErrorCode()
{
    g_alERROR_ucErrorCode = EAGLEK3_ERROR_SUCCESSFUL;
}

void alERROR_SetErrorCode(alERROR_ERROR_CODE ucErrorCode)
{
    g_alERROR_ucErrorCode = ucErrorCode;
}


//UINT8 EAGLEK3_ReadErrorCode()
//{
//    return g_alERROR_ucErrorCode;
//}
//


#ifdef WIN32
void alERROR_ReadDescriptionByErrorCodeW(alERROR_ERROR_CODE ucErrorCode, wchar_t * pwcErrorDescription, UINT8 ucBufferLen)
{
    switch (ucErrorCode)
    {

    case EAGLEK3_ERROR_SUCCESSFUL:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"No Error in this call.");
        break;
    case EAGLEK3_ERROR_BV_PARTITION_INVALID_POINTER:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"The input ¡§alPartLUT_v1_LUTSet_t¡¨ pointer is invalied.");
        break;
    case EAGLEK3_ERROR_BV_PARTITION_NOT_ENOUGH_MEMORY:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"The memory allocation for temporary buffer is failed.");
        break;
    case EAGLEK3_ERROR_BV_PARTITION_ARRAY_OVERFLOW:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"The number of partitioned blocks exceeds the maximum value.");
        break;
    case EAGLEK3_ERROR_BV_PARTITION_ARRAY_OVERFLOW_SINGLE:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"The number of partitioned blocks for single view exceeds the maximum value.");
        break;
    case EAGLEK3_ERROR_BV_GENLUT_OUTOF_UNDISTORTED_IMAGE:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"There are coordinates of in BV transform exceeds undistorted (720x480) range.");
        break;
    case EAGLEK3_ERROR_BV_GENLUT_OUTOF_DISTORTED_IMAGE:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"There are coordinates of in BV transform exceeds distorted image (720x480) range.");
        break;
    case EAGLEK3_ERROR_MEMORY_ALLOCATION_FAILED:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"Memory allocation is faileds.");
        break;
     case EAGLEK3_ERROR_BUFFER_OVERFLOW:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"Buffer overflow.");
        break;
	 case EAGLEK3_ERROR_CAMK_K_BVCAM_FACAUTOK_FAIL:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"BirdView AutoK is failed.");
        break;
	 case EAGLEK3_ERROR_CAMK_K_BVCAM_FACAUTOK_DISABLE:
		 wcscpy_s(pwcErrorDescription, ucBufferLen, L"BirdView AutoK is disable.");
		 break;

    default:
        wcscpy_s(pwcErrorDescription, ucBufferLen, L"No description.");
    }
}
#endif


