/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Mixer component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_MIXER_`$INSTANCE_NAME`_H) 
#define CY_MIXER_`$INSTANCE_NAME`_H 

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

/* Fixed configuration of SC Block only performed once */
extern uint8 `$INSTANCE_NAME`_initVar;

/***************************************
*        Function Prototypes 
***************************************/

void `$INSTANCE_NAME`_Start(void)                   `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void)                    `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_SetPower(uint8 power)         `=ReentrantKeil($INSTANCE_NAME . "_SetPower")`;
void `$INSTANCE_NAME`_Sleep(void)                   `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)                  `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_SaveConfig(void)              `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void)           `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Init(void)                    `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)                  `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;


/***************************************
*              Constants        
***************************************/

/* Constants for Mixer Type */
#define `$INSTANCE_NAME`_CTMIXER                    (0x00u)
#define `$INSTANCE_NAME`_DTMIXER                    (0x01u)

/* Constants for Local Oscillator Freq */
#define `$INSTANCE_NAME`_LO_CLOCK_FREQ_100_KHz      (100u)
#define `$INSTANCE_NAME`_UNKNOWN_EXTERNAL_LO        (-1)

/* Constants for SetPower function */
#define `$INSTANCE_NAME`_MINPOWER                   (0x00u)
#define `$INSTANCE_NAME`_LOWPOWER                   (0x01u)
#define `$INSTANCE_NAME`_MEDPOWER                   (0x02u)
#define `$INSTANCE_NAME`_HIGHPOWER                  (0x03u)

/* Constants for LO Source */
#define `$INSTANCE_NAME`_LO_SOURCE_INTERNAL         (0x00u)
#define `$INSTANCE_NAME`_LO_SOURCE_EXTERNAL         (0x01u)


/***************************************
*       Initial Paramater Values
***************************************/

#define `$INSTANCE_NAME`_MIXER_TYPE                 (`$Mixer_Type`u)
#define `$INSTANCE_NAME`_INIT_POWER                 (`$Power`u)
#define `$INSTANCE_NAME`_LO_SOURCE                  (`$LO_Source`u)
#define `$INSTANCE_NAME`_EXTERNAL_LO_CLK_FREQ       ((float)`$EXT_LO_CLK_FREQ`)
#define `$INSTANCE_NAME`_VddaVal                    (`$Vdda_Value`u)

#if (`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
    /* Internal LO clock frequency */
    #define `$INSTANCE_NAME`_LO_CLOCK_FREQ          ((float)`$LO_clock_freq`)
#else
    #define `$INSTANCE_NAME`_LO_CLOCK_FREQ          (((float)`$EXT_LO_CLK_FREQ` == \
                                                      `$INSTANCE_NAME`_UNKNOWN_EXTERNAL_LO) ? \
                                                      ((float)`$LO_clock_freq`) : ((float)`$EXT_LO_CLK_FREQ`))
#endif /* `$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL */


/***************************************
*              Registers        
***************************************/

