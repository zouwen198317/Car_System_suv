
#include "BVCAM_FACAUTOK/BVCAM_FACAUTOK_Def.h" // add by ancre for autoK
#include <locale.h> // add by ancre for char to wchar_t

#ifdef WIN32
#include "alINI.h"
#endif

/**
*  \addtogroup alBVCAM_FACAUTOK
*  @{
*/
#define alBVCAM_FACAUTOK_MAX_DATA_PER_ID         50

#define alBVCAM_FACAUTOK_HEX_SWITCH  1
static UINT32 g_aulDataBuffer[alBVCAM_FACAUTOK_MAX_DATA_PER_ID];


static void alBVCAM_FACAUTOK_CfgImporHextGlobal(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, BVCAM_FACAUTOK_CFG *a_ptCfg);
static void alBVCAM_FACAUTOK_CfgImportSingleCamera(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, UINT32 a_ulCamID, BVCAM_FACAUTOK_CFG *a_ptCfg);

/**
*  @}
*/

#if alBVCAM_FACAUTOK_HEX_SWITCH
static void alBVCAM_FACAUTOK_CfgImporHextGlobal(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, BVCAM_FACAUTOK_CFG *a_ptCfg)
{
	switch (a_ulDataID)
	{
	case 0x0000:    // lCammeraNum
	{
		a_ptCfg->lCammeraNum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	default:
		// Do nothing
        printf("Invalid Data ID: 0x%X\n - alBVCAM_FACAUTOK_CfgImport Global\n", a_ulDataID);
	break;
	}
}
#endif

#if alBVCAM_FACAUTOK_HEX_SWITCH
static void alBVCAM_FACAUTOK_CfgImportSingleCamera(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, UINT32 a_ulCamID, BVCAM_FACAUTOK_CFG *a_ptCfg)
{
	switch (a_ulDataID)
	{
	case 0x000:    // alBVCAM_FACAUTOK_RECK_ROI_NUMBER
	{
		a_ptCfg->atRecKCfg[a_ulCamID].lROINum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x001:    // alBVCAM_FACAUTOK_RECK_ROI_SCALE_0
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[0].eSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x002:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_X_0
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[0].lSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x003:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_Y_0
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[0].lSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x004:    // alBVCAM_FACAUTOK_RECK_ROI_POINT_NUMBER_0
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[0].lPointNum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x005:    // alBVCAM_FACAUTOK_RECK_ROI_SCALE_1
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[1].eSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x006:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_X_1
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[1].lSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x007:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_Y_1
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[1].lSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x008:    // alBVCAM_FACAUTOK_RECK_ROI_POINT_NUMBER_1
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[1].lPointNum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x009:    // alBVCAM_FACAUTOK_RECK_ROI_SCALE_2
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[2].eSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x00A:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_X_2
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[2].lSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x00B:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_Y_2
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[2].lSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x00C:    // alBVCAM_FACAUTOK_RECK_ROI_POINT_NUMBER_2
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[2].lPointNum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x00D:    // alBVCAM_FACAUTOK_RECK_ROI_SCALE_3
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[3].eSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x00E:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_X_3
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[3].lSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x00F:    // alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_Y_3
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[3].lSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x010:    // alBVCAM_FACAUTOK_RECK_ROI_POINT_NUMBER_3
	{
		a_ptCfg->atRecKCfg[a_ulCamID].atROICfg[3].lPointNum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x011:    // alBVCAM_FACAUTOK_CROSSMARK_ROI_NUMBER
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].lROINum = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x012:    // alBVCAM_FACAUTOK_CROSSMARK_MODE
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].ucMode = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x013:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_0
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x014:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_0
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x015:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_0
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x016:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_0
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x017:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_0
	{
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x018:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_1
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x019:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_1
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x01A:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_1
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x01B:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_1
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x01C:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_1
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x01D:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_2
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x01E:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_2
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x01F:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_2
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x020:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_2
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x021:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_2
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x022:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_3
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x023:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_3
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x024:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_3
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x025:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_3
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x026:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_3
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x027:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_4
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x028:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_4
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x029:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_4
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x02A:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_4
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x02B:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_4
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x02C:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_5
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x02D:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_5
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x02E:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_5
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x02F:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_5
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x030:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_5
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x031:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_6
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x032:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_6
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x033:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_6
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x034:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_6
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x035:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_6
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x036:    // alBVCAM_FACAUTOK_CROSSMARK_SCALE_7
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].aeSBVScale = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x037:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X_7
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].alSBVOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x038:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y_7
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].alSBVOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x039:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X_7
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].lSBVDetectOffsetX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x03A:    // alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y_7
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].lSBVDetectOffsetY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x03B:    // alCROSSMARKK_CROSSMARK_DIFF_TH
	{
		
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[0].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x03C:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
	{
		
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[0].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x03D:    // alCROSSMARKK_CROSSMARK_VARIN_TH
	{
		
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[0].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x03E:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
	{
		
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[0].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

	case 0x03F:    // alCROSSMARKK_CROSSMARK_VAR_TH
	{
		
		a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[0].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
	}
	break;

    case 0x040:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[1].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x041:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[1].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x042:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[1].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x043:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[1].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x044:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[1].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x045:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[2].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x046:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[2].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x047:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[2].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x048:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[2].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x049:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[2].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x04A:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[3].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x04B:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[3].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x04C:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[3].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x04D:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[3].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x04E:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[3].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x04F:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[4].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x050:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[4].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x051:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[4].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x052:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[4].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x053:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[4].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x054:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[5].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x055:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[5].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x056:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[5].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x057:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[5].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x058:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[5].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x059:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[6].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x05A:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[6].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x05B:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[6].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x05C:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[6].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x05D:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[6].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x05E:    // alCROSSMARKK_CROSSMARK_DIFF_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[7].eDifferenceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x05F:    // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[7].eVarianceInDetailTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x060:    // alCROSSMARKK_CROSSMARK_VARIN_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[7].eVarianceInTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x061:    // alCROSSMARKK_CROSSMARK_VAROUT_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[7].eVarianceOutTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x062:    // alCROSSMARKK_CROSSMARK_VAR_TH
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atCrossMarkDetCfg[7].eVarianceTH = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x063:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x064:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[0].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x065:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x066:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[1].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x067:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x068:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[2].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x069:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x06A:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[3].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x06B:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x06C:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[4].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x06D:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x06E:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[5].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x06F:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x070:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[6].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x071:    // alCROSSMARKK_DETECT_ROI_W
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].tROISize.lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

    case 0x072:    // alCROSSMARKK_DETECT_ROI_H
    {
        
        a_ptCfg->atCrossMarkKCfg[a_ulCamID].atROICfg[7].tROISize.lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
    }
    break;

	default:
	{
		// Do nothing
        printf("Invalid Data ID: 0x%X\n - alBVCAM_FACAUTOK_CfgImport Single\n", a_ulDataID);
	}
    break;
	}
}
#endif

BOOL alBVCAM_FACAUTOK_LoadRECKRefData(wchar_t * pwcIniFileName, alRECK_CalCfg *a_ptRECKFeildData)
{
    alRECK_LoadRefData(pwcIniFileName, a_ptRECKFeildData);

	return TRUE;
}


void alBVCAM_FACAUTOK_LoadDefault(BVCAM_FACAUTOK_CFG *a_ptCfg)
{
	INT32 lCnt = 0;

    memset(a_ptCfg, 0, sizeof(BVCAM_FACAUTOK_CFG));

    a_ptCfg->lCammeraNum = COMMONK_NUM_BV_CHANNEL;

    for (lCnt = 0; lCnt < COMMONK_NUM_BV_CHANNEL; lCnt++)
	{
		// for PreK
        alRECK_LoadDefault(lCnt, &a_ptCfg->atRecKCfg[lCnt]);

		// for 2 nd K
        alCROSSMARKK_LoadDefault(lCnt, &a_ptCfg->atCrossMarkKCfg[lCnt]);
	}
	
}

#if alBVCAM_FACAUTOK_HEX_SWITCH // > 1
UINT32 alBVCAM_FACAUTOK_CfgExport(
	UINT32 a_ulSectionID,
	BVCAM_FACAUTOK_CFG *a_ptBVCAM_FACAUTOKCfg,
	UINT8 *a_pucDataSectionBuffer
	)
{
	UINT32 ulSectionBufLen = 0;
	UINT32 ulDataBufLen = 0;
	UINT32 ulDataID = 0;
	UINT32 ulItemID = 0;
	UINT32 ulViewID = 0x0000; // 0: global 1: view 0 2: view 1 3: view 2  4: view 3
    UINT32 ulViewID_Step = 0x0100;
    UINT32 ulSubFuncID = 0x1000;
	UINT32 ulStitchPosIndex = 0;
    UINT8 ucNullFlag = 0;
	INT32 lCAMId = 0, lIndex = 0;

    ucNullFlag = (a_pucDataSectionBuffer == NULL) ? 0 : 1;

	// Camera number (global)
    ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
	ulDataBufLen = 0;
    ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->lCammeraNum, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
    ulSectionBufLen += ulDataBufLen;

    ulViewID += ulViewID_Step;

	// start to export each view
	for (lCAMId = 0; lCAMId < a_ptBVCAM_FACAUTOKCfg->lCammeraNum; lCAMId++)
	{
        ulItemID = 0x0000;
		// alBVCAM_FACAUTOK_RECK_ROI_NUMBER
		ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
		ulDataBufLen = 0;
		ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atRecKCfg[lCAMId].lROINum, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
		ulSectionBufLen += ulDataBufLen;

		ulItemID++;

		for (lIndex = 0; lIndex < 4; lIndex++)
		{
			// alBVCAM_FACAUTOK_RECK_ROI_SCALE
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atRecKCfg[lCAMId].atROICfg[lIndex].eSBVScale, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_X
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atRecKCfg[lCAMId].atROICfg[lIndex].lSBVOffsetX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_RECK_ROI_SBV_OFFSET_Y
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atRecKCfg[lCAMId].atROICfg[lIndex].lSBVOffsetY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_RECK_ROI_POINT_NUMBER
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atRecKCfg[lCAMId].atROICfg[lIndex].lPointNum, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;
		}

		// alBVCAM_FACAUTOK_CROSSMARK_ROI_NUMBER
		ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
		ulDataBufLen = 0;
		ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].lROINum, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
		ulSectionBufLen += ulDataBufLen;

		ulItemID++;

		// alBVCAM_FACAUTOK_CROSSMARK_MODE
		ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
		ulDataBufLen = 0;
		ulDataBufLen += alHEXDATA_PackUINT8(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].ucMode, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
		ulSectionBufLen += ulDataBufLen;

		ulItemID++;

		for (lIndex = 0; lIndex < 8; lIndex++)
		{
			// alBVCAM_FACAUTOK_CROSSMARK_SCALE
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].aeSBVScale, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_X
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].alSBVOffsetX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_CROSSMARK_SBV_OFFSET_Y
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].alSBVOffsetY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_X
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].lSBVDetectOffsetX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;

			// alBVCAM_FACAUTOK_CROSSMARK_SBV_DETECT_OFFSET_Y
			ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].lSBVDetectOffsetY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
			ulSectionBufLen += ulDataBufLen;

			ulItemID++;
		}

        for (lIndex = 0; lIndex < 8; lIndex++)
        {
            // alCROSSMARKK_CROSSMARK_DIFF_TH
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atCrossMarkDetCfg[lIndex].eDifferenceTH, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            // alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atCrossMarkDetCfg[lIndex].eVarianceInDetailTH, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            // alCROSSMARKK_CROSSMARK_VARIN_TH
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atCrossMarkDetCfg[lIndex].eVarianceInTH, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            // alCROSSMARKK_CROSSMARK_VAROUT_TH
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atCrossMarkDetCfg[lIndex].eVarianceOutTH, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            // alCROSSMARKK_CROSSMARK_VAR_TH
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackFLOAT64(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atCrossMarkDetCfg[lIndex].eVarianceTH, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }

        for (lIndex = 0; lIndex < 8; lIndex++)
        {
            // alCROSSMARKK_DETECT_ROI_W
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].tROISize.lX, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;

            // alCROSSMARKK_DETECT_ROI_H
            ulDataID = (a_ulSectionID << 16) + ulSubFuncID + ulViewID + ulItemID;
            ulDataBufLen = 0;
            ulDataBufLen += alHEXDATA_PackINT32(ulDataID, a_ptBVCAM_FACAUTOKCfg->atCrossMarkKCfg[lCAMId].atROICfg[lIndex].tROISize.lY, a_pucDataSectionBuffer + ulSectionBufLen*ucNullFlag);
            ulSectionBufLen += ulDataBufLen;

            ulItemID++;
        }
		

        ulViewID += ulViewID_Step;
	}
	return ulSectionBufLen;
}
#endif

