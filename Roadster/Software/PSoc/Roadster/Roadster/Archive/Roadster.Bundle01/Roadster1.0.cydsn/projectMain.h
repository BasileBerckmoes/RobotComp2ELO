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
void DecToHex(uint8 value ,char buffer[]);
uint8 getCMDValue(char delimiter, char str[], char HexBuffer[]);

/////////////////////////////////////////////////////
//Motor  
uint8 pwmMotorLinks;
uint8 pwmMotorRechts;

/////////////////////////////////////////////////////
//LCD
void printBINopLCD(uint8 value, int row);
void printTextopLCD(int testValue1, int testValue2);

/////////////////////////////////////////////////////
//IR
uint8 IRWaarden;
uint8 IRDrempel;

CY_ISR_PROTO(IRSensoren); 


void schuifRegister(uint16 array[], uint16 newValue);


/////////////////////////////////////////////////////
//Varia
int exponent(int grondgetal, int exponent);
void telProcedure(void);
void berekenMediaan(uint16 array[]);





/* [] END OF FILE */
