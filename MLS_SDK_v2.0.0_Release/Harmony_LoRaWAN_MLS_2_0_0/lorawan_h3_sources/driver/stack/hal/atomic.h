/**
* \file  atomic.h
*
* \brief Atomic operations APIs
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
/*      DECIDE ON THE LICENSE TEXT                                      */
/************************************************************************/

#ifndef ATOMIC_H
#define ATOMIC_H

/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#ifdef UT
#include "lora_test_main.h"
#endif

/************************************************************************/
/* Function Prototypes                                                  */
/************************************************************************/
/**
 * \brief Enters a critical section.
 *
 * Disables global interrupts. To support nested critical sections, an internal
 * count of the critical section nesting will be kept, so that global interrupts
 * are only re-enabled upon leaving the outermost nested critical section.
 *
 */
void system_enter_critical_section(void);

/**
 * \brief Leaves a critical section.
 *
 * Enables global interrupts. To support nested critical sections, an internal
 * count of the critical section nesting will be kept, so that global interrupts
 * are only re-enabled upon leaving the outermost nested critical section.
 *
 */
void system_leave_critical_section(void);

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#ifdef UT
#define   ATOMIC_SECTION_ENTER
#define   ATOMIC_SECTION_EXIT
#else
#define   ATOMIC_SECTION_ENTER  system_enter_critical_section();
#define   ATOMIC_SECTION_EXIT   system_leave_critical_section();
#endif /* UT */
#endif /* ATOMIC_H */

/* eof atomic.h */
