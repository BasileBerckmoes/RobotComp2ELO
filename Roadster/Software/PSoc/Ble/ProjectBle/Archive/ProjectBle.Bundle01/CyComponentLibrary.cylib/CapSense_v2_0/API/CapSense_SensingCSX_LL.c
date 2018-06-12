/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingCSX_LL.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file defines the data structure global variables and provides
*   implementation for the low-level APIs of the CSX part of
*   the Sensing module. The file contains the APIs used for the CSD block
*   initialization, calibration and scanning.
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
#include "gpio/cy_gpio.h"

#include "cy_device_headers.h"
#include "cyfitter_gpio.h"
#include "cyfitter_sysint_cfg.h"

#include "`$INSTANCE_NAME`_ModClk.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_SensingCSX_LL.h"
#include "`$INSTANCE_NAME`_Sensing.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)

/*******************************************************************************
* Function constants
*******************************************************************************/

#define  `$INSTANCE_NAME`_NUM_HALF_CYCLES                       (2u)


/*******************************************************************************
* Defines module variables
*******************************************************************************/

/* Local variable used to store the Scan period */
volatile uint16 `$INSTANCE_NAME`_csxScanPeriod = 0u;
/* Local variable used to return raw count from the post scan ISR */
volatile uint16 `$INSTANCE_NAME`_csxRawCount = 0u;
/* Pointer to Flash structure to hold Tx electrode that was connected previously */
static `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curTxIOPtr;
/* Pointer to Flash structure to hold Rx electrode that was connected previously */
static `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curRxIOPtr;
/* Local variable to hold total Tx in widget, while scanning all the sensors in widget */
static uint16 `$INSTANCE_NAME`_curWdgtTotalRx = 0u;
/* Local variable to hold total Rx in widget, while scanning all the sensors in widget */
static uint16 `$INSTANCE_NAME`_curWdgtTotalTx = 0u;
/* Flag to indicate that electrodes were connected previously */
static uint16 `$INSTANCE_NAME`_eleCsxDisconnectFlag = 0u;
/* Pointer to Flash structure holding info of sensor to be scanned */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
    static `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curGangRxPtr = 0u;
    static `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curGangTxPtr = 0u;
#endif

/*******************************************************************************
* Module local function declarations
*******************************************************************************/
/**
* \cond SECTION_CYSENSE_INTERNAL
* \addtogroup group_cysense_internal
* \{
*/

static void `$INSTANCE_NAME`_SsCSXStartSample(void);
static void `$INSTANCE_NAME`_SsCSXPostMultiScan(void);
static void `$INSTANCE_NAME`_SsCSXPostSingleScan(void);
static uint16 `$INSTANCE_NAME`_SsCalcCsxScanPeriod(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *wdgtPtr);

__STATIC_INLINE void `$INSTANCE_NAME`_SsCSXStartSampleExt(void);

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
    static uint32 `$INSTANCE_NAME`_SsCSXOversample(void);
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
    static void `$INSTANCE_NAME`_SsCSXPostMultiScanGanged(void);
#endif

/* Pointer to Pointer to function used to register callback in ISR */
void (*`$INSTANCE_NAME`_CSXPostScanApiPtr)(void) = &`$INSTANCE_NAME`_SsCSXPostMultiScan;
/** \}
* \endcond */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXInitialize
****************************************************************************//**
*
* \brief
*   Performs hardware and firmware initialization required for the CSX operation
*   of the `$INSTANCE_NAME` Component.
*
* \details
*   This function initializes hardware to perform the CSX sensing operation. This
*   function is called by the `$INSTANCE_NAME`_Start() API during the Component
*   initialization. If both CSX and CSD sensing methods are used in the Component,
*   this function is called by the `$INSTANCE_NAME`_SetupWidget() API to change hardware
*   configured for CSD to re-initialize for the CSX sensing.
*
*   If the CSD and CSX widgets are used in the Component, it is recommended not to
*   mix the CSD widgets between the CSX widgets, instead, place all CSX widgets in
*   the required scanning order and then place the CSD widgets in the customizer.
*   For the Component API, this action will eliminate the need for changing the hardware
*   configuration for every widget scan and will increase the execution speed
*   in the `$INSTANCE_NAME`_ScanAllWidgets() when the API is called.
*
*   Similarly, it is recommended to set up and scan all the CSX widgets in such
*   a sequence that the `$INSTANCE_NAME`_SetupWidget() API  shouldn't need
*   hardware  sensing-configuration change.
*
*   It is highly not recommended to call this API directly from the application layer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXInitialize(void)
{
    uint32 interruptState;
    uint32 tmpRegVal;

    `$INSTANCE_NAME`_BistDischargeExtCapacitors();

    Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CintA_0_PORT, `$INSTANCE_NAME`_CintA_0_NUM, `$INSTANCE_NAME`_CintA_0_DRIVEMODE);
    Cy_GPIO_SetDrivemode(`$INSTANCE_NAME`_CintB_0_PORT, `$INSTANCE_NAME`_CintB_0_NUM, `$INSTANCE_NAME`_CintB_0_DRIVEMODE);

    /* Clear all pending interrupts of CSD block */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR,             `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_SET_PTR,         `$INSTANCE_NAME`_DEFAULT_CSD_INTR_SET_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_MASK_PTR,        `$INSTANCE_NAME`_DEFAULT_CSD_INTR_MASK_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR,            `$INSTANCE_NAME`_DEFAULT_CSD_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_AMBUF_PTR,            `$INSTANCE_NAME`_DEFAULT_CSD_AMBUF_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_REFGEN_PTR,           `$INSTANCE_NAME`_DEFAULT_CSD_REFGEN_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR,           `$INSTANCE_NAME`_DEFAULT_CSD_CSDCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACA_PTR,            `$INSTANCE_NAME`_DEFAULT_CSD_IDACA_CFG);

    #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IDACB_USED))
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACB_PTR,    `$INSTANCE_NAME`_DEFAULT_CSD_IDACB_CFG);
    #endif /* (0u != `$INSTANCE_NAME`_ADC_EN) || (0u != `$INSTANCE_NAME`_IDACB_USED) */

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_RES_PTR,           `$INSTANCE_NAME`_DEFAULT_CSD_SW_RES_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_PERIOD_PTR,     `$INSTANCE_NAME`_DEFAULT_CSD_SENSE_PERIOD_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_DUTY_PTR,       `$INSTANCE_NAME`_DEFAULT_CSD_SENSE_DUTY_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_CSD_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_CSD_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_CSD_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR,   `$INSTANCE_NAME`_DEFAULT_CSD_SW_AMUXBUF_SEL_CFG);

    interruptState = Cy_SysLib_EnterCriticalSection();
    tmpRegVal = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR);
    tmpRegVal &= ~(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_SW_BYA_MSK);
    tmpRegVal |= `$INSTANCE_NAME`_DEFAULT_CSD_SW_BYP_SEL_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_BYP_SEL_PTR,       tmpRegVal);
    Cy_SysLib_ExitCriticalSection(interruptState);

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_P_SEL_PTR,     `$INSTANCE_NAME`_DEFAULT_CSD_SW_CMP_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR,     `$INSTANCE_NAME`_DEFAULT_CSD_SW_CMP_N_SEL_CFG);

    interruptState = Cy_SysLib_EnterCriticalSection();
    tmpRegVal = CY_GET_REG32(`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR);
    tmpRegVal &= ~`$INSTANCE_NAME`_DEFAULT_CSD_SW_REFGEN_SEL_MSK;
    tmpRegVal |= `$INSTANCE_NAME`_DEFAULT_CSD_SW_REFGEN_SEL_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR,    tmpRegVal);
    Cy_SysLib_ExitCriticalSection(interruptState);

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_CSD_SW_FW_MOD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_DEFAULT_CSD_SW_FW_TANK_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_DEFAULT_CSD_SW_DSI_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IO_SEL_PTR,           `$INSTANCE_NAME`_DEFAULT_CSD_SW_IO_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_TIME_PTR,         `$INSTANCE_NAME`_DEFAULT_CSD_SEQ_TIME_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_INIT_CNT_PTR,     `$INSTANCE_NAME`_DEFAULT_CSD_SEQ_INIT_CNT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR,     `$INSTANCE_NAME`_DEFAULT_CSD_SEQ_NORM_CNT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_ADC_CTL_PTR,          `$INSTANCE_NAME`_DEFAULT_CSD_ADC_CTL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR,        `$INSTANCE_NAME`_DEFAULT_CSD_SEQ_START_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR,           `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG_CFG);

    `$INSTANCE_NAME`_ModClk_SetDivider((uint32)`$INSTANCE_NAME`_dsRam.modCsxClk - 1uL);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
        `$INSTANCE_NAME`_SsSetSnsClockDivider((uint32)`$INSTANCE_NAME`_dsRam.snsCsxClk);
    #endif

    /* Set all IO states to default state */
    `$INSTANCE_NAME`_SsSetIOsInDefaultState();

    /* Enable CSD block interrupt and set interrupt vector to CSX sensing method */
    `$INSTANCE_NAME`_SsIsrInitialize(&`$INSTANCE_NAME`_CSXScanISR);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXElectrodeCheck
****************************************************************************//**
*
* \brief
*   Check if electrodes were previously connected using
*   the `$INSTANCE_NAME`_CSXSetupWidgetExt() API and if yes, disconnect them.
*
* \details
*   This function checks if `$INSTANCE_NAME`_eleCsxDisconnectFlag is set.
*   If it is set, the function disconnects the previously connected electrode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXElectrodeCheck(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
        uint32 numElectrodes;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN) */

    if (0u != `$INSTANCE_NAME`_eleCsxDisconnectFlag)
    {
       /* Disconnect if electrodes were previous connected by SetupWidgetExt() API */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
            /* Check ganged sns flag */
            if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_curFlashWdgtPtr->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
            {
                /* 1. Get number of pins in previous connected Tx electrode
                    3. Get Tx pointer
                    4. Disconnect all Tx */
                numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins;
                `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];

                do
                {
                    `$INSTANCE_NAME`_CSXDisconnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                    numElectrodes--;
                } while (0u != numElectrodes);

                /* 1. Get number of pins in previous connected Rx electrode
                    3. Get Rx pointer
                    4. Disconnect all Rx */
                numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins;
                `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];

                do
                {
                    `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                    numElectrodes--;
                } while (0u != numElectrodes);
            }
            else
            {
                /* Disconnect if electrodes were previous connected by SetupWidgetExt API */
                `$INSTANCE_NAME`_CSXDisconnectTx(`$INSTANCE_NAME`_curTxIOPtr);
                `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr);
            }
        #else
            /* Disconnect if electrodes were previous connected by SetupWidgetExt API */
            `$INSTANCE_NAME`_CSXDisconnectTx(`$INSTANCE_NAME`_curTxIOPtr);
            `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr);
        #endif
        `$INSTANCE_NAME`_eleCsxDisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXSetupWidget
