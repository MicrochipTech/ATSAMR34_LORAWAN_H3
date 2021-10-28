/**
* \file  pds_nvm.h
*
* \brief This is the PDS NVM header file which containes NVM abstractions for PDS.
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



#ifndef _PDS_NVM_H_
#define _PDS_NVM_H_

/******************************************************************************
                   Includes section
******************************************************************************/
#include "definitions.h"
#include <xc.h>
#include "pds_interface.h"

/******************************************************************************
                   Defines section
******************************************************************************/
/* Default EEPROM Size - 4K Bytes */
#ifndef EEPROM_SIZE
#define EEPROM_SIZE			4096
#endif

#define EEPROM_PAGE_SIZE        (NVMCTRL_FLASH_PAGESIZE)
#define EEPROM_PAGE_PER_ROW     ((NVMCTRL_FLASH_ROWSIZE)/(NVMCTRL_FLASH_PAGESIZE))
#define EEPROM_ROW_SIZE         (NVMCTRL_FLASH_ROWSIZE)
#define EEPROM_NUM_ROWS         ((EEPROM_SIZE)/(EEPROM_ROW_SIZE))


/******************************************************************************
                               Types section
*******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/**************************************************************************//**
\brief	Initializes the NVM by checking the EEPROM size and calling nvm init.

\param[in] none
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmInit(void);

/**************************************************************************//**
\brief	This function will calculate the crc of the buffer contents and writes
		the buffer contents to nvm. It will also read the same content to verify
		if its written properly.

\param[in] 	pdsFileItemIdx - The file id to be written.
\param[in] 	buffer - The buffer containing data to be written.
\param[in] 	size - The size of the data in the buffer.
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmWrite(uint16_t rowId, PdsMem_t *buffer, uint16_t size);

/**************************************************************************//**
\brief	This function will read the contents of NVM and verify the crc.

\param[in] 	pdsFileItemIdx - The file id to be read.
\param[in] 	buffer - The buffer containing data to be read.
\param[in] 	size - The size of the data in the buffer.
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmRead(uint16_t rowId, PdsMem_t *buffer, uint16_t size);

/**************************************************************************//**
\brief	Will erase the contents of a row.

\param[in] 	rowId - The rowId to be erased.
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmErase(uint16_t rowId);

/**************************************************************************//**
\brief	Erases all the contents of NVM of all rows.

\param[in] 	none
\param[out] status - The return status of the function's operation of type PdsStatus_t.
******************************************************************************/
PdsStatus_t pdsNvmEraseAll(void);

#endif  /* _PDS_NVM_H_ */

/* eof pds_nvm.h */