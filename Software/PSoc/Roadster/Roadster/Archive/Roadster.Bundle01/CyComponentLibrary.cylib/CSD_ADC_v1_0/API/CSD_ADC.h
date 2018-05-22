/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes, constants, registers,
* masks and shifts which are used in the CSD ADC component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_HEADER
#define `$INSTANCE_NAME`_HEADER


/***************************************
*       Includes
***************************************/
    
#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"
    
    
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
void `$INSTANCE_NAME`_Stop(void);

int32 `$INSTANCE_NAME`_CalibrateNoInput(void);
int32 `$INSTANCE_NAME`_StartConvert(void);
int32 `$INSTANCE_NAME`_IsEndConversion(int32 retMode);
int32 `$INSTANCE_NAME`_GetResult_mVolts(void);
int32 `$INSTANCE_NAME`_Read_mVolts(void);

void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);

/* power management API */
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*        Macros
***************************************/

#define `$INSTANCE_NAME`_ClearInterrupt() do{ \
            `$INSTANCE_NAME`_INTR_REG |= `$INSTANCE_NAME`_CSD_IRQ_MASK;}while(0)
            
#define `$INSTANCE_NAME`_SetInterrupt() do{ \
            `$INSTANCE_NAME`_INTR_SET_REG |= `$INSTANCE_NAME`_CSD_IRQ_MASK;}while(0)


/***************************************
*        Component Defines
***************************************/

/* -- Defines for `$INSTANCE_NAME`_IsEndConversion API -- */
            
#define `$INSTANCE_NAME`_RETURN_STATUS      (0L)
#define `$INSTANCE_NAME`_WAIT_FOR_RESULT    (1L)

#define `$INSTANCE_NAME`_CONV_IN_PROGRESS   (0L)
#define `$INSTANCE_NAME`_CONV_COMPLETE      (1L)
            
#define `$INSTANCE_NAME`_START_CONV_ERR     (0x7FFFFFFFL) 
#define `$INSTANCE_NAME`_START_CONV_OK      (0L)
            
/* -- Internal Defines -- */
            
#define `$INSTANCE_NAME`_CSD_NUMBER         `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_NUMBER
#define `$INSTANCE_NAME`_RESOLUTION         (`$Resolution`UL)
#define `$INSTANCE_NAME`_IDAC1_VALUE        (`$IDAC_Value`UL)
/* This option is changed via a hidden component parameter */
#if `$IDAC_HighRange` != 0
    #define `$INSTANCE_NAME`_IDAC_STEP      (2.4e-6)
    #define `$INSTANCE_NAME`_IDAC_STEP_NA   (2400L)
#else
    #define `$INSTANCE_NAME`_IDAC_STEP      (1.2e-6)
    #define `$INSTANCE_NAME`_IDAC_STEP_NA   (1200L)
#endif
#define `$INSTANCE_NAME`_VREF               (1.2)
#define `$INSTANCE_NAME`_VREF_MV            (1200L)


/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_CSD_ID_REG         (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_ID)
#define `$INSTANCE_NAME`_CONFIG_REG         (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_CONFIG)
#define `$INSTANCE_NAME`_IDAC_REG           (* (reg32*) `$INSTANCE_NAME`_Imod__CSD_IDAC)
#define `$INSTANCE_NAME`_COUNTER_REG        (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_COUNTER)
#define `$INSTANCE_NAME`_STATUS_REG         (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_STATUS)
#define `$INSTANCE_NAME`_INTR_REG           (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_INTR)
#define `$INSTANCE_NAME`_INTR_SET_REG       (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_INTR_SET)
#define `$INSTANCE_NAME`_PWM_REG            (* (reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_PWM)
#define `$INSTANCE_NAME`_TRIM_1_REG         (* (reg32*) `$INSTANCE_NAME`_Imod__CSD_TRIM1)
#define `$INSTANCE_NAME`_TRIM_2_REG         (* (reg32*) `$INSTANCE_NAME`_Imod__CSD_TRIM2)


/***************************************
*        Register Pointers
***************************************/

