/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides source code for the I2C LCD component's API.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/* Internal function ptototypes */
static void `$INSTANCE_NAME`_WrDataToBuff(uint8 dByte) CYREENTRANT;
static void `$INSTANCE_NAME`_WrCntrlPatt(uint8 cmdIndex) CYREENTRANT;
static void `$INSTANCE_NAME`_SendSequence(void) CYREENTRANT;

#if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
    static void `$INSTANCE_NAME`_SendCmd(uint8 cmd) CYREENTRANT;
#endif /* `$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X */

uint8 `$INSTANCE_NAME`_initVar = 0u;

/* Buffer that holds data to be send to LCD slave */
static uint8 `$INSTANCE_NAME`_buff[`$INSTANCE_NAME`_BUFF_SIZE];

/* Need to have `$INSTANCE_NAME`_buffIndex of different size to avoid MISRA
* warning when SCB based I2C Master is used. 
*/
#if(`$INSTANCE_NAME`_IS_SCB_MASTER_USED)
    /* Variable used for buffer indexing */
    static uint32 `$INSTANCE_NAME`_buffIndex = 0u;
    /* Variable stores the I2C address */
    static uint32 `$INSTANCE_NAME`_address = `$INSTANCE_NAME`_DEFAULT_I2C_ADDRESS;
#else
    /* Variable used for buffer indexing */
    static uint8 `$INSTANCE_NAME`_buffIndex = 0u;
    /* Variable stores the I2C address */
    static uint8 `$INSTANCE_NAME`_address = `$INSTANCE_NAME`_DEFAULT_I2C_ADDRESS;
#endif /* (`$INSTANCE_NAME`_IS_SCB_MASTER_USED) */

/********************
* Generated Code
********************/
/* Array with command patterns */
`$CmdPattArray`

