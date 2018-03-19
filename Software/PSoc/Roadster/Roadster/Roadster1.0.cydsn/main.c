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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    readIRSensors_StartEx(IRSensoren);

    LCD_Start();
    LCD_Position(0u, 0u);
    LCD_PrintString("Druk om te starten");
    
    ADC_IR_Start();
    ADC_IR_StartConvert();
    
    while(SW1_Read() == 1){
        
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    telProcedure();
    for(;;)
    {
       
            LCD_CLEAR_DISPLAY;
            LCD_Position(0u,0u);
            LCD_PrintString("sensor: ");
            LCD_Position(0u,9u);
            LCD_PrintDecUint16(IRWaarden);
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
