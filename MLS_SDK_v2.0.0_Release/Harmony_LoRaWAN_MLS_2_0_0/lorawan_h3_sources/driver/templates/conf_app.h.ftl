<#if MLSSRC_BOOLEAN_APPCONFEN == true>
<#----------------------------------------------------------------------------
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
----------------------------------------------------------------------------->

// === MLS APPLICATION CONFIGURATION BEGIN ===

/******************************************************************************/
/* EndDevice Demo Configuration Macros                                        */
/******************************************************************************/
#define DEMO_APP_DEFAULT_FPORT              (${MLSSRC_INTEGER_APPFPORT})
#define DEMO_APP_DEFAULT_UPLINK_PERIOD_MS   ((1000U) * (${MLSSRC_INTEGER_APPUPLINKPERIOD}))

#define DEMO_APP_FPORT                      (DEMO_APP_DEFAULT_FPORT)
#define APP_PERIODIC_TIMER_PERIOD_MS        (DEMO_APP_DEFAULT_UPLINK_PERIOD_MS)

#define SUBBAND 1
#if ((SUBBAND < 1 ) || (SUBBAND > 8 ) )
#error " Invalid Value of Subband"
#endif

// -----------------------------------------------------------------------------
/******************************************************************************/
/* Shall ED read DevEUI from SAMR34XPRO EDBG?                                 */
/******************************************************************************/
<#if MLSSRC_COMBO_APPPROVSOURCE == "MANUAL" && MLSSRC_COMBO_APPDEVEUISRC == "SAMR34_XPRO_EDBG">
#define EDBG_EUI_READ                       (1)
<#else>
#define EDBG_EUI_READ                       (0)
</#if>

// -----------------------------------------------------------------------------
/******************************************************************************/
/* Shall ED read DevEUI from WLR089U0 NVM?                                    */
/******************************************************************************/
<#if MLSSRC_COMBO_APPPROVSOURCE == "MANUAL" && MLSSRC_COMBO_APPDEVEUISRC == "WLR089U0_MODULE_USERPAGE">
#define WLR089U0_EUI_READ                   (1)
<#else>
#define WLR089U0_EUI_READ                   (0)
</#if>

// -----------------------------------------------------------------------------

/*
 * Enable one of the activation methods
 */
<#if MLSSRC_COMBO_APPJOINTYPE == "OTAA">
#define DEMO_APP_ACTIVATION_TYPE            LORAWAN_OTAA
//#define DEMO_APP_ACTIVATION_TYPE            LORAWAN_ABP
<#else>
//#define DEMO_APP_ACTIVATION_TYPE            LORAWAN_OTAA
#define DEMO_APP_ACTIVATION_TYPE            LORAWAN_ABP
</#if>

// -----------------------------------------------------------------------------

/*
 * Select the Type of Transmission - Confirmed(CNF) / Unconfirmed(UNCNF)
 */
<#if MLSSRC_COMBO_APPMSGTYPE == "UnCnf">
#define DEMO_APP_TRANSMISSION_TYPE          LORAWAN_UNCNF
//#define DEMO_APP_TRANSMISSION_TYPE          LORAWAN_CNF
<#else>
//#define DEMO_APP_TRANSMISSION_TYPE          LORAWAN_UNCNF
#define DEMO_APP_TRANSMISSION_TYPE          LORAWAN_CNF
</#if>

// -----------------------------------------------------------------------------

/*
 * Device Class
 */
<#if MLSSRC_BOOLEAN_APPCLASSC == false>
#define DEMO_APP_ENDDEVICE_CLASS            CLASS_A
//#define DEMO_APP_ENDDEVICE_CLASS            CLASS_C
<#else>
//#define DEMO_APP_ENDDEVICE_CLASS            CLASS_A
#define DEMO_APP_ENDDEVICE_CLASS            CLASS_C
</#if>

// -----------------------------------------------------------------------------

/*
 * ABP Join Parameters
 */
#define DEMO_DEVICE_ADDRESS                     0x33333334
#define DEMO_APPLICATION_SESSION_KEY            {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x39}
#define DEMO_NETWORK_SESSION_KEY                {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30}

// -----------------------------------------------------------------------------

/*
 * OTAA Join Parameters
 */

