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
    

/* Configuration structure */
`=$CY_CONST_CONFIG ? "const " : ""`stc_lcd_config_t `$INSTANCE_NAME`_Config =
{
    /* bTimerMod */             `=$bTimerMod ? "TRUE" : "FALSE"`,
    /* enDivMode */             `=GetNameForEnum("en_lcd_div_mode_t", $enDivMode)`,
    /* enDispMode */            `=GetNameForEnum("en_lcd_disp_mode_t", $enDispMode)`,
    /* enDivResVal */           `=GetNameForEnum("en_lcd_div_res_val_t", $enDivResVal)`,
    /* en8ComBias */            `=GetNameForEnum("en_lcd_8com_bias_t", $en8ComBias)`,
    /* bEnDispRevs */           `=$bTimerMod ? "TRUE" : "FALSE"`,
    /* bEnBlankDisp */          `=$bTimerMod ? "TRUE" : "FALSE"`,
    /* enInputIoMode */         `=GetNameForEnum("en_lcd_input_io_mode_t", $enInputIoMode)`,
    {/* stcClkConf */
        /* enSrcClk */          `=GetNameForEnum("en_lcd_src_clk_sel_t", $enSrcClk)`,
        /* u32DivVal */         `$u32DivVal`u
    },
    {/* stcVvSel */
        {
            /* VE0 */           (`=$VE0 ? "1u" : "0u"` << 0) | \
            /* VE1 */           (`=$VE1 ? "1u" : "0u"` << 1) | \
            /* VE2 */           (`=$VE2 ? "1u" : "0u"` << 2) | \
            /* VE3 */           (`=$VE3 ? "1u" : "0u"` << 3) | \
            /* VE4 */           (`=$VE4 ? "1u" : "0u"` << 4) | \
            /* RESERVED0 */     (0u << 5)
        }        
    },
    {/* stcSegSel1 */
        {
            /* SEG00 */         (`=$SEG00 ? "1u" : "0u"` << 0) | \
            /* SEG01 */         (`=$SEG01 ? "1u" : "0u"` << 1) | \
            /* SEG02 */         (`=$SEG02 ? "1u" : "0u"` << 2) | \
            /* SEG03 */         (`=$SEG03 ? "1u" : "0u"` << 3) | \
            /* SEG04 */         (`=$SEG04 ? "1u" : "0u"` << 4) | \
            /* SEG05 */         (`=$SEG05 ? "1u" : "0u"` << 5) | \
            /* SEG06 */         (`=$SEG06 ? "1u" : "0u"` << 6) | \
            /* SEG07 */         (`=$SEG07 ? "1u" : "0u"` << 7) | \
            /* SEG08 */         (`=$SEG08 ? "1u" : "0u"` << 8) | \
            /* SEG09 */         (`=$SEG09 ? "1u" : "0u"` << 9) | \
            /* SEG10 */         (`=$SEG10 ? "1u" : "0u"` << 10) | \
            /* SEG11 */         (`=$SEG11 ? "1u" : "0u"` << 11) | \
            /* SEG12 */         (`=$SEG12 ? "1u" : "0u"` << 12) | \
            /* SEG13 */         (`=$SEG13 ? "1u" : "0u"` << 13) | \
            /* SEG14 */         (`=$SEG14 ? "1u" : "0u"` << 14) | \
            /* SEG15 */         (`=$SEG15 ? "1u" : "0u"` << 15) | \
            /* SEG16 */         (`=$SEG16 ? "1u" : "0u"` << 16) | \
            /* SEG17 */         (`=$SEG17 ? "1u" : "0u"` << 17) | \
            /* SEG18 */         (`=$SEG18 ? "1u" : "0u"` << 18) | \
            /* SEG19 */         (`=$SEG19 ? "1u" : "0u"` << 19) | \
            /* SEG20 */         (`=$SEG20 ? "1u" : "0u"` << 20) | \
            /* SEG21 */         (`=$SEG21 ? "1u" : "0u"` << 21) | \
            /* SEG22 */         (`=$SEG22 ? "1u" : "0u"` << 22) | \
            /* SEG23 */         (`=$SEG23 ? "1u" : "0u"` << 23) | \
            /* SEG24 */         (`=$SEG24 ? "1u" : "0u"` << 24) | \
            /* SEG25 */         (`=$SEG25 ? "1u" : "0u"` << 25) | \
            /* SEG26 */         (`=$SEG26 ? "1u" : "0u"` << 26) | \
            /* SEG27 */         (`=$SEG27 ? "1u" : "0u"` << 27) | \
            /* SEG28 */         (`=$SEG28 ? "1u" : "0u"` << 28) | \
            /* SEG29 */         (`=$SEG29 ? "1u" : "0u"` << 29) | \
            /* SEG30 */         (`=$SEG30 ? "1u" : "0u"` << 30) | \
            /* SEG31 */         (`=$SEG31 ? "1u" : "0u"` << 31)
        }
    },
    {/* stcSegSel2 */
        {
            /* SEG32 */         (`=$SEG32 ? "1u" : "0u"` << 0) | \
            /* SEG33 */         (`=$SEG33 ? "1u" : "0u"` << 1) | \
            /* SEG34 */         (`=$SEG34 ? "1u" : "0u"` << 2) | \
            /* SEG35 */         (`=$SEG35 ? "1u" : "0u"` << 3) | \
            /* SEG36 */         (`=$SEG36 ? "1u" : "0u"` << 4) | \
            /* SEG37 */         (`=$SEG37 ? "1u" : "0u"` << 5) | \
            /* SEG38 */         (`=$SEG38 ? "1u" : "0u"` << 6) | \
            /* SEG39 */         (`=$SEG39 ? "1u" : "0u"` << 7) | \
            /* RESERVED0 */     (0u << 8)
        }
    },
    {/* stcComSel */
        {
            /* COM0 */          (`=$COM0 ? "1u" : "0u"` << 0) | \
            /* COM1 */          (`=$COM1 ? "1u" : "0u"` << 1) | \
            /* COM2 */          (`=$COM2 ? "1u" : "0u"` << 2) | \
            /* COM3 */          (`=$COM3 ? "1u" : "0u"` << 3) | \
            /* COM4 */          (`= ($enDispMode == 4) ? (($COM4 == 1) ? "1u" :"0u") : (($SEG40 == 1) ? "1u" :"0u")` << 4) | \
            /* COM5 */          (`= ($enDispMode == 4) ? (($COM5 == 1) ? "1u" :"0u") : (($SEG41 == 1) ? "1u" :"0u")` << 5) | \
            /* COM6 */          (`= ($enDispMode == 4) ? (($COM6 == 1) ? "1u" :"0u") : (($SEG42 == 1) ? "1u" :"0u")` << 6) | \
            /* COM7 */          (`= ($enDispMode == 4) ? (($COM7 == 1) ? "1u" :"0u") : (($SEG43 == 1) ? "1u" :"0u")` << 7)
        }
    },
#if (PDL_MCU_CORE == PDL_FM0P_CORE)
    /* bEnBooster */            `=$bEnBooster ? "TRUE" : "FALSE"`,
    {/* stcBooster */
        {
            /* BSTOPT */        (`=$BSTOPT ? "1u" : "0u"` << 0) | \
            /* BSTPD */         (`=$BSTPD ? "1u" : "0u"` << 1) | \
            /* RESERVED0 */     (0u << 2) | \
            /* CENSEL */        (`=$CENSEL ? "1u" : "0u"` << 3) | \
            /* RESERVED1 */     (0u << 4) | \
            /* BTRF */          (`$BTRF`u << 8) | \
            /* BTRC */          (`$BTRC`u << 12)
        }
    },
#endif

#if (PDL_INTERRUPT_ENABLE_LCD == PDL_ON)
    /* bIrqEn */                `=$bIrqEn ? "TRUE" : "FALSE"`,
    /* pfnIrqCb */              `=($pfnIrqCb eq "") || !$bIrqEn ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnIrqCb`, /* User-supplied callback function */
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`
#endif    
};

/* [] END OF FILE */
