/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides constants and parameter values for the UART component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_SCB_UART_PDL_H)
#define `$INSTANCE_NAME`_CY_SCB_UART_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_DIRECTION  (`$Direction`U)
#define `$INSTANCE_NAME`_ENABLE_RTS (`$EnableRts`U)
#define `$INSTANCE_NAME`_ENABLE_CTS (`$EnableCts`U)

/* UART direction enum */
#define `$INSTANCE_NAME`_RX    (0x1U)
#define `$INSTANCE_NAME`_TX    (0x2U)

#define `$INSTANCE_NAME`_ENABLE_RX  (0UL != (`$INSTANCE_NAME`_DIRECTION & `$INSTANCE_NAME`_RX))
#define `$INSTANCE_NAME`_ENABLE_TX  (0UL != (`$INSTANCE_NAME`_DIRECTION & `$INSTANCE_NAME`_TX))


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component specific functions. */
void `$INSTANCE_NAME`_Start(void);

/* Basic functions */
__STATIC_INLINE cy_en_scb_uart_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_uart_config_t const *config);
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);

/* Register callback. */
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterCallback(cy_cb_scb_uart_handle_events_t callback);

/* Configuration change. */
#if (`$INSTANCE_NAME`_ENABLE_CTS)
__STATIC_INLINE void `$INSTANCE_NAME`_EnableCts(void);
__STATIC_INLINE void `$INSTANCE_NAME`_DisableCts(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_CTS) */

#if (`$INSTANCE_NAME`_ENABLE_RTS)
__STATIC_INLINE void     `$INSTANCE_NAME`_SetRtsFifoLevel(uint32_t level);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetRtsFifoLevel(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_RTS) */

__STATIC_INLINE void `$INSTANCE_NAME`_EnableSkipStart(void);
__STATIC_INLINE void `$INSTANCE_NAME`_DisableSkipStart(void);

