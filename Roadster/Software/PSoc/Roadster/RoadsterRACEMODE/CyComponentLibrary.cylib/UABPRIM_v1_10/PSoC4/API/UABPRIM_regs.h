/*!*****************************************************************************
* \file `$INSTANCE_NAME`_regs.h
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
    
#ifndef `$INSTANCE_NAME`_REGS_H
#define `$INSTANCE_NAME`_REGS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_CyUAB_regs.h"

/*!
* \addtogroup group_general
* @{
*/

/*! Get right-aligned register field; mask parameter is alredy shifted */
#define `$INSTANCE_NAME`_GET_FIELD(addr,mask,shift)         CyUAB_GET_FIELD((addr),(mask),(shift))
/*! Set register field without modifying other fields; mask parameter is already shifted */
#define `$INSTANCE_NAME`_SET_FIELD(addr,mask,val,shift)     CyUAB_SET_FIELD((addr),(mask),(val),(shift))
/*! Set multiple register fields with a single register write; mask parameter is already shifted and composite of all fields being written */
#define `$INSTANCE_NAME`_SET_VARIOUS_FIELDS(addr,mask,val)  CyUAB_SET_VARIOUS_FIELDS((addr), (mask), (val))

/*! number of array elements */
#define `$INSTANCE_NAME`_ELEMENT_COUNT(x)  (sizeof((x))/sizeof((x)[0]))
/*! @} group_general */
    
    
#define `$INSTANCE_NAME`_POSITION `$INSTANCE_NAME`_halfuab__POSITION

#define `$INSTANCE_NAME`_ISODD  ( (`$INSTANCE_NAME`_POSITION % 2UL) != 0UL )


#define `$INSTANCE_NAME`_BAD_XIN 0xabadc0deUL
	
/* x input terminals to VIN mapping selected by Creator P&R */

/* 
Decision tree below assigns unused x inputs to unused vin 
can't use preprocessor undef (MISRA requirement, so using a separate flag variable for each stage
VIN_FLAGS A-D track assigned vin assignments through the decision tree steps
*/

#define `$INSTANCE_NAME`_VIN0_ASSIGNED  ( (\
        (`$INSTANCE_NAME`_halfuab__X0==0) || (`$INSTANCE_NAME`_halfuab__X1==0) || \
        (`$INSTANCE_NAME`_halfuab__X2==0) || (`$INSTANCE_NAME`_halfuab__X3==0) ) ? 1 : 0 )
#define `$INSTANCE_NAME`_VIN1_ASSIGNED  ( (\
        (`$INSTANCE_NAME`_halfuab__X0==1) || (`$INSTANCE_NAME`_halfuab__X1==1) || \
        (`$INSTANCE_NAME`_halfuab__X2==1) || (`$INSTANCE_NAME`_halfuab__X3==1) ) ? 1 : 0 )
#define `$INSTANCE_NAME`_VIN2_ASSIGNED  ( (\
        (`$INSTANCE_NAME`_halfuab__X0==2) || (`$INSTANCE_NAME`_halfuab__X1==2) || \
        (`$INSTANCE_NAME`_halfuab__X2==2) || (`$INSTANCE_NAME`_halfuab__X3==2) ) ? 1 : 0 )
#define `$INSTANCE_NAME`_VIN3_ASSIGNED  ( (\
        (`$INSTANCE_NAME`_halfuab__X0==3) || (`$INSTANCE_NAME`_halfuab__X1==3) || \
        (`$INSTANCE_NAME`_halfuab__X2==3) || (`$INSTANCE_NAME`_halfuab__X3==3) ) ? 1 : 0 )


#define `$INSTANCE_NAME`__X0_FLAGS  ( \
    ( (`$INSTANCE_NAME`_VIN0_ASSIGNED)    ) | \
    ( (`$INSTANCE_NAME`_VIN1_ASSIGNED)<<1 ) | \
    ( (`$INSTANCE_NAME`_VIN2_ASSIGNED)<<2 ) | \
    ( (`$INSTANCE_NAME`_VIN3_ASSIGNED)<<3 )   \
)
    
/*x0 input assignment*/
#if ( (0<=`$INSTANCE_NAME`_halfuab__X0) && (`$INSTANCE_NAME`_halfuab__X0<=3) )
    /*fitter assignment is valid*/
    #define `$INSTANCE_NAME`_X0         (`$INSTANCE_NAME`_halfuab__X0)
    #define `$INSTANCE_NAME`__X1_FLAGS  (`$INSTANCE_NAME`__X0_FLAGS)
#else
    /*x0 input is unused (==-1), so map to unused vin*/
    #if   (( `$INSTANCE_NAME`__X0_FLAGS & 0x1 )==0)
        #define `$INSTANCE_NAME`_X0 (0)
        #define `$INSTANCE_NAME`__X1_FLAGS (`$INSTANCE_NAME`__X0_FLAGS|0x1)
    #elif (( `$INSTANCE_NAME`__X0_FLAGS & 0x2 )==0)
        #define `$INSTANCE_NAME`_X0 (1)
        #define `$INSTANCE_NAME`__X1_FLAGS (`$INSTANCE_NAME`__X0_FLAGS|0x2)
    #elif (( `$INSTANCE_NAME`__X0_FLAGS & 0x4 )==0)
        #define `$INSTANCE_NAME`_X0 (2)
        #define `$INSTANCE_NAME`__X1_FLAGS (`$INSTANCE_NAME`__X0_FLAGS|0x4)
    #elif (( `$INSTANCE_NAME`__X0_FLAGS & 0x8 )==0)
        #define `$INSTANCE_NAME`_X0 (3)
        #define `$INSTANCE_NAME`__X1_FLAGS (`$INSTANCE_NAME`__X0_FLAGS|0x8)
    #else
        #error "`$INSTANCE_NAME`_X0 mapping is bad"
    #endif
#endif

/*x1 input assignment*/
#if ( (0<=`$INSTANCE_NAME`_halfuab__X1) && (`$INSTANCE_NAME`_halfuab__X1<=3) )
    /*fitter assignment is valid*/
    #define `$INSTANCE_NAME`_X1         (`$INSTANCE_NAME`_halfuab__X1)
    #define `$INSTANCE_NAME`__X2_FLAGS  (`$INSTANCE_NAME`__X1_FLAGS)
#else
    /*x1 input is unused (==-1), so map to unused vin*/
    #if   (( `$INSTANCE_NAME`__X1_FLAGS & 0x1 )==0)
        #define `$INSTANCE_NAME`_X1 (0)
        #define `$INSTANCE_NAME`__X2_FLAGS (`$INSTANCE_NAME`__X1_FLAGS|0x1)
    #elif (( `$INSTANCE_NAME`__X1_FLAGS & 0x2 )==0)
        #define `$INSTANCE_NAME`_X1 (1)
        #define `$INSTANCE_NAME`__X2_FLAGS (`$INSTANCE_NAME`__X1_FLAGS|0x2)
    #elif (( `$INSTANCE_NAME`__X1_FLAGS & 0x4 )==0)
        #define `$INSTANCE_NAME`_X1 (2)
        #define `$INSTANCE_NAME`__X2_FLAGS (`$INSTANCE_NAME`__X1_FLAGS|0x4)
    #elif (( `$INSTANCE_NAME`__X1_FLAGS & 0x8 )==0)
        #define `$INSTANCE_NAME`_X1 (3)
        #define `$INSTANCE_NAME`__X2_FLAGS (`$INSTANCE_NAME`__X1_FLAGS|0x8)
    #else
        #error "`$INSTANCE_NAME`_X1 mapping is bad"
    #endif
#endif

/*x2 input assignment*/
#if ( (0<=`$INSTANCE_NAME`_halfuab__X2) && (`$INSTANCE_NAME`_halfuab__X2<=3) )
    /*fitter assignment is valid*/
    #define `$INSTANCE_NAME`_X2         (`$INSTANCE_NAME`_halfuab__X2)
    #define `$INSTANCE_NAME`__X3_FLAGS  (`$INSTANCE_NAME`__X2_FLAGS)
