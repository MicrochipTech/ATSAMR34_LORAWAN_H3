/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
#pragma config NVMCTRL_BOOTPROT = 0x7
#pragma config NVMCTRL_EEPROM_SIZE = 0x7
#pragma config BOD33USERLEVEL = 0x6
#pragma config BOD33_DIS = CLEAR
#pragma config BOD33_ACTION = 0x0
#pragma config WDT_ENABLE = CLEAR
#pragma config WDT_ALWAYSON = CLEAR
#pragma config WDT_PER = 0xB
#pragma config WDT_WINDOW = 0xB
#pragma config WDT_EWOFFSET = 0xB
#pragma config WDT_WEN = CLEAR
#pragma config BOD33_HYST = CLEAR
#pragma config NVMCTRL_REGION_LOCKS = 0xffff




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void STDIO_BufferModeSet ( void )

  Summary:
    Sets the buffering mode for stdin and stdout

  Remarks:
 ********************************************************************************/
static void STDIO_BufferModeSet(void)
{

    /* Make stdin unbuffered */
    setbuf(stdin, NULL);

    /* Make stdout unbuffered */
    setbuf(stdout, NULL);
}




/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{

    NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(3UL);

    PM_Initialize();

    STDIO_BufferModeSet();


  
    PORT_Initialize();


    CLOCK_Initialize();




    NVMCTRL_Initialize( );

    SERCOM1_I2C_Initialize();

    EVSYS_Initialize();

    SERCOM0_USART_Initialize();

	SYSTICK_TimerInitialize();
    SERCOM4_SPI_Initialize();


    ADC_Initialize();
    SUPC_Initialize();

    EIC_Initialize();

    RTC_Initialize();

    TC0_CompareInitialize();

	RSTC_Initialize();

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



    CRYPT_WCCB_Initialize();

    APP_Initialize();


    NVIC_Initialize();

}


/*******************************************************************************
 End of File
*/
