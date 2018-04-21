/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands for the S/PDIF TX
*  component.
*
* Note:
*
*******************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_PVT.h"

uint8 `$INSTANCE_NAME`_initVar = 0u;

#if(0u != `$INSTANCE_NAME`_MANAGED_DMA)

    /* Channel status streams used for DMA transfer */
    volatile uint8 `$INSTANCE_NAME`_cstStream0[`$INSTANCE_NAME`_CST_LENGTH];
    volatile uint8 `$INSTANCE_NAME`_cstStream1[`$INSTANCE_NAME`_CST_LENGTH];

    /* Channel status streams to change from API at run time */
    volatile uint8 `$INSTANCE_NAME`_wrkCstStream0[`$INSTANCE_NAME`_CST_LENGTH];
    volatile uint8 `$INSTANCE_NAME`_wrkCstStream1[`$INSTANCE_NAME`_CST_LENGTH];

    /* Buffer offset variables */
    volatile uint8 `$INSTANCE_NAME`_cst0BufOffset = 0u;
    volatile uint8 `$INSTANCE_NAME`_cst1BufOffset = 0u;

    /* Cst DMA channels and transfer descriptors */
    static uint8 `$INSTANCE_NAME`_cst0Chan;
    static uint8 `$INSTANCE_NAME`_cst1Chan;

    static uint8 `$INSTANCE_NAME`_cst0Td[2u] = {CY_DMA_INVALID_TD, CY_DMA_INVALID_TD};
    static uint8 `$INSTANCE_NAME`_cst1Td[2u] = {CY_DMA_INVALID_TD, CY_DMA_INVALID_TD};

    /* Function prototype to set/release DMA */
    static void `$INSTANCE_NAME`_CstDmaInit(void)       `=ReentrantKeil($INSTANCE_NAME . "_CstDmaInit")`;
    static void `$INSTANCE_NAME`_CstDmaRelease(void)    `=ReentrantKeil($INSTANCE_NAME . "_CstDmaRelease")`;

