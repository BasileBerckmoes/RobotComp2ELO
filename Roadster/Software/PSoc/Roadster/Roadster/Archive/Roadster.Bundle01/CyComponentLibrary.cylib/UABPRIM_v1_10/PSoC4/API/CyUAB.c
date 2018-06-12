/*!*****************************************************************************
* \file `$INSTANCE_NAME`_CyUAB.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief 
*   API for Universal Analog Block (UAB)
*
********************************************************************************
* \copyright
* (c) 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#if !defined(CyUAB_C)
#define CyUAB_C

#include "`$INSTANCE_NAME`_CyUAB.h"    

/******************* CyUAB_SetClock() *****************************************/
/*!
* @brief Write clock - handles filling a bit column that spans multiple memory locations.
* 
* @details There are 8 non-modbit clocks (pattern only) and 
* 4 modbit clocks (pattern and modbit) - this functions can set either type.
* Set the pattern and modbit pattern of a modbit clock and just the pattern for a non-modbit clock.
* Returns @c void.
* clocks fill columns that span multiple RAM locations.
*
* @c modbit is only used for modbit clocks (PHI9-PHI12)
* @c modbit is ignored for non-modbit clocks (PHI1-PHI8)
*
* Always write all 16 steps, because you don't know what was set previously 
* (and keeps the parameter list down to 4 - threshold for function calling method)
*
* A call to this function must be preceded by Start(), Init(), or ClearAllClocks()
* to initialize the wavestep SRAM.
* The UAB clocking must be presently stopped.
* Before enabling UAB clocking, as needed, modify lastStep with SetLastStep()
*   
* @internal
* @reglist @reg `$INSTANCE_NAME`_SRAM<tt>xx</tt>_REG<, where <tt>xx</tt> 
* spans 00 to 15.
*
* This function relies on several assumptions/definitions:
* @li The SRAM clocks are all stored contiguously in memory.
* @li The lowest address is `$INSTANCE_NAME`_UAB0_SRAM00.
* @li The modbit clocks start at phi_m1 = 9
* @li The modbit clocks take two consecutive bit fields within a step 
*
* The expression (8 + 2*(phi - 9)) This expression 
* simplifies to the one used for field shifting
*
* @endinternal
*
* @param uabSram starting address of UAB half waveform SRAM; ie `$INSTANCE_NAME`_SRAM1_PTR
* @param pattern clocking in LSbit to MSbit ordering for step 0 to step 15.
* When the @p modbitPattern is high, the
* modbit waveform (chosen by `$INSTANCE_NAME`_SetModbitSource()) is used as
* this clock.  @p pattern inverts the modbit waveform when high, doesn’t invert
* it when low.  When the @p modbitPattern is low, this clock simply follows
* @p pattern as it would for the non-modbit clocks.
* @param modbitPattern A pattern which describes when to use the modbit
* waveform as this clock. When @p modbitPattern is high, the
* modbit waveform (chosen by `$INSTANCE_NAME`_SetModbitSource()) is used as
* this clock.  @p pattern inverts the modbit waveform when high, doesn’t invert
* it when low.  When the @p modbitPattern is low, this clock simply follows
* @p pattern as it would for the non-modbit clocks.
*
* @param phi The clock to configure.  Function ignores all other values besides valid:
* @arg @c CyUAB_CLK_PHI1
* @arg @c CyUAB_CLK_PHI2
* @arg @c CyUAB_CLK_PHI3
* @arg @c CyUAB_CLK_PHI4
* @arg @c CyUAB_CLK_PHI5
* @arg @c CyUAB_CLK_PHI6
* @arg @c CyUAB_CLK_PHI7
* @arg @c CyUAB_CLK_PHI8
* @arg @c CyUAB_CLK_PHI9
* @arg @c CyUAB_CLK_PHI10
* @arg @c CyUAB_CLK_PHI11
* @arg @c CyUAB_CLK_PHI12
*
* @see
* 
* @sideeffect None
*******************************************************************************/
void CyUAB_SetClock( reg32 uabSram[], CyUAB_clk_enum phi, uint16 pattern, uint16 modbitPattern )
{
    const uint32 PATTERN_SHIFT = 0UL;
    const uint32 MODBIT_SHIFT = 1UL;
    const uint32 PATTERN_MASK = 1UL<<PATTERN_SHIFT;
    const uint32 MODBIT_MASK  = 1UL<<MODBIT_SHIFT;
    const uint32 BOTH_MASK = PATTERN_MASK | MODBIT_MASK;
    const int32 PHI9_SHIFT = ((int32)CyUAB_CLK_PHI9)-1;
    
    uint32 i;
    int32 shift;
    uint32 mask;
    uint32 modbitCopy;
    
    if( ( ((int32)CyUAB_CLK_PHI1) <= ((int32)phi) ) && ( ((int32)phi) <= ((int32)CyUAB_CLK_PHI12) ) )
    {
        if( ((int32)phi) > ((int32)CyUAB_CLK_PHI8) )
        {
            shift = (2*((int32)phi))+(PHI9_SHIFT-(2*((int32)CyUAB_CLK_PHI9) ) ); /* ==2*phi-10==(2*(phi-CyUAB_CLK_PHI9))+PHI9_SHIFT */
            mask  = BOTH_MASK<<shift;
            modbitCopy = ((uint32)modbitPattern)<<MODBIT_SHIFT; /* pre-shift, so correct for right shift at each iteration */
        }
        else
        {
            shift = phi-CyUAB_CLK_PHI1;
            mask = 1UL<<shift;
            modbitCopy = 0UL;
        }
        
        for( i=0UL; i<CyUAB_STEPS_LEN_MAX; ++i )
        {
            uabSram[i] = (uabSram[i]&(~mask)) | (((((modbitCopy>>i)&MODBIT_MASK)|((((uint32)pattern)>>i)&PATTERN_MASK))<<((uint32)shift))&mask);
        }
    }
}


