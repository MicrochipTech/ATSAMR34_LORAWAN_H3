/*******************************************************************************
  MPLAB Harmony LORAWAN Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    mls_app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the template source code for the MPLAB Harmony application.

 *******************************************************************************/
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
// *****************************************************************************
// *****************************************************************************
// Section: Include files
// *****************************************************************************
// *****************************************************************************
#include "mls.h"
#include "mls_app.h"
#include "temperature_sensor.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global variables
// *****************************************************************************
// *****************************************************************************

volatile bool mlsAppSerRxPendFlag = false;
volatile uint8_t mlsAppSerRxByte;

bool mlsAppSerRxStartFlag = false;
uint8_t mlsAppSerialBuffer;
bool mlsAppSerialReceived = false;

AppDataCb_t mlsAppDataCallback;
JoinResponseCb_t mlsAppJoinCallback;
SleepCallback_t mlsAppSleepWakeupCallback;

uint8_t mlsAppTimerSysRst;
bool mlsAppIsJoined;
uint8_t mlsAppBuf[UINT8_MAX];
uint8_t mlsAppBufLen;
LorawanSendReq_t mlsAppSendReq;
uint8_t mlsAppPeriodicTimer;
bool mlsAppPeriodicStartFlag = false;
IsmBand_t mlsAppISMBand;

float celsius;
float fahrenheit;

#ifndef CRYPTO_DEV_ENABLED
uint32_t mlsAppDevAddr = DEMO_DEVICE_ADDRESS;
uint8_t mlsAppNwkSKey[LORAWAN_SESSIONKEY_LENGTH] = DEMO_NETWORK_SESSION_KEY;
uint8_t mlsAppAppSKey[LORAWAN_SESSIONKEY_LENGTH] = DEMO_APPLICATION_SESSION_KEY;

uint8_t mlsAppDevEUI[8] = DEMO_DEVICE_EUI;
uint8_t mlsAppJoinEUI[8] = DEMO_JOIN_EUI;
uint8_t mlsAppAppKey[LORAWAN_SESSIONKEY_LENGTH] = DEMO_APPLICATION_KEY;
#endif /* #ifndef CRYPTO_DEV_ENABLED */

bool mlsAppMcastEn = DEMO_APP_MCAST_ENABLE;
uint32_t mlsAppMcastGrpAddr = DEMO_APP_MCAST_GROUP_ADDRESS;
uint8_t mlsAppMcastNwkSKey[LORAWAN_SESSIONKEY_LENGTH] = DEMO_APP_MCAST_NWK_SESSION_KEY;
uint8_t mlsAppMcastAppSKey[LORAWAN_SESSIONKEY_LENGTH] = DEMO_APP_MCAST_APP_SESSION_KEY;
uint8_t mlsAppMcastGid = DEMO_APP_MCAST_GROUPID;

#if (CERT_APP == 1)
bool mlsAppIsCertModeEnabled = false;
bool mlsAppIsDeactFport224 = true;

uint8_t mlsAppTimerSysRst;
uint8_t mlsAppTimerCertMode;
uint32_t mlsAppTimerCertModePeriod = CERT_APP_TIMEOUT;
uint8_t mlsAppCertMsgBuf[255];
uint8_t mlsAppCertMsgBufLen;
uint16_t mlsAppCertRxAppCnt = 0;
ActivationType_t mlsAppCertJoinType;
LorawanSendReq_t mlsAppCertSendReq;
uint8_t mlsAppCertFPort = CERT_APP_FPORT;
bool mlsAppCertFPortRxFlag = false;
bool mlsAppIsPktReceived = false;
bool mlsAppCertCnf = CERT_APP_TRANSMISSION_TYPE;
uint8_t mlsAppTimerCwTx;

uint8_t mlsAppCertDevEUI[8] = CERT_DEVICE_EUI;
uint8_t mlsAppCertJoinEUI[8] = CERT_APPLICATION_EUI;
uint8_t mlsAppCertAppKey[LORAWAN_SESSIONKEY_LENGTH] = CERT_APPLICATION_KEY;

uint32_t mlsAppCertDevAddr = CERT_DEVICE_ADDRESS;
uint8_t mlsAppCertAppSKey[LORAWAN_SESSIONKEY_LENGTH] = CERT_APPLICATION_SESSION_KEY;
uint8_t mlsAppCertNwkSKey[LORAWAN_SESSIONKEY_LENGTH] = CERT_NETWORK_SESSION_KEY;

#if (ENABLE_PDS == 1)
const ItemMap_t mlsAppCertPdsItems[] = {
    DECLARE_ITEM(PDS_CERT_APP_ENABLE_ADDR,
                 PDS_FILE_APP_DATA1_13_IDX,
                 (uint8_t) PDS_CERT_APP_ENABLE,
                 PDS_CERT_APP_ENABLE_SIZE,
                 PDS_CERT_APP_ENABLE_OFFSET),
    DECLARE_ITEM(PDS_DEACTIVATE_FPORT_ADDR,
                 PDS_FILE_APP_DATA1_13_IDX,
                 (uint8_t) PDS_DEACTIVATE_FPORT,
                 PDS_DEACTIVATE_FPORT_SIZE,
                 PDS_DEACTIVATE_FPORT_OFFSET)
};
#endif /* #if (ENABLE_PDS==1) */
#endif /* #if (CERT_APP == 1) */

// *****************************************************************************
// *****************************************************************************
// Section: Function definitions
// *****************************************************************************
// *****************************************************************************
void MlsAppResetCausePrint(void)
{
    RSTC_RESET_CAUSE rcause = RSTC_ResetCauseGet();
    printf("Last reset cause: ");

    switch (rcause)
    {
        case RSTC_RESET_CAUSE_POR_RESET:
            printf("Power-On Reset\r\n");
            break;

        case RSTC_RESET_CAUSE_BOD12_RESET:
            printf("Brown Out 12 Detector Reset\r\n");
            break;

        case RSTC_RESET_CAUSE_BOD33_RESET:
            printf("Brown Out 33 Detector Reset\r\n");
            break;

        case RSTC_RESET_CAUSE_EXT_RESET:
            printf("External Reset\r\n");
            break;

        case RSTC_RESET_CAUSE_WDT_RESET:
            printf("Watchdog Reset\r\n");
            break;

        case RSTC_RESET_CAUSE_SYST_RESET:
            printf("System Reset Request\r\n");
            break;

        case RSTC_RESET_CAUSE_BACKUP_RESET:
            printf("Backup Reset\r\n");
            break;

        default:
            break;
    }
}
//------------------------------------------------------------------------------

