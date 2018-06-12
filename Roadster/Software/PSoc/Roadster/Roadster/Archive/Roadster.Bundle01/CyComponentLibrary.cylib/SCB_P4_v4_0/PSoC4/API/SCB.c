/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

#if (`$INSTANCE_NAME`_SCB_MODE_I2C_INC)
    #include "`$INSTANCE_NAME`_I2C_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_INC) */

#if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC)
    #include "`$INSTANCE_NAME`_EZI2C_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_EZI2C_INC) */

#if (`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC)
    #include "`$INSTANCE_NAME`_SPI_UART_PVT.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_INC || `$INSTANCE_NAME`_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_UNCONFIG;
    uint8 `$INSTANCE_NAME`_scbEnableWake;
    uint8 `$INSTANCE_NAME`_scbEnableIntr;

    /* I2C configuration variables */
    uint8 `$INSTANCE_NAME`_mode;
    uint8 `$INSTANCE_NAME`_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * `$INSTANCE_NAME`_rxBuffer;
    uint8  `$INSTANCE_NAME`_rxDataBits;
    uint32 `$INSTANCE_NAME`_rxBufferSize;

    volatile uint8 * `$INSTANCE_NAME`_txBuffer;
    uint8  `$INSTANCE_NAME`_txDataBits;
    uint32 `$INSTANCE_NAME`_txBufferSize;

    /* EZI2C configuration variables */
    uint8 `$INSTANCE_NAME`_numberOfAddr;
    uint8 `$INSTANCE_NAME`_subAddrSize;
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME` 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  `$INSTANCE_NAME`_Init() function can be called before the 
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable() function.
*/
uint8 `$INSTANCE_NAME`_initVar = 0u;


#if (! (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG || \
        `$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * `$INSTANCE_NAME`_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent `$INSTANCE_NAME`_Enable() call.
    */
    uint16 `$INSTANCE_NAME`_IntrTxMask = 0u;
#endif /* (! (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG || \
              `$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER)
    void (*`$INSTANCE_NAME`_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER) */
#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void `$INSTANCE_NAME`_ScbEnableIntr(void);
static void `$INSTANCE_NAME`_ScbModeStop(void);
static void `$INSTANCE_NAME`_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  Initializes the `$INSTANCE_NAME` component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  `$INSTANCE_NAME`_I2CInit, `$INSTANCE_NAME`_SpiInit, 
*  `$INSTANCE_NAME`_UartInit or `$INSTANCE_NAME`_EzI2CInit.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
    `$INSTANCE_NAME`_I2CInit();

#elif (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
    `$INSTANCE_NAME`_SpiInit();

#elif (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
    `$INSTANCE_NAME`_UartInit();

#elif (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
    `$INSTANCE_NAME`_EzI2CInit();

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
*  Enables `$INSTANCE_NAME` component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  `$INSTANCE_NAME`_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The `$INSTANCE_NAME` configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured `$INSTANCE_NAME`”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_CTRL_REG |= `$INSTANCE_NAME`_CTRL_ENABLED;

        `$INSTANCE_NAME`_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        `$INSTANCE_NAME`_ScbModePostEnable();
    }
#else
    `$INSTANCE_NAME`_CTRL_REG |= `$INSTANCE_NAME`_CTRL_ENABLED;

    `$INSTANCE_NAME`_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    `$INSTANCE_NAME`_ScbModePostEnable();
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Invokes `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u; /* Component was initialized */
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
*  Disables the `$INSTANCE_NAME` component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function `$INSTANCE_NAME`_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
    `$INSTANCE_NAME`_DisableInt();
#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    `$INSTANCE_NAME`_ScbModeStop();

    /* Disable SCB IP */
    `$INSTANCE_NAME`_CTRL_REG &= (uint32) ~`$INSTANCE_NAME`_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);

#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
    `$INSTANCE_NAME`_ClearPendingInt();
#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = `$INSTANCE_NAME`_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~`$INSTANCE_NAME`_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (`$INSTANCE_NAME`_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = `$INSTANCE_NAME`_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~`$INSTANCE_NAME`_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (`$INSTANCE_NAME`_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER)
        `$INSTANCE_NAME`_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_`$INSTANCE_NAME`_CUSTOM_INTR_HANDLER) */
    }