#if alBVCAM_FACAUTOK_HEX_SWITCH
void alBVCAM_FACAUTOK_CfgImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, BVCAM_FACAUTOK_CFG *a_ptCfg)
{
	UINT32 ulSubDataID = 0;

	ulSubDataID = a_ulDataID & 0x00FF;

	switch (a_ulDataID & 0x0F00)
	{
	case 0x0000:    // global data
	{
        alBVCAM_FACAUTOK_CfgImporHextGlobal(ulSubDataID, a_ulDataLength, a_pucBuffer, a_ptCfg);
	}
	break;

	case 0x0100:    // View 1
	{
        alBVCAM_FACAUTOK_CfgImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 0, a_ptCfg);
	}
	break;

	case 0x0200:    // View 2
	{
        alBVCAM_FACAUTOK_CfgImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 1, a_ptCfg);
	}
	break;

	case 0x0300:    // View 3
	{
        alBVCAM_FACAUTOK_CfgImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 2, a_ptCfg);
	}
	break;

	case 0x0400:    // View 4
	{
        alBVCAM_FACAUTOK_CfgImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 3, a_ptCfg);
	}
	break;

	default:
		// Do nothing
		printf("Invalid Data ID: 0x%X\n - alBVCAM_FACAUTOK_CfgImport\n", a_ulDataID);
	break;
	}
}
#endif