/******************* CyUAB_SetNSteps() ****************************************/
/*!
* @brief Write all clocks as a series of steps 
* 
* @details Writes stepArray of size @c n steps to memory.
*
* @param uabSram starting address of UAB half waveform SRAM; ie `$INSTANCE_NAME`_SRAM1_PTR
* @param n number of steps to write (starting at step0)
* @param stepArray of size @c n - each elements represents a single step
* specification for all clocks
*
* @internal
* @reglist @reg 
* @image html _.png 
* UAB SRAM locations are 32-bits in size with only the first 16 bytes populated
* Only lower 16 bits of stepArray elements used
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void CyUAB_SetNSteps( reg32 uabSram[], size_t n, const uint16 stepArray[] )
{
    uint32 i;
    if( n<=CyUAB_STEPS_LEN_MAX )
    {
        for( i=0UL; i<n; i++ )
        {
            uabSram[i] = stepArray[i];
        }
    }
}

/***************** CyUAB_SetSingleStep() **************************************/
/*!
* @brief Write all clocks for a single step 
* 
* @details Allows patching specific steps (can use for dynamic reconfig)
*
* @param uabSram starting address of UAB half waveform SRAM; ie `$INSTANCE_NAME`_SRAM1_PTR
* @param idx index of the targeted step
* @param stepValue all clocks specified for a single step
*
* @internal
* @reglist @reg 
* @image html _.png 
* UAB SRAM locations are 32-bits in size with only the first 16 bytes populated
* Only lower 16 bits of stepArray elements used
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void CyUAB_SetSingleStep(reg32 uabSram[], size_t idx, const uint16 stepValue )
{
    if( idx<=CyUAB_STEPS_IDX_MAX )
    {
        uabSram[idx] = ((uint32)stepValue);
    } 
}

/*! 
* @brief wordset is like a 32-bit aligned memset()
*
* @param s pointer to memory block of 32-bit words
* @param c value to overwrite words
* @param size length of memory block in bytes 
*/
reg32* CyUAB_wordset( reg32 s[], uint32 c, size_t size )
{
    size_t n = size/sizeof(c);
    while( 0UL != n )
    {
        --n;
        s[n] = c;
    }
    return s;
}

#endif /* #ifndef CyUAB_C */

/* [] END OF FILE */
