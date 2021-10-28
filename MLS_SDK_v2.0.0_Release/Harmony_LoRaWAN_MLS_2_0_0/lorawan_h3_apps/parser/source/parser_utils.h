/**
 * \file  parser_utils.h
 *
 * \brief Parser utils header file
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
#ifndef _PARSER_UTILS_H
#define _PARSER_UTILS_H

/****************************** INCLUDES **************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/****************************** DEFINES ***************************************/
#define PARSER_DEF_WORD_MAX_LEN      106U
#define PARSER_DEF_CMD_MAX_LEN      550U
#define PARSER_DEF_CMD_MAX_IDX      10U
#define PARSER_DEF_CMD_REPLY_LEN    550U
#define PARSER_DEF_DISPATCH_LEN     3U

/*************************** FUNCTIONS PROTOTYPE ******************************/
bool Validate_HexValue(void* pValue);
uint8_t Parser_HexAsciiToInt(uint16_t hexAsciiLen, char* pInHexAscii, uint8_t* pOutInt);
void Parser_IntArrayToHexAscii(uint8_t arrayLen, uint8_t* pInArray, char* pOutHexAscii);
bool Validate_Uint16DecAsciiValue(void* pValue, uint16_t* pDecValue);
bool Validate_Uint8DecAsciiValue(void* pValue, uint8_t* pDecValue);
bool Validate_UintDecAsciiValue(void* pValue, uint8_t DigitsNb, uint32_t maxValue);
uint8_t Validate_OnOffAsciiValue(void* pValue);
uint8_t Validate_Str1Str2AsciiValue(void* pValue, const void* pStr1, const void* pStr2);
int8_t Pin_Index(char* pinName);


/*
 * \brief Converts String to Un-singed Long Integer
 */
char * ultoa(char * str, unsigned long num, int radix);

/*
 * \brief Compare Strings without Case Sensitivity
 */
int stricmp(char *s1, const char *s2);

/*
 * \brief Converts the input string consisting of hexadecimal digits into an integer value
 */
int xtoi(char *c);
#endif	/* _PARSER_UTILS_H */

