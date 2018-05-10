/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Low Power Comparator component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_LPCOMP_`$INSTANCE_NAME`_H)
#define CY_LPCOMP_`$INSTANCE_NAME`_H

#include "lpcomp/cy_lpcomp.h"
#include "cyfitter.h"

/**
* \addtogroup group_globals
* @{
*/
extern uint8_t `$INSTANCE_NAME`_initVar;
extern `=$CY_CONST_CONFIG ? "const" : ""` cy_stc_lpcomp_config_t `$INSTANCE_NAME`_config;
/** @} group_globals */

/**************************************
*        Function Prototypes
**************************************/
/**
* \addtogroup group_general
* @{
*/

void `$INSTANCE_NAME`_Start(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_SetInterruptTriggerMode(uint32 intType);
__STATIC_INLINE void `$INSTANCE_NAME`_UlpReferenceEnable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_UlpReferenceDisable(void);
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetCompare(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetPower(uint32 power);
__STATIC_INLINE void `$INSTANCE_NAME`_SetHysteresis(uint32 hysteresis);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInputs(cy_en_lpcomp_inputs_t inputP, cy_en_lpcomp_inputs_t inputN);
__STATIC_INLINE void `$INSTANCE_NAME`_SetOutputMode(uint32 mode);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32 interruptMask);
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetInterruptMask(void);
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetInterruptStatusMasked(void);
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetInterruptStatus(void);
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask);
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask);
/** @} general */

/**************************************
*           API Constants
**************************************/

#define `$INSTANCE_NAME`_HW                             (`$INSTANCE_NAME`_cy_mxs40_lpcomp__HW)
#define `$INSTANCE_NAME`_IDX                            (`$INSTANCE_NAME`_cy_mxs40_lpcomp__IDX)                                                                                           

/* Channel */
#define `$INSTANCE_NAME`_CHANNEL ((cy_en_lpcomp_channel_t)((`$INSTANCE_NAME`_IDX == 0) ? \
                                                        (CY_LPCOMP_CHANNEL_0) : (CY_LPCOMP_CHANNEL_1)))

/* Constants for `$INSTANCE_NAME`_Start(), init parameter */
#define `$INSTANCE_NAME`_NOT_INITIALIZED                (0x00u)
#define `$INSTANCE_NAME`_INITIALIZED                    (0x01u)

/* Constant for `$INSTANCE_NAME`_GetInterruptStatus() and 
* `$INSTANCE_NAME`_ClearInterrupt(), interruptMask parameter 
*/
#define `$INSTANCE_NAME`_INTR                           (uint32_t)((`$INSTANCE_NAME`_IDX == 0) ? \
                                                                   (LPCOMP_INTR_COMP0_Msk) : (LPCOMP_INTR_COMP1_Msk))

/* Constant for `$INSTANCE_NAME`_SetInterrupt(), interruptMask parameter */
#define `$INSTANCE_NAME`_INTR_SET                       (uint32_t)((`$INSTANCE_NAME`_IDX == 0) ? \
                                                                   (LPCOMP_INTR_SET_COMP0_Msk) : (LPCOMP_INTR_SET_COMP1_Msk))

/* Constant for `$INSTANCE_NAME`_GetInterruptMask() and 
* `$INSTANCE_NAME`_SetInterruptMask(), interruptMask parameter 
*/
#define `$INSTANCE_NAME`_INTR_MASK                      (uint32_t)((`$INSTANCE_NAME`_IDX == 0) ? \
                                                                   (LPCOMP_INTR_MASK_COMP0_MASK_Msk) : (LPCOMP_INTR_MASK_COMP1_MASK_Msk))

/* Constant for `$INSTANCE_NAME`_GetInterruptStatusMasked() */ 
#define `$INSTANCE_NAME`_INTR_MASKED                    (uint32_t)((`$INSTANCE_NAME`_IDX == 0) ? \
                                                                   (LPCOMP_INTR_MASKED_COMP0_MASKED_Msk) : (LPCOMP_INTR_MASKED_COMP1_MASKED_Msk))

