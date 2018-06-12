/***************************************************************************//**
* \file `$INSTANCE_NAME`_SensingISX_LL.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file defines the data structure global variables and provides
*   implementation for the low-level APIs of the ISX part of
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
#include <cytypes.h>
#include "CyLib.h"

#include "`$INSTANCE_NAME`_Structure.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#include "`$INSTANCE_NAME`_SensingISX_LL.h"
#include "`$INSTANCE_NAME`_Sensing.h"
#include "`$INSTANCE_NAME`_SioClk.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if (0u != `$INSTANCE_NAME`_ISX_EN)
#include "`$INSTANCE_NAME`_DigPrt2.h"
    #if (`$INSTANCE_NAME`_USES_PORT_3)
        #include "`$INSTANCE_NAME`_DigPrt3.h"
    #endif

/*******************************************************************************
* Module local function declarations
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

static void `$INSTANCE_NAME`_SsISXStartSample (void);
static void `$INSTANCE_NAME`_SsISXPostMultiScan(void);
static void `$INSTANCE_NAME`_SsISXPostSingleScan(void);
static void `$INSTANCE_NAME`_ISXSetupClock(uint32 snsClkDivider);
static void `$INSTANCE_NAME`_initDigPrts(void);

#if (`$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE)
    static void `$INSTANCE_NAME`_ISXCalibrateIdac(uint32 widgetId, uint16 target);
    static void `$INSTANCE_NAME`_ISXCalibrateFrequency(uint32 widgetId);
#endif /* (`$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE) */

/** \}
* \endcond */

CY_INLINE static void `$INSTANCE_NAME`_SsISXStartSampleExt(void);
static uint16 `$INSTANCE_NAME`_CalcISXScanPeriod (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *wdgtPtr);

/*******************************************************************************
* Define module variables
*******************************************************************************/

/* Local variable used to store the Scan period */
static volatile uint16 `$INSTANCE_NAME`_isxScanPeriod = 0u;

/* Local variable used to return RawCount from the post scan ISR */
static volatile uint16 `$INSTANCE_NAME`_isxRawCount = 0u;

static volatile uint32 `$INSTANCE_NAME`_isxResamplingCyclesCnt = `$INSTANCE_NAME`_RESAMPLING_CYCLES_MAX_NUMBER;

