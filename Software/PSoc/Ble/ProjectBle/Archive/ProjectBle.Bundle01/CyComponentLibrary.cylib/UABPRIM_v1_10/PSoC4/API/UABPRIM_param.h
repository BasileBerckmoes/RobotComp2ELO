/*!*****************************************************************************
* \file `$INSTANCE_NAME`_param.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief 
*   Definitions from Component Parameter
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

/* excluding defs in this file with cond and endcond */
/*! @cond */

#if !defined(`$INSTANCE_NAME`_PARAM_H)
#define `$INSTANCE_NAME`_PARAM_H

#include "`$INSTANCE_NAME`_CyUAB_types.h"
#include "`$INSTANCE_NAME`_regs.h"
#include "cytypes.h"
#include "cyfitter.h"

#define `$INSTANCE_NAME`_Nonzero(x) ( (x) != 0 )

#define `$INSTANCE_NAME`_UnmappedIsZero(x)  ((uint32)(((x)==-1)? 0 : (x)))

/*!
* \addtogroup group_init
* @{
*/
/*! Component Parameters set in the component customizer */
#define `$INSTANCE_NAME`_PARAM_COMP_MASK        `$COMP_MASK`
#define `$INSTANCE_NAME`_PARAM_VDAC_EMPTY_MASK  `$VDAC_EMPTY_MASK`

#define `$INSTANCE_NAME`_NONZERO_INTR_MASK (`$INSTANCE_NAME`_Nonzero( \
    ( `$COMP_MASK` |`$VDAC_EMPTY_MASK`) ))
#define `$INSTANCE_NAME`_DEFAULT_INTR_MASK ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_COMP_MASK)<<`$INSTANCE_NAME`_INTR_COMP_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_VDAC_EMPTY_MASK)<<`$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_UAB_PWR        `$UAB_PWR`
#define `$INSTANCE_NAME`_PARAM_AGND_PTS       `$AGND_PTS`
#define `$INSTANCE_NAME`_PARAM_AGND_PWR       `$AGND_PWR`
#define `$INSTANCE_NAME`_PARAM_REF_PTS        `$REF_PTS`
#define `$INSTANCE_NAME`_PARAM_REF_PWR        `$REF_PWR`
#define `$INSTANCE_NAME`_PARAM_CMP_DSI_LEVEL  `$CMP_DSI_LEVEL`
#define `$INSTANCE_NAME`_PARAM_CMP_EDGE       `$CMP_EDGE`
#define `$INSTANCE_NAME`_PARAM_CMP_PWR        `$CMP_PWR`
#define `$INSTANCE_NAME`_PARAM_OA_PWR         `$OA_PWR`

#define `$INSTANCE_NAME`_PARAM_AGND_TIED      `$AGND_TIED`
#define `$INSTANCE_NAME`_PARAM_REF_TIED       `$REF_TIED`


/*
#define `$INSTANCE_NAME`_NONZERO_OA_CTRL (`$INSTANCE_NAME`_Nonzero( \
    (`$UAB_PWR`|`$AGND_PTS`|`$AGND_PWR`|`$REF_PTS`|\
    `$REF_PWR`|`$CMP_INVERT`|`$CMP_DSI_LEVEL`|`$CMP_EDGE`|`$CMP_PWR`|`$OA_PWR`) ))
*/

/* force inclusion in `$Instance_Name`_initPairs */
#define `$INSTANCE_NAME`_NONZERO_OA_CTRL (`$INSTANCE_NAME`_Nonzero(1))

