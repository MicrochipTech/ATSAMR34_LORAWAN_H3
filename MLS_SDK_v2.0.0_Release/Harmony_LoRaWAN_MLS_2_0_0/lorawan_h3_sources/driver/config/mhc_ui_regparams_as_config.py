# === AS923 configurations

global mlsMenuAS
mlsMenuAS = MLS_SRC.createMenuSymbol("MLSSRC_MENU_AS", mlsBooleanAS)
mlsMenuAS.setLabel("AS923 Configuration")
mlsMenuAS.setVisible(True)
mlsMenuAS.setDependencies(mlsMenuASDepend, ["MLSSRC_BOOLEAN_AS"])

global mlsComboASDefTxPower
global txPowerAS
txPowerAS = []
for i in range(0, 8):
    txPowerAS.append("%d" %i)
mlsComboASDefTxPower = MLS_SRC.createComboSymbol("MLSSRC_COMBO_ASDEFTXPOWER",  mlsMenuAS, txPowerAS)
mlsComboASDefTxPower.setDefaultValue(txPowerAS[1])
mlsComboASDefTxPower.setLabel("Default TX Power")
mlsComboASDefTxPower.setDescription("Initial/default tx power used for uplink")

global datarateAS
datarateAS = ["DR0", "DR1", "DR2", "DR3", "DR4", "DR5", "DR6", "DR7"]

global mlsComboASMinDr
mlsComboASMinDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_ASMINDR",  mlsMenuAS, datarateAS)
mlsComboASMinDr.setDefaultValue(datarateAS[7])
mlsComboASMinDr.setLabel("Fastest Datarate")
mlsComboASMinDr.setDescription("Fastest transmitting that to be used by Enddevice for uplinks")

global mlsCommentASMinDr
mlsCommentASMinDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_ASMINDR", mlsComboASMinDr)
mlsCommentASMinDr.setVisible(False)

global mlsComboASMaxDr
mlsComboASMaxDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_ASMAXDR",  mlsMenuAS, datarateAS)
mlsComboASMaxDr.setDefaultValue(datarateAS[0])
mlsComboASMaxDr.setLabel("Slowest Datarate")
mlsComboASMaxDr.setDescription("Slowest transmitting that to be used by Enddevice for uplinks")

global mlsCommentASMaxDr
mlsCommentASMaxDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_ASMAXDR", mlsComboASMaxDr)
mlsCommentASMaxDr.setVisible(False)

global mlsComboASDefUplinkDr
mlsComboASDefUplinkDr = MLS_SRC.createComboSymbol("MLSSRC_COMBO_ASDEFUPLINKDR",  mlsMenuAS, datarateAS)
mlsComboASDefUplinkDr.setDefaultValue(datarateAS[3])
mlsComboASDefUplinkDr.setLabel("Default Uplink Datarate")
mlsComboASDefUplinkDr.setDescription("DR to be used for uplink at reset/fresh start of device")

global mlsCommentASDefUplinkDr
mlsCommentASDefUplinkDr = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_ASDEFUPLINKDR", mlsComboASDefUplinkDr)
mlsCommentASDefUplinkDr.setVisible(False)

mlsComboASMinDr.setDependencies(mlsComboASMinDrDepend, ["MLSSRC_COMBO_ASMAXDR", "MLSSRC_COMBO_ASDEFUPLINKDR"])
mlsComboASMaxDr.setDependencies(mlsComboASMaxDrDepend, ["MLSSRC_COMBO_ASMINDR", "MLSSRC_COMBO_ASDEFUPLINKDR"])
mlsComboASDefUplinkDr.setDependencies(mlsComboASDefUplinkDrDepend, ["MLSSRC_COMBO_ASMINDR", "MLSSRC_COMBO_ASMAXDR"])

global mlsMenuASFeaturesSupported
mlsMenuASFeaturesSupported = MLS_SRC.createMenuSymbol("MLSSRC_MENU_ASFEATURESSUPPORTED", mlsMenuAS)
mlsMenuASFeaturesSupported.setLabel("Features Supported")
mlsMenuASFeaturesSupported.setVisible(True)

global mlsBooleanASDutyCycle
mlsBooleanASDutyCycle = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ASDUTYCYCLE", mlsMenuASFeaturesSupported)
mlsBooleanASDutyCycle.setLabel("Duty-cycle")
mlsBooleanASDutyCycle.setVisible(True)
mlsBooleanASDutyCycle.setDefaultValue(True)
mlsBooleanASDutyCycle.setDescription("Enable duty-cycling feature support for AS923 region")

global mlsBooleanASPA
mlsBooleanASPA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ASPA", mlsMenuASFeaturesSupported)
mlsBooleanASPA.setLabel("TX Power Amplification")
mlsBooleanASPA.setVisible(True)
mlsBooleanASPA.setDefaultValue(True)
mlsBooleanASPA.setDescription("Enable TX power amplification feature support for AS923 region")

global mlsBooleanASJoinBackOff
mlsBooleanASJoinBackOff = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ASJOINBACKOFF", mlsMenuASFeaturesSupported)
mlsBooleanASJoinBackOff.setLabel("Join Back-off")
mlsBooleanASJoinBackOff.setVisible(True)
mlsBooleanASJoinBackOff.setDefaultValue(True)
mlsBooleanASJoinBackOff.setDescription("Enable join back-off feature support for AS923 region")