#if alBVCAM_FACAUTOK_HEX_SWITCH > 1
UINT32 alBVCAM_FACAUTOK_ParameterExport(
	UINT32 a_ulSectionID,
	UINT32 a_ulSectionBufLenLimit,
	BVCAM_FACAUTOK_Parameter *a_ptBVCAM_FACAUTOKParams,
	UINT8 *a_pucDataSectionBuffer
	)
{
	UINT32 ulSectionBufLen = 0;
	UINT32 ulDataBufLen = 0;
	UINT32 ulDataID = 0;
	UINT32 ulItemID = 0;
	UINT32 ulViewID = 0x1000;
	UINT32 ulStitchPosIndex = 0;

	INT32 lCAMId = 0, i = 0, j = 0;

	{

		ulDataBufLen = sizeof(alRECK_Point);
		ulDataBufLen = sizeof(a_ptBVCAM_FACAUTOKParams->atFineTuneFP);
		ulDataBufLen = sizeof(a_ptBVCAM_FACAUTOKParams->atStitchLine);
		ulDataBufLen = sizeof(a_ptBVCAM_FACAUTOKParams->atRecKParameter);
		ulDataBufLen = sizeof(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter);
	}

	

	for (lCAMId = 0; lCAMId < COMMONK_NUM_BV_CHANNEL; lCAMId++)
	{
		ulItemID = 0x0000;

		// atFineTuneFP
		for (j = 0; j < BVCAM_FACAUTOK_MAX_POINT_FINETUNE; j++)
		{
			// atFineTuneFP X
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atFineTuneFP[lCAMId][j].eX, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// atFineTuneFP Y
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atFineTuneFP[lCAMId][j].eY, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;
		}

		// atStitchLine
		for (j = 0; j < BVCAM_FACAUTOK_MAX_POINT_FINETUNE; j++)
		{
			// atStitchLine start X
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atStitchLine[lCAMId][j].tStart.eX, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// atStitchLine start Y
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atStitchLine[lCAMId][j].tStart.eY, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// atStitchLine end X
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atStitchLine[lCAMId][j].tEnd.eX, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// atStitchLine end Y
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atStitchLine[lCAMId][j].tEnd.eY, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;
		}

		// RectK
		{
			// atIdealPointRectK
			for (j = 0; j < alRECK_MAX_POINT_VIEW; j++)
			{
				// atIdealPointRectK_X
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].atIdealPointRectK[j].eX, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				// atIdealPointRectK_Y
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].atIdealPointRectK[j].eY, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;
			}

			// atRecKROI
			for (j = 0; j < alRECK_MAX_ROI; j++)
			{
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].atRecKROI[j].lLeft, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].atRecKROI[j].lTop, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].atRecKROI[j].lRight, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].atRecKROI[j].lBottom, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;
			}

			// ptFisheyeModel
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen = sizeof(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].ptFisheyeModel) / 4;

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, (UINT32*)(&a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].ptFisheyeModel), a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// eMMPP
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].eMMPP, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lOriImgYLimit
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].lOriImgYLimit, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lAngleCAM
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].lAngleCAM, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lCamPosX
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].lCamPosX, ulDataBufLen, g_aulDataBuffer);


			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lCamPosY
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].lCamPosY, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;
		}

		// CrossMark
		{
			// atIdealPointCrossMark
			for (j = 0; j < alCROSSMARKK_MAX_ROI; j++)
			{
				// atIdealPointCrossMark_X
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[j].lX, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				// atIdealPointCrossMark_Y
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].atIdealPointCrossMark[j].lY, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;
			}

			// CrossMark_ROI
			for (j = 0; j < alCROSSMARKK_MAX_ROI; j++)
			{
				// CrossMark_ROI left
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[j].lLeft, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				// CrossMark_ROI top
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[j].lTop, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				// CrossMark_ROI right
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[j].lRight, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

				// CrossMark_ROI Bottom
				ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
				ulDataBufLen = 0;
				ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].atCrossMarkROI[j].lBottom, ulDataBufLen, g_aulDataBuffer);

				ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
				assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
				assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
				ulItemID++;

			}

			// ptFisheyeModel
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen = sizeof(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].ptFisheyeModel) / 4;

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, (UINT32*)(&a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].ptFisheyeModel), a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// eMMPP
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_FLOAT64(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].eMMPP, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lOriImgYLimit
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].lOriImgYLimit, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lAngleCAM
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].lAngleCAM, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lCamPosX
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].lCamPosX, ulDataBufLen, g_aulDataBuffer);


			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
			ulItemID++;

			// lCamPosY
			ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
			ulDataBufLen = 0;
			ulDataBufLen += DataPack_INT32(a_ptBVCAM_FACAUTOKParams->atCrossMarkKParameter[lCAMId].lCamPosY, ulDataBufLen, g_aulDataBuffer);

			ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
			assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
			assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
            ulItemID++;

            // RectK FP flag
            for (j = 0; j < 16; j++)
            {
                // FP DISABLE FLAG
                ulDataID = (a_ulSectionID << 16) + ulViewID + ulItemID;
                ulDataBufLen = 0;
                ulDataBufLen += DataPack_UINT8(a_ptBVCAM_FACAUTOKParams->atRecKParameter[lCAMId].aucPointFlag[j], ulDataBufLen, g_aulDataBuffer);

                ulSectionBufLen += DataSectionPack(ulDataID, ulDataBufLen, g_aulDataBuffer, a_pucDataSectionBuffer + ulSectionBufLen);
                assert(ulDataBufLen <= alBVCAM_FACAUTOK_MAX_DATA_PER_ID);
                assert(ulSectionBufLen <= a_ulSectionBufLenLimit);
                ulItemID++;
            }
		}

		ulViewID += 0x1000;
	}

	return ulSectionBufLen;
}
#endif

