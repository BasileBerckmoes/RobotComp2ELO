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

#include "cytypes.h"
#include "CyLib.h"
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

/***********************************************************************************************************************
* Definition of IO register modes
***********************************************************************************************************************/

/* Port Select HSIOM Register */
#define `$INSTANCE_NAME`_TST_HSIOM_GPIO                         (0Lu)
#define `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE                    (4Lu)
#define `$INSTANCE_NAME`_TST_HSIOM_CSD_SHIELD                   (5Lu)
#define `$INSTANCE_NAME`_TST_HSIOM_AMUXA                        (6Lu)
#define `$INSTANCE_NAME`_TST_HSIOM_AMUXB                        (7Lu)

/* Port Configuration Register */
#define `$INSTANCE_NAME`_TST_PC_HIGHZA                          (0Lu)
#define `$INSTANCE_NAME`_TST_PC_PULLUP                          (2Lu)
#define `$INSTANCE_NAME`_TST_PC_PULLDOWN                        (3Lu)
#define `$INSTANCE_NAME`_TST_PC_STRONG                          (6Lu)

/* Port Data Register */
#define `$INSTANCE_NAME`_TST_DR_PIN2GND                         (0Lu)
#define `$INSTANCE_NAME`_TST_DR_PIN2VDD                         (1Lu)

/***************************************************************************//**
* \brief Defines Self Test HW Configuration
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
    `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E          = 0x06u
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
    * Sensor capacitance measurement of the CSX widget
    */
    `$INSTANCE_NAME`_BIST_IO_STRONG_E           = 0x01u,
    /* 
    * Sensor Short 
    * External capacitor measurement
    */
    `$INSTANCE_NAME`_BIST_IO_HIGHZA_E           = 0x02u,
    /*
    * Sensor capacitance measurement of the CSD widget: 
    *     All CSX sensors are set to Strong
    *     All CSD sensors depend on the Inactive sensor parameter and can be:
    *       High-Z Analog | Strong | CSD_Shield
    */
    `$INSTANCE_NAME`_BIST_IO_CSD_E              = 0x03u,
    /*
    * Shield capacitance measurement
    *     All CSX sensors are set to Strong
    *     All CSD sensors depend on the Inactive sensor parameter and can be:
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
    static volatile uint32 `$INSTANCE_NAME`_bistConfigCsd = `$INSTANCE_NAME`_BIST_CSD_CONFIG;

    #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2)
        static volatile uint32 `$INSTANCE_NAME`_bistCounterResolution = `$INSTANCE_NAME`_BIST_SCAN_DURATION;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN) */

/***********************************************************************************************************************
* Static function prototypes
***********************************************************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
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
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)   */