#if (CERT_APP == 1) && (ENABLE_PDS == 1)

PdsStatus_t MlsAppPdsDataRegister(void)
{
    PdsStatus_t stat = PDS_OK;

    PdsFileMarks_t fm;

    PdsOperations_t ops[PDS_CERT_APP_PARAM_ITEM_ID_MAX_VALUE];

    fm.fileMarkListAddr = ops;
    fm.numItems = (uint8_t) (PDS_CERT_APP_PARAM_ITEM_ID_MAX_VALUE & 0x00FF);
    fm.itemListAddr = (ItemMap_t *) mlsAppCertPdsItems;
    fm.fIDcb = MlsAppPdsFileId13Callback;

    PDS_RegFile(PDS_FILE_APP_DATA1_13_IDX, fm);

    if (PDS_OK != stat)
    {
        printf("PDS register file failed = 0x%02X", stat);
    }

    return stat;
}
//------------------------------------------------------------------------------

void MlsAppPdsFileId13Callback(void)
{
    return;
}
//------------------------------------------------------------------------------

#endif /* #if (CERT_APP == 1) && (ENABLE_PDS == 1) */

StackRetStatus_t MlsAppJoinReq(ActivationType_t type)
{
    StackRetStatus_t status;
#if (CERT_APP == 1)
    if (mlsAppIsCertModeEnabled)
    {
        StackRetStatus_t stat = MlsAppCertModeJoinParamSet(type);

        if (LORAWAN_SUCCESS != stat)
        {
            printf("Certification Join parameters initialization failed\r\n");
        }
    }
    else
#endif
    {
        StackRetStatus_t stat = MlsAppJoinParamSet(type);

        if (LORAWAN_SUCCESS != stat)
        {
            printf("\nJoin parameters initialization failed\r\n");
        }
    }

    printf("\r\n%s Join Request...\r\n", (LORAWAN_OTAA == type) ? "OTAA" : "ABP");
    status = LORAWAN_Join(type);

#if (CERT_APP == 1)
    mlsAppCertJoinType = type;
#endif

    return status;
}
//------------------------------------------------------------------------------

void MlsAppJoinReqCallback(StackRetStatus_t status)
{
    printf("Join response\r\n");

    if (LORAWAN_RADIO_BUSY == status)
    {
        printf("JoinAccept NOT received\r\n");
    }

    if (LORAWAN_SUCCESS != status)
    {
        printf("Join failed\r\n");
#if (CERT_APP == 1)
        if (mlsAppIsCertModeEnabled && (LORAWAN_OTAA == mlsAppCertJoinType))
        {
            printf("\r\nOTAA Join Request...\r\n");
            status = LORAWAN_Join(LORAWAN_OTAA);

            return;
        }
#endif
    }
    else
    {
        /* on successful join */
        bool bTrue = true;

        uint32_t newADR;

        /* Get the new device address */
        LORAWAN_GetAttr(DEV_ADDR, NULL, &newADR);
        LORAWAN_SetAttr(ADR, &bTrue);

        printf("Join success\r\n");
        printf("New device address : %08X\r\n", (unsigned int) newADR);

        /* Check for address conflict with multicast group addr */
        if (DEMO_APP_MCAST_GROUP_ADDRESS == newADR)
        {
            printf("Warn - %s:%d - Address conflict b/w DevAddr and McGroupAddr\r\n",
                   __FUNCTION__, __LINE__);
        }

#if (ENABLE_PDS == 1)
        PDS_StoreAll();
#endif
    }
    
    if (mlsAppJoinCallback)
    {
        mlsAppJoinCallback(status);
    }
}
//------------------------------------------------------------------------------

void MlsAppJoinReqCallbackNotifySet(JoinResponseCb_t func)
{
    mlsAppJoinCallback = func;
}
//------------------------------------------------------------------------------

StackRetStatus_t MlsAppSendReq(void)
{
    uint8_t dr;
    static uint8_t minDRFlag = 0;
    LorawanSendReq_t *req;
    LorawanStatus_t lwstat;
    StackRetStatus_t stat;
    uint32_t fcntup;
    uint16_t szavl;
    
    LORAWAN_GetAttr(LORAWAN_STATUS, NULL, &lwstat);

    if (!lwstat.networkJoined)
    {
        return LORAWAN_NWK_NOT_JOINED;
    }

#if (CERT_APP == 1)
    if (mlsAppIsCertModeEnabled)
    {
        mlsAppIsPktReceived = false;

        SwTimerStop(mlsAppTimerCertMode);

        SwTimerStart(mlsAppTimerCertMode,
                     MS_TO_US(mlsAppTimerCertModePeriod),
                     SW_TIMEOUT_RELATIVE,
                     MlsAppTimerCertModeCallback,
                     NULL
                     );

        if (CERT_APP_FPORT == mlsAppCertFPort)
        {
            mlsAppCertMsgBuf[0] = (uint8_t) (mlsAppCertRxAppCnt >> 8);

            mlsAppCertMsgBuf[1] = (uint8_t) mlsAppCertRxAppCnt;

            mlsAppCertMsgBufLen = 2;
        }
        else if (TEST_PORT_NB != mlsAppCertFPort)
        {
            memset(mlsAppCertMsgBuf, 0x00, sizeof (mlsAppCertMsgBuf));
            mlsAppCertMsgBufLen = 0;
        }

        mlsAppCertSendReq.buffer = mlsAppCertMsgBuf;
        mlsAppCertSendReq.bufferLength = mlsAppCertMsgBufLen;
        mlsAppCertSendReq.confirmed = mlsAppCertCnf;
        mlsAppCertSendReq.port = mlsAppCertFPort;
        req = &mlsAppCertSendReq;
    }
    else
#endif
    {
        TEMPSENSOR_Read((uint8_t *)&celsius);
        fahrenheit = MlsAppCelsiusToFahrenheit(celsius);
        snprintf((char *)mlsAppBuf, sizeof(mlsAppBuf), "%.1fC/%.1fF\n", celsius, fahrenheit);
        mlsAppBufLen = strlen((char *)mlsAppBuf);
        mlsAppSendReq.buffer = mlsAppBuf;
        mlsAppSendReq.bufferLength = mlsAppBufLen;
        mlsAppSendReq.confirmed = DEMO_APP_TRANSMISSION_TYPE;
        mlsAppSendReq.port = DEMO_APP_FPORT;
        req = &mlsAppSendReq;
        mlsAppBuf[mlsAppBufLen] = '\0';
        printf("Temperature Data: %s\r\n", mlsAppBuf);
    }

    LORAWAN_GetAttr(UPLINK_COUNTER, NULL, &fcntup);

    // For EU and NA lowest dr is 0
    if (minDRFlag)
    {
        uint8_t dr = 0;
        LORAWAN_SetAttr(CURRENT_DATARATE, &dr);
        minDRFlag = 0;
    }

    LORAWAN_GetAttr(CURRENT_DATARATE, NULL, &dr);
    LORAWAN_GetAttr(NEXT_PAYLOAD_SIZE, NULL, &szavl);
    
    stat = LORAWAN_Send(req);
    mlsAppSerRxStartFlag = false;
    
    if (stat != LORAWAN_SUCCESS)
    {
        goto RETPOINT;
    }
    
    printf("\r\n=== Uplink =============================\r\n");
    printf("DR     : %d\r\n", dr);
    printf("Type   : %sCnf\r\n", req->confirmed ? "" : "Un");
    printf("FPort  : %d", req->port);
    if (req->port == TEST_PORT_NB)
    {
        printf(" (reply for TEST port command)");
    }
    printf("\r\nFCntUp : %d\r\n", (unsigned int) fcntup);

#if (CERT_APP == 1)
    if (mlsAppIsCertModeEnabled)
    {
        printf("MaxSize: %d\r\n", szavl);
        printf("DataLen: %d\r\n", req->bufferLength);
    }
#endif

    printf("DataHex: ");
    uint8_t *msgIndex = req->buffer;

    //if the msg is DutVersionsAns,then send the next uplink in the lowest dr of specific band
    if (*msgIndex == 127)
    {
        minDRFlag = 1;
    }

    if (req->buffer && (req->bufferLength))
    {
        MlsAppPrintArrayU8(req->buffer, req->bufferLength);
    }
    else
    {
        printf("*** E M P T Y ***\r\n");
    }

RETPOINT:
    return stat;
}
//------------------------------------------------------------------------------

