/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code the CSD ADC
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

/***************************************
* Function Prototypes for internal functions
***************************************/

int32 static `$INSTANCE_NAME`_GetResult32(void);
int32 static `$INSTANCE_NAME`_CountsTo_nAmps(int32 result);
int32 static `$INSTANCE_NAME`_CountsTo_mVolts(int32 result);

/***************************************
*               Globals
***************************************/

static int32 `$INSTANCE_NAME`_Imod_Cal_nA = 
    ((int32) `$INSTANCE_NAME`_IDAC1_VALUE * `$INSTANCE_NAME`_IDAC_STEP_NA);

uint8 `$INSTANCE_NAME`_initVar = 0u;

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initializes the CSD hardware by setting all the appropriate registers for 
*  the component.  Initialization is only required once after reset.
*  It is not necessary to call `$INSTANCE_NAME`_Init() because the 
*  `$INSTANCE_NAME`_Start() API calls this function and is the preferred 
*  method to begin component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void `$INSTANCE_NAME`_Init(void)
{
    
    /* Trim the IDACS for low voltage mode CSD.  We wont be sourcing current
    into anything higher than 1.2 volts so we do not need to use the HVIDAC
    Trim settings.*/
    `$INSTANCE_NAME`_TRIM_1_REG &=
        ~`$INSTANCE_NAME`_IDAC1_SRC_TRIM_MASK;
    
    /* TRIM 1 controls the trim for the IDACs in sourcing mode   
    write the trim IDAC1 stored in SFLASH into the trim register */
    `$INSTANCE_NAME`_TRIM_1_REG |= 
        (`$INSTANCE_NAME`_IDAC_TRIM_SRC_FLASH_REG << `$INSTANCE_NAME`_IDAC1_SRC_TRIM_SHIFT) &
        `$INSTANCE_NAME`_IDAC1_SRC_TRIM_MASK;
    
    /* Clear IDAC1 configuration */
    `$INSTANCE_NAME`_IDAC_REG &= 
        ~(`$INSTANCE_NAME`_IDAC1_VALUE_MASK | 
        `$INSTANCE_NAME`_IDAC1_MODE_MASK | 
        `$INSTANCE_NAME`_IDAC1_RANGE_MASK); 
    
    /* configure IDAC 1 */
    `$INSTANCE_NAME`_IDAC_REG |= 
        /* Set IDAC1 to have a value of `$IDAC_Value` */
        (`$INSTANCE_NAME`_IDAC1_VALUE << `$INSTANCE_NAME`_IDAC1_VALUE_SHIFT) |
         /* IDAC1 put into variable mode */
        (`$INSTANCE_NAME`_IDAC1_MODULATED << `$INSTANCE_NAME`_IDAC1_MODE_SHIFT);
    
        /* This option is changed via a hidden component parameter */
    #if `$IDAC_HighRange` != 0
        `$INSTANCE_NAME`_IDAC_REG |= 
            (`$INSTANCE_NAME`_IDAC1_612_UA_RANGE << `$INSTANCE_NAME`_IDAC1_RANGE_SHIFT);
    #endif
    
    /* clear the CSD hardware config, preserve IDAC2 polarity
    and the CSD block enable bit (if it is already set) */
    `$INSTANCE_NAME`_CONFIG_REG &= 
        (`$INSTANCE_NAME`_POLARITY_2_MASK |
        `$INSTANCE_NAME`_CSD_ENABLE_MASK);
    
    /* configure the CSD hardware*/
    `$INSTANCE_NAME`_CONFIG_REG |=         
        (`$INSTANCE_NAME`_DIV2_OR_PRS << `$INSTANCE_NAME`_BYPASS_SEL_SHIFT) | 
        (`$INSTANCE_NAME`_FILTER_DISABLE << `$INSTANCE_NAME`_FILTER_ENABLE_SHIFT) |
        (`$INSTANCE_NAME`_DIV_BY_2 << `$INSTANCE_NAME`_PRS_SELECT_SHIFT) |
        (`$INSTANCE_NAME`_PRS_8 << `$INSTANCE_NAME`_PRS_12_8_SHIFT) |
        (`$INSTANCE_NAME`_DELAY_OFF << `$INSTANCE_NAME`_SHIELD_DELAY_SHIFT) |
        (`$INSTANCE_NAME`_COMP_BW_HIGH << `$INSTANCE_NAME`_SENSE_COMP_BW_SHIFT) |  
        (`$INSTANCE_NAME`_SENSE_DISABLE << `$INSTANCE_NAME`_SENSE_EN_SHIFT) |
        (`$INSTANCE_NAME`_REFBUF_DISABLE << `$INSTANCE_NAME`_REFBUF_EN_SHIFT) |
        (`$INSTANCE_NAME`_CHARGE_VIA_BUFFER << `$INSTANCE_NAME`_COMP_MODE_SHIFT) |
        (`$INSTANCE_NAME`_CMOD_P0_4 << `$INSTANCE_NAME`_COMP_PIN_SHIFT) |
        (`$INSTANCE_NAME`_IDAC1_SOURCE << `$INSTANCE_NAME`_POLARITY_1_SHIFT) |
        (`$INSTANCE_NAME`_SENSE_COMP_DISABLE << `$INSTANCE_NAME`_SENSE_COMP_EN_SHIFT) |
        (`$INSTANCE_NAME`_REFBUF_TO_AMUXA << `$INSTANCE_NAME`_REFBUF_OUTSEL_SHIFT) |
        (`$INSTANCE_NAME`_SENSE_AMUXA << `$INSTANCE_NAME`_SENSE_INSEL_SHIFT) |
        (`$INSTANCE_NAME`_REFBUF_HIGH << `$INSTANCE_NAME`_REFBUF_DRIVE_SHIFT) | 
        (`$INSTANCE_NAME`_DDFTSEL_NORMAL << `$INSTANCE_NAME`_DDFTSEL_SHIFT) |
        (`$INSTANCE_NAME`_ADFTSEL_NORMAL << `$INSTANCE_NAME`_ADFTSEL_SHIFT) |
        (`$INSTANCE_NAME`_CSD_ENABLE << `$INSTANCE_NAME`_CSD_ENABLE_SHIFT);
    
    return;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the refbuf which charges CMOD.  This API should only be called 
*  after the component has been initialized.  Enabling the component before 
*  initialization may result in unexpected behavior.  It is not necessary to 
*  call `$INSTANCE_NAME`_Enable() because the `$INSTANCE_NAME`_Start() API 
*  calls this function, which is the preferred method to begin component 
*  operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_CONFIG_REG |= 
         /* REFBUF enabled */
        (`$INSTANCE_NAME`_REFBUF_ENABLE << `$INSTANCE_NAME`_REFBUF_EN_SHIFT);
    
    return;
}
    

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary: 
*  Initializes and enables the CSD_ADC component.  Calls the 
*  `$INSTANCE_NAME`_Init() and `$INSTANCE_NAME`_Enable() API.  
*  
*  If the `$INSTANCE_NAME` is being started for the first time since a 
*  device reset, ensure you that you disconnect all inputs to the
*  `$INSTANCE_NAME` and call the `$INSTANCE_NAME`_CalibrateNoInput() API.\
*  After calling the `$INSTANCE_NAME`_Start() API and calibrating 
*  with no input, the ADC is ready to take samples by calling the 
*  `$INSTANCE_NAME`_StartConvert() API.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/

