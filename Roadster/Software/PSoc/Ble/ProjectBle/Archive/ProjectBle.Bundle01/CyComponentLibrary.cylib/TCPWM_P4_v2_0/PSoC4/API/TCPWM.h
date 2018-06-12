/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the `$INSTANCE_NAME`
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_`$INSTANCE_NAME`_H)
#define CY_TCPWM_`$INSTANCE_NAME`_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  `$INSTANCE_NAME`_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define `$INSTANCE_NAME`_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define `$INSTANCE_NAME`_CONFIG                         (`$TCPWMConfig`lu)

/* Quad Mode */
/* Parameters */
#define `$INSTANCE_NAME`_QUAD_ENCODING_MODES            (`$QuadEncodingModes`lu)

/* Signal modes */
#define `$INSTANCE_NAME`_QUAD_INDEX_SIGNAL_MODE         (`$QuadIndexMode`lu)
#define `$INSTANCE_NAME`_QUAD_PHIA_SIGNAL_MODE          (`$QuadPhiAMode`lu)
#define `$INSTANCE_NAME`_QUAD_PHIB_SIGNAL_MODE          (`$QuadPhiBMode`lu)
#define `$INSTANCE_NAME`_QUAD_STOP_SIGNAL_MODE          (`$QuadStopMode`lu)

/* Signal present */
#define `$INSTANCE_NAME`_QUAD_INDEX_SIGNAL_PRESENT      (`$QuadIndexPresent`lu)
#define `$INSTANCE_NAME`_QUAD_STOP_SIGNAL_PRESENT       (`$QuadStopPresent`lu)

/* Interrupt Mask */
#define `$INSTANCE_NAME`_QUAD_INTERRUPT_MASK            (`$QuadInterruptMask`lu)

/* Timer/Counter Mode */
/* Parameters */
#define `$INSTANCE_NAME`_TC_RUN_MODE                    (`$TCRunMode`lu)
#define `$INSTANCE_NAME`_TC_COUNTER_MODE                (`$TCCountingModes`lu)
#define `$INSTANCE_NAME`_TC_COMP_CAP_MODE               (`$TCCompCapMode`lu)
#define `$INSTANCE_NAME`_TC_PRESCALER                   (`$TCPrescaler`lu)

/* Signal modes */
#define `$INSTANCE_NAME`_TC_RELOAD_SIGNAL_MODE          (`$TCReloadMode`lu)
#define `$INSTANCE_NAME`_TC_COUNT_SIGNAL_MODE           (`$TCCountMode`lu)
#define `$INSTANCE_NAME`_TC_START_SIGNAL_MODE           (`$TCStartMode`lu)
#define `$INSTANCE_NAME`_TC_STOP_SIGNAL_MODE            (`$TCStopMode`lu)
#define `$INSTANCE_NAME`_TC_CAPTURE_SIGNAL_MODE         (`$TCCaptureMode`lu)

/* Signal present */
#define `$INSTANCE_NAME`_TC_RELOAD_SIGNAL_PRESENT       (`$TCReloadPresent`lu)
#define `$INSTANCE_NAME`_TC_COUNT_SIGNAL_PRESENT        (`$TCCountPresent`lu)
#define `$INSTANCE_NAME`_TC_START_SIGNAL_PRESENT        (`$TCStartPresent`lu)
#define `$INSTANCE_NAME`_TC_STOP_SIGNAL_PRESENT         (`$TCStopPresent`lu)
#define `$INSTANCE_NAME`_TC_CAPTURE_SIGNAL_PRESENT      (`$TCCapturePresent`lu)

/* Interrupt Mask */
#define `$INSTANCE_NAME`_TC_INTERRUPT_MASK              (`$TCInterruptMask`lu)