#endif /* 0u != `$INSTANCE_NAME`_MANAGED_DMA */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables S/PDIF interface. Starts the generation of the S/PDIF output with
*  channel status, but the audio data is set to all 0's. This allows the S/PDIF
*  receiver to lock on to the component's clock.
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
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_BCNT_AUX_CTL_REG   |= `$INSTANCE_NAME`_BCNT_EN;    /* Bit counter enabling */
    `$INSTANCE_NAME`_STATUS_AUX_CTL_REG |= `$INSTANCE_NAME`_INT_EN;     /* Interrupt generation enabling */
    CyExitCriticalSection(enableInterrupts);

    #if(0u != `$INSTANCE_NAME`_MANAGED_DMA)
        /* Enable channel status ISRs */
        CyIntEnable(`$INSTANCE_NAME`_CST_0_ISR_NUMBER);
        CyIntEnable(`$INSTANCE_NAME`_CST_1_ISR_NUMBER);

        /* Prepare and enable channel status DMA transfer */
        `$INSTANCE_NAME`_CstDmaInit();

        while(0u != (`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_CHST_FIFOS_NOT_FULL))
        {
            ; /* Wait for DMA fills status FIFOs to proceed */
        }
    #endif /* 0u != `$INSTANCE_NAME`_MANAGED_DMA */

    `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_ENBL;
}


#if (0u != `$INSTANCE_NAME`_MANAGED_DMA)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CstDmaInit
    ********************************************************************************
    *
    * Summary:
    *  Inits channel status DMA transfer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_cst0Chan - DMA Channel to be used for Channel 0 Status
    *     DMA transfer.
    *  `$INSTANCE_NAME`_cst1Chan - DMA Channel to be used for Channel 1 Status
    *     DMA transfer.
    *  `$INSTANCE_NAME`_cst0Td[] - TD set to be used for Channel 0 Status DMA
    *     transfer.
    *  `$INSTANCE_NAME`_cst1Td[] - TD set to be used for Channel 1 Status DMA
    *     transfer.
    *  `$INSTANCE_NAME`_cstStream0[] - Channel 0 Status stream. Used as the source
    *     buffer for Channel 0 Status DMA. Modified when the data is copied for the
    *     first cycle.
    *  `$INSTANCE_NAME`_wrkCstStream0[] - Channel 0 Status intermediate buffer
    *     between API and DMA. This is required to allow changing of Channel Status
    *     at run time. Used when the data is copied for the first cycle.
    *  `$INSTANCE_NAME`_cstStream1[] - Channel 1 Status stream. Used as the source
    *     buffer for Channel 1 Status DMA. Modified when the data is copied for the
    *     first cycle.
    *  `$INSTANCE_NAME`_wrkCstStream1[] - Channel 1 Status intermediate buffer
    *     between API and DMA. This is required to allow changing of Channel Status
    *     at run time. Used when the data is copied for the first cycle.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_CstDmaInit(void) `=ReentrantKeil($INSTANCE_NAME . "_CstDmaInit")`
    {

        /* Copy channels' status values for the first cycle */
        (void) memcpy((void *) `$INSTANCE_NAME`_cstStream0,
                      (void *) `$INSTANCE_NAME`_wrkCstStream0, `$INSTANCE_NAME`_CST_LENGTH);

        (void) memcpy((void *) `$INSTANCE_NAME`_cstStream1,
                      (void *) `$INSTANCE_NAME`_wrkCstStream1, `$INSTANCE_NAME`_CST_LENGTH);

        `$INSTANCE_NAME`_cst0Td[0u] = CyDmaTdAllocate();
        `$INSTANCE_NAME`_cst0Td[1u] = CyDmaTdAllocate();

        `$INSTANCE_NAME`_cst1Td[0u] = CyDmaTdAllocate();
        `$INSTANCE_NAME`_cst1Td[1u] = CyDmaTdAllocate();

        (void) CyDmaTdSetConfiguration(
                `$INSTANCE_NAME`_cst0Td[0u],
                `$INSTANCE_NAME`_CST_HALF_LENGTH,
                `$INSTANCE_NAME`_cst0Td[1u],
                (CY_DMA_TD_INC_SRC_ADR | `$INSTANCE_NAME`_Cst0_DMA__TD_TERMOUT_EN));

        (void) CyDmaTdSetConfiguration(
                `$INSTANCE_NAME`_cst0Td[1u],
                `$INSTANCE_NAME`_CST_HALF_LENGTH,
                `$INSTANCE_NAME`_cst0Td[0u],
                (CY_DMA_TD_INC_SRC_ADR | `$INSTANCE_NAME`_Cst0_DMA__TD_TERMOUT_EN));

        (void) CyDmaTdSetConfiguration(
                `$INSTANCE_NAME`_cst1Td[0u],
                `$INSTANCE_NAME`_CST_HALF_LENGTH,
                `$INSTANCE_NAME`_cst1Td[1u],
                (CY_DMA_TD_INC_SRC_ADR | `$INSTANCE_NAME`_Cst1_DMA__TD_TERMOUT_EN));

        (void) CyDmaTdSetConfiguration(
                `$INSTANCE_NAME`_cst1Td[1u],
                `$INSTANCE_NAME`_CST_HALF_LENGTH,
                `$INSTANCE_NAME`_cst1Td[0u],
                (CY_DMA_TD_INC_SRC_ADR | `$INSTANCE_NAME`_Cst1_DMA__TD_TERMOUT_EN));

        (void) CyDmaTdSetAddress(
                `$INSTANCE_NAME`_cst0Td[0u],
                LO16((uint32)`$INSTANCE_NAME`_cstStream0),
                LO16((uint32)`$INSTANCE_NAME`_CST_FIFO_0_PTR));

        (void) CyDmaTdSetAddress(
                `$INSTANCE_NAME`_cst0Td[1u],
                LO16((uint32) (&`$INSTANCE_NAME`_cstStream0[`$INSTANCE_NAME`_CST_HALF_LENGTH])),
                LO16((uint32) `$INSTANCE_NAME`_CST_FIFO_0_PTR));

        (void) CyDmaTdSetAddress(
                `$INSTANCE_NAME`_cst1Td[0u],
                LO16((uint32) `$INSTANCE_NAME`_cstStream1),
                LO16((uint32) `$INSTANCE_NAME`_CST_FIFO_1_PTR));

        (void) CyDmaTdSetAddress(
                `$INSTANCE_NAME`_cst1Td[1u],
                LO16((uint32) (&`$INSTANCE_NAME`_cstStream1[`$INSTANCE_NAME`_CST_HALF_LENGTH])),
                LO16((uint32) `$INSTANCE_NAME`_CST_FIFO_1_PTR));

        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_cst0Chan, `$INSTANCE_NAME`_cst0Td[0u]);
        (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_cst1Chan, `$INSTANCE_NAME`_cst1Td[0u]);

        (void) CyDmaChEnable(`$INSTANCE_NAME`_cst0Chan, 1u);
        (void) CyDmaChEnable(`$INSTANCE_NAME`_cst1Chan, 1u);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_CstDmaRelease
    ********************************************************************************
    *
    * Summary:
    *  Release allocated DMA channels and transfer descriptors.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  `$INSTANCE_NAME`_cst0Chan - DMA Channel to be used for Channel 0 Status
    *     DMA transfer.
    *  `$INSTANCE_NAME`_cst1Chan - DMA Channel to be used for Channel 1 Status
    *     DMA transfer.
    *  `$INSTANCE_NAME`_cst0Td[] - TD set to be used for Channel 0 Status DMA
    *     transfer.
    *  `$INSTANCE_NAME`_cst1Td[] - TD set to be used for Channel 1 Status DMA
    *     transfer.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    static void `$INSTANCE_NAME`_CstDmaRelease(void) `=ReentrantKeil($INSTANCE_NAME . "_CstDmaRelease")`
    {
        /* Disable the managed channel status DMA */
        (void) CyDmaChDisable(`$INSTANCE_NAME`_cst0Chan);
        (void) CyDmaChDisable(`$INSTANCE_NAME`_cst1Chan);

        /* Clear any potential DMA requests and re-reset TD pointers */
        while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_cst0Chan].basic_status[0] & CY_DMA_STATUS_TD_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

        (void) CyDmaChSetRequest(`$INSTANCE_NAME`_cst0Chan, CY_DMA_CPU_TERM_CHAIN);
        (void) CyDmaChEnable    (`$INSTANCE_NAME`_cst0Chan, 1u);

        while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_cst0Chan].basic_cfg[0] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }


        while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_cst1Chan].basic_status[0] & CY_DMA_STATUS_TD_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

        (void) CyDmaChSetRequest(`$INSTANCE_NAME`_cst1Chan, CY_DMA_CPU_TERM_CHAIN);
        (void) CyDmaChEnable    (`$INSTANCE_NAME`_cst1Chan, 1u);

        while(0u != (CY_DMA_CH_STRUCT_PTR[`$INSTANCE_NAME`_cst1Chan].basic_cfg[0] & CY_DMA_STATUS_CHAIN_ACTIVE))
        {
            ; /* Wait for to be cleared */
        }

        /* Release all allocated TDs and mark them as invalid */
        CyDmaTdFree(`$INSTANCE_NAME`_cst0Td[0u]);
        CyDmaTdFree(`$INSTANCE_NAME`_cst0Td[1u]);
        CyDmaTdFree(`$INSTANCE_NAME`_cst1Td[0u]);
        CyDmaTdFree(`$INSTANCE_NAME`_cst1Td[1u]);
        `$INSTANCE_NAME`_cst0Td[0u] = CY_DMA_INVALID_TD;
        `$INSTANCE_NAME`_cst0Td[1u] = CY_DMA_INVALID_TD;
        `$INSTANCE_NAME`_cst1Td[0u] = CY_DMA_INVALID_TD;
        `$INSTANCE_NAME`_cst1Td[1u] = CY_DMA_INVALID_TD;
    }
