/***************************************************************************//**
* \file `$INSTANCE_NAME`_Structure.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   This file defines the data structure global variables and provides implementation
*   for the high-level and low-level APIs of the Data Structure module.
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

#if (0u != `$INSTANCE_NAME`_ADC_EN)
    #include "`$INSTANCE_NAME`_Adc.h"
#endif /* (0u != `$INSTANCE_NAME`_ADC_EN) */

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_SELF_TEST_EN)
    #include "`$INSTANCE_NAME`_SelfTest.h"
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN)
    #include "`$INSTANCE_NAME`_AdvancedCentroid_LL.h"
#endif

#if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN)
    #include "`$INSTANCE_NAME`_Gesture.h"
#endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_GES_GLOBAL_EN) */

/*******************************************************************************
* Defines the RAM Data Structure variables and their init data in flash
*******************************************************************************/
/**
* \cond SECTION_GLOBAL_VARIABLES
* \addtogroup group_global_variables
* \{
*/

/**
* The variable that contains the `$INSTANCE_NAME` configuration, settings and
* scanning results. `$INSTANCE_NAME`_dsRam represents RAM Data Structure.
*/
`$INSTANCE_NAME`_RAM_STRUCT `$INSTANCE_NAME`_dsRam;
/** \}
* \endcond */

/*******************************************************************************
* Declares Widget's De-bounce Counters
*******************************************************************************/
`$DebounceInit`
`$RamAuxInit`
/*******************************************************************************
* Defines and initializes the Flash Data Structure
*******************************************************************************/

`$RamBallisticInit`
/**
* \cond SECTION_API_CONSTANTS
* \addtogroup group_api_constants
* \{
*/
/**
* Constant for the FLASH Data Structure
*/
const `$INSTANCE_NAME`_FLASH_STRUCT `$INSTANCE_NAME`_dsFlash =
{
    /* Flash Widget Initialization Data */
`$FlashWidgetInit`
`$FlashSensorInit`};

/**
* The array of the pointers to the electrode specific register.
*/
const `$INSTANCE_NAME`_FLASH_IO_STRUCT `$INSTANCE_NAME`_ioList[`$INSTANCE_NAME`_TOTAL_ELECTRODES] =
{
`$IoInit`};
`$ShieldIoInit`
`$AdcIoInit`
`$ScanSlotListInit`
/** \}
* \endcond */

/* Initialization data for RAM widget list */
const `$INSTANCE_NAME`_RAM_WD_LIST_STRUCT `$INSTANCE_NAME`_ramWidgetInit =
{
`$RamWidgetInit`};
`$RamIdacInit`
`$RamGesturesInit`
/*******************************************************************************
* Defines internal data types and statements
*******************************************************************************/
#define PARAM_TYPE_OFFSET       (30u)
#define PARAM_TYPE_MASK         (3Lu << PARAM_TYPE_OFFSET)
#define PARAM_RWBIT_OFFSET      (29u)
#define PARAM_RWBIT_MASK        (1Lu << PARAM_RWBIT_OFFSET)
#define PARAM_FBIT_OFFSET       (28u)
#define PARAM_FBIT_MASK         (1Lu << PARAM_FBIT_OFFSET)
#define PARAM_UBIT_OFFSET       (23u)
#define PARAM_UBIT_MASK         (1Lu << PARAM_UBIT_OFFSET)
#define PARAM_WDID_OFFSET       (16u)
#define PARAM_WDID_MASK         (0x7FLu << PARAM_WDID_OFFSET)
#define PARAM_CRC_OFFSET        (24u)
#define PARAM_CRC_MASK          (0x0FLu << PARAM_CRC_OFFSET)

/* Defines align masks for uint16 and uint32 */
#define UINT16_ALIGN_MASK       (1Lu)
#define UINT32_ALIGN_MASK       (3Lu)

/* Defines supported parameter types */
#define DS_PARAM_TYPE_UINT8     (0x01u)
#define DS_PARAM_TYPE_UINT16    (0x02u)
#define DS_PARAM_TYPE_UINT32    (0x03u)


/* Defines PARAM_ID structure */
typedef struct
{
    uint16 offset;      /* parameter offset */
    uint8  widgetId;    /* widget Id parameter belongs to */
    uint8  affectsCrc;  /* parameter affects widget CRC */
    uint8  crc;         /* parameter CRC */
    uint8  flash;       /* parameter located in FLASH flag */
    uint8  rw;          /* parameter is read/write flag */
    uint8  type;        /* parameter type: uint8/uint16/uint32 */
} PARAM_ID_STRUCT;


/*******************************************************************************
* Static Function Prototypes
*******************************************************************************/
/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

`$FlashExtCapMappingInit`

static cystatus DsParseParamId(uint32 paramId, PARAM_ID_STRUCT *pData);

