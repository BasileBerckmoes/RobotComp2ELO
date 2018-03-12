/*******************************************************************************
* File Name: main.c
*
* Version: 2.10
*
* Description:
*  The PWM datasheet example project.
*  This example project demonstrates 8 bit PWM Fixed Function Block.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1: Enables the clock
*   2: Initializes the LCD
*   3: Start the PWM
*   4: Write a byte to control register to set Kill mode
*   5: Read the current value assigned to a Control Register 
*   6: Read the current value assigned to Status Register
*   7: Print Period value in LCD
*   8: Print Compare value in LCD
*   9: Print current status of PWM output in LCD
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    /* Prepare components */
    clock_1_Enable();    
    CharLCD_1_Start();
    PWM_1_Start();    
    
    /* Write a byte to a Control Register */
    Control_Reg_1_Write(0x00u);
    /* Read the current value assigned to a Control Register */
    Control_Reg_1_Read();
    /* Read the current value assigned to Status Register */
    Status_Reg_1_Read();
    
    /* Display current Period, Compare value, status of PWM output */
    CharLCD_1_Position(0u, 0u);
    CharLCD_1_PrintString("PWM BASIC TEST");
    CharLCD_1_Position(1u, 0u);
    CharLCD_1_PrintInt8(PWM_1_ReadPeriod());        
    CharLCD_1_Position(1u, 5u);
    CharLCD_1_PrintInt8(PWM_1_ReadCompare());  
    CharLCD_1_Position(1u, 10u);
    CharLCD_1_PrintInt8(Status_Reg_1_Read());
    
    for (;;)
    {
        CharLCD_1_Position(1u, 10u);
        CharLCD_1_PrintInt8(Status_Reg_1_Read());
    }
}


/* [] END OF FILE */
