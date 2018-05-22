/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_Sleep_Wakeup
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    #if defined(`$INSTANCE_NAME`__PC)
        `$INSTANCE_NAME`_backup.pcState = `$INSTANCE_NAME`_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            `$INSTANCE_NAME`_backup.usbState = `$INSTANCE_NAME`_CR1_REG;
            `$INSTANCE_NAME`_USB_POWER_REG |= `$INSTANCE_NAME`_USBIO_ENTER_SLEEP;
            `$INSTANCE_NAME`_CR1_REG &= `$INSTANCE_NAME`_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(`$INSTANCE_NAME`__SIO)
        `$INSTANCE_NAME`_backup.sioState = `$INSTANCE_NAME`_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        `$INSTANCE_NAME`_SIO_REG &= (uint32)(~`$INSTANCE_NAME`_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to `$INSTANCE_NAME`_Sleep() for an example usage.
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    #if defined(`$INSTANCE_NAME`__PC)
        `$INSTANCE_NAME`_PC = `$INSTANCE_NAME`_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            `$INSTANCE_NAME`_USB_POWER_REG &= `$INSTANCE_NAME`_USBIO_EXIT_SLEEP_PH1;
            `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_backup.usbState;
            `$INSTANCE_NAME`_USB_POWER_REG &= `$INSTANCE_NAME`_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(`$INSTANCE_NAME`__SIO)
        `$INSTANCE_NAME`_SIO_REG = `$INSTANCE_NAME`_backup.sioState;
    #endif
}


/* [] END OF FILE */