#define `$INSTANCE_NAME`_CSD_ID_PTR         ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_ID)
#define `$INSTANCE_NAME`_CONFIG_PTR         ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_CONFIG)
#define `$INSTANCE_NAME`_IDAC_PTR           ((reg32*) `$INSTANCE_NAME`_Imod__CSD_IDAC)
#define `$INSTANCE_NAME`_COUNTER_PTR        ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_COUNTER)
#define `$INSTANCE_NAME`_STATUS_PTR         ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_STATUS)
#define `$INSTANCE_NAME`_INTR_PTR           ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_INTR)
#define `$INSTANCE_NAME`_INTR_SET_PTR       ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_INTR_SET)
#define `$INSTANCE_NAME`_PWM_PTR            ((reg32*) `$INSTANCE_NAME`_cy_psoc4_csd_1__CSD_PWM)
#define `$INSTANCE_NAME`_TRIM_1_PTR         ((reg32*) `$INSTANCE_NAME`_Imod__CSD_TRIM1)
#define `$INSTANCE_NAME`_TRIM_2_PTR         ((reg32*) `$INSTANCE_NAME`_Imod__CSD_TRIM2)


/***************************************
*  Register Masks, Shifts and Constants
***************************************/

/***************************************
*    `$INSTANCE_NAME`_CSD_ID_REG 
***************************************/

#define `$INSTANCE_NAME`_ID_SHIFT               (0UL)
#define `$INSTANCE_NAME`_ID_MASK                (0x0000FFFFUL << `$INSTANCE_NAME`_ID_SHIFT)

#define `$INSTANCE_NAME`_REVISION_SHIFT         (16UL)
#define `$INSTANCE_NAME`_REVISION_MASK          (0x0000FFFFUL << `$INSTANCE_NAME`_REVISION_SHIFT)


/***************************************
*    `$INSTANCE_NAME`_CONFIG_REG 
***************************************/

#define `$INSTANCE_NAME`_BYPASS_SEL_SHIFT       (2UL)
#define `$INSTANCE_NAME`_BYPASS_SEL_MASK        (0x00000001UL << `$INSTANCE_NAME`_BYPASS_SEL_SHIFT)
    #define `$INSTANCE_NAME`_DIV2_OR_PRS        (0UL)
    #define `$INSTANCE_NAME`_DIRECT             (1UL)

#define `$INSTANCE_NAME`_FILTER_ENABLE_SHIFT    (3UL)
#define `$INSTANCE_NAME`_FILTER_ENABLE_MASK     (0x00000001UL << `$INSTANCE_NAME`_FILTER_ENABLE_SHIFT)
    #define `$INSTANCE_NAME`_FILTER_DISABLE     (0UL)
    #define `$INSTANCE_NAME`_FILTER_ENABLE      (1UL)

#define `$INSTANCE_NAME`_PRS_CLEAR_SHIFT        (5UL)
#define `$INSTANCE_NAME`_PRS_CLEAR_MASK         (0x00000001UL << `$INSTANCE_NAME`_PRS_CLEAR_SHIFT)
#define `$INSTANCE_NAME`_PRS_CLEAR              (1UL)

#define `$INSTANCE_NAME`_PRS_SELECT_SHIFT       (6UL)
#define `$INSTANCE_NAME`_PRS_SELECT_MASK        (0x00000001UL << `$INSTANCE_NAME`_PRS_SELECT_SHIFT)
    #define `$INSTANCE_NAME`_DIV_BY_2           (0UL)
    #define `$INSTANCE_NAME`_PRS                (1UL)

#define `$INSTANCE_NAME`_PRS_12_8_SHIFT         (7UL)
#define `$INSTANCE_NAME`_PRS_12_8_MASK          (0x00000001UL << `$INSTANCE_NAME`_PRS_12_8_SHIFT)
    #define `$INSTANCE_NAME`_PRS_8              (0UL)
    #define `$INSTANCE_NAME`_PRS_12             (1UL)

#define `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT     (9UL)
#define `$INSTANCE_NAME`_SHIELD_DELAY_MASK      (0x00000003UL << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT)
    #define `$INSTANCE_NAME`_DELAY_OFF          (0UL)
    #define `$INSTANCE_NAME`_DELAY_50_NS        (2UL)
    #define `$INSTANCE_NAME`_DELAY_10_NS        (3UL)

