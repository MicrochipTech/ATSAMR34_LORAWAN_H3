<#if HarmonyCore.SELECT_RTOS == "BareMetal">
    /* Call the MLS priority-based cooperative scheduler */
    SYSTEM_RunTasks();
</#if>
