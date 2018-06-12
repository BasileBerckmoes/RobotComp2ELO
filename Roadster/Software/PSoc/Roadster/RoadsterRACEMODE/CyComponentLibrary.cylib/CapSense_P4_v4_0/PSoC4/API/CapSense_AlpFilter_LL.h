/***************************************************************************//**
* \file `$INSTANCE_NAME`_AlpFilter_LL.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the API specific for ALP Filter implementation.
*
* \see CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
* 
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_CAPSENSE_ALP_FILTER_LL_H)
#define CY_CAPSENSE_ALP_FILTER_LL_H

#include "cytypes.h"

/*******************************************************************************
* Declares ALP filter data structure
*******************************************************************************/
typedef struct
{
    uint32 dataParam0;
    uint16 dataParam1;
    uint16 dataParam2;
    uint16 dataParam3;
    uint16 dataParam4;
    uint16 dataParam5;
    uint16 dataParam6;
    uint8 dataParam7;
} ALP_FLTR_CHANNEL_STRUCT;

/*******************************************************************************
* Declares ALP filter configuration structure
*******************************************************************************/
typedef struct
{
    uint16 configParam0;
    uint16 configParam1;
    uint16 configParam2;
    uint8 configParam3;
    uint8 configParam4;
    uint8 configParam5;
} ALP_FLTR_CONFIG_STRUCT;

/*****************************************************
* Function Prototypes - internal Low Level functions
*****************************************************/
void ALP_Run(ALP_FLTR_CHANNEL_STRUCT *ptrFilterObj, ALP_FLTR_CONFIG_STRUCT *ptrFilterConfig, uint16 *rawCount, uint16 *baseline);
void ALP_Initialize(ALP_FLTR_CHANNEL_STRUCT *ptrFilterObj, uint16 *rawCount);
void ALP_ResetState(ALP_FLTR_CHANNEL_STRUCT *ptrFilterObj);
uint32 ALP_GetAverage(ALP_FLTR_CHANNEL_STRUCT *ptrFilterObj);

#endif /* End CY_CAPSENSE_ALP_FILTER_LL_H */


/* [] END OF FILE */
