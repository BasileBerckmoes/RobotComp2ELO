/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides the source code to the API for the UART Component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "sysint/cy_sysint.h"
#include "cyfitter_sysint.h"
#include "cyfitter_sysint_cfg.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*     Global variables
***************************************/

/** `$INSTANCE_NAME`_initVar indicates whether the `$INSTANCE_NAME`
*  component has been initialized. The variable is initialized to 0
*  and set to 1 the first time `$INSTANCE_NAME`_Start() is called.
*  This allows  the component to restart without reinitialization
*  after the first call to the `$INSTANCE_NAME`_Start() routine.
*
*  If re-initialization of the component is required, then the
*  `$INSTANCE_NAME`_Init() function can be called before the
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable() function.
*/
uint8_t `$INSTANCE_NAME`_initVar = 0U;


/** The instance-specific configuration structure.
* The pointer to this structure should be passed to Cy_SCB_UART_Init function
* to initialize component with GUI selected settings.
*/
cy_stc_scb_uart_config_t `=$CY_CONST_CONFIG ? "const " : ""``$INSTANCE_NAME`_config =
{
    .uartMode                   = `= (0 == $ComMode) ? "CY_SCB_UART_STANDARD" : (1 == $ComMode) ? "CY_SCB_UART_SMARTCARD" : "CY_SCB_UART_IRDA"`,
    .enableMutliProcessorMode   = `= ($IsMultiprocessorModeAvailable && $EnableMultiProc) ? "true" : "false"`,
    .smartCardRetryOnNack       = `= ((1 == $ComMode) && $SmCardRetryOnNack) ? "true" : "false"`,
    .irdaInvertRx               = `= ((2 == $ComMode) && $IrdaPolarity) ? "true" : "false"`,
    .irdaEnableLowPowerReceiver = `= ((2 == $ComMode) && $IrdaLowPower) ? "true" : "false"`,

    .oversample                 = `= (!$IrdaLowPower) ? $OvsFactor . "UL" : 
                                                       ($OvsFactor == 16)  ? "CY_SCB_UART_IRDA_LP_OVS16"  : ($OvsFactor == 32)  ? "CY_SCB_UART_IRDA_LP_OVS32"  :
                                                       ($OvsFactor == 48)  ? "CY_SCB_UART_IRDA_LP_OVS48"  : ($OvsFactor == 96)  ? "CY_SCB_UART_IRDA_LP_OVS96"  :
                                                       ($OvsFactor == 192) ? "CY_SCB_UART_IRDA_LP_OVS192" : ($OvsFactor == 768) ? "CY_SCB_UART_IRDA_LP_OVS768" :
                                                       "CY_SCB_UART_IRDA_LP_OVS1536"`,
    
    .enableMsbFirst             = `= $BitsOrder ? "true" : "false"`,
    .dataWidth                  = `$DataWidth`UL,
    .parity                     = `= (0 == $ParityType) ? "CY_SCB_UART_PARITY_NONE" : (2 == $ParityType) ? "CY_SCB_UART_PARITY_EVEN" : "CY_SCB_UART_PARITY_ODD"`,
    .stopBits                   = `= ((2 == $StopBits) ? "CY_SCB_UART_STOP_BITS_1" : (3 == $StopBits) ? "CY_SCB_UART_STOP_BITS_1_5" :
                                      (4 == $StopBits) ? "CY_SCB_UART_STOP_BITS_2" : (5 == $StopBits) ? "CY_SCB_UART_STOP_BITS_2_5" :
                                      (6 == $StopBits) ? "CY_SCB_UART_STOP_BITS_3" : (7 == $StopBits) ? "CY_SCB_UART_STOP_BITS_3_5" : "CY_SCB_UART_STOP_BITS_4")`,
    .enableInputFilter          = `= (2 == $ComMode) ? "true" : ($IsEnableInputFilterVisible && $EnableInputFilter) ? "true" : "false"`,
    .breakWidth                 = `$BreakSignalBits`UL,
    .dropOnFrameError           = `= $DropOnFrameErr  ? "true" : "false"`,
    .dropOnParityError          = `= ((0 != $ParityType) && $DropOnParityErr) ? "true" : "false"`,

    .receiverAddress            = `= ($IsMultiprocessorModeAvailable && $EnableMultiProc) ? IntToHexString(`$MpRxAddress`) : "0x0"`UL,
    .receiverAddressMask        = `= ($IsMultiprocessorModeAvailable && $EnableMultiProc) ? IntToHexString(`$MpRxAddressMask`) : "0x0"`UL,
    .acceptAddrInFifo           = `= ($IsMultiprocessorModeAvailable && $EnableMultiProc && $MpRxAcceptAddress) ? "true" : "false"`,

    .enableCts                  = `= ($IsCtsPinAllowed && $EnableCts) ? "true" : "false"`,
    .ctsPolarity                = `= ($IsCtsPinAllowed && $EnableCts && (0 != $CtsPolarity)) ? "CY_SCB_UART_ACTIVE_HIGH" : "CY_SCB_UART_ACTIVE_LOW"`,
    .rtsRxFifoLevel             = `= $IsRtsTriggerLevelVisible ? $RtsTriggerLevel : "0"`UL,
    .rtsPolarity                = `= ($IsRtsTriggerLevelVisible && (0 != $RtsPolarity)) ? "CY_SCB_UART_ACTIVE_HIGH" : "CY_SCB_UART_ACTIVE_LOW"`,

    .rxFifoTriggerLevel         = `= $IsRxTriggerLevelVisible ? $RxTriggerLevel : "0"`UL,
    .rxFifoIntEnableMask        = `= IntToHexString(`$RxIntrMask`)`UL,

    .txFifoTriggerLevel         = `= $IsTxTriggerLevelVisible ? $TxTriggerLevel : "0"`UL,
    .txFifoIntEnableMask        = `= IntToHexString(`$TxIntrMask`)`UL
};

/** The instance-specific context structure.
* It is used while the driver operation for internal configuration and
* data keeping for the UART. The user should not modify anything in this 
* structure.
*/
cy_stc_scb_uart_context_t `$INSTANCE_NAME`_context;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
****************************************************************************//**
*
* Invokes `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable().
* Also configures interrupt if it is internal.
* After this function call the component is enabled and ready for operation.
* This is the preferred method to begin component operation.
*
* \globalvars
* \ref `$INSTANCE_NAME`_initVar - used to check initial configuration,
* modified  on first function call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if (0U == `$INSTANCE_NAME`_initVar)
    {
        /* Configure component */
        (void) Cy_SCB_UART_Init(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_config, &`$INSTANCE_NAME`_context);

        /* Hook interrupt service routine */
    #if defined(`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED)
        (void) Cy_SysInt_Init(&`$INSTANCE_NAME`_SCB_IRQ_cfg, &`$INSTANCE_NAME`_Interrupt);
    #endif /* (`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED) */
    
        /* Component is configured */
        `$INSTANCE_NAME`_initVar = 1U;
    }

    /* Enable interrupt in NVIC */
#if defined(`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED)
    NVIC_EnableIRQ((IRQn_Type) `$INSTANCE_NAME`_SCB_IRQ_cfg.intrSrc);
#endif /* (`$INSTANCE_NAME`_SCB_IRQ__INTC_ASSIGNED) */

    Cy_SCB_UART_Enable(`$INSTANCE_NAME`_HW);
}

#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