#else
    /*x2 input is unused (==-1), so map to unused vin*/
    #if   (( `$INSTANCE_NAME`__X2_FLAGS & 0x1 )==0)
        #define `$INSTANCE_NAME`_X2 (0)
        #define `$INSTANCE_NAME`__X3_FLAGS (`$INSTANCE_NAME`__X2_FLAGS|0x1)
    #elif (( `$INSTANCE_NAME`__X2_FLAGS & 0x2 )==0)
        #define `$INSTANCE_NAME`_X2 (1)
        #define `$INSTANCE_NAME`__X3_FLAGS (`$INSTANCE_NAME`__X2_FLAGS|0x2)
    #elif (( `$INSTANCE_NAME`__X2_FLAGS & 0x4 )==0)
        #define `$INSTANCE_NAME`_X2 (2)
        #define `$INSTANCE_NAME`__X3_FLAGS (`$INSTANCE_NAME`__X2_FLAGS|0x4)
    #elif (( `$INSTANCE_NAME`__X2_FLAGS & 0x8 )==0)
        #define `$INSTANCE_NAME`_X2 (3)
        #define `$INSTANCE_NAME`__X3_FLAGS (`$INSTANCE_NAME`__X2_FLAGS|0x8)
    #else
        #error "`$INSTANCE_NAME`_X2 mapping is bad"
    #endif
#endif

/*x3 input assignment*/
#if ( (0<=`$INSTANCE_NAME`_halfuab__X3) && (`$INSTANCE_NAME`_halfuab__X3<=3) )
    /*fitter assignment is valid*/
    #define `$INSTANCE_NAME`_X3         (`$INSTANCE_NAME`_halfuab__X3)
    #define `$INSTANCE_NAME`__X4_FLAGS  (`$INSTANCE_NAME`__X3_FLAGS)
#else
    /*x2 input is unused (==-1), so map to unused vin*/
    #if   (( `$INSTANCE_NAME`__X3_FLAGS & 0x1 )==0)
        #define `$INSTANCE_NAME`_X3 (0)
        #define `$INSTANCE_NAME`__X4_FLAGS (`$INSTANCE_NAME`__X3_FLAGS|0x1)
    #elif (( `$INSTANCE_NAME`__X3_FLAGS & 0x2 )==0)
        #define `$INSTANCE_NAME`_X3 (1)
        #define `$INSTANCE_NAME`__X4_FLAGS (`$INSTANCE_NAME`__X3_FLAGS|0x2)
    #elif (( `$INSTANCE_NAME`__X3_FLAGS & 0x4 )==0)
        #define `$INSTANCE_NAME`_X3 (2)
        #define `$INSTANCE_NAME`__X4_FLAGS (`$INSTANCE_NAME`__X3_FLAGS|0x4)
    #elif (( `$INSTANCE_NAME`__X3_FLAGS & 0x8 )==0)
        #define `$INSTANCE_NAME`_X3 (3)
        #define `$INSTANCE_NAME`__X4_FLAGS (`$INSTANCE_NAME`__X3_FLAGS|0x8)
    #else
        #error "`$INSTANCE_NAME`_X3 mapping is bad"
    #endif
#endif

/*check results of mapping
1. All vin mapped
2. x0,x1,x2, and x3 are in range of 0 to 3
3. x0,x1,x2, and x3 are unique
*/
#if !( (`$INSTANCE_NAME`__X4_FLAGS==0xF) && \
    ( (0<=`$INSTANCE_NAME`_X0) && (`$INSTANCE_NAME`_X0<=3) ) && \
    ( (0<=`$INSTANCE_NAME`_X1) && (`$INSTANCE_NAME`_X1<=3) ) && \
    ( (0<=`$INSTANCE_NAME`_X2) && (`$INSTANCE_NAME`_X2<=3) ) && \
    ( (0<=`$INSTANCE_NAME`_X3) && (`$INSTANCE_NAME`_X3<=3) ) && \
    (`$INSTANCE_NAME`_X0!=`$INSTANCE_NAME`_X1) && \
    (`$INSTANCE_NAME`_X1!=`$INSTANCE_NAME`_X2) && \
    (`$INSTANCE_NAME`_X2!=`$INSTANCE_NAME`_X3) )
#error "bad x input to vin mapping"
#endif

#define `$INSTANCE_NAME`_XIN_COUNT 4UL



/* UAB half shared switch assymmetry special cases */
#define `$INSTANCE_NAME`_AGND_TIED_ADDR (`$INSTANCE_NAME`_halfuab__AGND_TIED)
#define `$INSTANCE_NAME`_AGND_TIED_PTR  ((reg32*)`$INSTANCE_NAME`_AGND_TIED_ADDR)
#define `$INSTANCE_NAME`_AGND_TIED_REG  (*(`$INSTANCE_NAME`_AGND_TIED_PTR))

#define `$INSTANCE_NAME`_REF_TIED_PTR  ((reg32*)`$INSTANCE_NAME`_halfuab__REF_TIED)
#define `$INSTANCE_NAME`_REF_TIED_REG  (*(`$INSTANCE_NAME`_REF_TIED_PTR))

#define `$INSTANCE_NAME`_SW_AA_PTR     ((reg32*)`$INSTANCE_NAME`_halfuab__SW_AA)
#define `$INSTANCE_NAME`_SW_AA_REG     (*(`$INSTANCE_NAME`_SW_AA_PTR))

#define `$INSTANCE_NAME`_SW_BB_PTR     ((reg32*)`$INSTANCE_NAME`_halfuab__SW_BB)
#define `$INSTANCE_NAME`_SW_BB_REG     (*(`$INSTANCE_NAME`_SW_BB_PTR))

#define `$INSTANCE_NAME`_SW_CC_ADDR     (`$INSTANCE_NAME`_halfuab__SW_CC)
#define `$INSTANCE_NAME`_SW_CC_PTR     ((reg32*)`$INSTANCE_NAME`_SW_CC_ADDR)
#define `$INSTANCE_NAME`_SW_CC_REG     (*(`$INSTANCE_NAME`_SW_CC_PTR))

#define `$INSTANCE_NAME`_ISPAIRED      (`$INSTANCE_NAME`_halfuab__ISPAIRED)

#define `$INSTANCE_NAME`_UAB_CTRL_ADDR                 (`$INSTANCE_NAME`_halfuab__UAB_CTRL)
#define `$INSTANCE_NAME`_UAB_CTRL_PTR                 ((reg32*)`$INSTANCE_NAME`_UAB_CTRL_ADDR)
#define `$INSTANCE_NAME`_UAB_CTRL_REG                 (*(`$INSTANCE_NAME`_UAB_CTRL_PTR))

#define `$INSTANCE_NAME`_INTR_ADDR                     (`$INSTANCE_NAME`_halfuab__INTR)
#define `$INSTANCE_NAME`_INTR_PTR                     ((reg32*)`$INSTANCE_NAME`_INTR_ADDR)
#define `$INSTANCE_NAME`_INTR_REG                     (*(`$INSTANCE_NAME`_INTR_PTR))

#define `$INSTANCE_NAME`_INTR_SET_ADDR                 (`$INSTANCE_NAME`_halfuab__INTR_SET)
#define `$INSTANCE_NAME`_INTR_SET_PTR                 ((reg32*)`$INSTANCE_NAME`_INTR_SET_ADDR)
#define `$INSTANCE_NAME`_INTR_SET_REG                 (*(`$INSTANCE_NAME`_INTR_SET_PTR))

#define `$INSTANCE_NAME`_INTR_MASK_ADDR                (`$INSTANCE_NAME`_halfuab__INTR_MASK)
#define `$INSTANCE_NAME`_INTR_MASK_PTR                ((reg32*)`$INSTANCE_NAME`_INTR_MASK_ADDR)
#define `$INSTANCE_NAME`_INTR_MASK_REG                (*(`$INSTANCE_NAME`_INTR_MASK_PTR))

#define `$INSTANCE_NAME`_INTR_MASKED_ADDR              (`$INSTANCE_NAME`_halfuab__INTR_MASKED)
#define `$INSTANCE_NAME`_INTR_MASKED_PTR              ((reg32*)`$INSTANCE_NAME`_INTR_MASKED_ADDR)
#define `$INSTANCE_NAME`_INTR_MASKED_REG              (*(`$INSTANCE_NAME`_INTR_MASKED_PTR))

