# === EU863-870 configurations

global mlsMenuEU
mlsMenuEU = MLS_SRC.createMenuSymbol("MLSSRC_MENU_EU", mlsBooleanEU)
mlsMenuEU.setLabel("EU863-760 Configuration")
mlsMenuEU.setVisible(True)
mlsMenuEU.setDependencies(mlsMenuEUDepend, ["MLSSRC_BOOLEAN_EU"])

global mlsComboEUDefTxPower
global txPowerEU
txPowerEU = []
for i in range(0, 8):
    txPowerEU.append("%d" %i)
mlsComboEUDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_EUDEFTXPOWER",  mlsMenuEU, txPowerEU)
mlsComboEUDefTxPower.setDefaultValue(txPowerEU[1])
mlsComboEUDefTxPower.setLabel("Default TX Power")
mlsComboEUDefTxPower.setDescription("Initial/default tx power used for uplink")

global datarateEU
datarateEU = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR7"]

global mlsComboEUMinDr
mlsComboEUMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_EUMINDR",  mlsMenuEU, datarateEU)
mlsComboEUMinDr.setDefaultValue(datarateEU[5])
mlsComboEUMinDr.setLabel("Fastest Datarate")
mlsComboEUMinDr.setDescription("Fastest transmitting that to be used by Enddevice for uplinks")

global mlsCommentEUMinDr
mlsCommentEUMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_EUMINDR", mlsComboEUMinDr)
mlsCommentEUMinDr.setVisible(False)

global mlsComboEUMaxDr
mlsComboEUMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_EUMAXDR",  mlsMenuEU, datarateEU)
mlsComboEUMaxDr.setDefaultValue(datarateEU[0])
mlsComboEUMaxDr.setLabel("Slowest Datarate")
mlsComboEUMaxDr.setDescription("Slowest transmitting that to be used by Enddevice for uplinks")

global mlsCommentEUMaxDr
mlsCommentEUMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_EUMAXDR", mlsComboEUMaxDr)
mlsCommentEUMaxDr.setVisible(False)

global mlsComboEUDefUplinkDr
mlsComboEUDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_EUDEFUPLINKDR",  mlsMenuEU, datarateEU)
mlsComboEUDefUplinkDr.setDefaultValue(datarateEU[1])
mlsComboEUDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboEUDefUplinkDr.setDescription("DR to be used for uplink at reset/fresh start of device")

global mlsCommentEUDefUplinkDr
mlsCommentEUDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_EUDEFUPLINKDR", mlsComboEUDefUplinkDr)
mlsCommentEUDefUplinkDr.setVisible(False)

mlsComboEUMinDr.setDependencies(mlsComboEUMinDrDepend, ["MLSSRC_COMBO_EUMAXDR", "MLSSRC_COMBO_EUDEFUPLINKDR"])
mlsComboEUMaxDr.setDependencies(mlsComboEUMaxDrDepend, ["MLSSRC_COMBO_EUMINDR", "MLSSRC_COMBO_EUDEFUPLINKDR"])
mlsComboEUDefUplinkDr.setDependencies(mlsComboEUDefUplinkDrDepend, ["MLSSRC_COMBO_EUMINDR", "MLSSRC_COMBO_EUMAXDR"])

global mlsMenuEUFeaturesSupported
mlsMenuEUFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_EUFEATURESSUPPORTED", mlsMenuEU)
mlsMenuEUFeaturesSupported.setLabel("Features Supported")
mlsMenuEUFeaturesSupported.setVisible(True)

global mlsBooleanEUDutyCycle
mlsBooleanEUDutyCycle = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_EUDUTYCYCLE", mlsMenuEUFeaturesSupported)
mlsBooleanEUDutyCycle.setLabel("Duty-cycle")
mlsBooleanEUDutyCycle.setVisible(True)
mlsBooleanEUDutyCycle.setDefaultValue(True)
mlsBooleanEUDutyCycle.setDescription("Enable duty-cycling feature support for EU863-870 region")

global mlsBooleanEUPA
mlsBooleanEUPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_EUPA", mlsMenuEUFeaturesSupported)
mlsBooleanEUPA.setLabel("TX Power Amplification")
mlsBooleanEUPA.setVisible(True)
mlsBooleanEUPA.setDefaultValue(True)
mlsBooleanEUPA.setDescription("Enable TX power amplification feature support for EU863-870 region")

global mlsBooleanEUJoinBackOff
mlsBooleanEUJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_EUJOINBACKOFF", mlsMenuEUFeaturesSupported)
mlsBooleanEUJoinBackOff.setLabel("Join Back-off")
mlsBooleanEUJoinBackOff.setVisible(True)
mlsBooleanEUJoinBackOff.setDefaultValue(True)
mlsBooleanEUJoinBackOff.setDescription("Enable join back-off feature support for EU863-870 region")
