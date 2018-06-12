/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the DVDAC component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DVDAC_`$INSTANCE_NAME`_H)
#define CY_DVDAC_`$INSTANCE_NAME`_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Data Struct Definition
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;

/* Component init state */
extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*        API constants
***************************************/
#define `$INSTANCE_NAME`_RESOLUTION                 (`$Resolution`u)
#define `$INSTANCE_NAME`_INTERNAL_CLOCK_USED        (`$InternalClock`u)

#define `$INSTANCE_NAME`_INTEGER_PORTION_SHIFT      (`$INSTANCE_NAME`_RESOLUTION - 8u)
#define `$INSTANCE_NAME`_DITHERED_ARRAY_SIZE        ((uint8)(1u << `$INSTANCE_NAME`_INTEGER_PORTION_SHIFT))
#define `$INSTANCE_NAME`_FRACTIONAL_PORTION_MASK    (`$INSTANCE_NAME`_DITHERED_ARRAY_SIZE - 1u)
#define `$INSTANCE_NAME`_INTEGER_PORTION_MAX_VALUE  (0xFFu)

/* DMA Configuration */
#define `$INSTANCE_NAME`_DMA_BYTES_PER_BURST        (1u)
#define `$INSTANCE_NAME`_DMA_REQUEST_PER_BURST      (1u)
#define `$INSTANCE_NAME`_DMA_SRC_BASE               (CYDEV_SRAM_BASE)
#define `$INSTANCE_NAME`_DMA_DST_BASE               (CYDEV_PERIPH_BASE)


#if   (`$INSTANCE_NAME`_RESOLUTION ==  9u)
    #define `$INSTANCE_NAME`_DVDAC_MAX_VALUE        (0x1FEu)
#elif (`$INSTANCE_NAME`_RESOLUTION == 10u)
    #define `$INSTANCE_NAME`_DVDAC_MAX_VALUE        (0x3FCu)
#elif (`$INSTANCE_NAME`_RESOLUTION == 11u)
    #define `$INSTANCE_NAME`_DVDAC_MAX_VALUE        (0x7F8u)
#else   /* Resolution 12 bits */
    #define `$INSTANCE_NAME`_DVDAC_MAX_VALUE        (0xFF0u)
#endif  /* (`$INSTANCE_NAME`_RESOLUTION ==  9u) */


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Init(void)                `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)              `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Start(void)               `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void)                `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_SetValue(uint16 value)    `=ReentrantKeil($INSTANCE_NAME . "_SetValue")`;
void `$INSTANCE_NAME`_Sleep(void)               `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)              `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void `$INSTANCE_NAME`_SaveConfig(void)          `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void)       `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

#endif /* CY_DVDAC_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
