/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the IDAC7
*  component.
*
********************************************************************************
* \copyright
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_IDAC7_`$INSTANCE_NAME`_H)
#define CY_IDAC7_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_CURRENT_VALUE        ((uint32)`$Value`)
#define `$INSTANCE_NAME`_CURRENT_RANGE        ((uint32)`$IDACRange`)
#define `$INSTANCE_NAME`_CURRENT_POLARITY     ((uint32)`$Polarity`)


/**************************************
*    Enumerated Types and Parameters
**************************************/

/* IDAC7 polarity setting constants */
`#cy_declare_enum PolarityType`

/* IDAC7 range setting constants */
`#cy_declare_enum RangeType`

/* IDAC7 polarity setting definitions */
#define `$INSTANCE_NAME`_POL_SOURCE     ((uint32)`$INSTANCE_NAME`__POL_SOURCE)
#define `$INSTANCE_NAME`_POL_SINK       ((uint32)`$INSTANCE_NAME`__POL_SINK)

/* IDAC7 range setting definitions */
#define `$INSTANCE_NAME`_RNG_4_76UA     ((uint32)`$INSTANCE_NAME`__RNG_4_76UA)
#define `$INSTANCE_NAME`_RNG_9_52UA     ((uint32)`$INSTANCE_NAME`__RNG_9_52UA)
#define `$INSTANCE_NAME`_RNG_38_1UA     ((uint32)`$INSTANCE_NAME`__RNG_38_1UA)
#define `$INSTANCE_NAME`_RNG_76_2UA     ((uint32)`$INSTANCE_NAME`__RNG_76_2UA)
#define `$INSTANCE_NAME`_RNG_152_4UA    ((uint32)`$INSTANCE_NAME`__RNG_152_4UA)
#define `$INSTANCE_NAME`_RNG_304_8UA    ((uint32)`$INSTANCE_NAME`__RNG_304_8UA)
#define `$INSTANCE_NAME`_RNG_609_6UA    ((uint32)`$INSTANCE_NAME`__RNG_609_6UA)


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
void `$INSTANCE_NAME`_SetValue(uint32 current);
void `$INSTANCE_NAME`_SetPolarity(uint32 polarity);
void `$INSTANCE_NAME`_SetRange(uint32 range);
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
extern uint32 `$INSTANCE_NAME`_initVar;
/** @} globals */


/***************************************
*            API Constants
***************************************/

/* CSD Config register */
#define `$INSTANCE_NAME`_CSD_CONFIG_ENABLE_POS    ((uint32)31u)
#define `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN_POS  ((uint32)12u)
#define `$INSTANCE_NAME`_CSD_CONFIG_LOW_VDDA_POS  ((uint32)3u)
#define `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN      ((uint32)(0x1u) <<  `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN_POS)
#define `$INSTANCE_NAME`_CSD_CONFIG_ENABLE        ((uint32)(0x1u) <<  `$INSTANCE_NAME`_CSD_CONFIG_ENABLE_POS)
#define `$INSTANCE_NAME`_CSD_CONFIG_LOW_VDDA      ((uint32)(0x1u) <<  `$INSTANCE_NAME`_CSD_CONFIG_LOW_VDDA_POS)

/* IDAC register */
#define `$INSTANCE_NAME`_CURRENT_VALUE_POS        ((uint32)0u)
#define `$INSTANCE_NAME`_POLY_DYN_POS             ((uint32)7u)
#define `$INSTANCE_NAME`_POLARITY_POS             ((uint32)8u)
#define `$INSTANCE_NAME`_LEG1_MODE_POS            ((uint32)16u)
#define `$INSTANCE_NAME`_LEG2_MODE_POS            ((uint32)18u)
#define `$INSTANCE_NAME`_DSI_CTRL_EN_POS          ((uint32)21u)
#define `$INSTANCE_NAME`_RANGE_POS                ((uint32)22u)
#define `$INSTANCE_NAME`_LEG1_EN_POS              ((uint32)24u)
#define `$INSTANCE_NAME`_LEG2_EN_POS              ((uint32)25u)

#define `$INSTANCE_NAME`_CURRENT_VALUE_MASK       ((uint32)(0x7Fu)    <<  `$INSTANCE_NAME`_CURRENT_VALUE_POS)
#define `$INSTANCE_NAME`_POLARITY_MASK            ((uint32)(0x3u)     <<  `$INSTANCE_NAME`_POLARITY_POS)
#define `$INSTANCE_NAME`_POLY_DYN                 ((uint32)(0x1u)     <<  `$INSTANCE_NAME`_POLY_DYN_POS)
#define `$INSTANCE_NAME`_LEG1_MODE_MASK           ((uint32)(0x3u)     <<  `$INSTANCE_NAME`_LEG1_MODE_POS)
#define `$INSTANCE_NAME`_LEG2_MODE_MASK           ((uint32)(0x3u)     <<  `$INSTANCE_NAME`_LEG2_MODE_POS)
#define `$INSTANCE_NAME`_DSI_CTRL_EN              ((uint32)(0x1u)     <<  `$INSTANCE_NAME`_DSI_CTRL_EN_POS)
#define `$INSTANCE_NAME`_RANGE_MASK               ((uint32)(0x3u)     <<  `$INSTANCE_NAME`_RANGE_POS)
#define `$INSTANCE_NAME`_LEG1_EN                  ((uint32)(0x1u)     <<  `$INSTANCE_NAME`_LEG1_EN_POS)
#define `$INSTANCE_NAME`_LEG2_EN                  ((uint32)(0x1u)     <<  `$INSTANCE_NAME`_LEG2_EN_POS)

/* Creator-global defines */
#define `$INSTANCE_NAME`_2000_MV                  (2000u)

#ifdef CYDEV_VDDA_MV
    #define `$INSTANCE_NAME`_CYDEV_VDDA_MV        (CYDEV_VDDA_MV)
#else
    #ifdef CYDEV_VDD_MV
        #define `$INSTANCE_NAME`_CYDEV_VDDA_MV    (CYDEV_VDD_MV)
    #endif
#endif

#if defined(CYIPBLOCK_m0s8csdv2_VERSION)
    #define `$INSTANCE_NAME`_M0S8CSDV2_BLOCK_VER  (CYIPBLOCK_m0s8csdv2_VERSION)
#else
    #define `$INSTANCE_NAME`_M0S8CSDV2_BLOCK_VER  (0u)
#endif /* (CYIPBLOCK_m0s8csdv2_VERSION) */

#define `$INSTANCE_NAME`_S8CSDV2_VER_2            (2u)

#if ((`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV) &&\
     (`$INSTANCE_NAME`_S8CSDV2_VER_2 == `$INSTANCE_NAME`_M0S8CSDV2_BLOCK_VER))
     #define `$INSTANCE_NAME`_IDAC_EN_CONFIG      (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE |\
                                                   `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN |\
                                                   `$INSTANCE_NAME`_CSD_CONFIG_LOW_VDDA)
#else
     #define `$INSTANCE_NAME`_IDAC_EN_CONFIG      (`$INSTANCE_NAME`_CSD_CONFIG_ENABLE |\
                                                   `$INSTANCE_NAME`_CSD_CONFIG_SENSE_EN)
#endif /* (`$INSTANCE_NAME`_2000_MV > `$INSTANCE_NAME`_CYDEV_VDDA_MV) */

/***************************************
*        Registers
***************************************/

#define `$INSTANCE_NAME`_CSD_CONTROL_REG    (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CONFIG)
#define `$INSTANCE_NAME`_CSD_CONTROL_PTR    ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CONFIG)

#define `$INSTANCE_NAME`_IDAC_CONTROL_REG   (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__IDAC)
#define `$INSTANCE_NAME`_IDAC_CONTROL_PTR   ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__IDAC)

#endif /* CY_IDAC7_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
