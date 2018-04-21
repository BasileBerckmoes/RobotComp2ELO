/***************************************************************************//**
* \file     `$INSTANCE_NAME`.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values and API definition for the
*  I2S Component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined CY_I2S_`$INSTANCE_NAME`_H
#define CY_I2S_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "i2s/cy_i2s.h"

#if defined(__cplusplus)
extern "C" {
#endif
    
/***************************************
*     Data Structure Definitions
***************************************/

/* A backup structure to store current state */
typedef struct
{                                 
	/* Current component state storage */
	uint32_t enableState;
	/* Current interrupt setting storage */
	uint32_t interruptMask;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*   Variables with external linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern `=$CY_CONST_CONFIG ? "const " : ""`cy_stc_i2s_config_t `$INSTANCE_NAME`_config;
/** @} globals */

extern uint8_t `$INSTANCE_NAME`_initVar;
extern `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup;


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/
                void     `$INSTANCE_NAME`_Start(void);
                void     `$INSTANCE_NAME`_Stop(void);
                
__STATIC_INLINE void     `$INSTANCE_NAME`_Init(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DeInit(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_EnableTx(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_PauseTx(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ResumeTx(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableTx(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_EnableRx(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableRx(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCurrentState(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_ClearTxFifo(void);
__STATIC_INLINE uint16_t `$INSTANCE_NAME`_GetTxFifoLevel(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_WriteTxData(uint32_t data);
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetTxReadPointer(void);
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetTxWritePointer(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_ClearRxFifo(void);
__STATIC_INLINE uint16_t `$INSTANCE_NAME`_GetRxFifoLevel(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadRxData(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadSilentRxData(void);
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetRxReadPointer(void);
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetRxWritePointer(void);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearInterrupt(uint32_t interrupt);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterrupt(uint32_t interrupt);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterruptMask(uint32_t interrupt);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_constants
* @{
*/
/** The pointer to the base address of the HW I2S instance. */
#define `$INSTANCE_NAME`_HW             (`=LookupFitterDefine("`$INSTANCE_NAME`_cy_mxs40_i2s__HW")`)
/** Tx FIFO Write register pointer for DMA initialization. */
#define `$INSTANCE_NAME`_TX_FIFO_WR_PTR ((uint32_t *) &`$INSTANCE_NAME`_HW->TX_FIFO_WR)
/** Rx FIFO Read register pointer for DMA initialization. */
#define `$INSTANCE_NAME`_RX_FIFO_RD_PTR ((uint32_t *) &`$INSTANCE_NAME`_HW->RX_FIFO_RD)

/** \cond internal definitions */
#define `$INSTANCE_NAME`_CHAN_NMBR       (2U)
#define `$INSTANCE_NAME`_TX_ENABLED      (`=$TxEnabled ? true : false`)
#define `$INSTANCE_NAME`_RX_ENABLED      (`=$RxEnabled ? true : false`)

#if(`$INSTANCE_NAME`_TX_ENABLED)
    #define `$INSTANCE_NAME`_INT_MASK_TX ( \
        (_BOOL2FLD(I2S_INTR_MASK_TX_TRIGGER,   `=$TxTrig ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_TX_NOT_FULL,  `=$TxNotFull ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_TX_EMPTY,     `=$TxEmpty ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_TX_OVERFLOW,  `=$TxOverFlow ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_TX_UNDERFLOW, `=$TxUnderFlow ? true : false`)))
#else /* `$INSTANCE_NAME`_TX_ENABLED */
    #define `$INSTANCE_NAME`_INT_MASK_TX (0UL)
#endif /* `$INSTANCE_NAME`_TX_ENABLED */
        
#if(`$INSTANCE_NAME`_RX_ENABLED)
    #define `$INSTANCE_NAME`_INT_MASK_RX ( \
        (_BOOL2FLD(I2S_INTR_MASK_RX_TRIGGER,   `=$RxTrig ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_RX_NOT_EMPTY, `=$RxNotEmpty ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_RX_FULL,      `=$RxFull ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_RX_OVERFLOW,  `=$RxOverFlow ? true : false`)) | \
        (_BOOL2FLD(I2S_INTR_MASK_RX_UNDERFLOW, `=$RxUnderFlow ? true : false`)))
#else /* `$INSTANCE_NAME`_RX_ENABLED */
    #define `$INSTANCE_NAME`_INT_MASK_RX (0UL)
#endif /* `$INSTANCE_NAME`_RX_ENABLED */
/** \endcond */

/** The default (configured in GUI) interrupt mask. */
#define `$INSTANCE_NAME`_INT_MASK (`$INSTANCE_NAME`_INT_MASK_TX | `$INSTANCE_NAME`_INT_MASK_RX)

#if(`$INSTANCE_NAME`_TX_ENABLED)
    /** Tx FIFO Trigger Level. */
    #define `$INSTANCE_NAME`_TX_FIFO_TRG_LVL (`$TxFifoTriggerLevel`U)
#endif /* `$INSTANCE_NAME`_TX_ENABLED */

