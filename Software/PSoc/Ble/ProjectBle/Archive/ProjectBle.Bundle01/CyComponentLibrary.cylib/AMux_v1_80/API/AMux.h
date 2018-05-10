/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_`$INSTANCE_NAME`_H)
#define CY_AMUX_`$INSTANCE_NAME`_H

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
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
#define `$INSTANCE_NAME`_Init() `$INSTANCE_NAME`_Start()
void `$INSTANCE_NAME`_FastSelect(uint8 channel) `=ReentrantKeil($INSTANCE_NAME ."_FastSelect")`;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void `$INSTANCE_NAME`_Stop(void); */
/* void `$INSTANCE_NAME`_Select(uint8 channel); */
/* void `$INSTANCE_NAME`_Connect(uint8 channel); */
/* void `$INSTANCE_NAME`_Disconnect(uint8 channel); */
/* void `$INSTANCE_NAME`_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_CHANNELS  `$Channels`u
#define `$INSTANCE_NAME`_MUXTYPE   `$MuxType`
#define `$INSTANCE_NAME`_ATMOSTONE `$AtMostOneActive`

/***************************************
*             API Constants
***************************************/

#define `$INSTANCE_NAME`_NULL_CHANNEL 0xFFu
#define `$INSTANCE_NAME`_MUX_SINGLE   1
#define `$INSTANCE_NAME`_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if `$INSTANCE_NAME`_MUXTYPE == `$INSTANCE_NAME`_MUX_SINGLE
# if !`$INSTANCE_NAME`_ATMOSTONE
#  define `$INSTANCE_NAME`_Connect(channel) `$INSTANCE_NAME`_Set(channel)
# endif
# define `$INSTANCE_NAME`_Disconnect(channel) `$INSTANCE_NAME`_Unset(channel)
#else
# if !`$INSTANCE_NAME`_ATMOSTONE
void `$INSTANCE_NAME`_Connect(uint8 channel) `=ReentrantKeil($INSTANCE_NAME ."_Connect")`;
# endif
void `$INSTANCE_NAME`_Disconnect(uint8 channel) `=ReentrantKeil($INSTANCE_NAME ."_Disconnect")`;
#endif

#if `$INSTANCE_NAME`_ATMOSTONE
# define `$INSTANCE_NAME`_Stop() `$INSTANCE_NAME`_DisconnectAll()
# define `$INSTANCE_NAME`_Select(channel) `$INSTANCE_NAME`_FastSelect(channel)
void `$INSTANCE_NAME`_DisconnectAll(void) `=ReentrantKeil($INSTANCE_NAME ."_DisconnectAll")`;
#else
# define `$INSTANCE_NAME`_Stop() `$INSTANCE_NAME`_Start()
void `$INSTANCE_NAME`_Select(uint8 channel) `=ReentrantKeil($INSTANCE_NAME ."_Select")`;
# define `$INSTANCE_NAME`_DisconnectAll() `$INSTANCE_NAME`_Start()
#endif

#endif /* CY_AMUX_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
