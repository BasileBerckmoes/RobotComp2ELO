/*******************************************************************************
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Contains the function prototypes and constants available to the SENT
* component.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "`$INSTANCE_NAME`_PWM.h"
#include "`$INSTANCE_NAME`_ISR.h"
#include "`$INSTANCE_NAME`_CLK.h"


/*******************************************************************************
*    Conditional Compilation Parameters
*******************************************************************************/

#define `$INSTANCE_NAME`_CRC_IMPLEMENTATION     (`$CRC`UL)
#define `$INSTANCE_NAME`_PAUSE_PULSE            (`$PausePulse`UL)
#define `$INSTANCE_NAME`_CLOCK_PERIOD_NS_DECS   (`$ClockPeriodNsDecades`U)
#define `$INSTANCE_NAME`_TRANSMIT_MODE          (`$TransmitMode`UL)

#define `$INSTANCE_NAME`_CLOCK_ONE_DEC          (10U)
#define `$INSTANCE_NAME`_CLOCK_ROUND            (5U)

/* The clock divider define */
#define `$INSTANCE_NAME`_CLOCK_DIVIDER  ((uint16) (((`$INSTANCE_NAME`_CLOCK_PERIOD_NS_DECS * \
                                                     CYDEV_BCLK__HFCLK__MHZ) + `$INSTANCE_NAME`_CLOCK_ROUND) / \
                                                     `$INSTANCE_NAME`_CLOCK_ONE_DEC))


/*******************************************************************************
*   Custom Declarations
*******************************************************************************/

#ifdef CYDEV_VDDIO_MV
    #if (CYDEV_VDDIO_MV < 4850UL)
        #warning "As per the SAE J2716 standard, device should be operating in this range: 4.85 V to 5.15 V."
    #endif /* CYDEV_VDDIO_MV < 4850UL */
#endif /* CYDEV_VDDIO_MV */

#ifdef CYDEV_VDDD_MV
    #if (CYDEV_VDDD_MV < 4850UL)
        #warning "As per the SAE J2716 standard, device should be operating in this range: 4.85 V to 5.15 V."
    #endif /* CYDEV_VDDD_MV < 4850UL */
#endif /* CYDEV_VDDD_MV */

#ifdef CYDEV_VDD_MV
    #if (CYDEV_VDD_MV < 4850UL)
        #warning "As per the SAE J2716 standard, device should be operating in this range: 4.85 V to 5.15 V."
    #endif /* CYDEV_VDD_MV < 4850UL */
#endif /* CYDEV_VDD_MV */


/*******************************************************************************
*   Internal Constants
*******************************************************************************/

`#cy_declare_enum EnableDisable`
`#cy_declare_enum CRC`
`#cy_declare_enum TransmitMode`


/*******************************************************************************
*          API Constants
*******************************************************************************/

#define `$INSTANCE_NAME`_NIBBLE_MASK    (0xfU)
#define `$INSTANCE_NAME`_DATA_NIBBLES   (6U)

/* Status + data, crc is calculated automatically */
#define `$INSTANCE_NAME`_USER_NIBBLES   (`$INSTANCE_NAME`_DATA_NIBBLES + 1U)

#define `$INSTANCE_NAME`_ALL_TICKS      (282U)
#define `$INSTANCE_NAME`_SYNC_TICKS     (56UL)
#define `$INSTANCE_NAME`_ZERO_TICKS     (12U)

#define `$INSTANCE_NAME`_CRC_IDX        (7U)

#if (`$INSTANCE_NAME`_PAUSE_PULSE == `$INSTANCE_NAME`__ENABLED)
    #define `$INSTANCE_NAME`_LAST_IDX       (9U)
    #define `$INSTANCE_NAME`_PAUSE_IDX      (8U)
    #define `$INSTANCE_NAME`_ALL_NIBBLES    (`$INSTANCE_NAME`_USER_NIBBLES + 1U)
#else
    #define `$INSTANCE_NAME`_LAST_IDX       (8U)
    #define `$INSTANCE_NAME`_ALL_NIBBLES    (`$INSTANCE_NAME`_USER_NIBBLES)
#endif /* `$INSTANCE_NAME`_PAUSE_PULSE */

#define `$INSTANCE_NAME`_NEW_FRAME          (0U)

