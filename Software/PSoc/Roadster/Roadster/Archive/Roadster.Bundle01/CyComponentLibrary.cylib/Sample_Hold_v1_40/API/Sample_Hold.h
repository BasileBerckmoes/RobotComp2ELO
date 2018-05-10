/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the SAMPLE/TRACK AND HOLD component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SAMPLE_HOLD_`$INSTANCE_NAME`_H) 
#define CY_SAMPLE_HOLD_`$INSTANCE_NAME`_H 

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


#if(!CY_PSOC5A)
    #if(CYDEV_VARIABLE_VDDA == 1)
        #if (!defined(CY_LIB_SC_BST_CLK_EN))
            #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.30 or later
        #endif /* (!defined(CY_LIB_SC_BST_CLK_EN)) */
    #endif /* CYDEV_VARIABLE_VDDA == 1 */
#endif /* (!CY_PSOC5A) */

/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
    uint8   scCR0Reg;
    uint8   scCR1Reg;
    uint8   scCR2Reg;
}   `$INSTANCE_NAME`_backupStruct;

/* compinent init state */
extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*        Function Prototypes 
***************************************/
    
void `$INSTANCE_NAME`_Init(void)                `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)              `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Start(void)               `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void)                `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_SetPower(uint8 power)     `=ReentrantKeil($INSTANCE_NAME . "_SetPower")`;
void `$INSTANCE_NAME`_Sleep(void)               `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)              `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_SaveConfig(void)          `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void)       `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;


/***************************************
*            API Constants        
***************************************/

/* Constants for Mixer Type */
#define `$INSTANCE_NAME`_SAMPLEANDHOLD          (0x01u)
#define `$INSTANCE_NAME`_TRACKANDHOLD           (0x02u)

/* Power constants for SetPower function */
#define `$INSTANCE_NAME`_MINPOWER               (0x00u)
#define `$INSTANCE_NAME`_LOWPOWER               (0x01u)
#define `$INSTANCE_NAME`_MEDPOWER               (0x02u)
#define `$INSTANCE_NAME`_HIGHPOWER              (0x03u)

/* Vref constats */
#define `$INSTANCE_NAME`_INTERNAL               (0x01u)
#define `$INSTANCE_NAME`_EXTERNAL               (0x02u)

/* Clock edge constats */
#define `$INSTANCE_NAME`_EDGE_NEGATIVE          (0x01u)
#define `$INSTANCE_NAME`_EDGE_POSITIVENEGATIVE  (0x02u)


/***************************************
*       Initialization Values
***************************************/

#define `$INSTANCE_NAME`_INIT_POWER             (`$Power`u)
#define `$INSTANCE_NAME`_SAMPLE_TRACK_MODE      (`$Sample_Mode`u)
#define `$INSTANCE_NAME`_SAMPLE_CLOCK_EDGE      (`$Sample_Clock_Edge`u)
#define `$INSTANCE_NAME`_VddaVal                (`$Vdda_Value`u)
#define `$INSTANCE_NAME`_VREF_TYPE              (`$Vref_Type`u)


/***************************************
*              Registers        
***************************************/

