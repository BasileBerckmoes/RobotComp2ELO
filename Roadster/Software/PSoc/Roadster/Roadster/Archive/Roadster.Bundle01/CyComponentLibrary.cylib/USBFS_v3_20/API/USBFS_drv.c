/***************************************************************************//**
* \file `$INSTANCE_NAME`_drv.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file contains the Endpoint 0 Driver for the USBFS Component.  
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_pvt.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`


/***************************************
* Global data allocation
***************************************/

volatile T_`$INSTANCE_NAME`_EP_CTL_BLOCK `$INSTANCE_NAME`_EP[`$INSTANCE_NAME`_MAX_EP];

/** Contains the current configuration number, which is set by the host using a 
 * SET_CONFIGURATION request. This variable is initialized to zero in 
 * USBFS_InitComponent() API and can be read by the USBFS_GetConfiguration() 
 * API.*/
volatile uint8 `$INSTANCE_NAME`_configuration;

/** Contains the current interface number.*/
volatile uint8 `$INSTANCE_NAME`_interfaceNumber;

/** This variable is set to one after SET_CONFIGURATION and SET_INTERFACE 
 *requests. It can be read by the USBFS_IsConfigurationChanged() API */
volatile uint8 `$INSTANCE_NAME`_configurationChanged;

/** Contains the current device address.*/
volatile uint8 `$INSTANCE_NAME`_deviceAddress;

/** This is a two-bit variable that contains power status in the bit 0 
 * (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote wakeup 
 * status (DEVICE_STATUS_REMOTE_WAKEUP) in the bit 1. This variable is 
 * initialized to zero in USBFS_InitComponent() API, configured by the 
 * USBFS_SetPowerStatus() API. The remote wakeup status cannot be set using the 
 * API SetPowerStatus(). */
volatile uint8 `$INSTANCE_NAME`_deviceStatus;

