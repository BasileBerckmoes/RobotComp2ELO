/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides the source code to the API for the I2C Component.
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
* The pointer to this structure should be passed to Cy_SCB_I2C_Init function
* to initialize component with GUI selected settings.
*/
cy_stc_scb_i2c_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
    .i2cMode    = `= (1 == $Mode) ? "CY_SCB_I2C_SLAVE" : (2 == $Mode) ? "CY_SCB_I2C_MASTER" : "CY_SCB_I2C_MASTER_SLAVE"`,

    .useRxFifo = `= $IsEnableRxFifoVisible ? ($EnableRxFifo ? "true" : "false") : "false"`,
    .useTxFifo = `= $EnableTxFifo ? "true" : "false"`,

    .slaveAddress        = `= $IsSlaveVisible ? IntToHexString(`$SlaveAddress`) : "0"`U,
    .slaveAddressMask    = `= $IsSlaveVisible ? IntToHexString(`$SlaveAddressMask`) : "0"`U,
    .acceptAddrInFifo    = `= $IsSlaveVisible ? ($AcceptAddress ? "true" : "false") : "false"`,
    .ackGeneralAddr      = `= $IsSlaveVisible ? ($AcceptGeneralCall ? "true" : "false") : "false"`,

    .enableWakeFromSleep = `= $DeepSleepCapable ? "true" : "false"`
};

/** The instance-specific context structure.
* It is used while the driver operation for internal configuration and
* data keeping for the I2C. The user should not modify anything in this
* structure.
*/
cy_stc_scb_i2c_context_t `$INSTANCE_NAME`_context;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Invokes `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable().
* Also configures interrupt and low and high oversampling phases.
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
        (void) Cy_SCB_I2C_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config, &`$INSTANCE_NAME`_context);

    #if (`$INSTANCE_NAME`_ENABLE_MASTER)
        /* Configure desired data rate */
        (void) Cy_SCB_I2C_SetDataRate(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_DATA_RATE_HZ, `$INSTANCE_NAME`_CLK_FREQ_HZ);

        #if (`$INSTANCE_NAME`_MANUAL_SCL_CONTROL)
            Cy_SCB_I2C_MasterSetLowPhaseDutyCycle (`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_LOW_PHASE_DUTY_CYCLE);
            Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_HIGH_PHASE_DUTY_CYCLE);
        #endif /* (`$INSTANCE_NAME`_MANUAL_SCL_CONTROL) */
    #endif /* (`$INSTANCE_NAME`_ENABLE_MASTER) */

        /* Hook interrupt service routine */
    #if defined(`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED)
        (void) Cy_SysInt_Init(&`$INSTANCE_NAME`_SCB_IRQ_cfg, &`$INSTANCE_NAME`_Interrupt);
    #endif /* (`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED) */

        `$INSTANCE_NAME`_initVar = 1U;
    }

    /* Enable interrupt in NVIC */
#if defined(`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED)
    NVIC_EnableIRQ((IRQn_Type) `$INSTANCE_NAME`_SCB_IRQ_cfg.intrSrc);
#endif /* (`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED) */

    Cy_SCB_I2C_Enable(`$INSTANCE_NAME`_HW);
}

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