****************************************************************************//**
*
* \brief
*  Performs hardware and firmware initialization required for scanning sensors
*  in a specific widget using the CSX sensing method. This function requires
*  using the `$INSTANCE_NAME`_CSXScan() function to start scanning.
*
* \details
*  This function initializes the widgets specific common parameters to perform
*  the CSX scanning. The initialization includes the following:
*    1. The CSD_CONFIG register.
*    2. The IDAC register.
*    3. The Sense clock frequency
*    4. The phase alignment of the sense and modulator clocks.
*
*  This function does not connect any specific sensors to the scanning hardware
*  and neither does it start a scanning process. The `$INSTANCE_NAME`_CSXScan()
*  function must be called after initializing the widget to start scanning.
*
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  This function is called by the `$INSTANCE_NAME`_SetupWidget() API if the
*  given widget uses the CSX sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning sensors in the specific widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXSetupWidget(uint32 widgetId)
{
    /* variable to access widget details */
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * curRamWdgtBasePtr;

    uint32 tmpRegVal;
    uint32 snsClkVal;

    /* Save the current widget Id */
    `$INSTANCE_NAME`_widgetIndex = (uint8)widgetId;


    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))
         `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_CSX_E);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)) */

    /*
    *  Check if CSX electrodes were previously connected using
    *  `$INSTANCE_NAME`_CSXSetupWidgetExt API and if yes, disconnect them
    */
    `$INSTANCE_NAME`_CSXElectrodeCheck();

    /* Configure hardware block */
    `$INSTANCE_NAME`_curFlashWdgtPtr = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

    curRamWdgtBasePtr = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2WdgtRam;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
        snsClkVal = (uint32)`$INSTANCE_NAME`_dsRam.snsCsxClk;
    #else
        snsClkVal = (uint32)curRamWdgtBasePtr->snsClk;
    #endif /* (`$INSTANCE_NAME`_ENABLE  == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) */

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR, (uint32)curRamWdgtBasePtr->resolution);
    `$INSTANCE_NAME`_csxScanPeriod  = `$INSTANCE_NAME`_SsCalcCsxScanPeriod(curRamWdgtBasePtr);

    tmpRegVal = (uint32)curRamWdgtBasePtr->snsClkSource;

    snsClkVal = (snsClkVal - 1uL) & `$INSTANCE_NAME`_CSD_SENSE_PERIOD_SENSE_DIV_MSK;
    tmpRegVal = (tmpRegVal << `$INSTANCE_NAME`_CSD_SENSE_PERIOD_LFSR_SIZE_POS) | snsClkVal |
        `$INSTANCE_NAME`_CSD_SENSE_PERIOD_LFSR_BITS_MSK;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SENSE_PERIOD_PTR, tmpRegVal);
    `$INSTANCE_NAME`_ModClk_SetDivider((uint32)`$INSTANCE_NAME`_dsRam.modCsxClk - 1uL);

}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXSetupWidgetExt
****************************************************************************//**
*
* \brief
*  Performs extended initialization for the CSX widget and also performs
*  initialization required for a specific sensor in the widget. This function
*  requires using the `$INSTANCE_NAME`_CSXScan() function to initiate a scan.
*
* \details
*  This function does the same tasks as `$INSTANCE_NAME`_CSXSetupWidget() and
*  also connects a sensor in the widget for scanning. Once this function is
*  called to initialize a widget and a sensor, the `$INSTANCE_NAME`_CSXScanExt()
*  function must be called to scan the sensor.
*
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specifies the ID number of the widget to perform hardware and firmware
*  initialization required for scanning a specific sensor in a specific widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorId
*  Specifies the ID number of the sensor within the widget to perform hardware
*  and firmware initialization required for scanning a specific sensor in a
*  specific widget.
*  A macro for the sensor ID within a specified widget can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
*******************************************************************************/

void `$INSTANCE_NAME`_CSXSetupWidgetExt(uint32 widgetId, uint32 sensorId)
{
    uint32 txIndex;
    uint32 rxIndex;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
        uint16 numElectrodes;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN) */

    /* Initialize widget */
    `$INSTANCE_NAME`_CSXSetupWidget(widgetId);
    `$INSTANCE_NAME`_sensorIndex = (uint8)sensorId;

    /* initialize sensor data structure pointer to appropriate address */
    `$INSTANCE_NAME`_curRamSnsPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsRam;
    `$INSTANCE_NAME`_curRamSnsPtr = &`$INSTANCE_NAME`_curRamSnsPtr[sensorId];

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        if (0u != `$INSTANCE_NAME`_curRamSnsPtr->subConvNum)
        {
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

    /*
    *  Find Tx and Rx index for given snsIndex
    *    rxIndex = sensorId / TxCount
    *    txIndex = sensorId % TxCount
    */
    rxIndex = sensorId /`$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
    txIndex = sensorId % `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;

    /* If widget is APA, find node (Tx/Rx) to be connected for scanning */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
        if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_curFlashWdgtPtr->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
        {
            /*
            *  1. Get access to Rx sensor pointer (Rx = Base + rxIndex).
            *  2. Get number of Rx electrodes
            *  3. Get Rx pointer
            *  4. Connect all Rx
            */
            `$INSTANCE_NAME`_curGangRxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
            `$INSTANCE_NAME`_curGangRxPtr += rxIndex;
            numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins;
            `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];

            do
            {
                `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                numElectrodes--;
            } while (0u != numElectrodes);

            /*
            *  1. Get access to Tx sensor pointer (Tx = Base + NumberRx + TxIndex).
            *  2. Get number of Tx electrodes
            *  3. Get Tx pointer
            *  4. Connect all Tx
            */
            `$INSTANCE_NAME`_curGangTxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
            `$INSTANCE_NAME`_curGangTxPtr += (`$INSTANCE_NAME`_curFlashWdgtPtr->numCols + txIndex);

            numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins;
            `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];

            do
            {
                `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                numElectrodes--;
            }while (0u != numElectrodes);

            /* Set callback to scan connected ganged sensor only */
            `$INSTANCE_NAME`_CSXPostScanApiPtr = &`$INSTANCE_NAME`_SsCSXPostSingleScan;
        }
        else
    #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) */
        {
            /*
            *  If no ganged sensor in Component OR current widget no contains ganged sns, then:
            *    1. Find Rx pointer: Rx = Base address + RxIndex
            *    2. Find Tx pointer: Tx = Base address + (total Rx + TxIndex)
            */
            `$INSTANCE_NAME`_curRxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
            `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_curRxIOPtr[rxIndex];

            `$INSTANCE_NAME`_curTxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
            `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_curTxIOPtr[(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols + txIndex)];

            /* Connect Tx and Rx IOs for scan ad set flag to indicate that IOs should be disconnected */
            `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr);
            `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr);
            `$INSTANCE_NAME`_eleCsxDisconnectFlag = `$INSTANCE_NAME`_DISCONNECT_IO_FLAG;

            /* Set callback to scan all the sensors in widget */
            `$INSTANCE_NAME`_CSXPostScanApiPtr = &`$INSTANCE_NAME`_SsCSXPostSingleScan;
        }
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        }
    #endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXScan
****************************************************************************//**
*
* \brief
*  This function initiates a scan for the sensors of the widget initialized by
*  the `$INSTANCE_NAME`_CSXSetupWidget() function.
*
* \details
*  This function performs scanning of all the sensors in the widget configured by
*  the `$INSTANCE_NAME`_CSXSetupWidget() function. It does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Initializes an interrupt callback function to initialize a scan of the
*       next sensors in a widget.
*    3. Starts scanning for the first sensor in the widget.
*
*  This function is called by the `$INSTANCE_NAME`_Scan() API if the given
*  widget uses the CSX sensing method.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example).
*
*  This function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status. The widget must be
*  preconfigured by the `$INSTANCE_NAME`_CSXSetupWidget() function if any other
*  widget was previously scanned or any other type of scan functions were used.
*
*******************************************************************************/

void `$INSTANCE_NAME`_CSXScan(void)
{
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
        uint32 numElectrodes;
    #endif
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        uint32 snsIndex = 0u;
        uint32 snsNum;
    #endif

    `$INSTANCE_NAME`_sensorIndex = 0u;

    /* initialize pointer to access sensor RAM elements */
    `$INSTANCE_NAME`_curRamSnsPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsRam;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        /* Loop through the sensors until non-skipped is found */
        snsNum = `$INSTANCE_NAME`_curFlashWdgtPtr->totalNumSns;
        while ((snsIndex < snsNum) && (`$INSTANCE_NAME`_curRamSnsPtr->subConvNum == 0u))
        {
            /* Increment sensor pointers */
            `$INSTANCE_NAME`_curRamSnsPtr++;
            `$INSTANCE_NAME`_sensorIndex++;
            snsIndex++;
        }
        /*
        *  Calculate total sensor to be scanned. If buttons, one Tx and an Rx for each sensor
        *  if Matrix button or Touchpad, M x N rule applies
        */
        `$INSTANCE_NAME`_curWdgtTotalTx = (uint16)(`$INSTANCE_NAME`_curFlashWdgtPtr->numRows - (snsIndex % `$INSTANCE_NAME`_curFlashWdgtPtr->numRows));
        `$INSTANCE_NAME`_curWdgtTotalRx  = (uint16)(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols - (snsIndex / `$INSTANCE_NAME`_curFlashWdgtPtr->numRows));

        /* Scan sensor if it's index within a valid range otherwise do nothing as all the sensors are skipped */
        if (snsIndex < snsNum)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN)
                if ((`$INSTANCE_NAME`_curFlashWdgtPtr->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK) != 0u)
                {
                    /* Connect all Rx electrodes */
                    `$INSTANCE_NAME`_curGangRxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                    `$INSTANCE_NAME`_curGangRxPtr += snsIndex /`$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
                    numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins;
                    `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                    do
                    {
                        `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                        numElectrodes--;
                    } while (0u != numElectrodes);

                    /* Connect all Tx electrodes */
                    `$INSTANCE_NAME`_curGangTxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                    `$INSTANCE_NAME`_curGangTxPtr += (`$INSTANCE_NAME`_curFlashWdgtPtr->numCols + snsIndex % `$INSTANCE_NAME`_curFlashWdgtPtr->numRows);
                    numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins;
                    `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];
                    do
                    {
                        `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                        numElectrodes--;
                    }while (0u != numElectrodes);
                    /* Assign callback to ISR */
                    `$INSTANCE_NAME`_CSXPostScanApiPtr = &`$INSTANCE_NAME`_SsCSXPostMultiScanGanged;
                }
                else
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_GANGED_SNS_EN) */
            {
                /* Find Rx pointer: Rx = Base_address + SnsIndex / total_Tx */
                `$INSTANCE_NAME`_curRxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                `$INSTANCE_NAME`_curRxIOPtr += (snsIndex / `$INSTANCE_NAME`_curFlashWdgtPtr->numRows);
                /* Find Tx pointer: Tx = Base_address + total_Rx + SnsIndex % total_Tx */
                `$INSTANCE_NAME`_curTxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                `$INSTANCE_NAME`_curTxIOPtr += `$INSTANCE_NAME`_curFlashWdgtPtr->numCols;
                `$INSTANCE_NAME`_curTxIOPtr += (snsIndex % `$INSTANCE_NAME`_curFlashWdgtPtr->numRows);
                /* Connect Tx and Rx electrodes for scan */
                `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr);
                `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr);
                /* Set callback to scan all the sensors in widget */
                `$INSTANCE_NAME`_CSXPostScanApiPtr = &`$INSTANCE_NAME`_SsCSXPostMultiScan;
            }

            /* Reset multi-frequency scan channel if enabled */
            #if (`$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN == `$INSTANCE_NAME`_ENABLE)
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
            #endif

            /* Set scan status, enter critical section and initiate scan */
            `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;

            #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                #if(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL)
                    Cy_SysLib_DelayUs(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US);
                #endif /* (`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL) */
            #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
            `$INSTANCE_NAME`_SsCSXStartSample();
        }

    #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

        /*
        *  Calculate total sensor to be scanned. If buttons, one Tx and an Rx for each sensor
        *  if Matrix button or Touchpad, M x N rule applies
        */
        `$INSTANCE_NAME`_curWdgtTotalTx = `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
        `$INSTANCE_NAME`_curWdgtTotalRx  = `$INSTANCE_NAME`_curFlashWdgtPtr->numCols;

        /* If Component contains CSX ganged sensor, then check if widget contains ganged sensor */
        #if (`$INSTANCE_NAME`_CSX_GANGED_SNS_EN == 1u)
            if ((`$INSTANCE_NAME`_curFlashWdgtPtr->staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK) != 0u)
            {
                /*
                *  1. Get sns pointer for first Rx
                *  2. Get number of Rx pin
                *  3. Get pointer to the Rx pin
                *  4. Connect all Rx pins
                */
                `$INSTANCE_NAME`_curGangRxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins ;
                `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                do
                {
                    `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                    numElectrodes--;
                } while (0u != numElectrodes);

                /*
                *  1. Get sns pointer for first Tx (Tx = Base + number of Rx).
                *  2. Get number of Tx electrodes
                *  3. Get pointer the Tx electrode
                *  4. Connect all Tx
                */
                `$INSTANCE_NAME`_curGangTxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                `$INSTANCE_NAME`_curGangTxPtr += `$INSTANCE_NAME`_curFlashWdgtPtr->numCols;
                numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins ;
                `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];

                do
                {
                    `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                    numElectrodes--;
                }while (0u != numElectrodes);

                /* Assign callback to ISR */
                `$INSTANCE_NAME`_CSXPostScanApiPtr = &`$INSTANCE_NAME`_SsCSXPostMultiScanGanged;

            }
            else
        #endif
            {
                /*
                *  If no ganged sensor in the Component OR current widget contains no ganged sns, then:
                *    1. Find Rx pointer: Rx = Base address.
                *    2. Find Tx pointer: Tx = Base address + total Rx
                */
                `$INSTANCE_NAME`_curRxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                `$INSTANCE_NAME`_curTxIOPtr = `$INSTANCE_NAME`_curRxIOPtr;
                `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_curTxIOPtr[(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols)];

                /* Connect first Tx and first Rx IOs for scan */
                `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr);
                `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr);

                /* Set callback to scan all the sensors in widget */
                `$INSTANCE_NAME`_CSXPostScanApiPtr = &`$INSTANCE_NAME`_SsCSXPostMultiScan;
            }

            /* Reset multi-frequency scan channel if enabled */
            #if (`$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN == `$INSTANCE_NAME`_ENABLE)
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
            #endif

        /* Set scan status, enter critical section and initiate scan */
        `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;

        #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            #if(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL)
                Cy_SysLib_DelayUs(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US);
            #endif /* (`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL) */
        #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
        `$INSTANCE_NAME`_SsCSXStartSample();

    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXScanExt()
