/***************************************************************************//**
* \file `$INSTANCE_NAME`_SelfTest.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the source code for the Built-In Self-Test library.
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

#include "syslib/cy_syslib.h"
#include <stddef.h>
#include "cyfitter_sysint_cfg.h"
#include "`$INSTANCE_NAME`_ModClk.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#include "`$INSTANCE_NAME`_SelfTest.h"

/***********************************************************************************************************************
* Local definition
***********************************************************************************************************************/
#define `$INSTANCE_NAME`_TST_CRC_GROUP_EN                       (`$INSTANCE_NAME`_TST_GLOBAL_CRC_EN || \
                                                                 `$INSTANCE_NAME`_TST_WDGT_CRC_EN)

#define `$INSTANCE_NAME`_TST_BASELINE_GROUP_EN                  (`$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN || \
                                                                 `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN)

#define `$INSTANCE_NAME`_TST_HW_GROUP_EN                        (`$INSTANCE_NAME`_TST_SHORT_GROUP_EN || \
                                                                 `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN)

#define `$INSTANCE_NAME`_TST_SHORT_GROUP_EN                     (`$INSTANCE_NAME`_TST_SNS_SHORT_EN || \
                                                                 `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)

#define `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN               (`$INSTANCE_NAME`_TST_SNS_CAP_EN || \
                                                                 `$INSTANCE_NAME`_TST_SH_CAP_EN || \
                                                                 `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)

#define `$INSTANCE_NAME`_TST_SW_WATCHDOG_CYCLES_NUM             (0x0000FFFFLu)

/***********************************************************************************************************************
* Definition of IO register modes
***********************************************************************************************************************/
/* Port Select HSIOM Register */
#define `$INSTANCE_NAME`_TST_HSIOM_GPIO                         (HSIOM_SEL_GPIO)
#define `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE                    (HSIOM_SEL_ACT_3)
#define `$INSTANCE_NAME`_TST_HSIOM_CSD_SHIELD                   (HSIOM_SEL_ACT_2)
#define `$INSTANCE_NAME`_TST_HSIOM_AMUXA                        (HSIOM_SEL_AMUXA)
#define `$INSTANCE_NAME`_TST_HSIOM_AMUXB                        (HSIOM_SEL_AMUXB)

/* Port Configuration Register */
#define `$INSTANCE_NAME`_TST_PC_HIGHZA                          (CY_GPIO_DM_ANALOG)
#define `$INSTANCE_NAME`_TST_PC_PULLUP_IN_ON                    (CY_GPIO_DM_PULLUP)
#define `$INSTANCE_NAME`_TST_PC_PULLUP_IN_OFF                   (CY_GPIO_DM_PULLUP_IN_OFF)
#define `$INSTANCE_NAME`_TST_PC_PULLDOWN_IN_ON                  (CY_GPIO_DM_PULLDOWN)
#define `$INSTANCE_NAME`_TST_PC_PULLDOWN_IN_OFF                 (CY_GPIO_DM_PULLDOWN_IN_OFF)
#define `$INSTANCE_NAME`_TST_PC_STRONG_IN_ON                    (CY_GPIO_DM_STRONG)
#define `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF                   (CY_GPIO_DM_STRONG_IN_OFF)

/* Port Data Register */
#define `$INSTANCE_NAME`_TST_DR_PIN2GND                         (0Lu)
#define `$INSTANCE_NAME`_TST_DR_PIN2VDD                         (1Lu)

/* Defining the drive mode of pins depending on the Inactive sensor connection setting in the Component customizer. */
#if(`$INSTANCE_NAME`_SNS_CONNECTION_GROUND == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
    #define `$INSTANCE_NAME`_TST_INACTIVE_SNS_GPIO_DM               (CY_GPIO_DM_STRONG)
#elif(`$INSTANCE_NAME`_SNS_CONNECTION_HIGHZ == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
    #define `$INSTANCE_NAME`_TST_INACTIVE_SNS_GPIO_DM               (CY_GPIO_DM_ANALOG)
#elif(`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
    #define `$INSTANCE_NAME`_TST_INACTIVE_SNS_GPIO_DM               (CY_GPIO_DM_STRONG_IN_OFF)
#else
    #error "Unsupported inactive connection for the inactive sensors."
#endif /* (CS_123_SNS_CONNECTION_GROUND == CS_123_CSD_INACTIVE_SNS_CONNECTION) */

/***************************************************************************//**
* \brief Defines Self-test HW Configuration
*
* \detail
* Defines the HW configuration depended on the test type. It includes the
* HW CSD block configuration, clock configuration, IDAC configuration and
* all electrode configuration.
*
*******************************************************************************/
typedef enum
{
    `$INSTANCE_NAME`_BIST_HW_UNDEFINED_E        = 0x00u,
    `$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E        = 0x01u,
    `$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E        = 0x02u,
    `$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E      = 0x03u,
    `$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E      = 0x04u,
    `$INSTANCE_NAME`_BIST_HW_SH_CAP_E           = 0x05u,
    `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E          = 0x06u,
    `$INSTANCE_NAME`_BIST_HW_VDDA_E             = 0x07u
} `$INSTANCE_NAME`_BIST_HW_CONFIG_ENUM;

/***************************************************************************//**
* \brief Defines Self Test IO Configuration
*
* \detail
* Defines the IO configuration depends on the test type.
*
*******************************************************************************/
typedef enum
{
    /*
    * The previous state
    */
    `$INSTANCE_NAME`_BIST_IO_UNDEFINED_E        = 0x00u,
    /*
    * Sensor2Sensor Short
    * Sensor capacitance measurement of CSX widget
    */
    `$INSTANCE_NAME`_BIST_IO_STRONG_E           = 0x01u,
    /*
    * Sensor Short
    * Ext capacitor measurement
    */
    `$INSTANCE_NAME`_BIST_IO_HIGHZA_E           = 0x02u,
    /*
    * Sensor capacitance measurement of CSD widget:
    *     All CSX sensors are set to Strong
    *     All CSD sensors depends on Inactive sensor parameter and could be:
    *       High-Z Analog | Strong | CSD_Shield
    */
    `$INSTANCE_NAME`_BIST_IO_CSD_E              = 0x03u,
    /*
    * Shield capacitance measurement
    *     All CSX sensors is set to Strong
    *     All CSD sensors depends on Inactive sensor parameter and could be:
    *     High-Z Analog | Strong | CSD_Sense
    */
    `$INSTANCE_NAME`_BIST_IO_SHIELD_E           = 0x04u
} `$INSTANCE_NAME`_BIST_IO_CONFIG_ENUM;

/***********************************************************************************************************************
* Local variables
***********************************************************************************************************************/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
static `$INSTANCE_NAME`_BIST_HW_CONFIG_ENUM `$INSTANCE_NAME`_bistHwConfig = `$INSTANCE_NAME`_BIST_HW_UNDEFINED_E;
static `$INSTANCE_NAME`_BIST_IO_CONFIG_ENUM `$INSTANCE_NAME`_bistIoConfig = `$INSTANCE_NAME`_BIST_IO_UNDEFINED_E;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN)
    static volatile uint16 `$INSTANCE_NAME`_bistRawcount;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN) */

/***********************************************************************************************************************
* Static function prototypes
***********************************************************************************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/

/* CRC group function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
    static uint32 `$INSTANCE_NAME`_CheckAllWidgetCRC(void);
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_CRC_GROUP_EN)
    static uint16 `$INSTANCE_NAME`_DsCalculateCrc16(uint8 *ptrData, uint32 len);
#endif

/* Baseline group function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
    static uint32 `$INSTANCE_NAME`_CheckAllBaselineDuplication(void);
#endif

/* Sensor short test function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
    static uint32 `$INSTANCE_NAME`_CheckAllSensorShort(void);
    static void `$INSTANCE_NAME`_UpdateTestResultSnsShort(uint32 wdgtId, uint32 snsId);
    static uint32 `$INSTANCE_NAME`_ExecuteSnsShort(uint32 wdgtId, uint32 snsId);
    static uint32 `$INSTANCE_NAME`_ExecuteSnsShortExt(uint32 wdgtId, uint32 ioSnsId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */

/* Sensor to sensor test function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
    static uint32 `$INSTANCE_NAME`_CheckAllSns2SnsShort(void);
    static void `$INSTANCE_NAME`_UpdateTestResultSns2SnsShort(uint32 wdgtId, uint32 snsId);
    static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShort(uint32 wdgtId, uint32 snsId);
    static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(uint32 wdgtId, uint32 ioSnsId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */

/* Short group function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SHORT_GROUP_EN)
    static uint32 `$INSTANCE_NAME`_ReadElectrodeState(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SHORT_GROUP_EN) */

/* Shield capacitance measurement test function prototypes */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) && \
     (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
    static void `$INSTANCE_NAME`_BistConnectShieldAsSensor(void);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) && \
           (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

/* Sensor capacitance measurement test function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
    static uint32 `$INSTANCE_NAME`_GetSensorCapacitanceExt(uint32 wdgtId, uint32 ioSnsId);
    static uint32 `$INSTANCE_NAME`_MeasureAllSensorCapacitance(void);
    static void `$INSTANCE_NAME`_BistConnectSensor(uint32 wdgtId, uint32 ioSnsId);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
            static void `$INSTANCE_NAME`_BistEnableShieldElectrodes(void);
        #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
            static void `$INSTANCE_NAME`_BistEnableShieldTank(void);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */

/* External capacitor measurement test function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)
    static uint32 `$INSTANCE_NAME`_MeasureAllExtCapCapacitance(void);
    static uint32 `$INSTANCE_NAME`_MeasureExtCapCapacitance(uint32 extCapId);
    static void `$INSTANCE_NAME`_BistConnectExtCapacitor(uint32 extCapId);
    static void `$INSTANCE_NAME`_BistDisconnectExtCapacitor(uint32 extCapId);
    static void `$INSTANCE_NAME`_GetExtCapCapacitanceExt(uint32 modClkDivider, uint32 iDacVal);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */

/* Sensor and Shield capacitance measurement test function prototypes */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN))
    static void `$INSTANCE_NAME`_BistDisableHwSnsCap(void);
    static uint32 `$INSTANCE_NAME`_GetCapacitanceExt(void);
    static void `$INSTANCE_NAME`_BistSetInactiveSensorConnection(uint32 wdgtId, uint32 ioSnsId);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        static void `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
            static void `$INSTANCE_NAME`_BistDisableShieldElectrodes(void);
        #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)) */

/* Measurement test group function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN)
    static void `$INSTANCE_NAME`_BistPostSingleScan(void);
    /* Capturing/Releasing HW resources by measurement test group */
    static void `$INSTANCE_NAME`_BistEnableHwSnsCap(void);
    /* Scanning specific function */
    static void `$INSTANCE_NAME`_BistCmodPrecharge(void);
    static void `$INSTANCE_NAME`_BistStartSample(void);
    static void `$INSTANCE_NAME`_BistConfigClock(uint32 snsClk);
    static void `$INSTANCE_NAME`_BistSetScanDuration(void);
    static void `$INSTANCE_NAME`_BistSetIdac(uint32 idacValue);
    static void `$INSTANCE_NAME`_BistTriggerScan(void);
    static void `$INSTANCE_NAME`_WaitEndOfScan(uint32 timeout);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
    /* HW Config Switching function */
    static void `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_CONFIG_ENUM config);
    static void `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_CONFIG_ENUM config);
    /* IOs configuration function */
    static void `$INSTANCE_NAME`_SetAllIODrState(uint32 value);
    static void `$INSTANCE_NAME`_SetAllIOPcState(uint32 value);
    static void `$INSTANCE_NAME`_SetElectrodePc(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value);
    static void `$INSTANCE_NAME`_SetElectrodeDr(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value);
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
        (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
        static void `$INSTANCE_NAME`_SetAllIOHsiomState(en_hsiom_sel_t value);
    #endif
#endif

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)))
    static void `$INSTANCE_NAME`_SetElectrodeHsiom(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, en_hsiom_sel_t value);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
          ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN)
    static void `$INSTANCE_NAME`_BistEnableVddaMeasurement(void);
    static uint16 `$INSTANCE_NAME`_BistVddaRunMeasurement(void);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) */

