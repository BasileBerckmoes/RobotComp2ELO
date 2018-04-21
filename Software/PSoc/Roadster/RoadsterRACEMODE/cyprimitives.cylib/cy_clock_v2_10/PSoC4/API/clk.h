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

void `$INSTANCE_NAME`_Start(void);
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

#define `$INSTANCE_NAME`_DIV_REG    (*(reg32 *)`$INSTANCE_NAME`__REGISTER)
#define `$INSTANCE_NAME`_ENABLE_REG `$INSTANCE_NAME`_DIV_REG

#endif /* !defined(CY_CLOCK_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
