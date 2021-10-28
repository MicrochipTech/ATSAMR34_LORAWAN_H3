/**
* \file  enddevice_demo.c
*
* \brief End-Device demo application source
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
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "mls.h"
#include "mls_app.h"
#include "enddevice_demo.h"

#ifdef CRYPTO_DEV_ENABLED
#include "cryptoauthlib.h"
#endif /* #ifdef CRYPTO_DEV_ENABLED */

// *****************************************************************************
// *****************************************************************************
// Section: External variables
// *****************************************************************************
// *****************************************************************************
extern bool mlsAppSerRxStartFlag;
extern uint8_t mlsAppSerialBuffer;
extern bool mlsAppPeriodicStartFlag;
extern uint8_t mlsAppPeriodicTimer;

extern IsmBand_t mlsAppISMBand;

#ifdef CONF_PMM_ENABLE
extern uint32_t ulSleptDuration;
#endif

#if (CERT_APP == 1)
extern bool mlsAppIsCertModeEnabled;
extern bool mlsAppIsDeactFport224;
extern ActivationType_t mlsAppCertJoinType;
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
#if defined(BOARD_SAMR34_XPRO)
#define BOARD_NAME          "ATSAMR34-XPRO"
#elif defined(BOARD_WLR089U0)
#define BOARD_NAME          "WLR089U0"
#else
#define BOARD_NAME          "USER_BOARD"
#endif

#define LED_AMBER_ON        LED_AMBER_Clear();
#define LED_AMBER_OFF       LED_AMBER_Set();
#define LED_GREEN_ON        LED_GREEN_Clear();
#define LED_GREEN_OFF       LED_GREEN_Set();

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************
const char * pcInitMenu[] = {
	"Demo application",
#if(CERT_APP == 1)
	"Enable/disable Certification mode",
#endif
	"\0"
};

const char * pcMainMenu[] = {
#if(EU_BAND == 1)
	"EU868",
#endif
#if(NA_BAND == 1)
	"NA915",
#endif
#if(AU_BAND == 1)
	"AU915",
#endif
#if(AS_BAND == 1)
	"AS923",
#endif
#if(JPN_BAND == 1)
	"JPN923",
#endif
#if(KR_BAND == 1)
	"KR920",
#endif
#if(IND_BAND == 1)
	"IND865",
#endif
#if(ENABLE_PDS == 1)
	"Clear PDS",
#endif
	"Reset Board",
	"\0"
};

const char * pcAppMenu[] = {
	"Send Join Request",
	"Send Data",
	"Start Periodic Data",
	"Stop Periodic Data",
#if defined(CONF_PMM_ENABLE)
	"Sleep",
#endif
	"Main Menu",
	"\0"
};

const char* pcBandStrings[] = {
	"Dummy",
#if(EU_BAND == 1)
	"EU868",
#endif
#if(NA_BAND == 1)
	"NA915",
#endif
#if(AU_BAND == 1)
	"AU915",
#endif
#if(AS_BAND == 1)
	"AS923",
#endif
#if(JPN_BAND == 1)
	"JPN923",
#endif
#if(KR_BAND == 1)
	"KR920",
#endif
#if(IND_BAND == 1)
	"IND865"
#endif
};

const uint8_t pucBandTable[] = {
	0xFF,
#if(EU_BAND == 1)
	ISM_EU868,
#endif
#if(NA_BAND == 1)
	ISM_NA915,
#endif
#if(AU_BAND == 1)
	ISM_AU915,
#endif
#if(AS_BAND == 1)
	ISM_THAI923,
#endif
#if(JPN_BAND == 1)
	ISM_JPN923,
#endif
#if(KR_BAND == 1)
	ISM_KR920,
#endif
#if(IND_BAND == 1)
	ISM_IND865,
#endif
	0xFF,
	0xFF
};

