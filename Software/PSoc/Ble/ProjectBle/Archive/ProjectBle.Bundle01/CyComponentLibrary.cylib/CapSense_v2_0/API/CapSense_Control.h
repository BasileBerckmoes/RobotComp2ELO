/***************************************************************************//**
* \file `$INSTANCE_NAME`_Control.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the function prototypes of the Control Block.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_CONTROL_H)
#define CY_SENSE_`$INSTANCE_NAME`_CONTROL_H

#include "syspm/cy_syspm.h"
#include "`$INSTANCE_NAME`_Configuration.h"

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/*******************************************************************************
* HIGH LEVEL API
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_HIGH_LEVEL
* \addtogroup group_cysense_high_level
* \{
*/

cy_status `$INSTANCE_NAME`_Start(void);
cy_status `$INSTANCE_NAME`_Stop(void);
cy_status `$INSTANCE_NAME`_Resume(void);

cy_status `$INSTANCE_NAME`_ProcessAllWidgets(void);
cy_status `$INSTANCE_NAME`_ProcessWidget(uint32 widgetId);

void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);

cy_en_syspm_status_t `$INSTANCE_NAME`_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams);
cy_en_syspm_status_t `$INSTANCE_NAME`_EnterLowPowerCallback(cy_stc_syspm_callback_params_t *callbackParams);
cy_en_syspm_status_t `$INSTANCE_NAME`_ExitLowPowerCallback(cy_stc_syspm_callback_params_t *callbackParams);

/** \}
* \endcond */

/**
* \cond SECTION_CYSENSE_LOW_LEVEL
* \addtogroup group_cysense_low_level
* \{
*/

cy_status `$INSTANCE_NAME`_ProcessWidgetExt(uint32 widgetId, uint32 mode);
cy_status `$INSTANCE_NAME`_ProcessSensorExt(uint32 widgetId, uint32 sensorId, uint32 mode);

/** \}
* \endcond */

/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/
cy_status `$INSTANCE_NAME`_Initialize(void);

/** \}
* \endcond */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_CONTROL_H */


/* [] END OF FILE */
