/*******************************************************************************
* File Name: `$INSTANCE_NAME`_Defaults.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains a data structure for the default register store. The user
*  may enter default values for all the parameters. The generated comment
*  section contains a template.
*
*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

#if(0)

/*******************************************************************************
* Copy/Paste all the code between Start_Init and End_Init into cyapicallbacks.h
* or any header file included in cyapicallbacks.h to provide the default values
* for all the parameters.
*
* Start_Init
*******************************************************************************/

`$NullStructure`

/*******************************************************************************
* End_Init
*******************************************************************************/

#endif /* (0) */
    
const `$INSTANCE_NAME`_REGS CYCODE `$INSTANCE_NAME`_regsDefault

/*`#START DEFAULT_REGISTER_STORE`*/

/*`#END`*/

#ifdef `$INSTANCE_NAME`_DEFAULT_REGISTER_STORE
    `$INSTANCE_NAME`_DEFAULT_REGISTER_STORE
#endif /* `$INSTANCE_NAME`_DEFAULT_REGISTER_STORE */

;


/* [] END OF FILE */
