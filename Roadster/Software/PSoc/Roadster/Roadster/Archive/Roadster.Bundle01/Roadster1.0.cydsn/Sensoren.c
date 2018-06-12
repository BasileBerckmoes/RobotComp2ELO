/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "projectMain.h"
#include "project.h"

//Interupt "end of conversion" van SAR_ADC 
CY_ISR(IRSensoren)
{
	//uint8 tmpWaarden = IRWaarden;
	IRWaarden = 0;
    for(int i = 0; i < 8; i++)
    {
	    if (ADC_IR_GetResult16(i) > IRDrempel)
	    {
	        uint8 tmpWaarde = exponent(2,i); 
	        IRWaarden = IRWaarden | tmpWaarde;
	    }   
    }
    //IRWaarden =~IRWaarden;
}

uint16 readUSValue(void)
{
	while(statusEcho_Read() == 0)
		{
			TriggerReg_Write(1);
			CyDelayUs(10);
			TriggerReg_Write(0);
		}
	while(statusEcho_Read() == 1){}
	return TimerUS_ReadCounter();
}

void schuifRegister(uint16 array[], uint16 newValue)
{
	for(int i = 3; i >= 0; i--)
	{
		uint16 tmpvalue = avgUS1[i];
		array[i + 1] = tmpvalue;
	}
	array[0] = newValue;
}

void berekenMediaan(uint16 array[]) 
{ 
	//uint16 tmp = 0;
	uint16 tmpArray[] = {UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX};
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++) 
		{
			if (array[j] < tmpArray[i]) tmpArray[i] = array[j];
		}
	}
	mediaan = tmpArray[3];
}  

/* [] END OF FILE */
