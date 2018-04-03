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
    
    //Status led
	LED1_Write(~LED1_Read());
	
    //Zet IRWaarden om naar hexadecimaal stelsel
	DecToHex(IRWaarden);
    //Maak een string met hexaDecBuffer als parameter en sla die op in strBuffer
	sprintf(strBuffer, "I/%s/\r", hexaDecBuffer); 
    //Verstuur de string naar de bluetooth module
	BleUart_PutString(strBuffer);
	
    //Zet een testgetal om naar hex stelsel
	DecToHex(ADC_IR_GetResult16(0));
	sprintf(strBuffer, "T/%s/\r",hexaDecBuffer); 
	BleUart_PutString(strBuffer);
}

void ProcessCommandMsg(void)
{
    //Voorbeeld commando R/FF/
    //RB.cmd is de eerste waarde dus in dit voorbeeld R
    //RB.valstr = alles wat erna komt dus /FF/
    
	if (RB.cmd == 'R')
	{  
		pwmMotor1 = getCMDValue('/', RB.valstr);
	} 
	else if (RB.cmd == 'L')
	{
		pwmMotor2 = getCMDValue('/', RB.valstr);
	}
	else if (RB.cmd == 'M')
	{
		uint8 enable = getCMDValue('/', RB.valstr);
		ENA_Write(enable);
		ENB_Write(enable);
	}
}

//methode die een waarde uit een commando haalt
//delimiter zijn de karakters waar de waarde tussen staat 
//bvb delimiter is '/' en commando is R/FF/ dan is de return FF
uint8 getCMDValue(char delimiter, char str[])
{
	for (uint i = 0; i < strlen(str); i++)
		{
			if (str[i] == delimiter && str[i+3] == delimiter)
			{
				hexaDecBuffer[0] = str[i+1];
				hexaDecBuffer[1] = str[i+2];
			}    
		}
		
	return HexToDec(hexaDecBuffer);
}

//zet een getal om van dec naar hex
void DecToHex(uint8 value)
{
	uint8 i = 1;
    
    //Beveiliging als value 0 is;
	if (value == 0)
	{
		hexaDecBuffer[0] = '0';
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
