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
#include "cytypes.h"

/////////////////////////////////////////////////////
//Firmwire  
void initFirmwire(void);

/////////////////////////////////////////////////////
//Bluetooth communicatie  
//char hexaDecBuffer[2];
char strMsg1[64];

CY_ISR_PROTO(sendBleData);  

void ProcessCommandMsg(void);
uint8 HexToDec(char hexVal[]);
//void DecToHex(uint8 value ,char buffer[]);
uint8 getCMDValue(char delimiter, char str[], char HexBuffer[]);

/////////////////////////////////////////////////////
//Motor  
uint8 pwmMotorLinks;
uint8 pwmMotorRechts;

uint8 ValueX;
uint8 ValueY;

void BepaalMotorWaarden(void);

/////////////////////////////////////////////////////
//LCD
void printBINopLCD(uint8 value, int row);
void printTextopLCD(int testValue1, int testValue2);


/////////////////////////////////////////////////////
//Varia
int exponent(int grondgetal, int exponent);
void telProcedure(void);
void berekenMediaan(uint16 array[]);
uint8 telTot(uint8 getal, uint8 min, uint8 max);





/* [] END OF FILE */