/***************************************
*   Initial Parameter Constants
****************************************/
    
#define `$INSTANCE_NAME`_INTERRUPT                      (`$PulseInterruptConfiguration`u)
#define `$INSTANCE_NAME`_POWER                          (`$PowerSpeed`u)
#define `$INSTANCE_NAME`_HYSTERESIS                     (`$Hysteresis`u)
#define `$INSTANCE_NAME`_OUT_MODE                       (`$OutputConfiguration`u)
#define `$INSTANCE_NAME`_LOCAL_VREF_INPUT               (`$LocalVrefInput`u)

/******************************************************************************
* Functions
*******************************************************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Summary:
*  Turns off the LP Comparator.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  The function doesn't change component Speed settings.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    Cy_LPComp_SetInterruptTriggerMode(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, CY_LPCOMP_INTR_DISABLE);
    Cy_LPComp_SetPower(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, CY_LPCOMP_MODE_OFF);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UlpReferenceEnable
****************************************************************************//**
*
* Invokes the Cy_LPComp_UlpReferenceEnable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_UlpReferenceEnable(void)
{
    Cy_LPComp_UlpReferenceEnable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UlpReferenceDisable
****************************************************************************//**
*
* Invokes the Cy_LPComp_UlpReferenceDisable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_UlpReferenceDisable(void)
{
    Cy_LPComp_UlpReferenceDisable(`$INSTANCE_NAME`_HW);   
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
****************************************************************************//**
*
* Invokes the Cy_LPComp_GetCompare() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return (Cy_LPComp_GetCompare(`$INSTANCE_NAME`_HW, ((cy_en_lpcomp_channel_t)`$INSTANCE_NAME`_CHANNEL))); 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
****************************************************************************//**
*
* Invokes the Cy_LPComp_SetPower() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetPower(uint32 power)
{
    Cy_LPComp_SetPower(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, (cy_en_lpcomp_pwr_t)power);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetHysteresis
****************************************************************************//**
*
* Invokes the Cy_LPComp_SetHysteresis() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetHysteresis(uint32 hysteresis)
{
    Cy_LPComp_SetHysteresis(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, (cy_en_lpcomp_hyst_t) hysteresis); 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInputs
****************************************************************************//**
*
* Invokes the Cy_LPComp_SetInputs() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInputs(cy_en_lpcomp_inputs_t inputP, cy_en_lpcomp_inputs_t inputN)
{
    Cy_LPComp_SetInputs(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, inputP, inputN); 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOutputMode
****************************************************************************//**
*
* Invokes the Cy_LPComp_SetOutputMode() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetOutputMode(uint32 mode)
{
    Cy_LPComp_SetOutputMode(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, (cy_en_lpcomp_out_t)mode);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_LPComp_SetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterruptMask(uint32 interruptMask)
{
    Cy_LPComp_SetInterruptMask(`$INSTANCE_NAME`_HW, interruptMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
****************************************************************************//**
*
* Invokes the Cy_LPComp_GetInterruptMask() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (Cy_LPComp_GetInterruptMask(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatusMasked
****************************************************************************//**
*
* Invokes the Cy_LPComp_GetInterruptStatusMasked() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetInterruptStatusMasked(void)
{
    return (Cy_LPComp_GetInterruptStatusMasked(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptStatus
****************************************************************************//**
*
* Invokes the Cy_LPComp_GetInterruptStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32 `$INSTANCE_NAME`_GetInterruptStatus(void)
{
    return (Cy_LPComp_GetInterruptStatus(`$INSTANCE_NAME`_HW));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
****************************************************************************//**
*
* Invokes the Cy_LPComp_ClearInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask)
{
    Cy_LPComp_ClearInterrupt(`$INSTANCE_NAME`_HW, interruptMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
****************************************************************************//**
*
* Invokes the Cy_LPComp_SetInterrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask)
{
    Cy_LPComp_SetInterrupt(`$INSTANCE_NAME`_HW, interruptMask); 
}

#endif    /* CY_LPCOMP_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
