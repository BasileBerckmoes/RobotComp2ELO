/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PVT.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and structure declarations for the
*  CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CSD_PVT_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

typedef struct
{
    uint8 kValueScalingFactor;
    uint8 *idac1LevelsTbl;
    uint8 *idac2LevelsTbl;
    uint8 *sensetivityTbl;
    uint8 *chargeDivTbl;
    uint8 *modDivTbl;
    const uint8  *widgetNubmersTbl;
    uint8 *snsEnableMask;
    uint8 *resolutionsTbl;
    uint8 const  *rawDataIndex;
    uint8 const *numberOfSensors;
    uint8 const * ImmSnsMap;
    uint8 *proxEnableMask;
    uint16 (*ptrGetRaw)(uint32 sensor);
    void (*ptrPreScan)(uint32 sensor);
    void (*ptrClkChangeImoFreq)(uint32 freq);
    uint16 (*ptrReadSensorRaw)(uint32 sensor);
    uint32 (*ptrGetBitValue)(uint8 table[], uint32 position);
    void (*ptrSetBitValue)(uint8 table[], uint32 position, uint32 value);
}`$INSTANCE_NAME`_CONFIG_TYPE_POINTERS_SF_v1_0;

typedef struct
{
    uint8 totalScanslotsNum;
    uint8 totalWidgetsNum;
    uint8 totalSensorsNum;
    uint8 totalButtonsNum;
    uint8 totalSlidersNum;
    uint8 totalGenericsNum;
    uint8 immunityLevel;
    uint8 immunity0;
    uint8 immunity1;
    uint8 immunity2;
    uint8 immunityChannelSize;
    uint16 sensetivitySeed;
    uint16 imoFreq_MHz;
    `$INSTANCE_NAME`_CONFIG_TYPE_POINTERS_SF_v1_0 const * pointers;

}`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0;

#if(CYDEV_BCLK__HFCLK__MHZ > 12u)
    #define `$INSTANCE_NAME`_IDAC2_MAX      (127u)
#elif(CYDEV_BCLK__HFCLK__MHZ > 6u)
    #define `$INSTANCE_NAME`_IDAC2_MAX      (63u)
#else
    #define `$INSTANCE_NAME`_IDAC2_MAX      (31u)
#endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

#define `$INSTANCE_NAME`_BIST_API_GENERATE (`$EnableBIST`u)

/* STREET_FIGHTER related constants */
#if (1u != `$INSTANCE_NAME`_IS_STREET_FIGHTER)
    typedef `$SizeReplacementString`  `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE;
    typedef `$SizeReplacementString`  `$INSTANCE_NAME`_SIGNAL_SIZE_TYPE;
#else
    typedef uint8                     `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE;
    typedef uint16                    `$INSTANCE_NAME`_SIGNAL_SIZE_TYPE;
#endif  /* (0u != `$INSTANCE_NAME`_IS_STREET_FIGHTER */

#if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    void `$INSTANCE_NAME`_EnableScanSlot(uint32 slot);
    void `$INSTANCE_NAME`_DisableScanSlot(uint32 slot);
#else
    #define `$INSTANCE_NAME`_EnableScanSlot(slot)   `$INSTANCE_NAME`_EnableSensor(slot)
    #define `$INSTANCE_NAME`_DisableScanSlot(slot)  `$INSTANCE_NAME`_DisableSensor(slot)
#endif  /* End `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

/* Find next sensor for One Channel design */
uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex);


/* Start and Compete scan */
void `$INSTANCE_NAME`_PreScan(uint32 sensor);
void `$INSTANCE_NAME`_PostScan(uint32 sensor);

void `$INSTANCE_NAME`_DisableBaselineIDAC(void);
void `$INSTANCE_NAME`_EnableBaselineIDAC(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config);

extern uint8 `$INSTANCE_NAME`_widgetNumber[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

/* Global variables and arrays */
extern volatile uint8 `$INSTANCE_NAME`_csdStatusVar;
extern volatile uint8 `$INSTANCE_NAME`_sensorIndex;

void TunePrescalers_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config);
void TuneSensitivity_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config);
void MeasureNoiseEnvelope_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, const uint8 sensorNumber, const uint16 *rawData);
void CalculateThresholds_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, const uint8 sensorNumber, const uint16 *rawData, const uint8 widget, uint8 *fingerThres, uint8 *noiseThres);
void CalibrateSensors_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint16 rawLevel);
void CalibrateOneDAC_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint16 rawLevel, uint32 curSensor, uint8 *idacLevelsTbl);
uint32 GetImmunitySensorIndex_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 immunityIndex, uint32 sensor);
uint32 GetSensorImmunityIndex_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 immunitySensorIndex);
uint32 GetImmunityWidgetIndex_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 immunityIndex, uint32 widget);
uint32 GetImmunityWidgetIndexEX_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 immunitySensorIndex);
uint32 GetWidgetImmunityIndex_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 immunitySensorIndex);
uint32 GetImmunity_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 immunitySensorIndex);
void PreProcessDataLow_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 sensor);
void PreProcessDataMedium_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 sensor);
void PreProcessDataHigh_SF_v1_0(`$INSTANCE_NAME`_CONFIG_TYPE_SF_v1_0 *config, uint32 sensor);

#endif /* CY_CAPSENSE_CSD_PVT_`$INSTANCE_NAME`_H */
