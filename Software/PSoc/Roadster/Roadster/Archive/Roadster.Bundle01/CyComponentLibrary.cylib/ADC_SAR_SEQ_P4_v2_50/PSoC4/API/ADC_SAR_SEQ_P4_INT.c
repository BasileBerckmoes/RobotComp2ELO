/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(`$INSTANCE_NAME`_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( `$INSTANCE_NAME`_ISR )
    {
        uint32 intr_status;

        /* Read interrupt status register */
        intr_status = `$INSTANCE_NAME`_SAR_INTR_REG;

        #ifdef `$INSTANCE_NAME`_ISR_INTERRUPT_CALLBACK
            `$INSTANCE_NAME`_ISR_InterruptCallback();
        #endif /* `$INSTANCE_NAME`_ISR_INTERRUPT_CALLBACK */


        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
        /* `#START MAIN_ADC_ISR`  */

        /* `#END`  */
        
        /* Clear handled interrupt */
        `$INSTANCE_NAME`_SAR_INTR_REG = intr_status;
    }

#endif   /* End `$INSTANCE_NAME`_IRQ_REMOVE */


/* [] END OF FILE */