#if (`$INSTANCE_NAME`_ENABLE_RX)
/* Low level: Receive direction. */
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Get(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetArray(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_GetArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetRxFifoStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearRxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInRxFifo(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearRxFifo(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_RX) */

#if (`$INSTANCE_NAME`_ENABLE_TX)
/* Low level: Transmit direction. */
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Put(uint32_t data);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_PutArray(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_PutArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_PutString(char_t const string[]);
__STATIC_INLINE void     `$INSTANCE_NAME`_SendBreakBlocking(uint32_t breakWidth);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTxFifoStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearTxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInTxFifo(void);
__STATIC_INLINE bool     `$INSTANCE_NAME`_IsTxComplete(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearTxFifo(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_TX) */

#if (`$INSTANCE_NAME`_ENABLE_RX)
/* High level: Ring buffer functions. */
__STATIC_INLINE void     `$INSTANCE_NAME`_StartRingBuffer(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_StopRingBuffer(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearRingBuffer(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInRingBuffer(void);

/* High level: Receive direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t `$INSTANCE_NAME`_Receive(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_AbortReceive(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetReceiveStatus(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumReceived(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_RX) */

#if (`$INSTANCE_NAME`_ENABLE_TX)
/* High level: Transmit direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t `$INSTANCE_NAME`_Transmit(void *buffer, uint32_t size);
__STATIC_INLINE void     `$INSTANCE_NAME`_AbortTransmit(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTransmitStatus(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumLeftToTransmit(void);
#endif /* (`$INSTANCE_NAME`_ENABLE_TX) */

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
extern cy_stc_scb_uart_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
extern cy_stc_scb_uart_context_t `$INSTANCE_NAME`_context;
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
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_uart_config_t const *config)
{
   return Cy_SCB_UART_Init(`$INSTANCE_NAME`_HW, config, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)
{
    Cy_SCB_UART_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_SCB_UART_Enable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_SCB_UART_Disable(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RegisterCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_RegisterCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_RegisterCallback(cy_cb_scb_uart_handle_events_t callback)
{
    Cy_SCB_UART_RegisterCallback(`$INSTANCE_NAME`_HW, callback, &`$INSTANCE_NAME`_context);
}


#if (`$INSTANCE_NAME`_ENABLE_CTS)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableCts(void)
{
    Cy_SCB_UART_EnableCts(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableCts(void)
{
    Cy_SCB_UART_DisableCts(`$INSTANCE_NAME`_HW);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_CTS) */


#if (`$INSTANCE_NAME`_ENABLE_RTS)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetRtsFifoLevel(uint32_t level)
{
    Cy_SCB_UART_SetRtsFifoLevel(`$INSTANCE_NAME`_HW, level);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetRtsFifoLevel(void)
{
    return Cy_SCB_UART_GetRtsFifoLevel(`$INSTANCE_NAME`_HW);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_RTS) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableSkipStart(void)
{
    Cy_SCB_UART_EnableSkipStart(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableSkipStart(void)
{
    Cy_SCB_UART_DisableSkipStart(`$INSTANCE_NAME`_HW);
}


#if (`$INSTANCE_NAME`_ENABLE_RX)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Get
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Get() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Get(void)
{
    return Cy_SCB_UART_Get(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_GetArray(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_GetArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_GetArrayBlocking(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetRxFifoStatus(void)
{
    return Cy_SCB_UART_GetRxFifoStatus(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearRxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearRxFifoStatus(`$INSTANCE_NAME`_HW, clearMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumInRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInRxFifo(void)
{
    return Cy_SCB_UART_GetNumInRxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearRxFifo(void)
{
    Cy_SCB_UART_ClearRxFifo(`$INSTANCE_NAME`_HW);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_RX) */


#if (`$INSTANCE_NAME`_ENABLE_TX)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Put
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Put() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_Put(uint32_t data)
{
    return Cy_SCB_UART_Put(`$INSTANCE_NAME`_HW,data);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_PutArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_PutArray(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_PutArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_PutArrayBlocking(`$INSTANCE_NAME`_HW, buffer, size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PutString
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutString() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_PutString(char_t const string[])
{
    Cy_SCB_UART_PutString(`$INSTANCE_NAME`_HW, string);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SendBreakBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SendBreakBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SendBreakBlocking(uint32_t breakWidth)
{
    Cy_SCB_UART_SendBreakBlocking(`$INSTANCE_NAME`_HW, breakWidth);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTxFifoStatus(void)
{
    return Cy_SCB_UART_GetTxFifoStatus(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearTxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearTxFifoStatus(`$INSTANCE_NAME`_HW, clearMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumInTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInTxFifo(void)
{
    return Cy_SCB_UART_GetNumInTxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsTxComplete
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_IsTxComplete() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_IsTxComplete(void)
{
    return Cy_SCB_UART_IsTxComplete(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearTxFifo(void)
{
    Cy_SCB_UART_ClearTxFifo(`$INSTANCE_NAME`_HW);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_TX) */


#if (`$INSTANCE_NAME`_ENABLE_RX)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StartRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_StartRingBuffer(void *buffer, uint32_t size)
{
    Cy_SCB_UART_StartRingBuffer(`$INSTANCE_NAME`_HW, buffer, size, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StopRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StopRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_StopRingBuffer(void)
{
    Cy_SCB_UART_StopRingBuffer(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearRingBuffer(void)
{
    Cy_SCB_UART_ClearRingBuffer(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumInRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumInRingBuffer(void)
{
    return Cy_SCB_UART_GetNumInRingBuffer(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Receive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Receive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t `$INSTANCE_NAME`_Receive(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Receive(`$INSTANCE_NAME`_HW, buffer, size, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetReceiveStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetReceiveStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetReceiveStatus(void)
{
    return Cy_SCB_UART_GetReceiveStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AbortReceive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortReceive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_AbortReceive(void)
{
    Cy_SCB_UART_AbortReceive(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumReceived
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumReceived() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumReceived(void)
{
    return Cy_SCB_UART_GetNumReceived(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_RX) */


#if (`$INSTANCE_NAME`_ENABLE_TX)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Transmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Transmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t `$INSTANCE_NAME`_Transmit(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Transmit(`$INSTANCE_NAME`_HW, buffer, size, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTransmitStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTransmitStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTransmitStatus(void)
{
    return Cy_SCB_UART_GetTransmitStatus(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_AbortTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_AbortTransmit(void)
{
    Cy_SCB_UART_AbortTransmit(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumLeftToTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumLeftToTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetNumLeftToTransmit(void)
{
    return Cy_SCB_UART_GetNumLeftToTransmit(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_TX) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void)
{
    Cy_SCB_UART_Interrupt(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* `$INSTANCE_NAME`_CY_SCB_UART_PDL_H */


/* [] END OF FILE */
