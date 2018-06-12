/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Low Power Comparator
*  component.
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

#include "`$INSTANCE_NAME`.h"

/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME`  component
*  has been initialized. The variable is initialized to 0 and set to 1 the first
*  time `$INSTANCE_NAME`_Start() is called.
*  This allows the component to restart without reinitialization after the first 
*  call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  `$INSTANCE_NAME`_Init() function can be called before the 
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable() function.
*/
uint8_t `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_NOT_INITIALIZED;

/** The instance-specific configuration structure. This should be used in the 
*  associated `$INSTANCE_NAME`_Init() function.
*/
`=$CY_CONST_CONFIG ? "const" : ""` cy_stc_lpcomp_config_t `$INSTANCE_NAME`_config =
{
    (cy_en_lpcomp_out_t)`$INSTANCE_NAME`_OUT_MODE,
    (cy_en_lpcomp_hyst_t)`$INSTANCE_NAME`_HYSTERESIS,
    (cy_en_lpcomp_pwr_t)`$INSTANCE_NAME`_POWER,
    (cy_en_lpcomp_int_t)`$INSTANCE_NAME`_INTERRUPT
};

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  power to the block. The first time the routine is executed, the component is
*  initialized to the configuration from the customizer. When called to restart
*  the comparator following a `$INSTANCE_NAME`_Stop() call, the current
*  component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (`$INSTANCE_NAME`_NOT_INITIALIZED == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = `$INSTANCE_NAME`_INITIALIZED;
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Summary:
*  Initializes or restores the component according to the customizer settings.
*  It is not necessary to call `$INSTANCE_NAME`_Init() because the
*  `$INSTANCE_NAME`_Start() API calls this function and is the preferred method
*  to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    uint32_t interruptMask;
    
    (void)Cy_LPComp_Init(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL, &`$INSTANCE_NAME`_config);

    interruptMask = `$INSTANCE_NAME`_GetInterruptMask();
    `$INSTANCE_NAME`_SetInterruptMask(interruptMask | `$INSTANCE_NAME`_INTR_MASK);
    
    #if (0u != `$INSTANCE_NAME`_LOCAL_VREF_INPUT)
        Cy_LPComp_ConnectULPReference(`$INSTANCE_NAME`_HW, `$INSTANCE_NAME`_CHANNEL);
        Cy_LPComp_UlpReferenceEnable(`$INSTANCE_NAME`_HW);
    #endif 
}


/* [] END OF FILE */