#define `$INSTANCE_NAME`_OA_CTRL_ADDR                  (`$INSTANCE_NAME`_halfuab__OA_CTRL)
#define `$INSTANCE_NAME`_OA_CTRL_PTR                  ((reg32*)`$INSTANCE_NAME`_OA_CTRL_ADDR)
#define `$INSTANCE_NAME`_OA_CTRL_REG                  (*(`$INSTANCE_NAME`_OA_CTRL_PTR))

#define `$INSTANCE_NAME`_CAP_CTRL_ADDR                 (`$INSTANCE_NAME`_halfuab__CAP_CTRL)
#define `$INSTANCE_NAME`_CAP_CTRL_PTR                 ((reg32*)`$INSTANCE_NAME`_CAP_CTRL_ADDR)
#define `$INSTANCE_NAME`_CAP_CTRL_REG                 (*(`$INSTANCE_NAME`_CAP_CTRL_PTR))

#define `$INSTANCE_NAME`_CAP_ABCF_VAL_ADDR             (`$INSTANCE_NAME`_halfuab__CAP_ABCF_VAL)
#define `$INSTANCE_NAME`_CAP_ABCF_VAL_PTR             ((reg32*)`$INSTANCE_NAME`_CAP_ABCF_VAL_ADDR)
#define `$INSTANCE_NAME`_CAP_ABCF_VAL_REG             (*(`$INSTANCE_NAME`_CAP_ABCF_VAL_PTR))

#define `$INSTANCE_NAME`_CAP_AB_VAL_NXT_ADDR           (`$INSTANCE_NAME`_halfuab__CAP_AB_VAL_NXT)
#define `$INSTANCE_NAME`_CAP_AB_VAL_NXT_PTR           ((reg32*)`$INSTANCE_NAME`_CAP_AB_VAL_NXT_ADDR)
#define `$INSTANCE_NAME`_CAP_AB_VAL_NXT_REG           (*(`$INSTANCE_NAME`_CAP_AB_VAL_NXT_PTR))

#define `$INSTANCE_NAME`_CAP_CF_VAL_NXT_ADDR           (`$INSTANCE_NAME`_halfuab__CAP_CF_VAL_NXT)
#define `$INSTANCE_NAME`_CAP_CF_VAL_NXT_PTR           ((reg32*)`$INSTANCE_NAME`_CAP_CF_VAL_NXT_ADDR)
#define `$INSTANCE_NAME`_CAP_CF_VAL_NXT_REG           (*(`$INSTANCE_NAME`_CAP_CF_VAL_NXT_PTR))

#define `$INSTANCE_NAME`_STARTUP_DELAY_ADDR            (`$INSTANCE_NAME`_halfuab__STARTUP_DELAY)
#define `$INSTANCE_NAME`_STARTUP_DELAY_PTR            ((reg32*)`$INSTANCE_NAME`_STARTUP_DELAY_ADDR)
#define `$INSTANCE_NAME`_STARTUP_DELAY_REG            (*(`$INSTANCE_NAME`_STARTUP_DELAY_PTR))

#define `$INSTANCE_NAME`_SUBSAMPLE_CTRL_ADDR           (`$INSTANCE_NAME`_halfuab__SUBSAMPLE_CTRL)
#define `$INSTANCE_NAME`_SUBSAMPLE_CTRL_PTR           ((reg32*)`$INSTANCE_NAME`_SUBSAMPLE_CTRL_ADDR)
#define `$INSTANCE_NAME`_SUBSAMPLE_CTRL_REG           (*(`$INSTANCE_NAME`_SUBSAMPLE_CTRL_PTR))

#define `$INSTANCE_NAME`_SW_STATIC_ADDR               (`$INSTANCE_NAME`_halfuab__SW_STATIC )
#define `$INSTANCE_NAME`_SW_STATIC_PTR                ((reg32*)`$INSTANCE_NAME`_SW_STATIC_ADDR)
#define `$INSTANCE_NAME`_SW_STATIC_REG                (*(`$INSTANCE_NAME`_SW_STATIC_PTR))

#define `$INSTANCE_NAME`_SW_MODBIT_SRC_ADDR            (`$INSTANCE_NAME`_halfuab__SW_MODBIT_SRC)
#define `$INSTANCE_NAME`_SW_MODBIT_SRC_PTR            ((reg32*)`$INSTANCE_NAME`_SW_MODBIT_SRC_ADDR)
#define `$INSTANCE_NAME`_SW_MODBIT_SRC_REG            (*(`$INSTANCE_NAME`_SW_MODBIT_SRC_PTR))

#define `$INSTANCE_NAME`_SW_CA_IN0_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CA_IN0)
#define `$INSTANCE_NAME`_SW_CA_IN0_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CA_IN0_ADDR)
#define `$INSTANCE_NAME`_SW_CA_IN0_REG                (*(`$INSTANCE_NAME`_SW_CA_IN0_PTR))

#define `$INSTANCE_NAME`_SW_CA_IN1_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CA_IN1)
#define `$INSTANCE_NAME`_SW_CA_IN1_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CA_IN1_ADDR)
#define `$INSTANCE_NAME`_SW_CA_IN1_REG                (*(`$INSTANCE_NAME`_SW_CA_IN1_PTR))

#define `$INSTANCE_NAME`_SW_CA_TOP_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CA_TOP)
#define `$INSTANCE_NAME`_SW_CA_TOP_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CA_TOP_ADDR)
#define `$INSTANCE_NAME`_SW_CA_TOP_REG                (*(`$INSTANCE_NAME`_SW_CA_TOP_PTR))

#define `$INSTANCE_NAME`_SW_CB_IN0_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CB_IN0)
#define `$INSTANCE_NAME`_SW_CB_IN0_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CB_IN0_ADDR)
#define `$INSTANCE_NAME`_SW_CB_IN0_REG                (*(`$INSTANCE_NAME`_SW_CB_IN0_PTR))

#define `$INSTANCE_NAME`_SW_CB_IN1_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CB_IN1)
#define `$INSTANCE_NAME`_SW_CB_IN1_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CB_IN1_ADDR)
#define `$INSTANCE_NAME`_SW_CB_IN1_REG                (*(`$INSTANCE_NAME`_SW_CB_IN1_PTR))

#define `$INSTANCE_NAME`_SW_CB_TOP_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CB_TOP)
#define `$INSTANCE_NAME`_SW_CB_TOP_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CB_TOP_ADDR)
#define `$INSTANCE_NAME`_SW_CB_TOP_REG                (*(`$INSTANCE_NAME`_SW_CB_TOP_PTR))

#define `$INSTANCE_NAME`_SW_CC_IN0_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CC_IN0)
#define `$INSTANCE_NAME`_SW_CC_IN0_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CC_IN0_ADDR)
#define `$INSTANCE_NAME`_SW_CC_IN0_REG                (*(`$INSTANCE_NAME`_SW_CC_IN0_PTR))

#define `$INSTANCE_NAME`_SW_CC_IN1_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CC_IN1)
#define `$INSTANCE_NAME`_SW_CC_IN1_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CC_IN1_ADDR)
#define `$INSTANCE_NAME`_SW_CC_IN1_REG                (*(`$INSTANCE_NAME`_SW_CC_IN1_PTR))

#define `$INSTANCE_NAME`_SW_CC_TOP_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CC_TOP)
#define `$INSTANCE_NAME`_SW_CC_TOP_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CC_TOP_ADDR)
#define `$INSTANCE_NAME`_SW_CC_TOP_REG                (*(`$INSTANCE_NAME`_SW_CC_TOP_PTR))

#define `$INSTANCE_NAME`_SW_CF_BOT_ADDR                (`$INSTANCE_NAME`_halfuab__SW_CF_BOT)
#define `$INSTANCE_NAME`_SW_CF_BOT_PTR                ((reg32*)`$INSTANCE_NAME`_SW_CF_BOT_ADDR)
#define `$INSTANCE_NAME`_SW_CF_BOT_REG                (*(`$INSTANCE_NAME`_SW_CF_BOT_PTR))

#define `$INSTANCE_NAME`_SW_OTHER_ADDR                 (`$INSTANCE_NAME`_halfuab__SW_OTHER)
#define `$INSTANCE_NAME`_SW_OTHER_PTR                 ((reg32*)`$INSTANCE_NAME`_SW_OTHER_ADDR)
#define `$INSTANCE_NAME`_SW_OTHER_REG                 (*(`$INSTANCE_NAME`_SW_OTHER_PTR))

