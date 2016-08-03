
/***********************************************************************************************

Release note: 
20130314 - Chinson: first release
20130315 - Chinson: (1) Delete parameters eDestPlaneOriginOffsetX and eDestPlaneOriginOffsetY
                    (2) Add parameters lVCOriginOnDestPlaneX, lVCOriginOnDestPlaneY : indicate 
                        the (X,Y) origin position of virtual camera on destination plane
20130319 - Chinson: (1) Delete parameters lVCOriginOnDestPlaneX and lVCOriginOnDestPlaneY
                    (2) Add parameters lDestPlaneOriginOffsetX, lDestPlaneOriginOffsetY: indicate 
                        the (X,Y) origin position offset of virtual camera on destination plane
20130322 - Chinson: (1) Add some additional comments for "AlleyViewMatrixGenerator"
                    (2) Add #pragma once macro
20130401 - Chinson: (1) Pitch Angle 改為向上為正.

************************************************************************************************/

#include "mtype.h"
#include "AVM3DDef.h"

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

/**
  *  \addtogroup AVM3D
  *  @{
  */

/** \brief Define the parameters structure for matrix generator.

                                                        side view:

                                                          destination plane
                                                              _                 
               /\                                            | |               \ _  
               \/  real camera                               | |                |_|     virtual camera
    ______                                   =>              | |               /
    \     \                                                  |_|
     \     \   camera image plane                                        
      \_____\                                                             
                                                        top view:

                                                          destination plane 
                                                                _
                                                               / /  
                                                              / / 
                                                             / /          
                                                            /_/        |    
                                                                      
                                                                    _  /\  
                                                                       \/   virtual camera

      Definition:
      1. Pitch Angle : 向上為正
      2. Yaw Angle : 向右為正
      3. Roll Angle : 順時針為正

*/
typedef struct 
{

    /** \brief The width of the destination image plane. (in pixel) */
    UINT32  ulDestPlaneWidth;
    /** \brief The height of the destination image plane. (in pixel) */
    UINT32  ulDestPlaneHeight;
    /** \brief The width of the camera image plane. (in pixel) */
    UINT32  ulCameraPlaneWidth;
    /** \brief The height of the camera image plane. (in pixel) */
    UINT32  ulCameraPlaneHeight;

    /** \brief The real camera X position under the world coordinator. (in milimeter) */
    INT32 lRealCameraX;
    /** \brief The real camera Y position under the world coordinator. (in milimeter) */
    INT32 lRealCameraY;
    /** \brief The real camera Z position under the world coordinator. (in milimeter) */
    INT32 lRealCameraZ;

    /** \brief The virtual camera X position under the world coordinator. (in milimeter) */
    INT32 lVitrualCameraX;
    /** \brief The virtual camera Y position under the world coordinator. (in milimeter) */
    INT32 lVitrualCameraY;
    /** \brief The virtual camera Z position under the world coordinator. (in milimeter) */
    INT32 lVitrualCameraZ;

    /** \brief The current pitch angle of the real camera. (in degree) */
    FLOAT64 eCameraPitchAngle;
    /** \brief The current yaw angle of the real camera. (in degree) */
    FLOAT64 eCameraYawAngle;
    /** \brief The current roll angle of the real camera. (in degree) */
    FLOAT64 eCameraRollAngle;

    /** \brief The custom roll angle of the real camera. (in degree). This is used to roll the rear/left/right image. */
    FLOAT64 eCameraCustomRoll;

#if 0
    /** \brief The horizontal FOV of the real camera. (in degree) */
    FLOAT64 eCameraFOV_H;
#endif

    /** \brief The focal length of the real camera. (in mm) */
    FLOAT64 eCameraFocalLength;

#if 0
    /** \brief The horizontal FOV of the virtual camera. (in degree) */
    FLOAT64 eVCCameraFOV_H;
#endif

    /** \brief The focal length of the virtual camera. (in mm) */
    FLOAT64 eVCCameraFocalLength;

    // Define Rotation:
    /** \brief The designed destination pitch angle of the virtual camera. (in degradree) */
    FLOAT64 eDestPitchAngle;
    /** \brief The designed destination yaw angle of the virtual camera. (in degree) */
    FLOAT64 eDestYawAngle;
    /** \brief The designed destination roll angle of the virtual camera. (in degree)  */
    FLOAT64 eDestRollAngle;

    /** \brief The Rotation Matrix of the virtual camera. (0:BV2VC 1:VC2BV)  */
    FLOAT64 aeRotationMatrixVC[2][9];

    /** \brief The Translation Matrix of the virtual camera. (0:BV2VC 1:VC2BV)  */
    FLOAT64 aeTranslationMatrixVC[2][9];

} AVM3DGenerateParams;

