/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Low Power Comparator
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"
#include "cyPm.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;
static uint32 `$INSTANCE_NAME`_internalIntr = 0u;
#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #if(CY_IP_SRSSV2)
        /* This variable saves INTR_MASK register since it get reset after wakeup 
        * from Hibernate. Attribute CY_NOINIT puts SRAM variable in memory section 
        * which is retained in low power modes 
        */
        CY_NOINIT static uint32 `$INSTANCE_NAME`_intrMaskRegState;
    #endif /* (CY_IP_SRSSV2) */
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  power to the block. The first time the routine is executed, the component is
*  initialized to the configuration from the customizer. When called to restart
*  the comparator following a `$INSTANCE_NAME`_Stop() call, the current
*  component parameter settings are retained.
*
* Parameters:
*   None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
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
*  Initializes or restores the component according to the customizer settings.
*  It is not necessary to call `$INSTANCE_NAME`_Init() because the
*  `$INSTANCE_NAME`_Start() API calls this function and is the preferred method
*  to begin component operation.
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
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_REG_DEFAULT;
    `$INSTANCE_NAME`_internalIntr = `$INSTANCE_NAME`_GET_CONFIG_INTR(`$INSTANCE_NAME`_INTERRUPT);
    
    #if (`$INSTANCE_NAME`_CY_LPCOMP_V2)
        #if(CY_IP_SRSSV2)
            if (CySysPmGetResetReason() == CY_PM_RESET_REASON_WAKEUP_HIB)
            {
                /* Restore the INTR_MASK register state since it get reset after 
                * wakeup from Hibernate.  
                */
                `$INSTANCE_NAME`_INTR_MASK_REG |= `$INSTANCE_NAME`_intrMaskRegState;  
            }
            else
            {
                `$INSTANCE_NAME`_INTR_MASK_REG |= `$INSTANCE_NAME`_INTR_MASK_REG_DEFAULT;    
                `$INSTANCE_NAME`_intrMaskRegState = `$INSTANCE_NAME`_INTR_MASK_REG;
            }
        #else
            `$INSTANCE_NAME`_INTR_MASK_REG |= `$INSTANCE_NAME`_INTR_MASK_REG_DEFAULT;
        #endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */
    #endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */
    
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call `$INSTANCE_NAME`_Enable() because the `$INSTANCE_NAME`_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.
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
    `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_EN;
    
    /*******************************************************
    * When the Enable() API is called the CONFIG_EN bit is set. 
    * This can cause fake interrupt because of the output delay 
    * of the analog. This requires setting the CONFIG_INTR bits 
    * after the CONFIG_EN bit is set.
    *******************************************************/
    `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_internalIntr;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Turns off the LP Comparator.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  The function doesn't change component Speed settings.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    #if (`$INSTANCE_NAME`_CY_LPCOMP_V0)
        /*******************************************************
        * When the Stop() API is called the CONFIG_EN bit is 
        * cleared. This causes the output of the comparator to go 
        * low. If the comparator output was high and the Interrupt 
        * Configuration is set for Falling edge disabling the 
        * comparator will cause an fake interrupt. This requires 
        * to clear the CONFIG_INTR bits before the CONFIG_EN bit 
        * is cleared.
        *******************************************************/
        `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_INTR_MASK;
    #endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V0) */

    `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_EN;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
