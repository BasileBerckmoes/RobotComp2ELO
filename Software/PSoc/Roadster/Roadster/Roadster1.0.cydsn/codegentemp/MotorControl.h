/*******************************************************************************
* File Name: MotorControl.h
* Version 3.30
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

#if !defined(CY_PWM_MotorControl_H)
#define CY_PWM_MotorControl_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MotorControl_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define MotorControl_Resolution                     (8u)
#define MotorControl_UsingFixedFunction             (0u)
#define MotorControl_DeadBandMode                   (0u)
#define MotorControl_KillModeMinTime                (0u)
#define MotorControl_KillMode                       (0u)
#define MotorControl_PWMMode                        (1u)
#define MotorControl_PWMModeIsCenterAligned         (0u)
#define MotorControl_DeadBandUsed                   (0u)
#define MotorControl_DeadBand2_4                    (0u)

#if !defined(MotorControl_PWMUDB_genblk8_stsreg__REMOVED)
    #define MotorControl_UseStatus                  (1u)
#else
    #define MotorControl_UseStatus                  (0u)
#endif /* !defined(MotorControl_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(MotorControl_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define MotorControl_UseControl                 (1u)
#else
    #define MotorControl_UseControl                 (0u)
#endif /* !defined(MotorControl_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define MotorControl_UseOneCompareMode              (0u)
#define MotorControl_MinimumKillTime                (1u)
#define MotorControl_EnableMode                     (0u)

#define MotorControl_CompareMode1SW                 (0u)
#define MotorControl_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define MotorControl__B_PWM__DISABLED 0
#define MotorControl__B_PWM__ASYNCHRONOUS 1
#define MotorControl__B_PWM__SINGLECYCLE 2
#define MotorControl__B_PWM__LATCHED 3
#define MotorControl__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define MotorControl__B_PWM__DBMDISABLED 0
#define MotorControl__B_PWM__DBM_2_4_CLOCKS 1
#define MotorControl__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define MotorControl__B_PWM__ONE_OUTPUT 0
#define MotorControl__B_PWM__TWO_OUTPUTS 1
#define MotorControl__B_PWM__DUAL_EDGE 2
#define MotorControl__B_PWM__CENTER_ALIGN 3
#define MotorControl__B_PWM__DITHER 5
#define MotorControl__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define MotorControl__B_PWM__LESS_THAN 1
#define MotorControl__B_PWM__LESS_THAN_OR_EQUAL 2
#define MotorControl__B_PWM__GREATER_THAN 3
#define MotorControl__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define MotorControl__B_PWM__EQUAL 0
#define MotorControl__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!MotorControl_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!MotorControl_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!MotorControl_PWMModeIsCenterAligned) */
        #if (MotorControl_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (MotorControl_UseStatus) */

        /* Backup for Deadband parameters */
        #if(MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_256_CLOCKS || \
            MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(MotorControl_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (MotorControl_KillModeMinTime) */

        /* Backup control register */
        #if(MotorControl_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (MotorControl_UseControl) */

    #endif /* (!MotorControl_UsingFixedFunction) */

}MotorControl_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    MotorControl_Start(void) ;
void    MotorControl_Stop(void) ;

#if (MotorControl_UseStatus || MotorControl_UsingFixedFunction)
    void  MotorControl_SetInterruptMode(uint8 interruptMode) ;
    uint8 MotorControl_ReadStatusRegister(void) ;
#endif /* (MotorControl_UseStatus || MotorControl_UsingFixedFunction) */

#define MotorControl_GetInterruptSource() MotorControl_ReadStatusRegister()

#if (MotorControl_UseControl)
    uint8 MotorControl_ReadControlRegister(void) ;
    void  MotorControl_WriteControlRegister(uint8 control)
          ;
#endif /* (MotorControl_UseControl) */

#if (MotorControl_UseOneCompareMode)
   #if (MotorControl_CompareMode1SW)
       void    MotorControl_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (MotorControl_CompareMode1SW) */
