/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingCSD_LL.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file defines the data structure global variables and provides
*   implementation for the low-level APIs of the CSD part of
*   the Sensing module. The file contains the APIs used for the CSD block
*   initialization, calibration, and scanning.
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
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_SensingCSD_LL.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)

/***************************************
* API Constants
***************************************/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN)
    #define `$INSTANCE_NAME`_CSD_AZ_ENABLE_CFG                  (`$INSTANCE_NAME`_CSD_AZ_EN_MASK)
#else
    #define `$INSTANCE_NAME`_CSD_AZ_ENABLE_CFG                  (0uL)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_AUTO_ZERO_EN) */

#if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
    #define `$INSTANCE_NAME`_HSCMP_SCAN_MASK                    (`$INSTANCE_NAME`_HSCMP_EN_MASK | `$INSTANCE_NAME`_CSD_AZ_ENABLE_CFG |\
                                                                 `$INSTANCE_NAME`_HSCMP_INVERT_MASK)
#else
    #define `$INSTANCE_NAME`_HSCMP_SCAN_MASK                    (`$INSTANCE_NAME`_HSCMP_EN_MASK | `$INSTANCE_NAME`_CSD_AZ_ENABLE_CFG)
#endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

#define `$INSTANCE_NAME`_HSCMP_INIT_MASK                        (`$INSTANCE_NAME`_HSCMP_EN_MASK | `$INSTANCE_NAME`_CSD_AZ_ENABLE_CFG)

#define `$INSTANCE_NAME`_DEFAULT_SW_SHIELD_SEL                  (0x00000000uL)
#define `$INSTANCE_NAME`_DEFAULT_CSD_SW_DSI_SEL                 (`$INSTANCE_NAME`_SW_DSI_SEL_CMODPAD | `$INSTANCE_NAME`_SW_DSI_SEL_TANKPAD)
#define `$INSTANCE_NAME`_DEFAULT_CSD_INTR_SET                   (0x00000000uL)
#define `$INSTANCE_NAME`_DEFAULT_SW_HS_P_SEL                    (0x00000000uL)
#define `$INSTANCE_NAME`_DEFAULT_SW_HS_N_SEL                    (0x00000000uL)
#define `$INSTANCE_NAME`_DEFAULT_CSD_SW_FW_TANK_SEL             (0x00000000uL)
#define `$INSTANCE_NAME`_DEFAULT_CSD_ADC_CTL                    (0x00000000uL)
#define `$INSTANCE_NAME`_DEFAULT_HSCMP_CFG                      (0x00000000uL)

#else

    /* Set IDAC ranges */
    #if (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD_IDAC_GAIN)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE         (`$INSTANCE_NAME`_IDAC_MOD_RANGE_MASK)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE        (`$INSTANCE_NAME`_IDAC_COMP_RANGE_MASK)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE         (0u)
        #define `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE        (0u)
    #endif /* (`$INSTANCE_NAME`_IDAC_GAIN_8X == `$INSTANCE_NAME`_CSD_IDAC_GAIN) */

    /* Defining default IDACs configuration according to settings in customizer. */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        #define `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG        (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                 `$INSTANCE_NAME`_IDAC_COMP_MODE_FIXED |\
                                                                 `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE |\
                                                                 `$INSTANCE_NAME`_DEFAULT_IDAC_COMP_RANGE)
    #else
        #define `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG        (`$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE |\
                                                                 `$INSTANCE_NAME`_DEFAULT_IDAC_MOD_RANGE)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

/***************************************
* Variables
***************************************/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    uint32 `$INSTANCE_NAME`_configCsd = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG;
#else
    uint32 `$INSTANCE_NAME`_configCsd = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG | `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
    static uint32 `$INSTANCE_NAME`_counterResolution = `$INSTANCE_NAME`_CNT_RESOLUTION_12_BITS;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

/* Flag to indicate electrodes that were connected previously */
static uint8 `$INSTANCE_NAME`_eleCsdDisconnectFlag = 0u;
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN))
    /* Number of re-samplings when the bad conversion occurs */
    uint8 `$INSTANCE_NAME`_badConversionsNum = `$INSTANCE_NAME`_BAD_CONVERSIONS_NUM;
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_NOISE_METRIC_EN)) */

#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    /* Stores IDAC and raw count that corresponds to a sensor with maximum Cp within a widget */
    uint8 `$INSTANCE_NAME`_calibratedIdac = 1u;
    uint16 `$INSTANCE_NAME`_calibratedRawcount = 1u;
    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        uint8 `$INSTANCE_NAME`_calibratedIdacRow = 1u;
        uint16 `$INSTANCE_NAME`_calibratedRawcountRow = 1u;
    #endif /*(`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
    static void `$INSTANCE_NAME`_SsSetShieldDelay(uint32 delay);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
        static void `$INSTANCE_NAME`_SsCSDEnableShieldTank(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
    #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
        static void `$INSTANCE_NAME`_SsCSDEnableShieldElectrodes(void);
    #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    static cystatus `$INSTANCE_NAME`_SsCSDCalibrateCheck(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt, uint32 rawLevel, uint32 rawData);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        static void `$INSTANCE_NAME`_SsCSDSetSingleIdacMode(void);
        static void `$INSTANCE_NAME`_SsCSDRestoreIdacMode(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    static cystatus `$INSTANCE_NAME`_SsCSDCalibrateOneSensor(uint32 rawLevel,
                                                             uint8 *ptrIdac,
                                                             uint8 *iDAC8Max);
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))  */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    static void `$INSTANCE_NAME`_SsCSDSetFilterDelay(void);
#else
    CY_INLINE static void `$INSTANCE_NAME`_SsCSDClockRestart(void);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
CY_INLINE static void `$INSTANCE_NAME`_SsCSDCmodPrecharge(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSDTriggerScan(void);
static void `$INSTANCE_NAME`_SsCSDConfigIDACs(void);
static void `$INSTANCE_NAME`_SsCSDSetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider);

