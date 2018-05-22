/*******************************************************************************
* \file     `$INSTANCE_NAME`.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
* Note:
*
********************************************************************************
* \copyright
* (c) 2015-2016, Cypress Semiconductor Corporation. All rights reserved. This 
* software, including source code, documentation and related materials 
* ("Software"), is owned by Cypress Semiconductor Corporation ("Cypress") and 
* is protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Therefore, you may use this Software only as provided in the license 
* agreement accompanying the software package from which you obtained this 
* Software ("EULA"). If no EULA applies, Cypress hereby grants you a personal, 
* non-exclusive, non-transferable license to copy, modify, and compile the 
* Software source code solely for use in connection with Cypress's integrated 
* circuit products. Any reproduction, modification, translation, compilation, 
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* 
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use 
* of the Software or any product or circuit described in the Software. Cypress 
* does not authorize its products for use in any products where a malfunction 
* or failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death ("High Risk Product"). By 
* including Cypress's product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/
#if !defined(CY_ADC_UAB_`$INSTANCE_NAME`_H)
#define CY_ADC_UAB_`$INSTANCE_NAME`_H
    
    #include "cytypes.h"
    #include "`$INSTANCE_NAME`_HALF_A.h"
    #include "`$INSTANCE_NAME`_HALF_B.h"
    #include "`$INSTANCE_NAME`_REFSOURCE.h"
    #include "`$INSTANCE_NAME`_BUR_ISR.h"
    `$CY_API_CALLBACK_HEADER_INCLUDE`
/*******************************************************************************
* API Constants
*******************************************************************************/
    
/** Parameter constants for IsEndConversion(). */
    typedef enum
    {
        `$INSTANCE_NAME`_RETURN_STATUS = 0,
        `$INSTANCE_NAME`_WAIT_FOR_RESULT = 1,
    } `$INSTANCE_NAME`_eoc_enum;

/** Parameter constants for Calibrate(). */
    typedef enum
    {
        `$INSTANCE_NAME`_USE_INTERRUPT = 0,
        `$INSTANCE_NAME`_WAIT_FOR_CALIBRATE = 1,
    } `$INSTANCE_NAME`_calibrate_mode_enum;
    
    #define `$INSTANCE_NAME`_IDLE               (0x00u)
    #define `$INSTANCE_NAME`_CALIBRATING_PHASE1 (0x10u)
    #define `$INSTANCE_NAME`_CALIBRATING_PHASE2 (0x20u)
    
    #define `$INSTANCE_NAME`_HARDWARE_FREE      (0uL)
    #define `$INSTANCE_NAME`_CONVERSION_DONE    (1uL)
    #define `$INSTANCE_NAME`_CONVERSION_BUSY    (0uL)
/*******************************************************************************
* Function Prototypes
*******************************************************************************/
/** \addtogroup group_init 
    \{ */
    void `$INSTANCE_NAME`_Start(void);
    uint32 `$INSTANCE_NAME`_StartConvert(void);
    void `$INSTANCE_NAME`_Stop (void);
    void `$INSTANCE_NAME`_Init(void);
    void `$INSTANCE_NAME`_Enable(void);
 /** \} init */
    
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetRaw
    ************************************************************************//**
    *
    * Get a raw result value from the `$INSTANCE_NAME`'s decimator output 
    * register.
    *
    * \retval int32 Uncalibrated contents of decimator's result register.
    *
    ***************************************************************************/
    /* This function is implemented as a macro since it simply returns */
    /* a register's contents.                                          */
    /* int32 `$INSTANCE_NAME`_GetRaw(void); */
    #define `$INSTANCE_NAME`_GetRaw() ((int32)`$INSTANCE_NAME`_DCM_RESULT_REG)
    
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetResult16
    ************************************************************************//**
    *
    * Returns the calibrated `$INSTANCE_NAME` result. This result is saturated 
    * at the lower and upper limits of the operating resolution.
    *
    * \retval int16 Saturated, calibrated `$INSTANCE_NAME` result.
    *
    ***************************************************************************/
    /* This function is implemented as a macro since it simply an alias to calling *
     * RawToResult16 with current raw register.                                    */
    /* int16 `$INSTANCE_NAME`_GetResult16(void); */
    #define `$INSTANCE_NAME`_GetResult16() `$INSTANCE_NAME`_RawToResult16(`$INSTANCE_NAME`_DCM_RESULT_REG)
    
