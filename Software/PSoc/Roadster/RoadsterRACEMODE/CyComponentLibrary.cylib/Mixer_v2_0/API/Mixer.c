/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the MIXER Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
    #include "`$INSTANCE_NAME`_aclk.h"
#endif /* `$INSTANCE_NAME`_LO_SOURCE */

/* Fixed configuration of SC Block only performed once */
uint8 `$INSTANCE_NAME`_initVar = 0u;

/* Only for PSoC5A */
#if (CY_PSOC5A)
    static `$INSTANCE_NAME`_backupStruct `$INSTANCE_NAME`_P5backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  `$INSTANCE_NAME`_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`
{
    float LOf = `$INSTANCE_NAME`_LO_CLOCK_FREQ;
    
    /* Configure SC Block based on selected Mixer type */
    /* Continuous Time (up) mixer */
    #if (`$INSTANCE_NAME`_MIXER_TYPE == `$INSTANCE_NAME`_CTMIXER) 
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_CTMIXER;   

        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_DIV2_DISABLE |
                                `$INSTANCE_NAME`_GAIN_0DB);                                 

        /* 
            Set SC Block resistor values based on Local Oscillator being above 
            or below 100kHz - controled by r20_40 (Rmix) bit for CT mode mixer
            and SC Block
        */

        if (LOf < `$INSTANCE_NAME`_LO_CLOCK_FREQ_100_KHz)
        {
            `$INSTANCE_NAME`_CR2_REG = (`$INSTANCE_NAME`_BIAS_LOW |
										`$INSTANCE_NAME`_REDC_01 |
										`$INSTANCE_NAME`_GNDVREF_DI |
										`$INSTANCE_NAME`_R20_40B_40K);
        }
        else
        {
            `$INSTANCE_NAME`_CR2_REG = (`$INSTANCE_NAME`_BIAS_LOW |
										`$INSTANCE_NAME`_REDC_01 |
										`$INSTANCE_NAME`_GNDVREF_DI |
										`$INSTANCE_NAME`_R20_40B_20K);
        }
    #else
        /* Discrete Time (down) mixer */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_DTMIXER;       

        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_DIV2_ENABLE |
                                `$INSTANCE_NAME`_GAIN_0DB);

        /* 
            Set SC Block resistor values based on Local Oscillator beign above 
            or below 100kHz - set r20_40 (input resitance) and rval (feedback) 
            resistor values seperately for DT mode and SC Block
        */
        if (LOf < `$INSTANCE_NAME`_LO_CLOCK_FREQ_100_KHz)
        {
            `$INSTANCE_NAME`_CR2_REG = (`$INSTANCE_NAME`_BIAS_LOW |
										`$INSTANCE_NAME`_GNDVREF_DI |
										`$INSTANCE_NAME`_R20_40B_40K |
										`$INSTANCE_NAME`_RVAL_40K); 
        }
        else
        {
            `$INSTANCE_NAME`_CR2_REG = (`$INSTANCE_NAME`_BIAS_LOW |
										`$INSTANCE_NAME`_GNDVREF_DI |
										`$INSTANCE_NAME`_R20_40B_20K |
										`$INSTANCE_NAME`_RVAL_20K);
        }
    #endif /* end if - Mixer Type */

    /* Enable SC Block clocking */
    `$INSTANCE_NAME`_CLK_REG |= `$INSTANCE_NAME`_CLK_EN;

    /* Set default power */
    `$INSTANCE_NAME`_SetPower(`$INSTANCE_NAME`_INIT_POWER);
    
    /* Set 50 % Duty cycle for LO clock if LO source is internal */
    #if(`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
        `$INSTANCE_NAME`_aclk_SetMode(CYCLK_DUTY);
    #endif /* `$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL */

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*  
* Summary: 
*  Enables the Mixer block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(`$INSTANCE_NAME`_P5backup.enableState == 1u)
        {
            `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_P5backup.scCR1Reg;
            `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_P5backup.scCR2Reg;
            `$INSTANCE_NAME`_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */
    
    /* Enable power to SC block in active mode */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG |= `$INSTANCE_NAME`_ACT_PWR_EN;

    /* Enable power to SC block in Alternative active mode */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG |= `$INSTANCE_NAME`_STBY_PWR_EN;
    
    /* Enable LO_Internal clock if LO source is choosen as internal */
    #if(`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
        /* Enable power to the LO clock */
        `$INSTANCE_NAME`_PWRMGR_ACLK_REG |= `$INSTANCE_NAME`_ACT_PWR_ACLK_EN;        
        `$INSTANCE_NAME`_STBY_PWRMGR_ACLK_REG |= `$INSTANCE_NAME`_STBY_PWR_ACLK_EN;
        /* Enable the clock */
        `$INSTANCE_NAME`_aclk_Enable();        
    #endif /* `$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL */

    `$INSTANCE_NAME`_PUMP_CR1_REG |= `$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                `$INSTANCE_NAME`_BSTCLK_REG &= (uint8)(~`$INSTANCE_NAME`_BST_CLK_INDEX_MASK);
                `$INSTANCE_NAME`_BSTCLK_REG |= `$INSTANCE_NAME`_BST_CLK_EN | CyScBoostClk__INDEX;
                `$INSTANCE_NAME`_SC_MISC_REG |= `$INSTANCE_NAME`_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                `$INSTANCE_NAME`_BSTCLK_REG &= (uint8)(~`$INSTANCE_NAME`_BST_CLK_EN);
                `$INSTANCE_NAME`_SC_MISC_REG &= (uint8)(~`$INSTANCE_NAME`_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*  The start function initializes the SC block control registers based on the
*  Mixer type selected and and enables power to the SC block
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Global variables:
*  `$INSTANCE_NAME`_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Theory: 
*  Full initialization of the SC Block configuration registers is only perfomed 
*  the first time the routine executes - global variable 
*  `$INSTANCE_NAME`_initVar is used indicate that the static configuration has 
*  been completed.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`
{
    /* If not Initialized then initialize all required hardware and software */
    if(`$INSTANCE_NAME`_initVar == 0u)
    {
        `$INSTANCE_NAME`_Init();
        `$INSTANCE_NAME`_initVar = 1u;
    }
    /* Enable the power to the block */
    `$INSTANCE_NAME`_Enable();
    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Disables power to SC block.
*
* Parameters:  
*  void 
*
* Return: 
*  void 
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`
{       
    /* Disble power to the Amp in Active mode template */
    `$INSTANCE_NAME`_PM_ACT_CFG_REG &= (uint8)(~`$INSTANCE_NAME`_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    `$INSTANCE_NAME`_PM_STBY_CFG_REG &= (uint8)(~`$INSTANCE_NAME`_STBY_PWR_EN);
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            `$INSTANCE_NAME`_BSTCLK_REG &= (uint8)(~`$INSTANCE_NAME`_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((`$INSTANCE_NAME`_PM_ACT_CFG_REG & `$INSTANCE_NAME`_PM_ACT_CFG_MASK) == 0u)
            {
                `$INSTANCE_NAME`_SC_MISC_REG &= (uint8)(~`$INSTANCE_NAME`_PUMP_FORCE);
                `$INSTANCE_NAME`_PUMP_CR1_REG &= (uint8)(~`$INSTANCE_NAME`_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* This sets Sample and hold in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        `$INSTANCE_NAME`_P5backup.scCR1Reg = `$INSTANCE_NAME`_CR1_REG;
        `$INSTANCE_NAME`_P5backup.scCR2Reg = `$INSTANCE_NAME`_CR2_REG;
        `$INSTANCE_NAME`_CR1_REG = 0x00u;
        `$INSTANCE_NAME`_CR2_REG = 0x00u;
        `$INSTANCE_NAME`_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */  
    
    /* Disable aclk */
    #if(`$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL)
        /* Disable power to clock */
        `$INSTANCE_NAME`_PWRMGR_ACLK_REG &= (uint8)(~`$INSTANCE_NAME`_ACT_PWR_ACLK_EN);
        `$INSTANCE_NAME`_STBY_PWRMGR_ACLK_REG &= (uint8)(~`$INSTANCE_NAME`_STBY_PWR_ACLK_EN);
        /* Disable the clock */
        `$INSTANCE_NAME`_aclk_Disable();
    #endif /* `$INSTANCE_NAME`_LO_SOURCE == `$INSTANCE_NAME`_LO_SOURCE_INTERNAL */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Set the drive power of the MIXER
*
* Parameters:  
*  power:  Sets power level between (0) and (3) high power
*
* Return: 
*  void 
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPower(uint8 power) `=ReentrantKeil($INSTANCE_NAME . "_SetPower")`
{
    uint8 tmpCR;

    /* Sets drive bits in SC Block Control Register 1:  SCxx_CR[1:0] */    
    tmpCR = `$INSTANCE_NAME`_CR1_REG & (uint8)(~`$INSTANCE_NAME`_DRIVE_MASK);
    tmpCR |= (power & `$INSTANCE_NAME`_DRIVE_MASK);
    `$INSTANCE_NAME`_CR1_REG = tmpCR;  
}


/* [] END OF FILE */
