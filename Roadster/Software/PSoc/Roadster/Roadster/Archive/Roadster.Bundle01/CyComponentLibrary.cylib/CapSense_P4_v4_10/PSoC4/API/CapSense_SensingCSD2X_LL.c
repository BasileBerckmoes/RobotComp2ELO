/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingCSD2X_LL.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file defines the data structure global variables and provides 
*   implementation for low-level APIs of the CSD2X part of 
*   the Sensing module.
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
#include "`$INSTANCE_NAME`_SensingCSD2X_LL.h"
#include "`$INSTANCE_NAME`_Sensing.h"

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)

/***************************************
* Variables
***************************************/

uint32 `$INSTANCE_NAME`_configCsd0 = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG | `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
uint32 `$INSTANCE_NAME`_configCsd1 = `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG | `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
static uint32 `$INSTANCE_NAME`_counterResolution0 = `$INSTANCE_NAME`_CNT_RESOLUTION_12_BITS;
static uint32 `$INSTANCE_NAME`_counterResolution1 = `$INSTANCE_NAME`_CNT_RESOLUTION_12_BITS;

/* Flag to indicate electrodes that were connected previously */
static uint8 `$INSTANCE_NAME`_eleCsd0DisconnectFlag = 0u;
static uint8 `$INSTANCE_NAME`_eleCsd1DisconnectFlag = 0u;

/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) 
    static void `$INSTANCE_NAME`_SsCSD2XSetShield0Delay(uint32 delay);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN)
        static void `$INSTANCE_NAME`_SsCSD2XEnableShieldTank0(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN) */
    #if (0u != `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT)
        static void `$INSTANCE_NAME`_SsCSD2XEnableShield0Electrodes(void);
    #endif /* (0u != `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) 
    static void `$INSTANCE_NAME`_SsCSD2XSetShield1Delay(uint32 delay);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN)
        static void `$INSTANCE_NAME`_SsCSD2XEnableShieldTank1(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN) */
    #if (0u != `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT)
        static void `$INSTANCE_NAME`_SsCSD2XEnableShield1Electrodes(void);
    #endif /* (0u != `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) */
