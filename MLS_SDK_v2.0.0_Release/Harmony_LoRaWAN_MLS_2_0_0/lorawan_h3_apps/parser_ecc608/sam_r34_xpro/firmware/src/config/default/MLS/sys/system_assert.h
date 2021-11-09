/**
* \file  system_assert.h
*
* \brief This has all the dependencies for LoRaWAN system assertion
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



#ifndef SYSTEM_ASSERT_H
#define SYSTEM_ASSERT_H
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include <stdint.h>
#include <stddef.h>
/******************************************************************************/
/* Type definitions                                                            */
/******************************************************************************/
typedef enum _SystemAssertLevel_t
{
    ASSERT_INFO,
    ASSERT_ERROR,
    ASSERT_FATAL
} SystemAssertLevel_t;

typedef void(*SystemAssertCb_t)(SystemAssertLevel_t level, uint16_t assertNum);

#if (_DEBUG_ == 1)
#define SYS_ASSERT_FATAL(num)   SYSTEM_Assert(ASSERT_FATAL, num)
#define SYS_ASSERT_ERROR(num)   SYSTEM_Assert(ASSERT_ERROR, num)
#define SYS_ASSERT_INFO(num)    SYSTEM_Assert(ASSERT_INFO, num)
#else /* #if (_DEBUG_ == 1) */
#define SYS_ASSERT_FATAL(num)
#define SYS_ASSERT_ERROR(num)
#define SYS_ASSERT_INFO(num)
#endif /* #if (_DEBUG_ == 1) */

/* 4-bits - Module id, 12-bits - assert number */

/* Module ID */
#define ASSERT_APP      (0x0000)
#define ASSERT_MAC      (0x0100)
#define ASSERT_RADIO    (0x0200)
#define ASSERT_HAL      (0x0300)

/* Module specific asserts */
/* APP */
#define ASSERT_APP_GPSTIMEUNKNOWN_FAIL          (ASSERT_APP|1)
/* MAC */
#define ASSERT_MAC_RX1CALLBACK_RXFAIL           (ASSERT_MAC|1)
#define ASSERT_MAC_TXRETRY_RXSTOPFAIL           (ASSERT_MAC_RX1CALLBACK_RXFAIL+1)
#define ASSERT_MAC_AUTOREPLY_RXSTATEFAIL        (ASSERT_MAC_TXRETRY_RXSTOPFAIL+1)
#define ASSERT_MAC_UNCNFTXRETRY_RXSTATEFAIL     (ASSERT_MAC_AUTOREPLY_RXSTATEFAIL+1)
#define ASSERT_MAC_UNCNFTXRETRY_RXSTOPFAIL      (ASSERT_MAC_UNCNFTXRETRY_RXSTATEFAIL+1)
#define ASSERT_MAC_CONFIGRX2_RXFAIL             (ASSERT_MAC_UNCNFTXRETRY_RXSTOPFAIL+1)
#define ASSERT_MAC_SETEDCLASS_RXSTOPFAIL        (ASSERT_MAC_CONFIGRX2_RXFAIL+1)
#define ASSERT_MAC_PAUSE_RXSTOPFAIL             (ASSERT_MAC_SETEDCLASS_RXSTOPFAIL+1)
#define ASSERT_MAC_RXCALLBACK_RXSTOPFAIL        (ASSERT_MAC_PAUSE_RXSTOPFAIL+1)
#define ASSERT_MAC_CLASSCRX2TIMEOUT_STATEFAIL   (ASSERT_MAC_RXCALLBACK_RXSTOPFAIL+1)
#define ASSERT_MAC_CLASSCJOIN_STATEFAIL			(ASSERT_MAC_CLASSCRX2TIMEOUT_STATEFAIL+1)
/* HAL */
#define ASSERT_HAL_TIMERID_EXHAUSTED            (ASSERT_HAL|1)
#define ASSERT_HAL_TIMER_START_FAILURE          (ASSERT_HAL|2)
#define ASSERT_HAL_TIMER_STOP_FAILURE           (ASSERT_HAL|3)
#define ASSERT_HAL_TIMESTAMPID_EXHAUSTED        (ASSERT_HAL|4)

/******************************************************************************/
/* Function declarations                                                         */
/******************************************************************************/
#if (_DEBUG_ == 1)
void SYSTEM_Assert(SystemAssertLevel_t level, uint16_t assertNum);
void SYSTEM_AssertSubscribe(SystemAssertCb_t cb);
#endif /* #if (_DEBUG_ == 1) */
/* eof system_assert.h */


#endif /* #ifndef SYSTEM_ASSERT_H */
