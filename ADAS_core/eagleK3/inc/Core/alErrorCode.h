
#include "mtype.h"
#include <wchar.h>

#pragma once

/** \brief Define the error code of eagleK library.  */
typedef enum
{ 
    /** \brief No Error in this call. */
    EAGLEK3_ERROR_SUCCESSFUL = 0,

    /////////////////////////////// ¡¾ Common ¡¾ ///////////////////////////////////

    /** \brief Memory Allocation Errir */
    EAGLEK3_ERROR_MEMORY_ALLOCATION_FAILED, 

    /** \breif Buffer overflow. */
    EAGLEK3_ERROR_BUFFER_OVERFLOW, 

    /** \breif Function Disabled - The function (alAVM2D,AVM3D,...) is not enabled. */
    EAGLEK3_ERROR_FUNCTION_DISABLED, 

    /////////////////////////////// ¡µ Common ¡µ ///////////////////////////////////

    /////////////////////////////// ¡¾ Camera Calibration ¡¾ ///////////////////////////////////

    /** \bref Indicate the calibration filed file is not found in the working directory. */
    EAGLEK3_ERROR_CAMK_K_FIELD_FILE_NOT_FOUND,

    /** \bref Indicate the fine-tune file is not found in the working directory. */
    EAGLEK3_ERROR_CAMK_K_FINE_TUNE_FILE_NOT_FOUND,

	/** \brief The bird view AutoK is failed. */
	EAGLEK3_ERROR_CAMK_K_BVCAM_FACAUTOK_FAIL,

	/** \brief The bird view AutoK is disable. */
	EAGLEK3_ERROR_CAMK_K_BVCAM_FACAUTOK_DISABLE,

    /////////////////////////////// ¡µ Camera Calibration ¡µ ///////////////////////////////////

    /////////////////////////////// ¡¾ LUT Generation ¡¾ ///////////////////////////////////

    /** \brief The input ¡§alPartLUT_v1_LUTSet_t¡¨ pointer is invalied. */
    EAGLEK3_ERROR_BV_PARTITION_INVALID_POINTER,
    /** \brief The memory allocation for temporary buffer is failed. */
    EAGLEK3_ERROR_BV_PARTITION_NOT_ENOUGH_MEMORY, 
    /** \brief The number of partitioned blocks exceeds the maximum value. */
    EAGLEK3_ERROR_BV_PARTITION_ARRAY_OVERFLOW, 
    /** \brief The number of partitioned blocks for single view exceeds the maximum value. */
    EAGLEK3_ERROR_BV_PARTITION_ARRAY_OVERFLOW_SINGLE, 
    
    /** \brief There are coordinates of in BV transform exceeds undistorted (720x480) range */
    EAGLEK3_ERROR_BV_GENLUT_OUTOF_UNDISTORTED_IMAGE, 
    /** \brief There are coordinates of in BV transform exceeds distorted image (720x480) range */
    EAGLEK3_ERROR_BV_GENLUT_OUTOF_DISTORTED_IMAGE, 

    /////////////////////////////// ¡µ LUT Generation ¡µ ///////////////////////////////////

    /////////////////////////////// ¡¾ Trail Line ¡¾ ///////////////////////////////////

    /** \brief Dynamic trail line number exceeds maximum limitation. */
    EAGLEK3_ERROR_DTL_COUNT_EXCEEDS_LIMITATION,

    /////////////////////////////// ¡µ Trail Line ¡µ ///////////////////////////////////

    /////////////////////////////// ¡¾ AVM3D ¡¾ ///////////////////////////////////

    /** \brief The buffer allocation for AVM3D is failed. */
    EAGLEK3_ERROR_AVM3D_UNAVALIABLE_VIEW,

    /////////////////////////////// ¡µ AVM3D ¡µ ///////////////////////////////////

	


} alERROR_ERROR_CODE;

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief Extern the error code variable to other functions. */
extern alERROR_ERROR_CODE g_alERROR_ucErrorCode;


/** \brief Clear the error code, this call will reset it to EAGLEK3_ERROR_SUCCESSFUL. */
void alERROR_ClearErrorCode();

/**
    \brief Set the error code to the specific item.
    \param The error code to be assigned.
*/
void alERROR_SetErrorCode(alERROR_ERROR_CODE ucErrorCode);

///**
//    \brief Read the error code.
//    \return The number of error code.
//*/
//UINT8 EAGLEK3_ReadErrorCode();

#ifdef WIN32
/**
    \brief Get description string of the spedific error code.
    \param ucErrorCode [IN] The specific error code for this call.
    \param pwcErrorDescription [OUT] The c-string for the error code.
    \param ucBufferLen [IN] The length of buffer for string output. The suggest value is 255.
*/
void alERROR_ReadDescriptionByErrorCodeW(alERROR_ERROR_CODE ucErrorCode, wchar_t * pwcErrorDescription, UINT8 ucBufferLen);
#endif //#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC


#ifdef __cplusplus
}
#endif
