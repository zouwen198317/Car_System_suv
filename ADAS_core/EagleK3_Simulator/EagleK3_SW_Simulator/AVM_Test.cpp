
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <stdio.h>
#include <locale.h> // add by ancre for char to wchar_t


#include "alLUT_v2.h"
#include "basedef.h"
#include "EagleK3_SimulateMain.h"
#include "AVM3DK.h"




#if alEAGLEK3_SIMULATOR_OPENCV_TEST == 1
// #include <cv_libimport.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#define TEST_AVM3D_MORPHING 0

static void Test_GetYChannel(INT32 a_lWidth, INT32 a_lHeight, UINT8 *a_pucSrcBuffer, UINT8 *a_pucYBuffer);

static void Test_GetYChannel(
    INT32 a_lWidth,
    INT32 a_lHeight,
    UINT8 *a_pucSrcBuffer,
    UINT8 *a_pucYBuffer
    )
{
    INT32 i = 0, j = 0;

    for (i = 0; i < a_lWidth*a_lHeight; i++)
    {
        a_pucYBuffer[i] = a_pucSrcBuffer[i << 1];
    }
}


BOOL Test_ImportOtherHexFiles(const wchar_t * a_pwcHexFilePath, UINT8 ** a_ppucBuffer, UINT32 * a_plBufferLength)
{
    // Import Hex
    struct _stat st;
    if (_wstat(a_pwcHexFilePath, &st) != 0)
    {
        wprintf(L"Can not load hex file: \"%s\"\n", a_pwcHexFilePath);
        return FALSE;
    }

    (*a_ppucBuffer) = new UINT8[st.st_size];

    std::ifstream ifile(a_pwcHexFilePath, std::ios::binary);
    ifile.read((char*)(*a_ppucBuffer), st.st_size);
    ifile.close();

    *a_plBufferLength = st.st_size;

    return TRUE;
}

void Test_Memory2FileW(wchar_t * a_pwcFileName, UINT8 * a_pucBuf, INT32 a_lSize)
{
#define MAX_WRITE   65536

    FILE *ptFile;
    size_t ulCount = (a_lSize / MAX_WRITE) + 1;
    size_t ulIndex = 0;

    _wfopen_s(&ptFile, a_pwcFileName, L"wb");
    if (NULL == ptFile) {
        wprintf_s(L"can not create file %s.\n", a_pwcFileName);
        return;
    }

    // If the data array is too large, the fwrite function will be failed.
    // The writing limitation of fwrite is set to MAX_WRITE.
    for (ulIndex = 0; ulIndex < ulCount; ulIndex++)
    {
        if (a_lSize < MAX_WRITE)
        {
            fwrite(a_pucBuf, sizeof(unsigned char), a_lSize, ptFile);
        }
        else
        {
            fwrite(a_pucBuf, sizeof(unsigned char), MAX_WRITE, ptFile);
            a_lSize -= MAX_WRITE;
            a_pucBuf += MAX_WRITE;
        }
    }

    fclose(ptFile);
}