#if alBVCAM_FACAUTOK_HEX_SWITCH
UINT32 alBVCAM_FACAUTOK_ParamsImportSingleCamera(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer, UINT32 a_ulCamID, UINT32 a_ulCurrentDataLength)
{
	UINT32 ulDataIndex = 0;

	ulDataIndex = a_ulCurrentDataLength;

	switch (a_ulDataID)
	{
		case 0x000:    //FINETUNE_FP_0_X
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atFineTuneFP[a_ulCamID][0].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x001:    //FINETUNE_FP_0_Y
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atFineTuneFP[a_ulCamID][0].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x002:    //FINETUNE_FP_1_X
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atFineTuneFP[a_ulCamID][1].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x003:    //FINETUNE_FP_1_Y
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atFineTuneFP[a_ulCamID][1].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x004:    //StitchLine start_0 X
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][0].tStart.eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x005:    //StitchLine start_0 Y
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][0].tStart.eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x006:    //StitchLine END_0 X
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][0].tEnd.eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x007:    //StitchLine END_0 Y
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][0].tEnd.eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x008:    //StitchLine start_1 X
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][1].tStart.eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x009:    //StitchLine start_1 Y
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][1].tStart.eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x00A:    //StitchLine END_1 X
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][1].tEnd.eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x00B:    //StitchLine END_1 Y
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atStitchLine[a_ulCamID][1].tEnd.eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x00C:    //RecK_IdealPoint_X_0
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[0].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x00D:    //RecK_IdealPoint_Y_0
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[0].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x00E:    //RecK_IdealPoint_X_1
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[1].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x00F:    //RecK_IdealPoint_Y_1
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[1].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x010:    //RecK_IdealPoint_X_2
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[2].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x011:    //RecK_IdealPoint_Y_2
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[2].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x012:    //RecK_IdealPoint_X_3
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[3].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x013:    //RecK_IdealPoint_Y_3
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[3].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x014:    //RecK_IdealPoint_X_4
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[4].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x015:    //RecK_IdealPoint_Y_4
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[4].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x016:    //RecK_IdealPoint_X_5
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[5].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x017:    //RecK_IdealPoint_Y_5
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[5].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x018:    //RecK_IdealPoint_X_6
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[6].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x019:    //RecK_IdealPoint_Y_6
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[6].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x01A:    //RecK_IdealPoint_X_7
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[7].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x01B:    //RecK_IdealPoint_Y_7
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[7].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x01C:    //RecK_IdealPoint_X_8
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[8].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x01D:    //RecK_IdealPoint_Y_8
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[8].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x01E:    //RecK_IdealPoint_X_9
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[9].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x01F:    //RecK_IdealPoint_Y_9
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[9].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x020:    //RecK_IdealPoint_X_10
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[10].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x021:    //RecK_IdealPoint_Y_10
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[10].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x022:    //RecK_IdealPoint_X_11
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[11].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x023:    //RecK_IdealPoint_Y_11
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[11].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x024:    //RecK_IdealPoint_X_12
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[12].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x025:    //RecK_IdealPoint_Y_12
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[12].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x026:    //RecK_IdealPoint_X_13
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[13].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x027:    //RecK_IdealPoint_Y_13
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[13].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x028:    //RecK_IdealPoint_X_14
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[14].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x029:    //RecK_IdealPoint_Y_14
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[14].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x02A:    //RecK_IdealPoint_X_15
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[15].eX = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x02B:    //RecK_IdealPoint_Y_15
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atIdealPointRectK[15].eY = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x02C:    //RecK_ROI_0_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[0].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x02D:    //RecK_ROI_0_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[0].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x02E:    //RecK_ROI_0_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[0].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x02F:    //RecK_ROI_0_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[0].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x030:    //RecK_ROI_1_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[1].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x031:    //RecK_ROI_1_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[1].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x032:    //RecK_ROI_1_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[1].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x033:    //RecK_ROI_1_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[1].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x034:    //RecK_ROI_2_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[2].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x035:    //RecK_ROI_2_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[2].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x036:    //RecK_ROI_2_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[2].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x037:    //RecK_ROI_2_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[2].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x038:    //RecK_ROI_3_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[3].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x039:    //RecK_ROI_3_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[3].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x03A:    //RecK_ROI_3_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[3].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x03B:    //RecK_ROI_3_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].atRecKROI[3].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x03C:    //RecK_ptFisheyeModel
		{
			
			// g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].ptFisheyeModel = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
			memcpy(&g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].ptFisheyeModel, a_pucBuffer, a_ulDataLength * 4);
		}
		break;

		case 0x03D:    //RecK_mmpp
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].eMMPP = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x03E:    //lOriImgYLimit
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].lOriImgYLimit = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x03F:    //lAngleCAM
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].lAngleCAM = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x040:    //lCamPosX
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].lCamPosX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x041:    //lCamPosY
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].lCamPosY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x042:    //CrossMark_IdealPoint_X_0
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[0].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x043:    //CrossMark_IdealPoint_Y_0
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[0].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x044:    //CrossMark_IdealPoint_X_1
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[1].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x045:    //CrossMark_IdealPoint_Y_1
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[1].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x046:    //CrossMark_IdealPoint_X_2
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[2].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x047:    //CrossMark_IdealPoint_Y_2
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[2].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x048:    //CrossMark_IdealPoint_X_3
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[3].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x049:    //CrossMark_IdealPoint_Y_3
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[3].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x04A:    //CrossMark_IdealPoint_X_4
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[4].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x04B:    //CrossMark_IdealPoint_Y_4
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[4].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x04C:    //CrossMark_IdealPoint_X_5
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[5].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x04D:    //CrossMark_IdealPoint_Y_5
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[5].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x04E:    //CrossMark_IdealPoint_X_6
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[6].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x04F:    //CrossMark_IdealPoint_Y_6
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[6].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x050:    //CrossMark_IdealPoint_X_7
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[7].lX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x051:    //CrossMark_IdealPoint_Y_7
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atIdealPointCrossMark[7].lY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x052:    //CrossMark_0_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[0].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x053:    //CrossMark_0_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[0].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x054:    //CrossMark_0_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[0].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x055:    //CrossMark_0_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[0].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x056:    //CrossMark_1_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[1].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x057:    //CrossMark_1_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[1].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x058:    //CrossMark_1_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[1].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x059:    //CrossMark_1_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[1].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x05A:    //CrossMark_2_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[2].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x05B:    //CrossMark_2_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[2].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x05C:    //CrossMark_2_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[2].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x05D:    //CrossMark_2_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[2].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x05E:    //CrossMark_3_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[3].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x05F:    //CrossMark_3_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[3].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x060:    //CrossMark_3_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[3].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x061:    //CrossMark_3_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[3].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x062:    //CrossMark_4_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[4].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x063:    //CrossMark_4_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[4].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x064:    //CrossMark_4_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[4].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x065:    //CrossMark_4_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[4].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x066:    //CrossMark_5_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[5].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x067:    //CrossMark_5_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[5].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x068:    //CrossMark_5_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[5].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x069:    //CrossMark_5_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[5].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x06A:    //CrossMark_6_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[6].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x06B:    //CrossMark_6_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[6].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x06C:    //CrossMark_6_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[6].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x06D:    //CrossMark_6_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[6].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x06E:    //CrossMark_7_lLeft
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[7].lLeft = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x06F:    //CrossMark_7_lTop
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[7].lTop = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x070:    //CrossMark_7_lRight
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[7].lRight = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x071:    //CrossMark_7_lBottom
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].atCrossMarkROI[7].lBottom = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x072:    //ptFisheyeModel
		{
			
			// g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].ptFisheyeModel = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
			memcpy(&g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].ptFisheyeModel, a_pucBuffer, a_ulDataLength * 4);
		}
		break;

		case 0x073:    //eMMPP
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].eMMPP = alHEXDATA_UnpackFLOAT64(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x074:    //lOriImgYLimit
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].lOriImgYLimit = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x075:    //lAngleCAM
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].lAngleCAM = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x076:    //lCamPosX
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].lCamPosX = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

		case 0x077:    //lCamPosY
		{
			
			g_tBVCAM_FACAUTOK_Parameter.atCrossMarkKParameter[a_ulCamID].lCamPosY = alHEXDATA_UnpackINT32(a_ulDataLength, a_pucBuffer);
		}
		break;

        case 0x078:    // diaable flag 0
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[0] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x079:    // diaable flag 1
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[1] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x07A:    // diaable flag 2
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[2] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x07B:    // diaable flag 3
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[3] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x07C:    // diaable flag 4
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[4] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x07D:    // diaable flag 5
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[5] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x07E:    // diaable flag 6
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[6] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x07F:    // diaable flag 7
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[7] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x080:    // diaable flag 8
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[8] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x081:    // diaable flag 9
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[9] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x082:    // diaable flag 10
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[10] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x083:    // diaable flag 11
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[11] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x084:    // diaable flag 12
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[12] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x085:    // diaable flag 13
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[13] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x086:    // diaable flag 14
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[14] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

        case 0x087:    // diaable flag 15
        {
            
            g_tBVCAM_FACAUTOK_Parameter.atRecKParameter[a_ulCamID].aucPointFlag[15] = alHEXDATA_UnpackUINT8(a_ulDataLength, a_pucBuffer);
        }
        break;

		default:
		{
			// Do nothing
			printf("Invalid Data ID: 0x%X\n - alBVCAM_FACAUTOK_Params Import Single\n", a_ulDataID);
		}
		break;
	}
	return ulDataIndex;
}
#endif

