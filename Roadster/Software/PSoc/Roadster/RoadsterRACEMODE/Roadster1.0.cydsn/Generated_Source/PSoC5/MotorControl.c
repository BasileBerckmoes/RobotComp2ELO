/*******************************************************************************
* File Name: MotorControl.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "MotorControl.h"

/* Error message for removed <resource> through optimization */
#ifdef MotorControl_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* MotorControl_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 MotorControl_initVar = 0u;


/*******************************************************************************
* Function Name: MotorControl_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  MotorControl_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MotorControl_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MotorControl_initVar == 0u)
    {
        MotorControl_Init();
        MotorControl_initVar = 1u;
    }
    MotorControl_Enable();

}


/*******************************************************************************
* Function Name: MotorControl_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  MotorControl_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void MotorControl_Init(void) 
{
    #if (MotorControl_UsingFixedFunction || MotorControl_UseControl)
        uint8 ctrl;
    #endif /* (MotorControl_UsingFixedFunction || MotorControl_UseControl) */

    #if(!MotorControl_UsingFixedFunction)
        #if(MotorControl_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 MotorControl_interruptState;
        #endif /* (MotorControl_UseStatus) */
    #endif /* (!MotorControl_UsingFixedFunction) */

    #if (MotorControl_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        MotorControl_CONTROL |= MotorControl_CFG0_MODE;
        #if (MotorControl_DeadBand2_4)
            MotorControl_CONTROL |= MotorControl_CFG0_DB;
        #endif /* (MotorControl_DeadBand2_4) */

        ctrl = MotorControl_CONTROL3 & ((uint8 )(~MotorControl_CTRL_CMPMODE1_MASK));
        MotorControl_CONTROL3 = ctrl | MotorControl_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        MotorControl_RT1 &= ((uint8)(~MotorControl_RT1_MASK));
        MotorControl_RT1 |= MotorControl_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        MotorControl_RT1 &= ((uint8)(~MotorControl_SYNCDSI_MASK));
        MotorControl_RT1 |= MotorControl_SYNCDSI_EN;

    #elif (MotorControl_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = MotorControl_CONTROL & ((uint8)(~MotorControl_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~MotorControl_CTRL_CMPMODE1_MASK));
        MotorControl_CONTROL = ctrl | MotorControl_DEFAULT_COMPARE2_MODE |
                                   MotorControl_DEFAULT_COMPARE1_MODE;
    #endif /* (MotorControl_UsingFixedFunction) */

    #if (!MotorControl_UsingFixedFunction)
        #if (MotorControl_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            MotorControl_AUX_CONTROLDP0 |= (MotorControl_AUX_CTRL_FIFO0_CLR);
        #else /* (MotorControl_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            MotorControl_AUX_CONTROLDP0 |= (MotorControl_AUX_CTRL_FIFO0_CLR);
            MotorControl_AUX_CONTROLDP1 |= (MotorControl_AUX_CTRL_FIFO0_CLR);
        #endif /* (MotorControl_Resolution == 8) */

        MotorControl_WriteCounter(MotorControl_INIT_PERIOD_VALUE);
    #endif /* (!MotorControl_UsingFixedFunction) */

    MotorControl_WritePeriod(MotorControl_INIT_PERIOD_VALUE);

        #if (MotorControl_UseOneCompareMode)
            MotorControl_WriteCompare(MotorControl_INIT_COMPARE_VALUE1);
        #else
            MotorControl_WriteCompare1(MotorControl_INIT_COMPARE_VALUE1);
            MotorControl_WriteCompare2(MotorControl_INIT_COMPARE_VALUE2);
        #endif /* (MotorControl_UseOneCompareMode) */

        #if (MotorControl_KillModeMinTime)
            MotorControl_WriteKillTime(MotorControl_MinimumKillTime);
        #endif /* (MotorControl_KillModeMinTime) */

        #if (MotorControl_DeadBandUsed)
            MotorControl_WriteDeadTime(MotorControl_INIT_DEAD_TIME);
        #endif /* (MotorControl_DeadBandUsed) */

    #if (MotorControl_UseStatus || MotorControl_UsingFixedFunction)
        MotorControl_SetInterruptMode(MotorControl_INIT_INTERRUPTS_MODE);
    #endif /* (MotorControl_UseStatus || MotorControl_UsingFixedFunction) */

    #if (MotorControl_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        MotorControl_GLOBAL_ENABLE |= MotorControl_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        MotorControl_CONTROL2 |= MotorControl_CTRL2_IRQ_SEL;
    #else
        #if(MotorControl_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            MotorControl_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            MotorControl_STATUS_AUX_CTRL |= MotorControl_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(MotorControl_interruptState);

            /* Clear the FIFO to enable the MotorControl_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            MotorControl_ClearFIFO();
        #endif /* (MotorControl_UseStatus) */
    #endif /* (MotorControl_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorControl_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void MotorControl_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (MotorControl_UsingFixedFunction)
        MotorControl_GLOBAL_ENABLE |= MotorControl_BLOCK_EN_MASK;
        MotorControl_GLOBAL_STBY_ENABLE |= MotorControl_BLOCK_STBY_EN_MASK;
    #endif /* (MotorControl_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (MotorControl_UseControl || MotorControl_UsingFixedFunction)
        MotorControl_CONTROL |= MotorControl_CTRL_ENABLE;
    #endif /* (MotorControl_UseControl || MotorControl_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorControl_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void MotorControl_Stop(void) 
{
    #if (MotorControl_UseControl || MotorControl_UsingFixedFunction)
        MotorControl_CONTROL &= ((uint8)(~MotorControl_CTRL_ENABLE));
    #endif /* (MotorControl_UseControl || MotorControl_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (MotorControl_UsingFixedFunction)
        MotorControl_GLOBAL_ENABLE &= ((uint8)(~MotorControl_BLOCK_EN_MASK));
        MotorControl_GLOBAL_STBY_ENABLE &= ((uint8)(~MotorControl_BLOCK_STBY_EN_MASK));
    #endif /* (MotorControl_UsingFixedFunction) */
}

