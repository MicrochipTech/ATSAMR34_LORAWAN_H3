#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../stack/private/mac/lorawan.c ../../../stack/private/mac/lorawan_classc.c ../../../stack/private/mac/lorawan_init.c ../../../stack/private/mac/lorawan_mcast.c ../../../stack/private/mac/lorawan_pds.c ../../../stack/private/mac/lorawan_task_handler.c ../../../stack/private/tal/radio_get_set.c ../../../stack/private/tal/radio_interface.c ../../../stack/private/tal/radio_lbt.c ../../../stack/private/tal/radio_task_manager.c ../../../stack/private/tal/radio_transaction.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1017708749/lorawan.o ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o ${OBJECTDIR}/_ext/1017708749/lorawan_init.o ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o ${OBJECTDIR}/_ext/1017715485/radio_get_set.o ${OBJECTDIR}/_ext/1017715485/radio_interface.o ${OBJECTDIR}/_ext/1017715485/radio_lbt.o ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o ${OBJECTDIR}/_ext/1017715485/radio_transaction.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1017708749/lorawan.o.d ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o.d ${OBJECTDIR}/_ext/1017708749/lorawan_init.o.d ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o.d ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o.d ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o.d ${OBJECTDIR}/_ext/1017715485/radio_get_set.o.d ${OBJECTDIR}/_ext/1017715485/radio_interface.o.d ${OBJECTDIR}/_ext/1017715485/radio_lbt.o.d ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o.d ${OBJECTDIR}/_ext/1017715485/radio_transaction.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1017708749/lorawan.o ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o ${OBJECTDIR}/_ext/1017708749/lorawan_init.o ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o ${OBJECTDIR}/_ext/1017715485/radio_get_set.o ${OBJECTDIR}/_ext/1017715485/radio_interface.o ${OBJECTDIR}/_ext/1017715485/radio_lbt.o ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o ${OBJECTDIR}/_ext/1017715485/radio_transaction.o

