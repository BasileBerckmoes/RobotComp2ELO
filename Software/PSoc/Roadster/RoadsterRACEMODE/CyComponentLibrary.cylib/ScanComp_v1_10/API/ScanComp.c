/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the Scanning Comparator
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)

    static uint8  `$INSTANCE_NAME`_compDACRange;
    
    #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
        
        /* Variable declarations for DMA */
        static uint8 `$INSTANCE_NAME`_DMA_VDACUpdate_Chan;
        static uint8 `$INSTANCE_NAME`_DMA_VDACUpdate_TD = CY_DMA_INVALID_TD;
        
        static void `$INSTANCE_NAME`_InitDma(void)  `=ReentrantKeil($INSTANCE_NAME . "_InitDma")`;

        /* Array from customizer */
        static `$DacVoltagesArray`
    #else
        static uint8  `$INSTANCE_NAME`_compDACVoltage;
    #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */

#if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
    static uint8 storeStatusReg;
#endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */

uint8  `$INSTANCE_NAME`_initVar = 0u;

static reg8 * const CYCODE interruptStatusMaskRegs[`$INSTANCE_NAME`_NUM_OF_INT_REGISTERS] =
{
    `$INSTANCE_NAME`_STATUS_INT0_MASK_PTR,

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u)
        `$INSTANCE_NAME`_STATUS_INT1_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u */

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u)
        `$INSTANCE_NAME`_STATUS_INT2_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u */

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u)
        `$INSTANCE_NAME`_STATUS_INT3_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u */

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u)
        `$INSTANCE_NAME`_STATUS_INT4_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u */

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u)
        `$INSTANCE_NAME`_STATUS_INT5_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u */

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u)
        `$INSTANCE_NAME`_STATUS_INT6_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u */

    #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u)
        `$INSTANCE_NAME`_STATUS_INT7_MASK_PTR,
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the ScanComp component
*  and enables power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
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
*  Initializes or restores the ScanComp component according to
*  the customizer settings.
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
    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        storeStatusReg = 0u;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */

    `$INSTANCE_NAME`_Comp_Init();    
    
    #if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
        `$INSTANCE_NAME`_VDAC_Init();
        `$INSTANCE_NAME`_compDACRange = `$INSTANCE_NAME`_DEFAULT_RANGE;

        #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
            `$INSTANCE_NAME`_VDAC_SetValue(0x0u);
            
            if(CY_DMA_INVALID_TD == `$INSTANCE_NAME`_DMA_VDACUpdate_TD)
            {
                `$INSTANCE_NAME`_InitDma();
            }            
        #else
            `$INSTANCE_NAME`_SetDACVoltage(`$INSTANCE_NAME`_DEFAULT_VOLTAGE);
        #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
    #endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Turns off the Scanning Comparator by turning off the comparator itself and 
