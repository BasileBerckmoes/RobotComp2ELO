/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*    This file contains the constants and function prototypes for the AMuxSeq.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUXSEQ_`$INSTANCE_NAME`_H)
#define CY_AMUXSEQ_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_MUX_SINGLE 1
#define `$INSTANCE_NAME`_MUX_DIFF   2
#define `$INSTANCE_NAME`_MUXTYPE    `$MuxType`


/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Stop(void);
#if (`$INSTANCE_NAME`_MUXTYPE == `$INSTANCE_NAME`_MUX_DIFF)
void `$INSTANCE_NAME`_Next(void);
void `$INSTANCE_NAME`_DisconnectAll(void);
#else
/* The Next and DisconnectAll functions are declared in cyfitter_cfg.h. */
/* void `$INSTANCE_NAME`_Next(void); */
/* void `$INSTANCE_NAME`_DisconnectAll(void); */
#endif
int8 `$INSTANCE_NAME`_GetChannel(void);


/***************************************
*           Global Variables
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*         Parameter Constants
***************************************/
#define `$INSTANCE_NAME`_CHANNELS `$Channels`


#endif /* CY_AMUXSEQ_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
