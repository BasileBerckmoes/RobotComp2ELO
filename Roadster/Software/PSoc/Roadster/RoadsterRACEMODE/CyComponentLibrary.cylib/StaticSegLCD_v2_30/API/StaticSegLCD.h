/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This header file contains definitions associated with the Static Segment LCD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ST_SEG_LCD_`$INSTANCE_NAME`_H)
#define CY_ST_SEG_LCD_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include <`$INSTANCE_NAME`_Pins.h>


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* Print error if cy_boot version is below 3.0 */
#ifndef CY_PSOC5LP
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* CY_PSOC5LP */

#define `$INSTANCE_NAME`_PORT_SHIFT          (0x04u)
#define `$INSTANCE_NAME`_ROW_SHIFT           (0x08u)

/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;

`$writerDmaProtoEntry`


/***************************************
*        Function Prototypes
***************************************/

void   `$INSTANCE_NAME`_Init(void) `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
uint8  `$INSTANCE_NAME`_Enable(void) `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
uint8  `$INSTANCE_NAME`_Start(void) `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void   `$INSTANCE_NAME`_Stop(void) `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void   `$INSTANCE_NAME`_EnableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_EnableInt")`;
void   `$INSTANCE_NAME`_DisableInt(void) `=ReentrantKeil($INSTANCE_NAME . "_DisableInt")`;
void   `$INSTANCE_NAME`_ClearDisplay(void) `=ReentrantKeil($INSTANCE_NAME . "_ClearDisplay")`;
uint8  `$INSTANCE_NAME`_WritePixel(uint16 pixelNumber, uint8 pixelState)
                                                                    `=ReentrantKeil($INSTANCE_NAME . "_WritePixel")`;
uint8  `$INSTANCE_NAME`_ReadPixel(uint16 pixelNumber) `=ReentrantKeil($INSTANCE_NAME . "_ReadPixel")`;
uint8  `$INSTANCE_NAME`_WriteInvertState(uint8 invertState) `=ReentrantKeil($INSTANCE_NAME . "_WriteInvertState")`;
uint8  `$INSTANCE_NAME`_ReadInvertState(void) `=ReentrantKeil($INSTANCE_NAME . "_ReadInvertState")`;
void   `$INSTANCE_NAME`_Sleep(void) `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
uint8  `$INSTANCE_NAME`_Wakeup(void) `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void   `$INSTANCE_NAME`_RestoreConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void   `$INSTANCE_NAME`_SaveConfig(void) `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
`$writerHFuncDeclarations`

CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);

#define `$INSTANCE_NAME`_WRITE_PIXEL(pixelNumber, pixelState)    \
                                                        ((void) `$INSTANCE_NAME`_WritePixel(pixelNumber, pixelState))
#define `$INSTANCE_NAME`_READ_PIXEL(pixelNumber)                 (`$INSTANCE_NAME`_ReadPixel(pixelNumber))
#define `$INSTANCE_NAME`_FIND_PIXEL(port, pin, row)     \
                                                ((uint16) (((uint16) (((uint16) (row)) << `$INSTANCE_NAME`_ROW_SHIFT) +\
                                                    (uint16) (((uint16)(port)) << `$INSTANCE_NAME`_PORT_SHIFT)) + \
                                                       ((uint16)(pin))))


/***************************************
*           Global Variables
***************************************/
extern uint8 `$INSTANCE_NAME`_enableState;
extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*           API Constants
***************************************/

#if(CY_PSOC5)
    #define `$INSTANCE_NAME`_DMA_ADDRESS_MASK      (0xFFFFFFFFu)
#else
    #define `$INSTANCE_NAME`_DMA_ADDRESS_MASK      (0x0000FFFFu)
#endif /* (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD) */

#define `$INSTANCE_NAME`_ROW_LENGTH                (0x10u)

/* Number of pixels for different kind of LCDs */
#define `$INSTANCE_NAME`_7SEG_PIX_NUM              (0x07u)
#define `$INSTANCE_NAME`_14SEG_PIX_NUM             (0x0Eu)
#define `$INSTANCE_NAME`_16SEG_PIX_NUM             (0x10u)

/* Actually there is only one common line but we need to
* invert the signal on the common line for proper waveform generation.
*/
#define `$INSTANCE_NAME`_COMM_NUM                  (0x02u)

#define `$INSTANCE_NAME`_BIT_MASK                  (0x0007u)
#define `$INSTANCE_NAME`_PORT_MASK                 (0x00F0u)
#define `$INSTANCE_NAME`_ROW_MASK                  (0x0F00u)

#define `$INSTANCE_NAME`_NORMAL_STATE              (0x00u)
#define `$INSTANCE_NAME`_INVERTED_STATE            (0x01u)
#define `$INSTANCE_NAME`_STATE_MASK                (0x01u)

#define `$INSTANCE_NAME`_PIXEL_STATE_OFF           (0x00u)
#define `$INSTANCE_NAME`_PIXEL_STATE_ON            (0x01u)
#define `$INSTANCE_NAME`_PIXEL_STATE_INVERT        (0x02u)
#define `$INSTANCE_NAME`_PIXEL_UNKNOWN_STATE       (0xFFu)

#define `$INSTANCE_NAME`_TD_SIZE                   (0x10u)
#define `$INSTANCE_NAME`_BUFFER_LENGTH             (32u)

/* 0 - No leadig zeros, 1 - leadig zeros */
#define `$INSTANCE_NAME`_MODE_0                    (0x00u)
#define `$INSTANCE_NAME`_MODE_1                    (0x01u)

#define `$INSTANCE_NAME`_ROW_BYTE_LENGTH           (0x10u)

#define `$INSTANCE_NAME`_MAX_PORTS                 (0x10u)

#define `$INSTANCE_NAME`_ISR_NUMBER                (`$INSTANCE_NAME`_LCD_ISR__INTC_NUMBER)
#define `$INSTANCE_NAME`_ISR_PRIORITY              (`$INSTANCE_NAME`_LCD_ISR__INTC_PRIOR_NUM)

/* Defines index of "blank" digit in the look-up table for 7 segment helper */
#define `$INSTANCE_NAME`_7SEG_BLANK_DIG            (0x10u)

`$writerHPixelDef`


#define `$INSTANCE_NAME`_LCD_TD_SIZE               ((uint8) `$INSTANCE_NAME`_StSegLcdPort_DMA_TD_PROTO_COUNT)


/***************************************
*             Registers
***************************************/

#define `$INSTANCE_NAME`_ALIASED_AREA_PTR                        ((reg32) CYDEV_IO_DR_PRT0_DR_ALIAS)
#define `$INSTANCE_NAME`_PORT_BASE_PTR                           ((reg8 *) CYDEV_IO_PRT_PRT0_BASE)

#endif /* CY_ST_SEG_LCD_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
