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

uint8 IRsensorGewicht[] = {40,120,170,220,220,170,120,40};////{0,25,40,55  ,55,40,25,0}; ////{0,80,120,170  ,170,120,80,0};//{0,80,120,200  ,200,120,80,0};
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
    for(int i = 0; i < 4; i++) //linkse kant van de sensoren afgaan
	{
        if (IRDigitaleWaarden[i] == 1) //indien er een zwarte lijn is op de sensor
        {
            pwmMotorLinks = IRsensorGewicht[i];
            if (i == 0) pwmMotorRechts = 255;
            else if (i == 1) pwmMotorRechts = 240;
            else if (i == 2) pwmMotorRechts = 225;
            else if (i == 3) pwmMotorRechts = 255;//IRsensorGewicht[i];
            break;
        }
    }
    for(int i = 7; i > 3; i--)
	{
        if (IRDigitaleWaarden[i] == 1)
        {
            pwmMotorRechts = IRsensorGewicht[i];
            if (i == 7) pwmMotorLinks = 255;
            else if (i == 6) pwmMotorLinks = 240;
            else if (i == 5) pwmMotorLinks = 225;
            else if (i == 4) pwmMotorLinks = 255;
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
//  uint8 flag = 0;
//    
//  for(int i = 0; i < 8; i++)
//  {
//    
//  }  
//}
/* [] END OF FILE */
