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
#include "project.h"
#include "projectMain.h"

//INFRAROOD GLOBALS
uint8 IRWaarden;
uint8 IRDrempel = 190;

//US GLOBALS
uint8 selectUS = 0;
uint16 mediaan;

uint16 avgUS1[5];
uint16 avgUS2[5];
uint16 avgUS3[5];

//MOTOR GLOBALS
uint8 pwmMotor1 = 60;
uint8 pwmMotor2 = 50;

//Interupt "end of conversion" van SAR_ADC 
CY_ISR(IRSensoren)
{
    IRWaarden = 0;
   for(int i = 0; i < 8; i++)
   {
    if (ADC_IR_GetResult16(i) > IRDrempel)
    {
       uint8 tmpWaarde = exponent(2,i); 
       IRWaarden = IRWaarden | tmpWaarde;
    }
   }
}
  
CY_ISR(SwitchMotorEN)
{
   ENA_Write(~ENA_Read());
   ENB_Write(ENA_Read());
   CyDelay(200);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    readIRSensors_StartEx(IRSensoren);
    EnMotorISR_StartEx(SwitchMotorEN);
    
    LCD_Start(); 
    LCD_Position(0u, 0u);
    LCD_PrintString("Druk om te starten");
    
    ADC_IR_Start();
    ADC_IR_StartConvert();
    
    
    MotorControl_Start();
    MotorControl_WriteCompare1(pwmMotor1);
    MotorControl_WriteCompare2(pwmMotor2);
    ENA_Write(0);
    ENB_Write(ENA_Read());

    TimerUS_Start();
   
    
    while(SW1_Read() == 1) //Wait until press on SW1
    {
    }
    
    //telProcedure();
    
    for(;;)
    { 
        //US deel
        /////////////////////////////////////////////////////
        //Teller die door de mux loopt
        selectUS = telTot(selectUS, 0, 2); //PAS DIT AAN INDIEN NIET ALE US SENSOREN ZIJN AANGESLOTEN!!!!!
        selectUS_Write(selectUS);
        
        //vraag afstand aan 1 van de 3 us sensoren
       // uint16 counterValue = readUSValue();
        
        //schuif uitkomst timer in juiste array
        //if (selectUS == 0) schuifRegister(avgUS1, counterValue);
        //else if (selectUS == 1) schuifRegister(avgUS2, counterValue);
        //else if (selectUS == 2) schuifRegister(avgUS3, counterValue);
        
        //berekenen van de mediaan
        
         
        //LCD deel   
        /////////////////////////////////////////////////////
        //print text en een test variable op de lcd
        printTextopLCD(avgUS1[4]);
        //print de binaire waarde van de infrarood sensoren op de lcd
        printBINopLCD(IRWaarden, 1);
        
        //motordeel
        /////////////////////////////////////////////////////
        MotorControl_WriteCompare1(pwmMotor1);
        MotorControl_WriteCompare2(pwmMotor2);
    }
}


uint16 readUSValue(void)
{
    while(statusEcho_Read() == 0)
        {
            TriggerReg_Write(1);
            CyDelayUs(10);
            TriggerReg_Write(0);
        }
    while(statusEcho_Read() == 1){}
    return TimerUS_ReadCounter();
}

void schuifRegister(uint16 array[], uint16 newValue)
{
    for(int i = 3; i >= 0; i--)
    {
        uint16 tmpvalue = avgUS1[i];
        array[i + 1] = tmpvalue;
    }
    array[0] = newValue;
}

void berekenMediaan(uint16 array[]) 
{ 
    uint16 tmp = 0;
    uint16 tmpArray[] = {UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX,UINT16_MAX};
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++) 
        {
            if (array[j] < tmpArray[i]) tmpArray[i] = array[j];
        }
    }
    mediaan = tmpArray[3];
}    
//methode die een text en een testgetal op een 
void printTextopLCD(int testValue)
{
    LCD_CLEAR_DISPLAY; //Clear display
    LCD_Position(0u,0u); //Put cursor top left
    LCD_PrintString("sensor: "); //print something
    LCD_Position(0u,9u); //Replace cursor
    LCD_PrintDecUint16(testValue); //Print the value of first ultrasoonsensor
}

//methode die van min tot max telt en de huidige tel waarde terug geeft
uint8 telTot(uint8 getal, uint8 min, uint8 max)
{
   if (getal >= min && getal <= max - 1)
        {
            getal++;
        }   else getal = min; 
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

