/**
 * \file  parser_system.h
 *
 * \brief Parser system header file
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

#ifndef _PARSER_SYSTEM_H
#define _PARSER_SYSTEM_H

#include "conf_pmm.h"
#include "parser_private.h"

void Parser_SystemGetVer(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemReboot(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemGetHwEui(parserCmdInfo_t* pParserCmdInfo);
#ifdef CONF_PMM_ENABLE
void Parser_SystemSleep(parserCmdInfo_t* pParserCmdInfo);
#endif /* #ifdef CONF_PMM_ENABLE */
void Parser_SystemFactReset(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemGetCustomParam(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemSetCustomParam(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemGetCryptoSn(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemGetCryptoDevEui(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemGetCryptoJoinEui(parserCmdInfo_t* pParserCmdInfo);
void Parser_SystemGetCryptoTkmInfo(parserCmdInfo_t* pParserCmdInfo);

void Parser_EicCallback(uintptr_t context);
#endif /* _PARSER_SYSTEM_H */