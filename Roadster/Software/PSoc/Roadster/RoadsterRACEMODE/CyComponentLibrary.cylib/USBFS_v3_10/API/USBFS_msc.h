/***************************************************************************//**
* \file `$INSTANCE_NAME`_msc.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  MSC class support.
*
* Related Document:
*  Device Class Definition for Mass Storage (MSC) Version TDB
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_`$INSTANCE_NAME`_msc_H)
#define CY_USBFS_`$INSTANCE_NAME`_msc_H

#include "`$INSTANCE_NAME`.h"

/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_HANDLE_MSC_REQUESTS    (0u != (`$HandleMscRequests`u))
#define `$INSTANCE_NAME`_MSC_LUN_NUMBER         (`$MscLogicalUnitsNum`u - 1u)


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_msc
* @{
*/
#if (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS)
    void  `$INSTANCE_NAME`_MSC_SetLunCount(uint8 lunCount) `=ReentrantKeil($INSTANCE_NAME . "_MSC_SetLunCount")`;
    uint8 `$INSTANCE_NAME`_MSC_GetLunCount(void)           `=ReentrantKeil($INSTANCE_NAME . "_MSC_GetLunCount")`;
#endif /* (`$INSTANCE_NAME`_HANDLE_MSC_REQUESTS) */
/** @} msc */

/***************************************
*              Constants
***************************************/

/* MSC Class-Specific requests */
#define `$INSTANCE_NAME`_MSC_RESET          (0xFFu)
#define `$INSTANCE_NAME`_MSC_GET_MAX_LUN    (0xFEu)

/* MSC Class-Specific requests constant fields. */
#define `$INSTANCE_NAME`_MSC_RESET_WVALUE           (0u)
#define `$INSTANCE_NAME`_MSC_RESET_WLENGTH          (0u)

#define `$INSTANCE_NAME`_MSC_GET_MAX_LUN_WVALUE     (0u)
#define `$INSTANCE_NAME`_MSC_GET_MAX_LUN_WLENGTH    (1u)

#endif /*  CY_USBFS_`$INSTANCE_NAME`_msc_H */


/* [] END OF FILE */
