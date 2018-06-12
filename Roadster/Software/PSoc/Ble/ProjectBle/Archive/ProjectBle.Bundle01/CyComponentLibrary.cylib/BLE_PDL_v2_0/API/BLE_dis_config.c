/***************************************************************************//**
* \file CY_BLE_dis_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Device Information Service
* 
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_dis.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_DIS))

#ifdef CY_BLE_DIS_SERVER
`$DisServer`
#endif /* CY_BLE_DIS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Device Information Service. */
cy_stc_ble_dis_config_t cy_ble_disConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_DIS_SERVER
    .diss = &cy_ble_diss,
    #else
    .diss = NULL,
    #endif /* CY_BLE_DIS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_DIS)) */

/* [] END OF FILE */
