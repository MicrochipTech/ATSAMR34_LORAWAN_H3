/**
* \file  edbg_eui.h
*
* \brief This is the implementation of to read EUI value from EDBG
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




  /*
    4.3.1 Information Interface

    The TWI-bus can be used to request information from the EDBG. This
    is done by sending a special sequence as described below.

    ? START Condition
    ? Address + W
    ? Request token
    ? START Condition (repeated start)
    ? Address + R
    ? Response
    ? ...
    ? STOP Condition

    The sequence starts by sending a normal start condition followed
    by an address byte (default address is 0x28) with the RW bit
    cleared. Then a request token identifying the requested
    information is sent. Normally, a received byte would be put into
    the DGI buffer, but a repeated start will trigger the EDBG to
    parse the received token. Then an address with the RW bit set. The
    EDBG will then start to push the requested data onto the TWIbus.
    All response bytes must be ACKed by the master, and the final byte
    must be NAKed.


    4.3.1.2 Kit Data

    Token: 0xD2

    The EDBG has 256 bytes for storing kit-specific data such as MAC
    address, calibration values etc. See the kit documentation for
    details on how the data is organized. The information can be
    retrieved by using the Kit Data token. Note that not all kits have
    kit-specific data, and the entire section will read as 0.  After
    sending the token, the stored kit-specific data will be sent byte
    by byte starting with location 0, until a stop condition is
    detected.

   */

 #ifndef EDBG_EUI_H_
 #define EDBG_EUI_H_


/*------------------------------------Function Prototypes--------------------------------------------------------------*/

/*********************************************************************//**
\brief      Reads back the device MAC address stored in User page of EDBG
\param[in]  eui - Device EUI read back from EDBG(8 bytes)
*************************************************************************/
 void edbg_eui_read_eui64(uint8_t *eui);


 #endif /* EDBG_EUI_H_ */