#if alBVCAM_FACAUTOK_HEX_SWITCH
void alBVCAM_FACAUTOK_ParamsImportHex(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucBuffer)
{
	UINT32 ulDataIndex = 0;
	UINT32 ulSubDataID = 0;

	ulSubDataID = a_ulDataID & 0x0FFF;

	switch (a_ulDataID & 0xF000)
	{
	case 0x0000:    // global data
	{
		assert(0);
	}
	break;

	case 0x1000:    // View 1
	{
		ulDataIndex = alBVCAM_FACAUTOK_ParamsImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 0, ulDataIndex);
	}
	break;

	case 0x2000:    // View 2
	{
		ulDataIndex = alBVCAM_FACAUTOK_ParamsImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 1, ulDataIndex);
	}
	break;

	case 0x3000:    // View 3
	{
		ulDataIndex = alBVCAM_FACAUTOK_ParamsImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 2, ulDataIndex);
	}
	break;

	case 0x4000:    // View 4
	{
		ulDataIndex = alBVCAM_FACAUTOK_ParamsImportSingleCamera(ulSubDataID, a_ulDataLength, a_pucBuffer, 3, ulDataIndex);
	}
	break;

	default:
		// Do nothing
		printf("Invalid Data ID: 0x%X\n - alBVCAM_FACAUTOK_ParamsImportHex\n", a_ulDataID);
		break;
	}
	
}
#endif

