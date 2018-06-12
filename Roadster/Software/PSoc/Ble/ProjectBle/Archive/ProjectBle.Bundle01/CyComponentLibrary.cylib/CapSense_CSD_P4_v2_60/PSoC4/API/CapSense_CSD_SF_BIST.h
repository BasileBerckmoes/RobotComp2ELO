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

#define `$INSTANCE_NAME`_CAL_11BIT_COUNT        (1740u)
#define `$INSTANCE_NAME`_RESOLUTION_OFFSET      (16u)
#define `$INSTANCE_NAME`_CP_MEASURE_RES         (`$INSTANCE_NAME`_RESOLUTION_12_BITS)
#define `$INSTANCE_NAME`_CP_MEASURE_RES_MAX     (`$INSTANCE_NAME`_CP_MEASURE_RES >> `$INSTANCE_NAME`_RESOLUTION_OFFSET)

#define `$INSTANCE_NAME`_DESIRED_SENSE_CLK_MHZ  (3u)
#define `$INSTANCE_NAME`_SAMPLE_MEASURING_DIV   (2u)

#if(CYDEV_BCLK__HFCLK__MHZ >= 12u)
    #define `$INSTANCE_NAME`_SENSE_MEASURING_DIV    (CYDEV_BCLK__HFCLK__MHZ / `$INSTANCE_NAME`_DESIRED_SENSE_CLK_MHZ)
#else
    #define `$INSTANCE_NAME`_SENSE_MEASURING_DIV    (2u)
#endif /* (CYDEV_BCLK__HFCLK__MHZ >= 12u) */

#define `$INSTANCE_NAME`_AVR_SAMPLES            (1u)
#define `$INSTANCE_NAME`_IDAC1_MAX_VAL          (0xF8u)

#define `$INSTANCE_NAME`_CP_FACTOR             ((1u + `$INSTANCE_NAME`_CHAINED_CLOCKS) * `$INSTANCE_NAME`_SENSE_MEASURING_DIV \
                                                  * `$INSTANCE_NAME`_SAMPLE_MEASURING_DIV)
#define `$INSTANCE_NAME`_CP_DIVIDER            (CYDEV_BCLK__HFCLK__MHZ * (`$INSTANCE_NAME`_CP_MEASURE_RES >> \
                                                                          `$INSTANCE_NAME`_RESOLUTION_OFFSET))

/***********************************************************
    Defining the CSD block configuration:
    Precharging source                 - Prescaler
    Sense comparator bandwidth         - Low
    Modulator output state             - Enabled
    Reference buffer                   - Enabled
    Comparator mode                    - Connected to AMUX
    IDAC polarity                      - Sourcing
    CSD block mode                     - Selfcap
    Sense comparator state             - Enabled
    Vref buffer output connection      - AMUX_A
    Vref buffer current drive strength - OFF
    CSD block state                    - Enabled
************************************************************/
#define `$INSTANCE_NAME`_CP_PRECHARGE_CONFIG   (0x81C83000u)


/***********************************************************
    Defining the CSD block configuration:
    Precharging source                 - Prescaler
    Sense comparator bandwidth         - High
    Modulator output state             - Enabled
    Reference buffer                   - Enabled
    Comparator mode                    - Connected to AMUX
    IDAC polarity                      - Sourcing
    CSD block mode                     - Selfcap
    Sense comparator state             - Enabled
    Vref buffer output connection      - AMUX_B
    Vref buffer current drive strength - DRV_3
    CSD block state                    - Enabled
************************************************************/
#if(`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF)
    #define `$INSTANCE_NAME`_CP_SCANNING_CONFIG   (0x81E83800u)
#else
    #define `$INSTANCE_NAME`_CP_SCANNING_CONFIG   (0x81E87800u)
#endif /* (`$INSTANCE_NAME`_CMOD_PREGARGE_OPTION == `$INSTANCE_NAME`__CAPPRVREF) */

