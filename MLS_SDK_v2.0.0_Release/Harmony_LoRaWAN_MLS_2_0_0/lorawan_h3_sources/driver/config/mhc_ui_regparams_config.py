# === RegParams Configuration

# === RP top-level menu
global mlsMenuRP
mlsMenuRP = MLS_SRC.createMenuSymbol("MLSSRC_MENU_RP", mlsMenuManualConf)
mlsMenuRP.setLabel("RegParams Configuration")
mlsMenuRP.setVisible(True)

# === EU863-870
global mlsBooleanEU
mlsBooleanEU = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_EU", mlsMenuRP)
mlsBooleanEU.setLabel("EU863-870")
mlsBooleanEU.setVisible(True)
mlsBooleanEU.setDefaultValue(True)
mlsBooleanEU.setDescription("Enable support for EU863-870 region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_eu_config.py")

# === US902-928
global mlsBooleanUS
mlsBooleanUS = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_US", mlsMenuRP)
mlsBooleanUS.setLabel("US902-928")
mlsBooleanUS.setVisible(True)
mlsBooleanUS.setDefaultValue(True)
mlsBooleanUS.setDescription("Enable support for US902-928 region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_us_config.py")

# === AU915-928
global mlsBooleanAU
mlsBooleanAU = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AU", mlsMenuRP)
mlsBooleanAU.setLabel("AU915-928")
mlsBooleanAU.setVisible(True)
mlsBooleanAU.setDefaultValue(True)
mlsBooleanAU.setDescription("Enable support for AU915-928 region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_au_config.py")

# === AS923
global mlsBooleanAS
mlsBooleanAS = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_AS", mlsMenuRP)
mlsBooleanAS.setLabel("AS923")
mlsBooleanAS.setVisible(True)
mlsBooleanAS.setDefaultValue(True)
mlsBooleanAS.setDescription("Enable support for AS923 region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_as_config.py")

# === Japan 920.6-928 (AS923-1)
global mlsBooleanJP
mlsBooleanJP = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_JP", mlsMenuRP)
mlsBooleanJP.setLabel("AS923-1 (Japan)")
mlsBooleanJP.setVisible(True)
mlsBooleanJP.setDefaultValue(True)
mlsBooleanJP.setDescription("Enable support for Japan 920.6-928 (AS923-1) region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_jp_config.py")

# === KR920-923
global mlsBooleanKR
mlsBooleanKR = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_KR", mlsMenuRP)
mlsBooleanKR.setLabel("KR920-923")
mlsBooleanKR.setVisible(True)
mlsBooleanKR.setDefaultValue(True)
mlsBooleanKR.setDescription("Enable support for KR920-923 region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_kr_config.py")

# === IN865-867
global mlsBooleanIN
mlsBooleanIN = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_IN", mlsMenuRP)
mlsBooleanIN.setLabel("IN865-867")
mlsBooleanIN.setVisible(True)
mlsBooleanIN.setDefaultValue(True)
mlsBooleanIN.setDescription("Enable support for IN865-867 region")
execfile(Module.getPath() + "/driver/config/mhc_ui_regparams_in_config.py")

# === Random Network Acquisition
global mlsBooleanEnableRNA
mlsBooleanEnableRNA = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ENABLERNA", mlsMenuRP)
mlsBooleanEnableRNA.setLabel("Random NW Acquisition")
mlsBooleanEnableRNA.setVisible(True)
mlsBooleanEnableRNA.setDefaultValue(False)
mlsBooleanEnableRNA.setDescription("Enable random network acquisition for US902-928 and AU915-928 regions")

# === LBT scan retries
global mlsIntegerLbtScanRetries
mlsIntegerLbtScanRetries = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_LBTSCANRETRIES", mlsMenuRP)
mlsIntegerLbtScanRetries.setLabel("LBT Scan Retries")
mlsIntegerLbtScanRetries.setMin(0)
mlsIntegerLbtScanRetries.setMax(50)
mlsIntegerLbtScanRetries.setDefaultValue(2)
mlsIntegerLbtScanRetries.setDescription("Number of retries to scan channels for Listen-Before-Talk")
