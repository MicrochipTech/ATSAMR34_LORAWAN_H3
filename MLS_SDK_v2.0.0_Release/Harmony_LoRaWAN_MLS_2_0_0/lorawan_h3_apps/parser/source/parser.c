/**
 * \file  parser.c
 *
 * \brief Main parser file
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


#include <stdlib.h>
#include "definitions.h"
#include "parser.h"
#include "parser_commands.h"
#include "parser_tsp.h"
#include "parser_lorawan.h"
#include "parser_utils.h"

#define VER_STR            STACK_VER

#if defined(BOARD_SAMR34_XPRO)
#define HW_STR            "ATSAMR34-XPRO"
#elif defined(BOARD_WLR089U0)
#define HW_STR            "WLR089U0"
#else
#define HW_STR            "USER_BOARD"
#endif

/************************** Global variables ***********************************/
uint8_t devEui[8] = {0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd};
/****************************** PROTOTYPES *************************************/
typedef struct parserRxCmd_tag {
	char cmd[PARSER_DEF_CMD_MAX_LEN];
	uint16_t wordLen[PARSER_DEF_CMD_MAX_IDX];
	uint16_t wordStartPos[PARSER_DEF_CMD_MAX_IDX];
	uint8_t bCmdStatus;
	uint8_t crtWordIdx;
	uint16_t crtCmdPos;
	uint16_t crtWordPos;
} parserRxCmd_t;

static uint8_t Parser_ProcessCmd(const parserCmdEntry_t* pParserCmd, uint8_t nbParserCmd, uint8_t rxCmdIdx,
	uint8_t* pSavedCmdIdx);

SYSTEM_TaskStatus_t APP_TaskHandler(void);
extern volatile parserRxCmd_t mRxParserCmd;

static const char* gapParserStatus[] ={
	"ok",
	"invalid_param",
	"err"
};

char aParserData[PARSER_MAX_DATA_LEN];

char receiveBuffer[1] = {'\0'};
char messageError[] = "serial_err\r\n";
bool errorStatus = false;
bool writeStatus = false;
bool readStatus = false;

void Parser_WriteCallback(uintptr_t context)
{
	writeStatus = true;
}

void Parser_ReadCallback(uintptr_t context)
{
	if (SERCOM0_USART_ErrorGet() != USART_ERROR_NONE) {
		/* ErrorGet clears errors, set error flag to notify console */
		errorStatus = true;
	} else {
		readStatus = true;
	}
}

void parser_serial_data_handler(void)
{
	SERCOM0_USART_Read(&receiveBuffer[0], sizeof(receiveBuffer));
	SYSTEM_PostTask(APP_TASK_ID);
}

void Parser_Init(void)
{
	SERCOM0_USART_WriteCallbackRegister(Parser_WriteCallback, 0);
	SERCOM0_USART_ReadCallbackRegister(Parser_ReadCallback, 0);

	Parser_RxClearBuffer();
	Parser_LorawanInit();
}

void Parser_Main(void)
{
	uint8_t cmdTotalNb;
	uint8_t startCmdSize = gParserStartCmdSize;
	const parserCmdEntry_t* pStartCmd = gpParserStartCmd;
	uint8_t crtWordIdx;
	uint8_t savedCmdIdx;
	parserCmdEntry_t tempCmd;

	if (true == errorStatus) {
		errorStatus = false;
		SERCOM0_USART_Write(&messageError[0], sizeof(messageError));
	} else if (true == readStatus) {
		readStatus = false;
		Parser_RxAddChar((uint8_t) receiveBuffer[0]);
	} else if (true == writeStatus) {
		writeStatus = false;
		SERCOM0_USART_Read(&receiveBuffer[0], sizeof(receiveBuffer));
	} else {
		;
	}

	/* Verify if an entire command is received */
	if (mRxParserCmd.bCmdStatus) {
		cmdTotalNb = mRxParserCmd.crtWordIdx + 1;
		crtWordIdx = 0;

		while (cmdTotalNb) {
			if (Parser_ProcessCmd(pStartCmd, startCmdSize, crtWordIdx, &savedCmdIdx)) {
				/* Further processing is needed, continue with group commands */
				tempCmd = *(pStartCmd + savedCmdIdx);
				startCmdSize = tempCmd.nextParserCmdSize;
				pStartCmd = tempCmd.pNextParserCmd;

				/* Process the next command */
				crtWordIdx++;

				cmdTotalNb--;
			} else {
				break;
			}
		}

		Parser_RxClearBuffer();
	}

}

void Parser_GetSwVersion(char* pBuffData)
{
	/* Set HW */
	memcpy(pBuffData, HW_STR, sizeof(HW_STR));
	pBuffData[sizeof(HW_STR) - 1] = ' ';
	/* Set firmware version */
	memcpy(&pBuffData[sizeof(HW_STR)], VER_STR, sizeof(VER_STR));
	pBuffData[sizeof(HW_STR) + sizeof(VER_STR) - 1] = ' ';
	/* Set date and time */
	memcpy(&pBuffData[sizeof(HW_STR) + sizeof(VER_STR)], __DATE__, sizeof(__DATE__));
	pBuffData[sizeof(HW_STR) + sizeof(VER_STR) + sizeof(__DATE__) - 1] = ' ';
	memcpy(&pBuffData[sizeof(HW_STR) + sizeof(VER_STR) + sizeof(__DATE__)], __TIME__, sizeof(__TIME__));
	pBuffData[sizeof(HW_STR) + sizeof(VER_STR) + sizeof(__DATE__) + sizeof(__TIME__)] = '\0';
}

