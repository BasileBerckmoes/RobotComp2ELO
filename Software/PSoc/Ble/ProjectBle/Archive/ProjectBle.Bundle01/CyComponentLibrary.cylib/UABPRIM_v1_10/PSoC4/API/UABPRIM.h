/*!*****************************************************************************
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief 
*   API for Universal Analog Block (UAB)
*
********************************************************************************
* \copyright
* (c) 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`_H

#include "cytypes.h"
#include "`$INSTANCE_NAME`_CyUAB_types.h"
#include "`$INSTANCE_NAME`_CyUAB.h"
#include "`$INSTANCE_NAME`_regs.h"


/* Switch function implementation */

/* Dynamic and Static Switch control field shift and mask values */

/* sw_id:= switch identifier - See CyUAB_sw_id_enum -
values are not arbitrary - they are packed with:
register address offset, 
the switch control field shift value, and 
boolean "x" flag for switches that interact with the x inputs */

/* The x inputs are an abstract concept of analog inputs of the UABPRIM that 
PSoC Creator P&R maps to the underlying UAB hardware's vin analog inputs -
this shuffling of the inputs give the analog router more freedom */

/* Switch IDs that have the x flag set are switches that connect to the x inputs */

/* x input field shift value:= abstract UABPRIM instance x analog input switch field shift value (0,4,8,12) */    
/* x input index:= abstract UABPRIM instance x input switch number (0...3) */
/* vin input index:= underlying hardware UAB vin input switch number (0...3)  */
/* vin input field shift value:= underlying hardware UAB vin input switch field shift value (0,4,8,12) */

/* conversion process with nested macros: 
sw_id -> x input field shift value -> x input index -> vin input index -> vin input field shift value */   






/* Static switch control fields occupy 1 bit to configure statically open or statically closed. */
#define `$INSTANCE_NAME`_STATIC_PRESHIFT_MASK  1UL
/* Dynamic switch control fields occupy 4 bits to select one of twelve waveforms, statically open, or statically closed */
#define `$INSTANCE_NAME`_DYNAMIC_PRESHIFT_MASK 0xfUL

/* Spacing between the LSbit of each static switch field */
/* needed when converting between the field shift location and the number of the shuffled x analog inputs */
#define `$INSTANCE_NAME`_STATIC_FIELD_SIZE  1UL

/* Spacing between the LSbit of each dynamic switch field */
/* needed when converting between the field shift location and the number of the shuffled x analog inputs */
#define `$INSTANCE_NAME`_DYNAMIC_FIELD_SIZE 4UL


/*Macros*/

/* Find UAB vin input index from UABPRIM x input index with cyfitter.h mappings */
#if !defined(`$INSTANCE_NAME`_Vin)
#define `$INSTANCE_NAME`_Vin(xIndex) (\
    (0UL==(xIndex))? ((uint32)`$INSTANCE_NAME`_X0) : (\
    (1UL==(xIndex))? ((uint32)`$INSTANCE_NAME`_X1) : (\
    (2UL==(xIndex))? ((uint32)`$INSTANCE_NAME`_X2) : (\
                   ((uint32)`$INSTANCE_NAME`_X3) \
))))
#endif
    
/* static switch, get x input index from switch id by down-scaling the x input field shift value by the field size */
#define `$INSTANCE_NAME`_StaticXin(sw_id)     ( CyUAB_GetSwShift((sw_id)) / `$INSTANCE_NAME`_STATIC_FIELD_SIZE )    
    
/* static switch, get the vin input field shift value by converting x input index to vin input index and up-scaling by the field size */
#define `$INSTANCE_NAME`_StaticVShift(sw_id)  ( `$INSTANCE_NAME`_Vin( `$INSTANCE_NAME`_StaticXin((sw_id)) ) * `$INSTANCE_NAME`_STATIC_FIELD_SIZE )
/* static switch, if id refers to an x input, handle the shuffling, otherwise just unpack the field shift from id */
#define `$INSTANCE_NAME`_StaticSwShift(sw_id)   ( CyUAB_IsSwX((sw_id)) ? `$INSTANCE_NAME`_StaticVShift((sw_id)) : CyUAB_GetSwShift((sw_id)) )
/* static switch, post shift mask */
#define `$INSTANCE_NAME`_StaticSwMask(sw_id)    ( `$INSTANCE_NAME`_STATIC_PRESHIFT_MASK<<`$INSTANCE_NAME`_StaticSwShift((sw_id)) )

/* static switch address */
#define `$INSTANCE_NAME`_GetStaticSwAddr(sw_id)  ( (reg32*)( ((uint32)`$INSTANCE_NAME`_BASE_ADDR) + ((uint32)(CyUAB_GetSwAddr((sw_id)) )) ) )
    

