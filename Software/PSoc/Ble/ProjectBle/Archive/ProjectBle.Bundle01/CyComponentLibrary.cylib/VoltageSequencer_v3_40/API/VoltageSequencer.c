/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides all API functionality of the Voltage Sequencer component.
*
* Note:
*
*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/*******************************************************************************
* Custom Declarations and Variables
*   Add user include files, prototypes and variables between the following
*   #START and #END tags
*******************************************************************************/
/* `#START `$INSTANCE_NAME`_SYS_VAR` */

/* `#END` */

uint8 `$INSTANCE_NAME`_initVar = 0u;

/*******************************************************************************
*           Power system configuration set in the customizer
*******************************************************************************/

#if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)
    `$initStsPgoodMaskList`
    `$initStsPgoodPolarityList`
#endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */

#if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
    `$initCtlShutdownMaskList`
    `$initCtlFaultReseqCfg`
    `$initCtlPrereqList`
#endif /*`$INSTANCE_NAME`_CTL_INPUTS_EXIST */

`$initPgoodOnPrereqList`
`$initPgoodOffPrereqList`
`$initTonDelayList`
`$initTonMaxDelayList`
`$initPgoodShutdownMaskList`
`$initToffDelayList`
`$initToffMaxDelayList`
`$initTonMaxFaultReseqCfg`
`$initPgoodFaultReseqCfg`
`$initOvFaultReseqCfg`
`$initUvFaultReseqCfg`
`$initOcFaultReseqCfg`
`$initFaultReseqSrcList`

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u)
    `$initPgoodOnThresholdList`
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u */

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u)
    `$initPgoodOffThresholdList`
#endif /*`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u */


/*******************************************************************************
*                      Runtime power system configuration
*******************************************************************************/

#if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
    /* Defines which ctl[x] pins are power up pre-requisites for each converter */
    uint8  `$INSTANCE_NAME`_ctlPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    /* Defines which ctl[x] pins will generate a fault condition for each converter */
    uint8  `$INSTANCE_NAME`_ctlShutdownMaskList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    /* Defines shutdown group for each of ctl[x] inputs */
    `$ctlGroupShutdownMask`
    /* Specifies which ctl[x] pins have caused a shutdown */
    volatile uint8 `$INSTANCE_NAME`_ctlStatus = 0u;
    /* Defines the re-sequence configuration for CTL fault conditions */
    uint8 `$INSTANCE_NAME`_ctlFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */

#if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)
    /* Defines which pgood[x] pins are used to generate each sts[x] output */
    `$SeqBitsType` `$INSTANCE_NAME`_stsPgoodMaskList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
    /* Defines the logic conditions for generation of each sts[x] output */
    `$SeqBitsType` `$INSTANCE_NAME`_stsPgoodPolarityList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
#endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */

/* Defines power good voltage threshold for power on detection */
#if(`$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u)
    uint16 `$INSTANCE_NAME`_pgoodOnThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u */
/* Defines which pgood[x] pins are power up pre-requisites for each converter */
`$SeqBitsType` `$INSTANCE_NAME`_pgoodOnPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines which pgood[x] pins are power down pre-requisites for each converter */
`$SeqBitsType` `$INSTANCE_NAME`_pgoodOffPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines TON_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_tonDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines TON_MAX_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_tonMaxDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines power good voltage threshold for power off detection */
#if(`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u)
    uint16 `$INSTANCE_NAME`_pgoodOffThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u */
