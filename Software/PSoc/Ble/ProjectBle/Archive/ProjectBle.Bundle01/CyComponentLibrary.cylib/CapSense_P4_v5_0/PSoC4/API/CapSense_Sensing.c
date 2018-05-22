/***************************************************************************//**
* \file `$INSTANCE_NAME`_Sensing.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file contains the source of functions common for
*   different sensing methods.
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

#include "cyfitter.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
    #include "`$INSTANCE_NAME`_SensingCSX_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
    #include "`$INSTANCE_NAME`_SensingISX_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    #include "`$INSTANCE_NAME`_SensingCSD_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    #include "`$INSTANCE_NAME`_SmartSense_LL.h"
#endif  /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)
    #include "`$INSTANCE_NAME`_Adc.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

#if (0u != `$INSTANCE_NAME`_ISX_EN)
    #include "`$INSTANCE_NAME`_DigPrt2.h"
    #if (`$INSTANCE_NAME`_USES_PORT_3)
        #include "`$INSTANCE_NAME`_DigPrt3.h"
    #endif
#endif /* (0u != `$INSTANCE_NAME`_ISX_EN) */
/***************************************
* API Constants
***************************************/

#define `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_MIN               (0u)
#define `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_MAX               (255u)
#define `$INSTANCE_NAME`_CALIBRATION_RESOLUTION                 (12u)
#define `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ                   (1500u)
#define `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL                 (`$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL)
#define `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_UNITS                 (1000u)
#define `$INSTANCE_NAME`_CP_MIN                                 (0u)
#define `$INSTANCE_NAME`_CP_MAX                                 (65000Lu)
#define `$INSTANCE_NAME`_CP_ERROR                               (4000Lu)
#define `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET           (4u)

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    #define `$INSTANCE_NAME`_CSD_SNS_FREQ_KHZ_MAX               (6000u)
#else
    #define `$INSTANCE_NAME`_CSD_SNS_FREQ_KHZ_MAX               (12600u)
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#define `$INSTANCE_NAME`_FLIP_FLOP_DIV                          (1u)

#define `$INSTANCE_NAME`_MOD_CSD_CLK_12000KHZ                   (12000uL)
#define `$INSTANCE_NAME`_MOD_CSD_CLK_24000KHZ                   (24000uL)
#define `$INSTANCE_NAME`_MOD_CSD_CLK_48000KHZ                   (48000uL)

/*****************************************************************************/
/* Enumeration types definition                                              */
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
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
    static void `$INSTANCE_NAME`_SsTrimIdacs(void);
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) || \
         (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG))
        static void `$INSTANCE_NAME`_SsTrimIdacsSinking(void);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) || \
         (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG))
        static void `$INSTANCE_NAME`_SsTrimIdacsSourcing(void);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    static void `$INSTANCE_NAME`_SsCSDDisableMode(void);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
    static void `$INSTANCE_NAME`_SsDisableCSXMode(void);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
    static void `$INSTANCE_NAME`_SsDisableISXMode(void);
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */

#if(((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE) && \
     (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)))
    static uint8 `$INSTANCE_NAME`_SsCalcLfsrSize(uint32 snsClkDivider, uint32 conversionsNum);
    static uint8 `$INSTANCE_NAME`_SsCalcLfsrScale(uint32 snsClkDivider, uint8 lfsrSize);
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    static void `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(uint32 wdgtIndex, `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * ptrWdgt);
#endif

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
    static void `$INSTANCE_NAME`_SsSetWidgetTxClkSrc(uint32 wdgtIndex, `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * ptrWdgt);
#endif

/** \}
* \endcond */

/*******************************************************************************
* Defines module variables
*******************************************************************************/

`$INSTANCE_NAME`_SENSE_METHOD_ENUM `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_UNDEFINED_E;

#if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
    /* Module variable keep track of multi-frequency scan channel index */
    uint8 `$INSTANCE_NAME`_scanFreqIndex = 0u;
    /* Variable keep frequency offsets */
    uint8 `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_NUM_SCAN_FREQS] = {0u, 0u, 0u};
#else
    /* const allows C-compiler to do optimization */
    const uint8 `$INSTANCE_NAME`_scanFreqIndex = 0u;
#endif

/* Global software variables */
volatile uint8 `$INSTANCE_NAME`_widgetIndex = 0u;    /* Index of the scanning widget */
volatile uint8 `$INSTANCE_NAME`_sensorIndex = 0u;    /* Index of the scanning sensor */
uint8 `$INSTANCE_NAME`_requestScanAllWidget = 0u;

/* Pointer to RAM_SNS_STRUCT structure */
`$INSTANCE_NAME`_RAM_SNS_STRUCT *`$INSTANCE_NAME`_curRamSnsPtr;

#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN))
    /* Pointer to Flash structure holding configuration of widget to be scanned */
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *`$INSTANCE_NAME`_curFlashWdgtPtr = 0u;
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
    /* Pointer to Flash structure holding info of sensor to be scanned */
    `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *`$INSTANCE_NAME`_curFlashSnsPtr = 0u;
#endif

/* Pointer to Flash structure to hold Sns electrode that was connected previously */
`$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curSnsIOPtr;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsBusy
****************************************************************************//**
*
* \brief
*  Returns the current status of the Component (Scan is completed or Scan is in
*  progress).
*
* \details
*  This function returns a status of the hardware block whether a scan is
*  currently in progress or not. If the Component is busy, no new scan or setup
*  widgets is made. The critical section (i.e. disable global interrupt)
*  is recommended for the application when the device transitions from
*  the active mode to sleep or deep sleep modes.
*
* \return
*  Returns the current status of the Component:
*    - `$INSTANCE_NAME`_NOT_BUSY - No scan is in progress and a next scan
*      can be initiated.
*    - `$INSTANCE_NAME`_SW_STS_BUSY - The previous scanning is not completed
*      and the hardware block is busy.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsBusy(void)
{
    return (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetupWidget
****************************************************************************//**
*
* \brief
*  Performs the initialization required to scan the specified widget.
*
* \details
*  This function prepares the Component to scan all the sensors in the specified
*  widget by executing the following tasks:
*    1. Re-initialize the hardware if it is not configured to perform the
*       sensing method used by the specified widget, this happens only if multiple
*       sensing methods are used in the Component.
*    2. Initialize the hardware with specific sensing configuration (e.g.
*       sensor clock, scan resolution) used by the widget.
*    3. Disconnect all previously connected electrodes, if the electrodes
*       connected by the
*       \if SECTION_C_HIGH_LEVEL
*       `$INSTANCE_NAME`_CSDSetupWidgetExt(), `$INSTANCE_NAME`_CSXSetupWidgetExt(),
*       `$INSTANCE_NAME`_CSDConnectSns() functions and not disconnected.
*       \endif
*       \if SECTION_I_REP
*       `$INSTANCE_NAME`_ISXSetupWidgetExt() function and not disconnected.
*       \endif
*
*  This function does not start sensor scanning, the `$INSTANCE_NAME`_Scan()
*  function must be called to start the scan sensors in the widget. If this
*  function is called more than once, it does not break the Component operation,
*  but only the last initialized widget is in effect.
*
* \param widgetId
*  Specifies the ID number of the widget to be initialized for scanning.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \return
*  Returns the status of the widget setting up operation:
*    - CYRET_SUCCESS - The operation is successfully completed.
*    - CYRET_BAD_PARAM - The widget is invalid or if the specified widget is
*      disabled
*    - CYRET_INVALID_STATE - The previous scanning is not completed and the
*      hardware block is busy.
*    - CYRET_UNKNOWN - An unknown sensing method is used by the widget or any
*      other spurious error occurred.
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
    else if ((`$INSTANCE_NAME`_TOTAL_WIDGETS > widgetId) &&
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
        switch (`$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
        {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                /* Set up widget for CSX scan */
                `$INSTANCE_NAME`_CSXSetupWidget(widgetId);
                break;
        #endif
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                /* Set up widget for CSD scan */
                `$INSTANCE_NAME`_CSDSetupWidget(widgetId);
                break;
        #endif
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_ISX_E:
                /* Set up widget for ISX scan */
                `$INSTANCE_NAME`_ISXSetupWidget(widgetId);
                break;
        #endif
        default:
            /* Sensing method is invalid, return error to caller */
            widgetStatus = CYRET_UNKNOWN;
            break;
        }
    }
    return (widgetStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Scan
****************************************************************************//**
*
* \brief
*  Initiates scanning of all the sensors in the widget initialized by
*  `$INSTANCE_NAME`_SetupWidget(), if no scan is in progress.
*
* \details
*  This function is called only after the `$INSTANCE_NAME`_SetupWidget()
*  function is called to start the scanning of the sensors in the widget. The
*  status of a sensor scan must be checked using the `$INSTANCE_NAME`_IsBusy()
*  API prior to starting a next scan or setting up another widget.
*
* \return
*  Returns the status of the scan initiation operation:
*  - CYRET_SUCCESS - Scanning is successfully started.
*  - CYRET_INVALID_STATE - The previous scanning is not completed and the
*    hardware block is busy.
*  - CYRET_UNKNOWN - An unknown sensing method is used by the widget.
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
        switch (`$INSTANCE_NAME`_currentSenseMethod)
        {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                `$INSTANCE_NAME`_CSXScan();
                break;
        #endif
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                `$INSTANCE_NAME`_CSDScan();
                break;
        #endif
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_ISX_E:
                `$INSTANCE_NAME`_ISXScan();
                break;
        #endif
        default:
            scanStatus = CYRET_UNKNOWN;
            break;
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ScanAllWidgets
****************************************************************************//**
*
* \brief
*  Initializes the first enabled widget and scanning of all the sensors in the
*  widget, then the same process is repeated for all the widgets in the Component,
*  i.e. scanning of all the widgets in the Component.
*
* \details
*  This function initializes a widget and scans all the sensors in the widget,
*  and then repeats the same for all the widgets in the Component. The tasks of
*  the `$INSTANCE_NAME`_SetupWidget() and `$INSTANCE_NAME`_Scan() functions are
*  executed by these functions. The status of a sensor scan must be checked
*  using the `$INSTANCE_NAME`_IsBusy() API prior to starting a next scan
*  or setting up another widget.
*
* \return
*  Returns the status of the operation:
*  - CYRET_SUCCESS - Scanning is successfully started.
*  - CYRET_BAD_PARAM - All the widgets are disabled.
*  - CYRET_INVALID_STATE - The previous scanning is not completed and the HW block is busy.
*  - CYRET_UNKNOWN - There are unknown errors.
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
             wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS;
             wdgtIndex++)
        {

            scanStatus = `$INSTANCE_NAME`_SetupWidget(wdgtIndex);

            if (CYRET_SUCCESS == scanStatus)
            {
                #if (0u != (`$INSTANCE_NAME`_TOTAL_WIDGETS - 1u))
                    /* If there are more than one widget to be scanned, request callback to scan next widget */
                    if ((`$INSTANCE_NAME`_TOTAL_WIDGETS - 1u) > wdgtIndex)
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
                #endif  /* (0u != (`$INSTANCE_NAME`_TOTAL_WIDGETS - 1u)) */

                /* Initiate scan and quit loop */
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
*  Performs hardware and firmware initialization required for proper operation
*  of the `$INSTANCE_NAME` Component. This function is called from
*  the `$INSTANCE_NAME`_Start() API prior to calling any other APIs of the Component.
*
* \details
*  Performs hardware and firmware initialization required for proper operation
*  of the `$INSTANCE_NAME` Component. This function is called from
*  the `$INSTANCE_NAME`_Start() API prior to calling any other APIs of the Component.
*  1. Depending on the configuration, the function initializes the CSD block
*     for the corresponding sensing mode.
*  2. The function updates the dsRam.wdgtWorking variable with 1 when Self-test
*     is enabled.
*
*  Calling the `$INSTANCE_NAME`_Start API is the recommended method to initialize
*  the `$INSTANCE_NAME` Component at power-up. The `$INSTANCE_NAME`_SsInitialize()
*  API should not be used for initialization, resume, or wake-up operations.
*  The dsRam.wdgtWorking variable is updated.
*
* \return status
*  Returns status of operation:
*  - Zero        - Indicates successful initialization.
*  - Non-zero    - One or more errors occurred in the initialization process.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SsInitialize(void)
{
    cystatus initStatus;

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) &&\
         (`$INSTANCE_NAME`_MFS_IMO == `$INSTANCE_NAME`_MFS_METHOD))
        uint8 centerFreqTrim;

        centerFreqTrim = (uint8)CY_GET_REG32(CY_SYS_CLK_IMO_TRIM1_PTR);
        `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_0] = centerFreqTrim;

        if (centerFreqTrim < `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1)
        {
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = centerFreqTrim + `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1;
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = centerFreqTrim + (`$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1 +
                                                                                           `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F2);
        }
        else if (centerFreqTrim > (`$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_MAX - `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F2))
        {
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = centerFreqTrim - `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1;
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = centerFreqTrim - (`$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1 +
                                                                                           `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F2);
        }
        else
        {
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_1] = centerFreqTrim - `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F1;
            `$INSTANCE_NAME`_immunity[`$INSTANCE_NAME`_FREQ_CHANNEL_2] = centerFreqTrim + `$INSTANCE_NAME`_IMO_FREQUENCY_OFFSET_F2;
        }

    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) &&\
               (`$INSTANCE_NAME`_MFS_IMO == `$INSTANCE_NAME`_MFS_METHOD)) */

    initStatus = CYRET_SUCCESS;

    #if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
        `$INSTANCE_NAME`_SsTrimIdacs();
    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

    #if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)))
        `$INSTANCE_NAME`_SsInitializeSourceSenseClk();
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) ||\
              ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))) */

    /* Set all IO states to the default state */
    `$INSTANCE_NAME`_SsSetIOsInDefaultState();

    #if (`$INSTANCE_NAME`_DISABLE != `$INSTANCE_NAME`_USES_MANY_SENSE_MODES)
        /* Initialize CSD block for ADC scanning */
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_UNDEFINED_E);
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
        /* Initialize CSD block for CSD scanning */
        `$INSTANCE_NAME`_SsCSDInitialize();
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_CSD_E);
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
        /* Initialize CSD block for CSX scanning */
        `$INSTANCE_NAME`_CSXInitialize();
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_CSX_E);
    #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
        /* Initialize CSD block for ISX scanning */
        `$INSTANCE_NAME`_ISXInitialize();
        `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_ISX_E);
    #else
        #error "No sensing method enabled, Component cannot work in this mode"
        initStatus = CYRET_UNKNOWN;
    #endif

    return (initStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPinState
****************************************************************************//**
*
* \brief
*  Sets the state (drive mode and output state) of the port pin used by a sensor.
*  The possible states are GND, Shield, High-Z, Tx or Rx, Sensor. If the sensor
*  specified in the input parameter is a ganged sensor, then the state of all pins
*  associated with the ganged sensor is updated.
*
* \details
*  This function sets a specified state for a specified sensor element. For the
*  CSD widgets, sensor element is a sensor ID, for the CSX widgets, it is either
*  an Rx or Tx electrode ID. If the specified sensor is a ganged sensor, then
*  the specified state is set for all the electrodes belong to the sensor.
*  This function must not be called while the Component is in the busy state.
*
*  This function accepts the `$INSTANCE_NAME`_SHIELD and
*  `$INSTANCE_NAME`_SENSOR states as an input only if there is at least
*  one CSD widget. Similarly, this function accepts the `$INSTANCE_NAME`_TX_PIN
*  and `$INSTANCE_NAME`_RX_PIN states as an input only if there is at least
*  one CSX widget in the project.

*  Calling this function directly from the application layer is not
*  recommended. This function is used to implement only the custom-specific
*  use cases. Functions that perform a setup and scan of a sensor/widget
*  automatically set the required pin states. They ignore changes
*  in the design made by the `$INSTANCE_NAME`_SetPinState() function.
*  This function neither check wdgtIndex nor sensorElement for the correctness.
*
* \param widgetId
*  Specifies the ID of the widget to change the pin state of the specified
*  sensor.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration
*  header file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param sensorElement
*  Specifies the ID of the sensor element within the widget to change
*  its pin state.
*  \if SECTION_C_LOW_LEVEL
*  For the CSD widgets, sensorElement is the sensor ID and can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  - `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*  For the CSX widgets, sensorElement is defined either as Rx ID or Tx ID.
*  The first Rx in a widget corresponds to sensorElement = 0, the second
*  Rx in a widget corresponds to sensorElement = 1, and so on.
*  The last Tx in a widget corresponds to sensorElement = (RxNum + TxNum).
*  \endif
*  Macros for Rx and Tx IDs can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as:
*  - `$INSTANCE_NAME`_<WidgetName>_RX<RXNumber>_ID
*  - `$INSTANCE_NAME`_<WidgetName>_TX<TXNumber>_ID.
*
* \param state
*  Specifies the state of the sensor to be set:
*     1. `$INSTANCE_NAME`_GROUND - The pin is connected to the ground.
*     2. `$INSTANCE_NAME`_HIGHZ - The drive mode of the pin is set to High-Z
*        Analog.
*     3. `$INSTANCE_NAME`_SHIELD - The shield signal is routed to the pin
*        (available only if CSD sensing method with shield electrode is enabled).
*     4. `$INSTANCE_NAME`_SENSOR - The pin is connected to the scanning bus
*        (available only if CSD sensing method is enabled).
*     5. `$INSTANCE_NAME`_TX_PIN - The Tx signal is routed to the sensor
*        (available only if CSX sensing method is enabled).
*     6. `$INSTANCE_NAME`_RX_PIN - The pin is connected to the scanning bus
*        (available only if CSX sensing method is enabled).
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
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_SHIELD_EN) */
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */

        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
             (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN))
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
    *  1. Disconnect Cmod from AMUXBUS-A.
    *  2. Disconnect previous CSX electrode if it has been connected.
    *  3. Disconnect Csh from AMUXBUS-B.
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
    *  1. Disconnect CintA and CintB from AMUXBUS-A.
    *  2. Disconnect previous CSX electrode if it has been connected.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsDisableCSXMode(void)
    {
        uint32 newRegValue;

        /* Disconnect CintA from AMUXBUS-A using HSIOM registers */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintA_HSIOM_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, newRegValue);

        /* Disconnect CintB from AMUXBUS-A using HSIOM registers */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintB_HSIOM_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, newRegValue);

        /* Disconnect previous CSX electrode if it has been connected */
        `$INSTANCE_NAME`_CSXElectrodeCheck();
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsDisableISXMode
    ****************************************************************************//**
    *
    * \brief
    *  This function disables ISX mode.
    *
    * \details
    *  To disable ISX mode the following tasks are performed:
    *  1. Disconnect CintA and CintB from AMUXBUS-A
    *  2. Disconnect previous ISX electrode if it has been connected
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_SsDisableISXMode(void)
    {
        uint32 newRegValue;

        /* Disconnect CintA from AMUXBUS-A using HSIOM registers.   */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintA_HSIOM_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, newRegValue);

        /* Disconnect CintB from AMUXBUS-A using HSIOM registers.   */
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_CintB_HSIOM_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, newRegValue);

        /* Disconnect previous ISX electrode if it has been connected */
        `$INSTANCE_NAME`_ISXElectrodeCheck();
        `$INSTANCE_NAME`_DigPrt2_Stop();
        #if (`$INSTANCE_NAME`_USES_PORT_3)
            `$INSTANCE_NAME`_DigPrt3_Stop();
        #endif /* `$INSTANCE_NAME`_USES_PORT_3 */
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */

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
*  1. Disconnect CintA and CintB from AMUXBUS-A.
*  2. Disconnect previous CSD electrode if it has been connected.
*  3. Initialize CSD mode.
*
*  To switch to the CSX mode the following tasks are performed:
*  1. Disconnect Cmod from AMUXBUS-A.
*  2. Disconnect previous CSX electrode if it has been connected.
*  3. Initialize CSX mode.
*
* \param mode
*  Specifies the scan mode:
*  - `$INSTANCE_NAME`_SENSE_METHOD_CSD_E
*  - `$INSTANCE_NAME`_SENSE_METHOD_CSX_E
*  - `$INSTANCE_NAME`_SENSE_METHOD_ISX_E
*  - `$INSTANCE_NAME`_SENSE_METHOD_BIST_E
*  - `$INSTANCE_NAME`_UNDEFINED_E
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_ENUM mode)
{
    if (`$INSTANCE_NAME`_currentSenseMethod != mode)
    {
        /* The requested mode differes to the current one. Disable the current mode */
        if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E == `$INSTANCE_NAME`_currentSenseMethod)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                `$INSTANCE_NAME`_SsCSDDisableMode();
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
        }
        else if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_currentSenseMethod)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                `$INSTANCE_NAME`_SsDisableCSXMode();
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
        }
        else if (`$INSTANCE_NAME`_SENSE_METHOD_ISX_E == `$INSTANCE_NAME`_currentSenseMethod)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
                `$INSTANCE_NAME`_SsDisableISXMode();
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */
        }
        else if (`$INSTANCE_NAME`_SENSE_METHOD_BIST_E == `$INSTANCE_NAME`_currentSenseMethod)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
                `$INSTANCE_NAME`_BistDisableMode();
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */
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
        else if (`$INSTANCE_NAME`_SENSE_METHOD_ISX_E == mode)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
                /* Initialize ISX mode to guarantee configured ISX mode */
                `$INSTANCE_NAME`_ISXInitialize();
                `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_SENSE_METHOD_ISX_E;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */
        }
        else if (`$INSTANCE_NAME`_SENSE_METHOD_BIST_E == mode)
        {
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
                `$INSTANCE_NAME`_BistInitialize();
                `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_SENSE_METHOD_BIST_E;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */
        }
        else
        {
            `$INSTANCE_NAME`_currentSenseMethod = `$INSTANCE_NAME`_UNDEFINED_E;
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsSetIOsInDefaultState
****************************************************************************//**
*
* \brief
*  Sets all electrodes into a default state.
*
* \details
*  Sets all the CSD/CSX IOs into a default state:
*  - HSIOM   - Disconnected, the GPIO mode.
*  - DM      - Strong drive.
*  - State   - Zero.
*
*  Sets all the ADC channels into a default state:
*  - HSIOM   - Disconnected, the GPIO mode.
*  - DM      - HiZ-Analog.
*  - State   - Zero.
*
*  It is not recommended to call this function directly from the application
*  layer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetIOsInDefaultState(void)
{
    `$INSTANCE_NAME`_FLASH_IO_STRUCT const *ioPtr = &`$INSTANCE_NAME`_ioList[0u];
    uint32 loopIndex;
    uint32 regValue;

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < `$INSTANCE_NAME`_TOTAL_ELECTRODES; loopIndex++)
    {
        /*
        * 1. Disconnect HSIOM.
        * 2. Set strong DM.
        * 3. Set pin state to logic 0.
        */
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

        /* Get next electrode */
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
*  This function sets the resources that do not belong to the sensing HW block to
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
*  Returns the status of the operation:
*  - Zero        - Resources released successfully.
*  - Non-zero    - One or more errors occurred in releasing process.
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

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
            `$INSTANCE_NAME`_SsDisableISXMode();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */

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
*  The ISR function for multiple widget scanning implementation.
*
* \details
*  This is the function used by the `$INSTANCE_NAME` ISR to implement multiple widget
*  scanning.
*  Should not be used by the application layer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsPostAllWidgetsScan(void)
{
    /*
    *  1. Increment widget index
    *  2. Check if all the widgets are scanned
    *  3. If all the widgets are not scanned, set up and scan next widget
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
                        /* Disable the CSD block */
                        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_configCsd);
                    }
                #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_BLOCK_OFF_AFTER_SCAN_EN) && \
                           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)) */

                /* Update scan Counter */
                `$INSTANCE_NAME`_dsRam.scanCounter++;
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
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsIsrInitialize
****************************************************************************//**
*
* \brief
*  Enables and initializes for the function pointer for a callback for the ISR.
*
* \details
*  The "address" is a special type cyisraddress defined by Cylib. This function
*  is used by Component APIs and should not be used by an application program for
*  proper working of the Component.
*
* \param address
*  The address of the function to be called when interrupt is fired.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsIsrInitialize(cyisraddress address)
{
    `$INSTANCE_NAME`_ISR_StartEx(address);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsSetModClkClockDivider
****************************************************************************//**
*
* \brief
*  Sets the divider values for the modulator clock and then starts
*  the modulator clock.
*
* \details
*  It is not recommended to call this function directly by the application layer.
*  It is used by initialization, widget APIs or wakeup functions to
*  enable the clocks.
*
* \param modClk
*  The divider value for the modulator clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetModClkClockDivider(uint32 modClk)
{
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
    /* Stop modulator clock */
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

    /* Check whether previous modulator clock start command has finished. */
    while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_MODCLK_CMD_PTR) & `$INSTANCE_NAME`_MODCLK_CMD_ENABLE_MASK))
    {
        /* Wait until previous modulator clock start command has finished */
    }

    /* Start modulator clock, aligned to HFCLK */
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
*  Sets the divider values for the sense clock and then starts
*  the sense clock.
*
* \details
*  It is not recommended to call this function directly by the application layer.
*  It is used by initialization, widget APIs or wakeup functions to
*  enable the clocks.
*
* \param
*  snsClk The divider value for the sense clock.
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
        /* Stop sense clock clock   */
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

        /* Check whether previous sense clock start command has finished. */
        while(0u != (CY_GET_REG32(`$INSTANCE_NAME`_SNSCLK_CMD_PTR) & `$INSTANCE_NAME`_SNSCLK_CMD_ENABLE_MASK))
        {
            /* Wait until previous sense clock start command has finished. */
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
*  Sets the divider values for sense and modulator clocks and then starts
*  a modulator clock-phase aligned to HFCLK and sense clock-phase aligned to
*  the modulator clock.
*
* \details
*  It is not recommended to call this function directly by the application layer.
*  It is used by initialization, widget APIs or wakeup functions to
*  enable the clocks.
*
* \param
*  snsClk The divider value for the sense clock.
*  modClk The divider value for the modulator clock.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SsSetClockDividers(uint32 snsClk, uint32 modClk)
{
    /* Configure Mod clock */
    `$INSTANCE_NAME`_SsSetModClkClockDivider(modClk);

    /* Configure Sns clock */
    `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClk);
}


