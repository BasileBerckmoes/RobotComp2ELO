/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  API function prototypes, customizer parameters and other constants for the
*  Fan Controller component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_FAN_CONTROLLER_H)
#define `$INSTANCE_NAME`_CY_FAN_CONTROLLER_H

#include "cytypes.h"
#include "cyfitter.h"
#if (!CY_PSOC4)
    #include <CYDMAC.H>
#endif /* (!CY_PSOC4) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_FAN_CTL_MODE               (`$FanMode`u)
#define `$INSTANCE_NAME`_NUMBER_OF_FANS             (`$NumberOfFans`u)
#define `$INSTANCE_NAME`_NUMBER_OF_BANKS            (`$NumberOfBanks`u)
#define `$INSTANCE_NAME`_PWMRES                     (`$FanPWMRes`u)

#define `$INSTANCE_NAME`_MANUAL_MODE                (`$FanModeManual`u)

#define `$INSTANCE_NAME`_MANUAL_MODE_TRUE           (1u)
#define `$INSTANCE_NAME`_MANUAL_MODE_FALSE          (0u)

#define `$INSTANCE_NAME`_FANCTLMODE_FIRMWARE        (0u)
#define `$INSTANCE_NAME`_FANCTLMODE_HARDWARE        (1u)

#define `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS      (`$NumberOfFanOutputs`u)

/* Resolution constants */
#define `$INSTANCE_NAME`_PWMRES_EIGHTBIT            (0u)
#define `$INSTANCE_NAME`_PWMRES_TENBIT              (1u)

/* PWM Configuration Constants */
#if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
    #define `$INSTANCE_NAME`_PWM_PERIOD                 (240u)
#else
    #define `$INSTANCE_NAME`_PWM_PERIOD                 (960u)
#endif /*`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */

/* Macros to identify if Automatic or Manual Control mode is used */
#define `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE      \
                (`$INSTANCE_NAME`_FAN_CTL_MODE == `$INSTANCE_NAME`_FANCTLMODE_HARDWARE)
#define `$INSTANCE_NAME`_IS_MANUAL_MODE             \
                ((`$INSTANCE_NAME`_MANUAL_MODE == `$INSTANCE_NAME`_MANUAL_MODE_TRUE) && \
                    ((`$INSTANCE_NAME`_FAN_CTL_MODE != `$INSTANCE_NAME`_FANCTLMODE_HARDWARE)))
#define `$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE      \
                ((`$INSTANCE_NAME`_FAN_CTL_MODE == `$INSTANCE_NAME`_FANCTLMODE_FIRMWARE) && \
                    (!(`$INSTANCE_NAME`_IS_MANUAL_MODE)))

/* PID Constants */
#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    #define `$INSTANCE_NAME`_PID_A1             (`$pid_A1`)
    #define `$INSTANCE_NAME`_PID_A2             (`$pid_A2`)
    #define `$INSTANCE_NAME`_PID_A3             (`$pid_A3`)

    #define `$INSTANCE_NAME`_PID_POST_GAIN      (`$pid_output_gain`u)

    #define `$INSTANCE_NAME`_PID_OUTPUT_SAT_L   (`$pid_output_sat_L`u)
    #define `$INSTANCE_NAME`_PID_OUTPUT_SAT_H   (`$pid_output_sat_H`u)

    /* PID error low and high saturation. These are constants defined
    * by EROS to be (-4096) and (4096) respectively.
    */
    #define `$INSTANCE_NAME`_PID_ERROR_SAT_L    (-4096)
    #define `$INSTANCE_NAME`_PID_ERROR_SAT_H    (4096)

