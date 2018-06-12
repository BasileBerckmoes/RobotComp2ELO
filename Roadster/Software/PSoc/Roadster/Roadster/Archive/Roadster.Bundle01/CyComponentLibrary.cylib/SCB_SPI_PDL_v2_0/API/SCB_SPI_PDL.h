/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides constants and parameter values for the SPI component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_SCB_SPI_PDL_H)
#define `$INSTANCE_NAME`_CY_SCB_SPI_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_spi.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component specific functions. */
void `$INSTANCE_NAME`_Start(void);

/* Basic functions. */
__STATIC_INLINE cy_en_scb_spi_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_spi_config_t const *config);
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);

/* Register callback. */
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterCallback(cy_cb_scb_spi_handle_events_t callback);

/* Bus state. */
__STATIC_INLINE bool `$INSTANCE_NAME`_IsBusBusy(void);

/* Slave select control. */
__STATIC_INLINE void `$INSTANCE_NAME`_SetActiveSlaveSelect(cy_en_scb_spi_slave_select_t slaveSelect);
__STATIC_INLINE void `$INSTANCE_NAME`_SetActiveSlaveSelectPolarity(cy_en_scb_spi_slave_select_t slaveSelect, 
                                                                   cy_en_scb_spi_polarity_t polarity);

/* Low level: read. */
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Read(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadArray(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetRxFifoStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearRxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInRxFifo(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearRxFifo(void);

/* Low level: write. */
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Write(uint32_t data);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_WriteArray(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_WriteArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTxFifoStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearTxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInTxFifo(void);
__STATIC_INLINE bool     `$INSTANCE_NAME`_IsTxComplete(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearTxFifo(void);

/* Master/slave specific status. */
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetSlaveMasterStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearSlaveMasterStatus(uint32_t clearMask);

/* High level: transfer functions. */
__STATIC_INLINE cy_en_scb_spi_status_t `$INSTANCE_NAME`_Transfer(void *txBuffer, void *rxBuffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_AbortTransfer(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTransferStatus(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumTransfered(void);

/* Interrupt handler */
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
extern cy_stc_scb_spi_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
extern cy_stc_scb_spi_context_t `$INSTANCE_NAME`_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the hardware */
#define `$INSTANCE_NAME`_HW     ((CySCB_Type *) `$INSTANCE_NAME`_SCB__HW)

/** The slave select line 0 constant which takes into account pin placement */
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT0    ( (cy_en_scb_spi_slave_select_t) `$INSTANCE_NAME`_SCB__SS0_POSITION)

/** The slave select line 1 constant which takes into account pin placement */
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT1    ( (cy_en_scb_spi_slave_select_t) `$INSTANCE_NAME`_SCB__SS1_POSITION)

/** The slave select line 2 constant which takes into account pin placement */
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT2    ( (cy_en_scb_spi_slave_select_t) `$INSTANCE_NAME`_SCB__SS2_POSITION)

/** The slave select line 3 constant which takes into account pin placement */
#define `$INSTANCE_NAME`_SPI_SLAVE_SELECT3    ((cy_en_scb_spi_slave_select_t) `$INSTANCE_NAME`_SCB__SS3_POSITION)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_spi_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_spi_config_t const *config)
{
    return Cy_SCB_SPI_Init(`$INSTANCE_NAME`_HW, config, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)
{
    Cy_SCB_SPI_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_SCB_SPI_Enable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_SCB_SPI_Disable(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RegisterCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_RegisterCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterCallback(cy_cb_scb_spi_handle_events_t callback)
{
    Cy_SCB_SPI_RegisterCallback(`$INSTANCE_NAME`_HW, callback, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusBusy
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_IsBusBusy() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_IsBusBusy(void)
{
    return Cy_SCB_SPI_IsBusBusy(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetActiveSlaveSelect
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_SetActiveSlaveSelect() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetActiveSlaveSelect(cy_en_scb_spi_slave_select_t slaveSelect)
{
    Cy_SCB_SPI_SetActiveSlaveSelect(`$INSTANCE_NAME`_HW, slaveSelect);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetActiveSlaveSelectPolarity
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_SetActiveSlaveSelectPolarity() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetActiveSlaveSelectPolarity(cy_en_scb_spi_slave_select_t slaveSelect, 
                                                                   cy_en_scb_spi_polarity_t polarity)
{
    Cy_SCB_SPI_SetActiveSlaveSelectPolarity(`$INSTANCE_NAME`_HW, slaveSelect, polarity);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Read() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Read(void)
{
    return Cy_SCB_SPI_Read(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadArray
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_ReadArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadArray(void *buffer, uint32_t size)
{
    return Cy_SCB_SPI_ReadArray(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_GetRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetRxFifoStatus(void)
{
    return Cy_SCB_SPI_GetRxFifoStatus(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_ClearRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearRxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_SPI_ClearRxFifoStatus(`$INSTANCE_NAME`_HW, clearMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumInRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_GetNumInRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInRxFifo(void)
{
    return Cy_SCB_GetNumInRxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_ClearRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearRxFifo(void)
{
    Cy_SCB_SPI_ClearRxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Write
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Write() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Write(uint32_t data)
{
    return Cy_SCB_SPI_Write(`$INSTANCE_NAME`_HW, data);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteArray
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_WriteArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_WriteArray(void *buffer, uint32_t size)
{
    return Cy_SCB_SPI_WriteArray(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_WriteArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_WriteArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_SPI_WriteArrayBlocking(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_GetTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTxFifoStatus(void)
{
    return Cy_SCB_SPI_GetTxFifoStatus(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_ClearTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearTxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_SPI_ClearTxFifoStatus(`$INSTANCE_NAME`_HW, clearMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumInTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_GetNumInTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInTxFifo(void)
{
    return Cy_SCB_SPI_GetNumInTxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsTxComplete
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_IsTxComplete() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_IsTxComplete(void)
{
    return Cy_SCB_SPI_IsTxComplete(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_ClearTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearTxFifo(void)
{
    Cy_SCB_SPI_ClearTxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSlaveMasterStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_GetSlaveMasterStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetSlaveMasterStatus(void)
{
    return Cy_SCB_SPI_GetSlaveMasterStatus(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearSlaveMasterStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_ClearSlaveMasterStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearSlaveMasterStatus(uint32_t clearMask)
{
    Cy_SCB_SPI_ClearSlaveMasterStatus(`$INSTANCE_NAME`_HW, clearMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Transfer
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Transfer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_spi_status_t `$INSTANCE_NAME`_Transfer(void *txBuffer, void *rxBuffer, uint32_t size)
{
    return Cy_SCB_SPI_Transfer(`$INSTANCE_NAME`_HW, txBuffer, rxBuffer, size, &`$INSTANCE_NAME`_context);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AbortTransfer
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_AbortTransfer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_AbortTransfer(void)
{
    Cy_SCB_SPI_AbortTransfer(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTransferStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_GetTransferStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTransferStatus(void)
{
    return Cy_SCB_SPI_GetTransferStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumTransfered
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_GetNumTransfered() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumTransfered(void)
{
    return Cy_SCB_SPI_GetNumTransfered(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_SPI_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void)
{
    Cy_SCB_SPI_Interrupt(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


#if defined(__cplusplus)
}
#endif

#endif /* `$INSTANCE_NAME`_CY_SCB_SPI_PDL_H */


/* [] END OF FILE */
