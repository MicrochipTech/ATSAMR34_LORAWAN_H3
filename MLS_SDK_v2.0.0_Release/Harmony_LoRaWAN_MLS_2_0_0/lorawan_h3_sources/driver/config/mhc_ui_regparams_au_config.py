# === AU915-928 configurations

global mlsMenuAU
mlsMenuAU = MLS_SRC.createMenuSymbol("MLSSRC_MENU_AU", mlsBooleanAU)
mlsMenuAU.setLabel("AU915-928 Configuration")
mlsMenuAU.setVisible(True)
mlsMenuAU.setDependencies(mlsMenuAUDepend, ["MLSSRC_BOOLEAN_AU"])

global mlsComboAUDefTxPower
global txPowerAU
txPowerAU = []
for i in range(0, 15):
    txPowerAU.append("%d" %i)
mlsComboAUDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_AUDEFTXPOWER",  mlsMenuAU, txPowerAU)
mlsComboAUDefTxPower.setDefaultValue(txPowerAU[7])
mlsComboAUDefTxPower.setLabel("Default TX Power")
mlsComboAUDefTxPower.setDescription("Initial/default tx power AUed for uplink")

global datarateAU
datarateAU = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR8", "DR9", "DR10", "DR11", "DR12", "DR13"]

global mlsComboAUMinDr
mlsComboAUMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_AUMINDR",  mlsMenuAU, datarateAU[0:7])
mlsComboAUMinDr.setDefaultValue(datarateAU[6])
mlsComboAUMinDr.setLabel("Fastest Datarate")
mlsComboAUMinDr.setDescription("Fastest transmitting that to be AUed by Enddevice for uplinks")

global mlsCommentAUMinDr
mlsCommentAUMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_AUMINDR", mlsComboAUMinDr)
mlsCommentAUMinDr.setVisible(False)

global mlsComboAUMaxDr
mlsComboAUMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_AUMAXDR",  mlsMenuAU, datarateAU[0:7])
mlsComboAUMaxDr.setDefaultValue(datarateAU[0])
mlsComboAUMaxDr.setLabel("Slowest Datarate")
mlsComboAUMaxDr.setDescription("Slowest transmitting that to be AUed by Enddevice for uplinks")

global mlsCommentAUMaxDr
mlsCommentAUMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_AUMAXDR", mlsComboAUMaxDr)
mlsCommentAUMaxDr.setVisible(False)

global mlsComboAUDefUplinkDr
mlsComboAUDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_AUDEFUPLINKDR",  mlsMenuAU, datarateAU[0:7])
mlsComboAUDefUplinkDr.setDefaultValue(datarateAU[3])
mlsComboAUDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboAUDefUplinkDr.setDescription("DR to be AUed for uplink at reset/fresh start of device")

global mlsCommentAUDefUplinkDr
mlsCommentAUDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_AUDEFUPLINKDR", mlsComboAUDefUplinkDr)
mlsCommentAUDefUplinkDr.setVisible(False)

mlsComboAUMinDr.setDependencies(mlsComboAUMinDrDepend, ["MLSSRC_COMBO_AUMAXDR", "MLSSRC_COMBO_AUDEFUPLINKDR"])
mlsComboAUMaxDr.setDependencies(mlsComboAUMaxDrDepend, ["MLSSRC_COMBO_AUMINDR", "MLSSRC_COMBO_AUDEFUPLINKDR"])
mlsComboAUDefUplinkDr.setDependencies(mlsComboAUDefUplinkDrDepend, ["MLSSRC_COMBO_AUMINDR", "MLSSRC_COMBO_AUMAXDR"])

global mlsMenuAUFeaturesSupported
mlsMenuAUFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_AUFEATURESSUPPORTED", mlsMenuAU)
mlsMenuAUFeaturesSupported.setLabel("Features Supported")
mlsMenuAUFeaturesSupported.setVisible(True)

global mlsBooleanAUFHSS
mlsBooleanAUFHSS = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUFHSS", mlsMenuAUFeaturesSupported)
mlsBooleanAUFHSS.setLabel("FHSS")
mlsBooleanAUFHSS.setVisible(True)
mlsBooleanAUFHSS.setDefaultValue(True)
mlsBooleanAUFHSS.setDescription("Enable FHSS feature support for AU915-928 region")

