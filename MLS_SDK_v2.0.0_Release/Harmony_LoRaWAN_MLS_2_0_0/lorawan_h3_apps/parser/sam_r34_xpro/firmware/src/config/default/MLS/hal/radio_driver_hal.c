/**
* \file  radio_driver_hal.c
*
* \brief This is the Radio Driver HAL source file which 
*        contains LoRa-specific Radio Driver Hardware Abstract Layer
*		
*
*/
/*******************************************************************************
Copyright (C) 2020-21 released Microchip Technology Inc. and its subsidiaries. 

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR 
*******************************************************************************/

    
#include <stdbool.h>
#include "radio_driver_hal.h"
#include "sys.h"
#include "conf_pmm.h"
#ifdef CONF_PMM_ENABLE
#include "pmm.h"
#endif
#include "conf_radio.h"

/******************************************************************************/
/*  Defines                                                                   */
/******************************************************************************/
#ifndef RADIO_CLK_STABILITATION_DELAY
/* Delay in ms for Radio clock source to stabilize */
#define RADIO_CLK_STABILITATION_DELAY      0
#endif

#ifndef RADIO_CLK_SRC
/* Clock source for SX1276 radio */
#define RADIO_CLK_SRC                      XTAL
#endif

/*Enable the required DIO's*/
#define ENABLE_DIO0
#define ENABLE_DIO1
#define ENABLE_DIO2

/*** Macros for TCXO_PWR_PIN pin ***/
#define TCXO_PWR_PIN_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 9U))
#define TCXO_PWR_PIN_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 9U))
#define TCXO_PWR_PIN_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 9U))
#define TCXO_PWR_PIN_OutputEnable()      (PORT_REGS->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 9U))
#define TCXO_PWR_PIN_InputEnable()       (PORT_REGS->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 9U))
#define TCXO_PWR_PIN_Get()               (((PORT_REGS->GROUP[0].PORT_IN >> 9U)) & 0x01U)
#define TCXO_PWR_PIN_PIN                  PORT_PIN_PA09

/*** Macros for RF_SWITCH_PIN pin ***/
#define RF_SWITCH_PIN_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 13U))
#define RF_SWITCH_PIN_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 13U))
#define RF_SWITCH_PIN_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 13U))
#define RF_SWITCH_PIN_OutputEnable()      (PORT_REGS->GROUP[0].PORT_DIRSET = ((uint32_t)1U << 13U))
#define RF_SWITCH_PIN_InputEnable()       (PORT_REGS->GROUP[0].PORT_DIRCLR = ((uint32_t)1U << 13U))
#define RF_SWITCH_PIN_Get()               (((PORT_REGS->GROUP[0].PORT_IN >> 13U)) & 0x01U)
#define RF_SWITCH_PIN_PIN                  PORT_PIN_PA13

/*** Macros for DIO0_EIC_PIN pin ***/
#define DIO0_EIC_PIN_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 16U)) & 0x01U)
#define DIO0_EIC_PIN_PIN                  PORT_PIN_PB16

/*** Macros for DIO1_EIC_PIN pin ***/
#define DIO1_EIC_PIN_Get()               (((PORT_REGS->GROUP[0].PORT_IN >> 11U)) & 0x01U)
#define DIO1_EIC_PIN_PIN                  PORT_PIN_PA11

/*** Macros for DIO2_EIC_PIN pin ***/
#define DIO2_EIC_PIN_Get()               (((PORT_REGS->GROUP[0].PORT_IN >> 12U)) & 0x01U)
#define DIO2_EIC_PIN_PIN                  PORT_PIN_PA12

/*** Macros for DIO3_EIC_PIN pin ***/
#define DIO3_EIC_PIN_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 17U)) & 0x01U)
#define DIO3_EIC_PIN_PIN                  PORT_PIN_PB17

/*** Macros for DIO4_EIC_PIN pin ***/
#define DIO4_EIC_PIN_Get()               (((PORT_REGS->GROUP[0].PORT_IN >> 10U)) & 0x01U)
#define DIO4_EIC_PIN_PIN                  PORT_PIN_PA10

