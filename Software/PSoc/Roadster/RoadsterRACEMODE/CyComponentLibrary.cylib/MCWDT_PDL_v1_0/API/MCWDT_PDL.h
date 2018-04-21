/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the `$INSTANCE_NAME`
*  component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_MCWDT_PDL_H)
#define `$INSTANCE_NAME`_CY_MCWDT_PDL_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "cyfitter.h"
#include "mcwdt/cy_mcwdt.h"

/*******************************************************************************
*   Variables
*******************************************************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t  `$INSTANCE_NAME`_initVar;
extern `=$CY_CONST_CONFIG ? "const " : ""`cy_stc_mcwdt_config_t `$INSTANCE_NAME`_config;
/** @} group_globals */

/***************************************
*   Conditional Compilation Parameters
****************************************/
#define `$INSTANCE_NAME`_C0_CLEAR_ON_MATCH  (`$C0ClearOnMatch`U)
#define `$INSTANCE_NAME`_C1_CLEAR_ON_MATCH  (`$C1ClearOnMatch`U)
#define `$INSTANCE_NAME`_CASCADE_C0C1       (`$CascadeC0C1`U)
#define `$INSTANCE_NAME`_CASCADE_C1C2       (`$CascadeC1C2`U)
#define `$INSTANCE_NAME`_C0_MATCH           (`$C0Match`U)
#define `$INSTANCE_NAME`_C0_MODE            (`$C0Mode`U)
#define `$INSTANCE_NAME`_C1_MATCH           (`$C1Match`U)
#define `$INSTANCE_NAME`_C1_MODE            (`$C1Mode`U)
#define `$INSTANCE_NAME`_C2_PERIOD          (`$C2Period`U)
#define `$INSTANCE_NAME`_C2_MODE            (`$C2Mode`U)

#if (0u == `$C0_enable`U)
    #define `$INSTANCE_NAME`_CTR0_EN_MASK   0UL
#else
    #define `$INSTANCE_NAME`_CTR0_EN_MASK   CY_MCWDT_CTR0
#endif
#if (0u == `$C1_enable`U)
    #define `$INSTANCE_NAME`_CTR1_EN_MASK   0UL
#else
    #define `$INSTANCE_NAME`_CTR1_EN_MASK   CY_MCWDT_CTR1
#endif
#if (0u == `$C2_enable`U)
    #define `$INSTANCE_NAME`_CTR2_EN_MASK   0UL
#else
    #define `$INSTANCE_NAME`_CTR2_EN_MASK   CY_MCWDT_CTR2
#endif

#define `$INSTANCE_NAME`_ENABLED_CTRS_MASK  (`$INSTANCE_NAME`_CTR0_EN_MASK |\
                                             `$INSTANCE_NAME`_CTR1_EN_MASK |\
                                             `$INSTANCE_NAME`_CTR2_EN_MASK)
											 
#if (1U == `$INSTANCE_NAME`_C0_MODE) | (3U == `$INSTANCE_NAME`_C0_MODE)
    #define `$INSTANCE_NAME`_CTR0_INT_MASK   CY_MCWDT_CTR0
#else
    #define `$INSTANCE_NAME`_CTR0_INT_MASK   0UL
#endif
#if (1U == `$INSTANCE_NAME`_C1_MODE) | (3U == `$INSTANCE_NAME`_C1_MODE)
    #define `$INSTANCE_NAME`_CTR1_INT_MASK   CY_MCWDT_CTR1
#else
    #define `$INSTANCE_NAME`_CTR1_INT_MASK   0UL
#endif
#if (1U == `$INSTANCE_NAME`_C2_MODE)
    #define `$INSTANCE_NAME`_CTR2_INT_MASK   CY_MCWDT_CTR2
#else
    #define `$INSTANCE_NAME`_CTR2_INT_MASK   0UL
#endif 

#define `$INSTANCE_NAME`_CTRS_INT_MASK      (`$INSTANCE_NAME`_CTR0_INT_MASK |\
                                             `$INSTANCE_NAME`_CTR1_INT_MASK |\
                                             `$INSTANCE_NAME`_CTR2_INT_MASK)										 

/***************************************
*        Registers Constants
***************************************/

/* This is a ptr to the base address of the MCWDT instance. */
#define `$INSTANCE_NAME`_HW                 (`$INSTANCE_NAME`_MCWDT__HW)

#if (0u == `$INSTANCE_NAME`_MCWDT__IDX)
    #define `$INSTANCE_NAME`_RESET_REASON   CY_SYSLIB_RESET_SWWDT0
#else
    #define `$INSTANCE_NAME`_RESET_REASON   CY_SYSLIB_RESET_SWWDT1
#endif 

#define `$INSTANCE_NAME`_TWO_LF_CLK_CYCLES_DELAY (62u)


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/
/**
* \addtogroup group_general
* @{
*/
                void     `$INSTANCE_NAME`_Start(void);
                void     `$INSTANCE_NAME`_Stop(void);
