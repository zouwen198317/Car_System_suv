
#include "alTILIBDef.h"

#define DSP_L2_SIZE     (192*1024)
const unsigned int g_ulL2Size = DSP_L2_SIZE;

#ifdef WIN32
static unsigned char g_alTILIB_pucL2_SRAM[DSP_L2_SIZE];
void * g_alTILIB_pvL2_addr_DSP = (void*)&(g_alTILIB_pucL2_SRAM[0]);
void * g_alTILIB_pvL2_addr_DMA = (void*)&(g_alTILIB_pucL2_SRAM[0]);
#else
void * g_alTILIB_pvL2_addr_DSP = (void *)0x10800000;
void * g_alTILIB_pvL2_addr_DMA = (void *)0x40800000;
#endif
