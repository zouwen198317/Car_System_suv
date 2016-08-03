
#pragma once

#ifndef WIN32

#include <csl_dat.h>

#else

#define EDMA_SUPPORT 1
#define DAT_SUPPORT 1

#ifdef __cplusplus
extern "C" {
#endif // END #ifdef __cplusplus

/**
  *  \addtogroup TILib
  *  @{
  */

#define DAT_1D2D      0x000000D0
#define DAT_2D1D      0x00000070
#define DAT_2D2D      0x000000F0


/* special magic transfer IDs */
#define DAT_XFRID_WAITALL   0xFFFFFFFF
#define DAT_XFRID_WAITNONE  0xFFFF0010

typedef unsigned int   Uint32;
typedef unsigned short Uint16;
typedef unsigned char  Uint8;

Uint32 DAT_copy(void *src , void *dst , Uint16 byteCnt);
Uint32 DAT_fill(void *dst , Uint16 byteCnt, Uint32 *value);
void   DAT_wait(Uint32 id);

Uint32 DAT_copy2d(Uint32 type, void *src, void *dst, Uint16 lineLen, Uint16 lineCnt, Uint16 linePitch);
Uint32 DAT_copy2d_lut(Uint32 type, void const * src, void * dst, Uint16 lineLen, Uint16 lineCnt, Uint16 linePitch, Uint16 PixelDepth);

Uint32 DAT_copy2d2d(void *src, void *dst, Uint16 lineLen,
        Uint16 lineCnt, Uint16 linePitch_src, Uint16 linePitch_dst);

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif // END #ifdef __cplusplus

#endif

