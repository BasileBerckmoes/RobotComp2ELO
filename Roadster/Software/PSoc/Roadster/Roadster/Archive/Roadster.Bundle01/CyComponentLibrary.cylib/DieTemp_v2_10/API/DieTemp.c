/*******************************************************************************
* File Name: `$INSTANCE_NAME`_DieTemp.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  Provides the API to acquire the die temperature.
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.H>
#include <`$INSTANCE_NAME`.h>


#define `$INSTANCE_NAME`_NUMBER_OF_SAMPLES      (0x1u)
#define `$INSTANCE_NAME`_TIMER_PERIOD           (0xFFFu)
#define `$INSTANCE_NAME`_CLK_DIV_SELECT         (0x4u)
#define `$INSTANCE_NAME`_SPC_CLK_PERIOD         (120u) /* In nano seconds. */
#define `$INSTANCE_NAME`_NANO_TO_MILLI_FACTOR   (1000000u)
#define `$INSTANCE_NAME`_FRM_EXEC_TIME          (1000u) /* In nano seconds. */

#define `$INSTANCE_NAME`_GET_TEMPR_TIME     (uint32)(((((uint32)1u << (`$INSTANCE_NAME`_NUMBER_OF_SAMPLES + 1u))) * \
                                                ((uint32)(`$INSTANCE_NAME`_SPC_CLK_PERIOD * \
                                                `$INSTANCE_NAME`_CLK_DIV_SELECT)) * \
                                                ((uint32)`$INSTANCE_NAME`_TIMER_PERIOD)) + \
                                                (uint32)`$INSTANCE_NAME`_FRM_EXEC_TIME)

#define `$INSTANCE_NAME`_MAX_WAIT           (uint16)(((`$INSTANCE_NAME`_GET_TEMPR_TIME + \
                                                `$INSTANCE_NAME`_NANO_TO_MILLI_FACTOR) - 1u) / \
                                                `$INSTANCE_NAME`_NANO_TO_MILLI_FACTOR)  /* In milli seconds */
#define `$INSTANCE_NAME`_MAX_WAIT_USEC          (`$INSTANCE_NAME`_MAX_WAIT * 1000u)    /* In usec */
#define `$INSTANCE_NAME`_USEC_STEP              (10u) /* Step in usec */

static cystatus `$INSTANCE_NAME`_GetTempT(int16 * temperature);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  Sends the command and parameters to the SPC to start a Die Temperature 
*  reading. This function returns before the SPC finishes. 
*  This function call must always be paired with a call to the DieTemp_Query()
*  API to complete the Die Temperature read
*
* Parameters:
*  void.
*
* Return:
*  CYRET_STARTED if the spc command startes successfully.
*  CYRET_UNKNOWN if the spc command failes.
*  CYRET_LOCKED if the spc is busy.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    cystatus status;

    /* Plan for failure. */
    status = CYRET_UNKNOWN;

    /* Power up the SPC. */
    CySpcStart();

    if(CySpcLock() == CYRET_SUCCESS)
    {
        #if(CY_PSOC5A)
            if(CYRET_STARTED == CySpcGetTemp(`$INSTANCE_NAME`_NUMBER_OF_SAMPLES,
                                             `$INSTANCE_NAME`_TIMER_PERIOD,
                                             `$INSTANCE_NAME`_CLK_DIV_SELECT))
            {
                status = CYRET_STARTED;
            }
        #else
            if(CYRET_STARTED == CySpcGetTemp(`$INSTANCE_NAME`_NUMBER_OF_SAMPLES))
            {
                status = CYRET_STARTED;
            }
        #endif  /* (CY_PSOC5A) */
        CySpcUnlock();
    }
    else
    {
        status = CYRET_LOCKED;
    }
    return (status);
}


/*******************************************************************************
* FUNCTION NAME:   `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  There is no need to stop or disable this component. This component is
*  naturally a slave that sends request to SPC through SPC API of cy_boot
*  and waits for data to be ready or in the case of non-blocking operation it
*  sends the request to SPC and the user can manually poll the result.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{
    /* There aren't anything to stop */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Query
