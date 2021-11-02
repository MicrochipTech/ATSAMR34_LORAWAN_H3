![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip LoRaWAN Stack Release Notes

| MLS_SDK Version | LoRaWAN Version | RegParams Version | Classes Supported | Join Modes | MLS_SDK Release Date |
|-----------------|-----------------|-------------------|-------------------|------------|----------------------|
| v2.0.0          | LW1.0.4         | RP2-1.0.1         | Class-A & Class-C | OTAA & ABP | 2021-10-21           |

## Supported Platforms

- SAMR34 Xplained PRO

## v2.0.0

- v2.0.0-rc.6 is released as v2.0.0

## v2.0.0-rc.6

#### Bug Fixes

- LORA_DEV-2109: Fix TTIv3 NS join issue with ECC
- LORA_DEV-2107: H3 code cleanup, formatting and licence update
- LORA_DEV-1877: DR 0 in Class C downlink reception is not happening in Regression based tests

## v2.0.0-rc.5

#### New Features

- LORA_DEV-2054: Add secure element support

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
