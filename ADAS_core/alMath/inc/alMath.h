
#pragma once

#include "mtype.h"
#include "math.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    *  \defgroup alMATH   alMath
    *  This module provide additional math functions.
    *  @{
    */

    /** 
    *   \biref Returns a value with the magnitude of x and the sign of y. FLOAT64 format. 
    *   \param a_eX [IN] Value with the magnitude of the resulting value.
    *   \param a_eY [IN] Value with the sign of the resulting value.
    */
    inline FLOAT64 alCopysign(FLOAT64 a_eX, FLOAT64 a_eY)
    {
        UINT64 ullZ = (((*(UINT64*)(&a_eX)) & 0x7FFFFFFFFFFFFFFF) | ((*(UINT64*)(&a_eY)) & 0x8000000000000000));
        return *((FLOAT64*)(&ullZ));
    }

    /**
    *   \biref Returns a value with the magnitude of x and the sign of y. FLOAT32 format.
    *   \param a_fX [IN] Value with the magnitude of the resulting value.
    *   \param a_fY [IN] Value with the sign of the resulting value.
    *   \return The value with the magnitude of x and the sign of y
    */
    inline FLOAT32 alCopysignf(FLOAT32 a_fX, FLOAT32 a_fY)
    {
        UINT32 ulZ = (((*(UINT32*)(&a_fX)) & 0x7FFFFFFF) | ((*(UINT32*)(&a_fY)) & 0x80000000));
        return *((FLOAT32*)(&ulZ));
    }
    
    /**
    *   \biref Returns whether the sign of x is negative. Only for FLOAT64 format.
    *   \param a_eX [IN] A FLOAT64 value. .
    *   \return If the sign of x is negative,  0: positive, 1: negative.
    */
    #define alSignbit(a_eX) ((*(UINT64*)(&a_eX))>>63)

    /**
    *   \biref Returns whether the sign of x is negative. Only for FLOAT32 format.
    *   \param a_eX [IN] A FLOAT32 value. .
    *   \return If the sign of x is negative,  0: positive, 1: negative.
    */
    #define alSignbitf(a_fX) ((*(UINT32*)(&a_fX))>>31)

    /**
    *  @}
    */

#ifdef __cplusplus
}
#endif
