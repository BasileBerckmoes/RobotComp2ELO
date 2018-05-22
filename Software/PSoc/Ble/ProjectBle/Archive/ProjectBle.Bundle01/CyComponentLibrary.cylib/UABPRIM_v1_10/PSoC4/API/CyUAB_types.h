/*!*****************************************************************************
* \file `$INSTANCE_NAME`_CyUAB_types.h
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

#if !defined(CyUAB_TYPES_H)
#define CyUAB_TYPES_H

#include "cytypes.h"
#include "`$INSTANCE_NAME`_CyUAB_regs.h"
#include "`$INSTANCE_NAME`_regs.h"
    
/*!
* \addtogroup group_structures
* @{
*/

/*!*****************************************************************************
@brief function error status

@details 
*******************************************************************************/
typedef enum{
    CyUAB_OK = 0,    /**< 0 means success */
    CyUAB_ERROR = -1 /**< non-zero values are errors*/
} CyUAB_Result;


/*!*****************************************************************************
@brief UABPRIM address-data pairs structure
@details contains the address and value to write 
@see `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Start()
*******************************************************************************/
typedef struct{
    reg32* addr;   /**< address of register to write */
    uint32 value;  /**< write value */
} CyUAB_reg_pair;

/*!*****************************************************************************
@brief UABPRIM configuration structure
@details Points to waveform configuration, points to address-data pair configuration, contains shared switch configuration, waveform configuration size, and pair size 
@see `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Start()
*******************************************************************************/
typedef struct{
    uint16* waveSteps;     /**< assign address of array of waveform steps to write */
    CyUAB_reg_pair* pairs; /**< assign address of array of address-data pairs to write */
    uint16 shared_sw;      /**< packed shared switch configuration */
    uint8 stepCount;       /**< number of elements in the array pointed to by waveSteps */
    uint8 pairCount;       /**< number of elements in the array pointed to by pairs */
} CyUAB_config;

/*Shared Switch Configuration packed into a uint16*/
/*! SW_AA location within packed shared switch config */
#define CyUAB_SHARED_SW_CFG_AA_SHIFT (0UL)
/*! SW_BB location within packed shared switch config */
#define CyUAB_SHARED_SW_CFG_BB_SHIFT (4UL)
/*! SW_CC location within packed shared switch config */
#define CyUAB_SHARED_SW_CFG_CC_SHIFT (8UL)
/*! agnd_tied location within packed shared switch config */
#define CyUAB_SHARED_SW_CFG_AGNDTIED_SHIFT (12UL)
/*! ref_tied location within packed shared switch config */
#define CyUAB_SHARED_SW_CFG_REFTIED_SHIFT (13UL)

/*! SW_AA mask for packed shared switch config */
#define CyUAB_SHARED_SW_CFG_AA_MASK (0xfUL<<CyUAB_SHARED_SW_CFG_AA_SHIFT)
/*! SW_BB mask for packed shared switch config */
#define CyUAB_SHARED_SW_CFG_BB_MASK (0xfUL<<CyUAB_SHARED_SW_CFG_BB_SHIFT)
/*! SW_CC mask for packed shared switch config */
#define CyUAB_SHARED_SW_CFG_CC_MASK (0xfUL<<CyUAB_SHARED_SW_CFG_CC_SHIFT)
/*! agnd_tied mask for packed shared switch config */
#define CyUAB_SHARED_SW_CFG_AGNDTIED_MASK (1UL<<CyUAB_SHARED_SW_CFG_AGNDTIED_SHIFT)
/*! ref_tied mask for packed shared switch config */
#define CyUAB_SHARED_SW_CFG_REFTIED_MASK (1UL<<CyUAB_SHARED_SW_CFG_REFTIED_SHIFT)

/*! pack shared switch config */
#define CyUAB_SHARED_SW_CFG(reftied,agndtied,cc,bb,aa) ((uint16)(\
    ((reftied)<<CyUAB_SHARED_SW_CFG_REFTIED_SHIFT)|\
    ((agndtied)<<CyUAB_SHARED_SW_CFG_AGNDTIED_SHIFT)|\
    ((cc)<<CyUAB_SHARED_SW_CFG_CC_SHIFT)|\
    ((bb)<<CyUAB_SHARED_SW_CFG_BB_SHIFT)|\
    ((aa)<<CyUAB_SHARED_SW_CFG_AA_SHIFT)\
))

/*! unpack shared switch config */
/*! unpack SW_AA from shared switch config */
#define CyUAB_SHARED_SW_CFG_AA(shared_sw_cfg)       ((CyUAB_clk_enum)((int32)((uint16)\
    (((shared_sw_cfg)&CyUAB_SHARED_SW_CFG_AA_MASK)>>CyUAB_SHARED_SW_CFG_AA_SHIFT))))
/*! unpack SW_BB from shared switch config */
#define CyUAB_SHARED_SW_CFG_BB(shared_sw_cfg)       ((CyUAB_clk_enum)((int32)((uint16)\
    (((shared_sw_cfg)&CyUAB_SHARED_SW_CFG_BB_MASK)>>CyUAB_SHARED_SW_CFG_BB_SHIFT))))
/*! unpack SW_CC from shared switch config */
#define CyUAB_SHARED_SW_CFG_CC(shared_sw_cfg)       ((CyUAB_clk_enum)((int32)((uint16)\
    (((shared_sw_cfg)&CyUAB_SHARED_SW_CFG_CC_MASK)>>CyUAB_SHARED_SW_CFG_CC_SHIFT))))
/*! unpack agnd_tied from shared switch config */
#define CyUAB_SHARED_SW_CFG_AGNDTIED(shared_sw_cfg) ((CyUAB_agnd_tied_enum)((int32)((uint16)\
    (((shared_sw_cfg)&CyUAB_SHARED_SW_CFG_AGNDTIED_MASK)>>CyUAB_SHARED_SW_CFG_AGNDTIED_SHIFT))))
/*! unpack ref_tied from shared switch config */
#define CyUAB_SHARED_SW_CFG_REFTIED(shared_sw_cfg)  ((CyUAB_ref_tied_enum)((int32)((uint16)\
    (((shared_sw_cfg)&CyUAB_SHARED_SW_CFG_REFTIED_MASK)>>CyUAB_SHARED_SW_CFG_REFTIED_SHIFT))))



/*!*****************************************************************************
@brief Interrupt selection
@details The UAB has two interrupts.  1) Comparator 2) VDAC Empty
@see CyUAB_ClearInterrupt()
@see CyUAB_SetInterruptRQ()
@see CyUAB_SetInterruptMask()
@see CyUAB_GetInterruptIsMasked()
*******************************************************************************/
/*Values are arbitrarily chosen to not be in the range of 0...31*/
typedef enum{
    CyUAB_INTR_COMP       = 37, /**< Comparator */
    CyUAB_INTR_VDAC_EMPTY = 67  /**< VDAC Empty */
    /*intentionally omitting decimator interrupt - handled in decimator component*/
}CyUAB_intr_enum;

