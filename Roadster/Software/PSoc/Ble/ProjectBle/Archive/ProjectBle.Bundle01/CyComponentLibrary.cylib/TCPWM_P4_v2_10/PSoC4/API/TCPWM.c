/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the `$INSTANCE_NAME`
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default `$INSTANCE_NAME` configuration.
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

    /* Set values from customizer to CTRL */
    #if (`$INSTANCE_NAME`__QUAD == `$INSTANCE_NAME`_CONFIG)
        `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        `$INSTANCE_NAME`_TRIG_CONTROL1_REG  = `$INSTANCE_NAME`_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        `$INSTANCE_NAME`_SetInterruptMode(`$INSTANCE_NAME`_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        `$INSTANCE_NAME`_SetCounterMode(`$INSTANCE_NAME`_COUNT_DOWN);
        `$INSTANCE_NAME`_WritePeriod(`$INSTANCE_NAME`_QUAD_PERIOD_INIT_VALUE);
        `$INSTANCE_NAME`_WriteCounter(`$INSTANCE_NAME`_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (`$INSTANCE_NAME`__QUAD == `$INSTANCE_NAME`_CONFIG) */

    #if (`$INSTANCE_NAME`__TIMER == `$INSTANCE_NAME`_CONFIG)
        `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        `$INSTANCE_NAME`_TRIG_CONTROL1_REG  = `$INSTANCE_NAME`_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        `$INSTANCE_NAME`_SetInterruptMode(`$INSTANCE_NAME`_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        `$INSTANCE_NAME`_WritePeriod(`$INSTANCE_NAME`_TC_PERIOD_VALUE );

        #if (`$INSTANCE_NAME`__COMPARE == `$INSTANCE_NAME`_TC_COMP_CAP_MODE)
            `$INSTANCE_NAME`_WriteCompare(`$INSTANCE_NAME`_TC_COMPARE_VALUE);

            #if (1u == `$INSTANCE_NAME`_TC_COMPARE_SWAP)
                `$INSTANCE_NAME`_SetCompareSwap(1u);
                `$INSTANCE_NAME`_WriteCompareBuf(`$INSTANCE_NAME`_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == `$INSTANCE_NAME`_TC_COMPARE_SWAP) */
        #endif  /* (`$INSTANCE_NAME`__COMPARE == `$INSTANCE_NAME`_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (`$INSTANCE_NAME`_CY_TCPWM_V2 && `$INSTANCE_NAME`_TIMER_UPDOWN_CNT_USED && !`$INSTANCE_NAME`_CY_TCPWM_4000)
            `$INSTANCE_NAME`_WriteCounter(1u);
        #elif(`$INSTANCE_NAME`__COUNT_DOWN == `$INSTANCE_NAME`_TC_COUNTER_MODE)
            `$INSTANCE_NAME`_WriteCounter(`$INSTANCE_NAME`_TC_PERIOD_VALUE);
        #else
            `$INSTANCE_NAME`_WriteCounter(0u);
        #endif /* (`$INSTANCE_NAME`_CY_TCPWM_V2 && `$INSTANCE_NAME`_TIMER_UPDOWN_CNT_USED && !`$INSTANCE_NAME`_CY_TCPWM_4000) */
    #endif  /* (`$INSTANCE_NAME`__TIMER == `$INSTANCE_NAME`_CONFIG) */

    #if (`$INSTANCE_NAME`__PWM_SEL == `$INSTANCE_NAME`_CONFIG)
        `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_CTRL_PWM_BASE_CONFIG;

        #if (`$INSTANCE_NAME`__PWM_PR == `$INSTANCE_NAME`_PWM_MODE)
            `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_PWM_RUN_MODE;
            `$INSTANCE_NAME`_WriteCounter(`$INSTANCE_NAME`_PWM_PR_INIT_VALUE);
        #else
            `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_PWM_ALIGN | `$INSTANCE_NAME`_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (`$INSTANCE_NAME`_CY_TCPWM_V2 && `$INSTANCE_NAME`_PWM_UPDOWN_CNT_USED && !`$INSTANCE_NAME`_CY_TCPWM_4000)
                `$INSTANCE_NAME`_WriteCounter(1u);
            #elif (`$INSTANCE_NAME`__RIGHT == `$INSTANCE_NAME`_PWM_ALIGN)
                `$INSTANCE_NAME`_WriteCounter(`$INSTANCE_NAME`_PWM_PERIOD_VALUE);
            #else 
                `$INSTANCE_NAME`_WriteCounter(0u);
            #endif  /* (`$INSTANCE_NAME`_CY_TCPWM_V2 && `$INSTANCE_NAME`_PWM_UPDOWN_CNT_USED && !`$INSTANCE_NAME`_CY_TCPWM_4000) */
        #endif  /* (`$INSTANCE_NAME`__PWM_PR == `$INSTANCE_NAME`_PWM_MODE) */

        #if (`$INSTANCE_NAME`__PWM_DT == `$INSTANCE_NAME`_PWM_MODE)
            `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (`$INSTANCE_NAME`__PWM_DT == `$INSTANCE_NAME`_PWM_MODE) */

        #if (`$INSTANCE_NAME`__PWM == `$INSTANCE_NAME`_PWM_MODE)
            `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_PWM_PRESCALER;
        #endif  /* (`$INSTANCE_NAME`__PWM == `$INSTANCE_NAME`_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        `$INSTANCE_NAME`_TRIG_CONTROL1_REG  = `$INSTANCE_NAME`_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        `$INSTANCE_NAME`_SetInterruptMode(`$INSTANCE_NAME`_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (`$INSTANCE_NAME`__PWM_PR == `$INSTANCE_NAME`_PWM_MODE)
            `$INSTANCE_NAME`_TRIG_CONTROL2_REG =
                    (`$INSTANCE_NAME`_CC_MATCH_NO_CHANGE    |
                    `$INSTANCE_NAME`_OVERLOW_NO_CHANGE      |
                    `$INSTANCE_NAME`_UNDERFLOW_NO_CHANGE);
        #else
            #if (`$INSTANCE_NAME`__LEFT == `$INSTANCE_NAME`_PWM_ALIGN)
                `$INSTANCE_NAME`_TRIG_CONTROL2_REG = `$INSTANCE_NAME`_PWM_MODE_LEFT;
            #endif  /* ( `$INSTANCE_NAME`_PWM_LEFT == `$INSTANCE_NAME`_PWM_ALIGN) */

            #if (`$INSTANCE_NAME`__RIGHT == `$INSTANCE_NAME`_PWM_ALIGN)
                `$INSTANCE_NAME`_TRIG_CONTROL2_REG = `$INSTANCE_NAME`_PWM_MODE_RIGHT;
            #endif  /* ( `$INSTANCE_NAME`_PWM_RIGHT == `$INSTANCE_NAME`_PWM_ALIGN) */

            #if (`$INSTANCE_NAME`__CENTER == `$INSTANCE_NAME`_PWM_ALIGN)
                `$INSTANCE_NAME`_TRIG_CONTROL2_REG = `$INSTANCE_NAME`_PWM_MODE_CENTER;
            #endif  /* ( `$INSTANCE_NAME`_PWM_CENTER == `$INSTANCE_NAME`_PWM_ALIGN) */

            #if (`$INSTANCE_NAME`__ASYMMETRIC == `$INSTANCE_NAME`_PWM_ALIGN)
                `$INSTANCE_NAME`_TRIG_CONTROL2_REG = `$INSTANCE_NAME`_PWM_MODE_ASYM;
            #endif  /* (`$INSTANCE_NAME`__ASYMMETRIC == `$INSTANCE_NAME`_PWM_ALIGN) */
        #endif  /* (`$INSTANCE_NAME`__PWM_PR == `$INSTANCE_NAME`_PWM_MODE) */

        /* Set other values from customizer */
        `$INSTANCE_NAME`_WritePeriod(`$INSTANCE_NAME`_PWM_PERIOD_VALUE );
        `$INSTANCE_NAME`_WriteCompare(`$INSTANCE_NAME`_PWM_COMPARE_VALUE);

        #if (1u == `$INSTANCE_NAME`_PWM_COMPARE_SWAP)
            `$INSTANCE_NAME`_SetCompareSwap(1u);
            `$INSTANCE_NAME`_WriteCompareBuf(`$INSTANCE_NAME`_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == `$INSTANCE_NAME`_PWM_COMPARE_SWAP) */

        #if (1u == `$INSTANCE_NAME`_PWM_PERIOD_SWAP)
            `$INSTANCE_NAME`_SetPeriodSwap(1u);
            `$INSTANCE_NAME`_WritePeriodBuf(`$INSTANCE_NAME`_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == `$INSTANCE_NAME`_PWM_PERIOD_SWAP) */
    #endif  /* (`$INSTANCE_NAME`__PWM_SEL == `$INSTANCE_NAME`_CONFIG) */
    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the `$INSTANCE_NAME`.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_BLOCK_CONTROL_REG |= `$INSTANCE_NAME`_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (`$INSTANCE_NAME`__PWM_SEL == `$INSTANCE_NAME`_CONFIG)
        #if (0u == `$INSTANCE_NAME`_PWM_START_SIGNAL_PRESENT)
            `$INSTANCE_NAME`_TriggerCommand(`$INSTANCE_NAME`_MASK, `$INSTANCE_NAME`_CMD_START);
        #endif /* (0u == `$INSTANCE_NAME`_PWM_START_SIGNAL_PRESENT) */
    #endif /* (`$INSTANCE_NAME`__PWM_SEL == `$INSTANCE_NAME`_CONFIG) */

    #if (`$INSTANCE_NAME`__TIMER == `$INSTANCE_NAME`_CONFIG)
        #if (0u == `$INSTANCE_NAME`_TC_START_SIGNAL_PRESENT)
            `$INSTANCE_NAME`_TriggerCommand(`$INSTANCE_NAME`_MASK, `$INSTANCE_NAME`_CMD_START);
        #endif /* (0u == `$INSTANCE_NAME`_TC_START_SIGNAL_PRESENT) */
    #endif /* (`$INSTANCE_NAME`__TIMER == `$INSTANCE_NAME`_CONFIG) */
    
    #if (`$INSTANCE_NAME`__QUAD == `$INSTANCE_NAME`_CONFIG)
        #if (0u != `$INSTANCE_NAME`_QUAD_AUTO_START)
            `$INSTANCE_NAME`_TriggerCommand(`$INSTANCE_NAME`_MASK, `$INSTANCE_NAME`_CMD_RELOAD);
        #endif /* (0u != `$INSTANCE_NAME`_QUAD_AUTO_START) */
    #endif  /* (`$INSTANCE_NAME`__QUAD == `$INSTANCE_NAME`_CONFIG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Initializes the `$INSTANCE_NAME` with default customizer
*  values when called the first time and enables the `$INSTANCE_NAME`.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time `$INSTANCE_NAME`_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the `$INSTANCE_NAME`_Start() routine.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the `$INSTANCE_NAME`.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_BLOCK_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the `$INSTANCE_NAME`. This function is used when
*  configured as a generic `$INSTANCE_NAME` and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the `$INSTANCE_NAME` to operate in
*   Values:
*   - `$INSTANCE_NAME`_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - `$INSTANCE_NAME`_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - `$INSTANCE_NAME`_MODE_QUAD - Quadrature decoder
*         - `$INSTANCE_NAME`_MODE_PWM - PWM
*         - `$INSTANCE_NAME`_MODE_PWM_DT - PWM with dead time
*         - `$INSTANCE_NAME`_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_MODE_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - `$INSTANCE_NAME`_MODE_X1 - Counts on phi 1 rising
*         - `$INSTANCE_NAME`_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - `$INSTANCE_NAME`_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_QUAD_MODE_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY2    - Divide by 2
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY4    - Divide by 4
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY8    - Divide by 8
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY16   - Divide by 16
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY32   - Divide by 32
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY64   - Divide by 64
*         - `$INSTANCE_NAME`_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_PRESCALER_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the `$INSTANCE_NAME` runs
*  continuously or stops when terminal count is reached.  By default the
*  `$INSTANCE_NAME` operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_ONESHOT_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint32)((oneShotEnable & `$INSTANCE_NAME`_1BIT_MASK) <<
                                                               `$INSTANCE_NAME`_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPWMMode(uint32 modeMask)
{
    `$INSTANCE_NAME`_TRIG_CONTROL2_REG = (modeMask & `$INSTANCE_NAME`_6BIT_MASK);
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_PWM_SYNC_KILL_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint32)((syncKillEnable & `$INSTANCE_NAME`_1BIT_MASK)  <<
                                               `$INSTANCE_NAME`_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_PWM_STOP_KILL_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint32)((stopOnKillEnable & `$INSTANCE_NAME`_1BIT_MASK)  <<
                                                         `$INSTANCE_NAME`_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_PRESCALER_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint32)((deadTime & `$INSTANCE_NAME`_8BIT_MASK) <<
                                                          `$INSTANCE_NAME`_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - `$INSTANCE_NAME`_INVERT_LINE   - Inverts the line output
*         - `$INSTANCE_NAME`_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_INV_OUT_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteCounter(uint32 count)
{
    `$INSTANCE_NAME`_COUNTER_REG = (count & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadCounter(void)
{
    return (`$INSTANCE_NAME`_COUNTER_REG & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - `$INSTANCE_NAME`_COUNT_UP       - Counts up
*     - `$INSTANCE_NAME`_COUNT_DOWN     - Counts down
*     - `$INSTANCE_NAME`_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - `$INSTANCE_NAME`_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_UPDOWN_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_WritePeriod(uint32 period)
{
    `$INSTANCE_NAME`_PERIOD_REG = (period & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadPeriod(void)
{
    return (`$INSTANCE_NAME`_PERIOD_REG & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_RELOAD_CC_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= (swapEnable & `$INSTANCE_NAME`_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_WritePeriodBuf(uint32 periodBuf)
{
    `$INSTANCE_NAME`_PERIOD_BUF_REG = (periodBuf & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadPeriodBuf(void)
{
    return (`$INSTANCE_NAME`_PERIOD_BUF_REG & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_CONTROL_REG &= (uint32)~`$INSTANCE_NAME`_RELOAD_PERIOD_MASK;
    `$INSTANCE_NAME`_CONTROL_REG |= ((uint32)((swapEnable & `$INSTANCE_NAME`_1BIT_MASK) <<
                                                            `$INSTANCE_NAME`_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteCompare(uint32 compare)
{
    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */

    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        currentMode = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_UPDOWN_MASK) >> `$INSTANCE_NAME`_UPDOWN_SHIFT);

        if (((uint32)`$INSTANCE_NAME`__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)`$INSTANCE_NAME`__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */
    
    `$INSTANCE_NAME`_COMP_CAP_REG = (compare & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadCompare(void)
{
    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */

    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        currentMode = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_UPDOWN_MASK) >> `$INSTANCE_NAME`_UPDOWN_SHIFT);
        
        regVal = `$INSTANCE_NAME`_COMP_CAP_REG;
        
        if (((uint32)`$INSTANCE_NAME`__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)`$INSTANCE_NAME`__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & `$INSTANCE_NAME`_16BIT_MASK);
    #else
        return (`$INSTANCE_NAME`_COMP_CAP_REG & `$INSTANCE_NAME`_16BIT_MASK);
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteCompareBuf(uint32 compareBuf)
{
    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */

    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        currentMode = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_UPDOWN_MASK) >> `$INSTANCE_NAME`_UPDOWN_SHIFT);

        if (((uint32)`$INSTANCE_NAME`__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)`$INSTANCE_NAME`__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */
    
    `$INSTANCE_NAME`_COMP_CAP_BUF_REG = (compareBuf & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadCompareBuf(void)
{
    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */

    #if (`$INSTANCE_NAME`_CY_TCPWM_4000)
        currentMode = ((`$INSTANCE_NAME`_CONTROL_REG & `$INSTANCE_NAME`_UPDOWN_MASK) >> `$INSTANCE_NAME`_UPDOWN_SHIFT);

        regVal = `$INSTANCE_NAME`_COMP_CAP_BUF_REG;
        
        if (((uint32)`$INSTANCE_NAME`__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)`$INSTANCE_NAME`__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & `$INSTANCE_NAME`_16BIT_MASK);
    #else
        return (`$INSTANCE_NAME`_COMP_CAP_BUF_REG & `$INSTANCE_NAME`_16BIT_MASK);
    #endif /* (`$INSTANCE_NAME`_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadCapture(void)
{
    return (`$INSTANCE_NAME`_COMP_CAP_REG & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadCaptureBuf(void)
{
    return (`$INSTANCE_NAME`_COMP_CAP_BUF_REG & `$INSTANCE_NAME`_16BIT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - `$INSTANCE_NAME`_TRIG_LEVEL     - Level
*     - `$INSTANCE_NAME`_TRIG_RISING    - Rising edge
*     - `$INSTANCE_NAME`_TRIG_FALLING   - Falling edge
*     - `$INSTANCE_NAME`_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_TRIG_CONTROL1_REG &= (uint32)~`$INSTANCE_NAME`_CAPTURE_MASK;
    `$INSTANCE_NAME`_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - `$INSTANCE_NAME`_TRIG_LEVEL     - Level
*     - `$INSTANCE_NAME`_TRIG_RISING    - Rising edge
*     - `$INSTANCE_NAME`_TRIG_FALLING   - Falling edge
*     - `$INSTANCE_NAME`_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_TRIG_CONTROL1_REG &= (uint32)~`$INSTANCE_NAME`_RELOAD_MASK;
    `$INSTANCE_NAME`_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << `$INSTANCE_NAME`_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - `$INSTANCE_NAME`_TRIG_LEVEL     - Level
*     - `$INSTANCE_NAME`_TRIG_RISING    - Rising edge
*     - `$INSTANCE_NAME`_TRIG_FALLING   - Falling edge
*     - `$INSTANCE_NAME`_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_TRIG_CONTROL1_REG &= (uint32)~`$INSTANCE_NAME`_START_MASK;
    `$INSTANCE_NAME`_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << `$INSTANCE_NAME`_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - `$INSTANCE_NAME`_TRIG_LEVEL     - Level
*     - `$INSTANCE_NAME`_TRIG_RISING    - Rising edge
*     - `$INSTANCE_NAME`_TRIG_FALLING   - Falling edge
*     - `$INSTANCE_NAME`_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_TRIG_CONTROL1_REG &= (uint32)~`$INSTANCE_NAME`_STOP_MASK;
    `$INSTANCE_NAME`_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << `$INSTANCE_NAME`_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - `$INSTANCE_NAME`_TRIG_LEVEL     - Level
*     - `$INSTANCE_NAME`_TRIG_RISING    - Rising edge
*     - `$INSTANCE_NAME`_TRIG_FALLING   - Falling edge
*     - `$INSTANCE_NAME`_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_TRIG_CONTROL1_REG &= (uint32)~`$INSTANCE_NAME`_COUNT_MASK;
    `$INSTANCE_NAME`_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << `$INSTANCE_NAME`_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - `$INSTANCE_NAME`_CMD_CAPTURE    - Trigger Capture/Switch command
*     - `$INSTANCE_NAME`_CMD_RELOAD     - Trigger Reload/Index command
*     - `$INSTANCE_NAME`_CMD_STOP       - Trigger Stop/Kill command
*     - `$INSTANCE_NAME`_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    `$INSTANCE_NAME`_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the `$INSTANCE_NAME`.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - `$INSTANCE_NAME`_STATUS_DOWN    - Set if counting down
*     - `$INSTANCE_NAME`_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadStatus(void)
{
    return ((`$INSTANCE_NAME`_STATUS_REG >> `$INSTANCE_NAME`_RUNNING_STATUS_SHIFT) |
            (`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - `$INSTANCE_NAME`_INTR_MASK_TC       - Terminal count mask
*     - `$INSTANCE_NAME`_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint32 interruptMask)
{
    `$INSTANCE_NAME`_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - `$INSTANCE_NAME`_INTR_MASK_TC       - Terminal count mask
*     - `$INSTANCE_NAME`_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetInterruptSourceMasked(void)
{
    return (`$INSTANCE_NAME`_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - `$INSTANCE_NAME`_INTR_MASK_TC       - Terminal count mask
*     - `$INSTANCE_NAME`_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetInterruptSource(void)
{
    return (`$INSTANCE_NAME`_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - `$INSTANCE_NAME`_INTR_MASK_TC       - Terminal count mask
*     - `$INSTANCE_NAME`_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask)
{
    `$INSTANCE_NAME`_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - `$INSTANCE_NAME`_INTR_MASK_TC       - Terminal count mask
*     - `$INSTANCE_NAME`_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask)
{
    `$INSTANCE_NAME`_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