/** \}
* \endcond */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RunSelfTest
****************************************************************************//**
*
* \brief
*  Runs built-in self-tests specified by the test enable mask.
*
* \details
*  The function performs various self-tests on all the enabled widgets
*  and sensors in the Component. The required set of tests can be selected
*  using the bit-mask in testEnMask parameter.
*
*  Use `$INSTANCE_NAME`_TST_RUN_SELF_TEST_MASK to execute all the self-tests or
*  any combination of the masks (defined in testEnMask parameter) to specify the
*  test list.
*
*  To execute a single-element test (i.e. for one widget or sensor), the following
*  functions available:
*  - `$INSTANCE_NAME`_CheckGlobalCRC()
*  - `$INSTANCE_NAME`_CheckWidgetCRC()
*  - `$INSTANCE_NAME`_CheckBaselineDuplication()
*  - `$INSTANCE_NAME`_CheckSensorShort()
*  - `$INSTANCE_NAME`_CheckSns2SnsShort()
*  - `$INSTANCE_NAME`_GetSensorCapacitance()
*  - `$INSTANCE_NAME`_GetShieldCapacitance()
*  - `$INSTANCE_NAME`_GetExtCapCapacitance()
*  - `$INSTANCE_NAME`_GetVdda()
*
*  Refer to these functions for detail information on the corresponding test.
*
* \param testEnMask
*  Specifies the tests to be executed. Each bit corresponds to one test. It is
*  possible to launch the function with any combination of the available tests.
*  - `$INSTANCE_NAME`_TST_GLOBAL_CRC       - Verifies the RAM structure CRC of global parameters
*  - `$INSTANCE_NAME`_TST_WDGT_CRC         - Verifies the RAM widget structure CRC for all the widgets
*  - `$INSTANCE_NAME`_TST_BSLN_DUPLICATION - Verifies the baseline consistency of all the sensors (inverse copy)
*  - `$INSTANCE_NAME`_TST_SNS_SHORT        - Checks all the sensors for a short to GND or VDD
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT    - Checks all the sensors for a short to other sensors
*  - `$INSTANCE_NAME`_TST_SNS_CAP          - Measures all the sensors capacitance
*  - `$INSTANCE_NAME`_TST_SH_CAP           - Measures the shield capacitance
*  - `$INSTANCE_NAME`_TST_EXTERNAL_CAP     - Measures the capacitance of the available external capacitors
*  - `$INSTANCE_NAME`_TST_VDDA             - Measures the Vdda voltage
*  - `$INSTANCE_NAME`_TST_RUN_SELF_TEST_MASK - Executes all available tests.
*
* \return
*  Returns a bit-mask with a status of execution of the specified tests:
*  - CY_RET_SUCCESS - All the tests passed.
*  - `$INSTANCE_NAME`_TST_NOT_EXECUTED - The previously triggered scanning is not
*    completed.
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - A non-defined test was requested in the
*    testEnMask parameter.
*  - The bit-mask of the failed tests.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_RunSelfTest(uint32 testEnMask)
{
    uint32 result = CY_RET_SUCCESS;

    if(`$INSTANCE_NAME`_NOT_BUSY != `$INSTANCE_NAME`_IsBusy())
    {
        result = `$INSTANCE_NAME`_TST_NOT_EXECUTED;
    }
    else
    {
        if (0u == (testEnMask & (~`$INSTANCE_NAME`_TST_RUN_SELF_TEST_MASK)))
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
                if (0u != (`$INSTANCE_NAME`_TST_GLOBAL_CRC & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckGlobalCRC();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
                if (0u != (`$INSTANCE_NAME`_TST_WDGT_CRC & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllWidgetCRC();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
                if (0u != (`$INSTANCE_NAME`_TST_BSLN_DUPLICATION & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllBaselineDuplication();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN) */

            /* All the next tests are hardware dependent, so requesting to switch the sense method */
            `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
                if (0u != (`$INSTANCE_NAME`_TST_SNS_SHORT & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllSensorShort();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
                if (0u != (`$INSTANCE_NAME`_TST_SNS2SNS_SHORT & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllSns2SnsShort();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
                if (0u != (`$INSTANCE_NAME`_TST_SNS_CAP & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_MeasureAllSensorCapacitance();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
                if (0u != (`$INSTANCE_NAME`_TST_SH_CAP & testEnMask))
                {
                    (void)`$INSTANCE_NAME`_GetShieldCapacitance();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)
                if (0u != (`$INSTANCE_NAME`_TST_EXTERNAL_CAP & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_MeasureAllExtCapCapacitance();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN)
                if (0u != (`$INSTANCE_NAME`_TST_VDDA & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_GetVdda();
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA) */
        }
        else
        {
            result |= `$INSTANCE_NAME`_TST_BAD_PARAM;
        }
    }

    return result;
}

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckGlobalCRC
****************************************************************************//**
*
* \brief
*  Checks the stored CRC of the `$INSTANCE_NAME`_RAM_STRUCT data structure.
*
* \details
*  This function validates the data integrity of the
*  `$INSTANCE_NAME`_RAM_STRUCT data structure by calculating the CRC and
*  comparing it with the stored CRC value (i.e. `$INSTANCE_NAME`_GLB_CRC_VALUE).
*
*  If the stored and calculated CRC values differ, the calculated CRC
*  is stored to the `$INSTANCE_NAME`_GLB_CRC_CALC_VALUE register and
*  the `$INSTANCE_NAME`_TST_GLOBAL_CRC bit is set in the
*  `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register. The function never
*  clears the `$INSTANCE_NAME`_TST_GLOBAL_CRC bit.
*
*  It is recommended to use the `$INSTANCE_NAME`_SetParam() function to
*  change a value of `$INSTANCE_NAME`_RAM_STRUCT data structure register/elements
*  as CRC is updated by the `$INSTANCE_NAME`_SetParam() function.
*
*  This test also can be initiated by using `$INSTANCE_NAME`_RunSelfTest()
*  function with the `$INSTANCE_NAME`_TST_GLOBAL_CRC mask input.
*
* \return
*  Returns a status of the executed test:
*  - CY_RET_SUCCESS - The stored CRC matches the calculated CRC
*  - `$INSTANCE_NAME`_TST_GLOBAL_CRC - The stored CRC is wrong.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckGlobalCRC(void)
{
    uint32 result = `$INSTANCE_NAME`_TST_GLOBAL_CRC;
    uint16 crcValue;

    crcValue = `$INSTANCE_NAME`_DsCalculateCrc16((uint8 *)&`$INSTANCE_NAME`_dsRam +
                                    `$INSTANCE_NAME`_GLOBAL_CRC_AREA_START,
                                    `$INSTANCE_NAME`_GLOBAL_CRC_AREA_SIZE);
    if (`$INSTANCE_NAME`_dsRam.glbCrc == crcValue)
    {
        result = CY_RET_SUCCESS;
    }
    else
    {
        `$INSTANCE_NAME`_dsRam.selfTest.glbCrcCalc = crcValue;
        `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_GLOBAL_CRC;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DsUpdateGlobalCrc
****************************************************************************//**
*
* \brief
*   Recalculates the CRC for the global Component data (certain registers)
*   and writes it to the Data Structure.
*
* \details
*  Uses the function `$INSTANCE_NAME`_DsCalculateCrc16.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DsUpdateGlobalCrc(void)
{
    `$INSTANCE_NAME`_dsRam.glbCrc = `$INSTANCE_NAME`_DsCalculateCrc16((uint8 *)&`$INSTANCE_NAME`_dsRam +
                                                        `$INSTANCE_NAME`_GLOBAL_CRC_AREA_START,
                                                        `$INSTANCE_NAME`_GLOBAL_CRC_AREA_SIZE);
}
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckWidgetCRC
****************************************************************************//**
*
* \brief
*  Checks the stored CRC of the `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT data
*  structure of the specified widget.
*
* \details
*  This function validates the data integrity of the
*  `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT data structure of the specified widget
*  by calculating the CRC and comparing it with the stored CRC value
*  (i.e. `$INSTANCE_NAME`_<WidgetName>_CRC_VALUE).
*
*  If the stored and calculated CRC values differ:
*  1. The calculated CRC is stored to the `$INSTANCE_NAME`_WDGT_CRC_CALC_VALUE register
*  2. The widget ID is stored to the `$INSTANCE_NAME`_WDGT_CRC_ID_VALUE register
*  3. The `$INSTANCE_NAME`_TST_WDGT_CRC bit is set in the
*     `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*
*  The function never clears the `$INSTANCE_NAME`_TST_WDGT_CRC bit.
*  If the `$INSTANCE_NAME`_TST_WDGT_CRC bit is set, the `$INSTANCE_NAME`_WDGT_CRC_CALC_VALUE
*  and `$INSTANCE_NAME`_WDGT_CRC_ID_VALUE registers are not updated.
*
*  It is recommended to use the `$INSTANCE_NAME`_SetParam() function to change
*  a value of `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT data structure register/elements
*  as the CRC is updated by `$INSTANCE_NAME`_SetParam() function.
*
*  This test can be initiated by `$INSTANCE_NAME`_RunSelfTest() function with
*  the `$INSTANCE_NAME`_TST_WDGT_CRC mask as an input.
*
*  The function updates the wdgtWorking register
*  `$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE by clearing the widget-corresponding bit.
*  Those non-working widgets are skipped by the high-level API.
*  Restoring a widget to its working state should be done by the application level.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration
*  header file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \return
*  Returns a status of the test execution:
*  - CY_RET_SUCCESS - The stored CRC matches the calculated CRC.
*  - `$INSTANCE_NAME`_TST_WDGT_CRC - The widget CRC is wrong.
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - The input parameter is invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckWidgetCRC(uint32 widgetId)
{
    uint32 result = `$INSTANCE_NAME`_TST_WDGT_CRC;
    uint16 crcValue = 0u;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

    if (`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId)
    {
        /* Get pointer to RAM object data */
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        crcValue = `$INSTANCE_NAME`_DsCalculateCrc16((uint8 *)ptrWdgt +
                                    `$INSTANCE_NAME`_WIDGET_CRC_AREA_START,
                                    `$INSTANCE_NAME`_WIDGET_CRC_AREA_SIZE);
        if ((ptrWdgt->crc) != crcValue)
        {
            /* Write to Self-test Data Structure wdgtId of the first badtested widget */
            if (0Lu == (`$INSTANCE_NAME`_dsRam.selfTest.testResultMask &
                       `$INSTANCE_NAME`_TST_WDGT_CRC))
            {
                `$INSTANCE_NAME`_dsRam.selfTest.wdgtCrcCalc = crcValue;
                `$INSTANCE_NAME`_dsRam.selfTest.wdgtCrcId = (uint8)widgetId;
                `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_WDGT_CRC;
            }
            else
            {
            }
            `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(widgetId)] &=
                                             ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(widgetId));
        }
        else
        {
            result = CY_RET_SUCCESS;
        }
    }
    else
    {
        result = `$INSTANCE_NAME`_TST_BAD_PARAM;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckAllWidgetCRC
****************************************************************************//**
*
* \brief
*  The internal fuction that checks CRC of all widget structures.
*
* \details
*  The function calculates CRC of all widget structures and compare it
*  to the stored CRCs.
*  In case of failed comparison the function updates
*  testResultMask and returns the status.
*  The function use `$INSTANCE_NAME`_CheckWidgetCRC.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS if all widget CRC are OK;
*  - `$INSTANCE_NAME`_TST_WDGT_CRC if any widget CRC is wrong.
*  - `$INSTANCE_NAME`_TST_NOT_EXECUTED if any widget is unavailable.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllWidgetCRC(void)
{
    uint32 result = CY_RET_SUCCESS;
    uint32 wdgtIndex = 0u;

    for (wdgtIndex = 0u;
         wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS;
         wdgtIndex++)
    {
        if (0u != (`$INSTANCE_NAME`_CheckWidgetCRC(wdgtIndex)))
        {
            result |= `$INSTANCE_NAME`_TST_WDGT_CRC;
        }
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DsUpdateWidgetCrc
****************************************************************************//**
*
* \brief
*   Recalculates the CRC for the specified widgetId and
*   writes it to the Data Structure.
*
* \details
*  The maximum size of the RAM Widget Object is 192 bits. So, the best suitable
*  CRC polynomial is 0xAC9A that has hamming distance 5 for the data up to 241 bits.
*
*  Reference:  "P. Koopman, T. Chakravarthy,
*  "Cyclic Redundancy Code (CRC) Polynomial Selection for Embedded Networks",
*  The International Conference on Dependable Systems and Networks, DSN-2004"
*
* \param widgetId  The widget index number.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DsUpdateWidgetCrc(uint32 widgetId)
{
    uint32 len;
    uint8 *ptrData;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

    if (widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        /* Get pointer to RAM object data */
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        ptrData = (uint8 *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        len = (uint32)`$INSTANCE_NAME`_WIDGET_CRC_AREA_SIZE;

        /* Skip CRC in RAM object structure for CRC calculation */
        ptrData += `$INSTANCE_NAME`_WIDGET_CRC_AREA_START;

        ptrWdgt->crc = `$INSTANCE_NAME`_DsCalculateCrc16(ptrData, len);
    }
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_CRC_GROUP_EN)
/*******************************************************************************
* Function Name: DsCalculateCrc16
****************************************************************************//**
*
* \brief
*   Calculates CRC for the specified buffer and length. CRC Poly: 0xAC9A
*
* \details
*  This API is used for the CRC protection of the RAM Widget Object.
*  The maximum size of the RAM Widget Object is 192 bits. So, the best suitable
*  CRC polynomial is 0xAC9A. It has a Hamming distance 5 for data words up to 241 bits.
*
*  Reference:  "P. Koopman, T. Chakravarthy,
*  "Cyclic Redundancy Code (CRC) Polynomial Selection for Embedded Networks",
*  The International Conference on Dependable Systems and Networks, DSN-2004"
*
* \param ptrData The pointer to the data.
* \param len     The length of the data in bytes.
*
* \return A calculated CRC-16 value.
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_DsCalculateCrc16(uint8 *ptrData, uint32 len)
{
    uint32 idx;
    uint32 actualCrc = 0Lu;
    const uint16 crcTable[] =
    {
        0x0000u, 0xAC9Au, 0xF5AEu, 0x5934u, 0x47C6u, 0xEB5Cu, 0xB268u, 0x1EF2u,
        0x8F8Cu, 0x2316u, 0x7A22u, 0xD6B8u, 0xC84Au, 0x64D0u, 0x3DE4u, 0x917Eu
    };

    for (;len-- > 0u;)
    {
        /* Process HI Nibble */
        idx = ((actualCrc >> 12u) ^ (((uint32)*ptrData) >> 4u)) & 0xFLu;
        actualCrc = crcTable[idx] ^ (actualCrc << 4u);

        /* Process LO Nibble */
        idx = ((actualCrc >> 12u) ^ (uint32)*ptrData) & 0xFLu;
        actualCrc = crcTable[idx] ^ (actualCrc << 4u);

        ptrData++;
    }

    return (uint16)actualCrc;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_CRC_GROUP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckBaselineDuplication
****************************************************************************//**
*
* \brief
*  Checks that the baseline of the specified widget/sensor is not corrupted by
*  comparing it with a baseline inverse copy.
*
* \details
*  This function validates the integrity of baseline of sensor by comparing
*  the conformity of the baseline and its inversion.
*
*  If the baseline does not match its inverse copy:
*  1. The widget ID is stored to the `$INSTANCE_NAME`_INV_BSLN_WDGT_ID_VALUE register
*  2. The sensor ID is stored to the `$INSTANCE_NAME`_INV_BSLN_SNS_ID_VALUE register
*  3. The `$INSTANCE_NAME`_TST_BSLN_DUPLICATION bit is set in the
*     `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*
*  The function never clears the `$INSTANCE_NAME`_TST_BSLN_DUPLICATION bit.
*  If the `$INSTANCE_NAME`_TST_BSLN_DUPLICATION bit is set, the `$INSTANCE_NAME`_INV_BSLN_WDGT_ID_VALUE
*  and `$INSTANCE_NAME`_INV_BSLN_SNS_ID_VALUE registers are not updated.
*
*  It is possible to execute a test for all the widgets using `$INSTANCE_NAME`_RunSelfTest() function
*  with the `$INSTANCE_NAME`_TST_BSLN_DUPLICATION mask.
*  In this case, the `$INSTANCE_NAME`_INV_BSLN_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_INV_BSLN_SNS_ID_VALUE registers contain the widget and
*  sensor ID of the first detected fail.
*
*  The function updates the wdgtWorking register `$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE
*  by clearing the widget-corresponding bit. Those non-working widgets are skipped by
*  the high-level API. Restoring a widget to its working state should be done by the application level.
*
*  The test is integrated into the `$INSTANCE_NAME` Component. All `$INSTANCE_NAME`
*  processing functions like `$INSTANCE_NAME`_ProcessAllWidgets()
*  or `$INSTANCE_NAME`_UpdateSensorBaseline() automatically verify the baseline
*  value before using it and update its inverse copy after processing.
*  If fail is detected during a baseline update a CY_RET_BAD_DATA result
*  is returned. The baseline initialization functions do not verify the
*  baseline and update the baseline inverse copy.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns the status of the test execution:
*  - CY_RET_SUCCESS - The baseline matches its inverse copy.
*  - `$INSTANCE_NAME`_TST_BSLN_DUPLICATION - The test failed.
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - The input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckBaselineDuplication(uint32 widgetId, uint32 sensorId)
{
    uint32 result = CY_RET_SUCCESS;
    uint32 freqChannel;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = NULL;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) && ((`$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)) > sensorId))
    {
        ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        /* Find pointer to specified sensor object */
        ptrSensor = ptrWidget->ptr2SnsRam;
        ptrSensor = &ptrSensor[sensorId];
        /* Check baseline inversion of every channel in sensor */
        for(freqChannel = 0u; freqChannel < `$INSTANCE_NAME`_NUM_SCAN_FREQS; freqChannel++)
        {
            if (ptrSensor->bsln[freqChannel] != ((uint16) ~(ptrSensor->bslnInv[freqChannel])))
            {
                `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(widgetId, sensorId);
                result |= `$INSTANCE_NAME`_TST_BSLN_DUPLICATION;
            }
        }
    }
    else
    {
        result |= `$INSTANCE_NAME`_TST_BAD_PARAM;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckAllBaselineDuplication
****************************************************************************//**
*
* \brief
*  The internal fuction that checks baseline duplication of all the sensors.
*
* \details
*  The function checks baseline duplication of all the sensors by using
*  `$INSTANCE_NAME`_CheckBaselineDuplication() function.
*
* \return
*  Returns the status of the test processing:
*    - CY_RET_SUCCESS if the test is successfully completed;
*    - `$INSTANCE_NAME`_TST_BSLN_DUPLICATION if any sensor baseline duplication
       is wrong;
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllBaselineDuplication(void)
{
    uint32 result = CY_RET_SUCCESS;
    uint32 wdgtIndex;
    uint32 snsIndex;

    for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        for (snsIndex = 0u; snsIndex < (`$INSTANCE_NAME`_GET_SENSOR_COUNT(wdgtIndex)); snsIndex++)
        {
            if (CY_RET_SUCCESS != `$INSTANCE_NAME`_CheckBaselineDuplication(wdgtIndex, snsIndex))
            {
                result |= `$INSTANCE_NAME`_TST_BSLN_DUPLICATION;
                break;
            }
        }
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication
****************************************************************************//**
*
* \brief
*  The internal fuction that updates SefTest data structure and
*  widgetWorking register.
*
* \details
*  The function resets a corresponding bit in widgetWorking register,
*  checks TestResultMask for `$INSTANCE_NAME`_TST_BSLN_DUPLICATION
*  bit and if it was not setted to 1 sets it and memorizes wdgtId and snsId
*  in registers invBslnWdgtId and invBslnSnsId of the SefTest data structure.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget which
*  will be processed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(widgetId)] &=
                                     ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(widgetId));
    /* Write to Self-test Data Structure wdgtId and snsId of the first sensor with a damaged baseline inversion */
    if (0Lu == (`$INSTANCE_NAME`_dsRam.selfTest.testResultMask &
                `$INSTANCE_NAME`_TST_BSLN_DUPLICATION))
    {
        `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_BSLN_DUPLICATION;
        `$INSTANCE_NAME`_dsRam.selfTest.invBslnWdgtId = (uint8)widgetId;
        `$INSTANCE_NAME`_dsRam.selfTest.invBslnSnsId = (uint8)sensorId;
    }
}
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)*/

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckBaselineRawcountRange
****************************************************************************//**
*
* \brief
*  Checks that raw count and baseline of the specified widget/sensor are
*  within the specified range.
*
* \details
*  The baseline and raw count shall be within specific range (based on
*  calibration target) for good units. The function checks whether or not
*  the baseline and raw count are within the limits defined by the user in the
*  ranges function argument. If baseline or raw count are out of limits this
*  function sets the `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE bit in the
*  `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*
*  Unlike other tests, this test does not update
*  `$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE register and is not available in
*  the `$INSTANCE_NAME`_RunSelfTest() function.
*
*  Use this function to verify the uniformity of sensors, for example, at
*  mass-production or during an operation phase.
*
* \param widgetId
*  Specifies the ID number of the widget.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \param *ranges
*  Specifies the pointer to the `$INSTANCE_NAME`_BSLN_RAW_RANGE_STRUCT structure
*  with valid ranges for the raw count and baseline.
*
* \return
*  Returns a status of the test execution:
*  - CY_RET_SUCCESS - The raw count and baseline are within the specified range
*  - `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE - The test failed and baseline or
     raw count or both are out of the specified limit.
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - The input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckBaselineRawcountRange(uint32 widgetId, uint32 sensorId,`$INSTANCE_NAME`_BSLN_RAW_RANGE_STRUCT *ranges)
{
    uint32 result = CY_RET_SUCCESS;
    uint32 freqChannel;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = NULL;


    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) &&
       ((`$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)) > sensorId))
    {
        ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        /* Find pointer to specified sensor object */
        ptrSensor = ptrWidget->ptr2SnsRam;
        ptrSensor = &ptrSensor[sensorId];

        #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Check baseline and rawcont of every channel in sensor */
            for(freqChannel = 0u;
                freqChannel < `$INSTANCE_NAME`_NUM_SCAN_FREQS;
                freqChannel++)
            {
        #else
            freqChannel = 0u;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

                if ((ptrSensor->bsln[freqChannel] > ranges->bslnHiLim) ||
                    (ptrSensor->bsln[freqChannel] < ranges->bslnLoLim) ||
                    (ptrSensor->raw[freqChannel]  > ranges->rawHiLim)  ||
                    (ptrSensor->raw[freqChannel]  < ranges->rawLoLim))
                {
                    `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE;
                    result = `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE;
                }

        #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

    }
    else
    {
        result |= `$INSTANCE_NAME`_TST_BAD_PARAM;
    }
    return result;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckSensorShort
****************************************************************************//**
*
* \brief
*  Checks the specified widget/sensor for shorts to GND or VDD.
*
* \details
*  The function performs test to check for a short to GND or VDD on
*  the specified sensor. The resistance of electrical short must be
*  less than 1100 Ohm including series resistors on sensor for the short to
*  be detected. The `$INSTANCE_NAME`_GetSensorCapacitance() function can be
*  used to check an electrical short with resistance higher than 1100 Ohm or
*  when the specified ganged sensor consists of two or more electrodes.
*
*  This function performs the following tasks:
*  - If a short is detected, the widget ID is stored to the
*    `$INSTANCE_NAME`_SHORTED_WDGT_ID_VALUE register.
*  - If a short is detected, the sensor ID is stored to the
*    `$INSTANCE_NAME`_SHORTED_SNS_ID_VALUE register.
*  - If a short is detected, the `$INSTANCE_NAME`_TST_SNS_SHORT bit is
*    set in the `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*  - If a short is detected, the bit corresponding to the specified widget
*    (`$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE) is cleared in the
*    wdgtWorking register to indicate fault with the widget. Once the bit
*    is cleared, the widget is treated as non-working widget by the
*    high-level functions and further processing are skipped. Restoring
*    the bit corresponding the widget can be done by application layer
*    to restore the operation of the high-level functions.
*  - If `$INSTANCE_NAME`_TST_SNS_SHORT is already set due to previously
*    detected fault on any of the sensor, the `$INSTANCE_NAME`_TST_SNS_SHORT
*    register is not cleared by this function and
*    `$INSTANCE_NAME`_SHORTED_WDGT_ID_VALUE and
*    `$INSTANCE_NAME`_SHORTED_SNS_ID_VALUE registers are not updated.
*    For this reason, remember to read details of defective sensor and clear
*    `$INSTANCE_NAME`_TST_SNS_SHORT prior to calling this function on the
*    same or different sensor.
*
*  This function performs the test on one specific sensor. The
*  `$INSTANCE_NAME`_RunSelfTest() function with the
*  `$INSTANCE_NAME`_TST_SNS_SHORT mask, performs the short test on all
*  the widgets and sensors in the Component. In this case,
*  `$INSTANCE_NAME`_SHORTED_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_SHORTED_SNS_ID_VALUE registers stores the widget and sensor
*  ID of the first faulty sensor.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns a status of the test execution:
*  - CY_RET_SUCCESS - The sensor of the widget does not have a short to VDD or
*    GND and is in working condition.
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - A short is detected on the specified sensor.
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - The input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckSensorShort(uint32 widgetId, uint32 sensorId)
{
    uint32 result = CY_RET_SUCCESS;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) && ((`$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)) > sensorId))
    {
        /* Release previously captured HW resources by other mode and capture them for BIST */
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
        /* Switch HW resource configuration to sensor short test */
        `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E);
        /* Execute the test */
        result = `$INSTANCE_NAME`_ExecuteSnsShort(widgetId, sensorId);
    }
    else
    {
        result = `$INSTANCE_NAME`_TST_BAD_PARAM;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckAllSensorShort
****************************************************************************//**
*
* \brief
*  The internal fuction that checks all the sensors short to GND or VDD.
*
* \details
*  The fuction that checks for shorts on Vdd/GND of all sensor (not
*  electrode) by using `$INSTANCE_NAME`_ExecuteSnsShort. The function returns
*  the status and updates testResultMask and  wdgtWorking register
*  in a case of any shorts detection.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS if test passed successfully;
*  - `$INSTANCE_NAME`_TST_SNS_SHORT if any sensor of any widget is
*    shorted to Vdd or GND.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllSensorShort(void)
{
    uint32 wdgtIndex;
    uint32 snsIndex;
    uint32 result = CY_RET_SUCCESS;
    uint32 resultWidget = CY_RET_SUCCESS;

    /* Releasing of previously captured HW resources by other mode was done in the `$INSTANCE_NAME`_RunSelfTest() function */
    /* Switch HW resource configuration to sensor short test */
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E);
    /* Execute the test */
    for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        resultWidget = CY_RET_SUCCESS;
        for (snsIndex = 0u; snsIndex < (`$INSTANCE_NAME`_GET_SENSOR_COUNT(wdgtIndex)); snsIndex++)
        {
            resultWidget = `$INSTANCE_NAME`_ExecuteSnsShort(wdgtIndex, snsIndex);
            if (CY_RET_SUCCESS != resultWidget)
            {
                break;
            }
        }
        result |= resultWidget;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateTestResultSnsShort
****************************************************************************//**
* \brief
*  The internal fuction that updates SefTest data structure and
*  widgetWorking register.
*
* \details
*  The function resets a corresponding bit in widgetWorking register,
*  checks TestResultMask for `$INSTANCE_NAME`_TST_SNS_SHORT bit and if
*  it was not setted to 1 sets it and memorizes wdgtId and snsId
*  in corresponding registers of the SefTest data structure.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget which
*  will be processed.
*******************************************************************************/
static void `$INSTANCE_NAME`_UpdateTestResultSnsShort(uint32 wdgtId, uint32 snsId)
{
    `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdgtId)] &=
                                     ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdgtId));
    if (0Lu == (`$INSTANCE_NAME`_dsRam.selfTest.testResultMask & `$INSTANCE_NAME`_TST_SNS_SHORT))
    {
        /* Write to Self-test Data Structure wdgtId and snsId of the first shorted sensor */
        `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_SNS_SHORT;
        `$INSTANCE_NAME`_dsRam.selfTest.shortedWdgtId = (uint8)wdgtId;
        `$INSTANCE_NAME`_dsRam.selfTest.shortedSnsId = (uint8)snsId;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ExecuteSnsShort
****************************************************************************//**
*
* \brief
*  The internal fuction that checks one sensor for shorts on GND/VDD.
*
* \details
*  The function that checks for shorts on GND/VDD of a certain sensor for CSD
*  widgets or of Rx and Tx electrodes of a certain sensor for CSX widgets.
*  The function uses `$INSTANCE_NAME`_ExecuteSnsShortExt.
*  In a case of a shorts detection the function returns failed result.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS if any sensor's electrode of the widget isn't shorted to VDD or GND;
*  - `$INSTANCE_NAME`_TST_SNS_SHORT if the sensor is shorted to VDD or GND;
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSnsShort(uint32 wdgtId, uint32 snsId)
{
    uint32 ioSnsId;
    uint32 result = CY_RET_SUCCESS;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
        /* For CSX widgets get an index of Rx electrode, for CSD widgets an electrode index is the same as snsId */
        if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
        {
            ioSnsId = snsId / `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows;
        }
        else
        {
            ioSnsId = snsId;
        }
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        ioSnsId = snsId / `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows;
    #else
        ioSnsId = snsId;
    #endif

    result = `$INSTANCE_NAME`_ExecuteSnsShortExt(wdgtId, ioSnsId);

    /* For CSX widgets get an index of Tx electrode and repeat the test */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        if (CY_RET_SUCCESS == result)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
            {
                ioSnsId = (uint32)(snsId % `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows) +
                    (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numCols;
                result = `$INSTANCE_NAME`_ExecuteSnsShortExt(wdgtId, ioSnsId);
            }
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

    if (CY_RET_SUCCESS != result)
    {
        `$INSTANCE_NAME`_UpdateTestResultSnsShort(wdgtId, snsId);
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ExecuteSnsShortExt
****************************************************************************//**
*
* \brief
*  The internal fuction that checks one sensor for shorts on GND/VDD.
*
* \details
*  The function that checks for shorts on GND/VDD of a certain sensor (electrode)
*  for CSD widgets or of Rx or Tx electrode of a certain sensor for CSX widgets.
*  In a case of a shorts detection the function returns failed result.
*  The function proceeds ganged sensors (electrodes).
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor (electrode) within the widget to be processed.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS if the electrode of the widget isn't shorted to VDD or GND;
*  - `$INSTANCE_NAME`_TST_SNS_SHORT if the sensor or Rx or Tx electrode
*    is shorted to VDD or GND.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSnsShortExt(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    uint32 result = CY_RET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1u;
    }

    /* Loop through all electrodes of specified sensor */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Set electrode to pull up drive mode and check that electrode state is logical 1 */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr, `$INSTANCE_NAME`_TST_DR_PIN2VDD);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_PULLUP_IN_ON);
        if (0uL == `$INSTANCE_NAME`_ReadElectrodeState(ioPtr))
        {
            result = `$INSTANCE_NAME`_TST_SNS_SHORT;
        }
        /* Set electrode to pull down drive mode and check that electrode state is logical 0 */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr, `$INSTANCE_NAME`_TST_DR_PIN2GND);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_PULLDOWN_IN_ON);
        if (0uL != `$INSTANCE_NAME`_ReadElectrodeState(ioPtr))
        {
            result = `$INSTANCE_NAME`_TST_SNS_SHORT;
        }
        /* Revert electrode to default drive mode */
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_HIGHZA);

        if (`$INSTANCE_NAME`_TST_SNS_SHORT == result)
        {
            break;
        }

        /* Get the next electrode */
        ioPtr++;
    }
    return result;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckSns2SnsShort