/*!*****************************************************************************
@brief Interrupt and Trigger Edge Detect modes
@details Comparator Edge Detect modes for interrupt and trigger
@see OAn_CTL
@see `$INSTANCE_NAME`_SetCompEdgeDetect()
*******************************************************************************/
typedef enum{
      
    CyUAB_CMP_EDGE_DISABLE = 0, /**< disable - comparator edges don't change interrupt or trigger out */
    CyUAB_CMP_EDGE_RISING  = 1, /**< rising edge */
    CyUAB_CMP_EDGE_FALLING = 2, /**< falling edge */
    CyUAB_CMP_EDGE_BOTH    = 3  /**< both rising and falling edges*/
} CyUAB_cmp_edge_enum;

/*!*****************************************************************************
@brief Trigger out modes
@details Comparator Trigger out level
@see `$INSTANCE_NAME`_SetCompOutLevel()
*******************************************************************************/
typedef enum{
    CyUAB_CMP_PULSE = 0, /**< Pulsed trigger out */
    CyUAB_CMP_LEVEL = 1   /**< Level trigger out */
} CyUAB_cmp_level_enum;

/*!*****************************************************************************
@brief Invert Comparator Output
@details Note when the comparator is off the comparator output is normally 
forced low. However by setting this bit the comparator output is forced high 
when it is off.
@see `$INSTANCE_NAME`_SetCompOutInvert()
*******************************************************************************/
typedef enum{
    CyUAB_CMP_NOINVERT = 0, /**< comparator not inverted */
    CyUAB_CMP_INVERT   = 1  /**< comparator inverted */
} CyUAB_cmp_invert_enum;

/*!*****************************************************************************
@brief Force buffered ref to VDDA
@details Replace reference buffer output with VDDA. (REFx_PTS)
@see `$INSTANCE_NAME`_SetRefVdda()
*******************************************************************************/
typedef enum{
    CyUAB_REF_NORMAL     = 0, /**< Use buffered ref */
    CyUAB_REF_FORCE_VDDA = 1  /**< Use VDDA */
} CyUAB_ref_force_vdda_enum;

/*!*****************************************************************************
@brief Force buffered agnd to VDDA
@details Replace reference buffer output with VDDA. (AGNDx_PTS)
@see `$INSTANCE_NAME`_SetAgndVdda()
*******************************************************************************/
typedef enum{
    CyUAB_AGND_NORMAL     = 0, /**< Use buffered agnd */
    CyUAB_AGND_FORCE_VDDA = 1  /**< Use VDDA */
} CyUAB_agnd_force_vdda_enum;

/*!*****************************************************************************
@brief Tie agnd buffers within UAB pair
@details Allows driving both UAB halves of a pair with same agnd buffer.
Purpose: power saving feature and 
for 2nd order (both halves used in same application) want the same references 
to be used.
OA0_CTRL contains SW_GG
@see `$INSTANCE_NAME`_SetAgndSharing()
*******************************************************************************/
typedef enum{
    CyUAB_AGND_SEPARATE = 0, /**< agnd not shared*/
    CyUAB_AGND_TIED     = 1  /**< agnd shared */
} CyUAB_agnd_tied_enum;

/*!*****************************************************************************
@brief Tie ref buffers within UAB pair
@details Allows driving both UAB halves of a pair with same ref buffer.
Purpose: power saving feature and 
for 2nd order (both halves used in same application) want the same references 
to be used.
OA1_CTRL contains SW_RR
@see `$INSTANCE_NAME`_SetRefSharing()
*******************************************************************************/
typedef enum{
    CyUAB_REF_SEPARATE = 0, /**< ref not shared*/
    CyUAB_REF_TIED     = 1  /**< ref shared */
} CyUAB_ref_tied_enum;


/*!*****************************************************************************
@brief Fine granularity power options for blocks within 1/2 UAB
@details 
@see `$INSTANCE_NAME`_SetOAPower()
@see `$INSTANCE_NAME`_SetCompPower()
@see `$INSTANCE_NAME`_SetRefPower()
@see `$INSTANCE_NAME`_SetAgndPower()
*******************************************************************************/
typedef enum{
    CyUAB_PWR_OFF  = 0, /**< off */
    CyUAB_PWR_1_8  = 1, /**< 1/8 */
    CyUAB_PWR_3_8  = 2, /**< 3/8 */
    CyUAB_PWR_HALF = 3, /**< 1/2 */
    /*CyUAB_PWR_4_8  = 4,*/ /*Redundant - don't include in Doxygen enum table*/
    CyUAB_PWR_5_8  = 5, /**< 5/8 */
    CyUAB_PWR_7_8  = 6, /**< 7/8 */
    CyUAB_PWR_HIGH = 7  /**< high */
} CyUAB_fine_pwr_enum;

/*!*****************************************************************************
@brief Coarse granularity power options for 1/2 UAB
@details 
@see `$INSTANCE_NAME`_SetUABPower()
*******************************************************************************/
typedef enum{
    CyUAB_PWR_NORMAL     = 0, /**< normal     */
    CyUAB_PWR_ULTRA_LOW  = 1, /**< 0.5*normal */
    CyUAB_PWR_ULTRA_HIGH = 2  /**< 1.5*normal */
    /*CyUAB_PWR_NORMAL_TOO = 3*/
} CyUAB_coarse_pwr_enum;

/*!*****************************************************************************
@brief Grounded B and C caps?
@details Enable grounding of unused caps in B and C
CAP_CTRL
@see `$INSTANCE_NAME`_SetGroundUnused()
*******************************************************************************/
typedef enum{
    CyUAB_CAP_FLOAT  = 0, /**< unused capacitor's bottom plate float    */
    CyUAB_CAP_GROUND = 1  /**< unused capacitor's bottom plate grounded */
} CyUAB_gnd_unused_enum;

/*!*****************************************************************************
@brief Enable DAC mode
@details 
@see `$INSTANCE_NAME`_SetDacModeEn()
*******************************************************************************/
typedef enum{
    /** DAC off - @c SIGN_VAL is under firmware control */ 
      CyUAB_DAC_MODE_EN_OFF = 0,
    /** DAC on - @c SIGN_VAL is assumed to be part of the sign of a DAC number */  
      CyUAB_DAC_MODE_EN_ON  = 1
} CyUAB_dac_mode_en_enum;

/*!*****************************************************************************
@brief Select DAC resolution and sign
@details 
@see SIGNx_VAL  
@see `$INSTANCE_NAME`_SetDacMode()
*******************************************************************************/
typedef enum{
    
    /** Off or Unsigned 12-bit VDAC, i.e. no AB Cap value decoding.
    SIGN1_VAL can be used as Firmware controlled modbit (e.g. to invert the 
    Voltage for a Sign + Magnitude VDAC) */
    CyUAB_DAC_MODE_UNSIGNED12    = 0, 
    
    /** 'Virtual signed 12-bits' VDAC. AB Cap value decoding: 
    add 0x800 to the 12-bit AB Cap Value (=invert MSB), to convert the lowest 
    signed number 0x800 to the lowest unsigned number 0x000. This is the same 
    as the SAR handles 12-bit 'virtual' signed numbers. */
    CyUAB_DAC_MODE_VIRT_SIGNED12 = 1,
    
    /** Signed 13-bit twos complement. AB Cap value decoding: 
    for negative values (SIGN0_VAL=1) the AB Cap values are inverted, 
    the 64th B cap unit is enabled and the Voltage should be inverted.
    - Voltage inversion only works if the right clocking waveforms, switch 
    settings and reference voltages are used.
    - Enabling the 64th B cap unit adds 1 so that only a AB Cap value inversion 
    is needed to create a true twos complement.  */
    CyUAB_DAC_MODE_SIGNED13      = 2
    
} CyUAB_dac_mode_enum;  

