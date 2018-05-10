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

uint8 AVGLinks[5] = {255,255,255,255,255};
uint8 AVGRechts[5] = {255,255,255,255,255};

uint8 tmpLinks;
uint8 tmpRechts;

CY_ISR(AndereDraaiRichting)
{
    richting = ~richting;
    if (richting == 0)
    {
        LED2_Write(1);
        LED4_Write(0);
    }
    
    else if (richting == 255)
    {
       LED4_Write(1);
       LED2_Write(0);
       
    }
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
    //LED2_Write(1);
	//Interrupts
	readIRSensors_StartEx(IRSensoren);
    
    //DraaiRichtingISR_StartEx(AndereDraaiRichting);
    
    
    //schakel motoren uit 
	MotorControl_WriteCompare1(0);
	MotorControl_WriteCompare2(0);
	ENA_Write(0);
	ENB_Write(0);
	
   
	while(SW1_Read() == 1 && SW2_Read() == 1) 
	{
      
	} 
    if (SW2_Read() == 0)
    {
        telProcedure();
    }
    
	MotorControl_WriteCompare1(pwmMotorLinks);
	MotorControl_WriteCompare2(pwmMotorRechts);
    //start de 5 LED Procedure
	
    ENA_Write(1);
	ENB_Write(1);
    
    //Clear lcd zodat nieuwe waarden er op passen 
    
    //Loop
	for(;;)
	{
        
        AnalyseerData(IRWaarden);
      
        printBINopLCD(IRWaarden,0);
        
        LCD_Position(1u,0u);
        LCD_PrintInt16(pwmMotorLinks);  
        LCD_Position(1u,10u);
        LCD_PrintInt16(pwmMotorRechts);  

        uint16 links = tmpLinks + pwmMotorLinks;
        uint16 rechts = tmpRechts + pwmMotorRechts;
		MotorControl_WriteCompare1(links / 2);
        MotorControl_WriteCompare2(rechts / 2);
        
        tmpLinks = pwmMotorLinks;
        tmpRechts = pwmMotorRechts;
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
    
    LED4_Write(0);
    LED3_Write(0);
    LED2_Write(0);
    LED1_Write(0);
	
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




