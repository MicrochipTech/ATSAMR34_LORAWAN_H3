/**
 * \file  parser_tsp.c
 *
 * \brief Parser transport source file
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
#include "parser_tsp.h"
#include "parser.h"
#include "parser_lorawan.h"
#include "parser_private.h"
#include "parser_utils.h"
#include "definitions.h"

typedef struct parserRxCmd_tag {
	char cmd[PARSER_DEF_CMD_MAX_LEN];
	uint16_t wordLen[PARSER_DEF_CMD_MAX_IDX];
	uint16_t wordStartPos[PARSER_DEF_CMD_MAX_IDX];
	uint8_t bCmdStatus;
	uint8_t crtWordIdx;
	uint16_t crtCmdPos;
	uint16_t crtWordPos;
} parserRxCmd_t;

volatile parserRxCmd_t mRxParserCmd;
static const char* gpParserLineDelim = {PARSER_END_LINE_DELIM_STRING};

static const char* gapParserTspStatus[] ={
	"ok",
	"invalid_param",
	"err"
};

void Parser_RxClearBuffer(void)
{
	mRxParserCmd.bCmdStatus = 0;
	mRxParserCmd.crtWordIdx = 0;
	mRxParserCmd.crtCmdPos = 0;
	mRxParserCmd.crtWordPos = 0;

	memset((void*) mRxParserCmd.wordLen, 0, PARSER_DEF_CMD_MAX_IDX << 1);
	memset((void*) mRxParserCmd.wordStartPos, 0, PARSER_DEF_CMD_MAX_IDX << 1);
}

void Parser_RxAddChar(uint8_t rxChar)
{
	uint8_t retStatus = STATUS_DONE;
	bool bIsEndLine = false;
	uint8_t iCount;

	// Process special character: '\b'
	if (rxChar == '\b') {
		/* process delete character '\b' */
		if (mRxParserCmd.crtCmdPos > 0U) {
			// Check for ' '. This was previously replaced with '\0'
			//mRxParserCmd.crtCmdPos always indicates the first free position
			if (mRxParserCmd.cmd[mRxParserCmd.crtCmdPos - 1] == '\0') {
				mRxParserCmd.crtWordIdx--;
				mRxParserCmd.crtWordPos = mRxParserCmd.wordLen[mRxParserCmd.crtWordIdx];
				mRxParserCmd.wordLen[mRxParserCmd.crtWordIdx] = 0U;
				mRxParserCmd.wordStartPos[mRxParserCmd.crtWordIdx] = 0U;
			} else {
				mRxParserCmd.crtWordPos--;
			}

			mRxParserCmd.crtCmdPos--;
		}

		return;
	}

	// Regular command
	if (mRxParserCmd.crtCmdPos < PARSER_DEF_CMD_MAX_LEN - 1) {
		if (rxChar == ' ') {
			if (mRxParserCmd.crtWordIdx < PARSER_DEF_CMD_MAX_IDX - 1) {
				/* Command separator received */

				/* Replace ' ' with \0 */
				mRxParserCmd.cmd[mRxParserCmd.crtCmdPos++] = '\0';

				/* Save last filled position in mRxParserCmd.wordLen[mRxParserCmd.crtWordIdx] */
				mRxParserCmd.wordLen[mRxParserCmd.crtWordIdx] = mRxParserCmd.crtWordPos;
				mRxParserCmd.wordStartPos[mRxParserCmd.crtWordIdx] = mRxParserCmd.crtCmdPos - mRxParserCmd.crtWordPos - 1;

				/* Prepare to receive next word */
				mRxParserCmd.crtWordIdx++;
				mRxParserCmd.crtWordPos = 0;
			} else {
				retStatus = STATUS_ERROR;
			}
		} else {
			/* Save the character */
			mRxParserCmd.cmd[mRxParserCmd.crtCmdPos++] = rxChar;
			mRxParserCmd.crtWordPos++;

			if (mRxParserCmd.crtCmdPos >= strlen(gpParserLineDelim)) {
				bIsEndLine = true;

				for (iCount = strlen(gpParserLineDelim); (iCount > 0U) && bIsEndLine; iCount--) {

					if (mRxParserCmd.cmd[mRxParserCmd.crtCmdPos - iCount] != gpParserLineDelim[strlen(gpParserLineDelim) - iCount]) {
						bIsEndLine = false;
					}
					//printf("Comp %d ",bIsEndLine);
				}
			}
			if (bIsEndLine) {
				/* Entire command received */

				/* Replace new line with \0 */
				mRxParserCmd.cmd[mRxParserCmd.crtCmdPos - strlen(gpParserLineDelim)] = '\0';

				mRxParserCmd.wordLen[mRxParserCmd.crtWordIdx] = mRxParserCmd.crtWordPos - strlen(gpParserLineDelim);
				mRxParserCmd.wordStartPos[mRxParserCmd.crtWordIdx] = mRxParserCmd.crtCmdPos - mRxParserCmd.crtWordPos;

				mRxParserCmd.bCmdStatus = 1;
			}
		}
	} else {
		retStatus = STATUS_ERROR;
	}

	if (STATUS_ERROR == retStatus) {
		Parser_RxClearBuffer();
		/* Send reply code */
		Parser_TxAddReply((char*) gapParserTspStatus[ERR_STATUS_IDX], strlen(gapParserTspStatus[ERR_STATUS_IDX]));
	}

}

void Parser_TxAddReply(char* pReplyStr, uint16_t replyStrLen)
{
    SERCOM0_USART_Write((uint8_t *) pReplyStr, replyStrLen);
	while (SERCOM0_USART_WriteIsBusy()) {

	}

	/* Put the delimiter string in UART */
	SERCOM0_USART_Write((uint8_t *) gpParserLineDelim, strlen(gpParserLineDelim));
	while (SERCOM0_USART_WriteIsBusy()) {

	}
}
