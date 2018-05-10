/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the `$INSTANCE_NAME`
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_`$INSTANCE_NAME`_H)
#define CY_`$INSTANCE_NAME`_H

#include <cy_device_headers.h>
#include <ctb/cy_ctb.h>

/*******************************************************************************
                            Internal Constants
*******************************************************************************/
#define `$INSTANCE_NAME`_CTB_HW                         `=LookupFitterDefine("`$INSTANCE_NAME`_cy_mxs40_opamp__HW")`
#define `$INSTANCE_NAME`_OPAMP_NUM                      ((`$INSTANCE_NAME`_cy_mxs40_opamp__OA_IDX == 0u) \
                                                        ? CY_CTB_OPAMP_0 : CY_CTB_OPAMP_1)

/*******************************************************************************
                                  Parameters
The parameters that are set in the customizer are redefined as constants here.
*******************************************************************************/
#define `$INSTANCE_NAME`_PARAM_Power                    (`$Power`UL)
#define `$INSTANCE_NAME`_PARAM_OutputDrive              (`$OutputCurrent`UL)
#define `$INSTANCE_NAME`_PARAM_DeepSleep                (`$DeepSleepSupport`UL)

/*******************************************************************************
                    Variables with External Linkage
*******************************************************************************/

/** Tracks whether block is initialized (1) or not (0). */
extern uint8_t `$INSTANCE_NAME`_initVar;

/** Tracks the power level setting. Initialized to the power level setting in the customizer. */
extern cy_en_ctb_power_t `$INSTANCE_NAME`_opampPower;

/** Configuration structure for initializing one opamp using the CTB PDL. */
extern `=$CY_CONST_CONFIG ? "const " : ""`cy_stc_ctb_opamp_config_t `$INSTANCE_NAME`_opampConfig;


/*******************************************************************************
                        Opamp Configuration Defines
Constants used in the configuration structure for initializing the Opamp
*******************************************************************************/
#if (CYDEV_SYSTEM_AREF_CURRENT == CYDEV_SYSTEM_AREF_CURRENT_LOW)
    /* If the low reference current is used, disable the charge pump. */
    #define `$INSTANCE_NAME`_OPAMP_CHARGEPUMP           CY_CTB_PUMP_DISABLE
#else
    /* Charge pump configuration depends on Deep Sleep selection in the customizer. */
    #define `$INSTANCE_NAME`_OPAMP_CHARGEPUMP           `=$DeepSleepSupport == 0 ? "CY_CTB_PUMP_ENABLE" : "CY_CTB_PUMP_DISABLE"`
#endif
/*******************************************************************************
                        Function Prototypes
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Init(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void);
__STATIC_INLINE void `$INSTANCE_NAME`_SetPower(cy_en_ctb_power_t power);
__STATIC_INLINE void `$INSTANCE_NAME`_SetDeepSleepMode(cy_en_ctb_deep_sleep_t deepSleep);

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
****************************************************************************//**
*
* Initialize the component according to the customizer settings.
* This function can also be used to restore the customizer settings
* if they are changed at run time.
*
* It is not necessary to call `$INSTANCE_NAME`_Init() because
* `$INSTANCE_NAME`_Start() calls this function. `$INSTANCE_NAME`_Start() is the
* preferred method to begin component operation.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Init(void)
{
    (void) Cy_CTB_OpampInit(`$INSTANCE_NAME`_CTB_HW, `$INSTANCE_NAME`_OPAMP_NUM, &`$INSTANCE_NAME`_opampConfig);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Turn on the CTB and set the opamp power level based on last call to
* `$INSTANCE_NAME`_SetPower(). If `$INSTANCE_NAME`_SetPower() was never called,
* the power level set in the customizer is used.
*
* The other half of the CTB block is unaffected.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_CTB_Enable(`$INSTANCE_NAME`_CTB_HW);
    Cy_CTB_SetPower(`$INSTANCE_NAME`_CTB_HW, `$INSTANCE_NAME`_OPAMP_NUM, `$INSTANCE_NAME`_opampPower, `$INSTANCE_NAME`_OPAMP_CHARGEPUMP);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
* Turn off the opamp in the CTB block.
*
* The other half of the CTB block is unaffected.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    Cy_CTB_SetPower(`$INSTANCE_NAME`_CTB_HW, `$INSTANCE_NAME`_OPAMP_NUM, CY_CTB_POWER_OFF, `$INSTANCE_NAME`_OPAMP_CHARGEPUMP);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
****************************************************************************//**
*
* Set the power level for the opamp.
*
* \param power
* - CY_CTB_POWER_OFF: This input option does nothing. `$INSTANCE_NAME`_Stop()
*   is the preferred method to turn off the opamp.
* - CY_CTB_POWER_LOW: Low power level
* - CY_CTB_POWER_MEDIUM: Medium power level
* - CY_CTB_POWER_HIGH: High power level
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetPower(cy_en_ctb_power_t power)
{
    if (CY_CTB_POWER_OFF != power)
    {
        Cy_CTB_SetPower(`$INSTANCE_NAME`_CTB_HW, `$INSTANCE_NAME`_OPAMP_NUM, power, `$INSTANCE_NAME`_OPAMP_CHARGEPUMP);

        /* Update the tracking variable for the opamp power level */
        `$INSTANCE_NAME`_opampPower = power;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDeepSleepMode
****************************************************************************//**
*
* Set whether the entire CTB block continues to stay powered in Deep Sleep mode.
* This impacts both opamps in the CTB. If there are multiple instances of
* the Opamp component or other components that use the opamp resource
* (for example, Comparator or VDAC12 components), this will affect all instances.
*
* If `$INSTANCE_NAME`_Stop() is called before entering Deep Sleep mode,
* the opamp will remain off in Deep Sleep.
*
* Deep Sleep should not be enabled at run time if it was not enabled
* in the customizer. Analog routing and AREF block configuration are performed
* at build time. If Deep Sleep is not enabled in the customizer at build time
* the AREF block and the analog route may not be available during Deep Sleep.
*
* \param deepSleep
* - CY_CTB_DEEPSLEEP_DISABLE: Disable entire CTB is Deep Sleep mode
* - CY_CTB_DEEPSLEEP_ENABLE: Enable entire CTB in Deep Sleep mode
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SetDeepSleepMode(cy_en_ctb_deep_sleep_t deepSleep)
{
    Cy_CTB_SetDeepSleepMode(`$INSTANCE_NAME`_CTB_HW, deepSleep);
}

#endif /* !defined(CY_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
