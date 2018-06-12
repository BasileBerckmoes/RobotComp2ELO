/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Comparator component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u; /* Defines if component was initialized */
static uint32 `$INSTANCE_NAME`_internalSpeed = 0u; /* Defines component Speed value */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
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
    
    `$INSTANCE_NAME`_internalSpeed = `$INSTANCE_NAME`_POWER;
    `$INSTANCE_NAME`_CTB_CTRL_REG = `$INSTANCE_NAME`_DEFAULT_CTB_CTRL;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG = `$INSTANCE_NAME`_DEFAULT_OA_RES_CTRL;
    
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_INTR_MASK_REG |= `$INSTANCE_NAME`_INTR_MASK_REG_DEFAULT;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
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
    `$INSTANCE_NAME`_OA_RES_CTRL_REG |= `$INSTANCE_NAME`_internalSpeed | \
                                        `$INSTANCE_NAME`_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables 
*  power to the block. The first time the routine is executed, the speed/power 
*  level, and hysteresis are set. When called to restart the comparator 
*  following a Stop() call, the current component parameter settings are retained.
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
void `$INSTANCE_NAME`_Start(void)
{
    if( 0u == `$INSTANCE_NAME`_initVar)
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
*  Turns off the comparator block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Does not affect the comparator speed settings.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_OA_CTRL_REG &= ((uint32)~(`$INSTANCE_NAME`_OA_PWR_MODE_MASK | \
                                               `$INSTANCE_NAME`_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the speed to one of three settings: slow, medium, or fast.
*
* Parameters:
*  speed: Enumerated speed mode value.
*   `$INSTANCE_NAME`_SLOW_SPEED  - Slow speed
*   `$INSTANCE_NAME`_MED_SPEED   - Medium speed
*   `$INSTANCE_NAME`_FAST_SPEED  - Fast speed
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint32 speed)
{
    uint32 tmp;
    
    `$INSTANCE_NAME`_internalSpeed = `$INSTANCE_NAME`_GET_OA_PWR_MODE(speed);
    tmp = `$INSTANCE_NAME`_OA_RES_CTRL_REG & \
           (uint32)~`$INSTANCE_NAME`_OA_PWR_MODE_MASK;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG = tmp | `$INSTANCE_NAME`_internalSpeed;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ZeroCal
********************************************************************************
*
* Summary:
*  Performs custom calibration of the input offset to minimize the error for a 
*  specific set of conditions: the comparator reference voltage, supply voltage, 
*  and operating temperature. A reference voltage in the range at which the 
*  comparator will be used must be applied to the Negative and Positive inputs 
*  of the comparator while the offset calibration is performed. This can be done 
*  external to the device or by using an internal analog mux on the positive input 
*  that selects between the positive input signal for normal operation and the 
*  negative input signal for calibration.
*
* Parameters:
*  None
*
* Return:
*  (uint32): The value from the comparator trim register after the offset 
*  calibration is complete. This value has the same format as the input parameter 
*  for the LoadTrim() API routine.
*
*
* Side Effects:
*  During the calibration procedure, the comparator output may behave erratically. 
*  The comparator output should be ignored during calibration.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ZeroCal(void)
{
    uint32 cmpOut;
    uint32 i;
    
    /* Clear trim registers before trimming */
    `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG       = 0u;
    `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_REG = 0u;
    
    /* Check comparator's output state */
    cmpOut = `$INSTANCE_NAME`_GetCompare();
    
    /* Connect the outputs of trim IDACs to the positive
    * output leg of the folded cascade 
    */
    if(cmpOut == 0u)
    {
        `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG       = ((uint32) 1u << `$INSTANCE_NAME`_COMP_TRIM_SIGN_SHIFT);
        `$INSTANCE_NAME`_OA_SLOPE_OFFSET_TRIM_REG = ((uint32) 1u << `$INSTANCE_NAME`_COMP_TRIM_SIGN_SHIFT);
    }
        
    /* Searching offset trim setting, 
    * that flips comparator output 
    */
    for(i = `$INSTANCE_NAME`_COMP_TRIM_MAX_VALUE; i != 0u; i--)
    {
        `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG++;
        CyDelayUs(`$INSTANCE_NAME`_COMP_CALIBRATION_DELAY);
        if(cmpOut != `$INSTANCE_NAME`_GetCompare())
        {
            break;
        }
    }
    
    /* Returns offset trim value */
    return (`$INSTANCE_NAME`_OA_OFFSET_TRIM_REG);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadTrim
********************************************************************************
*
* Summary:
*  This function writes a value into the comparator offset trim register.
*
* Parameters:
*  uint32 trimVal: Value to be stored in the comparator offset trim register. 
*  This value has the same format as the parameter returned by the ZeroCal() 
*  routine.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_LoadTrim(uint32 trimVal)
{
    `$INSTANCE_NAME`_OA_OFFSET_TRIM_REG = trimVal;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
********************************************************************************
*
* Summary:
*  This function returns a non-zero value when the voltage connected to the positive 
*  input is greater than the negative input voltage. This value is not affected by 
*  the Polarity parameter. This value always reflects a non-inverted state 
*  configuration.
*  This function reads the direct (unflopped) comparator output which can also be 
*  metastable (since it may result in incorrect data).
*
* Parameters:
*   None
*
* Return:
*  The comparator output state. A non-zero value when the positive input voltage is 
*  greater than the negative input voltage; otherwise, the return value is zero.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCompare(void)
{
    return ((uint32)(`$INSTANCE_NAME`_OA_COMP_STAT_REG >> `$INSTANCE_NAME`_OA_COMP_SHIFT) & 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests. This function is for use when using the combined
*  interrupt signal from the global signal reference. This function from either
*  component instance can be used to determine the interrupt source for all the
*  comparator interrupts combined.
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
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
********************************************************************************
*
* Summary:
*  Configures the interrupt mask for all comparators in the system.
*
* Parameters:
*  uint32 interruptMask: Bit-mask of interrupt sources to be enabled. Each 
*  component instance has a mask value: `$INSTANCE_NAME`_INTR_MASK.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMask(uint32 interruptMask)
{
    `$INSTANCE_NAME`_INTR_MASK_REG = interruptMask;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
********************************************************************************
*
* Summary:
*  Returns interrupt mask for all comparators.
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
*  Returns interrupt request register masked by interrupt mask for all comparators. 
*  Returns the result of bitwise AND operation between corresponding interrupt 
*  request and mask bits.
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

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt edge detect mode.
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
    uint32 tmp;

    tmp = `$INSTANCE_NAME`_OA_RES_CTRL_REG & (uint32)~`$INSTANCE_NAME`_OA_COMPINT_MASK;
    `$INSTANCE_NAME`_OA_RES_CTRL_REG = tmp | `$INSTANCE_NAME`_GET_OA_COMPINT(mode);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableInterruptOutput
********************************************************************************
*
* Summary:
*  Disables the interrupt output so that it will not be ORed to the global 
*  Signal CTBmInt with the other comparator interrupt outputs.  
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_DisableInterruptOutput(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_INTR_MASK_REG &= ~`$INSTANCE_NAME`_INTR_MASK;
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
