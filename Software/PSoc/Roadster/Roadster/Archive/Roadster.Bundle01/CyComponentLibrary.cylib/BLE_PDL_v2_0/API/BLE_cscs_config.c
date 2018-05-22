/***************************************************************************//**
* \file CY_BLE_cscs_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Cycling Speed and Cadence Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_cscs.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_CSCS))

#ifdef CY_BLE_CSCS_SERVER

`$CscsServer`
#endif /* CY_BLE_CSCS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Cycling Speed and Cadence Service. */
cy_stc_ble_cscs_config_t cy_ble_cscsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_CSCS_SERVER
    .cscss = &cy_ble_cscss,
    #else
    .cscss = NULL,
    #endif /* CY_BLE_CSCS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_CSCS)) */

/* [] END OF FILE */