#else
    #if (MotorControl_CompareMode1SW)
        void    MotorControl_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (MotorControl_CompareMode1SW) */
    #if (MotorControl_CompareMode2SW)
        void    MotorControl_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (MotorControl_CompareMode2SW) */
#endif /* (MotorControl_UseOneCompareMode) */

#if (!MotorControl_UsingFixedFunction)
    uint8   MotorControl_ReadCounter(void) ;
    uint8 MotorControl_ReadCapture(void) ;

    #if (MotorControl_UseStatus)
            void MotorControl_ClearFIFO(void) ;
    #endif /* (MotorControl_UseStatus) */

    void    MotorControl_WriteCounter(uint8 counter)
            ;
#endif /* (!MotorControl_UsingFixedFunction) */

void    MotorControl_WritePeriod(uint8 period)
        ;
uint8 MotorControl_ReadPeriod(void) ;

#if (MotorControl_UseOneCompareMode)
    void    MotorControl_WriteCompare(uint8 compare)
            ;
    uint8 MotorControl_ReadCompare(void) ;
#else
    void    MotorControl_WriteCompare1(uint8 compare)
            ;
    uint8 MotorControl_ReadCompare1(void) ;
    void    MotorControl_WriteCompare2(uint8 compare)
            ;
    uint8 MotorControl_ReadCompare2(void) ;
#endif /* (MotorControl_UseOneCompareMode) */


#if (MotorControl_DeadBandUsed)
    void    MotorControl_WriteDeadTime(uint8 deadtime) ;
    uint8   MotorControl_ReadDeadTime(void) ;
#endif /* (MotorControl_DeadBandUsed) */

#if ( MotorControl_KillModeMinTime)
    void MotorControl_WriteKillTime(uint8 killtime) ;
    uint8 MotorControl_ReadKillTime(void) ;
#endif /* ( MotorControl_KillModeMinTime) */

void MotorControl_Init(void) ;
void MotorControl_Enable(void) ;
void MotorControl_Sleep(void) ;
void MotorControl_Wakeup(void) ;
void MotorControl_SaveConfig(void) ;
void MotorControl_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define MotorControl_INIT_PERIOD_VALUE          (255u)
#define MotorControl_INIT_COMPARE_VALUE1        (10u)
#define MotorControl_INIT_COMPARE_VALUE2        (10u)
#define MotorControl_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    MotorControl_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorControl_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorControl_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorControl_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define MotorControl_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  MotorControl_CTRL_CMPMODE2_SHIFT)
#define MotorControl_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  MotorControl_CTRL_CMPMODE1_SHIFT)
#define MotorControl_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (MotorControl_UsingFixedFunction)
   #define MotorControl_PERIOD_LSB              (*(reg16 *) MotorControl_PWMHW__PER0)
   #define MotorControl_PERIOD_LSB_PTR          ( (reg16 *) MotorControl_PWMHW__PER0)
   #define MotorControl_COMPARE1_LSB            (*(reg16 *) MotorControl_PWMHW__CNT_CMP0)
   #define MotorControl_COMPARE1_LSB_PTR        ( (reg16 *) MotorControl_PWMHW__CNT_CMP0)
   #define MotorControl_COMPARE2_LSB            (0x00u)
   #define MotorControl_COMPARE2_LSB_PTR        (0x00u)
   #define MotorControl_COUNTER_LSB             (*(reg16 *) MotorControl_PWMHW__CNT_CMP0)
   #define MotorControl_COUNTER_LSB_PTR         ( (reg16 *) MotorControl_PWMHW__CNT_CMP0)
   #define MotorControl_CAPTURE_LSB             (*(reg16 *) MotorControl_PWMHW__CAP0)
   #define MotorControl_CAPTURE_LSB_PTR         ( (reg16 *) MotorControl_PWMHW__CAP0)
   #define MotorControl_RT1                     (*(reg8 *)  MotorControl_PWMHW__RT1)
   #define MotorControl_RT1_PTR                 ( (reg8 *)  MotorControl_PWMHW__RT1)

