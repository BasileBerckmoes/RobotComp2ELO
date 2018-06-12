/*******************************************************************************
* File Name: LIN_Dynamic.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains implementation of dynamic part of LIN API.
*
********************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_LIN_LIN_DYNAMIC_H)
#define CY_LIN_LIN_DYNAMIC_H
    
/* IsMultiInstanse = 0u for single instance 
*  IsMultiInstanse = 1u for 1st and 2nd instance */
#define `$INSTANCE_1_NAME`_IS_MULTI_INSTANCE           (`$IsMultiInstance`u)

#include "`$INSTANCE_1_NAME`.h"

#if(`$INSTANCE_1_NAME`_IS_MULTI_INSTANCE)
        #if !defined(CY_LIN_`$INSTANCE_2_NAME`_H)
            #include "`$INSTANCE_2_NAME`.h"
        #endif /*(!defined(CY_LIN_`$INSTANCE_2_NAME`_H))*/
#endif /*(`$INSTANCE_NAME`_IS_MULTI_INSTANCE)*/

#if(1u == `$INSTANCE_1_NAME`_AUTO_BAUD_RATE_SYNC)

    /* Initial clock divider */
    extern l_u16 `$INSTANCE_1_NAME`_initialClockDivider; 

#endif  /* (1u == `$INSTANCE_1_NAME`_AUTO_BAUD_RATE_SYNC) */

#if(`$INSTANCE_1_NAME`_IS_MULTI_INSTANCE)

     #if(1u == `$INSTANCE_2_NAME`_AUTO_BAUD_RATE_SYNC)

        extern l_u16 `$INSTANCE_2_NAME`_initialClockDivider; 

    #endif  /* (1u == `$INSTANCE_2_NAME`_AUTO_BAUD_RATE_SYNC) */
#endif /*(`$INSTANCE_1_NAME`_IS_MULTI_INSTANCE)*/

/* Interface handle constant  for `$INSTANCE_NAME` */
#define `$INSTANCE_1_NAME`_IFC_HANDLE                 (0u)

#if(`$INSTANCE_1_NAME`_IS_MULTI_INSTANCE)
    #define `$INSTANCE_2_NAME`_IFC_HANDLE               (1u)
#else    
    #define `$INSTANCE_2_NAME`_TL_ENABLED               (0u)
    #define `$INSTANCE_2_NAME`_TL_API_FORMAT            (0u)
    #define `$INSTANCE_2_NAME`_CS_SEL_SERVICES01        (0u)
    #define `$INSTANCE_2_NAME`_CS_SEL_SERVICES01        (0u)
    #define `$INSTANCE_2_NAME`_CS_SEL_SERVICES01        (0u)
    
    #define `$INSTANCE_2_NAME`_NCS_0xB0_SEL               (0x01u)
    #define `$INSTANCE_2_NAME`_NCS_0xB1_SEL               (0x02u)
    #define `$INSTANCE_2_NAME`_NCS_0xB2_SEL               (0x04u)
    #define `$INSTANCE_2_NAME`_NCS_0xB3_SEL               (0x08u)
    #define `$INSTANCE_2_NAME`_NCS_0xB4_SEL               (0x10u)
    #define `$INSTANCE_2_NAME`_NCS_0xB5_SEL               (0x20u)
    #define `$INSTANCE_2_NAME`_NCS_0xB6_SEL               (0x40u)
    #define `$INSTANCE_2_NAME`_NCS_0xB7_SEL               (0x80u)

#endif /*(`$INSTANCE_NAME`_IS_MULTI_INSTANCE)*/

l_bool l_ifc_init(l_ifc_handle iii);
void l_ifc_wake_up(l_ifc_handle iii);
l_u16 l_ifc_ioctl(l_ifc_handle iii, l_ioctl_op op, void* pv);
void l_ifc_rx(l_ifc_handle iii);
void l_ifc_tx(l_ifc_handle iii);
void l_ifc_aux(l_ifc_handle iii);
l_u16 l_ifc_read_status(l_ifc_handle iii);


#if(1u == `$INSTANCE_1_NAME`_LIN_1_3)
        
    l_bool l_ifc_connect(l_ifc_handle iii);
    l_bool l_ifc_disconnect(l_ifc_handle iii);
    
#else
    #if(`$INSTANCE_1_NAME`_IS_MULTI_INSTANCE)
        #if(1u == `$INSTANCE_2_NAME`_LIN_1_3)
            l_bool l_ifc_connect(l_ifc_handle iii);
            l_bool l_ifc_disconnect(l_ifc_handle iii);
        #endif /* ( 1u == `$INSTANCE_2_NAME`_LIN_1_3) */
    #endif /*(`$INSTANCE_1_NAME`_IS_MULTI_INSTANCE)*/
#endif /* ( 1u == `$INSTANCE_1_NAME`_LIN_1_3) */

void        ld_init(l_ifc_handle iii);
l_u8 ld_read_by_id_callout(l_ifc_handle iii, l_u8 id, l_u8* frameData);

/* Transport Layer Functions: Node Configuration Functions */
l_u8        ld_read_configuration(l_ifc_handle iii, l_u8* pData, l_u8* const length);
l_u8        ld_set_configuration(l_ifc_handle iii, const l_u8* const pData, l_u16 length);
void        ld_send_message(l_ifc_handle iii, l_u16 length, l_u8 nad, const l_u8* const ld_data);
void        ld_receive_message(l_ifc_handle iii, l_u16* const length, l_u8* const nad, l_u8* const ld_data);
l_u8        ld_tx_status(l_ifc_handle iii);
l_u8        ld_rx_status(l_ifc_handle iii);

void        ld_put_raw(l_ifc_handle iii, const l_u8* const ld_data);
void        ld_get_raw(l_ifc_handle iii, l_u8* const ld_data);
l_u8        ld_raw_tx_status(l_ifc_handle iii);
l_u8        ld_raw_rx_status(l_ifc_handle iii);
   


`$LIN_DWC_H`

#endif /* CY_LIN_LIN_DYNAMIC_H */

/* [] END OF FILE */

