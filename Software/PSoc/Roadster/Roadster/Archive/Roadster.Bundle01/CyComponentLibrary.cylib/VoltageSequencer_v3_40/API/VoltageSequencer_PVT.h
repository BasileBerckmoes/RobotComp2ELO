/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the Voltage
*  Sequencer component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VOLTAGE_SEQUENCER_PVT_`$INSTANCE_NAME`_H)
#define CY_VOLTAGE_SEQUENCER_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/*******************************************************************************
*       Macros to accelerate processing of 32-bit variables
*******************************************************************************/

#if(`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS <= 8u)
    #define `$INSTANCE_NAME`_SET_BIT(var, grp, msk)    ((var) |= (msk))
    #define `$INSTANCE_NAME`_TEST_BIT(var, grp, msk)   ((var) &  (msk))
    #define `$INSTANCE_NAME`_GET_GROUP(var, grp)        (var)
    #define `$INSTANCE_NAME`_SET_VBIT(var, grp, msk)   `$INSTANCE_NAME`_SET_BIT(var, grp, msk)
    #define `$INSTANCE_NAME`_TEST_VBIT(var, grp, msk)  `$INSTANCE_NAME`_TEST_BIT(var, grp, msk)
    #define `$INSTANCE_NAME`_CLEAR_VBIT(var, grp, msk) ((var) &= (uint8)~(msk))
#else
    #define `$INSTANCE_NAME`_SET_BIT(var, grp, msk)    ((((uint8 *)&(var))[grp]) |= (msk))
    #define `$INSTANCE_NAME`_TEST_BIT(var, grp, msk)   ((((uint8 *)&(var))[grp]) &  (msk))
    #define `$INSTANCE_NAME`_GET_GROUP(var, grp)       ((( uint8 *)&(var))[grp])
    #define `$INSTANCE_NAME`_SET_VBIT(var, grp, msk)   ((((volatile uint8 *)&(var))[grp]) |= (msk))
    #define `$INSTANCE_NAME`_TEST_VBIT(var, grp, msk)  ((((volatile uint8 *)&(var))[grp]) &  (msk))
    #define `$INSTANCE_NAME`_CLEAR_VBIT(var, grp, msk) ((((volatile uint8 *)&(var))[grp]) &= (uint8)~(msk))
#endif /* `$INSTANCE_NAME`_NUMBER_OF_CONVERTERS <= 8u */


/*******************************************************************************
* While debug mode is enabled and the Sequencer is paused, the disabled ISR
* are not reenabled to prevent unintended resuming of Play mode.
*******************************************************************************/

#if(`$INSTANCE_NAME`_DEBUG_MODE != `$INSTANCE_NAME`_DISABLED)
    #define `$INSTANCE_NAME`_IntEnable(irqNum) \
        do { \
            if(`$INSTANCE_NAME`_operatingMode != `$INSTANCE_NAME`_SEQUENCER_PAUSE) \
            { \
                CyIntEnable(irqNum); \
            } \
        } while (0)
#else
    #define `$INSTANCE_NAME`_IntEnable(irqNum)  CyIntEnable(irqNum)
#endif /* `$INSTANCE_NAME`_DEBUG_MODE != `$INSTANCE_NAME`_DISABLED */
    
#define `$INSTANCE_NAME`_IntDisable(irqNum)     CyIntDisable(irqNum)


/*******************************************************************************
*       Power Up Configuration Variables
*******************************************************************************/

