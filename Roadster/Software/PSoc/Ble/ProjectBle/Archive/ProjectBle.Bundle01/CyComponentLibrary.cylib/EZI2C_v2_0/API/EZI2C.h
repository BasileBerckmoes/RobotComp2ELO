/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This is the header file for the EzI2C user module.  It contains function
*  prototypes and constants for the users convenience.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EZI2C_`$INSTANCE_NAME`_H)
#define CY_EZI2C_`$INSTANCE_NAME`_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check if required defines such as CY_PSOC5LP are available in cy_boot */
#if !defined (CY_PSOC5LP)
    #error Component `$CY_COMPONENT_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

/***************************************
*   Initial Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_DATA_RATE      (`$BusSpeed_kHz`u)
#define `$INSTANCE_NAME`_BUS_PORT       (`$I2cBusPort`u)
#define `$INSTANCE_NAME`_ENABLE_WAKEUP  (`$EnableWakeup`u)
#define `$INSTANCE_NAME`_SUBADDR_WIDTH  (`$Sub_Address_Size`u)
#define `$INSTANCE_NAME`_ADDRESSES      (`$I2C_Addresses`u)
#define `$INSTANCE_NAME`_DEFAULT_ADDR1  (`$I2C_Address1`u)
#define `$INSTANCE_NAME`_DEFAULT_ADDR2  (`$I2C_Address2`u)


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define `$INSTANCE_NAME`_WAKEUP_ENABLED (0u != `$INSTANCE_NAME`_ENABLE_WAKEUP)

/* Number of addresses enum. */
#define `$INSTANCE_NAME`_ONE_ADDRESS    (1u)
#define `$INSTANCE_NAME`_TWO_ADDRESSES  (2u)

/* Sub-address size enum. */
#define `$INSTANCE_NAME`_ANY   (0u)
#define `$INSTANCE_NAME`_I2C0  (1u)
#define `$INSTANCE_NAME`_I2C1  (2u)

/* Sub-address size enum. */
#define `$INSTANCE_NAME`_SUBADDR_8BIT   (0u)
#define `$INSTANCE_NAME`_SUBADDR_16BIT  (1u)


/***************************************
*       Type Definitions
***************************************/

