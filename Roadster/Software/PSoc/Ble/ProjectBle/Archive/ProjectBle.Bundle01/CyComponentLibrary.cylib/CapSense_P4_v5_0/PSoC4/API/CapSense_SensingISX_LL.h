/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingISX_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the headers of APIs specific to ISX sensing implementation.
*
* \see `$INSTANCE_NAME` v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_SENSE_`$INSTANCE_NAME`_SENSINGISX_LL_H)
#define CY_SENSE_`$INSTANCE_NAME`_SENSINGISX_LL_H

#include "cytypes.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"

#if (0u != `$INSTANCE_NAME`_ISX_EN)

/***************************************
* API Constants
***************************************/

/* PERI CLOCK registers */

#if defined(CYIPBLOCK_m0s8gpio2_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8GPIO2_BLOCK         (1u)
    #define `$INSTANCE_NAME`_M0S8GPIO2_BLOCK_VER        (CYIPBLOCK_m0s8gpio2_VERSION)
#else
    #define `$INSTANCE_NAME`_IS_M0S8GPIO2_BLOCK         (0u)
    #define `$INSTANCE_NAME`_M0S8GPIO2_BLOCK_VER        (0u)
#endif /* (CYIPBLOCK_m0s8gpio2_VERSION) */

#if defined(CYIPBLOCK_m0s8hsiom4a_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8HSIOM4A_BLOCK       (1u)
    #define `$INSTANCE_NAME`_M0S8HSIOM4A_BLOCK_VER      (CYIPBLOCK_m0s8hsiom4a_VERSION)
#else
    #define `$INSTANCE_NAME`_IS_M0S8HSIOM4A_BLOCK       (0u)
    #define `$INSTANCE_NAME`_M0S8HSIOM4A_BLOCK_VER      (0u)
#endif /* (CYIPBLOCK_m0s8hsiom4a_VERSION) */

#if defined(CYIPBLOCK_m0s8ioss_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8IOSS_BLOCK          (1u)
    #define `$INSTANCE_NAME`_M0S8IOSS_BLOCK_VER         (CYIPBLOCK_m0s8ioss_VERSION)
#else
    #define `$INSTANCE_NAME`_IS_M0S8IOSS_BLOCK          (0u)
    #define `$INSTANCE_NAME`_M0S8IOSS_BLOCK_VER         (0u)
#endif /* (CYIPBLOCK_m0s8ioss_VERSION) */

#if defined(CYIPBLOCK_m0s8pclk_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8PCLK_BLOCK          (1u)
    #define `$INSTANCE_NAME`_M0S8PCLK_BLOCK_VER         (CYIPBLOCK_m0s8pclk_VERSION)
#else
    #define `$INSTANCE_NAME`_IS_M0S8PCLK_BLOCK          (0u)
    #define `$INSTANCE_NAME`_M0S8PCLK_BLOCK_VER         (0u)
#endif /* (CYIPBLOCK_m0s8pclk_VERSION) */

#if defined(CYIPBLOCK_m0s8peri_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK          (1u)
    #define `$INSTANCE_NAME`_M0S8PERI_BLOCK_VER         ((CYIPBLOCK_m0s8peri_VERSION))
#else
    #define `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK          (0u)
    #define `$INSTANCE_NAME`_M0S8PERI_BLOCK_VER         (0u)
#endif /* (CYIPBLOCK_m0s8peri_VERSION) */

#if defined(CYIPBLOCK_m0s8csd_VERSION)
    #define `$INSTANCE_NAME`_IS_M0S8CSD_BLOCK           (1u)
    #define `$INSTANCE_NAME`_M0S8CSD_BLOCK_VER          (CYIPBLOCK_m0s8csd_VERSION)
#else
    #define `$INSTANCE_NAME`_IS_M0S8CSD_BLOCK           (0u)
    #define `$INSTANCE_NAME`_M0S8CSD_BLOCK_VER          (0u)
#endif /* (CYIPBLOCK_m0s8csd_VERSION) */

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
* \cond (SECTION_C_LOW_LEVEL || SECTION_I_LOW_LEVEL)
* \addtogroup group_c_low_level
* \{
*/

void `$INSTANCE_NAME`_ISXSetupWidget(uint32 widgetId);
void `$INSTANCE_NAME`_ISXSetupWidgetExt(uint32 widgetId, uint32 snsIndex);
void `$INSTANCE_NAME`_ISXScan(void);
void `$INSTANCE_NAME`_ISXScanExt(void);

#if (`$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE)
    void `$INSTANCE_NAME`_ISXCalibrateWidget(uint32 widgetId, uint16 idacTarget);
#endif /* (`$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE) */

void `$INSTANCE_NAME`_ISXConnectLx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *lxPtr);
void `$INSTANCE_NAME`_ISXConnectRx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *rxPtr);
void `$INSTANCE_NAME`_ISXDisconnectLx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *lxPtr);
void `$INSTANCE_NAME`_ISXDisconnectRx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *rxPtr);


/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/** \cond SECTION_C_INTERNAL
*
* \addtogroup group_c_internal
* \{
*/

void `$INSTANCE_NAME`_ISXInitialize(void);
void `$INSTANCE_NAME`_ISXElectrodeCheck(void);

/** \}
* \endcond */

/*******************************************************************************
* Global variables exposed by the module
*******************************************************************************/

/* The pointer to the function used to register a callback in ISR */
extern void (* `$INSTANCE_NAME`_ISXPostScanApiPtr)(void);

/*******************************************************************************
* External APIs required by the module
*******************************************************************************/

