/***************************************************************************//**
* \file `$INSTANCE_NAME`_Sensing.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file contains the source of functions common for
*   different sensing methods.
*
* \see CapSense P4 v`$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION` Datasheet
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

#include "cyfitter.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

/***************************************
* API Constants
***************************************/

#define `$INSTANCE_NAME`_WIDGET_NUM_32                          (32u)
#define `$INSTANCE_NAME`_WIDGET_NUM_32_DIV_SHIFT                (5u)
#define `$INSTANCE_NAME`_WIDGET_NUM_32_MASK                     (0x0000001FLu)
#define `$INSTANCE_NAME`_CALIBRATION_RESOLUTION                 (12u)
#define `$INSTANCE_NAME`_COARSE_TRIM_THRESHOLD_1                (40u)
#define `$INSTANCE_NAME`_COARSE_TRIM_THRESHOLD_2                (215u)
#define `$INSTANCE_NAME`_FREQUENCY_OFFSET_5                     (20u)
#define `$INSTANCE_NAME`_FREQUENCY_OFFSET_10                    (40u)
#define `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ                   (1500u)
#define `$INSTANCE_NAME`_CALIBRATION_MD                         (2u)
#define `$INSTANCE_NAME`_MIN_IMO_FREQ_KHZ                       (6000u)
#define `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL                 (`$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL)
#define `$INSTANCE_NAME`_CP_MIN                                 (0u)
#define `$INSTANCE_NAME`_CP_MAX                                 (65000Lu)
#define `$INSTANCE_NAME`_CP_ERROR                               (4000Lu)
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    #define `$INSTANCE_NAME`_TOTAL_SLOTS                        (`$INSTANCE_NAME`_TOTAL_SCAN_SLOTS)
#else
    #define `$INSTANCE_NAME`_TOTAL_SLOTS                        (`$INSTANCE_NAME`_TOTAL_WIDGETS)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

#define `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET           (4u)

#if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
        #define `$INSTANCE_NAME`_PRS_FACTOR_DIV                 (2u)
    #else
        #define `$INSTANCE_NAME`_PRS_FACTOR_DIV                 (1u)
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
#else
    #define `$INSTANCE_NAME`_PRS_FACTOR_DIV                     (0u)
#endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

#define `$INSTANCE_NAME`_FLIP_FLOP_DIV                          (1u)

#define `$INSTANCE_NAME`_MOD_CSD_CLK_12000KHZ                   (12000uL)
#define `$INSTANCE_NAME`_MOD_CSD_CLK_24000KHZ                   (24000uL)
#define `$INSTANCE_NAME`_MOD_CSD_CLK_48000KHZ                   (48000uL)

#if ((`$INSTANCE_NAME`_CLK_SOURCE_PRS8 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) || \
    (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) || \
    (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
    #define `$INSTANCE_NAME`_FACTOR_FILTER_DELAY_12MHZ          (2u)
#else
    #define `$INSTANCE_NAME`_FACTOR_FILTER_DELAY_12MHZ          (4u)
#endif /* (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT != `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

#define `$INSTANCE_NAME`_FACTOR_MOD_SNS                         (8u)
#define `$INSTANCE_NAME`_UINT8_MAX_VAL                          (0xFFu)
#define `$INSTANCE_NAME`_MSB_OFFSET                             (8u)

/*****************************************************************************/
/* Enumeration types definition                                               */
/*****************************************************************************/

typedef enum
{
    `$INSTANCE_NAME`_RES_PULLUP_E   = 0x02u,
    `$INSTANCE_NAME`_RES_PULLDOWN_E = 0x03u
} `$INSTANCE_NAME`_PORT_TEST_DM;

typedef enum
{
    `$INSTANCE_NAME`_STS_RESET      = 0x01u,
    `$INSTANCE_NAME`_STS_NO_RESET   = 0x02u
} `$INSTANCE_NAME`_TEST_TYPE;


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \if SECTION_CAPSENSE_INTERNAL
* \addtogroup group_capsense_internal
* \{
*/

#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
    static void `$INSTANCE_NAME`_SsTrimIdacs(void);
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG))
        static void `$INSTANCE_NAME`_SsTrimIdacsSinking(void);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG))
        static void `$INSTANCE_NAME`_SsTrimIdacsSourcing(void);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        static void `$INSTANCE_NAME`_SsCSDDisableMode(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        static void `$INSTANCE_NAME`_SsDisableCSXMode(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)) */
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        static void `$INSTANCE_NAME`_SsSetCSD0DirectClockMode(void);
        static void `$INSTANCE_NAME`_SsSetCSD1DirectClockMode(void);
    #else
        static void `$INSTANCE_NAME`_SsSetDirectClockMode(void);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

#if(((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)))
    static CY_INLINE uint8 `$INSTANCE_NAME`_SsCalcLfsrSize(uint32 snsClkDivider, uint32 conversionsNum);
    static CY_INLINE uint8 `$INSTANCE_NAME`_SsCalcLfsrScale(uint32 snsClkDivider, uint8 lfsrSize);
#endif /* (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
            (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)) ||\
           ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
            (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))) */
#if ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) && \
    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))
    static void `$INSTANCE_NAME`_SsSetEqualSlotClock(void);
#endif /* ((`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)) */
#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))
    static void `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(uint32 wdgtIndex, `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * ptrWdgt);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
    static void `$INSTANCE_NAME`_SsSetWidgetTxClkSrc(uint32 wdgtIndex, `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * ptrWdgt);
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)) */

/** \}
* \endif */

/*******************************************************************************
* Define module variables
*******************************************************************************/

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))
    `$INSTANCE_NAME`_SENSE_METHOD_ENUM `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_UNDEFINED_E;
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))) */