/* Defines which pgood[x] pins will generate a fault condition for each converter */
`$SeqBitsType` `$INSTANCE_NAME`_pgoodShutdownMaskList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines which converters will be disabled if pgood[x] generates a fault */
`$pgoodGroupShutdownMask`
/* Defines TOFF_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_toffDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines TOFF_MAX_DELAY parameter for each power converter */
uint16 `$INSTANCE_NAME`_toffMaxDelayList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* System Stable Time parameter */
uint16 `$INSTANCE_NAME`_sysStableTime;
/* Global TRESEQ_DELAY parameter */
uint16 `$INSTANCE_NAME`_globalReseqDelay;
/* Defines the power converter fault re-sequence sources */
uint8 `$INSTANCE_NAME`_faultReseqSrcList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for OV fault conditions */
uint8 `$INSTANCE_NAME`_ovFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for UV fault conditions */
uint8 `$INSTANCE_NAME`_uvFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for OC fault conditions */
uint8 `$INSTANCE_NAME`_ocFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for TON_MAX fault conditions */
uint8 `$INSTANCE_NAME`_tonMaxFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Defines the re-sequence configuration for pgood fault conditions */
uint8 `$INSTANCE_NAME`_pgoodFaultReseqCfg[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Enables/disables assertion of the fault output signal */
uint8 `$INSTANCE_NAME`_faultEnable;
/* Defines which power converters have faults enabled */
`$SeqBitsType` `$INSTANCE_NAME`_faultMask;
/* Enables/disables assertion of the warn output signal */
#if (`$INSTANCE_NAME`_ENABLE_WARNINGS != 0u)
    uint8 `$INSTANCE_NAME`_warnEnable;
#endif /* `$INSTANCE_NAME`_ENABLE_WARNINGS != 0u */
/* Defines which power converters have warnings enabled */
`$SeqBitsType` `$INSTANCE_NAME`_warnMask;
/* Power system status and mask registers */
/* Contains TOFF_MAX_WARN warning status for all power converters */
volatile `$SeqBitsType` `$INSTANCE_NAME`_warnStatus  = 0u;
/* Contains pgood fault status for all power converters */
volatile `$SeqBitsType` `$INSTANCE_NAME`_faultStatus = 0u;
/* Sequencer State Machine States  */
CYPDATA volatile uint8  `$INSTANCE_NAME`_state[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
/* Default initial states for all converters */
`$initState`
/* Forced ON and forced OFF command registers */
volatile `$SeqBitsType` `$INSTANCE_NAME`_forceOnCmdReg   = 0u;
volatile `$SeqBitsType` `$INSTANCE_NAME`_forceOffCmdReg  = 0u;
volatile `$SeqBitsType` `$INSTANCE_NAME`_forceOffModeReg = 0u;

/* Function prototypes */
static void `$INSTANCE_NAME`_InitSystemConfig(void);


/*******************************************************************************
*       Sequencer Debug Variables
*******************************************************************************/
#if(`$INSTANCE_NAME`_DEBUG_MODE != 0u)
    uint8   `$INSTANCE_NAME`_operatingMode  = 0u;
    uint8   `$INSTANCE_NAME`_singleStepMode = 0u;
#endif /* `$INSTANCE_NAME`_DEBUG_MODE != 0u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitSystemConfig
********************************************************************************
*
* Summary:
*  Sets all variables based on parameters entered into the customizer.
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
*******************************************************************************/
static void `$INSTANCE_NAME`_InitSystemConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_InitSystemConfig")`
{
    uint8 idx;

    #if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)
        for(idx = 0u; idx < `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS; idx++)
        {
            `$INSTANCE_NAME`_stsPgoodMaskList    [idx] = `$INSTANCE_NAME`_initStsPgoodMaskList    [idx];
            `$INSTANCE_NAME`_stsPgoodPolarityList[idx] = `$INSTANCE_NAME`_initStsPgoodPolarityList[idx];
        }
    #endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */

    `$INSTANCE_NAME`_sysStableTime    = `$INSTANCE_NAME`_INIT_SYS_STABLE_TIME;
    `$INSTANCE_NAME`_globalReseqDelay = `$INSTANCE_NAME`_INIT_GLOBAL_RESEQ_DELAY;

    for(idx = 0u; idx < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; idx++)
    {
        #if(`$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u)
            `$INSTANCE_NAME`_pgoodOnThresholdList[idx] = `$INSTANCE_NAME`_initPgoodOnThresholdList[idx];
        #endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u */
        
        #if(`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u)
            `$INSTANCE_NAME`_pgoodOffThresholdList[idx] = `$INSTANCE_NAME`_initPgoodOffThresholdList[idx];
        #endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u */

        `$INSTANCE_NAME`_pgoodOnPrereqList [idx] = `$INSTANCE_NAME`_initPgoodOnPrereqList [idx];
        `$INSTANCE_NAME`_pgoodOffPrereqList[idx] = `$INSTANCE_NAME`_initPgoodOffPrereqList[idx];
        `$INSTANCE_NAME`_tonDelayList      [idx] = `$INSTANCE_NAME`_initTonDelayList      [idx];
        `$INSTANCE_NAME`_tonMaxDelayList   [idx] = `$INSTANCE_NAME`_initTonMaxDelayList   [idx];

        #if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
            `$INSTANCE_NAME`_ctlShutdownMaskList[idx] = `$INSTANCE_NAME`_initCtlShutdownMaskList[idx];
            `$INSTANCE_NAME`_ctlFaultReseqCfg   [idx] = `$INSTANCE_NAME`_initCtlFaultReseqCfg   [idx];
            `$INSTANCE_NAME`_ctlPrereqList      [idx] = `$INSTANCE_NAME`_initCtlPrereqList      [idx];
        #endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */

        `$INSTANCE_NAME`_faultReseqSrcList    [idx] = `$INSTANCE_NAME`_initFaultReseqSrcList    [idx];
        `$INSTANCE_NAME`_toffDelayList        [idx] = `$INSTANCE_NAME`_initToffDelayList        [idx];
        `$INSTANCE_NAME`_toffMaxDelayList     [idx] = `$INSTANCE_NAME`_initToffMaxDelayList     [idx];
        `$INSTANCE_NAME`_pgoodShutdownMaskList[idx] = `$INSTANCE_NAME`_initPgoodShutdownMaskList[idx];
        `$INSTANCE_NAME`_tonMaxFaultReseqCfg  [idx] = `$INSTANCE_NAME`_initTonMaxFaultReseqCfg  [idx];
        `$INSTANCE_NAME`_pgoodFaultReseqCfg   [idx] = `$INSTANCE_NAME`_initPgoodFaultReseqCfg   [idx];
        `$INSTANCE_NAME`_ovFaultReseqCfg      [idx] = `$INSTANCE_NAME`_initOvFaultReseqCfg      [idx];
        `$INSTANCE_NAME`_uvFaultReseqCfg      [idx] = `$INSTANCE_NAME`_initUvFaultReseqCfg      [idx];
        `$INSTANCE_NAME`_ocFaultReseqCfg      [idx] = `$INSTANCE_NAME`_initOcFaultReseqCfg      [idx];
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Enables the component and places all power converter state machines
*  into the appropriate state (OFF or PEND_ON).
*  Calls the Init() API if the component has not been initialized before.
*  Calls the Enable() API.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    uint8 converterNum;

    if (`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }

    /* Place all power converter state machines into the appropriate state */
    for(converterNum = 0u; converterNum < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; converterNum++)
    {
        `$INSTANCE_NAME`_state[converterNum] = `$INSTANCE_NAME`_initState[converterNum];
    }
    /* Enable fault generation for all power converters */
    `$INSTANCE_NAME`_faultMask = `$INSTANCE_NAME`_CONVERTER_MASK;
    /* Enable assertion of the fault output signal */
    `$INSTANCE_NAME`_faultEnable = `$INSTANCE_NAME`_ENABLED;
    /* Clear power converter warning mask */
    `$INSTANCE_NAME`_warnMask = 0u;

    #if (`$INSTANCE_NAME`_ENABLE_WARNINGS != `$INSTANCE_NAME`_DISABLED)
        /* Enable assertion of the warn output signal */
        `$INSTANCE_NAME`_warnEnable = `$INSTANCE_NAME`_ENABLED;
    #endif /* `$INSTANCE_NAME`_ENABLE_WARNINGS != `$INSTANCE_NAME`_DISABLED) */

    /* Initialize general status outputs */
    #if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)
        `$INSTANCE_NAME`_STS_OUT_REG = (uint8)(~`$INSTANCE_NAME`_INIT_STS_POLARITY);
    #endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */


    /***************************************************************************
    * Add your custom code between the following #START and #END tags
    ***************************************************************************/
    /* `#START INIT_SECTION` */

    /* `#END`  */
    
    #ifdef `$INSTANCE_NAME`_START_CALLBACK
        `$INSTANCE_NAME`_Start_Callback();
    #endif /* `$INSTANCE_NAME`_START_CALLBACK */

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All output terminals are de-asserted.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    
    /* Disasble time tick genaration */
    `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG &= (uint8)~`$INSTANCE_NAME`_TICK_TIMER_EN;
    
    /* Disable ctl input monitoring */
    #if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
        `$INSTANCE_NAME`_CTL_MON_AUX_REG &= (uint8)~`$INSTANCE_NAME`_CTL_MON_EN;
    #endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */
    
    CyExitCriticalSection(enableInterrupts);

    /* Disable and flush pending interrupts */
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);

    /* De-assert converters 1 through 8 */
    `$INSTANCE_NAME`_ON_CTL1_REG = 0u;
    `$INSTANCE_NAME`_EN_CTL1_REG = 0u;

    /* De-assert converters 9 through 16 */
    #if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u)
        `$INSTANCE_NAME`_ON_CTL2_REG = 0u;
        `$INSTANCE_NAME`_EN_CTL2_REG = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u */

    /* De-assert converters 17 through 24 */
    #if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 16u)
        `$INSTANCE_NAME`_ON_CTL3_REG = 0u;
        `$INSTANCE_NAME`_EN_CTL3_REG = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 16u */

    /* De-assert converters 25 through 32 */
    #if (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 24u)
        `$INSTANCE_NAME`_ON_CTL4_REG = 0u;
        `$INSTANCE_NAME`_EN_CTL4_REG = 0u;
    #endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 24u */

    /* De-assert general status outputs */
    #if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)
        `$INSTANCE_NAME`_STS_OUT_REG = (uint8)~`$INSTANCE_NAME`_INIT_STS_POLARITY;
    #endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */

    /* De-assert system status outputs */
    `$INSTANCE_NAME`_SYSTEM_STATUS_REG &= (uint8)~`$INSTANCE_NAME`_SYS_STS_MASK;

    /* Clear all statuses */
    #if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
        `$INSTANCE_NAME`_ctlStatus   = 0u;
    #endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */
    `$INSTANCE_NAME`_faultStatus     = 0u;
    `$INSTANCE_NAME`_warnStatus      = 0u;
    `$INSTANCE_NAME`_forceOnCmdReg   = 0u;
    `$INSTANCE_NAME`_forceOffCmdReg  = 0u;
    `$INSTANCE_NAME`_forceOffModeReg = 0u;
    `$INSTANCE_NAME`_faultCond       = 0u;
    `$INSTANCE_NAME`_pendingOff      = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the component. Parameter settings are initialized based on
*  parameters entered into the customizer.
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
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    `$INSTANCE_NAME`_InitSystemConfig();
    
    /* Mask ctl[6:1] fault monitoring */
    #if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)    
        `$INSTANCE_NAME`_CTL_MON_MASK_REG = `$INSTANCE_NAME`_CTL_MON_DISBL;
    #endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */
    
    /* ISR Initialization */
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    
    /* Set the ISR to point to the Interrupt processing routines */
    (void) CyIntSetVector(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER, &`$INSTANCE_NAME`_SeqStateMachineIsr);
    (void) CyIntSetVector(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER, &`$INSTANCE_NAME`_SysStableTimerIsr);
    (void) CyIntSetVector(`$INSTANCE_NAME`_FAULT_ISR_NUMBER, &`$INSTANCE_NAME`_FaultHandlerIsr);
    
    /* Set the priority */
    CyIntSetPriority(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER, `$INSTANCE_NAME`_SEQUENCER_ISR_PRIORITY);
    CyIntSetPriority(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER, `$INSTANCE_NAME`_STABLE_TIMER_ISR_PRIORITY);
    CyIntSetPriority(`$INSTANCE_NAME`_FAULT_ISR_NUMBER, `$INSTANCE_NAME`_FAULT_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the component.
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
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;
    
    /* Read enable pin state */
    `$INSTANCE_NAME`_enPinLast = ((`$INSTANCE_NAME`_CTL_MON_REG & `$INSTANCE_NAME`_EN_PIN) != 0u) ? 1u : 0u;
    
    /* Enable the hardware fast fault shutdown block */
    `$INSTANCE_NAME`_SYSTEM_STATUS_REG |= `$INSTANCE_NAME`_RAPID_RESPONSE_EN;

    enableInterrupts = CyEnterCriticalSection();

    /* Enable control input fault monitoring */
    #if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
        `$INSTANCE_NAME`_CTL_MON_AUX_REG |= `$INSTANCE_NAME`_CTL_MON_EN;
    #endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */

    /* Enable interrupts */
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);

    /* Enable time tick genaration */
    `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG |= `$INSTANCE_NAME`_TICK_TIMER_EN;

    CyExitCriticalSection(enableInterrupts);
}

#if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlPrereq
    ********************************************************************************
    *
    * Summary:
    *  Sets which ctl[x] input is a pre-requisite for a power converter.
    *
    * Parameters:
    *  converterNum:
    *   Specifies the power converter number
    *   Valid range: 1-32
    *  ctlPinMask - specifies which ctl[x] pins are power up pre-requisites:
    *   Bit Field          Control Pin Pre-requisite Mask
    *   0                  1=ctl[1] is a power up pre-requisite
    *   1                  1=ctl[2] is a power up pre-requisite
    *   ...                ...
    *   5                  1=ctl[6] is a power up pre-requisite
    *   7..6               Reserved. Set to zeroes
    *
    *
    * Return:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlPrereqList - defines which ctl[x] pins are power
    *  up pre-requisites for each converter.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlPrereq(uint8 converterNum, uint8 ctlPinMask)
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetCtlPrereq")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            `$INSTANCE_NAME`_ctlPrereqList[converterNum - 1u] = ctlPinMask;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlPrereq
    ********************************************************************************
    *
    * Summary:
    *  Returns which ctl[x] input is a pre-requisite for a power converter.
    *
    * Parameters:
    *  converterNum:
    *   Specifies the power converter number
    *   Valid range: 1-32
    *
    * Return:
    *  ctlPinMask - specifies which ctl[x] pins are power up pre-requisites:
    *   Bit Field          Control Pin Pre-requisite Mask
    *   0                  1=ctl[1] is a power up pre-requisite
    *   1                  1=ctl[2] is a power up pre-requisite
    *   ...                ...
    *   5                  1=ctl[6] is a power up pre-requisite
    *   7..6               Reserved. Set to zeroes
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlPrereqList - defines which ctl[x] pins are power
    *  up pre-requisites for each converter.
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlPrereq(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlPrereq")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_ctlPrereqList[converterNum]);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlShutdownMask
    ********************************************************************************
    *
    * Summary:
    *  Determines which ctl[x] pins will cause the selected power converter to
    *  shutdown when de-asserted.
    *
    * Parameters:
    *  converterNum - specifies the power converter number.
    *   Valid range: 1-32.
    *  ctlPinMask - specifies which ctl[x] pins can cause a shutdown:
    *   Bit Field          Control Pin Shutdown Mask
    *   0                  1=ctl[1] de-assertion will shutdown the converter
    *   1                  1=ctl[2] de-assertion will shutdown the converter
    *   ...                ...
    *   5                  1=ctl[6] de-assertion will shutdown the converter
    *   7..6               Reserved. Set to zeroes
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlShutdownMaskList[] - defines which ctl[x] pins will
    *   cause shutdown for each converter.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlShutdownMask(uint8 converterNum, uint8 ctlPinMask)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetCtlShutdownMask")`
    {
        uint8 ctlPin;
        `$SeqBitsType` converterMask;
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
            converterMask = (`$SeqBitsType`)1u << converterNum; /* Determine bit to set */
            `$INSTANCE_NAME`_ctlShutdownMaskList[converterNum] = ctlPinMask;
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
            for(ctlPin = 0u; ctlPin < `$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS; ctlPin++)
            {
                if((ctlPinMask & 0x01u) == 0u)
                {
                    `$INSTANCE_NAME`_ctlGroupShutdownMask[ctlPin] &= (`$SeqBitsType`)~converterMask;
                }
                else
                {
                    `$INSTANCE_NAME`_ctlGroupShutdownMask[ctlPin] |= converterMask;
                }
                ctlPinMask >>= 1u;
            }
            `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlShutdownMask
    ********************************************************************************
    *
    * Summary:
    *  Determines which ctl[x] pins will cause the selected power converter to
    *  shutdown when de-asserted.
    *
    * Parameters:
    *  converterNum - specifies the power converter number.
    *   Valid range: 1-32.
    *
    * Return:
    *  ctlPinMask - specifies which ctl[x] pins can cause a shutdown:
    *   Bit Field          Control Pin Shutdown Mask
    *   0                  1=ctl[1] de-assertion will shutdown the converter
    *   1                  1=ctl[2] de-assertion will shutdown the converter
    *   ...                ...
    *   5                  1=ctl[6] de-assertion will shutdown the converter
    *   7..6               Reserved. Set to zeroes
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlShutdownMaskList[] - defines which ctl[x] pins will
    *   cause shutdown for each converter.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlShutdownMask(uint8 converterNum)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_GetCtlShutdownMask")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_ctlShutdownMaskList[converterNum]);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlReseqCnt
    ********************************************************************************
    *
    * Summary:
    *  Sets the re-sequence count for fault conditions due to
    *  de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
    *   1-30=valid re-sequencing counts.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlReseqCnt(uint8 converterNum, uint8 reseqCnt)
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetCtlReseqCnt")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            `$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum - 1u] =
                (`$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum - 1u] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                               | (reseqCnt & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlReseqCnt
    ********************************************************************************
    *
    * Summary:
    *  Returns the re-sequence count for fault conditions due to
    *  de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *
    * Return:
    *  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
    *   1-30=valid re-sequencing counts.
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlReseqCnt")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetCtlFaultResp
    ********************************************************************************
    *
    * Summary:
    *  Sets the shutdown mode for power converters in response to
    *  fault conditions due to de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *  faultResponse - specifies the shutdown mode for any slave power converters.
    *   Options: 0=immediate, 1=soft.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetCtlFaultResp(uint8 converterNum, uint8 faultResponse)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetCtlFaultResp")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            `$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum - 1u] =
                   (uint8)(faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) |
                   (`$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum - 1u] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlFaultResp
    ********************************************************************************
    *
    * Summary:
    *  Returns the shutdown mode for power converters in response to
    *  fault conditions due to de-asserted ctl[x] inputs.
    *
    * Parameters:
    *  converterNum - specifies the power converter number. Valid range: 1-32.
    *
    * Return:
    *  faultResponse - specifies the shutdown mode for any slave power converters.
    *   Options: 0=immediate, 1=soft.
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_ctlFaultReseqCfg[] - defines the re-sequence settings
    *   for fault conditions due to de-asserted ctl[x] inputs.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlFaultResp")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return ((`$INSTANCE_NAME`_ctlFaultReseqCfg[converterNum] >> `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetCtlStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns which ctl[x] pins have caused one or more converters to shutdown.
    *  These bits are sticky until the API is called.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  ctlStatus:
    *   Specifies which ctl[x] pins have caused a shutdown
    *   Bit Field          Control Pin Shutdown Mask
    *   0                  1=ctl[1] de-assertion caused a shutdown
    *   1                  1=ctl[2] de-assertion caused a shutdown
    *   ...                ...
    *   5                  1=ctl[6] de-assertion caused a shutdown
    *   7..6               Reserved. Set to zeroes.
    * Side Effects:
    *  Calling this API clears the ctl[x] fault status.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetCtlStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetCtlStatus")`
    {
        uint8 ctlStatus;
        
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
        ctlStatus = `$INSTANCE_NAME`_ctlStatus;
        `$INSTANCE_NAME`_ctlStatus = 0u;
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
        return (ctlStatus);
    }

#endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */

#if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetStsPgoodMask
    ********************************************************************************
    *
    * Summary:
    *  Specifies which pgood[x] signals participate in the generation of the
    *  specified general purpose sequencer status output pins (sts[x]).
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *  stsPgoodMask:
    *   Bit Field          Status Pgood Mask
    *   0                  1=Sts output depends on pgood[1]
    *   1                  1=Sts output depends on pgood[2]
    *   ...                ...
    *   31                 1=Sts output depends on pgood[32]
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodMaskList[] - defines which pgood[x] pins
    *   are used to generate each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetStsPgoodMask(uint8 stsNum, `$SeqBitsType` stsPgoodMask)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetStsPgoodMask")`
    {
        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
                `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
            
            `$INSTANCE_NAME`_stsPgoodMaskList[stsNum - 1u] = stsPgoodMask;
            
            #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
                `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
        }
        else
        {
            /* Halt CPU in debug mode if stsNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetStsPgoodMask
    ********************************************************************************
    *
    * Summary:
    *  Returns which pgood[x] signals participate in the generation of the
    *  specified general purpose sequencer status output pins (sts[x]).
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *
    * Return:
    *  stsPgoodMask:
    *   Bit Field          Status Pgood Mask
    *   0                  1=Sts output depends on pgood[1]
    *   1                  1=Sts output depends on pgood[2]
    *   ...                ...
    *   31                 1=Sts output depends on pgood[32]
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodMaskList[] - defines which pgood[x] pins
    *   are used to generate each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    `$SeqBitsType` `$INSTANCE_NAME`_GetStsPgoodMask(uint8 stsNum) `=ReentrantKeil($INSTANCE_NAME . "_GetStsPgoodMask")`
    {
        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            stsNum--;
        }
        else
        {
            /* Halt CPU in debug mode if stsNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_stsPgoodMaskList[stsNum]);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetStsPgoodPolarity
    ********************************************************************************
    *
    * Summary:
    *  Configures the logic conditions that will cause the selected general
    *  purpose sequencer control output pins (sts[x]) to be asserted.
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *  stsPgoodPolarity - specifies the polarity of the pgood[x] signal required
    *   to assert the specified sts[x] signal:
    *   Bit Field          Status Polarity
    *   0                  0=pgood[1] must be low,
    *                      1=pgood[1] must be high
    *   1                  0=pgood[2] must be low,
    *                      1=pgood[2] must be high
    *   ...                ...
    *   31                 0=pgood[32] must be low,
    *                      1=pgood[32] must be high
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodPolarityList[] - the logic conditions for
    *   generation of each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetStsPgoodPolarity(uint8 stsNum, `$SeqBitsType` pgoodPolarity)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetStsPgoodPolarity")`
    {
        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
                `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
            
            `$INSTANCE_NAME`_stsPgoodPolarityList[stsNum - 1u] = pgoodPolarity;
            
            #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
                `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */            
        }
        else
        {
            /* Halt CPU in debug mode if stsNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetStsPgoodPolarity
    ********************************************************************************
    *
    * Summary:
    *  Returns the polarity of the pgood[x] signals used in the AND expression
    *  for the selected general purpose sequencer control output (sts[x]).
    *
    * Parameters:
    *  stsNum - specifies the status pin number. Valid range: 1-6.
    *
    * Return:
    *  stsPgoodPolarity - specifies the polarity of the pgood[x] signal required
    *   to assert the specified sts[x] signal:
    *   Bit Field          Status Polarity
    *   0                  0=pgood[1] must be low,
    *                      1=pgood[1] must be high
    *   1                  0=pgood[2] must be low,
    *                      1=pgood[2] must be high
    *   ...                ...
    *   31                 0=pgood[32] must be low,
    *                      1=pgood[32] must be high
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_stsPgoodPolarityList[] - the logic conditions for
    *   generation of each sts[x] output.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    `$SeqBitsType` `$INSTANCE_NAME`_GetStsPgoodPolarity(uint8 stsNum)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetStsPgoodPolarity")`
    {
        if((stsNum > 0u) && (stsNum <= `$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS))
        {
            stsNum--;
        }
        else
        {
            /* Halt CPU in debug mode if stsNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_stsPgoodPolarityList[stsNum]);
    }

#endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetPgoodOnThreshold
    ********************************************************************************
    *
    * Summary:
    *  Sets the power good voltage threshold for power on detection.
    *
    * Parameters:
    *  ctlNum - specifies the converter number. Valid range: 1-32.
    *  onThreshold - specifies the power good power on threshold in mV.
    *   Valid range: 0-65535
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_pgoodOnThresholdList[] - defines power good voltage
    *   threshold for power on detection.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetPgoodOnThreshold(uint8 converterNum, uint16 onThreshold)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodOnThreshold")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            `$INSTANCE_NAME`_pgoodOnThresholdList[converterNum - 1u] = onThreshold;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetPgoodOnThreshold
    ********************************************************************************
    *
    * Summary:
    *  Returns the power good voltage threshold for power on detection.
    *
    * Parameters:
    *  ctlNum - specifies the converter number. Valid range: 1-32.
    *
    * Return:
    *  onThreshold - specifies the power good power on threshold in mV.
    *   Valid range: 0-65535
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_pgoodOnThresholdList[] - defines power good voltage
    *   threshold for power on detection.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetPgoodOnThreshold(uint8 converterNum)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodOnThreshold")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_pgoodOnThresholdList[converterNum]);
    }

#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPowerUpMode
********************************************************************************
*
* Summary:
*  Sets the power up default state for the selected power converter.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  powerUpMode - Specifies the power up mode for the selected power converter.
*   Options: 0=manual, 1=automatic
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initState - defines the default states for all power
*  converters.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPowerUpMode(uint8 converterNum, uint8 powerUpMode)
                                                             `=ReentrantKeil($INSTANCE_NAME . "_SetPowerUpMode")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        if(powerUpMode == `$INSTANCE_NAME`_MANUAL)
        {
            `$INSTANCE_NAME`_initState[converterNum - 1u] = `$INSTANCE_NAME`_OFF;
        }
        else
        {
            `$INSTANCE_NAME`_initState[converterNum - 1u] = `$INSTANCE_NAME`_PEND_ON;
        }
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPowerUpMode
********************************************************************************
*
* Summary:
*  Returns the power up default state for the selected power converter.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  powerUpMode - Specifies the power up mode for the selected power converter.
*   Options: 0=manual, 1=automatic
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initState - defines the default states for all power
*  converters.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetPowerUpMode(uint8 converterNum)       `=ReentrantKeil($INSTANCE_NAME . "_GetPowerUpMode")`
{    
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_initState[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodOnPrereq
********************************************************************************
*
* Summary:
*  Determines which pgood[x] pins are power up prerequisites
*  for the selected power converter state machine.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  pgoodMask - specifies which pgood[x] pins are power up prerequisites
*   for the selected power converter.
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=pgood[1] must be asserted
*   1                  1=pgood[2] must be asserted
*   ...                ...
*   31                 1=pgood[32] must be asserted
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOnPrereqList[] - defines which pgood[x] pins
*   are power up pre-requisites for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodOnPrereq(uint8 converterNum, `$SeqBitsType` pgoodMask)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodOnPrereq")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
        
        `$INSTANCE_NAME`_pgoodOnPrereqList[converterNum - 1u] = pgoodMask;
        
        #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
            `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodOnPrereq
********************************************************************************
*
* Summary:
*  Returns which pgood[x] pins are power up prerequisites
*  for the selected power converter state machine.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  pgoodMask - specifies which pgood[x] pins are power up prerequisites
*   for the selected power converter.
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=pgood[1] must be asserted
*   1                  1=pgood[2] must be asserted
*   ...                ...
*   31                 1=pgood[32] must be asserted
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOnPrereqList[]- defines which pgood[x] pins
*   are power up pre-requisites for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetPgoodOnPrereq(uint8 converterNum)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodOnPrereq")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_pgoodOnPrereqList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodOffPrereq
********************************************************************************
*
* Summary:
*  Determines which pgood[x] pins are power down prerequisites
*  for the selected power converter state machine.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  pgoodMask - specifies which pgood[x] pins are power down prerequisites
*   for the selected power converter.
*   Bit Field          Power Good Power Down Pre-Requisite Mask
*   0                  1=pgood[1] must be de-asserted
*   1                  1=pgood[2] must be de-asserted
*   ...                ...
*   31                 1=pgood[32] must be de-asserted
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOffPrereqList[] - defines which pgood[x] pins
*   are power down pre-requisites for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodOffPrereq(uint8 converterNum, `$SeqBitsType` pgoodMask)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodOffPrereq")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
        
        `$INSTANCE_NAME`_pgoodOffPrereqList[converterNum - 1u] = pgoodMask;
        
        #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
            `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodOffPrereq
********************************************************************************
*
* Summary:
*  Returns which pgood[x] pins are power down prerequisites
*  for the selected power converter state machine.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  pgoodMask - specifies which pgood[x] pins are power down prerequisites
*   for the selected power converter.
*   Bit Field          Power Good Power Down Pre-Requisite Mask
*   0                  1=pgood[1] must be de-asserted
*   1                  1=pgood[2] must be de-asserted
*   ...                ...
*   31                 1=pgood[32] must be de-asserted
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodOffPrereqList[]- defines which pgood[x] pins
*   are power down pre-requisites for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetPgoodOffPrereq(uint8 converterNum)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodOffPrereq")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_pgoodOffPrereqList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonDelay
********************************************************************************
*
* Summary:
*  Sets the TON delay parameter for the selected power converter.
*  Defined as the time between a state machine's pre-requisites
*  all becoming satisfied and the en[x] being asserted.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  tonDelay - units = 0.25 ms per LSB if number of converters <= 16;
*                     0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonDelayList[] - defines TON_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonDelay(uint8 converterNum, uint16 tonDelay) `=ReentrantKeil($INSTANCE_NAME . "_SetTonDelay")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        #if(CY_PSOC3)
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 */
        `$INSTANCE_NAME`_tonDelayList[converterNum - 1u] = tonDelay;
        #if(CY_PSOC3)
            `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 */
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonDelay
********************************************************************************
*
* Summary:
*  Returns the TON delay parameter for the selected power converter.
*  Defined as the time between a state machine's pre-requisites
*  all becoming satisfied and the en[x] being asserted.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  tonDelay - units = 0.25 ms per LSB if number of converters <= 16;
*                     0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonDelayList[]- defines TON_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetTonDelay(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonDelay")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_tonDelayList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonMax
********************************************************************************
*
* Summary:
*  Sets the TON_MAX parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being asserted and pgood[x] being asserted. Failure to do
*  so generates a fault condition.
*
* Parameters:
*  converterNum - specifies the power converter number.
*  tonMax - units = 0.25 ms per LSB if number of converters <= 16;
*                   0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxDelayList[] - defines TON_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonMax(uint8 converterNum, uint16 tonMax) `=ReentrantKeil($INSTANCE_NAME . "_SetTonMax")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        #if(CY_PSOC3)
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 */
        `$INSTANCE_NAME`_tonMaxDelayList[converterNum - 1u] = tonMax;
        #if(CY_PSOC3)
            `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        #endif /* CY_PSOC3 */
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonMax
********************************************************************************
*
* Summary:
*  Returns the TON_MAX parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being asserted and pgood[x] being asserted. Failure to do
*  so generates a fault condition.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  tonMax - units = 0.25 ms per LSB if number of converters <= 16;
*                   0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxDelayList[] - defines TON_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetTonMax(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonMax")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_tonMaxDelayList[converterNum]);
}

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u)


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetPgoodOffThreshold
    ********************************************************************************
    *
    * Summary:
    *  Sets the power good voltage threshold for power off detection.
    *
    * Parameters:
    *  converterNum - specifies the converter number. Valid range: 1-32.
    *  offThreshold - specifies the power good power off threshold in mV.
    *   Valid range: 0-65535
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_pgoodOffThresholdList[] - defines power good voltage
    *   threshold for power off detection.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetPgoodOffThreshold(uint8 converterNum, uint16 offThreshold)
                                                        `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodOffThreshold")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            #if(CY_PSOC3)
                `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            #endif /* CY_PSOC3 */
            `$INSTANCE_NAME`_pgoodOffThresholdList[converterNum - 1u] = offThreshold;
            #if(CY_PSOC3)
                `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            #endif /* CY_PSOC3 */
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetPgoodOffThreshold
    ********************************************************************************
    *
    * Summary:
    *  Returns the power good voltage threshold for power off detection.
    *
    * Parameters:
    *  converterNum - specifies the converter number. Valid range: 1-32.
    *
    * Return:
    *  offThreshold - specifies the power good power off threshold in mV.
    *   Valid range: 0-65535
    *
    * Side Effects:
    *  None
    *
    * Global variables:
    *  `$INSTANCE_NAME`_pgoodOffThresholdList[] - defines power good voltage
    *   threshold for power off detection.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint16 `$INSTANCE_NAME`_GetPgoodOffThreshold(uint8 converterNum)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodOffThreshold")`
    {
        if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
        {
            converterNum--;
        }
        else
        {
            /* Halt CPU in debug mode if converterNum is out of valid range */
            CYASSERT(0u != 0u);
        }
        return (`$INSTANCE_NAME`_pgoodOffThresholdList[converterNum]);
    }

#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodStatus
********************************************************************************
*
* Summary:
*  Returns a bit mask containing the pgood status for all power converters.
* Parameters:
*  None
*
* Return:
*  pgoodStatus - pgood status of power converters:
*   Bit Field          Power Good Status
*   0                  1=pgood[1] is asserted
*                      0=pgood[1] is de-asserted
*   1                  1=pgood[2] is asserted
*                      0=pgood[2] is de-asserted
*   ...                ...
*   31                 1=pgood[32] is asserted
*                      0=pgood[32] is de-asserted
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodStatus - live pgood status for all converters.
*
* Reentrant:
*  No
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetPgoodStatus(void)   `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodStatus")`
{
    `$SeqBitsType` pgStatus;
    
    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */

    pgStatus = `$INSTANCE_NAME`_pgStatus;

    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
    return (pgStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodShutdownMask
********************************************************************************
*
* Summary:
*  Determines which other pgood[x] pins will shutdown the selected power
*  converter state machine when de-asserted.
*  Note that the pgood[converterNum] pin is automatically a fault
*  source for the selected power converter whether or not the
*  corresponding bit in the pgoodMask is set or not.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  pgoodMask - specifies which pgood[x] pins can cause a shutdown:
*   Bit Field          Power Good Mask
*   0                  1=pgood[1] de-assertion will shutdown the converter
*   1                  1=pgood[2] de-assertion will shutdown the converter
*   ...                ...
*   31                 1=pgood[32] de-assertion will shutdown the converter
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodShutdownMaskList[] - defines which pgood[x] pins
*   will cause shutdown for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodShutdownMask(uint8 converterNum, `$SeqBitsType` pgoodMask)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodShutdownMask")`
{
    uint8 bitPos;
    `$SeqBitsType` bitMask;

    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {   
        converterNum--;
        bitMask = (`$SeqBitsType`)1u << converterNum; /* Determine bit to set */
        `$INSTANCE_NAME`_pgoodShutdownMaskList[converterNum] = pgoodMask;
        pgoodMask |= bitMask;

        /* Block Sequencer and Fault Handler interrupts for atomic access */
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);

        for(bitPos = 0u; bitPos < `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS; bitPos++)
        {
            if((pgoodMask & 0x01u) == 0u)
            {
                `$INSTANCE_NAME`_pgoodGroupShutdownMask[bitPos] &= (`$SeqBitsType`)~bitMask;
            }
            else
            {
                `$INSTANCE_NAME`_pgoodGroupShutdownMask[bitPos] |= bitMask;
            }
            pgoodMask >>= 1u;
        }
        /* Enable blocked interrupts */        
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodShutdownMask
********************************************************************************
*
* Summary:
*  Returns which other pgood[x] pins will shutdown the selected power converter
*  when de-asserted.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  pgoodMask - specifies which pgood[x] pins can cause a shutdown:
*   Bit Field          Power Good Power Mask
*   0                  1=pgood[1] de-assertion will shutdown the converter
*   1                  1=pgood[2] de-assertion will shutdown the converter
*   ...                ...
*   31                 1=pgood[32] de-assertion will shutdown the converter
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodShutdownMaskList[] - defines which pgood[x] pins
*   will cause shutdown for each converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetPgoodShutdownMask(uint8 converterNum)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodShutdownMask")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_pgoodShutdownMaskList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetToffDelay
********************************************************************************
*
* Summary:
*  Sets the TOFF delay parameter for the selected power converter.
*  Defined as the time between making the decision to turn a power
*  converter of and to actually deasserting the en[x] pin.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  toffDelay - units = 0.25 ms per LSB if number of converters <= 16;
*                      0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffDelayList[] - defines TOFF_DELAY parameter for
*   each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetToffDelay(uint8 converterNum, uint16 toffDelay)
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_SetToffDelay")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_toffDelayList[converterNum - 1u] = toffDelay;
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetToffDelay
********************************************************************************
*
* Summary:
*  Returns the TOFF delay parameter for the selected power converter.
*  Defined as the time between making the decision to turn a power
*  converter of and to actually de-asserting the en[x] pin.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  toffDelay - units = 0.25 ms per LSB if number of converters <= 16;
*                      0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffDelayList[] - defines TOFF_DELAY parameter for
*   each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetToffDelay(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetToffDelay")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_toffDelayList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetToffMax
********************************************************************************
*
* Summary:
*  Sets the TOFF_MAX_DELAY parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being de-asserted and power converter actually turning off.
*  Failure to do so generates a warning condition.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*  toffMax - units = 0.25 ms per LSB if number of converters <= 16;
*                    0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffMaxDelayList[] - defines TOFF_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetToffMax(uint8 converterNum, uint16 toffMax) `=ReentrantKeil($INSTANCE_NAME . "_SetToffMax")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_toffMaxDelayList[converterNum - 1u] = toffMax;
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetToffMax
********************************************************************************
*
* Summary:
*  Returns the TOFF_MAX_DELAY parameter for the selected power converter.
*  Defined as the maximum time allowable between a power converter's
*  en[x] being de-asserted and power converter actually turning off.
*  Failure to do so generates a warning condition.
*
* Parameters:
*  converterNum - specifies the power converter state machine number.
*   Valid range: 1-32.
*
* Return:
*  toffMax - units = 0.25 ms per LSB if number of converters <= 16;
*                    0.50 ms per LSB if number of converters  > 16;
*   Valid Range=0-65535 (0-16.384 s if number of converters <= 16);
*                       (0-32.768 s if number of converters  > 16).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_toffMaxDelayList[] - defines TOFF_MAX_DELAY parameter
*   for each power converter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetToffMax(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetToffMax")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_toffMaxDelayList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetSysStableTime
********************************************************************************
*
* Summary:
*  Sets the global System Stable Time parameter.
*
* Parameters:
*  stableTime - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_sysStableTime - system Stable Time parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetSysStableTime(uint16 stableTime) `=ReentrantKeil($INSTANCE_NAME . "_SetSysStableTime")`
{
    #if(CY_PSOC3)
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    #endif /* CY_PSOC3 */
    `$INSTANCE_NAME`_sysStableTime = stableTime;
    #if(CY_PSOC3)
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    #endif /* CY_PSOC3 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSysStableTime
********************************************************************************
*
* Summary:
*  Returns the global System Stable Time parameter.
*
* Parameters:
*  None
*
* Return:
*  stableTime - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_sysStableTime - system Stable Time parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetSysStableTime(void) `=ReentrantKeil($INSTANCE_NAME . "_GetSysStableTime")`
{
    return (`$INSTANCE_NAME`_sysStableTime);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetReseqDelay
********************************************************************************
*
* Summary:
*  Sets the global TRESEQ_DELAY parameter for all power
*  converter state machines. Defined as the time between making the
*  decision to re-sequence and beginning a new power up sequence.
*
* Parameters:
*  reseqDelay - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_globalReseqDelay - global TRESEQ_DELAY parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetReseqDelay(uint16 reseqDelay) `=ReentrantKeil($INSTANCE_NAME . "_SetReseqDelay")`
{
    #if(CY_PSOC3)
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    #endif /* CY_PSOC3 */
    `$INSTANCE_NAME`_globalReseqDelay = reseqDelay;
    #if(CY_PSOC3)
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    #endif /* CY_PSOC3 */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetReseqDelay
********************************************************************************
*
* Summary:
*  Returns the global TRESEQ_DELAY parameter for all power
*  converter state machines. Defined as the time between making the
*  decision to re-sequence and beginning a new power up sequence.
*
* Parameters:
*  None
*
* Return:
*  reseqDelay - units = 8 ms per LSB. Valid Range=0-65535 (0-534.28 s).
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_globalReseqDelay - global TRESEQ_DELAY parameter.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetReseqDelay(void) `=ReentrantKeil($INSTANCE_NAME . "_GetReseqDelay")`
{
    return (`$INSTANCE_NAME`_globalReseqDelay);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonMaxReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for TON_MAX fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  reseqCnt - 5 bit number. Options: 0=no re-sequencing,
*   31=infinite resequencing, 1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonMaxReseqCnt(uint8 converterNum, uint8 ReseqCnt)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetTonMaxReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum - 1u] =
             (`$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum - 1u] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (ReseqCnt & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonMaxReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for TON_MAX fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. Options: 0=no re-sequencing,
*   31=infinite resequencing, 1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTonMaxReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonMaxReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTonMaxFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves when a TON_MAX fault
*  condition occurs on the selected master converter.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTonMaxFaultResp(uint8 converterNum, uint8 faultResponse)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetTonMaxFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum - 1u] =
            (uint8)(faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) |
            (`$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum - 1u] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTonMaxFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves when a TON_MAX fault
*  condition occurs on the selected master converter.
*
* Parameters:
*  converterNum - specifies the power converter number.
*   Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_tonMaxFaultReseqCfg[] - defines the re-sequence settings
*   for TON_MAX fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTonMaxFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTonMaxFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return ((`$INSTANCE_NAME`_tonMaxFaultReseqCfg[converterNum] >> `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFaultReseqSrc
********************************************************************************
*
* Summary:
*  Sets the power converter fault re-sequence sources.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqSrc:
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=OV fault source enabled
*   1                  1=UV fault source enabled
*   2                  1=OC fault source enabled
*   7:3                Reserved
*
* Return:
*  None
*
* Side Effects:
*  When reseqSrc is zero, power good (pgood) inputs
*  become the fault re-sequence source.
*
* Global variables:
*  `$INSTANCE_NAME`_faultReseqSrcList[] - defines the power converter fault
*   re-sequence sources.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFaultReseqSrc(uint8 converterNum, uint8 reseqSrc)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetFaultReseqSrc")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_faultReseqSrcList[converterNum - 1u] = reseqSrc;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultReseqSrc
********************************************************************************
*
* Summary:
*  Sets the power converter fault re-sequence sources.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqSrc:
*   Bit Field          Power Good Power Up Pre-Requisite Mask
*   0                  1=OV fault source enabled
*   1                  1=UV fault source enabled
*   2                  1=OC fault source enabled
*   7:3                Reserved
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultReseqSrcList[] - defines the power converter fault
*   re-sequence sources.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetFaultReseqSrc(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetFaultReseqSrc")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_faultReseqSrcList[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for fault conditions due to
*  de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:.
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodReseqCnt(uint8 converterNum, uint8 reseqCnt)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum - 1u] =
            (`$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum - 1u] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                        | (reseqCnt & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for fault conditions due to
*  de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetPgoodReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPgoodFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves for fault conditions
*  due to de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPgoodFaultResp(uint8 converterNum, uint8 faultResponse)
                                                            `=ReentrantKeil($INSTANCE_NAME . "_SetPgoodFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum - 1u] =
            (uint8)(faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) |
            (`$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum - 1u] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetPgoodFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves for fault conditions
*  due to de-asserted pgood[x] inputs.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters.
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_pgoodFaultReseqCfg[] - defines the re-sequence settings
*   for fault conditions due to de-asserted pgood[x] inputs.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetPgoodFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetPgoodFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return ((`$INSTANCE_NAME`_pgoodFaultReseqCfg[converterNum] >> `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOvReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for over-voltage (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ovFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOvReseqCnt(uint8 converterNum, uint8 reseqCnt)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOvReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_ovFaultReseqCfg[converterNum - 1u] =
            (`$INSTANCE_NAME`_ovFaultReseqCfg[converterNum - 1u] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOvReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for over-voltage (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ovFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOvReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOvReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_ovFaultReseqCfg[converterNum] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOvFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves due to overvoltage
*  (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for slave power converters
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ovFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOvFaultResp(uint8 converterNum, uint8 faultResponse)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOvFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_ovFaultReseqCfg[converterNum - 1u] =
            (uint8)(faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) |
            (`$INSTANCE_NAME`_ovFaultReseqCfg[converterNum - 1u] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOvFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves due to overvoltage
*  (OV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for slave power converters
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initOvFaultReseqCfg[] - defines the re-sequence settings
*   for OV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOvFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOvFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return ((`$INSTANCE_NAME`_ovFaultReseqCfg[converterNum] >> `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUvReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for under-voltage (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetUvReseqCnt(uint8 converterNum, uint8 reseqCnt)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetUvReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_uvFaultReseqCfg[converterNum - 1u] =
            (`$INSTANCE_NAME`_uvFaultReseqCfg[converterNum - 1u] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUvReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for under-voltage (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetUvReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetUvReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_uvFaultReseqCfg[converterNum] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUvFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves due to undervoltage
*  (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetUvFaultResp(uint8 converterNum, uint8 faultResponse)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetUvFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_uvFaultReseqCfg[converterNum - 1u] =
               (uint8)(faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) |
                      (`$INSTANCE_NAME`_uvFaultReseqCfg[converterNum - 1u] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUvFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves due to undervoltage
*  (UV) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_uvFaultReseqCfg[] - defines the re-sequence settings
*   for UV fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetUvFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetUvFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return ((`$INSTANCE_NAME`_uvFaultReseqCfg[converterNum] >> `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOcReseqCnt
********************************************************************************
*
* Summary:
*  Sets the re-sequence count for over-current (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOcReseqCnt(uint8 converterNum, uint8 reseqCnt)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOcReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_ocFaultReseqCfg[converterNum - 1u] =
            (`$INSTANCE_NAME`_ocFaultReseqCfg[converterNum - 1u] & `$INSTANCE_NAME`_RESP_CNT_MASK)
                                                                 | (reseqCnt & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOcReseqCnt
********************************************************************************
*
* Summary:
*  Returns the re-sequence count for over-current (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  reseqCnt - 5 bit number. 0=no re-sequencing, 31=infinite re-sequencing,
*   1-30=valid re-sequencing counts.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOcReseqCnt(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOcReseqCnt")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_ocFaultReseqCfg[converterNum] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOcFaultResp
********************************************************************************
*
* Summary:
*  Sets the shutdown mode for fault slaves due to overcurrent
*  (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetOcFaultResp(uint8 converterNum, uint8 faultResponse)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetOcFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_ocFaultReseqCfg[converterNum - 1u] =
               (uint8)(faultResponse << `$INSTANCE_NAME`_RESP_MODE_OFFSET) |
                      (`$INSTANCE_NAME`_ocFaultReseqCfg[(converterNum - 1u)] & (uint8)~`$INSTANCE_NAME`_RESP_CNT_MASK);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOcFaultResp
********************************************************************************
*
* Summary:
*  Returns the shutdown mode for fault slaves due to overcurrent
*  (OC) fault conditions.
*
* Parameters:
*  converterNum - specifies the power converter number. Valid range: 1-32.
*
* Return:
*  faultResponse - specifies the shutdown mode for any slave power converters
*   Options: 0=immediate, 1=soft.
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_ocFaultReseqCfg[] - defines the re-sequence settings
*   for OC fault conditions.
*
* Reentrant:
*  No
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetOcFaultResp(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOcFaultResp")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return ((`$INSTANCE_NAME`_ocFaultReseqCfg[converterNum] >> `$INSTANCE_NAME`_RESP_MODE_OFFSET) & 0x01u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnFaults
********************************************************************************
*
* Summary:
*  Enables/disables assertion of the fault output signal.
*  Faults are still processed by the state machine and fault
*  status is still available through the GetFaultStatus() API.
*
* Parameters:
*  faultEnable - Options: 0=disabled, 1=enabled.
*   Enabled when the component is started.
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultEnable - enable/disable assertion of the
*   fault output signal.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnFaults(uint8 faultEnable) `=ReentrantKeil($INSTANCE_NAME . "_EnFaults")`
{
    `$INSTANCE_NAME`_faultEnable = faultEnable;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetFaultMask
********************************************************************************
*
* Summary:
*  Sets which power converters have faults enabled.
*
* Parameters:
*  faultMask:
*   Bit Field          Fault Mask
*   0                  1=enable fault detection for power converter 1
*   1                  1=enable fault detection for power converter 2
*   ...                ...
*   31                 1=enable fault detection for power converter 32
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultMask - defines which power converters have
*   faults enabled.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetFaultMask(`$SeqBitsType` faultMask) `=ReentrantKeil($INSTANCE_NAME . "_SetFaultMask")`
{
    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
    
    `$INSTANCE_NAME`_faultMask = faultMask;
    
    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultMask
********************************************************************************
*
* Summary:
*  Gets which power converters have faults enabled.
*
* Parameters:
*  None
*
* Return:
*  faultMask:
*   Fault mask of power converters
*    Bit Field          Fault Mask
*    0                  1=fault detection for power converter 1 is enabled
*    1                  1=fault detection for power converter 2 is enabled
*    ...                ...
*    31                 1=fault detection for power converter 32 is enabled
*
* Return:
*  None
*
* Side Effects:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_faultMask - defines which power converters have
*   faults enabled.
*
* Reentrant:
*  No
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetFaultMask(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFaultMask")`
{
    return(`$INSTANCE_NAME`_faultMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetFaultStatus
********************************************************************************
*
* Summary:
*  Returns a bit mask containing the pgood fault status for all power
*  converters. Bits are sticky until cleared by calling this API.
*
* Parameters:
*  None
*
* Return:
*  faultStatus:
*   Fault status of power converters
*   Bit Field          Fault Mask
*   0                  1=power converter 1 has/had a fault
*   1                  1=power converter 2 has/had a fault
*   ...                ...
*   31                 1=power converter 32 has/had a fault
*
* Side Effects:
*  Calling this API de-asserts the fault output pin.
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetFaultStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetFaultStatus")`
{
    `$SeqBitsType` faultStatus;

    /* Block Sequencer and Fault Handler interrupts for atomic access */
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);

    faultStatus = `$INSTANCE_NAME`_faultStatus;
    `$INSTANCE_NAME`_faultStatus = 0u;

    /* Enable blocked interrupts */
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    return (faultStatus);
}

#if (`$INSTANCE_NAME`_ENABLE_WARNINGS != 0u)

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnWarnings
    ********************************************************************************
    *
    * Summary:
    *  Enables/disables assertion of the warn output signal.
    *  Warning status is still available through the GetWarningStatus() API.
    *
    * Parameters:
    *  warnEnable:
    *   Options: 0=disabled, 1=enabled
    *   Enabled when the component is started
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EnWarnings(uint8 warnEnable) `=ReentrantKeil($INSTANCE_NAME . "_EnWarnings")`
    {
        `$INSTANCE_NAME`_warnEnable = warnEnable;
    }

#endif /* `$INSTANCE_NAME`_ENABLE_WARNINGS != 0u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetWarnMask
********************************************************************************
*
* Summary:
*  Sets which power converters have warnings enabled.
*
* Parameters:
*  warnMask:
*   Bit Field          Warning Mask
*   0                  1=enable warnings for power converter 1
*   1                  1=enable warnings for power converter 2
*   ...                ...
*   31                 1=enable warnings for power converter 32
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetWarnMask(`$SeqBitsType` warnMask) `=ReentrantKeil($INSTANCE_NAME . "_SetWarnMask")`
{
    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
    
    `$INSTANCE_NAME`_warnMask = warnMask;
    
    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetWarnMask
********************************************************************************
*
* Summary:
*  Returns which power converters have warnings enabled.
*
* Parameters:
*  None
*
* Return:
*  warnMask:
*   Bit Field          Warning Mask
*   0                  1=warnings for power converter 1 are enabled
*   1                  1=warnings for power converter 2 are enabled
*   ...                ...
*   31                 1=warnings for power converter 32 are enabled
*
* Side Effects:
*  None
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetWarnMask(void) `=ReentrantKeil($INSTANCE_NAME . "_GetWarnMask")`
{
    return (`$INSTANCE_NAME`_warnMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetWarnStatus
********************************************************************************
*
* Summary:
*  Returns a bit mask containing TOFF_MAX_WARN warning status
*  for all power converters. Bits are sticky until
*  cleared by calling this API.
*
* Parameters:
*  None
*
* Return:
*  warnStatus:
*   Warn status of power converters
*   Bit Field          Warning Status
*   0                  1=power converter 1 has/had a warning
*   1                  1=power converter 2 has/had a warning
*   ...                ...
*   31                 1=power converter 32 has/had a warning
*
* Side Effects:
*  Calling this API de-asserts the warn output pin.
*
*******************************************************************************/
`$SeqBitsType` `$INSTANCE_NAME`_GetWarnStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_GetWarnStatus")`
{
    `$SeqBitsType` warnStatus;

    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    warnStatus = `$INSTANCE_NAME`_warnStatus;
    `$INSTANCE_NAME`_warnStatus = 0u;
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    return (warnStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetState
********************************************************************************
*
* Summary:
*  Returns the current state machine state for the selected
*  power converter.
*
* Parameters:
*  converterNum:
*   Specifies the power converter number
*   Valid range: 1-32
*
* Return:
*  State:
*   Power converter state machine state
*   Encoding           State
*   0                  OFF
*   1                  PEND_ON
*   2                  TON_DELAY
*   3                  TON_MAX
*   4                  ON
*   5                  TOFF_DELAY
*   6                  TOFF_MAX
*   7                  PEND_RESEQ
*   8                  TRESEQ_DELAY
*   9..255             Undefined
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetState(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_GetState")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
    return (`$INSTANCE_NAME`_state[converterNum]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceOff
********************************************************************************
*
* Summary:
*  Forces the selected power converter to power down
*  either immediately or after the TOFF delay.
*
* Parameters:
*  converterNum:
*   Specifies the power converter number
*   Valid range: 1-32
*  powerOffMode:
*   Specifies the shutdown mode
*   Options: 0=immediate, 1=soft
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceOff(uint8 converterNum, uint8 powerOffMode) `=ReentrantKeil($INSTANCE_NAME . "_ForceOff")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        converterNum--;
        /* Block Sequencer and Fault Handler interrupts for atomic access */
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    
        if(powerOffMode == `$INSTANCE_NAME`_IMMEDIATE_OFF)
        {
            /* Immediate shutdown */
            `$INSTANCE_NAME`_forceOffModeReg &= (`$SeqBitsType`)~(`$SeqBitsType`)((`$SeqBitsType`)1u << converterNum);
        }
        else
        {
            /* Soft shutdown */
            `$INSTANCE_NAME`_forceOffModeReg |= (`$SeqBitsType`) ((`$SeqBitsType`)1u << converterNum);
        }
        `$INSTANCE_NAME`_forceOffCmdReg  |= (`$SeqBitsType`) ((`$SeqBitsType`)1u << converterNum);

        /* Indicate that converters are intentionally going off */ 
        `$INSTANCE_NAME`_pendingOff |= (`$SeqBitsType`)((`$SeqBitsType`)1u << converterNum);

        /* Enable blocked interrupts */
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceAllOff
********************************************************************************
*
* Summary:
*  Forces all power converters to power down either
*  immediately or after their TOFF delays.
*
* Parameters:
*  powerOffMode:
*   Specifies the shutdown mode
*   Options: 0=immediate, 1=soft
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceAllOff(uint8 powerOffMode) `=ReentrantKeil($INSTANCE_NAME . "_ForceAllOff")`
{
    /* Block Sequencer and Fault Handler interrupts for atomic access */
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    
    if(powerOffMode == `$INSTANCE_NAME`_IMMEDIATE_OFF)
    {
        /* Immediate shutdown */
        `$INSTANCE_NAME`_forceOffModeReg = 0u;
    }
    else
    {
        /* Soft shutdown */
        `$INSTANCE_NAME`_forceOffModeReg = `$INSTANCE_NAME`_CONVERTER_MASK;
    }
    `$INSTANCE_NAME`_forceOffCmdReg = `$INSTANCE_NAME`_CONVERTER_MASK;
    
    /* Indicate that converters are intentionally going off */ 
    `$INSTANCE_NAME`_pendingOff = `$INSTANCE_NAME`_CONVERTER_MASK;
     
    /* Enable blocked interrupts */
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceOn
********************************************************************************
*
* Summary:
*  Forces the selected power converter to the PEND_ON state. All selected 
*  power up pre-requisite conditions must be satisfied for the power converter
*  to turn on. The re-sequence counter for that converter's state machine is
*  re-initialized.
*
* Parameters:
*  converterNum:
*   Specifies the power converter number
*   Valid range: 1-32
*
* Return:
*  None
*
* Side Effects:
*  Reset the re-sequence counter for the selected power converter.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceOn(uint8 converterNum) `=ReentrantKeil($INSTANCE_NAME . "_ForceOn")`
{
    if((converterNum > 0u) && (converterNum <= `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS))
    {
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
        `$INSTANCE_NAME`_forceOnCmdReg |= (`$SeqBitsType`)((`$SeqBitsType`)1u << (converterNum - 1u));
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    }
    else
    {
        /* Halt CPU in debug mode if converterNum is out of valid range */
        CYASSERT(0u != 0u);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ForceAllOn
********************************************************************************
*
* Summary:
*  Forces all power converters to the PEND_ON state. All selected power up 
*  pre-requisite conditions must be satisfied for the power converters to 
*  turn on. The re-sequence counters for all converters' state machines are
*  re-initialized.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Reset the re-sequence counters for all power converters.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ForceAllOn(void) `=ReentrantKeil($INSTANCE_NAME . "_ForceAllOn")`
{
    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */

    `$INSTANCE_NAME`_forceOnCmdReg = `$INSTANCE_NAME`_CONVERTER_MASK;

    #if(CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u))
        `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    #endif /* CY_PSOC3 && (`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS > 8u) */
}

#if(`$INSTANCE_NAME`_DEBUG_MODE != 0u)

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_Pause
    ****************************************************************************
    * Summary:
    *  Pause the sequencer, preventing sequencer state machine state 
    *  transitions, system timer updates and fault handling.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  All 3 sequencer interrupts are disabled.
    *  While faulty rails will be shutdown immediately upon fault detection 
    *  due to the hardware fast shutdown block, fault slaves will not be 
    *  turned off while the sequencer is paused.
    ***************************************************************************/
    void `$INSTANCE_NAME`_Pause(void) `=ReentrantKeil($INSTANCE_NAME . "_Pause")`
    {
        uint8 enableInterrupts;
        
        if(`$INSTANCE_NAME`_SEQUENCER_PLAY == `$INSTANCE_NAME`_operatingMode)
        {
            enableInterrupts = CyEnterCriticalSection();
            /* Disable the sequencer tick timer */
            `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG &= (uint8)~`$INSTANCE_NAME`_TICK_TIMER_EN;
            CyExitCriticalSection(enableInterrupts);

            /* Disable and flush pending interrupts */
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);    
            CyIntClearPending(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            CyIntClearPending(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
            CyIntClearPending(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
            `$INSTANCE_NAME`_operatingMode = `$INSTANCE_NAME`_SEQUENCER_PAUSE;
        }
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_Play
    ****************************************************************************
    * Summary:
    *  Resumes the sequencer if previously paused. Re-enables sequencer state
    *  machine state transitions, system timer updates and fault handling.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  All 3 sequencer interrupts are enabled.
    ***************************************************************************/
    void `$INSTANCE_NAME`_Play(void) `=ReentrantKeil($INSTANCE_NAME . "_Play")`
    {
        uint8 enableInterrupts;
        
        `$INSTANCE_NAME`_singleStepMode = `$INSTANCE_NAME`_SINGLE_STEP_OFF;
        
        if(`$INSTANCE_NAME`_SEQUENCER_PAUSE == `$INSTANCE_NAME`_operatingMode)
        {
            `$INSTANCE_NAME`_operatingMode  = `$INSTANCE_NAME`_SEQUENCER_PLAY;
            
            CyIntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
            CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            CyIntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
            
            /* Enable the sequencer tick timer */
            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG |= `$INSTANCE_NAME`_TICK_TIMER_EN;
            CyExitCriticalSection(enableInterrupts);
        }
    }


    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_SingleStep
    ****************************************************************************
    * Summary:
    *  Puts the sequencer in single step mode. If the sequencer was paused, it 
    *  will resume normal operation. The sequencer will then run until there is
    *  a state transition on any rail. At that time, the sequencer will be
    *  paused automatically until the user takes action by either calling the
    *  Play() API or calling the SingleStep() again.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  All 3 sequencer interrupts are enabled until a state transition occurs
    *  on any rail. At that time, all 3 sequencer interrupts will be disabled
    *  again.
    ***************************************************************************/
    void `$INSTANCE_NAME`_SingleStep(void) `=ReentrantKeil($INSTANCE_NAME . "_SingleStep")`
    {
        uint8 enableInterrupts;
        `$INSTANCE_NAME`_singleStepMode = `$INSTANCE_NAME`_SINGLE_STEP_ON;

        if(`$INSTANCE_NAME`_SEQUENCER_PAUSE == `$INSTANCE_NAME`_operatingMode)
        {
            `$INSTANCE_NAME`_operatingMode  = `$INSTANCE_NAME`_SEQUENCER_PLAY;
            
            CyIntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
            CyIntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
            CyIntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
            
            /* Enable the sequencer tick timer */
            enableInterrupts = CyEnterCriticalSection();
            `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG |= `$INSTANCE_NAME`_TICK_TIMER_EN;
            CyExitCriticalSection(enableInterrupts);
        }
    }

#endif /* `$INSTANCE_NAME`_DEBUG_MODE != 0u */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableCalibrationState
********************************************************************************
* Summary:
*  Enables the sequencer calibration state, preventing sequencer state machine
*  state transitions, system timer updates and fault handling. 
*  Stops the hardware fast shutdown block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All 3 sequencer interrupts are disabled.
*  Power converter enable outputs will hold their states while the sequencer is
*  in calibration state. Faults will not be detected and faulty rails will not
*  be shutdown. 
*******************************************************************************/
void `$INSTANCE_NAME`_EnableCalibrationState(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableCalibrationState")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    /* Disable the sequencer tick timer */
    `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG &= (uint8)~`$INSTANCE_NAME`_TICK_TIMER_EN;
    CyExitCriticalSection(enableInterrupts);

    /* Stop the hardware fast shutdown block */
    `$INSTANCE_NAME`_SYSTEM_STATUS_REG &= (uint8)~`$INSTANCE_NAME`_RAPID_RESPONSE_EN;

    /* Disable and flush pending interrupts */
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntDisable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);    
    CyIntClearPending(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    CyIntClearPending(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableCalibrationState
********************************************************************************
* Summary:
*  Disables the sequencer calibration state. Re-enables sequencer state machine
*  state transitions, system timer updates and fault handling.
*  Enables the hardware fast shutdown block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All 3 sequencer interrupts are enabled.
*******************************************************************************/
void `$INSTANCE_NAME`_DisableCalibrationState(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableCalibrationState")`
{
    uint8 enableInterrupts;
    
    /* Read ctl[x] sticky bits to clear false faults that might be sampled
    * while the the sequencer was in calibration state.
    */
    #if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)
        (void)`$INSTANCE_NAME`_CTL_MON_REG;
    #endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */
    
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_STABLE_TIMER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_SEQUENCER_ISR_NUMBER);
    `$INSTANCE_NAME`_IntEnable(`$INSTANCE_NAME`_FAULT_ISR_NUMBER);

    /* Enable the hardware fast shutdown block */
    `$INSTANCE_NAME`_SYSTEM_STATUS_REG |= `$INSTANCE_NAME`_RAPID_RESPONSE_EN;

    /* Enable the sequencer tick timer */
    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_TICK_TIMER_AUX_CTL_REG |= `$INSTANCE_NAME`_TICK_TIMER_EN;
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