/* The ISR for the ISX sensing module      */
CY_ISR_PROTO(`$INSTANCE_NAME`_SsISXScanISR);

/*******************************************************************************
* Function constants
*******************************************************************************/

/*
   +--------+---------------+--------------------------------------------+-------------------------------------------+
   |        |               | BLOCK_OFF_AFTER_SCAN=TRUE                  | BLOCK_OFF_AFTER_SCAN=FALSE                |
   +  BITS  +   FIELD       +--------------------------------------------+-------------------------------------------+
   |        |               |              MODE                          |              MODE                         |
   |--------|---------------|--------------------------------------------|-------------------------------------------|
   |  6:4   | FILTER_DELAY  | 0x02(2-SampleClk cycles)                   | 0x02(2-SampleClk cycles)                  |
   |  9:8   | SHIELD_DELAY  | 0x00(Delay Line is OFF)                    | 0x00(Delay Line is OFF)                   |
   |  12    | SENSE_EN      | 0x00(Disabled. All switches are open)      | 0x01(Enabled. Switches can be closed)     |
   |  14    | CHARGE_MODE   | 0x00(Use internal switches)                | 0x00(Use internal switches)               |
   |  18    | MUTUAL_CAP    | 0x01(Mutual-cap mode)                      | 0x01(Mutual-cap mode)                     |
   |  19    | CSX_DUAL_CNT  | 0x01(Use two counters)                     | 0x01(Use two counters)                    |
   |  24    | DSI_COUNT_SEL | 0x00(CSD-Result on the DSI_COUNT bus)      | 0x00(CSD-Result on DSI_COUNT bus)         |
   |  25    | DSI_SAMPLE_EN | 0x00(DSI_SAMPLE_IN is disabled)            | 0x00(DSI_SAMPLE_IN is disabled)           |
   |  26    | SAMPLE_SYNC   | 0x00(Double sync is disabled)              | 0x00(Double sync is disabled)             |
   |  27    | DSI_SENSE_EN  | 0x00(DSI_SENSE_IN is disabled)             | 0x00(DSI_SENSE_IN is disabled)            |
   |  30    | LP_MODE       | 0x00(High power mode)                      | 0x00(High power mode)                     |
   |  31    | ENABLE        | 0x00(Analog part is OFF)                   | 0x01(Analog part is ON)                   |
   +--------+---------------+--------------------------------------------+-------------------------------------------+ */
