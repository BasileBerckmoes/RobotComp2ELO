/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains registers and constants associated with the
*  I2C LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_LCD_`$INSTANCE_NAME`_H)
#define CY_I2C_LCD_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"

#include "`$I2cMasterInstanceName`.h"

#if defined(`$I2cMasterInstanceName`_SCB_MODE)
    #include "`$I2cMasterInstanceName`_I2C.h"
#endif /* I2C_M_SCB_MODE */


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* This condition checks if I2C Master implemented on SCB
* block. There is mismatch in function names between I2C Master that is
* implemented on SCB and I2C Master that is implemented on UDB.
*/
#if defined(`$I2cMasterInstanceName`_SCB_MODE)
    /* In this case always returns - "true" */
    #define `$INSTANCE_NAME`_IS_SCB_MASTER_USED     (0x01u == 0x01u)
#else
    /* Always "false" */
    #define `$INSTANCE_NAME`_IS_SCB_MASTER_USED     (0x01u == 0x00u)
#endif /* I2C_M_SCB_MODE */

#define `$INSTANCE_NAME`_CUSTOM_CHAR_SET            (`$CharSetValue`)

/* Custom character set types */
#define `$INSTANCE_NAME`_NONE                       (0u)    /* No Custom Fonts      */
#define `$INSTANCE_NAME`_HORIZONTAL_BG              (1u)    /* Horizontal Bar Graph */
#define `$INSTANCE_NAME`_VERTICAL_BG                (2u)    /* Vertical Bar Graph   */
#define `$INSTANCE_NAME`_USER_DEFINED               (3u)    /* User Defined Fonts   */

#define `$INSTANCE_NAME`_COMMAND_FORMAT             (`$CommandFormat`u)

/* Possible command format values */
#define `$INSTANCE_NAME`_NXP_PCF2119X               (0x00u)
#define `$INSTANCE_NAME`_CUSTOM                     (0x01u)

/********************
* Generated Code
********************/
/* Indexes of command patterns in the look-up array. Required for a quick 
* access for the command.
*/
`$CommandDefines`


/***************************************
*        Function Prototypes
***************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_WriteControl(uint8 cByte) `=ReentrantKeil($INSTANCE_NAME . "_WriteControl")`;
void `$INSTANCE_NAME`_WriteData(uint8 dByte) `=ReentrantKeil($INSTANCE_NAME . "_WriteData")`;
void `$INSTANCE_NAME`_PrintString(char8 const string[]) `=ReentrantKeil($INSTANCE_NAME . "_PrintString")`;
void `$INSTANCE_NAME`_Position(uint8 row, uint8 column) `=ReentrantKeil($INSTANCE_NAME . "_Position")`;
void `$INSTANCE_NAME`_PutChar(char8 character) `=ReentrantKeil($INSTANCE_NAME . "_PutChar")`;
void `$INSTANCE_NAME`_SetAddr(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetAddr")`;
void `$INSTANCE_NAME`_HandleCustomCommand(uint8 cmdId, uint8 dataLength, uint8 const cmdData[])
                                            `=ReentrantKeil($INSTANCE_NAME . "_HandleCustomCommand")`;
void `$INSTANCE_NAME`_HandleOneByteCommand(uint8 cmdId, uint8 cmdByte)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_HandleOneByteCommand")`;
/* ASCII Conversion Routines */
void `$INSTANCE_NAME`_PrintInt8(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt8")`;
void `$INSTANCE_NAME`_PrintInt16(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt16")`;
void `$INSTANCE_NAME`_PrintNumber(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintNumber")`;

#if((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) || \
                (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG))

    void  `$INSTANCE_NAME`_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         `=ReentrantKeil($INSTANCE_NAME . "_DrawHorizontalBG")`;

    void `$INSTANCE_NAME`_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        `=ReentrantKeil($INSTANCE_NAME . "_DrawVerticalBG")`;

#endif /* ((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) ||
       * (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG))
       */

#if(`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE)

    void `$INSTANCE_NAME`_LoadCustomFonts(uint8 const customData[])
                            `=ReentrantKeil($INSTANCE_NAME . "_LoadCustomFonts")`;

#endif /* ((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_USER_DEFINED) */


/***************************************
*        Macros
***************************************/

/* Clear Macro */
#define `$INSTANCE_NAME`_ClearDisplay()            `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_CLEAR_DISPLAY)
/* Off Macro */
#define `$INSTANCE_NAME`_DisplayOff()              `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_CURSOR_OFF)
/* On Macro */
#define `$INSTANCE_NAME`_DisplayOn()               `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_ON_CURSOR_OFF)

/* Function-like macros for handling I2C MAster API names on SCB and UDB */
#if(`$INSTANCE_NAME`_IS_SCB_MASTER_USED)
    #define `$INSTANCE_NAME`_MasterWriteBuf(slaveAddress, wrData, cnt, mode)  \
                                `$I2cMasterInstanceName`_I2CMasterWriteBuf(slaveAddress, wrData, cnt, mode)

    #define `$INSTANCE_NAME`_MasterReadStatus()     `$I2cMasterInstanceName`_I2CMasterStatus()
#else
    #define `$INSTANCE_NAME`_MasterWriteBuf(slaveAddress, wrData, cnt, mode)  \
                                `$I2cMasterInstanceName`_MasterWriteBuf(slaveAddress, wrData, cnt, mode)

    #define `$INSTANCE_NAME`_MasterReadStatus()     `$I2cMasterInstanceName`_MasterStatus()
#endif /* `$INSTANCE_NAME`_IS_SCB_MASTER_USED */


#define `$INSTANCE_NAME`_AddrStart(addr) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_Start();\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrStop(addr) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_Stop(); \
                                                }while(0)

