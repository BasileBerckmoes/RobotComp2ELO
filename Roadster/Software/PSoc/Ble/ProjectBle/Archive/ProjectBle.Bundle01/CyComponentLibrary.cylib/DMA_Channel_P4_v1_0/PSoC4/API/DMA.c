/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains all of the channel DMA API functions.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Calls Init() to configure the DMA channel based on the customizer settings if
*  the channel has not been initialized before.
*  Sets source and destination address, validates descriptor 0 and enables the
*  channel. After calling this function the DMA channel is active and waiting
*  for a trigger.
*
* Parameters:
*  srcAddress: Address of DMA transfer source for descriptor 0.
*  dstAddress: Address of DMA transfer destination for descriptor 0.
*                   
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void * srcAddress, void * dstAddress)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    CyDmaEnable();
    `$INSTANCE_NAME`_SetSrcAddress(0, srcAddress);
    `$INSTANCE_NAME`_SetDstAddress(0, dstAddress);
    `$INSTANCE_NAME`_ValidateDescriptor(0);
    `$INSTANCE_NAME`_ChEnable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the DMA channel based on the parameters set in the component
*  customizer. It is not necessary to call `$INSTANCE_NAME`_Init() because the
*  `$INSTANCE_NAME`_Start() API calls this function, which is the preferred method
*  to begin component operation.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  The first descriptor is set to descriptor 0. This function should not be
*  called while the channel is enabled. All settings will be reset to their
*  initial values.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    CYDMA_CH_CTL_BASE.ctl[`$INSTANCE_NAME`_CHANNEL] = `$INSTANCE_NAME`_CHANNEL_CFG;
    CYDMA_DESCR_BASE.descriptor[`$INSTANCE_NAME`_CHANNEL][0].ctl = `$INSTANCE_NAME`_DESCR0_CFG;
    CYDMA_DESCR_BASE.descriptor[`$INSTANCE_NAME`_CHANNEL][1].ctl = `$INSTANCE_NAME`_DESCR1_CFG;

    /* If the Generate IRQ option is selected for descriptor 0 or 1, set the
    * channel bit field in the DMA interrupt mask register.
    */
    #if (0u != ((`$INSTANCE_NAME`_DESCR0_CFG | `$INSTANCE_NAME`_DESCR1_CFG) & CYDMA_GENERATE_IRQ))
        CYDMA_INTR_MASK_REG |= `$INSTANCE_NAME`_CHANNEL_MASK;
    #endif /* (0u != ((`$INSTANCE_NAME`_DESCR0_CFG | `$INSTANCE_NAME`_DESCR1_CFG) & CYDMA_GENERATE_IRQ)) */
}


/* [] END OF FILE */
