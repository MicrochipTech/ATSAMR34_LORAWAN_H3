# === APP Configuration
global mlsBooleanAppConfEn
mlsBooleanAppConfEn = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_APPCONFEN", None)
mlsBooleanAppConfEn.setLabel("Use app template?")
mlsBooleanAppConfEn.setVisible(True)
mlsBooleanAppConfEn.setDefaultValue(True)
mlsBooleanAppConfEn.setDescription("If selected, MHC includes a template application for LoRaWAN")

global mlsMenuApp
mlsMenuApp = MLS_SRC.createMenuSymbol("MLSSRC_MENU_APP", mlsBooleanAppConfEn)
mlsMenuApp.setLabel("Application Configuration")
mlsMenuApp.setVisible(True)
mlsMenuApp.setDependencies(mlsMenuAppDepend, ["MLSSRC_BOOLEAN_APPCONFEN"])

provSource = ["SECURE_ELEMENT", "MANUAL"]
global mlsComboAppProvSource
mlsComboAppProvSource = MLS_SRC.createComboSymbol("MLSSRC_COMBO_APPPROVSOURCE", mlsMenuApp, provSource)
mlsComboAppProvSource.setLabel("Device Provisioning")
mlsComboAppProvSource.setVisible(True)
mlsComboAppProvSource.setDefaultValue(provSource[1])
mlsComboAppProvSource.setDescription("Select the provisioning source")

devEuiSource = ["SAMR34_XPRO_EDBG", "WLR089U0_MODULE_USERPAGE", "MANUAL_INPUT"]
global mlsComboAppDevEuiSrc
mlsComboAppDevEuiSrc = MLS_SRC.createComboSymbol("MLSSRC_COMBO_APPDEVEUISRC", mlsComboAppProvSource, devEuiSource)
mlsComboAppDevEuiSrc.setLabel("DevEUI Source")
mlsComboAppDevEuiSrc.setVisible(True)
mlsComboAppDevEuiSrc.setDefaultValue(devEuiSource[0])
mlsComboAppDevEuiSrc.setDescription("Select the other provisioning source")
mlsComboAppDevEuiSrc.setDependencies(mlsComboAppDevEuiSrcDepend, ["MLSSRC_COMBO_APPPROVSOURCE"])

global mlsBooleanAppSnAsDevEui
mlsBooleanAppSnAsDevEui = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_SAL_SNASDEVEUI", mlsComboAppProvSource)
mlsBooleanAppSnAsDevEui.setLabel("Serial No. as DevEUI?")
mlsBooleanAppSnAsDevEui.setVisible(False)
mlsBooleanAppSnAsDevEui.setDefaultValue(False)
mlsBooleanAppSnAsDevEui.setDescription("If selected, ECC serial number will be used as DevEUI")
mlsBooleanAppSnAsDevEui.setDependencies(mlsBooleanAppSnAsDevEuiDepend, ["MLSSRC_COMBO_APPPROVSOURCE"])

global mlsCommentAppSrcManualIn
mlsCommentAppSrcManualIn = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_APPSRCMANUALIN", mlsComboAppDevEuiSrc)
mlsCommentAppSrcManualIn.setVisible(False)
mlsCommentAppSrcManualIn.setLabel("*** Input parameters in conf_app.h ***")
mlsCommentAppSrcManualIn.setDependencies(mlsCommentAppSrcManualInDepend, ["MLSSRC_COMBO_APPDEVEUISRC"])

global mlsCommentAppSrcEdbg
mlsCommentAppSrcEdbg = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_APPSRCEDBG", mlsComboAppDevEuiSrc)
mlsCommentAppSrcEdbg.setVisible(True)
mlsCommentAppSrcEdbg.setLabel("*** Ensure SERCOM1_I2C_MASTER is included ***")
mlsCommentAppSrcEdbg.setDependencies(mlsCommentAppSrcEdbgDepend, ["MLSSRC_COMBO_APPDEVEUISRC"])

joinTypes = ["OTAA", "ABP"]
global mlsComboAppJoinType
mlsComboAppJoinType = MLS_SRC.createComboSymbol("MLSSRC_COMBO_APPJOINTYPE", mlsMenuApp, joinTypes)
mlsComboAppJoinType.setLabel("Join type")
mlsComboAppJoinType.setVisible(True)
mlsComboAppJoinType.setDefaultValue(joinTypes[0])
mlsComboAppJoinType.setDescription("Select the join type")

joinNsVer = ["Up to (<=) Lw1.0.3", "From (>=) Lw1.0.4"]
mlsComboAppJoinNsVer = MLS_SRC.createComboSymbol("MLSSRC_COMBO_APPJOINNSVER", mlsMenuApp, joinNsVer)
mlsComboAppJoinNsVer.setLabel("Join server Version")
mlsComboAppJoinNsVer.setVisible(True)
mlsComboAppJoinNsVer.setDefaultValue(joinNsVer[1])
mlsComboAppJoinNsVer.setDescription("Select the join server compatibility")

msgTypes = ["UnCnf", "Cnf"]
mlsComboAppMsgType = MLS_SRC.createComboSymbol("MLSSRC_COMBO_APPMSGTYPE", mlsMenuApp, msgTypes)
mlsComboAppMsgType.setLabel("Message type")
mlsComboAppMsgType.setVisible(True)
mlsComboAppMsgType.setDefaultValue(msgTypes[0])
mlsComboAppMsgType.setDescription("Select the message type")

global mlsIntegerAppFport
mlsIntegerAppFport = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_APPFPORT", mlsMenuApp)
mlsIntegerAppFport.setLabel("Default FPort")
mlsIntegerAppFport.setMin(1)
mlsIntegerAppFport.setMax(223)
mlsIntegerAppFport.setDefaultValue(1)

global mlsIntegerAppUplinkPeriod
mlsIntegerAppUplinkPeriod = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_APPUPLINKPERIOD", mlsMenuApp)
mlsIntegerAppUplinkPeriod.setLabel("Default Uplink Period (sec)")
mlsIntegerAppUplinkPeriod.setMin(5)
mlsIntegerAppUplinkPeriod.setMax(24 * 60 * 60)
mlsIntegerAppUplinkPeriod.setDefaultValue(5)

global mlsBooleanAppClassC
mlsBooleanAppClassC = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_APPCLASSC", mlsMenuApp)
mlsBooleanAppClassC.setLabel("Class-C as default?")
mlsBooleanAppClassC.setVisible(True)
mlsBooleanAppClassC.setDefaultValue(False)
mlsBooleanAppClassC.setDescription("If selected, ED will switch automatically to class-C from first uplink")

global mlsIntegerAppSleepDuration
mlsIntegerAppSleepDuration = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_APPSLEEPDURATION", mlsMenuApp)
mlsIntegerAppSleepDuration.setLabel("Default sleep duration (sec)")
mlsIntegerAppSleepDuration.setMin(1)
mlsIntegerAppSleepDuration.setMax(130990)
mlsIntegerAppSleepDuration.setDefaultValue(1)

global mlsBooleanAppCertMode
mlsBooleanAppCertMode = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_APPCERTMODE", mlsMenuApp)
mlsBooleanAppCertMode.setLabel("Certification enabled?")
mlsBooleanAppCertMode.setVisible(True)
mlsBooleanAppCertMode.setDefaultValue(True)
mlsBooleanAppCertMode.setDescription("If selected, ED supports test port commands")

