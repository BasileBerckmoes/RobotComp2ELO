/***************************************************************************//**
* \file     `$INSTANCE_NAME`_FILTER.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* Provides filter defines to the API for the `$INSTANCE_NAME` Component.
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
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
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

#if !defined(CY_`$INSTANCE_NAME`_FILTER_H)
    #define CY_`$INSTANCE_NAME`_FILTER_H

    
#define `$INSTANCE_NAME`_FILTER_CFG0_FILTER_PRESENT          (`$Cfg0HasFilter`uL)
#define `$INSTANCE_NAME`_FILTER_CFG1_FILTER_PRESENT          (`$Cfg1HasFilter`uL)
#define `$INSTANCE_NAME`_FILTER_CFG2_FILTER_PRESENT          (`$Cfg2HasFilter`uL)
#define `$INSTANCE_NAME`_FILTER_CFG3_FILTER_PRESENT          (`$Cfg3HasFilter`uL)
	
#define `$INSTANCE_NAME`_FILTER_ANY_CONFIG_USES_FILTER       ( `$INSTANCE_NAME`_FILTER_CFG0_FILTER_PRESENT \
                                                             | `$INSTANCE_NAME`_FILTER_CFG1_FILTER_PRESENT \
                                                             | `$INSTANCE_NAME`_FILTER_CFG2_FILTER_PRESENT \
                                                             | `$INSTANCE_NAME`_FILTER_CFG3_FILTER_PRESENT \
                                                             )
	

#if(`$INSTANCE_NAME`_FILTER_ANY_CONFIG_USES_FILTER	!= 0u)	
    
#include "`$INSTANCE_NAME`_UABH_A_CyUAB_types.h"
#include "`$INSTANCE_NAME`_UABH_A_CyUAB_regs.h"
#include "`$INSTANCE_NAME`_UABH_A_CyUAB.h"
#include "`$INSTANCE_NAME`_UABH_A_param.h"
#include "`$INSTANCE_NAME`_UABH_B_param.h"
#include "`$INSTANCE_NAME`_UABH_A_regs.h"
#include "`$INSTANCE_NAME`_UABH_B_regs.h"
#include "`$INSTANCE_NAME`_UABH_A.h"
#include "`$INSTANCE_NAME`_UABH_B.h"

/*******************************************************************************
* Filter function prototypes
*******************************************************************************/
void `$INSTANCE_NAME`_TrimFilterVos(void);
void `$INSTANCE_NAME`_filterInit(uint32 configNum);

/*******************************************************************************
* Filter trim constants and macros
*******************************************************************************/
#define `$INSTANCE_NAME`_OPAMP_TRIM_POS_BASE     (0x00uL)
#define `$INSTANCE_NAME`_OPAMP_TRIM_POS_LIMIT    (0x08uL)
#define `$INSTANCE_NAME`_OPAMP_TRIM_NEG_BASE     (`$INSTANCE_NAME`_OPAMP_TRIM_POS_LIMIT)
#define `$INSTANCE_NAME`_OPAMP_TRIM_NEG_LIMIT    (0x10uL)
#define `$INSTANCE_NAME`_OPAMP_TRIM_MASK         (0x0fuL)
    
#define `$INSTANCE_NAME`_AGND_TRIM_POS_BASE      (0x00uL)
#define `$INSTANCE_NAME`_AGND_TRIM_POS_LIMIT     (0x10uL)
#define `$INSTANCE_NAME`_AGND_TRIM_NEG_BASE      (`$INSTANCE_NAME`_AGND_TRIM_POS_LIMIT)
#define `$INSTANCE_NAME`_AGND_TRIM_NEG_LIMIT     (0x20uL)
#define `$INSTANCE_NAME`_AGND_TRIM_MASK          (0x1fuL)

/*******************************************************************************
* Filter Parameters
*******************************************************************************/
#define `$INSTANCE_NAME`_FILTERTOPOLOGY_HIGH_Q  (0u)
#define `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q   (1u)
    