void MlsAppSendReqCallback(void *appHnd, appCbParams_t *data)
{
    uint32_t fcntdn;
    switch (data->evt)
    {
        default:
        {
            /* keep compiler happy */
            break;
        }

        case LORAWAN_EVT_TRANSACTION_COMPLETE:
        {
#if (CERT_APP == 1)
            if (mlsAppIsCertModeEnabled)
            {
                printf("\r\n--- Transaction Complete ---------------\r\n");

                if (LORAWAN_SUCCESS == data->param.transCmpl.status)
                {
                    if ((false == mlsAppIsPktReceived) && (mlsAppCertSendReq.confirmed))
                    {
                        /* CNF uplink may have received a ACK in empty frame */
                        mlsAppCertRxAppCnt++;
                    }

                    if (false == mlsAppIsPktReceived)
                    {
                        /* NS can send CPC command so check for RX */
                        mlsAppCertFPort = CERT_APP_FPORT;
                    }
                }
            }
            else
#endif
            {
                if (LORAWAN_SUCCESS == data->param.transCmpl.status)
                {
                    printf("Transmission Success\r\n");
                }
                else
                {
                    printf("\r\n--- Transaction Ended ------------------\r\n");

                    if (LORAWAN_NO_CHANNELS_FOUND == data->param.transCmpl.status)
                    {
                        uint32_t remtime;
                        LORAWAN_GetAttr(PENDING_DUTY_CYCLE_TIME, NULL, &remtime);
                        printf("\r\nPending duty cycle time: %dms\r\n",
                               (unsigned int) remtime);
                    }
                }
            }

            if (mlsAppDataCallback)
            {
                mlsAppDataCallback(appHnd, data);
            }

            break;
        }

        case LORAWAN_EVT_RX_DATA_AVAILABLE:
        {
#if (CERT_APP == 1)
            if (mlsAppIsCertModeEnabled)
            {
                mlsAppIsPktReceived = true;
                mlsAppCertRxAppCnt++;
            }
#endif
            LORAWAN_GetAttr(DOWNLINK_COUNTER, NULL, &fcntdn);
            printf("\r\n*** Received DL Data ***\r\n");
            printf("FPort  : %d\r\n", data->param.rxData.pData[0]);
            printf("FCntDn : %d\r\n", (unsigned int) fcntdn);

            if ((data->param.rxData.dataLength > 0) && (data->param.rxData.pData))
            {
                printf("Data   : ");

                MlsAppPrintArrayU8(data->param.rxData.pData + 1, data->param.rxData.dataLength - 1);
            }

#if (CERT_APP == 1)

            if (TEST_PORT_NB == data->param.rxData.pData[0])
            {
                if (MlsAppCertIsCmdValid(data->param.rxData.pData + 1, data->param.rxData.dataLength - 1))
                {
                    MlsAppCertCmdExecute(data->param.rxData.pData + 1, data->param.rxData.dataLength - 1);
                }
            }

#endif /* #if (CERT_APP == 1) */
            
            if (mlsAppDataCallback)
            {
                mlsAppDataCallback(appHnd, data);
            }
            break;
        }
    }

    (void) appHnd;
}
//------------------------------------------------------------------------------

void MlsAppSendReqCallbackNotifySet(AppDataCb_t func)
{
    mlsAppDataCallback = func;
}
//------------------------------------------------------------------------------

void MlsAppInitialize(void)
{
    StackRetStatus_t retval;

#if !defined(CRYPTO_DEV_ENABLED) && (EDBG_EUI_READ == 1)
    MlsAppEdbgEuiRead(mlsAppDevEUI);
#endif /* #if !defined(CRYPTO_DEV_ENABLED) && (EDBG_EUI_READ == 1) */

#if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1)
    MlsAppWlr089U0EuiRead(mlsAppDevEUI);
#endif /* #if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1) */

#if (CERT_APP == 1) && (ENABLE_PDS == 1)
    MlsAppPdsDataRegister();
#endif /* #if (ENABLE_PDS == 1) */

    MlsAppResetCausePrint();
    printf("\r\nMicrochip LoRaWAN Stack - %s\r\n", STACK_VER);
    
    LORAWAN_Init(MlsAppSendReqCallback, MlsAppJoinReqCallback);
    Stack_Init();

    mlsAppSerRxStartFlag = false;

    retval = SwTimerCreate(&mlsAppPeriodicTimer);

#if (CERT_APP == 1)
    mlsAppCertRxAppCnt = 0;

    if (retval == LORAWAN_SUCCESS)
    {
        retval = SwTimerCreate(&mlsAppTimerCertMode);
    }

    if (retval == LORAWAN_SUCCESS)
    {
        retval = SwTimerCreate(&mlsAppTimerSysRst);
    }

    if (retval == LORAWAN_SUCCESS)
    {
        retval = SwTimerCreate(&mlsAppTimerCwTx);
    }
#endif

    if (retval != LORAWAN_SUCCESS)
    {
        printf("Application Stopped\r\n");
        while (1);
    }
    
    TEMPSENSOR_Initialize();
}

