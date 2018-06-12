/*******************************************************************************
* \file Name: `$INSTANCE_NAME`_PM.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* This file contains the setup, control, and status commands to support
* the component in Low-Power modes.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
****************************************************************************//**
*
* Stops the component operation and saves the user configuration.
*
* Before call this function, ensure that SENT is ready to sleep by checking the 
* `$INSTANCE_NAME`_status flag. For this purpose, use the 
* `$INSTANCE_NAME`_GetStatus() function.
*
* \return
* CYRET_SUCCESS the SENT went into sleep. <br>
* CYRET_CANCELED the SENT did not go into sleep, because SENT still sending 
* previous data, `$INSTANCE_NAME`_status = `$INSTANCE_NAME`_BUSY. 
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Sleep(void)
{
    uint32 retVal = CYRET_CANCELED;

    if(`$INSTANCE_NAME`_READY == `$INSTANCE_NAME`_status)
    {
        `$INSTANCE_NAME`_PWM_Sleep();
        retVal = CYRET_SUCCESS;
    }

    return (retVal);
}


/* [] END OF FILE */
