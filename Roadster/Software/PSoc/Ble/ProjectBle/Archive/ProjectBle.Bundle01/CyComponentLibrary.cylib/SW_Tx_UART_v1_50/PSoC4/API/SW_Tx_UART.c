/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Software Transmit UART.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

#if(`$INSTANCE_NAME`_PIN_STATIC_MODE == 1u)
    uint32 `$INSTANCE_NAME`_pinNumber = `$INSTANCE_NAME`_PIN_NUMBER;
    uint32 `$INSTANCE_NAME`_pinPortNumber = `$INSTANCE_NAME`_PIN_PORT_NUMBER;
    #if(CY_PSOC3)
        uint32 pdata `$INSTANCE_NAME`_pinDrAdress = `$INSTANCE_NAME`_PIN_DR;
    #else
        uint32 `$INSTANCE_NAME`_pinDrAdress = `$INSTANCE_NAME`_PIN_DR;
    #endif /* (CY_PSOC3) */
#else
    uint32 `$INSTANCE_NAME`_pinNumber;
    uint32 `$INSTANCE_NAME`_pinPortNumber;
    #if(CY_PSOC3)
        uint32 pdata `$INSTANCE_NAME`_pinDrAdress;
    #else
        uint32 `$INSTANCE_NAME`_pinDrAdress;
    #endif /* (CY_PSOC3) */
#endif /* (`$INSTANCE_NAME`_PIN_STATIC_MODE == 1u) */


#if(`$INSTANCE_NAME`_PIN_STATIC_MODE == 1u)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_Start
    ********************************************************************************
    *
    * Summary:
    *  Empty function. Included for consistency with other
    *  components. This API is not available when PinAssignmentMethod
    *  is set to Dynamic.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil("`$INSTANCE_NAME`_Start")`
    {

    }
#else
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_StartEx
    ********************************************************************************
    *
    * Summary:
    *  Configures the SW Tx UART to use the pin specified
    *  by the parameters. This API is only available when
    *  PinAssignmentMethod is set to Dynamic.
    *
    * Parameters:
    *  port:  Port number for dynamic pin assignment
    *  pin:   Pin number for dynamic pin assignment
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_StartEx(uint8 port, uint8 pin) `=ReentrantKeil("`$INSTANCE_NAME`_StartEx")`
    {
        uint32 portConfigAddr;

        #if (CY_PSOC4)
            uint32 portDataRegAddr;
        #endif /* (CY_PSOC4) */

        if ((pin <= `$INSTANCE_NAME`_MAX_PIN_NUMBER) && (port <= `$INSTANCE_NAME`_MAX_PORT_NUMBER))
        {
            #if (!CY_PSOC4)
                portConfigAddr = `$INSTANCE_NAME`_PORT_CNF_BASE;
                portConfigAddr += ((uint32)port * (`$INSTANCE_NAME`_MAX_PIN_NUMBER + 1u)) + pin;
                CyPins_SetPinDriveMode(portConfigAddr, CY_PINS_DM_STRONG);
                CyPins_SetPin(portConfigAddr);
                `$INSTANCE_NAME`_pinDrAdress = portConfigAddr;
            #else
                portConfigAddr = `$INSTANCE_NAME`_PORT_CNF_BASE + (`$INSTANCE_NAME`_PORT_CNF_SIZE * port) +
                                                                                `$INSTANCE_NAME`_PORT_CNF_MODE_OFFSET;
                CY_SYS_PINS_SET_DRIVE_MODE(portConfigAddr, pin, CY_SYS_PINS_DM_STRONG);
                portDataRegAddr = `$INSTANCE_NAME`_PORT_CNF_BASE + (`$INSTANCE_NAME`_PORT_CNF_SIZE * port) +
                                                                                `$INSTANCE_NAME`_PORT_CNF_DR_OFFSET;
                CY_SYS_PINS_SET_PIN(portDataRegAddr, pin);
                `$INSTANCE_NAME`_pinDrAdress = portDataRegAddr;
            #endif /* (!CY_PSOC4) */
            `$INSTANCE_NAME`_pinNumber = pin;
            `$INSTANCE_NAME`_pinPortNumber = port;
        }
    }
#endif /* (`$INSTANCE_NAME`_PIN_STATIC_MODE == 1u) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil("`$INSTANCE_NAME`_Stop")`
{

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutString
********************************************************************************
*
* Summary:
*  Sends a NULL terminated string via the Tx pin.
*
* Parameters:
*  string: Pointer to the null terminated string to send
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutString(const char8 string[]) `=ReentrantKeil("`$INSTANCE_NAME`_PutString")`
{
    uint8 stringIndex = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while((char8) '\0' != current)
    {
        `$INSTANCE_NAME`_PutChar((uint8)current);
        current = string[stringIndex];
        stringIndex++;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutArray
********************************************************************************
*
* Summary:
*  Sends byteCount bytes from a memory array via the Tx pin.
*
* Parameters:
*  data: Pointer to the memory array
*  byteCount: Number of bytes to be transmitted
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutArray(const uint8 array[], uint32 byteCount) `=ReentrantKeil("`$INSTANCE_NAME`_PutArray")`
{
    uint32 arrayIndex;

    for (arrayIndex = 0u; arrayIndex < byteCount; arrayIndex++)
    {
        `$INSTANCE_NAME`_PutChar(array[arrayIndex]);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutHexByte
********************************************************************************
*
* Summary:
*  Sends a byte in Hex representation (two characters, uppercase for A-F) via
*  the Tx pin.
*
* Parameters:
*  TxHexByte: The byte to be converted to ASCII characters and
*             sent via the Tx pin.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutHexByte(uint8 txHexByte) `=ReentrantKeil("`$INSTANCE_NAME`_PutHexByte")`
{
    static char8 const CYCODE `$INSTANCE_NAME`_hex[] = "0123456789ABCDEF";

    `$INSTANCE_NAME`_PutChar((uint8) `$INSTANCE_NAME`_hex[txHexByte >> `$INSTANCE_NAME`_BYTE_UPPER_NIBBLE_SHIFT]);
    `$INSTANCE_NAME`_PutChar((uint8) `$INSTANCE_NAME`_hex[txHexByte & `$INSTANCE_NAME`_BYTE_LOWER_NIBBLE_MASK]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutHexInt
********************************************************************************
*
* Summary:
*  Sends a 16-bit unsigned integer in Hex representation (four characters,
*  uppercase for A-F) via the Tx pin.
*
* Parameters:
*  TxHexInt: The uint16 to be converted to ASCII characters and sent via
*            the Tx pin.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutHexInt(uint16 txHexInt) `=ReentrantKeil("`$INSTANCE_NAME`_PutHexInt")`
{
    `$INSTANCE_NAME`_PutHexByte((uint8)(txHexInt >> `$INSTANCE_NAME`_U16_UPPER_BYTE_SHIFT));
    `$INSTANCE_NAME`_PutHexByte((uint8)(txHexInt & `$INSTANCE_NAME`_U16_LOWER_BYTE_MASK));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutCRLF
********************************************************************************
*
* Summary:
*  Sends a carriage return (0x0D) and a line feed (0x0A) via the Tx pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutCRLF(void) `=ReentrantKeil("`$INSTANCE_NAME`_PutCRLF")`
{
    `$INSTANCE_NAME`_PutChar(0x0Du);
    `$INSTANCE_NAME`_PutChar(0x0Au);
}


/* [] END OF FILE */
