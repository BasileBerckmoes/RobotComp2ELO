/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands for the EZI2C
*  component. The actual protocol and operation code resides in the interrupt
*  service routine file.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

/**********************************
*      System variables
**********************************/

uint8 `$INSTANCE_NAME`_initVar = 0u; /* Defines if component was initialized */

/* Status and state variables */
volatile uint8 `$INSTANCE_NAME`_curStatus; /* Current status of the component */
volatile uint8 `$INSTANCE_NAME`_curState;  /* Current state of state machine */

/* Primary slave address variables */
volatile uint8* `$INSTANCE_NAME`_dataPtrS1; /* Pointer to data buffer 1 */
volatile uint16 `$INSTANCE_NAME`_bufSizeS1; /* Size of buffer 1 in bytes */
volatile uint16 `$INSTANCE_NAME`_wrProtectS1; /* Start index of write protected area in buffer 1 */
volatile `$BitWidthReplacementString`  `$INSTANCE_NAME`_rwOffsetS1; /* Current offset within buffer 1 */
volatile `$BitWidthReplacementString`  `$INSTANCE_NAME`_rwIndexS1;  /* Current index within buffer 1 */

/* Secondary slave address variables */
#if(`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)
    volatile uint8  `$INSTANCE_NAME`_addrS1; /* Primary slave address: software comparison */
    volatile uint8  `$INSTANCE_NAME`_addrS2; /* Secondary slave address: software comparison */
    volatile uint8* `$INSTANCE_NAME`_dataPtrS2; /* Pointer to data buffer 1 */
    volatile uint16 `$INSTANCE_NAME`_bufSizeS2; /* Size of buffer 2 in bytes */
    volatile uint16 `$INSTANCE_NAME`_wrProtectS2; /* Start index of write protected area in buffer 2 */
    volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwOffsetS2; /* Current offset within buffer 2 */
    volatile `$BitWidthReplacementString` `$INSTANCE_NAME`_rwIndexS2;  /* Current index within buffer 2 */
#endif  /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the Configure dialog
*  settings. It is not necessary to call EZI2C_Init() because the EZI2C_Start()
*  API calls this function, which is the preferred method to begin component
*  operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - It is used to indicate the initial configuration
*  of this component.  The variable is initialized to zero and set to 1
*  the first time `$INSTANCE_NAME`_Start() is called. This allows component  !
*  initialization without re-initialization in all subsequent calls
*  to the `$INSTANCE_NAME`_Start() routine.
*
*  `$INSTANCE_NAME`_curStatus - Stores the current status of the component.
*
*  `$INSTANCE_NAME`_curState- Stores the current state of an I2C state machine.
*
*  `$INSTANCE_NAME`_rwOffsetS1 - The global variable which stores an offset for read
*  and write operations, is set at each write sequence of the first slave
*  address is reset if `$INSTANCE_NAME`_initVar is 0, by
*  `$INSTANCE_NAME`_initVar function call.
*
*  `$INSTANCE_NAME`_rwIndexS1 - The global variable which stores a pointer to the
*  next value to be read or written for the first slave address is reset if
*  `$INSTANCE_NAME`_initVar is 0, by `$INSTANCE_NAME`_initVar function call.
*
* `$INSTANCE_NAME`_wrProtectS1 - The global variable which stores an offset where data
*  is read only for the first slave address is reset if
*  `$INSTANCE_NAME`_initVar is 0, by `$INSTANCE_NAME`_initVar function call.
*
*  `$INSTANCE_NAME`_rwOffsetS2 - The global variable, which stores an offset for read
*  and write operations, is set at each write sequence of the second slave
*  device is reset if `$INSTANCE_NAME`_initVar is 0, by `$INSTANCE_NAME`_initVar
*  function call.
*
*  `$INSTANCE_NAME`_rwIndexS2 - The global variable which stores a pointer to the
*  next value to be read or written for the second slave address is reset if
*  `$INSTANCE_NAME`_initVar is 0, by `$INSTANCE_NAME`_initVar function call.
*
* `$INSTANCE_NAME`_wrProtectS2 - The global variable which stores an offset where data
*  is read only for the second slave address is reset if
*  `$INSTANCE_NAME`_initVar is 0, by `$INSTANCE_NAME`_initVar function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    /* Configure fixed function block */
    `$INSTANCE_NAME`_CFG_REG  = `$INSTANCE_NAME`_DEFAULT_CFG;
    `$INSTANCE_NAME`_XCFG_REG = `$INSTANCE_NAME`_DEFAULT_XCFG;
    `$INSTANCE_NAME`_ADDR_REG = `$INSTANCE_NAME`_DEFAULT_ADDR;
    `$INSTANCE_NAME`_CLKDIV1_REG = `$INSTANCE_NAME`_DEFAULT_CLKDIV1;
    `$INSTANCE_NAME`_CLKDIV2_REG = `$INSTANCE_NAME`_DEFAULT_CLKDIV2;

