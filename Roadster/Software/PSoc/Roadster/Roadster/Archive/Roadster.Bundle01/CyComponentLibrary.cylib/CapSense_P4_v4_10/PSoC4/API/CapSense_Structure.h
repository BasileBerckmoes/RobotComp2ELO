/***************************************************************************//**
* \file `$INSTANCE_NAME`_Structure.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file provides the top level declarations of the Component data structure.
*   Also, the file declares the high-level and low-level APIs for data access.
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

#if !defined(CY_SENSE_`$INSTANCE_NAME`_STRUCTURE_H)
#define CY_SENSE_`$INSTANCE_NAME`_STRUCTURE_H

#include <cytypes.h>
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_Configuration.h"
#if (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE)
    #include "`$INSTANCE_NAME`_SmartSense_LL.h"
#endif  /* (`$INSTANCE_NAME`_CSD_SS_DIS != `$INSTANCE_NAME`_CSD_AUTOTUNE) */
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ALP_FILTER_EN)
    #include "`$INSTANCE_NAME`_AlpFilter_LL.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_ALP_FILTER_EN) */

/*******************************************************************************
* Constant Definitions
*******************************************************************************/

/* Defines size of Sensor Status Register in Data Structure */
#define `$INSTANCE_NAME`_SNS_STS_TYPE               `$SensorStatusType`

/* No touch condition for slider position report */
#define `$INSTANCE_NAME`_SLIDER_NO_TOUCH            (0xFFFFu)
#define `$INSTANCE_NAME`_TOUCHPAD_NO_TOUCH          (0xFFFFFFFFLu)

#define `$INSTANCE_NAME`_SLIDER_POS_NONE            (0xFFFFu)
#define `$INSTANCE_NAME`_TOUCHPAD_POS_NONE          (0xFFFFu)

#define `$INSTANCE_NAME`_MATRIX_POS_NONE            (0xFFu)
#define `$INSTANCE_NAME`_MATRIX_POS_MULTI           (0xFEu)

#define `$INSTANCE_NAME`_PROX_STS_MASK              (3Lu)
#define `$INSTANCE_NAME`_PROX_STS_OFFSET(proxId)    ((proxId) << 1u)
    
#define `$INSTANCE_NAME`_MATRIX_BUTTONS_TOUCHED     (0x80000000Lu)

/*******************************************************************************
* Enumeration types definition
*******************************************************************************/

/***************************************************************************//**
* \brief Defines widget types
*******************************************************************************/
typedef enum
{
    `$INSTANCE_NAME`_WD_BUTTON_E            = 0x01u,
    `$INSTANCE_NAME`_WD_LINEAR_SLIDER_E     = 0x02u,
    `$INSTANCE_NAME`_WD_RADIAL_SLIDER_E     = 0x03u,
    `$INSTANCE_NAME`_WD_MATRIX_BUTTON_E     = 0x04u,
    `$INSTANCE_NAME`_WD_TOUCHPAD_E          = 0x05u,
    `$INSTANCE_NAME`_WD_PROXIMITY_E         = 0x06u
} `$INSTANCE_NAME`_WD_TYPE_ENUM;


/***************************************************************************//**
* \brief Defines sensing methods types
*******************************************************************************/
typedef enum
{
    `$INSTANCE_NAME`_UNDEFINED_E            = 0x00u,
    `$INSTANCE_NAME`_SENSE_METHOD_CSD_E     = 0x01u,
    `$INSTANCE_NAME`_SENSE_METHOD_CSX_E     = 0x02u,
    `$INSTANCE_NAME`_SENSE_METHOD_BIST_E    = 0x03u,
    `$INSTANCE_NAME`_SENSE_METHOD_ISX_E     = 0x04u,
} `$INSTANCE_NAME`_SENSE_METHOD_ENUM;

/***************************************************************************//**
* \brief Defines electrode types
*******************************************************************************/
typedef enum
{
    `$INSTANCE_NAME`_ELTD_TYPE_SELF_E       = 0x01u,
    `$INSTANCE_NAME`_ELTD_TYPE_MUT_TX_E     = 0x02u,
    `$INSTANCE_NAME`_ELTD_TYPE_MUT_RX_E     = 0x03u
} `$INSTANCE_NAME`_ELTD_TYPE_ENUM;

`$RamAuxStruct`

/**
* \cond SECTION_STRUCTURES
* \addtogroup group_structures
* \{
*/

/*******************************************************************************
* Declares RAM structures for all used widgets
*******************************************************************************/
`$RamWidgetStruct`

