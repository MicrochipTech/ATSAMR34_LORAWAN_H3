/*******************************************************************************
  SAL configuration header

  File Name:
    conf_sal.h

  Summary:
    This file contains the sal configuration settings

  Description:
    This file contains the sal configuration settings. This file must be
    included in MLS project to configure the sal functionalities.

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

#ifndef CONF_SAL_H
#define CONF_SAL_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

<#if MLSSRC_COMBO_APPPROVSOURCE == "SECURE_ELEMENT">
#define CRYPTO_DEV_ENABLED
<#else>
//#define CRYPTO_DEV_ENABLED
</#if>

<#if MLSSRC_BOOLEAN_SAL_SNASDEVEUI == true>
#define SERIAL_NUM_AS_DEV_EUI       (1)
<#else>
#define SERIAL_NUM_AS_DEV_EUI       (0)
</#if>

#define APP_KEY_SLOT                (0)
#define APP_KEY_SLOT_BLOCK          (1)
#define APPS_KEY_SLOT               (2)
#define NWKS_KEY_SLOT               (3)
#define MCAST_APPS_KEY_SLOT         (11)
#define MCAST_NWKS_KEY_SLOT         (12)
#define KEK_SLOT                    (14)
#define APP_EUI_SLOT                (9)
#define DEV_EUI_SLOT                (10)


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* CONF_SAL_H */
/*******************************************************************************
 End of File
*/
