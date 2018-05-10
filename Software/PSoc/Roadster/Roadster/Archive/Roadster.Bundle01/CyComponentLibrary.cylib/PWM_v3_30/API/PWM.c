/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
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

#include "`$INSTANCE_NAME`.h"

/* Error message for removed <resource> through optimization */
#ifdef `$INSTANCE_NAME`_PWMUDB_genblk1_ctrlreg__REMOVED
    #error `$CY_COMPONENT_NAME` detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* `$INSTANCE_NAME`_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
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
*  `$INSTANCE_NAME`_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not Initialized then initialize all required hardware and software */
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  `$INSTANCE_NAME`_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    #if (`$INSTANCE_NAME`_UsingFixedFunction || `$INSTANCE_NAME`_UseControl)
        uint8 ctrl;
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction || `$INSTANCE_NAME`_UseControl) */

    #if(!`$INSTANCE_NAME`_UsingFixedFunction)
        #if(`$INSTANCE_NAME`_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 `$INSTANCE_NAME`_interruptState;
        #endif /* (`$INSTANCE_NAME`_UseStatus) */
    #endif /* (!`$INSTANCE_NAME`_UsingFixedFunction) */

    #if (`$INSTANCE_NAME`_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_CFG0_MODE;
        #if (`$INSTANCE_NAME`_DeadBand2_4)
            `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_CFG0_DB;
        #endif /* (`$INSTANCE_NAME`_DeadBand2_4) */

        ctrl = `$INSTANCE_NAME`_CONTROL3 & ((uint8 )(~`$INSTANCE_NAME`_CTRL_CMPMODE1_MASK));
        `$INSTANCE_NAME`_CONTROL3 = ctrl | `$INSTANCE_NAME`_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        `$INSTANCE_NAME`_RT1 &= ((uint8)(~`$INSTANCE_NAME`_RT1_MASK));
        `$INSTANCE_NAME`_RT1 |= `$INSTANCE_NAME`_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        `$INSTANCE_NAME`_RT1 &= ((uint8)(~`$INSTANCE_NAME`_SYNCDSI_MASK));
        `$INSTANCE_NAME`_RT1 |= `$INSTANCE_NAME`_SYNCDSI_EN;

    #elif (`$INSTANCE_NAME`_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = `$INSTANCE_NAME`_CONTROL & ((uint8)(~`$INSTANCE_NAME`_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~`$INSTANCE_NAME`_CTRL_CMPMODE1_MASK));
        `$INSTANCE_NAME`_CONTROL = ctrl | `$INSTANCE_NAME`_DEFAULT_COMPARE2_MODE |
                                   `$INSTANCE_NAME`_DEFAULT_COMPARE1_MODE;
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */

    #if (!`$INSTANCE_NAME`_UsingFixedFunction)
        #if (`$INSTANCE_NAME`_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            `$INSTANCE_NAME`_AUX_CONTROLDP0 |= (`$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR);
        #else /* (`$INSTANCE_NAME`_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            `$INSTANCE_NAME`_AUX_CONTROLDP0 |= (`$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR);
            `$INSTANCE_NAME`_AUX_CONTROLDP1 |= (`$INSTANCE_NAME`_AUX_CTRL_FIFO0_CLR);
        #endif /* (`$INSTANCE_NAME`_Resolution == 8) */

        `$INSTANCE_NAME`_WriteCounter(`$INSTANCE_NAME`_INIT_PERIOD_VALUE);
    #endif /* (!`$INSTANCE_NAME`_UsingFixedFunction) */

    `$INSTANCE_NAME`_WritePeriod(`$INSTANCE_NAME`_INIT_PERIOD_VALUE);

        #if (`$INSTANCE_NAME`_UseOneCompareMode)
            `$INSTANCE_NAME`_WriteCompare(`$INSTANCE_NAME`_INIT_COMPARE_VALUE1);
        #else
            `$INSTANCE_NAME`_WriteCompare1(`$INSTANCE_NAME`_INIT_COMPARE_VALUE1);
            `$INSTANCE_NAME`_WriteCompare2(`$INSTANCE_NAME`_INIT_COMPARE_VALUE2);
        #endif /* (`$INSTANCE_NAME`_UseOneCompareMode) */

        #if (`$INSTANCE_NAME`_KillModeMinTime)
            `$INSTANCE_NAME`_WriteKillTime(`$INSTANCE_NAME`_MinimumKillTime);
        #endif /* (`$INSTANCE_NAME`_KillModeMinTime) */

        #if (`$INSTANCE_NAME`_DeadBandUsed)
            `$INSTANCE_NAME`_WriteDeadTime(`$INSTANCE_NAME`_INIT_DEAD_TIME);
        #endif /* (`$INSTANCE_NAME`_DeadBandUsed) */

    #if (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction)
        `$INSTANCE_NAME`_SetInterruptMode(`$INSTANCE_NAME`_INIT_INTERRUPTS_MODE);
    #endif /* (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction) */

    #if (`$INSTANCE_NAME`_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        `$INSTANCE_NAME`_GLOBAL_ENABLE |= `$INSTANCE_NAME`_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        `$INSTANCE_NAME`_CONTROL2 |= `$INSTANCE_NAME`_CTRL2_IRQ_SEL;
    #else
        #if(`$INSTANCE_NAME`_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            `$INSTANCE_NAME`_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            `$INSTANCE_NAME`_STATUS_AUX_CTRL |= `$INSTANCE_NAME`_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(`$INSTANCE_NAME`_interruptState);

            /* Clear the FIFO to enable the `$INSTANCE_NAME`_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            `$INSTANCE_NAME`_ClearFIFO();
        #endif /* (`$INSTANCE_NAME`_UseStatus) */
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
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
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (`$INSTANCE_NAME`_UsingFixedFunction)
        `$INSTANCE_NAME`_GLOBAL_ENABLE |= `$INSTANCE_NAME`_BLOCK_EN_MASK;
        `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE |= `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK;
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (`$INSTANCE_NAME`_UseControl || `$INSTANCE_NAME`_UsingFixedFunction)
        `$INSTANCE_NAME`_CONTROL |= `$INSTANCE_NAME`_CTRL_ENABLE;
    #endif /* (`$INSTANCE_NAME`_UseControl || `$INSTANCE_NAME`_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
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
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    #if (`$INSTANCE_NAME`_UseControl || `$INSTANCE_NAME`_UsingFixedFunction)
        `$INSTANCE_NAME`_CONTROL &= ((uint8)(~`$INSTANCE_NAME`_CTRL_ENABLE));
    #endif /* (`$INSTANCE_NAME`_UseControl || `$INSTANCE_NAME`_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (`$INSTANCE_NAME`_UsingFixedFunction)
        `$INSTANCE_NAME`_GLOBAL_ENABLE &= ((uint8)(~`$INSTANCE_NAME`_BLOCK_EN_MASK));
        `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE &= ((uint8)(~`$INSTANCE_NAME`_BLOCK_STBY_EN_MASK));
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
}

#if (`$INSTANCE_NAME`_UseOneCompareMode)
    #if (`$INSTANCE_NAME`_CompareMode1SW)


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SetCompareMode
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
        void `$INSTANCE_NAME`_SetCompareMode(uint8 comparemode) `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode")`
        {
            #if(`$INSTANCE_NAME`_UsingFixedFunction)

                #if(0 != `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT) */

                `$INSTANCE_NAME`_CONTROL3 &= ((uint8)(~`$INSTANCE_NAME`_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                `$INSTANCE_NAME`_CONTROL3 |= comparemodemasked;

            #elif (`$INSTANCE_NAME`_UseControl)

                #if(0 != `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)) &
                                                `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK;
                #endif /* (0 != `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT) */

                #if(0 != `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)) &
                                               `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK;
                #endif /* (0 != `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                `$INSTANCE_NAME`_CONTROL &= ((uint8)(~(`$INSTANCE_NAME`_CTRL_CMPMODE1_MASK |
                                            `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK)));
                `$INSTANCE_NAME`_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
        }
    #endif /* `$INSTANCE_NAME`_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (`$INSTANCE_NAME`_CompareMode1SW)


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SetCompareMode1
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
        void `$INSTANCE_NAME`_SetCompareMode1(uint8 comparemode) `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode1")`
        {
            #if(0 != `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT)) &
                                           `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & `$INSTANCE_NAME`_CTRL_CMPMODE1_MASK;
            #endif /* (0 != `$INSTANCE_NAME`_CTRL_CMPMODE1_SHIFT) */

            #if (`$INSTANCE_NAME`_UseControl)
                `$INSTANCE_NAME`_CONTROL &= ((uint8)(~`$INSTANCE_NAME`_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                `$INSTANCE_NAME`_CONTROL |= comparemodemasked;
            #endif /* (`$INSTANCE_NAME`_UseControl) */
        }
    #endif /* `$INSTANCE_NAME`_CompareMode1SW */

#if (`$INSTANCE_NAME`_CompareMode2SW)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCompareMode2
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
    void `$INSTANCE_NAME`_SetCompareMode2(uint8 comparemode) `=ReentrantKeil($INSTANCE_NAME . "_SetCompareMode2")`
    {

        #if(0 != `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT)) &
                                                 `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & `$INSTANCE_NAME`_CTRL_CMPMODE2_MASK;
        #endif /* (0 != `$INSTANCE_NAME`_CTRL_CMPMODE2_SHIFT) */

        #if (`$INSTANCE_NAME`_UseControl)
            `$INSTANCE_NAME`_CONTROL &= ((uint8)(~`$INSTANCE_NAME`_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            `$INSTANCE_NAME`_CONTROL |= comparemodemasked;
        #endif /* (`$INSTANCE_NAME`_UseControl) */
    }
    #endif /*`$INSTANCE_NAME`_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!`$INSTANCE_NAME`_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteCounter
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
    void `$INSTANCE_NAME`_WriteCounter(`$RegSizeReplacementString` counter) \
                                       `=ReentrantKeil($INSTANCE_NAME . "_WriteCounter")`
    {
        `$CySetRegReplacementString`(`$INSTANCE_NAME`_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCounter
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
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCounter(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCounter")`
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(`$INSTANCE_NAME`_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (`$CyGetRegReplacementString`(`$INSTANCE_NAME`_CAPTURE_LSB_PTR));
    }

    #if (`$INSTANCE_NAME`_UseStatus)


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_ClearFIFO
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
        void `$INSTANCE_NAME`_ClearFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearFIFO")`
        {
            while(0u != (`$INSTANCE_NAME`_ReadStatusRegister() & `$INSTANCE_NAME`_STATUS_FIFONEMPTY))
            {
                (void)`$INSTANCE_NAME`_ReadCapture();
            }
        }

    #endif /* `$INSTANCE_NAME`_UseStatus */

#endif /* !`$INSTANCE_NAME`_UsingFixedFunction */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WritePeriod
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
void `$INSTANCE_NAME`_WritePeriod(`$RegSizeReplacementString` period) `=ReentrantKeil($INSTANCE_NAME . "_WritePeriod")`
{
    #if(`$INSTANCE_NAME`_UsingFixedFunction)
        CY_SET_REG16(`$INSTANCE_NAME`_PERIOD_LSB_PTR, (uint16)period);
    #else
        `$CySetRegReplacementString`(`$INSTANCE_NAME`_PERIOD_LSB_PTR, period);
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
}

#if (`$INSTANCE_NAME`_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteCompare
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
    void `$INSTANCE_NAME`_WriteCompare(`$RegSizeReplacementString` compare) \
                                       `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare")`
    {
        #if(`$INSTANCE_NAME`_UsingFixedFunction)
            CY_SET_REG16(`$INSTANCE_NAME`_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            `$CySetRegReplacementString`(`$INSTANCE_NAME`_COMPARE1_LSB_PTR, compare);
        #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */

        #if (`$INSTANCE_NAME`_PWMMode == `$INSTANCE_NAME`__B_PWM__DITHER)
            #if(`$INSTANCE_NAME`_UsingFixedFunction)
                CY_SET_REG16(`$INSTANCE_NAME`_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                `$CySetRegReplacementString`(`$INSTANCE_NAME`_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
        #endif /* (`$INSTANCE_NAME`_PWMMode == `$INSTANCE_NAME`__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteCompare1
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
    void `$INSTANCE_NAME`_WriteCompare1(`$RegSizeReplacementString` compare) \
                                        `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare1")`
    {
        #if(`$INSTANCE_NAME`_UsingFixedFunction)
            CY_SET_REG16(`$INSTANCE_NAME`_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            `$CySetRegReplacementString`(`$INSTANCE_NAME`_COMPARE1_LSB_PTR, compare);
        #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteCompare2
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
    void `$INSTANCE_NAME`_WriteCompare2(`$RegSizeReplacementString` compare) \
                                        `=ReentrantKeil($INSTANCE_NAME . "_WriteCompare2")`
    {
        #if(`$INSTANCE_NAME`_UsingFixedFunction)
            CY_SET_REG16(`$INSTANCE_NAME`_COMPARE2_LSB_PTR, compare);
        #else
            `$CySetRegReplacementString`(`$INSTANCE_NAME`_COMPARE2_LSB_PTR, compare);
        #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (`$INSTANCE_NAME`_DeadBandUsed)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteDeadTime
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
    void `$INSTANCE_NAME`_WriteDeadTime(uint8 deadtime) `=ReentrantKeil($INSTANCE_NAME . "_WriteDeadTime")`
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!`$INSTANCE_NAME`_DeadBand2_4)
            CY_SET_REG8(`$INSTANCE_NAME`_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            `$INSTANCE_NAME`_DEADBAND_COUNT &= ((uint8)(~`$INSTANCE_NAME`_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(`$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT)
                `$INSTANCE_NAME`_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT)) &
                                                    `$INSTANCE_NAME`_DEADBAND_COUNT_MASK;
            #else
                `$INSTANCE_NAME`_DEADBAND_COUNT |= deadtime & `$INSTANCE_NAME`_DEADBAND_COUNT_MASK;
            #endif /* (`$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT) */

        #endif /* (!`$INSTANCE_NAME`_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadDeadTime
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
    uint8 `$INSTANCE_NAME`_ReadDeadTime(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadDeadTime")`
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!`$INSTANCE_NAME`_DeadBand2_4)
            return (CY_GET_REG8(`$INSTANCE_NAME`_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(`$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(`$INSTANCE_NAME`_DEADBAND_COUNT & `$INSTANCE_NAME`_DEADBAND_COUNT_MASK)) >>
                                                                           `$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT));
            #else
                return (`$INSTANCE_NAME`_DEADBAND_COUNT & `$INSTANCE_NAME`_DEADBAND_COUNT_MASK);
            #endif /* (`$INSTANCE_NAME`_DEADBAND_COUNT_SHIFT) */
        #endif /* (!`$INSTANCE_NAME`_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetInterruptMode
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
    void `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptMode) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`
    {
        CY_SET_REG8(`$INSTANCE_NAME`_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadStatusRegister
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
    uint8 `$INSTANCE_NAME`_ReadStatusRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatusRegister")`
    {
        return (CY_GET_REG8(`$INSTANCE_NAME`_STATUS_PTR));
    }

#endif /* (`$INSTANCE_NAME`_UseStatus || `$INSTANCE_NAME`_UsingFixedFunction) */


#if (`$INSTANCE_NAME`_UseControl)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadControlRegister
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
    uint8 `$INSTANCE_NAME`_ReadControlRegister(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadControlRegister")`
    {
        uint8 result;

        result = CY_GET_REG8(`$INSTANCE_NAME`_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteControlRegister
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
    void `$INSTANCE_NAME`_WriteControlRegister(uint8 control) `=ReentrantKeil($INSTANCE_NAME . "_WriteControlRegister")`
    {
        CY_SET_REG8(`$INSTANCE_NAME`_CONTROL_PTR, control);
    }

#endif /* (`$INSTANCE_NAME`_UseControl) */


#if (!`$INSTANCE_NAME`_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCapture
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
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCapture(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCapture")`
    {
        return (`$CyGetRegReplacementString`(`$INSTANCE_NAME`_CAPTURE_LSB_PTR));
    }

#endif /* (!`$INSTANCE_NAME`_UsingFixedFunction) */


#if (`$INSTANCE_NAME`_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCompare
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
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCompare(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare")`
    {
        #if(`$INSTANCE_NAME`_UsingFixedFunction)
            return ((`$RegSizeReplacementString`)CY_GET_REG16(`$INSTANCE_NAME`_COMPARE1_LSB_PTR));
        #else
            return (`$CyGetRegReplacementString`(`$INSTANCE_NAME`_COMPARE1_LSB_PTR));
        #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCompare1
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
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCompare1(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare1")`
    {
        return (`$CyGetRegReplacementString`(`$INSTANCE_NAME`_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadCompare2
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
    `$RegSizeReplacementString` `$INSTANCE_NAME`_ReadCompare2(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadCompare2")`
    {
        return (`$CyGetRegReplacementString`(`$INSTANCE_NAME`_COMPARE2_LSB_PTR));
    }

#endif /* (`$INSTANCE_NAME`_UseOneCompareMode) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadPeriod
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
`$RegSizeReplacementString` `$INSTANCE_NAME`_ReadPeriod(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadPeriod")`
{
    #if(`$INSTANCE_NAME`_UsingFixedFunction)
        return ((`$RegSizeReplacementString`)CY_GET_REG16(`$INSTANCE_NAME`_PERIOD_LSB_PTR));
    #else
        return (`$CyGetRegReplacementString`(`$INSTANCE_NAME`_PERIOD_LSB_PTR));
    #endif /* (`$INSTANCE_NAME`_UsingFixedFunction) */
}

#if ( `$INSTANCE_NAME`_KillModeMinTime)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_WriteKillTime
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
    void `$INSTANCE_NAME`_WriteKillTime(uint8 killtime) `=ReentrantKeil($INSTANCE_NAME . "_WriteKillTime")`
    {
        CY_SET_REG8(`$INSTANCE_NAME`_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ReadKillTime
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
    uint8 `$INSTANCE_NAME`_ReadKillTime(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadKillTime")`
    {
        return (CY_GET_REG8(`$INSTANCE_NAME`_KILLMODEMINTIME_PTR));
    }

#endif /* ( `$INSTANCE_NAME`_KillModeMinTime) */

/* [] END OF FILE */
