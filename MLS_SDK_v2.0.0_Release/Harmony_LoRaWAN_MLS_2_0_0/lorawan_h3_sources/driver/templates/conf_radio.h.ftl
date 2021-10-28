/*******************************************************************************
  Radio configuration header

  File Name:
    conf_radio.h

  Summary:
    This file contains the radio configuration settings

  Description:
    This file contains the radio configuration settings. This file must be
    included in MLS project to configure the radio functionalities.

 *******************************************************************************/

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

#ifndef CONF_RADIO_H
#define CONF_RADIO_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

<#if MLSSRC_COMBO_CONFTYPE == "Auto">
//------------------------------------------------------------------------------
// Includes radio specific configurations
//------------------------------------------------------------------------------
// Possible Radio clock sources
#define TCXO_OSC    (0)
#define XTAL_OSC    (1)

// *****************************************************************************
// Enable RF switch
// *****************************************************************************
#define RFSWITCH_ENABLE

// *****************************************************************************
// Select oscillator to clock the radio
// *****************************************************************************
// Oscillator that clocks the radio
#define RADIO_CLK_SRC                   (TCXO_OSC)
// Stabilization delay for TCXO (unit: ms)
#define RADIO_CLK_STABILITATION_DELAY   (2)
// TCXO is enabled
#define TCXO_ENABLE
<#else>
//------------------------------------------------------------------------------
// Includes radio specific configurations
//------------------------------------------------------------------------------
// Possible Radio clock sources
#define TCXO_OSC    (0)
#define XTAL_OSC    (1)

<#if MLSSRC_BOOLEAN_RFSWITCHENABLE == true>
// *****************************************************************************
// Enable RF switch
// *****************************************************************************
#define RFSWITCH_ENABLE
</#if>

// *****************************************************************************
// Select oscillator to clock the radio
// *****************************************************************************
<#if MLSSRC_COMBO_RADIOCLOCKOSC == "TCXO">
// Oscillator that clocks the radio
#define RADIO_CLK_SRC                   (TCXO_OSC)
// Stabilization delay for TCXO (unit: ms)
#define RADIO_CLK_STABILITATION_DELAY   (2)
// TCXO is enabled
#define TCXO_ENABLE
<#elseif MLSSRC_COMBO_RADIOCLOCKOSC == "XTAL">
#define RADIO_CLK_SRC   (XTAL_OSC)
</#if>
</#if>
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* CONF_RADIO_H */
/*******************************************************************************
 End of File
*/
