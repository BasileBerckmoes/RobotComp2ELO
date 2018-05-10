/***************************************************************************//**
* \file CY_BLE_pass_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure for
*  the Phone Alert Status Profile of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_pass.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_PASS))

#ifdef CY_BLE_PASS_SERVER
`$PassServer`
#endif /* CY_BLE_PASS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Phone Alert Status Service. */
cy_stc_ble_pass_config_t cy_ble_passConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_PASS_SERVER
    .passs = &cy_ble_passs,
    #else
    .passs = NULL,
    #endif /* CY_BLE_PASS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_PASS)) */

/* [] END OF FILE */
