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
* Copyright 2015-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/******************************************************************************
* Custom Declarations and Variables
* - add user include files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START `$INSTANCE_NAME`_SYS_VAR`  */

/* `#END`  */

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR
*******************************************************************************
*
* \brief Handle Interrupt Service Routine.
*
* \param None
*
* \return None
*
* \sideeffect None
*
******************************************************************************/
CY_ISR( `$INSTANCE_NAME`_ISR )
{
    uint32 intr_status;

    /* Read interrupt status register */
    intr_status = `$INSTANCE_NAME`_SAR_INTR_REG;
    
    /* ISR Macro Callback */
    #ifdef `$INSTANCE_NAME`_ISR_CALLBACK
		`$INSTANCE_NAME`_ISR_Callback();
	#endif

    /************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    *************************************************************************/
    /* `#START MAIN_`$INSTANCE_NAME`_ISR`  */

    /* `#END`  */

    /* Clear handled interrupt */
    `$INSTANCE_NAME`_SAR_INTR_REG = intr_status;
}

/* [] END OF FILE */
