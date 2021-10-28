# === PMM Configuration
global mlsMenuPmm
mlsMenuPmm = MLS_SRC.createMenuSymbol("MLSSRC_MENU_PMM", mlsMenuManualConf)
mlsMenuPmm.setLabel("Sleep (PMM) Configuration")
mlsMenuPmm.setVisible(True)

global mlsBooleanEnableSleep
mlsBooleanEnableSleep = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ENABLESLEEP", mlsMenuPmm)
mlsBooleanEnableSleep.setLabel("Enable Sleep (PMM)")
mlsBooleanEnableSleep.setVisible(True)
mlsBooleanEnableSleep.setDefaultValue(True)
mlsBooleanEnableSleep.setDescription("Enable power management in stack")

pmmSleepModes = ["Stand-By", "Backup"] 
global mlsComboPmmSleepMode
mlsComboPmmSleepMode = MLS_SRC.createComboSymbol("MLSSRC_COMBO_PMMSLEEPMODE", mlsMenuPmm, pmmSleepModes)
mlsComboPmmSleepMode.setLabel("Default Sleep Mode")
mlsComboPmmSleepMode.setVisible(True)
mlsComboPmmSleepMode.setDefaultValue(pmmSleepModes[0])
mlsComboPmmSleepMode.setDescription("Select the default sleep mode for PMM")