#if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    /*  Module variable keep track of frequency hopping channel index   */
    uint8 `$INSTANCE_NAME`_scanFreqIndex = 0u;
    /*  Variable keep frequency offsets */
    uint8 `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_NUM_SCAN_FREQS] = {0u, 0u, 0u};
#else
    /* const allows C-compiler to do optimization */
    const uint8 `$INSTANCE_NAME`_scanFreqIndex = 0u;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

/* Global software variables */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    volatile uint8 `$INSTANCE_NAME`_widgetIndex0 = 0u;    /* Index of the scanning widget0 */
    volatile uint8 `$INSTANCE_NAME`_sensorIndex0 = 0u;    /* Index of the scanning sensor0 */
    volatile uint8 `$INSTANCE_NAME`_widgetIndex1 = 0u;    /* Index of the scanning widget1 */
    volatile uint8 `$INSTANCE_NAME`_sensorIndex1 = 0u;    /* Index of the scanning sensor1 */
#else
    volatile uint8 `$INSTANCE_NAME`_widgetIndex = 0u;    /* Index of the scanning widget */
    volatile uint8 `$INSTANCE_NAME`_sensorIndex = 0u;    /* Index of the scanning sensor */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
uint8 `$INSTANCE_NAME`_requestScanAllWidget = 0u;
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    uint8 `$INSTANCE_NAME`_prescalersTuningDone = 0u;
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */

/* Pointer to RAM_SNS_STRUCT structure  */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr0;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr1;
#else
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN))
    /*  Pointer to Flash structure holding configuration of widget to be scanned  */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
         `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr0 = 0u;
         `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr1 = 0u;
    #else
         `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr = 0u;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN))  */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
    /*  Pointer to Flash structure holding info of sensor to be scanned  */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr0 = 0u;
        `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr1 = 0u;
    #else
        `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr = 0u;
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
/*  Pointer to Flash structure to hold Sns electrode that was connected previously  */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr0;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr1;
#else
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusy
****************************************************************************//**
*
* \brief
*  Returns the current status of the component (scan completed or scan in
*  progress).
*
* \details
*  This function returns the status of the hardware block whether a scan is
*  currently in progress or not. If the component is busy, no new scan or setup
*  widgets should be made. It is recommended using the critical section (i.e.
*  disable global interrupt) in the application when the device transitions from
*  the active mode to sleep or deep sleep mode.
*
* \return
*  Returns the current status of the component:
*    - `$INSTANCE_NAME`_NOT_BUSY if there is no scan in progress and a next scan
*      can be initiated.
*    - `$INSTANCE_NAME`_SW_STS_BUSY if the previous scanning is not completed
*      and the hardware block is busy.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsBusy(void)
{
    return ((*(volatile uint32 *)&`$INSTANCE_NAME`_dsRam.status) & `$INSTANCE_NAME`_SW_STS_BUSY);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetupWidget
****************************************************************************//**
*
* \brief
*  Performs the initialization required to scan the specified widget.
*
* \details
*  This function prepares the component to scan all sensors in the specified
*  widget, by executing the following tasks.
*    1. Re-initialize the hardware if it is not configured to perform the
*       sensing method used by the specified widget, this happens only if the
*       CSD and CSX methods are used in the component.
*    2. Initialize the hardware with specific sensing configuration (e.g.
*       sensor clock, scan resolution) used by the widget.
*    3. Disconnect all previously connected electrodes, if the electrodes
*       connected by the `$INSTANCE_NAME`_CSDSetupWidgetExt(),
*       `$INSTANCE_NAME`_CSXSetupWidgetExt() or `$INSTANCE_NAME`_CSDConnectSns()
*       functions and not disconnected.
*
*  This function does not start sensor scanning, the `$INSTANCE_NAME`_Scan()
*  function must be called to start the scan sensors in the widget. If this
*  function is called more than once, it does not break the component operation,
*  but only the last initialized widget is in effect.

*
* \param widgetId
*  Specify the ID number of the widget to be initialized for scanning.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID
*
* \return
*  Returns the status of the widget setting up operation:
*    - CYRET_SUCCESS if the operation is successfully completed.
*    - CYRET_BAD_PARAM if the widget is invalid or if the specified widget is
*      disabled
*    - CYRET_INVALID_STATE if the previous scanning is not completed and the
*      hardware block is busy.
*    - CYRET_UNKNOWN if an unknown sensing method is used by the widget or
*      other spurious errors.
*
**********************************************************************************/
cystatus `$INSTANCE_NAME`_SetupWidget(uint32 widgetId)
{
    cystatus widgetStatus;

    if (`$INSTANCE_NAME`_WDGT_SW_STS_BUSY == (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_WDGT_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        widgetStatus = CYRET_INVALID_STATE;
    }
    /*
     *  Check if widget id is valid, specified widget is enabled and widget did not
     *  detect any fault conditions if BIST is enabled. If all conditions are met,
     *  set widgetStatus as good, if not, set widgetStatus as bad.
     */
    else if ((`$INSTANCE_NAME`_TOTAL_SLOTS > widgetId) &&
        (0uL != `$INSTANCE_NAME`_GET_WIDGET_EN_STATUS(widgetId)))

    {
        widgetStatus = CYRET_SUCCESS;
    }
    else
    {
        widgetStatus = CYRET_BAD_PARAM;
    }

    /*
     * Check widgetStatus flag that is set earlier, if flag is good, then set up only
     * widget
     */
    if (CYRET_SUCCESS == widgetStatus)
    {
        /*  Check if CSD2X is enabled   */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)

            widgetStatus = `$INSTANCE_NAME`_SetupWidget2x(widgetId);

        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
            /*  Check widget sensing method is CSX and call CSX APIs    */
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
            {
                /*  Set up widget for CSX scan  */
                `$INSTANCE_NAME`_CSXSetupWidget(widgetId);
            }
            /*  Check widget sensing method is CSD and call appropriate API */
            else if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                     `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
            {
                /*  Set up widget for CSD scan  */
                `$INSTANCE_NAME`_CSDSetupWidget(widgetId);
            }
            else
            {
                /*  Sensing method is invalid, return error to caller  */
                widgetStatus = CYRET_UNKNOWN;
            }
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            /*  Set up widget for scan */
            `$INSTANCE_NAME`_CSDSetupWidget(widgetId);
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            /*  Set up widgets for scan     */
            `$INSTANCE_NAME`_CSXSetupWidget(widgetId);
        #else
            widgetStatus = CYRET_UNKNOWN;
            #error "No sensing method enabled, component cannot work in this mode"
        #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
    }

    return (widgetStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Scan
****************************************************************************//**
*
* \brief
*  Initiates scan of all sensors in the widget which is initialized by
*  `$INSTANCE_NAME`_SetupWidget(), if the no scan is in progress.
*
* \details
*  This function should be called only after the `$INSTANCE_NAME`_SetupWidget()
*  function is called to start the scanning of the sensors in the widget. The
*  status of a sensor scan must be checked using the `$INSTANCE_NAME`_IsBusy()
*  API prior to starting a next scan or setting up another widget.
*
* \return
*  Returns the status of the scan initiation operation:
*    - CYRET_SUCCESS if scanning is successfully started.
*    - CYRET_INVALID_STATE if the previous scanning is not completed and the
*      hardware block is busy.
*    - CYRET_UNKNOWN if an unknown sensing method is used by the widget.
*
********************************************************************************/
cystatus `$INSTANCE_NAME`_Scan(void)
{
    cystatus scanStatus = CYRET_SUCCESS;

    if (`$INSTANCE_NAME`_WDGT_SW_STS_BUSY == (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_WDGT_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CYRET_INVALID_STATE;
    }
    else
    {
        /*  If CSD2X is enabled, call CSD2X scan    */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        scanStatus = `$INSTANCE_NAME`_Scan2x();

    /*  If both CSD and CSX are enabled, call scan API based on widget sensing method    */
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
        /*  Check widget sensing method and call appropriate APIs   */
        switch (`$INSTANCE_NAME`_currentSenseMethod)
        {
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                `$INSTANCE_NAME`_CSXScan();
                break;

            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                 `$INSTANCE_NAME`_CSDScan();
                break;

            default:
                scanStatus = CYRET_UNKNOWN;
                break;
        }

    /*  If only CSD is enabled, call CSD scan   */
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        `$INSTANCE_NAME`_CSDScan();

    /*  If only CSX is enabled, call CSX scan   */
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        `$INSTANCE_NAME`_CSXScan();

    #else
        scanStatus = CYRET_UNKNOWN;
        #error "No sensing method enabled, component cannot work in this mode"
    #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
    }

    return (scanStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanAllWidgets
****************************************************************************//**
*
* \brief
*  Initializes the first enabled widget and scans of all the sensors in the
*  widget, then the same process is repeated for all widgets in the component.
*  I.e. scan all the widgets in the component.
*
* \details
*  This function initializes a widget and scans all the sensors in the widget,
*  and then repeats the same for all the widgets in the component. The tasks of
*  the `$INSTANCE_NAME`_SetupWidget() and `$INSTANCE_NAME`_Scan() functions are
*  executed by these functions. The status of a sensor scan must be checked
*  using the `$INSTANCE_NAME`_IsBusy() API prior to starting a next scan
*  or setting up another widget.
*
* \return
*  Returns the status of operation:
*    - CYRET_SUCCESS if scanning is successfully started.
*    - CYRET_BAD_PARAM if all the widgets are disabled.
*    - CYRET_INVALID_STATE if the previous scanning is not completed and the HW block is busy.
*    - CYRET_UNKNOWN if there are unknown errors.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_ScanAllWidgets(void)
{
    cystatus scanStatus = CYRET_UNKNOWN;

    uint32 wdgtIndex;

    if (`$INSTANCE_NAME`_SW_STS_BUSY == (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CYRET_INVALID_STATE;
    }
    else
    {
        /*
         *  Set up widget first widget.
         *  If widget returned error, set up next, continue same until widget does not return error.
         */
        for (wdgtIndex = 0u;
             wdgtIndex < `$INSTANCE_NAME`_TOTAL_SLOTS;
             wdgtIndex++)
        {

            scanStatus = `$INSTANCE_NAME`_SetupWidget(wdgtIndex);

            if (CYRET_SUCCESS == scanStatus)
            {
                #if (0u != (`$INSTANCE_NAME`_TOTAL_SLOTS - 1u))
                    /* If there are more than one widget to be scanned, request callback to scan next widget */
                    if ((`$INSTANCE_NAME`_TOTAL_SLOTS - 1u) > wdgtIndex)
                    {
                         /* Request callback to scan next widget in ISR */
                        `$INSTANCE_NAME`_requestScanAllWidget = `$INSTANCE_NAME`_ENABLE;
                    }
                    else
                    {
                        /* Request to exit in ISR (Do not scan the next widgets) */
                        `$INSTANCE_NAME`_requestScanAllWidget = `$INSTANCE_NAME`_DISABLE;
                    }
                #else
                    {
                        /* Request to exit in ISR (We have only one widget) */
                        `$INSTANCE_NAME`_requestScanAllWidget = `$INSTANCE_NAME`_DISABLE;
                    }
                #endif  /* (0u != (`$INSTANCE_NAME`_TOTAL_SLOTS - 1u)) */

                /*  Initiate scan and quit loop */
                scanStatus = `$INSTANCE_NAME`_Scan();

                break;
            }
        }
    }

    return (scanStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsInitialize
****************************************************************************//**
*
* \brief
*   Performs hardware and firmware initialization required for proper operation
*   of the `$INSTANCE_NAME` component. This function is called from
*   the `$INSTANCE_NAME`_Start() API prior to calling any other APIs of the component.
*
* \details
*   Performs hardware and firmware initialization required for proper operation
*   of the `$INSTANCE_NAME` component. This function is called from
*   the `$INSTANCE_NAME`_Start() API prior to calling any other APIs of the component.
*   1. The function initializes immunity offsets when the frequency hopping is
*      enabled.
*   2. Depending on the configuration, the function initializes the CSD block
*      for the CSD2X, CSD, CSX, or CSD+CSX modes.
*   3. The function updates the dsRam.wdgtWorking variable with 1 when Self Test
*      is enabled.
*
*   Calling the `$INSTANCE_NAME`_Start API is the recommended method to initialize
*   the `$INSTANCE_NAME` component at power-up. The `$INSTANCE_NAME`_SsInitialize()
*   API should not be used for initialization, resume, or wake-up operations.
*   The dsRam.wdgtWorking variable is updated.
*
* \return status
*   Returns status of operation:
*   - Zero        - Indicates successful initialization.
*   - Non-zero    - One or more errors occurred in the initialization process.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SsInitialize(void)
{
    cystatus initStatus = CYRET_SUCCESS;

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
        `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] = (uint8)CY_GET_REG32(CY_SYS_CLK_IMO_TRIM1_PTR);
        if (`$INSTANCE_NAME`_COARSE_TRIM_THRESHOLD_1 > `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0])
        {
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] + `$INSTANCE_NAME`_FREQUENCY_OFFSET_5;
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_2] =
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] + `$INSTANCE_NAME`_FREQUENCY_OFFSET_10;
        }
        else if (`$INSTANCE_NAME`_COARSE_TRIM_THRESHOLD_2 > `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0])
        {
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] - `$INSTANCE_NAME`_FREQUENCY_OFFSET_5;
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_2] =
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] + `$INSTANCE_NAME`_FREQUENCY_OFFSET_5;
        }
        else
        {
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_1] =
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] - `$INSTANCE_NAME`_FREQUENCY_OFFSET_5;
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_2] =
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] - `$INSTANCE_NAME`_FREQUENCY_OFFSET_10;
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
        `$INSTANCE_NAME`_SsTrimIdacs();
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)))
        `$INSTANCE_NAME`_SsInitializeSourceSenseClk();
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
              ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))) */

    /* Set all IO states to default state  */
    `$INSTANCE_NAME`_SsSetIOsInDefaultState();

    /*
     *  Check if CSD2X is enabled, if yes, initialize `$INSTANCE_NAME` component
     *  for CSD2x operation
     */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        /*
         *  Check if CSX or CSD enable along with CSD2X, if yes, provide the error
         *  message as CSD2X can not coexist with CSD or CSX
         */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            #error "CSD2X and CSX can not be enabled together"
            initStatus = CYRET_UNKNOWN;
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            #error "CSD2X and CSD can not be enabled together"
            initStatus = CYRET_UNKNOWN;
        #endif /* (`$INSTANCE_NAME`_CSX_EN == `$INSTANCE_NAME`_ENABLE) */

        /* Initialize both CSD blocks for CSD2X scanning    */
        `$INSTANCE_NAME`_CSD2XInitialize();

    #elif ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))

        /*
         * CSD hardware block is initialized in the Setup Widget based
         * on widget sensing method. Release previously captured HW resources
         * if it is second call of `$INSTANCE_NAME`_Start() function.
         */
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_UNDEFINED_E);
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        /*  Initialize CSD block for CSD scanning   */
        `$INSTANCE_NAME`_SsCSDInitialize();

    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        /*  Initialize CSD block for CSX scanning   */
        `$INSTANCE_NAME`_CSXInitialize();

    #else
        #error "No sensing method enabled, component cannot work in this mode"
        initStatus = CYRET_UNKNOWN;
    #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

    return (initStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPinState
****************************************************************************//**
*
* \brief
*  Sets the state (drive mode and output state) of port pin used by a sensor.
*  The possible states are GND, Shield, High-Z, Tx or Rx, sensor. If the sensor
*  specified in the input parameter is a ganged sensor, then state of all pins
*  associated with ganged sensor is updated.
*
* \details
*  This function sets a specified state to the specified sensor element. For
*  CSD widgets sensor element is a sensor number, for CSX widgets it is either
*  RX or TX. If the sensor element is a ganged sensor, then the specified state
*  is also set for all ganged pins of this sensor. Scanning should be completed
*  before calling this API.
*
*  The `$INSTANCE_NAME`_SHIELD and `$INSTANCE_NAME`_SENSOR states are not
*  allowed if there is no CSD widget configured in the user’s project.
*  The `$INSTANCE_NAME`_TX_PIN and `$INSTANCE_NAME`_RX_PIN states are not
*  allowed if there is no CSX widget configured in the user’s project.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases. Functions that perform a setup and scan of the sensor/widget
*  automatically set needed pin states. They do not take into account changes
*  in the design made by the `$INSTANCE_NAME`_SetPinState() function.
*  This function neither check wdgtIndex nor sensorElement for correctness.
*
*  \param widgetId
*  Specify the ID number of the widget to change the pin state of the specified
*  sensor.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration
*  header file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
*  \param sensorElement
*  Specify the ID number of the sensor element within the widget to change
*  its pin state.
*  For CSD widgets sensorElement is a sensor ID and can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  - `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*  For CSX widgets sensorElement is defined either as Rx ID or Tx ID.
*  The first Rx in a widget corresponds to sensorElement = 0, the second
*  second Rx in a widget corresponds to sensorElement = 1 and so on.
*  The last Tx in a widget corresponds to sensorElement = (RxNum + TxNum).
*  Macros for Rx and Tx IDs can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as:
*  - `$INSTANCE_NAME`_<WidgetName>_RX<RXNumber>_ID
*  - `$INSTANCE_NAME`_<WidgetName>_TX<TXNumber>_ID
*
*  \param state
*   Specify the state of the sensor that needs to be set:
*     1. `$INSTANCE_NAME`_GROUND - The pin is connected to ground.
*     2. `$INSTANCE_NAME`_HIGHZ - The drive mode of the pin is set to High-Z
*        Analog.
*     3. `$INSTANCE_NAME`_SHIELD - The shield signal is routed to the pin (only
*        in CSD sensing method when shield electrode is enabled).
*     4. `$INSTANCE_NAME`_SENSOR – The pin is connected to the scanning bus
*        (only in CSD sensing method).
*     5. `$INSTANCE_NAME`_TX_PIN – The TX signal is routed to the sensor
*        (only in CSX sensing method).
*     6. `$INSTANCE_NAME`_RX_PIN – The pin is connected to the scanning bus
*        (only in CSX sensing method).
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPinState(uint32 widgetId, uint32 sensorElement, uint32 state)
{
    uint32 eltdNum;
    uint32 eltdIndex;
    uint8  interruptState;
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr;
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GANGED_SNS_EN)
        `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;
    #endif

    /* Getting sensor element pointer and number of electrodes */
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GANGED_SNS_EN)
        /* Check the ganged sns flag */
        if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].staticConfig & `$INSTANCE_NAME`_GANGED_SNS_MASK))
        {
            curFlashSnsPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash;
            curFlashSnsPtr += sensorElement;
            ioPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId];
            eltdNum = curFlashSnsPtr->numPins;
        }
        else
        {
            ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash + sensorElement;
            eltdNum = 1u;
        }
    #else
        ioPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsFlash + sensorElement;
        eltdNum = 1u;
    #endif

    /* Loop through all electrodes of the specified sensor element */
    for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
    {
        /* Reset HSIOM and PC registers */
        interruptState = CyEnterCriticalSection();
        CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) & ~(`$INSTANCE_NAME`_HSIOM_SEL_MASK << ioPtr->hsiomShift));
        CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) & ~(`$INSTANCE_NAME`_GPIO_PC_MASK << ioPtr->shift));
        CyExitCriticalSection(interruptState);

        switch (state)
        {
        case `$INSTANCE_NAME`_GROUND:

            interruptState = CyEnterCriticalSection();
            CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) | (`$INSTANCE_NAME`_SNS_GROUND_CONNECT << ioPtr->shift));
            CY_SET_REG32(ioPtr->drPtr, CY_GET_REG32(ioPtr->drPtr) & (uint32)(~(uint32)((uint32)1u << ioPtr->drShift)));
            CyExitCriticalSection(interruptState);
            break;

        case `$INSTANCE_NAME`_HIGHZ:
            interruptState = CyEnterCriticalSection();
            CY_SET_REG32(ioPtr->drPtr, CY_GET_REG32(ioPtr->drPtr) & (uint32)~(uint32)((uint32)1u << ioPtr->drShift));
            CyExitCriticalSection(interruptState);
            break;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_SENSOR:
                /* Enable sensor */
                `$INSTANCE_NAME`_CSDConnectSns(ioPtr);
                break;

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN)
                case `$INSTANCE_NAME`_SHIELD:
                    /* Set appropriate bit in HSIOM register to configure pin to shield mode */
                    interruptState = CyEnterCriticalSection();
                    CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) | (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SHIELD << ioPtr->hsiomShift));
                    CyExitCriticalSection(interruptState);
                    break;
            #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_TX_PIN:
                interruptState = CyEnterCriticalSection();
                CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) | (`$INSTANCE_NAME`_HSIOM_SEL_CSD_SENSE << ioPtr->hsiomShift));
                CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) | (`$INSTANCE_NAME`_GPIO_STRGDRV << ioPtr->shift));
                CyExitCriticalSection(interruptState);
                break;

            case `$INSTANCE_NAME`_RX_PIN:
                interruptState = CyEnterCriticalSection();
                CY_SET_REG32(ioPtr->hsiomPtr, CY_GET_REG32(ioPtr->hsiomPtr) | (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << ioPtr->hsiomShift));
                CY_SET_REG32(ioPtr->pcPtr, CY_GET_REG32(ioPtr->pcPtr) & ~(`$INSTANCE_NAME`_GPIO_PC_MASK << ioPtr->shift));
                CyExitCriticalSection(interruptState);
                break;
        #endif

        default:
            /* Wrong state */
            break;
        }

        ioPtr++;
    }
}


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))

    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDDisableMode
        ****************************************************************************//**
        *
        * \brief
        *  This function disables CSD mode.
        *
        * \details
        *  To disable CSD mode the following tasks are performed:
        *  1. Disconnect Cmod from AMUXBUS-A;
        *  2. Disconnect previous CSX electrode if it has been connected;
        *  3. Disconnect Csh from AMUXBUS-B;
        *  4. Disable Shield Electrodes.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsCSDDisableMode(void)
        {
            uint32 newRegValue;

            /* Disconnect Cmod from AMUXBUS-A using HSIOM registers */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CMOD_HSIOM_MASK);
            CY_SET_REG32(`$INSTANCE_NAME`_CMOD_HSIOM_PTR, newRegValue);

            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
                 ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN)))
                /* Disconnect IDACA and IDACB */
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
                newRegValue &= (uint32)(~`$INSTANCE_NAME`_SW_REFGEN_SEL_SW_IAIB_MASK);
                CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR, newRegValue);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
                       ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_DEDICATED_IDAC_COMP_EN))) */

            /* Disconnect previous CSD electrode if it has been connected */
            `$INSTANCE_NAME`_SsCSDElectrodeCheck();

            /* Disconnect Csh from AMUXBUS-B */
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN))
                newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR);
                newRegValue &= (uint32)(~(uint32)(`$INSTANCE_NAME`_CSH_TO_AMUXBUS_B_MASK << `$INSTANCE_NAME`_CSH_HSIOM_SHIFT));
                CY_SET_REG32(`$INSTANCE_NAME`_CSH_HSIOM_PTR, newRegValue);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_TANK_EN)) */

            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                 (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT))
                `$INSTANCE_NAME`_SsCSDDisableShieldElectrodes();
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) && \
                       (0u != `$INSTANCE_NAME`_CSD_TOTAL_SHIELD_COUNT)) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsDisableCSXMode
        ****************************************************************************//**
        *
        * \brief
        *  This function disables CSX mode.
        *
        * \details
        *  To disable CSX mode the following tasks are performed:
        *  1. Disconnect CintA and CintB from AMUXBUS-A
        *  2. Disconnect previous CSX electrode if it has been connected
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsDisableCSXMode(void)
        {
            uint32 newRegValue;

            /*  Disconnect CintA from AMUXBUS-A using HSIOM registers.   */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintA_HSIOM_MASK);
            CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, newRegValue);

            /*  Disconnect CintB from AMUXBUS-A using HSIOM registers.   */
            newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
            newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintB_HSIOM_MASK);
            CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, newRegValue);

            /* Disconnect previous CSX electrode if it has been connected */
            `$INSTANCE_NAME`_CSXElectrodeCheck();
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsSwitchSensingMode
    ****************************************************************************//**
    *
    * \brief
    *  This function changes the mode for case when both CSD and CSX widgets are
    *  scanned.
    *
    * \details
    *  To switch to the CSD mode the following tasks are performed:
    *  1. Disconnect CintA and CintB from AMUXBUS-A;
    *  2. Disconnect previous CSD electrode if it has been connected;
    *  3. Initialize CSD mode.
    *
    *  To switch to the CSX mode the following tasks are performed:
    *  1. Disconnect Cmod from AMUXBUS-A;
    *  2. Disconnect previous CSX electrode if it has been connected;
    *  3. Initialize CSX mode.
    *
    * \param mode Specifies the scan mode:
    *           -  (1) `$INSTANCE_NAME`_SENSE_METHOD_CSD_E
    *           -  (2) `$INSTANCE_NAME`_SENSE_METHOD_CSX_E
    *           -  (3) `$INSTANCE_NAME`_SENSE_METHOD_BIST_E
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_ENUM mode)
    {
        if (`$INSTANCE_NAME`_currentSenseMethod != mode)
        {
            /* The requested mode differes to the current one. Disable the current mode */
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==  `$INSTANCE_NAME`_currentSenseMethod)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                    `$INSTANCE_NAME`_SsCSDDisableMode();
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
            }
            else if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E ==  `$INSTANCE_NAME`_currentSenseMethod)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                    `$INSTANCE_NAME`_SsDisableCSXMode();
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
            }
            else if (`$INSTANCE_NAME`_SENSE_METHOD_BIST_E ==  `$INSTANCE_NAME`_currentSenseMethod)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
                    `$INSTANCE_NAME`_BistDisableMode();
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
            }
            else
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
                    /* Release ADC resources */
                    (void)`$INSTANCE_NAME`_AdcReleaseResources();
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */
            }

            /* Enable the specified mode */
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E == mode)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                    /* Initialize CSD mode to guarantee configured CSD mode */
                    `$INSTANCE_NAME`_SsCSDInitialize();
                    `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_SENSE_METHOD_CSD_E;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
            }
            else if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == mode)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                    /* Initialize CSX mode to guarantee configured CSX mode */
                    `$INSTANCE_NAME`_CSXInitialize();
                    `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_SENSE_METHOD_CSX_E;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
            }
            else if (`$INSTANCE_NAME`_SENSE_METHOD_BIST_E == mode)
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
                    /* Initialize CSX mode to guarantee configured CSX mode */
                    `$INSTANCE_NAME`_BistInitialize();
                    `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_SENSE_METHOD_BIST_E;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
            }
            else
            {
                `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_UNDEFINED_E;
            }
        }
    }
