
#ifdef WIN32 // EAGLEK3_EAGLEK_MODE == EAGLEK3_EAGLEK_MODE_PC

#include <string.h>
#include <stdio.h>
#include "alPartLUT_v2.h"

#ifndef WIN32
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>
#include <ti/ipc/Ipc.h>
#include <ti/sysbios/BIOS.h> 
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/hal/Cache.h>
#include <assert.h>
#include "system_config.h"
#include "Error.h"
//#include "BirdView.h"
#include "shared_region_util.h"
#include "ioutil.h"
#include "common_defs.h"
#include "cmd_def.h"
// #include "img_mgr.h"
// #include "proc_birdview.h"
// #include "proc_alleyview.h"
// #include "proc_mod.h"
#endif


#ifdef WIN32    // Visual C++ platform
    #include <assert.h>
    #include "dat_copy.h"
    #ifndef _min2
    #define _min2 __min
    #endif
    #ifndef _max2
    #define _max2 __max
    #endif
#else           // Eagle2 platform
    #include <csl_dat.h>
//    #include "dat_copy.h"//hsin test 

#endif
//find if (A > 255) A = 255; if (A < 0) A = 0; else A = A;
#define FIND_BOUND(A)  _min2(_max2(A, 0), 255)
// #define FIND_BOUND(A) (A)

typedef struct
{
    alPartLUT_v2_Def *pSet;
    // UINT64 *pLut_data;
    UINT32 uStartBlk;
    UINT32 uEndBlk;    
    UINT16 uwImageWidth;
    UINT16 uwImageHeight; 
//    UINT8 **pucSrcBuffer;     
    UINT8 *pucDestBuffer; 
    UINT8 *pLut_data;
} AVM_LUT_PARA;
/*
lut format for single pixel:
multi-channel reference

A1: 3 bits, Dec of Y for 1st view
B1: 3 bits, Dec of X for 1st view
C1: 20 bits, Offset for 1st view, => Int X * Int Y
D1: 3 bits, View index for 1st view
A2: 3 bits, Dec of Y for 2nd view
B2: 3 bits, Dec of X for 2nd view
C2: 20 bits, Offset for 2nd view, => Int X * Int Y
D2: 3 bits, View index for 2nd view
E: 5 bits, Weighting value for pixel from 1st view. For 2nd view, it is (31 – E).
F: 1 bits, Indicate if this pixel is disabled, 0: enabled, 1: disabled

|F|E|D2|C2|B2|A2|D1|C1|B1|A1|
|1|5| 3|20| 3| 3| 3|20| 3| 3|
*/
typedef struct
{
    UINT32 decY1:3;          //A1: 3;
    UINT32 decX1:3;          //B1: 3;
    UINT32 offset1:20;       //C1: 20;
    UINT32 viewIdx1:3;       //D1: 3;
    UINT32 decY2:3;          //A2: 3;
    UINT32 decX2:3;          //B2: 3;
    UINT32 offset2:20;       //C2: 20;
    UINT32 viewIdx2:3;       //D2: 3;        
    UINT32 weight:5;        //E : 5;
    UINT32 isBlack:1;        //F : 1;
} PIXEL_INFO;
/*
single-channel reference

A1: 3 bits, Dec of Y for 1st view
B1: 3 bits, Dec of X for 1st view
C1: 20 bits, Offset for 1st view, => Int X * Int Y
D1: 3 bits, View index for 1st view
E: 2bits, reserve
F: 1 bits, Indicate if this pixel is disabled, 0: enabled, 1: disabled
|F|E|D1|C1|B1|A1|
|1|2| 3|20| 3| 3|
*/
typedef struct
{
    UINT32 decY1:3;          //A1: 3;
    UINT32 decX1:3;          //B1: 3;
    UINT32 offset1:20;       //C1: 20;
    UINT32 viewIdx1:3;       //D1: 3;    
    UINT32 reserve:2;        //E : 2;
    UINT32 isBlack:1;        //F : 1;
} PIXEL_INFO_SINGLE;
AVM_LUT_PARA AvmLutPara;

/*mask for speeding up black pixel compare.
 black index 0: not black pixel
 black index 1: black pixel*/
static const UINT8 g_ublackMask[2] = {0xFF, 0x00};

// /** \brief The AND value for interpolation weighting. */
// static const UINT32 g_ulWeightAND=(1<<8)-1;
// /** \brief The look-up table for interpolation weighting. */
// static const UINT32 g_ulDecimalWeightBilinear[8][8] = 
// {
//     {2147483648, 1828721152, 1526735872, 1224750592, 905988352, 604003072, 302017792, 32768 },
//     {1829896192, 1578045186, 1309482757, 1040854791, 789003786, 520441357, 251813391, 27922 },
//     {1529085952, 1310657797, 1092229642, 873735951, 655307796, 436879642, 218451487, 23332 },
//     {1228275712, 1043270151, 874976271, 689905431, 521611551, 336540711, 168246831, 18742 },
//     {910753792, 792594186, 657723156, 522786591, 387915561, 252978996, 118107966, 13897 },
//     {609943552, 525206797, 440470042, 338956071, 254219316, 169482817, 84746062, 9307 },
//     {309133312, 257819151, 223216927, 171837231, 120523326, 85921102, 34541406, 4717 },
//     {8388608, 7143442, 5963812, 4784182, 3539017, 2359387, 1179757, 128 }
// };
// /** \brief The bit shift for look-up table of interpolation weighting. */
// static const UINT32 g_ulWeightBITshift[4] = {24,16,8,0};

static const UINT16 g_ulDecimalWeightBilinearYY1[64] = 
{
    0x80, 0x6D, 0x5B, 0x49, 0x36, 0x24, 0x12, 0x00,
    0x6D, 0x5E, 0x4E, 0x3E, 0x2F, 0x1F, 0x0F, 0x00,
    0x5B, 0x4E, 0x41, 0x34, 0x27, 0x1A, 0x0D, 0x00,
    0x49, 0x3E, 0x34, 0x29, 0x1F, 0x14, 0x0A, 0x00,
    0x36, 0x2F, 0x27, 0x1F, 0x17, 0x0F, 0x07, 0x00,
    0x24, 0x1F, 0x1A, 0x14, 0x0F, 0x0A, 0x05, 0x00,
    0x12, 0x0F, 0x0D, 0x0A, 0x07, 0x05, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const UINT16 g_ulDecimalWeightBilinearYY2[64] = 
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x12, 0x0F, 0x0D, 0x0A, 0x07, 0x05, 0x02, 0x00,
    0x24, 0x1F, 0x1A, 0x14, 0x0F, 0x0A, 0x05, 0x00,
    0x36, 0x2F, 0x27, 0x1F, 0x17, 0x0F, 0x07, 0x00,
    0x49, 0x3E, 0x34, 0x29, 0x1F, 0x14, 0x0A, 0x00,
    0x5B, 0x4E, 0x41, 0x34, 0x27, 0x1A, 0x0D, 0x00,
    0x6D, 0x5E, 0x4E, 0x3E, 0x2F, 0x1F, 0x0F, 0x00,
    0x80, 0x6D, 0x5B, 0x49, 0x36, 0x24, 0x12, 0x00
};
static const UINT16 g_ulDecimalWeightBilinearYY3[64] = 
{
    0x00, 0x12, 0x24, 0x36, 0x49, 0x5B, 0x6D, 0x80,
    0x00, 0x0F, 0x1F, 0x2F, 0x3E, 0x4E, 0x5E, 0x6D,
    0x00, 0x0D, 0x1A, 0x27, 0x34, 0x41, 0x4E, 0x5B,
    0x00, 0x0A, 0x14, 0x1F, 0x29, 0x34, 0x3E, 0x49,
    0x00, 0x07, 0x0F, 0x17, 0x1F, 0x27, 0x2F, 0x36,
    0x00, 0x05, 0x0A, 0x0F, 0x14, 0x1A, 0x1F, 0x24,
    0x00, 0x02, 0x05, 0x07, 0x0A, 0x0D, 0x0F, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const UINT16 g_ulDecimalWeightBilinearYY4[64] = 
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x05, 0x07, 0x0A, 0x0D, 0x0F, 0x12,
    0x00, 0x05, 0x0A, 0x0F, 0x14, 0x1A, 0x1F, 0x24,
    0x00, 0x07, 0x0F, 0x17, 0x1F, 0x27, 0x2F, 0x36,
    0x00, 0x0A, 0x14, 0x1F, 0x29, 0x34, 0x3E, 0x49,
    0x00, 0x0D, 0x1A, 0x27, 0x34, 0x41, 0x4E, 0x5B,
    0x00, 0x0F, 0x1F, 0x2F, 0x3E, 0x4E, 0x5E, 0x6D,
    0x00, 0x12, 0x24, 0x36, 0x49, 0x5B, 0x6D, 0x80
};
//static void Memory2File(char *filename, char *buf, int size)
//{
//    FILE *pf = NULL;
//   
//    pf = fopen(filename, "wb");
//    if (NULL == pf) {
//        printf("can not create file %s.\n", filename);
//        return;
//    }
//    
//    fwrite(buf, sizeof(unsigned char), size, pf);
//
//    fclose(pf);
//}

