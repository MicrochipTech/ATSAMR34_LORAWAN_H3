/**
* \file  lorawan_init.c
*
* \brief LoRaWAN Initialization file
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


 

/****************************** INCLUDES **************************************/

#include "sw_timer.h"
#include "lorawan_defs.h"
#include "lorawan_init.h"

/*
void DIO0_ISR_Lora_Init(void);
void DIO1_ISR_Lora_Init(void);
void DI02_ISR_Lora_Init(void);
void DIO4_ISR_Lora_Init(void);
void DIO5_ISR_Lora_Init(void);

void DIO0_ISR_Lora_Init(void)
{
    INT1_SetInterruptHandler(DIO0_ISR_Lora);
}

void DIO1_ISR_Lora_Init(void)
{
    INT2_SetInterruptHandler(DIO1_ISR_Lora);
}

void DIO2_ISR_Lora_Init(void)
{
    IOCB4_SetInterruptHandler(DIO2_ISR_Lora);
}

void DIO3_ISR_Lora_Init(void)
{
}

void DIO4_ISR_Lora_Init(void)
{
    IOCB5_SetInterruptHandler(DIO4_ISR_Lora);
}

void DIO5_ISR_Lora_Init(void)
{
    INT0_SetInterruptHandler(DIO5_ISR_Lora);
}*/

void LORAWAN_PlatformInit(void)
{
/*
    TMR_ISR_Lora_Init();
    DIO0_ISR_Lora_Init();
    DIO1_ISR_Lora_Init();
    DIO2_ISR_Lora_Init();
    DIO3_ISR_Lora_Init();
    DIO4_ISR_Lora_Init();
    DIO5_ISR_Lora_Init();
    SystemTimerInit();*/
}
/**
 End of File
*/