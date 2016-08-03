#pragma once
#include "mtype.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
*  \addtogroup TrailLine
*  @{
*/

//#pragma pack(1) // 使用 BYTE 的記憶體對齊

typedef enum 
{

    EAGLEGP_STL_LEFT     = 0,   // 0 for Static Left View
    EAGLEGP_STL_RIGHT    = 1,   // 1 for Static Right View
    EAGLEGP_STL_FRONT    = 2,   // 2 for Static Front View
    EAGLEGP_STL_BACK     = 3,   // 3 for Static Back View
    EAGLEGP_DTL_FRONT    = 4,   // 4 for Dynamic Front View
	EAGLEGP_DTL_BACK     = 5,   // 5 for Dynamic Back View

} EAGLEGP_TL_INDX;

typedef struct{
	UINT8 ucY;
	UINT8 ucCb;
	UINT8 ucCr;
	UINT16 uwStartx;
	UINT16 uwEndx;
	UINT16 uwYaxis;
	UINT16 uwLength;
	INT16 wPreLine_Difx;
	INT16 wPreLine_Dify;
	INT16 wQuotient;		//Quotient
	INT16 wRemainder;		//Remainder
	UINT8 ucCPC;			//Current Packet Count
	BOOL bSOP;				//Start Of Packet
	UINT16 uwOBI;			//OBbject Index
} EAGLEGP_PieceLineInfo;

//#pragma pack()  // 使用預設的記憶體對齊

void EAGLEGP_GenTrailLineBat(UINT8* pucData_FSTL, UINT8* pucData_BSTL, UINT8* pucData_LSTL, UINT8* pucData_RSTL,
							 UINT8* pucData_FDTL[], UINT8* pucData_BDTL[], INT32 lHeight, INT32 lWidth, INT32 lChannel, INT32 lDegree, INT32 lInterval);

void EAGLEGP_GenStaticTrailInfo(EAGLEGP_TL_INDX ucType, UINT8* pucData, INT32 lHeight, INT32 lWidth, INT32 lChannel,
								EAGLEGP_PieceLineInfo* poLine, UINT32* ulTotalLine, UINT16* uwTotalObject, UINT16* uwBuffer, UINT8* ucSOPC, UINT32* ulPacketTotal);

void EAGLEGP_GenDynamicTrailInfo(EAGLEGP_TL_INDX ucType, UINT8* pucData[], INT32 lHeight, INT32 lWidth, INT32 lChannel, INT32 lDegree, INT32 lInterval,
								 EAGLEGP_PieceLineInfo* poLine[], UINT32* ulTotalLine_DTL, UINT16* uwTotalObject_DTL, UINT16* uwBuffer_DTL[], UINT8* ucSOPC_DTL[], UINT32* ulPacketTotal_DTL);

void EAGLEGP_WriteBatFile(EAGLEGP_TL_INDX ucType, EAGLEGP_PieceLineInfo* poLine, UINT32 ulTotalLine, UINT16 uwTotalObject, UINT16* uwBuffer, UINT8* ucSOPC, UINT32 ulPacketTotal);

void EAGLEGP_WriteDyBatFile(EAGLEGP_TL_INDX ucType, INT32 lDegree, INT32 lInterval, EAGLEGP_PieceLineInfo* poLine[], UINT32* ulTotalLine_DTL, UINT16* uwTotalObject_DTL, UINT16* uwBuffer_DTL[], UINT8* ucSOPC_DTL[], UINT32* ulPacketTotal_DTL);

void EAGLEI_WriteDyBatFile(EAGLEGP_TL_INDX ucType, INT32 lDegree, INT32 lInterval, EAGLEGP_PieceLineInfo* poLine[], UINT32* ulTotalLine_DTL, UINT16* uwTotalObject_DTL, UINT16* uwBuffer_DTL[], UINT8* ucSOPC_DTL[], UINT32* ulPacketTotal_DTL);

/**
*  @}
*/

#ifdef __cplusplus
}
#endif
