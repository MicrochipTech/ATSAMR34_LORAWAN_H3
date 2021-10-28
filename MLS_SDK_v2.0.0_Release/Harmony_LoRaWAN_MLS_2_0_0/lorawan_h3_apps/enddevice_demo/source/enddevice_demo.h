/**
* \file  enddevice_demo.h
*
* \brief End-Device demo application header
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

#ifndef ENDDEVICE_DEMO_H
#define ENDDEVICE_DEMO_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "conf_regparams.h"
#include "conf_pmm.h"
#include "conf_sal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
#if (ENABLE_PDS == 1)
/* Period of the restorePromptTimer - default: 1s */
#define DEMOAPP_RESTOREPERIODTIMER_MS   (1000U)

/* Number of attempts for restoration */
#define DEMOAPP_RESTOREATTEMPT_MAX      (5U)
#endif /* #if (ENABLE_PDS == 1)*/

/* Status bit-mask for LoRaWAN Join indicator */
#define DEMOAPP_LORAWANJOINED_BITMASK   (0x00000001)

#define DEMOAPP_PROCESS_TASK()          \
    do { \
        DEMO_RunTask(PROCESS_TASK_HANDLER, xAppTaskState); \
    } while(0);
    

// *****************************************************************************
// *****************************************************************************
// Section: Types
// *****************************************************************************
// *****************************************************************************
/* Enumerate the application task handler functions */
typedef enum _AppTaskIds_t
{
    DISPLAY_TASK_HANDLER,
    PROCESS_TASK_HANDLER,
    APP_TASKS_COUNT
}AppTaskIds_t;

/* Enumerate the application states */
typedef enum _AppTaskState_t
{
    INIT_MENU_STATE,
    MAIN_MENU_STATE,
    APP_MENU_STATE
#if (ENABLE_PDS == 1)
    ,RESTORE_PROMPT_STATE
#endif
}AppTaskState_t;

typedef enum _InitMenuChoice
{
    INIT_MENU_DUMMY,
    INIT_MENU_DEMO_APP
#if(CERT_APP == 1)
    , INIT_MENU_CERT_MODE
#endif
} InitMenuChoice_t;

typedef enum _MainMenuChoice
{
    MAIN_MENU_DUMMY,
#if(EU_BAND == 1)
    MAIN_MENU_EU868,
#endif
#if(NA_BAND == 1)
    MAIN_MENU_NA915,
#endif
#if(AU_BAND == 1)
    MAIN_MENU_AU915,
#endif
#if(AS_BAND == 1)
    MAIN_MENU_AS923,
#endif
#if(JPN_BAND == 1)
    MAIN_MENU_JPN923,
#endif
#if(KR_BAND == 1)
    MAIN_MENU_KR920,
#endif
#if(IND_BAND == 1)
    MAIN_MENU_IND865,
#endif
#if(ENABLE_PDS == 1)
    MAIN_MENU_CLEAR_PDS,
#endif
    MAIN_MENU_RESET_BOARD
} MainMenuChoice_t;

typedef enum _AppMenuChoice
{
    APP_MENU_DUMMY,
    APP_MENU_SEND_JOIN_REQ,
    APP_MENU_SEND_DATA,
    APP_MENU_START_PERIODIC_DATA,
    APP_MENU_STOP_PERIODIC_DATA,
#if defined(CONF_PMM_ENABLE)
    APP_MENU_SLEEP,
#endif
    APP_MENU_MAIN_MENU
} AppMenuChoice_t;


// *****************************************************************************
// *****************************************************************************
// Section: Function prototypes
// *****************************************************************************
// *****************************************************************************
SYSTEM_TaskStatus_t APP_TaskHandler(void);

void DEMO_Init(void);

void DEMO_PostTask(AppTaskIds_t xId);
void DEMO_RunTask(AppTaskIds_t xTask, AppTaskState_t xState);

SYSTEM_TaskStatus_t DEMO_DisplayTask(void);
SYSTEM_TaskStatus_t DEMO_ProcessTask(void);

void DEMO_ProcessInitMenu(void);
void DEMO_ProcessMainMenu(void);
void DEMO_ProcessAppMenu(void);

void DEMO_PrintConfig(void);
void DEMO_PrintStatus(StackRetStatus_t xStat);

#if (ENABLE_PDS == 1)
void DEMO_ProcessRestorePrompt(void);
void DEMO_RestoreTimerCallback(void);
#endif

void DEMO_LedTimerCallback(void);

void DEMO_SendMessage(void);
void DEMO_MessageNotification(void *appHnd, appCbParams_t *data);

void DEMO_Join(ActivationType_t xType);
void DEMO_JoinNotification(StackRetStatus_t xStatus);
#ifdef CONF_PMM_ENABLE
void DEMO_WakeupNotification(uint32_t sleptDuration);
#endif
#ifdef CRYPTO_DEV_ENABLED
void DEMO_PrintECCInfo(void);
#endif /* #ifdef CRYPTO_DEV_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* _LORA_ENDDEVICE_DEMO_H */

/*******************************************************************************
 End of File
 */

