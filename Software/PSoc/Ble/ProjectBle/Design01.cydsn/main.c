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
#include <string.h>
//#include <stdlib.h> //atoi
#include <stdio.h> 
#include <myUART.h>

char lastChar;

uint8 valueX=0;
uint8 valueY=0;

uint8 motorStatus = 0;

uint8 IRWaarden = 0;
uint8 TestGetal = 0;

char strMsg1[64];
//char hexValueBuffer[2];
char hexaDecBuffer[2];

CY_ISR(dataBinnenPutty)
{
    char charBinnen = puttyUart1_GetChar();
    puttyUart1_PutChar(charBinnen);
    bleUart1_PutChar(charBinnen);
    
    if (charBinnen == '\r')
    {
        puttyUart1_PutChar('\n');
        bleUart1_PutChar('\n');
    }
}

CY_ISR(bleAntwoord)
{
    char charBinnen = bleUart1_GetChar();
    puttyUart1_PutChar(charBinnen); 
}

CY_ISR(getJoystickValues)
{
    valueX=JoyStickADC_GetResult16(0);
    valueY= JoyStickADC_GetResult16(1);
}

CY_ISR(motorControl)
{
    LED_Write(~LED_Read());
    char strBuffer[10];
    DecToHex(LED_Read());
    sprintf(strBuffer, "M/%s/\r", hexaDecBuffer); 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
}

CY_ISR(sendBleData)
{   
    uint8 pwml = 0;
    uint8 pwmr = 0;
    
    pwml = ((valueX)-127); 
    pwmr = pwml;
    
    
//    if (valueY < 124)
//    {
//        if (pwml > (~valueY))
//        {
//          pwml = pwml - (~valueY);
//        }else pwml = 0;
//    }
//    else if (valueY > 124)
//    {
//        if (pwmr > (valueY))
//        {
//         pwmr = pwmr - (valueY);
//        }else pwmr = 0;
//    }
    
    char strBuffer[10];
    DecToHex(pwml);
    sprintf(strBuffer, "PWML: /%u/\r", pwml); 
    //puttyUart1_PutString(strBuffer);
    sprintf(strBuffer, "L/%s/\r", hexaDecBuffer); 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
    
    DecToHex(pwmr);
    sprintf(strBuffer, "PWMR: /%u/\r", pwmr); 
    //puttyUart1_PutString(strBuffer);
    sprintf(strBuffer, "R/%s/\r",hexaDecBuffer); 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    rxPuttyISR_StartEx(dataBinnenPutty);
    
    
    rxBleISR_StartEx(MyRxInt);
    
    LCDD_Start();
    LCDD_Position(0u,0u);
    LCDD_PrintString("hello");
    
    VDAC_Start();
    Opamp_1_Start();
    puttyUart1_Start();
    bleUart1_Start();
    
    sendBleDataTimer_Start();
    sendBleDataISR_StartEx(sendBleData);
    
    JoyStickADC_Start();
    JoyStickADC_StartConvert();
    
    eocJoystickISR_StartEx(getJoystickValues);
    motorControlISR_StartEx(motorControl);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        
        if (IsCharReady())
        {
            
            
            if(GetRxStr())
            {
                
                ProcessCommandMsg();
            }
        }
        LCDD_Position(0u,0u);
        LCDD_PrintString("X:");
        LCDD_Position(0u,2u);
        LCDD_PrintDecUint16(valueX);
        LCDD_Position(0u,5u);
        LCDD_PrintString("Y:");
        LCDD_Position(0u,7u);
        LCDD_PrintDecUint16(valueY);
         LCDD_Position(0u,11u);
        LCDD_PrintDecUint16(TestGetal);
        
        LCDD_Position(1u,0u);
        printBINopLCD(IRWaarden, 1);
        //LCDD_PrintDecUint16();
//        CyDelay(200);
        LCDD_ClearDisplay();
        
    }
}
void ProcessCommandMsg(void){
//    sprintf(strMsg1,"Commando bevat %d waarden\r", strlen(RB.valstr));
//    puttyUart1_PutString(strMsg1);
    //1ste waarde zijn de IR sensoren 2e waarde is een testgetal
    if (RB.cmd == 'I')
    {  
        IRWaarden = getCMDValue('/', RB.valstr);
        sprintf(strMsg1,"IRWaarde=%u\r", IRWaarden); 
        puttyUart1_PutString(strMsg1);

    } 
    else if (RB.cmd == 'T')
    {
        TestGetal = getCMDValue('/', RB.valstr);
        sprintf(strMsg1,"TestGetal=%u\r", TestGetal); 
        puttyUart1_PutString(strMsg1);
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
void printBINopLCD(uint8 value, int row)
{
    for(int i = 0; i < 8; i++)
    {
        LCDD_Position(row,i);
        uint8 tmpWaarde =  exponent(2,i);
        if ((value & tmpWaarde) == tmpWaarde)
        {
            LCDD_PrintDecUint16(1);
        }
            else 
        {
            LCDD_PrintDecUint16(0);
        }  
     }  
}

int exponent(int grondgetal, int exponent)
{
    uint8 tmpWaarde = 1;
    for (int i = 0; i < exponent ; i ++)
    {
        tmpWaarde = tmpWaarde * grondgetal;
    }
    return tmpWaarde;
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

/* [] END OF FILE */
