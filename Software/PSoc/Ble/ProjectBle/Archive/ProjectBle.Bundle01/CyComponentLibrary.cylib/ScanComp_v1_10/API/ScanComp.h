/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Scanning Comparator Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ScanComp_`$INSTANCE_NAME`_H)
#define CY_ScanComp_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyLib.h"
#include "`$INSTANCE_NAME`_Comp.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* Channel mode type */
#define `$INSTANCE_NAME`_CHANNEL_MODE_COMMON    (0u)
#define `$INSTANCE_NAME`_CHANNEL_MODE_UNIQUE    (1u)
#define `$INSTANCE_NAME`_CHANNEL_MODE_INTERN    (2u)

#define `$INSTANCE_NAME`_INTERNAL_REF_USED      (`$InternalModeExist`u)

#define `$INSTANCE_NAME`_INTERNAL_REF_IS_USED   ((CY_PSOC3 || CY_PSOC5) &&  \
        (`$INSTANCE_NAME`_INTERNAL_REF_USED == `$INSTANCE_NAME`_CHANNEL_MODE_INTERN))

#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
    #define `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED  (`$VoltageMode`u)
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */

#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
    #include "`$INSTANCE_NAME`_VDAC.h"

    #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
        #include "CyDmac.h"
        #include "`$INSTANCE_NAME`_DMA_dma.h"
    #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */

    #define `$INSTANCE_NAME`_DEFAULT_VOLTAGE        (`$FixedVoltage`u)
    #define `$INSTANCE_NAME`_DEFAULT_RANGE          (`$VDACRange`u)
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */


/*******************************************************************************
*   Data Struct Definitions
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_SetSpeed(uint8 speed) `=ReentrantKeil($INSTANCE_NAME . "_SetSpeed")`;
uint8 `$INSTANCE_NAME`_GetCompare(uint8 channel) `=ReentrantKeil($INSTANCE_NAME . "_GetCompare")`;
uint8 `$INSTANCE_NAME`_GetInterruptSource(uint8 inputBlock)         \
                                          `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSource")`;
uint8 `$INSTANCE_NAME`_GetInterruptSourceMasked(uint8 inputBlock)   \
                                                `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSourceMasked")`;
uint8 `$INSTANCE_NAME`_GetInterruptMask(uint8 inputBlock)           \
                                        `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptMask")`;
void `$INSTANCE_NAME`_SetInterruptMask(uint8 inputBlock, uint8 mask)\
                                       `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMask")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;

#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
    void `$INSTANCE_NAME`_SetDACRange(uint8 DACRange) `=ReentrantKeil($INSTANCE_NAME . "_SetDACRange")`;
    uint8 `$INSTANCE_NAME`_GetDACRange(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDACRange")`;

    #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
        void `$INSTANCE_NAME`_SetChannelDACVoltage(uint8 channel, uint8 DACVoltage) \
                                                   `=ReentrantKeil($INSTANCE_NAME . "_SetChannelDACVoltage")`;
        uint8 `$INSTANCE_NAME`_GetChannelDACVoltage(uint8 channel)  \
                                                    `=ReentrantKeil($INSTANCE_NAME . "_GetChannelDACVoltage")`;
    #else
        void `$INSTANCE_NAME`_SetDACVoltage(uint8 DACVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetDACVoltage")`;
        uint8 `$INSTANCE_NAME`_GetDACVoltage(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDACVoltage")`;
    #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */


/*******************************************************************************
* Variable with external linkage
*******************************************************************************/

extern uint8  `$INSTANCE_NAME`_initVar;


/***************************************
*           API Constants
***************************************/

#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
    #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
        /* DMA Configuration for DMA */
        #define `$INSTANCE_NAME`_DMA_BYTES_PER_BURST    (1u)
        #define `$INSTANCE_NAME`_DMA_REQUEST_PER_BURST  (1u)
        #define `$INSTANCE_NAME`_DMA_SRC_BASE (CYDEV_SRAM_BASE)
        #define `$INSTANCE_NAME`_DMA_DST_BASE (CYDEV_PERIPH_BASE)
    #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */

/* Shift */
#define `$INSTANCE_NAME`_7BIT_SHIFT                 (0x07u)

/* Registers array defines */
#define `$INSTANCE_NAME`_NUM_OF_REGISTERS           ((`$INSTANCE_NAME`_DEFAULT_CHANNELS_VAL >> 3u) + 1u)

#define `$INSTANCE_NAME`_NUM_OF_OUT_REGISTERS       (`$INSTANCE_NAME`_NUM_OF_REGISTERS)

#define `$INSTANCE_NAME`_NUM_OF_INT_REGISTERS       (`$INSTANCE_NAME`_NUM_OF_REGISTERS)

/* Num of possible channels */
#define `$INSTANCE_NAME`_NUM_OF_POSSIBLE_CHAN       ((uint8)(`$INSTANCE_NAME`_NUM_OF_REGISTERS << 3u))

/* MSB register bit shift */
#define `$INSTANCE_NAME`_LSB_REG_BIT_SHIFT          (0xFFu >>    \
                                                    (`$INSTANCE_NAME`_NUM_OF_POSSIBLE_CHAN - \
                                                     `$INSTANCE_NAME`_NUM_OF_CHANNELS))

