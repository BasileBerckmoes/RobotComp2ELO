/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the IDAC_P4
*  component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_IDAC_`$INSTANCE_NAME`_H)
#define CY_IDAC_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Internal Type defines
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;


extern uint32 `$INSTANCE_NAME`_initVar;

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* IDAC polarity setting constants */
`#cy_declare_enum PolarityType`

/* IDAC range setting constants */
`#cy_declare_enum IDACRangeType`

/* IDAC polarity setting definitions */
#define `$INSTANCE_NAME`_MODE_SOURCE    (`$INSTANCE_NAME`__SOURCE)
#define `$INSTANCE_NAME`_MODE_SINK      (`$INSTANCE_NAME`__SINK)

/* IDAC RANGE setting definitions */
#define `$INSTANCE_NAME`_MODE_LOWRANGE  (`$INSTANCE_NAME`__LOWRANGE)
#define `$INSTANCE_NAME`_MODE_HIGHRANGE (`$INSTANCE_NAME`__HIGHRANGE)

/***************************************
*   Conditional Compilation Parameters
****************************************/

#define `$INSTANCE_NAME`_IDAC_RESOLUTION    (`$Resolution`u)
#define `$INSTANCE_NAME`_IDAC_RANGE         (`$IDACRange`u)
#define `$INSTANCE_NAME`_IDAC_POLARITY      (`$Polarity`u)


/***************************************
*    Initial Parameter Constants
***************************************/
#define `$INSTANCE_NAME`_IDAC_INIT_VALUE    (`$IDACValue`u)




/***************************************
*        Function Prototypes
***************************************/

void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetValue(uint32  value);
void `$INSTANCE_NAME`_SaveConfig(void);
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_RestoreConfig(void);
void `$INSTANCE_NAME`_Wakeup(void);


/***************************************
*            API Constants
***************************************/

#define `$INSTANCE_NAME`_IDAC_EN_MODE           (3u)
#define `$INSTANCE_NAME`_IDAC_CSD_EN            (1u)
#define `$INSTANCE_NAME`_IDAC_CSD_EN_POSITION   (31u)

#define `$INSTANCE_NAME`_IDAC_VALUE_POSITION    (`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC_SHIFT)

#define `$INSTANCE_NAME`_IDAC_MODE_SHIFT        (8u)
#define `$INSTANCE_NAME`_IDAC_MODE_POSITION     ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC_SHIFT +\
                                                 `$INSTANCE_NAME`_IDAC_MODE_SHIFT)

#define `$INSTANCE_NAME`_IDAC_RANGE_SHIFT       (10u)
#define `$INSTANCE_NAME`_IDAC_RANGE_POSITION    ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC_SHIFT +\
                                                 `$INSTANCE_NAME`_IDAC_RANGE_SHIFT)

#define `$INSTANCE_NAME`_IDAC_POLARITY_POSITION ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__POLARITY_SHIFT)

#define `$INSTANCE_NAME`_IDAC_TRIM1_POSITION    ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_TRIM1_SHIFT)
#define `$INSTANCE_NAME`_IDAC_TRIM2_POSITION    ((uint32)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_TRIM2_SHIFT)

#define `$INSTANCE_NAME`_IDAC_CDS_EN_MASK       (0x80000000u)

#if(`$INSTANCE_NAME`_IDAC_RESOLUTION == 8u)
  #define `$INSTANCE_NAME`_IDAC_VALUE_MASK      (0xFFu)
#else
  #define `$INSTANCE_NAME`_IDAC_VALUE_MASK      (0x7Fu)
#endif /* (`$INSTANCE_NAME`_IDAC_RESOLUTION == 8u) */

#define `$INSTANCE_NAME`_IDAC_MODE_MASK         (3u)
#define `$INSTANCE_NAME`_IDAC_RANGE_MASK        (1u)
#define `$INSTANCE_NAME`_IDAC_POLARITY_MASK     (1u)

#define `$INSTANCE_NAME`_CSD_IDAC_TRIM1_MASK    (0x0000000FuL << `$INSTANCE_NAME`_IDAC_TRIM1_POSITION)
#define `$INSTANCE_NAME`_CSD_IDAC_TRIM2_MASK    (0x0000000FuL << `$INSTANCE_NAME`_IDAC_TRIM2_POSITION)


/***************************************
*        Registers
***************************************/

#define `$INSTANCE_NAME`_IDAC_CONTROL_REG    (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC)
#define `$INSTANCE_NAME`_IDAC_CONTROL_PTR    ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_IDAC)

#define `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_REG    (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CONTROL)
#define `$INSTANCE_NAME`_IDAC_POLARITY_CONTROL_PTR    ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CONTROL)

#define `$INSTANCE_NAME`_CSD_TRIM1_REG       (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_TRIM1)
#define `$INSTANCE_NAME`_CSD_TRIM1_PTR       ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_TRIM1)

#define `$INSTANCE_NAME`_CSD_TRIM2_REG       (*(reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_TRIM2)
#define `$INSTANCE_NAME`_CSD_TRIM2_PTR       ( (reg32 *)`$INSTANCE_NAME`_cy_psoc4_idac__CSD_TRIM2)

#if (CY_PSOC4_4100M || CY_PSOC4_4200M)
    #if(`$INSTANCE_NAME`_cy_psoc4_idac__IDAC_NUMBER > 2u)
        #define `$INSTANCE_NAME`_SFLASH_TRIM1_REG       (*(reg8 *)CYREG_SFLASH_CSD1_TRIM1_HVIDAC)
        #define `$INSTANCE_NAME`_SFLASH_TRIM1_PTR       ( (reg8 *)CYREG_SFLASH_CSD1_TRIM1_HVIDAC)
        
        #define `$INSTANCE_NAME`_SFLASH_TRIM2_REG       (*(reg8 *)CYREG_SFLASH_CSD1_TRIM2_HVIDAC)
        #define `$INSTANCE_NAME`_SFLASH_TRIM2_PTR       ( (reg8 *)CYREG_SFLASH_CSD1_TRIM2_HVIDAC)
    #else
        #define `$INSTANCE_NAME`_SFLASH_TRIM1_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
        #define `$INSTANCE_NAME`_SFLASH_TRIM1_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
        
        #define `$INSTANCE_NAME`_SFLASH_TRIM2_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
        #define `$INSTANCE_NAME`_SFLASH_TRIM2_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
    #endif /* (`$INSTANCE_NAME`_cy_psoc4_idac__IDAC_NUMBER > 2u) */
#else
    #define `$INSTANCE_NAME`_SFLASH_TRIM1_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
    #define `$INSTANCE_NAME`_SFLASH_TRIM1_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM1_HVIDAC)
    
    #define `$INSTANCE_NAME`_SFLASH_TRIM2_REG       (*(reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
    #define `$INSTANCE_NAME`_SFLASH_TRIM2_PTR       ( (reg8 *)CYREG_SFLASH_CSD_TRIM2_HVIDAC)
#endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M) */

#endif /* CY_IDAC_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
