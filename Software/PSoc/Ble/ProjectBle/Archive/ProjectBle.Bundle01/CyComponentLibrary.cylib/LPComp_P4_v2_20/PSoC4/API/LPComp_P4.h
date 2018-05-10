/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Low Power Comparator component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMPARATOR_`$INSTANCE_NAME`_H)
#define CY_COMPARATOR_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"


extern uint8  `$INSTANCE_NAME`_initVar;


/***************************************
*  Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_CY_LPCOMP_V0 (CYIPBLOCK_m0s8lpcomp_VERSION == 0u) 
#define `$INSTANCE_NAME`_CY_LPCOMP_V2 (CYIPBLOCK_m0s8lpcomp_VERSION >= 2u) 


/**************************************
*        Function Prototypes
**************************************/

void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Init(void);
void    `$INSTANCE_NAME`_Enable(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetSpeed(uint32 speed);
void    `$INSTANCE_NAME`_SetInterruptMode(uint32 mode);
uint32  `$INSTANCE_NAME`_GetInterruptSource(void);
void    `$INSTANCE_NAME`_ClearInterrupt(uint32 interruptMask);
void    `$INSTANCE_NAME`_SetInterrupt(uint32 interruptMask);
void    `$INSTANCE_NAME`_SetHysteresis(uint32 hysteresis);
uint32  `$INSTANCE_NAME`_GetCompare(void);
uint32  `$INSTANCE_NAME`_ZeroCal(void);
void    `$INSTANCE_NAME`_LoadTrim(uint32 trimVal);
void    `$INSTANCE_NAME`_Sleep(void);
void    `$INSTANCE_NAME`_Wakeup(void);
void    `$INSTANCE_NAME`_SaveConfig(void);
void    `$INSTANCE_NAME`_RestoreConfig(void);
#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    void    `$INSTANCE_NAME`_SetOutputMode(uint32 mode);
    void    `$INSTANCE_NAME`_SetInterruptMask(uint32 interruptMask);
    uint32  `$INSTANCE_NAME`_GetInterruptMask(void);
    uint32  `$INSTANCE_NAME`_GetInterruptSourceMasked(void);
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/**************************************
*           API Constants
**************************************/

#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    /* Constants for `$INSTANCE_NAME`_SetOutputMode(), mode parameter */
    #define `$INSTANCE_NAME`_OUT_PULSE      (0x00u)
    #define `$INSTANCE_NAME`_OUT_SYNC       (0x01u)
    #define `$INSTANCE_NAME`_OUT_DIRECT     (0x02u)
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */

#define `$INSTANCE_NAME`_INTR_PARAM_MASK    (0x03u)
#define `$INSTANCE_NAME`_SPEED_PARAM_MASK   (0x03u)

/* Constants for `$INSTANCE_NAME`_SetSpeed(), speed parameter */
#define `$INSTANCE_NAME`_MED_SPEED          (0x00u)
#define `$INSTANCE_NAME`_HIGH_SPEED         (0x01u)
#define `$INSTANCE_NAME`_LOW_SPEED          (0x02u)

/* Constants for `$INSTANCE_NAME`_SetInterruptMode(), mode parameter */
#define `$INSTANCE_NAME`_INTR_DISABLE       (0x00u)
#define `$INSTANCE_NAME`_INTR_RISING        (0x01u)
#define `$INSTANCE_NAME`_INTR_FALLING       (0x02u)
#define `$INSTANCE_NAME`_INTR_BOTH          (0x03u)

/* Constants for `$INSTANCE_NAME`_SetHysteresis(), hysteresis parameter */
#define `$INSTANCE_NAME`_HYST_ENABLE        (0x00u)
#define `$INSTANCE_NAME`_HYST_DISABLE       (0x01u)

/* Constants for `$INSTANCE_NAME`_ZeroCal() */
#define `$INSTANCE_NAME`_TRIMA_MASK         (0x1Fu)
#define `$INSTANCE_NAME`_TRIMA_SIGNBIT      (4u)
#define `$INSTANCE_NAME`_TRIMA_MAX_VALUE    (15u)
#define `$INSTANCE_NAME`_TRIMB_MASK         (0x1Fu)
#define `$INSTANCE_NAME`_TRIMB_SHIFT        (8u)
#define `$INSTANCE_NAME`_TRIMB_SIGNBIT      (4u)
#define `$INSTANCE_NAME`_TRIMB_MAX_VALUE    (15u)

/* Constants for `$INSTANCE_NAME`_GetInterruptSource() and 
* `$INSTANCE_NAME`_ClearInterrupt(), interruptMask parameter 
*/
#define `$INSTANCE_NAME`_INTR_SHIFT         (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SHIFT)
#define `$INSTANCE_NAME`_INTR               ((uint32)0x01u << `$INSTANCE_NAME`_INTR_SHIFT)

/* Constants for `$INSTANCE_NAME`_SetInterrupt(), interruptMask parameter */
#define `$INSTANCE_NAME`_INTR_SET_SHIFT     (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SET_SHIFT)
#define `$INSTANCE_NAME`_INTR_SET           ((uint32)0x01u << `$INSTANCE_NAME`_INTR_SHIFT)

#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    /* Constants for `$INSTANCE_NAME`_GetInterruptMask() and 
    * `$INSTANCE_NAME`_SetInterruptMask(), interruptMask parameter 
    */
    #define `$INSTANCE_NAME`_INTR_MASK_SHIFT    (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_MASK_SHIFT)
    #define `$INSTANCE_NAME`_INTR_MASK          ((uint32)0x01u << `$INSTANCE_NAME`_INTR_MASK_SHIFT)

    /* Constants for `$INSTANCE_NAME`_GetInterruptSourceMasked() */ 
    #define `$INSTANCE_NAME`_INTR_MASKED_SHIFT  (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_MASKED_SHIFT)
    #define `$INSTANCE_NAME`_INTR_MASKED        ((uint32)0x01u << `$INSTANCE_NAME`_INTR_MASKED_SHIFT)
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/***************************************
* Enumerated Types and Parameters 
***************************************/

/* Enumerated Types LPCompSpeedType, Used in parameter Speed */
`#declare_enum LPCompSpeedType`

/* Enumerated Types LPCompInterruptType, Used in parameter Interrupt */
`#declare_enum LPCompInterruptType`

/* Enumerated Types LPCompHysteresisType, Used in parameter Hysteresis */
`#declare_enum LPCompHysteresisType`

/* Enumerated Types OutputModeType, Used in parameter OutputMode */
`#declare_enum OutputModeType`


/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_INTERRUPT    (`$Interrupt`u)
#define `$INSTANCE_NAME`_SPEED        (`$Speed`u)
#define `$INSTANCE_NAME`_HYSTERESIS   (`$Hysteresis`u)
#if (`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #define `$INSTANCE_NAME`_OUT_MODE       (`$OutputMode`u)
    #define `$INSTANCE_NAME`_INTERRUPT_EN   (`$InterruptEnabled`u)
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/**************************************
*             Registers
**************************************/

#define `$INSTANCE_NAME`_CONFIG_REG     (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_CONFIG)
#define `$INSTANCE_NAME`_CONFIG_PTR     ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_CONFIG)

#define `$INSTANCE_NAME`_DFT_REG        (*(reg32 *)CYREG_LPCOMP_DFT)
#define `$INSTANCE_NAME`_DFT_PTR        ( (reg32 *)CYREG_LPCOMP_DFT)

#define `$INSTANCE_NAME`_INTR_REG       (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR)
#define `$INSTANCE_NAME`_INTR_PTR       ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR)

#define `$INSTANCE_NAME`_INTR_SET_REG   (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SET)
#define `$INSTANCE_NAME`_INTR_SET_PTR   ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_SET)

#define `$INSTANCE_NAME`_TRIMA_REG      (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_A)
#define `$INSTANCE_NAME`_TRIMA_PTR      ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_A)

#define `$INSTANCE_NAME`_TRIMB_REG      (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_B)
#define `$INSTANCE_NAME`_TRIMB_PTR      ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__TRIM_B)

#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #define `$INSTANCE_NAME`_INTR_MASK_REG    (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_MASK) 
    #define `$INSTANCE_NAME`_INTR_MASK_PTR    ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_MASK) 

    #define `$INSTANCE_NAME`_INTR_MASKED_REG  (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_MASKED) 
    #define `$INSTANCE_NAME`_INTR_MASKED_PTR  ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_INTR_MASKED) 
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/***************************************
*        Registers Constants
***************************************/

#define `$INSTANCE_NAME`_CONFIG_REG_SHIFT           (`$INSTANCE_NAME`_cy_psoc4_lpcomp_1__LPCOMP_CONFIG_SHIFT)

/* `$INSTANCE_NAME``$INSTANCE_NAME`_CONFIG_REG */
#define `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT    (0u)    /* [1:0]    Operating mode for the comparator      */
#define `$INSTANCE_NAME`_CONFIG_HYST_SHIFT          (2u)    /* [2]      Add 10mV hysteresis to the comparator: 0-enable, 1-disable */
#define `$INSTANCE_NAME`_CONFIG_INTR_SHIFT          (4u)    /* [5:4]    Sets Pulse/Interrupt mode              */
#define `$INSTANCE_NAME`_CONFIG_OUT_SHIFT           (6u)    /* [6]      Current output value of the comparator    */
#define `$INSTANCE_NAME`_CONFIG_EN_SHIFT            (7u)    /* [7]      Enable comparator */
#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #define `$INSTANCE_NAME`_CONFIG_DSI_BYPASS_SHIFT    (16u)   /* [16]   Bypass comparator output synchronization for DSI output  */
    #define `$INSTANCE_NAME`_CONFIG_DSI_LEVEL_SHIFT     (17u)   /* [17]   Comparator DSI (trigger) out level: 0-pulse, 1-level  */
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */

#define `$INSTANCE_NAME`_CONFIG_SPEED_MODE_MASK     (((uint32) 0x03u << `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT) << \
                                                    `$INSTANCE_NAME`_CONFIG_REG_SHIFT)

