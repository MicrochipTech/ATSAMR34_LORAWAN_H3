/**
* \file  temperature_sensor.h
*
* \brief Temperature Sensor access functions interfaces
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

#ifndef _TEMPERATURE_SENSOR_H
#define _TEMPERATURE_SENSOR_H

/***************************** DEFINES ****************************************/
#define ADC_TEMP_SAMPLE_LENGTH				(63)
#define INT1V_VALUE_FLOAT					(1.0)
#define INT1V_DIVIDER_1000					(1000.0)
#define ADC_12BIT_FULL_SCALE_VALUE_FLOAT	(4095.0)

#define NVMCTRL_TEMP_LOG              (0x00806030UL) /**< \brief (NVMCTRL) TEMP_LOG Base Address */

#define FUSES_HOT_ADC_VAL_ADDR      (NVMCTRL_TEMP_LOG + 4)
#define FUSES_HOT_ADC_VAL_Pos       20           /**< \brief (NVMCTRL_TEMP_LOG) 12-bit ADC conversion at hot temperature */
#define FUSES_HOT_ADC_VAL_Msk       (_U_(0xFFF) << FUSES_HOT_ADC_VAL_Pos)
#define FUSES_HOT_ADC_VAL(value)    (FUSES_HOT_ADC_VAL_Msk & ((value) << FUSES_HOT_ADC_VAL_Pos))

#define FUSES_HOT_INT1V_VAL_ADDR    (NVMCTRL_TEMP_LOG + 4)
#define FUSES_HOT_INT1V_VAL_Pos     0            /**< \brief (NVMCTRL_TEMP_LOG) 2's complement of the internal 1V reference drift at hot temperature (versus a 1.0 centered value) */
#define FUSES_HOT_INT1V_VAL_Msk     (_U_(0xFF) << FUSES_HOT_INT1V_VAL_Pos)
#define FUSES_HOT_INT1V_VAL(value)  (FUSES_HOT_INT1V_VAL_Msk & ((value) << FUSES_HOT_INT1V_VAL_Pos))

#define FUSES_HOT_TEMP_VAL_DEC_ADDR NVMCTRL_TEMP_LOG
#define FUSES_HOT_TEMP_VAL_DEC_Pos  20           /**< \brief (NVMCTRL_TEMP_LOG) Decimal part of hot temperature */
#define FUSES_HOT_TEMP_VAL_DEC_Msk  (_U_(0xF) << FUSES_HOT_TEMP_VAL_DEC_Pos)
#define FUSES_HOT_TEMP_VAL_DEC(value) (FUSES_HOT_TEMP_VAL_DEC_Msk & ((value) << FUSES_HOT_TEMP_VAL_DEC_Pos))

#define FUSES_HOT_TEMP_VAL_INT_ADDR NVMCTRL_TEMP_LOG
#define FUSES_HOT_TEMP_VAL_INT_Pos  12           /**< \brief (NVMCTRL_TEMP_LOG) Integer part of hot temperature in oC */
#define FUSES_HOT_TEMP_VAL_INT_Msk  (_U_(0xFF) << FUSES_HOT_TEMP_VAL_INT_Pos)
#define FUSES_HOT_TEMP_VAL_INT(value) (FUSES_HOT_TEMP_VAL_INT_Msk & ((value) << FUSES_HOT_TEMP_VAL_INT_Pos))

#define FUSES_ROOM_ADC_VAL_ADDR     (NVMCTRL_TEMP_LOG + 4)
#define FUSES_ROOM_ADC_VAL_Pos      8            /**< \brief (NVMCTRL_TEMP_LOG) 12-bit ADC conversion at room temperature */
#define FUSES_ROOM_ADC_VAL_Msk      (_U_(0xFFF) << FUSES_ROOM_ADC_VAL_Pos)
#define FUSES_ROOM_ADC_VAL(value)   (FUSES_ROOM_ADC_VAL_Msk & ((value) << FUSES_ROOM_ADC_VAL_Pos))

#define FUSES_ROOM_INT1V_VAL_ADDR   NVMCTRL_TEMP_LOG
#define FUSES_ROOM_INT1V_VAL_Pos    24           /**< \brief (NVMCTRL_TEMP_LOG) 2's complement of the internal 1V reference drift at room temperature (versus a 1.0 centered value) */
#define FUSES_ROOM_INT1V_VAL_Msk    (_U_(0xFF) << FUSES_ROOM_INT1V_VAL_Pos)
#define FUSES_ROOM_INT1V_VAL(value) (FUSES_ROOM_INT1V_VAL_Msk & ((value) << FUSES_ROOM_INT1V_VAL_Pos))

#define FUSES_ROOM_TEMP_VAL_DEC_ADDR NVMCTRL_TEMP_LOG
#define FUSES_ROOM_TEMP_VAL_DEC_Pos 8            /**< \brief (NVMCTRL_TEMP_LOG) Decimal part of room temperature */
#define FUSES_ROOM_TEMP_VAL_DEC_Msk (_U_(0xF) << FUSES_ROOM_TEMP_VAL_DEC_Pos)
#define FUSES_ROOM_TEMP_VAL_DEC(value) (FUSES_ROOM_TEMP_VAL_DEC_Msk & ((value) << FUSES_ROOM_TEMP_VAL_DEC_Pos))

#define FUSES_ROOM_TEMP_VAL_INT_ADDR NVMCTRL_TEMP_LOG
#define FUSES_ROOM_TEMP_VAL_INT_Pos 0            /**< \brief (NVMCTRL_TEMP_LOG) Integer part of room temperature in oC */
#define FUSES_ROOM_TEMP_VAL_INT_Msk (_U_(0xFF) << FUSES_ROOM_TEMP_VAL_INT_Pos)
#define FUSES_ROOM_TEMP_VAL_INT(value) (FUSES_ROOM_TEMP_VAL_INT_Msk & ((value) << FUSES_ROOM_TEMP_VAL_INT_Pos))

/*************************** FUNCTIONS PROTOTYPE ******************************/

/*********************************************************************//**
 \brief      Function to initialize the ADC for reading temperature 
			 sensor value
*************************************************************************/
void TEMPSENSOR_Initialize(void);

/*********************************************************************//**
 \brief          Function to read the temperature sensor value
 \param[out]     Pointer to Temperature Sensor output value 
*************************************************************************/
void TEMPSENSOR_Read(uint8_t *data);

/*---------------------------------------------------------------------------*/
#endif  /* _TEMPERATURE_SENSOR_H */
