/**
* \file  radio_transaction.h
*
* \brief This is the radio_transaction header file which contains Transmit,
*        Receive and Interrupt handling interfaces.
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




#ifndef _RADIO_TRANSACTION_H
#define _RADIO_TRANSACTION_H


/************************************************************************/
/*  Includes                                                            */
/************************************************************************/
#include "radio_interface.h"
#include <stdint.h>
#include <stddef.h>

/************************************************************************/
/*  Defines                                                            */
/************************************************************************/
#define RADIO_LORA_BUFFER_SPACE     271u
#define RADIO_FSK_BUFFER_SPACE      64u
#define RADIO_BUFFER_SIZE           RADIO_LORA_BUFFER_SPACE

#define RADIO_RFCTRL_RX             (0u)
#define RADIO_RFCTRL_TX             (1u)

// FIFO Rx FIFO Threshold set to these number of bytes
#define RADIO_RX_FIFO_LEVEL         (63u)
// FIFO Tx FIFO Threshold set to these number of bytes
#define RADIO_TX_FIFO_LEVEL         (32u)

#define NON_BLOCKING_REQ            0
#define BLOCKING_REQ                1

/************************************************************************/
/*  Global variables                                                    */
/************************************************************************/

/*********************************************************************//**
\brief  Possible events from DIO's and timers
*************************************************************************/
typedef struct _RadioEvents_t
{
    uint16_t LoraTxDoneEvent : 1;
    uint16_t LoraRxDoneEvent : 1;
    uint16_t FskTxDoneEvent : 1;
    uint16_t FskRxDoneEvent : 1;
    uint16_t TxWatchdogTimoutEvent : 1;
    uint16_t RxWatchdogTimoutEvent : 1;
    uint16_t LoraRxTimoutEvent : 1;
    uint16_t FskRxTimoutEvent : 1;
    uint16_t RxError : 1;
    uint16_t LbtScanDoneEvent : 1;
    uint16_t reserved : 6;
} RadioEvents_t;

/*********************************************************************//**
\brief  Possible callback events registration
*************************************************************************/
typedef union _RadioCallbackMask_t
{
    struct _BitMask_
    {
        uint8_t radioRxDoneCallback : 1;
        uint8_t radioTxDoneCallback : 1;
        uint8_t radioTxTimeoutCallback : 1;
        uint8_t radioRxTimeoutCallback : 1;
        uint8_t radioRxErrorCallback : 1;
        uint8_t radioFhssfreqCallback : 1;
        uint8_t reserved : 2;
    } BitMask;
    uint8_t callbackMask;
} RadioCallbackMask_t;

/************************************************************************/
/*  Prototypes                                                    */
/************************************************************************/
/*********************************************************************//**
\brief  This function is the callback function for watchdog timer
        timeout.

\param time - The watchdog timeout time.
\return     - none
*************************************************************************/
void Radio_WatchdogTimeout(uint8_t time);

/*********************************************************************//**
\brief  This function is triggered by a timer timeout in FSK mode to save
        Rx power.

\param time - The time for which the timeout was started.
\return     - none
*************************************************************************/
void Radio_RxFSKTimeout(uint8_t time);

/*********************************************************************//**
\brief This function sets the radio state.

\param state - The state of the radio to be set to.
*************************************************************************/
void RadioSetState(RadioState_t state);

/*********************************************************************//**
\brief This function is to Set RF front End Control.

\param type - RX = false/0, TX = true/1.
*************************************************************************/
void Radio_EnableRfControl(bool type);
/*********************************************************************//**
\brief This function is to Reset RF front End Control.

\param type - RX = false/0, TX = true/1.
*************************************************************************/
void Radio_DisableRfControl(bool type);
/*********************************************************************//**
\brief  This function sets the clock input to Radio.
        It will inform the radio from which clock it is sourced

\param   - None
\return  - None.
*************************************************************************/
void Radio_SetClockInput(void);

/*********************************************************************//**
\brief  This function power off/Resets the clock source of Radio

\param   - None
\return  - None.
*************************************************************************/
void Radio_ResetClockInput(void);

/*********************************************************************//**
\brief  This function handles the payload transfer of bytes from buffer
        to FIFO.

\param[in] buffer Pointer to the data to be written into the frame buffer
\param[in] bufferLen Length of the data to be written
\return     - none
*************************************************************************/
void Radio_FSKTxPayloadHandler(uint8_t *buffer, uint8_t bufferLen);



#endif  /*_RADIO_TRANSACTION_H*/

// eof radio_transaction.h