/* Structure to store configuration before enter Sleep */
typedef struct
{
    uint8   enableState;
    uint8   xcfg;
    uint8   adr;
    uint8   cfg;
    uint8   clkDiv1;
    uint8   clkDiv2;

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void    `$INSTANCE_NAME`_Init(void)     `=ReentrantKeil($INSTANCE_NAME . "_Init")`;
void    `$INSTANCE_NAME`_Enable(void)   `=ReentrantKeil($INSTANCE_NAME . "_Enable")`;
void    `$INSTANCE_NAME`_Start(void)    `=ReentrantKeil($INSTANCE_NAME . "_Start")`;
void    `$INSTANCE_NAME`_Stop(void)     `=ReentrantKeil($INSTANCE_NAME . "_Stop")`;

#define `$INSTANCE_NAME`_EnableInt()        CyIntEnable      (`$INSTANCE_NAME`_ISR_NUMBER)
#define `$INSTANCE_NAME`_DisableInt()       CyIntDisable     (`$INSTANCE_NAME`_ISR_NUMBER)
#define `$INSTANCE_NAME`_ClearPendingInt()  CyIntClearPending(`$INSTANCE_NAME`_ISR_NUMBER)
#define `$INSTANCE_NAME`_SetPendingInt()    CyIntSetPending  (`$INSTANCE_NAME`_ISR_NUMBER)

void    `$INSTANCE_NAME`_Sleep(void)            `=ReentrantKeil($INSTANCE_NAME . "_Sleep")`;
void    `$INSTANCE_NAME`_Wakeup(void)           `=ReentrantKeil($INSTANCE_NAME . "_Wakeup")`;
void    `$INSTANCE_NAME`_SaveConfig(void)       `=ReentrantKeil($INSTANCE_NAME . "_SaveConfig")`;
void    `$INSTANCE_NAME`_RestoreConfig(void)    `=ReentrantKeil($INSTANCE_NAME . "_RestoreConfig")`;

uint8   `$INSTANCE_NAME`_GetActivity(void)      `=ReentrantKeil($INSTANCE_NAME . "_GetActivity")`;

void    `$INSTANCE_NAME`_SetBuffer1(uint16 bufSize, uint16 rwBoundary, volatile uint8 * dataPtr) `=ReentrantKeil($INSTANCE_NAME . "_SetBuffer1")`;
void    `$INSTANCE_NAME`_SetAddress1(uint8 address) `=ReentrantKeil($INSTANCE_NAME . "_SetAddress1")`;
uint8   `$INSTANCE_NAME`_GetAddress1(void)          `=ReentrantKeil($INSTANCE_NAME . "_GetAddress1")`;

#if (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES)
    void    `$INSTANCE_NAME`_SetBuffer2(uint16 bufSize, uint16 rwBoundary, volatile uint8 * dataPtr) `=ReentrantKeil($INSTANCE_NAME . "_SetBuffer2")`;
    void    `$INSTANCE_NAME`_SetAddress2(uint8 address )    `=ReentrantKeil($INSTANCE_NAME . "_SetAddress2")`;
    uint8   `$INSTANCE_NAME`_GetAddress2(void)              `=ReentrantKeil($INSTANCE_NAME . "_GetAddress2")`;
#endif /* (`$INSTANCE_NAME`_ADDRESSES == `$INSTANCE_NAME`_TWO_ADDRESSES) */

/* EZI2C interrupt handler */
CY_ISR_PROTO(`$INSTANCE_NAME`_ISR);
#if (`$INSTANCE_NAME`_WAKEUP_ENABLED)
    CY_ISR_PROTO(`$INSTANCE_NAME`_WAKEUP_ISR);
#endif /* (`$INSTANCE_NAME`_WAKEUP_ENABLED) */


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 `$INSTANCE_NAME`_initVar;


/***************************************
*              API Constants
***************************************/

/* Status bit definition */
#define `$INSTANCE_NAME`_STATUS_READ1   (0x01u) /* A read addr 1 operation occurred since last status check */
#define `$INSTANCE_NAME`_STATUS_WRITE1  (0x02u) /* A Write addr 1 operation occurred since last status check */
#define `$INSTANCE_NAME`_STATUS_READ2   (0x04u) /* A read addr 2 operation occurred since last status check */
#define `$INSTANCE_NAME`_STATUS_WRITE2  (0x08u) /* A Write addr 2 operation occurred since last status check */
#define `$INSTANCE_NAME`_STATUS_BUSY    (0x10u) /* A start has occurred, but a Stop has not been detected */
#define `$INSTANCE_NAME`_STATUS_RD1BUSY (0x11u) /* Addr 1 read busy  */
#define `$INSTANCE_NAME`_STATUS_WR1BUSY (0x12u) /* Addr 1 write busy */
#define `$INSTANCE_NAME`_STATUS_RD2BUSY (0x14u) /* Addr 2 read busy  */
#define `$INSTANCE_NAME`_STATUS_WR2BUSY (0x18u) /* Addr 2 write busy */
#define `$INSTANCE_NAME`_STATUS_MASK    (0x1Fu) /* Mask for status bits */
#define `$INSTANCE_NAME`_STATUS_ERR     (0x80u) /* An Error occurred since last read */

/* Data send to master in case of read overflow */
#define `$INSTANCE_NAME`_DUMMY_DATA         (0xFFu)

/* Address shift */
#define `$INSTANCE_NAME`_ADDRESS_SHIFT      (1u)
#define `$INSTANCE_NAME`_ADDRESS_LSB_SHIFT  (8u)

/* Component state enum. */
#define `$INSTANCE_NAME`_ENABLED            (0x01u)
#define `$INSTANCE_NAME`_DISABLED           (0x00u)

/* Return 1 if corresponding bit is set, otherwise 0 */
#define `$INSTANCE_NAME`_IS_BIT_SET(value, mask) (((mask) == ((value) & (mask))) ? (1u) : (0u))


/***************************************
*              Registers
***************************************/

/* I2C Extended Configuration Register */
#define `$INSTANCE_NAME`_XCFG_REG       (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__XCFG)
#define `$INSTANCE_NAME`_XCFG_PTR       ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__XCFG)

/* I2C Slave Address Register */
#define `$INSTANCE_NAME`_ADDR_REG       (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__ADR)
#define `$INSTANCE_NAME`_ADDR_PTR       ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__ADR)

/* I2C Configuration Register */
#define `$INSTANCE_NAME`_CFG_REG        (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__CFG)
#define `$INSTANCE_NAME`_CFG_PTR        ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__CFG)

/* I2C Control and Status Register */
#define `$INSTANCE_NAME`_CSR_REG        (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__CSR)
#define `$INSTANCE_NAME`_CSR_PTR        ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__CSR)

/* I2C Data Register */
#define `$INSTANCE_NAME`_DATA_REG       (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__D)
#define `$INSTANCE_NAME`_DATA_PTR       ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__D)

/*  8 LSB bits of the 10-bit Clock Divider */
#define `$INSTANCE_NAME`_CLKDIV1_REG    (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__CLK_DIV1)
#define `$INSTANCE_NAME`_CLKDIV1_PTR    ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__CLK_DIV1)

/* 2 MSB bits of the 10-bit Clock Divider */
#define `$INSTANCE_NAME`_CLKDIV2_REG    (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__CLK_DIV2)
#define `$INSTANCE_NAME`_CLKDIV2_PTR    ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__CLK_DIV2)

/* Power System Control Register 1 */
#define `$INSTANCE_NAME`_PWRSYS_CR1_REG (*(reg8 *) CYREG_PWRSYS_CR1)
#define `$INSTANCE_NAME`_PWRSYS_CR1_PTR ( (reg8 *) CYREG_PWRSYS_CR1)

/* I2C operation in Active Mode */
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__PM_ACT_CFG)
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__PM_ACT_CFG)
#define `$INSTANCE_NAME`_ACT_PWR_EN     ( (uint8)  `$INSTANCE_NAME`_I2C_Prim__PM_ACT_MSK)

