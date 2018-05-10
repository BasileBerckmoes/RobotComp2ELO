/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands for the I2S
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "`$INSTANCE_NAME`.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables I2S interface. Starts the generation of the sck and ws outputs.
*  The Tx and Rx directions remain disabled. It is not necessary to call
*  I2S_Enable() because the I2S_Start() routine calls this function, which is
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
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_AUX_CONTROL_REG |= `$INSTANCE_NAME`_CNT_START;
    CyExitCriticalSection(enableInterrupts);

    `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores default I2S configuration provided with customizer.
*  It is not necessary to call I2S_Init() because the I2S_Start() routine calls
*  this function, which is the preferred method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    #if (`$INSTANCE_NAME`_CLIP_DETECT_ENABLE)
        static const uint8 CYCODE `$INSTANCE_NAME`_posThresholds[] = {`$PosThresholds`};
        static const int8  CYCODE `$INSTANCE_NAME`_negThresholds[] = {`$NegThresholds`};
    #endif /* `$INSTANCE_NAME`_CLIP_DETECT_ENABLE */

    #if (`$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION)
        (void)`$INSTANCE_NAME`_SetDataBits(`$INSTANCE_NAME`_DATA_BITS);
    #endif /* `$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION */

    /* Initialize Tx interrupt source selected in customizer */
    #if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
        `$INSTANCE_NAME`_SET_TX_INT_MASK(CH0, `$INSTANCE_NAME`_TX_INT_SOURCE);
        #if (`$INSTANCE_NAME`_TX_STEREO_1_PRESENT)
            `$INSTANCE_NAME`_SET_TX_INT_MASK(CH1, `$INSTANCE_NAME`_TX_INT_SOURCE);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_1_PRESENT */
        #if (`$INSTANCE_NAME`_TX_STEREO_2_PRESENT)
            `$INSTANCE_NAME`_SET_TX_INT_MASK(CH2, `$INSTANCE_NAME`_TX_INT_SOURCE);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_2_PRESENT */
        #if (`$INSTANCE_NAME`_TX_STEREO_3_PRESENT)
            `$INSTANCE_NAME`_SET_TX_INT_MASK(CH3, `$INSTANCE_NAME`_TX_INT_SOURCE);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_3_PRESENT */
        #if (`$INSTANCE_NAME`_TX_STEREO_4_PRESENT)
            `$INSTANCE_NAME`_SET_TX_INT_MASK(CH4, `$INSTANCE_NAME`_TX_INT_SOURCE);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_4_PRESENT */
    #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
    
    /* Initialize Rx interrupt source and clipping thresholds selected in customizer */
    #if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
        `$INSTANCE_NAME`_SET_RX_INT_MASK(CH0, `$INSTANCE_NAME`_RX_INT_SOURCE);
        #if (`$INSTANCE_NAME`_CLIP_DETECT_ENABLE)
            `$INSTANCE_NAME`_SET_POS_THRESHOLD(CH0, `$INSTANCE_NAME`_posThresholds[`$INSTANCE_NAME`_STEREO_0]);
            `$INSTANCE_NAME`_SET_NEG_THRESHOLD(CH0, `$INSTANCE_NAME`_negThresholds[`$INSTANCE_NAME`_STEREO_0]);
        #endif /* `$INSTANCE_NAME`_CLIP_DETECT_ENABLE */
        #if (`$INSTANCE_NAME`_RX_STEREO_1_PRESENT)
            `$INSTANCE_NAME`_SET_RX_INT_MASK(CH1, `$INSTANCE_NAME`_RX_INT_SOURCE);
            #if (`$INSTANCE_NAME`_CLIP_DETECT_ENABLE)
                `$INSTANCE_NAME`_SET_POS_THRESHOLD(CH1, `$INSTANCE_NAME`_posThresholds[`$INSTANCE_NAME`_STEREO_1]);
                `$INSTANCE_NAME`_SET_NEG_THRESHOLD(CH1, `$INSTANCE_NAME`_negThresholds[`$INSTANCE_NAME`_STEREO_1]);
            #endif /* `$INSTANCE_NAME`_CLIP_DETECT_ENABLE */
        #endif /* `$INSTANCE_NAME`_RX_STEREO_1_PRESENT */
        #if (`$INSTANCE_NAME`_RX_STEREO_2_PRESENT)
            `$INSTANCE_NAME`_SET_RX_INT_MASK(CH2, `$INSTANCE_NAME`_RX_INT_SOURCE);
            #if (`$INSTANCE_NAME`_CLIP_DETECT_ENABLE)
                `$INSTANCE_NAME`_SET_POS_THRESHOLD(CH2, `$INSTANCE_NAME`_posThresholds[`$INSTANCE_NAME`_STEREO_2]);
                `$INSTANCE_NAME`_SET_NEG_THRESHOLD(CH2, `$INSTANCE_NAME`_negThresholds[`$INSTANCE_NAME`_STEREO_2]);
            #endif /* `$INSTANCE_NAME`_CLIP_DETECT_ENABLE */
        #endif /* `$INSTANCE_NAME`_RX_STEREO_2_PRESENT */
        #if (`$INSTANCE_NAME`_RX_STEREO_3_PRESENT)
            `$INSTANCE_NAME`_SET_RX_INT_MASK(CH3, `$INSTANCE_NAME`_RX_INT_SOURCE);
            #if (`$INSTANCE_NAME`_CLIP_DETECT_ENABLE)
                `$INSTANCE_NAME`_SET_POS_THRESHOLD(CH3, `$INSTANCE_NAME`_posThresholds[`$INSTANCE_NAME`_STEREO_3]);
                `$INSTANCE_NAME`_SET_NEG_THRESHOLD(CH3, `$INSTANCE_NAME`_negThresholds[`$INSTANCE_NAME`_STEREO_3]);
            #endif /* `$INSTANCE_NAME`_CLIP_DETECT_ENABLE */
        #endif /* `$INSTANCE_NAME`_RX_STEREO_3_PRESENT */
        #if (`$INSTANCE_NAME`_RX_STEREO_4_PRESENT)
            `$INSTANCE_NAME`_SET_RX_INT_MASK(CH4, `$INSTANCE_NAME`_RX_INT_SOURCE);
            #if (`$INSTANCE_NAME`_CLIP_DETECT_ENABLE)
                `$INSTANCE_NAME`_SET_POS_THRESHOLD(CH4, `$INSTANCE_NAME`_posThresholds[`$INSTANCE_NAME`_STEREO_4]);
                `$INSTANCE_NAME`_SET_NEG_THRESHOLD(CH4, `$INSTANCE_NAME`_negThresholds[`$INSTANCE_NAME`_STEREO_4]);
            #endif /* `$INSTANCE_NAME`_CLIP_DETECT_ENABLE */
        #endif /* `$INSTANCE_NAME`_RX_STEREO_4_PRESENT */
    #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Starts the I2S interface. Starts the generation of the sck and ws outputs.
