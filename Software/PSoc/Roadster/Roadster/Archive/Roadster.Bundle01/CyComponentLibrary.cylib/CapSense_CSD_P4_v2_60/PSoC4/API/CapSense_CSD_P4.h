/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "`$INSTANCE_NAME`_IP.h"
#include "`$INSTANCE_NAME`_SenseClk.h"
#include "`$INSTANCE_NAME`_SampleClk.h"

/* Constants set by Customizer */
`$DefineConstants`
#define `$INSTANCE_NAME`_TOTAL_SENSOR_MASK (((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

/* Interrupt handler */
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);

/* ISR Number and Priority to work with CyLib functions */
#define `$INSTANCE_NAME`_ISR_NUMBER        (`$INSTANCE_NAME`_ISR__INTC_NUMBER)
#define `$INSTANCE_NAME`_ISR_PRIORITY      (`$INSTANCE_NAME`_ISR__INTC_PRIOR_NUM)

/***************************************
*   Condition compilation parameters
***************************************/

#define `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS       (`$ConnectInactiveSensors`u)
#define `$INSTANCE_NAME`_IS_COMPLEX_SCANSLOTS       (`$IsComplexScanSlots`u)
#define `$INSTANCE_NAME`_COMPLEX_SCANSLOTS_NUM      (`$ComplexScanSlotCount`u)
#define `$INSTANCE_NAME`_DEDICATED_SENSORS_NUM      (`$DedicatedSensorCount`u)
#define `$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE   (`$PortPinConfigTableSize`u)

#define `$INSTANCE_NAME`_IDAC_CNT                   (`$IDACsCount`u)
#define `$INSTANCE_NAME`_IDAC1_POLARITY             (`$CurrentSource`u)
#define `$INSTANCE_NAME`_IDAC1_RANGE_VALUE          (`$IDACRange`u)
#define `$INSTANCE_NAME`_IDAC2_RANGE_VALUE          (`$IDACRange`u)

#define `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET     (`$SensorsFreqSettingsInd`u)
#define `$INSTANCE_NAME`_FILTER_ENABLE              (`$DfbEnable`u)
#define `$INSTANCE_NAME`_PRS_OPTIONS                (`$PrsOptions`u)

#define `$INSTANCE_NAME`_WATER_PROOF                (`$WaterProofingEnabled`u)

#define `$INSTANCE_NAME`_TUNING_METHOD              (`$TuningMethod`u)
#define `$INSTANCE_NAME`_TUNER_API_GENERATE         (`$EnableTuneHelper`u)

#define `$INSTANCE_NAME`_CSHL_API_GENERATE          (`$CshlApiGenerate`u)

#define `$INSTANCE_NAME`_CMOD_PREGARGE_OPTION       (`$CmodPrecharge`u)
#define `$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION   (`$CshTankPrecharge`u)
#define `$INSTANCE_NAME`_IS_SHIELD_ENABLE           (`$ShieldEnable`u)
#define `$INSTANCE_NAME`_CSH_TANK_ENABLE            (`$ShieldTankEnable`u)

#define `$INSTANCE_NAME`_SHIELD_DELAY               (`$ShieldDelayValue`u)
#define `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE     (`$EnableAutoCalibration`u)

#define `$INSTANCE_NAME`_IS_OVERSAMPLING_EN         (`$OversamplingEn`u)

#define `$INSTANCE_NAME`_CSD_4B_PWM_MODE            (`$DbPwmMode`u)
#define `$INSTANCE_NAME`_CSD_4B_PWM_COUNT           (`$DbPwmPeriod`u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
`#cy_declare_enum IDACOptions`
`#cy_declare_enum IDACRangeOptions`
`#cy_declare_enum PrsOptions`
/* Connection of inactive sensors definitions */
`#cy_declare_enum CISOptions`
/* Precharge options definitions */
`#cy_declare_enum CapacitorPrechargeOptions`
/* Method of tuning */
`#cy_declare_enum TuningMethodOptions`
/* Dead band PWM modulator options */
`#cy_declare_enum DbPwmOptions`

#define `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM          (9u)
#define `$INSTANCE_NAME`_GLITCH_ELIMINATION_TIMEOUT     (`$GlitchEliminateTimeout`u)
#define `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC (`$INSTANCE_NAME`_GLITCH_ELIMINATION_TIMEOUT * CYDEV_BCLK__SYSCLK__MHZ)

