
#include "alFM_v2_1_Default.h"

#include "alFM_v2_1_DistortionCurve_Sparrow144.h"
#include "alFM_v2_1_DistortionCurve_Sparrow190.h"
#include "alFM_v2_1_DistortionCurve_Sparrow90.h"
#include "alFM_v2_1_DistortionCurve_FCWDemo.h"
#include "alFM_v2_1_DistortionCurve_VC_NoFisheye.h"
#include "alFM_v2_1_DistortionCurve_VC_Curve1.h"
#include "alFM_v2_1_DistortionCurve_VC_Curve2.h"
#include "alFM_v2_1_DistortionCurve_VC_Curve3.h"
#include "alFM_v2_1_DistortionCurve_VC_NoFisheye2.h"

#include "mtype.h"

/** \cond DOXYGEN_EXCLUDE */

////////////////////////////////////////////////////////////////////////////////////////////
void alFM_v2_1_LoadDefaultModedCfg(alFM_v2_1_DefaultCameraModel a_ucCameraModel, alFM_v2_1_ModelCfg * a_ptFM_v2_Cfg)
{
    switch(a_ucCameraModel)
    {
    case alFM_v2_1_SPARROW_144: // Sparrow 144
        alFM_v2_1_LoadModedCfg_Sparrow144(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_SPARROW_190: // Sparrow 190
        alFM_v2_1_LoadModedCfg_Sparrow190(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_SPARROW_90: // Sparrow 90
        alFM_v2_1_LoadModedCfg_Sparrow90(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_FCWDemo: // FCW Demo
        alFM_v2_1_LoadModedCfg_FCWDemo(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_VC_NOFISH: 
        alFM_v2_1_LoadModedCfg_VC_NoFisheye(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_VC_CURVE1: 
        alFM_v2_1_LoadModedCfg_VC_Curve1(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_VC_CURVE2: 
        alFM_v2_1_LoadModedCfg_VC_Curve2(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_VC_CURVE3: 
        alFM_v2_1_LoadModedCfg_VC_Curve3(a_ptFM_v2_Cfg);
        break;
    case alFM_v2_1_VC_NOFISH2:
        alFM_v2_1_LoadModedCfg_VC_NoFisheye2(a_ptFM_v2_Cfg);
    }
}

/** \endcond DOXYGEN_EXCLUDE */
