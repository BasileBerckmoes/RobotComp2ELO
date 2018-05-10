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
    if((valueY > 120 && valueY < 130) && (valueX > 120 && valueX < 130)) {
        pwml = 0;
        pwmr = 0;
    } else if (valueY > 127) {
        if (valueX > 115 && valueX < 135) {
            pwml = 80;//(valueY - 127) * 2 - 200;
            pwmr = pwml;
        } else if (valueX > 124 && valueX < 192) {
            pwmr = 80;//255 - 200;
            //pwmr = 45;//(valueX - 125) * 2 - 200;
            pwml = 60;
        } 
        else if (valueX > 192) {
            pwmr = 80;//255 - 200;
            //pwmr = 45;//(valueX - 125) * 2 - 200;
            pwml = 25;
        }  else if (valueX < 124 && valueX > 64) {
            pwml = 80;//255 - 200;
            //else pwml = 45;//valueX * 2 - 200;
            pwmr = 50;
        }  else if (valueX < 64) {
            pwml = 80;//255 - 200;
            //else pwml = 45;//valueX * 2 - 200;
            pwmr = 25;
        }
    }
    
    if (pwml > 110 || pwmr > 110) {
        pwml = 0;
        pwmr = 0;
    }
    
    char strBuffer[10];
    
////////    sprintf(strBuffer, "L/%u/\r\n", pwml);
////////    puttyUart1_PutString(strBuffer);
////////    sprintf(strBuffer, "R/%u/\r\n", pwmr);
////////    puttyUart1_PutString(strBuffer);
    char hexDecBuffer[2];
    DecToHex(pwml, hexDecBuffer);
    sprintf(strBuffer, "L/%s/\r\n", hexDecBuffer); 
    bleUart1_PutString(strBuffer);
    puttyUart1_PutString(strBuffer);
    
    DecToHex(pwmr, hexDecBuffer);
    sprintf(strBuffer, "R/%s/\r\n",hexDecBuffer); 
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