/*Shared switches agnd_tied and ref_tied occupy the same bit position, so ommitting from DEFAULT_OA_CTRL -
handled in Init() */
#define `$INSTANCE_NAME`_DEFAULT_OA_CTRL ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_UAB_PWR)<<`$INSTANCE_NAME`_UAB_PWR_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_AGND_PTS)<<`$INSTANCE_NAME`_AGND_PTS_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_AGND_PWR)<<`$INSTANCE_NAME`_AGND_PWR_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_REF_PTS)<<`$INSTANCE_NAME`_REF_PTS_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_REF_PWR)<<`$INSTANCE_NAME`_REF_PWR_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CMP_DSI_LEVEL)<<`$INSTANCE_NAME`_CMP_DSI_LEVEL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CMP_EDGE)<<`$INSTANCE_NAME`_CMP_EDGE_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CMP_PWR)<<`$INSTANCE_NAME`_CMP_PWR_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_OA_PWR)<<`$INSTANCE_NAME`_OA_PWR_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_CB_GND       `$CB_GND`
#define `$INSTANCE_NAME`_PARAM_CC_GND       `$CC_GND`
#define `$INSTANCE_NAME`_PARAM_FRC_SIGN_BIT `$FRC_SIGN_BIT`
#define `$INSTANCE_NAME`_PARAM_DAC_MODE_EN  `$DAC_MODE_EN`
#define `$INSTANCE_NAME`_PARAM_DAC_MODE     `$DAC_MODE`

#define `$INSTANCE_NAME`_NONZERO_CAP_CTRL ( `$INSTANCE_NAME`_Nonzero( \
    (`$CB_GND`|`$CC_GND`|`$DAC_MODE_EN`|`$DAC_MODE`|`$FRC_SIGN_BIT`) ))
#define `$INSTANCE_NAME`_DEFAULT_CAP_CTRL ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_CB_GND)<<`$INSTANCE_NAME`_CB_GND_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CC_GND)<<`$INSTANCE_NAME`_CC_GND_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_FRC_SIGN_BIT)<<`$INSTANCE_NAME`_FRC_SIGN_BIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_DAC_MODE_EN)<<`$INSTANCE_NAME`_DAC_MODE_EN_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_DAC_MODE)<<`$INSTANCE_NAME`_DAC_MODE_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_CB_VAL    `$CB_VAL`
#define `$INSTANCE_NAME`_PARAM_CA_VAL    `$CA_VAL`
#define `$INSTANCE_NAME`_PARAM_SIGN_VAL  `$SIGN_VAL`
#define `$INSTANCE_NAME`_PARAM_CB_64     `$CB_64`
#define `$INSTANCE_NAME`_PARAM_CC_VAL    `$CC_VAL`
#define `$INSTANCE_NAME`_PARAM_CF_VAL    `$CF_VAL`

#define `$INSTANCE_NAME`_NONZERO_CAP_ABCF_VAL  (`$INSTANCE_NAME`_Nonzero( \
    (`$CB_VAL`|`$CA_VAL`|`$SIGN_VAL`|`$CB_64`|`$CC_VAL`|`$CF_VAL`) ))
#define `$INSTANCE_NAME`_DEFAULT_CAP_ABCF_VAL  ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_CB_VAL)<<`$INSTANCE_NAME`_CB_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CA_VAL)<<`$INSTANCE_NAME`_CA_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SIGN_VAL)<<`$INSTANCE_NAME`_SIGN_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CB_64)<<`$INSTANCE_NAME`_CB_64_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CC_VAL)<<`$INSTANCE_NAME`_CC_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CF_VAL)<<`$INSTANCE_NAME`_CF_VAL_SHIFT) \
))

#define `$INSTANCE_NAME`_NONZERO_CAP_AB_VAL_NXT (`$INSTANCE_NAME`_Nonzero( \
    (`$CB_VAL`|`$CA_VAL`|`$SIGN_VAL`) ))
#define `$INSTANCE_NAME`_DEFAULT_CAP_AB_VAL_NXT  ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_CB_VAL)<<`$INSTANCE_NAME`_CB_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CA_VAL)<<`$INSTANCE_NAME`_CA_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SIGN_VAL)<<`$INSTANCE_NAME`_SIGN_VAL_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_CC_VAL_UPDATE  `$CC_VAL_UPDATE`
#define `$INSTANCE_NAME`_PARAM_CF_VAL_UPDATE  `$CF_VAL_UPDATE`

#define `$INSTANCE_NAME`_NONZERO_CAP_CF_VAL_NXT (`$INSTANCE_NAME`_Nonzero( \
    (`$CC_VAL_UPDATE`|`$CF_VAL_UPDATE`|`$CC_VAL`|`$CF_VAL`) ))