/********************
* Generated Code 
********************/
/* Optional: Array with custom character set */
`$CustomFontsArray`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Performs initialization required for the component's normal work.
*  I2C_LCD_Init() also loads the custom character set if it was defined in the
*  Configure dialog.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    /* Following part of code is only applicable for NXP LCDs */
    #if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
        /* Select Extended Instruction set, 2x16 display */
        `$INSTANCE_NAME`_SendCmd(`$INSTANCE_NAME`_SET_EXTENDED_FUNC);
        /* Split screen configuration  */
        `$INSTANCE_NAME`_SendCmd(`$INSTANCE_NAME`_SPLIT_SCREEN);
        /* LCD Module format: left to right column, and top to bottom rows  */
        `$INSTANCE_NAME`_SendCmd(`$INSTANCE_NAME`_DISP_CONF);
        /* Icon mode not supported. Disable all icon enable settings */
        `$INSTANCE_NAME`_SendCmd(`$INSTANCE_NAME`_ICON_CTL);
        /* Set LCD bias voltage to 4.38 V since LCD module datasheet recommends 4.4 V */
        `$INSTANCE_NAME`_SendCmd(`$INSTANCE_NAME`_VLCD_SET);
        /* Select Standard Instruction set, 2x16 display */
        `$INSTANCE_NAME`_SendCmd(`$INSTANCE_NAME`_FUNCTION_SET_STANDARD);
    #endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) */
    
    /* Configure LCD for 2 lines and 16 characters */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_2_LINES_5x10);
    /* Turn on both display and cursor */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_CURSOR_ON);
    /* Turn on cursor auto incrementing */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_CURSOR_AUTO_INCR_ON);
    /* Turn off cursor underlining */
    `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_ON_CURSOR_OFF);
    /* Clear the Display */
    `$INSTANCE_NAME`_ClearDisplay();
    
    /* Load custom character set */
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
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
* Theory:
*  This function has no effect when it called first time as
*  `$INSTANCE_NAME`_Init() turns on the LCD.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    `$INSTANCE_NAME`_DisplayOn();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  This function initializes the LCD hardware module as follows:
*       Initialize the I2C bus if it hasn't already been
*       Clears the display;
*       Enables auto cursor increment;
*       Resets the cursor to start position;
*       It also loads a custom character set to LCD if it was defined in the
*  customizer's GUI.
*
* Parameters:
*  `$INSTANCE_NAME`_initVar - global variable.
*
* Return:
*  `$INSTANCE_NAME`_initVar - global variable.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not initialized then perform initialization */
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
*  Turns off the display of the LCD screen but does not stop the I2C Master
*  component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    `$INSTANCE_NAME`_DisplayOff();
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_Position
********************************************************************************
*
* Summary:
*  Moves the cursor to the location specified by arguments row and column.
*
* Parameters:
*  row:     The row number at which to position the cursor. Minimum value is
*           zero.
*  column:  The column number at which to position the cursor. Minimum value is
*           zero.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Position(uint8 row, uint8 column) `=ReentrantKeil($INSTANCE_NAME . "_Position")`
{
    /* Write command pattern for "Set cursor position" to buffer */
    `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_DDRAM_0_IDX);

    #if(`$INSTANCE_NAME`_LENGTH_2_BYTES == `$INSTANCE_NAME`_DDRAM_0_DATA_LEN)
        /* In case when there two bytes of data for "Set cursor position" it is
        * required to send both row and column. The numeration of rows and 
        * columns starts from '1' so the row and column should be incremented.
        */
        `$INSTANCE_NAME`_WrDataToBuff(column + 1u);
        `$INSTANCE_NAME`_WrDataToBuff(row + 1u);
    #else
        /* Position is sent as one byte so it is required to calculate the position */
        switch (row)
        {
            case (uint8) 0u:
                /* To avoid MISRA warnig */
                #if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
                    `$INSTANCE_NAME`_WrDataToBuff(`$INSTANCE_NAME`_ROW_0_START + column);
                #else
                    `$INSTANCE_NAME`_WrDataToBuff(column);
                #endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) */
                
                break;
            
            case (uint8) 1u:
                `$INSTANCE_NAME`_WrDataToBuff(`$INSTANCE_NAME`_ROW_1_START + column);
                break;
            
            case (uint8) 2u:
                `$INSTANCE_NAME`_WrDataToBuff(`$INSTANCE_NAME`_ROW_2_START + column);
                break;
            
            case (uint8) 3u:
                `$INSTANCE_NAME`_WrDataToBuff(`$INSTANCE_NAME`_ROW_3_START + column);
                break;
            
            default:
                /* if default case is hit, invalid row argument was passed.*/
                break;
        }        
    #endif /* (`$INSTANCE_NAME`_LENGTH_2_BYTES == `$INSTANCE_NAME`_SET_POS_DATA_LEN) */

    /* Send data to LCD and wait when transaction complete */
    `$INSTANCE_NAME`_SendSequence();
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WriteData
********************************************************************************
*
* Summary:
*  Writes data to the LCD RAM in the current position. Upon write completion,
*  the position is incremented or decremented depending on the entry mode
*  specified.
*
* Parameters:
*  dByte:  The byte to be written to the LCD module.
*
* Return:
*  None.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteData(uint8 dByte) `=ReentrantKeil($INSTANCE_NAME . "_WriteData")`
{
    /* Send required control byte value to address data register */
    `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_WRITE_DATA_IDX);

    /* Add byte of data to buffer */
    `$INSTANCE_NAME`_WrDataToBuff(dByte);

    /* Send data to LCD and wait when transaction complete */
    `$INSTANCE_NAME`_SendSequence();
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WrDataToBuff
********************************************************************************
*
* Summary:
*  Writes a byte of data to the display buffer.
*
* Parameters:
*  nibble:  the byte containing nibble in least significant nibble to be written
*           to the LCD module.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
static void `$INSTANCE_NAME`_WrDataToBuff(uint8 dByte) CYREENTRANT
{
    /* Put one byte of data to buffer at location of `$INSTANCE_NAME`_buffIndex */
    `$INSTANCE_NAME`_buff[`$INSTANCE_NAME`_buffIndex] = dByte;
    /* Increment `$INSTANCE_NAME`_buffIndex to point to next free position */
    `$INSTANCE_NAME`_buffIndex++;
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WriteControl
********************************************************************************
*
* Summary:
*  Writes a command byte to the LCD module. Different LCD models can have their
*  own commands. Review the specific LCD datasheet for commands valid for that
*  model.
*
* Parameters:
*  cByte:   An 8-bit value representing the command to be loaded into the command
*  register of the LCD module. Valid command parameters are specified in the
*  table below:
*   `$INSTANCE_NAME`_CLEAR_DISPLAY          Clear display.
*   `$INSTANCE_NAME`_CURSOR_HOME            Return cursor and LCD to home
*                                           position.
*   `$INSTANCE_NAME`_SET_CURSOR_POSITION    Set position of cursor.
*   `$INSTANCE_NAME`_DISPLAY_CURSOR_OFF     Disable display and cursor.
*   `$INSTANCE_NAME`_DISPLAY_CURSOR_ON      Enable display and cursor.
*   `$INSTANCE_NAME`_DISPLAY_ON_CURSOR_OFF
*   `$INSTANCE_NAME`_DISPLAY_ON             Enable display, cursor off.
*   `$INSTANCE_NAME`_CURSOR_BLINKING_ON     Enable display, cursor on, set
*                                           cursor blink.
*   `$INSTANCE_NAME`_CURSOR_BLINKING_OFF    Enable display, cursor on, cursor
*                                           blinking off.
*   `$INSTANCE_NAME`_SET_CGRAM_ADDR         Set position to the specific
*                                           address in CGRAM (used for loading
*                                           custom characters).
*   `$INSTANCE_NAME`_CURSOR_AUTO_INCR_ON    Enable auto increment of cursor
*                                           position.
*   `$INSTANCE_NAME`_DISPLAY_2_LINES_16     Set display to be 2 lines 16
*                                           characters.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteControl(uint8 cByte) `=ReentrantKeil($INSTANCE_NAME . "_WriteControl")`
{
    uint8 cmdIndx = 0u;
    
    while(cmdIndx < `$INSTANCE_NAME`_NUM_COMMANDS)
    {   
        if (cByte == `$INSTANCE_NAME`_cmdPatt[cmdIndx][`$INSTANCE_NAME`_COMMAND_BYTE_INDEX])
        {
            /* Fill control pattern based on found index */
            `$INSTANCE_NAME`_WrCntrlPatt(cmdIndx);

            /* Send data to LCD and wait when transaction complete */
            `$INSTANCE_NAME`_SendSequence();

            /* Following commands require 1.5 ms delay to execute */
            switch(cByte)
            {
                case `$INSTANCE_NAME`_CLEAR_DISPLAY :
                case `$INSTANCE_NAME`_CURSOR_HOME :
                case `$INSTANCE_NAME`_DISPLAY_CURSOR_ON :
                case `$INSTANCE_NAME`_DISPLAY_CURSOR_OFF :
                    CyDelayUs(`$INSTANCE_NAME`_CMOMMAND_DELAY);
                    break;
                default:
                    break;
            }
            /* Command index was found - break while() loop */
            break;
        }
        /* Increment command pattern index */
        cmdIndx++;
    } 
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_WrCntrlPatt
********************************************************************************
*
* Summary:
*  Writes a control pattern to the buffer that will be later send to the LCD
*  module.
*
* Parameters:
*  cmdIndex: Index of the command pattern in the look-up array.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
static void `$INSTANCE_NAME`_WrCntrlPatt(uint8 cmdIndex) CYREENTRANT
{
    /* Need to have index 'i' of different size to avoid MISRA
    * warning when SCB based I2C Master is used. 
    */
    #if(`$INSTANCE_NAME`_IS_SCB_MASTER_USED)
        uint32 i;
    #else
        uint8 i;
    #endif /* (`$INSTANCE_NAME`_IS_SCB_MASTER_USED) */

    /* Fill buffer with command pattern */
    for(i = 1u; i <= `$INSTANCE_NAME`_cmdPatt[cmdIndex][0u]; i++)
    {
        `$INSTANCE_NAME`_buff[i - 1u] =  `$INSTANCE_NAME`_cmdPatt[cmdIndex][i];
    }

    /* Set index to point on next free position in buffer */
    `$INSTANCE_NAME`_buffIndex = i - 1u;
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_SendSequence
********************************************************************************
*
* Summary:
*  Sends the content of the buffer to the LCD module and waits while transaction
*  completes. In the end resets index to point to the start of the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SendSequence(void) CYREENTRANT
{
    /* Send command pattern to LCD */
    (void) `$INSTANCE_NAME`_MasterWriteBuf(`$INSTANCE_NAME`_address,
                                           `$INSTANCE_NAME`_buff,
                                           `$INSTANCE_NAME`_buffIndex,
                                           `$INSTANCE_NAME`_MODE_COMPLETE_XFER);

    while(0u == (`$INSTANCE_NAME`_MasterReadStatus() & `$INSTANCE_NAME`_WRITE_COMPLETE))
    {
        /* Wait until I2C Master finishes transaction */
    }

    /* Reset buffer index */
    `$INSTANCE_NAME`_buffIndex = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleCustomCommand
********************************************************************************
*
* Summary:
*  This command adds a support of sending custom commands with parameters.
*
* Parameters:
*  uint8 cmdId: Command code.
*  uint8 dataLength: The length of data to be send for this command.
*  uint8 cmdData[]: The data to be send to I2C LCD.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_HandleCustomCommand(uint8 cmdId, uint8 dataLength, uint8 const cmdData[])
                                                        `=ReentrantKeil($INSTANCE_NAME . "_HandleCustomCommand")`
{
    uint8 i;
    uint8 ch;
    uint8 cmdIndx = 0u;
    
    while(cmdIndx < `$INSTANCE_NAME`_NUM_COMMANDS)
    {   
        if (cmdId == `$INSTANCE_NAME`_cmdPatt[cmdIndx][`$INSTANCE_NAME`_COMMAND_BYTE_INDEX])
        {
             /* Write control pattern for specific command */
            `$INSTANCE_NAME`_WrCntrlPatt(cmdIndx);

            for(i = 0u; i < dataLength; i++)
            {
                /* Get next byte from array of data */
                ch = cmdData[i];

                /* Add current byte to buffer */
                `$INSTANCE_NAME`_WrDataToBuff((uint8) ch);
            }

            /* Send data to LCD and wait when transaction completes */
            `$INSTANCE_NAME`_SendSequence();
            /* The command index was found - break while() loop */
            break;
        }
        /* Increment command pattern index */
        cmdIndx++;
    } 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleOneByteCommand
********************************************************************************
*
* Summary:
*  This command adds a support of sending custom commands with 1 byte parameter.
*
* Parameters:
*  uint8 cmdId: Command code.
*  uint8 cmdByte: One byte of data to be send to I2C LCD.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_HandleOneByteCommand(uint8 cmdId, uint8 cmdByte)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_HandleOneByteCommand")`
{
    uint8 oneByteArray[`$INSTANCE_NAME`_ONE_BYTE_LEN];
    
    oneByteArray[0u] = cmdByte;
    
    `$INSTANCE_NAME`_HandleCustomCommand(cmdId, `$INSTANCE_NAME`_ONE_BYTE_LEN, oneByteArray);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PrintString
********************************************************************************
*
* Summary:
*  Write a null-terminated string of characters to the screen beginning at the
*  current cursor location.
*
* Parameters:
*  string:  Null-terminated array of ASCII characters to be displayed on the LCD
*           module's screen.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PrintString(char8 const string[]) `=ReentrantKeil($INSTANCE_NAME . "_PrintString")`
{
    uint8 chIdx = 1u;
    char8 current = *string;

    /* Send required control byte value to address data register */
    `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_WRITE_DATA_IDX);

    /* Until null is reached, put next character into buffer */
    while((char8) '\0' != current)
    {
        /* Add current byte to buffer */
        #if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
            /* In case of NXP PCF2119x, LCD modules use character set "S"
            * (see LCD's module datasheet) that has English letters located in
            * "extended" area (ASCII code > 128) so it is required to handle
            * that. But the first eight generated character are exceptions.
            */
            if(((char8)(`$INSTANCE_NAME`_CUSTOM_CHAR_NUM)) > current)
            {
                `$INSTANCE_NAME`_WrDataToBuff((uint8) current);
            }
            else
            {
                `$INSTANCE_NAME`_WrDataToBuff(((uint8) current) ^ `$INSTANCE_NAME`_CHARACTER_SET_S_MASK);
            }
        #else
            `$INSTANCE_NAME`_WrDataToBuff((uint8) current);
        #endif /* ((`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) && \
               * (`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE))
               */

        /* Get next byte from string */
        current = string[chIdx];
        chIdx++;
    }

    /* Send data to LCD and wait when transaction completes */
    `$INSTANCE_NAME`_SendSequence();
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_PutChar
********************************************************************************
*
* Summary:
*  Writes an individual character to the screen at the current cursor location.
*  Used to display custom characters through their named values.
*  (I2C_LCD_CUSTOM_0 through I2C_LCD_CUSTOM_7).
*
* Parameters:
*  character:  An ASCII character to be displayed on the LCD module's screen.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PutChar(char8 character) `=ReentrantKeil($INSTANCE_NAME . "_PutChar")`
{
    /* Send one byte of data with I2C_LCD_WriteData() */
    #if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
        /* In case of NXP PCF2119x, the LCD modules use character set "S"
        * (see LCD's module datasheet) that has English letters located in
        * "extended" area (ASCII code > 128) so it is required to handle
        * that. But the first eight generated character are exceptions.
        */
        if(((char8) (`$INSTANCE_NAME`_CUSTOM_CHAR_NUM)) >  character)
        {
            `$INSTANCE_NAME`_WriteData((uint8) character);
        }
        else
        {
            `$INSTANCE_NAME`_WriteData(((uint8) character) ^ `$INSTANCE_NAME`_CHARACTER_SET_S_MASK);
        }
    #else
        `$INSTANCE_NAME`_WriteData((uint8) character);
    #endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) */
}


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
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PrintInt8(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt8")`
{
    static char8 const CYCODE `$INSTANCE_NAME`_hex[16u] = "0123456789ABCDEF";

    /* Send required control byte value to address data register */
    `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_WRITE_DATA_IDX);

    /* Add current byte to buffer */
    #if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
        /* In case of NXP PCF2119x, LCD modules use character set "S"
        * (see LCD's module datasheet) that has English letters located in
        * "extended" area (ASCII code > 128) so it is required to handle
        * that.
        */
        `$INSTANCE_NAME`_WrDataToBuff(((uint8) `$INSTANCE_NAME`_hex[value >> `$INSTANCE_NAME`_BYTE_UPPER_NIBBLE_SHIFT])
                                               ^ `$INSTANCE_NAME`_CHARACTER_SET_S_MASK );
        `$INSTANCE_NAME`_WrDataToBuff(((uint8) `$INSTANCE_NAME`_hex[value & `$INSTANCE_NAME`_BYTE_LOWER_NIBBLE_MASK]) ^
                                               `$INSTANCE_NAME`_CHARACTER_SET_S_MASK);
    #else
        `$INSTANCE_NAME`_WrDataToBuff((uint8) `$INSTANCE_NAME`_hex[value >> `$INSTANCE_NAME`_BYTE_UPPER_NIBBLE_SHIFT]);
        `$INSTANCE_NAME`_WrDataToBuff((uint8) `$INSTANCE_NAME`_hex[value & `$INSTANCE_NAME`_BYTE_LOWER_NIBBLE_MASK]);
    #endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) */

    /* Send data to LCD and wait when transaction complete */
    `$INSTANCE_NAME`_SendSequence();
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_PrintInt16
********************************************************************************
*
* Summary:
*  Print a uint16 as four ASCII characters.
*
* Parameters:
*  value:   The uint16 to be printed out as ASCII characters.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PrintInt16(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt16")`
{
    `$INSTANCE_NAME`_PrintInt8((uint8)(value >> `$INSTANCE_NAME`_U16_UPPER_BYTE_SHIFT));
    `$INSTANCE_NAME`_PrintInt8((uint8)(value & `$INSTANCE_NAME`_U16_LOWER_BYTE_MASK));
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_PrintNumber
********************************************************************************
*
* Summary:
*  Print a uint16 value as a left-justified decimal value.
*
* Parameters:
*  value:  The byte to be printed out as ASCII characters.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_PrintNumber(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintNumber")`
{
    char8 number[`$INSTANCE_NAME`_NUMBER_OF_REMAINDERS];
    char8 temp[`$INSTANCE_NAME`_NUMBER_OF_REMAINDERS];

    uint8 digIndex = 0u;
    uint8 numDigits;

    /* Load these in reverse order */
    while(value >= `$INSTANCE_NAME`_TEN)
    {
        temp[digIndex] = (value % `$INSTANCE_NAME`_TEN) + '0';
        value /= `$INSTANCE_NAME`_TEN;
        digIndex++;
    }

    temp[digIndex] = (value % `$INSTANCE_NAME`_TEN) + '0';
    numDigits = digIndex;

    /* While index is greater than or equal to zero copy number
    * from temporary array to number[].
    */
    while (digIndex != 0u)
    {
        number[numDigits - digIndex] = temp[digIndex];
        digIndex--;
    }

    /* Copy last digit */
    number[numDigits] = temp[0u];

    /* Null Termination */
    number[numDigits + 1u] = (char8) '\0';

    /* Print out number */
    `$INSTANCE_NAME`_PrintString(&number[0u]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAddr
********************************************************************************
*
* Summary:
*  This function allows the user to change the default I2C address of the LCD.
*  This function is not used for designs with a single LCD. Systems that have 2
*  or more LCDs on a single I2C bus, use this function to select which LCD to
*  communicate. A uint8 variable `$INSTANCE_NAME`_address, will be will be set
*  to the "address" parameter and be used for all further communication until
*  it is changed to a new address.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAddr(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetAddr")`
{
    #if(`$INSTANCE_NAME`_IS_SCB_MASTER_USED)
        `$INSTANCE_NAME`_address = ((uint32) address >> `$INSTANCE_NAME`_ADDRESS_SHIFT);
    #else
        `$INSTANCE_NAME`_address = ((uint8) address >> `$INSTANCE_NAME`_ADDRESS_SHIFT);
    #endif /* (`$INSTANCE_NAME`_IS_SCB_MASTER_USED) */
}


#if (`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_LoadCustomFonts
    ********************************************************************************
    *
    * Summary:
    *  Loads 8 custom font characters into the LCD Module for use.  Cannot use
    *  characters from two different font sets at once, but font sets can be
    *  switched out during runtime.
    *
    * Parameters:
    *  customData:  The pointer to a constant array of 64 bytes representing 
    *               8 custom font characters.
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    * Theory:
    *  Prior to using this function user need to import the pointer to custom
    *  font array to your project by writing the following in the source code file
    *  where custom font will be used:
    *       extern uint8 const CYCODE LCD_Char_customFonts[];
    *  This function is not automatically called by the Start() routine and must be
    *  called manually by the user.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_LoadCustomFonts(uint8 const customData[])
                                                            `=ReentrantKeil($INSTANCE_NAME . "_LoadCustomFonts")`
    {
        uint8 i;

        #if (`$INSTANCE_NAME`_COMMAND_FORMAT != `$INSTANCE_NAME`_NXP_PCF2119X)
            uint8 addrOffset = 0u;
            uint8 count = 0u;
        #endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT != `$INSTANCE_NAME`_NXP_PCF2119X) */

        #if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
            /* Set starting address in LCD Module as it is location of CGRAM */
            `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_CGRAM_0);

            /* Set Control pattern for data writing */
            `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_WRITE_DATA_IDX);

            /* Load in 64 bytes of CustomChar Data */
            for(i = 0u; i < `$INSTANCE_NAME`_CUSTOM_CHAR_SET_LEN; i++)
            {
                /* Variable 'i' defines character ID (character address) */
                `$INSTANCE_NAME`_WrDataToBuff(customData[i]);
            }

            /* Send data to LCD and wait when transaction completes */
            `$INSTANCE_NAME`_SendSequence();
            
            /* Set the LCD modules address register back to the start of the data RAM */
            `$INSTANCE_NAME`_Position(0u ,0u);
        #else
            while(addrOffset < `$INSTANCE_NAME`_CUSTOM_CHAR_SET_LEN)
            {
                /* Set starting address in LCD Module as it is location of CGRAM. */
                `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_CGRAM_0_IDX);
                
                /* Variable 'i' defines character ID (character address) */
                `$INSTANCE_NAME`_WrDataToBuff(count);
                
                /* Increment count (actually means to increment custom character address) */
                count++;
                
                for(i = 0u; i < `$INSTANCE_NAME`_CHARACTER_HEIGHT; i++)
                {
                    `$INSTANCE_NAME`_WrDataToBuff(customData[addrOffset + i]);
                }

                /* Send data to LCD and wait when transaction complete */
                `$INSTANCE_NAME`_SendSequence();
                
                /* Calculate next offset value */
                addrOffset += `$INSTANCE_NAME`_CHARACTER_HEIGHT;
            }
        #endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT != `$INSTANCE_NAME`_NXP_PCF2119X) */
    }

#endif /* `$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_NONE */


#if((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) || \
                (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG))

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DrawHorizontalBG
    ********************************************************************************
    *
    * Summary:
    *  Draws the horizontal bargraph.
    *
    * Parameters:
    *  row:            The row in which the bar graph starts.
    *  column:         The column in which the bar graph starts.
    *  maxCharacters:  The max length of the graph in whole characters.
    *  value:          The current length or height of the graph in pixels.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value) \
                                                            `=ReentrantKeil($INSTANCE_NAME . "_DrawHorizontalBG")`
    {
        /* 8-bit Counter */
        uint8 count8;
        uint8 fullChars;
        uint8 remainingPixels;

        /* Number of full characters to draw */
        fullChars = value / `$INSTANCE_NAME`_CHARACTER_WIDTH;

        /* Number of remaining pixels to draw */
        remainingPixels = value % `$INSTANCE_NAME`_CHARACTER_WIDTH;

        /* Ensure that maximum character limit is followed. */
        if(fullChars >= maxCharacters)
        {
            fullChars = maxCharacters;
        }

        /* Put Cursor at start position */
        `$INSTANCE_NAME`_Position(row, column);

        /* Set Control pattern for data writing */
        `$INSTANCE_NAME`_WrCntrlPatt(`$INSTANCE_NAME`_WRITE_DATA_IDX);

        /* Write full characters */
        for(count8 = 0u; count8 < fullChars; count8++)
        {
            `$INSTANCE_NAME`_WrDataToBuff(`$INSTANCE_NAME`_CUSTOM_5);
        }

        if(fullChars < maxCharacters)
        {
            /* Write remaining pixels */
            `$INSTANCE_NAME`_WrDataToBuff(remainingPixels);

            if(fullChars < (maxCharacters - 1u))
            {
                /* Fill with whitespace to end of bar graph */
                for(count8 = 0u; count8 < (maxCharacters - fullChars - 1u); count8++)
                {
                    `$INSTANCE_NAME`_WrDataToBuff(`$INSTANCE_NAME`_CUSTOM_0);
                }
            }
        }

        /* Send data to LCD and wait when transaction complete */
        `$INSTANCE_NAME`_SendSequence();
    }


    /*******************************************************************************
    *  Function Name: `$INSTANCE_NAME`_DrawVerticalBG
    ********************************************************************************
    *
    * Summary:
    *  Draws the vertical bargraph.
    *
    * Parameters:
    *  row:            The row in which the bar graph starts.
    *  column:         The column in which the bar graph starts.
    *  maxCharacters:  The max height of the graph in whole characters.
    *  value:          The current length or height of the graph in pixels.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_DrawVerticalBG")`
    {
        /* 8-bit Counter */
        uint8 count8 = 0u;
        /* Current Row Tracker */
        int8 currentRow;
        uint8 fullChars;
        uint8 remainingPixels;

        /* Number of full characters to draw */
        fullChars = value / `$INSTANCE_NAME`_CHARACTER_HEIGHT;

        /* Number of remaining pixels to draw */
        remainingPixels = value % `$INSTANCE_NAME`_CHARACTER_HEIGHT;

        /* Put Cursor at start position */
        `$INSTANCE_NAME`_Position(row, column);

        /* Make sure the bar graph fits inside the space allotted */
        if(fullChars >= maxCharacters)
        {
            fullChars = maxCharacters;
        }

        /*  Write full characters */
        while(count8 < fullChars)
        {
            `$INSTANCE_NAME`_WriteData(`$INSTANCE_NAME`_CUSTOM_7);

            count8++;

            /* Each pass through, move one row higher */
            if((((int8) row) - ((int8) count8)) >= 0)
            {
                `$INSTANCE_NAME`_Position(row - count8, column);
            }
            else
            {
                break;
            }
        }

        if(((((int8) row) - ((int8) count8)) >= 0) && (fullChars < maxCharacters))
        {
            /* Write remaining pixels */
            if(remainingPixels == 0u)
            {
                `$INSTANCE_NAME`_WriteData((uint8) ' ');
            }
            else
            {
                `$INSTANCE_NAME`_WriteData(remainingPixels - 1u);
            }

            currentRow = ((int8) row) - ((int8) count8) - 1;

            if(currentRow >= 0)
            {
                /* Move up one row and fill with white space till top of bar graph */
                for(count8 = 0u; count8 < (maxCharacters - fullChars - 1u); count8++)
                {
                    `$INSTANCE_NAME`_Position((uint8)currentRow, column);
                    `$INSTANCE_NAME`_WriteData((uint8) ' ');
                    currentRow --;
                }
            }
        }
    }

#endif /* ((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) || \
                (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG)) */


#if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SendCmd
    ********************************************************************************
    *
    * Summary:
    *  This function used to send the specific for NXP PCF2119X commands that are 
    *  used to configure the LCD panel.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SendCmd(uint8 cmd) CYREENTRANT
    {
        `$INSTANCE_NAME`_buff[0u] = `$INSTANCE_NAME`_COMMAND_SEND;
        `$INSTANCE_NAME`_buff[1u] = cmd;
        `$INSTANCE_NAME`_buffIndex = `$INSTANCE_NAME`_LENGTH_2_BYTES;
        
        `$INSTANCE_NAME`_SendSequence();
    }

#endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) */

/* [] END OF FILE */
