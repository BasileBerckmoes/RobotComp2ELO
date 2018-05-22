/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the DieTemp_P4
*  component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DIE_TEMP_`$INSTANCE_NAME`_H)
#define CY_DIE_TEMP_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "cydevice_trm.h"


/***************************************
*        API constants
***************************************/

#define `$INSTANCE_NAME`_SAR_TEMP_MULTIPLIER_REG    (*(reg16 *) CYREG_SFLASH_SAR_TEMP_MULTIPLIER)
#define `$INSTANCE_NAME`_SAR_TEMP_MULTIPLIER_PTR    ( (reg16 *) CYREG_SFLASH_SAR_TEMP_MULTIPLIER)
#define `$INSTANCE_NAME`_SAR_TEMP_OFFSET_REG        (*(reg16 *) CYREG_SFLASH_SAR_TEMP_OFFSET)
#define `$INSTANCE_NAME`_SAR_TEMP_OFFSET_PTR        ( (reg16 *) CYREG_SFLASH_SAR_TEMP_OFFSET)

#define `$INSTANCE_NAME`_SAR_TEMP_OFFSET_SHIFT      (10u)
#define `$INSTANCE_NAME`_SAR_TEMP_OFFSET_MULT       (0x400)
#define `$INSTANCE_NAME`_SAR_TEMP_OFFSET_DIVIDER    (0x10000)
#define `$INSTANCE_NAME`_SAR_TEMP_SHIFT             (16u)
#define `$INSTANCE_NAME`_SAR_TEMP_DIVIDER           (0x10000)
#define `$INSTANCE_NAME`_SCALE_ADJUSTMENT_DIVIDER   (16u)
#define `$INSTANCE_NAME`_HALF_OF_ONE                ((int32)1u << (`$INSTANCE_NAME`_SAR_TEMP_SHIFT - 1u))

/* (effectively 0.5 << 4u) 0.5 in Q28.4 format */
#define `$INSTANCE_NAME`_SCALE_ADJUSTMENT           (8)
/* 15 in Q16.16 format */
#define `$INSTANCE_NAME`_DUAL_SLOPE_CORRECTION      (0xF0000)
/* 100 in Q16.16 format */
#define `$INSTANCE_NAME`_HIGH_TEMPERATURE           (0x640000)
/* 40 in Q16.16 format */
#define `$INSTANCE_NAME`_LOW_TEMPERATURE            (0x280000)


/***************************************
*        Function Prototypes
***************************************/

int32 `$INSTANCE_NAME`_CountsTo_Celsius(int32 adcCounts);


#endif /* CY_DIE_TEMP_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
