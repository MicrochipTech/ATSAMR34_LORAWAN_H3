/**
* \file  sleep_timer.c
*
* \brief Sleep timer implementation
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


 

/**************************************** INCLUDES*****************************/
#include "definitions.h"
#include "sleep_timer.h"

#ifdef CONF_PMM_ENABLE
/**************************************** EXTERNS ****************************/

/************************************** IMPLEMENTATION************************/
/**
* \brief Initializes the sleep timer module
*/
void SleepTimerInit(void)
{
    RTC_Timer32InterruptDisable(RTC_TIMER32_INT_MASK_CMP0);
    RTC_Timer32Start();
}

/**
* \brief Calculate the Elapsed Time from the previous call of this function
* \retval Elapsed time in ticks
*/
uint32_t SleepTimerGetElapsedTime(void)
{
    return RTC_Timer32CounterGet();
}

/**
* \brief Initializes the sleep timer
*/
void SleepTimerStart(uint32_t sleepTicks, RTC_TIMER32_CALLBACK cb)
{
    RTC_Timer32CounterSet(0);
    RTC_Timer32CallbackRegister(cb,(uintptr_t)NULL);
    RTC_Timer32CompareSet(sleepTicks);
    RTC_Timer32InterruptEnable(RTC_TIMER32_INT_MASK_CMP0);
    
}

/**
* \brief Stop the sleep timer
*/
void SleepTimerStop(void)
{
    RTC_Timer32InterruptDisable(RTC_TIMER32_INT_MASK_CMP0);
}

#endif /* CONF_PMM_ENABLE */

/* eof sleep_timer.c */
