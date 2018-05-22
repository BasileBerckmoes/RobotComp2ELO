/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code for the API of the SM/PM Bus Slave component.
*
*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

/* User section for additional include libraries and variable declarations */
/*`#START LIB_INCLUDE_REGION`*/

/*`#END`*/

uint8 `$INSTANCE_NAME`_initVar = 0u;

/* This is "Operating Memory Register Store" (RAM) */
`$INSTANCE_NAME`_REGS `$INSTANCE_NAME`_regs;

/* Array structure that contains data from last Write transaction.
* Or it acts as place holder for data for Read transaction.
*/
`$INSTANCE_NAME`_TRANSACTION_STRUCT `$INSTANCE_NAME`_transactionData[`$INSTANCE_NAME`_TRANS_QUEUE_SIZE];

/* Defines number of active manual transaction records in Transaction Queue */
volatile uint8 `$INSTANCE_NAME`_trActiveCount = 0u;

static uint16 `$INSTANCE_NAME`_crc;     /* Stores intermediate CRC */

/* SMB Alert mode and Alert Response Address */
#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
    uint8 `$INSTANCE_NAME`_smbAlertMode;
    uint8 `$INSTANCE_NAME`_alertResponseAddress;
#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */

#if (`$INSTANCE_NAME`_SW_ADDR_DECODE)
    uint8 `$INSTANCE_NAME`_address;
#endif /* `$INSTANCE_NAME`_SW_ADDR_DECODE */

/* User section for variable declarations */
/*`#START VAR_DECLARATIONS_REGION`*/

/*`#END`*/

/* Function prototypes */
static uint16 `$INSTANCE_NAME`_CrcCalc(void)                `=ReentrantKeil($INSTANCE_NAME . "_CrcCalc")`;
static void   `$INSTANCE_NAME`_CrcCalcByte(uint8 newByte)   `=ReentrantKeil($INSTANCE_NAME . "_CrcCalcByte")`;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the SM/PM Bus Component with initial values derived from the
*  customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    `$INSTANCE_NAME`_I2C_Init();

     /* On PSoC 3/5LP scl timeout detection is a part of I2C */
    #if(CY_PSOC4)
        `$INSTANCE_NAME`_Timeout_Init();
        `$INSTANCE_NAME`_EnableGeneralCallAddress();
    #endif /* CY_PSOC4 */

    #if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS) 
        `$INSTANCE_NAME`_SetSmbAlert(1u); /* SMBALERT# pin (active low) is de-asserted at startup */
        `$INSTANCE_NAME`_SetSmbAlertMode(`$INSTANCE_NAME`_SMB_ALERT_MODE_INIT);
        `$INSTANCE_NAME`_SetAlertResponseAddress(`$INSTANCE_NAME`_ALERT_RESPONSE_ADDR);
    #endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */
    
    #if (`$INSTANCE_NAME`_SW_ADDR_DECODE)
        `$INSTANCE_NAME`_SetAddress(`$INSTANCE_NAME`_DEFAULT_ADDRESS);
    #endif /* `$INSTANCE_NAME`_SW_ADDR_DECODE */

    (void)CyIntSetVector(`$INSTANCE_NAME`_ISR_NUMBER, &`$INSTANCE_NAME`_ISR);
    (void)CyIntSetVector(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER, &`$INSTANCE_NAME`_TIMEOUT_ISR);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the SM/PMBus Component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    (void) `$INSTANCE_NAME`_RestoreDefaultAll();

    `$INSTANCE_NAME`_I2C_Enable();
    
    /* On PSoC 3/5LP scl timeout detection is part of I2C */
    #if(CY_PSOC4)
        `$INSTANCE_NAME`_Timeout_Enable();
    #endif /* CY_PSOC4 */

    `$INSTANCE_NAME`_EnableInt();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Starts the SM/PM Bus component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified
