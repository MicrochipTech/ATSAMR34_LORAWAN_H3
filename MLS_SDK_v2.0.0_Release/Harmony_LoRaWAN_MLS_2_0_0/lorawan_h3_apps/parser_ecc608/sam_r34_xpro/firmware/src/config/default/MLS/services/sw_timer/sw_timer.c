/**
 * \file  sw_timer.c
 *
 * \brief This is the implementation of LoRaWAN SW Timer module
 *		
 */
/*******************************************************************************
Copyright (C) 2020-21 released Microchip Technology Inc. and its subsidiaries. 

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

 */


/******************************************************************************
                     Includes section
 ******************************************************************************/
#include <string.h>
#include "definitions.h"
#include "atomic.h"
#include "system_assert.h"
#include "conf_sw_timer.h"
#include "sw_timer.h"

#ifndef TOTAL_NUMBER_SW_TIMESTAMPS
#define TOTAL_NUMBER_SW_TIMESTAMPS  (2u)
#endif /* #ifndef TOTAL_NUMBER_SW_TIMESTAMPS */

#define SWTIMER_MIN_DURATION        (MS_TO_US(1U)) // 1ms

#if (TOTAL_NUMBER_OF_SW_TIMERS > 0)

/******************************************************************************
                     Prototypes section
 ******************************************************************************/
static void hwTimerIrqHandler(TC_COMPARE_STATUS status, uintptr_t context);
static void hwTimerOverflowCallback(void);
static void hwTimerExpiryCallback(void);
static inline void hwTimerEnableCompare(void);
static inline void hwTimerDisableCompare(void);
static uint32_t hwTimerElapsedTime(void);

static uint32_t SwTimerInterrupt(void);
static uint32_t SwTimerUpdate(uint32_t elapsedTime);

/******************************************************************************
                     Global variables section
 ******************************************************************************/

/******************************************************************************
             +-------------------+----------+-----------+
             | SYS_TIME_OVERFLOW |      TCx_COUNT       |
             +-------------------+----------+-----------+
             63                  31         15          0
 ******************************************************************************/
/*
 * This represents the bits 31 to 63 of the high word of system time.
 * And, it is incremented whenever the \sysTime overflows.
 */
volatile uint32_t sysTimeOvf;

/* This is the timer array. */
SwTimer_t swTimers[TOTAL_NUMBER_OF_SW_TIMERS];

/* This is the timestamp array */
SwTimestamp_t swTimestamp[TOTAL_NUMBER_SW_TIMESTAMPS];

/******************************************************************************
                     Static variables section
 ******************************************************************************/
/* This is the count of timers that are allocated at the instance. */
static uint8_t allocatedTimerId = 0;

/* This is the count of timestamps that are allocated at the instance. */
static uint8_t allocatedTimestampId = 0;

/* This is the last known system time saved before sleep */
static uint64_t sysTimeLastKnown = 0UL;

/* This is the flag to enable/disable compare callback */
static volatile bool compareCallbackEnabled = false;

/* These are the variables to run the timer */
static volatile uint32_t lastCount = 0U;
static volatile uint32_t currentCount = 0U;
static volatile uint32_t compareValue = 0U;

/******************************************************************************
                     Hardware timer routines
 ******************************************************************************/

/* HW timer interrupt handler */
static void hwTimerIrqHandler(TC_COMPARE_STATUS status, uintptr_t context)
{
    if ((status & TC_INTFLAG_OVF_Msk) == TC_INTFLAG_OVF_Msk)
    {
        hwTimerOverflowCallback();
    }
    else if ((status & TC_INTFLAG_MC0_Msk) == TC_INTFLAG_MC0_Msk)
    {
        if (compareCallbackEnabled)
        {
            hwTimerDisableCompare();
            hwTimerExpiryCallback();
        }
    }
    (void) context;
}

/* ISR to handle OVF interrupt from TC */
static void hwTimerOverflowCallback(void)
{
    sysTimeOvf++;
}

