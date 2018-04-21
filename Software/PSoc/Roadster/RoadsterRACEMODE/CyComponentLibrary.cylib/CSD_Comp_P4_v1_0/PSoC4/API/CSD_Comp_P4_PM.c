/***************************************************************************//**
* \file `$INSTANCE_NAME`_PM.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the API source code for Power Management of the
*  Comparator component.
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
*  The `$INSTANCE_NAME`_Sleep() function checks to see if the component is
*  enabled and saves that state. Then it calls the _Stop() function.
*  It is recommended to call the `$INSTANCE_NAME`_Sleep() function before
*  calling the CyPmSleep() or the CyPmDeepSleep() function.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    if (0u != (`$INSTANCE_NAME`_CSD_CSDCMP_REG & `$INSTANCE_NAME`_CSDCMP_EN))
    {
        `$INSTANCE_NAME`_backup.enableState = 1u;
    }
    else
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;
    }

    `$INSTANCE_NAME`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
*  If the component was enabled before calling the `$INSTANCE_NAME`_Sleep()
*  function, the `$INSTANCE_NAME`_Wakeup() function will re-enable the
*  component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    if (0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
