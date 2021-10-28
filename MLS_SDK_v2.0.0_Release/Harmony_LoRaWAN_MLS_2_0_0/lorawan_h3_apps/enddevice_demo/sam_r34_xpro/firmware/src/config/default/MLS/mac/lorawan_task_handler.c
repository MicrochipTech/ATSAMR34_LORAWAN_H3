/**
* \file  lorawan_task_handler.c
*
* \brief LoRaWAN Task Handler file
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
 
/*****************************************************************************/
/*  Includes                                                                 */
/*****************************************************************************/
#include "lorawan.h"
#include "lorawan_private.h"
#include "lorawan_task_handler.h"
#include "radio_interface.h"
#include "sw_timer.h"
#include "system_task_manager.h"
#include "atomic.h"
#include "lorawan_reg_params.h"
#include "lorawan_radio.h"
#include "system_assert.h"

/******************************************************************************/
/*                      Static variables                                      */
/******************************************************************************/
static SYSTEM_TaskStatus_t (*lorawanHandlers[LORAWAN_TASKS_SIZE])(void) =
{	
	LORAWAN_JoinReqHandler,
    LORAWAN_TxHandler,
    LORAWAN_RxHandler
};

/******************************************************************************
                   Prototypes section
******************************************************************************/
SYSTEM_TaskStatus_t LORAWAN_TaskHandler(void);

/*******************************************************************************
                        Extern Variables
*******************************************************************************/
extern LoRa_t loRa;
extern uint8_t macBuffer[];
extern RadioCallbackID_t callbackBackup;

/******************************************************************************
                        Global variables section
 ******************************************************************************/
volatile static lorawanTaskID_t lorawanTaskBitMap = 0U;


/******************************************************************************
                           Implementations section
 ******************************************************************************/
/**************************************************************************//**
  \brief Prepare to run same LORAWAN task handler.

  \param[in] taskId - identifier of LORAWAN task.
  \return None.
 ******************************************************************************/
void LORAWAN_PostTask(const lorawanTaskID_t taskID)
{
	ATOMIC_SECTION_ENTER
    lorawanTaskBitMap |= (1U << taskID);
	ATOMIC_SECTION_EXIT
    SYSTEM_PostTask(LORAWAN_TASK_ID);
}

/**************************************************************************//**
  \brief Global task handler of LORAWAN layer.

  \param[in] None
  \return

 ******************************************************************************/
SYSTEM_TaskStatus_t LORAWAN_TaskHandler(void)
{
	while (lorawanTaskBitMap)
	{
		for (uint8_t task_id = 0; task_id < LORAWAN_TASKS_SIZE; task_id++ )
		{
			if(lorawanTaskBitMap & ( 1 << task_id))
			{
				ATOMIC_SECTION_ENTER
				lorawanTaskBitMap &= ~( 1U << task_id);
				ATOMIC_SECTION_EXIT

				lorawanHandlers[task_id]();
                break;
			}
		}
	}

    return SYSTEM_TASK_SUCCESS;
}

/**************************************************************************//**
  \brief Transmit subtask handler for LORAWAN MAC

  \param[in] None
  \return processing status

 ******************************************************************************/
SYSTEM_TaskStatus_t LORAWAN_TxHandler(void)
{
   StackRetStatus_t result;
   RadioTransmitParam_t RadioTransmitParam;
   radioConfig_t radioConfig;
   NewTxChannelReq_t newTxChannelReq;

	newTxChannelReq.transmissionType = true;
	newTxChannelReq.txPwr = loRa.txPower;
	newTxChannelReq.currDr = loRa.currentDataRate;

	result = LORAREG_GetAttr (NEW_TX_CHANNEL_CONFIG,&newTxChannelReq,&radioConfig);
	if (result != LORAWAN_SUCCESS)
	{     /* Send Status as NO_CHANNEL_FOUND */
			/* Transaction complete Event */
			UpdateTransactionCompleteCbParams(result);//get attr result status
	}
    else
    {
		/* Close the receive window in case of Class C device */
		if(CLASS_C == loRa.edClass)
		{
			RadioReceiveParam_t receive_param;
			receive_param.action = RECEIVE_STOP;

			RADIO_Receive(&receive_param);
		}

		ConfigureRadioTx(radioConfig);
        LorawanSendReq_t *LoRaCurrentSendReq = (LorawanSendReq_t *)loRa.appHandle;
        if(NULL != LoRaCurrentSendReq)
        {
			/*Retransmission enabled for NON ACK packets , retx/reps count depends on Retransmission or repetition count configured*/
			loRa.retransmission = ENABLED;
            AssemblePacket(LoRaCurrentSendReq->confirmed, LoRaCurrentSendReq->port, LoRaCurrentSendReq->buffer, LoRaCurrentSendReq->bufferLength);
        }
        else
        {
			/*ACK or NULL packets sent on Port 0 are not retransmitted*/
			loRa.retransmission = DISABLED;
            /* Handling of Empty Unconfirmed Packet*/
            AssemblePacket(0, 0, NULL, 0);
        }

		RadioTransmitParam.bufferLen = loRa.lastPacketLength;
		RadioTransmitParam.bufferPtr = &macBuffer[16];
        RadioError_t status;
		status = RADIO_Transmit(&RadioTransmitParam);
        if (status == ERR_NONE)
		{
			loRa.macStatus.macState = TRANSMISSION_OCCURRING; // set the state of MAC to transmission occurring. No other packets can be sent afterwards
		}
		else
        {
            loRa.lorawanMacStatus.syncronization = DISABLED;
            /* Send Status as RADIO_BUSY */
            /* Transaction complete Event */
             UpdateTransactionCompleteCbParams((StackRetStatus_t)status);//radio transmitcallback

        }
        loRa.lorawanMacStatus.fPending = DISABLED; //clear the fPending flag
	}
   
   return SYSTEM_TASK_SUCCESS;
}

