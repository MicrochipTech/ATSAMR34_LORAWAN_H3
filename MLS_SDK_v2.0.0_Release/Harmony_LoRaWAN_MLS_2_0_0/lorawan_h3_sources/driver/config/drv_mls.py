#-------------------------------------------------------------------------------
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MLS CONFIGURATIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COMPONENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#-------------------------------------------------------------------------------
def instantiateComponent(MLS_SRC):
    print("MLS (Confidential) Driver component")
    configName = Variables.get("__CONFIGURATION_NAME")
    print configName
    # === Activate required components automatically
    requiredComponents = [
        "eic",
        "nvmctrl",
        "pm",
        "sercom4",
        "HarmonyCore",
        "lib_wolfcrypt"
    ]

    res = Database.activateComponents(requiredComponents)
    
    # === EIC settings
    mlsEic = Database.getComponentByID("eic")
    mlsEicInts = [0, 1, 8, 10, 11, 12]
    mlsEic.setSymbolValue("EIC_CLKSEL", 1)
    for mlsEicInt in mlsEicInts:
        mlsEic.setSymbolValue("EIC_CHAN_%d" %mlsEicInt, True)
        mlsEic.setSymbolValue("EIC_INT_%d" %mlsEicInt, True)
        mlsEic.setSymbolValue("EIC_EXTINTEO_%d" %mlsEicInt, False)
        mlsEic.setSymbolValue("EIC_ASYNCH_%d" %mlsEicInt, 0)
        mlsEic.setSymbolValue("EIC_CONFIG_SENSE_%d" %mlsEicInt, 1)
        mlsEic.setSymbolValue("EIC_CONFIG_FILTEN_%d" %mlsEicInt, False)

    # === Interfaces
    mlsConfigTypes = ["Auto", "Manual"]
    global mlsComboConfType
    mlsComboConfType = MLS_SRC.createComboSymbol("MLSSRC_COMBO_CONFTYPE", None, mlsConfigTypes)
    mlsComboConfType.setLabel("Configuration")
    mlsComboConfType.setVisible(True)
    mlsComboConfType.setDefaultValue(mlsConfigTypes[0])
    mlsComboConfType.setDescription("Select the configuration type of MLS")
    
    global mlsCommentAutoConfMessage
    mlsCommentAutoConfMessage = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_AUTOCONFMESSAGE", mlsComboConfType)
    mlsCommentAutoConfMessage.setVisible(True)
    mlsCommentAutoConfMessage.setLabel("*** All user configuration will be overriden with default values ***")
    mlsCommentAutoConfMessage.setDependencies(mlsCommentAutoConfMessageDepend, ["MLSSRC_COMBO_CONFTYPE"])
    
    global mlsMenuManualConf
    mlsMenuManualConf = MLS_SRC.createMenuSymbol("MLSSRC_MENU_MANUALCONF", None)
    mlsMenuManualConf.setLabel("Manual Configuration")
    mlsMenuManualConf.setVisible(False)
    mlsMenuManualConf.setDependencies(mlsMenuManualConfDepend, ["MLSSRC_COMBO_CONFTYPE"])
    
    # global mlsBooleanSalCryptoDevEnabled
    # mlsBooleanSalCryptoDevEnabled = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_SALCRYPTODEVENABLED", None)
    # mlsBooleanSalCryptoDevEnabled.setLabel("Use Secure Element")
    # mlsBooleanSalCryptoDevEnabled.setVisible(True)
    # mlsBooleanSalCryptoDevEnabled.setDefaultValue(False)
    # mlsBooleanSalCryptoDevEnabled.setReadOnly(False)
    # mlsBooleanSalCryptoDevEnabled.setDescription("If selected, secure element will be used for cryptography and reading activation parameters")
    
    # === MAC menu
    # execfile(Module.getPath() + "/driver/config/mhc_ui_mac_config.py")
    # === Radio menu
    execfile(Module.getPath() + "/driver/config/mhc_ui_radio_config.py")
    # === RP menu
    execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_config.py")
    # === SwTimer menu
    execfile(Module.getPath() + "/driver/config/mhc_ui_swtimer_config.py")
    # === PMM menu
    execfile(Module.getPath() + "/driver/config/mhc_ui_pmm_config.py")
    # === APP menu
    execfile(Module.getPath() + "/driver/config/mhc_ui_app_config.py")

    # === MAC Conditions
    # checkMlsBooleanEnableClassC = (mlsBooleanEnableClassC.getValue() == True)
    # checkMlsBooleanEnablePds = (mlsBooleanEnablePds.getValue() == True)
    # === Radio conditions
    checkMlsBooleanRfSwitchEnable = (mlsBooleanRfSwitchEnable.getValue() == True)
    checkMlsComboRadioClockOscXtal = (mlsComboRadioClockOsc.getValue() == "XTAL")
    checkMlsComboRadioClockOscTcxo = (mlsComboRadioClockOsc.getValue() == "TCXO")
    # === RegParams band selection conditions
    print("AUTOMATICALLY CONFIGURED" if (mlsComboConfType.getValue() == "Auto") else "MANUALLY CONFIGURED")
    checkMlsBooleanEU = (mlsBooleanEU.getValue() == True)
    checkMlsBooleanUS = (mlsBooleanUS.getValue() == True)
    checkMlsBooleanAU = (mlsBooleanAU.getValue() == True)
    checkMlsBooleanAS = (mlsBooleanAS.getValue() == True)
    checkMlsBooleanJP = (mlsBooleanJP.getValue() == True)
    checkMlsBooleanKR = (mlsBooleanKR.getValue() == True)
    checkMlsBooleanIN = (mlsBooleanIN.getValue() == True)
    # === Random NW Acquisition
    checkMlsBooleanEnableRNA = (checkMlsBooleanUS or checkMlsBooleanAU) and (mlsBooleanEnableRNA.getValue() == True)
    # === EU
    checkMlsBooleanEUDutyCycle = checkMlsBooleanEU and (mlsBooleanEUDutyCycle.getValue() == True)
    checkMlsBooleanEUPA = checkMlsBooleanEU and (mlsBooleanEUPA.getValue() == True)
    checkMlsBooleanEUJoinBackOff = checkMlsBooleanEU and (mlsBooleanEUJoinBackOff.getValue() == True)
    # === US
    checkMlsBooleanUSFHSS = checkMlsBooleanUS and (mlsBooleanUSFHSS.getValue() == True)
    checkMlsBooleanUSPA = checkMlsBooleanUS and (mlsBooleanUSPA.getValue() == True)
    checkMlsBooleanUSJoinBackoff = checkMlsBooleanUS and (mlsBooleanUSJoinBackOff.getValue() == True)
    # === AU
    checkMlsBooleanAUFHSS = checkMlsBooleanAU and (mlsBooleanAUFHSS.getValue() == True)
    checkMlsBooleanAUPA = checkMlsBooleanAU and (mlsBooleanAUPA.getValue() == True)
    checkMlsBooleanAUJoinBackoff = checkMlsBooleanAU and (mlsBooleanAUJoinBackOff.getValue() == True)
    # === AS
    checkMlsBooleanASDutyCycle = checkMlsBooleanAS and (mlsBooleanASDutyCycle.getValue() == True)
    checkMlsBooleanASPA = checkMlsBooleanAS and (mlsBooleanASPA.getValue() == True)
    checkMlsBooleanASJoinBackOff = checkMlsBooleanAS and (mlsBooleanASJoinBackOff.getValue() == True)
    # === JP
    checkMlsBooleanJPDutyCycle = checkMlsBooleanJP and (mlsBooleanJPDutyCycle.getValue() == True)
    checkMlsBooleanJPPA = checkMlsBooleanJP and (mlsBooleanJPPA.getValue() == True)
    checkMlsBooleanJPJoinBackOff = checkMlsBooleanJP and (mlsBooleanJPJoinBackOff.getValue() == True)
    checkMlsBooleanJPLBT = checkMlsBooleanJP and (mlsBooleanJPLBT.getValue() == True)
    # === KR
    checkMlsBooleanKRPA = checkMlsBooleanKR and (mlsBooleanKRPA.getValue() == True)
    checkMlsBooleanKRJoinBackOff = checkMlsBooleanKR and (mlsBooleanKRJoinBackOff.getValue() == True)
    checkMlsBooleanKRLBT = checkMlsBooleanKR and (mlsBooleanKRLBT.getValue() == True)
    # === IN
    checkMlsBooleanINPA = checkMlsBooleanIN and (mlsBooleanINPA.getValue() == True)
    checkMlsBooleanINJoinBackOff = checkMlsBooleanIN and (mlsBooleanINJoinBackOff.getValue() == True)
    # === Sleep (PMM) conditions
    checkMlsBooleanEnableSleep = (mlsBooleanEnableSleep.getValue() == True)

    # === File inclusion
    mlsCondAlways = [True, None, []]
    # mlsCondEnableClassC = [checkMlsBooleanEnableClassC, mlsSetEnableClassC, ["MLSSRC_BOOLEAN_ENABLECLASSC"]]
    # mlsCondEnablePds = [checkMlsBooleanEnablePds, mlsSetEnablePds, ["MLSSRC_BOOLEAN_ENABLEPDS"]]
    # mlsCondEU = [checkMlsBooleanEU, mlsSetEnableEU, ["MLSSRC_BOOLEAN_EU"]]
    # mlsCondUS = [checkMlsBooleanUS, mlsSetEnableUS, ["MLSSRC_BOOLEAN_US"]]
    # mlsCondAU = [checkMlsBooleanAU, mlsSetEnableAU, ["MLSSRC_BOOLEAN_AU"]]
    # mlsCondAS = [checkMlsBooleanAS, mlsSetEnableAS, ["MLSSRC_BOOLEAN_AS"]]
    # mlsCondJP = [checkMlsBooleanJP, mlsSetEnableJP, ["MLSSRC_BOOLEAN_JP"]]
    # mlsCondKR = [checkMlsBooleanKR, mlsSetEnableKR, ["MLSSRC_BOOLEAN_KR"]]
    # mlsCondIN = [checkMlsBooleanIN, mlsSetEnableIN, ["MLSSRC_BOOLEAN_IN"]]
    # mlsCondEnableSleep = [checkMlsBooleanEnableSleep, mlsSetEnableSleep, ["MLSSRC_BOOLEAN_ENABLESLEEP"]]

    # === Header Files
    incMAC = [
        ["mac/lorawan.h", mlsCondAlways],
        ["private/mac/lorawan_defs.h", mlsCondAlways],
        ["private/mac/lorawan_mcast.h", mlsCondAlways],
        ["private/mac/lorawan_pds.h", mlsCondAlways],
        ["private/mac/lorawan_private.h", mlsCondAlways],
        ["private/mac/lorawan_radio.h", mlsCondAlways],
        ["private/mac/lorawan_task_handler.h", mlsCondAlways]
    ]
    incTAL = [
        ["tal/radio_interface.h", mlsCondAlways],
        ["tal/radio_get_set.h", mlsCondAlways],
        ["tal/radio_task_manager.h", mlsCondAlways],
        ["tal/radio_transaction.h", mlsCondAlways],
        ["tal/radio_lbt.h", mlsCondAlways],
        ["tal/sx1276/radio_driver_SX1276.h", mlsCondAlways],
        ["tal/sx1276/radio_registers_SX1276.h", mlsCondAlways]
    ]
    incSAL = [
        ["sal/sal.h", mlsCondAlways]
    ]
    incSYSTEM = [
        ["sys/system_assert.h", mlsCondAlways],
        ["sys/system_init.h", mlsCondAlways],
        ["sys/system_task_manager.h", mlsCondAlways]
    ]
    incSTACK = [
        ["common/stack_common.h", mlsCondAlways],
        ["common/mls.h", mlsCondAlways]
    ]
    incPMM = [
        ["pmm/pmm.h", mlsCondAlways]
    ]
    incHAL = [
        ["hal/radio_driver_hal.h", mlsCondAlways],
        ["hal/sleep.h", mlsCondAlways],
        ["hal/sleep_timer.h", mlsCondAlways],
        ["hal/sys.h", mlsCondAlways],
        ["hal/atomic.h", mlsCondAlways]
    ]
    incPDS = [
        ["services/pds/pds_interface.h", mlsCondAlways],
        ["services/pds/pds_wl.h", mlsCondAlways],
        ["services/pds/pds_nvm.h", mlsCondAlways],
        ["services/pds/pds_task_handler.h", mlsCondAlways],
        ["services/pds/pds_common.h", mlsCondAlways]
    ]
    incSWTIMER = [
        ["services/sw_timer/sw_timer.h", mlsCondAlways]
    ]
    incAES = [
        ["services/aes/aes_engine.h", mlsCondAlways],
        ["services/aes/aes_def.h", mlsCondAlways]
    ]
    incREGPARAMS = [
        ["regparams/lorawan_reg_params.h", mlsCondAlways],
        ["regparams/multiband/lorawan_multiband.h", mlsCondAlways]
    ]
    incCONFIG = [
        ["module_config/conf_stack.h", mlsCondAlways]
    ]

    # === Import the header files
    for incFileEntry in incAES:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incSTACK:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incHAL:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incMAC:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incPDS:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incPMM:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incREGPARAMS:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incSAL:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incSWTIMER:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incSYSTEM:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incTAL:
        importIncFile(MLS_SRC, configName, incFileEntry)
    for incFileEntry in incCONFIG:
        importIncFile(MLS_SRC, configName, incFileEntry)

    # === Source files
    srcMAC = [
        ["private/mac/lorawan.c", mlsCondAlways],
        ["private/mac/lorawan_classc.c", mlsCondAlways],
        ["private/mac/lorawan_mcast.c", mlsCondAlways],
        ["private/mac/lorawan_pds.c", mlsCondAlways],
        ["private/mac/lorawan_task_handler.c", mlsCondAlways]
    ]
    srcTAL = [
        ["tal/sx1276/radio_driver_sx1276.c", mlsCondAlways],
        ["private/tal/radio_get_set.c", mlsCondAlways],
        ["private/tal/radio_task_manager.c", mlsCondAlways],
        ["private/tal/radio_transaction.c", mlsCondAlways],
        ["private/tal/radio_lbt.c", mlsCondAlways],
        ["private/tal/radio_interface.c", mlsCondAlways],
    ]
    srcSYSTEM = [
        ["sys/system_assert.c", mlsCondAlways],
        ["sys/system_init.c", mlsCondAlways],
        ["sys/system_task_manager.c", mlsCondAlways]
    ]
    srcSWTIMER = [
        ["services/sw_timer/sw_timer.c", mlsCondAlways]
    ]
    srcSAL = [
        ["sal/sal.c", mlsCondAlways]
    ]
    srcPDS = [
        ["services/pds/pds_wl.c", mlsCondAlways],
        ["services/pds/pds_nvm.c", mlsCondAlways],
        ["services/pds/pds_interface.c", mlsCondAlways],
        ["services/pds/pds_task_handler.c", mlsCondAlways]
    ]
    srcPMM = [
        ["pmm/pmm.c", mlsCondAlways]
    ]
    srcAES = [
        ["services/aes/hw_aes_wc/aes_engine.c", mlsCondAlways]
    ]
    srcHAL = [
        ["hal/radio_driver_hal.c", mlsCondAlways],
        ["hal/sys.c", mlsCondAlways],
        ["hal/sleep.c", mlsCondAlways],
        ["hal/sleep_timer.c", mlsCondAlways]
    ]
    srcREGPARAMS = [
        ["regparams/multiband/lorawan_multiband.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_eu.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_na.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_au.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_as.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_kr.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_jp.c", mlsCondAlways],
        ["regparams/multiband/lorawan_mband_in.c", mlsCondAlways]
    ]
    # === Import the source files
    for srcFileEntry in srcAES:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcHAL:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcPDS:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcPMM:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcREGPARAMS:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcSAL:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcSWTIMER:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcSYSTEM:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcTAL:
        importSrcFile(MLS_SRC, configName, srcFileEntry)
    for srcFileEntry in srcMAC:
        importSrcFile(MLS_SRC, configName, srcFileEntry)

    # === Include path setting
    incPathsMLS = [
        ["/MLS/", mlsCondAlways],
        ["/MLS/common/", mlsCondAlways],
        ["/MLS/hal/", mlsCondAlways],
        ["/MLS/mac/", mlsCondAlways],
        ["/MLS/pmm/", mlsCondAlways],
        ["/MLS/regparams/", mlsCondAlways],
        ["/MLS/regparams/multiband/", mlsCondAlways],
        ["/MLS/sal/", mlsCondAlways],
        ["/MLS/services/aes/", mlsCondAlways],
        ["/MLS/services/pds/", mlsCondAlways],
        ["/MLS/services/sw_timer/", mlsCondAlways],
        ["/MLS/sys/", mlsCondAlways],
        ["/MLS/tal/", mlsCondAlways],
        ["/MLS/module_config/", mlsCondAlways],
        ["/MLS/tal/sx1276/", mlsCondAlways],
        ["/MLS/private/tal/", mlsCondAlways],
        ["/MLS/private/mac/", mlsCondAlways]
    ]
    for incPathEntry in incPathsMLS:
        setIncPath(MLS_SRC, configName, incPathEntry)

    # === File templates processing
    mlsDefinitionsH = MLS_SRC.createFileSymbol('MLS_DEFINITIONS_H', None)
    mlsDefinitionsH.setType('STRING')
    mlsDefinitionsH.setOutputName('core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES')
    mlsDefinitionsH.setSourcePath('driver/templates/system/system_definitions.h.ftl')
    mlsDefinitionsH.setMarkup(True)
    
    mlsInitializationC = MLS_SRC.createFileSymbol('MLS_INITIALIZATION_C', None)
    mlsInitializationC.setType('STRING')
    mlsInitializationC.setOutputName('core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS')
    mlsInitializationC.setSourcePath('driver/templates/system/system_initialize.c.ftl')
    mlsInitializationC.setMarkup(True)

    mlsTasksC = MLS_SRC.createFileSymbol('MLS_TASKS_C', None)
    mlsTasksC.setType('STRING')
    mlsTasksC.setOutputName('core.LIST_SYSTEM_TASKS_C_CALL_LIB_TASKS')
    mlsTasksC.setSourcePath('driver/templates/system/system_tasks.c.ftl')
    mlsTasksC.setMarkup(True)

    # mlsConfStack = MLS_SRC.createFileSymbol("MLSSRC_CONF_STACK", None)
    # mlsConfStack.setSourcePath("/driver/templates/conf_stack.h.ftl")
    # mlsConfStack.setOutputName("conf_stack.h")
    # mlsConfStack.setDestPath("/MLS/module_config/")
    # mlsConfStack.setProjectPath("config/" + configName + "/MLS/module_config/")
    # mlsConfStack.setType("HEADER")
    # mlsConfStack.setOverwrite(True)
    # mlsConfStack.setMarkup(True)

    mlsConfRadio = MLS_SRC.createFileSymbol("MLSSRC_CONF_RADIO", None)
    mlsConfRadio.setSourcePath("/driver/templates/conf_radio.h.ftl")
    mlsConfRadio.setOutputName("conf_radio.h")
    mlsConfRadio.setDestPath("/MLS/module_config/")
    mlsConfRadio.setProjectPath("config/" + configName + "/MLS/module_config/")
    mlsConfRadio.setType("HEADER")
    mlsConfRadio.setOverwrite(True)
    mlsConfRadio.setMarkup(True)

    mlsConfRegParams = MLS_SRC.createFileSymbol("MLSSRC_CONF_REGPARAMS", None)
    mlsConfRegParams.setSourcePath("/driver/templates/conf_regparams.h.ftl")
    mlsConfRegParams.setOutputName("conf_regparams.h")
    mlsConfRegParams.setDestPath("/MLS/module_config/")
    mlsConfRegParams.setProjectPath("config/" + configName + "/MLS/module_config/")
    mlsConfRegParams.setType("HEADER")
    mlsConfRegParams.setOverwrite(True)
    mlsConfRegParams.setMarkup(True)

    mlsConfSal = MLS_SRC.createFileSymbol("MLSSRC_CONF_SAL", None)
    mlsConfSal.setSourcePath("/driver/templates/conf_sal.h.ftl")
    mlsConfSal.setOutputName("conf_sal.h")
    mlsConfSal.setDestPath("/MLS/module_config/")
    mlsConfSal.setProjectPath("config/" + configName + "/MLS/module_config/")
    mlsConfSal.setType("HEADER")
    mlsConfSal.setOverwrite(True)
    mlsConfSal.setMarkup(True)

    mlsConfApp = MLS_SRC.createFileSymbol("MLSSRC_CONF_APP", None)
    mlsConfApp.setSourcePath("/driver/templates/conf_app.h.ftl")
    mlsConfApp.setOutputName("core.LIST_SYSTEM_CONFIG_H_APPLICATION_CONFIGURATION")
    mlsConfApp.setMarkup(True)
    mlsConfApp.setType("STRING")

    mlsConfPmm = MLS_SRC.createFileSymbol("MLSSRC_CONF_PMM", None)
    mlsConfPmm.setSourcePath("/driver/templates/conf_pmm.h.ftl")
    mlsConfPmm.setOutputName("conf_pmm.h")
    mlsConfPmm.setDestPath("/MLS/module_config/")
    mlsConfPmm.setProjectPath("config/" + configName + "/MLS/module_config/")
    mlsConfPmm.setType("HEADER")
    mlsConfPmm.setOverwrite(True)
    mlsConfPmm.setMarkup(True)

    mlsConfSwtimer = MLS_SRC.createFileSymbol("MLSSRC_CONF_SWTIMER", None)
    mlsConfSwtimer.setSourcePath("/driver/templates/conf_swtimer.h.ftl")
    mlsConfSwtimer.setOutputName("conf_sw_timer.h")
    mlsConfSwtimer.setDestPath("/MLS/module_config/")
    mlsConfSwtimer.setProjectPath("config/" + configName + "/MLS/module_config/")
    mlsConfSwtimer.setType("HEADER")
    mlsConfSwtimer.setOverwrite(True)
    mlsConfSwtimer.setMarkup(True)

    mlsAppHeader = MLS_SRC.createFileSymbol("MLSSRC_APP_HEADER", None)
    mlsAppHeader.setSourcePath("/driver/templates/mls_app.h.ftl")
    mlsAppHeader.setOutputName("mls_app.h")
    mlsAppHeader.setType("HEADER")
    mlsAppHeader.setOverwrite(True)
    mlsAppHeader.setMarkup(True)

    mlsAppSource = MLS_SRC.createFileSymbol("MLSSRC_APP_SOURCE", None)
    mlsAppSource.setSourcePath("/driver/templates/mls_app.c.ftl")
    mlsAppSource.setOutputName("mls_app.c")
    mlsAppSource.setType("SOURCE")
    mlsAppSource.setOverwrite(True)
    mlsAppSource.setMarkup(True)

    # === Compiler macros
    preprocessorCompiler = MLS_SRC.createSettingSymbol("MLSSRC_XC32_PREPRECESSOR", None)
    preprocessorCompiler.setValue("ENABLE_PDS=1;")
    preprocessorCompiler.setCategory("C32")
    preprocessorCompiler.setKey("preprocessor-macros")
    preprocessorCompiler.setAppend(True, ";")
    preprocessorCompiler.setEnabled(True)

    # === Setting the required heap size for the application
    Database.sendMessage("core", "HEAP_SIZE", {"heap_size":1024})

    # === Treat warnings as errors
    warningAsError = MLS_SRC.createSettingSymbol("MLSSRC_GCC_WARN_ERROR", None)
    warningAsError.setValue("false")
    warningAsError.setCategory("C32")
    warningAsError.setKey("make-warnings-into-errors")

    # === Set optimization level
    optlevel = MLS_SRC.createSettingSymbol("PET_LEVEL", None)
    optlevel.setValue("-Os")
    optlevel.setCategory("C32")
    optlevel.setKey("optimization-level")
