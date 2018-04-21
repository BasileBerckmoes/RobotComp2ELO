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

uint8 IRsensorGewicht[] = {0,180,235,255,235,210,180,0};////{0,25,40,55  ,55,40,25,0}; ////{0,80,120,170  ,170,120,80,0};//{0,80,120,200  ,200,120,80,0};
uint8 IRDigitaleWaarden[8];

uint8 TweedeLijnGedetecteerd = 0;

uint8 Data;
uint8 DataOrgineel;

void AnalyseerData(uint8 data)
{
    DataOrgineel = data;
    PlaatsIRWaardenInArray(DataOrgineel);
    Data = CheckVoor2eLijn();
    if (Data != DataOrgineel) PlaatsIRWaardenInArray(Data);
    
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

void PlaatsIRWaardenInArray(uint8 value)
{
    for(int i = 0; i < 8; i++)
	{
		uint8 tmpWaarde =  exponent(2,i);
		if ((value & tmpWaarde) == tmpWaarde)
		{
			IRDigitaleWaarden[i]= 1;
		}
			else 
		{
			IRDigitaleWaarden[i]= 0;
		}  
	 }  
}

uint8 CheckVoor2eLijn()
{
    uint8 diksteLijn = 0;
    uint8 teller = 0;
    
     uint8 laatsteWaarde = 0; 
     uint8 aantalWaardeWisselingen = 0;  
    
        for(int i = 0; i < 8; i++)
        {
            if (laatsteWaarde != IRDigitaleWaarden[i])
            {
                aantalWaardeWisselingen++;
                laatsteWaarde = IRDigitaleWaarden[i];
            } 
            if (IRDigitaleWaarden[i] == 1) teller++;
            else {
                if (teller > diksteLijn)
                {
                    diksteLijn = teller;
                    teller = 0;
                } 
            }
        }
        
        if (aantalWaardeWisselingen <= 3)
        {
            return Data;
        }
        else
        {
            uint8 compareValue = 1;
            compareValue = compareValue << (diksteLijn-1);
            for (uint8 i = 0; i < (8 - diksteLijn); i++)
            {
                if((compareValue & DataOrgineel) == compareValue) return compareValue;
            }
        }
    return 0;
}
/* [] END OF FILE */