/* ISR to handle MC0 interrupt from TC */
static void hwTimerExpiryCallback(void)
{
    uint32_t tmo = SwTimerInterrupt();
    if (tmo != SWTIMER_INVALID_TIMEOUT)
    {
        compareValue = tmo + currentCount;
        hwTimerEnableCompare();
        TC0_Compare32bitMatch0Set(compareValue);
    }
    else
    {
        hwTimerDisableCompare();
    }
}

static inline void hwTimerEnableCompare(void)
{
    TC0_REGS->COUNT32.TC_INTFLAG = TC_INTFLAG_MC0_Msk;
    TC0_REGS->COUNT32.TC_INTENSET = TC_INTENSET_OVF_Msk | TC_INTENSET_MC0_Msk;
    compareCallbackEnabled = true;
}

static inline void hwTimerDisableCompare(void)
{
    TC0_REGS->COUNT32.TC_INTENSET = TC_INTENSET_OVF_Msk;
    compareCallbackEnabled = false;
}

static uint32_t hwTimerElapsedTime(void)
{
    uint32_t elapsed = SWTIMER_INVALID_TIMEOUT;

    currentCount = TC0_Compare32bitCounterGet();

    if (currentCount < lastCount)
        elapsed = (UINT32_MAX - lastCount + 1U) + currentCount;
    else
        elapsed = currentCount - lastCount; // covers the case of first timer start

    lastCount = currentCount;

    return elapsed;
}

/******************************************************************************
               Static function implementation section
 ******************************************************************************/
static uint32_t SwTimerUpdate(uint32_t elapsedTime)
{
    uint32_t timer;
    uint32_t nextTimerInterval = SWTIMER_INVALID_TIMEOUT;

    for (timer = 0U; timer < TOTAL_NUMBER_OF_SW_TIMERS; timer++)
    {
        if (swTimers[timer].loaded)
        {
            if (swTimers[timer].timeToExpire <= elapsedTime)
            {
                swTimers[timer].timeToExpire = 0U;
                SYSTEM_PostTask(TIMER_TASK_ID);
            }
            else
            {
                swTimers[timer].timeToExpire -= elapsedTime;

                if (swTimers[timer].timeToExpire >= SWTIMER_MIN_DURATION)
                {
                    if (swTimers[timer].timeToExpire < nextTimerInterval)
                        nextTimerInterval = swTimers[timer].timeToExpire;
                }
                else
                {
                    swTimers[timer].timeToExpire = 0U;
                    SYSTEM_PostTask(TIMER_TASK_ID);
                }
            }
        }
    }

    return nextTimerInterval;
}

static uint32_t SwTimerInterrupt(void)
{
    return SwTimerUpdate(hwTimerElapsedTime());
}

/******************************************************************************
                     Implementation section
 ******************************************************************************/
void SwTimerReset(void)
{
    allocatedTimerId = 0U;
    sysTimeOvf = 0U;
    lastCount = 0U;
    currentCount = 0U;
    for (uint8_t timer = 0; timer < TOTAL_NUMBER_OF_SW_TIMERS; timer++)
    {
        swTimers[timer].timeToExpire = 0U;
        swTimers[timer].timerCb = NULL;
        swTimers[timer].paramCb = NULL;
        swTimers[timer].loaded = false;
    }
    hwTimerDisableCompare();
}

void SystemTimerInit(void)
{
    SwTimerReset();
    /* Configure and start the hardware timer */
    TC0_Compare32bitCounterSet(currentCount);
    TC0_CompareCallbackRegister((TC_COMPARE_CALLBACK) hwTimerIrqHandler,
                                (uintptr_t) NULL);
    TC0_CompareStart();
}

StackRetStatus_t SwTimerCreate(uint8_t *timerId)
{
    bool flags;
    StackRetStatus_t retval = LORAWAN_RESOURCE_UNAVAILABLE;

    flags = cpu_irq_save();
    if (allocatedTimerId < TOTAL_NUMBER_OF_SW_TIMERS)
    {
        *timerId = allocatedTimerId;
        allocatedTimerId++;
        retval = LORAWAN_SUCCESS;
    }
    cpu_irq_restore(flags);

    return retval;
}