****************************************************************************//**
*
* \brief
*  Checks the specified widget/sensor for shorts to any other `$INSTANCE_NAME`
*  sensors.
*
* \details
*  The function performs the test on the specified sensor to check for a short
*  to other sensors in the Component. The resistance of an electrical short
*  must be less than 1100 Ohm including the series resistors on the sensor for
*  the short to be detected. The `$INSTANCE_NAME`_GetSensorCapacitance()
*  function can be used to check the electrical short with the resistance
*  higher than 1100 Ohm or when the specified ganged sensor consists of two or
*  more electrodes.
*
*  This function performs the following tasks:
*  - If a short is detected, widget ID is stored to the
*    `$INSTANCE_NAME`_P2P_WDGT_ID_VALUE register.
*  - If a short is detected, sensor ID is stored to the
*    `$INSTANCE_NAME`_P2P_SNS_ID_VALUE register.
*  - If a short is detected, `$INSTANCE_NAME`_TST_SNS2SNS_SHORT bit is set
*    in the `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*  - If a short is detected, the bit corresponding to widget
*    (`$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE) is cleared in the
*    wdgtWorking register to indicate fault with widget. Once the bit is
*    cleared, the widget is treated as a non-working widget by the high-level
*    functions and further processing are skipped. Restoring the bit
*    corresponding to the widget can be done by application layer to restore
*    the operation of high-level functions.
*  - If `$INSTANCE_NAME`_TST_SNS2SNS_SHORT is already set due to the
*    previously detected fault on any of the sensor, the
*    `$INSTANCE_NAME`_TST_SNS2SNS_SHORT register is not cleared by this
*    function and `$INSTANCE_NAME`_P2P_WDGT_ID_VALUE and
*    `$INSTANCE_NAME`_P2P_SNS_ID_VALUE registers are not updated.
*    For this reason, remember to read details of defective sensor and clear
*    `$INSTANCE_NAME`_TST_SNS2SNS_SHORT prior to calling this function on the
*    same or different sensor.
*
*  This function performs the test on one specific sensor.
*  The `$INSTANCE_NAME`_RunSelfTest() function with the
*  `$INSTANCE_NAME`_TST_SNS2SNS_SHORT mask performs the short test on all the
*  widgets and sensors in the Component. In this case,
*  `$INSTANCE_NAME`_P2P_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_P2P_SNS_ID_VALUE registers store the widget and sensor ID
*  of the first faulty sensor.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns a status of the test execution:
*  - CY_RET_SUCCESS - The sensor is not shorted to any other sensor is in
*    working condition.
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT - A short is detected with one or
*    more sensors in the Component.
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - The input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckSns2SnsShort(uint32 widgetId, uint32 sensorId)
{
    uint32 result = CY_RET_SUCCESS;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) && ((`$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)) > sensorId))
    {
        /* Release previously captured HW resources by other mode and capture them for BIST */
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
        /* Switch HW resource configuration to sensor to sensor short test */
        `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E);
        /* Execute the test */
        result = `$INSTANCE_NAME`_ExecuteSns2SnsShort(widgetId, sensorId);
    }
    else
    {
        result |= `$INSTANCE_NAME`_TST_BAD_PARAM;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckAllSns2SnsShort
****************************************************************************//**
*
* \brief
*  The internal fuction that checks for shorts between all of
*  `$INSTANCE_NAME` sensors.
*
* \details
*  The function checks for all sensor shorts between them by using
*  `$INSTANCE_NAME`_ExecuteSns2SnsShort.
*  The function returns the status and updates testResultMask and
*  wdgtWorking register in a case of any shorts detection.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS - All the sensors of all the widgets aren't shorted to
*    any other sensors.
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - Any sensor of any widget is
*    shorted on any other sensor.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllSns2SnsShort(void)
{
    uint32 wdgtIndex;
    uint32 snsIndex;
    uint32 result = CY_RET_SUCCESS;
    uint32 resultWidget = CY_RET_SUCCESS;

    /* Releasing of previously captured HW resources by other mode was done in the `$INSTANCE_NAME`_RunSelfTest() function */
    /* Switch HW resource configuration to sensor to sensor to sensor short test */
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E);

    /* Execute the test */
    for (wdgtIndex = 0uL; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        resultWidget = CY_RET_SUCCESS;
        for (snsIndex = 0u; snsIndex < (`$INSTANCE_NAME`_GET_SENSOR_COUNT(wdgtIndex)); snsIndex++)
        {
            resultWidget = `$INSTANCE_NAME`_ExecuteSns2SnsShort(wdgtIndex, snsIndex);
            if (CY_RET_SUCCESS != resultWidget)
            {
                break;
            }
        }
        result |= resultWidget;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateTestResultSns2SnsShort
****************************************************************************//**
* \brief
*  The internal fuction that updates Self-test Data Structure and
*  widgetWorking register.
*
* \details
*  The function resets a corresponding bit in widgetWorking register,
*  checks TestResultMask for `$INSTANCE_NAME`_TST_SNS2SNS_SHORT bit and
*  if it was not setted to 1 sets it and memorizes wdgtId and snsId
*  in corresponding registers of the SefTest data structure.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget which
*  will be processed.
*******************************************************************************/
static void `$INSTANCE_NAME`_UpdateTestResultSns2SnsShort(uint32 wdgtId, uint32 snsId)
{
    `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdgtId)] &=
                                     ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdgtId));
    /* Write to Self-test Data Structure wdgtId and snsId of the first shorted sensor2sensor */
    if (0uL == (`$INSTANCE_NAME`_dsRam.selfTest.testResultMask & `$INSTANCE_NAME`_TST_SNS2SNS_SHORT))
    {
        `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_SNS2SNS_SHORT;
        `$INSTANCE_NAME`_dsRam.selfTest.p2pWdgtId = (uint8)wdgtId;
        `$INSTANCE_NAME`_dsRam.selfTest.p2pSnsId = (uint8)snsId;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ExecuteSns2SnsShort
****************************************************************************//**
*
* \brief
*  The internal fuction that checks one sensor for shorts to another sensor.
*
* \details
*  The function that checks for shorts to another sensor of a certain sensor
*  for CSD widgets or Rx and Tx electrodes of a certain sensor for CSX widgets.
*  The function uses `$INSTANCE_NAME`_ExecuteSnsShortExt.
*  In a case of a shorts detection the function returns failed result.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS if the electrode of the widget isn't shorted to another sensor;
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT if the sensor is shorted to another sensor.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShort(uint32 wdgtId, uint32 snsId)
{
    uint32 ioSnsId;
    uint32 result = CY_RET_SUCCESS;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
        /* For CSX widgets get an index of Rx electrode, for CSD widgets an electrode index is the same as snsId */
        if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
        {
            ioSnsId = snsId / `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows;
        }
        else
        {
            ioSnsId = snsId;
        }
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        ioSnsId = snsId / `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows;
    #else
        ioSnsId = snsId;
    #endif

    result = `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(wdgtId, ioSnsId);

    /* For CSX widgets get an index of Tx electrode and repeat the test */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        if (CY_RET_SUCCESS == result)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
            {
                ioSnsId = (uint32)(snsId % `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows) +
                    (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numCols;
                result = `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(wdgtId, ioSnsId);
            }
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

    if (CY_RET_SUCCESS != result)
    {
        `$INSTANCE_NAME`_UpdateTestResultSns2SnsShort(wdgtId, snsId);
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ExecuteSns2SnsShortExt
****************************************************************************//**
*
* \brief
*  The internal fuction that checks one sensor for shorts to another sensor.
*
* \details
*  The function that checks for shorts to another sensor of a certain sensor(electrode)
*  for CSD widgets or of Rx or Tx electrode of a certain sensor for CSX widgets.
*  In a case of a shorts detection the function returns failed result.
*  The function proceeds ganged sensors(electrodes).
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*
* \return
*  Returns the status of the test processing:
*  - CY_RET_SUCCESS if the electrode of the widget isn't shorted to another sensor;
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT if the sensor or Rx or Tx electrode
*    is shorted to another sensor.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    uint32 result = CY_RET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1uL;
    }

    /* Loop through all electrodes of specified sensor and set pull up drive mode */
    for (eltdIndex = 0uL; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Set electrode to pull up drive mode and check that electrode state is logical 1 */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_DR_PIN2VDD);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_PC_PULLUP_IN_ON);

        if (0uL == `$INSTANCE_NAME`_ReadElectrodeState(ioPtr + eltdIndex))
        {
            result = `$INSTANCE_NAME`_TST_SNS2SNS_SHORT;
            break;
        }

        /* Revert electrode to default drive mode */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_DR_PIN2GND);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
    }

    return(result);
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SHORT_GROUP_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadElectrodeState
****************************************************************************//**
*
* \brief
*  The internal function that reds a certain electrode state.
*
* \details
*  The function activates an input buffer for the specified electrode and reads
*  the correspondent input bit. After that it disables the input buffer.
*
* \param *ioPtr
*  A pointer to IO data structure of the specified electrode.
*
* \return
*  Returns the state of the input buffer of the electrode (0 or non 0).
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ReadElectrodeState(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr)
{
    uint32 result;

    /* Enable the input buffer for the specified electrode */
    uint32  interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
    result = Cy_GPIO_Read(ioPtr->pcPtr, (uint32)ioPtr->pinNumber);
    Cy_SysLib_ExitCriticalSection(interruptState);

    return(result);
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SHORT_GROUP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetExtCapCapacitance
****************************************************************************//**
*
* \brief
*  Measures the capacitance of the specified external capacitor.
*
* \details
*  The function measures the capacitance of the specified external capacitor
*  such as Cmod and returns the result, alternatively the result is stored in
*  the `$INSTANCE_NAME`_EXT_CAP<EXT_CAP_ID>_VALUE register in data structure.
*
*  The measurable capacitance range using this function is
*  from 200pF to 60,000pF with measurement accuracy of 10%.
*
*  This test can be executed for all the external capacitors at once using
*  the `$INSTANCE_NAME`_RunSelfTest() function with the
*  `$INSTANCE_NAME`_TST_EXTERNAL_CAP mask.
*
* \param extCapId
*  Specifies the ID number of the external capacitor to be measured:
*  - `$INSTANCE_NAME`_TST_CMOD_ID - Cmod capacitor
*  - `$INSTANCE_NAME`_TST_CSH_ID - Csh capacitor
*  - `$INSTANCE_NAME`_TST_CINTA_ID - CintA capacitor
*  - `$INSTANCE_NAME`_TST_CINTB_ID - CintB capacitor
*
* \return
*  Returns a status of the test execution:
*  - The capacitance (in pF) of the specified external capacitor
*  - `$INSTANCE_NAME`_TST_BAD_PARAM if the input parameter is invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetExtCapCapacitance(uint32 extCapId)
{
    uint32 result = CY_RET_SUCCESS;

    if (`$INSTANCE_NAME`_TST_EXT_CAPS_NUM > extCapId)
    {
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
        `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E);
        `$INSTANCE_NAME`_BistConfigClock((uint32)`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION);
        /* Set resolution to fixed value */
        `$INSTANCE_NAME`_BistSetScanDuration();
        result = `$INSTANCE_NAME`_MeasureExtCapCapacitance(extCapId);
    }
    else
    {
        result |= `$INSTANCE_NAME`_TST_BAD_PARAM;
    }
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureExtCapCapacitance
****************************************************************************//**
*
* \brief
*  The internal function that measures a capacitance of an external capacitor
*  when HW IP block is configured for an external capasitors measuring.
*
* \details
*  The function connect an external capacitor (Cmod, Csh, CintA/CintB)
*  to CSD block, defines a modclock frequency divider and an Idac code
*  and measures a capacitance in range of 0,5 to 5,0 nF.
*  If the result exceeds 75 % of a range high bound the function divides modClk,
*  multiply Idac code to the fixed value to wide a measurement range and performs
*  another measuring cycle for a capacitance in range of 5,0 to 60,0 nF.
*  After that the fuction disconnect the external capacitor, calculate a result
*  and stores it to a correspondent register of the Self-test Data Structure.
*
* \param extCapId
*  An index of the external cap to measure.
*
* \return
*  - Cext of the external capacitor in pF units.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_MeasureExtCapCapacitance(uint32 extCapId)
{
    uint32 modClkDivider;
    uint32 iDacVal;
    uint32 result = 0uL;

    /* Connect an extCap */
    `$INSTANCE_NAME`_BistConnectExtCapacitor(extCapId);
     /* Set modClk and Idac to the fixed value for a fine scan */
    #if (CYDEV_CLK_PERICLK__MHZ < `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ)
        modClkDivider = 1uL;
    #else
        modClkDivider = CYDEV_CLK_PERICLK__MHZ / `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ;
    #endif /* (CYDEV_CLK_PERICLK__MHZ < `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ) */

    iDacVal = (((`$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE * `$INSTANCE_NAME`_CSD_VREF_MV * CYDEV_CLK_PERICLK__MHZ) /
              `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN) / modClkDivider) + 1uL;
    `$INSTANCE_NAME`_GetExtCapCapacitanceExt(modClkDivider, iDacVal);

    /* For results more then 75 % of the resolution limit perform a second wide range scan */
    if (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION_75 < `$INSTANCE_NAME`_bistRawcount)
    {
         /* Divide modClk and Multiply Idac to the fixed value to wide a measurement range */
        modClkDivider <<= 2u;
        iDacVal <<= 2u;
        `$INSTANCE_NAME`_GetExtCapCapacitanceExt(modClkDivider, iDacVal);
    }
    /* Disconnect ext capacitor */
    `$INSTANCE_NAME`_BistDisconnectExtCapacitor(extCapId);
    /* Calculate result in 2 steps to prevent overflow */
    result = (iDacVal * modClkDivider * `$INSTANCE_NAME`_bistRawcount) / CYDEV_CLK_PERICLK__MHZ;
    result = (result * `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN) / `$INSTANCE_NAME`_CSD_VREF_MV;
    `$INSTANCE_NAME`_dsRam.selfTest.extCap[extCapId] = (uint16)result;

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetExtCapCapacitanceExt
****************************************************************************//**
*
* \brief
*  The internal function that performs a scan for an external capacitor measuring.
*
* \details
*  The function sets the modclock and Idac to defined values and performs a scan
*  by using CSD mode for an external capacitor (Cmod, Csh, or CintA/CintB).
*
* \param modClkDivider
*  Specifies a divider for a modulation clock frequency.
*
* \param iDacVal
*  Specifies an Idac modulation code.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_GetExtCapCapacitanceExt(uint32 modClkDivider, uint32 iDacVal)
{
    `$INSTANCE_NAME`_ModClk_SetDivider((uint32)(modClkDivider - 1uL));
    `$INSTANCE_NAME`_BistSetIdac(iDacVal);
    /* Start the scan */
    `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;
    `$INSTANCE_NAME`_BistStartSample();
    /* Initialize Watchdog Counter with time interval which is enough to charge 100 nF capacitor */
    `$INSTANCE_NAME`_WaitEndOfScan(`$INSTANCE_NAME`_BIST_CALIBR_WATCHDOG_CYCLES_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConnectExtCapacitor
****************************************************************************//**
*
* \brief
*  The internal function that connects an external capacitor to the
*  `$INSTANCE_NAME` block.
*
* \details
*  The function that that connects an external capacitor to the `$INSTANCE_NAME`
*  block by using HSIOM in CSD mode.
*
* \param extCapId
*  An index of the external cap to connect.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConnectExtCapacitor(uint32 extCapId)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        uint32 interruptState;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
    /* Connect AMUXBUS-A to CSDCOMP(sense path) */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFMA_STATIC_CLOSE);

    switch(`$INSTANCE_NAME`_extCapMap[extCapId])
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_TST_CMOD_MAP:
            {
                /* Connect Cmod pin using HSIOM registers */
                /* Connect CMOD to AMUXBUS-A */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, (uint32)`$INSTANCE_NAME`_CSD_CMOD_PIN,
                                                                                                 CY_GPIO_DM_STRONG_IN_OFF);
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN,
                              (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
                Cy_SysLib_ExitCriticalSection(interruptState);
                break;
            }
                #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                    case `$INSTANCE_NAME`_TST_CSH_MAP:
                    {
                        Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, (uint32)`$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                                                                CY_GPIO_DM_STRONG_IN_OFF);
                        Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                                    (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
                        break;
                    }
                #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                      (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_TST_CINTA_MAP:
            {
                Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintA_PORT, (uint32)`$INSTANCE_NAME`_CintA_NUM,
                                                                                                 CY_GPIO_DM_STRONG_IN_OFF);
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM,
                                                                     (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
                break;
            }
            case `$INSTANCE_NAME`_TST_CINTB_MAP:
            {
                Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintB_PORT, (uint32)`$INSTANCE_NAME`_CintB_NUM,
                                                                                                 CY_GPIO_DM_STRONG_IN_OFF);
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM,
                                                                     (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
                break;
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistDisconnectExtCapacitor
****************************************************************************//**
*
* \brief
*  The internal function that disconnects an external capacitor from the
*  `$INSTANCE_NAME` block.
*
* \details
*  The function that that disconnects an external capacitor from the
*  `$INSTANCE_NAME` block.
*  After that the function dicharges the specified capacitor to GND to provide
*  next regular scans.
*
* \param extCapId
*  An index of the external cap to disconnect.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistDisconnectExtCapacitor(uint32 extCapId)
{
    uint32 interruptState;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        uint32 newRegValue;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

    /* Disconnect AMUXBUS-A from CSDCOMP(sense path) */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFMA_STATIC_OPEN);

    switch(`$INSTANCE_NAME`_extCapMap[extCapId])
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_TST_CMOD_MAP:
            {
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN,
                                                                      (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);

                /* Disconnect CSDCMP from CSDBUS-A (parallel pass via SFCA switch) */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR);
                newRegValue &= (uint32) (~`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFCA_MSK);
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, newRegValue);

                /* Discharge CMOD by using GPIO mode */
                /* Set output port register for Cmod to 0 to connect Cmod to GND */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_Clr(`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN);
                Cy_SysLib_ExitCriticalSection(interruptState);

                /* Set port configuration register (drive mode) for Cmod in STRONG mode */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN, (uint32)CY_GPIO_DM_STRONG_IN_OFF);
                Cy_SysLib_ExitCriticalSection(interruptState);

                /* Delay 10 uS to discharge Cmod */
                Cy_SysLib_DelayUs(10u);
                /* Set port configuration register (drive mode) for Cmod in HIGHZ-A mode (PC=000) */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN, (uint32)CY_GPIO_DM_ANALOG);
                Cy_SysLib_ExitCriticalSection(interruptState);
                break;
            }

            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                case `$INSTANCE_NAME`_TST_CSH_MAP:
                {
                    /* Disconnect CTANK from AMUXBUS-A */
                    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                           (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);

                    /* Discharge CTANK by using GPIO mode */
                    /* Set output port register for Cmod to 0 to connect Cmod to GND */
                    interruptState = Cy_SysLib_EnterCriticalSection();
                    Cy_GPIO_Clr(`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN);
                    Cy_SysLib_ExitCriticalSection(interruptState);

                    /* Set port configuration register (drive mode) for CTANK in STRONG mode */
                    interruptState = Cy_SysLib_EnterCriticalSection();
                    Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN, (uint32)CY_GPIO_DM_STRONG_IN_OFF);
                    Cy_SysLib_ExitCriticalSection(interruptState);

                    /* Delay 10 uS to discharge CTANK */
                    Cy_SysLib_DelayUs(10u);
                    /* Set port configuration register (drive mode) for CTANK in HIGHZ-A mode (PC=000) */
                    interruptState = Cy_SysLib_EnterCriticalSection();
                    Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN, (uint32)CY_GPIO_DM_ANALOG);
                    Cy_SysLib_ExitCriticalSection(interruptState);
                    break;
                }
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_TST_CINTA_MAP:
            {
                /* Disconnect CintA from AMUXBUS-A using HSIOM registers. */
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM,
                              (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);

                /* Discharge CintA by using GPIO mode */
                /* Set output port register for CintA to 0 to connect CintA to GND */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_Clr(`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM);
                Cy_SysLib_ExitCriticalSection(interruptState);

                /* Set port configuration register (drive mode) for CintA in STRONG mode */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM, (uint32)CY_GPIO_DM_STRONG_IN_OFF);
                Cy_SysLib_ExitCriticalSection(interruptState);

                /* Delay 10 uS to discharge CintA */
                Cy_SysLib_DelayUs(10u);
                /* Set port configuration register (drive mode) for CintA in HIGHZ-A mode (PC=000) */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM, (uint32)CY_GPIO_DM_ANALOG);
                Cy_SysLib_ExitCriticalSection(interruptState);
                break;
            }
            case `$INSTANCE_NAME`_TST_CINTB_MAP:
            {
                /* Discharge CintB by using GPIO mode */
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM,
                              (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);

                /* Discharge CintB by using GPIO mode */
                /* Set output port register for CintB to 0 to connect CintB to GND */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_Clr(`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM);
                Cy_SysLib_ExitCriticalSection(interruptState);

                /* Set port configuration register (drive mode) for CintB in STRONG mode */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM, (uint32)CY_GPIO_DM_STRONG_IN_OFF);
                Cy_SysLib_ExitCriticalSection(interruptState);

                /* Delay 10 uS to discharge CintB */
                Cy_SysLib_DelayUs(10u);
                /* Set port configuration register (drive mode) for CintB in HIGHZ-A mode (PC=000) */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM, (uint32)CY_GPIO_DM_ANALOG);
                Cy_SysLib_ExitCriticalSection(interruptState);
                break;
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

        default:
        {
            break;
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureAllExtCapCapacitance
****************************************************************************//**
*
* \brief
*  The internal function that measures a capacitance of all external
*  capacitors.
*
* \details
*  The function measures capacitances of all external  capacitor (Cmod,
*  Csh, CintA, CintB).
*  The function stores cap values in corresponding registers.
*  The function does not affect on another Component parameters or
*  functionalities.
*
* \return
*  Returns the status of the measuring process:
*  - CY_RET_SUCCESS if all measurings is successfull;
*  - `$INSTANCE_NAME`_TST_EXTERNAL_CAP if any measuring is failed.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_MeasureAllExtCapCapacitance(void)
{
    uint32 extCapIndex;

    `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E);
    `$INSTANCE_NAME`_BistConfigClock(`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION);
    /* Set resolution to fixed value) */
    `$INSTANCE_NAME`_BistSetScanDuration();

    for (extCapIndex = 0u; extCapIndex < `$INSTANCE_NAME`_TST_EXT_CAPS_NUM; extCapIndex++)
    {
        (void)`$INSTANCE_NAME`_MeasureExtCapCapacitance(extCapIndex);
    }

    return (CY_RET_SUCCESS);
}
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistDisableMode
****************************************************************************//**
*
* \brief
*  Releases captured HW resources.
*
* \details
*  Releases captured HW resources to be used by other modes.
*
*******************************************************************************/
void `$INSTANCE_NAME`_BistDisableMode(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
        `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_UNDEFINED_E);
        `$INSTANCE_NAME`_bistIoConfig = `$INSTANCE_NAME`_BIST_IO_UNDEFINED_E;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistInitialize
****************************************************************************//**
*
* \brief
*  Initialize the HW resources to Built-in Self-test mode.
*
* \details
*  Preserved the function to be consistent with other modes (CSX or CSD).
*  In practice resource capturing and initialization are performed later when
*  defined which test type should be executed. Depends on the test type HW
*  resources initialized differently. Only disconnection of all IO from AMUX
*  is common for all the test types.
*
*******************************************************************************/
void `$INSTANCE_NAME`_BistInitialize(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
            (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
            /* Disconnect all the IOs from analog mux busses */
            `$INSTANCE_NAME`_SetAllIOHsiomState(`$INSTANCE_NAME`_TST_HSIOM_GPIO);
        #endif
        /* Set data register to GND that is applicable for all the tests */
        `$INSTANCE_NAME`_SetAllIODrState(`$INSTANCE_NAME`_TST_DR_PIN2GND);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN) */
}

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) && \
     (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConnectShieldAsSensor
****************************************************************************//**
*
* \brief
*  Connects (a) shield electrode(s) to the sensing HW block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the SHIELD_IO_STRUCT object. Basing on this data, it updates
*   the HSIOM and PC registers.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConnectShieldAsSensor(void)
{
    uint32 eltdIndex;
    uint32  interruptState;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;

    /* Loop through all electrodes of Shield */
    for (eltdIndex = 0u; eltdIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; eltdIndex++)
    {
        ioPtr = &`$INSTANCE_NAME`_shieldIoList[eltdIndex];
        /* Set electrode to High-Z Analog */
        /* Update HSIOM port select register */
        interruptState = Cy_SysLib_EnterCriticalSection();
        Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
        Cy_GPIO_SetHSIOM(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
        Cy_SysLib_ExitCriticalSection(interruptState);
    }
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) && \
           (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistEnableShieldElectrodes
****************************************************************************//**
*
* \brief
*  This internal function initializes Shield Electrodes.
*
* \details
*  The function sets the bit in the HSIOM register which enables the shield electrode
*  functionality on the pin. The port and pin configurations are stored in
*  the `$INSTANCE_NAME`_shieldIoList structure.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableShieldElectrodes(void)
{
    uint32 shieldIndex;
    uint32  interruptState;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;

    for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
    {
        ioPtr = &`$INSTANCE_NAME`_shieldIoList[shieldIndex];
        /* Set drive mode to Analog */
        /* Set HSIOM register mode to CSD_SHIELD or AMUXBUS B connection */
        /* Set HSIOM register mode to CSD_SHIELD */
        interruptState = Cy_SysLib_EnterCriticalSection();
        Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
        Cy_GPIO_SetHSIOM(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, `$INSTANCE_NAME`_TST_HSIOM_CSD_SHIELD);
        Cy_SysLib_ExitCriticalSection(interruptState);
    }
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistEnableShieldTank
****************************************************************************//**
*
* \brief
*   This function configures Csh pin
*
* \details
*   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
*   For CSD v1 IP HW block it additionally sets Strong drive mode for Csh
*   and applies High level to Csh pin when precharge is set to IO buffer.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableShieldTank(void)
{
    Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN, CY_GPIO_DM_ANALOG);
    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                                (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_AMUXB);
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorCapacitance
****************************************************************************//**
*
* \brief
*  Measures the specified widget/sensor capacitance.
*
* \details
*  The function measures capacitance of the specified sensor and returns the
*  result, alternatively the result is stored in the Component data structure.
*
*  For CSD sensors, the capacitance of the specified sensor is measured.
*  For CSX sensors, the capacitance the both Rx and Tx electrodes of the sensor
*  is measured. For ganged sensor, total capacitance of all electrodes associated
*  with the sensor is measured. The capacitance measurement result is independent
*  on the Component or sensor tuning parameters and neither tuning parameter nor
*  the capacitance measurement function creates interference to other.
*
*  While measuring capacitance of a CSX sensor electrode, all the non-measured
*  electrodes and CSD shield electrodes (if enabled) are set to active low (GND).
*  While measuring capacitance of a CSD sensor electrode, all the CSX sensor
*  electrodes are set to active low (GND) and all CSD sensor electrodes are
*  set to the state defined by the inactive sensor state parameter in the
*  Component CSD Setting tab of the customizer. If the shield electrode
*  is enabled, it is enabled during CSD sensor capacitance measurement.
*
*  The measurable capacitance range using this function is from 5pF to 255pF.
*  If a returned value is 255, the sensor capacitance can be higher.
*
*  The measured capacitance is stored in the `$INSTANCE_NAME`_RAM_SNS_CP_STRUCT structure.
*  The `$INSTANCE_NAME`_<WidgetName>_PTR2SNS_CP_VALUE register contains a pointer to
*  the array of the specified widget with the sensor capacitance.
*
*  This test can be executed for all the sensors at once using the
*  `$INSTANCE_NAME`_RunSelfTest() function along with the
*  `$INSTANCE_NAME`_TST_SNS_CAP mask.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns a result of the test execution:
*  - Bits [7..0] The capacitance (in pF) of the CSD electrode or the capacitance
*    of Rx electrode of CSX sensor.
*  - Bits [15..8] The capacitance (in pF) of Tx electrode of CSX sensor.
*  - Bit [30] `$INSTANCE_NAME`_TST_BAD_PARAM The input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetSensorCapacitance(uint32 widgetId, uint32 sensorId)
{
    uint32 result = 0uL;
    uint32 ioSnsId = sensorId;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) &&
        (`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].totalNumSns > sensorId))
    {
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);

        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
        {
        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

        default:
            CY_ASSERT(0 != 0);
            break;
        }

        /* For CSX widgets get an index of Rx electrode, for CSD widgets an electrode index is the same as snsId */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
            {
                ioSnsId = sensorId / `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numRows;
            }
            else
            {
                ioSnsId = sensorId;
            }
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            ioSnsId = sensorId / `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numRows;
        #else
            ioSnsId = sensorId;
        #endif
        result = `$INSTANCE_NAME`_GetSensorCapacitanceExt(widgetId, ioSnsId);

        /* For CSX widgets get an index of Tx electrode and repeat the test */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
            {
                ioSnsId = (sensorId % `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numRows) +
                                   `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols;

                result |= (`$INSTANCE_NAME`_GetSensorCapacitanceExt(widgetId, ioSnsId) << `$INSTANCE_NAME`_08_BIT_SHIFT);

            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
    }
    else
    {
        result = `$INSTANCE_NAME`_TST_BAD_PARAM;
    }

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorCapacitanceExt
****************************************************************************//**
*
* \brief
*  The internal function that measures a certain sensor
*  (electrode for CSX widgets) capacitance.
*
* \details
*  The function connects a certain sensor (electrode for CSX widgets)
*  to the previously configured `$INSTANCE_NAME` HW block by using the CSD mode.
*  Then measures a Cp by using the `$INSTANCE_NAME`_GetCapacitanceExt function.
*  After measuring the function sets an inactive connection of the sensor
*  (electrode for CSX widgets) and stores the Cp value in the corresponding
*  register of the `$INSTANCE_NAME`_RAM_SNS_STRUCT.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget
*  which capacitance will be measured.
*
* \return
*  - Cp of a certain capacitor in pF.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_GetSensorCapacitanceExt(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 result;
    uint8 * cpPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsCpArr + ioSnsId;

    /* Connect the specified sensor */
    `$INSTANCE_NAME`_BistConnectSensor(wdgtId, ioSnsId);

    result = `$INSTANCE_NAME`_GetCapacitanceExt();

    /* Disconnect the sensor */
    `$INSTANCE_NAME`_BistSetInactiveSensorConnection(wdgtId, ioSnsId);

    if (`$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP < result)
    {
        result = `$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP;
    }

    /* Save cp to data structure */
    *cpPtr = (uint8)result;

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConnectSensor
****************************************************************************//**
*
* \brief
*  Connects a sensor (including ganged) port-pin to the sensing HW block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and
*   PC registers.
*
* \param
*   wdgtIndex Specifies ID of the widget.
*   sensorIndex Specifies ID of the sensor in the widget.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConnectSensor(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1u;
    }

    /* Loop through all electrodes of specified sensor */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Set electrode to CSD_SENSE mode to be scanned */
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
        `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
        ioPtr++;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureAllSensorCapacitance
****************************************************************************//**
*
* \brief
*  The internal function that measures all the sensors Cp capacitance.
*
* \details
*  The function that measures Cp of all the sensors by using
*  `$INSTANCE_NAME`_GetSensorCapacitance function.
*  The function stores the Cp values in the corresponding BIST data
*  structure registers.
*
* \return
*  Returns the status of the measuring process:
*  - CY_RET_SUCCESS.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_MeasureAllSensorCapacitance(void)
{
    uint32 wdgtId;
    uint32 ioSnsId;
    uint32 totalNumIoSns;
    uint32 result = CY_RET_SUCCESS;

    /* Loop through all the widgets */
    for (wdgtId = 0u; wdgtId < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtId++)
    {
        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
        {
        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

        default:
            CY_ASSERT(0 != 0);
            break;
        }

        /* Get a total number of widget elements: for CSX it is numRows + numCols, for CSD it is totalNumSns */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
            {
                totalNumIoSns = (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows + `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numCols;
            }
            else
            {
                totalNumIoSns = (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].totalNumSns;
            }
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            totalNumIoSns = (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows + `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numCols;
        #else
            totalNumIoSns = (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].totalNumSns;
        #endif

        /* Loop through all the sensors */
        for (ioSnsId = 0u; ioSnsId < totalNumIoSns; ioSnsId++)
        {
            (void)`$INSTANCE_NAME`_GetSensorCapacitanceExt(wdgtId, ioSnsId);
        }
    }
    return result;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetShieldCapacitance
****************************************************************************//**
*
* \brief
*  Measures the shield electrode capacitance.
*
* \details
*  The function measures capacitance of the shield electrode and returns the
*  result, alternatively the result is stored in
*  `$INSTANCE_NAME`_SHIELD_CAP_VALUE of data structure. If the shield consists
*  of several electrodes, total capacitance of all shield electrodes is
*  reported.
*
*  While measuring capacitance of shield electrode, the sensor states are
*  inherited from the Component configuration. All the CSX electrodes are
*  set to active low (GND) and all the CSD electrodes are set to state defined
*  by the inactive sensor state parameter in the Component CSD Setting tab
*  of the customizer.
*
*  The measurable capacitance range using this function is from 5pF to 255pF.
*
*  This test can be executed for all the sensors at once using the
*  `$INSTANCE_NAME`_RunSelfTest() function with the `$INSTANCE_NAME`_TST_SH_CAP
*  mask.
*
* \return
*  The shield electrode capacitance (in pF)
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetShieldCapacitance(void)
{
    uint32 result;

    `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SH_CAP_E);

    #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
        `$INSTANCE_NAME`_BistConnectShieldAsSensor();
    #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */

    result = `$INSTANCE_NAME`_GetCapacitanceExt();

    /* Disconnect shield electrodes */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
        `$INSTANCE_NAME`_BistDisableShieldElectrodes();
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

    if (`$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP < result)
    {
        result = `$INSTANCE_NAME`_BIST_SNS_CAP_MAX_CP;
    }

    /* Save a capacitance value to the data structure */
    `$INSTANCE_NAME`_dsRam.selfTest.shieldCap = (uint16)result;

    return result;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCapacitanceExt
****************************************************************************//**
*
* \brief
*  The internal function that measures a capacitance attached to AMUXBUS.
*
* \details
*  The function measures Cp of a certain sensor or shield by using the
*  CSD mode and defined Idac mode, sense clock frequency and resolution.
*  The range for sensor measuring is 5 to 250 pF, for shield 10 to 250 pf.
*  The function calibrates the Idac for reach a defined target of raw counts.
*  If reached Idac will be lower then a certain value the function sets
*  the higher sense clock frequency.
*  The function stores the Cp value in the corresponding register of
*  `$INSTANCE_NAME`_RAM_SNS_STRUCT.
*
* \return
*  - Cp of  a certain sensor or shield in pF.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_GetCapacitanceExt(void)
{
    uint32 cp;
    uint32 idacValue = 0uL;
    uint32 snsClkIncrementIndex;
    uint32 idacMask = ((uint32)`$INSTANCE_NAME`_BIST_CAL_MIDDLE_BIT << 1uL);

    if (`$INSTANCE_NAME`_BIST_HW_SH_CAP_E == `$INSTANCE_NAME`_bistHwConfig)
    {
        snsClkIncrementIndex = 0uL;
    }
    else
    {
        snsClkIncrementIndex = 1uL;
    }

    /* Initialize raw count for first cycle pass */
    `$INSTANCE_NAME`_bistRawcount = 0u;

    `$INSTANCE_NAME`_BistSetScanDuration();

    /* Finding optimal IDAC and Frequency */
    while (0uL != idacMask)
    {
        /* Decrease IDAC until rawData reaches the calibration target */
        if (`$INSTANCE_NAME`_BIST_CALIBRATION_TARGET > `$INSTANCE_NAME`_bistRawcount)
        {
            idacValue &= (uint32)(~idacMask);
        }
        idacMask >>= 1uL;
        idacValue |= idacMask;
        if (0uL == idacValue)
        {
            idacValue++;
        }

        /* Revert back Idac value and increase SnsClk frequency if Idac is too small */
        if (idacValue < `$INSTANCE_NAME`_BIST_MIN_IDAC_VALUE)
        {
            if ((`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER >> (snsClkIncrementIndex + 1uL)) >= `$INSTANCE_NAME`_TST_MIN_SNS_CLK_DIVIDER)
            {
                snsClkIncrementIndex++;
                idacMask = (uint32)(`$INSTANCE_NAME`_BIST_CAL_MIDDLE_BIT);
                idacValue = idacMask;
            }
        }

        /*
        * Setup scan parameters:
        * - IDAC
        * - SnsClk
        * - Resolution (conversion number)
        */
        `$INSTANCE_NAME`_BistSetIdac(idacValue);
        `$INSTANCE_NAME`_BistConfigClock((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER >> snsClkIncrementIndex);

        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR, ((uint32)`$INSTANCE_NAME`_BIST_10_BIT_MASK /
                                        ((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER >> snsClkIncrementIndex)) &
                                        `$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_CONV_CNT_MSK);

        /* Perform scanning */
        `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;
        `$INSTANCE_NAME`_BistStartSample();
        `$INSTANCE_NAME`_WaitEndOfScan(`$INSTANCE_NAME`_BIST_CALIBR_WATCHDOG_CYCLES_NUM);
    }

    /*
    * Capacitance calculation:
    *   cp(pF) = Raw_count * IdacCode * IdacGain(nA) * 1000 / (MaxRaw * SnsClk(kHz) * Vref(mV))
    * Details:
    *   - The order of calculation is changed to avoid the potential overflow
    *   - The half of the last divider is added to implement the value rounding
    */
    cp = (`$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN * `$INSTANCE_NAME`_BIST_SNS_CAP_UNIT_SCALE) / `$INSTANCE_NAME`_CSD_VREF_MV;
    cp = (cp * idacValue) / `$INSTANCE_NAME`_BIST_10_BIT_MASK;
    cp = cp * (uint32)`$INSTANCE_NAME`_bistRawcount;
    cp = (cp + (((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_KHZ << snsClkIncrementIndex) >> 1uL)) /
                ((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_KHZ << snsClkIncrementIndex);

    return cp;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistDisableHwSnsCap
****************************************************************************//**
*
* \brief
*  This function disables CSD mode.
*
* \details
*  To disable CSD mode the following tasks are performed:
*  1. Disconnect Cmod from AMUXBUS-A.
*  2. Disconnect previous CSX electrode if it has been connected.
*  3. Disconnect Csh from AMUXBUS-B.
*  4. Disable Shield Electrodes.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistDisableHwSnsCap(void)
{
    /* Disconnect Cmod from AMUXBUS-A using HSIOM registers */
    uint32  interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN,
                                                          (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);
    #else
        Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM, (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);
        Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM, (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

    Cy_SysLib_ExitCriticalSection(interruptState);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
        /* Verification of the bist mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Disconnect Csh from AMUXBUS-B */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                       (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);
                Cy_SysLib_ExitCriticalSection(interruptState);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

            /* Disconnect shield electrodes */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
                `$INSTANCE_NAME`_BistDisableShieldElectrodes();
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
                /*
                * Disconnect all IOs from AMUXBUS_B as all rest tests suppose the electrodes are not
                * connected to any bus. It is done for performance optiomization:
                * not to write HSIOM register each time at test type switching.
                */
                `$INSTANCE_NAME`_SetAllIOHsiomState(`$INSTANCE_NAME`_TST_HSIOM_GPIO);
            #endif
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
}


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection
    ****************************************************************************//**
    *
    * \brief
    *  Resets all the CSD sensors to the non-sampling state by sequential
    *  disconnecting all the sensors from the Analog MUX bus and putting them to
    *  an inactive state.
    *
    * \details
    *   The function goes through all the sensors of CSD widgets and updates appropriate bits in
    *   the IO HSIOM, PC and DR registers depending on the Inactive sensor connection
    *   parameter. DR register bits are set to zero when the Inactive sensor
    *   connection is Ground or Hi-Z.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection(void)
    {
        uint32 wdgtId;
        uint32 snsId;

        for (wdgtId = 0uL; wdgtId < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtId++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
            {
                /* Go through all the sensors in widget */
                for (snsId = 0uL; snsId < (uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].totalNumSns; snsId++)
                {
                    `$INSTANCE_NAME`_BistSetInactiveSensorConnection(wdgtId, snsId);
                }
            }
        }
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSetInactiveSensorConnection
****************************************************************************//**
*
* \brief
*  Sets an inactive state for a certain sensor (electrode).
*
* \details
*  The function updates appropriate bits in the IO HSIOM and PC registers
*  depending on the Inactive sensor connection parameter.
*  The function proceeds ganged sensors(electrodes).
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param ioSnsId
*  Specifies the ID number of the sensor (electrode) within the widget to be processed.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSetInactiveSensorConnection(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1uL;
    }

    /* Loop through all electrodes of specified sensor */
    for (eltdIndex = 0uL; eltdIndex < eltdNum; eltdIndex++)
    {
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
                /* Update port configuration register (drive mode to HiZ Analog) for sensor */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
                /* Connect to Shield */
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_CSD_SHIELD);
            #else
                /* Update HSIOM register to disconnect sensor */
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
                /* Set drive mode for elecctrode based on inactive sensor connection parameter */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_INACTIVE_SNS_GPIO_DM);
            #endif /* (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION) */
        }
        else if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Update HSIOM register to disconnect sensor */
            `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
            /* Update port configuration register (drive mode to HiZ Analog) for sensor */
            `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
        }
        else if (`$INSTANCE_NAME`_BIST_HW_SH_CAP_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
                /* Set electrode to CSD_SENSE mode to be scanned */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
            #else
                /* Update HSIOM register to disconnect sensor */
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
                /* Set drive mode for elecctrode based on inactive sensor connection parameter */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_INACTIVE_SNS_GPIO_DM);
            #endif /* (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION) */
        }
        else
        {
            /* Do nothing */
        }
        ioPtr++;
    }
}

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistDisableShieldElectrodes
****************************************************************************//**
*
* \brief
*   This internal function disables Shield Electrodes.
*
* \details
*   The function resets the bit in the HSIOM register which disables the shield
*   electrode functionality on the pin. The port and pin configurations are
*   stored in  the `$INSTANCE_NAME`_shieldIoList structure.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistDisableShieldElectrodes(void)
{
    uint32 shieldIndex;
    uint32  interruptState;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;

    for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
    {
        ioPtr = &`$INSTANCE_NAME`_shieldIoList[shieldIndex];
        /*
        *  Reset HSIOM register (to GPIO state)
        *  Update port configuration register (drive mode to ground)
        *  Set logic 0 to port data register
        */
        interruptState = Cy_SysLib_EnterCriticalSection();
        Cy_GPIO_SetHSIOM(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
        Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, `$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
        Cy_GPIO_Clr(ioPtr->pcPtr, (uint32)ioPtr->pinNumber);
        Cy_SysLib_ExitCriticalSection(interruptState);
    }
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistPostSingleScan
****************************************************************************//**
*
* \brief
*  This is an internal ISR function for the single-sensor scanning implementation.
*
* \details
*  This ISR handler is triggered when the CSD scan for a capacitance measuring
*  is finished.
*
*  The following tasks are performed:
*    1. Disable the CSD interrupt.
*    2. Read the Counter register and update the `$INSTANCE_NAME`_bistRawcount with raw data.
*    3. Reset the BUSY flag.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistPostSingleScan(void)
{
    uint32 tmpRawData;

    /* Clear pending interrupt */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

    /* Read SlotResult from Raw Counter */
    tmpRawData = CY_GET_REG32(`$INSTANCE_NAME`_CSD_RESULT_VAL1_PTR);
    tmpRawData &= `$INSTANCE_NAME`_CSD_RESULT_VAL1_VALUE_MSK;
    if((`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION - 1uL) < tmpRawData)
    {
        tmpRawData = (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION - 1uL);
    }
    `$INSTANCE_NAME`_bistRawcount = CY_LO16(tmpRawData);

    /* Sensor is totally scanned. Reset BUSY flag */
    `$INSTANCE_NAME`_dsRam.status &= ~(`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_WDGT_SW_STS_BUSY);
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
         (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV))
        /* Disconnect Vrefhi from AMUBUF positive input. Disconnect AMUBUF output from CSDBUSB with sych PHI2+HSCMP */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_SW_DEFAULT);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
               (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV)) */

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        /* Open HCBV and HCBG switches */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN |
                                                             `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistStartSample
****************************************************************************//**
*
* \brief
*   Starts the CSD conversion for a capacitance measuring.
*
* \details
*   This function assumes that the CSD block is already set up using
*   the `$INSTANCE_NAME`_BistEnableHwSnsCap function and the capacitance
*   is connected to the CSD block.
*   The function performs the following tasks:
*   1. Disables the CSD interrupt
*   2. Enables CSD block if it was disabled
*   3. Precharges Cmod (only for a sensor capacitance measuring)
*   4. Starts the scan.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistStartSample(void)
{
    /* Disable interrupt */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        NVIC_DisableIRQ(`$INSTANCE_NAME`_ISR_cfg.intrSrc);
    #endif

    /* Enable power to sub-blocks */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, `$INSTANCE_NAME`_BIST_HSCMP_CFG);

    if (`$INSTANCE_NAME`_bistHwConfig != `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E)
    {
        /* Precharging Cmod and Csh */
        `$INSTANCE_NAME`_BistCmodPrecharge();
    }

    /* Trigger Scan */
    `$INSTANCE_NAME`_BistTriggerScan();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistEnableHwSnsCap
****************************************************************************//**
*
* \brief
*  Sets up the `$INSTANCE_NAME` block to perform a capacitanse measuring.
*
* \details
*   This function prepare HW of the `$INSTANCE_NAME` block to CSD sensing mode
*   with BIST defined parameters.
*   The function performs the following tasks:
*   1. Sets the default CSD configuration for BIST scans
*   2. Enables shield electrodes and Csh (if defined)
*   3. Sets Idac config for BIST scans
*   4. Sets a sensor clock frequency (only for a sensor capacitance measuring)
*   5. Sets the ISR handler for BIST scans.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableHwSnsCap(void)
{
    uint32 newRegValue;

    static volatile uint32 `$INSTANCE_NAME`_bistConfigCsd = `$INSTANCE_NAME`_BIST_CSD_CONFIG;

    `$INSTANCE_NAME`_BistDischargeExtCapacitors();

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
        /* Verification of the bist mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                /* Connect shields to AMUX-B bus (config HSIOM regs) */
                #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
                    `$INSTANCE_NAME`_BistEnableShieldElectrodes();
                #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                    /* Configure Csh */
                    `$INSTANCE_NAME`_BistEnableShieldTank();
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */

    /* Initialize the unused CSD IP registers to defaut state */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_DUTY_PTR,       `$INSTANCE_NAME`_BIST_CAP_SENSE_DUTY_SEL);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_SET_PTR,         `$INSTANCE_NAME`_BIST_INTR_SET_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_BIST_DEFAULT_CSD_SW_DSI_SEL);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_ADC_CTL_PTR,          `$INSTANCE_NAME`_BIST_ADC_CTL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_AMBUF_PTR,            `$INSTANCE_NAME`_BIST_AMBUF_PWR_MODE_OFF);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_BIST_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR,            `$INSTANCE_NAME`_BIST_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_TIME_PTR,         `$INSTANCE_NAME`_BIST_AUTO_ZERO_TIME);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_RES_PTR,           `$INSTANCE_NAME`_BIST_SW_RES_INIT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IO_SEL_PTR,           `$INSTANCE_NAME`_BIST_DEFAULT_CSD_IO_SEL);

    /* Connect AMUXBUS-A to CSDBUS-A */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR);
    newRegValue |= `$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYA_MSK;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR, newRegValue);

    /* Verification of the bist mode */
    if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            /* Connect CMOD to AMUXBUS-A */
            Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN, CY_GPIO_DM_ANALOG);
            Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CMOD_PORT_PTR, `$INSTANCE_NAME`_CSD_CMOD_PIN,
                                                                  (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_AMUXA);

            /* Connect CMOD to (sense path) to CSDCOMP */
            #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE);
            #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE);
            #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
        #else
            Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintA_PORT, (uint32)`$INSTANCE_NAME`_CintA_NUM, CY_GPIO_DM_ANALOG);
            Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintA_PORT, `$INSTANCE_NAME`_CintA_NUM, (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_AMUXA);

            Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintB_PORT, (uint32)`$INSTANCE_NAME`_CintB_NUM, CY_GPIO_DM_ANALOG);
            Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CintB_PORT, `$INSTANCE_NAME`_CintB_NUM, (en_hsiom_sel_t)`$INSTANCE_NAME`_TST_HSIOM_AMUXA);

            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
    }

    /* Verification of the bist mode */
    if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
    {
        /* Configure shield driving path */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Connect AMUXBUS-B to CSDBUS-B (and AMUXBUS-A to CSDBUS-A ) */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYA_MSK |
                                                              `$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYB_MSK);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
    }

    /* Connect VREF to REFGEN (IAIB switch is open) */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR);
    newRegValue |= `$INSTANCE_NAME`_BIST_SW_REFGEN_SEL_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR, newRegValue);

    #if (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV)

        /* Connect VREFHI to CSDCOMP */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_SW_DEFAULT);
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, `$INSTANCE_NAME`_CSD_REFGEN_WITH_SHIELD_CFG);
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_AMBUF_PTR, `$INSTANCE_NAME`_CSD_AMBUF_PWR_MODE_NORM);
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, `$INSTANCE_NAME`_CSD_REFGEN_NO_SHIELD_CFG);
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_AMBUF_PTR, `$INSTANCE_NAME`_CSD_AMBUF_PWR_MODE_OFF);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
    #else

        /* Connect VREFHI (from RefGen) to CSDCOMP when Vdda >= 2 V */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)

            /* Configure REFGEN. Set reference voltage when Vdda >= 2 V */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, `$INSTANCE_NAME`_CSD_REFGEN_WITH_SHIELD_CFG);

            /* Turn on CSD_AMBUF high power level when Vdaa >= 2V */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_AMBUF_PTR, `$INSTANCE_NAME`_CSD_AMBUF_PWR_MODE_HI);
        #else

            /* Configure REFGEN. Set reference voltage when Vdda >= 2 V */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, `$INSTANCE_NAME`_CSD_REFGEN_NO_SHIELD_CFG);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        /* Make sure that CSD_AMBUF is unconnected from Vrefhi and from Vreflo */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_SW_DEFAULT);
    #endif /* (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV) */

    if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
    {
        /* Configure ModClk */
        `$INSTANCE_NAME`_ModClk_SetDivider((uint32)(`$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER - 1uL));
    }

    /* Verification of the bist mode */
    if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Update CSD config register shield delay bits with shield delay value */
            `$INSTANCE_NAME`_bistConfigCsd &= (uint32)(~`$INSTANCE_NAME`_CSD_CONFIG_SHIELD_DELAY_MSK);
            `$INSTANCE_NAME`_bistConfigCsd |= ((uint32)`$INSTANCE_NAME`_CSD_SHIELD_DELAY <<
                                               `$INSTANCE_NAME`_CSD_CONFIG_SHIELD_DELAY_POS);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
    }

    /* Configure HW IP block filter delay */
    `$INSTANCE_NAME`_bistConfigCsd &= (uint32)(~`$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_MSK);
    `$INSTANCE_NAME`_bistConfigCsd |= `$INSTANCE_NAME`_FILTER_DELAY_CFG;

    /* Enable power to sub-blocks */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd |
                                                  `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN_MSK |
                                                  `$INSTANCE_NAME`_CSD_CONFIG_ENABLE_MSK);

    #if(`$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US > 0uL)
        Cy_SysLib_DelayUs(`$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US);
    #endif /* (`$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US > 0uL) */

    /* Set the number of dummy fine initialization cycles depending of the bist mode */
    /* Set Phi1 and Phi2 switches to non-overlapping (no low EMI) and width depending of the bist mode */
    if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_INIT_CNT_PTR, `$INSTANCE_NAME`_TST_FINE_INIT_TIME);
    }
    else
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_INIT_CNT_PTR, `$INSTANCE_NAME`_SEQ_INIT_CNT_FINE_INIT_SKIP);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_DUTY_PTR, `$INSTANCE_NAME`_SENSE_DUTY_TST_EXT_CAP_WIDTH );
    }

    /* Configure IDAC */
    `$INSTANCE_NAME`_BistSetIdac(0uL);

    if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
    {
        /* Set clock dividers and clock source mode */
        `$INSTANCE_NAME`_BistConfigClock(`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER);
    }
    else
    {
    }
    `$INSTANCE_NAME`_SsIsrInitialize(&`$INSTANCE_NAME`_BistPostSingleScan);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConfigClock
****************************************************************************//**
*
* \brief
*   Sets the sensor clock frequency for BIST scans
*
* \details
*   For a sensor or shield capasitance measurement sets a calculated value of
*   the sensor clock frequency and for an external capacitance measurement sets
*   the value for a one period scan.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConfigClock(uint32 snsClk)
{
    uint32 newRegValue;

    /*
     * Set divider value for sense clock.
     * 1u is subtracted from snsClk because SENSE_DIV value 0 corresponds
     * to dividing by 1.
     */
    newRegValue = (snsClk - 1u) & `$INSTANCE_NAME`_CSD_SENSE_PERIOD_SENSE_DIV_MSK;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_PERIOD_PTR, newRegValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSetScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by scan resolution
*
* \details
*   The function calculates the number of conversions and updates
*   SEQ_NORM_CNT register. The number of conversions depends on resolution and
*   snsClk divider.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSetScanDuration(void)
{
    uint32 scanDuration;

    if (`$INSTANCE_NAME`_bistHwConfig == `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E)
    {
        scanDuration = `$INSTANCE_NAME`_TST_EXT_CAP_DURATION;
    }
    else
    {
        /* Calculate scanning resolution value in register */
        scanDuration = (uint32) (`$INSTANCE_NAME`_BIST_10_BIT_MASK / `$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER);
    }

    /* Set Number Of Conversions based on scanning resolution */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR, scanDuration & `$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_CONV_CNT_MSK);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSetIdac
****************************************************************************//**
*
* \brief
*   This internal function changes the IDACs values for BIST scan.
*
* \details
*   The functions disables the compensation IDAC if enabled and sets
*   desired Idac value.
*
* \param idacValue
*   The Idac code to be set.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSetIdac(uint32 idacValue)
{
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACA_PTR, `$INSTANCE_NAME`_BIST_IDACA_CFG | (idacValue & `$INSTANCE_NAME`_CSD_IDACA_VAL_MSK));
    #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IDACB_USED))
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACB_PTR, `$INSTANCE_NAME`_BIST_IDACB_CFG);
    #endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistCmodPrecharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  Coarse initialization for CMOD and Cch.
*  The coarse initialization is performed by HSCOMP.
*  The HSCOMP monitors the Cmod voltage via Cmod sense path
*  and charges the Cmod using HCAV switch via CSDBUS-A, AMUXBUS-A
*  and static connection of Cmod to AMUXBUS-A.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistCmodPrecharge(void)
{
        uint32 watchdogCounter;

        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, `$INSTANCE_NAME`_BIST_CSDCMP_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR,  `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR,  `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_INIT);
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN))
            /*
             * Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad
             * Connect AMUXBUS-B to HSCMP positive input
             */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_COARSE);
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);

            #if(0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                /* Connect CTANK to AMUXBUS-A */
                Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                           (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_AMUXA);
            #endif /* (0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
        #else
            /* Connect CMOD to (sense path) to HSCOMP: HMPM or HMPS or HMPT switches depend on Cmod connects to certain pad */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_COARSE);
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN))
            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                /* Verification of the bist mode */
                if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
                {
                    /* Connect CTANK to AMUXBUS-A */
                    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)`$INSTANCE_NAME`_CSD_CTANK_PORT_PTR, `$INSTANCE_NAME`_CSD_CTANK_PIN,
                                                                       (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_AMUXA);
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_RES_PTR, `$INSTANCE_NAME`_BIST_SW_RES_INIT);

        /* Clear all interrupt pending requests */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
        (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

        /* Unmask INIT interrupt (enable interrupt) */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_MASK_PTR, `$INSTANCE_NAME`_CSD_INTR_MASK_CLEAR_MSK);

        /* Start SEQUENCER for coarse initialization for Cmod */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_CSD_SEQ_START_SEQ_MODE_MSK |
                                                         `$INSTANCE_NAME`_CSD_SEQ_START_START_MSK);

        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_BIST_PRECHARGE_WATCHDOG_CYCLES_NUM;

        /* Wait for INTR.INIT goes high */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR) & `$INSTANCE_NAME`_CSD_INTR_INIT_MSK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        if (0u == watchdogCounter)
        {
            /* Set sequencer to idle state if coarse initialization fails */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_CSD_SEQ_START_ABORT_MSK);
        }

        /* Set scanning configuration for switches */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_SCAN);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WaitEndOfScan