#end instantiateComponent

def finalizeComponent(mlsComponent):
    # === Remove FreeRTOS
    activeComponents = Database.getActiveComponentIDs()
    for i in range(0, len(activeComponents)):
        if (activeComponents[i] == "FreeRTOS"):
            Database.deactivateComponents(["FreeRTOS"])
    # === Auto-connect dependencies
    r1 = Database.connectDependencies([["MLS_SRC", "mlssrc_radio_sercom4spi_dependency", "sercom4", "SERCOM4_SPI"]])
    r2 = Database.connectDependencies([["MLS_SRC", "mlssrc_swtimer_tmr_dependency", "tc0", "TC0_TMR"]])
    r3 = Database.connectDependencies([["MLS_SRC", "mlssrc_sleeptimer_rtc_dependency", "rtc", "RTC_TMR"]])
    # === Harmony Core OSAL settings
    Database.sendMessage("HarmonyCore", "ENABLE_OSAL", {"isEnabled":True})
    Database.sendMessage("HarmonyCore", "ENABLE_SYS_RESET", {"isEnabled":True})
    Database.sendMessage("HarmonyCore", "ENABLE_SYS_INT", {"isEnabled":True})
    Database.sendMessage("HarmonyCore", "ENABLE_APP_FILE", {"isEnabled":True})
    #
    coreComp = Database.getComponentByID("core")
    coreComp.setSymbolValue("systickEnable", True)
    #
    cryptoComp = Database.getComponentByID("lib_wolfcrypt")
    cryptoComp.setSymbolValue("wolfcrypt_hw", True)
    cryptoComp.setSymbolValue("wolfcrypt_aes_hw", True)
    cryptoComp.setSymbolValue("wolfcrypt_aes_128", True)
    cryptoComp.setSymbolValue("wolfcrypt_aes_ecb", True)
    cryptoComp.setSymbolValue("wolfcrypt_aes_ecb_hw", True)
    cryptoComp.setSymbolValue("wolfcrypt_aes_cmac", True)
