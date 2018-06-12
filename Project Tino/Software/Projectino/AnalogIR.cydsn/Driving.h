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
#include <project.h>

#define ir_compare  0x60    //sensitivity line detection
//0x10 plakband+stift

//Constants for motor speed
#define Motor_Max   31
#define Motor_Main  31
#define Motor_Turn  31
#define Motor_Drive 31
#define Motor_Direction_High    {31,    23, 18}    
#define Motor_Direction_Low     {0,     9,  14}    
#define Motor_Difference        {31,    16, 4}    

//Needed for logic
#define Forward     0b01
#define Backward    0b10
#define Left        1
#define Right       0

void Drive(uint8_t ir[8]);
void Drive2(uint8_t ir[8]);
void DriveBetter(uint8_t ir[8]);
void DriveBetterSwing(uint8_t ir[8]);

//function used by drive methods
void Straight();
void HardTurn(_Bool left_right);
void Turn(_Bool left_right, uint8_t irLocation);
void Turn_Difference(_Bool left_right, uint8_t irLocation);
void Backwards();

/* [] END OF FILE */
