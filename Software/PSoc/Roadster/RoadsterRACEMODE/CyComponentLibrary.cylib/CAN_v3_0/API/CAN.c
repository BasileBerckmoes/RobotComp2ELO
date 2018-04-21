/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  The CAN Component provides functionality of Control Area Network.
*  The two types of mailbox configuration available are "Full" and "Basic".
*
* Note:
*  The CAN configuration is put as constant to ROM and can be changed
*  only directly by the registers written by the user.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_RxTxBuffersConfig
********************************************************************************
*
* Summary:
*  Inits/Restores default CAN Rx and Tx Buffers control registers configuration
*  provided by the customizer.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
* Side Effects:
*  All the Rx and Tx Buffers control registers will be reset to their initial
*  values.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_RxTxBuffersConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RxTxBuffersConfig")`
{
    /* Initial values of CAN RX and TX registers */
    static const `$INSTANCE_NAME`_RX_CFG CYCODE `$INSTANCE_NAME`_RXConfigStruct[] =
    {
        { 0u, 0x`$Rx0_Cmd`u, 0x`$Rx0_Amr`u, 0x`$Rx0_Acr`u },
        { 1u, 0x`$Rx1_Cmd`u, 0x`$Rx1_Amr`u, 0x`$Rx1_Acr`u },
        { 2u, 0x`$Rx2_Cmd`u, 0x`$Rx2_Amr`u, 0x`$Rx2_Acr`u },
        { 3u, 0x`$Rx3_Cmd`u, 0x`$Rx3_Amr`u, 0x`$Rx3_Acr`u },
        { 4u, 0x`$Rx4_Cmd`u, 0x`$Rx4_Amr`u, 0x`$Rx4_Acr`u },
        { 5u, 0x`$Rx5_Cmd`u, 0x`$Rx5_Amr`u, 0x`$Rx5_Acr`u },
        { 6u, 0x`$Rx6_Cmd`u, 0x`$Rx6_Amr`u, 0x`$Rx6_Acr`u },
        { 7u, 0x`$Rx7_Cmd`u, 0x`$Rx7_Amr`u, 0x`$Rx7_Acr`u },
        { 8u, 0x`$Rx8_Cmd`u, 0x`$Rx8_Amr`u, 0x`$Rx8_Acr`u },
        { 9u, 0x`$Rx9_Cmd`u, 0x`$Rx9_Amr`u, 0x`$Rx9_Acr`u },
        { 10u, 0x`$Rx10_Cmd`u, 0x`$Rx10_Amr`u, 0x`$Rx10_Acr`u },
        { 11u, 0x`$Rx11_Cmd`u, 0x`$Rx11_Amr`u, 0x`$Rx11_Acr`u },
        { 12u, 0x`$Rx12_Cmd`u, 0x`$Rx12_Amr`u, 0x`$Rx12_Acr`u },
        { 13u, 0x`$Rx13_Cmd`u, 0x`$Rx13_Amr`u, 0x`$Rx13_Acr`u },
        { 14u, 0x`$Rx14_Cmd`u, 0x`$Rx14_Amr`u, 0x`$Rx14_Acr`u },
        { 15u, 0x`$Rx15_Cmd`u, 0x`$Rx15_Amr`u, 0x`$Rx15_Acr`u }
    };

    static const `$INSTANCE_NAME`_TX_CFG CYCODE `$INSTANCE_NAME`_TXConfigStruct[] =
    {
        { 0u, 0x`$Tx0_Cmd`u, 0x`$Tx0_Id`u },
        { 1u, 0x`$Tx1_Cmd`u, 0x`$Tx1_Id`u },
        { 2u, 0x`$Tx2_Cmd`u, 0x`$Tx2_Id`u },
        { 3u, 0x`$Tx3_Cmd`u, 0x`$Tx3_Id`u },
        { 4u, 0x`$Tx4_Cmd`u, 0x`$Tx4_Id`u },
        { 5u, 0x`$Tx5_Cmd`u, 0x`$Tx5_Id`u },
        { 6u, 0x`$Tx6_Cmd`u, 0x`$Tx6_Id`u },
        { 7u, 0x`$Tx7_Cmd`u, 0x`$Tx7_Id`u }
    };

    uint8 result = CYRET_SUCCESS;
    uint8 i;

    /* Initialize TX mailboxes */
    for (i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_TX_MAILBOXES; i++)
    {
        if (`$INSTANCE_NAME`_TxBufConfig((const `$INSTANCE_NAME`_TX_CFG *)
            (&`$INSTANCE_NAME`_TXConfigStruct[i])) != CYRET_SUCCESS)
        {
            result = `$INSTANCE_NAME`_FAIL;
            break;
        }
    }

    if (result == CYRET_SUCCESS)
    {
        /* Initialize RX mailboxes */
        for (i = 0u; i < `$INSTANCE_NAME`_NUMBER_OF_RX_MAILBOXES; i++)
        {
            if (`$INSTANCE_NAME`_RxBufConfig((const `$INSTANCE_NAME`_RX_CFG *)
                (&`$INSTANCE_NAME`_RXConfigStruct[i])) != CYRET_SUCCESS)
            {
                result = `$INSTANCE_NAME`_FAIL;
                break;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default CAN configuration provided by the customizer.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
* Side Effects:
*  All the registers will be reset to their initial values. This will
*  re-initialize the component with the following exceptions - it will not clear
*  data from the mailboxes.
*  Enable power to the CAN Core.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    uint32 timeout = `$INSTANCE_NAME`_MODE_STATE_STOP_TIMEOUT;
    uint8 result = `$INSTANCE_NAME`_FAIL;
    uint8 localResult = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Enable CAN block in Active mode */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

        /* Sets CAN controller to stop mode */
        `$INSTANCE_NAME`_CMD_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_MODE_MASK);

        /* Timeout for CAN state machine to switch mode to Stop */
        while ((timeout != 0u) && ((`$INSTANCE_NAME`_CMD_REG.byte[0u] & `$INSTANCE_NAME`_MODE_MASK) != 0u))
        {
            timeout--;
        }
    #else  /* CY_PSOC4 */
        /* Enable CAN IP Block */
        `$INSTANCE_NAME`_CNTL_REG = `$INSTANCE_NAME`_IP_ENABLE;

        /* Sets CAN controller to stop mode */
        `$INSTANCE_NAME`_CMD_REG &= (uint32) (~((uint32) `$INSTANCE_NAME`_MODE_MASK));

        /* Timeout for CAN state machine to switch mode to Stop */
        while ((timeout != 0u) && ((`$INSTANCE_NAME`_CMD_REG & `$INSTANCE_NAME`_MODE_MASK) != 0u))
        {
            timeout--;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */
        if (timeout != 0u)
        {
    `$ISRInitialization`
            if (`$INSTANCE_NAME`_SetPreScaler(`$INSTANCE_NAME`_BITRATE) == CYRET_SUCCESS)
            {
                if (`$INSTANCE_NAME`_SetArbiter(`$INSTANCE_NAME`_ARBITER) == CYRET_SUCCESS)
                {
                    #if (!(CY_PSOC3 || CY_PSOC5))
                        if (`$INSTANCE_NAME`_SetSwapDataEndianness(`$INSTANCE_NAME`_SWAP_DATA_END) == CYRET_SUCCESS)
                    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
                        {
                            if (`$INSTANCE_NAME`_SetTsegSample(`$INSTANCE_NAME`_CFG_REG_TSEG1,
                                `$INSTANCE_NAME`_CFG_REG_TSEG2, `$INSTANCE_NAME`_CFG_REG_SJW,
                                `$INSTANCE_NAME`_SAMPLING_MODE) == CYRET_SUCCESS)
                            {
                                if (`$INSTANCE_NAME`_SetRestartType(`$INSTANCE_NAME`_RESET_TYPE) == CYRET_SUCCESS)
                                {
                                    if (`$INSTANCE_NAME`_SetEdgeMode(`$INSTANCE_NAME`_SYNC_EDGE) == CYRET_SUCCESS)
                                    {
                                        localResult = CYRET_SUCCESS;
                                    }
                                }
                            }
                        }
                }
            }

            if (localResult == CYRET_SUCCESS)
            {
                if (`$INSTANCE_NAME`_RxTxBuffersConfig() == CYRET_SUCCESS)
                {
                    /* Write IRQ Mask */
                    if (`$INSTANCE_NAME`_SetIrqMask(`$INSTANCE_NAME`_INIT_INTERRUPT_MASK) ==
                        CYRET_SUCCESS)
                    {
                        /* Set CAN Operation Mode to Active mode always */
                        #if (CY_PSOC3 || CY_PSOC5)
                            `$INSTANCE_NAME`_CMD_REG.byte[0u] = `$INSTANCE_NAME`_INITIAL_MODE;
                            if ((`$INSTANCE_NAME`_CMD_REG.byte[0u] & `$INSTANCE_NAME`_MODE_MASK) == 0u)
                        #else  /* CY_PSOC4 */
                            `$INSTANCE_NAME`_CMD_REG &= (uint32) (~((uint32) `$INSTANCE_NAME`_OPMODE_FIELD_MASK));
                            if ((`$INSTANCE_NAME`_CMD_REG & `$INSTANCE_NAME`_OPMODE_FIELD_MASK) == 0u)
                        #endif /* CY_PSOC3 || CY_PSOC5 */
                            {
                                result = CYRET_SUCCESS;
                            }
                    }
                }
            }
        }

    return (result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  This function enables the CAN Component and ISR of CAN Component.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint32 timeout = `$INSTANCE_NAME`_MODE_STATE_RUN_TIMEOUT;
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Enable CAN block in Active mode */
        `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;

        /* Enable CAN block in Alternate Active (Standby) mode */
        `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;

        CyExitCriticalSection(enableInterrupts);
    #endif /* CY_PSOC3 || CY_PSOC5 */

    /* Clear interrupts status */
    CY_SET_REG32(`$INSTANCE_NAME`_INT_SR_PTR, `$INSTANCE_NAME`_INIT_INTERRUPT_MASK);
    (void) `$INSTANCE_NAME`_GlobalIntEnable();

`$ISREnable`
    /* Sets CAN controller to run mode */
    CY_SET_REG32(`$INSTANCE_NAME`_CMD_PTR, CY_GET_REG32(`$INSTANCE_NAME`_CMD_PTR) | `$INSTANCE_NAME`_MODE_MASK);

    /* Timeout for CAN state machine to switch mode to Run */
    while ((timeout != 0u) && ((CY_GET_REG32(`$INSTANCE_NAME`_CMD_PTR) & `$INSTANCE_NAME`_MODE_MASK) == 0u))
    {
        timeout--;
    }

    if (timeout != 0u)
    {
        result = CYRET_SUCCESS;
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  This function sets CAN Component into the Run mode. Starts Rate Counter if
*  polling mailboxes are available.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - used to check the initial configuration, modified
*  on the first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    uint8 result = CYRET_SUCCESS;

    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        result = `$INSTANCE_NAME`_Init();
    }

    if (result == CYRET_SUCCESS)
    {
        `$INSTANCE_NAME`_initVar = 1u;
        result = `$INSTANCE_NAME`_Enable();
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  This function sets CAN Component into the Stop mode.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
* Side Effects:
*  Disable power to CAN Core in case of PSoC 3/5.
*  Pending message in the Tx buffer of PSoC 3/5 will not be aborted on calling
*  the `$INSTANCE_NAME`_Stop() API. User has to abort all pending messages
*  before calling the `$INSTANCE_NAME`_Stop() function to make sure that the
*  block stops all the message transmission immediately.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint32 timeout = `$INSTANCE_NAME`_MODE_STATE_STOP_TIMEOUT;
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;
    #endif /* CY_PSOC3 || CY_PSOC5 */

    /* Set CAN controller to stop mode */
    CY_SET_REG32(`$INSTANCE_NAME`_CMD_PTR, (CY_GET_REG32(`$INSTANCE_NAME`_CMD_PTR) &
                                            ((uint32) (~((uint32)`$INSTANCE_NAME`_MODE_MASK)))));

    /* Timeout for CAN state machine to switch mode to Stop */
    while ((timeout != 0u) && ((CY_GET_REG32(`$INSTANCE_NAME`_CMD_PTR) & `$INSTANCE_NAME`_MODE_MASK) != 0u))
    {
        timeout--;
    }

    /* Verify that bit is cleared */
    if (timeout != 0u)
    {
        result = CYRET_SUCCESS;

    `$ISRDisable`
        #if (CY_PSOC3 || CY_PSOC5)
            enableInterrupts = CyEnterCriticalSection();

            /* Disable CAN block in Active mode */
            `$INSTANCE_NAME`_PM_ACT_CFG_REG &= (uint8) (~`$INSTANCE_NAME`_ACT_PWR_EN);

            /* Disable CAN block in Alternate Active (Standby) mode template */
            `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8) (~`$INSTANCE_NAME`_STBY_PWR_EN);

            CyExitCriticalSection(enableInterrupts);
        #endif /* CY_PSOC3 || CY_PSOC5 */
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GlobalIntEnable
********************************************************************************
*
* Summary:
*  This function enables Global Interrupts from CAN Core.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GlobalIntEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_GlobalIntEnable")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        `$INSTANCE_NAME`_INT_EN_REG.byte[0u] |= `$INSTANCE_NAME`_GLOBAL_INT_MASK;

        /* Verify that bit is set */
        if ((`$INSTANCE_NAME`_INT_EN_REG.byte[0u] & `$INSTANCE_NAME`_GLOBAL_INT_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        `$INSTANCE_NAME`_INT_EN_REG |= `$INSTANCE_NAME`_GLOBAL_INT_MASK;
        /* Verify that bit is set */
        if ((`$INSTANCE_NAME`_INT_EN_REG & `$INSTANCE_NAME`_GLOBAL_INT_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GlobalIntDisable
********************************************************************************
*
* Summary:
*  This function disables Global Interrupts from CAN Core.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GlobalIntDisable(void) `=ReentrantKeil($INSTANCE_NAME . "_GlobalIntDisable")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        `$INSTANCE_NAME`_INT_EN_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_GLOBAL_INT_MASK);

        /* Verify that bit is cleared */
        if ((`$INSTANCE_NAME`_INT_EN_REG.byte[0u] & `$INSTANCE_NAME`_GLOBAL_INT_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        `$INSTANCE_NAME`_INT_EN_REG &= (uint32) (~((uint32) `$INSTANCE_NAME`_GLOBAL_INT_MASK));

        /* Verify that bit is cleared */
        if ((`$INSTANCE_NAME`_INT_EN_REG & `$INSTANCE_NAME`_GLOBAL_INT_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetPreScaler
********************************************************************************
*
* Summary:
*  This function sets PreScaler for generating the time quantum which defines
*  the time quanta. The values between 0x0 and 0x7FFF are valid.
*
* Parameters:
*  bitrate: PreScaler value.
*   Value           Description
*    0               One time quantum equals 1 clock cycle
*    1               One time quantum equals 2 clock cycles
*    ...             ...
*    32767           One time quantum equals 32768 clock cycles
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*    `$INSTANCE_NAME`_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetPreScaler(uint16 bitrate) `=ReentrantKeil($INSTANCE_NAME . "_SetPreScaler")`
{
    uint8 result = `$INSTANCE_NAME`_OUT_OF_RANGE;

    if (bitrate <= `$INSTANCE_NAME`_BITRATE_MASK)
    {
        result = `$INSTANCE_NAME`_FAIL;

        #if (CY_PSOC3 || CY_PSOC5)
            /* Set prescaler */
            CY_SET_REG16((reg16 *) (&`$INSTANCE_NAME`_CFG_REG.byte[2u]), bitrate);

            /* Verify that prescaler is set */
            if (CY_GET_REG16((reg16 *) (&`$INSTANCE_NAME`_CFG_REG.byte[2u])) == bitrate)
            {
                result = CYRET_SUCCESS;
            }
        #else  /* CY_PSOC4 */
            /* Set prescaler */
            `$INSTANCE_NAME`_CFG_REG = (`$INSTANCE_NAME`_CFG_REG & (uint32) (~`$INSTANCE_NAME`_BITRATE_MASK_SHIFTED)) |
            (uint32) ((uint32) bitrate << `$INSTANCE_NAME`_BITRATE_SHIFT);

            /* Verify that prescaler is set */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_BITRATE_MASK_SHIFTED) ==
               ((uint32) ((uint32) bitrate << `$INSTANCE_NAME`_BITRATE_SHIFT)))
            {
                result = CYRET_SUCCESS;
            }
        #endif /* CY_PSOC3 || CY_PSOC5 */
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetArbiter
********************************************************************************
*
* Summary:
*  This function sets the arbitration type for transmit mailboxes. The types of
*  the arbiters are Round Robin and Fixed Priority. Values 0 and 1 are valid.
*
* Parameters:
*  arbiter: The arbitration type for transmit mailboxes.
*   Value                              Description
*    `$INSTANCE_NAME`_ROUND_ROBIN       The Round Robin arbitration
*    `$INSTANCE_NAME`_FIXED_PRIORITY    The Fixed Priority arbitration.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetArbiter(uint8 arbiter) `=ReentrantKeil($INSTANCE_NAME . "_SetArbiter")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (arbiter == `$INSTANCE_NAME`_ROUND_ROBIN)
        {
            `$INSTANCE_NAME`_CFG_REG.byte[1u] &= (uint8) (~`$INSTANCE_NAME`_ARBITRATION_MASK);

            /* Verify that bit is cleared */
            if ((`$INSTANCE_NAME`_CFG_REG.byte[1u] & `$INSTANCE_NAME`_ARBITRATION_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Fixed Priority */
        {
            `$INSTANCE_NAME`_CFG_REG.byte[1u] |= `$INSTANCE_NAME`_ARBITRATION_MASK;

            /* Verify that bit is set */
            if ((`$INSTANCE_NAME`_CFG_REG.byte[1u] & `$INSTANCE_NAME`_ARBITRATION_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (arbiter == `$INSTANCE_NAME`_ROUND_ROBIN)
        {
            `$INSTANCE_NAME`_CFG_REG &= (uint32) (~`$INSTANCE_NAME`_ARBITRATION_MASK);

            /* Verify that bit is cleared */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_ARBITRATION_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Fixed priority */
        {
            `$INSTANCE_NAME`_CFG_REG |= `$INSTANCE_NAME`_ARBITRATION_MASK;

            /* Verify that bit is set */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_ARBITRATION_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME: `$INSTANCE_NAME`_SetTsegSample
********************************************************************************
*
* Summary:
*  This function configures: Time segment 1, Time segment 2, Sampling Mode
*  and Synchronization Jump Width.
*
* Parameters:
*  cfgTseg1: The length of time segment 1, values between 0x2 and 0xF are valid;
*  cfgTseg2: The length of time segment 2, values between 0x1 and 0x7 are valid;
*  sjw: Synchronization Jump Width, value between 0x0 and 0x3 are valid;
*  sm: Sampling Mode.
*   Define                               Description
*   `$INSTANCE_NAME`_ONE_SAMPLE_POINT     One sampling point is used
*   `$INSTANCE_NAME`_THREE_SAMPLE_POINTS  Three sampling points are used
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*    `$INSTANCE_NAME`_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                     `=ReentrantKeil($INSTANCE_NAME . "_SetTsegSample")`
{
    uint8 result = `$INSTANCE_NAME`_OUT_OF_RANGE;
    uint8 cfgTemp;

    if ((cfgTseg1 >= `$INSTANCE_NAME`_CFG_REG_TSEG1_LOWER_LIMIT) && (cfgTseg1 <=
         `$INSTANCE_NAME`_CFG_REG_TSEG1_UPPER_LIMIT))
    {
        if (((cfgTseg2 >= `$INSTANCE_NAME`_CFG_REG_TSEG2_LOWER_LIMIT) &&
             (cfgTseg2 <= `$INSTANCE_NAME`_CFG_REG_TSEG2_UPPER_LIMIT)) || ((sm == `$INSTANCE_NAME`_ONE_SAMPLE_POINT) &&
             (cfgTseg2 == `$INSTANCE_NAME`_CFG_REG_TSEG2_EXCEPTION)))
        {
            if ((sjw <= `$INSTANCE_NAME`_CFG_REG_SJW_LOWER_LIMIT) && (sjw <= cfgTseg1) && (sjw <= cfgTseg2))
            {
                result = `$INSTANCE_NAME`_FAIL;

                #if (CY_PSOC3 || CY_PSOC5)
                    cfgTemp = `$INSTANCE_NAME`_CFG_REG.byte[1];
                    cfgTemp &= (uint8) (~`$INSTANCE_NAME`_CFG_REG_TSEG1_MASK);
                    cfgTemp |= cfgTseg1;

                    /* Write register byte 1 */
                    `$INSTANCE_NAME`_CFG_REG.byte[1u] = cfgTemp;

                    /* Verify 1st byte of `$INSTANCE_NAME`_CFG_REG register */
                    if (`$INSTANCE_NAME`_CFG_REG.byte[1u] == cfgTemp)
                    {
                        cfgTemp = 0u;
                        /* Set appropriate bits */
                        if (sm != `$INSTANCE_NAME`_ONE_SAMPLE_POINT)
                        {
                            cfgTemp = `$INSTANCE_NAME`_SAMPLE_MODE_MASK;
                        }
                        cfgTemp |= ((uint8) (cfgTseg2 << `$INSTANCE_NAME`_CFG_REG_TSEG2_SHIFT)) |
                                   ((uint8) (sjw << `$INSTANCE_NAME`_CFG_REG_SJW_SHIFT));

                        /* Write register byte 0 */
                        `$INSTANCE_NAME`_CFG_REG.byte[0u] = cfgTemp;

                        /* Verify 1st byte of `$INSTANCE_NAME`_CFG_REG register */
                        if (`$INSTANCE_NAME`_CFG_REG.byte[0u] == cfgTemp)
                        {
                            result = CYRET_SUCCESS;
                        }
                    }
                #else  /* CY_PSOC4 */
                    cfgTemp = (uint8) (`$INSTANCE_NAME`_CFG_REG >> `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT);
                    cfgTemp &= (uint8) (~`$INSTANCE_NAME`_CFG_REG_TSEG1_MASK);
                    cfgTemp |= cfgTseg1;

                    /* Write register byte 1 */
                    `$INSTANCE_NAME`_CFG_REG =
                    (`$INSTANCE_NAME`_CFG_REG & (uint32) (~((uint32) ((uint32) `$INSTANCE_NAME`_CFG_REG_TSEG1_MASK <<
                    `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT)))) |
                    (uint32) ((uint32) cfgTemp << `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT);

                    /* Verify 1st byte of `$INSTANCE_NAME`_CFG_REG register */
                    if ((`$INSTANCE_NAME`_CFG_REG & (uint32) ((uint32) `$INSTANCE_NAME`_CFG_REG_TSEG1_MASK <<
                       `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT)) == (uint32) ((uint32) ((uint32) cfgTemp &
                       `$INSTANCE_NAME`_CFG_REG_TSEG1_MASK) << `$INSTANCE_NAME`_CFG_REG_TSEG1_SHIFT))
                    {
                        cfgTemp = 0u;
                        /* Set appropriate bits */
                        if (sm != `$INSTANCE_NAME`_ONE_SAMPLE_POINT)
                        {
                            cfgTemp = `$INSTANCE_NAME`_SAMPLE_MODE_MASK;
                        }
                        cfgTemp |= ((uint8) (cfgTseg2 << `$INSTANCE_NAME`_CFG_REG_TSEG2_SHIFT)) |
                                   ((uint8) (sjw << `$INSTANCE_NAME`_CFG_REG_SJW_SHIFT));

                        /* Write register byte 0 */
                        `$INSTANCE_NAME`_CFG_REG = (`$INSTANCE_NAME`_CFG_REG &
                        (uint32) (~((uint32) (`$INSTANCE_NAME`_CFG_REG_TSEG2_MASK | `$INSTANCE_NAME`_CFG_REG_SJW_MASK |
                        `$INSTANCE_NAME`_SAMPLE_MODE_MASK)))) | cfgTemp;

                        /* Verify 1st byte of `$INSTANCE_NAME`_CFG_REG register */
                        if ((`$INSTANCE_NAME`_CFG_REG & (`$INSTANCE_NAME`_CFG_REG_TSEG2_MASK |
                           `$INSTANCE_NAME`_CFG_REG_SJW_MASK | `$INSTANCE_NAME`_SAMPLE_MODE_MASK)) == cfgTemp)
                        {
                            result = CYRET_SUCCESS;
                        }
                    }
                #endif /* CY_PSOC3 || CY_PSOC5 */
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetRestartType
********************************************************************************
*
* Summary:
*  This function sets the Reset type. The types of Reset are Automatic and
*  Manual. Manual Reset is the recommended setting.
*
* Parameters:
*  reset: Reset Type.
*   Define                             Description
*    `$INSTANCE_NAME`_MANUAL_RESTART    After Bus-Off, CAN must be restarted
*                                       manually. This is the recommended
*                                       setting.
*    `$INSTANCE_NAME`_AUTO_RESTART      After Bus-Off, CAN restarts
*                                       automatically after 128 groups of 11
*                                       recessive bits.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetRestartType(uint8 reset) `=ReentrantKeil($INSTANCE_NAME . "_SetRestartType")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (reset == `$INSTANCE_NAME`_MANUAL_RESTART)
        {
            `$INSTANCE_NAME`_CFG_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_RESET_MASK);

            /* Verify that bit is cleared */
            if ((`$INSTANCE_NAME`_CFG_REG.byte[0u] & `$INSTANCE_NAME`_RESET_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Automatic restart */
        {
            `$INSTANCE_NAME`_CFG_REG.byte[0u] |= `$INSTANCE_NAME`_RESET_MASK;

            /* Verify that bit is set */
            if ((`$INSTANCE_NAME`_CFG_REG.byte[0u] & `$INSTANCE_NAME`_RESET_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (reset == `$INSTANCE_NAME`_MANUAL_RESTART)
        {
            `$INSTANCE_NAME`_CFG_REG &= (uint32) (~((uint32) `$INSTANCE_NAME`_RESET_MASK));

            /* Verify that bit is cleared */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_RESET_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Automatic restart */
        {
            `$INSTANCE_NAME`_CFG_REG |= `$INSTANCE_NAME`_RESET_MASK;

            /* Verify that bit is set */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_RESET_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetEdgeMode
********************************************************************************
*
* Summary:
*  This function sets Edge Mode. The modes are 'R' to 'D'(Recessive to Dominant)
*  and Both edges are used.
*
* Parameters:
*  edge: Edge Mode.
*   Define                             Description
*    `$INSTANCE_NAME`_EDGE_R_TO_D       The edge from R to D is used for
*                                       synchronization
*    `$INSTANCE_NAME`_BOTH_EDGES        Both edges are used
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetEdgeMode(uint8 edge) `=ReentrantKeil($INSTANCE_NAME . "_SetEdgeMode")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (edge == `$INSTANCE_NAME`_EDGE_R_TO_D)
        {
            /* Recessive to Dominant is used for synchronization */
            `$INSTANCE_NAME`_CFG_REG.byte[0u] &= (uint8) (~`$INSTANCE_NAME`_EDGE_MODE_MASK);

            /* Verify that bit is cleared */
            if ((`$INSTANCE_NAME`_CFG_REG.byte[0u] & `$INSTANCE_NAME`_EDGE_MODE_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else
        {
            /* Both edges to be used */
            `$INSTANCE_NAME`_CFG_REG.byte[0u] |= `$INSTANCE_NAME`_EDGE_MODE_MASK;

            /* Verify that bit is set */
            if ((`$INSTANCE_NAME`_CFG_REG.byte[0u] & `$INSTANCE_NAME`_EDGE_MODE_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (edge == `$INSTANCE_NAME`_EDGE_R_TO_D)
        {
            /* Recessive to Dominant is used for synchronization */
            `$INSTANCE_NAME`_CFG_REG &= (uint32) (~((uint32) `$INSTANCE_NAME`_EDGE_MODE_MASK));

            /* Verify that bit is cleared */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_EDGE_MODE_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else
        {
            /* Both edges to be used */
            `$INSTANCE_NAME`_CFG_REG |= `$INSTANCE_NAME`_EDGE_MODE_MASK;

            /* Verify that bit is set */
            if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_EDGE_MODE_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetOpMode
********************************************************************************
*
* Summary:
*  This function sets Operation Mode.
*
* Parameters:
*  opMode: Operation Mode value.
*   Define                              Description
*    `$INSTANCE_NAME`_STOP_MODE          The CAN controller is in the Stop mode
*    `$INSTANCE_NAME`_ACTIVE_RUN_MODE    The CAN controller is in the Active
*                                        mode
*    `$INSTANCE_NAME`_LISTEN_ONLY_MODE   The CAN controller is in the Listen
*                                        Only mode: The output is held at the
*                                        'R' level.
*    `$INSTANCE_NAME`_INTERNAL_LOOP_BACK The CAN controller is in the Internal
*                                        Loopback mode. This mode is used for
*                                        the testing purpose and the transmitted
*                                        transactions are internally routed
*                                        back to the receiver logic and
*                                        processed by the controller in this
*                                        mode. Not available for PSoC3/5.
*    `$INSTANCE_NAME`_EXTERNAL_LOOP_BACK This mode is used for the testing
*                                        purpose by connecting Tx and Rx lines
*                                        externally. The transmitted messages
*                                        are received back and processed by the
*                                        CAN controller in this mode.
*                                        Not available for PSoC3/5.
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
* Side Effects:
*  For PSoC 4 device family the function re-initializes the CAN registers.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetOpMode(uint8 opMode) `=ReentrantKeil($INSTANCE_NAME . "_SetOpMode")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 timeout;
    #endif /* CY_PSOC3 || CY_PSOC5 */
    uint8 result = `$INSTANCE_NAME`_FAIL;
    uint8 runState = `$INSTANCE_NAME`_STOP_MODE;

    #if (CY_PSOC3 || CY_PSOC5)
        if (((`$INSTANCE_NAME`_CMD_REG.byte[0u] & `$INSTANCE_NAME`_ACTIVE_RUN_MODE) != 0u) ||
            (opMode == `$INSTANCE_NAME`_ACTIVE_RUN_MODE))
        {
            runState = `$INSTANCE_NAME`_ACTIVE_RUN_MODE;
        }

        /* Set CAN to the Stop Mode */
        `$INSTANCE_NAME`_CMD_REG.byte[0u] = `$INSTANCE_NAME`_STOP_MODE;

        /* Timeout for CAN state machine to switch mode to Stop */
        for (timeout = `$INSTANCE_NAME`_MODE_STATE_STOP_TIMEOUT;
            (timeout != 0u) && ((`$INSTANCE_NAME`_CMD_REG.byte[0u] & `$INSTANCE_NAME`_ACTIVE_RUN_MODE) != 0u);
             timeout--)
        {
        }

        if (timeout != 0u)
        {
            result = CYRET_SUCCESS;
        }

        if ((result == CYRET_SUCCESS) && (opMode != `$INSTANCE_NAME`_STOP_MODE))
        {
            if (opMode == `$INSTANCE_NAME`_LISTEN_ONLY_MODE)
            {
                `$INSTANCE_NAME`_CMD_REG.byte[0u] = `$INSTANCE_NAME`_LISTEN_ONLY_MODE;
            }

            if (runState == `$INSTANCE_NAME`_ACTIVE_RUN_MODE)
            {
                `$INSTANCE_NAME`_CMD_REG.byte[0u] |= `$INSTANCE_NAME`_ACTIVE_RUN_MODE;

                /* Timeout for CAN state machine to switch mode to Run */
                for (timeout = `$INSTANCE_NAME`_MODE_STATE_RUN_TIMEOUT;
                    (timeout != 0u) && ((`$INSTANCE_NAME`_CMD_REG.byte[0u] & `$INSTANCE_NAME`_MODE_MASK) == 0u);
                     timeout--)
                {
                }

                if (timeout == 0u)
                {
                    result = `$INSTANCE_NAME`_FAIL;
                }
            }
        }
    #else  /* CY_PSOC4 */
        if (((`$INSTANCE_NAME`_CMD_REG & `$INSTANCE_NAME`_MODE_MASK) != 0u) ||
            (opMode == `$INSTANCE_NAME`_ACTIVE_RUN_MODE))
        {
            runState = `$INSTANCE_NAME`_ACTIVE_RUN_MODE;
        }

        /* Sets CAN Component into the Stop mode */
        if (`$INSTANCE_NAME`_Stop() == CYRET_SUCCESS)
        {
            /* Disable CAN IP Block to reset configuration before sets Operation Mode */
            `$INSTANCE_NAME`_CNTL_REG = (uint32) (~`$INSTANCE_NAME`_IP_ENABLE);

            /* Enable CAN IP Block */
            `$INSTANCE_NAME`_CNTL_REG = `$INSTANCE_NAME`_IP_ENABLE;

            result = `$INSTANCE_NAME`_Init();

            if ((result == CYRET_SUCCESS) && (opMode != `$INSTANCE_NAME`_STOP_MODE))
            {
                if (opMode != `$INSTANCE_NAME`_ACTIVE_RUN_MODE)
                {
                    /* Set CAN Operation Mode */
                    `$INSTANCE_NAME`_CMD_REG |= opMode;
                }

                if (runState == `$INSTANCE_NAME`_ACTIVE_RUN_MODE)
                {
                    /* Enable component's operation */
                    result = `$INSTANCE_NAME`_Enable();
                }
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_RXRegisterInit
********************************************************************************
*
* Summary:
*  This function writes only receive CAN registers.
*
* Parameters:
*  regAddr: The pointer to a CAN receive register;
*  config:  The value that will be written in the register.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*    `$INSTANCE_NAME`_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_RXRegisterInit(reg32 *regAddr, uint32 config)
                                      `=ReentrantKeil($INSTANCE_NAME . "_RXRegisterInit")`
{
    uint8 result = `$INSTANCE_NAME`_OUT_OF_RANGE;

    if ((((uint32) regAddr & `$INSTANCE_NAME`_REG_ADDR_MASK) >=
        ((uint32) `$INSTANCE_NAME`_RX_FIRST_REGISTER_PTR & `$INSTANCE_NAME`_REG_ADDR_MASK)) &&
        ((((uint32) regAddr & `$INSTANCE_NAME`_REG_ADDR_MASK)) <=
        ((uint32) `$INSTANCE_NAME`_RX_LAST_REGISTER_PTR & `$INSTANCE_NAME`_REG_ADDR_MASK)))
    {
        result = `$INSTANCE_NAME`_FAIL;

        if ((((uint32) regAddr & `$INSTANCE_NAME`_REG_ADDR_MASK) % `$INSTANCE_NAME`_RX_CMD_REG_WIDTH) == 0u)
        {
            config |= `$INSTANCE_NAME`_RX_WPN_SET;

`$ISRDisable`
            /* Write defined RX CMD registers */
            CY_SET_REG32(regAddr, config);

`$ISREnable`
            /* Verify register */
            if ((CY_GET_REG32(regAddr) & `$INSTANCE_NAME`_RX_READ_BACK_MASK) ==
                (config & `$INSTANCE_NAME`_RX_READ_BACK_MASK))
            {
                result = CYRET_SUCCESS;
            }
        }
        /* All registers except RX CMD*/
        else
        {
`$ISRDisable`
            /* Write defined CAN receive register */
            CY_SET_REG32(regAddr, config);

`$ISREnable`
            /* Verify register */
            if (CY_GET_REG32(regAddr) == config)
            {
                result = CYRET_SUCCESS;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetIrqMask
********************************************************************************
*
* Summary:
*  This function sets to enable/disable particular interrupt sources. Interrupt
*  Mask directly write to the CAN Interrupt Enable register. A particular
*  interrupt source is enabled by setting its respective flag to 1.
*
* Parameters:
*  mask: Interrupt enable/disable request. 1 bit per interrupt source.
*   Define                                    Description
*    `$INSTANCE_NAME`_GLOBAL_INT_ENABLE        Global Interrupt Enable Flag
*    `$INSTANCE_NAME`_ARBITRATION_LOST_ENABLE  Arbitration Loss Interrupt Enable
*    `$INSTANCE_NAME`_OVERLOAD_ERROR_ENABLE    Overload Interrupt Enable
*    `$INSTANCE_NAME`_BIT_ERROR_ENABLE         Bit Error Interrupt Enable
*    `$INSTANCE_NAME`_STUFF_ERROR_ENABLE       Stuff Error Interrupt Enable
*    `$INSTANCE_NAME`_ACK_ERROR_ENABLE         Ack Error Interrupt Enable
*    `$INSTANCE_NAME`_FORM_ERROR_ENABLE        Form Error Interrupt Enable
*    `$INSTANCE_NAME`_CRC_ERROR_ENABLE         CRC Error Interrupt Enable
*    `$INSTANCE_NAME`_BUS_OFF_ENABLE           Bus-Off State Interrupt Enable
*    `$INSTANCE_NAME`_RX_MSG_LOST_ENABLE       Rx Msg Loss Interrupt Enable
*    `$INSTANCE_NAME`_TX_MESSAGE_ENABLE        Tx Msg Sent Interrupt Enable
*    `$INSTANCE_NAME`_RX_MESSAGE_ENABLE        Msg Received Interrupt Enable
*    `$INSTANCE_NAME`_RTR_MESSAGE_ENABLE       RTR Auto-reply Interrupt Enable
*    `$INSTANCE_NAME`_STUCK_AT_ZERO_ENABLE     Stuck at dominant error Interrupt
*                                              Enable
*    `$INSTANCE_NAME`_SST_FAILURE_ENABLE       SST failure Interrupt Enable
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetIrqMask(uint16 mask) `=ReentrantKeil($INSTANCE_NAME . "_SetIrqMask")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        /* Write byte 0 and 1 of `$INSTANCE_NAME`_INT_EN_REG register */
        CY_SET_REG16((reg16 *) (&`$INSTANCE_NAME`_INT_EN_REG), mask);

        /* Verify `$INSTANCE_NAME`_INT_EN_REG register */
        if (CY_GET_REG16((reg16 *) (&`$INSTANCE_NAME`_INT_EN_REG)) == mask)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        /* Write byte 0 and 1 of `$INSTANCE_NAME`_INT_EN_REG register */
        `$INSTANCE_NAME`_INT_EN_REG = mask;

        /* Verify `$INSTANCE_NAME`_INT_EN_REG register */
        if ((`$INSTANCE_NAME`_INT_EN_REG & `$INSTANCE_NAME`_REG_ADDR_MASK) == mask)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GetTXErrorFlag
********************************************************************************
*
* Summary:
*  This function returns the bit that indicates if the number of TX errors
*  exceeds 0x60.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the number of TX errors exceeds 0x60.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTXErrorFlag(void) `=ReentrantKeil($INSTANCE_NAME . "_GetTXErrorFlag")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of transmit error flag */
        return (((`$INSTANCE_NAME`_ERR_SR_REG.byte[2u] & `$INSTANCE_NAME`_TX_ERROR_FLAG_MASK) ==
                  `$INSTANCE_NAME`_TX_ERROR_FLAG_MASK) ? 1u : 0u);
    #else  /* CY_PSOC4 */
        /* Get state of transmit error flag */
        return (((`$INSTANCE_NAME`_ERR_SR_REG & `$INSTANCE_NAME`_TX_ERROR_FLAG_MASK) ==
                  `$INSTANCE_NAME`_TX_ERROR_FLAG_MASK) ? 1u : 0u);
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GetRXErrorFlag
********************************************************************************
*
* Summary:
*  This function returns the bit that indicates if the number of RX errors
*  exceeds 0x60.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the number of TX errors exceeds 0x60.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetRXErrorFlag(void) `=ReentrantKeil($INSTANCE_NAME . "_GetRXErrorFlag")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of receive error flag */
        return (((`$INSTANCE_NAME`_ERR_SR_REG.byte[2u] & `$INSTANCE_NAME`_RX_ERROR_FLAG_MASK) ==
                  `$INSTANCE_NAME`_RX_ERROR_FLAG_MASK) ? 1u : 0u);
    #else  /* CY_PSOC4 */
        /* Get state of receive error flag */
        return (((`$INSTANCE_NAME`_ERR_SR_REG & `$INSTANCE_NAME`_RX_ERROR_FLAG_MASK) ==
                  `$INSTANCE_NAME`_RX_ERROR_FLAG_MASK) ? 1u : 0u);
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GetTXErrorCount
********************************************************************************
*
* Summary:
*  This function returns the number of Transmit Errors.
*
* Parameters:
*  None.
*
* Return:
*  The number of Transmit Errors.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTXErrorCount(void) `=ReentrantKeil($INSTANCE_NAME . "_GetTXErrorCount")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of transmit error count */
        return (`$INSTANCE_NAME`_ERR_SR_REG.byte[0u]);    /* bits 7-0 */
    #else  /* CY_PSOC4 */
        /* Get state of transmit error count */
        return ((uint8) `$INSTANCE_NAME`_ERR_SR_REG);    /* bits 7-0 */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GetRXErrorCount
********************************************************************************
*
* Summary:
*  This function returns the number of Receive Errors.
*
* Parameters:
*  None.
*
* Return:
*  The number of Receive Errors.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetRXErrorCount(void) `=ReentrantKeil($INSTANCE_NAME . "_GetRXErrorCount")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of receive error count */
        return (`$INSTANCE_NAME`_ERR_SR_REG.byte[1u]);    /* bits 15-8 */
    #else  /* CY_PSOC4 */
        /* Get state of receive error count (bits 15-8) */
        return ((uint8) (`$INSTANCE_NAME`_ERR_SR_REG >> `$INSTANCE_NAME`_ONE_BYTE_OFFSET));
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_GetErrorState
********************************************************************************
*
* Summary:
*  This function returns the error status of CAN Component.
*
* Parameters:
*  None.
*
* Return:
*  The error status.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetErrorState(void) `=ReentrantKeil($INSTANCE_NAME . "_GetErrorState")`
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get error state of receiver */
        return (`$INSTANCE_NAME`_ERR_SR_REG.byte[2u] & `$INSTANCE_NAME`_ERROR_STATE_MASK);
    #else  /* CY_PSOC4 */
        /* Get error state of receiver */
        return ((uint8) ((`$INSTANCE_NAME`_ERR_SR_REG >> `$INSTANCE_NAME`_TWO_BYTE_OFFSET) &
                `$INSTANCE_NAME`_ERROR_STATE_MASK));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_RxBufConfig
********************************************************************************
*
* Summary:
*  This function configures all receive registers for a particular mailbox.
*
* Parameters:
*  rxConfig: The pointer to a structure that contain all required values to
*  configure all receive registers for a particular mailbox.
*
* Return:
*  The indication if particular configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_RxBufConfig(const `$INSTANCE_NAME`_RX_CFG *rxConfig)
                                   `=ReentrantKeil($INSTANCE_NAME . "_RxBufConfig")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    /* Write RX CMD Register */
    CY_SET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxcmd), (rxConfig->rxcmd |
                 `$INSTANCE_NAME`_RX_WPN_SET));
    if ((CY_GET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxcmd)) &
         `$INSTANCE_NAME`_RX_READ_BACK_MASK) == (rxConfig->rxcmd & `$INSTANCE_NAME`_RX_WPN_CLEAR))
    {
        /* Write RX AMR Register */
        CY_SET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxamr), rxConfig->rxamr);
        if (CY_GET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxamr)) == rxConfig->rxamr)
        {
            /* Write RX ACR Register */
            CY_SET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxacr), rxConfig->rxacr);
            if (CY_GET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxacr)) == rxConfig->rxacr)
            {
                /* Write RX AMRD Register */
                CY_SET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxamrd), 0xFFFFFFFFu);
                if (CY_GET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxamrd)) == 0xFFFFFFFFu)
                {
                    /* Write RX ACRD Register */
                    CY_SET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxacrd), 0x00000000u);
                    if (CY_GET_REG32((reg32 *) (&`$INSTANCE_NAME`_RX[rxConfig->rxmailbox].rxacrd)) == 0x00000000u)
                    {
                        result = CYRET_SUCCESS;
                    }
                }
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_TxBufConfig
********************************************************************************
*
* Summary:
*  This function configures all transmit registers for a particular mailbox.
*  Mailbox number contains `$INSTANCE_NAME`_TX_CFG structure.
*
* Parameters:
*  txConfig: The pointer to structure that contain all required values to
*  configure all transmit registers for a particular mailbox.
*
* Return:
*  The indication if particular configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_TxBufConfig(const `$INSTANCE_NAME`_TX_CFG *txConfig)
                                   `=ReentrantKeil($INSTANCE_NAME . "_TxBufConfig")`
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    /* Write TX CMD Register */
    CY_SET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(txConfig->txmailbox), (txConfig->txcmd | `$INSTANCE_NAME`_TX_WPN_SET));
    if ((CY_GET_REG32(`$INSTANCE_NAME`_TX_CMD_PTR(txConfig->txmailbox)) &
        `$INSTANCE_NAME`_TX_READ_BACK_MASK) == (txConfig->txcmd & `$INSTANCE_NAME`_TX_WPN_CLEAR))
    {
        /* Write TX ID Register */
        CY_SET_REG32(`$INSTANCE_NAME`_TX_ID_PTR(txConfig->txmailbox), txConfig->txid);
        if (CY_GET_REG32(`$INSTANCE_NAME`_TX_ID_PTR(txConfig->txmailbox)) == txConfig->txid)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


#if (!(CY_PSOC3 || CY_PSOC5))

/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetSwapDataEndianness
********************************************************************************
*
* Summary:
*  This function selects whether the data byte endianness of the CAN receive and
*  transmit data fields has to be swapped or not swapped. This is useful to
*  match the data byte endianness to the endian setting of the processor or the
*  used CAN protocol.
*
* Parameters:
*  swap: Swap Enable/Disable setting.
*   Define                                   Description
*   `$INSTANCE_NAME`_SWAP_ENDIANNESS_ENABLE   The endianness of transmitted/
*                                             received data byte fields (Big
*                                             endian) is not swapped during
*                                             multibyte data transmission.
*   `$INSTANCE_NAME`_SWAP_ENDIANNESS_DISABLE  The endianness of transmitted/
*                                             received data byte fields is
*                                             swapped (Little endian) during
*                                             multi byte data transmission.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetSwapDataEndianness(uint8 swap)
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    if (swap == `$INSTANCE_NAME`_SWAP_ENDIANNESS_DISABLE)    /* Big endian */
    {
        `$INSTANCE_NAME`_CFG_REG &= (uint32) (~`$INSTANCE_NAME`_ENDIANNESS_MASK);

        /* Verify that bit is cleared */
        if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_ENDIANNESS_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    }
    else    /* Little endian */
    {
        `$INSTANCE_NAME`_CFG_REG |= `$INSTANCE_NAME`_ENDIANNESS_MASK;

        /* Verify that bit is set */
        if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_ENDIANNESS_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_SetErrorCaptureRegisterMode
********************************************************************************
*
* Summary:
*  This function sets the Error Capture register mode. The two modes are
*  possible: Free Running and Error Capture.
*
* Parameters:
*  ecrMode: The Error Capture register mode setting.
*   Define                               Description
*   `$INSTANCE_NAME`_ECR_FREE_RUNNING     The ECR captures the field and bit
*                                         position within the current CAN frame.
*   `$INSTANCE_NAME`_ECR_ERROR_CAPTURE    In this mode the ECR register only
*                                         captures an error event. For
*                                         successive error captures, the ECR
*                                         needs to be armed again by writing
*                                         to the ECR register.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_SetErrorCaptureRegisterMode(uint8 ecrMode)
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    if (ecrMode == `$INSTANCE_NAME`_ECR_FREE_RUNNING)
    {
        `$INSTANCE_NAME`_CFG_REG &= (uint32) (~`$INSTANCE_NAME`_ECR_MODE_MASK);

        /* Verify that bit is cleared */
        if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_ECR_MODE_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    }
    else    /* Capture mode */
    {
        `$INSTANCE_NAME`_CFG_REG |= `$INSTANCE_NAME`_ECR_MODE_MASK;

        /* Verify that bit is set */
        if ((`$INSTANCE_NAME`_CFG_REG & `$INSTANCE_NAME`_ECR_MODE_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_ReadErrorCaptureRegister
********************************************************************************
*
* Summary:
*  This function returns the value of the Error Capture register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the Error Capture register.
*   Bit  Name          Values
*    0    ECR_STATUS    0: The ECR register captured an error or it is a free
*                          running mode
*                       1: The ECR register is armed
*   3:1   ERROR_TYPE    000 : Arbitration loss
*                       001 : Bit Error
*                       010 : Bit Stuffing Error
*                       011 : Acknowledge Error
*                       100 : Form Error
*                       101 : CRC Error
*                       Others : N/A
*    4    TX_MODE       0: No status
*                       1: CAN Controller is the transmitter
*    5    RX_MODE       0: No status
*                       1: CAN Controller is the receiver
*  11:6   BIT           Bit number inside of Field
*  12:16  Field         0x00 : Stopped
*                       0x01 : Synchronize
*                       0x05 : Interframe
*                       0x06 : Bus Idle
*                       0x07 : Start of Frame
*                       0x08 : Arbitration
*                       0x09 : Control
*                       0x0A : Data
*                       0x0B : CRC
*                       0x0C : ACK
*                       0x0D : End of frame
*                       0x10 : Error flag
*                       0x11 : Error echo
*                       0x12 : Error delimiter
*                       0x18 : Overload flag
*                       0x19 : Overload echo
*                       0x1A : Overload delimiter
*                       Others : N/A
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadErrorCaptureRegister(void)
{
    return (`$INSTANCE_NAME`_ECR_REG);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_ArmErrorCaptureRegister
********************************************************************************
*
* Summary:
*  This function arms the Error Capture register when the ECR is in the Error
*  Capture mode, by setting the ECR_STATUS bit in the ECR register.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    `$INSTANCE_NAME`_FAIL              The function failed
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ArmErrorCaptureRegister(void)
{
    uint8 result = `$INSTANCE_NAME`_FAIL;

    `$INSTANCE_NAME`_ECR_REG |= `$INSTANCE_NAME`_ECR_STATUS_ARM;

    /* Verify that bit is set */
    if ((`$INSTANCE_NAME`_ECR_REG & `$INSTANCE_NAME`_ECR_STATUS_ARM) != 0u)
    {
        result = CYRET_SUCCESS;
    }

    return (result);
}

#endif /* (!(CY_PSOC3 || CY_PSOC5)) */


/* [] END OF FILE */
