/*******************************************************************************
* File Name: `$INSTANCE_NAME`_cmd.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition related
*  to the SM/PMBus command processing.
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_SMBusSlave_`$INSTANCE_NAME`_cmd_H)
#define CY_SMBusSlave_`$INSTANCE_NAME`_cmd_H

/*`#START ADDITIONAL_SMBUS_SLAVE_CMD_H_INCLUDE`*/

/*`#END`*/


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* Command list based on customizer settings */
`$CommandsDefines`

/* Check if the component is bootloader component or project type is loadable */
#if((defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) || \
    (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLE))
    
    /* Check if bootloader commands are enabled */
    #ifdef `$INSTANCE_NAME`_BOOTLOAD_READ
        #define `$INSTANCE_NAME`_BTLDR_READ_EN  (1u)
    #endif /* `$INSTANCE_NAME`_BOOTLOAD_READ */
    #ifdef `$INSTANCE_NAME`_BOOTLOAD_WRITE
        #define `$INSTANCE_NAME`_BTLDR_WRITE_EN (1u)
    #endif /* `$INSTANCE_NAME`_BOOTLOAD_WRITE */

#endif /* (defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) ||
    (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLE) */


/***************************************
*      Data Struct Definitions
***************************************/

#if (CY_PSOC3)
    typedef struct
#elif defined (__GNUC__)
    typedef struct __attribute__ ((packed))
#else
    typedef __packed struct
#endif /* (__GNUC__) */
{
    uint8   command;
    uint8   dataLength;
    uint8 * dataPtr;
    uint8   cmdProp;               /* command properties (read/write/page-indexed) */
} `$INSTANCE_NAME`_CMD_TABLE_ENTRY;


/***************************************
*        Function Prototypes
***************************************/

uint8 `$INSTANCE_NAME`_CheckCommand(uint8 command)    `=ReentrantKeil($INSTANCE_NAME . "_CheckCommand")`;
uint8 `$INSTANCE_NAME`_ReadHandler(void)              `=ReentrantKeil($INSTANCE_NAME . "_ReadHandler")`;
void  `$INSTANCE_NAME`_WriteHandler(void)             `=ReentrantKeil($INSTANCE_NAME . "_WriteHandler")`;
void  `$INSTANCE_NAME`_CompleteRead(void)             `=ReentrantKeil($INSTANCE_NAME . "_CompleteRead")`;

/* Bootloader Specific APIs */
#if(defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN))
    void     `$INSTANCE_NAME`_CyBtldrCommStart(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStart")`;
    void     `$INSTANCE_NAME`_CyBtldrCommStop(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommStop")`;
    void     `$INSTANCE_NAME`_CyBtldrCommReset(void) CYSMALL `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommReset")`;
#endif /* defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN) */

#ifdef `$INSTANCE_NAME`_BTLDR_READ_EN
    cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 * pData, uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommWrite")`;
#endif /* `$INSTANCE_NAME`_BTLDR_READ_EN */

#ifdef `$INSTANCE_NAME`_BTLDR_WRITE_EN
    cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 * pData, uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             `=ReentrantKeil($INSTANCE_NAME . "_CyBtldrCommRead")`;
#endif /* `$INSTANCE_NAME`_BTLDR_WRITE_EN */


/***************************************
*           API Constants
***************************************/

/* Command properties */
#define `$INSTANCE_NAME`_CMD_WR_SUPPORT                 (0x40u)
#define `$INSTANCE_NAME`_CMD_WR_MANUAL                  (0x40u)
#define `$INSTANCE_NAME`_CMD_WR_AUTO                    (0x02u)
#define `$INSTANCE_NAME`_CMD_RD_SUPPORT                 (0x20u)
#define `$INSTANCE_NAME`_CMD_RD_MANUAL                  (0x20u)
#define `$INSTANCE_NAME`_CMD_RD_AUTO                    (0x01u)
#define `$INSTANCE_NAME`_CMD_PAGED                      (0x80u)
#define `$INSTANCE_NAME`_CMD_FMT_MASK                   (0x1Cu)
#define `$INSTANCE_NAME`_CMD_FMT_NON_NUMERIC            (0x1Cu)
#define `$INSTANCE_NAME`_CMD_FMT_LINEAR                 (0x00u)
#define `$INSTANCE_NAME`_CMD_FMT_SIGNED                 (0x04u)
#define `$INSTANCE_NAME`_CMD_FMT_DIRECT                 (0x0Cu)
#define `$INSTANCE_NAME`_CMD_FMT_UNSIGNED               (0x10u)
#define `$INSTANCE_NAME`_CMD_FMT_VID_MODE               (0x14u)
#define `$INSTANCE_NAME`_CMD_FMT_MANUFACTURER           (0x18u)
#define `$INSTANCE_NAME`_CMD_SUPPORTED                  (0x80u)

/* Command types and flags */
#define `$INSTANCE_NAME`_CMD_VALID                      (0x00u)
#define `$INSTANCE_NAME`_CMD_READ                       (0x01u)
#define `$INSTANCE_NAME`_CMD_WRITE                      (0x00u)
#define `$INSTANCE_NAME`_CMD_UNDEFINED                  (0xFFu)
#define `$INSTANCE_NAME`_NON_BLOCK_CMD                  (0x00u)
#define `$INSTANCE_NAME`_BLOCK_CMD                      (0x01u)

/* "All Pages" wild card */
#define `$INSTANCE_NAME`_CMD_ALL_PAGES                  (0xFFu)
#define `$INSTANCE_NAME`_SUPPORT_PAGE_CMD               (`$SupportPageCmd`u)

/* Bootloader status */
#define `$INSTANCE_NAME`_BTLDR_WR_CMPT                  (0x10u)
#define `$INSTANCE_NAME`_BTLDR_RD_CMPT                  (0x01u)

/* Helpers to check if a command size is valid. Greater or equal is used to take
* into account the PEC byte. For example, when the PEC is enabled and a host
* writes to a word command, the correct index value is 2 if the host does not
* send PEC, and 3 if it does. The index value greater than 3 results in a Host
* Sends Too Many Bytes fault and is detected in the ISR.
*/
#define `$INSTANCE_NAME`_CMD_LEN_VALID                  (`$INSTANCE_NAME`_bufferIndex >= `$INSTANCE_NAME`_bufferSize)

/* Byte and word commands have fixed number of bytes */ 
#define `$INSTANCE_NAME`_BYTE_CMD_LEN_VALID             (`$INSTANCE_NAME`_bufferIndex >= 1u)
#define `$INSTANCE_NAME`_WORD_CMD_LEN_VALID             (`$INSTANCE_NAME`_bufferIndex >= 2u)

#endif /* !defined(CY_SMBusSlave_`$INSTANCE_NAME`_cmd_H) */


/* [] END OF FILE */