void Test_alAVM2D_Generate(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    )
{
#if 1 // pc LUT
    std::wstring salAVM2DLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_set.hex");
    std::wstring salAVM2DLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_data.hex");
#else FW LUT
    std::wstring salAVM2DLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_set_FW.hex");
    std::wstring salAVM2DLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_data_FW.hex");
#endif
    std::wstring sOutputImgeFile;
    UINT8 * pucBuffer = NULL;
    UINT8 * pucBuffer2 = NULL;
    UINT8 * pucDestBuffer = NULL;
    UINT32 ulBufferLength = 0, ulBufferLength2 = 0;
    alLUT_v2_Def talAVM2D_LUT;

	FILE *Ptr = NULL;
	
    /*Ptr = fopen("test.raw","wb");
	fwrite(a_apucSrcImage[2], ulSrcImgWidth * ulSrcImgHeight * 2, 1, Ptr);
	fclose(Ptr);*/
 
	// Import AVM 2D (BV) LUT Set
    if (Test_ImportOtherHexFiles(salAVM2DLUTSetFilePath.c_str(), &pucBuffer, &ulBufferLength))
    {
        if (!Test_ImportOtherHexFiles(salAVM2DLUTDataFilePath.c_str(), &pucBuffer2, &ulBufferLength2)) assert(0);

        memcpy(&talAVM2D_LUT, pucBuffer, sizeof(alLUT_v2_Def));

        talAVM2D_LUT.pullTable = (UINT64*)malloc(talAVM2D_LUT.ulLUTDataSize);
        memcpy(talAVM2D_LUT.pullTable, pucBuffer2, talAVM2D_LUT.ulLUTDataSize);

		pucDestBuffer = new UINT8[talAVM2D_LUT.atSrcImageSize->lX  * talAVM2D_LUT.atSrcImageSize->lY * 2];
		printf("BufferX:%dBufferY:%d\n", talAVM2D_LUT.tDestImageBufferSize.lX, talAVM2D_LUT.tDestImageBufferSize.lY);

        // Gen alAVM2D (Seamless BV) Image
		memset(pucDestBuffer, 0, talAVM2D_LUT.atSrcImageSize->lX * talAVM2D_LUT.atSrcImageSize->lY * 2);
        alLUT_v2_ProcessFullLU(&talAVM2D_LUT, a_apucSrcImage, pucDestBuffer);
        
        sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(L"alAVM2D_YUV_ByHex.raw");
        std::ofstream ofile_alAVM2D(sOutputImgeFile.c_str(), std::ios::binary);
		ofile_alAVM2D.write((char*)pucDestBuffer, talAVM2D_LUT.atSrcImageSize->lX * talAVM2D_LUT.atSrcImageSize->lY * 2);
		ofile_alAVM2D.close(); 


        free(talAVM2D_LUT.pullTable);

        delete[] pucBuffer;
        delete[] pucBuffer2;
        delete[] pucDestBuffer;
    }
}


void Test_alAVM2D_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;
    alLUT_v2_Def talAVM2D_LUT;
    alPartLUT_v2_Def  *ptalAVM2D_LUT_PART;

    UINT8 * apucSrcImage[4];


    INT32 alSFPX[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 alSFPY[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };


    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL];
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL];
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, *pucEagleK3WorkingBuffer = NULL;
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0, ulAVM2D_LUT_Size = 0;

    EAGLEK3_Cfg tEAGLEK3_Cfg;
    EAGLEK3_FieldData tEAGLEK3_FeildData;
    EAGLEK3_Param tEAGLEK3_Params;
    EAGLEK3_Data tEAGLEK3_Data;
    alAVM2D_Cfg tAVM2D_Cfg;
    alAVM2D_Params tAVM2D_Params;
    alCOMMONK_CommonCfg tCommonCfg = { 0 };

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Set_Bird-View_Fisheye Model (Test_SET_BV_FM will malloc for apucFMBuffer >> need to free)
    Test_SET_BV_FM(awcConfigFilePath, atFM_BV, aulFMBufferSize, apucFMBuffer, atFM_v2_Model);

    // Test DeFishEye Image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, 1.0, atFM_v2_Model);

    

#if 1
    {   // GEN alAVM2D LUT
        // set Common Cfg
        COMMONK_LoadDefault(&tCommonCfg);
        COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

        // Init LUT buffer
        alAVM2D_InitializeBuffer(&talAVM2D_LUT);

        // Load Default 
        alAVM2D_LoadDefault(&tAVM2D_Cfg);

        // Load conifg data from INI file
        alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);
		
		//////////////////////////////////ALLOC FM BUFFER//////////////////////////////////
		std::wstring sImageLeft = std::wstring(a_pwcSrcImageFolder).append(L"Source_2.raw");
		std::wstring sImageRight = std::wstring(a_pwcSrcImageFolder).append(L"Source_3.raw");
		std::wstring sImageFront = std::wstring(a_pwcSrcImageFolder).append(L"Source_0.raw");
		std::wstring sImageRear = std::wstring(a_pwcSrcImageFolder).append(L"Source_1.raw");
		std::ifstream ifile;
		apucSrcImage[0] = new UINT8[atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2];
		apucSrcImage[1] = new UINT8[atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2];
		apucSrcImage[2] = new UINT8[atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2];
		apucSrcImage[3] = new UINT8[atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2];
		ifile.open(sImageFront.c_str(), std::ios::binary);
		ifile.read((char*)apucSrcImage[0], atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2);
		ifile.close();
		ifile.open(sImageRear.c_str(), std::ios::binary);
		ifile.read((char*)apucSrcImage[1], atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2);
		ifile.close();
		ifile.open(sImageLeft.c_str(), std::ios::binary);
		ifile.read((char*)apucSrcImage[2], atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2);
		ifile.close();
		ifile.open(sImageRight.c_str(), std::ios::binary);
		ifile.read((char*)apucSrcImage[3], atFM_v2_Model->uwSrcWidth * atFM_v2_Model->uwSrcHeight * 2);
		ifile.close();
		//////////////////////////////////INITIAL BY CFG DATA////////////////////////////////////////////////////


        // Init By Cfg
        alAVM2D_InitialByConfigData(&tAVM2D_Cfg, &tCommonCfg, &tAVM2D_Params);

        // Qurry LUT data Size
        ulAVM2D_LUT_Size = alAVM2D_QurryLUTSize(&tAVM2D_Cfg, &tAVM2D_Params);

        // malloc LUT memory and assign pointer
        talAVM2D_LUT.pullTable = (UINT64*)malloc(ulAVM2D_LUT_Size);

        // set AVM2D Cfg, params
        alAVM2D_LoadDefault(&tAVM2D_Cfg);
        alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);
        alAVM2D_InitialByConfigData(&tAVM2D_Cfg, &tCommonCfg, &tAVM2D_Params);

        // Initialize for EagleK3 (Test_SET_EAGLEK3_PARAMS will malloc working buffer >> need to free)
        Test_SET_EAGLEK3_PARAMS(
            a_pwcEagleKWorkingFolder, a_pwcConfigFileName,
            atFM_v2_Model, &tCommonCfg, &tAVM2D_Cfg, &tAVM2D_Params,
            &tEAGLEK3_Cfg, &tEAGLEK3_Params,
            &tEAGLEK3_Data, &tEAGLEK3_FeildData,
            &ulEagleK3BufferSize, &pucEagleK3WorkingBuffer
            );

        // TEST ManualK
        Test_ManualK(
            apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName,
            &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data
            );

        // Gen LUT
