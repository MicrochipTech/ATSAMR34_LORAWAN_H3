    /* Initialize delay routines */
    delay_init();
    /* Initialize the Radio Hardware */
    HAL_RadioInit();
    /* Initialize the Software Timer Module */
    SystemTimerInit();
#ifdef CONF_PMM_ENABLE
    /* Initialize the Sleep Timer Module */
    SleepTimerInit();
#endif
#if (ENABLE_PDS == 1)
    /* PDS Module Init */
    PDS_Init();
#endif
    /* Initializes the Security modules */
    if (SAL_SUCCESS != SAL_Init()) {
        /* Stop Further execution */
        while (1) {
        }
    }
    /* Initialize the scheduler */
    Stack_Init();
