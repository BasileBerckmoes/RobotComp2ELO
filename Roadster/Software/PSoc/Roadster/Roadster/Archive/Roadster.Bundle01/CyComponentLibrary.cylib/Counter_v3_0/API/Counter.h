/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_`$INSTANCE_NAME`_H)
#define CY_COUNTER_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 `$INSTANCE_NAME`_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed `$INSTANCE_NAME`_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef `$INSTANCE_NAME`_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error `$CY_COMPONENT_NAME` detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* `$INSTANCE_NAME`_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define `$INSTANCE_NAME`_Resolution            `$Resolution`u
#define `$INSTANCE_NAME`_UsingFixedFunction    `$FixedFunctionUsed`u
#define `$INSTANCE_NAME`_ControlRegRemoved     `$ControlRegRemoved`u
#define `$INSTANCE_NAME`_COMPARE_MODE_SOFTWARE `$CompareModeSoftware`u
#define `$INSTANCE_NAME`_CAPTURE_MODE_SOFTWARE `$CaptureModeSoftware`u
#define `$INSTANCE_NAME`_RunModeUsed           `$RunMode`u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    `$RegSizeReplacementString` CounterUdb;         /* Current Counter Value */

    #if (!`$INSTANCE_NAME`_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!`$INSTANCE_NAME`_ControlRegRemoved) */

}`$INSTANCE_NAME`_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void    `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void    `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptsMask) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`;
uint8   `$INSTANCE_NAME`_ReadStatusRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatusRegister")`;
#define `$INSTANCE_NAME`_GetInterruptSource() `$INSTANCE_NAME`_ReadStatusRegister()
#if(!`$INSTANCE_NAME`_ControlRegRemoved)
    uint8   `$INSTANCE_NAME`_ReadControlRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadControlRegister")`;
    void    `$INSTANCE_NAME`_WriteControlRegister(uint8 control) \
        `=ReentrantKeil($INSTANCE_NAME . "_WriteControlRegister")`;
#endif /* (!`$INSTANCE_NAME`_ControlRegRemoved) */
#if (!(`$INSTANCE_NAME`_UsingFixedFunction && (CY_PSOC5A)))
    void    `$INSTANCE_NAME`_WriteCounter(`$RegSizeReplacementString` counter) \
            `=ReentrantKeil($INSTANCE_NAME . "_WriteCounter")`; 
#endif /* (!(`$INSTANCE_NAME`_UsingFixedFunction && (CY_PSOC5A))) */
`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadCounter(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCounter")`;
`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadCapture(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCapture")`;
void    `$INSTANCE_NAME`_WritePeriod(`$RegSizeReplacementString` period) \
    `=ReentrantKeil($INSTANCE_NAME . "_WritePeriod")`;
`$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadPeriod( void ) `=ReentrantKeil($INSTANCE_NAME . "_ReadPeriod")`;
#if (!`$INSTANCE_NAME`_UsingFixedFunction)
    void    `$INSTANCE_NAME`_WriteCompare(`$RegSizeReplacementString` compare) \
        `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare")`;
    `$RegSizeReplacementString`  `$INSTANCE_NAME`_ReadCompare( void ) \
        `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare")`;
#endif /* (!`$INSTANCE_NAME`_UsingFixedFunction) */

#if (`$INSTANCE_NAME`_COMPARE_MODE_SOFTWARE)
    void    `$INSTANCE_NAME`_SetCompareMode(uint8 compareMode) `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode")`;
#endif /* (`$INSTANCE_NAME`_COMPARE_MODE_SOFTWARE) */
#if (`$INSTANCE_NAME`_CAPTURE_MODE_SOFTWARE)
    void    `$INSTANCE_NAME`_SetCaptureMode(uint8 captureMode) `=ReentrantKeil($INSTANCE_NAME . "_SetCaptureMode")`;