//unsigned char Black_Idx_O[360*480*5];
//unsigned int Black_Idx_Len[480];
//UINT8 *Black_Idx_E;
//UINT8 *W1_E, *W2_E, *W2_O, *W1_O; 

// Get the Y mean Offset for Global AE.
char g_cOffset_Ymean_Firmware[4] = {0};

static UINT8 pucDstBuf1D[192*1024];//for verifying partitoned lut data
//static UINT8 pucBlackBuff[192*1024];//for verifying partitoned lut data

#ifdef WIN32
  static UINT8 L2_SRAM[192*1024];
  static UINT8 *L2_addr_DSP = &(L2_SRAM[0]);
  static UINT8 *L2_addr_DMA = &(L2_SRAM[0]);
#else
  static UINT8 *L2_addr_DSP = (UINT8 *) 0x10800000;
  static UINT8 *L2_addr_DMA = (UINT8 *) 0x40800000;
#endif
static UINT32 g_uEnL2Num[2] = {0};

//void TABLELU_CreatePerfLUT(TABLELUT_Def * a_ptTable)
//{
//    INT32 lX, lY;
//    UINT32 cnt = 0, cnt_b = 0;
//    UINT64 * pullLUTPtr = 0;
//    
//    Black_Idx_E = (UINT8 *)sharedMemAlloc(SHARED_FRAME_BUFFER_REGION_IDX, ROUNDUP_SIZE(720*240,128)); 
//
////    Black_Idx_O = Black_Idx_E + 720*480; 
//
//    W1_E = Black_Idx_O + 360*480; 
//    W2_E = W1_E + 360*480; 
//    W1_O = W2_E + 360*480; 
//    W2_O = W1_O + 360*480; 
//    
////    Cache_inv((Ptr)W1_E, 720*480,Cache_Type_ALL, TRUE);
////    
//     memset(Black_Idx_E, 0x00, 360*480);
////    
////    Cache_wbInv((Ptr) W1_E, 720*480, Cache_Type_ALL, TRUE);
//    
//                        
////    Memory2File("W1_E.bin", W1_E, 720*480);
//                        
//    for(lY = 0; lY < a_ptTable->tDestAreaSize.Y; lY++)
//    {
//
//        pullLUTPtr = a_ptTable->pullTable + lY * a_ptTable->tDestAreaSize.X;
//        
//        for(lX = 0; lX < a_ptTable->tDestAreaSize.X; lX+=2)
//        {
//            Black_Idx_E[cnt] = ((*pullLUTPtr)>>TABLELU_SHIFT_ENABLE)&TABLELU_AND_ENABLE;
//            W1_E[cnt] = ((*pullLUTPtr)>>TABLELU_SHIFT_WEIGHT)&TABLELU_AND_WEIGHT;
//            W2_E[cnt] = TABLELU_AND_WEIGHT - W1_E[cnt];
//            pullLUTPtr++;
//            Black_Idx_O[cnt] = ((*pullLUTPtr)>>TABLELU_SHIFT_ENABLE)&TABLELU_AND_ENABLE;   
//            W1_O[cnt] = ((*pullLUTPtr)>>TABLELU_SHIFT_WEIGHT)&TABLELU_AND_WEIGHT;
//            W2_O[cnt] = TABLELU_AND_WEIGHT - W1_O[cnt];   
//            
//            cnt++;                          
//            pullLUTPtr++;
//        }
//      
//    }
//    
////    Memory2File("W1_E_1.bin", W1_E, 720*480); 
//
//}
//
////#if 1
//void TABLELU_ProcessFullLU_Rear(TABLELUT_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage)
//{
//    INT32 lX, lY;
//
//    UINT8 * pucDstPtr = 0;
//    UINT64 * pullLUTPtr = 0;
//
//    UINT8 ucCameraIndex1, ucCameraIndex2 = 0;
//    UINT32 ulOffset1, ulOffset2;
//    UINT8 ucDecX1, ucDecY1, ucDecX2, ucDecY2;
////    UINT8 ucWeight1, ucWeight2;
//    UINT8 ucBlack;
//    UINT8 ucY1, ucY2, ucY3, ucY4;
//    UINT8 ucY, ucIntpoY1 = 0, ucIntpoY2 = 0;
//    UINT8 ucU, ucV, ucU1 = 0, ucV1 = 0, ucU2 = 0, ucV2 = 0;
//    UINT32 pattern = 0x80008000, *img_ptr = (UINT32 *)a_pucDstImage, count = 0;
//    UINT32 index = 0;    
//    //Draw Black Parts   
//    index = a_ptTable->tDestAreaSize.Y * a_ptTable->tDestAreaSize.X; 
//    for(lX = 0; lX < index; lX+=2, img_ptr++)
//        *img_ptr = pattern;         
////    //Draw Black Parts    
////    for(lY = 0; lY < a_ptTable->tDestAreaSize.Y; lY++)    
////         for(lX = 0; lX < a_ptTable->tDestAreaSize.X; lX+=2, img_ptr++)
////            *img_ptr = pattern;
//    // Even Pixel
//    for(lY = 0; lY < a_ptTable->tDestAreaSize.Y; lY++, count+=(a_ptTable->tDestAreaSize.X>>1) )
//    {
//        pucDstPtr = a_pucDstImage + (a_ptTable->tDestStartPoint.X<<1) + (a_ptTable->tDestStartPoint.Y + lY) * (a_ptTable->tDestImageBufferSize.X<<1);
//        pullLUTPtr = a_ptTable->pullTable + lY * a_ptTable->tDestAreaSize.X;                                      
//
//        IMG_LUTWeightCal_Even(a_pucSrcImage, pucDstPtr, &Black_Idx_E[count], 
//                         &W1_E[count], &W2_E[count], pullLUTPtr, a_ptTable->tDestAreaSize.X, a_ptTable);
////    }
//    
////    count = 0;    
//     // To next pixel - Odd Pixel
////    for(lY = 0; lY < a_ptTable->tDestAreaSize.Y; lY++,  count+=(a_ptTable->tDestAreaSize.X>>1))
////    {
////        pucDstPtr = a_pucDstImage + (a_ptTable->tDestStartPoint.X<<1) + (a_ptTable->tDestStartPoint.Y + lY) * (a_ptTable->tDestImageBufferSize.X<<1);
//        pullLUTPtr = a_ptTable->pullTable + lY * a_ptTable->tDestAreaSize.X + 1;
//        
//        IMG_LUTWeightCal_Odd(a_pucSrcImage, pucDstPtr, &Black_Idx_O[count], 
//                         &W1_O[count], &W2_O[count], pullLUTPtr, a_ptTable->tDestAreaSize.X, a_ptTable);
//          
//    } 
//}                     
////#else
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void TABLELU_ProcessFullLU_Top(TABLELUT_Def * a_ptTable, UINT8 ** a_pucSrcImage, UINT8 * a_pucDstImage)
//{
//    INT32 lX, lY;
//
//    UINT8 * pucDstPtr = 0;
//    UINT64 * pullLUTPtr = 0;
//
//    UINT8 ucCameraIndex1, ucCameraIndex2 = 0;
//    UINT32 ulOffset1, ulOffset2;
//    UINT8 ucDecX1, ucDecY1, ucDecX2, ucDecY2;
//    UINT8 ucWeight1, ucWeight2;
//    UINT8 ucBlack;
//    UINT8 ucY1, ucY2, ucY3, ucY4;
//    UINT8 ucY, ucIntpoY1 = 0, ucIntpoY2 = 0;
//    UINT8 ucU, ucV, ucU1 = 0, ucV1 = 0, ucU2 = 0, ucV2 = 0;
//
//    for(lY = 0; lY < a_ptTable->tDestAreaSize.Y; lY++)
//    {
//        pucDstPtr = a_pucDstImage + (a_ptTable->tDestStartPoint.X<<1) + (a_ptTable->tDestStartPoint.Y + lY) * (a_ptTable->tDestImageBufferSize.X<<1);
//        pullLUTPtr = a_ptTable->pullTable + lY * a_ptTable->tDestAreaSize.X;
//           
//        for(lX = 0; lX < a_ptTable->tDestAreaSize.X; lX+=2, pucDstPtr += 4)
//        {
//            // Even Pixel
//            ucBlack = ((*pullLUTPtr)>>TABLELU_SHIFT_ENABLE)&TABLELU_AND_ENABLE;                    
//            if(ucBlack == 0)
//            {
//                // 解出第一組Pixel的Weight值
//                ucWeight1 = ((*pullLUTPtr)>>TABLELU_SHIFT_WEIGHT)&TABLELU_AND_WEIGHT;
//
//                if(ucWeight1 > 0) // Weight值為0時，就不用做查表
//                {
//
//                    // 解出第一組Pixel的Dec,Offset,Camera值
//                    ucDecY1 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECY_1)&TABLELU_AND_DECY_1;
//                    ucDecX1 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECX_1)&TABLELU_AND_DECX_1;
//                    ulOffset1 = ((*pullLUTPtr)>>TABLELU_SHIFT_OFFSET_1)&TABLELU_AND_OFFSET_1;
//                    ucCameraIndex1 = ((*pullLUTPtr)>>TABLELU_SHIFT_CAM_1)&TABLELU_AND_CAM_1;
//
//                    // 根據Dec做內插
//			        ucY1 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1)<<1));
//			        ucY2 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + 1)<<1));
//                    ucY3 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].X)<<1));
//			        ucY4 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].X + 1)<<1));
//
//			        ucIntpoY1 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
//		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
//				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
//				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;
//
//                    // 取出 U1, V1 值
//                    if(ulOffset1 % 2 == 0)
//                    {
//                        // Even
//                        ucU1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 1];
//                        ucV1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 3];
//                    }
//                    else
//                    {
//                        // Odd
//                        ucU1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) - 1];
//                        ucV1 = a_pucSrcImage[ucCameraIndex1][(ulOffset1<<1) + 1];
//                   }
//                }
//
//                // 解出第二組Pixel的Weight值
//                ucWeight2 = TABLELU_AND_WEIGHT - ucWeight1;
//
//                if(ucWeight2 > 0) // Weight值為0時，就不用做查表
//                {
//                    // 解出第二組Pixel的Dec,Offset,Camera值
//                    ucDecY2 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECY_2)&TABLELU_AND_DECY_2;
//                    ucDecX2 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECX_2)&TABLELU_AND_DECX_2;
//                    ulOffset2 = ((*pullLUTPtr)>>TABLELU_SHIFT_OFFSET_2)&TABLELU_AND_OFFSET_2;
//                    ucCameraIndex2 = ((*pullLUTPtr)>>TABLELU_SHIFT_CAM_2)&TABLELU_AND_CAM_2;
//
//			        ucY1 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2)<<1));
//			        ucY2 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + 1)<<1));
//                    ucY3 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].X)<<1));
//			        ucY4 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].X + 1)<<1));
//
//			        ucIntpoY2 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
//		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
//				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
//				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;
//
//                    // U2, V2
//                    if(ulOffset2 % 2 == 0)
//                    {
//                        // Even
//                        ucU2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 1];
//                        ucV2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 3];
//                    }
//                    else
//                    {
//                        // Odd
//                        ucU2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) - 1];
//                        ucV2 = a_pucSrcImage[ucCameraIndex2][(ulOffset2<<1) + 1];
//                   }
//                }
//
//                // 將兩組Pixel的數值做weighting
//                ucY = (INT32)(ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)/TABLELU_AND_WEIGHT;
//                ucU = (INT32)(ucWeight1 * ucU1 + ucWeight2 * ucU2)/TABLELU_AND_WEIGHT;
//                ucV = (INT32)(ucWeight1 * ucV1 + ucWeight2 * ucV2)/TABLELU_AND_WEIGHT;
//
//                *(pucDstPtr    ) = ucY;
//                *(pucDstPtr + 1) = ucU;
//                *(pucDstPtr + 3) = ucV;
//            }
//            else
//            {
//                *(pucDstPtr    ) = 0;
//                *(pucDstPtr + 1) = 128;
//                *(pucDstPtr + 3) = 128;
//            }
//
//            // To next pixel - Odd Pixel
//            pullLUTPtr++;
//
//            // Odd Pixel
//            ucBlack = ((*pullLUTPtr)>>TABLELU_SHIFT_ENABLE)&TABLELU_AND_ENABLE;
//            if(ucBlack == 0)
//            {
//
//                ucWeight1 = ((*pullLUTPtr)>>TABLELU_SHIFT_WEIGHT)&TABLELU_AND_WEIGHT;
//
//                if(ucWeight1 > 0)
//                {
//                    ucDecY1 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECY_1)&TABLELU_AND_DECY_1;
//                    ucDecX1 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECX_1)&TABLELU_AND_DECX_1;
//                    ulOffset1 = ((*pullLUTPtr)>>TABLELU_SHIFT_OFFSET_1)&TABLELU_AND_OFFSET_1;
//                    ucCameraIndex1 = ((*pullLUTPtr)>>TABLELU_SHIFT_CAM_1)&TABLELU_AND_CAM_1;
//
//			        ucY1 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1)<<1));
//			        ucY2 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + 1)<<1));
//                    ucY3 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].X)<<1));
//			        ucY4 = *(a_pucSrcImage[ucCameraIndex1] + ((ulOffset1 + a_ptTable->atSrcImageSize[ucCameraIndex1].X + 1)<<1));
//
//			        ucIntpoY1 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
//		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
//				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
//				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX1][ucDecY1]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;
//                }
//                
//                ucWeight2 = TABLELU_AND_WEIGHT - ucWeight1;
//                if(ucWeight2 > 0)
//                {
//                    ucDecY2 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECY_2)&TABLELU_AND_DECY_2;
//                    ucDecX2 = ((*pullLUTPtr)>>TABLELU_SHIFT_DECX_2)&TABLELU_AND_DECX_2;
//                    ulOffset2 = ((*pullLUTPtr)>>TABLELU_SHIFT_OFFSET_2)&TABLELU_AND_OFFSET_2;
//                    ucCameraIndex2 = ((*pullLUTPtr)>>TABLELU_SHIFT_CAM_2)&TABLELU_AND_CAM_2;
//
//			        ucY1 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2)<<1));
//			        ucY2 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + 1)<<1));
//                    ucY3 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].X)<<1));
//			        ucY4 = *(a_pucSrcImage[ucCameraIndex2] + ((ulOffset2 + a_ptTable->atSrcImageSize[ucCameraIndex2].X + 1)<<1));
//
//			        ucIntpoY2 = ( ucY1 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[0])&g_ulWeightAND)+
//		  		          ucY2 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[1])&g_ulWeightAND)+
//				          ucY3 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[2])&g_ulWeightAND)+
//				          ucY4 *((g_ulDecimalWeightBilinear[ucDecX2][ucDecY2]>>g_ulWeightBITshift[3])&g_ulWeightAND))>>7;
//                }
//
//                // 將兩組Pixel的數值做weighting
//                ucY = (ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)/TABLELU_AND_WEIGHT;
//
//                *(pucDstPtr + 2) = ucY;
//            }
//            else
//            {
//                *(pucDstPtr + 2) = 0;
//            }
//
//            pullLUTPtr++;
//
//        }
//    }
//}
    
