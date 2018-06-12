/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides the source code to the API for the SPI Component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "sysint/cy_sysint.h"
#include "cyfitter_sysint.h"
#include "cyfitter_sysint_cfg.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*     Global variables
***************************************/

/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME`
*  component has been initialized. The variable is initialized to 0
*  and set to 1 the first time `$INSTANCE_NAME`_Start() is called.
*  This allows  the component to restart without reinitialization
*  after the first call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the
*  `$INSTANCE_NAME`_Init() function can be called before the
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable() function.
*/
uint8_t `$INSTANCE_NAME`_initVar = 0U;

/** The instance-specific configuration structure.
* The pointer to this structure should be passed to Cy_SCB_SPI_Init function
* to initialize component with GUI selected settings.
*/
cy_stc_scb_spi_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
    .spiMode  = `= (0 == $Mode) ? "CY_SCB_SPI_SLAVE" : "CY_SCB_SPI_MASTER"`,
    .subMode  = `= (0 == $SubMode) ? "CY_SCB_SPI_MOTOROLA" : (1 == $Mode) ? "CY_SCB_SPI_TI_COINCIDES" : (2 == $Mode) ? "CY_SCB_SPI_TI_PRECEDES" : "CY_SCB_SPI_NATIONAL"`,
    .sclkMode = `= (0 == $SclkMode) ? "CY_SCB_SPI_CPHA0_CPOL0" : (1 == $SclkMode) ? "CY_SCB_SPI_CPHA0_CPOL1" : (2 == $SclkMode) ? "CY_SCB_SPI_CPHA1_CPOL0" : "CY_SCB_SPI_CPHA1_CPOL1"`,

    .oversample = `= $MasterMode ? $OvsFactor : "0"`UL,

    .rxDataWidth              = `$RxDataWidth`UL,
    .txDataWidth              = `$TxDataWidth`UL,
    .enableMsbFirst           = `= $BitsOrder ? "true" : "false"`,
    .enableInputFilter        = `= $EnableInputFilter ? "true" : "false"`,

    .enableFreeRunSclk        = `= ($MasterMode && $EnableFreeRunSclk) ? "true" : "false"`,
    .enableMisoLateSample     = `= ($MasterMode && $EnableLateMisoSample) ? "true" : "false"`,
    .enableTransferSeperation = `= ($MasterMode && $DeassertSelectLine) ? "true" : "false"`,
    .ssPolarity               = ((`=                 (0 != $Ss0Polarity)  ? "((uint32_t) CY_SCB_SPI_ACTIVE_HIGH)" : "((uint32_t) CY_SCB_SPI_ACTIVE_LOW)"` << `$INSTANCE_NAME`_SPI_SLAVE_SELECT0) | \
                                 (`= ($MasterMode && (0 != $Ss1Polarity)) ? "((uint32_t) CY_SCB_SPI_ACTIVE_HIGH)" : "((uint32_t) CY_SCB_SPI_ACTIVE_LOW)"` << `$INSTANCE_NAME`_SPI_SLAVE_SELECT1) | \
                                 (`= ($MasterMode && (0 != $Ss2Polarity)) ? "((uint32_t) CY_SCB_SPI_ACTIVE_HIGH)" : "((uint32_t) CY_SCB_SPI_ACTIVE_LOW)"` << `$INSTANCE_NAME`_SPI_SLAVE_SELECT2) | \
                                 (`= ($MasterMode && (0 != $Ss3Polarity)) ? "((uint32_t) CY_SCB_SPI_ACTIVE_HIGH)" : "((uint32_t) CY_SCB_SPI_ACTIVE_LOW)"` << `$INSTANCE_NAME`_SPI_SLAVE_SELECT3)),

    .enableWakeFromSleep = `= $DeepSleepCapable ? "true" : "false"`,

    .rxFifoTriggerLevel  = `= $IsRxTriggerLevelVisible ? $RxTriggerLevel : "0"`UL,
    .rxFifoIntEnableMask = `= IntToHexString(`$IntrRxMask`)`UL,

    .txFifoTriggerLevel  = `= $IsTxTriggerLevelVisible ? $TxTriggerLevel : "0"`UL,
    .txFifoIntEnableMask = `= IntToHexString(`$IntrTxMask`)`UL,

    .masterSlaveIntEnableMask = `= IntToHexString(`$IntrMasterSlaveMask`)`UL
};

/** The instance-specific context structure.
* It is used while the driver operation for internal configuration and
* data keeping for the SPI. The user should not modify anything in this 
* structure.
*/
cy_stc_scb_spi_context_t `$INSTANCE_NAME`_context;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Invokes `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable().
* Also configures interrupt if it is internal.
* After this function call the component is enabled and ready for operation.
* This is the preferred method to begin component operation.
*
* \globalvars
* \ref `$INSTANCE_NAME`_initVar - used to check initial configuration,
* modified  on first function call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0U == `$INSTANCE_NAME`_initVar)
    {
        /* Configure component */
        (void) Cy_SCB_SPI_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config, &`$INSTANCE_NAME`_context);

        /* Set active slave select to line 0 */
        Cy_SCB_SPI_SetActiveSlaveSelect(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_SPI_SLAVE_SELECT0);

        /* Hook interrupt service routine */
    #if defined(`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED)
        (void) Cy_SysInt_Init(&`$INSTANCE_NAME`_SCB_IRQ_cfg, &`$INSTANCE_NAME`_Interrupt);
    #endif /* (`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED) */

        /* Component is configured */
        `$INSTANCE_NAME`_initVar = 1U;
    }

    /* Enable interrupt in NVIC */
#if defined(`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED)
    NVIC_EnableIRQ((IRQn_Type) `$INSTANCE_NAME`_SCB_IRQ_cfg.intrSrc);
#endif /* (`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED) */

    Cy_SCB_SPI_Enable(`$INSTANCE_NAME`_HW);
}

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