/********************************************************************************
*           API Constants related to the `$INSTANCE_NAME`_MeasureCmod() function.
*********************************************************************************/
#if (0u == CY_PSOC4SF)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV     (255u)
#else
    #define `$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV     (65535u)
#endif /* (0u == CY_PSOC4SF) */

#define `$INSTANCE_NAME`_CMOD_MEASURE_SAMPLE_CLK_DIV    (255u)

#define `$INSTANCE_NAME`_CMOD_MEASURE_AVG_SAMPLES_NUM   (2u)

/* 8-bit IDAC value that used for CMOD capacitance measurement */
#define `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_VAL          (0x0000000Fu)

/* Definition of scanning resolution for CMOD capacitance measurement */
#define `$INSTANCE_NAME`_CMOD_MEASURE_RES               (`$INSTANCE_NAME`_RESOLUTION_12_BITS)
#define `$INSTANCE_NAME`_CMOD_MEASURE_RES_MAX           (`$INSTANCE_NAME`_CMOD_MEASURE_RES >> `$INSTANCE_NAME`_RESOLUTION_OFFSET)
/* All values greater than 95% of max duty cycle are treated as saturation - CMOD is shorted to GND */
#define `$INSTANCE_NAME`_CMOD_MEASURE_MAX_VAL           (((`$INSTANCE_NAME`_CMOD_MEASURE_RES_MAX / 2u) * 95u) / 100u)

/* Defining the CSD block configuration:
    Precharging source                 - Prescaler
    Sense comparator bandwidth         - Low
    Modulator output state             - Enabled
    Reference buffer                   - Disabled
    Comparator mode                    - Connected to AMUX
    IDAC polarity                      - Sourcing
    CSD block mode                     - Selfcap
    Sense comparator state             - Enabled
    Vref buffer output connection      - AMUXB
    Vref buffer current drive strength - OFF
    CSD block state                    - Enabled
*/
#define `$INSTANCE_NAME`_CMOD_MEASURE_CSD_CONFIG        (0x81E81000u)

/* Defining IDACs configuration:
    IDAC1 mode  - Fixed
    IDAC2 mode  - Off
    IDAC1 range - 4X
    IDAC2 range - 4X
*/
#define `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_CONFIG       (`$INSTANCE_NAME`_CSD_IDAC1_MODE_FIXED |\
                                                         `$INSTANCE_NAME`_CMOD_MEASURE_IDAC_VAL)

#if (0u == CY_PSOC4SF)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_HSIOM_MASK        (0x00000F00u)

    #define `$INSTANCE_NAME`_CMOD_MEASURE_HSIOM_CONFIG      (0x00000400u)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_PORT_MODE_MASK    (0x000001C0u)
#else
    #define `$INSTANCE_NAME`_CMOD_MEASURE_HSIOM_MASK        (0x000F0000u)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_HSIOM_CONFIG      (0x00040000u)
    #define `$INSTANCE_NAME`_CMOD_MEASURE_PORT_MODE_MASK    (0x00000E00u)
#endif  /* (0u == CY_PSOC4SF) */

#if (0u == CY_PSOC4SF)
    #define `$INSTANCE_NAME`_FULL_DIVIDER ((uint32)`$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV * \
                                      (uint32)`$INSTANCE_NAME`_CMOD_MEASURE_SAMPLE_CLK_DIV * 2u)
#else
    #define `$INSTANCE_NAME`_FULL_DIVIDER ((uint32)`$INSTANCE_NAME`_CMOD_MEASURE_SENSE_CLK_DIV * 2u)
#endif  /* (0u == CY_PSOC4SF) */

#define `$INSTANCE_NAME`_CMOD_CAP_COEFICIENT (CYDEV_BCLK__HFCLK__MHZ * (`$INSTANCE_NAME`_CMOD_MEASURE_RES >> \
                                                                        `$INSTANCE_NAME`_RESOLUTION_OFFSET))

uint32 `$INSTANCE_NAME`_GetSensorCp(uint32 sensor);
uint32 `$INSTANCE_NAME`_MeasureCmod(void);

#endif /* CY_CAPSENSE_CSD_BIST_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
