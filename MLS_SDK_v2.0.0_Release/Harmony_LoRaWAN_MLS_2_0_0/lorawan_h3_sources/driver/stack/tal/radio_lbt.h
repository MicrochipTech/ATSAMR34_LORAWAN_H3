/**
* \file  radio_lbt.h
*
* \brief This is the Radio LBT header file which contains listen before talk specific
*       Radio functions declarations and defines for SX1276
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




/*#ifdef LBT*/

#ifndef RADIO_LBT_H_
#define RADIO_LBT_H_

/******************************************************************************
                   Includes section
******************************************************************************/
#include "system_task_manager.h"
#include "stdint.h"

/******************************************************************************
                   Defines section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*********************************************************************//**
\brief  This function is triggered by the scan done event and it sets up
        the radio for scanning.

\param  - none
\return - returns the success or failure of a task
*************************************************************************/
SYSTEM_TaskStatus_t radioScanDoneHandler(void);

/*********************************************************************//**
\brief  This function is the callback function for LBT scan timer
        timeout.

\param time - not used.
\return     - none
*************************************************************************/
void Radio_LBTScanTimeout(uint8_t time);

/*#endif LBT*/
#endif /* RADIO_LBT_H_ */