static void BufferSwap(UINT32 *pA, UINT32 *pB)
{
    UINT32 tmp;
    tmp = *pA;
    *pA = *pB;
    *pB = tmp;
}
#if 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void TABLELU_ProcessBlockLut(UINT8 * a_pLut, UINT8 * a_pucSrcImage, UINT32 * a_pucSrcOffset, UINT8 * a_pucDstImage, alPartLUT_v2_3DBlockInfo_t * a_pBInfo)
{
    INT32 lX, lY;

    UINT8 * pucDstPtr = 0;
    UINT64 * pullLUTPtr = 0;
    UINT32  ucDstPtrShift = 0;
    UINT64  ullLUTPtrShift = 0;
    
    UINT8 ucCameraIndex1, ucCameraIndex2 = 0;
    UINT32 ulOffset1, ulOffset2;
    UINT8 ucDecX1, ucDecY1, ucDecX2, ucDecY2;
    UINT8 ucWeight1, ucWeight2;
    UINT8 ucBlack;
    UINT8 ucY1, ucY2, ucY3, ucY4;
    UINT8 ucY1_chan2, ucY2_chan2, ucY3_chan2, ucY4_chan2;    
    UINT8 ucY, ucIntpoY1 = 0, ucIntpoY2 = 0;
    UINT8 ucU, ucV, ucU1 = 0, ucV1 = 0, ucU2 = 0, ucV2 = 0;
    PIXEL_INFO *ptPixelInfo = NULL;
    UINT8 ucDecXY1,ucDecXY2;
	INT16   wTmp1, wTmp2;

    // UINT32 ucPixNum = 0;
    UINT64 * pullDstImage = (UINT64*) a_pucDstImage;
    UINT8 * a_pucSrcImage1 = NULL;
    UINT8 * a_pucSrcImage2 = NULL;

    UINT64 *pLut = (UINT64*)a_pLut;
//
//    if(a_pBInfo->bBlackArea)
//    {
//        for(ucPixNum=0; ucPixNum < a_pBInfo->lut_num; ucPixNum+=4, pullDstImage++ )
//        {
//            *(pullDstImage) = 0x8000800080008000;
//        }
//            
//        return;
//    }

    // for(lY = 0; lY < a_pBInfo->dst_area.height; lY++)
    for(lY = a_pBInfo->dst_area.height; lY != 0; lY--)        
    {
        pucDstPtr = a_pucDstImage + ucDstPtrShift;
        pullLUTPtr = pLut + ullLUTPtrShift;
        ucDstPtrShift += (a_pBInfo->dst_area.width<<1);
        ullLUTPtrShift += a_pBInfo->dst_area.width;
        ptPixelInfo = (PIXEL_INFO*)pullLUTPtr;
        // for(lX = 0; lX < a_pBInfo->dst_area.width; lX+=2, pucDstPtr += 4)        
        for(lX = a_pBInfo->dst_area.width; lX != 0 ; lX-=2, pucDstPtr += 4)
        {
            // Even Pixel
            // ucBlack = ptPixelInfo->isBlack; 
            ucBlack = g_ublackMask[ptPixelInfo->isBlack];               
              
            // 解出第一組Pixel的Weight值
            ucWeight1 = ptPixelInfo->weight;

            // 解出第一組Pixel的Dec,Offset,Camera值
            ucDecX1 = ptPixelInfo->decX1;
            ucDecY1 = ptPixelInfo->decY1;
            ulOffset1 = ptPixelInfo->offset1;
            ucDecXY1 = ucDecY1+(ucDecX1<<3);

            ucCameraIndex1 = ptPixelInfo->viewIdx1;
            ucCameraIndex2 = ptPixelInfo->viewIdx2;

            a_pucSrcImage1 = a_pucSrcImage + a_pucSrcOffset[ucCameraIndex1];
            a_pucSrcImage2 = a_pucSrcImage + a_pucSrcOffset[ucCameraIndex2];
            // 根據Dec做內插
			ucY1 = *(a_pucSrcImage1 + ((ulOffset1)<<1));
            ucY2 = *(a_pucSrcImage1 + ((ulOffset1 + 1)<<1));            
            ucY3 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width)<<1));
            ucY4 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width + 1)<<1));
            ucIntpoY1 = ( ucY1 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY1))+
                          ucY2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY1))+
                          ucY3 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY1))+
                          ucY4 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY1)))>>7;
            //global AE                  
            wTmp1 = (INT16)ucIntpoY1 + g_cOffset_Ymean_Firmware[ucCameraIndex1];//a_pBInfo->ch_area[ucCameraIndex1].ch_idx];
            ucIntpoY1 = FIND_BOUND(wTmp1); 

            // 取出 U1, V1 值
            ucU1 = *(a_pucSrcImage1 +(ulOffset1<<1) + (1 - ((ulOffset1&1)<<1)));
            ucV1 = *(a_pucSrcImage1 +(ulOffset1<<1) + (3 - ((ulOffset1&1)<<1)));


            // 解出第二組Pixel的Weight值
            ucWeight2 = alLUT_v2_AND_WEIGHT - ucWeight1;

            // 解出第二組Pixel的Dec,Offset,Camera值
            ucDecX2 = ptPixelInfo->decX2;
            ucDecY2 = ptPixelInfo->decY2;
            ulOffset2 = ptPixelInfo->offset2;  
            ucDecXY2 = ucDecY2+(ucDecX2<<3);                      

			ucY1_chan2 = *(a_pucSrcImage2 + ((ulOffset2)<<1));
			ucY2_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + 1)<<1));
            ucY3_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[ucCameraIndex2].width)<<1));
			ucY4_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[ucCameraIndex2].width + 1)<<1));		        
            ucIntpoY2 = ( ucY1_chan2 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY2))+
                          ucY2_chan2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY2))+
                          ucY3_chan2 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY2))+
                          ucY4_chan2 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY2)))>>7;
            //global AE                  
            wTmp2 = (INT16)ucIntpoY2 + g_cOffset_Ymean_Firmware[ucCameraIndex2];//a_pBInfo->ch_area[ucCameraIndex2].ch_idx];
            ucIntpoY2 = FIND_BOUND(wTmp2); 

            // U2, V2
            ucU2 = *(a_pucSrcImage2 +(ulOffset2<<1) + (1 - ((ulOffset2&1)<<1)));
            ucV2 = *(a_pucSrcImage2 +(ulOffset2<<1) + (3 - ((ulOffset2&1)<<1)));   


            ucWeight1 = (ucWeight1>0) ? (ucWeight1+1) : ucWeight1;
            ucWeight2 = (ucWeight2>30) ? (ucWeight2+1) : ucWeight2;
                
            // 將兩組Pixel的數值做weighting
            ucY = (INT32)(ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)>>5;
            ucU = (INT32)(ucWeight1 * ucU1 + ucWeight2 * ucU2)>>5;
            ucV = (INT32)(ucWeight1 * ucV1 + ucWeight2 * ucV2)>>5;

            // *(pucDstPtr    ) = 0 + ((!ucBlack)*(ucY));
            // *(pucDstPtr + 1) = (ucBlack<<7)/*128*ucBlack*/ + ((!ucBlack)*ucU );
            // *(pucDstPtr + 3) = (ucBlack<<7)/*128*ucBlack*/ + ((!ucBlack)*ucV );
            *(pucDstPtr    ) = 0 + ((ucBlack)&(ucY));
            *(pucDstPtr + 1) = ((~ucBlack)&0x80)/*128*ucBlack*/ + ((ucBlack)&ucU );
            *(pucDstPtr + 3) = ((~ucBlack)&0x80)/*128*ucBlack*/ + ((ucBlack)&ucV );


            // To next pixel - Odd Pixel
            ptPixelInfo++;
            
            // Odd Pixel
            // ucBlack = ptPixelInfo->isBlack;  
            ucBlack = g_ublackMask[ptPixelInfo->isBlack];               

            // 解出第一組Pixel的Weight值
            ucWeight1 = ptPixelInfo->weight;

            ucDecX1 = ptPixelInfo->decX1;
            ucDecY1 = ptPixelInfo->decY1;
            ulOffset1 = ptPixelInfo->offset1;                    
            ucDecXY1 = ucDecY1+(ucDecX1<<3);                      

            ucCameraIndex1 = ptPixelInfo->viewIdx1;
            ucCameraIndex2 = ptPixelInfo->viewIdx2;
            a_pucSrcImage1 = a_pucSrcImage + a_pucSrcOffset[ucCameraIndex1];
            a_pucSrcImage2 = a_pucSrcImage + a_pucSrcOffset[ucCameraIndex2];


			ucY1 = *(a_pucSrcImage1 + ((ulOffset1)<<1));
			ucY2 = *(a_pucSrcImage1 + ((ulOffset1 + 1)<<1));
            ucY3 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width)<<1));
			ucY4 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width + 1)<<1));                                      
            ucIntpoY1 = ( ucY1 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY1))+
                          ucY2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY1))+
                          ucY3 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY1))+
                          ucY4 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY1)))>>7;
            //global AE                  
            wTmp1 = (INT16)ucIntpoY1 + g_cOffset_Ymean_Firmware[ucCameraIndex1];//a_pBInfo->ch_area[ucCameraIndex1].ch_idx];
            ucIntpoY1 = FIND_BOUND(wTmp1); 

            // 解出第二組Pixel的Weight值
            ucWeight2 = alLUT_v2_AND_WEIGHT - ucWeight1;

            ucDecX2 = ptPixelInfo->decX2;
            ucDecY2 = ptPixelInfo->decY2;
            ulOffset2 = ptPixelInfo->offset2;                    
            ucDecXY2 = ucDecY2+(ucDecX2<<3);                      

            ucY1_chan2 = *(a_pucSrcImage2 + ((ulOffset2)<<1));
            ucY2_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + 1)<<1));
            ucY3_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[ucCameraIndex2].width)<<1));
            ucY4_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[ucCameraIndex2].width + 1)<<1));                          

            ucIntpoY2 = ( ucY1_chan2 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY2))+
                          ucY2_chan2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY2))+
                          ucY3_chan2 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY2))+
                          ucY4_chan2 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY2)))>>7;
            //global AE                  
            wTmp2 = (INT16)ucIntpoY2 + g_cOffset_Ymean_Firmware[ucCameraIndex2];//_bInfo.ch_area[ucCameraIndex2].ch_idx];
            ucIntpoY2 = FIND_BOUND(wTmp2); 

            ucWeight1 = (ucWeight1>0) ? (ucWeight1+1) : ucWeight1;
            ucWeight2 = (ucWeight2>30) ? (ucWeight2+1) : ucWeight2;
             
            // 將兩組Pixel的數值做weighting
            ucY = (ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)>>5;

            // *(pucDstPtr + 2) = 0 + ((~ucBlack)&ucY);
            *(pucDstPtr + 2) = 0 + ((ucBlack)&ucY);
           
            ptPixelInfo++;

        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TABLELU_ProcessBlockLut_SingleChannel(UINT8 * a_pLut, UINT8 * a_pucSrcImage1, UINT8 * a_pucDstImage, alPartLUT_v2_3DBlockInfo_t * a_pBInfo)
{
    INT32 lX, lY;

    UINT8 * pucDstPtr = 0;
    UINT32 * pullLUTPtr = 0;
    UINT32  ucDstPtrShift = 0;
    UINT32  ullLUTPtrShift = 0;
    
    UINT8 ucCameraIndex1 = 0;
    UINT32 ulOffset1;//, ulOffset2;
    UINT8 ucDecX1, ucDecY1;//, ucDecX2, ucDecY2;
    UINT8 ucWeight1 = 0;//, ucWeight2;
    UINT8 ucBlack;
    UINT8 ucY1, ucY2, ucY3, ucY4;
    // UINT8 ucY1_chan2, ucY2_chan2, ucY3_chan2, ucY4_chan2;    
    UINT8 ucY =0, ucIntpoY1 = 0, ucIntpoY2 = 0;
    UINT8 ucU =0, ucV = 0, ucU1 = 0, ucV1 = 0;//, ucU2 = 0, ucV2 = 0;
    PIXEL_INFO_SINGLE *ptPixelInfo = NULL;
    UINT8 ucDecXY1;//,ucDecXY2;
	INT16   wTmp1;//, wTmp2;

    UINT32 ucPixNum = 0;
    UINT64 * pullDstImage = (UINT64*) a_pucDstImage;
    UINT32 *pLut = (UINT32*)a_pLut;
 
    if(a_pBInfo->bBlackArea)
    {
        for(ucPixNum=0; ucPixNum < a_pBInfo->lut_num; ucPixNum+=4, pullDstImage++ )
        {
            *(pullDstImage) = 0x8000800080008000;
        }
            
        return;
    }

    // for(lY = 0; lY < a_pBInfo->dst_area.height; lY++)
    for(lY = a_pBInfo->dst_area.height; lY != 0 ; lY--)        
    {
        pucDstPtr = a_pucDstImage + ucDstPtrShift;
		pullLUTPtr = pLut + ullLUTPtrShift;
        ucDstPtrShift += (a_pBInfo->dst_area.width<<1);
        ullLUTPtrShift += a_pBInfo->dst_area.width;
		ptPixelInfo = (PIXEL_INFO_SINGLE*)pullLUTPtr;
        // for(lX = 0; lX < a_pBInfo->dst_area.width; lX+=2, pucDstPtr += 4)        
        for(lX = a_pBInfo->dst_area.width; lX != 0 ; lX-=2, pucDstPtr += 4)
        {
            // Even Pixel
            // ucBlack = ptPixelInfo->isBlack;    
            ucBlack = g_ublackMask[ptPixelInfo->isBlack];               

            // 解出第一組Pixel的Weight值
//            ucWeight1 = ptPixelInfo->weight;

            // 解出第一組Pixel的Dec,Offset,Camera值
            ucDecX1 = ptPixelInfo->decX1;
            ucDecY1 = ptPixelInfo->decY1;
            ulOffset1 = ptPixelInfo->offset1;
            ucDecXY1 = ucDecY1+(ucDecX1<<3);          

            ucCameraIndex1 = ptPixelInfo->viewIdx1;

            // 根據Dec做內插
			ucY1 = *(a_pucSrcImage1 + ((ulOffset1)<<1));
			ucY2 = *(a_pucSrcImage1 + ((ulOffset1 + 1)<<1));
            ucY3 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width)<<1));
			ucY4 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width + 1)<<1));
            ucIntpoY1 = ( ucY1 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY1))+
                          ucY2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY1))+
                          ucY3 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY1))+
                          ucY4 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY1)))>>7;
            //global AE                  
            wTmp1 = (INT16)ucIntpoY1 + g_cOffset_Ymean_Firmware[ucCameraIndex1];//a_pBInfo->ch_area[ucCameraIndex1].ch_idx];
            ucIntpoY1 = FIND_BOUND(wTmp1); 

            // 取出 U1, V1 值
            ucU1 = *(a_pucSrcImage1 +(ulOffset1<<1) + (1 - ((ulOffset1&1)<<1)));
            ucV1 = *(a_pucSrcImage1 +(ulOffset1<<1) + (3 - ((ulOffset1&1)<<1)));