#else
   #if (MotorControl_Resolution == 8u) /* 8bit - PWM */

       #if(MotorControl_PWMModeIsCenterAligned)
           #define MotorControl_PERIOD_LSB      (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define MotorControl_PERIOD_LSB_PTR  ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define MotorControl_PERIOD_LSB      (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define MotorControl_PERIOD_LSB_PTR  ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (MotorControl_PWMModeIsCenterAligned) */

       #define MotorControl_COMPARE1_LSB        (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define MotorControl_COMPARE1_LSB_PTR    ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define MotorControl_COMPARE2_LSB        (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define MotorControl_COMPARE2_LSB_PTR    ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define MotorControl_COUNTERCAP_LSB      (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define MotorControl_COUNTERCAP_LSB_PTR  ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define MotorControl_COUNTER_LSB         (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define MotorControl_COUNTER_LSB_PTR     ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define MotorControl_CAPTURE_LSB         (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define MotorControl_CAPTURE_LSB_PTR     ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(MotorControl_PWMModeIsCenterAligned)
               #define MotorControl_PERIOD_LSB      (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define MotorControl_PERIOD_LSB_PTR  ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define MotorControl_PERIOD_LSB      (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define MotorControl_PERIOD_LSB_PTR  ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (MotorControl_PWMModeIsCenterAligned) */

            #define MotorControl_COMPARE1_LSB       (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define MotorControl_COMPARE1_LSB_PTR   ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define MotorControl_COMPARE2_LSB       (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define MotorControl_COMPARE2_LSB_PTR   ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define MotorControl_COUNTERCAP_LSB     (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define MotorControl_COUNTERCAP_LSB_PTR ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define MotorControl_COUNTER_LSB        (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define MotorControl_COUNTER_LSB_PTR    ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define MotorControl_CAPTURE_LSB        (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define MotorControl_CAPTURE_LSB_PTR    ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(MotorControl_PWMModeIsCenterAligned)
               #define MotorControl_PERIOD_LSB      (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define MotorControl_PERIOD_LSB_PTR  ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define MotorControl_PERIOD_LSB      (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define MotorControl_PERIOD_LSB_PTR  ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (MotorControl_PWMModeIsCenterAligned) */

            #define MotorControl_COMPARE1_LSB       (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define MotorControl_COMPARE1_LSB_PTR   ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define MotorControl_COMPARE2_LSB       (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define MotorControl_COMPARE2_LSB_PTR   ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define MotorControl_COUNTERCAP_LSB     (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define MotorControl_COUNTERCAP_LSB_PTR ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define MotorControl_COUNTER_LSB        (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define MotorControl_COUNTER_LSB_PTR    ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define MotorControl_CAPTURE_LSB        (*(reg16 *) MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define MotorControl_CAPTURE_LSB_PTR    ((reg16 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define MotorControl_AUX_CONTROLDP1          (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define MotorControl_AUX_CONTROLDP1_PTR      ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (MotorControl_Resolution == 8) */

   #define MotorControl_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define MotorControl_AUX_CONTROLDP0          (*(reg8 *)  MotorControl_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define MotorControl_AUX_CONTROLDP0_PTR      ((reg8 *)   MotorControl_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (MotorControl_UsingFixedFunction) */

#if(MotorControl_KillModeMinTime )
    #define MotorControl_KILLMODEMINTIME        (*(reg8 *)  MotorControl_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define MotorControl_KILLMODEMINTIME_PTR    ((reg8 *)   MotorControl_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (MotorControl_KillModeMinTime ) */