#define `$INSTANCE_NAME`_CONFIG_HYST                (((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_HYST_SHIFT) << \
                                                    `$INSTANCE_NAME`_CONFIG_REG_SHIFT)

#define `$INSTANCE_NAME`_CONFIG_INTR_MASK           (((uint32) 0x03u << `$INSTANCE_NAME`_CONFIG_INTR_SHIFT) << \
                                                    `$INSTANCE_NAME`_CONFIG_REG_SHIFT)

#define `$INSTANCE_NAME`_CONFIG_OUT                 (((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_OUT_SHIFT) << \
                                                    `$INSTANCE_NAME`_CONFIG_REG_SHIFT)

#define `$INSTANCE_NAME`_CONFIG_EN                  (((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_EN_SHIFT) << \
                                                    `$INSTANCE_NAME`_CONFIG_REG_SHIFT)
#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #define `$INSTANCE_NAME`_CONFIG_DSI_BYPASS          (((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_DSI_BYPASS_SHIFT) << \
                                                        (`$INSTANCE_NAME`_CONFIG_REG_SHIFT/2))

    #define `$INSTANCE_NAME`_CONFIG_DSI_LEVEL           (((uint32) 0x01u << `$INSTANCE_NAME`_CONFIG_DSI_LEVEL_SHIFT) << \
                                                        (`$INSTANCE_NAME`_CONFIG_REG_SHIFT/2))
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/* `$INSTANCE_NAME``$INSTANCE_NAME`_DFT_REG */
#define `$INSTANCE_NAME`_DFT_CAL_EN_SHIFT    (0u)    /* [0] Calibration enable */