volatile uint8 `$INSTANCE_NAME`_interfaceSetting[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
volatile uint8 `$INSTANCE_NAME`_interfaceSetting_last[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];
volatile uint8 `$INSTANCE_NAME`_interfaceStatus[`$INSTANCE_NAME`_MAX_INTERFACES_NUMBER];

/** Contains the started device number. This variable is set by the 
 * USBFS_Start() or USBFS_InitComponent() APIs.*/
volatile uint8 `$INSTANCE_NAME`_device;

/** Initialized class array for each interface. It is used for handling Class 
 * specific requests depend on interface class. Different classes in multiple 
 * alternate settings are not supported.*/
const uint8 CYCODE *`$INSTANCE_NAME`_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8  `$INSTANCE_NAME`_ep0Toggle;
volatile uint8  `$INSTANCE_NAME`_lastPacketSize;

/** This variable is used by the communication functions to handle the current 
* transfer state.
* Initialized to TRANS_STATE_IDLE in the USBFS_InitComponent() API and after a 
* complete transfer in the status stage.
* Changed to the TRANS_STATE_CONTROL_READ or TRANS_STATE_CONTROL_WRITE in setup 
* transaction depending on the request type.
*/
volatile uint8  `$INSTANCE_NAME`_transferState;
volatile T_`$INSTANCE_NAME`_TD `$INSTANCE_NAME`_currentTD;
volatile uint8  `$INSTANCE_NAME`_ep0Mode;
volatile uint8  `$INSTANCE_NAME`_ep0Count;
volatile uint16 `$INSTANCE_NAME`_transferByteCount;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ep_0_Interrupt
****************************************************************************//**
*
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_EP_0_ISR)
{
    `$UINT_TYPE` tempReg;
    `$UINT_TYPE` modifyReg;

#ifdef `$INSTANCE_NAME`_EP_0_ISR_ENTRY_CALLBACK
    `$INSTANCE_NAME`_EP_0_ISR_EntryCallback();
#endif /* (`$INSTANCE_NAME`_EP_0_ISR_ENTRY_CALLBACK) */
    
    tempReg = `$INSTANCE_NAME`_EP0_CR_REG;
    if ((tempReg & `$INSTANCE_NAME`_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((tempReg & `$INSTANCE_NAME`_MODE_SETUP_RCVD) != 0u)
        {
            if ((tempReg & `$INSTANCE_NAME`_MODE_MASK) != `$INSTANCE_NAME`_MODE_NAK_IN_OUT)
            {
                /* Mode not equal to NAK_IN_OUT: invalid setup */
                modifyReg = 0u;
            }
            else
            {
                `$INSTANCE_NAME`_HandleSetup();
                
                if ((`$INSTANCE_NAME`_ep0Mode & `$INSTANCE_NAME`_MODE_SETUP_RCVD) != 0u)
                {
                    /* SETUP bit set: exit without mode modificaiton */
                    modifyReg = 0u;
                }
            }
        }
        else if ((tempReg & `$INSTANCE_NAME`_MODE_IN_RCVD) != 0u)
        {
            `$INSTANCE_NAME`_HandleIN();
        }
        else if ((tempReg & `$INSTANCE_NAME`_MODE_OUT_RCVD) != 0u)
        {
            `$INSTANCE_NAME`_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        
        /* Modify the EP0_CR register */
        if (modifyReg != 0u)
        {
            
            tempReg = `$INSTANCE_NAME`_EP0_CR_REG;
            
            /* Make sure that SETUP bit is cleared before modification */
            if ((tempReg & `$INSTANCE_NAME`_MODE_SETUP_RCVD) == 0u)
            {
                /* Update count register */
                tempReg = (`$UINT_TYPE`) `$INSTANCE_NAME`_ep0Toggle | `$INSTANCE_NAME`_ep0Count;
                `$INSTANCE_NAME`_EP0_CNT_REG = tempReg;
               
                /* Make sure that previous write operaiton was successful */
                if (tempReg == `$INSTANCE_NAME`_EP0_CNT_REG)
                {
                    /* Repeat until next successful write operation */
                    do
                    {
                        /* Init temporary variable */
                        modifyReg = `$INSTANCE_NAME`_ep0Mode;
                        
                        /* Unlock register */
                        tempReg = (uint8) (`$INSTANCE_NAME`_EP0_CR_REG & `$INSTANCE_NAME`_MODE_SETUP_RCVD);
                        
                        /* Check if SETUP bit is not set */
                        if (0u == tempReg)
                        {
                            /* Set the Mode Register  */
                            `$INSTANCE_NAME`_EP0_CR_REG = `$INSTANCE_NAME`_ep0Mode;
                            
                            /* Writing check */
                            modifyReg = `$INSTANCE_NAME`_EP0_CR_REG & `$INSTANCE_NAME`_MODE_MASK;
                        }
                    }
                    while (modifyReg != `$INSTANCE_NAME`_ep0Mode);
                }
            }
        }
    }

    `$INSTANCE_NAME`_ClearSieInterruptSource(`$INSTANCE_NAME`_INTR_SIE_EP0_INTR);
	
#ifdef `$INSTANCE_NAME`_EP_0_ISR_EXIT_CALLBACK
    `$INSTANCE_NAME`_EP_0_ISR_ExitCallback();
#endif /* (`$INSTANCE_NAME`_EP_0_ISR_EXIT_CALLBACK) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleSetup
****************************************************************************//**
*
*  This Routine dispatches requests for the four USB request types
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_HandleSetup(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleSetup")`
{
    uint8 requestHandled;
    
    /* Clear register lock by SIE (read register) and clear setup bit 
    * (write any value in register).
    */
    requestHandled = (uint8) `$INSTANCE_NAME`_EP0_CR_REG;
    `$INSTANCE_NAME`_EP0_CR_REG = (`$UINT_TYPE`) requestHandled;
    requestHandled = (uint8) `$INSTANCE_NAME`_EP0_CR_REG;

    if ((requestHandled & `$INSTANCE_NAME`_MODE_SETUP_RCVD) != 0u)
    {
        /* SETUP bit is set: exit without mode modification. */
        `$INSTANCE_NAME`_ep0Mode = requestHandled;
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        `$INSTANCE_NAME`_UpdateStatusBlock(`$INSTANCE_NAME`_XFER_PREMATURE);

        /* Check request type. */
        switch (`$INSTANCE_NAME`_bmRequestTypeReg & `$INSTANCE_NAME`_RQST_TYPE_MASK)
        {
            case `$INSTANCE_NAME`_RQST_TYPE_STD:
                requestHandled = `$INSTANCE_NAME`_HandleStandardRqst();
                break;
                
            case `$INSTANCE_NAME`_RQST_TYPE_CLS:
                requestHandled = `$INSTANCE_NAME`_DispatchClassRqst();
                break;
                
            case `$INSTANCE_NAME`_RQST_TYPE_VND:
                requestHandled = `$INSTANCE_NAME`_HandleVendorRqst();
                break;
                
            default:
                requestHandled = `$INSTANCE_NAME`_FALSE;
                break;
        }
        
        /* If request is not recognized. Stall endpoint 0 IN and OUT. */
        if (requestHandled == `$INSTANCE_NAME`_FALSE)
        {
            `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleIN
****************************************************************************//**
*
*  This routine handles EP0 IN transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_HandleIN(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleIN")`
{
    switch (`$INSTANCE_NAME`_transferState)
    {
        case `$INSTANCE_NAME`_TRANS_STATE_IDLE:
            break;
        
        case `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ:
            `$INSTANCE_NAME`_ControlReadDataStage();
            break;
            
        case `$INSTANCE_NAME`_TRANS_STATE_CONTROL_WRITE:
            `$INSTANCE_NAME`_ControlWriteStatusStage();
            break;
            
        case `$INSTANCE_NAME`_TRANS_STATE_NO_DATA_CONTROL:
            `$INSTANCE_NAME`_NoDataControlStatusStage();
            break;
            
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleOUT
****************************************************************************//**
*
*  This routine handles EP0 OUT transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_HandleOUT(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleOUT")`
{
    switch (`$INSTANCE_NAME`_transferState)
    {
        case `$INSTANCE_NAME`_TRANS_STATE_IDLE:
            break;
        
        case `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ:
            `$INSTANCE_NAME`_ControlReadStatusStage();
            break;
            
        case `$INSTANCE_NAME`_TRANS_STATE_CONTROL_WRITE:
            `$INSTANCE_NAME`_ControlWriteDataStage();
            break;
            
        case `$INSTANCE_NAME`_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            `$INSTANCE_NAME`_UpdateStatusBlock(`$INSTANCE_NAME`_XFER_ERROR);
            
            /* We expect no more data, so stall INs and OUTs */
            `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_STALL_IN_OUT;
            break;
            
        default:    
            /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_LoadEP0
****************************************************************************//**
*
*  This routine loads the EP0 data registers for OUT transfers. It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
*
* \globalvars
*  `$INSTANCE_NAME`_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  `$INSTANCE_NAME`_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  `$INSTANCE_NAME`_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  `$INSTANCE_NAME`_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  `$INSTANCE_NAME`_ep0Toggle - inverted
*  `$INSTANCE_NAME`_ep0Mode  - prepare for mode register content.
*  `$INSTANCE_NAME`_transferState - set to TRANS_STATE_CONTROL_READ
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_LoadEP0(void) `=ReentrantKeil($INSTANCE_NAME . "_LoadEP0")`
{
    `$UINT_TYPE` ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    `$INSTANCE_NAME`_transferByteCount += `$INSTANCE_NAME`_lastPacketSize;

    /* Now load the next transaction */
    while ((`$INSTANCE_NAME`_currentTD.count > 0u) && (ep0Count < 8u))
    {
        `$INSTANCE_NAME`_EP0_DR_BASE.epData[ep0Count] = (`$UINT_TYPE`) *`$INSTANCE_NAME`_currentTD.pData;
        `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_currentTD.pData[1u];
        ep0Count++;
        `$INSTANCE_NAME`_currentTD.count--;
    }

    /* Support zero-length packet */
    if ((`$INSTANCE_NAME`_lastPacketSize == 8u) || (ep0Count > 0u))
    {
        /* Update the data toggle */
        `$INSTANCE_NAME`_ep0Toggle ^= `$INSTANCE_NAME`_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    `$INSTANCE_NAME`_ep0Count =       (uint8) ep0Count;
    `$INSTANCE_NAME`_lastPacketSize = (uint8) ep0Count;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitControlRead
****************************************************************************//**
*
*  Initialize a control read transaction. It is used to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
*
* \return
*  requestHandled state.
*
* \globalvars
*  `$INSTANCE_NAME`_currentTD.count - counts of data to be sent.
*  `$INSTANCE_NAME`_currentTD.pData - data pointer.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_InitControlRead(void) `=ReentrantKeil($INSTANCE_NAME . "_InitControlRead")`
{
    uint16 xferCount;

    if (`$INSTANCE_NAME`_currentTD.count == 0u)
    {
        (void) `$INSTANCE_NAME`_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ;
        
        /* Set the toggle, it gets updated in LoadEP */
        `$INSTANCE_NAME`_ep0Toggle = 0u;
        
        /* Initialize the Status Block */
        `$INSTANCE_NAME`_InitializeStatusBlock();
        
        xferCount = ((uint16)((uint16) `$INSTANCE_NAME`_lengthHiReg << 8u) | ((uint16) `$INSTANCE_NAME`_lengthLoReg));

        if (`$INSTANCE_NAME`_currentTD.count > xferCount)
        {
            `$INSTANCE_NAME`_currentTD.count = xferCount;
        }
        
        `$INSTANCE_NAME`_LoadEP0();
    }

    return (`$INSTANCE_NAME`_TRUE);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitZeroLengthControlTransfer
****************************************************************************//**
*
*  Initialize a zero length data IN transfer.
*
* \return
*  requestHandled state.
*
* \globalvars
*  `$INSTANCE_NAME`_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  `$INSTANCE_NAME`_ep0Mode  - prepare for mode register content.
*  `$INSTANCE_NAME`_transferState - set to TRANS_STATE_CONTROL_READ
*  `$INSTANCE_NAME`_ep0Count - cleared, means the zero-length packet.
*  `$INSTANCE_NAME`_lastPacketSize - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_InitZeroLengthControlTransfer(void)
                                                `=ReentrantKeil($INSTANCE_NAME . "_InitZeroLengthControlTransfer")`
{
    /* Update the state */
    `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_CONTROL_READ;
    
    /* Set the data toggle */
    `$INSTANCE_NAME`_ep0Toggle = `$INSTANCE_NAME`_EP0_CNT_DATA_TOGGLE;
    
    /* Set the Mode Register  */
    `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_ACK_IN_STATUS_OUT;
    
    /* Save the packet size for next time */
    `$INSTANCE_NAME`_lastPacketSize = 0u;
    
    `$INSTANCE_NAME`_ep0Count = 0u;

    return (`$INSTANCE_NAME`_TRUE);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ControlReadDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control read transfer.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ControlReadDataStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlReadDataStage")`

{
    `$INSTANCE_NAME`_LoadEP0();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ControlReadStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control read transfer.
*
*
* \globalvars
*  `$INSTANCE_NAME`_USBFS_transferByteCount - updated with last packet size.
*  `$INSTANCE_NAME`_transferState - set to TRANS_STATE_IDLE.
*  `$INSTANCE_NAME`_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ControlReadStatusStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlReadStatusStage")`
{
    /* Update the transfer byte count */
    `$INSTANCE_NAME`_transferByteCount += `$INSTANCE_NAME`_lastPacketSize;
    
    /* Go Idle */
    `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_IDLE;
    
    /* Update the completion block */
    `$INSTANCE_NAME`_UpdateStatusBlock(`$INSTANCE_NAME`_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitControlWrite
****************************************************************************//**
*
*  Initialize a control write transaction
*
* \return
*  requestHandled state.
*
* \globalvars
*  `$INSTANCE_NAME`_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  `$INSTANCE_NAME`_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  `$INSTANCE_NAME`_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_InitControlWrite(void) `=ReentrantKeil($INSTANCE_NAME . "_InitControlWrite")`
{
    uint16 xferCount;

    /* Set up the state machine */
    `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_CONTROL_WRITE;
    
    /* This might not be necessary */
    `$INSTANCE_NAME`_ep0Toggle = `$INSTANCE_NAME`_EP0_CNT_DATA_TOGGLE;
    
    /* Initialize the Status Block */
    `$INSTANCE_NAME`_InitializeStatusBlock();

    xferCount = ((uint16)((uint16) `$INSTANCE_NAME`_lengthHiReg << 8u) | ((uint16) `$INSTANCE_NAME`_lengthLoReg));

    if (`$INSTANCE_NAME`_currentTD.count > xferCount)
    {
        `$INSTANCE_NAME`_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_ACK_OUT_STATUS_IN;

    return(`$INSTANCE_NAME`_TRUE);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ControlWriteDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
*
* \globalvars
*  `$INSTANCE_NAME`_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  `$INSTANCE_NAME`_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  `$INSTANCE_NAME`_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  `$INSTANCE_NAME`_ep0Toggle - inverted
*  `$INSTANCE_NAME`_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ControlWriteDataStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlWriteDataStage")`
{
    `$UINT_TYPE` ep0Count;
    `$UINT_TYPE` regIndex = 0u;

    ep0Count = (`$INSTANCE_NAME`_EP0_CNT_REG & `$INSTANCE_NAME`_EPX_CNT0_MASK) - `$INSTANCE_NAME`_EPX_CNTX_CRC_COUNT;

    `$INSTANCE_NAME`_transferByteCount += (uint8)ep0Count;

    while ((`$INSTANCE_NAME`_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *`$INSTANCE_NAME`_currentTD.pData = (uint8) `$INSTANCE_NAME`_EP0_DR_BASE.epData[regIndex];
        `$INSTANCE_NAME`_currentTD.pData = &`$INSTANCE_NAME`_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        `$INSTANCE_NAME`_currentTD.count--;
    }
    
    `$INSTANCE_NAME`_ep0Count = (uint8)ep0Count;
    
    /* Update the data toggle */
    `$INSTANCE_NAME`_ep0Toggle ^= `$INSTANCE_NAME`_EP0_CNT_DATA_TOGGLE;
    
    /* Expect Data or Status Stage */
    `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ControlWriteStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control write transfer
*
* \globalvars
*  `$INSTANCE_NAME`_transferState - set to TRANS_STATE_IDLE.
*  `$INSTANCE_NAME`_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ControlWriteStatusStage(void) `=ReentrantKeil($INSTANCE_NAME . "_ControlWriteStatusStage")`
{
    /* Go Idle */
    `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_IDLE;
    
    /* Update the completion block */    
    `$INSTANCE_NAME`_UpdateStatusBlock(`$INSTANCE_NAME`_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitNoDataControlTransfer
****************************************************************************//**
*
*  Initialize a no data control transfer
*
* \return
*  requestHandled state.
*
* \globalvars
*  `$INSTANCE_NAME`_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  `$INSTANCE_NAME`_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  `$INSTANCE_NAME`_ep0Count - cleared.
*  `$INSTANCE_NAME`_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_InitNoDataControlTransfer(void) `=ReentrantKeil($INSTANCE_NAME . "_InitNoDataControlTransfer")`
{
    `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_NO_DATA_CONTROL;
    `$INSTANCE_NAME`_ep0Mode       = `$INSTANCE_NAME`_MODE_STATUS_IN_ONLY;
    `$INSTANCE_NAME`_ep0Toggle     = `$INSTANCE_NAME`_EP0_CNT_DATA_TOGGLE;
    `$INSTANCE_NAME`_ep0Count      = 0u;

    return (`$INSTANCE_NAME`_TRUE);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_NoDataControlStatusStage
****************************************************************************//**
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* \globalvars
*  `$INSTANCE_NAME`_transferState - set to TRANS_STATE_IDLE.
*  `$INSTANCE_NAME`_ep0Mode  - set to MODE_STALL_IN_OUT.
*  `$INSTANCE_NAME`_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  `$INSTANCE_NAME`_deviceAddress - used to set new address and cleared
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_NoDataControlStatusStage(void) `=ReentrantKeil($INSTANCE_NAME . "_NoDataControlStatusStage")`
{
    if (0u != `$INSTANCE_NAME`_deviceAddress)
    {
        /* Update device address if we got new address. */
        `$INSTANCE_NAME`_CR0_REG = (`$UINT_TYPE`) `$INSTANCE_NAME`_deviceAddress | `$INSTANCE_NAME`_CR0_ENABLE;
        `$INSTANCE_NAME`_deviceAddress = 0u;
    }

    `$INSTANCE_NAME`_transferState = `$INSTANCE_NAME`_TRANS_STATE_IDLE;
    
    /* Update the completion block. */
    `$INSTANCE_NAME`_UpdateStatusBlock(`$INSTANCE_NAME`_XFER_STATUS_ACK);
    
    /* Stall IN and OUT, no more data is expected. */
    `$INSTANCE_NAME`_ep0Mode = `$INSTANCE_NAME`_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateStatusBlock
****************************************************************************//**
*
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the `$INSTANCE_NAME`_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
*  completionCode - status.
*
*
* \globalvars
*  `$INSTANCE_NAME`_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  `$INSTANCE_NAME`_currentTD.pStatusBlock->length - updated.
*  `$INSTANCE_NAME`_currentTD.pStatusBlock - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UpdateStatusBlock(uint8 completionCode) `=ReentrantKeil($INSTANCE_NAME . "_UpdateStatusBlock")`
{
    if (`$INSTANCE_NAME`_currentTD.pStatusBlock != NULL)
    {
        `$INSTANCE_NAME`_currentTD.pStatusBlock->status = completionCode;
        `$INSTANCE_NAME`_currentTD.pStatusBlock->length = `$INSTANCE_NAME`_transferByteCount;
        `$INSTANCE_NAME`_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitializeStatusBlock
****************************************************************************//**
*
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes `$INSTANCE_NAME`_transferByteCount.  Save some space,
*  this is the only consumer.
*
* \globalvars
*  `$INSTANCE_NAME`_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  `$INSTANCE_NAME`_currentTD.pStatusBlock->length - cleared.
*  `$INSTANCE_NAME`_transferByteCount - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_InitializeStatusBlock(void) `=ReentrantKeil($INSTANCE_NAME . "_InitializeStatusBlock")`
{
    `$INSTANCE_NAME`_transferByteCount = 0u;
    
    if (`$INSTANCE_NAME`_currentTD.pStatusBlock != NULL)
    {
        `$INSTANCE_NAME`_currentTD.pStatusBlock->status = `$INSTANCE_NAME`_XFER_IDLE;
        `$INSTANCE_NAME`_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */
