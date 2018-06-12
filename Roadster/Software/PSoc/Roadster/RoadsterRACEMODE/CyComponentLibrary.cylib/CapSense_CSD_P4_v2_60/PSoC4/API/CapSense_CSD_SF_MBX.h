/*******************************************************************************
* File Name: `$INSTANCE_NAME`_MBX.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and structure declarations for the tuner
*  communication for the CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_MBX_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_MBX_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PVT.h"
#include "`$INSTANCE_NAME`_CSHL.h"


/***************************************
*   Condition compilation parameters
***************************************/

/* Check Sum to identify data */
#define `$INSTANCE_NAME`_CHECK_SUM      (`$CheckSum`u)

#define `$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT     (((`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define `$INSTANCE_NAME`_PACKED_STRUCT __attribute__ ((packed))
#elif defined(__ICCARM__)
    #define `$INSTANCE_NAME`_PACKED_STRUCT __packed
#else
    #define `$INSTANCE_NAME`_PACKED_STRUCT
#endif /* (defined(__GNUC__) || defined(__ARMCC_VERSION)) */

#if defined(__GNUC__)
    #define `$INSTANCE_NAME`_NO_STRICT_VOLATILE __attribute__((optimize("-fno-strict-volatile-bitfields")))
#else
    #define `$INSTANCE_NAME`_NO_STRICT_VOLATILE
#endif /* (defined(__GNUC__)) */

#define `$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT           (`$INSTANCE_NAME`_TOTAL_WIDGET_COUNT + \
                                                                 `$INSTANCE_NAME`_TOTAL_TOUCH_PADS_COUNT + \
                                                                 `$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)

#define `$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT     (`$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT + \
                                                                 `$INSTANCE_NAME`_TOTAL_GENERICS_COUNT)


/***************************************
*      Type defines for mailboxes
***************************************/

/* Outbox structure definition */
typedef struct _`$INSTANCE_NAME`_outbox
{
    #if (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT)
        uint16   position[`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT];
    #endif  /* (`$INSTANCE_NAME`_TOTAL_CENTROIDS_COUNT) */

    #if (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT)
        uint8   mb_position[`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT * 2u];
    #endif /* (`$INSTANCE_NAME`_TOTAL_MATRIX_BUTTONS_COUNT) */

    uint16   rawData[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
    uint16   baseLine[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

    `$SizeReplacementString` signal[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];

    uint8    onMask[`$INSTANCE_NAME`_TOTAL_SENSOR_MASK_COUNT];

    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
        `$SizeReplacementString`   fingerThreshold[`$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT];
        `$SizeReplacementString`   noiseThreshold[`$INSTANCE_NAME`_WIDGET_CSHL_PARAMETERS_COUNT];

        uint8   scanResolution[`$INSTANCE_NAME`_WIDGET_RESOLUTION_PARAMETERS_COUNT];
        uint8   idac1Value[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
        uint8   idac2Value[`$INSTANCE_NAME`_TOTAL_SENSOR_COUNT];
        uint8   analogSwitchDivider[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
        uint8   modulatorDivider[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

    #if(`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
        uint8   noReadMsg;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */
    uint16  checkSum;
} `$INSTANCE_NAME`_PACKED_STRUCT `$INSTANCE_NAME`_OUTBOX;

/* Inbox structure definition */
#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
    typedef struct _`$INSTANCE_NAME`_inbox
    {
        uint8   sensorIndex;
        uint8   idac1Settings;
        #if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
            uint8   idac2Settings;
        #endif /* ( (`$INSTANCE_NAME`_IDAC_CNT == 2u) */

        uint8   resolution;
        `$SizeReplacementString`   fingerThreshold;
        `$SizeReplacementString`   noiseThreshold;
        `$SizeReplacementString`   hysteresis;

        uint8   debounce;
        uint8   analogSwitchDivider;
        uint8   modulatorDivider;
    } `$INSTANCE_NAME`_PACKED_STRUCT `$INSTANCE_NAME`_INBOX;

#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */
/* Mailbox structure definition */
typedef struct _`$INSTANCE_NAME`_mailBox
{
    uint8   type;               /* Must be the first byte with values ranging from 0-119 */
    uint16  size;               /* Must be the size of this data structure. Range between 0-127 */
    `$INSTANCE_NAME`_OUTBOX  outbox;
    #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
        `$INSTANCE_NAME`_INBOX inbox;
    #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */

} `$INSTANCE_NAME`_PACKED_STRUCT `$INSTANCE_NAME`_MAILBOX;


/* Mailboxes structure definition */
typedef struct _`$INSTANCE_NAME`_mailboxes
{
    uint8   numMailBoxes;       /* This must always be the first. Represents # of mailboxes */
    `$INSTANCE_NAME`_MAILBOX    csdMailbox;

} `$INSTANCE_NAME`_PACKED_STRUCT `$INSTANCE_NAME`_MAILBOXES;

/***************************************
*        Function Prototypes
***************************************/

`$INSTANCE_NAME`_NO_STRICT_VOLATILE void `$INSTANCE_NAME`_InitMailbox(volatile `$INSTANCE_NAME`_MAILBOX *mbx);
`$INSTANCE_NAME`_NO_STRICT_VOLATILE void `$INSTANCE_NAME`_PostMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx);

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
    `$INSTANCE_NAME`_NO_STRICT_VOLATILE void `$INSTANCE_NAME`_ReadMessage(volatile `$INSTANCE_NAME`_MAILBOX *mbx);
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL) */