/** \}
* \endcond */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DsInitialize
****************************************************************************//**
*
* \brief
*   This function initializes the Data Structure storage.
*
* \details
*   This function copies the default widget configuration parameters
*   from the Flash storage into the RAM Data Structure.
*
*******************************************************************************/
void `$INSTANCE_NAME`_DsInitialize(void)
{
    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) || \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSD_IDAC_COMP_EN) || \
        ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)))
        uint32 snsId;
        uint32 wdgtId;
        `$INSTANCE_NAME`_RAM_SNS_STRUCT * ptrSnsTmp;
        `$INSTANCE_NAME`_FLASH_WD_STRUCT const * ptrFlashWdgt;
    #endif

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES))
        uint16 subConvNumber;
    #endif

    #if ((0u != `$INSTANCE_NAME`_CSX_EN) || (0 != `$INSTANCE_NAME`_CSD_IDAC_COMP_EN))
        uint8 const * ptrIdacInit = `$INSTANCE_NAME`_ramIdacInit;
    #endif

    /* Reset RAM data structure content */
    (void)memset(&`$INSTANCE_NAME`_dsRam, 0, sizeof(`$INSTANCE_NAME`_dsRam));

    /* Initialize configId, deviceId and hwClock registers */
    `$INSTANCE_NAME`_dsRam.configId = `$INSTANCE_NAME`_CONFIG_ID;
    `$INSTANCE_NAME`_dsRam.deviceId = `$INSTANCE_NAME`_DEVICE_ID;
    `$INSTANCE_NAME`_dsRam.hwClock = `$INSTANCE_NAME`_HW_CLOCK;

    /* Initialize global RAM data */
    `$INSTANCE_NAME`_dsRam.csd0Config = `$INSTANCE_NAME`_CSD0_CONFIG;

    #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS)
        `$INSTANCE_NAME`_dsRam.modCsdClk = `$INSTANCE_NAME`_CSD_SCANSPEED_DIVIDER;

        #if (0u != `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN)
            `$INSTANCE_NAME`_dsRam.snsCsdClk = `$INSTANCE_NAME`_CSD_SNS_CLK_DIVIDER;
        #endif /* #if (0u != `$INSTANCE_NAME`_CSD_COMMON_SNS_CLK_EN) */
    #endif /* #if (0u != `$INSTANCE_NAME`_TOTAL_CSD_WIDGETS) */

    #if (0u != `$INSTANCE_NAME`_CSX_EN)
        `$INSTANCE_NAME`_dsRam.modCsxClk = `$INSTANCE_NAME`_CSX_SCANSPEED_DIVIDER;

        #if (0u != `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN)
            `$INSTANCE_NAME`_dsRam.snsCsxClk = `$INSTANCE_NAME`_CSX_TX_CLK_DIVIDER;
        #endif /* #if (0u != `$INSTANCE_NAME`_CSX_COMMON_TX_CLK_EN) */
    #endif /* #if (0u != `$INSTANCE_NAME`_CSX_EN) */

    #if (0u != `$INSTANCE_NAME`_ISX_EN)
        `$INSTANCE_NAME`_dsRam.modIsxClk = `$INSTANCE_NAME`_ISX_SCANSPEED_DIVIDER;
    #endif /* #if (0u != `$INSTANCE_NAME`_ISX_EN) */

    #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN)
        `$INSTANCE_NAME`_dsRam.glbCrc = `$INSTANCE_NAME`_GLB_CRC;
    #endif /* #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN) */

    /* Initialize RAM widget data */
    `$INSTANCE_NAME`_dsRam.wdgtList = `$INSTANCE_NAME`_ramWidgetInit;

    /* Initialize Gesture configuration structure */
    #if ((0u != `$INSTANCE_NAME`_GES_GLOBAL_EN) || (0u != `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN))
        `$INSTANCE_NAME`_dsRam.timestampInterval = `$INSTANCE_NAME`_TIMESTAMP_INTERVAL;
    #endif /* ((0u != `$INSTANCE_NAME`_GES_GLOBAL_EN) || (0u != `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN)) */
        
    #if (0u != `$INSTANCE_NAME`_GES_GLOBAL_EN)
        `$INSTANCE_NAME`_dsRam.gestures = `$INSTANCE_NAME`_ramGesturesInit;
    #endif /* (0u != `$INSTANCE_NAME`_GES_GLOBAL_EN) */

    #if (0u != `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN)
        `$INSTANCE_NAME`_dsRam.ballisticConfig = `$INSTANCE_NAME`_ramBallisticInit;
    #endif /* (0u != `$INSTANCE_NAME`_BALLISTIC_MULTIPLIER_EN) */

    #if (0u != `$INSTANCE_NAME`_CSX_EN) || (0 != `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)
        /* Initialize IDAC data */
        ptrFlashWdgt = `$INSTANCE_NAME`_dsFlash.wdgtArray;

        for (wdgtId = `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtId-- > 0u; )
        {
            ptrSnsTmp = ptrFlashWdgt->ptr2SnsRam;

            for (snsId = `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrFlashWdgt); snsId-- > 0u;)
            {
                ptrSnsTmp->idacComp[0u] = *ptrIdacInit;
                ptrIdacInit++;

                #if (0u != `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN)
                    ptrSnsTmp->idacComp[1u] = *ptrIdacInit;
                    ptrIdacInit++;

                    ptrSnsTmp->idacComp[2u] = *ptrIdacInit;
                    ptrIdacInit++;
                #endif /* #if (0u != `$INSTANCE_NAME`_MULTI_FREQ_SCAN_EN) */

                ptrSnsTmp++;
            }

            ptrFlashWdgt++; /* Move to next widget */
        }
    #endif /*(0u != `$INSTANCE_NAME`_CSX_EN) || (0 != `$INSTANCE_NAME`_CSD_IDAC_COMP_EN)*/

    #if ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
         (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES))
        /* Initialize Sub-Conversion Number for each node of each CSX widget */
        ptrFlashWdgt = `$INSTANCE_NAME`_dsFlash.wdgtArray;
        for (wdgtId = `$INSTANCE_NAME`_TOTAL_WIDGETS; wdgtId-- > 0u;)
        {
            /* Check for widget sense method */
            if (`$INSTANCE_NAME`_SENSE_METHOD_CSX_E == `$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
            {
                /* Take the sub-convesion number of a CSX widget and initialize each node of this widget */
                subConvNumber = ((`$INSTANCE_NAME`_RAM_WD_BASE_STRUCT *)(ptrFlashWdgt->ptr2WdgtRam))->resolution;
                ptrSnsTmp = ptrFlashWdgt->ptr2SnsRam;
                for (snsId = `$INSTANCE_NAME`_GET_SNS_CNT_BY_PTR(ptrFlashWdgt); snsId-- > 0u;)
                {
                    ptrSnsTmp->subConvNum = subConvNumber;
                    ptrSnsTmp++;
                }
            }
            /* Move to the next widget */
            ptrFlashWdgt++;
        }
    #endif /* ((`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_EN) && \
               (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CSX_SKIP_OVSMPL_SPECIFIC_NODES)) */

    #if (0u != `$INSTANCE_NAME`_ADC_EN)
        `$INSTANCE_NAME`_AdcDsInitialize();
    #endif /* (0u != `$INSTANCE_NAME`_ADC_EN) */
}


