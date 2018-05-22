/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  MDIO Slave Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_MDIO_SLAVE_`$INSTANCE_NAME`_H)
#define CY_MDIO_SLAVE_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Error message for removed `$INSTANCE_NAME`_bMDIO_CtlReg due to the resource optimization */
#ifdef `$INSTANCE_NAME`_bMDIO_CtlReg__REMOVED
    #error `$CY_COMPONENT_NAME` detected with a constant 0 for the enable. This will prevent the component from operating.
#endif /* `$INSTANCE_NAME`_bMDIO_CtlReg__REMOVED */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_OP_MODE                (`$OperationMode`u)
#define `$INSTANCE_NAME`_BASIC_MODE             (0u == `$INSTANCE_NAME`_OP_MODE)
#define `$INSTANCE_NAME`_ADVANCED_MODE          (1u == `$INSTANCE_NAME`_OP_MODE)

#define `$INSTANCE_NAME`_PHYADDR_MODE           (`$PhyAddressMode`u)
#define `$INSTANCE_NAME`_PHYADDR_FIRMWARE       (0u == `$INSTANCE_NAME`_PHYADDR_MODE)
#define `$INSTANCE_NAME`_PHYADDR_HARDWARE       (1u == `$INSTANCE_NAME`_PHYADDR_MODE)


/***************************************
*     Data Struct Definitions
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 interruptState;
} `$INSTANCE_NAME`_BACKUP_STRUCT;

/* Structure that contains configuration data for each register */
typedef struct
{
    uint16 mask;                /* 16 bit writeable mask */
    uint8  ctrlReg;             /* Control register value */
    uint8  reserved;            /* Reserved */
}
`$INSTANCE_NAME`_REG_CONFIG_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start(void)                              `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void  `$INSTANCE_NAME`_Init(void)                               `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void  `$INSTANCE_NAME`_Enable(void)                             `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void  `$INSTANCE_NAME`_Stop(void)                               `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;
void  `$INSTANCE_NAME`_Sleep(void)                              `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void  `$INSTANCE_NAME`_Wakeup(void)                             `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void  `$INSTANCE_NAME`_SaveConfig(void)                         `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void  `$INSTANCE_NAME`_RestoreConfig(void)                      `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;
void  `$INSTANCE_NAME`_EnableInt(void)                          `=ReentrantKeil($INSTANCE_NAME . "_EnableInt")`;
void  `$INSTANCE_NAME`_DisableInt(void)                         `=ReentrantKeil($INSTANCE_NAME . "_DisableInt")`;
void  `$INSTANCE_NAME`_SetPhyAddress(uint8 phyAddr)             `=ReentrantKeil($INSTANCE_NAME . "_SetPhyAddress")`;
void  `$INSTANCE_NAME`_SetDevAddress(uint8 devAddr)             `=ReentrantKeil($INSTANCE_NAME . "_SetDevAddress")`;
void  `$INSTANCE_NAME`_UpdatePhyAddress(void)                   `=ReentrantKeil($INSTANCE_NAME . "_UpdatePhyAddress")`;

#if(`$INSTANCE_NAME`_BASIC_MODE)

    void  `$INSTANCE_NAME`_PutData(uint16 regData)              `=ReentrantKeil($INSTANCE_NAME . "_PutData")`;
    void  `$INSTANCE_NAME`_ProcessFrame(uint8 * opCode, uint16 * regData)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_ProcessFrame")`;
#endif /* `$INSTANCE_NAME`_BASIC_MODE */

#if(`$INSTANCE_NAME`_ADVANCED_MODE)

    uint8   `$INSTANCE_NAME`_GetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_GetData")`;
    uint8   `$INSTANCE_NAME`_SetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetData")`;
    uint8   `$INSTANCE_NAME`_SetBits(uint16 address, uint16 regBits)
                                                                `=ReentrantKeil($INSTANCE_NAME . "_SetBits")`;
    uint16  `$INSTANCE_NAME`_GetAddress(void)                   `=ReentrantKeil($INSTANCE_NAME . "_GetAddress")`;

    uint8 * `$INSTANCE_NAME`_GetConfiguration(uint8 regSpace)   `=ReentrantKeil($INSTANCE_NAME . "_GetConfiguration")`;

    /* Macros to quickly determine register page data width and memory type */
    #define `$INSTANCE_NAME`_REG_SPACE_IS_SRAM(x)       (0u != ((`$INSTANCE_NAME`_PAGE_MEM_TYPE   >> (x)) & 0x01u))
    #define `$INSTANCE_NAME`_REG_SPACE_IS_8BIT(x)       (0u == ((`$INSTANCE_NAME`_PAGE_DATA_WIDTH >> (x)) & 0x01u))
    #define `$INSTANCE_NAME`_REG_SPACE_IS_16BIT(x)      (0u != ((`$INSTANCE_NAME`_PAGE_DATA_WIDTH >> (x)) & 0x01u))

    /* Check if DMA channel is currently being serviced by DMAC */
    #define `$INSTANCE_NAME`_DMA_ACTIVE(mask)           (0u == (`$INSTANCE_NAME`_FW_DMA_STS_REG & (mask)))

    /* Clear DMA completion status */
    #define `$INSTANCE_NAME`_CLEAR_FW_DMA_STATUS        ((void)`$INSTANCE_NAME`_FW_DMA_STS_REG)

