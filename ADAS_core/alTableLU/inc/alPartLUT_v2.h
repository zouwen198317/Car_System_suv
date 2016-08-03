
#pragma once

#include "alLUT_v2_Def.h"
#include "alPartLUT_v1_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

//referenced souce channel(left, right, front, back)
#define REF_CHANNEL_NUM (4)

typedef struct 
{
    alPartLUT_v1_Area2_t          dst_area;
    INT32           ch_num;         // number of referenced source channel
    alPartLUT_v1_ChannelArea2_t  ch_area[REF_CHANNEL_NUM];     // referenced area in souce channel image
    UINT32          lut_offset;     // start offset (from lut_data) of this partition block
    UINT32          lut_num;        // number of LUT entries for this partitioned block
    char            bEnableGAE;     // indicate if this block sould enable Global AE offset
    char            bEnableL2;      // using L2 to speed up process time
    char            bBlackArea;     // indicate if all pixel in block is black pixel  
    char            reserved[1];   
} alPartLUT_v2_3DBlockInfo_t;

typedef struct 
{
    INT32 blk_num;                                    // number of partitioned blocks
    alPartLUT_v2_3DBlockInfo_t  BInfo[MAX_BV_BLOCK_INFO_NUM];   // block information
//    UINT64  *lut_data;                        // LUT entries of partitioned blocks
    UINT8  *lut_data;                        // LUT entries of partitioned blocks    
    INT32 lut_data_size;                              // 
} alPartLUT_v2_Def;



//void TABLELU_CreatePerfLUT(TABLELUT_Def * a_ptTable);
///** \brief To process the table LU according to original full look-up table. */
//void TABLELU_ProcessFullLU_Top(TABLELUT_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage);
//
//void TABLELU_ProcessFullLU_Rear(TABLELUT_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage);
//
void alPartLUT_v2_BlockClassify(alPartLUT_v2_Def * a_pSet, UINT32 lutIdx);
void alPartLUT_v2_Process3DAVM(UINT8 ** a_pucSrcBuffer, UINT16 a_uwImageWidth, UINT16 a_uwImageHeight, alPartLUT_v2_Def * a_pSet, UINT8 * a_pData, UINT8 * a_pucDestBuffer, UINT32 a_uLutIdx);

#ifdef __cplusplus
}
#endif

