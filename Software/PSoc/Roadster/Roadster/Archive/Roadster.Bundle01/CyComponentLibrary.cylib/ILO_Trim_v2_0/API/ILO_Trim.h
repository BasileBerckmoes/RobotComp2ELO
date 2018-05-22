/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  ILO_Trim Component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_ILO_Trim_`$INSTANCE_NAME`_H) /* ILO_Trim Header File */
#define CY_ILO_Trim_`$INSTANCE_NAME`_H

#include <`$INSTANCE_NAME`_CorrectionISR.h>
#if(CY_PSOC4 && `$FixedFunctionUsed`)
    #include <`$INSTANCE_NAME`_TCPWM.h>
#endif /* End of PSoC 4 code*/

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#ifndef CY_PSOC5A
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* CY_PSOC5A */


/*******************************************************************************
* Conditional Compilation Parameters
********************************************************************************/
#define `$INSTANCE_NAME`_REF_FREQUENCY_KHZ          ((uint32)`$RefFrequency`u)
#define `$INSTANCE_NAME`_ILO_FREQUENCY              (`$ILOFrequency`u)
#define `$INSTANCE_NAME`_RATIO                      (`$ClkRatio`u)

/* Fixed Function or UDB Timer */
#define `$INSTANCE_NAME`_USING_FIXED_FUNCTION     (`$FixedFunctionUsed`u)
/* External reference Clock */
#define `$INSTANCE_NAME`_REF_FREQ               ((uint32)(1000u * (uint32)`$RefFrequency`))
/* The target ILO frequency */
#define `$INSTANCE_NAME`_ILO_EDGE_FREQ          ((uint32)(1000u * (uint32)`$ILOFrequency`))


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 timerEnableState;
    #if(!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
        uint8 timerCapture;
		/* Declaration for backing up enable state of the Timer */
        uint8 timerControlRegister;
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}`$INSTANCE_NAME`_backupStruct;


/***************************************
*        Function Prototypes
***************************************/
#if (!CY_PSOC4)
    CY_ISR_PROTO(`$INSTANCE_NAME`_CorrectionIteration);
#endif

void  `$INSTANCE_NAME`_Start(void)                      `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void)                       `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
uint8 `$INSTANCE_NAME`_CheckStatus(void)                `=ReentrantKeil($INSTANCE_NAME . "_CheckStatus")`;
int16 `$INSTANCE_NAME`_CheckError(void)                 `=ReentrantKeil($INSTANCE_NAME . "_CheckError")`;
void `$INSTANCE_NAME`_BeginTrimming(void)               `=ReentrantKeil($INSTANCE_NAME . "_BeginTrimming")`;
void `$INSTANCE_NAME`_StopTrimming(void)                `=ReentrantKeil($INSTANCE_NAME . "_StopTrimming")`;
void `$INSTANCE_NAME`_RestoreTrim(void)                 `=ReentrantKeil($INSTANCE_NAME . "_RestoreTrim")`;
uint8 `$INSTANCE_NAME`_GetTrim(void)                    `=ReentrantKeil($INSTANCE_NAME . "_GetTrim")`;
void `$INSTANCE_NAME`_SetTrim(uint8 trimVal)            `=ReentrantKeil($INSTANCE_NAME . "_SetTrim")`;
uint16 `$INSTANCE_NAME`_Compensate(uint16 clocks)       `=ReentrantKeil($INSTANCE_NAME . "_Compensate")`;
void `$INSTANCE_NAME`_Sleep(void)                       `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)                      `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_SaveConfig(void)                  `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void)               `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;


/*******************************************************************************
* API Constants
********************************************************************************/
#define `$INSTANCE_NAME`_CORRECTION_STEP_SIZE       (1u)

#if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION || CY_PSOC4)
    /* Ideal edges */
	#define `$INSTANCE_NAME`_EDGES_IDEAL ((uint32)(`$INSTANCE_NAME`_REF_FREQ / `$INSTANCE_NAME`_ILO_EDGE_FREQ))
#else
    /* Ideal edges */
	#define `$INSTANCE_NAME`_EDGES_IDEAL ((uint32)(`$INSTANCE_NAME`_REF_FREQ / (2u * `$INSTANCE_NAME`_ILO_EDGE_FREQ)))
#endif /* End of Device and Implementation specific defines */

#define `$INSTANCE_NAME`_EDGES_THOUSAND    ((uint32)(`$INSTANCE_NAME`_EDGES_IDEAL * 1000u))
#define `$INSTANCE_NAME`_EDGES_ROUND       ((uint32)(`$INSTANCE_NAME`_EDGES_IDEAL >> 1u))
#define `$INSTANCE_NAME`_EDGES_PPT         ((uint32)(`$INSTANCE_NAME`_EDGES_THOUSAND + `$INSTANCE_NAME`_EDGES_ROUND))

