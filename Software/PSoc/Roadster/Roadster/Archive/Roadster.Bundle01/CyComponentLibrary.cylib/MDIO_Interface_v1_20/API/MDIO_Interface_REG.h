/*******************************************************************************
* File Name: `$INSTANCE_NAME`_REG.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains CFP register declaration for the MDIO Slave component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CFP_REGISTER_SET_`$INSTANCE_NAME`_H)
#define CY_CFP_REGISTER_SET_`$INSTANCE_NAME`_H

#if(`$INSTANCE_NAME`_ADVANCED_MODE)

/* Size of each register space */
`$RegPagesSize`

`$RegisterDeclaration`

/* Register page info list (the start address of the register space memory
*  and the start address of the register configuration associated with the
*  register space.
*/
extern const uint16 * const CYCODE `$INSTANCE_NAME`_pageInfoPtr[`$INSTANCE_NAME`_PAGE_INFO_SIZE];

#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */

#endif /* CY_CFP_REGISTER_SET_`$INSTANCE_NAME`_H */

/* [] END OF FILE */