#define `$INSTANCE_NAME`_SENSE_COMP_BW_SHIFT    (11UL)
#define `$INSTANCE_NAME`_SENSE_COMP_BW_MASK     (0x00000001UL << `$INSTANCE_NAME`_SENSE_COMP_BW_SHIFT)
    #define `$INSTANCE_NAME`_COMP_BW_LOW        (0UL)
    #define `$INSTANCE_NAME`_COMP_BW_HIGH       (1UL)

#define `$INSTANCE_NAME`_SENSE_EN_SHIFT         (12UL)
#define `$INSTANCE_NAME`_SENSE_EN_MASK          (0x00000001UL << `$INSTANCE_NAME`_SENSE_EN_SHIFT)
    #define `$INSTANCE_NAME`_SENSE_DISABLE      (0UL)
    #define `$INSTANCE_NAME`_SENSE_ENABLE       (1UL)

#define `$INSTANCE_NAME`_REFBUF_EN_SHIFT        (13UL)
#define `$INSTANCE_NAME`_REFBUF_EN_MASK         (0x00000001UL << `$INSTANCE_NAME`_REFBUF_EN_SHIFT)
    #define `$INSTANCE_NAME`_REFBUF_DISABLE     (0UL)
    #define `$INSTANCE_NAME`_REFBUF_ENABLE      (1UL)

#define `$INSTANCE_NAME`_COMP_MODE_SHIFT        (14UL)
#define `$INSTANCE_NAME`_COMP_MODE_MASK         (0x00000001UL << `$INSTANCE_NAME`_COMP_MODE_SHIFT)
    #define `$INSTANCE_NAME`_CHARGE_VIA_BUFFER  (0UL)
    #define `$INSTANCE_NAME`_CHARGE_VIA_IO      (1UL)

#define `$INSTANCE_NAME`_COMP_PIN_SHIFT         (15UL)
#define `$INSTANCE_NAME`_COMP_PIN_MASK          (0x00000001UL << `$INSTANCE_NAME`_COMP_PIN_SHIFT)
    #define `$INSTANCE_NAME`_CMOD_P0_4          (0UL)
    #define `$INSTANCE_NAME`_CTANK_P0_2         (1UL)

#define `$INSTANCE_NAME`_POLARITY_1_SHIFT       (16UL)
#define `$INSTANCE_NAME`_POLARITY_1_MASK        (0x00000001UL << `$INSTANCE_NAME`_POLARITY_1_SHIFT)
    #define `$INSTANCE_NAME`_IDAC1_SOURCE       (0UL)
    #define `$INSTANCE_NAME`_IDAC1_SINK         (1UL)

#define `$INSTANCE_NAME`_POLARITY_2_SHIFT       (17UL)
#define `$INSTANCE_NAME`_POLARITY_2_MASK        (0x00000001UL << `$INSTANCE_NAME`_POLARITY_2_SHIFT)
    #define `$INSTANCE_NAME`_IDAC2_SOURCE       (0UL)
    #define `$INSTANCE_NAME`_IDAC2_SINK         (1UL)

#define `$INSTANCE_NAME`_SENSE_COMP_EN_SHIFT    (19UL)
#define `$INSTANCE_NAME`_SENSE_COMP_EN_MASK     (0x00000001UL << `$INSTANCE_NAME`_SENSE_COMP_EN_SHIFT)
    #define `$INSTANCE_NAME`_SENSE_COMP_DISABLE (0UL)
    #define `$INSTANCE_NAME`_SENSE_COMP_ENABLE  (1UL)

#define `$INSTANCE_NAME`_REFBUF_OUTSEL_SHIFT    (21UL)
#define `$INSTANCE_NAME`_REFBUF_OUTSEL_MASK     (0x00000001UL << `$INSTANCE_NAME`_REFBUF_OUTSEL_SHIFT)
    #define `$INSTANCE_NAME`_REFBUF_TO_AMUXA    (0UL)
    #define `$INSTANCE_NAME`_REFBUF_TO_AMUXB    (1UL)

