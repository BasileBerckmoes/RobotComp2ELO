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


CY_ISR_PROTO(sendBleData);  


/////////////////////////////////////////////////////
//Motor  
uint8 pwmMotorLinks;
uint8 pwmMotorRechts;
uint8 richting; // 0 = met de klok mee, 255 = tegen de klok in

/////////////////////////////////////////////////////
//LCD
void printBINopLCD(uint8 value, int row);
void printTextopLCD(int testValue1, int testValue2);

/////////////////////////////////////////////////////
//IR
uint8 IRWaarden;
uint8 IRDrempel;

CY_ISR_PROTO(IRSensoren); 
CY_ISR_PROTO(AndereDraaiRichting);

uint8 TestGetal;
/////////////////////////////////////////////////////
//US
uint16 mediaan;
uint8 selectUS;

uint16 avgUS1[5];
uint16 avgUS2[5];
uint16 avgUS3[5];

uint16 readUSValue(void);
void schuifRegister(uint16 array[], uint16 newValue);

/////////////////////////////////////////////////////
//Race Logica
void stuurMotorenBij(void);
void PlaatsIRWaardenInArray(uint8 value);
void AnalyseerData(uint8 data);
uint8 CheckVoor2eLijn(void);

/////////////////////////////////////////////////////
//Varia
int exponent(int grondgetal, int exponent);
uint8 telTot(uint8 getal, uint8 min, uint8 max);
void telProcedure(void);
void looplicht(void);
void berekenMediaan(uint16 array[]);
uint8 boolSelect;




/* [] END OF FILE */
