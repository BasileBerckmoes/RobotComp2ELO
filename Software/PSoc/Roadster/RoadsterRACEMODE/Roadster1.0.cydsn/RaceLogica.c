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

uint8 IRsensorGewicht[] = {0,100,220,255,255,220,100,0};//{0,180,235,255,235,210,180,0};////{0,25,40,55  ,55,40,25,0}; ////{0,80,120,170  ,170,120,80,0};//{0,80,120,200  ,200,120,80,0};
uint8 IRDigitaleWaarden[8];

uint8 TweedeLijnGedetecteerd = 0;

uint8 Data;
uint8 DataOrgineel;

void AnalyseerData(uint8 data)
{
    if ((data & 11000000) == 11000000 ) data = 0b10000000;
    else if ((data & 00000011) == 00000011 ) data = 0b00000001;
    DataOrgineel = data;
    PlaatsIRWaardenInArray(DataOrgineel);
    Data = CheckVoor2eLijn();
    //printBINopLCD(DataOrgineel, 0);
    //printBINopLCD(Data, 1);
    //if (Data != DataOrgineel) PlaatsIRWaardenInArray(Data);
    
    stuurMotorenBij();
}

uint8 bepaalLijnDikte()
{
    uint8 teller = 0;
    uint8 diksteLijn = 0;
    for(int i = 0; i < 8; i++)
    {
        if (IRDigitaleWaarden[i] == 1) teller++;
        else {
            if (teller > diksteLijn)
            {
                diksteLijn = teller;
                teller = 0;
            } 
        }
     }
        
     if (teller > diksteLijn)diksteLijn = teller;
     return diksteLijn;
}

void stuurMotorenBij(void)
{ 
    for(int i = 3; i >= 0; i--) //linkse kant van de sensoren afgaan
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
    
    for(int i = 4; i <= 7; i++)
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
     uint8 aantalWaardeWisselingen = 1;  
    
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
        
        LCD_Position(0u,10u);
        LCD_PrintInt16(aantalWaardeWisselingen);  
         LCD_Position(1u,10u);
        LCD_PrintInt16(diksteLijn);  
        if (aantalWaardeWisselingen <= 3)
        {
            return Data;
        }
        else
        {
            uint8 compareValue = 1;
            
            for (int i = 0; i < diksteLijn; i++)
            {
                compareValue = compareValue | exponent(2,i);
            }
            for (uint8 i = 0; i < (8 - diksteLijn); i++)
            {
                uint8 test = compareValue & DataOrgineel;
                
                if((compareValue & DataOrgineel) == compareValue) return compareValue;
                compareValue = (compareValue << 1);
            }
        }
    return 0;
}
/* [] END OF FILE */
