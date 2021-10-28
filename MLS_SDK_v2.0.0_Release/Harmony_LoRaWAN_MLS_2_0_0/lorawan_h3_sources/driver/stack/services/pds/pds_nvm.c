/**
* \file  pds_nvm.c
*
* \brief This is the Pds NVM source file which contains NVM abstraction for PDS.
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



/******************************************************************************
                   Includes section
******************************************************************************/
#include "definitions.h"
#include "pds_interface.h"
#include "pds_common.h"
#include "pds_task_handler.h"
#include "pds_wl.h"

#define PDS_FLASH_START_ADDRESS     (NVMCTRL_RWWEEPROM_START_ADDRESS)

#define FLASH_USER_PAGE_ADDRESS     (0x00800000)
#define NVM_USER_MEMORY             ((volatile uint16_t *)FLASH_USER_PAGE_ADDRESS)

/************************************************************************/
/*  Static variables                                                    */
/************************************************************************/
#if (ENABLE_PDS == 1)
/******************************************************************************
                   Static prototype section
******************************************************************************/
static uint16_t calculate_crc(uint16_t length, uint8_t *data);
static uint16_t Crc16Ccitt(uint16_t initValue, uint8_t byte);
static uint32_t nvmLogicalRowToPhysicalAddr(uint16_t logicalRow);
static inline uint32_t pdsNvmRowStartAddr(uint32_t memAddr);

/******************************************************************************
                   Implementations section
******************************************************************************/

/**************************************************************************//**
\brief  Initializes the NVM by checking the EEPROM size and calling nvm init.

\param[in] none
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmInit(void)
{
    /* NVMCTRL_Initialize() shall be called before this function */
    return PDS_OK;
}

/**************************************************************************//**
\brief  This function will calculate the crc of the buffer contents and writes
        the buffer contents to nvm. It will also read the same content to verify
        if its written properly.

\param[in]  pdsFileItemIdx - The file id to be written.
\param[in]  buffer - The buffer containing data to be written.
\param[in]  size - The size of the data in the buffer.
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmWrite(uint16_t rowId, PdsMem_t *buffer, uint16_t size)
{
    uint32_t addr;
    uint32_t *nvmRow;
    PdsStatus_t status = PDS_OK;
    uint32_t pageWordLen = ((EEPROM_PAGE_SIZE) / sizeof(uint32_t));

    buffer->NVM_Struct.pdsNvmHeader.version = PDS_NVM_VERSION;
    buffer->NVM_Struct.pdsNvmHeader.size = size;
    buffer->NVM_Struct.pdsNvmHeader.crc =
            calculate_crc(buffer->NVM_Struct.pdsNvmHeader.size,
            (uint8_t *)(&(buffer->NVM_Struct.pdsNvmData)));
    size += sizeof(PdsNvmHeader_t);

    nvmRow = (uint32_t *)&(buffer->NVM_Mem.pdsNvmMem[0]);

    addr = pdsNvmRowStartAddr(nvmLogicalRowToPhysicalAddr(rowId));

    while(NVMCTRL_IsBusy());

    NVMCTRL_RWWEEPROM_RowErase(addr);

    while(NVMCTRL_IsBusy());

    if (NVMCTRL_ERROR_NONE != NVMCTRL_ErrorGet())
    {
        status = PDS_ERROR;
    }
    else
    {
        for (uint8_t i = 0; i < EEPROM_PAGE_PER_ROW; i++)
        {
            NVMCTRL_RWWEEPROM_PageWrite(&(nvmRow[i * pageWordLen]), addr);
            addr += EEPROM_PAGE_SIZE;
            while(NVMCTRL_IsBusy());
        }

        if (NVMCTRL_ERROR_NONE != NVMCTRL_ErrorGet())
        {
            status = PDS_ERROR;
        }
        else
        {
            status = pdsNvmRead(rowId, (PdsMem_t *const)buffer, size);
        }
    }
    return status;
}

/**************************************************************************//**
\brief  This function will read the contents of NVM and verify the crc.

\param[in]  pdsFileItemIdx - The file id to be read.
\param[in]  buffer - The buffer containing data to be read.
\param[in]  size - The size of the data in the buffer.
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmRead(uint16_t rowId, PdsMem_t *buffer, uint16_t size)
{
    PdsStatus_t status = PDS_OK;
    uint16_t crc = 0, crc2 = 0;
    uint8_t nvmRow[(EEPROM_ROW_SIZE)];

    while(NVMCTRL_IsBusy());

    NVMCTRL_Read(
            (uint32_t *)&(nvmRow[0]),
            EEPROM_ROW_SIZE,
            pdsNvmRowStartAddr(nvmLogicalRowToPhysicalAddr(rowId)));

    while(NVMCTRL_IsBusy());

    if (NVMCTRL_ERROR_NONE != NVMCTRL_ErrorGet())
    {
        status = PDS_ERROR;
    }
    else
    {
        /* Copy the required bytes to the target PDS buffer */
        memcpy((uint8_t *)&(buffer->NVM_Mem.pdsNvmMem[0]),
                (uint8_t *)&(nvmRow[0]), EEPROM_ROW_SIZE);

        crc = buffer->NVM_Struct.pdsNvmHeader.crc;
        crc2 = calculate_crc(buffer->NVM_Struct.pdsNvmHeader.size,
                (uint8_t *)&(buffer->NVM_Struct.pdsNvmData));
        if (crc != crc2)
        {
            status = PDS_CRC_ERROR;
        }
    }

    (void)size;
    return status;
}

