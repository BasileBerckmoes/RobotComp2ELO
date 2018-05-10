/*******************************************************************************
* File Name: `$INSTANCE_NAME`_BIST.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the Built In Self Test APIs
*  for the CapSesne CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CSD_BIST_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_BIST_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/* Init Idac current */
#define `$INSTANCE_NAME`_TURN_OFF_IDAC                      (0x00u)
#define `$INSTANCE_NAME`_PRECHARGE_IDAC1_VAL                (0xFAu)

/* Definition of time interval long enough for charging 100nF capacitor */
#define `$INSTANCE_NAME`_MAX_CHARGE_TIME_US                 (100u)
#define `$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP                (5u)
#define `$INSTANCE_NAME`_PRECHARGE_WATCHDOG_CYCLES_NUM      (((CYDEV_BCLK__SYSCLK__MHZ) * (`$INSTANCE_NAME`_MAX_CHARGE_TIME_US)) /\
                                                            (`$INSTANCE_NAME`_AVG_CYCLES_PER_LOOP))

#define `$INSTANCE_NAME`_SCANNING_RESOLUTION                (`$INSTANCE_NAME`_RESOLUTION_12_BITS)
#define `$INSTANCE_NAME`_RAW_DATA_MAX                       (`$INSTANCE_NAME`_SCANNING_RESOLUTION >> `$INSTANCE_NAME`_RESOLUTION_OFFSET)

#define `$INSTANCE_NAME`_CALIBRATION_COUNT                  ((`$INSTANCE_NAME`_RAW_DATA_MAX * 15u) / 100u)
#define `$INSTANCE_NAME`_CALIBRATION_ERROR                  ((`$INSTANCE_NAME`_CALIBRATION_COUNT * 15u) / 100u)
#define `$INSTANCE_NAME`_CALIBRATION_ERROR_TOP              (`$INSTANCE_NAME`_CALIBRATION_COUNT + `$INSTANCE_NAME`_CALIBRATION_ERROR)
#define `$INSTANCE_NAME`_CALIBRATION_ERROR_BOT              (`$INSTANCE_NAME`_CALIBRATION_COUNT - `$INSTANCE_NAME`_CALIBRATION_ERROR)

#define `$INSTANCE_NAME`_CHARGE_VALIDATION_COUNT            ((`$INSTANCE_NAME`_RAW_DATA_MAX * 30u) / 100u)
#define `$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR            ((`$INSTANCE_NAME`_CHARGE_VALIDATION_COUNT * 15u) / 100u)
#define `$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR_TOP        (`$INSTANCE_NAME`_CHARGE_VALIDATION_COUNT + `$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR)
#define `$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR_BOT        (`$INSTANCE_NAME`_CHARGE_VALIDATION_COUNT - `$INSTANCE_NAME`_CHARGE_VALIDATION_ERROR)

#define `$INSTANCE_NAME`_SENSE_CLK_DIV_MIN                  (2u)
#define `$INSTANCE_NAME`_SENSE_CLK_DIV_MAX                  (64u)

#if(CYDEV_BCLK__HFCLK__MHZ >= 24u)
    #define `$INSTANCE_NAME`_SAMPLE_CLK_DIV                 (CYDEV_BCLK__HFCLK__MHZ / 12u)
#else
    #define `$INSTANCE_NAME`_SAMPLE_CLK_DIV                 (2u)
#endif /* (CYDEV_BCLK__HFCLK__MHZ >= 24u) */

#define `$INSTANCE_NAME`_CALIBRATION_SUCCESS                (0u)
#define `$INSTANCE_NAME`_CALIBRATION_FAIL                   (1u)

#define `$INSTANCE_NAME`_VALIDATION_SUCCESS                 (0u)
#define `$INSTANCE_NAME`_VALIDATION_FAIL                    (1u)

