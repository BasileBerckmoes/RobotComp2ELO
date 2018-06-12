/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_`$INSTANCE_NAME`_H)
#define CY_CHARLCD_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_CONVERSION_ROUTINES     (`$ConversionRoutines_DEF`u)
#define `$INSTANCE_NAME`_CUSTOM_CHAR_SET         (`$CustomCharDefines_API_GEN`u)

/* Custom character set types */
#define `$INSTANCE_NAME`_NONE                     (0u)    /* No Custom Fonts      */
#define `$INSTANCE_NAME`_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define `$INSTANCE_NAME`_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define `$INSTANCE_NAME`_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


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
void `$INSTANCE_NAME`_IsReady(void) `=ReentrantKeil($INSTANCE_NAME . "_IsReady")`;
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;

#if((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) || \
                (`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_HORIZONTAL_BG))

    void  `$INSTANCE_NAME`_LoadCustomFonts(uint8 const customData[])
                        `=ReentrantKeil($INSTANCE_NAME . "_LoadCustomFonts")`;

    void  `$INSTANCE_NAME`_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         `=ReentrantKeil($INSTANCE_NAME . "_DrawHorizontalBG")`;

    void `$INSTANCE_NAME`_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        `=ReentrantKeil($INSTANCE_NAME . "_DrawVerticalBG")`;

#endif /* ((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_VERTICAL_BG) */

#if(`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_USER_DEFINED)

    void `$INSTANCE_NAME`_LoadCustomFonts(uint8 const customData[])
                            `=ReentrantKeil($INSTANCE_NAME . "_LoadCustomFonts")`;

#endif /* ((`$INSTANCE_NAME`_CUSTOM_CHAR_SET == `$INSTANCE_NAME`_USER_DEFINED) */