*  halting the muxing of inputs, and turning off the DAC if it is used.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_CONTROL_DISABLE;
    
    `$INSTANCE_NAME`_Comp_Stop();    
    
    #if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
        `$INSTANCE_NAME`_VDAC_Stop();

        #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)
            (void) CyDmaChDisable(`$INSTANCE_NAME`_DMA_VDACUpdate_Chan);
        #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
    #endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 interruptState;

    `$INSTANCE_NAME`_Comp_Enable();
    
    `$INSTANCE_NAME`_COUNTER_COUNT_REG  = `$INSTANCE_NAME`_DEFAULT_CHANNELS_VAL;

    #if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
        `$INSTANCE_NAME`_VDAC_Enable();
        #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)        
            (void)CyDmaClearPendingDrq(`$INSTANCE_NAME`_DMA_VDACUpdate_Chan);
            (void)CyDmaChEnable(`$INSTANCE_NAME`_DMA_VDACUpdate_Chan, 1u);
        #endif /* (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED) */    
    #endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */    

    /* Enable Status Int */
    interruptState = CyEnterCriticalSection();

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS < 8u)
        `$INSTANCE_NAME`_STATUS_INT0_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS < 8u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        `$INSTANCE_NAME`_STATUS_INT8_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 9u)
        `$INSTANCE_NAME`_STATUS_INT1_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 9u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u)
        `$INSTANCE_NAME`_STATUS_INT2_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u)
        `$INSTANCE_NAME`_STATUS_INT3_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u)
        `$INSTANCE_NAME`_STATUS_INT4_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u)
        `$INSTANCE_NAME`_STATUS_INT5_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u)
        `$INSTANCE_NAME`_STATUS_INT6_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u)
        `$INSTANCE_NAME`_STATUS_INT7_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u */

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS == 64)
        `$INSTANCE_NAME`_STATUS_INT9_AUX_CONTROL |= `$INSTANCE_NAME`_STATUS_INTR_ENBL;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS == 64u */

    `$INSTANCE_NAME`_COUNTER_AUX_CONTROL_REG |= `$INSTANCE_NAME`_COUNTER_ENABLE;

    CyExitCriticalSection(interruptState);

    `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_CONTROL_ENABLE ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the drive power and speed to one of three settings.
*
* Parameters:
*  speed: enumerated speed mode value.
*   `$INSTANCE_NAME`_SLOWSPEED  - Slow speed / Ultra low power
*   `$INSTANCE_NAME`_MEDSPEED   - Medium speed / Medium power
*   `$INSTANCE_NAME`_HIGHSPEED  - High speed / High power
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSpeed(uint8 speed) `=ReentrantKeil($INSTANCE_NAME . "_SetSpeed")`
{
    #if (CY_PSOC4)
        `$INSTANCE_NAME`_Comp_SetSpeed((uint32)speed);
    #else
        `$INSTANCE_NAME`_Comp_SetSpeed(speed);
    #endif /* CY_PSOC4 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the pending interrupt requests from the selected block.
*  Even masked interrupts are returned.
*
* Parameters:
*  InputBlock: Specifies the block of 8 channels whose interrupt requests
*  should be returned.
*
* Return:
*  Bit field of interrupt sources from the selected block of 8 inputs.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetInterruptSource(uint8 inputBlock) `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSource")`
{
    uint8 intSrc = 0u;

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        uint8 intMsb = 0u;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */

    static reg8 * const CYCODE interruptStatusRegs[`$INSTANCE_NAME`_NUM_OF_INT_REGISTERS] =
    {
        `$INSTANCE_NAME`_STATUS_INT0_PTR,

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u)
            `$INSTANCE_NAME`_STATUS_INT1_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u)
            `$INSTANCE_NAME`_STATUS_INT2_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u)
            `$INSTANCE_NAME`_STATUS_INT3_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u)
            `$INSTANCE_NAME`_STATUS_INT4_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u)
            `$INSTANCE_NAME`_STATUS_INT5_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u)
            `$INSTANCE_NAME`_STATUS_INT6_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u)
            `$INSTANCE_NAME`_STATUS_INT7_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u */
    };    
    
    if (inputBlock < `$INSTANCE_NAME`_NUM_OF_INT_REGISTERS)
    {
        intSrc = ((uint8) (* interruptStatusRegs[inputBlock])) & `$INSTANCE_NAME`_INT_REG_MASK;
    }
    
    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u)
        if (inputBlock == 7u)
        {
            intMsb = (uint8)(`$INSTANCE_NAME`_STATUS_INT9_REG  << `$INSTANCE_NAME`_7BIT_SHIFT);
        }
        else
        {
            storeStatusReg |= `$INSTANCE_NAME`_STATUS_INT8_REG;
            intMsb = (uint8)((storeStatusReg >> inputBlock) << `$INSTANCE_NAME`_7BIT_SHIFT);
            storeStatusReg = (storeStatusReg & (uint8)(~(uint8)(1u << inputBlock)));
        }
        intSrc |= intMsb;
    #elif (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        if (inputBlock != 7u)
        {
            storeStatusReg |= `$INSTANCE_NAME`_STATUS_INT8_REG;
            intMsb = (uint8)((storeStatusReg >> inputBlock) << `$INSTANCE_NAME`_7BIT_SHIFT);
            storeStatusReg = (storeStatusReg & (uint8)(~(uint8)(1u << inputBlock)));
        }
        intSrc |= intMsb;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 64u */

    return (intSrc);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the pending interrupt requests from the selected block.