#endif /* 0u != `$INSTANCE_NAME`_MANAGED_DMA */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the customizer settings for the component including channel
*  status.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_wrkCstStream0[] - Channel 0 Status internal buffer. Modified
*  when default S/PDIF configuration provided with customizer is initialized or
*  restored.
*  `$INSTANCE_NAME`_wrkCstStream1[] - Channel 1 Status internal buffer. Modified
*  when default S/PDIF configuration provided with customizer is initialized or
*  restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    #if(0u != `$INSTANCE_NAME`_MANAGED_DMA)
        /* Channel status set by user in the customizer. Used to initialize the
        *  settings in `$INSTANCE_NAME`_Init() API.
        */
        static const uint8 CYCODE `$INSTANCE_NAME`_initCstStream0[`$INSTANCE_NAME`_CST_LENGTH] = {
            `$StatusDataCh0`
        };
        static const uint8 CYCODE `$INSTANCE_NAME`_initCstStream1[`$INSTANCE_NAME`_CST_LENGTH] = {
            `$StatusDataCh1`
        };
    #endif /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */
    
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    /* Set FIFOs in the Single Buffer Mode */
    `$INSTANCE_NAME`_FCNT_AUX_CTL_REG    |= `$INSTANCE_NAME`_FX_CLEAR;
    `$INSTANCE_NAME`_PREGEN_AUX_CTL_REG  |= `$INSTANCE_NAME`_FX_CLEAR;
    CyExitCriticalSection(enableInterrupts);

    /* Channel status ISR initialization  */
    #if(0u != `$INSTANCE_NAME`_MANAGED_DMA)
        CyIntDisable(`$INSTANCE_NAME`_CST_0_ISR_NUMBER);
        CyIntDisable(`$INSTANCE_NAME`_CST_1_ISR_NUMBER);

        /* Set the ISR to point to the Interrupt processing routines */
        (void) CyIntSetVector(`$INSTANCE_NAME`_CST_0_ISR_NUMBER, &`$INSTANCE_NAME`_Cst0Copy);
        (void) CyIntSetVector(`$INSTANCE_NAME`_CST_1_ISR_NUMBER, &`$INSTANCE_NAME`_Cst1Copy);

        /* Set the priority */
        CyIntSetPriority(`$INSTANCE_NAME`_CST_0_ISR_NUMBER, `$INSTANCE_NAME`_CST_0_ISR_PRIORITY);
        CyIntSetPriority(`$INSTANCE_NAME`_CST_1_ISR_NUMBER, `$INSTANCE_NAME`_CST_1_ISR_PRIORITY);
    #endif /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */

    /* Setup Frame and Block Intervals */
    /* Frame Period */
    `$INSTANCE_NAME`_FRAME_PERIOD_REG = `$INSTANCE_NAME`_FRAME_PERIOD;
    /* Preamble and Post Data Period */
    `$INSTANCE_NAME`_FCNT_PRE_POST_REG = `$INSTANCE_NAME`_PRE_POST_PERIOD;
    /* Audio Sample Word Length */
    `$INSTANCE_NAME`_FCNT_AUDIO_LENGTH_REG = `$INSTANCE_NAME`_AUDIO_DATA_PERIOD;
    /* Number of frames in block */
    `$INSTANCE_NAME`_FCNT_BLOCK_PERIOD_REG = `$INSTANCE_NAME`_BLOCK_PERIOD;

    /* Set Preamble Patterns */
    `$INSTANCE_NAME`_PREGEN_PREX_PTRN_REG = `$INSTANCE_NAME`_PREAMBLE_X_PATTERN;
    `$INSTANCE_NAME`_PREGEN_PREY_PTRN_REG = `$INSTANCE_NAME`_PREAMBLE_Y_PATTERN;
    `$INSTANCE_NAME`_PREGEN_PREZ_PTRN_REG = `$INSTANCE_NAME`_PREAMBLE_Z_PATTERN;

    /* Set Interrupt Mask. By default interrupt generation is allowed only for
    *  error conditions, including audio or channel status FIFOs underflow.
    */
    `$INSTANCE_NAME`_STATUS_MASK_REG = `$INSTANCE_NAME`_DEFAULT_INT_SRC;

    /* Channel Status DMA Config */
    #if(0u != `$INSTANCE_NAME`_MANAGED_DMA)
        /* Init channel status streams */
        (void) memcpy((void *) `$INSTANCE_NAME`_wrkCstStream0,
                      (void *) `$INSTANCE_NAME`_initCstStream0, `$INSTANCE_NAME`_CST_LENGTH);

        (void) memcpy((void *) `$INSTANCE_NAME`_wrkCstStream1,
                      (void *) `$INSTANCE_NAME`_initCstStream1, `$INSTANCE_NAME`_CST_LENGTH);

        /* Init DMA, 1 byte bursts, each burst requires a request */
        `$INSTANCE_NAME`_cst0Chan = `$INSTANCE_NAME`_Cst0_DMA_DmaInitialize(
            `$INSTANCE_NAME`_CST_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_CST_DMA_REQUEST_PER_BURST,
            HI16(`$INSTANCE_NAME`_CST_DMA_SRC_BASE), HI16(`$INSTANCE_NAME`_CST_DMA_DST_BASE));

        `$INSTANCE_NAME`_cst1Chan = `$INSTANCE_NAME`_Cst1_DMA_DmaInitialize(
            `$INSTANCE_NAME`_CST_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_CST_DMA_REQUEST_PER_BURST,
            HI16(`$INSTANCE_NAME`_CST_DMA_SRC_BASE), HI16(`$INSTANCE_NAME`_CST_DMA_DST_BASE));
    #endif /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Starts the S/PDIF interface.
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
*  Disables the S/PDIF interface. The audio data and channel data FIFOs are
*  cleared. If the component is configured to manage channel status DMA, then
*  the DMA channels and TDs are released to the system.
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
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    uint8 enableInterrupts;

    /* Disable audio data transmission */
    `$INSTANCE_NAME`_DisableTx();

    `$INSTANCE_NAME`_CONTROL_REG &= ((uint8) ~`$INSTANCE_NAME`_ENBL);

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_STATUS_AUX_CTL_REG &= ((uint8) ~`$INSTANCE_NAME`_INT_EN);  /* Disable Interrupt generation */
    `$INSTANCE_NAME`_BCNT_AUX_CTL_REG   &= ((uint8) ~`$INSTANCE_NAME`_BCNT_EN); /* Disable Bit counter */
    CyExitCriticalSection(enableInterrupts);

    #if (0u != `$INSTANCE_NAME`_MANAGED_DMA)
        /* Disable channel status ISRs */
        CyIntDisable(`$INSTANCE_NAME`_CST_0_ISR_NUMBER);
        CyIntDisable(`$INSTANCE_NAME`_CST_1_ISR_NUMBER);

        CyIntClearPending(`$INSTANCE_NAME`_CST_0_ISR_NUMBER);
        CyIntClearPending(`$INSTANCE_NAME`_CST_1_ISR_NUMBER);

        /* Clear the buffer offset variables */
        `$INSTANCE_NAME`_cst0BufOffset = 0u;
        `$INSTANCE_NAME`_cst1BufOffset = 0u;
        `$INSTANCE_NAME`_CstDmaRelease();
    #endif /* 0u != `$INSTANCE_NAME`_MANAGED_DMA */

    `$INSTANCE_NAME`_ClearTxFIFO();
    `$INSTANCE_NAME`_ClearCstFIFO();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EnableTx