#define `$INSTANCE_NAME`_DEFAULT_CAP_CF_VAL_NXT ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_CC_VAL)<<`$INSTANCE_NAME`_CC_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CF_VAL)<<`$INSTANCE_NAME`_CF_VAL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CC_VAL_UPDATE)<<`$INSTANCE_NAME`_CC_VAL_UPDATE_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CF_VAL_UPDATE)<<`$INSTANCE_NAME`_CF_VAL_UPDATE_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_GX0        CyUAB_SwIsClosed( `$SW_GX0` )
#define `$INSTANCE_NAME`_PARAM_SW_GX1        CyUAB_SwIsClosed( `$SW_GX1` )
#define `$INSTANCE_NAME`_PARAM_SW_GX2        CyUAB_SwIsClosed( `$SW_GX2` )
#define `$INSTANCE_NAME`_PARAM_SW_GX3        CyUAB_SwIsClosed( `$SW_GX3` )
#define `$INSTANCE_NAME`_PARAM_SW_RG         CyUAB_SwIsClosed( `$SW_RG`  )
#define `$INSTANCE_NAME`_PARAM_SW_GG         CyUAB_SwIsClosed( `$SW_GG`  )
#define `$INSTANCE_NAME`_PARAM_SW_RT         CyUAB_SwIsClosed( `$SW_RT`  )
#define `$INSTANCE_NAME`_PARAM_SW_GT         CyUAB_SwIsClosed( `$SW_GT`  )
#define `$INSTANCE_NAME`_PARAM_SW_QT         CyUAB_SwIsClosed( `$SW_QT`  )
#define `$INSTANCE_NAME`_PARAM_EARLY_PS      `$EARLY_PS`
#define `$INSTANCE_NAME`_PARAM_EARLY_PO      `$EARLY_PO`

/*strobe source from cyfitter.h*/
#define `$INSTANCE_NAME`_PARAM_STRB_RST_SEL  (`$INSTANCE_NAME`_UnmappedIsZero(`$INSTANCE_NAME`_halfuab__STRB_RST_SEL))

#define `$INSTANCE_NAME`_PARAM_STRB_RST_EN   `$STRB_RST_EN`


/*if switch parameter references a bad x input, ignored in initialization*/
#define `$INSTANCE_NAME`_XIN_OK(xin) ( (0UL==((uint32)(xin))) || (1UL==((uint32)(xin))) || (2UL==((uint32)(xin))) || (3UL==((uint32)(xin))) )
#define `$INSTANCE_NAME`_IGNORE_VAL 0UL      
#define `$INSTANCE_NAME`_XField(xin,val)  ( `$INSTANCE_NAME`_XIN_OK((xin)) ? ((uint32)(val)) : `$INSTANCE_NAME`_IGNORE_VAL )

/*
#define `$INSTANCE_NAME`_NONZERO_SW_STATIC (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_GX0`|`$SW_GX1`|`$SW_GX2`|`$SW_GX3`|`$SW_RG`|`$SW_GG`|`$SW_RT`|`$SW_GT`|`$SW_QT`|`$EARLY_PS`|`$EARLY_PO`|`$STRB_RST_EN`|`$STRB_RST_SEL`) ))
*/

/* force inclusion in `$Instance_Name`_initPairs */
#define `$INSTANCE_NAME`_NONZERO_SW_STATIC (`$INSTANCE_NAME`_Nonzero(1))

#define `$INSTANCE_NAME`_DEFAULT_SW_STATIC ((uint32)(\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X0,`$INSTANCE_NAME`_PARAM_SW_GX0<<`$INSTANCE_NAME`_StaticVShift(CyUAB_SW_GX0)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X1,`$INSTANCE_NAME`_PARAM_SW_GX1<<`$INSTANCE_NAME`_StaticVShift(CyUAB_SW_GX1)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X2,`$INSTANCE_NAME`_PARAM_SW_GX2<<`$INSTANCE_NAME`_StaticVShift(CyUAB_SW_GX2)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X3,`$INSTANCE_NAME`_PARAM_SW_GX3<<`$INSTANCE_NAME`_StaticVShift(CyUAB_SW_GX3)) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_RG)<<`$INSTANCE_NAME`_SW_RG_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_GG)<<`$INSTANCE_NAME`_SW_GG_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_RT)<<`$INSTANCE_NAME`_SW_RT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_GT)<<`$INSTANCE_NAME`_SW_GT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_QT)<<`$INSTANCE_NAME`_SW_QT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_EARLY_PS)<<`$INSTANCE_NAME`_EARLY_PS_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_EARLY_PO)<<`$INSTANCE_NAME`_EARLY_PO_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_STRB_RST_SEL)<<`$INSTANCE_NAME`_STRB_RST_SEL_SHIFT) | \
    (((uint32)`$INSTANCE_NAME`_PARAM_STRB_RST_EN)<<`$INSTANCE_NAME`_STRB_RST_EN_SHIFT) \
))

