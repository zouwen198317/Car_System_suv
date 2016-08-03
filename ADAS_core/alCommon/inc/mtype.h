/****************************************************************************
* File: mtype.h                                                             *
* Description: Global type definition                                       *
****************************************************************************/

#ifndef _MTYPE_H_
#define _MTYPE_H_

/**
*   \defgroup alCOMMON   alCommon
*   This is an common group to define based declarations & functions.
*   @{
*/

// =======================================================================
// Global data type

/** \brief Define the data type for FLOAT32. */
typedef float                   FLOAT32;
/** \brief Define the data type for FLOAT64. */
typedef double                  FLOAT64;

#ifdef WIN32

    #include <windows.h>    // for basic type defines

#else

    #include <wchar.h>  // for wchar_t
	
    #ifndef TRUE
    /** \brief Define the data flag for TRUE. */
    #define TRUE                    1
    #endif

    #ifndef FALSE
    /** \brief Define the data flag for FALSE. */
    #define FALSE                   0
    #endif

    #ifndef NULL
    /** \brief Define the data flag for NULL. */
    #define NULL                    ((void *)0)
    #endif

    /** \brief Define the data type for WCHAR. */
    typedef wchar_t                 WCHAR;
    /** \brief Define the data type for CHAR. */
    typedef char                    CHAR;
    /** \brief Define the data type for INT8. */
    typedef char                    INT8;
    /** \brief Define the data type for UINT8. */
    typedef unsigned char           UINT8;
    /** \brief Define the data type for INT16. */
    typedef short                   INT16;
    /** \brief Define the data type for UINT16. */
    typedef unsigned short          UINT16;
    /** \brief Define the data type for INT32. */
    typedef int                     INT32;
    /** \brief Define the data type for UINT32. */
    typedef unsigned int            UINT32;
    /** \brief Define the data type for INT64. */
    typedef long long               INT64;
    /** \brief Define the data type for UINT64. */
    typedef unsigned long long      UINT64;

    #ifndef BOOL
    /** \brief Define the data type for BOOL. */
    #define BOOL					          UINT8
    //typedef UINT8                 BOOL; // 팒 ti platform ずヅ쬲식ю
    #endif
	
    ///** \brief Define the data type for DWORD. */
    //typedef UINT32                  DWORD; // 팒 ti platform ずヅ쬲식ю

    typedef void                    (*CALLBACK)();
    typedef unsigned long            ERRCODE;
    typedef void                    *PVOID;
    typedef char                    *PSTR;

    typedef PVOID                   HWND;

#endif


#endif

/**
  *  @}
  */