/* I2C operation in Alternate Active (Standby) Mode */
#define `$INSTANCE_NAME`_PM_STBY_CFG_REG    (*(reg8 *) `$INSTANCE_NAME`_I2C_Prim__PM_STBY_CFG)
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR    ( (reg8 *) `$INSTANCE_NAME`_I2C_Prim__PM_STBY_CFG)
#define `$INSTANCE_NAME`_STBY_PWR_EN        ( (uint8)  `$INSTANCE_NAME`_I2C_Prim__PM_STBY_MSK)


/***************************************
*       Register Constants
***************************************/

/* I2C backup regulator */
#define `$INSTANCE_NAME`_PWRSYS_CR1_I2C_BACKUP  (0x04u)

/* Interrupt number and priority */
#define `$INSTANCE_NAME`_ISR_NUMBER         (`$INSTANCE_NAME`_isr__INTC_NUMBER)
#define `$INSTANCE_NAME`_ISR_PRIORITY       (`$INSTANCE_NAME`_isr__INTC_PRIOR_NUM)

/* Block reset constants */
#define `$INSTANCE_NAME`_CLEAR_REG          (0x00u)
#define `$INSTANCE_NAME`_BLOCK_RESET_DELAY  (2u)

/* XCFG I2C Extended Configuration Register */
#define `$INSTANCE_NAME`_XCFG_CLK_EN        (0x80u) /* Clock enable */
#define `$INSTANCE_NAME`_XCFG_I2C_ON        (0x40u) /* Set before entering sleep mode */
#define `$INSTANCE_NAME`_XCFG_SLEEP_READY   (0x20u) /* Ready to sleep */
#define `$INSTANCE_NAME`_XCFG_FORCE_NACK    (0x10u) /* Force nack */
#define `$INSTANCE_NAME`_XCFG_HDWR_ADDR_EN  (0x01u) /* Hardware address comparison */

