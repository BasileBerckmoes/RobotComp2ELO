/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of APIs for the DVDAC component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_VDAC8.h"
#include "CyDmac.h"
#include "`$INSTANCE_NAME`_DMA_dma.H"

#if(`$INSTANCE_NAME`_INTERNAL_CLOCK_USED)
    #include "`$INSTANCE_NAME`_IntClock.h"
#endif /* `$INSTANCE_NAME`_INTERNAL_CLOCK_USED */


`$ditheredValues`

uint8 `$INSTANCE_NAME`_initVar = 0u;

static uint8 `$INSTANCE_NAME`_dmaChan;
static uint8 `$INSTANCE_NAME`_dmaTd = CY_DMA_INVALID_TD;

static void `$INSTANCE_NAME`_InitDma(void)  `=ReentrantKeil($INSTANCE_NAME . "_InitDma")`;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call `$INSTANCE_NAME`_Init() because
*  the `$INSTANCE_NAME`_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  All registers will be set to values according to the customizer Configure
*  dialog.
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    `$INSTANCE_NAME`_VDAC8_Init();

    if(CY_DMA_INVALID_TD == `$INSTANCE_NAME`_dmaTd)
    {
        `$INSTANCE_NAME`_InitDma();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary to
*  call `$INSTANCE_NAME`_Enable() because the `$INSTANCE_NAME`_Start() API calls
*  this function, which is the preferred method to begin component operation.
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
    (void) CyDmaChEnable(`$INSTANCE_NAME`_dmaChan, 1u);

    #if(`$INSTANCE_NAME`_INTERNAL_CLOCK_USED)
        `$INSTANCE_NAME`_IntClock_Start();
    #endif /* `$INSTANCE_NAME`_INTERNAL_CLOCK_USED */

    `$INSTANCE_NAME`_VDAC8_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  power to the block. The first time the routine is executed, the component is
*  initialized to the configured settings. When called to restart the DVDAC
*  following a `$INSTANCE_NAME`_Stop() call, the current component parameter
*  settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the `$INSTANCE_NAME`_initVar variable is already set, this function only
*  calls the `$INSTANCE_NAME`_Enable() function.
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - indicates whether the DVDAC has been initialized.
*  The variable is initialized to 0 and set to 1 the first time DVDAC_Start()
*  is called. This allows the component to restart without reinitialization
*  after the first call to the `$INSTANCE_NAME`_Start() routine. If
*  reinitialization of the component is required, then the
*  `$INSTANCE_NAME`_Init() function can be called before the
*  `$INSTANCE_NAME`_Start() or `$INSTANCE_NAME`_Enable() function.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* Hardware initiazation only needs to occure the first time */
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
*  Stops the component and turns off the analog blocks in the DVDAC.
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
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    #if(`$INSTANCE_NAME`_INTERNAL_CLOCK_USED)
        `$INSTANCE_NAME`_IntClock_Stop();
    #endif /* `$INSTANCE_NAME`_INTERNAL_CLOCK_USED */

    (void) CyDmaChDisable(`$INSTANCE_NAME`_dmaChan);
    `$INSTANCE_NAME`_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetValue
********************************************************************************
*
* Summary:
*  Sets the DVDACs output. The function populates the SRAM array based on the
*  value and the resolution setting. That array is then transferred to the
*  internal VDAC by DMA.
*
* Parameters:
*  (uint16) value:  The maximum value will be dependent on the resolution
*  selected:
*   Resolution       Valid range
*        9 bits       0x0 - 0x1FE
*       10 bits       0x0 - 0x3FC
*       11 bits       0x0 - 0x7F8
*       12 bits       0x0 - 0xFF0
*
*  This value includes an integer portion and a fractional portion that varies
*  depending on number of bits of resolution:
*   - 9-bits:  1 fractional bit
*   - 10-bits: 2 fractional bits
*   - 11-bits: 3 fractional bits
*   - 12-bits: 4 fractional bits
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetValue(uint16 value) `=ReentrantKeil($INSTANCE_NAME . "_SetValue")`
{
    uint8  lowCount  = (uint8)(value & `$INSTANCE_NAME`_FRACTIONAL_PORTION_MASK);
    uint8 highCount  = (uint8)(value >> `$INSTANCE_NAME`_INTEGER_PORTION_SHIFT);
    uint8 i;


    CYASSERT(value <= `$INSTANCE_NAME`_DVDAC_MAX_VALUE);

    if (`$INSTANCE_NAME`_INTEGER_PORTION_MAX_VALUE == highCount)
    {
        for (i = 0u; i < `$INSTANCE_NAME`_DITHERED_ARRAY_SIZE; i++)
        {
            `$INSTANCE_NAME`_ditheredValues[i] = `$INSTANCE_NAME`_INTEGER_PORTION_MAX_VALUE;
        }
    }
    else
    {
        for(i = 0u; i < `$INSTANCE_NAME`_DITHERED_ARRAY_SIZE; i++)
        {
            if(i < (`$INSTANCE_NAME`_DITHERED_ARRAY_SIZE - lowCount))
            {
                `$INSTANCE_NAME`_ditheredValues[i] = highCount;
            }
            else
            {
                `$INSTANCE_NAME`_ditheredValues[i] = highCount + 1u;
            }
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_InitDma
********************************************************************************
*
* Summary:
*  Configures a DMA transfer of channel values from memory to VDAC.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void `$INSTANCE_NAME`_InitDma(void)  `=ReentrantKeil($INSTANCE_NAME . "_InitDma")`
{
    /***************************************************************************
    * Transfers channel values from SRAM to VDAC register. One byte transfer,
    * each burst requires a request.
    ***************************************************************************/
    `$INSTANCE_NAME`_dmaChan = `$INSTANCE_NAME`_DMA_DmaInitialize(
                                    `$INSTANCE_NAME`_DMA_BYTES_PER_BURST,
                                    `$INSTANCE_NAME`_DMA_REQUEST_PER_BURST,
                                    HI16(`$INSTANCE_NAME`_DMA_SRC_BASE),
                                    HI16(`$INSTANCE_NAME`_DMA_DST_BASE));

    `$INSTANCE_NAME`_dmaTd = CyDmaTdAllocate();


    /***************************************************************************
    * One TD looping on itself, increment the source address, but not the
    * destination address.
    ***************************************************************************/
    (void) CyDmaTdSetConfiguration( `$INSTANCE_NAME`_dmaTd,
                                    `$INSTANCE_NAME`_DITHERED_ARRAY_SIZE,
                                    `$INSTANCE_NAME`_dmaTd,
                                    (uint8) CY_DMA_TD_INC_SRC_ADR);

    /* Transfers the value for each channel from memory to VDAC */
    (void) CyDmaTdSetAddress(   `$INSTANCE_NAME`_dmaTd,
                                LO16((uint32)`$INSTANCE_NAME`_ditheredValues),
                                LO16((uint32)`$INSTANCE_NAME`_VDAC8_Data_PTR));

    (void) CyDmaChSetInitialTd(`$INSTANCE_NAME`_dmaChan, `$INSTANCE_NAME`_dmaTd);
}

/* [] END OF FILE */