/** \}
* \endcond */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsSetShieldDelay
    ****************************************************************************//**
    *
    * \brief
    *   This is an internal function that sets a shield delay.
    *
    * \details
    *   The function updates the CSD configuration register bits that define the shield
    *   signal delay relatively to the sense signal.
    *
    * \param delay
    *   Specifies the shield delay value:
    *    PSoC 4100/4200 value interpretation:
    *         0 - no delay
    *         1 - 1 cycle of HFCLK
    *         2 - 2 cycles of HFCLK
    *    Third-generation HW block (except 4100/4200 devices):
    *         0 - no delay
    *         3 - 10ns delay
    *         2 - 50ns delay
    *    Fourth-generation HW block:
    *         0 - no delay
    *         1 - 5ns delay
    *         2 - 10ns delay
    *         3 - 20ns delay
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsSetShieldDelay(uint32 delay)
    {
        /* Update CSD config register shield delay bits with shield delay value */
        `$INSTANCE_NAME`_configCsd &= (uint32)(~`$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK);
        `$INSTANCE_NAME`_configCsd |= (delay << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT);
    }

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDEnableShieldTank
        ****************************************************************************//**
        *
        * \brief
        *   This function configures Csh pin
        *
        * \details
        *   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
        *   For Third-generation HW block it additionally sets Strong drive mode for Csh
        *   and applies High level to Csh pin when precharge is set to IO buffer.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSDEnableShieldTank(void)
        {
            uint32 newRegValue;

            /* Update the CSH_HSIOM register to connect Csh to AMUXBUS-B */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
            newRegValue |= (`$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT);
            CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, newRegValue);

            #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
                 (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                /* Set Strong drive mode for Csh */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR);
                newRegValue &= (uint32)(~(`$INSTANCE_NAME`_CSH_PC_MASK << `$INSTANCE_NAME`_CSH_PC_SHIFT));
                newRegValue |= (`$INSTANCE_NAME`_CSH_PC_STRONG_MODE << `$INSTANCE_NAME`_CSH_PC_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR, newRegValue);

                /* Appliy High level to Csh pin for Csh */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_DR_PTR);
                newRegValue &= (uint32)(~(`$INSTANCE_NAME`_DR_MASK << `$INSTANCE_NAME`_CSH_SHIFT));
                newRegValue |= (uint32)`$INSTANCE_NAME`_CSH_DR_CONFIG;
                CY_SET_REG32(`$INSTANCE_NAME`_CSH_DR_PTR, newRegValue);
            #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
                       (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */

    #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDEnableShieldElectrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function initializes Shield Electrodes.
        *
        * \details
        *   The function sets the bit in the HSIOM register which enables the shield electrode
        *   functionality on the pin. The port and pin configurations are stored in
        *   the `$INSTANCE_NAME`_shieldIoList structure.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSDEnableShieldElectrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Set drive mode to Analog */
                CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr, CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr) &
                           ~(`$INSTANCE_NAME`_GPIO_PC_MASK <<(`$INSTANCE_NAME`_shieldIoList[shieldIndex].shift)));

                /* Set HSIOM register mode to CSD_SHIELD or AMUXBUS B connection */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr);
                newRegValue &= ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << (`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomShift));

                /* Set HSIOM register mode to CSD_SHIELD */
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD << (`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomShift));

                CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr, newRegValue);
            }
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDDisableShieldElectrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function disables Shield Electrodes.
        *
        * \details
        *   The function resets the bit in the HSIOM register which disables the shield
        *   electrode functionality on the pin. The port and pin configurations are
        *   stored in  the `$INSTANCE_NAME`_shieldIoList structure.
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_SsCSDDisableShieldElectrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Reset HSIOM register (to GPIO state) */
                CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr, CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr) &
                             (uint32)~(uint32)(`$INSTANCE_NAME`_HSIOM_SEL_MASK << `$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomShift));

                /* Update port configuration register (drive mode to ground)  */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr);
                newRegValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_shieldIoList[shieldIndex].shift);
                newRegValue |= (`$INSTANCE_NAME`_SNS_GROUND_CONNECT << `$INSTANCE_NAME`_shieldIoList[shieldIndex].shift);
                CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr, newRegValue);

                /* Set logic 0 to port data register */
                CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].drPtr, CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].drPtr) &
                           (uint32)~(uint32)((uint32)1u << `$INSTANCE_NAME`_shieldIoList[shieldIndex].drShift));
            }
        }
    #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDSetModeSnsClockDivider
****************************************************************************//**
*
* \brief
*   Sets sense source and Sense Clock Divider
*
* \details
*   For Fourth-generation HW block: Updates `$INSTANCE_NAME`_SENSE_PERIOD register with
*   sense source and Sense Clock Divider.
*   For Third-generation HW block: Updates `$INSTANCE_NAME`_configCsd variable with
*   sense source and sets sense clock divider.
*
* \param
*   snsClkSource The sense source for the sense clock.
* \param
*   snsClkDivider The divider value for the sense clock.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSDSetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* Update reg value with divider and configuration */
        CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR, snsClkSource | (snsClkDivider - 1u));
    #else
        /* Set configuration */
        `$INSTANCE_NAME`_configCsd &= ~(`$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK | `$INSTANCE_NAME`_CSD_PRS_12_BIT);
        `$INSTANCE_NAME`_configCsd |= snsClkSource;

        /* Set sense clock divider */
        `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDSetFilterDelay
    ****************************************************************************//**
    *
    * \brief
    *   Sets the filter delay for Fourth-generation HW block.
    *
    * \details
    *   This function updates Fourth-generation HW block configuration
    *   variable `$INSTANCE_NAME`_configCsd
    *   with the filter delay which depends on the sample clock frequency.
    *   This variable is written into register during enabling
    *   Fourth-generation HW block .
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSDSetFilterDelay(void)
    {
        #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
            uint32 sampleClkFreqHz;
        #endif /* (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */

        `$INSTANCE_NAME`_configCsd &= ~`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_MASK;

        #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
            sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)`$INSTANCE_NAME`_dsRam.modCsdClk;
            if(sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
            {
                `$INSTANCE_NAME`_configCsd |= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ;
            }
            else if(sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
            {
                `$INSTANCE_NAME`_configCsd |= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_24MHZ;
            }
            else
            {
                `$INSTANCE_NAME`_configCsd |= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_48MHZ;
            }
        #else
            `$INSTANCE_NAME`_configCsd |= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ;
        #endif /* (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDConfigIDACs
****************************************************************************//**
*
* \brief
*   Configures the mode for IDAC registers
*
* \details
*   This function configures the IDAC modes depend on Compensation IDAC
*   enabled or disabled.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSDConfigIDACs(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, `$INSTANCE_NAME`_IDAC_MOD_DEFAULT_CFG);
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
        CY_SET_REG32(`$INSTANCE_NAME`_IDACB_PTR, `$INSTANCE_NAME`_IDAC_COMP_DEFAULT_CFG);
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                   (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */
    #else
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR) &
                                                                ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK |
                                                                  `$INSTANCE_NAME`_IDAC_MOD_MASK));
            CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR) |
                                                                 `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDInitialize
****************************************************************************//**
*
* \brief
*   This API initializes the CSD module.
*
* \details
*   The function performs the following steps for Fourth-generation HW block:
*   1) Sets GPIO output to "0" for all sensor pins;
*   2) Connects CMOD to AMUXBUS-A and to CSDBUS-A;
*   3) Connects CMOD to (sense path) to CSDCOMP;
*   4) Connects Csh_tank to AMUXBUS-B and to CSDBUS-B;
*   5) Connects VREF to REFGEN;
*   6) Configures REFGEN and sets the reference voltage;
*   7) Connects VREF to CSDCOMP and HSCOMP;
*   8) Configures IDAC and connect to CSDBUS-A (to drive CMOD);
*   9) Configures ModClk;
*   10) Configure SnsClk source;
*   11) Sets other CSD configurations (Csd Auto Zero time,
*       Sample Init period, interrupts,
*       CMOD and Csh_tank/shield initialization switch resistance).
*
*   The function performs the following steps for Third-generation HW block:
*   1) Sets all the sensors to the inactive state;
*   2) Enables Shield Electrodes;
*   3) Configures the CSD block and IDACs;
*   4) Connects Cmod to AMUXBUS-A;
*   5) Enables the clocks;
*   6) Sets the shield delay;
*   7) Enables the CSD block; connects Vref Buffer to the AMUX bus.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDInitialize(void)
{
    uint32 newRegValue;

    /* Set all the sensors to inactive state */
    `$INSTANCE_NAME`_SsClearCSDSensors();

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        `$INSTANCE_NAME`_BistDischargeExtCapacitors();
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        /* Connect shields to AMUX-B bus (config HSIOM regs) */
        #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
            `$INSTANCE_NAME`_SsCSDEnableShieldElectrodes();
        #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
            /* Configure Csh */
            `$INSTANCE_NAME`_SsCSDEnableShieldTank();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

        /* Initialize the unused CSD registers to defaut state */
        CY_SET_REG32(`$INSTANCE_NAME`_SENSE_DUTY_PTR,       `$INSTANCE_NAME`_DEFAULT_SENSE_DUTY_SEL);

        /* Configure VREF */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
        newRegValue |= `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL;

        CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR, newRegValue);
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_SET_PTR,         `$INSTANCE_NAME`_DEFAULT_CSD_INTR_SET);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_DEFAULT_CSD_SW_FW_TANK_SEL);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_DEFAULT_CSD_SW_DSI_SEL);
        CY_SET_REG32(`$INSTANCE_NAME`_ADC_CTL_PTR,          `$INSTANCE_NAME`_DEFAULT_CSD_ADC_CTL);
        CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR,            `$INSTANCE_NAME`_AMBUF_PWR_MODE_OFF);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_SW_SHIELD_SEL);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_SW_HS_P_SEL);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_SW_HS_N_SEL);
        CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR,            `$INSTANCE_NAME`_DEFAULT_HSCMP_CFG);

        /* Connect CMOD to AMUXBUS-A */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
        newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT);
        CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);

        /* Connect AMUXBUS-A to CSDBUS-A */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR);
        newRegValue |= `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYA_MASK;
        CY_SET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR, newRegValue);

        /* Connect CMOD to (sense path) to CSDCOMP */
        #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE);
        #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
            CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE);
        #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */

        /* Configure shield driving path */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Connect AMUXBUS-B to CSDBUS-B (and AMUXBUS-A to CSDBUS-A ) */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR, `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYA_MASK | `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYB_MASK);

        /* Connect AMUXBUS-B to HSCMP positive input */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, 0x00000000uL);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        /* Configure VREF */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)
            /* Connect VREF to REFGEN. Connect IDACB to CSDBUSA */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
            newRegValue |= `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK | `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_IAIB_MASK;
            CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR, newRegValue);
        #else
            /* Connect VREF to REFGEN (IAIB switch is open) */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
            newRegValue |= `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK;
            CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR, newRegValue);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN */

    #if (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV)

        /* Connect VREFLOW (from AMBUF and RefGen is in bypass mode) to CSDCOMP when Vdda < 2 V */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        /* Configure REFGEN. Set reference voltage when Vdda < 2 V */
        CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR, `$INSTANCE_NAME`_REFGEN_LV);

        /* Connect Vrefhi to AMUBUF positive input when Vdaa < 2V
         *  Connect AMUBUF to SCDCMP negative input when Vdaa < 2V
         */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
                CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                      `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_PHI2);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_DEFAULT);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
            CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR, `$INSTANCE_NAME`_AMBUF_PWR_MODE_NORM);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR, `$INSTANCE_NAME`_AMBUF_PWR_MODE_OFF);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        /* Connect VREFHI to HSCOMP */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
    #else

        /* Connect VREFHI (from RefGen) to CSDCOMP when Vdda >= 2 V */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        /* Configure REFGEN. Set reference voltage when Vdda >= 2 V */
        CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR, `$INSTANCE_NAME`_REFGEN_HV);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Turn on CSD_AMBUF high power level when Vdaa >= 2V */
            CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR, `$INSTANCE_NAME`_AMBUF_PWR_MODE_HI);

            #if (`$INSTANCE_NAME`_IDAC_SINKING != `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
                CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                      `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_PHI2);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_DEFAULT);
            #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_DEFAULT);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        /* Connect VREFHI to HSCOMP */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
    #endif /* (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV) */

    /* Configure IDACs mode */
    `$INSTANCE_NAME`_SsCSDConfigIDACs();

        /* Configure ModClk */
        `$INSTANCE_NAME`_SsSetModClkClockDivider((uint32)`$INSTANCE_NAME`_dsRam.modCsdClk);

    /* Set other CSD configurations */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        `$INSTANCE_NAME`_SsSetShieldDelay(`$INSTANCE_NAME`_CSD_SHIELD_DELAY);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

    /* Configure HW block filter delay */
    `$INSTANCE_NAME`_SsCSDSetFilterDelay();

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
        /* Enable power to sub-blocks */
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd |
                                                  `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |
                                                  `$INSTANCE_NAME`_CONFIG_ENABLE_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Set Csd Auto Zero time (set AZ_TIME bitmask) */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_TIME_PTR, `$INSTANCE_NAME`_CSD_AUTO_ZERO_TIME);

        /* Select CMOD and Csh_tank/shield initialization switch resistance */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR, 0x00000000);

        /* Set the number of dummy fine initialization cycles */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_INIT_CNT_PTR, `$INSTANCE_NAME`_CSD_FINE_INIT_TIME);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)

        /* Configure IDACs mode */
        `$INSTANCE_NAME`_SsCSDConfigIDACs();

        /* Connect Cmod to AMUXBUS-A using HSIOM registers */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
        newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT);
        CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            `$INSTANCE_NAME`_SsSetShieldDelay(`$INSTANCE_NAME`_CSD_SHIELD_DELAY);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        /* Enable CSD block. Connect Vref Buffer to AMUX bus to make sure that Cmod is charged before scanning in active mode */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd | `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) &&\
         (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
         /* Set clock dividers and clock source mode */
        `$INSTANCE_NAME`_SsCSDConfigClock();
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) &&\
               (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDElectrodeCheck
****************************************************************************//**
*
* \brief
*   Checks if electrodes were previously connected using
 * `$INSTANCE_NAME`_CSDSetupWidgetExt() API and if yes disconnects them.
*
* \details
*   This function checks if `$INSTANCE_NAME`_eleCsdDisconnectFlag is set.
*   If it set, the function disconnects the previously connected electrode.
*   The previous IO is contained in `$INSTANCE_NAME`_curSnsIOPtr and
*   `$INSTANCE_NAME`_curFlashSnsPtr contains the previous data for Ganged
*   sensors.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDElectrodeCheck(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_eleCsdDisconnectFlag)
    {
        /* Disconnect if electrodes were previous connected by CSDSetupWidgetExt() API */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            /* Check ganged sns flag  */
            if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_curFlashWdgtPtr->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
            {
                /* Get number of ganged pins */
                tempVal = `$INSTANCE_NAME`_curFlashSnsPtr->numPins;

                /* Get IO pointer  */
                `$INSTANCE_NAME`_curSnsIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curFlashSnsPtr->firstPinId];

                /* Disconnect all ganged sensors */
                do
                {
                    `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
                    `$INSTANCE_NAME`_curSnsIOPtr++;
                    tempVal--;
                } while (0u != tempVal);
            }
            else
            {
                /* Disconnect ganged sensor */
                `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
            }
        #else
            /* Disable sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

        `$INSTANCE_NAME`_eleCsdDisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDSetUpIdacs
****************************************************************************//**
*
* \brief
*  This internal function changes the IDACs values.
*
* \details
*  If Compensation IDAC is enabled, it updates two IDACs.
*  The Modulator IDAC is common for all the sensors of the widget.
*  The Compensation IDAC is updated for the sensor of the widget which
*  is available in the RAM_SNS_STRUCT structure.
*  If the Compensation IDAC is disabled, the function updates the Modulator IDAC
*  value only in the RAM_WD_BASE_STRUCT structure.
*
* \param
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDSetUpIdacs(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt)
{

    uint8 interruptState;

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    uint32 idacARegValue;
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
        uint32 idacBRegValue;
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */

    interruptState = CyEnterCriticalSection();

    /* Get IDACA Value */
    idacARegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR);

    /* Set IDACA Value mask */
    idacARegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_VAL_MASK);

    /* Set IDACA value */
    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex)].numCols <= `$INSTANCE_NAME`_sensorIndex)
        {
            idacARegValue |= (uint32)ptrWdgt->rowIdacMod[`$INSTANCE_NAME`_scanFreqIndex];
        }
        else
        {
            idacARegValue |= (uint32)ptrWdgt->idacMod[`$INSTANCE_NAME`_scanFreqIndex];
        }
    #else
        idacARegValue |= (uint32)ptrWdgt->idacMod[`$INSTANCE_NAME`_scanFreqIndex];
    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    /* Update IDACA register with new value */
    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, idacARegValue);
    CyExitCriticalSection(interruptState);

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))
        interruptState = CyEnterCriticalSection();
        /* Get IDACB Value */
        idacBRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR);

        /* Set IDACB Value mask */
        idacBRegValue &= ~(`$INSTANCE_NAME`_IDAC_COMP_VAL_MASK);

        /* Set IDACB value */
        idacBRegValue |= (uint32)`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_scanFreqIndex];

        /* Update IDACA register with new value */
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR, idacBRegValue);
        CyExitCriticalSection(interruptState);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)) */

