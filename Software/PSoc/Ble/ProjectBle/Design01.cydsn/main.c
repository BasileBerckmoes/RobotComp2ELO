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


CY_ISR(dataBinnenPutty)
{
    char charBinnen = puttyUart1_GetChar();
    puttyUart1_PutChar(charBinnen);
    
    bleUart1_PutString("AT");
}

CY_ISR(bleAntwoord)
{
    char charBinnen = bleUart1_GetChar();
    puttyUart1_PutChar(charBinnen);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    rxPuttyISR_StartEx(dataBinnenPutty);
    
    rxBleISR_StartEx(bleAntwoord);
    
    VDAC_Start();
    Opamp_1_Start();
    puttyUart1_Start();
    bleUart1_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
