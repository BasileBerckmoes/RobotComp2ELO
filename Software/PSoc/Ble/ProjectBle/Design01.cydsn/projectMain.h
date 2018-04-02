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
   
    
void ProcessCommandMsg(void);
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

/////////////////////////////////////////////////////
//Varia
void schuifRegister(uint16 array[], uint16 newValue);
int exponent(int grondgetal, int exponent);
uint8 telTot(uint8 getal, uint8 min, uint8 max);
void telProcedure(void);
void berekenMediaan(uint16 array[]);
uint8 HexToDec(char hexVal[]);
uint8 getCMDValue(char delimiter, char str[]);
void DecToHex(uint8 value);

/* [] END OF FILE */