****************************************************************************//**
*
* \brief
*  Starts the CSX conversion on the preconfigured sensor. This function requires
*  using the `$INSTANCE_NAME`_CSXSetupWidgetExt() function to set up a
*  widget.
*
* \details
*  This function performs single scanning of one sensor in the widget configured
*  by the `$INSTANCE_NAME`_CSXSetupWidgetExt() function. It does the following
*  tasks:
*    1. Sets a busy flag in the `$INSTANCE_NAME`_dsRam structure.
*    2. Configures the Tx clock frequency.
*    3. Configures the Modulator clock frequency.
*    4. Configures the IDAC value.
*    5. Starts single scanning.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time or pipeline scanning for example). This
*  function is called when no scanning is in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  The sensor must be preconfigured by using the
*  `$INSTANCE_NAME`_CSXSetupWidgetExt() API prior to calling this function.
*  The sensor remains ready for the next scan if a previous scan was triggered
*  by using the `$INSTANCE_NAME`_CSXScanExt() function. In this case, calling
*  `$INSTANCE_NAME`_CSXSetupWidgetExt() is not required every time before the
*  `$INSTANCE_NAME`_CSXScanExt() function. If a previous scan was triggered in
*  any other way - `$INSTANCE_NAME`_Scan(), `$INSTANCE_NAME`_ScanAllWidgets()
*  or `$INSTANCE_NAME`_RunTuner() - (see the `$INSTANCE_NAME`_RunTuner() function
*  description for more details), the sensor must be preconfigured again by
*  using the `$INSTANCE_NAME`_CSXSetupWidgetExt() API prior to calling the
*  `$INSTANCE_NAME`_CSXScanExt() function.
*
*  If disconnection of the sensors is required after calling
*  `$INSTANCE_NAME`_CSXScanExt(), the `$INSTANCE_NAME`_CSXDisconnectTx() and
*  `$INSTANCE_NAME`_CSXDisconnectRx() APIs can be used.
*
*******************************************************************************/

