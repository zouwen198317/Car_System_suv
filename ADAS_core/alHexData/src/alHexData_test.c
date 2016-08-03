
#include "alHexData.h"
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

static UINT32 PV_TestSectionPack1(UINT32 a_ulSectionID, UINT8 * a_pucSectionDataPtr)
{
    UINT32 ulSectionLength = 0;
    UINT32 ulDataBufferIndex = 0;
    //UINT8 * pucDataBuffer = 0;
    UINT8 * pucDataPtr = a_pucSectionDataPtr;
    UINT8 ucNULLBuffer = (a_pucSectionDataPtr == 0) ? 0 : 1;

    UINT8 ucData = (1 << 3);
    INT8 cData = -(1 << 3);
    UINT16 uwData = (1 << 8) + (1 << 3);
    INT16 wData = -((1 << 8) + (1 << 3));
    UINT32 ulData = (1 << 16) + (1 << 8) + (1 << 3);
    INT32 lData = -((1 << 16) + (1 << 8) + (1 << 3));
    UINT64 ullData = ((UINT64)1 << 32) + (1 << 16) + (1 << 8) + (1 << 3);
    INT64 llData = -(((INT64)1 << 32) + (1 << 16) + (1 << 8) + (1 << 3));
    FLOAT32 fData = 1.f / 3.f;
    FLOAT64 eData = 1.0 / 3.0;

    ulSectionLength += alHEXDATA_PackUINT8((a_ulSectionID << 2) + 0x0000, ucData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT8((a_ulSectionID << 2) + 0x0001, cData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackUINT16((a_ulSectionID << 2) + 0x0002, uwData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT16((a_ulSectionID << 2) + 0x0003, wData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackUINT32((a_ulSectionID << 2) + 0x0004, ulData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT32((a_ulSectionID << 2) + 0x0005, lData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackUINT64((a_ulSectionID << 2) + 0x0006, ullData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT64((a_ulSectionID << 2) + 0x0007, llData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackFLOAT32((a_ulSectionID << 2) + 0x0008, fData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackFLOAT64((a_ulSectionID << 2) + 0x0009, eData, pucDataPtr + ucNULLBuffer * ulSectionLength);

    return ulSectionLength;
}

static UINT32 PV_TestSectionPack2(UINT32 a_ulSectionID, UINT8 * a_pucSectionDataPtr)
{
    UINT32 ulSectionLength = 0;
    UINT32 ulDataBufferIndex = 0;
    //UINT8 * pucDataBuffer = 0;
    UINT8 * pucDataPtr = a_pucSectionDataPtr;
    UINT8 ucNULLBuffer = (a_pucSectionDataPtr == 0) ? 0 : 1;

    UINT8 ucData = (2 << 3);
    INT8 cData = -(2 << 3);
    UINT16 uwData = (2 << 8) + (2 << 3);
    INT16 wData = -((2 << 8) + (2 << 3));
    UINT32 ulData = (2 << 16) + (2 << 8) + (2 << 3);
    INT32 lData = -((2 << 16) + (2 << 8) + (2 << 3));
    UINT64 ullData = ((UINT64)2 << 32) + (2 << 16) + (2 << 8) + (2 << 3);
    INT64 llData = -(((INT64)2 << 32) + (2 << 16) + (2 << 8) + (2 << 3));
    FLOAT32 fData = 2.f / 3.f;
    FLOAT64 eData = 2.0 / 3.0;

    ulSectionLength += alHEXDATA_PackUINT8((a_ulSectionID << 2) + 0x0000, ucData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT8((a_ulSectionID << 2) + 0x0001, cData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackUINT16((a_ulSectionID << 2) + 0x0002, uwData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT16((a_ulSectionID << 2) + 0x0003, wData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackUINT32((a_ulSectionID << 2) + 0x0004, ulData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT32((a_ulSectionID << 2) + 0x0005, lData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackUINT64((a_ulSectionID << 2) + 0x0006, ullData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackINT64((a_ulSectionID << 2) + 0x0007, llData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackFLOAT32((a_ulSectionID << 2) + 0x0008, fData, pucDataPtr + ucNULLBuffer * ulSectionLength);
    ulSectionLength += alHEXDATA_PackFLOAT64((a_ulSectionID << 2) + 0x0009, eData, pucDataPtr + ucNULLBuffer * ulSectionLength);

    return ulSectionLength;
}

static void PV_TestSectionUnPack1(UINT8 * a_pucSectionDataPtr, UINT32 a_ulSectionLength, FILE * a_ptFileOut)
{
    UINT8 * pucSectionPtr = a_pucSectionDataPtr;
    UINT8 * pucDataPtr = 0;
    UINT32 ulDataID;
    UINT32 ulDataLength;

    UINT8 ucData = (1 << 3);
    INT8 cData = -(1 << 3);
    UINT16 uwData = (1 << 8) + (1 << 3);
    INT16 wData = -((1 << 8) + (1 << 3));
    UINT32 ulData = (1 << 16) + (1 << 8) + (1 << 3);
    INT32 lData = -((1 << 16) + (1 << 8) + (1 << 3));
    UINT64 ullData = ((UINT64)1 << 32) + (1 << 16) + (1 << 8) + (1 << 3);
    INT64 llData = -(((INT64)1 << 32) + (1 << 16) + (1 << 8) + (1 << 3));
    FLOAT32 fData = 1.f / 3.f;
    FLOAT64 eData = 1.0 / 3.0;

    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT8: 0x%08X, %u, (%u)\n", ulDataID, alHEXDATA_UnpackUINT8(ulDataLength, pucDataPtr), ucData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT8 : 0x%08X, %d, (%d)\n", ulDataID, alHEXDATA_UnpackINT8(ulDataLength, pucDataPtr), cData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT16: 0x%08X, %u, (%u)\n", ulDataID, alHEXDATA_UnpackUINT16(ulDataLength, pucDataPtr), uwData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT16 : 0x%08X, %d, (%d)\n", ulDataID, alHEXDATA_UnpackINT16(ulDataLength, pucDataPtr), wData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT32: 0x%08X, %u, (%u)\n", ulDataID, alHEXDATA_UnpackUINT32(ulDataLength, pucDataPtr), ulData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT32 : 0x%08X, %d, (%d)\n", ulDataID, alHEXDATA_UnpackINT32(ulDataLength, pucDataPtr), lData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT64: 0x%08X, %I64u, (%I64u)\n", ulDataID, alHEXDATA_UnpackUINT64(ulDataLength, pucDataPtr), ullData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT64 : 0x%08X, %I64d, (%I64d)\n", ulDataID, alHEXDATA_UnpackINT64(ulDataLength, pucDataPtr), llData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack FLOAT32: 0x%08X, %f, (%f)\n", ulDataID, alHEXDATA_UnpackFLOAT32(ulDataLength, pucDataPtr), fData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack FLOAT64: 0x%08X, %e, (%e)\n", ulDataID, alHEXDATA_UnpackFLOAT64(ulDataLength, pucDataPtr), eData);

}

static void PV_TestSectionUnPack2(UINT8 * a_pucSectionDataPtr, UINT32 a_ulSectionLength, FILE * a_ptFileOut)
{
    UINT8 * pucSectionPtr = a_pucSectionDataPtr;
    UINT8 * pucDataPtr = 0;
    UINT32 ulDataID;
    UINT32 ulDataLength;

    UINT8 ucData = (2 << 3);
    INT8 cData = -(2 << 3);
    UINT16 uwData = (2 << 8) + (2 << 3);
    INT16 wData = -((2 << 8) + (2 << 3));
    UINT32 ulData = (2 << 16) + (2 << 8) + (2 << 3);
    INT32 lData = -((2 << 16) + (2 << 8) + (2 << 3));
    UINT64 ullData = ((UINT64)2 << 32) + (2 << 16) + (2 << 8) + (2 << 3);
    INT64 llData = -(((INT64)2 << 32) + (2 << 16) + (2 << 8) + (2 << 3));
    FLOAT32 fData = 2.f / 3.f;
    FLOAT64 eData = 2.0 / 3.0;

    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT8: 0x%08X, %u, (%u)\n", ulDataID, alHEXDATA_UnpackUINT8(ulDataLength, pucDataPtr), ucData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT8 : 0x%08X, %d, (%d)\n", ulDataID, alHEXDATA_UnpackINT8(ulDataLength, pucDataPtr), cData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT16: 0x%08X, %u, (%u)\n", ulDataID, alHEXDATA_UnpackUINT16(ulDataLength, pucDataPtr), uwData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT16 : 0x%08X, %d, (%d)\n", ulDataID, alHEXDATA_UnpackINT16(ulDataLength, pucDataPtr), wData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT32: 0x%08X, %u, (%u)\n", ulDataID, alHEXDATA_UnpackUINT32(ulDataLength, pucDataPtr), ulData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT32 : 0x%08X, %d, (%d)\n", ulDataID, alHEXDATA_UnpackINT32(ulDataLength, pucDataPtr), lData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack UINT64: 0x%08X, %I64u, (%I64u)\n", ulDataID, alHEXDATA_UnpackUINT64(ulDataLength, pucDataPtr), ullData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack INT64 : 0x%08X, %I64d, (%I64d)\n", ulDataID, alHEXDATA_UnpackINT64(ulDataLength, pucDataPtr), llData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack FLOAT32: 0x%08X, %f, (%f)\n", ulDataID, alHEXDATA_UnpackFLOAT32(ulDataLength, pucDataPtr), fData);
    pucSectionPtr = alHEXDATA_DataUnpack(pucSectionPtr, &ulDataID, &ulDataLength, &pucDataPtr);
    fprintf(a_ptFileOut, "Unpack FLOAT64: 0x%08X, %e, (%e)\n", ulDataID, alHEXDATA_UnpackFLOAT64(ulDataLength, pucDataPtr), eData);

}

/** \brief Test all pack functions. This function will pack all data type and write to a hex file, "alHexData_test.hex". */
static void alHEXDATA_TestPack()
{
    UINT32 ulConfigFileLength = 0;
    UINT32 ulSectionLength1, ulSectionLength2;
    UINT8 * pucConfigFileBuffer = 0;
    UINT8 * pucConfigFilePtr = 0;

    // Count Section Length
    ulConfigFileLength = 0;
    ulSectionLength1 = PV_TestSectionPack1(0x0001, NULL);
    ulConfigFileLength += ulSectionLength1 + 8 /*Section ID + Section Length*/;
    ulSectionLength2 = PV_TestSectionPack2(0x0002, NULL);
    ulConfigFileLength += ulSectionLength2 + 8 /*Section ID + Section Length*/;

    // allocate Config File Buffer
    pucConfigFileBuffer = (UINT8*)malloc(ulConfigFileLength);

    // Export to Config File Buffer
    pucConfigFilePtr = alHEXDATA_SectionInitial(pucConfigFileBuffer, 0x0001, ulSectionLength1);
    pucConfigFilePtr += PV_TestSectionPack1(0x0001, pucConfigFilePtr);
    pucConfigFilePtr = alHEXDATA_SectionInitial(pucConfigFilePtr, 0x0002, ulSectionLength2);
    pucConfigFilePtr += PV_TestSectionPack2(0x0002, pucConfigFilePtr);

    assert((pucConfigFilePtr - pucConfigFileBuffer) == (INT32)ulConfigFileLength);

    FILE * ptFile = NULL;
    ptFile = fopen("alHexData_test.hex", "wb");
    fwrite(pucConfigFileBuffer, 1, ulConfigFileLength, ptFile);
    fclose(ptFile);

    free(pucConfigFileBuffer);
}

/** \brief Test all unpack functions. This function will unpack all data type from the hex file, "alHexData_test.hex", and output to a txt file. */
static void alHEXDATA_TestUnpack()
{
    FILE * ptFile = NULL;
    FILE * ptFileOut = NULL;
    UINT8 * pucHexFileBuffer = 0;
    UINT32 ulHexFileBufferLength = 0;
    UINT32 ulHexFileBufferIndex = 0;
    UINT8 * pucSectionDataPtr = 0;
    UINT32 ulSectionLength = 0;
    UINT8 * pucDataPtr = 0;

    struct _stat st;
    if (_stat("alHexData_test.hex", &st) != 0)
    {
        printf("Hex file is not existed.");
        return;
    }
    ulHexFileBufferLength = st.st_size;
    pucHexFileBuffer = (UINT8*)malloc(ulHexFileBufferLength);
    ptFile = fopen("alHexData_test.hex", "rb");
    fread(pucHexFileBuffer, 1, ulHexFileBufferLength, ptFile);
    fclose(ptFile);

    ptFileOut = fopen("alHexData_test.txt", "w");

    pucSectionDataPtr = alHEXDATA_SectionSeek(pucHexFileBuffer, ulHexFileBufferLength, 0x0002, &ulSectionLength);
    fprintf(ptFileOut, "Section ID: 0x%X\n", 0x0002);
    PV_TestSectionUnPack2(pucSectionDataPtr, ulSectionLength, ptFileOut);
    fprintf(ptFileOut, "Section ID: 0x%X\n", 0x0001);
    pucSectionDataPtr = alHEXDATA_SectionSeek(pucHexFileBuffer, ulHexFileBufferLength, 0x0001, &ulSectionLength);
    PV_TestSectionUnPack1(pucSectionDataPtr, ulSectionLength, ptFileOut);

    fclose(ptFileOut);

    free(pucHexFileBuffer);
}