
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
        \brief To load the default config of fisheye model for specofic camera model.
        \param a_ucCameraModel [IN] The specific camera model.
        \param a_ptFM_v2_Cfg [OUT] The loaded fisheye model config.
        */
    void alFM_v2_1_LoadDefaultModedCfg(alFM_v2_1_DefaultCameraModel a_ucCameraModel, alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg);

#ifdef __cplusplus
}
#endif

/**
  *  @}
  */
