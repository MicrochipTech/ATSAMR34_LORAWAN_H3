/**
* \file  sys.h
*
* \brief Sytem management module include  file
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


 
#ifndef _SYSTEM_H
#define	_SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "definitions.h"
    
#define INTERRUPT_GlobalInterruptEnable  SYS_INT_Enable
#define INTERRUPT_GlobalInterruptDisable SYS_INT_Disable

#define cpu_irq_save              SYS_INT_Disable
#define cpu_irq_restore           SYS_INT_Restore

static inline void delay_cycles(
		const uint32_t n)
{
	if (n > 0) {
        SYSTICK_TimerPeriodSet(n);
		SysTick->VAL = 0;

		while (!SYSTICK_TimerPeriodHasExpired()){
		};
	}
}

void SystemBlockingWaitMs(uint32_t ms);
void delay_init(void);
void delay_us(uint32_t n);
void delay_ms(uint32_t n);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYSTEM_H */

