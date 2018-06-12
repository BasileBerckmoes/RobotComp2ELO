/***************************************************************************//**
* \file `$INSTANCE_NAME`_I2C.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 `$INSTANCE_NAME`_state;  /* Current state of I2C FSM */

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const `$INSTANCE_NAME`_I2C_INIT_STRUCT `$INSTANCE_NAME`_configI2C =
    {
        `$INSTANCE_NAME`_I2C_MODE,
        `$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW,
        `$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH,
        `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE,
        `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS,
        `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS_MASK,
        `$INSTANCE_NAME`_I2C_ACCEPT_ADDRESS,
        `$INSTANCE_NAME`_I2C_WAKE_ENABLE,
        `$INSTANCE_NAME`_I2C_BYTE_MODE_ENABLE,
        `$INSTANCE_NAME`_I2C_DATA_RATE,
        `$INSTANCE_NAME`_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the `$INSTANCE_NAME` for I2C operation.
    *
    *  This function is intended specifically to be used when the `$INSTANCE_NAME` 
    *  configuration is set to “Unconfigured `$INSTANCE_NAME`” in the customizer. 
    *  After initializing the `$INSTANCE_NAME` in I2C mode using this function, 
    *  the component can be enabled using the `$INSTANCE_NAME`_Start() or 
    * `$INSTANCE_NAME`_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CInit(const `$INSTANCE_NAME`_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_I2C, `$INSTANCE_NAME`_DUMMY_PARAM,
                                     `$INSTANCE_NAME`_DUMMY_PARAM);

            /* Store internal configuration */
            `$INSTANCE_NAME`_scbMode       = (uint8) `$INSTANCE_NAME`_SCB_MODE_I2C;
            `$INSTANCE_NAME`_scbEnableWake = (uint8) config->enableWake;
            `$INSTANCE_NAME`_scbEnableIntr = (uint8) `$INSTANCE_NAME`_SCB_IRQ_INTERNAL;

            `$INSTANCE_NAME`_mode          = (uint8) config->mode;
            `$INSTANCE_NAME`_acceptAddr    = (uint8) config->acceptAddr;

        #if (`$INSTANCE_NAME`_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((`$INSTANCE_NAME`_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= `$INSTANCE_NAME`_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (`$INSTANCE_NAME`_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = `$INSTANCE_NAME`_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = `$INSTANCE_NAME`_DIGITAL_FILTER_ENABLE;
            }

        #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
            locEnableWake = (`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

            /* Configure I2C interface */
            `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE (locEnableWake);

            `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    `$INSTANCE_NAME`_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    `$INSTANCE_NAME`_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    `$INSTANCE_NAME`_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                `$INSTANCE_NAME`_I2C_RX_CTRL;
            `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_CLEAR_REG;

            /* Set default address and mask */
            `$INSTANCE_NAME`_RX_MATCH_REG    = ((`$INSTANCE_NAME`_I2C_SLAVE) ?
                                                (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (`$INSTANCE_NAME`_CLEAR_REG));


            /* Configure TX direction */
            `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_I2C_TX_CTRL;
            `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
            CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
            (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_I2C_ISR);

            /* Configure interrupt sources */
        #if(!`$INSTANCE_NAME`_CY_SCBIP_V1)
            `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

            `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;
            `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;

            `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = ((`$INSTANCE_NAME`_I2C_SLAVE) ?
                            (`$INSTANCE_NAME`_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             `$INSTANCE_NAME`_I2C_INTR_SLAVE_MASK) : (`$INSTANCE_NAME`_CLEAR_REG));

            `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = ((`$INSTANCE_NAME`_I2C_MASTER) ?
                                                     (`$INSTANCE_NAME`_I2C_INTR_MASTER_MASK) :
                                                     (`$INSTANCE_NAME`_CLEAR_REG));

            /* Configure global variables */
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

            /* Internal slave variables */
            `$INSTANCE_NAME`_slStatus        = 0u;
            `$INSTANCE_NAME`_slRdBufIndex    = 0u;
            `$INSTANCE_NAME`_slWrBufIndex    = 0u;
            `$INSTANCE_NAME`_slOverFlowCount = 0u;

            /* Internal master variables */
            `$INSTANCE_NAME`_mstrStatus     = 0u;
            `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
            `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CInit(void)
    {
    #if(`$INSTANCE_NAME`_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        `$INSTANCE_NAME`_SET_I2C_CFG_SDA_FILT_TRIM(`$INSTANCE_NAME`_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        `$INSTANCE_NAME`_CTRL_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_CTRL;
        `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        `$INSTANCE_NAME`_RX_CTRL_REG      = `$INSTANCE_NAME`_I2C_DEFAULT_RX_CTRL;
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        `$INSTANCE_NAME`_RX_MATCH_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        `$INSTANCE_NAME`_TX_CTRL_REG      = `$INSTANCE_NAME`_I2C_DEFAULT_TX_CTRL;
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (`$INSTANCE_NAME`_ISR_NUMBER);
        CyIntSetPriority(`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
    #if(!`$INSTANCE_NAME`_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_I2C_ISR);
    #endif /* (`$INSTANCE_NAME`_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!`$INSTANCE_NAME`_CY_SCBIP_V1)
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_I2C_EC_MASK;
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_SLAVE_MASK;
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_MASTER_MASK;
        `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_RX_MASK;
        `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

    #if(`$INSTANCE_NAME`_I2C_SLAVE)
        /* Internal slave variable */
        `$INSTANCE_NAME`_slStatus        = 0u;
        `$INSTANCE_NAME`_slRdBufIndex    = 0u;
        `$INSTANCE_NAME`_slWrBufIndex    = 0u;
        `$INSTANCE_NAME`_slOverFlowCount = 0u;
    #endif /* (`$INSTANCE_NAME`_I2C_SLAVE) */

    #if(`$INSTANCE_NAME`_I2C_MASTER)
    /* Internal master variable */
        `$INSTANCE_NAME`_mstrStatus     = 0u;
        `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
        `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
    #endif /* (`$INSTANCE_NAME`_I2C_MASTER) */
    }
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CStop(void)
{
    `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
}


#if(`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CSaveConfig(void)
    {
    #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
        #if (`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST && `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (`$INSTANCE_NAME`_CTRL_REG & `$INSTANCE_NAME`_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                `$INSTANCE_NAME`_Stop();
                `$INSTANCE_NAME`_CTRL_REG |= `$INSTANCE_NAME`_CTRL_EC_AM_MODE;
                `$INSTANCE_NAME`_Enable();
            }
        #endif /* (`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (`$INSTANCE_NAME`_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            `$INSTANCE_NAME`_SCBCLK_Stop();
        #endif /* (`$INSTANCE_NAME`_SCB_CLK_INTERNAL) */
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

    #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
        #if (`$INSTANCE_NAME`_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            `$INSTANCE_NAME`_SCBCLK_Start();
        #endif /* (`$INSTANCE_NAME`_SCB_CLK_INTERNAL) */
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */
    }
#endif /* (`$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