#if (0u != `$INSTANCE_NAME`_ADC_EN)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_AdcDsInitialize
    ****************************************************************************//**
    *
    * \brief
    *   Configures the initial Adc datastructure members.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_AdcDsInitialize(void)
    {
        `$INSTANCE_NAME`_dsRam.adcResolution = `$INSTANCE_NAME`_ADC_RESOLUTION;
        `$INSTANCE_NAME`_dsRam.adcIdac = (uint8)(`$INSTANCE_NAME`_ADC_IDAC_DEFAULT);
        `$INSTANCE_NAME`_dsRam.adcActiveCh = `$INSTANCE_NAME`_`$AdcModulePrefix`NO_CHANNEL;
    }
#endif /* (0u != `$INSTANCE_NAME`_ADC_EN) */


/*******************************************************************************
* Function Name: DsParseParamId
****************************************************************************//**
*
* \brief
*   This function parses the parameter ID and checks its correctness.
*
* \details
*   This function checks the parameter CRC if the self-test is enabled,
*   validates the offset value and parameter type.
*
* \param paramId The parameter to parse.
* \param pData   The pointer to the structure that will hold parsed data.
*
* \return CYRET_SUCCESS     If the parameter is valid
*         CYRET_BAD_PARAM   If the parameter is invalid
*
*******************************************************************************/
static cystatus DsParseParamId(uint32 paramId, PARAM_ID_STRUCT *pData)
{
    cystatus result = CYRET_SUCCESS;

    #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN)
        const uint8 crcTable[] =
        {
            0x00u, 0x09u, 0x0Bu, 0x02u, 0x0Fu, 0x06u, 0x04u, 0x0Du,
            0x07u, 0x0Eu, 0x0Cu, 0x05u, 0x08u, 0x01u, 0x03u, 0x0Au
        };

        uint32 i;
        uint32 actualCrc = 0u;
        uint32 crcIndex;
    #endif /* #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN) */

    /* Extract parameter data */
    pData->offset     = LO16(paramId);
    pData->affectsCrc = LO8((paramId & PARAM_UBIT_MASK)  >> PARAM_UBIT_OFFSET);
    pData->widgetId   = LO8((paramId & PARAM_WDID_MASK)  >> PARAM_WDID_OFFSET);
    pData->type       = LO8((paramId & PARAM_TYPE_MASK)  >> PARAM_TYPE_OFFSET);
    pData->flash      = LO8((paramId & PARAM_FBIT_MASK)  >> PARAM_FBIT_OFFSET);
    pData->rw         = LO8((paramId & PARAM_RWBIT_MASK) >> PARAM_RWBIT_OFFSET);
    pData->crc        = LO8((paramId & PARAM_CRC_MASK)   >> PARAM_CRC_OFFSET);

    /* Check parameter CRC if self-test is enabled */
    #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN)

        /* Calculate CRC for bits 0..24.
         * The CRC is calculated using nibbles (4-bits).
         * So for 0..24 bits there are in total 6 nibbles. */
        for (i = 6u; i > 0u; i--)
        {
            crcIndex = actualCrc ^ (paramId & 0x0Fu);
            actualCrc = crcTable[crcIndex];
            paramId >>= 4u;
        }

        /* Add bits 28..32 */
        crcIndex = actualCrc ^ ((paramId >> 4u) & 0x0Fu);
        actualCrc = crcTable[crcIndex];

        /* Add bits 24..28 (CRC) */
        crcIndex = actualCrc ^ (paramId & 0x0Fu);
        actualCrc = crcTable[crcIndex];

        if (0u != actualCrc)
        {
            /* CRC mismatch */
            result = CYRET_BAD_PARAM;
        }

        if ((CYRET_SUCCESS == result) &&
            (0u != pData->affectsCrc) && (pData->widgetId >= `$INSTANCE_NAME`_TOTAL_WIDGETS ))
        {
            /* Wrong widgetId for protected parameter */
            result = CYRET_BAD_PARAM;
        }

        /* Check offset value range */
        if (CYRET_SUCCESS == result)
        {
            if (0u == pData->flash)
            {
                /* Check offset for RAM Data Structure range */
                if (pData->offset >= sizeof(`$INSTANCE_NAME`_dsRam))
                {
                    result = CYRET_BAD_PARAM;
                }
            }
            else
            {
                /* Check offset for Flash Data Structure range */
                if (pData->offset >= sizeof(`$INSTANCE_NAME`_dsFlash))
                {
                    result = CYRET_BAD_PARAM;
                }

                /* Check if it is marked as Read Only */
                if (0u != pData->rw)
                {
                    result = CYRET_BAD_PARAM;
                }
            }
        }
    #else /* #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN) */
        /* Check offset value range */
        if (0u == pData->flash)
        {
            /* Check offset for RAM Data Structure range */
            if (pData->offset >= sizeof(`$INSTANCE_NAME`_dsRam))
            {
                result = CYRET_BAD_PARAM;
            }
        }
        else
        {
            /* Check offset for Flash Data Structure range */
            if (pData->offset >= sizeof(`$INSTANCE_NAME`_dsFlash))
            {
                result = CYRET_BAD_PARAM;
            }

            /* Check if it is marked as Read Only */
            if (0u != pData->rw)
            {
                result = CYRET_BAD_PARAM;
            }
        }
    #endif /* #if (0u != `$INSTANCE_NAME`_SELF_TEST_EN) */

    if (CYRET_SUCCESS == result)
    {
        /* Check parameter type, offset alignment */
        switch (pData->type)
        {
        case DS_PARAM_TYPE_UINT16:
            if (0u != (pData->offset & UINT16_ALIGN_MASK))
            {
                result = CYRET_BAD_PARAM;
            }
            break;

        case DS_PARAM_TYPE_UINT32:
            if (0u != (pData->offset & UINT32_ALIGN_MASK))
            {
                result = CYRET_BAD_PARAM;
            }
            break;

        case DS_PARAM_TYPE_UINT8:
            break;

        default:
            result = CYRET_BAD_PARAM;
            break;
        }
    }

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetParam
****************************************************************************//**
*
* \brief
*  Gets the specified parameter value from the \ref group_structures.
*
* \details
*  This function gets the value of the specified parameter by the paramId
*  argument. The paramId for each register is available in the
*  `$INSTANCE_NAME` RegisterMap header file as
*  `$INSTANCE_NAME`_<ParameterName>_PARAM_ID. The paramId is a special
*  enumerated value generated by the customizer. The format of paramId is as
*  follows:
*    1. [ byte 3 byte 2 byte 1 byte 0 ]
*    2. [ TTWFCCCC UIIIIIII MMMMMMMM LLLLLLLL ]
*    3. T - encodes the parameter type:
*      - 01b: uint8
*      - 10b: uint16
*      - 11b: uint32
*    4. W - indicates whether the parameter is writable:
*      - 0: ReadOnly
*      - 1: Read/Write
*    5. C - 4 bit CRC (X^3 + 1) of the whole paramId word, the C bits are
*       filled with 0s when the CRC is calculated.
*    6. U - indicates if the parameter affects the RAM Widget Object CRC.
*    7. I - specifies that the widgetId parameter belongs to
*    8. M,L - the parameter offset MSB and LSB accordingly in:
*      - Flash Data Structure if W bit is 0.
*      - RAM Data Structure if W bit is 1.
*
*  Refer to the \ref group_structures section for details of the data structure
*  organization and examples of its register access.
*
* \param paramId
*  Specifies the ID of parameter to get its value.
*  A macro for the parameter ID can be found in the `$INSTANCE_NAME` RegisterMap header
*  file defined as `$INSTANCE_NAME`_<ParameterName>_PARAM_ID.
*
* \param value
*  The pointer to a variable to be updated with the obtained value.
*
* \return
*  Returns the status of the operation:
*    - CYRET_SUCCESS - The operation is successfully completed.
*    - CYRET_BAD_PARAM - The input parameter is invalid.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_GetParam(uint32 paramId, uint32 *value)
{
    PARAM_ID_STRUCT pData;
    cystatus result;

    union
    {
        volatile void   const * ptr;
        volatile uint8  const * ptrUint8;
        volatile uint16 const * ptrUint16;
        volatile uint32 const * ptrUint32;
    } ptrData;

    result = DsParseParamId(paramId, &pData);

    /* Parse and validate paramId */
    if (CYRET_SUCCESS == result)
    {
        /* Get base address of parameter */
        if (0u == pData.flash)
        {
            ptrData.ptr = &`$INSTANCE_NAME`_dsRam;
        }
        else
        {
            ptrData.ptr = &`$INSTANCE_NAME`_dsFlash;
        }

        /* Add offset to base address */
        ptrData.ptrUint8 += pData.offset;

        /* Read data */
        if (DS_PARAM_TYPE_UINT8 == pData.type)
        {
            *value = (uint32) (*ptrData.ptrUint8);
        }
        else if (DS_PARAM_TYPE_UINT16 == pData.type)
        {
            *value = (uint32) (*ptrData.ptrUint16);
        }
        else if (DS_PARAM_TYPE_UINT32 == pData.type)
        {
            *value = *ptrData.ptrUint32;
        }
        else
        {
            /* Parameter comes here already validated. */
            CYASSERT(0u);
        }
    }

    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetParam
****************************************************************************//**
*
* \brief
*  Sets a new value for the specified parameter in the \ref group_structures.
*
* \details
*  This function sets the value of the specified parameter by the paramId
*  argument. The paramId for each register is available in the
*  `$INSTANCE_NAME` RegisterMap header file as
*  `$INSTANCE_NAME`_<ParameterName>_PARAM_ID. The paramId is a special
*  enumerated value generated by the customizer. The format of paramId is as
*  follows:
*    1. [ byte 3 byte 2 byte 1 byte 0 ]
*    2. [ TTWFCCCC UIIIIIII MMMMMMMM LLLLLLLL ]
*    3. T - encodes the parameter type:
*      - 01b: uint8
*      - 10b: uint16
*      - 11b: uint32
*    4. W - indicates whether the parameter is writable:
*      - 0: ReadOnly
*      - 1: Read/Write
*    5. C - 4 bit CRC (X^3 + 1) of the whole paramId word, the C bits are
*       filled with 0s when the CRC is calculated.
*    6. U - indicates if the parameter affects the RAM Widget Object CRC.
*    7. I - specifies that the widgetId parameter belongs to
*    8. M,L - the parameter offset MSB and LSB accordingly in:
*      - Flash Data Structure if W bit is 0.
*      - RAM Data Structure if W bit is 1.
*
*  Refer to the \ref group_structures section for details of the data structure
*  organization and examples of its register access.
*
*  This function writes specified value into the desired register without
*  other registers update. It is application layer responsibility to keep all
*  the data structure registers aligned. Repeated call of
*  `$INSTANCE_NAME`_Start() function helps aligning dependent register values.
*
* \param paramId
*  Specifies the ID of parameter to set its value.
*  A macro for the parameter ID can be found in the `$INSTANCE_NAME` RegisterMap header
*  file defined as `$INSTANCE_NAME`_<ParameterName>_PARAM_ID.

* \param value
*  Specifies the new parameter's value.
*
* \return
*  Returns the status of the operation:
*    - CYRET_SUCCESS - The operation is successfully completed.
*    - CYRET_BAD_PARAM - The input parameter is invalid.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetParam(uint32 paramId, uint32 value)
{
    cystatus result;
    PARAM_ID_STRUCT pData;

    union
    {
        volatile void   * ptr;
        volatile uint8  * ptrUint8;
        volatile uint16 * ptrUint16;
        volatile uint32 * ptrUint32;
    } ptrData;

    result = DsParseParamId(paramId, &pData);

    /* verify if parameter is writable */
    if (CYRET_SUCCESS == result)
    {
        if (0u == pData.rw)
        {
            result = CYRET_BAD_PARAM;
        }
    }

    /* Parse and validate paramId */
    if (CYRET_SUCCESS == result)
    {
        /* Get base address of parameter */
        ptrData.ptr = &`$INSTANCE_NAME`_dsRam;

        /* Add offset to base address */
        ptrData.ptrUint8 += pData.offset;

        /* Write data */
        if (DS_PARAM_TYPE_UINT8 == pData.type)
        {
            *ptrData.ptrUint8 = LO8(value);
        }
        else if (DS_PARAM_TYPE_UINT16 == pData.type)
        {
            *ptrData.ptrUint16 = LO16(value);
        }
        else if (DS_PARAM_TYPE_UINT32 == pData.type)
        {
            *ptrData.ptrUint32 = value;
        }
        else
        {
            /* Parameter comes here already validated. */
            CYASSERT(0u);
        }

        #if (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_TST_WDGT_CRC_EN || `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN))
            /* Update widget or global CRC if self-test is enabled and parameter affects it */
            if (0u != pData.affectsCrc)
            {
                if ((ptrData.ptrUint16 >= &`$INSTANCE_NAME`_dsRam.csd0Config) &&
                    (ptrData.ptrUint16 <  &`$INSTANCE_NAME`_dsRam.glbCrc))
                {

                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)
                        `$INSTANCE_NAME`_DsUpdateGlobalCrc();
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN) */

                }
                else
                {
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN)
                        `$INSTANCE_NAME`_DsUpdateWidgetCrc((uint32)pData.widgetId);
                    #endif /* (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_TST_WDGT_CRC_EN) */
                }
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE == (`$INSTANCE_NAME`_TST_WDGT_CRC_EN || `$INSTANCE_NAME`_TST_GLOBAL_CRC_EN)) */
    }

    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsAnyWidgetActive
****************************************************************************//**
*
* \brief
*  Reports if any widget has detected a touch.
*
* \details
*  This function reports if any widget has detected a touch or not by extracting
*  information from the wdgtStatus registers
*  (`$INSTANCE_NAME`_WDGT_STATUS<X>_VALUE). This function does not process a
*  widget but extracts processed results from the \ref group_structures.
*
* \return
*   Returns the touch detection status of all the widgets:
*     - Zero - No touch is detected in all the widgets or sensors.
*     - Non-zero - At least one widget or sensor detected a touch.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsAnyWidgetActive(void)
{
    uint32 result = 0Lu;
    uint32 wdWord;

    for (wdWord = `$INSTANCE_NAME`_WDGT_STATUS_WORDS; wdWord-- > 0u;)
    {
        result |= `$INSTANCE_NAME`_dsRam.wdgtStatus[wdWord];
    }

    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsWidgetActive
****************************************************************************//**
*
* \brief
*  Reports if the specified widget detects a touch on any of its sensors.
*
* \details
*  This function reports if the specified widget has detected a touch or not by
*  extracting information from the wdgtStatus registers
*  (`$INSTANCE_NAME`_WDGT_STATUS<X>_VALUE). This function does not process the
*  widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of the widget to get its status.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \return
*  Returns the touch detection status of the specified widgets:
*    - Zero - No touch is detected in the specified widget or a wrong widgetId
*      is specified.
*    - Non-zero if at least one sensor of the specified widget is active, i.e.
*      a touch is detected.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsWidgetActive(uint32 widgetId)
{
    uint32 result = 0Lu;

    if (widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        result = `$INSTANCE_NAME`_GET_WIDGET_ACTIVE_STATUS(widgetId);
    }
    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsSensorActive
****************************************************************************//**
*
* \brief
*  Reports if the specified sensor in the widget detects a touch.
*
* \details
*  This function reports if the specified sensor in the widget has detected a
*  touch or not by extracting information from the wdgtStatus registers
*  (`$INSTANCE_NAME`_WDGT_STATUS<X>_VALUE). This function does not process the
*  widget or sensor but extracts processed results from the \ref group_structures.
*
*  For proximity sensors, this function returns the proximity detection status. To
*  get the finger touch status of proximity sensors, use the
*  `$INSTANCE_NAME`_IsProximitySensorActive() function.
*
* \param widgetId
*  Specifies the ID number of the widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.

* \param sensorId
*  Specifies the ID number of the sensor within the widget to get its touch
*  detection status.
*  A macro for the sensor ID within the specified widget can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID.
*
* \return
*  Returns the touch detection status of the specified sensor / widget:
*    - Zero if no touch is detected in the specified sensor / widget or a wrong
*      widget ID / sensor ID is specified.
*    - Non-zero if the specified sensor is active i.e. touch is detected. If the
*      specific sensor belongs to a proximity widget, the proximity detection
*      status is returned.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsSensorActive(uint32 widgetId, uint32 sensorId)
{
    uint32 result = 0Lu;

    if ((widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS) &&
        (sensorId < `$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)))
    {
        #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN)
            if (`$INSTANCE_NAME`_WD_PROXIMITY_E ==
                (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].wdgtType)
            {
                sensorId = `$INSTANCE_NAME`_PROX_STS_OFFSET(sensorId);
            }
        #endif /* (`$INSTANCE_NAME`_ENABLE != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN) */
        result = `$INSTANCE_NAME`_dsRam.snsStatus[widgetId] & (1Lu << sensorId);
    }

    return result;
}

#if (0u != `$INSTANCE_NAME`_MATRIX_WIDGET_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsMatrixButtonsActive
****************************************************************************//**
*
* \brief
*  Reports the status of the specified matrix button widget.
*
* \details
*  This function reports if the specified matrix widget has detected a touch or
*  not by extracting information from the wdgtStatus registers
*  (`$INSTANCE_NAME`_WDGT_STATUS<X>_VALUE for the CSD widgets and
*  `$INSTANCE_NAME`_SNS_STATUS<WidgetId>_VALUE for CSX widget). In addition, the
*  function provides details of the active sensor including active rows/columns
*  for the CSD widgets. This function is used only with the matrix button
*  widgets. This function does not process the widget but extracts
*  processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of the matrix button widget to check the status of its
*  sensors.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header file
*  defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID
*
* \return
*  Returns the touch detection status of the sensors in the specified matrix
*  buttons widget. Zero indicates that no touch is detected in the specified
*  widget or a wrong widgetId is specified.
*    1. For the matrix buttons widgets with the CSD sensing mode:
*      - Bit [31] if set, indicates that one or more sensors in the widget
*        detected a touch.
*      - Bits [30..24] are reserved
*      - Bits [23..16] indicate the logical sensor number of the sensor that
*        detected a touch. If more than one sensor detected a touch for the CSD
*        widget, no status is reported because more than one touch is invalid for the
*        CSD matrix buttons widgets.
*      - Bits [15..8] indicate the active row number.
*      - Bits [7..0] indicate the active column number.
*    2. For the matrix buttons widgets with the CSX widgets, each bit (31..0)
*      corresponds to the TX/RX intersection.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsMatrixButtonsActive(uint32 widgetId)
{
    uint32 result = 0Lu;
    cystatus state = CYRET_SUCCESS;
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt = 0u;

    #if (0u != `$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN)
        `$INSTANCE_NAME`_RAM_WD_CSD_MATRIX_STRUCT *wdCsdMatrix;
    #endif

    if (widgetId >= `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        state = CYRET_BAD_PARAM;
    }
    else
    {
        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType != `$INSTANCE_NAME`_WD_MATRIX_BUTTON_E)
        {
            state = CYRET_BAD_PARAM;
        }
        else if (0u == `$INSTANCE_NAME`_GET_WIDGET_ACTIVE_STATUS(widgetId))
        {
            state = CYRET_BAD_PARAM;
        }
        else
        {
            /* input parameters are OK */
        }
    }

    if (CYRET_SUCCESS == state)
    {
        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != `$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                wdCsdMatrix = ptrFlashWdgt->ptr2WdgtRam;

                result = `$INSTANCE_NAME`_MATRIX_BUTTONS_TOUCHED |
                         ((uint32)wdCsdMatrix->posSnsId << 16u)  |
                         ((uint32)wdCsdMatrix->posRow   << 8u)   |
                         (uint32)wdCsdMatrix->posCol;
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_CSD_MATRIX_WIDGET_EN) */

        #if (0u != `$INSTANCE_NAME`_CSX_MATRIX_WIDGET_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                result = `$INSTANCE_NAME`_dsRam.snsStatus[widgetId];
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_CSX_MATRIX_WIDGET_EN) */

        default:
            CYASSERT(0u);
            break;
        }
    }

    return result;
}
#endif /* #if (0u != `$INSTANCE_NAME`_MATRIX_WIDGET_EN) */

