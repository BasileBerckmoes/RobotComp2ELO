/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides the source code to the API for the SMIF component.
*
*******************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if defined(__cplusplus)
extern "C" {
#endif


/***************************************
*     Global variables
***************************************/


/** `$INSTANCE_NAME`_initVar Indicates whether the `$INSTANCE_NAME` component
* has been initialized. The variable is initialized to 0 and set to 1 the first
* time `$INSTANCE_NAME`_Start() is called. This allows the component to restart
* without reinitialization after the first call to the `$INSTANCE_NAME`_Start()
* routine. */
uint8_t `$INSTANCE_NAME`_initVar = 0U;

/* Allocate space for the context and initialize. */
cy_stc_smif_context_t `$INSTANCE_NAME`_context;

/* Allocate space memories configurations sorted by the slot number. */
cy_stc_smif_mem_config_t* `$INSTANCE_NAME`_memSlotConfigs[`$INSTANCE_NAME`_MAX_SLOT_NUMBER];

/* Allocate the space device configuration. */
cy_stc_smif_config_t `=$CY_CONST_CONFIG ? "const" : ""` `$INSTANCE_NAME`_config =
{
    .mode           = (uint32_t)CY_SMIF_NORMAL,
    .deselectDelay  = `$INSTANCE_NAME`_DESELECT_DELAY,
    .rxClockSel     = (uint32_t)CY_SMIF_SEL_INV_INTERNAL_CLK,
    .blockEvent     = (uint32_t)CY_SMIF_BUS_ERROR
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  This function starts the SMIF block allocating and configuring its 
*  interrupt for Normal mode. This function initializes all the memory slots,
*  sets the trigger level, and enables Memory mode cache with prefetching.     
*  The SMIF HW block is configured according to the \ref `$INSTANCE_NAME`_config 
*  values.
*   
*  \note Changing of SMIF mode does not invalidate cache. Invalidate cache after changing the mode 
*  from Normal to Memory to prevent the reading 
*  of outdated values from cache in Memory mode.  
*   
* \param configStruct
* Define configuration of the external memories connected to the SMIF.
*
* \param timeout
* Timeout in microseconds for blocking APIs in use.
*
* \globalvars
*  - `$INSTANCE_NAME`_initVar - Checks the initial configuration modified
*  on the first function call.
*  - `$INSTANCE_NAME`_memSlotConfigs - Allocates the array of external memory 
*  configuration structures.
*
*******************************************************************************/
cy_en_smif_status_t `$INSTANCE_NAME`_Start(cy_stc_smif_block_config_t *blockConfig, uint32_t timeoutMs)
{
    if (0U == `$INSTANCE_NAME`_initVar)
    {
        /* Configure the component. */
        (void) Cy_SMIF_Init(`$INSTANCE_NAME`_HW , &`$INSTANCE_NAME`_config, timeoutMs, &`$INSTANCE_NAME`_context);
        
        /* Configure the interrupt sources. */
        Cy_SMIF_SetInterruptMask(`$INSTANCE_NAME`_HW , `$INSTANCE_NAME`_SMIF_INTR_MASK);
        
        /* Configure the trigger levels. */
        Cy_SMIF_SetTxFifoTriggerLevel(`$INSTANCE_NAME`_HW , `$INSTANCE_NAME`_TX_FIFO_TRIGEER_LEVEL);
        Cy_SMIF_SetRxFifoTriggerLevel(`$INSTANCE_NAME`_HW , `$INSTANCE_NAME`_RX_FIFO_TRIGEER_LEVEL);

        /* Hook the interrupt service routine. */


        #if defined(`$INSTANCE_NAME`_SMIF_IRQ__INTC_ASSIGNED)
           (void)Cy_SysInt_Init(&`$INSTANCE_NAME`_SMIF_IRQ_cfg, &`$INSTANCE_NAME`_Interrupt);
        #endif /* defined(`$INSTANCE_NAME`_SMIF_IRQ__INTC_ASSIGNED) */
        
        /* Enable the fast and slow caches with pre-fetching */
        (void)Cy_SMIF_CacheEnable(`$INSTANCE_NAME`_HW, CY_SMIF_CACHE_BOTH);
        (void)Cy_SMIF_CachePrefetchingEnable(`$INSTANCE_NAME`_HW, CY_SMIF_CACHE_BOTH);

        /* The component is configured. */
        `$INSTANCE_NAME`_initVar = 1U;
    }

    /* Enable the interrupt in NVIC. */
    #if defined(`$INSTANCE_NAME`_SMIF_IRQ__INTC_ASSIGNED)
       NVIC_EnableIRQ((IRQn_Type)`$INSTANCE_NAME`_SMIF_IRQ_cfg.intrSrc);
    #endif /*CY_CPU_CORTEX_M0P*/


    Cy_SMIF_Enable(`$INSTANCE_NAME`_HW , &`$INSTANCE_NAME`_context);

    /* Initialization of the SMIF DEVICE region needs the SMIF IP up and running to 
     * auto-detect configuration from external memory. */
    return `$INSTANCE_NAME`_Mem_Init(blockConfig); 
}

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