#define `$INSTANCE_NAME`_DFT_CAL_EN          ((uint32) 0x01u << `$INSTANCE_NAME`_DFT_CAL_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define `$INSTANCE_NAME`_GET_CONFIG_SPEED_MODE(mode)    ((uint32) ((((uint32) (mode) << `$INSTANCE_NAME`_CONFIG_SPEED_MODE_SHIFT) << \
                                                            `$INSTANCE_NAME`_CONFIG_REG_SHIFT) & \
                                                            `$INSTANCE_NAME`_CONFIG_SPEED_MODE_MASK))

#define `$INSTANCE_NAME`_GET_CONFIG_HYST(hysteresis)    ((0u != (hysteresis)) ? (`$INSTANCE_NAME`_CONFIG_HYST) : (0u))

#define `$INSTANCE_NAME`_GET_CONFIG_INTR(intType)   ((uint32) ((((uint32)(intType) << `$INSTANCE_NAME`_CONFIG_INTR_SHIFT) << \
                                                    `$INSTANCE_NAME`_CONFIG_REG_SHIFT) & \
                                                    `$INSTANCE_NAME`_CONFIG_INTR_MASK))
#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #define `$INSTANCE_NAME`_GET_CONFIG_DSI_BYPASS(bypass)  ((0u != ((bypass) & `$INSTANCE_NAME`_OUT_DIRECT)) ? \
                                                                    (`$INSTANCE_NAME`_CONFIG_DSI_BYPASS) : (0u))
   
    #define `$INSTANCE_NAME`_GET_CONFIG_DSI_LEVEL(level)    ((0u != ((level) & `$INSTANCE_NAME`_OUT_SYNC)) ? \
                                                                    (`$INSTANCE_NAME`_CONFIG_DSI_LEVEL) : (0u))
    
    #define `$INSTANCE_NAME`_GET_INTR_MASK(mask)            ((0u != (mask)) ? (`$INSTANCE_NAME`_INTR_MASK) : (0u))
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */

#if(`$INSTANCE_NAME`_CY_LPCOMP_V0)
    #define `$INSTANCE_NAME`_CONFIG_REG_DEFAULT (`$INSTANCE_NAME`_GET_CONFIG_SPEED_MODE(`$INSTANCE_NAME`_SPEED) |\
                                                 `$INSTANCE_NAME`_GET_CONFIG_HYST(`$INSTANCE_NAME`_HYSTERESIS))
#else
    #define `$INSTANCE_NAME`_CONFIG_REG_DEFAULT (`$INSTANCE_NAME`_GET_CONFIG_SPEED_MODE(`$INSTANCE_NAME`_SPEED) |\
                                                 `$INSTANCE_NAME`_GET_CONFIG_HYST(`$INSTANCE_NAME`_HYSTERESIS)  |\
                                                 `$INSTANCE_NAME`_GET_CONFIG_DSI_BYPASS(`$INSTANCE_NAME`_OUT_MODE) |\
                                                 `$INSTANCE_NAME`_GET_CONFIG_DSI_LEVEL(`$INSTANCE_NAME`_OUT_MODE))
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V0) */

#if(`$INSTANCE_NAME`_CY_LPCOMP_V2)
    #define `$INSTANCE_NAME`_INTR_MASK_REG_DEFAULT  (`$INSTANCE_NAME`_GET_INTR_MASK(`$INSTANCE_NAME`_INTERRUPT_EN))
#endif /* (`$INSTANCE_NAME`_CY_LPCOMP_V2) */


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define `$INSTANCE_NAME`_CONFIG_FILT_SHIFT          (3u)    
#define `$INSTANCE_NAME`_CONFIG_FILT                ((uint32)((uint32)((uint32)0x01u << \
                                                    `$INSTANCE_NAME`_CONFIG_FILT_SHIFT) << `$INSTANCE_NAME`_CONFIG_REG_SHIFT))

#define `$INSTANCE_NAME`_DIGITAL_FILTER             (`$DigitalFilter`u)

/* `$INSTANCE_NAME`_SetFilter() parameters */
#define `$INSTANCE_NAME`_FILT_DISABLE               (0x00u)
#define `$INSTANCE_NAME`_FILT_ENABLE                (0x01u)

/* `$INSTANCE_NAME`_SetSpeed() parameters */
#define `$INSTANCE_NAME`_MEDSPEED                   (`$INSTANCE_NAME`_MED_SPEED)
#define `$INSTANCE_NAME`_HIGHSPEED                  (`$INSTANCE_NAME`_HIGH_SPEED)
#define `$INSTANCE_NAME`_LOWSPEED                   (`$INSTANCE_NAME`_LOW_SPEED)

void    `$INSTANCE_NAME`_SetFilter(uint32 filter);

#endif    /* CY_COMPARATOR_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