#endif /* (`$INSTANCE_NAME`_CAPTURE_MODE_SOFTWARE) */
void `$INSTANCE_NAME`_ClearFIFO(void)     `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`;
void `$INSTANCE_NAME`_Init(void)          `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)        `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_SaveConfig(void)    `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Sleep(void)         `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)        `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
`#cy_declare_enum B_Counter__CompareModes`
/* Enumerated Type Counter_CompareModes */
#define `$INSTANCE_NAME`_CMP_MODE_LT 1u
#define `$INSTANCE_NAME`_CMP_MODE_LTE 2u
#define `$INSTANCE_NAME`_CMP_MODE_EQ 0u
#define `$INSTANCE_NAME`_CMP_MODE_GT 3u
#define `$INSTANCE_NAME`_CMP_MODE_GTE 4u
#define `$INSTANCE_NAME`_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
`#cy_declare_enum B_Counter__CaptureModes`
/* Enumerated Type Counter_CompareModes */
#define `$INSTANCE_NAME`_CAP_MODE_NONE 0u
#define `$INSTANCE_NAME`_CAP_MODE_RISE 1u
#define `$INSTANCE_NAME`_CAP_MODE_FALL 2u
#define `$INSTANCE_NAME`_CAP_MODE_BOTH 3u
#define `$INSTANCE_NAME`_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define `$INSTANCE_NAME`_CAPTURE_MODE_CONF       `$CaptureMode`u
#define `$INSTANCE_NAME`_INIT_PERIOD_VALUE       `$Period`u
#define `$INSTANCE_NAME`_INIT_COUNTER_VALUE      `$InitCounterValue`u
#if (`$INSTANCE_NAME`_UsingFixedFunction)
#define `$INSTANCE_NAME`_INIT_INTERRUPTS_MASK    ((uint8)((uint8)`$InterruptOnTC`u << `$INSTANCE_NAME`_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define `$INSTANCE_NAME`_INIT_COMPARE_VALUE      `$CompareValue`u
#define `$INSTANCE_NAME`_INIT_INTERRUPTS_MASK ((uint8)((uint8)`$InterruptOnTC`u << `$INSTANCE_NAME`_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)`$InterruptOnCapture`u << `$INSTANCE_NAME`_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)`$InterruptOnCompare`u << `$INSTANCE_NAME`_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)`$InterruptOnOverUnderFlow`u << `$INSTANCE_NAME`_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)`$InterruptOnOverUnderFlow`u << `$INSTANCE_NAME`_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define `$INSTANCE_NAME`_DEFAULT_COMPARE_MODE    `$CompareMode`u

#if( 0 != `$INSTANCE_NAME`_CAPTURE_MODE_CONF)
    #define `$INSTANCE_NAME`_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)`$CaptureMode`u << `$INSTANCE_NAME`_CTRL_CAPMODE0_SHIFT))
#else    
    #define `$INSTANCE_NAME`_DEFAULT_CAPTURE_MODE    (`$CaptureMode`u )
#endif /* ( 0 != `$INSTANCE_NAME`_CAPTURE_MODE_CONF) */

#endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (`$INSTANCE_NAME`_UsingFixedFunction)
    #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg16 *) `$INSTANCE_NAME`_CounterHW__CAP0 )
    #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg16 *) `$INSTANCE_NAME`_CounterHW__CAP0 )
    #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg16 *) `$INSTANCE_NAME`_CounterHW__PER0 )
    #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg16 *) `$INSTANCE_NAME`_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg16 *) `$INSTANCE_NAME`_CounterHW__CNT_CMP0 )
    #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg16 *) `$INSTANCE_NAME`_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg16 *) `$INSTANCE_NAME`_CounterHW__CNT_CMP0 )
    #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg16 *) `$INSTANCE_NAME`_CounterHW__CNT_CMP0 )
    #define `$INSTANCE_NAME`_RT1                 (*(reg8 *) `$INSTANCE_NAME`_CounterHW__RT1)
    #define `$INSTANCE_NAME`_RT1_PTR             ( (reg8 *) `$INSTANCE_NAME`_CounterHW__RT1)