*  on the first function call.
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the SM/PMBus Component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void  `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    `$INSTANCE_NAME`_I2C_Stop();
    
    /* On PSoC 3/5LP scl timeout detection is part of I2C */
    #if(CY_PSOC4)
        `$INSTANCE_NAME`_Timeout_Stop();
    #endif /* CY_PSOC4 */

    /* Deassert SMBALERT# pin. Signal is active low. */
    #if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
        `$INSTANCE_NAME`_SetSmbAlert(1u);
    #endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetNextTransaction
********************************************************************************
*
* Summary:
*  This function returns a pointer to the next transaction record in the
*  transaction queue. If the queue is empty, the function returns NULL. Only
*  Manual Reads and Writes will be returned by this function, as the component
*  will handle any Auto transactions on the queue. In the case of Writes, it is
*  the responsibility of the user's firmware servicing the Transaction Queue to
*  copy the "payload" to the register store. In the case of Reads, it is the
*  responsibility of the user's firmware to update the contents of the variable
*  for this command in the register store. For both, the user must call
*  `$INSTANCE_NAME`_CompleteTransaction() to free the transaction record.
*
*  Note: that for Read transactions, the length and payload fields are not used
*  for most transaction types. The exception to this is Process call, where the
*  Word from the write phase will be stored in the payload field.
*  The queue size is '1'.
*
* Parameters:
*  None
*
* Return:
*  Pointer to the transaction record or NULL if there are no active records.
*
*******************************************************************************/
`$INSTANCE_NAME`_TRANSACTION_STRUCT * `$INSTANCE_NAME`_GetNextTransaction(void)
                                `=ReentrantKeil($INSTANCE_NAME . "_GetNextTransaction")`
{
    return((`$INSTANCE_NAME`_trActiveCount > 0u) ? &`$INSTANCE_NAME`_transactionData[0u] : NULL);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CompleteTransaction
********************************************************************************
*
* Summary:
*  Causes the component to complete the currently pending transaction at the
*  head of the queue. The user firmware transaction handler calls this function
*  after processing a transaction. This alerts the component code to copy the
*  register variable associated with the pending Read transaction from the
*  register store to the I2C transfer buffer so that the transfer may complete.
*  It also advances the queue. Must be called for Reads and Writes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_CompleteTransaction(void) `=ReentrantKeil($INSTANCE_NAME . "_CompleteTransaction")`
{
    /* Check for read or write transaction */
    if(`$INSTANCE_NAME`_I2C_SM_SL_RD_DATA == `$INSTANCE_NAME`_I2C_state)
    {
        /* Read data from Register store to I2C Buffer */
        `$INSTANCE_NAME`_CompleteRead();
    }

    /* Clear transaction count */
    `$INSTANCE_NAME`_trActiveCount = 0u;

    /* Enable interrupt as manual handling of transaction was done */
    `$INSTANCE_NAME`_I2C_EnableInt();
}

#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_HandleSmbAlertResponse
    ****************************************************************************
    *
    * Summary:
    *  This API is called by the component when the host responds to the Alert
    *  Response Address and the SMBALERT Mode is set to MANUAL_MODE. This
    *  function calls a user provided callback function where you may insert
    *  code to run after the Master has responded. For example, you might update
    *  a status register and de-assert the SMBALERT# pin.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_HandleSmbAlertResponse(void) `=ReentrantKeil($INSTANCE_NAME . "_HandleSmbAlertResponse")`
    {
        /* Place your code between "start" and "end" comment blocks */
        /*`#START SMBUS_ALERT_REGION`*/

        /*`#END`*/
        #ifdef `$INSTANCE_NAME`_HANDLE_SMB_ALERT_RESPONSE_CALLBACK
            `$INSTANCE_NAME`_HandleSmbAlertResponse_Callback();
        #endif /* `$INSTANCE_NAME`_HANDLE_SMB_ALERT_RESPONSE_CALLBACK */
    }

    #if(CY_PSOC4)

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetSmbAlert
    ****************************************************************************
    *
    * Summary:
    *  Sets the SMBALERT# signal to the specified state. If the device
    *  pulled SMBALERT# low, it will acknowledge the ARA with its own 
    *  address. On PSoC 3 and PSoC 5LP this is implemented as function-like
    *  macro and does not require critical section protection.
    *
    * Parameters:
    *  uint8 state: value to set
    *
    * Return:
    *  None
    *
    ***************************************************************************/
    void `$INSTANCE_NAME`_SetSmbAlert(uint8 state) `=ReentrantKeil($INSTANCE_NAME . "_SetSmbAlert")`
    {
        uint8 interruptState;

        interruptState = CyEnterCriticalSection();

        `$INSTANCE_NAME`_SMBALERT_PIN_REG = ((state) == 0u) ?
            (`$INSTANCE_NAME`_SMBALERT_PIN_REG & (uint32) ~`$INSTANCE_NAME`_SMBALERT_PIN_MASK) :
            (`$INSTANCE_NAME`_SMBALERT_PIN_REG | (uint32)  `$INSTANCE_NAME`_SMBALERT_PIN_MASK);

        CyExitCriticalSection(interruptState);
    }

    #endif /* CY_PSOC4 */

