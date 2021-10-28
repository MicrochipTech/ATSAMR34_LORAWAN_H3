/*******************************************************************************
  MAC configuration header

  File Name:
    conf_stack.h

  Summary:
    This file contains the MAC configuration settings

  Description:
    This file contains the MAC configuration settings. This file must be
    included in MLS project to configure the MAC functionalities.

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

#ifndef CONF_STACK_H
#define CONF_STACK_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

//------------------------------------------------------------------------------
// Includes MAC specific configurations
//------------------------------------------------------------------------------
//
// NOTE: This file MUST be included after 'lorawan.h'
//
<#if MLSSRC_BOOLEAN_ENABLECLASSC == true>
// Both classes A and C are supported
#define LORAWAN_SUPPORTED_ED_CLASSES    (CLASS_A | CLASS_C)
// This enables class-C option in LoRaWAN layer
#define FEATURE_CLASSC                  (1)
// Class-C enables multicasting
#define FEATURE_DL_MCAST                (1)
<#else>
// Class-A is always enabled in LoRaWAN
#define LORAWAN_SUPPORTED_ED_CLASSES    (CLASS_A)
// Class-A does not have multicasting option as per specification
#define FEATURE_DL_MCAST                (0)
</#if>

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* CONF_STACK_H */
/*******************************************************************************
 End of File
*/
