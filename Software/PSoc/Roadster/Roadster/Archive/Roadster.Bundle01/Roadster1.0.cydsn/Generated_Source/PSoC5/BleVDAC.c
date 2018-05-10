/*******************************************************************************
* File Name: BleVDAC.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "BleVDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 BleVDAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 BleVDAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static BleVDAC_backupStruct BleVDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: BleVDAC_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_Init(void) 
{
    BleVDAC_CR0 = (BleVDAC_MODE_V );

    /* Set default data source */
    #if(BleVDAC_DEFAULT_DATA_SRC != 0 )
        BleVDAC_CR1 = (BleVDAC_DEFAULT_CNTL | BleVDAC_DACBUS_ENABLE) ;
    #else
        BleVDAC_CR1 = (BleVDAC_DEFAULT_CNTL | BleVDAC_DACBUS_DISABLE) ;
    #endif /* (BleVDAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(BleVDAC_DEFAULT_STRB != 0)
        BleVDAC_Strobe |= BleVDAC_STRB_EN ;
    #endif/* (BleVDAC_DEFAULT_STRB != 0) */

    /* Set default range */
    BleVDAC_SetRange(BleVDAC_DEFAULT_RANGE); 

    /* Set default speed */
    BleVDAC_SetSpeed(BleVDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: BleVDAC_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_Enable(void) 
{
    BleVDAC_PWRMGR |= BleVDAC_ACT_PWR_EN;
    BleVDAC_STBY_PWRMGR |= BleVDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(BleVDAC_restoreVal == 1u) 
        {
             BleVDAC_CR0 = BleVDAC_backup.data_value;
             BleVDAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: BleVDAC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  BleVDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void BleVDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(BleVDAC_initVar == 0u)
    { 
        BleVDAC_Init();
        BleVDAC_initVar = 1u;
    }

    /* Enable power to DAC */
    BleVDAC_Enable();

    /* Set default value */
    BleVDAC_SetValue(BleVDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: BleVDAC_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_Stop(void) 
{
    /* Disble power to DAC */
    BleVDAC_PWRMGR &= (uint8)(~BleVDAC_ACT_PWR_EN);
    BleVDAC_STBY_PWRMGR &= (uint8)(~BleVDAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        BleVDAC_backup.data_value = BleVDAC_CR0;
        BleVDAC_CR0 = BleVDAC_CUR_MODE_OUT_OFF;
        BleVDAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: BleVDAC_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    BleVDAC_CR0 &= (uint8)(~BleVDAC_HS_MASK);
    BleVDAC_CR0 |=  (speed & BleVDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: BleVDAC_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_SetRange(uint8 range) 
{
    BleVDAC_CR0 &= (uint8)(~BleVDAC_RANGE_MASK);      /* Clear existing mode */
    BleVDAC_CR0 |= (range & BleVDAC_RANGE_MASK);      /*  Set Range  */
    BleVDAC_DacTrim();
}


/*******************************************************************************
* Function Name: BleVDAC_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 BleVDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    BleVDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        BleVDAC_Data = value;
        CyExitCriticalSection(BleVDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: BleVDAC_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void BleVDAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((BleVDAC_CR0 & BleVDAC_RANGE_MASK) >> 2) + BleVDAC_TRIM_M7_1V_RNG_OFFSET;
    BleVDAC_TR = CY_GET_XTND_REG8((uint8 *)(BleVDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
