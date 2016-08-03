
#pragma once

#include "mtype.h"
/**
*   \addtogroup alCOMMON
*   @{
*/
#ifdef INC_TILIB

#include "alTILibDef.h"

#ifdef WIN32
#include "c6xsim/C6xSimulator.h"
#else // #ifdef WIN32
#include <c6x.h>
#endif // #ifdef WIN32

#endif //#ifdef INC_TILIB

#ifndef alPI
    /** \brief Define the ratio of a circle's circumference to its diameter. */
    #define alPI                (3.14159265358979323846)
#endif

#ifndef alRAD
    /** \brief To transfer degree to radian. */
    #define alRAD(degree) ((degree)*alPI/180)  
#endif

#ifndef alROUND
#ifdef INC_TILIB
    /** \brief To do rounding to eliminate decimal on FLOAT64. */
    #define alROUND(a)          _dpint(a)
#else
    /** \brief To do rounding to eliminate decimal on FLOAT64. Include if statement and should avoid to be used in cirtical function. */
    #define alROUND(a)          ((INT32)(a >= 0 ? (a + 0.5) : (a - 0.5)))
#endif
#endif

#ifndef alROUNDF
#ifdef INC_TILIB
    /** \brief To do rounding to eliminate decimal on FLOAT32. */
    #define alROUNDF(a)         _spint(a)
#else
    /** \brief To do rounding to eliminate decimal on FLOAT32. Include if statement and should avoid to be used in cirtical function. */
    #define alROUNDF(a)         ((INT32)(a >= 0 ? (a + 0.5) : (a - 0.5)))
#endif
#endif

#ifndef alROUND_P
    /** \brief To do rounding to eliminate decimal for positive value. */
    #define alROUND_P(a)        ((INT32)(a + 0.5))
#endif

#ifndef alROUND_N
    /** \brief To do rounding to eliminate decimal for negative value. */
    #define alROUND_N(a)        ((INT32)(a - 0.5))
#endif

#ifndef alROUND_EVEN
    /** \brief To do rounding to even number. Include if statement and should avoid to be used in cirtical function. */
    #define alROUND_EVEN(a)     ((a>0)?(((INT32)(a+1)>>1)<<1):(((INT32)(a-1)>>1)<<1))
#endif

#ifndef alMAX
    /** \brief Return the larger value. Include if statement and should avoid to be used in cirtical function. */
    #define alMAX(a,b)          ((a>b) ? a : b)
#endif  // #ifndef MAX

#ifndef alMIN
    /** \brief Return the lower value. Include if statement and should avoid to be used in cirtical function. */
    #define alMIN(a,b)          ((a<b) ? a : b)
#endif  // #ifndef MIN

#ifndef alMinINT32
    /** \brief The min function support for INT32. */
    #define alMinINT32(x, y)    ((y) + (((x) - (y)) & (((x) - (y))>>31)))
#endif  // #ifndef alMinINT32

#ifndef alMaxINT32
    /** \brief The max function support for INT32. */
    #define alMaxINT32(x, y)    ((x) - (((x) - (y)) & (((x) - (y))>>31)))
#endif  // #ifndef alMaxINT32

#ifdef INC_TILIB

#ifndef alMinINT16
    /** 
    \brief The min function for INT16. This function support single and two INT16 compare operation. 
            For two INT16 compare : 將兩個 INT16 分別放在第1~2及第3~4個Byte位置，可以同時比對，並分別輸出結果到相對應的 Byte 位置。 
    */
    #define alMinINT16(x, y)        _min2(x, y)
#endif  // #ifndef alMinINT16

#ifndef alMaxINT16
    /** 
    \brief The max function for INT16. This function support single or two INT16 compare operation. 
            For two INT16 compare : 將兩個 INT16 分別放在第1~2及第3~4個Byte位置，可以同時比對，並分別輸出結果到相對應的 Byte 位置。 
    */
    #define alMaxINT16(x, y)        _max2(x, y)
#endif  // #ifndef alMaxINT16

#ifndef alMinINT8
    /** 
    \brief The min function for INT8. This function support single or two INT8 compare operation. 
            For two INT8 compare : 將兩個 INT8 分別放在第1及第3個Byte位置，可以同時比對，並分別輸出結果到相對應的 Byte 位置。 
    */
    #define alMinINT8(x, y)         _min2(x, y)
#endif  // #ifndef alMinINT8

#ifndef alMaxINT8
    /** 
    \brief The max function for INT8. This function support single or two INT8 compare operation. 
            For two INT8 compare : 將兩個 INT8 分別放在第1及第3個Byte位置，可以同時比對，並分別輸出結果到相對應的 Byte 位置。 
    */
    #define alMaxINT8(x, y)         _max2(x, y)
#endif  // #ifndef alMaxINT8