#else
    
    #if (`$INSTANCE_NAME`_Resolution <= 8u) /* 8-bit Counter */
    
        #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
        #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
        #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
        #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
        #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
        #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
        #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg8 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )  
        #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg8 *)\
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )
    
    #elif(`$INSTANCE_NAME`_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
            #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )  
            #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg16 *)\
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_F0_REG )
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_F0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_D0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_D0_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_D1_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_D1_REG )
            #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg16 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_A0_REG )  
            #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg16 *)\
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(`$INSTANCE_NAME`_Resolution <= 24u) /* 24-bit Counter */
        
        #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
        #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
        #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
        #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
        #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
        #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
        #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg32 *) \
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )  
        #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg32 *)\
            `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__F0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D0_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__D1_REG )
            #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )  
            #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg32 *)\
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB     (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_F0_REG )
            #define `$INSTANCE_NAME`_STATICCOUNT_LSB_PTR ( (reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_F0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB          (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_D0_REG )
            #define `$INSTANCE_NAME`_PERIOD_LSB_PTR      ( (reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_D0_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB         (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_D1_REG )
            #define `$INSTANCE_NAME`_COMPARE_LSB_PTR     ( (reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_D1_REG )
            #define `$INSTANCE_NAME`_COUNTER_LSB         (*(reg32 *) \
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_A0_REG )  
            #define `$INSTANCE_NAME`_COUNTER_LSB_PTR     ( (reg32 *)\
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define `$INSTANCE_NAME`_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__A0_REG )
				
    #define `$INSTANCE_NAME`_AUX_CONTROLDP0 \
        (*(reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__DP_AUX_CTL_REG)
    
    #define `$INSTANCE_NAME`_AUX_CONTROLDP0_PTR \
        ( (reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (`$INSTANCE_NAME`_Resolution == 16 || `$INSTANCE_NAME`_Resolution == 24 || `$INSTANCE_NAME`_Resolution == 32)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP1 \
           (*(reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u1__DP_AUX_CTL_REG)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP1_PTR \
           ( (reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (`$INSTANCE_NAME`_Resolution == 16 || `$INSTANCE_NAME`_Resolution == 24 || `$INSTANCE_NAME`_Resolution == 32) */
    
    #if (`$INSTANCE_NAME`_Resolution == 24 || `$INSTANCE_NAME`_Resolution == 32)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP2 \
           (*(reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u2__DP_AUX_CTL_REG)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP2_PTR \
           ( (reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (`$INSTANCE_NAME`_Resolution == 24 || `$INSTANCE_NAME`_Resolution == 32) */
    
    #if (`$INSTANCE_NAME`_Resolution == 32)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP3 \
           (*(reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u3__DP_AUX_CTL_REG)
       #define `$INSTANCE_NAME`_AUX_CONTROLDP3_PTR \
           ( (reg8 *) `$INSTANCE_NAME`_CounterUDB_`$VerilogSectionReplacementString`_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (`$INSTANCE_NAME`_Resolution == 32) */

#endif  /* (`$INSTANCE_NAME`_UsingFixedFunction) */

#if (`$INSTANCE_NAME`_UsingFixedFunction)
    #define `$INSTANCE_NAME`_STATUS         (*(reg8 *) `$INSTANCE_NAME`_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define `$INSTANCE_NAME`_STATUS_MASK             (*(reg8 *) `$INSTANCE_NAME`_CounterHW__SR0 )
    #define `$INSTANCE_NAME`_STATUS_MASK_PTR         ( (reg8 *) `$INSTANCE_NAME`_CounterHW__SR0 )
    #define `$INSTANCE_NAME`_CONTROL                 (*(reg8 *) `$INSTANCE_NAME`_CounterHW__CFG0)
    #define `$INSTANCE_NAME`_CONTROL_PTR             ( (reg8 *) `$INSTANCE_NAME`_CounterHW__CFG0)
    #define `$INSTANCE_NAME`_CONTROL2                (*(reg8 *) `$INSTANCE_NAME`_CounterHW__CFG1)
    #define `$INSTANCE_NAME`_CONTROL2_PTR            ( (reg8 *) `$INSTANCE_NAME`_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define `$INSTANCE_NAME`_CONTROL3       (*(reg8 *) `$INSTANCE_NAME`_CounterHW__CFG2)
        #define `$INSTANCE_NAME`_CONTROL3_PTR   ( (reg8 *) `$INSTANCE_NAME`_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define `$INSTANCE_NAME`_GLOBAL_ENABLE           (*(reg8 *) `$INSTANCE_NAME`_CounterHW__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_ENABLE_PTR       ( (reg8 *) `$INSTANCE_NAME`_CounterHW__PM_ACT_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE      (*(reg8 *) `$INSTANCE_NAME`_CounterHW__PM_STBY_CFG)
    #define `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) `$INSTANCE_NAME`_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define `$INSTANCE_NAME`_BLOCK_EN_MASK          `$INSTANCE_NAME`_CounterHW__PM_ACT_MSK
    #define `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK     `$INSTANCE_NAME`_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      0x00u
    #define `$INSTANCE_NAME`_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_ENABLE            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT))         
    #define `$INSTANCE_NAME`_ONESHOT                ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define `$INSTANCE_NAME`_CTRL_MODE_SHIFT        0x01u    
        #define `$INSTANCE_NAME`_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define `$INSTANCE_NAME`_CTRL_MODE_SHIFT        0x00u    
        #define `$INSTANCE_NAME`_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << `$INSTANCE_NAME`_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define `$INSTANCE_NAME`_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_ZERO_INT_EN_MASK_SHIFT      (`$INSTANCE_NAME`_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define `$INSTANCE_NAME`_STATUS_ZERO            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define `$INSTANCE_NAME`_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)`$INSTANCE_NAME`_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define `$INSTANCE_NAME`_RT1_SHIFT            0x04u
    #define `$INSTANCE_NAME`_RT1_MASK             ((uint8)((uint8)0x03u << `$INSTANCE_NAME`_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define `$INSTANCE_NAME`_SYNC                 ((uint8)((uint8)0x03u << `$INSTANCE_NAME`_RT1_SHIFT))
    #define `$INSTANCE_NAME`_SYNCDSI_SHIFT        0x00u
    #define `$INSTANCE_NAME`_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << `$INSTANCE_NAME`_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define `$INSTANCE_NAME`_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << `$INSTANCE_NAME`_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !`$INSTANCE_NAME`_UsingFixedFunction */
    #define `$INSTANCE_NAME`_STATUS               (* (reg8 *) `$INSTANCE_NAME`_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define `$INSTANCE_NAME`_STATUS_PTR           (  (reg8 *) `$INSTANCE_NAME`_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define `$INSTANCE_NAME`_STATUS_MASK          (* (reg8 *) `$INSTANCE_NAME`_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define `$INSTANCE_NAME`_STATUS_MASK_PTR      (  (reg8 *) `$INSTANCE_NAME`_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define `$INSTANCE_NAME`_STATUS_AUX_CTRL      (*(reg8 *) `$INSTANCE_NAME`_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_STATUS_AUX_CTRL_PTR  ( (reg8 *) `$INSTANCE_NAME`_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_CONTROL              (* (reg8 *) `$INSTANCE_NAME`_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define `$INSTANCE_NAME`_CONTROL_PTR          (  (reg8 *) `$INSTANCE_NAME`_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define `$INSTANCE_NAME`_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define `$INSTANCE_NAME`_CTRL_CMPMODE_MASK      0x07u 
    #define `$INSTANCE_NAME`_CTRL_CAPMODE_MASK      0x03u  
    #define `$INSTANCE_NAME`_CTRL_RESET             ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_RESET_SHIFT))  
    #define `$INSTANCE_NAME`_CTRL_ENABLE            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define `$INSTANCE_NAME`_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define `$INSTANCE_NAME`_STATUS_CMP_INT_EN_MASK_SHIFT       `$INSTANCE_NAME`_STATUS_CMP_SHIFT       
    #define `$INSTANCE_NAME`_STATUS_ZERO_INT_EN_MASK_SHIFT      `$INSTANCE_NAME`_STATUS_ZERO_SHIFT      
    #define `$INSTANCE_NAME`_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  `$INSTANCE_NAME`_STATUS_OVERFLOW_SHIFT  
    #define `$INSTANCE_NAME`_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT `$INSTANCE_NAME`_STATUS_UNDERFLOW_SHIFT 
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_INT_EN_MASK_SHIFT   `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT   
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT  
    #define `$INSTANCE_NAME`_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  `$INSTANCE_NAME`_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define `$INSTANCE_NAME`_STATUS_CMP             ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_CMP_SHIFT))  
    #define `$INSTANCE_NAME`_STATUS_ZERO            ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_ZERO_SHIFT)) 
    #define `$INSTANCE_NAME`_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_OVERFLOW_SHIFT)) 
    #define `$INSTANCE_NAME`_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_UNDERFLOW_SHIFT)) 
    #define `$INSTANCE_NAME`_STATUS_CAPTURE         ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_CAPTURE_SHIFT)) 
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_FIFOFULL_SHIFT))
    #define `$INSTANCE_NAME`_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << `$INSTANCE_NAME`_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define `$INSTANCE_NAME`_STATUS_CMP_INT_EN_MASK            `$INSTANCE_NAME`_STATUS_CMP                    
    #define `$INSTANCE_NAME`_STATUS_ZERO_INT_EN_MASK           `$INSTANCE_NAME`_STATUS_ZERO            
    #define `$INSTANCE_NAME`_STATUS_OVERFLOW_INT_EN_MASK       `$INSTANCE_NAME`_STATUS_OVERFLOW        
    #define `$INSTANCE_NAME`_STATUS_UNDERFLOW_INT_EN_MASK      `$INSTANCE_NAME`_STATUS_UNDERFLOW       
    #define `$INSTANCE_NAME`_STATUS_CAPTURE_INT_EN_MASK        `$INSTANCE_NAME`_STATUS_CAPTURE         
    #define `$INSTANCE_NAME`_STATUS_FIFOFULL_INT_EN_MASK       `$INSTANCE_NAME`_STATUS_FIFOFULL        
    #define `$INSTANCE_NAME`_STATUS_FIFONEMP_INT_EN_MASK       `$INSTANCE_NAME`_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define `$INSTANCE_NAME`_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* `$INSTANCE_NAME`_UsingFixedFunction */

#endif  /* CY_COUNTER_`$INSTANCE_NAME`_H */


/* [] END OF FILE */

