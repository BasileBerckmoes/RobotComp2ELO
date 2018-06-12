/***************************************************************************//**
* \file BLE_aios_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Automation Input Output Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_aios.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_AIOS))

#ifdef CY_BLE_AIOS_SERVER
`$AiosServer`
#endif /* CY_BLE_AIOS_SERVER */

#ifdef CY_BLE_AIOS_CLIENT
`$AiosClient`
#endif /* CY_BLE_AIOS_CLIENT */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Automation Input Output Service. */
cy_stc_ble_aios_config_t cy_ble_aiosConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_AIOS_SERVER
        .aioss = &cy_ble_aioss,
        .aiossCharInstances = cy_ble_aiossCharInstances,
    #else
        .aioss = NULL,
        .aiossCharInstances = NULL,
    #endif /* CY_BLE_AIOS_SERVER */

    #ifdef CY_BLE_AIOS_CLIENT
        .aiosc = cy_ble_aiosc,
        .aioscCharInstances = cy_ble_aioscCharInstances,
    #else
        .aiosc = NULL,
        .aioscCharInstances = NULL,
    #endif /* CY_BLE_AIOS_CLIENT */
    
    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_AIOS)) */

/* [] END OF FILE */