#if(`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC >= `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM)
    #define `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES (`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC -\
                                                        `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM)
#else
    #define `$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES (`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (`$INSTANCE_NAME`_GLITCH_ELIMINATION_CYCLES_CALC >= `$INSTANCE_NAME`_DELAY_EXTRACYCLES_NUM) */

#define `$INSTANCE_NAME`_INITIAL_CLK_DIVIDER            (CYDEV_BCLK__HFCLK__KHZ / CYDEV_BCLK__SYSCLK__KHZ)


/* Structure to save registers before going to sleep */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_CsdHwBlockInit(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Wakeup(void);
uint32 `$INSTANCE_NAME`_IsBusy(void);
void `$INSTANCE_NAME`_ScanSensor(uint32 sensor);
void `$INSTANCE_NAME`_ScanWidget(uint32 widget);
void `$INSTANCE_NAME`_ScanEnabledWidgets(void);
uint16 `$INSTANCE_NAME`_ReadSensorRaw(uint32 sensor);
void `$INSTANCE_NAME`_WriteSensorRaw(uint32 sensor, uint16 value);
void `$INSTANCE_NAME`_ClearSensors(void);
void `$INSTANCE_NAME`_SetShieldDelay(uint32 delay);
uint32 `$INSTANCE_NAME`_ReadCurrentScanningSensor(void);

uint32 `$INSTANCE_NAME`_GetScanResolution(uint32 widget);
uint32 `$INSTANCE_NAME`_GetSenseClkDivider(uint32 sensor);
uint32 `$INSTANCE_NAME`_GetModulatorClkDivider(uint32 sensor);
uint32 `$INSTANCE_NAME`_GetModulationIDAC(uint32 sensor);
uint32 `$INSTANCE_NAME`_GetCompensationIDAC(uint32 sensor);
uint32 `$INSTANCE_NAME`_GetIDACRange(void);

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    void `$INSTANCE_NAME`_SetScanResolution(uint32 widget, uint32 resolution);
    void `$INSTANCE_NAME`_SetSenseClkDivider(uint32 sensor, uint32 senseClk);
    void `$INSTANCE_NAME`_SetModulatorClkDivider(uint32 sensor, uint32 modulatorClk);
    void `$INSTANCE_NAME`_SetModulationIDAC(uint32 sensor, uint32 modIdacValue);
    void `$INSTANCE_NAME`_SetCompensationIDAC(uint32 sensor, uint32 compIdacValue);
    void `$INSTANCE_NAME`_SetIDACRange(uint32 iDacRange);
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) */


void `$INSTANCE_NAME`_SetDriveModeAllPins(uint32 driveMode);
void `$INSTANCE_NAME`_RestoreDriveModeAllPins(void);
void `$INSTANCE_NAME`_SetUnscannedSensorState(uint32 sensor, uint32 sensorState);
void `$INSTANCE_NAME`_NormalizeWidgets(uint32 widgetsNum, uint8 dataPtr[]);

/***************************************
*           API Constants
***************************************/

/* PWM Resolution */
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_8_BITS  (0x00u)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_9_BITS  (0x01u)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_10_BITS (0x03u)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_11_BITS (0x07u)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_12_BITS (0x0Fu)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_13_BITS (0x1Fu)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_14_BITS (0x3Fu)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_15_BITS (0x7Fu)
#define `$INSTANCE_NAME`_CNT_MSB_RESOLUTION_16_BITS (0xFFu)

#define `$INSTANCE_NAME`_ONE_CYCLE                  (0x00010000Lu)

#define `$INSTANCE_NAME`_WINDOW_APPEND              (0xFFFF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_6_BITS          (0x003F0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_7_BITS          (0x007F0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_8_BITS          (0x00FF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_9_BITS          (0x01FF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_10_BITS         (0x03FF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_11_BITS         (0x07FF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_12_BITS         (0x0FFF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_13_BITS         (0x1FFF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_14_BITS         (0x3FFF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_15_BITS         (0x7FFF0000Lu)
#define `$INSTANCE_NAME`_RESOLUTION_16_BITS         (0xFFFF0000Lu)

#define `$INSTANCE_NAME`_RESOLUTION_OFFSET          (16u)
#define `$INSTANCE_NAME`_MSB_RESOLUTION_OFFSET      (22u)
#define `$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE       (`$WidgetElementCount`u)

/* Software Status Register Bit Masks */
#define `$INSTANCE_NAME`_SW_STS_BUSY                (0x01u)
/* Software Control Register Bit Masks */
#define `$INSTANCE_NAME`_SW_CTRL_SINGLE_SCAN        (0x80u)

/* Software Control Register Bit Masks for scanning one widget */
#define `$INSTANCE_NAME`_SW_CTRL_WIDGET_SCAN        (0x40u)

/* Flag for complex scan slot */
#define `$INSTANCE_NAME`_COMPLEX_SS_FLAG            (0x80u)

/* Flag for scanning is complete */
#define `$INSTANCE_NAME`_NOT_SENSOR                 (0xFFFFFFFFLu)

/* Number of bits for each pin in PC register. */
#define `$INSTANCE_NAME`_PC_PIN_CFG_SIZE            (0x03u)

/* Number of bits for each pin in HSIOM register. */
#define `$INSTANCE_NAME`_HSIOM_PIN_CFG_SIZE         (0x04u)

#define `$INSTANCE_NAME`_CFG_REG_TBL_SIZE           (`$cfgRegTblSize`u)

/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_CSD_ID_REG             (*(reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_ID)
#define `$INSTANCE_NAME`_CSD_ID_PTR             ( (reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_ID)

#define `$INSTANCE_NAME`_CSD_CFG_REG            (*(reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_CONFIG)
#define `$INSTANCE_NAME`_CSD_CFG_PTR            ( (reg32 *)  `$INSTANCE_NAME`_CSD_FFB__CSD_CONFIG)

#define `$INSTANCE_NAME`_CSD_IDAC_REG           (*(reg32 *)  `$INSTANCE_NAME`_IDAC1_cy_psoc4_idac__CSD_IDAC)
#define `$INSTANCE_NAME`_CSD_IDAC_PTR           ( (reg32 *)  `$INSTANCE_NAME`_IDAC1_cy_psoc4_idac__CSD_IDAC)

#define `$INSTANCE_NAME`_CSD_CNT_REG            (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_COUNTER)
#define `$INSTANCE_NAME`_CSD_CNT_PTR            ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_COUNTER)

#define `$INSTANCE_NAME`_CSD_STAT_REG           (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_STATUS)
#define `$INSTANCE_NAME`_CSD_STAT_PTR           ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_STATUS)

#define `$INSTANCE_NAME`_CSD_INTR_REG           (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR)
#define `$INSTANCE_NAME`_CSD_INTR_PTR           ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR)

#define `$INSTANCE_NAME`_CSD_INTR_SET_REG       (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR_SET)
#define `$INSTANCE_NAME`_CSD_INTR_SET_PTR       ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_INTR_SET)

#define `$INSTANCE_NAME`_CSD_4B_PWM_REG         (*(reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_PWM)
#define `$INSTANCE_NAME`_CSD_4B_PWM_PTR         ( (reg32 *) `$INSTANCE_NAME`_CSD_FFB__CSD_PWM)

#define `$INSTANCE_NAME`_CSD_TRIM1_REG          (*(reg32 *) `$INSTANCE_NAME`_IDAC1_cy_psoc4_idac__CSD_TRIM1)
#define `$INSTANCE_NAME`_CSD_TRIM1_PTR          ( (reg32 *) `$INSTANCE_NAME`_IDAC1_cy_psoc4_idac__CSD_TRIM1)

#define `$INSTANCE_NAME`_CSD_TRIM2_REG          (*(reg32 *) `$INSTANCE_NAME`_IDAC1_cy_psoc4_idac__CSD_TRIM2)
#define `$INSTANCE_NAME`_CSD_TRIM2_PTR          ( (reg32 *) `$INSTANCE_NAME`_IDAC1_cy_psoc4_idac__CSD_TRIM2)

#if (2u == `$INSTANCE_NAME`_M0S8CSD_BLOCK_CNT)
    #if (`$INSTANCE_NAME`_CSD_FFB__CSD_NUMBER != 1u)
        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #else
        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
        #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
    #endif /* (`$INSTANCE_NAME`_CSD_FFB__CSD_NUMBER != 1u) */
#else
    #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
    #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

    #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
    #define `$INSTANCE_NAME`_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#endif /* (2u == `$INSTANCE_NAME`_M0S8CSD_BLOCK_CNT) */

/* Port function select */
`$hsiomRegisters`
`$configRegisters`
`$dataRegisters`

#define `$INSTANCE_NAME`_CMOD_CONNECTION_REG        (*(reg32 *) `$INSTANCE_NAME`_Cmod__0__HSIOM)
#define `$INSTANCE_NAME`_CMOD_PORT_PC_REG           (*(reg32 *) `$INSTANCE_NAME`_Cmod__0__PC)
#define `$INSTANCE_NAME`_CMOD_PORT_DR_REG           (*(reg32 *) `$INSTANCE_NAME`_Cmod__0__DR)

#define `$INSTANCE_NAME`_CTANK_CONNECTION_REG       (*(reg32 *) `$INSTANCE_NAME`_Csh_tank__0__HSIOM)
#define `$INSTANCE_NAME`_CTANK_PORT_PC_REG          (*(reg32 *) `$INSTANCE_NAME`_Csh_tank__0__PC)
#define `$INSTANCE_NAME`_CTANK_PORT_DR_REG          (*(reg32 *) `$INSTANCE_NAME`_Csh_tank__0__DR)

/***************************************
*       Register Constants
***************************************/

/* Port configuration defines */
#define `$INSTANCE_NAME`_CSD_HSIOM_MASK                 (0x0000000FLu)

#define `$INSTANCE_NAME`_CSD_SENSE_PORT_MODE            (0x00000004Lu)
#define `$INSTANCE_NAME`_CSD_SHIELD_PORT_MODE           (0x00000005Lu)

#define `$INSTANCE_NAME`_AMUXA_CONNECTION_MODE          (0x00000006Lu)
#define `$INSTANCE_NAME`_AMUXB_CONNECTION_MODE          (0x00000007Lu)

#define `$INSTANCE_NAME`_CSD_PIN_MODE_MASK              (0x00000007Lu)
#define `$INSTANCE_NAME`_CSD_PIN_DRIVE_MASK             (0x00000001Lu)

#define `$INSTANCE_NAME`_CSD_PIN_DM_STRONG              (0x00000006Lu)
#define `$INSTANCE_NAME`_CSD_PIN_DM_HIGH_Z              (0x00000000Lu)

#define `$INSTANCE_NAME`_CSD_CMOD_CONNECTION_MASK   (uint32)(`$INSTANCE_NAME`_Cmod__0__HSIOM_MASK)
#define `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_A      (uint32)(`$INSTANCE_NAME`_AMUXA_CONNECTION_MODE << `$INSTANCE_NAME`_Cmod__0__HSIOM_SHIFT)
#define `$INSTANCE_NAME`_CSD_CMOD_TO_AMUXBUS_B      (uint32)(`$INSTANCE_NAME`_AMUXB_CONNECTION_MODE << `$INSTANCE_NAME`_Cmod__0__HSIOM_SHIFT)

#if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
    #define `$INSTANCE_NAME`_CSD_CTANK_CONNECTION_MASK  (uint32)(`$INSTANCE_NAME`_Csh_tank__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_A     (uint32)(`$INSTANCE_NAME`_AMUXA_CONNECTION_MODE << `$INSTANCE_NAME`_Csh_tank__0__HSIOM_SHIFT)
    #define `$INSTANCE_NAME`_CSD_CTANK_TO_AMUXBUS_B     (uint32)(`$INSTANCE_NAME`_AMUXB_CONNECTION_MODE << `$INSTANCE_NAME`_Csh_tank__0__HSIOM_SHIFT)
#endif /* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

#define  `$INSTANCE_NAME`_CSD_CMOD_PC_MASK          (uint32)(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK <<\
                                                            ((uint32)`$INSTANCE_NAME`_Cmod__0__SHIFT * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE))
#define  `$INSTANCE_NAME`_CMOD_PC_STRONG_MODE       (uint32)(`$INSTANCE_NAME`_CSD_PIN_DM_STRONG <<\
                                                            ((uint32)`$INSTANCE_NAME`_Cmod__0__SHIFT * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE))
