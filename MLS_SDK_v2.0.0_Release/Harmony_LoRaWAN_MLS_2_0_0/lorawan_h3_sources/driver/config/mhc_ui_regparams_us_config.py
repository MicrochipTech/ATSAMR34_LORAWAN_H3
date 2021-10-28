# === US902-928 configurations

global mlsMenuUS
mlsMenuUS = MLS_SRC.createMenuSymbol("MLSSRC_MENU_US", mlsBooleanUS)
mlsMenuUS.setLabel("US902-928 Configuration")
mlsMenuUS.setVisible(True)
mlsMenuUS.setDependencies(mlsMenuUSDepend, ["MLSSRC_BOOLEAN_US"])

global mlsComboUSDefTxPower
global txPowerUS
txPowerUS = []
for i in range(0, 15):
    txPowerUS.append("%d" %i)
mlsComboUSDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_USDEFTXPOWER",  mlsMenuUS, txPowerUS)
mlsComboUSDefTxPower.setDefaultValue(txPowerUS[7])
mlsComboUSDefTxPower.setLabel("Default TX Power")
mlsComboUSDefTxPower.setDescription("Initial/default tx power used for uplink")

global datarateUS
datarateUS = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR8", "DR9", "DR10", "DR11", "DR12", "DR13"]

global mlsComboUSMinDr
mlsComboUSMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_USMINDR",  mlsMenuUS, datarateUS[0:5])
mlsComboUSMinDr.setDefaultValue(datarateUS[4])
mlsComboUSMinDr.setLabel("Fastest Datarate")
mlsComboUSMinDr.setDescription("Fastest transmitting that to be used by Enddevice for uplinks")

global mlsCommentUSMinDr
mlsCommentUSMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_USMINDR", mlsComboUSMinDr)
mlsCommentUSMinDr.setVisible(False)

global mlsComboUSMaxDr
mlsComboUSMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_USMAXDR",  mlsMenuUS, datarateUS[0:5])
mlsComboUSMaxDr.setDefaultValue(datarateUS[0])
mlsComboUSMaxDr.setLabel("Slowest Datarate")
mlsComboUSMaxDr.setDescription("Slowest transmitting that to be used by Enddevice for uplinks")

global mlsCommentUSMaxDr
mlsCommentUSMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_USMAXDR", mlsComboUSMaxDr)
mlsCommentUSMaxDr.setVisible(False)

global mlsComboUSDefUplinkDr
mlsComboUSDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_USDEFUPLINKDR",  mlsMenuUS, datarateUS[0:5])
mlsComboUSDefUplinkDr.setDefaultValue(datarateUS[2])
mlsComboUSDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboUSDefUplinkDr.setDescription("DR to be used for uplink at reset/fresh start of device")

global mlsCommentUSDefUplinkDr
mlsCommentUSDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_USDEFUPLINKDR", mlsComboUSDefUplinkDr)
mlsCommentUSDefUplinkDr.setVisible(False)

mlsComboUSMinDr.setDependencies(mlsComboUSMinDrDepend, ["MLSSRC_COMBO_USMAXDR", "MLSSRC_COMBO_USDEFUPLINKDR"])
mlsComboUSMaxDr.setDependencies(mlsComboUSMaxDrDepend, ["MLSSRC_COMBO_USMINDR", "MLSSRC_COMBO_USDEFUPLINKDR"])
mlsComboUSDefUplinkDr.setDependencies(mlsComboUSDefUplinkDrDepend, ["MLSSRC_COMBO_USMINDR", "MLSSRC_COMBO_USMAXDR"])

global mlsMenuUSFeaturesSupported
mlsMenuUSFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_USFEATURESSUPPORTED", mlsMenuUS)
mlsMenuUSFeaturesSupported.setLabel("Features Supported")
mlsMenuUSFeaturesSupported.setVisible(True)

global mlsBooleanUSFHSS
mlsBooleanUSFHSS = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USFHSS", mlsMenuUSFeaturesSupported)
mlsBooleanUSFHSS.setLabel("FHSS")
mlsBooleanUSFHSS.setVisible(True)
mlsBooleanUSFHSS.setDefaultValue(True)
mlsBooleanUSFHSS.setDescription("Enable FHSS feature support for US902-928 region")