#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ScbEnableIntr(void)
{
#if (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != `$INSTANCE_NAME`_scbEnableIntr)
        {
            `$INSTANCE_NAME`_EnableInt();
        }

    #else
        `$INSTANCE_NAME`_EnableInt();

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (`$INSTANCE_NAME`_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ScbModePostEnable(void)
{
#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    if (`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_SpiPostEnable();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

#elif (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
    `$INSTANCE_NAME`_SpiPostEnable();

#elif (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
    `$INSTANCE_NAME`_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ScbModeStop(void)
{
#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    if (`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_I2CStop();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_EzI2CStop();
    }
#if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
    else if (`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_SpiStop();
    }
    else if (`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
    {
        `$INSTANCE_NAME`_UartStop();
    }
#endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
    `$INSTANCE_NAME`_I2CStop();

#elif (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
    `$INSTANCE_NAME`_EzI2CStop();

#elif (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
    `$INSTANCE_NAME`_SpiStop();

#elif (`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
    `$INSTANCE_NAME`_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[`$INSTANCE_NAME`_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
        
        uint32 hsiomSel[`$INSTANCE_NAME`_SCB_PINS_NUMBER] = 
        {
            `$HsiomSelInit`
        };

    #if (`$INSTANCE_NAME`_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < `$INSTANCE_NAME`_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = `$INSTANCE_NAME`_PIN_DM_ALG_HIZ;
        }

        if ((`$INSTANCE_NAME`_SCB_MODE_I2C   == mode) ||
            (`$INSTANCE_NAME`_SCB_MODE_EZI2C == mode))
        {
        #if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_I2C;
            pinsDm  [`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_OD_LO;
        #elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_I2C;
            pinsDm  [`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_OD_LO;
        #else
        #endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */
        
        #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_I2C;
            pinsDm  [`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_OD_LO;
        #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */
        }
    #if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
        else if (`$INSTANCE_NAME`_SCB_MODE_SPI == mode)
        {
        #if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_SPI;
        #elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_SPI;
        #else
        #endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */
        
        #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_SPI;
        #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */
        
        #if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
            hsiomSel[`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_SPI;
        #endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN) */

            if (`$INSTANCE_NAME`_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;
                pinsDm[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                pinsDm[`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;

            #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_SPI;
                pinsDm  [`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;
            #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

            #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
                /* Disable input buffer */
                 pinsInBuf |= `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_MASK;
            #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                pinsDm[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;
                pinsDm[`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;

            #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
                hsiomSel [`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_SPI;
                pinsDm   [`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                pinsInBuf |= `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_MASK;
            #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

            #if (`$INSTANCE_NAME`_SS1_PIN)
                hsiomSel [`$INSTANCE_NAME`_SS1_PIN_INDEX] = `$INSTANCE_NAME`_SS1_HSIOM_SEL_SPI;
                pinsDm   [`$INSTANCE_NAME`_SS1_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                pinsInBuf |= `$INSTANCE_NAME`_SS1_PIN_MASK;
            #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

            #if (`$INSTANCE_NAME`_SS2_PIN)
                hsiomSel [`$INSTANCE_NAME`_SS2_PIN_INDEX] = `$INSTANCE_NAME`_SS2_HSIOM_SEL_SPI;
                pinsDm   [`$INSTANCE_NAME`_SS2_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                pinsInBuf |= `$INSTANCE_NAME`_SS2_PIN_MASK;
            #endif /* (`$INSTANCE_NAME`_SS2_PIN) */

            #if (`$INSTANCE_NAME`_SS3_PIN)
                hsiomSel [`$INSTANCE_NAME`_SS3_PIN_INDEX] = `$INSTANCE_NAME`_SS3_HSIOM_SEL_SPI;
                pinsDm   [`$INSTANCE_NAME`_SS3_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                pinsInBuf |= `$INSTANCE_NAME`_SS3_PIN_MASK;
            #endif /* (`$INSTANCE_NAME`_SS3_PIN) */

                /* Disable input buffers */
            #if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
                pinsInBuf |= `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_MASK;
            #elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
                pinsInBuf |= `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_MASK;
            #else
            #endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */

            #if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
                pinsInBuf |= `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_MASK;
            #endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN) */
            }
        }
        else /* UART */
        {
            if (`$INSTANCE_NAME`_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
                hsiomSel[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_UART;
                pinsDm  [`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_OD_LO;
            #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (`$INSTANCE_NAME`_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
                    hsiomSel[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_UART;
                    pinsDm  [`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;
                #elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
                    hsiomSel[`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_UART;
                    pinsDm  [`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;
                #else
                #endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */
                }

                if (0u != (`$INSTANCE_NAME`_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
                    hsiomSel[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_UART;
                    pinsDm  [`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_MASK;
                #endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */
                }

            #if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
                if (`$INSTANCE_NAME`_UART_MODE_STD == subMode)
                {
                    if (0u != (`$INSTANCE_NAME`_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
                        hsiomSel[`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_UART;
                        pinsDm  [`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_DIG_HIZ;
                    #endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN) */
                    }

                    if (0u != (`$INSTANCE_NAME`_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
                        hsiomSel[`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_UART;
                        pinsDm  [`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX] = `$INSTANCE_NAME`_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_MASK;
                    #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */
                    }
                }
            #endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */
            }
        }
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_REG,
                                       `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_POS,
                                        hsiomSel[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX]);

        `$INSTANCE_NAME`_`$PinName0Unconfig`_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX]);

        #if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
            `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_`$PinName0Unconfig`_INP_DIS,
                                         `$INSTANCE_NAME`_`$PinName0Unconfig`_MASK,
                                         (0u != (pinsInBuf & `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_MASK)));
        #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    
    #elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG,
                                       `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_POS,
                                       hsiomSel[`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX]);

        `$INSTANCE_NAME`_`$PinName0UnconfigWake`_SetDriveMode((uint8)
                                                               pinsDm[`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX]);

        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_`$PinName0UnconfigWake`_INP_DIS,
                                     `$INSTANCE_NAME`_`$PinName0UnconfigWake`_MASK,
                                     (0u != (pinsInBuf & `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_MASK)));

         /* Set interrupt on falling edge */
        `$INSTANCE_NAME`_SET_INCFG_TYPE(`$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_REG,
                                        `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_TYPE_MASK,
                                        `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_TYPE_POS,
                                        `$INSTANCE_NAME`_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN) */

    #if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG,
                                       `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_POS,
                                        hsiomSel[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX]);

        `$INSTANCE_NAME`_`$PinName1Unconfig`_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX]);

    #if (!`$INSTANCE_NAME`_CY_SCBIP_V1)
        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_`$PinName1Unconfig`_INP_DIS,
                                     `$INSTANCE_NAME`_`$PinName1Unconfig`_MASK,
                                    (0u != (pinsInBuf & `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_MASK)));
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V1) */
    #endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_REG,
                                       `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_POS,
                                       hsiomSel[`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX]);

        `$INSTANCE_NAME`_`$PinName2Unconfig`_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX]);

        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_`$PinName2Unconfig`_INP_DIS,
                                     `$INSTANCE_NAME`_`$PinName2Unconfig`_MASK,
                                     (0u != (pinsInBuf & `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_MASK)));
    #endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG,
                                       `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK,
                                       `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS,
                                       hsiomSel[`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX]);

        `$INSTANCE_NAME`_`$PinName3Unconfig`_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX]);

        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_`$PinName3Unconfig`_INP_DIS,
                                     `$INSTANCE_NAME`_`$PinName3Unconfig`_MASK,
                                     (0u != (pinsInBuf & `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_MASK)));
    #endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

    #if (`$INSTANCE_NAME`_SS1_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS1_HSIOM_REG,
                                       `$INSTANCE_NAME`_SS1_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS1_HSIOM_POS,
                                       hsiomSel[`$INSTANCE_NAME`_SS1_PIN_INDEX]);

        `$INSTANCE_NAME`_spi_ss1_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_SS1_PIN_INDEX]);

        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_spi_ss1_INP_DIS,
                                     `$INSTANCE_NAME`_spi_ss1_MASK,
                                     (0u != (pinsInBuf & `$INSTANCE_NAME`_SS1_PIN_MASK)));
    #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

    #if (`$INSTANCE_NAME`_SS2_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS2_HSIOM_REG,
                                       `$INSTANCE_NAME`_SS2_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS2_HSIOM_POS,
                                       hsiomSel[`$INSTANCE_NAME`_SS2_PIN_INDEX]);

        `$INSTANCE_NAME`_spi_ss2_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_SS2_PIN_INDEX]);

        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_spi_ss2_INP_DIS,
                                     `$INSTANCE_NAME`_spi_ss2_MASK,
                                     (0u != (pinsInBuf & `$INSTANCE_NAME`_SS2_PIN_MASK)));
    #endif /* (`$INSTANCE_NAME`_SS2_PIN) */

    #if (`$INSTANCE_NAME`_SS3_PIN)
        `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS3_HSIOM_REG,
                                       `$INSTANCE_NAME`_SS3_HSIOM_MASK,
                                       `$INSTANCE_NAME`_SS3_HSIOM_POS,
                                       hsiomSel[`$INSTANCE_NAME`_SS3_PIN_INDEX]);

        `$INSTANCE_NAME`_spi_ss3_SetDriveMode((uint8) pinsDm[`$INSTANCE_NAME`_SS3_PIN_INDEX]);

        `$INSTANCE_NAME`_SET_INP_DIS(`$INSTANCE_NAME`_spi_ss3_INP_DIS,
                                     `$INSTANCE_NAME`_spi_ss3_MASK,
                                     (0u != (pinsInBuf & `$INSTANCE_NAME`_SS3_PIN_MASK)));
    #endif /* (`$INSTANCE_NAME`_SS3_PIN) */
    }

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (`$INSTANCE_NAME`_CTRL_REG & `$INSTANCE_NAME`_CTRL_EC_AM_MODE)) &&
            (0u == (`$INSTANCE_NAME`_I2C_CTRL_REG & `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            `$INSTANCE_NAME`_CTRL_REG &= ~`$INSTANCE_NAME`_CTRL_EC_AM_MODE;
            `$INSTANCE_NAME`_CTRL_REG |=  `$INSTANCE_NAME`_CTRL_EC_AM_MODE;
        }

        `$INSTANCE_NAME`_I2C_SLAVE_CMD_REG = `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */


/* [] END OF FILE */