# Source Files
SOURCEFILES=../../../stack/private/mac/lorawan.c ../../../stack/private/mac/lorawan_classc.c ../../../stack/private/mac/lorawan_init.c ../../../stack/private/mac/lorawan_mcast.c ../../../stack/private/mac/lorawan_pds.c ../../../stack/private/mac/lorawan_task_handler.c ../../../stack/private/tal/radio_get_set.c ../../../stack/private/tal/radio_interface.c ../../../stack/private/tal/radio_lbt.c ../../../stack/private/tal/radio_task_manager.c ../../../stack/private/tal/radio_transaction.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=ATSAMR34J18B
ProjectDir="D:\Harmony\v2.0.0\BitBucket\lorawan_h3_sources\driver\mls_libgen\firmware\mls_libgen_atsamr34.X"
ProjectName=mls_libgen_atsamr34
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [cp  ${ImagePath} ${ImageDir}\libmls_atsamr34.a]"
	@cp  ${ImagePath} ${ImageDir}\libmls_atsamr34.a
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATSAMR34J18B
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\ATSAMR34J18B.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1017708749/lorawan.o: ../../../stack/private/mac/lorawan.c  .generated_files/flags/default/11315340078ebdd0c01ff8f94f425bb9712eaa9c .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan.o ../../../stack/private/mac/lorawan.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_classc.o: ../../../stack/private/mac/lorawan_classc.c  .generated_files/flags/default/94217584d30fd6a7a609d65e4ae4a8672219e314 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_classc.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o ../../../stack/private/mac/lorawan_classc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_init.o: ../../../stack/private/mac/lorawan_init.c  .generated_files/flags/default/2744063097c8ac6fe6c162898e18fb713d88d6f3 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_init.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_init.o ../../../stack/private/mac/lorawan_init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o: ../../../stack/private/mac/lorawan_mcast.c  .generated_files/flags/default/e1441a96b2716af0ed7eb1fa60062e0a256661e8 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o ../../../stack/private/mac/lorawan_mcast.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_pds.o: ../../../stack/private/mac/lorawan_pds.c  .generated_files/flags/default/fa99bd8087c6f5579cedf782518175232f093b3d .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_pds.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o ../../../stack/private/mac/lorawan_pds.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o: ../../../stack/private/mac/lorawan_task_handler.c  .generated_files/flags/default/bd6888eb060d759fc10e77ada8b9312505fdd8b4 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o ../../../stack/private/mac/lorawan_task_handler.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_get_set.o: ../../../stack/private/tal/radio_get_set.c  .generated_files/flags/default/a3c31b40002e98e086d88979990c7b7e024d12df .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_get_set.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_get_set.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_get_set.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_get_set.o ../../../stack/private/tal/radio_get_set.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_interface.o: ../../../stack/private/tal/radio_interface.c  .generated_files/flags/default/7dca50bff1b0e1e223154217428164de21edf379 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_interface.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_interface.o ../../../stack/private/tal/radio_interface.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_lbt.o: ../../../stack/private/tal/radio_lbt.c  .generated_files/flags/default/5a1ff3c41b3b16665be1b3cc637d8f0eeabce75e .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_lbt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_lbt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_lbt.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_lbt.o ../../../stack/private/tal/radio_lbt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_task_manager.o: ../../../stack/private/tal/radio_task_manager.c  .generated_files/flags/default/a4822fd2499a99b07a1018f557ec652034df35e3 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_task_manager.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o ../../../stack/private/tal/radio_task_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_transaction.o: ../../../stack/private/tal/radio_transaction.c  .generated_files/flags/default/73dc1f411895bb90de158af40787ca7a3a7db81 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_transaction.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_transaction.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_transaction.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_transaction.o ../../../stack/private/tal/radio_transaction.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/1017708749/lorawan.o: ../../../stack/private/mac/lorawan.c  .generated_files/flags/default/4c27903afc2552e9058ae2778bca98b1911483a7 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan.o ../../../stack/private/mac/lorawan.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_classc.o: ../../../stack/private/mac/lorawan_classc.c  .generated_files/flags/default/604d880e3aba608b30eccb28f172d3ae75d95171 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_classc.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o ../../../stack/private/mac/lorawan_classc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_init.o: ../../../stack/private/mac/lorawan_init.c  .generated_files/flags/default/fe5f2a1ed1a96b2782568596e488af49507e7f4f .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_init.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_init.o ../../../stack/private/mac/lorawan_init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o: ../../../stack/private/mac/lorawan_mcast.c  .generated_files/flags/default/5f049baec5dc8545308490226feb9464b7c5a4f4 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o ../../../stack/private/mac/lorawan_mcast.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_pds.o: ../../../stack/private/mac/lorawan_pds.c  .generated_files/flags/default/63451c917ecf04b5b77e2f7b3a212d36c2e79cdf .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_pds.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o ../../../stack/private/mac/lorawan_pds.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o: ../../../stack/private/mac/lorawan_task_handler.c  .generated_files/flags/default/26e52e1602440c96a12d0b8062526df8f95a8fa2 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017708749" 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o.d" -o ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o ../../../stack/private/mac/lorawan_task_handler.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_get_set.o: ../../../stack/private/tal/radio_get_set.c  .generated_files/flags/default/8175cee3ba39c36671115a57c0720ade32b5c2b3 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_get_set.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_get_set.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_get_set.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_get_set.o ../../../stack/private/tal/radio_get_set.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_interface.o: ../../../stack/private/tal/radio_interface.c  .generated_files/flags/default/e59d236432488dbcf2192e87e378a6d72b26a763 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_interface.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_interface.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_interface.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_interface.o ../../../stack/private/tal/radio_interface.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_lbt.o: ../../../stack/private/tal/radio_lbt.c  .generated_files/flags/default/26967f8469563637869bd8b227502c7513435c5a .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_lbt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_lbt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_lbt.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_lbt.o ../../../stack/private/tal/radio_lbt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_task_manager.o: ../../../stack/private/tal/radio_task_manager.c  .generated_files/flags/default/e003c15baf6e072f60e8125ecbf0053864b4d281 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_task_manager.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o ../../../stack/private/tal/radio_task_manager.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1017715485/radio_transaction.o: ../../../stack/private/tal/radio_transaction.c  .generated_files/flags/default/148b60988dc7f1acfd1d5ccdbedc67b073e385a4 .generated_files/flags/default/f558a606006a75d8bb166323c5952bb768ccde2e
	@${MKDIR} "${OBJECTDIR}/_ext/1017715485" 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_transaction.o.d 
	@${RM} ${OBJECTDIR}/_ext/1017715485/radio_transaction.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -DENABLE_PDS=1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMR34J18B_DFP" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/" -I"../src" -I"../../../stack/common" -I"../../../stack/hal" -I"../../../stack/mac" -I"../../../stack/module_config" -I"../../../stack/pmm" -I"../../../stack/private" -I"../../../stack/sal" -I"../../../stack/regparams" -I"../../../stack/regparams/multiband" -I"../../../stack/sal" -I"../../../stack/services/aes/sw" -I"../../../stack/services/aes" -I"../../../stack/services/pds" -I"../../../stack/services/sw_timer" -I"../../../stack/sys" -I"../../../stack/tal" -I"../../../stack/tal/sx1276" -I"../../../stack/module_config" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1017715485/radio_transaction.o.d" -o ${OBJECTDIR}/_ext/1017715485/radio_transaction.o ../../../stack/private/tal/radio_transaction.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archiveChopped
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/ATSAMR34J18B.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  r dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}  ${OBJECTDIR}/_ext/1017708749/lorawan.o ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o ${OBJECTDIR}/_ext/1017708749/lorawan_init.o ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o ${OBJECTDIR}/_ext/1017715485/radio_get_set.o ${OBJECTDIR}/_ext/1017715485/radio_interface.o ${OBJECTDIR}/_ext/1017715485/radio_lbt.o ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o ${OBJECTDIR}/_ext/1017715485/radio_transaction.o 

	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/ATSAMR34J18B.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  r dist/${CND_CONF}/${IMAGE_TYPE}/mls_libgen_atsamr34.X.${OUTPUT_SUFFIX}  ${OBJECTDIR}/_ext/1017708749/lorawan.o ${OBJECTDIR}/_ext/1017708749/lorawan_classc.o ${OBJECTDIR}/_ext/1017708749/lorawan_init.o ${OBJECTDIR}/_ext/1017708749/lorawan_mcast.o ${OBJECTDIR}/_ext/1017708749/lorawan_pds.o ${OBJECTDIR}/_ext/1017708749/lorawan_task_handler.o ${OBJECTDIR}/_ext/1017715485/radio_get_set.o ${OBJECTDIR}/_ext/1017715485/radio_interface.o ${OBJECTDIR}/_ext/1017715485/radio_lbt.o ${OBJECTDIR}/_ext/1017715485/radio_task_manager.o ${OBJECTDIR}/_ext/1017715485/radio_transaction.o 

	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
