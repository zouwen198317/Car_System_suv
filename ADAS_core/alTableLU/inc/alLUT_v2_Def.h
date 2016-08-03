
#pragma once

#include "mtype.h"
#include "atype.h"

#if 0
typedef struct
{

    /** \brief The width/height of the destination image buffer. This is the full size of the destination image size. This table LU may not inclue this full area. */
    alPointINT32 tDestImageBufferSize;
    
    /** \brief The start point of the processed area on the destination image buffer. */
    alPointINT32 tDestStartPoint;
    /** \brief The width/height of the processed area size on the destination image buffer. */
    alPointINT32 tDestAreaSize;

    /** \brief The total block count in the destination area size. */
    UINT16 uwBlockCount;

    /** \brief The blocks' rest data in the destination area size. */
    alRectINT32 * ptDestBlock;

    /** \brief Size of the source images. */
    alPointINT32 atSrcImageSize[EAGLEK3_CAMERA_NUM];

} TABLELUT_Param;
#endif

typedef enum 
{
    alLUT_v2_SHIFT_DECY_1    = 0,
    alLUT_v2_SHIFT_DECX_1    = 3,
    alLUT_v2_SHIFT_OFFSET_1  = 6,
    alLUT_v2_SHIFT_CAM_1     = 26,
    alLUT_v2_SHIFT_DECY_2    = 29,
    alLUT_v2_SHIFT_DECX_2    = 32,
    alLUT_v2_SHIFT_OFFSET_2  = 35,
    alLUT_v2_SHIFT_CAM_2     = 55,
    alLUT_v2_SHIFT_WEIGHT    = 58,
    alLUT_v2_SHIFT_ENABLE    = 63,
} alLUT_v2_SHIFT_FORMAT;

typedef enum 
{
    alLUT_v2_AND_DECY_1      = 0x7,
    alLUT_v2_AND_DECX_1      = 0x7,
    alLUT_v2_AND_OFFSET_1    = 0xFFFFF,
    alLUT_v2_AND_CAM_1       = 0x7,
    alLUT_v2_AND_DECY_2      = 0x7,
    alLUT_v2_AND_DECX_2      = 0x7,
    alLUT_v2_AND_OFFSET_2    = 0xFFFFF,
    alLUT_v2_AND_CAM_2       = 0x7,
    alLUT_v2_AND_WEIGHT      = 0x1F,
    alLUT_v2_AND_ENABLE      = 0x1,
} alLUT_v2_AND_FORMAT;

typedef struct
{

    /** \brief The width/height of the destination image buffer. This is the full size of the destination image size. This table LU may not inclue this full area. */
    alPointINT32 tDestImageBufferSize;
    
    /** \brief The start point of the processed area on the destination image buffer. */
    alPointINT32 tDestStartPoint;
    /** \brief The width/height of the processed area size on the destination image buffer. */
    alPointINT32 tDestAreaSize;

    /** \brief Size of the source images. */
    alPointINT32 atSrcImageSize[7];

    /** \brief Buffer size of the LUT, in bytes - pullTable. */
    UINT32 ulLUTDataSize;

    /** \brief Buffer of the look-up table. */
    UINT64 * pullTable;

} alLUT_v2_Def;


