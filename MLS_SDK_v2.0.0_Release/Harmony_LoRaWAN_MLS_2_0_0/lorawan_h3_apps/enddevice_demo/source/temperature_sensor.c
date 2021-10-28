/**
* \file  temperature_sensor.c
*
* \brief Temperature Sensor access functions implementation
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
/***************************** DEFINES ****************************************/
#include "definitions.h"                // SYS function prototypes
#include "temperature_sensor.h"
#include "string.h"

/***************************** VARIABLES ****************************************/

/*  The following variables have referred with respect to device data sheet 
        Equation1 and Equation1b on section "Temperature Sensor Characteristics" 
        of Electrical Characteristics */

static float temperatureCourseVal; /* Coarse value of the temperature - tempC */
static float temperatureFineVal; /* Finer value of the temperature - tempF */

static float tempR; /* Production Room Temperature value read from NVM memory - tempR */
static float tempH; /* Production Hot Temperature value read from NVM memory - tempH */
static float INT1VR; /* Room temp 2?s complement of the internal 1V reference value - INT1VR */
static float INT1VH; /* Hot temp 2?s complement of the internal 1V reference value - INT1VR */
static uint16_t ADCR; /* Production Room Temperature ADC Value read from NVM memory - ADCR */
static uint16_t ADCH; /* Production Hot Temperature ADC Value read from NVM memory - ADCH */

static float VADCR; /* Room Temperature ADC voltage - VADCR */
static float VADCH; /* Hot Temperature ADC voltage - VADCH */

/***************************** STATIC FUNCTIONS **********************************/
static uint16_t tsAdcStartReadResult(void);
static float tsDecToFrac(uint8_t val);
static void tsLoadCalibData(void);
static float tsDecodeTemperature(uint16_t rawTemperatureCode);
static double tsReadSensorValue(int type);

/*************************** FUNCTIONS PROTOTYPE ******************************/

/*
 * \brief       The temperature sensor (datasheet 32.8.8) has the following characteristics:
 *              0.667 V at T = 25 deg C -> value is ca 2732 (with 12 bit/1V reference)
 *              2.36 mV / deg C
 * \param[out]  Temperature sensor value in Celsius
 */
static double tsReadSensorValue(int type)
{
    /*  To Store ADC output in voltage format */
    uint16_t raw_result;

    double temp;

    tsLoadCalibData();

    raw_result = tsAdcStartReadResult();

    temp = tsDecodeTemperature(raw_result);

    return temp;

}

/**
 * \brief ADC Temperature Sensor mode configuration.
 * This function enables internal temperature sensor feature of ADC with below Settings

 * GLCK for ADC		-> GCLK_GENERATOR_2 (1MHz)
 * CLK_ADC			-> 1KHz
 * REFERENCE			-> internal 1 V
 * POSITIVE INPUT	-> INTRENAL Temperature reference
 * NEGATIVE INPUT	-> GND
 * SAMPLES			-> 4
 * SAMPLE_LENGTH		-> 4
 */
void TEMPSENSOR_Initialize(void)
{
    /* Initialize ADC module */
    //ADC_Initialize();

    /* Enable ADC module */
    ADC_Enable();

}

/**
 * \brief        ADC START and Read Result.
 *
 *               This function starts the ADC and wait for the ADC
 *               conversation to be complete	and read the ADC result
 *               register and return the same to calling function.
 *
 * \param[out]   ADC result value
 */

static uint16_t tsAdcStartReadResult(void)
{
    uint16_t adc_result = 0;

    /* Start ADC conversion */
    ADC_ConversionStart();

    /* Wait till ADC conversion result is available */
    while (!ADC_ConversionStatusGet())
    {

    };

    /* Read the ADC result */
    adc_result = ADC_ConversionResultGet();

    return adc_result;
}

/**
 * \brief        Decimal to Fraction Conversation.
 *               This function converts the decimal value into fractional
 *               and return the fractional value for temperature calculation
 * \param[out]   Fraction value of Decimal
 */
static float tsDecToFrac(uint8_t val)
{
    if (val < 10)
    {
        return ((float) val / 10.0);
    }

    else if (val < 100)
    {
        return ((float) val / 100.0);
    }

    else
    {
        return ((float) val / 1000.0);
    }
}

/**
 * \brief Calibration Data.
 *        This function extract the production calibration data information from
 *        Temperature log row content and store it variables for temperature calculation
 *
 */