*
* Summary:
*  Sets the drive power and speed to one of three settings.
*
* Parameters:
*  uint32 speed: Sets operation mode of the component:
*   `$INSTANCE_NAME`_LOW_SPEED  - Slow/ultra low 
*   `$INSTANCE_NAME`_MED_SPEED  - Medium/low 
*   `$INSTANCE_NAME`_HIGH_SPEED - Fast/normal 
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint32 speed)
{
    uint32 config;
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    config = `$INSTANCE_NAME`_CONFIG_REG & (uint32)~`$INSTANCE_NAME`_CONFIG_SPEED_MODE_MASK;
    `$INSTANCE_NAME`_CONFIG_REG = config | `$INSTANCE_NAME`_GET_CONFIG_SPEED_MODE(speed);
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt edge detect mode. This also controls the value provided
*  on the output.
*
* Parameters:
*  uint32 mode: Enumerated edge detect mode value:
*  `$INSTANCE_NAME`_INTR_DISABLE - Disable
*  `$INSTANCE_NAME`_INTR_RISING  - Rising edge detect
*  `$INSTANCE_NAME`_INTR_FALLING - Falling edge detect
*  `$INSTANCE_NAME`_INTR_BOTH    - Detect both edges
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint32 mode)
{
    uint32 config;
    uint8 enableInterrupts;
    
    `$INSTANCE_NAME`_internalIntr = `$INSTANCE_NAME`_GET_CONFIG_INTR(mode);

    enableInterrupts = CyEnterCriticalSection();
    config = `$INSTANCE_NAME`_CONFIG_REG & (uint32)~`$INSTANCE_NAME`_CONFIG_INTR_MASK;
    `$INSTANCE_NAME`_CONFIG_REG = config | `$INSTANCE_NAME`_internalIntr;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests. This function is for use when using the combined
*  interrupt signal from the global signal reference. This function from either
*  component instance can be used to determine the interrupt source for both the
*  interrupts combined.
*
* Parameters:
*  None
*
* Return:
*  uint32: Interrupt source. Each component instance has a mask value:
*  `$INSTANCE_NAME`_INTR.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetInterruptSource(void)
{
    return (`$INSTANCE_NAME`_INTR_REG); 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to clear either or both
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to clear. Each component instance
*  has a mask value: `$INSTANCE_NAME`_INTR.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask)
{   
    `$INSTANCE_NAME`_INTR_REG = interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to trigger either or both software
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to set. Each component instance has
*  a mask value: `$INSTANCE_NAME`_INTR_SET.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_INTR_SET_REG |= interruptMask;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetHysteresis
********************************************************************************
*
* Summary:
*  Enables or disables the hysteresis.
*
* Parameters:
*  hysteresis: (uint32) Enables or disables the hysteresis setting.
*  `$INSTANCE_NAME`_HYST_ENABLE     - Enable hysteresis
*  `$INSTANCE_NAME`_HYST_DISABLE    - Disable hysteresis
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetHysteresis(uint32 hysteresis)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    if(0u != hysteresis)
    {
        `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_HYST;
    }
    else
    {
        `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_HYST;
    }
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFilter
********************************************************************************
*
* Summary:
*  Enables or disables the digital filter. This still exists for saving backward 
*  compatibility, but not recommended for using.
*  This API is DEPRECATED and should not be used in new projects.
*
* Parameters:
*  uint32 filter: filter enable.
*  `$INSTANCE_NAME`_FILT_ENABLE  - Enable filter
*  `$INSTANCE_NAME`_FILT_DISABLE - Disable filter
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFilter(uint32 filter)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    if( 0u != filter)
    {
        `$INSTANCE_NAME`_CONFIG_REG |= `$INSTANCE_NAME`_CONFIG_FILT;
    }
    else
    {
        `$INSTANCE_NAME`_CONFIG_REG &= (uint32)~`$INSTANCE_NAME`_CONFIG_FILT;
    }
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
********************************************************************************
*
* Summary:
*  This function returns a nonzero value when the voltage connected to the
*  positive input is greater than the negative input voltage.
*  This function reads the direct (unflopped) comparator output which can also be 
*  metastable (since it may result in incorrect data).
*
* Parameters:
*  None
*
* Return:
*  (uint32) Comparator output state. This value is not impacted by the interrupt
*  edge detect setting:
*   0 - if positive input is less than negative one.
*   1 - if positive input greater than negative one.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return((uint32)((0u == (`$INSTANCE_NAME`_CONFIG_REG & `$INSTANCE_NAME`_CONFIG_OUT)) ? 0u : 1u));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ZeroCal
********************************************************************************
*
* Summary:
*  Performs custom calibration of the input offset to minimize error for a
*  specific set of conditions: comparator reference voltage, supply voltage,
*  and operating temperature. A reference voltage in the range at which the
*  comparator will be used must be applied to one of the inputs. The two inputs
*  will be shorted internally to perform the offset calibration.
*
* Parameters:
*  None
*
* Return:
*  The value from the comparator trim register after the offset calibration is
*  complete. This value has the same format as the input parameter for the
*  `$INSTANCE_NAME`_LoadTrim() API routine.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ZeroCal(void)
{
    uint32 cmpOut;
    uint32 i;

    `$INSTANCE_NAME`_DFT_REG |= `$INSTANCE_NAME`_DFT_CAL_EN;
    `$INSTANCE_NAME`_TRIMA_REG = 0u;
    `$INSTANCE_NAME`_TRIMB_REG = 0u;

    CyDelayUs(1u);

    cmpOut = `$INSTANCE_NAME`_GetCompare();

    if(0u != cmpOut)
    {
        `$INSTANCE_NAME`_TRIMA_REG = ((uint32) 0x01u << `$INSTANCE_NAME`_TRIMA_SIGNBIT);
    }

    for(i = (`$INSTANCE_NAME`_TRIMA_MAX_VALUE +1u ); i != 0u; i--)
    {
        `$INSTANCE_NAME`_TRIMA_REG++;
        CyDelayUs(1u);
        if(cmpOut != `$INSTANCE_NAME`_GetCompare())
        {
            break;
        }
    }

    if(((uint32)(`$INSTANCE_NAME`_CONFIG_REG >> `$INSTANCE_NAME`_CONFIG_REG_SHIFT) &
        `$INSTANCE_NAME`_SPEED_PARAM_MASK) == `$INSTANCE_NAME`_MED_SPEED)
    {
        cmpOut = `$INSTANCE_NAME`_GetCompare();

        if(0u == cmpOut)
        {
            `$INSTANCE_NAME`_TRIMB_REG = ((uint32)1u << `$INSTANCE_NAME`_TRIMB_SIGNBIT);
        }

        for(i = (`$INSTANCE_NAME`_TRIMB_MAX_VALUE +1u ); i != 0u; i--)
        {
            `$INSTANCE_NAME`_TRIMB_REG++;
            CyDelayUs(1u);
            if(cmpOut != `$INSTANCE_NAME`_GetCompare())
            {
                break;
            }
        }
    }

    `$INSTANCE_NAME`_DFT_REG &= ((uint32)~`$INSTANCE_NAME`_DFT_CAL_EN);

    return (`$INSTANCE_NAME`_TRIMA_REG | ((uint32)`$INSTANCE_NAME`_TRIMB_REG << `$INSTANCE_NAME`_TRIMB_SHIFT));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadTrim
********************************************************************************
*
* Summary:
*  This function writes a value into the comparator offset trim register.
*
* Parameters:
*  trimVal: Value to be stored in the comparator offset trim register. This
*  value has the same format as the parameter returned by the
*  `$INSTANCE_NAME`_ZeroCal() API routine.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_LoadTrim(uint32 trimVal)
{
    `$INSTANCE_NAME`_TRIMA_REG = (trimVal & `$INSTANCE_NAME`_TRIMA_MASK);
    `$INSTANCE_NAME`_TRIMB_REG = ((trimVal >> `$INSTANCE_NAME`_TRIMB_SHIFT) & `$INSTANCE_NAME`_TRIMB_MASK);
}


#if (`$INSTANCE_NAME`_CY_LPCOMP_V2)
    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOutputMode
********************************************************************************
*
* Summary:
*  Set comparator output mode. 
*
* Parameters:
*  uint32 mode: Comparator output mode value
*  `$INSTANCE_NAME`_OUT_DIRECT - Direct output
*  `$INSTANCE_NAME`_OUT_SYNC   - Synchronized output
*  `$INSTANCE_NAME`_OUT_PULSE  - Pulse output
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOutputMode(uint32 mode)
{
    uint32 config;
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    config = `$INSTANCE_NAME`_CONFIG_REG & ((uint32)~(`$INSTANCE_NAME`_CONFIG_DSI_BYPASS | \
                                                     `$INSTANCE_NAME`_CONFIG_DSI_LEVEL));
    `$INSTANCE_NAME`_CONFIG_REG = config | `$INSTANCE_NAME`_GET_CONFIG_DSI_BYPASS(mode) | \
                                           `$INSTANCE_NAME`_GET_CONFIG_DSI_LEVEL(mode);
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
********************************************************************************
*
* Summary:
*  Configures which bits of interrupt request register will trigger an interrupt 
*  event.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to set. Each component instance has
*  a mask value: `$INSTANCE_NAME`_INTR_MASK.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMask(uint32 interruptMask)
{
    #if(CY_IP_SRSSV2)
        `$INSTANCE_NAME`_intrMaskRegState = interruptMask;
    #endif /* (CY_IP_SRSSV2) */
    
    `$INSTANCE_NAME`_INTR_MASK_REG = interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
********************************************************************************
*
* Summary:
*  Returns interrupt mask.
*
* Parameters:
*  None
*
* Return:
*  uint32:  Mask of enabled interrupt source. Each component instance 
*  has a mask value: `$INSTANCE_NAME`_INTR_MASK.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetInterruptMask(void)
{
    return (`$INSTANCE_NAME`_INTR_MASK_REG);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Returns interrupt request register masked by interrupt mask. Returns the result 
*  of bitwise AND operation between corresponding interrupt request and mask bits.
*
* Parameters:
*  None
*
* Return:
*  uint32: Status of enabled interrupt source. Each component instance 
*  has a mask value: `$INSTANCE_NAME`_INTR_MASKED.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetInterruptSourceMasked(void)
{
    return (`$INSTANCE_NAME`_INTR_MASKED_REG);
}

#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/* [] END OF FILE */
