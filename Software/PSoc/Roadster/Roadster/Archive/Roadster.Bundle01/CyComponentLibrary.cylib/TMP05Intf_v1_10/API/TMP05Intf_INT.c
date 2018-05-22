/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides Interrupt Service Routine (ISR) for the `$INSTANCE_NAME`
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START `$INSTANCE_NAME`_INT_HEADER` */

/* `#END` */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for `$INSTANCE_NAME`_ISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_busyFlag - used for reflect sensor masuring.
*  `$INSTANCE_NAME`_contMode - used for reflect modes of operation used:
*     - `$INSTANCE_NAME`_MODE_CONTINUOUS.
*     - `$INSTANCE_NAME`_MODE_ONESHOT.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_EOC_ISR_Int)
{
    uint8 enableInterrupts;
    uint8 indexVar;
   
    #ifdef `$INSTANCE_NAME`_EOC_ISR_INT_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EOC_ISR_Int_EntryCallback();
    #endif /* `$INSTANCE_NAME`_EOC_ISR_INT_ENTRY_CALLBACK */
 
    for(indexVar = 0u; indexVar < `$INSTANCE_NAME`_CUSTOM_NUM_SENSORS; indexVar++)
    {
        /* Store high time of sensor PWM */
        `$INSTANCE_NAME`_hi[indexVar] = CY_GET_REG16(`$INSTANCE_NAME`_HI_CNT_PTR);

         /* Store low time of sensor PWM */
        `$INSTANCE_NAME`_lo[indexVar] = CY_GET_REG16(`$INSTANCE_NAME`_LO_CNT_PTR);
    }
        /* Change shared regs, need to be safety */
        enableInterrupts = CyEnterCriticalSection();

       `$INSTANCE_NAME`_CONTROL_REG ^= `$INSTANCE_NAME`_CTRL_EOC;

        /* shared regs config are done */
        CyExitCriticalSection(enableInterrupts);
    
    /* In continuous mode, trigger next measurement, otherwise clear busy flag */
    if (`$INSTANCE_NAME`_contMode == `$INSTANCE_NAME`_MODE_CONTINUOUS)
    {
        /* Change shared regs, need to be safety */
        enableInterrupts = CyEnterCriticalSection();

       `$INSTANCE_NAME`_CONTROL_REG ^= `$INSTANCE_NAME`_CTRL_TRIG;

        /* shared regs config are done */
        CyExitCriticalSection(enableInterrupts);
    }
    else
    {
        `$INSTANCE_NAME`_busyFlag = 0u;
    }

    #ifdef `$INSTANCE_NAME`_EOC_ISR_INT_EXIT_CALLBACK
        `$INSTANCE_NAME`_EOC_ISR_Int_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EOC_ISR_INT_EXIT_CALLBACK */
}


/* [] END OF FILE */
