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
char teller;

CY_ISR(dataBinnenPutty)
{
    char charBinnen = puttyUart1_GetChar();
    if (charBinnen == '\n') teller=charBinnen;
    puttyUart1_PutChar(charBinnen);
    
    //puttyUart1_PutChar(charBinnen);
    bleUart1_PutChar(charBinnen);
}

CY_ISR(bleAntwoord)
{
    
    char charBinnen = bleUart1_GetChar();
    teller++;
    puttyUart1_PutChar(charBinnen); 
    if(charBinnen == '\r')
    {
        bleUart1_PutChar('\n');
    }
    
   
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    rxPuttyISR_StartEx(dataBinnenPutty);
    
    rxBleISR_StartEx(bleAntwoord);
    
    LCDD_Start();
    LCDD_Position(0u,0u);
    LCDD_PrintString("hello");
    VDAC_Start();
    Opamp_1_Start();
    puttyUart1_Start();
    bleUart1_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        LCDD_Position(0u,0u);
        LCDD_PrintString("fuck this");
        LCDD_Position(1u,0u);
        LCDD_PrintString("TIME FOR WEED!");
        CyDelay(1000);
        LCDD_ClearDisplay();
        CyDelay(1000);
    }
}

/* [] END OF FILE */