/* PWM Mode */
/* Parameters */
#define `$INSTANCE_NAME`_PWM_KILL_EVENT                 (`$PWMKillEvent`lu)
#define `$INSTANCE_NAME`_PWM_STOP_EVENT                 (`$PWMStopEvent`lu)
#define `$INSTANCE_NAME`_PWM_MODE                       (`$PWMMode`lu)
#define `$INSTANCE_NAME`_PWM_OUT_N_INVERT               (`$PWMLinenSignal`lu)
#define `$INSTANCE_NAME`_PWM_OUT_INVERT                 (`$PWMLineSignal`lu)
#define `$INSTANCE_NAME`_PWM_ALIGN                      (`$PWMSetAlign`lu)
#define `$INSTANCE_NAME`_PWM_RUN_MODE                   (`$PWMRunMode`lu)
#define `$INSTANCE_NAME`_PWM_DEAD_TIME_CYCLE            (`$PWMDeadTimeCycle`lu)
#define `$INSTANCE_NAME`_PWM_PRESCALER                  (`$PWMPrescaler`lu)

/* Signal modes */
#define `$INSTANCE_NAME`_PWM_RELOAD_SIGNAL_MODE         (`$PWMReloadMode`lu)
#define `$INSTANCE_NAME`_PWM_COUNT_SIGNAL_MODE          (`$PWMCountMode`lu)
#define `$INSTANCE_NAME`_PWM_START_SIGNAL_MODE          (`$PWMStartMode`lu)
#define `$INSTANCE_NAME`_PWM_STOP_SIGNAL_MODE           (`$PWMStopMode`lu)
#define `$INSTANCE_NAME`_PWM_SWITCH_SIGNAL_MODE         (`$PWMSwitchMode`lu)

/* Signal present */
#define `$INSTANCE_NAME`_PWM_RELOAD_SIGNAL_PRESENT      (`$PWMReloadPresent`lu)
#define `$INSTANCE_NAME`_PWM_COUNT_SIGNAL_PRESENT       (`$PWMCountPresent`lu)
#define `$INSTANCE_NAME`_PWM_START_SIGNAL_PRESENT       (`$PWMStartPresent`lu)
#define `$INSTANCE_NAME`_PWM_STOP_SIGNAL_PRESENT        (`$PWMStopPresent`lu)
#define `$INSTANCE_NAME`_PWM_SWITCH_SIGNAL_PRESENT      (`$PWMSwitchPresent`lu)

/* Interrupt Mask */
#define `$INSTANCE_NAME`_PWM_INTERRUPT_MASK             (`$PWMInterruptMask`lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define `$INSTANCE_NAME`_TC_PERIOD_VALUE                (`$TCPeriod`lu)
#define `$INSTANCE_NAME`_TC_COMPARE_VALUE               (`$TCCompare`lu)
#define `$INSTANCE_NAME`_TC_COMPARE_BUF_VALUE           (`$TCCompareBuf`lu)
#define `$INSTANCE_NAME`_TC_COMPARE_SWAP                (`$TCCompareSwap`lu)

/* PWM Mode */
#define `$INSTANCE_NAME`_PWM_PERIOD_VALUE               (`$PWMPeriod`lu)
#define `$INSTANCE_NAME`_PWM_PERIOD_BUF_VALUE           (`$PWMPeriodBuf`lu)
#define `$INSTANCE_NAME`_PWM_PERIOD_SWAP                (`$PWMPeriodSwap`lu)
#define `$INSTANCE_NAME`_PWM_COMPARE_VALUE              (`$PWMCompare`lu)
#define `$INSTANCE_NAME`_PWM_COMPARE_BUF_VALUE          (`$PWMCompareBuf`lu)
#define `$INSTANCE_NAME`_PWM_COMPARE_SWAP               (`$PWMCompareSwap`lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

`#cy_declare_enum pwmAlign`
`#cy_declare_enum quadMode`
`#cy_declare_enum pwmMode`
`#cy_declare_enum pwmInvert`
`#cy_declare_enum compCapMode`
`#cy_declare_enum triggerMode`
`#cy_declare_enum interruptMask`
`#cy_declare_enum TCPWMConfig`
`#cy_declare_enum CounterMode`

/* Prescaler */
#define `$INSTANCE_NAME`_PRESCALE_DIVBY1                ((uint32)(0u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY2                ((uint32)(1u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY4                ((uint32)(2u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY8                ((uint32)(3u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY16               ((uint32)(4u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY32               ((uint32)(5u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY64               ((uint32)(6u << `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_PRESCALE_DIVBY128              ((uint32)(7u << `$INSTANCE_NAME`_PRESCALER_SHIFT))

