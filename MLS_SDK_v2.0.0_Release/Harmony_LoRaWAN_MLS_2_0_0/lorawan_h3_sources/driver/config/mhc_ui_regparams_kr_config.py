# === KR920-923 configurations

global mlsMenuKR
mlsMenuKR = MLS_SRC.createMenuSymbol("MLSSRC_MENU_KR", mlsBooleanKR)
mlsMenuKR.setLabel("KR920-923 Configuration")
mlsMenuKR.setVisible(True)
mlsMenuKR.setDependencies(mlsMenuKRDepend, ["MLSSRC_BOOLEAN_KR"])

global mlsComboKRDefTxPower
global txPowerKR
txPowerKR = []
for i in range(0, 8):
    txPowerKR.append("%d" %i)
mlsComboKRDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_KRDEFTXPOWER",  mlsMenuKR, txPowerKR)
mlsComboKRDefTxPower.setDefaultValue(txPowerKR[1])
mlsComboKRDefTxPower.setLabel("Default TX Power")
mlsComboKRDefTxPower.setDescription("Initial/default tx power used for uplink")

global datarateKR
datarateKR = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR5"]

global mlsComboKRMinDr
mlsComboKRMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_KRMINDR",  mlsMenuKR, datarateKR)
mlsComboKRMinDr.setDefaultValue(datarateKR[5])
mlsComboKRMinDr.setLabel("Fastest Datarate")
mlsComboKRMinDr.setDescription("Fastest transmitting that to be used by Enddevice for uplinks")

global mlsCommentKRMinDr
mlsCommentKRMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_KRMINDR", mlsComboKRMinDr)
mlsCommentKRMinDr.setVisible(False)

global mlsComboKRMaxDr
mlsComboKRMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_KRMAXDR",  mlsMenuKR, datarateKR)
mlsComboKRMaxDr.setDefaultValue(datarateKR[0])
mlsComboKRMaxDr.setLabel("Slowest Datarate")
mlsComboKRMaxDr.setDescription("Slowest transmitting that to be used by Enddevice for uplinks")

global mlsCommentKRMaxDr
mlsCommentKRMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_KRMAXDR", mlsComboKRMaxDr)
mlsCommentKRMaxDr.setVisible(False)

global mlsComboKRDefUplinkDr
mlsComboKRDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_KRDEFUPLINKDR",  mlsMenuKR, datarateKR)
mlsComboKRDefUplinkDr.setDefaultValue(datarateKR[3])
mlsComboKRDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboKRDefUplinkDr.setDescription("DR to be used for uplink at reset/fresh start of device")

global mlsCommentKRDefUplinkDr
mlsCommentKRDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_KRDEFUPLINKDR", mlsComboKRDefUplinkDr)
mlsCommentKRDefUplinkDr.setVisible(False)

mlsComboKRMinDr.setDependencies(mlsComboKRMinDrDepend, ["MLSSRC_COMBO_KRMAXDR", "MLSSRC_COMBO_KRDEFUPLINKDR"])
mlsComboKRMaxDr.setDependencies(mlsComboKRMaxDrDepend, ["MLSSRC_COMBO_KRMINDR", "MLSSRC_COMBO_KRDEFUPLINKDR"])
mlsComboKRDefUplinkDr.setDependencies(mlsComboKRDefUplinkDrDepend, ["MLSSRC_COMBO_KRMINDR", "MLSSRC_COMBO_KRMAXDR"])

global mlsMenuKRFeaturesSupported
mlsMenuKRFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_KRFEATURESSUPPORTED", mlsMenuKR)
mlsMenuKRFeaturesSupported.setLabel("Features Supported")
mlsMenuKRFeaturesSupported.setVisible(True)

global mlsBooleanKRLBT
mlsBooleanKRLBT = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_KRLBT", mlsMenuKRFeaturesSupported)
mlsBooleanKRLBT.setLabel("Listen Before Talk")
mlsBooleanKRLBT.setVisible(True)
mlsBooleanKRLBT.setDefaultValue(True)
mlsBooleanKRLBT.setDescription("Enable listen-before-talk feature support for KR920-923 region")

global mlsBooleanKRPA
mlsBooleanKRPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_KRPA", mlsMenuKRFeaturesSupported)
mlsBooleanKRPA.setLabel("TX Power Amplification")
mlsBooleanKRPA.setVisible(True)
mlsBooleanKRPA.setDefaultValue(True)
mlsBooleanKRPA.setDescription("Enable TX power amplification feature support for KR920-923 region")

global mlsBooleanKRJoinBackOff
mlsBooleanKRJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_KRJOINBACKOFF", mlsMenuKRFeaturesSupported)
mlsBooleanKRJoinBackOff.setLabel("Join Back-off")
mlsBooleanKRJoinBackOff.setVisible(True)
mlsBooleanKRJoinBackOff.setDefaultValue(True)
mlsBooleanKRJoinBackOff.setDescription("Enable join back-off feature support for KR920-923 region")

global mlsIntegerKRLbtRssiSampleCount
mlsIntegerKRLbtRssiSampleCount = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_KRLBTRSSISAMPLESCOUNT", mlsBooleanKRLBT)
mlsIntegerKRLbtRssiSampleCount.setLabel("LBT Scan Retries")
mlsIntegerKRLbtRssiSampleCount.setMin(1)
mlsIntegerKRLbtRssiSampleCount.setMax(100)
mlsIntegerKRLbtRssiSampleCount.setDefaultValue(10)
mlsIntegerKRLbtRssiSampleCount.setDescription("Number of retries to scan channels for Listen-Before-Talk")
mlsIntegerKRLbtRssiSampleCount.setDependencies(mlsmlsIntegerKRLbtRssiSampleCountDepend, ["MLSSRC_BOOLEAN_KRLBT"])
