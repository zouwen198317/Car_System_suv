
#pragma once

#ifdef __cplusplus
extern "C" {
#endif // END #ifdef __cplusplus

#include "mtype.h"
#include "alPartLUT_v1_Def.h"
#include "dat_copy.h"

/**
  *  \addtogroup BirdView
  *  @{
  */


#define _EAGLE_GP_      (1)     // Eagle GP
#define _EAGLE_SIM_     (2)     // Eagle simulator 

#define _CAR_MODEL_     _EAGLE_SIM_  // can be _EAGLE_GP_ or _EAGLE_GP_

#if (_CAR_MODEL_ == _EAGLE_GP_)
  #define NULL_IDX_NUM      (31)
  #define SWITCH_BIT_SHIFT  (27)

#elif (_CAR_MODEL_ == _EAGLE_SIM_)
  #define NULL_IDX_NUM      (7)
  #define SWITCH_BIT_SHIFT  (29)
#endif  
  
//////////////////////////////////////////////////////////////////////////
typedef struct {
    int min_row;
    int max_row;
    int min_col;
    int max_col;
} alPartLUT_v1_Range_t;

typedef struct 
{

	unsigned int IMoffset;//image offset;for ch[]=startY*720+startX;for srcIMInfo[]=startY*720
	unsigned int size;//(pixel#)size of mapped source image
	unsigned int startX;//coordinate of mapped source image
	unsigned int startY;
	unsigned int endX;
	unsigned int endY;
	unsigned int width;//=endX-startX+1;
	unsigned int height;//=endY-startY+1
	unsigned int switchInfo;

} alPartLUT_v1_SourceStruct;//4*9=36

typedef struct 
{
	unsigned int cacheByte;//(byte)=size*4+ch[0~chIdx].size*2
	unsigned int LUToffset;//start LUT pixel data of g_MLUT_YUV_sorted(left-top is zero)
	//[1]=(startY+BV.TopY)*720+(startX+BV.LeftX). start pixel of FullBV at OSD. @runtime calculation  
	//[0]=(startY+DV.TopY)*720+(startX+DV.LeftX). start pixel of RightBV at OSD. @runtime calculation  
	unsigned int OSDoffset[2];
	unsigned int size;//(pixel#)size of each LUT block
	unsigned int startX;//coordinate of each LUT block at g_MLUT_YUV_unsorted(left-top is zero)
	unsigned int startY;
	unsigned int endX;
	unsigned int endY;
	unsigned int chIdx;//#+1 of mapped source channels 
    unsigned int singleChIdx; // indicate if single ch
    BOOL bEnableGAE; // indicate if single ch
	alPartLUT_v1_SourceStruct *ch;//each source image channel
} alPartLUT_v1_LUTStruct;//10*4=40

typedef struct
{

	unsigned int LUTIdx;//#+1 of (divided LUTs)/(headers)
	//unsigned int singleChIdx;//#+1 of LUT with single channel
	alPartLUT_v1_LUTStruct *header;//each header

} alPartLUT_v1_HeaderStruct;//2*4+40*8+36*12=760 bytes(8 blocks)



/**
    \brief Do BV Look-up table partition.
*/
void alPartLUT_v1_DoPartition(alPartLUT_v1_HeaderStruct *pMLUT, unsigned int *pMLUT_YUV, int mem_budget, alPartLUT_v1_LUTSet_t *pSet);

/** 
    \brief Do table look-up to generate image.
    \param ch_img [IN] Store the source images buffers.
    \param img_width [IN] The width of the source image.
    \param img_height [IN] The height of the source image.
    \param alPartLUT_v1_LUTSet_t [IN] The look-up table.
    \param dst_buf [OUT] The buffer the store the generated image.
*/
void alPartLUT_v1_DoTableLookup(UINT8 *ch_img[], UINT16 img_width, UINT16 img_height, alPartLUT_v1_LUTSet_t *pSet, UINT8 *dst_buf);

#ifdef WIN32
/*
    \brief To save the specified LUT (BV like) to a header file.
    \param pSet [IN] The alPartLUT_v1_LUTSet_t struct to indicate the LUT to be stored.
    \param entry_num [IN] the maximum entry number of the data.
    \param lMaxBlockCount [IN] the maximum block cout of the partitioning. (This will limit the output size of alPartLUT_v1_LUTSet_t)
    \param pcPrefix [IN] To indicate which type of this LUT set. ex. "BV", "AV".
    \param pwcFileName [IN] The filename to write the header data.
    \return None.
*/
void alPartLUT_v1_SaveLUTDataToHeaderFile(alPartLUT_v1_LUTSet_t * pSet, INT32 entry_num, char * pcPrefix, wchar_t * pwcFileName);
#endif


/**
  *  @}
  */

#ifdef __cplusplus
}
#endif // END #ifdef __cplusplus