#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void    `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void    `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void    `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void    `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void    `$INSTANCE_NAME`_EnableAlert(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableAlert")`;
void    `$INSTANCE_NAME`_DisableAlert(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableAlert")`;
void    `$INSTANCE_NAME`_SetAlertMode(uint8 alertMode) `=ReentrantKeil($INSTANCE_NAME . "_SetAlertMode")`;
uint8   `$INSTANCE_NAME`_GetAlertMode(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertMode")`;
void    `$INSTANCE_NAME`_SetAlertMask(uint16 alertMask) `=ReentrantKeil($INSTANCE_NAME . "_SetAlertMask")`;
uint16  `$INSTANCE_NAME`_GetAlertMask(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertMask")`;
uint8   `$INSTANCE_NAME`_GetAlertSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertSource")`;
uint16  `$INSTANCE_NAME`_GetFanStallStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFanStallStatus")`;
void    `$INSTANCE_NAME`_SetDutyCycle(uint8 fanOrBankNumber, uint16 dutyCycle)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_SetDutyCycle")`;
uint16  `$INSTANCE_NAME`_GetDutyCycle(uint8 fanOrBankNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetDutyCycle")`;
void    `$INSTANCE_NAME`_SetDesiredSpeed(uint8 fanNumber, uint16 rpm)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_SetDesiredSpeed")`;
uint16  `$INSTANCE_NAME`_GetActualSpeed(uint8 fanNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetActualSpeed")`;

#if (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    void `$INSTANCE_NAME`_SetPID(uint8 fanNum, uint16 kp, uint16 ki, uint16 kd)
            `=ReentrantKeil($INSTANCE_NAME . "_SetPID")`;
    void `$INSTANCE_NAME`_SetSaturation(uint8 fanNum, uint16 satH, uint16 satL)
            `=ReentrantKeil($INSTANCE_NAME . "_SetSaturation")`;
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

#if (!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    void    `$INSTANCE_NAME`_OverrideAutomaticControl(uint8 override)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_OverrideAutomaticControl")`;
    uint16  `$INSTANCE_NAME`_GetDesiredSpeed(uint8 fanNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetDesiredSpeed")`;
    uint16  `$INSTANCE_NAME`_GetFanSpeedStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFanSpeedStatus")`;
#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */

/* Interrupt handlers */
#if(CY_PSOC4)
    /* ISR for transferring data from Tachometer to RAM */
    CY_ISR_PROTO(`$INSTANCE_NAME`_DATA_SEND_ISR);
#endif /* (CY_PSOC4) */

#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    /* PID Control algorithm ISR */
    CY_ISR_PROTO(`$INSTANCE_NAME`_PID_CONTROL_ISR);
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */


/***************************************
*           API Constants
***************************************/

/* Constants for Acoustic Noise Reduction */
#define `$INSTANCE_NAME`_NOISE_REDUCTION_OFF        (0u)
#define `$INSTANCE_NAME`_NOISE_REDUCTION_ON         (1u)

/* Bit definitions for the Alert Source Status Register (`$INSTANCE_NAME`_GetAlertSource()) */
#define `$INSTANCE_NAME`_STALL_ALERT                (0x01u)
#define `$INSTANCE_NAME`_SPEED_ALERT                (0x02u)

/* End of Conversion constants */
#define `$INSTANCE_NAME`_EOC_HIGH                   (0x01u)
#define `$INSTANCE_NAME`_EOC_LOW                    (0x00u)

/* Maximum possible Fans number */
#define `$INSTANCE_NAME`_MAX_FANS                   (16u)

/* Treshold for speed regulation error coccurence */
#define `$INSTANCE_NAME`_SPEED_ERRORS_TRESHOLD      (16u)
#define `$INSTANCE_NAME`_MAX_SPEED_ERRORS           (255u)

#if (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    #define `$INSTANCE_NAME`_MAX_GAIN                   (65535u)
    #define `$INSTANCE_NAME`_GAIN_MULTIPLIER            (4096u)
#endif /* (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) */

/* RPM to Duty Cycle Conversion Constants */
#define `$INSTANCE_NAME`_TACH_CLOCK_FREQ            (500000u)
#define `$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR     (`$INSTANCE_NAME`_TACH_CLOCK_FREQ * 60u)

#define `$INSTANCE_NAME`_PWM_INIT_DUTY              (`$INSTANCE_NAME`_PWM_PERIOD)
#define `$INSTANCE_NAME`_PWM_DUTY_DIVIDER           (10000u)      /* API Duty Cycle is expressed in 100ths of % */

#if (CY_PSOC3)
    /* 8051 registers have 16-bit addresses */
    #define `$INSTANCE_NAME`_RegAddrType            uint16
    /* DMA TD endian swap flag - 8051 is big endian */
    #define `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG    (TD_SWAP_EN)
#else
    /* ARM registers have 32-bit addresses */
    #define `$INSTANCE_NAME`_RegAddrType            uint32
    /* DMA TD endian swap flag - ARM is little endian */
    #define `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG    (0u)
#endif /* CY_PSOC3 */

#define `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN ((`$INSTANCE_NAME`_TachOutDMA__TERMOUT0_EN ? TD_TERMOUT0_EN : 0u) | \
    (`$INSTANCE_NAME`_TachOutDMA__TERMOUT1_EN ? TD_TERMOUT1_EN : 0u))

#if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
    #define `$INSTANCE_NAME`_TachInDMA__TD_TERMOUT_EN ((`$INSTANCE_NAME`_TachInDMA__TERMOUT0_EN ? \
                                TD_TERMOUT0_EN : 0u) | (`$INSTANCE_NAME`_TachInDMA__TERMOUT1_EN ? TD_TERMOUT1_EN : 0u))
#endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

extern uint8 `$INSTANCE_NAME`_tachOutDMA_DmaHandle;
#if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
    extern uint8 `$INSTANCE_NAME`_tachInDMA_DmaHandle;
#endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */


/***************************************
*     Data Struct Definitions
***************************************/

/* Hardware and Firmware Fan Control Mode DMA transaction descriptors to store actual fan speeds in SRAM */
typedef struct
{
   uint8     setActualPeriodTD;                           /* Actual tach period from Tach block to SRAM */
} `$INSTANCE_NAME`_fanTdOutStruct;

/* Hardware Fan Control Mode DMA transaction descriptors to read desired speeds and tolerane from SRAM */
#if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
    typedef struct
    {
        uint8     getDesiredPeriodTD;                       /* Desired tach period from SRAM to Tach block */
        uint8     getToleranceTD;                           /* Desired period tolerance from SRAM to Tach block */
    } `$INSTANCE_NAME`_fanTdInStruct;
#endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

/* DMA Controller SRAM Structure */
typedef struct
{
    #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
        uint16  desiredPeriod[`$INSTANCE_NAME`_NUMBER_OF_FANS];
        uint16  tolerance[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

    #if(CY_PSOC3)
        uint16  actualPeriodDma1[`$INSTANCE_NAME`_NUMBER_OF_FANS];
        uint16  actualPeriodDma2[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    #else
        uint16  actualPeriod[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    #endif /* (CY_PSoC3) */

} `$INSTANCE_NAME`_fanControlStruct;

/* Fan Properties Structure. From parameters entered into the customizer */
typedef struct
{
    uint16 rpmA;
    uint16 rpmB;
    uint16 dutyA;
    uint16 dutyB;
    uint16 dutyRpmSlope;
    uint16 initRpm;
    uint16 initDuty;
} `$INSTANCE_NAME`_fanPropertiesStruct;

/* PWM configuration structure */
#if (!CY_PSOC4)
    #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

        /* An array that holds adresses of PWM configuration registers for Auto
        * Hardware mode.
        */
        typedef struct
        {
            `$INSTANCE_NAME`_RegAddrType  pwmPeriodReg;
            `$INSTANCE_NAME`_RegAddrType  pwmMaxDutyReg;
            `$INSTANCE_NAME`_RegAddrType  pwmSetDutyReg;
            `$INSTANCE_NAME`_RegAddrType  errorCountReg;
        } `$INSTANCE_NAME`_fanDriverRegsStruct;

    #else
        /* An array that holds adresses of PWM configuration registers for Auto
        * Firmware and Manual modes (PSoC 3/5LP).
        */
        typedef struct
        {
            `$INSTANCE_NAME`_RegAddrType  pwmSetDutyReg;
        } `$INSTANCE_NAME`_fanDriverRegsStruct;

        typedef struct
        {
            `$INSTANCE_NAME`_RegAddrType  pwmPeriodReg;
            `$INSTANCE_NAME`_RegAddrType  pwmAuxControlReg;
        } `$INSTANCE_NAME`_fanPwmInitRegsStruct;

        #define `$INSTANCE_NAME`_FANPWM_COUNT                   ((`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS / 2u) + \
                    (`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS % 2u))

        extern const  `$INSTANCE_NAME`_fanPwmInitRegsStruct CYCODE 
            `$INSTANCE_NAME`_fanPwmInitRegs[`$INSTANCE_NAME`_FANPWM_COUNT];

    #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

#else /* PSoC 4 */
    /* An array that holds adresses of PWM configuration registers for Auto
    * Firmware and Manual modes (PSoC 4).
    */
    typedef struct
    {
        `$INSTANCE_NAME`_RegAddrType  pwmSetDutyReg;
    } `$INSTANCE_NAME`_fanDriverRegsStruct;

    typedef struct
    {
        `$INSTANCE_NAME`_RegAddrType  pwmPeriodReg;
    } `$INSTANCE_NAME`_fanPwmInitRegsStruct;

    extern const `$INSTANCE_NAME`_fanPwmInitRegsStruct CYCODE
        `$INSTANCE_NAME`_fanPwmInitRegs[`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS];

#endif /* (!CY_PSOC4) */

extern uint8 `$INSTANCE_NAME`_initVar;

extern `$INSTANCE_NAME`_fanControlStruct `$INSTANCE_NAME`_fanControl;

#if(!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    /* An array ro store desired fans speeds */
    extern uint16 `$INSTANCE_NAME`_desiredFansSpeed[`$INSTANCE_NAME`_NUMBER_OF_FANS];
#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */

/* Array which store PID parameters for each fan */
#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    extern int16 `$INSTANCE_NAME`_pidA1[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    extern int16 `$INSTANCE_NAME`_pidA2[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    extern int16 `$INSTANCE_NAME`_pidA3[`$INSTANCE_NAME`_NUMBER_OF_FANS];

    extern uint32 `$INSTANCE_NAME`_outputSatL[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    extern uint32 `$INSTANCE_NAME`_outputSatH[`$INSTANCE_NAME`_NUMBER_OF_FANS];

    extern volatile uint16 `$INSTANCE_NAME`_speedStatus;
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

extern const `$INSTANCE_NAME`_fanDriverRegsStruct CYCODE
    `$INSTANCE_NAME`_fanDriverRegs[`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS];

extern `$INSTANCE_NAME`_fanPropertiesStruct `$INSTANCE_NAME`_fanProperties[`$INSTANCE_NAME`_NUMBER_OF_FANS];


/***************************************
* Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_MAX_FAN_NUM                 (`$INSTANCE_NAME`_NUMBER_OF_FANS - 1u)
#define `$INSTANCE_NAME`_DAMPING_FACTOR              (`$DampingFactor`u)
#define `$INSTANCE_NAME`_INIT_ALERT_ENABLE           (`$AlertEnable`u)
#define `$INSTANCE_NAME`_NOISE_REDUCTION_MODE        (`$AcousticNoiseReduction`u)
#define `$INSTANCE_NAME`_INIT_ALERT_MASK             ((uint16) (((uint32) 0x01u << `$NumberOfFans`u) - 1u))
#define `$INSTANCE_NAME`_DAMPING_FACTOR_PERIOD_LOW   (250u)
#define `$INSTANCE_NAME`_DAMPING_FACTOR_PERIOD_HIGH  (`$INSTANCE_NAME`_DAMPING_FACTOR)

/* Tolerance parameter and divider to convert it to % */
#define `$INSTANCE_NAME`_TOLERANCE                   (`$FanTolerance`u)
#define `$INSTANCE_NAME`_TOLERANCE_DIVIDER           (100u)

#if (CY_PSOC3)
    #define `$INSTANCE_NAME`_NUM_OUT_TDS                 (`$INSTANCE_NAME`_NUMBER_OF_FANS * 2u)
#else
    #define `$INSTANCE_NAME`_NUM_OUT_TDS                 (`$INSTANCE_NAME`_NUMBER_OF_FANS)
#endif /* (CY_PSOC3) */

/***************************************
*             Registers
***************************************/

/* Buried control/status registers */
#define    `$INSTANCE_NAME`_GLOBAL_CONTROL_REG                    \
                                    (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_GlobalControlReg__CONTROL_REG)
#define    `$INSTANCE_NAME`_GLOBAL_CONTROL_PTR                    \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_GlobalControlReg__CONTROL_REG)

#define    `$INSTANCE_NAME`_EOC_DMA_CONTROL_PTR                \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_DmaControlReg__CONTROL_REG)

/* Alert Mask LSB Control register */
#define `$INSTANCE_NAME`_ALERT_MASK_LSB_CONTROL_REG            \
                                    (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_AlertMaskLSB__CONTROL_REG)
#define `$INSTANCE_NAME`_ALERT_MASK_LSB_CONTROL_PTR            \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_AlertMaskLSB__CONTROL_REG)

#if(`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
    /* Alert Mask MSB Control register */
    #define `$INSTANCE_NAME`_ALERT_MASK_MSB_CONTROL_REG        \
                           (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_CtrlAlertMSB_AlertMaskMSB__CONTROL_REG)
    #define `$INSTANCE_NAME`_ALERT_MASK_MSB_CONTROL_PTR        \
                           (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_CtrlAlertMSB_AlertMaskMSB__CONTROL_REG)
#endif /* (`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u) */

#define `$INSTANCE_NAME`_STALL_ERROR_LSB_STATUS_REG            \
                                    (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_StallError_LSB__STATUS_REG)
#define `$INSTANCE_NAME`_STALL_ERROR_LSB_STATUS_PTR            \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_StallError_LSB__STATUS_REG)

#if(`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
    #define `$INSTANCE_NAME`_STALL_ERROR_MSB_STATUS_REG        \
                                    (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_StallStatusMSB_StallError_MSB__STATUS_REG)
    #define `$INSTANCE_NAME`_STALL_ERROR_MSB_STATUS_PTR        \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_StallStatusMSB_StallError_MSB__STATUS_REG)
#endif /* (`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u) */

#define `$INSTANCE_NAME`_ALERT_STATUS_REG                      \
                                    (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_AlertStatusReg__STATUS_REG)
#define `$INSTANCE_NAME`_ALERT_STATUS_PTR                      \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_AlertStatusReg__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_ALERT_AUX_CTL_REG              \
                                    (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_AlertStatusReg__STATUS_AUX_CTL_REG)
#define `$INSTANCE_NAME`_STATUS_ALERT_AUX_CTL_PTR              \
                                    (  (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_AlertStatusReg__STATUS_AUX_CTL_REG)
#define `$INSTANCE_NAME`_TACH_FAN_COUNTR_AUX_CTL_REG           \
                                    (* (reg8 *) `$INSTANCE_NAME`_FanTach_FanCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_TACH_FAN_COUNTR_AUX_CTL_PTR           \
                                    (  (reg8 *) `$INSTANCE_NAME`_FanTach_FanCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_TACH_GLITCH_FILTER_PERIOD_REG        \
                                    (* (reg8 *)  `$INSTANCE_NAME`_FanTach_GlitchFilterTimer_u0__D0_REG)

#if((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u))
    #define `$INSTANCE_NAME`_DAMPING_COUNTER_DIVIDER_REG        \
                                        (* (reg8 *)  `$INSTANCE_NAME`_FanTach_GlitchFilterTimer_u0__D1_REG)
#endif /* ((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u)) */

#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_TACH_FAN_COUNTER_REG            (* (reg8 *) `$INSTANCE_NAME`_FanTach_FanCounter__COUNT_REG)
    #define `$INSTANCE_NAME`_TACH_FAN_COUNTER_PTR            (  (reg8 *) `$INSTANCE_NAME`_FanTach_FanCounter__COUNT_REG)
#endif /* (CY_PSOC4) */

/* Register defines inside the embedded tach component - these are sources/destinations for DMA controller */
#define `$INSTANCE_NAME`_TACH_TOLERANCE_PTR                  (`$INSTANCE_NAME`_FanTach_FanTachCounter_u0__16BIT_D1_REG)
#define `$INSTANCE_NAME`_TACH_DESIRED_PERIOD_PTR             (`$INSTANCE_NAME`_FanTach_FanTachCounter_u0__16BIT_D0_REG)
#define `$INSTANCE_NAME`_TACH_ACTUAL_PERIOD_PTR              (`$INSTANCE_NAME`_FanTach_FanTachCounter_u0__16BIT_A0_REG)

#if((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u))

    /* Damping Factor counter Registers */
    #define `$INSTANCE_NAME`_TACH_DAMPING_PERIOD_LOW_LSB_REG       \
                                    (*  (reg8 *) `$INSTANCE_NAME`_FanTach_DmpgFactor_DmpgTimeCntr_u0__D0_REG)
    #define `$INSTANCE_NAME`_TACH_DAMPING_PERIOD_LOW_LSB_PTR       \
                                    (   (reg8 *) `$INSTANCE_NAME`_FanTach_DmpgFactor_DmpgTimeCntr_u0__D0_REG)
    #define `$INSTANCE_NAME`_TACH_DAMPING_PERIOD_HIGH_LSB_REG      \
                                    (*  (reg8 *) `$INSTANCE_NAME`_FanTach_DmpgFactor_DmpgTimeCntr_u0__D1_REG)
    #define `$INSTANCE_NAME`_TACH_DAMPING_PERIOD_HIGH_LSB_PTR      \
                                    (   (reg8 *) `$INSTANCE_NAME`_FanTach_DmpgFactor_DmpgTimeCntr_u0__D1_REG)

#endif /* ((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u)) */

#if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
    #define `$INSTANCE_NAME`_SPEED_ERROR_LSB_STATUS_REG           \
                                          (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_SpeedAlrt_SpeedError_LSB__STATUS_REG)

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
        #define `$INSTANCE_NAME`_SPEED_ERROR_MSB_STATUS_REG       \
                                      (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_SpeedAlrt_MSB_SpeedError_MSB__STATUS_REG )
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS > 8u */
#endif /* (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) */

#if(CY_PSOC3)

    /* DMA status. Used to capture the status of DMA state machine */
    #define `$INSTANCE_NAME`_DMA_STATUS_REG     (* (reg8 *) `$INSTANCE_NAME`_B_FanCtrl_DmaEoc_Sm_Dma_Status__STATUS_REG)

#endif /* (CY_PSOC3) */


/***************************************
*       Register Constants
***************************************/

#if(CY_PSOC3)

    #define `$INSTANCE_NAME`_DMA1                       (0x01u)
    #define `$INSTANCE_NAME`_DMA2                       (0x02u)

#endif /* (CY_PSOC3) */

#define `$INSTANCE_NAME`_COUNT7_ENABLE              (0x20u)
#define `$INSTANCE_NAME`_STATUS_ALERT_ENABLE        (0x10u)

#define `$INSTANCE_NAME`_COUNT7_PERIOD_MASK         (0x7Fu)

#if (!CY_PSOC4)
    #if(!`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
        #define `$INSTANCE_NAME`_FANPWM_AUX_CTRL_FIFO0_CLR_8    (0x03u)
        #define `$INSTANCE_NAME`_FANPWM_AUX_CTRL_FIFO0_CLR_10   (0x0303u)
    #endif /* (!`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) */
#endif /* (!CY_PSOC4) */

/* Control Register bit defines */
#define `$INSTANCE_NAME`_ALERT_PIN_ENABLE_SHIFT     (0x00u)
#define `$INSTANCE_NAME`_ALERT_ENABLE_SHIFT         (0x01u)
#define `$INSTANCE_NAME`_STALL_ALERT_ENABLE_SHIFT   (0x01u)
#define `$INSTANCE_NAME`_SPEED_ALERT_ENABLE_SHIFT   (0x02u)
#define `$INSTANCE_NAME`_ENABLE_SHIFT               (0x05u)
#define `$INSTANCE_NAME`_OVERRIDE_SHIFT             (0x06u)

#define `$INSTANCE_NAME`_ALERT_PIN_ENABLE           (uint8)(0x01u << `$INSTANCE_NAME`_ALERT_PIN_ENABLE_SHIFT)
#define `$INSTANCE_NAME`_STALL_ALERT_ENABLE         (uint8)(0x01u << `$INSTANCE_NAME`_STALL_ALERT_ENABLE_SHIFT)
#define `$INSTANCE_NAME`_SPEED_ALERT_ENABLE         (uint8)(0x01u << `$INSTANCE_NAME`_SPEED_ALERT_ENABLE_SHIFT)
#define `$INSTANCE_NAME`_ENABLE                     (uint8)(0x01u << `$INSTANCE_NAME`_ENABLE_SHIFT)
#define `$INSTANCE_NAME`_OVERRIDE                   (0x40u)
#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_SW_EOC                     (0x08u)
#endif /* (CY_PSOC4) */
#if (!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    #define `$INSTANCE_NAME`_SW_SPEED_ERROR             (0x10u)
#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */

#define `$INSTANCE_NAME`_ALERT_ENABLE_MASK          (uint8)(0x03u << `$INSTANCE_NAME`_ALERT_ENABLE_SHIFT)

#define `$INSTANCE_NAME`_ALERT_STATUS_MASK          (0x03u)

#define `$INSTANCE_NAME`_GLITCH_FILTER_VAL          (60u)

#if ((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u))
    #define `$INSTANCE_NAME`_DAMPING_FACTOR_DIVIDER_VAL          (10u)
#endif /* ((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u)) */


/***************************************
*       Obsolete #defines
***************************************/

/* Following #defines are obsolete and will be removed in following versions
* of the component.
*/
#if (!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    #define  `$INSTANCE_NAME`_OverrideHardwareControl(override) \
                                                        `$INSTANCE_NAME`_OverrideAutomaticControl(override)
#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */

#define `$INSTANCE_NAME`_TOLERANCE_FACTOR           ((`$FanTolerance` * 0.01))
#define `$INSTANCE_NAME`_STALL_ALERT_CLEAR_SHIFT    (0x03u)
#define `$INSTANCE_NAME`_SPEED_ALERT_CLEAR_SHIFT    (0x04u)
#define `$INSTANCE_NAME`_ALERT_CLEAR_SHIFT          (0x03u)
#define `$INSTANCE_NAME`_STALL_ALERT_CLEAR          (uint8)(0x01u << `$INSTANCE_NAME`_STALL_ALERT_CLEAR_SHIFT)
#define `$INSTANCE_NAME`_SPEED_ALERT_CLEAR          (uint8)(0x01u << `$INSTANCE_NAME`_SPEED_ALERT_CLEAR_SHIFT)
#define `$INSTANCE_NAME`_ALERT_CLEAR_MASK           (uint8)(0x03u << `$INSTANCE_NAME`_ALERT_CLEAR_SHIFT)

#endif /* `$INSTANCE_NAME`_CY_FAN_CONTROLLER_H */


/* [] END OF FILE */