#if (`$INSTANCE_NAME`_ANYMODE_AUTOCAL)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CalibrateWidget
    ****************************************************************************//**
    *
    * \brief
    *  Calibrates the IDACs for all the sensors in the specified widget to the default
    *  target, this function detects the sensing method used by the
    *  widget prior to calibration.
    *
    * \details
    *  This function performs exactly the same tasks as
    *  `$INSTANCE_NAME`_CalibrateAllWidgets, but only for a specified widget.
    *  This function detects the sensing method used by the widgets and uses
    *  the Enable compensation IDAC parameter. 
    *  \if SECTION_I_REP
    *  For ISX mode, the frequency is also calibrated.
    *  \endif
    *
    *  \if SECTION_C_LOW_LEVEL
    *  This function is available when the CSD and/or CSX Enable IDAC
    *  auto-calibration parameter is enabled.
    *  \endif
    *  \if SECTION_I_REP
    *  This function is available when the ISX Enable auto-calibration parameter
    *  is enabled.
    *  \endif
    *
    * \param widgetId
    *  Specifies the ID number of the widget to calibrate its raw count.
    *  A macro for the widget ID can be found in the
    *  `$INSTANCE_NAME` Configuration header file defined as
    *  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
    *
    * \return
    *  Returns the status of the specified widget calibration:
    *  - CYRET_SUCCESS - The operation is successfully completed.
    *  - CYRET_BAD_PARAM - The input parameter is invalid.
    *  - CYRET_BAD_DATA - The calibration failed and the Component may not
    *    operate as expected.
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

            /* If both CSD and CSX are enabled, calibrate widget using sensing method */
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
                /* Check widget sensing method and call appropriate APIs */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_IDAC_AUTOCAL_EN)
                    if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E ==
                        `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
                    {
                        /* Calibrate CSX widget */
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

            /* If only CSD is enabled, calibrate CSD sensor */
            #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
                calibrateStatus = `$INSTANCE_NAME`_CSDCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSD_RAWCOUNT_CAL_LEVEL);

            /* If only CSX is enabled, call CSX scan */
            #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                `$INSTANCE_NAME`_CSXCalibrateWidget(widgetId, `$INSTANCE_NAME`_CSX_RAWCOUNT_CAL_LEVEL);

            /* If only ISX is enabled, call ISX scan */
            #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
                `$INSTANCE_NAME`_ISXCalibrateWidget(widgetId, `$INSTANCE_NAME`_ISX_RAWCOUNT_CAL_LEVEL);

            #else
                calibrateStatus = CYRET_UNKNOWN;
            #endif

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
    *  Calibrates the IDACs for all the widgets in the Component to the default
    *  target, this function detects the sensing method used by the widgets
    *  prior to calibration.
    *
    * \details
    *  Calibrates the IDACs for all the widgets in the Component to the default
    *  target value. This function detects the sensing method used by the widgets
    *  and regards the Enable compensation IDAC parameter.
    *  \if SECTION_I_REP
    *  For ISX mode, the frequency is also calibrated.
    *  \endif
    *
    *  \cond SECTION_C_LOW_LEVEL
    *  This function is available when the CSD and/or CSX Enable IDAC
    *  auto-calibration parameter is enabled.
    *  \endcond
    *  \if SECTION_I_REP
    *  This function is available when the ISX Enable Auto-calibration parameter
    *  is enabled.
    *  \endif
    *
    * \return
    *  Returns the status of the calibration process:
    *  - CYRET_SUCCESS - The operation is successfully completed.
    *  - CYRET_BAD_DATA - The calibration failed and the Component may not
    *    operate as expected.
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
#endif /* (`$INSTANCE_NAME`_ANYMODE_AUTOCAL) */


#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
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
    *    2*5*R*Cp.
    *  - Calculates the resolution for the optimal finger capacitance.
    *
    * \return
    *  Returns the status of the operation:
    *  - Zero     - All the widgets are auto-tuned successfully.
    *  - Non-zero - Auto-tuning failed for any widget.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_SsAutoTune(void)
    {
        cystatus autoTuneStatus = CYRET_SUCCESS;
        uint32 wdgtIndex;

        uint32 cp = 0uL;
        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            uint32 cpRow = 0uL;
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

        uint32 cpWidget[`$INSTANCE_NAME`_TOTAL_WIDGETS];
        `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt;
        AUTO_TUNE_CONFIG_TYPE autoTuneConfig;

        /* Configure common config variables */
        autoTuneConfig.snsClkConstantR = `$INSTANCE_NAME`_CSD_SNSCLK_R_CONST;
        autoTuneConfig.vRef = `$INSTANCE_NAME`_CSD_VREF_MV;
        autoTuneConfig.iDacGain = `$INSTANCE_NAME`_CSD_IDAC_GAIN_VALUE_NA;

        /* Calculate snsClk Input Clock in KHz */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
            /* Dividers are chained (Fourth-generation HW block). Flip flop is not available */
            autoTuneConfig.snsClkInputClock = (CYDEV_BCLK__HFCLK__KHZ / `$INSTANCE_NAME`_dsRam.modCsdClk);
        #elif ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK) && (`$INSTANCE_NAME`_DISABLE == CY_PSOC4_4000))
            /* Dividers are not chained */
            autoTuneConfig.snsClkInputClock = CYDEV_BCLK__HFCLK__KHZ >> `$INSTANCE_NAME`_FLIP_FLOP_DIV;
        #elif (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
            /* Dividers are not chained (PSoC 4000) */
            autoTuneConfig.snsClkInputClock = CYDEV_BCLK__HFCLK__KHZ >> `$INSTANCE_NAME`_FLIP_FLOP_DIV;
        #else
            /* Dividers are chained (PSoC 4100, PSoC 4200) */
            autoTuneConfig.snsClkInputClock = (CYDEV_BCLK__HFCLK__KHZ / `$INSTANCE_NAME`_dsRam.modCsdClk) >> `$INSTANCE_NAME`_FLIP_FLOP_DIV;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

        /* If both CSD and CSX are enabled, calibrate widget using sensing method */
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN)
            /* Initialize CSD mode */
            `$INSTANCE_NAME`_SsCSDInitialize();
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_CSX_EN) */

        /*
        * Autotune phase #1:
        * - performing the first calibration at fixed settings
        * - getting sensor Cp
        * - getting sense clock frequency based on Cp
        */

        /* Tune sense clock for all the widgets */
        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                          `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;

                /* Set calibration resolution to 12 bits */
                ptrWdgt->resolution = `$INSTANCE_NAME`_CALIBRATION_RESOLUTION;

                /* Set clock source direct and sense clock frequency to 1.5 MHz */
                ptrWdgt->snsClkSource = (uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT;
                ptrWdgt->snsClk = (uint16)((uint32)autoTuneConfig.snsClkInputClock / `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ);
                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
                    {
                        ptrWdgt->rowSnsClkSource = (uint8)`$INSTANCE_NAME`_CLK_SOURCE_DIRECT;
                        ptrWdgt->rowSnsClk = (uint16)((uint32)autoTuneConfig.snsClkInputClock / `$INSTANCE_NAME`_CALIBRATION_FREQ_KHZ);
                    }
                #endif

                /* Calibrate CSD widget to the default calibration target */
                (void)`$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
                    {
                        /* Get pointer to Sense Clock Divider for columns */
                        autoTuneConfig.ptrSenseClk = &ptrWdgt->rowSnsClk;

                        /* Get IDAC */
                        autoTuneConfig.iDac = `$INSTANCE_NAME`_calibratedIdacRow;

                        /* Calculate achived calibration level */
                        autoTuneConfig.calTarget = (uint16)(((uint32)`$INSTANCE_NAME`_calibratedRawcountRow * `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_UNITS) /
                                ((uint32)(0x01uL << `$INSTANCE_NAME`_CALIBRATION_RESOLUTION) - 1u));

                        /* Find correct sense clock value */
                        cpRow = SmartSense_TunePrescalers(&autoTuneConfig);

                        if ((`$INSTANCE_NAME`_CP_MAX + `$INSTANCE_NAME`_CP_ERROR) <= cpRow)
                        {
                            autoTuneStatus = CYRET_BAD_DATA;
                        }

                        /*
                        * Multiply the sense Clock Divider by 2 while the desired Sense Clock Frequency is greater
                        * than maximum supported Sense Clock Frequency.
                        */
                        while((((uint32)autoTuneConfig.snsClkInputClock) > ((uint32)ptrWdgt->snsClk * `$INSTANCE_NAME`_CSD_SNS_FREQ_KHZ_MAX)) ||
                                (`$INSTANCE_NAME`_MIN_SNS_CLK_DIVIDER > ptrWdgt->snsClk))
                        {
                            ptrWdgt->snsClk <<= 1u;
                        }

                        #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2)
                            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
                                /* Make sure that ModClk >= 2 * rowSnsClk */
                                if (`$INSTANCE_NAME`_dsRam.modCsdClk >= ((uint8)(ptrWdgt->rowSnsClk << `$INSTANCE_NAME`_FLIP_FLOP_DIV)))
                                {
                                     ptrWdgt->rowSnsClk = `$INSTANCE_NAME`_dsRam.modCsdClk;
                                }
                            #else
                                /* Sense clock never equals to Modulator clock for chained dividers because of Flip Flop */
                            #endif
                        #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2) */
                    }
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

                /* Get pointer to Sense Clock Divider for columns */
                autoTuneConfig.ptrSenseClk = &ptrWdgt->snsClk;

                /* Get IDAC */
                autoTuneConfig.iDac = `$INSTANCE_NAME`_calibratedIdac;

                /* Calculate achived calibration level */
                autoTuneConfig.calTarget = (uint16)(((uint32)`$INSTANCE_NAME`_calibratedRawcount * `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_UNITS) /
                        ((uint32)(0x01uL << `$INSTANCE_NAME`_CALIBRATION_RESOLUTION) - 1u));

                /* Find correct sense clock value */
                cp = SmartSense_TunePrescalers(&autoTuneConfig);

                if ((`$INSTANCE_NAME`_CP_MAX + `$INSTANCE_NAME`_CP_ERROR) <= cp)
                {
                    autoTuneStatus = CYRET_BAD_DATA;
                }

                /*
                * Multiply the sense Clock Divider by 2 while the desired Sense Clock Frequency is greater
                * than MAX supported Sense Clock Frequency.
                */
                while((((uint32)autoTuneConfig.snsClkInputClock) > ((uint32)ptrWdgt->snsClk * `$INSTANCE_NAME`_CSD_SNS_FREQ_KHZ_MAX)) ||
                        (`$INSTANCE_NAME`_MIN_SNS_CLK_DIVIDER > ptrWdgt->snsClk))
                {
                    ptrWdgt->snsClk <<= 1u;
                }

                #if (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2)
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK)
                        /* Make sure that ModClk >= 2 * snsClk */
                        if (`$INSTANCE_NAME`_dsRam.modCsdClk >= ((uint8)(ptrWdgt->snsClk << `$INSTANCE_NAME`_FLIP_FLOP_DIV)))
                        {
                             ptrWdgt->snsClk = `$INSTANCE_NAME`_dsRam.modCsdClk;
                        }
                    #else
                        /* Sense clock never equals to Modulator clock for chained dividers because of Flip Flop */
                    #endif
                #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2) */

                cpWidget[wdgtIndex] = cp;

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
                    {
                        if (cpRow > cp)
                        {
                            cpWidget[wdgtIndex] = cpRow;
                        }
                    }
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
            }
            else
            {
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN)
                    /* Non-CSD widget */
                    cpWidget[wdgtIndex] = 1u;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) */
            }
        }

        /*
        * Autotune phase #2:
        * - repeating calibration with new sense clock frequency
        * - getting resolution
        */

        /* Tune resolution for all the widgets */
        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                          `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;

                /* Calibrate CSD widget to the default calibration target */
                autoTuneStatus |= `$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);

                /* Get pointer to Sense Clock Divider (column or row) */
                autoTuneConfig.ptrSenseClk = &ptrWdgt->snsClk;

                /* Set parasitic capacitance for columns */
                autoTuneConfig.sensorCap = cpWidget[wdgtIndex];

                /* Get IDAC */
                autoTuneConfig.iDac = `$INSTANCE_NAME`_calibratedIdac;

                #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                    if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                        (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))

                    {
                        /* Set the minimum sense clock frequency to calculate the resolution */
                        if (ptrWdgt->snsClk < ptrWdgt->rowSnsClk)
                        {
                            /* Rewrite pointer to Sense Clock Divider for rows */
                            autoTuneConfig.ptrSenseClk = &ptrWdgt->rowSnsClk;

                            /* Set parasitic capacitance for rows */
                            autoTuneConfig.sensorCap = cpWidget[wdgtIndex];

                            /* Get IDAC */
                            autoTuneConfig.iDac = `$INSTANCE_NAME`_calibratedIdacRow;
                        }
                    }
                #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

                /* Get finger capacitance */
                autoTuneConfig.fingerCap = ptrWdgt->fingerCap;

                /* Init pointer to sigPFC */
                autoTuneConfig.sigPFC = &ptrWdgt->sigPFC;

                /* Find resolution */
                ptrWdgt->resolution = SmartSense_TuneSensitivity(&autoTuneConfig);
            }
        }

        /*
        * Autotune phase #3:
        * - selecting a widget clock source if AUTO
        * - repeating calibration with found clock frequency, resolution and clock source
        * - updating sensitivity
        */

        /* Tune sensitivity for all the widgets */
        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                          `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2WdgtRam;

                `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(wdgtIndex, ptrWdgt);

                /* Calibrate CSD widget to the default calibration target */
                autoTuneStatus |= `$INSTANCE_NAME`_CSDCalibrateWidget(wdgtIndex, `$INSTANCE_NAME`_CSD_AUTOTUNE_CAL_LEVEL);

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
                    `$INSTANCE_NAME`_DsUpdateWidgetCrc(wdgtIndex);
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */
            }
        }

        return autoTuneStatus;
    }
#endif /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)) */


#if (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSDV2)
    #if ( ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) \
        || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)) ||\
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
        }
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
               (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)) */


    #if ( ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) \
        || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)) || \
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
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)
            `$INSTANCE_NAME`_SsTrimIdacsSinking();
            `$INSTANCE_NAME`_SsTrimIdacsSourcing();
        #elif (`$INSTANCE_NAME`_IDAC_SINKING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            `$INSTANCE_NAME`_SsTrimIdacsSinking();
        #elif (`$INSTANCE_NAME`_IDAC_SOURCING == `$INSTANCE_NAME`_CSD_IDAC_CONFIG)
            `$INSTANCE_NAME`_SsTrimIdacsSourcing();
        #else
            #error "Not supported Mode, Component cannot work in this mode"
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN) */
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
    *  The IMO frequency can have three offsets: 0%, -5% and +5%. The frequency
    *  trims are contained in the `$INSTANCE_NAME`_immunity[value] array for each
    *  frequency channel.
    *
    * \param value The frequency channel ID.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SsChangeImoFreq(uint32 value)
    {
        CY_SET_REG32(CY_SYS_CLK_IMO_TRIM1_PTR, `$INSTANCE_NAME`_immunity[value]);
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsChangeClkFreq
    ****************************************************************************//**
    *
    * \brief
    *  This function changes the sensor clock frequency by configuring
    *  the corresponding divider.
    *
    * \details
    *  This function changes the sensor clock frequency by configuring
    *  the corresponding divider.
    *
    * \param chId
    *  The frequency channel ID.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SsChangeClkFreq(uint32 chId)
    {
        uint32 snsClkDivider;
        uint32 freqOffset1 = 0u;
        uint32 freqOffset2 = 0u;

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                uint32 conversionsNum;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

            #if((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
                (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
                (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
                uint32 snsClkSrc;
            #endif
        #endif

        #if ((0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) || \
             ((`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) && (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)))
            `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex];
            `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)ptrFlashWdgt->ptr2WdgtRam;
        #endif

        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex]))
        {
        #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                /* Get sensor clock divider value */
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
                    snsClkDivider = `$INSTANCE_NAME`_dsRam.snsCsdClk;
                #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */
                    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                        /* Get SnsClck divider for rows or columns */
                        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].numCols <= `$INSTANCE_NAME`_sensorIndex)
                        {
                            snsClkDivider = ptrWdgt->rowSnsClk;
                        }
                        else
                        {
                            snsClkDivider = ptrWdgt->snsClk;
                        }
                    #else
                        snsClkDivider = ptrWdgt->snsClk;
                    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */

                freqOffset1 = `$INSTANCE_NAME`_CSD_MFS_DIVIDER_OFFSET_F1;
                freqOffset2 = `$INSTANCE_NAME`_CSD_MFS_DIVIDER_OFFSET_F2;

                #if((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
                    (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
                    (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
                    /* Get sense clk source */
                    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
                        /* Get SnsClc Source for rows or columns */
                        if (`$INSTANCE_NAME`_dsFlash.wdgtArray[`$INSTANCE_NAME`_widgetIndex].numCols <= `$INSTANCE_NAME`_sensorIndex)
                        {
                            snsClkSrc = (uint32)ptrWdgt->rowSnsClkSource;
                        }
                        else
                        {
                            snsClkSrc = (uint32)ptrWdgt->snsClkSource;
                        }
                    #else
                        snsClkSrc = (uint32)ptrWdgt->snsClkSource;
                    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

                    switch (snsClkSrc)
                    {
                    case `$INSTANCE_NAME`_CLK_SOURCE_PRS8:
                    case `$INSTANCE_NAME`_CLK_SOURCE_PRS12:
                        /* Multiply by 2 for PRS8/PRS12 mode */
                        freqOffset1 <<= 1u;
                        freqOffset2 <<= 1u;
                        break;

                    default:
                        break;
                    }
                #endif

                /* Change the divider based on the chId */
                switch (chId)
                {
                    case `$INSTANCE_NAME`_FREQ_CHANNEL_1:
                    {
                        snsClkDivider += freqOffset1;
                        break;
                    }
                    case `$INSTANCE_NAME`_FREQ_CHANNEL_2:
                    {
                        snsClkDivider += freqOffset2;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                    /* Set Number Of Conversions based on scanning resolution */
                    conversionsNum = `$INSTANCE_NAME`_SsCSDGetNumberOfConversions(snsClkDivider, (uint32)ptrWdgt->resolution, (uint32)ptrWdgt->snsClkSource);
                    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_NORM_CNT_PTR, (conversionsNum & `$INSTANCE_NAME`_SEQ_NORM_CNT_CONV_CNT_MASK));
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */

                #if((`$INSTANCE_NAME`_CLK_SOURCE_PRS8  == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
                    (`$INSTANCE_NAME`_CLK_SOURCE_PRS12 == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) ||\
                    (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))
                    switch (snsClkSrc)
                    {
                    case `$INSTANCE_NAME`_CLK_SOURCE_PRS8:
                    case `$INSTANCE_NAME`_CLK_SOURCE_PRS12:
                        /* Divide by 2 for PRS8/PRS12 mode */
                        snsClkDivider >>= 1;
                        if (snsClkDivider == 0u)
                        {
                            snsClkDivider = 1u;
                        }
                        break;

                    default:
                        break;
                    }
                #endif

                /* Configure the new divider */
                `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);

                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

        #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
                    snsClkDivider = `$INSTANCE_NAME`_dsRam.snsCsxClk;
                #else /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) */
                    snsClkDivider = ptrWdgt->snsClk;
                #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) */
                freqOffset1 = `$INSTANCE_NAME`_CSX_MFS_DIVIDER_OFFSET_F1;
                freqOffset2 = `$INSTANCE_NAME`_CSX_MFS_DIVIDER_OFFSET_F2;

                /* Change the divider based on the chId */
                switch (chId)
                {
                    case `$INSTANCE_NAME`_FREQ_CHANNEL_1:
                    {
                        snsClkDivider += freqOffset1;
                        break;
                    }
                    case `$INSTANCE_NAME`_FREQ_CHANNEL_2:
                    {
                        snsClkDivider += freqOffset2;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                /* Configure the new divider */
                `$INSTANCE_NAME`_SsSetSnsClockDivider(snsClkDivider);

                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS) */

        default:
            CYASSERT(0);
            break;
        }
    }
#endif  /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */


#if((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || \
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)))
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

        switch (`$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
        {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc(wdgtIndex, ptrWdgt);
                break;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */
        #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                `$INSTANCE_NAME`_SsSetWidgetTxClkSrc(wdgtIndex, ptrWdgt);
                break;
        #endif /* (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)) */
        default:
            break;
        }
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
            `$INSTANCE_NAME`_DsUpdateWidgetCrc(wdgtIndex);
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */
    }
}
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) || \
           (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ISX_EN)) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))) */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsSetWidgetSenseClkSrc
    ****************************************************************************//**
    *
    * \brief
    *  Sets a source for the sense clock for a widget.
    *
    * \param wdgtIndex
    *  Specifies the ID of the widget.
    * \param ptrWdgt
    *  The pointer to the RAM_WD_BASE_STRUCT structure.
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
                    /*
                    * Multiplying of the snsClkDivider by 2 is needed to pass the
                    * average PRS frequency through the argument.
                    */
                    lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                }
                lfsrScale = `$INSTANCE_NAME`_SsCalcLfsrScale(snsClkDivider, lfsrSize);
            #else
                /*
                * Multiplying of the snsClkDivider by 2 is needed to pass the
                * average PRS frequency through the argument.
                */
                lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                lfsrScale = 0u;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
        #else
            lfsrSize = (uint8)`$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
            lfsrScale = 0u;
            (void)wdgtIndex; /* This parameter is unused in such configurations */
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */

        ptrWdgt->snsClkSource = lfsrSize | (uint8)(lfsrScale << `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET);

        #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            if ((`$INSTANCE_NAME`_WD_TOUCHPAD_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType) ||
                (`$INSTANCE_NAME`_WD_MATRIX_BUTTON_E == (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].wdgtType))
            {
                #if(`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
                    snsClkDivider = `$INSTANCE_NAME`_SsCSDGetRowSnsClkDivider(wdgtIndex);

                    #if(`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
                        lfsrSize = `$INSTANCE_NAME`_SsCalcLfsrSize(snsClkDivider, conversionsNum);
                        if (`$INSTANCE_NAME`_CLK_SOURCE_DIRECT == lfsrSize)
                        {
                            /*
                            * Multiplying of the snsClkDivider by 2 is needed to pass the
                            * average PRS frequency through the argument.
                            */
                            lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                        }
                        lfsrScale = `$INSTANCE_NAME`_SsCalcLfsrScale(snsClkDivider, lfsrSize);
                    #else
                        /*
                        * Multiplying of the snsClkDivider by 2 is needed to pass the
                        * average PRS frequency through the argument.
                        */
                        lfsrSize = `$INSTANCE_NAME`_SsCSDCalcPrsSize(snsClkDivider << 1uL, (uint32)ptrWdgt->resolution);
                        lfsrScale = 0u;
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */
                #else
                    lfsrSize = (uint8)`$INSTANCE_NAME`_DEFAULT_MODULATION_MODE;
                    lfsrScale = 0u;
                #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE) */
                ptrWdgt->rowSnsClkSource = lfsrSize | (uint8)(lfsrScale << `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET);
            }
        #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


#if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2))
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SsSetWidgetTxClkSrc
    ****************************************************************************//**
    *
    * \brief
    *  Sets a source for the Tx clock for a widget.
    *
    * \param wdgtIndex
    *  Specifies the ID of the widget.
    * \param ptrWdgt
    *  The pointer to the RAM_WD_BASE_STRUCT structure.
    *
    * \details
    *  Updates snsClkSource with a source for Tx Clk for a widget.
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
                /* Unused function argument */
                (void)wdgtIndex;
            #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) */
        #else
            lfsrSize = (uint8)`$INSTANCE_NAME`_CSX_TX_CLK_SOURCE;
            lfsrScale = 0u;
            /* Unused function argument */
            (void)wdgtIndex;
        #endif /* (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE) */

        ptrWdgt->snsClkSource = lfsrSize | (uint8)(lfsrScale << `$INSTANCE_NAME`_CLK_SOURCE_LFSR_SCALE_OFFSET);
    }
#endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)) */


#if(((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
     (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)) ||\
    ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
     (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
     (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)))
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsCalcLfsrSize
****************************************************************************//**
*
* \brief
*  This is an internal function that finds a SSC polynomial size in the Auto mode.
*
* \details
*  The SSC polynomial size in the auto mode is found based on the following
*  requirements:
*  - an LFSR value should be selected so that the max clock dither is limited with +/-10%.
*  - at least one full spread spectrum polynomial should pass during the scan time.
*  - the value of the number of conversions should be an integer multiple of the
*    repeat period of the programmed LFSR_SIZE.
*
* \param
*  snsClkDivider The divider value for the sense clock.
*  resolution The widget resolution.
*
* \return lfsrSize The LFSRSIZE value for the SENSE_PERIOD register.
*
*******************************************************************************/
static uint8 `$INSTANCE_NAME`_SsCalcLfsrSize(uint32 snsClkDivider, uint32 conversionsNum)
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
* Function Name: `$INSTANCE_NAME`_SsCalcLfsrScale
****************************************************************************//**
*
* \brief
*  This is an internal function that calculates the LFSR scale value.
*
* \details
*  The LFSR scale value is used to increase the clock dither if the desired dither
*  is wider than can be achieved with the current Sense Clock Divider and current LFSR
*  period.
*
*  This returns the LFSR scale value needed to keep the clock dither in
*  range +/-10%.
*
* \param
*  snsClkDivider The divider value for the sense clock.
*  lfsrSize The period of the LFSR sequence.
*          For devices with `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN = TRUE, the
*          mode parameters can take the following values:
*          `$INSTANCE_NAME`_CLK_SOURCE_DIRECT The spreadspectrum is not used.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC1   The length of LFSR sequence is 63 cycles.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC2   The length of LFSR sequence is 127 cycles.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC3   The length of LFSR sequence is 255 cycles.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC4   The length of LFSR sequence is 511 cycles.
*
*          For devices with `$INSTANCE_NAME`_CSDV2_REF9P6UA_EN = TRUE, the
*          mode parameters can take the following values:
*          `$INSTANCE_NAME`_CLK_SOURCE_DIRECT The spreadspectrum is not used.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC1   The length of LFSR sequence is 3 cycles.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC2   The length of LFSR sequence is 7 cycles.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC3   The length of LFSR sequence is 15 cycles.
*          `$INSTANCE_NAME`_CLK_SOURCE_SSC4   The length of LFSR sequence is 31 cycles.
*
* \return
*  Returns the LFSR scale value needed to keep the clock dither in range +/-10%.
*
*******************************************************************************/
static uint8 `$INSTANCE_NAME`_SsCalcLfsrScale(uint32 snsClkDivider, uint8 lfsrSize)
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

#endif /* (((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
           (`$INSTANCE_NAME`_DISABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
           (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSX_TX_CLK_SOURCE)) ||\
          ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) && \
           (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) && \
           (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE))) */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN)
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
    *  The function goes through all the widgets and updates appropriate bits in
    *  the IO HSIOM, PC and DR registers depending on the Inactive sensor connection
    *  parameter. DR register bits are set to zero when the Inactive sensor
    *  connection is Ground or Hi-Z.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SsClearCSDSensors(void)
    {
        uint32 wdgtIndex;
        uint32 snsIndex;

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            uint32 pinIndex;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */

        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
            /* Declare ptr to sensor IO structure */
            `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curDedicatedSnsIOPtr;
            /* Pointer to Flash structure holding info of sensor to be scanned */
            `$INSTANCE_NAME`_FLASH_SNS_STRUCT const *curFlashSnsPtr;
        #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
        `$INSTANCE_NAME`_FLASH_IO_STRUCT const *curSnsIOPtr;

        for (wdgtIndex = 0u; wdgtIndex < `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtIndex++)
        {
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSD_E ==
                `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex]))
            {
                curSnsIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)
                                                `$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].ptr2SnsFlash;

                /* Go through all the sensors in widget */
                for (snsIndex = 0u; snsIndex < (uint8)`$INSTANCE_NAME`_dsFlash.wdgtArray[wdgtIndex].totalNumSns; snsIndex++)
                {
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN)
                        /* Check ganged sns flag */
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
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_GANGED_SNS_EN) */
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
    *  This function gets the Sense Clock Divider value based on the Component
    *  configuration. The function is applicable for one-dimension widgets and for
    *  two-dimension widgets.
    *
    * \param widgetId
    *  Specifies the ID of the widget.
    *
    * \return
    *  Returns the Sense Clock Divider value for one-dimension widgets
    *  and the Column Sense Clock divider value for two-dimension widgets.
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


    #if (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDGetRowSnsClkDivider
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
        * \return
        *  Returns the sense clock divider value for one-dimension widgets
        *  and column sense clock divider value for two-dimension widgets.
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
    #endif /* (`$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN || `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */


    #if (`$INSTANCE_NAME`_CLK_SOURCE_PRSAUTO == `$INSTANCE_NAME`_CSD_SNS_CLK_SOURCE)
        /*******************************************************************************
        * Function Name: `$INSTANCE_NAME`_SsCSDCalcPrsSize
        ****************************************************************************//**
        *
        * \brief
        *  The function finds PRS polynomial size in the Auto mode.
        *
        * \details
        *  The PRS polynomial size in the Auto mode is found based on the following
        *  requirements:
        *  - at least one full spread spectrum polynomial should pass during scan time.
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
            uint32 modClkDivider = 1u;

            #if ((`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_CSDV2) && \
                 (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_IS_M0S8PERI_BLOCK))
                    modClkDivider = (uint32)`$INSTANCE_NAME`_dsRam.modCsdClk;
            #endif

            if ((snsClkDivider * `$INSTANCE_NAME`_PRS_LENGTH_12_BITS) <= (modClkDivider * ((0x00000001Lu << resolution) - 1u)))
            {
                /* Set PRS12 mode */
                prsSize = `$INSTANCE_NAME`_PRS_12_CONFIG;
            }
            else if ((snsClkDivider * `$INSTANCE_NAME`_PRS_LENGTH_8_BITS) <= (modClkDivider * ((0x00000001Lu << resolution) - 1u)))
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
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_EN) */


