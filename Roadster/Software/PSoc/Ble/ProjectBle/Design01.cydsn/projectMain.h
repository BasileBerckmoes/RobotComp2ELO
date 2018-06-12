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

//buffer to hold application settings
   
/////////////////////////////////////////////////////
//Firmwire  
void initFirmwire(void);

/////////////////////////////////////////////////////
//LCD
void printBINopLCD(uint8 value, int row);
void printTextopLCD(int testValue);

/////////////////////////////////////////////////////
//US
uint16 readUSValue(void);

//Joystick
uint8 valueX;
uint8 valueY;

//PWM
uint8 pwml;
uint8 pwmr;

//Bluetooth communicatie
CY_ISR_PROTO(sendBleData);  
//char hexaDecBuffer[2];
void ProcessCommandMsg(void);
char strMsg1[64];
uint8 TestGetal;

//IR
uint8 IRWaarden;

/////////////////////////////////////////////////////
//Varia
void schuifRegister(uint16 array[], uint16 newValue);
int exponent(int grondgetal, int exponent);
uint8 telTot(uint8 getal, uint8 min, uint8 max);
void telProcedure(void);
void berekenMediaan(uint16 array[]);
uint8 HexToDec(char hexVal[]);
uint8 getCMDValue(char delimiter, char str[], char HexBuffer[]);
void DecToHex(uint8 value, char buffer[]);

/* [] END OF FILE */