#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*           API Constants
***************************************/

#define `$INSTANCE_NAME`_DISABLED                   (0x00u)
#define `$INSTANCE_NAME`_ENABLED                    (0x01u)
#define `$INSTANCE_NAME`_ADDR_PATTERN               (0xC000u)
#define `$INSTANCE_NAME`_PHYADDR_POS                (5u)
#define `$INSTANCE_NAME`_PHYADDR_MASK               (`$PhyAddressMask`u)
#define `$INSTANCE_NAME`_OPCODE_POS                 (10u)
#define `$INSTANCE_NAME`_OPCODE_MASK                (0x03u)

/* Operation code */
#define `$INSTANCE_NAME`_ADDRESS                    (0x00u)
#define `$INSTANCE_NAME`_WRITE                      (0x01u)
#define `$INSTANCE_NAME`_READ                       (0x03u)
#define `$INSTANCE_NAME`_POS_READ                   (0x02u)

/* Device address (device type) */
#define `$INSTANCE_NAME`_PMA_PMD                    (0x01u)
#define `$INSTANCE_NAME`_WIS                        (0x02u)
#define `$INSTANCE_NAME`_PCS                        (0x03u)
#define `$INSTANCE_NAME`_PHY_XS                     (0x04u)
#define `$INSTANCE_NAME`_DTE_XS                     (0x05u)

#if(`$INSTANCE_NAME`_ADVANCED_MODE)

    /* Number of register spaces */
    #define `$INSTANCE_NAME`_NUMBER_OF_PAGES        (`$NumRegSpaces`u)
    /* Bitmask for register spaces */
    #define `$INSTANCE_NAME`_PAGE_MASK              (0xFFu >> (8u - `$INSTANCE_NAME`_NUMBER_OF_PAGES))

    /* Bitmap that specifies data memory type of each register space */
    #define `$INSTANCE_NAME`_PAGE_MEM_TYPE          (`$MemoryType`)
    #define `$INSTANCE_NAME`_ALL_PAGES_IN_SRAM      (`$INSTANCE_NAME`_PAGE_MASK == `$INSTANCE_NAME`_PAGE_MEM_TYPE)
    #define `$INSTANCE_NAME`_ALL_PAGES_IN_FLASH     (0u == `$INSTANCE_NAME`_PAGE_MEM_TYPE)

    /* Bitmap that specifies the config memory type of each register space */
    #define `$INSTANCE_NAME`_CFG_MEM_TYPE           (`$ConfigType`)
    #define `$INSTANCE_NAME`_ALL_CFG_IN_SRAM        (`$INSTANCE_NAME`_PAGE_MASK == `$INSTANCE_NAME`_CFG_MEM_TYPE)
    #define `$INSTANCE_NAME`_ALL_CFG_IN_FLASH       (0u == `$INSTANCE_NAME`_CFG_MEM_TYPE)

    /* Bitmap that specifies data width of each register space */
    #define `$INSTANCE_NAME`_PAGE_DATA_WIDTH        (`$DataWidth`)
    #define `$INSTANCE_NAME`_ALL_PAGES_16BIT        (`$INSTANCE_NAME`_PAGE_MASK == `$INSTANCE_NAME`_PAGE_DATA_WIDTH)
    #define `$INSTANCE_NAME`_ALL_PAGES_8BIT         (0u == `$INSTANCE_NAME`_PAGE_DATA_WIDTH)

    /* Address conversion constants */
    #define `$INSTANCE_NAME`_HI16_ADDR_MASK         (0xFFFF0000Lu)
    #define `$INSTANCE_NAME`_LO16_ADDR_MASK         (0x0000FFFFLu)
    #define `$INSTANCE_NAME`_CPU_SRAM_BASE          (0x1FFF0000Lu)
    #define `$INSTANCE_NAME`_DMA_SRAM_BASE          (0x20000000Lu)