StackRetStatus_t MlsAppSet(IsmBand_t ismBand, const uint16_t index)
{
    StackRetStatus_t status;
    bool joinBackoffEn = false;

#if (NA_BAND == 1 || AU_BAND == 1)
#if (RANDOM_NW_ACQ == 0)
    ChannelParameters_t chParam;
    uint8_t minAllowed125kHz, maxAllowed125kHz, allowed500kHz;
    if ((ismBand == ISM_NA915) || (ismBand == ISM_AU915))
    {
#define MAX_NA_CHANNELS 72
#define MAX_SUBBAND_CHANNELS 8
        
        minAllowed125kHz = (SUBBAND - 1) * MAX_SUBBAND_CHANNELS;
        maxAllowed125kHz = ((SUBBAND - 1) * MAX_SUBBAND_CHANNELS) + 7;
        allowed500kHz = SUBBAND + 63;

        for (chParam.channelId = 0; chParam.channelId < MAX_NA_CHANNELS; chParam.channelId++)
        {
            if ((chParam.channelId >= minAllowed125kHz) && (chParam.channelId <= maxAllowed125kHz))
            {
                chParam.channelAttr.status = true;
            }
            else if (chParam.channelId == allowed500kHz)
            {
                chParam.channelAttr.status = true;
            }
            else
            {
                chParam.channelAttr.status = false;
            }
            LORAWAN_SetAttr(CH_PARAM_STATUS, &chParam);
        }
    }
#endif
#endif
    /*
     * Disabled Join backoff in Demo application
     *     
     * Needs to be enabled in Production Environment Ref Section
     */
    LORAWAN_SetAttr(JOIN_BACKOFF_ENABLE, &joinBackoffEn);

#ifdef CRYPTO_DEV_ENABLED
    bool cryptoDevEn = true;
    LORAWAN_SetAttr(CRYPTODEVICE_ENABLED, &cryptoDevEn);
#endif

#if (CERT_APP == 1)
    if (mlsAppIsCertModeEnabled)
    {
        /* Initialize the join parameters for  */
        status = MlsAppCertModeJoinParamSet(CERT_APP_ACTIVATION_TYPE);
        if (LORAWAN_SUCCESS != status)
        {
            printf("\nCertification Join parameters initialization failed\n\r");
            return status;
        }
    }
    else
#endif
    {
        /* Initialize the join parameters for Demo application */
        status = MlsAppJoinParamSet(DEMO_APP_ACTIVATION_TYPE);
        if (LORAWAN_SUCCESS != status)
        {
            printf("\nJoin parameters initialization failed\n\r");
            return status;
        }
    }

#if (CERT_APP == 1)
    if (mlsAppIsCertModeEnabled)
    {
        status = MlsAppEdClassSet(CERT_APP_ENDDEVICE_CLASS);
    }
    else
#endif
    {
        status = MlsAppEdClassSet(DEMO_APP_ENDDEVICE_CLASS);
    }

    if (LORAWAN_SUCCESS != status)
    {
        printf("\nUnsupported Device Type\n\r");
        return status;
    }

    /* Send Join request for Demo application */
#if (CERT_APP == 1)
    if (mlsAppIsCertModeEnabled)
    {
        status = LORAWAN_Join(CERT_APP_ACTIVATION_TYPE);
    }
    else
#endif /* #if (CERT_APP == 1) */
    {
        status = LORAWAN_Join(DEMO_APP_ACTIVATION_TYPE);
    }

    return status;
}
//------------------------------------------------------------------------------

StackRetStatus_t MlsAppJoinParamSet(ActivationType_t type)
{
    StackRetStatus_t status = LORAWAN_SUCCESS;

    printf("\r\n========= Demo Join Parameters =========\r\n");

    JoinNonceType_t jnType = APP_JOIN_NONCE_TYPE;
    LORAWAN_SetAttr(JOIN_NONCE_TYPE, &jnType);

#ifndef CRYPTO_DEV_ENABLED
    switch (type)
    {
        default:
            break;

        case LORAWAN_ABP:
        {
            status = LORAWAN_SetAttr(DEV_ADDR, &mlsAppDevAddr);
            if (LORAWAN_SUCCESS == status)
            {
                status = LORAWAN_SetAttr(APPS_KEY, mlsAppAppSKey);
            }

            if (LORAWAN_SUCCESS == status)
            {
                printf("AppSessionKey : ");
                MlsAppPrintArrayU8((uint8_t *) & mlsAppAppSKey, sizeof (mlsAppAppSKey));
                status = LORAWAN_SetAttr(NWKS_KEY, mlsAppNwkSKey);
            }

            if (LORAWAN_SUCCESS == status)
            {
                printf("NwkSessionKey : ");
                MlsAppPrintArrayU8((uint8_t *) & mlsAppNwkSKey, sizeof (mlsAppNwkSKey));
            }

            break;
        }

        case LORAWAN_OTAA:
        {
            status = LORAWAN_SetAttr(DEV_EUI, mlsAppDevEUI);
            if (LORAWAN_SUCCESS == status)
            {
                printf("DevEUI  : ");
                MlsAppPrintArrayU8((uint8_t *) & mlsAppDevEUI, sizeof (mlsAppDevEUI));
                status = LORAWAN_SetAttr(JOIN_EUI, mlsAppJoinEUI);
            }

            if (LORAWAN_SUCCESS == status)
            {
                printf("JoinEUI : ");
                MlsAppPrintArrayU8((uint8_t *) & mlsAppJoinEUI, sizeof (mlsAppJoinEUI));
                status = LORAWAN_SetAttr(APP_KEY, mlsAppAppKey);
            }
            if (LORAWAN_SUCCESS == status)
            {
                printf("AppKey  : ");
                MlsAppPrintArrayU8((uint8_t *) & mlsAppAppKey, sizeof (mlsAppAppKey));
            }
            break;
        }
    }
#endif
    return status;
}
//------------------------------------------------------------------------------

