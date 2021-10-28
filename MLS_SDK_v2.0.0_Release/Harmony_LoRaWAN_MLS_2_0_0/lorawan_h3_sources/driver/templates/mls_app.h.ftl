<#if MLSSRC_BOOLEAN_APPCONFEN == true>
/*******************************************************************************
  MPLAB Harmony LORAWAN Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    mls_app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.
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
#ifndef MLS_APP_H
#define MLS_APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "conf_sal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Defines and types
// *****************************************************************************
// *****************************************************************************
#if (CERT_APP == 1)
#define CPC_PKG_ID                          (6)
#define CPC_PKG_VER                         (1)

#define CPC_PKG_VER_REQ_LEN                 (1)
#define CPC_PKG_VER_REQ                     (0x00)
#define CPC_PKG_VER_ANS                     CPC_PKG_VER_REQ

#define CPC_DUT_RESET_REQ_LEN               (1)
#define CPC_DUT_RESET_REQ                   (0x01)
#define CPC_DUT_RESET_ANS                   CPC_DUT_RESET_REQ

#define CPC_DUT_JOIN_REQ_LEN                (1)
#define CPC_DUT_JOIN_REQ                    (0x02)

#define CPC_SWITCH_CLASS_REQ_LEN            (2)
#define CPC_SWITCH_CLASS_REQ                (0x03)

#define CPC_ADR_BIT_CHANGE_REQ_LEN          (2)
#define CPC_ADR_BIT_CHANGE_REQ              (0x04)

#define CPC_REGDCYCLE_CTRL_REQ_LEN          (2)
#define CPC_REGDCYCLE_CTRL_REQ              (0x05)

#define CPC_TX_PERIOD_CHANGE_REQ_LEN        (2)
#define CPC_TX_PERIOD_CHANGE_REQ            (0x06)

//** can contain 0..N variable payload
#define CPC_TX_FRAMES_CTRL_REQ_LEN          (2)
#define CPC_TX_FRAMES_CTRL_REQ              (0x07)

//** can contain 0..N variable payload
#define CPC_ECHO_INC_PAYLOAD_REQ_LEN        (1)
#define CPC_ECHO_INC_PAYLOAD_REQ            (0x08)
#define CPC_ECHO_INC_PAYLOAD_ANS            CPC_ECHO_INC_PAYLOAD_REQ

#define CPC_RX_APP_CNT_REQ_LEN              (1)
#define CPC_RX_APP_CNT_REQ                  (0x09)
#define CPC_RX_APP_CNT_ANS                  CPC_RX_APP_CNT_REQ

#define CPC_RX_APP_CNT_RESET_REQ_LEN        (1)
#define CPC_RX_APP_CNT_RESET_REQ            (0x0A)

// ones that trigger MAC commands
#define CPC_LINK_CHECK_REQ_LEN              (1)
#define CPC_LINK_CHECK_REQ                  (0x20)

#define CPC_DEVICE_TIME_REQ_LEN             (1)
#define CPC_DEVICE_TIME_REQ                 (0x21)

#define CPC_PING_SLOT_INFO_REQ_LEN          (2)
#define CPC_PING_SLOT_INFO_REQ              (0x22)

// miscellaneous
#define CPC_TX_CW_REQ_LEN                   (7)
#define CPC_TX_CW_REQ                       (0x7D)

#define CPC_DUT_FPORT224_DISABLE_REQ_LEN    (1)
#define CPC_DUT_FPORT224_DISABLE_REQ        (0x7E)

#define CPC_DUT_VERSIONS_REQ_LEN            (1)
#define CPC_DUT_VERSIONS_REQ                (0x7F)
#define CPC_DUT_VERSIONS_ANS                CPC_DUT_VERSIONS_REQ

#define CPC_SYSRST_TIMER_PERIOD_MS          (1000)

#if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1)
#define WLR089U0_MACIEEEADDR_OFFSET         _UL_(0x0080400A)
#endif /* #if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1) */

#if (ENABLE_PDS == 1)
extern bool mlsAppIsCertModeEnabled;
extern bool mlsAppIsDeactFport224;

