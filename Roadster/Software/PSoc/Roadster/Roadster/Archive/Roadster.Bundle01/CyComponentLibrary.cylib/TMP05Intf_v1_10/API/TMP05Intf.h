/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the TMP05Intf component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_`$INSTANCE_NAME`_H)
#define CY_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_CUSTOM_CONTINUOUS_MODE     (`$ContinuousMode`u)
#define `$INSTANCE_NAME`_CUSTOM_NUM_SENSORS         (`$NumSensors`u)

#if (CY_PSOC3)
    #define `$INSTANCE_NAME`_LO_CNT_REG         (* (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__F0_REG)
    #define `$INSTANCE_NAME`_LO_CNT_PTR         (  (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__F0_REG)
    #define `$INSTANCE_NAME`_HI_CNT_REG         (* (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__F1_REG)
    #define `$INSTANCE_NAME`_HI_CNT_PTR         (  (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__F1_REG)
    #define `$INSTANCE_NAME`_STATUS_REG         (* (reg8  *) `$INSTANCE_NAME`_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_PTR         (  (reg8  *) `$INSTANCE_NAME`_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define `$INSTANCE_NAME`_FIFO_AUXCTL_REG    (* (reg16 *)    \
                                                    `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_FIFO_AUXCTL_PTR    (  (reg16 *)    \
                                                    `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__DP_AUX_CTL_REG)

#else
    #define `$INSTANCE_NAME`_LO_CNT_REG         (* (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F0_REG)
    #define `$INSTANCE_NAME`_LO_CNT_PTR         (  (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F0_REG)
    #define `$INSTANCE_NAME`_HI_CNT_REG         (* (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F1_REG)
    #define `$INSTANCE_NAME`_HI_CNT_PTR         (  (reg16 *) `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__16BIT_F1_REG)
    #define `$INSTANCE_NAME`_STATUS_REG         (* (reg8  *) `$INSTANCE_NAME`_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define `$INSTANCE_NAME`_STATUS_PTR         (  (reg8  *) `$INSTANCE_NAME`_TMP05_STS_sts_sts_reg__STATUS_REG)
    #define `$INSTANCE_NAME`_FIFO_AUXCTL_REG    (* (reg16 *)    \
                                                    `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__16BIT_DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_FIFO_AUXCTL_PTR    (  (reg16 *)    \
                                                    `$INSTANCE_NAME`_bTMP05Intf_1_Tmp05Timer_u0__16BIT_DP_AUX_CTL_REG)
#endif

/* PSoC 5 support */
#if (CY_UDB_V0)
    #define `$INSTANCE_NAME`_CONTROL_REG    (* (reg8  *) `$INSTANCE_NAME`_bTMP05Intf_1_AsyncCtrl_CtrlReg__CONTROL_REG)
    #define `$INSTANCE_NAME`_CONTROL_PTR    (  (reg8  *) `$INSTANCE_NAME`_bTMP05Intf_1_AsyncCtrl_CtrlReg__CONTROL_REG)
#else
    #define `$INSTANCE_NAME`_CONTROL_REG    (* (reg8  *) `$INSTANCE_NAME`_bTMP05Intf_1_SyncCtrl_CtrlReg__CONTROL_REG)
    #define `$INSTANCE_NAME`_CONTROL_PTR    (  (reg8  *) `$INSTANCE_NAME`_bTMP05Intf_1_SyncCtrl_CtrlReg__CONTROL_REG)
#endif /* (End CY_UDB_V0) */


/*******************************************************************************
* Variables
*******************************************************************************/
extern volatile uint8  `$INSTANCE_NAME`_busyFlag;
extern uint8  `$INSTANCE_NAME`_initVar;


/***************************************
*         TMP05 Function Prototypes
***************************************/
void    `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void    `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void    `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void    `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void    `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void    `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void    `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void    `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void    `$INSTANCE_NAME`_Trigger(void) `=ReentrantKeil($INSTANCE_NAME . "_Trigger")`;
int16   `$INSTANCE_NAME`_GetTemperature (uint8 sensorNum) `=ReentrantKeil($INSTANCE_NAME . "_GetTemperature")`;
void    `$INSTANCE_NAME`_SetMode (uint8 mode) `=ReentrantKeil($INSTANCE_NAME . "_SetMode")`;
uint8   `$INSTANCE_NAME`_DiscoverSensors(void) `=ReentrantKeil($INSTANCE_NAME . "_DiscoverSensors")`;
uint8   `$INSTANCE_NAME`_ConversionStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ConversionStatus")`;


/***************************************
*       Enum Types
***************************************/

/* TMP05 status codes */
#define `$INSTANCE_NAME`_STATUS_IN_PROGRESS             (0x0u)
#define `$INSTANCE_NAME`_STATUS_COMPLETE                (0x1u)
#define `$INSTANCE_NAME`_STATUS_ERROR                   (0x2u)

/* TMP05 Modes */
#define `$INSTANCE_NAME`_MODE_CONTINUOUS                (0x1u)
#define `$INSTANCE_NAME`_MODE_ONESHOT                   (0x0u)

#endif /* `$INSTANCE_NAME`_H */


/* [] END OF FILE */