/* TCPWM set modes */
#define `$INSTANCE_NAME`_MODE_TIMER_COMPARE             ((uint32)(`$INSTANCE_NAME`__COMPARE         <<  \
                                                                  `$INSTANCE_NAME`_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_TIMER_CAPTURE             ((uint32)(`$INSTANCE_NAME`__CAPTURE         <<  \
                                                                  `$INSTANCE_NAME`_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_QUAD                      ((uint32)(`$INSTANCE_NAME`__QUAD            <<  \
                                                                  `$INSTANCE_NAME`_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_PWM                       ((uint32)(`$INSTANCE_NAME`__PWM             <<  \
                                                                  `$INSTANCE_NAME`_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_PWM_DT                    ((uint32)(`$INSTANCE_NAME`__PWM_DT          <<  \
                                                                  `$INSTANCE_NAME`_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_PWM_PR                    ((uint32)(`$INSTANCE_NAME`__PWM_PR          <<  \
                                                                  `$INSTANCE_NAME`_MODE_SHIFT))

/* Quad Modes */
#define `$INSTANCE_NAME`_MODE_X1                        ((uint32)(`$INSTANCE_NAME`__X1              <<  \
                                                                  `$INSTANCE_NAME`_QUAD_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_X2                        ((uint32)(`$INSTANCE_NAME`__X2              <<  \
                                                                  `$INSTANCE_NAME`_QUAD_MODE_SHIFT))
#define `$INSTANCE_NAME`_MODE_X4                        ((uint32)(`$INSTANCE_NAME`__X4              <<  \
                                                                  `$INSTANCE_NAME`_QUAD_MODE_SHIFT))

/* Counter modes */
#define `$INSTANCE_NAME`_COUNT_UP                       ((uint32)(`$INSTANCE_NAME`__COUNT_UP        <<  \
                                                                  `$INSTANCE_NAME`_UPDOWN_SHIFT))
#define `$INSTANCE_NAME`_COUNT_DOWN                     ((uint32)(`$INSTANCE_NAME`__COUNT_DOWN      <<  \
                                                                  `$INSTANCE_NAME`_UPDOWN_SHIFT))
#define `$INSTANCE_NAME`_COUNT_UPDOWN0                  ((uint32)(`$INSTANCE_NAME`__COUNT_UPDOWN0   <<  \
                                                                  `$INSTANCE_NAME`_UPDOWN_SHIFT))
#define `$INSTANCE_NAME`_COUNT_UPDOWN1                  ((uint32)(`$INSTANCE_NAME`__COUNT_UPDOWN1   <<  \
                                                                  `$INSTANCE_NAME`_UPDOWN_SHIFT))

/* PWM output invert */
#define `$INSTANCE_NAME`_INVERT_LINE                    ((uint32)(`$INSTANCE_NAME`__INVERSE         <<  \
                                                                  `$INSTANCE_NAME`_INV_OUT_SHIFT))
#define `$INSTANCE_NAME`_INVERT_LINE_N                  ((uint32)(`$INSTANCE_NAME`__INVERSE         <<  \
                                                                  `$INSTANCE_NAME`_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define `$INSTANCE_NAME`_TRIG_RISING                    ((uint32)`$INSTANCE_NAME`__TRIG_RISING)
#define `$INSTANCE_NAME`_TRIG_FALLING                   ((uint32)`$INSTANCE_NAME`__TRIG_FALLING)
#define `$INSTANCE_NAME`_TRIG_BOTH                      ((uint32)`$INSTANCE_NAME`__TRIG_BOTH)
#define `$INSTANCE_NAME`_TRIG_LEVEL                     ((uint32)`$INSTANCE_NAME`__TRIG_LEVEL)

