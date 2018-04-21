/*******************************************************************************
* File Name: `$INSTANCE_NAME`_INT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    #include "`$INSTANCE_NAME`_SMS.h"
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

/*******************************************************************************
*  Place your includes, defines and code here
********************************************************************************/
/* `#START `$INSTANCE_NAME`_IsrCH_ISR_intc` */

/* `#END` */

#if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)

    #if((0u != CapSense_IS_STREET_FIGHTER) && (CapSense_TOTAL_SLIDERS_COUNT >= 2u))
        extern uint8 `$INSTANCE_NAME`_numberOfSensors[];
    #else
        extern const uint8 `$INSTANCE_NAME`_numberOfSensors[];
    #endif /* ((0u != CapSense_IS_STREET_FIGHTER) && (CapSense_TOTAL_SLIDERS_COUNT >= 2u)) */

    extern uint8 `$INSTANCE_NAME`_widgetNumber[];
    extern uint8 `$INSTANCE_NAME`_immunityIndex;
    extern uint8 `$INSTANCE_NAME`_highImmunityEnable;
    extern `$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 `$INSTANCE_NAME`_config;
#endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when the measure window is closed. The measure window
*  depends on the  sensor scan resolution parameter.
*  The ISR has two modes:
*   1. Scans a single sensor and stores the measure result.
*   2. Stores a result of the current measure and starts the next scan till all
*      the enabled sensors are scanned.
*  This interrupt handler is used only in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_csdStatusVar - used to provide status and mode of scanning process.
*   Mode - single scan or scan of all enabled sensors.
*   Status - scan in progress or ready for new scan.
*  `$INSTANCE_NAME`_sensorIndex - used to store sensor scanning sensor number.
*  `$INSTANCE_NAME`_widgetNumber[] - This array contains current of widget for sensor.
*  `$INSTANCE_NAME`_numberOfSensors - This array contains numbers of sensors for widget.
*  `$INSTANCE_NAME`_immunityIndex - contains current Immunity index (0, 1, 2).
*
* Side Effects:
*  None
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_ISR)
{
    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        uint8 currentWidget;
        uint8 sensorsPerWidget;
        uint32 immunitySensorEnable;
    #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

    `$INSTANCE_NAME`_CSD_INTR_REG = 1u;

    #ifdef `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK
        `$INSTANCE_NAME`_ISR_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ISR_ENTRY_CALLBACK */

    /*  Place your Interrupt code here. */
    /* `#START `$INSTANCE_NAME`_ONE_CHANNEL_IsrCH0_ISR` */

    /* `#END` */

    #ifdef `$INSTANCE_NAME`_ONE_CHANNEL_ISRCH0_ISR_CALLBACK
        `$INSTANCE_NAME`_ONE_CHANNEL_IsrCH0_ISR_Callback();
    #endif /* `$INSTANCE_NAME`_ONE_CHANNEL_ISRCH0_ISR_CALLBACK */

    /* Save results and disable sensor */
    `$INSTANCE_NAME`_PostScan(`$INSTANCE_NAME`_sensorIndex);

    #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
        /* Get Widget number */
        currentWidget = `$INSTANCE_NAME`_widgetNumber[`$INSTANCE_NAME`_sensorIndex];
        /* Get Number of Sensors in the Widget */
        sensorsPerWidget = `$INSTANCE_NAME`_numberOfSensors[currentWidget];
        /* Check if button or Immunity is not low */
        if ((sensorsPerWidget <= 1) && (`$INSTANCE_NAME`_immunityIndex != 2u) && (`$INSTANCE_NAME`_highImmunityEnable == `$INSTANCE_NAME`_IMMUNITY_HIGH))
        {
            /* Prepare scanning for Immunity */
            if (`$INSTANCE_NAME`_immunityIndex == 0u)
            {
                /* Check if Immunity is enabled for this sensor */
                immunitySensorEnable = `$INSTANCE_NAME`_CheckEmcSensorEnable((`$INSTANCE_NAME`_immunityIndex + 1), `$INSTANCE_NAME`_sensorIndex);

                if(immunitySensorEnable == 1)
                {
                    /* Set Immunity = 1 */
                    `$INSTANCE_NAME`_immunityIndex++;
                    PreProcessDataMedium_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_sensorIndex);
                }
                else
                {
                    `$INSTANCE_NAME`_SetOneScanComplete();
                }
            }
            /* Check if Immunity = 1 */
            else if (`$INSTANCE_NAME`_immunityIndex == 1)
            {
                /* Set Immunity = 2 */
                `$INSTANCE_NAME`_immunityIndex++;
                PreProcessDataHigh_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_sensorIndex);
            }
        }
        else
    #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */
        {
            #if(`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
                `$INSTANCE_NAME`_immunityIndex = 0;
                PreProcessDataLow_SF_v1_0(&`$INSTANCE_NAME`_config, `$INSTANCE_NAME`_sensorIndex);
            #endif  /* (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH) */

            `$INSTANCE_NAME`_SetOneScanComplete();
        }

    #ifdef `$INSTANCE_NAME`_ISR_EXIT_CALLBACK
        `$INSTANCE_NAME`_ISR_ExitCallback();
    #endif /* `$INSTANCE_NAME`_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
