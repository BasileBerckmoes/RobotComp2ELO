/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the Interrupt Service Routines implementation for
*  Fan Controller component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    volatile uint16 `$INSTANCE_NAME`_speedStatus = 0u;
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */


#if(CY_PSOC4)
    /********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for transferring actual speed from tachometer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    * Theory:
    *  This interrupt, when its used, should have highest priority to guarantee
    *  proper data transferring. The subject of concern is value of tachometer
    *  fan counter that should be read within 48 cycles (for 24 MHz master clock)
    *  after interrupt was triggered.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_DATA_SEND_ISR)
    {
        uint8 fanNum;
        uint16 actSpeed;

        #ifdef `$INSTANCE_NAME`_DATA_SEND_ISR_ENTRY_CALLBACK
            `$INSTANCE_NAME`_DATA_SEND_ISR_EntryCallback();
        #endif /* `$INSTANCE_NAME`_DATA_SEND_ISR_ENTRY_CALLBACK */
        
        /* Get the number of active fan */
        fanNum = `$INSTANCE_NAME`_TACH_FAN_COUNTER_REG;

        /* Get measured actual speed period for a specific fan */
        actSpeed = CY_GET_REG16(`$INSTANCE_NAME`_TACH_ACTUAL_PERIOD_PTR);

        /* Apply mask to Count value to remove unnecesary TC bit */
        fanNum &= `$INSTANCE_NAME`_COUNT7_PERIOD_MASK;
        
        /* Put down the measured speed to the proper location in RAM */
        `$INSTANCE_NAME`_fanControl.actualPeriod[fanNum] = actSpeed;

        /* In case if the last fan in the sequence was measured it is required
        * to generate the "eoc" pulse from Global Control Register.
        */
        if(0u == fanNum)
        {
            `$INSTANCE_NAME`_GLOBAL_CONTROL_REG |= `$INSTANCE_NAME`_SW_EOC;
        }

        #ifdef `$INSTANCE_NAME`_DATA_SEND_ISR_EXIT_CALLBACK
            `$INSTANCE_NAME`_DATA_SEND_ISR_ExitCallback();
        #endif /* `$INSTANCE_NAME`_DATA_SEND_ISR_EXIT_CALLBACK */
    }
#endif /* (CY_PSOC4) */


