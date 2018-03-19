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
#include "projectMain.h"
///uint_fast8_t infraRoodWaarden[8];

uint8 IRWaarden;
uint8 IRDrempel = 200;

int afstandUS1 = 0;
uint8 selectUS = 0;

uint8 pwmMotor1;
uint8 pwmMotor2;

CY_ISR(IRSensoren)
{
   IRWaarden = 0;
   for(int i = 0; i < 8; i++)
   {
    if (ADC_IR_GetResult16(i) > IRDrempel)
    {
       uint8 tmpWaarde = exponent(2,i); 
       IRWaarden = IRWaarden | tmpWaarde;
    }
   }
}
CY_ISR(isrUltraSonen)
{
    LED1_Write(~LED1_Read());
    //afstandUS1 = Timer_1_ReadCounter();
}    

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   // readIRSensors_StartEx(IRSensoren);
    isrUltraSonen_StartEx(isrUltraSonen);
    
    LED1_Write(0);
    
    LCD_Start(); 
    LCD_Position(0u, 0u);
    LCD_PrintString("S");
    
    ADC_IR_Start();
    ADC_IR_StartConvert();
    
   // Timer_1_Enable();
   // Timer_1_Start();
    TimerUS_Start();
   
    
    
    while(SW1_Read() == 1)
    {
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //telProcedure();
    for(;;)
    {
        if (selectUS >= 0 && selectUS <= 3)
        {
            selectUS++;
        }else selectUS = 0;
        selectUS_Write(selectUS);
        
        while(Echo1_Read() == 0)
        {
            TriggerReg_Write(1);
            CyDelayUs(10);
            TriggerReg_Write(0);
        }
        
        while(Echo1_Read() == 1){}
        afstandUS1 = TimerUS_ReadCounter();
            
            LCD_CLEAR_DISPLAY;
            LCD_Position(0u,0u);
            LCD_PrintString("sensor: ");
            LCD_Position(0u,9u);
            LCD_PrintDecUint16(afstandUS1);
            //LCD_Position(1u,0u);
            for(int i = 0; i < 8; i++)
            {
                LCD_Position(1,i);
                uint8 tmpWaarde =  exponent(2,i);
                if ((IRWaarden & tmpWaarde) == tmpWaarde)
                {
                    LCD_PrintDecUint16(1);
                }
                else 
                {
                     LCD_PrintDecUint16(0);
                }  
            }
            MotorControl_WriteCompare1(pwmMotor1);
            MotorControl_WriteCompare2(pwmMotor2);
    }
}

void telProcedure(void)
{
    LED1_Write(1);
    CyDelay(1000);
    LED2_Write(1);
    CyDelay(1000);
    LED3_Write(1);
    CyDelay(1000);
    LED4_Write(1);
    CyDelay(1000);
    LED5_Write(1);
    CyDelay(1000);
}

int exponent(int grondgetal, int exponent)
{
    uint8 tmpWaarde = 1;
    for (int i = 0; i < exponent ; i ++)
    {
        tmpWaarde = tmpWaarde * grondgetal;
    }
    return tmpWaarde;
}

/* [] END OF FILE */
