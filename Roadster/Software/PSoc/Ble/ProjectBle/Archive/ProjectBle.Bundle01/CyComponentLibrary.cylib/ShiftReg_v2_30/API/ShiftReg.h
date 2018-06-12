/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_`$INSTANCE_NAME`_H)
#define CY_SHIFTREG_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_FIFO_SIZE          (`$FifoSize`u)
#define `$INSTANCE_NAME`_USE_INPUT_FIFO     (`$UseInputFifo`u)
#define `$INSTANCE_NAME`_USE_OUTPUT_FIFO    (`$UseOutputFifo`u)
#define `$INSTANCE_NAME`_SR_SIZE            (`$Length`u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    `$RegSizeReplacementString` saveSrA0Reg;
    `$RegSizeReplacementString` saveSrA1Reg;

    #if(CY_UDB_V0)
        `$RegSizeReplacementString` saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start(void)                              `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void)                               `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void  `$INSTANCE_NAME`_Init(void)                               `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void)                             `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void  `$INSTANCE_NAME`_RestoreConfig(void)                      `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void  `$INSTANCE_NAME`_SaveConfig(void)                         `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void  `$INSTANCE_NAME`_Sleep(void)                              `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void  `$INSTANCE_NAME`_Wakeup(void)                             `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void  `$INSTANCE_NAME`_EnableInt(void)                          `=ReentrantKeil($INSTANCE_NAME . "_EnableInt")`;