const char * pcLorawanStatus[] = {
	"RADIO_SUCCESS",
	"RADIO_NO_DATA",
	"RADIO_DATA_SIZE",
	"RADIO_INVALID_REQ",
	"RADIO_BUSY",
	"RADIO_OUT_OF_RANGE",
	"RADIO_UNSUPPORTED_ATTR",
	"RADIO_CHANNEL_BUSY",
	"SUCCESS",
	"NWK_NOT_JOINED",
	"INVALID_PARAMETER",
	"KEYS_NOT_INITIALIZED",
	"SILENT_IMMEDIATELY_ACTIVE",
	"FCNTR_ERROR_REJOIN_NEEDED",
	"INVALID_BUFFER_LENGTH",
	"MAC_PAUSED",
	"NO_CHANNELS_FOUND",
	"BUSY",
	"NO_ACK",
	"NWK_JOIN_IN_PROGRESS",
	"RESOURCE_UNAVAILABLE",
	"INVALID_REQUEST",
	"UNSUPPORTED_BAND",
	"FCNTR_ERROR",
	"MIC_ERROR",
	"INVALID_MTYPE",
	"MCAST_HDR_INVALID",
	"TX_TIMEOUT",
	"RADIO_TX_TIMEOUT",
	"MAX_MCAST_GROUP_REACHED",
	"INVALID_PACKET",
	"RXPKT_ENCRYPTION_FAILED",
	"TXPKT_ENCRYPTION_FAILED",
	"SKEY_DERIVATION_FAILED",
	"MIC_CALCULATION_FAILED",
	"SKEY_READ_FAILED",
	"JOIN_NONCE_ERROR"
};

// *****************************************************************************
// *****************************************************************************
// Section: Global variables
// *****************************************************************************
// *****************************************************************************
volatile uint8_t ucAppTaskFlags = 0x00u;
volatile AppTaskState_t xAppTaskState = INIT_MENU_STATE;

bool bIsJoined = false;

uint32_t ulSleptDuration = UINT32_MAX;

#if (ENABLE_PDS == 1)
uint8_t ucRestoreTimer;
uint8_t ucRestorePromptStopKey;
volatile uint8_t ucRestoreAttemptCnt = DEMOAPP_RESTOREATTEMPT_MAX;
#endif /* #if (ENABLE_PDS == 1) */

static SYSTEM_TaskStatus_t(*pxAppTaskHandlers[APP_TASKS_COUNT])(void) = {
	/* In the order of descending priority */
	DEMO_DisplayTask,
	DEMO_ProcessTask
};

// *****************************************************************************
// *****************************************************************************
// Section: Function definitions
// *****************************************************************************
// *****************************************************************************

SYSTEM_TaskStatus_t APP_TaskHandler(void)
{
	if (ucAppTaskFlags) {
		for (uint8_t ucTaskId = 0; ucTaskId < APP_TASKS_COUNT; ucTaskId++) {
			if ((1 << ucTaskId) & (ucAppTaskFlags)) {
				ATOMIC_SECTION_ENTER
				ucAppTaskFlags &= ~(1 << ucTaskId);
				ATOMIC_SECTION_EXIT

				pxAppTaskHandlers[ucTaskId]();

				if (ucAppTaskFlags) {
					SYSTEM_PostTask(APP_TASK_ID);
				}

				break;
			}
		}
	}

	return SYSTEM_TASK_SUCCESS;
}
//------------------------------------------------------------------------------

void DEMO_PostTask(AppTaskIds_t xId)
{
	ATOMIC_SECTION_ENTER
	ucAppTaskFlags |= (1 << xId);
	ATOMIC_SECTION_EXIT
	/* Also post a APP task to the system */
	SYSTEM_PostTask(APP_TASK_ID);
}
//------------------------------------------------------------------------------

void DEMO_RunTask(AppTaskIds_t xTask, AppTaskState_t xState)
{
	xAppTaskState = xState;
	DEMO_PostTask(xTask);
}
//------------------------------------------------------------------------------

