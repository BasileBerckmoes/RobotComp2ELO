/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition of the 
*  Voltage Fault Detector Component.
*
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_`$INSTANCE_NAME`_H)
#define CY_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_PVT.h"


/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void  `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void  `$INSTANCE_NAME`_SetSpeed(uint8 speedMode) `=ReentrantKeil($INSTANCE_NAME . "_SetSpeed")`;
void  `$INSTANCE_NAME`_ComparatorCal(uint8 compType) `=ReentrantKeil($INSTANCE_NAME . "_ComparatorCal")`;

#if (`$INSTANCE_NAME`_COMP_TYPE == `$INSTANCE_NAME`_OV_UV)
    void `$INSTANCE_NAME`_GetOVUVFaultStatus(uint32 * ovStatus, uint32 * uvStatus) `=ReentrantKeil($INSTANCE_NAME . "_GetOVUVFaultStatus")`;
#elif (`$INSTANCE_NAME`_COMP_TYPE == `$INSTANCE_NAME`_OV)
    void `$INSTANCE_NAME`_GetOVFaultStatus(uint32 * status) `=ReentrantKeil($INSTANCE_NAME . "_GetOVFaultStatus")`;
#else 
    void `$INSTANCE_NAME`_GetUVFaultStatus(uint32 * status) `=ReentrantKeil($INSTANCE_NAME . "_GetUVFaultStatus")`;
#endif /* (`$INSTANCE_NAME`_COMP_TYPE == `$INSTANCE_NAME`_OV_UV) */


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_LOW_SPEED                  0u
#define `$INSTANCE_NAME`_HIGH_SPEED                 1u

#define `$INSTANCE_NAME`_STATUS_MASK                `$StatusMask`

#define `$INSTANCE_NAME`_DAC_RANGE                  `$DacRange`u
#define `$INSTANCE_NAME`_DAC_RANGE_1V               0u
#define `$INSTANCE_NAME`_DAC_RANGE_4V               1u

#define `$INSTANCE_NAME`_GF_LENGTH                  `$GfLength`u


/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_CONTROL_REG                (* (reg8 *)`$INSTANCE_NAME`_bVFD_CtlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR                (  (reg8 *)`$INSTANCE_NAME`_bVFD_CtlReg__CONTROL_REG)

#define `$INSTANCE_NAME`_STATUS_REG                 (* (reg8 *)`$INSTANCE_NAME`_bVFD_StsReg__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_PTR                 (  (reg8 *)`$INSTANCE_NAME`_bVFD_StsReg__STATUS_REG)

/* Glitch filter definition */
#define `$INSTANCE_NAME`_PG_FILTER_LENGTH_REG       (* (reg8  *)`$INSTANCE_NAME`_bVFD_PgFilt__D0_REG)
#if (`$INSTANCE_NAME`_ENABLE_OV_DETECT)
#define `$INSTANCE_NAME`_FILTER_IN_FIFO_PTR         (  (reg16 *)`$INSTANCE_NAME`_bVFD_PgFilt__16BIT_F0_REG)
#define `$INSTANCE_NAME`_FILTER_OUT_FIFO_PTR        (  (reg16 *)`$INSTANCE_NAME`_bVFD_PgFilt__16BIT_F1_REG)
#define `$INSTANCE_NAME`_OV_FILTER_LENGTH_REG       (* (reg8  *)`$INSTANCE_NAME`_bVFD_OV_OvFilt__D0_REG)
#else
#define `$INSTANCE_NAME`_FILTER_IN_FIFO_PTR         (  (reg8 *)`$INSTANCE_NAME`_bVFD_PgFilt__F0_REG)
#define `$INSTANCE_NAME`_FILTER_OUT_FIFO_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_PgFilt__F1_REG)
#endif /* `$INSTANCE_NAME`_ENABLE_OV_DETECT */

#define `$INSTANCE_NAME`_PG_FILTER_FIFO_ACTL_REG    (* (reg8 *)`$INSTANCE_NAME`_bVFD_PgFilt__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_OV_FILTER_FIFO_ACTL_REG    (* (reg8 *)`$INSTANCE_NAME`_bVFD_OV_OvFilt__DP_AUX_CTL_REG)

/* Voltage index and settling delay counters */ 
#define `$INSTANCE_NAME`_VIN_DELAY_CNT_ACTL_REG     (* (reg8 *)`$INSTANCE_NAME`_bVFD_Settling_Timer__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_VIN_INDEX_CNT_ACTL_REG     (* (reg8 *)`$INSTANCE_NAME`_bVFD_VoltCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_VIN_INDEX_CNT_COUNT_REG    (* (reg8 *)`$INSTANCE_NAME`_bVFD_VoltCounter__COUNT_REG)

/* Power converters status bits */
#define `$INSTANCE_NAME`_PG_STS8_STATUS_REG         (* (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_8__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_PG_STS8_STATUS_PTR         (  (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_8__Sts__STATUS_REG)
#if (`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 8u)
#define `$INSTANCE_NAME`_PG_STS16_STATUS_REG        (* (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_16__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_PG_STS16_STATUS_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_16__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 8u */
#if (`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 16u)
#define `$INSTANCE_NAME`_PG_STS24_STATUS_REG        (* (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_24__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_PG_STS24_STATUS_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_24__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 16u */
#if (`$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 24u)
#define `$INSTANCE_NAME`_PG_STS32_STATUS_REG        (* (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_32__Sts__STATUS_REG)
#define `$INSTANCE_NAME`_PG_STS32_STATUS_PTR        (  (reg8 *)`$INSTANCE_NAME`_bVFD_PG_STS_32__Sts__STATUS_REG)
#endif /* `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES > 24u */


/***************************************
*       Register Constants
***************************************/

/* Control register bits */
#define `$INSTANCE_NAME`_EN                         0x01u
#define `$INSTANCE_NAME`_PAUSE                      0x02u

/* FIFO clearing bits */
#define `$INSTANCE_NAME`_FIFO_CLR                   0x03u

/* Firmware enable signal for internal counters */
#define `$INSTANCE_NAME`_CNT_START                  0x20u


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Pause
********************************************************************************
*
* Summary:
*  Pauses the controller state machine. The current PGOOD states are kept when
*  the component is paused.
*  Note that calling this API does not stop the component until it completes
*  the current process cycle. Therefore, if the purpose of calling this API is
*  specifically to change the VDAC settings (for calibration purposes for example),
*  sufficient time should be allowed to let the component run to a completion
*  before an attempt to access the VDACs directly. This can be checked by
*  calling VFD_IsPaused().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Stops the fault detection state machine. Does not stop the component 
*  immediately.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Pause()        (`$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_PAUSE)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsPaused
********************************************************************************
*
* Summary:
*  Checks to see if the component is paused.
*
* Parameters:
*  None.
*
* Return:
*  True if the component is paused.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_IsPaused()     (`$INSTANCE_NAME`_STATUS_REG == 0u)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Resume
********************************************************************************
*
* Summary:
*  Resumes the controller state machine.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Restarts the fault detection logic.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_Resume()       (`$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_EN)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetGlitchFilterLength
********************************************************************************
*
* Summary:
*  Sets glitch filter length.
*
* Parameters:
*  filterLength: Filter length. Absolute time units depend on the input clock
*  frequency. Valid range: 1..255
*
* Return:
*  None.
*
*******************************************************************************/
#ifdef `$INSTANCE_NAME`_OV_FILTER_LENGTH_REG
#define `$INSTANCE_NAME`_SetGlitchFilterLength(filterLength) do { \
                                                                 `$INSTANCE_NAME`_PG_FILTER_LENGTH_REG = (filterLength); \
                                                                 `$INSTANCE_NAME`_OV_FILTER_LENGTH_REG = (filterLength); \
                                                             } while(0)
#else
#define `$INSTANCE_NAME`_SetGlitchFilterLength(filterLength)    (`$INSTANCE_NAME`_PG_FILTER_LENGTH_REG = (filterLength))
#endif  /*`$INSTANCE_NAME`_OV_FILTER_LENGTH_REG */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetGlitchFilterLength
********************************************************************************
*
* Summary:
*  Returns glitch filter length. 
*
* Parameters:
*  None.
*
* Return:
*  Glitch filter length. Absolute time units depend on input clock frequency.
*  Valid range: 1..255.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_GetGlitchFilterLength()    `$INSTANCE_NAME`_PG_FILTER_LENGTH_REG


#endif /* CY_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
