![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# MLS (Confidential) Release Notes


## v2.0.0-rc.5

#### New Features

- LORA_DEV-2054: Add secure element support
- LORA_DEV-2011: Add LORAWAN_VERSION attribute LORAWAN_GetAttr() function
- LORA_DEV-2012: Add REGPARAMS_VERSION attribute in LORAREG_GetAttr()


#### Improvements

- LORA_DEV-2044: Enable Join with LoRaWAN 1.0.2 as well as LoRaWAN 1.0.4 NS
- LORA_DEV-2050: Add checkbox for automatic settings or manual settings
- LORA_DEV-2052: Add checkbox for automatic settings or manual settings
- LORA_DEV-2055: Add MHC configuration to provision the device
- LORA_DEV-2059: Add LoRaWAN Certification improvements

#### Bug Fixes

- LORA_DEV-2053: Set DR1 as default value for EU
- LORA_DEV-2057: Fix build failure of multiband selection test case
- LORA_DEV-2065: Fix non-expiry of software timers in case of repeating continuous run
- LORA_DEV-2066: Fix wakeup procedure of MCU to receive interrupts from SX1276 radio
- LORA_DEV-2066: Fix the immediate system reset happening when backup sleep is triggered
- LORA_DEV-2066: Fix name conflict of module ID in lorawan_h3 and lorawan_h3_sources
- LORA_DEV-2092: Fix build error in MLS projects if ENABLE_PDS=0
- LORA_DEV-2093: Fix build error in MLS projects if CONF_PMM_ENABLE is undefined


## v2.0.0-rc.4

#### New Features

#### Improvements

#### Bug Fixes

- LORA_DEV-2060: Fixes for failure in demo application build


## v2.0.0-rc.3

#### New Features

#### Improvements

- LORA_DEV-2039: Replace SW AES with WolfCrypt HW AES for SAMR34_35 platforms

#### Bug Fixes
