/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides the source code to the API for the Programmable
*  Voltage Reference component.
*
* Note:
*  None
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
*  Initialize/Restore the default Voltage Reference configuration as defined
*  in the customizer. If the reference is set to Vdda, it will enable all
*  Vdda-based references.
*
* \sideeffect
*  If the reference is Vdda-based, the function will enable all Vdda-based
*  references because they share the same resistor tree.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    `$INSTANCE_NAME`_PRB_CTRL_REG |= `$INSTANCE_NAME`_PRB_CTRL_REG_INIT;
    `$INSTANCE_NAME`_PRB_REF_REG = `$INSTANCE_NAME`_PRB_REF_REG_INIT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
*  Enables the Voltage Reference.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_PRB_REF_REG |= `$INSTANCE_NAME`_VREF_ENABLE;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
*  Initializes all parameters required to setup the component as defined in the
*  customizer. If the reference is set to Vdda, it will enable all Vdda based
*  references.
*
* \globalvars
*  \ref `$INSTANCE_NAME`_initVar - This variable is used to indicate the initial
*  configuration of this component. The variable is initialized to zero and
*  set to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows
*  the component initialization without re-initialization in all subsequent
*  calls to the `$INSTANCE_NAME`_Start() routine.
*
* \sideeffect
*  If the reference is Vdda-based, the function will enable all Vdda-based
*  references because they share the same resistor tree.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    /* If not Initialized, then initialize all required hardware and software. */
    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_initVar = 1u;
        `$INSTANCE_NAME`_Init();
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
*  Disables the Voltage Reference.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_PRB_REF_REG &= ~`$INSTANCE_NAME`_VREF_ENABLE;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTap
****************************************************************************//**
*
*  Selects which of the equally spaced resistor divider taps will be used for
*  the reference. The output will range in 1/16th steps between Vref/16 to Vref.
*
*  \param
*  dividerTap:    One of the 16-tap voltage dividers to select a voltage
*                 between 1/16 of the reference source to the full reference
*                 source in steps of 1/16.
* * 1   :    1/16 Vref
* * ... :    ...
* * 16  :    Vref
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTap(uint32 dividerTap)
{
    `$INSTANCE_NAME`_PRB_REF_REG = (`$INSTANCE_NAME`_PRB_REF_REG & ~`$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK) |
        (((dividerTap - 1u) << `$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK_POS) & `$INSTANCE_NAME`_VREF_LEVEL_SEL_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetVRefSrc
****************************************************************************//**
*
*  Selects whether the reference at the top of the resistor divider is based
*  on the bandgap or Vdda.
*
*  \param
*  reference:    The reference source.
* * `$INSTANCE_NAME`_BANDGAP_REFERENCE :    Bandgap reference
* * `$INSTANCE_NAME`_VDDA_REFERENCE    :    Vdda reference
*
* \sideeffect
*  If the reference is based on Vdda, it will affect all Vdda-based references
*  because they share the same resistor tree.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetVRefSrc(uint32 reference)
{
    if (`$INSTANCE_NAME`_BANDGAP_REFERENCE == reference)
    {
        `$INSTANCE_NAME`_PRB_REF_REG &= ~`$INSTANCE_NAME`_VREF_SUPPLY_SEL;
    }
    else /* Vdda reference source */
    {
        `$INSTANCE_NAME`_PRB_CTRL_REG |= `$INSTANCE_NAME`_VDDA_ENABLE;
        `$INSTANCE_NAME`_PRB_REF_REG |= `$INSTANCE_NAME`_VREF_SUPPLY_SEL;
    }
}


/* [] END OF FILE */