#if (CERT_APP == 1)

StackRetStatus_t MlsAppCertModeJoinParamSet(ActivationType_t type)
{
    StackRetStatus_t status = LORAWAN_SUCCESS;
#ifdef CRYPTO_DEV_ENABLED
    bool cryptoDevEn = true;
    status = LORAWAN_SetAttr(CRYPTODEVICE_ENABLED, &cryptoDevEn);
#endif
    printf("\r\n==== Certification Join Parameters =====\r\n");

#ifndef CRYPTO_DEV_ENABLED
    if (LORAWAN_ABP == type)
    {
        if (LORAWAN_SUCCESS == status)
        {
            status = LORAWAN_SetAttr(DEV_ADDR, &mlsAppCertDevAddr);
        }
        if (LORAWAN_SUCCESS == status)
        {
            printf("DevAddr : 0x%lx\r\n", mlsAppCertDevAddr);
            status = LORAWAN_SetAttr(APPS_KEY, mlsAppCertAppSKey);
        }
        if (LORAWAN_SUCCESS == status)
        {
            printf("AppSKey : ");
            MlsAppPrintArrayU8((uint8_t *) & mlsAppCertAppSKey, sizeof (mlsAppCertAppSKey));
            status = LORAWAN_SetAttr(NWKS_KEY, mlsAppCertNwkSKey);
        }
        if (LORAWAN_SUCCESS == status)
        {
            printf("NwkSKey : ");
            MlsAppPrintArrayU8((uint8_t *) & mlsAppCertNwkSKey, sizeof (mlsAppCertNwkSKey));
        }
    }
    else
    {
        if (LORAWAN_SUCCESS == status)
        {
            status = LORAWAN_SetAttr(DEV_EUI, mlsAppCertDevEUI);
        }
        if (LORAWAN_SUCCESS == status)
        {
            printf("DevEUI  : ");
            MlsAppPrintArrayU8((uint8_t *) & mlsAppCertDevEUI, sizeof (mlsAppCertDevEUI));
            status = LORAWAN_SetAttr(JOIN_EUI, mlsAppCertJoinEUI);
        }
        if (LORAWAN_SUCCESS == status)
        {
            printf("JoinEUI : ");
            MlsAppPrintArrayU8((uint8_t *) & mlsAppCertJoinEUI, sizeof (mlsAppCertJoinEUI));
            status = LORAWAN_SetAttr(APP_KEY, mlsAppCertAppKey);
        }
        if (LORAWAN_SUCCESS == status)
        {
            printf("AppKey  : ");
            MlsAppPrintArrayU8((uint8_t *) & mlsAppCertAppKey, sizeof (mlsAppCertAppKey));
        }
    }
#endif /* #ifndef CRYPTO_DEV_ENABLED */
    return status;
}
//------------------------------------------------------------------------------

#endif

StackRetStatus_t MlsAppEdClassSet(EdClass_t edclass)
{
    StackRetStatus_t status = LORAWAN_SUCCESS;
    status = LORAWAN_SetAttr(EDCLASS, &edclass);
    printf("Device Class is %c\r\n", (edclass == CLASS_A) ? 'A' : 'C');
    if ((LORAWAN_SUCCESS == status) && \
       ((CLASS_C | CLASS_B) & edclass) && \
       (DEMO_APP_MCAST_ENABLE))
    {
        MlsAppMcastParamSet();
    }

    return status;
}
//------------------------------------------------------------------------------

void MlsAppMcastParamSet(void)
{
    StackRetStatus_t status;
    LorawanMcastDevAddr_t mcAddr;
    LorawanMcastAppSkey_t mcAppSKey;
    LorawanMcastNwkSkey_t mcNwkSKey;
    LorawanMcastDlFreqeuncy_t mcDlFreq;
    LorawanMcastDatarate_t mcDr;
    LorawanMcastStatus_t mcStatus;
    ReceiveWindow2Params_t rx2WinParam;

    printf("\r\n========= Multicast Parameters =========\r\n");

    mcAddr.groupId = mlsAppMcastGid;
    mcAppSKey.groupId = mlsAppMcastGid;
    mcNwkSKey.groupId = mlsAppMcastGid;
    mcDlFreq.groupId = mlsAppMcastGid;
    mcDr.groupId = mlsAppMcastGid;
    mcStatus.groupId = mlsAppMcastGid;

    memcpy(&(mcAppSKey.mcastAppSKey), &mlsAppMcastAppSKey, LORAWAN_SESSIONKEY_LENGTH);
    mcAddr.mcast_dev_addr = mlsAppMcastGrpAddr;
    memcpy(&(mcNwkSKey.mcastNwkSKey), &mlsAppMcastNwkSKey, LORAWAN_SESSIONKEY_LENGTH);
    memcpy(&(mcStatus.status), &mlsAppMcastEn, sizeof (mlsAppMcastEn));
    LORAWAN_GetAttr(RX2_WINDOW_PARAMS, NULL, &rx2WinParam);
    mcDr.datarate = rx2WinParam.dataRate;
    mcDlFreq.dlFrequency = rx2WinParam.frequency;

    status = LORAWAN_SetAttr(MCAST_APPS_KEY, &mcAppSKey);
    if (status == LORAWAN_SUCCESS)
    {
        printf("McastAppSessionKey : ");
        MlsAppPrintArrayU8((uint8_t *)&(mcAppSKey.mcastAppSKey), LORAWAN_SESSIONKEY_LENGTH);
        status = LORAWAN_SetAttr(MCAST_NWKS_KEY, &mcNwkSKey);
    }

    if (status == LORAWAN_SUCCESS)
    {
        printf("McastNwkSessionKey : ");
        MlsAppPrintArrayU8((uint8_t *)&(mcNwkSKey.mcastNwkSKey), LORAWAN_SESSIONKEY_LENGTH);
        status = LORAWAN_SetAttr(MCAST_GROUP_ADDR, &mcAddr);
    }
    if (status == LORAWAN_SUCCESS)
    {
        printf("McastGroupAddr : 0x%lx\r\n", mcAddr.mcast_dev_addr);
        status = LORAWAN_SetAttr(MCAST_ENABLE, &mcStatus);
    }
    if (status == LORAWAN_SUCCESS)
    {
        status = LORAWAN_SetMulticastParam(MCAST_DATARATE, &mcDr);
    }
    if (status == LORAWAN_SUCCESS)
    {
        status = LORAWAN_SetMulticastParam(MCAST_FREQUENCY, &mcDlFreq);
    }
    else
    {
        printf("McastGroupAddrStatus : Failed\r\n");
    }

    if (status == LORAWAN_SUCCESS)
    {
        printf("MulticastStatus : Enabled\r\n");
    }
    else
    {
        printf("MulticastStatus : Failed\r\n");
    }

    printf("========================================\r\n");

}
//------------------------------------------------------------------------------