/*** Macros for SX_RF_SPI_MISO pin ***/
#define SX_RF_SPI_MISO_Set()               (PORT_REGS->GROUP[2].PORT_OUTSET = ((uint32_t)1U << 19U))
#define SX_RF_SPI_MISO_Clear()             (PORT_REGS->GROUP[2].PORT_OUTCLR = ((uint32_t)1U << 19U))
#define SX_RF_SPI_MISO_Toggle()            (PORT_REGS->GROUP[2].PORT_OUTTGL = ((uint32_t)1U << 19U))
#define SX_RF_SPI_MISO_OutputEnable()      (PORT_REGS->GROUP[2].PORT_DIRSET = ((uint32_t)1U << 19U))
#define SX_RF_SPI_MISO_InputEnable()       (PORT_REGS->GROUP[2].PORT_DIRCLR = ((uint32_t)1U << 19U))
#define SX_RF_SPI_MISO_Get()               (((PORT_REGS->GROUP[2].PORT_IN >> 19U)) & 0x01U)
#define SX_RF_SPI_MISO_PIN                  PORT_PIN_PC19

/*** Macros for SX_RF_SPI_MOSI pin ***/
#define SX_RF_SPI_MOSI_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 30U))
#define SX_RF_SPI_MOSI_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 30U))
#define SX_RF_SPI_MOSI_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 30U))
#define SX_RF_SPI_MOSI_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 30U))
#define SX_RF_SPI_MOSI_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 30U))
#define SX_RF_SPI_MOSI_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 30U)) & 0x01U)
#define SX_RF_SPI_MOSI_PIN                  PORT_PIN_PB30

/*** Macros for SX_RF_RESET_PIN pin ***/
#define SX_RF_RESET_PIN_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 15U))
#define SX_RF_RESET_PIN_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 15U))
#define SX_RF_RESET_PIN_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 15U))
#define SX_RF_RESET_PIN_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 15U))
#define SX_RF_RESET_PIN_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 15U))
#define SX_RF_RESET_PIN_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 15U)) & 0x01U)
#define SX_RF_RESET_PIN_PIN                  PORT_PIN_PB15

/*** Macros for SX_RF_SPI_CS pin ***/
#define SX_RF_SPI_CS_Set()               (PORT_REGS->GROUP[1].PORT_OUTSET = ((uint32_t)1U << 31U))
#define SX_RF_SPI_CS_Clear()             (PORT_REGS->GROUP[1].PORT_OUTCLR = ((uint32_t)1U << 31U))
#define SX_RF_SPI_CS_Toggle()            (PORT_REGS->GROUP[1].PORT_OUTTGL = ((uint32_t)1U << 31U))
#define SX_RF_SPI_CS_OutputEnable()      (PORT_REGS->GROUP[1].PORT_DIRSET = ((uint32_t)1U << 31U))
#define SX_RF_SPI_CS_InputEnable()       (PORT_REGS->GROUP[1].PORT_DIRCLR = ((uint32_t)1U << 31U))
#define SX_RF_SPI_CS_Get()               (((PORT_REGS->GROUP[1].PORT_IN >> 31U)) & 0x01U)
#define SX_RF_SPI_CS_PIN                  PORT_PIN_PB31

/*** Macros for SX_RF_SPI_SCK pin ***/
#define SX_RF_SPI_SCK_Set()               (PORT_REGS->GROUP[2].PORT_OUTSET = ((uint32_t)1U << 18U))
#define SX_RF_SPI_SCK_Clear()             (PORT_REGS->GROUP[2].PORT_OUTCLR = ((uint32_t)1U << 18U))
#define SX_RF_SPI_SCK_Toggle()            (PORT_REGS->GROUP[2].PORT_OUTTGL = ((uint32_t)1U << 18U))
#define SX_RF_SPI_SCK_OutputEnable()      (PORT_REGS->GROUP[2].PORT_DIRSET = ((uint32_t)1U << 18U))
#define SX_RF_SPI_SCK_InputEnable()       (PORT_REGS->GROUP[2].PORT_DIRCLR = ((uint32_t)1U << 18U))
#define SX_RF_SPI_SCK_Get()               (((PORT_REGS->GROUP[2].PORT_IN >> 18U)) & 0x01U)
#define SX_RF_SPI_SCK_PIN                  PORT_PIN_PC18