#define `$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR            (`$INSTANCE_NAME`_halfuab__SW_BOOST_CTRL)
#define `$INSTANCE_NAME`_SW_BOOST_CTRL_PTR            ((reg32*)`$INSTANCE_NAME`_SW_BOOST_CTRL_ADDR)
#define `$INSTANCE_NAME`_SW_BOOST_CTRL_REG            (*(`$INSTANCE_NAME`_SW_BOOST_CTRL_PTR))

#define `$INSTANCE_NAME`_SRAM_CTRL_ADDR                (`$INSTANCE_NAME`_halfuab__SRAM_CTRL)
#define `$INSTANCE_NAME`_SRAM_CTRL_PTR                ((reg32*)`$INSTANCE_NAME`_SRAM_CTRL_ADDR)
#define `$INSTANCE_NAME`_SRAM_CTRL_REG                (*(`$INSTANCE_NAME`_SRAM_CTRL_PTR))

#define `$INSTANCE_NAME`_STAT_ADDR                     (`$INSTANCE_NAME`_halfuab__STAT)
#define `$INSTANCE_NAME`_STAT_PTR                     ((reg32*)`$INSTANCE_NAME`_STAT_ADDR)
#define `$INSTANCE_NAME`_STAT_REG                     (*(`$INSTANCE_NAME`_STAT_PTR))

#define `$INSTANCE_NAME`_SRAM0_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM0)
#define `$INSTANCE_NAME`_SRAM0_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM0_ADDR)
#define `$INSTANCE_NAME`_SRAM0_REG                    (*(`$INSTANCE_NAME`_SRAM0_PTR))

#define `$INSTANCE_NAME`_SRAM1_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM1)
#define `$INSTANCE_NAME`_SRAM1_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM1_ADDR)
#define `$INSTANCE_NAME`_SRAM1_REG                    (*(`$INSTANCE_NAME`_SRAM1_PTR))

#define `$INSTANCE_NAME`_SRAM2_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM2)
#define `$INSTANCE_NAME`_SRAM2_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM2_ADDR)
#define `$INSTANCE_NAME`_SRAM2_REG                    (*(`$INSTANCE_NAME`_SRAM2_PTR))

#define `$INSTANCE_NAME`_SRAM3_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM3)
#define `$INSTANCE_NAME`_SRAM3_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM3_ADDR)
#define `$INSTANCE_NAME`_SRAM3_REG                    (*(`$INSTANCE_NAME`_SRAM3_PTR))

#define `$INSTANCE_NAME`_SRAM4_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM4)
#define `$INSTANCE_NAME`_SRAM4_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM4_ADDR)
#define `$INSTANCE_NAME`_SRAM4_REG                    (*(`$INSTANCE_NAME`_SRAM4_PTR))

#define `$INSTANCE_NAME`_SRAM5_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM5)
#define `$INSTANCE_NAME`_SRAM5_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM5_ADDR)
#define `$INSTANCE_NAME`_SRAM5_REG                    (*(`$INSTANCE_NAME`_SRAM5_PTR))

#define `$INSTANCE_NAME`_SRAM6_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM6)
#define `$INSTANCE_NAME`_SRAM6_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM6_ADDR)
#define `$INSTANCE_NAME`_SRAM6_REG                    (*(`$INSTANCE_NAME`_SRAM6_PTR))

#define `$INSTANCE_NAME`_SRAM7_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM7)
#define `$INSTANCE_NAME`_SRAM7_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM7_ADDR)
#define `$INSTANCE_NAME`_SRAM7_REG                    (*(`$INSTANCE_NAME`_SRAM7_PTR))

#define `$INSTANCE_NAME`_SRAM8_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM8)
#define `$INSTANCE_NAME`_SRAM8_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM8_ADDR)
#define `$INSTANCE_NAME`_SRAM8_REG                    (*(`$INSTANCE_NAME`_SRAM8_PTR))

#define `$INSTANCE_NAME`_SRAM9_ADDR                    (`$INSTANCE_NAME`_halfuab__SRAM9)
#define `$INSTANCE_NAME`_SRAM9_PTR                    ((reg32*)`$INSTANCE_NAME`_SRAM9_ADDR)
#define `$INSTANCE_NAME`_SRAM9_REG                    (*(`$INSTANCE_NAME`_SRAM9_PTR))

#define `$INSTANCE_NAME`_SRAM10_ADDR                   (`$INSTANCE_NAME`_halfuab__SRAM10)
#define `$INSTANCE_NAME`_SRAM10_PTR                   ((reg32*)`$INSTANCE_NAME`_SRAM10_ADDR)
#define `$INSTANCE_NAME`_SRAM10_REG                   (*(`$INSTANCE_NAME`_SRAM10_PTR))

#define `$INSTANCE_NAME`_SRAM11_ADDR                   (`$INSTANCE_NAME`_halfuab__SRAM11)
#define `$INSTANCE_NAME`_SRAM11_PTR                   ((reg32*)`$INSTANCE_NAME`_SRAM11_ADDR)
#define `$INSTANCE_NAME`_SRAM11_REG                   (*(`$INSTANCE_NAME`_SRAM11_PTR))

#define `$INSTANCE_NAME`_SRAM12_ADDR                   (`$INSTANCE_NAME`_halfuab__SRAM12)
#define `$INSTANCE_NAME`_SRAM12_PTR                   ((reg32*)`$INSTANCE_NAME`_SRAM12_ADDR)
#define `$INSTANCE_NAME`_SRAM12_REG                   (*(`$INSTANCE_NAME`_SRAM12_PTR))

#define `$INSTANCE_NAME`_SRAM13_ADDR                   (`$INSTANCE_NAME`_halfuab__SRAM13)
#define `$INSTANCE_NAME`_SRAM13_PTR                   ((reg32*)`$INSTANCE_NAME`_SRAM13_ADDR)
#define `$INSTANCE_NAME`_SRAM13_REG                   (*(`$INSTANCE_NAME`_SRAM13_PTR))

#define `$INSTANCE_NAME`_SRAM14_ADDR                   (`$INSTANCE_NAME`_halfuab__SRAM14)
#define `$INSTANCE_NAME`_SRAM14_PTR                   ((reg32*)`$INSTANCE_NAME`_SRAM14_ADDR)
#define `$INSTANCE_NAME`_SRAM14_REG                   (*(`$INSTANCE_NAME`_SRAM14_PTR))

#define `$INSTANCE_NAME`_SRAM15_ADDR                   (`$INSTANCE_NAME`_halfuab__SRAM15)
#define `$INSTANCE_NAME`_SRAM15_PTR                   ((reg32*)`$INSTANCE_NAME`_SRAM15_ADDR)
#define `$INSTANCE_NAME`_SRAM15_REG                   (*(`$INSTANCE_NAME`_SRAM15_PTR))

#define `$INSTANCE_NAME`_SW_CC1_IN0_ADDR               (`$INSTANCE_NAME`_halfuab__SW_CC1_IN0)
#define `$INSTANCE_NAME`_SW_CC1_IN0_PTR               ((reg32*)`$INSTANCE_NAME`_SW_CC1_IN0_ADDR)
#define `$INSTANCE_NAME`_SW_CC1_IN0_REG               (*(`$INSTANCE_NAME`_SW_CC1_IN0_PTR))

#define `$INSTANCE_NAME`_SW_CC1_IN1_ADDR               (`$INSTANCE_NAME`_halfuab__SW_CC1_IN1)
#define `$INSTANCE_NAME`_SW_CC1_IN1_PTR               ((reg32*)`$INSTANCE_NAME`_SW_CC1_IN1_ADDR)
#define `$INSTANCE_NAME`_SW_CC1_IN1_REG               (*(`$INSTANCE_NAME`_SW_CC1_IN1_PTR))

#define `$INSTANCE_NAME`_SW_CC1_TOP_ADDR               (`$INSTANCE_NAME`_halfuab__SW_CC1_TOP)
#define `$INSTANCE_NAME`_SW_CC1_TOP_PTR               ((reg32*)`$INSTANCE_NAME`_SW_CC1_TOP_ADDR)
#define `$INSTANCE_NAME`_SW_CC1_TOP_REG               (*(`$INSTANCE_NAME`_SW_CC1_TOP_PTR))

