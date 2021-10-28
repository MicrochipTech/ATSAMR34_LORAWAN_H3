# === SWTIMER Configuration
global mlsMenuSwtimer
mlsMenuSwtimer = MLS_SRC.createMenuSymbol("MLSSRC_MENU_SWTIMER", mlsMenuManualConf)
mlsMenuSwtimer.setLabel("SWTIMER Configuration")
mlsMenuSwtimer.setVisible(True)

global mlsIntegerSwtimerMaxTimers
mlsIntegerSwtimerMaxTimers = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_SWTIMERMAXTIMERS", mlsMenuSwtimer)
mlsIntegerSwtimerMaxTimers.setLabel("Max no. of SW timers")
mlsIntegerSwtimerMaxTimers.setMin(20)
mlsIntegerSwtimerMaxTimers.setMax(100)
mlsIntegerSwtimerMaxTimers.setDefaultValue(25)

global mlsCommentSwtimerMaxTimers
mlsCommentSwtimerMaxTimers = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_SWTIMERMAXTIMERS", mlsIntegerSwtimerMaxTimers)
mlsCommentSwtimerMaxTimers.setVisible(True)
timersTotalMem = 14 * mlsIntegerSwtimerMaxTimers.getValue()
mlsCommentSwtimerMaxTimers.setLabel("Memory occupied: ~%d bytes" %timersTotalMem)
mlsCommentSwtimerMaxTimers.setDependencies(mlsCommentSwtimerMaxTimersDepend, ["MLSSRC_INTEGER_SWTIMERMAXTIMERS"])

global mlsIntegerSwtimerMaxTimestamps
mlsIntegerSwtimerMaxTimestamps = MLS_SRC.createIntegerSymbol("MLSSRC_INTEGER_SWTIMERMAXTIMESTAMPS", mlsMenuSwtimer)
mlsIntegerSwtimerMaxTimestamps.setLabel("Max no. of SW timestamps")
mlsIntegerSwtimerMaxTimestamps.setMin(1)
mlsIntegerSwtimerMaxTimestamps.setMax(32)
mlsIntegerSwtimerMaxTimestamps.setDefaultValue(2)

global mlsCommentSwtimerMaxTimestamps
mlsCommentSwtimerMaxTimestamps = MLS_SRC.createCommentSymbol("MLSSRC_COMMENT_SWTIMERMAXTIMESTAMPS", mlsIntegerSwtimerMaxTimestamps)
mlsCommentSwtimerMaxTimestamps.setVisible(True)
timersTotalMem = 8 * mlsIntegerSwtimerMaxTimestamps.getValue()
mlsCommentSwtimerMaxTimestamps.setLabel("Memory occupied: %d bytes" %timersTotalMem)
mlsCommentSwtimerMaxTimestamps.setDependencies(mlsCommentSwtimerMaxTimestampsDepend, ["MLSSRC_INTEGER_SWTIMERMAXTIMESTAMPS"])