#if (MotorControl_UseOneCompareMode)
    #if (MotorControl_CompareMode1SW)


        /*******************************************************************************
        * Function Name: MotorControl_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void MotorControl_SetCompareMode(uint8 comparemode) 
        {
            #if(MotorControl_UsingFixedFunction)

                #if(0 != MotorControl_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorControl_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != MotorControl_CTRL_CMPMODE1_SHIFT) */

                MotorControl_CONTROL3 &= ((uint8)(~MotorControl_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                MotorControl_CONTROL3 |= comparemodemasked;

            #elif (MotorControl_UseControl)

                #if(0 != MotorControl_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << MotorControl_CTRL_CMPMODE1_SHIFT)) &
                                                MotorControl_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & MotorControl_CTRL_CMPMODE1_MASK;
                #endif /* (0 != MotorControl_CTRL_CMPMODE1_SHIFT) */

                #if(0 != MotorControl_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << MotorControl_CTRL_CMPMODE2_SHIFT)) &
                                               MotorControl_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & MotorControl_CTRL_CMPMODE2_MASK;
                #endif /* (0 != MotorControl_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                MotorControl_CONTROL &= ((uint8)(~(MotorControl_CTRL_CMPMODE1_MASK |
                                            MotorControl_CTRL_CMPMODE2_MASK)));
                MotorControl_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (MotorControl_UsingFixedFunction) */
        }
    #endif /* MotorControl_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (MotorControl_CompareMode1SW)


        /*******************************************************************************
        * Function Name: MotorControl_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void MotorControl_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != MotorControl_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorControl_CTRL_CMPMODE1_SHIFT)) &
                                           MotorControl_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & MotorControl_CTRL_CMPMODE1_MASK;
            #endif /* (0 != MotorControl_CTRL_CMPMODE1_SHIFT) */

            #if (MotorControl_UseControl)
                MotorControl_CONTROL &= ((uint8)(~MotorControl_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                MotorControl_CONTROL |= comparemodemasked;
            #endif /* (MotorControl_UseControl) */
        }
    #endif /* MotorControl_CompareMode1SW */

#if (MotorControl_CompareMode2SW)


    /*******************************************************************************
    * Function Name: MotorControl_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != MotorControl_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << MotorControl_CTRL_CMPMODE2_SHIFT)) &
                                                 MotorControl_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & MotorControl_CTRL_CMPMODE2_MASK;
        #endif /* (0 != MotorControl_CTRL_CMPMODE2_SHIFT) */

        #if (MotorControl_UseControl)
            MotorControl_CONTROL &= ((uint8)(~MotorControl_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            MotorControl_CONTROL |= comparemodemasked;
        #endif /* (MotorControl_UseControl) */
    }
    #endif /*MotorControl_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!MotorControl_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorControl_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void MotorControl_WriteCounter(uint8 counter) \
                                       
    {
        CY_SET_REG8(MotorControl_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: MotorControl_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint8 MotorControl_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(MotorControl_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG8(MotorControl_CAPTURE_LSB_PTR));
    }

    #if (MotorControl_UseStatus)


        /*******************************************************************************
        * Function Name: MotorControl_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void MotorControl_ClearFIFO(void) 
        {
            while(0u != (MotorControl_ReadStatusRegister() & MotorControl_STATUS_FIFONEMPTY))
            {
                (void)MotorControl_ReadCapture();
            }
        }

    #endif /* MotorControl_UseStatus */

#endif /* !MotorControl_UsingFixedFunction */


/*******************************************************************************
* Function Name: MotorControl_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void MotorControl_WritePeriod(uint8 period) 
{
    #if(MotorControl_UsingFixedFunction)
        CY_SET_REG16(MotorControl_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG8(MotorControl_PERIOD_LSB_PTR, period);
    #endif /* (MotorControl_UsingFixedFunction) */
}

#if (MotorControl_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorControl_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void MotorControl_WriteCompare(uint8 compare) \
                                       
    {
        #if(MotorControl_UsingFixedFunction)
            CY_SET_REG16(MotorControl_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(MotorControl_COMPARE1_LSB_PTR, compare);
        #endif /* (MotorControl_UsingFixedFunction) */

        #if (MotorControl_PWMMode == MotorControl__B_PWM__DITHER)
            #if(MotorControl_UsingFixedFunction)
                CY_SET_REG16(MotorControl_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG8(MotorControl_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (MotorControl_UsingFixedFunction) */
        #endif /* (MotorControl_PWMMode == MotorControl__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: MotorControl_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_WriteCompare1(uint8 compare) \
                                        
    {
        #if(MotorControl_UsingFixedFunction)
            CY_SET_REG16(MotorControl_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG8(MotorControl_COMPARE1_LSB_PTR, compare);
        #endif /* (MotorControl_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: MotorControl_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_WriteCompare2(uint8 compare) \
                                        
    {
        #if(MotorControl_UsingFixedFunction)
            CY_SET_REG16(MotorControl_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG8(MotorControl_COMPARE2_LSB_PTR, compare);
        #endif /* (MotorControl_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (MotorControl_DeadBandUsed)


    /*******************************************************************************
    * Function Name: MotorControl_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!MotorControl_DeadBand2_4)
            CY_SET_REG8(MotorControl_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            MotorControl_DEADBAND_COUNT &= ((uint8)(~MotorControl_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(MotorControl_DEADBAND_COUNT_SHIFT)
                MotorControl_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << MotorControl_DEADBAND_COUNT_SHIFT)) &
                                                    MotorControl_DEADBAND_COUNT_MASK;
            #else
                MotorControl_DEADBAND_COUNT |= deadtime & MotorControl_DEADBAND_COUNT_MASK;
            #endif /* (MotorControl_DEADBAND_COUNT_SHIFT) */

        #endif /* (!MotorControl_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: MotorControl_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 MotorControl_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!MotorControl_DeadBand2_4)
            return (CY_GET_REG8(MotorControl_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(MotorControl_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(MotorControl_DEADBAND_COUNT & MotorControl_DEADBAND_COUNT_MASK)) >>
                                                                           MotorControl_DEADBAND_COUNT_SHIFT));
            #else
                return (MotorControl_DEADBAND_COUNT & MotorControl_DEADBAND_COUNT_MASK);
            #endif /* (MotorControl_DEADBAND_COUNT_SHIFT) */
        #endif /* (!MotorControl_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (MotorControl_UseStatus || MotorControl_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorControl_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(MotorControl_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: MotorControl_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 MotorControl_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(MotorControl_STATUS_PTR));
    }

#endif /* (MotorControl_UseStatus || MotorControl_UsingFixedFunction) */


#if (MotorControl_UseControl)


    /*******************************************************************************
    * Function Name: MotorControl_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 MotorControl_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(MotorControl_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: MotorControl_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(MotorControl_CONTROL_PTR, control);
    }

#endif /* (MotorControl_UseControl) */


#if (!MotorControl_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: MotorControl_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint8 MotorControl_ReadCapture(void) 
    {
        return (CY_GET_REG8(MotorControl_CAPTURE_LSB_PTR));
    }

#endif /* (!MotorControl_UsingFixedFunction) */


#if (MotorControl_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: MotorControl_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint8 MotorControl_ReadCompare(void) 
    {
        #if(MotorControl_UsingFixedFunction)
            return ((uint8)CY_GET_REG16(MotorControl_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG8(MotorControl_COMPARE1_LSB_PTR));
        #endif /* (MotorControl_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: MotorControl_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 MotorControl_ReadCompare1(void) 
    {
        return (CY_GET_REG8(MotorControl_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: MotorControl_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint8 MotorControl_ReadCompare2(void) 
    {
        return (CY_GET_REG8(MotorControl_COMPARE2_LSB_PTR));
    }

#endif /* (MotorControl_UseOneCompareMode) */


/*******************************************************************************
* Function Name: MotorControl_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint8 MotorControl_ReadPeriod(void) 
{
    #if(MotorControl_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(MotorControl_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(MotorControl_PERIOD_LSB_PTR));
    #endif /* (MotorControl_UsingFixedFunction) */
}

#if ( MotorControl_KillModeMinTime)


    /*******************************************************************************
    * Function Name: MotorControl_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void MotorControl_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(MotorControl_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: MotorControl_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 MotorControl_ReadKillTime(void) 
    {
        return (CY_GET_REG8(MotorControl_KILLMODEMINTIME_PTR));
    }

#endif /* ( MotorControl_KillModeMinTime) */

/* [] END OF FILE */