void MlsAppPrintArrayU8(uint8_t *array, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
        printf("%02X", *array);
        array++;
    }
    printf("\r\n");
}
//------------------------------------------------------------------------------

#ifdef CONF_PMM_ENABLE

PMM_Status_t MlsAppSleep(void)
{
    PMM_Status_t stat = PMM_SLEEP_REQ_DENIED;
    PMM_SleepReq_t sleepReq;

    /* Put the application to sleep */
    sleepReq.sleepTimeMs = DEMO_CONF_DEFAULT_APP_SLEEP_TIME_MS;
    sleepReq.pmmWakeupCallback = MlsAppSleepCallback;
    sleepReq.sleep_mode = CONF_PMM_SLEEPMODE_WHEN_IDLE;

    if (LORAWAN_ReadyToSleep((sleepReq.sleep_mode != SLEEP_MODE_STANDBY)))
    {
        MlsAppResourceDeinitialize();

        if (PMM_SLEEP_REQ_DENIED == PMM_Sleep(&sleepReq))
        {
            MlsAppResourceInitialize();
        }
        else
        {
            stat = PMM_SLEEP_REQ_PROCESSED;
        }
    }

    return stat;
}
//------------------------------------------------------------------------------

void MlsAppSleepCallback(uint32_t sleptDuration)
{
    MlsAppResourceInitialize();
    
    if (mlsAppSleepWakeupCallback)
    {
        mlsAppSleepWakeupCallback(sleptDuration);
    }
}
//------------------------------------------------------------------------------

void MlsAppSleepCallbackNotifySet(SleepCallback_t func)
{
    mlsAppSleepWakeupCallback = func;
}
//------------------------------------------------------------------------------

void MlsAppResourceInitialize(void)
{
    PORT_Initialize();

    SERCOM4_SPI_Initialize();

    SERCOM0_USART_Initialize();

    HAL_RadioInit();

    HAL_Radio_resources_init();

    MlsAppSerialInitialize();
}
//------------------------------------------------------------------------------

void MlsAppResourceDeinitialize(void)
{
    while (SERCOM0_USART_WriteIsBusy());

    SERCOM0_USART_TransmitterDisable();
    SERCOM0_USART_ReceiverDisable();

    SERCOM0_REGS->USART_INT.SERCOM_CTRLA &= ~(SERCOM_USART_INT_CTRLA_ENABLE_Msk);

    while (SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY);

    /* Disable Transceiver SPI Module */
    HAL_RadioDeInit();
}
//------------------------------------------------------------------------------

#endif /* #ifdef CONF_PMM_ENABLE */

#if (CERT_APP == 1)

void MlsAppTimerCertModeCallback(void)
{
    SwTimerStart(mlsAppTimerCertMode,
                 MS_TO_US(mlsAppTimerCertModePeriod),
                 SW_TIMEOUT_RELATIVE,
                 MlsAppTimerCertModeCallback,
                 NULL
                 );

    MlsAppSendReq();
}
//------------------------------------------------------------------------------

void MlsAppTimerSysRstCallback(void)
{
    SYS_RESET_SoftwareReset();
}
//------------------------------------------------------------------------------