#define  `$INSTANCE_NAME`_CMOD_PC_HIGH_Z_MODE       (uint32)(`$INSTANCE_NAME`_CSD_PIN_DM_HIGH_Z <<\
                                                            ((uint32)`$INSTANCE_NAME`_Cmod__0__SHIFT * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE))

#if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
    #define  `$INSTANCE_NAME`_CSD_CTANK_PC_MASK         (uint32)(`$INSTANCE_NAME`_CSD_PIN_MODE_MASK <<\
                                                                ((uint32)`$INSTANCE_NAME`_Csh_tank__0__SHIFT * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE))
    #define  `$INSTANCE_NAME`_CTANK_PC_STRONG_MODE      (uint32)(`$INSTANCE_NAME`_CSD_PIN_DM_STRONG <<\
                                                                ((uint32)`$INSTANCE_NAME`_Csh_tank__0__SHIFT * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE))
    #define  `$INSTANCE_NAME`_CTANK_PC_HIGH_Z_MODE      (uint32)(`$INSTANCE_NAME`_CSD_PIN_DM_HIGH_Z <<\
                                                                ((uint32)`$INSTANCE_NAME`_Csh_tank__0__SHIFT * `$INSTANCE_NAME`_PC_PIN_CFG_SIZE))
#endif /* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