void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;   
    }
    
    `$INSTANCE_NAME`_Enable();
    
    return;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the power to the `$INSTANCE_NAME` component.  All 
*  configuration information is retained when the component is stopped.  
*  If `$INSTANCE_NAME`_Stop() is called during a conversion, the 
*  conversion that is currently in progress is aborted and any result 
*  returned by the `$INSTANCE_NAME`_GetResult_mVolts() API 
*  should be discarded.  `$INSTANCE_NAME`_Stop() or 
*  `$INSTANCE_NAME`_Sleep() should be called 
*  before putting the device to sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/


void `$INSTANCE_NAME`_Stop(void)
{     
    /* disable the hardware */
    `$INSTANCE_NAME`_CONFIG_REG &= 
         /* REFBUF disabled */
        ~(`$INSTANCE_NAME`_REFBUF_EN_MASK |
        /* disable the sense comparator */
        `$INSTANCE_NAME`_SENSE_COMP_EN_MASK | 
        /* disable the modulator */
        `$INSTANCE_NAME`_SENSE_EN_MASK);
    
    return;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StartConvert
********************************************************************************
*
* Summary:
*  Initiates a single conversion.  This function will return as soon 
*  as the conversion has started to enable the user to perform other 
*  tasks while the conversion is progressing.  To check on the status of 
*  the conversion, call the `$INSTANCE_NAME`_IsEndConversion() API.  
*  When the conversion completes, the user must call the 
*  `$INSTANCE_NAME`_StartConvert() API again to initiate another conversion.
*
* Parameters:
*  None
*
* Return:
*  `$INSTANCE_NAME`_START_CONV_OK : the conversion started succesfully
*  -or-
*  `$INSTANCE_NAME`_START_CONV_ERR : the 7-bit IDAC is not started, the 
*  conversion did not start
*  
*  If IDAC2 (the 7 bit IDAC) is not enabled, the API will return 
*  `$INSTANCE_NAME`_START_CONV_ERR and the conversion will not be started
*  if you recieve this error, you must start the 7-bit IDAC and call the 
*  `$INSTANCE_NAME`_StartConvert API again
*
*******************************************************************************/

int32 `$INSTANCE_NAME`_StartConvert(void)
{   
    /* verify that the 7-bit IDAC is enabled */
    if((`$INSTANCE_NAME`_IDAC_REG & `$INSTANCE_NAME`_IDAC2_MODE_MASK) != 
        (`$INSTANCE_NAME`_IDAC2_GENERAL << `$INSTANCE_NAME`_IDAC2_MODE_SHIFT))
    {
        /* The 7-bit IDAC is not in general purpose mode, return an error
        and do not start the conversion */
        return `$INSTANCE_NAME`_START_CONV_ERR;
    }
    
    /* start the modulator */
    `$INSTANCE_NAME`_CONFIG_REG |= 
        /* Enable the sense comparator */
        (`$INSTANCE_NAME`_SENSE_COMP_ENABLE << `$INSTANCE_NAME`_SENSE_COMP_EN_SHIFT) | 
        /* Enable the modulator */
        (`$INSTANCE_NAME`_SENSE_ENABLE << `$INSTANCE_NAME`_SENSE_EN_SHIFT);
    
    /* disconnect RefBuf from CMOD and start conversion */
    `$INSTANCE_NAME`_CONFIG_REG &= 
         /* REFBUF disabled */
        ~(`$INSTANCE_NAME`_REFBUF_ENABLE << `$INSTANCE_NAME`_REFBUF_EN_SHIFT);
    
    /* load the counter period value with the desired resolution */
    `$INSTANCE_NAME`_COUNTER_REG = 
        (`$INSTANCE_NAME`_RESOLUTION << `$INSTANCE_NAME`_PERIOD_SHIFT);
    
    /* the conversion started successfully */
    return `$INSTANCE_NAME`_START_CONV_OK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_IsEndConversion
********************************************************************************
*
* Summary:
*  After starting a conversion by calling the 
*  `$INSTANCE_NAME`_StartConvert() API, this function will either:
*  -    Wait for the conversion to finish
*  -    Return the status of the current conversion
*  depending on the value passed to the function
*
* Parameters:
*  The parameter passed to this API determines if the function will block 
*  and not return until the conversion has completed or if it will return 
*  the status of the current conversion.
* 
*  `$INSTANCE_NAME`_RETURN_STATUS (ZERO)
*  `$INSTANCE_NAME`_WAIT_FOR_RESULT (NON-ZERO)
*
* Return:
* 
*  `$INSTANCE_NAME`_CONV_IN_PROGRESS (ZERO): The conversion is in progress
*  `$INSTANCE_NAME`_CONV_COMPLETE (NON-ZERO): The conversion has completed

*
*******************************************************************************/

int32 `$INSTANCE_NAME`_IsEndConversion(int32 retMode)
{
    int32 returnVal = 0L;
    
    do
    {
        returnVal = (0U == (`$INSTANCE_NAME`_COUNTER_REG >> 16U)) ? 
            `$INSTANCE_NAME`_CONV_COMPLETE : `$INSTANCE_NAME`_CONV_IN_PROGRESS;
    }while((`$INSTANCE_NAME`_RETURN_STATUS != retMode) && 
        (`$INSTANCE_NAME`_CONV_IN_PROGRESS == returnVal));
    
    /* if the conversion is complete, reconnect the refbuf to CMOD */
    if(`$INSTANCE_NAME`_CONV_COMPLETE == returnVal)
    {
        /* REFBUF enabled */
        `$INSTANCE_NAME`_CONFIG_REG |= 
            (`$INSTANCE_NAME`_REFBUF_ENABLE << `$INSTANCE_NAME`_REFBUF_EN_SHIFT);  
        
        /* disable the modulator */
        `$INSTANCE_NAME`_CONFIG_REG &= 
            /* disable the sense comparator */
            ~(`$INSTANCE_NAME`_SENSE_COMP_EN_MASK | 
            /* disable the modulator */
            `$INSTANCE_NAME`_SENSE_EN_MASK);
    }
    return returnVal;   
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult32
********************************************************************************
*
* Summary:
*  Returns the result from the CSD counter register
*
* Parameters:
*  None
*
* Return:
*  The counter register value
*
*******************************************************************************/

int32 static `$INSTANCE_NAME`_GetResult32(void)
{
    return (int32) ((uint32) ((`$INSTANCE_NAME`_COUNTER_REG & 
        `$INSTANCE_NAME`_COUNTER_MASK) >> `$INSTANCE_NAME`_COUNTER_SHIFT));
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_nAmps
********************************************************************************
*
* Summary:
*  Using the Imod value, count value, maximum count (Resolution), Vref and
*  Rbleed  of the CSD configuration, calculate the average current.  
*  The equation used is:
* 
*  Isense = Imod*Result/Resolution - Vref/Rbleed
* 
*  After scaling for integer calculations
* 
*  Isense_nA = Imod_nA*Result/Resolution - Vref_mV * 1e3 / Rbleed_K
*
* Parameters:
*  The count result obtained from the `$INSTANCE_NAME`_GetResult32 API
*
* Return:
*  The measured current in nanoamps as a signed 32 bit integer
*
*******************************************************************************/

int32 static `$INSTANCE_NAME`_CountsTo_nAmps(int32 result)
{
    int32 ibleed_temp;
    int32 imod_temp;

    ibleed_temp = ((int32) `$INSTANCE_NAME`_VREF_MV) * 1000;
    ibleed_temp = ibleed_temp / ((int32) `$Rbleed_k`);
    
    imod_temp = `$INSTANCE_NAME`_Imod_Cal_nA * result;
    imod_temp = imod_temp / ((int32) `$Resolution`);
    
    return imod_temp - ibleed_temp;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Using the measured current in nanoamps (obtained from the 
*  `$INSTANCE_NAME`_CountsTo_nAmps() API), the known reference voltage,
*  and input resistance, the voltage applied to the input resistor can be
*  calculated.  The equation is:
* 
*  Vsense = Vref - Isense*Rin
* 
*  After scaling for integer math
* 
*  Vsense_mV = Vref_mV - Isense_nA / 1e3 * Rin_K
*
* Parameters:
*  The count result obtained from the `$INSTANCE_NAME`_GetResult32 API
*
* Return:
*  The measured voltage on the input resistor in millivolts
*  as a signed 32 bit integer
*
*******************************************************************************/

int32 static `$INSTANCE_NAME`_CountsTo_mVolts(int32 result)
{
    int32 vtemp_mV;
    
    vtemp_mV = `$INSTANCE_NAME`_CountsTo_nAmps(result);
    
    vtemp_mV = vtemp_mV * ((int32) `$Rin_k`);
    vtemp_mV = vtemp_mV / 1000;
    
    vtemp_mV = ((int32) `$INSTANCE_NAME`_VREF_MV) - vtemp_mV;
    
    return vtemp_mV;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetResult_mVolts
********************************************************************************
*
* Summary:
*  Call this API after `$INSTANCE_NAME`_IsEndConversion() indicates that 
*  the conversion has completed.  Returns the result of the most recently 
*  completed conversion in millivolts.
*
* Parameters:
*  None
*
* Return:
*  The measured voltage on the input resistor in millivolts
*  as a signed 32 bit integer
*
*******************************************************************************/

int32 `$INSTANCE_NAME`_GetResult_mVolts(void)
{
    return `$INSTANCE_NAME`_CountsTo_mVolts(`$INSTANCE_NAME`_GetResult32());
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read_mVolts
********************************************************************************
*
* Summary:
*  Starts a conversion, waits for the conversion to complete then returns 
*  the result in millivolts.  This is identical to calling 
*  `$INSTANCE_NAME`_StartConvert(), 
*  `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT) 
*  and `$INSTANCE_NAME`_GetResult_mVolts() in order.
*
* Parameters:
*  None
*
* Return:
*  The measured voltage on the input resistor in millivolts
*  as a signed 32 bit integer
*
*  -or-
*  
*  `$INSTANCE_NAME`_START_CONV_ERR : the 7-bit IDAC is not started, the 
*  conversion did not start
*  
*  If IDAC2 (the 7 bit IDAC) is not enabled, the API will return 
*  `$INSTANCE_NAME`_START_CONV_ERR and the conversion will not be started
*  if you recieve this error, you must start the 7-bit IDAC and call the 
*  `$INSTANCE_NAME`_Read_mVolts API again
*
*******************************************************************************/

int32 `$INSTANCE_NAME`_Read_mVolts(void)
{
    if(`$INSTANCE_NAME`_START_CONV_ERR == `$INSTANCE_NAME`_StartConvert())
    {
        return `$INSTANCE_NAME`_START_CONV_ERR;
    }
    
    (void) `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
    
    return `$INSTANCE_NAME`_GetResult_mVolts();
}


/************s*******************************************************************
* Function Name: `$INSTANCE_NAME`_CalibrateNoInput
********************************************************************************
*
* Summary:  
*  Before calling this API, ensure that the `$INSTANCE_NAME`
*  is started and the sense terminal of the component is not connected 
*  to anything by disconnecting all mux channels connected to the sense 
*  input.  This API calibrates the internal current source value.  This 
*  API must be called once before any measurements are taken.  Calibration 
*  is only required once per device reset.
*  
*  The API takes a sample with the knowledge that nothing is connected 
*  to the input and calculates the value of the internal current source.  
*  This calculation is critical for accurate operation of the `$INSTANCE_NAME`.
*  The following equation is used to calculate the Imod with no input:
* 
*  Imod = Vref * Resolution / (Rbleed * Result)
* 
*  After scaling for integer math:
* 
*  Imod_nA = (Vref_mV*Resolution*1e3) / (Rbleed_k*Result)
*  
*
* Parameters:
*  None
*
* Return:
*  `$INSTANCE_NAME`_START_CONV_OK : the conversion started succesfully and the
*  calibration was successful
*  -or-
*  `$INSTANCE_NAME`_START_CONV_ERR : the 7-bit IDAC is not started, the 
*  conversion did not start and the calibration was not successful
*  
*  If IDAC2 (the 7 bit IDAC) is not enabled, the API will return 
*  `$INSTANCE_NAME`_START_CONV_ERR and the conversion will not be started
*  if you recieve this error, you must start the 7-bit IDAC and call the 
*  `$INSTANCE_NAME`_CalibrateNoInput API again
*
*******************************************************************************/

int32 `$INSTANCE_NAME`_CalibrateNoInput(void)
{
    int32 result;
    
    if(`$INSTANCE_NAME`_START_CONV_ERR == `$INSTANCE_NAME`_StartConvert())
    {
        return `$INSTANCE_NAME`_START_CONV_ERR;
    }
    
    (void) `$INSTANCE_NAME`_IsEndConversion(`$INSTANCE_NAME`_WAIT_FOR_RESULT);
    result = `$INSTANCE_NAME`_GetResult32();
    
    `$INSTANCE_NAME`_Imod_Cal_nA = `$INSTANCE_NAME`_VREF_MV * 1000;
    `$INSTANCE_NAME`_Imod_Cal_nA = `$INSTANCE_NAME`_Imod_Cal_nA / ((int32) `$Rbleed_k`);
    `$INSTANCE_NAME`_Imod_Cal_nA = `$INSTANCE_NAME`_Imod_Cal_nA * ((int32) `$Resolution`);
    `$INSTANCE_NAME`_Imod_Cal_nA = `$INSTANCE_NAME`_Imod_Cal_nA / result;
    
    return `$INSTANCE_NAME`_START_CONV_OK;
}
    
/* [] END OF FILE */