/** \addtogroup group_general
    \{ */
    uint32 `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_eoc_enum retMode);
    uint32 `$INSTANCE_NAME`_Calibrate(`$INSTANCE_NAME`_calibrate_mode_enum calibrateMode);
    int16 `$INSTANCE_NAME`_RawToResult16(int32 raw);
    int16 `$INSTANCE_NAME`_CountsTo_mVolts(int32 counts);
    int32 `$INSTANCE_NAME`_CountsTo_uVolts(int32 counts);
    float32 `$INSTANCE_NAME`_CountsTo_Volts(int32 counts);
 /** \} general */
    
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_ClearInterrupt
    ************************************************************************//**
    *
    * Clear a pending interrupt.
    *
    ***************************************************************************/
    
    /* void `$INSTANCE_NAME`_ClearInterrupt(void); */
    #define `$INSTANCE_NAME`_ClearInterrupt() do{`$INSTANCE_NAME`_HALF_A_INTR_REG = `$INSTANCE_NAME`_DCM_INTR_MASK;}while(0)
    
/** \addtogroup group_interrupt
    \{ */
    void `$INSTANCE_NAME`_EnableIRQ(void);
    void `$INSTANCE_NAME`_DisableIRQ(void);
 /** \} interrupt */
    void `$INSTANCE_NAME`_ProcessCalibratePhase1(void);
    void `$INSTANCE_NAME`_ProcessCalibratePhase2(void);
    void `$INSTANCE_NAME`_ConversionInt(void);
    void `$INSTANCE_NAME`_CalibrateInt(void);

/** \addtogroup group_power
    \{ */
    void `$INSTANCE_NAME`_Sleep(void);
    void `$INSTANCE_NAME`_Wakeup(void);
 /** \} power */
    
/*******************************************************************************
* Parameter Defaults
*******************************************************************************/
    /* Default config values from user parameters, added to datasheet. */
    /** Full-scale center voltage, in millivolts. */
    #if (0 == `$INSTANCE_NAME`_REFSOURCE_SEL_REFERENCE_SOURCE)
        #define `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV ((`$INSTANCE_NAME`_REFSOURCE_BANDGAP_MVOLTS * (`$INSTANCE_NAME`_REFSOURCE_SEL_OUTPUT_VOLTAGE)) /16u )
    #else
        #define `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV ((`$INSTANCE_NAME`_REFSOURCE_VDDA_MVOLTS * (`$INSTANCE_NAME`_REFSOURCE_SEL_OUTPUT_VOLTAGE)) / 16u)
    #endif
    
    /** Full-scale center voltage, in microvolts. */
    #define `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_UV_SCALEDOWN   ((1000u * `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV) >> (`$INSTANCE_NAME`_PARAM_RESOLUTION - 1u))
    
    /** Full-scale center voltage, in volts. */
    #define `$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_V   (((float32)`$INSTANCE_NAME`_PARAM_VREF_VOLTAGE_MV) / `$INSTANCE_NAME`_UNITCONST_DIVISOR_MV2V)
    
    #define `$INSTANCE_NAME`_PARAM_INPUT_MODE          (`$Endedness`u)
        #define `$INSTANCE_NAME`_SINGLE_ENDED          (0x0u)
        #define `$INSTANCE_NAME`_DIFFERENTIAL         (0x1u)
    #define `$INSTANCE_NAME`_PARAM_RESOLUTION         (14u)
    #define `$INSTANCE_NAME`_PARAM_RANGE              (`$VRange`uL)
        
 
