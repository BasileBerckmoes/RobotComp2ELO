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
 
//Timer gestuurde interupt zodat data om de zoveel tijd verstuurd wordt via bluetooth
CY_ISR(sendBleData)
{
    //Buffer
	char strBuffer[10];
    
    char hexBuffer[2];
    //Status led
	LED1_Write(~LED1_Read());
	
    //Zet IRWaarden om naar hexadecimaal stelsel
	DecToHex(IRWaarden, hexBuffer);
     //LCD_Position(0u, 10u);
    //char testBuffer[] = {str[i+1], 'b',str[i+2] };
                    
    //Maak een string met hexaDecBuffer als parameter en sla die op in strBuffer
	sprintf(strBuffer, "I/%s/\r", hexBuffer); 
    
    //LCD_PrintString(strBuffer);
    //Verstuur de string naar de bluetooth module
	BleUart_PutString(strBuffer);
	
    //Zet een testgetal om naar hex stelsel
    
	DecToHex(ADC_IR_GetResult16(0), hexBuffer);
	sprintf(strBuffer, "T/%s/\r", hexBuffer); 
	BleUart_PutString(strBuffer);
}

void ProcessCommandMsg(void)
{
    char hexBuffer[2];
    //Voorbeeld commando R/FF/
    //RB.cmd is de eerste waarde dus in dit voorbeeld R
    //RB.valstr = alles wat erna komt dus /FF/
    
	if (RB.cmd == 'R')
	{  
         LED5_Write(~LED5_Read());
		pwmMotorLinks = getCMDValue('/', RB.valstr, hexBuffer);
	} 
	else if (RB.cmd == 'L')
	{
		pwmMotorRechts = getCMDValue('/', RB.valstr, hexBuffer);
	}
	else if (RB.cmd == 'M')
	{
        LCD_Position(0u,10u);
        LCD_PrintString("gud");
		uint8 enable = getCMDValue('/', RB.valstr, hexBuffer);
		ENA_Write(enable);
		ENB_Write(enable);
	}
}

//methode die een waarde uit een commando haalt
//delimiter zijn de karakters waar de waarde tussen staat 
//bvb delimiter is '/' en commando is R/FF/ dan is de return FF
uint8 getCMDValue(char delimiter, char str[], char hexBuffer[])
{
	for (uint i = 0; i < strlen(str); i++)
		{
			if (str[i] == delimiter && str[i+3] == delimiter)
			{
				hexBuffer[0] = str[i+1];
				hexBuffer[1] = str[i+2];
                   
			}    
		}
		
	return HexToDec(hexBuffer);
}

//zet een getal om van dec naar hex
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

//Zet een getal om van HEX naar dec
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
/* [] END OF FILE */