#define `$INSTANCE_NAME`_CAP_TRIM_ADDR                 (`$INSTANCE_NAME`_halfuab__CAP_TRIM)
#define `$INSTANCE_NAME`_CAP_TRIM_PTR                 ((reg32*)`$INSTANCE_NAME`_CAP_TRIM_ADDR)
#define `$INSTANCE_NAME`_CAP_TRIM_REG                 (*(`$INSTANCE_NAME`_CAP_TRIM_PTR))

#define `$INSTANCE_NAME`_OA_TRIM_ADDR                  (`$INSTANCE_NAME`_halfuab__OA_TRIM)
#define `$INSTANCE_NAME`_OA_TRIM_PTR                  ((reg32*)`$INSTANCE_NAME`_OA_TRIM_ADDR)
#define `$INSTANCE_NAME`_OA_TRIM_REG                  (*(`$INSTANCE_NAME`_OA_TRIM_PTR))

/* Starting address for half UAB region */
#define `$INSTANCE_NAME`_BASE_ADDR                    (`$INSTANCE_NAME`_halfuab__OA_CTRL)
    



/*Register Field Definitions*/

    
/*UAB_CTRL*/
#define `$INSTANCE_NAME`_ENABLED_SHIFT                CyUAB_ENABLED_SHIFT
#define `$INSTANCE_NAME`_ENABLED_MASK                 (1UL<<`$INSTANCE_NAME`_ENABLED_SHIFT)


/*INTR*/
#if `$INSTANCE_NAME`_ISODD==1
    #define `$INSTANCE_NAME`_INTR_COMP_SHIFT CyUAB_INTR_COMP1_SHIFT
#else
    #define `$INSTANCE_NAME`_INTR_COMP_SHIFT CyUAB_INTR_COMP0_SHIFT
#endif
#define `$INSTANCE_NAME`_INTR_COMP_MASK               (1UL<<`$INSTANCE_NAME`_INTR_COMP_SHIFT)

#if `$INSTANCE_NAME`_ISODD==1
   #define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT CyUAB_INTR_VDAC1_EMPTY_SHIFT
#else
   #define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT CyUAB_INTR_VDAC0_EMPTY_SHIFT
#endif
#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASK         (1UL<<`$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT)


/*INTR_SET*/
#define `$INSTANCE_NAME`_INTR_COMP_SET_SHIFT          `$INSTANCE_NAME`_INTR_COMP_SHIFT
#define `$INSTANCE_NAME`_INTR_COMP_SET_MASK           (1UL<<`$INSTANCE_NAME`_INTR_COMP_SET_SHIFT)

#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SET_SHIFT    `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT
#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SET_MASK     (1UL<<`$INSTANCE_NAME`_INTR_VDAC_EMPTY_SET_SHIFT)


/*INTR_MASK*/
#define `$INSTANCE_NAME`_INTR_COMP_MASK_SHIFT         `$INSTANCE_NAME`_INTR_COMP_SHIFT
#define `$INSTANCE_NAME`_INTR_COMP_MASK_MASK          (1UL<<`$INSTANCE_NAME`_INTR_COMP_MASK_SHIFT)

#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASK_SHIFT   `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT
#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASK_MASK    (1UL<<`$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASK_SHIFT)


/*INTR_MASKED*/
#define `$INSTANCE_NAME`_INTR_COMP_MASKED_SHIFT       `$INSTANCE_NAME`_INTR_COMP_SHIFT
#define `$INSTANCE_NAME`_INTR_COMP_MASKED_MASK        (1UL<<`$INSTANCE_NAME`_INTR_COMP_MASKED_SHIFT)

#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASKED_SHIFT `$INSTANCE_NAME`_INTR_VDAC_EMPTY_SHIFT
#define `$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASKED_MASK  (1UL<<`$INSTANCE_NAME`_INTR_VDAC_EMPTY_MASKED_SHIFT)


/*OA_CTRL*/
#define `$INSTANCE_NAME`_OA_PWR_SHIFT                 CyUAB_OA_PWR_SHIFT
#define `$INSTANCE_NAME`_OA_PWR_MASK                  (0x7UL<<`$INSTANCE_NAME`_OA_PWR_SHIFT)

#define `$INSTANCE_NAME`_CMP_PWR_SHIFT                CyUAB_CMP_PWR_SHIFT
#define `$INSTANCE_NAME`_CMP_PWR_MASK                 (0x7UL<<`$INSTANCE_NAME`_CMP_PWR_SHIFT)

#define `$INSTANCE_NAME`_CMP_EDGE_SHIFT               CyUAB_CMP_EDGE_SHIFT
#define `$INSTANCE_NAME`_CMP_EDGE_MASK                (0x3UL<<`$INSTANCE_NAME`_CMP_EDGE_SHIFT)
#define `$INSTANCE_NAME`_CMP_EDGE_DISABLE             (0UL)
#define `$INSTANCE_NAME`_CMP_EDGE_RISING              (1UL)
#define `$INSTANCE_NAME`_CMP_EDGE_FALLING             (2UL)
#define `$INSTANCE_NAME`_CMP_EDGE_BOTH                (3UL)

#define `$INSTANCE_NAME`_CMP_DSI_LEVEL_SHIFT          CyUAB_CMP_DSI_LEVEL_SHIFT
#define `$INSTANCE_NAME`_CMP_DSI_LEVEL_MASK           (1UL<<`$INSTANCE_NAME`_CMP_DSI_LEVEL_SHIFT)

#define `$INSTANCE_NAME`_CTRL_SPARE_SHIFT             CyUAB_CTRL_SPARE_SHIFT
#define `$INSTANCE_NAME`_CTRL_SPARE_MASK              (1UL<<`$INSTANCE_NAME`_CTRL_SPARE_SHIFT)

#define `$INSTANCE_NAME`_REF_PWR_SHIFT                CyUAB_REF_PWR_SHIFT
#define `$INSTANCE_NAME`_REF_PWR_MASK                 (0x7UL<<`$INSTANCE_NAME`_REF_PWR_SHIFT)

#define `$INSTANCE_NAME`_REF_PTS_SHIFT                CyUAB_REF_PTS_SHIFT
#define `$INSTANCE_NAME`_REF_PTS_MASK                 (1UL<<`$INSTANCE_NAME`_REF_PTS_SHIFT)

#define `$INSTANCE_NAME`_AGND_PWR_SHIFT               CyUAB_AGND_PWR_SHIFT
#define `$INSTANCE_NAME`_AGND_PWR_MASK                (0x7UL<<`$INSTANCE_NAME`_AGND_PWR_SHIFT)

#define `$INSTANCE_NAME`_AGND_PTS_SHIFT               CyUAB_AGND_PTS_SHIFT
#define `$INSTANCE_NAME`_AGND_PTS_MASK                (1UL<<`$INSTANCE_NAME`_AGND_PTS_SHIFT)

#define `$INSTANCE_NAME`_AGND_TIED_SHIFT              CyUAB_AGND_TIED_SHIFT
#define `$INSTANCE_NAME`_AGND_TIED_MASK               (1UL<<`$INSTANCE_NAME`_AGND_TIED_SHIFT)

#define `$INSTANCE_NAME`_REF_TIED_SHIFT               CyUAB_REF_TIED_SHIFT
#define `$INSTANCE_NAME`_REF_TIED_MASK                (1UL<<`$INSTANCE_NAME`_REF_TIED_SHIFT)    
    
#define `$INSTANCE_NAME`_UAB_PWR_SHIFT                CyUAB_UAB_PWR_SHIFT
#define `$INSTANCE_NAME`_UAB_PWR_MASK                 (0x3UL<<`$INSTANCE_NAME`_UAB_PWR_SHIFT)
#define `$INSTANCE_NAME`_UAB_PWR_NORMAL               (0UL)
#define `$INSTANCE_NAME`_UAB_PWR_ULTRA_LOW            (1UL)
#define `$INSTANCE_NAME`_UAB_PWR_ULTRA_HIGH           (2UL)
#define `$INSTANCE_NAME`_UAB_PWR_Reserved             (3UL)