/*! @brief ALIGN_MODE */
typedef enum{
    /* STARTUP_DELAY is number of clk_hf clocks to delay 
    the UAB clock after a SAR Trigger for UAB-SAR alignment in scheduled mode */
        CyUAB_ALIGN_MODE_SCHEDULED = 0,
    /* STARTUP_DELAY is number of clk_hf clocks to delay 
    UAB trigger to SAR for UAB-SAR alignment in unscheduled mode */
        CyUAB_ALIGN_MODE_UNSCHEDULED = 1
} CyUAB_align_mode_enum;


/*!*****************************************************************************
@brief Early clock timing for 
@details Early clock timing.  
Applies to PS (OUT<->SUM) and PO (VOUT->OUT) switches only.
@see `$INSTANCE_NAME`_SetEarly()
*******************************************************************************/
typedef enum{
    CyUAB_CLK_ADJ_NOEARLY = 0, /**< not early */ 
    CyUAB_CLK_ADJ_EARLY   = 1  /**< early */
}CyUAB_clk_adj_enum;


/*! @brief Strobe Mode */
typedef enum{
    CyUAB_STROBE_MODE_STROBE = 0, /**< Strobe (DAC use-case)*/
    CyUAB_STROBE_MODE_RESET  = 1  /**< Analog-reset to discharge all Caps 
      (Delsig Modulator use-case) */
} CyUAB_strobe_mode_enum;


/*!*****************************************************************************
@brief Selections for controlling dynamic switches and static switches

@details CyUAB_SW_OPEN and CyUAB_SW_CLOSED are generally used for 
static switches only.  
PHI1 to PHI8 do not have an accompanying modbit.
PHI9 to PHI12 have an accompanying modbit and should be used with switches that
require a modbit.

@see CyUAB_SetSwitch()
@see `$INSTANCE_NAME`_SetSwitch()
@see `$INSTANCE_NAME`_SetCompoutFFClock()
@see `$INSTANCE_NAME`_SetValidClock()
@see `$INSTANCE_NAME`_SetTrigClock()
@see `$INSTANCE_NAME`_SetStrobeClock()
*******************************************************************************/
typedef enum{
    CyUAB_SW_OPEN = 0,    /**< switch open (static) */ 
    
    CyUAB_CLK_PHI1 = 1,   /**< phi1 controls switch (no modbit) */ 
    CyUAB_CLK_PHI2 = 2,   /**< phi2 controls switch (no modbit) */
    CyUAB_CLK_PHI3 = 3,   /**< phi3 controls switch (no modbit) */
    CyUAB_CLK_PHI4 = 4,   /**< phi4 controls switch (no modbit) */
    CyUAB_CLK_PHI5 = 5,   /**< phi5 controls switch (no modbit) */
    CyUAB_CLK_PHI6 = 6,   /**< phi6 controls switch (no modbit) */
    CyUAB_CLK_PHI7 = 7,   /**< phi7 controls switch (no modbit) */
    CyUAB_CLK_PHI8 = 8,   /**< phi8 controls switch (no modbit) */
    
    CyUAB_CLK_PHI9 = 9,   /**< phi9 controls switch (has modbit) */
    CyUAB_CLK_PHI10 = 10, /**< phi10 controls switch (has modbit) */
    CyUAB_CLK_PHI11 = 11, /**< phi11 controls switch (has modbit) */
    CyUAB_CLK_PHI12 = 12, /**< phi12 controls switch (has modbit) */

    /*reserved*/
    /*`$INSTANCE_NAME`_CLK_RESERVED1 = 13,*/
    /*`$INSTANCE_NAME`_CLK_RESERVED2 = 14,*/
    
    CyUAB_SW_CLOSED = 15  /**< switch closed (static) */ 
}CyUAB_clk_enum;

/*! @} structures */

#define CyUAB_SwIsClosed(isClosed) ( ( ((uint32)(isClosed))!=((uint32)(CyUAB_SW_OPEN)) ) ? 1UL : 0UL)

/*Switch ID definitions*/
#define CyUAB_SW_NOX 0UL
#define CyUAB_SW_X   1UL


#define CyUAB_SW_ADDR_SHIFT  0UL
#define CyUAB_SW_ADDR_MASK   (0xffUL<<CyUAB_SW_ADDR_SHIFT)

#define CyUAB_SW_SHIFT_SHIFT 16UL
#define CyUAB_SW_SHIFT_MASK  (0x1fUL<<CyUAB_SW_SHIFT_SHIFT)

#define CyUAB_SW_X_SHIFT     23UL
#define CyUAB_SW_X_MASK      (1UL<<CyUAB_SW_X_SHIFT)

/*NOTE: Use (sw_id)&~CyUAB_SW_X_MASK to remove x->vin abstraction.
For manually configuring analog routing.
e.g. close switch from node A to vin0 (remove x0->vin# abstraction):
SetSwitch(CyUAB_SW_AX0_MODBIT&~CyUAB_SW_X_MASK,CyUAB_SW_CLOSED);*/


/*pack*/
#define CyUAB_SetSwAddr(addr)    ( ( ((uint32)(addr))  << CyUAB_SW_ADDR_SHIFT )  & CyUAB_SW_ADDR_MASK)
#define CyUAB_SetSwX(x)          ( ( ((uint32)(x))     << CyUAB_SW_X_SHIFT )     & CyUAB_SW_X_MASK)
#define CyUAB_SetSwShift(shift)  ( ( ((uint32)(shift)) << CyUAB_SW_SHIFT_SHIFT ) & CyUAB_SW_SHIFT_MASK)

#define CyUAB_SW_ID(addr,shift,x)  ((int32)( \
	CyUAB_SetSwX((x)) | CyUAB_SetSwShift((shift)) | CyUAB_SetSwAddr((addr)) \
))


/*unpack*/
#define CyUAB_GetSwAddr(sw_id)   ((uint32) ( ( ((uint32)(sw_id)) & CyUAB_SW_ADDR_MASK ) >> CyUAB_SW_ADDR_SHIFT ) )
#define CyUAB_IsSwX(sw_id)       (0UL != ( ( ((uint32)(sw_id)) & CyUAB_SW_X_MASK ) >> CyUAB_SW_X_SHIFT ) )
#define CyUAB_GetSwShift(sw_id)  ((uint32) ( ( ((uint32)(sw_id)) & CyUAB_SW_SHIFT_MASK ) >> CyUAB_SW_SHIFT_SHIFT ) )

/*!
* \addtogroup group_structures
* @{
*/

