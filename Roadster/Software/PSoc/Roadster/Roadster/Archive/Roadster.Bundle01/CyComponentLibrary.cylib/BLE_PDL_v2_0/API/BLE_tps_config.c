/***************************************************************************//**
* \file CY_BLE_tps_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Tx Power Service of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_tps.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_TPS))

#ifdef CY_BLE_TPS_SERVER
`$TpsServer`
#endif /* CY_BLE_TPS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Tx Power Service. */
cy_stc_ble_tps_config_t cy_ble_tpsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_TPS_SERVER
    .tpss = &cy_ble_tpss,
    #else
    .tpss = NULL,
    #endif /* CY_BLE_TPS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_TPS)) */

/* [] END OF FILE */
