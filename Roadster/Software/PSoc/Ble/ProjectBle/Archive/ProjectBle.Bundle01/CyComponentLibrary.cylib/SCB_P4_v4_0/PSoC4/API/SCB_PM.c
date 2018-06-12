/***************************************************************************//**
* \file `$INSTANCE_NAME`_PM.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"

#if(`$INSTANCE_NAME`_SCB_MODE_I2C_INC)
    #include "`$INSTANCE_NAME`_I2C_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_INC) */

#if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC)
    #include "`$INSTANCE_NAME`_EZI2C_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC) */

#if(`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC)
    #include "`$INSTANCE_NAME`_SPI_UART_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG || \
   (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG   && (!`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST))   || \
   (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG && (!`$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST)) || \
   (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG   && (!`$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST))   || \
   (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG  && (!`$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)))

    `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
*  Prepares the `$INSTANCE_NAME` component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the `$INSTANCE_NAME`_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    if(`$INSTANCE_NAME`_SCB_WAKE_ENABLE_CHECK)
    {
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CSaveConfig();
        }
    #if(!`$INSTANCE_NAME`_CY_SCBIP_V1)
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartSaveConfig();
        }
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = (uint8) `$INSTANCE_NAME`_GET_CTRL_ENABLED;

        if(0u != `$INSTANCE_NAME`_backup.enableState)
        {
            `$INSTANCE_NAME`_Stop();
        }
    }

#else

    #if (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_I2CSaveConfig();

    #elif (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG && `$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_EzI2CSaveConfig();

    #elif (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG && `$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_SpiSaveConfig();

    #elif (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG && `$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_UartSaveConfig();

    #else

        `$INSTANCE_NAME`_backup.enableState = (uint8) `$INSTANCE_NAME`_GET_CTRL_ENABLED;

        if(0u != `$INSTANCE_NAME`_backup.enableState)
        {
            `$INSTANCE_NAME`_Stop();
        }

    #endif /* defined (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) && (`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST) */

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
*  Prepares the `$INSTANCE_NAME` component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the `$INSTANCE_NAME`_Wakeup() function without first calling the 
*   `$INSTANCE_NAME`_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    if(`$INSTANCE_NAME`_SCB_WAKE_ENABLE_CHECK)
    {
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CRestoreConfig();
        }
    #if(!`$INSTANCE_NAME`_CY_SCBIP_V1)
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartRestoreConfig();
        }
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != `$INSTANCE_NAME`_backup.enableState)
        {
            `$INSTANCE_NAME`_Enable();
        }
    }

#else

    #if (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG  && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_I2CRestoreConfig();

    #elif (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG && `$INSTANCE_NAME`_EZI2C_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_EzI2CRestoreConfig();

    #elif (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG && `$INSTANCE_NAME`_SPI_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_SpiRestoreConfig();

    #elif (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG && `$INSTANCE_NAME`_UART_WAKE_ENABLE_CONST)
        `$INSTANCE_NAME`_UartRestoreConfig();

    #else

        if(0u != `$INSTANCE_NAME`_backup.enableState)
        {
            `$INSTANCE_NAME`_Enable();
        }

    #endif /* (`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST) */

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