/***************************************************************************//**
* \brief Declares RAM structure with all defined widgets
*******************************************************************************/
typedef struct
{
`$RamWidgetListStruct`
} `$INSTANCE_NAME`_RAM_WD_LIST_STRUCT;


/***************************************************************************//**
* \brief Declares RAM structure for sensors
*******************************************************************************/
typedef struct
{
`$RamSensorStruct`
} `$INSTANCE_NAME`_RAM_SNS_STRUCT;


/***************************************************************************//**
* \brief Declares RAM structure with all defined sensors
*******************************************************************************/
typedef struct
{
`$RamSensorListStruct`
} `$INSTANCE_NAME`_RAM_SNS_LIST_STRUCT;

`$RamSelfTestStruct`
/***************************************************************************//**
* \brief Declares the top-level RAM Data Structure
*******************************************************************************/
typedef struct
{
`$RamStruct`
} `$INSTANCE_NAME`_RAM_STRUCT;


/***************************************************************************//**
* \brief Declares the Flash IO object
*******************************************************************************/
typedef struct
{
    /**
     *  Pointer to the HSIOM configuration register of the IO.
     */
    reg32  * hsiomPtr;

    /**
     *  Pointer to the port configuration register of the IO.
     */
    reg32  * pcPtr;
`$IoPc2Ptr`
    /**
     *  Pointer to the port data register of the IO.
     */
    reg32  * drPtr;

    /**
     *  Pointer to the pin state data register of the IO.
     */
    reg32  * psPtr;

    /**
     *  IO mask in the HSIOM configuration register.
     */
    uint32   hsiomMask;

    /**
     *  IO mask in the DR and PS registers.
     */
    uint32   mask;

    /**
     *  Position of the IO configuration bits in the HSIOM register.
     */
    uint8    hsiomShift;

    /**
     *  Position of the IO configuration bits in the DR and PS registers.
     */
    uint8    drShift;

    /**
     *  Position of the IO configuration bits in the PC register.
     */
    uint8    shift;
} `$INSTANCE_NAME`_FLASH_IO_STRUCT;


/***************************************************************************//**
* \brief Declares the Flash Electrode object
*******************************************************************************/
typedef struct
{
    /**
     *  Index of the first IO in the Flash IO Object Array.
     */
    uint16 firstPinId;

    /**
     *  Total number of IOs in this sensor.
     */
    uint8  numPins;

    /**
     * Sensor type:
     * - ELTD_TYPE_SELF_E - CSD sensor;
     * - ELTD_TYPE_MUT_TX_E - CSX Tx / ISX Lx sensor;
     * - ELTD_TYPE_MUT_RX_E - CSX Rx / ISX Rx sensor;
     */
    uint8  type;
} `$INSTANCE_NAME`_FLASH_SNS_STRUCT;


/***************************************************************************//**
* \brief Declares the structure with all Flash electrode objects
*******************************************************************************/
typedef struct
{
`$FlashSensorListStruct`
} `$INSTANCE_NAME`_FLASH_SNS_LIST_STRUCT;


/***************************************************************************//**
* \brief Declares Flash widget object
*******************************************************************************/
typedef struct
{
`$FlashWidgetStruct`
} `$INSTANCE_NAME`_FLASH_WD_STRUCT;


/***************************************************************************//**
* \brief Declares top-level Flash Data Structure
*******************************************************************************/
typedef struct
{
`$FlashStruct`
} `$INSTANCE_NAME`_FLASH_STRUCT;

`$ShieldIoStruct`
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN)
    /***************************************************************************//**
    * \brief Define the structure for test of baseline and raw count limits which 
    * will be determined by user for every sensor grounding on the 
    * manufacturing specific data 
    *******************************************************************************/
    typedef struct
    {
        /**
         *  Upper limit of a sensor baseline.
         */
        uint16 bslnHiLim;
        /**
         *  Lower limit of a sensor baseline.
         */
        uint16 bslnLoLim;
        /**
         *  Upper limit of a sensor raw count.
         */
        uint16 rawHiLim;
        /**
         *  Lower limit of a sensor raw count.
         */
        uint16 rawLoLim;
    } `$INSTANCE_NAME`_BSLN_RAW_RANGE_STRUCT;
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_BSLN_RAW_OUT_RANGE_EN) */

/** \}
* \endcond */


/***************************************************************************//**
* Declares Dual-channel scan structure
*******************************************************************************/
typedef struct
{
    uint8 csd0WidgetId;
    uint8 csd0SensorId;
    uint8 csd1WidgetId;
    uint8 csd1SensorId;
} `$INSTANCE_NAME`_SCAN_SLOT_STRUCT;