#end finalizeComponent

def importIncFile(component, configName, incFileEntry, firmwarePath = None):
    incFilePath  = incFileEntry[0]
    isEnabled    = incFileEntry[1][0]
    callback     = incFileEntry[1][1]
    dependencies = incFileEntry[1][2]

    incFilePathTup = incFilePath.rsplit("/", 1)

    if len(incFilePathTup) == 1:
        secName = ""
        incFile = incFilePathTup[0]
    else :
        secName = incFilePathTup[0]
        incFile = incFilePathTup[1]

    symName = incFile.replace(".", "_").upper()
    secSName = secName + "/"
    secDName = secSName
    print("******", secDName)

    incFileSym = component.createFileSymbol(symName, None)
    incFileSym.setSourcePath("driver/stack/" + secSName + "/" + incFile)
    incFileSym.setOutputName(incFile)
    incFileSym.setDestPath("MLS/" + secDName + "")
    incFileSym.setProjectPath("config/" + configName + "/MLS/"+ secDName + "")
    incFileSym.setType("HEADER")
    incFileSym.setOverwrite(True)
    incFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        incFileSym.setDependencies(callback, dependencies)
#end importIncFile

def importSrcFile(component, configName, srcFileEntry, firmwarePath = None):
    srcFilePath  = srcFileEntry[0]
    isEnabled    = srcFileEntry[1][0]
    callback     = srcFileEntry[1][1]
    dependencies = srcFileEntry[1][2]

    srcFilePathTup = srcFilePath.rsplit("/", 1)

    if len(srcFilePathTup) == 1:
        secName = ""
        srcFile = srcFilePathTup[0]
    else:
        secName = srcFilePathTup[0]
        srcFile = srcFilePathTup[1]

    srcFilePrefix   = ""
    symName = srcFile.replace(".", "_").upper()
    secSName = secName + "/"
    secDName = secSName
    print("******", secDName)

    srcFileSym = component.createFileSymbol(symName, None)
    srcFileSym.setSourcePath("driver/stack/" + secSName + srcFile)
    srcFileSym.setOutputName(srcFile.rsplit("/", 1)[-1])
    srcFileSym.setDestPath("MLS/" + secDName + "")
    srcFileSym.setProjectPath("config/" + configName + "/MLS/"+ secDName + "")
    srcFileSym.setType("SOURCE")
    srcFileSym.setEnabled(isEnabled)

    if callback and dependencies:
        srcFileSym.setDependencies(callback, dependencies)