#define `$INSTANCE_NAME`_TRANSFERTYPE_LOW_PASS (0u)
#define `$INSTANCE_NAME`_TRANSFERTYPE_HIGH_PASS (1u)
#define `$INSTANCE_NAME`_TRANSFERTYPE_BAND_PASS (2u)
#define `$INSTANCE_NAME`_TRANSFERTYPE_BAND_STOP (3u)


#define `$INSTANCE_NAME`_UABH_A_INVAR_SRAM_CTRL        ((uint32)((uint32)1u << CyUAB_TRIGGER_EN_SHIFT) \
                                                    |  (uint32)((uint32)31u << CyUAB_TRIG_SEL_SHIFT)   \
                                                    |  (uint32)((uint32)1u << CyUAB_LAST_STEP_SHIFT))
#define `$INSTANCE_NAME`_UABH_B_INVAR_SRAM_CTRL        ((uint32)((uint32)1u << CyUAB_TRIGGER_EN_SHIFT) \
                                                    |  (uint32)((uint32)31u << CyUAB_TRIG_SEL_SHIFT)   \
                                                    |  (uint32)((uint32)1u << CyUAB_LAST_STEP_SHIFT))
#define `$INSTANCE_NAME`_UABH_A_INVAR_SW_MODBIT_SRC    ((31uL << CyUAB_MODBIT0_SRC_SEL_SHIFT) \
                                                    |  (31uL << CyUAB_MODBIT1_SRC_SEL_SHIFT))
#define `$INSTANCE_NAME`_UABH_B_INVAR_SW_MODBIT_SRC    ((31uL << CyUAB_MODBIT0_SRC_SEL_SHIFT) \
                                                    |  (31uL << CyUAB_MODBIT1_SRC_SEL_SHIFT))


/*******************************************************************************
* Low-Q definitions
*******************************************************************************/

