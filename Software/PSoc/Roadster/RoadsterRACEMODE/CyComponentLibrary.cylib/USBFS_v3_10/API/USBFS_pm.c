/***************************************************************************//**
* \file `$INSTANCE_NAME`_pm.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides Suspend/Resume APIs implementation.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_pvt.h"
#include "`$INSTANCE_NAME`_Dp.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/***************************************
* Custom Declarations
***************************************/
/* `#START PM_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/***************************************
* Local data allocation
***************************************/

static `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;

#if (`$INSTANCE_NAME`_DP_ISR_ACTIVE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DP_ISR
    ****************************************************************************//**
    *
    *  This Interrupt Service Routine handles DP pin changes for wake-up from
    *  the sleep mode.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_DP_ISR)
    {
    #ifdef `$INSTANCE_NAME`_DP_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_DP_ISR_EntryCallback();
    #endif /* (`$INSTANCE_NAME`_DP_ISR_ENTRY_CALLBACK) */

        /* `#START DP_USER_CODE` Place your code here */

        /* `#END` */

        (void) `$INSTANCE_NAME`_Dp_ClearInterrupt();
		
	#ifdef `$INSTANCE_NAME`_DP_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_DP_ISR_ExitCallback();
    #endif /* (`$INSTANCE_NAME`_DP_ISR_EXIT_CALLBACK) */
    }
#endif /* (`$INSTANCE_NAME`_DP_ISR_ACTIVE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
****************************************************************************//**
*
*  Saves the current user configuration.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`
{
    /* Empty function added for the compatibility purpose. */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
****************************************************************************//**
*
*  Restores the current user configuration.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`
{
    if (`$INSTANCE_NAME`_configuration != 0u)
    {
        `$INSTANCE_NAME`_ConfigReg();
        `$INSTANCE_NAME`_EpStateInit();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Suspend
****************************************************************************//**
*
*  This function prepares the USBFS component to enter low power mode. The 
*  interrupt on falling edge on Dp pin is configured to wakeup device when the 
*  host drives resume condition. The pull-up is enabled on the Dp line while 
*  device is in low power mode. The supported low power modes are Deep Sleep 
*  (PSoC 4200L) and Sleep (PSoC 3/ PSoC 5LP).
*  
*  *Note* For PSoC 4200L devices, this function should not be called before 
*  entering Sleep.
*  
*  *Note* After enter low power mode, the data which is left in the IN or OUT 
*  endpoint buffers is not restored after wakeup and lost. Therefore it should 
*  be stored in the SRAM for OUT endpoint or read by the host for IN endpoint 
*  before enter low power mode.
*
* \globalvars
*  `$INSTANCE_NAME`_backup.enable:  modified.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Suspend(void) `=ReentrantKeil($INSTANCE_NAME . "_Suspend")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    if (0u != (`$INSTANCE_NAME`_CR0_REG & `$INSTANCE_NAME`_CR0_ENABLE))
    {
        /* USB block is enabled. */
        `$INSTANCE_NAME`_backup.enableState = 1u;

    #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
        `$INSTANCE_NAME`_Stop_DMA(`$INSTANCE_NAME`_MAX_EP);
    #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

    #if (CY_PSOC4)
        /* Suspend enter sequence. */
        `$INSTANCE_NAME`_POWER_CTRL_REG |= (`$INSTANCE_NAME`_POWER_CTRL_SUSPEND |
                                            `$INSTANCE_NAME`_POWER_CTRL_SUSPEND_DEL);

        /* Store state of USB regulator and disable it. */
        `$INSTANCE_NAME`_backup.mode = (uint8)  (`$INSTANCE_NAME`_CR1_REG & `$INSTANCE_NAME`_CR1_REG_ENABLE);
        `$INSTANCE_NAME`_CR1_REG    &= (uint32) ~`$INSTANCE_NAME`_CR1_REG_ENABLE;
        
        /* Store SIE interrupt sources. Valid bits are 0 - 4. */
        `$INSTANCE_NAME`_backup.intrSeiMask = (uint8) `$INSTANCE_NAME`_INTR_SIE_MASK_REG;

    #else
        /* Ensure USB transmit enable is low (USB_USBIO_CR0.ten). - Manual Transmission - Disabled. */
        `$INSTANCE_NAME`_USBIO_CR0_REG &= (uint8) ~`$INSTANCE_NAME`_USBIO_CR0_TEN;
        CyDelayUs(`$INSTANCE_NAME`_WAIT_REG_STABILITY_50NS);  /*~50ns delay. */

        /* Disable the USBIO by asserting PM.USB_CR0.fsusbio_pd_n(Inverted) and pd_pullup_hv(Inverted) high. */
        `$INSTANCE_NAME`_PM_USB_CR0_REG &= (uint8) ~(`$INSTANCE_NAME`_PM_USB_CR0_PD_N |
                                                     `$INSTANCE_NAME`_PM_USB_CR0_PD_PULLUP_N);

        /* Disable the SIE. */
        `$INSTANCE_NAME`_CR0_REG &= (uint8) ~`$INSTANCE_NAME`_CR0_ENABLE;

        CyDelayUs(`$INSTANCE_NAME`_WAIT_REG_STABILITY_50NS);  /* ~50ns delay. */
        /* Store mode and disable VRegulator. */
        `$INSTANCE_NAME`_backup.mode = (uint8) (`$INSTANCE_NAME`_CR1_REG & `$INSTANCE_NAME`_CR1_REG_ENABLE);
        `$INSTANCE_NAME`_CR1_REG    &= (uint8) ~`$INSTANCE_NAME`_CR1_REG_ENABLE;

        CyDelayUs(`$INSTANCE_NAME`_WAIT_REG_STABILITY_1US); /* min 0.5us delay required. */

        /* Disable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        `$INSTANCE_NAME`_PM_USB_CR0_REG &= (uint8) ~`$INSTANCE_NAME`_PM_USB_CR0_REF_EN;

        /* Switch DP and DM terminals to GPIO mode and disconnect 1.5k pull-up. */
        `$INSTANCE_NAME`_USBIO_CR1_REG |= `$INSTANCE_NAME`_USBIO_CR1_IOMODE;

        /* Disable USBFS block. */
        /* Clear power active and standby mode templates: disable USB block. */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG  &= (uint8) ~`$INSTANCE_NAME`_PM_ACT_EN_FSUSB;
        `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8) ~`$INSTANCE_NAME`_PM_STBY_EN_FSUSB;

        CyDelayUs(`$INSTANCE_NAME`_WAIT_REG_STABILITY_1US); /* min 0.5us delay required. */
    #endif /* (CY_PSOC4) */
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }

    CyExitCriticalSection(enableInterrupts);

