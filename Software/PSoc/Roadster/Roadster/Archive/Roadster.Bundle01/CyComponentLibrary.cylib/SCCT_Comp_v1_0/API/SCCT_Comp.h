/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the SCCT Comparator
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCCT_COMP_`$INSTANCE_NAME`_H)
#define CY_SCCT_COMP_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*       Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
}   `$INSTANCE_NAME`_BACKUP_STRUCT;


/* Variable describes init state of the `$INSTANCE_NAME` */
extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_POLARITY                 (`$Polarity`u)
#define `$INSTANCE_NAME`_SYNC                     (`$Sync`u)


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void)                 `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void)                  `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_Init(void)                  `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)                `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Sleep(void)                 `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)                `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;


/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_CR0_REG                  (* (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR0_PTR                  (  (reg8 *) `$INSTANCE_NAME`_SC__CR0 )
#define `$INSTANCE_NAME`_CR1_REG                  (* (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR1_PTR                  (  (reg8 *) `$INSTANCE_NAME`_SC__CR1 )
#define `$INSTANCE_NAME`_CR2_REG                  (* (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_CR2_PTR                  (  (reg8 *) `$INSTANCE_NAME`_SC__CR2 )
#define `$INSTANCE_NAME`_SC_CLK_REG               (* (reg8 *) `$INSTANCE_NAME`_SC__CLK )
#define `$INSTANCE_NAME`_SC_CLK_PTR               (  (reg8 *) `$INSTANCE_NAME`_SC__CLK )

/* Power manager */
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG           (* (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR           (  (reg8 *) `$INSTANCE_NAME`_SC__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG          (* (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR          (  (reg8 *) `$INSTANCE_NAME`_SC__PM_STBY_CFG )
#define `$INSTANCE_NAME`_BSTCLK_REG               (* (reg8 *) `$INSTANCE_NAME`_SC__BST )
#define `$INSTANCE_NAME`_BSTCLK_PTR               (  (reg8 *) `$INSTANCE_NAME`_SC__BST )

/* Pump clock selection register */
#define `$INSTANCE_NAME`_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1 )
#define `$INSTANCE_NAME`_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1 )

/* Pump Register for SC block */
#define `$INSTANCE_NAME`_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define `$INSTANCE_NAME`_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */
#define `$INSTANCE_NAME`_ACT_PWR_EN               (`$INSTANCE_NAME`_SC__PM_ACT_MSK)

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register) mask */
#define `$INSTANCE_NAME`_STBY_PWR_EN              (`$INSTANCE_NAME`_SC__PM_STBY_MSK)


/***************************************
*        Register Constants
***************************************/

/* CR0 SC/CT Control Register 0 definitions */
#define `$INSTANCE_NAME`_MODE_COMPARATOR          (0x20u)

/* CR2 SC/CT Control Register 2 definitions */
#define `$INSTANCE_NAME`_BIAS                     (0x01u)

/* ANIF.PUMP.CR1 Constants */
#define `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL       (0x80u)

/* ANIF.PUMP.CR1 Constants */
#define `$INSTANCE_NAME`_CLK_EN                   (0x08u)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */
#define `$INSTANCE_NAME`_PM_ACT_CFG_MASK          (0x0Fu)

/* SC_BST Boost Clock Selection Register Constants */
#define `$INSTANCE_NAME`_BST_CLK_EN               (0x08u)
#define `$INSTANCE_NAME`_BST_CLK_INDEX_MASK       (0x07u)

/* SC_MISC Control Register Constants */
#define `$INSTANCE_NAME`_PUMP_FORCE               (0x20u)

#endif /* CY_SCCT_COMP_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
