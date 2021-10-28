/**
* \file  sys.c
*
* \brief System management file
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

  
#include "sys.h"
#include "atomic.h"

bool interrupt_flag = false;
static uint32_t cycles_per_ms = 48000000UL / 1000;
static uint32_t cycles_per_us = 48000000UL / 1000000;

/** 
 * \brief Performs a blocking delay
 * \param[in] ms Delay time in milliseconds
 */
void SystemBlockingWaitMs(uint32_t ms)
{
    delay_ms(ms);
}

void system_enter_critical_section(void)
{
    interrupt_flag = SYS_INT_Disable();
}

void system_leave_critical_section(void)
{
    SYS_INT_Restore(interrupt_flag);
    interrupt_flag = false;
}

/**
 * \brief Initialize the delay.
 *
 * This must be called during start up to initialize the delay routine with
 * the current used main clock. It must run any time the main CPU clock is changed.
 */
void delay_init(void)
{
   cycles_per_ms = SYSTICK_TimerFrequencyGet();
   cycles_per_ms /= 1000;
   cycles_per_us = cycles_per_ms / 1000;
   SYSTICK_TimerStart();
}

/**
 * \brief Delay loop to delay at least n number of microseconds
 *
 * \param n  Number of microseconds to wait
 */
void delay_us(
		uint32_t n)
{
	while (n--) {
		/* Divide up to blocks of 10u */
		delay_cycles(cycles_per_us);
	}
}

/**
 * \brief Delay loop to delay at least n number of milliseconds
 *
 * \param n  Number of milliseconds to wait
 */
void delay_ms(
		uint32_t n)
{
	while (n--) {
		/* Divide up to blocks of 1ms */
		delay_cycles(cycles_per_ms);
	}
}