#if (`$INSTANCE_NAME`_DP_ISR_ACTIVE)
    /* Clear active mode Dp interrupt source history. */
    (void) `$INSTANCE_NAME`_Dp_ClearInterrupt();
    CyIntClearPending(`$INSTANCE_NAME`_DP_INTC_VECT_NUM);

    CyIntEnable      (`$INSTANCE_NAME`_DP_INTC_VECT_NUM);
#endif /* (`$INSTANCE_NAME`_DP_ISR_ACTIVE). */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Resume
****************************************************************************//**
*
*  This function prepares the USBFS component for active mode operation after 
*  exit low power mode. It restores the component active mode configuration such 
*  as device address assigned previously by the host, endpoints buffer and disables 
*  interrupt on Dp pin.
*  The supported low power modes are Deep Sleep (PSoC 4200L) and Sleep 
*  (PSoC 3/ PSoC 5LP).
*  
*  *Note* For PSoC 4200L devices, this function should not be called after 
*  exiting Sleep.
*  
*  *Note* To resume communication with the host, the data endpoints must be 
*  managed: the OUT endpoints must be enabled and IN endpoints must be loaded 
*  with data. For DMA with Automatic Buffer Management, all endpoints buffers 
*  must be initialized again before making them available to the host.
*
*
* \globalvars
*  `$INSTANCE_NAME`_backup - checked.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Resume(void) `=ReentrantKeil($INSTANCE_NAME . "_Resume")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    if (0u != `$INSTANCE_NAME`_backup.enableState)
    {
    #if (`$INSTANCE_NAME`_DP_ISR_ACTIVE)
        CyIntDisable(`$INSTANCE_NAME`_DP_INTC_VECT_NUM);
    #endif /* (`$INSTANCE_NAME`_DP_ISR_ACTIVE) */

    #if (CY_PSOC4)
        /* Enable clock to USB IP. */
        `$INSTANCE_NAME`_USB_CLK_EN_REG |= `$INSTANCE_NAME`_USB_CLK_CSR_CLK_EN;

        /* Restore arbiter configuration for DMA transfers. */
        #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
            #if (`$INSTANCE_NAME`_ARB_ISR_ACTIVE)
                /* Enable ARB EP interrupt sources. */
                `$INSTANCE_NAME`_ARB_INT_EN_REG = `$INSTANCE_NAME`_DEFAULT_ARB_INT_EN;
            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

            /* Configure arbiter for Manual or Auto DMA operation and clear 
            * configuration completion. 
            */
            `$INSTANCE_NAME`_ARB_CFG_REG = `$INSTANCE_NAME`_DEFAULT_ARB_CFG;
        #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

        /* Restore level (hi, lo, med) for each interrupt source. */
        `$INSTANCE_NAME`_INTR_LVL_SEL_REG = `$INSTANCE_NAME`_DEFAULT_INTR_LVL_SEL;
        
        /* Store SIE interrupt sources. */
        `$INSTANCE_NAME`_INTR_SIE_MASK_REG = (uint32) `$INSTANCE_NAME`_backup.intrSeiMask;

        /* Set EP0.CR: ACK Setup, NAK IN/OUT. */
        `$INSTANCE_NAME`_EP0_CR_REG = `$INSTANCE_NAME`_MODE_NAK_IN_OUT;

        /* Restore data EP1-8 configuration. */
        `$INSTANCE_NAME`_RestoreConfig();

        /* Restore state of USB regulator and wait until it supples stable power. */
        `$INSTANCE_NAME`_CR1_REG |= `$INSTANCE_NAME`_backup.mode;
        CyDelayUs(`$INSTANCE_NAME`_WAIT_VREF_STABILITY);

        /* Suspend exit sequence. */
        `$INSTANCE_NAME`_POWER_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_POWER_CTRL_SUSPEND;
        CyDelayUs(`$INSTANCE_NAME`_WAIT_SUSPEND_DEL_DISABLE);
        `$INSTANCE_NAME`_POWER_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_POWER_CTRL_SUSPEND_DEL;

    #else
        /* Set power active and standby mode templates: enable USB block. */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG  |= `$INSTANCE_NAME`_PM_ACT_EN_FSUSB;
        `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_PM_STBY_EN_FSUSB;

        /* Enable core clock. */
        `$INSTANCE_NAME`_USB_CLK_EN_REG |= `$INSTANCE_NAME`_USB_CLK_ENABLE;

        /* Enable the USBIO reference by setting PM.USB_CR0.fsusbio_ref_en.*/
        `$INSTANCE_NAME`_PM_USB_CR0_REG |= `$INSTANCE_NAME`_PM_USB_CR0_REF_EN;

        /* The reference is available ~40us after power restored. */
        CyDelayUs(`$INSTANCE_NAME`_WAIT_VREF_RESTORE);
        /* Restore state of USB regulator and wait until it supples stable power. */
        `$INSTANCE_NAME`_CR1_REG |= `$INSTANCE_NAME`_backup.mode;
        CyDelayUs(`$INSTANCE_NAME`_WAIT_VREF_STABILITY);   /*~50ns delay. */

        /* Enable USBIO. */
        `$INSTANCE_NAME`_PM_USB_CR0_REG |= `$INSTANCE_NAME`_PM_USB_CR0_PD_N;
        CyDelayUs(`$INSTANCE_NAME`_WAIT_PD_PULLUP_N_ENABLE);
        /* Set the USBIO pull-up enable. */
        `$INSTANCE_NAME`_PM_USB_CR0_REG |= `$INSTANCE_NAME`_PM_USB_CR0_PD_PULLUP_N;

        /* Restore arbiter configuration for DMA transfers. */
        #if (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA)
            #if (`$INSTANCE_NAME`_ARB_ISR_ACTIVE)
                /* Enable ARB EP interrupt sources. */
                `$INSTANCE_NAME`_ARB_INT_EN_REG = `$INSTANCE_NAME`_DEFAULT_ARB_INT_EN;
            #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

            /* Configure arbiter for Manual or Auto DMA operation and clear 
            * configuration completion. 
            */
            `$INSTANCE_NAME`_ARB_CFG_REG = `$INSTANCE_NAME`_DEFAULT_ARB_CFG;
        #endif /* (`$INSTANCE_NAME`_EP_MANAGEMENT_DMA) */

        /* Set EP0.CR: ACK Setup, STALL IN/OUT. */
        `$INSTANCE_NAME`_EP0_CR_REG = `$INSTANCE_NAME`_MODE_STALL_IN_OUT;

        /* Enable the USB IP to respond to USB traffic with the last address. */
        `$INSTANCE_NAME`_CR0_REG |= `$INSTANCE_NAME`_CR0_ENABLE;
        CyDelayCycles(`$INSTANCE_NAME`_WAIT_CR0_REG_STABILITY);

        /* Enable D+ pull-up and keep USB control on IO. */
        `$INSTANCE_NAME`_USBIO_CR1_REG = `$INSTANCE_NAME`_USBIO_CR1_USBPUEN;

        /* Restore data EP1-8 configuration. */
        `$INSTANCE_NAME`_RestoreConfig();
    #endif /* (CY_PSOC4) */
    }

    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