static void `$INSTANCE_NAME`_SsCSD2XConfigIDACs(void);
static void `$INSTANCE_NAME`_SsCSD0ElectrodeCheck(void);
static void `$INSTANCE_NAME`_SsCSD1ElectrodeCheck(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XSnsClkRestart(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XClockRestart(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XCmod0Precharge(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XCmod1Precharge(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD0TriggerScan(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD1TriggerScan(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD0ScanOneCycle(void);
CY_INLINE static void `$INSTANCE_NAME`_SsCSD1ScanOneCycle(void);
static cystatus `$INSTANCE_NAME`_SsCSD0SetupWidgetExt(void);
static cystatus `$INSTANCE_NAME`_SsCSD1SetupWidgetExt(void);
#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    static cystatus `$INSTANCE_NAME`_SsCSD0CalibrateOneSensor(uint32 rawLevel, uint8 *iDAC8Max);
    static cystatus `$INSTANCE_NAME`_SsCSD1CalibrateOneSensor(uint32 rawLevel, uint8 *iDAC8Max);
    static void `$INSTANCE_NAME`_SsCSD0SetSingleIdacMode(void);
    static void `$INSTANCE_NAME`_SsCSD1SetSingleIdacMode(void);
    static void `$INSTANCE_NAME`_SsCSD0RestoreIdacMode(void);
    static void `$INSTANCE_NAME`_SsCSD1RestoreIdacMode(void);
    static uint32 `$INSTANCE_NAME`_SsCSD0StartSample(void);
    static uint32 `$INSTANCE_NAME`_SsCSD1StartSample(void);
    static cystatus `$INSTANCE_NAME`_SsCSDCalibrateCheck(uint32 rawLevel, uint32 rawData);
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)) */

/** \}
* \endcond */   

/* Global software variables */
volatile uint8 `$INSTANCE_NAME`_slotIndex = 0u;    /* Index of the scanning slot */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) 
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD2XSetShield0Delay
    ****************************************************************************//**
    *
    * \brief
    *   This is an internal function that sets a shield delay for CSD0 block.
    *
    * \details
    *   The function updates the CSD configuration register bits that define the shield 
    *   signal delay relatively to the sense signal.
    *
    * \param delay 
    *   Specifies the shield delay value:
    *                               0 - no delay
    *                               1 - 5ns delay (50 ns for CSDv1 block)
    *                               2 - 10ns delay (100 ns for CSDv1 block)
    *                               3 - 20ns delay
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSD2XSetShield0Delay(uint32 delay)
    {    
        /* Update CSD config register shield delay bits with shield delay value */
        `$INSTANCE_NAME`_configCsd0 &= (uint32)(~`$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK);
        `$INSTANCE_NAME`_configCsd0 |= (delay << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT);
    }   
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSD2XEnableShieldTank0
        ****************************************************************************//**
        *
        * \brief
        *   This function configures Csh0 pin
        *
        * \details
        *   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
        *   For CSD v1 IP HW block it additionally sets Strong drive mode for Csh
        *   and applies High level to Csh pin when precharge is set to IO buffer.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSD2XEnableShieldTank0(void)
        {    
            uint32 newRegValue;

            /* Update the CSH_HSIOM register to connect Csh to AMUXBUS-B */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH0_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH0_HSIOM_MASK);
            newRegValue |= (`$INSTANCE_NAME`_CSH0_TO_AMUXBUS_B_MASK << `$INSTANCE_NAME`_CSH0_HSIOM_SHIFT);
            CY_SET_REG32(`$INSTANCE_NAME`_CSH0_HSIOM_PTR, newRegValue);

            #if ((`$INSTANCE_NAME`_CSH0_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC) &&\
                 (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                /* Set Strong drive mode for Csh0 */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH0_PC_PTR);
                newRegValue &= (uint32)(~(`$INSTANCE_NAME`_CSH0_PC_MASK << `$INSTANCE_NAME`_CSH0_PC_SHIFT));
                newRegValue |= (`$INSTANCE_NAME`_CSH0_PC_STRONG_MODE << `$INSTANCE_NAME`_CSH0_PC_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CSH0_PC_PTR, newRegValue);

                /* Appliy High level to Csh0 pin */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH0_DR_PTR);
                newRegValue &= (uint32)(~(`$INSTANCE_NAME`_CSH0_DR_MASK << `$INSTANCE_NAME`_CSH0_SHIFT));
                newRegValue |= (uint32)`$INSTANCE_NAME`_CSH0_DR_CONFIG;
                CY_SET_REG32(`$INSTANCE_NAME`_CSH0_DR_PTR, newRegValue);
            #endif /* ((`$INSTANCE_NAME`_CSH0_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC) &&\
                       (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
        } 
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN) */   

    
    #if (0u != `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSD2XEnableShield0Electrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function initializes Shield Electrodes for CSD0 block.
        *
        * \details
        *   The function sets the bit in the HSIOM register which enables the shield electrode
        *   functionality on the pin. The port and pin configurations are stored in  
        *   the `$INSTANCE_NAME`_shield0IoList structure.
        * 
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSD2XEnableShield0Electrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Set drive mode to Analog */
                CY_SET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].pcPtr, CY_GET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].pcPtr) &
                           ~(`$INSTANCE_NAME`_GPIO_PC_MASK <<(`$INSTANCE_NAME`_shield0IoList[shieldIndex].shift)));

                /* Set HSIOM register mode to CSD_SHIELD or AMUXBUS B connection */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomPtr);
                newRegValue &= ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << (`$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomShift));
                
                /* Set HSIOM register mode to CSD_SHIELD */
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD << (`$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomShift));

                CY_SET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomPtr, newRegValue);
            }         
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDDisableShield0Electrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function disables Shield Electrodes for CSD0 block.
        *
        * \details
        *   The function resets the bit in the HSIOM register which disables the shield 
        *   electrode functionality on the pin. The port and pin configurations are  
        *   stored in  the `$INSTANCE_NAME`_shield0IoList structure.
        * 
        *******************************************************************************/
        void `$INSTANCE_NAME`_SsCSDDisableShield0Electrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Reset HSIOM register (to GPIO state) */
                CY_SET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomPtr, CY_GET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomPtr) & 
                             (uint32)~(uint32)(`$INSTANCE_NAME`_HSIOM_SEL_MASK << `$INSTANCE_NAME`_shield0IoList[shieldIndex].hsiomShift));          
                
                /* Update port configuration register (drive mode to ground)  */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].pcPtr);
                newRegValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_shield0IoList[shieldIndex].shift);
                newRegValue |= (`$INSTANCE_NAME`_SNS_GROUND_CONNECT << `$INSTANCE_NAME`_shield0IoList[shieldIndex].shift);   
                CY_SET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].pcPtr, newRegValue);
                
                /* Set logic 0 to port data register */
                CY_SET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].drPtr, CY_GET_REG32(`$INSTANCE_NAME`_shield0IoList[shieldIndex].drPtr) &
                           (uint32)~(uint32)((uint32)1u << `$INSTANCE_NAME`_shield0IoList[shieldIndex].drShift));
            }         
        }
    #endif /* (0u != `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) */ 


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) 
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD2XSetShield1Delay
    ****************************************************************************//**
    *
    * \brief
    *   This is an internal function that sets a shield delay for CSD1 block.
    *
    * \details
    *   The function updates the CSD configuration register bits that define the shield 
    *   signal delay relatively to the sense signal.
    *
    * \param delay 
    *   Specifies the shield delay value:
    *                               0 - no delay
    *                               1 - 5ns delay (50 ns for CSDv1 block)
    *                               2 - 10ns delay (100 ns for CSDv1 block)
    *                               3 - 20ns delay
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSD2XSetShield1Delay(uint32 delay)
    {    
        /* Update CSD config register shield delay bits with shield delay value */
        `$INSTANCE_NAME`_configCsd1 &= (uint32)(~`$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK);
        `$INSTANCE_NAME`_configCsd1 |= (delay << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT);
    }   
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSD2XEnableShieldTank1
        ****************************************************************************//**
        *
        * \brief
        *   This function configures Csh1 pin
        *
        * \details
        *   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
        *   For CSD v1 IP HW block it additionally sets Strong drive mode for Csh
        *   and applies High level to Csh pin when precharge is set to IO buffer.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSD2XEnableShieldTank1(void)
        {    
            uint32 newRegValue;

            /* Update the CSH_HSIOM register to connect Csh1 to AMUXBUS-B */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH1_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH1_HSIOM_MASK);
            newRegValue |= (`$INSTANCE_NAME`_CSH1_TO_AMUXBUS_B_MASK << `$INSTANCE_NAME`_CSH1_HSIOM_SHIFT);
            CY_SET_REG32(`$INSTANCE_NAME`_CSH1_HSIOM_PTR, newRegValue);

            #if ((`$INSTANCE_NAME`_CSH1_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC) &&\
                 (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
                /* Set Strong drive mode for Csh1 */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH1_PC_PTR);
                newRegValue &= (uint32)(~(`$INSTANCE_NAME`_CSH1_PC_MASK << `$INSTANCE_NAME`_CSH1_PC_SHIFT));
                newRegValue |= (`$INSTANCE_NAME`_CSH1_PC_STRONG_MODE << `$INSTANCE_NAME`_CSH1_PC_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CSH1_PC_PTR, newRegValue);

                /* Appliy High level to Csh1 pin for Csh */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH1_DR_PTR);
                newRegValue &= (uint32)(~(`$INSTANCE_NAME`_CSH1_DR_MASK << `$INSTANCE_NAME`_CSH1_SHIFT));
                newRegValue |= (uint32)`$INSTANCE_NAME`_CSH1_DR_CONFIG;
                CY_SET_REG32(`$INSTANCE_NAME`_CSH1_DR_PTR, newRegValue);
            #endif /* ((`$INSTANCE_NAME`_CSH1_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC) &&\
                       (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
        } 
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN) */   

    
    #if (0u != `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSD2XEnableShield1Electrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function initializes Shield Electrodes for CSD1 block.
        *
        * \details
        *   The function sets the bit in the HSIOM register which enables the shield electrode
        *   functionality on the pin. The port and pin configurations are stored in  
        *   the `$INSTANCE_NAME`_shield1IoList structure.
        * 
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSD2XEnableShield1Electrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Set drive mode to Analog */
                CY_SET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].pcPtr, CY_GET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].pcPtr) &
                           ~(`$INSTANCE_NAME`_GPIO_PC_MASK <<(`$INSTANCE_NAME`_shield1IoList[shieldIndex].shift)));

                /* Set HSIOM register mode to CSD_SHIELD or AMUXBUS B connection */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomPtr);
                newRegValue &= ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << (`$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomShift));
                
                /* Set HSIOM register mode to CSD_SHIELD */
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD << (`$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomShift));

                CY_SET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomPtr, newRegValue);
            }         
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDDisableShield1Electrodes
        ****************************************************************************//**
        *
        * \brief
        *   This internal function disables Shield Electrodes for CSD1 block.
        *
        * \details
        *   The function resets the bit in the HSIOM register which disables the shield 
        *   electrode functionality on the pin. The port and pin configurations are  
        *   stored in  the `$INSTANCE_NAME`_shield1IoList structure.
        * 
        *******************************************************************************/
        void `$INSTANCE_NAME`_SsCSDDisableShield1Electrodes(void)
        {
            uint32 newRegValue;
            uint32 shieldIndex;

            for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT; shieldIndex++)
            {
                /* Reset HSIOM register (to GPIO state) */
                CY_SET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomPtr, CY_GET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomPtr) & 
                             (uint32)~(uint32)(`$INSTANCE_NAME`_HSIOM_SEL_MASK << `$INSTANCE_NAME`_shield1IoList[shieldIndex].hsiomShift));          
                
                /* Update port configuration register (drive mode to ground)  */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].pcPtr);
                newRegValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_shield1IoList[shieldIndex].shift);
                newRegValue |= (`$INSTANCE_NAME`_SNS_GROUND_CONNECT << `$INSTANCE_NAME`_shield1IoList[shieldIndex].shift);   
                CY_SET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].pcPtr, newRegValue);
                
                /* Set logic 0 to port data register */
                CY_SET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].drPtr, CY_GET_REG32(`$INSTANCE_NAME`_shield1IoList[shieldIndex].drPtr) &
                           (uint32)~(uint32)((uint32)1u << `$INSTANCE_NAME`_shield1IoList[shieldIndex].drShift));
            }         
        }
    #endif /* (0u != `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) */ 


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD2XConfigIDACs
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
static void `$INSTANCE_NAME`_SsCSD2XConfigIDACs(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_CONFIG);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_CONFIG);
    #else
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR) &
                                                                  ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | 
                                                                  `$INSTANCE_NAME`_IDAC_MOD_MASK));
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR) | 
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_CONFIG);   
    
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR) &
                                                                  ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | 
                                                                  `$INSTANCE_NAME`_IDAC_MOD_MASK));
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR) | 
                                                                  `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_CONFIG);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0SetUpIdacs
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
void `$INSTANCE_NAME`_SsCSD0SetUpIdacs(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt)
{   

    uint8 interruptState;
    uint32 newRegValue;
    uint8 const *ptrIdacMod = ptrWdgt->idacMod;

    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN  | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex0)].numCols <= `$INSTANCE_NAME`_sensorIndex0)
        {
            ptrIdacMod = &ptrWdgt->rowIdacMod[0u];
        }
    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN  | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    interruptState = CyEnterCriticalSection();

    /* Get Idac Value */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR);
    
    /* Set Idac Value mask */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) 
        newRegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_MASK | `$INSTANCE_NAME`_IDAC_COMP_MASK);
    #else
        newRegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    
    /* Set Idac value */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        newRegValue |= (ptrIdacMod[`$INSTANCE_NAME`_scanFreqIndex] |        
                       (uint32)((uint32)`$INSTANCE_NAME`_curRamSnsPtr0->idacComp[`$INSTANCE_NAME`_scanFreqIndex] <<
                       `$INSTANCE_NAME`_IDAC_COMP_DATA_OFFSET));
    #else
        newRegValue |= ptrIdacMod[`$INSTANCE_NAME`_scanFreqIndex]; 
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */       
    CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, newRegValue);
    
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1SetUpIdacs
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
void `$INSTANCE_NAME`_SsCSD1SetUpIdacs(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt)
{   

    uint8 interruptState;
    uint32 newRegValue;
    uint8 const *ptrIdacMod = ptrWdgt->idacMod;

    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN  | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex1)].numCols <= `$INSTANCE_NAME`_sensorIndex1)
        {
            ptrIdacMod = &ptrWdgt->rowIdacMod[0u];
        }
    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    interruptState = CyEnterCriticalSection();

    /* Get Idac Value */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR);
    
    /* Set Idac Value mask */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) 
        newRegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_MASK | `$INSTANCE_NAME`_IDAC_COMP_MASK);
    #else
        newRegValue &= ~(`$INSTANCE_NAME`_IDAC_MOD_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    
    /* Set Idac value */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        newRegValue |= (ptrIdacMod[`$INSTANCE_NAME`_scanFreqIndex] |        
                       (uint32)((uint32)`$INSTANCE_NAME`_curRamSnsPtr1->idacComp[`$INSTANCE_NAME`_scanFreqIndex] <<
                       `$INSTANCE_NAME`_IDAC_COMP_DATA_OFFSET));
    #else
        newRegValue |= ptrIdacMod[`$INSTANCE_NAME`_scanFreqIndex]; 
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */       
    CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, newRegValue);
    
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSD2XInitialize
****************************************************************************//**
*
* \brief
*   This function initializes the CSD module.
*
* \details
*   The function performs the following steps for CSDv1 HW block:
*   1) Sets all the sensors to the inactive state;
*   2) Enables Shield Electrodes;
*   3) Configures the CSD block and IDACs;
*   4) Connects Cmod to AMUXBUS-A;
*   5) Enables the clocks;
*   6) Sets the shield delay;
*   7) Enables the CSD block; connects Vref Buffer to the AMUX bus.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSD2XInitialize(void)
{
    uint32 newRegValue;
    
    /* Set all sensors to inactive state */
    `$INSTANCE_NAME`_SsClearCSDSensors();
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN)  
        /* Connect shields to AMUX-B bus (config HSIOM regs) */        
        #if (0u != `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT)
            `$INSTANCE_NAME`_SsCSD2XEnableShield0Electrodes();
        #endif /* (0u != `$INSTANCE_NAME`_CSD0_TOTAL_SHIELD_COUNT) */
        
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN)
            /* Configure Csh0 */
            `$INSTANCE_NAME`_SsCSD2XEnableShieldTank0();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN)  
        /* Connect shields to AMUX-B bus (config HSIOM regs) */        
        #if (0u != `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT)
            `$INSTANCE_NAME`_SsCSD2XEnableShield1Electrodes();
        #endif /* (0u != `$INSTANCE_NAME`_CSD1_TOTAL_SHIELD_COUNT) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN)
            /* Configure Csh1 */
            `$INSTANCE_NAME`_SsCSD2XEnableShieldTank1();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) */
    
    /* Configure IDACs mode */
    `$INSTANCE_NAME`_SsCSD2XConfigIDACs();

    /* Connect Cmod0 to AMUXBUS-A using HSIOM registers */ 
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD0_HSIOM_PTR); 
    newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD0_HSIOM_MASK);
    newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CMOD0_HSIOM_SHIFT);
    CY_SET_REG32(`$INSTANCE_NAME`_CMOD0_HSIOM_PTR, newRegValue);
   
    /* Connect Cmod1 to AMUXBUS-A using HSIOM registers */ 
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD1_HSIOM_PTR); 
    newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD1_HSIOM_MASK);
    newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CMOD1_HSIOM_SHIFT);
    CY_SET_REG32(`$INSTANCE_NAME`_CMOD1_HSIOM_PTR, newRegValue);
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) 
        `$INSTANCE_NAME`_SsCSD2XSetShield0Delay(`$INSTANCE_NAME`_CSD0_SHIELD_DELAY);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_EN) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) 
        `$INSTANCE_NAME`_SsCSD2XSetShield1Delay(`$INSTANCE_NAME`_CSD1_SHIELD_DELAY);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_EN) */
    
    /* Enable CSD block. Connect Vref Buffer to AMUX bus to make sure that Cmod is charged before scanning in active mode */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1);
    #else
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG_CSD_EN);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG_CSD_EN);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /* Set clock source for all CSD widgets */
        `$INSTANCE_NAME`_SsInitializeSourceSenseClk();
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
    
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) &&\
         (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
         /* Set clock dividers and clock source mode */
        `$INSTANCE_NAME`_SsCSD0ConfigClock();
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) &&\
               (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0ElectrodeCheck
****************************************************************************//**
*
* \brief
*   Checks if electrodes were previously connected 
*   and if yes disconnects them.
*
* \details
*   This function checks if `$INSTANCE_NAME`_eleCsd0DisconnectFlag is set.
*   If it set, the function disconnects the previously connected electrode.
*   The previous IO is contained in `$INSTANCE_NAME`_curSnsIOPtr0 and 
*   `$INSTANCE_NAME`_curFlashSnsPtr0 contains the previous data for Ganged
*   sensors.
* 
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSD0ElectrodeCheck(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_eleCsd0DisconnectFlag)  
    {
        /* Disconnect if electrodes were previous connected */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            /* Check ganged sns flag  */
            if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_curFlashWdgtPtr0->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
            {
                /* Get number of ganged pins */
                tempVal = `$INSTANCE_NAME`_curFlashSnsPtr0->numPins;

                /* Get IO pointer  */
                `$INSTANCE_NAME`_curSnsIOPtr0 = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curFlashSnsPtr0->firstPinId];

                /* Disconnect all ganged sensors */
                do
                {
                    `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr0);
                    `$INSTANCE_NAME`_curSnsIOPtr0++;
                    tempVal--;
                } while (0u != tempVal);
            }
            else
            {
                /* Disconnect ganged sensor */
                `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr0);
            }
        #else
            /* Disable sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr0);    
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

        `$INSTANCE_NAME`_eleCsd0DisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1ElectrodeCheck
****************************************************************************//**
*
* \brief
*   Checks if electrodes were previously connected 
*   and if yes disconnects them.
*
* \details
*   This function checks if `$INSTANCE_NAME`_eleCsd1DisconnectFlag is set.
*   If it set, the function disconnects the previously connected electrode.
*   The previous IO is contained in `$INSTANCE_NAME`_curSnsIOPtr1 and 
*   `$INSTANCE_NAME`_curFlashSnsPtr1 contains the previous data for Ganged
*   sensors.
* 
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSD1ElectrodeCheck(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_eleCsd1DisconnectFlag)  
    {
        /* Disconnect if electrodes were previous connected */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            /* Check ganged sns flag  */
            if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_curFlashWdgtPtr1->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
            {
                /* Get number of ganged pins */
                tempVal = `$INSTANCE_NAME`_curFlashSnsPtr1->numPins;

                /* Get IO pointer  */
                `$INSTANCE_NAME`_curSnsIOPtr1 = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curFlashSnsPtr1->firstPinId];

                /* Disconnect all ganged sensors */
                do
                {
                    `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr1);
                    `$INSTANCE_NAME`_curSnsIOPtr1++;
                    tempVal--;
                } while (0u != tempVal);
            }
            else
            {
                /* Disconnect ganged sensor */
                `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr1);
            }
        #else
            /* Disable sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_curSnsIOPtr1);    
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

        `$INSTANCE_NAME`_eleCsd1DisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0SetupWidgetExt
****************************************************************************//**
*
* \brief
*   This API initializes the `$INSTANCE_NAME` CSD0 HW block 
*   with hardware-tuning parameters associated with a specific pair  
*   of widgets.
*
* \details
*   This API initializes the `$INSTANCE_NAME` CSD0 HW block 
*   with hardware-tuning parameters associated with a specific pair  
*   of widgets.
*
* \return Returns the status of operation:
*       Zero     - The `$INSTANCE_NAME` HW block is initialized.
*       Non-zero - The `$INSTANCE_NAME` HW block was busy and 
*                  could not be initialized.
*
*******************************************************************************/
static cystatus `$INSTANCE_NAME`_SsCSD0SetupWidgetExt(void)
{
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt;
  
    /* Disconnect previous electrode if it has been connected */
    `$INSTANCE_NAME`_SsCSD0ElectrodeCheck();
  
    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
    {       
        /*  Initialise ptr to widget structure to appropriate address */
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2WdgtRam;

        /*  Update global pointer to `$INSTANCE_NAME`_RAM_SNS_STRUCT to current sensor */
        `$INSTANCE_NAME`_curRamSnsPtr0 = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                                                  `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2SnsRam
                                                  + `$INSTANCE_NAME`_sensorIndex0;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) 
            /*  Initialise access pointers for current pointer to widget configuration in Flash */
            `$INSTANCE_NAME`_curFlashWdgtPtr0 = &`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0];
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */
        
        /* Update status register in Data structure */
        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_WDGT0_MASK;
        `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_widgetIndex0;
        
        /* Set up scanning resolution */
        `$INSTANCE_NAME`_SsCSD0CalculateScanDuration(ptrWdgt);
             
        #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) ||\
             (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
            `$INSTANCE_NAME`_SsCSD0ConfigClock();
        #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) ||\
                   (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */
             
        /* Setup Idac Value */
        `$INSTANCE_NAME`_SsCSD0SetUpIdacs(ptrWdgt);
        
        /* Initialise ptr to sensor IO structure to appropriate address */        
        `$INSTANCE_NAME`_curSnsIOPtr0 = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2SnsFlash
                                        + `$INSTANCE_NAME`_sensorIndex0;
        
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            /* Save sns pointer */
            `$INSTANCE_NAME`_curFlashSnsPtr0 = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2SnsFlash +
                                               `$INSTANCE_NAME`_sensorIndex0;

            /* Check ganged sns flag  */
            if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].staticConfig & 
                `$INSTANCE_NAME`_GANGED_SNS_MASK))
            { 
                /*  Setup ISR handler to multiple-sensor scan function with ganged sensors */
                `$INSTANCE_NAME`_ISR0_StartEx(&`$INSTANCE_NAME`_CSD0PostMultiScanGanged);
            }
            else
            {
                /*  Set up ISR handler to multiple-sensor scan function without ganged sensors */
                `$INSTANCE_NAME`_ISR0_StartEx(&`$INSTANCE_NAME`_CSD0PostMultiScan);
            }
        
            `$INSTANCE_NAME`_SsCSDConnectSensorExt((uint32)`$INSTANCE_NAME`_widgetIndex0, (uint32)`$INSTANCE_NAME`_sensorIndex0);
        #else   
             /*  Set up ISR handler to multiple-sensor scan function without ganged sensors */
            `$INSTANCE_NAME`_ISR0_StartEx(&`$INSTANCE_NAME`_CSD0PostMultiScan);
        
            /* Enable sensor */
            `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr0);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */  
        
        `$INSTANCE_NAME`_eleCsd0DisconnectFlag = `$INSTANCE_NAME`_DISCONNECT_IO_FLAG;
    }

    return (CYRET_SUCCESS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1SetupWidgetExt
****************************************************************************//**
*
* \brief
*   This API initializes the `$INSTANCE_NAME` CSD1 HW block 
*   with hardware-tuning parameters associated with a specific pair  
*   of widgets.
*
* \details
*   This API initializes the `$INSTANCE_NAME` CSD1 HW block 
*   with hardware-tuning parameters associated with a specific pair  
*   of widgets.
*
* \return Returns the status of operation:
*       Zero     - The `$INSTANCE_NAME` HW block is initialized.
*       Non-zero - The `$INSTANCE_NAME` HW block was busy and 
*                  could not be initialized.
*
*******************************************************************************/
static cystatus `$INSTANCE_NAME`_SsCSD1SetupWidgetExt(void)
{
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt;

    /* Disconnect previous electrode if it has been connected */
    `$INSTANCE_NAME`_SsCSD1ElectrodeCheck();
    
    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
    {       
        /* Initialise ptr to widget structure to appropriate address */
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2WdgtRam;
        
        /* Update global pointer to `$INSTANCE_NAME`_RAM_SNS_STRUCT to current sensor */
        `$INSTANCE_NAME`_curRamSnsPtr1 = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                                                  `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2SnsRam
                                                  + `$INSTANCE_NAME`_sensorIndex1;
        
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) 
            /*  Initialise access pointers for current pointer to widget configuration in Flash */
            `$INSTANCE_NAME`_curFlashWdgtPtr1 = &`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1];
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */
        
        /* Update status register in Data structure */
        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_WDGT1_MASK;
        `$INSTANCE_NAME`_dsRam.status |= ((uint32)`$INSTANCE_NAME`_widgetIndex1 << `$INSTANCE_NAME`_STATUS_WDGT1_SHIFT);
        
        /* Set up scanning resolution */
        `$INSTANCE_NAME`_SsCSD1CalculateScanDuration(ptrWdgt);
                           
        #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) ||\
             (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
            `$INSTANCE_NAME`_SsCSD1ConfigClock();
        #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) ||\
                   (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */   
                           
        /* Setup Idac Value */
        `$INSTANCE_NAME`_SsCSD1SetUpIdacs(ptrWdgt);
        
        /* Initialise ptr to sensor IO structure to appropriate address */        
        `$INSTANCE_NAME`_curSnsIOPtr1 = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2SnsFlash
                                        + `$INSTANCE_NAME`_sensorIndex1;
        
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) 
            /* Save sns pointer */
            `$INSTANCE_NAME`_curFlashSnsPtr1 = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2SnsFlash +
                                               `$INSTANCE_NAME`_sensorIndex1;
 
            /* Check ganged sns flag  */
            if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].staticConfig & 
                `$INSTANCE_NAME`_GANGED_SNS_MASK))
            { 
                /* Setup ISR handler to multiple-sensor scan function with ganged sensors */
                `$INSTANCE_NAME`_ISR1_StartEx(&`$INSTANCE_NAME`_CSD1PostMultiScanGanged);
            }
            else
            {
                /* Set up ISR handler to multiple-sensor scan function without ganged sensors */
                `$INSTANCE_NAME`_ISR1_StartEx(&`$INSTANCE_NAME`_CSD1PostMultiScan);
            }
            
            `$INSTANCE_NAME`_SsCSDConnectSensorExt((uint32)`$INSTANCE_NAME`_widgetIndex1, (uint32)`$INSTANCE_NAME`_sensorIndex1);
        #else
             /* Set up ISR handler to multiple-sensor scan function without ganged sensors */
            `$INSTANCE_NAME`_ISR1_StartEx(&`$INSTANCE_NAME`_CSD1PostMultiScan);
        
            /* Enable sensor */
            `$INSTANCE_NAME`_CSDConnectSns(`$INSTANCE_NAME`_curSnsIOPtr1);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */
        
        `$INSTANCE_NAME`_eleCsd1DisconnectFlag = `$INSTANCE_NAME`_DISCONNECT_IO_FLAG;
    }

    return (CYRET_SUCCESS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetupWidget2x
****************************************************************************//**
*
* \brief
*   This API initializes the `$INSTANCE_NAME` CSD0 and CSD1 HW blocks 
*   with hardware-tuning parameters associated with a specific pair  
*   of widgets.
*
* \details
*   The function reads IDs for widgets and sensors for the current 
*   slot index. Then it sets up the widget on CSD0 HW block and 
*   the widget on CSD1 HW block.
*
* \param  slotIndex specifies ID of the pair of widgets for which 
*  the hardware tuning parameters should be initialized in the 
*  `$INSTANCE_NAME` CSD0 and CSD1 HW blocks.
*
* \return Returns the status of operation:
*       Zero     - The `$INSTANCE_NAME` HW blocks are initialized.
*       Non-zero - The `$INSTANCE_NAME` HW blocks were busy and 
*                  could not be initialized.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetupWidget2x(uint32 slotIndex)
{
    cystatus setupWidget2xStatus = CYRET_SUCCESS;

    /* Configure CSD0 block */
    `$INSTANCE_NAME`_widgetIndex0 = `$INSTANCE_NAME`_scanSlots[slotIndex].csd0WidgetId;
    `$INSTANCE_NAME`_sensorIndex0 = `$INSTANCE_NAME`_scanSlots[slotIndex].csd0SensorId; 
    
    setupWidget2xStatus = `$INSTANCE_NAME`_SsCSD0SetupWidgetExt();
    
    /* Configure CSD1 block */
    `$INSTANCE_NAME`_widgetIndex1 = `$INSTANCE_NAME`_scanSlots[slotIndex].csd1WidgetId;
    `$INSTANCE_NAME`_sensorIndex1 = `$INSTANCE_NAME`_scanSlots[slotIndex].csd1SensorId; 

    setupWidget2xStatus |= `$INSTANCE_NAME`_SsCSD1SetupWidgetExt();

    `$INSTANCE_NAME`_slotIndex = (uint8)slotIndex;
    
    return (setupWidget2xStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanCSD2x
****************************************************************************//**
*
* \brief
*   This API initiates the scanning of the slot with two sensors. These sensors
*   belong to CSD0 and CSD1 HW blocks and are set up by the 
*   `$INSTANCE_NAME`_SetupWidget API in the CSD2x mode.
*
* \details
*   The function sets BUSY flags in status of `$INSTANCE_NAME`_dsRam structure
*   and initiates the scanning of the current slot.
*
*   This API does not support the CSX scanning.
*
* \return Returns the status of operation:
*    Zero     - The `$INSTANCE_NAME` scan is started.
*    Non-zero - The `$INSTANCE_NAME` HW block is busy and scan can't be started.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Scan2x(void)
{
    /* Set Start of slot scan flag */
    `$INSTANCE_NAME`_dsRam.status |= (`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_WDGT_SW_STS_BUSY);
                               
    `$INSTANCE_NAME`_SsCSD2XStartSample();

    return (CYRET_SUCCESS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD2XStartSample
****************************************************************************//**
*
* \brief
*   Starts the CSD conversion.
*
* \details
*   This function assumes that the CSD block is already set up using 
*   the `$INSTANCE_NAME`_CSDSetupWidget API and the sensor port-pin is connected to the CSD 
*   block using `$INSTANCE_NAME`_CSDConnectSns.
*   For CSDv1 the function performs the following tasks:
*   1. Disconnects the Vref buffer from AMUX;
*   2. Precharges Cmod;
*   3. Makes the PreSettling delay to have a stable Vref voltage;
*   4. Sets the resolution to the Counter register to start scanning.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD2XStartSample(void)
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
    {    
         /* Set Start of sensor0 scan flag */
        `$INSTANCE_NAME`_dsRam.status |= (`$INSTANCE_NAME`_STATUS_CSD0_MASK);

        /*  Enable CSD block. Disconnect Vref Buffer from AMUX */
        #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC) &&\
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN))
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG_CSD_EN);
        #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC) &&\
                   (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN)) */
    }

    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
    {
         /* Set Start of sensor0 scan flag */
        `$INSTANCE_NAME`_dsRam.status |= (`$INSTANCE_NAME`_STATUS_CSD1_MASK);

        /*  Enable CSD block. Disconnect Vref Buffer from AMUX */
        #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC) &&\
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN))
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG_CSD_EN);
        #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC) &&\
                   (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN)) */
    }
    
    /* Restart the clocks. Scan one cycle to reset the flip-flop for Direct clock mode */
    `$INSTANCE_NAME`_SsCSD2XClockRestart();

    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
    { 
        `$INSTANCE_NAME`_SsCSD0ScanOneCycle();

        /* Precharging Cmod to Vref */
        `$INSTANCE_NAME`_SsCSD2XCmod0Precharge();
    }
    
    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
    { 
        `$INSTANCE_NAME`_SsCSD1ScanOneCycle();

        /* Precharging Cmod to Vref */
        `$INSTANCE_NAME`_SsCSD2XCmod1Precharge();
    }
    
    #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /* Set PreSettling delay to skip IDAC glitch before scanning */
        CyDelayCycles(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES);
        
        /* Restart sense clock */
        `$INSTANCE_NAME`_SsCSD2XClockRestart();
    #endif /* (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE != `$INSTANCE_NAME`_CLK_SOURCE_DIRECT) */

    /* Trigger Scan */
    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
    {
        `$INSTANCE_NAME`_SsCSD0TriggerScan(); 
    }

    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
    { 
        `$INSTANCE_NAME`_SsCSD1TriggerScan();
    }

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD2XSnsClkRestart
****************************************************************************//**
*
* \brief
*  This function restarts the sense clock.
*
* \details
*  The function performs following:
*  1) Stops SnsClk clock;
*  2) Resets PRS polynominal;
*  3) Starts SnsClk clock.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XSnsClkRestart(void)
{
    /*  Stop sense clock clock   */
    CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR, 
                 ((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID <<
                 `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT)|
                 ((uint32)`$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_MASK));
  
    /*  Reset polynom */
    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | 
                                                       `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG_CSD_EN |
                                                       `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK);
    }
    if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | 
                                                       `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG_CSD_EN | 
                                                       `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK);
    }
  
    /*  Check whether previous sense clock start command has finished. */
    while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) & `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK))
    {
        /*  Wait until previous sense clock start command has finished. */  
    } 
    
    /* Start sense clock aligned to previously started modulator clock. */
    CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR, 
                 (uint32)(((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT) |
                  ((uint32)`$INSTANCE_NAME`_ModClk__PA_DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_PA_DIV_SHIFT) |
                  `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD2XClockRestart
****************************************************************************//**
*
* \brief
*  This function restarts the clocks.
*
* \details
*  The function performs following:
*  1) Stops, sets dividers and starts ModClk clock;
*  2) Stops SnsClk clock;
*  3) Resets PRS polynominal;
*  4) Starts SnsClk clock.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XClockRestart(void)
{
    /*  Stop clocks, set dividers, and start clock to align clock phase */
    `$INSTANCE_NAME`_SsSetModClkClockDivider((uint32)`$INSTANCE_NAME`_dsRam.modCsdClk);   
    
    /* Restart sense clock */
    `$INSTANCE_NAME`_SsCSD2XSnsClkRestart();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0ScanOneCycle
****************************************************************************//**
*
* \brief
*  This function scans one cycle.
*
* \details
*  The function performs following:
*   Scan one cycle to reset the flip-flop for Direct clock mode.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD0ScanOneCycle(void)
{
    #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /*  Scan one cycle to reset the flip-flop for Direct clock mode */
        CyIntDisable(`$INSTANCE_NAME`_ISR0_NUMBER);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_COUNTER_PTR, `$INSTANCE_NAME`_ONE_CYCLE);

        while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_CSD0_COUNTER_PTR) & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
        {
            /* Wait until scanning is complete */ 
        }
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
        CyIntClearPending(`$INSTANCE_NAME`_ISR0_NUMBER);
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1ScanOneCycle
****************************************************************************//**
*
* \brief
*  This function scans one cycle.
*
* \details
*  The function performs following:
*   Scan one cycle to reset the flip-flop for Direct clock mode.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD1ScanOneCycle(void)
{
    #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /*  Scan one cycle to reset the flip-flop for Direct clock mode */
        CyIntDisable(`$INSTANCE_NAME`_ISR1_NUMBER);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_COUNTER_PTR, `$INSTANCE_NAME`_ONE_CYCLE);

        while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_CSD1_COUNTER_PTR) & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
        {
            /* Wait until scanning is complete */ 
        }
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
        CyIntClearPending(`$INSTANCE_NAME`_ISR1_NUMBER);
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD2XCmod0Precharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  For CSDv1:
*  The function initializes the Cmod charging to Vref. 
*  Then it waits the even when Cmod is completely charged
*  to Vref to have stable Rawcounts. Software Watchdog Counter is implemented to 
*  prevent the project hanging.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XCmod0Precharge(void)
{ 
    uint32 newRegValue;
    uint32 watchdogCounter;

    /*  Save the current IDAC configuration */ 
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR);

    /*  Wait until Cmod discharges below Vref */ 
    CyDelayCycles(`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES);
    
    /*  Set the IDAC configuration for fast Cmod precharge to Vref */ 
    CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG);

    #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR) & ~`$INSTANCE_NAME`_CONFIG_POLARITY_MASK);
    #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    
    /*  Init Watchdog Counter to prevent a hang */ 
    watchdogCounter = `$INSTANCE_NAME`_SOFTWARE_WDT_CYCLES_NUM;

    /*  Wait until Cmod reaches to Vref */ 
    while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_CSD0_STATUS_PTR) & `$INSTANCE_NAME`_STATUS_SAMPLE)) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    } 
    
    #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR) | `$INSTANCE_NAME`_CONFIG_POLARITY_MASK);
    #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

    /*  Restore the current IDAC configuration */ 
    CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, newRegValue);

    /*  Enable the sense modulator output */ 
    CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG_CSD_EN | `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK);

    CyIntEnable(`$INSTANCE_NAME`_ISR0_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD2XCmod10Precharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  For CSDv1:
*  The function initializes the Cmod charging to Vref. 
*  Then it waits the even when Cmod is completely charged
*  to Vref to have stable Rawcounts. Software Watchdog Counter is implemented to 
*  prevent the project hanging.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD2XCmod1Precharge(void)
{ 
    uint32 newRegValue;
    uint32 watchdogCounter;

    /*  Save the current IDAC configuration */ 
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR);

    /*  Wait until Cmod discharges below Vref */ 
    CyDelayCycles(`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES);
    
    /*  Set the IDAC configuration for fast Cmod precharge to Vref */ 
    CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG);

    #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR) & ~`$INSTANCE_NAME`_CONFIG_POLARITY_MASK);
    #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */
    
    /*  Init Watchdog Counter to prevent a hang */ 
    watchdogCounter = `$INSTANCE_NAME`_SOFTWARE_WDT_CYCLES_NUM;

    /*  Wait until Cmod reaches to Vref */ 
    while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_CSD1_STATUS_PTR) & `$INSTANCE_NAME`_STATUS_SAMPLE)) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    } 
    
    #if (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR) | `$INSTANCE_NAME`_CONFIG_POLARITY_MASK);
    #endif /* (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG) */

    /*  Restore the current IDAC configuration */ 
    CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, newRegValue);

    /*  Enable the sense modulator output */ 
    CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG_CSD_EN | `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK);

    CyIntEnable(`$INSTANCE_NAME`_ISR1_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0TriggerScan
****************************************************************************//**
*
* \brief
*  This function triggers the scanning.
*
* \details
*  For CSDv1:
*  Writes resolution to start the scanning.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD0TriggerScan(void)
{ 
    /* Set resolution to Counter register to start scanning */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD0_COUNTER_PTR, `$INSTANCE_NAME`_counterResolution0);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1TriggerScan1
****************************************************************************//**
*
* \brief
*  This function triggers the scanning.
*
* \details
*  For CSDv1:
*  Writes resolution to start the scanning.
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsCSD1TriggerScan(void)
{ 
    /* Set resolution to Counter register to start scanning */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD1_COUNTER_PTR, `$INSTANCE_NAME`_counterResolution1);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDConnectSensorExt
****************************************************************************//**
*
* \brief
*  Connects a ganged sensor port-pin to the CapSense block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and 
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and 
*   PC registers.
*
* \param
*   wdgtIndex Specifies ID of the widget.
*   sensorIndex Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDConnectSensorExt(uint32 wdgtIndex, uint32 sensorIndex)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
        `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
    
    /*  Initialise ptr to sensor IO structure to appropriate address */  
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                      `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash 
                                                      + sensorIndex;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if (`$INSTANCE_NAME`_GANGED_SNS_MASK ==
           (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].staticConfig &
            `$INSTANCE_NAME`_GANGED_SNS_MASK))
        {
            /* Get sns pointer */
            curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash +
                                               sensorIndex;

            /* Get number of ganged pins */
            tempVal = curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            curSnsIOPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];

            /* Connect all ganged sensors  */
            do
            {
                `$INSTANCE_NAME`_CSDConnectSns(curSnsIOPtr);
                curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Connect sensor */
            `$INSTANCE_NAME`_CSDConnectSns(curSnsIOPtr);
        }
    #else
        /* Connect sensor */
        `$INSTANCE_NAME`_CSDConnectSns(curSnsIOPtr);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDDisconnectSnsExt
****************************************************************************//**
*
* \brief
*  Disconnects a ganged sensor port-pin from the CapSense block and AMUX bus. 
*  Sets the default state of the un-scanned sensor.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and 
*   masks from the FLASH_IO_STRUCT object. Basing on this data and Inactive sensor  
*   connection parameter, it updates the HSIOM, PC and DR registers. 
*   The HSIOM register is updated only when the Inactive sensor connection parameter
*   is set to Shield.
*
* \param  snsAddrPtr
*   wdgtIndex Specifies ID of the widget.
*   sensorIndex Specifies ID of the sensor in the widget.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSDDisconnectSnsExt(uint32 wdgtIndex, uint32 sensorIndex)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        uint32 tempVal;
        `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

    /*  Initialise ptr to sensor IO structure to appropriate address */  
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                      `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash 
                                                      + sensorIndex;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
        /* Check ganged sns flag  */
        if ((`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].staticConfig &
            `$INSTANCE_NAME`_GANGED_SNS_MASK) == `$INSTANCE_NAME`_GANGED_SNS_MASK)
        {
            /* Get sns pointer */
            curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash +
                                               sensorIndex;

            /* Get number of ganged pins */
            tempVal = curFlashSnsPtr->numPins;

            /* Get IO pointer  */
            curSnsIOPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];

            /* Disconnect all ganged sensors */
            do
            {
                `$INSTANCE_NAME`_CSDDisconnectSns(curSnsIOPtr);
                curSnsIOPtr++;
                tempVal--;
            } while (0u != tempVal);
        }
        else
        {
            /* Disconnect ganged sensor */
            `$INSTANCE_NAME`_CSDDisconnectSns(curSnsIOPtr);
        }
    #else
        /* Disconnect ganged sensor */
        `$INSTANCE_NAME`_CSDDisconnectSns(curSnsIOPtr); 
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSDConnectSns
****************************************************************************//**
*
* \brief
*  Connects a sensor port-pin to the CapSense block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and 
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and 
*   PC registers.
*
* \param  snsAddrPtr
*   Indicates the pointer to the FLASH_IO_STRUCT object belonging
*   to a sensor which should be connected to the CapSense block.
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
*  Disconnects a sensor port-pin from the CapSense block and AMUX bus. Sets the
*   default state of the un-scanned sensor.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and 
*   masks from the FLASH_IO_STRUCT object. Basing on this data and Inactive sensor  
*   connection parameter, it updates the HSIOM, PC and DR registers. 
*   The HSIOM register is updated only when the Inactive sensor connection parameter
*   is set to Shield.
*
* \param  snsAddrPtr
*   Indicates the pointer to the FLASH_IO_STRUCT object belonging
*   to a sensor which should be disconnected to the CapSense block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSDDisconnectSns(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *snsAddrPtr)
{
    uint32 pinHSIOMShift;
    uint32 newRegisterValue;
    uint32 pinModeShift;

    #if (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
        uint8  interruptState;
    #endif /* (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION) */
    
    pinHSIOMShift = (uint32)snsAddrPtr->hsiomShift;
    pinModeShift = (uint32)snsAddrPtr->shift;
 
    #if (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
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
    #endif /* (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0SetModeSnsClockDivider
****************************************************************************//**
*
* \brief
*   Sets sense source and Sense Clock Divider
*
* \details
*   For CSDv2: Updates `$INSTANCE_NAME`_SENSE_PERIOD register with 
*   sense source and Sense Clock Divider.
*   For CSDv1: Updates `$INSTANCE_NAME`_configCsd variable with 
*   sense source and sets sense clock divider.
*
* \param
*   snsClkSource The sense source for the sense clock.
* \param
*   snsClkDivider The divider value for the sense clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD0SetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider)
{
    /* Set configuration */
    `$INSTANCE_NAME`_configCsd0 &= ~(`$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK | `$INSTANCE_NAME`_CSD_PRS_12_BIT);
    `$INSTANCE_NAME`_configCsd0 |= snsClkSource;

    /* Set sense clock divider */
    `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1SetModeSnsClockDivider
****************************************************************************//**
*
* \brief
*   Sets sense source and Sense Clock Divider
*
* \details
*   For CSDv2: Updates `$INSTANCE_NAME`_SENSE_PERIOD register with 
*   sense source and Sense Clock Divider.
*   For CSDv1: Updates `$INSTANCE_NAME`_configCsd variable with 
*   sense source and sets sense clock divider.
*
* \param
*   snsClkSource The sense source for the sense clock.
* \param
*   snsClkDivider The divider value for the sense clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD1SetModeSnsClockDivider(uint32 snsClkSource, uint32 snsClkDivider)
{
    /* Set configuration */
    `$INSTANCE_NAME`_configCsd1 &= ~(`$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK | `$INSTANCE_NAME`_CSD_PRS_12_BIT);
    `$INSTANCE_NAME`_configCsd1 |= snsClkSource;

    /* Set sense clock divider */
    `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0ConfigClock
****************************************************************************//**
*
* \brief
*  This function configure sense clock for different modes. 
*
* \details
*  Function sets the clock divider and configures the mode based on configuration.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD0ConfigClock(void)
{
    uint32 snsClkDivider;
    uint32 newRegValue;

    #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) || \
         (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt0 = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                 `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2WdgtRam;
    #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) || \
               (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */

    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt1 = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                 `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2WdgtRam;
        uint32 newRegValue1;        
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
    
    /* Get sense divider based on configuration */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = (uint32)`$INSTANCE_NAME`_dsRam.snsCsdClk;
    #else
        #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                         `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            /*  Get SnsClck divider for rows or columns */
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].numCols <= `$INSTANCE_NAME`_sensorIndex0)
            {
                snsClkDivider = (uint32)(ptrWdgt0->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt0->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt0->snsClk);
        #endif /*  (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                                `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /* Get sense clk source calculated in `$INSTANCE_NAME`_SsCSDInitialize() before */
        #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                         `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            /*  Get SnsClc Source for rows or columns */
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].numCols <= `$INSTANCE_NAME`_sensorIndex0)
            {
                newRegValue = (uint32)ptrWdgt0->rowSnsClkSource;
            }
            else
            {
                newRegValue = (uint32)ptrWdgt0->snsClkSource;
            }
        #else
            newRegValue = (uint32)ptrWdgt0->snsClkSource;
        #endif /*  (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                                `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */
                                                
        /* Make sure that both scan clots have the same clock source */
        if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
        {
            /* Get sense clk source calculated in `$INSTANCE_NAME`_SsCSDInitialize() before */
            #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                             `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
                /*  Get SnsClc Source for rows or columns */
                if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].numCols <= `$INSTANCE_NAME`_sensorIndex1)
                {
                    newRegValue1 = (uint32)ptrWdgt1->rowSnsClkSource;
                }
                else
                {
                    newRegValue1 = (uint32)ptrWdgt1->snsClkSource;
                }
            #else
                newRegValue1 = (uint32)ptrWdgt1->snsClkSource;
            #endif /*  (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                                    `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */

            /* Set the lowest polynom to both slots */
            if (newRegValue1 < newRegValue)
            {
                newRegValue = newRegValue1;
            }       
        }                                        
    #else
        newRegValue = `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

    #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
        /* Use direct clock if pre-scalers have not been tuned */
        if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_prescalersTuningDone)
        {
            `$INSTANCE_NAME`_SsCSD0SetModeSnsClockDivider(newRegValue, snsClkDivider);
        }
        else
        {
            `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);
        }
    #else    
        `$INSTANCE_NAME`_SsCSD0SetModeSnsClockDivider(newRegValue, snsClkDivider);  
    #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1ConfigClock
