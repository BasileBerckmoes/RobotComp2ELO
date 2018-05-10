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
* (c) 2015-2016, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NON-INFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#if !defined(CY_POWERMONITOR_`$INSTANCE_NAME`_H)
#define CY_POWERMONITOR_`$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_USE_DMAC      (`$UseDmac`u)
#define `$INSTANCE_NAME`_CHECK_PGOOD   (`$UsePgood`u)
    
#include "cytypes.h"
#include "CyLib.h"
#include "`$INSTANCE_NAME`_ADC.h"
#include "`$INSTANCE_NAME`_ADC_IRQ.h"

#if (`$INSTANCE_NAME`_USE_DMAC == 1)
    #include "`$INSTANCE_NAME`_uv_isr.h"
    #include "`$INSTANCE_NAME`_ov_isr.h"
    #include "`$INSTANCE_NAME`_DMA_Check.h"
    #include "`$INSTANCE_NAME`_DMA_Sample.h"
    #include "`$INSTANCE_NAME`_DMA_LimitUV.h"
    #include "`$INSTANCE_NAME`_DMA_LimitOV.h"
    #include "`$INSTANCE_NAME`_DMA_Enable.h"
#endif

#if (`$INSTANCE_NAME`_CHECK_PGOOD == 1)
    #include "`$INSTANCE_NAME`_PGood_Control_Reg.h"
    
    #if !defined(`$INSTANCE_NAME`_PGood_Control_Reg_Sync_ctrl_reg__REMOVED)
        #define `$INSTANCE_NAME`_USE_PGOOD (1)
    #endif  /* (`$INSTANCE_NAME`_PGood_Control_Reg_Sync_ctrl_reg__REMOVED) */
#else
    #define `$INSTANCE_NAME`_USE_PGOOD (0)
#endif /*(`$INSTANCE_NAME`_USE_PGOOD == 1)*/

extern cyisraddress CyRamVectors[CYINT_IRQ_BASE + CY_NUM_INTERRUPTS];

/******************************************************************************
* Parameter Defaults
*******************************************************************************/
/* Default config values from user parameters */
/** \addtogroup group_globals
    \{ */
/** Number of converters to be monitored.  Range 1 to 8. */
#define `$INSTANCE_NAME`_NUM_CONVERTERS                  (`$NumConverters`u)
/** ADC maximum voltage in mV. Depends on the range chosen in the customizer. */
#define `$INSTANCE_NAME`_ADC_MAX_VOLTAGE                 (`$AdcRange_mV`)
/** ADC maximum number of counts. Depends on the resolution of the ADC. */
#define `$INSTANCE_NAME`_ADC_MAX_COUNTS                  ((uint32)(1uL << `$INSTANCE_NAME`_ADC_MAX_RESOLUTION) - 1uL)
/** \} globals */

#define `$INSTANCE_NAME`_UDB_PRESENT                     (`$UdbPresent`u)
#define `$INSTANCE_NAME`_PGOOD_CONFIG                    (`$PgoodConfig`u)

#define `$INSTANCE_NAME`_DEFAULT_OV_FAULT_MODE           (`$FaultSources_OV`u)
#define `$INSTANCE_NAME`_DEFAULT_UV_FAULT_MODE           (`$FaultSources_UV`u)
#define `$INSTANCE_NAME`_DEFAULT_OV_WARN_MODE            (`$WarnSources_OV`u)
#define `$INSTANCE_NAME`_DEFAULT_UV_WARN_MODE            (`$WarnSources_UV`u)

#define `$INSTANCE_NAME`_SAMPLE_AVERAGED                 (`$SamplesAveraged`u)
#define `$INSTANCE_NAME`_VREF_SELECT                     (`$VrefSelect`u)
#define `$INSTANCE_NAME`_VREF_VALUE                      (`$AdcVrefValue_mV`u)
#define `$INSTANCE_NAME`_ENABLE_DMA                      (`$EnableDma`u)
#define `$INSTANCE_NAME`_EXPOSE_SOC                      (`$ExposeSoc`u)