global mlsBooleanUSPA
mlsBooleanUSPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USPA", mlsMenuUSFeaturesSupported)
mlsBooleanUSPA.setLabel("TX Power Amplification")
mlsBooleanUSPA.setVisible(True)
mlsBooleanUSPA.setDefaultValue(True)
mlsBooleanUSPA.setDescription("Enable TX power amplification feature support for US902-928 region")

global mlsBooleanUSJoinBackOff
mlsBooleanUSJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USJOINBACKOFF", mlsMenuUSFeaturesSupported)
mlsBooleanUSJoinBackOff.setLabel("Join Back-off")
mlsBooleanUSJoinBackOff.setVisible(True)
mlsBooleanUSJoinBackOff.setDefaultValue(True)
mlsBooleanUSJoinBackOff.setDescription("Enable join back-off feature support for US902-928 region")

global mlsMenuUSSubband
mlsMenuUSSubband = MLS_SRC.createMenuSymbol("MLSSRC_MENU_USSUBBAND", mlsMenuUS)
mlsMenuUSSubband.setLabel("Sub-Bands")
mlsMenuUSSubband.setVisible(True)

global mlsBooleanUSSubband1
mlsBooleanUSSubband1 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND1", mlsMenuUSSubband)
mlsBooleanUSSubband1.setLabel("1 (Channels: 0 to 7, 64)")
mlsBooleanUSSubband1.setVisible(True)
mlsBooleanUSSubband1.setDefaultValue(True)
mlsBooleanUSSubband1.setDescription("Enable sub-band #1 for US902-928 region")

global mlsBooleanUSSubband2
mlsBooleanUSSubband2 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND2", mlsMenuUSSubband)
mlsBooleanUSSubband2.setLabel("2 (Channels: 8 to 15, 65)")
mlsBooleanUSSubband2.setVisible(True)
mlsBooleanUSSubband2.setDefaultValue(True)
mlsBooleanUSSubband2.setDescription("Enable sub-band #2 for US902-928 region")

global mlsBooleanUSSubband3
mlsBooleanUSSubband3 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND3", mlsMenuUSSubband)
mlsBooleanUSSubband3.setLabel("3 (Channels: 16 to 23, 66)")
mlsBooleanUSSubband3.setVisible(True)
mlsBooleanUSSubband3.setDefaultValue(True)
mlsBooleanUSSubband3.setDescription("Enable sub-band #3 for US902-928 region")

global mlsBooleanUSSubband4
mlsBooleanUSSubband4 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND4", mlsMenuUSSubband)
mlsBooleanUSSubband4.setLabel("4 (Channels: 24 to 31, 67)")
mlsBooleanUSSubband4.setVisible(True)
mlsBooleanUSSubband4.setDefaultValue(True)
mlsBooleanUSSubband4.setDescription("Enable sub-band #4 for US902-928 region")

global mlsBooleanUSSubband5
mlsBooleanUSSubband5 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND5", mlsMenuUSSubband)
mlsBooleanUSSubband5.setLabel("5 (Channels: 32 to 39, 68)")
mlsBooleanUSSubband5.setVisible(True)
mlsBooleanUSSubband5.setDefaultValue(True)
mlsBooleanUSSubband5.setDescription("Enable sub-band #5 for US902-928 region")

global mlsBooleanUSSubband6
mlsBooleanUSSubband6 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND6", mlsMenuUSSubband)
mlsBooleanUSSubband6.setLabel("6 (Channels: 40 to 47, 69)")
mlsBooleanUSSubband6.setVisible(True)
mlsBooleanUSSubband6.setDefaultValue(True)
mlsBooleanUSSubband6.setDescription("Enable sub-band #6 for US902-928 region")

global mlsBooleanUSSubband7
mlsBooleanUSSubband8 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND7", mlsMenuUSSubband)
mlsBooleanUSSubband8.setLabel("7 (Channels: 48 to 55, 70)")
mlsBooleanUSSubband8.setVisible(True)
mlsBooleanUSSubband8.setDefaultValue(True)
mlsBooleanUSSubband8.setDescription("Enable sub-band #7 for US902-928 region")

global mlsBooleanUSSubband8
mlsBooleanUSSubband8 = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_USSUBBAND8", mlsMenuUSSubband)
mlsBooleanUSSubband8.setLabel("8 (Channels: 56 to 63, 71)")
mlsBooleanUSSubband8.setVisible(True)
mlsBooleanUSSubband8.setDefaultValue(True)
mlsBooleanUSSubband8.setDescription("Enable sub-band #8 for US902-928 region")