/*CAP_CTRL*/
#define `$INSTANCE_NAME`_CB_GND_SHIFT                 CyUAB_CB_GND_SHIFT
#define `$INSTANCE_NAME`_CB_GND_MASK                  (1UL<<`$INSTANCE_NAME`_CB_GND_SHIFT)

#define `$INSTANCE_NAME`_CC_GND_SHIFT                 CyUAB_CC_GND_SHIFT
#define `$INSTANCE_NAME`_CC_GND_MASK                  (1UL<<`$INSTANCE_NAME`_CC_GND_SHIFT)

#define `$INSTANCE_NAME`_FRC_SIGN_BIT_SHIFT           CyUAB_FRC_SIGN_BIT_SHIFT
#define `$INSTANCE_NAME`_FRC_SIGN_BIT_MASK            (1UL<<CyUAB_FRC_SIGN_BIT_SHIFT)

#define `$INSTANCE_NAME`_DAC_MODE_EN_SHIFT            CyUAB_DAC_MODE_EN_SHIFT
#define `$INSTANCE_NAME`_DAC_MODE_EN_MASK             (1UL<<`$INSTANCE_NAME`_DAC_MODE_EN_SHIFT)

#define `$INSTANCE_NAME`_DAC_MODE_SHIFT               CyUAB_DAC_MODE_SHIFT
#define `$INSTANCE_NAME`_DAC_MODE_MASK                (0x3UL<<`$INSTANCE_NAME`_DAC_MODE_SHIFT)
#define `$INSTANCE_NAME`_DAC_MODE_UNSIGNED12          (0UL)
#define `$INSTANCE_NAME`_DAC_MODE_VIRT_SIGNED12       (1UL)
#define `$INSTANCE_NAME`_DAC_MODE_SIGNED13            (2UL)
#define `$INSTANCE_NAME`_DAC_MODE_RESERVED            (3UL)


/*CAP_ABCF_VAL, CAP_AB_VAL_NXT, and CAP_CF_VAL_NXT*/
#define `$INSTANCE_NAME`_CB_VAL_SHIFT                 CyUAB_CB_VAL_SHIFT
#define `$INSTANCE_NAME`_CB_VAL_MASK                  (0x3fUL<<`$INSTANCE_NAME`_CB_VAL_SHIFT)

#define `$INSTANCE_NAME`_CA_VAL_SHIFT                 CyUAB_CA_VAL_SHIFT
#define `$INSTANCE_NAME`_CA_VAL_MASK                  (0x3fUL<<`$INSTANCE_NAME`_CA_VAL_SHIFT)

#define `$INSTANCE_NAME`_SIGN_VAL_SHIFT               CyUAB_SIGN_VAL_SHIFT
#define `$INSTANCE_NAME`_SIGN_VAL_MASK                (1UL<<`$INSTANCE_NAME`_SIGN_VAL_SHIFT)

#define `$INSTANCE_NAME`_CB_64_SHIFT                  CyUAB_CB_64_SHIFT
#define `$INSTANCE_NAME`_CB_64_MASK                   (1UL<<`$INSTANCE_NAME`_CB_64_SHIFT)

#define `$INSTANCE_NAME`_CC_VAL_SHIFT                 CyUAB_CC_VAL_SHIFT
#define `$INSTANCE_NAME`_CC_VAL_MASK                  (0x3fUL<<`$INSTANCE_NAME`_CC_VAL_SHIFT)

#define `$INSTANCE_NAME`_CF_VAL_SHIFT                 CyUAB_CF_VAL_SHIFT
#define `$INSTANCE_NAME`_CF_VAL_MASK                  (0x1fUL<<`$INSTANCE_NAME`_CF_VAL_SHIFT)


/*CAP_CF_VAL_NXT*/
#define `$INSTANCE_NAME`_CC_VAL_UPDATE_SHIFT          CyUAB_CC_VAL_UPDATE_SHIFT
#define `$INSTANCE_NAME`_CC_VAL_UPDATE_MASK           (1UL<<`$INSTANCE_NAME`_CC_VAL_UPDATE_SHIFT)

#define `$INSTANCE_NAME`_CF_VAL_UPDATE_SHIFT          CyUAB_CF_VAL_UPDATE_SHIFT
#define `$INSTANCE_NAME`_CF_VAL_UPDATE_MASK           (1UL<<`$INSTANCE_NAME`_CF_VAL_UPDATE_SHIFT)


/*STARTUP_DELAY*/
#define `$INSTANCE_NAME`_STARTUP_DELAY_SHIFT          CyUAB_STARTUP_DELAY_SHIFT
#define `$INSTANCE_NAME`_STARTUP_DELAY_MASK           (0x0000ffffUL)

#define `$INSTANCE_NAME`_ALIGN_MODE_SHIFT             CyUAB_ALIGN_MODE_SHIFT
#define `$INSTANCE_NAME`_ALIGN_MODE_MASK              (1UL<<`$INSTANCE_NAME`_ALIGN_MODE_SHIFT)


/*SUBSAMPLE_CTRL*/
#define `$INSTANCE_NAME`_SUBSAMPLE_SHIFT              CyUAB_SUBSAMPLE_SHIFT
#define `$INSTANCE_NAME`_SUBSAMPLE_MASK               (0xffUL<<`$INSTANCE_NAME`_SUBSAMPLE_SHIFT)

#define `$INSTANCE_NAME`_SUBSAMPLE_INIT_SHIFT         CyUAB_SUBSAMPLE_INIT_SHIFT
#define `$INSTANCE_NAME`_SUBSAMPLE_INIT_MASK          (0xffUL<<`$INSTANCE_NAME`_SUBSAMPLE_INIT_SHIFT)


/*SW_STATIC*/
#define `$INSTANCE_NAME`_SW_G0_SHIFT                  CyUAB_SW_G0_SHIFT
#define `$INSTANCE_NAME`_SW_G0_MASK                   (1UL<<`$INSTANCE_NAME`_SW_G0_SHIFT)

#define `$INSTANCE_NAME`_SW_G1_SHIFT                  CyUAB_SW_G1_SHIFT
#define `$INSTANCE_NAME`_SW_G1_MASK                   (1UL<<`$INSTANCE_NAME`_SW_G1_SHIFT)

#define `$INSTANCE_NAME`_SW_G2_SHIFT                  CyUAB_SW_G2_SHIFT
#define `$INSTANCE_NAME`_SW_G2_MASK                   (1UL<<`$INSTANCE_NAME`_SW_G2_SHIFT)

#define `$INSTANCE_NAME`_SW_G3_SHIFT                  CyUAB_SW_G3_SHIFT
#define `$INSTANCE_NAME`_SW_G3_MASK                   (1UL<<`$INSTANCE_NAME`_SW_G3_SHIFT)

#define `$INSTANCE_NAME`_SW_RG_SHIFT                  CyUAB_SW_RG_SHIFT
#define `$INSTANCE_NAME`_SW_RG_MASK                   (1UL<<`$INSTANCE_NAME`_SW_RG_SHIFT)

#define `$INSTANCE_NAME`_SW_GG_SHIFT                  CyUAB_SW_GG_SHIFT
#define `$INSTANCE_NAME`_SW_GG_MASK                   (1UL<<`$INSTANCE_NAME`_SW_GG_SHIFT)

#define `$INSTANCE_NAME`_SW_RT_SHIFT                  CyUAB_SW_RT_SHIFT
#define `$INSTANCE_NAME`_SW_RT_MASK                   (1UL<<`$INSTANCE_NAME`_SW_RT_SHIFT)

#define `$INSTANCE_NAME`_SW_GT_SHIFT                  CyUAB_SW_GT_SHIFT
#define `$INSTANCE_NAME`_SW_GT_MASK                   (1UL<<`$INSTANCE_NAME`_SW_GT_SHIFT)

#define `$INSTANCE_NAME`_SW_QT_SHIFT                  CyUAB_SW_QT_SHIFT
#define `$INSTANCE_NAME`_SW_QT_MASK                   (1UL<<`$INSTANCE_NAME`_SW_QT_SHIFT)

#define `$INSTANCE_NAME`_EARLY_PS_SHIFT               CyUAB_EARLY_PS_SHIFT
#define `$INSTANCE_NAME`_EARLY_PS_MASK                (1UL<<`$INSTANCE_NAME`_EARLY_PS_SHIFT)