`$RegSpaceInfo`

    /* Address analyzer DMA configuration */
    /* Register page start and end address DMAs */
    #define `$INSTANCE_NAME`_PAGE_ADDR_DMA_BYTES_PER_BURST          (2u)
    #define `$INSTANCE_NAME`_PAGE_ADDR_DMA_REQUEST_PER_BURST        (1u)
    #define `$INSTANCE_NAME`_PAGE_ADDR_DMA_TD_SIZE                  (`$INSTANCE_NAME`_NUMBER_OF_PAGES * 2u)
    #if(CY_PSOC3)
        #define `$INSTANCE_NAME`_PAGE_ADDR_DMA_CFG                  (TD_INC_SRC_ADR | TD_SWAP_EN)
        #define `$INSTANCE_NAME`_FW_DMA1_CFG                        (TD_INC_SRC_ADR | TD_INC_DST_ADR | \
                                                                        `$INSTANCE_NAME`_FwDMA1__TD_TERMOUT_EN)
    #else
        #define `$INSTANCE_NAME`_PAGE_ADDR_DMA_CFG                  (TD_INC_SRC_ADR)
        #define `$INSTANCE_NAME`_FW_DMA1_CFG                        (TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_SWAP_EN | \
                                                                        `$INSTANCE_NAME`_FwDMA1__TD_TERMOUT_EN)
    #endif /* CY_PSOC3 */

    /* Register physical memory address DMA, Write DMA, Read DMA */
    #define `$INSTANCE_NAME`_REG_MEM_DMA_BYTES_PER_BURST            (2u)
    #define `$INSTANCE_NAME`_REG_MEM_DMA_REQUEST_PER_BURST          (1u)
    #define `$INSTANCE_NAME`_REG_MEM_DMA_TD_SIZE                    (2u)
    #define `$INSTANCE_NAME`_REG_MEM_ADDR_DMA_TD_NUM                (7u)

    /* Register page info DMA */
    #define `$INSTANCE_NAME`_PAGE_INFO_DMA_BYTES_PER_BURST          (2u)
    #define `$INSTANCE_NAME`_PAGE_INFO_DMA_REQUEST_PER_BURST        (0u)
    #define `$INSTANCE_NAME`_PAGE_INFO_DMA_TD_SIZE                  (8u)

    /* Register configuration DMAs */
    #define `$INSTANCE_NAME`_CFG_DMA1_BYTES_PER_BURST               (4u)
    #define `$INSTANCE_NAME`_CFG_DMA1_REQUEST_PER_BURST             (0u)
    #define `$INSTANCE_NAME`_CFG_DMA1_TD_SIZE                       (4u)
    #define `$INSTANCE_NAME`_CFG_DMA2_BYTES_PER_BURST               (1u)
    #define `$INSTANCE_NAME`_CFG_DMA2_REQUEST_PER_BURST             (0u)
    #define `$INSTANCE_NAME`_CFG_DMA2_TD1_SIZE                      (2u)
    #define `$INSTANCE_NAME`_CFG_DMA2_TD2_SIZE                      (1u)
    #if(CY_PSOC3)
        #define `$INSTANCE_NAME`_CFG_DMA1_CFG                       (TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_SWAP_EN | \
                                                                        `$INSTANCE_NAME`_CfgDMA1__TD_TERMOUT_EN)
        #define `$INSTANCE_NAME`_CTRL_BITS_OFFSET                   (3u)
    #else
        #define `$INSTANCE_NAME`_CFG_DMA1_CFG                       (TD_INC_SRC_ADR | TD_INC_DST_ADR | \
                                                                        `$INSTANCE_NAME`_CfgDMA1__TD_TERMOUT_EN)
        #define `$INSTANCE_NAME`_CTRL_BITS_OFFSET                   (2u)
    #endif /* CY_PSOC3 */

    /* Firmware DMA */
    #define `$INSTANCE_NAME`_FW_DMA_BYTES_PER_BURST                 (2u)
    #define `$INSTANCE_NAME`_FW_DMA_REQUEST_PER_BURST               (0u)
    #define `$INSTANCE_NAME`_FW_DMA_TD_SIZE                         (2u)
    #define `$INSTANCE_NAME`_NUM_OF_8BIT_REGS                       (2u)
    #define `$INSTANCE_NAME`_NUM_OF_16BIT_REGS                      (1u)

    /* The data stored for each page contains the register space memory address
    * and the memory address of the configuration array associated with the
    * register space. The number of elements of the register page info array is
    * the number of register spaces multiply by two.
    */
    #define `$INSTANCE_NAME`_PAGE_INFO_SIZE             (`$INSTANCE_NAME`_NUMBER_OF_PAGES * 2u)

    /* Register space info size */
    #define `$INSTANCE_NAME`_PAGE_INFO_INC              (8u)

    /* Number of DMA channels */
    #define `$INSTANCE_NAME`_NUMBER_OF_CHANNELS         (10u)

    #define `$INSTANCE_NAME`_TIMEOUT_PERIOD             (255u)

