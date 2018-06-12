/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code of the API for the CapSense TMG component.
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"


static void `$INSTANCE_NAME`_SysTickISR(void);
uint32      `$INSTANCE_NAME`_currentTimestamp;
uint16 `$INSTANCE_NAME`_edgeSwipeCompleteTimeout = `$INSTANCE_NAME`_EDGE_SWIPE_COMPLETE_TIMEOUT;

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimerEnableInt
********************************************************************************
*
* Summary:
*  Enables Systick timer interrupts and configures the SystemTick timer callback
*  slot to the component function that updates the timestamp value.
*
* Parameters:
*  None
*
* Return:
*  Status
*     Value               Description
*    CYRET_SUCCESS       Successful
*    CYRET_INVALID_STATE Failure - no free callback slot was found
*
* Side Effects:
*  This function reinitialises the System Tick timer settings and callbacks so
*  that all the settings applied to the System Tick timer except for
*  the callback table will be lost and default parameters will be set.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_TimerEnableInt(void)
{
    uint32 i;
    cySysTickCallback sysTickCallbacks[CY_SYS_SYST_NUM_OF_CALLBACKS];
    cySysTickCallback sysTickCallbackAddress;
    cystatus retValue = CYRET_INVALID_STATE;

    for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
    {
        sysTickCallbacks[i] = (void *) 0;
    }

    `$INSTANCE_NAME`_currentTimestamp = 0u;

    /* If SysTick timer wasn't configured */
    if (CySysTickInitVar == 0u)
    {
        /* SysTick timer seems to be not configured.
         * Configure SysTick timer and set callback.
         */
        CySysTickStart();
        (void)CySysTickSetCallback(0u, &`$INSTANCE_NAME`_SysTickISR);
        retValue = CYRET_SUCCESS;
    }
    else
    {
        /* If SysTick timer was configured save user callbacks */
        for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
        {
            sysTickCallbackAddress = CySysTickGetCallback(i);

            /* Make sure that callback slot is used */
            if (sysTickCallbackAddress != (void *) 0 )
            {
                /* Save address if it wasn't set by this component */
                if (sysTickCallbackAddress != &`$INSTANCE_NAME`_SysTickISR)
                {
                    sysTickCallbacks[i] = sysTickCallbackAddress;
                }
                else
                {
                    /* In case there already is one callback from `$INSTANCE_NAME`*/
                    retValue = CYRET_SUCCESS;
                }
            }
            else if (CYRET_SUCCESS != retValue)
            {
                /* If there was a free callback slot - use it */
                sysTickCallbacks[i] = &`$INSTANCE_NAME`_SysTickISR;
                retValue = CYRET_SUCCESS;
            }
            else
            {
                /* Skip empty slot if we already added one for component */
            }
        }

        if (CYRET_SUCCESS == retValue)
        {
            /* Reset System Tick timer configuration */
            CySysTickInitVar = 0u;
            CySysTickStart();

            /* Restore user callbacks if any and set own callback */
            for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
            {
                (void)CySysTickSetCallback(i, sysTickCallbacks[i]);
            }
        }
    }

    return (retValue);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_TimerDisableInt
********************************************************************************
*
* Summary:
*  Disables Systick timer interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Stops the SysTick timer if there are no active callback slots left and
*  disables SysTick interrupt.
*
*******************************************************************************/
void `$INSTANCE_NAME`_TimerDisableInt(void)
{
    uint32 i;
    uint32 nullPointers = 0u;


    /* Find used callback slot */
    for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; i++)
    {
        if (CySysTickGetCallback(i) == &`$INSTANCE_NAME`_SysTickISR)
        {
            /* Free callback */
            (void)CySysTickSetCallback(i, (void *) 0 );
            nullPointers++;
        }
        else if (CySysTickGetCallback(i) == (void *) 0 )
        {
            /* This callback slot is unused */
            nullPointers++;
        }
        else
        {
            /* This callback slot is used by some function */
        }
    }

    if (nullPointers == CY_SYS_SYST_NUM_OF_CALLBACKS)
    {
        /* If there are no used callback slots - disable SysTick timer */
        CySysTickDisableInterrupt();
        CySysTickStop();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_DecodeAllGestures
********************************************************************************
*
* Summary:
*  Decodes all enabled gestures in the customizer and returns the detected
*  gesture code.
*  `$INSTANCE_NAME`_InitGestures and `$INSTANCE_NAME`_TimerEnableInt has to be
*  called once prior calling this or any other API for gesture decoding.
*
* Parameters:
*  touchNumber: Number of fingers on the trackpad. Valid range 0-2.
*  pos: Pointer to structure with coordinates of touches.
*
* Return:
*  Detected gesture code.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_DecodeAllGestures(uint32 touchNumber, const `$INSTANCE_NAME`_POSITION_STRUCT *pos)
{
    uint32 gestureID = `$INSTANCE_NAME`_NO_GESTURE;

    /* Variable for detected click gestures */
    uint32 clickGesture = `$INSTANCE_NAME`_NO_GESTURE;

    /* Variable for detected single touch gestures */
    uint32 stGesture = `$INSTANCE_NAME`_NO_GESTURE;

    /* Variable for detected double touch gestures */
    uint32 dtGesture = `$INSTANCE_NAME`_NO_GESTURE;

    #if (`$INSTANCE_NAME`_ROTATE_ENABLED != 0u)
        static uint32 rotationActive = 0u;
    #endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED != 0u) */

	#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)
		static uint32 edgeTimeoutStamp = 0u;
		uint32 deltaTimeoutStamp = 0u;
    #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u) */
	
    #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                         (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                         (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
        static uint32 edgeSwipeActive = 0u;
    #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                               (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                               (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */

    #if ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                     (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                     (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
        static uint32 clickAndDragActive = 0u;
    #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                           (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                           (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */

    #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
        uint32 edgeSwipeGesture = `$INSTANCE_NAME`_NO_GESTURE;
    #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */

	#if ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u))
		clickGesture = Gesture_DecodeAllClickGestures((uint8)touchNumber, `$INSTANCE_NAME`_currentTimestamp, pos);
	#endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) || (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)) */
	
    #if (`$INSTANCE_NAME`_CLICKS_ENABLED != 0u)
		gestureID = clickGesture;
        #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) || (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u))
        if (clickGesture == `$INSTANCE_NAME`_CLICK_AND_DRAG)
        {
            clickAndDragActive = 1u;
        }
        #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) || (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)) */
    #endif /* (`$INSTANCE_NAME`_CLICKS_ENABLED != 0u) */

    #if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
        stGesture = Gesture_DecodeSTRotateGestures((uint8)touchNumber, `$INSTANCE_NAME`_currentTimestamp, pos);

        #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) || (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u))
            #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u))
                if ((clickAndDragActive == 1) || (edgeSwipeActive == 1u))
            #elif (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
                if (clickAndDragActive == 1)
            #elif (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
                if (edgeSwipeActive == 1u)
            #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)) */
            {
                stGesture = `$INSTANCE_NAME`_NO_GESTURE;
            }
        #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) || (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)) */
        if ((stGesture == `$INSTANCE_NAME`_ROTATE_CW) || (stGesture == `$INSTANCE_NAME`_ROTATE_CCW))
        {
            rotationActive = `$INSTANCE_NAME`_ROTATE_TO_OTHER_DEBOUNCE;
        }
        else
        {
            if (rotationActive > 0u)
            {
                rotationActive--;
            }
        }

        if (((stGesture == `$INSTANCE_NAME`_NO_GESTURE)||(stGesture == `$INSTANCE_NAME`_TOUCHDOWN) \
                                        ||(stGesture == `$INSTANCE_NAME`_LIFT_OFF))&&(rotationActive == 0u))
    #else
        if ((stGesture == `$INSTANCE_NAME`_NO_GESTURE)||(stGesture == `$INSTANCE_NAME`_TOUCHDOWN) \
                                        ||(stGesture == `$INSTANCE_NAME`_LIFT_OFF))
    #endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */
    {
        #if (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)
            #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u))
                if ((clickAndDragActive == 0u)&&(edgeSwipeActive == 0u))
            #elif (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)
                if (clickAndDragActive == 0u)
            #elif (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
                if (edgeSwipeActive == 0u)
            #else
                if (1u == 1u)
            #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && (`$INSTANCE_NAME`_CLICKS_ENABLED == 1u)) */
            {
                stGesture = Gesture_DecodeSTScrollGestures((uint8)touchNumber, `$INSTANCE_NAME`_currentTimestamp, pos);
            }
        #elif (`$INSTANCE_NAME`_FLICKS_ENABLED == 1u)
            stGesture = Gesture_DecodeFlickGestures((uint8)touchNumber, `$INSTANCE_NAME`_currentTimestamp, pos);
        #endif /* (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) */
    }

    #if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u)
        edgeSwipeGesture = Gesture_DecodeEdgeSwipeGestures((uint8)touchNumber, `$INSTANCE_NAME`_currentTimestamp, pos);

        #if (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)
            if (((edgeSwipeGesture != `$INSTANCE_NAME`_NO_GESTURE) && \
                (edgeSwipeGesture != `$INSTANCE_NAME`_TOUCHDOWN) && (edgeSwipeGesture != `$INSTANCE_NAME`_LIFT_OFF)) \
                                                                                        && (rotationActive == 0u))
        #else
            if ((edgeSwipeGesture != `$INSTANCE_NAME`_NO_GESTURE) && \
                (edgeSwipeGesture != `$INSTANCE_NAME`_TOUCHDOWN) && (edgeSwipeGesture != `$INSTANCE_NAME`_LIFT_OFF))
        #endif /* (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u) */
        {
            stGesture = edgeSwipeGesture;
            #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                                 (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                                 (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
                edgeSwipeActive = 1u;
            #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) ||\
                                                                       (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                                       (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */
        }
    #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) */

    if ((stGesture != `$INSTANCE_NAME`_NO_GESTURE)&&(stGesture != `$INSTANCE_NAME`_TOUCHDOWN) \
                                        &&(stGesture != `$INSTANCE_NAME`_LIFT_OFF))
    {
        gestureID = stGesture;
    }
    else if ((clickGesture == `$INSTANCE_NAME`_TOUCHDOWN) || (clickGesture == `$INSTANCE_NAME`_LIFT_OFF))
    {
        gestureID = clickGesture;
    }
    else
    {
        /* Do not change gestureID */
    }

    dtGesture = `$INSTANCE_NAME`_DecodeZoomGestures(touchNumber, pos);
    if ((dtGesture == `$INSTANCE_NAME`_NO_GESTURE) || (dtGesture == `$INSTANCE_NAME`_TOUCHDOWN) \
                                        || (dtGesture == `$INSTANCE_NAME`_LIFT_OFF))
    {
        dtGesture = `$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber, pos);
    }
    else
    {
        (void)`$INSTANCE_NAME`_DecodeDTScrollGestures(touchNumber, pos);
    }

    if ((dtGesture != `$INSTANCE_NAME`_NO_GESTURE) && (dtGesture != `$INSTANCE_NAME`_TOUCHDOWN) \
                                        && (dtGesture != `$INSTANCE_NAME`_LIFT_OFF))
    {
        gestureID = dtGesture;
    }
	
	#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)
		if((gestureID >= `$INSTANCE_NAME`_EDGE_SWIPE_LEFT)&&(gestureID <= `$INSTANCE_NAME`_EDGE_SWIPE_BOTTOM))
		{
			edgeTimeoutStamp = `$INSTANCE_NAME`_currentTimestamp;
		}
    #endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u) */

    if ((clickGesture == `$INSTANCE_NAME`_LIFT_OFF) || (clickGesture == `$INSTANCE_NAME`_TOUCHDOWN) || \
            (gestureID == `$INSTANCE_NAME`_NO_GESTURE))
    {
        #if ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                         (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                         (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u)))
			if(0u != clickAndDragActive)
			{
				clickAndDragActive = 0u;
			}
        #endif /* ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) && ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) ||\
                                                               (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u) ||\
                                                               (`$INSTANCE_NAME`_ROTATE_ENABLED == 1u))) */
        
		#if (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u)
		deltaTimeoutStamp = `$INSTANCE_NAME`_currentTimestamp - edgeTimeoutStamp;
        if ((clickGesture == `$INSTANCE_NAME`_LIFT_OFF) || (deltaTimeoutStamp >= (`$INSTANCE_NAME`_edgeSwipeCompleteTimeout)))
        {
		    edgeTimeoutStamp = 0u;
            #if ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) || \
                                                                        (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u)))
				if(0u != edgeSwipeActive)
				{
					edgeSwipeActive = 0u;
				}
				
            #endif /* ((`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED == 1u) && ((`$INSTANCE_NAME`_CLICKS_ENABLED == 1u) || \
                                                                        (`$INSTANCE_NAME`_ST_SCROLLS_ENABLED == 1u))) */
        }
		#endif /* (`$INSTANCE_NAME`_EDGE_SWIPE_ENABLED != 0u) */
    }

    return (gestureID);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SysTickISR
********************************************************************************
*
* Summary:
*  Interrupt routine for System Tick Timer
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void `$INSTANCE_NAME`_SysTickISR(void)
{
    `$INSTANCE_NAME`_currentTimestamp++;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ballisticsMultiplier
********************************************************************************
*
* Summary:
*  This API is to run the ballistic Multiplier.
*  `$INSTANCE_NAME`_TimerEnableInt has to be called once prior calling this API.
*
* Parameters:
*   ballisticMultiplier: Pointer to the structure which contains API parameters.
*   pos: Pointer to dX and dY coordinates.
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_BallisticsMultiplier(const `$INSTANCE_NAME`_BALLISTIC_MULT * ballisticMultiplier, int16 *pos)
{
    #if (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u)
        `$INSTANCE_NAME`_BALLISTIC_MULT_INT ballisticsStrct;
        ballisticsStrct.paramStr = *ballisticMultiplier;
        ballisticsStrct.currentTimestamp = `$INSTANCE_NAME`_GetTimerGlobalCounter();
        BallisticMultiplier_TMG_v1_00(&ballisticsStrct, pos);
    #endif /* (`$INSTANCE_NAME`_BALLISTICS_ENABLED == 1u) */
}


/* [] END OF FILE */
