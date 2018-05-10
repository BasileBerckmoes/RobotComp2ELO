/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PVT.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains internal definitions for the `$INSTANCE_NAME`
*  component. It must be included after `$INSTANCE_NAME`.h.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TMP05INTF_`$INSTANCE_NAME`_PVT_H)
#define CY_TMP05INTF_`$INSTANCE_NAME`_PVT_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_EOC_ISR.h"


/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */

#if !defined (CY_PSOC5A)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5A) */


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/*******************************************************************************
* Internal variables
*******************************************************************************/
extern volatile uint16 `$INSTANCE_NAME`_lo[`$INSTANCE_NAME`_CUSTOM_NUM_SENSORS];
extern volatile uint16 `$INSTANCE_NAME`_hi[`$INSTANCE_NAME`_CUSTOM_NUM_SENSORS];
extern volatile uint8  `$INSTANCE_NAME`_contMode;


/*******************************************************************************
* Internal register contents
*******************************************************************************/

/* Status Reg defines */
#define `$INSTANCE_NAME`_STATUS_EOC                 (0x01u)
#define `$INSTANCE_NAME`_STATUS_ERR                 (0x02u)
#define `$INSTANCE_NAME`_STATUS_CLR_MASK            (0x03u)

/* Control Reg Enable */
#define `$INSTANCE_NAME`_CTRL_TRIG                  (0x01u)

/* Control Reg EOC */
#define `$INSTANCE_NAME`_CTRL_EOC                   (0x8u)

/* Control Reg EOC */
#define `$INSTANCE_NAME`_CTRL_EOC_TRIG              (`$INSTANCE_NAME`_CTRL_TRIG | `$INSTANCE_NAME`_CTRL_EOC)

/* Control Reg Sensors Mask */
#define `$INSTANCE_NAME`_CTRL_NUM_SNS_MASK          ((uint8)(~0x6u))

/* Component Enable */
#define `$INSTANCE_NAME`_CTRL_REG_ENABLE            (0x80u)

/* Component Disable */
#define `$INSTANCE_NAME`_CTRL_REG_DISABLE           ((uint8)(~`$INSTANCE_NAME`_COMP_CTRL_REG_ENABLE))

/* Control Reg sensor position */
#define `$INSTANCE_NAME`_CTRL_REG_SNS_SHIFT         (0x01u)

/* FIFO clear define */
#define `$INSTANCE_NAME`_FIFO_CLEAR_MASK            (0x0303u)


/*******************************************************************************
* Internal constants
*******************************************************************************/
#define `$INSTANCE_NAME`_SCALED_CONST_TMP1          ((int32)42100)
#define `$INSTANCE_NAME`_SCALED_CONST_TMP2          ((int32)75100)


/******************************************
* Buried Interrupt Support
******************************************/
CY_ISR_PROTO(`$INSTANCE_NAME`_EOC_ISR_Int);

#endif /* End CY_`$INSTANCE_NAME`_PVT_H */


/* [] END OF FILE */
