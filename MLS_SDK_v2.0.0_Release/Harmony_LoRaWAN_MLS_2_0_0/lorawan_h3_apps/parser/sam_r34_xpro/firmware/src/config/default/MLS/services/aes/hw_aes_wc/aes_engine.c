/**
* \file  aes_engine.c
*
* \brief This is the wrapper implementation for AES
*		
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



#include <stdlib.h>
#include <stdint.h>
#include "aes_engine.h"
#include "configuration.h"
#include "wolfcrypt/aes.h"

/* 32bit array of size 4 used as input/argument for aes drivers*/
#define SUB_BLOCK_COUNT 4

extern int wc_AesEncrypt(Aes* aes, const byte* inBlock, byte* outBlock);

#ifndef UT
struct Aes wcAes;
static uint32_t in[SUB_BLOCK_COUNT];
static uint32_t out[SUB_BLOCK_COUNT];
#endif
 
/* Converts a 4 Byte array into a 32-Bit value */
static inline uint32_t byteArrayToU32(uint8_t *byte)
{
    union
    {
        uint32_t u32;
        uint8_t u8[sizeof(uint32_t)];
    } longAddr;

    uint8_t index = 0;

    while(index < sizeof(uint32_t))
    {
        longAddr.u8[index] = *byte++;
        index++;
    }

    return longAddr.u32;
}

void AESEncode(unsigned char* block, unsigned char* masterKey)
{
#ifndef UT
    wcAes.keylen = BLOCKSIZE;

    for(uint8_t i = 0; i < SUB_BLOCK_COUNT; i++)
    {
      wcAes.key[i] = byteArrayToU32(masterKey + (i * sizeof(uint32_t)));
      in[i] = byteArrayToU32(block + (i * sizeof(uint32_t)));
      out[i] = 0;
    }

    wc_AesEncrypt(&wcAes, (uint8_t *) &in, (uint8_t *) &out);
    memcpy(block, out, BLOCKSIZE);
#endif
}

void AESInit(void)
{
#ifndef UT
    // WolfCrypt initialization is done by Harmony
    return;
#endif
}

/* eof aes_engine.c */