#define PDS_CERT_APP_PARAM_START_INDEX	(PDS_FILE_APP_DATA1_13_IDX << 8)
#define PDS_CERT_APP_ENABLE_SIZE		(sizeof(mlsAppIsCertModeEnabled))
#define PDS_DEACTIVATE_FPORT_SIZE		(sizeof(mlsAppIsDeactFport224))
#define PDS_CERT_APP_ENABLE_OFFSET		PDS_FILE_START_OFFSET
#define PDS_DEACTIVATE_FPORT_OFFSET		(PDS_CERT_APP_ENABLE_OFFSET + PDS_SIZE_OF_ITEM_HDR + PDS_DEACTIVATE_FPORT_SIZE)
#define PDS_CERT_APP_ENABLE_ADDR		((uint8_t *)&(mlsAppIsCertModeEnabled))
#define PDS_DEACTIVATE_FPORT_ADDR		((uint8_t *)&(mlsAppIsDeactFport224))

typedef enum _MlsPdsCertAppItems {
    PDS_CERT_APP_ENABLE = PDS_CERT_APP_PARAM_START_INDEX,
    PDS_DEACTIVATE_FPORT,
    PDS_CERT_APP_PARAM_ITEM_ID_MAX_VALUE /* Always add new items above this value */
} MlsPdsCertAppItems_t;
#endif /* #if (ENABLE_PDS == 1) */
#endif /* #if (CERT_APP == 1) */

typedef void (*SleepCallback_t)(uint32_t);

// *****************************************************************************
// *****************************************************************************
// Section: Function prototypes
// *****************************************************************************
// *****************************************************************************
#if (CERT_APP == 1)
StackRetStatus_t MlsAppCertModeJoinParamSet(ActivationType_t join_type);
bool MlsAppCertIsCmdValid(uint8_t *buffer, uint8_t len);
void MlsAppCertCmdExecute(uint8_t *buffer, uint8_t buflen);
void MlsAppTimerCertModeCallback(void);
void MlsAppTimerCwTxCallback(void);
void MlsAppTimerSysRstCallback(void);
#if (ENABLE_PDS == 1)
PdsStatus_t MlsAppPdsDataRegister(void);
void MlsAppPdsFileId13Callback(void);
#endif /* #if (ENABLE_PDS == 1) */
#endif /* #if (CERT_APP == 1) */


#if defined(CONF_PMM_ENABLE)
PMM_Status_t MlsAppSleep(void);
void MlsAppSleepCallback(uint32_t sleptDuration);
void MlsAppSleepCallbackNotifySet(SleepCallback_t func);
void MlsAppResourceInitialize(void);
void MlsAppResourceDeinitialize(void);
#endif /* #if defined(CONF_PMM_ENABLE) */


#if !defined(CRYPTO_DEV_ENABLED) && (EDBG_EUI_READ == 1)
void MlsAppEdbgEuiRead(uint8_t *eui);
#endif /* #if !defined(CRYPTO_DEV_ENABLED) && (EDBG_EUI_READ == 1) */

#if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1)
void MlsAppWlr089U0EuiRead(uint8_t *eui);
#endif /* #if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1) */

void MlsAppInitialize(void);

StackRetStatus_t MlsAppJoinReq(ActivationType_t type);
void MlsAppJoinReqCallback(StackRetStatus_t status);
void MlsAppJoinReqCallbackNotifySet(JoinResponseCb_t func);

StackRetStatus_t MlsAppSendReq(void);
void MlsAppSendReqCallback(void *appHnd, appCbParams_t *data);
void MlsAppSendReqCallbackNotifySet(AppDataCb_t func);

void MlsAppPeriodicTimerCallback(void);

StackRetStatus_t MlsAppSet(IsmBand_t band, const uint16_t index);
StackRetStatus_t MlsAppJoinParamSet(ActivationType_t type);
StackRetStatus_t MlsAppEdClassSet(EdClass_t edclass);
void MlsAppMcastParamSet(void);

void MlsAppResetCausePrint(void);
void MlsAppPrintArrayU8(uint8_t *array, uint8_t length);

void MlsAppSerialInitialize(void);
void MlsAppSerialDataHandler(void);
bool MlsAppSerialRead(uint8_t *rxchar);
void MlsAppSerialReadCallback(uintptr_t ctx);
void MlsAppSerialWriteCallback(uintptr_t ctx);
bool MlsAppSerialIsCharPending(void);

float MlsAppCelsiusToFahrenheit(float c);
#endif /* MLS_APP_H */

/* EOF mls_app.h */
</#if>