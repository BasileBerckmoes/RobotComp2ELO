/*******************************************************************************
* \file `$INSTANCE_NAME`_config.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable definitions for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_config.h"

/* Interrupt enable structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_qprc_irq_en_t `$INSTANCE_NAME`_IrqEn =
{
    /* bQprcPcOfUfZeroIrq */    `=$bQprcPcOfUfZeroIrq ? "TRUE" : "FALSE"`,
    /* bQprcPcMatchIrq */       `=$bQprcPcMatchIrq ? "TRUE" : "FALSE"`,
    /* bQprcPcRcMatchIrq */     `=$bQprcPcRcMatchIrq ? "TRUE" : "FALSE"`,
    /* bQprcPcMatchRcMatchIrq */`=$bQprcPcMatchRcMatchIrq ? "TRUE" : "FALSE"`,
    /* bQprcPcCountInvertIrq */ `=$bQprcPcCountInvertIrq ? "TRUE" : "FALSE"`,
    /* bQprcRcOutrangeIrq */    `=$bQprcRcOutrangeIrq ? "TRUE" : "FALSE"`,
};

/* Interrupt callback functions structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_qprc_irq_cb_t `$INSTANCE_NAME`_IrqCb =
{
    /* pfnPcOfUfZeroIrqCb */    `=($pfnPcOfUfZeroIrqCb eq "") || !$bQprcPcOfUfZeroIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPcOfUfZeroIrqCb`, /* User-supplied callback function */
    /* pfnPcMatchIrqCb */       `=($pfnPcMatchIrqCb eq "") || !$bQprcPcMatchIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPcMatchIrqCb`, /* User-supplied callback function */
    /* pfnPcRcMatchIrqCb */     `=($pfnPcRcMatchIrqCb eq "") || !$bQprcPcRcMatchIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPcRcMatchIrqCb`, /* User-supplied callback function */
    /* pfnPcMatchRcMatchIrqCb */`=($pfnPcMatchRcMatchIrqCb eq "") || !$bQprcPcMatchRcMatchIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPcMatchRcMatchIrqCb`, /* User-supplied callback function */
    /* pfnPcCountInvertIrqCb */ `=($pfnPcCountInvertIrqCb eq "") || !$bQprcPcCountInvertIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnPcCountInvertIrqCb`, /* User-supplied callback function */
    /* pfnRcOutrangeIrqCb */    `=($pfnRcOutrangeIrqCb eq "") || !$bQprcRcOutrangeIrq ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnRcOutrangeIrqCb`, /* User-supplied callback function */
};

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_qprc_config_t `$INSTANCE_NAME`_Config =
{
    /* bSwapAinBin */       `=$bSwapAinBin ? "TRUE" : "FALSE"`,
    /* enCompareMode */     `=GetNameForEnum("en_qprc_compmode_t",$enCompareMode)`,
    /* enZinEdge */         `=GetNameForEnum("en_qprc_zinedge_t",$enZinEdge)`, 
    /* enBinEdge */         `=GetNameForEnum("en_qprc_binedge_t",$enBinEdge)`, 
    /* enAinEdge */         `=GetNameForEnum("en_qprc_ainedge_t",$enAinEdge)`,      
    /* enPcResetMask */     `=GetNameForEnum("en_qprc_pcresetmask_t",$enPcResetMask)`, 
    /* b8KValue */          `=$b8KValue ? "TRUE" : "FALSE"`,
#if (PDL_MCU_CORE == PDL_FM4_CORE) || (PDL_MCU_CORE == PDL_FM0P_CORE)
    {/* stcAinFilter */
        `=$bAinInputMask ? "TRUE" : "FALSE"`,
        `=$bAinInputInvert ? "TRUE" : "FALSE"`,
        `=GetNameForEnum("en_qprc_filter_width_t",$enAinWidth)`,
    },
    {/* stcBinFilter */
        `=$bBinInputMask ? "TRUE" : "FALSE"`,
        `=$bBinInputInvert ? "TRUE" : "FALSE"`,
        `=GetNameForEnum("en_qprc_filter_width_t",$enBinWidth)`,
    },
    {/* stcCinFilter */
        `=$bCinInputMask ? "TRUE" : "FALSE"`,
        `=$bCinInputInvert ? "TRUE" : "FALSE"`,
        `=GetNameForEnum("en_qprc_filter_width_t",$enCinWidth)`,
    },
#endif
    /* pstcIrqEn */         `=$CY_CONST_CONFIG ? "(stc_qprc_irq_en_t *)" : ""`&`$INSTANCE_NAME`_IrqEn,
    /* pstcIrqCb */         `=$CY_CONST_CONFIG ? "(stc_qprc_irq_cb_t *)" : ""`&`$INSTANCE_NAME`_IrqCb,
    /* bTouchNvic */        `=$bTouchNvic  ? "TRUE" : "FALSE"`  
    
};

/* [] END OF FILE */
