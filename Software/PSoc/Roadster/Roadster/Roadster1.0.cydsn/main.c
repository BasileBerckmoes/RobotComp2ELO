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
uint_fast8_t infraRoodWaarden[8];



CY_ISR(IRSensoren)
{
   for(int i = 0; i < 8; i++)
   {
    infraRoodWaarden[i] = ADC_IR_GetResult16(i);
   }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    readIRSensors_StartEx(IRSensoren);

    LCD_Start();
    LCD_Position(0u, 0u);
    LCD_PrintString("TEST");
    
    ADC_IR_Start();
    ADC_IR_StartConvert();
    
    while(SW1_Read() == 1){
        
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //telProcedure();
    for(;;)
    {
       
            LCD_CLEAR_DISPLAY;
            LCD_Position(0u,0u);
            LCD_PrintString("sensor: ");
            LCD_Position(0u,9u);
            LCD_PrintInt8(1);
            LCD_Position(1u,0u);
            LCD_PrintDecUint16(infraRoodWaarden[1]);
            LCD_PrintString("-------------------");
            
            CyDelay(500);
        
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
/* [] END OF FILE */