/* dynamic switch, get x input index from switch id by down-scaling the x input field shift value by the field size */
#define `$INSTANCE_NAME`_DynamicXin(sw_id)    ( CyUAB_GetSwShift((sw_id)) / `$INSTANCE_NAME`_DYNAMIC_FIELD_SIZE )
/* dynamic switch, get the vin input field shift value by converting x input index to vin input index and up-scaling by the field size */
#define `$INSTANCE_NAME`_DynamicVShift(sw_id) ( `$INSTANCE_NAME`_Vin( `$INSTANCE_NAME`_DynamicXin((sw_id)) ) * `$INSTANCE_NAME`_DYNAMIC_FIELD_SIZE )
/* dynamic switch, if id refers to an x input, handle the shuffling, otherwise just unpack the field shift from id */
#define `$INSTANCE_NAME`_DynamicSwShift(sw_id)  ( CyUAB_IsSwX((sw_id)) ? `$INSTANCE_NAME`_DynamicVShift((sw_id)) : CyUAB_GetSwShift((sw_id)) )
/* dynamic switch, post shift mask */
#define `$INSTANCE_NAME`_DynamicSwMask(sw_id)   ( `$INSTANCE_NAME`_DYNAMIC_PRESHIFT_MASK<<`$INSTANCE_NAME`_DynamicSwShift((sw_id)) )

/* dynamic switch address - handle SW_AA, SW_BB, and SW_CC */
#define `$INSTANCE_NAME`_GetDynamicSwAddr(sw_id)  ( (CyUAB_SW_AA==(sw_id)) ? `$INSTANCE_NAME`_SW_AA_PTR : (\
    (CyUAB_SW_BB==(sw_id)) ? `$INSTANCE_NAME`_SW_BB_PTR : ( \
    (CyUAB_SW_CC==(sw_id)) ? `$INSTANCE_NAME`_SW_CC_PTR : ( \
    ( (reg32*)( ((uint32)`$INSTANCE_NAME`_BASE_ADDR) + ((uint32)(CyUAB_GetSwAddr((sw_id)) )) ) ) \
) ) ) )



#include "`$INSTANCE_NAME`_param.h"


/*! Calculate waveConfig array size */
#define `$INSTANCE_NAME`_NUM_STEPS ( (uint8)( \
(`$INSTANCE_NAME`_INC_STEP_0  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_1  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_2  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_3  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_4  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_5  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_6  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_7  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_8  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_9  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_10 ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_11 ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_12 ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_13 ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_14 ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_INC_STEP_15 ? 1UL : 0UL) ) )

/*! initPairs array index of default OA_CTRL */
#define `$INSTANCE_NAME`_IDX_OA_CTRL       (0UL)
/*! initPairs array index of default SW_STATIC */
#define `$INSTANCE_NAME`_IDX_SW_STATIC     (1UL)
/*! initPairs array index of default SW_MODBIT_SRC */
#define `$INSTANCE_NAME`_IDX_SW_MODBIT_SRC (2UL)
/*! initPairs array index of default SRAM_CTRL */
#define `$INSTANCE_NAME`_IDX_SRAM_CTRL     (3UL)

/*! Calculate initPairs array size*/
#define `$INSTANCE_NAME`_INIT_PAIRS_COUNT ( \
(`$INSTANCE_NAME`_NONZERO_OA_CTRL        ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_STATIC      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_MODBIT_SRC  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SRAM_CTRL      ? 1UL : 0UL) + \
  \
(`$INSTANCE_NAME`_NONZERO_INTR_MASK      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_CAP_CTRL       ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_CAP_ABCF_VAL   ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_CAP_AB_VAL_NXT ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_CAP_CF_VAL_NXT ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_STARTUP_DELAY  ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SUBSAMPLE_CTRL ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CA_IN0      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CA_IN1      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CA_TOP      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CB_IN0      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CB_IN1      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CB_TOP      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CC_IN0      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CC_IN1      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CC_TOP      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_CF_BOT      ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_OTHER       ? 1UL : 0UL) + \
(`$INSTANCE_NAME`_NONZERO_SW_BOOST_CTRL  ? 1UL : 0UL) \
)

/***************************************
*    Variables with External Linkage
***************************************/
/*!
* \addtogroup group_globals
* Globals are noted in the descriptions of the functions that use globals.
* They are marked with (R), (W), or (RW) noting whether the variable is read,
* write, or read/write.
* @{
*/
/*! Tracks whether block is initialized (1) or not (0). */
extern uint32 `$INSTANCE_NAME`_initVar;
extern CyUAB_config `$INSTANCE_NAME`_config;
extern uint16 `$INSTANCE_NAME`_waveConfig[`$INSTANCE_NAME`_NUM_STEPS];
extern CyUAB_reg_pair `$INSTANCE_NAME`_initPairs[`$INSTANCE_NAME`_INIT_PAIRS_COUNT];