#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    /*******************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for implementation of PID Firmware Controlling
    *  algorithm.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    * Theory:
    *  PID interrupt occurs in constant periods of time that is configured through
    *  the component customizer.
    *
    *******************************************************************************/
    CY_ISR(`$INSTANCE_NAME`_PID_CONTROL_ISR)
    {
        uint8 i;
        int16 pidErrorZ0;
        uint32 newCompare;
        int16 periodError;
        uint32 currActSpeed;
        uint32 tmpCompare;
        uint16 mask;

        /***************************************
        *   PID Parameters
        ***************************************/
        /* The error history */
        static int16 `$INSTANCE_NAME`_pidErrorZ1[`$INSTANCE_NAME`_NUMBER_OF_FANS] = {0};
        static int16 `$INSTANCE_NAME`_pidErrorZ2[`$INSTANCE_NAME`_NUMBER_OF_FANS] = {0};

        /* The compensator integrator */
        static uint32 `$INSTANCE_NAME`_pidArea[`$INSTANCE_NAME`_NUMBER_OF_FANS] = {0u};

        /* Holds result of PID algorithm execution for currently active fan */
        static uint16 `$INSTANCE_NAME`_pidOut;

        /* Fans speed regulation counters */
        static uint8 `$INSTANCE_NAME`_spdErrCount[`$INSTANCE_NAME`_NUMBER_OF_FANS] = {0u};

        #ifdef `$INSTANCE_NAME`_PID_CONTROL_ISR_ENTRY_CALLBACK
            `$INSTANCE_NAME`_PID_CONTROL_ISR_EntryCallback();
        #endif /* `$INSTANCE_NAME`_PID_CONTROL_ISR_ENTRY_CALLBACK */
        
        for(i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_FANS; i++)
        {
            /* Calculate the error in number of cycles of tachometer clock */
            #if(CY_PSOC3)
                if(0u != (`$INSTANCE_NAME`_DMA_STATUS_REG & `$INSTANCE_NAME`_DMA1))
                {
                    /* If DMA writes to actualPeriodDma1 (DMA1 state) then read actualPeriodDma2. */
                    currActSpeed =
                        (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR / `$INSTANCE_NAME`_fanControl.actualPeriodDma2[i]);
                }
                else
                {
                    /* If DMA writes to actualPeriodDma2 (DMA2 state) then read actualPeriodDma1. */
                    currActSpeed =
                        (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR / `$INSTANCE_NAME`_fanControl.actualPeriodDma1[i]);
                }
            #else
               currActSpeed =
                    (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR / (uint32)`$INSTANCE_NAME`_fanControl.actualPeriod[i]);
            #endif /* (CY_PSOC3) */

            periodError = (int16) ((int32) `$INSTANCE_NAME`_desiredFansSpeed[i] - (int32) currActSpeed);

            /* The error in RPM */
            pidErrorZ0 = periodError;

            /* Saturate... Limit the error within the design range of the compensator */
            if(`$INSTANCE_NAME`_PID_ERROR_SAT_L > pidErrorZ0)
            {
                pidErrorZ0 = `$INSTANCE_NAME`_PID_ERROR_SAT_L;
            }
            else if(`$INSTANCE_NAME`_PID_ERROR_SAT_H < pidErrorZ0)
            {
                pidErrorZ0 = `$INSTANCE_NAME`_PID_ERROR_SAT_H;
            }
            else
            {
                /* Do nothing, the error is in range */
            }

            /* Process PID compensation */
            `$INSTANCE_NAME`_pidArea[i] = (uint32) ((int32) `$INSTANCE_NAME`_pidArea[i] +
                                            ((int32) pidErrorZ0 * (int32) `$INSTANCE_NAME`_pidA1[i]));
            `$INSTANCE_NAME`_pidArea[i] = (uint32) ((int32) `$INSTANCE_NAME`_pidArea[i] +
                                            ((int32) `$INSTANCE_NAME`_pidErrorZ1[i] *
                                            (int32) `$INSTANCE_NAME`_pidA2[i]));
            `$INSTANCE_NAME`_pidArea[i] = (uint32) ((int32) `$INSTANCE_NAME`_pidArea[i] +
                                            ((int32) `$INSTANCE_NAME`_pidErrorZ2[i] *
                                            (int32) `$INSTANCE_NAME`_pidA3[i]));

            /* Save error history */
            `$INSTANCE_NAME`_pidErrorZ2[i] = `$INSTANCE_NAME`_pidErrorZ1[i];
            `$INSTANCE_NAME`_pidErrorZ1[i] = pidErrorZ0;

            /* Saturate... Limit the error within the design range of the compensator */
            if(((int32) `$INSTANCE_NAME`_outputSatL[i]) > ((int32) `$INSTANCE_NAME`_pidArea[i]))
            {
                `$INSTANCE_NAME`_pidArea[i] = `$INSTANCE_NAME`_outputSatL[i];
            }
            else if(((int32) `$INSTANCE_NAME`_outputSatH[i]) < ((int32) `$INSTANCE_NAME`_pidArea[i]))
            {
                `$INSTANCE_NAME`_pidArea[i] = `$INSTANCE_NAME`_outputSatH[i];
            }
            else
            {
                /* Do nothing, the error is in range */
            }

            /* Get the algorithm result */
            `$INSTANCE_NAME`_pidOut = (uint16) (`$INSTANCE_NAME`_pidArea[i] >> `$INSTANCE_NAME`_PID_POST_GAIN);

            #if (!CY_PSOC4)
                /* Get compare from UDB PWMs */
                #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
                    tmpCompare = CY_GET_REG8(`$INSTANCE_NAME`_fanDriverRegs[i].pwmSetDutyReg);
                #else
                    tmpCompare = CY_GET_REG16(`$INSTANCE_NAME`_fanDriverRegs[i].pwmSetDutyReg);
                #endif /* `$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */
            #else
                /* Get compare from TCPWMs */
                tmpCompare = CY_GET_REG32(`$INSTANCE_NAME`_fanDriverRegs[i].pwmSetDutyReg);
            #endif /* (!CY_PSOC4) */

            /* Assign new compare value for fas' PWM with PID out */
            newCompare = `$INSTANCE_NAME`_pidOut;

            if (0u == (`$INSTANCE_NAME`_GLOBAL_CONTROL_REG & `$INSTANCE_NAME`_OVERRIDE))
            {
                /* If override bit is cleared then set the newly tuned compare value */
                #if (!CY_PSOC4)
                    #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
                        CY_SET_REG8(`$INSTANCE_NAME`_fanDriverRegs[i].pwmSetDutyReg, (uint8) newCompare);
                    #else
                        CY_SET_REG16(`$INSTANCE_NAME`_fanDriverRegs[i].pwmSetDutyReg, (uint16) newCompare);
                    #endif /* `$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */
                #else
                    CY_SET_REG32(`$INSTANCE_NAME`_fanDriverRegs[i].pwmSetDutyReg, newCompare);
                #endif /* (!CY_PSOC4) */
            }

            /*************************************
            * Speed regulation status
            **************************************/
            /* Analyze compare and result from PID */
            if ((`$INSTANCE_NAME`_PWM_PERIOD == tmpCompare) &&
                (currActSpeed < `$INSTANCE_NAME`_desiredFansSpeed[i]))
            {
                /* Increase speed failure counter */
                `$INSTANCE_NAME`_spdErrCount[i]++;
            }
            else if ((0u == tmpCompare) &&
                (currActSpeed > `$INSTANCE_NAME`_desiredFansSpeed[i]))
            {
                /* Avoid overflow */
                if (`$INSTANCE_NAME`_spdErrCount[i] < `$INSTANCE_NAME`_MAX_SPEED_ERRORS)
                {
                    /* Increase speed failure counter */
                    `$INSTANCE_NAME`_spdErrCount[i]++;
                }
            }
            else
            {
                /* Clear speed failure counter */
                `$INSTANCE_NAME`_spdErrCount[i] = 0u;
            }

            if (`$INSTANCE_NAME`_SPEED_ERRORS_TRESHOLD < `$INSTANCE_NAME`_spdErrCount[i])
            {
                /* The number of speed errors is above threshold so set the
                * respective speed error bit in the software speed status but
                * only if respective bit is set in the alert mask register.
                */
                mask = (uint16) `$INSTANCE_NAME`_ALERT_MASK_LSB_CONTROL_REG;
                #if (`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
                    mask = mask | (uint16)((uint16)`$INSTANCE_NAME`_ALERT_MASK_MSB_CONTROL_REG << 8u);
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS > 8u */

                `$INSTANCE_NAME`_speedStatus = (uint16) ((((uint16) 1u) << i)) & mask;
            }
        }

        /* If software speed status register is not zero then simulate
        * hardware failure event. This will generate a pulse that goes to
        * Alert Status register.
        */
        if (0u !=`$INSTANCE_NAME`_speedStatus)
        {
            `$INSTANCE_NAME`_GLOBAL_CONTROL_REG |= `$INSTANCE_NAME`_SW_SPEED_ERROR;
        }

        #ifdef `$INSTANCE_NAME`_PID_CONTROL_ISR_EXIT_CALLBACK
            `$INSTANCE_NAME`_PID_CONTROL_ISR_ExitCallback();
        #endif /* `$INSTANCE_NAME`_PID_CONTROL_ISR_EXIT_CALLBACK */
    }
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */


/* [] END OF FILE */