/***************************************************************************//**
* Declares Filter module structures
*******************************************************************************/
`$FilterStruct`

typedef struct
{
    uint16 posMedianZ1;
    uint16 posMedianZ2;
} `$INSTANCE_NAME`_SLIDER_POS_HISTORY_STRUCT;

typedef struct
{
    `$INSTANCE_NAME`_SLIDER_POS_HISTORY_STRUCT xPos;
    `$INSTANCE_NAME`_SLIDER_POS_HISTORY_STRUCT yPos;
} `$INSTANCE_NAME`_TOUCHPAD_POS_HISTORY_STRUCT;

/*******************************************************************************
* API Constants
*******************************************************************************/

/*******************************************************************************
* Defines shift/mask values for data structure register bit fields
*******************************************************************************/

`$CsdConfigBitField`
`$StatusBitField`
`$StaticConfigBitField`

/*******************************************************************************
* Define Data Structure Macro helpers
*******************************************************************************/

/*******************************************************************************
* Determines the widget specific word in the wdgtStatus array by widget ID
*******************************************************************************/

/* Divide by 32 - size of the wdgtStatus word in bits to find the word index */
#define `$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdgtId)  ((wdgtId) >> 5u)

/*******************************************************************************
* Determines the widget bitmask in wdgtStatus word by widget ID
*******************************************************************************/

/* Take the least 5 bits of widget id to find the bit number */
#define `$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdgtId)   (1Lu << ((wdgtId) & 0x1FLu))

/*******************************************************************************
* Determines the sense method of the widget
*******************************************************************************/

/* If there are multiple sensing methods, get senseMethod from flash structure,
   otherwise, hardcode it for speed. */
#if (`$INSTANCE_NAME`_USES_MANY_SENSE_MODES)
    #define `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlash) ((`$INSTANCE_NAME`_SENSE_METHOD_ENUM)(ptrFlash)->senseMethod)
#elif (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
    #define `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlash) `$INSTANCE_NAME`_SENSE_METHOD_CSD_E
#elif (0u != `$INSTANCE_NAME`_TOTAL_CSX_WIDGETS)
    #define `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlash) `$INSTANCE_NAME`_SENSE_METHOD_CSX_E
#elif (0u != `$INSTANCE_NAME`_TOTAL_ISX_WIDGETS)
    #define `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlash) `$INSTANCE_NAME`_SENSE_METHOD_ISX_E
#endif /* (`$INSTANCE_NAME`_USES_MANY_SENSE_MODES) */

/*******************************************************************************
* Gets the widget type
*******************************************************************************/
#define `$INSTANCE_NAME`_GET_WIDGET_TYPE(ptrFlashWdgt)  ((`$INSTANCE_NAME`_WD_TYPE_ENUM)((ptrFlashWdgt)->wdgtType))

/*******************************************************************************
* Gets the number of the widget's sensors
*******************************************************************************/
#define `$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)         `$INSTANCE_NAME`_dsFlash.wdgtArray[(widgetId)].totalNumSns
#define `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrFlashWidget) (ptrFlashWidget)->totalNumSns


/*******************************************************************************
* Increments the pointer to the Regular Filter History Object
*******************************************************************************/
#if ((0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN) &&                                               \
     ((0u != `$INSTANCE_NAME`_BUTTON_WIDGET_EN) || (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN)  ||    \
      (0u != `$INSTANCE_NAME`_MATRIX_WIDGET_EN) || (0u != `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN)))

    #define `$INSTANCE_NAME`_INC_REG_FLTR_OBJ(fltrVariant)    \
    do {                                                      \
        (fltrVariant).ptrRegular++;                           \
    } while(0)

#else

    #define `$INSTANCE_NAME`_INC_REG_FLTR_OBJ(fltrVariant)

#endif /* #if ((0u != `$INSTANCE_NAME`_REGULAR_RC_FILTER_EN) &&                                 
               ((0u != `$INSTANCE_NAME`_BUTTON_WIDGET_EN) || (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN)  ||
                (0u != `$INSTANCE_NAME`_MATRIX_WIDGET_EN) || (0u != `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN))) */


/*******************************************************************************
* Increments the pointer to the Proximity Filter History Object
*******************************************************************************/
#if ((0u != `$INSTANCE_NAME`_PROX_RC_FILTER_EN) && (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN))
    #define `$INSTANCE_NAME`_INC_PROX_FLTR_OBJ(fltrVariant)     \
        do {                                                    \
            (fltrVariant).ptrProx++;                            \
        } while(0)
#else
    #define `$INSTANCE_NAME`_INC_PROX_FLTR_OBJ(fltrVariant)
