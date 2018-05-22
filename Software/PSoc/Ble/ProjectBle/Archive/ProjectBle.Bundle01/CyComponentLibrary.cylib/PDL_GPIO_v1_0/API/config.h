/*******************************************************************************
* \file `$INSTANCE_NAME`_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the macro function definitions for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_CONFIG_H
#define `$INSTANCE_NAME`_CONFIG_H

#include "gpio/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_GpioInitIn(v)      Gpio1pin_InitIn(`=LookupFitterDefine($PortPinNum)`, Gpio1pin_InitPullup(v))
#define `$INSTANCE_NAME`_GpioInitOut(v)     Gpio1pin_InitOut(`=LookupFitterDefine($PortPinNum)`, Gpio1pin_InitVal(v))
#define `$INSTANCE_NAME`_GpioGet()          Gpio1pin_Get(`=LookupFitterDefine($PortPinNum)`)
#define `$INSTANCE_NAME`_GpioPut(v)         Gpio1pin_Put(`=LookupFitterDefine($PortPinNum)`, (v))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
