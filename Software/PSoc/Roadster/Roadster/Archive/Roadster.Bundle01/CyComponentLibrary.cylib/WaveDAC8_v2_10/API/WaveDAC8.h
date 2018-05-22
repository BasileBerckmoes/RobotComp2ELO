/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_`$INSTANCE_NAME`_H) 
#define CY_WaveDAC8_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include <`$INSTANCE_NAME`_Wave1_DMA_dma.h>
#include <`$INSTANCE_NAME`_Wave2_DMA_dma.h>
#include <`$INSTANCE_NAME`_`$DacModeReplString`.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_WAVE1_TYPE     (`$Wave1_Type`u)     /* Waveform for wave1 */
#define `$INSTANCE_NAME`_WAVE2_TYPE     (`$Wave2_Type`u)     /* Waveform for wave2 */
#define `$INSTANCE_NAME`_SINE_WAVE      (0u)
#define `$INSTANCE_NAME`_SQUARE_WAVE    (1u)
#define `$INSTANCE_NAME`_TRIANGLE_WAVE  (2u)
#define `$INSTANCE_NAME`_SAWTOOTH_WAVE  (3u)
#define `$INSTANCE_NAME`_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define `$INSTANCE_NAME`_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define `$INSTANCE_NAME`_WAVE1_LENGTH   (`$Wave1_Length`u)   /* Length for wave1 */
#define `$INSTANCE_NAME`_WAVE2_LENGTH   (`$Wave2_Length`u)   /* Length for wave2 */
	