#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */

#if(`$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED)

    /***************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetReceiveByteResponse
    ****************************************************************************
    *
    * Summary:
    *  This function is called by the I2C ISR to determine the response byte
    *  when it detects a "Receive Byte" protocol request. This function calls
    *  a user provided callback functions where the user may insert their code
    *  to override the default return value of this function - which is 0xFF.
    *  This function will be called in ISR context. Therefore, the user code
    *  must be fast, non-blocking, and may only call re-entrant functions.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  User-Specified status byte: `$INSTANCE_NAME`_RET_UNDEFINED(0xFF): default
    *                                return value.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_GetReceiveByteResponse(void) `=ReentrantKeil($INSTANCE_NAME . "_GetReceiveByteResponse")`
    {
        uint8 status = `$INSTANCE_NAME`_RET_UNDEFINED;

        /* Place your code between "start" and "end" comment blocks */
        /*`#START RECEIVE_BYTE_REGION`*/

        /*`#END`*/

        #ifdef `$INSTANCE_NAME`_GET_RECEIVE_BYTE_RESPONSE_CALLBACK
            `$INSTANCE_NAME`_GetReceiveByteResponse_Callback();
        #endif /* `$INSTANCE_NAME`_GET_RECEIVE_BYTE_RESPONSE_CALLBACK */

        return(status);
    }