#if 1
		FLOAT64 eUndistX = 0, eUndistY = 0;
		COMMONK_PerformCoordinatesTransform(
			tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix[0],
			286, 56,
			&eUndistX, &eUndistY
		);

        alAVM2D_GenerateLUT2DBirdView(
            &tAVM2D_Cfg,
            &tAVM2D_Params,
            atFM_v2_Model,
            tEAGLEK3_Data.atCalibrationParams[0].aeHomographyMatrix,
            tEAGLEK3_Data.atCalibrationParams[1].aeHomographyMatrix,
            tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix,
            tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix,
            &talAVM2D_LUT
            );
#endif
    
#if 1   // Save M33
        FILE *pFileM33 = NULL;
        pFileM33 = fopen("M33_L.hex", "wb");
        fwrite(&tEAGLEK3_Data.atCalibrationParams[0].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[0].aeHomographyMatrix), 1, pFileM33);
        fclose(pFileM33);

        pFileM33 = fopen("M33_R.hex", "wb");
        fwrite(&tEAGLEK3_Data.atCalibrationParams[1].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[1].aeHomographyMatrix), 1, pFileM33);
        fclose(pFileM33);

        pFileM33 = fopen("M33_F.hex", "wb");
        fwrite(&tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[2].aeHomographyMatrix), 1, pFileM33);
        fclose(pFileM33);

        pFileM33 = fopen("M33_B.hex", "wb");
        fwrite(&tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix, sizeof(tEAGLEK3_Data.atCalibrationParams[3].aeHomographyMatrix), 1, pFileM33);
        fclose(pFileM33);

        pFileM33 = fopen("AVM2D_Cfg.hex", "wb");
        fwrite(&tAVM2D_Cfg, sizeof(alAVM2D_Cfg), 1, pFileM33);
        fclose(pFileM33);

        pFileM33 = fopen("COMMON_Cfg.hex", "wb");
        fwrite(&tCommonCfg, sizeof(alCOMMONK_CommonCfg), 1, pFileM33);
        fclose(pFileM33);
#endif


#if 1   // Save LUT
        wchar_t awcFilePath[MAX_PATH];
        UINT8 *pucData = NULL;
        INT32 lSize = 0;
        if (tAVM2D_Cfg.ucFunctionEnabled == 1)
        {
            // alAVM2D LUT File (Set)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_alAVM2DLUT_set.hex");
            lSize = sizeof(alLUT_v2_Def);
            pucData = (UINT8*)(&talAVM2D_LUT);
            Test_Memory2FileW(awcFilePath, pucData, lSize);

            // alAVM2D LUT File (Data)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcscat_s(awcFilePath, MAX_PATH, L"EagleK_alAVM2DLUT_data.hex");
            lSize = talAVM2D_LUT.ulLUTDataSize;
            pucData = (UINT8*)(talAVM2D_LUT.pullTable);
            Test_Memory2FileW(awcFilePath, pucData, lSize);
        }