void `$INSTANCE_NAME`_CSXScanExt(void)
{
    /* Reset multi-frequency scan channel if enabled */
    #if (`$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN == `$INSTANCE_NAME`_ENABLE)
        `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
    #endif

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        if (0u != `$INSTANCE_NAME`_curRamSnsPtr->subConvNum)
        {
            /* Set busy flag and start conversion */
            `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;

            #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                #if(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL)
                    Cy_SysLib_DelayUs(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US);
                #endif /* (`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL) */
            #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
            `$INSTANCE_NAME`_SsCSXStartSample();
        }
    #else
        /* Set busy flag and start conversion */
        `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;

        #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
            #if(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL)
                Cy_SysLib_DelayUs(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US);
            #endif /* (`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL) */
        #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */
        `$INSTANCE_NAME`_SsCSXStartSample();
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXPostMultiScan
****************************************************************************//**
*
* \brief
*   ISR function implements the multiple-sensor scanning for un-ganged CSX widgets.
*   This function is called by the Component ISR only, it should not be used by
*   the application layer.
*
*******************************************************************************/

static void `$INSTANCE_NAME`_SsCSXPostMultiScan(void)
{
    #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

    /* Copy scan result into sensor raw count array */
    `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex] = \
                             (`$INSTANCE_NAME`_csxScanPeriod - `$INSTANCE_NAME`_csxRawCount);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Increment multi frequency scan index if all channels are not scanned */
        if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 > `$INSTANCE_NAME`_scanFreqIndex)
        {
            /* Change multi-frequency channel and start sample */
            `$INSTANCE_NAME`_scanFreqIndex++;
            `$INSTANCE_NAME`_SsChangeClkFreq((uint32)`$INSTANCE_NAME`_scanFreqIndex);
            `$INSTANCE_NAME`_SsCSXStartSample();
        }
        else
    #endif
        {
            #if (`$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN == `$INSTANCE_NAME`_ENABLE)
                /* All channels are scanned. Reset the multi frequency scan channel */
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
                `$INSTANCE_NAME`_SsChangeClkFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_0);
            #endif

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
                /* Disconnect Tx/Rx electrodes of previously scanned sensor as preparation for next sensor scan */
                `$INSTANCE_NAME`_CSXDisconnectTx(`$INSTANCE_NAME`_curTxIOPtr);
                `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr);

                /* Increment sensor until non-skipped is found */
                do
                {
                    /* Increment sensor index to configure next sensor in widget */
                    `$INSTANCE_NAME`_sensorIndex++;

                    /* Increment sensor pointers */
                    `$INSTANCE_NAME`_curRamSnsPtr++;
                    `$INSTANCE_NAME`_curWdgtTotalTx--;
                    if (`$INSTANCE_NAME`_curWdgtTotalTx > 0u)
                    {
                        `$INSTANCE_NAME`_curTxIOPtr++;
                    }
                    else
                    {
                        `$INSTANCE_NAME`_curWdgtTotalRx--;
                        if (`$INSTANCE_NAME`_curWdgtTotalRx > 0u)
                        {
                            `$INSTANCE_NAME`_curRxIOPtr++;
                            `$INSTANCE_NAME`_curWdgtTotalTx  = `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
                            `$INSTANCE_NAME`_curTxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                            `$INSTANCE_NAME`_curTxIOPtr = & `$INSTANCE_NAME`_curTxIOPtr[(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols)];
                        }
                    }
                } while ((`$INSTANCE_NAME`_curWdgtTotalRx != 0u) && (`$INSTANCE_NAME`_curRamSnsPtr->subConvNum == 0u));

                /* Perform the next scan or switch to the next widget */
                if(`$INSTANCE_NAME`_curWdgtTotalRx != 0u)
                {
                    /* Connect Tx/Rx electrodes for the next scan */
                    `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr);
                    `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr);
                    /* Reset scan result holder, and initiate scan */
                    `$INSTANCE_NAME`_SsCSXStartSample();
                }
                else
                {
                    /* Call scan next widget API if requested, if not, complete scan */
                    if (`$INSTANCE_NAME`_requestScanAllWidget != 0u)
                    {
                        `$INSTANCE_NAME`_SsPostAllWidgetsScan();
                    }
                    else
                    {
                        `$INSTANCE_NAME`_dsRam.scanCounter++;
                        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
                    }
                }
            #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

                /*
                *  Disconnect Tx electrodes of previously scanned sensor as
                *  preparation for next sensor scan
                */
                `$INSTANCE_NAME`_CSXDisconnectTx (`$INSTANCE_NAME`_curTxIOPtr);

                /* Increment sensor index to configure next sensor in widget */
                `$INSTANCE_NAME`_sensorIndex++;

                /*
                *  Initiate scan for next sensor in widget, if all the sensors in
                *  widget are not scanned
                */
                `$INSTANCE_NAME`_curWdgtTotalTx--;
                if (`$INSTANCE_NAME`_curWdgtTotalTx > 0u)
                {
                    /*
                    *  1. Increment pointer to next Tx
                    *  2. Connect next Rx for scan
                    *  3. Increment pointer to sns data
                    */
                    `$INSTANCE_NAME`_curTxIOPtr++;
                    `$INSTANCE_NAME`_CSXConnectTx (`$INSTANCE_NAME`_curTxIOPtr);
                    `$INSTANCE_NAME`_curRamSnsPtr++;

                    /* Reset scan result holder, and initiate scan */
                    `$INSTANCE_NAME`_SsCSXStartSample();
                }

                /* Check if all Rx are looped through */
                else
                {
                    `$INSTANCE_NAME`_curWdgtTotalRx--;
                    if (`$INSTANCE_NAME`_curWdgtTotalRx > 0u)
                    {
                        /*
                        *  1. Disconnect current Rx electrode
                        *  2. Connect next Rx electrode
                        *  3. Re-initialize total Tx to be scanned per Rx
                        *  4. Find first Tx electrode again
                        *  5. Connect first Tx electrode
                        */
                        `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr);
                        `$INSTANCE_NAME`_curRxIOPtr++;
                        `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr);
                        `$INSTANCE_NAME`_curWdgtTotalTx  = `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
                        `$INSTANCE_NAME`_curTxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                        `$INSTANCE_NAME`_curTxIOPtr = & `$INSTANCE_NAME`_curTxIOPtr[(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols)];
                        `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr);

                        /* Increment RAM sensor pointer pointer */
                        `$INSTANCE_NAME`_curRamSnsPtr++;

                        /* Initiate sample */
                        `$INSTANCE_NAME`_SsCSXStartSample();
                    }
                    else
                    {
                        /* If all the sensors are scanned, disconnect Tx */
                        `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr);

                        /* Call scan next widget API if requested, if not, complete scan */
                        if (`$INSTANCE_NAME`_requestScanAllWidget != 0u)
                        {
                            `$INSTANCE_NAME`_SsPostAllWidgetsScan();
                        }
                        else
                        {
                            /*
                            *  All pending scans completed,
                            *    1. update the counter to indicat same
                            *    2. Clear busy state as scanning is completed
                            */
                            `$INSTANCE_NAME`_dsRam.scanCounter++;
                            `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
                        }
                    }
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
        }

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXPostMultiScanGanged
****************************************************************************//**
*
* \brief
*   The ISR function implements the multiple-sensor scanning for ganged CSX widgets.
*   This function is called by the Component ISR only, should not be used by
*   the application layer.
*
* \details
*   The ISR function implements the multiple-sensor scanning for ganged CSX widgets.
*   This function is called by the Component ISR only, should not be used by
*   the application layer.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_CSX_GANGED_SNS_EN == 1u)

