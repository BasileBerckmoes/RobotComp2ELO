/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides constants and parameter values for the I2C component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_SCB_I2C_PDL_H)
#define `$INSTANCE_NAME`_CY_SCB_I2C_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_i2c.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_MODE               (0x`$Mode`U)
#define `$INSTANCE_NAME`_MODE_SLAVE_MASK    (0x1U)
#define `$INSTANCE_NAME`_MODE_MASTER_MASK   (0x2U)

#define `$INSTANCE_NAME`_ENABLE_SLAVE       (0UL != (`$INSTANCE_NAME`_MODE & `$INSTANCE_NAME`_MODE_SLAVE_MASK))
#define `$INSTANCE_NAME`_ENABLE_MASTER      (0UL != (`$INSTANCE_NAME`_MODE & `$INSTANCE_NAME`_MODE_MASTER_MASK))
#define `$INSTANCE_NAME`_MANUAL_SCL_CONTROL (`$EnableManualSclControl`U)


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component only APIs. */
void `$INSTANCE_NAME`_Start(void);

/* Basic functions. */
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_i2c_config_t const *config);
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit (void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable (void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);

/* Data rate configuration functions. */
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SetDataRate(uint32_t dataRateHz, uint32_t scbClockHz);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetDataRate(uint32_t scbClockHz);

/* Register callbacks. */
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterEventCallback(cy_cb_scb_i2c_handle_events_t callback);
#if (`$INSTANCE_NAME`_ENABLE_SLAVE)
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterAddrCallback (cy_cb_scb_i2c_handle_addr_t callback);
#endif /* (`$INSTANCE_NAME`_ENABLE_SLAVE) */

/* Configuration functions. */
#if (`$INSTANCE_NAME`_ENABLE_SLAVE)
__STATIC_INLINE void     `$INSTANCE_NAME`_SlaveSetAddress(uint8_t addr);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetAddress(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SlaveSetAddressMask(uint8_t addrMask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetAddressMask(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_SLAVE) */

#if (`$INSTANCE_NAME`_ENABLE_MASTER)
__STATIC_INLINE void `$INSTANCE_NAME`_MasterSetLowPhaseDutyCycle (uint32_t clockCycles);
__STATIC_INLINE void `$INSTANCE_NAME`_MasterSetHighPhaseDutyCycle(uint32_t clockCycles);
#endif /* (`$INSTANCE_NAME`_ENABLE_MASTER) */

/* Bus status. */
__STATIC_INLINE bool     `$INSTANCE_NAME`_IsBusBusy(void);

/* Slave functions. */
#if (`$INSTANCE_NAME`_ENABLE_SLAVE)
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetStatus(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_SlaveConfigReadBuf(uint8_t *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_SlaveAbortRead(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetReadTransferCount(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveClearReadStatus(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_SlaveConfigWriteBuf(uint8_t *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_SlaveAbortWrite(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetWriteTransferCount(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveClearWriteStatus(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_SLAVE) */

/* Master interrupt processing functions. */
#if (`$INSTANCE_NAME`_ENABLE_MASTER)
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_MasterGetStatus(void);

__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterRead(cy_stc_scb_i2c_master_xfer_config_t *xferConfig);
__STATIC_INLINE void `$INSTANCE_NAME`_MasterAbortRead(void);
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterWrite(cy_stc_scb_i2c_master_xfer_config_t *xferConfig);
__STATIC_INLINE void `$INSTANCE_NAME`_MasterAbortWrite(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_MasterGetTransferCount(void);

/* Master manual processing functions. */
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterSendStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterSendReStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterSendStop(uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterReadByte(cy_en_scb_i2c_command_t ackNack, uint8_t *byte, uint32_t timeoutMs);
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterWriteByte(uint8_t byte, uint32_t timeoutMs);
#endif /* (`$INSTANCE_NAME`_ENABLE_MASTER) */

/* Interrupt handler. */
__STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void);
/** @} group_general */


/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t `$INSTANCE_NAME`_initVar;
extern cy_stc_scb_i2c_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
extern cy_stc_scb_i2c_context_t `$INSTANCE_NAME`_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the SCB instance */
#define `$INSTANCE_NAME`_HW     ((CySCB_Type *) `$INSTANCE_NAME`_SCB__HW)

/** The desired data rate in Hz */
#define `$INSTANCE_NAME`_DATA_RATE_HZ      (`$DataRateHz`U)

/** The frequency of the clock used by the Component in Hz */
#define `$INSTANCE_NAME`_CLK_FREQ_HZ       (`$ScbClockHz`U)

/** The number of Component clocks used by the master to generate the SCL
* low phase. This number is calculated by GUI based on the selected data rate.
*/
#define `$INSTANCE_NAME`_LOW_PHASE_DUTY_CYCLE   (`$LowPhaseDutyCycle`U)

/** The number of Component clocks used by the master to generate the SCL
* high phase. This number is calculated by GUI based on the selected data rate.
*/
#define `$INSTANCE_NAME`_HIGH_PHASE_DUTY_CYCLE  (`$HighPhaseDutyCycle`U)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_i2c_config_t const *config)
{
    return Cy_SCB_I2C_Init(`$INSTANCE_NAME`_HW, config, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)
{
    Cy_SCB_I2C_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_SCB_I2C_Enable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_SCB_I2C_Disable(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDataRate
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SetDataRate() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SetDataRate(uint32_t dataRateHz, uint32_t scbClockHz)
{
    return Cy_SCB_I2C_SetDataRate(`$INSTANCE_NAME`_HW, dataRateHz, scbClockHz);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDataRate
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_GetDataRate() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetDataRate(uint32_t scbClockHz)
{
    return Cy_SCB_I2C_GetDataRate(`$INSTANCE_NAME`_HW, scbClockHz);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RegisterEventCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_RegisterEventCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterEventCallback(cy_cb_scb_i2c_handle_events_t callback)
{
    Cy_SCB_I2C_RegisterEventCallback(`$INSTANCE_NAME`_HW, callback, &`$INSTANCE_NAME`_context);
}


#if (`$INSTANCE_NAME`_ENABLE_SLAVE)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RegisterAddrCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_RegisterAddrCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterAddrCallback(cy_cb_scb_i2c_handle_addr_t callback)
{
    Cy_SCB_I2C_RegisterAddrCallback(`$INSTANCE_NAME`_HW, callback, &`$INSTANCE_NAME`_context);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_SLAVE) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusBusy
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_IsBusBusy() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_IsBusBusy(void)
{
    return Cy_SCB_I2C_IsBusBusy(`$INSTANCE_NAME`_HW);
}


#if (`$INSTANCE_NAME`_ENABLE_SLAVE)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveSetAddress
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetAddress() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SlaveSetAddress(uint8_t addr)
{
    Cy_SCB_I2C_SlaveSetAddress(`$INSTANCE_NAME`_HW, addr);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveGetAddress
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetAddress() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetAddress(void)
{
    return Cy_SCB_I2C_SlaveGetAddress(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveSetAddressMask
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveSetAddressMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SlaveSetAddressMask(uint8_t addrMask)
{
    Cy_SCB_I2C_SlaveSetAddressMask(`$INSTANCE_NAME`_HW, addrMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveGetAddressMask
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetAddressMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetAddressMask(void)
{
    return Cy_SCB_I2C_SlaveGetAddressMask(`$INSTANCE_NAME`_HW);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_SLAVE) */

#if (`$INSTANCE_NAME`_ENABLE_MASTER)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterSetLowPhaseDutyCycle
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSetLowPhaseDutyCycle() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_MasterSetLowPhaseDutyCycle(uint32_t clockCycles)
{
    Cy_SCB_I2C_MasterSetLowPhaseDutyCycle(`$INSTANCE_NAME`_HW, clockCycles);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterSetHighPhaseDutyCycle
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSetHighPhaseDutyCycle() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_MasterSetHighPhaseDutyCycle(uint32_t clockCycles)
{
    Cy_SCB_I2C_MasterSetHighPhaseDutyCycle(`$INSTANCE_NAME`_HW, clockCycles);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_MASTER) */


#if (`$INSTANCE_NAME`_ENABLE_SLAVE)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveGetStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetStatus(void)
{
    return Cy_SCB_I2C_SlaveGetStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveConfigReadBuf
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveConfigReadBuf() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SlaveConfigReadBuf(uint8_t *buffer, uint32_t size)
{
    Cy_SCB_I2C_SlaveConfigReadBuf(`$INSTANCE_NAME`_HW, buffer, size, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveAbortRead
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveAbortRead() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SlaveAbortRead(void)
{
    Cy_SCB_I2C_SlaveAbortRead(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveGetReadTransferCount
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetReadTransferCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetReadTransferCount(void)
{
    return Cy_SCB_I2C_SlaveGetReadTransferCount(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveClearReadStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveClearReadStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveClearReadStatus(void)
{
    return Cy_SCB_I2C_SlaveClearReadStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveConfigWriteBuf
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveConfigWriteBuf() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SlaveConfigWriteBuf(uint8_t *buffer, uint32_t size)
{
    Cy_SCB_I2C_SlaveConfigWriteBuf(`$INSTANCE_NAME`_HW, buffer, size, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveAbortWrite
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveAbortWrite() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SlaveAbortWrite(void)
{
    Cy_SCB_I2C_SlaveAbortWrite(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveGetWriteTransferCount
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveGetWriteTransferCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveGetWriteTransferCount(void)
{
    return Cy_SCB_I2C_SlaveGetWriteTransferCount(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SlaveClearWriteStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_SlaveClearWriteStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_SlaveClearWriteStatus(void)
{
    return Cy_SCB_I2C_SlaveClearWriteStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_SLAVE) */


#if (`$INSTANCE_NAME`_ENABLE_MASTER)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterGetStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterGetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_MasterGetStatus(void)
{
    return Cy_SCB_I2C_MasterGetStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterRead
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterRead() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterRead(cy_stc_scb_i2c_master_xfer_config_t *xferConfig)
{
    return Cy_SCB_I2C_MasterRead(`$INSTANCE_NAME`_HW, xferConfig, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterAbortRead
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterAbortRead() PDL driver function.
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_MasterAbortRead(void)
{
    Cy_SCB_I2C_MasterAbortRead(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterWrite
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterWrite() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterWrite(cy_stc_scb_i2c_master_xfer_config_t *xferConfig)
{
    return Cy_SCB_I2C_MasterWrite(`$INSTANCE_NAME`_HW, xferConfig, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterAbortWrite
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterAbortWrite() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_MasterAbortWrite(void)
{
    Cy_SCB_I2C_MasterAbortWrite(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterGetTransferCount
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterGetTransferCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_MasterGetTransferCount(void)
{
    return Cy_SCB_I2C_MasterGetTransferCount(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterSendStart
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSendStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterSendStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterSendStart(`$INSTANCE_NAME`_HW, address, bitRnW, timeoutMs, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterSendReStart
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSendReStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterSendReStart(uint32_t address, cy_en_scb_i2c_direction_t bitRnW, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterSendReStart(`$INSTANCE_NAME`_HW, address, bitRnW, timeoutMs, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterSendStop
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterSendStop() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterSendStop(uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterSendStop(`$INSTANCE_NAME`_HW, timeoutMs, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterReadByte
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterReadByte() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterReadByte(cy_en_scb_i2c_command_t ackNack, uint8_t *byte, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterReadByte(`$INSTANCE_NAME`_HW, ackNack, byte, timeoutMs, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MasterWriteByte
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_MasterWriteByte() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_i2c_status_t `$INSTANCE_NAME`_MasterWriteByte(uint8_t byte, uint32_t timeoutMs)
{
    return Cy_SCB_I2C_MasterWriteByte(`$INSTANCE_NAME`_HW, byte, timeoutMs, &`$INSTANCE_NAME`_context);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_MASTER) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_I2C_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void)
{
    Cy_SCB_I2C_Interrupt(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* `$INSTANCE_NAME`_CY_SCB_I2C_PDL_H */


/* [] END OF FILE */