#if (`$INSTANCE_NAME`_TWO_ADDRESSES == `$INSTANCE_NAME`_ADDRESSES)
    /* Set address variables */
    `$INSTANCE_NAME`_SetAddress1(`$INSTANCE_NAME`_DEFAULT_ADDR1);
    `$INSTANCE_NAME`_SetAddress2(`$INSTANCE_NAME`_DEFAULT_ADDR2);
#endif /* #if (`$INSTANCE_NAME`_TWO_ADDRESSES == `$INSTANCE_NAME`_ADDRESSES) */

    /* Configure interrupt */
    CyIntDisable         (`$INSTANCE_NAME`_ISR_NUMBER);
    CyIntSetPriority     (`$INSTANCE_NAME`_ISR_NUMBER, `$INSTANCE_NAME`_ISR_PRIORITY);
    (void) CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_ISR);

     /* Reset state and status to default */
    `$INSTANCE_NAME`_curState  = `$INSTANCE_NAME`_SM_IDLE;
    `$INSTANCE_NAME`_curStatus = 0u;

    /* Reset all buffer 1 indexes (primary address) */
    `$INSTANCE_NAME`_rwOffsetS1  = 0u;
    `$INSTANCE_NAME`_rwIndexS1   = 0u;
    `$INSTANCE_NAME`_wrProtectS1 = 0u;

#if (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)
    /* Reset all buffer 2 indexes (secondary address) */
    `$INSTANCE_NAME`_rwOffsetS2  = 0u;
    `$INSTANCE_NAME`_rwIndexS2   = 0u;
    `$INSTANCE_NAME`_wrProtectS2 = 0u;
#endif  /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation.Calls EZI2C_EnableInt()
*  to enable the I2C component interrupt. It is not necessary to call
*  EZI2C_Enable() because the EZI2C_Start() API calls this function, which is
*  the preferred method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 intState;

    /* Enable power to block */
    intState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_PM_ACT_CFG_REG  |= `$INSTANCE_NAME`_ACT_PWR_EN;
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;
    CyExitCriticalSection(intState);

    /* Enable interrupt to start operation */
    `$INSTANCE_NAME`_EnableInt();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation. EZI2C_Start(),
