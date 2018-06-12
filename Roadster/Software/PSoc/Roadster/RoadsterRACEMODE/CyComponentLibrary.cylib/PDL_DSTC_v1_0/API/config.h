/*******************************************************************************
* \file `$INSTANCE_NAME`_config.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  Contains the variable declarations for the `$INSTANCE_NAME` component.
*
********************************************************************************
* \copyright
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef `$INSTANCE_NAME`_CONFIG_H
#define `$INSTANCE_NAME`_CONFIG_H

#include "dstc/dstc.h"
    
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Note to user – this macro should be used to set up an stc_dstc_config variable 
before calling Dstc_Init(). Note, however, that not all members of the struct are
initialized, only the first none. You must supply function pointers for the 
remaining members, as follows (for a component called “`INSTANCE_NAME`”).

stc_dstc_des0123_t descriptor; Initialize the descriptor with data/peripheral 
                               pointers used in the transmission

stc_dstc_config_t dstc_Config =
{
    0,
    `INSTANCE_NAME`_Config,
    pfnDstcAdc0PrioCallback,
    …,
    pfnDstcWcCallback
};

dstc_config.u32Destp = (uint32_t)&descriptor; Set the descriptor address in the 
                                              configuration structure
*/

/* Configuration structure */
#define `$INSTANCE_NAME`_Config    \
    /* bSwInterruptEnable */    `=$bSwInterruptEnable ? "TRUE" : "FALSE"`,\
    /* bErInterruptEnable */    `=$bErInterruptEnable ? "TRUE" : "FALSE"`,\
    /* bReadSkipBufferDisable */`=$bReadSkipBufferDisable ? "TRUE" : "FALSE"`,\
    /* bErrorStopEnable */      `=$bErrorStopEnable ? "TRUE" : "FALSE"`,\
    /* enSwTransferPriority */  `=GetNameForEnum("en_dstc_swpr_t", $enSwTransferPriority)`,\
    /* bTouchNvic */            `=$bTouchNvic ? "TRUE" : "FALSE"`,\
    /* pfnNotifySwCallback */   `=($pfnNotifySwCallback eq "") || !$bSwInterruptEnable ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnNotifySwCallback`, /* User-supplied callback function */\
    /* pfnErrorCallback */      `=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "NULL" : "&" . $INSTANCE_NAME . "_" . $pfnErrorCallback`, /* User-supplied callback function */


/* Notification SW callback function */
`=($pfnNotifySwCallback eq "") || !$bSwInterruptEnable ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnNotifySwCallback . "(void);"`

/* Error callback function */
`=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "/* Callback unused */" : "void " . $INSTANCE_NAME . "_" . $pfnErrorCallback . "(en_dstc_est_error_t enEstError,"`
`=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "" : "                    uint16_t u16ErrorChannel,"` 
`=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "" : "                    uint16_t u16ErrorDesPointer,"`
`=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "" : "                    boolean_t bSoftwareError,"`
`=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "" : "                    boolean_t bDoubleError,"`
`=($pfnErrorCallback eq "") || !$bErInterruptEnable ? "" : "                    boolean_t bErrorStop);"`


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* `$INSTANCE_NAME`_CONFIG_H */

/* [] END OF FILE */