#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_BistDischargeExtCapacitors
    ****************************************************************************//**
    *
    * \brief
    *  The function discharge available external capacitors.
    *
    * \details
    *  The function discharge available external capacitors by connection them
    *  to GND using STRONG GPIO drive mode. Additionaly, the function disconnects 
    *  the capacitors from analog mux buses if connected.
    *  Note: the function does not restore the connection to analog mux busses 
    *  and supposes that all the capacitors belong to a single device port.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_BistDischargeExtCapacitors(void)
    {
        uint32 newRegValue;
        uint8  interruptState;
        
        /* Disconnect Ext Cap from AMUXBUS-A using HSIOM registers */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_EXT_CAP_HSIOM_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_EXT_CAP_HSIOM_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_EXT_CAP_HSIOM_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        /* Set output port register to 0 to connect to GND */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_EXT_CAP_DR_PTR);
        newRegValue &= (uint32)(~(uint32)`$INSTANCE_NAME`_EXT_CAP_DR_MASK);
        CY_SET_REG32(`$INSTANCE_NAME`_EXT_CAP_DR_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        /* Set port configuration register (drive mode) in STRONG mode */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_EXT_CAP_PC_PTR);
        newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_EXT_CAP_PC_MASK));
        newRegValue |= (`$INSTANCE_NAME`_EXT_CAP_PC_STRONG_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_EXT_CAP_PC_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

        /* Delay to discharge external capacitors */
        CyDelayUs(`$INSTANCE_NAME`_EXT_CAP_DISCHARGE_TIME);

        /* Set port configuration register (drive mode) in STRONG mode */
        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(`$INSTANCE_NAME`_EXT_CAP_PC_PTR);
        newRegValue &= (uint32)(~((uint32)`$INSTANCE_NAME`_EXT_CAP_PC_MASK));
        CY_SET_REG32(`$INSTANCE_NAME`_EXT_CAP_PC_PTR, newRegValue);
        CyExitCriticalSection(interruptState);
    }
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSDV2) */


/* [] END OF FILE */