#define `$INSTANCE_NAME`_SENSE_INSEL_SHIFT      (22UL)
#define `$INSTANCE_NAME`_SENSE_INSEL_MASK       (0x00000001UL << `$INSTANCE_NAME`_SENSE_INSEL_SHIFT)
    #define `$INSTANCE_NAME`_SENSE_P0_4         (0UL)
    #define `$INSTANCE_NAME`_SENSE_AMUXA        (1UL)

#define `$INSTANCE_NAME`_REFBUF_DRIVE_SHIFT     (23UL)
#define `$INSTANCE_NAME`_REFBUF_DRIVE_MASK      (0x00000003UL << `$INSTANCE_NAME`_REFBUF_DRIVE_SHIFT)
    #define `$INSTANCE_NAME`_REFBUF_OFF         (0UL)
    #define `$INSTANCE_NAME`_REFBUF_LOW         (1UL)
    #define `$INSTANCE_NAME`_REFBUF_MED         (2UL)
    #define `$INSTANCE_NAME`_REFBUF_HIGH        (3UL)

#define `$INSTANCE_NAME`_DDFTSEL_SHIFT          (26UL)
#define `$INSTANCE_NAME`_DDFTSEL_MASK           (0x00000007UL << `$INSTANCE_NAME`_DDFTSEL_SHIFT)
    #define `$INSTANCE_NAME`_DDFTSEL_NORMAL     (0UL)
    #define `$INSTANCE_NAME`_DDFTSEL_CSD_SENSE  (1UL)
    #define `$INSTANCE_NAME`_DDFTSEL_CSD_SHIELD (2UL)
    #define `$INSTANCE_NAME`_DDFTSEL_CLK_SAMPLE (3UL)
    #define `$INSTANCE_NAME`_DDFTSEL_COMP_OUT   (4UL)

#define `$INSTANCE_NAME`_ADFTSEL_SHIFT          (29UL)
#define `$INSTANCE_NAME`_ADFTSEL_MASK           (0x00000001UL << `$INSTANCE_NAME`_ADFTSEL_SHIFT)
    #define `$INSTANCE_NAME`_ADFTSEL_NORMAL     (0UL)
    #define `$INSTANCE_NAME`_ADFTSEL_VDAC       (1UL)

#define `$INSTANCE_NAME`_CSD_ENABLE_SHIFT       (31UL)
#define `$INSTANCE_NAME`_CSD_ENABLE_MASK        (0x00000001UL << `$INSTANCE_NAME`_CSD_ENABLE_SHIFT)
    #define `$INSTANCE_NAME`_CSD_DISABLE        (0UL)
    #define `$INSTANCE_NAME`_CSD_ENABLE         (1UL)


/***************************************
*    `$INSTANCE_NAME`_IDAC_REG
***************************************/

#define `$INSTANCE_NAME`_IDAC1_VALUE_SHIFT      (0UL)
#define `$INSTANCE_NAME`_IDAC1_VALUE_MASK       (0x000000FFUL << `$INSTANCE_NAME`_IDAC1_VALUE_SHIFT)

#define `$INSTANCE_NAME`_IDAC1_MODE_SHIFT       (8UL)
#define `$INSTANCE_NAME`_IDAC1_MODE_MASK        (0x00000003UL << `$INSTANCE_NAME`_IDAC1_MODE_SHIFT)
    #define `$INSTANCE_NAME`_IDAC1_OFF          (0UL)
    #define `$INSTANCE_NAME`_IDAC1_COMPENSATION (1UL)
    #define `$INSTANCE_NAME`_IDAC1_MODULATED    (2UL)
    #define `$INSTANCE_NAME`_IDAC1_GENERAL      (3UL)

#define `$INSTANCE_NAME`_IDAC1_RANGE_SHIFT      (10UL)
#define `$INSTANCE_NAME`_IDAC1_RANGE_MASK       (0x00000001UL << `$INSTANCE_NAME`_IDAC1_RANGE_SHIFT)
    #define `$INSTANCE_NAME`_IDAC1_306_UA_RANGE (0UL)
    #define `$INSTANCE_NAME`_IDAC1_612_UA_RANGE (1UL)

