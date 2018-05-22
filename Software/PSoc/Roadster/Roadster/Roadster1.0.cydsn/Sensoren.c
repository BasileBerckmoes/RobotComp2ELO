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



/* [] END OF FILE */
