

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
#include <assert.h>
#include "mtype.h"
#include "dat_copy.h"

#ifdef WIN32
#include "c6xsim/C6xSimulator_type_modifiers.h"
#endif

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
void ImgProc_ROIMean(   UINT8 * restrict a_pucImgYUYVBuf, 
                     const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                     const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                     const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                     UINT8 * a_pucLumaMean
                     )
{

    UINT32 ulY, ulIndex;
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

#ifdef _DEBUG
    UINT32 ulPixelCnt = 0;
#endif

    //assert(a_ulProcWidth * a_ulProcHeight < 96000);

    for(ulY = 0; ulY < a_ulProcHeight; ulY+=ulMaxLineCntInSection)
    {
        ulSectionIndex = ulY/ulMaxLineCntInSection;
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
            for(ulIndex = 0; ulIndex < ulSectionLength; ulIndex+=2, pucSRAMPtr+=2)
            {
                ulSum += (*pucSRAMPtr);
#ifdef _DEBUG
                ulPixelCnt++;
#endif
            }
        }

        DAT_wait(DAT_XFRID_WAITALL);	

    }

    // Calculate the final one section
    //DAT_wait(ulDMAID[!ulSectionID]);	

    pucSRAMPtr = g_L2_SRAM_ROI_DSP + (!ulSectionID) * ulSectionLength;
    for(ulIndex = 0; ulIndex < ulLastSectionLine*(a_ulProcWidth<<1); ulIndex+=2, pucSRAMPtr+=2)
    {
        ulSum += (*pucSRAMPtr);
#ifdef _DEBUG
        ulPixelCnt++;
#endif
    }

#ifdef _DEBUG
    assert(ulPixelCnt == a_ulProcWidth*a_ulProcHeight);
#endif

    (*a_pucLumaMean) = (UINT8) (ulSum / (a_ulProcWidth*a_ulProcHeight));

}

#ifndef WIN32 //Joey++ Performance Fine Tune

#pragma CODE_SECTION(ImgProc_MeanCalculate,   ".text:optimized");
__inline void ImgProc_MeanCalculate(

    const UINT8 *pucSRAMPtr,
    UINT8 a_ucLumaTh,
    UINT32 size,
    UINT32 *ulSum,
    UINT32 *ulSumL,
    UINT32 *ulSumH,
    UINT32 *a_pulCountMean_L,
    UINT32 *a_pulCountMean_H
)
{
    UINT32 ulIndex, cnt_l = 0, cnt_h = 0;
    const UINT8 *ptr = pucSRAMPtr;
    _nassert(size%2 == 0);
    
    #pragma MUST_ITERATE(1, ,2)
    for(ulIndex = 0; ulIndex < size; ulIndex+=2, ptr+=2)
    {
        *ulSum += *ptr;
        if(*ptr < a_ucLumaTh)
        {
            *ulSumL += *ptr;
            cnt_l++;
        }
        else
        {
            *ulSumH += *ptr;
            cnt_h++;        
        }    
    }
    *a_pulCountMean_H += cnt_h;
    *a_pulCountMean_L += cnt_l;    
}
#include "ioutil.h"
//////////////////////////////////////////////////////////////////////////
void ImgProc_ROISeperateMean(const UINT8 *restrict a_pucImgYUYVBuf, 
                             const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                             const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                             const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                             const UINT8 a_ucLumaTh,
                             UINT8 * a_pcLumaMean,
                             UINT8 * a_pucLumaMean_L,
                             UINT32 * a_pulCountMean_L,
                             UINT8 * a_pucLumaMean_H,
                             UINT32 * a_pulCountMean_H
                             )
{

    UINT32 ulY, ulIndex;
    UINT32 ulSectionIndex = 0;
    UINT32 ulMaxLineCntInSection = 65536 / (a_ulProcWidth<<1);
    UINT32 ulSectionCnt = (a_ulProcHeight)/ulMaxLineCntInSection;
    UINT32 ulSectionLength = ((ulMaxLineCntInSection * a_ulProcWidth)<<1);
    UINT32 ulSectionPitchLength = ((ulMaxLineCntInSection * a_ulBufferWidth)<<1);
    UINT32 ulSum = 0, ulSumL = 0, ulSumH = 0;
    const UINT8 * pucPtr = a_pucImgYUYVBuf + ((a_ulProcStartY * a_ulBufferWidth + a_ulProcStartX)<<1);
    UINT8 * pucSRAMPtr = 0;

    UINT32 ulSectionID = 0;
    UINT32 ulDMAID[2] = {0, 0};
    UINT32 ulLastSectionLine = a_ulProcHeight % ulMaxLineCntInSection;

    //assert(a_ulProcWidth * a_ulProcHeight < 96000);

    (*a_pulCountMean_L) = 0;
    (*a_pulCountMean_H) = 0;

    for(ulY = 0; ulY < a_ulProcHeight; ulY+=ulMaxLineCntInSection)
    {
        ulSectionIndex = ulY/ulMaxLineCntInSection;
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
            DAT_wait(ulDMAID[!ulSectionID]);	

            pucSRAMPtr = g_L2_SRAM_ROI_DSP + (!ulSectionID) * ulSectionLength;

            ImgProc_MeanCalculate(
            
                pucSRAMPtr,
                a_ucLumaTh,
                ulSectionLength,
                &ulSum,
                &ulSumL,
                &ulSumH,
                a_pulCountMean_L,
                a_pulCountMean_H
            );
                                  
        }

    }

    // Calculate the final one section
    DAT_wait(ulDMAID[ulSectionID]);		

    pucSRAMPtr = g_L2_SRAM_ROI_DSP + (ulSectionID) * ulSectionLength;
    
    //Memory2File("Crop24x24.raw", pucSRAMPtr, sizeof(UINT8) * ((a_ulProcHeight * a_ulProcWidth)<<1));

    ImgProc_MeanCalculate(
    
        pucSRAMPtr,
        a_ucLumaTh,
        ulLastSectionLine*(a_ulProcWidth<<1),
        &ulSum,
        &ulSumL,
        &ulSumH,
        a_pulCountMean_L,
        a_pulCountMean_H
    );
            
    assert(((*a_pulCountMean_L) + (*a_pulCountMean_H)) == a_ulProcWidth*a_ulProcHeight);

    (*a_pcLumaMean) = (UINT8) (ulSum / (a_ulProcWidth*a_ulProcHeight));
    (*a_pucLumaMean_L) = 0;
    (*a_pucLumaMean_H) = 0;

    if((*a_pulCountMean_L) > 0) (*a_pucLumaMean_L) = (UINT8) (ulSumL / (*a_pulCountMean_L));
    if((*a_pulCountMean_H) > 0) (*a_pucLumaMean_H) = (UINT8) (ulSumH / (*a_pulCountMean_H));

}