#define `$INSTANCE_NAME`_ADC_SCAN_NS                     (`$AdcScanTime`u)
#define `$INSTANCE_NAME`_RSP_TIME_NS                     (`$RspTime`u)
#define `$INSTANCE_NAME`_ADC_CLK_DIV                     (`$AdcClockDivider`u)
#define `$INSTANCE_NAME`_ADC_CLK_A                       (`$AdcAClock`u)
#define `$INSTANCE_NAME`_ADC_CLK_B                       (`$AdcBClock`u)
#define `$INSTANCE_NAME`_ADC_CLK_C                       (`$AdcCClock`u)
#define `$INSTANCE_NAME`_ADC_CLK_D                       (`$AdcDClock`u)

/******************************************************************************
* Parameter Defaults
*******************************************************************************/
#if (`$INSTANCE_NAME`_USE_DMAC == 1)
    /* Datapath Registers */
    #define `$INSTANCE_NAME`_HwComp_A0_REG         (*(reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_A0_REG )
    #define `$INSTANCE_NAME`_HwComp_A0_PTR         ( (reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_A0_REG )    
    #define `$INSTANCE_NAME`_HwComp_A1_REG         (*(reg8  *) `$INSTANCE_NAME`_HwComp_Comp_u0__A1_REG )
    #define `$INSTANCE_NAME`_HwComp_A1_PTR         ( (reg8  *) `$INSTANCE_NAME`_HwComp_Comp_u0__A1_REG )  
    #define `$INSTANCE_NAME`_HwComp_D0_REG         (*(reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_D0_REG )
    #define `$INSTANCE_NAME`_HwComp_D0_PTR         ( (reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_D0_REG )  
    #define `$INSTANCE_NAME`_HwComp_D1_REG         (*(reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_D1_REG )
    #define `$INSTANCE_NAME`_HwComp_D1_PTR         ( (reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_D1_REG )  
    #define `$INSTANCE_NAME`_HwComp_F0_REG         (*(reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_F0_REG )
    #define `$INSTANCE_NAME`_HwComp_F0_PTR         ( (reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_F0_REG ) 
    #define `$INSTANCE_NAME`_HwComp_F1_REG         (*(reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_F1_REG )
    #define `$INSTANCE_NAME`_HwComp_F1_PTR         ( (reg16 *) `$INSTANCE_NAME`_HwComp_Comp_u0__16BIT_F1_REG )  
#endif /* `$INSTANCE_NAME`_USE_DMAC */

/* Callback typedef */
typedef void (*`$INSTANCE_NAME`_callback)(uint32 converterNum, uint32 faultType);


/**
 \addtogroup group_globals 
 Globals are noted in the description of the functions that use 
 globals.
 \{
*/

/** Indicates whether the PowerMonitor has been initialized. */
extern uint32 `$INSTANCE_NAME`_initVar;

/** Array containing the UV fault threshold translated to ADC counts.*/
extern uint16 `$INSTANCE_NAME`_UVFaultThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];
/** Array containing the OV fault threshold translated to ADC counts.*/
extern uint16 `$INSTANCE_NAME`_OVFaultThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];
/** Array containing the UV warning threshold translated to ADC counts.*/
extern uint16 `$INSTANCE_NAME`_UVWarnThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];
/** Array containing the OV warning threshold translated to ADC counts.*/
extern uint16 `$INSTANCE_NAME`_OVWarnThreshold_Count[`$INSTANCE_NAME`_NUM_CONVERTERS];

/** Array containing the voltage scaling factors. It is calculated in the 
following format:

Y = Scale Factor x 2^16 x ADC Max Counts / ADC Max Voltage (mV)
*/
extern const uint32 `$INSTANCE_NAME`_VoltageScalingFactor[`$INSTANCE_NAME`_NUM_CONVERTERS];

/** Array containing the count scaling factors. It should be calculated in the 
following format:
Y = 2^16 / Scale Factor ADC Max Voltage (mV) / ADC Max Counts
*/
extern const uint32 `$INSTANCE_NAME`_CountScalingFactor[`$INSTANCE_NAME`_NUM_CONVERTERS];

/** Indicates what kind of faults are currently enabled for each of the converters. */
extern uint8 `$INSTANCE_NAME`_faultEnable[`$INSTANCE_NAME`_NUM_CONVERTERS]; 