********************************************************************************
*
* Summary:
*  Enables the audio data output in the S/PDIF bit stream. Transmission will
*  begin at the next X or Z frame.
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
    `$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_TX_EN;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DisableTx
********************************************************************************
*
* Summary:
*  Disables the Tx direction of the the audio output S/PDIF bit stream.
*  Transmission of data will stop at the next rising edge of the clock and a
*  constant 0 value will be transmitted.
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
    `$INSTANCE_NAME`_CONTROL_REG &= ((uint8) ~`$INSTANCE_NAME`_TX_EN);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt source for the S/PDIF. Multiple sources may be ORed
*  together.
*
* Parameters:
*  Byte containing the constant for the selected interrupt sources.
*   `$INSTANCE_NAME`_AUDIO_FIFO_UNDERFLOW
*   `$INSTANCE_NAME`_AUDIO_0_FIFO_NOT_FULL
*   `$INSTANCE_NAME`_AUDIO_1_FIFO_NOT_FULL
*   `$INSTANCE_NAME`_CHST_FIFO_UNDERFLOW
*   `$INSTANCE_NAME`_CHST_0_FIFO_NOT_FULL
*   `$INSTANCE_NAME`_CHST_1_FIFO_NOT_FULL
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetInterruptMode(uint8 interruptSource) `=ReentrantKeil($INSTANCE_NAME . "_SetInterruptMode")`
{
    `$INSTANCE_NAME`_STATUS_MASK_REG = interruptSource;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadStatus
********************************************************************************
*
* Summary:
*  Returns state in the SPDIF status register.
*
* Parameters:
*  None.
*
* Return:
*  State of the SPDIF status register
*   `$INSTANCE_NAME`_AUDIO_FIFO_UNDERFLOW (Clear on Read)
*   `$INSTANCE_NAME`_AUDIO_0_FIFO_NOT_FULL
*   `$INSTANCE_NAME`_AUDIO_1_FIFO_NOT_FULL
*   `$INSTANCE_NAME`_CHST_FIFO_UNDERFLOW (Clear on Read)
*   `$INSTANCE_NAME`_CHST_0_FIFO_NOT_FULL
*   `$INSTANCE_NAME`_CHST_1_FIFO_NOT_FUL
*
* Side Effects:
*  Clears the bits of SPDIF status register that are Clear on Read.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_ReadStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadStatus")`
{
    return(`$INSTANCE_NAME`_STATUS_REG & `$INSTANCE_NAME`_INT_MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteTxByte
********************************************************************************
*
* Summary:
*  Writes a single byte into the specified Audio FIFO.
*
* Parameters:
*  wrData: Byte containing the data to transmit.
*  channelSelect: Byte containing the constant for Channel to write.
*    `$INSTANCE_NAME`_CHANNEL_0 indicates to write to the Channel 0 and
*    `$INSTANCE_NAME`_CHANNEL_1 indicates to write to the Channel 1.
*  In the interleaved mode this parameter is ignored.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteTxByte(uint8 wrData, uint8 channelSelect) `=ReentrantKeil($INSTANCE_NAME . "_WriteTxByte")`
{
    #if(0u != `$INSTANCE_NAME`_DATA_INTERLEAVING)

        if(0u != channelSelect)
        {
            /* Suppress compiler warning */
        }

        `$INSTANCE_NAME`_TX_FIFO_0_REG = wrData;

    #else

        if(`$INSTANCE_NAME`_CHANNEL_0 == channelSelect)
        {
            `$INSTANCE_NAME`_TX_FIFO_0_REG = wrData;
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_1_REG = wrData;
        }

    #endif /* (0u != `$INSTANCE_NAME`_DATA_INTERLEAVING) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearTxFIFO
********************************************************************************
*
* Summary:
*  Clears out the Tx FIFO. Any data present in the FIFO will not be sent. This
*  call should be made only when transmit is disabled. In the case of separated
*  audio mode, both audio FIFOs will be cleared.
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
    `$INSTANCE_NAME`_TX_AUX_CTL_REG |= ((uint8)  `$INSTANCE_NAME`_FX_CLEAR);
    `$INSTANCE_NAME`_TX_AUX_CTL_REG &= ((uint8) ~`$INSTANCE_NAME`_FX_CLEAR);
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteCstByte
********************************************************************************
*
* Summary:
*  Writes a single byte into the specified Channel Status FIFO.
*
* Parameters:
*  wrData: Byte containing the status data to transmit.
*  channelSelect: Byte containing the constant for Channel to write.
*    `$INSTANCE_NAME`_CHANNEL_0 indicates to write to the Channel 0 and
*    `$INSTANCE_NAME`_CHANNEL_1 indicates to write to the Channel 1.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteCstByte(uint8 wrData, uint8 channelSelect) `=ReentrantKeil($INSTANCE_NAME . "_WriteCstByte")`
{
    if(`$INSTANCE_NAME`_CHANNEL_0 == channelSelect)
    {
        `$INSTANCE_NAME`_CST_FIFO_0_REG = wrData;
    }
    else
    {
        `$INSTANCE_NAME`_CST_FIFO_1_REG = wrData;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ClearCstFIFO
********************************************************************************
*
* Summary:
*  Clears out the Channel Status FIFOs. Any data present in either FIFO will not
*  be sent. This call should be made only when the component is stopped.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_ClearCstFIFO(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearCstFIFO")`
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    `$INSTANCE_NAME`_CST_AUX_CTL_REG |= ((uint8)  `$INSTANCE_NAME`_FX_CLEAR);
    `$INSTANCE_NAME`_CST_AUX_CTL_REG &= ((uint8) ~`$INSTANCE_NAME`_FX_CLEAR);
    CyExitCriticalSection(enableInterrupts);
}


#if(0u != `$INSTANCE_NAME`_MANAGED_DMA)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetChannelStatus
    ********************************************************************************
    *
    * Summary:
    *  Sets the values of the channel status at run time. This API is only valid
    *  when the component is managing the DMA.
    *
    * Parameters:
    *  channel: Byte containing the constant for Channel to modify.
    *   `$INSTANCE_NAME`_CHANNEL_0 and `$INSTANCE_NAME`_CHANNEL_1 are used to
    *   specify Channel 0 and Channel 1 respectively.
    *  byte : Byte to modify. This argument should be in range from 0 to 23.
    *  mask : Mask on the byte.
    *  value: Value to set.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetChannelStatus(uint8 channel, uint8 byte, uint8 mask, uint8 value) \
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetChannelStatus")`
    {
        if(`$INSTANCE_NAME`_CHANNEL_0 == channel)
        {
            /* Update of status stream needs to be atomic */
            CyIntDisable(`$INSTANCE_NAME`_CST_0_ISR_NUMBER);
            `$INSTANCE_NAME`_wrkCstStream0[byte] &= ((uint8) ~mask);    /* Clear the applicable bits */
            `$INSTANCE_NAME`_wrkCstStream0[byte] |= ((uint8) value);    /* Set the applicable bits   */
            CyIntEnable(`$INSTANCE_NAME`_CST_0_ISR_NUMBER);
        }
        else
        {
            /* Update of status stream needs to be atomic */
            CyIntDisable(`$INSTANCE_NAME`_CST_1_ISR_NUMBER);
            `$INSTANCE_NAME`_wrkCstStream1[byte] &= ((uint8) ~mask);    /* Clear the applicable bits */
            `$INSTANCE_NAME`_wrkCstStream1[byte] |= ((uint8) value);    /* Set the applicable bits   */
            CyIntEnable(`$INSTANCE_NAME`_CST_1_ISR_NUMBER);
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetFrequency
    ********************************************************************************
    *
    * Summary:
    *  Sets the values of the channel status for a specified frequency and returns
    *  1. This function only works if the component is stopped. If this is called
    *  while the component is started, a zero will be returned and the values will
    *  not be modified. This API is only valid when the component is managing the
    *  DMA.
    *
    * Parameters:
    *  Byte containing the constant for the specified frequency.
    *    `$INSTANCE_NAME`_SPS_UNKNOWN
    *    `$INSTANCE_NAME`_SPS_22KHZ
    *    `$INSTANCE_NAME`_SPS_24KHZ
    *    `$INSTANCE_NAME`_SPS_32KHZ
    *    `$INSTANCE_NAME`_SPS_44KHZ
    *    `$INSTANCE_NAME`_SPS_48KHZ
    *    `$INSTANCE_NAME`_SPS_64KHZ
    *    `$INSTANCE_NAME`_SPS_88KHZ
    *    `$INSTANCE_NAME`_SPS_96KHZ
    *    `$INSTANCE_NAME`_SPS_192KHZ
    *
    * Return:
    *  1 on success.
    *  0 on failure.
    *
    *******************************************************************************/
    uint8 `$INSTANCE_NAME`_SetFrequency(uint8 frequency) `=ReentrantKeil($INSTANCE_NAME . "_SetFrequency")`
    {
        uint8 result;

        result = ((uint8) `$INSTANCE_NAME`_IS_DISABLED);

        /* The values of the channel status should not be modified if the component is started */
        if(0u != result)
        {
            /* Refer to sample frequency constansts: `$INSTANCE_NAME`_SF_freqKHZ  (3u) (0xCFu) (freq) */
            `$INSTANCE_NAME`_SetChannelStatus(`$INSTANCE_NAME`_CHANNEL_0, 3u, 0xCFu, frequency);
            `$INSTANCE_NAME`_SetChannelStatus(`$INSTANCE_NAME`_CHANNEL_1, 3u, 0xCFu, frequency);
        }

        return(result);
    }
#endif /* (0u != `$INSTANCE_NAME`_MANAGED_DMA) */


/* [] END OF FILE */
