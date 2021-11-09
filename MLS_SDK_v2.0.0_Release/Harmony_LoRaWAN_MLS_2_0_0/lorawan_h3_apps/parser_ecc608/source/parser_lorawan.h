/**
 * \file  parser_lorawan.h
 *
 * \brief Parser lorawan APIs definition header file
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

#ifndef _PARSER_LORAWAN_H
#define _PARSER_LORAWAN_H


#include "parser_private.h"
#include "lorawan.h"

/* Length values in Bytes */
#define CH_FREQUENCY_LEN                    4U
#define CH_DUTY_CYCLE_LEN                   4U
#define FRAME_COUNTER_LEN                   4U
#define DEV_EUI_LEN                         8U
#define JOIN_EUI_LEN                         8U
#define APP_KEY_LEN                        16U
#define APPS_KEY_LEN                       16U
#define NWKS_KEY_LEN                       16U
#define DEV_ADDR_LEN                        4U



void Parser_LoraForceEnable(parserCmdInfo_t* pParserCmdInfo);

void Parser_LoraGetAdr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetAggregatedDutyCycle(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetAutoReply(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetChannelFreq(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetChannelStatus(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetClass(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetCrtDataRate(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetCryptoDevEnabled(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetDatarateRange(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetDevAddr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetDevEui(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetDevEuiArray(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetDevNonce(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetDownlinkCounter(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetIsFpending(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetIsm(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetJoinBackoff(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetJoinEui(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetJoinEuiArray(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetJoinNonceType(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetJoindutycycleremaining(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetLbt(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetLinkCheckGwCnt(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetLinkCheckMargin(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacCnfRetryCnt(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacDlAckReqd(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacLastChId(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacLastPacketRssi(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacNextPayloadSize(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacPendingDutyCycle(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacStatus(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMacUncnfRetryCnt(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMcast(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMcastDevAddr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMcastDownCounter(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMcastDr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetMcastFreq(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetReTxNb(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetRepsNb(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetRx2WindowParams(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetRxDelay1(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetRxDelay2(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetSubBandStatus(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetSupportedEdClass(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetSyncWord(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetTxPower(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraGetUplinkCounter(parserCmdInfo_t* pParserCmdInfo);

void Parser_LoraJoin(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraLinkCheck(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraPause(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraReset(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraResume(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSave(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSend(parserCmdInfo_t* pParserCmdInfo);

void Parser_LoraSetAdr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetAggregatedDutyCycle(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetAppKey(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetAppSKey(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetAutoReply(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetBatLevel(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetChannelFreq(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetChannelStatus(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetClass(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetCrtDataRate(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetCryptoDevEnabled(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetDatarateRange(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetDevAddr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetDevEui(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetDevEuiArray(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetDevNonce(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetDownlinkCounter(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetJoinBackoff(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetJoinEui(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetJoinEuiArray(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetJoinNonceType(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetLbt(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMaxFcntPdsUpdtVal(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMcast(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMcastAppsKey(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMcastDevAddr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMcastDr(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMcastFreq(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetMcastNwksKey(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetNwkSKey(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetReTxNb(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetRepsNb(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetRx2WindowParams(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetRxDelay1(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetSubBandStatus(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetSyncWord(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetTestModeEnabled (parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetTxPower(parserCmdInfo_t* pParserCmdInfo);
void Parser_LoraSetUplinkCounter(parserCmdInfo_t* pParserCmdInfo);

void Parser_LorawanInit(void);
#endif /* _PARSER_LORAWAN_H */