/* Sensor to sensor test function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
    static uint32 `$INSTANCE_NAME`_CheckAllSns2SnsShort(void);
    static void `$INSTANCE_NAME`_UpdateTestResultSns2SnsShort(uint32 wdgtId, uint32 snsId);
    static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShort(uint32 wdgtId, uint32 snsId);
    static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(uint32 wdgtId, uint32 ioSnsId);
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)   */

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
    static void `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection(void);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
        #if (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)
            static void `$INSTANCE_NAME`_BistDisableShieldElectrodes(void);
        #endif /* (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)) */

/* Measurement test group function prototypes */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN)
    CY_ISR_PROTO(`$INSTANCE_NAME`_BistPostSingleScan);
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
    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
        static void `$INSTANCE_NAME`_BistClockRestart(void);
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
    /* HW configuration switching function */
    static void `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_CONFIG_ENUM config);
    static void `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_CONFIG_ENUM config);
    /* IOs configuration function */
    static void `$INSTANCE_NAME`_SetAllIODrState(uint32 value);
    static void `$INSTANCE_NAME`_SetAllIOPcState(uint32 value);
    static void `$INSTANCE_NAME`_SetElectrodePc(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value);
    static void `$INSTANCE_NAME`_SetElectrodeDr(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value);
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
        (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
        static void `$INSTANCE_NAME`_SetAllIOHsiomState(uint32 value);
    #endif
#endif

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
     (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)))
    static void `$INSTANCE_NAME`_SetElectrodeHsiom(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
          ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))) */

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
*  The function performs the tests that correspond to the specified bits in 
*  the testEnMask parameter.
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
*
*  Refer to these functions for detail information on the corresponding test.
* 
* \param testEnMask
*  Specify the tests to be executed. Each bit corresponds to one test. It is 
*  possible to launch the function with any combination of the available tests.
*  - `$INSTANCE_NAME`_TST_GLOBAL_CRC       - Verifies the RAM structure CRC of global parameters
*  - `$INSTANCE_NAME`_TST_WDGT_CRC         - Verifies the RAM widget structure CRC for all the widgets
*  - `$INSTANCE_NAME`_TST_BSLN_DUPLICATION - Verifies the baseline consistency of all sensors (inverse copy)
*  - `$INSTANCE_NAME`_TST_SNS_SHORT        - Checks all sensors for a short to GND or VDD
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT    - Checks all sensors for a short to other sensors
*  - `$INSTANCE_NAME`_TST_SNS_CAP          - Measures all sensors capacitance
*  - `$INSTANCE_NAME`_TST_SH_CAP           - Measures the shield capacitance
*  - `$INSTANCE_NAME`_TST_EXTERNAL_CAP     - Measures the capacitance of the available external capacitors
*  - `$INSTANCE_NAME`_TST_RUN_SELF_TEST_MASK - Executes all available tests.
*
* \return
*  Returns a bit-mask with a status of execution of the specified tests:
*  - CYRET_SUCCESS - if all tests passed
*  - `$INSTANCE_NAME`_TST_NOT_EXECUTED - if previously triggered scanning is not 
*    completed
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - if a non-defined test was requested in the
*    testEnMask parameter
*  - The bit-mask of the failed tests.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_RunSelfTest(uint32 testEnMask)
{
    uint32 result = CYRET_SUCCESS;

    if(`$INSTANCE_NAME`_NOT_BUSY != `$INSTANCE_NAME`_IsBusy())
    {
        result = (uint32)`$INSTANCE_NAME`_TST_NOT_EXECUTED;
    }
    else
    {
        if (0u == (testEnMask & ((uint32)(~`$INSTANCE_NAME`_TST_RUN_SELF_TEST_MASK))))
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
                if (0u != (`$INSTANCE_NAME`_TST_GLOBAL_CRC & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckGlobalCRC();
                }         
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */
            
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)    
                if (0u != (`$INSTANCE_NAME`_TST_WDGT_CRC & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllWidgetCRC();
                }
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)   */
            
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)    
                if (0u != (`$INSTANCE_NAME`_TST_BSLN_DUPLICATION & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllBaselineDuplication();
                }
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_DUPLICATION_EN)   */

            /* All the next tests are hardware-dependent, so they request switching the sense method */
            `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)    
                if (0u != (`$INSTANCE_NAME`_TST_SNS_SHORT & testEnMask))  
                {
                    result |= `$INSTANCE_NAME`_CheckAllSensorShort();
                }
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)   */
            
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)    
                if (0u != (`$INSTANCE_NAME`_TST_SNS2SNS_SHORT & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_CheckAllSns2SnsShort();
                }
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)   */
            
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)        
                if (0u != (`$INSTANCE_NAME`_TST_SNS_CAP & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_MeasureAllSensorCapacitance();
                }
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)   */
            
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)        
                if (0u != (`$INSTANCE_NAME`_TST_SH_CAP & testEnMask))
                {
                    (void)`$INSTANCE_NAME`_GetShieldCapacitance();
                }
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)   */

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)    
                if (0u != (`$INSTANCE_NAME`_TST_EXTERNAL_CAP & testEnMask))
                {
                    result |= `$INSTANCE_NAME`_MeasureAllExtCapCapacitance();        
                }    
            #endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)   */
        }
        else
        {
            result |= (uint32)`$INSTANCE_NAME`_TST_BAD_PARAM;
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
*  The function calculates the CRC value of the `$INSTANCE_NAME`_RAM_STRUCT data 
*  structure and compares it with the stored CRC value `$INSTANCE_NAME`_GLB_CRC_VALUE.
*  
*  Use this function to verify that the register values in the `$INSTANCE_NAME`_RAM_STRUCT 
*  data structure are not corrupted.
*    
*  If the stored and calculated CRC values differ, the calculated CRC is stored to the 
*  `$INSTANCE_NAME`_GLB_CRC_CALC_VALUE register and the `$INSTANCE_NAME`_TST_GLOBAL_CRC bit
*  is set in the `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*
*  The function never clears the `$INSTANCE_NAME`_TST_GLOBAL_CRC bit.
*  `$INSTANCE_NAME`_SetParam() function is recommended for changing a 
*  `$INSTANCE_NAME`_RAM_STRUCT register. Then the CRC is updated automatically.
*  
*  Another way to launch the test is using `$INSTANCE_NAME`_RunSelfTest() function 
*  with the `$INSTANCE_NAME`_TST_GLOBAL_CRC mask.
*
* \return
*  Returns a status of the executed test:
*  - CYRET_SUCCESS - if the stored CRC matches the calculated CRC
*  - `$INSTANCE_NAME`_TST_GLOBAL_CRC - if the stored CRC is wrong.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckGlobalCRC(void)
{
    uint32 result = `$INSTANCE_NAME`_TST_GLOBAL_CRC;
    uint16 crc;

    crc = `$INSTANCE_NAME`_DsCalculateCrc16((uint8 *)&`$INSTANCE_NAME`_dsRam + 
                                    `$INSTANCE_NAME`_GLOBAL_CRC_AREA_START,
                                    `$INSTANCE_NAME`_GLOBAL_CRC_AREA_SIZE);
    if (`$INSTANCE_NAME`_dsRam.glbCrc == crc)
    {
        result = CYRET_SUCCESS;
    }
    else
    {
        `$INSTANCE_NAME`_dsRam.selfTest.glbCrcCalc = crc;
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
*   and writes it to the data structure.
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
*  The function calculates the CRC value of the `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT 
*  data structure of the specified widget and compares it with the stored CRC value 
*  `$INSTANCE_NAME`_<WidgetName>_CRC_VALUE.
*  
*  Use this function to verify that the register values in the `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT 
*  data structure are not corrupted.
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
*  It is possible to execute the test for all the widgets using
*  the `$INSTANCE_NAME`_RunSelfTest() function with the `$INSTANCE_NAME`_TST_WDGT_CRC mask.
*  In this case the `$INSTANCE_NAME`_WDGT_CRC_CALC_VALUE and 
*  `$INSTANCE_NAME`_WDGT_CRC_ID_VALUE registers contain the CRC and ID of the first 
*  detected widget with the wrong CRC.
*
*  The `$INSTANCE_NAME`_SetParam() function is recommended for changing 
*  a `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT register. Then the CRC is updated automatically.
*  
*  The function updates the wdgtWorking register 
*  `$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE by clearing the widget-corresponding bit. 
*  Those non-working widgets are skipped by the high-level API.
*  Restoring a widget to its working state should be done by the application level.
*
* \param widgetId
*  Specify the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration
*  header file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*  
* \return
*  Returns a status of the test execution:
*  - CYRET_SUCCESS - if the stored CRC matches the calculated CRC
*  - `$INSTANCE_NAME`_TST_WDGT_CRC - if the widget CRC is wrong
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - if the input parameter is invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckWidgetCRC(uint32 widgetId)
{
    uint32 result = `$INSTANCE_NAME`_TST_WDGT_CRC;
    uint16 crc;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

    if (`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId)
    {
        /* Get a pointer to the RAM object data */
        ptrWdgt = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        crc = `$INSTANCE_NAME`_DsCalculateCrc16((uint8 *)ptrWdgt +
                                    `$INSTANCE_NAME`_WIDGET_CRC_AREA_START,
                                    `$INSTANCE_NAME`_WIDGET_CRC_AREA_SIZE);
        if ((ptrWdgt->crc) != crc)
        {
            /* Write to SelfTest DataStructure wdgtId of the first failed widget */
            if (0Lu == (`$INSTANCE_NAME`_dsRam.selfTest.testResultMask &
                       `$INSTANCE_NAME`_TST_WDGT_CRC))
            {
                `$INSTANCE_NAME`_dsRam.selfTest.wdgtCrcCalc = crc;
                `$INSTANCE_NAME`_dsRam.selfTest.wdgtCrcId = (uint8)widgetId;
                `$INSTANCE_NAME`_dsRam.selfTest.testResultMask |= `$INSTANCE_NAME`_TST_WDGT_CRC;
            }
            `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(widgetId)] &=
                                             ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(widgetId));
        }
        else
        {
            result = CYRET_SUCCESS;
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
*  The internal function that checks CRCs of all widget structures.
*
* \details
*  The function calculates CRCs of all widget structures and compare them
*  to the stored CRCs.
*  If a comparison fails, the function updates
*  testResultMask and returns a status.
*  The function uses `$INSTANCE_NAME`_CheckWidgetCRC.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS if all widgets' CRCs are OK;
*  - `$INSTANCE_NAME`_TST_WDGT_CRC if any widget's CRC is wrong.
*  - `$INSTANCE_NAME`_TST_NOT_EXECUTED if any widget is unavailable.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllWidgetCRC(void)
{
    uint32 result = CYRET_SUCCESS;
    uint32 wdgtIndex;

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
*   writes it to the data structure.
*
* \details
*  The maximum size of the RAM widget object is 192 bits. So, the best suitable
*  CRC polynomial is 0xAC9A. It has a hamming distance of 5 for data words up to 241 bits.
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
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWd;

    if (widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        /* Get a pointer to the RAM object data */
        ptrWd = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        ptrData = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        len = (uint32)`$INSTANCE_NAME`_WIDGET_CRC_AREA_SIZE;

        /* Skip CRC in the RAM object structure to calculate the CRC */
        ptrData += `$INSTANCE_NAME`_WIDGET_CRC_AREA_START;

        ptrWd->crc = `$INSTANCE_NAME`_DsCalculateCrc16(ptrData, len);
    }
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_CRC_GROUP_EN)

/*******************************************************************************
* Function Name: DsCalculateCrc16
****************************************************************************//**
*
* \brief
*   Calculates the CRC for the specified buffer and length. CRC Poly: 0xAC9A
*
* \details
*  This API is used for the CRC protection of the RAM widget object.
*  The maximum size of the RAM widget object is 192 bits. So, the best suitable
*  CRC polynomial is 0xAC9A. It has a hamming distance of 5 for data words up to 241 bits.
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
*  The function checks the baseline of the specified widget/sensor by comparing
*  the conformity of the baseline and its inversion.
*
*  Use this function to verify that a sensor baseline is not corrupted.
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
*  If fail is detected during a baseline update a CYRET_BAD_DATA result
*  is returned. The baseline initialization functions do not verify the
*  baseline and update the baseline inverse copy.
*
* \param widgetId
*  Specify the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specify the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns the status of the test execution:
*  - CYRET_SUCCESS - if the baseline matches its inverse copy
*  - `$INSTANCE_NAME`_TST_BSLN_DUPLICATION - if the test failed
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - if the input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckBaselineDuplication(uint32 widgetId, uint32 sensorId)
{
    uint32 result = CYRET_SUCCESS;
    uint32 channel;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = NULL;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) &&
        (`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].totalNumSns > sensorId))
    {
        ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        /* Find a pointer to the specified sensor object */
        ptrSensor = ptrWidget->ptr2SnsRam;
        ptrSensor = &ptrSensor[sensorId];
        /* Check te baseline inversion of each channel in the sensor */
        for(channel = 0u; channel < `$INSTANCE_NAME`_NUM_SCAN_FREQS; channel++)
        {
            if (ptrSensor->bsln[channel] != ((uint16) ~(ptrSensor->bslnInv[channel])))
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
*  This internal function checks baseline duplication of all sensors.
*
* \details
*  The function checks baseline duplication of all sensors by using
*  the `$INSTANCE_NAME`_CheckBaselineDuplication() function.
*
* \return
*  Returns a status of the test processing:
*    - CYRET_SUCCESS - If the test is successfully completed.
*    - `$INSTANCE_NAME`_TST_BSLN_DUPLICATION - If any sensor baseline duplication
       is wrong
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllBaselineDuplication(void)
{
    uint32 result = CYRET_SUCCESS;
    uint32 wdgtIndex;
    uint32 snsIndex;

    for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        for (snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_TOTAL_SENSORS; snsIndex++)
        {
            if (CYRET_SUCCESS != `$INSTANCE_NAME`_CheckBaselineDuplication(wdgtIndex, snsIndex))
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
*  This internal function updates the SefTest data structure and
*  widgetWorking register.
*
* \details
*  This function resets the corresponding bit in the widgetWorking register,
*  checks TestResultMask for the `$INSTANCE_NAME`_TST_BSLN_DUPLICATION
*  bit, sets it to 1 if it wasn't set to 1 before, and memorizes wdgtId and snsId
*  in the registers invBslnWdgtId and invBslnSnsId of the SefTest data structure.
*
* \param widgetId
*  Specifies the ID number of the widget to be processed.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget to be processed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateTestResultBaselineDuplication(uint32 widgetId, uint32 sensorId)
{
    `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(widgetId)] &=
                                     ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(widgetId));
    /* Write to SelfTest DataStructure wdgtId and snsId of the first sensor with a damaged baseline inversion */
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
*  The function checks the baseline and raw count with  limits defined by the user.
*  If the limits can be overpassed, the function sets the 
*  `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE bit in the 
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
*  Specify the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specify the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \param *ranges
*  Specify the pointer to the `$INSTANCE_NAME`_BSLN_RAW_RANGE_STRUCT structure
*  with valid ranges for the raw count and baseline.
*
* \return
*  Returns a status of the test execution:
*  - CYRET_SUCCESS - if the raw count and baseline are within the specified range
*  - `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE - if the test failed
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - if the input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckBaselineRawcountRange(uint32 widgetId, uint32 sensorId,`$INSTANCE_NAME`_BSLN_RAW_RANGE_STRUCT *ranges)
{
    uint32 result = CYRET_SUCCESS;
    uint32 channel;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *ptrSensor = NULL;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrWidget = NULL;


    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) &&
       ((`$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)) > sensorId))
    {
        ptrWidget = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];
        /* Find a pointer to the specified sensor object */
        ptrSensor = ptrWidget->ptr2SnsRam;
        ptrSensor = &ptrSensor[sensorId];

        #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Check the baseline and raw count of each channel in the sensor */
            for(channel = 0u;
                channel < `$INSTANCE_NAME`_NUM_SCAN_FREQS;
                channel++)
            {
        #else
            channel = 0u;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

                if ((ptrSensor->bsln[channel] > ranges->bslnHiLim) ||
                    (ptrSensor->bsln[channel] < ranges->bslnLoLim) ||
                    (ptrSensor->raw[channel]  > ranges->rawHiLim)  ||
                    (ptrSensor->raw[channel]  < ranges->rawLoLim))
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
*  The function performs verification if the specified sensor is shorted to
*  GND or VDD. The test does:
*  1. Sets all `$INSTANCE_NAME` sensors to the High-Z state
*  2. Changes the drive mode of the tested sensor to Pull-Down and verifies
*     if there is a logical 0
*  3. Changes the drive mode of the tested sensor to Pull-Up and verifies
*     if there is a logical 1
*  If a sensor consists of several electrodes that using the ganged option, all the
*  sensor electrodes are considered as one sensor and are tested together.
*
*  If the test detects a short:
*  1. The widget ID is stored to the `$INSTANCE_NAME`_SHORTED_WDGT_ID_VALUE register
*  2. The sensor ID is stored to the `$INSTANCE_NAME`_SHORTED_SNS_ID_VALUE register
*  3. The `$INSTANCE_NAME`_TST_SNS_SHORT bit is set in the
*     `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*
*  The function never clears the `$INSTANCE_NAME`_TST_SNS_SHORT bit.
*  If the `$INSTANCE_NAME`_TST_SNS_SHORT bit is set, the `$INSTANCE_NAME`_SHORTED_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_SHORTED_SNS_ID_VALUE registers are not updated.
*
*  It is possible to execute the test for all the widgets using
*  the `$INSTANCE_NAME`_RunSelfTest() function with the `$INSTANCE_NAME`_TST_SNS_SHORT mask.
*  In this case the `$INSTANCE_NAME`_SHORTED_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_SHORTED_SNS_ID_VALUE registers contain the widget and
*  sensor ID of the first detected fail.
*
*  The function updates the wdgtWorking register
*  `$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE by clearing the
*  widget-corresponding bit. Those non-working widgets are skipped by the high-level API.
*  Restoring a widget to its working state should be done by the application level.
*
* \param widgetId
*  Specify the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specify the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns a status of the test execution:
*  - CYRET_SUCCESS - if the sensor of the widget isn't shorted to VDD or GND
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - if the test failed
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - if the input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckSensorShort(uint32 widgetId, uint32 sensorId)
{
    uint32 result = CYRET_SUCCESS;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) && ((`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].totalNumSns) > sensorId))
    {
        /* Release HW resources previously captured by other mode and capture them for BIST */
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
        /* Switch the HW resource configuration to the sensor short test */
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
*  This internal function checks all sensors short to GND or VDD.
*
* \details
*  This function checks for shorts on Vdd/GND of all sensors (not
*  electrode) by using $INSTANCE_NAME`_ExecuteSnsShort. The function returns
*  a status and updates the testResultMask and  wdgtWorking register
*  in a case of any short detection.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS - If test passed successfully.
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - If any sensor of any widget is
*    shorted to Vdd or GND.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllSensorShort(void)
{
    uint32 wdgtIndex;
    uint32 snsIndex;
    uint32 result = CYRET_SUCCESS;
    uint32 resultWidget = CYRET_SUCCESS;

    /* HW resources previously captured by other mode were released in the RunSelfTest function */
    /* Switch the HW resource configuration to the sensor short test */
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E);
    /* Execute the test */
    for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        resultWidget = CYRET_SUCCESS;
        for (snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_dsFlash.wdgtArray[(wdgtIndex)].totalNumSns; snsIndex++)
        {
            resultWidget = `$INSTANCE_NAME`_ExecuteSnsShort(wdgtIndex, snsIndex);
            if (CYRET_SUCCESS != resultWidget)
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
*  This internal function updates the SefTest data structure and
*  widgetWorking register.
*
* \details
*  This function resets the corresponding bit in the widgetWorking register,
*  checks TestResultMask for the `$INSTANCE_NAME`_TST_SNS_SHORT bit, a
*  sets it to 1 if it was not set to 1 before, and memorizes wdgtId and snsId
*  in the corresponding registers of the SefTest data structure.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*******************************************************************************/
static void `$INSTANCE_NAME`_UpdateTestResultSnsShort(uint32 wdgtId, uint32 snsId)
{
    `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdgtId)] &=
                                     ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdgtId));
    if (0Lu == (`$INSTANCE_NAME`_dsRam.selfTest.testResultMask & `$INSTANCE_NAME`_TST_SNS_SHORT))
    {
        /* Write to SelfTest DataStructure wdgtId and snsId of the first shorted sensor */
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
*  This internal function checks one sensor for shorts on GND/VDD.
*
* \details
*  This function checks for shorts on GND/VDD of a certain sensor for CSD
*  widgets or of Rx and Tx electrodes of a certain sensor for CSX widgets.
*  The function uses `$INSTANCE_NAME`_ExecuteSnsShortExt.
*  If a short is detected, the function returns the Fail result.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS - If any sensor's electrode of the widget isn't shorted to VDD or GND.
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - If the sensor is shorted to VDD or GND.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSnsShort(uint32 wdgtId, uint32 snsId)
{
    uint32 ioSnsId;
    uint32 result = CYRET_SUCCESS;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
        /* For CSX widgets, get an index of an Rx electrode, for CSD widgets, an electrode index is the same as snsId */
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

    /* For CSX widgets, get an index of a Tx electrode and repeat the test */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        if (CYRET_SUCCESS == result)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
            {
                ioSnsId = (uint32)(snsId % `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows) +
                    (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numCols;
                result = `$INSTANCE_NAME`_ExecuteSnsShortExt(wdgtId, ioSnsId);
            }
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

    if (CYRET_SUCCESS != result)
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
*  This internal function checks one sensor for shorts on GND/VDD.
*
* \details
*  This function checks for shorts on GND/VDD of a certain sensor (electrode)
*  for CSD widgets or of an Rx or Tx electrode of a certain sensor for CSX widgets.
*  If a short is detected, the function returns the Fail result.
*  The function proceeds ganged sensors (electrodes).
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor (electrode) within the widget to be processed.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS - If the electrode of the widget isn't shorted to VDD or GND.
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - If a sensor or an Rx or Tx electrode
*    is shorted to VDD or GND.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSnsShortExt(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    uint32 result = CYRET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check the ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1u;
    }

    /* Loop through all electrodes of the specified sensor */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Set an electrode to the pull-up drive mode and check that the electrode state is a logical 1 */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr, `$INSTANCE_NAME`_TST_DR_PIN2VDD);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_PULLUP);
        if (0uL == `$INSTANCE_NAME`_ReadElectrodeState(ioPtr))
        {
            result = `$INSTANCE_NAME`_TST_SNS_SHORT;
        }
        /* Set an electrode to the pull-down drive mode and check that the electrode state is a logical 0 */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr, `$INSTANCE_NAME`_TST_DR_PIN2GND);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_PULLDOWN);
        if (0uL != `$INSTANCE_NAME`_ReadElectrodeState(ioPtr))
        {
            result = `$INSTANCE_NAME`_TST_SNS_SHORT;
        }
        /* Revert the electrode to the default drive mode */
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_HIGHZA);

        if (`$INSTANCE_NAME`_TST_SNS_SHORT == result)
        {
            break;
        }

        /* Get a next electrode */
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
*  The function performs verification if the specified sensor is shorted to
*  any other `$INSTANCE_NAME` sensors. The test does:
*  1. Sets all `$INSTANCE_NAME` sensors to the Strong drive mode with a logical 0
*  2. Changes the drive mode of the tested sensor to Pull-Up and verifies
*     if there is logical 1
   If a sensor consists of several electrodes using the ganged option, all the
