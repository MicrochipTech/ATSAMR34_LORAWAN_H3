/*******************************************************************************
  SWTIMER configuration header

  File Name:
    conf_swtimer.h

  Summary:
    This file contains the swtimer configuration settings

  Description:
    This file contains the swtimer configuration settings. This file must be
    included in MLS project to configure the swtimer functionalities.

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

#ifndef CONF_SWTIMER_H
#define CONF_SWTIMER_H

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

//------------------------------------------------------------------------------
// Includes swtimer specific configurations
//------------------------------------------------------------------------------
<#if MLSSRC_COMBO_CONFTYPE == "Auto">
// Maximum number of SW timers
#define TOTAL_NUMBER_OF_SW_TIMERS   (25)    

// Maximum number of SWTimer Timestamps
#define TOTAL_NUMBER_SW_TIMESTAMPS  (2)
<#else>
// Maximum number of SW timers
#define TOTAL_NUMBER_OF_SW_TIMERS   (${MLSSRC_INTEGER_SWTIMERMAXTIMERS})    

// Maximum number of SWTimer Timestamps
#define TOTAL_NUMBER_SW_TIMESTAMPS  (${MLSSRC_INTEGER_SWTIMERMAXTIMESTAMPS})
</#if>
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* CONF_SWTIMER_H */
/*******************************************************************************
 End of File
*/
