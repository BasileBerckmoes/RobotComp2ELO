/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SMS.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the declarations of a wrapper between the CapSense CSD component
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

#define `$INSTANCE_NAME`_AVG_SAMPLES_NUM        (`$AvgSamplesNumber`u)
#define `$INSTANCE_NAME`_CALIBRATION_RESOLUTION (15u)

#if (0u != CY_PSOC4SF)
    #define `$INSTANCE_NAME`_SCANNING_MD            (1u)
#else
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        #define `$INSTANCE_NAME`_SCANNING_MD        (4u)
    #else
        #define `$INSTANCE_NAME`_SCANNING_MD        (2u)
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* (0u != CY_PSOC4SF) */

#define `$INSTANCE_NAME`_THRESHOLD_1                (220u)
#define `$INSTANCE_NAME`_THRESHOLD_2                (237u)
#define `$INSTANCE_NAME`_THRESHOLD_3                (245u)
#define `$INSTANCE_NAME`_THRESHOLD_4                (250u)

#if (0u != CY_PSOC4SF)
    #define `$INSTANCE_NAME`_IMO_CORRECTION         (1u)
#else
    #if (CYDEV_BCLK__HFCLK__MHZ > 24u)
        #define `$INSTANCE_NAME`_IMO_CORRECTION     (4u)
    #elif (CYDEV_BCLK__HFCLK__MHZ > 12u)
        #define `$INSTANCE_NAME`_IMO_CORRECTION     (2u)
    #else
        #define `$INSTANCE_NAME`_IMO_CORRECTION     (1u)
    #endif /* (CYDEV_BCLK__HFCLK__MHZ > 24u) */
#endif /* (0u != CY_PSOC4SF) */

#if(`$INSTANCE_NAME`_CHAINED_CLOCKS == `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED)
    #define `$INSTANCE_NAME`_CALIBRATION_ASD            (`$AnalogSwitchDiv`u)
#else
    #define `$INSTANCE_NAME`_CALIBRATION_ASD            ((`$AnalogSwitchDiv`u) * `$INSTANCE_NAME`_IMO_CORRECTION / 4u)
#endif  /* (`$INSTANCE_NAME`_CHAINED_CLOCKS != `$INSTANCE_NAME`_CHAINED_CLOCKS_ENABLED) */

#define `$INSTANCE_NAME`_CALIBRATION_MD             (`$ModulatorDiv`u)

#define `$INSTANCE_NAME`_SENSITIVITY_MASK           (0x0Fu)

#define `$INSTANCE_NAME`_SLIDER_THRESHOLDS_MANUAL  (`$SliderThresholdsUpdateManual`u)

#if(`$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT < `$INSTANCE_NAME`_TOTAL_EMC_CHANNELS)
    #define `$INSTANCE_NAME`_IMMUNITY_CHANNEL_SIZE  (`$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT)
#else
    #define `$INSTANCE_NAME`_IMMUNITY_CHANNEL_SIZE  (`$INSTANCE_NAME`_TOTAL_EMC_CHANNELS)
#endif /* (`$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT < `$INSTANCE_NAME`_TOTAL_EMC_CHANNELS) */

#define `$INSTANCE_NAME`_NON_EMC_SCANSLOTS_NUM  (`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT - `$INSTANCE_NAME`_TOTAL_BUTTONS_COUNT)

#define `$INSTANCE_NAME`_IMMUNITY_ENABLE_SCANSLOTS_NUM  (`$INSTANCE_NAME`_IMMUNITY_CHANNEL_SIZE + `$INSTANCE_NAME`_NON_EMC_SCANSLOTS_NUM)
#define `$INSTANCE_NAME`_IMMUNITY_DISABLE_SCANSLOTS_NUM (`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT)

#define `$INSTANCE_NAME`_IMMUNITY_ENABLE_WIDGETS_NUM    (`$INSTANCE_NAME`_IMMUNITY_CHANNEL_SIZE +\
                                                         `$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT +\
                                                         `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)

#define `$INSTANCE_NAME`_IMMUNITY_DISABLE_WIDGETS_NUM   (`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT)

#define `$INSTANCE_NAME`_CAL_RAW_COUNT           (3482u)

void `$INSTANCE_NAME`_AutoTuneInit(void);
void `$INSTANCE_NAME`_AutoTune(void);

void `$INSTANCE_NAME`_UpdateThresholds(uint32 sensor);
void `$INSTANCE_NAME`_SetSensitivity(uint32 sensor, uint32 value);

void `$INSTANCE_NAME`_SetAnalogSwitchesSrcDirect(void);

uint16 `$INSTANCE_NAME`_GetSensorRaw(uint32 sensor);
uint16 `$INSTANCE_NAME`_GetNoiseEnvelope(uint32 sensor);

void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr);
uint8 `$INSTANCE_NAME`_GetSensitivityCoefficient(uint32 sensor);

/* Median filter function prototype */
#if (`$INSTANCE_NAME`_IMMUNITY_LEVEL == `$INSTANCE_NAME`_IMMUNITY_HIGH)
    uint16 `$INSTANCE_NAME`_MedianFilter(uint16 x1, uint16 x2, uint16 x3);
#endif /* (CapSense_IMMUNITY_LEVEL == CapSense_IMMUNITY_HIGH) */

#endif  /* (CY_CAPSENSE_CSD_SMS_`$INSTANCE_NAME`_H) */

/* [] END OF FILE */