static void `$INSTANCE_NAME`_SsCSXPostMultiScanGanged(void)
{
    uint32 numElectrodes;

    #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

    /* Copy scan result into sensor raw count array */
    `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex] = \
                    (`$INSTANCE_NAME`_csxScanPeriod - `$INSTANCE_NAME`_csxRawCount);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Increment multi frequency scan index if all channels are not scanned */
        if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 > `$INSTANCE_NAME`_scanFreqIndex)
        {
            /* Change multi-frequency channel and start sample */
            `$INSTANCE_NAME`_scanFreqIndex++;
            `$INSTANCE_NAME`_SsChangeClkFreq((uint32)`$INSTANCE_NAME`_scanFreqIndex);
            `$INSTANCE_NAME`_SsCSXStartSample();
        }
        else
    #endif
        {
            #if (`$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN == `$INSTANCE_NAME`_ENABLE)
                /* All channels are scanned. Reset the multi frequency scan channel */
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
                `$INSTANCE_NAME`_SsChangeClkFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_0);
            #endif

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
                /* Disconnect Tx electrodes of previously scanned sensor as preparation for next sensor scan */
                numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins;
                `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];
                do
                {
                    `$INSTANCE_NAME`_CSXDisconnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                    numElectrodes--;
                } while (0u != numElectrodes);
                /* Disconnect Rx electrodes of previously scanned sensor as preparation for next sensor scan */
                numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins;
                `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                do
                {
                    `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                    numElectrodes--;
                } while (0u != numElectrodes);

                /* Increment sensor until non-skipped is found */
                do
                {
                    /* Increment sensor index to configure next sensor in widget */
                    `$INSTANCE_NAME`_sensorIndex++;

                    /* Increment RAM sensor pointer */
                    `$INSTANCE_NAME`_curRamSnsPtr++;
                    `$INSTANCE_NAME`_curWdgtTotalTx--;
                    if (`$INSTANCE_NAME`_curWdgtTotalTx > 0u)
                    {
                        `$INSTANCE_NAME`_curGangTxPtr++;
                    }
                    else
                    {
                        /* Check if all Rx are scanned, if not, initiate scan for next Rx */
                        `$INSTANCE_NAME`_curWdgtTotalRx--;
                        if (`$INSTANCE_NAME`_curWdgtTotalRx > 0u)
                        {
                            `$INSTANCE_NAME`_curGangRxPtr++;
                            `$INSTANCE_NAME`_curWdgtTotalTx = `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
                            `$INSTANCE_NAME`_curGangTxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                            `$INSTANCE_NAME`_curGangTxPtr += `$INSTANCE_NAME`_curFlashWdgtPtr->numCols;
                        }
                    }
                } while ((`$INSTANCE_NAME`_curWdgtTotalRx != 0u) && (`$INSTANCE_NAME`_curRamSnsPtr->subConvNum == 0u));

                if(`$INSTANCE_NAME`_curWdgtTotalRx != 0u)
                {
                    /* Connect Tx electrodes for the next scan */
                    numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins;
                    `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];
                    do
                    {
                        `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                        numElectrodes--;
                    } while (0u != numElectrodes);
                    /* Connect Tx electrodes for the next scan */
                    numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins ;
                    `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                    do
                    {
                        `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                        numElectrodes--;
                    } while (0u != numElectrodes);
                    /* Reset scan result holder, and initiate scan */
                    `$INSTANCE_NAME`_SsCSXStartSample();
                }
                else
                {
                    /* Call scan next widget API if requested, if not, complete scan */
                    if (`$INSTANCE_NAME`_requestScanAllWidget != 0u)
                    {
                        `$INSTANCE_NAME`_SsPostAllWidgetsScan();
                    }
                    else
                    {
                        `$INSTANCE_NAME`_dsRam.scanCounter++;
                        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
                    }
                }
            #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

                /* Disconnect ALL pins of previously scanned Tx */
                numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins ;
                `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];
                do
                {
                    `$INSTANCE_NAME`_CSXDisconnectTx (`$INSTANCE_NAME`_curTxIOPtr++);
                    numElectrodes--;
                } while (0u != numElectrodes);

                /* Increment sensor index to configure next sensor in widget */
                `$INSTANCE_NAME`_sensorIndex++;

                /* Check if all Tx are scanned, if not, initiate scan for next Tx */
                `$INSTANCE_NAME`_curWdgtTotalTx--;
                if (`$INSTANCE_NAME`_curWdgtTotalTx > 0u)
                {
                    /*
                    *  1. Find pointer of next Tx (ganged)
                    *  2. Connect all Tx pins
                    */
                    `$INSTANCE_NAME`_curGangTxPtr++;
                    numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins ;
                    `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];
                    do
                    {
                        `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                        numElectrodes--;
                    } while (0u != numElectrodes);

                    /* Increment RAM pointer to next sensor */
                    `$INSTANCE_NAME`_curRamSnsPtr++;

                    /* Reset scan result holder and initiate scan */
                    `$INSTANCE_NAME`_SsCSXStartSample();
                }
                else
                {
                    /* Check if all Rx are scanned, if not, initiate scan for next Rx */
                    `$INSTANCE_NAME`_curWdgtTotalRx--;
                    if (`$INSTANCE_NAME`_curWdgtTotalRx > 0u)
                    {
                        /* 1. Disconnect current Rx ALL pins */
                        numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins ;
                        `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                        do
                        {
                            `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                            numElectrodes--;
                        } while (0u != numElectrodes);

                        /* 2. Connect next Rx ALL pins */
                        `$INSTANCE_NAME`_curGangRxPtr++;
                        numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins ;
                        `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                        do
                        {
                            `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                            numElectrodes--;
                        } while (0u != numElectrodes);

                        /*
                        *  3. Re-initialize total Tx to be scanned per Rx
                        *  4. Find first Tx  again
                        *  5. Connect first Tx ALL pins
                        */
                        `$INSTANCE_NAME`_curWdgtTotalTx = `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
                        `$INSTANCE_NAME`_curGangTxPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
                        `$INSTANCE_NAME`_curGangTxPtr += `$INSTANCE_NAME`_curFlashWdgtPtr->numCols;

                        /* 6. Connect Tx ALL pins */
                        numElectrodes = `$INSTANCE_NAME`_curGangTxPtr->numPins ;
                        `$INSTANCE_NAME`_curTxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangTxPtr->firstPinId];
                        do
                        {
                            `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_curTxIOPtr++);
                            numElectrodes--;
                        } while (0u != numElectrodes);

                        /* Increment RAM pointer to next sensor */
                        `$INSTANCE_NAME`_curRamSnsPtr++;

                        /* Reset scan result holder and initiate scan */
                        `$INSTANCE_NAME`_SsCSXStartSample();
                    }
                    else
                    {
                        /* Disconnect ALL electrodes of previously scanned Rx */
                        numElectrodes = `$INSTANCE_NAME`_curGangRxPtr->numPins ;
                        `$INSTANCE_NAME`_curRxIOPtr = &`$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_curGangRxPtr->firstPinId];
                        do
                        {
                            `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_curRxIOPtr++);
                            numElectrodes--;
                        } while (0u != numElectrodes);

                        /* Call scan next widget API if requested, if not, complete scan */
                        if (`$INSTANCE_NAME`_requestScanAllWidget != 0u)
                        {
                            `$INSTANCE_NAME`_SsPostAllWidgetsScan();
                        }
                        else
                        {
                            /*
                            *  All pending scans completed,
                            *    1. update the counter to indicate same
                            *    2. Clear busy state as scanning is completed
                            */
                            `$INSTANCE_NAME`_dsRam.scanCounter++;
                            `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
                        }
                    }
                }
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
        }

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
}

