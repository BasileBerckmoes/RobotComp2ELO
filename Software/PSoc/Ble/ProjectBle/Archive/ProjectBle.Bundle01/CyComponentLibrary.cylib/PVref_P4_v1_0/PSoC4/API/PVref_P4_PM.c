/***************************************************************************//**
* \file `$INSTANCE_NAME`_PM.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the API source code for Power Management of the
*  Programmable Voltage Reference component.
*
* Note:
*  None
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

static `$INSTANCE_NAME`_backup_struct `$INSTANCE_NAME`_backup = {0u};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
*  Prepares the component to enter Sleep mode.
*  If the reference is based on Vdda, the function will open the switch at the
*  bottom of the resistor tree to eliminate the current flow through the
*  resistor. If the reference is based on the bandgap, this function will do
*  nothing.
*
* \sideeffect
*  If the reference is based on Vdda, it will affect all Vdda-based references
*  because they share the same resistor tree.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    if (0u != (`$INSTANCE_NAME`_PRB_REF_REG & `$INSTANCE_NAME`_VREF_SUPPLY_SEL))
    {
        `$INSTANCE_NAME`_PRB_CTRL_REG &= ~`$INSTANCE_NAME`_VDDA_ENABLE;
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
    else /* The reference is based on the bandgap */
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
*  Restores the component after exiting Sleep mode.
*  By calling this function for any Vdda-based reference, the function will
*  enable all Vdda-based references because they all are based on the same
*  resistor divider. For bandgap-based references, nothing will happen.
*
* \sideeffect
*  If the reference is based on Vdda, it will affect all Vdda-based references
*  because they share the same resistor tree.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    if (0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_PRB_CTRL_REG |= `$INSTANCE_NAME`_VDDA_ENABLE;
    } /* Do nothing if the reference is based on the bandgap */
}


/* [] END OF FILE */
