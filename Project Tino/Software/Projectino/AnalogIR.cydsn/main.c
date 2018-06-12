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
#include "project.h"
#include "LiquidCrystal_I2C.h"
#include "Driving.h"

#define  Addr 0x27
#define ir_compare2 90

uint32_t distances[3] ={0,0,0};
uint8_t ir[8];
uint8 links = 8;
uint8 rechts = 8;

CY_ISR(isr_ADC_1_Main)
{       
    for (uint8_t i = 0; i < 8; i++){
        ir[i]=ADC_SAR_Seq_1_GetResult16(i);   
    }       
    //Drive(ir);    
    DriveBetter(ir); 
    isr_ADC_1_ClearPending();
}

CY_ISR(isr_UltraSoon_Main)
{               
    //time = counter/frequentie                 24Mhz => will give time in seconds, when using 24 it will give time in us
    //distance = time*V/2   *E3                 V is soundspeed 343m/s, E3 is to get answer in mm
    //distance = (counter/frequentie )*V/2  *E3
    //distance = counter /24E6 *343 /2   *E3 
    //distance = counter *114.33E-3/ 2^4          
    //distance = counter *114.33  /E3  >>4      We wanna bitshift as much as possible to improve performence   
    //distance = counter *117    >>14           E3~=2^10 
    //distance = counter *117    >>5            Register can hold 8 bits so we just take the 8MSB of the 17Bits     
    /*
    distances[0] = (((uint16)Status_Reg_UltraSoon_1_Read()) *117 )>> 5;
    distances[1] = (((uint16)Status_Reg_UltraSoon_2_Read()) *117 )>> 5;
    distances[2] = (((uint16)Status_Reg_UltraSoon_3_Read()) *117 )>> 5;
   *//*
    distances[0] = (Status_Reg_UltraSoon_1_Read());
    distances[1] = (Status_Reg_UltraSoon_2_Read()) ;
    distances[2] = (Status_Reg_UltraSoon_3_Read()) ;*/
   //     distances[0] = (((uint16)Status_Reg_UltraSoon_1_Read()) *117 )>> 5;
    //constant might have to be altered for when in motion. Dopler effect    
    
    
    /*    
    //time = counter/frequentie                 24Mhz => will give time in seconds, when using 24 it will give time in us
    //distance = time*V/2   *E3                 V is soundspeed 343m/s, E3 is to get answer in mm
    //distance = (counter/frequentie )*V/2  *E3
    //distance = counter /750E3 *343 /2   *E3 
    //distance = counter *457.33E-3/ 2          
    //distance = counter *457.33  /E3  >>1      We wanna bitshift as much as possible to improve performence   
    //distance = counter *468.3    >>11           E3~=2^10 
    //distance = counter *468.3    >>3            Register can hold 8 bits so we just take the 8MSB of the 17Bits

    distances[0] = ((((uint32_t)Status_Reg_UltraSoon_2_Read()) *468 )>>3)+((((uint32_t)Status_Reg_UltraSoon_1_Read()) *468 )>> 11);
    */
    
    /*    
    //time = counter/frequentie                 24Mhz => will give time in seconds, when using 24 it will give time in us
    //distance = time*V/2   *E3                 V is soundspeed 343m/s, E3 is to get answer in mm
    //distance = (counter/frequentie )*V/2  *E3
    //distance = counter /3E6 *343 /2   *E3 
    //distance = counter *114.33E-3/ 2          
    //distance = counter *114.33  /E3  >>1      We wanna bitshift as much as possible to improve performence   
    //distance = counter *117    >>11           E3~=2^10 
    //distance = counter *117    >>5            Register can hold 8 bits so we just take the 8MSB of the 17Bits   

    distances[0] = ((((uint32_t)Status_Reg_UltraSoon_2_Read()) *468 )>>3)+((((uint32_t)Status_Reg_UltraSoon_1_Read()) *468 )>> 11);
    */
    distances[1] = (uint32_t)Status_Reg_UltraSoon_1_Read();
    distances[2] = ((uint32_t)Status_Reg_UltraSoon_2_Read());
     distances[0] = distances[2]  *117 +((distances[1]*117 )>> 8);
}
CY_ISR(isr_UltraSoon_ToClose_Main)
{ 
    //muur corrigerend
    /*
    if(Status_Reg_UltraSoon_3_Read() == 1)  //links is grotere afstand dan rechts
    {        
        PWM_1_WriteCompare1(Motor_Main);
        PWM_1_WriteCompare2(0);
    }
    else
     {        
        PWM_1_WriteCompare1(0);
        PWM_1_WriteCompare2(Motor_Main);
    }*/
    
    Backwards();
    CyDelay(250);
    
    isr_UltraSoon_ClearPending();
    isr_UltraSoon_ToClose_ClearPending();
    //isr_ADC_1_ClearPending();
}