/*! @} globals */

/*------------------ Function Prototypes -------------------------------------*/


    
/*!
* \addtogroup group_init
* @{
*/    
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_Init(const CyUAB_config* cfg);
void `$INSTANCE_NAME`_Enable(void);


/*! @} group_init */

/* Support function for `$INSTANCE_NAME`_Init()
prototyp here for MISRA compliance - exclude from group_init */
void `$INSTANCE_NAME`_WriteInitPairs(const CyUAB_reg_pair pairs[], size_t n);

/*!
* \addtogroup group_interrupts
* @{
*/ 
void `$INSTANCE_NAME`_ClearInterrupt(CyUAB_intr_enum intr);
void `$INSTANCE_NAME`_SetInterrupt(CyUAB_intr_enum intr);
void `$INSTANCE_NAME`_SetInterruptMask(CyUAB_intr_enum intr);
void `$INSTANCE_NAME`_ClearInterruptMask(CyUAB_intr_enum intr);
uint32 `$INSTANCE_NAME`_GetInterruptIsMasked(CyUAB_intr_enum intr);
/*! @} interrupts */

/*!
* \addtogroup group_power
* @{
*/
void `$INSTANCE_NAME`_SetUABPower(CyUAB_coarse_pwr_enum powerLevel);
void `$INSTANCE_NAME`_SetOAPower(CyUAB_fine_pwr_enum powerLevel);
void `$INSTANCE_NAME`_SetCompPower(CyUAB_fine_pwr_enum powerLevel);
void `$INSTANCE_NAME`_SetRefPower(CyUAB_fine_pwr_enum powerLevel);
void `$INSTANCE_NAME`_SetAgndPower(CyUAB_fine_pwr_enum powerLevel);
/** @} power */

/*!
* \addtogroup group_ref
* @{
*/
void `$INSTANCE_NAME`_SetRefVdda(CyUAB_ref_force_vdda_enum forceVdda);
void `$INSTANCE_NAME`_SetAgndVdda(CyUAB_agnd_force_vdda_enum forceVdda);

void `$INSTANCE_NAME`_SetRefTied( CyUAB_ref_tied_enum refTied);
void `$INSTANCE_NAME`_SetAgndTied(CyUAB_agnd_tied_enum agndTied);
/*! @} vref */

/*!
* \addtogroup group_caps
* @{
*/
void `$INSTANCE_NAME`_SetCapA(CyUAB_cap_enum   capA);
void `$INSTANCE_NAME`_SetCapB(CyUAB_b_cap_enum capB);
void `$INSTANCE_NAME`_SetCapC(CyUAB_cap_enum   capC);
void `$INSTANCE_NAME`_SetCapF(CyUAB_f_cap_enum capF);
void `$INSTANCE_NAME`_SetCaps(CyUAB_cap_enum capA, CyUAB_b_cap_enum capB, 
    CyUAB_cap_enum capC, CyUAB_f_cap_enum capF);
void `$INSTANCE_NAME`_SetGroundUnused(CyUAB_gnd_unused_enum gndUnusedB, CyUAB_gnd_unused_enum gndUnusedC );


/*! @} caps */

/*!
* \addtogroup group_dac
* @{
*/
void `$INSTANCE_NAME`_SetDacModeEn(CyUAB_dac_mode_en_enum isEnabled);
void `$INSTANCE_NAME`_SetDacMode(CyUAB_dac_mode_enum dacMode);

void `$INSTANCE_NAME`_SetDacNext(int16 nextDACVal);
/** @} dac */

/*!
* \addtogroup group_pga
* @{
*/
void `$INSTANCE_NAME`_SetCapCFNext(CyUAB_cap_enum nextCapC,
    CyUAB_f_cap_enum nextCapF);
/*! Maps gain ratio to appropriate capacitance function parameters */
#define `$INSTANCE_NAME`_SetPGAGain(NUMERATOR,DENOMINATOR) \
  (CyUAB_SetCapCFNext((NUMERATOR),(DENOMINATOR)))
/** @} pga */

/*!
* \addtogroup group_comparator
* @{
*/
void `$INSTANCE_NAME`_SetCompEdgeDetect(CyUAB_cmp_edge_enum detectMode);
void `$INSTANCE_NAME`_SetCompOutLevel(CyUAB_cmp_level_enum isLevel);
uint32 `$INSTANCE_NAME`_GetCompStatus(void);
/*! @} comparator */


/*!
* \addtogroup group_switches
* @{
*/
void `$INSTANCE_NAME`_SetStaticSwitch( CyUAB_sw_id_enum sw_id, CyUAB_clk_enum clk);
void `$INSTANCE_NAME`_SetSwitch(CyUAB_sw_id_enum sw_id, CyUAB_clk_enum clk);