#define  `$INSTANCE_NAME`_CMOD_DR_VSSIO             (uint32)(`$INSTANCE_NAME`_Cmod__0__MASK)
#define  `$INSTANCE_NAME`_CMOD_DR_VDDIO             (0x00000000Lu)
#define  `$INSTANCE_NAME`_CMOD_DR_MASK              (uint32)(`$INSTANCE_NAME`_Cmod__0__MASK)

#if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
    #define  `$INSTANCE_NAME`_CTANK_DR_VSSIO            (uint32)(`$INSTANCE_NAME`_Csh_tank__0__MASK)
    #define  `$INSTANCE_NAME`_CTANK_DR_VDDIO            (0x00000000Lu)
    #define  `$INSTANCE_NAME`_CTANK_DR_MASK             (uint32)(`$INSTANCE_NAME`_Csh_tank__0__MASK)
#endif /* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

#define  `$INSTANCE_NAME`_CMOD_PIN_NUMBER               (`$INSTANCE_NAME`_Cmod__0__SHIFT)
#define  `$INSTANCE_NAME`_CMOD_PRT_NUMBER               (`$INSTANCE_NAME`_Cmod__0__PORT)

#if(0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE)
    #define  `$INSTANCE_NAME`_CTANK_PIN_NUMBER          (`$INSTANCE_NAME`_Csh_tank__0__SHIFT)
    #define  `$INSTANCE_NAME`_CTANK_PRT_NUMBER          (`$INSTANCE_NAME`_Csh_tank__0__PORT)
#endif /* (0u != `$INSTANCE_NAME`_CSH_TANK_ENABLE) */

/* ID register fields position */
#define `$INSTANCE_NAME`_CSD_ID_ID__POS                 (0x00u)
#define `$INSTANCE_NAME`_CSD_ID_REV__POS                (0x10u)

#define `$INSTANCE_NAME`_CSD_ID_ID                      (0xFFLu << `$INSTANCE_NAME`_CSD_ID_ID__POS)
#define `$INSTANCE_NAME`_CSD_ID_REV                     (0xFFLu << `$INSTANCE_NAME`_CSD_ID_REV__POS)

/* CSD_CONFIG register fields position */
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SAMPLE_EN_POS      (0x00u)
#define `$INSTANCE_NAME`_CSD_CFG_SAMPLE_SYNC_POS        (0x01u)
#define `$INSTANCE_NAME`_CSD_CFG_FILTER_EN_POS          (0x03u)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR_POS          (0x05u)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT_POS         (0x06u)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_12_8_POS           (0x07u)
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SENSE_EN_POS       (0x08u)
#define `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY_POS       (0x09u)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW_POS      (0x0Bu)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_EN_POS           (0x0Cu)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN_POS          (0x0Du)
#define `$INSTANCE_NAME`_CSD_CFG_CHARGE_IO_POS          (0x0Eu)
#define `$INSTANCE_NAME`_CSD_CFG_COMP_PIN_POS           (0x0Fu)
#define `$INSTANCE_NAME`_CSD_CFG_POLARITY_POS           (0x10u)
#define `$INSTANCE_NAME`_CSD_CFG_MUTUAL_CAP_POS         (0x12u)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN_POS      (0x13u)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL_POS      (0x15u)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL_POS        (0x16u)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_POS             (0x17u)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTSEL_POS            (0x1Au)
#define `$INSTANCE_NAME`_CSD_CFG_ADFTEN_POS             (0x1Du)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_POS           (0x1Eu)
#define `$INSTANCE_NAME`_CSD_CFG_ENABLE_POS             (0x1Fu)