/* Pointer to Flash structure to hold Lx electrode that was connected previously */
static `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curIsxLxIOPtr;

/* Pointer to Flash structure to hold Rx electrode that was connected previously */
static `$INSTANCE_NAME`_FLASH_IO_STRUCT const *`$INSTANCE_NAME`_curIsxRxIOPtr;

/* Pointer to Pointer to function used to register callback in ISR */
void (*`$INSTANCE_NAME`_ISXPostScanApiPtr)(void) = &`$INSTANCE_NAME`_SsISXPostMultiScan;

/* Local variable to hold total Tx in widget, while scanning all sensors in widget */
static uint16 `$INSTANCE_NAME`_curWdgtTotalRx = 0u;

/* Local variable to hold total Rx in widget, while scanning all sensors in widget */
static uint16 `$INSTANCE_NAME`_curWdgtTotalTx = 0u;

/* Flag to indicate that electrodes were connected previously */
static uint16 `$INSTANCE_NAME`_eleIsxDisconnectFlag = 0u;

/*******************************************************************************
* Function constants
*******************************************************************************/

#define  `$INSTANCE_NAME`_NUM_HALF_CYCLES       2u

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXInitialize
****************************************************************************//**
*
* \brief
*   Performs hardware and firmware initialization required for the ISX operation
*   of the Component.
*
* \details
*   This function initializes hardware to perform the ISX sensing operation. This
*   function is called by the `$INSTANCE_NAME`_Start() API during the Component
*   initialization. If multiple sensing methods are used in the Component,
*   this function is called by the `$INSTANCE_NAME`_SetupWidget() API to
*   re-initialize for the ISX sensing.
*
*   If multiple sensing modes' widgets are used in the Component, it is recommended
*   to place all widgets of each sensing mode in sequence using the customizer.
*   For the Component API, this action will eliminate the need for changing the
*   hardware configuration for every widget scan and will increase the execution
*   speed in the `$INSTANCE_NAME`_ScanAllWidgets() when the API is called.
*
*   Similarly, it is recommended to set up and scan all the ISX widgets in such
*   a sequence that the `$INSTANCE_NAME`_SetupWidget() API  shouldn't need
*   hardware  sensing-configuration change.
*
*   It is highly recommended to not call this API directly from the application layer.
*
*******************************************************************************/

void `$INSTANCE_NAME`_ISXInitialize(void)
{
    uint8  interruptState;

    /* Used for multiple read, modify, and write operations. */
    uint32 memWorkingReg;

    `$INSTANCE_NAME`_DigPrt2_Init();
    `$INSTANCE_NAME`_DigPrt2_Enable();
    #if (`$INSTANCE_NAME`_USES_PORT_3)
        `$INSTANCE_NAME`_DigPrt3_Init();
        `$INSTANCE_NAME`_DigPrt3_Enable();
    #endif /* `$INSTANCE_NAME`_USES_PORT_3 */
    `$INSTANCE_NAME`_initDigPrts();

    CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR,             `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_INTR_SET_PTR,         `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_SET_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_INTR_MASK_PTR,        `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_MASK_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR,            `$INSTANCE_NAME`_DEFAULT_ISX_CSD_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_AMBUF_PTR,            `$INSTANCE_NAME`_DEFAULT_ISX_CSD_AMBUF_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_REFGEN_PTR,           `$INSTANCE_NAME`_DEFAULT_ISX_CSD_REFGEN_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR,           `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CSDCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR,         `$INSTANCE_NAME`_DEFAULT_ISX_CSD_IDACA_CFG);

    #if((0u != `$INSTANCE_NAME`_ADC_EN) || (0u != `$INSTANCE_NAME`_IDACB_USED))
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_COMP_PTR,    `$INSTANCE_NAME`_DEFAULT_ISX_CSD_IDACB_CFG);
    #endif /* (0u != `$INSTANCE_NAME`_ADC_EN) || (0u != `$INSTANCE_NAME`_IDACB_USED) */

    CY_SET_REG32(`$INSTANCE_NAME`_SW_RES_PTR,           `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_RES_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR,     `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SENSE_PERIOD_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SENSE_DUTY_PTR,       `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SENSE_DUTY_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_AMUXBUF_SEL_PTR,   `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_AMUXBUF_SEL_CFG);

    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR);
    memWorkingReg |= `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_BYP_SEL_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR,       memWorkingReg);

    CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_P_SEL_PTR,     `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_CMP_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_CMP_N_SEL_PTR,     `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_CMP_N_SEL_CFG);

    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR);
    memWorkingReg |= `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_REFGEN_SEL_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_SW_REFGEN_SEL_PTR,    memWorkingReg);

    CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_FW_MOD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_FW_TANK_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_DSI_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_TIME_PTR,         `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_TIME_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_INIT_CNT_PTR,     `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_INIT_CNT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_NORM_CNT_PTR,     `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_NORM_CNT_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_ADC_CTL_PTR,          `$INSTANCE_NAME`_DEFAULT_ISX_CSD_ADC_CTL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR,        `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_START_CFG);

    interruptState = CyEnterCriticalSection();
    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_CintA_PC_PTR);
    memWorkingReg &= (~(`$INSTANCE_NAME`_GPIO_PC_MASK << (`$INSTANCE_NAME`_CintA_SHIFT * `$INSTANCE_NAME`_GPIO_PC_BIT_SIZE)));
    CY_SET_REG32(`$INSTANCE_NAME`_CintA_PC_PTR, memWorkingReg);
    CyExitCriticalSection(interruptState);

    interruptState = CyEnterCriticalSection();
    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_CintB_PC_PTR);
    memWorkingReg &= (~(`$INSTANCE_NAME`_GPIO_PC_MASK << (`$INSTANCE_NAME`_CintB__SHIFT * `$INSTANCE_NAME`_GPIO_PC_BIT_SIZE)));
    CY_SET_REG32(`$INSTANCE_NAME`_CintB_PC_PTR, memWorkingReg);
    CyExitCriticalSection(interruptState);

    /* Connect CintA_tank pin to AMUXBUS-A using HSIOM registers. */
    interruptState = CyEnterCriticalSection();
    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR);
    memWorkingReg &= ~`$INSTANCE_NAME`_CintA_HSIOM_MASK;
    memWorkingReg |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CintA_HSIOM_SHIFT);
    CY_SET_REG32(`$INSTANCE_NAME`_CintA_HSIOM_PTR, memWorkingReg);
    CyExitCriticalSection(interruptState);

    /* Connect CintB to AMUXBUS-A using HSIOM registers. */
    interruptState = CyEnterCriticalSection();
    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR);
    memWorkingReg &= ~`$INSTANCE_NAME`_CintB_HSIOM_MASK;
    memWorkingReg |= (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << `$INSTANCE_NAME`_CintB_HSIOM_SHIFT);
    CY_SET_REG32(`$INSTANCE_NAME`_CintB_HSIOM_PTR, memWorkingReg);
    CyExitCriticalSection(interruptState);

    `$INSTANCE_NAME`_SsSetModClkClockDivider((uint32)`$INSTANCE_NAME`_dsRam.modIsxClk);

    /* Set all IO states to default state */
    `$INSTANCE_NAME`_SsSetIOsInDefaultState();
    memWorkingReg = CY_GET_REG32(CYREG_HSIOM_PORT_SEL2);
    memWorkingReg &= ~`$INSTANCE_NAME`_DIG1_PIN_MASK;
    memWorkingReg = memWorkingReg | `$INSTANCE_NAME`_DIG1_PIN_CONNECT;
    /* Set back the port again */
    CY_SET_REG32(CYREG_HSIOM_PORT_SEL2, memWorkingReg);
    #if (`$INSTANCE_NAME`_USES_PORT_3)
        memWorkingReg = CY_GET_REG32(CYREG_HSIOM_PORT_SEL3);
        memWorkingReg &= ~`$INSTANCE_NAME`_DIG2_PIN_MASK;
        memWorkingReg = memWorkingReg | `$INSTANCE_NAME`_DIG2_PIN_CONNECT;
        /* Set back the port again */
        CY_SET_REG32(CYREG_HSIOM_PORT_SEL3, memWorkingReg);
    #endif /* (`$INSTANCE_NAME`_USES_PORT_3) */
    /* Enable the ISR and set ISR for ISX sensing */
    `$INSTANCE_NAME`_SsIsrInitialize(&`$INSTANCE_NAME`_SsISXScanISR);
}

static void `$INSTANCE_NAME`_initDigPrts(void)
{
    uint32 widgetIndex;
    uint8 p2PinMask = `$INSTANCE_NAME`_RSV2_MASK;
    #if `$INSTANCE_NAME`_USES_PORT_3
        uint8 p3PinMask = `$INSTANCE_NAME`_RSV3_MASK;
        `$INSTANCE_NAME`_DigPrt3_Disable();
    #endif
    `$INSTANCE_NAME`_DigPrt2_Disable();

    for(widgetIndex = 0uL; widgetIndex < `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS; widgetIndex++)
    {
        uint32 ioIndex = (widgetIndex * 2uL) + 1uL;
        uint32 portNum = (((uint32)`$INSTANCE_NAME`_ioList[ioIndex].hsiomPtr) & 0x700uL) >> 0x8uL;
        uint32 pinNum = `$INSTANCE_NAME`_ioList[ioIndex].drShift;
        switch(portNum)
        {
        case 2uL:     
            p2PinMask |= (uint8)(1u << pinNum);
            `$INSTANCE_NAME`_DigPrt2_LUT_CONGIG_BASE.lutSel[pinNum] = `$INSTANCE_NAME`_CALC_DIG_IO(pinNum);
            `$INSTANCE_NAME`_DigPrt2_LUT_CONGIG_BASE.lutCtl[pinNum] = 0xAAuL;
            break;        
        #if `$INSTANCE_NAME`_USES_PORT_3
            case 3uL:        
                p3PinMask |= (uint8)(1u << pinNum);
                `$INSTANCE_NAME`_DigPrt3_LUT_CONGIG_BASE.lutSel[pinNum] = `$INSTANCE_NAME`_CALC_DIG_IO(pinNum);
                `$INSTANCE_NAME`_DigPrt3_LUT_CONGIG_BASE.lutCtl[pinNum] = 0xAAuL;
                break;        
        #endif
        default:
            break;
        }
    }
    
    switch(`$INSTANCE_NAME`_RSV_PORT)    
    {
    case 2u:
    `$INSTANCE_NAME`_DigPrt2_LUT_CONGIG_BASE.lutSel[`$INSTANCE_NAME`_DIG1_CHAN1] = `$INSTANCE_NAME`_CALC_DIG_IO((uint32)`$INSTANCE_NAME`_DIG1_CHAN1);
    break;
    
    #if `$INSTANCE_NAME`_USES_PORT_3
        case 3u:
            `$INSTANCE_NAME`_DigPrt3_LUT_CONGIG_BASE.lutSel[`$INSTANCE_NAME`_DIG2_CHAN1] = `$INSTANCE_NAME`_CALC_DIG_IO((uint32)`$INSTANCE_NAME`_DIG2_CHAN1);
            break;        
    #endif
    default:
    break;
    }

    `$INSTANCE_NAME`_DigPrt2_CTL &= ~(`$INSTANCE_NAME`_DigPrt2_BYPASS_MASK);
    `$INSTANCE_NAME`_DigPrt2_CTL |= (uint8)(~p2PinMask);
    `$INSTANCE_NAME`_DigPrt2_Enable();
    #if `$INSTANCE_NAME`_USES_PORT_3
        `$INSTANCE_NAME`_DigPrt3_CTL &= ~(`$INSTANCE_NAME`_DigPrt3_BYPASS_MASK);
        `$INSTANCE_NAME`_DigPrt3_CTL |= (uint8)(~p3PinMask);
        `$INSTANCE_NAME`_DigPrt3_Enable();
    #endif
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXElectrodeCheck
****************************************************************************//**
*
* \brief
*   Check if electrodes were previously connected using
*   the `$INSTANCE_NAME`_ISXSetupWidgetExt() API and if yes, disconnect them.
*
* \details
*   This function checks if `$INSTANCE_NAME`_eleIsxDisconnectFlag is set.
*   If it is set, the function disconnects the previously connected electrode.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISXElectrodeCheck(void)
{
    if (0u != `$INSTANCE_NAME`_eleIsxDisconnectFlag)
    {
        /* Disconnect if electrodes were previous connected by SetupWidgetExt API */
        `$INSTANCE_NAME`_ISXDisconnectLx(`$INSTANCE_NAME`_curIsxLxIOPtr);
        `$INSTANCE_NAME`_ISXDisconnectRx(`$INSTANCE_NAME`_curIsxRxIOPtr);
        `$INSTANCE_NAME`_eleIsxDisconnectFlag = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXSetupWidget
****************************************************************************//**
*
* \brief
*  Performs hardware and firmware initialization required for scanning sensors
*  in a specific widget using the ISX sensing method. The
*  `$INSTANCE_NAME`_ISXScan() function should be used to start scanning when
*  using this function.
*
* \details
*  This function initializes the widgets specific common parameters to perform
*  the ISX scanning. The initialization includes the following:
*    1. The CSD_CONFIG register.
*    2. The IDAC register.
*    3. The Sense clock frequency
*    4. The phase alignment of the sense and modulator clocks.
*
*  This function does not connect any specific sensors to the scanning hardware
*  and also does not start a scanning process. The `$INSTANCE_NAME`_ISXScan()
*  function must be called after initializing the widget to start scanning.
*
*  This function should be called when no scanning is in progress. I.e.,
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  This function is called by the `$INSTANCE_NAME`_SetupWidget() API if the
*  given widget uses the ISX sensing method.
*
*  It is recommended to not call this function directly from the application.
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specify the ID number of the widget to perform hardware and firmware
*  initialization required for scanning sensors in the specific widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
*******************************************************************************/

void `$INSTANCE_NAME`_ISXSetupWidget(uint32 widgetId)
{
    /* variable to access widget details */
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT * curRamWdgtBasePtr;

    /* Used for multiple read, modify, and write operations. */
    uint32 memWorkingReg;
    uint32 snsClkVal;

    #if ((`$INSTANCE_NAME`_USES_MANY_SENSE_MODES) || \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
        (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN))
         `$INSTANCE_NAME`_SsSwitchSensingMode(`$INSTANCE_NAME`_SENSE_METHOD_ISX_E);
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_ISX_EN) || \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) || \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ADC_EN)) */

    /*
     * Check if ISX electrodes were previously connected using
     * `$INSTANCE_NAME`_ISXSetupWidgetExt API and if yes, disconnect them
     */
    `$INSTANCE_NAME`_ISXElectrodeCheck();

    /* Save the current widget Id */
    `$INSTANCE_NAME`_widgetIndex = (uint8)widgetId;

    /* Configure hardware block */
    `$INSTANCE_NAME`_curFlashWdgtPtr = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

    curRamWdgtBasePtr = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2WdgtRam;

    snsClkVal = (uint32)curRamWdgtBasePtr->snsClk;

    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_NORM_CNT_PTR, (uint32)curRamWdgtBasePtr->resolution);
    `$INSTANCE_NAME`_isxScanPeriod  = `$INSTANCE_NAME`_CalcISXScanPeriod(curRamWdgtBasePtr);

    memWorkingReg = (uint32)curRamWdgtBasePtr->snsClkSource;

    snsClkVal = (snsClkVal - 1uL) & `$INSTANCE_NAME`_SENSE_PERIOD_SENSE_DIV_MASK;
    memWorkingReg = (memWorkingReg << `$INSTANCE_NAME`_SENSE_PERIOD_LFSR_SIZE_SHIFT) | snsClkVal;
    `$INSTANCE_NAME`_ISXSetupClock(memWorkingReg);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXSetupClock
****************************************************************************//**
*
* \brief
*  Configures Component clock and digital output.
*
* \param snsClkDivider
*  This is the divider to be used for setting the Lx frequency.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ISXSetupClock(uint32 snsClkDivider)
{
    uint32 size, pSio;
    uint32 snsClkVal = (snsClkDivider & `$INSTANCE_NAME`_SENSE_PERIOD_SENSE_DIV_MASK) + 1u;
    CY_SET_REG32(`$INSTANCE_NAME`_SENSE_PERIOD_PTR, snsClkDivider);
    `$INSTANCE_NAME`_SsSetModClkClockDivider((uint32)`$INSTANCE_NAME`_dsRam.modIsxClk);

    /* pSio*size + pHf*2/3 = pSns*phiLx/360
     * pSns = div_sns * div_mod
     * digPrt delay + ~ gate delay = phiLx's portion of sense period*/

    /* First, assuming pSio is 1, estimate size. May be larger than 8. */
    pSio = 1uL;
    size = ((snsClkVal * `$INSTANCE_NAME`_dsRam.modIsxClk) * `$INSTANCE_NAME`_DIG_DEL);
    size = size - `$INSTANCE_NAME`_DIG_CORRECTION;
    size = size + ((`$INSTANCE_NAME`_CONST_360 >> 1uL) * pSio);
    size = size / (`$INSTANCE_NAME`_CONST_360 * pSio);

    /* size must be <= 8, so adjust pSio upward if larger size is needed. */
    pSio = (size / 8uL) + 1uL;

    /* Recalculate size based on modified pSio. */
    size = ((snsClkVal * `$INSTANCE_NAME`_dsRam.modIsxClk) * `$INSTANCE_NAME`_DIG_DEL);
    size = size - (`$INSTANCE_NAME`_DIG_CORRECTION);
    size = size + ((`$INSTANCE_NAME`_CONST_360 >> 1uL) * pSio);
    size = size / (`$INSTANCE_NAME`_CONST_360 * pSio);

    /* Change the SioClk, if needed. */
    if(pSio != (`$INSTANCE_NAME`_SioClk_GetDividerRegister() + 1uL))
    {
        `$INSTANCE_NAME`_SioClk_Stop();
        `$INSTANCE_NAME`_SioClk_SetDividerValue((uint16)pSio);
        `$INSTANCE_NAME`_SioClk_Start();
    }

    /* Adjust Component digital resources based on widget index. */
    if(`$INSTANCE_NAME`_ON_PORT_2(`$INSTANCE_NAME`_widgetIndex))
    {
        (void)`$INSTANCE_NAME`_DigPrt2_DU_OpCode(`$INSTANCE_NAME`_DigPrt2_OPC_SHR, size);
        switch(`$INSTANCE_NAME`_widgetIndex)
        {
        case 0u:
            `$INSTANCE_NAME`_DigPrt2_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG1_CHAN0,
                `$INSTANCE_NAME`_DIG_OUT,
                `$INSTANCE_NAME`_DigPrt2_MODE_COMB);
            `$INSTANCE_NAME`_DigPrt2_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG1_CHAN1,
                `$INSTANCE_NAME`_DIG_IN,
                `$INSTANCE_NAME`_DigPrt2_MODE_COMB);
            (void)`$INSTANCE_NAME`_DigPrt2_DU_SelectTriggers(
                `$INSTANCE_NAME`_DigPrt2_TR_CONST_ZERO,
                `$INSTANCE_NAME`_DigPrt2_TR_CONST_ONE,
                (`$INSTANCE_NAME`_DIG1_CHAN1 + 3u));
            break;
        case 1u:
            `$INSTANCE_NAME`_DigPrt2_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG1_CHAN0,
                `$INSTANCE_NAME`_DIG_IN,
                `$INSTANCE_NAME`_DigPrt2_MODE_COMB);
            `$INSTANCE_NAME`_DigPrt2_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG1_CHAN1,
                `$INSTANCE_NAME`_DIG_OUT,
                `$INSTANCE_NAME`_DigPrt2_MODE_COMB);
            (void)`$INSTANCE_NAME`_DigPrt2_DU_SelectTriggers(
                `$INSTANCE_NAME`_DigPrt2_TR_CONST_ZERO,
                `$INSTANCE_NAME`_DigPrt2_TR_CONST_ONE,
                (`$INSTANCE_NAME`_DIG1_CHAN0 + 3u));
            break;
        default:
            break;
        }
    }
    #if (`$INSTANCE_NAME`_USES_PORT_3)
    else
    {
        (void)`$INSTANCE_NAME`_DigPrt3_DU_OpCode(`$INSTANCE_NAME`_DigPrt3_OPC_SHR, size);
        switch(`$INSTANCE_NAME`_widgetIndex)        
        {
        case 8u:
            `$INSTANCE_NAME`_DigPrt3_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG2_CHAN0,
                `$INSTANCE_NAME`_DIG_OUT,
                `$INSTANCE_NAME`_DigPrt3_MODE_COMB);
            `$INSTANCE_NAME`_DigPrt3_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG2_CHAN1,
                `$INSTANCE_NAME`_DIG_IN,
                `$INSTANCE_NAME`_DigPrt3_MODE_COMB);
            (void)`$INSTANCE_NAME`_DigPrt3_DU_SelectTriggers(
                `$INSTANCE_NAME`_DigPrt3_TR_CONST_ZERO,
                `$INSTANCE_NAME`_DigPrt3_TR_CONST_ONE,
                (`$INSTANCE_NAME`_DIG2_CHAN1 + 3u));
            break;
        case 9u:        
            `$INSTANCE_NAME`_DigPrt3_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG2_CHAN0,
                `$INSTANCE_NAME`_DIG_IN,
                `$INSTANCE_NAME`_DigPrt3_MODE_COMB);
            `$INSTANCE_NAME`_DigPrt3_LUT_ConfigureMode(
                `$INSTANCE_NAME`_DIG2_CHAN1,
                `$INSTANCE_NAME`_DIG_OUT,
                `$INSTANCE_NAME`_DigPrt3_MODE_COMB);
            (void)`$INSTANCE_NAME`_DigPrt3_DU_SelectTriggers(
                `$INSTANCE_NAME`_DigPrt3_TR_CONST_ZERO,
                `$INSTANCE_NAME`_DigPrt3_TR_CONST_ONE,
                (`$INSTANCE_NAME`_DIG2_CHAN0 + 3u));
            break;
        default:
            break;
        }
    }
    #endif /* `$INSTANCE_NAME`_USES_PORT_3 */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXSetupWidgetExt
****************************************************************************//**
*
* \brief
*  Performs extended initialization for the ISX widget and also performs
*  initialization required for a specific sensor in the widget. The
*  `$INSTANCE_NAME`_ISXScanExt() function should be called to initiate the scan
*  when using this function.
*
* \details
*  This function does the same tasks as `$INSTANCE_NAME`_ISXSetupWidget() and
*  also connects a sensor in the widget for scanning. Once this function is
*  called to initialize a widget and a sensor, the `$INSTANCE_NAME`_ISXScanExt()
*  function should be called to scan the sensor.
*
*  This function should be called when no scanning in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time or pipeline scanning for example).
*
* \param widgetId
*  Specify the ID number of the widget to perform hardware and firmware
*  initialization required for scanning a specific sensor in a specific widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param snsIndex
*  Specify the ID number of the sensor within the widget to perform hardware
*  and firmware initialization required for scanning a specific sensor in a
*  specific widget.
*  A macro for the sensor ID within a specified widget can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*
*******************************************************************************/

void `$INSTANCE_NAME`_ISXSetupWidgetExt(uint32 widgetId, uint32 snsIndex)
{
    uint32 txIndex;
    uint32 rxIndex;

    /* Initialize widget */
    `$INSTANCE_NAME`_ISXSetupWidget(widgetId);

    /* Initialise sensor data structure pointer to appropriate address */
    `$INSTANCE_NAME`_curRamSnsPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsRam;
    `$INSTANCE_NAME`_curRamSnsPtr = &`$INSTANCE_NAME`_curRamSnsPtr[snsIndex];

    /*
     * Find Tx and Rx index for given snsIndex
     * rxIndex = snsIndex / TxCount
     * txIndex = snsIndex % TxCount
     */
    rxIndex = snsIndex /`$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
    txIndex = snsIndex % `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;

     /*
      * 1. Find Rx pointer: Rx = Base address + RxIndex
      * 2. Find Tx pointer: Tx = Base address + (total Rx + TxIndex)
      */
    `$INSTANCE_NAME`_curIsxRxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
    `$INSTANCE_NAME`_curIsxRxIOPtr = &`$INSTANCE_NAME`_curIsxRxIOPtr[rxIndex];

    `$INSTANCE_NAME`_curIsxLxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
    `$INSTANCE_NAME`_curIsxLxIOPtr = &`$INSTANCE_NAME`_curIsxLxIOPtr[(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols + txIndex)];

    /* Connect Tx and Rx IOs for scan ad set flag to indicate that IOs should be disconnected */
    `$INSTANCE_NAME`_ISXConnectLx(`$INSTANCE_NAME`_curIsxLxIOPtr);
    `$INSTANCE_NAME`_ISXConnectRx(`$INSTANCE_NAME`_curIsxRxIOPtr);
    `$INSTANCE_NAME`_eleIsxDisconnectFlag = `$INSTANCE_NAME`_DISCONNECT_IO_FLAG;

    /* Set callback to scan all sensors in widget */
    `$INSTANCE_NAME`_ISXPostScanApiPtr = &`$INSTANCE_NAME`_SsISXPostSingleScan;

}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXScan
****************************************************************************//**
*
* \brief
*  This function initiates the scan for sensors of the widget initialized by
*  the `$INSTANCE_NAME`_ISXSetupWidget() function.
*
* \details
*  This function performs scanning of all sensors in the widget configured by
*  the `$INSTANCE_NAME`_ISXSetupWidget() function. It does the following tasks:
*    1. Connects the first sensor of the widget.
*    2. Initializes an interrupt callback function to initialize a scan of the
*       next sensors in a widget.
*    3. Starts scanning for the first sensor in the widget.
*
*  This function is called by the `$INSTANCE_NAME`_Scan() API if the given
*  widget uses the ISX sensing method.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time or pipeline scanning for example).
*
*  This function should be called when no scanning in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status. The widget must be
*  preconfigured by the `$INSTANCE_NAME`_ISXSetupWidget() function if other
*  widget was previously scanned or other type of scan functions were used.
*
*******************************************************************************/