#define `$INSTANCE_NAME`_EARLY_PO_SHIFT               CyUAB_EARLY_PO_SHIFT
#define `$INSTANCE_NAME`_EARLY_PO_MASK                (1UL<<`$INSTANCE_NAME`_EARLY_PO_SHIFT)

#define `$INSTANCE_NAME`_STRB_RST_SEL_SHIFT           CyUAB_STRB_RST_SEL_SHIFT
#define `$INSTANCE_NAME`_STRB_RST_SEL_MASK            (0x1fUL<<`$INSTANCE_NAME`_STRB_RST_SEL_SHIFT)

#define `$INSTANCE_NAME`_STRB_RST_EN_SHIFT            CyUAB_STRB_RST_EN_SHIFT
#define `$INSTANCE_NAME`_STRB_RST_EN_MASK             (1UL<<`$INSTANCE_NAME`_STRB_RST_EN_SHIFT)


/*SW_MODBIT_SRC*/
#define `$INSTANCE_NAME`_MODBIT0_SRC_SEL_SHIFT        CyUAB_MODBIT0_SRC_SEL_SHIFT
#define `$INSTANCE_NAME`_MODBIT0_SRC_SEL_MASK         (0x1fUL<<`$INSTANCE_NAME`_MODBIT0_SRC_SEL_SHIFT)

#define `$INSTANCE_NAME`_MODBIT1_SRC_SEL_SHIFT        CyUAB_MODBIT1_SRC_SEL_SHIFT
#define `$INSTANCE_NAME`_MODBIT1_SRC_SEL_MASK         (0x1fUL<<`$INSTANCE_NAME`_MODBIT1_SRC_SEL_SHIFT)


/*SW_CA_IN0*/
#define `$INSTANCE_NAME`_SW_A0_MODBIT_SHIFT           CyUAB_SW_A0_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_A0_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_A0_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_A1_MODBIT_SHIFT           CyUAB_SW_A1_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_A1_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_A1_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_A2_MODBIT_SHIFT           CyUAB_SW_A2_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_A2_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_A2_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_A3_MODBIT_SHIFT           CyUAB_SW_A3_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_A3_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_A3_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_AP_SHIFT                  CyUAB_SW_AP_SHIFT
#define `$INSTANCE_NAME`_SW_AP_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_AP_SHIFT)

#define `$INSTANCE_NAME`_SW_AQ_SHIFT                  CyUAB_SW_AQ_SHIFT
#define `$INSTANCE_NAME`_SW_AQ_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_AQ_SHIFT)

/*SW_CA_IN1*/    
#define `$INSTANCE_NAME`_SW_AA_SHIFT                  CyUAB_SW_AA_SHIFT
#define `$INSTANCE_NAME`_SW_AA_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_AA_SHIFT)

#define `$INSTANCE_NAME`_SW_AR_MODBIT_SHIFT           CyUAB_SW_AR_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_AR_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_AR_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_AG_MODBIT_SHIFT           CyUAB_SW_AG_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_AG_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_AG_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_AV_MODBIT_SHIFT           CyUAB_SW_AV_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_AV_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_AV_MODBIT_SHIFT)


/*SW_CA_TOP*/
#define `$INSTANCE_NAME`_SW_RA_MODBIT_SHIFT           CyUAB_SW_RA_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_RA_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_RA_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_GA_MODBIT_SHIFT           CyUAB_SW_GA_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_GA_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_GA_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_VA_MODBIT_SHIFT           CyUAB_SW_VA_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_VA_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_VA_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_SA_SHIFT                  CyUAB_SW_SA_SHIFT
#define `$INSTANCE_NAME`_SW_SA_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_SA_SHIFT)


/*SW_CB_IN0*/
#define `$INSTANCE_NAME`_SW_B0_MODBIT_SHIFT           CyUAB_SW_B0_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_B0_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_B0_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_B1_MODBIT_SHIFT           CyUAB_SW_B1_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_B1_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_B1_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_B2_MODBIT_SHIFT           CyUAB_SW_B2_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_B2_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_B2_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_B3_MODBIT_SHIFT           CyUAB_SW_B3_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_B3_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_B3_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_BP_SHIFT                  CyUAB_SW_BP_SHIFT
#define `$INSTANCE_NAME`_SW_BP_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_BP_SHIFT)

#define `$INSTANCE_NAME`_SW_BQ_SHIFT                  CyUAB_SW_BQ_SHIFT
#define `$INSTANCE_NAME`_SW_BQ_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_BQ_SHIFT)


/*SW_CB_IN1*/
#define `$INSTANCE_NAME`_SW_BB_SHIFT                  CyUAB_SW_BB_SHIFT
#define `$INSTANCE_NAME`_SW_BB_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_BB_SHIFT)

#define `$INSTANCE_NAME`_SW_BR_MODBIT_SHIFT           CyUAB_SW_BR_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_BR_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_BR_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_BG_MODBIT_SHIFT           CyUAB_SW_BG_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_BG_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_BG_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_BV_MODBIT_SHIFT           CyUAB_SW_BV_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_BV_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_BV_MODBIT_SHIFT)


/*SW_CB_TOP*/
#define `$INSTANCE_NAME`_SW_RB_MODBIT_SHIFT           CyUAB_SW_RB_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_RB_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_RB_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_GB_MODBIT_SHIFT           CyUAB_SW_GB_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_GB_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_GB_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_VB_MODBIT_SHIFT           CyUAB_SW_VB_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_VB_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_VB_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_TB_SHIFT                  CyUAB_SW_TB_SHIFT
#define `$INSTANCE_NAME`_SW_TB_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_TB_SHIFT)

#define `$INSTANCE_NAME`_SW_SB_SHIFT                  CyUAB_SW_SB_SHIFT
#define `$INSTANCE_NAME`_SW_SB_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_SB_SHIFT)


/*SW_CC_IN0*/
#define `$INSTANCE_NAME`_SW_C0_MODBIT_SHIFT           CyUAB_SW_C0_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_C0_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_C0_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_C1_MODBIT_SHIFT           CyUAB_SW_C1_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_C1_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_C1_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_C2_MODBIT_SHIFT           CyUAB_SW_C2_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_C2_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_C2_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_C3_MODBIT_SHIFT           CyUAB_SW_C3_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_C3_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_C3_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_CP_SHIFT                  CyUAB_SW_CP_SHIFT
#define `$INSTANCE_NAME`_SW_CP_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_CP_SHIFT)

#define `$INSTANCE_NAME`_SW_CQ_SHIFT                  CyUAB_SW_CQ_SHIFT
#define `$INSTANCE_NAME`_SW_CQ_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_CQ_SHIFT)


/*SW_CC_IN1*/
#define `$INSTANCE_NAME`_SW_CC_SHIFT                  CyUAB_SW_CC_SHIFT
#define `$INSTANCE_NAME`_SW_CC_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_CC_SHIFT)

#define `$INSTANCE_NAME`_SW_CR_MODBIT_SHIFT           CyUAB_SW_CR_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_CR_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_CR_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_CG_MODBIT_SHIFT           CyUAB_SW_CG_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_CG_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_CG_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_CV_MODBIT_SHIFT           CyUAB_SW_CV_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_CV_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_CV_MODBIT_SHIFT)


/*SW_CC_TOP*/
#define `$INSTANCE_NAME`_SW_RC_MODBIT_SHIFT           CyUAB_SW_RC_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_RC_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_RC_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_GC_MODBIT_SHIFT           CyUAB_SW_GC_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_GC_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_GC_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_VC_MODBIT_SHIFT           CyUAB_SW_VC_MODBIT_SHIFT
#define `$INSTANCE_NAME`_SW_VC_MODBIT_MASK            (0xfUL<<`$INSTANCE_NAME`_SW_VC_MODBIT_SHIFT)

#define `$INSTANCE_NAME`_SW_TC_SHIFT                  CyUAB_SW_TC_SHIFT
#define `$INSTANCE_NAME`_SW_TC_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_TC_SHIFT)

#define `$INSTANCE_NAME`_SW_SC_SHIFT                  CyUAB_SW_SC_SHIFT
#define `$INSTANCE_NAME`_SW_SC_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_SC_SHIFT)

