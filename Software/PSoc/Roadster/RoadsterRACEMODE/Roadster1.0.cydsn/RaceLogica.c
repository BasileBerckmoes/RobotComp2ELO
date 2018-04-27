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

uint8 indexLijn = 0;

uint8 Data;

uint8 boolIsVanLijn;

uint8 laatsteKant = 0; //0 = geen invloed, 100 = linkse kant laatste gedetecteerd, 200= rechts laatste detectie
uint16 antiSlipTeller = 0;

void AnalyseerData(uint8 data)
{
    if (((data & 11000000) == 11000000) /*|| ((data & 11100000) == 11100000) || ((data & 11110000) == 11110000) || ((data & 11111000) == 11111000)*/) data = 0b10000000;
    else if ((data & 00000011) == 00000011 /*|| ((data & 00000111) == 00000111) || ((data & 00001111) == 00001111) || ((data & 00011111) == 00011111)*/)  data = 0b00000001;
    Data = data;
    PlaatsIRWaardenInArray(Data);
    if (richting == 255) stuurMotorenBijLNR();
    else if (richting == 0) stuurMotorenBijRNL();

   
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
                indexLijn = i - diksteLijn;
                teller = 0;
            } 
        }
     }
        
     if (teller > diksteLijn)diksteLijn = teller;
     return diksteLijn;
}

void stuurMotorenBijRNL(void)
{ 
    
     for(int i = 7; i > 3; i--)// for(int i = 4; i <= 7; i++)
	{
        if (IRDigitaleWaarden[i] == 1)
        {
            antiSlipTeller = 0;
            if (i == 7) laatsteKant = 200;
            else laatsteKant = 0;
            
            pwmMotorRechts = IRsensorGewicht[i];
            
            if (i == 7) pwmMotorLinks = 255;
            else if (i == 6) pwmMotorLinks = 240;
            else if (i == 5) pwmMotorLinks = 225;
            else if (i == 4) pwmMotorLinks = 255;
            return;
        }
    }
    //Zet de eerste for loop in commentaar indien de robot met de klok mee rijd
    /*for(int i = 0; i < 4; i++)*/ for(int i = 3; i >= 0; i--) //linkse kant van de sensoren afgaan
	{
        if (IRDigitaleWaarden[i] == 1) //indien er een zwarte lijn is op de sensor
        {
            antiSlipTeller = 0;
            if (i == 0) laatsteKant = 100;
            else laatsteKant = 0;
            
            pwmMotorLinks = IRsensorGewicht[i];
           
            if (i == 0) pwmMotorRechts = 255;
            else if (i == 1) pwmMotorRechts = 240;
            else if (i == 2) pwmMotorRechts = 225;
            else if (i == 3) pwmMotorRechts = 255;//IRsensorGewicht[i];
            return;
        }
    }
    //Zet tweede for loop in commentaar indien de robot met de klok mee rijd
   
        
    if (antiSlipTeller < UINT16_MAX && laatsteKant != 0)
    {
        antiSlipTeller++;
    }   
    if ( antiSlipTeller > 300 && laatsteKant != 0)
    {
        if (laatsteKant == 100)
        {
            if (pwmMotorLinks < 255) pwmMotorLinks = pwmMotorLinks + 2;
        }
        
        
        else if (laatsteKant == 200) 
        {
            if (pwmMotorRechts < 255) pwmMotorRechts = pwmMotorRechts + 2;
        }
    }
}

void stuurMotorenBijLNR(void)
{ 
    //Zet de eerste for loop in commentaar indien de robot met de klok mee rijd
    for(int i = 0; i < 4; i++) //for(int i = 3; i >= 0; i--) //linkse kant van de sensoren afgaan
	{
        if (IRDigitaleWaarden[i] == 1) //indien er een zwarte lijn is op de sensor
        {
            antiSlipTeller = 0;
            if (i == 0) laatsteKant = 100;
            else laatsteKant = 0;
            
            pwmMotorLinks = IRsensorGewicht[i];
           
            if (i == 0) pwmMotorRechts = 255;
            else if (i == 1) pwmMotorRechts = 240;
            else if (i == 2) pwmMotorRechts = 225;
            else if (i == 3) pwmMotorRechts = 255;//IRsensorGewicht[i];
            return;
        }
    }
    //Zet tweede for loop in commentaar indien de robot met de klok mee rijd
    /*for(int i = 7; i > 3; i--)*/ for(int i = 4; i <= 7; i++)
	{
        if (IRDigitaleWaarden[i] == 1)
        {
            antiSlipTeller = 0;
            if (i == 7) laatsteKant = 200;
            else laatsteKant = 0;
            
            pwmMotorRechts = IRsensorGewicht[i];
            
            if (i == 7) pwmMotorLinks = 255;
            else if (i == 6) pwmMotorLinks = 240;
            else if (i == 5) pwmMotorLinks = 225;
            else if (i == 4) pwmMotorLinks = 255;
            return;
        }
    }
        
    if (antiSlipTeller < UINT16_MAX && laatsteKant != 0)
    {
        antiSlipTeller++;
    }   
    if ( antiSlipTeller > 300 && laatsteKant != 0)
    {
        if (laatsteKant == 100)
        {
            if (pwmMotorLinks < 255) pwmMotorLinks = pwmMotorLinks + 2;
        }
        
        
        else if (laatsteKant == 200) 
        {
            if (pwmMotorRechts < 255) pwmMotorRechts = pwmMotorRechts + 2;
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

//uint8 CheckVoor2eLijn()
//{
//    uint8 diksteLijn = 0;
//    uint8 teller = 0;
//    
//     uint8 laatsteWaarde = 0; 
//     uint8 aantalWaardeWisselingen = 1;  
//    
//        for(int i = 0; i < 8; i++)
//        {
//            if (laatsteWaarde != IRDigitaleWaarden[i])
//            {
//                aantalWaardeWisselingen++;
//                laatsteWaarde = IRDigitaleWaarden[i];
//            } 
//            if (IRDigitaleWaarden[i] == 1) teller++;
//            else {
//                if (teller > diksteLijn)
//                {
//                    diksteLijn = teller;
//                    teller = 0;
//                } 
//            }
//        }
//        
////        LCD_Position(0u,10u);
////        LCD_PrintInt16(aantalWaardeWisselingen);  
////         LCD_Position(1u,10u);
////        LCD_PrintInt16(diksteLijn);  
//        if (aantalWaardeWisselingen <= 3)
//        {
//            return Data;
//        }
//        else
//        {
//            uint8 compareValue = 1;
//            
//            for (int i = 0; i < diksteLijn; i++)
//            {
//                compareValue = compareValue | exponent(2,i);
//            }
//            for (uint8 i = 0; i < (8 - diksteLijn); i++)
//            {
//                if((compareValue & DataOrgineel) == compareValue) return compareValue;
//                compareValue = (compareValue << 1);
//            }
//        }
//    return 0;
//}
/* [] END OF FILE */
