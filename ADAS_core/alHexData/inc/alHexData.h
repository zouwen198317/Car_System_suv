
#include "mtype.h"

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif


    /**
    *   \defgroup alHEXDATA alHexData
    *   Provide functions to pack & unpack a Hex data package and a Hex data section.
    *   One data section includes 4 bytes "Data ID", 4 bytes "Data Length", and the following data package with the length bytes (the length must align to 4).
    *   When users have a Hex file, he should call alHEXDATA_DataUnpack in a for/while loop to unpack all data sections in the file untill the returned pointer exceeds buffer range.
    *   @{
    */

    /** \brief Define the size to store the data ID. (in bytes) */
    #define     BYTE_OF_DATA_ID      4
    /** \brief Define the size to store the data length. (in bytes) */
    #define     BYTE_OF_LENGTH       4
    /** \brief Define the size for one data item. (in bytes) It means the minimum size for one data item needs 4 bytes to store even for UINT8,INT8, UINT16, and INT16 items. */
    #define     BYTE_OF_DATA_ITEM    4

    /**
    *   \brief Input a config file buffer and seek the specified section ID. This function will find the specified section id and section length first.
    *          And then give the start pointer of the section data in the buffer.
    *   \param a_pucConfigFileBuf [IN] The config file buffer.
    *   \param a_ulConfigFileLength [IN] Length of the config file buffer, counted by bytes.
    *   \param a_ulSectionID [IN] The specified section ID to seek.
    *   \param a_pulSectionLength [OUT] Data length of the specified section ID. This length is counted by bytes.
    *   \return The start pointer of the specified section data. Return NULL if the section ID is not exist.
    *   \see alHEXDATA_SectionInitial
    */
    UINT8 * alHEXDATA_SectionSeek(UINT8 * a_pucConfigFileBuf, UINT32 a_ulConfigFileLength, UINT32 a_ulSectionID, UINT32 * a_pulSectionLength);

    /**
    *   \brief To initialize a section in the config file buffer to store section data. The section length should be counted before this call.
    *   \param a_pucConfigFileBuf [IN] The start pointer of config file buffer to store the current section.
    *   \param a_pulSectionID [IN] Data ID to be packed.
    *   \param a_pulSectionLength [IN] Buffer length of a_pucDataBuf. This length is counted by bytes.
    *   \see alHEXDATA_SectionSeek
    */
    UINT8* alHEXDATA_SectionInitial(UINT8 * a_pucConfigFileBuf, UINT32 a_pulSectionID, UINT32 a_pulSectionLength);

    /** 
    *   \brief Perform data unpack. This function will unpack data id and data length first. 
    *          And then give the start pointer of the data in the buffer. 
    *          If a_pucDataBuf is equal to 0, only data id and data length is unpacked.
    *   \param a_pucPackedDataBuf [IN] Packed data pointer for input.
    *   \param a_pulDataID [OUT] Unpacked data ID.
    *   \param a_pulDataLength [OUT] Required buffer length of a_pucDataBuf. This length is counted by bytes.
    *   \param a_pucDataBuf [OUT] The pointer of the data.
    *   \return The start postion of the next section.
    *   \see alHEXDATA_DataPack
    */
    UINT8 * alHEXDATA_DataUnpack(UINT8 * a_pucPackedDataBuf, UINT32 * a_pulDataID, UINT32 * a_pulDataLength, UINT8 ** a_pucDataBuf);

    /** 
    *   \brief Perform data pack. This function will pack data id and data length first. 
    *          And then pack data into section buffer. 
    *          If a_pucPackedDataBuf is equal to 0, only required data length of a_pucPackedDataBuf is calculated.
    *   \param a_ulDataID [IN] Data ID to be packed.
    *   \param a_ulDataLength [IN] Buffer length of a_pucDataBuf. This length is counted by bytes.
    *   \param a_pucDataBuf [IN] Data to be packed.
    *   \param a_pucPackedDataBuf [OUT] Section data buffer for output.
    *   \return The required buffer length of a_pucPackedDataBuf. This length is counted by bytes.
    *   \see alHEXDATA_DataUnpack
    */
    UINT32 alHEXDATA_DataPack(UINT32 a_ulDataID, UINT32 a_ulDataLength, UINT8 * a_pucDataBuf, UINT8 * a_pucSectionBuf);

    /** 
    *   \brief Unpack data package to UINT8 type. a_pucDataBuf includes the data buffer without data id. 
    *          DataUnpack_UINT8 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID. Should be 4 bytes.
    *   \return The unpaced value with UINT8 type.
    *   \see alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32, alHEXDATA_UnpackFLOAT64
    */ 
    UINT8 alHEXDATA_UnpackUINT8(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to INT8 type. a_pucDataBuf includes the data buffer without data id. 
    *          alHEXDATA_UnpackINT8 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with INT8 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32, alHEXDATA_UnpackFLOAT64
    */ 
    INT8 alHEXDATA_UnpackINT8(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to UINT16 type. a_pucDataBuf includes the data buffer without data id. 
    *          alHEXDATA_UnpackUINT16 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with UINT16 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32, alHEXDATA_UnpackFLOAT64
    */ 
    UINT16 alHEXDATA_UnpackUINT16(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to INT16 type. a_pucDataBuf includes the data buffer without data id. 
    *          alHEXDATA_UnpackINT16 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with INT16 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32, alHEXDATA_UnpackFLOAT64
    */ 
    INT16 alHEXDATA_UnpackINT16(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to UINT32 type. a_pucDataBuf includes the data buffer without data id. 
    *          a_ulDataIndex indicate which index of data is going to be unpacked. 
    *          Note that each index indicate four bytes in the buffer. 
    *          alHEXDATA_UnpackUINT32 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with UINT32 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32, alHEXDATA_UnpackFLOAT64
    */ 
    UINT32 alHEXDATA_UnpackUINT32(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to INT32 type. a_pucDataBuf includes the data buffer without data id. 
    *          a_ulDataIndex indicate which index of data is going to be unpacked. 
    *          Note that each index indicate four bytes in the buffer. 
    *          alHEXDATA_UnpackINT32 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with INT32 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackFLOAT32, alHEXDATA_UnpackFLOAT64
    */ 
    INT32 alHEXDATA_UnpackINT32(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to FLOAT32 type. a_pucDataBuf includes the data buffer without data id. 
    *          a_ulDataIndex indicate which index of data is going to be unpacked. 
    *          Note that each index indicate four bytes in the buffer. 
    *          alHEXDATA_UnpackFLOAT32 will start to unpack data from a_pucDataBuf and unpack total 4 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with FLOAT32 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT64
    */ 
    FLOAT32 alHEXDATA_UnpackFLOAT32(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /** 
    *   \brief Unpack data package to FLOAT64 type. a_pucDataBuf includes the data buffer without data id. 
    *          alHEXDATA_UnpackFLOAT64 will start to unpack data from a_pucDataBuf and unpack total 8 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with FLOAT64 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32
    */ 
    FLOAT64 alHEXDATA_UnpackFLOAT64(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /**
    *   \brief Unpack data package to UINT64 type. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_UnpackUINT64 will start to unpack data from a_pucDataBuf and unpack total 8 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with UINT64 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32
    */
    UINT64 alHEXDATA_UnpackUINT64(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /**
    *   \brief Unpack data package to INT64 type. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_UnpackINT64 will start to unpack data from a_pucDataBuf and unpack total 8 bytes in the data buffer.
    *   \param a_ulDataLength [IN] Indicate data length of a_pucDataBuf, in bytes.
    *   \param a_pucDataBuf [IN] The data buffer of specific data ID.
    *   \return The unpaced value with INT64 type.
    *   \see DataUnpack_UINT8, alHEXDATA_UnpackINT8, alHEXDATA_UnpackUINT16, alHEXDATA_UnpackINT16, alHEXDATA_UnpackUINT32, alHEXDATA_UnpackINT32, alHEXDATA_UnpackFLOAT32
    */
    INT64 alHEXDATA_UnpackINT64(UINT32 a_ulDataLength, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack UINT8 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackUINT8 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_ucData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackUINT8(UINT32 a_ulDataID, UINT8 a_ucData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack INT8 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackINT8 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_cData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackINT8(UINT32 a_ulDataID, INT8 a_cData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack UINT16 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackUINT16 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_uwData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackUINT16(UINT32 a_ulDataID, UINT16 a_uwData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack INT16 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackINT16 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_wData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackINT16(UINT32 a_ulDataID, INT16 a_wData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack UINT32 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackUINT32 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_ulData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackUINT32(UINT32 a_ulDataID, UINT32 a_ulData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack INT32 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackINT32 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_lData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackINT32(UINT32 a_ulDataID, INT32 a_lData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack UINT64 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackUINT64 will start to pack data at a_pucDataBuf and pack total 8 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_ullData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackUINT64(UINT32 a_ulDataID, UINT64 a_ullData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack INT64 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackINT64 will start to pack data at a_pucDataBuf and pack total 8 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_llData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackINT64(UINT32 a_ulDataID, INT64 a_llData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack FLOAT32 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackFLOAT32 will start to pack data at a_pucDataBuf and pack total 4 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_fData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackFLOAT32(UINT32 a_ulDataID, FLOAT32 a_fData, UINT8 * a_pucDataBuf);

    /**
    *   \brief Pack FLOAT64 type data into the package. a_pucDataBuf includes the data buffer without data id.
    *          alHEXDATA_PackFLOAT32 will start to pack data at a_pucDataBuf and pack total 8 bytes in the data buffer.
    *   \param a_ulDataID [IN] Indicate the data ID.
    *   \param a_eData [IN] The data value to be packed.
    *   \param a_pucDataBuf [OUT] The buffer to pack data.
    *   \return The packed length in bytes.
    *   \see alHEXDATA_PackUINT8, alHEXDATA_PackINT8, alHEXDATA_PackUINT16, alHEXDATA_PackINT16, alHEXDATA_PackUINT32, alHEXDATA_PackINT32, alHEXDATA_PackFLOAT32, alHEXDATA_PackFLOAT64
    */
    UINT32 alHEXDATA_PackFLOAT64(UINT32 a_ulDataID, FLOAT64 a_eData, UINT8 * a_pucDataBuf);

    /**
    *   @}
    */

#ifdef __cplusplus
}
#endif