#define `$INSTANCE_NAME`_SENSITIVITY_COEFFICIENT            ((CYDEV_BCLK__HFCLK__MHZ * `$INSTANCE_NAME`_RAW_DATA_MAX) / 2u)

#define `$INSTANCE_NAME`_CP_MEASURE_MAX_VAL                 (200u)
#define `$INSTANCE_NAME`_AVG_SAMPLES_NUM                    (1u)

#define `$INSTANCE_NAME`_IDAC1_MAX_VAL                      (0xF8u)

/***********************************************************
*   Defining the CSD block configuration:
*   Precharging source                 - Prescaler          CSD_CONFIG[6]     = 0
*   Sense comparator bandwidth         - Low                CSD_CONFIG[11]    = 0
*   Modulator output state             - Enabled            CSD_CONFIG[12]    = 1
*   Reference buffer                   - Enabled            CSD_CONFIG[13]    = 1
*   Comparator mode                    - Connected to AMUX  CSD_CONFIG[14]    = 0
*   IDAC polarity                      - Sourcing           CSD_CONFIG[16]    = 0
*   CSD block mode                     - Selfcap            CSD_CONFIG[18]    = 0
*   Sense comparator state             - Enabled            CSD_CONFIG[19]    = 1
*   Vref buffer output connection      - AMUX_A             CSD_CONFIG[21]    = 0
*   Sense input select                 - SENSE_AMUXA        CSD_CONFIG[22]    = 1
*   Vref buffer current drive strength - DRV_3              CSD_CONFIG[24:23] = 11
*   CSD block state                    - Enabled            CSD_CONFIG[31]    = 1
************************************************************/
#define `$INSTANCE_NAME`_CP_PRECHARGE_CONFIG   (0x81C83000u)


/***********************************************************
*   Defining the CSD block configuration:
*   Precharging source                 - Prescaler         CSD_CONFIG[6]     = 0
*   Sense comparator bandwidth         - High              CSD_CONFIG[11]    = 1
*   Modulator output state             - Enabled           CSD_CONFIG[12]    = 1
*   Reference buffer                   - Enabled           CSD_CONFIG[13]    = 1
*   Comparator mode                    - Connected to AMUX CSD_CONFIG[14]    = 0
*   IDAC polarity                      - Sourcing          CSD_CONFIG[16]    = 0
*   CSD block mode                     - Selfcap           CSD_CONFIG[18]    = 0
*   Sense comparator state             - Enabled           CSD_CONFIG[19]    = 1
*   Vref buffer output connection      - AMUX_B            CSD_CONFIG[21]    = 1
*   Sense input select                 - SENSE_AMUXA       CSD_CONFIG[22]    = 1
*   Vref buffer current drive strength - DRV_3             CSD_CONFIG[24:23] = 11
*   CSD block state                    - Enabled           CSD_CONFIG[31]    = 1
************************************************************/
#define `$INSTANCE_NAME`_CP_SCANNING_CONFIG   (0x81E83800u)

/********************************************************************************
*           API Constants related to the `$INSTANCE_NAME`_MeasureCmod() function.
*********************************************************************************/

#define `$INSTANCE_NAME`_CMOD_MEASURE_AVG_SAMPLES_NUM       (2u)
#define `$INSTANCE_NAME`_CTANK_MEASURE_AVG_SAMPLES_NUM      (2u)

/* 8-bit IDAC value that used for CMOD capacitance measurement */
#define `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_VAL              (0x0000000Fu)
#define `$INSTANCE_NAME`_CTANK_MEASURE_IDAC_VAL             (0x0000000Fu)

/* Definition of scanning resolution for CMOD capacitance measurement */
#define `$INSTANCE_NAME`_CMOD_MEASURE_RES                   (`$INSTANCE_NAME`_RESOLUTION_12_BITS)
#define `$INSTANCE_NAME`_CMOD_MEASURE_RES_MAX               (`$INSTANCE_NAME`_CMOD_MEASURE_RES >> `$INSTANCE_NAME`_RESOLUTION_OFFSET)

