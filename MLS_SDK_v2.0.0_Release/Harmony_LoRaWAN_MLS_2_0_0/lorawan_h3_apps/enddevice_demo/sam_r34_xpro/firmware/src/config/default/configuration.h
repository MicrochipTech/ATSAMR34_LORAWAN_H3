/*******************************************************************************
  System Configuration Header

  File Name:
    configuration.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "user.h"
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

/*** wolfCrypt Library Configuration ***/
#define MICROCHIP_PIC32
#define MICROCHIP_MPLAB_HARMONY
#define MICROCHIP_MPLAB_HARMONY_3
#define HAVE_MCAPI
#define SIZEOF_LONG_LONG 8
#define WOLFSSL_USER_IO
#define NO_WRITEV
#define NO_FILESYSTEM
#define USE_FAST_MATH
#define NO_PWDBASED
#define HAVE_MCAPI
#define WOLF_CRYPTO_CB  // provide call-back support
#define WOLFCRYPT_ONLY
#define WOLFSSL_HAVE_MCHP_HW_CRYPTO
// ---------- CRYPTO HARDWARE MANIFEST START ----------
#define WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238
#define WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_U2242
// ---------- CRYPTO HARDWARE MANIFEST END ----------
// ---------- FUNCTIONAL CONFIGURATION START ----------
#define NO_MD4
#define NO_MD5
#define NO_SHA // specifically, no SHA1 (legacy name)
#define NO_SHA256
#define NO_SHA224
#define NO_HMAC
#define NO_DES3
#define WOLFSSL_AES_128
#define NO_AES_192 // not supported by HW accelerator
#define NO_AES_256 // not supported by HW accelerator
#define WOLFSSL_AES_DIRECT
#define HAVE_AES_DECRYPT
#define WOLFSSL_HAVE_MCHP_HW_AES_DIRECT
#define HAVE_AES_ECB
#define WOLFSSL_HAVE_MCHP_HW_AES_ECB
#define HAVE_AES_CBC
#define WOLFSSL_HAVE_MCHP_HW_AES_CBC
#define WOLFSSL_CMAC
#define NO_RC4
#define NO_HC128
#define NO_RABBIT
#define NO_DH
#define NO_DSA
#define NO_RSA
#define NO_DEV_RANDOM
#define WC_NO_RNG
#define WC_NO_HASHDRBG
#define WC_NO_HARDEN
#define SINGLE_THREADED
#define NO_ASN
#define NO_SIG_WRAPPER
#define NO_ERROR_STRINGS
#define NO_WOLFSSL_MEMORY
// ---------- FUNCTIONAL CONFIGURATION END ----------



// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

// === MLS APPLICATION CONFIGURATION BEGIN ===

/******************************************************************************/
/* EndDevice Demo Configuration Macros                                        */
/******************************************************************************/
#define DEMO_APP_DEFAULT_FPORT              (1)
#define DEMO_APP_DEFAULT_UPLINK_PERIOD_MS   ((1000U) * (5))

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
#define EDBG_EUI_READ                       (1)

// -----------------------------------------------------------------------------
/******************************************************************************/
/* Shall ED read DevEUI from WLR089U0 NVM?                                    */
/******************************************************************************/
#define WLR089U0_EUI_READ                   (0)

// -----------------------------------------------------------------------------

/*
 * Enable one of the activation methods
 */
#define DEMO_APP_ACTIVATION_TYPE            LORAWAN_OTAA
//#define DEMO_APP_ACTIVATION_TYPE            LORAWAN_ABP

// -----------------------------------------------------------------------------

/*
 * Select the Type of Transmission - Confirmed(CNF) / Unconfirmed(UNCNF)
 */
#define DEMO_APP_TRANSMISSION_TYPE          LORAWAN_UNCNF
//#define DEMO_APP_TRANSMISSION_TYPE          LORAWAN_CNF

// -----------------------------------------------------------------------------

/*
 * Device Class
 */
#define DEMO_APP_ENDDEVICE_CLASS            CLASS_A
//#define DEMO_APP_ENDDEVICE_CLASS            CLASS_C

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
#define DEMO_CONF_DEFAULT_APP_SLEEP_TIME_MS     ((1000) * (1))

// -----------------------------------------------------------------------------


/* To join with NS supporting LW1.0.4 */
#define APP_JOIN_NONCE_TYPE                     JOIN_NONCE_INCREMENTAL

/* To join with NS supporting LW1.0.3, LW1.0.2, LW1.0.1 */
//#define APP_JOIN_NONCE_TYPE                     JOIN_NONCE_RANDOM


// -----------------------------------------------------------------------------

/*
 * Multicast Parameters
 */
#define DEMO_APP_MCAST_GROUPID                  (0)
#define DEMO_APP_MCAST_ENABLE                   (true)
#define DEMO_APP_MCAST_GROUP_ADDRESS            (0x0037CC56)
#define DEMO_APP_MCAST_APP_SESSION_KEY          {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6}
#define DEMO_APP_MCAST_NWK_SESSION_KEY          {0x3C, 0x8F, 0x26, 0x27, 0x39, 0xBF, 0xE3, 0xB7, 0xBC, 0x08, 0x26, 0x99, 0x1A, 0xD0, 0x50, 0x4D}

#define CERT_APP                                (1)

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
#define CERT_APP_ACTIVATION_TYPE                LORAWAN_OTAA
//#define CERT_APP_ACTIVATION_TYPE                LORAWAN_ABP
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



//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/