__STATIC_INLINE cy_en_mcwdt_status_t `$INSTANCE_NAME`_Init(const cy_stc_mcwdt_config_t *config);
__STATIC_INLINE void     `$INSTANCE_NAME`_DeInit(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Enable(uint32_t counters, uint16_t waitUs);
__STATIC_INLINE void     `$INSTANCE_NAME`_Disable(uint32_t counters, uint16_t waitUs);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetEnabledStatus(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     `$INSTANCE_NAME`_Lock(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_Unlock(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetLockedStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetMode(cy_en_mcwdtctr_t counter, cy_en_mcwdtmode_t mode);
__STATIC_INLINE cy_en_mcwdtmode_t `$INSTANCE_NAME`_GetMode(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetClearOnMatch(cy_en_mcwdtctr_t counter, uint32_t enable);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetClearOnMatch(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetCascade(cy_en_mcwdtcascade_t cascade);
__STATIC_INLINE cy_en_mcwdtcascade_t `$INSTANCE_NAME`_GetCascade(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetMatch(cy_en_mcwdtctr_t counter, uint32_t match, uint16_t waitUs);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetMatch(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetToggleBit(uint32_t bit);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetToggleBit(void);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCount(cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     `$INSTANCE_NAME`_ResetCounters(uint32_t counters, uint16_t waitUs);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_ClearInterrupt(uint32_t counters);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterrupt(uint32_t counters);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetInterruptMask(uint32_t counters);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void);
/** @} general */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdt_status_t `$INSTANCE_NAME`_Init(const cy_stc_mcwdt_config_t *config)
{
    return (Cy_MCWDT_Init(`$INSTANCE_NAME`_HW, config));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
*
* Invokes the Cy_MCWDT_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)
{
    Cy_MCWDT_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(uint32_t counters, uint16_t waitUs)
{
    Cy_MCWDT_Enable(`$INSTANCE_NAME`_HW, counters, waitUs);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(uint32_t counters, uint16_t waitUs)
{
    Cy_MCWDT_Disable(`$INSTANCE_NAME`_HW, counters, waitUs);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetEnabledStatus
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetEnabledStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetEnabledStatus(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetEnabledStatus(`$INSTANCE_NAME`_HW, counter));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Lock
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Lock() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Lock(void)
{
    Cy_MCWDT_Lock(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Unlock
****************************************************************************//**
*
* Invokes the Cy_MCWDT_Unlock() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Unlock(void)
{
   Cy_MCWDT_Unlock(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetLockStatus
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetLockedStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetLockedStatus(void)
{
    return (Cy_MCWDT_GetLockedStatus(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMode
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetMode() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetMode(cy_en_mcwdtctr_t counter, cy_en_mcwdtmode_t mode)
{
    Cy_MCWDT_SetMode(`$INSTANCE_NAME`_HW, counter, mode);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMode
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetMode() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtmode_t `$INSTANCE_NAME`_GetMode(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetMode(`$INSTANCE_NAME`_HW, counter));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetClearOnMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetClearOnMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetClearOnMatch(cy_en_mcwdtctr_t counter, uint32_t enable)
{
    Cy_MCWDT_SetClearOnMatch(`$INSTANCE_NAME`_HW, counter, enable);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetClearOnMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetClearOnMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetClearOnMatch(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetClearOnMatch(`$INSTANCE_NAME`_HW, counter));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCascade
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetCascade() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetCascade(cy_en_mcwdtcascade_t cascade)
{
    Cy_MCWDT_SetCascade(`$INSTANCE_NAME`_HW, cascade);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCascade
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetCascade() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtcascade_t `$INSTANCE_NAME`_GetCascade(void)
{
    return (Cy_MCWDT_GetCascade(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetMatch(cy_en_mcwdtctr_t counter, uint32_t match, uint16_t waitUs)
{
    Cy_MCWDT_SetMatch(`$INSTANCE_NAME`_HW, counter, match, waitUs);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMatch
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetMatch() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetMatch(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetMatch(`$INSTANCE_NAME`_HW, counter));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetToggleBit
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetToggleBit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetToggleBit(uint32_t bit)
{
    Cy_MCWDT_SetToggleBit(`$INSTANCE_NAME`_HW, bit);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetToggleBit
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetToggleBit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetToggleBit(void)
{
    return (Cy_MCWDT_GetToggleBit(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCount
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetCount() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetCount(cy_en_mcwdtctr_t counter)
{
    return (Cy_MCWDT_GetCount(`$INSTANCE_NAME`_HW, counter));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ResetCounters
****************************************************************************//**
*
* Invokes the Cy_MCWDT_ResetCounters() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ResetCounters(uint32_t counters, uint16_t waitUs)
{
    Cy_MCWDT_ResetCounters(`$INSTANCE_NAME`_HW, counters, waitUs);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return (Cy_MCWDT_GetInterruptStatus(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_MCWDT_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32_t counters)
{
    Cy_MCWDT_ClearInterrupt(`$INSTANCE_NAME`_HW, counters);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32_t counters)
{
    Cy_MCWDT_SetInterrupt(`$INSTANCE_NAME`_HW, counters);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_MCWDT_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (Cy_MCWDT_GetInterruptMask(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_MCWDT_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32_t counters)
{
    Cy_MCWDT_SetInterruptMask(`$INSTANCE_NAME`_HW, counters);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
* Invokes the Cy_MCWDT_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return (Cy_MCWDT_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW));
}

#if defined(__cplusplus)
}
#endif

#endif /* `$INSTANCE_NAME`_CY_MCWDT_PDL_H */


/* [] END OF FILE */