/* Data I2C Slave Data Register */
#define `$INSTANCE_NAME`_SADDR_MASK         (0x7Fu)
#define `$INSTANCE_NAME`_DATA_MASK          (0xFFu)
#define `$INSTANCE_NAME`_READ_FLAG          (0x01u)

/* CFG I2C Configuration Register */
#define `$INSTANCE_NAME`_CFG_SIO_SELECT    (0x80u) /* Pin Select for SCL/SDA lines */
#define `$INSTANCE_NAME`_CFG_PSELECT       (0x40u) /* Pin Select */
#define `$INSTANCE_NAME`_CFG_BUS_ERR_IE    (0x20u) /* Bus Error Interrupt Enable */
#define `$INSTANCE_NAME`_CFG_STOP_ERR_IE   (0x10u) /* Enable Interrupt on STOP condition */
#define `$INSTANCE_NAME`_CFG_STOP_IE       (0x10u) /* Enable Interrupt on STOP condition */
#define `$INSTANCE_NAME`_CFG_CLK_RATE      (0x04u) /* Clock rate mask. 1 for 50K, 0 for 100K and 400K */
#define `$INSTANCE_NAME`_CFG_EN_SLAVE      (0x01u) /* Enable Slave operation */

/* CSR I2C Control and Status Register */
#define `$INSTANCE_NAME`_CSR_BUS_ERROR     (0x80u) /* Active high when bus error has occurred */
#define `$INSTANCE_NAME`_CSR_LOST_ARB      (0x40u) /* Set to 1 if lost arbitration in host mode */
#define `$INSTANCE_NAME`_CSR_STOP_STATUS   (0x20u) /* Set to 1 if Stop has been detected */
#define `$INSTANCE_NAME`_CSR_ACK           (0x10u) /* ACK response */
#define `$INSTANCE_NAME`_CSR_NAK           (0x00u) /* NAK response */
#define `$INSTANCE_NAME`_CSR_LRB_ACK       (0x00u) /* Last received bit was an ACK */
#define `$INSTANCE_NAME`_CSR_ADDRESS       (0x08u) /* Set in firmware 0 = status bit, 1 Address is slave */
#define `$INSTANCE_NAME`_CSR_TRANSMIT      (0x04u) /* Set in firmware 1 = transmit, 0 = receive */
#define `$INSTANCE_NAME`_CSR_LRB           (0x02u) /* Last received bit */
#define `$INSTANCE_NAME`_CSR_LRB_NAK       (0x02u) /* Last received bit was an NAK */
#define `$INSTANCE_NAME`_CSR_BYTE_COMPLETE (0x01u) /* Informs that last byte has been sent */

/* I2C state machine constants */
#define  `$INSTANCE_NAME`_SM_IDLE              (0x00u) /* Wait for Start */

/* Primary slave address states */
#define  `$INSTANCE_NAME`_SM_DEV1_WR_ADDR      (0x01u) /* Wait for sub-address */
#define  `$INSTANCE_NAME`_SM_DEV1_WR_ADDR_MSB  (0x01u) /* Wait for sub-address MSB */
#define  `$INSTANCE_NAME`_SM_DEV1_WR_ADDR_LSB  (0x02u) /* Wait for sub-address LSB */
#define  `$INSTANCE_NAME`_SM_DEV1_WR_DATA      (0x04u) /* Get data from Master */
#define  `$INSTANCE_NAME`_SM_DEV1_RD_DATA      (0x08u) /* Send data to Master */

/* Secondary slave address states */
#define  `$INSTANCE_NAME`_SM_DEV2_WR_ADDR      (0x11u) /* Wait for sub-address */
#define  `$INSTANCE_NAME`_SM_DEV2_WR_ADDR_MSB  (0x11u) /* Wait for sub-address MSB */
#define  `$INSTANCE_NAME`_SM_DEV2_WR_ADDR_LSB  (0x12u) /* Wait for sub-address LSB */
#define  `$INSTANCE_NAME`_SM_DEV2_WR_DATA      (0x14u) /* Get data from Master */
#define  `$INSTANCE_NAME`_SM_DEV2_RD_DATA      (0x18u) /* Send data to Master */