#endif
        // Free LUT buffer
        alAVM2D_FreeBuffer(&talAVM2D_LUT, &ptalAVM2D_LUT_PART);
    }
#endif

#if 1 
    Test_alAVM2D_Generate(
        a_pwcEagleKWorkingFolder,
        a_pwcConfigFileName,
        a_pwcSrcImageFolder,
        a_pwcOutImageFolder,
        apucSrcImage
    );
#endif

    // free Eaglek3 Buffer
    free(pucEagleK3WorkingBuffer);

    // free FM Buffer
    free(apucFMBuffer[EAGLEK3_BV_LEFT]);
    free(apucFMBuffer[EAGLEK3_BV_RIGHT]);
    free(apucFMBuffer[EAGLEK3_BV_FRONT]);
    free(apucFMBuffer[EAGLEK3_BV_BACK]);

	delete[] apucSrcImage[0];
	delete[] apucSrcImage[1];
	delete[] apucSrcImage[2];
	delete[] apucSrcImage[3];

}

void Test_alAVM3D_By_LoadINICfg(
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    wchar_t * a_pwcFPFileName
    )
{
    std::wstring sOutputImgeFile;
    alLUT_v2_Def atalAVM3D_LUT[AVM3D_MAX_VIEW_ANGLE_CNT];
    alPartLUT_v2_Def  *aptalAVM3D_LUT_PART[AVM3D_MAX_VIEW_ANGLE_CNT] = {0};

	//UINT8 * pucSrcBufferFront = new UINT8[IMAGE_WIDTH*IMAGE_HEIGHT * 2];


    UINT8 * apucSrcImage[4], ucViewIndex = 0;
    INT32 alSFPX[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 alSFPY[EAGLEK3_NUM_BV_CHANNEL][EAGLEK3_CAMERA_FP_NUM] = { 0 };
    INT32 lMorphingIndex = 0, lSrcIndex = 0, lDestIndex = 0, lMorphingFlag = 0, lMorphinfType = 0, lMorphingFrame = 0;



    alFM_v2_1_ModelCfg atFM_BV[EAGLEK3_NUM_BV_CHANNEL] = {0};
    alFM_v2_1_Model atFM_v2_Model[EAGLEK3_NUM_BV_CHANNEL] = {0};
    alFM_v2_1_ModelCfg atFM_Cfg_AVM3D[AVM3D_MAX_VIEW_ANGLE_CNT] = {0};
    alFM_v2_1_Model atFM_Model_AVM3D[AVM3D_MAX_VIEW_ANGLE_CNT] = {0};
    UINT32 aulAVM3D_VC_FMBufferSize[AVM3D_MAX_VIEW_ANGLE_CNT] = { 0 };
    wchar_t awcConfigFilePath[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_ManualK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_AutoK[MAX_PATH] = { 0 };
    wchar_t awcFeildDataINIFilePath_FineTune[MAX_PATH] = { 0 };
    UINT8 *apucAVM3D_VC_FMBuffer[AVM3D_MAX_VIEW_ANGLE_CNT] = { 0 }, *pucEagleK3WorkingBuffer = NULL;
    UINT8 *apucFMBuffer[EAGLEK3_NUM_BV_CHANNEL] = { 0 };
    UINT32 aulFMBufferSize[EAGLEK3_NUM_BV_CHANNEL] = { 0 }, ulEagleK3BufferSize = 0;

    EAGLEK3_Cfg tEAGLEK3_Cfg;
    EAGLEK3_FieldData tEAGLEK3_FeildData;
    EAGLEK3_Param tEAGLEK3_Params;
    EAGLEK3_Data tEAGLEK3_Data;
    alCOMMONK_CommonCfg tCommonCfg = { 0 };
    alAVM2D_Cfg tAVM2D_Cfg = { 0 };
    alAVM2D_Params tAVM2D_Params = { 0 };

    // GEN alAVM3D LUT
    alAVM3D_Cfg tAVM3D_Cfg;
    alAVM3D_MorphingCfgStruct tMorphingCfg;
    alAVM3D_MorphingStruct tMorphingInfo = {0};
    alAVM3D_Params talAVM3DParam;

    wcscpy_s(awcConfigFilePath, MAX_PATH, a_pwcEagleKWorkingFolder);
    wcscat_s(awcConfigFilePath, MAX_PATH, a_pwcConfigFileName);

    // 檢查檔案是否存在
    struct _stat64i32 tFileStat;
    assert(_wstat(awcConfigFilePath, &tFileStat) == 0);

    // Load Default
    EAGLEK3_LoadFM_BV_CfgByDefault(EAGLEK3_NUM_BV_CHANNEL, atFM_BV);

    // Load conifg data from INI file
    EAGLEK3_LoadFM_BV_CfgByINI(awcConfigFilePath, EAGLEK3_NUM_BV_CHANNEL, atFM_BV);
	printf("Width:%d Height:%d", atFM_BV->ulImageWidth ,atFM_BV->ulImageHeight);

 
	// Query FM BV Working Buffer Size For Each FM
    EAGLEK3_QueryFM_BV_WorkingBufferSizeForEachFM(atFM_BV, aulFMBufferSize);

    // alloc FM  Buffer
    apucFMBuffer[EAGLEK3_BV_LEFT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_LEFT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_RIGHT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_RIGHT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_FRONT] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_FRONT] * sizeof(UINT8));
    apucFMBuffer[EAGLEK3_BV_BACK] = (UINT8*)malloc(aulFMBufferSize[EAGLEK3_BV_BACK] * sizeof(UINT8));


	//////////////////////////////////Edit////////////////////////////////////////////////////
	std::wstring sImageLeft = std::wstring(a_pwcSrcImageFolder).append(L"Source_2.raw");
	std::wstring sImageRight = std::wstring(a_pwcSrcImageFolder).append(L"Source_3.raw");
	std::wstring sImageFront = std::wstring(a_pwcSrcImageFolder).append(L"Source_0.raw");
	std::wstring sImageRear = std::wstring(a_pwcSrcImageFolder).append(L"Source_1.raw");
	std::ifstream ifile;
	apucSrcImage[0] = new UINT8[atFM_BV->ulImageWidth*atFM_BV->ulImageHeight * 2];
	apucSrcImage[1] = new UINT8[atFM_BV->ulImageWidth*atFM_BV->ulImageHeight * 2];
	apucSrcImage[2] = new UINT8[atFM_BV->ulImageWidth*atFM_BV->ulImageHeight * 2];
	apucSrcImage[3] = new UINT8[atFM_BV->ulImageWidth*atFM_BV->ulImageHeight * 2];

	ifile.open(sImageFront.c_str(), std::ios::binary);
	ifile.read((char*)apucSrcImage[0], atFM_BV->ulImageWidth* atFM_BV->ulImageHeight * 2);
	ifile.close();
	ifile.open(sImageRear.c_str(), std::ios::binary);
	ifile.read((char*)apucSrcImage[1], atFM_BV->ulImageWidth* atFM_BV->ulImageHeight * 2);
	ifile.close();
	ifile.open(sImageLeft.c_str(), std::ios::binary);
	ifile.read((char*)apucSrcImage[2], atFM_BV->ulImageWidth* atFM_BV->ulImageHeight * 2);
	ifile.close();
	ifile.open(sImageRight.c_str(), std::ios::binary);
	ifile.read((char*)apucSrcImage[3], atFM_BV->ulImageWidth* atFM_BV->ulImageHeight * 2);
	ifile.close();
	//////////////////////////////////Edit////////////////////////////////////////////////////
	
    // Initial By Cfg Data
    EAGLEK3_InitialBV_FM_ByCfg(atFM_BV, atFM_v2_Model, apucFMBuffer);

    // Test DeFishEye Image
    TEST_ExportUndistortedImage(a_pwcSrcImageFolder, a_pwcOutImageFolder, 1.0, atFM_v2_Model);

    // set Common Cfg
    COMMONK_LoadDefault(&tCommonCfg);
    COMMONK_CfgImportByINI(awcConfigFilePath, &tCommonCfg);

    // set AVM2D Cfg, params
    alAVM2D_LoadDefault(&tAVM2D_Cfg);
    alAVM2D_CfgImportByINIFile(awcConfigFilePath, &tAVM2D_Cfg);
    alAVM2D_InitialByConfigData(&tAVM2D_Cfg, &tCommonCfg, &tAVM2D_Params);

    // Initialize for EagleK3 (Test_SET_EAGLEK3_PARAMS will malloc working buffer >> need to free)
    Test_SET_EAGLEK3_PARAMS(
        a_pwcEagleKWorkingFolder, a_pwcConfigFileName,
        atFM_v2_Model, &tCommonCfg, &tAVM2D_Cfg, &tAVM2D_Params,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params,
        &tEAGLEK3_Data, &tEAGLEK3_FeildData,
        &ulEagleK3BufferSize, &pucEagleK3WorkingBuffer
        );


    //// TEST ManualK ////
    Test_ManualK(
        apucSrcImage, a_pwcOutImageFolder, a_pwcFPFileName,
        &tEAGLEK3_Cfg, &tEAGLEK3_Params, &tEAGLEK3_Data
    );

    // Gennerate RT Matrix
    EAGLEK3_Gen_RT_Matrix(&tEAGLEK3_Cfg, &tAVM2D_Cfg, &tAVM2D_Params, &tEAGLEK3_Params, &tEAGLEK3_Data);


#if 1
    {   
        // Init LUT buffer
        for (ucViewIndex = 0; ucViewIndex < AVM3D_MAX_VIEW_ANGLE_CNT; ucViewIndex++)
        {
            AVM3D_InitializeBuffer(&atalAVM3D_LUT[ucViewIndex], &aptalAVM3D_LUT_PART[ucViewIndex]);
        }
        
        // Load Default
        AVM3D_LoadDefault(&tAVM3D_Cfg, &tMorphingCfg);

        // Load conifg data from INI file
        alAVM3D_CfgImportByINIFile(awcConfigFilePath, &tAVM3D_Cfg);
#if TEST_AVM3D_MORPHING
        alAVM3D_MORPHING_CfgImportByINI(awcConfigFilePath, &tMorphingCfg);
#endif

        // set VC FM of each view
        for (ucViewIndex = 0; ucViewIndex < AVM3D_MAX_VIEW_ANGLE_CNT; ucViewIndex++)
        {
            // set Virtual fish eye model by AVM3D's Cfg
            alFM_v2_1_LoadDefaultModedCfg(
                tAVM3D_Cfg.atViewCfg[ucViewIndex].ucVCFisheyeModel,
                &atFM_Cfg_AVM3D[ucViewIndex]
                );

            // calculate FM Model working buffer size
            aulAVM3D_VC_FMBufferSize[ucViewIndex] = alFM_v2_1_QueryFM_WorkingBufferSizeSingle(&atFM_Cfg_AVM3D[ucViewIndex]);
            
            // Query FM Model working buffer
            apucAVM3D_VC_FMBuffer[ucViewIndex] = (UINT8*)malloc(aulAVM3D_VC_FMBufferSize[ucViewIndex] * sizeof(UINT8));

            // initail FM Model
            alFM_v2_1_InitialByCfgDataExternalBuffer(
                &atFM_Cfg_AVM3D[ucViewIndex],
                &atFM_Model_AVM3D[ucViewIndex],
                apucAVM3D_VC_FMBuffer[ucViewIndex]
                );
        }

        // Init By Cfg
        AVM3D_InitialByCfg(&talAVM3DParam, &tAVM3D_Cfg, atFM_Model_AVM3D);

        // log 光機所需資訊 在韌體上不需要做
        AVM3D_LogDataForAnalyzing(atFM_v2_Model, &talAVM3DParam, &tAVM3D_Cfg);

        // Gen LUT
#if 1
        // AVM3D LUT
        for (ucViewIndex = 0; ucViewIndex < tAVM3D_Cfg.lViewCnt; ucViewIndex++)
        {
            AVM3D_GenerateLUT(
                ucViewIndex,
                &talAVM3DParam.atViewParams[ucViewIndex],
                &tAVM3D_Cfg.atViewCfg[ucViewIndex],
                atFM_v2_Model,
                tEAGLEK3_Data.atCalibrationParams,
                &atalAVM3D_LUT[ucViewIndex]
            );
        }

        // AVM3D LUT for morphing
#if TEST_AVM3D_MORPHING
        tMorphingInfo.lMorphingNum = tMorphingCfg.lMorphingNum;
        for (lMorphingIndex = 0; lMorphingIndex < tMorphingCfg.lMorphingNum; lMorphingIndex++)
        {
            lSrcIndex = tMorphingCfg.atMorphingSet[lMorphingIndex].lSrcIndex;
            lDestIndex = tMorphingCfg.atMorphingSet[lMorphingIndex].lDestIndex;
            lMorphingFlag = tMorphingCfg.atMorphingSet[lMorphingIndex].lTableIndex;
            lMorphinfType = tMorphingCfg.atMorphingSet[lMorphingIndex].lMorphingType;
            lMorphingFrame = tMorphingCfg.atMorphingSet[lMorphingIndex].lFrameNumber;

            AVM3D_MorphingLUTGenerating(
                &tAVM3D_Cfg,
                &tAVM3D_Cfg.atViewCfg[lSrcIndex],					// AVM3D_CfgView *a_ptDestViewPara, (AVM3DLeft)
                &tAVM3D_Cfg.atViewCfg[lDestIndex],				// AVM3D_CfgView *a_ptSrcViewPara, (AVM3DBack2Front)
                lMorphingFlag,										// INT32 a_lMorphingLUTFlag,
                lMorphingFrame,										// INT32 a_lMorphingLUTNum,
                lMorphinfType,										// INT32 a_lMorphingType,
                &tMorphingInfo,
                atFM_v2_Model,
                tEAGLEK3_Data.atCalibrationParams,
                &tMorphingInfo.atMorphingLUTArray[lMorphingFlag]	// AVM3D_MorphingLUT *a_ptMorphingLUT
                );
        }
#endif

#endif

#if 1   // Save LUT
        wchar_t awcFilePath[MAX_PATH] = {0};
        CHAR acFilePath[MAX_PATH] = {0};
        CHAR acTmpPath[MAX_PATH] = { 0 };
        UINT8 *pucData = NULL;
        INT32 lSize = 0;
        INT32 lConvertedChars = 0;

        for (ucViewIndex = 0; ucViewIndex < tAVM3D_Cfg.lViewCnt; ucViewIndex++)
        {
            // alAVM3D LUT File (Set)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcstombs(acTmpPath, awcFilePath, MAX_PATH);
            sprintf(acFilePath, "%sEagleK_%s_set.hex", acTmpPath, tAVM3D_Cfg.atViewCfg[ucViewIndex].acName);
            lSize = sizeof(alLUT_v2_Def);
            pucData = (UINT8*)(&atalAVM3D_LUT[ucViewIndex]);
            mbstowcs(awcFilePath, acFilePath, MAX_PATH);
            Test_Memory2FileW(awcFilePath, pucData, lSize);

            // alAVM3D LUT File (Data)
            wcscpy_s(awcFilePath, MAX_PATH, a_pwcOutImageFolder);
            wcstombs(acTmpPath, awcFilePath, MAX_PATH);
            sprintf(acFilePath, "%sEagleK_%s_data.hex", acTmpPath, tAVM3D_Cfg.atViewCfg[ucViewIndex].acName);
            lSize = atalAVM3D_LUT[ucViewIndex].ulLUTDataSize;
            pucData = (UINT8*)(atalAVM3D_LUT[ucViewIndex].pullTable);
            mbstowcs(awcFilePath, acFilePath, MAX_PATH);
            Test_Memory2FileW(awcFilePath, pucData, lSize);
        }

#if TEST_AVM3D_MORPHING // save morphing LUT

#endif

#endif
        // Free LUT buffer
        for (ucViewIndex = 0; ucViewIndex < AVM3D_MAX_VIEW_ANGLE_CNT; ucViewIndex++)
        {
            AVM3D_FreeBuffer(&atalAVM3D_LUT[ucViewIndex], &aptalAVM3D_LUT_PART[ucViewIndex]);
        }
    }
#endif
	
#if 1
    Test_alAVM3D_Generate(
        &tAVM3D_Cfg,
        a_pwcEagleKWorkingFolder,
        a_pwcConfigFileName,
        a_pwcSrcImageFolder,
        a_pwcOutImageFolder,
        apucSrcImage
        );
#endif

    // free VC FM of each view
    for (ucViewIndex = 0; ucViewIndex < AVM3D_MAX_VIEW_ANGLE_CNT; ucViewIndex++)
    {
        free(apucAVM3D_VC_FMBuffer[ucViewIndex]);
    }

    // free FM Buffer
    free(apucFMBuffer[EAGLEK3_BV_LEFT]);
    free(apucFMBuffer[EAGLEK3_BV_RIGHT]);
    free(apucFMBuffer[EAGLEK3_BV_FRONT]);
    free(apucFMBuffer[EAGLEK3_BV_BACK]);

	delete[] apucSrcImage[0];
	delete[] apucSrcImage[1];
	delete[] apucSrcImage[2];
	delete[] apucSrcImage[3];
    //delete[] pucDestBuffer;

}