uint64_t SwTimerGetTime(void)
{
    uint64_t systime;
    uint32_t *psystime = (uint32_t *) & systime;
    psystime[0] = TC0_Compare32bitCounterGet();
    psystime[1] = sysTimeOvf;
    return systime;
}

StackRetStatus_t SwTimerStart(uint8_t timerId, uint32_t timerCount,
                              SwTimeoutType_t timeoutType, void *timerCb, void *paramCb)
{
    uint32_t interval;
    uint32_t now;
    uint32_t tmo;

    if (timerId == SWTIMER_INVALID)
        return LORAWAN_INVALID_REQUEST;

    if (swTimers[timerId].loaded)
        return LORAWAN_INVALID_REQUEST;

    if (timeoutType == SW_TIMEOUT_ABSOLUTE)
    {
        now = TC0_Compare32bitCounterGet();
        if (timerCount >= now)
            interval = timerCount - now;
        else
            interval = (UINT32_MAX - now + 1U) + timerCount;
    }
    else
        interval = timerCount;

    if ((interval < SWTIMER_MIN_TIMEOUT) || (interval > SWTIMER_MAX_TIMEOUT))
        return LORAWAN_INVALID_PARAMETER;

    swTimers[timerId].timerCb = timerCb;
    swTimers[timerId].paramCb = paramCb;
    swTimers[timerId].timeToExpire = interval;

    hwTimerDisableCompare();

    tmo = SwTimerInterrupt();

    if (tmo == SWTIMER_INVALID_TIMEOUT)
    {
        tmo = interval;
    }
    else if (interval < tmo)
    {
        tmo = interval;
    }
    swTimers[timerId].loaded = true;

    compareValue = TC0_Compare32bitCounterGet() + tmo;
    TC0_Compare32bitMatch0Set(compareValue);

    hwTimerEnableCompare();

    return LORAWAN_SUCCESS;
}

StackRetStatus_t SwTimerStop(uint8_t timerId)
{
    bool flags = cpu_irq_save();
    swTimers[timerId].loaded = false;
    cpu_irq_restore(flags);

    return LORAWAN_SUCCESS;
}

bool SwTimerIsRunning(uint8_t timerid)
{
    uint8_t isRunning;
    bool flags;

    flags = cpu_irq_save();
    isRunning = swTimers[timerid].loaded;
    cpu_irq_restore(flags);

    return isRunning;
}

void SystemTimerSuspend(void)
{
    bool flags = cpu_irq_save();
    hwTimerDisableCompare();
    sysTimeLastKnown = SwTimerGetTime();
    SwTimerInterrupt();    
    TC0_CompareStop();
    cpu_irq_restore(flags);
}

void SystemTimerSync(uint64_t timeToSync)
{
    uint32_t *pTime = (uint32_t *) & sysTimeLastKnown;
    uint32_t tmo;
    sysTimeLastKnown += timeToSync;
    sysTimeOvf = pTime[1];
    lastCount = pTime[0];
    currentCount = pTime[0];

    TC0_CompareInitialize();
    TC0_CompareCallbackRegister((TC_COMPARE_CALLBACK) hwTimerIrqHandler,
                                (uintptr_t) NULL);
    TC0_Compare32bitCounterSet(currentCount);

    tmo = SwTimerUpdate((uint32_t) timeToSync);
    if (tmo != SWTIMER_INVALID_TIMEOUT)
    {
        hwTimerEnableCompare();
        compareValue = tmo + currentCount;
        TC0_Compare32bitMatch0Set(compareValue);
    }
    else
    {
        hwTimerDisableCompare();
    }

    TC0_CompareStart();
}

uint32_t SwTimerReadValue(uint8_t timerId)
{
    bool flags;
    uint32_t remainingTime;

    flags = cpu_irq_save();
    SwTimerInterrupt();
    remainingTime = swTimers[timerId].timeToExpire;
    cpu_irq_restore(flags);

    return remainingTime;
}