#if (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsProximitySensorActive
****************************************************************************//**
*
* \brief
*  Reports the finger detection status of the specified proximity widget/sensor.
*
* \details
*  This function reports if the specified proximity sensor has detected a touch
*  or not by extracting information from the wdgtStatus registers
*  (`$INSTANCE_NAME`_SNS_STATUS<WidgetId>_VALUE). This function is used
*  only with proximity sensor widgets. This function does not process the
*  widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of the proximity widget.
*  A macro for the widget ID can be found in the `$INSTANCE_NAME` Configuration header
*  file defined as `$INSTANCE_NAME`_<WidgetName>_WDGT_ID
*
* \param proxId
*  Specifies the ID number of the proximity sensor within the proximity widget to
*  get its touch detection status.
*  A macro for the proximity ID within a specified widget can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_SNS<SensorNumber>_ID
*
* \return
*  Returns the status of the specified sensor of the proximity widget. Zero
*  indicates that no touch is detected in the specified sensor / widget or a
*  wrong widgetId / proxId is specified.
*    - Bits [31..2] are reserved.
*    - Bit [1] indicates that a touch is detected.
*    - Bit [0] indicates that a proximity is detected.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_IsProximitySensorActive(uint32 widgetId, uint32 proxId)
{
    uint32 result = 0Lu;

    if ((widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS) && (proxId < `$INSTANCE_NAME`_GET_SENSOR_COUNT(widgetId)) &&
        (`$INSTANCE_NAME`_WD_PROXIMITY_E ==
            (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].wdgtType))
    {
        result = `$INSTANCE_NAME`_dsRam.snsStatus[widgetId];
        result >>= `$INSTANCE_NAME`_PROX_STS_OFFSET(proxId);
        result &=  `$INSTANCE_NAME`_PROX_STS_MASK;
    }

    return result;
}
#endif /* #if (0u != `$INSTANCE_NAME`_PROXIMITY_WIDGET_EN) */


