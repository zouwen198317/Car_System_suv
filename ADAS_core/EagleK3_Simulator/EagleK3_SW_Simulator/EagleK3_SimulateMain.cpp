
#define EAGLEK_FACTORYAUTOK_TEST_FLAG 1

#include <iostream>
#include "EagleK3_SimulateMain.h"
#include "EagleK3.h"
#include "alINI.h"
#include <vector>
// #include "FolderSearch.h"


int wmain(int argc, wchar_t * argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    wchar_t awcSourceImageFolder[MAX_PATH];
    wchar_t awcOutputImageFolder[MAX_PATH];
    wchar_t awcEagleKWorkingFolder[MAX_PATH];

    wchar_t awcProgramSettingFileName[MAX_PATH];
    wchar_t awcConfigINIFileName[MAX_PATH];
    wchar_t awcFPINIFileName[MAX_PATH];

    wcscpy_s(awcEagleKWorkingFolder, MAX_PATH, L"EagleKWorkingFolder/");
    // wcscpy_s(awcSourceImageFolder, MAX_PATH, L"SourceImage/AVM_AM_TEST_VGA/"); 
    wcscpy_s(awcSourceImageFolder, MAX_PATH, L"SourceImage/AVM_AM_TEST_MEGA/");     wcscpy_s(awcOutputImageFolder, MAX_PATH, L"OutputImage/");
    wcscpy_s(awcProgramSettingFileName, MAX_PATH, L"./Setting.ini");
    // wcscpy_s(awcConfigINIFileName, MAX_PATH, L"CarModelSetting_MV_MC_AltekM7_VGA_AM_AVM_TOY_CAR_DCAC173.ini");
    wcscpy_s(awcConfigINIFileName, MAX_PATH, L"CarModelSetting_MV_MC_AltekM7_Maga_AM_AVM_TOY_CAR_DCAC173_.ini");    


    if (argc >= 2) // INI 檔案
    {
        wcscpy_s(awcConfigINIFileName, MAX_PATH, argv[1]);
    }
    if (argc >= 3) // 工作目錄
    {
        wcscpy_s(awcEagleKWorkingFolder, MAX_PATH, argv[2]);
    }
    if (argc >= 4) // 原影像目錄
    {
        wcscpy_s(awcSourceImageFolder, MAX_PATH, argv[3]);
    }
    if (argc >= 5) // 輸出影像目錄
    {
        wcscpy_s(awcOutputImageFolder, MAX_PATH, argv[4]);
    }

    wprintf(L"Load config ini file : \"%s\".\n This file should be put into the \"EagleKWorkingFolder\" folder.\n", awcConfigINIFileName);
    wprintf(L"Set EagleK Working Folder: \"%s\"\n", awcEagleKWorkingFolder);
    wprintf(L"Set Source Image Folder: \"%s\"\n", awcSourceImageFolder);
    wprintf(L"Set Output Image Folder: \"%s\"\n\n", awcOutputImageFolder);


    wcscpy_s(awcFPINIFileName, MAX_PATH, awcSourceImageFolder);
    wcscat_s(awcFPINIFileName, MAX_PATH, L"EagleK_FP.ini");

#if 0
    Test_LineSegDetectTmp();
#endif

#if 0 // test BV FM flow
    Test_BV_FM(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder
     );
#endif

#if 0 // test SBV flow
    Test_SBV_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder
     );
#endif

#if 0 // Test ManualK
    Test_ManualK_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
    );
#endif

#if 0 // Test ManualK by default
    Test_Only_BV_ManualK_By_Default();
#endif

#if 0 // Test BV Facotory AutoK by default
    Test_BV_FACTORY_AUTOKK_By_Default(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 1 // Test BV Facotory AutoK
    Test_BV_FACTORY_AUTOKK_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test alAVM2D
    Test_alAVM2D_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Hex file
    Test_HexFile_Tmp_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Hex file export
    Test_HexFile_Tmp_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Hex file export
        Test_HexFile_Export_TMP_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Hex file export
    Test_HexFile_Export_CFG1_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Hex file export
    Test_HexFile_Export_CFG2_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Hex file export
    Test_HexFile_Export_CFG4_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif


    

#if 0 // Test alAVM3D
    Test_alAVM3D_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test AV
    Test_AV_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Trail Line
    Test_TrailLine_By_LoadINICfg(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test Global AE
    Test_GAE_By_Load_LUT(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder,
        awcFPINIFileName
        );
#endif

#if 0 // Test LDCK
    Test_LDC(
        awcEagleKWorkingFolder,
        awcConfigINIFileName,
        awcSourceImageFolder,
        awcOutputImageFolder
    );
#endif

#if 0 // Test LDCK
    Test_test();
#endif

    std::cout << "Press any key to continue...\n";
    std::cin.get();

    return 0;
}