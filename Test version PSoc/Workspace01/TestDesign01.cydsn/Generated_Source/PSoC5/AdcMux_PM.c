/*******************************************************************************
* File Name: AdcMux_PM.c
* Version 2.0
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

#include "AdcMux.h"
#include "AdcMux_SAR.h"
#if(AdcMux_CLOCK_SOURCE == AdcMux_CLOCK_INTERNAL)
    #include "AdcMux_IntClock.h"
#endif   /* AdcMux_CLOCK_SOURCE == AdcMux_CLOCK_INTERNAL */


/*******************************************************************************
* Function Name: AdcMux_Sleep
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
void AdcMux_Sleep(void)
{
    AdcMux_SAR_Stop();
    AdcMux_SAR_Sleep();
    AdcMux_Disable();

    #if(AdcMux_CLOCK_SOURCE == AdcMux_CLOCK_INTERNAL)
        AdcMux_IntClock_Stop();
    #endif   /* AdcMux_CLOCK_SOURCE == AdcMux_CLOCK_INTERNAL */
}


/*******************************************************************************
* Function Name: AdcMux_Wakeup
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
void AdcMux_Wakeup(void)
{
    AdcMux_SAR_Wakeup();
    AdcMux_SAR_Enable();

    #if(AdcMux_CLOCK_SOURCE == AdcMux_CLOCK_INTERNAL)
        AdcMux_IntClock_Start();
    #endif   /* AdcMux_CLOCK_SOURCE == AdcMux_CLOCK_INTERNAL */

    /* The block is ready to use 10 us after the SAR enable signal is set high. */
    CyDelayUs(10u);
    
    AdcMux_Enable();

    #if(AdcMux_SAMPLE_MODE == AdcMux_SAMPLE_MODE_FREE_RUNNING)
        AdcMux_SAR_StartConvert();
    #endif /* (AdcMux_SAMPLE_MODE == AdcMux_SAMPLE_MODE_FREE_RUNNING) */

    (void) CY_GET_REG8(AdcMux_STATUS_PTR);
}


/*******************************************************************************
* Function Name: AdcMux_SaveConfig
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
void AdcMux_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: AdcMux_RestoreConfig
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
void AdcMux_RestoreConfig(void)
{

}


/* [] END OF FILE */