#if(`$INSTANCE_NAME`_RX_ENABLED)
    /** Rx FIFO Trigger Level. */
    #define `$INSTANCE_NAME`_RX_FIFO_TRG_LVL (`$RxFifoTriggerLevel`U)
#endif /* `$INSTANCE_NAME`_RX_ENABLED */

/** @} globals */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
* Invokes the Cy_I2S_Init() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Init(void)
{
    (void)Cy_I2S_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
* Invokes the Cy_I2S_DeInit() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)
{
    `$INSTANCE_NAME`_initVar = 0U;
	Cy_I2S_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableTx
****************************************************************************//**
* Invokes the Cy_I2S_TxStart() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableTx(void)
{
    Cy_I2S_TxStart(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_PauseTx
****************************************************************************//**
* Invokes the Cy_I2S_TxPause() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_PauseTx(void)
{
    Cy_I2S_TxPause(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ResumeTx
****************************************************************************//**
* Invokes the Cy_I2S_TxResume() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ResumeTx(void)
{
    Cy_I2S_TxResume(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableTx
****************************************************************************//**
* Invokes the Cy_I2S_TxStop() PDL driver function.
* *****************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableTx(void)
{
    Cy_I2S_TxStop(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCurrentState
****************************************************************************//**
* Invokes the Cy_I2S_GetCurrentState() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCurrentState(void)
{
    return (Cy_I2S_GetCurrentState(`$INSTANCE_NAME`_HW));
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFifo
****************************************************************************//**
* Invokes the Cy_I2S_ClearTxFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearTxFifo(void)
{
    Cy_I2S_ClearTxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxFifoLevel
****************************************************************************//**
* Invokes the Cy_I2S_GetTxFifoLevel() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint16_t `$INSTANCE_NAME`_GetTxFifoLevel(void)
{
    return (Cy_I2S_GetTxFifoLevel(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteTxData
****************************************************************************//**
* Invokes the Cy_I2S_WriteTxData() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_WriteTxData(uint32_t data)
{
    Cy_I2S_WriteTxData(`$INSTANCE_NAME`_HW, data);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxReadPointer
****************************************************************************//**
* Invokes the Cy_I2S_GetTxReadPointer() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetTxReadPointer(void)
{
    return (Cy_I2S_GetTxReadPointer(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxWritePointer
****************************************************************************//**
* Invokes the Cy_I2S_GetTxWritePointer() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetTxWritePointer(void)
{
    return (Cy_I2S_GetTxWritePointer(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableRx
****************************************************************************//**
* Invokes the Cy_I2S_RxStart() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableRx(void)
{
    Cy_I2S_RxStart(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableRx
****************************************************************************//**
* Invokes the Cy_I2S_RxStop() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableRx(void)
{
    Cy_I2S_RxStop(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearRxFifo
****************************************************************************//**
* Invokes the Cy_I2S_ClearRxFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearRxFifo(void)
{
    Cy_I2S_ClearRxFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRxFifoLevel
****************************************************************************//**
* Invokes the Cy_I2S_GetRxFifoLevel() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint16_t `$INSTANCE_NAME`_GetRxFifoLevel(void)
{
    return (Cy_I2S_GetRxFifoLevel(`$INSTANCE_NAME`_HW));
}

 
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadRxData
****************************************************************************//**
* Invokes the Cy_I2S_ReadRxData() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadRxData(void)
{
    return (Cy_I2S_ReadRxData(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadSilentRxData
****************************************************************************//**
* Invokes the Cy_I2S_ReadSilentRxData() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadSilentRxData(void)
{
    return (Cy_I2S_ReadSilentRxData(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRxReadPointer
****************************************************************************//**
* Invokes the Cy_I2S_GetRxReadPointer() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetRxReadPointer(void)
{
    return (Cy_I2S_GetRxReadPointer(`$INSTANCE_NAME`_HW));
}

 
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetRxWritePointer
****************************************************************************//**
* Invokes the Cy_I2S_GetRxWritePointer() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetRxWritePointer(void)
{
    return (Cy_I2S_GetRxWritePointer(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
* Invokes the Cy_I2S_GetInterruptStatus() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return (Cy_I2S_GetInterruptStatus(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
* Invokes the Cy_I2S_ClearInterrupt() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t interrupt)
{
    Cy_I2S_ClearInterrupt(`$INSTANCE_NAME`_HW, interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
* Invokes the Cy_I2S_SetInterrupt() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t interrupt)
{
    Cy_I2S_SetInterrupt(`$INSTANCE_NAME`_HW, interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
* Invokes the Cy_I2S_GetInterruptMask() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (Cy_I2S_GetInterruptMask(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
* Invokes the Cy_I2S_SetInterruptMask() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t interrupt)
{
    Cy_I2S_SetInterruptMask(`$INSTANCE_NAME`_HW, interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
* Invokes the Cy_I2S_GetInterruptStatusMasked() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return (Cy_I2S_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW));
}


#if defined(__cplusplus)
}
#endif

#endif /* CY_I2S_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
