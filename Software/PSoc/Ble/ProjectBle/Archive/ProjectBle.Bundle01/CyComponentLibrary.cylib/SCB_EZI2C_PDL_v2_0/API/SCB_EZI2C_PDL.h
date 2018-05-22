/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides constants and parameter values for the EZI2C component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_SCB_EZI2C_PDL_H)
#define `$INSTANCE_NAME`_CY_SCB_EZI2C_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_ezi2c.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_ENABLE_SECOND_ADDR  (`$NumOfAddr`U)


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
__STATIC_INLINE cy_en_scb_ezi2c_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_ezi2c_config_t const *config);
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit (void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable (void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);

__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetActivity(void);

/* Configuration functions for address 1 */
__STATIC_INLINE void     `$INSTANCE_NAME`_SetAddress1(uint8_t addr);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetAddress1(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetBuffer1(uint8_t* buffer, uint32_t size, uint32_t rwBoundary);

#if (`$INSTANCE_NAME`_ENABLE_SECOND_ADDR)
/* Configuration functions for address 2 */
__STATIC_INLINE void     `$INSTANCE_NAME`_SetAddress2(uint8_t addr);
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetAddress2(void);
__STATIC_INLINE void     `$INSTANCE_NAME`_SetBuffer2(uint8_t* buffer, uint32_t size, uint32_t rwBoundary);
#endif /* (`$INSTANCE_NAME`_ENABLE_SECOND_ADDR) */

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
extern cy_stc_scb_ezi2c_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config;
extern cy_stc_scb_ezi2c_context_t `$INSTANCE_NAME`_context;
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
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_ezi2c_status_t `$INSTANCE_NAME`_Init(cy_stc_scb_ezi2c_config_t const *config)
{
    return Cy_SCB_EZI2C_Init(`$INSTANCE_NAME`_HW, config, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
*  Function Name: `$INSTANCE_NAME`_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_DeInit(void)
{
    Cy_SCB_EZI2C_DeInit(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_SCB_EZI2C_Enable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_SCB_EZI2C_Disable(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetActivity
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_GetActivity() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetActivity(void)
{
    return Cy_SCB_EZI2C_GetActivity(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAddress1
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_SetAddress1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetAddress1(uint8_t addr)
{
    Cy_SCB_EZI2C_SetAddress1(`$INSTANCE_NAME`_HW, addr, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAddress1
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_GetAddress1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetAddress1(void)
{
    return Cy_SCB_EZI2C_GetAddress1(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBuffer1
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_SetBuffer1() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetBuffer1(uint8_t* buffer, uint32_t size, uint32_t rwBoundary)
{
    Cy_SCB_EZI2C_SetBuffer1(`$INSTANCE_NAME`_HW, buffer, size, rwBoundary, &`$INSTANCE_NAME`_context);
}


#if (`$INSTANCE_NAME`_ENABLE_SECOND_ADDR)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAddress2
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_SlaveGetAddress2() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetAddress2(uint8_t addr)
{
    Cy_SCB_EZI2C_SetAddress2(`$INSTANCE_NAME`_HW, addr, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAddress2
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_SlaveGetAddress2() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetAddress2(void)
{
    return Cy_SCB_EZI2C_GetAddress2(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBuffer2
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_SetBuffer2() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetBuffer2(uint8_t* buffer, uint32_t size, uint32_t rwBoundary)
{
    Cy_SCB_EZI2C_SetBuffer2(`$INSTANCE_NAME`_HW, buffer, size, rwBoundary, &`$INSTANCE_NAME`_context);
}
#endif /* (`$INSTANCE_NAME`_ENABLE_SECOND_ADDR) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_EZI2C_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void)
{
    Cy_SCB_EZI2C_Interrupt(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* `$INSTANCE_NAME`_CY_SCB_EZI2C_PDL_H */


/* [] END OF FILE */
