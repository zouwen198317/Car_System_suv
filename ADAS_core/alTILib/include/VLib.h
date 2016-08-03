
#pragma once

/**
  *  \addtogroup TILib
  *  @{
  */

#ifdef __cplusplus
extern "C" {
#endif // END #ifdef __cplusplus

#ifdef WIN32
//#pragma comment(lib, "vlib.lib")
#pragma comment(linker, "/NODEFAULTLIB:LIBCD.lib")
#pragma warning(disable : 4068) 
#endif

#include "alTILibDef.h"

#ifdef WIN32
#include "vlib/VLIB_prototypes.h"
#else
#include "VLIB_prototypes.h"
#endif

int VLIB_extractLumaFromYUYV(   unsigned char* restrict inputImage,
                                unsigned short inputWidth,
                                unsigned short inputPitch,
                                unsigned short inputHeight,
                                unsigned char* restrict outputImage);


/** \brief Deinterleaves color channels of an interleaved YUV422 data block. 
           Given pixels in the interleaved format, this function separates the three channels into separate buffers. 
           The width must be a multiple of 8, while input and output buffers must be 64-bit aligned.
    \param src_buf [IN] Interleaved luma/chroma, YUYV format.
    \param width [IN] Width of input image (number of luma pixels).
    \param pitch [IN] Pitch of input image (number of luma pixels).
    \param height [IN] Height of input image(number of luma pixels).
    \param y [OUT] Luma plane (8-bit).
    \param cb [OUT] Cb chroma plane (8-bit).
    \param cr [OUT] Cr chroma plane (8-bit).
*/
int VLIB_convertYUYVint_to_YUVpl(   const unsigned char *src_buf,  
                                    int width,
                                    int pitch,
                                    int height,
                                    unsigned char *y,
                                    unsigned char *cb,
                                    unsigned char *cr                                        
                                    );

/** \brief Interleaves YUV channels of a planar YUV422 data block.. 
           Given data in the planar format, this function interleaves the data to the YUV422 format. 
           The width must be a multiple of 8, while input and output buffers must be 64-bit aligned.
    \param y [IN] Luma plane (8-bit).
    \param cb [IN] Cb chroma plane (8-bit).
    \param cr [IN] Cr chroma plane (8-bit).
    \param width [IN] Width of input image (number of luma pixels).
    \param pitch [IN] Pitch of input image (number of luma pixels).
    \param height [IN] Height of input image(number of luma pixels).
    \param yc [OUT] Interleaved luma/chroma, YUYV format.
*/
int VLIB_convertYUYVpl_to_YUVint(   const unsigned char *restrict y, /* Luma plane (8-bit) */
                                    const unsigned char *restrict cb, /* Cb chroma plane (8-bit) */
                                    const unsigned char *restrict cr, /* Cr chroma plane (8-bit) */
                                    int width,
                                    int pitch,
                                    int height,
                                    unsigned char *restrict yc); /* Interleaved luma/chroma */

#if 0 // already defined in VLIB_prototypes.h & vlib.lib
/** \brief Given pixels in the semiplanar format, this function separates the chroma channels into separate buffers. 
           The width must be a multiple of 8, while input and output buffers must be 64-bit aligned.
           If the input format is cbcr, then the output should be swapped.
    \param crcb [IN] Interleaved chroma.
    \param width [IN] width (number of luma pixels).
    \param pitch [IN] pitch (number of luma pixels).
    \param height [IN] height (number of luma pixels).
    \param cr [IN] Cr chroma plane (8-bit).
    \param cb [IN] Cb chroma plane (8-bit).
*/
int VLIB_convertUYVYsemipl_to_YUVpl(    const unsigned char * crcb,         /* Interleaved chroma */
                                        int width,                          /* width (number of luma pixels) */
                                        int pitch,                          /* pitch (number of luma pixels) */
                                        int height,                         /* height (number of luma pixels)*/
                                        unsigned char *restrict cr,         /* Cr chroma plane (8-bit) */
                                        unsigned char *restrict cb);        /* Cb chroma plane (8-bit) */
#endif

#ifdef __cplusplus
}
#endif // END #ifdef __cplusplus

/**
*  @}
*/
