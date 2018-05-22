/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides the source code to the API for the SAMPLE/TRACK AND HOLD 
*  component.
*
* Note:
*  None
*
********************************************************************************
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

uint8 `$INSTANCE_NAME`_initVar = 0u;

/* static `$INSTANCE_NAME`_backupStruct  `$INSTANCE_NAME`_backup; */
#if (CY_PSOC5A)
    static `$INSTANCE_NAME`_backupStruct  `$INSTANCE_NAME`_P5backup;
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
    /* Configure SC Block based on selected Sample/Track type */
    #if (`$INSTANCE_NAME`_SAMPLE_TRACK_MODE == `$INSTANCE_NAME`_SAMPLEANDHOLD) /* Sample and hold mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_SAMPLEANDHOLD;
        
        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = (`$INSTANCE_NAME`_COMP_4P35PF  |
                                `$INSTANCE_NAME`_GAIN_0DB);
        #if(`$INSTANCE_NAME`_SAMPLE_CLOCK_EDGE == `$INSTANCE_NAME`_EDGE_POSITIVENEGATIVE)
            `$INSTANCE_NAME`_CR1_REG =  `$INSTANCE_NAME`_CR1_REG  | `$INSTANCE_NAME`_DIV2_DISABLE ;
        #else
            `$INSTANCE_NAME`_CR1_REG =  `$INSTANCE_NAME`_CR1_REG  | `$INSTANCE_NAME`_DIV2_ENABLE ;
        #endif
         
        #if(`$INSTANCE_NAME`_VREF_TYPE == `$INSTANCE_NAME`_EXTERNAL)
            `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_BIAS_LOW |
                                       `$INSTANCE_NAME`_REDC_00 | 
                                       `$INSTANCE_NAME`_GNDVREF_DI;
        #else
            `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_BIAS_LOW |
                                       `$INSTANCE_NAME`_REDC_00 | 
                                       `$INSTANCE_NAME`_GNDVREF_E;
        #endif
    #else
        /* Track and Hold Mode */
        /* SC Block mode -  - SCxx_CR0[3:1] */
        `$INSTANCE_NAME`_CR0_REG = `$INSTANCE_NAME`_MODE_TRACKANDHOLD; 
        
        /* SC Block CR1 */ 
        `$INSTANCE_NAME`_CR1_REG = `$INSTANCE_NAME`_COMP_4P35PF  |
                                   `$INSTANCE_NAME`_DIV2_ENABLE |
                                   `$INSTANCE_NAME`_GAIN_0DB;
                                
        /* SC Block CR2 */
        `$INSTANCE_NAME`_CR2_REG = `$INSTANCE_NAME`_BIAS_LOW |
                                   `$INSTANCE_NAME`_REDC_00 |
                                   `$INSTANCE_NAME`_GNDVREF_E;
    #endif /* end if - Sample/Track Type */
    
    /* Enable SC Block clocking */
    `$INSTANCE_NAME`_CLK_REG |= `$INSTANCE_NAME`_CLK_EN;
    
    /* Set default power */
    `$INSTANCE_NAME`_SetPower(`$INSTANCE_NAME`_INIT_POWER);
}


/*******************************************************************************   
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*  Enables the Sample/Track and Hold block operation
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
*  The start function initializes the Sample and Hold with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
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
    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
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
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the Sample/Track and Hold.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
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