/*!*****************************************************************************
@brief Identifiers for most static and dynamic switches in a 1/2 UAB

@details Anything (switches or otherwise) that can select one of the 12 UAB
clocks or can be statically set open or closed is listed here.  The exception is the two agnd
and ref buffer sharing switches - they are not listed and are set through a
different interface.

Values have significance and are encoded with the group (e.g. A group), 
the subgroup (a particular register identifier/offset), and the field offset.
The encoding chosen allows the lookup code to be smaller and faster.

Refer to `$INSTANCE_NAME`.h for x input to vin input shuffling implementation details

@see CyUAB_SwitchRegLookup()
@see CyUAB_SetSwitch()
@see `$INSTANCE_NAME`_SetSwitch()
@see `$INSTANCE_NAME`_SetCompoutFFClock()
@see `$INSTANCE_NAME`_SetValidClock()
@see `$INSTANCE_NAME`_SetTrigClock()
@see `$INSTANCE_NAME`_SetStrobeClock()

@image html halfswitches.png

*******************************************************************************/
typedef enum{
    
    /* Static Switches */    
    CyUAB_SW_GX0 = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_G0_SHIFT, CyUAB_SW_X),    /**< static: OA+ <-> X0 */
    CyUAB_SW_GX1 = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_G1_SHIFT, CyUAB_SW_X),    /**< static: OA+ <-> X1 */  
    CyUAB_SW_GX2 = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_G2_SHIFT, CyUAB_SW_X),    /**< static: OA+ <-> X2 */  
    CyUAB_SW_GX3 = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_G3_SHIFT, CyUAB_SW_X),    /**< static: OA+ <-> X3 */  
    CyUAB_SW_RG  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_RG_SHIFT, CyUAB_SW_NOX),  /**< static: OA+ <-> REF */   
    CyUAB_SW_GG  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_GG_SHIFT, CyUAB_SW_NOX),  /**< static: OA+ <-> AGND */   
    CyUAB_SW_RT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_RT_SHIFT, CyUAB_SW_NOX),  /**< static: CMP+ <-> REF */  
    CyUAB_SW_GT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_GT_SHIFT, CyUAB_SW_NOX),  /**< static: CMP+ <-> AGND */ 
    CyUAB_SW_QT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_STATIC_ADDR,`$INSTANCE_NAME`_SW_QT_SHIFT, CyUAB_SW_NOX),  /**< static: CMP+ <-> OUT from other half */
    
    /* Dynamic Switches */
    /* reg SW_CAx_IN0 */
    CyUAB_SW_AX0_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN0_ADDR,`$INSTANCE_NAME`_SW_A0_MODBIT_SHIFT,  CyUAB_SW_X), /**< A in <-> X0 */
    CyUAB_SW_AX1_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN0_ADDR,`$INSTANCE_NAME`_SW_A1_MODBIT_SHIFT,  CyUAB_SW_X),   /**< A in <-> X1 */  
    CyUAB_SW_AX2_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN0_ADDR,`$INSTANCE_NAME`_SW_A2_MODBIT_SHIFT,  CyUAB_SW_X),   /**< A in <-> X2 */  
    CyUAB_SW_AX3_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN0_ADDR,`$INSTANCE_NAME`_SW_A3_MODBIT_SHIFT,  CyUAB_SW_X),   /**< A in <-> X3 */  
    CyUAB_SW_AP         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN0_ADDR,`$INSTANCE_NAME`_SW_AP_SHIFT,       CyUAB_SW_NOX), /**< A in <-> VOUT */  
    CyUAB_SW_AQ         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN0_ADDR,`$INSTANCE_NAME`_SW_AQ_SHIFT,       CyUAB_SW_NOX), /**< A in <-> VOUT from other half */
    /* reg SW_CAx_IN1 */
    CyUAB_SW_AA         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN1_ADDR,`$INSTANCE_NAME`_SW_AA_SHIFT,        CyUAB_SW_NOX), /**< short A inputs between each half - NOTE: exists only in half0 */ 
    CyUAB_SW_AR_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN1_ADDR,`$INSTANCE_NAME`_SW_AR_MODBIT_SHIFT, CyUAB_SW_NOX), /**< A in <-> REF */
    CyUAB_SW_AG_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN1_ADDR,`$INSTANCE_NAME`_SW_AG_MODBIT_SHIFT, CyUAB_SW_NOX), /**< A in <-> AGND */
    CyUAB_SW_AV_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_IN1_ADDR,`$INSTANCE_NAME`_SW_AV_MODBIT_SHIFT, CyUAB_SW_NOX), /**< A in <-> VSS */
    /*reg SW_CAx_TOP */
    CyUAB_SW_RA_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_TOP_ADDR,`$INSTANCE_NAME`_SW_RA_MODBIT_SHIFT, CyUAB_SW_NOX), /**< A top <-> REF */
    CyUAB_SW_GA_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_TOP_ADDR,`$INSTANCE_NAME`_SW_GA_MODBIT_SHIFT, CyUAB_SW_NOX), /**< A top <-> AGND */
    CyUAB_SW_VA_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_TOP_ADDR,`$INSTANCE_NAME`_SW_VA_MODBIT_SHIFT, CyUAB_SW_NOX), /**< A top <-> VSS */
    /* OK: nothing at bits 15:12 */
    CyUAB_SW_SA         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CA_TOP_ADDR,`$INSTANCE_NAME`_SW_SA_SHIFT,        CyUAB_SW_NOX), /**< A top <-> SUM */
    /*reg SW_CBx_IN0 */
    CyUAB_SW_BX0_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN0_ADDR,`$INSTANCE_NAME`_SW_B0_MODBIT_SHIFT,  CyUAB_SW_X), /**< B in <-> X0 */
    CyUAB_SW_BX1_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN0_ADDR,`$INSTANCE_NAME`_SW_B1_MODBIT_SHIFT,  CyUAB_SW_X), /**< B in <-> X1 */
    CyUAB_SW_BX2_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN0_ADDR,`$INSTANCE_NAME`_SW_B2_MODBIT_SHIFT,  CyUAB_SW_X), /**< B in <-> X2 */
    CyUAB_SW_BX3_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN0_ADDR,`$INSTANCE_NAME`_SW_B3_MODBIT_SHIFT,  CyUAB_SW_X), /**< B in <-> X3 */
    CyUAB_SW_BP         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN0_ADDR,`$INSTANCE_NAME`_SW_BP_SHIFT,        CyUAB_SW_NOX), /**< B in <-> VOUT */
    CyUAB_SW_BQ         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN0_ADDR,`$INSTANCE_NAME`_SW_BQ_SHIFT,        CyUAB_SW_NOX), /**< B in <-> VOUT from other half */
    /* reg SW_CBx_IN1 */
    CyUAB_SW_BB         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN1_ADDR,`$INSTANCE_NAME`_SW_BB_SHIFT,        CyUAB_SW_NOX), /**< short B inputs between each half - NOTE: exists only in half0 */
    CyUAB_SW_BR_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN1_ADDR,`$INSTANCE_NAME`_SW_BR_MODBIT_SHIFT, CyUAB_SW_NOX), /**< B in <-> REF */
    CyUAB_SW_BG_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN1_ADDR,`$INSTANCE_NAME`_SW_BG_MODBIT_SHIFT, CyUAB_SW_NOX), /**< B in <-> AGND */
    CyUAB_SW_BV_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_IN1_ADDR,`$INSTANCE_NAME`_SW_BV_MODBIT_SHIFT, CyUAB_SW_NOX), /**< B in <-> VSS */   
    /* reg SW_CBx_TOP */
    CyUAB_SW_RB_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_TOP_ADDR,`$INSTANCE_NAME`_SW_RB_MODBIT_SHIFT, CyUAB_SW_NOX), /**< B top <-> REF */   
    CyUAB_SW_GB_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_TOP_ADDR,`$INSTANCE_NAME`_SW_GB_MODBIT_SHIFT, CyUAB_SW_NOX), /**< B top <-> AGND */ 
    CyUAB_SW_VB_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_TOP_ADDR,`$INSTANCE_NAME`_SW_VB_MODBIT_SHIFT, CyUAB_SW_NOX), /**< B top <-> VSS */  
    CyUAB_SW_TB         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_TOP_ADDR,`$INSTANCE_NAME`_SW_TB_SHIFT,        CyUAB_SW_NOX), /**< B top <-> trim/attenuator bypass */
    CyUAB_SW_SB         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CB_TOP_ADDR,`$INSTANCE_NAME`_SW_SB_SHIFT,        CyUAB_SW_NOX), /**< B top <-> SUM */  
    /* reg SW_CCx_IN0 */
    CyUAB_SW_CX0_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN0_ADDR,`$INSTANCE_NAME`_SW_C0_MODBIT_SHIFT,  CyUAB_SW_X), /**< C in <-> X0 */  
    CyUAB_SW_CX1_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN0_ADDR,`$INSTANCE_NAME`_SW_C1_MODBIT_SHIFT,  CyUAB_SW_X), /**< C in <-> X1 */  
    CyUAB_SW_CX2_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN0_ADDR,`$INSTANCE_NAME`_SW_C2_MODBIT_SHIFT,  CyUAB_SW_X), /**< C in <-> X2 */  
    CyUAB_SW_CX3_MODBIT = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN0_ADDR,`$INSTANCE_NAME`_SW_C3_MODBIT_SHIFT,  CyUAB_SW_X), /**< C in <-> X3 */  
    CyUAB_SW_CP         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN0_ADDR,`$INSTANCE_NAME`_SW_CP_SHIFT,        CyUAB_SW_NOX), /**< C in <-> SUM */   
    CyUAB_SW_CQ         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN0_ADDR,`$INSTANCE_NAME`_SW_CQ_SHIFT,        CyUAB_SW_NOX), /**< C in <-> SUM from other half */
    /* reg SW_CCx_IN1 */
    CyUAB_SW_CC         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN1_ADDR,`$INSTANCE_NAME`_SW_CC_SHIFT,        CyUAB_SW_NOX), /**< short C inputs between each half */         
    CyUAB_SW_CR_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN1_ADDR,`$INSTANCE_NAME`_SW_CR_MODBIT_SHIFT, CyUAB_SW_NOX), /**< C in <-> REF */   
    CyUAB_SW_CG_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN1_ADDR,`$INSTANCE_NAME`_SW_CG_MODBIT_SHIFT, CyUAB_SW_NOX), /**< C in <-> AGND */  
    CyUAB_SW_CV_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_IN1_ADDR,`$INSTANCE_NAME`_SW_CV_MODBIT_SHIFT, CyUAB_SW_NOX), /**< C in <-> VSS */   
    /* reg SW_CCx_TOP */
    CyUAB_SW_RC_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_TOP_ADDR,`$INSTANCE_NAME`_SW_RC_MODBIT_SHIFT, CyUAB_SW_NOX), /**< C top <-> REF */  
    CyUAB_SW_GC_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_TOP_ADDR,`$INSTANCE_NAME`_SW_GC_MODBIT_SHIFT, CyUAB_SW_NOX), /**< C top <-> AGND */ 
    CyUAB_SW_VC_MODBIT  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_TOP_ADDR,`$INSTANCE_NAME`_SW_VC_MODBIT_SHIFT, CyUAB_SW_NOX), /**< C top <-> VSS */  
    CyUAB_SW_TC         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_TOP_ADDR,`$INSTANCE_NAME`_SW_TC_SHIFT,        CyUAB_SW_NOX), /**< C top <-> trim/attenuator bypass */ 
    CyUAB_SW_SC         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_TOP_ADDR,`$INSTANCE_NAME`_SW_SC_SHIFT,        CyUAB_SW_NOX), /**< C top <-> sum */  
    CyUAB_SW_ZC         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CC_TOP_ADDR,`$INSTANCE_NAME`_SW_ZC_SHIFT,        CyUAB_SW_NOX), /**< C top <-> sum from other half */ 
    /* reg SW_CFx_BOT  */ 
    CyUAB_SW_GF         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CF_BOT_ADDR,`$INSTANCE_NAME`_SW_GF_SHIFT, CyUAB_SW_NOX), /**< F bot <-> AGND */ 
    CyUAB_SW_PF         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CF_BOT_ADDR,`$INSTANCE_NAME`_SW_PF_SHIFT, CyUAB_SW_NOX), /**< F bot <-> VOUT */ 
    CyUAB_SW_PS         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CF_BOT_ADDR,`$INSTANCE_NAME`_SW_PS_SHIFT, CyUAB_SW_NOX), /**< F bypass, OUT <-> SUM */ 
    CyUAB_SW_PO         = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_CF_BOT_ADDR,`$INSTANCE_NAME`_SW_PO_SHIFT, CyUAB_SW_NOX), /**< OUT <-> VOUT */   
    
    /* reg SW_OTHERx */
    CyUAB_SW_CMP_FF     = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_OTHER_ADDR,`$INSTANCE_NAME`_CMP_FF_SHIFT,     CyUAB_SW_NOX), /**< Clock for FF after Comparator */
    CyUAB_SW_VALID      = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_OTHER_ADDR,`$INSTANCE_NAME`_VALID_SHIFT,      CyUAB_SW_NOX), /**< Valid output flag */
    CyUAB_SW_TRIG_OUT   = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_OTHER_ADDR,`$INSTANCE_NAME`_TRIG_OUT_SHIFT,   CyUAB_SW_NOX), /**< Trigger output */
    CyUAB_SW_STROBE_SW  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_OTHER_ADDR,`$INSTANCE_NAME`_STROBE_SW_SHIFT,  CyUAB_SW_NOX), /**< Strobe sync waveform selection */
    CyUAB_SW_STROBE_RST = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_OTHER_ADDR,`$INSTANCE_NAME`_STROBE_RST_SHIFT, CyUAB_SW_NOX), /**< Reset waveform selection */
    
    /* SW_BOOST_CTRL */
    CyUAB_SW_A_BOOST    = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR,`$INSTANCE_NAME`_CA_BOOST_SHIFT,  CyUAB_SW_NOX), /**< Boost A */        
    CyUAB_SW_B_BOOST    = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR,`$INSTANCE_NAME`_CB_BOOST_SHIFT,  CyUAB_SW_NOX), /**< Boost B */        
    CyUAB_SW_C_BOOST    = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR,`$INSTANCE_NAME`_CC_BOOST_SHIFT,  CyUAB_SW_NOX), /**< Boost C */        
    CyUAB_SW_F_BOOST    = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR,`$INSTANCE_NAME`_CF_BOOST_SHIFT,  CyUAB_SW_NOX), /**< Boost F */        
    CyUAB_SW_SUM_BOOST  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR,`$INSTANCE_NAME`_SUM_BOOST_SHIFT, CyUAB_SW_NOX), /**< SUM */            
    CyUAB_SW_PUMP_WAVE  = CyUAB_SW_ID(`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR,`$INSTANCE_NAME`_PUMP_WAVE_SHIFT, CyUAB_SW_NOX)  /**< Pump */           
    
} CyUAB_sw_id_enum;

    

    
/*!*****************************************************************************
@brief A and C branch cap values

@details The values repeat, once listed with the capacitance value, and again
in terms of UNIT capacitance.

@see `$INSTANCE_NAME`_SetCapA()
@see `$INSTANCE_NAME`_SetCapC()
*******************************************************************************/
typedef enum{
    CyUAB_CAP_OPEN   = 0, 
    CyUAB_CAP_0050fF = 1, 
    CyUAB_CAP_0100fF = 2, 
    CyUAB_CAP_0150fF = 3,
    CyUAB_CAP_0200fF = 4, 
    CyUAB_CAP_0250fF = 5, 
    CyUAB_CAP_0300fF = 6, 
    CyUAB_CAP_0350fF = 7,
    CyUAB_CAP_0400fF = 8, 
    CyUAB_CAP_0450fF = 9, 
    CyUAB_CAP_0500fF = 10, 
    CyUAB_CAP_0550fF = 11,
    CyUAB_CAP_0600fF = 12, 
    CyUAB_CAP_0650fF = 13, 
    CyUAB_CAP_0700fF = 14, 
    CyUAB_CAP_0750fF = 15,
    CyUAB_CAP_0800fF = 16, 
    CyUAB_CAP_0850fF = 17, 
    CyUAB_CAP_0900fF = 18, 
    CyUAB_CAP_0950fF = 19,
    CyUAB_CAP_1000fF = 20, 
    CyUAB_CAP_1050fF = 21, 
    CyUAB_CAP_1100fF = 22, 
    CyUAB_CAP_1150fF = 23,
    CyUAB_CAP_1200fF = 24, 
    CyUAB_CAP_1250fF = 25, 
    CyUAB_CAP_1300fF = 26, 
    CyUAB_CAP_1350fF = 27,
    CyUAB_CAP_1400fF = 28, 
    CyUAB_CAP_1450fF = 29, 
    CyUAB_CAP_1500fF = 30, 
    CyUAB_CAP_1550fF = 31,
    CyUAB_CAP_1600fF = 32, 
    CyUAB_CAP_1650fF = 33, 
    CyUAB_CAP_1700fF = 34, 
    CyUAB_CAP_1750fF = 35,
    CyUAB_CAP_1800fF = 36, 
    CyUAB_CAP_1850fF = 37, 
    CyUAB_CAP_1900fF = 38, 
    CyUAB_CAP_1950fF = 39,
    CyUAB_CAP_2000fF = 40, 
    CyUAB_CAP_2050fF = 41, 
    CyUAB_CAP_2100fF = 42, 
    CyUAB_CAP_2150fF = 43,
    CyUAB_CAP_2200fF = 44, 
    CyUAB_CAP_2250fF = 45, 
    CyUAB_CAP_2300fF = 46, 
    CyUAB_CAP_2350fF = 47,
    CyUAB_CAP_2400fF = 48, 
    CyUAB_CAP_2450fF = 49, 
    CyUAB_CAP_2500fF = 50, 
    CyUAB_CAP_2550fF = 51,
    CyUAB_CAP_2600fF = 52, 
    CyUAB_CAP_2650fF = 53, 
    CyUAB_CAP_2700fF = 54, 
    CyUAB_CAP_2750fF = 55,
    CyUAB_CAP_2800fF = 56, 
    CyUAB_CAP_2850fF = 57, 
    CyUAB_CAP_2900fF = 58, 
    CyUAB_CAP_2950fF = 59,
    CyUAB_CAP_3000fF = 60, 
    CyUAB_CAP_3050fF = 61, 
    CyUAB_CAP_3100fF = 62, 
    CyUAB_CAP_3150fF = 63,
    
    CyUAB_CAP_01UNIT = 1, 
    CyUAB_CAP_02UNIT = 2, 
    CyUAB_CAP_03UNIT = 3, 
    CyUAB_CAP_04UNIT = 4,
    CyUAB_CAP_05UNIT = 5, 
    CyUAB_CAP_06UNIT = 6, 
    CyUAB_CAP_07UNIT = 7, 
    CyUAB_CAP_08UNIT = 8,
    CyUAB_CAP_09UNIT = 9, 
    CyUAB_CAP_10UNIT = 10, 
    CyUAB_CAP_11UNIT = 11, 
    CyUAB_CAP_12UNIT = 12,
    CyUAB_CAP_13UNIT = 13, 
    CyUAB_CAP_14UNIT = 14, 
    CyUAB_CAP_15UNIT = 15, 
    CyUAB_CAP_16UNIT = 16,
    CyUAB_CAP_17UNIT = 17, 
    CyUAB_CAP_18UNIT = 18, 
    CyUAB_CAP_19UNIT = 19, 
    CyUAB_CAP_20UNIT = 20,
    CyUAB_CAP_21UNIT = 21, 
    CyUAB_CAP_22UNIT = 22, 
    CyUAB_CAP_23UNIT = 23, 
    CyUAB_CAP_24UNIT = 24,
    CyUAB_CAP_25UNIT = 25, 
    CyUAB_CAP_26UNIT = 26, 
    CyUAB_CAP_27UNIT = 27, 
    CyUAB_CAP_28UNIT = 28,
    CyUAB_CAP_29UNIT = 29, 
    CyUAB_CAP_30UNIT = 30, 
    CyUAB_CAP_31UNIT = 31, 
    CyUAB_CAP_32UNIT = 32,
    CyUAB_CAP_33UNIT = 33, 
    CyUAB_CAP_34UNIT = 34, 
    CyUAB_CAP_35UNIT = 35, 
    CyUAB_CAP_36UNIT = 36,
	CyUAB_CAP_37UNIT = 37, 
    CyUAB_CAP_38UNIT = 38, 
    CyUAB_CAP_39UNIT = 39, 
    CyUAB_CAP_40UNIT = 40,
    CyUAB_CAP_41UNIT = 41, 
    CyUAB_CAP_42UNIT = 42, 
    CyUAB_CAP_43UNIT = 43, 
    CyUAB_CAP_44UNIT = 44,
    CyUAB_CAP_45UNIT = 45, 
    CyUAB_CAP_46UNIT = 46, 
    CyUAB_CAP_47UNIT = 47, 
    CyUAB_CAP_48UNIT = 48,
    CyUAB_CAP_49UNIT = 49, 
    CyUAB_CAP_50UNIT = 50, 
    CyUAB_CAP_51UNIT = 51, 
    CyUAB_CAP_52UNIT = 52,
    CyUAB_CAP_53UNIT = 53, 
    CyUAB_CAP_54UNIT = 54, 
    CyUAB_CAP_55UNIT = 55, 
    CyUAB_CAP_56UNIT = 56,
    CyUAB_CAP_57UNIT = 57, 
    CyUAB_CAP_58UNIT = 58, 
    CyUAB_CAP_59UNIT = 59, 
    CyUAB_CAP_60UNIT = 60,
    CyUAB_CAP_61UNIT = 61, 
    CyUAB_CAP_62UNIT = 62, 
    CyUAB_CAP_63UNIT = 63
}CyUAB_cap_enum;

/*!*****************************************************************************
@brief B branch cap values

@details The values repeat, once listed with the capacitance value, and again
in terms of UNIT capacitance.

@see `$INSTANCE_NAME`_SetCapB()
*******************************************************************************/
typedef enum{
    CyUAB_B_CAP_OPEN   = 0, 
    CyUAB_B_CAP_0050fF = 1, 
    CyUAB_B_CAP_0100fF = 2, 
    CyUAB_B_CAP_0150fF = 3,
    CyUAB_B_CAP_0200fF = 4, 
    CyUAB_B_CAP_0250fF = 5, 
    CyUAB_B_CAP_0300fF = 6, 
    CyUAB_B_CAP_0350fF = 7,
    CyUAB_B_CAP_0400fF = 8, 
    CyUAB_B_CAP_0450fF = 9, 
    CyUAB_B_CAP_0500fF = 10, 
    CyUAB_B_CAP_0550fF = 11,
    CyUAB_B_CAP_0600fF = 12, 
    CyUAB_B_CAP_0650fF = 13, 
    CyUAB_B_CAP_0700fF = 14, 
    CyUAB_B_CAP_0750fF = 15,
    CyUAB_B_CAP_0800fF = 16, 
    CyUAB_B_CAP_0850fF = 17, 
    CyUAB_B_CAP_0900fF = 18, 
    CyUAB_B_CAP_0950fF = 19,
    CyUAB_B_CAP_1000fF = 20, 
    CyUAB_B_CAP_1050fF = 21, 
    CyUAB_B_CAP_1100fF = 22, 
    CyUAB_B_CAP_1150fF = 23,
    CyUAB_B_CAP_1200fF = 24, 
    CyUAB_B_CAP_1250fF = 25, 
    CyUAB_B_CAP_1300fF = 26, 
    CyUAB_B_CAP_1350fF = 27,
    CyUAB_B_CAP_1400fF = 28, 
    CyUAB_B_CAP_1450fF = 29, 
    CyUAB_B_CAP_1500fF = 30, 
    CyUAB_B_CAP_1550fF = 31,
    CyUAB_B_CAP_1600fF = 32, 
    CyUAB_B_CAP_1650fF = 33, 
    CyUAB_B_CAP_1700fF = 34, 
    CyUAB_B_CAP_1750fF = 35,
    CyUAB_B_CAP_1800fF = 36, 
    CyUAB_B_CAP_1850fF = 37, 
    CyUAB_B_CAP_1900fF = 38, 
    CyUAB_B_CAP_1950fF = 39,
    CyUAB_B_CAP_2000fF = 40, 
    CyUAB_B_CAP_2050fF = 41, 
    CyUAB_B_CAP_2100fF = 42, 
    CyUAB_B_CAP_2150fF = 43,
    CyUAB_B_CAP_2200fF = 44, 
    CyUAB_B_CAP_2250fF = 45, 
    CyUAB_B_CAP_2300fF = 46, 
    CyUAB_B_CAP_2350fF = 47,
    CyUAB_B_CAP_2400fF = 48, 
    CyUAB_B_CAP_2450fF = 49, 
    CyUAB_B_CAP_2500fF = 50, 
    CyUAB_B_CAP_2550fF = 51,
    CyUAB_B_CAP_2600fF = 52, 
    CyUAB_B_CAP_2650fF = 53, 
    CyUAB_B_CAP_2700fF = 54, 
    CyUAB_B_CAP_2750fF = 55,
    CyUAB_B_CAP_2800fF = 56, 
    CyUAB_B_CAP_2850fF = 57, 
    CyUAB_B_CAP_2900fF = 58, 
    CyUAB_B_CAP_2950fF = 59,
    CyUAB_B_CAP_3000fF = 60, 
    CyUAB_B_CAP_3050fF = 61, 
    CyUAB_B_CAP_3100fF = 62, 
    CyUAB_B_CAP_3150fF = 63,
    CyUAB_B_CAP_3200fF = 64, 
    
    CyUAB_B_CAP_01UNIT = 1, 
    CyUAB_B_CAP_02UNIT = 2, 
    CyUAB_B_CAP_03UNIT = 3, 
    CyUAB_B_CAP_04UNIT = 4,
    CyUAB_B_CAP_05UNIT = 5, 
    CyUAB_B_CAP_06UNIT = 6, 
    CyUAB_B_CAP_07UNIT = 7, 
    CyUAB_B_CAP_08UNIT = 8,
    CyUAB_B_CAP_09UNIT = 9, 
    CyUAB_B_CAP_10UNIT = 10, 
    CyUAB_B_CAP_11UNIT = 11, 
    CyUAB_B_CAP_12UNIT = 12,
    CyUAB_B_CAP_13UNIT = 13, 
    CyUAB_B_CAP_14UNIT = 14, 
    CyUAB_B_CAP_15UNIT = 15, 
    CyUAB_B_CAP_16UNIT = 16,
    CyUAB_B_CAP_17UNIT = 17, 
    CyUAB_B_CAP_18UNIT = 18, 
    CyUAB_B_CAP_19UNIT = 19, 
    CyUAB_B_CAP_20UNIT = 20,
    CyUAB_B_CAP_21UNIT = 21, 
    CyUAB_B_CAP_22UNIT = 22, 
    CyUAB_B_CAP_23UNIT = 23, 
    CyUAB_B_CAP_24UNIT = 24,
    CyUAB_B_CAP_25UNIT = 25, 
    CyUAB_B_CAP_26UNIT = 26, 
    CyUAB_B_CAP_27UNIT = 27, 
    CyUAB_B_CAP_28UNIT = 28,
    CyUAB_B_CAP_29UNIT = 29, 
    CyUAB_B_CAP_30UNIT = 30, 
    CyUAB_B_CAP_31UNIT = 31, 
    CyUAB_B_CAP_32UNIT = 32,
    CyUAB_B_CAP_33UNIT = 33, 
    CyUAB_B_CAP_34UNIT = 34, 
    CyUAB_B_CAP_35UNIT = 35, 
    CyUAB_B_CAP_36UNIT = 36,
	CyUAB_B_CAP_37UNIT = 37, 
    CyUAB_B_CAP_38UNIT = 38, 
    CyUAB_B_CAP_39UNIT = 39, 
    CyUAB_B_CAP_40UNIT = 40,
    CyUAB_B_CAP_41UNIT = 41, 
    CyUAB_B_CAP_42UNIT = 42, 
    CyUAB_B_CAP_43UNIT = 43, 
    CyUAB_B_CAP_44UNIT = 44,
    CyUAB_B_CAP_45UNIT = 45, 
    CyUAB_B_CAP_46UNIT = 46, 
    CyUAB_B_CAP_47UNIT = 47, 
    CyUAB_B_CAP_48UNIT = 48,
    CyUAB_B_CAP_49UNIT = 49, 
    CyUAB_B_CAP_50UNIT = 50, 
    CyUAB_B_CAP_51UNIT = 51, 
    CyUAB_B_CAP_52UNIT = 52,
    CyUAB_B_CAP_53UNIT = 53, 
    CyUAB_B_CAP_54UNIT = 54, 
    CyUAB_B_CAP_55UNIT = 55, 
    CyUAB_B_CAP_56UNIT = 56,
    CyUAB_B_CAP_57UNIT = 57, 
    CyUAB_B_CAP_58UNIT = 58, 
    CyUAB_B_CAP_59UNIT = 59, 
    CyUAB_B_CAP_60UNIT = 60,
    CyUAB_B_CAP_61UNIT = 61, 
    CyUAB_B_CAP_62UNIT = 62, 
    CyUAB_B_CAP_63UNIT = 63, 
    CyUAB_B_CAP_64UNIT = 64
}CyUAB_b_cap_enum;

/*!*****************************************************************************
@brief F branch cap values

@details The values repeat, once listed with the capacitance value, and again
in terms of UNIT capacitance.

@see `$INSTANCE_NAME`_SetCapF()
*******************************************************************************/
typedef enum{
    CyUAB_F_CAP_0100fF = 0, 
    CyUAB_F_CAP_0200fF = 1, 
    CyUAB_F_CAP_0300fF = 2, 
    CyUAB_F_CAP_0400fF = 3, 
    CyUAB_F_CAP_0500fF = 4, 
    CyUAB_F_CAP_0600fF = 5, 
    CyUAB_F_CAP_0700fF = 6, 
    CyUAB_F_CAP_0800fF = 7, 
    CyUAB_F_CAP_0900fF = 8, 
    CyUAB_F_CAP_1000fF = 9, 
    CyUAB_F_CAP_1100fF = 10, 
    CyUAB_F_CAP_1200fF = 11, 
    CyUAB_F_CAP_1300fF = 12, 
    CyUAB_F_CAP_1400fF = 13, 
    CyUAB_F_CAP_1500fF = 14, 
    CyUAB_F_CAP_1600fF = 15, 
    CyUAB_F_CAP_1700fF = 16, 
    CyUAB_F_CAP_1800fF = 17, 
    CyUAB_F_CAP_1900fF = 18, 
    CyUAB_F_CAP_2000fF = 19, 
    CyUAB_F_CAP_2100fF = 20, 
    CyUAB_F_CAP_2200fF = 21, 
    CyUAB_F_CAP_2300fF = 22, 
    CyUAB_F_CAP_2400fF = 23, 
    CyUAB_F_CAP_2500fF = 24, 
    CyUAB_F_CAP_2600fF = 25, 
    CyUAB_F_CAP_2700fF = 26, 
    CyUAB_F_CAP_2800fF = 27, 
    CyUAB_F_CAP_2900fF = 28, 
    CyUAB_F_CAP_3000fF = 29, 
    CyUAB_F_CAP_3100fF = 30, 
    CyUAB_F_CAP_3200fF = 31, 
    
    CyUAB_F_CAP_02UNIT = 0, 
    CyUAB_F_CAP_04UNIT = 1,
    CyUAB_F_CAP_06UNIT = 2, 
    CyUAB_F_CAP_08UNIT = 3,
    CyUAB_F_CAP_10UNIT = 4, 
    CyUAB_F_CAP_12UNIT = 5,
    CyUAB_F_CAP_14UNIT = 6, 
    CyUAB_F_CAP_16UNIT = 7,
    CyUAB_F_CAP_18UNIT = 8, 
    CyUAB_F_CAP_20UNIT = 9,
    CyUAB_F_CAP_22UNIT = 10, 
    CyUAB_F_CAP_24UNIT = 11,
    CyUAB_F_CAP_26UNIT = 12, 
    CyUAB_F_CAP_28UNIT = 13,
    CyUAB_F_CAP_30UNIT = 14, 
    CyUAB_F_CAP_32UNIT = 15,
    CyUAB_F_CAP_34UNIT = 16, 
    CyUAB_F_CAP_36UNIT = 17,
    CyUAB_F_CAP_38UNIT = 18, 
    CyUAB_F_CAP_40UNIT = 19,
    CyUAB_F_CAP_42UNIT = 20, 
    CyUAB_F_CAP_44UNIT = 21,
    CyUAB_F_CAP_46UNIT = 22, 
    CyUAB_F_CAP_48UNIT = 23,
    CyUAB_F_CAP_50UNIT = 24, 
    CyUAB_F_CAP_52UNIT = 25,
    CyUAB_F_CAP_54UNIT = 26, 
    CyUAB_F_CAP_56UNIT = 27,
    CyUAB_F_CAP_58UNIT = 28, 
    CyUAB_F_CAP_60UNIT = 29,
    CyUAB_F_CAP_62UNIT = 30, 
    CyUAB_F_CAP_64UNIT = 31
}CyUAB_f_cap_enum;

/*! @} structures */


/*Macro to convert capacitance value (in fempto Farads) in steps of 50fF to enumerated value ;
for use with SetCapA(), SetCapB(), SetCapC(), and SetCaps()
A and C: 0 to 3150 (fF), cast to CyUAB_cap_enum   e.g. SetCapA( ((CyUAB_cap_enum)A_CAP_VALUE_fF(3150)) );
B:       0 to 3200 (fF), cast to CyUAB_b_cap_enum e.g. SetCapB( ((CyUAB_b_cap_enum)B_CAP_VALUE_fF(3200)) ); */
#define ABC_CAP_VALUE_fF(C) (((C)/50UL))
#define A_CAP_VALUE_fF(C) ABC_CAP_VALUE_fF((C))
#define B_CAP_VALUE_fF(C) ABC_CAP_VALUE_fF((C))
#define C_CAP_VALUE_fF(C) ABC_CAP_VALUE_fF((C))

/*Macro to convert capacitance value (in fempto Farads) in steps of 100fF to enumerated value
for use with SetCapF(), SetCapCFNext(), and SetCaps()
F:       100 to 3200 (fF), cast to CyUAB_f_cap_enum e.g. SetCapF( ((CyUAB_b_cap_enum)F_CAP_VALUE_fF(3200)) ); */
#define F_CAP_VALUE_fF(C)   (((C)/100UL)-1UL)



#endif /* #ifndef CyUAB_TYPES_H */

/* [] END OF FILE */
