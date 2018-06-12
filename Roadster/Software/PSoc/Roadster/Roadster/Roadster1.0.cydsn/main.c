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

uint8 richting = 0;

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
	//sendBleDataTimer_Start();
    
    pwmMotorLinks = 255; 
    pwmMotorRechts = 255; 
} 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

	initFirmwire();
	
	//Interrupts
	//EnMotorISR_StartEx(SwitchMotorEN);
	BleRxISR_StartEx(MyRxInt);
    
    //schakel motoren uit 
	MotorControl_WriteCompare1(0);
	MotorControl_WriteCompare2(0);

    ENA_Write(0);
	ENB_Write(0);
    
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
        BepaalMotorWaarden();
        
        //Pas snelheid motoren aan
		MotorControl_WriteCompare1(pwmMotorLinks);
        MotorControl_WriteCompare2(pwmMotorRechts);
	}
}

void printTextopLCD(int testValue1, int testValue2)
{
	LCD_ClearDisplay(); //Clear display
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

void BepaalMotorWaarden()
{
    uint16 tmpValueY;
    if (ValueY >= 122 && ValueY <= 126) tmpValueY = 0;
    else if (ValueY < 122)
    {
        RijRichting_Write(0);
        tmpValueY = 255 - (ValueY * 2);
        //if (tmpValueY > 255) tmpValueY = 255;
    }
    else if (ValueY > 126)
     {
        RijRichting_Write(1);
        tmpValueY = ValueY / 2;
        //if (tmpValueY > 255) tmpValueY = 255;
    }
    
    
    LCD_Position(0u,0);
    LCD_PrintDecUint16(tmpValueY);
    
    
    LCD_Position(1u,0);
    LCD_PrintDecUint16(ValueY);
    
    LCD_Position(1u,5);
    LCD_PrintDecUint16(ValueX);
    
    pwmMotorLinks = tmpValueY;
    pwmMotorRechts = tmpValueY;
    
    if (ValueX >= 122 && ValueX <= 128) return;
    else if (ValueX < 122)
    {
        pwmMotorRechts = pwmMotorRechts - (100);
    } 
    else if (ValueX > 128)
    {
        pwmMotorLinks = pwmMotorLinks - (100);
    }
}