#endif  /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsSetIOsInDefaultState
****************************************************************************//**
*
* \brief
*   Sets all electrodes into a default state.
*
* \details
*   Sets all the CSD/CSX IOs into a default state:
*   - HSIOM   - Disconnected, the GPIO mode.
*   - DM      - Strong drive.
*   - State   - Zero.
*
*   Sets all the ADC channels into a default state:
*   - HSIOM   - Disconnected, the GPIO mode.
*   - DM      - HiZ-Analog.
*   - State   - Zero.
*
*   It is not recommended to call this function directly from the application
*   layer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetIOsInDefaultState(void)
{
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];
    uint32 loopIndex;
    uint32 regValue;

    /*  Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < `$INSTANCE_NAME`_TOTAL_ELECTRODES; loopIndex++)
    {
        /*  1. Disconnect HSIOM
            2. Set strong DM
            3. Set pin state to logic 0     */
        regValue = CY_GET_REG32 (ioPtr->hsiomPtr);
        regValue &= ~(ioPtr->hsiomMask);
        CY_SET_REG32 (ioPtr->hsiomPtr, regValue);

        regValue = CY_GET_REG32 (ioPtr->pcPtr);
        regValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << ioPtr->shift);
        regValue |=  (`$INSTANCE_NAME`_GPIO_STRGDRV << ioPtr->shift);
        CY_SET_REG32 (ioPtr->pcPtr, regValue);

        regValue = CY_GET_REG32 (ioPtr->drPtr);
        regValue &= ~(ioPtr->mask);
        CY_SET_REG32 (ioPtr->drPtr, regValue);

        /*  Get next electrode  */
        ioPtr++;
    }

    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
        `$INSTANCE_NAME`_ClearAdcChannels();
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */
}


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsReleaseResources()
****************************************************************************//**
*
* \brief
*  This function sets the resources that do not belong to the CSDv2 HW block to
*  default state.
*
* \details
*  The function performs following tasks:
*  1. Checks if CSD block busy and returns error if it is busy
*  2. Disconnects integration capacitors (CintA, CintB for CSX mode and
*     Cmod for CSD mode)
*  3. Disconnect electroded if they have been connected.
*
* \return
*   Returns the status of operation:
*   - Zero        - Resources released successfully.
*   - Non-zero    - One or more errors occurred in releasing process.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SsReleaseResources(void)
{
    cystatus busyStatus = CYRET_SUCCESS;

    if (`$INSTANCE_NAME`_SW_STS_BUSY == (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY))
    {
        /* Previous widget is being scanned. Return error. */
        busyStatus = CYRET_INVALID_STATE;
    }
    else
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            `$INSTANCE_NAME`_SsDisableCSXMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            `$INSTANCE_NAME`_SsCSDDisableMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
            `$INSTANCE_NAME`_BistDisableMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */

        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) &&  \
             (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION))
            `$INSTANCE_NAME`_SsSetIOsInDefaultState();
        #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
             (`$INSTANCE_NAME`_DISABLE != `$INSTANCE_NAME`_CSD_SHIELD_EN) &&  \
             (`$INSTANCE_NAME`_SNS_CONNECTION_SHIELD == `$INSTANCE_NAME`_CSD_INACTIVE_SNS_CONNECTION)) */

        /*
         * Reset of the currentSenseMethod variable to make sure that the next
         * call of SetupWidget() API setups the correct widget mode
         */
        `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_UNDEFINED_E;
    }

    return busyStatus;
}
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsPostAllWidgetsScan
****************************************************************************//**
*
* \brief
*   The ISR function for multiple widget scanning implementation.
*
* \details
*   This is the function used by the `$INSTANCE_NAME` ISR to implement multiple widget
*   scanning.
*   Should not be used by the application layer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsPostAllWidgetsScan(void)
{
    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN)
        /*
        *   1. Increment widget index
        *   2. Check if all widgets are scanned
        *   3. If all widgets are not scanned, set up and scan next widget
        */
        #if (1u != `$INSTANCE_NAME`_TOTAL_WIDGETS)
            cystatus postScanStatus;

            do
            {
                `$INSTANCE_NAME`_widgetIndex++;

                postScanStatus = `$INSTANCE_NAME`_SetupWidget((uint32)`$INSTANCE_NAME`_widgetIndex);

                if (CYRET_SUCCESS == postScanStatus)
                {
                    if((`$INSTANCE_NAME`_TOTAL_WIDGETS - 1u) == `$INSTANCE_NAME`_widgetIndex)
                    {
                        /* The last widget will be scanned. Reset flag to skip configuring the next widget setup in ISR. */
                        `$INSTANCE_NAME`_requestScanAllWidget = `$INSTANCE_NAME`_DISABLE;
                    }
                    (void)`$INSTANCE_NAME`_Scan();
                }
                else if((`$INSTANCE_NAME`_TOTAL_WIDGETS - 1u) == `$INSTANCE_NAME`_widgetIndex)
                {
                    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) && \
                         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN))
                        if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                             `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex]))
                        {
                            /*  Disable the CSD block */
                            CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd);
                        }
                    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) && \
                               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

                    /* All widgets are totally processed. Reset BUSY flag */
                    `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;

                    /* Update status with with the failure */
                    `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_ERR_MASK;
                    `$INSTANCE_NAME`_dsRam.status |= ((postScanStatus & `$INSTANCE_NAME`_STATUS_ERR_SIZE) << `$INSTANCE_NAME`_STATUS_ERR_SHIFT);

                    /* Set postScanStatus to exit the while loop */
                    postScanStatus = CYRET_SUCCESS;
                }
                else
                {
                    /* Update status with with the failure. Configure the next widget in while() loop */
                    `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_ERR_MASK;
                    `$INSTANCE_NAME`_dsRam.status |= ((postScanStatus & `$INSTANCE_NAME`_STATUS_ERR_SIZE) << `$INSTANCE_NAME`_STATUS_ERR_SHIFT);
                }
            } while (CYRET_SUCCESS != postScanStatus);
        #endif /* (1u != `$INSTANCE_NAME`_TOTAL_WIDGETS) */
    #else
        #if (1u != `$INSTANCE_NAME`_TOTAL_SLOTS)
            cystatus postScanStatus = CYRET_SUCCESS;

            do
            {
                if ((`$INSTANCE_NAME`_TOTAL_SLOTS - 1u) > `$INSTANCE_NAME`_slotIndex)
                {
                    `$INSTANCE_NAME`_slotIndex++;
                    postScanStatus = `$INSTANCE_NAME`_SetupWidget((uint32)`$INSTANCE_NAME`_slotIndex);


                    if (CYRET_SUCCESS == postScanStatus)
                    {
                        if((`$INSTANCE_NAME`_TOTAL_SLOTS - 1u) == `$INSTANCE_NAME`_slotIndex)
                        {
                            /* The last slot will be scanned. Reset flag to skip configuring the next widget setup in ISR. */
                            `$INSTANCE_NAME`_requestScanAllWidget = `$INSTANCE_NAME`_DISABLE;
                        }
                        (void)`$INSTANCE_NAME`_Scan();
                    }
                    else if((`$INSTANCE_NAME`_TOTAL_SLOTS - 1u) == `$INSTANCE_NAME`_slotIndex)
                    {
                        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN)
                            /*  Disable the CSD blocks */
                            CY_SET_REG32(`$INSTANCE_NAME`_CSD0_CONFIG_PTR, `$INSTANCE_NAME`_configCsd0);
                            CY_SET_REG32(`$INSTANCE_NAME`_CSD1_CONFIG_PTR, `$INSTANCE_NAME`_configCsd1);
                        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) */

                        /* All widgets are totally processed. Reset BUSY flag */
                        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;

                        /* Update status with with the failure */
                        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_ERR_MASK;
                        `$INSTANCE_NAME`_dsRam.status |= ((postScanStatus & `$INSTANCE_NAME`_STATUS_ERR_SIZE) << `$INSTANCE_NAME`_STATUS_ERR_SHIFT);

                        /* Set postScanStatus to exit the while loop */
                        postScanStatus = CYRET_SUCCESS;
                    }
                    else
                    {
                        /* Update status with with the failure. Configure the next widget in while() loop */
                        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_STATUS_ERR_MASK;
                        `$INSTANCE_NAME`_dsRam.status |= ((postScanStatus & `$INSTANCE_NAME`_STATUS_ERR_SIZE) << `$INSTANCE_NAME`_STATUS_ERR_SHIFT);
                    }
                }
            } while (CYRET_SUCCESS != postScanStatus);
        #endif /* (1u != `$INSTANCE_NAME`_TOTAL_SLOTS) */
    #endif /* (`$INSTANCE_NAME`_CSD2X_EN == `$INSTANCE_NAME`_DISABLE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsIsrInitialize
****************************************************************************//**
*
* \brief
*   Enables and initializes for the function pointer for a callback for the ISR.
*
* \details
*   The  "address" is a special type cyisraddress defined by Cylib. This function
*   is used by component APIs and should not be used by an application program for
*   proper working of the component.
*
* \param  address The address of the function to be called when interrupt is fired.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsIsrInitialize(cyisraddress address)
{
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
    `$INSTANCE_NAME`_ISR0_StartEx(address);
    `$INSTANCE_NAME`_ISR1_StartEx(address);
#else
    `$INSTANCE_NAME`_ISR_StartEx(address);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsSetModClkClockDivider
****************************************************************************//**
*
* \brief
*   Sets the divider values for the modulator clock and then starts
*   the modulator clock.
*
* \details
*   It is not recommended to call this function directly by the application layer.
*   It is used by initialization, widget APIs or wakeup functions to
*   enable the clocks.
*
* \param
*   modClk The divider value for the modulator clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetModClkClockDivider(uint32 modClk)
{
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
    /*  Stop modulator clock   */
    CY_SET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR,
                 ((uint32)`$INSTANCE_NAME`_ModClk__DIV_ID <<
                 `$INSTANCE_NAME`_MODCLK_CMD_DIV_SHIFT)|
                 ((uint32)`$INSTANCE_NAME`_MODCLK_CMD_DISABLE_MASK));

    /*
     * Set divider value for sense modClk.
     * 1u is subtracted from modClk because Divider register value 0 corresponds
     * to dividing by 1.
     */
    CY_SET_REG32(`$INSTANCE_NAME`_MODCLK_DIV_PTR, ((modClk - 1u) << 8u));

    /*  Check whether previous modulator clock start command has finished. */
    while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR) & `$INSTANCE_NAME`_MODCLK_CMD_ENABLE_MASK))
    {
        /*  Wait until previous modulator clock start command has finished. */
    }

    /*  Start modulator clock, aligned to HFCLK */
    CY_SET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR,
                 (uint32)(((uint32)`$INSTANCE_NAME`_ModClk__DIV_ID << `$INSTANCE_NAME`_MODCLK_CMD_DIV_SHIFT) |
                  ((uint32)`$INSTANCE_NAME`_ModClk__PA_DIV_ID << `$INSTANCE_NAME`_MODCLK_CMD_PA_DIV_SHIFT) |
                  `$INSTANCE_NAME`_MODCLK_CMD_ENABLE_MASK));
#else
    uint32 newRegValue;

    /* Clear bit to disable ModClk clock. */
    CY_SET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR,
                 CY_GET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR) &
                 (uint32)(~`$INSTANCE_NAME`_ModClk__ENABLE_MASK));

    /*
     * Update ModClk clock divider.
     * 1u is subtracted from modClk because Divider register value has range (0-65535).
     */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_MODCLK_DIV_PTR) & (uint32)(~(uint32)`$INSTANCE_NAME`_ModClk__DIVIDER_MASK);
    newRegValue |= (modClk - 1u);
    CY_SET_REG32(`$INSTANCE_NAME`_MODCLK_DIV_PTR, newRegValue);

    /* Set bit to enable ModClk clock. */
    CY_SET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR,
                 CY_GET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR) |
                `$INSTANCE_NAME`_ModClk__ENABLE_MASK);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsSetSnsClockDivider
****************************************************************************//**
*
* \brief
*   Sets the divider values for the sense clock and then starts
*   the sense clock.
*
* \details
*   It is not recommended to call this function directly by the application layer.
*   It is used by initialization, widget APIs or wakeup functions to
*   enable the clocks.
*
* \param
*   snsClk The divider value for the sense clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetSnsClockDivider(uint32 snsClk)
{
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    uint32 newRegValue;

    /*
     * Set divider value for sense clock.
     * 1u is subtracted from snsClk because SENSE_DIV value 0 corresponds
     * to dividing by 1.
     */
    newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR);
    newRegValue &= (uint32)(~`$INSTANCE_NAME`_SENSE_PERIOD_SENSE_DIV_MASK);
    newRegValue |= snsClk - 1u;
    CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR, newRegValue);
#else
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
        /*  Stop sense clock clock   */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     ((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID <<
                     `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT)|
                     ((uint32)`$INSTANCE_NAME`_SNSCLK_CMD_DISABLE_MASK));

        /*
         * Set divider value for sense clock.
         * 1u is subtracted from snsClk because Divider register value 0 corresponds
         * to dividing by 1.
         */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_DIV_PTR, ((snsClk - 1u) << 8u));

        /*  Check whether previous sense clock start command has finished. */
        while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) & `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK))
        {
            /*  Wait until previous sense clock start command has finished. */
        }

        /* Start sense clock aligned to previously started modulator clock. */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     (uint32)(((uint32)`$INSTANCE_NAME`_SnsClk__DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_DIV_SHIFT) |
                      ((uint32)`$INSTANCE_NAME`_ModClk__PA_DIV_ID << `$INSTANCE_NAME`_SNSCLK_CMD_PA_DIV_SHIFT) |
                      `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK));
    #else
        uint32 newRegValue;

        /* Clear bit to disable SnsClk clock. */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) &
                     (uint32)(~(uint32)`$INSTANCE_NAME`_SnsClk__ENABLE_MASK));

        /*
         * Update snsClk clock divider.
         * 1u is subtracted from snsClk because Divider register value has range (0-65535).
         */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_DIV_PTR) & (uint32)(~(uint32)`$INSTANCE_NAME`_SnsClk__DIVIDER_MASK);
        newRegValue |= (snsClk - 1u);
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_DIV_PTR, newRegValue);

        /* Set bit to enable SnsClk clock. */
        CY_SET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR,
                     CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) |
                    `$INSTANCE_NAME`_SnsClk__ENABLE_MASK);
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsSetClockDividers
****************************************************************************//**
*
* \brief
*   Sets the divider values for sense and modulator clocks and then starts
*   a modulator clock-phase aligned to HFCLK and sense clock-phase aligned to
*   the modulator clock.
*
* \details
*   It is not recommended to call this function directly by the application layer.
*   It is used by initialization, widget APIs or wakeup functions to
*   enable the clocks.
*
* \param
*   snsClk The divider value for the sense clock.
*   modClk The divider value for the modulator clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetClockDividers(uint32 snsClk, uint32 modClk)
{
    /* Configure Mod clock */
    `$INSTANCE_NAME`_SsSetModClkClockDivider(modClk);

    /* Configure Sns clock */
    `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClk);
}


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Calibrates the IDACs for all sensors in the specified widget to default
    *  target, this function detects sensing method used by the
    *  widget prior to calibration.
    *
    * \details
    *  This function performs exactly the same tasks as
    *  `$INSTANCE_NAME`_CalibrateAllWidgets, but only for a specified widget.
    *  This function detects the sensing method used by the widgets and takes
    *  into account the Enable compensation IDAC parameter.
    *
    *  This function is available when the CSD and/or CSX Enable IDAC
    *  auto-calibration parameter is enabled.

    *
    * \param widgetId
    *  Specify the ID number of the widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  `$INSTANCE_NAME` Configuration header file defined as
    *  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
    *
    * \return
    *  Returns the status of the specified widget calibration:
    *    - CYRET_SUCCESS if operation is successfully completed.
    *    - CYRET_BAD_PARAM if the input parameter is invalid.
    *    - CYRET_BAD_DATA if the calibration failed and the component may not
    *      operate as expected.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_CalibrateWidget(uint32 widgetId)
    {
        cystatus calibrateStatus = CYRET_SUCCESS;

        do
        {
            if (`$INSTANCE_NAME`_TOTAL_WIDGETS <= widgetId)
            {
                calibrateStatus = CYRET_BAD_PARAM;
            }

            /*
             *  Check if widget id is valid, specified widget did not
             *  detect any faults conditions if BIST is enabled.
             */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
                if (0u != `$INSTANCE_NAME`_GET_WIDGET_EN_STATUS(widgetId))
                {
                    calibrateStatus = CYRET_SUCCESS;
                }
                else
                {
                    calibrateStatus = CYRET_INVALID_STATE;
                }
            #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */

            if (CYRET_SUCCESS != calibrateStatus)
            {
                /* Exit from the loop because of a fail */
                break;
            }

            /* If CSD2X is enabled, calibrate CSD sensor    */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
                /* Calibrate CSD2X slot */
                calibrateStatus = `$INSTANCE_NAME`_CSD2XCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL);

            /*  If both CSD and CSX are enabled, calibrate widget using sensing method */
            #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)

                /* Check widget sensing method and call appropriate APIs */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN)
                    if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E ==
                        `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
                    {
                        /* Calibrate CSX widget  */
                       `$INSTANCE_NAME`_CSXCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSX_RAWCOUNT_CAL_LEVEL);
                    }
                #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN) */

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN)
                    if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                        `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
                    {
                        /* Calibrate CSD widget */
                        calibrateStatus = `$INSTANCE_NAME`_CSDCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL);
                    }
                #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN) */

            /*  If only CSD is enabled, calibrate CSD sensor  */
            #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                calibrateStatus = `$INSTANCE_NAME`_CSDCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL);

            /*  If only CSX is enabled, call CSX scan   */
            #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                `$INSTANCE_NAME`_CSXCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSX_RAWCOUNT_CAL_LEVEL);

            #else
                calibrateStatus = CYRET_UNKNOWN;
            #endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

             /* Update CRC */
            #if (`$INSTANCE_NAME`_ENABLE ==`$INSTANCE_NAME`_TST_WDGT_CRC_EN)
                `$INSTANCE_NAME`_DsUpdateWidgetCrc(widgetId);
            #endif /* (`$INSTANCE_NAME`_ENABLE ==`$INSTANCE_NAME`_TST_WDGT_CRC_EN) */

        } while (0u);

        return calibrateStatus;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CalibrateAllWidgets
    ****************************************************************************//**
    *
    * \brief
    *  Calibrates the IDACs for all widgets in the component to default target
    *  (85%) value, this function detects sensing method used by the widgets
    *  prior to calibration.
    *
    * \details
    *  Calibrates the IDACs for all widgets in the component to the default
    *  target (85% of maximum possible raw count) value. This function detects
    *  the sensing method used by the widgets and takes into account the Enable
    *  compensation IDAC parameter.
    *
    *  This function is available when the CSD and/or CSX Enable IDAC
    *  auto-calibration parameter is enabled.
    *
    * \return
    *  Returns the status of the calibration process:
    *    - CYRET_SUCCESS if the operation is successfully completed.
    *    - CYRET_BAD_DATA if the calibration failed and the component may not
    *      operate as expected.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_CalibrateAllWidgets(void)
    {
        cystatus calibrateStatus = CYRET_SUCCESS;
        uint32 wdgtIndex;

        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            calibrateStatus |= `$INSTANCE_NAME`_CalibrateWidget(wdgtIndex);
        }

        return calibrateStatus;
    }
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_AUTOCAL_EN) ||
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN)) */


#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsSetEqualSlotClock
        ****************************************************************************//**
        *
        * \brief
        *  This function sets sense clocks to be equal on both CSD blocks.
        *
        * \details
        *  This function sets clock dividers to equal
        *  to widget divider that has higher value.
        *
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsSetEqualSlotClock(void)
        {
            `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrCSD0Wdgt = 0u;
            `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrCSD1Wdgt = 0u;
            uint32 widgetIndex;
            uint32 emptySlot;

            /* Make sure that sense clocks are equal on both CSD blocks */
            for (widgetIndex = 0u; widgetIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; widgetIndex++)
            {
                emptySlot = 0u;
                for (`$INSTANCE_NAME`_slotIndex = 0u; `$INSTANCE_NAME`_slotIndex < `$INSTANCE_NAME`_TOTAL_SLOTS; `$INSTANCE_NAME`_slotIndex++)
                {
                    `$INSTANCE_NAME`_widgetIndex0 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd0WidgetId;
                    `$INSTANCE_NAME`_sensorIndex0 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd0SensorId;

                    `$INSTANCE_NAME`_widgetIndex1 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd1WidgetId;
                    `$INSTANCE_NAME`_sensorIndex1 = `$INSTANCE_NAME`_scanSlots[`$INSTANCE_NAME`_slotIndex].csd1SensorId;

                    if (`$INSTANCE_NAME`_EMPTY_SLOT == `$INSTANCE_NAME`_widgetIndex0)
                    {
                        emptySlot++;
                    }

                    if (`$INSTANCE_NAME`_EMPTY_SLOT == `$INSTANCE_NAME`_widgetIndex1)
                    {
                        emptySlot++;
                    }

                    if (0u == emptySlot)
                    {
                        ptrCSD0Wdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                       `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].ptr2WdgtRam;
                        ptrCSD1Wdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                       `$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].ptr2WdgtRam;

                        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                            /* Check if current slot for CSD0 block has a row */
                            if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex0].numCols <= `$INSTANCE_NAME`_sensorIndex0)
                            {
                                /* Check if current slot for CSD1 block has a row */
                                if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].numCols <= `$INSTANCE_NAME`_sensorIndex1)
                                {
                                    /* Both slots have the rows. Compare rowSnsClk and reassign the higher divider to widget with the lower divider */
                                    if (ptrCSD0Wdgt->rowSnsClk < ptrCSD1Wdgt->rowSnsClk)
                                    {
                                        ptrCSD0Wdgt->rowSnsClk = ptrCSD1Wdgt->rowSnsClk;
                                    }
                                    else
                                    {
                                        ptrCSD1Wdgt->rowSnsClk = ptrCSD0Wdgt->rowSnsClk;
                                    }
                                }
                                else
                                {
                                    /* CSD0 block has the row and CSD1 block has the column. Compare rowSnsClk and snsClk */
                                    if (ptrCSD0Wdgt->rowSnsClk < ptrCSD1Wdgt->snsClk)
                                    {
                                        ptrCSD0Wdgt->rowSnsClk = ptrCSD1Wdgt->snsClk;
                                    }
                                    else
                                    {
                                        ptrCSD1Wdgt->snsClk = ptrCSD0Wdgt->rowSnsClk;
                                    }
                                }
                            }
                            else
                            {
                                /* Check if current slot for CSD1 block has a row */
                                if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex1].numCols <= `$INSTANCE_NAME`_sensorIndex1)
                                {
                                    /* CSD0 block has the column and CSD1 block has the row. Compare snsClk and rowSnsClk */
                                    if (ptrCSD0Wdgt->snsClk < ptrCSD1Wdgt->rowSnsClk)
                                    {
                                        ptrCSD0Wdgt->snsClk = ptrCSD1Wdgt->rowSnsClk;
                                    }
                                    else
                                    {
                                        ptrCSD1Wdgt->rowSnsClk = ptrCSD0Wdgt->snsClk;
                                    }
                                }
                                else
                                {
                                    /* Both slots have the columns. Compare snsClk and reassign the higher divider to widget with the lower divider */
                                    if (ptrCSD0Wdgt->snsClk < ptrCSD1Wdgt->snsClk)
                                    {
                                        ptrCSD0Wdgt->snsClk = ptrCSD1Wdgt->snsClk;
                                    }
                                    else
                                    {
                                        ptrCSD1Wdgt->snsClk = ptrCSD0Wdgt->snsClk;
                                    }
                                }
                            }
                        #else
                            /* Compare snsClk and reassign the higher divider to widget with the lower divider */
                            if (ptrCSD0Wdgt->snsClk < ptrCSD1Wdgt->snsClk)
                            {
                                ptrCSD0Wdgt->snsClk = ptrCSD1Wdgt->snsClk;
                            }
                            else
                            {
                                ptrCSD1Wdgt->snsClk = ptrCSD0Wdgt->snsClk;
                            }
                        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
                    }
                }
            }
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsSetCSD0DirectClockMode
        ****************************************************************************//**
        *
        * \brief
        *  Sets Direct Clock Mode.
        *
        * \details
        *  For CSDv1: Resets PRS bit in `$INSTANCE_NAME`_configCsd variable;
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsSetCSD0DirectClockMode(void)
        {
            #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
                `$INSTANCE_NAME`_configCsd0 = `$INSTANCE_NAME`_configCsd0 &(uint32)~(`$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        }


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsSetCSD1DirectClockMode
        ****************************************************************************//**
        *
        * \brief
        *  Sets Direct Clock Mode.
        *
        * \details
        *  For CSDv1: Resets PRS bit in `$INSTANCE_NAME`_configCsd variable;
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsSetCSD1DirectClockMode(void)
        {
            #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
                `$INSTANCE_NAME`_configCsd1 = `$INSTANCE_NAME`_configCsd1 &(uint32)~(`$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        }
    #else


        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsSetDirectClockMode
        ****************************************************************************//**
        *
        * \brief
        *  Sets Direct Clock Mode.
        *
        * \details
        *  For CSDv1: Resets PRS bit in `$INSTANCE_NAME`_configCsd variable;
        *  For CSDv2: Resets `$INSTANCE_NAME`_SENSE_PERIOD_SEL_LFSR_MSB_MASK and
        *  `$INSTANCE_NAME`_SENSE_PERIOD_SEL_LFSR_MSB_MASK bits in
        *  `$INSTANCE_NAME`_SENSE_PERIOD register.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsSetDirectClockMode(void)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR, CY_GET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR) &
                                                                     (uint32)~(`$INSTANCE_NAME`_SENSE_PERIOD_SEL_LFSR_MSB_MASK | \
                                                                     `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_SIZE_MASK));
            #else
                `$INSTANCE_NAME`_configCsd = `$INSTANCE_NAME`_configCsd &(uint32)~(`$INSTANCE_NAME`_CONFIG_PRS_SELECT_MASK);
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsAutoTune
    ****************************************************************************//**
    *
    * \brief
    *  This API performs the parameters auto-tuning for the optimal `$INSTANCE_NAME` operation.
    *
    * \details
    *  This API performs the following:
    *  - Calibrates Modulator and Compensation IDACs.
    *  - Tunes the Sense Clock optimal value to get a Sense Clock period greater than
    *     2*5*R*Cp.
    *  - Calculates the resolution for the optimal finger capacitance.
    *
    * \return
    *   Returns the status of operation:
    *   - Zero     - All the widgets are auto-tuned successfully.
    *   - Non-zero - Auto-tuning failed for any widget.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_SsAutoTune(void)
    {
        cystatus autoTuneStatus = CYRET_SUCCESS;
        uint32 wdgtIndex;
        uint32 cp = 0uL;
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            uint32 cpRow = 0uL;
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
        uint32 cpWidget[`$INSTANCE_NAME`_TOTAL_WIDGETS];
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;
        AUTO_TUNE_CONFIG_TYPE autoTuneConfig;
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
            uint32 csdBlockID;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

        /* Configure common config variables */
        autoTuneConfig.snsClkConstantR = `$INSTANCE_NAME`_CSD_SNSCLK_R_CONST;
        autoTuneConfig.vRef = `$INSTANCE_NAME`_CSD_VREF_MV;
        #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN)
            autoTuneConfig.iDacGain = `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA * `$INSTANCE_NAME`_CSD_DUAL_IDAC_FACTOR;
        #endif /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSD2X_EN) */
        autoTuneConfig.calTarget = `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL;

        /* Calculate snsClk Input Clock in KHz */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
            /*  Dividers are chained (CSDV2). Flip flop is not available */
            autoTuneConfig.snsClkInputClock = (CYDEV_BCLK__HFCLK__KHZ / `$INSTANCE_NAME`_dsRam.modCsdClk);
        #elif ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) && (`$INSTANCE_NAME`_DISABLE == CY_PSOC4_4000))
            /*  Dividers are not chained */
            autoTuneConfig.snsClkInputClock = CYDEV_BCLK__HFCLK__KHZ >> `$INSTANCE_NAME`_FLIP_FLOP_DIV;
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
            /*  Dividers are not chained (PSoC 4000) */
            autoTuneConfig.snsClkInputClock = CYDEV_BCLK__HFCLK__KHZ >> `$INSTANCE_NAME`_FLIP_FLOP_DIV;
        #else
            /*  Dividers are chained (PSoC 4100, PSoC 4200) */
            autoTuneConfig.snsClkInputClock = (CYDEV_BCLK__HFCLK__KHZ / `$INSTANCE_NAME`_dsRam.modCsdClk) >> `$INSTANCE_NAME`_FLIP_FLOP_DIV;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

        /* If both CSD and CSX are enabled, calibrate widget using sensing method */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
            /* Initialize CSD mode */
            `$INSTANCE_NAME`_SsCSDInitialize();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) */

        /* Set flag to calibrate in PWM mode only */
        `$INSTANCE_NAME`_prescalersTuningDone = `$INSTANCE_NAME`_DISABLE;

        /* Switch charge clock source to direct clock mode */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
            `$INSTANCE_NAME`_SsSetCSD0DirectClockMode();
            `$INSTANCE_NAME`_SsSetCSD1DirectClockMode();
        #else
            `$INSTANCE_NAME`_SsSetDirectClockMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */


        /* Tune sense clock for all widgets */
        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                          `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
                    csdBlockID = `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].csdblk;

                    if (`$INSTANCE_NAME`_CSD0_BLOCK_ID == csdBlockID)
                    {
                        autoTuneConfig.iDacGain = `$INSTANCE_NAME`_CSD0_IDAC_GAIN_VALUE_NA * `$INSTANCE_NAME`_CSD_DUAL_IDAC_FACTOR;
                    }
                    else
                    {
                        autoTuneConfig.iDacGain = `$INSTANCE_NAME`_CSD1_IDAC_GAIN_VALUE_NA * `$INSTANCE_NAME`_CSD_DUAL_IDAC_FACTOR;
                    }
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

                /* Set calibration resolution to 12 bits */
                ptrWdgt->resolution = `$INSTANCE_NAME`_CALIBRATION_RESOLUTION;

                /* Set Sense clock frequency to 1.5 MHz */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
                    `$INSTANCE_NAME`_dsRam.snsCsdClk = (uint8)((uint32)autoTuneConfig.snsClkInputClock /
                                                       `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ);
                #elif (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
                    {
                        ptrWdgt->rowSnsClk = (uint16)((uint32)autoTuneConfig.snsClkInputClock /
                                             `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ);
                    }
                    ptrWdgt->snsClk = (uint16)((uint32)autoTuneConfig.snsClkInputClock /
                                      `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ);
                #else
                    ptrWdgt->snsClk = (uint16)((uint32)autoTuneConfig.snsClkInputClock /
                                      `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ);
                #endif /*  (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

                /* Calibrate CSD widget to 85% */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
                    (void)`$INSTANCE_NAME`_CSD2XCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                #else
                    (void)`$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
                    {
                        /* Get pointer to Modulator IDAC for columns */
                        autoTuneConfig.ptrModIDAC = &ptrWdgt->rowIdacMod[0u];

                        /* Get pointer to Sense Clock Divider for columns */
                        autoTuneConfig.ptrSenseClk = &ptrWdgt->rowSnsClk;

                        /* Find correct sense clock value */
                        cpRow = SmartSense_TunePrescalers(&autoTuneConfig);

                        if ((`$INSTANCE_NAME`_CP_MAX + `$INSTANCE_NAME`_CP_ERROR) <= cpRow)
                        {
                            autoTuneStatus = CYRET_BAD_DATA;
                        }

                        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                            /* Make sure that ModClk >= 4 * rowSnsClk for ModClk <= 12 MHz and rowSnsClk <= 6MHz */
                            if (autoTuneConfig.snsClkInputClock <= `$INSTANCE_NAME`_MOD_CSD_CLK_24000KHZ)
                            {
                                if (ptrWdgt->rowSnsClk < `$INSTANCE_NAME`_FACTOR_FILTER_DELAY_12MHZ)
                                {
                                    ptrWdgt->rowSnsClk = `$INSTANCE_NAME`_FACTOR_FILTER_DELAY_12MHZ;
                                }
                            }
                            else if (autoTuneConfig.snsClkInputClock <= `$INSTANCE_NAME`_MOD_CSD_CLK_48000KHZ)
                            {
                                if (ptrWdgt->rowSnsClk < `$INSTANCE_NAME`_FACTOR_MOD_SNS)
                                {
                                    ptrWdgt->rowSnsClk = `$INSTANCE_NAME`_FACTOR_MOD_SNS;
                                }
                            }
                            else
                            {
                                /* rowSnsClk is valid*/
                            }
                        #else
                            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
                                /* Make sure that ModClk >= 2 * rowSnsClk */
                                if (`$INSTANCE_NAME`_dsRam.modCsdClk >= ((uint8)(ptrWdgt->rowSnsClk << `$INSTANCE_NAME`_FLIP_FLOP_DIV)))
                                {
                                     ptrWdgt->rowSnsClk = `$INSTANCE_NAME`_dsRam.modCsdClk;
                                }
                            #else
                                /* Sense clock never equals to Modulator clock for chained dividers because of Flip Flop */
                            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
                        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
                    }
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

                /* Get pointer to Modulator IDAC  for rows */
                autoTuneConfig.ptrModIDAC = &ptrWdgt->idacMod[0u];

                /* Get pointer to Sense Clock Divider for columns */
                autoTuneConfig.ptrSenseClk = &ptrWdgt->snsClk;

                /* Find correct sense clock value */
                cp = SmartSense_TunePrescalers(&autoTuneConfig);

                if ((`$INSTANCE_NAME`_CP_MAX + `$INSTANCE_NAME`_CP_ERROR) <= cp)
                {
                    autoTuneStatus = CYRET_BAD_DATA;
                }

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                    /* Make sure that ModClk >= 4 * SnsClk for ModClk <= 12 MHz and SnsClk <= 6MHz */
                    if (autoTuneConfig.snsClkInputClock <= `$INSTANCE_NAME`_MOD_CSD_CLK_24000KHZ)
                    {
                        if (ptrWdgt->snsClk < `$INSTANCE_NAME`_FACTOR_FILTER_DELAY_12MHZ)
                        {
                            ptrWdgt->snsClk = `$INSTANCE_NAME`_FACTOR_FILTER_DELAY_12MHZ;
                        }
                    }
                    else if (autoTuneConfig.snsClkInputClock <= `$INSTANCE_NAME`_MOD_CSD_CLK_48000KHZ)
                    {
                        if (ptrWdgt->snsClk < `$INSTANCE_NAME`_FACTOR_MOD_SNS)
                        {
                            ptrWdgt->snsClk = `$INSTANCE_NAME`_FACTOR_MOD_SNS;
                        }
                    }
                    else
                    {
                        /* SnsClk is valid*/
                    }
                #else
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
                        /* Make sure that ModClk >= 2 * snsClk */
                        if (`$INSTANCE_NAME`_dsRam.modCsdClk >= ((uint8)(ptrWdgt->snsClk << `$INSTANCE_NAME`_FLIP_FLOP_DIV)))
                        {
                             ptrWdgt->snsClk = `$INSTANCE_NAME`_dsRam.modCsdClk;
                        }
                    #else
                        /* Sense clock never equals to Modulator clock for chained dividers because of Flip Flop */
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

                cpWidget[wdgtIndex] = cp;

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[(wdgtIndex)].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[(wdgtIndex)].wdgtType))
                    {
                        if (cpRow > cp)
                        {
                            cpWidget[wdgtIndex] = cpRow;
                        }
                    }
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
            }
        }

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
            `$INSTANCE_NAME`_SsSetEqualSlotClock();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

        /* Set flag to indicate that calibration in PWM mode has been performed */
        `$INSTANCE_NAME`_prescalersTuningDone = 1u;

        /* Multiply Clk divider to 2 for PRS mode to take into account average PRS frequency */
        autoTuneConfig.prsFactor = `$INSTANCE_NAME`_PRS_FACTOR_DIV;

        /* Tune sensitivity and resolution for all widgets */
        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                          `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;

                /* Get pointer to Modulator IDAC for rows */
                autoTuneConfig.ptrModIDAC = &ptrWdgt->idacMod[0u];

                /* Get pointer to maximum Sense Clock Divider (column or row) */
                autoTuneConfig.ptrSenseClk = &ptrWdgt->snsClk;

                /* Set parasitic capacitance for columns */
                autoTuneConfig.sensorCap = cpWidget[wdgtIndex];

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[(wdgtIndex)].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[(wdgtIndex)].wdgtType))

                    {
                        /* Set the minimum sense clock frequency to calculate the resolution */
                        if (ptrWdgt->snsClk < ptrWdgt->rowSnsClk)
                        {
                            /* Rewrite pointer to Sense Clock Divider for rows */
                            autoTuneConfig.ptrSenseClk = &ptrWdgt->rowSnsClk;

                            /* Set parasitic capacitance for rows */
                            autoTuneConfig.sensorCap = cpWidget[wdgtIndex];
                        }
                    }
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

                /* Get finger capacitance */
                autoTuneConfig.fingerCap = ptrWdgt->fingerCap;

                /* Init pointer to sigPFC */
                autoTuneConfig.sigPFC = &ptrWdgt->sigPFC;

                #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
                    `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(wdgtIndex, ptrWdgt);
                #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

                /* Calibrate CSD widget to 85% */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
                    autoTuneStatus |=`$INSTANCE_NAME`_CSD2XCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                #else
                    autoTuneStatus |= `$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */

                /* Find resolution */
                ptrWdgt->resolution = SmartSense_TuneSensitivity(&autoTuneConfig);

                #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
                    `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(wdgtIndex, ptrWdgt);

                    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                        if (((uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == ptrWdgt->snsClkSource) ||
                            ((uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == ptrWdgt->rowSnsClkSource))
                        {
                            /* Recalibrate CSD widget to 85% because source is changed to direct */
                            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
                                autoTuneStatus |= `$INSTANCE_NAME`_CSD2XCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                            #else
                                autoTuneStatus |= `$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
                        }
                    #else
                        if ((uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == ptrWdgt->snsClkSource)
                        {
                            /* Recalibrate CSD widget to 85% because source is changed to direct */
                            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)
                                autoTuneStatus |= `$INSTANCE_NAME`_CSD2XCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                            #else
                                autoTuneStatus |= `$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);
                            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
                        }
                    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
                #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
                    `$INSTANCE_NAME`_DsUpdateWidgetCrc(wdgtIndex);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */
            }
        }

        return autoTuneStatus;
    }
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)) */


#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG))
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsTrimIdacsSinking
        ****************************************************************************//**
        *
        * \brief
        *  This function loads trim values from SFLASH rows to calibrate
        *  IDAC1 and IDAC2 for Sinking CSD Mode
        *
        * \details
        *  Function reads trim value from SFLASH and loads it into IDAC trim register.
        *  If Compensation IDAC is disabled the function loads trim values for IDAC1 only.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsTrimIdacsSinking(void)
        {
            uint32 trimValue;

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)

                /* iDAC0 Sinking Mode */
                trimValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD0_TRIM2_PTR) & ~`$INSTANCE_NAME`_IDAC_TRIM2_MOD_SNK_MASK;
                trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD0_SFLASH_TRIM2_PTR) &
                                                          `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK) ;

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                    /* iDAC1 Sinking Mode */
                    trimValue &= ~`$INSTANCE_NAME`_IDAC_TRIM2_COMP_SNK_MASK;
                    trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD0_SFLASH_TRIM2_PTR) &
                                                              `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

                /* Update IDAC trim bits for gain control in current sink mode */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD0_TRIM2_PTR, trimValue);

                /* iDAC2 Sinking Mode */
                trimValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD1_TRIM2_PTR) & ~`$INSTANCE_NAME`_IDAC_TRIM2_MOD_SNK_MASK;
                trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD1_SFLASH_TRIM2_PTR) &
                                                          `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK) ;

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                    /* iDAC3 Sinking Mode */
                    trimValue &= ~`$INSTANCE_NAME`_IDAC_TRIM2_COMP_SNK_MASK;
                    trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD1_SFLASH_TRIM2_PTR) &
                                                              `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

                /* Update IDAC trim bits for gain control in current sink mode */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD1_TRIM2_PTR, trimValue);

            #else

                /* Mod iDAC Sinking Mode */
                trimValue = CY_GET_REG32(`$INSTANCE_NAME`_TRIM2_PTR) & ~`$INSTANCE_NAME`_IDAC_TRIM2_MOD_SNK_MASK;
                trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_SFLASH_TRIM2_PTR) &
                                                          `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK) ;

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                    /* Comp iDAC Sinking Mode */
                    trimValue &= ~`$INSTANCE_NAME`_IDAC_TRIM2_COMP_SNK_MASK;
                    trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_SFLASH_TRIM2_PTR) &
                                                              `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

                /* Update IDAC trim bits for gain control in current sink mode */
                CY_SET_REG32(`$INSTANCE_NAME`_TRIM2_PTR, trimValue);

            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)) */
        }
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */


    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG))
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsTrimIdacsSourcing
        ****************************************************************************//**
        *
        * \brief
        *  This function loads trim values from SFLASH rows to calibrate
        *  IDAC1 and IDAC2 for Sourcing CSD Mode
        *
        * \details
        *  Function reads trim value from SFLASH and loads it into IDAC trim register.
        *  If Compensation IDAC is disabled the function loads trim values for IDAC1 only.
        *
        *******************************************************************************/
        static void `$INSTANCE_NAME`_SsTrimIdacsSourcing(void)
        {
            uint32 trimValue;

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)

                /* iDAC0 Sourcing Mode */
                trimValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD0_TRIM1_PTR) & ~`$INSTANCE_NAME`_IDAC_TRIM1_MOD_SRC_MASK;
                trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD0_SFLASH_TRIM1_PTR) &
                                                          `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK);

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                     /* iDAC1 Sourcing Mode */
                    trimValue &= ~`$INSTANCE_NAME`_IDAC_TRIM1_COMP_SRC_MASK;
                    trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD0_SFLASH_TRIM1_PTR) &
                                                              `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

                /* Update IDAC trim bits for gain control in current source mode */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD0_TRIM1_PTR, trimValue);

                /* iDAC2 Sourcing Mode */
                trimValue = CY_GET_REG32(`$INSTANCE_NAME`_CSD1_TRIM1_PTR) & ~`$INSTANCE_NAME`_IDAC_TRIM1_MOD_SRC_MASK;
                trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD1_SFLASH_TRIM1_PTR) &
                                                          `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK);

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                     /* iDAC3 Sourcing Mode */
                    trimValue &= ~`$INSTANCE_NAME`_IDAC_TRIM1_COMP_SRC_MASK;
                    trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_CSD1_SFLASH_TRIM1_PTR) &
                                                              `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

                /* Update IDAC trim bits for gain control in current source mode */
                CY_SET_REG32(`$INSTANCE_NAME`_CSD1_TRIM1_PTR, trimValue);

            #else

                /* Mod iDAC Sourcing Mode */
                trimValue = CY_GET_REG32(`$INSTANCE_NAME`_TRIM1_PTR) & ~`$INSTANCE_NAME`_IDAC_TRIM1_MOD_SRC_MASK;
                trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_SFLASH_TRIM1_PTR) &
                                                          `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_MOD_MASK);

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
                     /* Comp iDAC Sourcing Mode */
                    trimValue &= ~`$INSTANCE_NAME`_IDAC_TRIM1_COMP_SRC_MASK;
                    trimValue |= ((uint32)CY_GET_REG8(`$INSTANCE_NAME`_SFLASH_TRIM1_PTR) &
                                                              `$INSTANCE_NAME`_SFLASH_TRIM_IDAC_COMP_MASK);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) */

                /* Update IDAC trim bits for gain control in current source mode */
                CY_SET_REG32(`$INSTANCE_NAME`_TRIM1_PTR, trimValue);

            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) */
        }
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsTrimIdacs
    ****************************************************************************//**
    *
    * \brief
    *  This function loads trim values from SFLASH rows to calibrate
    *  IDAC1 and IDAC2 for CSD Mode
    *
    * \details
    *  If CSX mode is enabled the function loads trim values for both sink and source
    *  mode. If CSX mode is disabled the function loads trim values for sink or
    *  source mode based on sink/source mode configuration.
    *  If Compensation IDAC is disabled the function loads trim values for IDAC1 only.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsTrimIdacs(void)
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            `$INSTANCE_NAME`_SsTrimIdacsSinking();
            `$INSTANCE_NAME`_SsTrimIdacsSourcing();
        #elif (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            `$INSTANCE_NAME`_SsTrimIdacsSinking();
        #elif (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            `$INSTANCE_NAME`_SsTrimIdacsSourcing();
        #else
            #error "Not supported Mode, component cannot work in this mode"
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
    }