#else

    uint32 newRegValue;
    uint8 const *ptrIdacMod = ptrWdgt->idacMod;

    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN  | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex)].numCols <= `$INSTANCE_NAME`_sensorIndex)
        {
            ptrIdacMod = &ptrWdgt->rowIdacMod[0u];
        }
    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN  | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    interruptState = CyEnterCriticalSection();

    /* Get Idac Value */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR);

    /* Set Idac Value mask */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        newRegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_MASK | `$INSTANCE_NAME`_IDAC_COMP_MASK);
    #else
        newRegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

    /* Set Idac value */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        newRegValue |= (ptrIdacMod[`$INSTANCE_NAME`_scanFreqIndex] |
                       (uint32)((uint32)`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_scanFreqIndex] <<
                       `$INSTANCE_NAME`_IDAC_COMP_DATA_OFFSET));
    #else
        newRegValue |= ptrIdacMod[`$INSTANCE_NAME`_scanFreqIndex];
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, newRegValue);

    CyExitCriticalSection(interruptState);

#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDGetNumberOfConversions
    ****************************************************************************//**
    *
    * \brief
    *  This function gets Number of conversions.
    *
    * \details
    *  This function gets Number of conversions using foll.owing equation:
    *   conversionsNum = (2^resolution - 1) / snsClkDivider.
    *
    * \param
    *  snsClkDivider The divider value for the sense clock.
    *  resolution The widget resolution.
    *  snsClkSrc The current Sense Clock Source.
    *
    * \return Returns the Number of conversions.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_SsCSDGetNumberOfConversions(uint32 snsClkDivider, uint32 resolution, uint32 snsClkSrc)
    {
        uint32 conversionsNum;
        #if ((`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) && (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN))
            uint32 sampleClkFreqHz;
        #endif /* ((`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) && (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN)) */

        /* Calculate scanning resolution value in register */
        conversionsNum = (uint32)((1uL << resolution) - 1uL);

        #if(`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN)
            /* Apply correction to oveflow for 16 bit resolution */
            if (`$INSTANCE_NAME`_RES16BIT == resolution)
            {
                conversionsNum -= ((snsClkDivider + 1u) >> 1u);

                #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
                    sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)`$INSTANCE_NAME`_dsRam.modCsdClk;

                    if (sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
                    {
                        conversionsNum -= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES;
                    }
                    else if (sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
                    {
                        conversionsNum -= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_3_CYCLES;
                    }
                    else
                    {
                        conversionsNum -= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_4_CYCLES;
                    }
                #else
                    conversionsNum -= `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_2_CYCLES;
                #endif /* (INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN) */

        if (0u < snsClkDivider)
        {
            conversionsNum /= snsClkDivider;
        }

    #if((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
        (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
        (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
        switch (snsClkSrc)
        {
            case `$INSTANCE_NAME`_CLK_SOURCE_PRS8:
            case `$INSTANCE_NAME`_CLK_SOURCE_PRS12:
                /* Divide by 2 for PRS8/PRS12 mode */
                conversionsNum >>= 1u;
                break;

            default:
                break;
        }
    #endif /* ((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
               (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
               (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */

    return((conversionsNum > 0uL) ? (conversionsNum) : 1uL);
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDConfigClock
****************************************************************************//**
*
* \brief
*  This function configure sense clock for different modes.
*
* \details
*  Function sets the clock divider and configures the mode based on configuration.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDConfigClock(void)
{
    uint32 snsClkDivider;
    uint32 snsClkSrc;
    uint32 newRegValue;

    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
             `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2WdgtRam;

    /* Get sense divider based on configuration */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = (uint32)`$INSTANCE_NAME`_dsRam.snsCsdClk;
    #else
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            /* Get SnsClck divider for rows or columns */
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].numCols <= `$INSTANCE_NAME`_sensorIndex)
            {
                snsClkDivider = (uint32)(ptrWdgt->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt->snsClk);
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

    /* Get sense clk source calculated in `$INSTANCE_NAME`_SsCSDInitialize() before */
    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        /* Get SnsClc Source for rows or columns */
        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].numCols <= `$INSTANCE_NAME`_sensorIndex)
        {
            snsClkSrc = (uint32)ptrWdgt->rowSnsClkSource;
        }
        else
        {
            snsClkSrc = (uint32)ptrWdgt->snsClkSource;
        }
    #else
        snsClkSrc = (uint32)ptrWdgt->snsClkSource;
    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        newRegValue = (snsClkSrc << CYFLD_CSD_LFSR_SIZE__OFFSET);

        /* Configuring PRS SEL_BIT */
        if ((`$INSTANCE_NAME`_CLK_SOURCE_PRS8 == snsClkSrc) ||
            (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == snsClkSrc))
        {
            newRegValue |= `$INSTANCE_NAME`_SENSE_PERIOD_SEL_LFSR_MSB_MASK;
        }
    #else
        newRegValue = snsClkSrc;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    #if((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
        (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
        (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
        switch (snsClkSrc)
        {
        case `$INSTANCE_NAME`_CLK_SOURCE_PRS8:
        case `$INSTANCE_NAME`_CLK_SOURCE_PRS12:
            /* Divide by 2 for PRS8/PRS12 mode */
            snsClkDivider >>= 1;
            if (snsClkDivider == 0u)
            {
                snsClkDivider = 1u;
            }
            break;

        default:
            break;
        }
    #endif /* ((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
               (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
               (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */
    `$INSTANCE_NAME`_SsCSDSetModeSnsClockDivider(newRegValue, snsClkDivider);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDCalculateScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by scan resolution
*
* \details
*   For Fourth-generation HW block: The function calculates the number of conversions and updates
*   SEQ_NORM_CNT register. The number of conversions depends on resolution and
*   snsClk divider.
*   For Third-generation HW block: The function recalculate the resolution using following equation:
*   2^resolution - 1. The calculated value is contained in
*   `$INSTANCE_NAME`_counterResolution global variable and used in
*   `$INSTANCE_NAME`_SsCSDStartSample() function to trigger the scan process.
*
* \param wdgtIndex
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDCalculateScanDuration(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        uint32 conversionsNum;
        uint32 snsClkDivider;

    /* Get Number Of Conversions */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = `$INSTANCE_NAME`_dsRam.snsCsdClk;
    #else
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            /* Get SnsClck divider for rows or columns */
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].numCols <= `$INSTANCE_NAME`_sensorIndex)
            {
                snsClkDivider = (uint32)(ptrWdgt->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt->snsClk);
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

    conversionsNum = `$INSTANCE_NAME`_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution, (uint32)ptrWdgt->snsClkSource);

        /* Set Number Of Conversions based on scanning resolution */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_NORM_CNT_PTR, (conversionsNum & `$INSTANCE_NAME`_SEQ_NORM_CNT_CONV_CNT_MASK));
    #else
        /* Set up scanning resolution  */
        `$INSTANCE_NAME`_counterResolution = (uint32)((0x00000001Lu << ptrWdgt->resolution) - 1u) << `$INSTANCE_NAME`_RESOLUTION_OFFSET;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDSetupWidget
****************************************************************************//**
*
* \brief
*  Performs hardware and firmware initialization required for scanning sensors
*  in a specific widget using the CSD sensing method. This function requires using
*  the `$INSTANCE_NAME`_CSDScan() function to start scanning.
*
* \details
*  This function initializes the specific widget common parameters to perform
*  the CSD scanning. The initialization includes setting up a Modulator and
*  Sense clock frequency and scanning resolution.
*
*  This function does not connect any specific sensors to the scanning hardware,
*  neither does it start a scanning process. The `$INSTANCE_NAME`_CSDScan()
*  API must be called after initializing the widget to start scanning.
*
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  This function is called by the `$INSTANCE_NAME`_SetupWidget() API if the
*  given widget uses the CSD sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param  widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning sensors in the specific widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDSetupWidget(uint32 widgetId)
{

    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                                    `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

    /* Save widget Id to have assess to it after scanning  */
    `$INSTANCE_NAME`_widgetIndex = (uint8)widgetId;

    `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_CSD_E);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

    /* Disconnect previous electrode if it has been connected */
    `$INSTANCE_NAME`_SsCSDElectrodeCheck();

    /* Initialize IO Sns electrode structure pointer to current widget */
    `$INSTANCE_NAME`_curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                    `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsFlash;

    /* Update status register in Data structure */
    `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_WDGT0_MASK;
    `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_widgetIndex;

    /* Set up scanning resolution (Number ofconversion for CSDv2) */
    `$INSTANCE_NAME`_SsCSDCalculateScanDuration(ptrWdgt);

    #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) ||\
         (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
        `$INSTANCE_NAME`_SsCSDConfigClock();
    #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) ||\
               (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDSetupWidgetExt
****************************************************************************//**
*
* \brief
*  Performs extended initialization for the CSD widget and also performs
*  initialization required for a specific sensor in the widget. This function
*  requires using the `$INSTANCE_NAME`_CSDScanExt() function to initiate a scan.
*
* \details
*  This function does the same as `$INSTANCE_NAME`_CSDSetupWidget() and also
*  does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the IDAC value.
*    3. Initializes an interrupt callback function to initialize a scan of the
*  next sensors in a widget.
*
*  Once this function is called to initialize a widget and a sensor, the
*  `$INSTANCE_NAME`_CSDScanExt() function is called to scan the sensor.
*
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning the specific sensor in the specific
*  widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget to perform hardware
*  and firmware initialization required for scanning a specific sensor in a
*  specific widget.
*  A macro for the sensor ID within a specified widget can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDSetupWidgetExt(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                                    `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

    /* Save widget and sensor Ids to have access to it after scanning  */
    `$INSTANCE_NAME`_sensorIndex = (uint8)sensorId;

    /* Update global pointer to `$INSTANCE_NAME`_RAM_SNS_STRUCT to current sensor  */
    `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                                              `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam
                                              + `$INSTANCE_NAME`_sensorIndex;

    `$INSTANCE_NAME`_CSDSetupWidget(widgetId);

     /* Setup Idac Value */
    `$INSTANCE_NAME`_SsCSDSetUpIdacs(ptrWdgt);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* initialize access pointers for current pointer to widget configuration in Flash */
        `$INSTANCE_NAME`_curFlashWdgtPtr = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        `$INSTANCE_NAME`_SsCSDConnectSensorExt(widgetId, sensorId);
    #else
        /* Enable sensor */
        `$INSTANCE_NAME`_curSnsIOPtr += `$INSTANCE_NAME`_sensorIndex;
        `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* Save sns pointer */
        `$INSTANCE_NAME`_curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                           `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsFlash +
                                           `$INSTANCE_NAME`_sensorIndex;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    `$INSTANCE_NAME`_eleCsdDisconnectFlag = `$INSTANCE_NAME`_DISCONNECT_IO_FLAG;

    /* Setup ISR handler to single-sensor scan function */
    `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_CSDPostSingleScan);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDStartSample
****************************************************************************//**
*
* \brief
*   Starts the CSD conversion.
*
* \details
*   This function assumes that the CSD block is already set up using
*   the `$INSTANCE_NAME`_CSDSetupWidget API and the sensor port-pin is connected to the CSD
*   block using `$INSTANCE_NAME`_CSDConnectSns.
*   For Third-generation HW block the function performs the following tasks:
*   1. Disconnects the Vref buffer from AMUX;
*   2. Precharges Cmod;
*   3. Makes the PreSettling delay to have a stable Vref voltage;
*   4. Sets the resolution to the Counter register to start scanning.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDStartSample(void)
{
    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2)
        uint8 interruptState;
    #endif

    #ifdef `$INSTANCE_NAME`_START_SAMPLE_CALLBACK
        `$INSTANCE_NAME`_StartSampleCallback(`$INSTANCE_NAME`_widgetIndex, `$INSTANCE_NAME`_sensorIndex);
    #endif /* `$INSTANCE_NAME`_START_SAMPLE_CALLBACK */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* Fourth-generation HW block section */

        /* Disable CSD interrupt to prevent it during coarse initialization */
        CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

        /* Enable power to sub-blocks */
        CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, `$INSTANCE_NAME`_HSCMP_INIT_MASK);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd |
                                                      `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |
                                                      `$INSTANCE_NAME`_CONFIG_ENABLE_MASK);
            #if(`$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US > 0uL)
                CyDelayUs(`$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US);
            #endif /* (`$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US > 0uL) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Precharging Cmod and Csh */
        `$INSTANCE_NAME`_SsCSDCmodPrecharge();

        /* Trigger Scan */
        `$INSTANCE_NAME`_SsCSDTriggerScan();

    #else
        /* Third-generation HW block section */
        interruptState = CyEnterCriticalSection();

        /* Enable CSD block. Disconnect Vref Buffer from AMUX */
        #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd | `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd | `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
                   (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        /* Restart the clocks. Scan one cycle to reset the flip-flop for Direct clock mode */
        `$INSTANCE_NAME`_SsCSDClockRestart();

        /* Precharging Cmod to Vref */
        `$INSTANCE_NAME`_SsCSDCmodPrecharge();

        #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
            /* Set PreSettling delay to skip IDAC glitch before scanning */
            CyDelayCycles(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES);
        #endif /* (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE != `$INSTANCE_NAME`_CLK_SOURCE_DIRECT) */

        /* Trigger Scan */
        `$INSTANCE_NAME`_SsCSDTriggerScan();

        CyExitCriticalSection(interruptState);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDScanExt
****************************************************************************//**
*
* \brief
*  Starts the CSD conversion on the preconfigured sensor. This function requires
*  using the `$INSTANCE_NAME`_CSDSetupWidgetExt() function to set up the a
*  widget.
*
* \details
*  This function performs single scanning of one sensor in the widget configured
*  by the `$INSTANCE_NAME`_CSDSetupWidgetExt() function. It does the following
*  tasks:
*    1. Sets the busy flag in the `$INSTANCE_NAME`_dsRam structure.
*    2. Performs the clock-phase alignment of the sense and modulator clocks.
*    3. Performs the Cmod pre-charging.
*    4. Starts single scanning.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  The sensor must be preconfigured by using the
*  `$INSTANCE_NAME`_CSDSetupWidgetExt() API prior to calling this function.
*  The sensor remains ready for a next scan if a previous scan was triggered
*  by using the `$INSTANCE_NAME`_CSDScanExt() function. In this case, calling
*  `$INSTANCE_NAME`_CSDSetupWidgetExt() is not required every time before the
*  `$INSTANCE_NAME`_CSDScanExt() function. If a previous scan was triggered in
*  any other way - `$INSTANCE_NAME`_Scan(), `$INSTANCE_NAME`_ScanAllWidgets() or
*  `$INSTANCE_NAME`_RunTuner() - (see the `$INSTANCE_NAME`_RunTuner() function
*  description for more details), the sensor must be preconfigured again by
*  using the `$INSTANCE_NAME`_CSDSetupWidgetExt() API prior to calling the
*  `$INSTANCE_NAME`_CSDScanExt() function.
*
*  If disconnection of the sensors is required after calling
*  `$INSTANCE_NAME`_CSDScanExt(), the `$INSTANCE_NAME`_CSDDisconnectSns()
*  function can be used.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDScanExt(void)
{
    /* Set Start of sensor scan flag */
    `$INSTANCE_NAME`_dsRam.status |= (`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_WDGT_SW_STS_BUSY);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) &&\
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        #if(`$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US > 0uL)
            CyDelayUs(`$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US);
        #endif /* (`$INSTANCE_NAME`_CSD_ANALOG_STARTUP_DELAY_US > 0uL) */
    #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) &&\
              (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)*/

    `$INSTANCE_NAME`_SsCSDStartSample();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDScan
****************************************************************************//**
*
* \brief
*  This function initiates a scan for the sensors of the widget initialized by the
*  `$INSTANCE_NAME`_CSDSetupWidget() function.
*
* \details
*  This function performs scanning of all the sensors in the widget configured by
*  the `$INSTANCE_NAME`_CSDSetupWidget() function. It does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Configures the IDAC value.
*    3. Initializes the interrupt callback function to initialize a scan of
*       the next sensors in a widget.
*    4. Starts scanning for the first sensor in the widget.
*
*  This function is called by the `$INSTANCE_NAME`_Scan() API if the given
*  widget uses the CSD sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status. The widget must be
*  preconfigured by the `$INSTANCE_NAME`_CSDSetupWidget() function if any other
*  widget was previously scanned or any other type of the scan functions was used.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDScan(void)
{
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                                    `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2WdgtRam;

     /*
      * Update `$INSTANCE_NAME`_sensorIndex with the first sensor in
      * widget to use it in ISR handler to configure the next sensor
      */
    `$INSTANCE_NAME`_sensorIndex = 0u;

    /* Update global pointer to `$INSTANCE_NAME`_RAM_SNS_STRUCT to current sensor  */
    `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                                              `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsRam
                                              + `$INSTANCE_NAME`_sensorIndex;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Reset the frequency scan channel if enabled */
        `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

    /* Setup Idac Value */
   `$INSTANCE_NAME`_SsCSDSetUpIdacs(ptrWdgt);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].staticConfig &
            `$INSTANCE_NAME`_GANGED_SNS_MASK))
        {
            /* Setup ISR handler to multiple-sensor scan function with ganged sensors */
            `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_CSDPostMultiScanGanged);
        }
        else
        {
            /* Set up ISR handler to multiple-sensor scan function without ganged sensors */
            `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_CSDPostMultiScan);
        }

        `$INSTANCE_NAME`_SsCSDConnectSensorExt((uint32)`$INSTANCE_NAME`_widgetIndex, (uint32)`$INSTANCE_NAME`_sensorIndex);
    #else
        /* initialize ptr to sensor IO structure to appropriate address */
        `$INSTANCE_NAME`_curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsFlash
                                        + `$INSTANCE_NAME`_sensorIndex;

        /* Enable sensor */
        `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr);

        /* Set-up ISR handler to multiple-sensor scan function without ganged sensors */
        `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_CSDPostMultiScan);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

    /* Start scanning */
    `$INSTANCE_NAME`_CSDScanExt();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDConnectSensorExt
****************************************************************************//**
*
* \brief
*  Connects a ganged sensor port-pin to the sensing HW block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and
*   PC registers.
*
* \param widgetId
*  Specifies ID of the widget.
*
* \param sensorId
*  Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDConnectSensorExt(uint32 widgetId, uint32 sensorId)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    /* initialize ptr to sensor IO structure to appropriate address */
    `$INSTANCE_NAME`_curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                      `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash
                                                      + sensorId;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (`$INSTANCE_NAME`_GANGED_SNS_MASK ==
           (`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].staticConfig &
            `$INSTANCE_NAME`_GANGED_SNS_MASK))
        {
            /* Get sns pointer */
            `$INSTANCE_NAME`_curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash +
                                               sensorId;

            /* Get number of ganged pins */
            tempVal = `$INSTANCE_NAME`_curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            `$INSTANCE_NAME`_curSnsIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curFlashSnsPtr->firstPinId];

            /* Connect all ganged sensors  */
            do
            {
                `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
                `$INSTANCE_NAME`_curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Connect sensor */
            `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
        }
    #else
        /* Connect sensor */
        `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDDisconnectSnsExt
****************************************************************************//**
*
* \brief
*  Disconnects a ganged sensor port-pin from the sensing HW block and AMUX bus.
*  Sets the default state of the un-scanned sensor.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data and Inactive sensor
*   connection parameter, it updates the HSIOM, PC and DR registers.
*   The HSIOM register is updated only when the Inactive sensor connection parameter
*   is set to Shield.
*
* \param widgetId
*  Specifies ID of the widget.
*
* \param sensorId
*  Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDDisconnectSnsExt(uint32 widgetId, uint32 sensorId)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    /* initialize ptr to sensor IO structure to appropriate address        */
    `$INSTANCE_NAME`_curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                      `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash
                                                      + sensorId;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if ((`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].staticConfig &
            `$INSTANCE_NAME`_GANGED_SNS_MASK) == `$INSTANCE_NAME`_GANGED_SNS_MASK)
        {
            /* Get sns pointer */
            `$INSTANCE_NAME`_curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash +
                                               sensorId;

            /* Get number of ganged pins */
            tempVal = `$INSTANCE_NAME`_curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            `$INSTANCE_NAME`_curSnsIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curFlashSnsPtr->firstPinId];

            /* Disconnect all ganged sensors */
            do
            {
                `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
                `$INSTANCE_NAME`_curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Disconnect ganged sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
        }
    #else
        /* Disconnect ganged sensor */
        `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDConnectSns
****************************************************************************//**
*
* \brief
*  Connects a port pin used by the sensor to the AMUX bus of the sensing HW block.
*
* \details
*  Connects a port pin used by the sensor to the AMUX bus of the sensing HW block
*  while a sensor is being scanned. The function ignores the fact if
*  the sensor is a ganged sensor and connects only a specified pin.
*
*  Scanning should be completed before calling this API.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases. Functions that perform a setup and scan of a sensor/widget,
*  automatically set the required pin states and perform the sensor connection.
*  They do not take into account changes in the design made by the
*  `$INSTANCE_NAME`_CSDConnectSns() function.
*
* \param  snsAddrPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which to be connected to the sensing HW block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 pinModeShift;
    uint32 pinHSIOMShift;

    /* Get offsets for sensor */
    pinModeShift = (uint32)snsAddrPtr->shift;
    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;

    interruptState = CyEnterCriticalSection();

    /* Use temporary variable to update registers without multiple writings to them */
    newRegisterValue = CY_GET_REG32(snsAddrPtr->hsiomPtr);
    newRegisterValue &= ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << pinHSIOMShift);
    newRegisterValue |= (uint32)((uint32)`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE << pinHSIOMShift);

    /* Update port configuration register (drive mode) for sensor */
    CY_SET_REG32(snsAddrPtr->pcPtr, CY_GET_REG32(snsAddrPtr->pcPtr) & (uint32)~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << pinModeShift));

    /* Update HSIOM register for sensor */
    CY_SET_REG32(snsAddrPtr->hsiomPtr, newRegisterValue);

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDDisconnectSns
****************************************************************************//**
*
* \brief
*  Disconnects a sensor port pin from the sensing HW block and the AMUX bus. Sets
*  the default state of the un-scanned sensor.
*
* \details
*  This function works identically to `$INSTANCE_NAME`_CSDConnectSns() except
*  it disconnects the specified port-pin used by the sensor.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases. Functions that perform a setup and scan of sensor/widget
*  automatically set the required pin states and perform the sensor connection.
*  They ignore changes in the design made by the
*  `$INSTANCE_NAME`_CSDDisconnectSns() function.
*
* \param  snsAddrPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which should be disconnected from the sensing HW block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint32 pinHSIOMShift;
    uint32 newRegisterValue;
    uint32 pinModeShift;

    #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) || \
        (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
        uint8  interruptState;
    #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))) */

    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;
    pinModeShift = (uint32)snsAddrPtr->shift;

    #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) ||  \
        (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
        /* Update HSIOM register to disconnect sensor */
        CY_SET_REG32(snsAddrPtr->hsiomPtr, CY_GET_REG32(snsAddrPtr->hsiomPtr) & ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << pinHSIOMShift));

        interruptState = CyEnterCriticalSection();

        /* Update port configuration register (drive mode) for sensor */
        newRegisterValue = CY_GET_REG32(snsAddrPtr->pcPtr);
        newRegisterValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << pinModeShift);
        newRegisterValue |= `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION << pinModeShift;
        CY_SET_REG32(snsAddrPtr->pcPtr, newRegisterValue);

        CyExitCriticalSection(interruptState);

        /* Set logic 0 to port data register */
        CY_SET_REG32(snsAddrPtr->drPtr, CY_GET_REG32(snsAddrPtr->drPtr) & (uint32)~(uint32)((uint32)1u << snsAddrPtr->drShift));
    #else
        /* Update port configuration register (drive mode to HiZ Analog) for sensor */
        CY_SET_REG32(snsAddrPtr->pcPtr, CY_GET_REG32(snsAddrPtr->pcPtr) & (uint32)~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << pinModeShift));

        /* Connect to Shield */
        newRegisterValue = CY_GET_REG32(snsAddrPtr->hsiomPtr) & ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << pinHSIOMShift);
        newRegisterValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD << pinHSIOMShift);
        CY_SET_REG32(snsAddrPtr->hsiomPtr, newRegisterValue);
    #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)) */
}

