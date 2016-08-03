
#pragma once

#include "mtype.h"

#define PC_USE_INTRINSIC_CODE    1

#ifdef __cplusplus
extern "C" {
#endif // END #ifdef __cplusplus

#ifdef WIN32
#include "c6xsim/C6xSimulator_type_modifiers.h"
#endif

/** 
    \brief To sharpen an image by un-sharp masking method. The processing area should not include the 2D boundary of the buffer.
    \param a_pucImgBuf [IN] The source image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pucImgOutBuf [OUT] The destination image buffer which contain the processed image.
*/
void ImgProc_SharpenByUnSharpMask(  UINT8 * __restrict a_pucImgYUYVBuf, 
                                    const UINT32 a_ulImgWidth, const UINT32 a_ulImgHeight, 
                                    const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                                    const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                                    const UINT8 a_ucWeightingCurveIndex,
									UINT8 * a_pucPixelWeightingTable,
                                    const UINT8 a_ucSharpnessLevel,
                                    const UINT32 a_aulBlockRegion[][4],
                                    const UINT8 a_ucBlockCnt
                                    );

/** 
    \brief To extract Y only image from YUYV image. 
    \param a_pucImgYUYVBuf [IN] The source YUYV image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pucImgYBuf [INOUT The destination Y image buffer.
*/
void ImgProc_YExtractOnly(  UINT8 * __restrict a_pucImgYUYVBuf,  
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            UINT8 * __restrict a_pucImgYBuf);

/** 
    \brief To seperate YUYV interleaved image to YUV planar image
    \param a_pucImgYUYVBuf [IN] The source YUYV image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pucImgYBuf [INOUT The destination Y image buffer.
    \param a_pucImgCbBuf [INOUT The destination Cb image buffer.
    \param a_pucImgCrBuf [INOUT The destination Cr image buffer.
*/
void ImgProc_YUYVint2YUVpl( const UINT8 * __restrict a_pucImgYUYVBuf,  
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            UINT8 * __restrict a_pucImgYBuf,
                            UINT8 * __restrict a_pucImgCbBuf,
                            UINT8 * __restrict a_pucImgCrBuf);

/** 
    \brief To seperate YUYV interleaved image to YUV planar image
    \param a_pucImgYUYVBuf [IN] The source YUYV image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pucImgYBuf [INOUT The destination Y image buffer.
    \param a_pucImgCbBuf [INOUT The destination Cb image buffer.
    \param a_pucImgCrBuf [INOUT The destination Cr image buffer.
*/
void ImgProc_YUYVpl2YUVint( const UINT8 * __restrict a_pucImgYBuf,
                            const UINT8 * __restrict a_pucImgCbBuf,
                            const UINT8 * __restrict a_pucImgCrBuf,
                            const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                            const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                            const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                            UINT8 * __restrict a_pucImgYUYVBuf);

/** 
    \brief To do 3x3 convolution in 8 bit single channel image.
    \param a_pucImgBuf [IN] The source YUYV image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pwImgOutBuf [OUT] The destination Y image buffer.
*/
void ImgProc_3x3Convolution(    const UINT8 * __restrict a_pucImgBuf, 
                                const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                                const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                                const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                                const INT8 * __restrict a_pcMask,
                                INT16 wShift,
                                UINT8 * __restrict a_pucImgOutBuf
                                );

/** 
    \brief To do 5x5 convolution in 8 bit single channel image.
    \param a_pucImgBuf [IN] The source YUYV image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pwImgOutBuf [OUT] The destination Y image buffer.
*/
void ImgProc_5x5Convolution(    const UINT8 * __restrict a_pucImgBuf, 
                                const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                                const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                                const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                                const INT8 * __restrict a_pcMask,
                                INT16 wShift,
                                UINT8 * __restrict a_pucImgOutBuf
                                );

/** 
    \brief To do 7x7 convolution in 8 bit single channel image.
    \param a_pucImgBuf [IN] The source YUYV image buffer.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
    \param a_pwImgOutBuf [OUT] The destination Y image buffer.
*/
void ImgProc_7x7Convolution(    const UINT8 * __restrict a_pucImgBuf, 
                                const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                                const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                                const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                                const INT8 * __restrict a_pcMask,
                                INT16 wShift,
                                UINT8 * __restrict a_pucImgOutBuf
                                );


/** 
    \brief Down scaling the image to 1/4 width & 1/4 height & smooth the image by 3x3 conv
    \param a_pucSrc [IN] The source image buffer - 8 bit.
    \param a_pucTemp [IN] The temp image buffer - 8 bit.
    \param a_pucDst [OUT] The destination image buffer - 8 bit.
    \param a_lSrcWidth [IN] The width of the source buffer.
    \param a_lDstWidth [IN] The width of the desination buffer.
    \param a_lBlkWidth [IN] The width of the block area to be processed. 
    \param a_lBlkHeight [IN] The height of the block area to be processed. 
*/
void ImgProc_QuarterDownScalingWithSmooth(UINT8 * a_pucSrc,
                                          UINT8 * a_pucTemp, 
                                          UINT8 * a_pucDst, 
                                          INT32 a_lSrcWidth, 
                                          INT32 a_lDstWidth, 
                                          INT32 a_lBlkWidth, 
                                          INT32 a_lBlkHeight,
                                          INT32 a_rate);

/** 
    \brief Down scaling the image to 1/4 width & 1/4 height
    \param a_pucSrc [IN] The source image buffer - 8 bit.
    \param a_pucDst [OUT] The destination image buffer - 8 bit.
    \param a_lSrcWidth [IN] The width of the source buffer.
    \param a_lDstWidth [IN] The width of the desination buffer.
    \param a_lBlkWidth [IN] The width of the block area to be processed. 
    \param a_lBlkHeight [IN] The height of the block area to be processed. 
*/
void ImgProc_QuarterDownScaling(    const UINT8 *restrict a_pucSrc,
                                    UINT8 *restrict a_pucDst, 
                                    INT32 a_lSrcWidth, 
                                    INT32 a_lDstWidth, 
                                    INT32 a_lBlkWidth, 
                                    INT32 a_lBlkHeight
                                    );

/** 
    \brief Calculate the mean value of the specified area.
    \param a_pucImgYUYVBuf [IN] The source image buffer - 8 bit.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
	\param a_pucLumaMean [OUT] The luminance mean value for the processed area.
	*/
void ImgProc_ROIMean(   UINT8 * restrict a_pucImgYUYVBuf, 
                        const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                        const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                        const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
						UINT8 * a_pucLumaMean
                        );
/** 
    \brief Calculate the seperated means in the ROI of the image. The pixels with pixel value < a_ucLumaTh is included in a_pulMeanL 
	       and the pixels with pixel value >= a_ucLumaTh is included in a_pulMeanH.
    \param a_pucImgYUYVBuf [IN] The source image buffer - 8 bit.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
	\param a_ucLumaTh [IN] The luminance threshold for the seperated mean values.
	\param a_pulLumaMean_L [OUT] The luminance mean value for those pixels with luminance < a_ucLumaTh.
	\param a_pulCountMean_L [OUT] The pixel count for those pixels with luminance < a_ucLumaTh.
	\param a_pucLumaMean_H [OUT] The luminance mean value for those pixels with luminance >= a_ucLumaTh.
	\param a_pulCountMean_H [OUT] The pixel count for those pixels with luminance >= a_ucLumaTh.
	*/
void ImgProc_ROISeperateMean(   UINT8 * restrict a_pucImgYUYVBuf, 
                                const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                                const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                                const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
								const UINT8 a_ucLumaTh,
                                UINT8 * a_pcLumaMean,
								UINT8 * a_pucLumaMean_L,
								UINT32 * a_pulCountMean_L,
								UINT8 * a_pucLumaMean_H,
								UINT32 * a_pulCountMean_H
                                );

/** 
    \brief Noise estimation for specific image in specifed ROI area.
    \param a_pucImgYUYVBuf [IN] The source image buffer - 8 bit.
    \param a_ulBufferWidth [IN] The width of the buffer. The real image may not fill the whole width.
    \param a_ulBufferHeight [IN] The height of the buffer. The real image may not fill the whole height.
    \param a_ulProcStartX [IN] The starting X position of the area to be processed. 
    \param a_ulProcStartY [IN] The starting Y position of the area to be processed. 
    \param a_ulProcWidth [IN] The width of the area to be processed. 
    \param a_ulProcHeight [IN] The width of the area to be processed. 
	\param a_pulNoiseSum [IN] The noise summation of the specified area. This function support accumulate for different area, thus this parameter won't be initialized to zero before the calculation.
	*/
void ImgProc_NoiseEstimation(UINT8 * restrict a_pucImgYUYVBuf, 
                             const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                             const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                             const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                             UINT32 * a_pulNoiseSum);



#ifdef __cplusplus
}
#endif // END #ifdef __cplusplus