/* SC Block Configuration Registers */
#define `$INSTANCE_NAME`_CR0_REG                    (* (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR0_PTR                    (  (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR1_REG                    (* (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR1_PTR                    (  (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR2_REG                    (* (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_CR2_PTR                    (  (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
/* SC Block clk control */
#define `$INSTANCE_NAME`_CLK_REG                    (* (reg8 *) `$INSTANCE_NAME`_SC__CLK )  
#define `$INSTANCE_NAME`_CLK_PTR                    (  (reg8 *) `$INSTANCE_NAME`_SC__CLK )
/* SC Boost clk Control */
#define `$INSTANCE_NAME`_BSTCLK_REG                 (* (reg8 *) `$INSTANCE_NAME`_SC__BST )  
#define `$INSTANCE_NAME`_BSTCLK_PTR                 (  (reg8 *) `$INSTANCE_NAME`_SC__BST )
/* Power manager */
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG             (* (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )  
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR             (  (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )
/* Power manager */
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG            (* (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )  
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR            (  (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )
/* Pump clock selectin register */
#define `$INSTANCE_NAME`_PUMP_CR1_REG               (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)   
#define `$INSTANCE_NAME`_PUMP_CR1_PTR               (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
/* Pump Register for SC block */
#define `$INSTANCE_NAME`_SC_MISC_REG                (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define `$INSTANCE_NAME`_SC_MISC_PTR                (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
/* Power enable mask */
#define `$INSTANCE_NAME`_ACT_PWR_EN                 `$INSTANCE_NAME`_SC__PM_ACT_MSK 
/* PM_STBY_CFG (Alternative Active Power Mode CFG Register) mask */ 
/* Power enable mask */
#define `$INSTANCE_NAME`_STBY_PWR_EN                `$INSTANCE_NAME`_SC__PM_STBY_MSK 
/* LO oscillator clock register defines */
#if(`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
    #define `$INSTANCE_NAME`_PWRMGR_ACLK_REG        (* (reg8 *) `$INSTANCE_NAME`_aclk__PM_ACT_CFG ) 
    #define `$INSTANCE_NAME`_PWRMGR_ACLK_PTR        (  (reg8 *) `$INSTANCE_NAME`_aclk__PM_ACT_CFG ) 

    #define `$INSTANCE_NAME`_STBY_PWRMGR_ACLK_REG   (* (reg8 *) `$INSTANCE_NAME`_aclk__PM_STBY_CFG )
    #define `$INSTANCE_NAME`_STBY_PWRMGR_ACLK_PTR   (  (reg8 *) `$INSTANCE_NAME`_aclk__PM_STBY_CFG )
#endif /* `$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL */

/* Below defines are to retain backward compatibility. These are depricated 
   and should not be used in future designs */

/* SC Block Configuration Registers */
#define `$INSTANCE_NAME`_CR0                        `$INSTANCE_NAME`_CR0_REG
#define `$INSTANCE_NAME`_CR1                        `$INSTANCE_NAME`_CR1_REG
#define `$INSTANCE_NAME`_CR2                        `$INSTANCE_NAME`_CR2_REG
/* SC Block clk control */
#define `$INSTANCE_NAME`_CLK                        `$INSTANCE_NAME`_CLK_REG     
/* SC Boost clk Control */
#define `$INSTANCE_NAME`_BSTCLK                     `$INSTANCE_NAME`_BSTCLK_REG  
/* Power manager */
#define `$INSTANCE_NAME`_PM_ACT_CFG                 `$INSTANCE_NAME`_PM_ACT_CFG_REG  
/* Power manager */
#define `$INSTANCE_NAME`_PM_STBY_CFG                `$INSTANCE_NAME`_PM_STBY_CFG_REG  
/* Pump clock selectin register */
#define `$INSTANCE_NAME`_PUMP_CR1                   `$INSTANCE_NAME`_PUMP_CR1_REG   
/* Pump Register for SC block */
#define `$INSTANCE_NAME`_SC_MISC                    `$INSTANCE_NAME`_SC_MISC_REG


/***************************************
*        Register Constants        
***************************************/

/* ANIF.PUMP.CR1 Constants */
#define `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL         (0x80u)

/* SC_MISC constants */
#define `$INSTANCE_NAME`_PUMP_FORCE                 (0x20u)
#define `$INSTANCE_NAME`_PUMP_AUTO                  (0x10u)
#define `$INSTANCE_NAME`_DIFF_PGA_1_3               (0x02u)
#define `$INSTANCE_NAME`_DIFF_PGA_0_2               (0x01u)

/* CR0 SC Block Control Register 0 definitions */

/* Bit Field SC_MODE_ENUM - SCxx_CR0[3:1] */
#define `$INSTANCE_NAME`_MODE_CTMIXER               ((uint8)(0x02u << 1))
#define `$INSTANCE_NAME`_MODE_DTMIXER               ((uint8)(0x03u << 1))

/* CR1 SC Block Control Register 1 definitions */

/* Bit Field  SC_DRIVE_ENUM - SCxx_CR1[1:0] */
#define `$INSTANCE_NAME`_DRIVE_MASK                 (0x03u)
#define `$INSTANCE_NAME`_DRIVE_280UA                (0x00u)
#define `$INSTANCE_NAME`_DRIVE_420UA                (0x01u)
#define `$INSTANCE_NAME`_DRIVE_530UA                (0x02u)
#define `$INSTANCE_NAME`_DRIVE_650UA                (0x03u)

/* Bit Field  SC_COMP_ENUM - SCxx_CR1[3:2] */
#define `$INSTANCE_NAME`_COMP_MASK                  ((uint8)(0x03u << 2))
#define `$INSTANCE_NAME`_COMP_3P0PF                 ((uint8)(0x00u << 2))
#define `$INSTANCE_NAME`_COMP_3P6PF                 ((uint8)(0x01u << 2))
#define `$INSTANCE_NAME`_COMP_4P35PF                ((uint8)(0x02u << 2))
#define `$INSTANCE_NAME`_COMP_5P1PF                 ((uint8)(0x03u << 2))

/* Bit Field  SC_DIV2_ENUM - SCxx_CR1[4] */
#define `$INSTANCE_NAME`_DIV2                       ((uint8)(0x01u << 4))
#define `$INSTANCE_NAME`_DIV2_DISABLE               ((uint8)(0x00u << 4))
#define `$INSTANCE_NAME`_DIV2_ENABLE                ((uint8)(0x01u << 4))

/* Bit Field  SC_GAIN_ENUM - SCxx_CR1[5] */
#define `$INSTANCE_NAME`_GAIN                       ((uint8)(0x01u << 5))
#define `$INSTANCE_NAME`_GAIN_0DB                   ((uint8)(0x00u << 5))
#define `$INSTANCE_NAME`_GAIN_6DB                   ((uint8)(0x01u << 5))

/* CR2 SC Block Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM - SCxx_CR2[0] */
#define `$INSTANCE_NAME`_BIAS                       (0x01u)
#define `$INSTANCE_NAME`_BIAS_NORMAL                (0x00u)
#define `$INSTANCE_NAME`_BIAS_LOW                   (0x01u)

/* Bit Field  SC_R20_40B_ENUM - SCxx_CR2[1] */
#define `$INSTANCE_NAME`_R20_40B                    ((uint8)(0x01u << 1))
#define `$INSTANCE_NAME`_R20_40B_40K                ((uint8)(0x00u << 1))
#define `$INSTANCE_NAME`_R20_40B_20K                ((uint8)(0x01u << 1))

/* Bit Field  SC_REDC_ENUM  - SCxx_CR2[3:2] */
#define `$INSTANCE_NAME`_REDC_MASK                  ((uint8)(0x03u << 2))
#define `$INSTANCE_NAME`_REDC_00                    ((uint8)(0x00u << 2))
#define `$INSTANCE_NAME`_REDC_01                    ((uint8)(0x01u << 2))
#define `$INSTANCE_NAME`_REDC_10                    ((uint8)(0x02u << 2))
#define `$INSTANCE_NAME`_REDC_11                    ((uint8)(0x03u << 2))

/* Bit Field  SC_RVAL_ENUM  - SCxx_CR2[6:4] */
#define `$INSTANCE_NAME`_RVAL_MASK                  ((uint8)(0x07u << 4))
#define `$INSTANCE_NAME`_RVAL_20K                   ((uint8)(0x00u << 4))
#define `$INSTANCE_NAME`_RVAL_30K                   ((uint8)(0x01u << 4))
#define `$INSTANCE_NAME`_RVAL_40K                   ((uint8)(0x02u << 4))
#define `$INSTANCE_NAME`_RVAL_80K                   ((uint8)(0x03u << 4))
#define `$INSTANCE_NAME`_RVAL_120K                  ((uint8)(0x04u << 4))
#define `$INSTANCE_NAME`_RVAL_250K                  ((uint8)(0x05u << 4))
#define `$INSTANCE_NAME`_RVAL_500K                  ((uint8)(0x06u << 4))
#define `$INSTANCE_NAME`_RVAL_1000K                 ((uint8)(0x07u << 4))

/* Bit Field  SC_PGA_GNDVREF_ENUM - SCxx_CR2[7] */
#define `$INSTANCE_NAME`_GNDVREF                    ((uint8)(0x01u << 7))
#define `$INSTANCE_NAME`_GNDVREF_DI                 ((uint8)(0x00u << 7))
#define `$INSTANCE_NAME`_GNDVREF_E                  ((uint8)(0x01u << 7)) 

/* SC Block Clock Control SCx.CLk */
#define `$INSTANCE_NAME`_DYN_CNTL_EN                ((uint8)(0x01u << 5))
#define `$INSTANCE_NAME`_BYPASS_SYNC                ((uint8)(0x01u << 4))
#define `$INSTANCE_NAME`_CLK_EN                     ((uint8)(0x01u << 3))

/* SC Block Boost Clock Selection Register - Boost Clock Enable  SCxx_BST[3]  */
#define `$INSTANCE_NAME`_BST_CLK_EN                 ((uint8)(0x01u << 3))
#define `$INSTANCE_NAME`_BST_CLK_INDEX_MASK         (0x07u)
#define `$INSTANCE_NAME`_PM_ACT_CFG_MASK            (0x0Fu)

/* internal LO oscillator Clock enable */
#if(`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
    #define `$INSTANCE_NAME`_ACT_PWR_ACLK_EN        `$INSTANCE_NAME`_aclk__PM_ACT_MSK 
    #define `$INSTANCE_NAME`_STBY_PWR_ACLK_EN       `$INSTANCE_NAME`_aclk__PM_STBY_MSK 
#endif /* `$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL */

/* Constant for VDDA Threshold */
#define `$INSTANCE_NAME`_CYDEV_VDDA_MV              (CYDEV_VDDA_MV)
#define `$INSTANCE_NAME`_MINIMUM_VDDA_THRESHOLD_MV  (2700u)

#endif /* CY_MIXER_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