#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */


/***************************************
*    Enumerated Types and Parameters
***************************************/


/***************************************
*    Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_INIT_PHYADDR           (`$PhyAddress`u)
#define `$INSTANCE_NAME`_INIT_DEVADDR           (`$DevAddress`u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define `$INSTANCE_NAME`_CONTROL_REG           (* (reg8 *) `$INSTANCE_NAME`_bMDIO_CtlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR           (  (reg8 *) `$INSTANCE_NAME`_bMDIO_CtlReg__CONTROL_REG)

/* Physical address status register */
#if(`$INSTANCE_NAME`_PHYADDR_HARDWARE)
    #define `$INSTANCE_NAME`_PHYADDR_REG       (* (reg8 *) `$INSTANCE_NAME`_bMDIO_Hardware_PhyAddr__STATUS_REG)
    #define `$INSTANCE_NAME`_PHYADDR_PTR       (  (reg8 *) `$INSTANCE_NAME`_bMDIO_Hardware_PhyAddr__STATUS_REG)
#endif /* `$INSTANCE_NAME`_PHYADDR_HARDWARE */

/* Bit counter control and period registers */
#define `$INSTANCE_NAME`_BCNT_AUX_CTL_REG      (* (reg8 *) `$INSTANCE_NAME`_bMDIO_BitCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_BCNT_AUX_CTL_PTR      (  (reg8 *) `$INSTANCE_NAME`_bMDIO_BitCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_BCNT_PERIOD_REG       (* (reg8 *) `$INSTANCE_NAME`_bMDIO_BitCounter__PERIOD_REG)
#define `$INSTANCE_NAME`_BCNT_PERIOD_PTR       (  (reg8 *) `$INSTANCE_NAME`_bMDIO_BitCounter__PERIOD_REG)

/* Physical and device address pattern register */
#if(CY_PSOC3)
    #define `$INSTANCE_NAME`_ADDR_PTRN_PTR     (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__D0_REG)
#else
    #define `$INSTANCE_NAME`_ADDR_PTRN_PTR     (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__16BIT_D0_REG)
#endif /* CY_PSOC3 */

/* The MDIO Frame processing block FIFO buffers. In the basic mode CPU reads/writes MDIO
*  Frame processing registers, therefore the proper address space should be
*  accessed.
*/
#if(`$INSTANCE_NAME`_BASIC_MODE && CY_PSOC3)
    #define `$INSTANCE_NAME`_FP_FIFO0_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__F0_REG)
    #define `$INSTANCE_NAME`_FP_FIFO1_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__F1_REG)
#else
    #define `$INSTANCE_NAME`_FP_FIFO0_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__16BIT_F0_REG)
    #define `$INSTANCE_NAME`_FP_FIFO1_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__16BIT_F1_REG)
#endif /* `$INSTANCE_NAME`_BASIC_MODE && CY_PSOC3 */

#define `$INSTANCE_NAME`_FP_AUX_CTL0_REG       (* (reg8  *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_FP_AUX_CTL1_REG       (* (reg8  *) `$INSTANCE_NAME`_bMDIO_MdioDp_u1__DP_AUX_CTL_REG)

