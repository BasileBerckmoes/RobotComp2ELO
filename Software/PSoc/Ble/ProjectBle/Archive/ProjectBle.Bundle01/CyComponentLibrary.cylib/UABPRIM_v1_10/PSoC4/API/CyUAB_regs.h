/*!*****************************************************************************
* \file `$INSTANCE_NAME`_CyUAB_regs.h
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

#if !defined(CyUAB_REGS_H)
#define CyUAB_REGS_H

#include "cytypes.h"
    
#define CyUAB_GET_FIELD(addr, mask,shift)       ( ( (*((reg32*)(addr))) & (mask) ) >> (shift) )
#define CyUAB_SET_FIELD(addr, mask, val, shift) (   (*((reg32*)(addr))) = \
    ( ( (*((reg32*)(addr))) & (~(mask)) ) | ( ((val) << (shift)) & (mask)) ) )

/*Same as CyUAB_SET_FIELD(), but val is already shifted - optimization use for single write of multiple fields*/
#define CyUAB_SET_VARIOUS_FIELDS(addr, mask, val) ( (*((reg32*)(addr))) = \
    ( ( (*((reg32*)(addr))) & (~(mask)) ) | ((val) & (mask)) ) )
    
/*Register Field Shift Definitions*/

/*UAB_CTRL*/
#define CyUAB_ENABLED_SHIFT                31UL


/*INTR, INTR_SET, INTR_MASK, INTR_MASKED, */
#define CyUAB_INTR_COMP0_SHIFT             0UL
#define CyUAB_INTR_VDAC0_EMPTY_SHIFT       1UL

#define CyUAB_INTR_COMP1_SHIFT             16UL
#define CyUAB_INTR_VDAC1_EMPTY_SHIFT       17UL


/*OA_CTRL*/
#define CyUAB_OA_PWR_SHIFT                 0UL
#define CyUAB_CMP_PWR_SHIFT                8UL
#define CyUAB_CMP_EDGE_SHIFT               12UL
#define CyUAB_CMP_DSI_LEVEL_SHIFT          14UL
#define CyUAB_CTRL_SPARE_SHIFT             15UL
#define CyUAB_REF_PWR_SHIFT                16UL
#define CyUAB_REF_PTS_SHIFT                19UL
#define CyUAB_AGND_PWR_SHIFT               20UL
#define CyUAB_AGND_PTS_SHIFT               23UL
#define CyUAB_AGND_TIED_SHIFT              24UL
#define CyUAB_REF_TIED_SHIFT               24UL
#define CyUAB_UAB_PWR_SHIFT                30UL


/*CAP_CTRL*/
#define CyUAB_CB_GND_SHIFT                 5UL
#define CyUAB_CC_GND_SHIFT                 6UL
#define CyUAB_FRC_SIGN_BIT_SHIFT           28UL
#define CyUAB_DAC_MODE_EN_SHIFT            29UL
#define CyUAB_DAC_MODE_SHIFT               30UL


/*CAP_ABCF_VAL, CAP_AB_VAL_NXT, and CAP_CF_VAL_NXT*/
#define CyUAB_CB_VAL_SHIFT                 0UL
#define CyUAB_CA_VAL_SHIFT                 6UL
#define CyUAB_SIGN_VAL_SHIFT               12UL
#define CyUAB_CB_64_SHIFT                  13UL
#define CyUAB_CC_VAL_SHIFT                 16UL
#define CyUAB_CF_VAL_SHIFT                 24UL


/*CAP_CF_VAL_NXT*/
#define CyUAB_CC_VAL_UPDATE_SHIFT          30UL
#define CyUAB_CF_VAL_UPDATE_SHIFT          31UL


/*STARTUP_DELAY*/
#define CyUAB_STARTUP_DELAY_SHIFT          0UL
#define CyUAB_ALIGN_MODE_SHIFT             16UL


/*SUBSAMPLE_CTRL*/
#define CyUAB_SUBSAMPLE_SHIFT              0UL
#define CyUAB_SUBSAMPLE_INIT_SHIFT         8UL


/*SW_STATIC*/
#define CyUAB_SW_G0_SHIFT                  0UL
#define CyUAB_SW_G1_SHIFT                  1UL
#define CyUAB_SW_G2_SHIFT                  2UL
#define CyUAB_SW_G3_SHIFT                  3UL
#define CyUAB_SW_RG_SHIFT                  4UL
#define CyUAB_SW_GG_SHIFT                  5UL
#define CyUAB_SW_RT_SHIFT                  8UL
#define CyUAB_SW_GT_SHIFT                  9UL
#define CyUAB_SW_QT_SHIFT                  10UL
#define CyUAB_EARLY_PS_SHIFT               12UL
#define CyUAB_EARLY_PO_SHIFT               13UL
#define CyUAB_STRB_RST_SEL_SHIFT           24UL
#define CyUAB_STRB_RST_EN_SHIFT            29UL


/*SW_MODBIT_SRC*/
#define CyUAB_MODBIT0_SRC_SEL_SHIFT        0UL
#define CyUAB_MODBIT1_SRC_SEL_SHIFT        8UL


