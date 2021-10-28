/**
* \file  pmm.c
*
* \brief This is the implementation of LoRaWAN power management module
*
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
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR
*******************************************************************************/



/************************************************************************/
/* Includes                                                             */
/************************************************************************/
/* Standard headers */
#include <stdint.h>
#include "definitions.h"

/* PMM headers */
#include "pmm.h"
#include "conf_pmm.h"

/* Timer headers */
#include "sw_timer.h"
#include "sleep_timer.h"

/* HAL sleep header */
#include "sleep.h"

/* Other required headers */
#include "atomic.h"
#include "system_task_manager.h"

/************************************************************************/
/*                   Prototypes section                                 */
/************************************************************************/
#ifdef CONF_PMM_ENABLE
static inline bool validateSleepDuration(uint32_t durationMs);
#endif
/************************************************************************/
/* Static variables                                                     */
/************************************************************************/
#ifdef CONF_PMM_ENABLE
static PMM_SleepReq_t *sleepReq = NULL;
static PMM_State_t pmmState = PMM_STATE_ACTIVE;
#endif

/************************************************************************/
/* Function definitions                                                 */
/************************************************************************/
static inline bool validateSleepDuration(uint32_t durationMs)
{
#ifdef CONF_PMM_ENABLE
    return (PMM_SLEEPTIME_MIN_MS <= durationMs) && \
           (PMM_SLEEPTIME_MAX_MS >= durationMs) && \
           (SWTIMER_INVALID_TIMEOUT != durationMs);
#else
    return false;
#endif /* CONF_PMM_ENABLE */
}

/**
* \brief This function puts the system to sleep if possible
*
* \param[in]  *req  -  pointer to PMM_SleepReq_t request structure
*
* \return value of type PMM_Status_t
*         PMM_SLEEP_REQ_DENIED -- when sleep is not possible at the instance
*         PMM_SLEEP_REQ_PROCESSED -- when sleep is possible and have already done
*/
PMM_Status_t PMM_Sleep(PMM_SleepReq_t *req)
{
    PMM_Status_t status = PMM_SLEEP_REQ_DENIED;
#ifdef CONF_PMM_ENABLE
    uint32_t sysSleepTime = ~0u; /* 0xffFFffFF is invalid */
    bool canSleep;

    if ( req && (PMM_STATE_ACTIVE == pmmState) )
    {
        canSleep = SYSTEM_ReadyToSleep();
        canSleep = canSleep && validateSleepDuration( req->sleepTimeMs );

        if ( false == canSleep )
        {
            return status;
        }

        if ( SLEEP_MODE_BACKUP == req->sleep_mode )
        {
            canSleep = canSleep && ( SWTIMER_INVALID_TIMEOUT == SwTimerNextExpiryDuration() );
            sysSleepTime = req->sleepTimeMs;
        }
        else if ( SLEEP_MODE_STANDBY == req->sleep_mode )
        {
            sysSleepTime = SwTimerNextExpiryDuration();
            sysSleepTime = (SWTIMER_INVALID_TIMEOUT == sysSleepTime) ? PMM_SLEEPTIME_MAX_MS : US_TO_MS( sysSleepTime );
            canSleep = canSleep && validateSleepDuration( sysSleepTime );
            if ( canSleep && (req->sleepTimeMs < sysSleepTime) )
            {
                sysSleepTime = req->sleepTimeMs;
            }
        }

        if ( canSleep && SYSTEM_ReadyToSleep() )
        {
            /* Start of sleep preparation */
            SystemTimerSuspend();
            SleepTimerStart( MS_TO_SLEEP_TICKS( sysSleepTime - PMM_WAKEUPTIME_MS ), PMM_Wakeup );
            pmmState = PMM_STATE_SLEEP;
            sleepReq = req;
            /* End of sleep preparation */

            /* Put the system to sleep */
            HAL_Sleep(req->sleep_mode);

            status = PMM_SLEEP_REQ_PROCESSED;
        }
    }
#endif /* CONF_PMM_ENABLE */
    return status;
}

/**
* \brief Wakeup from sleep
*/
void PMM_Wakeup(RTC_TIMER32_INT_MASK intCause, uintptr_t context)
{
#ifdef CONF_PMM_ENABLE
    uint64_t sleptTimeUs = 0;

    if (PMM_STATE_SLEEP == pmmState)
    {

        pmmState = PMM_STATE_ACTIVE;
        sleptTimeUs = SLEEP_TICKS_TO_US(SleepTimerGetElapsedTime());
        SleepTimerStop();

        SystemTimerSync(sleptTimeUs);
        if (sleepReq && sleepReq->pmmWakeupCallback)
        {
            sleepReq->pmmWakeupCallback(US_TO_MS(sleptTimeUs));
            sleepReq = NULL;
        }
    }
#endif /* CONF_PMM_ENABLE */
}

/* eof pmm.c */
