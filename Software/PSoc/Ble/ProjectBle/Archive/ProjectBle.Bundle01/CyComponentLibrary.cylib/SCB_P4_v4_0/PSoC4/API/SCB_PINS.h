/***************************************************************************//**
* \file `$INSTANCE_NAME`_PINS.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_`$INSTANCE_NAME`_H)
#define CY_SCB_PINS_`$INSTANCE_NAME`_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define `$INSTANCE_NAME`_REMOVE_`$Pn0UnconfigWake`_PIN  (`$RemoveMosiSclRxWake`u)
#define `$INSTANCE_NAME`_REMOVE_`$Pn0Unconfig`_PIN      (`$RemoveMosiSclRx`u)
#define `$INSTANCE_NAME`_REMOVE_`$Pn1Unconfig`_PIN      (`$RemoveMisoSdaTx`u)
#define `$INSTANCE_NAME`_REMOVE_`$Pn2Unconfig`_PIN      (`$RemoveSpiSclk`u)
#define `$INSTANCE_NAME`_REMOVE_`$Pn3Unconfig`_PIN      (`$RemoveSpiSs0`u)
#define `$INSTANCE_NAME`_REMOVE_SS1_PIN                 (`$RemoveSpiSs1`u)
#define `$INSTANCE_NAME`_REMOVE_SS2_PIN                 (`$RemoveSpiSs2`u)
#define `$INSTANCE_NAME`_REMOVE_SS3_PIN                 (`$RemoveSpiSs3`u)

/* Mode defined pins */
#define `$INSTANCE_NAME`_REMOVE_I2C_PINS                (`$RemoveI2cPins`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_PINS         (`$RemoveSpiMasterPins`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SCLK_PIN     (`$RemoveSpiMasterSclk`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_MOSI_PIN     (`$RemoveSpiMasterMosi`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_MISO_PIN     (`$RemoveSpiMasterMiso`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS0_PIN      (`$RemoveSpiMasterSs0Pin`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS1_PIN      (`$RemoveSpiMasterSs1Pin`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS2_PIN      (`$RemoveSpiMasterSs2Pin`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS3_PIN      (`$RemoveSpiMasterSs3Pin`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_SLAVE_PINS          (`$RemoveSpiSlavePins`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_SLAVE_MOSI_PIN      (`$RemoveSpiSlaveMosi`u)
#define `$INSTANCE_NAME`_REMOVE_SPI_SLAVE_MISO_PIN      (`$RemoveSpiSlaveMiso`u)
#define `$INSTANCE_NAME`_REMOVE_UART_TX_PIN             (`$RemoveUartTxPin`u)
#define `$INSTANCE_NAME`_REMOVE_UART_RX_TX_PIN          (`$RemoveUartRxTxPin`u)
#define `$INSTANCE_NAME`_REMOVE_UART_RX_PIN             (`$RemoveUartRxPin`u)
#define `$INSTANCE_NAME`_REMOVE_UART_RX_WAKE_PIN        (`$RemoveUartRxWake`u)
#define `$INSTANCE_NAME`_REMOVE_UART_RTS_PIN            (`$RemoveUartRtsPin`u)
#define `$INSTANCE_NAME`_REMOVE_UART_CTS_PIN            (`$RemoveUartCtsPin`u)

/* Unconfigured pins */
#define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN (0u == `$INSTANCE_NAME`_REMOVE_`$Pn0UnconfigWake`_PIN)
#define `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN     (0u == `$INSTANCE_NAME`_REMOVE_`$Pn0Unconfig`_PIN)
#define `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN     (0u == `$INSTANCE_NAME`_REMOVE_`$Pn1Unconfig`_PIN)
#define `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN     (0u == `$INSTANCE_NAME`_REMOVE_`$Pn2Unconfig`_PIN)
#define `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN     (0u == `$INSTANCE_NAME`_REMOVE_`$Pn3Unconfig`_PIN)
#define `$INSTANCE_NAME`_SS1_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS1_PIN)
#define `$INSTANCE_NAME`_SS2_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS2_PIN)
#define `$INSTANCE_NAME`_SS3_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS3_PIN)