#define `$INSTANCE_NAME`_CR0_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR0_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR1_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR1_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR2_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_CR2_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_CLK_REG                (* (reg8 *) `$INSTANCE_NAME`_SC__CLK )  /* SC Block clk control */
#define `$INSTANCE_NAME`_CLK_PTR                (  (reg8 *) `$INSTANCE_NAME`_SC__CLK )
#define `$INSTANCE_NAME`_BSTCLK_REG             (* (reg8 *) `$INSTANCE_NAME`_SC__BST )
#define `$INSTANCE_NAME`_BSTCLK_PTR             (  (reg8 *) `$INSTANCE_NAME`_SC__BST )
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG         (* (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )  /* Power manager */
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR         (  (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG        (* (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )  /* Power manager */
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR        (  (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )

/* Pump clock selectin register */
#define `$INSTANCE_NAME`_PUMP_CR1_REG           (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)   
#define `$INSTANCE_NAME`_PUMP_CR1_PTR           (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define `$INSTANCE_NAME`_SC_MISC_REG            (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define `$INSTANCE_NAME`_SC_MISC_PTR            (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* Power manager */
/* Active mode power enable register */
#define `$INSTANCE_NAME`_ACLK_PM_ACT_CFG_REG    (* (reg8 *) `$INSTANCE_NAME`_PM_ACT_CFG ) 
#define `$INSTANCE_NAME`_ACLK_PM_ACT_CFG_PTR    (  (reg8 *) `$INSTANCE_NAME`_PM_ACT_CFG ) 

/* Power manager */
/* Alternative Active mode power enable register */
#define `$INSTANCE_NAME`_ACLK_PM_STBY_CFG_REG   (* (reg8 *) `$INSTANCE_NAME`_PM_STBY_CFG )
#define `$INSTANCE_NAME`_ACLK_PM_STBY_CFG_PTR   (  (reg8 *) `$INSTANCE_NAME`_PM_STBY_CFG ) 

/* PM_ACT_CFG (Active Power Mode CFG Register)mask */ 
#define `$INSTANCE_NAME`_ACT_PWR_EN             `$INSTANCE_NAME`_SC__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register)mask */ 
#define `$INSTANCE_NAME`_STBY_PWR_EN            `$INSTANCE_NAME`_SC__PM_STBY_MSK /* Power enable mask */


/***************************************
*            Register Constants        
***************************************/

/* ANIF.PUMP.CR1 Constants */
#define `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL     (0x80u)

/* SC_MISC constants */
#define `$INSTANCE_NAME`_PUMP_FORCE             (0x20u)
#define `$INSTANCE_NAME`_PUMP_AUTO              (0x10u)
#define `$INSTANCE_NAME`_DIFF_PGA_1_3           (0x02u)
#define `$INSTANCE_NAME`_DIFF_PGA_0_2           (0x01u)

/* CR0 SC/CT Control Register 0 definitions */

/* Bit Field SC_MODE_ENUM - SCxx_CR0[3:1] */
#define `$INSTANCE_NAME`_MODE_SAMPLEANDHOLD     ((uint8)(0x03u << 1u))
#define `$INSTANCE_NAME`_MODE_TRACKANDHOLD      ((uint8)(0x07u << 1u))

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_DRIVE_ENUM - SCxx_CR1[1:0] */
#define `$INSTANCE_NAME`_DRIVE_MASK             (0x03u)
#define `$INSTANCE_NAME`_DRIVE_280UA            (0x00u)
#define `$INSTANCE_NAME`_DRIVE_420UA            (0x01u)
#define `$INSTANCE_NAME`_DRIVE_530UA            (0x02u)
#define `$INSTANCE_NAME`_DRIVE_650UA            (0x03u)

/* Bit Field  SC_COMP_ENUM - SCxx_CR1[3:2] */
#define `$INSTANCE_NAME`_COMP_MASK              ((uint8)(0x03u << 2u))
#define `$INSTANCE_NAME`_COMP_3P0PF             ((uint8)(0x00u << 2u))
#define `$INSTANCE_NAME`_COMP_3P6PF             ((uint8)(0x01u << 2u))
#define `$INSTANCE_NAME`_COMP_4P35PF            ((uint8)(0x02u << 2u))
#define `$INSTANCE_NAME`_COMP_5P1PF             ((uint8)(0x03u << 2u))

/* Bit Field  SC_DIV2_ENUM - SCxx_CR1[4] */
#define `$INSTANCE_NAME`_DIV2                   ((uint8)(0x01u << 4u))
#define `$INSTANCE_NAME`_DIV2_DISABLE           ((uint8)(0x00u << 4u))
#define `$INSTANCE_NAME`_DIV2_ENABLE            ((uint8)(0x01u << 4u))

/* Bit Field  SC_GAIN_ENUM - SCxx_CR1[5] */
#define `$INSTANCE_NAME`_GAIN                   ((uint8)(0x01u << 5u))
#define `$INSTANCE_NAME`_GAIN_0DB               ((uint8)(0x00u << 5u))
#define `$INSTANCE_NAME`_GAIN_6DB               ((uint8)(0x01u << 5u))

/* CR2 SC Block Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM - SCxx_CR2[0] */
#define `$INSTANCE_NAME`_BIAS                   (0x01u)
#define `$INSTANCE_NAME`_BIAS_NORMAL            (0x00u)
#define `$INSTANCE_NAME`_BIAS_LOW               (0x01u)

/* Bit Field  SC_R20_40B_ENUM - SCxx_CR2[1] */
#define `$INSTANCE_NAME`_R20_40B                ((uint8)(0x01u << 1u))
#define `$INSTANCE_NAME`_R20_40B_40K            ((uint8)(0x00u << 1u))
#define `$INSTANCE_NAME`_R20_40B_20K            ((uint8)(0x01u << 1u))

/* Bit Field  SC_REDC_ENUM  - SCxx_CR2[3:2] */
#define `$INSTANCE_NAME`_REDC_MASK              ((uint8)(0x03u << 2u))
#define `$INSTANCE_NAME`_REDC_00                ((uint8)(0x00u << 2u))
#define `$INSTANCE_NAME`_REDC_01                ((uint8)(0x01u << 2u))
#define `$INSTANCE_NAME`_REDC_10                ((uint8)(0x02u << 2u))
#define `$INSTANCE_NAME`_REDC_11                ((uint8)(0x03u << 2u))

/* Bit Field  SC_RVAL_ENUM  - SCxx_CR2[6:4] */
#define `$INSTANCE_NAME`_RVAL_MASK              ((uint8)(0x07u << 4u))
#define `$INSTANCE_NAME`_RVAL_20K               ((uint8)(0x00u << 4u))
#define `$INSTANCE_NAME`_RVAL_30K               ((uint8)(0x01u << 4u))
#define `$INSTANCE_NAME`_RVAL_40K               ((uint8)(0x02u << 4u))
#define `$INSTANCE_NAME`_RVAL_80K               ((uint8)(0x03u << 4u))
#define `$INSTANCE_NAME`_RVAL_120K              ((uint8)(0x04u << 4u))
#define `$INSTANCE_NAME`_RVAL_250K              ((uint8)(0x05u << 4u))
#define `$INSTANCE_NAME`_RVAL_500K              ((uint8)(0x06u << 4u))
#define `$INSTANCE_NAME`_RVAL_1000K             ((uint8)(0x07u << 4u))

/* Bit Field  SC_PGA_GNDVREF_ENUM - SCxx_CR2[7] */
#define `$INSTANCE_NAME`_GNDVREF                ((uint8)(0x01u << 7u))
#define `$INSTANCE_NAME`_GNDVREF_DI             ((uint8)(0x00u << 7u))
#define `$INSTANCE_NAME`_GNDVREF_E              ((uint8)(0x01u << 7u)) 

/* SC Block Clock Control SCx.CLk */
#define `$INSTANCE_NAME`_DYN_CNTL_EN            ((uint8)(0x01u << 5u))
#define `$INSTANCE_NAME`_BYPASS_SYNC            ((uint8)(0x01u << 4u))
#define `$INSTANCE_NAME`_CLK_EN                 ((uint8)(0x01u << 3u))

/* SC Block Boost Clock Selection Register - Boost Clock Enable  SCxx_BST[3]  */
#define `$INSTANCE_NAME`_BST_CLK_EN             ((uint8)(0x01u << 3u))
#define `$INSTANCE_NAME`_BST_CLK_INDEX_MASK     (0x07u)
#define `$INSTANCE_NAME`_PM_ACT_CFG_MASK        (0x0Fu)

/* Constant for VDDA Threshold */
#define `$INSTANCE_NAME`_CYDEV_VDDA_MV               (CYDEV_VDDA_MV)
#define `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV   (2700u)


/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from SampleHold 1.40
*******************************************************************************/
/* Component's enable/disable state */
#define `$INSTANCE_NAME`_ENABLED             (0x01u)
#define `$INSTANCE_NAME`_DISABLED            (0x00u)
#define `$INSTANCE_NAME`_VDDA_THRESHOLD_MV   (3500u)
#if (CY_PSOC5A)
    /* For stop API changes mask to make the SC registers CR1 and CR2 null  */
    #define `$INSTANCE_NAME`_REG_NULL        (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_SAMPLE_HOLD_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
