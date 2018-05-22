/***************************************************************************//**
* \file CY_BLE_ess_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Environmental Sensing Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_ess.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_ESS))

#ifdef CY_BLE_ESS_SERVER
`$EssServer`
#endif /* CY_BLE_ESS_SERVER */

#ifdef CY_BLE_ESS_CLIENT
`$EssClient`
#endif /* CY_BLE_ESS_CLIENT */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Environmental Sensing Service. */
cy_stc_ble_ess_config_t cy_ble_essConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_ESS_SERVER
        .esss = &cy_ble_esss,
        .esssCharInstances = cy_ble_esssCharInstances,
    #else
        .esss = NULL,
        .esssCharInstances = NULL,
    #endif /* CY_BLE_ESS_SERVER */

    #ifdef CY_BLE_ESS_CLIENT
        .essc = cy_ble_essc,
        .esscCharInstances = cy_ble_esscCharInstances,
    #else
        .essc = NULL,
        .esscCharInstances = NULL,
    #endif /* CY_BLE_ESS_CLIENT */
    
    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_ESS)) */

/* [] END OF FILE */
