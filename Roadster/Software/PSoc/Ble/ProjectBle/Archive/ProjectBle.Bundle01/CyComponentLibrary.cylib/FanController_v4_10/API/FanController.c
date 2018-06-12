/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the API files for the FanController component.
*  The FanController component supports up to 16 pulse width modulator (PWM)
*  controlled 4-wire fans and through an intuitive graphical interface,
*  enabling designers to quickly configure the number of fans, their electro-
*  mechanical properties, organization into banks (if desired) and the control
*  algorithm type: firmware or hardware based.
*
*  Refer to AN66627 "PSoC(R) 3 and PSoC 5 - Intelligent Fan Controller" for
*  more details and example projects.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"

#if(CY_PSOC4)
    #include "`$INSTANCE_NAME`_DataSend.h"

    #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u)
        #include "`$INSTANCE_NAME`_FW_PWM1.h"
    #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 2u)
        #include "`$INSTANCE_NAME`_FW_PWM1.h"
        #include "`$INSTANCE_NAME`_FW_PWM2.h"
    #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 3u)
        #include "`$INSTANCE_NAME`_FW_PWM1.h"
        #include "`$INSTANCE_NAME`_FW_PWM2.h"
        #include "`$INSTANCE_NAME`_FW_PWM3.h"
    #else
        #include "`$INSTANCE_NAME`_FW_PWM1.h"
        #include "`$INSTANCE_NAME`_FW_PWM2.h"
        #include "`$INSTANCE_NAME`_FW_PWM3.h"
        #include "`$INSTANCE_NAME`_FW_PWM4.h"
    #endif /* (`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u) */

#endif /* (CY_PSOC4) */

#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    #include "`$INSTANCE_NAME`_PID_ISR.h"
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */


/*******************************************************************************
* Variables
*
* Fan Control Data Structure declaration and initialization can be found at the
* end of this file due to its large size.
********************************************************************************/
uint8   `$INSTANCE_NAME`_initVar = 0u;

#if (CY_PSOC4)
    uint16 `$INSTANCE_NAME`_alertMask = 0u;
    uint16 `$INSTANCE_NAME`_stallStatus = 0u;
#else
    
    /* Stores channel number of Tachometer out DMA */
    static uint8 `$INSTANCE_NAME`_TachOutDMA_channel = 0u;

    #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
        
        /* Stores channel number of Tachometer in DMA */
        static uint8 `$INSTANCE_NAME`_TachInDMA_channel = 0u;

    #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

#endif /* (CY_PSOC4) */

/* Arrays for storing PID parameters and saturation ranges */
#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    int16 `$INSTANCE_NAME`_pidA1[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    int16 `$INSTANCE_NAME`_pidA2[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    int16 `$INSTANCE_NAME`_pidA3[`$INSTANCE_NAME`_NUMBER_OF_FANS];

    uint32 `$INSTANCE_NAME`_outputSatL[`$INSTANCE_NAME`_NUMBER_OF_FANS];
    uint32 `$INSTANCE_NAME`_outputSatH[`$INSTANCE_NAME`_NUMBER_OF_FANS];
#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

#if(!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    /* An array to store desired fans speeds */
    uint16 `$INSTANCE_NAME`_desiredFansSpeed[`$INSTANCE_NAME`_NUMBER_OF_FANS];
#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */


/*******************************************************************************
* Private API Prototypes
********************************************************************************/
#if (!CY_PSOC4)
    static void  `$INSTANCE_NAME`_SetupDMA(void) CYREENTRANT;
    static uint8 `$INSTANCE_NAME`_TachOutDMA_DmaInitialize(uint8 burstCount, uint8 requestPerBurst,
                                                    uint16 upperSrcAddress, uint16 upperDestAddress) CYREENTRANT;
    static void  `$INSTANCE_NAME`_TachOutDMA_DmaRelease(void) CYREENTRANT;

    #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

        static uint8 `$INSTANCE_NAME`_TachInDMA_DmaInitialize(uint8 burstCount, uint8 requestPerBurst,
                                                        uint16 upperSrcAddress, uint16 upperDestAddress) CYREENTRANT;
        static void  `$INSTANCE_NAME`_TachInDMA_DmaRelease(void) CYREENTRANT;

    #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

