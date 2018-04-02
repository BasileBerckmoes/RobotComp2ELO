/*******************************************************************************
* File Name: sendBleDataTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_sendBleDataTimer_H)
#define CY_TIMER_sendBleDataTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 sendBleDataTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define sendBleDataTimer_Resolution                 16u
#define sendBleDataTimer_UsingFixedFunction         1u
#define sendBleDataTimer_UsingHWCaptureCounter      0u
#define sendBleDataTimer_SoftwareCaptureMode        0u
#define sendBleDataTimer_SoftwareTriggerMode        0u
#define sendBleDataTimer_UsingHWEnable              0u
#define sendBleDataTimer_EnableTriggerMode          0u
#define sendBleDataTimer_InterruptOnCaptureCount    0u
#define sendBleDataTimer_RunModeUsed                0u
#define sendBleDataTimer_ControlRegRemoved          0u

#if defined(sendBleDataTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define sendBleDataTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (sendBleDataTimer_UsingFixedFunction)
    #define sendBleDataTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define sendBleDataTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End sendBleDataTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!sendBleDataTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (sendBleDataTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!sendBleDataTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}sendBleDataTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    sendBleDataTimer_Start(void) ;
void    sendBleDataTimer_Stop(void) ;

void    sendBleDataTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   sendBleDataTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define sendBleDataTimer_GetInterruptSource() sendBleDataTimer_ReadStatusRegister()

#if(!sendBleDataTimer_UDB_CONTROL_REG_REMOVED)
    uint8   sendBleDataTimer_ReadControlRegister(void) ;
    void    sendBleDataTimer_WriteControlRegister(uint8 control) ;
#endif /* (!sendBleDataTimer_UDB_CONTROL_REG_REMOVED) */

uint16  sendBleDataTimer_ReadPeriod(void) ;
void    sendBleDataTimer_WritePeriod(uint16 period) ;
uint16  sendBleDataTimer_ReadCounter(void) ;
void    sendBleDataTimer_WriteCounter(uint16 counter) ;
uint16  sendBleDataTimer_ReadCapture(void) ;
void    sendBleDataTimer_SoftwareCapture(void) ;

#if(!sendBleDataTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (sendBleDataTimer_SoftwareCaptureMode)
        void    sendBleDataTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!sendBleDataTimer_UsingFixedFunction) */

    #if (sendBleDataTimer_SoftwareTriggerMode)
        void    sendBleDataTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (sendBleDataTimer_SoftwareTriggerMode) */

    #if (sendBleDataTimer_EnableTriggerMode)
        void    sendBleDataTimer_EnableTrigger(void) ;
        void    sendBleDataTimer_DisableTrigger(void) ;
    #endif /* (sendBleDataTimer_EnableTriggerMode) */


    #if(sendBleDataTimer_InterruptOnCaptureCount)
        void    sendBleDataTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (sendBleDataTimer_InterruptOnCaptureCount) */

    #if (sendBleDataTimer_UsingHWCaptureCounter)
        void    sendBleDataTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   sendBleDataTimer_ReadCaptureCount(void) ;
    #endif /* (sendBleDataTimer_UsingHWCaptureCounter) */

    void sendBleDataTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void sendBleDataTimer_Init(void)          ;
void sendBleDataTimer_Enable(void)        ;
void sendBleDataTimer_SaveConfig(void)    ;
void sendBleDataTimer_RestoreConfig(void) ;
void sendBleDataTimer_Sleep(void)         ;
void sendBleDataTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define sendBleDataTimer__B_TIMER__CM_NONE 0
#define sendBleDataTimer__B_TIMER__CM_RISINGEDGE 1
#define sendBleDataTimer__B_TIMER__CM_FALLINGEDGE 2
#define sendBleDataTimer__B_TIMER__CM_EITHEREDGE 3
#define sendBleDataTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define sendBleDataTimer__B_TIMER__TM_NONE 0x00u
#define sendBleDataTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define sendBleDataTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define sendBleDataTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define sendBleDataTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define sendBleDataTimer_INIT_PERIOD             65535u
#define sendBleDataTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << sendBleDataTimer_CTRL_CAP_MODE_SHIFT))
#define sendBleDataTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << sendBleDataTimer_CTRL_TRIG_MODE_SHIFT))
#if (sendBleDataTimer_UsingFixedFunction)
    #define sendBleDataTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << sendBleDataTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << sendBleDataTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define sendBleDataTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << sendBleDataTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << sendBleDataTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << sendBleDataTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (sendBleDataTimer_UsingFixedFunction) */