#define `$INSTANCE_NAME`_AddrDisplayOn(addr) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_DisplayOn();\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrDisplayOff(addr) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_DisplayOff();\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrPrintString(addr, str) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_PrintString(str);\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrPutChar(addr, ch) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_PutChar(ch);\
                                               }while(0)

#define `$INSTANCE_NAME`_AddrPosition(addr, row, col) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_Position(row, col);\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrWriteData(addr, dByte) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_WriteData(dByte);\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrWriteControl(addr, cByte) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_WriteControl(cByte);\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrClearDisplay(addr) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_ClearDisplay();\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrEnable(addr) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr); \
                                                    `$INSTANCE_NAME`_Enable();\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrPrintInt8(addr, value) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr); \
                                                    `$INSTANCE_NAME`_PrintInt8(value);\
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_AddrPrintInt16(addr, value) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr); \
                                                    `$INSTANCE_NAME`_PrintInt16(value);\
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_AddrPrintNumber(addr, value) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr); \
                                                    `$INSTANCE_NAME`_PrintNumber(value);\
                                                }while(0)

#if(`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE)

    #define `$INSTANCE_NAME`_AddrLoadCustomFonts(addr, customFont) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_LoadCustomFonts(customFont);\
                                                }while(0)

#endif /* (`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE) */


#if((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) || \
                (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG))

    #define `$INSTANCE_NAME`_AddrDrawHorizontalBG(addr, row, column, maxCharacters, value) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_DrawHorizontalBG(row,column,maxCharacters,value);\
                                                }while(0)


    #define `$INSTANCE_NAME`_AddrDrawVerticalBG(addr, row, column, maxCharacters, value) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_DrawVerticalBG(row, column, maxCharacters, value);\
                                                }while(0)

#endif /* ((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) ||
       * (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG))
       */

#define `$INSTANCE_NAME`_AddrHandleCustomCommand(addr, cmdId, dataLength, cmdData) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_HandleCustomCommand(cmdId, dataLength, cmdData);\
                                                }while(0)

#define `$INSTANCE_NAME`_AddrHandleOneByteCommand(addr, cmdId, cmdByte) \
                                                do {\
                                                    `$INSTANCE_NAME`_SetAddr(addr);\
                                                    `$INSTANCE_NAME`_HandleOneByteCommand(cmdId, cmdByte);\
                                                }while(0)

/********************
* Generated Code
********************/
`$HandleCustomCmdDefines`


/***************************************
*           Global Variables
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;
extern uint8 const CYCODE `$INSTANCE_NAME`_customFonts[64u];


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_ADDRESS_SHIFT              (0x01u)

/* Default I2C address in 7-bit mode */
#define `$INSTANCE_NAME`_DEFAULT_I2C_ADDRESS        ((uint8)((uint8)(`$DefaultI2cAddress`u) >> \
                                                                            `$INSTANCE_NAME`_ADDRESS_SHIFT))

/* This value should be generated by API customizer */
#define `$INSTANCE_NAME`_NUM_COMMANDS               (`$UsedCommandCount`)

/********************
* Generated Code
********************/
/* Legacy names from Character LCD */
`$IndexDefines`

#define `$INSTANCE_NAME`_DISPLAY_2_LINES_5x10       (`$INSTANCE_NAME`_DISPLAY_2_LINES_5X10)
#define `$INSTANCE_NAME`_CURSOR_AUTO_INCR_ON        (`$INSTANCE_NAME`_CURSOR_RIGHT)

/********************
* Generated Code
********************/
`$LenDefines`

#if(`$INSTANCE_NAME`_IS_SCB_MASTER_USED)
    #define `$INSTANCE_NAME`_MODE_COMPLETE_XFER         (`$I2cMasterInstanceName`_I2C_MODE_COMPLETE_XFER)
    #define `$INSTANCE_NAME`_WRITE_COMPLETE             (`$I2cMasterInstanceName`_I2C_MSTAT_WR_CMPLT)
