/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  PDM_PCM Component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
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

#define `$INSTANCE_NAME`_GAIN_RIGHT             ((uint8_t)(`$GainRight`u))              /* uint8_t */
#define `$INSTANCE_NAME`_GAIN_LEFT				((uint8_t)(`$GainLeft`u))               /* uint8_t */
#define `$INSTANCE_NAME`_SOFT_MUTE_ENABLE   	((bool)(`$SoftMuteEnable`))             /* bool */
#define `$INSTANCE_NAME`_SOFT_MUTE_GAIN  		((bool)(`$SoftMuteFineGain`u))          /* PDM_SM_GAIN_LEVEL */
#define `$INSTANCE_NAME`_CLK_DIV 				((cy_en_pdm_pcm_clk_div_t)(`$ClkDiv`u)) /* PDM_CLK_DIV */
#define `$INSTANCE_NAME`_MCLK_DIV 				((cy_en_pdm_pcm_clk_div_t)(`$MclkDiv`u))/* PDM_CLK_DIV */
#define `$INSTANCE_NAME`_CKO_DIV 				((uint8_t)(`$CkoDiv`u))                 /* uint8_t */
#define `$INSTANCE_NAME`_SINC_DEC_RATE 			((uint8_t)(`$SincDecRate`u))            /* uint8_t */
#define `$INSTANCE_NAME`_CHAN_SELECT 			((cy_en_pdm_pcm_out_t)(`$ChanSelect`u)) /* PDM_PCM_OUT */
#define `$INSTANCE_NAME`_CHAN_SWAP       		((bool)(`$ChanSwapEnable`))             /* bool */
#define `$INSTANCE_NAME`_SOFT_MUTE_CYCLES 		((uint8_t)(`$SoftMuteCycles`u))         /* PDM_SM_CYCLES */
#define `$INSTANCE_NAME`_CKO_DELAY 				((uint8_t)(`$CkoDelay`u))               /* uint8_t */
#define `$INSTANCE_NAME`_HPF_COEFF          	((uint8_t)(`$HighPassFilterCoeff`u))    /* uint8_t */
#define `$INSTANCE_NAME`_HPF_DISABLE            ((bool)(`$HighPassDisable`))            /* bool */
#define `$INSTANCE_NAME`_WORD_LEN 		        ((cy_en_pdm_pcm_wlen_t)(`$WordLength`u))/* PDM_WORD_LEN */
#define `$INSTANCE_NAME`_WORD_BIT_EXT           ((bool)(`$WordBitExtension`u))          /* PDM_WORD_EXT */
#define `$INSTANCE_NAME`_DATA_STREAM_ENABLE     ((bool)(`$DataStreamingEnable`))        /* bool */
#define `$INSTANCE_NAME`_RX_FIFO_TRG_LVL        ((uint8_t)(`$RxFifoTriggerLevel`u))     /* uint8_t */

#define `$INSTANCE_NAME`_DMA_TRG_ENABLE         ((bool)(`$RxFifoDmaEnable`))            /* bool */

#define `$INSTANCE_NAME`_IRQ_RX_TRIGGER         ((bool)(`$RxTriger`))
#define `$INSTANCE_NAME`_IRQ_RX_NOT_EMPTY       ((bool)(`$RxNotEmpty`))
#define `$INSTANCE_NAME`_IRQ_RX_OVERFLOW        ((bool)(`$RxOverflow`))
#define `$INSTANCE_NAME`_IRQ_RX_UNDERFLOW       ((bool)(`$RxUnderflow`))

/* Interrupt masks */
#define `$INSTANCE_NAME`_INT_MASK               (_BOOL2FLD(PDM_INTR_RX_TRIGGER,     `$INSTANCE_NAME`_IRQ_RX_TRIGGER)   | \
                                                 _BOOL2FLD(PDM_INTR_RX_NOT_EMPTY,   `$INSTANCE_NAME`_IRQ_RX_NOT_EMPTY) | \
                                                 _BOOL2FLD(PDM_INTR_RX_OVERFLOW,    `$INSTANCE_NAME`_IRQ_RX_OVERFLOW)  | \
                                                 _BOOL2FLD(PDM_INTR_RX_UNDERFLOW,   `$INSTANCE_NAME`_IRQ_RX_UNDERFLOW) \
                                                )

