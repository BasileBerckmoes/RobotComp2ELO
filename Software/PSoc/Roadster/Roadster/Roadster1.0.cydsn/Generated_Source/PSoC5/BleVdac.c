/*******************************************************************************
* File Name: BleVdac.c  
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
#include "BleVdac.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 BleVdac_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 BleVdac_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static BleVdac_backupStruct BleVdac_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: BleVdac_Init
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
void BleVdac_Init(void) 
{
    BleVdac_CR0 = (BleVdac_MODE_V );

    /* Set default data source */
    #if(BleVdac_DEFAULT_DATA_SRC != 0 )
        BleVdac_CR1 = (BleVdac_DEFAULT_CNTL | BleVdac_DACBUS_ENABLE) ;
    #else
        BleVdac_CR1 = (BleVdac_DEFAULT_CNTL | BleVdac_DACBUS_DISABLE) ;
    #endif /* (BleVdac_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(BleVdac_DEFAULT_STRB != 0)
        BleVdac_Strobe |= BleVdac_STRB_EN ;
    #endif/* (BleVdac_DEFAULT_STRB != 0) */

    /* Set default range */
    BleVdac_SetRange(BleVdac_DEFAULT_RANGE); 

    /* Set default speed */
    BleVdac_SetSpeed(BleVdac_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: BleVdac_Enable
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
void BleVdac_Enable(void) 
{
    BleVdac_PWRMGR |= BleVdac_ACT_PWR_EN;
    BleVdac_STBY_PWRMGR |= BleVdac_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(BleVdac_restoreVal == 1u) 
        {
             BleVdac_CR0 = BleVdac_backup.data_value;
             BleVdac_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: BleVdac_Start
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
*  BleVdac_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void BleVdac_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(BleVdac_initVar == 0u)
    { 
        BleVdac_Init();
        BleVdac_initVar = 1u;
    }

    /* Enable power to DAC */
    BleVdac_Enable();

    /* Set default value */
    BleVdac_SetValue(BleVdac_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: BleVdac_Stop
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
void BleVdac_Stop(void) 
{
    /* Disble power to DAC */
    BleVdac_PWRMGR &= (uint8)(~BleVdac_ACT_PWR_EN);
    BleVdac_STBY_PWRMGR &= (uint8)(~BleVdac_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        BleVdac_backup.data_value = BleVdac_CR0;
        BleVdac_CR0 = BleVdac_CUR_MODE_OUT_OFF;
        BleVdac_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: BleVdac_SetSpeed
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
void BleVdac_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    BleVdac_CR0 &= (uint8)(~BleVdac_HS_MASK);
    BleVdac_CR0 |=  (speed & BleVdac_HS_MASK);
}


/*******************************************************************************
* Function Name: BleVdac_SetRange
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
void BleVdac_SetRange(uint8 range) 
{
    BleVdac_CR0 &= (uint8)(~BleVdac_RANGE_MASK);      /* Clear existing mode */
    BleVdac_CR0 |= (range & BleVdac_RANGE_MASK);      /*  Set Range  */
    BleVdac_DacTrim();
}


/*******************************************************************************
* Function Name: BleVdac_SetValue
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
void BleVdac_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 BleVdac_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    BleVdac_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        BleVdac_Data = value;
        CyExitCriticalSection(BleVdac_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: BleVdac_DacTrim
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
void BleVdac_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((BleVdac_CR0 & BleVdac_RANGE_MASK) >> 2) + BleVdac_TRIM_M7_1V_RNG_OFFSET;
    BleVdac_TR = CY_GET_XTND_REG8((uint8 *)(BleVdac_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
