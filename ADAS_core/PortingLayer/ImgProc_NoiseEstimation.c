
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
#include <assert.h>
#include "mtype.h"
#include "ImageProc.h"
#include "dat_copy.h"

//#ifdef WIN32    // Visual C++ platform
//#include "Debug/FileOperation.h"
//#endif

#ifdef WIN32
static UINT8 g_ucL2_SRAM[192*1024];
static UINT8 * g_L2_SRAM_ROI_DSP = &(g_ucL2_SRAM[0]);
static UINT8 * g_L2_SRAM_ROI_DMA = &(g_ucL2_SRAM[0]);
#else
static UINT8 * g_L2_SRAM_ROI_DSP = (UINT8 *) 0x10800000;
static UINT8 * g_L2_SRAM_ROI_DMA = (UINT8 *) 0x40800000;
#endif

//////////////////////////////////////////////////////////////////////////
void ImgProc_NoiseEstimation(UINT8 * restrict a_pucImgYUYVBuf, 
                             const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                             const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                             const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                             UINT32 * a_pulNoiseSum)
{
 
    UINT32 ulLineIndex, ulRowIndex;
    UINT32 ulSectionIndex = 0;
    UINT32 ulMaxLineCntInSection = 65536 / (a_ulProcWidth<<1);
    UINT32 ulSectionCnt = (a_ulProcHeight)/ulMaxLineCntInSection;
    UINT32 ulSectionLength = ((ulMaxLineCntInSection * a_ulProcWidth)<<1);
    UINT32 ulSectionPitchLength = ((ulMaxLineCntInSection * a_ulBufferWidth)<<1);
    register UINT32 ulSum = 0;
    UINT8 * pucPtr = a_pucImgYUYVBuf + ((a_ulProcStartY * a_ulBufferWidth + a_ulProcStartX)<<1);
    UINT8 * pucSRAMPtr = 0;

    UINT32 ulSectionID = 0;
    UINT32 ulDMAID[2] = {0, 0};
    UINT32 ulLastSectionLine = a_ulProcHeight % ulMaxLineCntInSection;
    UINT32 ulX, ulY;

#ifdef _DEBUG
    UINT32 ulPixelCnt = 0;
#endif

    //(*a_pulNoiseSum) = 0;

    for(ulLineIndex = 0; ulLineIndex < a_ulProcHeight; ulLineIndex+=ulMaxLineCntInSection)
    {
        ulSectionIndex = ulLineIndex/ulMaxLineCntInSection;
        ulSectionID = (ulSectionIndex&0x1);

        if(ulSectionIndex == ulSectionCnt)
        {
            ulDMAID[ulSectionID] = DAT_copy2d(DAT_2D1D, pucPtr + ulSectionIndex * ulSectionPitchLength, g_L2_SRAM_ROI_DMA + ulSectionID * ulSectionLength, 
                (a_ulProcWidth<<1), ulLastSectionLine, (a_ulBufferWidth<<1));
        }
        else
        {
            ulDMAID[ulSectionID] = DAT_copy2d(DAT_2D1D, pucPtr + ulSectionIndex * ulSectionPitchLength, g_L2_SRAM_ROI_DMA + ulSectionID * ulSectionLength, 
                (a_ulProcWidth<<1), ulMaxLineCntInSection, (a_ulBufferWidth<<1));
        }

        if(ulSectionIndex > 0) 
        {	
            //DAT_wait(ulDMAID[!ulSectionID]);	

            pucSRAMPtr = g_L2_SRAM_ROI_DSP + (!ulSectionID) * ulSectionLength;
            for(ulY = 0, ulRowIndex = 0 ; ulY < a_ulProcHeight ; ulY++, ulRowIndex+=a_ulProcWidth)
            {
                for(ulX = 0 ; ulX < a_ulProcWidth - 1 ; ulX++)
                {
                    (*a_pulNoiseSum) += abs(pucSRAMPtr[(ulRowIndex+ulX)<<1] - pucSRAMPtr[(ulRowIndex+ulX+1)<<1]);
#ifdef _DEBUG
                    ulPixelCnt ++;
#endif
                }
            }   

        }

        DAT_wait(DAT_XFRID_WAITALL);	

    }

    // Calculate the final one section
    //DAT_wait(ulDMAID[ulSectionID]);	

    pucSRAMPtr = g_L2_SRAM_ROI_DSP + (ulSectionID) * ulSectionLength;

    //Memory2File("Crop24x24.raw", pucSRAMPtr, sizeof(UINT8) * ((a_ulProcHeight * a_ulProcWidth)<<1));

    for(ulY = 0, ulRowIndex = 0 ; ulY < ulLastSectionLine ; ulY++, ulRowIndex+=a_ulProcWidth)
    {
        for(ulX = 0 ; ulX < a_ulProcWidth - 1 ; ulX++)
        {
            (*a_pulNoiseSum) += abs(pucSRAMPtr[(ulRowIndex+ulX)<<1] - pucSRAMPtr[(ulRowIndex+ulX+1)<<1]);
#ifdef _DEBUG
            ulPixelCnt ++;
#endif
        }
    }   

#ifdef _DEBUG
    assert(ulPixelCnt == (a_ulProcWidth-1)*a_ulProcHeight);
#endif

}