/* CSD_STATUS register fields position */
#define `$INSTANCE_NAME`_CSD_STAT_CSD_CHARGE_POS        (0x00u)
#define `$INSTANCE_NAME`_CSD_STAT_CSD_SENSE_POS         (0x01u)
#define `$INSTANCE_NAME`_CSD_STAT_COMP_OUT_POS          (0x02u)
#define `$INSTANCE_NAME`_CSD_STAT_SAMPLE_POS            (0x03u)

/* CSD_IDAC control register fields position */
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK_POS        (0x08u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED_POS       (0x08u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE_POS    (0x08u)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_DSI_POS         (0x08u)
#define `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X_POS         (0x0Au)
#define `$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK_POS        (0x00u)

#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK_POS        (0x18u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED_POS       (0x18u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE_POS    (0x18u)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_DSI_POS         (0x18u)
#define `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X_POS         (0x1Au)
#define `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK_POS        (0x10u)

/* CSD_COUNTER register fields position */
#define `$INSTANCE_NAME`_CSD_CNT_COUNTER_POS            (0x00u)
#define `$INSTANCE_NAME`_CSD_CNT_PERIOD_POS             (0x10u)

/* CSD_CONFIRG register definitions */
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SAMPLE_EN          (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_DSI_SAMPLE_EN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_SAMPLE_SYNC            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SAMPLE_SYNC_POS)
#define `$INSTANCE_NAME`_CSD_CFG_FILTER_EN              (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_FILTER_EN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR              (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR_POS)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT             (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT_POS)
#define `$INSTANCE_NAME`_CSD_CFG_PRS_12_8               (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_PRS_12_8_POS)
#define `$INSTANCE_NAME`_CSD_CFG_DSI_SENSE_EN           (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_DSI_SENSE_EN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY_MASK      (0x03Lu << `$INSTANCE_NAME`_CSD_CFG_SHIELD_DELAY_POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW          (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW_POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_EN               (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_EN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN              (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_CHARGE_IO              (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_CHARGE_IO_POS)
#define `$INSTANCE_NAME`_CSD_CFG_COMP_PIN_CH2           (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_COMP_PIN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_POLARITY_VDDIO         (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_POLARITY_POS)
#define `$INSTANCE_NAME`_CSD_CFG_MUTUAL_CAP             (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_MUTUAL_CAP_POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN          (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_EN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL          (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL_POS)
#define `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL            (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_SENSE_INSEL_POS)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_MASK            (0x03Lu << `$INSTANCE_NAME`_CSD_REFBUF_DRV_POS)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_LOW             (0x01Lu << `$INSTANCE_NAME`_CSD_REFBUF_DRV_POS)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_MEDIUM          (0x02Lu << `$INSTANCE_NAME`_CSD_REFBUF_DRV_POS)
#define `$INSTANCE_NAME`_CSD_REFBUF_DRV_HIGH            (0x03Lu << `$INSTANCE_NAME`_CSD_REFBUF_DRV_POS)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTSEL_MASK           (0x07Lu << `$INSTANCE_NAME`_CSD_CFG_DDFTSEL_POS)
#define `$INSTANCE_NAME`_CSD_CFG_ADFTEN                 (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_ADFTEN_POS)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_MASK          (0x03Lu << `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_POS)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_REFCOMP       (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_POS)
#define `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_SENSECOMP     (0x02Lu << `$INSTANCE_NAME`_CSD_CFG_DDFTCOMP_POS)
#define `$INSTANCE_NAME`_CSD_CFG_ENABLE                 (0x01Lu << `$INSTANCE_NAME`_CSD_CFG_ENABLE_POS)

/* CSD_STATUS register definitions */
#define `$INSTANCE_NAME`_CSD_STAT_CSD_CHARGE            (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_CSD_CHARGE_POS)
#define `$INSTANCE_NAME`_CSD_STAT_CSD_SENSE             (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_CSD_SENSE_POS)
#define `$INSTANCE_NAME`_CSD_STAT_COMP_OUT              (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_COMP_OUT_POS)
#define `$INSTANCE_NAME`_CSD_STAT_SAMPLE                (0x01Lu << `$INSTANCE_NAME`_CSD_STAT_SAMPLE_POS)

/* CSD_IDAC control register definitions */
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK            (0x03Lu << `$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK_POS)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED           (0x01Lu << `$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED_POS)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE        (0x02Lu << `$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE_POS)
#define `$INSTANCE_NAME`_CSD_IDAC1_MODE_DSI             (0x03Lu << `$INSTANCE_NAME`_CSD_IDAC1_MODE_DSI_POS)
#define `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X             (0x01Lu << `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X_POS)
#define `$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK            (0xFFLu << `$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK_POS)

#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK            (0x03Lu << `$INSTANCE_NAME`_CSD_IDAC2_MODE_MASK_POS)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED           (0x01Lu << `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED_POS)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE        (0x02Lu << `$INSTANCE_NAME`_CSD_IDAC2_MODE_VARIABLE_POS)
#define `$INSTANCE_NAME`_CSD_IDAC2_MODE_DSI             (0x03Lu << `$INSTANCE_NAME`_CSD_IDAC2_MODE_DSI_POS)
#define `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X             (0x01Lu << `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X_POS)
#define `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK            (0x7FLu << `$INSTANCE_NAME`_CSD_IDAC2_DATA_MASK_POS)

#define `$INSTANCE_NAME`_CSD_IDAC2_DATA_OFFSET          (16u)

#define `$INSTANCE_NAME`_CSD_IDAC1_TRIM_MASK            (0xFFFFFFF0u)
#define `$INSTANCE_NAME`_CSD_IDAC2_TRIM_MASK            (0xFFFFFF0Fu)

#define `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC1_MASK        (0x0Fu)
#define `$INSTANCE_NAME`_CSFLASH_TRIM_IDAC2_MASK        (0xF0)

#define `$INSTANCE_NAME`_CSD_4B_PWM_MODE_OFFSET         (4u)
#define `$INSTANCE_NAME`_CSD_4B_PWM_MODE_DEFAULT        (`$INSTANCE_NAME`_CSD_4B_PWM_MODE << `$INSTANCE_NAME`_CSD_4B_PWM_MODE_OFFSET)

#define `$INSTANCE_NAME`_CSD_4B_PWM_COUNT_MASK          (0x0000000Fu)
#define `$INSTANCE_NAME`_CSD_4B_PWM_MODE_MASK           (0x00000030u)

#define `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG      (`$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED |\
                                                        `$INSTANCE_NAME`_PRECHARGE_IDAC1_VAL)

/* CSD_COUNTER register definitions */
#define `$INSTANCE_NAME`_CSD_CNT_COUNTER                (0xFFLu << `$INSTANCE_NAME`_CSD_CNT_COUNTER_POS )
#define `$INSTANCE_NAME`_CSD_CNT_PERIOD                 (0xFFLu << `$INSTANCE_NAME`_CSD_CNT_PERIOD_POS)

#define `$INSTANCE_NAME`_CSD_PRS_8_BIT                  (0x00000000u)
#define `$INSTANCE_NAME`_CSD_PRS_12_BIT                 (`$INSTANCE_NAME`_CSD_CFG_PRS_12_8)
#define `$INSTANCE_NAME`_PRS_MODE_MASK                  (`$INSTANCE_NAME`_CSD_CFG_PRS_12_8)

/***************************************
*    Initial Parameter Constants
***************************************/

#if (0u != `$INSTANCE_NAME`_FILTER_ENABLE)
    #define `$INSTANCE_NAME`_DEFAULT_FILTER_STATE       (`$INSTANCE_NAME`_CSD_CFG_FILTER_EN)

#else
    #define `$INSTANCE_NAME`_DEFAULT_FILTER_STATE       (0u)

#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`_PRS_8BITS) */

#define `$INSTANCE_NAME`_DEFAULT_CSD_4B_PWM_CONFIG      (`$INSTANCE_NAME`_CSD_4B_PWM_MODE_DEFAULT | `$INSTANCE_NAME`_CSD_4B_PWM_COUNT)

/* Set PRS */
#if (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_8BITS)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT

#elif (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_12BITS)
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    (`$INSTANCE_NAME`_CSD_CFG_PRS_12_8 |\
                                                        `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT)
#else
    #define `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE    (0u)
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`_PRS_8BITS) */

/* Set IDAC ranges */
#if (`$INSTANCE_NAME`_IDAC1_RANGE_VALUE == `$INSTANCE_NAME`__IDAC_8X)
    #define `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE        `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X
    #define `$INSTANCE_NAME`_DEFAULT_IDAC2_RANGE        `$INSTANCE_NAME`_CSD_IDAC2_RANGE_8X
#else
    #define `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE        (0u)
    #define `$INSTANCE_NAME`_DEFAULT_IDAC2_RANGE        (0u)
#endif /* (`$INSTANCE_NAME`_IDAC1_RANGE_VALUE == `$INSTANCE_NAME`_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(`$INSTANCE_NAME`_IDAC1_POLARITY == `$INSTANCE_NAME`__IDAC_SINK)

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY      `$INSTANCE_NAME`_CSD_CFG_POLARITY_VDDIO
    #define `$INSTANCE_NAME`_CMOD_DR_CONFIG             `$INSTANCE_NAME`_CMOD_DR_VDDIO
    #define `$INSTANCE_NAME`_CTANK_DR_CONFIG            `$INSTANCE_NAME`_CTANK_DR_VDDIO
#else

    #define `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY      (0u)
    #define `$INSTANCE_NAME`_CMOD_DR_CONFIG             `$INSTANCE_NAME`_CMOD_DR_VSSIO
    #define `$INSTANCE_NAME`_CTANK_DR_CONFIG            `$INSTANCE_NAME`_CTANK_DR_VSSIO
#endif /* (`$INSTANCE_NAME`_IDAC_OPTIONS == `$INSTANCE_NAME`_IDAC_SINK) */

#define `$INSTANCE_NAME`_SNS_GROUND_CONNECT             (6u)
#define `$INSTANCE_NAME`_SNS_HIZANALOG_CONNECT          (0u)

/* Inactive sensors connection configuration */
#if (`$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__GROUND)
    #define `$INSTANCE_NAME`_CSD_INACTIVE_CONNECT       (`$INSTANCE_NAME`_SNS_GROUND_CONNECT)
#else
    #define `$INSTANCE_NAME`_CSD_INACTIVE_CONNECT       (`$INSTANCE_NAME`_SNS_HIZANALOG_CONNECT)
#endif /* `$INSTANCE_NAME`_CONNECT_INACTIVE_SNS == `$INSTANCE_NAME`__GROUND */

#if(`$INSTANCE_NAME`_IS_SHIELD_ENABLE)
    #define `$INSTANCE_NAME`_SHIELD_PORT_NUMBER `$INSTANCE_NAME`_Shield__PORT
    #define `$INSTANCE_NAME`_SHIELD_PIN_NUMBER  `$INSTANCE_NAME`_Shield__SHIFT
#endif /* (`$INSTANCE_NAME`_IS_SHIELD_ENABLE) */

/* Defining default CSD configuration according to settings in customizer. */
#define `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG             (`$INSTANCE_NAME`_DEFAULT_FILTER_STATE |\
                                                         `$INSTANCE_NAME`_DEFAULT_MODULATION_MODE |\
                                                         `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW |\
                                                         `$INSTANCE_NAME`_DEFAULT_IDAC_POLARITY |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL |\
                                                         `$INSTANCE_NAME`_CSD_REFBUF_DRV_HIGH)

#define `$INSTANCE_NAME`_CSD_CONFIG_MASK                (`$INSTANCE_NAME`_CSD_CFG_FILTER_EN |\
                                                         `$INSTANCE_NAME`_CSD_CFG_PRS_SELECT |\
                                                         `$INSTANCE_NAME`_CSD_CFG_PRS_12_8 |\
                                                         `$INSTANCE_NAME`_CSD_CFG_SENSE_COMP_BW |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL |\
                                                         `$INSTANCE_NAME`_CSD_CFG_POLARITY_VDDIO |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL  |\
                                                         `$INSTANCE_NAME`_CSD_REFBUF_DRV_MASK)


/* Defining the default IDACs configuration according to settings in customizer. */
#if (`$INSTANCE_NAME`_IDAC_CNT == 1u)
    #define `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG    (`$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE |\
                                                             `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE)
#else
    #define `$INSTANCE_NAME`_DEFAULT_CSD_IDAC_CONFIG    (`$INSTANCE_NAME`_CSD_IDAC1_MODE_VARIABLE |\
                                                             `$INSTANCE_NAME`_CSD_IDAC2_MODE_FIXED |\
                                                             `$INSTANCE_NAME`_DEFAULT_IDAC1_RANGE |\
                                                             `$INSTANCE_NAME`_DEFAULT_IDAC2_RANGE)
#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 1u) */

/* Defining mask intended for clearing bits related to pre-charging options. */
#define `$INSTANCE_NAME`_PRECHARGE_CONFIG_MASK          (`$INSTANCE_NAME`_CSD_CFG_REFBUF_EN |\
                                                         `$INSTANCE_NAME`_CSD_CFG_CHARGE_IO |\
                                                         `$INSTANCE_NAME`_CSD_CFG_COMP_PIN_CH2  |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL)

/* Cmod the precharge mode configuration */
#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG      (`$INSTANCE_NAME`_CSD_CFG_REFBUF_EN |\
                                                         `$INSTANCE_NAME`_CSD_CFG_COMP_PIN_CH2)

#else

    #define `$INSTANCE_NAME`_CMOD_PRECHARGE_CONFIG      (`$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN |\
                                                         `$INSTANCE_NAME`_CSD_CFG_CHARGE_IO)