#define DEMO_DEVICE_EUI                         {0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04}
#define DEMO_JOIN_EUI                           {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03}
#define DEMO_APPLICATION_KEY                    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03}

// -----------------------------------------------------------------------------

/*
 * This macro defines the application's default sleep duration in ms
 */
#define DEMO_CONF_DEFAULT_APP_SLEEP_TIME_MS     ((1000) * (${MLSSRC_INTEGER_APPSLEEPDURATION}))

// -----------------------------------------------------------------------------

<#if MLSSRC_COMBO_APPJOINNSVER == "From (>=) Lw1.0.4">

/* To join with NS supporting LW1.0.4 */
#define APP_JOIN_NONCE_TYPE                     JOIN_NONCE_INCREMENTAL

/* To join with NS supporting LW1.0.3, LW1.0.2, LW1.0.1 */
//#define APP_JOIN_NONCE_TYPE                     JOIN_NONCE_RANDOM

<#else>

/* To join with NS supporting LW1.0.4 */
//#define APP_JOIN_NONCE_TYPE                     JOIN_NONCE_INCREMENTAL

/* To join with NS supporting LW1.0.3, LW1.0.2, LW1.0.1 */
#define APP_JOIN_NONCE_TYPE                     JOIN_NONCE_RANDOM

</#if>

// -----------------------------------------------------------------------------

/*
 * Multicast Parameters
 */
#define DEMO_APP_MCAST_GROUPID                  (0)
#define DEMO_APP_MCAST_ENABLE                   (true)
#define DEMO_APP_MCAST_GROUP_ADDRESS            (0x0037CC56)
#define DEMO_APP_MCAST_APP_SESSION_KEY          {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6}
#define DEMO_APP_MCAST_NWK_SESSION_KEY          {0x3C, 0x8F, 0x26, 0x27, 0x39, 0xBF, 0xE3, 0xB7, 0xBC, 0x08, 0x26, 0x99, 0x1A, 0xD0, 0x50, 0x4D}

<#if MLSSRC_BOOLEAN_APPCERTMODE == true>
#define CERT_APP                                (1)
<#else>
#define CERT_APP                                (0)
</#if>

/******************************************************************************/
/* EndDevice Certification Configuration Macros                               */
/******************************************************************************/
#if (CERT_APP == 1)
#define TEST_PORT_NB                            (224)
#define CERT_APP_FPORT                          (DEMO_APP_DEFAULT_FPORT)
#define CERT_APP_TIMEOUT                        (DEMO_APP_DEFAULT_UPLINK_PERIOD_MS)
/*
 * Define the Sub band of Channels to be enabled by default for the application
 */
#define SUBBAND 1
#if ((SUBBAND < 1 ) || (SUBBAND > 8 ) )
#error " Invalid Value of Subband"
#endif
/*
 * Enable one of the activation methods
 */
<#if MLSSRC_COMBO_APPJOINTYPE == "OTAA">
#define CERT_APP_ACTIVATION_TYPE                LORAWAN_OTAA
//#define CERT_APP_ACTIVATION_TYPE                LORAWAN_ABP
<#else>
//#define CERT_APP_ACTIVATION_TYPE                LORAWAN_OTAA
#define CERT_APP_ACTIVATION_TYPE                LORAWAN_ABP
</#if>
/*
 * Certification is available only for Class A device
 */
#define CERT_APP_ENDDEVICE_CLASS                CLASS_A
/*
 * Select the Type of Transmission - Confirmed(CNF) / Unconfirmed(UNCNF)
 */
#define CERT_APP_TRANSMISSION_TYPE              LORAWAN_UNCNF
//#define CERT_APP_TRANSMISSION_TYPE            LORAWAN_CNF
/*
 * ABP Join Parameters
 */
#define CERT_DEVICE_ADDRESS                     0x11111111
#define CERT_APPLICATION_SESSION_KEY            {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}
#define CERT_NETWORK_SESSION_KEY                {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}
/*
 * OTAA Join Parameters
 */
#define CERT_DEVICE_EUI                         {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}
#define CERT_APPLICATION_EUI                    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}
#define CERT_APPLICATION_KEY                    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11}
#endif /* CERT_APP == 1 */

// === MLS APPLICATION CONFIGURATION END ===
</#if>