#if(`$INSTANCE_NAME`_ADVANCED_MODE)

    /* Address Analyzer module registers */
    #define `$INSTANCE_NAME`_PAGE_START_PTR    (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u0__16BIT_F0_REG)
    #define `$INSTANCE_NAME`_PAGE_END_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u0__16BIT_F1_REG)
    #define `$INSTANCE_NAME`_REG_IDX_PTR       (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u0__16BIT_A0_REG)
    #define `$INSTANCE_NAME`_INFO_ADDR_PTR     (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__16BIT_A0_REG)
    #define `$INSTANCE_NAME`_PAGE_INFO_PTR     (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__16BIT_F0_REG)
    #define `$INSTANCE_NAME`_REG_OFFSET_PTR    (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__16BIT_A1_REG)
    #define `$INSTANCE_NAME`_REG_ADDR_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__16BIT_A0_REG)
    #define `$INSTANCE_NAME`_REG_MASK_PTR      (  (reg16 *) `$INSTANCE_NAME`_bMDIO_MdioDp_u0__D1_REG)
    #define `$INSTANCE_NAME`_REG_VAL_PTR       (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_FwAlu_u0__16BIT_A0_REG)

    #define `$INSTANCE_NAME`_REG_ATTR_REG      (* (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_CfgReg__CONTROL_REG)
    #define `$INSTANCE_NAME`_REG_ATTR_PTR      (  (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_CfgReg__CONTROL_REG)
    #define `$INSTANCE_NAME`_MEM_TYPE_REG      (* (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_MemTypeCfg__CONTROL_REG)
    #define `$INSTANCE_NAME`_MEM_TYPE_PTR      (  (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_MemTypeCfg__CONTROL_REG)
    #define `$INSTANCE_NAME`_PAGE_WIDTH_REG    (* (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_DataWidthCfg__CONTROL_REG)
    #define `$INSTANCE_NAME`_PAGE_WIDTH_PTR    (  (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_DataWidthCfg__CONTROL_REG)

    #define `$INSTANCE_NAME`_AC_AUX_CTL0_REG   (* (reg8  *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u0__DP_AUX_CTL_REG)
    #define `$INSTANCE_NAME`_AC_AUX_CTL1_REG   (* (reg8  *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u1__DP_AUX_CTL_REG)

    #if(CY_PSOC3)
        #define `$INSTANCE_NAME`_LAST_ADDR_PTR (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u0__A1_REG)
        #define `$INSTANCE_NAME`_INFO_INC_PTR  (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__D1_REG)
        #define `$INSTANCE_NAME`_INFO_BASE_PTR (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__D0_REG)
        #define `$INSTANCE_NAME`_REG_BITS_PTR  (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_FwAlu_u0__A1_REG)
    #else
        #define `$INSTANCE_NAME`_LAST_ADDR_PTR (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrComp_u0__16BIT_A1_REG)
        #define `$INSTANCE_NAME`_INFO_INC_PTR  (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__16BIT_D1_REG)
        #define `$INSTANCE_NAME`_INFO_BASE_PTR (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_AddrCalc_u0__16BIT_D0_REG)
        #define `$INSTANCE_NAME`_REG_BITS_PTR  (  (reg16 *) `$INSTANCE_NAME`_bMDIO_Advanced_FwAlu_u0__16BIT_A1_REG)
    #endif /* CY_PSOC3 */

    /* Firmware DMA status register */
    #define `$INSTANCE_NAME`_FW_DMA_STS_REG    (* (reg8 *)  `$INSTANCE_NAME`_bMDIO_Advanced_FwDmaStatus__STATUS_REG)

#endif /* `$INSTANCE_NAME`_ADVANCED_MODE */


/***************************************
*       Register Constants
***************************************/

/* Enabling and interrupt generation */
#define `$INSTANCE_NAME`_EN             (0x01u)
#define `$INSTANCE_NAME`_INT_EN         (0x02u)
#define `$INSTANCE_NAME`_TRIG_DMA       (0x04u)

/* Bit counter enabling and period */
#define `$INSTANCE_NAME`_BCNT_EN        (0x20u)
#define `$INSTANCE_NAME`_BCNT_PER       (0x1Eu)

/* FIFOs clear bit masks */
#define `$INSTANCE_NAME`_F0_CLEAR       (0x01u)
#define `$INSTANCE_NAME`_F1_CLEAR       (0x02u)
#define `$INSTANCE_NAME`_FX_CLEAR       (0x03u)

/* Firmware DMA status register masks */
#define `$INSTANCE_NAME`_FW_DMA1_MASK   (0x01u)
#define `$INSTANCE_NAME`_FW_DMA2_MASK   (0x02u)

#endif /* CY_MDIO_SLAVE_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