/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_HW                     (`$INSTANCE_NAME`_cy_mxs40_pdm__HW)

#define `$INSTANCE_NAME`_RX_FIFO_DMA_PTR        (void *)&(`$INSTANCE_NAME`_HW->RX_FIFO_RD)
    
/***************************************
*        Function Prototypes
***************************************/

__STATIC_INLINE cy_en_pdm_pcm_status_t `$INSTANCE_NAME`_Init(void);

                void     `$INSTANCE_NAME`_Start(void);
                void     `$INSTANCE_NAME`_Stop(void);
                void     `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Disable(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_EnableDataStream(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableDataStream(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_SetFifoLevel(uint8_t const level);
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetFifoLevel(void);
__STATIC_INLINE uint16_t `$INSTANCE_NAME`_GetFifoNumWords(void);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifo(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearFifo(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_SetGain(cy_en_pdm_pcm_chan_select_t chan, const uint8_t gain);
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetGain(cy_en_pdm_pcm_chan_select_t chan);

__STATIC_INLINE void     `$INSTANCE_NAME`_EnableSoftMute(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableSoftMute(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_FreezeFifo(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_UnfreezeFifo(void);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifoSilent(void);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearInterrupt(uint32_t const interrupt);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterrupt(uint32_t const interrupt);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterruptMask(uint32_t const interrupt);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);

__STATIC_INLINE void     `$INSTANCE_NAME`_EnableInterrupts(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableInterrupts(void);


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;
extern `=$CY_CONST_CONFIG ? "const " : ""` cy_stc_pdm_pcm_config_t `$INSTANCE_NAME`_config;


/***************************************
*    In-line Functions Implementation
***************************************/

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
***************************************************************************//**
*
* Initialize PDM_PCM module
*
******************************************************************************/
__STATIC_INLINE cy_en_pdm_pcm_status_t `$INSTANCE_NAME`_Init(void)
{
    return Cy_PDM_PCM_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
***************************************************************************//**
*
* Disable PDM_PCM module
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_PDM_PCM_Disable(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableDataStream
***************************************************************************//**
*
* Enable sampling in PDM_PCM module
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableDataStream(void)
{
    Cy_PDM_PCM_EnableDataStream(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableDataStream
***************************************************************************//**
*
* Disable sampling in PDM_PCM module
*
******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableDataStream(void)
{
    Cy_PDM_PCM_DisableDataStream(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFifoLevel
***************************************************************************//**
*
* Set FIFO level value
*
* \param fifoLevel    FIFO level (0 - 254 in Mono mode, 0 - 253 in Stereo mode)
*
******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_SetFifoLevel(uint8_t level)
{
    Cy_PDM_PCM_SetFifoLevel(`$INSTANCE_NAME`_HW, level);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFifoLevel
***************************************************************************//**
*
* Get FIFO level value
*
* \return              Current FIFO level
*
******************************************************************************/
__STATIC_INLINE uint8_t  `$INSTANCE_NAME`_GetFifoLevel(void)
{
    return (Cy_PDM_PCM_GetFifoLevel(`$INSTANCE_NAME`_HW));
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFifoNumWords
***************************************************************************//**
*
* Get elements number in the FIFO
*
* \return              Current number of words (0 - 256)
*
******************************************************************************/
__STATIC_INLINE uint16_t `$INSTANCE_NAME`_GetFifoNumWords(void)
{
    return (Cy_PDM_PCM_GetFifoNumWords(`$INSTANCE_NAME`_HW));
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadFifo
***************************************************************************//**
*
* Get element from FIFO
*
* \return              Data word
*
******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_ReadFifo(void)
{
    return (Cy_PDM_PCM_ReadFifo(`$INSTANCE_NAME`_HW));
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearFifo
***************************************************************************//**
*
* Clear FIFO buffer
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearFifo(void)
{
    Cy_PDM_PCM_ClearFifo(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGain
***************************************************************************//**
*
* Set gain value for data sampling
*
* \param base            Pointer to PDM-PCM instance address
* \param chan            channel selector for gain setting (see #en_pdm_pcm_chan_select_t)
* \param gain            Gain for the selected channel in +1.5dB steps: 0 = -12dB ... 15 = +10.5 dB
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetGain(cy_en_pdm_pcm_chan_select_t chan, uint8_t gain)
{
    Cy_PDM_PCM_SetGain(`$INSTANCE_NAME`_HW, chan, gain);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetGain
***************************************************************************//**
*
* Get gain value for data sampling
*
* \param base           Pointer to PDM-PCM instance address
* \param chan           channel selector for gain setting (see #en_pdm_pcm_chan_select_t)
*
* \return               Gain of the selected channel in +1.5dB steps: 0 = -12dB ... 15 = +10.5 dB
*
******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetGain(cy_en_pdm_pcm_chan_select_t chan)
{
    return (Cy_PDM_PCM_GetGain(`$INSTANCE_NAME`_HW, chan));
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableSoftMute
***************************************************************************//**
*
* Enable soft mute mode
*
******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_EnableSoftMute(void)
{
    Cy_PDM_PCM_EnableSoftMute(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableSoftMute
***************************************************************************//**
*
* Disable soft mute mode
*
******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_DisableSoftMute(void)
{
    Cy_PDM_PCM_DisableSoftMute(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_FreezeFifo
***************************************************************************//**
*
* Freeze FIFO buffer
*
******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_FreezeFifo(void)
{
    Cy_PDM_PCM_FreezeFifo(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_UnfreezeFifo
***************************************************************************//**
*
* Unfreeze FIFO buffer
*
******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_UnfreezeFifo(void)
{
    Cy_PDM_PCM_UnfreezeFifo(`$INSTANCE_NAME`_HW);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadFifoSilent
***************************************************************************//**
*
* Get element from FOFO buffer without change of the FIFO pointer
*
* \return              FIFO value
*
******************************************************************************/
__STATIC_INLINE uint32_t  `$INSTANCE_NAME`_ReadFifoSilent(void)
{
    return (Cy_PDM_PCM_ReadFifoSilent(`$INSTANCE_NAME`_HW));
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
***************************************************************************//**
*
* Get interrupt status
*
* \return uint32_t             Interrupt bits
*
******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return (Cy_PDM_PCM_GetInterruptStatus(`$INSTANCE_NAME`_HW));
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
***************************************************************************//**
*
* Clear one of more interrupt factors
*
* \param interrupt     Interrupt bit(s)
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t interrupt)
{
    Cy_PDM_PCM_ClearInterrupt(`$INSTANCE_NAME`_HW, interrupt);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
***************************************************************************//**
*
* Set one of more interrupt factors
*
* \param interrupt     Interrupt bit(s)
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t interrupt)
{
    Cy_PDM_PCM_SetInterrupt(`$INSTANCE_NAME`_HW, interrupt);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
***************************************************************************//**
*
* Get interrupt mask
*
* \return              Interrupt bits
*
******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (Cy_PDM_PCM_GetInterruptMask(`$INSTANCE_NAME`_HW));
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
***************************************************************************//**
*
* Set one of more interrupt factor mask
*
* \param interrupt     Interrupt bit(s)
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t interrupt)
{
    Cy_PDM_PCM_SetInterruptMask(`$INSTANCE_NAME`_HW, interrupt);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
***************************************************************************//**
*
* \brief Get interrupt status masked
*
* \return             Interrupt bits
*
******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return (Cy_PDM_PCM_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW));
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableInterrupts
***************************************************************************//**
*
* Enable selected interrupt sources
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_EnableInterrupts(void)
{
    Cy_PDM_PCM_SetInterruptMask(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_INT_MASK);
}

/******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableInterrupts
***************************************************************************//**
*
* Disable interrupt sources
*
******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DisableInterrupts(void)
{
    Cy_PDM_PCM_SetInterruptMask(`$INSTANCE_NAME`_HW, 0);
}

#endif /* CY_PDMPCM_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
