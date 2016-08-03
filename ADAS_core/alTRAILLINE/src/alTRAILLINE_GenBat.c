
#ifdef WIN32 // Only do "Gen Trail Line Bat" in PC mode

#include "alTRAILLINE_GenBat.h"
#include <stdio.h>
#include <stdlib.h>

void EAGLEGP_GenTrailLineBat(UINT8* pucData_FSTL, UINT8* pucData_BSTL, UINT8* pucData_LSTL, UINT8* pucData_RSTL,
							 UINT8* pucData_FDTL[], UINT8* pucData_BDTL[], INT32 lHeight, INT32 lWidth, INT32 lChannel, INT32 lDegree, INT32 lInterval)
{
	//static variable declare
	UINT32 i = 0;
	UINT8 ucSOPC[500];
	UINT16 uwBuffer[500];
	UINT16 uwTotalObject = 0;
	UINT32 ulTotalLine = 0;
	UINT32 ulPacketTotal = 0;
	EAGLEGP_PieceLineInfo *pulFrontSTL, *pulRearSTL, *pulLeftSTL, *pulRightSTL;

	//dynamic variable declare
	UINT8 *ucSOPC_DTL[61];
	UINT16 *uwBuffer_DTL[61];
	UINT16 uwTotalObject_DTL[61] = {0};
	UINT32 ulTotalLine_DTL[61] = {0};
	UINT32 ulPacketTotal_DTL[61] = {0};
	EAGLEGP_PieceLineInfo *pulFrontDTL[61], *pulRearDTL[61];

	pulFrontSTL = (EAGLEGP_PieceLineInfo*) calloc(1000,sizeof(EAGLEGP_PieceLineInfo));
	pulRearSTL  = (EAGLEGP_PieceLineInfo*) calloc(1000,sizeof(EAGLEGP_PieceLineInfo));
	pulLeftSTL  = (EAGLEGP_PieceLineInfo*) calloc(1000,sizeof(EAGLEGP_PieceLineInfo));
	pulRightSTL = (EAGLEGP_PieceLineInfo*) calloc(1000,sizeof(EAGLEGP_PieceLineInfo));
	for(i=0;i<61;i++)
	{
		ucSOPC_DTL[i] = (UINT8*) calloc(500,sizeof(UINT8));
		uwBuffer_DTL[i] = (UINT16*) calloc(500,sizeof(UINT16));
		pulFrontDTL[i] = (EAGLEGP_PieceLineInfo*) calloc(5000,sizeof(EAGLEGP_PieceLineInfo));
		pulRearDTL[i]  = (EAGLEGP_PieceLineInfo*) calloc(5000,sizeof(EAGLEGP_PieceLineInfo));
	}

    /* static trail line - front */
    EAGLEGP_GenStaticTrailInfo(EAGLEGP_STL_FRONT, pucData_FSTL, lHeight, lWidth, lChannel, 
		pulFrontSTL, &ulTotalLine, &uwTotalObject, uwBuffer, ucSOPC, &ulPacketTotal);
	EAGLEGP_WriteBatFile(EAGLEGP_STL_FRONT, pulFrontSTL, ulTotalLine, uwTotalObject, uwBuffer, ucSOPC, ulPacketTotal);

    /* static trail line - rear */
    EAGLEGP_GenStaticTrailInfo(EAGLEGP_STL_BACK, pucData_BSTL, lHeight, lWidth, lChannel,
		pulRearSTL, &ulTotalLine, &uwTotalObject, uwBuffer, ucSOPC, &ulPacketTotal);
	EAGLEGP_WriteBatFile(EAGLEGP_STL_BACK, pulRearSTL, ulTotalLine, uwTotalObject, uwBuffer, ucSOPC, ulPacketTotal);

    /* static trail line - left */
    EAGLEGP_GenStaticTrailInfo(EAGLEGP_STL_LEFT, pucData_LSTL, lWidth, lHeight, lChannel,
		pulLeftSTL, &ulTotalLine, &uwTotalObject, uwBuffer, ucSOPC, &ulPacketTotal);
	EAGLEGP_WriteBatFile(EAGLEGP_STL_LEFT, pulLeftSTL, ulTotalLine, uwTotalObject, uwBuffer, ucSOPC, ulPacketTotal);

    /* static trail line - right */
    EAGLEGP_GenStaticTrailInfo(EAGLEGP_STL_RIGHT, pucData_RSTL, lWidth, lHeight, lChannel,
		pulRightSTL, &ulTotalLine, &uwTotalObject, uwBuffer, ucSOPC, &ulPacketTotal);
	EAGLEGP_WriteBatFile(EAGLEGP_STL_RIGHT, pulRightSTL, ulTotalLine, uwTotalObject, uwBuffer, ucSOPC, ulPacketTotal);

    /* dynamic trail line - front */
    EAGLEGP_GenDynamicTrailInfo(EAGLEGP_DTL_FRONT, pucData_FDTL, lHeight, lWidth, lChannel, lDegree, lInterval,
		pulFrontDTL, ulTotalLine_DTL, uwTotalObject_DTL, uwBuffer_DTL, ucSOPC_DTL, ulPacketTotal_DTL);
	EAGLEGP_WriteDyBatFile(EAGLEGP_DTL_FRONT, lDegree, lInterval, pulFrontDTL, ulTotalLine_DTL, uwTotalObject_DTL, uwBuffer_DTL, ucSOPC_DTL, ulPacketTotal_DTL);

    /* dynamic trail line - rear */
    EAGLEGP_GenDynamicTrailInfo(EAGLEGP_DTL_BACK, pucData_BDTL, lHeight, lWidth, lChannel, lDegree, lInterval,
		pulRearDTL, ulTotalLine_DTL, uwTotalObject_DTL, uwBuffer_DTL, ucSOPC_DTL, ulPacketTotal_DTL);
	EAGLEGP_WriteDyBatFile(EAGLEGP_DTL_BACK, lDegree, lInterval, pulRearDTL, ulTotalLine_DTL, uwTotalObject_DTL, uwBuffer_DTL, ucSOPC_DTL, ulPacketTotal_DTL);
	//EAGLEGP_WriteDyBatFile_MVEV(EAGLEGP_DTL_BACK, lDegree, lInterval, pulRearDTL, ulTotalLine_DTL, uwTotalObject_DTL, uwBuffer_DTL, ucSOPC_DTL, ulPacketTotal_DTL);
	
	free(pulFrontSTL);
	free(pulRearSTL);
	free(pulLeftSTL);
	free(pulRightSTL);
}