*  Masked interrupts are not returned.
*
* Parameters:
*  InputBlock: Specifies the block of 8 channels whose interrupt requests
*  should be returned.
*
* Return:
*  Bit field of interrupt sources from the selected block of 8 inputs.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetInterruptSourceMasked(uint8 inputBlock)   \
                                                `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptSourceMasked")`
{
    return (`$INSTANCE_NAME`_GetInterruptSource(inputBlock) & (uint8)~`$INSTANCE_NAME`_GetInterruptMask (inputBlock));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetInterruptMask
********************************************************************************
*
* Summary:
*  Gets the current interrupt mask for the selected block.
*
* Parameters:
*  InputBlock: Specifies the block of 8 channels whose interrupt requests
*  should be returned.
*
* Return:
*  The interrupt mask for the given block of channels.
*  A '1' indicates that the interrupt is enabled, a '0' indicates that it 
*  is masked off.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetInterruptMask(uint8 inputBlock) `=ReentrantKeil($INSTANCE_NAME . "_GetInterruptMask")`
{
    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        uint8 maskMsb = 0u;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */

    uint8 intSrc = 0u;

    if (inputBlock < `$INSTANCE_NAME`_NUM_OF_INT_REGISTERS)
    {
        intSrc = (uint8) (* interruptStatusMaskRegs[inputBlock]);
    }    

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u)
        if (inputBlock == 7u)
        {
            maskMsb = (uint8)(`$INSTANCE_NAME`_STATUS_INT9_MASK  << `$INSTANCE_NAME`_7BIT_SHIFT);
        }
        else
        {
            maskMsb = (uint8)((`$INSTANCE_NAME`_STATUS_INT8_MASK >> inputBlock) << `$INSTANCE_NAME`_7BIT_SHIFT);
        }
        intSrc |= maskMsb;
    #elif (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        if (inputBlock != 7u)
        {
            maskMsb = (uint8)((`$INSTANCE_NAME`_STATUS_INT8_MASK >> inputBlock) << `$INSTANCE_NAME`_7BIT_SHIFT);
        }
        intSrc |= maskMsb;
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u */

    return ((uint8)intSrc);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMask
********************************************************************************
*
* Summary:
*  Sets the interrupt masks for the set block of 8 channels.
*
* Parameters:
*  InputBlock: specifies the block of 8 channels whose interrupt requests
*  should be returned.
*  mask: Interrupt mask value for the specified block of 8 or less channels. 
*  A '1' indicates that the interrupt is enabled, a '0' indicates that it 
*  is masked off.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMask(uint8 inputBlock, uint8 mask)    \
                                       `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMask")`
{
    uint8 maskLsb = mask & `$INSTANCE_NAME`_7BIT_MASK;

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        uint8 maskMsb = (uint8)((mask >> `$INSTANCE_NAME`_7BIT_SHIFT) << inputBlock);
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u */
    
    if (inputBlock < `$INSTANCE_NAME`_NUM_OF_INT_REGISTERS)
    {
        (* interruptStatusMaskRegs[inputBlock]) = maskLsb;
    }    

    #if (`$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u)
        if (inputBlock == 7u)
        {
            `$INSTANCE_NAME`_STATUS_INT9_MASK = maskMsb;
        }
        else
        {
            `$INSTANCE_NAME`_STATUS_INT8_MASK = maskMsb;
        }

    #elif (`$INSTANCE_NAME`_NUM_OF_CHANNELS >= 8u)
        if (inputBlock != 7u)
        {
            `$INSTANCE_NAME`_STATUS_INT8_MASK = maskMsb;
        }
    #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 63u */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCompare
********************************************************************************
*
* Summary:
*  Returns a nonzero value when the voltage connected to the positive input
*  is greater than the negative input voltage.
*
* Parameters:
*  channel: channel whose compare output is to be read.
*
* Return:
*  Comparator output state
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetCompare(uint8 channel) `=ReentrantKeil($INSTANCE_NAME . "_GetCompare")`
{
    uint8 compVal;
    uint8 chanPos;
    uint8 blockNum;

    static reg8 * const CYCODE outputStatusRegs[`$INSTANCE_NAME`_NUM_OF_OUT_REGISTERS] =
    {
        `$INSTANCE_NAME`_STATUS_OUT0_PTR,

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u)
            `$INSTANCE_NAME`_STATUS_OUT1_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 8u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u)
            `$INSTANCE_NAME`_STATUS_OUT2_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 16u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u)
            `$INSTANCE_NAME`_STATUS_OUT3_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 24u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u)
            `$INSTANCE_NAME`_STATUS_OUT4_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 32u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u)
            `$INSTANCE_NAME`_STATUS_OUT5_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 40u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u)
            `$INSTANCE_NAME`_STATUS_OUT6_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 48u */

        #if(`$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u)
            `$INSTANCE_NAME`_STATUS_OUT7_PTR,
        #endif /* `$INSTANCE_NAME`_NUM_OF_CHANNELS > 56u */
    };

    /* Identify block number by dividing by 8 */
    blockNum = (channel >> 3u);

    /* Identify maximum available channels for block */
    chanPos = (uint8)((blockNum + 1u) << 3u);
    
    /* Identify channel position in the register */
    chanPos = `$INSTANCE_NAME`_MSB_REG_BIT_HIGH >> ((chanPos - 1u) - channel);
    
    /* Input block int register & MSB bit shift */
    compVal = ((uint8) * outputStatusRegs[blockNum]) & chanPos;

    return (compVal);
}

