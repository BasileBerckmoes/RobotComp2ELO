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
#include "Driving.h"

uint8_t motor_Direction_High[3] = Motor_Direction_High;    
uint8_t motor_Direction_Low[3] = Motor_Direction_Low;    
uint8_t motor_Difference[3] = Motor_Difference;    


int16 direction=0;

uint8_t path =0;
_Bool holdL;
_Bool holdR;


    uint8 ToLeft=0;
    uint8 ToRight=0;   
    void Drive(uint8_t ir[8])
{ 
     ToLeft=0;
     ToRight=0;   
    //path =0;
    for (uint8_t i = 1; i < 4; i++){
        if(ir[i]>ir_compare)    {ToLeft+=(16>>(i-1));      holdR=0; holdL =0;   /*path=path + (128>>i);*/} 
        if(ir[7-i]>ir_compare)  {ToRight+=(16>>(i-1));     holdL=0; holdR =0;   /*path=path + (1<<i);*/}
    }
    if(ir[0]>ir_compare)    {holdL =1;  /*path=path + (128);*/}   
    if(ir[7]>ir_compare)    {holdR =1;  /*path=path + (1);*/} 
    if(holdL==1)       ToLeft=Motor_Main;
    if(holdR==1)       ToRight=Motor_Main;
    
    direction = ToLeft;    
    direction -= ToRight;    
    
    if(direction>0)     {ToLeft = Motor_Main; ToRight = Motor_Main - direction;}
    if(direction==0)    {ToLeft = Motor_Main>>1; ToRight = Motor_Main>>2;}
    if(direction<0)     {ToLeft = Motor_Main+ direction; ToRight = Motor_Main;}
    
    PWM_1_WriteCompare1(ToLeft);
    PWM_1_WriteCompare2(ToRight);          
}
    void Drive2(uint8_t ir[8])
{
    if(ir[0]>ir_compare){holdL =1;}
    if(ir[7]>ir_compare){holdR =1;}
    if(holdL || holdR){ToLeft=255;ToRight=255;}
    if(holdL && holdR);
     ToLeft=0;
     ToRight=0;   
    path =0;
    for (uint8_t i = 1; i < 4; i++){
        if(ir[i]>ir_compare)    {    holdR =0;  holdL =0;  ToLeft =Motor_Drive>>(i-1);  } 
        if(ir[7-i]>ir_compare)  {    holdL =0;  holdR =0;  ToRight=Motor_Drive>>(i-1);  }
    }
    if(ir[0]>ir_compare)    {holdL =1;  }   
    if(ir[7]>ir_compare)    {holdR =1;  } 
    if(holdL==1)       ToLeft=255;
    if(holdR==1)       ToRight=255;
    
    direction = ToLeft;    
    direction -= ToRight;    
    
    if(direction>0)     {ToLeft = Motor_Main; ToRight = Motor_Main - direction;}
    if(direction==0)    {ToLeft = Motor_Drive; ToRight = Motor_Drive;}
    if(direction<0)     {ToLeft = Motor_Main+ direction; ToRight = Motor_Main;}
    
    PWM_1_WriteCompare1(ToLeft);
    PWM_1_WriteCompare2(ToRight);  
}


    void DriveBetter(uint8_t ir[8])
{     
    if(ir[0]>ir_compare){holdL =1;}
    if(ir[7]>ir_compare){holdR =1;}    
    if(holdL && holdR)  {  Straight(); }      
    if(holdL)  {HardTurn(Left); }
    if(holdR)  {HardTurn(Right);}       
    for (uint8_t i = 0; i < 3; i++){
        if(ir[1+i]>ir_compare){   holdL =0;   holdR =0;   Turn(Left,i);  return;}
        if(ir[6-i]>ir_compare){ holdL =0;   holdR =0;   Turn(Right,i);  return;}
    }
    if(!holdL && !holdR)    Straight();     
}
void DriveBetterSwing(uint8_t ir[8])
{     
    if(ir[0]>ir_compare || ir[1]>ir_compare){holdL =1;}
    if(ir[7]>ir_compare || ir[6]>ir_compare){holdR =1;}    
    if(holdL && holdR)  {  Straight(); }      
    if(holdL)  {HardTurn(Left); }
    if(holdR)  {HardTurn(Right);}       
    for (uint8_t i = 0; i < 3; i++){
        if(ir[1+i]>ir_compare){   holdL =0;   holdR =0;   Turn_Difference(Left,i);  return;}
        if(ir[6-i]>ir_compare){ holdL =0;   holdR =0;   Turn_Difference(Right,i);  return;}
    }
    if(!holdL && !holdR)    Straight(); 
}
    
void Straight()
{    
    Pin_Motor_1_Write(Forward);
    Pin_Motor_2_Write(Forward);
    PWM_1_WriteCompare1(Motor_Drive);
    PWM_1_WriteCompare2(Motor_Drive);  
}
void Backwards()
{    
    Pin_Motor_1_Write(Backward);
    Pin_Motor_2_Write(Backward);
    PWM_1_WriteCompare1(Motor_Drive);
    PWM_1_WriteCompare2(Motor_Drive);  
}
void HardTurn(_Bool left_right)
{
    if(left_right)  {Pin_Motor_1_Write(Backward);   Pin_Motor_2_Write(Forward); Pin_Led_5_Write(1);}
    else            {Pin_Motor_1_Write(Forward);    Pin_Motor_2_Write(Backward);Pin_Led_1_Write(1);}
    PWM_1_WriteCompare1(Motor_Turn);
    PWM_1_WriteCompare2(Motor_Turn);
}
void Turn(_Bool left_right, uint8_t irLocation)
{    
    Pin_Motor_1_Write(Forward);
    Pin_Motor_2_Write(Forward);    
    if(left_right)
    {
        PWM_1_WriteCompare1(motor_Direction_Low[irLocation]);
        PWM_1_WriteCompare2(motor_Direction_High[irLocation]);
    }   
    else          
    {
        PWM_1_WriteCompare1(motor_Direction_High[irLocation]);
        PWM_1_WriteCompare2(motor_Direction_Low[irLocation]);
    }     
}
void Turn_Difference(_Bool left_right, uint8_t irLocation)
{    
    Pin_Motor_1_Write(Forward);
    Pin_Motor_2_Write(Forward);    
    if(left_right)  
    {
        PWM_1_WriteCompare1(Motor_Drive-motor_Difference[irLocation]);
        PWM_1_WriteCompare2(Motor_Turn);
    }   
    else            
    {
        PWM_1_WriteCompare1(Motor_Turn);   
        PWM_1_WriteCompare2(Motor_Drive-motor_Difference[irLocation]);
    }     
}
/* [] END OF FILE */
