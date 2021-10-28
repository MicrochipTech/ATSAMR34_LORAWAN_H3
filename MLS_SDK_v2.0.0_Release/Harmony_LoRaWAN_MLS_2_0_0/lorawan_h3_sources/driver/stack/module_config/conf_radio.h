/**
* \file  conf_radio.h
*
* \brief This is the radio configuration file
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

#ifndef _CONF_RADIO_H
#define _CONF_RADIO_H

#define RFSWITCH_ENABLE

/* Possible Radio clock sources */
#define TCXO_OSC                0
#define XTAL_OSC                1

/* Clock source for SX1276 radio */
#define RADIO_CLK_SRC        TCXO_OSC

#if (RADIO_CLK_SRC == TCXO_OSC)
#define TCXO_ENABLE
#endif

/* Delay in ms for TCXO to stabilize */
#define RADIO_CLK_STABILITATION_DELAY       2

/* Uncomment the below macro to make the TCXO oscillator always ON
   irrespective of Transceiver state (Even if it is in SLeep state) */
//#define TCXO_ALWAYS_ON

#endif /* _CONF_RADIO_H */
