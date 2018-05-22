/***************************************************************************//**
* \file CY_BLE_bms_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Bond Management Service of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_bms.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_BMS))

#ifdef CY_BLE_BMS_SERVER
/* Service GATT DB handles structure */
`$BmsServer`
#endif /* CY_BLE_BMS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Bond Management Service. */
cy_stc_ble_bms_config_t cy_ble_bmsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_BMS_SERVER
    .bmss = &cy_ble_bmss,
    #else
    .bmss = NULL,
    #endif /* CY_BLE_BMS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_BMS)) */

/* [] END OF FILE */
