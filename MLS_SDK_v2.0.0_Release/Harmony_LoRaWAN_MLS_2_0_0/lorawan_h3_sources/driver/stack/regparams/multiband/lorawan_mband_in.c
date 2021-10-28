/**
* \file  lorawan_in.c
*
* \brief LoRaWAN INDIA file
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



/************************ PRIVATE FUNCTION PROTOTYPES *************************/
#include "lorawan_multiband.h"

#if(IND_BAND == 1)
/*Init Functions's*/
static void InitDefault865Channels (void);


/*****************************CONSTANTS ***************************************/
static const ChannelParams_t DefaultChannels865[] = {
    LC0_865_IN,
    LC1_865_IN,
    LC2_865_IN
};

static const OthChannelParams_t AdvChannels865[] = {
    ADV_LC0_865_IN,
    ADV_LC1_865_IN,
    ADV_LC2_865_IN
};

static const DRParams_t DefaultDrParamsIN[] = {
    DR0_PARAMS_IN,
    DR1_PARAMS_IN,
    DR2_PARAMS_IN,
    DR3_PARAMS_IN,
    DR4_PARAMS_IN,
    DR5_PARAMS_IN,
    DR6_PARAMS_IN,
    DR7_PARAMS_IN,
};

#if (ENABLE_PDS == 1)

#define PDS_REG_IND_CH_PARAM_1_ADDR                      ((uint8_t *)&(RegParams.cmnParams.paramsType2.chParams[MAX_CHANNELS_T2 - MAX_CHANNELS_T2]))
#define PDS_REG_IND_CH_PARAM_2_ADDR                      ((uint8_t *)&(RegParams.cmnParams.paramsType2.othChParams[MAX_CHANNELS_T2 - MAX_CHANNELS_T2]))

#define PDS_REG_IND_CH_PARAM_1_SIZE                     sizeof(RegParams.cmnParams.paramsType2.chParams)
#define PDS_REG_IND_CH_PARAM_2_SIZE                     sizeof(RegParams.cmnParams.paramsType2.othChParams)

#define PDS_REG_IND_CH_PARAM_1_OFFSET                    (PDS_FILE_START_OFFSET)
#define PDS_REG_IND_CH_PARAM_2_OFFSET                    (PDS_REG_IND_CH_PARAM_1_OFFSET + PDS_SIZE_OF_ITEM_HDR + PDS_REG_IND_CH_PARAM_1_SIZE)


/* PDS Reg Params Ind Item declaration */

const ItemMap_t pds_reg_ind_item_list[] = {
    DECLARE_ITEM(PDS_REG_IND_CH_PARAM_1_ADDR,
    PDS_FILE_REG_IND_07_IDX,
    (uint8_t)PDS_REG_IND_CH_PARAM_1,
    PDS_REG_IND_CH_PARAM_1_SIZE,
    PDS_REG_IND_CH_PARAM_1_OFFSET),
    DECLARE_ITEM(PDS_REG_IND_CH_PARAM_2_ADDR,
    PDS_FILE_REG_IND_07_IDX,
    (uint8_t)PDS_REG_IND_CH_PARAM_2,
    PDS_REG_IND_CH_PARAM_2_SIZE,
    PDS_REG_IND_CH_PARAM_2_OFFSET)
};

PdsOperations_t aRegIndPdsOps[PDS_REG_IND_MAX_VALUE];

/* PDS Callback function */
void LorawanReg_IND_Pds_Cb(void);

#endif
#endif

/****************************** FUNCTIONS *************************************/

