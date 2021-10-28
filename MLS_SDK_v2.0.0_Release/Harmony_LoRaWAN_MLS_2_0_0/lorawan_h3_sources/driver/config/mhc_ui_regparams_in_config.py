# === IN865-867 configurations

global mlsMenuIN
mlsMenuIN = MLS_SRC.createMenuSymbol("MLSSRC_MENU_IN", mlsBooleanIN)
mlsMenuIN.setLabel("IN865-867 Configuration")
mlsMenuIN.setVisible(True)
mlsMenuIN.setDependencies(mlsMenuINDepend, ["MLSSRC_BOOLEAN_IN"])

global mlsComboINDefTxPower
global txPowerIN
txPowerIN = []
for i in range(0, 8):
    txPowerIN.append("%d" %i)
mlsComboINDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_INDEFTXPOWER",  mlsMenuIN, txPowerIN)
mlsComboINDefTxPower.setDefaultValue(txPowerIN[1])
mlsComboINDefTxPower.setLabel("Default TX Power")
mlsComboINDefTxPower.setDescription("Initial/default tx power used for uplink")

global datarateIN
datarateIN = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR5", None, "DR7"]

global mlsComboINMinDr
mlsComboINMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_INMINDR",  mlsMenuIN, datarateIN[:5] + [datarateIN[7]])
mlsComboINMinDr.setDefaultValue(datarateIN[7])
mlsComboINMinDr.setLabel("Fastest Datarate")
mlsComboINMinDr.setDescription("Fastest transmitting that to be used by Enddevice for uplinks")

global mlsCommentINMinDr
mlsCommentINMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_INMINDR", mlsComboINMinDr)
mlsCommentINMinDr.setVisible(False)

global mlsComboINMaxDr
mlsComboINMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_INMAXDR",  mlsMenuIN, datarateIN[:5] + [datarateIN[7]])
mlsComboINMaxDr.setDefaultValue(datarateIN[0])
mlsComboINMaxDr.setLabel("Slowest Datarate")
mlsComboINMaxDr.setDescription("Slowest transmitting that to be used by Enddevice for uplinks")

global mlsCommentINMaxDr
mlsCommentINMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_INMAXDR", mlsComboINMaxDr)
mlsCommentINMaxDr.setVisible(False)

global mlsComboINDefUplinkDr
mlsComboINDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_INDEFUPLINKDR",  mlsMenuIN, datarateIN[:5] + [datarateIN[7]])
mlsComboINDefUplinkDr.setDefaultValue(datarateIN[3])
mlsComboINDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboINDefUplinkDr.setDescription("DR to be used for uplink at reset/fresh start of device")

global mlsCommentINDefUplinkDr
mlsCommentINDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_INDEFUPLINKDR", mlsComboINDefUplinkDr)
mlsCommentINDefUplinkDr.setVisible(False)

mlsComboINMinDr.setDependencies(mlsComboINMinDrDepend, ["MLSSRC_COMBO_INMAXDR", "MLSSRC_COMBO_INDEFUPLINKDR"])
mlsComboINMaxDr.setDependencies(mlsComboINMaxDrDepend, ["MLSSRC_COMBO_INMINDR", "MLSSRC_COMBO_INDEFUPLINKDR"])
mlsComboINDefUplinkDr.setDependencies(mlsComboINDefUplinkDrDepend, ["MLSSRC_COMBO_INMINDR", "MLSSRC_COMBO_INMAXDR"])

global mlsMenuINFeaturesSupported
mlsMenuINFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_INFEATURESSUPPORTED", mlsMenuIN)
mlsMenuINFeaturesSupported.setLabel("Features Supported")
mlsMenuINFeaturesSupported.setVisible(True)

global mlsBooleanINPA
mlsBooleanINPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_INPA", mlsMenuINFeaturesSupported)
mlsBooleanINPA.setLabel("TX Power Amplification")
mlsBooleanINPA.setVisible(True)
mlsBooleanINPA.setDefaultValue(True)
mlsBooleanINPA.setDescription("Enable TX power amplification feature support for IN865-867 region")

global mlsBooleanINJoinBackOff
mlsBooleanINJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_INJOINBACKOFF", mlsMenuINFeaturesSupported)
mlsBooleanINJoinBackOff.setLabel("Join Back-off")
mlsBooleanINJoinBackOff.setVisible(True)
mlsBooleanINJoinBackOff.setDefaultValue(True)
mlsBooleanINJoinBackOff.setDescription("Enable join back-off feature support for IN865-867 region")
