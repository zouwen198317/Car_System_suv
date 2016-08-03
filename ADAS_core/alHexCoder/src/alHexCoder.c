
#include "alHexCoder.h"


UINT8* alHEXCODER_GetCfgBuffer(UINT32 a_ulSectionID, UINT8 *a_pucDataSectionBuffer, UINT32 a_ulBufferSize, UINT32 *a_pulCfgSize)
{
    UINT32 ulDataID;                                    // Single Data ID
    UINT32 ulDataLength;                                // Single Data Length
    UINT8 *pucDataBuffer;                               // Single Data Buffer
    UINT32 ulBufferLength = 0;
    UINT32 *pucBuffer = NULL;   // 將 UINT8* 指標轉為 UINT32* 指標
    UINT32 *pulPtr = NULL;

    if (a_pucDataSectionBuffer == NULL)
    {
        return 0;
    }

    ulBufferLength = (a_ulBufferSize);
    pucBuffer = (UINT32*)a_pucDataSectionBuffer;   // 將 UINT8* 指標轉為 UINT32* 指標
    pulPtr = pucBuffer;

    // import
    while ((INT32)(pulPtr - pucBuffer) < (INT32)(ulBufferLength >> 2))
    {
        // 1. 從 File Buffer 中解出 Single Data 的相對資訊位置
        ulDataID = *pulPtr;
        ulDataLength = *(pulPtr + 1);
        pucDataBuffer = (UINT8 *)(pulPtr + 2);

        *a_pulCfgSize = ulDataLength << 2;

        if (ulDataID == a_ulSectionID)
        {
            return pucDataBuffer;
        }

        // 3. 累進指標
        pulPtr += (2 + ulDataLength);
    }

    return 0;
}