/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the `$INSTANCE_NAME`
*  component.
*
********************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_TCPWM_QUADDEC_PDL_H)
#define `$INSTANCE_NAME`_CY_TCPWM_QUADDEC_PDL_H

#include "cyfitter.h"
#include "tcpwm/cy_tcpwm_quaddec.h"

   
/*******************************************************************************
* Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  `$INSTANCE_NAME`_initVar;
extern cy_stc_tcpwm_quaddec_config_t `= $CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
/** @} group_globals */

    
/***************************************
*        Function Prototypes
****************************************/
/**
* \addtogroup group_general
* @{
*/
void `$INSTANCE_NAME`_Start(void);
__STATIC_INLINE cy_en_tcpwm_status_t `$INSTANCE_NAME`_Init(cy_stc_tcpwm_quaddec_config_t const *config);
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetStatus(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCapture(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCaptureBuf(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetCounter(uint32_t count);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCounter(void);
__STATIC_INLINE void `$INSTANCE_NAME`_TriggerIndex(void);
__STATIC_INLINE void `$INSTANCE_NAME`_TriggerStop(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t source);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t source);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t mask);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);
/** @} general */


/***************************************
*           API Constants
***************************************/

/**
* \addtogroup group_macros
* @{
*/
/** This is a ptr to the base address of the TCPWM instance */
#define `$INSTANCE_NAME`_HW                 (`$INSTANCE_NAME`_TCPWM__HW)

/** This is a ptr to the base address of the TCPWM CNT instance */
#define `$INSTANCE_NAME`_CNT_HW             (`$INSTANCE_NAME`_TCPWM__CNT_HW)

/** This is the counter instance number in the selected TCPWM */
#define `$INSTANCE_NAME`_CNT_NUM            (`$INSTANCE_NAME`_TCPWM__CNT_IDX)

/** This is the bit field representing the counter instance in the selected TCPWM */
#define `$INSTANCE_NAME`_CNT_MASK           (1UL << `$INSTANCE_NAME`_CNT_NUM)
/** @} group_macros */

#define `$INSTANCE_NAME`_INPUT_MODE_MASK    (0x3U)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t `$INSTANCE_NAME`_Init(cy_stc_tcpwm_quaddec_config_t const *config)
{
    return(Cy_TCPWM_QuadDec_Init(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, config));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)                   
{
    Cy_TCPWM_QuadDec_DeInit(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, &`$INSTANCE_NAME`_config);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Enable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)                   
{
    Cy_TCPWM_Enable_Multiple(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_TCPWM_Disable_Multiple() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)                  
{
    Cy_TCPWM_Disable_Multiple(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_GetStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetStatus(void)                
{
    return(Cy_TCPWM_QuadDec_GetStatus(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCapture
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_GetCapture() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCapture(void)               
{
    return(Cy_TCPWM_QuadDec_GetCapture(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCaptureBuf
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_GetCaptureBuf() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCaptureBuf(void)            
{
    return(Cy_TCPWM_QuadDec_GetCaptureBuf(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_SetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetCounter(uint32_t count)          
{
    Cy_TCPWM_QuadDec_SetCounter(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, count);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCounter
****************************************************************************//**
*
* Invokes the Cy_TCPWM_QuadDec_GetCounter() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCounter(void)               
{
    return(Cy_TCPWM_QuadDec_GetCounter(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TriggerIndex
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerReloadOrIndex() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_TriggerIndex(void)     
{
    Cy_TCPWM_TriggerReloadOrIndex(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TriggerStop
****************************************************************************//**
*
* Invokes the Cy_TCPWM_TriggerStopOrKill() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_TriggerStop(void)
{
    Cy_TCPWM_TriggerStopOrKill(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)       
{
    return(Cy_TCPWM_GetInterruptStatus(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t source)     
{
    Cy_TCPWM_ClearInterrupt(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t source)
{
    Cy_TCPWM_SetInterrupt(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, source);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t mask)     
{
    Cy_TCPWM_SetInterruptMask(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM, mask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)         
{
    return(Cy_TCPWM_GetInterruptMask(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_TCPWM_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return(Cy_TCPWM_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CNT_NUM));
}

#endif /* `$INSTANCE_NAME`_CY_TCPWM_QUADDEC_PDL_H */


/* [] END OF FILE */