*  sensor electrodes are considered as one sensor and are tested together.
*
*  If the test detects a short:
*  1. The widget ID is stored to the `$INSTANCE_NAME`_P2P_WDGT_ID_VALUE register
*  2. The sensor ID is stored to the `$INSTANCE_NAME`_P2P_SNS_ID_VALUE register
*  3. The `$INSTANCE_NAME`_TST_SNS2SNS_SHORT bit is set in the
*     `$INSTANCE_NAME`_TEST_RESULT_MASK_VALUE register.
*
*  The function never clears the `$INSTANCE_NAME`_TST_SNS2SNS_SHORT bit.
*  If the `$INSTANCE_NAME`_TST_SNS2SNS_SHORT bit is set, the `$INSTANCE_NAME`_P2P_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_P2P_SNS_ID_VALUE registers are not updated.
*
*  It is possible to execute the test for all widgets/sensors using
*  the `$INSTANCE_NAME`_RunSelfTest() function with the
*  `$INSTANCE_NAME`_TST_SNS2SNS_SHORT mask.
*  In this case, the `$INSTANCE_NAME`_P2P_WDGT_ID_VALUE and
*  `$INSTANCE_NAME`_P2P_SNS_ID_VALUE registers contain the widget and
*  sensor ID of the first detected fail.
*
*  The function updates the wdgtWorking register
*  `$INSTANCE_NAME`_WDGT_WORKING<Number>_VALUE by clearing the
*  widget-corresponding bit. Those non-working widgets are skipped by the high-level API.
*  Restoring a widget to its working state should be done by the application level.
*
* \param widgetId
*  Specify the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specify the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns a status of the test execution:
*  - CYRET_SUCCESS - if the sensor is not shorted to any other `$INSTANCE_NAME` sensor
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT - if the test failed
*  - `$INSTANCE_NAME`_TST_BAD_PARAM - if the input parameters are invalid.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_CheckSns2SnsShort(uint32 widgetId, uint32 sensorId)
{
    uint32 result = CYRET_SUCCESS;

    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) && ((`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].totalNumSns) > sensorId))
    {
        /* Release HW resources previously captured by other mode and capture them for BIST */
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
        /* Switch the HW resource configuration to sensor to te sensor short test */
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
*  This internal function checks for shorts between all of
*  `$INSTANCE_NAME` sensors.
*
* \details
*  This function checks for all sensor shorts between them by using
*  `$INSTANCE_NAME`_ExecuteSns2SnsShort.
*  The function returns a status and updates the testResultMask and
*  wdgtWorking registers if a short is detected.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS - If all the sensors of all widgets aren't shorted to
*    any other sensors.
*  - `$INSTANCE_NAME`_TST_SNS_SHORT - If any sensor of any widget is
*    shorted on any other sensor.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_CheckAllSns2SnsShort(void)
{
    uint32 wdgtIndex;
    uint32 snsIndex;
    uint32 result = CYRET_SUCCESS;
    uint32 resultWidget = CYRET_SUCCESS;

    /* HW resources previously captured by other mode were released in the RunSelfTest function */
    /* Switch the HW resource configuration to the sensor short test */
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E);

    /* Execute the test */
    for (wdgtIndex = 0uL; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        resultWidget = CYRET_SUCCESS;
        for (snsIndex = 0u; snsIndex < `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].totalNumSns; snsIndex++)
        {
            resultWidget = `$INSTANCE_NAME`_ExecuteSns2SnsShort(wdgtIndex, snsIndex);
            if (CYRET_SUCCESS != resultWidget)
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
*  This internal function updates the SelfTest data structure and
*  widgetWorking register.
*
* \details
*  This function resets the corresponding bit in the widgetWorking register,
*  checks TestResultMask for the `$INSTANCE_NAME`_TST_SNS2SNS_SHORT bit,
*  sets it to 1 if it wasn't set to 1 before, and memorizes wdgtId and snsId
*  in the corresponding registers of the SefTest data structure.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*******************************************************************************/
static void `$INSTANCE_NAME`_UpdateTestResultSns2SnsShort(uint32 wdgtId, uint32 snsId)
{
    `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdgtId)] &=
                                     ~(`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdgtId));
    /* Write to SelfTest DataStructure wdgtId and snsId of the first shorted sensor2sensor */
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
*  This internal function checks one sensor for shorts to another sensor.
*
* \details
*  This function checks for shorts to another sensor of a certain sensor
*  for CSD widgets or Rx and Tx electrodes of a certain sensor for CSX widgets.
*  The function uses `$INSTANCE_NAME`_ExecuteSnsShortExt.
*  If a short is detected, the function returns the Fail result.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS - If the electrode of the widget isn't shorted to another sensor.
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT - If the sensor is shorted to another sensor.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShort(uint32 wdgtId, uint32 snsId)
{
    uint32 ioSnsId;
    uint32 result = CYRET_SUCCESS;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
        /* For CSX widgets, get an Rx electrode index, for CSD widgets, an electrode index is the same as snsId */
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

    /* For CSX widgets, get a Tx electrode index and repeat the test */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        if (CYRET_SUCCESS == result)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
            {
                ioSnsId = (uint32)(snsId % `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numRows) +
                    (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].numCols;
                result = `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(wdgtId, ioSnsId);
            }
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

    if (CYRET_SUCCESS != result)
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
*  This internal function checks one sensor for shorts to another sensor.
*
* \details
*  This function checks for shorts to another sensor of a certain sensor(electrode)
*  for CSD widgets or of a Rx or Tx electrode of a certain sensor for CSX widgets.
*  If a short is detected, the function returns the Fail result.
*  The function proceeds ganged sensors(electrodes).
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param snsId
*  Specifies the ID number of the sensor within the widget to be processed.
*
* \return
*  Returns a status of the test processing:
*  - CYRET_SUCCESS - If the electrode of the widget isn't shorted to another sensor.
*  - `$INSTANCE_NAME`_TST_SNS2SNS_SHORT - If a sensor or Rx or Tx electrode
*    is shorted to another sensor.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ExecuteSns2SnsShortExt(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    uint32 result = CYRET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check the ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1uL;
    }

    /* Loop through all electrodes of the specified sensor and set the pull-up drive mode */
    for (eltdIndex = 0uL; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Set an electrode to the pull-up drive mode and check that the electrode state is a logical 1 */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_DR_PIN2VDD);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_PC_PULLUP);
    }
    /* Loop through all electrodes of specified sensor and check the state */
    for (eltdIndex = 0uL; eltdIndex < eltdNum; eltdIndex++)
    {
        if (0uL == `$INSTANCE_NAME`_ReadElectrodeState(ioPtr + eltdIndex))
        {
            result = `$INSTANCE_NAME`_TST_SNS2SNS_SHORT;
            break;
        }
    }

    /* Loop through all electrodes of the specified sensor and revert the drive mode to the default state */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Revert the electrode to the default drive mode */
        `$INSTANCE_NAME`_SetElectrodeDr(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_DR_PIN2GND);
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr + eltdIndex, `$INSTANCE_NAME`_TST_PC_STRONG);
    }

    return result;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SHORT_GROUP_EN)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadElectrodeState
****************************************************************************//**
*
* \brief
*  This internal function reads a certain electrode state.
*
* \details
*  This function activates an input buffer for the specified electrode and reads
*  the correspondent input bit. After that it disables the input buffer.
*
* \param *ioPtr
*  A pointer to the IO data structure of the specified electrode.
*
* \return
*  Returns a state of the input buffer of the electrode (0 or non 0).
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_ReadElectrodeState(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr)
{
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 result;

    /* Enable the input buffer for the specified electrode */
    interruptState = CyEnterCriticalSection();
    newRegisterValue = CY_GET_REG32(ioPtr->pc2Ptr);
    newRegisterValue &= ~(ioPtr->mask);
    CY_SET_REG32(ioPtr->pc2Ptr, newRegisterValue);
    CyExitCriticalSection(interruptState);

    /* Read the bit from the IO pad state register (PS) */
    result = CY_GET_REG32(ioPtr->psPtr) & ioPtr->mask;

    /* Disable the input buffer for this pin (set PC2 bit to logic 1) */
    interruptState = CyEnterCriticalSection();
    newRegisterValue = CY_GET_REG32(ioPtr->pc2Ptr);
    newRegisterValue |= ioPtr->mask;
    CY_SET_REG32(ioPtr->pc2Ptr, newRegisterValue);
    CyExitCriticalSection(interruptState);

    return result;
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
*  The function measures the capacitance, returns the measurement result
*  and stores it into the `$INSTANCE_NAME`_EXT_CAP<EXT_CAP_ID>_VALUE
*  register.
*
*  The `$INSTANCE_NAME` sensor state during measurement is High-Z Analog.
*
*  The measurement capacitance range is from 200pF to 60000pF.
*  The accuracy of the measurement is 10%.
*
*  It is possible to execute the test using the `$INSTANCE_NAME`_RunSelfTest()
*  function with the `$INSTANCE_NAME`_TST_EXTERNAL_CAP mask.
*
* \param extCapId
*  Specify the ID number of the external capacitor to be measured:
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
    uint32 result = CYRET_SUCCESS;

    if (`$INSTANCE_NAME`_TST_EXT_CAPS_NUM > extCapId)
    {
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
        `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E);
        `$INSTANCE_NAME`_BistConfigClock((uint32)`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION);
        /* Set a resolution to the fixed value */
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
*  This internal function measures capacitance of an external capacitor
*  when the HW IP block is configured for external capacitor measuring.
*
* \details
*  This function connects an external capacitor (Cmod, Csh, CintA/CintB)
*  to the CSD block, defines a modclock frequency divider and Idac code
*  and measures capacitance in the range from 0,5 to 5,0 nF.
*  If the result exceeds 75 % of the range high bound, the function divides modClk,
*  multiplies the Idac code to the fixed value to widen the measurement range and performs
*  another measuring cycle for capacitance in the range from 5,0 to 60,0 nF.
*  After that, the function disconnects the external capacitor, calculates a result
*  and stores it to teh correspondent register of the Selftest data structure.
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

    /* Connect an extCap  */
    `$INSTANCE_NAME`_BistConnectExtCapacitor(extCapId);
     /* Set modClk and Idac to the fixed value for a fine scan */
    if (CYDEV_BCLK__HFCLK__MHZ < `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ)
    {
        modClkDivider = 1uL;
    }
    else
    {
        modClkDivider = CYDEV_BCLK__HFCLK__MHZ / `$INSTANCE_NAME`_TST_EXT_CAP_MODCLK_MHZ;
    }
    iDacVal = (((`$INSTANCE_NAME`_TST_EXT_CAP_LOW_RANGE * `$INSTANCE_NAME`_CSD_VREF_MV * CYDEV_BCLK__HFCLK__MHZ) /
              `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN) / modClkDivider) + 1uL;
    `$INSTANCE_NAME`_GetExtCapCapacitanceExt(modClkDivider, iDacVal);

    /* For results more than 75 % of the resolution limit, perform a second wide range scan  */
    if (`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION_75 < `$INSTANCE_NAME`_bistRawcount)
    {
         /* Divide modClk and multiply Idac by 4 to get wider measurement range */
        modClkDivider <<= 2u;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
            iDacVal <<= 2u;
        #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
            iDacVal = `$INSTANCE_NAME`_BIST_MAX_IDAC_VALUE;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

        `$INSTANCE_NAME`_GetExtCapCapacitanceExt(modClkDivider, iDacVal);
    }
    /* Disconnect the external capacitor */
    `$INSTANCE_NAME`_BistDisconnectExtCapacitor(extCapId);
    /* Calculate a result in 2 steps to prevent an overflow */
    result = (iDacVal * modClkDivider * `$INSTANCE_NAME`_bistRawcount) / CYDEV_BCLK__HFCLK__MHZ;
    result = (result * `$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN) / `$INSTANCE_NAME`_CSD_VREF_MV;
    `$INSTANCE_NAME`_dsRam.selfTest.extCap[extCapId] = (uint16)result;

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetExtCapCapacitanceExt
****************************************************************************//**
*
* \brief
*  This internal function performs scanning for external capacitor measuring.
*
* \details
*  This function sets the modclock and Idac to defined values and performs scanning
*  for an external capacitor by using the CSD mode (Cmod, Csh, or CintA/CintB).
*
* \param modClkDivider
*  Specifies a divider for a modulation clock frequency.
*
* \param iDacVal
*  Specifies Idac modulation code.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_GetExtCapCapacitanceExt(uint32 modClkDivider, uint32 iDacVal)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        `$INSTANCE_NAME`_BistConfigClock(`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION * modClkDivider);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

    `$INSTANCE_NAME`_SsSetModClkClockDivider(modClkDivider);
    `$INSTANCE_NAME`_BistSetIdac(iDacVal);
    /* Start scanning  */
    `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;
    `$INSTANCE_NAME`_BistStartSample();
    /* Initialize the watchdog counter with a time interval enough to charge a 100 nF capacitor */
    `$INSTANCE_NAME`_WaitEndOfScan(`$INSTANCE_NAME`_EXT_CAP_WATCHDOG_CYCLES_NUM);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConnectExtCapacitor
****************************************************************************//**
*
* \brief
*  This internal function connects an external capacitor to the
*  `$INSTANCE_NAME` block.
*
* \details
*  This function connects an external capacitor to the $INSTANCE_NAME
*  block by using HSIOM in the CSD mode.
*
* \param extCapId
*  The index of an external cap to connect.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConnectExtCapacitor(uint32 extCapId)
{
    uint32 newRegValue;
    uint8  interruptState;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* Connect AMUXBUS-A to CSDCOMP(sense path) */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFMA_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    switch(`$INSTANCE_NAME`_extCapMap[extCapId])
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_TST_CMOD_MAP:
            {
                /* Connect the Cmod pin using HSIOM registers */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE << `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);
                break;
            }
                #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                    case `$INSTANCE_NAME`_TST_CSH_MAP:
                    {
                        /* Connect CTANK to AMUXBUS-A */
                        interruptState = CyEnterCriticalSection();
                        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
                        newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT);
                        CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, newRegValue);
                        CyExitCriticalSection(interruptState);
                        break;
                    }
                #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                      (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_TST_CINTA_MAP:
            {
                /* Connect the CintA pin using HSIOM registers */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
                newRegValue &= ~`$INSTANCE_NAME`_CintA_HSIOM_MASK;
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE << `$INSTANCE_NAME`_CintA_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);
                break;
            }
            case `$INSTANCE_NAME`_TST_CINTB_MAP:
            {
                /* Connect CintB to AMUXBUS-A using HSIOM registers */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
                newRegValue &= ~`$INSTANCE_NAME`_CintB_HSIOM_MASK;
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE << `$INSTANCE_NAME`_CintB_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);
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
*  This internal function disconnects an external capacitor from the
*  $INSTANCE_NAME block.
*
* \details
*  This function disconnects an external capacitor from the
*  $INSTANCE_NAME block.
*  After that the function discharges the specified capacitor to GND to provide
*  next regular scans.
*
* \param extCapId
*  The index of an external cap to disconnect.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistDisconnectExtCapacitor(uint32 extCapId)
{
    uint32 newRegValue;
    uint8  interruptState;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* Disconnect AMUXBUS-A from CSDCOMP(sense path) */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFMA_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, newRegValue);
        CyExitCriticalSection(interruptState);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    switch(`$INSTANCE_NAME`_extCapMap[extCapId])
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_TST_CMOD_MAP:
            {
                /* Disconnect Cmod from AMUXBUS-A using HSIOM registers */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
                CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                    /* Disconnect CSDCMP from CSDBUS-A (parallel pass via SFCA switch) */
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR);
                    newRegValue &= (uint32) (~`$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFCA_MASK);
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, newRegValue);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

                /* Discharge CMOD by using GPIO mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_GPIO << `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set an output port register for Cmod to 0 to connect Cmod to GND */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_DR_PTR);
                newRegValue &= (uint32)(~(uint32) (1uL << `$INSTANCE_NAME`_CMOD_DR_SHIFT));
                CY_SET_REG32(`$INSTANCE_NAME`_CMOD_DR_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set port configuration register (drive mode) for Cmod in STRONG mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_PC_PTR);
                newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_CMOD_PC_SHIFT));
                newRegValue |= (`$INSTANCE_NAME`_GPIO_STRGDRV << `$INSTANCE_NAME`_CMOD_PC_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CMOD_PC_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Delay 10 uS to discharge Cmod */
                CyDelayUs(10u);

                /* Set a port configuration register (drive mode) for Cmod in the HIGHZ-A mode (PC=000) */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_PC_PTR);
                newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_CMOD_PC_SHIFT));
                CY_SET_REG32(`$INSTANCE_NAME`_CMOD_PC_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                break;
            }

            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                case `$INSTANCE_NAME`_TST_CSH_MAP:
                {
                    /* Disconnect CTANK to AMUXBUS-A */
                    interruptState = CyEnterCriticalSection();
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                    newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
                    CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, newRegValue);
                    CyExitCriticalSection(interruptState);

                    /* Discharge CSH by using the GPIO mode */
                    interruptState = CyEnterCriticalSection();
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                    newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
                    newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_GPIO << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT);
                    CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, newRegValue);
                    CyExitCriticalSection(interruptState);

                    /* Set an output port register for CSH to 0 to connect CSH to GND */
                    interruptState = CyEnterCriticalSection();
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_DR_PTR);
                    newRegValue &= (uint32)(~(uint32) (1uL << `$INSTANCE_NAME`_CSH_SHIFT));
                    CY_SET_REG32(`$INSTANCE_NAME`_CSH_DR_PTR, newRegValue);
                    CyExitCriticalSection(interruptState);

                    /* Set a port configuration register (drive mode) for CSH in the Strong mode */
                    interruptState = CyEnterCriticalSection();
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR);
                    newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_CSH_PC_SHIFT));
                    newRegValue |= (`$INSTANCE_NAME`_GPIO_STRGDRV << `$INSTANCE_NAME`_CSH_PC_SHIFT);
                    CY_SET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR, newRegValue);
                    CyExitCriticalSection(interruptState);

                    /* Delay 10 uS to discharge CSH */
                    CyDelayUs(10u);

                    /* Set a port configuration register (drive mode) for CSH in the HIGHZ-A mode (PC=000) */
                    interruptState = CyEnterCriticalSection();
                    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR);
                    newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_CSH_PC_SHIFT));
                    CY_SET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR, newRegValue);
                    CyExitCriticalSection(interruptState);

                    break;
                }
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_TST_CINTA_MAP:
            {
                /*  Disconnect CintA from AMUXBUS-A using HSIOM registers.   */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintA_HSIOM_MASK);
                CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Discharge CintA by using the GPIO mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintA_HSIOM_MASK);
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_GPIO << `$INSTANCE_NAME`_CintA_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set an output port register for CintA to 0 to connect CintA to GND */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_DR_PTR);
                newRegValue &= (uint32)(~(uint32) (1uL << `$INSTANCE_NAME`_CintA_SHIFT));
                CY_SET_REG32(`$INSTANCE_NAME`_CintA_DR_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set a port configuration register (drive mode) for CintA in the Strong mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_PC_PTR);
                newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << (`$INSTANCE_NAME`_CintA_SHIFT * 3uL)));
                newRegValue |= (`$INSTANCE_NAME`_GPIO_STRGDRV << (`$INSTANCE_NAME`_CintA_SHIFT * 3uL));
                CY_SET_REG32(`$INSTANCE_NAME`_CintA_PC_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Delay 10 uS to discharge CintA */
                CyDelayUs(10u);

                /* Set a port configuration register (drive mode) for CintA in the HIGHZ-A mode (PC=000) */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_PC_PTR);
                newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << (`$INSTANCE_NAME`_CintA_SHIFT * 3uL)));
                CY_SET_REG32(`$INSTANCE_NAME`_CintA_PC_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                break;
            }
            case `$INSTANCE_NAME`_TST_CINTB_MAP:
            {
                /* Discharge CintB by using the GPIO mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintB_HSIOM_MASK);
                CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set a CintB HSIOM register to the GPIO mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintB_HSIOM_MASK);
                newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_GPIO << `$INSTANCE_NAME`_CintB_HSIOM_SHIFT);
                CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set an output port register for CintB to 0 to connect CintB to GND */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_DR_PTR);
                newRegValue &= (uint32)(~(uint32) (1uL << `$INSTANCE_NAME`_CintB_SHIFT));
                CY_SET_REG32(`$INSTANCE_NAME`_CintB_DR_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Set a port configuration register (drive mode) for CintB in the Strong mode */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_PC_PTR);
                newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << (`$INSTANCE_NAME`_CintB_SHIFT * 3uL)));
                newRegValue |= (`$INSTANCE_NAME`_GPIO_STRGDRV << (`$INSTANCE_NAME`_CintB_SHIFT * 3uL));
                CY_SET_REG32(`$INSTANCE_NAME`_CintB_PC_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

                /* Delay 10 uS to discharge CintB */
                CyDelayUs(10u);

                /* Set a port configuration register (drive mode) for CintB in the HIGHZ-A mode (PC=000) */
                interruptState = CyEnterCriticalSection();
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_PC_PTR);
                newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_GPIO_PC_MASK << (`$INSTANCE_NAME`_CintB_SHIFT * 3uL)));
                CY_SET_REG32(`$INSTANCE_NAME`_CintB_PC_PTR, newRegValue);
                CyExitCriticalSection(interruptState);

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
*  This internal function measures capacitance of all external
*  capacitors.
*
* \details
*  This function measures capacitances of all external  capacitors (Cmod,
*  Csh, CintA, CintB).
*  The function stores cap values in the corresponding registers.
*  The function does not affect another Component parameters or
*  functionalities.
*
* \return
*  Returns a status of the measuring process:
*  - CYRET_SUCCESS - If all measurements were successful.
*  - `$INSTANCE_NAME`_TST_EXTERNAL_CAP - If any measuring failed.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_MeasureAllExtCapCapacitance(void)
{
    uint32 extCapIndex;

    `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_BIST_E);
    `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E);
    `$INSTANCE_NAME`_BistConfigClock(`$INSTANCE_NAME`_TST_EXT_CAP_RESOLUTION);
    /* Set a resolution to a fixed value) */
    `$INSTANCE_NAME`_BistSetScanDuration();

    for (extCapIndex = 0u; extCapIndex < `$INSTANCE_NAME`_TST_EXT_CAPS_NUM; extCapIndex++)
    {
        (void)`$INSTANCE_NAME`_MeasureExtCapCapacitance(extCapIndex);
    }

    return (CYRET_SUCCESS);
}
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN)   */

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
*  Initializes the HW resources to the Built-in Self-test mode.
*
* \details
*  Preserves the function to be consistent with other modes (CSX or CSD).
*  In reality, resource capturing and initialization are performed later than
*  it is defined which test type should be executed. Depending on the test type, the HW
*  resources are initialized differently. Only disconnection of all IOs from AMUX
*  is common for all test types.
*
*******************************************************************************/
void `$INSTANCE_NAME`_BistInitialize(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
            (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
            /* Disconnect all the IOs from analog mux buses */
            `$INSTANCE_NAME`_SetAllIOHsiomState(`$INSTANCE_NAME`_TST_HSIOM_GPIO);
        #endif
        /* Set the data register to GND which is applicable to all the tests */
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
*  Connects the shield to the CapSense block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the SHIELD_IO_STRUCT object. Basing on this data, it updates
*   the HSIOM and PC registers.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConnectShieldAsSensor(void)
{
    uint8 interruptState;
    uint32 regValue;
    uint32 eltdIndex;
    `$INSTANCE_NAME`_SHIELD_IO_STRUCT const *ioPtr;

    /* Loop through all electrodes of the Shield */
    for (eltdIndex = 0u; eltdIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; eltdIndex++)
    {
        ioPtr = &`$INSTANCE_NAME`_shieldIoList[eltdIndex];

        /* Set an electrode to High-Z Analog */
        interruptState = CyEnterCriticalSection();
        regValue = CY_GET_REG32(ioPtr->pcPtr);
        regValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << ioPtr->shift);
        CY_SET_REG32(ioPtr->pcPtr, regValue);
        CyExitCriticalSection(interruptState);

        /* Update the HSIOM port select register */
        interruptState = CyEnterCriticalSection();
        regValue = CY_GET_REG32(ioPtr->hsiomPtr);
        regValue &= ~(ioPtr->hsiomMask);
        regValue |= (`$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE << ioPtr->hsiomShift);
        CY_SET_REG32(ioPtr->hsiomPtr, regValue);
        CyExitCriticalSection(interruptState);
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
*  This internal function initializes the shield electrodes.
*
* \details
*  The function sets the bit in the HSIOM register which enables the shield electrode
*  functionality on the pin. The port and pin configurations are stored in
*  the `$INSTANCE_NAME`_shieldIoList structure.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableShieldElectrodes(void)
{
    uint32 newRegValue;
    uint32 shieldIndex;

    for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
    {
        /* Set the drive mode to analog */
        CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr, CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr) &
                   ~(`$INSTANCE_NAME`_GPIO_PC_MASK <<(`$INSTANCE_NAME`_shieldIoList[shieldIndex].shift)));

        /* Set the HSIOM register mode to the CSD_SHIELD or AMUXBUS B connection */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr);
        newRegValue &= ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << (`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomShift));

        /* Set the HSIOM register mode to CSD_SHIELD */
        newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD << (`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomShift));

        CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr, newRegValue);
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
*   This function configures the Csh pin
*
* \details
*   The function updates the CSH_HSIOM register to connect Csh to AMUXBUS-B.
*   For the CSD v1 IP HW block, it additionally sets the Strong drive mode for Csh
*   and applies High level to the Csh pin when pre-charge is set to the IO buffer.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableShieldTank(void)
{
    uint32 newRegValue;

    /* Update the CSH_HSIOM register to connect Csh to AMUXBUS-B */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
    newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
    newRegValue |= (`$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT);
    CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, newRegValue);

    #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
         (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2))
        /* Set the Strong drive mode for Csh */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR);
        newRegValue &= (uint32)(~(`$INSTANCE_NAME`_CSH_PC_MASK << `$INSTANCE_NAME`_CSH_PC_SHIFT));
        newRegValue |= (`$INSTANCE_NAME`_CSH_PC_STRONG_MODE << `$INSTANCE_NAME`_CSH_PC_SHIFT);
        CY_SET_REG32(`$INSTANCE_NAME`_CSH_PC_PTR, newRegValue);

        /* Apply High level to the Csh pin for Csh */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_DR_PTR);
        newRegValue &= (uint32)(~(`$INSTANCE_NAME`_DR_MASK << `$INSTANCE_NAME`_CSH_SHIFT));
        newRegValue |= (uint32)`$INSTANCE_NAME`_CSH_DR_CONFIG;
        CY_SET_REG32(`$INSTANCE_NAME`_CSH_DR_PTR, newRegValue);
    #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
               (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)) */
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

