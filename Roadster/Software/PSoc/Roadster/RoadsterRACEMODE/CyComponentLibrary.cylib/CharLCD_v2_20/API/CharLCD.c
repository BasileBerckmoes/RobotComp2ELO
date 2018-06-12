/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides source code for the Character LCD component's API.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "`$INSTANCE_NAME`.h"


static void `$INSTANCE_NAME`_WrDatNib(uint8 nibble) `=ReentrantKeil($INSTANCE_NAME . "_WrDatNib")`;
static void `$INSTANCE_NAME`_WrCntrlNib(uint8 nibble) `=ReentrantKeil($INSTANCE_NAME . "_WrCntrlNib")`;

/* Stores state of component. Indicates whether component is or not
* in enable state.
*/
uint8 `$INSTANCE_NAME`_enableState = 0u;

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Performs initialization required for the components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enables a 4-bit interface
*        Clears the display
*        Enables the auto cursor increment
*        Resets the cursor to start position
*  Also, it loads a custom character set to the LCD if it was defined in the customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    /* INIT CODE */
    CyDelay(40u);                                                        /* Delay 40 ms */
    `$INSTANCE_NAME`_WrCntrlNib(`$INSTANCE_NAME`_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(5u);                                                         /* Delay 5 ms */
    `$INSTANCE_NAME`_WrCntrlNib(`$INSTANCE_NAME`_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(15u);                                                        /* Delay 15 ms */
    `$INSTANCE_NAME`_WrCntrlNib(`$INSTANCE_NAME`_DISPLAY_8_BIT_INIT);    /* Selects 8-bit mode */
    CyDelay(1u);                                                         /* Delay 1 ms */
    `$INSTANCE_NAME`_WrCntrlNib(`$INSTANCE_NAME`_DISPLAY_4_BIT_INIT);    /* Selects 4-bit mode */
    CyDelay(5u);                                                         /* Delay 5 ms */

    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_CURSOR_AUTO_INCR_ON);    /* Incr Cursor After Writes */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_CURSOR_ON);      /* Turn Display, Cursor ON */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_2_LINES_5x10);   /* 2 Lines by 5x10 Characters */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_CURSOR_OFF);     /* Turn Display, Cursor OFF */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_CLEAR_DISPLAY);          /* Clear LCD Screen */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_ON_CURSOR_OFF);  /* Turn Display ON, Cursor OFF */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_RESET_CURSOR_POSITION);  /* Set Cursor to 0,0 */
    CyDelay(5u);

    #if(`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE)
        `$INSTANCE_NAME`_LoadCustomFonts(`$INSTANCE_NAME`_customFonts);
    #endif /* `$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Turns on the display.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
* Theory:
*  This function has no effect when it is called the first time as
*  `$INSTANCE_NAME`_Init() turns on the LCD.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    `$INSTANCE_NAME`_DisplayOn();
    `$INSTANCE_NAME`_enableState = 1u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs initialization required for the components normal work.
*  This function initializes the LCD hardware module as follows:
*        Enables 4-bit interface
*        Clears the display
*        Enables auto cursor increment
*        Resets the cursor to start position
*  Also, it loads a custom character set to the LCD if it was defined in the customizer.
*  If it was not the first call in this project, then it just turns on the
*  display
*
*
* Parameters:
*  `$INSTANCE_NAME`_initVar - global variable.
*
* Return:
*  `$INSTANCE_NAME`_initVar - global variable.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not initialized, perform initialization */
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    /* Turn on the LCD */
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Turns off the display of the LCD screen.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* Calls LCD Off Macro */
    `$INSTANCE_NAME`_DisplayOff();
    `$INSTANCE_NAME`_enableState = 0u;
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_Position
********************************************************************************
*
* Summary:
*  Moves the active cursor location to a point specified by the input arguments
*
* Parameters:
*  row:    Specific row of LCD module to be written
*  column: Column of LCD module to be written
*
* Return:
*  None.
*
* Note:
*  This only applies for LCD displays that use the 2X40 address mode.
*  In this case Row 2 starts with a 0x28 offset from Row 1.
*  When there are more than 2 rows, each row must be fewer than 20 characters.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Position(uint8 row, uint8 column) `=ReentrantKeil($INSTANCE_NAME . "_Position")`
{
    switch (row)
    {
        case (uint8)0:
            `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_ROW_0_START + column);
            break;
        case (uint8) 1:
            `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_ROW_1_START + column);
            break;
        case (uint8) 2:
            `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_ROW_2_START + column);
            break;
        case (uint8) 3:
            `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_ROW_3_START + column);
            break;
        default:
            /* if default case is hit, invalid row argument was passed.*/
            break;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PrintString
