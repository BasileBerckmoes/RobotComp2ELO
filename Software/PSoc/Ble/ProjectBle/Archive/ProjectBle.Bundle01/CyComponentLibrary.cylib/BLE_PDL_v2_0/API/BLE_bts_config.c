/***************************************************************************//**
* \file CY_BLE_bts_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
* 
* \brief
*  This file contains the source code of initialization of the config structure
*  for the Bootloader Service.
*
********************************************************************************
* \copyright
* Copyright 2017-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "ble/cy_ble_bts.h"

#if(CY_BLE_MODE_PROFILE && defined(CY_BLE_BTS))
    
#ifdef CY_BLE_BTS_SERVER
/* Generated code */
`$BtsServer`
#endif /* CY_BLE_BTS_SERVER */

/* The configuration structure for the Bootloader Service. */
cy_stc_ble_bts_config_t cy_ble_btsConfig =
{
    /* Service GATT DB handles structure */
    #ifdef CY_BLE_BTS_SERVER
    .btss = &cy_ble_btss,
    #else
    .btss = NULL,
    #endif /* CY_BLE_BTS_SERVER */   
    
    /* An application layer event callback function to receive service events from the BLE Component. */
    .callbackFunc = NULL,
};
#endif /* (CY_BLE_MODE_PROFILE && defined(CY_BLE_BTS)) */

    
/* [] END OF FILE */