/*
            // 解出第二組Pixel的Weight值
            ucWeight2 = LUT_v2_AND_WEIGHT - ucWeight1;

            // 解出第二組Pixel的Dec,Offset,Camera值
            ucDecX2 = ptPixelInfo->decX2;
            ucDecY2 = ptPixelInfo->decY2;
            ulOffset2 = ptPixelInfo->offset2;  
            ucDecXY2 = ucDecX2+(ucDecY2<<3);                      

			ucY1_chan2 = *(a_pucSrcImage2 + ((ulOffset2)<<1));
			ucY2_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + 1)<<1));
            ucY3_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[1].width)<<1));
			ucY4_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[1].width + 1)<<1));		        
            ucIntpoY2 = ( ucY1_chan2 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY2))+
                          ucY2_chan2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY2))+
                          ucY3_chan2 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY2))+
                          ucY4_chan2 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY2)))>>6;
            //global AE                  
            wTmp2 = (INT16)ucIntpoY2 + g_cOffset_Ymean_Firmware[a_pBInfo->ch_area[1].ch_idx];
            ucIntpoY2 = (wTmp2>255)?255:((wTmp2<0)?0:wTmp2); 

            // U2, V2
            ucU2 = *(a_pucSrcImage2 +(ulOffset2<<1) + (1 - ((ulOffset2&1)<<1)));
            ucV2 = *(a_pucSrcImage2 +(ulOffset2<<1) + (3 - ((ulOffset2&1)<<1)));   


           ucWeight1 = (ucWeight1>16) ? (ucWeight1+1) : ucWeight1;
           ucWeight2 = (ucWeight2>16) ? (ucWeight2+1) : ucWeight2;
                
           // 將兩組Pixel的數值做weighting
           ucY = (INT32)(ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)>>5;
           ucU = (INT32)(ucWeight1 * ucU1 + ucWeight2 * ucU2)>>5;
           ucV = (INT32)(ucWeight1 * ucV1 + ucWeight2 * ucV2)>>5;
*/
             // *(pucDstPtr    ) = 0 + ((!ucBlack)*(ucIntpoY1));
             // *(pucDstPtr + 1) = (ucBlack<<7)/*128*ucBlack*/ + ((!ucBlack)*ucU1 );
             // *(pucDstPtr + 3) = (ucBlack<<7)/*128*ucBlack*/ + ((!ucBlack)*ucV1 );
           *(pucDstPtr    ) = 0 + ((ucBlack)&(ucIntpoY1));
           *(pucDstPtr + 1) = ((~ucBlack)&0x80)/*128*ucBlack*/ + ((ucBlack)&ucU1 );
           *(pucDstPtr + 3) = ((~ucBlack)&0x80)/*128*ucBlack*/ + ((ucBlack)&ucV1 );           

            // To next pixel - Odd Pixel
            ptPixelInfo++;
            
            // Odd Pixel
            // ucBlack = ptPixelInfo->isBlack;   
            ucBlack = g_ublackMask[ptPixelInfo->isBlack];               


            // 解出第一組Pixel的Weight值
