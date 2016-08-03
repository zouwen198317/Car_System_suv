
#pragma once

#include "Core/ModeDefine.h"

#if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC

/** \brief Test Config File #1. */
void TEST_ConfigFile1();

/** \brief Test Config File #2. */
void TEST_ConfigFile2();

/** \brief Test Config File #3. */
void TEST_ConfigFile3();

/** \brief Test Config File FMv2. */
void TEST_ConfigFile_FMv2();

/** \brief Test Config File for AutoK. */
void TEST_ConfigFileFactoryAutoK();

/** \brief Test Params File for AutoK. */
void TEST_ParamsFileFactoryAutoK();

/** \brief Export the test image for BV Mean ROI. */
void TEST_ExportBVMeanROIImage(wchar_t * a_pwcOutImageFolder);

/** \brief Export the test image for Single View Noise ROI. */
void TEST_ExportSingleViewNoiseROIImage(wchar_t * a_pwcOutImageFolder);

/** \brief Export the test image for trail lines. */
void TEST_ExportTrailLineImage(wchar_t * a_pwcSrcImageFolder, wchar_t * a_pwcOutImageFolder);

/** \brief Export the test image for lens distortion correction by Fisheye Model. */
void TEST_ExportUndistortedImage(wchar_t * a_pwcSrcImageFolder, wchar_t * a_pwcOutImageFolder, FLOAT32 a_fScale);

#endif // #if EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC
