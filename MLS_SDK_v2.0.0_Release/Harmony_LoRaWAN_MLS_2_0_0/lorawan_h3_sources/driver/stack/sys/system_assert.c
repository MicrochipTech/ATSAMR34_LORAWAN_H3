/**
* \file  system_assert.c
*
* \brief This is the implementation of LoRaWAN system assertion
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



/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include "system_assert.h"

#if (_DEBUG_ == 1)
/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/
SystemAssertCb_t assertHandler = NULL;

/******************************************************************************/
/* Implementations                                                            */
/******************************************************************************/
/**************************************************************************//**
\brief Takes action based on assert called
******************************************************************************/
void SYSTEM_Assert(SystemAssertLevel_t level, uint16_t assertNum)
{
    switch (level)
    {
        case ASSERT_ERROR:
        case ASSERT_FATAL:
        {
          if (assertHandler)
          {
              assertHandler(level, assertNum);
          }
          while(1);
        }
        break;

        case ASSERT_INFO:
        {
          if (assertHandler)
          {
              assertHandler(level, assertNum);
          }
        }
        break;

        default:
            /* add optional handling here */
            break;
    }
}

/**************************************************************************//**
\brief Subscribes the handler function to be called on assert
******************************************************************************/
void SYSTEM_AssertSubscribe(SystemAssertCb_t cb)
{
    assertHandler = cb;
}

#endif /* #if (_DEBUG_ == 1) */

/* eof system_assert.c */