/***************************************
*           API Constants
***************************************/

/* The selected ID for this version of Tuner */
#define `$INSTANCE_NAME`_TYPE_ID        (0x04u)

#define `$INSTANCE_NAME`_BUSY_FLAG      (`$INSTANCE_NAME`_TYPE_ID | 0x80u)
#define `$INSTANCE_NAME`_HAVE_MSG       (sizeof(`$INSTANCE_NAME`_MAILBOX) | 0x8000u)

extern uint8 `$INSTANCE_NAME`_modulationIDAC[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];

#if (`$INSTANCE_NAME`_IDAC_CNT == 2u)
    extern uint8 `$INSTANCE_NAME`_compensationIDAC[`$INSTANCE_NAME`_TOTAL_IMMUNITY_COUNT];
#endif /* (`$INSTANCE_NAME`_IDAC_CNT == 2u) */

extern uint8 `$INSTANCE_NAME`_widgetResolution[`$INSTANCE_NAME`_RESOLUTIONS_TBL_SIZE];

#if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_MANUAL)
    extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];
    extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_noiseThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];
    extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_hysteresis[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];
    extern uint8 `$INSTANCE_NAME`_debounce[`$INSTANCE_NAME`_WIDGET_PARAM_TBL_SIZE];

#elif (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
    extern `$SizeReplacementString` `$INSTANCE_NAME`_fingerThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];
    extern `$INSTANCE_NAME`_THRESHOLD_SIZE_TYPE `$INSTANCE_NAME`_noiseThreshold[`$INSTANCE_NAME`_THRESHOLD_TBL_SIZE];
    extern uint8 `$INSTANCE_NAME`_GetPrescaler(void);
#else
    /* No tuning */
#endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */

#if ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET ) || \
      (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) )
            extern uint8 `$INSTANCE_NAME`_senseClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
            #if (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO)
                extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal;
            #else
                extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal[`$INSTANCE_NAME`_TOTAL_SCANSLOT_COUNT];
            #endif  /* (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) */
#else
            extern uint8 `$INSTANCE_NAME`_senseClkDividerVal;
            extern uint8 `$INSTANCE_NAME`_sampleClkDividerVal;
#endif /* ( (`$INSTANCE_NAME`_MULTIPLE_FREQUENCY_SET) || \
       *    (`$INSTANCE_NAME`_TUNING_METHOD == `$INSTANCE_NAME`__TUNING_AUTO) )
       */


#endif  /* (CY_CAPSENSE_CSD_MBX_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