#if (`$INSTANCE_NAME`_INTERNAL_REF_IS_USED)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetDACRange
    ********************************************************************************
    *
    * Summary:
    *  Sets the DAC to a new range.
    *
    * Parameters:
    *  uint8 DACRange: new range to be written to the DAC:
    *   `$INSTANCE_NAME`_SCANCOMP_DACRANGE_1V
    *   `$INSTANCE_NAME`_SCANCOMP_DACRANGE_4V
    *
    * Return:
    *  void
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetDACRange(uint8 DACRange) `=ReentrantKeil($INSTANCE_NAME . "_SetDACRange")`
    {
        `$INSTANCE_NAME`_VDAC_SetRange(DACRange);
        `$INSTANCE_NAME`_compDACRange = DACRange;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetDACRange
    ********************************************************************************
    *
    * Summary:
    *  Gets the DAC range setting..
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8 DACrange:
    *   `$INSTANCE_NAME`_SCANCOMP_DACRANGE_1V
    *   `$INSTANCE_NAME`_SCANCOMP_DACRANGE_4V
    *
    *******************************************************************************/

    uint8 `$INSTANCE_NAME`_GetDACRange(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDACRange")`
    {
        return (`$INSTANCE_NAME`_compDACRange);
    }


    #if (`$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED)

        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SetChannelDACVoltage
        ********************************************************************************
        *
        * Summary:
        *  Sets the DAC output for a specific channel to a new voltage.
        *
        * Parameters:
        *  Channel: Specifies the channel whose DAC voltage should be changed. 0
        *           indexed.
        *  DACVoltage: Voltage to be written to the DAC, in units depending on the
        *              selected range (4 or 16 mV per bit in 1 or 4V range,
        *              respectively). Should only be used when the DAC is enabled and
        *              voltage is per channel.
        *
        * Return:
        *  void
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_SetChannelDACVoltage(uint8 channel, uint8 DACVoltage) \
                                                   `=ReentrantKeil($INSTANCE_NAME . "_SetChannelDACVoltage")`
        {
            if (channel < `$INSTANCE_NAME`_NUM_OF_CHANNELS)
            {
                `$INSTANCE_NAME`_DacVoltages[(`$INSTANCE_NAME`_DEFAULT_CHANNELS_VAL - channel)] = DACVoltage;
            }
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_GetChannelDACVoltage
        ********************************************************************************
        *
        * Summary:
        *  Gets the DAC output voltage for a specific channel.
        *
        * Parameters:
        *  Channel: Specifies the channel whose DAC voltage should be returned.
        *
        * Return:
        *  Voltage the DAC is configured for, for the given channel, in units
        *  depending on the selected range (4 or 16 mV per bit in 1 or 4V range,
        *  respectively).
        *
        *******************************************************************************/
        uint8 `$INSTANCE_NAME`_GetChannelDACVoltage(uint8 channel)  \
                                                    `=ReentrantKeil($INSTANCE_NAME . "_GetChannelDACVoltage")`
        {
            uint8 DACVoltage = 0u;

            if (channel < `$INSTANCE_NAME`_NUM_OF_CHANNELS)
            {
                DACVoltage = `$INSTANCE_NAME`_DacVoltages[(`$INSTANCE_NAME`_DEFAULT_CHANNELS_VAL - channel)];
            }

            return (DACVoltage);
        }
        
        
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_InitDma
        ********************************************************************************
        *
        * Summary:
        *  Configures a DMA transfer of channel values from memory to VDAC.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_InitDma(void)  `=ReentrantKeil($INSTANCE_NAME . "_InitDma")`
        {
            /***************************************************************************
            * Transfers channel values from SRAM to VDAC register. One byte transfer,
            * each burst requires a request.
            ***************************************************************************/
            `$INSTANCE_NAME`_DMA_VDACUpdate_Chan =  `$INSTANCE_NAME`_DMA_DmaInitialize(
                                                    `$INSTANCE_NAME`_DMA_BYTES_PER_BURST,
                                                    `$INSTANCE_NAME`_DMA_REQUEST_PER_BURST,
                                                    HI16(`$INSTANCE_NAME`_DMA_SRC_BASE),
                                                    HI16(`$INSTANCE_NAME`_DMA_DST_BASE));

            `$INSTANCE_NAME`_DMA_VDACUpdate_TD = CyDmaTdAllocate();


            /***************************************************************************
            * One TD looping on itself, increment the source address, but not the
            * destination address.
            ***************************************************************************/
            (void) CyDmaTdSetConfiguration( `$INSTANCE_NAME`_DMA_VDACUpdate_TD,
                                            `$INSTANCE_NAME`_NUM_OF_CHANNELS,
                                            `$INSTANCE_NAME`_DMA_VDACUpdate_TD,
                                            TD_INC_SRC_ADR);

            /* Transfers the value for each channel from memory to VDAC */
            (void) CyDmaTdSetAddress(   `$INSTANCE_NAME`_DMA_VDACUpdate_TD,
                                        LO16((uint32)`$INSTANCE_NAME`_DacVoltages),
                                        LO16((uint32)`$INSTANCE_NAME`_VDAC_Data_PTR));

            (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_DMA_VDACUpdate_Chan, `$INSTANCE_NAME`_DMA_VDACUpdate_TD);
        }

    #else
        
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SetDACVoltage
        ********************************************************************************
        *
        * Summary:
        *  Sets the DAC output to a new voltage.
        *
        * Parameters:
        *  DACVoltage: Voltage to be written to the DAC, in units depending
        *  on the selected range
        *
        * Return:
        *  void
        *
        *******************************************************************************/
        void `$INSTANCE_NAME`_SetDACVoltage(uint8 DACVoltage) `=ReentrantKeil($INSTANCE_NAME . "_SetDACVoltage")`
        {
            `$INSTANCE_NAME`_VDAC_SetValue(DACVoltage);
            `$INSTANCE_NAME`_compDACVoltage = DACVoltage;
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_GetDACVoltage
        ********************************************************************************
        *
        * Summary:
        *  Gets the DAC output to a new voltage.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  Voltage the DAC is configured for, in units depending on the selected range
        *  (4 or 16 mV per bit in 1 or 4V range, respectively).
        *
        *******************************************************************************/
        uint8 `$INSTANCE_NAME`_GetDACVoltage(void) `=ReentrantKeil($INSTANCE_NAME . "_GetDACVoltage")`
        {
            return (`$INSTANCE_NAME`_compDACVoltage);
        }

    #endif /* `$INSTANCE_NAME`_VDAC_PER_CHANNEL_MODE_USED */
#endif /* `$INSTANCE_NAME`_INTERNAL_REF_IS_USED */


/* [] END OF FILE */