/** \cond SECTION_C_LOW_LEVEL */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetSensorCapacitance
****************************************************************************//**
*
* \brief
*  Measures the specified widget/sensor capacitance.
*
* \details
*  The function measures the specified widget/sensor, returns the measurement result,
*  and stores it into the data structure.
*
*  For CSX sensors, the measurement is performed twice: for RX and for TX electrodes.
*
*  If a sensor consists of several electrodes using the ganged option, all the
*  sensor electrodes are considered as one sensor and are tested together.
*
*  Component configuration does not influence measurement. It is done with the following
*  parameter settings:
*  - Modulator clock frequency - as high as possible
*  - Sense clock source - Direct
*  - IDAC sensing configuration - IDAC sourcing
*  - Compensation IDAC - Disabled
*  - Resolution - 10 bits
*
*  The measurement consists of several scans to find an optimal IDAC value and sense
*  clock frequency. Then, the sensor capacitance is calculated based on the found
*  values and received raw counts.
*
*  All non-measured sensor states are inherited from the Component configuration.
*  - While measuring a CSX sensor, all non-measured sensors and shield electrodes
*  (if enabled) are set to the Strong drive mode.
*  - While measuring CSD sensor, all CSX sensors are set to the Strong drive mode and all
*  CSD sensors are set to the state defined by the inactive sensor connection parameter.
*  If the shield electrode parameter is enabled, it is also enabled at a CSD sensor
*  capacitance measurement.
*
*  The measurement sensor capacitance range is from 5pF to 255pF. If a returned value
*  is 255, the sensor capacitance can be higher.
*
*  It is possible to execute the test for all widgets/sensors using the `$INSTANCE_NAME`_RunSelfTest()
*  function with the `$INSTANCE_NAME`_TST_SNS_CAP mask.
*
*  The measured capacitance is stored in the `$INSTANCE_NAME`_RAM_SNS_CP_STRUCT structure.
*  The `$INSTANCE_NAME`_<WidgetName>_PTR2SNS_CP_VALUE register contains a pointer to
*  the array of the specified widget with the sensor capacitance.
*
* \param widgetId
*  Specify the ID number of the widget to be processed.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specify the ID number of the sensor within the widget.
*  A macro for the sensor ID within the specified widget can be found in
*  the `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns a result of the test execution:
*  - Bits [7..0] the capacitance (in pF) of the CSD sensor or the capacitance
*    of RX electrode if the specified sensor type is CSX
*  - Bits [15..8] the capacitance (in pF) of TX electrode if the specified
*    sensor type is CSX
*  - Bit [30] `$INSTANCE_NAME`_TST_BAD_PARAM if the input parameters are invalid.
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

        if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
        {
            `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E);
        }
        else
        {
            `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E);
        }

        /* For the CSX widgets, get an Rx electrode index, for CSD widgets, an electrode index is the same as snsId */
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

        /* For the CSX widgets, get a Tx electrode index and repeat the test */
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
*  This internal function measures certain sensor
*  (electrode for CSX widgets) capacitance.
*
* \details
*  The function connects a certain sensor (electrode for CSX widgets)
*  to the previously configured `$INSTANCE_NAME` HW block by using the CSD mode.
*  Then measures Cp by using the `$INSTANCE_NAME`_GetCapacitanceExt function.
*  After measuring, the function sets an inactive connection of the sensor
*  (electrode for CSX widgets) and stores the Cp value in the corresponding
*  register of the `$INSTANCE_NAME`_RAM_SNS_STRUCT.
*
* \param wdgtId
*  Specifies the ID number of the widget to be processed.
*
* \param ioSnsId
*  Specifies the ID number of the sensor within the widget
*  whose capacitance will be measured.
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

    /* Save cp to the data structure */
    *cpPtr = (uint8)result;

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConnectSensor
****************************************************************************//**
*
* \brief
*  Connects a sensor (including ganged) port-pin to the CapSense block via the AMUX bus.
*
* \details
*   The function gets the IO configuration registers addresses, their shifts and
*   masks from the FLASH_IO_STRUCT object. Basing on this data, it updates the HSIOM and
*   PC registers.
*
* \param
*   wdgtIndex Specifies the ID of the widget.
*   ioSnsId Specifies the ID of the sensor in the widget.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConnectSensor(uint32 wdgtId, uint32 ioSnsId)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;

    /* Check the ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1u;
    }

    /* Loop through all electrodes of the specified sensor */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Set an electrode to the CSD_SENSE mode to be scanned */
        `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_HIGHZA);
        `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
        ioPtr++;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MeasureAllSensorCapacitance
****************************************************************************//**
*
* \brief
*  The internal function that measures all sensors Cp capacitance.
*
* \details
*  The function that measures Cp of all sensors by using the
*  `$INSTANCE_NAME`_GetSensorCapacitance function.
*  The function stores the Cp values in the corresponding BIST data
*  structure registers.
*
* \return
*  Returns a status of the measuring process:
*  - CYRET_SUCCESS.
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_MeasureAllSensorCapacitance(void)
{
    uint32 wdgtId;
    uint32 ioSnsId;
    uint32 totalNumIoSns;
    uint32 result = CYRET_SUCCESS;

    /* Loop through all widgets */
    for (wdgtId = 0u; wdgtId < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtId++)
    {
        /* Switch the HW resource configuration depending on the widget type */
        if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId]))
        {
            `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E);
        }
        else
        {
            `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E);
        }

        /* Get a total number of the widget elements: for CSX, it is numRows + numCols, for CSD, it is totalNumSns */
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
*  The function measures the shield capacitance, returns the measurement result,
*  and stores it into the `$INSTANCE_NAME`_SHIELD_CAP_VALUE register.
*
*  If the shield consists of several electrodes, all the electrodes are
*  joined together.
*
*  The sensor state is inherited from the Component configuration.
*  - All CSX sensors are set to the Strong drive mode.
*  - All CSD sensors are set to the state defined by inactive sensor connection
*    parameter.
*
*  If the inactive sensor connection parameter is set to the shield, all CSD sensors
*  are connected to the shield and are measured together with the shield.
*
*  Component configuration does not influence a measurement. It is always done with the following
*  parameter settings:
*  - Modulator clock frequency - as high as possible
*  - Sense clock source - Direct
*  - IDAC sensing configuration - IDAC sourcing
*  - Compensation IDAC - disabled
*  - Resolution - 10 bits
*
*  The measurement consists of several scans to find an optimal IDAC value and sense
*  clock frequency. Then the shield capacitance is calculated based on the found
*  values and received raw counts.
*
*  The measurement shield capacitance range is from 5pF to 500pF.
*
*  It is possible to execute the test using the `$INSTANCE_NAME`_RunSelfTest()
*  function with the `$INSTANCE_NAME`_TST_SH_CAP mask.
*
* \return
*  The shield electorde capacitance (in pF)
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

    `$INSTANCE_NAME`_BistDisableShieldElectrodes();

    if (`$INSTANCE_NAME`_BIST_SH_CAP_MAX_CP < result)
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
*  This internal function measures a capacitance attached to AMUXBUS.
*
* \details
*  The function measures Cp of a certain sensor or shield by using the
*  CSD mode and defined Idac mode, sense clock frequency and resolution.
*  The range for sensor measuring is from 5 to 250 pF, for a shield - from 5 to 500 pf.
*  The function calibrates the Idac to reach a defined target of raw counts.
*  If a reached Idac is lower than a certain value, the function sets
*  a higher sense clock frequency.
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
    uint32 idacMask = (uint32)(`$INSTANCE_NAME`_CAL_MIDDLE_BIT << 1uL);

    if (`$INSTANCE_NAME`_BIST_HW_SH_CAP_E == `$INSTANCE_NAME`_bistHwConfig)
    {
        /* Set the SnsClk frequency for a shield measurement up to 500pF */
        snsClkIncrementIndex = 0uL;
    }
    else
    {
        /* Set the SnsClk frequency for a sensor measurement up to 250pF */
        snsClkIncrementIndex = 1uL;
    }

    /* Initialize a raw count for the first cycle pass */
    `$INSTANCE_NAME`_bistRawcount = 0u;

    `$INSTANCE_NAME`_BistSetScanDuration();

    /* Finding an optimal IDAC and frequency */
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

        /* Revert the back Idac value and increase the SnsClk frequency if Idac is too small */
        if (idacValue < `$INSTANCE_NAME`_BIST_MIN_IDAC_VALUE)
        {
            if ((`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER >> (snsClkIncrementIndex + 1uL)) >= `$INSTANCE_NAME`_TST_MIN_SNS_CLK_DIVIDER)
            {
                snsClkIncrementIndex++;
                idacValue &= (uint32)(~idacMask);
                idacMask <<= 1uL;
                idacValue |= idacMask;
            }
        }

        /*
        * Set up the scan parameters:
        * - IDAC
        * - SnsClk
        * - Resolution (conversion number for CSDv2)
        */
        `$INSTANCE_NAME`_BistSetIdac(idacValue);
        `$INSTANCE_NAME`_BistConfigClock((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER >> snsClkIncrementIndex);
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
            CY_SET_REG32(`$INSTANCE_NAME`_SEQ_NORM_CNT_PTR, ((uint32)`$INSTANCE_NAME`_BIST_10_BIT_MASK /
                                            ((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER >> snsClkIncrementIndex)) &
                                            `$INSTANCE_NAME`_SEQ_NORM_CNT_CONV_CNT_MASK);
        #endif

        /* Perform scanning */
        `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;
        `$INSTANCE_NAME`_BistStartSample();
        `$INSTANCE_NAME`_WaitEndOfScan(`$INSTANCE_NAME`_CALIBR_WATCHDOG_CYCLES_NUM);
    }

    /*
    * Capacitance calculation:
    *   cp(pF) = Rawcount * IdacCode * IdacGain(nA) * 1000 / (MaxRaw * SnsClk(kHz) * Vref(mV))
    * Details:
    *   - The order of calculation is changed to avoid a possible overflow
    *   - The half of the last divider is added to implement the value rounding
    */
    cp = (`$INSTANCE_NAME`_TST_SNS_CAP_IDAC_GAIN * `$INSTANCE_NAME`_BIST_SNS_CAP_UNIT_SCALE) / `$INSTANCE_NAME`_CSD_VREF_MV;
    cp = (cp * idacValue) / `$INSTANCE_NAME`_BIST_10_BIT_MASK;
    cp = cp * (uint32)`$INSTANCE_NAME`_bistRawcount;
    cp = (cp + (((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_KHZ << snsClkIncrementIndex) >> 1uL)) /
                ((uint32)`$INSTANCE_NAME`_TST_BASE_SNS_CLK_KHZ << snsClkIncrementIndex);

    return cp;
}
#endif /* #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)) */
/** \endcond */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistDisableHwSnsCap
****************************************************************************//**
*
* \brief
*  This function disables the CSD mode.
*
* \details
*  To disable the CSD mode:
*  1. Disconnect Cmod from AMUXBUS-A.
*  2. Disconnect a previous CSX electrode (if it has been connected).
*  3. Disconnect Csh from AMUXBUS-B.
*  4. Disable Shield Electrodes.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistDisableHwSnsCap(void)
{
    uint32 regValue;
    uint8  interruptState;

    /* Disconnect Cmod from AMUXBUS-A using HSIOM registers */
    interruptState = CyEnterCriticalSection();
    regValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
    regValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
    CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, regValue);
    CyExitCriticalSection(interruptState);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
        /* Verification of the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Disconnect Csh from AMUXBUS-B */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                interruptState = CyEnterCriticalSection();
                regValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                regValue &= (uint32)(~(uint32)(`$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT));
                CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, regValue);
                CyExitCriticalSection(interruptState);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

            /* Disconnect the shield electrodes */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
                `$INSTANCE_NAME`_BistDisableShieldElectrodes();
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */

            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
                /*
                * Disconnect all IOs from AMUXBUS_B because all the rest of the tests suppose that the electrodes are not
                * connected to any bus. To optimize performance:
                * do not write a HSIOM register at every test type switching.
                */
                `$INSTANCE_NAME`_SetAllIOHsiomState(`$INSTANCE_NAME`_TST_HSIOM_GPIO);
            #endif
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
}

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
*   The function goes through all the sensors of CSD widgets and updates the appropriate bits in
*   the IO HSIOM, P,C and DR registers depending on the Inactive sensor connection
*   parameter. The DR register bits are set to a zero when the Inactive sensor
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
            /* Go through all sensors in the widget */
            for (snsId = 0uL; snsId < (uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].totalNumSns; snsId++)
            {
                `$INSTANCE_NAME`_BistSetInactiveSensorConnection(wdgtId, snsId);
            }
        }
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSetInactiveSensorConnection
****************************************************************************//**
*
* \brief
*  Sets an inactive state for a certain sensor (electrode).
*
* \details
*  The function updates the appropriate bits in the IO HSIOM and PC registers
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

    /* Check the ganged sns flag */
    if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
    {
        curFlashSnsPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash;
        curFlashSnsPtr += ioSnsId;
        ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
        eltdNum = curFlashSnsPtr->numPins;
    }
    else
    {
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtId].ptr2SnsFlash + ioSnsId;
        eltdNum = 1uL;
    }

    /* Loop through all electrodes of the specified sensor */
    for (eltdIndex = 0uL; eltdIndex < eltdNum; eltdIndex++)
    {
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
                /* Update the port configuration register (drive mode to HiZ Analog) for the sensor */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_HIGHZA);
                /* Connect to the shield */
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_CSD_SHIELD);
            #else
                /* Update the HSIOM register to disconnect the sensor */
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
                /* Set the drive mode for the electrode based on the inactive sensor connection parameter */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION);
            #endif /* (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD != `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION) */
        }
        else if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSX_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Update the HSIOM register to disconnect the sensor */
            `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
            /* Update port configuration register (drive mode to HiZ Analog) for sensor */
            `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_STRONG);
        }
        else if (`$INSTANCE_NAME`_BIST_HW_SH_CAP_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)
                /* Set an electrode to the CSD_SENSE mode to be scanned */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_TST_PC_HIGHZA);
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_CSD_SENSE);
            #else
                /* Update the HSIOM register to disconnect the sensor */
                `$INSTANCE_NAME`_SetElectrodeHsiom(ioPtr, `$INSTANCE_NAME`_TST_HSIOM_GPIO);
                /* Set the drive mode for electrode based on the inactive sensor connection parameter */
                `$INSTANCE_NAME`_SetElectrodePc(ioPtr, `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION);
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
*   This internal function disables shield electrodes.
*
* \details
*   The function resets the bit in the HSIOM register which disables the shield
*   electrode functionality on the pin. The port and pin configurations are
*   stored in  the `$INSTANCE_NAME`_shieldIoList structure.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistDisableShieldElectrodes(void)
{
    uint32 newRegValue;
    uint32 shieldIndex;

    for (shieldIndex = 0u; shieldIndex < `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT; shieldIndex++)
    {
        /* Reset the HSIOM register (to GPIO state) */
        CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr, CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomPtr) &
                     (uint32)~(uint32)(`$INSTANCE_NAME`_HSIOM_SEL_MASK << `$INSTANCE_NAME`_shieldIoList[shieldIndex].hsiomShift));

        /* Update the port configuration register (drive mode to ground)  */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr);
        newRegValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << `$INSTANCE_NAME`_shieldIoList[shieldIndex].shift);
        newRegValue |= (`$INSTANCE_NAME`_SNS_GROUND_CONNECT << `$INSTANCE_NAME`_shieldIoList[shieldIndex].shift);
        CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].pcPtr, newRegValue);

        /* Set a logic 0 to the port data register */
        CY_SET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].drPtr, CY_GET_REG32(`$INSTANCE_NAME`_shieldIoList[shieldIndex].drPtr) &
                   (uint32)~(uint32)((uint32)1u << `$INSTANCE_NAME`_shieldIoList[shieldIndex].drShift));
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
*  This is an internal ISR function for single-sensor scanning implementation.
*
* \details
*  This ISR handler is triggered when the CSD scan for a capacitance measuring
*  is completed.
*
*  The following tasks are performed:
*    1. Disable the CSD interrupt.
*    2. Read the Counter register and update the `$INSTANCE_NAME`_bistRawcount with raw data.
*    3. Reset the BUSY flag.
*    4. Connect the Vref buffer to the AMUX bus (for CSDv1 HW IP block).
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_BistPostSingleScan)
{
    /* Clear a pending interrupt */
    CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
    /* Read the raw count */
    `$INSTANCE_NAME`_bistRawcount = (uint16)CY_GET_REG32(`$INSTANCE_NAME`_COUNTER_PTR);
    /* The sensor is totally scanned. Reset the BUSY flag */
    `$INSTANCE_NAME`_dsRam.status &= ~(`$INSTANCE_NAME`_SW_STS_BUSY | `$INSTANCE_NAME`_WDGT_SW_STS_BUSY);
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
             (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV))
            /*  Disconnect Vrefhi from the AMUBUF positive input. Disconnect the AMUBUF output from CSDBUSB with sych PHI2+HSCMP  */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_DEFAULT);
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                   (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV)) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Open the HCBV and HCBG switches */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN |
                                                             `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            /*  Disable the CSDv2 block */
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
    #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            /*  Disable the CSDv1 block. Connect the Vref buffer to AMUX bus */
            #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG);
            #endif /* ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */
        #else
            /*  Connect the Vref buffer to AMUX bus. The CSDv1 block is enabled */
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG_CSD_EN);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistClockRestart
****************************************************************************//**
*
* \brief
*  This function restarts the clocks.
*
* \details
*  The function performs the following:
*  1) Stops, sets dividers and starts ModClk clock.
*  2) Stops and starts the SnsClk clock.
*  3) Scans one cycle to reset the flip-flop for the Direct clock mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistClockRestart(void)
{
    /*  Stop clocks, set dividers, and start the clock to align the clock phase */
    `$INSTANCE_NAME`_SsSetModClkClockDivider(`$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER);
    
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        /*  Stop the sense clock   */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     ((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID <<
                     `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT)|
                     ((uint32)`$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_MASK));

        /*  Check whether the previous sense clock start command has completed */
        while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) & `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK))
        {
            /*  Wait until the previous sense clock start command has completed */
        }

        /* Start the sense clock aligned to a previously started modulator clock */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     (uint32)(((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT) |
                      ((uint32)`$INSTANCE_NAME`_ModClk__PA_DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_PA_DIV_SHIFT) |
                      `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK));
    #else
        /* Clear the bit to disable the SnsClk clock */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) &
                     (uint32)(~(uint32)`$INSTANCE_NAME`_SnsClk__ENABLE_MASK));

        /* Set a bit to enable the SnsClk clock */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) |
                    `$INSTANCE_NAME`_SnsClk__ENABLE_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */

    /*  Scan one cycle to reset the flip-flop for the Direct clock mode */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
    CY_SET_REG32(`$INSTANCE_NAME`_COUNTER_PTR, `$INSTANCE_NAME`_ONE_CYCLE);

    while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_COUNTER_PTR) & `$INSTANCE_NAME`_RESOLUTION_16_BITS))
    {
        /* Wait until scanning is complete */
    }
    CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_MASK);
    CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);
}
#endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistStartSample
****************************************************************************//**
*
* \brief
*   Starts the CSD conversion for capacitance measuring.
*
* \details
*   This function assumes that the CSD block is already set up using
*   the `$INSTANCE_NAME`_BistEnableHwSnsCap function and the capacitance
*   is connected to the CSD block.
*   The function performs the following tasks:
*   1. Disables the CSD interrupt.
*   2. Enables CSD block if it was disabled.
*   3. Restarts the clock (only for the CSDv1 and only for sensor capacitance measuring).
*   3. Pre charges Cmod (only for a sensor capacitance measuring or for the CSDv1).
*   4. Starts the scan.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistStartSample(void)
{
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    /* CSDv2 HW IP block section */

    /* Disable the CSD interrupt to prevent it during coarse initialization */
    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);
    /* Enable power to sub-blocks */
    CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, `$INSTANCE_NAME`_HSCMP_EN_MASK);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd |
                                                  `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |
                                                  `$INSTANCE_NAME`_CONFIG_ENABLE_MASK);

        /*  Wait until CSD block power is ON */
        CyDelayCycles(`$INSTANCE_NAME`_BIST_BLOCK_ON_DELAY);
    #else
        /*  Wait until HSCMP power is ON */
        CyDelayCycles(`$INSTANCE_NAME`_BIST_HSCMP_ON_DELAY);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

    if (`$INSTANCE_NAME`_bistHwConfig != `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E)
    {
        /* Pre charging Cmod and Csh */
        `$INSTANCE_NAME`_BistCmodPrecharge();
    }
    /* Trigger scanning */
    `$INSTANCE_NAME`_BistTriggerScan();

