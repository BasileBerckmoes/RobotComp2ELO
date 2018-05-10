/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the Comparator
*  component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CSD_Comp_P4_`$INSTANCE_NAME`_H)
#define CY_CSD_Comp_P4_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

#include "`$INSTANCE_NAME`_SampleClk.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_VOLTAGE_REF_SOURCE         (`$VoltageRefSource`u)
#define `$INSTANCE_NAME`_VOLTAGE_REF_TYPE           (`$VoltageRefType`u)
#define `$INSTANCE_NAME`_TAP                        (`$Tap`UL)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_backup_struct;


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetReferenceVoltageType(uint32 refVoltageType);
void `$INSTANCE_NAME`_SetVoltageTap(uint32 voltageTap);
uint32 `$INSTANCE_NAME`_GetCompare(void);
/** @} group_general */
/**
* \addtogroup group_power
* @{
*/
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);
/** @} power */


/***************************************
*           Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8 `$INSTANCE_NAME`_initVar;
/** @} globals */


/***************************************
*           API Constants
***************************************/

/* Calculating divider for SampleClock to have its frequency equal to SYSCLK  */
#define `$INSTANCE_NAME`_SAMPLECLK_DIVIDER          (CYDEV_BCLK__HFCLK__MHZ/CYDEV_BCLK__SYSCLK__MHZ)
`$VRefRange`
#define `$INSTANCE_NAME`_VREF_STEP_MVOLTS           (`$VRefStep`u)
#define `$INSTANCE_NAME`_REFGEN_GAIN                (`$RefGenGain`UL)

#define `$INSTANCE_NAME`_FIXED_REF_VOLTAGE          (0u)
#define `$INSTANCE_NAME`_ADJUSTABLE_REF_VOLTAGE     (1u)

#define `$INSTANCE_NAME`_INTERNAL_BANDGAP_REFERENCE (0u)
#define `$INSTANCE_NAME`_EXTERNAL_REFERENCE         (1u)

/* Startup timeouts for different parts of CSD IP in micro seconds */
#define `$INSTANCE_NAME`_CSD_IP_STARTUP_TIMEOUT     (5u)
#define `$INSTANCE_NAME`_REFGEN_STARTUP_TIMEOUT     (10u)
#define `$INSTANCE_NAME`_CSDCMP_STARTUP_TIMEOUT     (1u)

#define `$INSTANCE_NAME`_2000_MV                    (2000u)
#ifdef CYDEV_VDDA_MV
    #define `$INSTANCE_NAME`_CYDEV_VDDA_MV          (CYDEV_VDDA_MV)
#else
    #define `$INSTANCE_NAME`_CYDEV_VDDA_MV          (CYDEV_VDD_MV)
#endif  /* CYDEV_VDDA_MV */

#if (`$INSTANCE_NAME`_FIXED_REF_VOLTAGE == `$INSTANCE_NAME`_VOLTAGE_REF_TYPE)
    #define `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG_INIT (`$INSTANCE_NAME`_SW_SCRH_CLOSED)
    #define `$INSTANCE_NAME`_CSD_REFGEN_SW_CFG         (`$INSTANCE_NAME`_BYPASS)
#else /* `$INSTANCE_NAME`_ADJUSTABLE_REF_VOLTAGE */
    #define `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG_INIT (`$INSTANCE_NAME`_SW_SCRL_CLOSED)
    #define `$INSTANCE_NAME`_CSD_REFGEN_SW_CFG         (`$INSTANCE_NAME`_RES_EN)
#endif /* (`$INSTANCE_NAME`_FIXED_REF_VOLTAGE == `$INSTANCE_NAME`_VOLTAGE_REF_TYPE) */

#define `$INSTANCE_NAME`_CSD_CONFIG_REG_INIT        (`$INSTANCE_NAME`_CSD_ENABLE | `$INSTANCE_NAME`_CSD_SENSE_EN)
#define `$INSTANCE_NAME`_CSD_REFGEN_REG_INIT        (`$INSTANCE_NAME`_CSD_REFGEN_SW_CFG | \
            (uint32) (`$INSTANCE_NAME`_REFGEN_GAIN << CYFLD_CSD_GAIN__OFFSET) | \
            (uint32) ((`$INSTANCE_NAME`_TAP - 1u) << CYFLD_CSD_VREFLO_SEL__OFFSET))
#define `$INSTANCE_NAME`_CSD_CSDCMP_REG_INIT        (`$INSTANCE_NAME`_CMP_MODE | `$INSTANCE_NAME`_FEEDBACK_MODE)


/***************************************
*             Registers
***************************************/

