/***************************************************************************//**
* \file `$INSTANCE_NAME`_cydmac.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides macros implemenation of DMA_P4 functions.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_`$INSTANCE_NAME`_cydmac_H)
#define CY_USBFS_`$INSTANCE_NAME`_cydmac_H

#include "`$INSTANCE_NAME`_pvt.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaSetConfiguration
****************************************************************************//**
*
*  Sets configuration information for the specified descriptor.
*
*  \param ch:    DMA ch modified by this function.
*  \param descr: Descriptor (0 or 1) modified by this function.
*  \param cfg:   Descriptor control register.
*
* \sideeffect
*   The status register associated with the specified descriptor is reset to 
*   zero after this function call. This function should not be called while 
*   the descriptor is active. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaSetConfiguration(ch, descr, cfg) \
    do{ \
        CYDMA_DESCR_BASE.descriptor[ch][descr].ctl = (cfg); \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaSetInterruptMask
****************************************************************************//**
*
*  Enables the DMA channel interrupt.
*
*  \param ch: Channel used by this function.
*
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaSetInterruptMask(ch) \
    do{ \
        CYDMA_INTR_MASK_REG |= ((uint32)(1UL << (ch))); \
    }while(0)


/*******************************************************************************
* Function Name:`$INSTANCE_NAME`_CyDmaSetDescriptor0Next
****************************************************************************//**
*
*  Sets the descriptor 0 that should be run the next time the channel is
*  triggered.
*
*  \param channel:    Channel used by this function.
*
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaSetDescriptor0Next(ch) \
    do{ \
        CYDMA_CH_CTL_BASE.ctl[(ch)] &= (uint32) ~CYDMA_DESCRIPTOR; \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaSetNumDataElements
****************************************************************************//**
*
*  Sets the number of data elements to transfer for specified descriptor.
*
*  \param ch:    Channel used by this function.
*  \param descr: Descriptor (0 or 1) modified by this function.
*  \param numEl: Total number of data elements this descriptor transfers - 1u.
*         Valid ranges are 0 to 65535.
*
*
* \sideeffect
*   This function should not be called when the specified descriptor is active 
*   in the DMA transfer engine. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaSetNumDataElements(ch, descr, numEl) \
    do{ \
        CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].ctl = \
            ((CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].ctl & (uint32) ~CYDMA_DATA_NR) | ((uint32) (numEl))); \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaGetSrcAddress
****************************************************************************//**
*
*  Returns the source address for the specified descriptor.
*
*  \param ch:    Channel used by this function.
*  \param descr: Specifies descriptor (0 or 1) used by this function.
*
* \return
*  Source address written to specified descriptor.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaGetSrcAddress(ch, descr)    CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].src


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaSetSrcAddress
****************************************************************************//**
*
*  Configures the source address for the specified descriptor.
*
*  \param ch:         Channel used by this function.
*  \param descr:      Descriptor (0 or 1) modified by this function.
*  \param srcAddress: Address of DMA transfer source.
*
*
* \sideeffect
*   This function should not be called when the specified descriptor is active 
*   in the DMA transfer engine. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaSetSrcAddress(ch, descr, srcAddress) \
    do{ \
        CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].src = (srcAddress); \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaGetDstAddress
****************************************************************************//**
*
*  Returns the destination address for the specified descriptor, set by
*  CyDmaSetDstAddress().
*
*  \param ch:    Channel used by this function.
*  \param descr: Specifies descriptor (0 or 1) used by this function.
*
* \return
*  Destination address written to specified descriptor.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaGetDstAddress(ch, descr)    CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].dst


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaSetDstAddress
****************************************************************************//**
*
*  Configures the destination address for the specified descriptor.
*
*  \param ch:         Channel used by this function.
*  \param descr:      Descriptor (0 or 1) modified by this function.
*  \param dstAddress: Address of DMA transfer destination.
*
*
* \sideeffect
*   This function should not be called when the specified descriptor is active 
*   in the DMA transfer engine. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaSetDstAddress(ch, descr, dstAddress) \
    do{ \
        CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].dst = (dstAddress); \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaValidateDescriptor
****************************************************************************//**
*
*  Validates the specified descriptor after it has been invalidated.
*
*  \param ch:    Channel used by this function.
*  \param descr: Descriptor (0 or 1) modified by this function.
*
*
* \sideeffect
*   The status register associated with the specified descriptor is reset to 
*   zero after this function call.
*   This function should not be called when the specified descriptor is active 
*   in the DMA transfer engine. This can be checked by calling CyDmaGetStatus().
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaValidateDescriptor(ch, descr) \
    do{ \
        CYDMA_DESCR_BASE.descriptor[(ch)][(descr)].status = CYDMA_VALID; \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaChEnable
****************************************************************************//**
*
*  Enables the DMA ch.
*
*  \param ch: Channel used by this function.
*
*
* \sideeffect
*   If this function is called before DMA is completely configured the operation 
*   of the DMA is undefined and could result in system data corruption.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaChEnable(ch) \
    do{ \
        CYDMA_CH_CTL_BASE.ctl[(ch)] |= CYDMA_ENABLED; \
    }while(0)


/*******************************************************************************
* Function Name: CyDmaChDisable
****************************************************************************//**
*
*  Disables the DMA ch.
*
*  \param ch: Channel used by this function.
*
*
* \sideeffect
*  If this function is called during a DMA transfer the transfer is aborted.
*
*******************************************************************************/
#define `$INSTANCE_NAME`_CyDmaChDisable(ch) \
    do{ \
        CYDMA_CH_CTL_BASE.ctl[(ch)] &= (uint32) ~CYDMA_ENABLED; \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaTriggerIn
****************************************************************************//**
*
*  Triggers the DMA channel to execute a transfer. The tr_in signal is 
*  triggered.
*
*  \param trSel: trigger to be activated.
*
*
*******************************************************************************/
#define `$INSTANCE_NAME`_DMA_USB_REQ_TR_OUT `$DMA_USB_REQ_TR_OUT`
#define `$INSTANCE_NAME`_CyDmaTriggerIn(trSel) \
    do{ \
        CYDMA_TR_CTL_REG = `$INSTANCE_NAME`_DMA_USB_REQ_TR_OUT | (uint32)(trSel); \
    }while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyDmaTriggerOut
****************************************************************************//**
*
*  Triggers the DMA channel to generate a transfer completion signal without 
*  actual transfer executed. The tr_out signal is triggered.
*
*  \param trSel: trigger to be activated.
*
*
*******************************************************************************/
#define `$INSTANCE_NAME`_DMA_USB_BURST_END_TR_OUT  `$DMA_USB_BURST_END_TR_OUT`
#define `$INSTANCE_NAME`_CyDmaTriggerOut(trSel) \
    do{ \
        CYDMA_TR_CTL_REG = `$INSTANCE_NAME`_DMA_USB_BURST_END_TR_OUT | (uint32)(trSel); \
    }while(0)


#endif /* (CY_USBFS_`$INSTANCE_NAME`_cydmac_H) */


/* [] END OF FILE */