/*************************************** RADIO Callbacks***********************/
#ifdef ENABLE_DIO0
static DioInterruptHandler_t interruptHandlerDio0 = NULL;
#endif

#ifdef ENABLE_DIO1
static DioInterruptHandler_t interruptHandlerDio1 = NULL;
#endif

#ifdef ENABLE_DIO2
static DioInterruptHandler_t interruptHandlerDio2 = NULL;
#endif

#ifdef ENABLE_DIO3
static DioInterruptHandler_t interruptHandlerDio3 = NULL;
#endif

#ifdef ENABLE_DIO4
static DioInterruptHandler_t interruptHandlerDio4 = NULL;
#endif

#ifdef ENABLE_DIO5
static DioInterruptHandler_t interruptHandlerDio5 = NULL;
#endif

/*************************************** Prototypes ***************************/

/*
 * \brief Initializes the Radio SPI Interface
 */
static void HAL_RadioSpiInit(void);

/*
 * \brief Initializes the Radio Digital IO's,Reset Pins
 */ 
static void HAL_RadioIOInit(void);

/*
 * \brief The below functions are callbacks for the TRX DIO interrupts
 */
#ifdef ENABLE_DIO0
static void HAL_RadioDIO0Callback(void);
#endif
#ifdef ENABLE_DIO1
static void HAL_RadioDIO1Callback(void);
#endif
#ifdef ENABLE_DIO2
static void HAL_RadioDIO2Callback(void);
#endif
#ifdef ENABLE_DIO3
static void HAL_RadioDIO3Callback(void);
#endif
#ifdef ENABLE_DIO4
static void HAL_RadioDIO4Callback(void);
#endif
#ifdef ENABLE_DIO5
static void HAL_RadioDIO5Callback(void);
#endif

/*
 * \brief This function is used to make the Reset Pin as Output Pin
 */
static void HAL_ResetPinMakeOutput(void);


/*
 * \brief This function is used to make the Reset Pin as Input Pin
 */
static void HAL_ResetPinMakeInput(void);


/*
 * \brief This function is used to set/clear the Radio Reset Pin
 * \param[in] value Set/Clear the Radio Reset pin 
 */
static void HAL_ResetPinOutputValue(uint8_t value);


/*
 * \brief This function is used to write a byte of data to the SPI DATA register
 * \param[in] data Byte of data to be written into the SPI DATA register
 */
static uint8_t HAL_SPISend(uint8_t data);

/*
 * \brief This function is called to select a SPI slave
 */
static void HAL_SPICSAssert(void);

/*
 * \brief This function is called to deselect a SPI slave
 */
static void HAL_SPICSDeassert(void);

/***************************************** GLOBALS ***************************/
static uint8_t dioStatus;	

/*********************************** Implementation***************************/
/*
 * \brief These functions are temporarily placed here 
 */
static inline void spi_enable(void)
{

	while(SERCOM4_REGS->SPIM.SERCOM_SYNCBUSY)
    {
        
    }

	/* Enable SPI */
	SERCOM4_REGS->SPIM.SERCOM_CTRLA |= SERCOM_SPIM_CTRLA_ENABLE_Msk;
}
/**
 * \brief Disables the SERCOM SPI module
 *
 * This function will disable the SERCOM SPI module.
 *
 * \param[in,out] module  Pointer to the software instance struct
 */
static inline void spi_disable(void)
{
	while(SERCOM4_REGS->SPIM.SERCOM_SYNCBUSY)
    {
        
    }
    /* Wait until the synchronization is complete */
	/* Disable interrupt */
	SERCOM4_REGS->SPIM.SERCOM_INTENCLR = SERCOM_SPIM_INTENCLR_Msk;
	/* Clear interrupt flag */
	SERCOM4_REGS->SPIM.SERCOM_INTFLAG = SERCOM_SPIM_INTFLAG_Msk;
    while(SERCOM4_REGS->SPIM.SERCOM_SYNCBUSY)
    {
        
    }

	/* Disable SPI */
	SERCOM4_REGS->SPIM.SERCOM_CTRLA &= ~(SERCOM_SPIM_CTRLA_ENABLE_Msk);
    while(SERCOM4_REGS->SPIM.SERCOM_SYNCBUSY)
    {
        
    }
}

static void spi_select_slave(bool select)
{
    if(select){
     SX_RF_SPI_CS_Clear();
    }
    else{
        SX_RF_SPI_CS_Set();
    }
 
}
/********************************************************************************/
/** 
 * \brief This function is used to initialize the Radio Hardware
 * The SPI interface,DIO and reset pins are initialized by this api
 */
void HAL_RadioInit(void)
{
	HAL_RadioIOInit();
	HAL_RadioSpiInit();
}
/**
 * \brief This function is used to initialize the SPI Interface after PMM wakeup
 *
 */
void HAL_Radio_resources_init(void)
{
	spi_enable();
	while (SERCOM4_REGS->SPIM.SERCOM_SYNCBUSY) {
		/* Wait until the synchronization is complete */
	}
}
/**
 * \brief This function is used to deinitialize the SPI Interface
 */
void HAL_RadioDeInit(void)
{
	spi_disable();
}
 
/** 
 * \brief This function resets the Radio hardware by pulling the reset pin low
 */
void RADIO_Reset(void)
{
    HAL_ResetPinMakeOutput();
    /* Pull down the RF_NRST pin */
    HAL_ResetPinOutputValue(0);
    /* Hold for 100us */
    delay_us(100);
    /* Release the RF_NRST pin */
    HAL_ResetPinMakeInput();
    /* Wait for 5ms */
    delay_ms(5);
    /* Make sure this pin is not floating */
    HAL_ResetPinOutputValue(1);
}

/** 
 * \brief This function is used to write a byte of data to the radio register
 * \param[in] reg Radio register to be written
 * \param[in] value Value to be written into the radio register
 */
void RADIO_RegisterWrite(uint8_t reg, uint8_t value)
{
	HAL_SPICSAssert();
	HAL_SPISend(REG_WRITE_CMD | reg);
	HAL_SPISend(value);
	HAL_SPICSDeassert();
}

/** 
 * \brief This function is used to read a byte of data from the radio register
 * \param[in] reg Radio register to be read
 * \retval  Value read from the radio register
 */
uint8_t RADIO_RegisterRead(uint8_t reg)
{
	uint8_t readValue;
	reg &= 0x7F;    // Make sure write bit is not set
	HAL_SPICSAssert();
	HAL_SPISend(reg);
	readValue = HAL_SPISend(0xFF);
	HAL_SPICSDeassert();
	return readValue;
}

/** 
 * \brief This function is used to  write a stream of data into the Radio Frame buffer
 * \param[in] FIFO offset to be written to
 * \param[in] buffer Pointer to the data to be written into the frame buffer
 * \param[in] bufferLen Length of the data to be written
 */
void RADIO_FrameWrite(uint8_t offset, uint8_t* buffer, uint8_t bufferLen)
{
    HAL_SPICSAssert();
    HAL_SPISend(REG_WRITE_CMD | offset);

    for (uint8_t i = 0; i < bufferLen; i++)
    {
	    HAL_SPISend(buffer[i]);
    }
    HAL_SPICSDeassert();

}

/** 
 * \brief This function is used to  read a stream of data from the Radio Frame buffer
 * \param[in] FIFO offset to be read from
 * \param[in] buffer Pointer to the data where the data is read and stored
 * \param[in] bufferLen Length of the data to be read from the frame buffer
 */
void RADIO_FrameRead(uint8_t offset, uint8_t* buffer, uint8_t bufferLen)
{
    HAL_SPICSAssert();
    HAL_SPISend(offset);
    for (uint8_t i = 0; i < bufferLen; i++)
    {
	    buffer[i] = HAL_SPISend(0xFF);
    }
    HAL_SPICSDeassert();
}


#ifdef ENABLE_DIO0
/** 
 * \brief This function is used to enable DIO0 interrupt
 */
void HAL_EnableDIO0Interrupt(void)
{
     EIC_InterruptEnable(EIC_PIN_0);
}

/** 
 * \brief This function is used to disable DIO0 interrupt
 */
void HAL_DisbleDIO0Interrupt(void)
{
     EIC_InterruptDisable(EIC_PIN_0);
}

/** 
 * \brief This function is used to read the status of  DIO0 pin
 */
uint8_t HAL_DIO0PinValue(void)
{
    return DIO0_EIC_PIN_Get();
}

static void HAL_RadioDIO0Callback(void)
{
  if (interruptHandlerDio0)
  {
#ifdef CONF_PMM_ENABLE
	PMM_Wakeup(0xFFFFFFFF, (uintptr_t)NULL);
#endif	
    interruptHandlerDio0();
  }    
}
#endif

#ifdef ENABLE_DIO1

/** 
 * \brief This function is used to enable DIO1 interrupt
 */
void HAL_EnableDIO1Interrupt(void)
{
    EIC_InterruptEnable(EIC_PIN_11);
}

/** 
 * \brief This function is used to disable DIO2 interrupt
 */
void HAL_DisbleDIO1Interrupt(void)
{
    EIC_InterruptDisable(EIC_PIN_11);
}
/** 
 * \brief This function is used to read the status of  DIO1 pin
 */
uint8_t HAL_DIO1PinValue(void)
{
    return DIO1_EIC_PIN_Get();
}

static void HAL_RadioDIO1Callback(void)
{
  if (interruptHandlerDio1)
  {
#ifdef CONF_PMM_ENABLE
	PMM_Wakeup(0xFFFFFFFF, (uintptr_t)NULL);
#endif
    interruptHandlerDio1();
  }
}
#endif

#ifdef ENABLE_DIO2

/** 
 * \brief This function is used to enable DIO2 interrupt
 */
void HAL_EnableDIO2Interrupt(void)
{
    EIC_InterruptEnable(EIC_PIN_12);
}
/** 
 * \brief This function is used to disable DIO2 interrupt
 */
void HAL_DisbleDIO2Interrupt(void)
{
     EIC_InterruptDisable(EIC_PIN_12);
}
/** 
 * \brief This function is used to read the status of  DIO2 pin
 */
uint8_t HAL_DIO2PinValue(void)
{
    return DIO2_EIC_PIN_Get();
}

static void HAL_RadioDIO2Callback(void)
{
  if (interruptHandlerDio2)
  {
#ifdef CONF_PMM_ENABLE
	PMM_Wakeup(0xFFFFFFFF, (uintptr_t)NULL);
#endif
    interruptHandlerDio2();
  }
}

#endif

#ifdef ENABLE_DIO3

/** 
 * \brief This function is used to enable DIO3 interrupt
 */
void HAL_EnableDIO3Interrupt(void)
{
    EIC_InterruptEnable(EIC_PIN_1);
}
/** 
 * \brief This function is used to disable DIO3 interrupt
 */
void HAL_DisbleDIO3Interrupt(void)
{
    EIC_InterruptDisable(EIC_PIN_1);
}
/** 
 * \brief This function is used to read the status of  DIO3 pin
 */
uint8_t HAL_DIO3PinValue(void)
{
    return DIO3_EIC_PIN_Get();
}

static void HAL_RadioDIO3Callback(void)
{
  if (interruptHandlerDio3)
  {
#ifdef CONF_PMM_ENABLE
	PMM_Wakeup();
#endif
    interruptHandlerDio3();
  }
}
#endif

#ifdef ENABLE_DIO4
/** 
 * \brief This function is used to enable DIO4 interrupt
 */
void HAL_EnableDIO4Interrupt(void)
{
    EIC_InterruptEnable(EIC_PIN_10);
}
/** 
 * \brief This function is used to disable DIO4 interrupt
 */
void HAL_DisbleDIO4Interrupt(void)
{
    EIC_InterruptDisable(EIC_PIN_10);
}

/** 
 * \brief This function is used to read the status of  DIO4 pin
 */
uint8_t HAL_DIO4PinValue(void)
{
    return DIO4_EIC_PIN_Get();
}

static void HAL_RadioDIO4Callback(void)
{
  if (interruptHandlerDio4)
  {
#ifdef CONF_PMM_ENABLE
	PMM_Wakeup(0xFFFFFFFF, (uintptr_t)NULL);
#endif
    interruptHandlerDio4();
  }
}
#endif

#ifdef ENABLE_DIO5

/** 
 * \brief This function is used to enable DIO5 interrupt
 */
void HAL_EnableDIO5Interrupt(void)
{
    EIC_InterruptEnable(EIC_PIN_0);
}
/** 
 * \brief This function is used to disable DIO5 interrupt
 */
void HAL_DisbleDIO5Interrupt(void)
{
    EIC_InterruptDisable(EIC_PIN_0);
}

static void HAL_RadioDIO5Callback(void)
{
  if (interruptHandlerDio5)
  {
#ifdef CONF_PMM_ENABLE
	PMM_Wakeup(0xFFFFFFFF, (uintptr_t)NULL);
#endif
    interruptHandlerDio5();
  }
}
/** 
 * \brief This function is used to read the status of  DIO5 pin
 */
uint8_t HAL_DIO5PinValue(void)
{
    return PORT_PinRead(PORT_PIN_PB00);
}
#endif

/** 
 * \brief This function is used to get the interrupt status
 * The interrupt status is cleared after calling this function
 * \retval Returns the mask of received interrupts
 */
uint8_t INTERRUPT_GetDioStatus(void)
{
	uint8_t a;
	INTERRUPT_GlobalInterruptDisable();
	a = dioStatus;
	dioStatus = 0;
	INTERRUPT_GlobalInterruptEnable();
	return a;
}

/** 
 * \brief This function is used to get the interrupt status
 * The interrupt status is not cleared after calling this function 
 * \retval Returns the mask of received interrupts
 */
uint8_t INTERRUPT_PeekDioStatus(void)
{
	return dioStatus;
}

/*
 * \brief Initializes the Radio SPI Interface
 */
void HAL_RadioSpiInit(void)
{
    /*SPI initializations are done inside plib_sercom4_spi_master.h */
    SX_RF_SPI_CS_Set();
    
            
    /* PC18 - SCK  - O - SERCOM4_PAD_3 */
    /* PC19 - MISO - I - SERCOM4_PAD_0 */
    PORT_REGS->GROUP[2].PORT_PINCFG[18] = 0x01;
    PORT_REGS->GROUP[2].PORT_PINCFG[19] = 0x01;
    PORT_REGS->GROUP[2].PORT_PMUX[9] = 0x55;
    /* PB30 - MOSI - O - SERCOM4_PAD_2 */
    PORT_REGS->GROUP[1].PORT_PINCFG[30] = 0x01;
    PORT_REGS->GROUP[1].PORT_PMUX[15] |= 0x05;
}


/*
 * \brief Initializes the Radio Digital IO's,Reset Pins
 */ 
