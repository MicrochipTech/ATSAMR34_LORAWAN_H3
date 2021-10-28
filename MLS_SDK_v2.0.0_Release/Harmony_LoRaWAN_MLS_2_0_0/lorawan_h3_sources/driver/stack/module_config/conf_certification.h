/**
* \file  conf_certification.h
*
* \brief Application Configuration
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




#ifndef ENDDEVICE_CERT_CONF_H_
#define ENDDEVICE_CERT_CONF_H_

/****************************** INCLUDES **************************************/

/****************************** MACROS **************************************/

/**** EndDevice Certification Macros ****/
#if (CERT_APP == 1)

#define CERT_APP_FPORT                          1
#define TEST_PORT_NB                            224
#define DEACTIVATE_MODE                         0
#define ACTIVATE_MODE                           1
#define CNF_MODE                                2
#define UNCNF_MODE                              3
#define CRYPTO_MODE                             4
#define LINK_CHECK_MODE                         5
#define OTAA_TRIGGER_MODE                       6
#define LINK_CHECK_ANS_CID                      2
#define UPLINK_NO_RESPONSE_NB                   128
#define ON                                      1
#define OFF                                     0
#define NOT_JOINED                              0
#define JOINED                                  1

/*Define the Sub band of Channels to be enabled by default for the application*/
#define SUBBAND 1
#if ((SUBBAND < 1 ) || (SUBBAND > 8 ) )
#error " Invalid Value of Subband"
#endif


/* Activation method constants */
#define OVER_THE_AIR_ACTIVATION                     LORAWAN_OTAA
#define ACTIVATION_BY_PERSONALIZATION               LORAWAN_ABP

/* Message Type constants */
#define UNCONFIRMED                                 LORAWAN_UNCNF
#define CONFIRMED                                   LORAWAN_CNF

/* Enable one of the activation methods */
#define CERT_APP_ACTIVATION_TYPE                OVER_THE_AIR_ACTIVATION
//#define CERT_APP_ACTIVATION_TYPE              ACTIVATION_BY_PERSONALIZATION

/* Certification is available only for Class A device */
#define CERT_APP_ENDDEVICE_CLASS                CLASS_A

/* Select the Type of Transmission - Confirmed(CNF) / Unconfirmed(UNCNF) */
#define CERT_APP_TRANSMISSION_TYPE              UNCONFIRMED
//#define CERT_APP_TRANSMISSION_TYPE            CONFIRMED

#define CERT_APP_TIMEOUT                        5000 //ms

/* FPORT Value (1-255) */
#define CERT_APP_FPORT                           1

/* ABP Join Parameters */
/* 20202020 */
#define CERT_DEVICE_ADDRESS                     0x20202020
/* 12345678123456781234567812345678 */
#define CERT_APPLICATION_SESSION_KEY            {0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78}
/* ABCDABCDABCDABCDABCDABCDABCDABCD */
#define CERT_NETWORK_SESSION_KEY                {0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD}

/* OTAA Join Parameters */
/* 1234567812345678 */
#define CERT_DEVICE_EUI                         {0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78}
/* ABCDABCDABCDABCD */
#define CERT_APPLICATION_EUI                    {0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD}
/* 1234567812345678ABCDABCDABCDABCD */
#define CERT_APPLICATION_KEY                    {0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD, 0xAB, 0xCD}

#endif /* CERT_APP == 1 */

#endif /* ENDDEVICE_CERT_CONF_H_ */