#else
    #define `$INSTANCE_NAME`_MODE_COMPLETE_XFER         (`$I2cMasterInstanceName`_MODE_COMPLETE_XFER)
    #define `$INSTANCE_NAME`_WRITE_COMPLETE             (`$I2cMasterInstanceName`_MSTAT_WR_CMPLT)
#endif /* `$INSTANCE_NAME`_IS_SCB_MASTER_USED */

/* Constants for PrintNumber routine */
#define `$INSTANCE_NAME`_NUMBER_OF_REMAINDERS           (0x05u)
#define `$INSTANCE_NAME`_TEN                            (0x0Au)

/* Nibble Offset and Mask */
#define `$INSTANCE_NAME`_NIBBLE_SHIFT                   (0x04u)
#define `$INSTANCE_NAME`_NIBBLE_MASK                    (0x0Fu)
#define `$INSTANCE_NAME`_BUFF_SIZE                      (0x100u)
#define `$INSTANCE_NAME`_LENGTH_2_BYTES                 (0x02u)
#define `$INSTANCE_NAME`_COMMAND_BYTE_INDEX             (0x02u)

/* Delay value required for some commands to execute */
#define `$INSTANCE_NAME`_CMOMMAND_DELAY                 (1500u)

/* LCD Module RAM Address Constants */
#if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
    #define `$INSTANCE_NAME`_ROW_0_START                    (0x80u)
    #define `$INSTANCE_NAME`_ROW_1_START                    (0xC0u)
    #define `$INSTANCE_NAME`_ROW_2_START                    (0x94u)
    #define `$INSTANCE_NAME`_ROW_3_START                    (0xD4u)
#else
    #define `$INSTANCE_NAME`_ROW_0_START                    (0x00u)
    #define `$INSTANCE_NAME`_ROW_1_START                    (0x40u)
    #define `$INSTANCE_NAME`_ROW_2_START                    (0x14u)
    #define `$INSTANCE_NAME`_ROW_3_START                    (0x54u)
#endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)  */

/* Custom character handling related constants */
#if(`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE)
    #define `$INSTANCE_NAME`_CHARACTER_WIDTH                (0x05u)
    #define `$INSTANCE_NAME`_CHARACTER_HEIGHT               (0x08u)
    #define `$INSTANCE_NAME`_CUSTOM_CHAR_SET_LEN            (0x40u)
#endif /* (`$INSTANCE_NAME`_CUSTOM_CHAR_SET != `$INSTANCE_NAME`_NONE) */

#define `$INSTANCE_NAME`_CUSTOM_CHAR_NUM                (0x08u)

#define `$INSTANCE_NAME`_ONE_BYTE_LEN                   (0x01u)

/* Other constants */
#define `$INSTANCE_NAME`_BYTE_UPPER_NIBBLE_SHIFT        (0x04u)
#define `$INSTANCE_NAME`_BYTE_LOWER_NIBBLE_MASK         (0x0Fu)
#define `$INSTANCE_NAME`_U16_UPPER_BYTE_SHIFT           (0x08u)
#define `$INSTANCE_NAME`_U16_LOWER_BYTE_MASK            (0xFFu)
                                                    
/* Custom Character References */
#define `$INSTANCE_NAME`_CUSTOM_0                       (0x00u)
#define `$INSTANCE_NAME`_CUSTOM_1                       (0x01u)
#define `$INSTANCE_NAME`_CUSTOM_2                       (0x02u)
#define `$INSTANCE_NAME`_CUSTOM_3                       (0x03u)
#define `$INSTANCE_NAME`_CUSTOM_4                       (0x04u)
#define `$INSTANCE_NAME`_CUSTOM_5                       (0x05u)
#define `$INSTANCE_NAME`_CUSTOM_6                       (0x06u)
#define `$INSTANCE_NAME`_CUSTOM_7                       (0x07u)

#if (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X)
    
    /* Command send opcode */
    #define `$INSTANCE_NAME`_COMMAND_SEND               (0x00u) 
    
    #define `$INSTANCE_NAME`_SET_EXTENDED_FUNC          (0x35u)      
    #define `$INSTANCE_NAME`_SPLIT_SCREEN               (0x02u)
    #define `$INSTANCE_NAME`_DISP_CONF                  (0x04u)
    
    #define `$INSTANCE_NAME`_ICON_CTL                   (0x08u)  
    #define `$INSTANCE_NAME`_VLCD_SET                   (0xA0u)
    #define `$INSTANCE_NAME`_FUNCTION_SET_STANDARD      (0x34u)  /* Select Standard Instruction set, 2x16 display */

    /* This is mask for character set "S" that is used in NXP
    * compatible LCD Module.
    */
    #define `$INSTANCE_NAME`_CHARACTER_SET_S_MASK       ((uint8) (0x80u))
    
#endif /* (`$INSTANCE_NAME`_COMMAND_FORMAT == `$INSTANCE_NAME`_NXP_PCF2119X) */


#endif /* CY_I2C_LCD_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