*  calls the EZI2C_Init() function, and then calls the EZI2C_Enable() function.
*  It must be executed before I2C bus operation.
*  This function enables the component interrupt because interrupt is required
*  for most component operations.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if (0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u; /* Component initialized */
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables I2C hardware and component interrupt. The I2C bus is released if it
*  was locked up by the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8  intState;
    uint16 blockResetCycles;

    `$INSTANCE_NAME`_DisableInt();

    /* Store registers effected by block disable */
    `$INSTANCE_NAME`_backup.adr     = `$INSTANCE_NAME`_ADDR_REG;
    `$INSTANCE_NAME`_backup.clkDiv1 = `$INSTANCE_NAME`_CLKDIV1_REG;
    `$INSTANCE_NAME`_backup.clkDiv2 = `$INSTANCE_NAME`_CLKDIV2_REG;

    /* Calculate number of cycles to reset block */
    blockResetCycles = ((uint16) ((uint16) `$INSTANCE_NAME`_CLKDIV2_REG << 8u) | `$INSTANCE_NAME`_CLKDIV1_REG) + 1u;

    /* Disable block */
    `$INSTANCE_NAME`_CFG_REG &= (uint8) ~`$INSTANCE_NAME`_CFG_EN_SLAVE;
    /* Wait for block reset before disable power */
    CyDelayCycles((uint32) blockResetCycles);

    /* Disable power to block */
    intState = CyEnterCriticalSection();
    `$INSTANCE_NAME`_PM_ACT_CFG_REG  &= (uint8) ~`$INSTANCE_NAME`_ACT_PWR_EN;
    `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8) ~`$INSTANCE_NAME`_STBY_PWR_EN;
    CyExitCriticalSection(intState);

    /* Enable block */
    `$INSTANCE_NAME`_CFG_REG |= (uint8) `$INSTANCE_NAME`_CFG_EN_SLAVE;

    /* Restore registers effected by block disable. Ticket ID#198004 */
    `$INSTANCE_NAME`_ADDR_REG    = `$INSTANCE_NAME`_backup.adr;
    `$INSTANCE_NAME`_ADDR_REG    = `$INSTANCE_NAME`_backup.adr;
    `$INSTANCE_NAME`_CLKDIV1_REG = `$INSTANCE_NAME`_backup.clkDiv1;
    `$INSTANCE_NAME`_CLKDIV2_REG = `$INSTANCE_NAME`_backup.clkDiv2;

    `$INSTANCE_NAME`_ClearPendingInt();

    /* Reset state and status to default */
    `$INSTANCE_NAME`_curState  = `$INSTANCE_NAME`_SM_IDLE;
    `$INSTANCE_NAME`_curStatus = 0u;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetAddress1
********************************************************************************
*
* Summary:
*  Sets the primary I2C slave address. This address is used by the master to
*  access the primary data buffer.
*
* Parameters:
*  address: Primary I2C slave address.
*           This address is the 7-bit right-justified slave address and does not
*           include the R/W bit.
*           This value can be any address between 0 and 127 (0x00 to 0x7F).
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_addrS1 - A new slave address for the first slave device is
*  saved in it, if the component is configured to act as two slave devices.
*
* Reentrant:
*  No, if two addresses are used.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAddress1(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetAddress1")`
{
#if (`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES)
    `$INSTANCE_NAME`_ADDR_REG = (address & `$INSTANCE_NAME`_SADDR_MASK);
#else
    `$INSTANCE_NAME`_addrS1   = (address & `$INSTANCE_NAME`_SADDR_MASK);
#endif /* (`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetAddress1
********************************************************************************
*
* Summary:
*  Returns the primary I2C slave address.
*  This address is the 7-bit right-justified slave address and does not include
*  the R/W bit.
*
* Parameters:
*  None.
*
* Return:
*  Primary I2C slave address.
*
* Global variables:
*  `$INSTANCE_NAME`_addrS1 - If component is configured to has two slave
*  addresses than the primary address is saved here, otherwise the address is written to
*  the register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetAddress1(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAddress1")`
{
#if (`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES)
    return (`$INSTANCE_NAME`_ADDR_REG);
#else
    return (`$INSTANCE_NAME`_addrS1);
#endif /* (`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetActivity
********************************************************************************
*
* Summary:
*  Returns a non-zero value if an I2C read or write cycle has occurred since
*  the last time this function was called. The activity flag resets to zero at
*  the end of this function call.
*  The Read and Write busy flags are cleared when read, but the “BUSY” flag is
*  only cleared when slave is free (i.e master finishes communication with
*  slave generating Stop or repeated Start condition).
*
* Parameters:
*  None
*
* Return:
*  Status of I2C activity.
*
*   `$INSTANCE_NAME`_STATUS_READ1   Set if a Read sequence is detected for the first
*                                   address. Cleared when the status is read.
*
*   `$INSTANCE_NAME`_STATUS_WRITE1  Set if a Write sequence is detected for the first
*                                   address. Cleared when the status is  read.
*
*   `$INSTANCE_NAME`_STATUS_READ2   Set if a Read sequence is detected for the second
*                                   address (if enabled). Cleared when the status
*                                   read.
*
*   `$INSTANCE_NAME`_STATUS_WRITE2  Set if a Write sequence is detected for the second
*                                   address (if enabled). Cleared when the status is
*                                   read.
*
*   `$INSTANCE_NAME`_STATUS_BUSY    Set when the master starts communication with
*                                   the slave (the slave is addressed with Start or
*                                   repeated Start) and cleared when the master
*                                   finishes communication (a Stop or repeated
*                                   Start condition is generated).
*
*   `$INSTANCE_NAME`_STATUS_ERR     Set when the I2C hardware is detected, cleared
*                                   when the status is read.
*
* Global variables:
*  `$INSTANCE_NAME`_curStatus - The global variable which stores the current
*  component status.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetActivity(void) `=ReentrantKeil($INSTANCE_NAME . "_GetActivity")`
{
    uint8 tmpStatus;

    `$INSTANCE_NAME`_DisableInt(); /* Lock from component interrupt */

    tmpStatus = `$INSTANCE_NAME`_curStatus;
    /* Clear status bits. Do not touch busy status */
    `$INSTANCE_NAME`_curStatus &= `$INSTANCE_NAME`_STATUS_BUSY;

    `$INSTANCE_NAME`_EnableInt(); /* Release lock */

    return (tmpStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBuffer1
********************************************************************************
*
* Summary:
*  Sets up the data buffer to be exposed to the master on a primary slave
*  address request.
*
* Parameters:
*  bufSize:    Size of the buffer in bytes.
*  rwBoundary: Number of data bytes starting from the beginning of the buffer
*              with read and write access. Data bytes located at offset
*              rwBoundary or greater are read only.
*              This value must be less than or equal to the buffer size.
*  dataPtr:    Pointer to the data buffer.
*
* Return:
*  None.
*
* Global variables:
*  `$INSTANCE_NAME`_dataPtrS1 - Stores the pointer to the data exposed to an I2C
*  master for the first slave address, is modified with the the new pointer to    the    ?? no sense without a comma
*  data passed by the function parameter.
*
*  `$INSTANCE_NAME`_rwOffsetS1 - Stores an offset for read and write operations, is
*  modified at each write sequence of the first slave address is?? reset.   ?
*
*  `$INSTANCE_NAME`_rwIndexS1 - Stores the pointer to the next value to be read or
*  written for the first slave address is?? set to 0.  ??
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetBuffer1(uint16 bufSize, uint16 rwBoundary, volatile uint8 * dataPtr) `=ReentrantKeil($INSTANCE_NAME . "_SetBuffer1")`
{
    `$INSTANCE_NAME`_DisableInt(); /* Lock from component interrupt */

    if (NULL != dataPtr)
    {
        /* Configure buffer 1 */
        `$INSTANCE_NAME`_dataPtrS1   = dataPtr;
        `$INSTANCE_NAME`_bufSizeS1   = bufSize;
        `$INSTANCE_NAME`_wrProtectS1 = rwBoundary;
    }

    /* Clear buffer offset and index */
    `$INSTANCE_NAME`_rwOffsetS1 = 0u;
    `$INSTANCE_NAME`_rwIndexS1  = 0u;

    `$INSTANCE_NAME`_EnableInt(); /* Release lock */
}


#if (`$INSTANCE_NAME`_TWO_ADDRESSES == `$INSTANCE_NAME`_ADDRESSES)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetBuffer2
    ********************************************************************************
    *
    * Summary:
    *  Sets up the data buffer to be exposed to the master on a secondary slave
    *  address request.
    *
    * Parameters:
    *  bufSize:    Size of the buffer in bytes.
    *  rwBoundary: Number of data bytes starting from the beginning of the buffer
    *              with read and write access. Data bytes located at offset
    *              rwBoundary or greater are read only.
    *              This value must be less than or equal to the buffer size.
    *  dataPtr:    Pointer to the data buffer.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_dataPtrS2 - Stores the pointer to the data exposed to an I2C
    *  master for the second slave address, is modified with the the new pointer to the
    *  data, passed by the unction parameter.
    *
    *  `$INSTANCE_NAME`_rwOffsetS2 - Stores teh offset for read and write operations,
    *  is modified at each write sequence of the second slave address is?? reset.  ??
    *
    *  `$INSTANCE_NAME`_rwIndexS2 - Stores the pointer to the next value to be read or
    *  written for the second slave address is?? set to 0.  ??
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetBuffer2(uint16 bufSize, uint16 rwBoundary, volatile uint8 * dataPtr) `=ReentrantKeil($INSTANCE_NAME . "_SetBuffer2")`
    {
        `$INSTANCE_NAME`_DisableInt(); /* Lock from component interrupt */

        if (NULL != dataPtr)
        {
            /* Configure buffer 2 */
            `$INSTANCE_NAME`_dataPtrS2   = dataPtr;
            `$INSTANCE_NAME`_bufSizeS2   = bufSize;
            `$INSTANCE_NAME`_wrProtectS2 = rwBoundary;
        }

        /* Clear buffer offset and index */
        `$INSTANCE_NAME`_rwOffsetS2 = 0u;
        `$INSTANCE_NAME`_rwIndexS2  = 0u;

        `$INSTANCE_NAME`_EnableInt(); /* Release lock */
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the secondary I2C slave address. This address is used by the master to
    *  access the secondary data buffer.
    *
    * Parameters:
    *  address: Secondary I2C slave address.
    *           This address is the 7-bit right-justified slave address and does
    *           not include the R/W bit. This value can be any address between
    *           0 and 127 (0x00 to 0x7F).
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_addrS2 - The secondary slave address is modified.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetAddress2(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetAddress2")`
    {
        `$INSTANCE_NAME`_addrS2 = (address & `$INSTANCE_NAME`_SADDR_MASK);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetAddress2
    ********************************************************************************
    *
    * Summary:
    *  Returns the secondary I2C slave address.
    *  This address is the 7-bit right-justified slave address and does not
    *  include the R/W bit.
    *
    * Parameters:
    *  `$INSTANCE_NAME`_addrS2 - The global variable which stores the second I2C
    *   address.
    *
    * Return:
    *  Secondary I2C slave address.
    *
    * Global variables:
    *  `$INSTANCE_NAME`_addrS2 - The secondary slave address is used.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetAddress2(void) `=ReentrantKeil($INSTANCE_NAME . "_GetAddress2")`
    {
        return (`$INSTANCE_NAME`_addrS2);
    }

#endif  /* (`$INSTANCE_NAME`_TWO_ADDRESSES == `$INSTANCE_NAME`_ADDRESSES) */


/* [] END OF FILE */
