/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  LED Driver Component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_LED_Driver_`$INSTANCE_NAME`_H)
#define CY_LED_Driver_`$INSTANCE_NAME`_H


/***************************************
*   Conditional Compilation Parameters
***************************************/
#define `$INSTANCE_NAME`_BRIGHTNESS_EN                (`$BrightnessCtrl`u)
#define `$INSTANCE_NAME`_COM_DRIVE                    (`$CommonDrive`u)
#define `$INSTANCE_NAME`_SEG_DRIVE                    (`$SegmentDrive`u)
#define `$INSTANCE_NAME`_NUM_COM                      (`$NumCom`u)
#define `$INSTANCE_NAME`_NUM_SEG                      (`$NumSeg`u)
#define `$INSTANCE_NAME`_TWO_NUM_COM                  ((uint8)((uint8)`$INSTANCE_NAME`_NUM_COM << 1u))

/* Error message for removed commons control register through optimization */
#ifdef `$INSTANCE_NAME`_Com_Driver_Sync_ctrl_reg__REMOVED
    #error `$CY_COMPONENT_NAME` requires all the signals from the commons terminal to be connected to pins.
#endif /* `$INSTANCE_NAME`_Com_Driver_Sync_ctrl_reg__REMOVED */

/* Error message for removed segments control registers through optimization */
#if defined `$INSTANCE_NAME`_Seg_Driver_L_Sync_ctrl_reg__REMOVED || \
defined `$INSTANCE_NAME`_Seg_Driver_M_Sync_ctrl_reg__REMOVED || \
defined `$INSTANCE_NAME`_Seg_Driver_H_Sync_ctrl_reg__REMOVED
    #error `$CY_COMPONENT_NAME` requires all the signals from the segments terminal to be connected to pins.
#endif /* `$INSTANCE_NAME`_Seg_Driver_L_Sync_ctrl_reg__REMOVED */


/***************************************
*   Header files
***************************************/
#include <`$INSTANCE_NAME`_Com_Driver.h>
#include <`$INSTANCE_NAME`_Seg_Driver_L.h>
#if (`$INSTANCE_NAME`_NUM_SEG > 8u)
    #include <`$INSTANCE_NAME`_Seg_Driver_M.h>
#endif /* Segment_M control register */
#if (`$INSTANCE_NAME`_NUM_SEG > 16u)
    #include <`$INSTANCE_NAME`_Seg_Driver_H.h>
#endif /* Segment_H control register */

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#ifndef CY_PSOC5A
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* CY_PSOC5A */


/***************************************
*        Structure Definitions
***************************************/
typedef struct
{
    uint8 ledEnableState;
    /* Backup the segment values when going to sleep. (Stop() clears the buffers) */
    uint8 segLBackup[`$INSTANCE_NAME`_NUM_COM];
    #if (`$INSTANCE_NAME`_NUM_SEG > 8u) 
        uint8 segMBackup[`$INSTANCE_NAME`_NUM_COM];
    #endif /* (`$INSTANCE_NAME`_NUM_SEG > 8u) */
    #if (`$INSTANCE_NAME`_NUM_SEG > 16u) 
        uint8 segHBackup[`$INSTANCE_NAME`_NUM_COM];
    #endif /* (`$INSTANCE_NAME`_NUM_SEG > 16u) */
}`$INSTANCE_NAME`_backupStruct;


/***************************************
*        Function Prototypes
***************************************/
void `$INSTANCE_NAME`_Init(void)                       `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)                     `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Start(void)                      `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void)                       `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_SetDisplayRAM(uint8 value, uint8 position) 
                                                        `=ReentrantKeil($INSTANCE_NAME . "_SetDisplayRAM")`;
