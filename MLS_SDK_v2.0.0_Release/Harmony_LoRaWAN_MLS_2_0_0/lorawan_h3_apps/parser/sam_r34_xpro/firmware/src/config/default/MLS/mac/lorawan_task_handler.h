/**
 * \file  lorawan_task_handler.h
 *
 * \brief LoRaWAN Task Handler header file
 *		
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

#ifndef LORAWAN_TASK_HANDLER_H_
#define LORAWAN_TASK_HANDLER_H_

/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <system_task_manager.h>

/******************************************************************************
                              Types section
 ******************************************************************************/

/** External req identifiers. */
typedef enum {
    LORAWAN_JOIN_TASK_ID = 0u,
    LORAWAN_TX_TASK_ID = 1u,
    LORAWAN_RX_TASK_ID = 2u
} lorawanTaskID_t;

/******************************************************************************
                             Constants section
 ******************************************************************************/
#define LORAWAN_TASKS_SIZE         3u

/*************************** FUNCTIONS PROTOTYPE ******************************/

/** LORAWAN Subtask Handlers*/
SYSTEM_TaskStatus_t LORAWAN_TxHandler(void);

SYSTEM_TaskStatus_t LORAWAN_JoinReqHandler(void);

SYSTEM_TaskStatus_t LORAWAN_RxHandler(void);

/** Lorawan post task - Post a task to Lorawan Handler*/
void LORAWAN_PostTask(const lorawanTaskID_t taskID);

/** helper function for setting up radio for transmission */
void ConfigureRadioTx(radioConfig_t radioConfig);

#endif /* LORAWAN_TASK_HANDLER_H_ */