/*******************************************************************************
* Parameter-derived Default configurations
*******************************************************************************/
    #define `$INSTANCE_NAME`_DCM_GLOBALCTRL_DEFAULT (1uL << `$INSTANCE_NAME`_DCM_GLOBALCTRL_DECEN_SHIFT)
    
    #if (`$INSTANCE_NAME`_PARAM_RESOLUTION == 12u)
        #define `$INSTANCE_NAME`_DCM_CTRL_DEFAULT ((1uL << `$INSTANCE_NAME`_DCM_CTRL_MODE_SHIFT) \
        | ((1uL << `$INSTANCE_NAME`_DCM_CTRL_TYPE_SHIFT) \
        | ((4uL << `$INSTANCE_NAME`_DCM_CTRL_SHIFT_SHIFT) \
        | (255uL << `$INSTANCE_NAME`_DCM_CTRL_RATIO_SHIFT))))
        #define `$INSTANCE_NAME`_DCM_OVR_DEFAULT (16uL << `$INSTANCE_NAME`_DCM_OVR_CORR_LOC_SHIFT)
    #else /* #elif (`$INSTANCE_NAME`_PARAM_RESOLUTION == 14u) */
        #define `$INSTANCE_NAME`_DCM_CTRL_DEFAULT ((0uL << `$INSTANCE_NAME`_DCM_CTRL_MODE_SHIFT) \
        | ((1uL << `$INSTANCE_NAME`_DCM_CTRL_TYPE_SHIFT) \
        | ((4uL << `$INSTANCE_NAME`_DCM_CTRL_SHIFT_SHIFT) \
        | (`$OSR`uL << `$INSTANCE_NAME`_DCM_CTRL_RATIO_SHIFT))))
        #define `$INSTANCE_NAME`_DCM_OVR_DEFAULT (18uL << `$INSTANCE_NAME`_DCM_OVR_CORR_LOC_SHIFT)
    #endif /* (`$INSTANCE_NAME`_PARAM_RESOLUTION == 12u)) */
    
    #define `$INSTANCE_NAME`_DCM_TRIG_DEFAULT (0uL)
    
    #define `$INSTANCE_NAME`_HA_B_CAP_DEFAULT ((`$INSTANCE_NAME`_PARAM_RANGE == 0uL) ? CyUAB_B_CAP_06UNIT : \
                                              ((`$INSTANCE_NAME`_PARAM_RANGE == 1uL) ? CyUAB_B_CAP_12UNIT : \
                                              ((`$INSTANCE_NAME`_PARAM_RANGE == 2uL) ? CyUAB_B_CAP_24UNIT : \
                                                                                     CyUAB_B_CAP_48UNIT)))
    #define `$INSTANCE_NAME`_HA_C_CAP_DEFAULT ((`$INSTANCE_NAME`_PARAM_RANGE == 4uL) ? CyUAB_CAP_08UNIT : CyUAB_CAP_16UNIT)
    #define `$INSTANCE_NAME`_HA_B_CAP_CAL (CyUAB_B_CAP_12UNIT)
    #define `$INSTANCE_NAME`_HA_C_CAP_CAL (CyUAB_CAP_16UNIT)
    #define `$INSTANCE_NAME`_GAIN_NUMERATOR ((`$INSTANCE_NAME`_PARAM_RANGE == 0uL) ? 2uL : 1uL)
    #define `$INSTANCE_NAME`_GAIN_DENOMINATOR ((`$INSTANCE_NAME`_PARAM_RANGE == 0uL) ? 1uL : (1uL << (`$INSTANCE_NAME`_PARAM_RANGE - 1uL)))
    
    #define `$INSTANCE_NAME`_HA_B_IN0_CAL1 (0uL)
    #define `$INSTANCE_NAME`_HA_B_IN1_CAL1 ((2uL << CyUAB_SW_BG_MODBIT_SHIFT) | (1uL << CyUAB_SW_BV_MODBIT_SHIFT))
    #define `$INSTANCE_NAME`_HA_B_IN0_CAL2 (0uL)
    #define `$INSTANCE_NAME`_HA_B_IN1_CAL2 ((2uL << CyUAB_SW_BV_MODBIT_SHIFT) | (1uL << CyUAB_SW_BG_MODBIT_SHIFT))
    #define `$INSTANCE_NAME`_MAX_LOW  (`$INSTANCE_NAME`_LIMIT_LOWBOUND)  /* -2^Res-1 */
    #define `$INSTANCE_NAME`_MAX_HIGH (`$INSTANCE_NAME`_LIMIT_HIGHBOUND) /* 2^Res-1 - 1*/
    #if (`$INSTANCE_NAME`_SINGLE_ENDED == `$INSTANCE_NAME`_PARAM_INPUT_MODE)
        #define `$INSTANCE_NAME`_HA_B_IN0_CONV (1uL << (((uint32)`$INSTANCE_NAME`_HALF_A_halfuab__X0) * 4uL))
        #define `$INSTANCE_NAME`_HA_B_IN1_CONV (2uL << (CyUAB_SW_BG_MODBIT_SHIFT))
    #else /* #elif (`$INSTANCE_NAME`_DIFFERENTIAL == `$INSTANCE_NAME`_PARAM_INPUT_MODE)*/
        #define `$INSTANCE_NAME`_HA_B_IN0_CONV ((1uL << (((uint32)`$INSTANCE_NAME`_HALF_A_halfuab__X0) * 4uL)) | (2uL << (((uint32)`$INSTANCE_NAME`_HALF_A_halfuab__X1) * 4uL)))
        #define `$INSTANCE_NAME`_HA_B_IN1_CONV (0uL << (CyUAB_SW_BG_MODBIT_SHIFT))
    #endif /* (`$INSTANCE_NAME`_SINGLE_ENDED == `$INSTANCE_NAME`_PARAM_INPUT_MODE) */