#define `$INSTANCE_NAME`_EDGES_HUNDRED     ((uint32)(`$INSTANCE_NAME`_EDGES_IDEAL * 100u))
#define `$INSTANCE_NAME`_EDGES_PPH         ((uint32)(`$INSTANCE_NAME`_EDGES_HUNDRED + `$INSTANCE_NAME`_EDGES_ROUND))

#if (!CY_PSOC4)
	/*  ILO_TR0[3:0] are reserved for 1kHz fine trim, 
		ILO_TR0[7:4] are reserved for 100kHz fine trim,
		ILO_TR1[1:0] are reserved for coarse trim  */
	#if (`$ILOFrequency` == 1u)
		#define `$INSTANCE_NAME`_ILO_TR0_MASK       (0x0Fu)
		#define `$INSTANCE_NAME`_FINE_TRIM_CLEAR    ((uint8)(~(uint8)`$INSTANCE_NAME`_ILO_TR0_MASK))
	#else
		#define `$INSTANCE_NAME`_ILO_TR0_MASK       (0xF0u)
		#define `$INSTANCE_NAME`_FINE_TRIM_CLEAR    ((uint8)(~(uint8)`$INSTANCE_NAME`_ILO_TR0_MASK))
	#endif /* End of ILO Frequency dependant code*/

	#define `$INSTANCE_NAME`_ILO_TR1_MASK           (0x03u)
	#define `$INSTANCE_NAME`_COARSE_TRIM_CLEAR      (0xF8u)
#endif /* End of PSoC 3 and PSOC 5LP code*/

#define `$INSTANCE_NAME`_FINE_TRIM_MASK         (0x0Fu)
#define `$INSTANCE_NAME`_COARSE_TRIM_ADD        (0x10u)
#define `$INSTANCE_NAME`_FINE_TRIM_ADD          (0x07u)

/* Default error values at startup and ISR control */
#define `$INSTANCE_NAME`_ERROR_DEFAULT          ((uint16)0x7FFFu)
#define `$INSTANCE_NAME`_INIT_DELAY             (0x00u)
#define `$INSTANCE_NAME`_FINAL_DELAY            (0x04u)
#define `$INSTANCE_NAME`_DELAY_COUNT            (0x01u)
#define `$INSTANCE_NAME`_ISR_INVALID            (0x01u)
#define `$INSTANCE_NAME`_ISR_VALID              (0x00u)
#define `$INSTANCE_NAME`_ISR_OFF                (0x00u)

/* Constants for error calculation and compensation */
#define `$INSTANCE_NAME`_PP_THOUSAND            ((uint32)0x000003E8u)
#define `$INSTANCE_NAME`_PP_HUNDRED             ((uint32)0x00000064u)
#define `$INSTANCE_NAME`_HALF                   ((uint32)0x00000002u)
#define `$INSTANCE_NAME`_TIME_SCALE             ((uint32)0x00002710u)
#define `$INSTANCE_NAME`_ILO_SCALE              ((uint32)0x00000064u)
#define `$INSTANCE_NAME`_COUNTER_SATURATE       ((uint16)0xFFFFu)

/* Misc Constants */
#define `$INSTANCE_NAME`_COUNT_ZERO             (0x00u)
#define `$INSTANCE_NAME`_ERROR_ZERO             (0x00)
#define `$INSTANCE_NAME`_TRIM_INVALID           (0x00u)
#define `$INSTANCE_NAME`_TRIM_COARSE_NEXT       (0x00u)

/* Accuracy status */
#define `$INSTANCE_NAME`_ACCURATE_SHIFT         (0x00u)
#define `$INSTANCE_NAME`_IS_ACCURATE            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_ACCURATE_SHIFT))

/* Trimming status */
#define `$INSTANCE_NAME`_TRIMMED                (0x00u)
#define `$INSTANCE_NAME`_TRIMMING_SHIFT         (0x01u)
#define `$INSTANCE_NAME`_TRIMMING               ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_TRIMMING_SHIFT))

/* ILO frequency definitions */
#define `$INSTANCE_NAME`_1kHz                   (1u)
#define `$INSTANCE_NAME`_32kHz                  (32u)
#define `$INSTANCE_NAME`_100kHz                 (100u)

/* Resolution of the timer */
#if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
	#define `$INSTANCE_NAME`_RESOLUTION         ((uint16)0x00FFu)
#else
	#define `$INSTANCE_NAME`_RESOLUTION         ((uint16)0xFFFFu)
#endif /* End of Fixed Function code */

/* Used for shifting the contents of the ILO Trim registers */
#define `$INSTANCE_NAME`_TRIM_SHIFT             (4u)

/* Timer needs an offset when converting to real number */
#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_TIMER_OFFSET       (2u)
#else
    #if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
        #define `$INSTANCE_NAME`_TIMER_OFFSET   (2u)
    #else
        #define `$INSTANCE_NAME`_TIMER_OFFSET   (3u)
    #endif
