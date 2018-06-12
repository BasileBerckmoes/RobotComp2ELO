/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_`$INSTANCE_NAME`_H)
#define CY_PWM_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define `$INSTANCE_NAME`_Resolution                     (`$Resolution`u)
#define `$INSTANCE_NAME`_UsingFixedFunction             (`$FixedFunctionUsed`u)
#define `$INSTANCE_NAME`_DeadBandMode                   (`$DeadBand`u)
#define `$INSTANCE_NAME`_KillModeMinTime                (`$KillModeMinTime`u)
#define `$INSTANCE_NAME`_KillMode                       (`$KillMode`u)
#define `$INSTANCE_NAME`_PWMMode                        (`$PWMMode`u)
#define `$INSTANCE_NAME`_PWMModeIsCenterAligned         (`$PWMModeCenterAligned`u)
#define `$INSTANCE_NAME`_DeadBandUsed                   (`$DeadBandUsed`u)
#define `$INSTANCE_NAME`_DeadBand2_4                    (`$DeadBand2_4`u)

#if !defined(`$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__REMOVED)
    #define `$INSTANCE_NAME`_UseStatus                  (`$UseStatus`u)
#else
    #define `$INSTANCE_NAME`_UseStatus                  (0u)
#endif /* !defined(`$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(`$INSTANCE_NAME`_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define `$INSTANCE_NAME`_UseControl                 (`$UseControl`u)
#else
    #define `$INSTANCE_NAME`_UseControl                 (0u)
#endif /* !defined(`$INSTANCE_NAME`_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define `$INSTANCE_NAME`_UseOneCompareMode              (`$OneCompare`u)
#define `$INSTANCE_NAME`_MinimumKillTime                (`$MinimumKillTime`u)
#define `$INSTANCE_NAME`_EnableMode                     (`$EnableMode`u)

#define `$INSTANCE_NAME`_CompareMode1SW                 (`$CompareType1Software`u)
#define `$INSTANCE_NAME`_CompareMode2SW                 (`$CompareType2Software`u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
`#cy_declare_enum B_PWM__KillModes`

/* Use Dead Band Mode Enumerated Types */
`#cy_declare_enum B_PWM__DeadBandModes`

/* Used PWM Mode Enumerated Types */
`#cy_declare_enum B_PWM__PWMModes`

/* Used PWM Compare Mode Enumerated Types */
`#cy_declare_enum B_PWM__CompareTypes`


/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!`$INSTANCE_NAME`_UsingFixedFunction)
        `$RegSizeReplacementString` PWMUdb;               /* PWM Current Counter value  */
        #if(!`$INSTANCE_NAME`_PWMModeIsCenterAligned)
            `$RegSizeReplacementString` PWMPeriod;
        #endif /* (!`$INSTANCE_NAME`_PWMModeIsCenterAligned) */
        #if (`$INSTANCE_NAME`_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (`$INSTANCE_NAME`_UseStatus) */

        /* Backup for Deadband parameters */
        #if(`$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_256_CLOCKS || \
            `$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(`$INSTANCE_NAME`_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (`$INSTANCE_NAME`_KillModeMinTime) */

        /* Backup control register */
        #if(`$INSTANCE_NAME`_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (`$INSTANCE_NAME`_UseControl) */

    #endif /* (!`$INSTANCE_NAME`_UsingFixedFunction) */

}`$INSTANCE_NAME`_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void    `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;

#if (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction)
    void  `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptMode) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`;
    uint8 `$INSTANCE_NAME`_ReadStatusRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatusRegister")`;
#endif /* (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction) */

#define `$INSTANCE_NAME`_GetInterruptSource() `$INSTANCE_NAME`_ReadStatusRegister()

#if (`$INSTANCE_NAME`_UseControl)
    uint8 `$INSTANCE_NAME`_ReadControlRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadControlRegister")`;
    void  `$INSTANCE_NAME`_WriteControlRegister(uint8 control)
          `=ReentrantKeil($INSTANCE_NAME . "_WriteControlRegister")`;
#endif /* (`$INSTANCE_NAME`_UseControl) */

#if (`$INSTANCE_NAME`_UseOneCompareMode)
   #if (`$INSTANCE_NAME`_CompareMode1SW)
       void    `$INSTANCE_NAME`_SetCompareMode(uint8 comparemode)
               `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode")`;
   #endif /* (`$INSTANCE_NAME`_CompareMode1SW) */