/*modbitab source from cyfitter.h*/
#define `$INSTANCE_NAME`_PARAM_MODBIT0_SRC_SEL   (`$INSTANCE_NAME`_UnmappedIsZero(`$INSTANCE_NAME`_halfuab__MODBIT0_SEL))
/*modbitc source from cyfitter.h*/
#define `$INSTANCE_NAME`_PARAM_MODBIT1_SRC_SEL   (`$INSTANCE_NAME`_UnmappedIsZero(`$INSTANCE_NAME`_halfuab__MODBIT1_SEL))

/*
#define `$INSTANCE_NAME`_NONZERO_SW_MODBIT_SRC (`$INSTANCE_NAME`_Nonzero( \
    (`$MODBIT1_SRC_SEL`|`$MODBIT0_SRC_SEL`) ))
*/
/* force inclusion in `$Instance_Name`_initPairs */
#define `$INSTANCE_NAME`_NONZERO_SW_MODBIT_SRC (`$INSTANCE_NAME`_Nonzero(1))

#define `$INSTANCE_NAME`_DEFAULT_SW_MODBIT_SRC ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_MODBIT0_SRC_SEL)<<`$INSTANCE_NAME`_MODBIT0_SRC_SEL_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_MODBIT1_SRC_SEL)<<`$INSTANCE_NAME`_MODBIT1_SRC_SEL_SHIFT) \
))


    
#define `$INSTANCE_NAME`_PARAM_SW_AX0_MODBIT  `$SW_AX0_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_AX1_MODBIT  `$SW_AX1_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_AX2_MODBIT  `$SW_AX2_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_AX3_MODBIT  `$SW_AX3_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_AP          `$SW_AP`
#define `$INSTANCE_NAME`_PARAM_SW_AQ          `$SW_AQ`

#define `$INSTANCE_NAME`_NONZERO_SW_CA_IN0 (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_AX0_MODBIT`|`$SW_AX1_MODBIT`|`$SW_AX2_MODBIT`|`$SW_AX3_MODBIT`|`$SW_AP`|`$SW_AQ`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CA_IN0 ((uint32)(\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X0,`$INSTANCE_NAME`_PARAM_SW_AX0_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_AX0_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X1,`$INSTANCE_NAME`_PARAM_SW_AX1_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_AX1_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X2,`$INSTANCE_NAME`_PARAM_SW_AX2_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_AX2_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X3,`$INSTANCE_NAME`_PARAM_SW_AX3_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_AX3_MODBIT)) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_AP)<<`$INSTANCE_NAME`_SW_AP_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_AQ)<<`$INSTANCE_NAME`_SW_AQ_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_AA         `$SW_AA`
#define `$INSTANCE_NAME`_PARAM_SW_AR_MODBIT  `$SW_AR_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_AG_MODBIT  `$SW_AG_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_AV_MODBIT  `$SW_AV_MODBIT`

/*Shared switch AA intentionally ommitted - handled in Init()*/
#define `$INSTANCE_NAME`_NONZERO_SW_CA_IN1 (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_AR_MODBIT`|`$SW_AG_MODBIT`|`$SW_AV_MODBIT`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CA_IN1 ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_AR_MODBIT)<<`$INSTANCE_NAME`_SW_AR_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_AG_MODBIT)<<`$INSTANCE_NAME`_SW_AG_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_AV_MODBIT)<<`$INSTANCE_NAME`_SW_AV_MODBIT_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_RA_MODBIT  `$SW_RA_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_GA_MODBIT  `$SW_GA_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_VA_MODBIT  `$SW_VA_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_SA         `$SW_SA`