#endif /* (!CY_PSOC4) */


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
*******************************************************************************
*
* Summary:
*  Initializes component if not already initialized, then re-enables it.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not already initialized, then initialize hardware and variables */
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
*******************************************************************************
*
* Summary:
*  Stop the fan controller component.  Disables all hardware sub-components,
*  drives fan outputs high and de-asserts the alert pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All PWM outputs to fans will be driven high (100% duty cycle).
*  Alert output de-asserted.
*
******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* Turn off the hardware sub-components */
    `$INSTANCE_NAME`_GLOBAL_CONTROL_REG = 0u;

    /* De-assert the alert pin */
    `$INSTANCE_NAME`_DisableAlert();

    #if (!CY_PSOC4)

        /* Release DMA resources */
        `$INSTANCE_NAME`_TachOutDMA_DmaRelease();

        #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
            `$INSTANCE_NAME`_TachInDMA_DmaRelease();
        #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

    #else

        /* Disable PWMs */
        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u)
            `$INSTANCE_NAME`_FW_PWM1_Stop();
        #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 2u)
            `$INSTANCE_NAME`_FW_PWM1_Stop();
            `$INSTANCE_NAME`_FW_PWM2_Stop();
        #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 3u)
            `$INSTANCE_NAME`_FW_PWM1_Stop();
            `$INSTANCE_NAME`_FW_PWM2_Stop();
            `$INSTANCE_NAME`_FW_PWM3_Stop();
        #else
            `$INSTANCE_NAME`_FW_PWM1_Stop();
            `$INSTANCE_NAME`_FW_PWM2_Stop();
            `$INSTANCE_NAME`_FW_PWM3_Stop();
            `$INSTANCE_NAME`_FW_PWM4_Stop();
        #endif /* (`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u) */

    #endif /* (!CY_PSOC4) */
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
*******************************************************************************
*
* Summary:
*  Sets up DMA channels and transaction descriptors. Configures PWMs and
*  Tachometer hardware blocks. Also it configures interrupts if they are used
*  in the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Allocates DMA channels and transaction descriptors (TDs).
*
******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint8 counti;
    uint8 interruptState;

    #if (!CY_PSOC4)
        
        /* Performs configuration of DMA used in the component */
        `$INSTANCE_NAME`_SetupDMA();

        /***********************************************************************
        * Initialize the PWMs
        ***********************************************************************/
        #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

            /* Configure hardware controlled PWMs */
            for (counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FANS; counti++)
            {
                /* 8-bit hardware controlled PWM */
                #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
                    /* Set max PWM period */
                    CY_SET_REG8(`$INSTANCE_NAME`_fanDriverRegs[counti].pwmPeriodReg, `$INSTANCE_NAME`_PWM_PERIOD);
                    /* Set max PWM duty cycle (must be <= PWM period) */
                    CY_SET_REG8(`$INSTANCE_NAME`_fanDriverRegs[counti].pwmMaxDutyReg, `$INSTANCE_NAME`_PWM_PERIOD);
                /* 10-bit hardware controlled PWM */
                #else
                    /* Set max PWM period */
                    CY_SET_REG16(`$INSTANCE_NAME`_fanDriverRegs[counti].pwmPeriodReg, `$INSTANCE_NAME`_PWM_PERIOD);
                    /* Set max PWM duty cycle (must be <= PWM period) */
                    CY_SET_REG16(`$INSTANCE_NAME`_fanDriverRegs[counti].pwmMaxDutyReg, `$INSTANCE_NAME`_PWM_PERIOD);
                #endif /* `$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */

                /* Set initial duty cycle */
                `$INSTANCE_NAME`_SetDutyCycle((counti + 1u), `$INSTANCE_NAME`_fanProperties[counti].initDuty);
                /* Set initial speed */
                `$INSTANCE_NAME`_SetDesiredSpeed((counti + 1u), `$INSTANCE_NAME`_fanProperties[counti].initRpm);

                /* Enable cnt7 to track speed regulation errors */
                CY_SET_REG8(`$INSTANCE_NAME`_fanDriverRegs[counti].errorCountReg,
                    CY_GET_REG8(`$INSTANCE_NAME`_fanDriverRegs[counti].errorCountReg) | `$INSTANCE_NAME`_COUNT7_ENABLE);
            }

        #else

            /* Configure firmware controlled PWMs */
            for (counti = 0u; counti < `$INSTANCE_NAME`_FANPWM_COUNT; counti++)
            {
                /* 8-bit firmware controlled PWM */
                #if (`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
                    CY_SET_REG8(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmPeriodReg, `$INSTANCE_NAME`_PWM_PERIOD);

                    interruptState = CyEnterCriticalSection();

                    CY_SET_REG8(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmAuxControlReg,
                        CY_GET_REG8(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmAuxControlReg) |
                            `$INSTANCE_NAME`_FANPWM_AUX_CTRL_FIFO0_CLR_8);

                    CyExitCriticalSection(interruptState);

                /* 10-bit firmware controlled PWM */
                #else
                    CY_SET_REG16(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmPeriodReg, `$INSTANCE_NAME`_PWM_PERIOD);

                    interruptState = CyEnterCriticalSection();

                    CY_SET_REG16(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmAuxControlReg,
                        CY_GET_REG16(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmAuxControlReg) |
                            `$INSTANCE_NAME`_FANPWM_AUX_CTRL_FIFO0_CLR_10);

                    CyExitCriticalSection(interruptState);

                #endif /* `$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */
            }

            for (counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS; counti++)
            {
                /* Set Desired speed to initial RPM from the customizer */
                `$INSTANCE_NAME`_SetDesiredSpeed((counti + 1u), `$INSTANCE_NAME`_fanProperties[counti].initRpm);
            }

        #endif /* ((`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) || (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)) */

    #else

        /***********************************************************************
        * Configure the PWMs (TCPWMs)
        ***********************************************************************/

        /* Initialize PWMs */
        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u)
            `$INSTANCE_NAME`_FW_PWM1_Init();
        #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 2u)
            `$INSTANCE_NAME`_FW_PWM1_Init();
            `$INSTANCE_NAME`_FW_PWM2_Init();
        #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 3u)
            `$INSTANCE_NAME`_FW_PWM1_Init();
            `$INSTANCE_NAME`_FW_PWM2_Init();
            `$INSTANCE_NAME`_FW_PWM3_Init();
        #else
            `$INSTANCE_NAME`_FW_PWM1_Init();
            `$INSTANCE_NAME`_FW_PWM2_Init();
            `$INSTANCE_NAME`_FW_PWM3_Init();
            `$INSTANCE_NAME`_FW_PWM4_Init();
        #endif /* (`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u) */

        for (counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS; counti++)
        {
            /* Set the hard-coded PWM period */
            CY_SET_REG32(`$INSTANCE_NAME`_fanPwmInitRegs[counti].pwmPeriodReg, `$INSTANCE_NAME`_PWM_PERIOD);

            #if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
                /* In Auto Firmware Mode it is required to set duty cycle directly on the
                * start.
                */
                `$INSTANCE_NAME`_SetDutyCycle((counti + 1u), `$INSTANCE_NAME`_fanProperties[counti].initDuty);
            #endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

            /* Set Desired speed to initial RPM from the customizer */
            `$INSTANCE_NAME`_SetDesiredSpeed((counti + 1u), `$INSTANCE_NAME`_fanProperties[counti].initRpm);
        }

    #endif /* (!CY_PSOC4) */

    /***********************************************************************
    * Initialize the Tachometer
    ***********************************************************************/

    interruptState = CyEnterCriticalSection();
    #if (CY_PSOC4)
        /* Clear the tachometer FIFO */
        `$INSTANCE_NAME`_TACH_CUNTER_AUX_CTL_REG |= `$INSTANCE_NAME`_TACH_COUNTER_FIFO_CLR;
        `$INSTANCE_NAME`_TACH_CUNTER_AUX_CTL_REG &= ((uint8) ~`$INSTANCE_NAME`_TACH_COUNTER_FIFO_CLR);
    #else
        /* Enable count7 hardware block to drive fan address */
        `$INSTANCE_NAME`_TACH_FAN_COUNTR_AUX_CTL_REG |= `$INSTANCE_NAME`_COUNT7_ENABLE;
    #endif /* (!CY_PSOC4) */
    (void)CyExitCriticalSection(interruptState);
    
    /* Initialize glitch filter counter */
    `$INSTANCE_NAME`_TACH_GLITCH_FILTER_PERIOD_REG = `$INSTANCE_NAME`_GLITCH_FILTER_VAL;

    #if((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u))

        /* Set the divider by 10 */
        `$INSTANCE_NAME`_DAMPING_COUNTER_DIVIDER_REG = `$INSTANCE_NAME`_DAMPING_FACTOR_DIVIDER_VAL;

        /* Init lower 8 bits of 16-bit Damping Factor Counter */
         `$INSTANCE_NAME`_TACH_DAMPING_PERIOD_LOW_LSB_REG = `$INSTANCE_NAME`_DAMPING_FACTOR_PERIOD_LOW;

        /* Init high 8 bits of 16-bit Damping Factor Counter */
        `$INSTANCE_NAME`_TACH_DAMPING_PERIOD_HIGH_LSB_REG = `$INSTANCE_NAME`_DAMPING_FACTOR_PERIOD_HIGH;

    #endif /* ((!`$INSTANCE_NAME`_IS_MANUAL_MODE) && (`$INSTANCE_NAME`_DAMPING_FACTOR > 0u)) */

    /***********************************************************************
    * Initialize the Alert Mask Register based on customizer defaults
    ***********************************************************************/
    `$INSTANCE_NAME`_SetAlertMask(`$INSTANCE_NAME`_INIT_ALERT_MASK);

    #if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
        /***********************************************************************
        * Set PID coefficients for fans
        ***********************************************************************/
        for(counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FANS; counti++)
        {
            /* Disable interrupts while updating PID constants */
            interruptState = CyEnterCriticalSection();

            /* Initialize both PID parameters and output saturation with
            * default values from the customizer.
            */
            `$INSTANCE_NAME`_pidA1[counti] = `$INSTANCE_NAME`_PID_A1;
            `$INSTANCE_NAME`_pidA2[counti] = `$INSTANCE_NAME`_PID_A2;
            `$INSTANCE_NAME`_pidA3[counti] = `$INSTANCE_NAME`_PID_A3;

            `$INSTANCE_NAME`_outputSatL[counti] = `$INSTANCE_NAME`_PID_OUTPUT_SAT_L;
            `$INSTANCE_NAME`_outputSatH[counti] = `$INSTANCE_NAME`_PID_OUTPUT_SAT_H;
            CyExitCriticalSection(interruptState);
        }
    #endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

    /***********************************************************************
    * Set up required interrupts
    ***********************************************************************/
    #if(CY_PSOC4)
        `$INSTANCE_NAME`_DataSend_StartEx(&`$INSTANCE_NAME`_DATA_SEND_ISR);
    #endif /* (CY_PSOC4) */

    #if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
        `$INSTANCE_NAME`_PID_ISR_StartEx(&`$INSTANCE_NAME`_PID_CONTROL_ISR);
    #endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
*******************************************************************************
*
* Summary:
*  Enables hardware blocks in the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 interruptState;

    #if(CY_PSOC4)
        /* Ehable PWMs */
        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u)
            `$INSTANCE_NAME`_FW_PWM1_Enable();
        #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 2u)
            `$INSTANCE_NAME`_FW_PWM1_Enable();
            `$INSTANCE_NAME`_FW_PWM2_Enable();
        #elif(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 3u)
            `$INSTANCE_NAME`_FW_PWM1_Enable();
            `$INSTANCE_NAME`_FW_PWM2_Enable();
            `$INSTANCE_NAME`_FW_PWM3_Enable();
        #else
            `$INSTANCE_NAME`_FW_PWM1_Enable();
            `$INSTANCE_NAME`_FW_PWM2_Enable();
            `$INSTANCE_NAME`_FW_PWM3_Enable();
            `$INSTANCE_NAME`_FW_PWM4_Enable();
        #endif /*(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS == 1u) */

    #endif /* (CY_PSOC4) */

    /* Write to control register based on customizer defaults */
    `$INSTANCE_NAME`_GLOBAL_CONTROL_REG = `$INSTANCE_NAME`_ENABLE | `$INSTANCE_NAME`_ALERT_PIN_ENABLE |
        ((uint8) (`$INSTANCE_NAME`_INIT_ALERT_ENABLE << `$INSTANCE_NAME`_ALERT_ENABLE_SHIFT));

    interruptState = CyEnterCriticalSection();

    /* Enable alerts from the Alert Status register */
    `$INSTANCE_NAME`_STATUS_ALERT_AUX_CTL_REG |= `$INSTANCE_NAME`_STATUS_ALERT_ENABLE;
    
    #if(!CY_PSOC4)
        
        /* Enable DMA channels for operation */
        (void) CyDmaChEnable(`$INSTANCE_NAME`_TachOutDMA_channel, 1u);
        
        #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
            (void) CyDmaChEnable(`$INSTANCE_NAME`_TachInDMA_channel, 1u);

        #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
    #endif /* !CY_PSOC4 */
        
    (void) CyExitCriticalSection(interruptState);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableAlert
*******************************************************************************
*
* Summary:
*  Enables alerts from this component. Specifically which alert sources are
*  enabled is configured using SetAlertMode() API.  This API only
*  enables alert conditions to propagate to the Fan Controller component
*  Alert output pin.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_EnableAlert(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableAlert")`
{
    uint8 interruptState = CyEnterCriticalSection();

    `$INSTANCE_NAME`_GLOBAL_CONTROL_REG |= `$INSTANCE_NAME`_ALERT_PIN_ENABLE;

    (void) CyExitCriticalSection(interruptState);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableAlert
*******************************************************************************
*
* Summary:
*  Disables alerts from this component. This API only disables alert
*  conditions from propagating to the fan controller component Alert output/pin
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_DisableAlert(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableAlert")`
{
    uint8 interruptState = CyEnterCriticalSection();

    `$INSTANCE_NAME`_GLOBAL_CONTROL_REG &= (uint8) ~`$INSTANCE_NAME`_ALERT_PIN_ENABLE;

    (void) CyExitCriticalSection(interruptState);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAlertMode
*******************************************************************************
*
* Summary:
*  Enables alert sources from the component.
*
* Parameters:
*  alertMode:
*   b0:   STALL_ALERT_ENABLE (1==Enable, 0==Disable)
*   b1:   SPEED_ALERT_ENABLE (1==Enable, 0==Disable)
*   b7-2: RESERVED (write with zeroes)
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_SetAlertMode(uint8 alertMode) `=ReentrantKeil($INSTANCE_NAME . "_SetAlertMode")`
{
    uint8 interruptState = CyEnterCriticalSection();

    `$INSTANCE_NAME`_GLOBAL_CONTROL_REG = (`$INSTANCE_NAME`_GLOBAL_CONTROL_REG &
            (uint8) ~`$INSTANCE_NAME`_ALERT_ENABLE_MASK) |
               ((uint8) (alertMode << `$INSTANCE_NAME`_ALERT_ENABLE_SHIFT) & `$INSTANCE_NAME`_ALERT_ENABLE_MASK);

    (void) CyExitCriticalSection(interruptState);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAlertMode
*******************************************************************************
*
* Summary:
* Returns enabled alert sources from this component.
*
* Parameters:
*  None
*
* Return:
*  alertMode:
*   b0:   STALL_ALERT_ENABLE (1==Enable, 0==Disable)
*   b1:   SPEED_ALERT_ENABLE (1==Enable, 0==Disable)
*   b7-2: RESERVED (write with zeroes)
*
* Side Effects:
*  None
*
****************************************************************************/
uint8 `$INSTANCE_NAME`_GetAlertMode(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertMode")`
{
    return((`$INSTANCE_NAME`_GLOBAL_CONTROL_REG & `$INSTANCE_NAME`_ALERT_ENABLE_MASK) >>
                `$INSTANCE_NAME`_ALERT_ENABLE_SHIFT);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAlertMask
*******************************************************************************
*
* Summary:
*  Sets the per fan Alert Mask for both Stall and Speed errors.
*
* Parameters:
*  alertMask (1==Enable Alert, 0==Disable Alert)
*   b0:   FAN1 ALERT ENABLE/DISABLE
*   b1:   FAN2 ALERT ENABLE/DISABLE
*   ...
*   b15:  FAN16 ALERT ENABLE/DISABLE
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_SetAlertMask(uint16 alertMask) `=ReentrantKeil($INSTANCE_NAME . "_SetAlertMask")`
{
    #if (CY_PSOC4)
        `$INSTANCE_NAME`_alertMask = alertMask;
    #else
        `$INSTANCE_NAME`_ALERT_MASK_LSB_CONTROL_REG = LO8(alertMask);

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
            `$INSTANCE_NAME`_ALERT_MASK_MSB_CONTROL_REG = HI8(alertMask);
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS > 8u */
    #endif /* (CY_PSOC4) */
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAlertMask
*******************************************************************************
*
* Summary:
*  Gets the current per fan Alert Mask for both Stall and Speed errors.
*
* Parameters:
*  None
*
* Return:
*  alertMask (1==Alert Enabled, 0==Alert Disabled)
*   b0:   FAN1 ALERT ENABLE/DISABLE
*   b1:   FAN2 ALERT ENABLE/DISABLE
*   ...
*   b15:  FAN16 ALERT ENABLE/DISABLE
*
* Side Effects:
*  None
*
****************************************************************************/
uint16 `$INSTANCE_NAME`_GetAlertMask(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertMask")`
{
    uint16 alertMask;

    #if (CY_PSOC4)
        alertMask = `$INSTANCE_NAME`_alertMask;
    #else
        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
            alertMask = (uint16)`$INSTANCE_NAME`_ALERT_MASK_LSB_CONTROL_REG |
                (uint16)((uint16)`$INSTANCE_NAME`_ALERT_MASK_MSB_CONTROL_REG << 8u);
        #else
            alertMask = (uint16)`$INSTANCE_NAME`_ALERT_MASK_LSB_CONTROL_REG;
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS > 8u */
    #endif /* (CY_PSOC4) */

    return(alertMask);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAlertSource
*******************************************************************************
*
* Summary:
*  Returns pending alert sources. The alert pin is not de-asserted through
*  this API call. If this API call returns a non-zero value, call the
*  GetFanStallStatus() or GetFanSpeedStatus() APIs to determine the exact
*  source of the alert and simultaneously de-assert the pending alert and
*  alert pin.
*
* Parameters:
*  None
*
* Return:
*  alertSource:
*   b0:   STALL_ALERT (1==Present, 0==Not Present)
*   b1:   SPEED_ALERT (1==Present, 0==Not Present)
*   b7-2: RESERVED (returns all zeroes)
*
* Side Effects:
*  None
*
****************************************************************************/
uint8 `$INSTANCE_NAME`_GetAlertSource(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAlertSource")`
{
    return ((`$INSTANCE_NAME`_ALERT_STATUS_REG & `$INSTANCE_NAME`_ALERT_STATUS_MASK));
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFanStallStatus
*******************************************************************************
*
* Summary:
*  Returns the stall status of all fans
*
* Parameters:
*  None
*
* Return:
*  stallStatus (1==Fan Stalled, 0=Fan OK)
*   b0:   FAN1 STALL
*   b1:   FAN2 STALL
*   ...
*   b15:  FAN16 STALL
*
* Side Effects:
*  Calling this API de-asserts the alert pin and clears all pending stall
*  status alerts.
*
******************************************************************************/
uint16 `$INSTANCE_NAME`_GetFanStallStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFanStallStatus")`
{
    uint16 stallStatus;

    #if (CY_PSOC4)
        stallStatus = `$INSTANCE_NAME`_stallStatus;

        /* Clear stall status for individual fans */
        `$INSTANCE_NAME`_stallStatus = 0u;

        /* Clear the common SW stall signal on the control register */
        `$INSTANCE_NAME`_GLOBAL_CONTROL_REG &= ((uint8) ~`$INSTANCE_NAME`_SW_STALL);
    #else
        
        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
            stallStatus = (uint16)`$INSTANCE_NAME`_STALL_ERROR_LSB_STATUS_REG |
                (uint16)((uint16)`$INSTANCE_NAME`_STALL_ERROR_MSB_STATUS_REG << 8u);
        #else
            stallStatus = (uint16)`$INSTANCE_NAME`_STALL_ERROR_LSB_STATUS_REG;
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS > 8u */
    #endif /* (CY_PSOC4) */
        
    return(stallStatus);
}


#if (!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetFanSpeedStatus
    *******************************************************************************
    *
    * Summary:
    *  Returns the speed regulation status of all fans.
    *  This API is not available if Firmware Controller fan control method is
    *  selected.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  speedStatus (1==Fan Speed Failure, 0=Fan OK)
    *   b0:   FAN1 SPEED REGULATION FAIL
    *   b1:   FAN2 SPEED REGULATION FAIL
    *   ...
    *   b15:  FAN16 SPEED REGULATION FAIL
    *
    * Side Effects:
    *  Calling this API de-asserts the alert pin and clears all pending speed
    *  regulation failure status alerts.
    *
    ******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetFanSpeedStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFanSpeedStatus")`
    {
        uint16 speedStatus;

        /* In case of Auto Hardware mode speed status is received from hardware
        * status register...
        */
        #if (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
            #if (`$INSTANCE_NAME`_NUMBER_OF_FANS > 8u)
                speedStatus = (uint16)`$INSTANCE_NAME`_SPEED_ERROR_LSB_STATUS_REG |
                    (uint16)((uint16)`$INSTANCE_NAME`_SPEED_ERROR_MSB_STATUS_REG << 8u);
            #else
                speedStatus = (uint16)`$INSTANCE_NAME`_SPEED_ERROR_LSB_STATUS_REG;
            #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS > 8u */
        #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

        /* ... in case of Auto Firmware mode the software status is used. */
        #if (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)

            speedStatus = `$INSTANCE_NAME`_speedStatus;

            /* Simulate clear-on-read status */
            `$INSTANCE_NAME`_speedStatus = 0u;
        #endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

        return(speedStatus);
    }

#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDutyCycle
*******************************************************************************
*
* Summary:
*  Sets the duty cycle of selected fan or bank in hundredths of a percent,
*  i.e. 5000=50% duty cycle. In hardware controlled fan mode, if manual duty
*  cycle control is desirable, call the OverrideAutomaticControl(true) API 
*  prior to calling this API.
*
* Parameters:
*  uint8 fanOrBankNumber
*   Valid range is 1-16 and should not exceed the number of fans or banks in the
*   system.
*
*  uint16 dutyCycle
*   dutyCycle is entered in hundredths of a percent, i.e. 5000=50% duty cycle
*   Valid range is 0 to 10000.
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_SetDutyCycle(uint8 fanOrBankNumber, uint16 dutyCycle)
        `=ReentrantKeil($INSTANCE_NAME . "_SetDutyCycle")`
{
    uint32 newCompare;      /* Needs to be 32-bit to allow for overflow during the math calculations */

    /* Make sure the Fan/Bank number is valid */
    if(fanOrBankNumber <= `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS)
    {
        newCompare = (`$INSTANCE_NAME`_PWM_PERIOD * (uint32) dutyCycle) / `$INSTANCE_NAME`_PWM_DUTY_DIVIDER;

        /* Make sure the Compare value is in range (user entered a valid duty
        * cycle value).
        */
        if(newCompare <= `$INSTANCE_NAME`_PWM_PERIOD)
        {
            #if (!CY_PSOC4)
                #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
                    CY_SET_REG8(`$INSTANCE_NAME`_fanDriverRegs[fanOrBankNumber - 1u].pwmSetDutyReg, (uint8)newCompare);
                #else
                    CY_SET_REG16(`$INSTANCE_NAME`_fanDriverRegs[fanOrBankNumber - 1u].pwmSetDutyReg, (uint16)newCompare);
                #endif /* `$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_fanDriverRegs[fanOrBankNumber - 1u].pwmSetDutyReg, newCompare);
            #endif /* (!CY_PSOC4) */
        }
    }
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDutyCycle
*******************************************************************************
*
* Summary:
*  Returns the current duty cycle of the selected fan or bank in hundredths
*  of a percent, i.e. 5000=50% duty cycle.
*
* Parameters:
*  uint8 fanOrBankNumber
*  Valid range is 1-16 and should not exceed the number of fans or banks in
*  the system.
*
* Return:
*  uint16 duyCycle
*  Current duty cycle in hundredths of a percent.
*
* Side Effects:
*  None
*
****************************************************************************/
uint16 `$INSTANCE_NAME`_GetDutyCycle(uint8 fanOrBankNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetDutyCycle")`
{
    uint16 duyCycle = 0u;

    if(fanOrBankNumber <= `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS)
    {
        #if (!CY_PSOC4)
            #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)
                duyCycle = (uint16)
                    ((((uint32) CY_GET_REG8(`$INSTANCE_NAME`_fanDriverRegs[fanOrBankNumber - 1u].pwmSetDutyReg))
                            * `$INSTANCE_NAME`_PWM_DUTY_DIVIDER) / `$INSTANCE_NAME`_PWM_PERIOD);
            #else
                duyCycle = (uint16)
                    (((uint32) CY_GET_REG16(`$INSTANCE_NAME`_fanDriverRegs[fanOrBankNumber - 1u].pwmSetDutyReg)
                                * `$INSTANCE_NAME`_PWM_DUTY_DIVIDER) / `$INSTANCE_NAME`_PWM_PERIOD);
            #endif /* `$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT */
        #else
            duyCycle = (uint16)
                (((uint32) CY_GET_REG32(`$INSTANCE_NAME`_fanDriverRegs[fanOrBankNumber - 1u].pwmSetDutyReg)
                        * `$INSTANCE_NAME`_PWM_DUTY_DIVIDER) / `$INSTANCE_NAME`_PWM_PERIOD);
        #endif /* (!CY_PSOC4) */
    }

    return(duyCycle);
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetDesiredSpeed
*******************************************************************************
*
* Summary:
*  Sets the desired RPM of specified fan. If the AcousticNoiseReduction
*  parameter is true (enabled via the component customizer) in hardware
*  controlled fan mode, the desired speed is converted to a fan rotation period
*  and written to SRAM for subsequent DMA into the tachometer block. If the
*  AcousticNoiseReduction parameter is false, the desired speed is converted to
*  a duty cycle and written directly into the PWM register for the selected fan.
*
* Parameters:
*  uint8 fanNumber
*  Valid range is 1-16 and should not exceed the number of fans in the system.
*
* uint16 rpm
*  Valid range is 500 to 25,000, but should not exceed the max RPM of the
*  selected fan.
*
* Return:
*  None
*
* Side Effects:
*  None
*
****************************************************************************/
void `$INSTANCE_NAME`_SetDesiredSpeed(uint8 fanNumber, uint16 rpm) `=ReentrantKeil($INSTANCE_NAME . "_SetDesiredSpeed")`
{
    uint32 overrideDuty;        /* Needs to be 32-bit to allow for overflow during the math calculations */
    uint16 currentSpeed;

    /* Check for valid Fan number */
    if(fanNumber <= `$INSTANCE_NAME`_NUMBER_OF_FANS)
    {
        /* Get the actual speed */
        currentSpeed = `$INSTANCE_NAME`_GetActualSpeed(fanNumber);

        /* 3 cases where we will directly write a new duty cycle in firmware: */
            /* Case 1) Manual Control fan mode */
        if((`$INSTANCE_NAME`_IS_MANUAL_MODE)   ||
            /* Case 2) Auto controlled fan mode and noise reduction is off */
            ((`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) &&
                (`$INSTANCE_NAME`_NOISE_REDUCTION_MODE == `$INSTANCE_NAME`_NOISE_REDUCTION_OFF)) ||
            /* Case 3) hardware controlled fan mode and new rpm is slower than current */
            ((`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) && (rpm < currentSpeed)))
        {
            /* Override hardware controlled fan mode temporarily to write new duty cycle */
            #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
                `$INSTANCE_NAME`_OverrideAutomaticControl(1u);
            #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

            /* Desired speed is slower than rpmA */
            if(rpm < `$INSTANCE_NAME`_fanProperties[fanNumber - 1u].rpmA)
            {
                overrideDuty =  (uint32)`$INSTANCE_NAME`_fanProperties[fanNumber - 1u].dutyA -
                                (((uint32)`$INSTANCE_NAME`_fanProperties[fanNumber - 1u].dutyRpmSlope *
                                   ((uint32)`$INSTANCE_NAME`_fanProperties[fanNumber - 1u].rpmA - (uint32)rpm)) / 100u);

                /* Check for math underflow */
                if(overrideDuty > 10000u)
                {
                    overrideDuty = 0u;
                }
            }

            /* Desired speed is faster than rpmA */
            else
            {
                overrideDuty =  (uint32)`$INSTANCE_NAME`_fanProperties[fanNumber - 1u].dutyA +
                                (((uint32)`$INSTANCE_NAME`_fanProperties[fanNumber - 1u].dutyRpmSlope *
                                   ((uint32)rpm - (uint32)`$INSTANCE_NAME`_fanProperties[fanNumber - 1u].rpmA)) / 100u);

                /* Check for math overflow */
                if(overrideDuty > 10000u)
                {
                    overrideDuty = 10000u;
                }
            }

            /* Set the newly calculated duty cycle */
            `$INSTANCE_NAME`_SetDutyCycle(fanNumber, (uint16) overrideDuty);
        }

        /* Set newly requested desired rpm including tolerance calculation and store
        * in SRAM for the tachometer block DMA controller.
        */
        #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

            `$INSTANCE_NAME`_fanControl.desiredPeriod[fanNumber - 1u] =
                (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
                    (uint32) ((uint32) rpm + (((uint32) rpm * `$INSTANCE_NAME`_TOLERANCE) /
                        `$INSTANCE_NAME`_TOLERANCE_DIVIDER)));

            if(rpm > 500u)
            {
                `$INSTANCE_NAME`_fanControl.tolerance[fanNumber - 1u] =
                    (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
                        `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (uint32) rpm);
            }
            else
            {
                `$INSTANCE_NAME`_fanControl.tolerance[fanNumber - 1u] = 100u;
            }

            /* Go back to hardware controlled fan mode */
            `$INSTANCE_NAME`_OverrideAutomaticControl(0u);

        #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
        
        /* Store the desired speed to RAM if we are in auto mode. It will be used by 
        * `$INSTANCE_NAME`_GetDesiredSpeed() and PID algorithm.
        */
        #if((`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) || (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE))
            `$INSTANCE_NAME`_desiredFansSpeed[fanNumber - 1u] = rpm;
        #endif /* (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) */
    }
}


#if (!`$INSTANCE_NAME`_IS_MANUAL_MODE)
    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetDesiredSpeed
    *******************************************************************************
    *
    * Summary:
    *  Returns the currently desired speed of the selected fan in RPMs in hardware
    *  controlled fan mode. This API is not available if firmware controlled fan
    *  mode is selected.
    *
    * Parameters:
    *  uint8 fanNumber
    *  Valid range is 1-16 and should not exceed the number of fans in the system.
    *
    * Return:
    *  uint16 desiredSpeed: Current desired speed for selected fan.
    *
    * Side Effects:
    *  None
    *
    ******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetDesiredSpeed(uint8 fanNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetDesiredSpeed")`
    {
        return(`$INSTANCE_NAME`_desiredFansSpeed[fanNumber - 1u]);
    }

#endif /* (!`$INSTANCE_NAME`_IS_MANUAL_MODE) */


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetActualSpeed
*******************************************************************************
*
* Summary:
*  Returns the actual measured RPM of selected fan. This function should be 
*  called first time in the design only after the requested fan is made a full
*  rotation. This can be ensured by calling the function after End-of-Cycle 
*  (eoc) pulse generation.
*
* Parameters:
*  uint8 fanNumber
*  Valid range is 1-16 and should not exceed the number of fans in the system.
*
* Return:
*  uint16 actualSpeed: Actual measured RPM of target fan.
*
* Side Effects:
*  None
*
****************************************************************************/
uint16 `$INSTANCE_NAME`_GetActualSpeed(uint8 fanNumber) `=ReentrantKeil($INSTANCE_NAME . "_GetActualSpeed")`
{
    uint16 actualSpeed = 0u;

    if(fanNumber <= `$INSTANCE_NAME`_NUMBER_OF_FANS)
    {
        #if(CY_PSOC3)

            if(0u != (`$INSTANCE_NAME`_DMA_STATUS_REG & `$INSTANCE_NAME`_DMA1))
            {
                /* If DMA writes to actualPeriodDma1 (DMA1 state) then read
                * actualPeriodDma2.
                */
                if(`$INSTANCE_NAME`_fanControl.actualPeriodDma2[fanNumber - 1u] != 0u)
                {
                    /* Calculate RPM from value measured by tachometer counter */
                    actualSpeed = (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
                        (uint32) `$INSTANCE_NAME`_fanControl.actualPeriodDma2[fanNumber - 1u]);
                }
            }
            else
            {
                /* If DMA writes to actualPeriodDma2 (DMA2 state) then read
                * actualPeriodDma1.
                */
                if(`$INSTANCE_NAME`_fanControl.actualPeriodDma1[fanNumber - 1u] != 0u)
                {
                    /* Calculate RPM from value measured bu tachometer counter */
                    actualSpeed = (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
                        (uint32) `$INSTANCE_NAME`_fanControl.actualPeriodDma1[fanNumber - 1u]);
                }
            }

        #else

            if(`$INSTANCE_NAME`_fanControl.actualPeriod[fanNumber - 1u] != 0u)
            {
                /* Calculate RPM from value measured by tachometer counter */
                actualSpeed = (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
                    (uint32) `$INSTANCE_NAME`_fanControl.actualPeriod[fanNumber - 1u]);
            }

        #endif /* (CY_PSOC3) */
    }

    return(actualSpeed);
}


#if (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_OverrideAutomaticControl
    *******************************************************************************
    *
    * Summary:
    *  Allows firmware to take over fan control when hardware controlled fan mode
    *  is enabled. That is, directly control fan speed using the SetDutyCycle() API.
    *  This API is not available if firmware controlled fan mode is selected.
    *
    * Parameters:
    *  uint8 override
    *   non-zero = firmware assumes control of fans
    *   zero     = hardware assumes control of fans
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    ******************************************************************************/

    void `$INSTANCE_NAME`_OverrideAutomaticControl(uint8 override)
                                `=ReentrantKeil($INSTANCE_NAME . "_OverrideAutomaticControl")`
    {
        uint8 interruptState = CyEnterCriticalSection();

        if(override != 0u)
        {
            `$INSTANCE_NAME`_GLOBAL_CONTROL_REG |= `$INSTANCE_NAME`_OVERRIDE;
        }
        else
        {
            `$INSTANCE_NAME`_GLOBAL_CONTROL_REG &= ((uint8) ~`$INSTANCE_NAME`_OVERRIDE);
        }

        CyExitCriticalSection(interruptState);
    }

#endif /* (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE) */


#if(`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE)
    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetSaturation
    *******************************************************************************
    *
    * Summary:
    *  Changes the PID controller output saturation. This bounds the output PWM to
    *  the fan and prevents what is known as integrator windup.
    *
    * Parameters:
    *  uint8 fanNum : Valid range is 1..16 but should not exceed the number of fans
    *                 in the system.
    *  uint16 satH  : The upper threshold for saturation. Valid range is 0 to
    *                 65535. A value of 0 represents 0% of the duty cycle. A value
    *                 of 65535 represents 100% duty cycle.
    *
    *  uint16 satL  : The lower threshold for saturation. Valid range is 0 to
    *                 65535. A value of 0 represents 0% of the duty cycle. A value
    *                 of 65535 represents 100% duty cycle.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    ****************************************************************************/
    void `$INSTANCE_NAME`_SetSaturation(uint8 fanNum, uint16 satH, uint16 satL)
                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetSaturation")`
    {
        uint8 interruptState;
        uint32 tmpOutL;
        uint32 tmpOutH;

        if((fanNum - 1u) < `$INSTANCE_NAME`_NUMBER_OF_FANS)
        {
            /* Calculate PID Constants for fan and store them into temporary variables to
            * be later written to PID vars. This is done so to not disable interrupt for a
            * long time.
            */
            tmpOutH = ((`$INSTANCE_NAME`_PWM_PERIOD * ((uint32) (((uint32) 1u) << `$INSTANCE_NAME`_PID_POST_GAIN))) /
                                           `$INSTANCE_NAME`_MAX_GAIN) * satH;
            tmpOutL = ((`$INSTANCE_NAME`_PWM_PERIOD * ((uint32) (((uint32) 1u) << `$INSTANCE_NAME`_PID_POST_GAIN))) /
                                           `$INSTANCE_NAME`_MAX_GAIN) * satL;

            /* Disable interrupts while updating PID constants */
            interruptState = CyEnterCriticalSection();

            `$INSTANCE_NAME`_outputSatH[fanNum - 1u] = tmpOutH;
            `$INSTANCE_NAME`_outputSatL[fanNum - 1u] = tmpOutL;

            CyExitCriticalSection(interruptState);
        }
    }


    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetPID
    *******************************************************************************
    *
    * Summary:
    *  Changes the PID controller coefficients for the controlled fan. The
    *  coefficients are integers that are proportional to the gain.
    *
    * Parameters:
    *  uint8 fanNum : Valid range is 1..16 but should not exceed the number of fans
    *                 in the system.
    *  uint16 kp    : Proportional gain. Valid range is 0 to 65535. A value of 0
    *                 represents 0% gain. A value of 65535 represents 100% gain.
    *
    *  uint16 ki    : Integral gain. Valid range is 0 to 65535. A value of 0
    *                 represents 0% gain. A value of 65535 represents 100% gain.
    *
    *  uint16 kd    : Derivative gain. Valid range is 0 to 65535. A value of 0
    *                 represents 0% gain. A value of 65535 represents 100% gain.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    ****************************************************************************/
    void `$INSTANCE_NAME`_SetPID(uint8 fanNum, uint16 kp, uint16 ki, uint16 kd)
                                                                        `=ReentrantKeil($INSTANCE_NAME . "_SetPID")`
    {
        uint8 interruptState;
        /* Variables for temporary storing of a calculated PID constants */
        int16 tmpA1;
        int16 tmpA2;
        int16 tmpA3;

        if((fanNum - 1u) < `$INSTANCE_NAME`_NUMBER_OF_FANS)
        {
            /* Calculate PID Constants for fan and store them into temporary variables to
            * be later written to PID vars. This is done so to not disable interrupt for a
            * long time.
            */
            tmpA1 = (int16) ((((int32) kp + (int32) ki + (int32) kd) * ((int32) `$INSTANCE_NAME`_GAIN_MULTIPLIER)) /
                    (int32) `$INSTANCE_NAME`_MAX_GAIN);
            tmpA2 = (int16) (((-((int32) kp + (2 * (int32) kd))) * ((int32) `$INSTANCE_NAME`_GAIN_MULTIPLIER )) /
                    (int32) `$INSTANCE_NAME`_MAX_GAIN);
            tmpA3 = (int16) ((((int32) kd) * ((int32) `$INSTANCE_NAME`_GAIN_MULTIPLIER )) /
                    (int32) `$INSTANCE_NAME`_MAX_GAIN);

            /* Disable interrupts while updating PID constants */
            interruptState = CyEnterCriticalSection();

            `$INSTANCE_NAME`_pidA1[fanNum - 1u] = tmpA1;
            `$INSTANCE_NAME`_pidA2[fanNum - 1u] = tmpA2;
            `$INSTANCE_NAME`_pidA3[fanNum - 1u] = tmpA3;

            CyExitCriticalSection(interruptState);
        }
    }


#endif /* (`$INSTANCE_NAME`_IS_AUTO_FIRMWARE_MODE) */

#if (!CY_PSOC4)

    /******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetupDMA
    *******************************************************************************
    *
    * Summary:
    *  This is a private API not exposed to users.
    *
    *  Sets up the DMA controllers depending on firmware or hardware controlled fan
    *  mode. The number and the sequence of the transaction descriptors depends on
    *  the number of fans in the system.
    *
    *  The NRQ output of the DMA controllers is used in different ways depending
    *  on the fan control mode:
    *
    *  1) In firmware controlled fan mode, the NRQ of the TachOutDMA is asserted
    *     only once at the end of the TD chain. This is used to generate the
    *     end-of-cylce (eoc) pulse for the component.
    *
    *  2) In hardware controlled fan mode, the NRQ of the TachOutDMA is asserted
    *     after every TD and connects to the DRQ of the TachInDMA. This ensures
    *     that reading desired speeds and hysteresis into the tachometer block
    *     occurs automatically when the fan input is changed. In this
    *     configuration, the NRQ output of the TachInDMA is used to generate the
    *     end-of-cylce (eoc) pulse for the component.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    ****************************************************************************/
    static void `$INSTANCE_NAME`_SetupDMA(void) CYREENTRANT
    {
        uint8 counti;
        uint8 fanNum;
        
        /* DMA transfer descriptors used by the tachometer block for fan speed 
        * control/reporting.
        */
        static `$INSTANCE_NAME`_fanTdOutStruct `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUM_OUT_TDS];
    
        #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

            /* DMA transfer descriptors used by the tachometer block for fan speed 
            * tunning. 
            */
            static `$INSTANCE_NAME`_fanTdInStruct `$INSTANCE_NAME`_fanInTds[`$INSTANCE_NAME`_NUMBER_OF_FANS];

        #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

        /* Get DMA controller channels allocated */
        /* PSoC 3 family memory spaces */
        #if defined(__C51__)

            `$INSTANCE_NAME`_TachOutDMA_channel =   `$INSTANCE_NAME`_TachOutDMA_DmaInitialize(
                                                    2u,
                                                    1u,
                                                    HI16(CYDEV_PERIPH_BASE),
                                                    HI16(CYDEV_SRAM_BASE));

            #if (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

                `$INSTANCE_NAME`_TachInDMA_channel =    `$INSTANCE_NAME`_TachInDMA_DmaInitialize(
                                                        2u,
                                                        1u,
                                                        HI16(CYDEV_SRAM_BASE),
                                                        HI16(CYDEV_PERIPH_BASE));
            #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

        /* PSoC 5 family memory spaces */
        #else

            `$INSTANCE_NAME`_TachOutDMA_channel =   `$INSTANCE_NAME`_TachOutDMA_DmaInitialize(
                                                    2u,
                                                    1u,
                                                    HI16(`$INSTANCE_NAME`_TACH_ACTUAL_PERIOD_PTR),
                                                    HI16(((uint32)&`$INSTANCE_NAME`_fanControl.actualPeriod[0])));

            #if (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

                `$INSTANCE_NAME`_TachInDMA_channel =    `$INSTANCE_NAME`_TachInDMA_DmaInitialize(
                                                        2u,
                                                        1u,
                                                        HI16(((uint32)&`$INSTANCE_NAME`_fanControl.desiredPeriod[0])),
                                                        HI16(`$INSTANCE_NAME`_TACH_DESIRED_PERIOD_PTR));
            #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
        #endif /* __C51__ */

        /* Get transaction descriptors allocated */
        for (counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FANS; counti++)
        {
            #if (CY_PSOC3)
                /* For PSoC 3 it is required to allocate two times more TDs */
                `$INSTANCE_NAME`_fanOutTds[counti].setActualPeriodTD = CyDmaTdAllocate();
                `$INSTANCE_NAME`_fanOutTds[counti + `$INSTANCE_NAME`_NUMBER_OF_FANS].setActualPeriodTD =
                        CyDmaTdAllocate();
            #else
                `$INSTANCE_NAME`_fanOutTds[counti].setActualPeriodTD = CyDmaTdAllocate();
            #endif /* (CY_PSOC3) */

            #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
                `$INSTANCE_NAME`_fanInTds[counti].getDesiredPeriodTD = CyDmaTdAllocate();
                `$INSTANCE_NAME`_fanInTds[counti].getToleranceTD = CyDmaTdAllocate();
            #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
        }

        /* Configure the transaction descriptors and sequence depending on fan control mode */
        for (counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FANS; counti++)
        {
            fanNum = `$INSTANCE_NAME`_NUMBER_OF_FANS - counti - 1u;

            /* Put current actual tachometer periods (hardware and firmware
            * controlled fan modes) to SRAM for the GetActualSpeed API.
            */
            if(fanNum == 0u)
            {
                /* TDs need to be sequenced in reverse to match the Tachometer hardware
                * block address bus sequence. Next TD after fan[0] is final fan:
                fan[NUMBER_OF_FANS-1].
                */
                #if (CY_PSOC3)

                    /* For PSoC 3 the DMA can write to two RAM locations and therefore it
                    * uses two times more TDs. The configuration is a bit complex.
                    * Short explanation is for a set of 16 fans the TD[0] will be chained to
                    * TD[31] and TD[16] will be chained to TD[15]. It's because TD[0] to TD[15]
                    * are used by DMA2 and TD[16] to TD[31] are used by DMA1. DMA1 will write
                    * measured data to .actualPeriodDma1[] and DMA2 will write to
                    * .actualPeriodDma2[].
                    */
                    (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanOutTds[fanNum].setActualPeriodTD,
                                            2u,
                                            `$INSTANCE_NAME`_fanOutTds[
                            (`$INSTANCE_NAME`_NUMBER_OF_FANS +`$INSTANCE_NAME`_NUMBER_OF_FANS) - 1u].setActualPeriodTD,
                                            TD_INC_DST_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG  |
                                            /* Assert NRQ at final TD in hardware and firmware controlled fan modes */
                                            `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN);

                    (void) CyDmaTdSetConfiguration(
                                `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUMBER_OF_FANS].setActualPeriodTD,
                                2u,
                                `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUMBER_OF_FANS - 1u].setActualPeriodTD,
                                TD_INC_DST_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG  |
                                /* Assert NRQ at final TD in hardware and firmware controlled fan modes */
                                `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN);

                #else

                    /* For PSoC 5LP or PSoC 4 there is no need of two TD sets */
                    (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanOutTds[fanNum].setActualPeriodTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUMBER_OF_FANS - 1u].setActualPeriodTD,
                                    TD_INC_DST_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG  |
                                    /* Assert NRQ at final TD in hardware and firmware controlled fan modes */
                                    `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN);

                #endif /* (CY_PSOC3) */
            }
            else
            {
                /* TDs need to be sequenced in reverse to match the Tachometer hardware
                * block address bus sequence. Next TD after fan[n] is fan[n-1].
                */
                #if (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
                    #if (CY_PSOC3)

                        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanOutTds[fanNum].setActualPeriodTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanOutTds[fanNum - 1u].setActualPeriodTD,
                                    TD_INC_DST_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG  |
                                    /* Also assert NRQ at end of each TD in hardware controlled fan mode */
                                    `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN);

                        (void) CyDmaTdSetConfiguration(
                            `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUMBER_OF_FANS + fanNum].setActualPeriodTD,
                            2u,
                            `$INSTANCE_NAME`_fanOutTds[
                                (`$INSTANCE_NAME`_NUMBER_OF_FANS + fanNum) - 1u].setActualPeriodTD,
                            TD_INC_DST_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG  |
                            /* Also assert NRQ at end of each TD in hardware controlled fan mode */
                            `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN);

                    #else

                        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanOutTds[fanNum].setActualPeriodTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanOutTds[fanNum - 1u].setActualPeriodTD,
                                    TD_INC_DST_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG  |
                                    /* Also assert NRQ at end of each TD in hardware controlled fan mode */
                                    `$INSTANCE_NAME`_TachOutDMA__TD_TERMOUT_EN);

                    #endif /* (CY_PSOC3) */

                #else
                    #if (CY_PSOC3)

                        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanOutTds[fanNum].setActualPeriodTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanOutTds[fanNum - 1u].setActualPeriodTD,
                                    TD_INC_DST_ADR |
                                    /* Don't assert NRQ at end of each TD in firmware controlled fan mode */
                                    `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG);

                        (void) CyDmaTdSetConfiguration(
                            `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUMBER_OF_FANS + fanNum].setActualPeriodTD,
                            2u,
                            `$INSTANCE_NAME`_fanOutTds[
                                (`$INSTANCE_NAME`_NUMBER_OF_FANS + fanNum) - 1u].setActualPeriodTD,
                            TD_INC_DST_ADR |
                            /* Don't assert NRQ at end of each TD in firmware controlled fan mode */
                            `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG);

                    #else

                        (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanOutTds[fanNum].setActualPeriodTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanOutTds[fanNum - 1u].setActualPeriodTD,
                                    TD_INC_DST_ADR |
                                    /* Don't assert NRQ at end of each TD in firmware controlled fan mode */
                                    `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG);

                    #endif /* (CY_PSOC3) */
                #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
            }

            /* Get desired tachometer periods and hysteresis (hardware controlled fan mode
            * only) from SRAM from the SetActualSpeed API.
            */
            #if (`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

                /* Get desired tachometer periods */
                (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanInTds[fanNum].getDesiredPeriodTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanInTds[fanNum].getToleranceTD,
                                    TD_INC_SRC_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG | TD_AUTO_EXEC_NEXT);

                /* And get tachometer tolerances - either chain to the next fan OR wrap around to the last fan */
                if(fanNum == 0u)
                {
                    /* Next TD after fan[0] is final fan: fan[NUMBER_OF_FANS-1] */
                    (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanInTds[fanNum].getToleranceTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanInTds[`$INSTANCE_NAME`_NUMBER_OF_FANS - 1u].getDesiredPeriodTD,
                                    TD_INC_SRC_ADR | `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG |
                                    `$INSTANCE_NAME`_TachInDMA__TD_TERMOUT_EN);  /* Assert NRQ at end of all TDs */
                }
                else
                {
                    /* Next TD after fan[n] is fan[n-1] */
                    (void) CyDmaTdSetConfiguration(`$INSTANCE_NAME`_fanInTds[fanNum].getToleranceTD,
                                    2u,
                                    `$INSTANCE_NAME`_fanInTds[fanNum - 1u].getDesiredPeriodTD,
                                    TD_INC_SRC_ADR |
                                    /* Don't assert NRQ on intermediate TDs */
                                    `$INSTANCE_NAME`_TD_SWAP_ENDIAN_FLAG);
                }
            #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
        }

        /* Setup SRAM source/destination addresses and datapath register addresses */
        for (counti = 0u; counti < `$INSTANCE_NAME`_NUMBER_OF_FANS; counti++)
        {
            /* TD for actual period to RAM */
            #if (CY_PSOC3)

                (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fanOutTds[counti].setActualPeriodTD,
                                  LO16(`$INSTANCE_NAME`_TACH_ACTUAL_PERIOD_PTR),
                                  LO16(((uint32) &`$INSTANCE_NAME`_fanControl.actualPeriodDma2[counti])));

                (void) CyDmaTdSetAddress(
                                `$INSTANCE_NAME`_fanOutTds[`$INSTANCE_NAME`_NUMBER_OF_FANS + counti].setActualPeriodTD,
                                LO16(`$INSTANCE_NAME`_TACH_ACTUAL_PERIOD_PTR),
                                LO16(((uint32) &`$INSTANCE_NAME`_fanControl.actualPeriodDma1[counti])));

            #else
                (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fanOutTds[counti].setActualPeriodTD,
                                  LO16(`$INSTANCE_NAME`_TACH_ACTUAL_PERIOD_PTR),
                                  LO16(((uint32) &`$INSTANCE_NAME`_fanControl.actualPeriod[counti])));
            #endif /* (CY_PSOC3) */

            #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

                /* TD for desired period to tachometer */
                (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fanInTds[counti].getDesiredPeriodTD,
                                LO16(((uint32) &`$INSTANCE_NAME`_fanControl.desiredPeriod[counti])),
                                LO16(`$INSTANCE_NAME`_TACH_DESIRED_PERIOD_PTR));

                /* TD for tolerance to tachometer */
                (void) CyDmaTdSetAddress(`$INSTANCE_NAME`_fanInTds[counti].getToleranceTD,
                                LO16(((uint32) &`$INSTANCE_NAME`_fanControl.tolerance[counti])),
                                LO16(`$INSTANCE_NAME`_TACH_TOLERANCE_PTR));

            #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
        }

        /* Set the initial transaction descriptor to kick things off */
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_TachOutDMA_channel,
                `$INSTANCE_NAME`_fanOutTds[0u].setActualPeriodTD);
                
        #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

            (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_TachInDMA_channel,
                    `$INSTANCE_NAME`_fanInTds[0u].getDesiredPeriodTD);

        #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
    }


    /*********************************************************************
    * Function Name: `$INSTANCE_NAME`_TachOutDMA_DmaInitalize
    **********************************************************************
    *
    * Summary:
    *  This is a private API not exposed to users.
    *
    *  Allocates and initializes a channel of the DMAC to be used by the
    *  caller.
    *
    * Parameters:
    *  uint8  burstCount
    *  uint8  requestPerBurst
    *  uint16 upperSrcAddress
    *  uint16 upperDestAddress
    *
    * Return:
    *  The channel that can be used by the caller for DMA activity.
    *  DMA_INVALID_CHANNEL (0xFF) if there are no channels left.
    *
    * Side Effects:
    *  None
    *
    *****************************************************************/
    static uint8 `$INSTANCE_NAME`_TachOutDMA_DmaInitialize(uint8 burstCount, uint8 requestPerBurst,
                                                        uint16 upperSrcAddress, uint16 upperDestAddress) CYREENTRANT
    {
        /* Allocate a DMA channel */
        uint8 tachOutDMA_dmaHandle = `$INSTANCE_NAME`_TachOutDMA__DRQ_NUMBER;

        if(tachOutDMA_dmaHandle != DMA_INVALID_CHANNEL)
        {
            /* Configure the channel */
            (void) CyDmaChSetConfiguration(tachOutDMA_dmaHandle,
                                    burstCount,
                                    requestPerBurst,
                                    `$INSTANCE_NAME`_TachOutDMA__TERMOUT0_SEL,
                                    `$INSTANCE_NAME`_TachOutDMA__TERMOUT1_SEL,
                                    `$INSTANCE_NAME`_TachOutDMA__TERMIN_SEL);

            /* Set the extended address for the transfers */
            (void) CyDmaChSetExtendedAddress(tachOutDMA_dmaHandle, upperSrcAddress, upperDestAddress);

            /* Set the priority for this channel */
            (void) CyDmaChPriority(tachOutDMA_dmaHandle, `$INSTANCE_NAME`_TachOutDMA__PRIORITY);
        }

        return(tachOutDMA_dmaHandle);
    }


    /*********************************************************************
    * Function Name: void `$INSTANCE_NAME`_TachOutDMA_DmaRelease
    **********************************************************************
    *
    * Summary:
    *   Frees the channel associated with `$INSTANCE_NAME`_TachOutDMA and
    *   also frees the TD descriptors.
    *
    * Parameters:
    *   None
    *
    * Return:
    *   None
    *
    * Side Effects:
    *  None
    *
    *****************************************************************/
    static void `$INSTANCE_NAME`_TachOutDMA_DmaRelease(void) CYREENTRANT
    {
        /* Disable the channel, even if someone just did! */
        (void) CyDmaChDisable(`$INSTANCE_NAME`_TachOutDMA_channel);
    }


    #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
        
        /*********************************************************************
        * Function Name: uint8 `$INSTANCE_NAME`_TachInDMA_DmaInitalize
        **********************************************************************
        *
        * Summary:
        *   Allocates and initializes a channel of the DMAC to be used by the
        *   caller.
        *
        * Parameters:
        *  uint8  burstCount
        *  uint8  requestPerBurst
        *  uint16 upperSrcAddress
        *  uint16 upperDestAddress
        *
        * Return:
        *  The channel that can be used by the caller for DMA activity.
        *  DMA_INVALID_CHANNEL (0xFF) if there are no channels left.
        *
        * Side Effects:
        *  None
        *
        *******************************************************************/
        static uint8 `$INSTANCE_NAME`_TachInDMA_DmaInitialize(uint8 burstCount, uint8 requestPerBurst,
                                        uint16 upperSrcAddress,   uint16 upperDestAddress) CYREENTRANT
        {
            /* Allocate a DMA channel */
            uint8 tachInDMA_dmaHandle = `$INSTANCE_NAME`_TachInDMA__DRQ_NUMBER;

            if(tachInDMA_dmaHandle != DMA_INVALID_CHANNEL)
            {
                /* Configure the channel */
                (void) CyDmaChSetConfiguration(tachInDMA_dmaHandle,
                                        burstCount,
                                        requestPerBurst,
                                        `$INSTANCE_NAME`_TachInDMA__TERMOUT0_SEL,
                                        `$INSTANCE_NAME`_TachInDMA__TERMOUT1_SEL,
                                        `$INSTANCE_NAME`_TachInDMA__TERMIN_SEL);

                /* Set the extended address for the transfers */
                (void) CyDmaChSetExtendedAddress(tachInDMA_dmaHandle, upperSrcAddress, upperDestAddress);

                /* Set the priority for this channel */
                (void) CyDmaChPriority(tachInDMA_dmaHandle, `$INSTANCE_NAME`_TachInDMA__PRIORITY);
            }

            return(tachInDMA_dmaHandle);
        }

        /*********************************************************************
        * Function Name: void `$INSTANCE_NAME`_TachInDMA_DmaRelease
        **********************************************************************
        *
        * Summary:
        *   Frees the channel associated with `$INSTANCE_NAME`_TachInDMA and
        *   also frees the TD descriptors
        *
        * Parameters:
        *   None
        *
        * Return:
        *   None
        *
        * Side Effects:
        *  None
        *
        *******************************************************************/
        static void `$INSTANCE_NAME`_TachInDMA_DmaRelease(void) CYREENTRANT
        {
            /* Disable the channel, even if someone just did! */
            (void) CyDmaChDisable(`$INSTANCE_NAME`_TachInDMA_channel);
        }

    #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

#endif /* (!CY_PSOC4) */

/*****************************************************************************
* PWM Data Structure Initialization
*****************************************************************************/
#if (!CY_PSOC4)
    #if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)

        /***********************************************************************
        * Hardware Controlled PWM Control Registers (8-bit)
        ***********************************************************************/
        #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)

            const `$INSTANCE_NAME`_fanDriverRegsStruct CYCODE
                `$INSTANCE_NAME`_fanDriverRegs[`$INSTANCE_NAME`_NUMBER_OF_FANS] =
            {
                #if (`$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif  /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_PWM8_ClosedLoopFan8_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_PWM8_ClosedLoopFan8_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_PWM8_ClosedLoopFan8_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    }
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u */
            };

        /***********************************************************************
        * Hardware Controlled PWM Control Registers (10-bit)
        ***********************************************************************/
        #else

            const `$INSTANCE_NAME`_fanDriverRegsStruct CYCODE 
                `$INSTANCE_NAME`_fanDriverRegs[`$INSTANCE_NAME`_NUMBER_OF_FANS] =
            {
                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_Fan_1_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN2_Fan_2_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN3_Fan_3_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN4_Fan_4_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN5_Fan_5_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN6_Fan_6_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN7_Fan_7_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN8_Fan_8_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN9_Fan_9_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN10_Fan_10_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN11_Fan_11_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN12_Fan_12_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN13_Fan_13_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN14_Fan_14_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN15_Fan_15_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_PWM10_ClosedLoopFan10_u0__D1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_PWM10_ClosedLoopFan10_u0__D0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_PWM10_ClosedLoopFan10_u0__A0_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_CLOSED_LOOP_FAN16_Fan_16_SpeedErrorCounter__CONTROL_AUX_CTL_REG
                    }
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u */
            };

        #endif /* Hardware Controlled Fan Mode */

    #else

        /***********************************************************************
        * Firmware Controlled PWM Control Registers (8-bit)
        ***********************************************************************/
        #if(`$INSTANCE_NAME`_PWMRES == `$INSTANCE_NAME`_PWMRES_EIGHTBIT)

            const `$INSTANCE_NAME`_fanDriverRegsStruct CYCODE
            `$INSTANCE_NAME`_fanDriverRegs[`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS] =
            {
                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 6u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 6u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 8u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 8u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 10u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 10u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 12u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 12u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 14u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM8_OpenLoopFan8_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 14u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM8_OpenLoopFan8_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 16u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM8_OpenLoopFan8_u0__F1_REG
                    }
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 16u */
            };

            const `$INSTANCE_NAME`_fanPwmInitRegsStruct CYCODE
            `$INSTANCE_NAME`_fanPwmInitRegs[`$INSTANCE_NAME`_FANPWM_COUNT] =
            {
                #if `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7 */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13 */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM8_OpenLoopFan8_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM8_OpenLoopFan8_u0__DP_AUX_CTL_REG
                    }
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u */
            };

        /***********************************************************************
        * Firmware Controlled PWM Control Registers (10-bit)
        ***********************************************************************/
        #else

            const `$INSTANCE_NAME`_fanDriverRegsStruct CYCODE
                `$INSTANCE_NAME`_fanDriverRegs[`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS] =
            {
                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2 */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 6u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 6u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 8u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 8u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 10u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 10u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 12u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 12u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 14u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM10_OpenLoopFan10_u0__F1_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 14u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM10_OpenLoopFan10_u0__F0_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 16u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM10_OpenLoopFan10_u0__F1_REG
                    }
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 16u */
            };

            const `$INSTANCE_NAME`_fanPwmInitRegsStruct CYCODE
                `$INSTANCE_NAME`_fanPwmInitRegs[`$INSTANCE_NAME`_FANPWM_COUNT] =
            {
                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FanPWM_1_2_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN34_FanPWM_3_4_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN56_FanPWM_5_6_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 5u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN78_FanPWM_7_8_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 7u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN910_FanPWM_9_10_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 9u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1112_FanPWM_11_12_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 11u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1314_FanPWM_13_14_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    },
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 13u */

                #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u)
                    {
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM10_OpenLoopFan10_u0__A1_REG,
                        `$INSTANCE_NAME`_B_FanCtrl_OPEN_LOOP_FAN1516_FanPWM_15_16_PWM10_OpenLoopFan10_u0__DP_AUX_CTL_REG
                    }
                #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 15u */
            };

        #endif    /* 10-bit Resolution */
    #endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */

#else  /* PSoC 4 */

    const `$INSTANCE_NAME`_fanDriverRegsStruct CYCODE
        `$INSTANCE_NAME`_fanDriverRegs[`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS] =
    {
        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u)
            {
                `$INSTANCE_NAME`_FW_PWM1_cy_m0s8_tcpwm_1__CC
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u)
            {
                `$INSTANCE_NAME`_FW_PWM2_cy_m0s8_tcpwm_1__CC
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u)
            {
                `$INSTANCE_NAME`_FW_PWM3_cy_m0s8_tcpwm_1__CC
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u)
            {
                `$INSTANCE_NAME`_FW_PWM4_cy_m0s8_tcpwm_1__CC
            }
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u */
    };

    const  `$INSTANCE_NAME`_fanPwmInitRegsStruct CYCODE 
        `$INSTANCE_NAME`_fanPwmInitRegs[`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS] =
    {
        #if `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u
            {
                `$INSTANCE_NAME`_FW_PWM1_cy_m0s8_tcpwm_1__PERIOD
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 1u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u)
            {
                `$INSTANCE_NAME`_FW_PWM2_cy_m0s8_tcpwm_1__PERIOD
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 2u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u)
            {
                `$INSTANCE_NAME`_FW_PWM3_cy_m0s8_tcpwm_1__PERIOD
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 3u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4u)
            {
                `$INSTANCE_NAME`_FW_PWM4_cy_m0s8_tcpwm_1__PERIOD
            },
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FAN_OUTPUTS >= 4 */
    };

#endif /* (!CY_PSOC4) */

/*****************************************************************************
* Hardware Controlled Fan Mode Fan Control Data Structure Initialization
*****************************************************************************/
`$INSTANCE_NAME`_fanControlStruct `$INSTANCE_NAME`_fanControl
#if(`$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE)
= {
    {
        /* Initialize the Desired Period Field (RPM B scaled up by tolerance factor %) */
        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM01`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM01`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM02`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM02`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM03`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM03`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM04`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM04`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 4 */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 5)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM05`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM05`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM06`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM06`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM07`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM07`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM08`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM08`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM09`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM09`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM10`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM10`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM11`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM11`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM12`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM12`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM13`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM13`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM14`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM14`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM15`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM15`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 15 */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u)
            (uint16) (`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR /
            (`$MaxRPM16`u + ((`$INSTANCE_NAME`_TOLERANCE * `$MaxRPM16`u)/ `$INSTANCE_NAME`_TOLERANCE_DIVIDER))),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u */
    },
    {
        /* Initialize the Tolerance Field (% of RPM B) */
        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM01`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM02`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM03`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM04`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM05`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM06`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM07`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM08`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM09`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 10)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM10`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM11`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM12`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 12 */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM13`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM14`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM15`u)),
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u */

        #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u)
            (uint16) (((`$INSTANCE_NAME`_RPM_PERIOD_CONV_FACTOR * `$INSTANCE_NAME`_TOLERANCE) /
              `$INSTANCE_NAME`_TOLERANCE_DIVIDER) / (`$MaxRPM16`u))
        #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u */
    }
}
#endif /* `$INSTANCE_NAME`_IS_AUTO_HARDWARE_MODE */
;

/*****************************************************************************
* Fan Electromechanical Properties Data Structure Initialization
*****************************************************************************/
 /* Properties come from customizer GUI */
`$INSTANCE_NAME`_fanPropertiesStruct `$INSTANCE_NAME`_fanProperties[`$INSTANCE_NAME`_NUMBER_OF_FANS] =
{
    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u)
        {
            `$MinRPM01`u,
            `$MaxRPM01`u,
            (`$MinDuty01`u * 100u),
            (`$MaxDuty01`u * 100u),
            (((`$MaxDuty01`u - `$MinDuty01`u) * 100u) / ((`$MaxRPM01`u - `$MinRPM01`u) / 100u)),
            `$InitialRPM01`u,
            (`$InitialDutyCycle01`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 1u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 2u)
        {
            `$MinRPM02`u,
            `$MaxRPM02`u,
            (`$MinDuty02`u * 100u),
            (`$MaxDuty02`u * 100u),
            (((`$MaxDuty02`u - `$MinDuty02`u) * 100u) / ((`$MaxRPM02`u - `$MinRPM02`u) / 100u)),
            `$InitialRPM02`u,
            (`$InitialDutyCycle02`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 2 */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u)
        {
            `$MinRPM03`u,
            `$MaxRPM03`u,
            (`$MinDuty03`u * 100u),
            (`$MaxDuty03`u * 100u),
            (((`$MaxDuty03`u - `$MinDuty03`u) * 100u) / ((`$MaxRPM03`u - `$MinRPM03`u) / 100u)),
            `$InitialRPM03`u,
            (`$InitialDutyCycle03`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 3u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u)
        {
            `$MinRPM04`u,
            `$MaxRPM04`u,
            (`$MinDuty04`u * 100u),
            (`$MaxDuty04`u * 100u),
            (((`$MaxDuty04`u - `$MinDuty04`u) * 100u) / ((`$MaxRPM04`u - `$MinRPM04`u) / 100u)),
            `$InitialRPM04`u,
            (`$InitialDutyCycle04`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 4u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u)
        {
            `$MinRPM05`u,
            `$MaxRPM05`u,
            (`$MinDuty05`u * 100u),
            (`$MaxDuty05`u * 100u),
            (((`$MaxDuty05`u - `$MinDuty05`u) * 100u) / ((`$MaxRPM05`u - `$MinRPM05`u) / 100u)),
            `$InitialRPM05`u,
            (`$InitialDutyCycle05`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 5u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u)
        {
            `$MinRPM06`u,
            `$MaxRPM06`u,
            (`$MinDuty06`u * 100u),
            (`$MaxDuty06`u * 100u),
            (((`$MaxDuty06`u - `$MinDuty06`u) * 100u) / ((`$MaxRPM06`u - `$MinRPM06`u) / 100u)),
            `$InitialRPM06`u,
            (`$InitialDutyCycle06`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 6u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u)
        {
            `$MinRPM07`u,
            `$MaxRPM07`u,
            (`$MinDuty07`u * 100u),
            (`$MaxDuty07`u * 100u),
            (((`$MaxDuty07`u - `$MinDuty07`u) * 100u) / ((`$MaxRPM07`u - `$MinRPM07`u) / 100u)),
            `$InitialRPM07`u,
            (`$InitialDutyCycle07`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 7u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u)
        {
            `$MinRPM08`u,
            `$MaxRPM08`u,
            (`$MinDuty08`u * 100u),
            (`$MaxDuty08`u * 100u),
            (((`$MaxDuty08`u - `$MinDuty08`u) * 100u) / ((`$MaxRPM08`u - `$MinRPM08`u) / 100u)),
            `$InitialRPM08`u,
            (`$InitialDutyCycle08`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 8u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u)
        {
            `$MinRPM09`u,
            `$MaxRPM09`u,
            (`$MinDuty09`u * 100u),
            (`$MaxDuty09`u * 100u),
            (((`$MaxDuty09`u - `$MinDuty09`u) * 100u) / ((`$MaxRPM09`u - `$MinRPM09`u) / 100u)),
            `$InitialRPM09`u,
            (`$InitialDutyCycle09`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 9u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u)
        {
            `$MinRPM10`u,
            `$MaxRPM10`u,
            (`$MinDuty10`u * 100u),
            (`$MaxDuty10`u * 100u),
            (((`$MaxDuty10`u - `$MinDuty10`u) * 100u) / ((`$MaxRPM10`u - `$MinRPM10`u) / 100u)),
            `$InitialRPM10`u,
            (`$InitialDutyCycle10`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 10u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u)
        {
            `$MinRPM11`u,
            `$MaxRPM11`u,
            (`$MinDuty11`u * 100u),
            (`$MaxDuty11`u * 100u),
            (((`$MaxDuty11`u - `$MinDuty11`u) * 100u) / ((`$MaxRPM11`u - `$MinRPM11`u) / 100u)),
            `$InitialRPM11`u,
            (`$InitialDutyCycle11`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 11u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u)
        {
            `$MinRPM12`u,
            `$MaxRPM12`u,
            (`$MinDuty12`u * 100u),
            (`$MaxDuty12`u * 100u),
            (((`$MaxDuty12`u - `$MinDuty12`u) * 100u) / ((`$MaxRPM12`u - `$MinRPM12`u) / 100u)),
            `$InitialRPM12`u,
            (`$InitialDutyCycle12`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 12u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u)
        {
            `$MinRPM13`u,
            `$MaxRPM13`u,
            (`$MinDuty13`u * 100u),
            (`$MaxDuty13`u * 100u),
            (((`$MaxDuty13`u - `$MinDuty13`u) * 100u) / ((`$MaxRPM13`u - `$MinRPM13`u) / 100u)),
            `$InitialRPM13`u,
            (`$InitialDutyCycle13`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 13u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u)
        {
            `$MinRPM14`u,
            `$MaxRPM14`u,
            (`$MinDuty14`u * 100u),
            (`$MaxDuty14`u * 100u),
            (((`$MaxDuty14`u - `$MinDuty14`u) * 100u) / ((`$MaxRPM14`u - `$MinRPM14`u) / 100u)),
            `$InitialRPM14`u,
            (`$InitialDutyCycle14`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 14u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u)
        {
            `$MinRPM15`u,
            `$MaxRPM15`u,
            (`$MinDuty15`u * 100u),
            (`$MaxDuty15`u * 100u),
            (((`$MaxDuty15`u - `$MinDuty15`u) * 100u) / ((`$MaxRPM15`u - `$MinRPM15`u) / 100u)),
            `$InitialRPM15`u,
            (`$InitialDutyCycle15`u * 100u)
        },
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 15u */

    #if(`$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u)
        {
            `$MinRPM16`u,
            `$MaxRPM16`u,
            (`$MinDuty16`u * 100u),
            (`$MaxDuty16`u * 100u),
            (((`$MaxDuty16`u - `$MinDuty16`u) * 100u) / ((`$MaxRPM16`u - `$MinRPM16`u) / 100u)),
             `$InitialRPM16`u,
            (`$InitialDutyCycle16`u * 100u)
        }
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_FANS >= 16u */
};


/* [] END OF FILE */
