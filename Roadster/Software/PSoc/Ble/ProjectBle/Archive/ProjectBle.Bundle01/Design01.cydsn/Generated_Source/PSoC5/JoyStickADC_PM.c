/*******************************************************************************
* File Name: JoyStickADC_PM.c
* Version 2.10
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

#include "JoyStickADC.h"
#include "JoyStickADC_SAR.h"
#if(JoyStickADC_CLOCK_SOURCE == JoyStickADC_CLOCK_INTERNAL)
    #include "JoyStickADC_IntClock.h"
#endif   /* JoyStickADC_CLOCK_SOURCE == JoyStickADC_CLOCK_INTERNAL */


/*******************************************************************************
* Function Name: JoyStickADC_Sleep
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
void JoyStickADC_Sleep(void)
{
    JoyStickADC_SAR_Stop();
    JoyStickADC_SAR_Sleep();
    JoyStickADC_Disable();

    #if(JoyStickADC_CLOCK_SOURCE == JoyStickADC_CLOCK_INTERNAL)
        JoyStickADC_IntClock_Stop();
    #endif   /* JoyStickADC_CLOCK_SOURCE == JoyStickADC_CLOCK_INTERNAL */
}


/*******************************************************************************
* Function Name: JoyStickADC_Wakeup
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
void JoyStickADC_Wakeup(void)
{
    JoyStickADC_SAR_Wakeup();
    JoyStickADC_SAR_Enable();

    #if(JoyStickADC_CLOCK_SOURCE == JoyStickADC_CLOCK_INTERNAL)
        JoyStickADC_IntClock_Start();
    #endif   /* JoyStickADC_CLOCK_SOURCE == JoyStickADC_CLOCK_INTERNAL */

    /* The block is ready to use 10 us after the SAR enable signal is set high. */
    CyDelayUs(10u);
    
    JoyStickADC_Enable();

    #if(JoyStickADC_SAMPLE_MODE == JoyStickADC_SAMPLE_MODE_FREE_RUNNING)
        JoyStickADC_SAR_StartConvert();
    #endif /* (JoyStickADC_SAMPLE_MODE == JoyStickADC_SAMPLE_MODE_FREE_RUNNING) */

    (void) CY_GET_REG8(JoyStickADC_STATUS_PTR);
}


/*******************************************************************************
* Function Name: JoyStickADC_SaveConfig
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
void JoyStickADC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: JoyStickADC_RestoreConfig
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
void JoyStickADC_RestoreConfig(void)
{

}


/* [] END OF FILE */
