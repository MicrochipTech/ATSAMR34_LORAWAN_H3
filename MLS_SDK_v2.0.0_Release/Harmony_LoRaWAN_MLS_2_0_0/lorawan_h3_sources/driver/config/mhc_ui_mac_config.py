# === MAC Configuration
global mlsMenuMac
mlsMenuMac = MLS_SRC.createMenuSymbol("MLSSRC_MENU_MAC", None)
mlsMenuMac.setLabel("MAC Configuration")
mlsMenuMac.setVisible(True)

global mlsBooleanEnableClassC
mlsBooleanEnableClassC = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ENABLECLASSC", mlsMenuMac)
mlsBooleanEnableClassC.setLabel("Enable Class C")
mlsBooleanEnableClassC.setVisible(True)
mlsBooleanEnableClassC.setDefaultValue(False)
mlsBooleanEnableClassC.setDescription("Enable/disable class C option")

global mlsCommentEnableClassC
mlsCommentEnableClassC = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_ENABLECLASSC", mlsBooleanEnableClassC)
mlsCommentEnableClassC.setVisible(True)
mlsCommentEnableClassC.setLabel("*** Class-A is always enabled ***")
mlsCommentEnableClassC.setDependencies(mlsCommentEnableClassCDepend, ["MLSSRC_BOOLEAN_ENABLECLASSC"])

# global mlsBooleanEnablePds
mlsBooleanEnablePds = MLS_SRC.createBooleanSymbol("MLSSRC_BOOLEAN_ENABLEPDS", mlsMenuMac)
mlsBooleanEnablePds.setLabel("Enable Persistent Data (PDS)")
mlsBooleanEnablePds.setVisible(True)
mlsBooleanEnablePds.setDefaultValue(True)
mlsBooleanEnablePds.setDescription("Enable/disable MAC Persistent Storage")

global mlsCommentEnablePds
mlsCommentEnablePds = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_ENABLEPDS", mlsBooleanEnablePds)
mlsCommentEnablePds.setVisible(False)
mlsCommentEnablePds.setDependencies(mlsCommentEnablePdsDepend, ["MLSSRC_BOOLEAN_ENABLEPDS"])