#if(0u != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CONFIG_CFG        (0x00000020uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CONFIG_CFG        (0x80041020uL)
#endif /* (0u != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 1      | SAMPLE        | 0x01(Clear CSD End Of Scan interrupt)                                                  |
   | 2      | INIT          | 0x01(Clear CSD End Of Coarse Init interrupt)                                           |
   | 8      | ADC_RES       | 0x01(Clear ADC End Of Scan interrupt)                                                  |
   +--------+---------------+----------------------------------------------------------------------------------------+ */
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_CFG              (0x00000106uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 1      | SAMPLE        | 0x00(CSD End Of Scan interrupt is cleared)                                             |
   | 2      | INIT          | 0x00(CSD End Of Coarse Init interrupt is cleared)                                      |
   | 8      | ADC_RES       | 0x00(ADC End Of Scan interrupt is cleared)                                             |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_SET_CFG          (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 1      | SAMPLE        | 0x00(CSD End Of Scan interrupt is masked)                                              |
   | 2      | INIT          | 0x00(CSD End Of Coarse Init interrupt is masked)                                       |
   | 8      | ADC_RES       | 0x00(ADC End Of Scan interrupt is masked)                                              |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_MASK_CFG         (0x00000002uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   |  0     |  HSCMP_EN     | 0x00(High Speed comparator is disabled)                                                |
   |  4     |  HSCMP_INVERT | 0x00(High Speed comparator output is not inverted)                                     |
   |  31    |  AZ_EN        | 0x00(Auto-Zero is disabled)                                                            |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_HSCMP_CFG            (0x00000000uL)

 /*+--------+---------------+------------------------------------------+-------------------------------------------+
   |        |               |           VDDA >= 2V                     |          VDDA <2V                         |
   +  BITS  +   FIELD       +------------------------------------------+-------------------------------------------+
   |        |               |              MODE                        |             MODE                          |
   |--------|---------------|------------------------------------------|-------------------------------------------|
   |  1:0   | PWR_MODE      | 0x00(Amux buffer is disabled)            | 0x01(Amux buffer is at normal power level)|
   +--------+---------------+------------------------------------------+-------------------------------------------+ */
#if (`$INSTANCE_NAME`_CYDEV_VDDA_MV >= 2000u)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_AMBUF_CFG           (0x00000000uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_AMBUF_CFG           (0x00000001uL)
#endif /* (CYDEV_VDDA_MV >= 2000u) */

 /*+--------+---------------+------------------------------------------+---------------------------------------------+
   |        |               |           VDDA >= 2V                     |          VDDA <2V                           |
   +  BITS  +   FIELD       +------------------------------------------+---------------------------------------------+
   |        |               |              MODE                        |             MODE                            |
   |--------|---------------|------------------------------------------|---------------------------------------------|
   |  0     | REFGEN_EN     | 0x01(Reference generator is enabled)     | 0x01(Reference generator is enabled)        |
   |  4     | BYPASS        | 0x00(BYPASS mode switch is open)         | 0x01(BYPASS mode switch is closed)          |
   |  5     | VDDA_EN       | 0x00(DDA mode switch is open)            | 0x00(VDDA mode switch is open)              |
   |  6     | RES_EN        | 0x01(Resistor string is enabled)         | 0x00(Resistor string is disabled)           |
   |  12:08 | GAIN          | 0x1F(All feedback switches are closed)   | 0x00(All feedback switches are open)        |
   |  20:16 | VREFLO_SEL    | 0x00(Open all VREFLO switches)           | 0x01(Close 1 lower VREFLO switch in the tap)|
   |  23    | VREFHI_SEL    | 0x00(Open VREF_LO_INT switch)            | 0x00(Open VREF_LO_INT switch)               |
   +--------+---------------+------------------------------------------+---------------------------------------------+ */
#if (`$INSTANCE_NAME`_CYDEV_VDDA_MV >= 2000u)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_REFGEN_CFG          (0x001E1F41uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_REFGEN_CFG          (0x00800011uL)
#endif /* (CYDEV_VDDA_MV >= 2000u) */

 /*+--------+---------------+------------------------------------------+---------------------------------------------+
   |        |               |        AUTO_ZERO_EN=TRUE                 |       AUTO_ZERO_EN=FALSE                    |
   +  BITS  +   FIELD       +------------------------------------------+---------------------------------------------+
   |        |               |              MODE                        |             MODE                            |
   |--------|---------------|------------------------------------------|---------------------------------------------|
   |  0     | CSDCMP_EN     | 0x00(CSD comparator is disabled)         | 0x00(CSD comparator is disabled)            |
   |  5:04  | POLARITY_SEL  | 0x00(IDAC_A polarity is used)            | 0x00(IDAC_A polarity is used)               |
   |  9:08  | CMP_PHASE     | 0x03(Comparator activated on both phases)| 0x03(Comparator activated in both phases)   |
   |  28    | CMP_MODE      | 0x00(CSD mode)                           | 0x00(CSD mode)                              |
   |  29    | FEEDBACK_MODE | 0x00(Feedback from sampling flip-flop)   | 0x00(Feedback from sampling flip-flop)      |
   |  31    | AZ_EN         | 0x01(Auto-Zero functionality is enabled) | 0x00(Auto-Zero functionality is disabled)   |
   +--------+---------------+------------------------------------------+---------------------------------------------+ */
#if(0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CSDCMP_CFG          (0x80000300uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CSDCMP_CFG          (0x00000300uL)
#endif /* (0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN) */

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 6:0    | VAL           | 0x00(Set IDAC value to "0")                                                            |
   | 7      | POL_DYN       | 0x01(Set dynamic IDAC polarity)                                                        |
   | 9:8    | POLARITY      | 0x02(IDAC polarity follows CSD_SENSE signal)                                           |
   | 11:10  | BAL_MODE      | 0x03(IDAC is enabled in both phases and disabled by CSDCOMP at the end of balancing)   |
   | 17:16  | LEG1_MODE     | 0x03(Configure LEG1 to CSD dynamic mode)                                               |
   | 19:18  | LEG2_MODE     | 0x03(Configure LEG2 to CSD dynamic mode)                                                                 |
   | 21     | DSI_CTRL_EN   | 0x00(IDAC DSI control is disabled)                                                     |
   | 23:22  | RANGE         | Set range according to Csx0IdacGainV2 parameter value                                  |
   | 24     | LEG1_EN       | 0x01(Output for LEG1 is enabled)                                                       |
   | 25     | LEG2_EN       | 0x01(Output for LEG2 is enabled)                                                      |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_IDACA_CFG           ((0x030f0f80uL) | ((`$INSTANCE_NAME`_ISX_IDAC_GAIN << CYFLD_CSD_RANGE__OFFSET) &\
                                                                                                     `$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK))

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 6:0    | VAL           | 0x00(Set IDAC value to "0")                                                            |
   | 7      | POL_DYN       | 0x00(Set to "0" since IDACB is not used)                                               |
   | 9:8    | POLARITY      | 0x00(Set to "0" since IDACB is not used)                                               |
   | 11:10  | BAL_MODE      | 0x00(Set to "0" since IDACB is not used)                                               |
   | 17:16  | LEG1_MODE     | 0x00(Set to "0" since IDACB is not used)                                               |
   | 19:18  | LEG2_MODE     | 0x00(Set to "0" since IDACB is not used)                                               |
   | 21     | DSI_CTRL_EN   | 0x00(Set to "0" since IDACB is not used)                                               |
   | 23:22  | RANGE         | 0x00(Set to "0" since IDACB is not used)                                               |
   | 24     | LEG1_EN       | 0x00(Output for LEG2 is disabled)                                                      |
   | 25     | LEG2_EN       | 0x00(Output for LEG2 is disabled)                                                      |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_IDACB_CFG           (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   +--------+---------------+----------------------------------------------------------------------------------------+
   | 1:0    | RES_HCAV      | 0x00(Configure HCAV switch to LOW resistance)                                          |
   | 3:2    | RES_HCAG      | 0x00(Configure HCAG switch to LOW resistance)                                          |
   | 5:4    | RES_HCBV      | 0x00(Configure HCBV switch to LOW resistance)                                          |
   | 7:6    | RES_HCBG      | 0x00(Configure HCBG switch to LOW resistance)                                          |
   | 17:16  | RES_F1PM      | 0x00(Configure F1PM switch to LOW resistance)                                          |
   | 19:18  | RES_F2PT      | 0x00(Configure 2PT switch to LOW resistance)                                           |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_RES_CFG          ((`$INSTANCE_NAME`_ISX_INIT_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET) |\
                                                          (`$INSTANCE_NAME`_ISX_INIT_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCAG__OFFSET) |\
                                                          (`$INSTANCE_NAME`_ISX_INIT_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET) |\
                                                          (`$INSTANCE_NAME`_ISX_INIT_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBG__OFFSET) |\
                                                          (`$INSTANCE_NAME`_ISX_INIT_SWITCH_RES << CYFLD_CSD_RES_F1PM__OFFSET) |\
                                                          (`$INSTANCE_NAME`_ISX_INIT_SWITCH_RES << CYFLD_CSD_RES_F2PT__OFFSET))

 /*+--------+---------------+--------------------------------------------+-------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   |  11:00 | SENSE_DIV     |  Set to ISX_LX_CLK_DIVIDER value                                                       |
   |  18:16 | LFSR_SIZE     |  0x00(Set to "0" since not used)                                                       |
   |  23:20 | LFSR_SCALE    |  0x00(Set to "0" since not used)                                                     |
   |  24    | LFSR_CLEAR    |  0x00(Set to "0" since not used)                                                  |
   |  25    | SEL_LFSR_MSB  |  0x00(Set to "0" since not used)                                                |
   +--------+---------------+-----------------------------+----------------------------------------------------------+ */
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SENSE_PERIOD_CFG    (`$INSTANCE_NAME`_ISX_LX_CLK_DIVIDER & `$INSTANCE_NAME`_SENSE_PERIOD_SENSE_DIV_MASK)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 11:0   | SENSE_WIDTH   | 0x0000(Set to "0" SenseClk cycles)                                                     |
   | 16     | SENSE_POL     | 0x00(Start with low phase)                                                             |
   | 18     | OVERLAP_PHI1  | 0x00(Non overlap for Phi1)                                                             |
   | 19     | OVERLAP_PHI2  | 0x00(Non overlap for Phi2)                                                             |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SENSE_DUTY_CFG      (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 0      | SW_HMPM       | 0x00(HMPM switch is statically open)                                                   |
   | 4      | SW_HMPT       | 0x00(HMPT switch is statically open)                                                   |
   | 8      | SW_HMPS       | 0x00(HMPS switch is statically open)                                                   |
   | 12     | SW_HMMA       | 0x00(HMMA switch is statically open)                                                   |
   | 16     | SW_HMMB       | 0x00(HMMB switch is statically open)                                                   |
   | 20     | SW_HMCA       | 0x00(HMCA switch is statically open)                                                   |
   | 24     | SW_HMCB       | 0x00(HMCB switch is statically open)                                                   |
   | 28     | SW_HMRH       | 0x00(HMRH switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_HS_P_SEL_CFG     (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 16     | SW_HCCC       | 0x00(HCCC switch is statically open)                                                   |
   | 20     | SW_HCCD       | 0x00(HCCD switch is statically open)                                                   |
   | 26:24  | SW_HCRH       | 0x00(HCRH switch is statically open)                                                   |
   | 30:28  | SW_HCRL       | 0x00(HCRL switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_HS_N_SEL_CFG     (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 2:0    | SW_HCAV       | 0x00(HCAV switch is statically open)                                                   |
   | 6:4    | SW_HCAG       | 0x00(HCAG switch is statically open)                                                   |
   | 10:8   | SW_HCBV       | 0x00(HCBV switch is statically open)                                                   |
   | 14:12  | SW_HCBG       | 0x00(HCBG switch is statically open)                                                   |
   | 16     | SW_HCCV       | 0x00(HCCV switch is statically open)                                                   |
   | 20     | SW_HCCG       | 0x00(HCCG switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_SHIELD_SEL_CFG   (0x00000000uL)

 /*+--------+---------------+--------------------------------------------+-------------------------------------------+
   |        |               |           VDDA >= 2V                       |          VDDA < 2V                        |
   +  BITS  +   FIELD       +--------------------------------------------+-------------------------------------------+
   |        |               |              MODE                          |             MODE                          |
   |--------|---------------|--------------------------------------------|-------------------------------------------|
   |  4     | SW_IRBY       | 0x00(IRBY switch is statically open)       | 0x00(IRBY switch is statically open)      |
   |  8     | SW_IRLB       | 0x00(IRLB switch is statically open)       | 0x01(IRLB switch is statically closed)    |
   |  12    | SW_ICA        | 0x00(ICA  switch is statically open)       | 0x00(ICA  switch is statically open)      |
   |  18:16 | SW_ICB        | 0x00(ICB  switch is statically open)       | 0x00(ICB  switch is statically open)      |
   |  20    | SW_IRLI       | 0x00(IRLI switch is statically open)       | 0x00(IRLI switch is statically open)      |
   |  24    | SW_IRH        | 0x00(IRH  switch is statically open)       | 0x01(IRH  switch is statically closed)    |
   |  28    | SW_IRL        | 0x00(IRL  switch is statically open)       | 0x00(IRL  switch is statically open)      |
   +--------+---------------+--------------------------------------------+-------------------------------------------+*/
#if (`$INSTANCE_NAME`_CYDEV_VDDA_MV >= 2000u)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_AMUXBUF_SEL_CFG  (0x00000000uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_AMUXBUF_SEL_CFG  (0x01000100uL)
#endif /* (CYDEV_VDDA_MV >= 2000u) */

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 12     | SW_BYA        | 0x01(BYA switch is statically closed)                                                  |
   | 16     | SW_BYB        | 0x00(BYB switch is statically open)                                                    |
   | 20     | SW_CBCC       | 0x00(CBCC switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_BYP_SEL_CFG      (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 2:0    | SW_SFPM       | 0x02(SFPM switch is controlled by Phi1 of SenseClk signal)                             |
   | 6:4    | SW_SFPT       | 0x03(SFPM switch is controlled by Phi2 of the SenseClk signal)                         |
   | 10:8   | SW_SFPS       | 0x00(SFPS switch is statically open)                                                   |
   | 12     | SW_SFMA       | 0x00(SFMA switch is statically open)                                                   |
   | 16     | SW_SFMB       | 0x00(SFMB switch is statically open)                                                   |
   | 20     | SW_SFCA       | 0x00(SFCA switch is statically open)                                                   |
   | 24     | SW_SFCB       | 0x00(SFCB switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_CMP_P_SEL_CFG    (0x00000023uL)

 /*+--------+---------------+--------------------------------------------+-------------------------------------------+
   |        |               |           VDDA >= 2V                       |          VDDA <2V                         |
   +  BITS  +   FIELD       +--------------------------------------------+-------------------------------------------+
   |        |               |              MODE                          |             MODE                          |
   |--------|---------------|--------------------------------------------|-------------------------------------------|
   |  26:24 | SW_SCRH       |  0x01(SFPS switch is statically closed)    | 0x00(SFPS switch is statically open)      |
   |  30:28 | SW_SCRL       |  0x00(SFPS switch is statically open)      | 0x01(SFPS switch is statically closed)    |
   +--------+---------------+--------------------------------------------+-------------------------------------------+ */
#if (`$INSTANCE_NAME`_CYDEV_VDDA_MV >= 2000u)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_CMP_N_SEL_CFG    (0x01000000uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_CMP_N_SEL_CFG    (0x10000000uL)
#endif /* (CYDEV_VDDA_MV >= 2000u) */

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 0      | SW_IAIB       | 0x00(IAIB switch is statically open)                                                   |
   | 4      | SW_IBCB       | 0x00(IBCB switch is statically open)                                                   |
   | 16     | SW_SGMB       | 0x00(SGMB switch is statically open)                                                   |
   | 24     | SW_SGRE       | 0x00(SGRE switch is statically open)                                                   |
   | 28     | SW_SGR        | 0x01(SGR switch is statically closed)                                                  |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_REFGEN_SEL_CFG   (0x10000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 0      | SW_F1PM       | 0x00(F1PM switch is statically open)                                                   |
   | 10:8   | SW_F1MA       | 0x00(F1MA switch is statically open)                                                   |
   | 18:16  | SW_F1CA       | 0x00(F1CA switch is statically open)                                                   |
   | 20     | SW_C1CC       | 0x00(C1CC switch is statically open)                                                   |
   | 24     | SW_C1CD       | 0x00(C1CD switch is statically open)                                                   |
   | 28     | SW_C1F1       | 0x00(C1F1 switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_FW_MOD_SEL_CFG   (0x00030201uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 4      | SW_F2PT       | 0x00(F2PT switch is statically open)                                                   |
   | 10:8   | SW_F2MA       | 0x00(F2MA switch is statically open)                                                   |
   | 14:12  | SW_F2CA       | 0x00(F2CA switch is statically open)                                                   |
   | 18:16  | SW_F2CB       | 0x00(F2CB switch is statically open)                                                   |
   | 20     | SW_C2CC       | 0x00(C2CC switch is statically open)                                                   |
   | 24     | SW_C2CD       | 0x00(C2CD switch is statically open)                                                   |
   | 28     | SW_C2F2       | 0x00(C2F2 switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_FW_TANK_SEL_CFG  (0x00002310uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 2:0    | DSI_CSH_TANK  | 0x03(DSI_CSH_TANK switch is controlled by Phi2 of SenseClk signal)                     |
   | 6:4    | DSI_CMOD      | 0x02(DSI_CMOD switch is controlled by Phi1 of SenseClk signal)                         |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_DSI_SEL_CFG      (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 7:0    | AZ_TIME       | Set to AUTO_ZERO_TIME value                                                            |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_TIME_CFG        (`$INSTANCE_NAME`_ISX_AUTO_ZERO_TIME &\
                                                          `$INSTANCE_NAME`_SEQ_INIT_CNT_CONV_CNT_MASK)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 15:0   | CONV_CNT      | 0x0014(Set coarse initialization time to 20 SenseClk periods)                          |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_INIT_CNT_CFG    (`$INSTANCE_NAME`_ISX_FINE_INIT_TIME)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 15:0   | CONV_CNT      | 0x0000(Sets the number of conversions per sample to "0")                               |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_NORM_CNT_CFG    (0x00000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 7:0    | ADC_TIME      | 0x00(Set to "0" since ADC is not used)                                                 |
   | 17:16  | ADC_MODE      | 0b00(Set to "0" since ADC is not used)                                                 |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_ADC_CTL_CFG         (0x00000000uL)

 /*+--------+---------------+--------------------------------------------+--------------------------------------------+
   |        |               |      AUTO_ZERO_EN=TRUE                     |     AUTO_ZERO_EN=TRUE                      |
   +  BITS  +   FIELD       +--------------------------------------------+--------------------------------------------+
   |        |               |              MODE                          |             MODE                           |
   |--------|---------------|--------------------------------------------|--------------------------------------------|
   |  0     | START         | 0x00(CSD sequencer is stopped)             | 0x00(CSD sequencer is stopped)             |
   |  1     | SEQ_MODE      | 0x00(Regular scan mode is used)            | 0x00(Regular scan mode is used)            |
   |  3     | ABORT         | 0x01(Reset CSD sequencer to IDLE state)    | 0x01(Reset CSD sequencer to IDLE state)    |
   |  4     | DSI_START_EN  | 0x00(Disable control by DSI)               | 0x00(Disable control by DSI)               |
   |  8     | AZ0_SKIP      | 0x00(Do not skip AZ0 state)                | 0x01(Skip AZ0 state)                       |
   |  9     | AZ1_SKIP      | 0x00(Do not skip AZ1 state)                | 0x01(Skip AZ1 state)                       |
   +--------+---------------+--------------------------------------------+--------------------------------------------+ */
#if(0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN)
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_START_CFG       (0x00000008uL)
#else
    #define `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_START_CFG       (0x00000308uL)
#endif /* (0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN) */

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   |  6:4   | FILTER_DELAY  | 0x02(Will be reconfigured in Run Time)                                                 |
   |  9:8   | SHIELD_DELAY  | 0x00(Delay Line is OFF)                                                                |
   |  12    | SENSE_EN      | 0x01(Enabled. Switches can be closed)                                                  |
   |  14    | CHARGE_MODE   | 0x00(Use internal switches)                                                            |
   |  18    | MUTUAL_CAP    | 0x01(Mutual-cap mode)                                                                  |
   |  19    | CSX_DUAL_CNT  | 0x01(Use two counters)                                                                 |
   |  24    | DSI_COUNT_SEL | 0x00(CSD-Result on DSI_COUNT bus)                                                      |
   |  25    | DSI_SAMPLE_EN | 0x00(DSI_SAMPLE_IN is disabled)                                                        |
   |  26    | SAMPLE_SYNC   | 0x00(Double sync is disabled)                                                          |
   |  27    | DSI_SENSE_EN  | 0x00(DSI_SENSE_IN is disabled)                                                         |
   |  30    | LP_MODE       | 0x00(High power mode)                                                                  |
   |  31    | ENABLE        | 0x01(Analog part is ON)                                                                |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRESCAN_CSD_CONFIG_CFG          (0x800C1000uL)

 /*+--------+---------------+--------------------------------------------+-------------------------------------------+
   |        |               |    AUTO_ZERO_EN=TRUE                       |    AUTO_ZERO_EN=FALSE                     |
   +  BITS  +   FIELD       +--------------------------------------------+-------------------------------------------+
   |        |               |              MODE                          |             MODE                          |
   |--------|---------------|--------------------------------------------|-------------------------------------------|
   |  0     | CSDCMP_EN     | 0x01(CSD comparator is Enabled)            | 0x01(CSD comparator is Eisabled)          |
   |  5:4   | POLARITY_SEL  | 0x00(IDAC_A polarity is used)              | 0x00(IDAC_A polarity is used)             |
   |  9:8   | CMP_PHASE     | 0x03(Comparator activated in both phases)  | 0x03(Comparator activated in both phases) |
   |  28    | CMP_MODE      | 0x00(CSD mode)                             | 0x00(CSD mode)                            |
   |  29    | FEEDBACK_MODE | 0x00(Feedback from sampling flip-flop)     | 0x00(Feedback from sampling flip-flop)    |
   |  31    | AZ_EN         | 0x01(Auto-Zero functionality is enabled)   | 0x00(Auto-Zero functionality is disabled) |
   +--------+---------------+--------------------------------------------+-------------------------------------------+ */
#if(0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN)
    #define `$INSTANCE_NAME`_PRESCAN_CSD_CSDCMP_CFG      (0x80000301uL)
#else
    #define `$INSTANCE_NAME`_PRESCAN_CSD_CSDCMP_CFG      (0x00000301uL)
#endif /* (0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN) */

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   |  0     |  HSCMP_EN     | 0x01(High Speed comparator is Enabled)                                                 |
   |  4     |  HSCMP_INVERT | 0x00(High Speed comparator output is not inverted)                                     |
   |  31    |  AZ_EN        | 0x00(Auto-Zero is Disabled)                                                            |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_HSCMP_CFG             (0x00000001uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 0      | SW_HMPM       | 0x01(HMPM switch is statically closed)                                                 |
   | 4      | SW_HMPT       | 0x01(HMPT switch is statically closed)                                                 |
   | 8      | SW_HMPS       | 0x00(HMPS switch is statically open)                                                   |
   | 12     | SW_HMMA       | 0x00(HMMA switch is statically open)                                                   |
   | 16     | SW_HMMB       | 0x00(HMMB switch is statically open)                                                   |
   | 20     | SW_HMCA       | 0x00(HMCA switch is statically open)                                                   |
   | 24     | SW_HMCB       | 0x00(HMCB switch is statically open)                                                   |
   | 28     | SW_HMRH       | 0x00(HMRH switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SW_HS_P_SEL_CFG     (0x00000011uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 16     | SW_HCCC       | 0x00(HCCC switch is statically open)                                                   |
   | 20     | SW_HCCD       | 0x00(HCCD switch is statically open)                                                   |
   | 26:24  | SW_HCRH       | 0x01(HCRH switch is statically closed)                                                 |
   | 30:28  | SW_HCRL       | 0x00(HCRL switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SW_HS_N_SEL_CFG     (0x01000000uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 2:0    | DSI_CSH_TANK  | 0x01(DSI_CSH_TANK switch is statically closed)                                         |
   | 6:4    | DSI_CMOD      | 0x01(DSI_CMOD     switch is statically closed)                                         |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SW_DSI_SEL_CFG      (0x00000011uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 2:0    | SW_HCAV       | 0x06(HCAV switch is controlled by HSCMP output)                                        |
   | 6:4    | SW_HCAG       | 0x00(HCAG switch is statically open)                                                   |
   | 10:8   | SW_HCBV       | 0x00(HCBV switch is statically open)                                                   |
   | 14:12  | SW_HCBG       | 0x00(HCBG switch is statically open)                                                   |
   | 16     | SW_HCCV       | 0x00(HCCV switch is statically open)                                                   |
   | 20     | SW_HCCG       | 0x00(HCCG switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SW_SHIELD_SEL_CFG   (0x00000006uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 0      | SW_F1PM       | 0x00(F1PM switch is statically open)                                                   |
   | 10:8   | SW_F1MA       | 0x00(F1MA switch is statically open)                                                   |
   | 18:16  | SW_F1CA       | 0x00(F1CA switch is statically open)                                                   |
   | 20     | SW_C1CC       | 0x00(C1CC switch is statically open)                                                   |
   | 24     | SW_C1CD       | 0x00(C1CD switch is statically open)                                                   |
   | 28     | SW_C1F1       | 0x00(C1F1 switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SW_FW_MOD_SEL_CFG   (0x00010101uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 4      | SW_F2PT       | 0x00(F2PT switch is statically open)                                                   |
   | 10:8   | SW_F2MA       | 0x00(F2MA switch is statically open)                                                   |
   | 14:12  | SW_F2CA       | 0x00(F2CA switch is statically open)                                                   |
   | 18:16  | SW_F2CB       | 0x00(F2CB switch is statically open)                                                   |
   | 20     | SW_C2CC       | 0x00(C2CC switch is statically open)                                                   |
   | 24     | SW_C2CD       | 0x00(C2CD switch is statically open)                                                   |
   | 28     | SW_C2F2       | 0x00(C2F2 switch is statically open)                                                   |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SW_FW_TANK_SEL_CFG  (0x00001010uL)

/* +--------+---------------+----------------------------------------------------------------------------------------+
   |  BITS  |   FIELD       |              MODE                                                                      |
   |--------|---------------|----------------------------------------------------------------------------------------|
   | 0      | START         | 0x01(STARTED)                                                                          |
   | 1      | SEQ_MODE      | 0x01(INIT_COARSE)                                                                      |
   | 3      | ABORT         | 0x00(RESET_TO_IDLE_STATE)                                                              |
   | 4      | DSI_START_EN  | 0x00(DISABLE_CONTROL_BY_DSI)                                                           |
   | 8      | AZ0_SKIP      | 0x00(DO_NOT_SKIP_AZ0)                                                                  |
   | 9      | AZ1_SKIP      | 0x00(DO_BOT_SKIP_AZ1)                                                                  |
   +--------+---------------+----------------------------------------------------------------------------------------+*/
#define `$INSTANCE_NAME`_PRECHARGE_CSD_SEQ_START_CFG       (0x00000303uL)

 /*+--------+---------------+--------------------------------------------+--------------------------------------------+
   |        |               |      AUTO_ZERO_EN=TRUE                     |     AUTO_ZERO_EN=TRUE                      |
   +  BITS  +   FIELD       +--------------------------------------------+--------------------------------------------+
   |        |               |              MODE                          |             MODE                           |
   |--------|---------------|--------------------------------------------|--------------------------------------------|
   |  0     | START         | 0x01(CSD sequencer is stopped)             | 0x01(CSD sequencer is stopped)             |
   |  1     | SEQ_MODE      | 0x00(Regular CSD scan mode is used)        | 0x00(Regular CSD scan mode is used)        |
   |  3     | ABORT         | 0x00(Do not reset CSD sequencer)           | 0x00(Do not reset CSD sequencer)           |
   |  4     | DSI_START_EN  | 0x00(Disable control by DSI)               | 0x00(Disable control by DSI)               |
   |  8     | AZ0_SKIP      | 0x00(Do not skip AZ0 state)                | 0x01(Skip AZ0 state)                       |
   |  9     | AZ1_SKIP      | 0x00(Do not skip AZ1 state)                | 0x01(Skip AZ1 state)                       |
   +--------+---------------+--------------------------------------------+--------------------------------------------+ */
#if(0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN)
    #define `$INSTANCE_NAME`_SCAN_CSD_SEQ_START_CFG   (0x00000001uL)
#else
    #define `$INSTANCE_NAME`_SCAN_CSD_SEQ_START_CFG   (0x00000301uL)
#endif /* (0u != `$INSTANCE_NAME`_ISX_AUTO_ZERO_EN)  */

#define `$INSTANCE_NAME`_ISX_DEADBAND_CYCLES_NUMBER   (2u)

#define `$INSTANCE_NAME`_ISX_DEFAULT_IDAC_TARGET      (60u)

#define `$INSTANCE_NAME`_CONST_360                    (360u)

/* The definition of the time interval is long enough for charging a 100-nF capacitor */
#define `$INSTANCE_NAME`_ISX_MAX_CHARGE_TIME_US             (100u)
#define `$INSTANCE_NAME`_ISX_AVG_CYCLES_PER_LOOP            (5u)
#define `$INSTANCE_NAME`_ISX_PRECHARGE_WATCHDOG_CYCLES_NUM  (((CYDEV_BCLK__SYSCLK__MHZ) * (`$INSTANCE_NAME`_ISX_MAX_CHARGE_TIME_US)) /\
                                                            (`$INSTANCE_NAME`_ISX_AVG_CYCLES_PER_LOOP))
/*
 * Scan timer should be (NumSub * F_Mod) / (F_Lx * Cyc_Avg)
 * NumSub is limited by design by: NumSub < 2^16 * (F_Lx / F_Mod)
 * Substituting, we find scan timer is (2^16 - 1) / Cyc_Avg
 */
#define `$INSTANCE_NAME`_ISX_NUMSUB_WORST_CASE              (0xffffuL)
#define `$INSTANCE_NAME`_ISX_SCAN_WATCHDOG_CYCLES_NUM       (`$INSTANCE_NAME`_ISX_NUMSUB_WORST_CASE / `$INSTANCE_NAME`_ISX_AVG_CYCLES_PER_LOOP)
#define `$INSTANCE_NAME`_USES_PORT_3      (`$INSTANCE_NAME`_TOTAL_ISX_WIDGETS > 8u)

#ifdef `$INSTANCE_NAME`_Rsv__0__SHIFT
    #if `$INSTANCE_NAME`_USES_PORT_3
        #define `$INSTANCE_NAME`_RSV_PORT   (3u)
        #define `$INSTANCE_NAME`_DIG1_CHAN0 (`$INSTANCE_NAME`_Lx_1__0__SHIFT)
        #define `$INSTANCE_NAME`_DIG1_CHAN1 (`$INSTANCE_NAME`_Lx_1__1__SHIFT)
        #define `$INSTANCE_NAME`_DIG2_CHAN0 (`$INSTANCE_NAME`_Lx_2__0__SHIFT)
        #define `$INSTANCE_NAME`_DIG2_CHAN1 (`$INSTANCE_NAME`_Rsv__0__SHIFT)
        #define `$INSTANCE_NAME`_RSV2_MASK  (0u)
        #define `$INSTANCE_NAME`_RSV3_MASK  (1u << `$INSTANCE_NAME`_Rsv__0__SHIFT)
    #else
        #define `$INSTANCE_NAME`_RSV_PORT   (2u)
        #define `$INSTANCE_NAME`_DIG1_CHAN0 (`$INSTANCE_NAME`_Lx_1__0__SHIFT)
        #define `$INSTANCE_NAME`_DIG1_CHAN1 (`$INSTANCE_NAME`_Rsv__0__SHIFT)
        #define `$INSTANCE_NAME`_RSV2_MASK  (1u << `$INSTANCE_NAME`_Rsv__0__SHIFT)
        #define `$INSTANCE_NAME`_RSV3_MASK  (0u)
    #endif
#else
    #define `$INSTANCE_NAME`_RSV_PORT       (0xffu)
    #define `$INSTANCE_NAME`_RSV2_MASK  (0u)
    #define `$INSTANCE_NAME`_RSV3_MASK  (0u)
    #if `$INSTANCE_NAME`_USES_PORT_3
        #define `$INSTANCE_NAME`_DIG1_CHAN0 (`$INSTANCE_NAME`_Lx_1__0__SHIFT)
        #define `$INSTANCE_NAME`_DIG1_CHAN1 (`$INSTANCE_NAME`_Lx_1__1__SHIFT)
        #define `$INSTANCE_NAME`_DIG2_CHAN0 (`$INSTANCE_NAME`_Lx_2__0__SHIFT)
        #define `$INSTANCE_NAME`_DIG2_CHAN1 (`$INSTANCE_NAME`_Lx_2__1__SHIFT)
    #else
        #define `$INSTANCE_NAME`_DIG1_CHAN0 (`$INSTANCE_NAME`_Lx_1__0__SHIFT)
        #define `$INSTANCE_NAME`_DIG1_CHAN1 (`$INSTANCE_NAME`_Lx_1__1__SHIFT)
    #endif
#endif

#define `$INSTANCE_NAME`_DIG1_PIN_MASK     ((0xFuL << (4u * `$INSTANCE_NAME`_DIG1_CHAN0)) \
                                         | ( 0xFuL << (4u * `$INSTANCE_NAME`_DIG1_CHAN1)))
#define `$INSTANCE_NAME`_DIG1_PIN_CONNECT  ((((uint32)CYVAL_HSIOM_IO0_SEL_CSD_SENSE) << (4u * `$INSTANCE_NAME`_DIG1_CHAN0)) \
                                         | ( ((uint32)CYVAL_HSIOM_IO0_SEL_CSD_SENSE) << (4u * `$INSTANCE_NAME`_DIG1_CHAN1)))

#if `$INSTANCE_NAME`_USES_PORT_3
    #define `$INSTANCE_NAME`_DIG2_PIN_MASK     ((0xFuL << (4u * `$INSTANCE_NAME`_DIG2_CHAN0)) \
                                             | ( 0xFuL << (4u * `$INSTANCE_NAME`_DIG2_CHAN1)))
    #define `$INSTANCE_NAME`_DIG2_PIN_CONNECT  ((((uint32)CYVAL_HSIOM_IO0_SEL_CSD_SENSE) << (4u * `$INSTANCE_NAME`_DIG2_CHAN0)) \
                                             | (((uint32) CYVAL_HSIOM_IO0_SEL_CSD_SENSE) << (4u * `$INSTANCE_NAME`_DIG2_CHAN1)))
#endif /* `$INSTANCE_NAME`_USES_PORT_3 */

#define `$INSTANCE_NAME`_DIG_OUT (0xAAu)
#define `$INSTANCE_NAME`_DIG_IN (0xCCu)

#define `$INSTANCE_NAME`_ON_PORT_2(wi)    ((wi) < 8uL)
#define `$INSTANCE_NAME`_CALC_DIG_IO(p)  (((8u + ((p) % 4u)) << 8u) | ((8u + ((p) % 4u)) << 16u))
#define `$INSTANCE_NAME`_DIG_DEL          (30uL)
#define `$INSTANCE_NAME`_DIG_CORRECTION   (60uL)

#endif  /* End of `$INSTANCE_NAME`_ISX_EN */
#endif  /* End of !defined(`$INSTANCE_NAME`_SENSING_ISX_LL_H) */


/* [] END OF FILE */
