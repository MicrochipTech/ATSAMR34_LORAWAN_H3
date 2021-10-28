# === RADIO Configuration
global mlsMenuRadio
mlsMenuRadio = MLS_SRC.createMenuSymbol("MLSSRC_MENU_RADIO", mlsMenuManualConf)
mlsMenuRadio.setLabel("RADIO Configuration")
mlsMenuRadio.setVisible(True)

global mlsBooleanRfSwitchEnable
mlsBooleanRfSwitchEnable = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_RFSWITCHENABLE", mlsMenuRadio)
mlsBooleanRfSwitchEnable.setLabel("Enable RF switch")
mlsBooleanRfSwitchEnable.setVisible(True)
mlsBooleanRfSwitchEnable.setDefaultValue(True)
mlsBooleanRfSwitchEnable.setReadOnly(False)
mlsBooleanRfSwitchEnable.setDescription("Enable RF switch")

radioClockOsc = ["TCXO", "XTAL"]
global mlsComboRadioClockOsc
mlsComboRadioClockOsc = MLS_SRC.createComboSymbol("MLSSRC_COMBO_RADIOCLOCKOSC", mlsMenuRadio, radioClockOsc)
mlsComboRadioClockOsc.setLabel("Radio Clock Oscillator")
mlsComboRadioClockOsc.setVisible(True)
mlsComboRadioClockOsc.setDefaultValue(radioClockOsc[0])
mlsComboRadioClockOsc.setDescription("Select the clock oscillator for the RADIO")

global mlsIntegerRadioStabilizationDelay
mlsIntegerRadioStabilizationDelay = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_RADIOSTABILIZATIONDELAY", mlsComboRadioClockOsc)
mlsIntegerRadioStabilizationDelay.setLabel("TCXO Stabilization Delay (unit: ms)")
mlsIntegerRadioStabilizationDelay.setMin(0)
mlsIntegerRadioStabilizationDelay.setMax(100)
mlsIntegerRadioStabilizationDelay.setDefaultValue(2)
mlsIntegerRadioStabilizationDelay.setDependencies(mlsIntegerRadioStabilizationDelayDepend, ["MLSSRC_COMBO_RADIOCLOCKOSC"])