/* Definition scanning resolution for CTANK capacitance measurement */
#define `$INSTANCE_NAME`_CTANK_MEASURE_RES                  (`$INSTANCE_NAME`_RESOLUTION_12_BITS)
#define `$INSTANCE_NAME`_CTANK_MEASURE_RES_MAX              (`$INSTANCE_NAME`_CTANK_MEASURE_RES >> `$INSTANCE_NAME`_RESOLUTION_OFFSET)

/* All values greater than 95% of max duty cycle are treated as saturation - CMOD is shorted to GND */
#define `$INSTANCE_NAME`_HIGH_CP_MEASURE_MAX_VAL            (((`$INSTANCE_NAME`_HIGH_CP_MEASURE_RES_MAX / 2u) * 95u) / 100u)

/* Defining the CSD block configuration:
*   Precharging source                 - Prescaler         CSD_CONFIG[6]     = 0
*   Sense comparator bandwidth         - High              CSD_CONFIG[11]    = 0
*   Modulator output state             - Enabled           CSD_CONFIG[12]    = 1
*   Reference buffer                   - Enabled           CSD_CONFIG[13]    = 0
*   Comparator mode                    - Connected to AMUX CSD_CONFIG[14]    = 0
*   IDAC polarity                      - Sourcing          CSD_CONFIG[16]    = 0
*   CSD block mode                     - Selfcap           CSD_CONFIG[18]    = 0
*   Sense comparator state             - Enabled           CSD_CONFIG[19]    = 1
*   Vref buffer output connection      - AMUX_B            CSD_CONFIG[21]    = 1
*   Sense input select                 - SENSE_AMUXA       CSD_CONFIG[22]    = 1
*   Vref buffer current drive strength - DRV_3             CSD_CONFIG[24:23] = 11
*   CSD block state                    - Enabled           CSD_CONFIG[31]    = 1
*/
#define `$INSTANCE_NAME`_HIGH_CP_MEASURE_CSD_CONFIG     (0x81E81000u)

/* Defining IDACs configuration:
*   IDAC1 mode  - Fixed
*   IDAC2 mode  - Off
*   IDAC1 range - 4X
*   IDAC2 range - 4X
*/
#define `$INSTANCE_NAME`_HIGH_CP_MEASURE_IDAC_CONFIG        (`$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED)
#define `$INSTANCE_NAME`_IDAC1_CONFIG_MASK                  (`$INSTANCE_NAME`_CSD_IDAC1_MODE_MASK | `$INSTANCE_NAME`_CSD_IDAC1_RANGE_8X |\
                                                                                                `$INSTANCE_NAME`_CSD_IDAC1_DATA_MASK)


#if (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV     (65025u)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_SAMPLE_CLK_DIV    (255u)
#else
    #define `$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV     (255u)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_SAMPLE_CLK_DIV    (255u)
#endif  /* (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

#if (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
    #define `$INSTANCE_NAME`_CTANK_MEASURE_SENSE_CLK_DIV    (65025u)
    #define `$INSTANCE_NAME`_CTANK_MEASURE_SAMPLE_CLK_DIV   (255u)
#else
    #define `$INSTANCE_NAME`_CTANK_MEASURE_SENSE_CLK_DIV    (255u)
    #define `$INSTANCE_NAME`_CTANK_MEASURE_SAMPLE_CLK_DIV   (255u)
#endif  /* (0u != `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

#define `$INSTANCE_NAME`_FULL_DIVIDER                       (65025Lu * 2Lu)


uint32 `$INSTANCE_NAME`_GetSensorCp(uint32 sensor);
uint32 `$INSTANCE_NAME`_MeasureCShield(void);

uint32 `$INSTANCE_NAME`_MeasureCmod(void);
uint32 `$INSTANCE_NAME`_MeasureCShieldTank(void);

#endif /* CY_CAPSENSE_CSD_BIST_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
