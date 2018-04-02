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

//INFRAROOD GLOBALS
uint8 IRWaarden;
uint8 IRDrempel = 100;

//US GLOBALS
uint8 selectUS = 0;
uint16 mediaan;

uint16 avgUS1[5];
uint16 avgUS2[5];
uint16 avgUS3[5];

//MOTOR GLOBALS
uint8 pwmMotor1 = 0;
uint8 pwmMotor2 = 0;


char hexaDecBuffer[2];
char strMsg1[64];

//Interupt "end of conversion" van SAR_ADC 
CY_ISR(IRSensoren)
{
    uint8 tmpWaarden = IRWaarden;
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
   //ENA_Write(~ENA_Read());
    char strBuffer[10];
   //ENB_Write(ENA_Read());
     DecToHex(IRWaarden);
    sprintf(strBuffer, "I/%s/\r", hexaDecBuffer); 
    BleUart_PutString(strBuffer);
    
    DecToHex(ADC_IR_GetResult16(0));
    sprintf(strBuffer,"T/%s/\r",hexaDecBuffer); 
    BleUart_PutString(strBuffer);
    
}

CY_ISR(sendBleData)
{
    char strBuffer[10];
    LED1_Write(~LED1_Read());
    
    DecToHex(IRWaarden);
    sprintf(strBuffer, "I/%s/\r", hexaDecBuffer); 
    BleUart_PutString(strBuffer);
    
    DecToHex(ADC_IR_GetResult16(0));
    sprintf(strBuffer, "T/%s/\r",hexaDecBuffer); 
    BleUart_PutString(strBuffer);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    initFirmwire();
    
    //Interrupts
    readIRSensors_StartEx(IRSensoren);
    EnMotorISR_StartEx(SwitchMotorEN);
    BleRxISR_StartEx(MyRxInt);
    SendBleDataISR_StartEx(sendBleData);
    
    LCD_Position(0u, 0u);
    LCD_PrintString("Druk om te starten");
    
    MotorControl_WriteCompare1(pwmMotor1);
    MotorControl_WriteCompare2(pwmMotor2);
    ENA_Write(0);
    ENB_Write(0);
    
    

    while(SW1_Read() == 1) //Wait until press on SW1
    {
    }
    
    //telProcedure();
    LCD_ClearDisplay();
    for(;;)
    { 
        if (IsCharReady())
        {
            if(GetRxStr())
            {
                ProcessCommandMsg();
            }
        }
        //US deel
        /////////////////////////////////////////////////////
        //Teller die door de mux loopt
        selectUS = telTot(selectUS, 0, 2); //PAS DIT AAN INDIEN NIET ALE US SENSOREN ZIJN AANGESLOTEN!!!!!
        //selectUS_Write(selectUS);
        
        //vraag afstand aan 1 van de 3 us sensoren
       // uint16 counterValue = readUSValue();
        
        //schuif uitkomst timer in juiste array
        //if (selectUS == 0) schuifRegister(avgUS1, counterValue);
        //else if (selectUS == 1) schuifRegister(avgUS2, counterValue);
        //else if (selectUS == 2) schuifRegister(avgUS3, counterValue);
        
        //berekenen van de mediaan
        
         
        //LCD deel   
        /////////////////////////////////////////////////////
//        BleUart_PutString("\r\n");
//        BleUart_PutChar('S');
//        BleUart_WriteTxData(ADC_IR_GetResult16(0));
//        BleUart_PutString("\r\n");
//        BleUart_PutChar('I');
//        BleUart_WriteTxData(IRWaarden);
//        BleUart_PutString("\r\n");
//        LED1_Write(~LED1_Read());
        
        
       // LCD_ClearDisplay();
       // print text en een test variable op de lcd
        printTextopLCD(pwmMotor1, pwmMotor2);
        //print de binaire waarde van de infrarood sensoren op de lcd
        printBINopLCD(IRWaarden, 1);
        
        //motordeel
        /////////////////////////////////////////////////////
        MotorControl_WriteCompare1(pwmMotor1);
        MotorControl_WriteCompare2(pwmMotor2);
    }
}

void initFirmwire()
{
    ADC_IR_Start();
    ADC_IR_StartConvert();
    
    LCD_Start(); 
    
    MotorControl_Start();
    
    TimerUS_Start();
   
    BleVDAC_Start();
    BleBuffer_Start();
    BleUart_Start();
    sendBleDataTimer_Start();
   
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
    //uint16 tmp = 0;
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

void ProcessCommandMsg(void){
//    sprintf(strMsg1,"Commando bevat %d waarden\r", strlen(RB.valstr));
//    puttyUart1_PutString(strMsg1);
    //1ste waarde zijn de IR sensoren 2e waarde is een testgetal
    if (RB.cmd == 'R')
    {  
        pwmMotor1 = getCMDValue('/', RB.valstr);
        //sprintf(strMsg1,"IRWaarde=%u\n", IRWaarden); 
        //puttyUart1_PutString(strMsg1);

    } 
    else if (RB.cmd == 'L')
    {
        pwmMotor2 = getCMDValue('/', RB.valstr);
        //sprintf(strMsg1,"TestGetal=%u\n", TestGetal); 
        //puttyUart1_PutString(strMsg1);
    }
    else if (RB.cmd == 'M')
    {
        
        uint8 enable = getCMDValue('/', RB.valstr);
        ENA_Write(enable);
        ENB_Write(enable);
        //sprintf(strMsg1,"TestGetal=%u\n", TestGetal); 
        //puttyUart1_PutString(strMsg1);
    }
        
}
uint8 getCMDValue(char delimiter, char str[])
{
    for (uint i = 0; i < strlen(str); i++)
        {
            if (str[i] == delimiter && str[i+3] == delimiter)
            {
                hexaDecBuffer[0] = str[i+1];
                hexaDecBuffer[1] = str[i+2];
                //sprintf(strMsg1,"IRWaarde=%u ", IRWaarden); 
                //puttyUart1_PutString(strMsg1);
            }    
        }
        
    return HexToDec(hexaDecBuffer);
}
void DecToHex(uint8 value)
{
    uint8 i = 1;
    if (value == 0)
    {
        hexaDecBuffer[0] =  '0';
        hexaDecBuffer[1] ='0';
    }
    while (value != 0)
    {
        uint8 temp = value % 16;
        if (temp < 10)
        {
         hexaDecBuffer[i] = temp + 48;
        i--;
        } 
        else 
        {
            hexaDecBuffer[i] = temp + 55;
            i--;
        }
        value = value / 16;
    }
}

uint8 HexToDec(char hexVal[])
{
    uint8 len = strlen(hexVal);
    uint base = 1;
    uint dec_val =0;
    for (int i=len-1; i>=0; i--)
    {
        if (hexVal[i] >= '0' && hexVal[i] <='9')
        {
         dec_val += (hexVal[i] - 48) * base;
         base = base*16;   
        } else if (hexVal[i]>='A' && hexVal[i]<='F')
        {
            dec_val += (hexVal[i] - 55)*base;
            base = base*16;
        }
    }
    return dec_val;
}