static void tsLoadCalibData(void)
{
    volatile uint32_t val1; /* Temperature Log Row Content first 32 bits */
    volatile uint32_t val2; /* Temperature Log Row Content another 32 bits */
    uint8_t room_temp_val_int; /* Integer part of room temperature in °C */
    uint8_t room_temp_val_dec; /* Decimal part of room temperature in °C */
    uint8_t hot_temp_val_int; /* Integer part of hot temperature in °C */
    uint8_t hot_temp_val_dec; /* Decimal part of hot temperature in °C */
    int8_t room_int1v_val; /* internal 1V reference drift at room temperature */
    int8_t hot_int1v_val; /* internal 1V reference drift at hot temperature*/

    uint32_t *temp_log_row_ptr = (uint32_t *) TEMP_LOG_ADDR;

    val1 = *temp_log_row_ptr;
    temp_log_row_ptr++;
    val2 = *temp_log_row_ptr;


    room_temp_val_int = (uint8_t) ((val1 & FUSES_ROOM_TEMP_VAL_INT_Msk) >> FUSES_ROOM_TEMP_VAL_INT_Pos);

    room_temp_val_dec = (uint8_t) ((val1 & FUSES_ROOM_TEMP_VAL_DEC_Msk) >> FUSES_ROOM_TEMP_VAL_DEC_Pos);

    hot_temp_val_int = (uint8_t) ((val1 & FUSES_HOT_TEMP_VAL_INT_Msk) >> FUSES_HOT_TEMP_VAL_INT_Pos);

    hot_temp_val_dec = (uint8_t) ((val1 & FUSES_HOT_TEMP_VAL_DEC_Msk) >> FUSES_HOT_TEMP_VAL_DEC_Pos);

    room_int1v_val = (int8_t) ((val1 & FUSES_ROOM_INT1V_VAL_Msk) >> FUSES_ROOM_INT1V_VAL_Pos);

    hot_int1v_val = (int8_t) ((val2 & FUSES_HOT_INT1V_VAL_Msk) >> FUSES_HOT_INT1V_VAL_Pos);

    ADCR = (uint16_t) ((val2 & FUSES_ROOM_ADC_VAL_Msk) >> FUSES_ROOM_ADC_VAL_Pos);

    ADCH = (uint16_t) ((val2 & FUSES_HOT_ADC_VAL_Msk) >> FUSES_HOT_ADC_VAL_Pos);


    tempR = room_temp_val_int + tsDecToFrac(room_temp_val_dec);

    tempH = hot_temp_val_int + tsDecToFrac(hot_temp_val_dec);

    INT1VR = 1 - ((float) room_int1v_val / INT1V_DIVIDER_1000);

    INT1VH = 1 - ((float) hot_int1v_val / INT1V_DIVIDER_1000);

    VADCR = ((float) ADCR * INT1VR) / ADC_12BIT_FULL_SCALE_VALUE_FLOAT;

    VADCH = ((float) ADCH * INT1VH) / ADC_12BIT_FULL_SCALE_VALUE_FLOAT;
}

/**
 * \brief       Temperature Calculation.
 *              This function calculate fine temperature using Equation1 and Equation
 *              1b as mentioned in data sheet section "Temperature Sensor Characteristics"
 *              of Electrical Characteristics.
 * \param[in]   ADC output value
 * \param[out]  Temperature value in Celsius
 *
 */
static float tsDecodeTemperature(uint16_t rawTemperatureCode)
{
    float VADC; /* Voltage calculation using ADC result for Coarse Temp calculation */
    float VADCM; /* Voltage calculation using ADC result for Fine Temp calculation. */
    float INT1VM; /* Voltage calculation for reality INT1V value during the ADC conversion */

    VADC = ((float) rawTemperatureCode * INT1V_VALUE_FLOAT) / ADC_12BIT_FULL_SCALE_VALUE_FLOAT;

    /* Coarse Temp Calculation by assume INT1V=1V for this ADC conversion */
    temperatureCourseVal = tempR + (((tempH - tempR) / (VADCH - VADCR)) * (VADC - VADCR));

    /* Calculation to find the real INT1V value during the ADC conversion */
    INT1VM = INT1VR + (((INT1VH - INT1VR) * (temperatureCourseVal - tempR)) / (tempH - tempR));

    VADCM = ((float) rawTemperatureCode * INT1VM) / ADC_12BIT_FULL_SCALE_VALUE_FLOAT;

    /* Fine Temp Calculation by replace INT1V=1V by INT1V = INT1Vm for ADC conversion */
    temperatureFineVal = tempR + (((tempH - tempR) / (VADCH - VADCR)) * (VADCM - VADCR));

    return temperatureFineVal;
}

void TEMPSENSOR_Read(uint8_t *data)
{
    float local_temp = 0;
    local_temp = tsReadSensorValue(0);
    memcpy(data, (uint8_t *) & local_temp, sizeof (local_temp));
}

/* eof temperature_sensor.c */

