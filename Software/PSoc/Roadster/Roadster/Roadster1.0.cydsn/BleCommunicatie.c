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
	LED1_Write(~LED1_Read());
    
	sprintf(strBuffer, "T/%X/\r", 77); 
	BleUart_PutString(strBuffer);
}

void ProcessCommandMsg(void)
{
    LCD_ClearDisplay();
    char hexBuffer[2];
    //Voorbeeld commando R/FF/
    //RB.cmd is de eerste waarde dus in dit voorbeeld R
    //RB.valstr = alles wat erna komt dus /FF/

	if (RB.cmd == 'X')
	{  
		ValueX = getCMDValue('/', RB.valstr, hexBuffer);
	} 
	else if (RB.cmd == 'Y')
	{
		ValueY = getCMDValue('/', RB.valstr, hexBuffer);
	}
	else if (RB.cmd == 'M')
	{
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
    if (strlen(str) == 4)
    {
        for (uint i = 0; i < strlen(str); i++)
		{
			if (str[i] == delimiter && str[i+3] == delimiter)
			{
				hexBuffer[0] = str[i+1];
				hexBuffer[1] = str[i+2];
                   
			}    
		}
    } 
    else if (strlen(str) == 3)
    {
        for (uint i = 0; i < strlen(str); i++)
		{
			if (str[i] == delimiter && str[i+2] == delimiter)
			{
				hexBuffer[0] = str[0];
				hexBuffer[1] = str[i+1];
                   
			}    
		}
    }
	return HexToDec(hexBuffer);
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
