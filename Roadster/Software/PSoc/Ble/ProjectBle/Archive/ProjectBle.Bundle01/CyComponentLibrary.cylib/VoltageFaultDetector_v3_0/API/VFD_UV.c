/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the Voltage Fault Detector Component.
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_UV.h"

/***************************************
*   Internal definitions
***************************************/

#define UV_DMA_DATA_SIZE     1u


/***************************************
*   Internal variables
***************************************/

static  uint8   uvDmaCh;


/***************************************
*   External variables
***************************************/

`$UVFaultThreshold`
`$initUVFaultThreshold`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetUVFaultThreshold
********************************************************************************
*
* Summary:
*  Returns the under voltage fault threshold for the specified voltage input.
*  This API does not apply when ExternalRef=true. 
*
* Parameters:
*  uint8 voltageNum: Specifies the voltage input number. Valid range: 1..32.
*
* Return:
*  The over voltage fault threshold in mV. Valid range: 1..65,535.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetUVFaultThreshold(uint8 voltageNum) `=ReentrantKeil($INSTANCE_NAME . "_GetUVFaultThreshold")`
{   
    uint32 threshold;

    /* Voltages are stored in decreasing order to reflect scanning sequence */
    voltageNum = `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - voltageNum;

	threshold = ((uint32)`$INSTANCE_NAME`_UVFaultThreshold[voltageNum] * `$INSTANCE_NAME`_DAC_mV_LSb * 1000u) /
		`$INSTANCE_NAME`_VoltageScale[voltageNum];
		
	return ((uint16)(threshold));		
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetUVFaultThreshold
********************************************************************************
*
* Summary:
*  Sets the under voltage fault threshold for the specified voltage input.
*  Calculates the VDAC value to reflect a new UV threshold and writes it to an
*  SRAM buffer to be used by the DMA controller that drives the UV DAC.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  voltageNum:       Specifies the voltage input number. Valid range: 1..32.
*  uvFaultThreshold: Specifies the under voltage fault threshold in mV. 
*                    Valid range: 1..65,535.
*
* Return:
*  CYRET_SUCCESS  : Operation is successful.
*  CYRET_BAD_PARAM: The fault threshold exceeds DAC max value.
*  
* Reentrant:
*  No.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_SetUVFaultThreshold(uint8 voltageNum, uint16 uvFaultThreshold) `= ReentrantKeil($INSTANCE_NAME . "_SetUVFaultThreshold")`
{
    cystatus    status;
    uint32      threshold;

    /* Voltages are stored in decreasing order to reflect scanning sequence */
    voltageNum = `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - voltageNum;

    /* UV threshold is scaled to fall within selected VDAC range */
    threshold = uvFaultThreshold * (uint32)`$INSTANCE_NAME`_VoltageScale[voltageNum];

    /* Saturate threshold to DAC range limit */
    if(threshold > `$INSTANCE_NAME`_FAULT_THRESHOLD_SAT_H)
    {
        `$INSTANCE_NAME`_UVFaultThreshold[voltageNum] = `$INSTANCE_NAME`_DAC_MAX;
        status = CYRET_BAD_PARAM;
    }
    else
    {
        `$INSTANCE_NAME`_UVFaultThreshold[voltageNum] = (uint8)`$INSTANCE_NAME`_ConvertDacVoltageToValue(threshold);
        status = CYRET_SUCCESS;
    }
    return (status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UVRefInit
********************************************************************************
*
* Summary:
*  Initializes the internal UV DAC and configures a DMA controller to transfer
*  UV thresholds from the SRAM array to the DAC data register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UVRefInit(void) `=ReentrantKeil($INSTANCE_NAME . "_UVRefInit")`
{
    static uint8 uvDmaTd = CY_DMA_INVALID_TD;

    `$INSTANCE_NAME`_VDAC_UV_Init();

    /* Configure UV DMA first time `$INSTANCE_NAME`_UVRefInit is called */
    if(uvDmaTd == CY_DMA_INVALID_TD)
    {
        uvDmaTd = CyDmaTdAllocate();
        uvDmaCh = `$INSTANCE_NAME`_DMA_CFG(UvDMA, UV_DMA_DATA_SIZE, HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));
        (void)CyDmaTdSetConfiguration(uvDmaTd, `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES, uvDmaTd, CY_DMA_TD_INC_SRC_ADR);
        (void)CyDmaTdSetAddress(uvDmaTd, LO16((uint32)`$INSTANCE_NAME`_UVFaultThreshold), LO16((uint32)`$INSTANCE_NAME`_VDAC_UV_Data_PTR));
        (void)CyDmaChSetInitialTd(uvDmaCh, uvDmaTd);   
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UVRefEnable
********************************************************************************
*
* Summary:
*  Enables UV DAC and the corresponding DMA channel.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UVRefEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_UVRefEnable")`
{
    `$INSTANCE_NAME`_VDAC_UV_Enable();
    (void)CyDmaChEnable(uvDmaCh, 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UVRefDisable
********************************************************************************
*
* Summary:
*  Stops UV DAC. Terminates and disables the DMA channel that drives UV DAC.
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
void `$INSTANCE_NAME`_UVRefStop(void) `=ReentrantKeil($INSTANCE_NAME . "_UVRefStop")`
{
    `$INSTANCE_NAME`_VDAC_UV_Stop();
    (void)CyDmaChSetRequest(uvDmaCh, CY_DMA_CPU_TERM_CHAIN);
    (void)CyDmaClearPendingDrq(uvDmaCh);
}


/* [] END OF FILE */
