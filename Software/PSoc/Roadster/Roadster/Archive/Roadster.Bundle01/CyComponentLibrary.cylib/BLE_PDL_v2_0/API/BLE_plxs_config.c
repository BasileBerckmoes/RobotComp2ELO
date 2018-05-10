/***************************************************************************//**
* \file CY_BLE_plxs_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Pulse Oximeter Service of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_plxs.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_PLXS))

#ifdef CY_BLE_PLXS_SERVER
`$PlxsServer`
#endif /* CY_BLE_PLXS_SERVER */
 
/**
* \addtogroup group_globals
* @{
*/
 
/** The configuration structure for the Pulse Oximeter Service. */
cy_stc_ble_plxs_config_t cy_ble_plxsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_PLXS_SERVER
    .plxss = &cy_ble_plxss,
    #else
    .plxss = NULL,
    #endif /* CY_BLE_PLXS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_PLXS)) */

/* [] END OF FILE */