#else
    #if (`$INSTANCE_NAME`_CompareMode1SW)
        void    `$INSTANCE_NAME`_SetCompareMode1(uint8 comparemode)
                `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode1")`;
    #endif /* (`$INSTANCE_NAME`_CompareMode1SW) */
    #if (`$INSTANCE_NAME`_CompareMode2SW)
        void    `$INSTANCE_NAME`_SetCompareMode2(uint8 comparemode)
                `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode2")`;
    #endif /* (`$INSTANCE_NAME`_CompareMode2SW) */
#endif /* (`$INSTANCE_NAME`_UseOneCompareMode) */

#if (!`$INSTANCE_NAME`_UsingFixedFunction)
    `$RegSizeReplacementString`   `$INSTANCE_NAME`_ReadCounter(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCounter")`;
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCapture(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCapture")`;

    #if (`$INSTANCE_NAME`_UseStatus)
            void `$INSTANCE_NAME`_ClearFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`;
    #endif /* (`$INSTANCE_NAME`_UseStatus) */

    void    `$INSTANCE_NAME`_WriteCounter(`$RegSizeReplacementString` counter)
            `=ReentrantKeil($INSTANCE_NAME . "_WriteCounter")`;
#endif /* (!`$INSTANCE_NAME`_UsingFixedFunction) */

void    `$INSTANCE_NAME`_WritePeriod(`$RegSizeReplacementString` period)
        `=ReentrantKeil($INSTANCE_NAME . "_WritePeriod")`;
`$RegSizeReplacementString` `$INSTANCE_NAME`_ReadPeriod(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadPeriod")`;

#if (`$INSTANCE_NAME`_UseOneCompareMode)
    void    `$INSTANCE_NAME`_WriteCompare(`$RegSizeReplacementString` compare)
            `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare")`;
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCompare(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare")`;
#else
    void    `$INSTANCE_NAME`_WriteCompare1(`$RegSizeReplacementString` compare)
            `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare1")`;
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCompare1(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare1")`;
    void    `$INSTANCE_NAME`_WriteCompare2(`$RegSizeReplacementString` compare)
            `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare2")`;
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCompare2(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare2")`;
#endif /* (`$INSTANCE_NAME`_UseOneCompareMode) */


#if (`$INSTANCE_NAME`_DeadBandUsed)
    void    `$INSTANCE_NAME`_WriteDeadTime(uint8 deadtime) `=ReentrantKeil($INSTANCE_NAME . "_WriteDeadTime")`;
    uint8   `$INSTANCE_NAME`_ReadDeadTime(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadDeadTime")`;
#endif /* (`$INSTANCE_NAME`_DeadBandUsed) */

#if ( `$INSTANCE_NAME`_KillModeMinTime)
    void `$INSTANCE_NAME`_WriteKillTime(uint8 killtime) `=ReentrantKeil($INSTANCE_NAME . "_WriteKillTime")`;
    uint8 `$INSTANCE_NAME`_ReadKillTime(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadKillTime")`;
#endif /* ( `$INSTANCE_NAME`_KillModeMinTime) */

void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;


/***************************************
*         Initialization Values
**************************************/
#define `$INSTANCE_NAME`_INIT_PERIOD_VALUE          (`$Period`u)
#define `$INSTANCE_NAME`_INIT_COMPARE_VALUE1        (`$CompareValue1`u)
#define `$INSTANCE_NAME`_INIT_COMPARE_VALUE2        (`$CompareValue2`u)
#define `$INSTANCE_NAME`_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(`$IntOnTC`u <<   \
                                                    `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(`$IntOnCMP2`u <<  \
                                                    `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(`$IntOnCMP1`u <<  \
                                                    `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(`$IntOnKill`u <<  \
                                                    `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define `$INSTANCE_NAME`_DEFAULT_COMPARE2_MODE      (uint8)((uint8)`$CompareType2`u <<  `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
#define `$INSTANCE_NAME`_DEFAULT_COMPARE1_MODE      (uint8)((uint8)`$CompareType1`u <<  `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)
#define `$INSTANCE_NAME`_INIT_DEAD_TIME             (`$DeadTime`u)


/********************************
*         Registers
******************************** */

#if (`$INSTANCE_NAME`_UsingFixedFunction)
   #define `$INSTANCE_NAME`_PERIOD_LSB              (*(reg16 *) `$INSTANCE_NAME`_PWMHW__PER0)
   #define `$INSTANCE_NAME`_PERIOD_LSB_PTR          ( (reg16 *) `$INSTANCE_NAME`_PWMHW__PER0)
   #define `$INSTANCE_NAME`_COMPARE1_LSB            (*(reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_COMPARE1_LSB_PTR        ( (reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_COMPARE2_LSB            (0x00u)
   #define `$INSTANCE_NAME`_COMPARE2_LSB_PTR        (0x00u)
   #define `$INSTANCE_NAME`_COUNTER_LSB             (*(reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_COUNTER_LSB_PTR         ( (reg16 *) `$INSTANCE_NAME`_PWMHW__CNT_CMP0)
   #define `$INSTANCE_NAME`_CAPTURE_LSB             (*(reg16 *) `$INSTANCE_NAME`_PWMHW__CAP0)
   #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR         ( (reg16 *) `$INSTANCE_NAME`_PWMHW__CAP0)
   #define `$INSTANCE_NAME`_RT1                     (*(reg8 *)  `$INSTANCE_NAME`_PWMHW__RT1)
   #define `$INSTANCE_NAME`_RT1_PTR                 ( (reg8 *)  `$INSTANCE_NAME`_PWMHW__RT1)

#else
   #if (`$INSTANCE_NAME`_Resolution == 8u) /* 8bit - PWM */

       #if(`$INSTANCE_NAME`_PWMModeIsCenterAligned)
           #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
           #define `$INSTANCE_NAME`_PERIOD_LSB_PTR  ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
       #else
           #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F0_REG)
           #define `$INSTANCE_NAME`_PERIOD_LSB_PTR  ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F0_REG)
       #endif /* (`$INSTANCE_NAME`_PWMModeIsCenterAligned) */

       #define `$INSTANCE_NAME`_COMPARE1_LSB        (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D0_REG)
       #define `$INSTANCE_NAME`_COMPARE1_LSB_PTR    ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D0_REG)
       #define `$INSTANCE_NAME`_COMPARE2_LSB        (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
       #define `$INSTANCE_NAME`_COMPARE2_LSB_PTR    ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
       #define `$INSTANCE_NAME`_COUNTERCAP_LSB      (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
       #define `$INSTANCE_NAME`_COUNTERCAP_LSB_PTR  ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
       #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A0_REG)
       #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A0_REG)
       #define `$INSTANCE_NAME`_CAPTURE_LSB         (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F1_REG)
       #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR     ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(`$INSTANCE_NAME`_PWMModeIsCenterAligned)
               #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
               #define `$INSTANCE_NAME`_PERIOD_LSB_PTR  ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
            #else
               #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F0_REG)
               #define `$INSTANCE_NAME`_PERIOD_LSB_PTR  ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F0_REG)
            #endif /* (`$INSTANCE_NAME`_PWMModeIsCenterAligned) */

            #define `$INSTANCE_NAME`_COMPARE1_LSB       (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D0_REG)
            #define `$INSTANCE_NAME`_COMPARE1_LSB_PTR   ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D0_REG)
            #define `$INSTANCE_NAME`_COMPARE2_LSB       (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
            #define `$INSTANCE_NAME`_COMPARE2_LSB_PTR   ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__D1_REG)
            #define `$INSTANCE_NAME`_COUNTERCAP_LSB     (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
            #define `$INSTANCE_NAME`_COUNTERCAP_LSB_PTR ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
            #define `$INSTANCE_NAME`_COUNTER_LSB        (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A0_REG)
            #define `$INSTANCE_NAME`_COUNTER_LSB_PTR    ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A0_REG)
            #define `$INSTANCE_NAME`_CAPTURE_LSB        (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F1_REG)
            #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR    ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__F1_REG)
        #else
            #if(`$INSTANCE_NAME`_PWMModeIsCenterAligned)
               #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_D1_REG)
               #define `$INSTANCE_NAME`_PERIOD_LSB_PTR  ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_D1_REG)
            #else
               #define `$INSTANCE_NAME`_PERIOD_LSB      (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_F0_REG)
               #define `$INSTANCE_NAME`_PERIOD_LSB_PTR  ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_F0_REG)
            #endif /* (`$INSTANCE_NAME`_PWMModeIsCenterAligned) */

            #define `$INSTANCE_NAME`_COMPARE1_LSB       (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_D0_REG)
            #define `$INSTANCE_NAME`_COMPARE1_LSB_PTR   ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_D0_REG)
            #define `$INSTANCE_NAME`_COMPARE2_LSB       (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_D1_REG)
            #define `$INSTANCE_NAME`_COMPARE2_LSB_PTR   ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_D1_REG)
            #define `$INSTANCE_NAME`_COUNTERCAP_LSB     (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_A1_REG)
            #define `$INSTANCE_NAME`_COUNTERCAP_LSB_PTR ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_A1_REG)
            #define `$INSTANCE_NAME`_COUNTER_LSB        (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_A0_REG)
            #define `$INSTANCE_NAME`_COUNTER_LSB_PTR    ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_A0_REG)
            #define `$INSTANCE_NAME`_CAPTURE_LSB        (*(reg16 *) `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_F1_REG)
            #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR    ((reg16 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define `$INSTANCE_NAME`_AUX_CONTROLDP1          (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u1__DP_AUX_CTL_REG)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP1_PTR      ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (`$INSTANCE_NAME`_Resolution == 8) */

   #define `$INSTANCE_NAME`_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__A1_REG)
   #define `$INSTANCE_NAME`_AUX_CONTROLDP0          (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__DP_AUX_CTL_REG)
   #define `$INSTANCE_NAME`_AUX_CONTROLDP0_PTR      ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_`$VerilogSectionReplacementString`_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */

#if(`$INSTANCE_NAME`_KillModeMinTime )
    #define `$INSTANCE_NAME`_KILLMODEMINTIME        (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define `$INSTANCE_NAME`_KILLMODEMINTIME_PTR    ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (`$INSTANCE_NAME`_KillModeMinTime ) */

#if(`$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_256_CLOCKS)
    #define `$INSTANCE_NAME`_DEADBAND_COUNT         (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define `$INSTANCE_NAME`_DEADBAND_COUNT_PTR     ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define `$INSTANCE_NAME`_DEADBAND_LSB_PTR       ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define `$INSTANCE_NAME`_DEADBAND_LSB           (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(`$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (`$INSTANCE_NAME`_UsingFixedFunction)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT         (*(reg8 *)  `$INSTANCE_NAME`_PWMHW__CFG0)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_PTR     ((reg8 *)   `$INSTANCE_NAME`_PWMHW__CFG0)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define `$INSTANCE_NAME`_DEADBAND_COUNT         (*(reg8 *)  `$INSTANCE_NAME`_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_PTR     ((reg8 *)   `$INSTANCE_NAME`_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
#endif /* (`$INSTANCE_NAME`_DeadBandMode == `$INSTANCE_NAME`__B_PWM__DBM_256_CLOCKS) */



#if (`$INSTANCE_NAME`_UsingFixedFunction)
    #define `$INSTANCE_NAME`_STATUS                 (*(reg8 *) `$INSTANCE_NAME`_PWMHW__SR0)
    #define `$INSTANCE_NAME`_STATUS_PTR             ((reg8 *) `$INSTANCE_NAME`_PWMHW__SR0)
    #define `$INSTANCE_NAME`_STATUS_MASK            (*(reg8 *) `$INSTANCE_NAME`_PWMHW__SR0)
    #define `$INSTANCE_NAME`_STATUS_MASK_PTR        ((reg8 *) `$INSTANCE_NAME`_PWMHW__SR0)
    #define `$INSTANCE_NAME`_CONTROL                (*(reg8 *) `$INSTANCE_NAME`_PWMHW__CFG0)
    #define `$INSTANCE_NAME`_CONTROL_PTR            ((reg8 *) `$INSTANCE_NAME`_PWMHW__CFG0)
    #define `$INSTANCE_NAME`_CONTROL2               (*(reg8 *) `$INSTANCE_NAME`_PWMHW__CFG1)
    #define `$INSTANCE_NAME`_CONTROL3               (*(reg8 *) `$INSTANCE_NAME`_PWMHW__CFG2)
    #define `$INSTANCE_NAME`_GLOBAL_ENABLE          (*(reg8 *) `$INSTANCE_NAME`_PWMHW__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_ENABLE_PTR      ( (reg8 *) `$INSTANCE_NAME`_PWMHW__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE     (*(reg8 *) `$INSTANCE_NAME`_PWMHW__PM_STBY_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) `$INSTANCE_NAME`_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define `$INSTANCE_NAME`_BLOCK_EN_MASK          (`$INSTANCE_NAME`_PWMHW__PM_ACT_MSK)
    #define `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK     (`$INSTANCE_NAME`_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define `$INSTANCE_NAME`_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define `$INSTANCE_NAME`_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define `$INSTANCE_NAME`_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define `$INSTANCE_NAME`_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            (uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_RESET             (uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_RESET_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define `$INSTANCE_NAME`_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define `$INSTANCE_NAME`_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK_SHIFT            (`$INSTANCE_NAME`_STATUS_TC_SHIFT - 4u)
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK_SHIFT          (`$INSTANCE_NAME`_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_TC              (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP1            (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK              (uint8)((uint8)`$INSTANCE_NAME`_STATUS_TC >> 4u)
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)`$INSTANCE_NAME`_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define `$INSTANCE_NAME`_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define `$INSTANCE_NAME`_RT1_MASK              (uint8)((uint8)0x03u << `$INSTANCE_NAME`_RT1_SHIFT)
    #define `$INSTANCE_NAME`_SYNC                  (uint8)((uint8)0x03u << `$INSTANCE_NAME`_RT1_SHIFT)
    #define `$INSTANCE_NAME`_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define `$INSTANCE_NAME`_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << `$INSTANCE_NAME`_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define `$INSTANCE_NAME`_SYNCDSI_EN            (uint8)((uint8)0x0Fu << `$INSTANCE_NAME`_SYNCDSI_SHIFT)


#else
    #define `$INSTANCE_NAME`_STATUS                (*(reg8 *)   `$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define `$INSTANCE_NAME`_STATUS_PTR            ((reg8 *)    `$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define `$INSTANCE_NAME`_STATUS_MASK           (*(reg8 *)   `$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_MASK_PTR       ((reg8 *)    `$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__MASK_REG)
    #define `$INSTANCE_NAME`_STATUS_AUX_CTRL       (*(reg8 *)   `$INSTANCE_NAME`_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_CONTROL               (*(reg8 *)   `$INSTANCE_NAME`_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define `$INSTANCE_NAME`_CONTROL_PTR           ((reg8 *)    `$INSTANCE_NAME`_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      (0x07u)
    #define `$INSTANCE_NAME`_CTRL_RESET_SHIFT       (0x06u)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define `$INSTANCE_NAME`_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            (uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_RESET             (uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_RESET_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
    #define `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_SHIFT          (0x05u)
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define `$INSTANCE_NAME`_STATUS_TC_SHIFT            (0x02u)
    #define `$INSTANCE_NAME`_STATUS_CMP2_SHIFT          (0x01u)
    #define `$INSTANCE_NAME`_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK_SHIFT          (`$INSTANCE_NAME`_STATUS_KILL_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (`$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (`$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK_SHIFT            (`$INSTANCE_NAME`_STATUS_TC_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK_SHIFT          (`$INSTANCE_NAME`_STATUS_CMP2_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK_SHIFT          (`$INSTANCE_NAME`_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define `$INSTANCE_NAME`_STATUS_KILL            (uint8)((uint8)0x00u << `$INSTANCE_NAME`_STATUS_KILL_SHIFT )
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL        (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_FIFONEMPTY_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_TC              (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_TC_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP2            (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_CMP2_SHIFT)
    #define `$INSTANCE_NAME`_STATUS_CMP1            (uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_KILL_INT_EN_MASK            (`$INSTANCE_NAME`_STATUS_KILL)
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK        (`$INSTANCE_NAME`_STATUS_FIFOFULL)
    #define `$INSTANCE_NAME`_STATUS_FIFONEMPTY_INT_EN_MASK      (`$INSTANCE_NAME`_STATUS_FIFONEMPTY)
    #define `$INSTANCE_NAME`_STATUS_TC_INT_EN_MASK              (`$INSTANCE_NAME`_STATUS_TC)
    #define `$INSTANCE_NAME`_STATUS_CMP2_INT_EN_MASK            (`$INSTANCE_NAME`_STATUS_CMP2)
    #define `$INSTANCE_NAME`_STATUS_CMP1_INT_EN_MASK            (`$INSTANCE_NAME`_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* `$INSTANCE_NAME`_UsingFixedFunction */

#endif  /* CY_PWM_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
