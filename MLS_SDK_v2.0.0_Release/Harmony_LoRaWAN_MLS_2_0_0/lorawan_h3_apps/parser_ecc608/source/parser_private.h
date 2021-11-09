/**
 * \file  parser_private.h
 *
 * \brief Parser private header file
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

#ifndef _PARSER_PRIVATE_H
#define _PARSER_PRIVATE_H


#include <stdint.h>
#include <stdbool.h>

enum {
    OK_STATUS_IDX = 0x00U,
    INVALID_PARAM_IDX,
    ERR_STATUS_IDX,
    BUSY_STATUS_IDX,
    INVALID_REQ_IDX,
};

enum {
    OFF_IDX = 0x00U,
    ON_IDX
};

enum {
    STATUS_ERROR = 0xFFU,
    STATUS_DONE = 0x00U
};

enum {
    REPLY_OK_STATUS = 0x00U,
    REPLY_ERR_STATUS,
    REPLY_EXIT_STATUS,
    REPLY_CMD_STATUS,
    REPLY_DO_NOT_REPLY
};

#define PARSER_END_LINE_DELIM_STRING "\r\n"

typedef struct parserCmdInfo_tag {
    char* pParam1;
    char* pParam2;
    char* pParam3;
    char* pParam4;
    char* pParam5;
    char* pReplyCmd;
} parserCmdInfo_t;


#endif /* _PARSER_PRIVATE_H */