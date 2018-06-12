/***************************************************************************//**
* \file `$INSTANCE_NAME`_boot.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the Bootloader API for USBFS Component.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_pvt.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))   

/***************************************
*    Bootloader Variables
***************************************/
    

static uint8  `$INSTANCE_NAME`_started = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStart
****************************************************************************//**
*
*  This function performs all required initialization for the USBFS component, 
*  waits on enumeration, and enables communication.
*
* \sideeffect
*  This function starts the USB with 3V or 5V operation.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStart(void) `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStart")`
{
    /* Enable Global Interrupts. Interrupts are mandatory for USBFS component operation. */
    CyGlobalIntEnable;

    /* Start USBFS Operation: device 0 and with 5V or 3V operation depend on Voltage Configuration in DWR. */
    `$INSTANCE_NAME`_Start(0u, `$INSTANCE_NAME`_DWR_POWER_OPERATION);

    /* USB component started, the correct enumeration will be checked in the first Read operation. */
    `$INSTANCE_NAME`_started = 1u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStop.
****************************************************************************//**
*
*  This function performs all necessary shutdown tasks required for the USBFS 
*  component.
*  
*  \sideeffect
*   Calls the USBFS_Stop() function.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommStop(void) `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStop")`
{
    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommReset.
****************************************************************************//**
*
*  This function resets receive and transmit communication buffers.
*
* \reentrant
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_CyBtldrCommReset(void) `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommReset")`
{
    `$INSTANCE_NAME`_EnableOutEP(`$INSTANCE_NAME`_BTLDR_OUT_EP); 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommWrite.
****************************************************************************//**
*
*  This function allows the caller to write data to the bootloader host. It 
*  handles polling to allow a block of data to be completely sent to the host 
*  device.
*
*  \param pData    A pointer to the block of data to send to the device
*  \param size     The number of bytes to write.
*  \param count    Pointer to an unsigned short variable to write the number of
*                  bytes actually written.
*  \param timeOut  Number of units to wait before returning because of a timeout.
*
* \return
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value that 
*  best describes the problem. For more information, see the “Return Codes” 
*  section of the System Reference Guide.
*
* \reentrant
*  No
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommWrite")`
{
    cystatus retCode;
    uint16 timeoutMs;

    /* Convert 10mS checks into 1mS checks. */
    timeoutMs = ((uint16) 10u * timeOut);

    /* Load data into IN endpoint to be read by host. */
    `$INSTANCE_NAME`_LoadInEP(`$INSTANCE_NAME`_BTLDR_IN_EP, pData, `$INSTANCE_NAME`_BTLDR_SIZEOF_READ_BUFFER);

    /* Wait unitl host reads data from IN endpoint. */
    while ((`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_IN_EP) == `$INSTANCE_NAME`_IN_BUFFER_FULL) &&
           (0u != timeoutMs))
    {
        CyDelay(`$INSTANCE_NAME`_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    if (`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_IN_EP) == `$INSTANCE_NAME`_IN_BUFFER_FULL)
    {
        retCode = CYRET_TIMEOUT;
    }
    else
    {
        *count = size;
        retCode = CYRET_SUCCESS;
    }

    return (retCode);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommRead.
****************************************************************************//**
*
*  This function allows the caller to read data from the bootloader host. It 
*  handles polling to allow a block of data to be completely received from the 
*  host device.
*
*  \param pData    A pointer to the area to store the block of data received
*                  from the device.
*  \param size     The number of bytes to read.
*  \param count    Pointer to an unsigned short variable to write the number
*                  of bytes actually read.
*  \param timeOut  Number of units to wait before returning because of a timeOut.
*                  Timeout is measured in 10s of ms.
*
* \return
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value that 
*  best describes the problem. For more information, see the “Return Codes” 
*  section of the System Reference Guide.
*
* \reentrant
*  No
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                            `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommRead")`
{
    cystatus retCode;
    uint16 timeoutMs;

    /* Convert 10mS checks into 1mS checks. */
    timeoutMs = ((uint16) 10u * timeOut);

    if (size > `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER)
    {
        size = `$INSTANCE_NAME`_BTLDR_SIZEOF_WRITE_BUFFER;
    }

    /* Wait for enumeration first time. */
    if (0u != `$INSTANCE_NAME`_started)
    {
        /* Wait for device enumeration. */
        while ((0u == `$INSTANCE_NAME`_GetConfiguration()) && (0u != timeoutMs))
        {
            CyDelay(`$INSTANCE_NAME`_BTLDR_WAIT_1_MS);
            timeoutMs--;
        }

        /* Enable OUT after enumeration. */
        if (0u != `$INSTANCE_NAME`_GetConfiguration())
        {
            (void) `$INSTANCE_NAME`_IsConfigurationChanged();  /* Clear configuration changes state status. */
            `$INSTANCE_NAME`_CyBtldrCommReset();
            
            `$INSTANCE_NAME`_started = 0u;
        }
    }
    else /* Check for configuration changes, has been done by Host. */
    {
        if (0u != `$INSTANCE_NAME`_IsConfigurationChanged()) /* Host could send double SET_INTERFACE request or RESET. */
        {
            if (0u != `$INSTANCE_NAME`_GetConfiguration())   /* Init OUT endpoints when device reconfigured. */
            {
                `$INSTANCE_NAME`_CyBtldrCommReset();
            }
        }
    }

    timeoutMs = ((uint16) 10u * timeOut); /* Re-arm timeout */

    /* Wait unitl host writes data into OUT endpoint. */
    while ((`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_OUT_EP) != `$INSTANCE_NAME`_OUT_BUFFER_FULL) && \
           (0u != timeoutMs))
    {
        CyDelay(`$INSTANCE_NAME`_BTLDR_WAIT_1_MS);
        timeoutMs--;
    }

    /* Read data from OUT endpoint if host wrote data into it. */
    if (`$INSTANCE_NAME`_GetEPState(`$INSTANCE_NAME`_BTLDR_OUT_EP) == `$INSTANCE_NAME`_OUT_BUFFER_FULL)
    {
        *count = `$INSTANCE_NAME`_ReadOutEP(`$INSTANCE_NAME`_BTLDR_OUT_EP, pData, size);
        retCode = CYRET_SUCCESS;
    }
    else
    {
        *count = 0u;
        retCode = CYRET_TIMEOUT;
    }

    return (retCode);
}

#endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) */


/* [] END OF FILE */
