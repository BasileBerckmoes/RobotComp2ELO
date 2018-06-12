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

#include "projectMain.h"
#include "project.h"
#include "string.h"
#include "stdio.h"
#include "myUART.h"

CY_ISR(sendBleData) 
{
    char strBuffer[10];
    
    //char hexDecBuffer[2];
    //DecToHex(pwml, hexDecBuffer);
    sprintf(strBuffer, "X/%X/\r\n", valueX); 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
    
    //DecToHex(pwmr, hexDecBuffer);
    sprintf(strBuffer, "Y/%X/\r\n",valueY); 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
}

void ProcessCommandMsg(void)
{
    char hexInputBuffer[2];
    if (RB.cmd == 'I')
    {  
        IRWaarden = getCMDValue('/', RB.valstr, hexInputBuffer);
        sprintf(strMsg1,"IRWaarde=%u\r", IRWaarden); 
        puttyUart1_PutString(strMsg1);

    } 
    else if (RB.cmd == 'T')
    {
        TestGetal = getCMDValue('/', RB.valstr, hexInputBuffer);
        //sprintf(strMsg1,"TestGetal=%u\r\n", TestGetal); 
//        puttyUart1_PutString(strMsg1);
    }
}

    
/* [] END OF FILE */
