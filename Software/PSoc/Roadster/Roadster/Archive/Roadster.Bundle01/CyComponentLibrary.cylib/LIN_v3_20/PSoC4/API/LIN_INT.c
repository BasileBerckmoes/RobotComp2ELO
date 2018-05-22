/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the code that operates during the interrupt service
*  routine.
*
********************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "`$INSTANCE_NAME`.h"
#include "LIN_Dynamic.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

CY_ISR(`$INSTANCE_NAME`_UART_ISR)
{
    #ifdef `$INSTANCE_NAME`_UART_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_UART_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_UART_ISR_ENTRY_CALLBACK */

    l_ifc_rx_`$INSTANCE_NAME`();

    #ifdef `$INSTANCE_NAME`_UART_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_UART_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_UART_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