global mlsBooleanAUPA
mlsBooleanAUPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUPA", mlsMenuAUFeaturesSupported)
mlsBooleanAUPA.setLabel("TX Power Amplification")
mlsBooleanAUPA.setVisible(True)
mlsBooleanAUPA.setDefaultValue(True)
mlsBooleanAUPA.setDescription("Enable TX power amplification feature support for AU915-928 region")

global mlsBooleanAUJoinBackOff
mlsBooleanAUJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUJOINBACKOFF", mlsMenuAUFeaturesSupported)
mlsBooleanAUJoinBackOff.setLabel("Join Back-off")
mlsBooleanAUJoinBackOff.setVisible(True)
mlsBooleanAUJoinBackOff.setDefaultValue(True)
mlsBooleanAUJoinBackOff.setDescription("Enable join back-off feature support for AU915-928 region")

global mlsMenuAUSubband
mlsMenuAUSubband = MLS_SRC.createMenuSymbol("MLSSRC_MENU_AUSUBBAND", mlsMenuAU)
mlsMenuAUSubband.setLabel("Sub-Bands")
mlsMenuAUSubband.setVisible(True)

global mlsBooleanAUSubband1
mlsBooleanAUSubband1 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND1", mlsMenuAUSubband)
mlsBooleanAUSubband1.setLabel("1 (Channels: 0 to 7, 64)")
mlsBooleanAUSubband1.setVisible(True)
mlsBooleanAUSubband1.setDefaultValue(True)
mlsBooleanAUSubband1.setDescription("Enable sub-band #1 for AU915-928 region")

global mlsBooleanAUSubband2
mlsBooleanAUSubband2 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND2", mlsMenuAUSubband)
mlsBooleanAUSubband2.setLabel("2 (Channels: 8 to 15, 65)")
mlsBooleanAUSubband2.setVisible(True)
mlsBooleanAUSubband2.setDefaultValue(True)
mlsBooleanAUSubband2.setDescription("Enable sub-band #2 for AU915-928 region")

global mlsBooleanAUSubband3
mlsBooleanAUSubband3 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND3", mlsMenuAUSubband)
mlsBooleanAUSubband3.setLabel("3 (Channels: 16 to 23, 66)")
mlsBooleanAUSubband3.setVisible(True)
mlsBooleanAUSubband3.setDefaultValue(True)
mlsBooleanAUSubband3.setDescription("Enable sub-band #3 for AU915-928 region")

global mlsBooleanAUSubband4
mlsBooleanAUSubband4 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND4", mlsMenuAUSubband)
mlsBooleanAUSubband4.setLabel("4 (Channels: 24 to 31, 67)")
mlsBooleanAUSubband4.setVisible(True)
mlsBooleanAUSubband4.setDefaultValue(True)
mlsBooleanAUSubband4.setDescription("Enable sub-band #4 for AU915-928 region")

global mlsBooleanAUSubband5
mlsBooleanAUSubband5 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND5", mlsMenuAUSubband)
mlsBooleanAUSubband5.setLabel("5 (Channels: 32 to 39, 68)")
mlsBooleanAUSubband5.setVisible(True)
mlsBooleanAUSubband5.setDefaultValue(True)
mlsBooleanAUSubband5.setDescription("Enable sub-band #5 for AU915-928 region")

global mlsBooleanAUSubband6
mlsBooleanAUSubband6 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND6", mlsMenuAUSubband)
mlsBooleanAUSubband6.setLabel("6 (Channels: 40 to 47, 69)")
mlsBooleanAUSubband6.setVisible(True)
mlsBooleanAUSubband6.setDefaultValue(True)
mlsBooleanAUSubband6.setDescription("Enable sub-band #6 for AU915-928 region")

global mlsBooleanAUSubband7
mlsBooleanAUSubband8 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND7", mlsMenuAUSubband)
mlsBooleanAUSubband8.setLabel("7 (Channels: 48 to 55, 70)")
mlsBooleanAUSubband8.setVisible(True)
mlsBooleanAUSubband8.setDefaultValue(True)
mlsBooleanAUSubband8.setDescription("Enable sub-band #7 for AU915-928 region")

global mlsBooleanAUSubband8
mlsBooleanAUSubband8 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AUSUBBAND8", mlsMenuAUSubband)
mlsBooleanAUSubband8.setLabel("8 (Channels: 56 to 63, 71)")
mlsBooleanAUSubband8.setVisible(True)
mlsBooleanAUSubband8.setDefaultValue(True)
mlsBooleanAUSubband8.setDescription("Enable sub-band #8 for AU915-928 region")