/* Interrupt mask */
#define `$INSTANCE_NAME`_INTR_MASK_TC                   ((uint32)`$INSTANCE_NAME`__INTR_MASK_TC)
#define `$INSTANCE_NAME`_INTR_MASK_CC_MATCH             ((uint32)`$INSTANCE_NAME`__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define `$INSTANCE_NAME`_CC_MATCH_SET                   (0x00u)
#define `$INSTANCE_NAME`_CC_MATCH_CLEAR                 (0x01u)
#define `$INSTANCE_NAME`_CC_MATCH_INVERT                (0x02u)
#define `$INSTANCE_NAME`_CC_MATCH_NO_CHANGE             (0x03u)
#define `$INSTANCE_NAME`_OVERLOW_SET                    (0x00u)
#define `$INSTANCE_NAME`_OVERLOW_CLEAR                  (0x04u)
#define `$INSTANCE_NAME`_OVERLOW_INVERT                 (0x08u)
#define `$INSTANCE_NAME`_OVERLOW_NO_CHANGE              (0x0Cu)
#define `$INSTANCE_NAME`_UNDERFLOW_SET                  (0x00u)
#define `$INSTANCE_NAME`_UNDERFLOW_CLEAR                (0x10u)
#define `$INSTANCE_NAME`_UNDERFLOW_INVERT               (0x20u)
#define `$INSTANCE_NAME`_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define `$INSTANCE_NAME`_PWM_MODE_LEFT                  (`$INSTANCE_NAME`_CC_MATCH_CLEAR        |   \
                                                         `$INSTANCE_NAME`_OVERLOW_SET           |   \
                                                         `$INSTANCE_NAME`_UNDERFLOW_NO_CHANGE)
#define `$INSTANCE_NAME`_PWM_MODE_RIGHT                 (`$INSTANCE_NAME`_CC_MATCH_SET          |   \
                                                         `$INSTANCE_NAME`_OVERLOW_NO_CHANGE     |   \
                                                         `$INSTANCE_NAME`_UNDERFLOW_CLEAR)
#define `$INSTANCE_NAME`_PWM_MODE_ASYM                  (`$INSTANCE_NAME`_CC_MATCH_INVERT       |   \
                                                         `$INSTANCE_NAME`_OVERLOW_SET           |   \
                                                         `$INSTANCE_NAME`_UNDERFLOW_CLEAR)

#if (`$INSTANCE_NAME`_CY_TCPWM_V2)
    #if(`$INSTANCE_NAME`_CY_TCPWM_4000)
        #define `$INSTANCE_NAME`_PWM_MODE_CENTER                (`$INSTANCE_NAME`_CC_MATCH_INVERT       |   \
                                                                 `$INSTANCE_NAME`_OVERLOW_NO_CHANGE     |   \
                                                                 `$INSTANCE_NAME`_UNDERFLOW_CLEAR)
    #else
        #define `$INSTANCE_NAME`_PWM_MODE_CENTER                (`$INSTANCE_NAME`_CC_MATCH_INVERT       |   \
                                                                 `$INSTANCE_NAME`_OVERLOW_SET           |   \
                                                                 `$INSTANCE_NAME`_UNDERFLOW_CLEAR)
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */
#else
    #define `$INSTANCE_NAME`_PWM_MODE_CENTER                (`$INSTANCE_NAME`_CC_MATCH_INVERT       |   \
                                                             `$INSTANCE_NAME`_OVERLOW_NO_CHANGE     |   \
                                                             `$INSTANCE_NAME`_UNDERFLOW_CLEAR)
#endif /* (`$INSTANCE_NAME`_CY_TCPWM_NEW) */

/* Command operations without condition */
#define `$INSTANCE_NAME`_CMD_CAPTURE                    (0u)
#define `$INSTANCE_NAME`_CMD_RELOAD                     (8u)
#define `$INSTANCE_NAME`_CMD_STOP                       (16u)
#define `$INSTANCE_NAME`_CMD_START                      (24u)

/* Status */
#define `$INSTANCE_NAME`_STATUS_DOWN                    (1u)
#define `$INSTANCE_NAME`_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   `$INSTANCE_NAME`_Init(void);
void   `$INSTANCE_NAME`_Enable(void);
void   `$INSTANCE_NAME`_Start(void);
void   `$INSTANCE_NAME`_Stop(void);

