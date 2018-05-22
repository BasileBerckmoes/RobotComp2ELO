/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the Voltage Fault Detector Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_OV.h"

/***************************************
*   Internal definitions
***************************************/

#define OV_DMA_DATA_SIZE     1u


/***************************************
*   Internal variables
***************************************/

static  uint8   ovDmaCh;


/***************************************
*   External variables
***************************************/

`$OVFaultThreshold`
`$initOVFaultThreshold`


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetOVFaultThreshold
********************************************************************************
*
* Summary:
*  Returns the over voltage fault threshold for the specified voltage input.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  uint8 voltageNum: Specifies the voltage input number. Valid range: 1..32.
*
* Return:
*  The over voltage fault threshold in mV. Valid range: 1..65,535.
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_GetOVFaultThreshold(uint8 voltageNum) `=ReentrantKeil($INSTANCE_NAME . "_GetOVFaultThreshold")`
{   
    uint32 threshold;

    /* Voltages are stored in decreasing order to reflect scanning sequence */
    voltageNum = `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - voltageNum;

	threshold = ((uint32)`$INSTANCE_NAME`_OVFaultThreshold[voltageNum] * `$INSTANCE_NAME`_DAC_mV_LSb * 1000u) /
		`$INSTANCE_NAME`_VoltageScale[voltageNum];
		
	return ((uint16)(threshold));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetOVFaultThreshold
********************************************************************************
*
* Summary:
*  Sets the over voltage fault threshold for the specified voltage input.
*  Calculates the VDAC value to reflect a new OV threshold and writes it to an
*  SRAM buffer to be used by the DMA controller that drives the OV DAC.
*  This API does not apply when ExternalRef=true.
*
* Parameters:
*  voltageNum:       Specifies the voltage input number. Valid range: 1..32.
*  ovFaultThreshold: Specifies the over voltage fault threshold in mV. 
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
cystatus `$INSTANCE_NAME`_SetOVFaultThreshold(uint8 voltageNum, uint16 ovFaultThreshold) `= ReentrantKeil($INSTANCE_NAME . "_SetOVFaultThreshold")`
{
    cystatus    status;
    uint32      threshold;

    /* Voltages are stored in decreasing order to reflect scanning sequence */
    voltageNum = `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES - voltageNum;

    /* OV threshold is scaled to fall within selected VDAC range */
    threshold = ovFaultThreshold * (uint32)`$INSTANCE_NAME`_VoltageScale[voltageNum];

    /* Saturate threshold to DAC range limit */
    if(threshold > `$INSTANCE_NAME`_FAULT_THRESHOLD_SAT_H)
    {
        `$INSTANCE_NAME`_OVFaultThreshold[voltageNum] = `$INSTANCE_NAME`_DAC_MAX;
        status = CYRET_BAD_PARAM;
    }
    else
    {
        `$INSTANCE_NAME`_OVFaultThreshold[voltageNum] = (uint8)`$INSTANCE_NAME`_ConvertDacVoltageToValue(threshold);
        status = CYRET_SUCCESS;
    }
    return (status);
}

    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_OVRefInit
********************************************************************************
*
* Summary:
*  Initializes the internal OV DAC and configures a DMA controller to transfer
*  OV thresholds from the SRAM array to the DAC data register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_OVRefInit(void) `=ReentrantKeil($INSTANCE_NAME . "_OVRefInit")`
{
    static uint8 ovDmaTd = CY_DMA_INVALID_TD;

    `$INSTANCE_NAME`_VDAC_OV_Init();

    /* Configure OV DMA first time `$INSTANCE_NAME`_OVRefInit is called */
    if(ovDmaTd == CY_DMA_INVALID_TD)
    {
        ovDmaTd = CyDmaTdAllocate();
        ovDmaCh = `$INSTANCE_NAME`_DMA_CFG(OvDMA, OV_DMA_DATA_SIZE, HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));
        (void)CyDmaTdSetConfiguration(ovDmaTd, `$INSTANCE_NAME`_NUMBER_OF_VOLTAGES, ovDmaTd, CY_DMA_TD_INC_SRC_ADR);
        (void)CyDmaTdSetAddress(ovDmaTd, LO16((uint32)`$INSTANCE_NAME`_OVFaultThreshold), LO16((uint32)`$INSTANCE_NAME`_VDAC_OV_Data_PTR));
        (void)CyDmaChSetInitialTd(ovDmaCh, ovDmaTd);
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_OVRefEnable
********************************************************************************
*
* Summary:
*  Enables OV DAC and the corresponding DMA channel.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_OVRefEnable(void) `=ReentrantKeil($INSTANCE_NAME . "_OVRefEnable")`
{
    `$INSTANCE_NAME`_VDAC_OV_Enable();
    (void)CyDmaChEnable(ovDmaCh, 1u);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_OVRefDisable
********************************************************************************
*
* Summary:
*  Stops OV DAC. Terminates and disables the DMA channel that drives OV DAC.
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
void `$INSTANCE_NAME`_OVRefStop(void) `=ReentrantKeil($INSTANCE_NAME . "_OVRefStop")`
{
    `$INSTANCE_NAME`_VDAC_OV_Stop();
    (void)CyDmaChSetRequest(ovDmaCh, CY_DMA_CPU_TERM_CHAIN);
    (void)CyDmaClearPendingDrq(ovDmaCh);
}


/* [] END OF FILE */
