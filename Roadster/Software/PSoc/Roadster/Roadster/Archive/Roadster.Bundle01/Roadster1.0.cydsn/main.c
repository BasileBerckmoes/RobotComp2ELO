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



CY_ISR(SwitchMotorEN)
{
}


//Start alle firmwire blokken
void initFirmwire()
{   
	LCD_Start(); 
	
	MotorControl_Start();

	BleVDAC_Start();
	BleBuffer_Start();
	BleUart_Start();
	sendBleDataTimer_Start();
    
    pwmMotorLinks = 0; 
    pwmMotorRechts = 0; 
} 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

	initFirmwire();
	
	//Interrupts
	EnMotorISR_StartEx(SwitchMotorEN);
	BleRxISR_StartEx(MyRxInt);
	
    //Print start text op lcd
	//LCD_Position(0u, 0u);
	//LCD_PrintString("Druk om te starten");
	
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
	//LCD_ClearDisplay();
    
    //Loop
	for(;;)
	{ 
        //Kijk als er een string klaar is om te verwerken
		if (IsCharReady())
		{
            //Zet de string in een buffer variable
			if(GetRxStr())
			{
                
                //Verwerk de string
				ProcessCommandMsg();
			}
		}
        
        //Motoren met joystick
        LCD_Position(0u,0u);
        LCD_PrintInt16(pwmMotorLinks);
        LCD_Position(1u,0u);
        LCD_PrintInt16(pwmMotorRechts);
        
	    //CyDelay(10);
		//motordeel
		//===================================================================
        
        AnalyseerData(IRWaarden);
      
        //Pas snelheid motoren aan
		MotorControl_WriteCompare1(pwmMotorLinks);
        MotorControl_WriteCompare2(pwmMotorRechts);
	}
}

void printTextopLCD(int testValue1, int testValue2)
{
	LCD_CLEAR_DISPLAY; //Clear display
	LCD_Position(0u,0u); //Put cursor top left
	LCD_PrintString("sensor: "); //print something
	LCD_Position(0u,9u); //Replace cursor
	LCD_PrintDecUint16(testValue1); //Print the value of first ultrasoonsensor
	LCD_Position(1u,9u); //Replace cursor
	LCD_PrintDecUint16(testValue2);
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
	LED1_Write(1);
	CyDelay(1000);
	LED2_Write(1);
	CyDelay(1000);
	LED3_Write(1);
	CyDelay(1000);
	LED4_Write(1);
	CyDelay(1000);
	LED5_Write(1);
	CyDelay(1000);
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