void alBVCAM_FACAUTOK_CfgImportINI(wchar_t * a_pwcConfigFilePath, BVCAM_FACAUTOK_CFG *a_ptCfg)
{
#ifdef WIN32
	INT32 lConvertedChars = 0, i = 0, j = 0;
	wchar_t * pwcSectionName = L"alBVCAM_FACAUTOK_Cfg";
	wchar_t pwcViewNo[MAX_PATH];
	wchar_t pwcCnt[MAX_PATH];
	wchar_t pwcTmpName[MAX_PATH] = { 0 };
	wchar_t pwcViewName[MAX_PATH] = { 0 };
	char acViewName[MAX_PATH] = { 0 };
	char acViewCnt[30] = { 0 };

#if 0 // for memory ldebug 
    UINT8 *pucMemDebug = NULL;
    pucMemDebug = a_ptCfg;
    pucMemDebug += 4;
#endif
	
    memset(a_ptCfg, 0, sizeof(BVCAM_FACAUTOK_CFG));

	// alBVCAM_FACAUTOK_VIEW element Name
	wchar_t * alBVCAM_FACAUTOK_alRECK_ROI_NUM = L"alBVCAM_FACAUTOK_alRECK_ROI_NUM";
	wchar_t * alBVCAM_FACAUTOK_alRECK_POINT_NUM = L"alBVCAM_FACAUTOK_alRECK_POINT_NUM";
	wchar_t * alBVCAM_FACAUTOK_alRECK_SCALE = L"alBVCAM_FACAUTOK_alRECK_SCALE";
	wchar_t * alBVCAM_FACAUTOK_alRECK_SBV_OFFSETX = L"alBVCAM_FACAUTOK_alRECK_SBV_OFFSETX";
	wchar_t * alBVCAM_FACAUTOK_alRECK_SBV_OFFSETY = L"alBVCAM_FACAUTOK_alRECK_SBV_OFFSETY";

	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_MODE = L"alBVCAM_FACAUTOK_alCROSSMARKK_MODE";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_ROI_NUM = L"alBVCAM_FACAUTOK_alCROSSMARKK_ROI_NUM";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_DIFF_TH = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_DIFF_TH";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_TH = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_TH";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAROUT_TH = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAROUT_TH";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAR_TH = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAR_TH";

	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_SBV_SCALE = L"alBVCAM_FACAUTOK_alCROSSMARKK_SBV_SCALE";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETX = L"alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETX";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETY = L"alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETY";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETX = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETX";
	wchar_t * alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETY = L"alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETY";

    wchar_t * alCROSSMARKK_DETECT_ROI_W = L"alCROSSMARKK_DETECT_ROI_W";
    wchar_t * alCROSSMARKK_DETECT_ROI_H = L"alCROSSMARKK_DETECT_ROI_H";
	// alBVCAM_FACAUTOK_VIEW element Name

#if 0 // for debug test 
	BVCAM_FACAUTOK_CFG tBVCAM_FACAUTOK_Cfg;
	memcpy(&tBVCAM_FACAUTOK_Cfg, &g_tBVCAM_FACAUTOK_Cfg, sizeof(BVCAM_FACAUTOK_CFG));
	memset(&g_tBVCAM_FACAUTOK_Cfg, 0, sizeof(BVCAM_FACAUTOK_CFG));
#endif

	// Global
	a_ptCfg->lCammeraNum = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, L"alBVCAM_FACAUTOK_VIEW_CNT");

	for (i = 0; i < a_ptCfg->lCammeraNum; i++)
	{
		swprintf(pwcViewNo, MAX_PATH, L"_%d", i);

		wcscpy_s(pwcTmpName, MAX_PATH, L"");

		// alBVCAM_FACAUTOK_alRECK_ROI_NUM
		wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alRECK_ROI_NUM);
		wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
		a_ptCfg->atRecKCfg[i].lROINum = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

		for (j = 0; j < a_ptCfg->atRecKCfg[i].lROINum ; j++)
		{
			swprintf(pwcCnt, MAX_PATH, L"_%d_%d", i, j);
			
			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alRECK_POINT_NUM
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alRECK_POINT_NUM);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atRecKCfg[i].atROICfg[j].lPointNum = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alRECK_SCALE
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alRECK_SCALE);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atRecKCfg[i].atROICfg[j].eSBVScale = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alRECK_SBV_OFFSETX
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alRECK_SBV_OFFSETX);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atRecKCfg[i].atROICfg[j].lSBVOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alRECK_SBV_OFFSETY
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alRECK_SBV_OFFSETY);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atRecKCfg[i].atROICfg[j].lSBVOffsetY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);
		}

		wcscpy_s(pwcTmpName, MAX_PATH, L"");

		// alBVCAM_FACAUTOK_alCROSSMARKK_MODE
		wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_MODE);
		wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
		a_ptCfg->atCrossMarkKCfg[i].ucMode = (UINT8)alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

		wcscpy_s(pwcTmpName, MAX_PATH, L"");

		// alBVCAM_FACAUTOK_alCROSSMARKK_ROI_NUM
		wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_ROI_NUM);
		wcscat_s(pwcTmpName, MAX_PATH, pwcViewNo);
		a_ptCfg->atCrossMarkKCfg[i].lROINum = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

		wcscpy_s(pwcTmpName, MAX_PATH, L"");

		
		for (j = 0; j < a_ptCfg->atCrossMarkKCfg[i].lROINum; j++)
		{
			swprintf(pwcCnt, MAX_PATH, L"_%d_%d", i, j);

            // alCROSSMARKK_DETECT_ROI_W
            wcscat_s(pwcTmpName, MAX_PATH, alCROSSMARKK_DETECT_ROI_W);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].tROISize.lX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

            wcscpy_s(pwcTmpName, MAX_PATH, L"");

            // alCROSSMARKK_DETECT_ROI_H
            wcscat_s(pwcTmpName, MAX_PATH, alCROSSMARKK_DETECT_ROI_H);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].tROISize.lY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

            wcscpy_s(pwcTmpName, MAX_PATH, L"");

            // alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_DIFF_TH
            wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_DIFF_TH);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atCrossMarkDetCfg[j].eDifferenceTH = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

            wcscpy_s(pwcTmpName, MAX_PATH, L"");

            // alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH
            wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_DTAIL_TH);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atCrossMarkDetCfg[j].eVarianceInDetailTH = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

            wcscpy_s(pwcTmpName, MAX_PATH, L"");

            // alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_TH
            wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VARIN_TH);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atCrossMarkDetCfg[j].eVarianceInTH = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

            wcscpy_s(pwcTmpName, MAX_PATH, L"");

            // alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAROUT_TH
            wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAROUT_TH);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atCrossMarkDetCfg[j].eVarianceOutTH = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

            wcscpy_s(pwcTmpName, MAX_PATH, L"");

            // alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAR_TH
            wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_VAR_TH);
            wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
            a_ptCfg->atCrossMarkKCfg[i].atCrossMarkDetCfg[j].eVarianceTH = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);
			
            wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alCROSSMARKK_SBV_SCALE
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_SBV_SCALE);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].aeSBVScale = alINI_GetKeyValue_FLOAT64W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETX
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETX);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].alSBVOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETY
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_SBV_OFFSETY);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].alSBVOffsetY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETX
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETX);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].lSBVDetectOffsetX = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);

			wcscpy_s(pwcTmpName, MAX_PATH, L"");

			// alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETY
			wcscat_s(pwcTmpName, MAX_PATH, alBVCAM_FACAUTOK_alCROSSMARKK_CROSSMARK_OFFSETY);
			wcscat_s(pwcTmpName, MAX_PATH, pwcCnt);
			a_ptCfg->atCrossMarkKCfg[i].atROICfg[j].lSBVDetectOffsetY = alINI_GetKeyValue_INT32W(a_pwcConfigFilePath, pwcSectionName, pwcTmpName);
		    
            wcscpy_s(pwcTmpName, MAX_PATH, L"");
        }
	}