void `$INSTANCE_NAME`_ISXScan(void)
{
    /* Initialise pointer to access sensor RAM elements */
    `$INSTANCE_NAME`_curRamSnsPtr = `$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsRam;

    /* Calculate total sensors to be scanned. If proximity, one Tx and an Rx
     *  for each sensor. */
    `$INSTANCE_NAME`_curWdgtTotalTx = `$INSTANCE_NAME`_curFlashWdgtPtr->numRows;
    `$INSTANCE_NAME`_curWdgtTotalRx  = `$INSTANCE_NAME`_curFlashWdgtPtr->numCols;

    /* 1. Find Rx pointer: Rx = Base address.
        2. Find Rx pointer: Tx = Base address + total Rx */
    `$INSTANCE_NAME`_curIsxRxIOPtr = (`$INSTANCE_NAME`_FLASH_IO_STRUCT const *)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2SnsFlash;
    `$INSTANCE_NAME`_curIsxLxIOPtr = `$INSTANCE_NAME`_curIsxRxIOPtr;
    `$INSTANCE_NAME`_curIsxLxIOPtr = &`$INSTANCE_NAME`_curIsxLxIOPtr[(`$INSTANCE_NAME`_curFlashWdgtPtr->numCols)];

    /* Connect first Tx and first Rx IOs for scan */
    `$INSTANCE_NAME`_ISXConnectLx(`$INSTANCE_NAME`_curIsxLxIOPtr);
    `$INSTANCE_NAME`_ISXConnectRx(`$INSTANCE_NAME`_curIsxRxIOPtr);

    /* Set callback to scan all sensors in widget */
    `$INSTANCE_NAME`_ISXPostScanApiPtr = &`$INSTANCE_NAME`_SsISXPostMultiScan;

    /* Set scan status, enter critical section and initiate scan */
    `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;
    `$INSTANCE_NAME`_SsISXStartSample();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXScanExt()
****************************************************************************//**
*
* \brief
*  Starts the ISX conversion on the preconfigured sensor. The
*  `$INSTANCE_NAME`_ISXSetupWidgetExt() function should be used to setup a
*  widget when using this function.
*
* \details
*  This function performs single scanning of one sensor in the widget configured
*  by `$INSTANCE_NAME`_ISXSetupWidgetExt()  function. It does the following
*  tasks:
*    1. Sets a busy flag in the `$INSTANCE_NAME`_dsRam structure.
*    2. Configures the Lx clock frequency.
*    3. Configures the Modulator clock frequency.
*    4. Configures the IDAC value.
*    5. Starts single scanning.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time or pipeline scanning for example). This
*  function should be called when no scanning in progress. I.e.
*  `$INSTANCE_NAME`_IsBusy() returns a non-busy status.
*
*  The sensor must be preconfigured by using the
*  `$INSTANCE_NAME`_ISXSetupWidgetExt() API prior to calling this function.
*  The sensor remains ready for the next scan if a previous scan was triggered
*  by using the `$INSTANCE_NAME`_ISXScanExt() function. In this case, calling
*  `$INSTANCE_NAME`_ISXSetupWidgetExt() is not required every time before the
*  `$INSTANCE_NAME`_ISXScanExt() function. If a previous scan was triggered in
*  any other way: `$INSTANCE_NAME`_Scan(), `$INSTANCE_NAME`_ScanAllWidgets()
*  or `$INSTANCE_NAME`_RunTuner() (see the `$INSTANCE_NAME`_RunTuner() function
*  description for more details), the sensor must be preconfigured again by
*  using the `$INSTANCE_NAME`_ISXSetupWidgetExt() API prior to calling the
*  `$INSTANCE_NAME`_ISXScanExt() function.
*
*  If disconnection of the sensors is required after calling
*  `$INSTANCE_NAME`_ISXScanExt(), the `$INSTANCE_NAME`_ISXDisconnectLx() and
*  `$INSTANCE_NAME`_ISXDisconnectRx() APIs can be used.
*
*******************************************************************************/