/**************************************************************************//**
\brief  Will erase the contents of a row.

\param[in]  rowId - The rowId to be erased.
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmErase(uint16_t rowId)
{
    PdsStatus_t status = PDS_OK;

    while(NVMCTRL_IsBusy());

    /* RowErase ALWAYS returns true hence, return value unused */
    NVMCTRL_RWWEEPROM_RowErase(pdsNvmRowStartAddr(nvmLogicalRowToPhysicalAddr(rowId)));

    while(NVMCTRL_IsBusy());

    if (NVMCTRL_ERROR_NONE != NVMCTRL_ErrorGet())
    {
        status = PDS_ERROR;
    }

    return status;
}

/**************************************************************************//**
\brief  Erases all the contents of NVM of all rows.

\param[in]  none
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmEraseAll(void)
{
    PdsStatus_t statusCode;
    for(uint8_t row_idx = 0; row_idx< EEPROM_NUM_ROWS; row_idx++)
    {
        statusCode = pdsNvmErase(row_idx);
        if (PDS_OK != statusCode)
        {
            return statusCode;
        }
    }

    return PDS_OK;
}

/**************************************************************************//**
\brief  Calculates the CRC in CCITT polynome.

\param[in]  initValue - The rowId to be erased.
\param[in]  byte - The rowId to be erased.
\param[out] uint16_t - The calculated 16 bit CRC.
******************************************************************************/
uint16_t Crc16Ccitt(uint16_t initValue, uint8_t byte)
{
  byte ^= initValue & 0xffU;
  byte ^= byte << 4U;

  return ((((uint16_t)byte << 8) | ((initValue & 0xff00U) >> 8))
          ^ (uint8_t)(byte >> 4) ^ ((uint16_t)byte << 3));
}

/**************************************************************************//**
\brief  Calculates the CRC.

\param[in]  length - The amount of data for which CRC is to be calculated.
\param[in]  data - The data.
\param[out] uint16_t - The calculated 16 bit CRC.
******************************************************************************/
static uint16_t calculate_crc(uint16_t length, uint8_t *data)
{
  uint16_t eeprom_crc = 0U;
  for (uint16_t i = 0; i < length; i++)
  {
    eeprom_crc = Crc16Ccitt(eeprom_crc, data[i]);
  }
  return eeprom_crc;
}

/**************************************************************************//**
\brief  Converts logical rows to physical address.

\param[in]  logicalRow - The logical row.
\param[out] uint16_t - The calculated 16 bit CRC.
******************************************************************************/
static uint32_t nvmLogicalRowToPhysicalAddr(uint16_t logicalRow)
{
     return (PDS_FLASH_START_ADDRESS + (NVMCTRL_ROW_SIZE * logicalRow));
}

/**************************************************************************//**
\brief  Computes the start address of the row that contains the given address

\param[in]  memAddr - Address in NVM
\return     uint32_t - Start address of the row with \memAddr
******************************************************************************/
static inline uint32_t pdsNvmRowStartAddr(uint32_t memAddr)
{
    return (memAddr & ~((EEPROM_ROW_SIZE) - 1));
}
#endif
/* eof pds_nvm.c */