#define `$INSTANCE_NAME`_NONZERO_SW_CA_TOP (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_RA_MODBIT`|`$SW_GA_MODBIT`|`$SW_VA_MODBIT`|`$SW_SA`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CA_TOP ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_RA_MODBIT)<<`$INSTANCE_NAME`_SW_RA_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_GA_MODBIT)<<`$INSTANCE_NAME`_SW_GA_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_VA_MODBIT)<<`$INSTANCE_NAME`_SW_VA_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_SA)<<`$INSTANCE_NAME`_SW_SA_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_BX0_MODBIT `$SW_BX0_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_BX1_MODBIT `$SW_BX1_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_BX2_MODBIT `$SW_BX2_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_BX3_MODBIT `$SW_BX3_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_BP         `$SW_BP`
#define `$INSTANCE_NAME`_PARAM_SW_BQ         `$SW_BQ`

#define `$INSTANCE_NAME`_NONZERO_SW_CB_IN0 (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_BX0_MODBIT`|`$SW_BX1_MODBIT`|`$SW_BX2_MODBIT`|`$SW_BX3_MODBIT`|`$SW_BP`|`$SW_BQ`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CB_IN0 ((uint32)(\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X0,`$INSTANCE_NAME`_PARAM_SW_BX0_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_BX0_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X1,`$INSTANCE_NAME`_PARAM_SW_BX1_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_BX1_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X2,`$INSTANCE_NAME`_PARAM_SW_BX2_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_BX2_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X3,`$INSTANCE_NAME`_PARAM_SW_BX3_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_BX3_MODBIT)) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_BP)<<`$INSTANCE_NAME`_SW_BP_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_BQ)<<`$INSTANCE_NAME`_SW_BQ_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_BB        `$SW_BB`
#define `$INSTANCE_NAME`_PARAM_SW_BR_MODBIT `$SW_BR_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_BG_MODBIT `$SW_BG_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_BV_MODBIT `$SW_BV_MODBIT`

/*Shared switch BB intentionally ommitted - handled in Init()*/
#define `$INSTANCE_NAME`_NONZERO_SW_CB_IN1 (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_BR_MODBIT`|`$SW_BG_MODBIT`|`$SW_BV_MODBIT`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CB_IN1 ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_BR_MODBIT)<<`$INSTANCE_NAME`_SW_BR_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_BG_MODBIT)<<`$INSTANCE_NAME`_SW_BG_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_BV_MODBIT)<<`$INSTANCE_NAME`_SW_BV_MODBIT_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_RB_MODBIT `$SW_RB_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_GB_MODBIT `$SW_GB_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_VB_MODBIT `$SW_VB_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_TB        `$SW_TB`
#define `$INSTANCE_NAME`_PARAM_SW_SB        `$SW_SB`

#define `$INSTANCE_NAME`_NONZERO_SW_CB_TOP (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_RB_MODBIT`|`$SW_GB_MODBIT`|`$SW_VB_MODBIT`|`$SW_TB`|`$SW_SB`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CB_TOP ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_RB_MODBIT)<<`$INSTANCE_NAME`_SW_RB_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_GB_MODBIT)<<`$INSTANCE_NAME`_SW_GB_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_VB_MODBIT)<<`$INSTANCE_NAME`_SW_VB_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_TB)<<`$INSTANCE_NAME`_SW_TB_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_SB)<<`$INSTANCE_NAME`_SW_SB_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_CX0_MODBIT `$SW_CX0_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_CX1_MODBIT `$SW_CX1_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_CX2_MODBIT `$SW_CX2_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_CX3_MODBIT `$SW_CX3_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_CP         `$SW_CP`
#define `$INSTANCE_NAME`_PARAM_SW_CQ         `$SW_CQ`
    