****************************************************************************//**
*
* \brief
*   Waits the end of scan for capacitance measurements.
*
* \details
*   Apart the waiting end of scan the function sets a watchdog to prevent
*   a hangout
*
*******************************************************************************/
static void `$INSTANCE_NAME`_WaitEndOfScan(uint32 timeout)
{
    uint32 watchdogCounter = timeout;

    while (((`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY) != 0u) &&
           (0u != watchdogCounter))
    {
        watchdogCounter--;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistTriggerScan
****************************************************************************//**
*
* \brief
*  This function triggers the scanning.
*
* \details
*  Trigger the fine initialization (scan some dummy cycles only for sensor or
*  shield capacitance meterings) and start sampling.
*  For the fine initialization and sampling the measured capacitance is charged
*  from Idac and discharged to ground using the switches in GPIO cell.
*  The CSDCOMP monitors voltage on the measured capacitance using the sense path
*  and charges it to Vref using IDAC.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistTriggerScan(void)
{
    uint32 watchdogCounter;

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

    /* Enable interrupt */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        NVIC_EnableIRQ(`$INSTANCE_NAME`_ISR_cfg.intrSrc);
    #endif

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_BIST_HS_P_SEL_SCAN);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
        /* Verification of the bist mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)

                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR,  `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG);
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                    `$INSTANCE_NAME`_BistEnableShieldTank();
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
                CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        }
        else
        {
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
        }
    #else
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_RES_PTR, `$INSTANCE_NAME`_BIST_SW_RES_SCAN);

    /* Enable CSDCMP */
    if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E == `$INSTANCE_NAME`_bistHwConfig)
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, `$INSTANCE_NAME`_CSDCMP_TST_CAP_MEAS);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR,  `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_CSD_WAVEFORM_STATIC_OPEN);
    }
    else
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, `$INSTANCE_NAME`_CSD_CSDCMP_CSDCMP_EN_MSK);
    }

    /* Verification of the bist mode */
    if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, `$INSTANCE_NAME`_BIST_HSCMP_SCAN_MASK);
        #else
            /* Disable HSCOMP during the sampling phase when shield is disabled */
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, 0uL);
        #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
    }
    else
    {
        /* Disable HSCOMP during the sampling phase when shield is disabled */
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, 0uL);
    }
    /* Enable SAMPLE interrupt */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_MASK_PTR, `$INSTANCE_NAME`_CSD_INTR_MASK_SAMPLE_MSK);

    /* Init Watchdog Counter to prevent a hang */
    watchdogCounter = `$INSTANCE_NAME`_BIST_PRECHARGE_WATCHDOG_CYCLES_NUM;
    /* Wait for IDLE state of the HW sequencer */
    while((0u != (`$INSTANCE_NAME`_CSD_STAT_SEQ_REG & `$INSTANCE_NAME`_CSD_STAT_SEQ_SEQ_STATE_MSK)) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    }

    /* Start SEQUENCER for fine initialization scan for Cmod and then for normal scan */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_CSD_SEQ_START_AZ0_SKIP_MSK |
                                                     `$INSTANCE_NAME`_CSD_SEQ_START_AZ1_SKIP_MSK |
                                                     `$INSTANCE_NAME`_CSD_SEQ_START_START_MSK);
}
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetVdda
****************************************************************************//**
*
* \brief
*  Measures and returns the VDDA voltage.
*
* \details
*  This function measures voltage on VDDA terminal of the chip and returns
*  the result, alternatively the result is stores in the
*  `$INSTANCE_NAME`_VDDA_VOLTAGE_VALUE register of data structure.
*
* \return
*  The VDDA voltage in mV.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetVdda(void)
{
    uint16 tmpResult;

    `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_VDDA_E);
    tmpResult = `$INSTANCE_NAME`_BistVddaRunMeasurement();
    `$INSTANCE_NAME`_dsRam.selfTest.vddaVoltage = tmpResult;

    return (tmpResult);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistEnableVddaMeasurement
****************************************************************************//**
*
* \brief
*  Configures the CSD block to be used for VDDA measurement.
*
* \details
*  Configures the IDACB, HW IP block internal switches, REFGEN, HSCOMP and
*  interrupt.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableVddaMeasurement(void)
{
    /* Configure clocks */
    `$INSTANCE_NAME`_ModClk_SetDivider(`$INSTANCE_NAME`_TST_VDDA_MODCLK_DIV_DEFAULT - 1uL);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_PERIOD_PTR, (`$INSTANCE_NAME`_TST_VDDA_SENSE_DIV_DEFAULT - 1uL));

    /* Configure the IDAC */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_TST_VDDA_CONFIG_DEFAULT_CFG);

    #if(`$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US > 0uL)
        Cy_SysLib_DelayUs(`$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US);
    #endif /* (`$INSTANCE_NAME`_TST_ANALOG_STARTUP_DELAY_US > 0uL) */

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACB_PTR, `$INSTANCE_NAME`_TST_VDDA_IDACB_DEFAULT_CFG);

    /* Configure AZ Time */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_TIME_PTR, (`$INSTANCE_NAME`_TST_VDDA_SEQ_TIME_DEFAULT - 1u));

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACA_PTR, `$INSTANCE_NAME`_TST_VDDA_IDACA_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, `$INSTANCE_NAME`_TST_CSDCMP_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_DSI_SEL_PTR, `$INSTANCE_NAME`_TST_SW_DSI_SEL_DEFAULT_CFG);

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_DUTY_PTR, `$INSTANCE_NAME`_TST_SENSE_DUTY_VDDA_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_INIT_CNT_PTR, `$INSTANCE_NAME`_TST_SEQ_INIT_CNT_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR, `$INSTANCE_NAME`_TST_SEQ_NORM_CNT_DEFAULT_CFG);

    /* Configure the block-level routing */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_TST_SW_HS_P_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_TST_SW_HS_N_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_TST_SW_SHIELD_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR, `$INSTANCE_NAME`_TST_SW_BYP_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_TST_SW_CMP_P_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_TST_SW_CMP_N_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_TST_SW_FW_MOD_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_TST_SW_FW_TANK_SEL_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR, `$INSTANCE_NAME`_TST_SW_REFGEN_SEL_DEFAULT_CFG);

    /* Config RefGen */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR, `$INSTANCE_NAME`_TST_REFGEN_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_TST_SW_AMUXBUF_SEL_DEFAULT_CFG);

    /* Configure HSCOMP */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, `$INSTANCE_NAME`_TST_HSCMP_DEFAULT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_MASK_PTR, `$INSTANCE_NAME`_CSD_INTR_MASK_CLEAR_MSK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistVddaRunMeasurement
****************************************************************************//**
*
* \brief
*  This function triggers the VDDA measurement.
*
* \details
*  The function initiates a conversion, waits for completion and
*  returns the result in mV.
*  The function returns voltage in millivolts or
*  `$INSTANCE_NAME`_TST_VDDA_BAD_RESULT if:
*   - The ADC conversion is not started
*   - The ADC conversion watch-dog triggered.
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_BistVddaRunMeasurement(void)
{
    uint16 tVdda2Vref;
    uint16 tVssa2Vref;
    uint16 tRecover;
    uint16 tmpResult;
    uint32 tmpVrefCal;
    uint32 registerValue;
    uint32 watchdogCounter;
    uint32 interruptState;

    watchdogCounter = `$INSTANCE_NAME`_TST_SW_WATCHDOG_CYCLES_NUM;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_ADC_CTL_PTR, (`$INSTANCE_NAME`_TST_MEASMODE_VREF | (`$INSTANCE_NAME`_VDDA_ACQUISITION_BASE - 1u)));
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_TST_VDDA_SEQ_START_MEASURE_CFG);

    /* Wait for INTR.INIT goes high */
    while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR) & `$INSTANCE_NAME`_CSD_INTR_ADC_RES_MSK)) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    }

    /* Clear all interrupt pending requests */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

    tVssa2Vref = (uint16)CY_GET_REG32(`$INSTANCE_NAME`_CSD_ADC_RES_PTR);

    if(0uL != watchdogCounter)
    {
        watchdogCounter = `$INSTANCE_NAME`_TST_SW_WATCHDOG_CYCLES_NUM;
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_ADC_CTL_PTR, (`$INSTANCE_NAME`_TST_MEASMODE_VREFBY2 | (`$INSTANCE_NAME`_VDDA_ACQUISITION_BASE - 1u)));
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_TST_VDDA_SEQ_START_MEASURE_CFG);

        /* Wait for INTR.INIT goes high */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR) & `$INSTANCE_NAME`_CSD_INTR_ADC_RES_MSK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
        (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);
    }
    else
    {
        /* Do nothing. */
    }

    tRecover = (uint16)CY_GET_REG32(`$INSTANCE_NAME`_CSD_ADC_RES_PTR);
    if(0uL != watchdogCounter)
    {
        /* Disconnect amuxbusB, Connect VDDA to csdbusB */
        interruptState = Cy_SysLib_EnterCriticalSection();
        registerValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR);
        registerValue &= (uint32)(~(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYA_MSK | `$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYB_MSK));
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR, registerValue);
        Cy_SysLib_ExitCriticalSection(interruptState);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_SW_HCBV_STATIC_CLOSE);

        watchdogCounter = `$INSTANCE_NAME`_TST_SW_WATCHDOG_CYCLES_NUM;
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_ADC_CTL_PTR, (`$INSTANCE_NAME`_TST_MEASMODE_VIN | (`$INSTANCE_NAME`_VDDA_ACQUISITION_BASE - 1u)));
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_TST_VDDA_SEQ_START_MEASURE_CFG);

        /* Wait for INTR.INIT goes high */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR) & `$INSTANCE_NAME`_CSD_INTR_ADC_RES_MSK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
        (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

        tVdda2Vref = (uint16)CY_GET_REG32(`$INSTANCE_NAME`_CSD_ADC_RES_PTR);
        /* Test whether the full range is 2-bits higher than adc resolution */

        tVdda2Vref = (uint16)(((((uint32)tVdda2Vref << 1u) * tRecover) + ((uint32)tVssa2Vref >> 1u)) / tVssa2Vref);

        /* Get Vref trim-value */
        tmpVrefCal = (`$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_REG & `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MSK) >>
                                                               `$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_POS;

        /* Update nominal Vref to real Vref */
        tmpVrefCal *= `$INSTANCE_NAME`_TST_VDDA_VREF_MV;
        tmpVrefCal /= `$INSTANCE_NAME`_TST_VDDA_VREF_CALIB_USED;

        tmpResult = (uint16)tmpVrefCal;

        /* Calculate deviation of trim register */
        if (tmpVrefCal > `$INSTANCE_NAME`_TST_VDDA_VREF_MV)
        {
            tmpVrefCal = tmpVrefCal - `$INSTANCE_NAME`_TST_VDDA_VREF_MV;
        }
        else
        {
            tmpVrefCal = `$INSTANCE_NAME`_TST_VDDA_VREF_MV - tmpVrefCal;
        }
        tmpVrefCal = (tmpVrefCal * `$INSTANCE_NAME`_PERCENTAGE_100) / `$INSTANCE_NAME`_TST_VDDA_VREF_MV;

        /* Use nominal Vref if trim-value is not within the allowed range */
        if (`$INSTANCE_NAME`_TST_VDDA_VREF_TRIM_MAX_DEVIATION < tmpVrefCal)
        {
            tmpResult = `$INSTANCE_NAME`_TST_VDDA_VREF_MV;
        }

        tmpResult = tmpResult + (((tmpResult * tVdda2Vref) + (tVssa2Vref >> 1uL)) / tVssa2Vref);
    }
    else
    {
        tmpResult = `$INSTANCE_NAME`_TST_VDDA_BAD_RESULT;
    }

    return(tmpResult);
}

#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSwitchHwConfig
****************************************************************************//**
*
* \brief
*   The function switches HW configuration.
*
* \details
*   The function checks the current HW configuration of `$INSTANCE_NAME` block.
*   If it differs from a desired configuration the function disables the current
*   configuration and sets the desired one.
*
* \param config
*   Specifies desired configuration.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_CONFIG_ENUM config)
{
    if (`$INSTANCE_NAME`_bistHwConfig != config)
    {
        /* The requested config differes to the current one. Disable the current config */
        switch(`$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
                case `$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E:
                {
                    /* Nothing to do */
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
                case `$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E:
                {
                    /* Nothing to do */
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
                case `$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E:
                {
                    `$INSTANCE_NAME`_BistDisableHwSnsCap();
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN))
                case `$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E:
                {
                    `$INSTANCE_NAME`_BistDisableHwSnsCap();
                    break;
                }
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
                case `$INSTANCE_NAME`_BIST_HW_SH_CAP_E:
                {
                    `$INSTANCE_NAME`_BistDisableHwSnsCap();
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)
                case `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E:
                {
                    /* Nothing to do */
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN)
                case `$INSTANCE_NAME`_BIST_HW_VDDA_E:
                {
                    /* Nothing to do */
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) */
            default:
            {
                break;
            }
        }

        `$INSTANCE_NAME`_bistHwConfig = config;

        /* Enable the specified mode */
        switch(config)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
                case `$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E:
                {
                    /* No HW CSD Block changes required */
                    `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_HIGHZA_E);
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
                case `$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E:
                {
                    /* No HW CSD Block changes required */
                    `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_STRONG_E);
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
                case `$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E:
                {
                    `$INSTANCE_NAME`_BistEnableHwSnsCap();
                    `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_CSD_E);
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN))
                case `$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E:
                {
                    `$INSTANCE_NAME`_BistEnableHwSnsCap();
                    `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_STRONG_E);
                    break;
                }
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
                case `$INSTANCE_NAME`_BIST_HW_SH_CAP_E:
                {
                    `$INSTANCE_NAME`_BistEnableHwSnsCap();
                    `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_SHIELD_E);
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)
                case `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E:
                {
                    `$INSTANCE_NAME`_BistEnableHwSnsCap();
                    `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_HIGHZA_E);
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN)
                case `$INSTANCE_NAME`_BIST_HW_VDDA_E:
                {
                    `$INSTANCE_NAME`_BistEnableVddaMeasurement();
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_VDDA_EN) */
            default:
            {
                break;
            }
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SwitchAllIOState
****************************************************************************//**
*
* \brief
*   Sets all the sensors pins in a desired state.
*
* \details
*   Sets all the sensors and shield (if defined) pins in a desired state.
*
* \param config
*   Specifies desired IO configuration.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_CONFIG_ENUM config)
{
    /* Re-configure the IOs if mode is changed */
    if (`$INSTANCE_NAME`_bistIoConfig != config)
    {
        switch(config)
        {
            case `$INSTANCE_NAME`_BIST_IO_STRONG_E:
            {
                `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
                break;
            }
            case `$INSTANCE_NAME`_BIST_IO_HIGHZA_E:
            {
                `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_HIGHZA);
                break;
            }
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
                case `$INSTANCE_NAME`_BIST_IO_CSD_E:
                {
                    /* Configure CSX sensors to Strong */
                    #if (0u != `$INSTANCE_NAME`_CSX_EN)
                        /* Set all IO to strong (including CSX IOs). It is faster than loop through only CSX sensors */
                        `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
                    #endif

                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                        /* Reconfigure only CSD sensors to required state */
                        `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection();
                    #endif

                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
                case `$INSTANCE_NAME`_BIST_IO_SHIELD_E:
                {
                    /* Configure CSX sensors to Strong */
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                        /* Set all IO to strong (including CSX IOs). It is faster than loop through only CSX sensors */
                        `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_STRONG_IN_OFF);
                    #endif

                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                        /* Reconfigure only CSD sensors to required state */
                        `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection();
                    #endif

                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) */
            default:
            {
                break;
            }
        }
        /* Save the configured state */
        `$INSTANCE_NAME`_bistIoConfig = config;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetElectrodeDr
****************************************************************************//**
*
* \brief
*  The internal function that sets a certain electrode port output data.
*
* \details
*  The function sets an electrode port output data register (DR) in a demand state.
*
* \param *ioPtr
*  A pointer to the specified electrode in the flash IO structure.
*
* \param value
*  A port output data which will be setted for an electrode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetElectrodeDr(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value)
{
    uint32  interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
    if (`$INSTANCE_NAME`_TST_DR_PIN2GND == value)
    {
        /* Set pin to logic 0 */
        Cy_GPIO_Clr(ioPtr->pcPtr, (uint32)ioPtr->pinNumber);
    }
    else
    {
        /* Set pin to logic 1 */
        Cy_GPIO_Set(ioPtr->pcPtr, (uint32)ioPtr->pinNumber);
    }
    Cy_SysLib_ExitCriticalSection(interruptState);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetElectrodePc
****************************************************************************//**
*
* \brief
*  The internal function that sets a certain electrode drive mode.
*
* \details
*  The function sets an electrode drive mode (PC register) in a demand state.
*
* \param *ioPtr
*  A pointer to the specified electrode in the flash IO structure.
*
* \param value
*  A drive mode which will be setted for an electrode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetElectrodePc(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value)
{
    uint32  interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, value);
    Cy_SysLib_ExitCriticalSection(interruptState);
}

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
    (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAllIOHsiomState
****************************************************************************//**
*
* \brief
*  The internal function that sets all pins in a demand HSIOM mode.
*
* \details
*  The function sets all pins to a demand HSIOM mode.
*
* \param value
*  A demand HSIOM mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetAllIOHsiomState(en_hsiom_sel_t value)
{
    uint32 loopIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < `$INSTANCE_NAME`_TOTAL_ELECTRODES; loopIndex++)
    {
        `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, value);
        ioPtr++;
    }
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
          (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAllIODrState
****************************************************************************//**
*
* \brief
*  The internal function that sets a specific port output data for all electrodes.
*
* \details
*  The function sets a specific port output data register (DR) in a demand state for all electrodes.
*
* \param value
*  A port output data which will be set for all electrodes.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetAllIODrState(uint32 value)
{
    uint32 loopIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < `$INSTANCE_NAME`_TOTAL_ELECTRODES; loopIndex++)
    {
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr, value);
        ioPtr++;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAllIOPcState
****************************************************************************//**
*
* \brief
*  The internal function that sets a specific drive mode for all electrodes.
*
* \details
*  The function sets a specific drive mode (PC register) in a demand state for all electrodes.
*
* \param value
*  A drive mode which will be set for all electrodes.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetAllIOPcState(uint32 value)
{
    uint32 loopIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < `$INSTANCE_NAME`_TOTAL_ELECTRODES; loopIndex++)
    {
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, value);
        ioPtr++;
    }
}

#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetElectrodeHsiom
****************************************************************************//**
*
* \brief
*  The internal function that sets a certain electrode in a demand HSIOM mode.
*
* \details
*  The function sets an electrode to a demand HSIOM mode.
*
* \param *ioPtr
*  A pointer to the specified electrode in the flash IO structure.
*
* \param value
*  A demand HSIOM mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetElectrodeHsiom(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, en_hsiom_sel_t value)
{
    /* Update HSIOM port select register */
    uint32  interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_GPIO_SetHSIOM(ioPtr->pcPtr, (uint32)ioPtr->pinNumber, value);
    Cy_SysLib_ExitCriticalSection(interruptState);
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
          ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))) */


/* [] END OF FILE */
