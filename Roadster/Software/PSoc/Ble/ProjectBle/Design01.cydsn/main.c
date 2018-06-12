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

uint8 motorStatus = 0;
//uint8 IRWaarden;
//uint8 TestGetal = 0;

//char strMsg1[64];
//char hexValueBuffer[2];

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
    valueX=(JoyStickADC_GetResult16(0));
    valueY= (JoyStickADC_GetResult16(1));
}

CY_ISR(motorControl)
{
   
    LED_Write(~LED_Read());
//     uint8 status = 0;
//    if (LED_Read() != 0)
//    {
//        status = 1;
//    } 
    char strBuffer[10];
    ////char motorHexBuffer[2];
    ////DecToHex(LED_Read(), motorHexBuffer);
    //puttyUart1_PutString(hexaDecBuffer);
    sprintf(strBuffer, "M/%X/\r\n", LED_Read()); // strBuffer -> plaats waar string opgeslagen wordt
                                                  // %s -> string die een hexadeximale bevat namelijk hexaDecBuffer bv 65 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
}



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    rxPuttyISR_StartEx(dataBinnenPutty);
    
    
    rxBleISR_StartEx(MyRxInt);
    
    LCDD_Start();
    
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
        LCDD_ClearDisplay();
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
        //---LCDD_Position(0u,11u);
//        
//        DecToHex(valueX);
//        LCDD_Position(1u,0u);
//        LCDD_PrintString(hexaDecBuffer);
//        
//        DecToHex(valueY);
//        LCDD_Position(1u,7u);
//        LCDD_PrintString(hexaDecBuffer);
  
        //---LCDD_PrintDecUint16(IRWaarden);
        
        // LCDD_Position(1u,0u);
        //---printBINopLCD(IRWaarden, 1);
        CyDelay(200);
        
        
    }
}

uint8 getCMDValue(char delimiter, char str[], char HexBuffer[])
{
    for (uint8 i = 0; i < strlen(str); i++)
        {
            LCDD_Position(1u,11u);
            char buffer[] = {str[i+3]};
            LCDD_PrintString(buffer);
            if (str[i] == delimiter /*&& str[i+3] == delimiter*/)
            {
                
                HexBuffer[0] = str[i+1];
                HexBuffer[1] = str[i+2];
                //sprintf(strMsg1,"IRWaarde=%u ", IRWaarden); 
                //puttyUart1_PutString(strMsg1);
                break;
            }    
        }
        
    return HexToDec(HexBuffer);
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

void DecToHex(uint8 value, char buffer[])
{
    char strBuffer[20];
    uint8 i = 2;
    //sprintf(strBuffer, "input is: %u/\r\n", value);
        //puttyUart1_PutString(strBuffer);
    if (value == 0)
    {
        buffer[0] =  '0';
        buffer[1] ='0';
        
    } else {
    
    for (int i = 1; i >=0 ; i--)
    {
        uint8 temp = value % 16;
        if (temp < 10)
        {
        buffer[i] = temp + 48;
        //sprintf(strBuffer, "waarde is: %u/\r\n", buffer[i]);
        //puttyUart1_PutString(strBuffer);
        } 
        else 
        {
            buffer[i] = temp + 55;
        }
        value = value / 16;
    }
   }
}

/* [] END OF FILE */