#if 0 // for debug test
	{
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[0], &a_ptCfg->atRecKCfg[0], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[1], &a_ptCfg->atRecKCfg[1], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[2], &a_ptCfg->atRecKCfg[2], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atRecKCfg[3], &a_ptCfg->atRecKCfg[3], sizeof(alRECK_Cfg)) == 0);

		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[0], &a_ptCfg->atCrossMarkKCfg[0], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[1], &a_ptCfg->atCrossMarkKCfg[1], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[2], &a_ptCfg->atCrossMarkKCfg[2], sizeof(alRECK_Cfg)) == 0);
		assert(memcmp(&tBVCAM_FACAUTOK_Cfg.atCrossMarkKCfg[3], &a_ptCfg->atCrossMarkKCfg[3], sizeof(alRECK_Cfg)) == 0);
	}
#endif

#endif
}


void alBVCAM_FACAUTOK_LoadDefaultFeildData(BVCAM_FACAUTOK_CalibrationFeildData *a_ptFeildData)
{
    // Load Default Calibration for cross mark
    a_ptFeildData->tCrossmarkFeildData.uwFWheeltoFChart = alBVCAM_FACAUTOK_DEFAULT_CHART_F_WHEEL_TO_HEAD_DIST;
    a_ptFeildData->tCrossmarkFeildData.uwChartHoriDistance = alBVCAM_FACAUTOK_DEFAULT_CHART_HORI_DIST;
    a_ptFeildData->tCrossmarkFeildData.uwCharVertDistance = alBVCAM_FACAUTOK_DEFAULT_CHART_VERT_DIST;
    a_ptFeildData->tCrossmarkFeildData.FW1 = alBVCAM_FACAUTOK_DEFAULT_FW1;
    a_ptFeildData->tCrossmarkFeildData.FH1 = alBVCAM_FACAUTOK_DEFAULT_FH1;
    a_ptFeildData->tCrossmarkFeildData.FW2 = alBVCAM_FACAUTOK_DEFAULT_FW2;
    a_ptFeildData->tCrossmarkFeildData.FH2 = alBVCAM_FACAUTOK_DEFAULT_FH2;
    a_ptFeildData->tCrossmarkFeildData.FW3 = alBVCAM_FACAUTOK_DEFAULT_FW3;
    a_ptFeildData->tCrossmarkFeildData.FH3 = alBVCAM_FACAUTOK_DEFAULT_FH3;
    a_ptFeildData->tCrossmarkFeildData.FW4 = alBVCAM_FACAUTOK_DEFAULT_FW4;
    a_ptFeildData->tCrossmarkFeildData.FH4 = alBVCAM_FACAUTOK_DEFAULT_FH4;
    a_ptFeildData->tCrossmarkFeildData.FW5 = alBVCAM_FACAUTOK_DEFAULT_FW5;
    a_ptFeildData->tCrossmarkFeildData.FH5 = alBVCAM_FACAUTOK_DEFAULT_FH5;
    a_ptFeildData->tCrossmarkFeildData.FW6 = alBVCAM_FACAUTOK_DEFAULT_FW6;
    a_ptFeildData->tCrossmarkFeildData.FH6 = alBVCAM_FACAUTOK_DEFAULT_FH6;
    a_ptFeildData->tCrossmarkFeildData.BW1 = alBVCAM_FACAUTOK_DEFAULT_BW1;
    a_ptFeildData->tCrossmarkFeildData.BH1 = alBVCAM_FACAUTOK_DEFAULT_BH1;
    a_ptFeildData->tCrossmarkFeildData.BW2 = alBVCAM_FACAUTOK_DEFAULT_BW2;
    a_ptFeildData->tCrossmarkFeildData.BH2 = alBVCAM_FACAUTOK_DEFAULT_BH2;
    a_ptFeildData->tCrossmarkFeildData.BW3 = alBVCAM_FACAUTOK_DEFAULT_BW3;
    a_ptFeildData->tCrossmarkFeildData.BH3 = alBVCAM_FACAUTOK_DEFAULT_BH3;
    a_ptFeildData->tCrossmarkFeildData.BW4 = alBVCAM_FACAUTOK_DEFAULT_BW4;
    a_ptFeildData->tCrossmarkFeildData.BH4 = alBVCAM_FACAUTOK_DEFAULT_BH4;
    a_ptFeildData->tCrossmarkFeildData.BW5 = alBVCAM_FACAUTOK_DEFAULT_BW5;
    a_ptFeildData->tCrossmarkFeildData.BH5 = alBVCAM_FACAUTOK_DEFAULT_BH5;
    a_ptFeildData->tCrossmarkFeildData.BW6 = alBVCAM_FACAUTOK_DEFAULT_BW6;
    a_ptFeildData->tCrossmarkFeildData.BH6 = alBVCAM_FACAUTOK_DEFAULT_BH6;

    a_ptFeildData->tCrossmarkFeildData.BW7 = alBVCAM_FACAUTOK_DEFAULT_BW7;
    a_ptFeildData->tCrossmarkFeildData.BH7 = alBVCAM_FACAUTOK_DEFAULT_BH7;
    a_ptFeildData->tCrossmarkFeildData.BW8 = alBVCAM_FACAUTOK_DEFAULT_BW8;
    a_ptFeildData->tCrossmarkFeildData.BH8 = alBVCAM_FACAUTOK_DEFAULT_BH8;

    // Load Default Calibration for rectangle
    alRECK_LoadDefaultRefData(&a_ptFeildData->tRECK_FeildData);
}

