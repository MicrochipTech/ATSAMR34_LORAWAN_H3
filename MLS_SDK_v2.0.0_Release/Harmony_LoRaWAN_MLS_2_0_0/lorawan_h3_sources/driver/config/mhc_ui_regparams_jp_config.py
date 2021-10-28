# === AS923-1 configurations

global mlsMenuJP
mlsMenuJP = MLS_SRC.createMenuSymbol("MLSSRC_MENU_JP", mlsBooleanJP)
mlsMenuJP.setLabel("AS923-1 Configuration")
mlsMenuJP.setVisible(True)
mlsMenuJP.setDependencies(mlsMenuJPDepend, ["MLSSRC_BOOLEAN_JP"])

global mlsComboJPDefTxPower
global txPowerJP
txPowerJP = []
for i in range(0, 8):
    txPowerJP.append("%d" %i)
mlsComboJPDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_JPDEFTXPOWER",  mlsMenuJP, txPowerJP)
mlsComboJPDefTxPower.setDefaultValue(txPowerJP[1])
mlsComboJPDefTxPower.setLabel("Default TX Power")
mlsComboJPDefTxPower.setDescription("Initial/default tx power used for uplink")

global datarateJP
datarateJP = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR7"]

global mlsComboJPMinDr
mlsComboJPMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_JPMINDR",  mlsMenuJP, datarateJP)
mlsComboJPMinDr.setDefaultValue(datarateJP[7])
mlsComboJPMinDr.setLabel("Fastest Datarate")
mlsComboJPMinDr.setDescription("Fastest transmitting that to be used by Enddevice for uplinks")

global mlsCommentJPMinDr
mlsCommentJPMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_JPMINDR", mlsComboJPMinDr)
mlsCommentJPMinDr.setVisible(False)

global mlsComboJPMaxDr
mlsComboJPMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_JPMAXDR",  mlsMenuJP, datarateJP)
mlsComboJPMaxDr.setDefaultValue(datarateJP[0])
mlsComboJPMaxDr.setLabel("Slowest Datarate")
mlsComboJPMaxDr.setDescription("Slowest transmitting that to be used by Enddevice for uplinks")

global mlsCommentJPMaxDr
mlsCommentJPMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_JPMAXDR", mlsComboJPMaxDr)
mlsCommentJPMaxDr.setVisible(False)

global mlsComboJPDefUplinkDr
mlsComboJPDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_JPDEFUPLINKDR",  mlsMenuJP, datarateJP)
mlsComboJPDefUplinkDr.setDefaultValue(datarateJP[3])
mlsComboJPDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboJPDefUplinkDr.setDescription("DR to be used for uplink at reset/fresh start of device")

global mlsCommentJPDefUplinkDr
mlsCommentJPDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_JPDEFUPLINKDR", mlsComboJPDefUplinkDr)
mlsCommentJPDefUplinkDr.setVisible(False)

mlsComboJPMinDr.setDependencies(mlsComboJPMinDrDepend, ["MLSSRC_COMBO_JPMAXDR", "MLSSRC_COMBO_JPDEFUPLINKDR"])
mlsComboJPMaxDr.setDependencies(mlsComboJPMaxDrDepend, ["MLSSRC_COMBO_JPMINDR", "MLSSRC_COMBO_JPDEFUPLINKDR"])
mlsComboJPDefUplinkDr.setDependencies(mlsComboJPDefUplinkDrDepend, ["MLSSRC_COMBO_JPMINDR", "MLSSRC_COMBO_JPMAXDR"])

global mlsMenuJPFeaturesSupported
mlsMenuJPFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_JPFEATURESSUPPORTED", mlsMenuJP)
mlsMenuJPFeaturesSupported.setLabel("Features Supported")
mlsMenuJPFeaturesSupported.setVisible(True)

global mlsBooleanJPLBT
mlsBooleanJPLBT = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_JPLBT", mlsMenuJPFeaturesSupported)
mlsBooleanJPLBT.setLabel("Listen Before Talk")
mlsBooleanJPLBT.setVisible(True)
mlsBooleanJPLBT.setDefaultValue(True)
mlsBooleanJPLBT.setDescription("Enable listen-before-talk feature support for AS923-1 region")

global mlsBooleanJPDutyCycle
mlsBooleanJPDutyCycle = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_JPDUTYCYCLE", mlsMenuJPFeaturesSupported)
mlsBooleanJPDutyCycle.setLabel("Duty-cycle")
mlsBooleanJPDutyCycle.setVisible(True)
mlsBooleanJPDutyCycle.setDefaultValue(True)
mlsBooleanJPDutyCycle.setDescription("Enable duty-cycling feature support for AS923-1 region")

global mlsBooleanJPPA
mlsBooleanJPPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_JPPA", mlsMenuJPFeaturesSupported)
mlsBooleanJPPA.setLabel("TX Power Amplification")
mlsBooleanJPPA.setVisible(True)
mlsBooleanJPPA.setDefaultValue(True)
mlsBooleanJPPA.setDescription("Enable TX power amplification feature support for AS923-1 region")

global mlsBooleanJPJoinBackOff
mlsBooleanJPJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_JPJOINBACKOFF", mlsMenuJPFeaturesSupported)
mlsBooleanJPJoinBackOff.setLabel("Join Back-off")
mlsBooleanJPJoinBackOff.setVisible(True)
mlsBooleanJPJoinBackOff.setDefaultValue(True)
mlsBooleanJPJoinBackOff.setDescription("Enable join back-off feature support for AS923-1 region")

global mlsIntegerJPLbtRssiSampleCount
mlsIntegerJPLbtRssiSampleCount = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_JPLBTRSSISAMPLESCOUNT", mlsBooleanJPLBT)
mlsIntegerJPLbtRssiSampleCount.setLabel("LBT Scan Retries")
mlsIntegerJPLbtRssiSampleCount.setMin(1)
mlsIntegerJPLbtRssiSampleCount.setMax(100)
mlsIntegerJPLbtRssiSampleCount.setDefaultValue(5)
mlsIntegerJPLbtRssiSampleCount.setDescription("Number of retries to scan channels for Listen-Before-Talk")
mlsIntegerJPLbtRssiSampleCount.setDependencies(mlsmlsIntegerJPLbtRssiSampleCountDepend, ["MLSSRC_BOOLEAN_JPLBT"])
