/*******************************************************************************
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the function prototypes and constants available to the TrimMargin
*  component.
*
********************************************************************************
* \copyright
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS       `$NumConverters`u
#define `$INSTANCE_NAME`_PWM_RESOLUTION             `$PWMResolution`u
#define `$INSTANCE_NAME`_PWM_IMPLEMENTATION         `$UseFF_PWM`u
#define `$INSTANCE_NAME`_CONTROLLER_TYPE            `$ControllerMethod`u
#define `$INSTANCE_NAME`_INCREMENTAL                0u
#define `$INSTANCE_NAME`_INTEGRAL                   1u


/***************************************
*      Data Struct Definition
***************************************/

/** \internal */
typedef struct
{
    uint8 above;        /* Cumulative ADC readings ABOVE rawMax     */
    uint8 below;        /* Cumulative ADC readings BELOW rawMin     */
} `$INSTANCE_NAME`_TRIMCTL_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

/** \addtogroup group_general
* @{ */
void   `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void   `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void   `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void   `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
`$DutyCycleType` `$INSTANCE_NAME`_ConvertVoltageToDutyCycle(uint8 converterNum, uint16 desiredVoltage) `=ReentrantKeil($INSTANCE_NAME . "_ConvertVoltageToDutyCycle")`;
`$DutyCycleType` `$INSTANCE_NAME`_ConvertVoltageToPreRunDutyCycle(uint8 converterNum, uint16 desiredVoltage) `=ReentrantKeil($INSTANCE_NAME . "_ConvertVoltageToPreRunDutyCycle")`;
void   `$INSTANCE_NAME`_SetMarginHighVoltage(uint8 converterNum, uint16 marginHiVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetMarginHighVoltage")`;
uint16 `$INSTANCE_NAME`_GetMarginHighVoltage(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetMarginHighVoltage")`;
void   `$INSTANCE_NAME`_SetMarginLowVoltage(uint8 converterNum, uint16 marginLoVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetMarginLowVoltage")`;
uint16 `$INSTANCE_NAME`_GetMarginLowVoltage(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetMarginLowVoltage")`;
void   `$INSTANCE_NAME`_SetNominalVoltage(uint8 converterNum, uint16 nominalVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetNominalVoltage")`;
uint16 `$INSTANCE_NAME`_GetNominalVoltage(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetNominalVoltage")`;
void   `$INSTANCE_NAME`_ActiveTrim(uint8 converterNum, uint16 actualVoltage, uint16 desiredVoltage) `=ReentrantKeil($INSTANCE_NAME . "_ActiveTrim")`;
void   `$INSTANCE_NAME`_SetDutyCycle(uint8 converterNum, `$DutyCycleType` dutyCycle) `=ReentrantKeil($INSTANCE_NAME . "_SetDutyCycle")`;
`$DutyCycleType` `$INSTANCE_NAME`_GetDutyCycle(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetDutyCycle")`;
`$ConverterMaskType` `$INSTANCE_NAME`_GetAlertSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertSource")`;
/** @} general */

/***************************************
*   Variables with external linkage
***************************************/

/** \addtogroup group_globals
@{ */
extern         uint8         `$INSTANCE_NAME`_initVar;

extern  const  uint16 CYCODE `$INSTANCE_NAME`_VMARGIN_LOW[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         uint16        `$INSTANCE_NAME`_vMarginLow[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  uint16 CYCODE `$INSTANCE_NAME`_VMARGIN_HIGH[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         uint16        `$INSTANCE_NAME`_vMarginHigh[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  uint16 CYCODE `$INSTANCE_NAME`_VNOMINAL[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         uint16        `$INSTANCE_NAME`_vNom[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

extern  const  `$DutyCycleType` CYCODE `$INSTANCE_NAME`_VMARGIN_LOW_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         `$DutyCycleType`        `$INSTANCE_NAME`_vMarginLowDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  `$DutyCycleType` CYCODE `$INSTANCE_NAME`_VMARGIN_HIGH_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         `$DutyCycleType`        `$INSTANCE_NAME`_vMarginHighDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  `$DutyCycleType` CYCODE `$INSTANCE_NAME`_VNOMINAL_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         `$DutyCycleType`        `$INSTANCE_NAME`_vNominalDutyCycle[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  `$DutyCycleType` CYCODE `$INSTANCE_NAME`_PRE_RUN_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  `$DutyCycleType` CYCODE `$INSTANCE_NAME`_STARTUP_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  `$DutyCycleType` CYCODE `$INSTANCE_NAME`_STARTUP_PRE_RUN_DUTYCYCLE[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

extern  const  uint16 CYCODE `$INSTANCE_NAME`_VMAX[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern  const  uint16 CYCODE `$INSTANCE_NAME`_VMIN[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/** @} globals */

/** \internal */
extern         `$ConverterMaskType`        `$INSTANCE_NAME`_alertSource;
extern         uint8         `$INSTANCE_NAME`_trimCycleCount;

extern  const  uint16 CYCODE `$INSTANCE_NAME`_PRE_COEF[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#if (`$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL)
extern  const  uint16 CYCODE `$INSTANCE_NAME`_VDELTA[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern         `$INSTANCE_NAME`_TRIMCTL_STRUCT `$INSTANCE_NAME`_trimCtl[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_CONTROLLER_TYPE == `$INSTANCE_NAME`_INCREMENTAL */

                                    
/***************************************
*          API Constants
***************************************/

/** \addtogroup group_constants
* @{ */
#define `$INSTANCE_NAME`_MAX_NUMBER_OF_CONVERTERS   24u
#define `$INSTANCE_NAME`_PWM_MIN                    0u
#define `$INSTANCE_NAME`_PWM_MAX                    (0xFFFFu >> (16u - `$INSTANCE_NAME`_PWM_RESOLUTION))

/**
* \addtogroup trim_cycle Trim cycle count
* \brief Cycle count constants for the `$INSTANCE_NAME`_SetTrimCycleCount()
*  function. 
*
* This slows-down the trim process, so that it compensates the initial and
* long-term regulator drift and associated component drift.  This should be
* long enough to avoid interacting with the regulator's high-speed transient
* response to dynamic changes in Vin and Iout.
*
* @{
*/
#define `$INSTANCE_NAME`_CYCLE_SLOW             20u
#define `$INSTANCE_NAME`_CYCLE_MEDIUM           15u
#define `$INSTANCE_NAME`_CYCLE_FAST             10u

/** @} trim_cycle */

/** @} constants */

/* If a rail is noisy, the quantity of both ABOVE and BELOW measurements have
* similar magnitude and neither will "dominate" (i.e. exceed MIN_DELTA), so no
* adjustment would made.
* A 25% (1/4) majority is a reasonable decisive majority.
*/
#define `$INSTANCE_NAME`_TRIM_MIN_DELTA_FACTOR      2u
#define `$INSTANCE_NAME`_MIN_DELTA                  (`$INSTANCE_NAME`_trimCycleCount >> `$INSTANCE_NAME`_TRIM_MIN_DELTA_FACTOR)

/* Specifies the polarity of the voltage adjust feedback input from the power
* converter. This will decide if increasing the PWM duty cycle will increase
* (positive polarity) or decrease (negative polarity) the converter output
* voltage.
*/
#define `$INSTANCE_NAME`_FEEDBACK                   `$FeedbackValue`
#define `$INSTANCE_NAME`_POLARITY_POSITIVE          0u
#define `$INSTANCE_NAME`_POLARITY_NEGATIVE          1u

/* Determines the PWM implementation */
#define `$INSTANCE_NAME`_UDB_PWM                    (`$INSTANCE_NAME`_PWM_IMPLEMENTATION == 0u)
#define `$INSTANCE_NAME`_FF_PWM                     (!`$INSTANCE_NAME`_UDB_PWM)

#define `$INSTANCE_NAME`_FALSE                      0u
#define `$INSTANCE_NAME`_TRUE                       1u

/* Determine if the alert terminal is present in a design */
#ifdef `$INSTANCE_NAME`_Control_En_Reg_Sync_ctrl_reg__CONTROL_REG
#define `$INSTANCE_NAME`_ALERT_PRESENT              1u
#endif /* `$INSTANCE_NAME`_Control_En_Reg_Sync_ctrl_reg__CONTROL_REG */

/** \addtogroup group_general
* @{ */

/*******************************************************************************
* Macro: `$INSTANCE_NAME`_MarginLow
****************************************************************************//**
*
* \brief
*  Sets the selected power converter output voltage to the desired margin low
*  setting as specified in the customizer or by calling 
*  `$INSTANCE_NAME`_SetMarginLowVoltage() API.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_MarginLow(n)  `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_vMarginLowDutyCycle[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_MarginHigh
****************************************************************************//**
*
* \brief
*  Sets the selected power converter output voltage to the desired margin high
*  setting as specified in the customizer or by calling 
*  `$INSTANCE_NAME`_SetMarginHighVoltage() API.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_MarginHigh(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_vMarginHighDutyCycle[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_Nominal
****************************************************************************//**
*
* \brief
*  Sets the selected power converter output voltage to the nominal voltage
*  setting as specified in the customizer or by calling 
*  `$INSTANCE_NAME`_SetNominalVoltage() API.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Nominal(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_vNominalDutyCycle[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_PreRun
****************************************************************************//**
*
* \brief
*  Sets the pre-charge PWM duty cycle required to achieve the nominal voltage
*  before the power converter is enabled with the assumption that R1 is
*  grounded in parallel with R2.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_PreRun(n)  `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_PRE_RUN_DUTYCYCLE[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_Startup
****************************************************************************//**
*
* \brief
*  Sets the selected power converter output voltage to the startup voltage
*  setting as specified in the Voltages Tab of the customizer.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Startup(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_STARTUP_DUTYCYCLE[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_StartupPreRun
****************************************************************************//**
*
* \brief
*  Sets the pre-charge PWM duty cycle required to achieve the Startup Voltage
*  before the power converter is enabled with the assumption that R1 is
*  grounded in parallel with R2.
*
* \param converterNum
*  Specifies the power converter number. Valid range: 1..24.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_StartupPreRun(n) `$INSTANCE_NAME`_SetDutyCycle(n, `$INSTANCE_NAME`_STARTUP_PRE_RUN_DUTYCYCLE[(n) - 1u])


/*******************************************************************************
* Macro: `$INSTANCE_NAME`_SetTrimCycleCount
****************************************************************************//**
*
* \brief
*  Sets the internal adjustment cycle count that affects how often the PWM duty
*  cycle is updated when calling `$INSTANCE_NAME`_ActiveTrim() API. The default
*  value is `$INSTANCE_NAME`_CYCLE_SLOW.
*
* \param count
*   Specifies the cycle count value. See the \ref trim_cycle constants for
*   the valid values.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_SetTrimCycleCount(count)       (`$INSTANCE_NAME`_trimCycleCount = (count))

/** @} general */

/***************************************
*           Registers
***************************************/

#define `$INSTANCE_NAME`_CTRL_REG                   (* (reg8 *)`$INSTANCE_NAME`_Control_En_Reg_Sync_ctrl_reg__CONTROL_REG)


/***************************************
*       Register Constants
***************************************/

/* Control Enable Register Bit Masks */
#define `$INSTANCE_NAME`_CTRL_ENABLE                (0x01u)
#define `$INSTANCE_NAME`_CTRL_ALERT                 (0x02u)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/** \addtogroup group_deprecated
* @{ */
#define `$INSTANCE_NAME`_SetNominal(n)              `$INSTANCE_NAME`_Nominal(n)  
#define `$INSTANCE_NAME`_SetPreRun(n)               `$INSTANCE_NAME`_PreRun(n)
#define `$INSTANCE_NAME`_SetStartup(n)              `$INSTANCE_NAME`_Startup(n)
#define `$INSTANCE_NAME`_SetStartupPreRun(n)        `$INSTANCE_NAME`_StartupPreRun(n)
#define `$INSTANCE_NAME`_DUTYCYCLE                  `$INSTANCE_NAME`_VNOMINAL_DUTYCYCLE
#define `$INSTANCE_NAME`_TRIM_SLOW_PERIOD           `$INSTANCE_NAME`_CYCLE_SLOW
/** @} deprecated */

#endif  /* `$INSTANCE_NAME`_H */


/* [] END OF FILE */
