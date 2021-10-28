/**
* \file  radio_task_manager.c
*
* \brief This is the Radio Driver Task Manager source file which contains Radio task
*		 scheduler of the Radio Driver
*
*/
//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (C) 2020-21 released Microchip Technology Inc. All rights reserved.

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
*******************************************************************************/
//DOM-IGNORE-END

/******************************************************************************
                   Includes section
******************************************************************************/
#include "radio_task_manager.h"
#include "atomic.h"
#include <stdint.h>

/************************************************************************/
/*  Static variables                                                    */
/************************************************************************/

/**************************************************************************//**
\brief radioTaskFlags - 16-bit bitmap for the tasks of RADIO layer.
******************************************************************************/
static volatile uint16_t radioTaskFlags = 0x0000u;

/**************************************************************************//**
\brief Array of radio task handlers.
******************************************************************************/
static SYSTEM_TaskStatus_t (*radioTaskHandlers[RADIO_TASKS_COUNT])(void) = {
    /* In the order of descending priority */
    RADIO_TxDoneHandler,
    RADIO_RxDoneHandler,
    RADIO_TxHandler,
    RADIO_RxHandler,
	RADIO_ScanHandler
    /* , RADIO_SleepHandler */
};

/******************************************************************************
                   Prototypes section
******************************************************************************/
SYSTEM_TaskStatus_t RADIO_TaskHandler(void);

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Set task for RADIO task manager.

\param[in] id - a single value from the type RadioTaskIds_t
******************************************************************************/
void radioPostTask(RadioTaskIds_t id)
{
    ATOMIC_SECTION_ENTER
    radioTaskFlags |= id;
    ATOMIC_SECTION_EXIT

    /* Also post a RADIO task to the system */
    SYSTEM_PostTask(RADIO_TASK_ID);
}

/**************************************************************************//**
\brief Clear task for RADIO task manager.

\param[in] id - a single value from the type RadioTaskIds_t
******************************************************************************/
void radioClearTask(RadioTaskIds_t id)
{
    ATOMIC_SECTION_ENTER
    radioTaskFlags &= ~id;
    ATOMIC_SECTION_EXIT
}

/**************************************************************************//**
\brief RADIO task handler.
******************************************************************************/
SYSTEM_TaskStatus_t RADIO_TaskHandler(void)
{
#ifdef UT_D
    printf("\n Starting RADIO_TaskHandler() \n");
#endif

    if (radioTaskFlags)
    {
        for (uint16_t taskId = 0; taskId < RADIO_TASKS_COUNT; taskId++)
        {
            if ((1 << taskId) & (radioTaskFlags))
            {

#ifdef UT_D
                printf("\n radioTaskFlags : %d \n", radioTaskFlags);
#endif

                ATOMIC_SECTION_ENTER
                radioTaskFlags &= ~(1 << taskId);
                ATOMIC_SECTION_EXIT

#ifdef UT_D
                printf("\n radioTaskFlags : %d \n", radioTaskFlags);
#endif

                radioTaskHandlers[taskId]();

                if (radioTaskFlags)
                {
                    SYSTEM_PostTask(RADIO_TASK_ID);
                }
                
                break;
            }
        }
    }
    /*
     * else
     * {
     *   radioPostTask(RADIO_SLEEP_TASK_ID);
       * SYSTEM_PostTask(RADIO_TASK_ID);
     * }
     */

    return SYSTEM_TASK_SUCCESS;
}

/* eof radio_task_manager.c */
