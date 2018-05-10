/***************************************************************************//**
* \file `$INSTANCE_NAME`_PM.c  
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the power manager source code to the API for 
*  `$INSTANCE_NAME` component.
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

#include "`$INSTANCE_NAME`.h"

/**
* \addtogroup group_globals
* @{
*/
/** Contains configuration of `$INSTANCE_NAME` before sleep. Enable state is the
*   only data required to be preserved. */
static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup =
{
    0u,
};
/** @} globals */


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* \brief This is the preferred routine to prepare the component for sleep. The 
* `$INSTANCE_NAME`_Sleep() routine saves the current component state. Then it 
* calls the `$INSTANCE_NAME`_Stop() function and calls 
* `$INSTANCE_NAME`_SaveConfig() to save the hardware configuration.
* 
* Call the `$INSTANCE_NAME`_Sleep() function before calling the 
* CySysPmDeepSleep() or the CySysPmHibernate() function. See the PSoC Creator 
* System Reference Guide for more information about power-management functions.
* 
* \param None
* 
* \return None
*
* \sideeffect If this function is called twice in the enable state of the 
* component, the disabled state of the component will be stored. So 
* `$INSTANCE_NAME`_Enable() and `$INSTANCE_NAME`_StartConvert() must be called 
* after `$INSTANCE_NAME`_Wakeup() in this case.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup (W)
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) 
{
    uint32 dftRegVal = (uint32) `$INSTANCE_NAME`_SAR_DFT_CTRL_REG;

    `$INSTANCE_NAME`_backup.enableState = 0u;
    
    /* Save nonretention SAR_DFT_CTRL register state. */
    if((dftRegVal & `$INSTANCE_NAME`_SAR_DFT_CTRL_DCEN_MSK) != 0u)
    {
        `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_SLEEP_DFT_DCEN;
    }
    if((dftRegVal & `$INSTANCE_NAME`_SAR_DFT_CTRL_DLY_INC_MSK) != 0u)
    {
        `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_SLEEP_DFT_DLY_INC;
    }
    
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    `$INSTANCE_NAME`_SAR_DFT_CTRL_REG |= `$INSTANCE_NAME`_SAR_DFT_CTRL_ADFT_OVERRIDE_MSK;
    
    if((`$INSTANCE_NAME`_SAR_CTRL_REG  & `$INSTANCE_NAME`_SAR_CTRL_ENABLED_MSK) != 0u)
    {
        `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_ENABLED;
        if((`$INSTANCE_NAME`_SAR_SAMPLE_CTRL_REG & `$INSTANCE_NAME`_SAR_SAMPLE_CTRL_CONTINUOUS_MSK) != 0u)
        {
            `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_STARTED;
        }

        `$INSTANCE_NAME`_StopConvert();
        `$INSTANCE_NAME`_Stop();
    }

    /* Disable the SAR internal pump before entering the chip low power mode */
    if((`$INSTANCE_NAME`_SAR_CTRL_REG & `$INSTANCE_NAME`_SAR_CTRL_BOOSTPUMP_EN_MSK) != 0u)
    {
        `$INSTANCE_NAME`_SAR_CTRL_REG &= (uint32)~`$INSTANCE_NAME`_SAR_CTRL_BOOSTPUMP_EN_MSK;
        `$INSTANCE_NAME`_backup.enableState |= `$INSTANCE_NAME`_BOOSTPUMP_ENABLED;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* \brief This is the preferred routine to restore the component to the state when 
* `$INSTANCE_NAME`_Sleep() was called. The `$INSTANCE_NAME`_Wakeup() function 
* calls the `$INSTANCE_NAME`_RestoreConfig() function to restore the 
* configuration. If the component was enabled before the `$INSTANCE_NAME`_Sleep() 
* function was called, the `$INSTANCE_NAME`_Wakeup() function also re-enables the 
* component.
*
* \param None
* 
* \return None
*
* \sideeffect
* Calling this function without previously calling `$INSTANCE_NAME`_Sleep() may lead to 
* unpredictable results.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup (R)
*
* \globalvars
*  \ref `$INSTANCE_NAME`_backup
* 
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    uint32 dftRegVal = (uint32)`$INSTANCE_NAME`_SAR_DFT_CTRL_HIZ_MSK;
    
    /* Restore nonretention SAR_DFT_CTRL register state. */
    if ((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_SLEEP_DFT_DCEN) != 0u)
    {
        dftRegVal |= `$INSTANCE_NAME`_SAR_DFT_CTRL_DCEN_MSK;
    }
    if ((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_SLEEP_DFT_DLY_INC) != 0u)
    {
        dftRegVal |= `$INSTANCE_NAME`_SAR_DFT_CTRL_DLY_INC_MSK;
    }
    `$INSTANCE_NAME`_SAR_DFT_CTRL_REG = dftRegVal;
    
    if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_ENABLED) != 0u)
    {
        /* Enable the SAR internal pump  */
        if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_BOOSTPUMP_ENABLED) != 0u)
        {
            `$INSTANCE_NAME`_SAR_CTRL_REG |= `$INSTANCE_NAME`_SAR_CTRL_BOOSTPUMP_EN_MSK;
        }
        
        `$INSTANCE_NAME`_Enable();
        
        if((`$INSTANCE_NAME`_backup.enableState & `$INSTANCE_NAME`_STARTED) != 0u)
        {
            `$INSTANCE_NAME`_StartConvert();
        }
    }
}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
****************************************************************************//*
*
* \brief Saves the current configuration of `$INSTANCE_NAME` non-retention registers.
*
* \param None
* 
* \return None
* 
* \sideeffect None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{
     /* All configuration registers are marked as [reset_all_retention] */
}

/* ****************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
****************************************************************************//*
*
* \brief Restores the configuration of `$INSTANCE_NAME` non-retention registers.
* 
* \param None
* 
* \return None
*
* \sideeffect Calling this function without previously calling 
* `$INSTANCE_NAME`_SaveConfig() or `$INSTANCE_NAME`_Sleep will lead to 
* unpredictable results.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}

/* [] END OF FILE */