#define `$INSTANCE_NAME`_MSB_REG_CHAN_EXIST         (`$INSTANCE_NAME`_LSB_REG_BIT_SHIFT >> 7u)

/* MSB-bit of the register in high */
#define `$INSTANCE_NAME`_MSB_REG_BIT_HIGH           (0x80u)


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* VDAC Range constants */
#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
    #define `$INSTANCE_NAME`_SCANCOMP_DACRANGE_1V   (`$INSTANCE_NAME`_VDAC_RANGE_1V)
    #define `$INSTANCE_NAME`_SCANCOMP_DACRANGE_4V   (`$INSTANCE_NAME`_VDAC_RANGE_4V)
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */

/* Constants for SetSpeed() function */
#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_SLOWSPEED   (`$INSTANCE_NAME`_Comp_SLOWSPEED)
    #define `$INSTANCE_NAME`_MEDSPEED    (`$INSTANCE_NAME`_Comp_MEDSPEED)
    #define `$INSTANCE_NAME`_HIGHSPEED   (`$INSTANCE_NAME`_Comp_HIGHSPEED)
#else
    #define `$INSTANCE_NAME`_SLOWSPEED   (`$INSTANCE_NAME`_Comp_LOWPOWER)
    #define `$INSTANCE_NAME`_MEDSPEED    (`$INSTANCE_NAME`_Comp_SLOWSPEED)
    #define `$INSTANCE_NAME`_HIGHSPEED   (`$INSTANCE_NAME`_Comp_HIGHSPEED)
#endif /* CY_PSOC4 */


/***************************************
*   Initial Parameter Constants
***************************************/
#define `$INSTANCE_NAME`_NUM_OF_CHANNELS                (`$SequencedChannels`u)
#define `$INSTANCE_NAME`_DEFAULT_CHANNELS_VAL           (`$SequencedChannels`u - 1u)
#define `$INSTANCE_NAME`_DEFAULT_SPEED                  (`$SpeedPower`u)


/***************************************
*             Registers
***************************************/

/* Status Registers */
#define `$INSTANCE_NAME`_STATUS_INT0_REG                (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_IntReg0__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_INT0_PTR                (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_IntReg0__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_INT0_MASK               (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_IntReg0__MASK_REG)
#define `$INSTANCE_NAME`_STATUS_INT0_MASK_PTR           (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_IntReg0__MASK_REG)
#define `$INSTANCE_NAME`_STATUS_INT0_AUX_CONTROL        (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St0_IntReg0__STATUS_AUX_CTL_REG)

#define `$INSTANCE_NAME`_STATUS_OUT0_REG                (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_OutReg0__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_OUT0_PTR                (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_OutReg0__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_OUT0_MASK               (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St0_OutReg0__MASK_REG)
#define `$INSTANCE_NAME`_STATUS_OUT0_AUX_CONTROL        (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St0_OutReg0__STATUS_AUX_CTL_REG)

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
    #define `$INSTANCE_NAME`_STATUS_INT8_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St8_IntReg8__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT8_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St8_IntReg8__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT8_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St8_IntReg8__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT8_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St8_IntReg8__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT8_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St8_IntReg8__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u)
    #define `$INSTANCE_NAME`_STATUS_INT1_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_IntReg1__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT1_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_IntReg1__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT1_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_IntReg1__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT1_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_IntReg1__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT1_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St1_IntReg1__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT1_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_OutReg1__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT1_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_OutReg1__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT1_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St1_OutReg1__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT1_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St1_OutReg1__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u)
    #define `$INSTANCE_NAME`_STATUS_INT2_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_IntReg2__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT2_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_IntReg2__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT2_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_IntReg2__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT2_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_IntReg2__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT2_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St2_IntReg2__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT2_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_OutReg2__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT2_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_OutReg2__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT2_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St2_OutReg2__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT2_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St2_OutReg2__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u)
    #define `$INSTANCE_NAME`_STATUS_INT3_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_IntReg3__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT3_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_IntReg3__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT3_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_IntReg3__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT3_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_IntReg3__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT3_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St3_IntReg3__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT3_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_OutReg3__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT3_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_OutReg3__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT3_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St3_OutReg3__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT3_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St3_OutReg3__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u)
    #define `$INSTANCE_NAME`_STATUS_INT4_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_IntReg4__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT4_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_IntReg4__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT4_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_IntReg4__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT4_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_IntReg4__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT4_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St4_IntReg4__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT4_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_OutReg4__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT4_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_OutReg4__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT4_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St4_OutReg4__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT4_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St4_OutReg4__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u)
    #define `$INSTANCE_NAME`_STATUS_INT5_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_IntReg5__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT5_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_IntReg5__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT5_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_IntReg5__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT5_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_IntReg5__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT5_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St5_IntReg5__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT5_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_OutReg5__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT5_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_OutReg5__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT5_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St5_OutReg5__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT5_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St5_OutReg5__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u)
    #define `$INSTANCE_NAME`_STATUS_INT6_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_IntReg6__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT6_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_IntReg6__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT6_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_IntReg6__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT6_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_IntReg6__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT6_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St6_IntReg6__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT6_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_OutReg6__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT6_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_OutReg6__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT6_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St6_OutReg6__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT6_AUX_CONTROL    (* (reg8 *) \
                                                         `$INSTANCE_NAME`_bScanComp_St6_OutReg6__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u)
    #define `$INSTANCE_NAME`_STATUS_INT7_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_IntReg7__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT7_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_IntReg7__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT7_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_IntReg7__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT7_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_IntReg7__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT7_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St7_IntReg7__STATUS_AUX_CTL_REG)

    #define `$INSTANCE_NAME`_STATUS_OUT7_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_OutReg7__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT7_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_OutReg7__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT7_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St7_OutReg7__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_OUT7_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St7_OutReg7__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u)
    #define `$INSTANCE_NAME`_STATUS_INT9_REG            (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St9_IntReg9__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT9_PTR            (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St9_IntReg9__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_INT9_MASK           (* (reg8 *) `$INSTANCE_NAME`_bScanComp_St9_IntReg9__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT9_MASK_PTR       (  (reg8 *) `$INSTANCE_NAME`_bScanComp_St9_IntReg9__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_INT9_AUX_CONTROL    (* (reg8 *) \
                                                        `$INSTANCE_NAME`_bScanComp_St9_IntReg9__STATUS_AUX_CTL_REG)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u */

