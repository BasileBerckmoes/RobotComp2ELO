/***************************************************************************//**
* \file CY_BLE_ans_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Alert Notification Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_ans.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_ANS))

#ifdef CY_BLE_ANS_SERVER

`$AnsServer`
#endif /* CY_BLE_ANS_SERVER */

/**
* \addtogroup group_globals
* @{
*/

/** The configuration structure for the Alert Notification Service. */
cy_stc_ble_ans_config_t cy_ble_ansConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_ANS_SERVER
    .anss = &cy_ble_anss,
    #else
    .anss = NULL,
    #endif /* CY_BLE_ANS_SERVER */

    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};

/** @} group_globals */

#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_ANS)) */

/* [] END OF FILE */
