/*******************************************************************************
  Regional Parameters configuration header

  File Name:
    conf_regparams.h

  Summary:
    This file contains the RegParams configuration settings

  Description:
    This file contains the RegParams configuration settings. This file must be
    included in MLS project to configure the RegParams functionalities.

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
#ifndef CONF_REGPARAMS_H
#define CONF_REGPARAMS_H
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END
//------------------------------------------------------------------------------
// Includes RegParams specific configurations
//------------------------------------------------------------------------------
//
// NOTE: This file MUST be included after 'lorawan_multiband.h'
//
// *****************************************************************************
// Band selection: 0 - Disabled, 1 - Enabled
// *****************************************************************************
// EU863-870 band support is ENABLED
#define EU_BAND     (1)
// US902-928 band support is ENABLED
#define NA_BAND     (1)
// AU915-928 band support is ENABLED
#define AU_BAND     (1)
// AS923 band support is ENABLED
#define AS_BAND     (1)
// AS923-1 band support is ENABLED
#define JPN_BAND    (1)
// KR920-923 band support is ENABLED
#define KR_BAND     (1)
// IN865-867 band support is ENABLED
#define IND_BAND    (1)
// *****************************************************************************
// Check if at least 1 region is enabled
// *****************************************************************************
#if (!(NA_BAND == 1)  && !(AS_BAND == 1) && !(AU_BAND == 1) && !(EU_BAND == 1) \
    && !(IND_BAND == 1) && !(JPN_BAND == 1) && !(KR_BAND == 1) )
#error "Error: Atleast one regional band should be enabled."
#endif
// *****************************************************************************
// Configurations for EU863-870 region
// *****************************************************************************
#define MAC_DEF_TX_POWER_EU             (1)
#define MAC_DEF_TX_CURRENT_DATARATE_EU  (DR0)
#define MAC_DATARATE_MIN_EU             (DR7)
#define MAC_DATARATE_MAX_EU             (DR0)
// Features supported
#define FEATURES_SUPPORTED_EU           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(DUTY_CYCLE_SUPPORT))
// *****************************************************************************
// *****************************************************************************
// Configurations for US902-928 region
// *****************************************************************************
#define MAC_DEF_TX_POWER_NA             (7)
#define MAC_DEF_TX_CURRENT_DATARATE_NA  (DR2)
#define MAC_DATARATE_MIN_NA             (DR4)
#define MAC_DATARATE_MAX_NA             (DR0)
// Features supported
#define FEATURES_SUPPORTED_NA           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(PA_SUPPORT)|(FHSS_SUPPORT))
// Sub-bands enabled
#define NA_SUBBAND_1_STATUS             (ENABLED)
#define NA_SUBBAND_2_STATUS             (ENABLED)
#define NA_SUBBAND_3_STATUS             (ENABLED)
#define NA_SUBBAND_4_STATUS             (ENABLED)
#define NA_SUBBAND_5_STATUS             (ENABLED)
#define NA_SUBBAND_6_STATUS             (ENABLED)
#define NA_SUBBAND_7_STATUS             (ENABLED)
#define NA_SUBBAND_8_STATUS             (ENABLED)
// *****************************************************************************
// *****************************************************************************
// Configurations for AU915-928 region
// *****************************************************************************
#define MAC_DEF_TX_POWER_AU             (7)
#define MAC_DEF_TX_CURRENT_DATARATE_AU  (DR0)
#define MAC_DATARATE_MIN_AU             (DR6)
#define MAC_DATARATE_MAX_AU             (DR0)
// Features supported
#define FEATURES_SUPPORTED_AU           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(PA_SUPPORT)|(FHSS_SUPPORT))
// Sub-bands enabled
#define AU_SUBBAND_1_STATUS             (ENABLED)
#define AU_SUBBAND_2_STATUS             (ENABLED)
#define AU_SUBBAND_3_STATUS             (ENABLED)
#define AU_SUBBAND_4_STATUS             (ENABLED)
#define AU_SUBBAND_5_STATUS             (ENABLED)
#define AU_SUBBAND_6_STATUS             (ENABLED)
#define AU_SUBBAND_7_STATUS             (ENABLED)
#define AU_SUBBAND_8_STATUS             (ENABLED)
// *****************************************************************************
// *****************************************************************************
// Configurations for AS923 region
// *****************************************************************************
#define MAC_DEF_TX_POWER_AS             (1)
#define MAC_DEF_TX_CURRENT_DATARATE_AS  (DR3)
#define MAC_DATARATE_MIN_AS             (DR7)
#define MAC_DATARATE_MAX_AS             (DR0)
// Features supported
#define FEATURES_SUPPORTED_AS           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(PA_SUPPORT)|(DUTY_CYCLE_SUPPORT))
// *****************************************************************************
// *****************************************************************************
// Configurations for AS923-1 (Japan) region
// *****************************************************************************
#define MAC_DEF_TX_POWER_JP             (1)
#define MAC_DEF_TX_CURRENT_DATARATE_JP  (DR3)
#define MAC_DATARATE_MIN_JP             (DR7)
#define MAC_DATARATE_MAX_JP             (DR0)
// Features supported
#define FEATURES_SUPPORTED_JP           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(PA_SUPPORT)|(DUTY_CYCLE_SUPPORT)|(LBT_SUPPORT))
#define LBT_RSSI_SAMPLES_COUNT_JP       (5)
// *****************************************************************************
// *****************************************************************************
// Configurations for KR920-923 region
// *****************************************************************************
#define MAC_DEF_TX_POWER_KR             (1)
#define MAC_DEF_TX_CURRENT_DATARATE_KR  (DR3)
#define MAC_DATARATE_MIN_KR             (DR5)
#define MAC_DATARATE_MAX_KR             (DR0)
// Features supported
#define FEATURES_SUPPORTED_KR           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(PA_SUPPORT)|(LBT_SUPPORT))
#define LBT_RSSI_SAMPLES_COUNT_KR       (10)
// *****************************************************************************
// *****************************************************************************
// Configurations for IN865-867 region
// *****************************************************************************
#define MAC_DEF_TX_POWER_IN             (1)
#define MAC_DEF_TX_CURRENT_DATARATE_IN  (DR0)
#define MAC_DATARATE_MIN_IN             (DR7)
#define MAC_DATARATE_MAX_IN             (DR0)
// Features supported
#define FEATURES_SUPPORTED_IN           ((0x00)|(JOIN_BACKOFF_SUPPORT)|(PA_SUPPORT))
// *****************************************************************************

// *****************************************************************************
// RNA feature is disabled by default to enable scanning all channels in
// US902-928 and AU915-928 regions
// *****************************************************************************
#define RANDOM_NW_ACQ                   (1)
// *****************************************************************************

// *****************************************************************************
// Number of scan retries for channels during LBT procedure
// *****************************************************************************
#define LBT_MAX_RETRY_CHANNELS          (2)
// *****************************************************************************
//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* CONF_REGPARAMS_H */
/*******************************************************************************
 End of File
*/
