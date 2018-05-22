/***************************************************************************//**
* \file CY_BLE_wss_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure the
*  for Weight Scale Service.
* 
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_wss.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_WSS))

#ifdef CY_BLE_WSS_SERVER
/* Generated code */
`$WssServer`
/* End of generated code */
#endif /* CY_BLE_WSS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Weight Scale Service. */
cy_stc_ble_wss_config_t cy_ble_wssConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_WSS_SERVER
    .wsss = &cy_ble_wsss,
    #else
    .wsss = NULL,
    #endif /* CY_BLE_WSS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_WSS)) */

/* [] END OF FILE */
