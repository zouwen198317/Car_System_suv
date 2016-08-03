
#include "alTimeLog.h"
#include <assert.h>
#include <string.h>

#ifndef WIN32
#include <ti/sysbios/knl/Clock.h>
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
void alTIMELOG_SetStart(alTIMELOG_Data * a_ptTimeLog)
{
    assert(a_ptTimeLog != NULL);

    memset(a_ptTimeLog, 0, sizeof(alTIMELOG_Data));

#ifdef WIN32

    QueryPerformanceFrequency(&(a_ptTimeLog->tCPUFreq));
    QueryPerformanceCounter(&(a_ptTimeLog->tStartClock));

#else

    a_ptTimeLog->ulStartTick = Clock_getTicks();

#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////
void alTIMELOG_SetCurrent(alTIMELOG_Data * a_ptTimeLog)
{

#ifdef WIN32

    QueryPerformanceCounter(&(a_ptTimeLog->tCurrentClock));
    // 1000000 : to get micro-second resolution. If milisecond is requrired, use 1000 instead.
    a_ptTimeLog->llTimeInterval_us = (a_ptTimeLog->tCurrentClock.QuadPart - a_ptTimeLog->tStartClock.QuadPart) * 1000000 / a_ptTimeLog->tCPUFreq.QuadPart;

#else

    a_ptTimeLog->ulCurrentTick = Clock_getTicks();
    a_ptTimeLog->llTimeInterval_us = (a_ptTimeLog->ulCurrentTick - a_ptTimeLog->ulStartTick) * 1000;

#endif

}

//////////////////////////////////////////////////////////////////////////////////////////////////
INT64 alTIMELOG_GetTimeInterval(alTIMELOG_Data * a_ptTimeLog)
{
    return a_ptTimeLog->llTimeInterval_us;
}

