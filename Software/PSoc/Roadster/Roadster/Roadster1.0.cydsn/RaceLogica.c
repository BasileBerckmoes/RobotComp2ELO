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

uint8 IRsensorGewicht[] = {0,80,120,170  ,170,120,80,0};//{0,80,120,200  ,200,120,80,0};
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
            pwmMotorLinks = IRsensorGewicht[i];
            break;
        }
        pwmMotorLinks = IRsensorGewicht[3];
    }
    for(int i = 7; i > 3; i--)
	{
        if (IRDigitaleWaarden[i] == 1)
        {
            pwmMotorRechts = IRsensorGewicht[i];
             break;
        }
         pwmMotorRechts = IRsensorGewicht[3];
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
//  uint8 flag = 0;
//    
//  for(int i = 0; i < 8; i++)
//  {
//    
//  }  
//}
/* [] END OF FILE */
