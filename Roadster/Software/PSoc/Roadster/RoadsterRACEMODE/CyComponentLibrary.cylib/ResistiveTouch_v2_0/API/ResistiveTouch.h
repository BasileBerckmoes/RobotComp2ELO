/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the constants and parameter values for the ResistiveTouch
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RESISTIVE_TOUCH_`$INSTANCE_NAME`_H)
#define CY_RESISTIVE_TOUCH_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "`$INSTANCE_NAME`_`$ADC`.h"
#include "`$INSTANCE_NAME`_AMux.h"


/***************************************
*        Function Prototypes
****************************************/

void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`; 
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_ActivateX(void) `=ReentrantKeil($INSTANCE_NAME . "_ActivateX")`;
void `$INSTANCE_NAME`_ActivateY(void)`=ReentrantKeil($INSTANCE_NAME . "_ActivateY")`;
int16 `$INSTANCE_NAME`_Measure(void) `=ReentrantKeil($INSTANCE_NAME . "_Measure")`;
uint8 `$INSTANCE_NAME`_TouchDetect(void) `=ReentrantKeil($INSTANCE_NAME . "_TouchDetect")`;

void `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`; 
void `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`; 

/* Macros for emWinGraphics Library */
#define CYTOUCH_START()         `$INSTANCE_NAME`_Start() 
#define CYTOUCH_STOP()          `$INSTANCE_NAME`_Stop()
#define CYTOUCH_MEASURE()       `$INSTANCE_NAME`_Measure()
#define CYTOUCH_ACTIVATE_X()    `$INSTANCE_NAME`_ActivateX()
#define CYTOUCH_ACTIVATE_Y()    `$INSTANCE_NAME`_ActivateY()
#define CYTOUCH_TOUCHED()       `$INSTANCE_NAME`_TouchDetect()


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*       Constants
***************************************/

/* AMUX channel definitions */
#define `$INSTANCE_NAME`_AMUX_XP_CHAN   (0)
#define `$INSTANCE_NAME`_AMUX_YP_CHAN   (1)
#define `$INSTANCE_NAME`_AMUX_NO_CHAN   (-1)

/* The screen is touched if the measured value is lower than the specified
* threshold.
*/
#define `$INSTANCE_NAME`_TOUCH_THRESHOLD        (0x778)


#endif /* CY_RESIST_TOUCH_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
