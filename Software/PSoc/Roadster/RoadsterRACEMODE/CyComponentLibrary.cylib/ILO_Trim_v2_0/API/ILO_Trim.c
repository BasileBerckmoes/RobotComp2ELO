/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the setup, control and status commands for the 
*  ILO_Trim component. It also contains the ISR for the trimming operation.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "`$INSTANCE_NAME`.h"
`$CY_API_CALLBACK_HEADER_INCLUDE`

static uint16 `$INSTANCE_NAME`_ReadCapture(void) CYREENTRANT;
static uint16 `$INSTANCE_NAME`_ReadEdgeCount(void) CYREENTRANT;

#if (!CY_PSOC4)
	static uint8 trimFactory;
#endif /* End of PSoC 3 and PSoC 5LP code */

#if(!CY_PSOC4)


/*******************************************************************************
* Interrupt Name: `$INSTANCE_NAME`_CorrectionISR
********************************************************************************
*
* Summary: 
*  If enabled, this CorrectionISR is executed for every cycle of the ILO. It 
*  reads the counter capture register to find out how many Reference edges were
*  counted per cycle of the ILO. Then, the CorrectionISR checks whether this 
*  value is within the acceptable range. If yes, it disables itself. If not, 
*  it corrects the ILO frequency by unit trim - either coarse or fine, and exits
*  the routine.
*
* Parameters:
*  None
*
* Side Effects: 
*  1) Turns off CorrectionISR if ILO is trimmed.
*  2) Reads counter capture register directly
*  3) Changes ILO frequency
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_CorrectionIteration)
{
    uint16 edgeCount, errorNewAbs;
    int16 errorNew;
    uint8 trimNew;
    static uint16 errorOld = `$INSTANCE_NAME`_ERROR_DEFAULT;
    static uint8 trimOld, startDelay = `$INSTANCE_NAME`_INIT_DELAY;
    static uint8 iteration = `$INSTANCE_NAME`_ISR_INVALID;

    #ifdef `$INSTANCE_NAME`_CORRECTION_ITERATION_ENTRY_CALLBACK
        `$INSTANCE_NAME`_CorrectionIteration_EntryCallback();
    #endif /* `$INSTANCE_NAME`_CORRECTION_ITERATION_ENTRY_CALLBACK */
    
    if(iteration == `$INSTANCE_NAME`_ISR_INVALID)
    {
        if(startDelay == `$INSTANCE_NAME`_FINAL_DELAY)
        {
            iteration = `$INSTANCE_NAME`_ISR_VALID;
        }
        else
        {
            /* Give some time once the component has started */
            startDelay += `$INSTANCE_NAME`_DELAY_COUNT;
        }
    }
    else
    {
        iteration = `$INSTANCE_NAME`_ISR_INVALID;
        
        edgeCount = `$INSTANCE_NAME`_ReadEdgeCount();
            
        if(edgeCount != `$INSTANCE_NAME`_COUNT_ZERO)
        {
            errorNew = (int16)((uint16)((`$INSTANCE_NAME`_EDGES_PPT / edgeCount) - `$INSTANCE_NAME`_PP_THOUSAND));            
        }
        else
        {
            errorNew = (int16)`$INSTANCE_NAME`_COUNT_ZERO;
        }
    
        #if (`$INSTANCE_NAME`_ILO_FREQUENCY == `$INSTANCE_NAME`_1kHz)
            /* 1k ILO fine trim - TR0[3:0] reserved for 1kHz ILO */
            trimNew = (uint8)((`$INSTANCE_NAME`_ILO_TR0_MASK & CY_GET_REG8(CYREG_ILO_TR0))
                        | (uint8)((`$INSTANCE_NAME`_ILO_TR1_MASK & CY_GET_REG8(CYREG_ILO_TR1))
                            << `$INSTANCE_NAME`_TRIM_SHIFT));
        #else
            /* 100k ILO fine trim - TR0[7:4] reserved for 100kHz ILO */
            trimNew = (uint8)((uint8)((`$INSTANCE_NAME`_ILO_TR0_MASK & CY_GET_REG8(CYREG_ILO_TR0))
                            >>`$INSTANCE_NAME`_TRIM_SHIFT)
                        | (uint8)((`$INSTANCE_NAME`_ILO_TR1_MASK & CY_GET_REG8(CYREG_ILO_TR1))
                            << `$INSTANCE_NAME`_TRIM_SHIFT));
        #endif /* End of ILO Frequency dependent code. */
    
        if(errorNew < `$INSTANCE_NAME`_ERROR_ZERO)
        {
            errorNewAbs = (uint16)(-errorNew);
        }
        else
        {
             errorNewAbs = (uint16)errorNew;
        }
        
        if(errorNewAbs > errorOld)
        {
            if(errorOld <= `$INSTANCE_NAME`_PP_HUNDRED)
            {
                /* Revert back to the previous Trim */
                trimNew = trimOld;
        
                /* Stop the CorrectionISR but not the Timer if the ILO frequency is stable */
                `$INSTANCE_NAME`_CorrectionISR_Disable();
            }
            else
            {
                /* Start all over again from another coarse trim value */                
                if((trimNew & `$INSTANCE_NAME`_FINE_TRIM_MASK)!=`$INSTANCE_NAME`_TRIM_COARSE_NEXT)
                {
                    trimNew += `$INSTANCE_NAME`_COARSE_TRIM_ADD; 
                }
                else
                {
                    trimNew += `$INSTANCE_NAME`_FINE_TRIM_ADD; 
                }
            }
            /* Reinitialize the errorOld memory at the end of function */
            errorNewAbs = `$INSTANCE_NAME`_ERROR_DEFAULT;
        }
        else
        {
            /* Keep a copy of the old trim setting */
            trimOld = trimNew;
    
            if(edgeCount < (uint16)`$INSTANCE_NAME`_EDGES_IDEAL)
            {
                trimNew -= `$INSTANCE_NAME`_CORRECTION_STEP_SIZE;
            }
            else 
            {
                trimNew += `$INSTANCE_NAME`_CORRECTION_STEP_SIZE;
            }
        }

        #if (`$INSTANCE_NAME`_ILO_FREQUENCY == `$INSTANCE_NAME`_1kHz)
            CY_SET_REG8(CYREG_ILO_TR0, 
                (uint8)(CY_GET_REG8(CYREG_ILO_TR0) & `$INSTANCE_NAME`_FINE_TRIM_CLEAR)
                | (trimNew & `$INSTANCE_NAME`_ILO_TR0_MASK));
            CY_SET_REG8(CYREG_ILO_TR1, 
                (uint8)(CY_GET_REG8(CYREG_ILO_TR1) & `$INSTANCE_NAME`_COARSE_TRIM_CLEAR)
                | ((uint8)((uint8)trimNew >> `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR1_MASK));
        #else
            CY_SET_REG8(CYREG_ILO_TR0, 
                (uint8)(CY_GET_REG8(CYREG_ILO_TR0) & `$INSTANCE_NAME`_FINE_TRIM_CLEAR)
                | ((uint8)((uint8)trimNew << `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR0_MASK));
            CY_SET_REG8(CYREG_ILO_TR1, 
                (uint8)(CY_GET_REG8(CYREG_ILO_TR1) & `$INSTANCE_NAME`_COARSE_TRIM_CLEAR)
                | ((uint8)((uint8)trimNew >> `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR1_MASK));
        #endif /* End of ILO Frequency dependent code */
        
        /* Keep a copy of the old error */
        errorOld = errorNewAbs;
    }
    
    #ifdef `$INSTANCE_NAME`_CORRECTION_ITERATION_EXIT_CALLBACK
        `$INSTANCE_NAME`_CorrectionIteration_ExitCallback();
    #endif /* `$INSTANCE_NAME`_CORRECTION_ITERATION_EXIT_CALLBACK */
}/* End CorrectionISR */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckStatus
********************************************************************************
*
* Summary: 
*  Checks whether the ILO frequency is in the best possible error range.
*
* Parameters:
*  None
*
* Return: 
*  uint8 status
*   IS_ACCURATE     ILO is within error range
*   TRIMMING        CorrectionISR is running 
*
* Side Effects: 
*  May not return correct value when called in the first 
*  millisecond of component start.
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_CheckStatus(void) `=ReentrantKeil($INSTANCE_NAME . "_CheckStatus")`
{
	uint16 errorAbs;
    int16 error;
    uint8 isrOn;
	uint8 status = `$INSTANCE_NAME`_TRIMMED;

	isrOn = `$INSTANCE_NAME`_CorrectionISR_GetState();
	
	/* Change status for CorrectionISR */
	if(isrOn!=`$INSTANCE_NAME`_ISR_OFF)
    {
		status = `$INSTANCE_NAME`_TRIMMING;
	}
	
    error = `$INSTANCE_NAME`_CheckError();
    
    if(error < `$INSTANCE_NAME`_ERROR_ZERO)
    {
        errorAbs = (uint16)(-error);
    }
    else
    {
         errorAbs = (uint16)error;
    }

	if(errorAbs <= `$INSTANCE_NAME`_PP_HUNDRED)
	{
		status |= `$INSTANCE_NAME`_IS_ACCURATE;
	}
    
	return(status);
}

#endif /* End of PSoC 3 and PSoC 5LP code */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CheckError
********************************************************************************
*
* Summary: 
*  Calculates ILO error in parts per thousand.
*
* Parameters:
*  None
*
* Return: 
*  int16 error
*   error value in parts per thousand.
*
* Side Effects:
*  May not return correct value when called in the first 
*  millisecond of component start.
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_CheckError(void) `=ReentrantKeil($INSTANCE_NAME . "_CheckError")`
{
	uint16 edgeCount;
	int16 error;

	edgeCount = `$INSTANCE_NAME`_ReadEdgeCount();
	
    if(edgeCount != `$INSTANCE_NAME`_COUNT_ZERO)
	{
        error = (int16)((uint16)((`$INSTANCE_NAME`_EDGES_PPT / edgeCount) - `$INSTANCE_NAME`_PP_THOUSAND));
    }
    else
    {
        error = (int16)`$INSTANCE_NAME`_COUNT_ZERO;
    }
	
	return(error);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Compensate
********************************************************************************
*
* Summary: 
*  Compensates for the ILO clock inaccuracy by converting from a desired 
*  nominal number of clock cycles to the effective number of ILO clock cycles 
*  required based on the current accuracy of the ILO.  
*
* Parameters:
*  targetTime
*
* Return: 
*  uint16 scaleFactor
*
* Side Effects: 
*  None
*
*******************************************************************************/
uint16 `$INSTANCE_NAME`_Compensate(uint16 clocks) `=ReentrantKeil($INSTANCE_NAME . "_Compensate")`
{
	uint32 timeDesired, ILOActual, clocksActual;
	uint16 edgeCount, clocksOut;
	int16 error;

	/* Calculate the user's target time */
	timeDesired = (uint32)(((uint32)clocks * `$INSTANCE_NAME`_TIME_SCALE) / `$INSTANCE_NAME`_ILO_FREQUENCY);
	
	/* Calculate the ILO error */
	edgeCount = `$INSTANCE_NAME`_ReadEdgeCount();
	if(edgeCount != `$INSTANCE_NAME`_COUNT_ZERO)
	{
        /* ILO error is proportional to the difference of the inverse of edge count and EDGES_IDEAL */
        error = (int16)((uint16)((`$INSTANCE_NAME`_EDGES_PPH / edgeCount) - `$INSTANCE_NAME`_PP_HUNDRED));
    }
    else
    {
        error = (int16)`$INSTANCE_NAME`_COUNT_ZERO;
    }
    
	ILOActual = ((uint32)`$INSTANCE_NAME`_ILO_FREQUENCY * `$INSTANCE_NAME`_ILO_SCALE)
                + ((uint32)`$INSTANCE_NAME`_ILO_FREQUENCY * (uint32)error);
	
	/* Calculate the scaled clock count */
	clocksActual = ILOActual * (timeDesired / `$INSTANCE_NAME`_ILO_SCALE);
	
	if((clocksActual / `$INSTANCE_NAME`_TIME_SCALE) > `$INSTANCE_NAME`_COUNTER_SATURATE)
	{
		clocksOut = `$INSTANCE_NAME`_COUNTER_SATURATE;
	}
	else
	{
		clocksOut = (uint16)(clocksActual / `$INSTANCE_NAME`_TIME_SCALE);
	}
	
	return(clocksOut);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Enables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side effects: 
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    #if (!CY_PSOC4)
	    `$INSTANCE_NAME`_CorrectionISR_StartEx(&`$INSTANCE_NAME`_CorrectionIteration);
    #endif /* Only available for PSoC 3 and PSoC 5LP */
	
    `$INSTANCE_NAME`_CorrectionISR_Disable();	
	
	/* Store away the factory trim value */
	#if (!CY_PSOC4)
        #if (`$INSTANCE_NAME`_ILO_FREQUENCY == `$INSTANCE_NAME`_1kHz)
            /* 1k ILO fine trim - TR0[3:0] reserved for 1kHz ILO */
            trimFactory = (uint8)((`$INSTANCE_NAME`_ILO_TR0_MASK & CY_GET_REG8(CYREG_ILO_TR0))
                        |(uint8)((`$INSTANCE_NAME`_ILO_TR1_MASK & CY_GET_REG8(CYREG_ILO_TR1))
                            << `$INSTANCE_NAME`_TRIM_SHIFT));
        #else
            /* 100k ILO fine trim - TR0[7:4] reserved for 100kHz ILO */
            trimFactory = (uint8)((uint8)((`$INSTANCE_NAME`_ILO_TR0_MASK & CY_GET_REG8(CYREG_ILO_TR0))
                            >>`$INSTANCE_NAME`_TRIM_SHIFT)
                        |(uint8)((`$INSTANCE_NAME`_ILO_TR1_MASK & CY_GET_REG8(CYREG_ILO_TR1))
                            << `$INSTANCE_NAME`_TRIM_SHIFT));
        #endif /* End of ILO Frequency dependent code. */
	#endif /* End of PSoC 3 and PSoC 5LP code */
	
	/* Start Edge_Counter */
	#if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
		/* Enable UDB Timer */
		`$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_ENABLE;
	#else
		#if (CY_PSOC4)
			`$INSTANCE_NAME`_TCPWM_Start();
			`$INSTANCE_NAME`_TCPWM_TriggerCommand(`$INSTANCE_NAME`_TCPWM_MASK, `$INSTANCE_NAME`_TCPWM_CMD_START); 
		#else
			/* Enable FF Timer */
			/* Clear all bits but the enable bit (if it's already set) for Timer operation */
		    `$INSTANCE_NAME`_CONTROL_REG &= `$INSTANCE_NAME`_CTRL_ENABLE;
			
			/* CONTROL3 register exists only in PSoC3 OR PSoC5LP */
		    `$INSTANCE_NAME`_CONTROL3_REG &= ((uint8)(~`$INSTANCE_NAME`_CTRL_MODE_MASK));

	        /*Enable DSI Sync on all inputs of the Timer*/
	        `$INSTANCE_NAME`_RT1_REG &= ((uint8)(~`$INSTANCE_NAME`_SYNCDSI_MASK));
	        `$INSTANCE_NAME`_RT1_REG |= `$INSTANCE_NAME`_SYNCDSI_EN;
		
		    /* Set Initial values from Configuration */
			CY_SET_REG16(`$INSTANCE_NAME`_PERIOD_LSB_PTR, `$INSTANCE_NAME`_INIT_PERIOD);
			CY_SET_REG16(`$INSTANCE_NAME`_COUNTER_LSB_PTR, `$INSTANCE_NAME`_INIT_PERIOD);
			
			`$INSTANCE_NAME`_GLOBAL_ENABLE |= `$INSTANCE_NAME`_BLOCK_EN_MASK;
	        `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE |= `$INSTANCE_NAME`_BLOCK_STBY_EN_MASK;

			`$INSTANCE_NAME`_CONTROL_REG |= `$INSTANCE_NAME`_CTRL_ENABLE;
		#endif /* End of PSoC 3 and PSoC 5LP code */
	#endif /* End of Fixed Function code */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
	`$INSTANCE_NAME`_CorrectionISR_Disable();
	`$INSTANCE_NAME`_CorrectionISR_ClearPending();
	
    #if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
		/* Stop the Edge_Counter */
		`$INSTANCE_NAME`_CONTROL_REG &= ((uint8) ~`$INSTANCE_NAME`_CTRL_ENABLE);
	#else
		#if (CY_PSOC4)
			`$INSTANCE_NAME`_TCPWM_Stop();
		#else
			/* Disable Timer */
		    `$INSTANCE_NAME`_CONTROL_REG &= ((uint8)(~`$INSTANCE_NAME`_CTRL_ENABLE));
			
	        `$INSTANCE_NAME`_GLOBAL_ENABLE &= ((uint8)(~`$INSTANCE_NAME`_BLOCK_EN_MASK));
	        `$INSTANCE_NAME`_GLOBAL_STBY_ENABLE &= ((uint8)(~`$INSTANCE_NAME`_BLOCK_STBY_EN_MASK));
		#endif /* End of PSoC 3 and PSoC 5LP code */
    #endif /* End of Fixed Function code */
}

#if(!CY_PSOC4)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BeginTrimming
********************************************************************************
*
* Summary:
*  Sets and starts the CorrectionISR vector. This causes the trimming 
*  process to begin.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side effects: 
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_BeginTrimming(void) `=ReentrantKeil($INSTANCE_NAME . "_BeginTrimming")`
{
    uint8 isrOn;
    
    isrOn = `$INSTANCE_NAME`_CorrectionISR_GetState();
    if(isrOn == `$INSTANCE_NAME`_ISR_OFF)
    {
        `$INSTANCE_NAME`_CorrectionISR_Enable();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_StopTrimming
********************************************************************************
*
* Summary:
*  Disables the CorrectionISR vector, clears pedning interrupts. 
*  This causes the trimming process to stop.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects: 
*  Turns the isr off
*
*******************************************************************************/
void `$INSTANCE_NAME`_StopTrimming(void) `=ReentrantKeil($INSTANCE_NAME . "_StopTrimming")`
{
    uint8 isrOn;
    
    isrOn = `$INSTANCE_NAME`_CorrectionISR_GetState();
    if(isrOn != `$INSTANCE_NAME`_ISR_OFF)
    {
        `$INSTANCE_NAME`_CorrectionISR_Disable();
        `$INSTANCE_NAME`_CorrectionISR_ClearPending();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_RestoreTrim
********************************************************************************
*
* Summary: 
*  Restores ILO factory trim.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects: 
*  Turns off the isr.
*
*******************************************************************************/
void `$INSTANCE_NAME`_RestoreTrim(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreTrim")`
{
	`$INSTANCE_NAME`_CorrectionISR_ClearPending();
	`$INSTANCE_NAME`_CorrectionISR_Disable();
	
    #if (`$INSTANCE_NAME`_ILO_FREQUENCY == `$INSTANCE_NAME`_1kHz)
        CY_SET_REG8(CYREG_ILO_TR0, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR0) & `$INSTANCE_NAME`_FINE_TRIM_CLEAR)
            | (trimFactory & `$INSTANCE_NAME`_ILO_TR0_MASK));
        CY_SET_REG8(CYREG_ILO_TR1, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR1) & `$INSTANCE_NAME`_COARSE_TRIM_CLEAR)
            | ((uint8)((uint8)trimFactory >> `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR1_MASK));
    #else
        CY_SET_REG8(CYREG_ILO_TR0, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR0) & `$INSTANCE_NAME`_FINE_TRIM_CLEAR)
            | ((uint8)((uint8)trimFactory << `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR0_MASK));
        CY_SET_REG8(CYREG_ILO_TR1, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR1) & `$INSTANCE_NAME`_COARSE_TRIM_CLEAR)
            | ((uint8)((uint8)trimFactory >> `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR1_MASK));
    #endif /* End of ILO Frequency dependent code */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTrim
********************************************************************************
*
* Summary:
*  Returns the current ILO trim value
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_GetTrim(void) `=ReentrantKeil($INSTANCE_NAME . "_GetTrim")`
{
	uint8 trimVal;
	
	#if (`$INSTANCE_NAME`_ILO_FREQUENCY == `$INSTANCE_NAME`_1kHz)
		/* 1k ILO fine trim - TR0[3:0] reserved for 1kHz ILO */
		trimVal = (uint8)((`$INSTANCE_NAME`_ILO_TR0_MASK & CY_GET_REG8(CYREG_ILO_TR0))
                    | (uint8)((uint8)(`$INSTANCE_NAME`_ILO_TR1_MASK & CY_GET_REG8(CYREG_ILO_TR1)) 
                    << `$INSTANCE_NAME`_TRIM_SHIFT));
	#else
		/* 100k ILO fine trim - TR0[7:4] reserved for 100kHz ILO */
		trimVal = (uint8)((uint8)((uint8)(`$INSTANCE_NAME`_ILO_TR0_MASK & CY_GET_REG8(CYREG_ILO_TR0))
                    >> `$INSTANCE_NAME`_TRIM_SHIFT)
                    | (uint8)((uint8)(`$INSTANCE_NAME`_ILO_TR1_MASK & CY_GET_REG8(CYREG_ILO_TR1)) 
                    << `$INSTANCE_NAME`_TRIM_SHIFT));
	#endif /* End of ILO Frequency dependent code */
	
	return trimVal;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetTrim
********************************************************************************
*
* Summary:
*  Sets the ILO trim value
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTrim(uint8 trimVal) `=ReentrantKeil($INSTANCE_NAME . "_SetTrim")`
{
    #if (`$INSTANCE_NAME`_ILO_FREQUENCY == `$INSTANCE_NAME`_1kHz)
        CY_SET_REG8(CYREG_ILO_TR0, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR0) & `$INSTANCE_NAME`_FINE_TRIM_CLEAR)
            | (trimVal & `$INSTANCE_NAME`_ILO_TR0_MASK));
        CY_SET_REG8(CYREG_ILO_TR1, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR1) & `$INSTANCE_NAME`_COARSE_TRIM_CLEAR)
            | ((uint8)((uint8)trimVal >> `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR1_MASK));
    #else
        CY_SET_REG8(CYREG_ILO_TR0, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR0) & `$INSTANCE_NAME`_FINE_TRIM_CLEAR)
            | ((uint8)((uint8)trimVal << `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR0_MASK));
        CY_SET_REG8(CYREG_ILO_TR1, 
            (uint8)(CY_GET_REG8(CYREG_ILO_TR1) & `$INSTANCE_NAME`_COARSE_TRIM_CLEAR)
            | ((uint8)((uint8)trimVal >> `$INSTANCE_NAME`_TRIM_SHIFT) & `$INSTANCE_NAME`_ILO_TR1_MASK));
    #endif /* End of ILO Frequency dependent code */
}

#endif /* End of PSoC 3 and PSoC 5LP code */
/* End of non-PSoC 4 code */


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadCapture
*******************************************************************************
* Summary:
*  Retrieves the value held in the capture register.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_ReadCapture(void) CYREENTRANT
{
	uint16 captured;
    /* Get the captured counter value */
	#if (!`$INSTANCE_NAME`_USING_FIXED_FUNCTION)
        captured = CY_GET_REG8(`$INSTANCE_NAME`_CAPTURE_PTR);
	#else
		#if (CY_PSOC4)
			captured = (uint16)`$INSTANCE_NAME`_TCPWM_ReadCapture();
		#else
			captured = CY_GET_REG16(`$INSTANCE_NAME`_CAPTURE_LSB_PTR);
		#endif /* End of PSoC 3 and PSoC 5LP code */
	#endif /* End of Fixed Function code */
	
	return captured;
}


/******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadEdgeCount
*******************************************************************************
* Summary:
*  Calculates the edge count
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static uint16 `$INSTANCE_NAME`_ReadEdgeCount(void) CYREENTRANT
{
	uint16 edgecount, captureOld, captureNew;
	
	captureOld = `$INSTANCE_NAME`_ReadCapture();
	captureNew = `$INSTANCE_NAME`_ReadCapture();
	
	/* Make sure that the read value is correct (perhaps read on transition) */
	while (captureOld != captureNew)
	{	
		captureNew = `$INSTANCE_NAME`_ReadCapture();
		captureOld = `$INSTANCE_NAME`_ReadCapture();
	}
	
	/* Make the captured value into a real count number. Then add the offset term.    */
	/* The offsets are different for PSoC 4 */
    #if(CY_PSOC4)
        edgecount = (`$INSTANCE_NAME`_RESOLUTION - captureNew) - `$INSTANCE_NAME`_TIMER_OFFSET;
    #else
	    edgecount = (`$INSTANCE_NAME`_RESOLUTION - captureNew) + `$INSTANCE_NAME`_TIMER_OFFSET;
	#endif /* End of PSoC 3 and PSoC 5LP code */
    
	return edgecount;
}

/* [] END OF FILE */
