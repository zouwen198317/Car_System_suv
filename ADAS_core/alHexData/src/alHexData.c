
#include <assert.h>
#include <string.h>
#include "alHexData.h"

/** \cond DOXYGEN_EXCLUDE */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 * alHEXDATA_SectionSeek(UINT8 * a_pucConfigFileBuf, UINT32 a_ulConfigFileLength, UINT32 a_ulSectionID, UINT32 * a_pulSectionLength)
{
    UINT32 * pulConfigFilePtr = (UINT32*)a_pucConfigFileBuf;
    UINT32 ulSectionID;
    UINT32 ulSectionLength;
    while (((UINT8*)pulConfigFilePtr - a_pucConfigFileBuf) < (INT32)a_ulConfigFileLength)
    {
        ulSectionID = *pulConfigFilePtr;
        ulSectionLength = *(pulConfigFilePtr + 1);
        if (ulSectionID == a_ulSectionID)
        {
            (*a_pulSectionLength) = ulSectionLength * BYTE_OF_DATA_ITEM;
            return (UINT8*)(pulConfigFilePtr + 2);
        }
        else
        {
            pulConfigFilePtr += (ulSectionLength + 2);
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 * alHEXDATA_SectionInitial(UINT8 * a_pucConfigFileBuf, UINT32 a_pulSectionID, UINT32 a_pulSectionLength)
{
    UINT32 * pulConfigFilePtr = (UINT32*)a_pucConfigFileBuf;
    *pulConfigFilePtr = a_pulSectionID;
    *(pulConfigFilePtr + 1) = a_pulSectionLength / BYTE_OF_DATA_ITEM;
    return (UINT8*)(pulConfigFilePtr + 2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 * alHEXDATA_DataUnpack(UINT8 * a_pucSectionBuf, UINT32 * a_pulDataID, UINT32 * a_pulDataLength, UINT8 ** a_pucDataBuf)
{
    //UINT32 ulLength;
    UINT8 * pucSrc = a_pucSectionBuf;

    assert(sizeof(UINT32) == BYTE_OF_DATA_ITEM);

    // 1. 解出 Data ID
    memcpy(a_pulDataID, pucSrc, BYTE_OF_DATA_ID);
    pucSrc += BYTE_OF_DATA_ID;

    // 2. 解出 Data Length
    memcpy(a_pulDataLength, pucSrc, BYTE_OF_LENGTH);
    (*a_pulDataLength) *= BYTE_OF_DATA_ITEM;
    pucSrc += BYTE_OF_LENGTH;

    // 3. 解出 Data
    if (a_pucDataBuf != NULL)
    {
        (*a_pucDataBuf) = pucSrc;
    }

    return a_pucSectionBuf + BYTE_OF_DATA_ID + BYTE_OF_LENGTH + (*a_pulDataLength);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_DataPack(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucDataBuf, UINT8 * a_pucSectionBuf)
{
    UINT32 ulLength;
    UINT8 * pucDest = a_pucSectionBuf;

    assert(sizeof(UINT32) == BYTE_OF_DATA_ITEM);

    // 1. 算出 Section Buffer Length : in byte
    ulLength = BYTE_OF_DATA_ID + BYTE_OF_LENGTH + a_ulDataLength;

    if(a_pucSectionBuf != NULL)
    {
        UINT32 ulDataLengthInINT32 = a_ulDataLength / BYTE_OF_DATA_ITEM;

        // 1. 打包 Data ID
        memcpy(pucDest, &a_ulDataID, BYTE_OF_DATA_ID);
        pucDest += BYTE_OF_DATA_ID;

        // 2. 打包 Data Length
        memcpy(pucDest, &(ulDataLengthInINT32), BYTE_OF_LENGTH);
        pucDest += BYTE_OF_LENGTH;

        // 3. 打包 Data
        memcpy(pucDest, a_pucDataBuf, a_ulDataLength);
    }

    return ulLength;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 alHEXDATA_UnpackUINT8(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((UINT8*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT8 alHEXDATA_UnpackINT8(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((INT8*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT16 alHEXDATA_UnpackUINT16(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((UINT16*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT16 alHEXDATA_UnpackINT16(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((INT16*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_UnpackUINT32(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((UINT32*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT32 alHEXDATA_UnpackINT32(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((INT32*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FLOAT32 alHEXDATA_UnpackFLOAT32(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == BYTE_OF_DATA_ITEM);
    return *((FLOAT32*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FLOAT64 alHEXDATA_UnpackFLOAT64(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == (BYTE_OF_DATA_ITEM << 1));
    return *((FLOAT64*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT64 alHEXDATA_UnpackUINT64(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == (BYTE_OF_DATA_ITEM << 1));
    return *((UINT64*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT64 alHEXDATA_UnpackINT64(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf)
{
    assert(a_ulDataLength == (BYTE_OF_DATA_ITEM << 1));
    return *((INT64*)(a_pucDataBuf));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackUINT8(UINT32 a_ulDataID, UINT8 a_ucData, UINT8 * a_pucDestDataBuf)
{
    UINT32 ulSingleData; // minimum 4 bytes for single Data
    *((UINT8*)(&ulSingleData)) = a_ucData;
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&ulSingleData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackINT8(UINT32 a_ulDataID, INT8 a_cData, UINT8 * a_pucDestDataBuf)
{
    UINT32 ulSingleData; // minimum 4 bytes for single Data
    *((INT8*)(&ulSingleData)) = a_cData;
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&ulSingleData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackUINT16(UINT32 a_ulDataID, UINT16 a_uwData, UINT8 * a_pucDestDataBuf)
{
    UINT32 ulSingleData; // minimum 4 bytes for single Data
    *((UINT16*)(&ulSingleData)) = a_uwData;
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&ulSingleData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackINT16(UINT32 a_ulDataID, INT16 a_wData, UINT8 * a_pucDestDataBuf)
{
    UINT32 ulSingleData; // minimum 4 bytes for single Data
    *((INT16*)(&ulSingleData)) = a_wData;
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&ulSingleData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackUINT32(UINT32 a_ulDataID, UINT32 a_ulData, UINT8 * a_pucDestDataBuf)
{
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&a_ulData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackINT32(UINT32 a_ulDataID, INT32 a_lData, UINT8 * a_pucDestDataBuf)
{
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&a_lData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackFLOAT32(UINT32 a_ulDataID, FLOAT32 a_fData, UINT8 * a_pucDestDataBuf)
{
    UINT32 ulSingleData; // minimum 4 bytes for single Data
    *((FLOAT32*)(&ulSingleData)) = a_fData;
    return alHEXDATA_DataPack(a_ulDataID, BYTE_OF_DATA_ITEM, (UINT8*)&ulSingleData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackFLOAT64(UINT32 a_ulDataID, FLOAT64 a_eData, UINT8 * a_pucDestDataBuf)
{
    UINT64 ullSingleData; // 8 bytes for FLOAT64
    *((FLOAT64*)(&ullSingleData)) = a_eData;
    return alHEXDATA_DataPack(a_ulDataID, (BYTE_OF_DATA_ITEM << 1), (UINT8*)&ullSingleData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackUINT64(UINT32 a_ulDataID, UINT64 a_ullData, UINT8 * a_pucDestDataBuf)
{
    return alHEXDATA_DataPack(a_ulDataID, (BYTE_OF_DATA_ITEM << 1), (UINT8*)&a_ullData, a_pucDestDataBuf);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT32 alHEXDATA_PackINT64(UINT32 a_ulDataID, INT64 a_llData, UINT8 * a_pucDestDataBuf)
{
    return alHEXDATA_DataPack(a_ulDataID, (BYTE_OF_DATA_ITEM << 1), (UINT8*)&a_llData, a_pucDestDataBuf);
}

/** \endcond DOXYGEN_EXCLUDE */
