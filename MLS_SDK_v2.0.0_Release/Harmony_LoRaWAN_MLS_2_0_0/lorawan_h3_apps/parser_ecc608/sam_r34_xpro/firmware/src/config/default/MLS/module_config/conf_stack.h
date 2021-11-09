/**
* \file  conf_stack.h
*
* \brief LORAWAN STack Configuration File
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


 

#ifndef CONF_STACK_H_INCLUDED
#define CONF_STACK_H_INCLUDED

/*****************************************************************************/
/* LoRaWAN MAC layer configuration parameters                                */
/*****************************************************************************/
#define FEATURE_CLASSC 1

#if (FEATURE_CLASSC == 1)
#define FEATURE_DL_MCAST 1
#else
#define FEATURE_DL_MCAST 0
#endif

#if (FEATURE_CLASSC == 1)
#define LORAWAN_SUPPORTED_ED_CLASSES                (CLASS_A | CLASS_C)
#else
#define LORAWAN_SUPPORTED_ED_CLASSES                CLASS_A
#endif

#endif /* CONF_STACK_H_INCLUDED */

/* eof conf_stack.h */