/**************************************************************************//**
  \brief Transmit subtask handler for Sending LORAWAN Join Request Messages

  \param[in] None
  \return processing status

 ******************************************************************************/
SYSTEM_TaskStatus_t LORAWAN_JoinReqHandler(void)
{
	StackRetStatus_t result;
	RadioTransmitParam_t RadioTransmitParam;
	radioConfig_t radioConfig;
	NewTxChannelReq_t newTxChannelReq;
	uint8_t bufferIndex;
	
	newTxChannelReq.transmissionType = false;
	newTxChannelReq.txPwr = loRa.txPower;
	newTxChannelReq.currDr = loRa.currentDataRate;
	if(loRa.featuresSupported & JOIN_BACKOFF_SUPPORT)
	{
	if(loRa.joinreqinfo.firstJoinReqTimestamp ==0)
	{
		loRa.joinreqinfo.isFirstJoinReq = true;
	}
	}
		
	result = LORAREG_GetAttr (NEW_TX_CHANNEL_CONFIG,&newTxChannelReq,&radioConfig);
	if (result != LORAWAN_SUCCESS)
	{
		SetJoinFailState(result);
	}
	else
	{  
		ConfigureRadioTx(radioConfig);			   
        if (CLASS_C == loRa.edClass)
        {
	        RadioReceiveParam_t RadioReceiveParam;

	        RadioReceiveParam.action = RECEIVE_STOP;
	        if (ERR_NONE != RADIO_Receive(&RadioReceiveParam))
	        {
		        SYS_ASSERT_ERROR(ASSERT_MAC_CLASSCJOIN_STATEFAIL);
	        }
        }	
		/*Join Requests are not retransmitted*/
		loRa.retransmission = DISABLED;		
		bufferIndex = PrepareJoinRequestFrame ();	
		RadioTransmitParam.bufferLen = bufferIndex;					
		RadioTransmitParam.bufferPtr = (uint8_t *)&macBuffer;
		if (RADIO_Transmit(&RadioTransmitParam) != ERR_NONE)
		{
			SetJoinFailState(LORAWAN_TX_TIMEOUT);
		}
		else
		{

			loRa.macStatus.macState = TRANSMISSION_OCCURRING;	
		}
		
	}

   return SYSTEM_TASK_SUCCESS;
}

/**************************************************************************//**
  \brief Receive subtask handler for LORAWAN MAC

  \param[in] None
  \return processing status

 ******************************************************************************/
SYSTEM_TaskStatus_t LORAWAN_RxHandler(void)
{
	switch(callbackBackup)
	{
		case RADIO_RX_DONE_CALLBACK:
		case RADIO_RX_ERROR_CALLBACK:
		{
			uint8_t *data;
			uint16_t dataLen;

			/* Buffer length is not checked as it can be 0 for error case */
			RADIO_GetData(&data, &dataLen);
			if (NULL != data)
			{
				LORAWAN_RxDone(data, dataLen);
			}
		}
		break;

		case RADIO_RX_TIMEOUT_CALLBACK:
		{
			LORAWAN_RxTimeout();
		}
		break;

		default:
		{
			/* dont know what step to take. hence do nothing for now */
		}
		break;
	}
	return SYSTEM_TASK_SUCCESS;
}
 