#define `$INSTANCE_NAME`_NONZERO_SW_CC_IN0 (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_CX0_MODBIT`|`$SW_CX1_MODBIT`|`$SW_CX2_MODBIT`|`$SW_CX3_MODBIT`|`$SW_CP`|`$SW_CQ`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CC_IN0 ((uint32)(\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X0,`$INSTANCE_NAME`_PARAM_SW_CX0_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_CX0_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X1,`$INSTANCE_NAME`_PARAM_SW_CX1_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_CX1_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X2,`$INSTANCE_NAME`_PARAM_SW_CX2_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_CX2_MODBIT)) |\
    `$INSTANCE_NAME`_XField(`$INSTANCE_NAME`_X3,`$INSTANCE_NAME`_PARAM_SW_CX3_MODBIT<<`$INSTANCE_NAME`_DynamicVShift(CyUAB_SW_CX3_MODBIT)) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_CP)<<`$INSTANCE_NAME`_SW_CP_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_CQ)<<`$INSTANCE_NAME`_SW_CQ_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_CC        `$SW_CC`
#define `$INSTANCE_NAME`_PARAM_SW_CR_MODBIT `$SW_CR_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_CG_MODBIT `$SW_CG_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_CV_MODBIT `$SW_CV_MODBIT`

/*Shared switch CC intentionally ommitted - handled in Init()*/
#define `$INSTANCE_NAME`_NONZERO_SW_CC_IN1 (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_CR_MODBIT`|`$SW_CG_MODBIT`|`$SW_CV_MODBIT`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CC_IN1 ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_CR_MODBIT)<<`$INSTANCE_NAME`_SW_CR_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_CG_MODBIT)<<`$INSTANCE_NAME`_SW_CG_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_CV_MODBIT)<<`$INSTANCE_NAME`_SW_CV_MODBIT_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_RC_MODBIT `$SW_RC_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_GC_MODBIT `$SW_GC_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_VC_MODBIT `$SW_VC_MODBIT`
#define `$INSTANCE_NAME`_PARAM_SW_TC        `$SW_TC`
#define `$INSTANCE_NAME`_PARAM_SW_SC        `$SW_SC`
#define `$INSTANCE_NAME`_PARAM_SW_ZC        `$SW_ZC`

#define `$INSTANCE_NAME`_NONZERO_SW_CC_TOP (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_RC_MODBIT`|`$SW_GC_MODBIT`|`$SW_VC_MODBIT`|`$SW_TC`|`$SW_SC`|`$SW_ZC`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CC_TOP ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_RC_MODBIT)<<`$INSTANCE_NAME`_SW_RC_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_GC_MODBIT)<<`$INSTANCE_NAME`_SW_GC_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_VC_MODBIT)<<`$INSTANCE_NAME`_SW_VC_MODBIT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_TC)<<`$INSTANCE_NAME`_SW_TC_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_SC)<<`$INSTANCE_NAME`_SW_SC_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_ZC)<<`$INSTANCE_NAME`_SW_ZC_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SW_GF `$SW_GF`
#define `$INSTANCE_NAME`_PARAM_SW_PF `$SW_PF`
#define `$INSTANCE_NAME`_PARAM_SW_PS `$SW_PS`
#define `$INSTANCE_NAME`_PARAM_SW_PO `$SW_PO`

#define `$INSTANCE_NAME`_NONZERO_SW_CF_BOT (`$INSTANCE_NAME`_Nonzero( \
    (`$SW_GF`|`$SW_PF`|`$SW_PS`|`$SW_PO`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_CF_BOT ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_GF)<<`$INSTANCE_NAME`_SW_GF_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_PF)<<`$INSTANCE_NAME`_SW_PF_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_PS)<<`$INSTANCE_NAME`_SW_PS_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SW_PO)<<`$INSTANCE_NAME`_SW_PO_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_CMP_FF     `$CMP_FF`
#define `$INSTANCE_NAME`_PARAM_VALID_WAVE `$VALID_WAVE`
#define `$INSTANCE_NAME`_PARAM_TRIG_OUT   `$TRIG_OUT`
#define `$INSTANCE_NAME`_PARAM_STROBE_SW  `$STROBE_SW`
#define `$INSTANCE_NAME`_PARAM_STROBE_RST `$STROBE_RST`

