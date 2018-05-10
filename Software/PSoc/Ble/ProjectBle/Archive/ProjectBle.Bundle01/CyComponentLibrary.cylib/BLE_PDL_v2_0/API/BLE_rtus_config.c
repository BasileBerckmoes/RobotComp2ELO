/***************************************************************************//**
* \file CY_BLE_rtus_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Reference Time Update Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_rtus.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_RTUS))

#if defined(CY_BLE_RTUS_SERVER)

`$RtusServer`
    
#endif /* CY_BLE_RTUS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Reference Time Update Service. */
cy_stc_ble_rtus_config_t cy_ble_rtusConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_RTUS_SERVER
    .rtuss = &cy_ble_rtuss,
    #else
    .rtuss = NULL,
    #endif /* CY_BLE_RTUS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_RTUS)) */

/* [] END OF FILE */
