
#pragma once

#include "mtype.h"

/**
  *  \defgroup alFM_v2_1   alFM_v2_1
  *   This module is used to do lens distortion correction. This version uses the sphere model to include the correction for wider angle larger than 180 degree.
  *  @{
  */

/** \brief Define the maximum length of distortion curve. */
#define alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH     500 // 1000 for H012

#ifdef __cplusplus
extern "C"
{
#endif

    /** \brief Define the structure for single point data in the distortion curve. */
    typedef struct
    {
        /** \brief The angle degree for this distortion curve point, 反魚眼座標與光軸的夾角. */
        FLOAT64 eAngleDegree;
        /** \brief The sensor height for this distortion curve point. */
        FLOAT64 eRealHeight;

    #if 0
        /** \brief The sensor height for this distortion curve point. */
        FLOAT64 eRefHeight;
        /** \brief The distortion for this distortion curve point. */
        FLOAT64 eDistortion;
    #endif

        /** \brief The angle interval between this and next distortion curve point. */
        FLOAT64 eAngleInterval;
        /** \brief The sensor height between this and next distortion curve point. For the last distortion point, this value should be 1. */
        FLOAT64 eRealHeightInterval;

    #if 0
        /** \brief The sensor height between this and next distortion curve point. For the last distortion point, this value should be 1. */
        FLOAT64 eRefHeightInterval;
        /** \brief The distortion between this and next distortion curve point. For the last distortion point, this value should be 0. (It means the distortion value is fixed to the last point.) */
        FLOAT64 eDistortionInterval;
    #endif

    } alFM_v2_1_Distortion;

    /** \brief Define the structure to config the lens distortion. */
    typedef struct
    {
#if 0
        /** \brief The hieght of the source image with fisheye distorted. */
        UINT32  ulSrcHeight;
        /** \brief The width of the source image with fisheye distorted. */
        UINT32  ulSrcWidth;
#endif
        /** \brief Image width of the camera output. */
        UINT32 ulImageWidth;
        /** \brief Image height of the camera output. */
        UINT32 ulImageHeight;
        /** \brief Define the COD (X) - the center of lens. */
        UINT16 uwCOD_X;
        /** \brief Define the COD (Y) - the center of lens. */
        UINT16 uwCOD_Y;

        /** \brief The width of the source sensor image. For NTSC camera, the original sensor image size is 640x480, and NTSC will rescale it to 720x480. */
        UINT16 uwSrcSensorWidth;
        /** \brief The height of the source sensor image. For NTSC camera, the original sensor image size is 640x480, and NTSC will rescale it to 720x480. */
        UINT16 uwSrcSensorHeight;
        /** \brief The real pixel size of the sensor. in nano-meter. */
        UINT32 ulSensorPixelSize;

        /** \brief Define the horizontal FOV (in degree). */
        FLOAT64  eFOV_H;
        /** \brief Focal length of the camera in mm. */
        FLOAT64 eFocalLength;
        /** \brief Define the undistorted 2D horizontal FOV (in degree). This is used to record the 2D undistorted image. */
        FLOAT64  eUD_FOV_H;

        /** \brief Define the horizontal resize ratio of output image (only for analog camera). */
        FLOAT64  eHResizeRatio;

        /** \brief Define the length of the distortion curve. */
        UINT16 uwLengthOfDistortionCurve;

        /** \brief Define the scale of the angle table for du to di, larger value for better angle resolutuin, but larger memory and worse performacne. */
        UINT16 uwAngleTableScale;

	    /** \brief The buffer to record angle degree. */
        FLOAT64 aeAngleDegree[alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH];
	    /** \brief The buffer to record real height data (on sensor). */
        FLOAT64 aeRealHeight[alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH];

#if 0
	    /** \brief The buffer to record ref height data. */
        FLOAT64 aeRefHeight[alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH];
	    /** \brief The buffer to record distortion data. */
        FLOAT64 aeDistortion[alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH];
#endif

    } alFM_v2_1_ModelCfg;

    /** \brief Define the model structure for run-time distortion correction. */
    typedef struct
    {

        /** \brief The hieght of the source image with fisheye distorted. */
        UINT16  uwSrcHeight;
        /** \brief The width of the source image with fisheye distorted. */
        UINT16  uwSrcWidth;
        /** \brief The hieght of the destination image with fisheye corrected, for 2D only. */
        UINT16  uwDestHeight;
        /** \brief The width of the destination image with fisheye corrected, for 2D only. */
        UINT16  uwDestWidth;

        /** \brief The width of the source sensor image. For NTSC camera, the original sensor image size is 640x480, and NTSC will rescale it to 720x480. */
        UINT16 uwSrcSensorWidth;
        /** \brief Define the resize ratio. (= uwSrcWidth / uwSrcSensorWidth) */
        FLOAT64 eResizeRatio;
        /** \brief The real pixel size of the sensor. in nano-meter. */
        UINT32 ulSensorPixelSize;

        /** \brief Define the horizontal FOV (in degree). */
        FLOAT64  eFOV_H;
        /** \brief Focal length of the camera in mm. */
        FLOAT64 eFocalLength;
        /** \brief Define the undistorted 2D horizontal FOV (in degree). This is used to record the 2D undistorted image. */
        FLOAT64  eUD_FOV_H;

        /** \brief Define the COD (X) - the center of lens. */
        UINT16 uwCOD_X;
        /** \brief Define the COD (Y) - the center of lens. */
        UINT16 uwCOD_Y;

        /** \brief Define the length of the pixel table. */
        UINT16 uwLengthOfDistortPixelTable;
	    /** \brief The pixel table to do maping from di to atDistortionCurve. */
        UINT16 * puwDistortPixelTable;

        /** \brief Define the scale of the angle table for du to di, larger value for better angle resolutuin. */
        UINT16 uwAngleTableScale;
        /** \brief Define the length of the angle table for du to di. */
        UINT16 uwLengthOfAngleTable;
	    /** \brief The angle table to do maping from angle to atDistortionCurve index. This is used for du to di. */
        UINT16 * puwAngleTable;

        /** \brief Define the length of the distortion curve. */
        UINT16 uwLengthOfDistortionCurve;
    	
        /** \brief The buffer to record distortion curve - for Di to Du. */
        alFM_v2_1_Distortion atDistortionCurve[alFM_v2_1_MAX_DISTORTION_CRUVE_LENGTH];

    } alFM_v2_1_Model;

    /** \brief Define the flag for default FM_v2 config. */
    typedef enum
    {
        /** \brief The flag of default config for Sparrow 144. */
        alFM_v2_1_SPARROW_144 = 0x00,
        /** \brief The flag of default config for Sparrow 190. */
        alFM_v2_1_SPARROW_190 = 0x01,
        /** \brief The flag of default config for Sparrow 90. */
        alFM_v2_1_SPARROW_90 = 0x02,
        /** \brief The flag of default config for FCWDemo. */
        alFM_v2_1_FCWDemo = 0x10,

        /** \brief The flag of default config for Virtual Camera - No-Fisheye model. */
        alFM_v2_1_VC_NOFISH = 0x80,
        /** \brief The flag of default config for Virtual Camera - Curve 1. */
        alFM_v2_1_VC_CURVE1 = 0x81,
        /** \brief The flag of default config for Virtual Camera - Curve 2. */
        alFM_v2_1_VC_CURVE2 = 0x82,
        /** \brief The flag of default config for Virtual Camera - Curve 3. */
        alFM_v2_1_VC_CURVE3 = 0x83,
        /** \brief The flag of default config for Virtual Camera - No-Fisheye model - 2. */
        alFM_v2_1_VC_NOFISH2 = 0x84,
    } alFM_v2_1_DefaultCameraModel;

    /** 
        \brief To load the FM_v2 default setting from .h file.
        \param a_ucDefaultCamera [IN] Indicate which camera model is used as the default.
        \param a_ptCameraFMCfg [OUT] The buffer to store FM_v2 config data.
    */
    void alFM_v2_1_LoadDefault(alFM_v2_1_DefaultCameraModel a_ucDefaultCameraModel, alFM_v2_1_ModelCfg * a_ptCameraFMCfg);

#ifdef WIN32
    /**
    \brief To load user config data from INI file.
    \param a_pwcFileName [IN] The name of INI config file, 特定的 Camera Confg INI File, ex. CameraFisheyeParam_v2-Sparrow190.ini
    \param a_ptFM_v2_Cfg [OUT] The buffer to store the config data.
    */
    void alFM_v2_1_LoadUserCfgByINI(const wchar_t * a_pwcFileName, alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg);
#endif

/**
\brief Cfg Export to Hex file
\param a_ulSectionID [IN] Section ID
\param a_ptFMCfg [IN] Fish eye model Config data
\param a_pucDataSectionBuffer [OUT] Data Section Buffer for output
*/
UINT32 alFM_v2_1_SingleFisheyeModelCfgExport(
    UINT32 a_ulSectionID,
    alFM_v2_1_ModelCfg * a_ptFMCfg,
    UINT8 * a_pucDataSectionBuffer
);

/**
\brief Cfg Import by Hex file
\param a_ulDataID [IN] Data ID
\param a_ulDataLength [IN] Data Length
\param a_pulBuffer [IN] Data Section Buffer for reading
\param a_ptFMCfg [IN] Fish eye model Config data
*/
void alFM_v2_1_CfgImportHex(
    UINT32 a_ulDataID,
    UINT32 a_ulDataLength, UINT8 * a_pucBuffer,
    alFM_v2_1_ModelCfg *a_ptFMCfg
);

#ifdef __cplusplus
}
#endif

/**
  *  @}
  */
