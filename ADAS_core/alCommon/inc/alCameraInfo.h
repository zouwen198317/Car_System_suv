
#pragma once

#include "mtype.h"

/**
*   \defgroup alCAMERAINFO    alCameraInfo
*   The module define the struct and some enum data whiche inclues camera information, such like time stamp, camera ID, .. etc.
*   @{
*/

/** \brief Define the flag for Camera ID. */
typedef enum
{

    /** \brief Indicate the camera belong to BV Left Camera. */
    alCAMERAINFO_BV_LEFT    = 0,
    /** \brief Indicate the camera belong to BV Right Camera. */
    alCAMERAINFO_BV_RIGHT   = 1,
    /** \brief Indicate the camera belong to BV Front Camera. */
    alCAMERAINFO_BV_FRONT   = 2,
    /** \brief Indicate the camera belong to BV Back Camera. */
    alCAMERAINFO_BV_BACK    = 3,
    /** \brief Indicate the camera belong to SV Left Camera. */
    alCAMERAINFO_SV_LEFT    = 4,
    /** \brief Indicate the camera belong to SV Right Camera. */
    alCAMERAINFO_SV_RIGHT   = 5,
    /** \brief Indicate the camera belong to WindShied Front Camera. */
    alCAMERAINFO_WS_FRONT   = 6,

} alCAMERAINFO_CameraID;

/** \brief Define the structure for camera data set. */
typedef struct
{

    /** \brief The camera ID. */
    alCAMERAINFO_CameraID ucCameraID;

    /** \brief The time stamp of the current frame. (in ms) */
    UINT32 ulTimeStamp;

    /** \brief The exposure time when the current frame is taken. (in us) */
    UINT32 ulExposureTime;

    /** \brief The gain of AGC when the current frame is taken. */
    UINT32 ulGain;

} alCAMERAINFO_Set;

/** \brief Define the structure for camera data set. (extrinsic params) */
typedef struct
{
    /** \brief Image Width (in pixel) */
    UINT32          ulImageWidth;
    /** \brief Image Height (in pixel) */
    UINT32          ulImageHeight;

    /** \brief Pitch angle (in degree) */
    FLOAT32         fPitchAngle;
    /** \brief Yaw angle (in degree) */
    FLOAT32         fYawAngle;
    /** \brief Roll angle (in degree) */
    FLOAT32         fRollAngle;
    /** \brief Camera Position X (in milimeter) : according to center of car center on the ground */
    INT32           lCameraPosX;
    /** \brief Camera Position Y (in milimeter) : according to center of car center on the ground  */
    INT32           lCameraPosY;
    /** \brief Camera Position Z (in milimeter) : according to center of car center on the ground */
    INT32           lCameraPosZ;
} alCAMERAINFO_ExtrinsicParams;



/**
*   @}
*/
