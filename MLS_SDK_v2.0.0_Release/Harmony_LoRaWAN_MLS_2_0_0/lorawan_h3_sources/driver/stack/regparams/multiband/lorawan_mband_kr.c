/**
* \file  lorawan_kr.c
*
* \brief LoRaWAN KOREAN file
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

#if (KR_BAND == 1)
/*Init Functions's*/



/*****************************CONSTANTS ***************************************/
static const ChannelParams_t DefaultChannels920KR[] = {
    LC0_920_KR,
    LC1_920_KR,
    LC2_920_KR
};

static const OthChannelParams_t AdvChannels920KR[] = {
    ADV_LC0_920_KR,
    ADV_LC1_920_KR,
    ADV_LC2_920_KR
};

static const DRParams_t DefaultDrParamsKR[] = {
    DR0_PARAMS_KR,
    DR1_PARAMS_KR,
    DR2_PARAMS_KR,
    DR3_PARAMS_KR,
    DR4_PARAMS_KR,
    DR5_PARAMS_KR
};

#if (ENABLE_PDS == 1)
#define PDS_REG_KR_CH_PARAM_1_ADDR                   ((uint8_t *)&(RegParams.cmnParams.paramsType2.chParams[MAX_CHANNELS_T2 - MAX_CHANNELS_T2]))
#define PDS_REG_KR_CH_PARAM_2_ADDR                   ((uint8_t *)&(RegParams.cmnParams.paramsType2.othChParams[MAX_CHANNELS_T2 - MAX_CHANNELS_T2]))

#define PDS_REG_KR_CH_PARAM_1_SIZE                   sizeof(RegParams.cmnParams.paramsType2.chParams)
#define PDS_REG_KR_CH_PARAM_2_SIZE                   sizeof(RegParams.cmnParams.paramsType2.othChParams)

#define PDS_REG_KR_CH_PARAM_1_OFFSET                  (PDS_FILE_START_OFFSET)
#define PDS_REG_KR_CH_PARAM_2_OFFSET                  (PDS_REG_KR_CH_PARAM_1_OFFSET + PDS_SIZE_OF_ITEM_HDR + PDS_REG_KR_CH_PARAM_1_SIZE)

/* PDS Reg Params KR Item declaration */

const ItemMap_t pds_reg_kr_fid1_item_list[] = {
    DECLARE_ITEM(PDS_REG_KR_CH_PARAM_1_ADDR,
    PDS_FILE_REG_KR_06_IDX,
    (uint8_t)PDS_REG_KR_CH_PARAM_1,
    PDS_REG_KR_CH_PARAM_1_SIZE,
    PDS_REG_KR_CH_PARAM_1_OFFSET),
    DECLARE_ITEM(PDS_REG_KR_CH_PARAM_2_ADDR,
    PDS_FILE_REG_KR_06_IDX,
    (uint8_t)PDS_REG_KR_CH_PARAM_2,
    PDS_REG_KR_CH_PARAM_2_SIZE,
    PDS_REG_KR_CH_PARAM_2_OFFSET)
};

PdsOperations_t aRegKrFid1PdsOps[PDS_REG_KR_FID1_MAX_VALUE];
void LorawanReg_KR_Pds_Cb(void);

#endif
#endif

/****************************** FUNCTIONS *************************************/