/*******************************************************************************
* Global variables
*******************************************************************************/
    /** \addtogroup group_globals 
     Globals are noted in the description of the functions that use globals.
     \{ */
    /** Indicates whether the `$INSTANCE_NAME` has been initialized. Set by 
    `$INSTANCE_NAME`_Start(). */
    extern uint8 `$INSTANCE_NAME`_initVar;
    
    /** Indicates whether the `$INSTANCE_NAME` uses interrupts. Set by 
    `$INSTANCE_NAME`_EnableIRQ(), cleared by `$INSTANCE_NAME`_DisableIRQ(). */
    extern uint8 `$INSTANCE_NAME`_irqEnabled;
    /** \} globals */
    
    #define `$INSTANCE_NAME`_LIMIT_LOWBOUND             (0 - (1 << (((int32)`$INSTANCE_NAME`_PARAM_RESOLUTION) - 1)))
    #define `$INSTANCE_NAME`_LIMIT_HIGHBOUND            ((1 << (((int32)`$INSTANCE_NAME`_PARAM_RESOLUTION) - 1)) - 1)
    #define `$INSTANCE_NAME`_TIMEOUT_DURATION           (0x10000uL)
    #define `$INSTANCE_NAME`_UNITCONST_FACTOR_MV2UV     (1000uL)
    #define `$INSTANCE_NAME`_UNITCONST_DIVISOR_MV2V     ((float32) 1000.0)
    
