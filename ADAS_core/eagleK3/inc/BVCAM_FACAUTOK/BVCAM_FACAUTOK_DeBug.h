#pragma once

/**
*  \addtogroup alBVCAM_FACAUTOK_PC_DeBug
*  @{
*/


#define alBVCAM_FACAUTOK_PC_DeBug 1

#define BVCAM_FACAUTOK_FAIL_LOG 1

#if alBVCAM_FACAUTOK_PC_DeBug
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

extern char g_acalBVCAM_FACAUTOK_WorkingFolder[MAX_PATH];
extern char g_acalBVCAM_FACAUTOK_SourceFolder[MAX_PATH];
extern char g_acalBVCAM_FACAUTOK_OutputFolder[MAX_PATH];

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

/**
*  @}
*/
