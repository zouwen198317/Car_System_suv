
#pragma once

#include "mtype.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    *  \addtogroup alCOMMON
    *  @{
    */

    /** \brief The INT32 point struct for recording X, Y position of points. */
    typedef struct
    {
        /** \brief The x data for alPointINT32. */
        INT32   lX;
        /** \brief The y data for alPointINT32. */
        INT32   lY;

    } alPointINT32;

    /** \brief The FLOAT64 point struct for recording X, Y position of points. */
    typedef struct
    {
        /** \brief The x data for alPointFLOAT64. */
        FLOAT64   eX;
        /** \brief The y data for alPointFLOAT64. */
        FLOAT64   eY;

    } alPointFLOAT64;

    /** \brief The INT32 rect struct for recording top, left, bottom, right position of a rect range. The bottom, right is not included in the rect. */
    typedef struct
    {

        /** \brief The top position of the alRectINT32. */
        INT32   lTop;
        /** \brief The left position of the alRectINT32. */
        INT32   lLeft;
        /** \brief The bottom position of the alRectINT32. */
        INT32   lBottom;
        /** \brief The right position of the alRectINT32. */
        INT32   lRight;

    } alRectINT32;

    /**
    *   \brief To get width of the alRectINT32 structure.
    *   \param a_ptRectINT32 [IN] The alRectINT32 structure to get width.
    *   \return The calculated rect width.
    */
    __inline INT32 alRectINT32_GetWidth(alRectINT32 * a_ptRectINT32)
    {
        return a_ptRectINT32->lRight - a_ptRectINT32->lLeft;
    }

    /**
    *   \brief To get height of the alRectINT32 structure.
    *   \param a_ptRectINT32 [IN] The alRectINT32 structure to get height.
    *   \return The calculated rect height.
    */
    __inline INT32 alRectINT32_GetHeight(alRectINT32 * a_ptRectINT32)
    {
        return a_ptRectINT32->lBottom - a_ptRectINT32->lTop;
    }

    /**
    *   \brief To get height of the alRectINT32 structure.
    *   \param a_ptRectINT32 [IN] The alRectINT32 structure to get height.
    *   \return The calculated rect size (lX = width, lY = height).
    */
    __inline alPointINT32 alRectINT32_GetSize(alRectINT32 * a_ptRectINT32)
    {
        alPointINT32 tSize;
        tSize.lX = a_ptRectINT32->lRight - a_ptRectINT32->lLeft;
        tSize.lY = a_ptRectINT32->lBottom - a_ptRectINT32->lTop;
        return tSize;
    }

    /**
    *   \brief To offset the rect position.
    *   \param a_ptRectINT32 [IN/OUT] The alRectINT32 structure to do offset.
    *   \param a_lOffsetX [IN] The x offset.
    *   \param a_lOffsetY [IN] The y offset.
    */
    __inline void alRectINT32_Offset(alRectINT32 * a_ptRectINT32, INT32 a_lOffsetX, INT32 a_lOffsetY)
    {
        a_ptRectINT32->lLeft += a_lOffsetX;
        a_ptRectINT32->lRight += a_lOffsetX;
        a_ptRectINT32->lTop += a_lOffsetY;
        a_ptRectINT32->lBottom += a_lOffsetY;
    }

    /**
    *   \brief Get the top-left position of the rect.
    *   \param a_ptRectINT32 [IN] The rect.
    *   \return The top-left position.
    */
    __inline alPointINT32 alRectINT32_GetTopLeft(alRectINT32 * a_ptRectINT32)
    {
        alPointINT32 tPoint;
        tPoint.lX = a_ptRectINT32->lLeft;
        tPoint.lY = a_ptRectINT32->lTop;
        return tPoint;
    }

    /**
    *   \brief Get the bottom-right position of the WOI.
    *   \param a_ptRectINT32 [IN] The rect.
    *   \return The bottom-right position.
    */
    __inline alPointINT32 alRectINT32_GetBottomRight(alRectINT32 * a_ptRectINT32)
    {
        alPointINT32 tPoint;
        tPoint.lX = a_ptRectINT32->lRight;
        tPoint.lY = a_ptRectINT32->lBottom;
        return tPoint;
    }

    /**
    *   \brief Get the bottom-central position of the WOI.
    *   \param a_ptRectINT32 [IN] The rect.
    *   \return The bottom-central position.
    */
    __inline alPointINT32 alRectINT32_GetBottomCentral(alRectINT32 * a_ptRectINT32)
    {
        alPointINT32 tPoint;
        tPoint.lX = ((a_ptRectINT32->lLeft + a_ptRectINT32->lRight) >> 1);
        tPoint.lY = a_ptRectINT32->lBottom;
        return tPoint;
    }

    /**
    *   \brief Move the bottom-central point to a specified position.
    *   \param a_ptRectINT32 [IN/OUT] The rect.
    *   \param a_lX [IN] The x offset to be applied.
    *   \param a_lY [IN] The y offset to be applied.
    */
    __inline void alRectINT32_MoveBottomCentralTo(alRectINT32 * a_ptRectINT32, INT32 a_lX, INT32 a_lY)
    {
        // Get current bottom-central position.
        alPointINT32 ulBottomCentral = alRectINT32_GetBottomCentral(a_ptRectINT32);
        // Offset to specified position.
        alRectINT32_Offset(a_ptRectINT32, a_lX - ulBottomCentral.lX, a_lY - ulBottomCentral.lY);
    }

    /**
    *   \brief To check if the input point insides in this "rect".
    *   \param a_ptRectINT32 [IN/OUT] The rect.
    */
    __inline BOOL alRectINT32_PtInRect(alRectINT32 * a_ptRectINT32, alPointINT32 * a_ptPt)
    {
        return ((a_ptPt->lX >= a_ptRectINT32->lLeft) * (a_ptPt->lX < a_ptRectINT32->lRight) * (a_ptPt->lY >= a_ptRectINT32->lTop) * (a_ptPt->lY < a_ptRectINT32->lBottom));
    }

    /** \brief The INT32 rect struct for recording top, left, width, height of a rect range. */
    typedef struct
    {

        /** \brief The top position of the alRectINT32. */
        INT32   lTop;
        /** \brief The left position of the alRectINT32. */
        INT32   lLeft;
        /** \brief The width position of the alRectINT32. */
        INT32   lWidth;
        /** \brief The height position of the alRectINT32. */
        INT32   lHeight;

    } alRectINT32wh;

    /**
    *   \brief Transfer an alRectINT32 structure to alRectINT32wh structure.
    *   \param a_ptRectINT32 [IN] The alRectINT32 structure.
    *   \param a_ptRectINT32wh [OUT] The alRectINT32wh structure.
    */
    __inline void alRectINT32toalRectINT32wh(alRectINT32 * a_ptRectINT32, alRectINT32wh * a_ptRectINT32wh)
    {
        a_ptRectINT32wh->lLeft = a_ptRectINT32->lLeft;
        a_ptRectINT32wh->lTop = a_ptRectINT32->lTop;
        a_ptRectINT32wh->lWidth = alRectINT32_GetWidth(a_ptRectINT32);
        a_ptRectINT32wh->lWidth = alRectINT32_GetHeight(a_ptRectINT32);
    }

    /** \brief Define the precision of KBM parameters. */
    #define alKMB_PRECISION          4194304
    /** \brief Define the shift value of KBM parameters. */
    #define alKMB_PRECISION_SHIFT    22

    /** \brief Define the structure for 2-order curve equation: y = k * x^2 + m * x + b. */
    typedef struct
    {
        /** \brief The 2nd-order parameter. */
        INT64 llK;
        /** \brief The 1st-order parameter. */
        INT64 llM;
        /** \brief The offset parameter. */
        INT64 llB;

    } alKMBSet;

    /**
    *  @}
    */

#ifdef __cplusplus
}
#endif
