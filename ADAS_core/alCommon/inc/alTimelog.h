
#pragma once

#include "mtype.h"

/**
*   \defgroup alTIMELOG    alTimeLog
*   The module define the struct whiche inclues car information, such like gear status, door opened/closed, .. etc.
*   Most of these information are provided by car sensor through CAN protocol.
*   There are some enum data are defined to incidate the status of gear, door, headlight, ....
*  @{
*/

/** \brief This structure is used to store the start lock of the time log. */
typedef struct
{

#ifdef WIN32

    /** \brief The CPU clock frequence. */
    LARGE_INTEGER tCPUFreq;

    /** \brief The start clock of this time log. */
    LARGE_INTEGER tStartClock;

    /** \brief The current clock of this time log. */
    LARGE_INTEGER tCurrentClock;

#else
    UINT32 ulStartTick;
    UINT32 ulCurrentTick;
#endif

    /** \brief The microsecond time interval between lStartClock & lCurrentClock. */
    INT64 llTimeInterval_us;

} alTIMELOG_Data;

#ifdef __cplusplus
extern "C"
{
#endif

    /** \brief To initialize and set the start clock of the "alTimeLog" structure. */
    void alTIMELOG_SetStart(alTIMELOG_Data * a_ptTimeLog);

    /** \brief To set the current clock to the "alTimeLog" structure. */
    void alTIMELOG_SetCurrent(alTIMELOG_Data * a_ptTimeLog);

    /** \brief To get the time inverval between the start clock and current clock. */
    INT64 alTIMELOG_GetTimeInterval(alTIMELOG_Data * a_ptTimeLog);
   
#ifdef __cplusplus
}
#endif

/**
*  @}
*/
