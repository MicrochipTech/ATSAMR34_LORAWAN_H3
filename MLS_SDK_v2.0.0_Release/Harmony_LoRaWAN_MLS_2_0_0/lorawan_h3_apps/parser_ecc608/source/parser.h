/**
 * \file  parser.h
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
#ifndef _PARSER_H
#define _PARSER_H

#include <stdint.h>
#include "pds_interface.h"

typedef enum _appPdsEntries
{
	PDS_APP_CUSTOMPARAMETER = (PDS_FILE_APP_DATA1_13_IDX << 8),
	PDS_APP_FILEID_MAX_VALUE
} AppPdsEntries_t;

#define PARSER_MAX_DATA_LEN 530U

typedef union {
    uint32_t value;
    uint8_t buffer[4];
} auint32_t;

typedef union {
    uint16_t value;

    struct {
        uint16_t deveui : 1;
        uint16_t joineui : 1;
        uint16_t appkey : 1;
        uint16_t devaddr : 1;
        uint16_t nwkskey : 1;
        uint16_t appskey : 1;
        uint16_t mcastdevaddr : 1;
        uint16_t mcastnwkskey : 1;
        uint16_t mcastappskey : 1;
        uint16_t mcastfreq : 1;
        uint16_t mcastdr : 1;
    } flags;
} parserConfiguredJoinParameters_t;


extern char aParserData[PARSER_MAX_DATA_LEN];

void Parser_Init(void);
void Parser_Main(void);

void Parser_GetSwVersion(char* pBuffData);

uint8_t Parser_GetConfiguredJoinParameters(void);
void Parser_SetConfiguredJoinParameters(uint8_t val);

void parser_serial_data_handler(void);
void printResetCauses(void);
void Parser_WriteCallback(uintptr_t context);
void Parser_ReadCallback(uintptr_t context);

#endif /* _PARSER_H */