#define `$INSTANCE_NAME`_IDAC1_POL_MIR_SHIFT    (12UL)
#define `$INSTANCE_NAME`_IDAC1_POL_MIR_MASK     (0x00000001UL << `$INSTANCE_NAME`_IDAC1_POL_MIR_SHIFT)
    /* #define `$INSTANCE_NAME`_IDAC1_SOURCE       (0UL) */
    /* #define `$INSTANCE_NAME`_IDAC1_SINK         (1UL) */

#define `$INSTANCE_NAME`_IDAC2_VALUE_SHIFT      (16UL)
#define `$INSTANCE_NAME`_IDAC2_VALUE_MASK       (0x0000007FUL << `$INSTANCE_NAME`_IDAC2_VALUE_SHIFT)

#define `$INSTANCE_NAME`_IDAC2_MODE_SHIFT       (24UL)
#define `$INSTANCE_NAME`_IDAC2_MODE_MASK        (0x00000003UL << `$INSTANCE_NAME`_IDAC2_MODE_SHIFT)
    #define `$INSTANCE_NAME`_IDAC2_OFF          (0UL)
    #define `$INSTANCE_NAME`_IDAC2_COMPENSATION (1UL)
    #define `$INSTANCE_NAME`_IDAC2_MODULATED    (2UL)
    #define `$INSTANCE_NAME`_IDAC2_GENERAL      (3UL)

#define `$INSTANCE_NAME`_IDAC2_RANGE_SHIFT      (26UL)
#define `$INSTANCE_NAME`_IDAC2_RANGE_MASK       (0x00000001UL << `$INSTANCE_NAME`_IDAC2_RANGE_SHIFT)
    #define `$INSTANCE_NAME`_IDAC2_152_UA_RANGE (0UL)
    #define `$INSTANCE_NAME`_IDAC2_304_UA_RANGE (1UL)

#define `$INSTANCE_NAME`_IDAC2_POL_MIR_SHIFT    (28UL)
#define `$INSTANCE_NAME`_IDAC2_POL_MIR_MASK     (0x00000001UL << `$INSTANCE_NAME`_IDAC2_POL_MIR_SHIFT)
    /* #define `$INSTANCE_NAME`_IDAC2_SOURCE       (0UL) */
    /* #define `$INSTANCE_NAME`_IDAC2_SINK         (1UL) */

#define `$INSTANCE_NAME`_FEEDBACK_MODE_SHIFT    (30UL)
#define `$INSTANCE_NAME`_FEEDBACK_MODE_MASK     (0x00000001UL << `$INSTANCE_NAME`_FEEDBACK_MODE_SHIFT)
    #define `$INSTANCE_NAME`_FLOP_MODE          (0UL)
    #define `$INSTANCE_NAME`_COMP_MODE          (1UL)


/***************************************
*    `$INSTANCE_NAME`_COUNTER_REG
***************************************/

#define `$INSTANCE_NAME`_COUNTER_SHIFT          (0UL)
#define `$INSTANCE_NAME`_COUNTER_MASK           (0x0000FFFFUL << `$INSTANCE_NAME`_COUNTER_SHIFT)

#define `$INSTANCE_NAME`_PERIOD_SHIFT           (16UL)
#define `$INSTANCE_NAME`_PERIOD_MASK            (0x0000FFFFUL << `$INSTANCE_NAME`_PERIOD_SHIFT)


/***************************************
*     `$INSTANCE_NAME`_STATUS_REG
***************************************/

#define `$INSTANCE_NAME`_CSD_CHARGE_SHIFT       (0UL)
#define `$INSTANCE_NAME`_CSD_CHARGE_MASK        (0x00000001UL << `$INSTANCE_NAME`_CSD_CHARGE_SHIFT)

#define `$INSTANCE_NAME`_CSD_SENSE_SHIFT        (1UL)
#define `$INSTANCE_NAME`_CSD_SENSE_MASK         (0x00000001UL << `$INSTANCE_NAME`_CSD_SENSE_SHIFT)

