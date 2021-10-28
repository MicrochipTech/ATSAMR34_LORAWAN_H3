/**
 * \file  parser_commands.h
 *
 * \brief Command definition header file
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

#ifndef _PARSER_COMMANDS_H
#define _PARSER_COMMANDS_H


#include <stdint.h>
#include "parser_private.h"


typedef void (*actionCbFct_t)(parserCmdInfo_t* pParserCmdInfo);

typedef struct parserCmdEntry_tag {
    const char* pCommand;
    const struct parserCmdEntry_tag* pNextParserCmd;
    actionCbFct_t pActionCbFct;
    uint8_t nextParserCmdSize;
    uint8_t flags;
} parserCmdEntry_t;

extern const parserCmdEntry_t* gpParserStartCmd;
extern const uint8_t gParserStartCmdSize;


#endif /* _PARSER_COMMANDS_H */