#endif /* `$INSTANCE_NAME`_RECEIVE_BYTE_PROT_ENABLED */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_HandleBusError
********************************************************************************
*
* Summary:
*  This API is called by the component whenever a bus protocol error occurs.
*  Examples of bus errors would be: invalid command, data underflow, and clock
*  stretch violation. This function is only responsible for the aftermath of
*  an error since the component will already handle errors in a deterministic
*  manner. This function is primarily for the purpose of notifying the user's
*  firmware that an error has occurred. For example, in a PMBus device this
*  would give the user's firmware an opportunity to set the appropriate error
*  bit in the STATUS_CML register.
*
* Parameters:
*  errorCode - code of occured error
*   `$INSTANCE_NAME`_ERR_READ_FLAG              (0x01u)
*   `$INSTANCE_NAME`_ERR_RD_TO_MANY_BYTES       (0x02u)
*   `$INSTANCE_NAME`_ERR_WR_TO_MANY_BYTES       (0x04u)
*   `$INSTANCE_NAME`_ERR_UNSUPPORTED_CMD        (0x08u)
*   `$INSTANCE_NAME`_ERR_INVALID_DATA           (0x10u)
*   `$INSTANCE_NAME`_ERR_TIMEOUT                (0x20u)
*   `$INSTANCE_NAME`_ERR_WR_TO_FEW_BYTES        (0x40u)
*   `$INSTANCE_NAME`_ERR_CORRUPTED_DATA         (0x80u)
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_HandleBusError(uint8 errorCode) `=ReentrantKeil($INSTANCE_NAME . "_HandleBusError")`
{
    /* Place your code between "start" and "end" comment blocks */
    /*`#START BUS_ERROR_REGION`*/

    /*`#END`*/

    #ifdef `$INSTANCE_NAME`_HANDLE_BUS_ERROR_CALLBACK
        `$INSTANCE_NAME`_HandleBusError_Callback();
    #endif /* `$INSTANCE_NAME`_HANDLE_BUS_ERROR_CALLBACK */

    /* To suppress "unreferenced variable" warning" */
    if(0u == errorCode)
    {
        errorCode = errorCode;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StoreUserAll
********************************************************************************
*
* Summary:
*  This function saves the RAM Register Store to the User Register Store in
*  Flash. The CRC field in the Register Store data structure is recalculated and
*  updated prior to the save.
*
* Parameters:
*  flashRegs - a pointer to a location where Register Store (RAM) should be 
*              stored.
*
* Return:
*  CYRET_SUCCESS  : Operation is successful
*  CYRET_MEMORY   : Memory related failure
*  CYRET_BAD_PARAM: Invalid parameter value
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_StoreUserAll(const uint8 * flashRegs) `=ReentrantKeil($INSTANCE_NAME . "_StoreUserAll")`
{
    uint8 result = CYRET_SUCCESS;
    
    /* Place your variable declarations between "start" and "end" comment blocks */
    /*`#START STORE_USER_ALL_DECL_REGION`*/

    /*`#END`*/

    #ifdef `$INSTANCE_NAME`_STORE_USER_ALL_DECL_CALLBACK
        `$INSTANCE_NAME`_StoreUserAllDecl_Callback();
    #endif /* `$INSTANCE_NAME`_STORE_USER_ALL_DECL_CALLBACK */
    
    if(NULL != flashRegs)
    {
        /* Disable interrupts to not damage Registers Store that may
        * happen if "Auto" transaction occurs while storing.
        */
        `$INSTANCE_NAME`_DisableInt();
    
        `$INSTANCE_NAME`_regs.FLASH_CRC = `$INSTANCE_NAME`_CrcCalc();
    
        /* Implement your method of storing Operating Memory to Flash in User 
        * section below.
        */
        /* Place your code between "start" and "end" comment blocks */
        /*`#START STORE_USER_ALL_REGION`*/

        /*`#END`*/

        #ifdef `$INSTANCE_NAME`_STORE_USER_ALL_CALLBACK
            `$INSTANCE_NAME`_StoreUserAll_Callback();
        #endif /* `$INSTANCE_NAME`_STORE_USER_ALL_CALLBACK */
        
    
        `$INSTANCE_NAME`_EnableInt();
    }
    else
    {
        result = CYRET_BAD_PARAM;
    }
    return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreUserAll
********************************************************************************
*
* Summary:
*  This function verifies the CRC field of the User Register Store and then
*  copies the contents of the User Register Store to the RAM Register Store.
*
* Parameters:
*  flashRegs - a pointer to a location where Register Store (Flash) is stored.
*
* Return:
*  CYRET_SUCCESS  : Operation is successful
*  CYRET_BAD_DATA : CRC does not match
*  CYRET_BAD_PARAM: Invalid parameter value
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_RestoreUserAll(const uint8 * flashRegs) `=ReentrantKeil($INSTANCE_NAME . "_RestoreUserAll")`
{
    uint8 result;

    if(NULL != flashRegs)
    {
        /* Disable interrupts to not damage Registers Store that may
        * happen if "Auto" transaction occurs while restoring.
        */
        `$INSTANCE_NAME`_DisableInt();
        
        /* Restore Operating memory from Flash */
        (void)memcpy((void *) &`$INSTANCE_NAME`_regs, (`$ConstQualifier`void *)flashRegs, `$LenType``$INSTANCE_NAME`_REGS_SIZE);
        
		/* If the CRC matches then indicate success */
        if (`$INSTANCE_NAME`_regs.FLASH_CRC == `$INSTANCE_NAME`_CrcCalc())
        {
            result = CYRET_SUCCESS;
        }
        else
        {
            result = CYRET_BAD_DATA;
        }
        `$INSTANCE_NAME`_EnableInt();
    }
    else
    {
        result = CYRET_BAD_PARAM;
    }
    return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EraseUserAll
********************************************************************************
*
* Summary:
*  This function verifies the CRC field of the User Register Store and then
*  copies the contents of the User Register Store to the RAM Register Store.
*
* Parameters:
*  None
*
* Return:
*  CYRET_SUCCESS: Operation is successful. Determine your non-SUCCESS status.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_EraseUserAll(void) `=ReentrantKeil($INSTANCE_NAME . "_EraseUserAll")`
{
    uint8 result = CYRET_SUCCESS;
    
    /* Implement your method of erasing Operating Memory in Flash in User 
    * section below.
    */
    /* Place your code between "start" and "end" comment blocks */
    /*`#START ERASE_USER_ALL_REGION`*/

    /*`#END`*/
    
    #ifdef `$INSTANCE_NAME`_ERASE_USER_ALL_CALLBACK
        `$INSTANCE_NAME`_EraseUserAll_Callback();
    #endif /* `$INSTANCE_NAME`_ERASE_USER_ALL_CALLBACK */
    
    return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreDefaultAll
********************************************************************************
*
* Summary:
*  This function verifies the signature field of the Default Register Store and
*  then copies the contents of the Default Register Store to the RAM Register
*  Store.
*
* Parameters:
*  None
*
* Return:
*  CYRET_SUCCESS : Operation is successful
*  CYRET_BAD_DATA: Signature is not valid
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_RestoreDefaultAll(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreDefaultAll")`
{
    uint8 result;

    /* Check signature for validness */
    if(`$INSTANCE_NAME`_SIGNATURE == `$INSTANCE_NAME`_regsDefault.SMBUS_REGS_SIG)
    {
        /* Signature is valid so default register store can be copied into RAM */
        (void)memcpy((void *)&`$INSTANCE_NAME`_regs, (`$ConstQualifier`void *)&`$INSTANCE_NAME`_regsDefault,
            `$LenType``$INSTANCE_NAME`_REGS_SIZE);
        result = CYRET_SUCCESS;
    }
    else
    {
        result = CYRET_BAD_DATA;
    }    

    return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StoreComponentAll
********************************************************************************
*
* Summary:
*  This function should be called to update the parameters of other components
*  in the system with the current PMBus settings. Since this action is very
*  application specific, this function must be user provided.
*
* Parameters:
*  None
*
* Return:
*  CYRET_SUCCESS: Operation is successful. Determine your non-SUCCESS status.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_StoreComponentAll(void) `=ReentrantKeil($INSTANCE_NAME . "_StoreComponentAll")`
{
    uint8 status = CYRET_SUCCESS;

    /* Below are references to commands data of Operating Memory (RAM).
    * They should be used to implement Component Register Store concept.
    * Each parameter can be individually selected and assigned with 
    * desired value(s).
    
      `$StoreComponentAllVar` 
    */

    /* Place your code between "start" and "end" comment blocks */
    /*`#START STORE_COMPONENT_ALL_REGION`*/

    /*`#END`*/

    #ifdef `$INSTANCE_NAME`_STORE_COMPONENT_ALL_CALLBACK
        `$INSTANCE_NAME`_StoreComponentAll_Callback();
    #endif /* `$INSTANCE_NAME`_STORE_COMPONENT_ALL_CALLBACK */

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreComponentAll
********************************************************************************
*
* Summary:
*  This function should be called to update the PMBus Operating Register Store
*  with the current configuration parameters of other components in the system.
*  Since this action is very application specific, this function must be user
*  provided.
*
* Parameters:
*  None
*
* Return:
*  CYRET_SUCCESS: Operation is successful. Determine your non-SUCCESS status.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_RestoreComponentAll(void) `=ReentrantKeil($INSTANCE_NAME . "RestoreComponentAll")`
{
    uint8 status = CYRET_SUCCESS;

    /* Below are references to commands data of Operating Memory (RAM).
    * They should be used to implement Component Register Store concept.
    * Each parameter can be individually selected and assigned with 
    * desired value(s).
    
      `$StoreComponentAllVar` 
    */
    
    /* Place your code between "start" and "end" comment blocks */
    /*`#START RESTORE_COMPONENT_ALL_REGION`*/

    /*`#END`*/

    #ifdef `$INSTANCE_NAME`_RESTORE_COMPONENT_ALL_CALLBACK
        `$INSTANCE_NAME`_RestoreComponentAll_Callback();
    #endif /* `$INSTANCE_NAME`_RESTORE_COMPONENT_ALL_CALLBACK */

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Lin11ToFloat
********************************************************************************
*
* Summary:
*  This function converts the argument "linear11" to a floating point and returns
*  it.
*
* Parameters:
*  uint16 linear11: a number in LINEAR11 format
*
* Return:
*  The linear11 parameter converted to floating point
*
* Theory:
*  linear11 has signed 5-bit exponent (2^15 to 2^-16) and signed 11-bit
*  mantissa (sXX XXXX XXXX).
*
*  32-bit floating point IEEE numbers 8-bit signed exponent, 23-bit mantissa
*   S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF
*   0 1      8 9                    31
*
*******************************************************************************/
float32 `$INSTANCE_NAME`_Lin11ToFloat(uint16 linear11) `=ReentrantKeil($INSTANCE_NAME . "_Lin11ToFloat")`
{
    uint8   manSign;
    uint8   expSign;
    uint8   exponent;
    uint16  mantissa;
    float32 retval;
    uint16  power;

   /* Disassemble linear11 into 4 parts */
    exponent = `$INSTANCE_NAME`_LIN11_TO_EXP(linear11);
    mantissa = `$INSTANCE_NAME`_LIN11_TO_MAN(linear11);
    expSign  = `$INSTANCE_NAME`_LIN11_TO_EXP_SIGN(exponent);
    manSign  = `$INSTANCE_NAME`_LIN11_TO_MAN_SIGN(mantissa);

     /* Convert (-) mantissa to (+) */
    if(manSign != 0u)
    {
        mantissa = `$INSTANCE_NAME`_11BIT_2S_COMPLEMENT(mantissa);
    }

    /* Tossing mantissa into float return value */
    retval = (float32) mantissa;
    if(manSign != 0u)
    {
        retval = -retval;
    }

    /* Convert (-) exponent to (+) */
    if(expSign != 0u)
    {
        exponent = `$INSTANCE_NAME`_5BIT_2S_COMPLEMENT(exponent);
    }

    power = (uint16)1u << exponent;

    /* The max absolute exponent value is explicitly tested to correct
    * overflow that may occur while shifting into 16-bit variable.
    */
    if(exponent == `$INSTANCE_NAME`_MAX_5BIT_EXP)
    {
        retval /= `$INSTANCE_NAME`_MAX_POWER;
    }
    else if(expSign != 0u) /* If negative exponent, decrease retval */
    { 
        retval /= (float32)power;
    }
    else /* Else positive exponent, increase retval */
    {
        retval *= (float32)power;
    }

    return(retval);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FloatToLin11
********************************************************************************
*
* Summary:
*  This function takes the argument "floatvar" (a floating point number) and
*  converts it to a 16-bit LINEAR11 value (11-bit mantissa + 5-bit exponent),
*  which it returns.
*
* Parameters:
*  floatvar: a floating point number
*
* Return:
*  floatvar converted to LINEAR11
*
* Theory:
*  linear11 has signed 5-bit exponent (2^15 to 2^-16) and signed 11-bit
*  mantissa (sXX XXXX XXXX).
*
*  32-bit floating point IEEE numbers 8-bit signed exponent, 23-bit mantissa
*   S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF
*   0 1      8 9                    31
*
*  If E==255 and F!=0, then value = "not a number"
*     E==255 and F==0, then value = +/- Infinity, depending on S
*     0<E<255        then value = 2^(E-127) * (1.F) (implicit leading 1)
*     E==0 and F!=0, then value = 2^( -126) * (0.F)
*     E==0 and F==0, then value = +/- 0.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_FloatToLin11(float32 floatvar) `=ReentrantKeil($INSTANCE_NAME . "_FloatToLin11")`
{
    uint16 mantissa;
    uint8  rawExp;
    int16  exponent;
    uint16 retval;
    uint32 var32;
    
    #if defined(__GNUC__)
        
        /* This is required to avoid GCC warning caused by expression 
        * "var32 = *(uint32*)(&floatvar);". 
        */
        (void)memcpy((void *)&var32, (const void *)&floatvar, sizeof(float32));
    
    #else /* If compiler is not GCC */
    
        /* var32 = floating point number loaded as raw uint32 */
        var32 = *(uint32*)(&floatvar);       /* should auto handle endian issues */

    #endif /* __GNUC__ */
    
    if(0uL == var32)
    {
        /* 0.0 is a special-case floating point number */
        retval = 0u;
    }
    else
    {
        /* Get top 10 bits of mantissa and restore suppressed leading "1" to make
        * 11 bits.
        */
        mantissa = `$INSTANCE_NAME`_FLOAT_10MSB_MAN(var32);        /* Top 10-bit mantissa */
        rawExp = `$INSTANCE_NAME`_FLOAT_EXP(var32);                /* Isolate 8-bit raw exponent */

        /* Convert to "true" signed exponent by subtracting 127 */
        exponent = (int16)rawExp;
        exponent -= `$INSTANCE_NAME`_IEEE754_IMPLICIT_MAGNITUDE;

        /* Linear 11 assumes decimal to far right, so need to decrease exponent
        * by 2^9 (i.e. move decimal 9 places right from 1.x xxxx xxxx to 1x xxxx xxxx.
        */
        exponent -= `$INSTANCE_NAME`_LIN11_EXP_SCALING_FACTOR;

        /* If exponent is < -16, increase it to avoid exceeding 5-bit signed minimum
        * by right-shifting mantissa (possibly throwing away LS bits).
        */
        while(exponent < `$INSTANCE_NAME`_NEG_EXP_MIN)
        {
            ++exponent;
            mantissa >>= 1u;
        }

        if (floatvar < 0.0)
        {
            mantissa = `$INSTANCE_NAME`_11BIT_2S_COMPLEMENT(mantissa);  /* Convert (+) mantissa to (-) */
        }

        /* Assembly linear11 from exponent and mantissa */
        rawExp =  (uint8)exponent;
        retval  = `$INSTANCE_NAME`_EXP_TO_LIN11(rawExp);    /*  5-bit signed exponent */
        retval += `$INSTANCE_NAME`_MAN_TO_LIN11(mantissa);  /* 11-bit signed mantissa */
    }

    return(retval);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Lin16ToFloat
********************************************************************************
*
* Summary:
*  This function converts the argument "linear16" to floating point and returns
*  it. The argument Linear16 contains the mantissa. The argument inExponent is
*  the 5-bit 2's complement exponent to use in the conversion.
*
* Parameters:
*  uint16 linear16: the 16-bit mantissa of a LINEAR16 number
*  int8 inExponent: the 5-bit exponent of a LINEAR16 number. Packed in the
*                   lower 5 bits. 2's complement.
*
* Return:
*  The parameters converted to floating point.
*
*******************************************************************************/
float32 `$INSTANCE_NAME`_Lin16ToFloat(uint16 linear16, int8 inExponent) 
                                                                `=ReentrantKeil($INSTANCE_NAME . "_Lin16ToFloat")`
{
    float32 retval;
    uint16  power;
    uint8   rawExp;
    uint8   expSign;

    /* Start by tossing mantissa (linear16) into a float return value */
    retval = (float32) linear16;
    
    /* Get 5-bit exponent */
    rawExp = (uint8)inExponent & `$INSTANCE_NAME`_EXP_LIN11_MASK;
    expSign = `$INSTANCE_NAME`_LIN11_TO_EXP_SIGN(rawExp);
    if(expSign != 0u)
    {
        rawExp = `$INSTANCE_NAME`_5BIT_2S_COMPLEMENT(rawExp); /* convert (-) exponent to (+)  */
    }
    power = (uint16)1u << rawExp;

    /* The max absolute exponent value is explicitly tested to correct
    * overflow that may occur while shifting into 16-bit variable.
    */
    if(rawExp == `$INSTANCE_NAME`_MAX_5BIT_EXP)
    {
        retval /= `$INSTANCE_NAME`_MAX_POWER;
    }
    else if(expSign != 0u) /* If negative exponent, decrease retval */
    { 
        retval /= (float32)power;
    }
    else /* Else positive exponent, increase retval */
    {
        retval *= (float32)power;
    }
    return(retval);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_FloatToLin16
********************************************************************************
*
* Summary:
*  This function takes the argument "floatvar" (a floating point number) and
*  converts it to a 16-bit LINEAR16 value (16-bit mantissa), which it returns.
*  The argument outExponent is the 5-bit 2's complement exponent to use in the
*  conversion.
*
* Parameters:
*  float floatvar:   a floating point number to be converted to LINEAR16
*  int8 outExponent: user provided 5-bit exponent to use in the conversion.
*
* Return:
*  The parameters converted to LINEAR16
*
*******************************************************************************/
uint16  `$INSTANCE_NAME`_FloatToLin16(float32 floatvar, int8 outExponent)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_FloatToLin16")`
{
    uint16 mantissa;
    uint8  rawExp;
    int16  exponent;
    uint8  roundoff;
    uint32 var32;
    
    #if defined(__GNUC__)
        
        /* This is required to avoid GCC warning caused by expression 
        * "var32 = *(uint32*)(&floatvar);". 
        */
        (void)memcpy((void *)&var32, (const void *)&floatvar, sizeof(float32));
    
    #else /* If compiler is not GCC */
    
        /* var32 = floating point number loaded as raw uint32 */
        var32 = *(uint32*)(&floatvar);       /* should auto handle endian issues */

    #endif /* __GNUC__ */

    /* 0.0 is special-case floating point number */
    if(0uL == var32)
    {
        mantissa = 0u;
    }
    else
    {
        /* Get top 15 bits of mantissa and restore suppressed leading "1" to make
        * 16 bits.
        */
        mantissa = `$INSTANCE_NAME`_FLOAT_16MSB_MAN(var32);
        rawExp   = `$INSTANCE_NAME`_FLOAT_EXP(var32);          /* Isolate 8-bit raw exponent */
        
        /* Convert to "true" signed exponent by subtracting 127 */
        exponent = (int16)rawExp;
        exponent -= `$INSTANCE_NAME`_IEEE754_IMPLICIT_MAGNITUDE;

        /* Linear 16 assumes decimal to far right, so need to decrease exponent
        *  by 2^15 (i.e. move decimal 15 places right from 1.xxx xxxx xxxx xxxx
        *                                               to  1xxx xxxx xxxx xxxx.
        */
        exponent -= `$INSTANCE_NAME`_LIN16_EXP_SCALING_FACTOR;

        /* Adjust mantissa to render caller-specified exponent */
        roundoff = 0u;
        
        /* Extend outExponent sign to 8 bits */
        rawExp = (uint8)outExponent;
        rawExp = `$INSTANCE_NAME`_SIGN_EXTEND(rawExp);
        outExponent = (int8)rawExp;
        
        while(exponent > outExponent)
        {
            --exponent;
            mantissa <<= 1u;                                /* WARNING: may trash value if bit exponent */
        }

        while(exponent < outExponent)
        {
            ++exponent;
            roundoff = (uint8)mantissa & 0x01u;
            mantissa >>= 1u;                                /* WARNING: may lose precision   */
        }

        if(mantissa != `$INSTANCE_NAME`_LIN16_MAN_MAX_VAL)  /* If not 0xFFFFu */
        {
            mantissa += roundoff;
        }
    }
    return(mantissa);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CrcCalc()
********************************************************************************
*
* Summary:
*  Calculates the CRC over the Register Store in RAM.
*
* Parameters:
*  None
*
* Return:
*  A copy of an updated CRC value (can be used or discarded)
*
* Theory:
*  Using non-zero CRC Seed avoids the all-zeros codeword. Changing or not
*  changing (by simply decrementing) the seed with a new firmware release
*  provides a method to re-initialize (or keep unchanged) the EEPROM when the
*  new firmware is initially run.
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_CrcCalc(void)    `=ReentrantKeil($INSTANCE_NAME . "_CrcCalc")`
{
    uint8 * pdat;
    uint16 cnt;
    uint16 size; 

    pdat = (uint8 *) &`$INSTANCE_NAME`_regs;
    
    /* Calculate size of Register store. */
    size = sizeof(`$INSTANCE_NAME`_regs);
    
    `$INSTANCE_NAME`_crc = `$INSTANCE_NAME`_CRC_SEED;

    /* Calculate CRC using each byte from register store. Do not use last two
    * bytes from register store as they hold checksum for this register store.
    */
    for(cnt = 0u; cnt < (size - 2u); ++cnt)
    {
        `$INSTANCE_NAME`_CrcCalcByte(*pdat);
        ++pdat;
    }
    return (`$INSTANCE_NAME`_crc);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CrcCalcByte()
********************************************************************************
*
* Summary:
*  Update the CRC based on a supplied Byte using the CCITT polynomial
*       X^16 + X^12 + X^5 + X^0
*
*  Basic test cases:
*  If CRC = 0, then processing 0x01 yields 0x1021, or X^12+X^5+X^0
*  If CRC = 0, then processing 0x01,0x10,0x21, yields 0 (or no change)
*
* Parameters:
*  uint8 newByte: new 8 bits, MSB = first bit shifted, LSB = final bit shifted
*
* Return:
*  None
*
*  Note:
*   The efficacy of this method is highly dependent on the generator
*   polynomial coefficients.
*
*******************************************************************************/
static void `$INSTANCE_NAME`_CrcCalcByte(uint8 newByte) `=ReentrantKeil($INSTANCE_NAME . "_CrcCalcByte")`
{
    `$INSTANCE_NAME`_crc = (uint8) (`$INSTANCE_NAME`_crc >> `$INSTANCE_NAME`_CRC_BYTE_SHIFT) |
        (uint16)(`$INSTANCE_NAME`_crc << `$INSTANCE_NAME`_CRC_BYTE_SHIFT);
    `$INSTANCE_NAME`_crc ^= newByte;
    `$INSTANCE_NAME`_crc ^= (`$INSTANCE_NAME`_crc & `$INSTANCE_NAME`_CRC_BYTE_MASK) >> 4u;
    `$INSTANCE_NAME`_crc ^= (uint16)(`$INSTANCE_NAME`_crc << 12u);
    `$INSTANCE_NAME`_crc ^= (uint16)((`$INSTANCE_NAME`_crc & `$INSTANCE_NAME`_CRC_BYTE_MASK) << 5u);
}


/* [] END OF FILE */
