
#pragma once

#include "mtype.h"

#define MAX_DISPLAY_AREA_SIZE_X 720
#define MAX_DISPLAY_AREA_SIZE_Y 480
#define MAX_L2_BLOCK_LUT_NUM    (MAX_DISPLAY_AREA_SIZE_X*MAX_DISPLAY_AREA_SIZE_Y)

typedef struct {
    UINT16 start_row;   // start row of the area
    UINT16 start_col;   // start column of the area
    UINT16 width;       // area width, 0 means this area is not available
    UINT16 height;      // area height, 0 means this area is not available
} alPartLUT_v1_Area2_t;

typedef struct 
{
    UINT16 ch_idx;      // channel_idx;
    UINT16 start_row;   // start row of the area
    UINT16 start_col;   // start column of the area
    UINT16 width;       // area width, 0 means this area is not available
    UINT16 height;      // area height, 0 means this area is not available
} alPartLUT_v1_ChannelArea2_t;
      
typedef struct 
{
    alPartLUT_v1_Area2_t          dst_area;
    INT32           ch_num;         // number of referenced source channel
    alPartLUT_v1_ChannelArea2_t  ch_area[2];     // referenced area in souce channel image
    UINT32          lut_offset;     // start offset (from lut_data) of this partition block
    UINT32          lut_num;        // number of LUT entries for this partitioned block
    BOOL            bEnableGAE;     // indicate if this block sould enable Global AE offset
}   alPartLUT_v1_BlockInfo_t;

//#define MAX_BV_BLOCK_INFO_NUM (256) // change back to 256 because of FW issue 
#define MAX_BV_BLOCK_INFO_NUM (1024) // modifyed by chinson: (1024) Increase the partitioned block number to decrease the possibility of partion failed. However this increasing may cause frame rate droped.

typedef struct 
{
    INT32 blk_num;                                    // number of partitioned blocks
    alPartLUT_v1_BlockInfo_t  BInfo[MAX_BV_BLOCK_INFO_NUM];   // block information
    UINT32  *lut_data;                        // LUT entries of partitioned blocks
    INT32 lut_data_size;                              // 
} alPartLUT_v1_LUTSet_t;