void MlsAppCertCmdExecute(uint8_t *buffer, uint8_t buflen)
{
    StackRetStatus_t status;

    memset(mlsAppCertMsgBuf, 0x00, sizeof (mlsAppCertMsgBuf));
    printf("Command received: ");

    switch (buffer[0])
    {
        case CPC_PKG_VER_REQ:
        {
            printf("PackageVersionReq");
            mlsAppCertMsgBuf[0] = CPC_PKG_VER_ANS;
            mlsAppCertMsgBuf[1] = CPC_PKG_ID;
            mlsAppCertMsgBuf[2] = CPC_PKG_VER;

            mlsAppCertMsgBufLen = 3;
            mlsAppCertFPort = TEST_PORT_NB;
            
            break;
        }


        case CPC_DUT_RESET_REQ:
        {
            printf("DutResetReq");
            //All channels must be enabled after the reset
            ChannelParameters_t ch_params;
            for (ch_params.channelId = 0; ch_params.channelId <= 15; ch_params.channelId++)
            {
                ch_params.channelAttr.status = true;
                LORAWAN_SetAttr(CH_PARAM_STATUS, &ch_params);
            }

            bool new_adr;
            uint8_t dr = 0;

            LORAWAN_GetAttr(ADR, NULL, &new_adr);

            if (new_adr == 1)
            {
                LORAWAN_SetAttr(CURRENT_DATARATE, &dr);
            }

            delay_ms(1000);
            SwTimerStart(mlsAppTimerSysRst,
                         MS_TO_US(CPC_SYSRST_TIMER_PERIOD_MS),
                         SW_TIMEOUT_RELATIVE,
                         MlsAppTimerSysRstCallback,
                         NULL
                         );
            break;
        }


        case CPC_DUT_JOIN_REQ:
        {
            bool bTrue = true;
            printf("DutJoinReq");
#ifdef CRYPTO_DEV_ENABLED
            LORAWAN_SetAttr(CRYPTODEVICE_ENABLED, &bTrue);
#endif /* #ifdef CRYPTO_DEV_ENABLED */
            SwTimerStop(mlsAppTimerCertMode);
            //LORAWAN_Reset(mlsAppISMBand);

#if (ENABLE_PDS == 1)
            PDS_RestoreAll();
#endif
            LORAWAN_SetAttr(TEST_MODE_ENABLE, &bTrue);
            LORAWAN_SetAttr(DEV_EUI, mlsAppCertDevEUI);
            LORAWAN_SetAttr(JOIN_EUI, mlsAppCertJoinEUI);
            LORAWAN_SetAttr(APP_KEY, mlsAppCertAppKey);
            LORAWAN_SetAttr(ADR, &bTrue);

            MlsAppJoinReq(LORAWAN_OTAA);

            break;
        }


        case CPC_SWITCH_CLASS_REQ:
        {
            EdClass_t target_class = (1 << buffer[1]);
            printf("SwitchClassReq");
            printf("\nSwitch to class %c:%sOK\n\r",
                   (1 == target_class) ? 'A' : (2 == target_class) ? 'B' : 'C',
                   (LORAWAN_SUCCESS == LORAWAN_SetAttr(EDCLASS, &target_class)) ?
                   " " : "NOT");

            break;
        }


        case CPC_ADR_BIT_CHANGE_REQ:
        {
            bool new_adr;
            printf("AdrBitChangeReq");
            LORAWAN_SetAttr(ADR, &buffer[1]);
            LORAWAN_GetAttr(ADR, NULL, &new_adr);

            break;
        }


        case CPC_REGDCYCLE_CTRL_REQ:
        {
            bool new_regdcycle;
            printf("RegionalDutyCycleCtrlReq");
            LORAWAN_SetAttr(REGIONAL_DUTY_CYCLE, &buffer[1]);
            LORAWAN_GetAttr(REGIONAL_DUTY_CYCLE, NULL, &new_regdcycle);

            break;
        }


        case CPC_TX_PERIOD_CHANGE_REQ:
        {
            uint16_t periodicity[11] = {5, 5, 10, 20, 30, 40, 50, 60, 120, 240, 480};
            printf("TxPeriodicityChangeReq");
            if (10 >= buffer[1])
            {
                mlsAppTimerCertModePeriod = 1000 * periodicity[buffer[1]];

                SwTimerStop(mlsAppTimerCertMode);

                SwTimerStart(mlsAppTimerCertMode,
                             MS_TO_US(mlsAppTimerCertModePeriod),
                             SW_TIMEOUT_RELATIVE,
                             MlsAppTimerCertModeCallback,
                             NULL
                             );
            }

            break;
        }


        case CPC_TX_FRAMES_CTRL_REQ:
        {
            printf("TxFramesCtrlReq");
            switch (buffer[1])
            {
                case 0:
                {
                    mlsAppCertCnf = mlsAppCertCnf;
                    break;
                }
                case 1:
                {
                    mlsAppCertCnf = (bool) LORAWAN_UNCNF;
                    break;
                }
                case 2:
                {
                    mlsAppCertCnf = (bool) LORAWAN_CNF;
                    break;
                }
                default:
                {
                    // keep compiler happy
                    break;
                }
            }

            break;
        }


        case CPC_ECHO_INC_PAYLOAD_REQ:
        {
            printf("EchoPayloadReq");
            LORAWAN_GetAttr(NEXT_PAYLOAD_SIZE, NULL, &mlsAppCertMsgBufLen);
            mlsAppCertMsgBufLen = (mlsAppCertMsgBufLen <= buflen) ? mlsAppCertMsgBufLen : buflen;
            mlsAppCertMsgBuf[0] = CPC_ECHO_INC_PAYLOAD_ANS;
            for (uint8_t i = 1; i < mlsAppCertMsgBufLen; i++)
            {
                mlsAppCertMsgBuf[i] = (1 + buffer[i]) % UINT8_MAX;
            }
            if (mlsAppIsDeactFport224)
            {
                mlsAppCertFPort = CERT_APP_FPORT;
            }
            else
            {
                mlsAppCertFPort = TEST_PORT_NB;
            }

            break;
        }


        case CPC_RX_APP_CNT_REQ:
        {
            printf("RxAppCntReq");
            mlsAppCertMsgBuf[0] = CPC_RX_APP_CNT_ANS;
            mlsAppCertMsgBuf[1] = (uint8_t) (mlsAppCertRxAppCnt);
            mlsAppCertMsgBuf[2] = (uint8_t) (mlsAppCertRxAppCnt >> 8);
            mlsAppCertMsgBufLen = 3;
            mlsAppCertFPort = TEST_PORT_NB;
            break;
        }

        case CPC_RX_APP_CNT_RESET_REQ:
        {
            printf("RxAppCntResetReq");
            mlsAppCertRxAppCnt = 0;
            break;
        }

        case CPC_LINK_CHECK_REQ:
        {
            printf("LinkCheckReq");
            LORAWAN_SetAttr(SEND_LINK_CHECK_CMD, NULL);
            break;
        }

        case CPC_DEVICE_TIME_REQ:
        {
            printf("DeviceTimeReq");
            LORAWAN_SetAttr(SEND_DEVICE_TIME_CMD, NULL);
            break;
        }

        case CPC_PING_SLOT_INFO_REQ:
        {
            printf("PingSlotInfoReq");
            break;
        }

        case CPC_TX_CW_REQ:
        {
            uint8_t txpower = 0;
            uint16_t timeout = 0;
            uint32_t freq = 0;
            
            printf("TxCwReq");

            timeout = buffer[2];
            timeout |= ((uint16_t) buffer[1]) << 8;

            freq = buffer[5];
            freq |= ((uint32_t) buffer[4]) << 8;
            freq |= ((uint32_t) buffer[3]) << 16;
            freq *= 100U;

            txpower = buffer[6];

            RADIO_SetAttr(CHANNEL_FREQUENCY, (void *) &freq);
            RADIO_SetAttr(OUTPUT_POWER, (void *) &txpower);

            if (LORAWAN_SUCCESS == SwTimerStart(mlsAppTimerCwTx,
                                                MS_TO_US(timeout * 1000U), SW_TIMEOUT_RELATIVE,
                                                MlsAppTimerCwTxCallback, NULL))
            {
                RADIO_TransmitCW();
            }
            break;
        }

        case CPC_DUT_FPORT224_DISABLE_REQ:
        {
            bool disable = false;
            printf("DutFPort224DisableReq");
            mlsAppIsDeactFport224 = true;
#if (ENABLE_PDS == 1)
            PDS_STORE(PDS_DEACTIVATE_FPORT);
#endif
            LORAWAN_SetAttr(TEST_MODE_ENABLE, &disable);
            delay_ms(1000);
            SwTimerStart(mlsAppTimerSysRst,
                         MS_TO_US(CPC_SYSRST_TIMER_PERIOD_MS),
                         SW_TIMEOUT_RELATIVE,
                         MlsAppTimerSysRstCallback,
                         NULL
                         );

            break;
        }

        case CPC_DUT_VERSIONS_REQ:
        {
            printf("DutVersionsReq");
            mlsAppCertMsgBuf[0] = CPC_DUT_VERSIONS_ANS;

            // FwVersion
            mlsAppCertMsgBuf[1] = 1; // 1
            mlsAppCertMsgBuf[2] = 0; // 0
            mlsAppCertMsgBuf[3] = 4; // P_4

            // LrwanVersion
            mlsAppCertMsgBuf[4] = 1;
            mlsAppCertMsgBuf[5] = 0;
            mlsAppCertMsgBuf[6] = 4;

            // LrwanRpVersion
            mlsAppCertMsgBuf[7] = 1;
            mlsAppCertMsgBuf[8] = 0;
            mlsAppCertMsgBuf[9] = 4;

            mlsAppCertMsgBufLen = 10;
            mlsAppCertFPort = TEST_PORT_NB;

            //uint8_t dr = 0;
            //LORAWAN_SetAttr(CURRENT_DATARATE,&dr);

            break;
        }
        
        default:
        {
            if ((buffer[0] >= 0x23) && (buffer[0] <= 0x7c))
            {
                printf("RFU");
            }
            else if ((buffer[0] >= 0x80) && (buffer[0] <= 0xff))
            {
                printf("Proprietary");
            }
            break;
        }
    }
    printf("\r\n");
    (void) status;
}
//------------------------------------------------------------------------------

