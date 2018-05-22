/*******************************************************************************
* File Name: LCDD.h
* Version 2.20
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

#if !defined(CY_CHARLCD_LCDD_H)
#define CY_CHARLCD_LCDD_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCDD_CONVERSION_ROUTINES     (1u)
#define LCDD_CUSTOM_CHAR_SET         (3u)

/* Custom character set types */
#define LCDD_NONE                     (0u)    /* No Custom Fonts      */
#define LCDD_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define LCDD_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define LCDD_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} LCDD_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void LCDD_Init(void) ;
void LCDD_Enable(void) ;
void LCDD_Start(void) ;
void LCDD_Stop(void) ;
void LCDD_WriteControl(uint8 cByte) ;
void LCDD_WriteData(uint8 dByte) ;
void LCDD_PrintString(char8 const string[]) ;
void LCDD_Position(uint8 row, uint8 column) ;
void LCDD_PutChar(char8 character) ;
void LCDD_IsReady(void) ;
void LCDD_SaveConfig(void) ;
void LCDD_RestoreConfig(void) ;
void LCDD_Sleep(void) ;
void LCDD_Wakeup(void) ;

#if((LCDD_CUSTOM_CHAR_SET == LCDD_VERTICAL_BG) || \
                (LCDD_CUSTOM_CHAR_SET == LCDD_HORIZONTAL_BG))

    void  LCDD_LoadCustomFonts(uint8 const customData[])
                        ;

    void  LCDD_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void LCDD_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((LCDD_CUSTOM_CHAR_SET == LCDD_VERTICAL_BG) */

#if(LCDD_CUSTOM_CHAR_SET == LCDD_USER_DEFINED)

    void LCDD_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((LCDD_CUSTOM_CHAR_SET == LCDD_USER_DEFINED) */

#if(LCDD_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void LCDD_PrintInt8(uint8 value) ;
    void LCDD_PrintInt16(uint16 value) ;
    void LCDD_PrintInt32(uint32 value) ;
    void LCDD_PrintNumber(uint16 value) ; 
    void LCDD_PrintU32Number(uint32 value) ;
    
#endif /* LCDD_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define LCDD_ClearDisplay() LCDD_WriteControl(LCDD_CLEAR_DISPLAY)

/* Off Macro */
#define LCDD_DisplayOff() LCDD_WriteControl(LCDD_DISPLAY_CURSOR_OFF)

/* On Macro */
#define LCDD_DisplayOn() LCDD_WriteControl(LCDD_DISPLAY_ON_CURSOR_OFF)

#define LCDD_PrintNumber(value) LCDD_PrintU32Number((uint16) (value))


/***************************************
*           Global Variables
***************************************/

extern uint8 LCDD_initVar;
extern uint8 LCDD_enableState;
extern uint8 const CYCODE LCDD_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define LCDD_DISPLAY_8_BIT_INIT       (0x03u)
#define LCDD_DISPLAY_4_BIT_INIT       (0x02u)
#define LCDD_DISPLAY_CURSOR_OFF       (0x08u)
#define LCDD_CLEAR_DISPLAY            (0x01u)
#define LCDD_CURSOR_AUTO_INCR_ON      (0x06u)
#define LCDD_DISPLAY_CURSOR_ON        (0x0Eu)
#define LCDD_DISPLAY_2_LINES_5x10     (0x2Cu)
#define LCDD_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define LCDD_RESET_CURSOR_POSITION    (0x03u)
#define LCDD_CURSOR_WINK              (0x0Du)
#define LCDD_CURSOR_BLINK             (0x0Fu)
#define LCDD_CURSOR_SH_LEFT           (0x10u)
#define LCDD_CURSOR_SH_RIGHT          (0x14u)
#define LCDD_DISPLAY_SCRL_LEFT        (0x18u)
#define LCDD_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define LCDD_CURSOR_HOME              (0x02u)
#define LCDD_CURSOR_LEFT              (0x04u)
#define LCDD_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define LCDD_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define LCDD_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define LCDD_CHARACTER_WIDTH          (0x05u)
#define LCDD_CHARACTER_HEIGHT         (0x08u)

#if(LCDD_CONVERSION_ROUTINES == 1u)
    #define LCDD_NUMBER_OF_REMAINDERS_U32 (0x0Au)
    #define LCDD_TEN                      (0x0Au)
    #define LCDD_8_BIT_SHIFT              (8u)
    #define LCDD_32_BIT_SHIFT             (32u)
    #define LCDD_ZERO_CHAR_ASCII          (48u)
#endif /* LCDD_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define LCDD_NIBBLE_SHIFT             (0x04u)
#define LCDD_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define LCDD_ROW_0_START              (0x80u)
#define LCDD_ROW_1_START              (0xC0u)
#define LCDD_ROW_2_START              (0x94u)
#define LCDD_ROW_3_START              (0xD4u)

/* Custom Character References */
#define LCDD_CUSTOM_0                 (0x00u)
#define LCDD_CUSTOM_1                 (0x01u)
#define LCDD_CUSTOM_2                 (0x02u)
#define LCDD_CUSTOM_3                 (0x03u)
#define LCDD_CUSTOM_4                 (0x04u)
#define LCDD_CUSTOM_5                 (0x05u)
#define LCDD_CUSTOM_6                 (0x06u)
#define LCDD_CUSTOM_7                 (0x07u)

/* Other constants */
#define LCDD_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define LCDD_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define LCDD_U16_UPPER_BYTE_SHIFT     (0x08u)
#define LCDD_U16_LOWER_BYTE_MASK      (0xFFu)
#define LCDD_CUSTOM_CHAR_SET_LEN      (0x40u)

#define LCDD_LONGEST_CMD_US           (0x651u)
#define LCDD_WAIT_CYCLE               (0x10u)
#define LCDD_READY_DELAY              ((LCDD_LONGEST_CMD_US * 4u)/(LCDD_WAIT_CYCLE))


/***************************************
*             Registers
***************************************/

/* Device specific registers */
#if (CY_PSOC4)

    #define LCDD_PORT_DR_REG           (*(reg32 *) LCDD_LCDPort__DR)  /* Data Output Register */
    #define LCDD_PORT_DR_PTR           ( (reg32 *) LCDD_LCDPort__DR)
    #define LCDD_PORT_PS_REG           (*(reg32 *) LCDD_LCDPort__PS)  /* Pin State Register */
    #define LCDD_PORT_PS_PTR           ( (reg32 *) LCDD_LCDPort__PS)
    
    #define LCDD_PORT_PC_REG           (*(reg32 *) LCDD_LCDPort__PC)
    #define LCDD_PORT_PC_PTR           (*(reg32 *) LCDD_LCDPort__PC)
    
#else

    #define LCDD_PORT_DR_REG           (*(reg8 *) LCDD_LCDPort__DR)  /* Data Output Register */
    #define LCDD_PORT_DR_PTR           ( (reg8 *) LCDD_LCDPort__DR)
    #define LCDD_PORT_PS_REG           (*(reg8 *) LCDD_LCDPort__PS)  /* Pin State Register */
    #define LCDD_PORT_PS_PTR           ( (reg8 *) LCDD_LCDPort__PS)

    #define LCDD_PORT_DM0_REG          (*(reg8 *) LCDD_LCDPort__DM0) /* Port Drive Mode 0 */
    #define LCDD_PORT_DM0_PTR          ( (reg8 *) LCDD_LCDPort__DM0)
    #define LCDD_PORT_DM1_REG          (*(reg8 *) LCDD_LCDPort__DM1) /* Port Drive Mode 1 */
    #define LCDD_PORT_DM1_PTR          ( (reg8 *) LCDD_LCDPort__DM1)
    #define LCDD_PORT_DM2_REG          (*(reg8 *) LCDD_LCDPort__DM2) /* Port Drive Mode 2 */
    #define LCDD_PORT_DM2_PTR          ( (reg8 *) LCDD_LCDPort__DM2)

#endif /* CY_PSOC4 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#if (0 == LCDD_LCDPort__SHIFT)
    #define LCDD_PORT_SHIFT               (0x00u)
#else
    #define LCDD_PORT_SHIFT               (0x01u)
#endif /* (0 == LCDD_LCDPort__SHIFT) */

#define LCDD_PORT_MASK                ((uint8) (LCDD_LCDPort__MASK))

#if (CY_PSOC4)

    #define LCDD_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define LCDD_HIGH_Z_DATA_DM           ((0x00000249ul) << (LCDD_PORT_SHIFT *\
                                                                          LCDD_DM_PIN_STEP))
    #define LCDD_STRONG_DATA_DM           ((0x00000DB6ul) << (LCDD_PORT_SHIFT *\
                                                                          LCDD_DM_PIN_STEP))
    #define LCDD_DATA_PINS_MASK           (0x00000FFFul)
    #define LCDD_DM_DATA_MASK             ((uint32) (LCDD_DATA_PINS_MASK << \
                                                      (LCDD_PORT_SHIFT * LCDD_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define LCDD_HIGH_Z_DM0               (0xFFu)
    #define LCDD_HIGH_Z_DM1               (0x00u)
    #define LCDD_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define LCDD_HIGH_Z_A_DM0             (0x00u)
    #define LCDD_HIGH_Z_A_DM1             (0x00u)
    #define LCDD_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define LCDD_STRONG_DM0               (0x00u)
    #define LCDD_STRONG_DM1               (0xFFu)
    #define LCDD_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define LCDD_RS                     ((uint8) \
                                                (((uint8) 0x20u) << LCDD_LCDPort__SHIFT))
