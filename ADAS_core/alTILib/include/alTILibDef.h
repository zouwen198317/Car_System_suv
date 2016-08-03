
#pragma once

/**
  *  \addtogroup TILib
  *  @{
  */

#ifdef WIN32

#include "c6xsim/C6xSimulator_type_modifiers.h"

#ifdef _DEBUG
#pragma comment(lib, "alTILib_d.lib")
#else
#pragma comment(lib, "alTILib.lib")
#endif

#endif

#ifdef __cplusplus
extern "C"
{
#endif

	/** \brief Define the available size of L2 internal cache. */
	extern const unsigned int g_ulL2Size;
    /** \brief Define the address pointer of internal L2 cache for DSP processing. The cache size is 192kbytes */
    extern void * g_alTILIB_pvL2_addr_DSP;
    /** \brief Define the address pointer of internal L2 cache for DMA processing. The cache size is 192kbytes. */
    extern void * g_alTILIB_pvL2_addr_DMA;

#ifdef __cplusplus
}
#endif

/**
  *  @}
  */