//            ucWeight1 = ptPixelInfo->weight;

            ucDecX1 = ptPixelInfo->decX1;
            ucDecY1 = ptPixelInfo->decY1;
            ulOffset1 = ptPixelInfo->offset1;                    
            ucDecXY1 = ucDecY1+(ucDecX1<<3);                      

            ucCameraIndex1 = ptPixelInfo->viewIdx1;

			ucY1 = *(a_pucSrcImage1 + ((ulOffset1)<<1));
			ucY2 = *(a_pucSrcImage1 + ((ulOffset1 + 1)<<1));
            ucY3 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width)<<1));
			ucY4 = *(a_pucSrcImage1 + ((ulOffset1 + a_pBInfo->ch_area[ucCameraIndex1].width + 1)<<1));                                      

            ucIntpoY1 = ( ucY1 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY1))+
                          ucY2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY1))+
                          ucY3 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY1))+
                          ucY4 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY1)))>>7;
            //global AE                  
            wTmp1 = (INT16)ucIntpoY1 + g_cOffset_Ymean_Firmware[ucCameraIndex1];//a_pBInfo->ch_area[ucCameraIndex1].ch_idx];
            ucIntpoY1 = FIND_BOUND(wTmp1); 

/*            // 解出第二組Pixel的Weight值
            ucWeight2 = LUT_v2_AND_WEIGHT - ucWeight1;

            ucDecX2 = ptPixelInfo->decX2;
            ucDecY2 = ptPixelInfo->decY2;
            ulOffset2 = ptPixelInfo->offset2;                    
            ucDecXY2 = ucDecX2+(ucDecY2<<3);                      

            ucY1_chan2 = *(a_pucSrcImage2 + ((ulOffset2)<<1));
            ucY2_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + 1)<<1));
            ucY3_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[1].width)<<1));
            ucY4_chan2 = *(a_pucSrcImage2 + ((ulOffset2 + a_pBInfo->ch_area[1].width + 1)<<1));                          

            ucIntpoY2 = ( ucY1_chan2 *(*(g_ulDecimalWeightBilinearYY1+ucDecXY2))+
                          ucY2_chan2 *(*(g_ulDecimalWeightBilinearYY2+ucDecXY2))+
                          ucY3_chan2 *(*(g_ulDecimalWeightBilinearYY3+ucDecXY2))+
                          ucY4_chan2 *(*(g_ulDecimalWeightBilinearYY4+ucDecXY2)))>>6;
            //global AE                  
            wTmp2 = (INT16)ucIntpoY2 + g_cOffset_Ymean_Firmware[a_pBInfo->ch_area[1].ch_idx];
            ucIntpoY2 = (wTmp2>255)?255:((wTmp2<0)?0:wTmp2); 

            ucWeight1 = (ucWeight1>16) ? (ucWeight1+1) : ucWeight1;
            ucWeight2 = (ucWeight2>16) ? (ucWeight2+1) : ucWeight2;
             
            // 將兩組Pixel的數值做weighting
            ucY = (ucWeight1 * ucIntpoY1 + ucWeight2 * ucIntpoY2)>>5;
*/
            // *(pucDstPtr + 2) = 0 + ((!ucBlack)*ucIntpoY1);
            *(pucDstPtr + 2) = 0 + ((ucBlack)&ucIntpoY1);

            ptPixelInfo++;

        }
    }
}