void   `$INSTANCE_NAME`_SetMode(uint32 mode);
void   `$INSTANCE_NAME`_SetCounterMode(uint32 counterMode);
void   `$INSTANCE_NAME`_SetPWMMode(uint32 modeMask);
void   `$INSTANCE_NAME`_SetQDMode(uint32 qdMode);

void   `$INSTANCE_NAME`_SetPrescaler(uint32 prescaler);
void   `$INSTANCE_NAME`_TriggerCommand(uint32 mask, uint32 command);
void   `$INSTANCE_NAME`_SetOneShot(uint32 oneShotEnable);
uint32 `$INSTANCE_NAME`_ReadStatus(void);

void   `$INSTANCE_NAME`_SetPWMSyncKill(uint32 syncKillEnable);
void   `$INSTANCE_NAME`_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   `$INSTANCE_NAME`_SetPWMDeadTime(uint32 deadTime);
void   `$INSTANCE_NAME`_SetPWMInvert(uint32 mask);

void   `$INSTANCE_NAME`_SetInterruptMode(uint32 interruptMask);
uint32 `$INSTANCE_NAME`_GetInterruptSourceMasked(void);
uint32 `$INSTANCE_NAME`_GetInterruptSource(void);
void   `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask);
void   `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask);

void   `$INSTANCE_NAME`_WriteCounter(uint32 count);
uint32 `$INSTANCE_NAME`_ReadCounter(void);

uint32 `$INSTANCE_NAME`_ReadCapture(void);
uint32 `$INSTANCE_NAME`_ReadCaptureBuf(void);

void   `$INSTANCE_NAME`_WritePeriod(uint32 period);
uint32 `$INSTANCE_NAME`_ReadPeriod(void);
void   `$INSTANCE_NAME`_WritePeriodBuf(uint32 periodBuf);
uint32 `$INSTANCE_NAME`_ReadPeriodBuf(void);

void   `$INSTANCE_NAME`_WriteCompare(uint32 compare);
uint32 `$INSTANCE_NAME`_ReadCompare(void);
void   `$INSTANCE_NAME`_WriteCompareBuf(uint32 compareBuf);
uint32 `$INSTANCE_NAME`_ReadCompareBuf(void);

void   `$INSTANCE_NAME`_SetPeriodSwap(uint32 swapEnable);
void   `$INSTANCE_NAME`_SetCompareSwap(uint32 swapEnable);

void   `$INSTANCE_NAME`_SetCaptureMode(uint32 triggerMode);
void   `$INSTANCE_NAME`_SetReloadMode(uint32 triggerMode);
void   `$INSTANCE_NAME`_SetStartMode(uint32 triggerMode);
void   `$INSTANCE_NAME`_SetStopMode(uint32 triggerMode);
void   `$INSTANCE_NAME`_SetCountMode(uint32 triggerMode);

