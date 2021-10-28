![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip LoRaWAN Stack Release Notes

| MLS_SDK Version | LoRaWAN Version | RegParams Version | Classes Supported | Join Modes | MLS_SDK Release Date |
|-----------------|-----------------|-------------------|-------------------|------------|----------------------|
| v2.0.0          | LW1.0.4         | RP2-1.0.1         | Class-A & Class-C | OTAA & ABP | 2021-10-21           |

## Supported Platforms

- SAMR34 Xplained PRO

## Supported applications

- LoRaWAN Enddevice Demo (with certification mode & ATECC608 support)
- RN-style Parser for SAMR34

## v2.0.0

#### Fixes & Improvements

- LORA_DEV-2054: Add secure element support
- LORA_DEV-2039: Replace SW AES with WolfCrypt HW AES for SAMR34_35 platforms
- LORA_DEV-2044: Enable Join with LoRaWAN 1.0.2 as well as LoRaWAN 1.0.4 NS
- LORA_DEV-2050: Add checkbox for automatic settings or manual settings
- LORA_DEV-2052: Add checkbox for automatic settings or manual settings
- LORA_DEV-2055: Add MHC configuration to provision the device
- LORA_DEV-2059: Add LoRaWAN Certification improvements
- LORA_DEV-1877: Fix for KR&EU_OTAA&ABP UNCNF & CNF at DR 0 in Class C downlink reception is not happening in Regression based tests
- LORA_DEV-1998: Demo sanity testcase (EU_OTAA_A) failed
- LORA_DEV-2033: Parser does not print payload bigger than 123 bytes
- LORA_DEV-2038: ADR test case failed while setting the default power and datarate
- LORA_DEV-2041: Demo RNA related test case failed
- LORA_DEV-2045: Sleep commands not working in Parser application
- LORA_DEV-2048: Standby Sleep test cases failed in Demo and Parser
- LORA_DEV-2053: Set DR1 as default value for EU
- LORA_DEV-2057: Fix build failure of multiband selection test case
- LORA_DEV-2060: Fix for Parser and Demo Build Failures
- LORA_DEV-2062: Join back off testcases in all the time slots got failed in NA,AU bands
- LORA_DEV-2063: Fix incorrect firmware version reported in v2.0.0-rc.3 release
- LORA_DEV-2065: Fix non-expiry of software timers in case of repeating continuous run
- LORA_DEV-2066: Fix wakeup procedure of MCU to receive interrupts from SX1276 radio
- LORA_DEV-2067: Fix the immediate system reset happening when backup sleep is triggered
- LORA_DEV-2092: Fix build error in MLS projects if ENABLE_PDS-0
- LORA_DEV-2093: Fix build error in MLS projects if CONF_PMM_ENABLE is undefined
- LORA_DEV-2109: H3 EDDEMO firmware DOES NOT uplink to TTIv3 NS