#else

//////////////////////////////////////////////////////////////////////////
void ImgProc_ROISeperateMean(   UINT8 * restrict a_pucImgYUYVBuf, 
                             const UINT32 a_ulBufferWidth, const UINT32 a_ulBufferHeight, 
                             const UINT32 a_ulProcStartX, const UINT32 a_ulProcStartY, 
                             const UINT32 a_ulProcWidth, const UINT32 a_ulProcHeight,
                             const UINT8 a_ucLumaTh,
                             UINT8 * a_pcLumaMean,
                             UINT8 * a_pucLumaMean_L,
                             UINT32 * a_pulCountMean_L,
                             UINT8 * a_pucLumaMean_H,
                             UINT32 * a_pulCountMean_H
                             )
{

    UINT32 ulY, ulIndex;
    UINT32 ulSectionIndex = 0;
    UINT32 ulMaxLineCntInSection = 65536 / (a_ulProcWidth<<1);
    UINT32 ulSectionCnt = (a_ulProcHeight)/ulMaxLineCntInSection;
    UINT32 ulSectionLength = ((ulMaxLineCntInSection * a_ulProcWidth)<<1);
    UINT32 ulSectionPitchLength = ((ulMaxLineCntInSection * a_ulBufferWidth)<<1);
    register UINT32 ulSum = 0, ulSumL = 0, ulSumH = 0;
    UINT8 * pucPtr = a_pucImgYUYVBuf + ((a_ulProcStartY * a_ulBufferWidth + a_ulProcStartX)<<1);
    UINT8 * pucSRAMPtr = 0;

    UINT32 ulSectionID = 0;
    UINT32 ulDMAID[2] = {0, 0};
    UINT32 ulLastSectionLine = a_ulProcHeight % ulMaxLineCntInSection;
    register UINT8 ucTmp = 0;

    //assert(a_ulProcWidth * a_ulProcHeight < 96000);

    (*a_pulCountMean_L) = 0;
    (*a_pulCountMean_H) = 0;

    for(ulY = 0; ulY < a_ulProcHeight; ulY+=ulMaxLineCntInSection)
    {
        ulSectionIndex = ulY/ulMaxLineCntInSection;
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
            DAT_wait(ulDMAID[!ulSectionID]);	

            pucSRAMPtr = g_L2_SRAM_ROI_DSP + (!ulSectionID) * ulSectionLength;
            for(ulIndex = 0; ulIndex < ulSectionLength; ulIndex+=2, pucSRAMPtr+=2)
            {
                ucTmp = *(pucSRAMPtr);
                ulSum += ucTmp;
                if(ucTmp < a_ucLumaTh)
                {
                    ulSumL += ucTmp;
                    (*a_pulCountMean_L) ++;
                }
                else
                {
                    ulSumH += ucTmp;
                    (*a_pulCountMean_H) ++;
                }
            }
        }
    }

    // Calculate the final one section
    DAT_wait(ulDMAID[ulSectionID]);	

    pucSRAMPtr = g_L2_SRAM_ROI_DSP + (ulSectionID) * ulSectionLength;


    for(ulIndex = 0; ulIndex < ulLastSectionLine*(a_ulProcWidth<<1); ulIndex+=2, pucSRAMPtr+=2)
    {
        ucTmp = *(pucSRAMPtr);
        ulSum += ucTmp;
        if(ucTmp < a_ucLumaTh)
        {
            ulSumL += ucTmp;
            (*a_pulCountMean_L) ++;
        }
        else
        {
            ulSumH += ucTmp;
            (*a_pulCountMean_H) ++;
        }
    }

    assert(((*a_pulCountMean_L) + (*a_pulCountMean_H)) == a_ulProcWidth*a_ulProcHeight);

    (*a_pcLumaMean) = (UINT8) (ulSum / (a_ulProcWidth*a_ulProcHeight));
    (*a_pucLumaMean_L) = 0;
    (*a_pucLumaMean_H) = 0;

    if((*a_pulCountMean_L) > 0) (*a_pucLumaMean_L) = (UINT8) (ulSumL / (*a_pulCountMean_L));
    if((*a_pulCountMean_H) > 0) (*a_pucLumaMean_H) = (UINT8) (ulSumH / (*a_pulCountMean_H));

}

#endif

