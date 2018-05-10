/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the S/PDIF
*  Transmitter component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


#if(0u != `$INSTANCE_NAME`_MANAGED_DMA)
    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_Cst0Copy
    ****************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine to implement double buffered DMA for Channel 0
    *  Status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_cst0BufOffset - used as offset for buffer management.
    *  `$INSTANCE_NAME`_cstStream0[`$INSTANCE_NAME`_CST_LENGTH] - destination
    *  array for Channel 0 status. Used as source data for status DMA.
    *  `$INSTANCE_NAME`_wrkCstStream0[`$INSTANCE_NAME`_CST_LENGTH] - source
    *  array for Channel 0 status. Used to allow Channel 0 status changing at
    *  run time.
    *
    ***************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_Cst0Copy)
    {
        uint8 offset;
        
        #ifdef `$INSTANCE_NAME`_CST0_COPY_ENTRY_CALLBACK
            `$INSTANCE_NAME`_Cst0Copy_EntryCallback();
        #endif /* `$INSTANCE_NAME`_CST0_COPY_ENTRY_CALLBACK */

        offset = `$INSTANCE_NAME`_cst0BufOffset;
        
        (void) memcpy((void *) &`$INSTANCE_NAME`_cstStream0[offset],
                      (void *) &`$INSTANCE_NAME`_wrkCstStream0[offset],
                      `$INSTANCE_NAME`_CST_HALF_LENGTH);

        `$INSTANCE_NAME`_cst0BufOffset ^= `$INSTANCE_NAME`_CST_HALF_LENGTH;

        #ifdef `$INSTANCE_NAME`_CST0_COPY_EXIT_CALLBACK
            `$INSTANCE_NAME`_Cst0Copy_ExitCallback();
        #endif /* `$INSTANCE_NAME`_CST0_COPY_EXIT_CALLBACK */
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_Cst1Copy
    ****************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine to implement double buffered DMA for Channel 1
    *  Status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_cst1BufOffset - used as offset for buffer management.
    *  `$INSTANCE_NAME`_cstStream1[`$INSTANCE_NAME`_CST_LENGTH] - destination
    *  array or Channel 1 status. Used as source data for status DMA.
    *  `$INSTANCE_NAME`_wrkCstStream1[`$INSTANCE_NAME`_CST_LENGTH] - source
    *  array for Channel 1 status. Used to allow Channel 1 status changing at run
    *  time.
    *
    ***************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_Cst1Copy)
    {
        uint8 offset;
        
        #ifdef `$INSTANCE_NAME`_CST1_COPY_ENTRY_CALLBACK
            `$INSTANCE_NAME`_Cst1Copy_EntryCallback();
        #endif /* `$INSTANCE_NAME`_CST1_COPY_ENTRY_CALLBACK */

        offset = `$INSTANCE_NAME`_cst1BufOffset;
        
        (void) memcpy((void *) &`$INSTANCE_NAME`_cstStream1[offset],
                      (void *) &`$INSTANCE_NAME`_wrkCstStream1[offset],
                      `$INSTANCE_NAME`_CST_HALF_LENGTH);

        `$INSTANCE_NAME`_cst1BufOffset ^= `$INSTANCE_NAME`_CST_HALF_LENGTH;

        #ifdef `$INSTANCE_NAME`_CST1_COPY_EXIT_CALLBACK
            `$INSTANCE_NAME`_Cst1Copy_ExitCallback();
        #endif /* `$INSTANCE_NAME`_CST1_COPY_EXIT_CALLBACK */
    }

#endif  /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */


/* [] END OF FILE */
