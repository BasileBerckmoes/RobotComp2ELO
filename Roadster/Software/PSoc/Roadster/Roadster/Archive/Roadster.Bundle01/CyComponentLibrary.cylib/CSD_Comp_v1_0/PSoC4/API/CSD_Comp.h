/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the CSD Comparator component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CSD_Comp_`$INSTANCE_NAME`_H)
#define CY_CSD_Comp_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
    
#include "`$INSTANCE_NAME`_SampleClk.h"

   
/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetSpeed(uint32 speed);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
uint32 `$INSTANCE_NAME`_GetCompare(void);


/***************************************
*           API Constants
***************************************/

/* Constants for SetSpeed() function */
#define `$INSTANCE_NAME`_SLOW_SPEED  (0x00u)
#define `$INSTANCE_NAME`_FAST_SPEED  (0x01u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_SPEED  (`$Speed`u)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8  `$INSTANCE_NAME`_initVar;


/***************************************
*             Registers
***************************************/
#define `$INSTANCE_NAME`_CONFIG_REG (* (reg32 *) `$INSTANCE_NAME`_CSD_Comp__CSD_CONFIG)
#define `$INSTANCE_NAME`_CONFIG_PTR (  (reg32 *) `$INSTANCE_NAME`_CSD_Comp__CSD_CONFIG)

#define `$INSTANCE_NAME`_STATUS_REG (* (reg32 *) `$INSTANCE_NAME`_CSD_Comp__CSD_STATUS)
#define `$INSTANCE_NAME`_STATUS_PTR (  (reg32 *) `$INSTANCE_NAME`_CSD_Comp__CSD_STATUS)


/***************************************
*       Register Constants
***************************************/

/* `$INSTANCE_NAME`_CONFIG_REG */
#define `$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_POS   (11u)  /* [11]      Selects bandwidth for sensing comparator */
#define `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_POS   (19u)  /* [19]      Turns on the sense comparator circuit */
#define `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_POS     (22u)  /* [22]      Selects how to connect the sensing comparator to the Cmod capacitor */
#define `$INSTANCE_NAME`_CONFIG_DDFTSEL_POS         (26u)  /* [28:26]   The dsi_sample_out signal setting*/
#define `$INSTANCE_NAME`_CONFIG_DDFTCOMP_POS        (30u)  /* [30]      The comp_out signal setting */
#define `$INSTANCE_NAME`_CONFIG_ENABLE_POS          (31u)  /* [31]      Master enable of the CSD IP */

#define `$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW       ((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW_POS)

#define `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN       ((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_SENSE_COMP_EN_POS)

#define `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_SENSE_AMUXA    ((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_POS)

#define `$INSTANCE_NAME`_CONFIG_DDFTSEL_COMP_OUT    ((uint32) 0x04u << `$INSTANCE_NAME`_CONFIG_DDFTSEL_POS)
#define `$INSTANCE_NAME`_CONFIG_DDFTSEL_MASK        ((uint32) 0x07u << `$INSTANCE_NAME`_CONFIG_DDFTSEL_POS)

#define `$INSTANCE_NAME`_CONFIG_DDFTCOMP_SENSECOMP  ((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_DDFTCOMP_POS)

#define `$INSTANCE_NAME`_CONFIG_ENABLE              ((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_ENABLE_POS)

/* `$INSTANCE_NAME`_STATUS_REG */
#define `$INSTANCE_NAME`_STATUS_SAMPLE_POS      (3u)   /* [3]   Output of main sensing comparator */
#define `$INSTANCE_NAME`_STATUS_SAMPLE          ((uint32) 0x01u << `$INSTANCE_NAME`_STATUS_SAMPLE_POS)

/***************************************
*       Init Macros Definitions
***************************************/
#define `$INSTANCE_NAME`_GET_SENSE_COMP_BW(speed)   ((0u != (speed)) ? (`$INSTANCE_NAME`_CONFIG_SENSE_COMP_BW) : (0u))

/* Calculating divider for SampleClock to having it Freq equal SYSCLK */
#define `$INSTANCE_NAME`_SAMPLECLK_DIVIDER (CYDEV_BCLK__HFCLK__MHZ/CYDEV_BCLK__SYSCLK__MHZ)


/***************************************
*    Initialization Register Settings
***************************************/

#define `$INSTANCE_NAME`_DEFAULT_CONFIG ( `$INSTANCE_NAME`_GET_SENSE_COMP_BW(`$INSTANCE_NAME`_SPEED)    | \
                                          `$INSTANCE_NAME`_CONFIG_SENSE_INSEL_SENSE_AMUXA               | \
                                          `$INSTANCE_NAME`_CONFIG_DDFTSEL_COMP_OUT                      | \
                                          `$INSTANCE_NAME`_CONFIG_DDFTCOMP_SENSECOMP                    | \
                                          `$INSTANCE_NAME`_CONFIG_ENABLE )

#endif  /* CY_CSD_Comp_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