#define `$INSTANCE_NAME`_UABH_A_LOWQSTAT_SW_CA_IN0 (CyUAB_SW_CLOSED << CyUAB_SW_AP_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_LOWQSTAT_SW_CA_TOP (CyUAB_SW_CLOSED << CyUAB_SW_SA_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_LOWQSTAT_SW_CC_IN0 (CyUAB_CLK_PHI1  << CyUAB_SW_CQ_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_LOWQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI2  << CyUAB_SW_CG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_LOWQSTAT_SW_CF_BOT (CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CA_IN0 (CyUAB_CLK_PHI2  << CyUAB_SW_AP_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CA_IN1 (CyUAB_CLK_PHI1  << CyUAB_SW_AG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI2  << CyUAB_SW_SA_SHIFT) \
                                                 | (CyUAB_CLK_PHI1  << CyUAB_SW_GA_MODBIT_SHIFT))
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CB_IN0 (CyUAB_CLK_PHI1  << CyUAB_SW_BQ_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CB_IN1 (CyUAB_CLK_PHI2  << CyUAB_SW_BG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CB_TOP ((CyUAB_CLK_PHI2 << CyUAB_SW_SB_SHIFT) \
                                                 | (CyUAB_CLK_PHI1  << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                 | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CC_IN0 ((uint32)CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_B_halfuab__X0 << 2u))
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI11 << CyUAB_SW_CG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_LOWQSTAT_SW_CF_BOT ((CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT) \
                                                 |  (CyUAB_CLK_PHI3  << CyUAB_SW_PO_SHIFT))

/*******************************************************************************
* High-Q definitions
*******************************************************************************/

#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CA_IN0 (CyUAB_SW_CLOSED << CyUAB_SW_AQ_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CA_TOP (CyUAB_SW_CLOSED << CyUAB_SW_SA_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CB_IN0 (CyUAB_CLK_PHI1 << CyUAB_SW_BQ_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CB_IN1 (CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CC_IN0 (CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI11 << CyUAB_SW_CG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CC_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT) \
                                                |    (CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT))
#define `$INSTANCE_NAME`_UABH_A_HIGHQSTAT_SW_CF_BOT (CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CA_IN0 (CyUAB_CLK_PHI1 << CyUAB_SW_AQ_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CA_IN1 (CyUAB_CLK_PHI2 << CyUAB_SW_AG_MODBIT_SHIFT)
#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_GA_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI2 << CyUAB_SW_SA_SHIFT))

#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CB_IN0 (CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_B_halfuab__X0 << 2u))
#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CB_IN1 (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CC_IN0 (CyUAB_CLK_PHI10 << (`$INSTANCE_NAME`_UABH_B_halfuab__X0 << 2u))
#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI9 << CyUAB_SW_CG_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_UABH_B_HIGHQSTAT_SW_CF_BOT ((CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT) \
                                                 |   (CyUAB_CLK_PHI3  << CyUAB_SW_PO_SHIFT))


/*******************************************************************************
* CFG0 definitions
*******************************************************************************/
#if (0u != `$INSTANCE_NAME`_FILTER_CFG0_FILTER_PRESENT)
    
    #define `$INSTANCE_NAME`_CFG0_FILTERTYPE_USED   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg0FilterTopology`
    #define `$INSTANCE_NAME`_CFG0_TRANSFERTYPE_0   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg0TransferType`
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL    (`$Cfg0GtC1Numerator`ul)
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_C1_DENOMINATOR_VAL  (`$Cfg0GtC1Denominator`ul)
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_C2_NUMERATOR_VAL    (`$Cfg0GtC2Numerator`ul)
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_C2_DENOMINATOR_VAL  (`$Cfg0GtC2Denominator`ul) 
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_C3_VAL              (`$Cfg0GtC3Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_C4_VAL              (`$Cfg0GtC4Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_Cp_VAL              (`$Cfg0GtCpNumerator`ul)      
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL   (`$Cfg0GtCppNumerator`ul)  
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL (`$Cfg0GtCppDenominator`ul)  
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_CA_VAL              (`$Cfg0GtCANumerator`ul)      
    #define `$INSTANCE_NAME`_CFG0_FILTER_GT_CB_VAL              (`$Cfg0GtCBNumerator`ul)     

    #define `$INSTANCE_NAME`_CFG0_FILTER_IDEAL_BIQUAD_NUM0      (`$Cfg0IdealBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_IDEAL_BIQUAD_NUM1      (`$Cfg0IdealBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_IDEAL_BIQUAD_NUM2      (`$Cfg0IdealBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_IDEAL_BIQUAD_DEN0      (`$Cfg0IdealBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_IDEAL_BIQUAD_DEN1      (`$Cfg0IdealBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_IDEAL_BIQUAD_DEN2      (`$Cfg0IdealBiquadDen2`)

    #define `$INSTANCE_NAME`_CFG0_FILTER_UAB_BIQUAD_NUM0        (`$Cfg0UabBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_UAB_BIQUAD_NUM1        (`$Cfg0UabBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_UAB_BIQUAD_NUM2        (`$Cfg0UabBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_UAB_BIQUAD_DEN0        (`$Cfg0UabBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_UAB_BIQUAD_DEN1        (`$Cfg0UabBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG0_FILTER_UAB_BIQUAD_DEN2        (`$Cfg0UabBiquadDen2`)
    
    #define `$INSTANCE_NAME`_CFG0_UABH_A_STARTUP_DELAY    ((uint32)((uint32)`$Cfg0FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    #define `$INSTANCE_NAME`_CFG0_UABH_B_STARTUP_DELAY    ((uint32)((uint32)`$Cfg0FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (`$INSTANCE_NAME`_CFG0_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < `$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == `$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == `$INSTANCE_NAME`_CFG0_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG0_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(`$INSTANCE_NAME`_CFG0_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE (`$INSTANCE_NAME`_CFG0_FILTER_GT_CA_VAL/4u)
        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(`$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((`$INSTANCE_NAME`_CFG0_FILTER_GT_CA_VAL - (2u * (`$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_ABCF_VAL ((`$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG0_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG0_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(`$INSTANCE_NAME`_CFG0_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG0_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((`$INSTANCE_NAME`_CFG0_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_CAP_CTRL ((((`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((`$INSTANCE_NAME`_CFG0_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define `$INSTANCE_NAME`_CFG0_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((`$INSTANCE_NAME`_CFG0_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define `$INSTANCE_NAME`_CFG0_UABH_B_LOWQDYN_CAP_CTRL     ((`$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define `$INSTANCE_NAME`_CFG0_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((`$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG0 High-Q definitions
    *******************************************************************************/
        
    #elif (`$INSTANCE_NAME`_CFG0_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define `$INSTANCE_NAME`_CFG0_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG0_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG0_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (`$INSTANCE_NAME`_CFG0_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (`$INSTANCE_NAME`_CFG0_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((`$INSTANCE_NAME`_CFG0_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG0_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (`$INSTANCE_NAME`_CFG0_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (`$INSTANCE_NAME`_CFG0_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((`$INSTANCE_NAME`_CFG0_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG0_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG0_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define `$INSTANCE_NAME`_CFG0_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define `$INSTANCE_NAME`_CFG0_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG0_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define `$INSTANCE_NAME`_CFG0_UABH_A_HIGHQDYN_CAP_CTRL ((1u < `$INSTANCE_NAME`_CFG0_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define `$INSTANCE_NAME`_CFG0_UABH_B_HIGHQDYN_CAP_CTRL (((1u < `$INSTANCE_NAME`_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < `$INSTANCE_NAME`_CFG0_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(`$INSTANCE_NAME`_CFG0_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != `$INSTANCE_NAME`_FILTER_CFG0_FILTER_PRESENT) */
/*******************************************************************************
* CFG1 definitions
*******************************************************************************/
#if (0u != `$INSTANCE_NAME`_FILTER_CFG1_FILTER_PRESENT)
    
    #define `$INSTANCE_NAME`_CFG1_FILTERTYPE_USED   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg1FilterTopology`
    #define `$INSTANCE_NAME`_CFG1_TRANSFERTYPE_0   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg1TransferType`
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL    (`$Cfg1GtC1Numerator`ul)
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_C1_DENOMINATOR_VAL  (`$Cfg1GtC1Denominator`ul)
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_C2_NUMERATOR_VAL    (`$Cfg1GtC2Numerator`ul)
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_C2_DENOMINATOR_VAL  (`$Cfg1GtC2Denominator`ul) 
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_C3_VAL              (`$Cfg1GtC3Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_C4_VAL              (`$Cfg1GtC4Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_Cp_VAL              (`$Cfg1GtCpNumerator`ul)      
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL   (`$Cfg1GtCppNumerator`ul)  
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL (`$Cfg1GtCppDenominator`ul)  
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_CA_VAL              (`$Cfg1GtCANumerator`ul)      
    #define `$INSTANCE_NAME`_CFG1_FILTER_GT_CB_VAL              (`$Cfg1GtCBNumerator`ul)     

    #define `$INSTANCE_NAME`_CFG1_FILTER_IDEAL_BIQUAD_NUM0      (`$Cfg1IdealBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_IDEAL_BIQUAD_NUM1      (`$Cfg1IdealBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_IDEAL_BIQUAD_NUM2      (`$Cfg1IdealBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_IDEAL_BIQUAD_DEN0      (`$Cfg1IdealBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_IDEAL_BIQUAD_DEN1      (`$Cfg1IdealBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_IDEAL_BIQUAD_DEN2      (`$Cfg1IdealBiquadDen2`)

    #define `$INSTANCE_NAME`_CFG1_FILTER_UAB_BIQUAD_NUM0        (`$Cfg1UabBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_UAB_BIQUAD_NUM1        (`$Cfg1UabBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_UAB_BIQUAD_NUM2        (`$Cfg1UabBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_UAB_BIQUAD_DEN0        (`$Cfg1UabBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_UAB_BIQUAD_DEN1        (`$Cfg1UabBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG1_FILTER_UAB_BIQUAD_DEN2        (`$Cfg1UabBiquadDen2`)
    
    #define `$INSTANCE_NAME`_CFG1_UABH_A_STARTUP_DELAY    ((uint32)((uint32)`$Cfg1FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    #define `$INSTANCE_NAME`_CFG1_UABH_B_STARTUP_DELAY    ((uint32)((uint32)`$Cfg1FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (`$INSTANCE_NAME`_CFG1_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < `$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == `$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == `$INSTANCE_NAME`_CFG1_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG1_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(`$INSTANCE_NAME`_CFG1_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE (`$INSTANCE_NAME`_CFG1_FILTER_GT_CA_VAL/4u)
        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(`$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((`$INSTANCE_NAME`_CFG1_FILTER_GT_CA_VAL - (2u * (`$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_ABCF_VAL ((`$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG1_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG1_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(`$INSTANCE_NAME`_CFG1_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG1_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((`$INSTANCE_NAME`_CFG1_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_CAP_CTRL ((((`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((`$INSTANCE_NAME`_CFG1_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define `$INSTANCE_NAME`_CFG1_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((`$INSTANCE_NAME`_CFG1_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define `$INSTANCE_NAME`_CFG1_UABH_B_LOWQDYN_CAP_CTRL     ((`$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define `$INSTANCE_NAME`_CFG1_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((`$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG1 High-Q definitions
    *******************************************************************************/
        
    #elif (`$INSTANCE_NAME`_CFG1_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define `$INSTANCE_NAME`_CFG1_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG1_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG1_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (`$INSTANCE_NAME`_CFG1_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (`$INSTANCE_NAME`_CFG1_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((`$INSTANCE_NAME`_CFG1_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG1_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (`$INSTANCE_NAME`_CFG1_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (`$INSTANCE_NAME`_CFG1_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((`$INSTANCE_NAME`_CFG1_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG1_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG1_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define `$INSTANCE_NAME`_CFG1_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define `$INSTANCE_NAME`_CFG1_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG1_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define `$INSTANCE_NAME`_CFG1_UABH_A_HIGHQDYN_CAP_CTRL ((1u < `$INSTANCE_NAME`_CFG1_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define `$INSTANCE_NAME`_CFG1_UABH_B_HIGHQDYN_CAP_CTRL (((1u < `$INSTANCE_NAME`_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < `$INSTANCE_NAME`_CFG1_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(`$INSTANCE_NAME`_CFG1_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != `$INSTANCE_NAME`_FILTER_CFG1_FILTER_PRESENT) */

/*******************************************************************************
* CFG2 definitions
*******************************************************************************/
#if (0u != `$INSTANCE_NAME`_FILTER_CFG2_FILTER_PRESENT)
    
    #define `$INSTANCE_NAME`_CFG2_FILTERTYPE_USED   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg2FilterTopology`
    #define `$INSTANCE_NAME`_CFG2_TRANSFERTYPE_0   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg2TransferType`
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL    (`$Cfg2GtC1Numerator`ul)
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_C1_DENOMINATOR_VAL  (`$Cfg2GtC1Denominator`ul)
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_C2_NUMERATOR_VAL    (`$Cfg2GtC2Numerator`ul)
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_C2_DENOMINATOR_VAL  (`$Cfg2GtC2Denominator`ul) 
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_C3_VAL              (`$Cfg2GtC3Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_C4_VAL              (`$Cfg2GtC4Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_Cp_VAL              (`$Cfg2GtCpNumerator`ul)      
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL   (`$Cfg2GtCppNumerator`ul)  
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL (`$Cfg2GtCppDenominator`ul)  
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_CA_VAL              (`$Cfg2GtCANumerator`ul)      
    #define `$INSTANCE_NAME`_CFG2_FILTER_GT_CB_VAL              (`$Cfg2GtCBNumerator`ul)     

    #define `$INSTANCE_NAME`_CFG2_FILTER_IDEAL_BIQUAD_NUM0      (`$Cfg2IdealBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_IDEAL_BIQUAD_NUM1      (`$Cfg2IdealBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_IDEAL_BIQUAD_NUM2      (`$Cfg2IdealBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_IDEAL_BIQUAD_DEN0      (`$Cfg2IdealBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_IDEAL_BIQUAD_DEN1      (`$Cfg2IdealBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_IDEAL_BIQUAD_DEN2      (`$Cfg2IdealBiquadDen2`)

    #define `$INSTANCE_NAME`_CFG2_FILTER_UAB_BIQUAD_NUM0        (`$Cfg2UabBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_UAB_BIQUAD_NUM1        (`$Cfg2UabBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_UAB_BIQUAD_NUM2        (`$Cfg2UabBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_UAB_BIQUAD_DEN0        (`$Cfg2UabBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_UAB_BIQUAD_DEN1        (`$Cfg2UabBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG2_FILTER_UAB_BIQUAD_DEN2        (`$Cfg2UabBiquadDen2`)
    
    #define `$INSTANCE_NAME`_CFG2_UABH_A_STARTUP_DELAY    ((uint32)((uint32)`$Cfg2FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    #define `$INSTANCE_NAME`_CFG2_UABH_B_STARTUP_DELAY    ((uint32)((uint32)`$Cfg2FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (`$INSTANCE_NAME`_CFG2_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < `$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == `$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == `$INSTANCE_NAME`_CFG2_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG2_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(`$INSTANCE_NAME`_CFG2_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE (`$INSTANCE_NAME`_CFG2_FILTER_GT_CA_VAL/4u)
        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(`$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((`$INSTANCE_NAME`_CFG2_FILTER_GT_CA_VAL - (2u * (`$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_ABCF_VAL ((`$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG2_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG2_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(`$INSTANCE_NAME`_CFG2_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG2_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((`$INSTANCE_NAME`_CFG2_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_CAP_CTRL ((((`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((`$INSTANCE_NAME`_CFG2_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define `$INSTANCE_NAME`_CFG2_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((`$INSTANCE_NAME`_CFG2_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define `$INSTANCE_NAME`_CFG2_UABH_B_LOWQDYN_CAP_CTRL     ((`$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define `$INSTANCE_NAME`_CFG2_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((`$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG2 High-Q definitions
    *******************************************************************************/
        
    #elif (`$INSTANCE_NAME`_CFG2_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define `$INSTANCE_NAME`_CFG2_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG2_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG2_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (`$INSTANCE_NAME`_CFG2_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (`$INSTANCE_NAME`_CFG2_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((`$INSTANCE_NAME`_CFG2_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG2_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (`$INSTANCE_NAME`_CFG2_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (`$INSTANCE_NAME`_CFG2_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((`$INSTANCE_NAME`_CFG2_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG2_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG2_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define `$INSTANCE_NAME`_CFG2_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define `$INSTANCE_NAME`_CFG2_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG2_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define `$INSTANCE_NAME`_CFG2_UABH_A_HIGHQDYN_CAP_CTRL ((1u < `$INSTANCE_NAME`_CFG2_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define `$INSTANCE_NAME`_CFG2_UABH_B_HIGHQDYN_CAP_CTRL (((1u < `$INSTANCE_NAME`_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < `$INSTANCE_NAME`_CFG2_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(`$INSTANCE_NAME`_CFG2_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != `$INSTANCE_NAME`_FILTER_CFG2_FILTER_PRESENT) */

/*******************************************************************************
* CFG3 definitions
*******************************************************************************/
#if (0u != `$INSTANCE_NAME`_FILTER_CFG3_FILTER_PRESENT)
    
    #define `$INSTANCE_NAME`_CFG3_FILTERTYPE_USED   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg3FilterTopology`
    #define `$INSTANCE_NAME`_CFG3_TRANSFERTYPE_0   `$INSTANCE_NAME`_FILTERTOPOLOGY_`$Cfg3TransferType`
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL    (`$Cfg3GtC1Numerator`ul)
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_C1_DENOMINATOR_VAL  (`$Cfg3GtC1Denominator`ul)
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_C2_NUMERATOR_VAL    (`$Cfg3GtC2Numerator`ul)
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_C2_DENOMINATOR_VAL  (`$Cfg3GtC2Denominator`ul) 
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_C3_VAL              (`$Cfg3GtC3Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_C4_VAL              (`$Cfg3GtC4Numerator`ul)      
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_Cp_VAL              (`$Cfg3GtCpNumerator`ul)      
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL   (`$Cfg3GtCppNumerator`ul)  
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL (`$Cfg3GtCppDenominator`ul)  
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_CA_VAL              (`$Cfg3GtCANumerator`ul)      
    #define `$INSTANCE_NAME`_CFG3_FILTER_GT_CB_VAL              (`$Cfg3GtCBNumerator`ul)     

    #define `$INSTANCE_NAME`_CFG3_FILTER_IDEAL_BIQUAD_NUM0      (`$Cfg3IdealBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_IDEAL_BIQUAD_NUM1      (`$Cfg3IdealBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_IDEAL_BIQUAD_NUM2      (`$Cfg3IdealBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_IDEAL_BIQUAD_DEN0      (`$Cfg3IdealBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_IDEAL_BIQUAD_DEN1      (`$Cfg3IdealBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_IDEAL_BIQUAD_DEN2      (`$Cfg3IdealBiquadDen2`)

    #define `$INSTANCE_NAME`_CFG3_FILTER_UAB_BIQUAD_NUM0        (`$Cfg3UabBiquadNum0`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_UAB_BIQUAD_NUM1        (`$Cfg3UabBiquadNum1`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_UAB_BIQUAD_NUM2        (`$Cfg3UabBiquadNum2`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_UAB_BIQUAD_DEN0        (`$Cfg3UabBiquadDen0`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_UAB_BIQUAD_DEN1        (`$Cfg3UabBiquadDen1`)
    #define `$INSTANCE_NAME`_CFG3_FILTER_UAB_BIQUAD_DEN2        (`$Cfg3UabBiquadDen2`)
    
    #define `$INSTANCE_NAME`_CFG3_UABH_A_STARTUP_DELAY    ((uint32)((uint32)`$Cfg3FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    #define `$INSTANCE_NAME`_CFG3_UABH_B_STARTUP_DELAY    ((uint32)((uint32)`$Cfg3FilterStartDelay`u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (`$INSTANCE_NAME`_CFG3_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < `$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == `$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == `$INSTANCE_NAME`_CFG3_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(`$INSTANCE_NAME`_CFG3_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(`$INSTANCE_NAME`_CFG3_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE (`$INSTANCE_NAME`_CFG3_FILTER_GT_CA_VAL/4u)
        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(`$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((`$INSTANCE_NAME`_CFG3_FILTER_GT_CA_VAL - (2u * (`$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_ABCF_VAL ((`$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (`$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG3_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG3_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(`$INSTANCE_NAME`_CFG3_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG3_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(`$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((`$INSTANCE_NAME`_CFG3_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_CAP_CTRL ((((`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((`$INSTANCE_NAME`_CFG3_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (`$INSTANCE_NAME`_UABH_A_halfuab__X0 << 2u))
            #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define `$INSTANCE_NAME`_CFG3_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((`$INSTANCE_NAME`_CFG3_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define `$INSTANCE_NAME`_CFG3_UABH_B_LOWQDYN_CAP_CTRL     ((`$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define `$INSTANCE_NAME`_CFG3_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((`$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG3 High-Q definitions
    *******************************************************************************/
        
    #elif (`$INSTANCE_NAME`_CFG3_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define `$INSTANCE_NAME`_CFG3_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG3_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG3_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (`$INSTANCE_NAME`_CFG3_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (`$INSTANCE_NAME`_CFG3_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((`$INSTANCE_NAME`_CFG3_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define `$INSTANCE_NAME`_CFG3_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == `$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (`$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (`$INSTANCE_NAME`_CFG3_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (`$INSTANCE_NAME`_CFG3_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((`$INSTANCE_NAME`_CFG3_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define `$INSTANCE_NAME`_CFG3_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG3_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define `$INSTANCE_NAME`_CFG3_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define `$INSTANCE_NAME`_CFG3_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < `$INSTANCE_NAME`_CFG3_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define `$INSTANCE_NAME`_CFG3_UABH_A_HIGHQDYN_CAP_CTRL ((1u < `$INSTANCE_NAME`_CFG3_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define `$INSTANCE_NAME`_CFG3_UABH_B_HIGHQDYN_CAP_CTRL (((1u < `$INSTANCE_NAME`_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < `$INSTANCE_NAME`_CFG3_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(`$INSTANCE_NAME`_CFG3_FILTERTYPE_USED == `$INSTANCE_NAME`_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != `$INSTANCE_NAME`_FILTER_CFG3_FILTER_PRESENT) */


#endif /* (`$INSTANCE_NAME`_ANY_CONFIG_USES_FILTER	!= 0u)	 */
#endif /* !defined(CY_`$INSTANCE_NAME`_FILTER_H) */
/* [] END OF FILE */