void  `$INSTANCE_NAME`_DisableInt(void)                         `=ReentrantKeil($INSTANCE_NAME . "_DisableInt")`;
void  `$INSTANCE_NAME`_SetIntMode(uint8 interruptSource)        `=ReentrantKeil($INSTANCE_NAME . "_SetIntMode")`;
uint8 `$INSTANCE_NAME`_GetIntStatus(void)                       `=ReentrantKeil($INSTANCE_NAME . "_GetIntStatus")`;
void  `$INSTANCE_NAME`_WriteRegValue(`$RegSizeReplacementString` shiftData) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_WriteRegValue")`;
`$RegSizeReplacementString` `$INSTANCE_NAME`_ReadRegValue(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadRegValue")`;
uint8    `$INSTANCE_NAME`_GetFIFOStatus(uint8 fifoId)           `=ReentrantKeil($INSTANCE_NAME . "_GetFIFOStatus")`;

#if(0u != `$INSTANCE_NAME`_USE_INPUT_FIFO)
    cystatus `$INSTANCE_NAME`_WriteData(`$RegSizeReplacementString` shiftData) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_WriteData")`;
#endif /* (0u != `$INSTANCE_NAME`_USE_INPUT_FIFO) */

#if(0u != `$INSTANCE_NAME`_USE_OUTPUT_FIFO)
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadData(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadData")`;
#endif /* (0u != `$INSTANCE_NAME`_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_LOAD                   (0x01u)
#define `$INSTANCE_NAME`_STORE                  (0x02u)
#define `$INSTANCE_NAME`_RESET                  (0x04u)

#define `$INSTANCE_NAME`_IN_FIFO                (0x01u)
#define `$INSTANCE_NAME`_OUT_FIFO               (0x02u)

#define `$INSTANCE_NAME`_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define `$INSTANCE_NAME`_RET_FIFO_NOT_EMPTY     (0x01u)

#define `$INSTANCE_NAME`_RET_FIFO_PARTIAL       (0x01u)
#define `$INSTANCE_NAME`_RET_FIFO_EMPTY         (0x02u)
#define `$INSTANCE_NAME`_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

`#cy_declare_enum Direction`


/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_SR_MASK    (`$SR_MASK`) /* Unsigned is added to parameter */
#define `$INSTANCE_NAME`_INT_SRC    (`$InterruptSource`u)
#define `$INSTANCE_NAME`_DIRECTION  (`$Direction`u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define `$INSTANCE_NAME`_SR_CONTROL_REG (* (reg8 *) \
                                           `$INSTANCE_NAME`_bSR_`$ControlRegUsageReplacemetString`_CtrlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_SR_CONTROL_PTR (  (reg8 *) \
                                           `$INSTANCE_NAME`_bSR_`$ControlRegUsageReplacemetString`_CtrlReg__CONTROL_REG)

/* Status register */
#define `$INSTANCE_NAME`_SR_STATUS_REG      (* (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_REG)
#define `$INSTANCE_NAME`_SR_STATUS_PTR      (  (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define `$INSTANCE_NAME`_SR_STATUS_MASK_REG (* (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__MASK_REG)
#define `$INSTANCE_NAME`_SR_STATUS_MASK_PTR (  (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__MASK_REG)

/* Aux control register */
#define `$INSTANCE_NAME`_SR_AUX_CONTROL_REG (* (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_AUX_CTL_REG)
#define `$INSTANCE_NAME`_SR_AUX_CONTROL_PTR (  (reg8 *) `$INSTANCE_NAME`_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define `$INSTANCE_NAME`_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define `$INSTANCE_NAME`_IN_FIFO_VAL_LSB_PTR        ( (`$RegDefReplacementString` *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F0_REG )

    #define `$INSTANCE_NAME`_SHIFT_REG_LSB_PTR          ( (`$RegDefReplacementString` *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A0_REG )

    #define `$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR    ( (`$RegDefReplacementString` *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A1_REG )

    #define `$INSTANCE_NAME`_OUT_FIFO_VAL_LSB_PTR       ( (`$RegDefReplacementString` *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F1_REG )

#else
    #if(`$INSTANCE_NAME`_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define `$INSTANCE_NAME`_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A1_REG )

        #define `$INSTANCE_NAME`_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F1_REG )

    #elif(`$INSTANCE_NAME`_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define `$INSTANCE_NAME`_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__16BIT_F0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__16BIT_A0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__16BIT_A1_REG )

        #define `$INSTANCE_NAME`_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(`$INSTANCE_NAME`_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define `$INSTANCE_NAME`_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__A1_REG )

        #define `$INSTANCE_NAME`_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define `$INSTANCE_NAME`_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__32BIT_F0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__32BIT_A0_REG )

        #define `$INSTANCE_NAME`_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__32BIT_A1_REG )

        #define `$INSTANCE_NAME`_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  `$INSTANCE_NAME`_bSR_`$VerilogSectionReplacementString`_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (`$INSTANCE_NAME`_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define `$INSTANCE_NAME`_INTERRUPTS_ENABLE      (0x10u)
#define `$INSTANCE_NAME`_LOAD_INT_EN            (0x01u)
#define `$INSTANCE_NAME`_STORE_INT_EN           (0x02u)
#define `$INSTANCE_NAME`_RESET_INT_EN           (0x04u)
#define `$INSTANCE_NAME`_CLK_EN                 (0x01u)

#define `$INSTANCE_NAME`_RESET_INT_EN_MASK      (0xFBu)
#define `$INSTANCE_NAME`_LOAD_INT_EN_MASK       (0xFEu)
#define `$INSTANCE_NAME`_STORE_INT_EN_MASK      (0xFDu)
#define `$INSTANCE_NAME`_INTS_EN_MASK           (0x07u)

#define `$INSTANCE_NAME`_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != `$INSTANCE_NAME`_USE_INPUT_FIFO)

    #define `$INSTANCE_NAME`_IN_FIFO_MASK       (0x18u)

    #define `$INSTANCE_NAME`_IN_FIFO_FULL       (0x00u)
    #define `$INSTANCE_NAME`_IN_FIFO_EMPTY      (0x01u)
    #define `$INSTANCE_NAME`_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define `$INSTANCE_NAME`_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != `$INSTANCE_NAME`_USE_INPUT_FIFO) */

#define `$INSTANCE_NAME`_OUT_FIFO_MASK          (0x60u)

#define `$INSTANCE_NAME`_OUT_FIFO_EMPTY         (0x00u)
#define `$INSTANCE_NAME`_OUT_FIFO_FULL          (0x01u)
#define `$INSTANCE_NAME`_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define `$INSTANCE_NAME`_OUT_FIFO_NOT_EMPTY     (0x02u)

#define `$INSTANCE_NAME`_IN_FIFO_SHIFT_MASK     (0x03u)
#define `$INSTANCE_NAME`_OUT_FIFO_SHIFT_MASK    (0x05u)

#define `$INSTANCE_NAME`_DISABLED               (0u)
#define `$INSTANCE_NAME`_DEFAULT_A0             (0u)
#define `$INSTANCE_NAME`_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define `$INSTANCE_NAME`_IS_ENABLED         (0u != (`$INSTANCE_NAME`_SR_CONTROL & `$INSTANCE_NAME`_CLK_EN))

#define `$INSTANCE_NAME`_GET_OUT_FIFO_STS   ((`$INSTANCE_NAME`_SR_STATUS & `$INSTANCE_NAME`_OUT_FIFO_MASK) >> \
                                              `$INSTANCE_NAME`_OUT_FIFO_SHIFT_MASK)

#define `$INSTANCE_NAME`_GET_IN_FIFO_STS    ((`$INSTANCE_NAME`_SR_STATUS & `$INSTANCE_NAME`_IN_FIFO_MASK)  >> \
                                              `$INSTANCE_NAME`_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define `$INSTANCE_NAME`_SR_CONTROL     (`$INSTANCE_NAME`_SR_CONTROL_REG)
#define `$INSTANCE_NAME`_SR_STATUS      (`$INSTANCE_NAME`_SR_STATUS_REG)
#define `$INSTANCE_NAME`_SR_STATUS_MASK (`$INSTANCE_NAME`_SR_STATUS_MASK_REG)
#define `$INSTANCE_NAME`_SR_AUX_CONTROL (`$INSTANCE_NAME`_SR_AUX_CONTROL_REG)

#define `$INSTANCE_NAME`_IN_FIFO_SHFT_MASK  (`$INSTANCE_NAME`_IN_FIFO_SHIFT_MASK)
#define `$INSTANCE_NAME`_OUT_FIFO_SHFT_MASK (`$INSTANCE_NAME`_OUT_FIFO_SHFIT_MASK)

#define `$INSTANCE_NAME`_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