/***************************************
*    Initialization Register Settings
***************************************/

/* Oversampling rate for data date 50kpbs and less is 32, 16 for others */
#define `$INSTANCE_NAME`_OVS_32_LIM      (50u)
#define `$INSTANCE_NAME`_OVERSAMPLE_RATE ((`$INSTANCE_NAME`_DATA_RATE <= `$INSTANCE_NAME`_OVS_32_LIM) ? (32u) : (16u))

/* Return default bits depends on configuration */
#define `$INSTANCE_NAME`_DEFAULT_HDWR_ADDR  ((`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES) ? (1u) : (0u))

#define `$INSTANCE_NAME`_DEFAULT_PSELECT    ((`$INSTANCE_NAME`_ANY  != `$INSTANCE_NAME`_BUS_PORT) ? (1u) : (0u))
#define `$INSTANCE_NAME`_DEFAULT_SIO_SELECT ((`$INSTANCE_NAME`_I2C1 == `$INSTANCE_NAME`_BUS_PORT) ? (1u) : (0u))
#define `$INSTANCE_NAME`_DEFUALT_CLK_RATE   ((`$INSTANCE_NAME`_DATA_RATE <= `$INSTANCE_NAME`_OVS_32_LIM) ? (1u) : (0u))

/* Return bits within registers position */
#define `$INSTANCE_NAME`_GET_XCFG_HDWR_ADDR_EN(hwAddr) ((0u != (hwAddr)) ? (`$INSTANCE_NAME`_XCFG_HDWR_ADDR_EN) : (0u))
#define `$INSTANCE_NAME`_GET_XCFG_I2C_ON(wakeup)       ((0u != (wakeup)) ? (`$INSTANCE_NAME`_XCFG_I2C_ON) : (0u))

#define `$INSTANCE_NAME`_GET_CFG_PSELECT(pSel)      ((0u != (pSel)) ? (`$INSTANCE_NAME`_CFG_PSELECT) : (0u))
#define `$INSTANCE_NAME`_GET_CFG_SIO_SELECT(sioSel) ((0u != (sioSel)) ? (`$INSTANCE_NAME`_CFG_SIO_SELECT) : (0u))
#define `$INSTANCE_NAME`_GET_CFG_CLK_RATE(clkRate)  ((0u != (clkRate)) ? (`$INSTANCE_NAME`_CFG_CLK_RATE) : (0u))

/* Initial registers settings */
#define `$INSTANCE_NAME`_DEFAULT_CFG    (`$INSTANCE_NAME`_GET_CFG_SIO_SELECT (`$INSTANCE_NAME`_DEFAULT_SIO_SELECT) | \
                                         `$INSTANCE_NAME`_GET_CFG_PSELECT(`$INSTANCE_NAME`_DEFAULT_PSELECT)        | \
                                         `$INSTANCE_NAME`_GET_CFG_CLK_RATE(`$INSTANCE_NAME`_DEFUALT_CLK_RATE)      | \
                                         `$INSTANCE_NAME`_CFG_EN_SLAVE)

#define `$INSTANCE_NAME`_DEFAULT_XCFG   (`$INSTANCE_NAME`_GET_XCFG_HDWR_ADDR_EN(`$INSTANCE_NAME`_DEFAULT_HDWR_ADDR) | \
                                         `$INSTANCE_NAME`_GET_XCFG_I2C_ON(`$INSTANCE_NAME`_ENABLE_WAKEUP)           | \
                                         `$INSTANCE_NAME`_XCFG_CLK_EN)

#define `$INSTANCE_NAME`_DEFAULT_ADDR   (`$INSTANCE_NAME`_DEFAULT_ADDR1)