/* Control register */
#define `$INSTANCE_NAME`_CONTROL_REG        (*(reg8 *) `$INSTANCE_NAME`_bScanComp_CtrlCnt__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR        ( (reg8 *) `$INSTANCE_NAME`_bScanComp_CtrlCnt__CONTROL_REG)

/* Count 7 */
#define `$INSTANCE_NAME`_COUNTER_COUNT_REG          (*(reg8 *) `$INSTANCE_NAME`_bScanComp_ChannelCounter__COUNT_REG)
#define `$INSTANCE_NAME`_COUNTER_PERIOD_REG          (*(reg8 *) `$INSTANCE_NAME`_bScanComp_ChannelCounter__PERIOD_REG)
#define `$INSTANCE_NAME`_COUNTER_AUX_CONTROL_REG    (*(reg8 *) \
                                                    `$INSTANCE_NAME`_bScanComp_ChannelCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_COUNTER_AUX_CONTROL_PTR    ( (reg8 *) \
                                                    `$INSTANCE_NAME`_bScanComp_ChannelCounter__CONTROL_AUX_CTL_REG)

/***************************************
*   Register Constants
***************************************/

#define `$INSTANCE_NAME`_COUNTER_ENABLE             (0x20u)
#define `$INSTANCE_NAME`_STATUS_INTR_ENBL           (0x10u)
#define `$INSTANCE_NAME`_CONTROL_ENABLE             (0x01u)
#define `$INSTANCE_NAME`_CONTROL_DISABLE            (0x00u)

/* Masks */
#define `$INSTANCE_NAME`_3BIT_MASK                  (0x07u)
#define `$INSTANCE_NAME`_7BIT_MASK                  (0x7Fu)
#define `$INSTANCE_NAME`_INT_REG_MASK               (0x7Fu)

/* INTR_MASK for each channel */
#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 1u)
    #define `$INSTANCE_NAME`_INTR_MASK_0    (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_1    (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_2    (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_3    (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_4    (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_5    (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_6    (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_7    (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS <= 8u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u)
    #define `$INSTANCE_NAME`_INTR_MASK_8    (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_9    (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_10   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_11   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_12   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_13   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_14   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_15   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u)
    #define `$INSTANCE_NAME`_INTR_MASK_16   (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_17   (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_18   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_19   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_20   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_21   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_22   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_23   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u)
    #define `$INSTANCE_NAME`_INTR_MASK_24   (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_25   (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_26   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_27   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_28   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_29   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_30   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_31   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u)
    #define `$INSTANCE_NAME`_INTR_MASK_32   (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_33   (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_34   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_35   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_36   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_37   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_38   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_39   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u)
    #define `$INSTANCE_NAME`_INTR_MASK_40   (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_41   (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_42   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_43   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_44   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_45   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_46   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_47   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u)
    #define `$INSTANCE_NAME`_INTR_MASK_48   (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_49   (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_50   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_51   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_52   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_53   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_54   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_55   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u)
    #define `$INSTANCE_NAME`_INTR_MASK_56   (0x01u)
    #define `$INSTANCE_NAME`_INTR_MASK_57   (0x02u)
    #define `$INSTANCE_NAME`_INTR_MASK_58   (0x04u)
    #define `$INSTANCE_NAME`_INTR_MASK_59   (0x08u)
    #define `$INSTANCE_NAME`_INTR_MASK_60   (0x10u)
    #define `$INSTANCE_NAME`_INTR_MASK_61   (0x20u)
    #define `$INSTANCE_NAME`_INTR_MASK_62   (0x40u)
    #define `$INSTANCE_NAME`_INTR_MASK_63   (0x80u)
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u */

#endif  /* CY_SCANCOMP_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