/*! Select B branch attenuation bypass switch waveform */
#define `$INSTANCE_NAME`_SetAttenBypassSwitchB(clk) `$INSTANCE_NAME`_SetSwitch(CyUAB_SW_TB,(clk))
/*! Select C branch attenuation bypass switch waveform */
#define `$INSTANCE_NAME`_SetAttenBypassSwitchC(clk) `$INSTANCE_NAME`_SetSwitch(CyUAB_SW_TC,(clk))

/*! Select Comparator flip-flop clock */
#define `$INSTANCE_NAME`_SetCompoutFFClock(clk) `$INSTANCE_NAME`_SetSwitch(CyUAB_SW_CMP_FF,(clk))
/*! Select VALID waveform */
#define `$INSTANCE_NAME`_SetValidClock(clk)     `$INSTANCE_NAME`_SetSwitch(CyUAB_SW_VALID, (clk))
/*! Select Output trigger waveform */
#define `$INSTANCE_NAME`_SetTrigClock(clk)      `$INSTANCE_NAME`_SetSwitch(CyUAB_SW_TRIG_OUT,  (clk))

/*! Strobe anytime */
#define `$INSTANCE_NAME`_STROBE_UPDATE_ANYTIME `$INSTANCE_NAME`_DYNAMIC_SWITCH_CLOSED
/*! Select strobe waveform */
#define `$INSTANCE_NAME`_SetStrobeClock(clk)    `$INSTANCE_NAME`_SetSwitch(CyUAB_SW_STROBE_RST,(clk))

void `$INSTANCE_NAME`_SetEarly(CyUAB_sw_id_enum sw_id, CyUAB_clk_adj_enum isEarly);

/*! @} switches */

/*!
* \addtogroup group_clocking
* @{
*/

void `$INSTANCE_NAME`_Run(uint32 flag);
/*! Enable clocking of already configured UAB half */
#define `$INSTANCE_NAME`_EnableClocks()  `$INSTANCE_NAME`_Run(1UL)
/*! Disable clocking of UAB half */
#define `$INSTANCE_NAME`_DisableClocks() `$INSTANCE_NAME`_Run(0UL)

void `$INSTANCE_NAME`_SetLastStep(uint32 lastStep);

void `$INSTANCE_NAME`_SetStartupDelay(uint16 delayCount);
void `$INSTANCE_NAME`_SetAlignMode(CyUAB_align_mode_enum alignMode);
void `$INSTANCE_NAME`_SetSubsample(uint8 subsample);
void `$INSTANCE_NAME`_SetSubsampleInit(uint8 subsampleInit);

uint32 `$INSTANCE_NAME`_GetCurrentSubsample(void);
uint32 `$INSTANCE_NAME`_GetCurrentStep(void);

void `$INSTANCE_NAME`_SetModbitSource( uint32 modbitSrcAB, uint32 modbitSrcC );

void `$INSTANCE_NAME`_SetStrobeMode(CyUAB_strobe_mode_enum strobeMode);
void `$INSTANCE_NAME`_SetStrobeSource(uint32 strobeSource);

void `$INSTANCE_NAME`_SetFirmwareModbit(uint32 flag);

void `$INSTANCE_NAME`_SetInputTrigger(uint32 triggerEn, uint32 triggerSel );

/*! Clear all clock waveform memory */
#define `$INSTANCE_NAME`_ClearAllClocks() CyUAB_wordset(\
    (`$INSTANCE_NAME`_SRAM0_PTR), \
    0UL,\
    (CyUAB_STEPS_LEN_MAX*sizeof(uint32)) \
)

/*! Set all steps for a single clock phi; 
@param phi clock 1-12
@param pattern PHI1 to PHI12 waveform steps; uint16 where step0 is LSbit and step15 is MSbit; 
@param modbitPattern PHI9 to PHI12 modbit waveform steps; uint16 where step0 is LSbit and step15 is MSbit */
#define `$INSTANCE_NAME`_SetClock(phi,pattern,modbitPattern)  \
  CyUAB_SetClock(`$INSTANCE_NAME`_SRAM0_PTR,(phi),(pattern),(modbitPattern))

/*! Set multiple steps for all clocks 
@param len number of steps
@param stepArray array of steps */
#define `$INSTANCE_NAME`_SetNSteps(len,stepArray)  \
  CyUAB_SetNSteps(`$INSTANCE_NAME`_SRAM0_PTR,(len),(stepArray))

/*! Set single step for all clocks
@param idx index of step to write
@param stepVal value of step */
#define `$INSTANCE_NAME`_SetSingleStep(idx,stepVal)  \
  CyUAB_SetSingleStep(`$INSTANCE_NAME`_SRAM0_PTR,(idx),(stepVal))

/*! @} group_clocking */




#endif /* #if !defined(`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