#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF) */

/* Ctank the precharge mode configuration */
#if(`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)

    #if(0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE)
        #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG    (`$INSTANCE_NAME`_CSD_CFG_REFBUF_EN |\
                                                             `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR |\
                                                             `$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL)
    #else
        #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG    (`$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL |\
                                                             `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR)
    #endif /* (0u != `$INSTANCE_NAME`_IS_SHIELD_ENABLE) */

#else

    #define  `$INSTANCE_NAME`_CTANK_PRECHARGE_CONFIG    (`$INSTANCE_NAME`_CSD_CFG_REFBUF_OUTSEL |\
                                                         `$INSTANCE_NAME`_CSD_CFG_REFBUF_EN |\
                                                         `$INSTANCE_NAME`_CSD_CFG_CHARGE_IO |\
                                                         `$INSTANCE_NAME`_CSD_CFG_PRS_CLEAR |\
                                                         `$INSTANCE_NAME`_CSD_CFG_COMP_PIN_CH2)
#endif /* (`$INSTANCE_NAME`_CSH_TANK_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRIOBUF) */

#define `$INSTANCE_NAME`_MAX_UINT_8                     (0xFFu)
#define `$INSTANCE_NAME`_MAX_UINT_16                    (0xFFFFu)
#define `$INSTANCE_NAME`_MAX_UINT_32                    (0xFFFFFFFFLu)

/***************************************
*     Vars with External Linkage
***************************************/
/* SmartSense functions */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    extern uint8 `$INSTANCE_NAME`_lowLevelTuningDone;
    extern uint8 `$INSTANCE_NAME`_scanSpeedTbl[((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u];
    extern void `$INSTANCE_NAME`_AutoTune(void);
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

#if(`$INSTANCE_NAME`_PRS_OPTIONS != `$INSTANCE_NAME`__PRS_NONE)
    extern uint8 `$INSTANCE_NAME`_prescalersTuningDone;
#endif /* (`$INSTANCE_NAME`_PRS_OPTIONS == `$INSTANCE_NAME`__PRS_NONE) */

/* Global software variables */
extern volatile uint8 `$INSTANCE_NAME`_csdStatusVar;
extern volatile uint8 `$INSTANCE_NAME`_sensorIndex;
extern uint16 `$INSTANCE_NAME`_sensorRaw[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
extern uint8 `$INSTANCE_NAME`_unscannedSnsDriveMode[`$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE];
extern uint8 `$INSTANCE_NAME`_sensorEnableMaskBackup[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];
extern uint8 `$INSTANCE_NAME`_sensorEnableMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK];