void   `$INSTANCE_NAME`_SaveConfig(void);
void   `$INSTANCE_NAME`_RestoreConfig(void);
void   `$INSTANCE_NAME`_Sleep(void);
void   `$INSTANCE_NAME`_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_BLOCK_CONTROL_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define `$INSTANCE_NAME`_BLOCK_CONTROL_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define `$INSTANCE_NAME`_COMMAND_REG                    (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define `$INSTANCE_NAME`_COMMAND_PTR                    ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define `$INSTANCE_NAME`_INTRRUPT_CAUSE_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define `$INSTANCE_NAME`_INTRRUPT_CAUSE_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define `$INSTANCE_NAME`_CONTROL_REG                    (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__CTRL )
#define `$INSTANCE_NAME`_CONTROL_PTR                    ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__CTRL )
#define `$INSTANCE_NAME`_STATUS_REG                     (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__STATUS )
#define `$INSTANCE_NAME`_STATUS_PTR                     ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__STATUS )
#define `$INSTANCE_NAME`_COUNTER_REG                    (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__COUNTER )
#define `$INSTANCE_NAME`_COUNTER_PTR                    ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__COUNTER )
#define `$INSTANCE_NAME`_COMP_CAP_REG                   (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__CC )
#define `$INSTANCE_NAME`_COMP_CAP_PTR                   ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__CC )
#define `$INSTANCE_NAME`_COMP_CAP_BUF_REG               (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__CC_BUFF )
#define `$INSTANCE_NAME`_COMP_CAP_BUF_PTR               ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__CC_BUFF )
#define `$INSTANCE_NAME`_PERIOD_REG                     (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__PERIOD )
#define `$INSTANCE_NAME`_PERIOD_PTR                     ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__PERIOD )
#define `$INSTANCE_NAME`_PERIOD_BUF_REG                 (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define `$INSTANCE_NAME`_PERIOD_BUF_PTR                 ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define `$INSTANCE_NAME`_TRIG_CONTROL0_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define `$INSTANCE_NAME`_TRIG_CONTROL0_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define `$INSTANCE_NAME`_TRIG_CONTROL1_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define `$INSTANCE_NAME`_TRIG_CONTROL1_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define `$INSTANCE_NAME`_TRIG_CONTROL2_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define `$INSTANCE_NAME`_TRIG_CONTROL2_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define `$INSTANCE_NAME`_INTERRUPT_REQ_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR )
#define `$INSTANCE_NAME`_INTERRUPT_REQ_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR )
#define `$INSTANCE_NAME`_INTERRUPT_SET_REG              (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR_SET )
#define `$INSTANCE_NAME`_INTERRUPT_SET_PTR              ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR_SET )
#define `$INSTANCE_NAME`_INTERRUPT_MASK_REG             (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR_MASK )
#define `$INSTANCE_NAME`_INTERRUPT_MASK_PTR             ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR_MASK )
#define `$INSTANCE_NAME`_INTERRUPT_MASKED_REG           (*(reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR_MASKED )
#define `$INSTANCE_NAME`_INTERRUPT_MASKED_PTR           ( (reg32 *) `$INSTANCE_NAME`_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define `$INSTANCE_NAME`_MASK                           ((uint32)`$INSTANCE_NAME`_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define `$INSTANCE_NAME`_RELOAD_CC_SHIFT                (0u)
#define `$INSTANCE_NAME`_RELOAD_PERIOD_SHIFT            (1u)
#define `$INSTANCE_NAME`_PWM_SYNC_KILL_SHIFT            (2u)
#define `$INSTANCE_NAME`_PWM_STOP_KILL_SHIFT            (3u)
#define `$INSTANCE_NAME`_PRESCALER_SHIFT                (8u)
#define `$INSTANCE_NAME`_UPDOWN_SHIFT                   (16u)
#define `$INSTANCE_NAME`_ONESHOT_SHIFT                  (18u)
#define `$INSTANCE_NAME`_QUAD_MODE_SHIFT                (20u)
#define `$INSTANCE_NAME`_INV_OUT_SHIFT                  (20u)
#define `$INSTANCE_NAME`_INV_COMPL_OUT_SHIFT            (21u)
#define `$INSTANCE_NAME`_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define `$INSTANCE_NAME`_RELOAD_CC_MASK                 ((uint32)(`$INSTANCE_NAME`_1BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_RELOAD_CC_SHIFT))
#define `$INSTANCE_NAME`_RELOAD_PERIOD_MASK             ((uint32)(`$INSTANCE_NAME`_1BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_RELOAD_PERIOD_SHIFT))
#define `$INSTANCE_NAME`_PWM_SYNC_KILL_MASK             ((uint32)(`$INSTANCE_NAME`_1BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_PWM_SYNC_KILL_SHIFT))
#define `$INSTANCE_NAME`_PWM_STOP_KILL_MASK             ((uint32)(`$INSTANCE_NAME`_1BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_PWM_STOP_KILL_SHIFT))
#define `$INSTANCE_NAME`_PRESCALER_MASK                 ((uint32)(`$INSTANCE_NAME`_8BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_PRESCALER_SHIFT))
#define `$INSTANCE_NAME`_UPDOWN_MASK                    ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_UPDOWN_SHIFT))
#define `$INSTANCE_NAME`_ONESHOT_MASK                   ((uint32)(`$INSTANCE_NAME`_1BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_ONESHOT_SHIFT))
#define `$INSTANCE_NAME`_QUAD_MODE_MASK                 ((uint32)(`$INSTANCE_NAME`_3BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_QUAD_MODE_SHIFT))
#define `$INSTANCE_NAME`_INV_OUT_MASK                   ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_INV_OUT_SHIFT))
#define `$INSTANCE_NAME`_MODE_MASK                      ((uint32)(`$INSTANCE_NAME`_3BIT_MASK        <<  \
                                                                            `$INSTANCE_NAME`_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define `$INSTANCE_NAME`_CAPTURE_SHIFT                  (0u)
#define `$INSTANCE_NAME`_COUNT_SHIFT                    (2u)
#define `$INSTANCE_NAME`_RELOAD_SHIFT                   (4u)
#define `$INSTANCE_NAME`_STOP_SHIFT                     (6u)
#define `$INSTANCE_NAME`_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define `$INSTANCE_NAME`_CAPTURE_MASK                   ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                  `$INSTANCE_NAME`_CAPTURE_SHIFT))
#define `$INSTANCE_NAME`_COUNT_MASK                     ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                  `$INSTANCE_NAME`_COUNT_SHIFT))
#define `$INSTANCE_NAME`_RELOAD_MASK                    ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                  `$INSTANCE_NAME`_RELOAD_SHIFT))
#define `$INSTANCE_NAME`_STOP_MASK                      ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                  `$INSTANCE_NAME`_STOP_SHIFT))
#define `$INSTANCE_NAME`_START_MASK                     ((uint32)(`$INSTANCE_NAME`_2BIT_MASK        <<  \
                                                                  `$INSTANCE_NAME`_START_SHIFT))

