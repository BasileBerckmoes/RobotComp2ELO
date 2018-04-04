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

uint8 IRsensorGewicht[] = {170,200,230,255  ,255,230,200,170};
uint8 IRDigitaleWaarden[8];

uint8 TweedeLijnGedetecteerd = 0;

uint8 Data;

void AnalyseerData(uint8 data)
{
    Data = data;
    PlaatsIRWaardenInArray();
    stuurMotorenBij();
}

void stuurMotorenBij(void)
{ 
    for(int i = 0; i < 4; i++)
	{
        if (IRDigitaleWaarden[i] == 1)
        {
            pwmMotor1 = IRsensorGewicht[i];
            break;
        }
    }
    for(int i = 7; i > 3; i--)
	{
        if (IRDigitaleWaarden[i] == 1)
        {
            pwmMotor2 = IRsensorGewicht[i];
            break;
        }
    }
    
}

void PlaatsIRWaardenInArray(void)
{
    for(int i = 0; i < 8; i++)
	{
		uint8 tmpWaarde =  exponent(2,i);
		if ((Data & tmpWaarde) == tmpWaarde)
		{
			IRDigitaleWaarden[i]= 1;
		}
			else 
		{
			IRDigitaleWaarden[i]= 0;
		}  
	 }  
}

//uint8 CheckVoor2eLijn()
//{
//    
//}
/* [] END OF FILE */