#define `$INSTANCE_NAME`_REF_COMP_OUT_SHIFT     (2UL)
#define `$INSTANCE_NAME`_REF_COMP_OUT_MASK      (0x00000001UL << `$INSTANCE_NAME`_COMP_OUT_SHIFT)

#define `$INSTANCE_NAME`_SAMPLE_COMP_OUT_SHIFT  (3UL)
#define `$INSTANCE_NAME`_SAMPLE_COMP_OUT_MASK   (0x00000001UL << `$INSTANCE_NAME`_SAMPLE_COMP_OUT_SHIFT)


/***************************************
*     `$INSTANCE_NAME`_INTR_REG 
***************************************/

#define `$INSTANCE_NAME`_CSD_IRQ_SHIFT          (0UL)
#define `$INSTANCE_NAME`_CSD_IRQ_MASK           (0x00000001UL << `$INSTANCE_NAME`_CSD_IRQ_SHIFT)


/***************************************
*    `$INSTANCE_NAME`_INTR_SET_REG
***************************************/

/* #define `$INSTANCE_NAME`_CSD_IRQ_SHIFT          (0UL) */
/* #define `$INSTANCE_NAME`_CSD_IRQ_MASK           (1UL << `$INSTANCE_NAME`_CSD_IRQ_SHIFT) */


/***************************************
*    `$INSTANCE_NAME`_PWM_REG
***************************************/

#define `$INSTANCE_NAME`_PWM_COUNT_SHIFT        (0UL)
#define `$INSTANCE_NAME`_PWM_COUNT_MASK         (0x0000000FUL << `$INSTANCE_NAME`_PWM_COUNT_SHIFT)

#define `$INSTANCE_NAME`_PWM_SEL_SHIFT          (4UL)
#define `$INSTANCE_NAME`_PWM_SEL_MASK           (0x00000003UL << `$INSTANCE_NAME`_PWM_SEL_SHIFT)
    #define `$INSTANCE_NAME`_PWM_OFF            (0UL)
    #define `$INSTANCE_NAME`_PWM_FIXED_HIGH     (2UL)
    #define `$INSTANCE_NAME`_PWM_FIXED_LOW      (3UL)


/***************************************
*     `$INSTANCE_NAME`_TRIM1_REG
***************************************/

#define `$INSTANCE_NAME`_IDAC1_SRC_TRIM_SHIFT   (0UL)
#define `$INSTANCE_NAME`_IDAC1_SRC_TRIM_MASK    (0x0000000FUL << `$INSTANCE_NAME`_IDAC1_SRC_TRIM_SHIFT)

#define `$INSTANCE_NAME`_IDAC2_SRC_TRIM_SHIFT   (4UL)
#define `$INSTANCE_NAME`_IDAC2_SRC_TRIM_MASK    (0x0000000FUL << `$INSTANCE_NAME`_IDAC2_SRC_TRIM_SHIFT)


/***************************************
*     `$INSTANCE_NAME`_TRIM2_REG
***************************************/

#define `$INSTANCE_NAME`_IDAC1_SNK_TRIM_SHIFT   (0UL)
#define `$INSTANCE_NAME`_IDAC1_SNK_TRIM_MASK    (0x0000000FUL << `$INSTANCE_NAME`_IDAC1_SNK_TRIM_SHIFT)

#define `$INSTANCE_NAME`_IDAC2_SNK_TRIM_SHIFT   (4UL)
#define `$INSTANCE_NAME`_IDAC2_SNK_TRIM_MASK    (0x0000000FUL << `$INSTANCE_NAME`_IDAC2_SNK_TRIM_SHIFT)

/***************************************
* `$INSTANCE_NAME`_IDAC_TRIM_FLASH_REG
***************************************/

#define `$INSTANCE_NAME`_IDAC_TRIM_SRC_FLASH_REG    ((uint32) (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD))
#define `$INSTANCE_NAME`_IDAC_TRIM_SNK_FLASH_REG    ((uint32) (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD))

#endif

/* [] END OF FILE */