void Test_alAVM3D_Generate(
    alAVM3D_Cfg *a_ptCfg,
    wchar_t * a_pwcEagleKWorkingFolder,
    wchar_t * a_pwcConfigFileName,
    wchar_t * a_pwcSrcImageFolder,
    wchar_t * a_pwcOutImageFolder,
    UINT8 *a_apucSrcImage[4]
    )
{
    std::wstring salAVM2DLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_set.hex");
    std::wstring salAVM2DLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(L"EagleK_alAVM2DLUT_data.hex");
    std::wstring sOutputImgeFile;
    UINT8 * pucBuffer = NULL;
    UINT8 * pucBuffer2 = NULL, ucViewIndex = 0;
	UINT8 * pucDestBuffer = NULL;
    UINT32 ulBufferLength = 0, ulBufferLength2 = 0;
    alLUT_v2_Def talAVM3D_LUT;

    wchar_t awcTmp[MAX_PATH] = {0};
    CHAR acTmp[MAX_PATH] = {0};
    CHAR acSetFilePath[MAX_PATH] = "HELLO_123 ";
    CHAR acDataFilePath[MAX_PATH] = "HELLO_456 ";


    for (ucViewIndex = 0; ucViewIndex < a_ptCfg->lViewCnt; ucViewIndex++)
    {

        sprintf(acSetFilePath, "EagleK_%s_set.hex", a_ptCfg->atViewCfg[ucViewIndex].acName);
        sprintf(acDataFilePath, "EagleK_%s_data.hex", a_ptCfg->atViewCfg[ucViewIndex].acName);

        mbstowcs(awcTmp, acSetFilePath, MAX_PATH);
        salAVM2DLUTSetFilePath = std::wstring(a_pwcOutImageFolder).append(awcTmp);

        mbstowcs(awcTmp, acDataFilePath, MAX_PATH);
        salAVM2DLUTDataFilePath = std::wstring(a_pwcOutImageFolder).append(awcTmp);

        // Import AVM 3D (BV) LUT Set
        if (Test_ImportOtherHexFiles(salAVM2DLUTSetFilePath.c_str(), &pucBuffer, &ulBufferLength))
        {
            if (!Test_ImportOtherHexFiles(salAVM2DLUTDataFilePath.c_str(), &pucBuffer2, &ulBufferLength2)) assert(0);

            memcpy(&talAVM3D_LUT, pucBuffer, sizeof(alLUT_v2_Def));
            talAVM3D_LUT.pullTable = (UINT64*)malloc(talAVM3D_LUT.ulLUTDataSize);
            memcpy(talAVM3D_LUT.pullTable, pucBuffer2, talAVM3D_LUT.ulLUTDataSize);

			pucDestBuffer = new UINT8[talAVM3D_LUT.tDestImageBufferSize.lX * talAVM3D_LUT.tDestImageBufferSize.lY * 2];
			printf("BufferX:%dBufferY:%d\n", talAVM3D_LUT.tDestImageBufferSize.lX, talAVM3D_LUT.tDestImageBufferSize.lY);
			// Gen alAVM3D Image
			//////////////////////////////////Edit////////////////////////////////////////////////////
			memset(pucDestBuffer, 0, talAVM3D_LUT.tDestImageBufferSize.lX * talAVM3D_LUT.tDestImageBufferSize.lY * 2);
			//////////////////////////////////Edit////////////////////////////////////////////////////

            alLUT_v2_ProcessFullLU(&talAVM3D_LUT, a_apucSrcImage, pucDestBuffer);


            sprintf(acTmp, "%s_YUV_ByHex.raw", a_ptCfg->atViewCfg[ucViewIndex].acName);
            mbstowcs(awcTmp, acTmp, MAX_PATH);
            sOutputImgeFile = std::wstring(a_pwcOutImageFolder).append(awcTmp);
            std::ofstream ofile_alAVM2D(sOutputImgeFile.c_str(), std::ios::binary);

			//////////////////////////////////Edit////////////////////////////////////////////////////
			ofile_alAVM2D.write((char*)pucDestBuffer, talAVM3D_LUT.tDestImageBufferSize.lX * talAVM3D_LUT.tDestImageBufferSize.lY * 2);
			//////////////////////////////////Edit////////////////////////////////////////////////////

            ofile_alAVM2D.close();

            free(talAVM3D_LUT.pullTable);

            delete[] pucBuffer;
            delete[] pucBuffer2;
			delete[] pucDestBuffer;
        }
    }
}