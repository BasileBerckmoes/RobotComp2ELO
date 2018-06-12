/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code for the 8-bit Waveform DAC 
*  (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

uint8  `$INSTANCE_NAME`_initVar = 0u;

const uint8 CYCODE `$INSTANCE_NAME`_wave1[`$INSTANCE_NAME`_WAVE1_LENGTH] = { `$Wave1_Data` };
const uint8 CYCODE `$INSTANCE_NAME`_wave2[`$INSTANCE_NAME`_WAVE2_LENGTH] = { `$Wave2_Data` };

static uint8  `$INSTANCE_NAME`_Wave1Chan;
static uint8  `$INSTANCE_NAME`_Wave2Chan;
static uint8  `$INSTANCE_NAME`_Wave1TD;
static uint8  `$INSTANCE_NAME`_Wave2TD;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes component with parameters set in the customizer.
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
	`$INSTANCE_NAME`_`$DacModeReplString`_Init();
	`$INSTANCE_NAME`_`$DacModeReplString`_SetSpeed(`$INSTANCE_NAME`_HIGHSPEED);
	`$INSTANCE_NAME`_`$DacModeReplString`_SetRange(`$INSTANCE_NAME`_DAC_RANGE);

	#if(`$INSTANCE_NAME`_DAC_MODE == `$INSTANCE_NAME`_CURRENT_MODE)
		`$INSTANCE_NAME`_IDAC8_SetPolarity(`$INSTANCE_NAME`_DAC_POL);
	#endif /* `$INSTANCE_NAME`_DAC_MODE == `$INSTANCE_NAME`_CURRENT_MODE */

	#if(`$INSTANCE_NAME`_OUT_MODE == `$INSTANCE_NAME`_BUFFER_MODE)
	   `$INSTANCE_NAME`_BuffAmp_Init();
	#endif /* `$INSTANCE_NAME`_OUT_MODE == `$INSTANCE_NAME`_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	`$INSTANCE_NAME`_Wave1TD = CyDmaTdAllocate();
	`$INSTANCE_NAME`_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	`$INSTANCE_NAME`_Wave1Setup(`$INSTANCE_NAME`_wave1, `$INSTANCE_NAME`_WAVE1_LENGTH) ;
	`$INSTANCE_NAME`_Wave2Setup(`$INSTANCE_NAME`_wave2, `$INSTANCE_NAME`_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(`$INSTANCE_NAME`_DacClk_PHASE)
	   `$INSTANCE_NAME`_DacClk_SetPhase(`$INSTANCE_NAME`_CLK_PHASE_0nS);
	#endif /* defined(`$INSTANCE_NAME`_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
	`$INSTANCE_NAME`_`$DacModeReplString`_Enable();

	#if(`$INSTANCE_NAME`_OUT_MODE == `$INSTANCE_NAME`_BUFFER_MODE)
	   `$INSTANCE_NAME`_BuffAmp_Enable();
	#endif /* `$INSTANCE_NAME`_OUT_MODE == `$INSTANCE_NAME`_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(`$INSTANCE_NAME`_Wave1Chan, 1u);
	(void)CyDmaChEnable(`$INSTANCE_NAME`_Wave2Chan, 1u);
	
	/* set the initial value */
	`$INSTANCE_NAME`_SetValue(0u);
	
	#if(`$INSTANCE_NAME`_CLOCK_SRC == `$INSTANCE_NAME`_CLOCK_INT)  	
	   `$INSTANCE_NAME`_DacClk_Start();
	#endif /* `$INSTANCE_NAME`_CLOCK_SRC == `$INSTANCE_NAME`_CLOCK_INT */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
	/* If not Initialized then initialize all required hardware and software */
	if(`$INSTANCE_NAME`_initVar == 0u)
	{
		`$INSTANCE_NAME`_Init();
		`$INSTANCE_NAME`_initVar = 1u;
	}
	
	`$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartEx
********************************************************************************
*
* Summary:
*  The StartEx function sets pointers and sizes for both waveforms
*  and then starts the component.
*
* Parameters:  
*   uint8 * wavePtr1:     Pointer to the waveform 1 array.
*   uint16  sampleSize1:  The amount of samples in the waveform 1.
*   uint8 * wavePtr2:     Pointer to the waveform 2 array.
*   uint16  sampleSize2:  The amount of samples in the waveform 2.
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void `$INSTANCE_NAME`_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
`=ReentrantKeil($INSTANCE_NAME . "_StartEx")`
{
	`$INSTANCE_NAME`_Wave1Setup(wavePtr1, sampleSize1);
	`$INSTANCE_NAME`_Wave2Setup(wavePtr2, sampleSize2);
	`$INSTANCE_NAME`_Start();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Stops the clock (if internal), disables the DMA channels
*  and powers down the DAC.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
	/* Turn off internal clock, if one present */
	#if(`$INSTANCE_NAME`_CLOCK_SRC == `$INSTANCE_NAME`_CLOCK_INT)  	
	   `$INSTANCE_NAME`_DacClk_Stop();
	#endif /* `$INSTANCE_NAME`_CLOCK_SRC == `$INSTANCE_NAME`_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(`$INSTANCE_NAME`_Wave1Chan);
	(void)CyDmaChDisable(`$INSTANCE_NAME`_Wave2Chan);

	/* Disable power to DAC */
	`$INSTANCE_NAME`_`$DacModeReplString`_Stop();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wave1Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 1.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None 
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
`=ReentrantKeil($INSTANCE_NAME . "_Wave1Setup")`
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (`$INSTANCE_NAME`_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		`$INSTANCE_NAME`_Wave1Chan = `$INSTANCE_NAME`_Wave1_DMA_DmaInitialize(
		`$INSTANCE_NAME`_Wave1_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		`$INSTANCE_NAME`_Wave1Chan = `$INSTANCE_NAME`_Wave1_DMA_DmaInitialize(
		`$INSTANCE_NAME`_Wave1_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(`$INSTANCE_NAME`_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Wave1TD, sampleSize, `$INSTANCE_NAME`_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)`$INSTANCE_NAME`_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(`$INSTANCE_NAME`_Wave1TD, LO16((uint32)wavePtr), LO16(`$INSTANCE_NAME`_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(`$INSTANCE_NAME`_Wave1Chan, `$INSTANCE_NAME`_Wave1TD);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wave2Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 2.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
`=ReentrantKeil($INSTANCE_NAME . "_Wave2Setup")` 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (`$INSTANCE_NAME`_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		`$INSTANCE_NAME`_Wave2Chan = `$INSTANCE_NAME`_Wave2_DMA_DmaInitialize(
		`$INSTANCE_NAME`_Wave2_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		`$INSTANCE_NAME`_Wave2Chan = `$INSTANCE_NAME`_Wave2_DMA_DmaInitialize(
		`$INSTANCE_NAME`_Wave2_DMA_BYTES_PER_BURST, `$INSTANCE_NAME`_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(`$INSTANCE_NAME`_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(`$INSTANCE_NAME`_Wave2TD, sampleSize, `$INSTANCE_NAME`_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)`$INSTANCE_NAME`_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(`$INSTANCE_NAME`_Wave2TD, LO16((uint32)wavePtr), LO16(`$INSTANCE_NAME`_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(`$INSTANCE_NAME`_Wave2Chan, `$INSTANCE_NAME`_Wave2TD);
}


/* [] END OF FILE */