#if(MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_256_CLOCKS)
    #define MotorControl_DEADBAND_COUNT         (*(reg8 *)  MotorControl_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorControl_DEADBAND_COUNT_PTR     ((reg8 *)   MotorControl_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorControl_DEADBAND_LSB_PTR       ((reg8 *)   MotorControl_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define MotorControl_DEADBAND_LSB           (*(reg8 *)  MotorControl_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (MotorControl_UsingFixedFunction)
        #define MotorControl_DEADBAND_COUNT         (*(reg8 *)  MotorControl_PWMHW__CFG0)
        #define MotorControl_DEADBAND_COUNT_PTR     ((reg8 *)   MotorControl_PWMHW__CFG0)
        #define MotorControl_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorControl_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define MotorControl_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define MotorControl_DEADBAND_COUNT         (*(reg8 *)  MotorControl_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorControl_DEADBAND_COUNT_PTR     ((reg8 *)   MotorControl_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorControl_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorControl_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define MotorControl_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (MotorControl_UsingFixedFunction) */
#endif /* (MotorControl_DeadBandMode == MotorControl__B_PWM__DBM_256_CLOCKS) */



#if (MotorControl_UsingFixedFunction)
    #define MotorControl_STATUS                 (*(reg8 *) MotorControl_PWMHW__SR0)
    #define MotorControl_STATUS_PTR             ((reg8 *) MotorControl_PWMHW__SR0)
    #define MotorControl_STATUS_MASK            (*(reg8 *) MotorControl_PWMHW__SR0)
    #define MotorControl_STATUS_MASK_PTR        ((reg8 *) MotorControl_PWMHW__SR0)
    #define MotorControl_CONTROL                (*(reg8 *) MotorControl_PWMHW__CFG0)
    #define MotorControl_CONTROL_PTR            ((reg8 *) MotorControl_PWMHW__CFG0)
    #define MotorControl_CONTROL2               (*(reg8 *) MotorControl_PWMHW__CFG1)
    #define MotorControl_CONTROL3               (*(reg8 *) MotorControl_PWMHW__CFG2)
    #define MotorControl_GLOBAL_ENABLE          (*(reg8 *) MotorControl_PWMHW__PM_ACT_CFG)
    #define MotorControl_GLOBAL_ENABLE_PTR      ( (reg8 *) MotorControl_PWMHW__PM_ACT_CFG)
    #define MotorControl_GLOBAL_STBY_ENABLE     (*(reg8 *) MotorControl_PWMHW__PM_STBY_CFG)
    #define MotorControl_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) MotorControl_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define MotorControl_BLOCK_EN_MASK          (MotorControl_PWMHW__PM_ACT_MSK)
    #define MotorControl_BLOCK_STBY_EN_MASK     (MotorControl_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define MotorControl_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define MotorControl_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define MotorControl_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define MotorControl_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define MotorControl_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define MotorControl_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define MotorControl_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorControl_CTRL_ENABLE_SHIFT)
    #define MotorControl_CTRL_RESET             (uint8)((uint8)0x01u << MotorControl_CTRL_RESET_SHIFT)
    #define MotorControl_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorControl_CTRL_CMPMODE2_SHIFT)
    #define MotorControl_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorControl_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MotorControl_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define MotorControl_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << MotorControl_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define MotorControl_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define MotorControl_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define MotorControl_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define MotorControl_STATUS_TC_INT_EN_MASK_SHIFT            (MotorControl_STATUS_TC_SHIFT - 4u)
    #define MotorControl_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define MotorControl_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorControl_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define MotorControl_STATUS_TC              (uint8)((uint8)0x01u << MotorControl_STATUS_TC_SHIFT)
    #define MotorControl_STATUS_CMP1            (uint8)((uint8)0x01u << MotorControl_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define MotorControl_STATUS_TC_INT_EN_MASK              (uint8)((uint8)MotorControl_STATUS_TC >> 4u)
    #define MotorControl_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)MotorControl_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define MotorControl_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define MotorControl_RT1_MASK              (uint8)((uint8)0x03u << MotorControl_RT1_SHIFT)
    #define MotorControl_SYNC                  (uint8)((uint8)0x03u << MotorControl_RT1_SHIFT)
    #define MotorControl_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define MotorControl_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << MotorControl_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define MotorControl_SYNCDSI_EN            (uint8)((uint8)0x0Fu << MotorControl_SYNCDSI_SHIFT)


