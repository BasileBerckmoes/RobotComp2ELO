/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_`$INSTANCE_NAME`_H)
#define CY_CLOCK_`$INSTANCE_NAME`_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void `$INSTANCE_NAME`_StartEx(uint32 alignClkDiv);
#define `$INSTANCE_NAME`_Start() \
    `$INSTANCE_NAME`_StartEx(`$INSTANCE_NAME`__PA_DIV_ID)

#else

void `$INSTANCE_NAME`_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void `$INSTANCE_NAME`_Stop(void);

void `$INSTANCE_NAME`_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 `$INSTANCE_NAME`_GetDividerRegister(void);
uint8  `$INSTANCE_NAME`_GetFractionalDividerRegister(void);

#define `$INSTANCE_NAME`_Enable()                         `$INSTANCE_NAME`_Start()
#define `$INSTANCE_NAME`_Disable()                        `$INSTANCE_NAME`_Stop()
#define `$INSTANCE_NAME`_SetDividerRegister(clkDivider, reset)  \
    `$INSTANCE_NAME`_SetFractionalDividerRegister((clkDivider), 0u)
#define `$INSTANCE_NAME`_SetDivider(clkDivider)           `$INSTANCE_NAME`_SetDividerRegister((clkDivider), 1u)
#define `$INSTANCE_NAME`_SetDividerValue(clkDivider)      `$INSTANCE_NAME`_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define `$INSTANCE_NAME`_DIV_ID     `$INSTANCE_NAME`__DIV_ID

#define `$INSTANCE_NAME`_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define `$INSTANCE_NAME`_CTRL_REG   (*(reg32 *)`$INSTANCE_NAME`__CTRL_REGISTER)
#define `$INSTANCE_NAME`_DIV_REG    (*(reg32 *)`$INSTANCE_NAME`__DIV_REGISTER)

#define `$INSTANCE_NAME`_CMD_DIV_SHIFT          (0u)
#define `$INSTANCE_NAME`_CMD_PA_DIV_SHIFT       (8u)
#define `$INSTANCE_NAME`_CMD_DISABLE_SHIFT      (30u)
#define `$INSTANCE_NAME`_CMD_ENABLE_SHIFT       (31u)

#define `$INSTANCE_NAME`_CMD_DISABLE_MASK       ((uint32)((uint32)1u << `$INSTANCE_NAME`_CMD_DISABLE_SHIFT))
#define `$INSTANCE_NAME`_CMD_ENABLE_MASK        ((uint32)((uint32)1u << `$INSTANCE_NAME`_CMD_ENABLE_SHIFT))

#define `$INSTANCE_NAME`_DIV_FRAC_MASK  (0x000000F8u)
#define `$INSTANCE_NAME`_DIV_FRAC_SHIFT (3u)
#define `$INSTANCE_NAME`_DIV_INT_MASK   (0xFFFFFF00u)
#define `$INSTANCE_NAME`_DIV_INT_SHIFT  (8u)

#else 

#define `$INSTANCE_NAME`_DIV_REG        (*(reg32 *)`$INSTANCE_NAME`__REGISTER)
#define `$INSTANCE_NAME`_ENABLE_REG     `$INSTANCE_NAME`_DIV_REG
#define `$INSTANCE_NAME`_DIV_FRAC_MASK  `$INSTANCE_NAME`__FRAC_MASK
#define `$INSTANCE_NAME`_DIV_FRAC_SHIFT (16u)
#define `$INSTANCE_NAME`_DIV_INT_MASK   `$INSTANCE_NAME`__DIVIDER_MASK
#define `$INSTANCE_NAME`_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