#if(`$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void `$INSTANCE_NAME`_PrintInt8(uint8 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt8")`;
    void `$INSTANCE_NAME`_PrintInt16(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt16")`;
    void `$INSTANCE_NAME`_PrintInt32(uint32 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintInt32")`;
    void `$INSTANCE_NAME`_PrintNumber(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintNumber")`; 
    void `$INSTANCE_NAME`_PrintU32Number(uint32 value) `=ReentrantKeil($INSTANCE_NAME . "_PrintU32Number")`;
    
#endif /* `$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define `$INSTANCE_NAME`_ClearDisplay() `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_CLEAR_DISPLAY)

/* Off Macro */
#define `$INSTANCE_NAME`_DisplayOff() `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_CURSOR_OFF)

/* On Macro */
#define `$INSTANCE_NAME`_DisplayOn() `$INSTANCE_NAME`_WriteControl(`$INSTANCE_NAME`_DISPLAY_ON_CURSOR_OFF)

#define `$INSTANCE_NAME`_PrintNumber(value) `$INSTANCE_NAME`_PrintU32Number((uint16) (value))


/***************************************
*           Global Variables
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;
extern uint8 `$INSTANCE_NAME`_enableState;
extern uint8 const CYCODE `$INSTANCE_NAME`_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define `$INSTANCE_NAME`_DISPLAY_8_BIT_INIT       (0x03u)
#define `$INSTANCE_NAME`_DISPLAY_4_BIT_INIT       (0x02u)
#define `$INSTANCE_NAME`_DISPLAY_CURSOR_OFF       (0x08u)
#define `$INSTANCE_NAME`_CLEAR_DISPLAY            (0x01u)
#define `$INSTANCE_NAME`_CURSOR_AUTO_INCR_ON      (0x06u)
#define `$INSTANCE_NAME`_DISPLAY_CURSOR_ON        (0x0Eu)
#define `$INSTANCE_NAME`_DISPLAY_2_LINES_5x10     (0x2Cu)
#define `$INSTANCE_NAME`_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define `$INSTANCE_NAME`_RESET_CURSOR_POSITION    (0x03u)
#define `$INSTANCE_NAME`_CURSOR_WINK              (0x0Du)
#define `$INSTANCE_NAME`_CURSOR_BLINK             (0x0Fu)
#define `$INSTANCE_NAME`_CURSOR_SH_LEFT           (0x10u)
#define `$INSTANCE_NAME`_CURSOR_SH_RIGHT          (0x14u)
#define `$INSTANCE_NAME`_DISPLAY_SCRL_LEFT        (0x18u)
#define `$INSTANCE_NAME`_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define `$INSTANCE_NAME`_CURSOR_HOME              (0x02u)
#define `$INSTANCE_NAME`_CURSOR_LEFT              (0x04u)
#define `$INSTANCE_NAME`_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define `$INSTANCE_NAME`_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define `$INSTANCE_NAME`_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define `$INSTANCE_NAME`_CHARACTER_WIDTH          (0x05u)
#define `$INSTANCE_NAME`_CHARACTER_HEIGHT         (0x08u)

#if(`$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u)
    #define `$INSTANCE_NAME`_NUMBER_OF_REMAINDERS_U32 (0x0Au)
    #define `$INSTANCE_NAME`_TEN                      (0x0Au)
    #define `$INSTANCE_NAME`_8_BIT_SHIFT              (8u)
    #define `$INSTANCE_NAME`_32_BIT_SHIFT             (32u)
    #define `$INSTANCE_NAME`_ZERO_CHAR_ASCII          (48u)
#endif /* `$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define `$INSTANCE_NAME`_NIBBLE_SHIFT             (0x04u)
#define `$INSTANCE_NAME`_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define `$INSTANCE_NAME`_ROW_0_START              (0x80u)
#define `$INSTANCE_NAME`_ROW_1_START              (0xC0u)
#define `$INSTANCE_NAME`_ROW_2_START              (0x94u)
#define `$INSTANCE_NAME`_ROW_3_START              (0xD4u)

/* Custom Character References */
#define `$INSTANCE_NAME`_CUSTOM_0                 (0x00u)
#define `$INSTANCE_NAME`_CUSTOM_1                 (0x01u)
#define `$INSTANCE_NAME`_CUSTOM_2                 (0x02u)
#define `$INSTANCE_NAME`_CUSTOM_3                 (0x03u)
#define `$INSTANCE_NAME`_CUSTOM_4                 (0x04u)
#define `$INSTANCE_NAME`_CUSTOM_5                 (0x05u)
#define `$INSTANCE_NAME`_CUSTOM_6                 (0x06u)
#define `$INSTANCE_NAME`_CUSTOM_7                 (0x07u)

/* Other constants */
#define `$INSTANCE_NAME`_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define `$INSTANCE_NAME`_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define `$INSTANCE_NAME`_U16_UPPER_BYTE_SHIFT     (0x08u)
#define `$INSTANCE_NAME`_U16_LOWER_BYTE_MASK      (0xFFu)
#define `$INSTANCE_NAME`_CUSTOM_CHAR_SET_LEN      (0x40u)

#define `$INSTANCE_NAME`_LONGEST_CMD_US           (0x651u)
#define `$INSTANCE_NAME`_WAIT_CYCLE               (0x10u)
#define `$INSTANCE_NAME`_READY_DELAY              ((`$INSTANCE_NAME`_LONGEST_CMD_US * 4u)/(`$INSTANCE_NAME`_WAIT_CYCLE))


/***************************************
*             Registers
***************************************/

/* Device specific registers */
#if (CY_PSOC4)

    #define `$INSTANCE_NAME`_PORT_DR_REG           (*(reg32 *) `$INSTANCE_NAME`_LCDPort__DR)  /* Data Output Register */
    #define `$INSTANCE_NAME`_PORT_DR_PTR           ( (reg32 *) `$INSTANCE_NAME`_LCDPort__DR)
    #define `$INSTANCE_NAME`_PORT_PS_REG           (*(reg32 *) `$INSTANCE_NAME`_LCDPort__PS)  /* Pin State Register */
    #define `$INSTANCE_NAME`_PORT_PS_PTR           ( (reg32 *) `$INSTANCE_NAME`_LCDPort__PS)
    
    #define `$INSTANCE_NAME`_PORT_PC_REG           (*(reg32 *) `$INSTANCE_NAME`_LCDPort__PC)
    #define `$INSTANCE_NAME`_PORT_PC_PTR           (*(reg32 *) `$INSTANCE_NAME`_LCDPort__PC)
    
#else

    #define `$INSTANCE_NAME`_PORT_DR_REG           (*(reg8 *) `$INSTANCE_NAME`_LCDPort__DR)  /* Data Output Register */
    #define `$INSTANCE_NAME`_PORT_DR_PTR           ( (reg8 *) `$INSTANCE_NAME`_LCDPort__DR)
    #define `$INSTANCE_NAME`_PORT_PS_REG           (*(reg8 *) `$INSTANCE_NAME`_LCDPort__PS)  /* Pin State Register */
    #define `$INSTANCE_NAME`_PORT_PS_PTR           ( (reg8 *) `$INSTANCE_NAME`_LCDPort__PS)

    #define `$INSTANCE_NAME`_PORT_DM0_REG          (*(reg8 *) `$INSTANCE_NAME`_LCDPort__DM0) /* Port Drive Mode 0 */
    #define `$INSTANCE_NAME`_PORT_DM0_PTR          ( (reg8 *) `$INSTANCE_NAME`_LCDPort__DM0)
    #define `$INSTANCE_NAME`_PORT_DM1_REG          (*(reg8 *) `$INSTANCE_NAME`_LCDPort__DM1) /* Port Drive Mode 1 */
    #define `$INSTANCE_NAME`_PORT_DM1_PTR          ( (reg8 *) `$INSTANCE_NAME`_LCDPort__DM1)
    #define `$INSTANCE_NAME`_PORT_DM2_REG          (*(reg8 *) `$INSTANCE_NAME`_LCDPort__DM2) /* Port Drive Mode 2 */
    #define `$INSTANCE_NAME`_PORT_DM2_PTR          ( (reg8 *) `$INSTANCE_NAME`_LCDPort__DM2)

#endif /* CY_PSOC4 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#if (0 == `$INSTANCE_NAME`_LCDPort__SHIFT)
    #define `$INSTANCE_NAME`_PORT_SHIFT               (0x00u)
#else
    #define `$INSTANCE_NAME`_PORT_SHIFT               (0x01u)
#endif /* (0 == `$INSTANCE_NAME`_LCDPort__SHIFT) */

#define `$INSTANCE_NAME`_PORT_MASK                ((`$TypeReplacementString`) (`$INSTANCE_NAME`_LCDPort__MASK))

#if (CY_PSOC4)

    #define `$INSTANCE_NAME`_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define `$INSTANCE_NAME`_HIGH_Z_DATA_DM           ((0x00000249ul) << (`$INSTANCE_NAME`_PORT_SHIFT *\
                                                                          `$INSTANCE_NAME`_DM_PIN_STEP))
    #define `$INSTANCE_NAME`_STRONG_DATA_DM           ((0x00000DB6ul) << (`$INSTANCE_NAME`_PORT_SHIFT *\
                                                                          `$INSTANCE_NAME`_DM_PIN_STEP))
    #define `$INSTANCE_NAME`_DATA_PINS_MASK           (0x00000FFFul)
    #define `$INSTANCE_NAME`_DM_DATA_MASK             ((uint32) (`$INSTANCE_NAME`_DATA_PINS_MASK << \
                                                      (`$INSTANCE_NAME`_PORT_SHIFT * `$INSTANCE_NAME`_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define `$INSTANCE_NAME`_HIGH_Z_DM0               (0xFFu)
    #define `$INSTANCE_NAME`_HIGH_Z_DM1               (0x00u)
    #define `$INSTANCE_NAME`_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define `$INSTANCE_NAME`_HIGH_Z_A_DM0             (0x00u)
    #define `$INSTANCE_NAME`_HIGH_Z_A_DM1             (0x00u)
    #define `$INSTANCE_NAME`_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define `$INSTANCE_NAME`_STRONG_DM0               (0x00u)
    #define `$INSTANCE_NAME`_STRONG_DM1               (0xFFu)
    #define `$INSTANCE_NAME`_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define `$INSTANCE_NAME`_RS                     ((`$TypeReplacementString`) \
                                                (((`$TypeReplacementString`) 0x20u) << `$INSTANCE_NAME`_LCDPort__SHIFT))