void EAGLEGP_GenStaticTrailInfo(EAGLEGP_TL_INDX ucType, UINT8* pucData, INT32 lHeight, INT32 lWidth, INT32 lChannel,
								EAGLEGP_PieceLineInfo* poLine, UINT32* ulTotalLine, UINT16* uwTotalObject, UINT16* uwBuffer, UINT8* ucSOPC, UINT32* ulPacketTotal)
{
	INT32 lX=0, lY=0, lZ=0, lObject=0;
	INT32 lLine_idx = 0, lCompare_idx = 0, lBefLine_idx = 0, lBefObj_idx = 0;
	UINT32 ulIndex = 0;
	UINT32 ulCount = 0;
	BOOL bFirst = FALSE;
	BOOL bSaveBuf = FALSE;	//判別buffer內是否有element

	//initialize
	*ulTotalLine = 0;
	*uwTotalObject = 0;
	*ulPacketTotal = 0;
	memset(ucSOPC, 0, 500*sizeof(UINT8));
	memset(uwBuffer, 0, 500*sizeof(UINT16));

	for(lY = 0; lY<lHeight; lY++, bFirst = FALSE)
	{
		for(lX = 0; lX<lWidth; lX++)
		{
			//起始行&不等於底色
			if(bFirst == FALSE && (pucData[lX*lChannel+lY*lWidth*lChannel] != 0xFF || pucData[lX*lChannel+lY*lWidth*lChannel+1] != 0x80 || pucData[lX*lChannel+lY*lWidth*lChannel+2] != 0x80) )
			{
				(poLine+ulIndex)->ucY = pucData[lX*lChannel+lY*lWidth*lChannel];
				(poLine+ulIndex)->ucCr = pucData[lX*lChannel+lY*lWidth*lChannel+1];
				(poLine+ulIndex)->ucCb = pucData[lX*lChannel+lY*lWidth*lChannel+2];
				(poLine+ulIndex)->uwStartx = lX;
				(poLine+ulIndex)->uwEndx = lX;
				(poLine+ulIndex)->uwYaxis = lY;
				(poLine+ulIndex)->uwOBI = ulIndex;
				((poLine+ulIndex)->uwLength)++;
				bFirst = TRUE;
				*ulTotalLine = ulIndex;
				if(lX == lWidth-1)
					ulIndex++;
			}
			//起始行延伸&(延伸色=前一行延伸色)
			else if(bFirst == TRUE && pucData[lX*lChannel+lY*lWidth*lChannel] == pucData[(lX-1)*lChannel+lY*lWidth*lChannel]
								  && pucData[lX*lChannel+lY*lWidth*lChannel+1] == pucData[(lX-1)*lChannel+lY*lWidth*lChannel+1]
								  && pucData[lX*lChannel+lY*lWidth*lChannel+2] == pucData[(lX-1)*lChannel+lY*lWidth*lChannel+2])
			{
				(poLine+ulIndex)->uwEndx = lX;
				(poLine+ulIndex)->uwLength = ((poLine+ulIndex)->uwEndx - (poLine+ulIndex)->uwStartx) + 1;
				//延伸色大於127length
				if((poLine+ulIndex)->uwLength > 0x7F)
				{
					((poLine+ulIndex)->uwEndx)--;
					((poLine+ulIndex)->uwLength)--;
					ulIndex++;
					(poLine+ulIndex)->ucY = pucData[lX*lChannel+lY*lWidth*lChannel];
					(poLine+ulIndex)->ucCr = pucData[lX*lChannel+lY*lWidth*lChannel+1];
					(poLine+ulIndex)->ucCb = pucData[lX*lChannel+lY*lWidth*lChannel+2];
					(poLine+ulIndex)->uwStartx = lX;
					(poLine+ulIndex)->uwEndx = lX;
					(poLine+ulIndex)->uwYaxis = lY;
					(poLine+ulIndex)->uwOBI = ulIndex;
					((poLine+ulIndex)->uwLength)++;
					bFirst = TRUE;
					*ulTotalLine = ulIndex;
					if(lX == lWidth-1)
					{
						ulIndex++;
						continue;
					}
				}
				if(lX == lWidth-1)
					ulIndex++;
			}
		    //起始行延伸&&(延伸色!=前一行延伸色)
			else if(bFirst == TRUE && (pucData[lX*lChannel+lY*lWidth*lChannel] != pucData[(lX-1)*lChannel+lY*lWidth*lChannel]
								  || pucData[lX*lChannel+lY*lWidth*lChannel+1] != pucData[(lX-1)*lChannel+lY*lWidth*lChannel+1]
								  || pucData[lX*lChannel+lY*lWidth*lChannel+2] != pucData[(lX-1)*lChannel+lY*lWidth*lChannel+2]))
			{
				ulIndex++;
				//延伸色為另一色
				if(pucData[lX*lChannel+lY*lWidth*lChannel] != 0xFF
				|| pucData[lX*lChannel+lY*lWidth*lChannel+1] != 0x80
				|| pucData[lX*lChannel+lY*lWidth*lChannel+2] != 0x80)
				{
					(poLine+ulIndex)->ucY = pucData[lX*lChannel+lY*lWidth*lChannel];
					(poLine+ulIndex)->ucCr = pucData[lX*lChannel+lY*lWidth*lChannel+1];
					(poLine+ulIndex)->ucCb = pucData[lX*lChannel+lY*lWidth*lChannel+2];
					(poLine+ulIndex)->uwStartx = lX;
					(poLine+ulIndex)->uwEndx = lX;
					(poLine+ulIndex)->uwYaxis = lY;
					(poLine+ulIndex)->uwOBI = ulIndex;
					((poLine+ulIndex)->uwLength)++;
					bFirst = TRUE;
					*ulTotalLine = ulIndex;
					if(lX == lWidth-1)
						ulIndex++;
				}
				//延伸色為底色
				else
					bFirst = FALSE;
				*ulTotalLine = ulIndex;
			}
		}
	}
	/*{
		int i;
		FILE* step1;
		step1 = fopen("step1.txt","w");
		for(i=0; i<(INT32)(*ulTotalLine); i++)
		{
			fprintf(step1,"(%3d,%3d,%3d) (%3d~%3d,%3d) %3d %3d\n",(poLine+i)->ucY, (poLine+i)->ucCb, (poLine+i)->ucCr, (poLine+i)->uwStartx, (poLine+i)->uwEndx, (poLine+i)->uwYaxis, (poLine+i)->uwLength, (poLine+i)->uwOBI);
		}
		fclose(step1);
	}*/
	//物件切割-由上至下
	for(lLine_idx = 0; lLine_idx<(INT32)(*ulTotalLine); lLine_idx++){//scan total line
		for(lCompare_idx=0; lCompare_idx<lLine_idx; lCompare_idx++){//scan before line
			if((poLine+lLine_idx)->uwYaxis - (poLine+lCompare_idx)->uwYaxis ==1)	//上下相鄰
			{
				if(((poLine+lLine_idx)->uwStartx < (poLine+lCompare_idx)->uwStartx && (poLine+lLine_idx)->uwEndx < (poLine+lCompare_idx)->uwStartx)
				  ||((poLine+lLine_idx)->uwStartx > (poLine+lCompare_idx)->uwEndx && (poLine+lLine_idx)->uwEndx > (poLine+lCompare_idx)->uwEndx))
					continue;
				else
				{
					if((poLine+lLine_idx)->ucY == (poLine+lCompare_idx)->ucY
						&&(poLine+lLine_idx)->ucCb == (poLine+lCompare_idx)->ucCb
						&&(poLine+lLine_idx)->ucCr == (poLine+lCompare_idx)->ucCr)
					{
						if((poLine+lLine_idx)->uwOBI>(poLine+lCompare_idx)->uwOBI)
							(poLine+lLine_idx)->uwOBI = (poLine+lCompare_idx)->uwOBI;
						else
							(poLine+lCompare_idx)->uwOBI = (poLine+lLine_idx)->uwOBI;
					}
				}
			}
			else
				continue;
		}
	}

	//物件切割-由下至上
	for(lLine_idx = (*ulTotalLine); lLine_idx>=0; lLine_idx--){//scan total line
		for(lCompare_idx=0; lCompare_idx<lLine_idx; lCompare_idx++){//scan before line
			if((poLine+lLine_idx)->uwYaxis - (poLine+lCompare_idx)->uwYaxis ==1)	//上下相鄰
			{
				if(((poLine+lLine_idx)->uwStartx < (poLine+lCompare_idx)->uwStartx && (poLine+lLine_idx)->uwEndx < (poLine+lCompare_idx)->uwStartx)
				  ||((poLine+lLine_idx)->uwStartx > (poLine+lCompare_idx)->uwEndx && (poLine+lLine_idx)->uwEndx > (poLine+lCompare_idx)->uwEndx))
					continue;
				else
				{ 
					if((poLine+lLine_idx)->ucY == (poLine+lCompare_idx)->ucY
						&&(poLine+lLine_idx)->ucCb == (poLine+lCompare_idx)->ucCb
						&&(poLine+lLine_idx)->ucCr == (poLine+lCompare_idx)->ucCr)
					{
						if((poLine+lLine_idx)->uwOBI>(poLine+lCompare_idx)->uwOBI)
							(poLine+lLine_idx)->uwOBI = (poLine+lCompare_idx)->uwOBI;
						else
							(poLine+lCompare_idx)->uwOBI = (poLine+lLine_idx)->uwOBI;
					}
				}
			}
			else
				continue;
		}
	}
	/*{
		int i;
		FILE* step2;
		step2 = fopen("step2.txt","w");
		for(i=0; i<(INT32)(*ulTotalLine); i++)
		{
			fprintf(step2,"(%3d,%3d,%3d) (%3d~%3d,%3d) %3d %3d\n",(poLine+i)->ucY, (poLine+i)->ucCb, (poLine+i)->ucCr, (poLine+i)->uwStartx, (poLine+i)->uwEndx, (poLine+i)->uwYaxis, (poLine+i)->uwLength, (poLine+i)->uwOBI);
		}
		fclose(step2);
	}*/

	//物件個數
	for(lLine_idx = 0; lLine_idx<(INT32)(*ulTotalLine); lLine_idx++, bSaveBuf = FALSE)
	{
		if(lLine_idx == 0)	//起始line
		{
			*(uwBuffer+(*uwTotalObject)) = (poLine+lLine_idx)->uwOBI;	//存入buffer
			(*uwTotalObject)++;
		}
		else
		{
			for(lZ=0; lZ<(*uwTotalObject); lZ++)	//與buffer內的element元素互相比較，若發現buffer內有此object，則savebuf=TRUE
			{
				if((poLine+lLine_idx)->uwOBI == *(uwBuffer+lZ))
					bSaveBuf = TRUE;
			}
			if(bSaveBuf == FALSE)	//buffer中未具有此object，存入buffer
			{
				*(uwBuffer+(*uwTotalObject)) = (poLine+lLine_idx)->uwOBI;
				(*uwTotalObject)++;
			}
		}
	}
	
	for(lObject=0, ulCount=0, ulIndex=0; lObject<(*uwTotalObject); lObject++, ulCount=0, ulIndex++)	//scan object
	{
		for(lLine_idx = 0; lLine_idx<(INT32)(*ulTotalLine); lLine_idx++)	//scan line
		{
			if(*(uwBuffer+lObject) == (poLine+lLine_idx)->uwOBI)	//scan line的object index == *(buffer+object)
			{
				if(lLine_idx == *(uwBuffer+lObject))	
				{
					(poLine+*(uwBuffer+lObject))->wPreLine_Difx = 0;
					(poLine+*(uwBuffer+lObject))->wPreLine_Dify = 0;
					(poLine+*(uwBuffer+lObject))->wQuotient = 0;
					(poLine+*(uwBuffer+lObject))->wRemainder = 0;
					(poLine+*(uwBuffer+lObject))->bSOP = TRUE;
					ulCount += 11;
					(poLine+*(uwBuffer+lObject))->ucCPC = ulCount;
					lBefLine_idx = lLine_idx;
					lBefObj_idx = lObject;
				}
				else if(lBefObj_idx != lObject)
				{			
					(poLine+lLine_idx)->wPreLine_Difx = 0;
					(poLine+lLine_idx)->wPreLine_Dify = 0;
					(poLine+lLine_idx)->wQuotient = 0;
					(poLine+lLine_idx)->wRemainder = 0;
					(poLine+lLine_idx)->bSOP = TRUE;
					ulCount += 11;
					(poLine+lLine_idx)->ucCPC = ulCount;
					lBefLine_idx = lLine_idx;
					lBefObj_idx = lObject;
				}
				else
				{
					(poLine+lLine_idx)->wPreLine_Difx = (poLine+lLine_idx)->uwStartx - (poLine+lBefLine_idx)->uwStartx;
					(poLine+lLine_idx)->wPreLine_Dify = (poLine+lLine_idx)->uwYaxis - (poLine+lBefLine_idx)->uwYaxis;
					(poLine+lLine_idx)->wQuotient = ((poLine+lLine_idx)->wPreLine_Difx)/0x7F;
					(poLine+lLine_idx)->wRemainder = ((poLine+lLine_idx)->wPreLine_Difx)%0x7F;
					if((poLine+lLine_idx)->wQuotient == 0)
						ulCount += 3;
					else
					{
						if((poLine+lLine_idx)->wRemainder == 0)
							ulCount += (abs((poLine+lLine_idx)->wQuotient))*3;
						else
							ulCount += ((abs((poLine+lLine_idx)->wQuotient))+1)*3;
					}
					(poLine+lLine_idx)->ucCPC = ulCount;

					if(ulCount>240)	//封包數量>240bytes時
					{
						*(ucSOPC+ulIndex) = (poLine+lBefLine_idx)->ucCPC;
						ulIndex++;
						*(ulPacketTotal) += ulCount;	//total sum
						*(ulPacketTotal) -= (ulCount - (poLine+lBefLine_idx)->ucCPC);	//扣掉超出封包量
						//start of packet initialize
						(poLine+lLine_idx)->wPreLine_Difx = 0;
						(poLine+lLine_idx)->wPreLine_Dify = 0;
						(poLine+lLine_idx)->wQuotient = 0;
						(poLine+lLine_idx)->wRemainder = 0;
						(poLine+lLine_idx)->ucCPC = 11;
						ulCount = 11;
						(poLine+lLine_idx)->bSOP = TRUE;
					}
					lBefLine_idx = lLine_idx;
					lBefObj_idx = lObject;
				}
			}
		}
		*(ulPacketTotal) += ulCount;
		*(ucSOPC+ulIndex) = ulCount;
	}
	/*{
		int i,j;
		FILE* step3;
		step3 = fopen("step3.txt","w");
		for(j=0; j<(*uwTotalObject); j++)
		{
			for(i=0; i<(INT32)(*ulTotalLine); i++)
			{
				if(*(uwBuffer+j) == (poLine+i)->uwOBI)
					fprintf(step3,"(%3d,%3d,%3d) (%3d~%3d,%3d) %3d %3d %3d %3d\n",(poLine+i)->ucY, (poLine+i)->ucCb, (poLine+i)->ucCr, (poLine+i)->uwStartx, (poLine+i)->uwEndx, (poLine+i)->uwYaxis, (poLine+i)->uwLength, (poLine+i)->uwOBI, (poLine+i)->bSOP, (poLine+i)->ucCPC);
				else
					continue;
			}
			fprintf(step3,"\n");
		}
		fclose(step3);
	}*/
}

