/*******************************************************************************
* File Name: `$INSTANCE_NAME`_TunerHelper.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and structure declarations for the tuner helper
*  APIs for the CapSense CSD component.
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_`$INSTANCE_NAME`_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"

#if(0u != `$INSTANCE_NAME`_CSHL_API_GENERATE)
    #include "`$INSTANCE_NAME`_CSHL.h"
#endif /* (0u != `$INSTANCE_NAME`_CSHL_API_GENERATE) */

#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    #include "`$INSTANCE_NAME`_MBX.h"
#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define `$INSTANCE_NAME`_DEFAULT_MAILBOXES_NUMBER       (1u)

#define `$INSTANCE_NAME`_CENTROID_POSITION_BUFFER_SIZE  (2u)
#define `$INSTANCE_NAME`_MB_POSITION_BUFFER_SIZE        (2u)

#define `$INSTANCE_NAME`_DEFAULT_TRACKPAD_INDEX         (0u)

#define `$INSTANCE_NAME`_FIRST_FINGER_INDEX             (0u)
#define `$INSTANCE_NAME`_SECOND_FINGER_INDEX            (1u)

#define `$INSTANCE_NAME`_FIRST_FINGER_X_INDEX           (0u)
#define `$INSTANCE_NAME`_FIRST_FINGER_Y_INDEX           (1u)

#define `$INSTANCE_NAME`_SECOND_FINGER_X_INDEX          (2u)
#define `$INSTANCE_NAME`_SECOND_FINGER_Y_INDEX          (3u)

#define `$INSTANCE_NAME`_GESTURE_TYPE_MASK              (0xF0u)
#define `$INSTANCE_NAME`_INERTIAL_SCROLL                (0xB0u)
#define `$INSTANCE_NAME`_NON_INERTIAL_SCROLL            (0xC0u)


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_TunerStart(void);
void `$INSTANCE_NAME`_TunerComm(void);

#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
   `$INSTANCE_NAME`_NO_STRICT_VOLATILE void `$INSTANCE_NAME`_ProcessAllWidgets(volatile `$INSTANCE_NAME`_OUTBOX *outbox);
#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */


/***************************************
*     Vars with External Linkage
***************************************/
#if (`$INSTANCE_NAME`_TUNER_API_GENERATE)
    extern volatile `$INSTANCE_NAME`_MAILBOXES `$INSTANCE_NAME`_mailboxesComm;
#endif /* (`$INSTANCE_NAME`_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_`$INSTANCE_NAME`_H)*/


/* [] END OF FILE */