#ifndef alMin4UINT8
    /** 
    \brief The min function for UINT8. This function support 4 UINT8 compare operation. 
           將4個 UINT8 分別放在第1, 2, 3, 4 個Byte位置，可以同時比對，並分別輸出結果到相對應的 Byte 位置。 
           若需要比對的數目較少，可自由減少。例如只需比對2個 UINT8 ，則只需要將該2個UINT8放在第1及第2個位置，其餘Byte補0即可。
    */
    #define alMin4UINT8(x, y)       _minu4(x, y)
#endif  // #ifndef alMin4UINT8

#ifndef alMax4UINT8
    /** 
    \brief The max function for UINT8. This function support 4 UINT8 compare operation. 
           將4個 UINT8 分別放在第1, 2, 3, 4 個Byte位置，可以同時比對，並分別輸出結果到相對應的 Byte 位置。 
           若需要比對的數目較少，可自由減少。例如只需比對2個 UINT8 ，則只需要將該2個UINT8放在第1及第2個位置，其餘Byte補0即可。
    */
    #define alMax4UINT8(x, y)       _maxu4(x, y)
#endif  // #ifndef alMax4UINT8

#ifndef alMinFLOAT32
    /** \brief The min function support for FLOAT32. This function support single FLOAT32 compare operation. */
    #define alMinFLOAT32(x, y)      ((y) + (((x) - (y)) * (((*(INT32*)(&x) - *(INT32*)(&y))>>31)&0x1)))
#endif  // #ifndef alMinFLOAT32

#ifndef alMaxFLOAT32
    /** \brief The max function support for FLOAT32. This function support single FLOAT32 compare operation. */
    #define alMaxFLOAT32(x, y)      ((x) - (((x) - (y)) * (((*(INT32*)(&x) - *(INT32*)(&y))>>31)&0x1)))
#endif  // #ifndef alMaxFLOAT32

//#ifndef alMinFLOAT64 //回傳值有精確度的問題，故不建議使用
//#define alMinFLOAT64(x, y)      ((y) + ((x - (y)) * (((*(INT64*)(&x) - *(INT64*)(&y))>>63)&0x1)))
//#endif
//
//#ifndef alMaxFLOAT64
//#define alMaxFLOAT64(x, y)      ((x) - ((x - (y)) * (((*(INT64*)(&x) - *(INT64*)(&y))>>63)&0x1)))
//#endif

#endif // #ifdef INC_TILIB

#ifndef alABS
    #ifdef INC_TILIB
        /** \brief Define the alABS to use TI _abs function. */
        #define alABS(x)     _abs(x)
    #else //#ifdef INC_TILIB
        /** \brief Define the alABS to use C/C++ standard abs function. */
        #define alABS(x)     abs(x)
    #endif //#ifdef INC_TILIB
#endif  // #ifndef alABS

#ifndef alFABS
#ifdef INC_TILIB
/** \brief Define the alFABS to use TI _abs function. */
#define alFABS(x)     _fabs(x)
#else //#ifdef INC_TILIB
/** \brief Define the alFABS to use C/C++ standard abs function. */
#define alFABS(x)     fabs(x)
#endif //#ifdef INC_TILIB
#endif  // #ifndef alABS

#ifndef alFABSF
#ifdef INC_TILIB
/** \brief Define the alFABSF to use TI _abs function. */
#define alFABSF(x)     _fabsf(x)
#else //#ifdef INC_TILIB
/** \brief Define the alFABSF to use C/C++ standard abs function. */
#define alFABSF(x)     fabsf(x)
#endif //#ifdef INC_TILIB
#endif  // #ifndef alABS

#ifndef alSignINT16
/** \brief Return the sign bit (0 or 1) for INT16. */
#define alSignINT16(a)          (((a) & 0x8FFF) >> 15)
#endif  // #ifndef alSignINT16

#ifndef alSignINT32
/** \brief Return the sign bit (0 or 1) for INT16. */
#define alSignINT32(a)          (((a) & 0x8FFFFFFF) >> 31)
#endif  // #ifndef alSignINT16

#ifdef WIN32
    #include <stdio.h>      // for printf
    #include <wchar.h>      // for wprintf

    /** \brief Define macro of DEBUG_Printf for multibytes output. */
    #define     DEBUG_Printf        printf
    /** \brief Define macro of DEBUG_PrintfW for unicode output. */
    #define     DEBUG_PrintfW       wprintf
#else
	#include "ioutil.h" // for IoPrintf
	/** \brief Define macro of DEBUG_Printf for multibytes output. */
	#define     DEBUG_Printf        IoPrintf
	/** \brief Define macro of DEBUG_PrintfW for unicode output. */
	#define     DEBUG_PrintfW       

	#define 	__restrict			restrict
#endif	

/**
  *  @}
  */ 