/** Holds the under voltage warning status for each of the power converters. */
extern volatile uint32 `$INSTANCE_NAME`_UVWarnStatus;
/** Holds the over voltage warning status for each of the power converters. */
extern volatile uint32 `$INSTANCE_NAME`_OVWarnStatus;
/** Holds the under voltage fault status for each of the power converters. */
extern volatile uint32 `$INSTANCE_NAME`_UVFaultStatus;
/** Holds the over voltage fault status for each of the power converters. */
extern volatile uint32 `$INSTANCE_NAME`_OVFaultStatus;

/** Holds the PGood Status for each of the power converter. */ 
extern volatile uint32 `$INSTANCE_NAME`_PGoodStatus;

/** Internal register controlling which faults are active. */
extern volatile uint8 `$INSTANCE_NAME`_faultConfig[`$INSTANCE_NAME`_NUM_CONVERTERS];

 /** \} globals */

extern const uint32 `$INSTANCE_NAME`_UVFaultThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern const uint32 `$INSTANCE_NAME`_UVWarnThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern const uint32 `$INSTANCE_NAME`_OVWarnThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern const uint32 `$INSTANCE_NAME`_OVFaultThresholdInit_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern const uint32 `$INSTANCE_NAME`_AdcClockSelect[`$INSTANCE_NAME`_NUM_CONVERTERS];

extern uint32 `$INSTANCE_NAME`_UVFaultThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern uint32 `$INSTANCE_NAME`_OVFaultThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern uint32 `$INSTANCE_NAME`_UVWarnThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];
extern uint32 `$INSTANCE_NAME`_OVWarnThreshold_mV[`$INSTANCE_NAME`_NUM_CONVERTERS];

extern uint32 `$INSTANCE_NAME`_samplesAveraged;
extern uint32 `$INSTANCE_NAME`_converterCounts[`$INSTANCE_NAME`_NUM_CONVERTERS];

/* ISS callbacks. */
extern `$INSTANCE_NAME`_callback faultCallback;

#if (`$INSTANCE_NAME`_USE_DMAC == 1)
    extern volatile uint8 `$INSTANCE_NAME`_isDmaTriggered;
#endif /* `$INSTANCE_NAME`_USE_DMAC */
    
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/** \addtogroup group_init 
    \{ */
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop (void);
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
 /** \} init */
 
/** \addtogroup group_general
    \{ */
void `$INSTANCE_NAME`_EnableFault(uint32 converterMask);
void `$INSTANCE_NAME`_DisableFault(uint32 converterMask);
void `$INSTANCE_NAME`_SetFaultMode(uint32 converterNum, uint32 faultMode);
uint32 `$INSTANCE_NAME`_GetFaultMode(uint32 converterNum);
uint32 `$INSTANCE_NAME`_GetPGoodStatus(void);

uint32 `$INSTANCE_NAME`_GetFaultSource(void);
uint32 `$INSTANCE_NAME`_GetOVFaultStatus(void);
uint32 `$INSTANCE_NAME`_GetUVFaultStatus(void);
uint32 `$INSTANCE_NAME`_GetOVWarnStatus(void);
uint32 `$INSTANCE_NAME`_GetUVWarnStatus(void);

cystatus `$INSTANCE_NAME`_SetUVWarnThreshold(uint32 converterNum, uint32 uvWarnThreshold_mV);
uint32 `$INSTANCE_NAME`_GetUVWarnThreshold(uint32 converterNum);
cystatus `$INSTANCE_NAME`_SetOVWarnThreshold(uint32 converterNum, uint32 ovWarnThreshold_mV);
uint32 `$INSTANCE_NAME`_GetOVWarnThreshold(uint32 converterNum);

cystatus `$INSTANCE_NAME`_SetUVFaultThreshold(uint32 converterNum, uint32 uvFaultThreshold_mV);
uint32 `$INSTANCE_NAME`_GetUVFaultThreshold(uint32 converterNum);
cystatus `$INSTANCE_NAME`_SetOVFaultThreshold(uint32 converterNum, uint32 ovFaultThreshold_mV);
uint32 `$INSTANCE_NAME`_GetOVFaultThreshold(uint32 converterNum);