#if (`$INSTANCE_NAME`_TRANSMIT_MODE == `$INSTANCE_NAME`__SINGLE_MODE)
    #if (`$INSTANCE_NAME`_PWM_CY_TCPWM_V2 == 0U)
        #define `$INSTANCE_NAME`_END_OF_FRAME   (`$INSTANCE_NAME`_LAST_IDX + 4U)
        #define `$INSTANCE_NAME`_STOP_COUNTER   (`$INSTANCE_NAME`_LAST_IDX + 3U)
        #define `$INSTANCE_NAME`_PREPARE_TO_STOP_COUNTER   (`$INSTANCE_NAME`_LAST_IDX + 2U)
    #else
        #define `$INSTANCE_NAME`_END_OF_FRAME   (`$INSTANCE_NAME`_LAST_IDX + 3U)
        #define `$INSTANCE_NAME`_STOP_COUNTER   (`$INSTANCE_NAME`_LAST_IDX + 2U)
        #define `$INSTANCE_NAME`_PREPARE_TO_STOP_COUNTER   (`$INSTANCE_NAME`_LAST_IDX + 1U)
    #endif /* (`$INSTANCE_NAME`_PWM_CY_TCPWM_V2 == 0U) */
#else
    #define `$INSTANCE_NAME`_END_OF_FRAME   (`$INSTANCE_NAME`_LAST_IDX)
#endif /* `$INSTANCE_NAME`_PAUSE_PULSE */

#define `$INSTANCE_NAME`_SEED                (0x5U)
#define `$INSTANCE_NAME`_PWM_LOW_TICKS       (0x5U)
#define `$INSTANCE_NAME`_TICKS_PREP_TO_STOP  ((uint32) `$INSTANCE_NAME`_PWM_LOW_TICKS - 1U)

/* Need to take into account that PSoC 4000 has different version of TCPWM V2 HW */
#if (CY_PSOC4_4000)
    #define `$INSTANCE_NAME`_COMP_PREP_TO_STOP   (`$INSTANCE_NAME`_PWM_LOW_TICKS)
#else
    #define `$INSTANCE_NAME`_COMP_PREP_TO_STOP   (0U)
#endif /* CY_PSOC4_4000 */

/** \addtogroup group_constants
* @{ */

/**
* \defgroup group_sent_status SENT TX status definitions
* \{
* Definitions of SENT TX status
*/

/** The define to show the data is sent and the component is ready 
* to send a new data */
#define `$INSTANCE_NAME`_READY        (0U)

/** The define to show the component is sending previous data */
#define `$INSTANCE_NAME`_BUSY         (1U)
/** \} group_sent_status */
/** @} constants */


/*******************************************************************************
*       Function Prototypes
*******************************************************************************/

/** \addtogroup group_general
* @{ */
/** \cond INTERNAL */
CY_ISR_PROTO(`$INSTANCE_NAME`_Interrupt); 
/** \endcond */

void   `$INSTANCE_NAME`_Init(void);
void   `$INSTANCE_NAME`_UpdateData(uint8 const data[]);
void   `$INSTANCE_NAME`_Start(uint8 const data[]);
static  CY_INLINE void `$INSTANCE_NAME`_Enable(void);
static  CY_INLINE void `$INSTANCE_NAME`_Stop(void);
static  CY_INLINE uint8 `$INSTANCE_NAME`_GetStatus(void);
/** @} general */

/** \addtogroup group_power
* @{ */
uint32   `$INSTANCE_NAME`_Sleep(void);
static void CY_INLINE `$INSTANCE_NAME`_Wakeup(void);
/** @} power */


/*******************************************************************************
*    Variables with external linkage 
*******************************************************************************/

/** \addtogroup group_globals
@{ */
extern uint8  `$INSTANCE_NAME`_initVar;
extern uint8 `$INSTANCE_NAME`_status;
/** @} group_globals */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Enables the PWM that is used in `$INSTANCE_NAME` to generate pulses.
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_PWM_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
****************************************************************************//**
*
*  Disables `$INSTANCE_NAME`.
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_PWM_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetStatus
****************************************************************************//**
*
* Returns the state of SENT readiness to send new data message.
*
* \return
* Status of readiness to send new data, see \ref group_sent_status.
*
*******************************************************************************/
static CY_INLINE uint8 `$INSTANCE_NAME`_GetStatus(void)
{
    return (`$INSTANCE_NAME`_status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
****************************************************************************//**
*
* Restores the user configuration and restores the enable state.
*
*******************************************************************************/
static CY_INLINE void `$INSTANCE_NAME`_Wakeup(void)
{
    `$INSTANCE_NAME`_PWM_Wakeup();
}

#endif /* `$INSTANCE_NAME`_H */


/* [] END OF FILE */
