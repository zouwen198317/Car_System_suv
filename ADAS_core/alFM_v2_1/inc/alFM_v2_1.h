
#pragma once 

#include "mtype.h"
#include "alFM_v2_1_Def.h"

/**
  *  \addtogroup alFM_v2_1
  *  @{
  */

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    \brief Query FM_BV_Working Buffer Size
    \param a_ptFMCfg [INOut] The Cfg data
    \return None.
    */
    UINT32  alFM_v2_1_QueryFM_WorkingBufferSizeSingle(alFM_v2_1_ModelCfg *a_ptFMCfg);


    /** 
        \brief To initial the alFM_v2_1_Model structure, all data in the structure will be set to 0.
        \param a_ptFM_v2_Model [IN] The structure to be initialize.
    */
    void alFM_v2_1_InitialBuffer(alFM_v2_1_Model * a_ptFM_v2_Model);

    /**
        \brief To load user config data from HEX file. 
        \param a_ulDataID [IN] ID of the current data.
        \param a_ulDataLength [IN] Length of the current data.
        \param a_pulDataBuffer [IN] Data buffer array.
        \param a_ptFM_v2_Cfg [OUT] The buffer to store the config data.
    */
    void alFM_v2_1_LoadCfgInfoByHexData(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT32 * a_pulDataBuffer, alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg);

    /**
        \brief Initialize the FM_v2 by the FM_v2 Config. 
        \param a_ptFM_v2_Cfg [IN] The fisheye model (v2) config data for single camera. 
        \param a_ptFM_v2_Model [OUT] To store the initialized FM parameters.
    */
    void alFM_v2_1_InitialByCfgData(alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg, alFM_v2_1_Model * a_ptFM_v2_Model);

    /**
    \brief Initialize the FM_v2 by the FM_v2 Config.
    \param a_ptFM_v2_Cfg [IN] The fisheye model (v2) config data for single camera.
    \param a_ptFM_v2_Model [OUT] To store the initialized FM parameters.
    */
    void alFM_v2_1_InitialByCfgDataExternalBuffer(alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg, alFM_v2_1_Model * a_ptFM_v2_Model, UINT8 *a_pucBuffer);

    /**
        \brief To convert coordinates from distorted image, pixel, to undistorted sphere, mm. 
               計算得到的 Undistorted 3D 座標，都會落在半徑為 focal length 的球上面
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eDistX [IN] The x coordinates on distorted image, pixel.
        \param a_eDistY [IN] The y coordinates on distorted image, pixel.
        \param a_peUnDistX [OUT] The x coordinates on undistorted shpere, mm.
        \param a_peUnDistY [OUT] The y coordinates on undistorted shpere, mm.
        \param a_peUnDistZ [OUT] The z coordinates on undistorted shpere, mm.
    */
    void alFM_v2_1_Distorted2Undistorted_Sphere(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eDistX, FLOAT64 a_eDistY, FLOAT64 * a_peUnDistX, FLOAT64 * a_peUnDistY, FLOAT64 * a_peUnDistZ);

    /**
        \brief To convert coordinates from distorted image, pixel, to undistorted sphere and then project to a planar, pixel. 
               計算得到的 Undistorted 3D 座標，都會落在半徑為 focal length 的球上面
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eDistX [IN] The x coordinates on distorted image, pixel.
        \param a_eDistY [IN] The y coordinates on distorted image, pixel.
        \param a_peUnDistX [OUT] The x coordinates on undistorted and projected image, pixel.
        \param a_peUnDistY [OUT] The y coordinates on undistorted and projected image, pixel.
    */
    void alFM_v2_1_Distorted2Undistorted_SpherePixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eDistX, FLOAT64 a_eDistY, FLOAT64 * a_peUnDistX, FLOAT64 * a_peUnDistY);

    /**
        \brief To convert coordinates from distorted image, pixel, to undistorted image - planar, mm. 
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eDistX [IN] The x coordinates on distorted image, pixel.
        \param a_eDistY [IN] The y coordinates on distorted image, pixel.
        \param a_peUnDistX [OUT] The x coordinates on undistorted image - planar, mm.
        \param a_peUnDistY [OUT] The y coordinates on undistorted image - planar, mm.
    */
    void alFM_v2_1_Distorted2Undistorted_Planar(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eDistX, FLOAT64 a_eDistY, FLOAT64 * a_peUnDistX, FLOAT64 * a_peUnDistY);

    /**
        \brief To convert coordinates from distorted image, pixel, to undistorted image - planar, pixel. 
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eDistX [IN] The x coordinates on distorted image, pixel.
        \param a_eDistY [IN] The y coordinates on distorted image, pixel.
        \param a_peUnDistX [OUT] The x coordinates on undistorted image - planar, pixel.
        \param a_peUnDistY [OUT] The y coordinates on undistorted image - planar, pixel.
    */
    void alFM_v2_1_Distorted2Undistorted_PlanarPixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eDistX, FLOAT64 a_eDistY, FLOAT64 * a_peUnDistX, FLOAT64 * a_peUnDistY);

    /**
        \brief To convert coordinates from undistorted sphere, mm, to distorted image, pixel. 
               傳入的 Undistorted 3D 座標可以不在半徑為 Flocal Length 的球面上，輸入的座標單位為 mm
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eUnDistX [IN] The x coordinates on undistorted shpere, mm.
        \param a_eUnDistY [IN] The y coordinates on undistorted shpere, mm.
        \param a_eUnDistZ [IN] The z coordinates on undistorted shpere, mm.
        \param a_peDistX [OUT] The x coordinates on distorted image, pixel.
        \param a_peDistY [OUT] The y coordinates on distorted image, pixel.
    */
    void alFM_v2_1_Undistorted2Distorted_Sphere(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eUnDistX, FLOAT64 a_eUnDistY, FLOAT64 a_eUnDistZ, FLOAT64 * a_peDistX, FLOAT64 * a_peDistY);

    /**
        \brief To convert coordinates from undistorted and projected image, pixel, to distorted image, pixel.
               傳入的 Undistorted 2D 座標是位在球面上座標點的 X, Y 位置，Z位置必須由球面公式推算。
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eUnDistX [IN] The x coordinates on undistorted and projected image, pixel.
        \param a_eUnDistY [IN] The y coordinates on undistorted and projected image, pixel.
        \param a_peDistX [OUT] The x coordinates on distorted image, pixel.
        \param a_peDistY [OUT] The y coordinates on distorted image, pixel.
    */
    void alFM_v2_1_Undistorted2Distorted_SpherePixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eUnDistX, FLOAT64 a_eUnDistY, FLOAT64 * a_peDistX, FLOAT64 * a_peDistY);

    /**
        \brief To convert coordinates from undistorted image, mm, to distorted image, pixel. 
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eUnDistX [IN] The x coordinates on undistorted image - planar, mm.
        \param a_eUnDistY [IN] The y coordinates on undistorted image - planar, mm.
        \param a_peDistX [OUT] The x coordinates on distorted image, pixel.
        \param a_peDistY [OUT] The y coordinates on distorted image, pixel.
    */
    void alFM_v2_1_Undistorted2Distorted_Planar(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eUnDistX, FLOAT64 a_eUnDistY, FLOAT64 * a_peDistX, FLOAT64 * a_peDistY);
    
    /**
        \brief To convert coordinates from undistorted image, pixel, to udistorted image - planar, pixel. 
        \param a_ptFM_v2_Model [IN] The initialized FM parameters.
        \param a_eUnDistX [IN] The x coordinates on undistorted image - planar, pixel.
        \param a_eUnDistY [IN] The y coordinates on undistorted image - planar, pixel.
        \param a_peDistX [OUT] The x coordinates on distorted image, pixel.
        \param a_peDistY [OUT] The y coordinates on distorted image, pixel.
    */
    void alFM_v2_1_Undistorted2Distorted_PlanarPixel(const alFM_v2_1_Model * a_ptFM_v2_Model, FLOAT64 a_eUnDistX, FLOAT64 a_eUnDistY, FLOAT64 * a_peDistX, FLOAT64 * a_peDistY);


    /**
        \brief To free the initialized FM_v2 model structure. 
        \param a_ptFM_v2_Model [IN] The FM_v2 structure to be freed.
    */
    void alFM_v2_1_FreeBuffer(alFM_v2_1_Model * a_ptFM_v2_Model);

#ifdef __cplusplus
}
#endif

/**
  *  @}
  */
