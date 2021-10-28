######################  Harmony replaceme  ######################
def loadModule():
    print("Load Module: Harmony Microchip LoRaWAN Stack")
    print(Variables.get("__PROCESSOR"))
    # === Create MLS
    MLS_SRC  = Module.CreateComponent('MLS_SRC', 'LORAWAN stack', 'Wireless/Drivers', 'driver/config/drv_mls.py')
    MLS_SRC.setDisplayType('LoRaWAN EndDevice')
    MLS_SRC.addDependency('HarmonyCoreDependency', 'Core Service', 'Core Service', True, True)
    MLS_SRC.addDependency('mlssrc_radio_sercom4spi_dependency', 'SPI', 'SPI (LoRa Radio)', False, True)
    MLS_SRC.addDependency('mlssrc_swtimer_tmr_dependency', 'TMR', 'TMR (Stack Timer)', False, True)
    MLS_SRC.addDependency('mlssrc_sleeptimer_rtc_dependency', 'TMR', 'TMR (Sleep RTC)', False, True)
    MLS_SRC.addDependency('mlssrc_lib_wolfcrypt_dependency', 'LIB_WOLFCRYPT', 'Crypto', True, False)