********************************************************************************
*
* Summary:
*  Writes a zero terminated string to the LCD.
*
* Parameters:
*  string: Pointer to head of char8 array to be written to the LCD module
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_PrintString(char8 const string[]) `=ReentrantKeil($INSTANCE_NAME . "_PrintString")`
{
    uint8 indexU8 = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while((char8) '\0' != current)
    {
        `$INSTANCE_NAME`_WriteData((uint8)current);
        current = string[indexU8];
        indexU8++;
    }
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_PutChar
********************************************************************************
*
* Summary:
*  Writes a single character to the current cursor position of the LCD module.
*  Custom character names (`$INTANCE_NAME`_CUSTOM_0 through
*  `$INTANCE_NAME`_CUSTOM_7) are acceptable as inputs.
*
* Parameters:
*  character: Character to be written to LCD
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutChar(char8 character) `=ReentrantKeil($INSTANCE_NAME . "_PutChar")`
{
    `$INSTANCE_NAME`_WriteData((uint8)character);
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WriteData
********************************************************************************
*
* Summary:
*  Writes a data byte to the LCD module's Data Display RAM.
*
* Parameters:
*  dByte: Byte to be written to the LCD module
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteData(uint8 dByte) `=ReentrantKeil($INSTANCE_NAME . "_WriteData")`
{
    uint8 nibble;

    `$INSTANCE_NAME`_IsReady();
    nibble = dByte >> `$INSTANCE_NAME`_NIBBLE_SHIFT;

    /* Write high nibble */
    `$INSTANCE_NAME`_WrDatNib(nibble);

    nibble = dByte & `$INSTANCE_NAME`_NIBBLE_MASK;
    /* Write low nibble */
    `$INSTANCE_NAME`_WrDatNib(nibble);
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WriteControl
********************************************************************************
*
* Summary:
*  Writes a command byte to the LCD module.
*
* Parameters:
*  cByte:  The byte to be written to theLCD module
* 
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteControl(uint8 cByte) `=ReentrantKeil($INSTANCE_NAME . "_WriteControl")`
{
    uint8 nibble;

    `$INSTANCE_NAME`_IsReady();

    nibble = cByte >> `$INSTANCE_NAME`_NIBBLE_SHIFT;
    
    /* WrCntrlNib(High Nibble) */
    `$INSTANCE_NAME`_WrCntrlNib(nibble);
    nibble = cByte & `$INSTANCE_NAME`_NIBBLE_MASK;

    /* WrCntrlNib(Low Nibble) */
    `$INSTANCE_NAME`_WrCntrlNib(nibble);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsReady
********************************************************************************
*
* Summary:
*  Polls the LCD until the ready bit is set or a timeout occurs.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Note:
*  Changes the pins to High-Z.
*
*******************************************************************************/
void `$INSTANCE_NAME`_IsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_IsReady")`
{
    `$TypeReplacementString` value;
    uint32 timeout;
    timeout = `$INSTANCE_NAME`_READY_DELAY;

    /* Clear LCD port*/
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_PORT_MASK));

    /* PSoC4 has a little different from PSoC3/5 port/pin organization for setting Drive Modes.
  
    */
    #if (CY_PSOC4)
        
        /* Mask off data pins to clear old values out */
        value = `$INSTANCE_NAME`_PORT_PC_REG & ((uint32) (~ `$INSTANCE_NAME`_DM_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        `$INSTANCE_NAME`_PORT_PC_REG = value | `$INSTANCE_NAME`_HIGH_Z_DATA_DM;

    #else
    
        /* Change Port to High-Z Status on data pins */

        /* Mask off data pins to clear old values out */
        value = `$INSTANCE_NAME`_PORT_DM0_REG & ((uint8)(~`$INSTANCE_NAME`_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        `$INSTANCE_NAME`_PORT_DM0_REG = value | (`$INSTANCE_NAME`_HIGH_Z_DM0 & `$INSTANCE_NAME`_DATA_MASK);

        /* Mask off data pins to clear old values out */
        value = `$INSTANCE_NAME`_PORT_DM1_REG & ((uint8)(~`$INSTANCE_NAME`_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        `$INSTANCE_NAME`_PORT_DM1_REG = value;

        /* Mask off data pins to clear old values out */
        value = `$INSTANCE_NAME`_PORT_DM2_REG & ((uint8)(~`$INSTANCE_NAME`_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        `$INSTANCE_NAME`_PORT_DM2_REG = value;
    
    #endif /* CY_PSOC4 */
    
    /* Make sure RS is low */
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_RS));

    /* Set R/W high to read */
    `$INSTANCE_NAME`_PORT_DR_REG |= `$INSTANCE_NAME`_RW;

    do
    {
        /* 40 ns delay required before rising Enable and 500ns between neighbour Enables */
        CyDelayUs(0u);

        /* Set E high */
        `$INSTANCE_NAME`_PORT_DR_REG |= `$INSTANCE_NAME`_E;

        /* 360 ns delay setup time for data pins */
        CyDelayUs(1u);

        /* Get port state */
        value = `$INSTANCE_NAME`_PORT_PS_REG;

        /* Set enable low */
        `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_E));

        /* This gives true delay between disabling Enable bit and polling Ready bit */
        CyDelayUs(0u);

        /* Extract ready bit */
        value &= `$INSTANCE_NAME`_READY_BIT;

        /* Set E high as we in 4-bit interface we need extra operation */
        `$INSTANCE_NAME`_PORT_DR_REG |= `$INSTANCE_NAME`_E;

        /* 360 ns delay setup time for data pins */
        CyDelayUs(1u);

        /* Set enable low */
        `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_E));

        /* If LCD is not ready make a delay */
        if (value == 0u)
        {
            CyDelayUs(10u);
        }

        /* Repeat until bit 4 is not zero or until timeout. */
        timeout--;

    } while ((value != 0u) && (timeout > 0u));

    /* Set R/W low to write */
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_RW));

    /* Clear LCD port*/
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_PORT_MASK));

    #if (CY_PSOC4)
        
        /* Mask off data pins to clear old values out */
        value = `$INSTANCE_NAME`_PORT_PC_REG & ((uint32)(~ `$INSTANCE_NAME`_DM_DATA_MASK));
        /* Load in high Z values for data pins, others unchanged */
        `$INSTANCE_NAME`_PORT_PC_REG = value | `$INSTANCE_NAME`_STRONG_DATA_DM;

    #else

        /* Change Port to Output (Strong) on data pins */
        /* Mask off data pins to clear high z values out. Configure data pins 
        * to Strong Drive, others unchanged.
        */
        `$INSTANCE_NAME`_PORT_DM0_REG &= ((uint8)(~`$INSTANCE_NAME`_DATA_MASK));
        /* Mask off data pins to clear high z values out */
        value = `$INSTANCE_NAME`_PORT_DM1_REG & ((uint8)(~`$INSTANCE_NAME`_DATA_MASK));
        /* Configure data pins to Strong Drive, others unchanged */
        `$INSTANCE_NAME`_PORT_DM1_REG = value | (`$INSTANCE_NAME`_STRONG_DM1 & `$INSTANCE_NAME`_DATA_MASK);

        /* Mask off data pins to clear high z values out */
        value = `$INSTANCE_NAME`_PORT_DM2_REG & ((uint8)(~`$INSTANCE_NAME`_DATA_MASK));
        /* Configure data pins to Strong Drive, others unchanged */
        `$INSTANCE_NAME`_PORT_DM2_REG = value | (`$INSTANCE_NAME`_STRONG_DM2 & `$INSTANCE_NAME`_DATA_MASK);
    
    #endif /* CY_PSOC4 */
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WrDatNib
********************************************************************************
*
* Summary:
*  Writes a data nibble to the LCD module.
*
* Parameters:
*  nibble:  Byte containing nibble in the least significant nibble to be
*           written to the LCD module.
*
* Return:
*  None.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_WrDatNib(uint8 nibble) `=ReentrantKeil($INSTANCE_NAME . "_WrDatNib")`
{
    /* RS should be low to select data register */
    `$INSTANCE_NAME`_PORT_DR_REG |= `$INSTANCE_NAME`_RS;
    /* Reset RW for write operation */
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_RW));

    /* Guaranteed delay between Setting RS and RW and setting E bits */
    CyDelayUs(0u);
    
    /* Clear data pins */
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_DATA_MASK));

    /* Write data, bring E high */
    #if(0u != `$INSTANCE_NAME`_PORT_SHIFT) /* MISRA forbids shift by 0 so need to handle that */
        `$INSTANCE_NAME`_PORT_DR_REG |= 
            (`$INSTANCE_NAME`_E | ((uint8)(((uint8) nibble) << `$INSTANCE_NAME`_PORT_SHIFT)));
    #else
        `$INSTANCE_NAME`_PORT_DR_REG |= (`$INSTANCE_NAME`_E | nibble);
    #endif /* (0u != `$INSTANCE_NAME`_PORT_SHIFT) */

    /* Minimum of 230 ns delay */
    CyDelayUs(1u);

    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_E));
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WrCntrlNib
********************************************************************************
*
* Summary:
*  Writes a control nibble to the LCD module.
*
* Parameters:
*  nibble: The byte containing a nibble in the four least significant bits.????
*
* Return:
*  None.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_WrCntrlNib(uint8 nibble) `=ReentrantKeil($INSTANCE_NAME . "_WrCntrlNib")`
{
    /* RS and RW should be low to select instruction register and  write operation respectively */
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~(`$INSTANCE_NAME`_RS | `$INSTANCE_NAME`_RW)));

    /* Two following lines of code will give 40ns delay */
    /* Clear data pins */
    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_DATA_MASK));

    /* Write control data and set enable signal */
    #if(0u != `$INSTANCE_NAME`_PORT_SHIFT) /* MISRA forbids shift by 0 so need to handle that */
        `$INSTANCE_NAME`_PORT_DR_REG |= 
            (`$INSTANCE_NAME`_E | ((uint8)(((uint8) nibble) << `$INSTANCE_NAME`_PORT_SHIFT)));
    #else
        `$INSTANCE_NAME`_PORT_DR_REG |= (`$INSTANCE_NAME`_E | nibble);
    #endif /* (0u != `$INSTANCE_NAME`_PORT_SHIFT) */

    /* Minimum of 230 ns delay */
    CyDelayUs(1u);

    `$INSTANCE_NAME`_PORT_DR_REG &= ((`$TypeReplacementString`)(~`$INSTANCE_NAME`_E));
}


