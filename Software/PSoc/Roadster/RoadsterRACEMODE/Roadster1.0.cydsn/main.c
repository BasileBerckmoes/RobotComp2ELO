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
#include <string.h>
//#include <stdlib.h> //atoi
#include <stdio.h> 
#include <myUART.h>



//CY_ISR(TestIRFilter)
//{
//    LCD_ClearDisplay();
//    uint8 testGetal = 0b01001100;
//    AnalyseerData(testGetal);
//    
//    //printBINopLCD(TestGetal, 1);
//    
//}

CY_ISR(AndereDraaiRichting)
{
    richting = ~richting;
    if (richting == 0) LED1_Write(1);
    else if (richting == 255) LED4_Write(1);
}


//Start alle firmwire blokken
void initFirmwire()
{
	ADC_IR_Start();
	ADC_IR_StartConvert();
    
	LCD_Start(); 
	
	MotorControl_Start();
	
	TimerUS_Start();

    
    pwmMotorLinks = 0; 
    pwmMotorRechts = 0; 
} 


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    //drempelwaarde van de IR sensoren
    IRDrempel = 100;

	initFirmwire();
	richting = 0;
    LED1_Write(1);
	//Interrupts
	readIRSensors_StartEx(IRSensoren);
    
    //pasRijRichtingAan_StartEx(AndereDraaiRichting);
    
    
    //schakel motoren uit 
	MotorControl_WriteCompare1(0);
	MotorControl_WriteCompare2(0);
	ENA_Write(0);
	ENB_Write(0);
	
   
	while(SW1_Read() == 1) 
	{
      
	} 
    
	MotorControl_WriteCompare1(pwmMotorLinks);
	MotorControl_WriteCompare2(pwmMotorRechts);
    //start de 5 LED Procedure
	telProcedure();
    ENA_Write(1);
	ENB_Write(1);
    
    //Clear lcd zodat nieuwe waarden er op passen 
    
    //Loop
	for(;;)
	{ 
		//US deel
		//===================================================================
		//Teller die door de mux loopt
		//selectUS = telTot(selectUS, 0, 2); //PAS DIT AAN INDIEN NIET ALE US SENSOREN ZIJN AANGESLOTEN!!!!!
		//selectUS_Write(selectUS);
		
		//vraag afstand aan 1 van de 3 us sensoren
	    // uint16 counterValue = readUSValue();
		//schuif uitkomst timer in juiste array
		//if (selectUS == 0) schuifRegister(avgUS1, counterValue);
		//else if (selectUS == 1) schuifRegister(avgUS2, counterValue);
		//else if (selectUS == 2) schuifRegister(avgUS3, counterValue);
		
		//berekenen van de mediaan
        
        
        //Motoren met joystick
        //LCD_Position(0u,0u);
        //LCD_PrintInt16(pwmMotorLinks);
        //LCD_Position(1u,0u);
        //LCD_PrintInt16(pwmMotorRechts);
        
	    //CyDelay(10);
		//motordeel
		//===================================================================
        
        AnalyseerData(IRWaarden);
      
        printBINopLCD(IRWaarden,0);
        
        LCD_Position(1u,0u);
        LCD_PrintInt16(pwmMotorLinks);  
        LCD_Position(1u,10u);
        LCD_PrintInt16(pwmMotorRechts);  
        //Pas snelheid motoren aan
		MotorControl_WriteCompare1(pwmMotorLinks);
        MotorControl_WriteCompare2(pwmMotorRechts);
	}
}


//methode die van min tot max telt en de huidige tel waarde terug geeft
uint8 telTot(uint8 getal, uint8 min, uint8 max)
{
   if (getal >= min && getal <= max - 1)
		{
	        getal++;
		}   
        else getal = min; 
   return getal;
}

//methode die een binair getal op de LCD print
void printBINopLCD(uint8 value, int row)
{
	for(int i = 0; i < 8; i++)
	{
		LCD_Position(row,i);
		uint8 tmpWaarde =  exponent(2,i);
		if ((value & tmpWaarde) == tmpWaarde)
		{
			LCD_PrintDecUint16(1);
		}
			else 
		{
			LCD_PrintDecUint16(0);
		}  
	 }  
}

//methode met delays om af te tellen
void telProcedure(void)
{
    //Teller is totaal 4000ms maar in praktijk +/- 5000ms
    //CyDelay(1000);
	LED1_Write(1);
	CyDelay(1000);
	LED2_Write(1);
	CyDelay(1000);
	LED3_Write(1);
	CyDelay(1000);
	LED4_Write(1);
	CyDelay(1000);
	LED5_Write(1);
	
}


//methode die een macht berekend
int exponent(int grondgetal, int exponent)
{
	uint8 tmpWaarde = 1;
	for (int i = 0; i < exponent ; i ++)
	{
		tmpWaarde = tmpWaarde * grondgetal;
	}
	return tmpWaarde;
}