/* CSD IP block registers */
#define `$INSTANCE_NAME`_CSD_CONFIG_REG             (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__CSD_CONFIG)
#define `$INSTANCE_NAME`_CSD_CONFIG_PTR             ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__CSD_CONFIG)
#define `$INSTANCE_NAME`_CSD_STATUS_REG             (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__CSD_STATUS)
#define `$INSTANCE_NAME`_CSD_STATUS_PTR             ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__CSD_STATUS)
#define `$INSTANCE_NAME`_CSD_CSDCMP_REG             (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__CSDCMP)
#define `$INSTANCE_NAME`_CSD_CSDCMP_PTR             ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__CSDCMP)
#define `$INSTANCE_NAME`_CSD_REFGEN_REG             (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__REFGEN)
#define `$INSTANCE_NAME`_CSD_REFGEN_PTR             ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__REFGEN)
#define `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_REG       (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__SW_CMP_N_SEL)
#define `$INSTANCE_NAME`_CSD_SW_CMP_N_SEL_PTR       ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__SW_CMP_N_SEL)
#define `$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_REG     (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__SW_AMUXBUF_SEL)
#define `$INSTANCE_NAME`_CSD_SW_AMUXBUF_SEL_PTR     ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__SW_AMUXBUF_SEL)
#define `$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_REG      (*(reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__SW_REFGEN_SEL)
#define `$INSTANCE_NAME`_CSD_SW_REFGEN_SEL_PTR      ( (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_v2_comp__SW_REFGEN_SEL)


/***************************************
*       Register Constants
***************************************/

/* CSD IP block Configuration and control register bits */
#define `$INSTANCE_NAME`_CSD_ENABLE                 ((uint32) (0x01UL << CYFLD_CSD_ENABLE__OFFSET))
#define `$INSTANCE_NAME`_CSD_SENSE_EN               ((uint32) (0x01UL << CYFLD_CSD_SENSE_EN__OFFSET))

/* CSD IP block Status register bits */
#define `$INSTANCE_NAME`_CSDCMP_OUT                 ((uint32) (0x01UL << CYFLD_CSD_CSDCMP_OUT__OFFSET))

/* CSD IP block Reference Generator configration register bits */
#define `$INSTANCE_NAME`_REFGEN_EN                  ((uint32) (0x01UL << CYFLD_CSD_REFGEN_EN__OFFSET))
#define `$INSTANCE_NAME`_BYPASS                     ((uint32) (0x01UL << CYFLD_CSD_BYPASS__OFFSET))
#define `$INSTANCE_NAME`_RES_EN                     ((uint32) (0x01UL << CYFLD_CSD_RES_EN__OFFSET))
#define `$INSTANCE_NAME`_GAIN_MASK                  ((uint32) (0x1FUL << CYFLD_CSD_GAIN__OFFSET))
#define `$INSTANCE_NAME`_VREFLO_SEL_MASK            ((uint32) (0x1FUL << CYFLD_CSD_VREFLO_SEL__OFFSET))

/* CSD IP block Comparator configuration register bits */
#define `$INSTANCE_NAME`_CSDCMP_EN                  ((uint32) (0x01UL << CYFLD_CSD_CSDCMP_EN__OFFSET))
#define `$INSTANCE_NAME`_CMP_MODE                   ((uint32) (0x01UL << CYFLD_CSD_CMP_MODE__OFFSET))
#define `$INSTANCE_NAME`_FEEDBACK_MODE              ((uint32) (0x01UL << CYFLD_CSD_FEEDBACK_MODE__OFFSET))

/* CSD IP block Negative comparator input switch configuration register bits */
#define `$INSTANCE_NAME`_SW_SCRH_CLOSED             ((uint32) (0x01UL << CYFLD_CSD_SW_SCRH__OFFSET))
#define `$INSTANCE_NAME`_SW_SCRL_CLOSED             ((uint32) (0x01UL << CYFLD_CSD_SW_SCRL__OFFSET))

/* CSD IP block Amux buffer switch configuration register bits */
#define `$INSTANCE_NAME`_SW_IRLB_CLOSED             ((uint32) (0x01UL << CYFLD_CSD_SW_IRLB__OFFSET))
#define `$INSTANCE_NAME`_SW_IRH_CLOSED              ((uint32) (0x01UL << CYFLD_CSD_SW_IRH__OFFSET))

/* CSD IP block Reference Generator switch configuration register bits */
#define `$INSTANCE_NAME`_SW_SGMB_CLOSED             ((uint32) (0x01UL << CYFLD_CSD_SW_SGMB__OFFSET))
#define `$INSTANCE_NAME`_SW_SGRE_CLOSED             ((uint32) (0x01UL << CYFLD_CSD_SW_SGRE__OFFSET))
#define `$INSTANCE_NAME`_SW_SGR_CLOSED              ((uint32) (0x01UL << CYFLD_CSD_SW_SGR__OFFSET))

#endif /* End CY_CSD_Comp_P4_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