CY_ISR(isr_btn_1_Main)
{
    PWM_1_Stop();
}
CY_ISR(isr_btn_2_Main)
{    
    PWM_1_Enable();
}
CY_ISR(isr_btn_3_Pressed_Main)
{
    PWM_1_Stop();
    Pin_Led_1_Write(1);
    Pin_Led_2_Write(1);    
    Pin_Led_3_Write(1);    
    Pin_Led_4_Write(1);    
    Pin_Led_5_Write(1);
}
CY_ISR(isr_btn_3_Main)
{    
    isr_ADC_1_Disable();    
    isr_UltraSoon_Disable();        
    uint16_t second = 500;
    CyDelay(second);
    Pin_Led_1_Write(0);
    CyDelay(second);
    Pin_Led_2_Write(0);
    CyDelay(second);
    Pin_Led_3_Write(0);
    CyDelay(second);
    Pin_Led_4_Write(0);
    CyDelay(second);
    Pin_Led_5_Write(0);
    PWM_1_Enable();
    isr_ADC_1_Enable();
    isr_UltraSoon_Enable();
}

int main(void)
{
    CyDelay(500);
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Pin_Motor_1_Write(Forward);
    Pin_Motor_2_Write(Forward); 
        
    ADC_SAR_Seq_1_Start();
    PWM_1_Start();
    isr_btn_3_ClearPending();
    PWM_1_Stop();
    
    
    I2C_Start();             
    LiquidCrystal_I2C_init(Addr,16,2,0);       
    begin();  
    
    isr_ADC_1_StartEx(isr_ADC_1_Main);
    isr_UltraSoon_StartEx(isr_UltraSoon_Main);
    isr_UltraSoon_ToClose_StartEx(isr_UltraSoon_ToClose_Main);
    isr_btn_1_StartEx(isr_btn_1_Main);
    isr_btn_2_StartEx(isr_btn_2_Main);
    isr_btn_3_Pressed_StartEx(isr_btn_3_Pressed_Main);
    isr_btn_3_StartEx(isr_btn_3_Main);
    
    
    ADC_SAR_Seq_1_StartConvert();   
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        /*
        setCursor(0,0);
        clearLine(0);
        LCD_print_num(direction,10);   
                
        setCursor(6,0);        
        LCD_print_num(Motor_Main,10);
        setCursor(12,0);
        LCD_print_num(drivemode,10);
        CyDelay(200);
        setCursor(0,1);
        for (uint32_t i = 0; i < 7; i++){
            if(path<(128>>i))  LCD_print("0");
            else i=7;
        }        
        LCD_print_num(path,2);
        */
        
        //print ultrasoon
        /*
        setCursor(0,0);
        LCD_print("UltraSoon   "); 
          for (uint32_t i = 0; i < 3; i++){
            setCursor(i*4,1);
            
            if(distances[i]<100){LCD_print(" ");}  
            if(distances[i]<10){LCD_print(" ");}            
            LCD_print_num(distances[i],10);    
        }
        uint8 temp = distances[0]>>4;
        if(temp<100){LCD_print(" ");}  
            if(temp<10){LCD_print(" ");}            
            LCD_print_num(temp,10);
        */
        //analog ir value print
        /*
        uint8_t line,col;  
         setCursor(0,0);
        for (uint8_t i = 0; i < 8; i++){
            line=   i/4;
            col =   (i-(line*4))*4;
            setCursor(col,line);
            if(ir[i]<100)   LCD_print(" ");            
            if(ir[i]<10)    LCD_print(" ");             
            LCD_print_num(ir[i],10);
        }
        */
        setCursor(0,0);
         for (uint8_t i = 0; i < 8; i++){
            if(ir[i]<16)    LCD_print(" ");             
            LCD_print_num(ir[i],16);
        }
        setCursor(0,1);
        LCD_print("R");
        LCD_print_num(rechts,10);
        setCursor(13,1);
        LCD_print("L");
        LCD_print_num(links,10);
        
         setCursor(4,1);       
            if(distances[0]<10000){LCD_print(" ");}  
            if(distances[0]<1000){LCD_print(" ");}  
            if(distances[0]<100){LCD_print(" ");}  
            if(distances[0]<10){LCD_print(" ");}            
            LCD_print_num(distances[0],10); 
            setCursor(9,1); LCD_print("  ");
        /*
        clearLine(1);
        setCursor(0,1);
        LCD_print_num(ToLeft,10);
        LCD_print(" ");  
        LCD_print_num(holdL,2);        
        setCursor(8,1);
        LCD_print_num(ToRight,10);
        LCD_print(" ");  
        LCD_print_num(holdR,2);
        
        LCD_print(" ");  
        if(irNumber<100)   LCD_print(" ");            
        if(irNumber<10)    LCD_print(" ");  
        LCD_print_num(irNumber,10);*/
        
        //process time checker
        /*
        setCursor(0,0);        
        LCD_print_num(countmax,10);  
        for (uint16_t i = 0; i < 65535; i++){
            count=count+1;
        }               */
    }
}

/* [] END OF FILE */