/* Mode defined pins */
#define `$INSTANCE_NAME`_I2C_PINS               (0u == `$INSTANCE_NAME`_REMOVE_I2C_PINS)
#define `$INSTANCE_NAME`_SPI_MASTER_PINS        (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_PINS)
#define `$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN    (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SCLK_PIN)
#define `$INSTANCE_NAME`_SPI_MASTER_MOSI_PIN    (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_MOSI_PIN)
#define `$INSTANCE_NAME`_SPI_MASTER_MISO_PIN    (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_MISO_PIN)
#define `$INSTANCE_NAME`_SPI_MASTER_SS0_PIN     (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS0_PIN)
#define `$INSTANCE_NAME`_SPI_MASTER_SS1_PIN     (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS1_PIN)
#define `$INSTANCE_NAME`_SPI_MASTER_SS2_PIN     (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS2_PIN)
#define `$INSTANCE_NAME`_SPI_MASTER_SS3_PIN     (0u == `$INSTANCE_NAME`_REMOVE_SPI_MASTER_SS3_PIN)
#define `$INSTANCE_NAME`_SPI_SLAVE_PINS         (0u == `$INSTANCE_NAME`_REMOVE_SPI_SLAVE_PINS)
#define `$INSTANCE_NAME`_SPI_SLAVE_MOSI_PIN     (0u == `$INSTANCE_NAME`_REMOVE_SPI_SLAVE_MOSI_PIN)
#define `$INSTANCE_NAME`_SPI_SLAVE_MISO_PIN     (0u == `$INSTANCE_NAME`_REMOVE_SPI_SLAVE_MISO_PIN)
#define `$INSTANCE_NAME`_UART_TX_PIN            (0u == `$INSTANCE_NAME`_REMOVE_UART_TX_PIN)
#define `$INSTANCE_NAME`_UART_RX_TX_PIN         (0u == `$INSTANCE_NAME`_REMOVE_UART_RX_TX_PIN)
#define `$INSTANCE_NAME`_UART_RX_PIN            (0u == `$INSTANCE_NAME`_REMOVE_UART_RX_PIN)
#define `$INSTANCE_NAME`_UART_RX_WAKE_PIN       (0u == `$INSTANCE_NAME`_REMOVE_UART_RX_WAKE_PIN)
#define `$INSTANCE_NAME`_UART_RTS_PIN           (0u == `$INSTANCE_NAME`_REMOVE_UART_RTS_PIN)
#define `$INSTANCE_NAME`_UART_CTS_PIN           (0u == `$INSTANCE_NAME`_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
    #include "`$INSTANCE_NAME`_`$PinName0UnconfigWake`.h"
#endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`) */

#if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
    #include "`$INSTANCE_NAME`_`$PinName0Unconfig`.h"
#endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`) */

#if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
    #include "`$INSTANCE_NAME`_`$PinName1Unconfig`.h"
#endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`) */

#if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
    #include "`$INSTANCE_NAME`_`$PinName2Unconfig`.h"
#endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`) */

#if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
    #include "`$INSTANCE_NAME`_`$PinName3Unconfig`.h"
#endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

#if (`$INSTANCE_NAME`_SS1_PIN)
    #include "`$INSTANCE_NAME`_spi_ss1.h"
#endif /* (`$INSTANCE_NAME`_SS1_PIN) */

#if (`$INSTANCE_NAME`_SS2_PIN)
    #include "`$INSTANCE_NAME`_spi_ss2.h"
#endif /* (`$INSTANCE_NAME`_SS2_PIN) */

#if (`$INSTANCE_NAME`_SS3_PIN)
    #include "`$INSTANCE_NAME`_spi_ss3.h"
#endif /* (`$INSTANCE_NAME`_SS3_PIN) */

#if (`$INSTANCE_NAME`_I2C_PINS)
    #include "`$INSTANCE_NAME`_scl.h"
    #include "`$INSTANCE_NAME`_sda.h"
#endif /* (`$INSTANCE_NAME`_I2C_PINS) */

#if (`$INSTANCE_NAME`_SPI_MASTER_PINS)
#if (`$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN)
    #include "`$INSTANCE_NAME`_sclk_m.h"
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_MOSI_PIN)
    #include "`$INSTANCE_NAME`_mosi_m.h"
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_MOSI_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_MISO_PIN)
    #include "`$INSTANCE_NAME`_miso_m.h"
#endif /*(`$INSTANCE_NAME`_SPI_MASTER_MISO_PIN) */
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_PINS) */

#if (`$INSTANCE_NAME`_SPI_SLAVE_PINS)
    #include "`$INSTANCE_NAME`_sclk_s.h"
    #include "`$INSTANCE_NAME`_ss_s.h"

#if (`$INSTANCE_NAME`_SPI_SLAVE_MOSI_PIN)
    #include "`$INSTANCE_NAME`_mosi_s.h"
#endif /* (`$INSTANCE_NAME`_SPI_SLAVE_MOSI_PIN) */

#if (`$INSTANCE_NAME`_SPI_SLAVE_MISO_PIN)
    #include "`$INSTANCE_NAME`_miso_s.h"
#endif /*(`$INSTANCE_NAME`_SPI_SLAVE_MISO_PIN) */
#endif /* (`$INSTANCE_NAME`_SPI_SLAVE_PINS) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN)
    #include "`$INSTANCE_NAME`_ss0_m.h"
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN)
    #include "`$INSTANCE_NAME`_ss1_m.h"
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN)
    #include "`$INSTANCE_NAME`_ss2_m.h"
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN)
    #include "`$INSTANCE_NAME`_ss3_m.h"
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN) */

#if (`$INSTANCE_NAME`_UART_TX_PIN)
    #include "`$INSTANCE_NAME`_tx.h"
#endif /* (`$INSTANCE_NAME`_UART_TX_PIN) */

#if (`$INSTANCE_NAME`_UART_RX_TX_PIN)
    #include "`$INSTANCE_NAME`_rx_tx.h"
#endif /* (`$INSTANCE_NAME`_UART_RX_TX_PIN) */

