/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants, parameter values, and API definition for the
*  `$INSTANCE_NAME` Component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PDMPCM_`$INSTANCE_NAME`_H)
#define CY_PDMPCM_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "pdm_pcm/cy_pdm_pcm.h"


/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_GAIN_LEFT              (`=GetNameForEnum("cy_en_pdm_pcm_gain_t", $GainLeft)`)
#define `$INSTANCE_NAME`_GAIN_RIGHT             (`=GetNameForEnum("cy_en_pdm_pcm_gain_t", $GainRight)`)
#define `$INSTANCE_NAME`_CHANNELS               (`=GetNameForEnum("cy_en_pdm_pcm_out_t", $ChanSelect)`)
#define `$INSTANCE_NAME`_WORD_LEN               (`=GetNameForEnum("cy_en_pdm_pcm_word_len_t", $WordLength)`)
#define `$INSTANCE_NAME`_RX_FIFO_TRG_LVL        (`$RxFifoTriggerLevel`U)

/* Interrupt mask */
#define `$INSTANCE_NAME`_INT_MASK               (_BOOL2FLD(PDM_INTR_RX_TRIGGER,   `=$RxTrig ? true : false`)     | \
                                                 _BOOL2FLD(PDM_INTR_RX_NOT_EMPTY, `=$RxNotEmpty ? true : false`) | \
                                                 _BOOL2FLD(PDM_INTR_RX_OVERFLOW,  `=$RxOverflow ? true : false`) | \
                                                 _BOOL2FLD(PDM_INTR_RX_UNDERFLOW, `=$RxUnderflow ? true : false`))


/***************************************
*           API Constants
***************************************/
    
/** The pointer to the base address of the HW PDM-PCM instance. */
#define `$INSTANCE_NAME`_HW                     (`=LookupFitterDefine("`$INSTANCE_NAME`_cy_mxs40_pdm__HW")`)
/** The Rx FIFO Read register pointer for DMA initialization. */
#define `$INSTANCE_NAME`_RX_FIFO_RD_PTR         ((volatile const uint32_t *) &(`$INSTANCE_NAME`_HW->RX_FIFO_RD))
    
/***************************************
*        Function Prototypes
***************************************/

__STATIC_INLINE void     `$INSTANCE_NAME`_Init(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Deinit(void);
                void     `$INSTANCE_NAME`_Start(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Stop(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Disable(void);

__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetNumInFifo(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifo(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearFifo(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifoSilent(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_FreezeFifo(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_UnfreezeFifo(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_SetGain(cy_en_pdm_pcm_chan_select_t chan, cy_en_pdm_pcm_gain_t gain);
__STATIC_INLINE cy_en_pdm_pcm_gain_t `$INSTANCE_NAME`_GetGain(cy_en_pdm_pcm_chan_select_t chan);

__STATIC_INLINE void     `$INSTANCE_NAME`_EnableSoftMute(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableSoftMute(void);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearInterrupt(uint32_t interrupt);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterrupt(uint32_t interrupt);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterruptMask(uint32_t interrupt);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;
extern `=$CY_CONST_CONFIG ? "const " : ""` cy_stc_pdm_pcm_config_t `$INSTANCE_NAME`_config;


/***************************************
*    In-line Functions Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
* Invokes the Cy_PDM_PCM_Init() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Init(void)
{
    (void) Cy_PDM_PCM_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Deinit
****************************************************************************//**
* Invokes the Cy_PDM_PCM_DeInit() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Deinit(void)
{
    `$INSTANCE_NAME`_initVar = 0U;
    Cy_PDM_PCM_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
* Invokes the Cy_PDM_PCM_Disable() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    Cy_PDM_PCM_Disable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
* Invokes the Cy_PDM_PCM_Enable() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_PDM_PCM_Enable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
* Invokes the Cy_PDM_PCM_Disable() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_PDM_PCM_Disable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNumInFifo
****************************************************************************//**
* Invokes the Cy_PDM_PCM_GetNumInFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetNumInFifo(void)
{
    return (Cy_PDM_PCM_GetNumInFifo(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadFifo
****************************************************************************//**
* Invokes the Cy_PDM_PCM_ReadFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifo(void)
{
    return (Cy_PDM_PCM_ReadFifo(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearFifo
****************************************************************************//**
* Invokes the Cy_PDM_PCM_ClearFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearFifo(void)
{
    Cy_PDM_PCM_ClearFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
****************************************************************************//**
* Invokes the Cy_PDM_PCM_SetGain() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetGain(cy_en_pdm_pcm_chan_select_t chan, cy_en_pdm_pcm_gain_t gain)
{
    Cy_PDM_PCM_SetGain(`$INSTANCE_NAME`_HW, chan, gain);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetGain
****************************************************************************//**
* Invokes the Cy_PDM_PCM_GetGain() PDL driver function.
*******************************************************************************/
__STATIC_INLINE cy_en_pdm_pcm_gain_t `$INSTANCE_NAME`_GetGain(cy_en_pdm_pcm_chan_select_t chan)
{
    return (Cy_PDM_PCM_GetGain(`$INSTANCE_NAME`_HW, chan));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableSoftMute
****************************************************************************//**
* Invokes the Cy_PDM_PCM_EnableSoftMute() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableSoftMute(void)
{
    Cy_PDM_PCM_EnableSoftMute(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableSoftMute
****************************************************************************//**
* Invokes the Cy_PDM_PCM_DisableSoftMute() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableSoftMute(void)
{
    Cy_PDM_PCM_DisableSoftMute(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FreezeFifo
****************************************************************************//**
* Invokes the Cy_PDM_PCM_FreezeFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_FreezeFifo(void)
{
    Cy_PDM_PCM_FreezeFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UnfreezeFifo
****************************************************************************//**
* Invokes the Cy_PDM_PCM_UnfreezeFifo() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_UnfreezeFifo(void)
{
    Cy_PDM_PCM_UnfreezeFifo(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadFifoSilent
****************************************************************************//**
* Invokes the Cy_PDM_PCM_ReadFifoSilent() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifoSilent(void)
{
    return (Cy_PDM_PCM_ReadFifoSilent(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
* Invokes the Cy_PDM_PCM_GetInterruptStatus() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return (Cy_PDM_PCM_GetInterruptStatus(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
* Invokes the Cy_PDM_PCM_ClearInterrupt() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t interrupt)
{
    Cy_PDM_PCM_ClearInterrupt(`$INSTANCE_NAME`_HW, interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
* Invokes the Cy_PDM_PCM_SetInterrupt() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t interrupt)
{
    Cy_PDM_PCM_SetInterrupt(`$INSTANCE_NAME`_HW, interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
* Invokes the Cy_PDM_PCM_GetInterruptMask() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (Cy_PDM_PCM_GetInterruptMask(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
* Invokes the Cy_PDM_PCM_SetInterruptMask() PDL driver function.
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t interrupt)
{
    Cy_PDM_PCM_SetInterruptMask(`$INSTANCE_NAME`_HW, interrupt);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
* Invokes the Cy_PDM_PCM_GetInterruptStatusMasked() PDL driver function.
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return (Cy_PDM_PCM_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW));
}


#endif /* CY_PDMPCM_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