#else
    /* CSDv1 HW IP block section */
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();

    /*  Enable the CSD block. Disconnect the Vref buffer from AMUX */
    #if ((`$INSTANCE_NAME`_CSH_PRECHARGE_IO_BUF == `$INSTANCE_NAME`_CSD_CSH_PRECHARGE_SRC) &&\
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CMOD_PRECHARGE_CONFIG_CSD_EN);
    #else
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG_CSD_EN);
    #endif

    /* Restart the clocks. Scan one cycle to reset the flip-flop for the Direct clock mode */
    if (`$INSTANCE_NAME`_bistHwConfig != `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E)
    {
        `$INSTANCE_NAME`_BistClockRestart();
    }
    /* Pre-charging Cmod and Csh */
    `$INSTANCE_NAME`_BistCmodPrecharge();
    /* Trigger Scan */
    `$INSTANCE_NAME`_BistTriggerScan();

    CyExitCriticalSection(interruptState);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistEnableHwSnsCap
****************************************************************************//**
*
* \brief
*  Sets up the `$INSTANCE_NAME` block to perform capacitance measuring.
*
* \details
*   This function prepares the `$INSTANCE_NAME` block HW to the CSD sensing mode
*   with BIST defined parameters.
*   The function performs the following tasks:
*   1. Sets the default CSD configuration for BIST scans.
*   2. Enables shield electrodes and Csh (if defined).
*   3. Sets Idac config for BIST scans.
*   4. Sets a sensor clock frequency (only for a sensor capacitance measuring).
*   5. Sets the ISR handler for BIST scans.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistEnableHwSnsCap(void)
{
    uint32 newRegValue;

    `$INSTANCE_NAME`_bistConfigCsd = `$INSTANCE_NAME`_BIST_CSD_CONFIG;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
        /* Verification of the BIST mode */
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

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)

        /* Initialize unused CSD IP registers to the default state */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_SET_PTR,         `$INSTANCE_NAME`_BIST_INTR_SET_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_BIST_SW_DSI_SEL_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_ADC_CTL_PTR,          `$INSTANCE_NAME`_BIST_ADC_CTL_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR,            `$INSTANCE_NAME`_AMBUF_PWR_MODE_OFF);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_BIST_SW_HS_P_SEL_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_BIST_SW_HS_N_SEL_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR,            `$INSTANCE_NAME`_BIST_HSCMP_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_TIME_PTR,         `$INSTANCE_NAME`_CSD_AUTO_ZERO_TIME);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR,           0x00000000);

        /* Connect AMUXBUS-A to CSDBUS-A */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR);
        newRegValue |= `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYA_MASK;
        CY_SET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR, newRegValue);

        /* Verification of the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Connect CMOD to AMUXBUS-A */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
            newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT);
            CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);

            /* Connect CMOD to (sense path) to CSDCOMP */
            #if (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
                CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE);
            #elif (`$INSTANCE_NAME`_CSD__CSHIELD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION)
                CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE);
            #endif /* (`$INSTANCE_NAME`_CSD__CMOD_PAD == `$INSTANCE_NAME`_CMOD_CONNECTION) */
        }

        /* Verification of the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Configure a shield driving path */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                /* Connect AMUXBUS-B to CSDBUS-B (and AMUXBUS-A to CSDBUS-A ) */
                CY_SET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR, `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYA_MASK | `$INSTANCE_NAME`_SW_BYP_SEL_SW_BYB_MASK);

                /* Connect AMUXBUS-B to the HSCMP positive input */
                CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        }

        /* Connect VREF to REFGEN (IAIB switch is open) */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
        newRegValue |= `$INSTANCE_NAME`_SW_REFGEN_SEL_SW_SGR_MASK;
        CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR, newRegValue);

        #if (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV)
            /* Connect VREFLOW (from AMBUF and RefGen is in the bypass mode) to CSDCOMP when Vdda < 2 V */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRL_STATIC_CLOSE);
            /* Configure REFGEN to the bypass mode when Vdda < 2 V */
            CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR, `$INSTANCE_NAME`_REFGEN_REFGEN_EN_MASK |
                                                      `$INSTANCE_NAME`_REFGEN_BYPASS_MASK |
                                                      `$INSTANCE_NAME`_REFGEN_VREFLO_INT_MASK);
            /*  Connect Vrefhi to the AMUBUF positive input when Vdaa < 2V
             *  Connect AMUBUF to the SCDCMP negative input when Vdaa < 2V
             */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                              `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRLB_STATIC_CLOSE);
            /* Turn on the CSD_AMBUF normal power level when Vdaa < 2V */
            CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR, `$INSTANCE_NAME`_AMBUF_PWR_MODE_NORM);
        #else
            /* Connect VREFHI (from RefGen) to CSDCOMP when Vdda >= 2 V */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_N_SEL_PTR, `$INSTANCE_NAME`_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE);

            /* Verification of the BIST mode */
            if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                    /* Configure REFGEN. Set a reference voltage when Vdda >= 2 V */
                    CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR, `$INSTANCE_NAME`_REFGEN_WITH_SHIELD);
                    /* Turn on the CSD_AMBUF high power level when Vdaa >= 2V */
                    CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR, `$INSTANCE_NAME`_AMBUF_PWR_MODE_HI);
                #else
                    /* Configure REFGEN. Set a reference voltage when Vdda >= 2 V */
                    CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR, `$INSTANCE_NAME`_REFGEN_NO_SHIELD);
                    /* Connect VREFHI to HSCOMP */
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
            }
            else
            {
                /* Configure REFGEN. Set a reference voltage when Vdda >= 2 V */
                CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR, `$INSTANCE_NAME`_REFGEN_NO_SHIELD);
                /* Connect VREFHI to HSCOMP */
                CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
            }
            /* Make sure that CSD_AMBUF is unconnected from Vrefhi and from Vreflo */
            CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_DEFAULT);
        #endif /* (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV) */

        if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Configure ModClk */
            `$INSTANCE_NAME`_SsSetModClkClockDivider(`$INSTANCE_NAME`_TST_MOD_CLK_DIVIDER);
        }

        /* Verification of the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                /* Update the CSD config register shield delay bits with a shield delay value */
                `$INSTANCE_NAME`_bistConfigCsd &= (uint32)(~`$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK);
                `$INSTANCE_NAME`_bistConfigCsd |= ((uint32)`$INSTANCE_NAME`_CSD_SHIELD_DELAY << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        }

        /* Configure CSDv2 filter delay */
        `$INSTANCE_NAME`_bistConfigCsd &= (uint32)(~`$INSTANCE_NAME`_CONFIG_FILTER_DELAY_MASK);
        `$INSTANCE_NAME`_bistConfigCsd |= `$INSTANCE_NAME`_FILTER_DELAY_CFG;

        #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            /* Enable power to sub-blocks */
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd |
                                                      `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK |
                                                      `$INSTANCE_NAME`_CONFIG_ENABLE_MASK);

            /*  Wait until CSD block powers ON */
            CyDelayCycles(`$INSTANCE_NAME`_BIST_BLOCK_ON_DELAY);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

        /* Set a number of dummy fine initialization cycles depending of the BIST mode */
        /* Set Phi1 and Phi2 switches to non-overlapping (no low EMI) and width depending on the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
        {
            CY_SET_REG32(`$INSTANCE_NAME`_SEQ_INIT_CNT_PTR, `$INSTANCE_NAME`_TST_FINE_INIT_TIME);
            CY_SET_REG32(`$INSTANCE_NAME`_SENSE_DUTY_PTR, `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI1_MASK |
                                                      `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI2_MASK);
        }
        else
        {
            CY_SET_REG32(`$INSTANCE_NAME`_SEQ_INIT_CNT_PTR, `$INSTANCE_NAME`_SEQ_INIT_CNT_FINE_INIT_SKIP);
            CY_SET_REG32(`$INSTANCE_NAME`_SENSE_DUTY_PTR, `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI1_MASK |
                                                          `$INSTANCE_NAME`_SENSE_DUTY_OVERLAP_PHI2_MASK |
                                                          `$INSTANCE_NAME`_SENSE_DUTY_TST_EXT_CAP_WIDTH );
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)

        if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Connect Cmod to AMUXBUS-A using the HSIOM registers */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
            newRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CMOD_HSIOM_SHIFT);
            CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);
        }
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            /* Verification of the BIST mode */
            if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
            {
                /* Update CSD config register shield delay bits with a shield delay value */
                `$INSTANCE_NAME`_bistConfigCsd &= (uint32)(~`$INSTANCE_NAME`_CONFIG_SHIELD_DELAY_MASK);
                `$INSTANCE_NAME`_bistConfigCsd |= ((uint32)`$INSTANCE_NAME`_CSD_SHIELD_DELAY << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT);
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
        {
            /* Enable the CSD block. Connect Vref buffer to AMUX bus to make sure that Cmod is charged before scanning in the active mode */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd);
            #else
                CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG_CSD_EN);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
        }
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */

    /* Configure the IDAC */
    `$INSTANCE_NAME`_BistSetIdac(0uL);

    if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E != `$INSTANCE_NAME`_bistHwConfig)
    {
        /* Set the clock dividers and clock source mode */
        `$INSTANCE_NAME`_BistConfigClock(`$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER);
    }
    else
    {
        #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
            /* Enable the CSD block. Connect Vref buffer to AMUX bus to make sure that Cmod is charged before scanning in the active mode */
            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd | `$INSTANCE_NAME`_CONFIG_ENABLE_MASK);
        #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */
    }
    `$INSTANCE_NAME`_ISR_StartEx(&`$INSTANCE_NAME`_BistPostSingleScan);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistConfigClock
****************************************************************************//**
*
* \brief
*   Sets the sensor clock frequency for BIST scans.
*
* \details
*   For a sensor or shield capacitance measurement, sets a calculated value of
*   the sensor clock frequency and for an external capacitance measurement, sets
*   the value for a one-period scan.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistConfigClock(uint32 snsClk)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* Update the reg value with the divider and configuration */
        CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR, snsClk - 1uL);
    #else
        /* Set a sense clock divider */
        `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClk);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSetScanDuration
****************************************************************************//**
*
* \brief
*   Calculates Scan Duration which is defined by the scan resolution.
*
* \details
*   For CSDv2: The function calculates the number of conversions and updates the
*   SEQ_NORM_CNT register. The number of conversions depends on the resolution and
*   snsClk divider.
*   For CSDv1: The function recalculates the resolution using the following equation:
*   2^resolution - 1. The calculated value is contained in the
*   `$INSTANCE_NAME`_bistCounterResolution global variable and used in the
*   `$INSTANCE_NAME`_bistStartSample() function to trigger a scan process.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSetScanDuration(void)
{
    uint32 scanDuration;

    if (`$INSTANCE_NAME`_bistHwConfig == `$INSTANCE_NAME`_BIST_HW_EXT_CAP_E)
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
            scanDuration = `$INSTANCE_NAME`_TST_EXT_CAP_DURATION;
        #else
            scanDuration = `$INSTANCE_NAME`_BIST_SCAN_DURATION_255;
        #endif
    }
    else
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
            /* Calculate the scanning resolution value in the register */
            scanDuration = (uint32) (`$INSTANCE_NAME`_BIST_10_BIT_MASK / `$INSTANCE_NAME`_TST_BASE_SNS_CLK_DIVIDER);
        #else
            scanDuration = `$INSTANCE_NAME`_BIST_SCAN_DURATION;
        #endif
    }

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* Set a number of conversions based on the scanning resolution */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_NORM_CNT_PTR, scanDuration & `$INSTANCE_NAME`_SEQ_NORM_CNT_CONV_CNT_MASK);
    #else
        /* Set up a scanning resolution */
        `$INSTANCE_NAME`_bistCounterResolution = scanDuration;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSetIdac
****************************************************************************//**
*
* \brief
*   This internal function changes the IDACs values for the BIST scan.
*
* \details
*   The functions disables the compensation IDAC if enabled and sets
*   the desired Idac value.
*
* \param idacValue
*   The Idac code to be set.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSetIdac(uint32 idacValue)
{
    #if ((`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2) && \
        (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSD_IDAC_COMP_EN))
        uint32 regValue;
        uint8  interruptState;
    #endif

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, `$INSTANCE_NAME`_BIST_IDACA_CFG | (idacValue & `$INSTANCE_NAME`_IDAC_MOD_VAL_MASK));
        #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IDACB_USED))
            CY_SET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR, `$INSTANCE_NAME`_BIST_IDACB_CFG);
        #endif
    #else
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
            CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, `$INSTANCE_NAME`_BIST_IDAC_CFG | (idacValue & `$INSTANCE_NAME`_BIST_IDAC_MOD_VAL_MASK));
        #else
            interruptState = CyEnterCriticalSection();
            regValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR);
            regValue &= ~(`$INSTANCE_NAME`_BIST_IDAC_MOD_MASK);
            regValue |= (`$INSTANCE_NAME`_BIST_IDAC_CFG | (idacValue & `$INSTANCE_NAME`_BIST_IDAC_MOD_VAL_MASK));
            CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, regValue);
            CyExitCriticalSection(interruptState);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistCmodPrecharge
****************************************************************************//**
*
* \brief
*  This function initializes the Cmod charging to Vref.
*
* \details
*  For CSDv1:
*  The function initializes the Cmod charging to Vref.
*  Then it waits until Cmod is completely charged
*  to Vref to have stable raw counts. The Software Watchdog Counter is implemented to
*  prevent project hanging.
*
*  For CSDv2:
*  Coarse initialization for CMOD and Cch.
*  The coarse initialization is performed by HSCOMP.
*  The HSCOMP monitors the Cmod voltage via the Cmod sense path
*  and charges the Cmod using the HCAV switch via CSDBUS-A, AMUXBUS-A
*  and static connection of Cmod to AMUXBUS-A.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistCmodPrecharge(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* CSDv2 HW IP block section */

        uint32 watchdogCounter;

        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
             (0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
            uint32 tmpRegValue;
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                   (0u != `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR,  `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_INIT);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,  `$INSTANCE_NAME`_SW_SHIELD_SEL_SW_HCAV_HSCMP);

        /*
         * Connect CMOD (sense path) to HSCOMP
         * Connect AMUXBUS-B to the HSCMP positive input
         */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_SW_HS_P_SEL_COARSE);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                /* Verification of the BIST mode */
                if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
                {
                    /* Connect CTANK to AMUXBUS-A */
                    tmpRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                    tmpRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CSH_HSIOM_MASK);
                    tmpRegValue |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT);
                    CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, tmpRegValue);
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */

        CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR, `$INSTANCE_NAME`_BIST_SW_RES_INIT);

        /* Clear all interrupt pending requests */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_SAMPLE_MASK |
                                                `$INSTANCE_NAME`_INTR_SET_INIT_MASK |
                                                `$INSTANCE_NAME`_INTR_SET_ADC_RES_MASK);

        /* Enable the INIT interrupt */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_MASK_PTR, `$INSTANCE_NAME`_INTR_MASK_INIT_MASK);

        /* Start SEQUENCER for coarse initialization for Cmod */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SEQ_START_SEQ_MODE_MASK |
                                                     `$INSTANCE_NAME`_SEQ_START_START_MASK);

        /* Initialize the watchdog counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_SOFTWARE_WDT_CYCLES_NUM;

        /* Wait until INTR.INIT is set */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_INTR_PTR) & `$INSTANCE_NAME`_INTR_INIT_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        if (0u == watchdogCounter)
        {
            /* Set the sequencer to an idle state if coarse initialization fails */
            CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SEQ_START_ABORT_MASK);
        }

        /* Set scanning configuration for switches */
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_BIST_SW_FW_MOD_SEL_SCAN);
        CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,`$INSTANCE_NAME`_BIST_SW_FW_TANK_SEL_SCAN);

    #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

        uint32 newRegValue;
        uint32 watchdogCounter;

        /*  Save the current IDAC configuration */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_IDAC_PTR);

        /*  Wait until Cmod discharges below Vref */
        CyDelayCycles(`$INSTANCE_NAME`_CMOD_DISCHARGE_CYCLES);

        /*  Set the IDAC configuration for fast Cmod pre-charge to Vref */
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, `$INSTANCE_NAME`_CSD_IDAC_PRECHARGE_CONFIG);

        /*  Initialize the watchdog counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_SOFTWARE_WDT_CYCLES_NUM;
        /*  Wait until Cmod reaches Vref */
        while((0u == (CY_GET_REG32(`$INSTANCE_NAME`_STATUS_PTR) & `$INSTANCE_NAME`_STATUS_SAMPLE)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        /*  Restore the current IDAC configuration */
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_PTR, newRegValue);

        /*  Enable the sense modulator output */
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_bistConfigCsd | `$INSTANCE_NAME`_BIST_CTANK_PRECHARGE_CONFIG_CSD_EN | `$INSTANCE_NAME`_CONFIG_SENSE_EN_MASK);

        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WaitEndOfScan
****************************************************************************//**
*
* \brief
*   Waits for the end of scan for capacitance measurements.
*
* \details
*   Apart from waiting for an end of the scan, the function sets a watchdog to prevent
*   a hangout.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_WaitEndOfScan(uint32 timeout)
{
    uint32 watchdogCounter = timeout;

    while (((*(volatile uint8 *)&`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY) != 0u) &&
           (0u != watchdogCounter))
    {
        watchdogCounter--;
    }
    (void)watchdogCounter;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistTriggerScan
****************************************************************************//**
*
* \brief
*  This function triggers scanning.
*
* \details
*  For CSDv1:
*  Writes a resolution to start scanning.
*
*  For CSDv2:
*  Triggers the fine initialization and starts sampling.
*  For the fine initialization and sampling, the measured capacitance is charged
*  from Idac and discharged to the ground using the GPIO cell switches.
*  The CSDCOMP monitors the voltage on the measured capacitance using the sense path
*  and charges it to Vref using IDAC.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistTriggerScan(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        /* CSDv2 HW IP block section */
        uint32 watchdogCounter;

        /* Clear previous interrupts */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_INTR_SET_SAMPLE_MASK |
                                                `$INSTANCE_NAME`_INTR_SET_INIT_MASK |
                                                `$INSTANCE_NAME`_INTR_SET_ADC_RES_MASK);
        /* Clear pending interrupts  */
        CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER);
        /* Enable the CSD interrupt */
        CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN)
            /* Verification of the BIST mode */
            if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_BIST_SW_SHIELD_SEL);
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_SW_HS_P_SEL_SCAN);
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)
                        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE);
                        /* Connect CTANK to AMUXBUS-B */
                        `$INSTANCE_NAME`_BistEnableShieldTank();
                    #else
                        CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_SW_HS_N_SEL_SW_HCRL_STATIC_CLOSE);
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN) */
                #else
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR, 0x00000000uL);
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_STATIC_OPEN);
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_STATIC_OPEN);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
            }
            else
            {
                CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR, 0x00000000uL);
                CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_STATIC_OPEN);
                CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_STATIC_OPEN);
            }
        #else
            CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR, 0x00000000uL);
            CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_STATIC_OPEN);
            CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_STATIC_OPEN);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */

        CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR, `$INSTANCE_NAME`_BIST_SW_RES_SCAN);

        /* Enable CSDCMP */
        if (`$INSTANCE_NAME`_BIST_HW_EXT_CAP_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR, `$INSTANCE_NAME`_CSDCMP_TST_CAP_MEAS);
        }
        else
        {
            CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR, `$INSTANCE_NAME`_CSDCMP_CSDCMP_EN_MASK);
        }
        /* Verification of the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV))
                    /*  Connect Vrefhi to the AMUBUF positive input. Connect AMUBUF output to CSDBUSB with sych PHI2  */
                    CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR, `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                                      `$INSTANCE_NAME`_SW_AMUXBUF_SEL_SW_ICB_PHI2);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (`$INSTANCE_NAME`_2000_MV <= `$INSTANCE_NAME`_CYDEV_VDDA_MV)) */
        }

        /* Verification of the BIST mode */
        if (`$INSTANCE_NAME`_BIST_HW_SNS_CAP_CSD_E == `$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, `$INSTANCE_NAME`_BIST_HSCMP_SCAN_MASK);
            #else
                /* Disable HSCOMP during the sampling phase when the shield is disabled */
                CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, 0uL);
            #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        }
        else
        {
            /* Disable HSCOMP during the sampling phase when the shield is disabled */
            CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR, 0uL);
        }
        /* Enable the SAMPLE interrupt */
        CY_SET_REG32(`$INSTANCE_NAME`_INTR_MASK_PTR, `$INSTANCE_NAME`_INTR_MASK_SAMPLE_MASK);

        /* Initialize the watchdog counter to prevent a hang */
        watchdogCounter = `$INSTANCE_NAME`_SOFTWARE_WDT_CYCLES_NUM;
        /* Wait for an IDLE state of the CSDv2 HW sequencer */
        while((0u != (CY_GET_REG32(`$INSTANCE_NAME`_STAT_SEQ_PTR) & `$INSTANCE_NAME`_STAT_SEQ_SEQ_STATE_MASK)) && (0u != watchdogCounter))
        {
            watchdogCounter--;
        }

        /* Start SEQUENCER for a fine initialization scan for Cmod and then for normal scan */
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SEQ_START_AZ0_SKIP_MASK |
                                                     `$INSTANCE_NAME`_SEQ_START_AZ1_SKIP_MASK |
                                                     `$INSTANCE_NAME`_SEQ_START_START_MASK);

    #else

        /* CSDv1 HW IP block section */

        /* Set a resolution to the counter register to start scanning */
        CY_SET_REG32(`$INSTANCE_NAME`_COUNTER_PTR, `$INSTANCE_NAME`_bistCounterResolution);

    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}
#endif /*(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_MEASUREMENT_GROUP_EN) */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_HW_GROUP_EN)

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BistSwitchHwConfig
****************************************************************************//**
*
* \brief
*   The function switches HW configuration.
*
* \details
*   The function checks the current HW configuration of the `$INSTANCE_NAME` block.
*   If it differs from the desired configuration, the function disables the current
*   configuration and sets the desired one.
*
* \param config
*   Specifies the desired configuration.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_BistSwitchHwConfig(`$INSTANCE_NAME`_BIST_HW_CONFIG_ENUM config)
{
    if (`$INSTANCE_NAME`_bistHwConfig != config)
    {
        /* The requested config differs from the current one. Disable the current config */
        switch(`$INSTANCE_NAME`_bistHwConfig)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN)
                case `$INSTANCE_NAME`_BIST_HW_SNS_SHORT_E:
                {
                    /* Do nothing */
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_SHORT_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS2SNS_SHORT_EN)
                case `$INSTANCE_NAME`_BIST_HW_S2S_SHORT_E:
                {
                    /* Do nothing */
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
                    /* Do nothing */
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_EXTERNAL_CAP_EN) */
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
*   Sets all sensors pins in the desired state.
*
* \details
*   Sets all sensors and shield (if defined) pins in the desired state.
*
* \param config
*   Specifies the desired IO configuration.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SwitchAllIOState(`$INSTANCE_NAME`_BIST_IO_CONFIG_ENUM config)
{
    /* Re-configure the IOs if the mode is changed */
    if (`$INSTANCE_NAME`_bistIoConfig != config)
    {
        switch(config)
        {
            case `$INSTANCE_NAME`_BIST_IO_STRONG_E:
            {
                `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_STRONG);
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
                    /* Configure the CSX sensors to Strong */
                    #if (0u != `$INSTANCE_NAME`_CSX_EN)
                        /* Set all IO to Strong (including CSX IOs). It is faster than a loop through only CSX sensors */
                        `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_STRONG);
                    #endif
                        /* Reconfigure only the CSD sensors to the required state */
                        `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection();
                    break;
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN)
                case `$INSTANCE_NAME`_BIST_IO_SHIELD_E:
                {
                    /* Configure the CSX sensors to Strong */
                    #if (0u != `$INSTANCE_NAME`_CSX_EN)
                        /* Set all IO to Strong (including CSX IOs). It is faster than a loop through only CSX sensors */
                        `$INSTANCE_NAME`_SetAllIOPcState(`$INSTANCE_NAME`_TST_PC_STRONG);
                    #endif
                        /* Reconfigure only the CSD sensors to the required state */
                        `$INSTANCE_NAME`_BistSetAllInactiveSensorConnection();
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
*  This internal function sets a certain electrode port output data.
*
* \details
*  This function sets an electrode port output data register (DR) in the required state.
*
* \param *ioPtr
*  The pointer to the specified electrode in the flash IO structure.
*
* \param value
*  The port output data to be set for an electrode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetElectrodeDr(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value)
{
    uint32 regValue;
    uint8  interruptState;

    /*  Set a data register */
    interruptState = CyEnterCriticalSection();
    regValue = CY_GET_REG32(ioPtr->drPtr);
    regValue &= ~(ioPtr->mask);
    regValue |= value << ioPtr->drShift;
    CY_SET_REG32(ioPtr->drPtr, regValue);
    CyExitCriticalSection(interruptState);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetElectrodePc
****************************************************************************//**
*
* \brief
*  This internal function sets a certain electrode drive mode.
*
* \details
*  The function sets an electrode drive mode (PC register) in the required state.
*
* \param *ioPtr
*  The pointer to the specified electrode in the flash IO structure.
*
* \param value
*  the drive mode to be set for an electrode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetElectrodePc(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value)
{
    uint32 regValue;
    uint8  interruptState;

    /* Update port configuration register (drive mode) */
    interruptState = CyEnterCriticalSection();
    regValue = CY_GET_REG32(ioPtr->pcPtr);
    regValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << ioPtr->shift);
    regValue |= value << ioPtr->shift;
    CY_SET_REG32(ioPtr->pcPtr, regValue);
    CyExitCriticalSection(interruptState);
}

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
    (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAllIOHsiomState
****************************************************************************//**
*
* \brief
*  This internal function sets all the pins in the required HSIOM mode.
*
* \details
*  This function sets all the pins to the required HSIOM mode.
*
* \param value
*  The required HSIOM mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetAllIOHsiomState(uint32 value)
{
    uint32 loopIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];

    /*  Loop through all the electrodes */
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

    /*  Loop through all electrodes */
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
*  This internal function sets the specific drive mode for all electrodes.
*
* \details
*  This function sets the specific drive mode (PC register) in the required state for all electrodes.
*
* \param value
*  The drive mode to be set for all electrodes.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetAllIOPcState(uint32 value)
{
    uint32 loopIndex;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];

    /*  Loop through all electrodes */
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
*  This internal function sets a certain electrode in the required HSIOM mode.
*
* \details
*  This function sets an electrode to the required HSIOM mode.
*
* \param *ioPtr
*  The pointer to the specified electrode in the flash IO structure.
*
* \param value
*  The required HSIOM mode.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SetElectrodeHsiom(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr, uint32 value)
{
    uint32 regValue;
    uint8  interruptState;

    /* Update the HSIOM port select register */
    interruptState = CyEnterCriticalSection();
    regValue = CY_GET_REG32(ioPtr->hsiomPtr);
    regValue &= ~(ioPtr->hsiomMask);
    regValue |= (value << ioPtr->hsiomShift);
    CY_SET_REG32(ioPtr->hsiomPtr, regValue);
    CyExitCriticalSection(interruptState);
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SNS_CAP_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_SH_CAP_EN) || \
          ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
           (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))) */


/* [] END OF FILE */
