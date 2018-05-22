/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the RTDCalc Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if(!CY_PSOC3)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_MultShift24
    ********************************************************************************
    *
    * Summary:
    *  Performs the math function (op1 * op2) >> 24 using 64 bit arithmetic without
    *  any loss of precision and without overflow.
    *
    * Parameters:
    *  op1: Signed 32-bit operand
    *  op2: Unsigned 24-bit operand
    *
    * Return:
    *  Signed 32-bit result of the math calculation
    *
    *******************************************************************************/
    int32 `$INSTANCE_NAME`_MultShift24(int32 op1, uint32 op2) `=ReentrantKeil($INSTANCE_NAME . "_MultShift24")`
    {
        int64 result=0;

        result = (int64)op1 * (int64)op2;
        
        if (result < 0)
        {
            result = -result;
            result = (int32)((uint32)((uint64)result >> `$INSTANCE_NAME`_24BIT_SHIFTING));
            result = -result;
        }
        else
        {
            result = (int32)((uint32)((uint64)result >> `$INSTANCE_NAME`_24BIT_SHIFTING));
        }
        return (result);
    }
#endif /* End (!CY_PSOC3) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTemperature
********************************************************************************
*
* Summary:
*  Calculates the temperature from RTD resistance.
*
* Parameters:
*  res: Resistance in milliohms.
*
* Return:
*  Temperature in 1/100ths degrees C.
*
*******************************************************************************/
int32 `$INSTANCE_NAME`_GetTemperature(uint32 res) `=ReentrantKeil($INSTANCE_NAME . "_GetTemperature")`

#if (CY_PSOC3)
{

    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    `$GenCoefficients`

    uint8 i=0u;
    float32 resNorm=0.0f;
    float32 temp=0.0f;

    resNorm = (float32)res;

    if (((`$INSTANCE_NAME`_RTD_TYPE == (uint32)`$INSTANCE_NAME`__PT100) && (res > `$INSTANCE_NAME`_ZERO_VAL_PT100)) ||
        ((`$INSTANCE_NAME`_RTD_TYPE == (uint32)`$INSTANCE_NAME`__PT500) && (res > `$INSTANCE_NAME`_ZERO_VAL_PT500)) ||
        ((`$INSTANCE_NAME`_RTD_TYPE == (uint32)`$INSTANCE_NAME`__PT1000) && (res > `$INSTANCE_NAME`_ZERO_VAL_PT1000)))
    {
         /* Temperature above 0 degrees C */
        for (i = `$INSTANCE_NAME`_ORDER_POS - 1u; i > 0u; i--)
        {
            temp = (`$INSTANCE_NAME`_coeffPos[i] + temp) * resNorm;
        }
        temp = temp + `$INSTANCE_NAME`_coeffPos[`$INSTANCE_NAME`_FIRST_EL_MAS];
    }
    else
    {
        /* Temperature below 0 degrees C */
        for (i = `$INSTANCE_NAME`_ORDER_NEG - 1u; i > 0u; i--)
        {
            temp = (`$INSTANCE_NAME`_coeffNeg[i] + temp) * resNorm;
        }
        temp = temp + `$INSTANCE_NAME`_coeffNeg[`$INSTANCE_NAME`_FIRST_EL_MAS];
    }
    return ((int32)(temp));
}
#else
{
    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    `$GenCoefficients`

    uint8 i;
    int32 temp=0;

    if (((`$INSTANCE_NAME`_RTD_TYPE == (uint32)`$INSTANCE_NAME`__PT100) && (res > `$INSTANCE_NAME`_ZERO_VAL_PT100)) ||
        ((`$INSTANCE_NAME`_RTD_TYPE == (uint32)`$INSTANCE_NAME`__PT500) && (res > `$INSTANCE_NAME`_ZERO_VAL_PT500)) ||
        ((`$INSTANCE_NAME`_RTD_TYPE == (uint32)`$INSTANCE_NAME`__PT1000) && (res > `$INSTANCE_NAME`_ZERO_VAL_PT1000)))
    {
         /* Temperature above 0 degrees C */
        res = res << (`$INSTANCE_NAME`_IN_NORMALIZATION - `$INSTANCE_NAME`_POS_INPUT_SCALE);

        for (i = `$INSTANCE_NAME`_ORDER_POS - 1u; i > 0u; i--)
        {
            temp = `$INSTANCE_NAME`_MultShift24((`$INSTANCE_NAME`_coeffPos[i] + temp), res);
        }
        temp = (int32)((uint32)((uint64)(int32)(temp + `$INSTANCE_NAME`_coeffPos[`$INSTANCE_NAME`_FIRST_EL_MAS]) >> 
                       `$INSTANCE_NAME`_POS_COEFF_SCALE));
    }

    else
    {
        /* Temperature below 0 degrees C */
        res = res << (`$INSTANCE_NAME`_IN_NORMALIZATION - `$INSTANCE_NAME`_NEG_INPUT_SCALE);

        for (i = `$INSTANCE_NAME`_ORDER_NEG - 1u; i > 0u; i--)
        {
            temp = `$INSTANCE_NAME`_MultShift24((`$INSTANCE_NAME`_coeffNeg[i] + temp), res);
        }

        temp = (int32)((uint32)((uint64)(int32)(temp + `$INSTANCE_NAME`_coeffNeg[`$INSTANCE_NAME`_FIRST_EL_MAS]) >> 
                       `$INSTANCE_NAME`_NEG_COEFF_SCALE));
    }
    return (temp);
}
#endif /* End PSoC3 */

/* [] END OF FILE */
