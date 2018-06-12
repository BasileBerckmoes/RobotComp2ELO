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

#include "gpio/fgpio.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define `$INSTANCE_NAME`_FGpioInitIn(v)             FGpio1pin_InitIn(F`=LookupFitterDefine($PortPinNum)`, FGpio1pin_InitPullup(v))
#define `$INSTANCE_NAME`_FGpioInitOut(v)            FGpio1pin_InitOut(F`=LookupFitterDefine($PortPinNum)`, FGpio1pin_InitVal(v))
#define `$INSTANCE_NAME`_FGpioGet()                 FGpio1pin_Get(F`=LookupFitterDefine($PortPinNum)`)
#define `$INSTANCE_NAME`_FGpioPut(v)                FGpio1pin_Put(F`=LookupFitterDefine($PortPinNum)`, (v))
#define `$INSTANCE_NAME`_FGpioEnableOutput()        FGpio_EnableOutput(`$INSTANCE_NAME`_FGPIO_GPIO_PORT_NUM, 1UL << `$INSTANCE_NAME`_FGPIO_GPIO_PIN_NUM)
#define `$INSTANCE_NAME`_FGpioDisableOutput()       FGpio_DisableOutput(`$INSTANCE_NAME`_FGPIO_GPIO_PORT_NUM)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
