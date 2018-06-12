/***************************************************************************//**
* \file CY_BLE_uds_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the User Data Service of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ble/cy_ble_uds.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_UDS))

#ifdef CY_BLE_UDS_SERVER
/* Generated code */
`$UdsServer`
/* End of generated code */
#endif /* CYBCY_BLE_UDS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the User Data Service. */
cy_stc_ble_uds_config_t cy_ble_udsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_UDS_SERVER
    .udss = &cy_ble_udss,
    #else
    .udss = NULL,
    #endif /* CY_BLE_UDS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_UDS)) */
    
/* [] END OF FILE */