void EAGLEGP_GenDynamicTrailInfo(EAGLEGP_TL_INDX ucType, UINT8* pucData[], INT32 lHeight, INT32 lWidth, INT32 lChannel, INT32 lDegree, INT32 lInterval,
								 EAGLEGP_PieceLineInfo* poLine[], UINT32* ulTotalLine_DTL, UINT16* uwTotalObject_DTL, UINT16* uwBuffer_DTL[], UINT8* ucSOPC_DTL[], UINT32* ulPacketTotal_DTL)
{
	INT32 lTrailDegree;
	INT32 lX=0, lY=0, lZ=0, lObject=0;
	INT32 lLine_idx = 0, lCompare_idx = 0, lBefLine_idx = 0, lBefObj_idx = 0, lDegree_idx=0;
	UINT32 ulIndex = 0;
	UINT32 ulCount = 0;
	BOOL bFirst = FALSE;
	BOOL bSaveBuf = FALSE;	//判別buffer內是否有element

	//initialize
	memset(uwTotalObject_DTL,0,61*sizeof(UINT16));
	memset(ulTotalLine_DTL,0,61*sizeof(UINT32));
	memset(ulPacketTotal_DTL,0,61*sizeof(UINT32));
	for(lZ=0; lZ<61; lZ++)
	{
		memset((*(uwBuffer_DTL+lZ)), 0, 500*sizeof(UINT16));
		memset((*(ucSOPC_DTL+lZ)), 0, 500*sizeof(UINT8));
	}

	for(lTrailDegree=-lDegree; lTrailDegree<=lDegree; lTrailDegree+=lInterval, lDegree_idx++, ulIndex=0)
	{
		for(lY = 0; lY<lHeight; lY++, bFirst = FALSE)
		{
			for(lX = 0; lX<lWidth; lX++)
			{
				//起始行&不等於底色
				if(bFirst == FALSE && (*(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel)) != 0xFF || *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1)) != 0x80 || *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2)) != 0x80) )
				{
					(*(poLine+lDegree_idx)+ulIndex)->ucY = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel));
					(*(poLine+lDegree_idx)+ulIndex)->ucCr = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1));
					(*(poLine+lDegree_idx)+ulIndex)->ucCb = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2));
					(*(poLine+lDegree_idx)+ulIndex)->uwStartx = lX;
					(*(poLine+lDegree_idx)+ulIndex)->uwEndx = lX;
					(*(poLine+lDegree_idx)+ulIndex)->uwYaxis = lY;
					(*(poLine+lDegree_idx)+ulIndex)->uwOBI = ulIndex;
					((*(poLine+lDegree_idx)+ulIndex)->uwLength)++;
					bFirst = TRUE;
					*(ulTotalLine_DTL+lDegree_idx) = ulIndex;
					if(lX == lWidth-1)
						ulIndex++;
				}
				//起始行延伸&(延伸色=前一行延伸色)
				else if(bFirst == TRUE && *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel)) == *(*(pucData+lDegree_idx)+((lX-1)*lChannel+lY*lWidth*lChannel))
									  && *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1)) == *(*(pucData+lDegree_idx)+((lX-1)*lChannel+lY*lWidth*lChannel+1))
									  && *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2)) == *(*(pucData+lDegree_idx)+((lX-1)*lChannel+lY*lWidth*lChannel+2)))
				{
					(*(poLine+lDegree_idx)+ulIndex)->uwEndx = lX;
					(*(poLine+lDegree_idx)+ulIndex)->uwLength = ((*(poLine+lDegree_idx)+ulIndex)->uwEndx - (*(poLine+lDegree_idx)+ulIndex)->uwStartx) + 1;
					//延伸色大於127length
					if((*(poLine+lDegree_idx)+ulIndex)->uwLength > 0x7F)
					{
						((*(poLine+lDegree_idx)+ulIndex)->uwEndx)--;
						((*(poLine+lDegree_idx)+ulIndex)->uwLength)--;
						ulIndex++;
						(*(poLine+lDegree_idx)+ulIndex)->ucY = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel));
						(*(poLine+lDegree_idx)+ulIndex)->ucCr = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1));
						(*(poLine+lDegree_idx)+ulIndex)->ucCb = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2));
						(*(poLine+lDegree_idx)+ulIndex)->uwStartx = lX;
						(*(poLine+lDegree_idx)+ulIndex)->uwEndx = lX;
						(*(poLine+lDegree_idx)+ulIndex)->uwYaxis = lY;
						(*(poLine+lDegree_idx)+ulIndex)->uwOBI = ulIndex;
						((*(poLine+lDegree_idx)+ulIndex)->uwLength)++;
						bFirst = TRUE;
						*(ulTotalLine_DTL+lDegree_idx) = ulIndex;
						if(lX == lWidth-1)
						{
							ulIndex++;
							continue;
						}
					}
					if(lX == lWidth-1)
						ulIndex++;
				}
				//起始行延伸&&(延伸色!=前一行延伸色)
				else if(bFirst == TRUE && (*(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel)) != *(*(pucData+lDegree_idx)+((lX-1)*lChannel+lY*lWidth*lChannel))
									  || *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1)) != *(*(pucData+lDegree_idx)+((lX-1)*lChannel+lY*lWidth*lChannel+1))
									  || *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2)) != *(*(pucData+lDegree_idx)+((lX-1)*lChannel+lY*lWidth*lChannel+2))))
				{
					ulIndex++;
					//延伸色為另一色
					if(*(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel)) != 0xFF
					|| *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1)) != 0x80
					|| *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2)) != 0x80)
					{
						(*(poLine+lDegree_idx)+ulIndex)->ucY = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel));
						(*(poLine+lDegree_idx)+ulIndex)->ucCr = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+1));
						(*(poLine+lDegree_idx)+ulIndex)->ucCb = *(*(pucData+lDegree_idx)+(lX*lChannel+lY*lWidth*lChannel+2));
						(*(poLine+lDegree_idx)+ulIndex)->uwStartx = lX;
						(*(poLine+lDegree_idx)+ulIndex)->uwEndx = lX;
						(*(poLine+lDegree_idx)+ulIndex)->uwYaxis = lY;
						(*(poLine+lDegree_idx)+ulIndex)->uwOBI = ulIndex;
						((*(poLine+lDegree_idx)+ulIndex)->uwLength)++;
						bFirst = TRUE;
						*(ulTotalLine_DTL+lDegree_idx) = ulIndex;
						if(lX == lWidth-1)
							ulIndex++;
					}
					//延伸色為底色
					else
						bFirst = FALSE;
					*(ulTotalLine_DTL+lDegree_idx) = ulIndex;
				}
			}
		}

		//{
		//int i;
		//FILE* step1;
		//step1 = fopen("step1.txt","w");
		//for(i=0; i<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); i++)
		//{
		//	fprintf(step1,"(%3d,%3d,%3d) (%3d~%3d,%3d) %3d %3d\n",(*(poLine+lDegree_idx)+i)->ucY, (*(poLine+lDegree_idx)+i)->ucCb, (*(poLine+lDegree_idx)+i)->ucCr, (*(poLine+lDegree_idx)+i)->uwStartx, (*(poLine+lDegree_idx)+i)->uwEndx, (*(poLine+lDegree_idx)+i)->uwYaxis, (*(poLine+lDegree_idx)+i)->uwLength, (*(poLine+lDegree_idx)+i)->uwOBI);
		//}
		//fclose(step1);
		//}

		//物件切割-由上至下
		for(lLine_idx = 0; lLine_idx<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); lLine_idx++){//scan total line
			for(lCompare_idx=0; lCompare_idx<lLine_idx; lCompare_idx++){//scan before line
				if((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis - (*(poLine+lDegree_idx)+lCompare_idx)->uwYaxis ==1)	//上下相鄰
				{
					if(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx < (*(poLine+lDegree_idx)+lCompare_idx)->uwStartx && (*(poLine+lDegree_idx)+lLine_idx)->uwEndx < (*(poLine+lDegree_idx)+lCompare_idx)->uwStartx)
					  ||((*(poLine+lDegree_idx)+lLine_idx)->uwStartx > (*(poLine+lDegree_idx)+lCompare_idx)->uwEndx && (*(poLine+lDegree_idx)+lLine_idx)->uwEndx > (*(poLine+lDegree_idx)+lCompare_idx)->uwEndx))
						continue;
					else
					{
						if((*(poLine+lDegree_idx)+lLine_idx)->ucY == (*(poLine+lDegree_idx)+lCompare_idx)->ucY
							&&(*(poLine+lDegree_idx)+lLine_idx)->ucCb == (*(poLine+lDegree_idx)+lCompare_idx)->ucCb
							&&(*(poLine+lDegree_idx)+lLine_idx)->ucCr == (*(poLine+lDegree_idx)+lCompare_idx)->ucCr)
						{
							if((*(poLine+lDegree_idx)+lLine_idx)->uwOBI>(*(poLine+lDegree_idx)+lCompare_idx)->uwOBI)
								(*(poLine+lDegree_idx)+lLine_idx)->uwOBI = (*(poLine+lDegree_idx)+lCompare_idx)->uwOBI;
							else
								(*(poLine+lDegree_idx)+lCompare_idx)->uwOBI = (*(poLine+lDegree_idx)+lLine_idx)->uwOBI;
						}
					}
				}
				else
					continue;
			}
		}

		//物件切割-由下至上
		for(lLine_idx = (*(ulTotalLine_DTL+lDegree_idx)); lLine_idx>=0; lLine_idx--){//scan total line
			for(lCompare_idx=0; lCompare_idx<lLine_idx; lCompare_idx++){//scan before line
				if((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis - (*(poLine+lDegree_idx)+lCompare_idx)->uwYaxis ==1)	//上下相鄰
				{
					if(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx < (*(poLine+lDegree_idx)+lCompare_idx)->uwStartx && (*(poLine+lDegree_idx)+lLine_idx)->uwEndx < (*(poLine+lDegree_idx)+lCompare_idx)->uwStartx)
					  ||((*(poLine+lDegree_idx)+lLine_idx)->uwStartx > (*(poLine+lDegree_idx)+lCompare_idx)->uwEndx && (*(poLine+lDegree_idx)+lLine_idx)->uwEndx > (*(poLine+lDegree_idx)+lCompare_idx)->uwEndx))
						continue;
					else
					{ 
						if((*(poLine+lDegree_idx)+lLine_idx)->ucY == (*(poLine+lDegree_idx)+lCompare_idx)->ucY
							&&(*(poLine+lDegree_idx)+lLine_idx)->ucCb == (*(poLine+lDegree_idx)+lCompare_idx)->ucCb
							&&(*(poLine+lDegree_idx)+lLine_idx)->ucCr == (*(poLine+lDegree_idx)+lCompare_idx)->ucCr)
						{
							if((*(poLine+lDegree_idx)+lLine_idx)->uwOBI>(*(poLine+lDegree_idx)+lCompare_idx)->uwOBI)
								(*(poLine+lDegree_idx)+lLine_idx)->uwOBI = (*(poLine+lDegree_idx)+lCompare_idx)->uwOBI;
							else
								(*(poLine+lDegree_idx)+lCompare_idx)->uwOBI = (*(poLine+lDegree_idx)+lLine_idx)->uwOBI;
						}
					}
				}
				else
					continue;
			}
		}

		//{
		//int i;
		//FILE* step2;
		//step2 = fopen("step2.txt","w");
		//for(i=0; i<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); i++)
		//{
		//	fprintf(step2,"(%3d,%3d,%3d) (%3d~%3d,%3d) %3d %3d\n",(*(poLine+lDegree_idx)+i)->ucY, (*(poLine+lDegree_idx)+i)->ucCb, (*(poLine+lDegree_idx)+i)->ucCr, (*(poLine+lDegree_idx)+i)->uwStartx, (*(poLine+lDegree_idx)+i)->uwEndx, (*(poLine+lDegree_idx)+i)->uwYaxis, (*(poLine+lDegree_idx)+i)->uwLength, (*(poLine+lDegree_idx)+i)->uwOBI);
		//}
		//fclose(step2);
		//}

		//物件個數
		for(lLine_idx = 0; lLine_idx<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); lLine_idx++, bSaveBuf = FALSE)
		{
			if(lLine_idx == 0)	//起始line
			{
				*(*(uwBuffer_DTL+lDegree_idx)+(*(uwTotalObject_DTL+lDegree_idx))) = (*(poLine+lDegree_idx)+lLine_idx)->uwOBI;
				(*(uwTotalObject_DTL+lDegree_idx))++;
			}
			else
			{
				for(lZ=0; lZ<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); lZ++)	//與buffer內的element元素互相比較，若發現buffer內有此object，則savebuf=TRUE
				{
					if((*(poLine+lDegree_idx)+lLine_idx)->uwOBI == *(*(uwBuffer_DTL+lDegree_idx)+lZ))
						bSaveBuf = TRUE;
				}
				if(bSaveBuf == FALSE)	//buffer中未具有此object，存入buffer
				{
					*(*(uwBuffer_DTL+lDegree_idx)+(*(uwTotalObject_DTL+lDegree_idx))) = (*(poLine+lDegree_idx)+lLine_idx)->uwOBI;
					(*(uwTotalObject_DTL+lDegree_idx))++;
				}
			}
		}

		for(lObject=0, ulCount=0, ulIndex=0; lObject<(*(uwTotalObject_DTL+lDegree_idx)); lObject++, ulCount=0, ulIndex++)	//scan object
		{
			for(lLine_idx = 0; lLine_idx<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); lLine_idx++)	//scan line
			{
				if(*(*(uwBuffer_DTL+lDegree_idx)+lObject) == (*(poLine+lDegree_idx)+lLine_idx)->uwOBI)	//scan line的object index == *(buffer+object)
				{
					if(lLine_idx == *(*(uwBuffer_DTL+lDegree_idx)+lObject))	
					{
						(*(poLine+lDegree_idx)+*(*(uwBuffer_DTL+lDegree_idx)+lObject))->wPreLine_Difx = 0;
						(*(poLine+lDegree_idx)+*(*(uwBuffer_DTL+lDegree_idx)+lObject))->wPreLine_Dify = 0;
						(*(poLine+lDegree_idx)+*(*(uwBuffer_DTL+lDegree_idx)+lObject))->wQuotient = 0;
						(*(poLine+lDegree_idx)+*(*(uwBuffer_DTL+lDegree_idx)+lObject))->wRemainder = 0;
						(*(poLine+lDegree_idx)+*(*(uwBuffer_DTL+lDegree_idx)+lObject))->bSOP = TRUE;
						ulCount += 11;
						(*(poLine+lDegree_idx)+*(*(uwBuffer_DTL+lDegree_idx)+lObject))->ucCPC = ulCount;
						lBefLine_idx = lLine_idx;
						lBefObj_idx = lObject;
					}
					else if(lBefObj_idx != lObject)
					{			
						(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx = 0;
						(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify = 0;
						(*(poLine+lDegree_idx)+lLine_idx)->wQuotient = 0;
						(*(poLine+lDegree_idx)+lLine_idx)->wRemainder = 0;
						(*(poLine+lDegree_idx)+lLine_idx)->bSOP = TRUE;
						ulCount += 11;
						(*(poLine+lDegree_idx)+lLine_idx)->ucCPC = ulCount;
						lBefLine_idx = lLine_idx;
						lBefObj_idx = lObject;
					}
					else
					{
						(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx = (*(poLine+lDegree_idx)+lLine_idx)->uwStartx - (*(poLine+lDegree_idx)+lBefLine_idx)->uwStartx;
						(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify = (*(poLine+lDegree_idx)+lLine_idx)->uwYaxis - (*(poLine+lDegree_idx)+lBefLine_idx)->uwYaxis;
						(*(poLine+lDegree_idx)+lLine_idx)->wQuotient = ((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx)/0x7F;
						(*(poLine+lDegree_idx)+lLine_idx)->wRemainder = ((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx)%0x7F;
						if((*(poLine+lDegree_idx)+lLine_idx)->wQuotient == 0)
							ulCount += 3;
						else
						{
							if((*(poLine+lDegree_idx)+lLine_idx)->wRemainder == 0)
								ulCount += (abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*3;
							else
								ulCount += ((abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))+1)*3;
						}
						(*(poLine+lDegree_idx)+lLine_idx)->ucCPC = ulCount;

						if(ulCount>240)	//封包數量>240bytes時
						{
							*(*(ucSOPC_DTL+lDegree_idx)+ulIndex) = (*(poLine+lDegree_idx)+lBefLine_idx)->ucCPC;
							ulIndex++;
							*(ulPacketTotal_DTL+lDegree_idx) += ulCount;	//total sum
							*(ulPacketTotal_DTL+lDegree_idx) -= (ulCount - (*(poLine+lDegree_idx)+lBefLine_idx)->ucCPC);	//扣掉超出封包量
							//start of packet initialize
							(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx = 0;
							(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify = 0;
							(*(poLine+lDegree_idx)+lLine_idx)->wQuotient = 0;
							(*(poLine+lDegree_idx)+lLine_idx)->wRemainder = 0;
							(*(poLine+lDegree_idx)+lLine_idx)->ucCPC = 11;
							ulCount = 11;
							(*(poLine+lDegree_idx)+lLine_idx)->bSOP = TRUE;
						}
						lBefLine_idx = lLine_idx;
						lBefObj_idx = lObject;
					}
				}
			}
			*(ulPacketTotal_DTL+lDegree_idx) += ulCount;
			*(*(ucSOPC_DTL+lDegree_idx)+ulIndex) = ulCount;
		}
	}
}

void EAGLEGP_WriteBatFile(EAGLEGP_TL_INDX ucType, EAGLEGP_PieceLineInfo* poLine, UINT32 ulTotalLine, UINT16 uwTotalObject, UINT16* uwBuffer, UINT8* ucSOPC, UINT32 ulPacketTotal)
{
	FILE* pGenFile;
	INT8 sView[10];
	INT8 sFileName[15];
	INT8 sFormatType[15];
	INT32 lZ = 0, lStartPacIndex = 0, lObject = 0;
	INT32 lLine_idx = 0;

	switch(ucType)
	{
	case 0:
		strcpy_s(sView,10,"BV_Left");
		strcpy_s(sFileName,15,"BV_Left.bat");
		strcpy_s(sFormatType,15," 90 3F B0 00 ");
		break;
	case 1:
		strcpy_s(sView,10,"BV_Right");
		strcpy_s(sFileName,15,"BV_Right.bat");
		strcpy_s(sFormatType,15," 90 3F C0 00 ");
		break;
	case 2:
		strcpy_s(sView,10,"BV_Front");
		strcpy_s(sFileName,15,"BV_Front.bat");
		strcpy_s(sFormatType,15," 90 38 00 00 ");
		break;
	case 3:
		strcpy_s(sView,10,"BV_Rear");
		strcpy_s(sFileName,15,"BV_Rear.bat");
		strcpy_s(sFormatType,15," 90 3B C0 00 ");
		break;
	}

	fopen_s(&pGenFile, sFileName, "w");
	fprintf(pGenFile,";Write date (%s)\n", sView);
	fprintf(pGenFile,"55 0E A5 3A EC EE AD DA%s00 99\n",sFormatType);
	fprintf(pGenFile,"55 26 A5 3B BA BE %02X %02X %02X %02X FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 00 99",(ulPacketTotal>>24)&0xFF,(ulPacketTotal>>16)&0xFF,(ulPacketTotal>>8)&0xFF,ulPacketTotal&0xFF);
	
	for(lObject=0, lStartPacIndex = 0; lObject<uwTotalObject; lObject++)	//scan object
	{
		for(lLine_idx=0; lLine_idx<(INT32)ulTotalLine ; lLine_idx++)	//scan line
		{
			if((poLine+lLine_idx)->uwOBI != *(uwBuffer+lObject))
				continue;
			if(lLine_idx == *(uwBuffer+lObject))	//packet header
			{
				fprintf(pGenFile,"\n55 %02X A5 3B",(*(ucSOPC+lStartPacIndex)+6));
				fprintf(pGenFile," FF %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",(poLine+lLine_idx)->ucY,(poLine+lLine_idx)->ucCb,(poLine+lLine_idx)->ucCr
					,(((poLine+lLine_idx)->uwYaxis)>>8)&0xFF,((poLine+lLine_idx)->uwYaxis)&0xFF,(((poLine+lLine_idx)->uwStartx)>>8)&0xFF,((poLine+lLine_idx)->uwStartx)&0xFF
					,(poLine+lLine_idx)->uwLength,(poLine+lLine_idx)->wPreLine_Dify,(poLine+lLine_idx)->wPreLine_Difx);
				lStartPacIndex++;
			}
			else if((poLine+lLine_idx)->bSOP==1)	//new packet header because overpacket
			{
				fprintf(pGenFile," 00 99\n55 %02X A5 3B",(*(ucSOPC+lStartPacIndex)+6));
				fprintf(pGenFile," FF %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",(poLine+lLine_idx)->ucY,(poLine+lLine_idx)->ucCb,(poLine+lLine_idx)->ucCr
					,(((poLine+lLine_idx)->uwYaxis)>>8)&0xFF,((poLine+lLine_idx)->uwYaxis)&0xFF,(((poLine+lLine_idx)->uwStartx)>>8)&0xFF,((poLine+lLine_idx)->uwStartx)&0xFF
					,(poLine+lLine_idx)->uwLength,(poLine+lLine_idx)->wPreLine_Dify,(poLine+lLine_idx)->wPreLine_Difx);
				lStartPacIndex++;
			}
			else
			{
				if((poLine+lLine_idx)->wQuotient!=0 && (poLine+lLine_idx)->wRemainder!=0)
				{
					for(lZ = 1; lZ <= abs((poLine+lLine_idx)->wQuotient); lZ++)
						fprintf(pGenFile," %02X %02X %02X",0,0, (unsigned char)(((poLine+lLine_idx)->wQuotient / abs((poLine+lLine_idx)->wQuotient))*127));
					fprintf(pGenFile," %02X %02X %02X",(poLine+lLine_idx)->uwLength,(unsigned char)((poLine+lLine_idx)->wPreLine_Dify),(unsigned char)((poLine+lLine_idx)->wRemainder));
				}
				else if((poLine+lLine_idx)->wQuotient!=0 && (poLine+lLine_idx)->wRemainder == 0)
				{
					for(lZ = 1; lZ <= (abs((poLine+lLine_idx)->wQuotient))-1; lZ++)
						fprintf(pGenFile," %02X %02X %02X",0,0, (unsigned char)(((poLine+lLine_idx)->wQuotient / abs((poLine+lLine_idx)->wQuotient))*127));	
					fprintf(pGenFile," %02X %02X %02X",(poLine+lLine_idx)->uwLength,(unsigned char)((poLine+lLine_idx)->wPreLine_Dify),(unsigned char)(((poLine+lLine_idx)->wQuotient / abs((poLine+lLine_idx)->wQuotient))*127));
				}
				else
				{
					fprintf(pGenFile," %02X %02X %02X",(poLine+lLine_idx)->uwLength,(unsigned char)((poLine+lLine_idx)->wPreLine_Dify),(unsigned char)((poLine+lLine_idx)->wPreLine_Difx));
				}
			}
		}
		fprintf(pGenFile," 00 99");
	}
	fprintf(pGenFile,"\n");
	fclose(pGenFile);
}

void EAGLEGP_WriteDyBatFile(EAGLEGP_TL_INDX ucType, INT32 lDegree, INT32 lInterval, EAGLEGP_PieceLineInfo* poLine[], UINT32* ulTotalLine_DTL, UINT16* uwTotalObject_DTL, UINT16* uwBuffer_DTL[], UINT8* ucSOPC_DTL[], UINT32* ulPacketTotal_DTL)
{
	FILE* pGenFile;
	INT8 sView[10];
	INT8 sFileName[15];
	INT8 sFormatType[15];
	INT32 lZ = 0, lStartPacIndex = 0, lObject = 0;
	INT32 lLine_idx = 0;
	INT32 lSum = 0, lTotalSum = 0;
	INT32 lTrailDegree, lDegree_idx = 0;

	switch(ucType)
	{
	case 4:
		strcpy_s(sView,10,"Dy_Front");
		strcpy_s(sFileName,15,"Dy_Front.bat");
		strcpy_s(sFormatType,15," 90 38 30 00 ");
		break;
	case 5:
		strcpy_s(sView,10,"Dy_Back");
		strcpy_s(sFileName,15,"Dy_Back.bat");
		strcpy_s(sFormatType,15," 90 3B F0 00 ");
		break;
	}
	
	fopen_s(&pGenFile, sFileName, "w");
	fprintf(pGenFile,";Write date (%s)\n", sView);
	fprintf(pGenFile,"55 0E A5 3A EC EE AD DA%s00 99\n",sFormatType);
	for(lZ=0; lZ<((lDegree/lInterval)<<1)+1; lZ++)
	{
		lTotalSum+=(*(ulPacketTotal_DTL+lZ));
	}
	fprintf(pGenFile,"55 26 A5 3B BA BE %02X %02X %02X %02X %02X %02X FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 00 99\n",(lTotalSum>>24)&0xFF, (lTotalSum>>16)&0xFF, (lTotalSum>>8)&0xFF, lTotalSum&0xFF, ((((lDegree/lInterval)<<1)+1)>>8)&0xFF, (((lDegree/lInterval)<<1)+1)&0xFF);
	for(lZ=0; lZ<((lDegree/lInterval)<<1)+1; lZ++)
	{
		if(lZ == 0)
		{
			fprintf(pGenFile,"55 %02X A5 3B 00 00 00 00 ",((((lDegree/lInterval)<<1)+1)*4)+6);
		}
		else if(lZ != 0 && lZ!=((lDegree/lInterval)<<1))
		{
			lSum+=(*(ulPacketTotal_DTL+(lZ-1)));
			fprintf(pGenFile,"%02X %02X %02X %02X ",(lSum>>24)&0xFF,(lSum>>16)&0xFF,(lSum>>8)&0xFF,lSum&0xFF);
		}
		else if(lZ==((lDegree/lInterval)<<1))
		{
			lSum+=(*(ulPacketTotal_DTL+(lZ-1)));
			fprintf(pGenFile,"%02X %02X %02X %02X 00 99",(lSum>>24)&0xFF,(lSum>>16)&0xFF,(lSum>>8)&0xFF,lSum&0xFF);
		}
	}

	for(lTrailDegree=-lDegree; lTrailDegree<=lDegree; lTrailDegree+=lInterval, lDegree_idx++, lStartPacIndex=0)
	{
		for(lObject=0, lStartPacIndex = 0; lObject<(*(uwTotalObject_DTL+lDegree_idx)); lObject++)	//scan object
		{
			for(lLine_idx=0; lLine_idx<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); lLine_idx++)	//scan line
			{
				if((*(poLine+lDegree_idx)+lLine_idx)->uwOBI != (*(*(uwBuffer_DTL+lDegree_idx)+lObject)))
					continue;
				if(lLine_idx == (*(*(uwBuffer_DTL+lDegree_idx)+lObject)))	//packet header	
				{
					fprintf(pGenFile,"\n55 %02X A5 3B",(*(*(ucSOPC_DTL+lDegree_idx)+lStartPacIndex)+6));
					fprintf(pGenFile," FF %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->ucY,(*(poLine+lDegree_idx)+lLine_idx)->ucCb,(*(poLine+lDegree_idx)+lLine_idx)->ucCr
						,(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF,(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF
						,(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx);
					lStartPacIndex++;
				}
				else if((*(poLine+lDegree_idx)+lLine_idx)->bSOP==1)	//new packet header because overpacket
				{
					fprintf(pGenFile," 00 99\n55 %02X A5 3B",(*(*(ucSOPC_DTL+lDegree_idx)+lStartPacIndex)+6));
					fprintf(pGenFile," FF %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->ucY,(*(poLine+lDegree_idx)+lLine_idx)->ucCb,(*(poLine+lDegree_idx)+lLine_idx)->ucCr
						,(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF,(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF
						,(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx);
					lStartPacIndex++;
				}
				else
				{
					if((*(poLine+lDegree_idx)+lLine_idx)->wQuotient!=0 && (*(poLine+lDegree_idx)+lLine_idx)->wRemainder!=0)
					{
						for(lZ = 1; lZ <= abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient); lZ++)
							fprintf(pGenFile," %02X %02X %02X",0,0, (unsigned char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
						fprintf(pGenFile," %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wRemainder));
					}
					else if((*(poLine+lDegree_idx)+lLine_idx)->wQuotient!=0 && (*(poLine+lDegree_idx)+lLine_idx)->wRemainder == 0)
					{
						for(lZ = 1; lZ <= (abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))-1; lZ++)
							fprintf(pGenFile," %02X %02X %02X",0,0, (unsigned char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));	
						fprintf(pGenFile," %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(unsigned char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
					}
					else
					{
						fprintf(pGenFile," %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx));
					}
				}
			}
			fprintf(pGenFile," 00 99");
		}
	}
	fprintf(pGenFile,"\n");
	fclose(pGenFile);
}

void EAGLEI_WriteDyBatFile(EAGLEGP_TL_INDX ucType, INT32 lDegree, INT32 lInterval, EAGLEGP_PieceLineInfo* poLine[], UINT32* ulTotalLine_DTL, UINT16* uwTotalObject_DTL, UINT16* uwBuffer_DTL[], UINT8* ucSOPC_DTL[], UINT32* ulPacketTotal_DTL)
{
	FILE* pGenFile;
	INT8 sView[10];
	INT8 sFileName[15];
	INT8 sFormatType[15];
	INT32 lZ = 0, lStartPacIndex = 0, lObject = 0;
	INT32 lLine_idx = 0;
	INT32 lSum = 0, lTotalSum = 0;
	INT32 lTrailDegree, lDegree_idx = 0;

	switch(ucType)
	{
	case 4:
		strcpy_s(sView,10,"Dy_Front");
		strcpy_s(sFileName,15,"Dy_Front.txt");
		strcpy_s(sFormatType,15," 90 38 30 00 ");
		break;
	case 5:
		strcpy_s(sView,10,"Dy_Back");
		strcpy_s(sFileName,15,"Dy_Back.txt");
		strcpy_s(sFormatType,15," 90 3B F0 00 ");
		break;
	}
	
	fopen_s(&pGenFile, sFileName, "w");
	fprintf(pGenFile,";Write date (%s)\n", sView);
	//fprintf(pGenFile,"55 0E A5 3A EC EE AD DA%s00 99\n",sFormatType);
	for(lZ=0; lZ<((lDegree/lInterval)<<1)+1; lZ++)
	{
		lTotalSum+=(*(ulPacketTotal_DTL+lZ));
	}
	fprintf(pGenFile,"#defined BDynTrail_Len %d\n",lTotalSum);
	for(lZ=0; lZ<((lDegree/lInterval)<<1)+1; lZ++)
	{
		if(lZ == 0)
		{
			fprintf(pGenFile,"unsigned int AngleIdx[] = \n{");
			fprintf(pGenFile,"0, ",((((lDegree/lInterval)<<1)+1)*4)+6);
		}
		else if(lZ != 0 && lZ!=((lDegree/lInterval)<<1))
		{
			lSum+=(*(ulPacketTotal_DTL+(lZ-1)));
			fprintf(pGenFile,"%d, ",lSum);
		}
		else if(lZ==((lDegree/lInterval)<<1))
		{
			lSum+=(*(ulPacketTotal_DTL+(lZ-1)));
			fprintf(pGenFile,"%d\n};\n",lSum);
		}
	}

	for(lTrailDegree=-lDegree; lTrailDegree<=lDegree; lTrailDegree+=lInterval, lDegree_idx++, lStartPacIndex=0)
	{
		for(lObject=0, lStartPacIndex = 0; lObject<(*(uwTotalObject_DTL+lDegree_idx)); lObject++)	//scan object
		{
			for(lLine_idx=0; lLine_idx<(INT32)(*(ulTotalLine_DTL+lDegree_idx)); lLine_idx++)	//scan line
			{
				if((*(poLine+lDegree_idx)+lLine_idx)->uwOBI != (*(*(uwBuffer_DTL+lDegree_idx)+lObject)))
					continue;
				if(lLine_idx == (*(*(uwBuffer_DTL+lDegree_idx)+lObject)))	//packet header	
				{
					fprintf(pGenFile,"\n-1, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ",(char)((*(poLine+lDegree_idx)+lLine_idx)->ucY),(char)((*(poLine+lDegree_idx)+lLine_idx)->ucCb),(char)((*(poLine+lDegree_idx)+lLine_idx)->ucCr)
						,(char)((((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF),(char)(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF),(char)((((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF),(char)(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF)
						,(char)((*(poLine+lDegree_idx)+lLine_idx)->uwLength),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx));

					/*fprintf(pGenFile,"-1, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ",(*(poLine+lDegree_idx)+lLine_idx)->ucY,(*(poLine+lDegree_idx)+lLine_idx)->ucCb,(*(poLine+lDegree_idx)+lLine_idx)->ucCr
						,(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF,(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF
						,(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx);*/
					
					//fprintf(pGenFile,"\n55 %02X A5 3B",(*(*(ucSOPC_DTL+lDegree_idx)+lStartPacIndex)+6));
					//fprintf(pGenFile," FF %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->ucY,(*(poLine+lDegree_idx)+lLine_idx)->ucCb,(*(poLine+lDegree_idx)+lLine_idx)->ucCr
					//	,(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF,(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF
					//	,(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx);
					
					lStartPacIndex++;
				}
				else if((*(poLine+lDegree_idx)+lLine_idx)->bSOP==1)	//new packet header because overpacket
				{
					fprintf(pGenFile,"\n-1, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ",(char)((*(poLine+lDegree_idx)+lLine_idx)->ucY),(char)((*(poLine+lDegree_idx)+lLine_idx)->ucCb),(char)((*(poLine+lDegree_idx)+lLine_idx)->ucCr)
						,(char)((((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF),(char)(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF),(char)((((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF),(char)(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF)
						,(char)((*(poLine+lDegree_idx)+lLine_idx)->uwLength),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx));

					/*fprintf(pGenFile,"\n-1, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, ",(*(poLine+lDegree_idx)+lLine_idx)->ucY,(*(poLine+lDegree_idx)+lLine_idx)->ucCb,(*(poLine+lDegree_idx)+lLine_idx)->ucCr
						,(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF,(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF
						,(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx);*/

					//fprintf(pGenFile," 00 99\n55 %02X A5 3B",(*(*(ucSOPC_DTL+lDegree_idx)+lStartPacIndex)+6));
					//fprintf(pGenFile," FF %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->ucY,(*(poLine+lDegree_idx)+lLine_idx)->ucCb,(*(poLine+lDegree_idx)+lLine_idx)->ucCr
					//	,(((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwYaxis)&0xFF,(((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)>>8)&0xFF,((*(poLine+lDegree_idx)+lLine_idx)->uwStartx)&0xFF
					//	,(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify,(*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx);

					lStartPacIndex++;
				}
				else
				{
					if((*(poLine+lDegree_idx)+lLine_idx)->wQuotient!=0 && (*(poLine+lDegree_idx)+lLine_idx)->wRemainder!=0)
					{
						for(lZ = 1; lZ <= abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient); lZ++)
							fprintf(pGenFile,"0, 0, %d, ",(char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
							//fprintf(pGenFile," %02X %02X %02X",0,0, (unsigned char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
						//fprintf(pGenFile," %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wRemainder));
						fprintf(pGenFile,"%d, %d, %d, ",(char)((*(poLine+lDegree_idx)+lLine_idx)->uwLength),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(char)((*(poLine+lDegree_idx)+lLine_idx)->wRemainder));
					}
					else if((*(poLine+lDegree_idx)+lLine_idx)->wQuotient!=0 && (*(poLine+lDegree_idx)+lLine_idx)->wRemainder == 0)
					{
						for(lZ = 1; lZ <= (abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))-1; lZ++)
							fprintf(pGenFile,"0, 0, %d, ",(char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
							//fprintf(pGenFile," %02X %02X %02X",0,0, (unsigned char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));	
						//fprintf(pGenFile," %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(unsigned char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
						fprintf(pGenFile,"%d, %d, %d, ",(char)((*(poLine+lDegree_idx)+lLine_idx)->uwLength),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(char)(((*(poLine+lDegree_idx)+lLine_idx)->wQuotient / abs((*(poLine+lDegree_idx)+lLine_idx)->wQuotient))*127));
					}
					else
					{
						//fprintf(pGenFile," %02X %02X %02X",(*(poLine+lDegree_idx)+lLine_idx)->uwLength,(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(unsigned char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx));
						fprintf(pGenFile,"%d, %d, %d, ",(char)((*(poLine+lDegree_idx)+lLine_idx)->uwLength),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Dify),(char)((*(poLine+lDegree_idx)+lLine_idx)->wPreLine_Difx));
					}
				}
			}
			//fprintf(pGenFile," 00 99");
		}
	}
	fprintf(pGenFile,"\n");
	fclose(pGenFile);
}

#endif // Only do "Gen Trail Line Bat" in PC mode