void `$INSTANCE_NAME`_SetRC(uint8 row, uint8 column)    `=ReentrantKeil($INSTANCE_NAME . "_SetRC")`;
void `$INSTANCE_NAME`_ClearRC(uint8 row, uint8 column)  `=ReentrantKeil($INSTANCE_NAME . "_ClearRC")`;
void `$INSTANCE_NAME`_ToggleRC(uint8 row, uint8 column) `=ReentrantKeil($INSTANCE_NAME . "_ToggleRC")`;
uint8 `$INSTANCE_NAME`_GetRC(uint8 row, uint8 column)   `=ReentrantKeil($INSTANCE_NAME . "_GetRC")`;
void `$INSTANCE_NAME`_ClearDisplay(uint8 position)      `=ReentrantKeil($INSTANCE_NAME . "_ClearDisplay")`;
void `$INSTANCE_NAME`_ClearDisplayAll(void)             `=ReentrantKeil($INSTANCE_NAME . "_ClearDisplayAll")`;
void `$INSTANCE_NAME`_Write7SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write7SegNumberDec")`;
void `$INSTANCE_NAME`_Write7SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write7SegNumberHex")`;
void `$INSTANCE_NAME`_WriteString7Seg(char8 const character[], uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_WriteString7Seg")`;
void `$INSTANCE_NAME`_PutChar7Seg(char8 character , uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_PutChar7Seg")`;
void `$INSTANCE_NAME`_Write7SegDigitDec(uint8 digit, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write7SegDigitDec")`;
void `$INSTANCE_NAME`_Write7SegDigitHex(uint8 digit, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write7SegDigitHex")`;
void `$INSTANCE_NAME`_Write14SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write14SegNumberDec")`;
void `$INSTANCE_NAME`_Write14SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write14SegNumberHex")`;
void `$INSTANCE_NAME`_WriteString14Seg(char8 const character[], uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_WriteString14Seg")`;
void `$INSTANCE_NAME`_PutChar14Seg(char8 character , uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_PutChar14Seg")`;
void `$INSTANCE_NAME`_Write14SegDigitDec(uint8 digit, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write14SegDigitDec")`;
void `$INSTANCE_NAME`_Write14SegDigitHex(uint8 digit, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write14SegDigitHex")`;
void `$INSTANCE_NAME`_Write16SegNumberDec(int32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write16SegNumberDec")`;
void `$INSTANCE_NAME`_Write16SegNumberHex(uint32 number, uint8 position, uint8 digits, uint8 alignment)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write16SegNumberHex")`;
void `$INSTANCE_NAME`_WriteString16Seg(char8 const character[], uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_WriteString16Seg")`;
void `$INSTANCE_NAME`_PutChar16Seg(char8 character , uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_PutChar16Seg")`;
void `$INSTANCE_NAME`_Write16SegDigitDec(uint8 digit, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write16SegDigitDec")`;
void `$INSTANCE_NAME`_Write16SegDigitHex(uint8 digit, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_Write16SegDigitHex")`;
void `$INSTANCE_NAME`_PutDecimalPoint(uint8 dp, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_PutDecimalPoint")`;
uint8 `$INSTANCE_NAME`_GetDecimalPoint(uint8 position)  `=ReentrantKeil($INSTANCE_NAME . "_GetDecimalPoint")`;
uint8 `$INSTANCE_NAME`_EncodeNumber7Seg(uint8 number)   `=ReentrantKeil($INSTANCE_NAME . "_EncodeNumber7Seg")`;
uint8 `$INSTANCE_NAME`_EncodeChar7Seg(char8 input)      `=ReentrantKeil($INSTANCE_NAME . "_EncodeChar7Seg")`;
uint16 `$INSTANCE_NAME`_EncodeNumber14Seg(uint8 number) `=ReentrantKeil($INSTANCE_NAME . "_EncodeNumber14Seg")`;
uint16 `$INSTANCE_NAME`_EncodeChar14Seg(char8 input)    `=ReentrantKeil($INSTANCE_NAME . "_EncodeChar14Seg")`;
uint16 `$INSTANCE_NAME`_EncodeNumber16Seg(uint8 number) `=ReentrantKeil($INSTANCE_NAME . "_EncodeNumber16Seg")`;
uint16 `$INSTANCE_NAME`_EncodeChar16Seg(char8 input)    `=ReentrantKeil($INSTANCE_NAME . "_EncodeChar16Seg")`;
void `$INSTANCE_NAME`_SetBrightness(uint8 bright, uint8 position)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_SetBrightness")`;
uint8 `$INSTANCE_NAME`_GetBrightness(uint8 position)    `=ReentrantKeil($INSTANCE_NAME . "_GetBrightness")`;
void `$INSTANCE_NAME`_Sleep(void)                       `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)                      `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;


/***************************************
*           Global Variables
***************************************/
extern uint8 `$INSTANCE_NAME`_initVar;
extern uint8 `$INSTANCE_NAME`_enableVar;

/* Buffers used to hold the display(segment) values to be transferred to the control registers */
extern uint8 `$INSTANCE_NAME`_segLBuffer[`$INSTANCE_NAME`_NUM_COM];
#if (`$INSTANCE_NAME`_NUM_SEG > 8u) 
    extern uint8 `$INSTANCE_NAME`_segMBuffer[`$INSTANCE_NAME`_NUM_COM];
#endif /* (`$INSTANCE_NAME`_NUM_SEG > 8u) */
#if (`$INSTANCE_NAME`_NUM_SEG > 16u) 
    extern uint8 `$INSTANCE_NAME`_segHBuffer[`$INSTANCE_NAME`_NUM_COM];
#endif /* (`$INSTANCE_NAME`_NUM_SEG > 16u) */


/***************************************
*           API Constants
***************************************/

/* Related to conditional compilation */
#define `$INSTANCE_NAME`_HIGH                   (0x01u)
#define `$INSTANCE_NAME`_ENABLED                (0x01u)

/* Number of DMA channels */
#if (`$INSTANCE_NAME`_BRIGHTNESS_EN == `$INSTANCE_NAME`_ENABLED)
    #define `$INSTANCE_NAME`_CHANNEL_LIMIT      (0x03u)
#else
    #define `$INSTANCE_NAME`_CHANNEL_LIMIT      (0x02u)
#endif /* (`$INSTANCE_NAME`_BRIGHTNESS_EN == `$INSTANCE_NAME`_ENABLED) */

/* Defines related to sign extraction for number displays */
#define `$INSTANCE_NAME`_SIGNED                 (0x01u)
#define `$INSTANCE_NAME`_UNSIGNED               (0x00u)
#define `$INSTANCE_NAME`_ZERO_NEG               ((int32)0x00000000)

/* Brightness control defines */
#define `$INSTANCE_NAME`_INIT_BRIGHT            (0xFFu)

/* Segment display defines */
#if(`$INSTANCE_NAME`_SEG_DRIVE == `$INSTANCE_NAME`_HIGH)
    #define `$INSTANCE_NAME`_CLEAR              (0x00u)
    #define `$INSTANCE_NAME`_CLEAR_16           ((uint16)0x0000u)
    #define `$INSTANCE_NAME`_ZERO_7CHAR         (0x3Fu)
    #define `$INSTANCE_NAME`_ZERO_14CHAR        ((uint16)0x243Fu)
    #define `$INSTANCE_NAME`_ZERO_16CHAR        ((uint16)0x90FFu)
#else
    #define `$INSTANCE_NAME`_CLEAR              (0xFFu)
    #define `$INSTANCE_NAME`_CLEAR_16           ((uint16)0xFFFFu)
    #define `$INSTANCE_NAME`_ZERO_7CHAR         (0xC0u)
    #define `$INSTANCE_NAME`_ZERO_14CHAR        ((uint16)0xDBC0u)
    #define `$INSTANCE_NAME`_ZERO_16CHAR        ((uint16)0x6F00u)
#endif /* (`$INSTANCE_NAME`_SEG_DRIVE == `$INSTANCE_NAME`_HIGH) */

/* Shifts and 4-bit operation mask */
#define `$INSTANCE_NAME`_SHIFT_NIBBLE           (0x04u)
#define `$INSTANCE_NAME`_NIBBLE_MASK            (0x0Fu)
#define `$INSTANCE_NAME`_SHIFT_BYTE             (0x08u)

/* ASCII table access defines */
#define `$INSTANCE_NAME`_SEG_ASCII_OFFSET       (0x02u)
#define `$INSTANCE_NAME`_SEG_ASCII_LIM_HI       (0x08u)
#define `$INSTANCE_NAME`_SEG_ASCII_LIM_LO       (0x01u)

/* Decimal point defines */
#define `$INSTANCE_NAME`_DEC_POINT              (0x07u)
#define `$INSTANCE_NAME`_DEC_POINT_MASK         (0x01u)
#if(`$INSTANCE_NAME`_SEG_DRIVE == `$INSTANCE_NAME`_HIGH)
    #define `$INSTANCE_NAME`_DEC_POINT_VALUE    (0x80u)
#else
    #define `$INSTANCE_NAME`_DEC_POINT_VALUE    (0x7Fu)
#endif /* (`$INSTANCE_NAME`_SEG_DRIVE == `$INSTANCE_NAME`_HIGH) */

/* 7-seg position to register mapping defines */
#define `$INSTANCE_NAME`_SEG_REG_LOW            (0x00u)
#define `$INSTANCE_NAME`_SEG_REG_MID            (0x01u)
#define `$INSTANCE_NAME`_SEG_REG_HIGH           (0x02u)

/* Segment display alignment defines */
#define `$INSTANCE_NAME`_RIGHT_ALIGN            (0x00u)
#define `$INSTANCE_NAME`_LEFT_ALIGN             (0x01u)
#define `$INSTANCE_NAME`_ZERO_PAD               (0x02u)


/***************************************
*           Registers
***************************************/
#define `$INSTANCE_NAME`_CONTROL_REG_BASE       (CYDEV_PERIPH_BASE)
#define `$INSTANCE_NAME`_SRAM_BASE              (CYDEV_SRAM_BASE)

#define `$INSTANCE_NAME`_COM_CONTROL_PTR        (`$INSTANCE_NAME`_Com_Driver_Control_PTR)
#define `$INSTANCE_NAME`_SEG_L_CONTROL_PTR      (`$INSTANCE_NAME`_Seg_Driver_L_Control_PTR)

#if (`$INSTANCE_NAME`_NUM_SEG > 8u)
    #define `$INSTANCE_NAME`_SEG_M_CONTROL_PTR  (`$INSTANCE_NAME`_Seg_Driver_M_Control_PTR)
#endif /* (`$INSTANCE_NAME`_NUM_SEG > 8u) */
#if (`$INSTANCE_NAME`_NUM_SEG > 16u)
    #define `$INSTANCE_NAME`_SEG_H_CONTROL_PTR  (`$INSTANCE_NAME`_Seg_Driver_H_Control_PTR)
#endif /* (`$INSTANCE_NAME`_NUM_SEG > 16u) */


/***************************************
*           UDB PWM Registers
***************************************/
/* Control register */
#define `$INSTANCE_NAME`_CONTROL_REG            (*(reg8 *) `$INSTANCE_NAME`_bLED_PWM_CtlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR            ( (reg8 *) `$INSTANCE_NAME`_bLED_PWM_CtlReg__CONTROL_REG)

/* Counter register */
#define `$INSTANCE_NAME`_COUNTER_REG            (*(reg8 *) `$INSTANCE_NAME`_bLED_PWM_PwmDP_u0__A1_REG)
#define `$INSTANCE_NAME`_COUNTER_PTR            ((reg8 *) `$INSTANCE_NAME`_bLED_PWM_PwmDP_u0__A1_REG)
/* Compare value buffer */
#define `$INSTANCE_NAME`_COMPARE_REG            (*(reg8 *) `$INSTANCE_NAME`_bLED_PWM_PwmDP_u0__D0_REG)
#define `$INSTANCE_NAME`_COMPARE_PTR            ((reg8 *) `$INSTANCE_NAME`_bLED_PWM_PwmDP_u0__D0_REG)


/***************************************
*          Register Constants
***************************************/
/* Control Register Enable/Disable. Also use for `$INSTANCE_NAME`_enableVar */
#define `$INSTANCE_NAME`_CTRL_ENABLE            (0x01u)
#define `$INSTANCE_NAME`_CTRL_DISABLE           (0x00u)

#endif /* CY_LED_Driver_`$INSTANCE_NAME`_H Header File */


/* [] END OF FILE */