#define LCDD_RW                     ((uint8) \
                                                (((uint8) 0x40u) << LCDD_LCDPort__SHIFT))
#define LCDD_E                      ((uint8) \
                                                (((uint8) 0x10u) << LCDD_LCDPort__SHIFT))
#define LCDD_READY_BIT              ((uint8) \
                                                (((uint8) 0x08u) << LCDD_LCDPort__SHIFT))
#define LCDD_DATA_MASK              ((uint8) \
                                                (((uint8) 0x0Fu) << LCDD_LCDPort__SHIFT))

/* These names are obsolete and will be removed in future revisions */
#define LCDD_PORT_DR                  LCDD_PORT_DR_REG
#define LCDD_PORT_PS                  LCDD_PORT_PS_REG
#define LCDD_PORT_DM0                 LCDD_PORT_DM0_REG
#define LCDD_PORT_DM1                 LCDD_PORT_DM1_REG
#define LCDD_PORT_DM2                 LCDD_PORT_DM2_REG


/***************************************
*       Obsolete function names
***************************************/
#if(LCDD_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete and will be removed in future 
    * revisions of the component.
    */
    #define LCDD_PrintDecUint16(x)   LCDD_PrintNumber(x)  
    #define LCDD_PrintHexUint8(x)    LCDD_PrintInt8(x)
    #define LCDD_PrintHexUint16(x)   LCDD_PrintInt16(x)        

#endif /* LCDD_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_LCDD_H */


/* [] END OF FILE */