#endif /* #if ((0u != `$INSTANCE_NAME`_PROX_RC_FILTER_EN) && (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN)) */


/*******************************************************************************
* Increments the pointer to the Filter History Object Variant
*******************************************************************************/
#define `$INSTANCE_NAME`_INC_FLTR_OBJ_VARIANT(isProxHistObj, fltrVariant)   \
    do {                                                                    \
        if (0u == (isProxHistObj))                                          \
        {                                                                   \
            `$INSTANCE_NAME`_INC_REG_FLTR_OBJ(fltrVariant);                 \
        }                                                                   \
        else                                                                \
        {                                                                   \
            `$INSTANCE_NAME`_INC_PROX_FLTR_OBJ(fltrVariant);                \
        }                                                                   \
    } while(0)

/*******************************************************************************
* Gets a widget status in the global enable register dsRam.wdgtEnable[]
*******************************************************************************/
#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #define `$INSTANCE_NAME`_GET_WIDGET_EN_STATUS(wdId)                                                     \
                 (`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdId) &                                             \
                  `$INSTANCE_NAME`_dsRam.wdgtEnable[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdId)] &         \
                  `$INSTANCE_NAME`_dsRam.wdgtWorking[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdId)])
#else
    #define `$INSTANCE_NAME`_GET_WIDGET_EN_STATUS(wdId)                    \
                (`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdId) &             \
                 `$INSTANCE_NAME`_dsRam.wdgtEnable[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdId)])
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN) */

/*******************************************************************************
* Gets a widget active status from the dsRam.wdgtStatus[] register
*******************************************************************************/
#define `$INSTANCE_NAME`_GET_WIDGET_ACTIVE_STATUS(wdId)                    \
            (`$INSTANCE_NAME`_GET_WDGT_STATUS_MASK(wdId) &                 \
             `$INSTANCE_NAME`_dsRam.wdgtStatus[`$INSTANCE_NAME`_GET_WDGT_STATUS_INDEX(wdId)])

/*******************************************************************************
* Declares Flash and RAM Data Structure variables
*******************************************************************************/
extern `$INSTANCE_NAME`_RAM_STRUCT            `$INSTANCE_NAME`_dsRam;
extern const `$INSTANCE_NAME`_FLASH_STRUCT    `$INSTANCE_NAME`_dsFlash;
extern const `$INSTANCE_NAME`_FLASH_IO_STRUCT `$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_TOTAL_ELECTRODES];
`$ShieldIoVar`
`$AdcIoVar`
`$ScanSlotListVar`

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/*******************************************************************************
* High-level API
*******************************************************************************/

/**
* \cond (SECTION_C_HIGH_LEVEL || SECTION_I_HIGH_LEVEL)
* \addtogroup group_c_high_level
* \{
*/

uint32 `$INSTANCE_NAME`_IsAnyWidgetActive(void);
uint32 `$INSTANCE_NAME`_IsWidgetActive(uint32 widgetId);
uint32 `$INSTANCE_NAME`_IsSensorActive(uint32 widgetId, uint32 sensorId);

#if (0u != `$INSTANCE_NAME`_MATRIX_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_IsMatrixButtonsActive(uint32 widgetId);
#endif /* #if (0u != `$INSTANCE_NAME`_MATRIX_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_IsProximitySensorActive(uint32 widgetId, uint32 proxId);
#endif /* #if (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_GetCentroidPos(uint32 widgetId);
#endif /* #if (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN)
    uint32 `$INSTANCE_NAME`_GetXYCoordinates(uint32 widgetId);
#endif /* #if (0u != `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN) */

/** 
* \}
* \endcond */

/*******************************************************************************
* Low level API
*******************************************************************************/

/**
* \cond (SECTION_C_LOW_LEVEL || SECTION_I_LOW_LEVEL)
* \addtogroup group_c_low_level
* \{
*/

cystatus `$INSTANCE_NAME`_GetParam(uint32 paramId, uint32 *value);
cystatus `$INSTANCE_NAME`_SetParam(uint32 paramId, uint32 value);

/** \}
* \endcond
*/

/*******************************************************************************
* Function Prototypes - internal functions
*******************************************************************************/

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/
`$FlashExtCapMappingVar`

void `$INSTANCE_NAME`_DsInitialize(void);
#if (0u != `$INSTANCE_NAME`_ADC_EN)
    void `$INSTANCE_NAME`_AdcDsInitialize(void);
#endif /* (0u != `$INSTANCE_NAME`_ADC_EN) */

/** \}
* \endcond */

#endif /* End CY_SENSE_`$INSTANCE_NAME`_STRUCTURE_H */

/* [] END OF FILE */