extern const `$SeqBitsType` CYCODE `$INSTANCE_NAME`_initPgoodOnPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_initTonDelayList     [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_initTonMaxDelayList  [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       `$SeqBitsType`        `$INSTANCE_NAME`_pgoodOnPrereqList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint16        `$INSTANCE_NAME`_tonDelayList         [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint16        `$INSTANCE_NAME`_tonMaxDelayList      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint16        `$INSTANCE_NAME`_sysStableTime;

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u)
    extern const uint16 CYCODE `$INSTANCE_NAME`_initPgoodOnThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern       uint16        `$INSTANCE_NAME`_pgoodOnThresholdList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_ON != 0u */


/*******************************************************************************
*       Control Input Configuration Variables
*******************************************************************************/

#if(`$INSTANCE_NAME`_CTL_INPUTS_EXIST)   
    extern const uint8  CYCODE `$INSTANCE_NAME`_initCtlPrereqList      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern const uint8  CYCODE `$INSTANCE_NAME`_initCtlShutdownMaskList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern const uint8  CYCODE `$INSTANCE_NAME`_initCtlFaultReseqCfg   [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern       uint8         `$INSTANCE_NAME`_ctlPrereqList          [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern       uint8         `$INSTANCE_NAME`_ctlFaultReseqCfg       [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern       `$SeqBitsType`        `$INSTANCE_NAME`_ctlGroupShutdownMask   [`$INSTANCE_NAME`_NUMBER_OF_CTL_INPUTS];
    extern       uint8         `$INSTANCE_NAME`_ctlShutdownMaskList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern volatile uint8 `$INSTANCE_NAME`_ctlStatus;
#endif /* `$INSTANCE_NAME`_CTL_INPUTS_EXIST */


/*******************************************************************************
*      Power Down Configaration Variables
*******************************************************************************/

extern const `$SeqBitsType` CYCODE `$INSTANCE_NAME`_initPgoodOffPrereqList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_initToffDelayList     [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint16 CYCODE `$INSTANCE_NAME`_initToffMaxDelayList  [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       `$SeqBitsType`        `$INSTANCE_NAME`_pgoodOffPrereqList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint16        `$INSTANCE_NAME`_toffDelayList         [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint16        `$INSTANCE_NAME`_toffMaxDelayList      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

#if(`$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u)
    extern const uint16 CYCODE `$INSTANCE_NAME`_initPgoodOffThresholdList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
    extern       uint16        `$INSTANCE_NAME`_pgoodOffThresholdList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
#endif /* `$INSTANCE_NAME`_ENABLE_PGOOD_OFF != 0u */


/*******************************************************************************
*       Fault Response and Resequence Configuration Variables
*******************************************************************************/

extern       uint16        `$INSTANCE_NAME`_globalReseqDelay;
extern const `$SeqBitsType` CYCODE `$INSTANCE_NAME`_initPgoodShutdownMaskList[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint8  CYCODE `$INSTANCE_NAME`_initTonMaxFaultReseqCfg  [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint8  CYCODE `$INSTANCE_NAME`_initPgoodFaultReseqCfg   [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint8  CYCODE `$INSTANCE_NAME`_initOvFaultReseqCfg      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint8  CYCODE `$INSTANCE_NAME`_initUvFaultReseqCfg      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint8  CYCODE `$INSTANCE_NAME`_initOcFaultReseqCfg      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern const uint8  CYCODE `$INSTANCE_NAME`_initFaultReseqSrcList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       `$SeqBitsType`        `$INSTANCE_NAME`_pgoodShutdownMaskList    [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       `$SeqBitsType`        `$INSTANCE_NAME`_pgoodGroupShutdownMask   [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint8         `$INSTANCE_NAME`_tonMaxFaultReseqCfg      [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint8         `$INSTANCE_NAME`_pgoodFaultReseqCfg       [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint8         `$INSTANCE_NAME`_ovFaultReseqCfg          [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint8         `$INSTANCE_NAME`_uvFaultReseqCfg          [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint8         `$INSTANCE_NAME`_ocFaultReseqCfg          [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern       uint8         `$INSTANCE_NAME`_faultReseqSrcList        [`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];


/*******************************************************************************
*       Sequencer Command and Status Registers
*******************************************************************************/

extern volatile `$SeqBitsType` `$INSTANCE_NAME`_forceOnCmdReg;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_forceOffCmdReg;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_forceOffModeReg;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_faultStatus;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_warnStatus;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_faultCond;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_pgStatus;
extern volatile `$SeqBitsType` `$INSTANCE_NAME`_pendingOff;

/*******************************************************************************
*      Output Configuration Registers
*******************************************************************************/

extern `$SeqBitsType` `$INSTANCE_NAME`_faultMask;
extern uint8  `$INSTANCE_NAME`_faultEnable;
extern `$SeqBitsType` `$INSTANCE_NAME`_warnMask;

#if (`$INSTANCE_NAME`_ENABLE_WARNINGS != 0u)
    extern uint8 `$INSTANCE_NAME`_warnEnable;
#endif /* `$INSTANCE_NAME`_ENABLE_WARNINGS != 0u */

#if(`$INSTANCE_NAME`_STS_OUTPUTS_EXIST)
    extern const `$SeqBitsType` CYCODE `$INSTANCE_NAME`_initStsPgoodMaskList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
    extern const `$SeqBitsType` CYCODE `$INSTANCE_NAME`_initStsPgoodPolarityList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
    extern `$SeqBitsType` `$INSTANCE_NAME`_stsPgoodMaskList    [`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
    extern `$SeqBitsType` `$INSTANCE_NAME`_stsPgoodPolarityList[`$INSTANCE_NAME`_NUMBER_OF_STS_OUTPUTS];
#endif /* `$INSTANCE_NAME`_STS_OUTPUTS_EXIST */


/*******************************************************************************
*       Sequencer State Machine State Variable
*******************************************************************************/

extern uint8 `$INSTANCE_NAME`_initState[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];
extern CYPDATA volatile uint8   `$INSTANCE_NAME`_state[`$INSTANCE_NAME`_NUMBER_OF_CONVERTERS];

/* Enable pin last sample */
extern volatile CYBIT `$INSTANCE_NAME`_enPinLast;

#endif /* (CY_VOLTAGE_SEQUENCER_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