#define sendBleDataTimer_INIT_CAPTURE_COUNT      (2u)
#define sendBleDataTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << sendBleDataTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (sendBleDataTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define sendBleDataTimer_STATUS         (*(reg8 *) sendBleDataTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define sendBleDataTimer_STATUS_MASK    (*(reg8 *) sendBleDataTimer_TimerHW__SR0 )
    #define sendBleDataTimer_CONTROL        (*(reg8 *) sendBleDataTimer_TimerHW__CFG0)
    #define sendBleDataTimer_CONTROL2       (*(reg8 *) sendBleDataTimer_TimerHW__CFG1)
    #define sendBleDataTimer_CONTROL2_PTR   ( (reg8 *) sendBleDataTimer_TimerHW__CFG1)
    #define sendBleDataTimer_RT1            (*(reg8 *) sendBleDataTimer_TimerHW__RT1)
    #define sendBleDataTimer_RT1_PTR        ( (reg8 *) sendBleDataTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define sendBleDataTimer_CONTROL3       (*(reg8 *) sendBleDataTimer_TimerHW__CFG2)
        #define sendBleDataTimer_CONTROL3_PTR   ( (reg8 *) sendBleDataTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define sendBleDataTimer_GLOBAL_ENABLE  (*(reg8 *) sendBleDataTimer_TimerHW__PM_ACT_CFG)
    #define sendBleDataTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) sendBleDataTimer_TimerHW__PM_STBY_CFG)

    #define sendBleDataTimer_CAPTURE_LSB         (* (reg16 *) sendBleDataTimer_TimerHW__CAP0 )
    #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg16 *) sendBleDataTimer_TimerHW__CAP0 )
    #define sendBleDataTimer_PERIOD_LSB          (* (reg16 *) sendBleDataTimer_TimerHW__PER0 )
    #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg16 *) sendBleDataTimer_TimerHW__PER0 )
    #define sendBleDataTimer_COUNTER_LSB         (* (reg16 *) sendBleDataTimer_TimerHW__CNT_CMP0 )
    #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg16 *) sendBleDataTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define sendBleDataTimer_BLOCK_EN_MASK                     sendBleDataTimer_TimerHW__PM_ACT_MSK
    #define sendBleDataTimer_BLOCK_STBY_EN_MASK                sendBleDataTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define sendBleDataTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define sendBleDataTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define sendBleDataTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define sendBleDataTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define sendBleDataTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define sendBleDataTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << sendBleDataTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define sendBleDataTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define sendBleDataTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << sendBleDataTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define sendBleDataTimer_CTRL_MODE_SHIFT                 0x01u
        #define sendBleDataTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << sendBleDataTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define sendBleDataTimer_CTRL_RCOD_SHIFT        0x02u
        #define sendBleDataTimer_CTRL_ENBL_SHIFT        0x00u
        #define sendBleDataTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define sendBleDataTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << sendBleDataTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define sendBleDataTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << sendBleDataTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define sendBleDataTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << sendBleDataTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define sendBleDataTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << sendBleDataTimer_CTRL_RCOD_SHIFT))
        #define sendBleDataTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << sendBleDataTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define sendBleDataTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define sendBleDataTimer_RT1_MASK                        ((uint8)((uint8)0x03u << sendBleDataTimer_RT1_SHIFT))
    #define sendBleDataTimer_SYNC                            ((uint8)((uint8)0x03u << sendBleDataTimer_RT1_SHIFT))
    #define sendBleDataTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define sendBleDataTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << sendBleDataTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define sendBleDataTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << sendBleDataTimer_SYNCDSI_SHIFT))

    #define sendBleDataTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << sendBleDataTimer_CTRL_MODE_SHIFT))
    #define sendBleDataTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << sendBleDataTimer_CTRL_MODE_SHIFT))
    #define sendBleDataTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << sendBleDataTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define sendBleDataTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define sendBleDataTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define sendBleDataTimer_STATUS_TC_INT_MASK_SHIFT        (sendBleDataTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define sendBleDataTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (sendBleDataTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define sendBleDataTimer_STATUS_TC                       ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_TC_SHIFT))
    #define sendBleDataTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define sendBleDataTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define sendBleDataTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define sendBleDataTimer_STATUS              (* (reg8 *) sendBleDataTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define sendBleDataTimer_STATUS_MASK         (* (reg8 *) sendBleDataTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define sendBleDataTimer_STATUS_AUX_CTRL     (* (reg8 *) sendBleDataTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define sendBleDataTimer_CONTROL             (* (reg8 *) sendBleDataTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(sendBleDataTimer_Resolution <= 8u) /* 8-bit Timer */
        #define sendBleDataTimer_CAPTURE_LSB         (* (reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sendBleDataTimer_PERIOD_LSB          (* (reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sendBleDataTimer_COUNTER_LSB         (* (reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(sendBleDataTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define sendBleDataTimer_CAPTURE_LSB         (* (reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sendBleDataTimer_PERIOD_LSB          (* (reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sendBleDataTimer_COUNTER_LSB         (* (reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define sendBleDataTimer_CAPTURE_LSB         (* (reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define sendBleDataTimer_PERIOD_LSB          (* (reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define sendBleDataTimer_COUNTER_LSB         (* (reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg16 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(sendBleDataTimer_Resolution <= 24u)/* 24-bit Timer */
        #define sendBleDataTimer_CAPTURE_LSB         (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define sendBleDataTimer_PERIOD_LSB          (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define sendBleDataTimer_COUNTER_LSB         (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define sendBleDataTimer_CAPTURE_LSB         (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define sendBleDataTimer_PERIOD_LSB          (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define sendBleDataTimer_COUNTER_LSB         (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define sendBleDataTimer_CAPTURE_LSB         (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define sendBleDataTimer_CAPTURE_LSB_PTR       ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define sendBleDataTimer_PERIOD_LSB          (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define sendBleDataTimer_PERIOD_LSB_PTR        ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define sendBleDataTimer_COUNTER_LSB         (* (reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define sendBleDataTimer_COUNTER_LSB_PTR       ((reg32 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define sendBleDataTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) sendBleDataTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (sendBleDataTimer_UsingHWCaptureCounter)
        #define sendBleDataTimer_CAP_COUNT              (*(reg8 *) sendBleDataTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define sendBleDataTimer_CAP_COUNT_PTR          ( (reg8 *) sendBleDataTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define sendBleDataTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) sendBleDataTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define sendBleDataTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) sendBleDataTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (sendBleDataTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define sendBleDataTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define sendBleDataTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define sendBleDataTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define sendBleDataTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define sendBleDataTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define sendBleDataTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << sendBleDataTimer_CTRL_INTCNT_SHIFT))
    #define sendBleDataTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << sendBleDataTimer_CTRL_TRIG_MODE_SHIFT))
    #define sendBleDataTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << sendBleDataTimer_CTRL_TRIG_EN_SHIFT))
    #define sendBleDataTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << sendBleDataTimer_CTRL_CAP_MODE_SHIFT))
    #define sendBleDataTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << sendBleDataTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define sendBleDataTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define sendBleDataTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define sendBleDataTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define sendBleDataTimer_STATUS_TC_INT_MASK_SHIFT       sendBleDataTimer_STATUS_TC_SHIFT
    #define sendBleDataTimer_STATUS_CAPTURE_INT_MASK_SHIFT  sendBleDataTimer_STATUS_CAPTURE_SHIFT
    #define sendBleDataTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define sendBleDataTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define sendBleDataTimer_STATUS_FIFOFULL_INT_MASK_SHIFT sendBleDataTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define sendBleDataTimer_STATUS_TC                      ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define sendBleDataTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define sendBleDataTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define sendBleDataTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define sendBleDataTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define sendBleDataTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define sendBleDataTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << sendBleDataTimer_STATUS_FIFOFULL_SHIFT))

    #define sendBleDataTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define sendBleDataTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define sendBleDataTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define sendBleDataTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define sendBleDataTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define sendBleDataTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_sendBleDataTimer_H */


/* [] END OF FILE */
