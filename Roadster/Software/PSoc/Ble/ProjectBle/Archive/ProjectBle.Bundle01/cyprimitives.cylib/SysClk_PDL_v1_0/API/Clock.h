/***************************************************************************//**
* \file     `$INSTANCE_NAME`.h
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* Provides the source code to the API for the `$INSTANCE_NAME` Component.
*
********************************************************************************
* \copyright
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_`$INSTANCE_NAME`_NAME_`$INSTANCE_NAME`_H)
#define CY_`$INSTANCE_NAME`_NAME_`$INSTANCE_NAME`_H

/* For _DIV_TYPE and _DIV_NUM #defines */
#include "cyfitter.h"

/* makes uint32_t defined */
#include <stdint.h>

#include "sysclk/cy_sysclk.h"

/***************************************
* Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The peripheral clock divider number */
#define `$INSTANCE_NAME`_DIV_NUM ((uint32_t)`$INSTANCE_NAME`__DIV_NUM)
/** The peripheral clock divider type */
#define `$INSTANCE_NAME`_DIV_TYPE ((cy_en_divider_types_t)`$INSTANCE_NAME`__DIV_TYPE)
/** @} group_macros */

/***************************************
* Function Prototypes
***************************************/

/**
* \addtogroup group_general
* @{
*/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Enables the programmable clock divider assigned to this Component.
*
* \param None
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    (void)Cy_SysClk_PeriphEnableDivider(`$INSTANCE_NAME`_DIV_TYPE, `$INSTANCE_NAME`_DIV_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Disables the programmable clock divider assigned to this Component.
*
* \param None
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    (void)Cy_SysClk_PeriphDisableDivider(`$INSTANCE_NAME`_DIV_TYPE, `$INSTANCE_NAME`_DIV_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDivider
****************************************************************************//**
*
* Sets the value of a programmable clock divider assigned to this Component.
* This is only used for integer dividers. Use `$INSTANCE_NAME`_SetFracDivider()
* for setting factional dividers.
*
* \param dividerValue
* The divider value. The source of the divider is peri_clk which is a divided
* version of hf_clk[0]. The divider value causes integer division of
* (divider value + 1), or division by 1 to 256 (8-bit divider) or
* 1 to 65536 (16-bit divider).
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetDivider(uint32_t dividerValue)
{
    (void)Cy_SysClk_PeriphSetDivider(`$INSTANCE_NAME`_DIV_TYPE, `$INSTANCE_NAME`_DIV_NUM, dividerValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDivider
****************************************************************************//**
*
* Returns the integer divider value for the programmable clock divider assigned
* to this Component. This is only used for integer dividers.
* Use `$INSTANCE_NAME`_GetFracDivider() with a fractional divider.
*
* \param None
*
* \return
* The divider value. The source of the divider is peri_clk which is a divided
* version of hf_clk[0]. The integer division done is by (divider value + 1),
* or division by 1 to 256 (8-bit divider) or 1 to 65536 (16-bit divider).
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetDivider(void)
{
    return Cy_SysClk_PeriphGetDivider(`$INSTANCE_NAME`_DIV_TYPE, `$INSTANCE_NAME`_DIV_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFracDivider
****************************************************************************//**
*
* Sets the values of a programmable clock divider assigned to this Component.
* This is only used for fractional dividers. Use `$INSTANCE_NAME`_SetDivider()
* for setting integer dividers.
*
* \param dividerIntValue
* The integer divider value. The source of the divider is peri_clk which is a
* divided version of hf_clk[0]. The divider value causes integer division of
* (divider value + 1), or division by 1 to 65536 (16-bit divider) or
* 1 to 16777216 (24-bit divider).
*
* \param dividerFracValue
* This is the fraction piece of the divider. The fractional divider can be
* 0 - 31; it divides the clock by 1/32 for each count. To divide the clock by
* 11/32nds, set this value to 11.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetFracDivider(uint32_t dividerIntValue, uint32_t dividerFracValue)
{
    (void)Cy_SysClk_PeriphSetFracDivider(`$INSTANCE_NAME`_DIV_TYPE, `$INSTANCE_NAME`_DIV_NUM, dividerIntValue, dividerFracValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFracDivider
****************************************************************************//**
*
* Returns the divider values for the programmable clock divider assigned to this
* Component. This is only used for fractional dividers.
* Use `$INSTANCE_NAME`_GetDivider() with an integer divider.
*
* \param *dividerIntValue
* pointer to return integer divider value
*
* \param *dividerFracValue
* pointer to return fractional divider value
*
* \return None. Loads pointed-to variables.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_GetFracDivider(uint32_t *dividerIntValue, uint32_t *dividerFracValue)
{
    Cy_SysClk_PeriphGetFracDivider(`$INSTANCE_NAME`_DIV_TYPE, `$INSTANCE_NAME`_DIV_NUM, dividerIntValue, dividerFracValue);
}

/** @} general */

#endif /* CY_CLOCK_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