void DEMO_Init(void)
{
	LED_AMBER_OFF;
	LED_GREEN_OFF;

#ifdef CONF_PMM_ENABLE
	MlsAppSleepCallbackNotifySet(DEMO_WakeupNotification);
#endif
	MlsAppSendReqCallbackNotifySet(DEMO_MessageNotification);
	MlsAppJoinReqCallbackNotifySet(DEMO_JoinNotification);

	printf("\r\nInit - Successful\r\n");

#ifdef CRYPTO_DEV_ENABLED
	DEMO_PrintECCInfo();
#endif /* #ifdef CRYPTO_DEV_ENABLED */

#if 0
	{
		uint8_t space[LORAWAN_SESSIONKEY_LENGTH];
		memset(space, 0, LORAWAN_SESSIONKEY_LENGTH);
		SAL_Read(APP_KEY, space);
	}
#endif    

#if (ENABLE_PDS == 1)
	if (PDS_IsRestorable()) {
		static uint8_t ucPrevBand = 0xFF;
		uint8_t ucPrevChoice = 0xFF;
		PDS_RestoreAll();
		LORAWAN_GetAttr(ISMBAND, NULL, &ucPrevBand);
		for (uint32_t i = 0; i < sizeof(pucBandTable) - 1; i++) {
			if (pucBandTable[i] == ucPrevBand) {
				ucPrevChoice = i;
				break;
			}
		}

		ucRestoreAttemptCnt = DEMOAPP_RESTOREATTEMPT_MAX;
#if (CERT_APP == 1)        
		if (mlsAppIsCertModeEnabled) {
			printf("Device SHALL restore in CERTIFICATION mode\r\n");
		}
#endif
		printf("Last configured regional band %s\r\n", pcBandStrings[ucPrevChoice]);
		printf("Press a key ([A-Z;0-9]) to change band\r\n");
		printf("Continuing to %s in ", pcBandStrings[ucPrevChoice]);

		SwTimerStart(ucRestoreTimer,
			MS_TO_US(DEMOAPP_RESTOREPERIODTIMER_MS),
			SW_TIMEOUT_RELATIVE,
			DEMO_RestoreTimerCallback,
			NULL
			);
	} else
#endif
	{
		DEMO_RunTask(DISPLAY_TASK_HANDLER, INIT_MENU_STATE);
	}
}
//------------------------------------------------------------------------------

SYSTEM_TaskStatus_t DEMO_DisplayTask(void)
{
	bool bAskChoice = true;
	printf("\r\n\r\n");

	switch (xAppTaskState) {
	case INIT_MENU_STATE:
	{
		uint8_t i = 0;
		while (strcmp("\0", pcInitMenu[i])) {
			printf("%2d. %s\r\n", (i + 1), pcInitMenu[i]);
			i++;
		}
		break;
	}

	case MAIN_MENU_STATE:
	{
		uint8_t i = 0;
		while (strcmp("\0", pcMainMenu[i])) {
			printf("%2d. %s\r\n", (i + 1), pcMainMenu[i]);
			i++;
		}
		break;
	}

	case APP_MENU_STATE:
	{
		uint8_t i = 0;
		if (UINT32_MAX != ulSleptDuration) {
			printf("Sleep done: %ld ms\r\n", ulSleptDuration);

			ulSleptDuration = UINT32_MAX;
		}

		printf("\r\n\r\n");

		while (strcmp("\0", pcAppMenu[i])) {
			printf("%2d. %s\r\n", (i + 1), pcAppMenu[i]);
			i++;
		}
		break;
	}


#if (ENABLE_PDS == 1)
	case RESTORE_PROMPT_STATE:
	{
		printf("ED will restore the previous configuration!\r\n");
		DEMO_RunTask(PROCESS_TASK_HANDLER, RESTORE_PROMPT_STATE);
		bAskChoice = false;

		break;
	}
#endif

	default:
	{
		printf("Warn - %s:%d - Invalid app_task_state\r\n",
			__FUNCTION__, __LINE__);
		break;
	}
	}

	if (bAskChoice) {
		printf("\r\nEnter your choice: ");
		mlsAppSerRxStartFlag = true;
	}

	return LORAWAN_SUCCESS;
}
//------------------------------------------------------------------------------

SYSTEM_TaskStatus_t DEMO_ProcessTask(void)
{
	printf("\r\n\r\n");

	switch (xAppTaskState) {
	case INIT_MENU_STATE:
	{
		DEMO_ProcessInitMenu();

		break;
	}


	case MAIN_MENU_STATE:
	{
		DEMO_ProcessMainMenu();

		break;
	}

	case APP_MENU_STATE:
	{
		DEMO_ProcessAppMenu();

		break;
	}
#if (ENABLE_PDS == 1)
	case RESTORE_PROMPT_STATE:
	{
		DEMO_ProcessRestorePrompt();

		break;
	}
#endif
	default:
	{
		printf("Warn - %s:%d - Invalid app_task_state\r\n",
			__FUNCTION__, __LINE__);

		break;
	}
	}

	return LORAWAN_SUCCESS;
}
//------------------------------------------------------------------------------