#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDSetSingleIdacMode
        ****************************************************************************//**
        *
        * \brief
        *  This function set single IDAC mode.
        *
        * \details
        *   For Third-generation HW block: The function enables Modulator IDAC only in variable mode.
        *   For Fourth-generation HW block: The function enables IDACA LEG1 in CSD mode, IDACA LEG2 in GP mode.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSDSetSingleIdacMode(void)
        {
            uint32 newRegValue;

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                /* Enable IDACA LEG1 in CSD mode, IDACA LEG2 in GP mode */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR) &
                              `$INSTANCE_NAME`_IDAC_MOD_VAL_MASK;
                newRegValue |= `$INSTANCE_NAME`_IDAC_MOD_CALIBRATION_CFG;
                CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, newRegValue);
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR) & `$INSTANCE_NAME`_IDAC_COMP_VAL_MASK;
                    newRegValue |= `$INSTANCE_NAME`_IDAC_COMP_CALIBRATION_CFG;
                    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR, newRegValue);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                          (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN */
            #else
                /* Enable Modulator IDAC only in variable mode */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR) &
                              ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | `$INSTANCE_NAME`_IDAC_COMP_MODE_MASK);
                newRegValue |= `$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE;
                CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, newRegValue);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)) */

#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDRestoreIdacMode
        ****************************************************************************//**
        *
        * \brief
        *  This function restores IDAC configuration.
        *
        * \details
        *   The function restores Compensation IDAC if it is enabled.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSDRestoreIdacMode(void)
        {
            /* Restore IDAC configuration */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                uint32 newRegValue;

                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
                newRegValue |= `$INSTANCE_NAME`_DEFAULT_SW_REFGEN_SEL;
                CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR, newRegValue);
                CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, `$INSTANCE_NAME`_IDAC_MOD_DEFAULT_CFG);
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)
                CY_SET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR, `$INSTANCE_NAME`_IDAC_COMP_DEFAULT_CFG);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                          (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN */
            #else
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG);
                #else
                    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR) &
                                                                        ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | `$INSTANCE_NAME`_IDAC_MOD_MASK));
                    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR) | `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDCalibrateCheck
    ****************************************************************************//**
    *
    * \brief
    *  This internal function checks if the calibration is performed successfully.
    *
    * \details
    *   The function verifies calibration error based on maximum raw count level.
    *
    * \param rawLevel The raw data level which should be reached during the
    *   calibration procedure.
    * \param rawData  Calibrated raw counts.
    *
    * \return Returns the status of the operation:
    *   - Zero     - All the sensors in the widget are calibrated successfully.
    *   - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus `$INSTANCE_NAME`_SsCSDCalibrateCheck(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt, uint32 rawLevel, uint32 rawData)
    {
        cystatus calibrateStatus;
        uint32 rawCountsError;
        uint32 minRawLevel = 0u;
        uint32 maxRawLevel = (0x00000001Lu << ptrWdgt->resolution) - 1u;

        /* Calculate the error in rawcounts for given resolution (round to floor) */
        rawCountsError = ((maxRawLevel * `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR) /
                          `$INSTANCE_NAME`_PERCENTAGE_100) + 1u;

        /* Get minimum and maximum range values */
        if ((rawLevel + rawCountsError) <= maxRawLevel)
        {
            maxRawLevel = rawLevel + rawCountsError;
        }
        if (rawLevel >= rawCountsError)
        {
            minRawLevel = rawLevel - rawCountsError;
        }

        /* Check if calibration is in valid range */
        if ((rawData < minRawLevel) || (rawData > maxRawLevel))
        {
            calibrateStatus = CYRET_BAD_DATA;
        }
        else
        {
            calibrateStatus = CYRET_SUCCESS;
        }

        return (calibrateStatus);
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDCalibrateOneSensor
    ****************************************************************************//**
    *
    * \brief
    *  Computes the Modulator IDAC value for one sensor that provides raw signal at
    *  the specified level.
    *
    * \details
    *   The function performs the following tasks:
    *   1. initializes The Compensation IDAC to zero
    *   2. Enables the calibrated sensor
    *   3. Performs eight iteration steps to get the target = rawLevel
    *      setting and resetting the IDAC value bits beginning from the
    *      MSB bit to an MSB bit.
    *   4. Disables the calibrated sensor
    *   5. Checks if the IDAC is in the correct range
    *   6. Updates the maximum IDAC value in the widget
    *   7. Stores the temporary ModIDAC8 value (in the single-IDAC mode).
    *
    *  The CSD block should be initialized with the `$INSTANCE_NAME`_SsCSDInitialize()
    *  API before using this function.
    *
    * \param  rawLevel
    *   The raw data level which should be reached during the calibration procedure.
    * \param  ptrIdac  The pointer to IDAC.
    * \param  iDAC8Max The pointer to the maximum IDAC value in the widget.
    *
    * \return Returns the status of the operation:
    *  - Zero     - All the sensors in the widget are calibrated successfully.
    *  - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus `$INSTANCE_NAME`_SsCSDCalibrateOneSensor(uint32 rawLevel,
                                                           uint8 *ptrIdac,
                                                           uint8 *iDAC8Max)
    {
        cystatus calibrateStatus;
        uint32 calMask = ((uint32)`$INSTANCE_NAME`_CAL_MIDDLE_BIT << 1uL);
        uint32 watchdogCounter;

        uint16 rawData0 = 0u;
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            uint16 rawData1 = 0u;
            uint16 rawData2 = 0u;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

        /* Declare and initialize ptr to widget and sensor structures to appropriate address */
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2WdgtRam;

        ptrIdac[0u] = 0u;
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = 0u;
            ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = 0u;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

        /* Setup the calibrated sensor of the widget (Set IDAC = calMask and connect the sensor) */
        `$INSTANCE_NAME`_CSDSetupWidgetExt((uint32)`$INSTANCE_NAME`_widgetIndex, (uint32)`$INSTANCE_NAME`_sensorIndex);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /* Set single IDAC mode */
            `$INSTANCE_NAME`_SsCSDSetSingleIdacMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

        /*
         * Perform the iteration steps to get target = rawLevel.
         * The number of iteration steps is defined by calMask and depend on IDAC resolution.
         */
        do
        {
            /* Decrease IDAC until rawData reaches rawLevel */
            if (rawData0 < rawLevel)
            {
                /* Reset bit for null channel (decrease IDAC -> will increase rawData) */
                ptrIdac[0u] &= (uint8)(~calMask);
            }
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                if (rawData1 < rawLevel)
                {
                    ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] &= (uint8)(~calMask);
                }
                if (rawData2 < rawLevel)
                {
                    ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] &= (uint8)(~calMask);
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /*
            * Shift calMask to set or reset next bit.
            * Perform scan even if callibration mask is equal to zero.
            * It gives raw counts for the last changed IDAC.
            */
            calMask >>= 1u;

            /* Set bit for null channel */
            ptrIdac[0u] |= (uint8)calMask;
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] |= (uint8)calMask;
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] |= (uint8)calMask;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /* Update IDAC */
            `$INSTANCE_NAME`_SsCSDSetUpIdacs(ptrWdgt);

            /* Scan sensor */
            `$INSTANCE_NAME`_CSDScanExt();

            /* Initialize Watchdog Counter with time interval which is enough to charge 100 nF capacitor */
            watchdogCounter = `$INSTANCE_NAME`_CSD_CALIBR_WATCHDOG_CYCLES_NUM;
            while (((`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY) != 0u) &&
                   (0u != watchdogCounter))
            {
                /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
                watchdogCounter--;
            }

            /* Read rawData */
            rawData0 = `$INSTANCE_NAME`_curRamSnsPtr->raw[0u];
            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                rawData1 = `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                rawData2 = `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        }
        while (calMask > 0u);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            `$INSTANCE_NAME`_SsCSDDisconnectSnsExt((uint32)`$INSTANCE_NAME`_widgetIndex, (uint32)`$INSTANCE_NAME`_sensorIndex);
        #else
            /* initialize pointer to sensor IO structure */
            `$INSTANCE_NAME`_curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                            `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].ptr2SnsFlash
                                            + `$INSTANCE_NAME`_sensorIndex;

            /* Disable sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

        /* Set flag about disconnecting the electrode */
        `$INSTANCE_NAME`_eleCsdDisconnectFlag = 0u;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /* Restore IDAC configuration to default state */
            `$INSTANCE_NAME`_SsCSDRestoreIdacMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

        /* Check if IDAC is in correct range */
        calibrateStatus = `$INSTANCE_NAME`_SsCSDCalibrateCheck(ptrWdgt, rawLevel, (uint32)rawData0);
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateCheck(ptrWdgt, rawLevel, (uint32)rawData1);
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateCheck(ptrWdgt, rawLevel, (uint32)rawData2);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

        /*
         * Update maximum IDAC value in widget. iDAC8Max variable will contain
         * maximum IDAC value after all the sensors in a widget have been scanned.
         */
        if (*iDAC8Max < ptrIdac[0u])
        {
            *iDAC8Max = ptrIdac[0u];
            #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
                /* Stores IDAC and raw count that corresponds to a sensor with maximum Cp within a widget */
                `$INSTANCE_NAME`_calibratedIdac = *iDAC8Max;
                `$INSTANCE_NAME`_calibratedRawcount = rawData0;
            #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
        }
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
            }
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /*
             * Store temporary ModIDAC8 value (in single-IDAC mode) in idacComp variable.
             * We need this value to calculate idacMod value the in the dual-IDAC mode.
             */
            `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] = ptrIdac[0u];
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

        return (calibrateStatus);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CSDCalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Executes the IDAC calibration for all the sensors in the widget specified in
    *  the input.
    *
    * \details
    *  Performs a successive approximation search algorithm to find appropriate
    *  IDAC values for sensors in the specified widget that provides the raw
    *  count to the level specified by the target parameter.
    *
    *  Calibration is always performed in the single IDAC mode and if the dual
    *  IDAC mode (Enable compensation IDAC is enabled) is configured, the IDAC
    *  values are re-calculated to match the raw count target. If a widget
    *  consists of two or more elements (buttons, slider segments, etc.), then
    *  calibration is performed by the element with the highest sensor
    *  capacitance.
    *
    *  Calibration fails if the achieved raw count is outside of the +/-10%
    *  range of the target.
    *
    *  This function is available when the CSD Enable IDAC auto-calibration
    *  parameter is enabled or the  SmartSense auto-tuning mode is configured.
    *
    * \param widgetId
    *  Specifies the ID number of the CSD widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  `$INSTANCE_NAME` Configuration header file defined as
    *  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
    *
    * \param target
    *  Specifies the calibration target in percentages of the maximum raw count.
    *
    * \return
    *  Returns the status of the specified widget calibration:
    *    - CYRET_SUCCESS - The operation is successfully completed.
    *    - CYRET_BAD_PARAM - The input parameter is invalid.
    *    - CYRET_BAD_DATA - The calibration failed and the Component may not operate as expected.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_CSDCalibrateWidget(uint32 widgetId, uint32 target)
    {
        uint32 rawLevel;
        cystatus calibrateStatus = CYRET_SUCCESS;

        #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
            #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                uint8 maxIdac = 1u;
                uint16 maxRaw = 1u;
            #endif /*(`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
        #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

        /* Declare and initialize ptr to widget and sensor structures to appropriate address */
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                              `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

        #if (1u == `$INSTANCE_NAME`_NUM_SCAN_FREQS)
            uint8 iDAC8Max[`$INSTANCE_NAME`_NUM_SCAN_FREQS] = {1u};
        #else
            uint8 iDAC8Max[`$INSTANCE_NAME`_NUM_SCAN_FREQS] = {1u, 1u, 1u};
        #endif /* (1u == `$INSTANCE_NAME`_NUM_SCAN_FREQS) */

        uint8 *ptrIdac;

        /* Calibrate maximum level for given resolution */
        rawLevel = (0x00000001Lu << ptrWdgt->resolution) - 1u;

        /* Calculate percentage of maximum value */
        rawLevel = (rawLevel * target) / `$INSTANCE_NAME`_PERCENTAGE_100;

        /* Update `$INSTANCE_NAME`_widgetIndex */
        `$INSTANCE_NAME`_widgetIndex = (uint8)widgetId;

        /* Setup ISR handler to single-sensor scan function */
        `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_CSDPostSingleScan);

        /* Init pointer to Modulator IDAC */
        ptrIdac = &ptrWdgt->idacMod[0u];

        #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
            `$INSTANCE_NAME`_calibratedIdac = 1u;
            `$INSTANCE_NAME`_calibratedRawcount = 1u;
        #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

        /* Go through all the sensors (or columns of touchpad) of widget to calibrate them */
        for (`$INSTANCE_NAME`_sensorIndex = 0u;
             `$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols;
             `$INSTANCE_NAME`_sensorIndex++)
        {
            /* Calibrate current sensor in widget */
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateOneSensor(rawLevel, ptrIdac, iDAC8Max);
        }

        /* Normalize idacMod and idacComp values */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /* Calculate Modulator value: idacMod = (iDAC8Max + 1)/2 */
            ptrIdac[0u] = (iDAC8Max[0u] + 1u) >> 1u;
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =  (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] + 1u) >> 1u;
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] + 1u) >> 1u;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /* Go through all columns of touchpad (or all the sensors in button) to normalize them */
            for (`$INSTANCE_NAME`_sensorIndex = 0u;
                 `$INSTANCE_NAME`_sensorIndex < `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols;
                 `$INSTANCE_NAME`_sensorIndex++)
            {
                `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                         `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam + `$INSTANCE_NAME`_sensorIndex;
                /* Calculate Compensation IDAC value: idacComp(i) = (iDAC8(i) - idacMod) * Target */
                if (`$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] >= ptrIdac[0u])
                {
                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] -= ptrIdac[0u];
                    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                         (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                        `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] =
                            (uint8)((((target * `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u]) + `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) /
                            `$INSTANCE_NAME`_PERCENTAGE_100);
                    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                               (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
                }
                else
                {
                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] = 0u;
                }
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    /* Do same for first frequency channel */
                    if (`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] >= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1])
                    {
                        `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] -= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                             (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                            `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =
                                (uint8)((((target * `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1]) +
                                `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                   (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
                    }
                    else
                    {
                       `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = 0u;
                    }
                    /* Do same for second frequency channel */
                    if (`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] >= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2])
                    {
                        `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] -= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
                        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                             (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                            `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] =
                                (uint8)((((target * `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2]) +
                                `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                   (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
                    }
                    else
                    {
                        `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = 0u;
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            }
        #else
            /* Normalize widget for single-IDAC mode*/
            ptrIdac[0u] = iDAC8Max[0u];
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].wdgtType) ||
                (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].wdgtType))
            {
                /* Init pointer to Modulator IDAC for columns */
                ptrIdac = &ptrWdgt->rowIdacMod[0u];

                /* Reset the maximum value for columns */
                iDAC8Max[0u] = 1u;
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = 1u;
                    iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = 1u;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

                #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
                    maxIdac = `$INSTANCE_NAME`_calibratedIdac;
                    maxRaw = `$INSTANCE_NAME`_calibratedRawcount;
                    `$INSTANCE_NAME`_calibratedIdac = 1u;
                    `$INSTANCE_NAME`_calibratedRawcount = 1u;
                #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

                /* Go through all columns of touchpad to calibrate them */
                for (`$INSTANCE_NAME`_sensorIndex = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols;
                     `$INSTANCE_NAME`_sensorIndex < (uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].totalNumSns;
                     `$INSTANCE_NAME`_sensorIndex++)
                {
                    /* Calibrate current sensor in widget */
                    calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateOneSensor(rawLevel, ptrIdac, iDAC8Max);
                }

                #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
                    `$INSTANCE_NAME`_calibratedIdacRow = `$INSTANCE_NAME`_calibratedIdac;
                    `$INSTANCE_NAME`_calibratedRawcountRow = `$INSTANCE_NAME`_calibratedRawcount;
                    `$INSTANCE_NAME`_calibratedIdac = maxIdac;
                    `$INSTANCE_NAME`_calibratedRawcount = maxRaw;
                #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

                /* Normalize idacMod and idacComp values */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                    /* Calculate Modulator value: idacMod = (iDAC8Max + 1)/2 */
                    ptrIdac[0u] = (iDAC8Max[0u] + 1u) >> 1u;
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                        ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =  (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] + 1u) >> 1u;
                        ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] + 1u) >> 1u;
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

                    /* Go through all columns of touchpad to normalize them */
                    for (`$INSTANCE_NAME`_sensorIndex = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols;
                         `$INSTANCE_NAME`_sensorIndex < (uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].totalNumSns;
                         `$INSTANCE_NAME`_sensorIndex++)
                    {
                        `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                                 `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam + `$INSTANCE_NAME`_sensorIndex;

                        /* Calculate Compensation IDAC value: idacComp(i) = (iDAC8(i) - idacMod) * Target */
                        if (`$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] >= ptrIdac[0u])
                        {
                            `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] -= ptrIdac[0u];
                            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                 (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u] =
                                    (uint8)((((target * `$INSTANCE_NAME`_curRamSnsPtr->idacComp[0u]) +
                                        `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                       (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
                        }
                        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                            /* Do same for first frequency channel */
                            if (`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] >= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1])
                            {
                                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] -= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                                #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                     (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =
                                        (uint8)((((target * `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1]) +
                                        `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                                #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                           (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
                            }
                            /* Do same for second frequency channel */
                            if (`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] >= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2])
                            {
                                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] -= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
                                #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                     (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] =
                                        (uint8)((((target * `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2]) +
                                        `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                                #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN) ||\
                                           (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
                            }
                        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
                    }
                #else
                    /* Normalize widget for single-IDAC mode*/
                    ptrIdac[0u] = iDAC8Max[0u];
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                        ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                        ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
            }
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

        `$INSTANCE_NAME`_sensorIndex = 0u;

        return calibrateStatus;
    }
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)) */


#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDClockRestart
    ****************************************************************************//**
    *
    * \brief
    *  This function restarts the clocks.
    *
    * \details
    *  The function performs following:
    *  1) Stops, sets dividers and starts ModClk clock;
    *  2) Stops and starts SnsClk clock;
    *  3) Scan one cycle to reset the flip-flop for Direct clock mode.
    *
    *******************************************************************************/
    CY_INLINE static void `$INSTANCE_NAME`_SsCSDClockRestart(void)
    {
        /* Stop clocks, set dividers, and start clock to align clock phase */
        `$INSTANCE_NAME`_SsSetModClkClockDivider((uint32)`$INSTANCE_NAME`_dsRam.modCsdClk);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
            /* Stop sense clock clock   */
            CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                         ((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID <<
                         `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT)|
                         ((uint32)`$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_MASK));

            /* Check whether previous sense clock start command has finished. */
            while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) & `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK))
            {
                /* Wait until previous sense clock start command has finished. */
            }

            /* Start sense clock aligned to previously started modulator clock. */
            CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                         (uint32)(((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT) |
                          ((uint32)`$INSTANCE_NAME`_ModClk__PA_DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_PA_DIV_SHIFT) |
                          `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK));
        #else
            /* Clear bit to disable SnsClk clock. */
            CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                         CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) &
                         (uint32)(~(uint32)`$INSTANCE_NAME`_SnsClk__ENABLE_MASK));

            /* Set bit to enable SnsClk clock. */
            CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                         CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) |
                        `$INSTANCE_NAME`_SnsClk__ENABLE_MASK);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

        #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
            /* Scan one cycle to reset the flip-flop for Direct clock mode */
            CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
            CY_SET_REG32(`$INSTANCE_NAME`_COUNTER_PTR, `$INSTANCE_NAME`_ONE_CYCLE);

            while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_COUNTER_PTR) & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
            {
                /* Wait until scanning is complete */
            }
            CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
            CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
    }
#endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDCmodPrecharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  For Third-generation HW block:
*  The function initializes the Cmod charging to Vref.
*  Then it waits the even when Cmod is completely charged
*  to Vref to have stable raw counts. Software Watchdog Counter is implemented to
*  prevent the project hanging.
*
*  For Fourth-generation HW block:
*  Coarse initialization for CMOD and Cch.
*  The coarse initialization is performed by HSCOMP.
*  The HSCOMP monitors the Cmod voltage via Cmod sense path
*  and charges the Cmod using HCAV switch via CSDBUS-A, AMUXBUS-A
*  and static connection of Cmod to AMUXBUS-A.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSDCmodPrecharge(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

        /* Fourth-generation HW block section */

        uint32 watchdogCounter;
        #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) &&\
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
            uint32 tmpRegValue;
        #endif

        CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR, `$INSTANCE_NAME`_CSD_CSDCMP_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR,  `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,  `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_INIT);
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /*
             * Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad
             * Connect AMUXBUS-B to HSCMP positive input
             */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_SW_HS_P_SEL_COARSE);

            #if(0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                /* Connect CTANK to AMUXBUS-A */
                tmpRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                tmpRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
                tmpRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, tmpRegValue);
            #endif /* (0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
        #else
            /* Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_SW_HS_P_SEL_COARSE);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR, `$INSTANCE_NAME`_CSD_SW_RES_INIT);

        /* Clear all interrupt pending requests */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_ALL_MASK);

        CY_SET_REG32(`$INSTANCE_NAME`_INTR_MASK_PTR, `$INSTANCE_NAME`_CLEAR_MASK);

        /* Start SEQUENCER for coarse initialization for Cmod */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SEQ_START_SEQ_MODE_MASK |
                                                         `$INSTANCE_NAME`_SEQ_START_START_MASK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for INTR.INIT goes high */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_INTR_PTR) & `$INSTANCE_NAME`_INTR_INIT_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        if (0u == watchdogCounter)
        {
            /* Set sequencer to idle state if coarse initialization fails */
            CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SEQ_START_ABORT_MASK);
        }

    #else

        uint32 tmpRegValue;
        uint32 newRegValue;
        uint32 watchdogCounter;

        /* Save the current IDAC configuration */
        tmpRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR);

        /* Wait until Cmod discharges below Vref */
        CyDelayCycles(`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES);

        newRegValue = `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG | (tmpRegValue & ~`$INSTANCE_NAME`_IDAC_MOD_CFG_MASK);

        /* Set the IDAC configuration for fast Cmod precharge to Vref */
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, newRegValue);

        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CONFIG_PTR) & ~`$INSTANCE_NAME`_CONFIG_POLARITY_MASK);
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait until Cmod reaches to Vref */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_STATUS_PTR) & `$INSTANCE_NAME`_STATUS_SAMPLE)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CONFIG_PTR) | `$INSTANCE_NAME`_CONFIG_POLARITY_MASK);
        #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

        /* Restore the current IDAC configuration */
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, tmpRegValue);

        /* Enable the sense modulator output */
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd | `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG_CSD_EN | `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK);

        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDTriggerScan
****************************************************************************//**
*
* \brief
*  This function triggers the scanning.
*
* \details
*  For Third-generation HW block:
*  Writes resolution to start the scanning.
*
*  For Fourth-generation HW block:
*  Trigger the fine initialization (scan some dummy cycles) and start sampling.
*  Fine initialization for CMOD and Start scan.
*  For the fine initialization and sampling, Cmod is static connected to AMUXBUS-A
*  and in every conversion (one cycle of SnsClk), the sensor capacitance is charged
*  from Cmod and discharged to ground using the switches in GPIO cell.
*  The CSDCOMP monitors voltage on Cmod using the sense path and charges Cmod back
*  to Vref using IDACs by connecting IDAC to CSDBUS-A and then the AMUXBUS-A.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSDTriggerScan(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

        /* Fourth-generation HW block section */

        uint32 watchdogCounter;

        /* Clear previous interrupts */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_ALL_MASK);

        /* Clear pending interrupts  */
        CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);

        /* Enable CSD interrupt */
        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);


        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_HS_P_SEL_SCAN);

        /* Set scanning configuration for switches */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_SCAN);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_SCAN);

        CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,  `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SCAN);

        #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
            /* Connect CTANK to AMUXBUS-B */
            `$INSTANCE_NAME`_SsCSDEnableShieldTank();
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR, `$INSTANCE_NAME`_CSD_SW_RES_SCAN);
        CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR, `$INSTANCE_NAME`_CSD_CSDCMP_SCAN);

        #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Disable HSCOMP during the sampling phase when shield is disabled */
            CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, 0u);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, `$INSTANCE_NAME`_HSCMP_SCAN_MASK);
        #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
            /* Force the LFSR to it's initial state (all ones) */
            CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR, CY_GET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR) |
                                                           `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_CLEAR_MASK);
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

        /* Enable SAMPLE interrupt */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_MASK_PTR, `$INSTANCE_NAME`_INTR_MASK_SAMPLE_MASK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for IDLE state of the HW sequencer */
        while((0u != (`$INSTANCE_NAME`_STAT_SEQ_REG & `$INSTANCE_NAME`_STAT_SEQ_SEQ_STATE_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        /* Start SEQUENCER for fine initialization scan for Cmod and then for normal scan */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SEQ_START_AZ0_SKIP_MASK |
                                                     `$INSTANCE_NAME`_SEQ_START_AZ1_SKIP_MASK |
                                                     `$INSTANCE_NAME`_SEQ_START_START_MASK);

    #else

        /* Third-generation HW block section */

        /* Set resolution to Counter register to start scanning */
        CY_SET_REG32(`$INSTANCE_NAME`_COUNTER_PTR, `$INSTANCE_NAME`_counterResolution);

    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


/* [] END OF FILE */