*  The Tx and Rx directions remain disabled.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
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
*  Disables the I2S interface. The sck and ws outputs are set to 0. The Tx and
*  Rx directions are disabled and their FIFOs are cleared.
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
    uint8 enableInterrupts;

    `$INSTANCE_NAME`_CONTROL_REG &= (uint8)~`$INSTANCE_NAME`_EN;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_AUX_CONTROL_REG &= (uint8)~`$INSTANCE_NAME`_CNT_START;
    CyExitCriticalSection(enableInterrupts);

    /* Clear counter value to force reload when component is enabled */
    `$INSTANCE_NAME`_CNT_COUNT_REG = 0u;

    #if (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
        `$INSTANCE_NAME`_DisableTx();
        `$INSTANCE_NAME`_ClearTxFIFO();
    #endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */
    
    #if (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
        `$INSTANCE_NAME`_DisableRx();
        `$INSTANCE_NAME`_ClearRxFIFO();
    #endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */
}

#if (`$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetDataBits
    ********************************************************************************
    *
    * Summary:
    *  Sets the number of data bits for each sample. The component must be stopped
    *  before calling this API.
    *
    * Parameters:
    *  dataBits: the number of data bits for each sample. Valid values - 8/16/24/32.
    *  If Tx or Rx byte swapping is enabled, valid values are 16 and 24.
    *
    * Return:
    *  CYRET_SUCCESS  : Operation is successful
    *  CYRET_BAD_PARAM: Invalid parameter value
    *
    * Side effects:
    *  Calling this API while the component is operating may cause unexpected
    *  behavior.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_SetDataBits(uint8 dataBits)   `=ReentrantKeil($INSTANCE_NAME . "_SetDataBits")`
    {
        cystatus status;

        CYASSERT((dataBits >= `$INSTANCE_NAME`_MIN_DATA_BITS) && (dataBits <= `$INSTANCE_NAME`_MAX_DATA_BITS));

        status = CYRET_SUCCESS;
        /* The component must be stopped prior calling this API. Therefore
        * all the control bits except the bits modified are zeros.
        */
        switch(dataBits)
        {
        case `$INSTANCE_NAME`_8BIT_DATA:
            `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_8BIT_MODE;
            break;
        case `$INSTANCE_NAME`_16BIT_DATA:
            `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_16BIT_MODE;
            break;
        case `$INSTANCE_NAME`_24BIT_DATA:
            `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_24BIT_MODE;
            break;
        case `$INSTANCE_NAME`_32BIT_DATA:
            `$INSTANCE_NAME`_CONTROL_REG = `$INSTANCE_NAME`_32BIT_MODE;
            break;
        default: status = CYRET_BAD_PARAM;
            break;
        }

        return (status);
    }

#endif /* `$INSTANCE_NAME`_DYNAMIC_BIT_RESOLUTION */

#if(`$INSTANCE_NAME`_TX_DIRECTION_ENABLE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnableTx
    ********************************************************************************
    *
    * Summary:
    *  Enables the Tx direction of the I2S interface.  At the next word
    *  select falling edge transmission will begin.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EnableTx(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableTx")`
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_TX_STS0_1_ACTL_REG |= `$INSTANCE_NAME`_INT_EN;
        #ifdef `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG
            `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG |= `$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG */
        #ifdef `$INSTANCE_NAME`_TX_STS4_ACTL_REG
            `$INSTANCE_NAME`_TX_STS4_ACTL_REG |= `$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_TX_STS4_ACTL_REG */
        CyExitCriticalSection(enableInterrupts);
        
        `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_TX_EN;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DisableTx
    ********************************************************************************
    *
    * Summary:
    *  Disables the Tx direction of the I2S interface.  At the next word
    *  select falling edge transmission of data will stop and a constant 0 value
    *  will be transmitted.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_DisableTx(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableTx")`
    {
        uint8 enableInterrupts;

        `$INSTANCE_NAME`_CONTROL_REG &= (uint8)~`$INSTANCE_NAME`_TX_EN;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_TX_STS0_1_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_INT_EN;
        #ifdef `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG
            `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_TX_STS2_3_ACTL_REG */
        #ifdef `$INSTANCE_NAME`_TX_STS4_ACTL_REG
            `$INSTANCE_NAME`_TX_STS4_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_TX_STS4_ACTL_REG */
        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ClearTxFIFO
    ********************************************************************************
    *
    * Summary:
    *  Clears out the FIFOs for all Tx channels. Any data present in the FIFO will
    *  not be sent. This call should be made only when the Tx direction is disabled.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ClearTxFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearTxFIFO")`
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_CLEAR_TX_FIFO(CH0);
        #if (`$INSTANCE_NAME`_TX_STEREO_1_PRESENT)
            `$INSTANCE_NAME`_CLEAR_TX_FIFO(CH1);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_1_PRESENT */
        #if (`$INSTANCE_NAME`_TX_STEREO_2_PRESENT)
            `$INSTANCE_NAME`_CLEAR_TX_FIFO(CH2);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_2_PRESENT */
        #if (`$INSTANCE_NAME`_TX_STEREO_3_PRESENT)
            `$INSTANCE_NAME`_CLEAR_TX_FIFO(CH3);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_3_PRESENT */
        #if (`$INSTANCE_NAME`_TX_STEREO_4_PRESENT)
            `$INSTANCE_NAME`_CLEAR_TX_FIFO(CH4);
        #endif /* `$INSTANCE_NAME`_TX_STEREO_4_PRESENT */
        CyExitCriticalSection(enableInterrupts);
    }

#endif /* (`$INSTANCE_NAME`_TX_DIRECTION_ENABLE) */


#if(`$INSTANCE_NAME`_RX_DIRECTION_ENABLE)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnableRx
    ********************************************************************************
    *
    * Summary:
    *  Enables the Rx direction of the I2S interface.  At the next word
    *  select falling edge reception of data will begin.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EnableRx(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableRx")`
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_RX_STS0_1_ACTL_REG |= `$INSTANCE_NAME`_INT_EN;
        #ifdef `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG
            `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG |= `$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG */
        #ifdef `$INSTANCE_NAME`_RX_STS4_ACTL_REG
            `$INSTANCE_NAME`_RX_STS4_ACTL_REG |= `$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_RX_STS4_ACTL_REG */
        CyExitCriticalSection(enableInterrupts);
        
        `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_RX_EN;
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_DisableRx
    ********************************************************************************
    *
    * Summary:
    *  Disables the Rx direction of the I2S interface.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_DisableRx(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableRx")`
    {
        uint8 enableInterrupts;

        `$INSTANCE_NAME`_CONTROL_REG &= (uint8)~`$INSTANCE_NAME`_RX_EN;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_RX_STS0_1_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_INT_EN;
        #ifdef `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG
            `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_RX_STS2_3_ACTL_REG */
        #ifdef `$INSTANCE_NAME`_RX_STS4_ACTL_REG
            `$INSTANCE_NAME`_RX_STS4_ACTL_REG &= (uint8)~`$INSTANCE_NAME`_INT_EN;
        #endif /* `$INSTANCE_NAME`_RX_STS4_ACTL_REG */
        CyExitCriticalSection(enableInterrupts);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_ClearRxFIFO
    ********************************************************************************
    *
    * Summary:
    *  Clears out the Rx FIFO.  Any data present in the FIFO will be lost.
    *  This call should be made only when the Rx direction is disabled.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_ClearRxFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearRxFIFO")`
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        `$INSTANCE_NAME`_CLEAR_RX_FIFO(CH0);
        #if (`$INSTANCE_NAME`_RX_STEREO_1_PRESENT)
            `$INSTANCE_NAME`_CLEAR_RX_FIFO(CH1);
        #endif /* `$INSTANCE_NAME`_RX_STEREO_1_PRESENT */
        #if (`$INSTANCE_NAME`_RX_STEREO_2_PRESENT)
            `$INSTANCE_NAME`_CLEAR_RX_FIFO(CH2);
        #endif /* `$INSTANCE_NAME`_RX_STEREO_2_PRESENT */
        #if (`$INSTANCE_NAME`_RX_STEREO_3_PRESENT)
            `$INSTANCE_NAME`_CLEAR_RX_FIFO(CH3);
        #endif /* `$INSTANCE_NAME`_RX_STEREO_3_PRESENT */
        #if (`$INSTANCE_NAME`_RX_STEREO_4_PRESENT)
            `$INSTANCE_NAME`_CLEAR_RX_FIFO(CH4);
        #endif /* `$INSTANCE_NAME`_RX_STEREO_4_PRESENT */
        CyExitCriticalSection(enableInterrupts);
    }
#endif /* (`$INSTANCE_NAME`_RX_DIRECTION_ENABLE) */


/* [] END OF FILE */
