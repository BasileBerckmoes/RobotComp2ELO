/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of APIs for the DieTemp_P4 component.
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_Celsius
********************************************************************************
*
* Summary:
*  Converts the ADC output to degrees Celsius.
*
* Parameters:
*  int32 adcCounts:
*   Result from the ADC Conversion
*
* Return:
*  Temperature in degrees Celsius
*
* Global variables:
*  None
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_CountsTo_Celsius(int32 adcCounts)
{
    int32 tempCelsius;
    int32 tInitial;
    int32 tAdjust;
    int32 offsetReg;
    int32 multReg;

    offsetReg = (int16)`$INSTANCE_NAME`_SAR_TEMP_OFFSET_REG;
    multReg   = (int16)`$INSTANCE_NAME`_SAR_TEMP_MULTIPLIER_REG;
    /* Calculate tInitial in Q16.16 */
    tInitial = (adcCounts * multReg) + (offsetReg * `$INSTANCE_NAME`_SAR_TEMP_OFFSET_MULT);

    if(tInitial >= `$INSTANCE_NAME`_DUAL_SLOPE_CORRECTION)
    {
        /* Shift (100 - tInitial) by 4 bits to prevent scale-adjustment from overflowing. */
        /* Then divide by the integer bits of (100 - cutoff) to end up with a Q16.16 tAdjust */
        tAdjust = (`$INSTANCE_NAME`_SCALE_ADJUSTMENT * (((int32)`$INSTANCE_NAME`_HIGH_TEMPERATURE - tInitial)
            / (int32)`$INSTANCE_NAME`_SCALE_ADJUSTMENT_DIVIDER)) /
            (((int32)`$INSTANCE_NAME`_HIGH_TEMPERATURE - (int32)`$INSTANCE_NAME`_DUAL_SLOPE_CORRECTION) /
            `$INSTANCE_NAME`_SAR_TEMP_DIVIDER);
    }
    else
    {
        /* Shift (40 + tInitial) by 4 bits to prevent scale-adjustment from overflowing. */
        /* Then divide by the integer bits of (40 + cutoff) to end up with a Q16.16 tAdjust */
        tAdjust = ((int32)`$INSTANCE_NAME`_SCALE_ADJUSTMENT * (((int32)`$INSTANCE_NAME`_LOW_TEMPERATURE + tInitial)
           / (int32)`$INSTANCE_NAME`_SCALE_ADJUSTMENT_DIVIDER)) /
            (((int32)`$INSTANCE_NAME`_LOW_TEMPERATURE + (int32)`$INSTANCE_NAME`_DUAL_SLOPE_CORRECTION) /
            (int32)`$INSTANCE_NAME`_SAR_TEMP_DIVIDER);
    }

    /* Add tInitial + tAdjust + 0.5 to round to nearest int. Shift off frac bits, and return. */
    tempCelsius = tInitial + tAdjust + `$INSTANCE_NAME`_HALF_OF_ONE;

    return (tempCelsius / `$INSTANCE_NAME`_SAR_TEMP_OFFSET_DIVIDER);
}


/* [] END OF FILE */