bool MlsAppCertIsCmdValid(uint8_t *buffer, uint8_t len)
{
    bool valid = false;
    switch (*buffer)
    {
        case CPC_TX_FRAMES_CTRL_REQ:
        case CPC_ECHO_INC_PAYLOAD_REQ:
        {
            valid = (len >= 1);
            break;
        }

        case CPC_PKG_VER_REQ:
        case CPC_DUT_RESET_REQ:
        case CPC_DUT_JOIN_REQ:
        case CPC_RX_APP_CNT_REQ:
        case CPC_RX_APP_CNT_RESET_REQ:
        case CPC_LINK_CHECK_REQ:
        case CPC_DEVICE_TIME_REQ:
        case CPC_DUT_FPORT224_DISABLE_REQ:
        case CPC_DUT_VERSIONS_REQ:
        {
            valid = (1 == len);
            break;
        }

        case CPC_SWITCH_CLASS_REQ:
        case CPC_ADR_BIT_CHANGE_REQ:
        case CPC_REGDCYCLE_CTRL_REQ:
        case CPC_TX_PERIOD_CHANGE_REQ:
        case CPC_PING_SLOT_INFO_REQ:
        {
            valid = (2 == len);
            break;
        }

        case CPC_TX_CW_REQ:
        {
            valid = (7 == len);
            break;
        }
    }

    if (!valid)
    {
        printf("\r\nCertification command received with invalid payload\r\n");
    }
    return valid;
}
//------------------------------------------------------------------------------

void MlsAppTimerCwTxCallback(void)
{
    RADIO_StopCW();
}
//------------------------------------------------------------------------------

#endif /* #if (CERT_APP == 1) */

void MlsAppSerialInitialize(void)
{
    SERCOM0_USART_WriteCallbackRegister(MlsAppSerialWriteCallback, (uintptr_t) NULL);

    SERCOM0_USART_ReadCallbackRegister(MlsAppSerialReadCallback, (uintptr_t) NULL);

    mlsAppSerRxPendFlag = false;

    mlsAppSerRxByte = '\0';
}
//------------------------------------------------------------------------------

void MlsAppSerialDataHandler(void)
{
    unsigned char rxchar = 0xff;
    
    SERCOM0_USART_Read((void *)&mlsAppSerRxByte, sizeof (uint8_t));

    if (mlsAppSerRxStartFlag)
    {
        if (MlsAppSerialRead(&rxchar))
        {
            switch (rxchar)
            {
                case '\b':
                case '\r':
                case '\n':
                case '\t':
                {
                    mlsAppSerialBuffer = (uint8_t) '\0';
                    break;
                }
                default:
                {
                    mlsAppSerRxStartFlag = false;

                    /* set the received character in buffer */
                    mlsAppSerialBuffer = (uint8_t) rxchar;
                    mlsAppSerialBuffer -= (uint8_t) '0';
                    
                    mlsAppSerialReceived = true;

                    break;
                }
            }
        }
    }
}
//------------------------------------------------------------------------------

bool MlsAppSerialRead(uint8_t* rxchar)
{
    if (mlsAppSerRxPendFlag)
    {
        *rxchar = mlsAppSerRxByte;
        mlsAppSerRxPendFlag = false;
        return true;
    }
    else
    {
        return false;
    }
}
//------------------------------------------------------------------------------

void MlsAppSerialReadCallback(uintptr_t ctx)
{
    if (SERCOM0_USART_ErrorGet() != USART_ERROR_NONE)
    {
        return;
    }
    else
    {
        mlsAppSerRxPendFlag = true;
    }
    (void) ctx;
}
//------------------------------------------------------------------------------

void MlsAppSerialWriteCallback(uintptr_t ctx)
{
    (void) ctx;
}
//------------------------------------------------------------------------------

bool MlsAppSerialIsCharPending(void)
{
    bool retval = mlsAppSerialReceived;
    
    mlsAppSerialReceived = false;
    
    return retval;
}
//------------------------------------------------------------------------------

#if !defined(CRYPTO_DEV_ENABLED) && (EDBG_EUI_READ == 1)

void MlsAppEdbgEuiRead(uint8_t *eui)
{
    uint8_t rdata[256];
    uint8_t wdata[2] = {0x51, 0xd2};

    SERCOM1_I2C_WriteRead(0x28, wdata, 2, rdata, 256);
    while (SERCOM1_I2C_IsBusy());

    memcpy(eui, rdata, sizeof (uint64_t));
}
#endif
//------------------------------------------------------------------------------

#if !defined(CRYPTO_DEV_ENABLED) && (WLR089U0_EUI_READ == 1)

void MlsAppWlr089U0EuiRead(uint8_t *eui)
{
    const uint8_t * const rdata = (uint8_t *)(WLR089U0_MACIEEEADDR_OFFSET);
    eui[0] = rdata[7];
    eui[1] = rdata[6];
    eui[2] = rdata[5];
    eui[3] = rdata[4];
    eui[4] = rdata[3];
    eui[5] = rdata[2];
    eui[6] = rdata[1];
    eui[7] = rdata[0];
}
#endif
//------------------------------------------------------------------------------

float MlsAppCelsiusToFahrenheit(float c)
{
    float f = (((c * 9.0f)/5.0f) + 32.0f);
    return f;

}
//------------------------------------------------------------------------------

/* EOF mls_app.c */
