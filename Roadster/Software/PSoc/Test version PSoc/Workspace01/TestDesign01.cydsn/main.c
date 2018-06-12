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

int main(void)
{
    AdcMux_Start();
    AdcMux_StartConvert();
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int aValue;
    int bValue;
    int cValue;
    for(;;)
    {
        aValue = AdcMux_GetResult16(0);
        bValue = AdcMux_GetResult16(1);
        cValue = AdcMux_GetResult16(2);
        
        if (aValue > 1000)LED1_Write(1);
        else LED1_Write(0);
        
        if (bValue > 1000)LED2_Write(1);
        else LED2_Write(0);
        
        if (cValue > 1000)LED3_Write(1);
        else LED3_Write(0);
       
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
