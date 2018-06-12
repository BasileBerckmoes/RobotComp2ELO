/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_SAR.h"
#if(`$INSTANCE_NAME`_CLOCK_SOURCE == `$INSTANCE_NAME`_CLOCK_INTERNAL)
    #include "`$INSTANCE_NAME`_IntClock.h"
#endif   /* `$INSTANCE_NAME`_CLOCK_SOURCE == `$INSTANCE_NAME`_CLOCK_INTERNAL */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void)
{
    `$INSTANCE_NAME`_SAR_Stop();
    `$INSTANCE_NAME`_SAR_Sleep();
    `$INSTANCE_NAME`_Disable();

    #if(`$INSTANCE_NAME`_CLOCK_SOURCE == `$INSTANCE_NAME`_CLOCK_INTERNAL)
        `$INSTANCE_NAME`_IntClock_Stop();
    #endif   /* `$INSTANCE_NAME`_CLOCK_SOURCE == `$INSTANCE_NAME`_CLOCK_INTERNAL */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers. This should
*  be called just after awaking from sleep mode
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void)
{
    `$INSTANCE_NAME`_SAR_Wakeup();
    `$INSTANCE_NAME`_SAR_Enable();

    #if(`$INSTANCE_NAME`_CLOCK_SOURCE == `$INSTANCE_NAME`_CLOCK_INTERNAL)
        `$INSTANCE_NAME`_IntClock_Start();
    #endif   /* `$INSTANCE_NAME`_CLOCK_SOURCE == `$INSTANCE_NAME`_CLOCK_INTERNAL */

    /* The block is ready to use 10 us after the SAR enable signal is set high. */
    CyDelayUs(10u);
    
    `$INSTANCE_NAME`_Enable();

    #if(`$INSTANCE_NAME`_SAMPLE_MODE == `$INSTANCE_NAME`_SAMPLE_MODE_FREE_RUNNING)
        `$INSTANCE_NAME`_SAR_StartConvert();
    #endif /* (`$INSTANCE_NAME`_SAMPLE_MODE == `$INSTANCE_NAME`_SAMPLE_MODE_FREE_RUNNING) */

    (void) CY_GET_REG8(`$INSTANCE_NAME`_STATUS_PTR);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current configuration of ADC non-retention registers
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the configuration of ADC non-retention registers
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreConfig(void)
{

}


/* [] END OF FILE */
