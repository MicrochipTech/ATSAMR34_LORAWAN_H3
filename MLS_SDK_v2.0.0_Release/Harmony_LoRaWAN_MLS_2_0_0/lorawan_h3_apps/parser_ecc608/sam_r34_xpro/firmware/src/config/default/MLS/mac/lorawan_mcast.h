/**
 * \file  lorawan_mcast.h
 *
 * \brief LoRaWAN header file for multicast data & control definition(classB & classC)
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
#ifndef _LORAWAN_MCAST_H_
#define _LORAWAN_MCAST_H_

/***************************** TYPEDEFS ***************************************/

/*************************** FUNCTIONS PROTOTYPE ******************************/

/*********************************************************************//**
\brief	Multicast - initialization of variables and states

\return					- none.
*************************************************************************/
void LorawanMcastInit(void);

/*********************************************************************//**
\brief	Check if the incoming packet is a multicast group the device
        supports
\param[in]  hdr - mac header of the received frame
\param[in]  mType - message type of the received frame
\param[in]  fPort - frame port of the received frame
\return	    LORAWAN_SUCCESS, if successfully validated
            LORAWAN_INVALID_PARAMETER, otherwise
*************************************************************************/
StackRetStatus_t LorawanMcastValidateHdr(Hdr_t *hdr, uint8_t mType, uint8_t fPort, uint8_t* groupId);

/*********************************************************************//**
\brief	Decrypt the packet and provide callback to application
\param[in,out]  buffer  - placeholder for input and output data
\param[in]      bufferLength - length of the received packet
\param[in]      hdr - mac header of the received packet
\return	LORAWAN_SUCCESS, if successfully processed
        LORAWAN_INVALID_PARAMETER, otherwise
*************************************************************************/
StackRetStatus_t LorawanMcastProcessPkt(uint8_t* buffer, uint8_t bufferLength, Hdr_t *hdr, uint8_t groupId);

/*********************************************************************//**
\brief	Multicast enable/disable configuration function
\param[in]  enable - notifies whether to enable or disable multicast
\return	LORAWAN_SUCCESS, if successfully enabled
        LORAWAN_INVALID_PARAMETER, otherwise
*************************************************************************/
StackRetStatus_t LorawanMcastEnable(bool enable, uint8_t groupid);

StackRetStatus_t LorawanAddMcastAddr(uint32_t mcast_devaddr, uint8_t groupId);

StackRetStatus_t LorawanAddMcastAppskey(uint8_t * appSkey, uint8_t groupId);

StackRetStatus_t LorawanAddMcastNwkskey(uint8_t * nwkSkey, uint8_t groupId);

StackRetStatus_t LorawanAddMcastFcntMin(uint32_t cnt, uint8_t groupId);
StackRetStatus_t LorawanAddMcastFcntMax(uint32_t cnt, uint8_t groupId);

StackRetStatus_t LorawanAddMcastDlFrequency(uint32_t dlFreq, uint8_t groupId);
StackRetStatus_t LorawanAddMcastDatarate(uint8_t dr, uint8_t groupId);
StackRetStatus_t LorawanAddMcastPeriodicity(uint8_t periodicity, uint8_t groupId);
#endif // _LORAWAN_MCAST_H_

//eof lorawan_mcast.h