#define `$INSTANCE_NAME`_DEFAULT_RANGE    (`$DAC_Range`u) /* Default DAC range */
#define `$INSTANCE_NAME`_DAC_RANGE_1V     (0u)
#define `$INSTANCE_NAME`_DAC_RANGE_1V_BUF (16u)
#define `$INSTANCE_NAME`_DAC_RANGE_4V     (1u)
#define `$INSTANCE_NAME`_DAC_RANGE_4V_BUF (17u)
#define `$INSTANCE_NAME`_VOLT_MODE        (0u)
#define `$INSTANCE_NAME`_CURRENT_MODE     (1u)
#define `$INSTANCE_NAME`_DAC_MODE         (((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`_DAC_RANGE_1V) || \
									  (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`_DAC_RANGE_4V) || \
							  		  (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`_DAC_RANGE_1V_BUF) || \
									  (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`_DAC_RANGE_4V_BUF)) ? \
									   `$INSTANCE_NAME`_VOLT_MODE : `$INSTANCE_NAME`_CURRENT_MODE)

#define `$INSTANCE_NAME`_DACMODE `$INSTANCE_NAME`_DAC_MODE /* legacy definition for backward compatibility */

#define `$INSTANCE_NAME`_DIRECT_MODE (0u)
#define `$INSTANCE_NAME`_BUFFER_MODE (1u)
#define `$INSTANCE_NAME`_OUT_MODE    (((`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`_DAC_RANGE_1V_BUF) || \
								 (`$INSTANCE_NAME`_DEFAULT_RANGE == `$INSTANCE_NAME`_DAC_RANGE_4V_BUF)) ? \
								  `$INSTANCE_NAME`_BUFFER_MODE : `$INSTANCE_NAME`_DIRECT_MODE)

#if(`$INSTANCE_NAME`_OUT_MODE == `$INSTANCE_NAME`_BUFFER_MODE)
    #include <`$INSTANCE_NAME`_BuffAmp.h>
#endif /* `$INSTANCE_NAME`_OUT_MODE == `$INSTANCE_NAME`_BUFFER_MODE */

#define `$INSTANCE_NAME`_CLOCK_INT      (1u)
#define `$INSTANCE_NAME`_CLOCK_EXT      (0u)
#define `$INSTANCE_NAME`_CLOCK_SRC      (`$Clock_SRC`u)

#if(`$INSTANCE_NAME`_CLOCK_SRC == `$INSTANCE_NAME`_CLOCK_INT)  
	#include <`$INSTANCE_NAME`_DacClk.h>
	#if defined(`$INSTANCE_NAME`_DacClk_PHASE)
		#define `$INSTANCE_NAME`_CLK_PHASE_0nS (1u)
	#endif /* defined(`$INSTANCE_NAME`_DacClk_PHASE) */
#endif /* `$INSTANCE_NAME`_CLOCK_SRC == `$INSTANCE_NAME`_CLOCK_INT */

#if (CY_PSOC3)
	#define `$INSTANCE_NAME`_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define `$INSTANCE_NAME`_Wave1_DMA_BYTES_PER_BURST      (1u)
#define `$INSTANCE_NAME`_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define `$INSTANCE_NAME`_Wave2_DMA_BYTES_PER_BURST      (1u)
#define `$INSTANCE_NAME`_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}`$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void `$INSTANCE_NAME`_Start(void)             `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void `$INSTANCE_NAME`_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        `=ReentrantKeil($INSTANCE_NAME . "_StartEx")`;
void `$INSTANCE_NAME`_Init(void)              `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void `$INSTANCE_NAME`_Enable(void)            `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void `$INSTANCE_NAME`_Stop(void)              `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;

void `$INSTANCE_NAME`_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        `=ReentrantKeil($INSTANCE_NAME . "_Wave1Setup")`;
void `$INSTANCE_NAME`_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        `=ReentrantKeil($INSTANCE_NAME . "_Wave2Setup")`;

void `$INSTANCE_NAME`_Sleep(void)             `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void `$INSTANCE_NAME`_Wakeup(void)            `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;

#define `$INSTANCE_NAME`_SetSpeed       `$INSTANCE_NAME`_`$DacModeReplString`_SetSpeed
#define `$INSTANCE_NAME`_SetRange       `$INSTANCE_NAME`_`$DacModeReplString`_SetRange
#define `$INSTANCE_NAME`_SetValue       `$INSTANCE_NAME`_`$DacModeReplString`_SetValue
#define `$INSTANCE_NAME`_DacTrim        `$INSTANCE_NAME`_`$DacModeReplString`_DacTrim
#define `$INSTANCE_NAME`_SaveConfig     `$INSTANCE_NAME`_`$DacModeReplString`_SaveConfig
#define `$INSTANCE_NAME`_RestoreConfig  `$INSTANCE_NAME`_`$DacModeReplString`_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;

extern const uint8 CYCODE `$INSTANCE_NAME`_wave1[`$INSTANCE_NAME`_WAVE1_LENGTH];
extern const uint8 CYCODE `$INSTANCE_NAME`_wave2[`$INSTANCE_NAME`_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(`$INSTANCE_NAME`_DAC_MODE == `$INSTANCE_NAME`_VOLT_MODE)
    #define `$INSTANCE_NAME`_RANGE_1V       (0x00u)
    #define `$INSTANCE_NAME`_RANGE_4V       (0x04u)
#else /* current mode */
    #define `$INSTANCE_NAME`_RANGE_32uA     (0x00u)
    #define `$INSTANCE_NAME`_RANGE_255uA    (0x04u)
    #define `$INSTANCE_NAME`_RANGE_2mA      (0x08u)
    #define `$INSTANCE_NAME`_RANGE_2048uA   `$INSTANCE_NAME`_RANGE_2mA
#endif /* `$INSTANCE_NAME`_DAC_MODE == `$INSTANCE_NAME`_VOLT_MODE */

/* Power setting for SetSpeed API */
#define `$INSTANCE_NAME`_LOWSPEED       (0x00u)
#define `$INSTANCE_NAME`_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define `$INSTANCE_NAME`_DAC8__D `$INSTANCE_NAME`_`$DacModeReplString`_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define `$INSTANCE_NAME`_HS_MASK        (0x02u)
#define `$INSTANCE_NAME`_HS_LOWPOWER    (0x00u)
#define `$INSTANCE_NAME`_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define `$INSTANCE_NAME`_MODE_MASK      (0x10u)
#define `$INSTANCE_NAME`_MODE_V         (0x00u)
#define `$INSTANCE_NAME`_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define `$INSTANCE_NAME`_RANGE_MASK     (0x0Cu)
#define `$INSTANCE_NAME`_RANGE_0        (0x00u)
#define `$INSTANCE_NAME`_RANGE_1        (0x04u)
#define `$INSTANCE_NAME`_RANGE_2        (0x08u)
#define `$INSTANCE_NAME`_RANGE_3        (0x0Cu)
#define `$INSTANCE_NAME`_IDIR_MASK      (0x04u)

#define `$INSTANCE_NAME`_DAC_RANGE      ((uint8)(`$DAC_Range`u << 2u) & `$INSTANCE_NAME`_RANGE_MASK)
#define `$INSTANCE_NAME`_DAC_POL        ((uint8)(`$DAC_Range`u >> 1u) & `$INSTANCE_NAME`_IDIR_MASK)


#endif /* CY_WaveDAC8_`$INSTANCE_NAME`_H  */

/* [] END OF FILE */