static void HAL_RadioIOInit(void)
{
    uint32_t reg;
    
    PORT_REGS->GROUP[0].PORT_PINCFG[10] = 0x3;
    PORT_REGS->GROUP[0].PORT_PINCFG[11] = 0x3;
    
    reg = (0xc0008000 | PORT_REGS->GROUP[1].PORT_DIR);
    PORT_REGS->GROUP[1].PORT_DIR = reg;
    reg = (0x80008000 | PORT_REGS->GROUP[1].PORT_OUT);
    PORT_REGS->GROUP[1].PORT_OUT = reg;
    
    PORT_REGS->GROUP[1].PORT_PINCFG[16] = 0x3;
    PORT_REGS->GROUP[1].PORT_PINCFG[17] = 0x3;
    
    SX_RF_SPI_SCK_OutputEnable();
    SX_RF_SPI_SCK_Set();
    SX_RF_SPI_MOSI_OutputEnable();
    SX_RF_SPI_MOSI_Set();
    SX_RF_SPI_CS_OutputEnable();
    SX_RF_SPI_CS_Set();
    SX_RF_RESET_PIN_OutputEnable();
    SX_RF_RESET_PIN_Set();
    SX_RF_SPI_MISO_InputEnable();
#ifdef RFSWITCH_ENABLE
    RF_SWITCH_PIN_OutputEnable();
    RF_SWITCH_PIN_Clear();
#endif
    
#ifdef TCXO_ENABLE
    TCXO_PWR_PIN_OutputEnable();
    TCXO_PWR_PIN_Clear();
#endif
    
#ifdef ENABLE_DIO0
    EIC_CallbackRegister(EIC_PIN_0, (EIC_CALLBACK)HAL_RadioDIO0Callback, (uintptr_t)NULL);
	EIC_InterruptEnable(EIC_PIN_0);
#endif

#ifdef ENABLE_DIO1
    EIC_CallbackRegister(EIC_PIN_11, (EIC_CALLBACK)HAL_RadioDIO1Callback, (uintptr_t)NULL);
	EIC_InterruptEnable(EIC_PIN_11);
#endif

#ifdef ENABLE_DIO2
    EIC_CallbackRegister(EIC_PIN_12, (EIC_CALLBACK)HAL_RadioDIO2Callback, (uintptr_t)NULL);
	EIC_InterruptEnable(EIC_PIN_12);
#endif

#ifdef ENABLE_DIO3
    EIC_CallbackRegister(EIC_PIN_1, (EIC_CALLBACK)HAL_RadioDIO3Callback, (uintptr_t)NULL);
	EIC_InterruptEnable(EIC_PIN_1);
#endif

#ifdef ENABLE_DIO4
    EIC_CallbackRegister(EIC_PIN_10, (EIC_CALLBACK)HAL_RadioDIO4Callback, (uintptr_t)NULL);
	EIC_InterruptEnable(EIC_PIN_10);
#endif

#ifdef ENABLE_DIO5
    EIC_CallbackRegister(EIC_PIN_0, (EIC_CALLBACK)HAL_RadioDIO5Callback, (uintptr_t)NULL);
	EIC_InterruptEnable(EIC_PIN_0);
#endif
}


/*
 * \brief This function is used to make the Reset Pin as Output Pin
 */

static void HAL_ResetPinMakeOutput(void)
{
    SX_RF_RESET_PIN_OutputEnable();
}
/*
 * \brief This function is used to make the Reset Pin as Input Pin
 */
static void HAL_ResetPinMakeInput(void)
{
    SX_RF_RESET_PIN_InputEnable();
}

/*
 * \brief This function is used to set/clear the Radio Reset Pin
 * \param[in] value Set/Clear the Radio Reset pin 
 */
static void HAL_ResetPinOutputValue(uint8_t value)
{
	if (value == 0)
	{
        SX_RF_RESET_PIN_Clear();
	}
	else if (value == 1)
	{
        SX_RF_RESET_PIN_Set();
	}
}
/*
 * \brief This function is called to select a SPI slave
 */
static void HAL_SPICSAssert(void)
{
	spi_select_slave(1);
}

/*
 * \brief This function is called to deselect a SPI slave
 */
static void HAL_SPICSDeassert(void)
{
	spi_select_slave(0);
}

/*
 * \brief This function is used to write a byte of data to the SPI DATA register
 * \param[in] data Byte of data to be written into the SPI DATA register
 */
static uint8_t HAL_SPISend(uint8_t data)
{
	uint16_t read_val = 0;
	
    SERCOM4_SPI_WriteRead(&data, 1, &read_val, 1);
	
	return ((uint8_t)read_val);
}