/* MASK */
#define `$INSTANCE_NAME`_1BIT_MASK                      ((uint32)0x01u)
#define `$INSTANCE_NAME`_2BIT_MASK                      ((uint32)0x03u)
#define `$INSTANCE_NAME`_3BIT_MASK                      ((uint32)0x07u)
#define `$INSTANCE_NAME`_6BIT_MASK                      ((uint32)0x3Fu)
#define `$INSTANCE_NAME`_8BIT_MASK                      ((uint32)0xFFu)
#define `$INSTANCE_NAME`_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define `$INSTANCE_NAME`_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define `$INSTANCE_NAME`_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(`$INSTANCE_NAME`_QUAD_ENCODING_MODES     << `$INSTANCE_NAME`_QUAD_MODE_SHIFT))       |\
         ((uint32)(`$INSTANCE_NAME`_CONFIG                  << `$INSTANCE_NAME`_MODE_SHIFT)))

#define `$INSTANCE_NAME`_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(`$INSTANCE_NAME`_PWM_STOP_EVENT          << `$INSTANCE_NAME`_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(`$INSTANCE_NAME`_PWM_OUT_INVERT          << `$INSTANCE_NAME`_INV_OUT_SHIFT))         |\
         ((uint32)(`$INSTANCE_NAME`_PWM_OUT_N_INVERT        << `$INSTANCE_NAME`_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(`$INSTANCE_NAME`_PWM_MODE                << `$INSTANCE_NAME`_MODE_SHIFT)))

#define `$INSTANCE_NAME`_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(`$INSTANCE_NAME`_PWM_RUN_MODE         << `$INSTANCE_NAME`_ONESHOT_SHIFT))
            
#define `$INSTANCE_NAME`_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(`$INSTANCE_NAME`_PWM_ALIGN            << `$INSTANCE_NAME`_UPDOWN_SHIFT))

#define `$INSTANCE_NAME`_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(`$INSTANCE_NAME`_PWM_KILL_EVENT      << `$INSTANCE_NAME`_PWM_SYNC_KILL_SHIFT))

#define `$INSTANCE_NAME`_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(`$INSTANCE_NAME`_PWM_DEAD_TIME_CYCLE  << `$INSTANCE_NAME`_PRESCALER_SHIFT))

#define `$INSTANCE_NAME`_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(`$INSTANCE_NAME`_PWM_PRESCALER        << `$INSTANCE_NAME`_PRESCALER_SHIFT))