#else
    #define MotorControl_STATUS                (*(reg8 *)   MotorControl_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorControl_STATUS_PTR            ((reg8 *)    MotorControl_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorControl_STATUS_MASK           (*(reg8 *)   MotorControl_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorControl_STATUS_MASK_PTR       ((reg8 *)    MotorControl_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorControl_STATUS_AUX_CTRL       (*(reg8 *)   MotorControl_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define MotorControl_CONTROL               (*(reg8 *)   MotorControl_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define MotorControl_CONTROL_PTR           ((reg8 *)    MotorControl_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define MotorControl_CTRL_ENABLE_SHIFT      (0x07u)
    #define MotorControl_CTRL_RESET_SHIFT       (0x06u)
    #define MotorControl_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define MotorControl_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define MotorControl_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define MotorControl_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorControl_CTRL_ENABLE_SHIFT)
    #define MotorControl_CTRL_RESET             (uint8)((uint8)0x01u << MotorControl_CTRL_RESET_SHIFT)
    #define MotorControl_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorControl_CTRL_CMPMODE2_SHIFT)
    #define MotorControl_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorControl_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define MotorControl_STATUS_KILL_SHIFT          (0x05u)
    #define MotorControl_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define MotorControl_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define MotorControl_STATUS_TC_SHIFT            (0x02u)
    #define MotorControl_STATUS_CMP2_SHIFT          (0x01u)
    #define MotorControl_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define MotorControl_STATUS_KILL_INT_EN_MASK_SHIFT          (MotorControl_STATUS_KILL_SHIFT)
    #define MotorControl_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (MotorControl_STATUS_FIFONEMPTY_SHIFT)
    #define MotorControl_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (MotorControl_STATUS_FIFOFULL_SHIFT)
    #define MotorControl_STATUS_TC_INT_EN_MASK_SHIFT            (MotorControl_STATUS_TC_SHIFT)
    #define MotorControl_STATUS_CMP2_INT_EN_MASK_SHIFT          (MotorControl_STATUS_CMP2_SHIFT)
    #define MotorControl_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorControl_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define MotorControl_STATUS_KILL            (uint8)((uint8)0x00u << MotorControl_STATUS_KILL_SHIFT )
    #define MotorControl_STATUS_FIFOFULL        (uint8)((uint8)0x01u << MotorControl_STATUS_FIFOFULL_SHIFT)
    #define MotorControl_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << MotorControl_STATUS_FIFONEMPTY_SHIFT)
    #define MotorControl_STATUS_TC              (uint8)((uint8)0x01u << MotorControl_STATUS_TC_SHIFT)
    #define MotorControl_STATUS_CMP2            (uint8)((uint8)0x01u << MotorControl_STATUS_CMP2_SHIFT)
    #define MotorControl_STATUS_CMP1            (uint8)((uint8)0x01u << MotorControl_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define MotorControl_STATUS_KILL_INT_EN_MASK            (MotorControl_STATUS_KILL)
    #define MotorControl_STATUS_FIFOFULL_INT_EN_MASK        (MotorControl_STATUS_FIFOFULL)
    #define MotorControl_STATUS_FIFONEMPTY_INT_EN_MASK      (MotorControl_STATUS_FIFONEMPTY)
    #define MotorControl_STATUS_TC_INT_EN_MASK              (MotorControl_STATUS_TC)
    #define MotorControl_STATUS_CMP2_INT_EN_MASK            (MotorControl_STATUS_CMP2)
    #define MotorControl_STATUS_CMP1_INT_EN_MASK            (MotorControl_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define MotorControl_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define MotorControl_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define MotorControl_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define MotorControl_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define MotorControl_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* MotorControl_UsingFixedFunction */

#endif  /* CY_PWM_MotorControl_H */


/* [] END OF FILE */