StackRetStatus_t LORAReg_InitKR(IsmBand_t ismBand)
{
    StackRetStatus_t result = LORAWAN_SUCCESS;

#if (KR_BAND == 1)

    RegParams.TxCurDataRate = MAC_DEF_TX_CURRENT_DATARATE_KR;
    RegParams.maxChannels = MAX_CHANNELS_KR;
    RegParams.maxSubBands = MAX_NUM_SUBBANDS_KR;
    RegParams.MacTxPower = MAC_DEF_TX_POWER_KR;
    RegParams.pChParams = &RegParams.cmnParams.paramsType2.chParams[0];
    RegParams.pDrParams = &RegParams.cmnParams.paramsType2.DRParams[0];
    RegParams.pOtherChParams = &RegParams.cmnParams.paramsType2.othChParams[0];
    RegParams.pDutyCycleTimer = &RegParams.cmnParams.paramsType2.DutyCycleTimer;
    RegParams.pJoinDutyCycleTimer = &RegParams.joinDutyCycleTimer;
    RegParams.pJoinBackoffTimer = &RegParams.joinBackoffTimer;
    RegParams.DefRx1DataRate = MAC_RX1_WINDOW_DATARATE_KR;
    RegParams.DefRx2DataRate = MAC_RX2_WINDOW_DATARATE_KR;
    RegParams.DefRx2Freq = MAC_RX2_WINDOW_FREQ_KR;
    RegParams.MinNewChIndex = MIN_CHANNEL_INDEX_KR;
    RegParams.FeaturesSupport = FEATURES_SUPPORTED_KR;
    RegParams.minDataRate = MAC_DATARATE_MIN_KR;
    RegParams.maxDataRate = MAC_DATARATE_MAX_KR;
    RegParams.cmnParams.paramsType2.LBTScanPeriod = LBT_SCAN_PERIOD_KR;
    RegParams.cmnParams.paramsType2.LBTSignalThreshold = LBT_SIGNAL_THRESHOLD_KR;
    RegParams.cmnParams.paramsType2.LBT_RSSISamplesCount = LBT_RSSI_SAMPLES_COUNT_KR;
    RegParams.cmnParams.paramsType2.minNonDefChId = 3;
    RegParams.Rx1DrOffset = 5;
    RegParams.maxTxPwrIndx = 7;
    RegParams.defTxPwrIndx = MAC_DEF_TX_POWER_KR;
    RegParams.maxTxPwr = DEFAULT_EIRP_KR_HF;
    RegParams.cmnParams.paramsType2.LBTTimer.timerId = regTimerId[0];
    RegParams.pJoinBackoffTimer->timerId = regTimerId[1];
    RegParams.pJoinDutyCycleTimer->timerId = regTimerId[2];
    RegParams.pDutyCycleTimer->timerId = regTimerId[3];
    RegParams.pJoinDutyCycleTimer->remainingtime =0;
    RegParams.joinbccount =0;
    RegParams.joinDutyCycleTimeout =0;
    RegParams.aggregatedDutyCycleTimeout = 0;
    RegParams.band = ismBand;

    if(ismBand == ISM_KR920)
    {
        InitDefault920ChannelsKR();

        memcpy (RegParams.pDrParams, DefaultDrParamsKR, sizeof(DefaultDrParamsKR) );
        for(int8_t dataRate = 0; dataRate < RegParams.maxDataRate; dataRate++)
        {
            RegParams.pDrParams[dataRate].modulation = MODULATION_LORA;
            RegParams.pDrParams[dataRate].bandwidth = BW_125KHZ;
        }
#if (ENABLE_PDS == 1)

        /*Fill PDS item id in RegParam Structure */
        RegParams.regParamItems.fileid = PDS_FILE_REG_KR_06_IDX;
        RegParams.regParamItems.ch_param_1_item_id = PDS_REG_KR_CH_PARAM_1;
        RegParams.regParamItems.ch_param_2_item_id = PDS_REG_KR_CH_PARAM_2;
        RegParams.regParamItems.band_item_id = 0;
        RegParams.regParamItems.lastUsedSB = 0;

        PdsFileMarks_t filemarks;
        /* File ID KR - Register */
        filemarks.fileMarkListAddr = aRegKrFid1PdsOps;
        filemarks.numItems =  (uint8_t)(PDS_REG_KR_FID1_MAX_VALUE & 0x00FF);
        filemarks.itemListAddr = (ItemMap_t *)&pds_reg_kr_fid1_item_list;
        filemarks.fIDcb = LorawanReg_KR_Pds_Cb;
        PDS_RegFile(PDS_FILE_REG_KR_06_IDX,filemarks);

#endif
    }
    else
    {
        result = UNSUPPORTED_BAND;
    }

    LORAREG_InitGetAttrFnPtrsKR();
    LORAREG_InitValidateAttrFnPtrsKR();
    LORAREG_InitSetAttrFnPtrsKR();
#else
    result = UNSUPPORTED_BAND;
#endif
    return result;
}


/*
 * \brief This function initializes all the IN865 Channels to default values
 */
#if (KR_BAND == 1)
void InitDefault920ChannelsKR (void)
{
    uint8_t i;
    memset (RegParams.pChParams, 0, sizeof(DefaultChannels920KR) );
    memset (RegParams.pOtherChParams, 0, sizeof(AdvChannels920KR) );
    memcpy (RegParams.pChParams, DefaultChannels920KR, sizeof(DefaultChannels920KR) );
    memcpy (RegParams.pOtherChParams, AdvChannels920KR, sizeof(AdvChannels920KR) );
    for (i = 3; i < RegParams.maxChannels; i++)
    {
        RegParams.pChParams[i].dataRange.value = UINT8_MAX;
        RegParams.pChParams[i].status = DISABLED;
        RegParams.pOtherChParams[i].joinRequestChannel = DISABLED;
        RegParams.cmnParams.paramsType2.txParams.maxEIRP = UINT8_MAX;
        RegParams.cmnParams.paramsType2.channelTimer[i] = 0;
    }
    RegParams.lastUsedChannelIndex = UINT8_MAX;
}
#if (ENABLE_PDS == 1)
/* PDS Callback */
void LorawanReg_KR_Pds_Cb(void)
{

}
#endif
#endif