uint32_t SwTimerNextExpiryDuration(void)
{
    uint32_t duration = SWTIMER_INVALID_TIMEOUT;
    uint32_t countValue;
    uint8_t timersRunning = 0U;

    for (uint8_t i = 0; i < TOTAL_NUMBER_OF_SW_TIMERS; i++)
    {
        if (swTimers[i].loaded)
        {
            timersRunning = 1U;
            break;
        }
    }

    if (timersRunning)
    {
        countValue = TC0_Compare32bitCounterGet();
        if (countValue < compareValue)
            duration = compareValue - countValue;
        else
            duration = (UINT32_MAX - countValue + 1U) + compareValue;
    }
    return duration;
}

void SwTimersExecute(void)
{
    bool flag = cpu_irq_save();
    for (uint8_t timer = 0; timer < TOTAL_NUMBER_OF_SW_TIMERS; timer++)
    {
        if (swTimers[timer].loaded)
        {
            if (swTimers[timer].timeToExpire == 0U)
            {
                swTimers[timer].loaded = false;
                cpu_irq_restore(flag);
                if (swTimers[timer].timerCb)
                {
                    swTimers[timer].timerCb(swTimers[timer].paramCb);
                }
                flag = cpu_irq_save();
            }
        }
    }
    cpu_irq_restore(flag); 
}
SYSTEM_TaskStatus_t TIMER_TaskHandler(void)
{
    SwTimersExecute();
    return LORAWAN_SUCCESS;
}

/**************************************************************************//**
\brief Returns a timestamp id to be used before using it

\param[out] timestampId Value of the id returned by the function

\return LORAWAN_SUCCESS if new timerId is allocated
        LORAWAN_RESOURCE_UNAVAILABLE if there is no more timerId to allocate
******************************************************************************/

StackRetStatus_t SwTimerTimestampCreate(uint8_t *timestampId)
{
    StackRetStatus_t retVal = LORAWAN_SUCCESS;

    if (allocatedTimestampId < TOTAL_NUMBER_SW_TIMESTAMPS)
    {
        bool flags = cpu_irq_save();
        *timestampId = allocatedTimestampId;
        allocatedTimestampId++;
        cpu_irq_restore(flags);
    }
    else
    {
        retVal = LORAWAN_RESOURCE_UNAVAILABLE;
    }

    return retVal;
}

/**************************************************************************//**
\brief Returns the timestamp stored in the given timestamp index
\param[in] index Index of the system timestamp
\param[out] *timestamp Pointer-to-timestamp to be read from the given index
******************************************************************************/

void SwTimerReadTimestamp(uint8_t index, SwTimestamp_t *timestamp)
{
    *timestamp = swTimestamp[index];
}

/**************************************************************************//**
\brief Stores the timestamp in the given timestamp index
\param[in] index Index of the system timestamp
\param[in] *timestamp Pointer-to-timestamp to be stored in the given index
******************************************************************************/

void SwTimerWriteTimestamp(uint8_t index, SwTimestamp_t *timestamp)
{
    swTimestamp[index] = *timestamp;
}

/**************************************************************************//**
\brief Difference between the given timestamps
\param[in] *earlier  Pointer-to-timestamp of known-to-be-earlier time
\param[in] *later    Pointer-to-timestamp of known-to-be-later time
\return SwTimestamp_t - time difference between later and earlier timestamps
******************************************************************************/

SwTimestamp_t SwTimerTimeDiff(SwTimestamp_t *earlier, SwTimestamp_t *later)
{
    SwTimestamp_t diff = SW_TIMESTAMP_INVALID;

    if (*later >= *earlier)
    {
        diff = *later - *earlier;
    }
    else
    {
        diff = (UINT64_MAX - *earlier) + *later;
    }

    return diff;
}
#endif /* #if (TOTAL_NUMBER_OF_SW_TIMERS > 0) */

/* EOF sw_timer.c */