#end importSrcFile

def setIncPath(component, configName, incPathEntry):
    incPath      = incPathEntry[0]
    isEnabled    = incPathEntry[1][0]
    callback     = incPathEntry[1][1]
    dependencies = incPathEntry[1][2]
    incPathSym = component.createSettingSymbol("MLSSRC_INC_PATH" + incPath.replace(".", "_").replace("/", "_").upper(), None)
    incPathSym.setValue("../src/config/" + configName + incPath + ";")
    incPathSym.setCategory("C32")
    incPathSym.setKey("extra-include-directories")
    incPathSym.setAppend(True, ";")
    incPathSym.setEnabled(isEnabled)
    incPathSym.setDependencies(callback, dependencies)
#end setIncPath

# def mlsCommentEnableClassCDepend(sourceSymbol, event):
#     if event["value"] == True:
#         sourceSymbol.setLabel("*** Classes A & C are enabled ***")
#     else:
#         sourceSymbol.setLabel("*** Class A is always enabled ***")
#end mlsCommentEnableClassCDepend

# def mlsCommentEnablePdsDepend(sourceSymbol, event):
#     if event["value"] == True:
#         sourceSymbol.setVisible(False)
#     else:
#         sourceSymbol.setVisible(True)
#         sourceSymbol.setLabel("*** PDS is necessary to run many MAC related functionalities ***")
#end mlsCommentEnablePdsDepend

