/**
* \file  sleep_timer.h
*
* \brief Sleep timer interface
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




#ifndef SLEEP_TIMER_H_INCLUDED
#define SLEEP_TIMER_H_INCLUDED

#include "conf_pmm.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef CONF_PMM_ENABLE
/**************************************** INCLUDES*****************************/
#include <stdint.h>
#include "definitions.h"

#define     COMPARE_COUNT_MAX_VALUE     (0xFFFFFFFF)

#define     US_TO_SLEEP_TICKS(u)        ((u) * (0.03278f))
#define     SLEEP_TICKS_TO_US(s)        ((s) * (30.5175f))

#define     MS_TO_SLEEP_TICKS(m)        ((m) * (32.769f))
#define     SLEEP_TICKS_TO_MS(s)        ((s) * (0.0306f))

/***************************************PROTOTYPES**************************/
/**
* \brief Initializes the sleep timer module
*/
void SleepTimerInit(void);

/**
* \brief Start the sleep timer
*/
void SleepTimerStart(uint32_t sleepTicks, RTC_TIMER32_CALLBACK cb);

/**
* \brief Stop the sleep timer
*/
void SleepTimerStop(void);

/**
* \brief Calculate the Elapsed Time from the previous call of this function
* \retval Elapsed time in ticks
*/
uint32_t SleepTimerGetElapsedTime(void);

#endif /* CONF_PMM_ENABLE */

#ifdef  __cplusplus
}
#endif

#endif /* SLEEP_TIMER_H_INCLUDED */

/* eof sleep_timer.h */