#endif  /* (`$INSTANCE_NAME`_CSX_GANGED_SNS_EN == 1u) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXPostSingleScan
****************************************************************************//**
*
* \brief
*   The ISR function for single-sensor scanning implementation.
*
* \details
*   This function is used by `$INSTANCE_NAME` ISR in the CSX scanning mode to implement
*   the single-sensor scanning.
*   This function should not be used by the application layer.
*
*******************************************************************************/

static void `$INSTANCE_NAME`_SsCSXPostSingleScan(void)
{
    #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

    /*
    * Copy scan result into sensor raw count array and clear busy flag
    *    No sensor is connected or disconnected in this function
    *    Calling `$INSTANCE_NAME`_ScanExt from application would perform
    *    one more scan of same sensor. Specifically for low-power mode.
    */
    `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex] =
                        (`$INSTANCE_NAME`_csxScanPeriod - `$INSTANCE_NAME`_csxRawCount);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        /* Increment multi frequency scan index if all channels are not scanned */
        if (`$INSTANCE_NAME`_FREQ_CHANNEL_2 > `$INSTANCE_NAME`_scanFreqIndex)
        {
            /* Change multi-frequency channel and start sample */
            `$INSTANCE_NAME`_scanFreqIndex++;
            `$INSTANCE_NAME`_SsChangeClkFreq((uint32)`$INSTANCE_NAME`_scanFreqIndex);
            `$INSTANCE_NAME`_SsCSXStartSample();
        }
        else
    #endif
        {
            #if (`$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN == `$INSTANCE_NAME`_ENABLE)
                /* All channels are scanned. Reset the multi frequency scan channel */
                `$INSTANCE_NAME`_scanFreqIndex = `$INSTANCE_NAME`_FREQ_CHANNEL_0;
                `$INSTANCE_NAME`_SsChangeClkFreq(`$INSTANCE_NAME`_FREQ_CHANNEL_0);
            #endif
            /*
            * All pending scans completed,
            *   1. Update the counter to indicate same
            *   2. Clear busy state as scanning is completed
            */
            `$INSTANCE_NAME`_dsRam.scanCounter++;
            `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
        }

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXCalibrateWidget
****************************************************************************//**
*
* \brief
*  Calibrates the raw count values of all the sensors/nodes in a CSX widget.
*
* \details
*  Performs a successive approximation search algorithm to find appropriate
*  IDAC values for sensors in the specified widget that provides a raw count
*  to the level specified by the target parameter.
*
*  This function is available when the CSX Enable IDAC auto-calibration
*  parameter is enabled.
*
* \param widgetId
*  Specifies the ID number of the CSX widget to calibrate its raw count.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param target
*  Specifies the calibration target in percentages of the maximum raw count.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN)

void `$INSTANCE_NAME`_CSXCalibrateWidget(uint32 widgetId, uint16 target)
{
    /* Variable to calculate raw count target */
    uint32 rawTarget;
    /* Counter for loop execution */
    uint32 totalSns;
    /* Counter for loop execution */
    uint32 calibrationIndex;

    /* Currently used IDAC-bit */
    uint8 curIdacMask = (1u << (`$INSTANCE_NAME`_CSX_IDAC_BITS_USED-1u));
    /* Next used IDAC-bit */
    uint8 nextIdacMask = (curIdacMask >> 1u);

    /* initialize ptr to sensor structures */
    `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam;

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        /* Calculate target raw count */
        `$INSTANCE_NAME`_csxScanPeriod  = `$INSTANCE_NAME`_SsCalcCsxScanPeriod(
            (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam);
        rawTarget = `$INSTANCE_NAME`_csxScanPeriod;
        rawTarget = (rawTarget * target) / `$INSTANCE_NAME`_PERCENTAGE_100;
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

    if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E ==
       `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
    {
        /* Find out total sensors/nodes in widget */
        totalSns = ((uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols *
                    (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numRows);

        /* Clear raw count registers and IDAC registers of all the sensors/nodes */
        for (calibrationIndex = 0u; calibrationIndex < totalSns; calibrationIndex++)
        {
            `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_0] = 0u;
            `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_0] = curIdacMask;
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = 0u;
                `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = 0u;
                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = curIdacMask;
                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = curIdacMask;
            #endif
            `$INSTANCE_NAME`_curRamSnsPtr++;
        }

        /* Perform binary search for accurate IDAC value for each sensor/node */
        do
        {
            /* Scan all the sensors/nodes in widget */
            (void)`$INSTANCE_NAME`_SetupWidget(widgetId);
            (void)`$INSTANCE_NAME`_Scan();

            while ((`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY) != 0u)
            {
            }

            /* Get access to sensor data */
            `$INSTANCE_NAME`_curRamSnsPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam;

            /* Check raw count and adjust IDAC, loop through all the sensors/nodes */
            for (calibrationIndex = 0u; calibrationIndex < totalSns; calibrationIndex++)
            {
                /* Calculate raw count target for specified node */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
                    rawTarget = (`$INSTANCE_NAME`_SsCSXOversample() * target) / `$INSTANCE_NAME`_PERCENTAGE_100;
                #endif

                /* Check if current raw count is above target,
                *   if yes, clear the MS bit of bit
                *   if no, keep the MS bit and set next bit
                */
                if (`$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_0] > rawTarget)
                {
                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_0] &= (uint8)(~curIdacMask);
                }
                `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_0] |= nextIdacMask;

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    if (`$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_1] > rawTarget)
                    {
                        `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] &= (uint8)(~curIdacMask);
                    }

                    if (`$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_FREQ_CHANNEL_2] > rawTarget)
                    {
                        `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] &= (uint8)(~curIdacMask);
                    }

                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_1] |= nextIdacMask;
                    `$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_FREQ_CHANNEL_2] |= nextIdacMask;
                #endif
                `$INSTANCE_NAME`_curRamSnsPtr++;
            }

            /* Shift both current idac and pre Idac values to right by 1 */
            curIdacMask = nextIdacMask;
            nextIdacMask = nextIdacMask >> 1u;
        }
        while (curIdacMask != 0u);
    }
}