#if ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) || (0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE))
    extern uint8 `$INSTANCE_NAME`_modulationIDAC[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    extern uint8 `$INSTANCE_NAME`_compensationIDAC[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
#else
    extern const uint8 `$INSTANCE_NAME`_modulationIDAC[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    extern const uint8 `$INSTANCE_NAME`_compensationIDAC[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
#endif /* ((`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE) || (0u != `$INSTANCE_NAME`_AUTOCALIBRATION_ENABLE)) */

#if (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)
    extern uint32 `$INSTANCE_NAME`_widgetResolution[`$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE];
    #if (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
        extern uint8 `$INSTANCE_NAME`_senseClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
        extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
    #else
        extern uint8 `$INSTANCE_NAME`_senseClkDividerVal;
        extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal;
    #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
#else
    extern const uint32 `$INSTANCE_NAME`_widgetResolution[`$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE];
    #if (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET)
        extern const uint8 `$INSTANCE_NAME`_senseClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
        extern const uint8 `$INSTANCE_NAME`_sampleClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
    #else
        extern const uint8 `$INSTANCE_NAME`_senseClkDividerVal;
        extern const uint8 `$INSTANCE_NAME`_sampleClkDividerVal;
    #endif /* (0u != `$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) */
#endif /* (`$INSTANCE_NAME`_TUNING_METHOD != `$INSTANCE_NAME`__TUNING_NONE)  */

extern const uint8 `$INSTANCE_NAME`_widgetNumber[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

extern reg32* const `$INSTANCE_NAME`_prtSelTbl[`$INSTANCE_NAME`_CFG_REG_TBL_SIZE];
extern reg32* const `$INSTANCE_NAME`_prtCfgTbl[`$INSTANCE_NAME`_CFG_REG_TBL_SIZE];
extern reg32* const `$INSTANCE_NAME`_prtDRTbl[`$INSTANCE_NAME`_CFG_REG_TBL_SIZE];
extern reg32 * `$INSTANCE_NAME`_pcTable[`$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE];

extern const uint8  `$INSTANCE_NAME`_portTable[`$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint32 `$INSTANCE_NAME`_maskTable[`$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE];
extern const uint8  `$INSTANCE_NAME`_pinShiftTbl[`$INSTANCE_NAME`_PORT_PIN_CONFIG_TBL_ZISE];

#if (0u != `$INSTANCE_NAME`_INDEX_TABLE_SIZE)
extern const uint8 CYCODE `$INSTANCE_NAME`_indexTable[`$INSTANCE_NAME`_INDEX_TABLE_SIZE];
#endif /* (0u != `$INSTANCE_NAME`_INDEX_TABLE_SIZE)) */

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  `$INSTANCE_NAME`_PrescalersTuningDone         `$INSTANCE_NAME`_prescalersTuningDone
#define  `$INSTANCE_NAME`_SensorRaw                    `$INSTANCE_NAME`_sensorRaw
#define  `$INSTANCE_NAME`_PRSResolutionTbl             `$INSTANCE_NAME`_prsResolutionTbl
#define  `$INSTANCE_NAME`_SensorEnableMask             `$INSTANCE_NAME`_sensorEnableMask
#define  `$INSTANCE_NAME`_Clk1DividerVal               `$INSTANCE_NAME`_senseClkDividerVal
#define  `$INSTANCE_NAME`_Clk2DividerVal               `$INSTANCE_NAME`_sampleClkDividerVal
#define  `$INSTANCE_NAME`_PrtSelTbl                    `$INSTANCE_NAME`_prtSelTbl
#define  `$INSTANCE_NAME`_PrtCfgTbl                    `$INSTANCE_NAME`_prtCfgTbl
#define  `$INSTANCE_NAME`_PrtDRTbl                     `$INSTANCE_NAME`_prtDRTbl
#define  `$INSTANCE_NAME`_idac1Settings                `$INSTANCE_NAME`_modulationIDAC
#define  `$INSTANCE_NAME`_idac2Settings                `$INSTANCE_NAME`_compensationIDAC

#endif /* CY_CAPSENSE_CSD_`$INSTANCE_NAME`_H */


 /* [] END OF FILE */