///////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_MatrixGeneratorStep1(AVM3DGenerateParams * a_ptAVM3DParam, FLOAT64 * a_peM33);

///////////////////////////////////////////////////////////////////////////////////////////////////
void AVM3D_MatrixGeneratorStep2(AVM3DGenerateParams * a_ptAVM3DParam, FLOAT64 * a_peM33);

/** 
    \brief To generate the perspective matrix according to the input parameters of each virtual view. The output type of matrix is FLOAT64.
	use for morphing around type
    \param a_ptAVMCfg [IN] parameters of each virtual view
    \param a_peM33 [OUT] Output the generated matrix.
    \see 
*/
void AVM3D_MatrixGeneratorBVTransform(alAVM3D_CfgSingleView * a_ptAVMCfg, FLOAT64 *a_peRT4x4);

/** 
    \brief To generate the perspective matrix according to the input parameters (pPTParams). The output type of matrix is FLOAT64. 
           The input for M3x3 is in pixel on real camera and output is in pixel on destination plane. The output matrix can be used 
           by PerformCoordinatesTransform defined in "PerspectiveTransform.h".
    \param a_ptNVParam [IN] Define the space relation between real camera and virtual camera.
    \param a_peM33 [OUT] Output the generated matrix.
    \see AVM3DGenerateParams, PerformCoordinatesTransform
*/
void AVM3D_MatrixGenerator(AVM3DGenerateParams * a_ptAVM3DParam, FLOAT64 * a_peM33);

/** 
    \brief To do the batch coordinates transform from normal view image plane to 3D fishey model sphere plane. 
           The input coordinates(a_peSrcX, a_peSrcY) are in pixel on real camera and output coordinates (a_peDestX, a_peDestY, a_peDestZ) 
           are in mm on destination sphere plane. 
    \param a_aeM33 [IN] The M33 matrix to do the coordinates transform.
    \param a_peSrcX [IN] The source coordinates array - X.
    \param a_peSrcY [IN] The source coordinates array - Y.
    \param a_peSrcZ [IN] The source coordinates array - Z.
    \param a_peDestX [OUT] The output coordinates array - X.
    \param a_peDestY [OUT] The output coordinates array - Y.
    \param a_peDestZ [OUT] The output coordinates array - Z.
    \see AVM3DGenerateParams, AVM3D_MatrixGenerator
*/
void AVM3D_CoordinatesTransform3D_Batch(FLOAT64 a_aeM33[9], FLOAT64 * a_peSrcX, FLOAT64 * a_peSrcY, FLOAT64 * a_peSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ, UINT32 a_ulCount);

/** 
    \brief To do the single point coordinates transform from normal view image plane to 3D fishey model sphere plane. 
           The input coordinates(a_peSrcX, a_peSrcY) are in pixel on real camera and output coordinates (a_peDestX, a_peDestY, a_peDestZ) 
           are in mm on destination sphere plane. 
    \param a_aeM33 [IN] The M33 matrix to do the coordinates transform.
    \param a_peSrcX [IN] The source coordinates - X.
    \param a_peSrcY [IN] The source coordinates - Y.
    \param a_peSrcZ [IN] The source coordinates - Z.
    \param a_peDestX [OUT] The output coordinates - X.
    \param a_peDestY [OUT] The output coordinates - Y.
    \param a_peDestZ [OUT] The output coordinates - Z.
    \see AlleyViewParams, AlleyViewM33Generator
*/
void AVM3D_CoordinatesTransform3D(FLOAT64 a_aeM33[9], FLOAT64 a_eSrcX, FLOAT64 a_eSrcY, FLOAT64 a_eSrcZ, FLOAT64 * a_peDestX, FLOAT64 * a_peDestY, FLOAT64 * a_peDestZ);


/**
  *  @}
  */

#ifdef __cplusplus
}
#endif