#if (`$INSTANCE_NAME`_UART_RX_PIN)
    #include "`$INSTANCE_NAME`_rx.h"
#endif /* (`$INSTANCE_NAME`_UART_RX_PIN) */

#if (`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
    #include "`$INSTANCE_NAME`_rx_wake.h"
#endif /* (`$INSTANCE_NAME`_UART_RX_WAKE_PIN) */

#if (`$INSTANCE_NAME`_UART_RTS_PIN)
    #include "`$INSTANCE_NAME`_rts.h"
#endif /* (`$INSTANCE_NAME`_UART_RTS_PIN) */

#if (`$INSTANCE_NAME`_UART_CTS_PIN)
    #include "`$INSTANCE_NAME`_cts.h"
#endif /* (`$INSTANCE_NAME`_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM)
    
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_MASK      (`$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_POS       (`$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_I2C   (`$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM_SPI)
    #define `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_SEL_UART  (`$INSTANCE_NAME`_`$PinName0Unconfig`__0__HSIOM_UART)
    
#elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM)
    
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_MASK      (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_POS       (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_I2C   (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM_SPI)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_SEL_UART  (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__HSIOM_UART)    
   
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_REG (*(reg32 *) `$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__INTCFG)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_PTR ( (reg32 *) `$INSTANCE_NAME`_`$PinName0UnconfigWake`__0__INTCFG)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_TYPE_POS  (`$INSTANCE_NAME`_`$PinName0UnconfigWake`__SHIFT)
    #define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_TYPE_MASK ((uint32) `$INSTANCE_NAME`_INTCFG_TYPE_MASK << \
                                                                           `$INSTANCE_NAME`_`$Pn0UnconfigWake`_INTCFG_TYPE_POS)
#else
    /* None of pins `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN or `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN present.*/
#endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */

#if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM)
    
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_MASK      (`$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_POS       (`$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_I2C   (`$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM_SPI)
    #define `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_SEL_UART  (`$INSTANCE_NAME`_`$PinName1Unconfig`__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */

#if (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM)
    
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_MASK      (`$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_POS       (`$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_I2C   (`$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM_SPI)
    #define `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_SEL_UART  (`$INSTANCE_NAME`_`$PinName2Unconfig`__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_`$Pn2Unconfig`_PIN) */

#if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM)
    
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK      (`$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS       (`$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_I2C   (`$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM_SPI)
#if !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
    #define `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_SEL_UART  (`$INSTANCE_NAME`_`$PinName3Unconfig`__0__HSIOM_UART)
#endif /* !(`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */
#endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

#if (`$INSTANCE_NAME`_SS1_PIN)
    #define `$INSTANCE_NAME`_SS1_HSIOM_REG  (*(reg32 *) `$INSTANCE_NAME`_spi_ss1__0__HSIOM)
    #define `$INSTANCE_NAME`_SS1_HSIOM_PTR  ( (reg32 *) `$INSTANCE_NAME`_spi_ss1__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS1_HSIOM_MASK     (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS1_HSIOM_POS      (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS1_HSIOM_SEL_GPIO (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS1_HSIOM_SEL_I2C  (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_SS1_HSIOM_SEL_SPI  (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SS1_PIN) */

#if (`$INSTANCE_NAME`_SS2_PIN)
    #define `$INSTANCE_NAME`_SS2_HSIOM_REG     (*(reg32 *) `$INSTANCE_NAME`_spi_ss2__0__HSIOM)
    #define `$INSTANCE_NAME`_SS2_HSIOM_PTR     ( (reg32 *) `$INSTANCE_NAME`_spi_ss2__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS2_HSIOM_MASK     (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS2_HSIOM_POS      (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS2_HSIOM_SEL_GPIO (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS2_HSIOM_SEL_I2C  (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_SS2_HSIOM_SEL_SPI  (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SS2_PIN) */

#if (`$INSTANCE_NAME`_SS3_PIN)
    #define `$INSTANCE_NAME`_SS3_HSIOM_REG     (*(reg32 *) `$INSTANCE_NAME`_spi_ss3__0__HSIOM)
    #define `$INSTANCE_NAME`_SS3_HSIOM_PTR     ( (reg32 *) `$INSTANCE_NAME`_spi_ss3__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS3_HSIOM_MASK     (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS3_HSIOM_POS      (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS3_HSIOM_SEL_GPIO (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS3_HSIOM_SEL_I2C  (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_I2C)
    #define `$INSTANCE_NAME`_SS3_HSIOM_SEL_SPI  (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SS3_PIN) */

#if (`$INSTANCE_NAME`_I2C_PINS)
    #define `$INSTANCE_NAME`_SCL_HSIOM_REG  (*(reg32 *) `$INSTANCE_NAME`_scl__0__HSIOM)
    #define `$INSTANCE_NAME`_SCL_HSIOM_PTR  ( (reg32 *) `$INSTANCE_NAME`_scl__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SCL_HSIOM_MASK     (`$INSTANCE_NAME`_scl__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SCL_HSIOM_POS      (`$INSTANCE_NAME`_scl__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SCL_HSIOM_SEL_GPIO (`$INSTANCE_NAME`_sda__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SCL_HSIOM_SEL_I2C  (`$INSTANCE_NAME`_sda__0__HSIOM_I2C)
    
    #define `$INSTANCE_NAME`_SDA_HSIOM_REG  (*(reg32 *) `$INSTANCE_NAME`_sda__0__HSIOM)
    #define `$INSTANCE_NAME`_SDA_HSIOM_PTR  ( (reg32 *) `$INSTANCE_NAME`_sda__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SDA_HSIOM_MASK     (`$INSTANCE_NAME`_sda__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SDA_HSIOM_POS      (`$INSTANCE_NAME`_sda__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SDA_HSIOM_SEL_GPIO (`$INSTANCE_NAME`_sda__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SDA_HSIOM_SEL_I2C  (`$INSTANCE_NAME`_sda__0__HSIOM_I2C)
#endif /* (`$INSTANCE_NAME`_I2C_PINS) */

#if (`$INSTANCE_NAME`_SPI_SLAVE_PINS)
    #define `$INSTANCE_NAME`_SCLK_S_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_sclk_s__0__HSIOM)
    #define `$INSTANCE_NAME`_SCLK_S_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_sclk_s__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SCLK_S_HSIOM_MASK      (`$INSTANCE_NAME`_sclk_s__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SCLK_S_HSIOM_POS       (`$INSTANCE_NAME`_sclk_s__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SCLK_S_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_sclk_s__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SCLK_S_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_sclk_s__0__HSIOM_SPI)
    
    #define `$INSTANCE_NAME`_SS0_S_HSIOM_REG    (*(reg32 *) `$INSTANCE_NAME`_ss0_s__0__HSIOM)
    #define `$INSTANCE_NAME`_SS0_S_HSIOM_PTR    ( (reg32 *) `$INSTANCE_NAME`_ss0_s__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS0_S_HSIOM_MASK       (`$INSTANCE_NAME`_ss0_s__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS0_S_HSIOM_POS        (`$INSTANCE_NAME`_ss0_s__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS0_S_HSIOM_SEL_GPIO   (`$INSTANCE_NAME`_ss0_s__0__HSIOM_GPIO)  
    #define `$INSTANCE_NAME`_SS0_S_HSIOM_SEL_SPI    (`$INSTANCE_NAME`_ss0_s__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_SLAVE_PINS) */

#if (`$INSTANCE_NAME`_SPI_SLAVE_MOSI_PIN)
    #define `$INSTANCE_NAME`_MOSI_S_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_mosi_s__0__HSIOM)
    #define `$INSTANCE_NAME`_MOSI_S_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_mosi_s__0__HSIOM)
    
    #define `$INSTANCE_NAME`_MOSI_S_HSIOM_MASK      (`$INSTANCE_NAME`_mosi_s__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MOSI_S_HSIOM_POS       (`$INSTANCE_NAME`_mosi_s__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_MOSI_S_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_mosi_s__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_MOSI_S_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_mosi_s__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_SLAVE_MOSI_PIN) */

#if (`$INSTANCE_NAME`_SPI_SLAVE_MISO_PIN)
    #define `$INSTANCE_NAME`_MISO_S_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_miso_s__0__HSIOM)
    #define `$INSTANCE_NAME`_MISO_S_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_miso_s__0__HSIOM)
    
    #define `$INSTANCE_NAME`_MISO_S_HSIOM_MASK      (`$INSTANCE_NAME`_miso_s__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MISO_S_HSIOM_POS       (`$INSTANCE_NAME`_miso_s__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_MISO_S_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_miso_s__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_MISO_S_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_miso_s__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_SLAVE_MISO_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_MISO_PIN)
    #define `$INSTANCE_NAME`_MISO_M_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_miso_m__0__HSIOM)
    #define `$INSTANCE_NAME`_MISO_M_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_miso_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_MISO_M_HSIOM_MASK      (`$INSTANCE_NAME`_miso_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MISO_M_HSIOM_POS       (`$INSTANCE_NAME`_miso_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_MISO_M_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_miso_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_MISO_M_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_miso_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_MISO_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_MOSI_PIN)
    #define `$INSTANCE_NAME`_MOSI_M_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_mosi_m__0__HSIOM)
    #define `$INSTANCE_NAME`_MOSI_M_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_mosi_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_MOSI_M_HSIOM_MASK      (`$INSTANCE_NAME`_mosi_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MOSI_M_HSIOM_POS       (`$INSTANCE_NAME`_mosi_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_MOSI_M_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_mosi_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_MOSI_M_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_mosi_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_MOSI_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN)
    #define `$INSTANCE_NAME`_SCLK_M_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_sclk_m__0__HSIOM)
    #define `$INSTANCE_NAME`_SCLK_M_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_sclk_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SCLK_M_HSIOM_MASK      (`$INSTANCE_NAME`_sclk_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SCLK_M_HSIOM_POS       (`$INSTANCE_NAME`_sclk_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SCLK_M_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_sclk_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SCLK_M_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_sclk_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SCLK_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN)
    #define `$INSTANCE_NAME`_SS0_M_HSIOM_REG    (*(reg32 *) `$INSTANCE_NAME`_ss0_m__0__HSIOM)
    #define `$INSTANCE_NAME`_SS0_M_HSIOM_PTR    ( (reg32 *) `$INSTANCE_NAME`_ss0_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS0_M_HSIOM_MASK       (`$INSTANCE_NAME`_ss0_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS0_M_HSIOM_POS        (`$INSTANCE_NAME`_ss0_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS0_M_HSIOM_SEL_GPIO   (`$INSTANCE_NAME`_ss0_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS0_M_HSIOM_SEL_SPI    (`$INSTANCE_NAME`_ss0_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS0_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN)
    #define `$INSTANCE_NAME`_SS1_M_HSIOM_REG    (*(reg32 *) `$INSTANCE_NAME`_ss1_m__0__HSIOM)
    #define `$INSTANCE_NAME`_SS1_M_HSIOM_PTR    ( (reg32 *) `$INSTANCE_NAME`_ss1_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS1_M_HSIOM_MASK       (`$INSTANCE_NAME`_ss1_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS1_M_HSIOM_POS        (`$INSTANCE_NAME`_ss1_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS1_M_HSIOM_SEL_GPIO   (`$INSTANCE_NAME`_ss1_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS1_M_HSIOM_SEL_SPI    (`$INSTANCE_NAME`_ss1_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS1_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN)
    #define `$INSTANCE_NAME`_SS2_M_HSIOM_REG    (*(reg32 *) `$INSTANCE_NAME`_ss2_m__0__HSIOM)
    #define `$INSTANCE_NAME`_SS2_M_HSIOM_PTR    ( (reg32 *) `$INSTANCE_NAME`_ss2_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS2_M_HSIOM_MASK       (`$INSTANCE_NAME`_ss2_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS2_M_HSIOM_POS        (`$INSTANCE_NAME`_ss2_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS2_M_HSIOM_SEL_GPIO   (`$INSTANCE_NAME`_ss2_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS2_M_HSIOM_SEL_SPI    (`$INSTANCE_NAME`_ss2_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS2_PIN) */

#if (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN)
    #define `$INSTANCE_NAME`_SS3_M_HSIOM_REG    (*(reg32 *) `$INSTANCE_NAME`_ss3_m__0__HSIOM)
    #define `$INSTANCE_NAME`_SS3_M_HSIOM_PTR    ( (reg32 *) `$INSTANCE_NAME`_ss3_m__0__HSIOM)
    
    #define `$INSTANCE_NAME`_SS3_M_HSIOM_MASK      (`$INSTANCE_NAME`_ss3_m__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS3_M_HSIOM_POS       (`$INSTANCE_NAME`_ss3_m__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_SS3_M_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_ss3_m__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_SS3_M_HSIOM_SEL_SPI   (`$INSTANCE_NAME`_ss3_m__0__HSIOM_SPI)
#endif /* (`$INSTANCE_NAME`_SPI_MASTER_SS3_PIN) */

#if (`$INSTANCE_NAME`_UART_RX_PIN)
    #define `$INSTANCE_NAME`_RX_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_rx__0__HSIOM)
    #define `$INSTANCE_NAME`_RX_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_rx__0__HSIOM)
    
    #define `$INSTANCE_NAME`_RX_HSIOM_MASK      (`$INSTANCE_NAME`_rx__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_RX_HSIOM_POS       (`$INSTANCE_NAME`_rx__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_RX_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_rx__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_RX_HSIOM_SEL_UART  (`$INSTANCE_NAME`_rx__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_UART_RX_PIN) */

#if (`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
    #define `$INSTANCE_NAME`_RX_WAKE_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_rx_wake__0__HSIOM)
    #define `$INSTANCE_NAME`_RX_WAKE_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_rx_wake__0__HSIOM)
    
    #define `$INSTANCE_NAME`_RX_WAKE_HSIOM_MASK      (`$INSTANCE_NAME`_rx_wake__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_RX_WAKE_HSIOM_POS       (`$INSTANCE_NAME`_rx_wake__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_RX_WAKE_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_rx_wake__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_RX_WAKE_HSIOM_SEL_UART  (`$INSTANCE_NAME`_rx_wake__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_UART_WAKE_RX_PIN) */

#if (`$INSTANCE_NAME`_UART_CTS_PIN)
    #define `$INSTANCE_NAME`_CTS_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_cts__0__HSIOM)
    #define `$INSTANCE_NAME`_CTS_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_cts__0__HSIOM)
    
    #define `$INSTANCE_NAME`_CTS_HSIOM_MASK      (`$INSTANCE_NAME`_cts__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CTS_HSIOM_POS       (`$INSTANCE_NAME`_cts__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CTS_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_cts__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_CTS_HSIOM_SEL_UART  (`$INSTANCE_NAME`_cts__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_UART_CTS_PIN) */

#if (`$INSTANCE_NAME`_UART_TX_PIN)
    #define `$INSTANCE_NAME`_TX_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_tx__0__HSIOM)
    #define `$INSTANCE_NAME`_TX_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_tx__0__HSIOM)
    
    #define `$INSTANCE_NAME`_TX_HSIOM_MASK      (`$INSTANCE_NAME`_tx__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_TX_HSIOM_POS       (`$INSTANCE_NAME`_tx__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_TX_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_tx__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_TX_HSIOM_SEL_UART  (`$INSTANCE_NAME`_tx__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_UART_TX_PIN) */

#if (`$INSTANCE_NAME`_UART_RX_TX_PIN)
    #define `$INSTANCE_NAME`_RX_TX_HSIOM_REG   (*(reg32 *) `$INSTANCE_NAME`_rx_tx__0__HSIOM)
    #define `$INSTANCE_NAME`_RX_TX_HSIOM_PTR   ( (reg32 *) `$INSTANCE_NAME`_rx_tx__0__HSIOM)
    
    #define `$INSTANCE_NAME`_RX_TX_HSIOM_MASK      (`$INSTANCE_NAME`_rx_tx__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_RX_TX_HSIOM_POS       (`$INSTANCE_NAME`_rx_tx__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_RX_TX_HSIOM_SEL_GPIO  (`$INSTANCE_NAME`_rx_tx__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_RX_TX_HSIOM_SEL_UART  (`$INSTANCE_NAME`_rx_tx__0__HSIOM_UART)
#endif /* (`$INSTANCE_NAME`_UART_RX_TX_PIN) */

#if (`$INSTANCE_NAME`_UART_RTS_PIN)
    #define `$INSTANCE_NAME`_RTS_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_rts__0__HSIOM)
    #define `$INSTANCE_NAME`_RTS_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_rts__0__HSIOM)
    
    #define `$INSTANCE_NAME`_RTS_HSIOM_MASK     (`$INSTANCE_NAME`_rts__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_RTS_HSIOM_POS      (`$INSTANCE_NAME`_rts__0__HSIOM_SHIFT)    
    #define `$INSTANCE_NAME`_RTS_HSIOM_SEL_GPIO (`$INSTANCE_NAME`_rts__0__HSIOM_GPIO)
    #define `$INSTANCE_NAME`_RTS_HSIOM_SEL_UART (`$INSTANCE_NAME`_rts__0__HSIOM_UART)    
#endif /* (`$INSTANCE_NAME`_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define `$INSTANCE_NAME`_HSIOM_DEF_SEL      (0x00u)
#define `$INSTANCE_NAME`_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for `$INSTANCE_NAME`_CY_SCBIP_V0 
* and `$INSTANCE_NAME`_CY_SCBIP_V1. It is not recommended to use them for 
* `$INSTANCE_NAME`_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define `$INSTANCE_NAME`_HSIOM_UART_SEL     (0x09u)
#define `$INSTANCE_NAME`_HSIOM_I2C_SEL      (0x0Eu)
#define `$INSTANCE_NAME`_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX   (0u)
#define `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX       (0u)
#define `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX       (1u)
#define `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX       (2u)
#define `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX       (3u)
#define `$INSTANCE_NAME`_SS1_PIN_INDEX                  (4u)
#define `$INSTANCE_NAME`_SS2_PIN_INDEX                  (5u)
#define `$INSTANCE_NAME`_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_MASK ((uint32) 0x01u << `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX)
#define `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_MASK     ((uint32) 0x01u << `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX)
#define `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_MASK     ((uint32) 0x01u << `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX)
#define `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_MASK     ((uint32) 0x01u << `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX)
#define `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_MASK     ((uint32) 0x01u << `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX)
#define `$INSTANCE_NAME`_SS1_PIN_MASK                ((uint32) 0x01u << `$INSTANCE_NAME`_SS1_PIN_INDEX)
#define `$INSTANCE_NAME`_SS2_PIN_MASK                ((uint32) 0x01u << `$INSTANCE_NAME`_SS2_PIN_INDEX)
#define `$INSTANCE_NAME`_SS3_PIN_MASK                ((uint32) 0x01u << `$INSTANCE_NAME`_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define `$INSTANCE_NAME`_INTCFG_TYPE_MASK           (0x03u)
#define `$INSTANCE_NAME`_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define `$INSTANCE_NAME`_PIN_DM_ALG_HIZ  (0u)
#define `$INSTANCE_NAME`_PIN_DM_DIG_HIZ  (1u)
#define `$INSTANCE_NAME`_PIN_DM_OD_LO    (4u)
#define `$INSTANCE_NAME`_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define `$INSTANCE_NAME`_DM_MASK    (0x7u)
#define `$INSTANCE_NAME`_DM_SIZE    (3u)
#define `$INSTANCE_NAME`_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) `$INSTANCE_NAME`_DM_MASK << (`$INSTANCE_NAME`_DM_SIZE * (pos)))) >> \
                                                              (`$INSTANCE_NAME`_DM_SIZE * (pos)) )

#if (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
    #define `$INSTANCE_NAME`_CHECK_`$Pn1Unconfig`_PIN_USED \
                (`$INSTANCE_NAME`_PIN_DM_ALG_HIZ != \
                    `$INSTANCE_NAME`_GET_P4_PIN_DM(`$INSTANCE_NAME`_`$PinName1Unconfig`_PC, \
                                                   `$INSTANCE_NAME`_`$PinName1Unconfig`_SHIFT))
#endif /* (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN) */

#if (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN)
    #define `$INSTANCE_NAME`_CHECK_`$Pn3Unconfig`_PIN_USED \
                (`$INSTANCE_NAME`_PIN_DM_ALG_HIZ != \
                    `$INSTANCE_NAME`_GET_P4_PIN_DM(`$INSTANCE_NAME`_`$PinName3Unconfig`_PC, \
                                                   `$INSTANCE_NAME`_`$PinName3Unconfig`_SHIFT))
#endif /* (`$INSTANCE_NAME`_`$Pn3Unconfig`_PIN) */

/* Set bits-mask in register */
#define `$INSTANCE_NAME`_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define `$INSTANCE_NAME`_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define `$INSTANCE_NAME`_SET_HSIOM_SEL(reg, mask, pos, sel) `$INSTANCE_NAME`_SET_REGISTER_BITS(reg, mask, pos, sel)
#define `$INSTANCE_NAME`_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        `$INSTANCE_NAME`_SET_REGISTER_BITS(reg, mask, pos, intType)
#define `$INSTANCE_NAME`_SET_INP_DIS(reg, mask, val) `$INSTANCE_NAME`_SET_REGISTER_BIT(reg, mask, val)

/* `$INSTANCE_NAME`_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (`$INSTANCE_NAME`_CY_SCBIP_V0)
#if (`$INSTANCE_NAME`_I2C_PINS)
    #define `$INSTANCE_NAME`_SET_I2C_SCL_DR(val) `$INSTANCE_NAME`_scl_Write(val)

    #define `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(sel) \
                          `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SCL_HSIOM_REG,  \
                                                         `$INSTANCE_NAME`_SCL_HSIOM_MASK, \
                                                         `$INSTANCE_NAME`_SCL_HSIOM_POS,  \
                                                         (sel))
    #define `$INSTANCE_NAME`_WAIT_SCL_SET_HIGH  (0u == `$INSTANCE_NAME`_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
    #define `$INSTANCE_NAME`_SET_I2C_SCL_DR(val) \
                            `$INSTANCE_NAME`_`$PinName0UnconfigWake`_Write(val)

    #define `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(sel) \
                    `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG,  \
                                                   `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_MASK, \
                                                   `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_POS,  \
                                                   (sel))

    #define `$INSTANCE_NAME`_WAIT_SCL_SET_HIGH  (0u == `$INSTANCE_NAME`_`$PinName0UnconfigWake`_Read())

#elif (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
    #define `$INSTANCE_NAME`_SET_I2C_SCL_DR(val) \
                            `$INSTANCE_NAME`_`$PinName0Unconfig`_Write(val)


    #define `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(sel) \
                            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_REG,  \
                                                           `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_MASK, \
                                                           `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_POS,  \
                                                           (sel))

    #define `$INSTANCE_NAME`_WAIT_SCL_SET_HIGH  (0u == `$INSTANCE_NAME`_`$PinName0Unconfig`_Read())

#else
    #define `$INSTANCE_NAME`_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define `$INSTANCE_NAME`_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define `$INSTANCE_NAME`_WAIT_SCL_SET_HIGH  (0u)
#endif /* (`$INSTANCE_NAME`_I2C_PINS) */

/* SCB I2C: sda signal */
#if (`$INSTANCE_NAME`_I2C_PINS)
    #define `$INSTANCE_NAME`_WAIT_SDA_SET_HIGH  (0u == `$INSTANCE_NAME`_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (`$INSTANCE_NAME`_`$Pn1Unconfig`_PIN)
    #define `$INSTANCE_NAME`_WAIT_SDA_SET_HIGH  (0u == `$INSTANCE_NAME`_`$PinName1Unconfig`_Read())
#else
    #define `$INSTANCE_NAME`_WAIT_SDA_SET_HIGH  (0u)
#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */
#endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN)
    #define `$INSTANCE_NAME`_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN)
    #define `$INSTANCE_NAME`_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) `$INSTANCE_NAME`_`$PinName0UnconfigWake`_ClearInterrupt(); \
            }while(0)

#elif(`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
    #define `$INSTANCE_NAME`_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) `$INSTANCE_NAME`_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (`$INSTANCE_NAME`_`$Pn0Unconfig`_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define `$INSTANCE_NAME`_REMOVE_MOSI_SCL_RX_WAKE_PIN    `$INSTANCE_NAME`_REMOVE_`$Pn0UnconfigWake`_PIN
#define `$INSTANCE_NAME`_REMOVE_MOSI_SCL_RX_PIN         `$INSTANCE_NAME`_REMOVE_`$Pn0Unconfig`_PIN
#define `$INSTANCE_NAME`_REMOVE_MISO_SDA_TX_PIN         `$INSTANCE_NAME`_REMOVE_`$Pn1Unconfig`_PIN
#ifndef `$INSTANCE_NAME`_REMOVE_SCLK_PIN
#define `$INSTANCE_NAME`_REMOVE_SCLK_PIN                `$INSTANCE_NAME`_REMOVE_`$Pn2Unconfig`_PIN
#endif /* `$INSTANCE_NAME`_REMOVE_SCLK_PIN */
#ifndef `$INSTANCE_NAME`_REMOVE_SS0_PIN
#define `$INSTANCE_NAME`_REMOVE_SS0_PIN                 `$INSTANCE_NAME`_REMOVE_`$Pn3Unconfig`_PIN
#endif /* `$INSTANCE_NAME`_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN   `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN
#define `$INSTANCE_NAME`_MOSI_SCL_RX_PIN        `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN
#define `$INSTANCE_NAME`_MISO_SDA_TX_PIN        `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN
#ifndef `$INSTANCE_NAME`_SCLK_PIN
#define `$INSTANCE_NAME`_SCLK_PIN               `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN
#endif /* `$INSTANCE_NAME`_SCLK_PIN */
#ifndef `$INSTANCE_NAME`_SS0_PIN
#define `$INSTANCE_NAME`_SS0_PIN                `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN
#endif /* `$INSTANCE_NAME`_SS0_PIN */

#if (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM_REG     `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM_PTR     `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM_MASK    `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM_POS     `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG

    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_REG    `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_PTR    `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG

    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  `$INSTANCE_NAME`_`$Pn0UnconfigWake`_HSIOM_REG
#endif /* (`$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN) */

#if (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_REG      `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_REG
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_PTR      `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_PTR
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_MASK     `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_MASK
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_POS      `$INSTANCE_NAME`_`$Pn0Unconfig`_HSIOM_POS
#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

#if (`$INSTANCE_NAME`_MISO_SDA_TX_PIN)
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_REG      `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_PTR      `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_MASK     `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_POS      `$INSTANCE_NAME`_`$Pn1Unconfig`_HSIOM_REG
#endif /* (`$INSTANCE_NAME`_MISO_SDA_TX_PIN_PIN) */

#if (`$INSTANCE_NAME`_SCLK_PIN)
    #ifndef `$INSTANCE_NAME`_SCLK_HSIOM_REG
    #define `$INSTANCE_NAME`_SCLK_HSIOM_REG     `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_REG
    #define `$INSTANCE_NAME`_SCLK_HSIOM_PTR     `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_PTR
    #define `$INSTANCE_NAME`_SCLK_HSIOM_MASK    `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_MASK
    #define `$INSTANCE_NAME`_SCLK_HSIOM_POS     `$INSTANCE_NAME`_`$Pn2Unconfig`_HSIOM_POS
    #endif /* `$INSTANCE_NAME`_SCLK_HSIOM_REG */
#endif /* (`$INSTANCE_NAME`_SCLK_PIN) */

#if (`$INSTANCE_NAME`_SS0_PIN)
    #ifndef `$INSTANCE_NAME`_SS0_HSIOM_REG
    #define `$INSTANCE_NAME`_SS0_HSIOM_REG      `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_REG
    #define `$INSTANCE_NAME`_SS0_HSIOM_PTR      `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_PTR
    #define `$INSTANCE_NAME`_SS0_HSIOM_MASK     `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_MASK
    #define `$INSTANCE_NAME`_SS0_HSIOM_POS      `$INSTANCE_NAME`_`$Pn3Unconfig`_HSIOM_POS
    #endif /* `$INSTANCE_NAME`_SS0_HSIOM_REG */
#endif /* (`$INSTANCE_NAME`_SS0_PIN) */

#define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN_INDEX `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_INDEX
#define `$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX      `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_INDEX
#define `$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX      `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_INDEX
#ifndef `$INSTANCE_NAME`_SCLK_PIN_INDEX
#define `$INSTANCE_NAME`_SCLK_PIN_INDEX             `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_INDEX
#endif /* `$INSTANCE_NAME`_SCLK_PIN_INDEX */
#ifndef `$INSTANCE_NAME`_SS0_PIN_INDEX
#define `$INSTANCE_NAME`_SS0_PIN_INDEX              `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_INDEX
#endif /* `$INSTANCE_NAME`_SS0_PIN_INDEX */

#define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN_MASK `$INSTANCE_NAME`_`$Pn0UnconfigWake`_PIN_MASK
#define `$INSTANCE_NAME`_MOSI_SCL_RX_PIN_MASK      `$INSTANCE_NAME`_`$Pn0Unconfig`_PIN_MASK
#define `$INSTANCE_NAME`_MISO_SDA_TX_PIN_MASK      `$INSTANCE_NAME`_`$Pn1Unconfig`_PIN_MASK
#ifndef `$INSTANCE_NAME`_SCLK_PIN_MASK
#define `$INSTANCE_NAME`_SCLK_PIN_MASK             `$INSTANCE_NAME`_`$Pn2Unconfig`_PIN_MASK
#endif /* `$INSTANCE_NAME`_SCLK_PIN_MASK */
#ifndef `$INSTANCE_NAME`_SS0_PIN_MASK
#define `$INSTANCE_NAME`_SS0_PIN_MASK              `$INSTANCE_NAME`_`$Pn3Unconfig`_PIN_MASK
#endif /* `$INSTANCE_NAME`_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