#define `$INSTANCE_NAME`_NONZERO_SW_OTHER (`$INSTANCE_NAME`_Nonzero( \
    (`$CMP_FF`|`$VALID_WAVE`|`$TRIG_OUT`|`$STROBE_SW`|`$STROBE_RST`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_OTHER ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_CMP_FF)<<`$INSTANCE_NAME`_CMP_FF_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_VALID_WAVE)<<`$INSTANCE_NAME`_VALID_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_TRIG_OUT)<<`$INSTANCE_NAME`_TRIG_OUT_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_STROBE_SW)<<`$INSTANCE_NAME`_STROBE_SW_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_STROBE_RST)<<`$INSTANCE_NAME`_STROBE_RST_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_CA_BOOST  `$CA_BOOST`
#define `$INSTANCE_NAME`_PARAM_CB_BOOST  `$CB_BOOST`
#define `$INSTANCE_NAME`_PARAM_CC_BOOST  `$CC_BOOST`
#define `$INSTANCE_NAME`_PARAM_CF_BOOST  `$CF_BOOST`
#define `$INSTANCE_NAME`_PARAM_SUM_BOOST `$SUM_BOOST`
#define `$INSTANCE_NAME`_PARAM_PUMP_WAVE `$PUMP_WAVE`
    
#define `$INSTANCE_NAME`_NONZERO_SW_BOOST_CTRL (`$INSTANCE_NAME`_Nonzero( \
    (`$CA_BOOST`|`$CB_BOOST`|`$CC_BOOST`|`$CF_BOOST`|`$SUM_BOOST`|`$PUMP_WAVE`) ))
#define `$INSTANCE_NAME`_DEFAULT_SW_BOOST_CTRL ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_CA_BOOST)<<`$INSTANCE_NAME`_CA_BOOST_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CB_BOOST)<<`$INSTANCE_NAME`_CB_BOOST_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CC_BOOST)<<`$INSTANCE_NAME`_CC_BOOST_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_CF_BOOST)<<`$INSTANCE_NAME`_CF_BOOST_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SUM_BOOST)<<`$INSTANCE_NAME`_SUM_BOOST_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_PUMP_WAVE)<<`$INSTANCE_NAME`_PUMP_WAVE_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_STARTUP_DELAY `$STARTUP_DELAY`
#define `$INSTANCE_NAME`_PARAM_ALIGN_MODE    `$ALIGN_MODE`

#define `$INSTANCE_NAME`_NONZERO_STARTUP_DELAY (`$INSTANCE_NAME`_Nonzero( \
	(`$STARTUP_DELAY`|`$ALIGN_MODE`) ))
#define `$INSTANCE_NAME`_DEFAULT_STARTUP_DELAY ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_STARTUP_DELAY)<<`$INSTANCE_NAME`_STARTUP_DELAY_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_ALIGN_MODE)<<`$INSTANCE_NAME`_ALIGN_MODE_SHIFT) \
))

#define `$INSTANCE_NAME`_PARAM_SUBSAMPLE `$SUBSAMPLE`    
#define `$INSTANCE_NAME`_PARAM_SUBSAMPLE_INIT `$SUBSAMPLE_INIT`    
    
#define `$INSTANCE_NAME`_NONZERO_SUBSAMPLE_CTRL (`$INSTANCE_NAME`_Nonzero( \
    (`$SUBSAMPLE`|`$SUBSAMPLE_INIT`) ))
#define `$INSTANCE_NAME`_DEFAULT_SUBSAMPLE_CTRL ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_SUBSAMPLE)<<`$INSTANCE_NAME`_SUBSAMPLE_SHIFT) |\
    (((uint32)`$INSTANCE_NAME`_PARAM_SUBSAMPLE_INIT)<<`$INSTANCE_NAME`_SUBSAMPLE_INIT_SHIFT) \
))
    
#define `$INSTANCE_NAME`_PARAM_LAST_STEP  `$LAST_STEP`

/*trigger_in source from cyfitter.h*/
#define `$INSTANCE_NAME`_PARAM_TRIG_SEL    (`$INSTANCE_NAME`_UnmappedIsZero(`$INSTANCE_NAME`_halfuab__TRIG_SEL))

#define `$INSTANCE_NAME`_PARAM_TRIGGER_EN `$TRIGGER_EN`

