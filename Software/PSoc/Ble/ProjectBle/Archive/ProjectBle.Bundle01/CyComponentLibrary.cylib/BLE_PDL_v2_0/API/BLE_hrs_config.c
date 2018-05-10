/***************************************************************************//**
* \file CY_BLE_hrs_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Heart Rate Service of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ble/cy_ble_hrs.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_HRS))

#ifdef CY_BLE_HRS_SERVER
`$HrsServer`
#endif /* CY_BLE_HRS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Heart Rate Service. */
cy_stc_ble_hrs_config_t cy_ble_hrsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_HRS_SERVER
    .hrss = &cy_ble_hrss,
    #else
    .hrss = NULL,
    #endif /* CY_BLE_HRS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_HRS)) */

/* [] END OF FILE */
