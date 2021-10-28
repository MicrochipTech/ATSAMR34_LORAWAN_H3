/**
* \file  conf_regparams.h
*
* \brief LORAWAN Regional Parameter Configuration
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




#ifndef CONF_REGPARAMS_H_INCLUDED
#define CONF_REGPARAMS_H_INCLUDED

/*****************************************************************************/
/* LoRaWAN Regional configuration parameters                                */
/*****************************************************************************/

#if (!(NA_BAND == 1)  && !(AS_BAND == 1) && !(AU_BAND == 1) && !(EU_BAND == 1) && !(IND_BAND == 1) && !(JPN_BAND == 1) && !(KR_BAND == 1) )
#error "Error: Atleast one regional band should be enabled."
#endif

#if (NA_BAND == 1)

#define MAC_DEF_TX_POWER_NA                 (7)
#define MAC_DEF_TX_CURRENT_DATARATE_NA      (DR2)
#define MAC_DATARATE_MIN_NA                 (DR4)
#define MAC_DATARATE_MAX_NA                 (DR0)
#define FEATURES_SUPPORTED_NA               (FHSS_SUPPORT | PA_SUPPORT|JOIN_BACKOFF_SUPPORT)

#endif

#if (AS_BAND == 1)

#define MAC_DEF_TX_POWER_AS                  (1)
#define MAC_DEF_TX_CURRENT_DATARATE_AS       (DR3)
#define MAC_DATARATE_MIN_AS                  (DR7)
#define MAC_DATARATE_MAX_AS                  (DR0)
#define FEATURES_SUPPORTED_AS                (PA_SUPPORT | DUTY_CYCLE_SUPPORT|JOIN_BACKOFF_SUPPORT)

#endif

#if (AU_BAND == 1)

#define MAC_DEF_TX_POWER_AU                  (7)
#define MAC_DEF_TX_CURRENT_DATARATE_AU       (DR3)
#define MAC_DATARATE_MIN_AU                  (DR6)
#define MAC_DATARATE_MAX_AU                  (DR0)
#define FEATURES_SUPPORTED_AU                (FHSS_SUPPORT | PA_SUPPORT|JOIN_BACKOFF_SUPPORT)

#endif

#if (EU_BAND == 1)

#define MAC_DEF_TX_POWER_EU                 (1)
#define MAC_DEF_TX_CURRENT_DATARATE_EU      (DR3)
#define MAC_DATARATE_MIN_EU                 (DR7)
#define MAC_DATARATE_MAX_EU                 (DR0)
#define FEATURES_SUPPORTED_EU               (JOIN_BACKOFF_SUPPORT)
#endif

#if (IND_BAND == 1)

#define MAC_DEF_TX_POWER_IN                  (1)
#define MAC_DEF_TX_CURRENT_DATARATE_IN       (DR3)
#define MAC_DATARATE_MIN_IN                  (DR7)
#define MAC_DATARATE_MAX_IN                  (DR0)
#define FEATURES_SUPPORTED_IN                (PA_SUPPORT|JOIN_BACKOFF_SUPPORT)
#endif

#if (JPN_BAND == 1)

#define MAC_DEF_TX_POWER_JP                  (1)
#define MAC_DEF_TX_CURRENT_DATARATE_JP       (DR3)
#define MAC_DATARATE_MIN_JP                  (DR7)
#define MAC_DATARATE_MAX_JP                  (DR0)

#define LBT_RSSI_SAMPLES_COUNT_JP            (5)
#define FEATURES_SUPPORTED_JP                (LBT_SUPPORT| DUTY_CYCLE_SUPPORT | PA_SUPPORT|JOIN_BACKOFF_SUPPORT)
#endif

#if (KR_BAND == 1)

#define MAC_DEF_TX_POWER_KR                   (1)
#define MAC_DEF_TX_CURRENT_DATARATE_KR        (DR3)
#define MAC_DATARATE_MIN_KR                   (DR5)
#define MAC_DATARATE_MAX_KR                   (DR0)

#define LBT_RSSI_SAMPLES_COUNT_KR             (10)
#define FEATURES_SUPPORTED_KR                 (LBT_SUPPORT | PA_SUPPORT|JOIN_BACKOFF_SUPPORT)
#endif

#if (KR_BAND == 1 || JPN_BAND == 1)

/*Number of Scan retries*/
#define LBT_MAX_RETRY_CHANNELS                (5)

#endif

#endif /* CONF_REGPARAMS_H_INCLUDED */

/* eof conf_regparams.h */