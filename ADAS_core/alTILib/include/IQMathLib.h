
#pragma once

/**
  *  \addtogroup TILib
  *  @{
  */

#include "alTILibDef.h"

#ifdef WIN32
//#pragma comment(lib, "IQmath_pc.lib") => Use obj files to avoid confliction of C6xSimulator.
#include "iqmath/IQmath.h"
#include "iqmath/IQmath_inline.h"
#else
#include "IQmath.h"
#include "IQmath_inline.h"
#endif

/**
  *  @}
  */