/*SW_CA_IN0*/
#define CyUAB_SW_A0_MODBIT_SHIFT           0UL
#define CyUAB_SW_A1_MODBIT_SHIFT           4UL
#define CyUAB_SW_A2_MODBIT_SHIFT           8UL
#define CyUAB_SW_A3_MODBIT_SHIFT           12UL
#define CyUAB_SW_AP_SHIFT                  16UL
#define CyUAB_SW_AQ_SHIFT                  20UL
/*SW_CA_IN1*/
#define CyUAB_SW_AA_SHIFT                  0UL
#define CyUAB_SW_AR_MODBIT_SHIFT           4UL
#define CyUAB_SW_AG_MODBIT_SHIFT           8UL
#define CyUAB_SW_AV_MODBIT_SHIFT           12UL
/*SW_CA_TOP*/
#define CyUAB_SW_RA_MODBIT_SHIFT           0UL
#define CyUAB_SW_GA_MODBIT_SHIFT           4UL
#define CyUAB_SW_VA_MODBIT_SHIFT           8UL
#define CyUAB_SW_SA_SHIFT                  16UL


/*SW_CB_IN0*/
#define CyUAB_SW_B0_MODBIT_SHIFT           0UL
#define CyUAB_SW_B1_MODBIT_SHIFT           4UL
#define CyUAB_SW_B2_MODBIT_SHIFT           8UL
#define CyUAB_SW_B3_MODBIT_SHIFT           12UL
#define CyUAB_SW_BP_SHIFT                  16UL
#define CyUAB_SW_BQ_SHIFT                  20UL
/*SW_CB_IN1*/
#define CyUAB_SW_BB_SHIFT                  0UL
#define CyUAB_SW_BR_MODBIT_SHIFT           4UL
#define CyUAB_SW_BG_MODBIT_SHIFT           8UL
#define CyUAB_SW_BV_MODBIT_SHIFT           12UL
/*SW_CB_TOP*/
#define CyUAB_SW_RB_MODBIT_SHIFT           0UL
#define CyUAB_SW_GB_MODBIT_SHIFT           4UL
#define CyUAB_SW_VB_MODBIT_SHIFT           8UL
#define CyUAB_SW_TB_SHIFT                  12UL
#define CyUAB_SW_SB_SHIFT                  16UL


/*SW_CC_IN0*/
#define CyUAB_SW_C0_MODBIT_SHIFT           0UL
#define CyUAB_SW_C1_MODBIT_SHIFT           4UL
#define CyUAB_SW_C2_MODBIT_SHIFT           8UL
#define CyUAB_SW_C3_MODBIT_SHIFT           12UL
#define CyUAB_SW_CP_SHIFT                  16UL
#define CyUAB_SW_CQ_SHIFT                  20UL
#define CyUAB_SW_CC_SHIFT                  0UL
/*SW_CC_IN1*/
#define CyUAB_SW_CR_MODBIT_SHIFT           4UL
#define CyUAB_SW_CG_MODBIT_SHIFT           8UL
#define CyUAB_SW_CV_MODBIT_SHIFT           12UL
/*SW_CC_TOP*/
#define CyUAB_SW_RC_MODBIT_SHIFT           0UL
#define CyUAB_SW_GC_MODBIT_SHIFT           4UL
#define CyUAB_SW_VC_MODBIT_SHIFT           8UL
#define CyUAB_SW_TC_SHIFT                  12UL
#define CyUAB_SW_SC_SHIFT                  16UL
#define CyUAB_SW_ZC_SHIFT                  20UL

    
/*SW_CF_BOT*/
#define CyUAB_SW_GF_SHIFT                  0UL
#define CyUAB_SW_PF_SHIFT                  4UL
#define CyUAB_SW_PS_SHIFT                  8UL
#define CyUAB_SW_PO_SHIFT                  12UL


/*SW_OTHER*/
#define CyUAB_CMP_FF_SHIFT                 0UL
#define CyUAB_VALID_SHIFT                  4UL
#define CyUAB_TRIG_OUT_SHIFT               8UL
#define CyUAB_STROBE_SW_SHIFT              24UL
#define CyUAB_STROBE_RST_SHIFT             28UL


/*SW_BOOST_CTRL*/
#define CyUAB_CA_BOOST_SHIFT               0UL
#define CyUAB_CB_BOOST_SHIFT               4UL
#define CyUAB_CC_BOOST_SHIFT               8UL
#define CyUAB_CF_BOOST_SHIFT               12UL
#define CyUAB_SUM_BOOST_SHIFT              16UL
#define CyUAB_PUMP_WAVE_SHIFT              20UL

    
/*SRAM_CTRL*/
#define CyUAB_LAST_STEP_SHIFT              0UL
#define CyUAB_TRIG_SEL_SHIFT               24UL
#define CyUAB_TRIGGER_EN_SHIFT             29UL
#define CyUAB_RUN_SHIFT                    31UL


/*STAT*/
#define CyUAB_CURR_STEP_SHIFT              0UL
#define CyUAB_COMP_SHIFT                   4UL
#define CyUAB_CURR_SUBSAMPLE_SHIFT         24UL


/*SRAM*/
#define CyUAB_WAVE_STEP_SHIFT              0UL


/*CAP_TRIM*/
#define CyUAB_CBTC_VAL_SHIFT               0UL
#define CyUAB_CCTC_VAL_SHIFT               4UL


/*OA_TRIM*/
#define CyUAB_OA_OFFSET_SHIFT              0UL
#define CyUAB_REF_OFFSET_SHIFT             8UL
#define CyUAB_AGND_OFFSET_SHIFT            16UL

#endif /* #ifndef CyUAB_REGS_H */

/* [] END OF FILE */