#if (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetCentroidPos
****************************************************************************//**
*
* \brief
*  Reports the centroid position for the specified slider widget.
*
* \details
*  This function reports the centroid value of a specified radial or linear
*  slider widget by extracting information from the wdgtStatus registers
*  (`$INSTANCE_NAME`_<WidgetName>_POSITION<X>_VALUE). This function is
*  used only with radial or linear slider widgets. This function does not
*  process the widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of a slider widget to get the centroid of the
*  detected touch.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID
*
* \return
*  Returns the centroid position of a specified slider widget:
*    - The centroid position if a touch is detected.
*    - `$INSTANCE_NAME`_SLIDER_NO_TOUCH - No touch is detected or a wrong
*      widgetId is specified.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetCentroidPos(uint32 widgetId)
{
    uint32 result = `$INSTANCE_NAME`_SLIDER_NO_TOUCH;
    `$INSTANCE_NAME`_RAM_WD_SLIDER_STRUCT *wdSlider;

    if ((widgetId < `$INSTANCE_NAME`_TOTAL_WIDGETS) &&
        ((`$INSTANCE_NAME`_WD_LINEAR_SLIDER_E ==
            (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].wdgtType) ||
         (`$INSTANCE_NAME`_WD_RADIAL_SLIDER_E ==
            (`$INSTANCE_NAME`_WD_TYPE_ENUM)`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].wdgtType)))
    {
        wdSlider = `$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId].ptr2WdgtRam;
        result = (uint32)wdSlider->position[0u];
    }

    return result;
}
#endif /* #if (0u != `$INSTANCE_NAME`_SLIDER_WIDGET_EN) */


#if (0u != `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetXYCoordinates
****************************************************************************//**
*
* \brief
*  Reports the X/Y position detected for the specified touchpad widget.
*
* \details
*  This function reports a touch position (X and Y coordinates) value of a
*  specified touchpad widget by extracting information from the wdgtStatus
*  registers (`$INSTANCE_NAME`_<WidgetName>_POS_Y_VALUE). This function should
*  be used only with the touchpad widgets. This function does not process the
*  widget but extracts processed results from the \ref group_structures.
*
* \param widgetId
*  Specifies the ID number of a touchpad widget to get the X/Y position of a
*  detected touch.
*  A macro for the widget ID can be found in the
*  `$INSTANCE_NAME` Configuration header file defined as
*  `$INSTANCE_NAME`_<WidgetName>_WDGT_ID.
*
* \return
*  Returns the touch position of a specified touchpad widget:
*    1. If a touch is detected:
*      - Bits [31..16] indicate the Y coordinate.
*      - Bits [15..0] indicate the X coordinate.
*    2. If no touch is detected or a wrong widgetId is specified:
*      - `$INSTANCE_NAME`_TOUCHPAD_NO_TOUCH.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetXYCoordinates(uint32 widgetId)
{
    `$INSTANCE_NAME`_FLASH_WD_STRUCT const *ptrFlashWdgt = NULL;

    #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
        `$INSTANCE_NAME`_RAM_WD_CSD_TOUCHPAD_STRUCT *wdCsdTouchpad;
    #endif /* #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

    #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
        `$INSTANCE_NAME`_RAM_WD_CSX_TOUCHPAD_STRUCT *wdCsxTouchpad;
    #endif /* #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN) */

    cystatus state = CYRET_SUCCESS;
    uint32 result = `$INSTANCE_NAME`_TOUCHPAD_NO_TOUCH;

    if (widgetId >= `$INSTANCE_NAME`_TOTAL_WIDGETS)
    {
        state = CYRET_BAD_PARAM;
    }
    else
    {
        ptrFlashWdgt = &`$INSTANCE_NAME`_dsFlash.wdgtArray[widgetId];

        if ((`$INSTANCE_NAME`_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType != `$INSTANCE_NAME`_WD_TOUCHPAD_E)
        {
            state = CYRET_BAD_PARAM;
        }
    }

    if (CYRET_SUCCESS == state)
    {
        switch(`$INSTANCE_NAME`_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSD_E:
                wdCsdTouchpad = ptrFlashWdgt->ptr2WdgtRam;
                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN)
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN)
                        if (0 != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_CENTROID_5X5_MASK))
                        {
                    #endif
                        result = ((uint32)wdCsdTouchpad->position.pos[0u].x) |
                                 ((uint32)wdCsdTouchpad->position.pos[0u].y << 16u);
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN)
                        }
                    #endif
                #endif

                #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_3X3_CSD_EN)
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN)
                        if (0 != (ptrFlashWdgt->staticConfig & `$INSTANCE_NAME`_CENTROID_3X3_MASK))
                        {
                    #endif
                        result = ((uint32)wdCsdTouchpad->posX) |
                                 ((uint32)wdCsdTouchpad->posY << 16u);
                    #if (`$INSTANCE_NAME`_ENABLE == `$INSTANCE_NAME`_CENTROID_5X5_CSD_EN)
                        }
                    #endif
                #endif

                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_CSD_TOUCHPAD_WIDGET_EN) */

        #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN)
            case `$INSTANCE_NAME`_SENSE_METHOD_CSX_E:
                wdCsxTouchpad = ptrFlashWdgt->ptr2WdgtRam;

                result = ((uint32)wdCsxTouchpad->touch[0u].x) |
                         ((uint32)wdCsxTouchpad->touch[0u].y << 16u);
                break;
        #endif /* #if (0u != `$INSTANCE_NAME`_CSX_TOUCHPAD_WIDGET_EN) */

        default:
            CYASSERT(0u);
            break;
        }
    }

    return result;
}
#endif /* #if (0u != `$INSTANCE_NAME`_TOUCHPAD_WIDGET_EN) */


/* [] END OF FILE */