/*
#define `$INSTANCE_NAME`_NONZERO_SRAM_CTRL (`$INSTANCE_NAME`_Nonzero( \
    (`$LAST_STEP`|`$TRIG_SEL`|`$TRIGGER_EN`) ))
*/
/* force inclusion in `$Instance_Name`_initPairs */
#define `$INSTANCE_NAME`_NONZERO_SRAM_CTRL (`$INSTANCE_NAME`_Nonzero(1))    
 
#define `$INSTANCE_NAME`_DEFAULT_SRAM_CTRL ((uint32)(\
    (((uint32)`$INSTANCE_NAME`_PARAM_LAST_STEP)<<`$INSTANCE_NAME`_LAST_STEP_SHIFT) | \
    (((uint32)`$INSTANCE_NAME`_PARAM_TRIG_SEL)<<`$INSTANCE_NAME`_TRIG_SEL_SHIFT)   | \
    (((uint32)`$INSTANCE_NAME`_PARAM_TRIGGER_EN)<<`$INSTANCE_NAME`_TRIGGER_EN_SHIFT) \
))
/*There is intentionally no run bit symbol parameter and the run bit is not set as part of the Init() function*/

#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_0  `$WAVE_STEP_0`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_1  `$WAVE_STEP_1`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_2  `$WAVE_STEP_2`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_3  `$WAVE_STEP_3`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_4  `$WAVE_STEP_4`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_5  `$WAVE_STEP_5`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_6  `$WAVE_STEP_6`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_7  `$WAVE_STEP_7`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_8  `$WAVE_STEP_8`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_9  `$WAVE_STEP_9`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_10 `$WAVE_STEP_10`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_11 `$WAVE_STEP_11`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_12 `$WAVE_STEP_12`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_13 `$WAVE_STEP_13`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_14 `$WAVE_STEP_14`
#define `$INSTANCE_NAME`_PARAM_WAVE_STEP_15 `$WAVE_STEP_15`

#define `$INSTANCE_NAME`_NONZERO_WAVE_0  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_0 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_1  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_1 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_2  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_2 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_3  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_3 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_4  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_4 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_5  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_5 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_6  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_6 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_7  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_7 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_8  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_8 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_9  (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_9 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_10 (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_10 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_11 (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_11 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_12 (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_12 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_13 (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_13 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_14 (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_14 ) )
#define `$INSTANCE_NAME`_NONZERO_WAVE_15 (`$INSTANCE_NAME`_Nonzero( `$INSTANCE_NAME`_PARAM_WAVE_STEP_15 ) )


/*all wave steps up to and including the last non-zero wave step 
    are included in the waveConfig array definition */
/*always include WAVE_STEP_0, since LAST_STEP minimum is 0*/
#define `$INSTANCE_NAME`_INC_STEP_0 (`$INSTANCE_NAME`_Nonzero(1))

#define `$INSTANCE_NAME`_INC_STEP_1  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_1  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_2  || `$INSTANCE_NAME`_NONZERO_WAVE_3  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_4  || `$INSTANCE_NAME`_NONZERO_WAVE_5  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_6  || `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_2  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_2  || `$INSTANCE_NAME`_NONZERO_WAVE_3  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_4  || `$INSTANCE_NAME`_NONZERO_WAVE_5  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_6  || `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_3  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_3  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_4  || `$INSTANCE_NAME`_NONZERO_WAVE_5  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_6  || `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_4  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_4  || `$INSTANCE_NAME`_NONZERO_WAVE_5  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_6  || `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )

#define `$INSTANCE_NAME`_INC_STEP_5  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_5  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_6  || `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )

#define `$INSTANCE_NAME`_INC_STEP_6  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_6  || `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_7  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_7  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_8  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_8  || `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_9  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_9  || \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_10  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_10 || `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_11  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_11 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_12  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_12 || `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_13  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_13 || \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_14  ( \
    `$INSTANCE_NAME`_NONZERO_WAVE_14 || `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
#define `$INSTANCE_NAME`_INC_STEP_15  ( `$INSTANCE_NAME`_NONZERO_WAVE_15 )
    
    
/*! @} group_init */

#endif /* #ifndef `$INSTANCE_NAME`_PARAM_H */
    
/*! @endcond */

/* [] END OF FILE */
