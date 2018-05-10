/***************************************************************************//**
* \file CY_BLE_wpts_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Wireless Power Transfer Service.
* 
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_wpts.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_WPTS))

#ifdef CY_BLE_WPTS_SERVER
/* Generated code */
`$WptsServer`
/* End of generated code */
#endif /* CY_BLE_WPTS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Wireless Power Transfer Service. */
cy_stc_ble_wpts_config_t cy_ble_wptsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_WPTS_SERVER
    .wptss = &cy_ble_wptss,
    #else
    .wptss = NULL,
    #endif /* CY_BLE_WPTS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_WPTS)) */

/* [] END OF FILE */
