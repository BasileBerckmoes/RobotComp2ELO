/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the EZI2C
*  component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EZI2C_PVT_`$INSTANCE_NAME`_H)
#define CY_EZI2C_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*     Vars with External Linkage
***************************************/

extern `$INSTANCE_NAME`_BACKUP_STRUCT  `$INSTANCE_NAME`_backup;

/* Status and state variables */
extern volatile uint8 `$INSTANCE_NAME`_curStatus;
extern volatile uint8 `$INSTANCE_NAME`_curState;

/* Primary slave address variables */
extern volatile uint8* `$INSTANCE_NAME`_dataPtrS1;
extern volatile uint16 `$INSTANCE_NAME`_bufSizeS1;
extern volatile uint16 `$INSTANCE_NAME`_wrProtectS1;
extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwOffsetS1;
extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwIndexS1;

/* Secondary slave address variables */
#if (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)
    extern volatile uint8  `$INSTANCE_NAME`_addrS1;
    extern volatile uint8  `$INSTANCE_NAME`_addrS2;
    extern volatile uint8* `$INSTANCE_NAME`_dataPtrS2;
    extern volatile uint16 `$INSTANCE_NAME`_bufSizeS2;
    extern volatile uint16 `$INSTANCE_NAME`_wrProtectS2;
    extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwOffsetS2;
    extern volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwIndexS2;
#endif  /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */

#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    extern volatile uint8 `$INSTANCE_NAME`_wakeupSource;
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */

#endif /* CY_EZI2C_PVT_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