****************************************************************************//**
*
* \brief
*  This function configure sense clock for different modes. 
*
* \details
*  Function sets the clock divider and configures the mode based on configuration.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD1ConfigClock(void)
{
    uint32 snsClkDivider;
    uint32 newRegValue;

    #if ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) || \
         (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt1 = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                 `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2WdgtRam;
    #endif /* ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) || \
               (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)) */

    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt0 = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                 `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2WdgtRam;
        uint32 newRegValue0;        
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
               
    /* Get sense divider based on configuration */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
        snsClkDivider = (uint32)`$INSTANCE_NAME`_dsRam.snsCsdClk;
    #else
        #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                         `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            /*  Get SnsClck divider for rows or columns */
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].numCols <= `$INSTANCE_NAME`_sensorIndex1)
            {
                snsClkDivider = (uint32)(ptrWdgt1->rowSnsClk);
            }
            else
            {
                snsClkDivider = (uint32)(ptrWdgt1->snsClk);
            }
        #else
            snsClkDivider = (uint32)(ptrWdgt1->snsClk);
        #endif /*  (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                                `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /* Get sense clk source calculated in `$INSTANCE_NAME`_SsCSDInitialize() before */
        #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                         `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            /*  Get SnsClc Source for rows or columns */
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].numCols <= `$INSTANCE_NAME`_sensorIndex1)
            {
                newRegValue = (uint32)ptrWdgt1->rowSnsClkSource;
            }
            else
            {
                newRegValue = (uint32)ptrWdgt1->snsClkSource;
            }
        #else
            newRegValue = (uint32)ptrWdgt1->snsClkSource;
        #endif /*  (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                                `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */
                                                
        /* Make sure that both scan clots have the same clock source */
        if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
        {
            /* Get sense clk source calculated in `$INSTANCE_NAME`_SsCSDInitialize() before */
            #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                             `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
                /*  Get SnsClc Source for rows or columns */
                if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].numCols <= `$INSTANCE_NAME`_sensorIndex0)
                {
                    newRegValue0 = (uint32)ptrWdgt0->rowSnsClkSource;
                }
                else
                {
                    newRegValue0 = (uint32)ptrWdgt0->snsClkSource;
                }
            #else
                newRegValue0 = (uint32)ptrWdgt0->snsClkSource;
            #endif /*  (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | \
                                                    `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */

            /* Set the lowest polynom to both slots */
            if (newRegValue0 < newRegValue)
            {
                newRegValue = newRegValue0;
            }       
        }                                       
    #else
        newRegValue = `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

    #if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
        /* Use direct clock if pre-scalers have not been tuned */
        if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_prescalersTuningDone)
        {
            `$INSTANCE_NAME`_SsCSD1SetModeSnsClockDivider(newRegValue, snsClkDivider);
        }
        else
        {
            `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);
        }
    #else    
        `$INSTANCE_NAME`_SsCSD1SetModeSnsClockDivider(newRegValue, snsClkDivider);  
    #endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD0CalculateScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by scan resolution
*
* \details
*   The function recalculate the resolution using following equation:
*   2^resolution - 1. The calculated value is contained in 
*   `$INSTANCE_NAME`_counterResolution global variable and used in 
*   `$INSTANCE_NAME`_SsCSDStartSample() function to trigger the scan process.
*
* \param
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD0CalculateScanDuration(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt)
{   
    /*  Set up scanning resolution  */
    `$INSTANCE_NAME`_counterResolution0 = (uint32)((0x00000001Lu << ptrWdgt->resolution) - 1u) << `$INSTANCE_NAME`_RESOLUTION_OFFSET;
}  


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSD1CalculateScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by scan resolution
*
* \details
*   The function recalculate the resolution using following equation:
*   2^resolution - 1. The calculated value is contained in 
*   `$INSTANCE_NAME`_counterResolution global variable and used in 
*   `$INSTANCE_NAME`_SsCSDStartSample() function to trigger the scan process.
*
* \param 
*  ptrWdgt The pointer to the RAM_WD_BASE_STRUCT structure.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsCSD1CalculateScanDuration(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt)
{   
    /*  Set up scanning resolution  */
    `$INSTANCE_NAME`_counterResolution1 = (uint32)((0x00000001Lu << ptrWdgt->resolution) - 1u) << `$INSTANCE_NAME`_RESOLUTION_OFFSET;
} 


#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDCalibrateCheck
    ****************************************************************************//**
    *
    * \brief
    *  This internal function checks if the calibration is performed successfully.
    *
    * \details
    *   The function shifts the rawLevel to 16 to implement the integer mathematics.
    * 
    * \param rawLevel The raw data level which should be reached during the 
    *   calibration procedure.
    * \param rawData  Calibrated raw counts.
    *
    * \return Returns the status of operation: 
    *   - Zero     - All the sensors in the widget are calibrated successfully.
    *   - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus `$INSTANCE_NAME`_SsCSDCalibrateCheck(uint32 rawLevel, uint32 rawData)
    {
        cystatus calibrateStatus;
        uint32 minRawLevel;
        uint32 maxRawLevel;

        /* Check if calibration is in valid range */
        minRawLevel = (uint32)((uint32)rawLevel * `$INSTANCE_NAME`_IDAC_MOD_MIN_CALIB_ERROR_MULT);
        maxRawLevel = (uint32)((uint32)rawLevel * `$INSTANCE_NAME`_IDAC_MOD_MAX_CALIB_ERROR_MULT);

        if (((rawData << `$INSTANCE_NAME`_IDAC_MOD_MAX_INT_MATH_SHIFT) < minRawLevel) || 
            ((rawData << `$INSTANCE_NAME`_IDAC_MOD_MAX_INT_MATH_SHIFT) > maxRawLevel))
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
    * Function Name: `$INSTANCE_NAME`_SsCSD0SetSingleIdacMode
    ****************************************************************************//**
    *
    * \brief
    *  This function set single IDAC mode for CSD0 HW block.
    *
    * \details
    *   For CSDv1: The function enables Modulator IDAC only in variable mode.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSD0SetSingleIdacMode(void)
    {
        uint32 newRegValue;
    
        /* Enable Modulator IDAC only in variable mode */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR) & 
                      ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | `$INSTANCE_NAME`_IDAC_COMP_MODE_MASK);
        newRegValue |= `$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE;
         CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, newRegValue);
    }

    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD1SetSingleIdacMode
    ****************************************************************************//**
    *
    * \brief
    *  This function set single IDAC mode for CSD1 HW block.
    *
    * \details
    *   For CSDv1: The function enables Modulator IDAC only in variable mode.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSD1SetSingleIdacMode(void)
    {
        uint32 newRegValue;
    
        /* Enable Modulator IDAC only in variable mode */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR) & 
                      ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | `$INSTANCE_NAME`_IDAC_COMP_MODE_MASK);
        newRegValue |= `$INSTANCE_NAME`_IDAC_MOD_MODE_VARIABLE;
         CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, newRegValue);
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD0RestoreIdacMode
    ****************************************************************************//**
    *
    * \brief
    *  This function restores IDAC configuration for CSD0 HW block.
    *
    * \details
    *   The function restores Compensation IDAC if it is enabled.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSD0RestoreIdacMode(void)
    {
        /* Restore IDAC configuration */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_CONFIG);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR) &
                                                                ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | 
                                                                  `$INSTANCE_NAME`_IDAC_MOD_MASK));
            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD0_IDAC_PTR) | 
                                                                `$INSTANCE_NAME`_DEFAULT_CSD0_IDAC_CONFIG);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD1RestoreIdacMode
    ****************************************************************************//**
    *
    * \brief
    *  This function restores IDAC configuration for CSD0 HW block.
    *
    * \details
    *   The function restores Compensation IDAC if it is enabled.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsCSD1RestoreIdacMode(void)
    {
        /* Restore IDAC configuration */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_CONFIG);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR) &
                                                                ~(`$INSTANCE_NAME`_IDAC_MOD_MODE_MASK | 
                                                                  `$INSTANCE_NAME`_IDAC_MOD_MASK));
            CY_SET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CSD1_IDAC_PTR) | 
                                                                `$INSTANCE_NAME`_DEFAULT_CSD1_IDAC_CONFIG);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD0StartSample
    ****************************************************************************//**
    *
    * \brief
    *   Starts the CSD0 HW block conversion in blocking mode.
    *
    * \details
    *   This function assumes that the CSD block is already set up using 
    *   the `$INSTANCE_NAME`_CSDSetupWidget API and the sensor port-pin is connected to the CSD 
    *   block using `$INSTANCE_NAME`_CSDConnectSns.
    *   For CSDv1 the function performs the following tasks:
    *   1. Disconnects the Vref buffer from AMUX;
    *   2. Precharges Cmod;
    *   3. Makes the PreSettling delay to have a stable Vref voltage;
    *   4. Sets the resolution to the Counter register to start scanning.
    *
    * \return Returns rawcounts
    *
    *******************************************************************************/
    static uint32 `$INSTANCE_NAME`_SsCSD0StartSample(void)
    {
        uint8 interruptState;
        uint32 watchdogCounter;

        interruptState = CyEnterCriticalSection();

        if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex0) 
        {
            /*  Enable CSD block. Disconnect Vref Buffer from AMUX */
            #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC) &&\
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN))
                CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0 | `$INSTANCE_NAME`_CTANK0_PRECHARGE_CONFIG_CSD_EN);
            #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD0_CSH_PRECHARGE_SRC) &&\
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD0_SHIELD_TANK_EN)) */
        
            /* Restart the clocks. Scan one cycle to reset the flip-flop for Direct clock mode */
            `$INSTANCE_NAME`_SsCSD2XClockRestart();

            /* Reset trigger */
            `$INSTANCE_NAME`_SsCSD0ScanOneCycle();

            /* Precharging Cmod to Vref */
            `$INSTANCE_NAME`_SsCSD2XCmod0Precharge();

            #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
                /* Set PreSettling delay to skip IDAC glitch before scanning */
                CyDelayCycles(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES);
            #endif /* (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE != `$INSTANCE_NAME`_CLK_SOURCE_DIRECT) */
      
            CyIntDisable(`$INSTANCE_NAME`_ISR0_NUMBER);

            /* Trigger Scan */
            `$INSTANCE_NAME`_SsCSD0TriggerScan(); 
        }
        
        CyExitCriticalSection(interruptState);
        
        /* Initialize Watchdog Counter with time interval which is enough to charge 100 nF capacitor */
        watchdogCounter = `$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM;
        
        while ((0u != (CY_GET_REG32(`$INSTANCE_NAME`_CSD0_COUNTER_PTR) & `$INSTANCE_NAME`_RESOLUTION_16_BITS)) &&
               (0u != watchdogCounter))
        {
            /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
            watchdogCounter--;
        }
        
        CY_SET_REG32(`$INSTANCE_NAME`_CSD0_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
        CyIntClearPending(`$INSTANCE_NAME`_ISR0_NUMBER);
        
        /* Read Rawdata */
        `$INSTANCE_NAME`_curRamSnsPtr0->raw[`$INSTANCE_NAME`_scanFreqIndex] = (uint16)CY_GET_REG32(`$INSTANCE_NAME`_CSD0_COUNTER_PTR);
        
        return ((uint32)`$INSTANCE_NAME`_curRamSnsPtr0->raw[`$INSTANCE_NAME`_scanFreqIndex]);
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD1StartSample
    ****************************************************************************//**
    *
    * \brief
    *   Starts the CSD1 HW block conversion in blocking mode.
    *
    * \details
    *   This function assumes that the CSD block is already set up using 
    *   the `$INSTANCE_NAME`_CSDSetupWidget API and the sensor port-pin is connected to the CSD 
    *   block using `$INSTANCE_NAME`_CSDConnectSns.
    *   For CSDv1 the function performs the following tasks:
    *   1. Disconnects the Vref buffer from AMUX;
    *   2. Precharges Cmod;
    *   3. Makes the PreSettling delay to have a stable Vref voltage;
    *   4. Sets the resolution to the Counter register to start scanning.
    *
    * \return Returns rawcounts
    *
    *******************************************************************************/
    static uint32 `$INSTANCE_NAME`_SsCSD1StartSample(void)
    {
        uint8 interruptState;
        uint32 watchdogCounter;

        interruptState = CyEnterCriticalSection();

        if (`$INSTANCE_NAME`_EMPTY_SLOT != `$INSTANCE_NAME`_widgetIndex1) 
        {
            /*  Enable CSD block. Disconnect Vref Buffer from AMUX */
            #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC) &&\
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN))
                CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG_CSD_EN);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1 | `$INSTANCE_NAME`_CTANK1_PRECHARGE_CONFIG_CSD_EN);
            #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD1_CSH_PRECHARGE_SRC) &&\
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD1_SHIELD_TANK_EN)) */
        
            /* Restart the clocks. Scan one cycle to reset the flip-flop for Direct clock mode */
            `$INSTANCE_NAME`_SsCSD2XClockRestart();

            /* Reset trigger */
            `$INSTANCE_NAME`_SsCSD1ScanOneCycle();

            /* Precharging Cmod to Vref */
            `$INSTANCE_NAME`_SsCSD2XCmod1Precharge();

            #if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
                /* Set PreSettling delay to skip IDAC glitch before scanning */
                CyDelayCycles(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES);
            #endif /* (`$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE != `$INSTANCE_NAME`_CLK_SOURCE_DIRECT) */
      
            CyIntDisable(`$INSTANCE_NAME`_ISR1_NUMBER);

            /* Trigger Scan */
            `$INSTANCE_NAME`_SsCSD1TriggerScan(); 
        }
        
        CyExitCriticalSection(interruptState);
        
        /* Initialize Watchdog Counter with time interval which is enough to charge 100 nF capacitor */
        watchdogCounter = `$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM;
        
        while ((0u != (CY_GET_REG32(`$INSTANCE_NAME`_CSD1_COUNTER_PTR) & `$INSTANCE_NAME`_RESOLUTION_16_BITS)) &&
               (0u != watchdogCounter))
        {
            /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
            watchdogCounter--;
        }

        CY_SET_REG32(`$INSTANCE_NAME`_CSD1_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
        CyIntClearPending(`$INSTANCE_NAME`_ISR1_NUMBER);
        
        /* Read Rawdata */
        `$INSTANCE_NAME`_curRamSnsPtr1->raw[`$INSTANCE_NAME`_scanFreqIndex] = (uint16)CY_GET_REG32(`$INSTANCE_NAME`_CSD1_COUNTER_PTR);
        
        return ((uint32)`$INSTANCE_NAME`_curRamSnsPtr1->raw[`$INSTANCE_NAME`_scanFreqIndex]);
    }
    
    
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD0CalibrateOneSensor
    ****************************************************************************//**
    *
    * \brief
    *  Computes the Modulator IDAC value for one sensor that provides raw signal at
    *  the specified level.
    *
    * \details
    *   The function performs the following tasks:
    *   1. Initialises The Compensation IDAC to zero
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
    * \param  iDAC8Max The pointer to the maximum IDAC value in the widget.
    * \return Returns the status of operation: 
    *  - Zero     - All the sensors in the widget are calibrated successfully.
    *  - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus `$INSTANCE_NAME`_SsCSD0CalibrateOneSensor(uint32 rawLevel, uint8 *iDAC8Max)
    {
        cystatus calibrateStatus;
        uint32 rawData0;
        uint8 calMask = (uint8)`$INSTANCE_NAME`_CAL_MIDDLE_BIT;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            uint32 rawData1;
            uint32 rawData2;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        uint8 *ptrIdac;
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

        `$INSTANCE_NAME`_widgetIndex0 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd0WidgetId;
        `$INSTANCE_NAME`_sensorIndex0 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd0SensorId; 

        /*  Initialise ptr to widget and sensor structures to appropriate address        */
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                   `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2WdgtRam;
                                
        /* Init pointer to Modulator IDAC */
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex0)].numCols <= `$INSTANCE_NAME`_sensorIndex0)
            {
                ptrIdac = &ptrWdgt->rowIdacMod[0u];
            }
            else
            {
                ptrIdac = &ptrWdgt->idacMod[0u];
            }
        #else
            ptrIdac = &ptrWdgt->idacMod[0u];
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */                                
                                           
        /* Init compensation IDAC */
        ptrIdac[0u] = calMask;
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = calMask;
            ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = calMask;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

        /* Setup widget0 for current slot */
        calibrateStatus = `$INSTANCE_NAME`_SsCSD0SetupWidgetExt();
        
        /* Set single IDAC mode */
        `$INSTANCE_NAME`_SsCSD0SetSingleIdacMode();
        
        /* 
         * Perform the iteration steps to get target = rawLevel. 
         * The number of iteration steps is defined by calMask and depend on IDAC resolution. 
         */
        do
        {
            /* Read rawData */
            rawData0 = `$INSTANCE_NAME`_SsCSD0StartSample();
            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_1;
                `$INSTANCE_NAME`_SsChangeImoFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_1);
                rawData1 = `$INSTANCE_NAME`_SsCSD0StartSample();
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_2;
                `$INSTANCE_NAME`_SsChangeImoFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_2);
                rawData2 = `$INSTANCE_NAME`_SsCSD0StartSample();
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /* Decrease IDAC until rawData reaches rawLevel */ 
            if (rawData0 < rawLevel)
            {
                /* Reset bit for null channel (decrease IDAC -> will increase rawData) */ 
                ptrIdac[0u] &= (uint8)(~calMask);
            }
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                if (rawData1 < rawLevel)
                {
                    /* Reset bit for null channel  */ 
                    ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] &= (uint8)(~calMask);
                }
                if (rawData2 < rawLevel)
                {
                    /* Reset bit for null channel  */ 
                    ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] &= (uint8)(~calMask);
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /* Shift calMask to set or reset next bit */
            calMask >>= 1u;
            
            /* Set bit for null channel */
            ptrIdac[0u] |= calMask;
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] |= calMask;
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] |= calMask;     
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            
            /* Update IDAC */
            `$INSTANCE_NAME`_SsCSD0SetUpIdacs(ptrWdgt);
        }
        while (calMask > 0u);
        
        /* Restore IDAC configuration to default state */
        `$INSTANCE_NAME`_SsCSD0RestoreIdacMode();
        
        /* Check if IDAC is in correct range */
        calibrateStatus = `$INSTANCE_NAME`_SsCSDCalibrateCheck(rawLevel, rawData0);
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateCheck(rawLevel, rawData1);
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateCheck(rawLevel, rawData2);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
     
        /* 
         * Update maximum IDAC value in widget. iDAC8Max variable will contain 
         * maximum IDAC value after all sensors in widget have been scanned.  
         */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_0] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_0])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_0] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_0];
            }   
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
            }
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            }
        #else
            if (*iDAC8Max < ptrIdac[0u])
            {
                *iDAC8Max = ptrIdac[0u];
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /* 
             * Store temporary ModIDAC8 value (in single-IDAC mode) in idacComp variable.
             * We need this value to calculate idacMod value the in the dual-IDAC mode.  
             */
            `$INSTANCE_NAME`_curRamSnsPtr0->idacComp[0u] = ptrIdac[0u];
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                `$INSTANCE_NAME`_curRamSnsPtr0->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                `$INSTANCE_NAME`_curRamSnsPtr0->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */ 
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
     
        return (calibrateStatus);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSD1CalibrateOneSensor
    ****************************************************************************//**
    *
    * \brief
    *  Computes the Modulator IDAC value for one sensor that provides raw signal at
    *  the specified level.
    *
    * \details
    *   The function performs the following tasks:
    *   1. Initialises the Compensation IDAC to zero
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
    * \param  iDAC8Max The pointer to the maximum IDAC value in the widget.
    * \return Returns the status of operation: 
    *  - Zero     - All the sensors in the widget are calibrated successfully.
    *  - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    static cystatus `$INSTANCE_NAME`_SsCSD1CalibrateOneSensor(uint32 rawLevel, uint8 *iDAC8Max)
    {
        cystatus calibrateStatus;
        uint32 rawData0;
        uint8 calMask = (uint8)`$INSTANCE_NAME`_CAL_MIDDLE_BIT;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            uint32 rawData1;
            uint32 rawData2;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        uint8 *ptrIdac;
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

        `$INSTANCE_NAME`_widgetIndex1 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd1WidgetId;
        `$INSTANCE_NAME`_sensorIndex1 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd1SensorId; 

        /*  Initialise ptr to widget and sensor structures to appropriate address        */
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                                        `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2WdgtRam;
                                
        /* Init pointer to Modulator IDAC */
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[(`$INSTANCE_NAME`_widgetIndex1)].numCols <= `$INSTANCE_NAME`_sensorIndex1)
            {
                ptrIdac = &ptrWdgt->rowIdacMod[0u];
            }
            else
            {
                ptrIdac = &ptrWdgt->idacMod[0u];
            }
        #else
            ptrIdac = &ptrWdgt->idacMod[0u];
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */                                
                                           
        /* Init compensation IDAC */
        ptrIdac[0u] = calMask;
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = calMask;
            ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = calMask;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

        /* Set single IDAC mode */
        `$INSTANCE_NAME`_SsCSD1SetSingleIdacMode();

        /* Setup widget0 for current slot */
        calibrateStatus = `$INSTANCE_NAME`_SsCSD1SetupWidgetExt();
        
        /* 
         * Perform the iteration steps to get target = rawLevel. 
         * The number of iteration steps is defined by calMask and depend on IDAC resolution. 
         */
        do
        {

            /* Read rawData */
            rawData0 = `$INSTANCE_NAME`_SsCSD1StartSample();
            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_1;
                `$INSTANCE_NAME`_SsChangeImoFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_1);
                rawData1 = `$INSTANCE_NAME`_SsCSD1StartSample();
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_2;
                `$INSTANCE_NAME`_SsChangeImoFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_2);
                rawData2 = `$INSTANCE_NAME`_SsCSD1StartSample();
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;   
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /* Decrease IDAC until rawData reaches rawLevel */ 
            if (rawData0 < rawLevel)
            {
                /* Reset bit for null channel (decrease IDAC -> will increase rawData) */ 
                ptrIdac[0u] &= (uint8)(~calMask);
            }
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                if (rawData1 < rawLevel)
                {
                    /* Reset bit for null channel  */ 
                    ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] &= (uint8)(~calMask);
                }
                if (rawData2 < rawLevel)
                {
                    /* Reset bit for null channel  */ 
                    ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] &= (uint8)(~calMask);
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

            /* Shift calMask to set or reset next bit */
            calMask >>= 1u;
            
            /* Set bit for null channel */
            ptrIdac[0u] |= calMask;
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1] |= calMask;
                ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2] |= calMask;     
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            
            /* Update IDAC */
            `$INSTANCE_NAME`_SsCSD1SetUpIdacs(ptrWdgt);
        }
        while (calMask > 0u);
        
        /* Restore IDAC configuration to default state */
        `$INSTANCE_NAME`_SsCSD1RestoreIdacMode();
        
        /* Check if IDAC is in correct range */
        calibrateStatus = `$INSTANCE_NAME`_SsCSDCalibrateCheck(rawLevel, rawData0);
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateCheck(rawLevel, rawData1);
            calibrateStatus |= `$INSTANCE_NAME`_SsCSDCalibrateCheck(rawLevel, rawData2);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
     
        /* 
         * Update maximum IDAC value in widget. iDAC8Max variable will contain 
         * maximum IDAC value after all sensors in widget have been scanned.  
         */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_0] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_0])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_0] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_0];
            }   
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
            }
            if (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] < ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2])
            {
                iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            }
        #else
            if (*iDAC8Max < ptrIdac[0u])
            {
                *iDAC8Max = ptrIdac[0u];
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
        
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /* 
             * Store temporary ModIDAC8 value (in single-IDAC mode) in idacComp variable.
             * We need this value to calculate idacMod value the in the dual-IDAC mode.  
             */
            `$INSTANCE_NAME`_curRamSnsPtr1->idacComp[0u] = ptrIdac[0u];
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                `$INSTANCE_NAME`_curRamSnsPtr1->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                `$INSTANCE_NAME`_curRamSnsPtr1->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */ 
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
     
        return (calibrateStatus);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CSDCalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Executes IDAC calibration for all sensors in the widget specified in an input.
    *
    * \details
    *   There are two IDAC modes: the single-IDAC mode and the dual-IDAC mode.
    *   In the single-IDAC mode Modulator IDAC is enabled only. 
    *   In the dual-IDAC mode both Modulator and Compensation IDACs are enabled. 
    *
    *   The calibration in the single-IDAC mode:
    *   1. Calibrate the IDAC for all the sensors (IDAC in in 8-bit mode);
    *   2. Identify the maximum IDAC value (highest Cp sensor), then apply the same 
    *      values for all the sensors.
    *   
    *   The calibration in the dual-IDAC mode:
    *   1. Find the 8-bit IDAC values (iDAC8(i)) for each sensor to set 
    *      Raw Count of respective sensor to 85% of full-scale value.
    *   2. Identify the maximum IDAC value (highest Cp sensor - iDAC8Max).
    *   3. Calculate modulator IDAC for all sensors in the widget to be equal to
    *      50% max iDAC8Max value (idacMod = iDAC8Max/2 + 1). 
    *      Note: we add 1 to always have idacMod >= idacComp;
    *   4. Find compensation IDAC for each sensor using following equation:
    *      idacComp(i) = (iDAC8(i) - idacMod) * target.
    *   idacComp must be different to maintain the same raw count level for all the 
    *   sensors.
    *
    *  This function does not check the CSD or CSX widget type.
    *   
    * \param wdgtIndex The Id of the widget which should be calibrated.
    * \param target    Percentage of the maximum to calibrate to.
    * \return Returns the status of operation: 
    *   - Zero     - All the sensors in the widget are calibrated successfully.
    *   - Non-Zero - Calibration failed for any sensor in the widget.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_CSD2XCalibrateWidget(uint32 wdgtIndex, uint32 target)
    {
        uint32 rawLevel;
        uint32 csdBlockID;
        uint32 snsIndex;
        cystatus calibrateStatus = CYRET_SUCCESS;
        
        /*  Declare and initialize ptr to widget and sensor structures to appropriate address        */
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                              `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;
        uint8 iDAC8Max[`$INSTANCE_NAME`_NUM_SCAN_FREQS] = {0u};
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            uint8 rowIDAC8Max[`$INSTANCE_NAME`_NUM_SCAN_FREQS] = {0u};
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
        uint8 *ptrIdacMax;
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            uint8 *ptrIdac;
            `$INSTANCE_NAME`_RAM_SNS_STRUCT *curRamSnsPtr;
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
  
        /* Calibrate maximum level for given resolution */
        rawLevel = (0x00000001Lu << ptrWdgt->resolution);
        
        /* Calculate percentage of maximum value */
        rawLevel = (rawLevel * target) / `$INSTANCE_NAME`_PERCENTAGE_100;

        csdBlockID = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].csdblk;

        /* Go through all sensors (or columns of touchpad) of widget to calibrate them */
        for (snsIndex = 0u; 
             snsIndex < `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].totalNumSns;
             snsIndex++)
        {
            /* Calculate slot Index */
            `$INSTANCE_NAME`_slotIndex = (uint8)(`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].slotIndex + snsIndex);

            #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                if (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].numCols <= snsIndex)
                {
                    ptrIdacMax = rowIDAC8Max;
                }
                else
                {
                    ptrIdacMax = iDAC8Max;
                }
            #else
                ptrIdacMax = iDAC8Max;
            #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

            if (`$INSTANCE_NAME`_CSD0_BLOCK_ID == csdBlockID)
            {
                /* Calibrate current sensor in widget */
                calibrateStatus |= `$INSTANCE_NAME`_SsCSD0CalibrateOneSensor(rawLevel, ptrIdacMax);
            } 
            else
            {
                calibrateStatus |= `$INSTANCE_NAME`_SsCSD1CalibrateOneSensor(rawLevel, ptrIdacMax);
            }
        } 
      
        /* Normalize idacMod and idacComp values */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            /* Calculate Modulator value: idacMod = (iDAC8Max + 1)/2  */
            #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                /* Set modulation IDAC for rows */
                ptrWdgt->rowIdacMod[0u] = (rowIDAC8Max[0u] + 1u) >> 1u;
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    /* Do same for first frequency channel  */
                    ptrWdgt->rowIdacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = (rowIDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] + 1u) >> 1u;

                    /* Do same for second frequency channel  */
                    ptrWdgt->rowIdacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = (rowIDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] + 1u) >> 1u;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

                /* Set modulation IDAC for columns */
                ptrWdgt->idacMod[0u] = (iDAC8Max[0u] + 1u) >> 1u;
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    /* Do same for first frequency channel  */
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] + 1u) >> 1u;

                    /* Do same for second frequency channel  */
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] + 1u) >> 1u;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            #else
                /* Set modulation IDAC  */
                ptrWdgt->idacMod[0u] = (iDAC8Max[0u] + 1u) >> 1u;
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    /* Do same for first frequency channel  */
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1] + 1u) >> 1u;

                    /* Do same for second frequency channel  */
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = (iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2] + 1u) >> 1u;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */ 

            /* Go through all columns of touchpad (or all sensors in button) to normalize them */ 
            for (snsIndex = 0u; 
                 snsIndex < `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].totalNumSns;
                 snsIndex++)
            { 
                /* Calculate slot Index */
                `$INSTANCE_NAME`_slotIndex = (uint8)(`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].slotIndex + snsIndex);

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].numCols <= snsIndex)
                    {
                        /* Init pointer to Modulator IDAC */
                        ptrIdac = &ptrWdgt->rowIdacMod[0u];
                    }
                    else
                    {
                        /* Init pointer to Modulator IDAC */
                        ptrIdac = &ptrWdgt->idacMod[0u];
                    }
                #else
                    /* Init pointer to Modulator IDAC */
                    ptrIdac = &ptrWdgt->idacMod[0u];
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

                curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)
                         `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsRam + snsIndex;
                /* Calculate Compensation IDAC value: idacComp(i) = iDAC8(i) - idacMod */
                if (curRamSnsPtr->idacComp[0u] >= ptrIdac[0u])
                {
                    curRamSnsPtr->idacComp[0u] -= ptrIdac[0u];
                    curRamSnsPtr->idacComp[0u] = 
                        (uint8)((((target * curRamSnsPtr->idacComp[0u]) + `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) /
                        `$INSTANCE_NAME`_PERCENTAGE_100);
                }
                else
                {
                    curRamSnsPtr->idacComp[0u] = 0u;
                }
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    /* Do same for first frequency channel  */
                    if (curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] >= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1])
                    {
                        curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] -= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_1]; 
                        curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = 
                            (uint8)((((target * curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1]) + 
                            `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                    }
                    else
                    {
                       curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = 0u; 
                    }
                    /* Do same for second frequency channel  */
                    if (curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] >= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2])
                    {
                        curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] -= ptrIdac[`$INSTANCE_NAME`_FREQ_CHANNEL_2]; 
                        curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = 
                            (uint8)((((target * curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2]) + 
                            `$INSTANCE_NAME`_PERCENTAGE_100) - 1u) / `$INSTANCE_NAME`_PERCENTAGE_100);
                    }
                    else
                    {
                        curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = 0u;
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */   
            }
        #else
            /* Normalize widget for single-IDAC mode */    
            #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                /* Set modulation IDAC for rows */    
                ptrWdgt->rowIdacMod[0u] = rowIDAC8Max[0u];
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    ptrWdgt->rowIdacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = rowIDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                    ptrWdgt->rowIdacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = rowIDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
                
                /* Set modulation IDAC for columns */   
                ptrWdgt->idacMod[0u] = iDAC8Max[0u];
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            #else
                /* Set modulation IDAC */ 
                ptrWdgt->idacMod[0u] = iDAC8Max[0u];
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_1];
                    ptrWdgt->idacMod[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = iDAC8Max[`$INSTANCE_NAME`_FREQ_CHANNEL_2];
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */
            #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */ 
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
        
        return calibrateStatus;
    }
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN))  */

#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

/* [] END OF FILE */