#endif  /* (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2) */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsChangeImoFreq
    ****************************************************************************//**
    *
    * \brief
    *  This function changes the IMO frequency.
    *
    * \details
    *   The IMO frequency can have three offsets: 0%, -5% and +5%. The frequency
    *   trims are contained in the `$INSTANCE_NAME`_immunity[value] array for each
    *   frequency channel.
    *
    * \param value The frequency channel ID.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SsChangeImoFreq(uint32 value)
    {
        CY_SET_REG32(CY_SYS_CLK_IMO_TRIM1_PTR, `$INSTANCE_NAME`_immunity[value]);
    }
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */


#if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsInitializeSourceSenseClk
****************************************************************************//**
*
* \brief
*  Sets a source for Sense Clk for all CSD widgets.
*
* \details
*  Updates snsClkSource and rowSnsClkSource with a source for the sense Clk.
*  for all CSD widgets.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsInitializeSourceSenseClk(void)
{
    uint32 wdgtIndex;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

    for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
    {
        ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;
        if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
        `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
        {
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))
                `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(wdgtIndex, ptrWdgt);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || `$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)) */
        }
        else
        {
            #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
                `$INSTANCE_NAME`_SsSetWidgetTxClkSrc(wdgtIndex, ptrWdgt);
            #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)) */
        }
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
            `$INSTANCE_NAME`_DsUpdateWidgetCrc(wdgtIndex);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */
    }
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN) ||\
           ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))) */


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc
    ****************************************************************************//**
    *
    * \brief
    *  Sets a source for the sense clock for a widget.
    *
    * \param wdgtIndex
    *   Specifies the ID of the widget.
    * \param ptrWdgt
    *   The pointer to the RAM_WD_BASE_STRUCT structure.
    *
    * \details
    *  Updates snsClkSource and rowSnsClkSource with a source for the sense Clk for a
    *  widget.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(uint32 wdgtIndex, `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * ptrWdgt)
    {
        uint8 lfsrSize;
        uint8 lfsrScale;

        #if(`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                uint32 conversionsNum;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
            uint32 snsClkDivider;
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

        #if(`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
            snsClkDivider = `$INSTANCE_NAME`_SsCSDGetColSnsClkDivider(wdgtIndex);

            #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                conversionsNum = `$INSTANCE_NAME`_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution,
                                                                                             `$INSTANCE_NAME`_CLK_SOURCE_DIRECT);
                lfsrSize = `$INSTANCE_NAME`_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == lfsrSize)
                {
                    lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider, (uint32)ptrWdgt->resolution);
                }
                lfsrScale = `$INSTANCE_NAME`_SsCalcLfsrScale(snsClkDivider, lfsrSize);
            #else
                lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider, (uint32)ptrWdgt->resolution);
                lfsrScale = 0u;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        #else
            lfsrSize = (uint8)`$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
            lfsrScale = 0u;
            (void)wdgtIndex; /* This parameter is unused in such configurations */
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

        ptrWdgt->snsClkSource = lfsrSize | (uint8)(lfsrScale << `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET);

        #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
            if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
            {
                #if(`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
                    snsClkDivider = `$INSTANCE_NAME`_SsCSDGetRowSnsClkDivider(wdgtIndex);

                    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                        lfsrSize = `$INSTANCE_NAME`_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                        if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == lfsrSize)
                        {
                            lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider, (uint32)ptrWdgt->resolution);
                        }
                        lfsrScale = `$INSTANCE_NAME`_SsCalcLfsrScale(snsClkDivider, lfsrSize);
                    #else
                        lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider, (uint32)ptrWdgt->resolution);
                        lfsrScale = 0u;
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
                #else
                    lfsrSize = (uint8)`$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
                    lfsrScale = 0u;
                #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
                ptrWdgt->rowSnsClkSource = lfsrSize | (uint8)(lfsrScale << `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET);
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */
    }
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))*/


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsSetWidgetTxClkSrc
    ****************************************************************************//**
    *
    * \brief
    *  Sets a source for the Tx clock for a widget.
    *
    * \param wdgtIndex
    *   Specifies the ID of the widget.
    * \param ptrWdgt
    *   The pointer to the RAM_WD_BASE_STRUCT structure.
    *
    * \details
    *  Updates snsClkSourcewith with a source for Tx Clk for a widget.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsSetWidgetTxClkSrc(uint32 wdgtIndex, `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * ptrWdgt)
    {
        uint8 lfsrSize;
        uint8 lfsrScale;

        #if ((`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE) && \
             (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES))
            uint32 conversionsNum;
            uint32 snsClkDivider;
        #endif

        #if(`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)
            #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)
                conversionsNum = (uint32)ptrWdgt->resolution;
                snsClkDivider = `$INSTANCE_NAME`_SsCSXGetTxClkDivider(wdgtIndex);
                lfsrSize = `$INSTANCE_NAME`_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                lfsrScale = `$INSTANCE_NAME`_SsCalcLfsrScale(snsClkDivider, lfsrSize);
            #else
                lfsrSize = (uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT;
                lfsrScale = 0u;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
        #else
            lfsrSize = (uint8)`$INSTANCE_NAME`_CSX_TX_CLK_SOURCE;
            lfsrScale = 0u;
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE) */

        ptrWdgt->snsClkSource = lfsrSize | (uint8)(lfsrScale << `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET);
    }
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)) */


#if(((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDCalcLfsr
****************************************************************************//**
*
* \brief
*   This is an internal function that finds a SSC polynomial size in the Auto mode.
*
* \details
*   The SSC polynomial size in the auto mode is found based on the following
*   requirements:
*   - an LFSR value should be selected so that the max clock dither is limited with +/-10%.
*   - at least one full spread spectrum polynomial should pass during the scan time.
*   - the value of the number of conversions should be an integer multiple of the
*     repeat period of the programmed LFSR_SIZE.
*
* \param
*  snsClkDivider The divider value for the sense clock.
*  resolution The widget resolution.
*
* \return lfsrSize The LFSRSIZE value for the SENSE_PERIOD register.
*
*******************************************************************************/
static CY_INLINE  uint8 `$INSTANCE_NAME`_SsCalcLfsrSize(uint32 snsClkDivider, uint32 conversionsNum)
{
    uint8 lfsrSize = 0u;

    /* Find LFSR value */
    if((`$INSTANCE_NAME`_SNSCLK_SSC4_THRESHOLD <= snsClkDivider) &&
       (`$INSTANCE_NAME`_SNSCLK_SSC4_PERIOD <= conversionsNum) &&
       (0uL == (conversionsNum % `$INSTANCE_NAME`_SNSCLK_SSC4_PERIOD)))
    {
        lfsrSize = `$INSTANCE_NAME`_CLK_SOURCE_SSC4;
    }
    else if((`$INSTANCE_NAME`_SNSCLK_SSC3_THRESHOLD <= snsClkDivider) &&
            (`$INSTANCE_NAME`_SNSCLK_SSC3_PERIOD <= conversionsNum) &&
            (0uL == (conversionsNum % `$INSTANCE_NAME`_SNSCLK_SSC3_PERIOD)))
    {
        lfsrSize = `$INSTANCE_NAME`_CLK_SOURCE_SSC3;
    }
    else if((`$INSTANCE_NAME`_SNSCLK_SSC2_THRESHOLD <= snsClkDivider) &&
            (`$INSTANCE_NAME`_SNSCLK_SSC2_PERIOD <= conversionsNum) &&
            (0uL == (conversionsNum % `$INSTANCE_NAME`_SNSCLK_SSC2_PERIOD)))
    {
        lfsrSize = `$INSTANCE_NAME`_CLK_SOURCE_SSC2;
    }
    else if((`$INSTANCE_NAME`_SNSCLK_SSC1_THRESHOLD <= snsClkDivider) &&
            (`$INSTANCE_NAME`_SNSCLK_SSC1_PERIOD <= conversionsNum) &&
            (0uL == (conversionsNum % `$INSTANCE_NAME`_SNSCLK_SSC1_PERIOD)))
    {
        lfsrSize = `$INSTANCE_NAME`_CLK_SOURCE_SSC1;
    }
    else
    {
        lfsrSize = (uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT;
    }

    return (lfsrSize);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCSDCalcLfsr
****************************************************************************//**
*
* \brief
*   This is an internal function that calculates the LFSR scale value.
*
* \details
*   The LFSR scale value is used to increase the clock dither if the desired dither
*   is wider than can be achieved with the current Sense Clock Divider and current LFSR
*   period.
*
*   This returns the LFSR scale value needed to keep the clock dither in
*   range +/-10%.
*
* \param
*  snsClkDivider The divider value for the sense clock.
*  lfsrSize The period of the LFSR sequence.
*           For devices with `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN = TRUE, the
*           mode parameters can take the following values:
*           `$INSTANCE_NAME`_CLK_SOURCE_DIRECT The spreadspectrum is not used.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC1   The length of LFSR sequence is 63 cycles.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC2   The length of LFSR sequence is 127 cycles.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC3   The length of LFSR sequence is 255 cycles.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC4   The length of LFSR sequence is 511 cycles.
*
*           For devices with `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN = TRUE, the
*           mode parameters can take the following values:
*           `$INSTANCE_NAME`_CLK_SOURCE_DIRECT The spreadspectrum is not used.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC1   The length of LFSR sequence is 3 cycles.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC2   The length of LFSR sequence is 7 cycles.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC3   The length of LFSR sequence is 15 cycles.
*           `$INSTANCE_NAME`_CLK_SOURCE_SSC4   The length of LFSR sequence is 31 cycles.
*
* \return The LFSR scale value needed to keep the clock dither in range +/-10%.
*
*******************************************************************************/
static CY_INLINE uint8 `$INSTANCE_NAME`_SsCalcLfsrScale(uint32 snsClkDivider, uint8 lfsrSize)
{
    uint32 lfsrScale;
    uint32 lfsrRange;
    uint32 lfsrDither;

    /* Initialize the lfsrSize variable with the LFSR Range for given Lfsr Size. */
    switch(lfsrSize)
    {
        case `$INSTANCE_NAME`_CLK_SOURCE_SSC1:
        {
            lfsrRange = `$INSTANCE_NAME`_SNSCLK_SSC1_RANGE;
            break;
        }
        case `$INSTANCE_NAME`_CLK_SOURCE_SSC2:
        {
            lfsrRange = `$INSTANCE_NAME`_SNSCLK_SSC2_RANGE;
            break;
        }
        case `$INSTANCE_NAME`_CLK_SOURCE_SSC3:
        {
            lfsrRange = `$INSTANCE_NAME`_SNSCLK_SSC3_RANGE;
            break;
        }
        case `$INSTANCE_NAME`_CLK_SOURCE_SSC4:
        {
            lfsrRange = `$INSTANCE_NAME`_SNSCLK_SSC4_RANGE;
            break;
        }
        default:
        {
            lfsrRange = 0u;
            break;
        }
    }

    /* Calculate the LFSR Scale value that is required to keep the Clock dither
     * as close as possible to the +/-10% limit of the used frequency.
     */
    if((lfsrSize != `$INSTANCE_NAME`_CLK_SOURCE_DIRECT) && (0u != lfsrRange))
    {
        /* Calculate the LFSR Dither in percents. */
        lfsrDither  = ((lfsrRange * 100uL) / snsClkDivider);
        lfsrScale = 0uL;

        while(lfsrDither < `$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE)
        {
            lfsrScale++;
            lfsrDither <<=1uL;
        }

        if(lfsrDither > `$INSTANCE_NAME`_LFSR_DITHER_PERCENTAGE)
        {
            lfsrScale--;
        }
    }
    else
    {
        lfsrScale = 0uL;
    }

    return ((uint8)lfsrScale);
}
#endif /* (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) &&  \
            (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) &&  \
            (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)) ||\
          ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) &&  \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) &&  \
           (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))) */


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
    (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsClearCSDSensors
    ****************************************************************************//**
    *
    * \brief
    *  Resets all the CSD sensors to the non-sampling state by sequentially
    *  disconnecting all the sensors from the Analog MUX bus and putting them to
    *  an inactive state.
    *
    * \details
    *   The function goes through all the widgets and updates appropriate bits in
    *   the IO HSIOM, PC and DR registers depending on the Inactive sensor connection
    *   parameter. DR register bits are set to zero when the Inactive sensor
    *   connection is Ground or Hi-Z.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SsClearCSDSensors(void)
    {
        uint32 wdgtIndex;
        uint32 snsIndex;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            uint32 pinIndex;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            /* Declare ptr to sensor IO structure */
            `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curDedicatedSnsIOPtr;
            /*  Pointer to Flash structure holding info of sensor to be scanned  */
            `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */
        `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curSnsIOPtr;

        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash;

                /* Go through all sensors in widget */
                for (snsIndex = 0u; snsIndex < (uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[(wdgtIndex)].totalNumSns; snsIndex++)
                {
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
                        /* Check ganged sns flag  */
                        if (`$INSTANCE_NAME`_GANGED_SNS_MASK == (`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].staticConfig &
                                                                 `$INSTANCE_NAME`_GANGED_SNS_MASK))
                        {
                            /* Get sns pointer */
                            curFlashSnsPtr = (`$INSTANCE_NAME`_FLASH_SNS_STRUCT const *)
                                                               `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash +
                                                               snsIndex;

                            for(pinIndex = 0u; pinIndex < curFlashSnsPtr->numPins; pinIndex++)
                            {
                                /* Get IO pointer for dedicated pin */
                                curDedicatedSnsIOPtr = &`$INSTANCE_NAME`_ioList[curFlashSnsPtr->firstPinId + pinIndex];

                                /* Disconnect dedicated pin */
                                `$INSTANCE_NAME`_CSDDisconnectSns(curDedicatedSnsIOPtr);
                            }
                        }
                        else
                        {
                            /* Disable sensor */
                            `$INSTANCE_NAME`_CSDDisconnectSns(&curSnsIOPtr[snsIndex]);
                        }
                    #else
                        /* Disable sensor */
                        `$INSTANCE_NAME`_CSDDisconnectSns(&curSnsIOPtr[snsIndex]);
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)  */
                }
            }
        }
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsCSDGetColSnsClkDivider
    ****************************************************************************//**
    *
    * \brief
    *  This function gets the Sense Clock Divider value for one-dimension widgets
    *  and Column Sense Clock divider value for two-dimension widgets.
    *
    * \details
    *  This function gets the Sense Clock Divider value based on the component
    *  configuration. The function is applicable for one-dimension widgets and for
    *  two-dimension widgets.
    *
    * \param widgetId
    *  Specifies the ID of the widget.
    *
    * \return The Sense Clock Divider value for one-dimension widgets
    *         and the Column Sense Clock divider value for two-dimension widgets.
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_SsCSDGetColSnsClkDivider(uint32 widgetId)
    {
        uint32 retVal;

        /* Get sense divider based on configuration */
        #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
            `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

            ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
            `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

            retVal = (uint32)(ptrWdgt->snsClk);
        #else
            retVal = (uint32)`$INSTANCE_NAME`_dsRam.snsCsdClk;

            (void)widgetId; /* This parameter is unused in such configurations */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

        return (retVal);
    }


    #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN))
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDGetRowSnsClkDivider
        ****************************************************************************//**
        *
        * \brief
        *  This function gets the Sense Clock Divider value for one-dimension widgets
        *  and the Column Sense Clock divider value for two-dimension widgets.
        *
        * \details
        *  This function gets the Sense Clock Divider value based on the component
        *  configuration. The function is applicable for one-dimension widgets and for
        *  two-dimension widgets.
        *
        * \param
        *  widgetId Specifies the ID of the widget.
        *
        * \return The Sense Clock Divider value for one-dimension widgets
        *         and Column Sense Clock divider value for two-dimension widgets.
        *
        *******************************************************************************/
        uint32 `$INSTANCE_NAME`_SsCSDGetRowSnsClkDivider(uint32 widgetId)
        {
            uint32 retVal;

            /* Get sense divider based on configuration */
            #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
                `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;

                ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;

                retVal = ptrWdgt->rowSnsClk;
            #else
                retVal = (uint32)`$INSTANCE_NAME`_dsRam.snsCsdClk;

                (void)widgetId; /* This parameter is unused in such configurations */
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

            return (retVal);
        }
    #endif /* (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN | `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)) */

    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDCalcPrsSize
        ****************************************************************************//**
        *
        * \brief
        *   The function finds PRS polynomial size in the Auto mode.
        *
        * \details
        *   The PRS polynomial size in the Auto mode is found based on the following
        *   requirements:
        *   - at least one full spread spectrum polynomial should pass during scan time.
        *
        * \param
        *  snsClkDivider The divider value for the sense clock.
        *  resolution The widget resolution.
        *
        * \return prsSize PRS value for SENSE_PERIOD register.
        *
        *******************************************************************************/
        uint8 `$INSTANCE_NAME`_SsCSDCalcPrsSize(uint32 snsClkDivider, uint32 resolution)
        {
            uint32 prsSize;
            uint32 modClkDivider;

            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                modClkDivider = 1uL;
            #else
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
                    modClkDivider = (uint32)`$INSTANCE_NAME`_dsRam.modCsdClk;
                #else
                    modClkDivider = 1uL;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) */
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

            if ((snsClkDivider * `$INSTANCE_NAME`_PRS_LENGTH_12_BITS) <
                (modClkDivider * ((0x00000001Lu << resolution) - 1u)))
            {
                /* Set PRS12 mode */
                prsSize = `$INSTANCE_NAME`_PRS_12_CONFIG;
            }
            else if ((snsClkDivider * `$INSTANCE_NAME`_PRS_LENGTH_8_BITS) <
                     (modClkDivider * ((0x00000001Lu << resolution) - 1u)))
            {
                /* Set PRS8 mode */
                prsSize = `$INSTANCE_NAME`_PRS_8_CONFIG;
            }
            else
            {
                /* Set Direct clock mode */
                prsSize = `$INSTANCE_NAME`_CLK_SOURCE_DIRECT;
            }

            return (uint8)prsSize;
        }
    #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD2X_EN)) */


/* [] END OF FILE */
