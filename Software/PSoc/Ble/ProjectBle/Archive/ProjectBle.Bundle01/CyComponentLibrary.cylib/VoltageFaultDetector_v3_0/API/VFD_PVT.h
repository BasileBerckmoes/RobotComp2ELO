/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains global definitions for the component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VFD_PVT_`$INSTANCE_NAME`_H)
#define CY_VFD_PVT_`$INSTANCE_NAME`_H

#include "cytypes.h"


/***************************************
*       External Dependencies
***************************************/
    
/* AMux constant and variable definitions */
#define `$INSTANCE_NAME`_AMUX_INPUTS                32

/* Array storing addresses of AMUX ports */
extern uint8 CYXDATA * const CYCODE `$INSTANCE_NAME`_AMux__addrTable[`$INSTANCE_NAME`_AMUX_INPUTS];

/* Array storing masks for pins on AMUX ports */
extern const uint8 CYCODE `$INSTANCE_NAME`_AMux__maskTable[`$INSTANCE_NAME`_AMUX_INPUTS];


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* Number of inputs */
#define `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES         `$NumVoltages`u

/* Comparator types */
#define `$INSTANCE_NAME`_OV_UV                      0u
#define `$INSTANCE_NAME`_OV                         1u
#define `$INSTANCE_NAME`_UV                         2u
#define `$INSTANCE_NAME`_COMP_TYPE                  `$CompareType`u
#define `$INSTANCE_NAME`_ENABLE_OV_DETECT           (`$INSTANCE_NAME`_COMP_TYPE != `$INSTANCE_NAME`_UV)
#define `$INSTANCE_NAME`_ENABLE_UV_DETECT           (`$INSTANCE_NAME`_COMP_TYPE != `$INSTANCE_NAME`_OV)


/***************************************
*    Internal API Constants
***************************************/

/* Voltage reference */
#define `$INSTANCE_NAME`_VREF                       `$ExternalRef`u
#define `$INSTANCE_NAME`_INT_VREF                   (`$INSTANCE_NAME`_VREF == 0u)
#define `$INSTANCE_NAME`_EXT_VREF                   (!`$INSTANCE_NAME`_INT_VREF)

/* Vin settling delay */
#define `$INSTANCE_NAME`_VIN_SETTLING_DELAY         `$SettlingDelay`u
#define `$INSTANCE_NAME`_VIN_SETTLING_DELAY_MIN     3u

/* Common part of DMA configuration. Each burst requires request */
#define `$INSTANCE_NAME`_DMA_CFG(chan, size, src, dst)    `$INSTANCE_NAME`_##chan##_DmaInitialize((size), 1u, (src), (dst))
    
/* DAC max value is limited by DAC resolution */
#define `$INSTANCE_NAME`_DAC_MAX                    255u

/* DAC mV/LSb */
#define `$INSTANCE_NAME`_DAC_mV_LSb                 `$DACmVperLSb`u

/* Number of bits to shift right when dividing by DAC mV/LSb */
#define `$INSTANCE_NAME`_DAC_SHR_LSb                `$DACshiftsLSb`u

/* This is the fault threshold saturation for the VDAC.
* The upper limit must account for the VDAC max value of 255, VDAC mV per LSb,
* the input scaling factor of 1000.
*/
#define `$INSTANCE_NAME`_FAULT_THRESHOLD_SAT_H      (255UL * `$INSTANCE_NAME`_DAC_mV_LSb * 1000UL)

/* Constants to convert DAC voltage to DAC value. Refer to description
* of `$INSTANCE_NAME`_ConvertDacVoltageToValue() below for more information.
*/
#define `$INSTANCE_NAME`_DAC_VOLT2VAL_SHR           (`$INSTANCE_NAME`_DAC_SHR_LSb + 2u)
#define `$INSTANCE_NAME`_DAC_VOLT2VAL_ADD           125u
#define `$INSTANCE_NAME`_DAC_VOLT2VAL_DIV           250u


/***************************************
*   Internal Global Variables
***************************************/

/* Input voltage scaling factor. Indicates amount of attenuation applied
* to converter output voltage before connecting to PSoC.
*/
#if (`$INSTANCE_NAME`_INT_VREF)
extern const uint16 CYCODE `$INSTANCE_NAME`_VoltageScale[`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES];
#endif /* `$INSTANCE_NAME`_INT_VREF */


/***************************************
*   Macro helpers to simplify coding
***************************************/

/* The scaling factor is a real number in the range from 0.001 to 1.000 with 
*  step 0.001. To eliminate the float point arithmetic, the value entered in
*  the customizer is multiplied by 1000 before storing in memory. Thus the
*  scaled threshold is divided by 1000 to obtain the desired DAC voltage.
*
*       DAC voltage = threshold * scaling factor / 1000
*
*  Add 0.5 LSb so that fractions >= 0.5 LSb are rounded up.
*
*       DAC value = (DAC voltage + 0.5 LSb) / LSb
* 
*  DAC LSb is 4mV for 1V and 16mV for the 4V range. Substituting 1000 as 4 * 250
*  and replacing divisions by shifts right the equations are as follows.
*
*       1V: DAC value = (((threshold * scaling factor) >> 4) + 125) / 250
*       4V: DAC value = (((threshold * scaling factor) >> 6) + 125) / 250
*
*  These equations reduce the execution time significantly by replacing the 32-bit
*  division with a 32-bit shift right and a 16-bit division.
*/
#define `$INSTANCE_NAME`_ConvertDacVoltageToValue(voltage) \
    ((((uint16)((voltage) >> `$INSTANCE_NAME`_DAC_VOLT2VAL_SHR)) + `$INSTANCE_NAME`_DAC_VOLT2VAL_ADD) / `$INSTANCE_NAME`_DAC_VOLT2VAL_DIV)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define `$INSTANCE_NAME`_External_Reference     `$ExternalRef`u
#define `$INSTANCE_NAME`_CompareType            `$CompareType`u
#define `$INSTANCE_NAME`_DAC_VOL_DIVIDER        `$INSTANCE_NAME`_DAC_mV_LSb
#define `$INSTANCE_NAME`_Dac_Range              `$DacRange`u
#define `$INSTANCE_NAME`_OV_ONLY                `$INSTANCE_NAME`_OV
#define `$INSTANCE_NAME`_UV_ONLY                `$INSTANCE_NAME`_UV

#endif /* CY_VFD_PVT_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