/************************************************************************************
 *  @func       TABLELU_process3DAVM_L2
 *
 *  @brief      Process 3DAVM by using L2 SRAM
 *
 *  @param[in]  None
 *
 *  @returns    None
 ***********************************************************************************/
void TABLELU_ProcessLut_L2(UINT8 ** a_pucSrcBuffer, AVM_LUT_PARA* a_pLutPara)//(UINT8 * a_pucSrcBuffer[], UINT16 a_uwImageWidth, UINT16 a_uwImageHeight, BV_LUTSet_t * a_pSet, UINT32 * a_pData, UINT8 * a_pucDestBuffer)
{           
    // Ping-pong buffer, accessed by CPU side
    UINT32 aCPU_base[2];
    UINT8  *pucCPU_dst;    // destination BV image block for CPU access
    UINT8  *pulCPU_lut;    // lut for CPU access
    UINT8  *pucCPU_src;    // source image block for CPU access       
    // Ping-pong buffer, accessed by DMA side
    UINT32 aDMA_base[2];
    UINT8  *pucDMA_dst;    // destination BV image block for DMA access;
    UINT8  *pulDMA_lut;    // lut for DMA access
    UINT8  *pucDMA_src;    // source image block for DMA access    
    UINT32 lDMA_src_size;    // total size (lut, src, dst) for DMA access

    UINT32 uSrc0_size_buf[2][4] = {0};
    UINT8  ucSrcSizeBufIdx = 0;
    UINT32 *upSrcOffset = NULL;
    alPartLUT_v2_3DBlockInfo_t *ptBInfo;        
    alPartLUT_v1_Area2_t *ptArea;
    alPartLUT_v1_ChannelArea2_t *ptChArea;    
    INT32 lBlkIndex;
    INT32 lPixelNum;
    INT32 lIndex; 
    
    // beware that aCPU_base[0] and aDMA_base[0] make up the ping-pong buffer, thus
    //             (1) aCPU_base[0] and aDMA_base[1] point to the same physical buffer in L2 SRAM
    //             (2) aCPU_base[1] and aDMA_base[0] point to the same physical buffer in L2 SRAM
    aCPU_base[0]= (UINT32) L2_addr_DSP;
    aCPU_base[1]= (UINT32) L2_addr_DSP + 98304; // (192/2)*1024;
    
    aDMA_base[0] = (UINT32) L2_addr_DMA + 98304; // (192/2)*1024;
    aDMA_base[1] = (UINT32) L2_addr_DMA;    
    
    ptBInfo = &(a_pLutPara->pSet->BInfo[0]);
    
//    uIndex = 0;
//    while(!ptBInfo->bEnableL2 && uIndex<a_pLutPara->uEndBlk)/*FIXME*/ 
//    {
//        uIndex++;
//        a_pLutPara->uStartBlk++;
//        ptBInfo = &(a_pLutPara->pSet->BInfo[uIndex]);
//    }
    // DMA 0-th buf            
    pucDMA_dst = (UINT8 *) aDMA_base[0];
    pulDMA_lut = (UINT8 *) (aDMA_base[0] + (ptBInfo->lut_num << 1));
    pucDMA_src = (UINT8 *) (aDMA_base[0] + (ptBInfo->lut_num << 1) + (ptBInfo->lut_num << 3));//*sizeof(UINT64) 8byte

#ifdef WIN32    
    DAT_copy((UINT8 *)a_pLutPara->pLut_data + ptBInfo->lut_offset, pulDMA_lut, ptBInfo->lut_num << 3);//*sizeof(UINT64) 8byte        
#else
    DAT_copy((UINT8 *)(a_pLutPara->pLut_data) + ptBInfo->lut_offset, pulDMA_lut, ptBInfo->lut_num << 3);//*sizeof(UINT64) 8byte    
#endif

  #ifndef WIN32                       
    //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
  #endif    
    //move first block source buffer to DMA
    lDMA_src_size = 0;
    for (lIndex=0; lIndex < REF_CHANNEL_NUM/*ptBInfo->ch_num*/; lIndex++) {
        ptChArea = &(ptBInfo->ch_area[lIndex]);
        if(0 == ptChArea->width)
            continue;  
#ifdef WIN32
        DAT_copy2d_(DAT_2D1D, 
#else
        DAT_copy2d(DAT_2D1D, 
#endif
                   a_pucSrcBuffer[ptChArea->ch_idx] +((ptChArea->start_row*a_pLutPara->uwImageWidth + ptChArea->start_col) << 1),
                   pucDMA_src + lDMA_src_size,
                   ptChArea->width << 1, ptChArea->height, a_pLutPara->uwImageWidth << 1);

        uSrc0_size_buf[ucSrcSizeBufIdx][ptChArea->ch_idx] = lDMA_src_size;
                   
        lDMA_src_size += (ptChArea->width * ptChArea->height << 1);
      #ifndef WIN32                       
        //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
      #endif
    } 
    upSrcOffset = uSrc0_size_buf[ucSrcSizeBufIdx];       
    //switch pingpong index
    ucSrcSizeBufIdx = !ucSrcSizeBufIdx;//(ucSrcSizeBufIdx==1)?0:1;
    // swap the ping-pong buffer
    BufferSwap(&aDMA_base[0], &aDMA_base[1]);
    BufferSwap(&aCPU_base[0], &aCPU_base[1]);
        
    DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish                                       
                
    for (lBlkIndex=a_pLutPara->uStartBlk; lBlkIndex < a_pLutPara->uEndBlk; lBlkIndex++) /*FIXME*/                
    {

        // DMA the generated dst image block from L2 to memory
        if (a_pLutPara->uStartBlk != lBlkIndex)
        {
            ptArea = &(a_pLutPara->pSet->BInfo[lBlkIndex-1].dst_area);

            pucDMA_dst = (UINT8 *) aDMA_base[0];
            
#ifdef WIN32
            DAT_copy2d_(DAT_1D2D, 
#else
            DAT_copy2d(DAT_1D2D, 
#endif
                pucDMA_dst,
                       a_pLutPara->pucDestBuffer + ((ptArea->start_row * a_pLutPara->uwImageWidth + ptArea->start_col) << 1),
                       ptArea->width << 1, ptArea->height, a_pLutPara->uwImageWidth << 1);
            
          #ifndef WIN32                       
            //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
          #endif
        }
        
        // DMA the next block of lut, src from memory to L2
        if (lBlkIndex != a_pLutPara->uEndBlk-1)
        {
//        
            ptBInfo = &(a_pLutPara->pSet->BInfo[lBlkIndex+1]); // next block

            pucDMA_dst = (UINT8 *) aDMA_base[0];              
            pulDMA_lut = (UINT8 *)(aDMA_base[0] + (ptBInfo->lut_num << 1));  // 2 bytes per pixel for YUV422I
            pucDMA_src = (UINT8 *) (aDMA_base[0] + (ptBInfo->lut_num << 1) + (ptBInfo->lut_num << 3));     //*sizeof(UINT64)       
#ifdef WIN32
            DAT_copy((UINT8 *)a_pLutPara->pLut_data + ptBInfo->lut_offset, pulDMA_lut, (ptBInfo->lut_num << 3));//*sizeof(UINT64)            
#else   
            DAT_copy((UINT8 *)(a_pLutPara->pLut_data) + ptBInfo->lut_offset, pulDMA_lut, (ptBInfo->lut_num << 3));//*sizeof(UINT64) 
#endif  
            
          #ifndef WIN32
            //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish                       
          #endif
  
            lDMA_src_size = 0;
            for (lIndex=0; lIndex < REF_CHANNEL_NUM/*ptBInfo->ch_num*/; lIndex++) {
                ptChArea = &(ptBInfo->ch_area[lIndex]);
                if(0 == ptChArea->width)
                    continue;  

#ifdef WIN32
                DAT_copy2d_(DAT_2D1D, 
#else
                DAT_copy2d(DAT_2D1D, 
#endif
                           a_pucSrcBuffer[ptChArea->ch_idx] + ((ptChArea->start_row*a_pLutPara->uwImageWidth + ptChArea->start_col) << 1),
                           pucDMA_src + lDMA_src_size,
                           ptChArea->width << 1, ptChArea->height, a_pLutPara->uwImageWidth << 1);

                uSrc0_size_buf[ucSrcSizeBufIdx][ptChArea->ch_idx] = lDMA_src_size;

                lDMA_src_size += (ptChArea->width * ptChArea->height << 1);
   
              #ifndef WIN32                       
                //DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish
              #endif
            } 
        } // END if (lBlkIndex != a_pSet->blk_num-1) {
        // CPU process the current buffer
        lPixelNum = a_pLutPara->pSet->BInfo[lBlkIndex].lut_num;
        
        pucCPU_dst = (UINT8 *) aCPU_base[0];
        pulCPU_lut = (UINT8 *) (aCPU_base[0] + (lPixelNum << 1));
        pucCPU_src = (UINT8 *) (aCPU_base[0] + (lPixelNum << 1) + (lPixelNum << 3));//*sizeof(UINT64)
        
//            if(!ptBInfo->bEnableL2)/*FIXME*/
//            {
//            // swap the ping-pong buffer
//            BufferSwap(&aDMA_base[0], &aDMA_base[1]);
//            BufferSwap(&aCPU_base[0], &aCPU_base[1]);
//            continue;     
//            }
//        if(a_pLutPara->pSet->BInfo[lBlkIndex].bBlackArea)/*FIXME*/
//        {
////            //fill black
////            ptArea = &(a_pLutPara->pSet->BInfo[lBlkIndex].dst_area);
////            DAT_copy2d(DAT_1D2D, pucBlackBuff,
////            pucCPU_dst,a_pLutPara->pucDestBuffer + ((ptArea->start_row * a_pLutPara->uwImageWidth + ptArea->start_col) << 1),
////            ptArea->width << 1, ptArea->height, a_pLutPara->uwImageWidth << 1);                
//            // swap the ping-pong buffer
//            BufferSwap(&aDMA_base[0], &aDMA_base[1]);
//            BufferSwap(&aCPU_base[0], &aCPU_base[1]);
//            continue;    
//        }              
//        if(a_pLutPara->pSet->BInfo[lBlkIndex].bEnableGAE)
//        {
//            // Do the table lookup for the current block area with interpolation and global AE
//            DoBlockLUT_InterpolationAndGlobalAE(pucCPU_src, pucCPU_dst, pulCPU_lut, (UINT32*) g_aulDecimalWeightBilinear, g_aulWeightBITshift, g_cOffset_Ymean_Firmware, a_pSet->BInfo[lBlkIndex].ch_area, lPixelNum);
//        }
//        else
//        {
//            // Do the table lookup for the current block area with interpolation only
//            DoBlockLUT_Interpolation(pucCPU_src, pucCPU_dst, pulCPU_lut, (UINT32*) g_aulDecimalWeightBilinear, g_aulWeightBITshift, a_pSet->BInfo[lBlkIndex].ch_area, lPixelNum);
//        }

        if(a_pLutPara->pSet->BInfo[lBlkIndex].ch_num > 1)
        {
            TABLELU_ProcessBlockLut(pulCPU_lut, pucCPU_src, upSrcOffset, pucCPU_dst, &(a_pLutPara->pSet->BInfo[lBlkIndex]));
        }
        else
        {
            TABLELU_ProcessBlockLut_SingleChannel(pulCPU_lut, pucCPU_src, pucCPU_dst, &(a_pLutPara->pSet->BInfo[lBlkIndex]));
        }
        //switch size information 
        upSrcOffset = uSrc0_size_buf[ucSrcSizeBufIdx];
        //switch pingpong index
        ucSrcSizeBufIdx = !ucSrcSizeBufIdx;//(ucSrcSizeBufIdx==1)?0:1;
        // swap the ping-pong buffer
        BufferSwap(&aDMA_base[0], &aDMA_base[1]);
        BufferSwap(&aCPU_base[0], &aCPU_base[1]);
                
        DAT_wait(DAT_XFRID_WAITALL);    // wait for DMA finish

    } // END for (lBlkIndex=0; lBlkIndex<a_pSet->blk_num; lBlkIndex++)
    
    // DMA the last  dst image block from L2 to memory
    ptArea = &(a_pLutPara->pSet->BInfo[lBlkIndex-1].dst_area);    
    pucDMA_dst = (UINT8 *)aDMA_base[0];
            
#ifdef WIN32
    DAT_copy2d_(DAT_1D2D, 
#else
    DAT_copy2d(DAT_1D2D, 
#endif
        pucDMA_dst,
               a_pLutPara->pucDestBuffer + ((ptArea->start_row * a_pLutPara->uwImageWidth + ptArea->start_col) << 1),
               ptArea->width << 1, ptArea->height, a_pLutPara->uwImageWidth << 1);
}

#define SRCBUF_SHIFT (360*480*2)
static UINT8 srcBuf0[SRCBUF_SHIFT*3];
static UINT8 *srcBuf1 = srcBuf0 + SRCBUF_SHIFT;
static UINT8 *srcBuf2 = srcBuf0 + SRCBUF_SHIFT*2;

void TABLELU_ProcessLut_L2NOPINGPONG(UINT8 ** a_pucSrcBuffer, AVM_LUT_PARA* a_pLutPara)//(UINT8 * a_pucSrcBuffer[], UINT16 a_uwImageWidth, UINT16 a_uwImageHeight, BV_LUTSet_t * a_pSet, UINT32 * a_pData, UINT8 * a_pucDestBuffer)
{           
    UINT8* g_pucSrcBuf[4] = {srcBuf0, srcBuf1, srcBuf2, NULL};

    UINT64 *pulLut = NULL;    // lut for CPU access
    alPartLUT_v2_3DBlockInfo_t *ptBInfo;        
    alPartLUT_v1_Area2_t *ptArea;
    alPartLUT_v1_ChannelArea2_t *ptChArea;    
    INT32 lBlkIndex = 0;
    UINT8* pucDstBuf = NULL;
    INT32 lIndex = 0;  
    UINT32 *pDst_temp[2] = {pucDstBuf1D, pucDstBuf1D+96*1024};
    UINT32 *pSrcBuf[2] = {NULL, NULL};    
    UINT32 *pSrc_temp = NULL, *pDstForDMA = NULL;
    UINT32 pingpong = 0;
  	int waitId = 0;
    int i = 0;
    UINT32 uSrcShift[4] = {SRCBUF_SHIFT, SRCBUF_SHIFT*2, SRCBUF_SHIFT*3, SRCBUF_SHIFT*4};
    
    for (lBlkIndex=a_pLutPara->uStartBlk; lBlkIndex < a_pLutPara->uEndBlk; lBlkIndex++) /*FIXME*/                
    {
        ptBInfo = &(a_pLutPara->pSet->BInfo[lBlkIndex]);//&(a_pSet->BInfo[0]);
        
//        if(ptBInfo->bEnableL2)/*FIXME*/
//        {
////            IoPrintf("%s %d disable L2 lBlkIndex=%d\n", __FUNCTION__, __LINE__, lBlkIndex);
//            continue;
//        }   
        pulLut = a_pLutPara->pLut_data + ptBInfo->lut_offset;
        //SOURCE
        for (lIndex=0; lIndex < ptBInfo->ch_num; lIndex++) {
            ptChArea = &(ptBInfo->ch_area[lIndex]);//source area
            pSrc_temp = a_pucSrcBuffer[ptChArea->ch_idx] + ((ptChArea->start_row*(a_pLutPara->uwImageWidth) + ptChArea->start_col) << 1);
            //copy source from 2D dimention to 1 dimention (2D1D)
//            DAT_copy2d(DAT_2D1D,
//                   pDstForDMA,
//                   pucDstBuf,//a_pLutPara->pucDestBuffer + ((ptArea->start_row * a_pLutPara->uwImageWidth + ptArea->start_col) << 1),
//                   ptArea->width << 1, ptArea->height, a_pLutPara->uwImageWidth << 1);
//            
            for (i=0; i<ptChArea->height; i++)
                memcpy((Uint8 *)g_pucSrcBuf[lIndex] + i*(ptChArea->width << 1), (Uint8 *)pSrc_temp + i*((a_pLutPara->uwImageWidth) << 1), (ptChArea->width) << 1);        
            } 
        //DESTINATION      
        ptArea = &(a_pLutPara->pSet->BInfo[lBlkIndex].dst_area);  
        
        pucDstBuf = a_pLutPara->pucDestBuffer + ((ptArea->start_row * a_pLutPara->uwImageWidth + ptArea->start_col) << 1);
//        IoPrintf("%s %d pucDstBuf=%x x=%d y=%d w=%d\n", __FUNCTION__, __LINE__, pucDstBuf, ptArea->start_row, ptArea->start_col, a_pLutPara->uwImageWidth);

        TABLELU_ProcessBlockLut(pulLut, srcBuf0, uSrcShift, pDst_temp[pingpong], &(a_pLutPara->pSet->BInfo[lBlkIndex]));
        
        pDstForDMA = pDst_temp[pingpong];
        //switch pingpong
        pingpong++;
        pingpong = pingpong % 2;
//          pingpong = (pingpong > 1)?0:1;
//        waitId = DAT_copy2d(DAT_1D2D,
//                   pDstForDMA,
//                   pucDstBuf,//a_pLutPara->pucDestBuffer + ((ptArea->start_row * a_pLutPara->uwImageWidth + ptArea->start_col) << 1),
//                   ptArea->width << 1, ptArea->height, a_pLutPara->uwImageWidth << 1);
        i=0;
        for (i=0; i<ptArea->height; i++)
            memcpy((Uint8 *)pucDstBuf + i*(a_pLutPara->uwImageWidth << 1), (Uint8 *)pDstForDMA + i*((ptArea->width) << 1), (ptArea->width) << 1);        

//        DAT_wait(waitId);    // wait for DMA finish                                       
//        if(g_pucSrcBuf[0]!=NULL)
//            free(g_pucSrcBuf[0]);
//        if(g_pucSrcBuf[1]!=NULL)
//            free(g_pucSrcBuf[1]);                     
    } // END for (lBlkIndex=0; lBlkIndex<a_pSet->blk_num; lBlkIndex++)
 
}

void TABLELU_showBlockInfo(alPartLUT_v2_Def * a_pSet)
{
    INT32 i =0, j=0, k=0;
    UINT32 temp =0;
    UINT32 size =0, totalSize=0;
    
    for (i=0; i < a_pSet->blk_num; i++) /*FIXME*/
    {    
        DEBUG_Printf("Blk_Num=%03d: Dst X=%d Y=%d W=%d H=%d Lut_offset=%d\n", 
        i, a_pSet->BInfo[i].dst_area.start_col, a_pSet->BInfo[i].dst_area.start_row, 
        a_pSet->BInfo[i].dst_area.width, a_pSet->BInfo[i].dst_area.height, a_pSet->BInfo[i].lut_offset);//0:BV, 1:Front 
 
        for(k=0; k<a_pSet->BInfo[i].ch_num; k++)
        {
            DEBUG_Printf("             Sur[%d=>%d]: X=%d Y=%d W=%d H=%d\n", 
            k, a_pSet->BInfo[i].ch_area[k].ch_idx, 
            a_pSet->BInfo[i].ch_area[k].start_col, a_pSet->BInfo[i].ch_area[k].start_row, 
            a_pSet->BInfo[i].ch_area[k].width, a_pSet->BInfo[i].ch_area[k].height);//0:BV, 1:Front 
        }
    }
    
    DEBUG_Printf("\nBlock size:\n"); 
 
    //calculate block size and display it on CLI
    for (i=0; i < a_pSet->blk_num; i++) /*FIXME*/
    {
        size = 0;
        //calculate Lut_data size
        size += (a_pSet->BInfo[i].dst_area.width * a_pSet->BInfo[i].dst_area.height) << 3;
        //calculate Destination buffer size
        size += (a_pSet->BInfo[i].dst_area.width * a_pSet->BInfo[i].dst_area.height) << 1;    
        //calculate Source buffer size
        for(j=0; j<a_pSet->BInfo[i].ch_num;j++)
            size += (a_pSet->BInfo[i].ch_area[j].width * a_pSet->BInfo[i].ch_area[j].height) << 1;    
           
        DEBUG_Printf("Blk_Num=%03d: Blk_size=%d\n", i, size); 
        totalSize = totalSize+size;
    }    
 
    DEBUG_Printf("Blk_total_Num=%d: Blk_average_size=%d\n", a_pSet->blk_num, totalSize/a_pSet->blk_num ); 
  
}

/************************************************************************************
 *  @func       alPartLUT_v2_BlockClassify
 *
 *  @brief      To calculate blocks number that enable L2 SRAM
 *
 *  @param[in]  None
 *
 *  @returns    None
 ***********************************************************************************/
void alPartLUT_v2_BlockClassify(alPartLUT_v2_Def * a_pSet, UINT32 lutIdx)
{
    /*
    lutIdx == 0: TopLut
    lutIdx == 1: RearLut
    */
    INT32 i =0;
    UINT32 temp =0;
    for (i=0; i < a_pSet->blk_num; i++) /*FIXME*/
    {
        temp= (a_pSet->BInfo[i].bEnableL2)?1:0;
        g_uEnL2Num[lutIdx] += temp;
        if(!a_pSet->BInfo[i].bEnableL2)
        DEBUG_Printf("lutIdx=%d DisableL2 idx=%d\n", lutIdx, i);//0:BV, 1:Front 
    }
    
    DEBUG_Printf("\n"); 

    /*print black block info*/
    for (i=0; i < a_pSet->blk_num; i++)
    {
        if(a_pSet->BInfo[i].bBlackArea)
            DEBUG_Printf("lutIdx=%d isBlackArea idx=%d\n", lutIdx, i);//0:BV, 1:Front 
    }
    DEBUG_Printf("\n%s %d g_uEnL2Num[%d]=%d blk_num=%d\n", __FUNCTION__, __LINE__, lutIdx, g_uEnL2Num[lutIdx], a_pSet->blk_num);//hsin test
//    if(0 == lutIdx)//show 3D BV info only
//    TABLELU_showBlockInfo(a_pSet);
    
//    memset(&AvmLutPara, 0x00, sizeof(AVM_LUT_PARA));
//    memset(&pucBlackBuff, 0x00, 192*1024);
    
}
/************************************************************************************
 *  @func       alPartLUT_v2_Process3DAVM
 *
 *  @brief      Process 3DAVM 
 *
 *  @param[in]  None
 *
 *  @returns    None
 ***********************************************************************************/
void alPartLUT_v2_Process3DAVM(UINT8 ** a_pucSrcBuffer, UINT16 a_uwImageWidth, UINT16 a_uwImageHeight, alPartLUT_v2_Def * a_pSet, UINT8 * a_pData, UINT8 * a_pucDestBuffer, UINT32 a_uLutIdx)
{
//    IoPrintf("%s a_uLutIdx=%d a_pSet=0x%x a_pData=0x%x\n", __FUNCTION__, a_uLutIdx, a_pSet, a_pData);//0:BV, 1:Front 
   
    AvmLutPara.uwImageWidth = a_uwImageWidth;
    AvmLutPara.uwImageHeight = a_uwImageHeight;
    AvmLutPara.pLut_data = a_pData;
//    a_pSet->lut_data = a_pData;//it can't update a_pSet->lut_data here, it will cause CRC error when calibration. 
    AvmLutPara.pSet = a_pSet;
    AvmLutPara.pucDestBuffer = a_pucDestBuffer;
    AvmLutPara.uStartBlk = 0;    
//    AvmLutPara.uEndBlk = g_uEnL2Num[a_uLutIdx];
//    TABLELU_ProcessLut_L2(a_pucSrcBuffer, &AvmLutPara); 
//    AvmLutPara.uStartBlk = g_uEnL2Num[a_uLutIdx];    
    AvmLutPara.uEndBlk = a_pSet->blk_num; 
    /*speed up process blocks using L2 SRAM*/    
    TABLELU_ProcessLut_L2(a_pucSrcBuffer, &AvmLutPara); 
    /*process blocks that doesn't use L2 SRAM*/     
//    TABLELU_ProcessLut_L2NOPINGPONG(a_pucSrcBuffer, &AvmLutPara);
      
}
#endif
//#endif

#endif