def mlsMenuManualConfDepend(sourceSymbol, event):
    if event["value"] == "Manual":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsMenuManualConfDepend

def mlsCommentAutoConfMessageDepend(sourceSymbol, event):
    if event["value"] == "Auto":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsCommentAutoConfMessageDepend

def mlsIntegerRadioStabilizationDelayDepend(sourceSymbol, event):
    if event["value"] == "TCXO":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsIntegerRadioStabilizationDelayDepend

def mlsMenuEUDepend(sourceSymbol, event):
    mlsMenuEU.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboEUMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboEUMaxDr.getValue()[-1])
    curDr = int(mlsComboEUDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentEUMinDr.setVisible(True)
        mlsCommentEUMinDr.setLabel("*** Please select a DR so that slowest <= default <= FASTEST ***")
    else:
        mlsCommentEUMinDr.setVisible(False)
        mlsCommentEUMaxDr.setVisible(False)
        mlsCommentEUDefUplinkDr.setVisible(False)
#end mlsComboEUMinDrDepend

def mlsComboEUMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboEUMinDr.getValue()[-1])
    curDr = int(mlsComboEUDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentEUMaxDr.setVisible(True)
        mlsCommentEUMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentEUMinDr.setVisible(False)
        mlsCommentEUMaxDr.setVisible(False)
        mlsCommentEUDefUplinkDr.setVisible(False)
#end mlsComboEUMaxDrDepend

def mlsComboEUDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboEUMinDr.getValue()[-1])
    maxDr = int(mlsComboEUMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentEUDefUplinkDr.setVisible(True)
        mlsCommentEUDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentEUMinDr.setVisible(False)
        mlsCommentEUMaxDr.setVisible(False)
        mlsCommentEUDefUplinkDr.setVisible(False)
#end mlsComboEUDefUplinkDrDepend

def mlsMenuUSDepend(sourceSymbol, event):
    mlsMenuUS.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboUSMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboUSMaxDr.getValue()[-1])
    curDr = int(mlsComboUSDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentUSMinDr.setVisible(True)
        mlsCommentUSMinDr.setLabel("*** Please select a DR so that slowest <= default <= FASTEST ***")
    else:
        mlsCommentUSMinDr.setVisible(False)
        mlsCommentUSMaxDr.setVisible(False)
        mlsCommentUSDefUplinkDr.setVisible(False)
#end mlsComboUSMinDrDepend

def mlsComboUSMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboUSMinDr.getValue()[-1])
    curDr = int(mlsComboUSDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentUSMaxDr.setVisible(True)
        mlsCommentUSMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentUSMinDr.setVisible(False)
        mlsCommentUSMaxDr.setVisible(False)
        mlsCommentUSDefUplinkDr.setVisible(False)
#end mlsComboUSMaxDrDepend

def mlsComboUSDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboUSMinDr.getValue()[-1])
    maxDr = int(mlsComboUSMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentUSDefUplinkDr.setVisible(True)
        mlsCommentUSDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentUSMinDr.setVisible(False)
        mlsCommentUSMaxDr.setVisible(False)
        mlsCommentUSDefUplinkDr.setVisible(False)
#end mlsComboUSDefUplinkDrDepend

def mlsMenuAUDepend(sourceSymbol, event):
    mlsMenuAU.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboAUMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboAUMaxDr.getValue()[-1])
    curDr = int(mlsComboAUDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentAUMinDr.setVisible(True)
        mlsCommentAUMinDr.setLabel("*** Please select a DR so that slowest <= default <= FASTEST ***")
    else:
        mlsCommentAUMinDr.setVisible(False)
        mlsCommentAUMaxDr.setVisible(False)
        mlsCommentAUDefUplinkDr.setVisible(False)
#end mlsComboAUMinDrDepend

def mlsComboAUMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboAUMinDr.getValue()[-1])
    curDr = int(mlsComboAUDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentAUMaxDr.setVisible(True)
        mlsCommentAUMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentAUMinDr.setVisible(False)
        mlsCommentAUMaxDr.setVisible(False)
        mlsCommentAUDefUplinkDr.setVisible(False)
#end mlsComboAUMaxDrDepend

def mlsComboAUDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboAUMinDr.getValue()[-1])
    maxDr = int(mlsComboAUMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentAUDefUplinkDr.setVisible(True)
        mlsCommentAUDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentAUMinDr.setVisible(False)
        mlsCommentAUMaxDr.setVisible(False)
        mlsCommentAUDefUplinkDr.setVisible(False)
#end mlsComboAUDefUplinkDrDepend

def mlsMenuASDepend(sourceSymbol, event):
    mlsMenuAS.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboASMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboASMaxDr.getValue()[-1])
    curDr = int(mlsComboASDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentASMinDr.setVisible(True)
        mlsCommentASMinDr.setLabel("*** Please select a DR so that slowest <= default <= FASTEST ***")
    else:
        mlsCommentASMinDr.setVisible(False)
        mlsCommentASMaxDr.setVisible(False)
        mlsCommentASDefUplinkDr.setVisible(False)
#end mlsComboASMinDrDepend

def mlsComboASMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboASMinDr.getValue()[-1])
    curDr = int(mlsComboASDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentASMaxDr.setVisible(True)
        mlsCommentASMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentASMinDr.setVisible(False)
        mlsCommentASMaxDr.setVisible(False)
        mlsCommentASDefUplinkDr.setVisible(False)
#end mlsComboASMaxDrDepend

def mlsComboASDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboASMinDr.getValue()[-1])
    maxDr = int(mlsComboASMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentASDefUplinkDr.setVisible(True)
        mlsCommentASDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentASMinDr.setVisible(False)
        mlsCommentASMaxDr.setVisible(False)
        mlsCommentASDefUplinkDr.setVisible(False)
#end mlsComboASDefUplinkDrDepend

def mlsMenuJPDepend(sourceSymbol, event):
    mlsMenuJP.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboJPMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboJPMaxDr.getValue()[-1])
    curDr = int(mlsComboJPDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentJPMinDr.setVisible(True)
        mlsCommentJPMinDr.setLabel("*** Please select a DR so that slowest <= default <= FJPTEST ***")
    else:
        mlsCommentJPMinDr.setVisible(False)
        mlsCommentJPMaxDr.setVisible(False)
        mlsCommentJPDefUplinkDr.setVisible(False)
#end mlsComboJPMinDrDepend

def mlsComboJPMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboJPMinDr.getValue()[-1])
    curDr = int(mlsComboJPDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentJPMaxDr.setVisible(True)
        mlsCommentJPMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentJPMinDr.setVisible(False)
        mlsCommentJPMaxDr.setVisible(False)
        mlsCommentJPDefUplinkDr.setVisible(False)
#end mlsComboJPMaxDrDepend

def mlsComboJPDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboJPMinDr.getValue()[-1])
    maxDr = int(mlsComboJPMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentJPDefUplinkDr.setVisible(True)
        mlsCommentJPDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentJPMinDr.setVisible(False)
        mlsCommentJPMaxDr.setVisible(False)
        mlsCommentJPDefUplinkDr.setVisible(False)
#end mlsComboJPDefUplinkDrDepend

def mlsMenuKRDepend(sourceSymbol, event):
    mlsMenuKR.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboKRMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboKRMaxDr.getValue()[-1])
    curDr = int(mlsComboKRDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentKRMinDr.setVisible(True)
        mlsCommentKRMinDr.setLabel("*** Please select a DR so that slowest <= default <= FKRTEST ***")
    else:
        mlsCommentKRMinDr.setVisible(False)
        mlsCommentKRMaxDr.setVisible(False)
        mlsCommentKRDefUplinkDr.setVisible(False)
#end mlsComboKRMinDrDepend

def mlsComboKRMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboKRMinDr.getValue()[-1])
    curDr = int(mlsComboKRDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentKRMaxDr.setVisible(True)
        mlsCommentKRMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentKRMinDr.setVisible(False)
        mlsCommentKRMaxDr.setVisible(False)
        mlsCommentKRDefUplinkDr.setVisible(False)
#end mlsComboKRMaxDrDepend

def mlsComboKRDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboKRMinDr.getValue()[-1])
    maxDr = int(mlsComboKRMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentKRDefUplinkDr.setVisible(True)
        mlsCommentKRDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentKRMinDr.setVisible(False)
        mlsCommentKRMaxDr.setVisible(False)
        mlsCommentKRDefUplinkDr.setVisible(False)
#end mlsComboKRDefUplinkDrDepend

def mlsMenuINDepend(sourceSymbol, event):
    mlsMenuIN.setVisible(event["value"])
#end mlsMenuEUDepend

def mlsComboINMinDrDepend(sourceSymbol, event):
    minDr = int(sourceSymbol.getValue()[-1])
    maxDr = int(mlsComboINMaxDr.getValue()[-1])
    curDr = int(mlsComboINDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentINMinDr.setVisible(True)
        mlsCommentINMinDr.setLabel("*** Please select a DR so that slowest <= default <= FINTEST ***")
    else:
        mlsCommentINMinDr.setVisible(False)
        mlsCommentINMaxDr.setVisible(False)
        mlsCommentINDefUplinkDr.setVisible(False)
#end mlsComboINMinDrDepend

def mlsComboINMaxDrDepend(sourceSymbol, event):
    maxDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboINMinDr.getValue()[-1])
    curDr = int(mlsComboINDefUplinkDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentINMaxDr.setVisible(True)
        mlsCommentINMaxDr.setLabel("*** Please select a DR so that SLOWEST <= default <= fastest ***")
    else:
        mlsCommentINMinDr.setVisible(False)
        mlsCommentINMaxDr.setVisible(False)
        mlsCommentINDefUplinkDr.setVisible(False)
#end mlsComboINMaxDrDepend

def mlsComboINDefUplinkDrDepend(sourceSymbol, event):
    curDr = int(sourceSymbol.getValue()[-1])
    minDr = int(mlsComboINMinDr.getValue()[-1])
    maxDr = int(mlsComboINMaxDr.getValue()[-1])
    invalidity = not(maxDr <= curDr <= minDr)
    if invalidity == True:
        mlsCommentINDefUplinkDr.setVisible(True)
        mlsCommentINDefUplinkDr.setLabel("*** Please select a DR so that slowest <= DEFAULT <= fastest ***")
    else:
        mlsCommentINMinDr.setVisible(False)
        mlsCommentINMaxDr.setVisible(False)
        mlsCommentINDefUplinkDr.setVisible(False)
#end mlsComboINDefUplinkDrDepend

def mlsCommentSwtimerMaxTimersDepend(sourceSymbol, event):
    totalMem = 14 * mlsIntegerSwtimerMaxTimers.getValue()
    mlsCommentSwtimerMaxTimers.setLabel("Memory occupied: %d bytes (w/o packing)" %totalMem)
#end mlsCommentSwtimerMaxTimersDepend

def mlsCommentSwtimerMaxTimestampsDepend(sourceSymbol, event):
    totalMem = 8 * mlsIntegerSwtimerMaxTimestamps.getValue()
    mlsCommentSwtimerMaxTimestamps.setLabel("Memory occupied: ~%d bytes" %totalMem)
#end mlsCommentSwtimerMaxTimestampsDepend

def mlsmlsIntegerKRLbtRssiSampleCountDepend(sourceSymbol, event):
    if event["value"] == True:
        mlsIntegerKRLbtRssiSampleCount.setVisible(True)
    else:
        mlsIntegerKRLbtRssiSampleCount.setVisible(False)
#end mlsmlsIntegerKRLbtRssiSampleCountDepend

def mlsmlsIntegerJPLbtRssiSampleCountDepend(sourceSymbol, event):
    if event["value"] == True:
        mlsIntegerJPLbtRssiSampleCount.setVisible(True)
    else:
        mlsIntegerJPLbtRssiSampleCount.setVisible(False)
#end mlsmlsIntegerJPLbtRssiSampleCountDepend

def mlsSetEnableEU(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_EU') == True)
#end mlsSetEnableEU

def mlsSetEnableUS(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_US') == True)
#end mlsSetEnableUS

def mlsSetEnableAU(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_AU') == True)
#end mlsSetEnableAU

def mlsSetEnableAS(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_AS') == True)
#end mlsSetEnableAS

def mlsSetEnableJP(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_JP') == True)
#end mlsSetEnableJP

def mlsSetEnableKR(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_KR') == True)
#end mlsSetEnableKR

def mlsSetEnableIN(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_IN') == True)
#end mlsSetEnableIN

def mlsSetEnableSleep(sourceSymbol, event):
    sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_ENABLESLEEP') == True)
#end mlsSetEnableIN

# def mlsSetEnableClassC(sourceSymbol, event):
    # sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_ENABLECLASSC') == True)
#end mlsSetEnableIN

# def mlsSetEnablePds(sourceSymbol, event):
    # sourceSymbol.setEnabled(sourceSymbol.getComponent().getSymbolValue('MLS_BOOLEAN_ENABLEPDS') == True)
#end mlsSetEnableIN

def mlsComboAppDevEuiSrcDepend(sourceSymbol, event):
    if event["value"] == "MANUAL":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsMenuAppManualProv

def mlsBooleanAppSnAsDevEuiDepend(sourceSymbol, event):
    if event["value"] == "SECURE_ELEMENT":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsMenuAppManualProv

def mlsCommentAppSrcManualInDepend(sourceSymbol, event):
    if event["value"] == "MANUAL_INPUT":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsCommentSourceManualInputDepend

def mlsCommentAppSrcEdbgDepend(sourceSymbol, event):
    if event["value"] == "SAMR34_XPRO_EDBG":
        sourceSymbol.setVisible(True)
    else:
        sourceSymbol.setVisible(False)
#end mlsCommentSourceManualInputDepend

def mlsMenuAppDepend(sourceSymbol, event):
    mlsMenuApp.setVisible(event["value"])
#end mlsCommentSourceManualInputDepend

#eof drv_mls.py