void alBVCAM_FACAUTOK_LoadFeildDataByINI(wchar_t * pwcIniFileName, BVCAM_FACAUTOK_CalibrationFeildData *a_ptFeildData)
{
#ifdef WIN32
    wchar_t pwcIniFilePath[MAX_PATH];

    wcscpy_s(pwcIniFilePath, MAX_PATH, pwcIniFileName);
    a_ptFeildData->tCrossmarkFeildData.uwFWheeltoFChart = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"F_WHEEL_TO_HEAD_DIST");
    a_ptFeildData->tCrossmarkFeildData.uwChartHoriDistance = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"CHART_HORI_DIST");
    a_ptFeildData->tCrossmarkFeildData.uwCharVertDistance = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"CHART_VERT_DIST");

    a_ptFeildData->tCrossmarkFeildData.FW1 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FW1");
    a_ptFeildData->tCrossmarkFeildData.FH1 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FH1");;
    a_ptFeildData->tCrossmarkFeildData.FW2 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FW2");;
    a_ptFeildData->tCrossmarkFeildData.FH2 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FH2");;
    a_ptFeildData->tCrossmarkFeildData.FW3 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FW3");;
    a_ptFeildData->tCrossmarkFeildData.FH3 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FH3");;
    a_ptFeildData->tCrossmarkFeildData.FW4 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FW4");;
    a_ptFeildData->tCrossmarkFeildData.FH4 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FH4");;
    a_ptFeildData->tCrossmarkFeildData.FW5 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FW5");;
    a_ptFeildData->tCrossmarkFeildData.FH5 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FH5");;
    a_ptFeildData->tCrossmarkFeildData.FW6 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FW6");;
    a_ptFeildData->tCrossmarkFeildData.FH6 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"FH6");;
    a_ptFeildData->tCrossmarkFeildData.BW1 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW1");;
    a_ptFeildData->tCrossmarkFeildData.BH1 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH1");;
    a_ptFeildData->tCrossmarkFeildData.BW2 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW2");;
    a_ptFeildData->tCrossmarkFeildData.BH2 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH2");;
    a_ptFeildData->tCrossmarkFeildData.BW3 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW3");;
    a_ptFeildData->tCrossmarkFeildData.BH3 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH3");;
    a_ptFeildData->tCrossmarkFeildData.BW4 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW4");;
    a_ptFeildData->tCrossmarkFeildData.BH4 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH4");;
    a_ptFeildData->tCrossmarkFeildData.BW5 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW5");;
    a_ptFeildData->tCrossmarkFeildData.BH5 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH5");;
    a_ptFeildData->tCrossmarkFeildData.BW6 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW6");;
    a_ptFeildData->tCrossmarkFeildData.BH6 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH6");;

    a_ptFeildData->tCrossmarkFeildData.BW7 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW7");
    a_ptFeildData->tCrossmarkFeildData.BH7 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH7");
    a_ptFeildData->tCrossmarkFeildData.BW8 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BW8");
    a_ptFeildData->tCrossmarkFeildData.BH8 = alINI_GetKeyValue_INT32W(pwcIniFilePath, L"CrossMark_Field_Data", L"BH8");

    alBVCAM_FACAUTOK_LoadRECKRefData(pwcIniFileName, &a_ptFeildData->tRECK_FeildData);
#endif
}

void alBVCAM_FACAUTOK_SetWorkingPath(wchar_t * a_pwcWorkingPath)
{
	wcstombs(g_acalBVCAM_FACAUTOK_WorkingFolder, a_pwcWorkingPath, MAX_PATH);
}