#define `$INSTANCE_NAME`_SW_ZC_SHIFT                  CyUAB_SW_ZC_SHIFT
#define `$INSTANCE_NAME`_SW_ZC_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_ZC_SHIFT)


/*SW_CF_BOT*/
#define `$INSTANCE_NAME`_SW_GF_SHIFT                  CyUAB_SW_GF_SHIFT
#define `$INSTANCE_NAME`_SW_GF_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_GF_SHIFT)

#define `$INSTANCE_NAME`_SW_PF_SHIFT                  CyUAB_SW_PF_SHIFT
#define `$INSTANCE_NAME`_SW_PF_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_PF_SHIFT)

#define `$INSTANCE_NAME`_SW_PS_SHIFT                  CyUAB_SW_PS_SHIFT
#define `$INSTANCE_NAME`_SW_PS_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_PS_SHIFT)

#define `$INSTANCE_NAME`_SW_PO_SHIFT                  CyUAB_SW_PO_SHIFT
#define `$INSTANCE_NAME`_SW_PO_MASK                   (0xfUL<<`$INSTANCE_NAME`_SW_PO_SHIFT)


/*SW_OTHER*/
#define `$INSTANCE_NAME`_CMP_FF_SHIFT                 CyUAB_CMP_FF_SHIFT
#define `$INSTANCE_NAME`_CMP_FF_MASK                  (0xfUL<<`$INSTANCE_NAME`_CMP_FF_SHIFT)

#define `$INSTANCE_NAME`_VALID_SHIFT                  CyUAB_VALID_SHIFT
#define `$INSTANCE_NAME`_VALID_MASK                   (0xfUL<<`$INSTANCE_NAME`_VALID_SHIFT)

#define `$INSTANCE_NAME`_TRIG_OUT_SHIFT               CyUAB_TRIG_OUT_SHIFT
#define `$INSTANCE_NAME`_TRIG_OUT_MASK                (0xfUL<<`$INSTANCE_NAME`_TRIG_OUT_SHIFT)

#define `$INSTANCE_NAME`_STROBE_SW_SHIFT              CyUAB_STROBE_SW_SHIFT
#define `$INSTANCE_NAME`_STROBE_SW_MASK               (0xfUL<<`$INSTANCE_NAME`_STROBE_SW_SHIFT)

#define `$INSTANCE_NAME`_STROBE_RST_SHIFT             CyUAB_STROBE_RST_SHIFT
#define `$INSTANCE_NAME`_STROBE_RST_MASK              (0xfUL<<`$INSTANCE_NAME`_STROBE_RST_SHIFT)


/*SW_BOOST_CTRL*/
#define `$INSTANCE_NAME`_CA_BOOST_SHIFT               CyUAB_CA_BOOST_SHIFT
#define `$INSTANCE_NAME`_CA_BOOST_MASK                (0xfUL<<`$INSTANCE_NAME`_CA_BOOST_SHIFT)

#define `$INSTANCE_NAME`_CB_BOOST_SHIFT               CyUAB_CB_BOOST_SHIFT
#define `$INSTANCE_NAME`_CB_BOOST_MASK                (0xfUL<<`$INSTANCE_NAME`_CB_BOOST_SHIFT)

#define `$INSTANCE_NAME`_CC_BOOST_SHIFT               CyUAB_CC_BOOST_SHIFT
#define `$INSTANCE_NAME`_CC_BOOST_MASK                (0xfUL<<`$INSTANCE_NAME`_CC_BOOST_SHIFT)

#define `$INSTANCE_NAME`_CF_BOOST_SHIFT               CyUAB_CF_BOOST_SHIFT
#define `$INSTANCE_NAME`_CF_BOOST_MASK                (0xfUL<<`$INSTANCE_NAME`_CF_BOOST_SHIFT)

#define `$INSTANCE_NAME`_SUM_BOOST_SHIFT              CyUAB_SUM_BOOST_SHIFT
#define `$INSTANCE_NAME`_SUM_BOOST_MASK               (0xfUL<<`$INSTANCE_NAME`_SUM_BOOST_SHIFT)

#define `$INSTANCE_NAME`_PUMP_WAVE_SHIFT              CyUAB_PUMP_WAVE_SHIFT
#define `$INSTANCE_NAME`_PUMP_WAVE_MASK               (0xfUL<<`$INSTANCE_NAME`_PUMP_WAVE_SHIFT)


/*SRAM_CTRL*/
#define `$INSTANCE_NAME`_LAST_STEP_SHIFT              CyUAB_LAST_STEP_SHIFT
#define `$INSTANCE_NAME`_LAST_STEP_MASK               (0xfUL<<`$INSTANCE_NAME`_LAST_STEP_SHIFT)

#define `$INSTANCE_NAME`_TRIG_SEL_SHIFT               CyUAB_TRIG_SEL_SHIFT
#define `$INSTANCE_NAME`_TRIG_SEL_MASK                (0x1fUL<<`$INSTANCE_NAME`_TRIG_SEL_SHIFT)

#define `$INSTANCE_NAME`_TRIGGER_EN_SHIFT             CyUAB_TRIGGER_EN_SHIFT
#define `$INSTANCE_NAME`_TRIGGER_EN_MASK              (1UL<<`$INSTANCE_NAME`_TRIGGER_EN_SHIFT)

#define `$INSTANCE_NAME`_RUN_SHIFT                    CyUAB_RUN_SHIFT
#define `$INSTANCE_NAME`_RUN_MASK                     (1UL<<`$INSTANCE_NAME`_RUN_SHIFT)


/*STAT*/
#define `$INSTANCE_NAME`_CURR_STEP_SHIFT              CyUAB_CURR_STEP_SHIFT
#define `$INSTANCE_NAME`_CURR_STEP_MASK               (0xfUL<<`$INSTANCE_NAME`_CURR_STEP_SHIFT)

#define `$INSTANCE_NAME`_COMP_SHIFT                   CyUAB_COMP_SHIFT
#define `$INSTANCE_NAME`_COMP_MASK                    (1UL<<`$INSTANCE_NAME`_COMP_SHIFT)

#define `$INSTANCE_NAME`_CURR_SUBSAMPLE_SHIFT         CyUAB_CURR_SUBSAMPLE_SHIFT
#define `$INSTANCE_NAME`_CURR_SUBSAMPLE_MASK          (0xffUL<<`$INSTANCE_NAME`_CURR_SUBSAMPLE_SHIFT)


/*SRAM*/
#define `$INSTANCE_NAME`_WAVE_STEP_SHIFT              CyUAB_WAVE_STEP_SHIFT
#define `$INSTANCE_NAME`_WAVE_STEP_MASK               (0x0000ffffUL)


/*CAP_TRIM*/
#define `$INSTANCE_NAME`_CBTC_VAL_SHIFT               CyUAB_CBTC_VAL_SHIFT
#define `$INSTANCE_NAME`_CBTC_VAL_MASK                (0x7UL<<`$INSTANCE_NAME`_CBTC_VAL_SHIFT)

#define `$INSTANCE_NAME`_CCTC_VAL_SHIFT               CyUAB_CCTC_VAL_SHIFT
#define `$INSTANCE_NAME`_CCTC_VAL_MASK                (0x7UL<<`$INSTANCE_NAME`_CCTC_VAL_SHIFT)


/*OA_TRIM*/
#define `$INSTANCE_NAME`_OA_OFFSET_SHIFT              CyUAB_OA_OFFSET_SHIFT
#define `$INSTANCE_NAME`_OA_OFFSET_MASK               (0xfUL<<`$INSTANCE_NAME`_OA_OFFSET_SHIFT)

#define `$INSTANCE_NAME`_REF_OFFSET_SHIFT             CyUAB_REF_OFFSET_SHIFT
#define `$INSTANCE_NAME`_REF_OFFSET_MASK              (0x1fUL<<`$INSTANCE_NAME`_REF_OFFSET_SHIFT)

#define `$INSTANCE_NAME`_AGND_OFFSET_SHIFT            CyUAB_AGND_OFFSET_SHIFT
#define `$INSTANCE_NAME`_AGND_OFFSET_MASK             (0x1fUL<<`$INSTANCE_NAME`_AGND_OFFSET_SHIFT)



#define `$INSTANCE_NAME`_DAC_NEXT_MASK (CyUAB_DAC_NEXT_MASK)


#endif
