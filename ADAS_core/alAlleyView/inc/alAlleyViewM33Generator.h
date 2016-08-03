
/***********************************************************************************************

Release note: 
20130314 - Chinson: first release
20130315 - Chinson: (1) Delete parameters eDestPlaneOriginOffsetX and eDestPlaneOriginOffsetY
                    (2) Add parameters lVCOriginOnDestPlaneX, lVCOriginOnDestPlaneY : indicate 
                        the (X,Y) origin position of virtual camera on destination plane
20130319 - Chinson: (1) Delete parameters lVCOriginOnDestPlaneX and lVCOriginOnDestPlaneY
                    (2) Add parameters lDestPlaneOriginOffsetX, lDestPlaneOriginOffsetY: indicate 
                        the (X,Y) origin position offset of virtual camera on destination plane
20130322 - Chinson: (1) Add some additional comments for "alAlleyViewMatrixGenerator"
                    (2) Add #pragma once macro
20130401 - Chinson: (1) Pitch Angle 改為向上為正.

************************************************************************************************/

#include "mtype.h"
#include "alAlleyViewDef.h"

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
  *  \defgroup alALLEYVIEW    alAlleyView
  *  @{
  */



/** 
    \brief To generate the perspective matrix according to the input parameters (pPTParams). The output type of matrix is FLOAT64. 
           The input for M3x3 is in pixel on real camera and output is in pixel on destination plane. The output matrix can be used 
           by PerformCoordinatesTransform defined in "PerspectiveTransform.h".
    \param pPTParams [IN] Define the space relation between real camera and virtual camera.
    \param peM33 [OUT] Output the generated matrix.
    \see alAlleyViewParams, PerformCoordinatesTransform
*/
void alAlleyViewM33Generator(alAlleyViewParams * pAVParams, FLOAT64 * peM33);

/** 
    \brief To do the single point coordinates transform from alley view image plane to 2D fishey model sphere plane. 
           The input coordinates(a_peSrcX, a_peSrcY) are in pixel on real camera and output coordinates (a_peDestX, a_peDestY, a_peDestZ) 
           are in mm on destination sphere plane. 
    \param a_aeM33 [IN] The M33 matrix to do the coordinates transform.
    \param a_eSrcX [IN] The source coordinates array - X.
    \param a_eSrcY [IN] The source coordinates array - Y.
    \param a_peDestX [OUT] The output coordinates array - X.
    \param a_peDestY [OUT] The output coordinates array - Y.
    \see alAlleyViewParams, alAlleyViewM33Generator
*/void alAlleyViewCoordinatesTransform2D(FLOAT64 a_aeM33[9], FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY);

/** 
    \brief To do the batch coordinates transform from alley view image plane to 2D fishey model sphere plane. 
           The input coordinates(a_peSrcX, a_peSrcY) are in pixel on real camera and output coordinates (a_peDestX, a_peDestY, a_peDestZ) 
           are in mm on destination sphere plane. 
    \param a_aeM33 [IN] The M33 matrix to do the coordinates transform.
    \param a_peSrcX [IN] The source coordinates array - X.
    \param a_peSrcY [IN] The source coordinates array - Y.
    \param a_peDestX [OUT] The output coordinates array - X.
    \param a_peDestY [OUT] The output coordinates array - Y.
    \see alAlleyViewParams, alAlleyViewM33Generator
*/
void alAlleyViewCoordinatesTransform2D_Batch(FLOAT64 a_aeM33[9], FLOAT64 * a_peSrcX, FLOAT64 * a_peSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, UINT32 a_ulCount);

/** 
    \brief To do the batch coordinates transform from alley view image plane to 3D fishey model sphere plane. 
           The input coordinates(a_peSrcX, a_peSrcY) are in pixel on real camera and output coordinates (a_peDestX, a_peDestY, a_peDestZ) 
           are in mm on destination sphere plane. 
    \param a_aeM33 [IN] The M33 matrix to do the coordinates transform.
    \param a_eSrcX [IN] The source coordinates array - X.
    \param a_eSrcY [IN] The source coordinates array - Y.
    \param a_peDestX [OUT] The output coordinates array - X.
    \param a_peDestY [OUT] The output coordinates array - Y.
    \param a_peDestZ [OUT] The output coordinates array - Z.
    \see alAlleyViewParams, alAlleyViewM33Generator
*/
void alAlleyViewCoordinatesTransform3D_Batch(FLOAT64 a_aeM33[9], FLOAT64 * a_peSrcX, FLOAT64 * a_peSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ, UINT32 a_ulCount);

/** 
    \brief To do the single point coordinates transform from alley view image plane to 3D fishey model sphere plane. 
           The input coordinates(a_peSrcX, a_peSrcY) are in pixel on real camera and output coordinates (a_peDestX, a_peDestY, a_peDestZ) 
           are in mm on destination sphere plane. 
    \param a_aeM33 [IN] The M33 matrix to do the coordinates transform.
    \param a_peSrcX [IN] The source coordinates array - X.
    \param a_peSrcY [IN] The source coordinates array - Y.
    \param a_peDestX [OUT] The output coordinates array - X.
    \param a_peDestY [OUT] The output coordinates array - Y.
    \param a_peDestZ [OUT] The output coordinates array - Z.
    \see alAlleyViewParams, alAlleyViewM33Generator
*/
void alAlleyViewCoordinatesTransform3D(FLOAT64 a_aeM33[9], FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ);

/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