/* Divide factor calculation */
#define `$INSTANCE_NAME`_DIVIDE_FACTOR_WITH_FRACT_BYTE \
    (((uint32) BCLK__BUS_CLK__KHZ << 8u) / ((uint32) `$INSTANCE_NAME`_DATA_RATE * `$INSTANCE_NAME`_OVERSAMPLE_RATE))

#define `$INSTANCE_NAME`_DEFAULT_DIVIDE_FACTOR  (((uint32) `$INSTANCE_NAME`_DIVIDE_FACTOR_WITH_FRACT_BYTE) >> 8u)

#define `$INSTANCE_NAME`_DEFAULT_CLKDIV1    LO8(`$INSTANCE_NAME`_DEFAULT_DIVIDE_FACTOR)
#define `$INSTANCE_NAME`_DEFAULT_CLKDIV2    HI8(`$INSTANCE_NAME`_DEFAULT_DIVIDE_FACTOR)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define `$INSTANCE_NAME`_BUS_SPEED_50KHZ    (50u)
#define `$INSTANCE_NAME`_BUS_SPEED          `$INSTANCE_NAME`_DATA_RATE
#define `$INSTANCE_NAME`_OVER_SAMPLE_RATE   `$INSTANCE_NAME`_OVERSAMPLE_RATE

#define `$INSTANCE_NAME`_I2C_MASTER_MASK    (0xDDu)

#define `$INSTANCE_NAME`__ANY    `$INSTANCE_NAME`_ANY
#define `$INSTANCE_NAME`__I2C0   `$INSTANCE_NAME`_I2C0
#define `$INSTANCE_NAME`__I2C1   `$INSTANCE_NAME`_I2C1

#define `$INSTANCE_NAME`_DIVIDE_FACTOR  `$INSTANCE_NAME`_DEFAULT_DIVIDE_FACTOR

#if (`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES)
    void `$INSTANCE_NAME`_SlaveSetSleepMode(void)   `=ReentrantKeil($INSTANCE_NAME . "_SlaveSetSleepMode")`;
    void `$INSTANCE_NAME`_SlaveSetWakeMode(void)    `=ReentrantKeil($INSTANCE_NAME . "_SlaveSetWakeMode")`;
#endif /* (`$INSTANCE_NAME`_ONE_ADDRESS == `$INSTANCE_NAME`_ADDRESSES) */

#define `$INSTANCE_NAME`_State          `$INSTANCE_NAME`_curState
#define `$INSTANCE_NAME`_Status         `$INSTANCE_NAME`_curStatus
#define `$INSTANCE_NAME`_DataPtr        `$INSTANCE_NAME`_dataPtrS1

#define `$INSTANCE_NAME`_RwOffset1      `$INSTANCE_NAME`_rwOffsetS1
#define `$INSTANCE_NAME`_RwIndex1       `$INSTANCE_NAME`_rwIndexS1
#define `$INSTANCE_NAME`_WrProtect1     `$INSTANCE_NAME`_wrProtectS1
#define `$INSTANCE_NAME`_BufSize1       `$INSTANCE_NAME`_bufSizeS1

#if (`$INSTANCE_NAME`_TWO_ADDRESSES == `$INSTANCE_NAME`_ADDRESSES)
    #define `$INSTANCE_NAME`_DataPtr2   `$INSTANCE_NAME`_dataPtrS2
    #define `$INSTANCE_NAME`_Address1   `$INSTANCE_NAME`_addrS1
    #define `$INSTANCE_NAME`_Address2   `$INSTANCE_NAME`_addrS2

    #define `$INSTANCE_NAME`_RwOffset2  `$INSTANCE_NAME`_rwOffsetS2
    #define `$INSTANCE_NAME`_RwIndex2   `$INSTANCE_NAME`_rwIndexS2
    #define `$INSTANCE_NAME`_WrProtect2 `$INSTANCE_NAME`_wrProtectS2
    #define `$INSTANCE_NAME`_BufSize2   `$INSTANCE_NAME`_bufSizeS2
#endif /* (`$INSTANCE_NAME`_TWO_ADDRESSES == `$INSTANCE_NAME`_ADDRESSES) */

#endif /* CY_EZI2C_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