void DEMO_PrintStatus(StackRetStatus_t xStat)
{
	printf("Status : LORAWAN_%s\r\n", pcLorawanStatus[xStat]);
}
//------------------------------------------------------------------------------

void DEMO_ProcessInitMenu(void)
{
	switch (mlsAppSerialBuffer) {
	default:
		printf("Choice not valid\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, INIT_MENU_STATE);
		break;

	case INIT_MENU_DEMO_APP:
		DEMO_RunTask(DISPLAY_TASK_HANDLER, MAIN_MENU_STATE);
		break;

#if (CERT_APP == 1)
	case INIT_MENU_CERT_MODE:
	{
		bool bTrue = true;

		mlsAppIsCertModeEnabled = !mlsAppIsCertModeEnabled;
		mlsAppIsDeactFport224 = !mlsAppIsCertModeEnabled;

		LORAWAN_SetAttr(TEST_MODE_ENABLE, &mlsAppIsCertModeEnabled);
		LORAWAN_SetAttr(ADR, &bTrue);
#if (ENABLE_PDS == 1)
		PDS_STORE(PDS_CERT_APP_ENABLE);
#endif
		DEMO_RunTask(DISPLAY_TASK_HANDLER, INIT_MENU_STATE);

		printf("Certification mode (FPort#224): %sABLED\r\n",
			mlsAppIsCertModeEnabled ? "EN" : "DIS");

		break;
	}
#endif
	}
}
//------------------------------------------------------------------------------

void DEMO_ProcessMainMenu(void)
{
	bool bIsBandSet = true;
	switch (mlsAppSerialBuffer) {
	default:
	{
		bIsBandSet = false;
		printf("Choice not valid\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, MAIN_MENU_STATE);

		break;
	}

	case MAIN_MENU_RESET_BOARD:
		SYS_RESET_SoftwareReset();

		break;

#if (ENABLE_PDS == 1)
	case MAIN_MENU_CLEAR_PDS:
	{
		bIsBandSet = false;
		PDS_DeleteAll();
		printf("PDS is now cleared, device at factory new state\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, MAIN_MENU_STATE);

		break;
	}
#endif

#if (EU_BAND == 1)
	case MAIN_MENU_EU868:
		mlsAppISMBand = ISM_EU868;
		break;
#endif
#if (NA_BAND == 1)
	case MAIN_MENU_NA915:
		mlsAppISMBand = ISM_NA915;
		break;
#endif
#if (AU_BAND == 1)
	case MAIN_MENU_AU915:
		mlsAppISMBand = ISM_AU915;
		break;
#endif
#if (AS_BAND == 1)
	case MAIN_MENU_AS923:
		mlsAppISMBand = ISM_THAI923;
		break;
#endif
#if (JPN_BAND == 1)
	case MAIN_MENU_JPN923:
		mlsAppISMBand = ISM_JPN923;
		break;
#endif
#if (KR_BAND == 1)
	case MAIN_MENU_KR920:
		mlsAppISMBand = ISM_KR920;
		break;
#endif
#if (IND_BAND == 1)
	case MAIN_MENU_IND865:
		mlsAppISMBand = ISM_IND865;
		break;
#endif
	}

	if (bIsBandSet) {
		StackRetStatus_t xSetStatus;

		LORAWAN_Reset(mlsAppISMBand);

		xSetStatus = MlsAppSet(mlsAppISMBand, mlsAppSerialBuffer);

		if ((xSetStatus == LORAWAN_SUCCESS) && (mlsAppSerialBuffer < sizeof(pucBandTable))) {
			printf("\nJoin Request Sent for %s\n\r", pcBandStrings[mlsAppSerialBuffer]);
		} else {
			DEMO_PrintStatus(xSetStatus);

			DEMO_RunTask(PROCESS_TASK_HANDLER, APP_MENU_STATE);
		}
	}
}
//------------------------------------------------------------------------------

void DEMO_ProcessAppMenu(void)
{
	StackRetStatus_t xStat;
	switch (mlsAppSerialBuffer) {
	default:
	{
		printf("Choice not valid\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		break;
	}

	case APP_MENU_SEND_JOIN_REQ:
	{
		ActivationType_t xJoinType = DEMO_APP_ACTIVATION_TYPE;
#if (CERT_APP == 1)
		if (mlsAppIsCertModeEnabled) {
			xJoinType = CERT_APP_ACTIVATION_TYPE;
		}
#endif
		DEMO_Join(xJoinType);
		break;
	}

	case APP_MENU_SEND_DATA:
	{
		DEMO_SendMessage();
		break;
	}

	case APP_MENU_START_PERIODIC_DATA:
	{
		if (!mlsAppPeriodicStartFlag) {
			mlsAppPeriodicStartFlag = 1;
			DEMO_SendMessage();
			SwTimerStop(mlsAppPeriodicTimer);
			xStat = SwTimerStart(mlsAppPeriodicTimer,
				MS_TO_US(APP_PERIODIC_TIMER_PERIOD_MS),
				SW_TIMEOUT_RELATIVE,
				MlsAppPeriodicTimerCallback,
				NULL);
			if (xStat != LORAWAN_SUCCESS) {
				printf("Failed to start periodic timer %d\r\n", xStat);
			}
		} else {
			printf("Periodic uplink already started\r\n");
			DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		}
		break;
	}

	case APP_MENU_STOP_PERIODIC_DATA:
	{
		if (mlsAppPeriodicStartFlag) {
			mlsAppPeriodicStartFlag = 0;
			SwTimerStop(mlsAppPeriodicTimer);
			printf("Periodic uplink stopped\r\n");
		}

		DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);

		break;
	}

	case APP_MENU_MAIN_MENU:
	{
		DEMO_RunTask(DISPLAY_TASK_HANDLER, MAIN_MENU_STATE);
		break;
	}

#ifdef CONF_PMM_ENABLE
	case APP_MENU_SLEEP:
	{
		if (MlsAppSleep() == PMM_SLEEP_REQ_DENIED) {
			printf("ED cannot sleep now\r\n");

			DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		}

		break;
	}
#endif /* #ifdef CONF_PMM_ENABLE */
	}
}
//------------------------------------------------------------------------------

#if (ENABLE_PDS == 1)

void DEMO_ProcessRestorePrompt(void)
{
	StackRetStatus_t xStat = LORAWAN_SUCCESS;
	uint8_t ucPrevBand = 0xff;
	uint8_t ucCurChoice = 0xff;
	bool bJoinBackoffEn = false;

	PDS_RestoreAll();
	LORAWAN_GetAttr(ISMBAND, NULL, &ucPrevBand);

	for (uint32_t ulIdx = 0; ulIdx < sizeof(pucBandTable) - 1; ulIdx++) {
		if (pucBandTable[ulIdx] == ucPrevBand) {
			ucCurChoice = ulIdx;
			break;
		}
	}
	if ((ucCurChoice > 0) && (ucCurChoice < (sizeof(pucBandTable) - 1))) {
		xStat = LORAWAN_Reset(pucBandTable[ucCurChoice]);
	}

	/*
	 * Disabled Join back-off in Demo application
	 * Needs to be enabled in Production Environment Ref Section
	 */
	LORAWAN_SetAttr(JOIN_BACKOFF_ENABLE, &bJoinBackoffEn);

	if ((xStat == LORAWAN_SUCCESS) && (ucCurChoice < (sizeof(pucBandTable) - 1))) {
		uint32_t ulJoinStatus = 0;
		PDS_RestoreAll();
		LORAWAN_GetAttr(LORAWAN_STATUS, NULL, &ulJoinStatus);
		printf("Successfully restored settings from PDS\r\n");

		if (ulJoinStatus & DEMOAPP_LORAWANJOINED_BITMASK) {
			bIsJoined = true;
			LED_GREEN_ON;
			printf("Device has joined already\r\n");
		} else {
			bIsJoined = false;
			printf("Device has not joined previously\r\n");
		}
		printf("Band : %s\r\n", pcBandStrings[ucCurChoice]);

		DEMO_PrintConfig();

#if (CERT_APP == 1)
		if (mlsAppIsCertModeEnabled) {
			if (CERT_APP_ACTIVATION_TYPE == LORAWAN_ABP) {
				DEMO_SendMessage();
			} else {
				DEMO_Join(LORAWAN_OTAA);
			}

		} else
#endif /* #if (CERT_APP == 1) */
		{
			DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		}
	} else {
		printf("Failed to restore settings from PDS\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
	}
}
#endif
//------------------------------------------------------------------------------

#if (ENABLE_PDS == 1)

void DEMO_RestoreTimerCallback(void)
{
	printf("%d..", ucRestoreAttemptCnt);
	ucRestoreAttemptCnt--;

	if (MlsAppSerialRead((void *) &(ucRestorePromptStopKey))) {
		/* User has pressed a key; start fresh */
		printf("\r\n");

		PDS_DeleteAll();

		SwTimerStop(ucRestoreTimer);

		DEMO_RunTask(DISPLAY_TASK_HANDLER, INIT_MENU_STATE);
	} else if (ucRestoreAttemptCnt) {
		/* User has not pressed a key YET and attempts remaining */
		SwTimerStart(ucRestoreTimer,
			MS_TO_US(DEMOAPP_RESTOREPERIODTIMER_MS),
			SW_TIMEOUT_RELATIVE,
			DEMO_RestoreTimerCallback,
			NULL
			);
	} else {
		/* User has not pressed a key YET and attempts are over */
		printf("\r\nNo key pressed\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, RESTORE_PROMPT_STATE);
	}
}
#endif

//------------------------------------------------------------------------------

#ifdef CRYPTO_DEV_ENABLED

void DEMO_PrintECCInfo(void)
{
	ATCA_STATUS xStat;
	uint8_t pucSerialNumber[9];
	uint8_t pucInfo[2];
	uint8_t ucTKMInfo[10];
	int lSlot = 10;
	int lOffset = 70;
	uint8_t pucAppEUI[8];
	uint8_t pucDevEUIASCII[16];
	uint8_t pucDevEUIDecoded[8];
	size_t xBinSize = sizeof(pucDevEUIDecoded);

	delay_ms(5);
	(void) xStat;

	/* read the serial number */
	xStat = atcab_read_serial_number(pucSerialNumber);
	printf("\r\n------------------------------\r\n");

	/* read the SE_INFO */
	xStat = atcab_read_bytes_zone(ATCA_ZONE_DATA, lSlot, lOffset, pucInfo, sizeof(pucInfo));

	/* Read the CustomDevEUI */
	xStat = atcab_read_bytes_zone(ATCA_ZONE_DATA, DEV_EUI_SLOT, 0, pucDevEUIASCII, 16);
	atcab_hex2bin((char*) pucDevEUIASCII, strlen((char*) pucDevEUIASCII), pucDevEUIDecoded, &xBinSize);

	/* Print DevEUI */
	printf("DEV EUI:  ");
#if (SERIAL_NUM_AS_DEV_EUI == 1)
	MlsAppPrintArrayU8(pucSerialNumber, sizeof(pucSerialNumber) - 1);
#else
	MlsAppPrintArrayU8(pucDevEUIDecoded, sizeof(pucDevEUIDecoded));
#endif

	/* Read the AppEUI */
	xStat = atcab_read_bytes_zone(ATCA_ZONE_DATA, APP_EUI_SLOT, 0, pucAppEUI, 8);
	printf("APP EUI:  ");
	MlsAppPrintArrayU8(pucAppEUI, sizeof(pucAppEUI));

	/* assemble full TKM_INFO */
	memcpy(ucTKMInfo, pucInfo, 2);
	memcpy(&ucTKMInfo[2], pucSerialNumber, 8);

	/* ucTKMInfo[] now contains the assembled ucTKMInfo data */
	printf("TKM INFO: ");
	MlsAppPrintArrayU8(ucTKMInfo, sizeof(ucTKMInfo));
	printf("------------------------------\r\n");
}
#endif /* #ifdef CRYPTO_DEV_ENABLED */
//------------------------------------------------------------------------------

void DEMO_PrintConfig(void)
{
	EdClass_t xClass;

	printf("\r\n====== Application Configuration =======\r\n");

	LORAWAN_GetAttr(EDCLASS, NULL, &xClass);
	printf("DevType : Class %c\r\n", (xClass == CLASS_A) ? 'A' : 'C');

	/* ------------------------------------ */

	printf("ActivationType : ");
#if (CERT_APP == 1)
	if (mlsAppIsCertModeEnabled) {
		printf("%s\r\n", (CERT_APP_ACTIVATION_TYPE == LORAWAN_OTAA) ?
			"OTAA" : "ABP");
	} else
#endif
	{
		printf("%s\r\n", (DEMO_APP_ACTIVATION_TYPE == LORAWAN_OTAA) ?
			"OTAA" : "ABP");
	}
	/* ------------------------------------ */

	printf("Transmission Type : ");
#if (CERT_APP == 1)
	if (mlsAppIsCertModeEnabled) {
		printf("%sCONFIRMED\r\n",
			(CERT_APP_TRANSMISSION_TYPE == LORAWAN_UNCNF) ? "UN" : "");
	} else
#endif
	{
		printf("%sCONFIRMED\r\n",
			(DEMO_APP_TRANSMISSION_TYPE == LORAWAN_UNCNF) ? "UN" : "");
	}
	/* ------------------------------------ */

	printf("FPort : %d\r\n", DEMO_APP_FPORT);
	printf("\r\n========================================\r\n");
}
//------------------------------------------------------------------------------

void DEMO_SendMessage(void)
{
	StackRetStatus_t xStat;

	xStat = MlsAppSendReq();
	//DEMO_PrintStatus(xStat);

	switch (xStat) {
	case LORAWAN_SUCCESS:
		LED_AMBER_ON;
		break;

	case LORAWAN_NWK_NOT_JOINED:
		printf("Warn - Cannot uplink, device not joined\r\n");
		DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		break;

	default:
		break;
	}
}
//------------------------------------------------------------------------------

void DEMO_MessageNotification(void *appHnd, appCbParams_t *data)
{
	(void) appHnd;

	EdClass_t xClass;

	LORAWAN_GetAttr(EDCLASS, NULL, &xClass);

	LED_AMBER_OFF;

	switch (data->evt) {
	default:
		break;

	case LORAWAN_EVT_TRANSACTION_COMPLETE:
	{
		DEMO_PrintStatus(data->param.transCmpl.status);
#if (CERT_APP == 1)
		if (!mlsAppIsCertModeEnabled)
#endif
		{
			DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		}
		break;
	}

	case LORAWAN_EVT_RX_DATA_AVAILABLE:
	{
		if (
#if (CERT_APP == 1)
			(!mlsAppIsCertModeEnabled) &&
#endif
			(CLASS_C == xClass)) {
			DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
		}
		break;
	}
	}
}
//------------------------------------------------------------------------------

void DEMO_Join(ActivationType_t xType)
{
	StackRetStatus_t xStat = MlsAppJoinReq(xType);
	LED_GREEN_OFF;
	DEMO_PrintStatus(xStat);
}
//------------------------------------------------------------------------------

void DEMO_JoinNotification(StackRetStatus_t xStatus)
{
	DEMO_PrintStatus(xStatus);
	if (xStatus != LORAWAN_SUCCESS) {
		LED_GREEN_OFF;
#if (CERT_APP == 1)
		if (mlsAppIsCertModeEnabled) {
			if (mlsAppCertJoinType == LORAWAN_OTAA) {
				DEMO_PrintStatus(xStatus);
			}
		}
#endif
	} else {
		LED_GREEN_ON;
		DEMO_PrintConfig();

#if (CERT_APP == 1)
		if (mlsAppIsCertModeEnabled) {
			DEMO_SendMessage();

			return;
		}
#endif
	}

	DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
}
//------------------------------------------------------------------------------
#ifdef CONF_PMM_ENABLE

void DEMO_WakeupNotification(uint32_t sleptDuration)
{
	ulSleptDuration = sleptDuration;

	DEMO_RunTask(DISPLAY_TASK_HANDLER, APP_MENU_STATE);
}
#endif
//------------------------------------------------------------------------------

void MlsAppPeriodicTimerCallback(void)
{
	if (mlsAppPeriodicStartFlag) {
		DEMO_SendMessage();

		if (SwTimerStart(mlsAppPeriodicTimer,
			MS_TO_US(APP_PERIODIC_TIMER_PERIOD_MS),
			SW_TIMEOUT_RELATIVE,
			MlsAppPeriodicTimerCallback,
			NULL) != LORAWAN_SUCCESS) {
			printf("Failed to restart periodic timer\r\n");
		}
	}
}
//------------------------------------------------------------------------------

/* EOF enddevice_demo.c */
