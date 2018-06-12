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

#if(`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u)
    #include "`$INSTANCE_NAME`_GESTURE.h"
#endif /* (`$INSTANCE_NAME`_TOTAL_TRACKPAD_GESTURES_COUNT > 0u) */

typedef struct
{
    #if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    uint8 sensor;
    #endif  /* `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */
    uint8 pinNumber;
    uint8 portNumber;
    uint8 idacValue;
    uint16 senseClkDiv;
    uint16 sampleClkDiv;
    uint8 avgSamplesNum;
    uint16 calibrationCount;
    uint32 scanResolution;
}`$INSTANCE_NAME`_CP_MEASURE_CONFIG;

typedef struct
{
    uint8 *idac1LevelsTbl;
    uint8 *idac2LevelsTbl;
    uint8 *sensetivityTbl;
    uint8 *chargeDivTbl;
    uint8 *modDivTbl;
    const uint8 *widgetNubmersTbl;
    uint32 *resolutionsTbl;
    uint8 *noiseEnvelopeTbl;
    uint8 *runningDifferenceTbl;
    uint8 *signRegisterTbl;
    uint16 *sampleMinTbl;
    uint16 *sampleMaxTbl;
    uint16 *previousSampleTbl;
    uint8 *kValueTbl;
    uint8 *scanSpeedTbl;
    const uint8 *prescalerTable;
    uint8 const *rawDataIndex;
    uint8 const *numberOfSensors;
    uint16 (*ptrGetRaw)(uint32 sensor);
    void (*ptrPreScan)(uint32 sensor);
    uint16 (*ptrReadSensorRaw)(uint32 sensor);
    uint32 (*ptrGetBitValue)(const uint8 table[], uint32 position);
    void (*ptrSetBitValue)(uint8 table[], uint32 position, uint32 value);
}`$INSTANCE_NAME`_CONFIG_TYPE_POINTERS_P4_v2_60;

typedef struct
{
    uint8 totalScanslotsNum;
    uint8 totalWidgetsNum;
    uint8 totalSensorsNum;
    uint16 sensetivitySeed;
    uint16 hfclkFreq_MHz;
    `$INSTANCE_NAME`_CONFIG_TYPE_POINTERS_P4_v2_60 const * pointers;
}`$INSTANCE_NAME`_CONFIG_TYPE_P4_v2_60;

#define `$INSTANCE_NAME`_AVG_SAMPLES_NUM        (`$AvgSamplesNumber`u)


/***************************************
*        Function Prototypes
***************************************/
void `$INSTANCE_NAME`_PreScan(uint32 sensor);
void `$INSTANCE_NAME`_PostScan(uint32 sensor);

void `$INSTANCE_NAME`_EnableSensor(uint32 sensor);
void `$INSTANCE_NAME`_DisableSensor(uint32 sensor);

#if (`$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS)
    void `$INSTANCE_NAME`_EnableScanSlot(uint32 slot);
    void `$INSTANCE_NAME`_DisableScanSlot(uint32 slot);
#else
    #define `$INSTANCE_NAME`_EnableScanSlot(slot)   `$INSTANCE_NAME`_EnableSensor(slot)
    #define `$INSTANCE_NAME`_DisableScanSlot(slot)  `$INSTANCE_NAME`_DisableSensor(slot)
#endif  /* End `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS */

void `$INSTANCE_NAME`_EnableShieldElectrode(uint32 pinNumber, uint32 portNumber);

uint32 `$INSTANCE_NAME`_GetBitValue(const uint8 table[], uint32 position);
void `$INSTANCE_NAME`_SetBitValue(uint8 table[], uint32 position, uint32 value);

/* Find next sensor for One Channel design */
uint8 `$INSTANCE_NAME`_FindNextSensor(uint8 snsIndex);

void `$INSTANCE_NAME`_SetPinDriveMode(uint32 driveMode, uint32 pinNumber, uint32 portNumber);
void `$INSTANCE_NAME`_CalibrateSensor(uint32 sensor, uint32 rawLevel, uint8 idacLevelsTbl[]);
uint16  `$INSTANCE_NAME`_GetSensorRaw(uint32 sensor);

void `$INSTANCE_NAME`_DisableBaselineIDAC(void);
void `$INSTANCE_NAME`_EnableBaselineIDAC(const `$INSTANCE_NAME`_CONFIG_TYPE_P4_v2_60 *config);

uint32 `$INSTANCE_NAME`_GetLowCp(`$INSTANCE_NAME`_CP_MEASURE_CONFIG *config);
uint32 `$INSTANCE_NAME`_GetHighCp(const `$INSTANCE_NAME`_CP_MEASURE_CONFIG *config);
uint32 `$INSTANCE_NAME`_CalibrateIDAC(`$INSTANCE_NAME`_CP_MEASURE_CONFIG *config);
uint16 `$INSTANCE_NAME`_ScanSensorCp(const `$INSTANCE_NAME`_CP_MEASURE_CONFIG *config);

void `$INSTANCE_NAME`_ConnectElectrode(uint32 pinNumber, uint32 portNumber);
void `$INSTANCE_NAME`_DisconnectElectrode(uint32 pinNumber, uint32 portNumber);

void TunePrescalers_P4_v2_60(void *config);
void TuneSensitivity_P4_v2_60(void *config);
void MeasureNoiseEnvelope_P4_v2_60(void *config, const uint8 sensorNumber, const uint16 *rawData);
void CalculateThresholds_P4_v2_60(void *config, const uint8 sensorNumber, const uint8 widget, uint8 *fingerThres, uint8 *noiseThres);
void CalibrateSensors_P4_v2_60(void *config, uint16 rawLevel);
void CalibrateOneDAC_P4_v2_60(void *config, uint16 rawLevel, uint32 curSensor, uint8 *idacLevelsTbl);


#endif /* CY_CAPSENSE_CSD_PVT_`$INSTANCE_NAME`_H */