#endif /* (`$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXStartSample
****************************************************************************//**
*
* \brief
*   Starts scanning for the CSX widget.
*
* \details
*   Starts scanning for the CSX widget.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsCSXStartSample(void)
{
    uint32 tmpRegVal;

    tmpRegVal = (uint32)`$INSTANCE_NAME`_curRamSnsPtr->idacComp[`$INSTANCE_NAME`_scanFreqIndex];
    tmpRegVal = (tmpRegVal & `$INSTANCE_NAME`_CSD_IDACA_VAL_MSK) | `$INSTANCE_NAME`_DEFAULT_CSD_IDACA_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACA_PTR, tmpRegVal);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
        /* Configure node-specific number of sub-conversion */
        `$INSTANCE_NAME`_csxScanPeriod = (uint16)`$INSTANCE_NAME`_SsCSXOversample();
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_NORM_CNT_PTR, (uint32)`$INSTANCE_NAME`_curRamSnsPtr->subConvNum);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

    /* Clear scan result holder */
    `$INSTANCE_NAME`_csxRawCount = 0u;

    #ifdef `$INSTANCE_NAME`_START_SAMPLE_CALLBACK
        `$INSTANCE_NAME`_StartSampleCallback(`$INSTANCE_NAME`_widgetIndex, `$INSTANCE_NAME`_sensorIndex);
    #endif /* `$INSTANCE_NAME`_START_SAMPLE_CALLBACK */

    `$INSTANCE_NAME`_SsCSXStartSampleExt();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXConnectTx
****************************************************************************//**
*
* \brief
*  Connects a Tx electrode to the CSX scanning hardware.
*
* \details
*  This function connects a port pin (Tx electrode) to the CSD_SENSE signal.
*  It is assumed that drive mode of the port pin is already set to STRONG
*  in the HSIOM_PORT_SELx register.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time when there is only one port pin for an
*  electrode for example).
*
* \param txPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  to be connected to the sensing HW block as a Tx pin.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXConnectTx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *txPtr)
{
    uint32 interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();

    Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)txPtr->pcPtr, (uint32)txPtr->pinNumber, CY_GPIO_DM_STRONG_IN_OFF);
    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)txPtr->pcPtr, (uint32)txPtr->pinNumber, (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD);

    Cy_SysLib_ExitCriticalSection(interruptState);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXConnectRx
****************************************************************************//**
*
* \brief
*  Connects an Rx electrode to the CSX scanning hardware.
*
* \details
*  This function connects a port pin (Rx electrode) to AMUXBUS-A and sets
*  drive mode of the port pin to High-Z in the GPIO_PRT_PCx register.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time when there is only one port pin for an
*  electrode for example).
*
* \param rxPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  to be connected to the sensing HW block as an Rx pin.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXConnectRx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *rxPtr)
{
    uint32 interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();

    Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)rxPtr->pcPtr, (uint32)rxPtr->pinNumber, CY_GPIO_DM_ANALOG);
    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)rxPtr->pcPtr, (uint32)rxPtr->pinNumber, (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_AMUXA);

    Cy_SysLib_ExitCriticalSection(interruptState);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXDisconnectTx
****************************************************************************//**
*
* \brief
*  Disconnects a Tx electrode from the CSX scanning hardware.
*
* \details
*  This function disconnects a port pin (Tx electrode) from the CSD_SENSE
*  signal and configures the port pin to the strong drive mode. It is assumed
*  that the data register (GPIO_PRTx_DR) of the port pin is already 0.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time when there is only one port pin for an
*  electrode for example).
*
* \param txPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to a Tx pin
*  sensor to be disconnected from the sensing HW block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXDisconnectTx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *txPtr)
{
    uint32 interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)txPtr->pcPtr, (uint32)txPtr->pinNumber, (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);
    Cy_SysLib_ExitCriticalSection(interruptState);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXDisconnectRx
****************************************************************************//**
*
* \brief
*  Disconnects an Rx electrode from the CSX scanning hardware.
*
* \details
*  This function disconnects a port pin (Rx electrode) from AMUXBUS_A and
*  configures the port pin to the strong drive mode. It is assumed that the
*  data register (GPIO_PRTx_DR) of the port pin is already 0.
*
*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the user's specific
*  use cases (for faster execution time when there is only one port pin for
*  an electrode for example).
*
* \param rxPtr
*  Specifies the pointer to the FLASH_IO_STRUCT object belonging to an Rx pin
*  sensor to be disconnected from the sensing HW block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXDisconnectRx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *rxPtr)
{
    uint32  interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();

    Cy_GPIO_SetHSIOM((GPIO_PRT_Type*)rxPtr->pcPtr, (uint32)rxPtr->pinNumber, (en_hsiom_sel_t)`$INSTANCE_NAME`_HSIOM_SEL_GPIO);
    Cy_GPIO_SetDrivemode((GPIO_PRT_Type*)rxPtr->pcPtr, (uint32)rxPtr->pinNumber, CY_GPIO_DM_STRONG_IN_OFF);
    Cy_GPIO_Clr((GPIO_PRT_Type*)rxPtr->pcPtr, (uint32)rxPtr->pinNumber);

    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXGetTxClkDivider
****************************************************************************//**
*
* \brief
*  This function gets the Sense Clock Divider value for one-dimension widgets
*  and the Column Sense Clock divider value for two-dimension widgets.
*
* \details
*  This function gets the Sense Clock Divider value based on the Component
*  configuration. The function is applicable for one-dimension widgets and for
*  two-dimension widgets.
*
* \param
*  widgetId Specifies the ID of the widget.
*
* \return The Sense Clock Divider value for one-dimension widgets
*         and the Column Sense Clock divider value for two-dimension widgets.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SsCSXGetTxClkDivider(uint32 widgetId)
{
    uint32 retVal;

    /* Get sense divider based on configuration */
    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
        `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

        retVal = (uint32)(ptrWdgt->snsClk);
    #else
        retVal = (uint32)`$INSTANCE_NAME`_dsRam.snsCsxClk;
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) */

    if(widgetId == 0uL)
    {
        ;
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCalcCsxScanPeriod
****************************************************************************//**
*
* \brief
*  Calculates scan period for a desired CSX widget.
*
* \details
*  This function calculates a scan period for a desired CSX widget considering
*  common TX clock option.
*
* \param wdgtPtr
*  The pointer to a register map object that contains widget information.
*
* \return
*  Returns the CSX scan period for the widget.
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_SsCalcCsxScanPeriod(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *wdgtPtr)
{
    uint32 temp;

    #if(`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
        temp = (uint32)(wdgtPtr->snsClk);
    #else
        temp = (uint32)(`$INSTANCE_NAME`_dsRam.snsCsxClk);
    #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) */

    temp = CY_LO16((uint32)wdgtPtr->resolution * (temp - `$INSTANCE_NAME`_CSX_DEADBAND_CYCLES_NUMBER));

    /* return the scan period */
    return ((uint16)temp);
}


/**
* \cond SECTION_CYSENSE_INTERRUPT
* \addtogroup group_cysense_interrupt
* \{
*/
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CSXScanISR
****************************************************************************//**
*
* \brief
*  This is an internal ISR function to handle the CSX sensing method operation.
*
* \details
*  This handler covers the following functionality:
*   - Read the result of the measurement and store it into the corresponding register of
*     the data structure.
*   - If the Noise Metric functionality is enabled, then check the number of bad
*     conversions and repeat the scan of the current sensor of the number of bad
*     conversions is greater than the Noise Metric Threshold.
*   - Initiate the scan of the next sensor for multiple sensor scanning mode.
*   - Update the Status register in the data structure.
*   - Switch the HW IP block to the default state if scanning of all the sensors is
*     completed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_CSXScanISR(void)
{
    uint32 tmpRawCount;

    #if(0u != `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN)
        uint32 tmpRegVal;
    #endif /* (0u != `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN) */

    #if(0u != `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN)
        static uint32 `$INSTANCE_NAME`_resamplingCyclesCnt = `$INSTANCE_NAME`_RESAMPLING_CYCLES_MAX_NUMBER;
    #endif /* (0u != `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN) */

    /* Disable interrupt */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        NVIC_DisableIRQ(`$INSTANCE_NAME`_ISR_cfg.intrSrc);
    #endif

    /* Clear all pending interrupts of CSD block */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

    tmpRawCount  = (uint16)(`$INSTANCE_NAME`_CSD_RESULT_VAL1_REG &
                                             `$INSTANCE_NAME`_CSD_RESULT_VAL1_VALUE_MSK);

    tmpRawCount += (uint16)(`$INSTANCE_NAME`_CSD_RESULT_VAL2_REG &
                                             `$INSTANCE_NAME`_CSD_RESULT_VAL2_VALUE_MSK);

    /* This workaround neded to prevent overflow in the SW register map. Cypress ID #234358 */
    if(tmpRawCount > (uint32)`$INSTANCE_NAME`_csxScanPeriod)
    {
        `$INSTANCE_NAME`_csxRawCount = `$INSTANCE_NAME`_csxScanPeriod;
    }
    else
    {
        `$INSTANCE_NAME`_csxRawCount = (uint16)tmpRawCount;
    }

    #if(0u != `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN)
        tmpRegVal = CY_GET_REG32(`$INSTANCE_NAME`_CSD_RESULT_VAL1_PTR) >> `$INSTANCE_NAME`_CSD_RESULT_VAL1_BAD_CONVS_POS;

        if((tmpRegVal > `$INSTANCE_NAME`_CSX_NOISE_METRIC_TH) && (`$INSTANCE_NAME`_resamplingCyclesCnt > 0uL))
        {
            CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_SCAN_CSD_SEQ_START_CFG);
            `$INSTANCE_NAME`_resamplingCyclesCnt--;
        }
        else
        {
            `$INSTANCE_NAME`_CSXPostScanApiPtr();
            `$INSTANCE_NAME`_resamplingCyclesCnt = `$INSTANCE_NAME`_RESAMPLING_CYCLES_MAX_NUMBER;
        }
    #else
        `$INSTANCE_NAME`_CSXPostScanApiPtr();
    #endif /* (0u != `$INSTANCE_NAME`_CSX_NOISE_METRIC_EN) */

    if(`$INSTANCE_NAME`_NOT_BUSY == (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY))
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_CSDCMP_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_IDACA_PTR,  `$INSTANCE_NAME`_DEFAULT_CSD_IDACA_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_IO_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_IO_SEL_CFG);
    }

    /* Enable interrupt */
    #if defined(`$INSTANCE_NAME`_ISR__INTC_ASSIGNED)
        NVIC_EnableIRQ(`$INSTANCE_NAME`_ISR_cfg.intrSrc);
    #endif
}
/** \}
* \endcond */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXStartSampleExt
****************************************************************************//**
*
* \brief
*   Starts the HW sequencer to perform the CSX conversion.
*   specific widget.
*
* \details
*   This function covers the following functionality:
*      1. Configures the HW sequencer to perform the coarse initialization.
*      2. Waiting for completion of the coarse initialization.
*      3. Configures the HW sequencer to perform the normal conversion.
*      4. Starts the normal conversion
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_SsCSXStartSampleExt(void)
{
    uint32 filterDelay;
    uint32 watchdogCounter;
    #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_CLK_PERICLK__HZ)
        uint32 sampleClkFreqHz;
    #endif /* (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_CLK_PERICLK__HZ) */

    /* Configure the HW sequencer to perform the coarse initialization. */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR,           `$INSTANCE_NAME`_DEFAULT_CSD_CONFIG_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR,            `$INSTANCE_NAME`_PRECHARGE_CSD_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_PRECHARGE_CSD_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_PRECHARGE_CSD_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_PRECHARGE_CSD_SW_DSI_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_PRECHARGE_CSD_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR,    `$INSTANCE_NAME`_PRECHARGE_CSD_SW_FW_MOD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_PRECHARGE_CSD_SW_FW_TANK_SEL_CFG);

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_RES_PTR,           `$INSTANCE_NAME`_PRECHARGE_CSD_SW_RES_CFG);

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
        #if(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL)
            Cy_SysLib_DelayUs(`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US);
        #endif /* (`$INSTANCE_NAME`_CSX_ANALOG_STARTUP_DELAY_US > 0uL) */
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR,        `$INSTANCE_NAME`_PRECHARGE_CSD_SEQ_START_CFG);

    /* Wait for the HSCMP trigger and retutn the sequencer to the IDLE state. */
    watchdogCounter = `$INSTANCE_NAME`_CSX_PRECHARGE_WATCHDOG_CYCLES_NUM;
    while((0u != (`$INSTANCE_NAME`_CSD_SEQ_START_START_MSK & CY_GET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR))) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    }

    /* Reset the sequencer to the IDLE state if HSCMP not triggered till watchdog period is out. */
    if(0u != (`$INSTANCE_NAME`_CSD_SEQ_START_START_MSK & CY_GET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR)))
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR,  `$INSTANCE_NAME`_DEFAULT_CSD_SEQ_START_CFG);
    }

    #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_CLK_PERICLK__HZ)
        sampleClkFreqHz = CYDEV_CLK_PERICLK__HZ / (uint32)`$INSTANCE_NAME`_dsRam.modCsxClk;
        if(sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
        {
            filterDelay = `$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_12MHZ;
        }
        else if(sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
        {
            filterDelay = `$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_24MHZ;
        }
        else
        {
            filterDelay = `$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_48MHZ;
        }
    #else
        filterDelay = `$INSTANCE_NAME`_CSD_CONFIG_FILTER_DELAY_12MHZ;
    #endif /* (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_CLK_PERICLK__HZ) */

    /* Configure the HW sequencer to perform the normal conversion. */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CONFIG_PTR, `$INSTANCE_NAME`_PRESCAN_CSD_CONFIG_CFG | filterDelay);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_CSDCMP_PTR, `$INSTANCE_NAME`_PRESCAN_CSD_CSDCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_HSCMP_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_P_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_HS_N_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_DSI_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_DSI_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_SHIELD_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_MOD_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_FW_MOD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_FW_TANK_SEL_PTR, `$INSTANCE_NAME`_DEFAULT_CSD_SW_FW_TANK_SEL_CFG);

    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SW_RES_PTR, `$INSTANCE_NAME`_SCAN_CSD_SW_RES_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_IO_SEL_PTR, `$INSTANCE_NAME`_SCAN_CSD_SW_IO_SEL_CFG);

    /* Clear all pending interrupts of CSD block */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR, `$INSTANCE_NAME`_CSD_INTR_ALL_MSK);
    (void)CY_GET_REG32(`$INSTANCE_NAME`_CSD_INTR_PTR);

    /* Start the normal conversion. */
    CY_SET_REG32(`$INSTANCE_NAME`_CSD_SEQ_START_PTR, `$INSTANCE_NAME`_SCAN_CSD_SEQ_START_CFG);
}

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSXOversample
****************************************************************************//**
*
* \brief
*   Calculates the scan period of specific node.
*
* \details
*   Calculates the scan period of specific node that is used as maximum
*   raw count at raw count inversion (`$INSTANCE_NAME`_csxScanPeriod variable).
*   The `$INSTANCE_NAME`_curFlashWdgtPtr and `$INSTANCE_NAME`_curRamSnsPtr
*   must be configured to proper widget/sensor before calling this function.
*
* \return
*   Returns the scan period of specific node (used as maximum raw count)
*
*******************************************************************************/
static uint32 `$INSTANCE_NAME`_SsCSXOversample(void)
{
    uint32 result;
    #if(`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * curRamWdgtBasePtr;
    #endif

    /* Find scan period */
    #if(`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
        curRamWdgtBasePtr = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2WdgtRam;
        result = ((uint32)`$INSTANCE_NAME`_curRamSnsPtr->subConvNum *
            ((uint32)curRamWdgtBasePtr->snsClk - `$INSTANCE_NAME`_CSX_DEADBAND_CYCLES_NUMBER));
    #else
        result = ((uint32)`$INSTANCE_NAME`_curRamSnsPtr->subConvNum *
            ((uint32)`$INSTANCE_NAME`_dsRam.snsCsxClk - `$INSTANCE_NAME`_CSX_DEADBAND_CYCLES_NUMBER));
    #endif

    return result;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */

#endif  /* (0u != `$INSTANCE_NAME`_CSX_EN) */


/* [] END OF FILE */