void `$INSTANCE_NAME`_ISXScanExt(void)
{
    /* Set busy flag and start conversion */
    `$INSTANCE_NAME`_dsRam.status |= `$INSTANCE_NAME`_SW_STS_BUSY;
    `$INSTANCE_NAME`_SsISXStartSample();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsISXPostMultiScan
****************************************************************************//**
*
* \brief
*   ISR function implements the multiple-sensor scanning for ISX widgets.
*   This function is called by the Component ISR only, it should not be used by
*   the application layer.
*
*******************************************************************************/

static void `$INSTANCE_NAME`_SsISXPostMultiScan(void)
{
    #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

    /* Copy scan result into sensor raw count array */
    `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex] = \
                             (`$INSTANCE_NAME`_isxScanPeriod - `$INSTANCE_NAME`_isxRawCount);

    /*
     * Disconnect Tx electrodes of previously scanned sensor as
     * preparation for next sensor scan
     */
    `$INSTANCE_NAME`_ISXDisconnectLx (`$INSTANCE_NAME`_curIsxLxIOPtr);
    `$INSTANCE_NAME`_ISXDisconnectRx(`$INSTANCE_NAME`_curIsxRxIOPtr);

    /*
     * Initiate scan for next sensor in widget, if all sensors in
     *  widget are not scanned
     */
    `$INSTANCE_NAME`_curWdgtTotalTx--;
    `$INSTANCE_NAME`_curWdgtTotalRx--;

    /* Call scan next widget API if requested, if not, complete scan */
    if (`$INSTANCE_NAME`_requestScanAllWidget != 0u)
    {
        `$INSTANCE_NAME`_SsPostAllWidgetsScan();
    }
    else
    {
        /*
         * All pending scans completed,
         * 1. Update the counter to indicate same
         * 2. Clear busy state since scanning is complete
         */
        `$INSTANCE_NAME`_dsRam.scanCounter++;
        `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;
    }

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsISXPostSingleScan
****************************************************************************//**
*
* \brief
*   The ISR function for single-sensor scanning implementation.
*
* \details
*   This function is used by `$INSTANCE_NAME` ISR in the ISX scanning mode to implement
*   the single-sensor scanning.
*   This function should not be used by the application layer.
*
*******************************************************************************/

static void `$INSTANCE_NAME`_SsISXPostSingleScan(void)
{
    #ifdef `$INSTANCE_NAME`_ENTRY_CALLBACK
        `$INSTANCE_NAME`_EntryCallback();
    #endif /* `$INSTANCE_NAME`_ENTRY_CALLBACK */

    /*
     * Copy scan result into sensor raw count array and clear busy flag
     * No sensor is connected or disconnected in this function
     * Calling `$INSTANCE_NAME`_ScanExt from application would perform
     * one more scan of same sensor. Specifically for low-power mode.
     */
    `$INSTANCE_NAME`_curRamSnsPtr->raw[`$INSTANCE_NAME`_scanFreqIndex]
        = (`$INSTANCE_NAME`_isxScanPeriod - `$INSTANCE_NAME`_isxRawCount);

    /*
     * All pending scans completed,
     * 1. Update the counter to indicate same
     * 2. Clear busy state since scanning is complete
     */
    `$INSTANCE_NAME`_dsRam.scanCounter++;
    `$INSTANCE_NAME`_dsRam.status &= ~`$INSTANCE_NAME`_SW_STS_BUSY;

    #ifdef `$INSTANCE_NAME`_EXIT_CALLBACK
        `$INSTANCE_NAME`_ExitCallback();
    #endif /* `$INSTANCE_NAME`_EXIT_CALLBACK */
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXCalibrateWidget
****************************************************************************//**
*
* \brief
*  Calibrates the raw count values of all sensors/nodes in an ISX widget.
*
* \details
*  Performs a rough calibration of IDAC values, then incrementally searches a
*  small range of frequencies around the widget's Lx frequency to find the
*  optimal Lx frequency. Then performs a search algorithm to find appropriate
*  IDAC values for sensors in the specified widget that provides a raw count
*  to the level specified by the target parameter.
*
*  This function is available when the ISX Enable auto-calibration
*  parameter is enabled.
*
* \param  widgetId
*  Specify the ID number of the ISX widget to calibrate its raw count.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param  idacTarget
*  Specify the calibration target in percentages of the maximum raw count.
*
*******************************************************************************/
#if (`$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE)

void `$INSTANCE_NAME`_ISXCalibrateWidget(uint32 widgetId, uint16 idacTarget)
{

    if (`$INSTANCE_NAME`_SENSE_METHOD_ISX_E ==
       `$INSTANCE_NAME`_GET_SENSE_METHOD(&`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId]))
    {
    `$INSTANCE_NAME`_ISXCalibrateIdac(widgetId, `$INSTANCE_NAME`_ISX_DEFAULT_IDAC_TARGET);
    `$INSTANCE_NAME`_ISXCalibrateFrequency(widgetId);
    `$INSTANCE_NAME`_ISXCalibrateIdac(widgetId, idacTarget);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXCalibrateIdac
****************************************************************************//**
*
* \brief
*  Calibration helper function. Calibrates the idac so that at the current signal
*  level, the count result will be at target percent.
*
* \details
*  Performs a successive approximation search algorithm to find appropriate
*  IDAC values for sensors in the specified widget that provides a raw count
*  to the level specified by the target parameter.
*
* \param  widgetId
*  Specify the ID number of the ISX widget to calibrate its raw count.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \param  target
*  Specify the calibration target in percentages of the maximum raw count.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ISXCalibrateIdac(uint32 widgetId, uint16 target)
{
    uint32 watchdogCounter;
    /* Declare and initialize ptr to widget and sensor structures. */
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *snsRamPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)
                                          `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
    /*
     *  Current IDAC bit in use
     *  next idac bit to be used
     *  counters for loop execution
     *  variable to calculate raw count target
     */
    uint8 curIdacMask = (1u << (`$INSTANCE_NAME`_ISX_IDAC_BITS_USED - 1u));
    uint8 nextIdacMask = (curIdacMask >> 1u);
    uint32 calibrationIndex, totalSns;
    uint32 rawTarget = 0uL;
    `$INSTANCE_NAME`_isxScanPeriod = `$INSTANCE_NAME`_CalcISXScanPeriod(ptrWdgt);
    rawTarget = `$INSTANCE_NAME`_isxScanPeriod;

    /* Calculate target raw count */
    rawTarget = (rawTarget * target);
    rawTarget = (rawTarget / `$INSTANCE_NAME`_PERCENTAGE_100);

    /* Calculate total sensors/nodes in widget */
    totalSns = ((uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols *
                (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numRows);
    ((`$INSTANCE_NAME`_RAM_WD_PROXIMITY_STRUCT*)ptrWdgt)->idacMod[0] = curIdacMask;

    (void)`$INSTANCE_NAME`_ISXSetupWidgetExt(widgetId, 0u);
    /* Perform binary search for accurate IDAC value for each sensor/node */
    do
    {
        /* Access sensor data */
        snsRamPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam;

        /* Scan all sensors/nodes in widget */
        (void)`$INSTANCE_NAME`_ISXScanExt();
        watchdogCounter = `$INSTANCE_NAME`_ISX_SCAN_WATCHDOG_CYCLES_NUM;
        while (((`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY) != 0u)
                && (0uL != watchdogCounter))
        {
            watchdogCounter--;
        }

        /* Check raw count and adjust IDAC, loop through all sensors/nodes */
        for (calibrationIndex = 0u; calibrationIndex < totalSns; calibrationIndex++)
        {
            /*
             * Check if current raw count is above target,
             *     if yes, clear the current bit
             *     if no, keep the current bit
             */
            if (snsRamPtr->raw[0u] > rawTarget)
            {
               ((`$INSTANCE_NAME`_RAM_WD_PROXIMITY_STRUCT*)ptrWdgt)->idacMod[0] &= (uint8)(~curIdacMask);
            }

            /* Set next bit */
            ((`$INSTANCE_NAME`_RAM_WD_PROXIMITY_STRUCT*)ptrWdgt)->idacMod[0] |= nextIdacMask;

            snsRamPtr++;
        }

        /* Shift both current idac and pre Idac values to right by 1 */
        curIdacMask = nextIdacMask;
        nextIdacMask = nextIdacMask >> 1u;
    } while (curIdacMask != 0u);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXCalibrateFrequency
****************************************************************************//**
*
* \brief
*  Calibration helper function. Calibrates the frequency so that the tank's
*  amplitude is maximized.
*
* \param  widgetId
*  Specify the ID number of the ISX widget to calibrate its raw count.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_ISXCalibrateFrequency(uint32 widgetId)
{
    /* Declare and initialize ptr to widget and sensor structures */
    uint16 maxFreqDivider, minFreqDivider, cur;
    uint16* criterionPtr;
    uint16 best = 0u;
    uint32 totalRaw = 0ul;
    uint32 totalSns;
    uint32 bestRaw = 0xfffffffful;
    uint32 calibrationIndex = 0uL;
    uint32 watchdogCounter;
    `$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *ptrWdgt = (`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)  `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
    `$INSTANCE_NAME`_RAM_SNS_STRUCT *snsRamPtr = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam;

    uint16 midPoint = ptrWdgt->snsClk;

    /* Step size is 2%, or 1/50th of current clock divider value. */
    uint16 divStep = (midPoint  + 25u) / 50u;

    /* divStep minimum is 1. */
    if(0u == divStep)
    {
        divStep = 1u;
    }
    best = midPoint;
    maxFreqDivider = midPoint - (5u * divStep);
    if (maxFreqDivider < 4u)
    {
        maxFreqDivider = 4u;
    }
    minFreqDivider = midPoint + (5u * divStep);
    criterionPtr = (uint16*)&(ptrWdgt->snsClk);

    /* Calculate total sensors/nodes in widget. */
    totalSns = ((uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numCols *
                (uint32)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].numRows);

    for(cur = maxFreqDivider; cur <= minFreqDivider; cur += divStep)
    {
        totalRaw = 0uL;

        /* Set next criterion to test. */
        *criterionPtr = cur;

        /* Access sensor data. */
        snsRamPtr = (`$INSTANCE_NAME`_RAM_SNS_STRUCT *)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2SnsRam;

        /* Scan all sensors/nodes in widget. */
        (void)`$INSTANCE_NAME`_SetupWidget(widgetId);
        (void)`$INSTANCE_NAME`_Scan();
        watchdogCounter = `$INSTANCE_NAME`_ISX_SCAN_WATCHDOG_CYCLES_NUM;
        while (((`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY) != 0u)
               && (watchdogCounter != 0uL))
        {
            watchdogCounter--;
        }

        /* Sum all raw counts */
        for (calibrationIndex = 0u; calibrationIndex < totalSns; calibrationIndex++)
        {
            totalRaw += snsRamPtr->raw[0u];
            snsRamPtr++;
        }

        /* If sum is lowest so far, remember this criterion. */
        if (totalRaw < bestRaw)
        {
            bestRaw = totalRaw;
            best = cur;
        }
    }

    /* Set criterion to best value. */
    *criterionPtr = best;
}
#endif /* (`$INSTANCE_NAME`_ISX_IDAC_AUTOCAL_EN == `$INSTANCE_NAME`_ENABLE) */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsISXStartSample
****************************************************************************//**
*
* \brief
*   Starts scanning for the ISX widget.
*
* \details
*   Starts scanning for the ISX widget.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SsISXStartSample(void)
{
    uint32 memWorkingReg;
    #ifdef `$INSTANCE_NAME`_START_SAMPLE_CALLBACK
        `$INSTANCE_NAME`_StartSampleCallback(`$INSTANCE_NAME`_widgetIndex, `$INSTANCE_NAME`_sensorIndex);
    #endif /* `$INSTANCE_NAME`_START_SAMPLE_CALLBACK */

    memWorkingReg = (uint32)((`$INSTANCE_NAME`_RAM_WD_PROXIMITY_STRUCT*)`$INSTANCE_NAME`_curFlashWdgtPtr->ptr2WdgtRam)->idacMod[0];
    memWorkingReg = (memWorkingReg & `$INSTANCE_NAME`_IDAC_MOD_VAL_MASK) | `$INSTANCE_NAME`_DEFAULT_ISX_CSD_IDACA_CFG;
    CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, memWorkingReg);

    /* Clear scan result holder */
    `$INSTANCE_NAME`_isxRawCount = 0u;
    `$INSTANCE_NAME`_SsISXStartSampleExt();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXConnectLx
****************************************************************************//**
*
* \brief
*  Connects a LX electrode to the ISX scanning hardware.
*
* \details
*  This function connects a port pin (Lx electrode) to the forcing signal.
*  It is assumed that the drive mode of the port pin is already set to STRONG
*  in the HSIOM_PORT_SELx register.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time when there is only one port pin for an
*  electrode for example).
*
* \param  lxPtr
*  Specify the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which should be connected to the sensing block as Lx pin.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISXConnectLx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *lxPtr)
{
    uint32 regValue = CY_GET_REG32 (lxPtr->pcPtr);
    regValue &= ~(0x7uL << (lxPtr->shift));
    regValue |= (`$INSTANCE_NAME`_GPIO_STRGDRV << (lxPtr->shift));
    CY_SET_REG32 (lxPtr->pcPtr, regValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXConnectRx
****************************************************************************//**
*
* \brief
*  Connects an RX electrode to the ISX scanning hardware.
*
* \details
*  This function connects a port pin (Rx electrode)to AMUXBUS-A and sets the
*  drive mode of the port pin to High-Z in the GPIO_PRT_PCx register.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time when there is only one port pin for an
*  electrode for example).
*
* \param  rxPtr
*  Specify the pointer to the FLASH_IO_STRUCT object belonging to a sensor
*  which should be connected to the sensing block as Rx pin.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISXConnectRx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *rxPtr)
{
    uint32 regValue = CY_GET_REG32 (rxPtr->pcPtr);
    regValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << rxPtr->shift);
    CY_SET_REG32 (rxPtr->pcPtr, regValue);

    regValue = CY_GET_REG32 (rxPtr->hsiomPtr);
    regValue |=  (`$INSTANCE_NAME`_HSIOM_SEL_AMUXA << rxPtr->hsiomShift);
    CY_SET_REG32 (rxPtr->hsiomPtr, regValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXDisconnectLx
****************************************************************************//**
*
* \brief
*  Disconnects a LX electrode from the ISX scanning hardware.
*
* \details
*  This function disconnects a port pin (Lx electrode) from the forcing
*  signal.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time when there is only one port pin for an
*  electrode for example).
*
* \param  lxPtr
*  Specify the pointer to the FLASH_IO_STRUCT object belonging to a Lx pin
*  sensor which should be disconnected from the sensing block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISXDisconnectLx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *lxPtr)
{
    uint32 regValue = CY_GET_REG32 (lxPtr->pcPtr);
    regValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << (lxPtr->shift));
    CY_SET_REG32 (lxPtr->pcPtr, regValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ISXDisconnectRx
****************************************************************************//**
*
* \brief
*  Disconnects an RX electrode from the ISX scanning hardware.
*
* \details
*  This function disconnects a port pin (Rx electrode) from AMUXBUS_A and
*  configures the port pin to the strong drive mode. It is assumed that the
*  data register (GPIO_PRTx_DR) of the port pin is already 0.
*
*  It is not recommended to call this function directly from the application
*  layer. This function should be used to implement only the user’s specific
*  use cases (for faster execution time when there is only one port pin for
*  an electrode for example).
*
* \param  rxPtr
*  Specify the pointer to the FLASH_IO_STRUCT object belonging to a Rx pin
*  sensor which should be disconnected from the sensing block.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISXDisconnectRx(`$INSTANCE_NAME`_FLASH_IO_STRUCT const *rxPtr)
{
    /* Clear HSIOM connection. */
    uint32 regValue = CY_GET_REG32 (rxPtr->hsiomPtr);
    regValue &= ~(rxPtr->hsiomMask);
    CY_SET_REG32 (rxPtr->hsiomPtr, regValue);

    /* Set drive mode to Strong Drive. */
    regValue = CY_GET_REG32 (rxPtr->pcPtr);
    regValue &= ~(`$INSTANCE_NAME`_GPIO_PC_MASK << rxPtr->shift);
    regValue |=  (`$INSTANCE_NAME`_GPIO_STRGDRV << rxPtr->shift);
    CY_SET_REG32 (rxPtr->pcPtr, regValue);

    /* Set data register (drive level) to 0. */
    regValue = CY_GET_REG32 (rxPtr->drPtr);
    regValue &=  ~(rxPtr->mask);
    CY_SET_REG32 (rxPtr->drPtr, regValue);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CalcISXScanPeriod
****************************************************************************//**
*
* \brief
*   Calculates scan  period for ISX.
*
* \details
*   This function calculates scan period for ISX considering deadband cycles.
*
* \param  wdgtPtr The pointer to a register map object that contains widget
*                     information.
*
* \return     Returns the ISX scan period for the widget.
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_CalcISXScanPeriod(`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT const *wdgtPtr)
{
    uint32 scanPeriod = (uint32)(wdgtPtr->snsClk);

    /* wdgtPtr->resolution contains Number of Subconversions for ISX mode. */
    scanPeriod  = LO16((uint32)wdgtPtr->resolution * (scanPeriod - `$INSTANCE_NAME`_ISX_DEADBAND_CYCLES_NUMBER));

    /* return the scan period */
    return ((uint16)scanPeriod);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsISXScanISR
****************************************************************************//**
*
* \brief
*  This is the handler of the WDT interrupt in CPU NVIC. The handler is executed
*  when normal sample is complete.
*
* \details
*  This handler covers the following functionality:
*   - Read result of measurement and store it into the corresponding register of
*     the data structure.
*   - If the Noise Metric functionality is enabled then repeat scan of the
*     current sensor if the number of bad conversions is greater than Noise
*     Metric Threshold.
*   - Initiate scan of the next sensor for the multiple-sensor scanning mode.
*   - Update the Status register in the data structure.
*   - Switch HW block to the default state if scanning of all sensors is
*     complete.
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_SsISXScanISR)
{
#if(0u != `$INSTANCE_NAME`_ISX_NOISE_METRIC_EN)
    uint32 memWorkingReg;
#endif /* (0u != `$INSTANCE_NAME`_ISX_NOISE_METRIC_EN) */

    CyIntDisable(`$INSTANCE_NAME`_ISR_NUMBER);

    CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR, `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_CFG);

    `$INSTANCE_NAME`_isxRawCount  = (uint16)(CY_GET_REG32(`$INSTANCE_NAME`_RESULT_VAL1_PTR) &\
                                                         `$INSTANCE_NAME`_RESULT_VAL1_VALUE_MASK);

    `$INSTANCE_NAME`_isxRawCount += (uint16)(CY_GET_REG32(`$INSTANCE_NAME`_RESULT_VAL2_PTR) &\
                                                         `$INSTANCE_NAME`_RESULT_VAL2_VALUE_MASK);

    /* This workaround needed to prevent overflow in the SW register map. Cypress ID #234358 */
    if(`$INSTANCE_NAME`_isxRawCount > `$INSTANCE_NAME`_isxScanPeriod)
    {
        `$INSTANCE_NAME`_isxRawCount = `$INSTANCE_NAME`_isxScanPeriod;
    }

#if(0u != `$INSTANCE_NAME`_ISX_NOISE_METRIC_EN)
    memWorkingReg = CY_GET_REG32(`$INSTANCE_NAME`_RESULT_VAL1_PTR) >> `$INSTANCE_NAME`_RESULT_VAL1_BAD_CONVS_SHIFT;

    if((memWorkingReg > `$INSTANCE_NAME`_ISX_NOISE_METRIC_TH) && (`$INSTANCE_NAME`_isxResamplingCyclesCnt > 0uL))
    {
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SCAN_CSD_SEQ_START_CFG);
        `$INSTANCE_NAME`_isxResamplingCyclesCnt--;
    }
    else
    {
        `$INSTANCE_NAME`_ISXPostScanApiPtr();
        `$INSTANCE_NAME`_isxResamplingCyclesCnt = `$INSTANCE_NAME`_RESAMPLING_CYCLES_MAX_NUMBER;
    }
#else
    `$INSTANCE_NAME`_ISXPostScanApiPtr();
#endif /* (0u != `$INSTANCE_NAME`_ISX_NOISE_METRIC_EN) */

    if(`$INSTANCE_NAME`_NOT_BUSY == (`$INSTANCE_NAME`_dsRam.status & `$INSTANCE_NAME`_SW_STS_BUSY))
    {
        CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CONFIG_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR, `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CSDCMP_CFG);
        CY_SET_REG32(`$INSTANCE_NAME`_IDAC_MOD_PTR, `$INSTANCE_NAME`_DEFAULT_ISX_CSD_IDACA_CFG);
    }

    CyIntEnable(`$INSTANCE_NAME`_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SsISXStartSampleExt
****************************************************************************//**
*
* \brief
*   Starts the hardware sequencer to perform the ISX conversion.
*
* \details
*   This function covers the following functionality:
*      1. Configures the hardware sequencer to perform the coarse initialization.
*      2. Waiting for completion of the coarse initialization.
*      3. Configures the hardware sequencer to perform the normal conversion.
*      4. Starts the normal conversion
*
*******************************************************************************/
CY_INLINE static void `$INSTANCE_NAME`_SsISXStartSampleExt(void)
{
    uint32 filterDelay;
    uint32 watchdogCounter;
    #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
        uint32 sampleClkFreqHz;
    #endif /* (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */

    /* Configure the CSDV2 sequencer to perform the coarse initialization. */
    CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR,           `$INSTANCE_NAME`_DEFAULT_ISX_CSD_CONFIG_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR,            `$INSTANCE_NAME`_PRECHARGE_CSD_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_PRECHARGE_CSD_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_PRECHARGE_CSD_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_PRECHARGE_CSD_SW_DSI_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_PRECHARGE_CSD_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR,    `$INSTANCE_NAME`_PRECHARGE_CSD_SW_FW_MOD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_PRECHARGE_CSD_SW_FW_TANK_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR,        `$INSTANCE_NAME`_PRECHARGE_CSD_SEQ_START_CFG);

    /* Wait for the HSCMP trigger and return the sequencer to the IDLE state. */
    watchdogCounter = `$INSTANCE_NAME`_ISX_PRECHARGE_WATCHDOG_CYCLES_NUM;
    while((0u != (`$INSTANCE_NAME`_SEQ_START_START_MASK & CY_GET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR))) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    }

    /* Reset the sequencer to the IDLE state if HSCMP not triggered till watchdog period is out. */
    if(0u != (`$INSTANCE_NAME`_SEQ_START_START_MASK & CY_GET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR)))
    {
        CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR,  `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SEQ_START_CFG);
    }

    #if (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ)
        sampleClkFreqHz = CYDEV_BCLK__HFCLK__HZ / (uint32)`$INSTANCE_NAME`_dsRam.modIsxClk;
        if(sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ)
        {
            filterDelay = `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ;
        }
        else if(sampleClkFreqHz <= `$INSTANCE_NAME`_MOD_CSD_CLK_24MHZ)
        {
            filterDelay = `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_24MHZ;
        }
        else
        {
            filterDelay = `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_48MHZ;
        }
    #else
        filterDelay = `$INSTANCE_NAME`_CONFIG_FILTER_DELAY_12MHZ;
    #endif /* (`$INSTANCE_NAME`_MOD_CSD_CLK_12MHZ < CYDEV_BCLK__HFCLK__HZ) */

    /* Configure the CSDV2 sequencer to perform the normal conversion. */
    CY_SET_REG32(`$INSTANCE_NAME`_CONFIG_PTR, `$INSTANCE_NAME`_PRESCAN_CSD_CONFIG_CFG | filterDelay);
    CY_SET_REG32(`$INSTANCE_NAME`_CSDCMP_PTR, `$INSTANCE_NAME`_PRESCAN_CSD_CSDCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_HSCMP_PTR,            `$INSTANCE_NAME`_DEFAULT_ISX_CSD_HSCMP_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_P_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_HS_P_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_HS_N_SEL_PTR,      `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_HS_N_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_DSI_SEL_PTR,       `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_DSI_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_SHIELD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_SHIELD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_MOD_SEL_PTR,    `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_FW_MOD_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_FW_TANK_SEL_PTR,   `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_FW_TANK_SEL_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_INTR_PTR,             `$INSTANCE_NAME`_DEFAULT_ISX_CSD_INTR_CFG);
    CY_SET_REG32(`$INSTANCE_NAME`_SW_BYP_SEL_PTR,       `$INSTANCE_NAME`_DEFAULT_ISX_CSD_SW_BYP_SEL_CFG);

    /* Start the normal conversion. */
    CY_SET_REG32(`$INSTANCE_NAME`_SEQ_START_PTR, `$INSTANCE_NAME`_SCAN_CSD_SEQ_START_CFG);
}

#endif  /* (0u != `$INSTANCE_NAME`_ISX_EN) */


/* [] END OF FILE */