StackRetStatus_t LORAReg_InitIN(IsmBand_t ismBand)
{
    StackRetStatus_t result = LORAWAN_SUCCESS;
#if(IND_BAND == 1)
    RegParams.TxCurDataRate = MAC_DEF_TX_CURRENT_DATARATE_IN;
    RegParams.maxChannels = MAX_CHANNELS_IN;
    RegParams.maxSubBands = MAX_NUM_SUBBANDS_IN;
    RegParams.MacTxPower = MAC_DEF_TX_POWER_IN;
    RegParams.pChParams = &RegParams.cmnParams.paramsType2.chParams[0];
    RegParams.pDrParams = &RegParams.cmnParams.paramsType2.DRParams[0];
    RegParams.pOtherChParams = &RegParams.cmnParams.paramsType2.othChParams[0];
    RegParams.pDutyCycleTimer = &RegParams.cmnParams.paramsType2.DutyCycleTimer;
    RegParams.pJoinDutyCycleTimer = &RegParams.joinDutyCycleTimer;
    RegParams.pJoinBackoffTimer = &RegParams.joinBackoffTimer;
    RegParams.DefRx1DataRate = MAC_RX1_WINDOW_DATARATE_IN;
    RegParams.DefRx2DataRate = MAC_RX2_WINDOW_DATARATE_IN;
    RegParams.DefRx2Freq = MAC_RX2_WINDOW_FREQ_IN;
    RegParams.MinNewChIndex = MIN_CHANNEL_INDEX_IN;
    RegParams.FeaturesSupport = FEATURES_SUPPORTED_IN;
    RegParams.minDataRate = MAC_DATARATE_MIN_IN;
    RegParams.maxDataRate = MAC_DATARATE_MAX_IN;
    RegParams.cmnParams.paramsType2.minNonDefChId = 3;
    RegParams.Rx1DrOffset = 7;
    RegParams.maxTxPwrIndx = 10;
    RegParams.defTxPwrIndx = MAC_DEF_TX_POWER_IN;
    RegParams.maxTxPwr = DEFAULT_EIRP_IN;
    RegParams.pJoinDutyCycleTimer->timerId = regTimerId[0];
    RegParams.pJoinDutyCycleTimer->remainingtime = 0;
    RegParams.pJoinBackoffTimer->timerId = regTimerId[1];
    RegParams.pDutyCycleTimer->timerId = regTimerId[2];
    RegParams.joinbccount =0;
    RegParams.joinDutyCycleTimeout =0;
    RegParams.aggregatedDutyCycleTimeout = 0;
    RegParams.band = ismBand;

    if(ismBand == ISM_IND865)
    {
        InitDefault865Channels();
        RegParams.cmnParams.paramsType2.txParams.maxEIRP = DEFAULT_EIRP_IN;
        memcpy (RegParams.pDrParams, DefaultDrParamsIN, sizeof(DefaultDrParamsIN) );
#if (ENABLE_PDS == 1)

        /*Fill PDS item id in RegParam Structure */
        RegParams.regParamItems.fileid = PDS_FILE_REG_IND_07_IDX;
        RegParams.regParamItems.ch_param_1_item_id = PDS_REG_IND_CH_PARAM_1;
        RegParams.regParamItems.ch_param_2_item_id = PDS_REG_IND_CH_PARAM_2;
        RegParams.regParamItems.band_item_id = 0;
        RegParams.regParamItems.lastUsedSB = 0;

        PdsFileMarks_t filemarks;
        /* File ID IND - Register */
        filemarks.fileMarkListAddr = aRegIndPdsOps;
        filemarks.numItems =  (uint8_t)(PDS_REG_IND_MAX_VALUE & 0x00FF);
        filemarks.itemListAddr = (ItemMap_t *)&pds_reg_ind_item_list;
        filemarks.fIDcb = LorawanReg_IND_Pds_Cb;
        PDS_RegFile(PDS_FILE_REG_IND_07_IDX,filemarks);
#endif
    }
    else
    {
        result = LORAWAN_INVALID_PARAMETER;
    }

    LORAREG_InitGetAttrFnPtrsIN();
    LORAREG_InitValidateAttrFnPtrsIN();
    LORAREG_InitSetAttrFnPtrsIN();
#else
    result = UNSUPPORTED_BAND;
#endif
    return result;
}


/*
 * \brief This function initializes all the IN865 Channels to default values
 */
#if(IND_BAND == 1)
static void InitDefault865Channels (void)
{
    uint8_t i;
    memset (RegParams.pChParams, 0, sizeof(DefaultChannels865) );
    memset (RegParams.pOtherChParams, 0, sizeof(AdvChannels865) );
    memcpy (RegParams.pChParams, DefaultChannels865, sizeof(DefaultChannels865) );
    memcpy (RegParams.pOtherChParams, AdvChannels865, sizeof(AdvChannels865) );
    for (i = MIN_CHANNEL_INDEX_IN; i < MAX_CHANNELS_IN; i++)
    {
        RegParams.pChParams[i].dataRange.value = UINT8_MAX;
    }
}
#if (ENABLE_PDS == 1)
/* PDS Callback function */
void LorawanReg_IND_Pds_Cb(void)
{

}
#endif
#endif
