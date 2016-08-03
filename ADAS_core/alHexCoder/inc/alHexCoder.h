
#include "basedef.h"

//#include "EagleK3.h"
//#include "alAVM2DK.h"
//#include "alAlleyViewK.h"
//#include "alTRAILLINE.h"
//#include "alTILibDef.h"
//#include "AVM3DK.h"
//#include "alINI.h"
//#include "alLUT_v2.h"
//#include "AVM3DK.h"

/**
*  \addtogroup alHEXCODER
*  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief The Cfg id */
typedef enum
{
    alHEXCODER_CFG_1 = 0x00,
    alHEXCODER_CFG_2 = 0x01,
    alHEXCODER_CFG_3 = 0x02,
    alHEXCODER_CFG_4 = 0x03
} alHEXCODER_CFG_ID;

/** \brief The module id */
typedef enum
{
    alHEXCODER_COMMONK = 0x0000,
    alHEXCODER_EAGLEK3 = 0x0001,
    alHEXCODER_AVM2D = 0x0002,
    alHEXCODER_ALLEYVIEW = 0x0003,
    alHEXCODER_TRAILLINE = 0x0004,
    alHEXCODER_EXTRINSIC_CFG = 0x0005,
    alHEXCODER_CALIBRATE_CFG = 0x0006,
    alHEXCODER_FM_LEFT = 0x0100,
    alHEXCODER_FM_RIGHT = 0x0101,
    alHEXCODER_FM_FRONT = 0x0102,
    alHEXCODER_FM_BACK = 0x0103,
    alHEXCODER_EXTRINSIC_RESULT = 0x0200,
    alHEXCODER_CALIBRATE_RESULT = 0x0201,
    alHEXCODER_EAGLEK3_FIELD_DATA = 0x0300
} alHEXCODER_MODULE_ID;


/**
\brief Get module configure buffer pointer & length by its module ID
\param a_ulSectionID [IN] module ID
\param a_pucDataSectionBuffer [IN] configure file buffer
\param a_ulBufferSize [IN] configure file buffer size
\param a_pulCfgSize [INOUT] module configure file buffer size
\return module configure buffer
*/
UINT8* alHEXCODER_GetCfgBuffer(
    UINT32 a_ulSectionID, 
    UINT8 *a_pucDataSectionBuffer, 
    UINT32 a_ulBufferSize, 
    UINT32 *a_pulCfgSize
);


/**
*  @}
*/

#ifdef __cplusplus
}
#endif