/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingCSD2X_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the headers of APIs specific to the CSD2X sensing implementation.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD2X_LL_H)

#define CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD2X_LL_H
    
#include "cytypes.h"
#include "cyfitter.h"
#include "project.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Sensing.h"

/***************************************
* Function Prototypes
***************************************/

/**
* \cond SECTION_C_HIGH_LEVEL
* \addtogroup group_c_high_level
* \{
*/
    
cystatus `$INSTANCE_NAME`_SetupWidget2x( uint32 slotIndex);
cystatus `$INSTANCE_NAME`_Scan2x(void);
void `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr);
void `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr);

/** \}
* \endcond */

/**
* \cond SECTION_C_LOW_LEVEL
* \addtogroup group_c_low_level
* \{
*/

void `$INSTANCE_NAME`_CSD2XInitialize(void);

/** \}
* \endcond */

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

void `$INSTANCE_NAME`_SsCSD0SetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider);
void `$INSTANCE_NAME`_SsCSD1SetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider);
void `$INSTANCE_NAME`_SsCSD0CalculateScanDuration(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt);
void `$INSTANCE_NAME`_SsCSD1CalculateScanDuration(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt);
void `$INSTANCE_NAME`_SsCSD0SetUpIdacs(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt);
void `$INSTANCE_NAME`_SsCSD1SetUpIdacs(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt);
void `$INSTANCE_NAME`_SsCSDConnectSensorExt(uint32 wdgtIndex, uint32 sensorIndex);
void `$INSTANCE_NAME`_SsCSDDisconnectSnsExt(uint32 wdgtIndex, uint32 sensorIndex);
void `$INSTANCE_NAME`_SsCSD2XStartSample(void);
void `$INSTANCE_NAME`_SsCSD0ConfigClock(void);
void `$INSTANCE_NAME`_SsCSD1ConfigClock(void);
cystatus `$INSTANCE_NAME`_CSD2XCalibrateWidget(uint32 wdgtIndex, uint32 target);

/** \}
* \endcond */


/***************************************
* Global software variables
***************************************/
extern uint32 `$INSTANCE_NAME`_configCsd0;
extern uint32 `$INSTANCE_NAME`_configCsd1;
extern volatile uint8 `$INSTANCE_NAME`_slotIndex;

/* Interrupt handler */
extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSD0PostMultiScan);
extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSD1PostMultiScan);
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
    extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSD0PostMultiScanGanged);
    extern CY_ISR_PROTO(`$INSTANCE_NAME`_CSD1PostMultiScanGanged);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */


/****************************************************************************
* m0s8csd, m0s8peri, hsiom, and IO hardware-related registers address
****************************************************************************/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    /* CSD0 block registers   */
    #define `$INSTANCE_NAME`_CSD0_CONFIG_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_CONFIG)
    #define `$INSTANCE_NAME`_CSD0_CONFIG_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_CONFIG)
    #define `$INSTANCE_NAME`_CSD0_IDAC_CONTR_REG                 (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CONTROL)
    #define `$INSTANCE_NAME`_CSD0_IDAC_CONTR_PTR                 ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CONTROL)
    #define `$INSTANCE_NAME`_CSD0_IDAC_REG                       (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_IDAC)
    #define `$INSTANCE_NAME`_CSD0_IDAC_PTR                       ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_IDAC)
    #define `$INSTANCE_NAME`_CSD0_COUNTER_REG                    (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_COUNTER)
    #define `$INSTANCE_NAME`_CSD0_COUNTER_PTR                    ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_COUNTER)
    #define `$INSTANCE_NAME`_CSD0_STATUS_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_STATUS)
    #define `$INSTANCE_NAME`_CSD0_STATUS_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_STATUS)
    #define `$INSTANCE_NAME`_CSD0_INTR_REG                       (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR)
    #define `$INSTANCE_NAME`_CSD0_INTR_PTR                       ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR)
    #define `$INSTANCE_NAME`_CSD0_INTR_SET_REG                   (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR_SET)
    #define `$INSTANCE_NAME`_CSD0_INTR_SET_PTR                   ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_INTR_SET)
    #define `$INSTANCE_NAME`_CSD0_PWM_REG                        (*(reg32 *) `$INSTANCE_NAME`_CSD0__CSD_PWM)
    #define `$INSTANCE_NAME`_CSD0_PWM_PTR                        ( (reg32 *) `$INSTANCE_NAME`_CSD0__CSD_PWM)
    #define `$INSTANCE_NAME`_CSD0_TRIM1_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM1)
    #define `$INSTANCE_NAME`_CSD0_TRIM1_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM1)
    #define `$INSTANCE_NAME`_CSD0_TRIM2_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM2)
    #define `$INSTANCE_NAME`_CSD0_TRIM2_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod0_cy_psoc4_idac__CSD_TRIM2)
    
    /* CSD1 block registers   */
    #define `$INSTANCE_NAME`_CSD1_CONFIG_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD1__CSD_CONFIG)
    #define `$INSTANCE_NAME`_CSD1_CONFIG_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD1__CSD_CONFIG)
    #define `$INSTANCE_NAME`_CSD1_IDAC_CONTR_REG                 (*(reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CONTROL)
    #define `$INSTANCE_NAME`_CSD1_IDAC_CONTR_PTR                 ( (reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CONTROL)
    #define `$INSTANCE_NAME`_CSD1_IDAC_REG                       (*(reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CSD_IDAC)
    #define `$INSTANCE_NAME`_CSD1_IDAC_PTR                       ( (reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CSD_IDAC)
    #define `$INSTANCE_NAME`_CSD1_COUNTER_REG                    (*(reg32 *) `$INSTANCE_NAME`_CSD1__CSD_COUNTER)
    #define `$INSTANCE_NAME`_CSD1_COUNTER_PTR                    ( (reg32 *) `$INSTANCE_NAME`_CSD1__CSD_COUNTER)
    #define `$INSTANCE_NAME`_CSD1_STATUS_REG                     (*(reg32 *) `$INSTANCE_NAME`_CSD1__CSD_STATUS)
    #define `$INSTANCE_NAME`_CSD1_STATUS_PTR                     ( (reg32 *) `$INSTANCE_NAME`_CSD1__CSD_STATUS)
    #define `$INSTANCE_NAME`_CSD1_INTR_REG                       (*(reg32 *) `$INSTANCE_NAME`_CSD1__CSD_INTR)
    #define `$INSTANCE_NAME`_CSD1_INTR_PTR                       ( (reg32 *) `$INSTANCE_NAME`_CSD1__CSD_INTR)
    #define `$INSTANCE_NAME`_CSD1_INTR_SET_REG                   (*(reg32 *) `$INSTANCE_NAME`_CSD1__CSD_INTR_SET)
    #define `$INSTANCE_NAME`_CSD1_INTR_SET_PTR                   ( (reg32 *) `$INSTANCE_NAME`_CSD1__CSD_INTR_SET)
    #define `$INSTANCE_NAME`_CSD1_PWM_REG                        (*(reg32 *) `$INSTANCE_NAME`_CSD1__CSD_PWM)
    #define `$INSTANCE_NAME`_CSD1_PWM_PTR                        ( (reg32 *) `$INSTANCE_NAME`_CSD1__CSD_PWM)
    #define `$INSTANCE_NAME`_CSD1_TRIM1_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CSD_TRIM1)
    #define `$INSTANCE_NAME`_CSD1_TRIM1_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CSD_TRIM1)
    #define `$INSTANCE_NAME`_CSD1_TRIM2_REG                      (*(reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CSD_TRIM2)
    #define `$INSTANCE_NAME`_CSD1_TRIM2_PTR                      ( (reg32 *) `$INSTANCE_NAME`_IDACMod1_cy_psoc4_idac__CSD_TRIM2) 
    
    /* Cmod and Csh capacitor port-pins registers */
    #define `$INSTANCE_NAME`_CSH0_PC_REG                         (* (reg32 *) `$INSTANCE_NAME`_Csh0__PC)
    #define `$INSTANCE_NAME`_CSH0_PC_PTR                         (  (reg32 *) `$INSTANCE_NAME`_Csh0__PC)
    #define `$INSTANCE_NAME`_CSH0_DR_REG                         (* (reg32 *) `$INSTANCE_NAME`_Csh0__DR)
    #define `$INSTANCE_NAME`_CSH0_DR_PTR                         (  (reg32 *) `$INSTANCE_NAME`_Csh0__DR)
    #define `$INSTANCE_NAME`_CSH0_HSIOM_REG                      (* (reg32 *) `$INSTANCE_NAME`_Csh0__0__HSIOM)
    #define `$INSTANCE_NAME`_CSH0_HSIOM_PTR                      (  (reg32 *) `$INSTANCE_NAME`_Csh0__0__HSIOM)
    #define `$INSTANCE_NAME`_CMOD0_PC_REG                        (* (reg32 *) `$INSTANCE_NAME`_Cmod0__PC)
    #define `$INSTANCE_NAME`_CMOD0_PC_PTR                        (  (reg32 *) `$INSTANCE_NAME`_Cmod0__PC)
    #define `$INSTANCE_NAME`_CMOD0_DR_REG                        (* (reg32 *) `$INSTANCE_NAME`_Cmod0__DR)
    #define `$INSTANCE_NAME`_CMOD0_DR_PTR                        (  (reg32 *) `$INSTANCE_NAME`_Cmod0__DR)
    #define `$INSTANCE_NAME`_CMOD0_HSIOM_REG                     (* (reg32 *) `$INSTANCE_NAME`_Cmod0__0__HSIOM)
    #define `$INSTANCE_NAME`_CMOD0_HSIOM_PTR                     (  (reg32 *) `$INSTANCE_NAME`_Cmod0__0__HSIOM)

    #define `$INSTANCE_NAME`_CSH1_PC_REG                         (* (reg32 *) `$INSTANCE_NAME`_Csh1__PC)
    #define `$INSTANCE_NAME`_CSH1_PC_PTR                         (  (reg32 *) `$INSTANCE_NAME`_Csh1__PC)
    #define `$INSTANCE_NAME`_CSH1_DR_REG                         (* (reg32 *) `$INSTANCE_NAME`_Csh1__DR)
    #define `$INSTANCE_NAME`_CSH1_DR_PTR                         (  (reg32 *) `$INSTANCE_NAME`_Csh1__DR)
    #define `$INSTANCE_NAME`_CSH1_HSIOM_REG                      (* (reg32 *) `$INSTANCE_NAME`_Csh1__0__HSIOM)
    #define `$INSTANCE_NAME`_CSH1_HSIOM_PTR                      (  (reg32 *) `$INSTANCE_NAME`_Csh1__0__HSIOM)
    #define `$INSTANCE_NAME`_CMOD1_PC_REG                        (* (reg32 *) `$INSTANCE_NAME`_Cmod1__PC)
    #define `$INSTANCE_NAME`_CMOD1_PC_PTR                        (  (reg32 *) `$INSTANCE_NAME`_Cmod1__PC)
    #define `$INSTANCE_NAME`_CMOD1_DR_REG                        (* (reg32 *) `$INSTANCE_NAME`_Cmod1__DR)
    #define `$INSTANCE_NAME`_CMOD1_DR_PTR                        (  (reg32 *) `$INSTANCE_NAME`_Cmod1__DR)
    #define `$INSTANCE_NAME`_CMOD1_HSIOM_REG                     (* (reg32 *) `$INSTANCE_NAME`_Cmod1__0__HSIOM)
    #define `$INSTANCE_NAME`_CMOD1_HSIOM_PTR                     (  (reg32 *) `$INSTANCE_NAME`_Cmod1__0__HSIOM)
    

    #define `$INSTANCE_NAME`_CSD0_SFLASH_TRIM1_REG               (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
    #define `$INSTANCE_NAME`_CSD0_SFLASH_TRIM1_PTR               ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

    #define `$INSTANCE_NAME`_CSD0_SFLASH_TRIM2_REG               (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #define `$INSTANCE_NAME`_CSD0_SFLASH_TRIM2_PTR               ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)

    #define `$INSTANCE_NAME`_CSD1_SFLASH_TRIM1_REG               (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
    #define `$INSTANCE_NAME`_CSD1_SFLASH_TRIM1_PTR               ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

    #define `$INSTANCE_NAME`_CSD1_SFLASH_TRIM2_REG               (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
    #define `$INSTANCE_NAME`_CSD1_SFLASH_TRIM2_PTR               ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)

    /* AMUX splitter cell control  */
    #define `$INSTANCE_NAME`_HSIOM_AMUX_SPLIT_REG                (* (reg32 *) CYREG_HSIOM_AMUX_SPLIT_CTL0)
    #define `$INSTANCE_NAME`_HSIOM_AMUX_SPLIT_PTR                (  (reg32 *) CYREG_HSIOM_AMUX_SPLIT_CTL0)

    /***************************************
    * CSDv1 Registers masks
    ***************************************/

    /* Cmod and Csh pin masks */
    #define `$INSTANCE_NAME`_CMOD0_HSIOM_MASK                   (`$INSTANCE_NAME`_Cmod0__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CMOD0_HSIOM_SHIFT                  (`$INSTANCE_NAME`_Cmod0__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CSH0_HSIOM_MASK                    (`$INSTANCE_NAME`_Csh0__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CSH0_HSIOM_SHIFT                   (`$INSTANCE_NAME`_Csh0__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CSH0_SHIFT                         (`$INSTANCE_NAME`_Csh0__0__SHIFT)
    #define `$INSTANCE_NAME`_CSH0_TO_AMUXBUS_B_MASK             (`$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK)
    #define `$INSTANCE_NAME`_CSH0_PC_MASK                       (`$INSTANCE_NAME`_CSH_PC_MASK)
    #define `$INSTANCE_NAME`_CSH0_PC_STRONG_MODE                (`$INSTANCE_NAME`_CSH_PC_STRONG_MODE)
    #define `$INSTANCE_NAME`_CSH0_PC_SHIFT                      (`$INSTANCE_NAME`_Csh0__0__SHIFT * 3u)
    #define `$INSTANCE_NAME`_CSH0_DR_MASK                       (`$INSTANCE_NAME`_DR_MASK)
    
    #define `$INSTANCE_NAME`_CMOD1_HSIOM_MASK                   (`$INSTANCE_NAME`_Cmod1__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CMOD1_HSIOM_SHIFT                  (`$INSTANCE_NAME`_Cmod1__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CSH1_HSIOM_MASK                    (`$INSTANCE_NAME`_Csh1__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CSH1_HSIOM_SHIFT                   (`$INSTANCE_NAME`_Csh1__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CSH1_SHIFT                         (`$INSTANCE_NAME`_Csh1__0__SHIFT)
    #define `$INSTANCE_NAME`_CSH1_TO_AMUXBUS_B_MASK             (`$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK)
    #define `$INSTANCE_NAME`_CSH1_PC_MASK                       (`$INSTANCE_NAME`_CSH_PC_MASK)
    #define `$INSTANCE_NAME`_CSH1_PC_STRONG_MODE                (`$INSTANCE_NAME`_CSH_PC_STRONG_MODE)
    #define `$INSTANCE_NAME`_CSH1_PC_SHIFT                      (`$INSTANCE_NAME`_Csh1__0__SHIFT * 3u)
    #define `$INSTANCE_NAME`_CSH1_DR_MASK                       (`$INSTANCE_NAME`_DR_MASK)
    
    /* AMUX splitter cell control register masks */
    #define `$INSTANCE_NAME`_HSIOM_AMUXA_CONNECT                ((CYFLD_HSIOM_SWITCH_AA_SL__SIZE << CYFLD_HSIOM_SWITCH_AA_SL__OFFSET) | \
                                                                 (CYFLD_HSIOM_SWITCH_AA_SR__SIZE << CYFLD_HSIOM_SWITCH_AA_SR__OFFSET))
    #define `$INSTANCE_NAME`_HSIOM_AMUXB_CONNECT                ((CYFLD_HSIOM_SWITCH_BB_SL__SIZE << CYFLD_HSIOM_SWITCH_BB_SL__OFFSET) | \
                                                                 (CYFLD_HSIOM_SWITCH_BB_SR__SIZE << CYFLD_HSIOM_SWITCH_BB_SR__OFFSET))

    /* CSDv1 CTANK masks    */
    #define `$INSTANCE_NAME`_CTANK0_DR_VDDIO                    (0x0u)
    #define `$INSTANCE_NAME`_CTANK1_DR_VDDIO                    (0x0u)
    #define `$INSTANCE_NAME`_CTANK0_DR_VSSIO                    (`$INSTANCE_NAME`_DR_MASK << `$INSTANCE_NAME`_CSH0_SHIFT)
    #define `$INSTANCE_NAME`_CTANK1_DR_VSSIO                    (`$INSTANCE_NAME`_DR_MASK << `$INSTANCE_NAME`_CSH1_SHIFT)

    /* CSDv1 Set IDAC polarity */
    #if (`$INSTANCE_NAME`_CSD_IDAC_CONFIG == `$INSTANCE_NAME`_IDAC_SINKING)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY          (`$INSTANCE_NAME`_CONFIG_POLARITY_MASK)
        #define `$INSTANCE_NAME`_CSH0_DR_CONFIG                 (`$INSTANCE_NAME`_CTANK0_DR_VDDIO)
        #define `$INSTANCE_NAME`_CSH1_DR_CONFIG                 (`$INSTANCE_NAME`_CTANK1_DR_VDDIO)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY          (0u)
        #define `$INSTANCE_NAME`_CSH0_DR_CONFIG                 (`$INSTANCE_NAME`_CTANK0_DR_VSSIO)
        #define `$INSTANCE_NAME`_CSH1_DR_CONFIG                 (`$INSTANCE_NAME`_CTANK1_DR_VSSIO)
    #endif /* (`$INSTANCE_NAME`_CSD_IDAC_CONFIG == `$INSTANCE_NAME`_IDAC_SINKING) */
    
    /* Defining default CSD configuration according to settings in customizer. */
    #define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG            (`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_MASK |\
                                                             `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY |\
                                                             `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_DRV_MASK)

    #define `$INSTANCE_NAME`_CSD_ENABLE_MASK                (`$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)

    /* CSDv1 Defining mask intended for clearing bits related to pre-charging options. */
    #define `$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK          (`$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK  |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG          (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN   (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                             `$INSTANCE_NAME`_CSD_ENABLE_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                             `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)
    
    /* CSDv1 Ctank pre-charge mode configuration */
    #if (`$INSTANCE_NAME`_CSH_PRECHARGE_VREF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC)
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN)
            #define  `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG   (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)
        #else
            #define  `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG   (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK)
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) */
    #else
        #define  `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG       (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)
    #endif /* (`$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC == `$INSTANCE_NAME`__CSH_PRECHARGE_IO_BUF) */
    
    #if (`$INSTANCE_NAME`_CSH_PRECHARGE_VREF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC)
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN)
            #define  `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG   (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK)
        #else
            #define  `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG   (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK)
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) */
    #else
        #define  `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG       (`$INSTANCE_NAME`_DEFAULT_CSD_CONFIG |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_REFBUF_EN_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_MODE_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_PRS_CLEAR_MASK |\
                                                                `$INSTANCE_NAME`_CONFIG_COMP_PIN_MASK)
    #endif /* (`$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC == `$INSTANCE_NAME`__CSH_PRECHARGE_IO_BUF) */

    #define  `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG_CSD_EN    (`$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)
                                                                 
    #define  `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG_CSD_EN    (`$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG |\
                                                                 `$INSTANCE_NAME`_CONFIG_ENABLE_MASK |\
                                                                 `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_MASK)

    /* Set IDAC ranges */
    #if (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD0_IDAC_GAIN)
        #define `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_MOD_RANGE         (`$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_COMP_RANGE        (`$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_MOD_RANGE         (0u)
        #define `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_COMP_RANGE        (0u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD0_IDAC_GAIN) */
    #if (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD1_IDAC_GAIN)
        #define `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_MOD_RANGE         (`$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_COMP_RANGE        (`$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_MOD_RANGE         (0u)
        #define `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_COMP_RANGE        (0u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD1_IDAC_GAIN) */

    /* Defining default IDACs configuration according to settings in customizer. */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        #define `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_CONFIG        (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                  `$INSTANCE_NAME`_IDAC_COMP_MODE_FIXED |\
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_MOD_RANGE |\
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_COMP_RANGE)
        #define `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_CONFIG        (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                  `$INSTANCE_NAME`_IDAC_COMP_MODE_FIXED |\
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_MOD_RANGE |\
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_COMP_RANGE)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_CONFIG        (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_MOD_RANGE)
        #define `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_CONFIG        (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_MOD_RANGE)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

    /***************************************
    * API Constants
    ***************************************/

    #define `$INSTANCE_NAME`_CSH0_PRECHARGE_VREF                 (`$INSTANCE_NAME`_CSH_PRECHARGE_VREF)
    #define `$INSTANCE_NAME`_CSH0_PRECHARGE_IO_BUF               (`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF)
    #define `$INSTANCE_NAME`_CSH1_PRECHARGE_VREF                 (`$INSTANCE_NAME`_CSH_PRECHARGE_VREF)
    #define `$INSTANCE_NAME`_CSH1_PRECHARGE_IO_BUF               (`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF)
    
    #define `$INSTANCE_NAME`_CSD0_BLOCK_ID                       (0u)
    #define `$INSTANCE_NAME`_CSD1_BLOCK_ID                       (1u)
    
    #if (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD0_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD0_IDAC_GAIN_VALUE_NA         (2400u)
    #else
        #define `$INSTANCE_NAME`_CSD0_IDAC_GAIN_VALUE_NA         (1200u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD0_IDAC_GAIN) */

    #if (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD1_IDAC_GAIN)
        #define `$INSTANCE_NAME`_CSD1_IDAC_GAIN_VALUE_NA         (2400u)
    #else
        #define `$INSTANCE_NAME`_CSD1_IDAC_GAIN_VALUE_NA         (1200u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD0_IDAC_GAIN) */
 
    #define `$INSTANCE_NAME`_CSD_SHIELD_EN                       (`$INSTANCE_NAME`_CSD0_SHIELD_EN | `$INSTANCE_NAME`_CSD1_SHIELD_EN)
    
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */


#endif /* End CY_SENSE_`$INSTANCE_NAME`_SENSINGCSD_LL_H */


/* [] END OF FILE */