/**
 * \brief This function sets the interrupt handler for given DIO interrupt
 *
 * \param[in] dioPin  - DIO pin
 * \param[in] handler - function to be called upon given DIO interrupt
 */
void HAL_RegisterDioInterruptHandler(uint8_t dioPin, DioInterruptHandler_t handler)
{
  switch (dioPin)
  {
#ifdef ENABLE_DIO0
    case DIO0:
      interruptHandlerDio0 = handler;
      break;
#endif

#ifdef ENABLE_DIO1
    case DIO1:
      interruptHandlerDio1 = handler;
      break;
#endif

#ifdef ENABLE_DIO2
    case DIO2:
      interruptHandlerDio2 = handler;
      break;
#endif

#ifdef ENABLE_DIO3
    case DIO3:
      interruptHandlerDio3 = handler;
      break;
#endif

#ifdef ENABLE_DIO4
    case DIO4:
      interruptHandlerDio4 = handler;
      break;
#endif

#ifdef ENABLE_DIO5
    case DIO5:
      interruptHandlerDio5 = handler;
      break;
#endif

    default:
      break;
  }
}


/**
 * \brief This function Enables RF Control pins
 *
 * \param[in] RFCtrl1
 * 				RFO_LF = 0
 *				RFO_HF = 1
 *				PA_BOOST = 2
 * \param[in] RFCtrl2
 *				RX = 0
 *				TX = 1 
 * \param[out] None
 */

void HAL_EnableRFCtrl(RFCtrl1_t RFCtrl1, RFCtrl2_t RFCtrl2)
{
	/* In standard SAMR34_XPRO, Only RFO_HF and PA_BOOST needs to be controlled by a GPIO pin */
#ifdef RFSWITCH_ENABLE
   if ((RFCtrl1 == RFO_HF) || (RFCtrl2 == RX))
   {
        RF_SWITCH_PIN_Set();
   }
   else if ((RFCtrl1 == PA_BOOST) && (RFCtrl2 == TX))
   {
       RF_SWITCH_PIN_Clear();
   }
#endif	
}

/**
 * \brief This function Disables RF Control pins
 *
 * \param[in] RFCtrl1
 * 				RFO_LF = 0
 *				RFO_HF = 1
 *				PA_BOOST = 2
 * \param[in] RFCtrl2
 *				RX = 0
 *				TX = 1 
 * \param[out] None
 */

void HAL_DisableRFCtrl(RFCtrl1_t RFCtrl1, RFCtrl2_t RFCtrl2)
{
	/* In standard SAMR34_XPRO, Only RFO_HF and PA_BOOST needs to be controlled by a GPIO pin */
#ifdef RFSWITCH_ENABLE
	if ((RFCtrl1 == RFO_HF) || (RFCtrl2 == RX))
	{
        RF_SWITCH_PIN_Clear();
	}
#endif	
}

/**
 * \brief This function gets the time taken for the radio clock to stabilize
 *
 * \param[in] None
 * \param[out] Time value in ms
 */
uint8_t HAL_GetRadioClkStabilizationDelay(void)
{
	return RADIO_CLK_STABILITATION_DELAY;
}

/**
 * \brief This function gets the clock source of Radio defined by user
 *
 * \param[in] None
 * \param[out] Type of clock source TCXO or XTAL
 */
RadioClockSources_t HAL_GetRadioClkSrc(void)
{
	return RADIO_CLK_SRC;
}

/**
 * \brief This function Powering up the TCXO oscillator
 *
 * \param[in] None
 * \param[out] None
 */
void HAL_TCXOPowerOn(void)
{
#ifdef TCXO_ENABLE
	delay_ms(RADIO_CLK_STABILITATION_DELAY);
    TCXO_PWR_PIN_Set();
#endif
}

/**
 * \brief This function Powering off the TCXO oscillator
 *
 * \param[in] None
 * \param[out] None
 */
void HAL_TCXOPowerOff(void)
{
#ifdef TCXO_ENABLE
#ifndef TCXO_ALWAYS_ON
    TCXO_PWR_PIN_Clear();
#endif
#endif
}


/**
 End of File
*/