********************************************************************************
*
* Summary:
*  Checks to see if the SPC command started by DieTemp_Start() has finished. 
*  If the command has not finished, the temperature value is not read and
*  returned. The caller will need to poll this function while the return status 
*  remains CYRET_STARTED.
*  This can be used only in conjunction with the DieTemp_Start() API to 
*  successfully get the correct Die Temperature.
*  The Die Temperature reading returned on the first sequence of DieTemp_Start() 
*  followed by DieTemp_Query() can be unreliable, so you must do this sequence
*  twice and use the value returned from the second sequence.
*
* Parameters:
*  temperature: Address to store the two-byte temperature value.
*
* Return:
*  CYRET_SUCCESS if the temperature command completes successfully.
*  CYRET_UNKNOWN if the spc failures.
*  CYRET_STARTED if the temperature command has not completed.
*  CYRET_TIMEOUT if waites too long before reading data.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_Query(int16 * temperature) `=ReentrantKeil($INSTANCE_NAME . "_Query")`
{
    uint8 temp[2u];
    cystatus status;

    if(CY_SPC_BUSY)
    {
        if((CY_SPC_STATUS_REG>>2u) == CYRET_SUCCESS)
        {
            /* See if any data is ready. */
            if(CY_SPC_DATA_READY)
            {
                temp[0u] = CY_SPC_CPU_DATA_REG;
                /* Wait for second byte to be ready */
                while(!CY_SPC_DATA_READY)
                {
                    CyDelayUs(1u);
                }
                temp[1u] = CY_SPC_CPU_DATA_REG;
                status = CYRET_SUCCESS;
            }
            else
            {
            	status = CYRET_STARTED;
            }

            if (status == CYRET_SUCCESS)
            {
                if(temp[0u] == 1u)
                {
                    *temperature = (int16) ((uint16) temp[1]);
                }
                else
                {
                    *temperature = (int16) - ((int16) temp[1]);
                }
                status = CYRET_SUCCESS;
            }
        }
        else
        {
            status = CYRET_STARTED;
        }
    }
    else
    {
        status = CYRET_TIMEOUT;
    }

    if(status != CYRET_STARTED)
    {
        /* Unlock the SPC so someone else can use it. */
        CySpcUnlock();
    }

    return (status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTempT
********************************************************************************
*
* Summary:
*  Sends the command and parameters to the SPC to start a Die Temperature 
*  reading and waits until it fails or completes. This is a blocking function.
*  This function starts the temperature reading and returns the temperature 
*  value after the SPC temperature command completes successfully.
*
* Parameters:
*  temperature: Address to store the two byte temperature value.
*
* Return:
*  CYRET_SUCCESS if the command completes successfully.
*  The Status code from `$INSTANCE_NAME`_Start or `$INSTANCE_NAME`_Query.
*
*******************************************************************************/
static cystatus `$INSTANCE_NAME`_GetTempT(int16 * temperature) `=ReentrantKeil($INSTANCE_NAME . "_GetTempT")`
{
    uint16 us;
    cystatus status;

    /* Start the temp reading */
    status = `$INSTANCE_NAME`_Start();

    if(status == CYRET_STARTED)
    {
        /**************************************************************************
        * Wait for SPC to finish temperature reading. If state changes and SPC
        * finishes - break cycle.
        * `$INSTANCE_NAME`_MAX_WAIT_USEC is maximum time in usec to wait for SPC.
        **************************************************************************/
        for (us=(`$INSTANCE_NAME`_MAX_WAIT_USEC); us>0u; us-=`$INSTANCE_NAME`_USEC_STEP)
        {
            if((CYRET_STARTED != status)&&(CY_SPC_IDLE))
            {
                break;
            }
            else if(CYRET_STARTED == status)
            {
                status = `$INSTANCE_NAME`_Query(temperature);
            }
            else
            {
                /* SPC has not finished reading or isn't idle */
            }
            CyDelayUs(`$INSTANCE_NAME`_USEC_STEP);
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTemp
********************************************************************************
*
* Summary:
*  Sends the command and parameters to the SPC to start a Die Temperature 
*  reading and waits until it fails or completes. This is a blocking API.
*  This function reads the Die Temperature twice and returns the second value
*  to work around an issue in the silicon that causes the first value read 
*  to be unreliable.
*
* Parameters:
*  temperature: Address to store the two byte temperature value.
*
* Return:
*  CYRET_SUCCESS if the command completes successfully.
*  The Status code from `$INSTANCE_NAME`_Start or `$INSTANCE_NAME`_Query.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_GetTemp(int16 * temperature) `=ReentrantKeil($INSTANCE_NAME . "_GetTemp")`
{
    cystatus status;
    uint8 count = 2u;
    while (count != 0u)
    {
        status = `$INSTANCE_NAME`_GetTempT(temperature);
        if (status != CYRET_SUCCESS)
        {
            break;
        }
        count--;
    }
    return status;
}


/* [] END OF FILE */