uint32 `$INSTANCE_NAME`_GetConverterVoltage(uint32 converterNum);
cystatus `$INSTANCE_NAME`_SetSamplesAveraged(uint32 numSample);
uint32 `$INSTANCE_NAME`_GetSamplesAveraged(void);

void `$INSTANCE_NAME`_SetFaultCallbackFunction(`$INSTANCE_NAME`_callback func);
/** \} general */

#if (`$INSTANCE_NAME`_USE_DMAC == 1)
    /** \addtogroup group_interrupts
        \{*/
    CY_ISR_PROTO(`$INSTANCE_NAME`_Uv_ISR_Handler);
    CY_ISR_PROTO(`$INSTANCE_NAME`_Ov_ISR_Handler);
    CY_ISR_PROTO(`$INSTANCE_NAME`_ADC_DMA_ISR);
        /** \} interrupts */
#endif /* `$INSTANCE_NAME`_USE_DMAC */

/******************************************************************************
* API Constants
*******************************************************************************/
/* OV and UV Masks */
#define `$INSTANCE_NAME`_OV_MASK                       (1u)
#define `$INSTANCE_NAME`_UV_MASK                       (2u)

/* Default warn and fault modes */
#define `$INSTANCE_NAME`_WARN_MODE_MASK                (3u)
#define `$INSTANCE_NAME`_FAULT_MODE_MASK               (3u)

#define `$INSTANCE_NAME`_DEFAULT_WARN_MODE             (`$INSTANCE_NAME`_DEFAULT_OV_WARN_MODE | \
                                                          (uint8)(`$INSTANCE_NAME`_DEFAULT_UV_WARN_MODE << 1u))
#define `$INSTANCE_NAME`_DEFAULT_FAULT_MODE            (`$INSTANCE_NAME`_DEFAULT_OV_FAULT_MODE | \
                                                          (uint8)(`$INSTANCE_NAME`_DEFAULT_UV_FAULT_MODE << 1u))

/* Constants for `$INSTANCE_NAME`_faultConfig values. */
#define `$INSTANCE_NAME`_ENABLE_CONVERTER_NUM_MSK      (0x1Fu)
#define `$INSTANCE_NAME`_ENABLE_OV_MASK                (0x20u)
#define `$INSTANCE_NAME`_ENABLE_OV_SHIFT               (5u)
#define `$INSTANCE_NAME`_ENABLE_UV_MASK                (0x40u)
#define `$INSTANCE_NAME`_ENABLE_UV_SHIFT               (6u)
#define `$INSTANCE_NAME`_ENABLE_FAULT_MASK             (0x80u)

#define `$INSTANCE_NAME`_MAX_SAMPLES_BIT               (8u)
#define `$INSTANCE_NAME`_MAX_SAMPLES                   (0x100u)

/* Constants for Scaling factor*/
#define `$INSTANCE_NAME`_SCALE_ROUNDING                (0x8000u)
#define `$INSTANCE_NAME`_SCALE_DIVIDE                  (16u)

/* Interrupt Number of the ADC_IRQ interrupt. */
#define `$INSTANCE_NAME`_IRQ__INTC_NUMBER              (`$INSTANCE_NAME`_ADC_IRQ__INTC_NUMBER)

/* Interrupt macros. */
#define CY_INT_NUMBER_MASK                             (0u)
#define `$INSTANCE_NAME`_IntDisable(irqNum) \
    do { \
        *(uint32*)CY_INT_CLEAR_PTR = \
        (uint32)(1ul << (CY_INT_NUMBER_MASK & (irqNum))); \
    } while(0)
#define `$INSTANCE_NAME`_IntEnable(irqNum) \
    do { \
        *(uint32*)CY_INT_ENABLE_PTR = \
        (uint32)(1ul << (CY_INT_NUMBER_MASK & (irqNum))); \
    } while(0)

/* Macro for function that just returns variable */
#define `$INSTANCE_NAME`_GetSamplesAveraged() (`$INSTANCE_NAME`_samplesAveraged)

/* Powermonitor enable state macro. */
#define `$INSTANCE_NAME`_ENABLED  ((`$INSTANCE_NAME`_ADC_SAR_CTRL_REG & `$INSTANCE_NAME`_ADC_ENABLE))


#endif /* CY_POWERMONITOR_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
