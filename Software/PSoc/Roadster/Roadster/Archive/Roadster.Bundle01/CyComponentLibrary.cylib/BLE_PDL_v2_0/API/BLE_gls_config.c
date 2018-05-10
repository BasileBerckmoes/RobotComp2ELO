/***************************************************************************//**
* \file CY_BLE_gls_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Glucose Service of the BLE Component.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_gls.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_GLS))

#ifdef CY_BLE_GLS_SERVER
`$GlsServer`
#endif /* CY_BLE_GLS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Glucose Service. */
cy_stc_ble_gls_config_t cy_ble_glsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_GLS_SERVER
    .glss = &cy_ble_glss,
    #else
    .glss = NULL,
    #endif /* CY_BLE_GLS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_GLS)) */

/* [] END OF FILE */