#define `$INSTANCE_NAME`_RW                     ((`$TypeReplacementString`) \
                                                (((`$TypeReplacementString`) 0x40u) << `$INSTANCE_NAME`_LCDPort__SHIFT))
#define `$INSTANCE_NAME`_E                      ((`$TypeReplacementString`) \
                                                (((`$TypeReplacementString`) 0x10u) << `$INSTANCE_NAME`_LCDPort__SHIFT))
#define `$INSTANCE_NAME`_READY_BIT              ((`$TypeReplacementString`) \
                                                (((`$TypeReplacementString`) 0x08u) << `$INSTANCE_NAME`_LCDPort__SHIFT))
#define `$INSTANCE_NAME`_DATA_MASK              ((`$TypeReplacementString`) \
                                                (((`$TypeReplacementString`) 0x0Fu) << `$INSTANCE_NAME`_LCDPort__SHIFT))

/* These names are obsolete and will be removed in future revisions */
#define `$INSTANCE_NAME`_PORT_DR                  `$INSTANCE_NAME`_PORT_DR_REG
#define `$INSTANCE_NAME`_PORT_PS                  `$INSTANCE_NAME`_PORT_PS_REG
#define `$INSTANCE_NAME`_PORT_DM0                 `$INSTANCE_NAME`_PORT_DM0_REG
#define `$INSTANCE_NAME`_PORT_DM1                 `$INSTANCE_NAME`_PORT_DM1_REG
#define `$INSTANCE_NAME`_PORT_DM2                 `$INSTANCE_NAME`_PORT_DM2_REG


/***************************************
*       Obsolete function names
***************************************/
#if(`$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete and will be removed in future 
    * revisions of the component.
    */
    #define `$INSTANCE_NAME`_PrintDecUint16(x)   `$INSTANCE_NAME`_PrintNumber(x)  
    #define `$INSTANCE_NAME`_PrintHexUint8(x)    `$INSTANCE_NAME`_PrintInt8(x)
    #define `$INSTANCE_NAME`_PrintHexUint16(x)   `$INSTANCE_NAME`_PrintInt16(x)        

#endif /* `$INSTANCE_NAME`_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