/******************************************************************************
* Register locations and bitfield shifts
*******************************************************************************/
    #define `$INSTANCE_NAME`_DCM_INTR_MASK              (0x4uL << (`$INSTANCE_NAME`_DCMTR__HALF_UAB_NUMBER * 16u))
    
    #define `$INSTANCE_NAME`_DCM_GLOBALCTRL_ADDR        (`$INSTANCE_NAME`_DCMTR__DECM_CTRL)
    #define `$INSTANCE_NAME`_DCM_GLOBALCTRL_PTR         ((reg32*)`$INSTANCE_NAME`_DCM_GLOBALCTRL_ADDR)
    #define `$INSTANCE_NAME`_DCM_GLOBALCTRL_REG         (*`$INSTANCE_NAME`_DCM_GLOBALCTRL_PTR)
    #define `$INSTANCE_NAME`_DCM_GLOBALCTRL_DECEN_SHIFT (31uL)
    
    #define `$INSTANCE_NAME`_DCM_CTRL_ADDR              (`$INSTANCE_NAME`_DCMTR__DC_CTRL)
    #define `$INSTANCE_NAME`_DCM_CTRL_PTR               ((reg32*)`$INSTANCE_NAME`_DCM_CTRL_ADDR)
    #define `$INSTANCE_NAME`_DCM_CTRL_REG               (*`$INSTANCE_NAME`_DCM_CTRL_PTR)
    #define `$INSTANCE_NAME`_DCM_CTRL_START_SHIFT       CYFLD_UAB_DC0_START__OFFSET
    #define `$INSTANCE_NAME`_DCM_CTRL_MODE_SHIFT        CYFLD_UAB_DC0_MODE__OFFSET
    #define `$INSTANCE_NAME`_DCM_CTRL_SEL_SHIFT         CYFLD_UAB_DC0_SEL__OFFSET
    #define `$INSTANCE_NAME`_DCM_CTRL_SEL_MASK          (0x3uL << `$INSTANCE_NAME`_DCM_CTRL_SEL_SHIFT)
    #define `$INSTANCE_NAME`_DCM_CTRL_TYPE_SHIFT        CYFLD_UAB_DC0_TYPE__OFFSET
      /* CYVAL_UAB_DC0_TYPE_SINC1    */
      /* CYVAL_UAB_DC0_TYPE_SINC2    */
      /* CYVAL_UAB_DC0_TYPE_SINC3    */
      /* CYVAL_UAB_DC0_TYPE_reserved */
    #define `$INSTANCE_NAME`_DCM_CTRL_SHIFT_SHIFT       CYFLD_UAB_DC0_SHIFT__OFFSET
    #define `$INSTANCE_NAME`_DCM_CTRL_RATIO_SHIFT       CYFLD_UAB_DC0_RATIO__OFFSET
    
    #define `$INSTANCE_NAME`_DCM_TRIG_ADDR              (`$INSTANCE_NAME`_DCMTR__DC_TRIG)
    #define `$INSTANCE_NAME`_DCM_TRIG_PTR               ((reg32*)`$INSTANCE_NAME`_DCM_TRIG_ADDR)
    #define `$INSTANCE_NAME`_DCM_TRIG_REG               (*`$INSTANCE_NAME`_DCM_TRIG_PTR)
    #define `$INSTANCE_NAME`_DCM_TRIG_SEL_SHIFT         CYFLD_UAB_DC0_TRIG_SEL__OFFSET
    #define `$INSTANCE_NAME`_DCM_TRIG_SEL_MASK          (0x1fuL << `$INSTANCE_NAME`_DCM_TRIG_SEL_SHIFT)
    #define `$INSTANCE_NAME`_DCM_TRIG_EN_SHIFT          CYFLD_UAB_DC0_DSI_TRIG_EN__OFFSET
    
    #define `$INSTANCE_NAME`_DCM_OVR_ADDR               (`$INSTANCE_NAME`_DCMTR__DC_OVR)
    #define `$INSTANCE_NAME`_DCM_OVR_PTR                ((reg32*)`$INSTANCE_NAME`_DCM_OVR_ADDR)
    #define `$INSTANCE_NAME`_DCM_OVR_REG                (*`$INSTANCE_NAME`_DCM_OVR_PTR)
    #define `$INSTANCE_NAME`_DCM_OVR_CORR_LOC_SHIFT     CYFLD_UAB_DC0_OVR_CORR_LOC__OFFSET
    
    #define `$INSTANCE_NAME`_DCM_RESULT_ADDR            (`$INSTANCE_NAME`_DCMTR__DC_RES)
    #define `$INSTANCE_NAME`_DCM_RESULT_DMAPTR          ((void*)`$INSTANCE_NAME`_DCM_RESULT_ADDR)
    #define `$INSTANCE_NAME`_DCM_RESULT_PTR             ((reg32*)`$INSTANCE_NAME`_DCM_RESULT_ADDR)
    #define `$INSTANCE_NAME`_DCM_RESULT_REG             (*`$INSTANCE_NAME`_DCM_RESULT_PTR)
    #define `$INSTANCE_NAME`_DCM_RESULT_SHIFT           CYFLD_UAB_RES__OFFSET
    
#endif /* !defined(CY_ADC_UAB_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