#endif /* End of PSoC 4 code*/


/*******************************************************************************
*   UDB Timer defines
********************************************************************************/
#if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)


    /***************************************
    *             UDB Registers
    ***************************************/
    /* Control register */
    #define `$INSTANCE_NAME`_CONTROL_REG            (*(reg8 *) `$INSTANCE_NAME`_bILO_Timer_CtlReg__CONTROL_REG)
    #define `$INSTANCE_NAME`_CONTROL_PTR            ( (reg8 *) `$INSTANCE_NAME`_bILO_Timer_CtlReg__CONTROL_REG)

    /* Counter register */
    #define `$INSTANCE_NAME`_COUNTER_PTR            ((reg8 *) `$INSTANCE_NAME`_bILO_Timer_CounterDP_u0__A0_REG)
    /* Capture register */
    #define `$INSTANCE_NAME`_CAPTURE_PTR            ((reg8 *) `$INSTANCE_NAME`_bILO_Timer_CounterDP_u0__A1_REG)


    /***************************************
    *    Register Constants
    ***************************************/
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      (0x00u)
     /* Control Register Bit Mask */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT))


/*******************************************************************************
*   Fixed Function Timer defines
********************************************************************************/
#else


    /***************************************
    *    Fixed Function constants
    ***************************************/
    #define `$INSTANCE_NAME`_INIT_PERIOD           ((uint16)0xFFFFu)


    /***************************************
    *    Fixed Function Registers
    ***************************************/
    #define `$INSTANCE_NAME`_STATUS_REG         (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define `$INSTANCE_NAME`_STATUS_MASK        (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__SR0 )
    #define `$INSTANCE_NAME`_CONTROL_REG        (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CFG0)
    #define `$INSTANCE_NAME`_CONTROL2_REG       (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CFG1)
    #define `$INSTANCE_NAME`_CONTROL2_PTR       ( (reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CFG1)

    #define `$INSTANCE_NAME`_CONTROL3_REG       (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CFG2)
    #define `$INSTANCE_NAME`_CONTROL3_PTR       ( (reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CFG2)

    #define `$INSTANCE_NAME`_GLOBAL_ENABLE      (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__PM_STBY_CFG)

    #define `$INSTANCE_NAME`_CAPTURE_LSB        (* (reg16 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CAP0 )
    #define `$INSTANCE_NAME`_CAPTURE_LSB_PTR    ((reg16 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CAP0 )
    #define `$INSTANCE_NAME`_PERIOD_LSB         (* (reg16 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__PER0 )
    #define `$INSTANCE_NAME`_PERIOD_LSB_PTR     ((reg16 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__PER0 )
    #define `$INSTANCE_NAME`_COUNTER_LSB        (* (reg16 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CNT_CMP0 )
    #define `$INSTANCE_NAME`_COUNTER_LSB_PTR    ((reg16 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__CNT_CMP0 )

    #define `$INSTANCE_NAME`_RT1_REG            (*(reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__RT1)
    #define `$INSTANCE_NAME`_RT1_PTR            ( (reg8 *) `$INSTANCE_NAME`_bILO_Trim_FF_Timer__RT1)


    /***************************************
    *    Register Constants
    ***************************************/
    #define `$INSTANCE_NAME`_BLOCK_EN_MASK          `$INSTANCE_NAME`_bILO_Trim_FF_Timer__PM_ACT_MSK
    #define `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK     `$INSTANCE_NAME`_bILO_Trim_FF_Timer__PM_STBY_MSK

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define `$INSTANCE_NAME`_RT1_SHIFT              (0x04u)
    /* Sync TC and CMP bit masks */
    #define `$INSTANCE_NAME`_RT1_MASK               ((uint8)((uint8)0x03u << `$INSTANCE_NAME`_RT1_SHIFT))
    #define `$INSTANCE_NAME`_SYNC                   ((uint8)((uint8)0x03u << `$INSTANCE_NAME`_RT1_SHIFT))
    #define `$INSTANCE_NAME`_SYNCDSI_SHIFT          (0x00u)
    /* Sync all DSI inputs with Mask  */
    #define `$INSTANCE_NAME`_SYNCDSI_MASK           ((uint8)((uint8)0x0Fu << `$INSTANCE_NAME`_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define `$INSTANCE_NAME`_SYNCDSI_EN             ((uint8)((uint8)0x0Fu << `$INSTANCE_NAME`_SYNCDSI_SHIFT))

    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      (0x00u)
     /* Control Register Bit Mask */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT))

    /* Control3 Register Bit Locations */
    #define `$INSTANCE_NAME`_CTRL_MODE_SHIFT        (0x00u)
    /* Control3 Register Bit Mask */
    #define `$INSTANCE_NAME`_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT))

#endif /* End of Fixed Function code */

#endif /* End of ILO_Trim Header File */


/* [] END OF FILE */