#if(`$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u)

    /*******************************************************************************
    *  Function Name: `$INSTANCE_NAME`_PrintInt8
    ********************************************************************************
    *
    * Summary:
    *  Print a byte as two ASCII characters.
    *
    * Parameters:
    *  value: The byte to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PrintInt8(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt8")`
    {
        static char8 const CYCODE `$INSTANCE_NAME`_hex[16u] = "0123456789ABCDEF";
        
        `$INSTANCE_NAME`_PutChar((char8) `$INSTANCE_NAME`_hex[value >> `$INSTANCE_NAME`_BYTE_UPPER_NIBBLE_SHIFT]);
        `$INSTANCE_NAME`_PutChar((char8) `$INSTANCE_NAME`_hex[value & `$INSTANCE_NAME`_BYTE_LOWER_NIBBLE_MASK]);
    }


    /*******************************************************************************
    *  Function Name: `$INSTANCE_NAME`_PrintInt16
    ********************************************************************************
    *
    * Summary:
    *  Print a uint16 as four ASCII characters.
    *
    * Parameters:
    *  value: The uint16 to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PrintInt16(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt16")`
    {
        `$INSTANCE_NAME`_PrintInt8((uint8)(value >> `$INSTANCE_NAME`_U16_UPPER_BYTE_SHIFT));
        `$INSTANCE_NAME`_PrintInt8((uint8)(value & `$INSTANCE_NAME`_U16_LOWER_BYTE_MASK));
    }

    
    /*******************************************************************************
    *  Function Name: `$INSTANCE_NAME`_PrintInt32
    ********************************************************************************
    *
    * Summary:
    *  Print a uint32 hexadecimal number as eight ASCII characters.
    *
    * Parameters:
    *  value: The uint32 to be printed out as ASCII characters.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PrintInt32(uint32 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt32")`
    {
        uint8 shift = `$INSTANCE_NAME`_32_BIT_SHIFT;
        
        while (shift != 0u)
        {
            /* "shift" var is to be subtracted by 8 prior shifting. This implements 
            * shifting by 24, 16, 8 and 0u. 
            */
            shift -= `$INSTANCE_NAME`_8_BIT_SHIFT;
            
            /* Print 8 bits of uint32 hex number */
            `$INSTANCE_NAME`_PrintInt8((uint8) ((uint32) (value >> shift)));
        }
    }
    
    
    /*******************************************************************************
    *  Function Name: `$INSTANCE_NAME`_PrintNumber
    ********************************************************************************
    *
    * Summary:
    *  Print an uint16 value as a left-justified decimal value.
    *
    * Parameters:
    *  value: A 16-bit value to be printed in ASCII characters as a decimal number
    *
    * Return:
    *  None.
    *
    * Note:
    *  This function is implemented as a macro.
    *
    *******************************************************************************/

    
    /*******************************************************************************
    *  Function Name: `$INSTANCE_NAME`_PrintU32Number
    ********************************************************************************
    *
    * Summary:
    *  Print an uint32 value as a left-justified decimal value.
    *
    * Parameters:
    *  value: A 32-bit value to be printed in ASCII characters as a decimal number
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PrintU32Number(uint32 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintU32Number")`
    {
        uint8 tmpDigit;
        char8 number[`$INSTANCE_NAME`_NUMBER_OF_REMAINDERS_U32 + 1u];
        uint8 digIndex = `$INSTANCE_NAME`_NUMBER_OF_REMAINDERS_U32;
        
        /* This API will output a decimal number as a string and that string will be 
        * filled from end to start. Set Null termination character first.
        */
        number[digIndex] = (char8) '\0';
        digIndex--;
        
        /* Load these in reverse order */
        while(value >= `$INSTANCE_NAME`_TEN)
        {
            /* Extract decimal digit, indexed by 'digIndex', from 'value' and
            * convert it to ASCII character.
            */
            tmpDigit = (uint8) (((uint8) (value % `$INSTANCE_NAME`_TEN)) + (uint8) `$INSTANCE_NAME`_ZERO_CHAR_ASCII);
            
            /* Temporary variable 'tmpDigit' is used to avoid Violation of MISRA rule 
            * #10.3.
            */
            number[digIndex] = (char8) tmpDigit;
            value /= `$INSTANCE_NAME`_TEN;
            digIndex--;
        }
        
        /* Extract last decimal digit 'digIndex', from the 'value' and convert it
        * to ASCII character.
        */
        tmpDigit = (uint8) (((uint8)(value % `$INSTANCE_NAME`_TEN)) + (uint8) `$INSTANCE_NAME`_ZERO_CHAR_ASCII);
        number[digIndex] = (char8) tmpDigit;

        /* Print out number */
        `$INSTANCE_NAME`_PrintString(&number[digIndex]);
    }
    
#endif /* `$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u */


/* [] END OF FILE */
