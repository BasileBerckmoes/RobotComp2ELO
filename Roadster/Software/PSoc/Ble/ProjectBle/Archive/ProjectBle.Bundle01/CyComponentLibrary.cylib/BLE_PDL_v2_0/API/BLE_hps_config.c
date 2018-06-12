/***************************************************************************//**
* \file CY_BLE_hps_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure 
*  for HTTP Proxy Service.
* 
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ble/cy_ble_hps.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_HPS))

#ifdef CY_BLE_HPS_SERVER

`$HpsServer`
#endif /* CY_BLE_HPS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the HTTP Proxy Service. */
cy_stc_ble_hps_config_t cy_ble_hpsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_HPS_SERVER
    .hpss = &cy_ble_hpss,
    #else
    .hpss = NULL,
    #endif /* CY_BLE_HPS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_HPS)) */

/* [] END OF FILE */