#define `$INSTANCE_NAME`_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(`$INSTANCE_NAME`_TC_PRESCALER            << `$INSTANCE_NAME`_PRESCALER_SHIFT))       |\
         ((uint32)(`$INSTANCE_NAME`_TC_COUNTER_MODE         << `$INSTANCE_NAME`_UPDOWN_SHIFT))          |\
         ((uint32)(`$INSTANCE_NAME`_TC_RUN_MODE             << `$INSTANCE_NAME`_ONESHOT_SHIFT))         |\
         ((uint32)(`$INSTANCE_NAME`_TC_COMP_CAP_MODE        << `$INSTANCE_NAME`_MODE_SHIFT)))
        
#define `$INSTANCE_NAME`_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(`$INSTANCE_NAME`_QUAD_PHIA_SIGNAL_MODE   << `$INSTANCE_NAME`_COUNT_SHIFT))           |\
         ((uint32)(`$INSTANCE_NAME`_QUAD_INDEX_SIGNAL_MODE  << `$INSTANCE_NAME`_RELOAD_SHIFT))          |\
         ((uint32)(`$INSTANCE_NAME`_QUAD_STOP_SIGNAL_MODE   << `$INSTANCE_NAME`_STOP_SHIFT))            |\
         ((uint32)(`$INSTANCE_NAME`_QUAD_PHIB_SIGNAL_MODE   << `$INSTANCE_NAME`_START_SHIFT)))

#define `$INSTANCE_NAME`_PWM_SIGNALS_MODES                                                              \
        (((uint32)(`$INSTANCE_NAME`_PWM_SWITCH_SIGNAL_MODE  << `$INSTANCE_NAME`_CAPTURE_SHIFT))         |\
         ((uint32)(`$INSTANCE_NAME`_PWM_COUNT_SIGNAL_MODE   << `$INSTANCE_NAME`_COUNT_SHIFT))           |\
         ((uint32)(`$INSTANCE_NAME`_PWM_RELOAD_SIGNAL_MODE  << `$INSTANCE_NAME`_RELOAD_SHIFT))          |\
         ((uint32)(`$INSTANCE_NAME`_PWM_STOP_SIGNAL_MODE    << `$INSTANCE_NAME`_STOP_SHIFT))            |\
         ((uint32)(`$INSTANCE_NAME`_PWM_START_SIGNAL_MODE   << `$INSTANCE_NAME`_START_SHIFT)))

#define `$INSTANCE_NAME`_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(`$INSTANCE_NAME`_TC_CAPTURE_SIGNAL_MODE  << `$INSTANCE_NAME`_CAPTURE_SHIFT))         |\
         ((uint32)(`$INSTANCE_NAME`_TC_COUNT_SIGNAL_MODE    << `$INSTANCE_NAME`_COUNT_SHIFT))           |\
         ((uint32)(`$INSTANCE_NAME`_TC_RELOAD_SIGNAL_MODE   << `$INSTANCE_NAME`_RELOAD_SHIFT))          |\
         ((uint32)(`$INSTANCE_NAME`_TC_STOP_SIGNAL_MODE     << `$INSTANCE_NAME`_STOP_SHIFT))            |\
         ((uint32)(`$INSTANCE_NAME`_TC_START_SIGNAL_MODE    << `$INSTANCE_NAME`_START_SHIFT)))
        
#define `$INSTANCE_NAME`_TIMER_UPDOWN_CNT_USED                                                          \
                ((`$INSTANCE_NAME`__COUNT_UPDOWN0 == `$INSTANCE_NAME`_TC_COUNTER_MODE)                  ||\
                 (`$INSTANCE_NAME`__COUNT_UPDOWN1 == `$INSTANCE_NAME`_TC_COUNTER_MODE))

#define `$INSTANCE_NAME`_PWM_UPDOWN_CNT_USED                                                            \
                ((`$INSTANCE_NAME`__CENTER == `$INSTANCE_NAME`_PWM_ALIGN)                               ||\
                 (`$INSTANCE_NAME`__ASYMMETRIC == `$INSTANCE_NAME`_PWM_ALIGN))               
        
#define `$INSTANCE_NAME`_PWM_PR_INIT_VALUE              (1u)
#define `$INSTANCE_NAME`_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
