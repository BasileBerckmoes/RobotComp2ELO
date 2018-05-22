/***************************************************************************//**
* \file `$INSTANCE_NAME`_Structure.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file defines the data structure global variables and provides implementation
*   for the high-level and low-level APIs of the Data Structure module.
*
* \see `$INSTANCE_NAME` v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
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

#include <string.h>
#include <cytypes.h>
#include "CyLib.h"
#include "`$INSTANCE_NAME`_Structure.h"

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
    #include "`$INSTANCE_NAME`_Adc.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */

/*******************************************************************************
* Define the RAM Data Structure variables and their init data in flash
*******************************************************************************/

/**
* \cond SECTION_GLOBAL_VARIABLES
* \addtogroup group_global_variables
* \{
*/

/**
* The variable that contains the `$INSTANCE_NAME` configuration, settings and scanning results.
* `$INSTANCE_NAME`_dsRam represents RAM Data Structure.
*/
`$INSTANCE_NAME`_RAM_STRUCT `$INSTANCE_NAME`_dsRam;

/** \}
* \endcond */

/**
* \cond SECTION_API_CONSTANTS
* \addtogroup group_api_constants
* \{
*/

`$AdcIoInit`

/** \}
* \endcond */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DsInitialize
****************************************************************************//**
*
* \brief
*   This function initializes the Data Structure storage.
*
* \details
*   Configures the initial Adc datastructure members.
*
*******************************************************************************/
void `$INSTANCE_NAME`_`$AdcModulePrefix`DsInitialize(void)
{
    /* Reset RAM data structure content */
    (void)memset(&`$INSTANCE_NAME`_dsRam, 0, sizeof(`$INSTANCE_NAME`_dsRam));

    `$INSTANCE_NAME`_dsRam.adcResolution = `$INSTANCE_NAME`_ADC_RESOLUTION;
    `$INSTANCE_NAME`_dsRam.adcIdac = (uint8)(`$INSTANCE_NAME`_ADC_IDAC_DEFAULT);
}

/* [] END OF FILE */