static uint8_t Parser_ProcessCmd(const parserCmdEntry_t* pParserCmd, uint8_t nbParserCmd, uint8_t rxCmdIdx,
	uint8_t* pSavedCmdIdx)
{
	uint8_t cmdCtr;
	uint8_t retValue = 0x00U; /* Consider returning error by default */
	parserCmdInfo_t parserCmdInfo;
	parserCmdEntry_t parserCmdEntry;

	parserCmdInfo.pReplyCmd = (char*) gapParserStatus[INVALID_PARAM_IDX];
	/* Reply with error by default */;

	/* Validate and find the group command */
	for (cmdCtr = 0; cmdCtr < nbParserCmd; cmdCtr++) {
		parserCmdEntry = *(pParserCmd + cmdCtr);
		if (strcmp(parserCmdEntry.pCommand, (char*) &mRxParserCmd.cmd[mRxParserCmd.wordStartPos[rxCmdIdx]]) == 0U) {
			/* Command found */
			break;
		}
	}

	if (cmdCtr < nbParserCmd) {
		if (parserCmdEntry.pNextParserCmd == NULL) {
			/* No other commands, just execute the callback */
			if (parserCmdEntry.pActionCbFct) {
				if ((mRxParserCmd.crtWordIdx - rxCmdIdx) == parserCmdEntry.flags) {
					uint8_t iCtr = rxCmdIdx + 1;
					bool bInvalidParam = false;
					if (parserCmdEntry.flags > 0) {
						do {
							//Make sure that the parameters are not empty
							if (mRxParserCmd.wordLen[iCtr++] == 0) {
								bInvalidParam = true;
								break;
							}
						} while (iCtr <= mRxParserCmd.crtWordIdx);
					}

					if (bInvalidParam == false) {
						memset(&parserCmdInfo, 0, sizeof(parserCmdInfo_t));

						if ((rxCmdIdx + 1U < PARSER_DEF_CMD_MAX_IDX) && (mRxParserCmd.wordLen[rxCmdIdx + 1U] > 0U)) {
							parserCmdInfo.pParam1 = (char*) (&mRxParserCmd.cmd[mRxParserCmd.wordStartPos[rxCmdIdx + 1]]);
						}

						if ((rxCmdIdx + 2U < PARSER_DEF_CMD_MAX_IDX) && (mRxParserCmd.wordLen[rxCmdIdx + 2U] > 0U)) {
							parserCmdInfo.pParam2 = (char*) (&mRxParserCmd.cmd[mRxParserCmd.wordStartPos[rxCmdIdx + 2]]);
						}

						if ((rxCmdIdx + 3U < PARSER_DEF_CMD_MAX_IDX) && (mRxParserCmd.wordLen[rxCmdIdx + 3U] > 0U)) {
							parserCmdInfo.pParam3 = (char*) (&mRxParserCmd.cmd[mRxParserCmd.wordStartPos[rxCmdIdx + 3]]);
						}

						if ((rxCmdIdx + 4U < PARSER_DEF_CMD_MAX_IDX) && (mRxParserCmd.wordLen[rxCmdIdx + 4U] > 0U)) {
							parserCmdInfo.pParam4 = (char*) (&mRxParserCmd.cmd[mRxParserCmd.wordStartPos[rxCmdIdx + 4]]);
						}

						if ((rxCmdIdx + 5U < PARSER_DEF_CMD_MAX_IDX) && (mRxParserCmd.wordLen[rxCmdIdx + 5U] > 0U)) {
							parserCmdInfo.pParam5 = (char*) (&mRxParserCmd.cmd[mRxParserCmd.wordStartPos[rxCmdIdx + 5]]);
						}

						/* Execute callback */
						parserCmdEntry.pActionCbFct(&parserCmdInfo);
					}
				}
			}
		} else {
			/* Additional parsing */
			retValue = 1U;
			*pSavedCmdIdx = cmdCtr;
			/* DO not send a reply yet */
			parserCmdInfo.pReplyCmd = NULL;
		}
	}

	if (parserCmdInfo.pReplyCmd) {
		Parser_TxAddReply(parserCmdInfo.pReplyCmd, strlen(parserCmdInfo.pReplyCmd));
	}

	return retValue;
}

void printResetCauses(void)
{
	RSTC_RESET_CAUSE rcause = RSTC_ResetCauseGet();
	printf("Last reset cause: ");
	switch (rcause) {
	case RSTC_RESET_CAUSE_POR_RESET:
		printf("Power-On Reset\r\n");
		break;
	case RSTC_RESET_CAUSE_BOD12_RESET:
		printf("Brown Out 12 Detector Reset\r\n");
		break;
	case RSTC_RESET_CAUSE_BOD33_RESET:
		printf("Brown Out 33 Detector Reset\r\n");
		break;
	case RSTC_RESET_CAUSE_EXT_RESET:
		printf("External Reset\r\n");
		break;
	case RSTC_RESET_CAUSE_WDT_RESET:
		printf("Watchdog Reset\r\n");
		break;
	case RSTC_RESET_CAUSE_SYST_RESET:
		printf("System Reset Request\r\n");
		break;
	case RSTC_RESET_CAUSE_BACKUP_RESET:
		printf("Backup Reset\r\n");
		break;
	default:
		break;
	}
}

SYSTEM_TaskStatus_t APP_TaskHandler(void)
{
	Parser_Main();
	return SYSTEM_TASK_SUCCESS;
}
