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
#include <string.h>
#include <stdlib.h> //atoi
#include <stdio.h> 
#include <myUART1.h>

char teller;

uint8 valueX=0;
uint8 valueY=0;

uint8 motorStatus = 0;

uint8 IRWaarden = 0;

CY_ISR(dataBinnenPutty)
{
    char charBinnen = puttyUart1_GetChar();
    puttyUart1_PutChar(charBinnen);
    bleUart1_PutChar(charBinnen);
    
    if (charBinnen == '\r')
    {
        puttyUart1_PutChar('\n');
    bleUart1_PutChar('\n');
    }
    
    //puttyUart1_PutChar(charBinnen);
    
}

CY_ISR(bleAntwoord)
{
    
    char charBinnen = bleUart1_GetChar();
    teller++;
    puttyUart1_PutChar(charBinnen); 
    //if(charBinnen == '\r')
    //{
    //    bleUart1_PutChar('\n');
    //}
}

CY_ISR(getJoystickValues)
{
    valueX=JoyStickADC_GetResult16(0);
    valueY= JoyStickADC_GetResult16(1);
}

CY_ISR(motorControl)
{
    
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
    
    JoyStickADC_Start();
    JoyStickADC_StartConvert();
    
    eocJoystickISR_StartEx(getJoystickValues);
    motorControlISR_StartEx(motorControl);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        
        if (IsCharReady())
        {
            if(GetRxStr())
            {
                ProcessCommandMsg();
            }
        }
        LCDD_Position(0u,0u);
        //LCDD_PrintString("fuck this");
        LCDD_Position(1u,0u);
        LCDD_PrintDecUint16(IRWaarden);
        CyDelay(1000);
        LCDD_ClearDisplay();
        CyDelay(1000);
    }
}
void ProcessCommandMsg(void){
    if (RB.cmd == 'I')
    {
        IRWaarden = RB.valstr[0];
    }
        
}
/* [] END OF FILE */
