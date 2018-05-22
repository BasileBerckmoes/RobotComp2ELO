/***************************************************************************//**
* \file `$INSTANCE_NAME`_I2C.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the SCB Component in
*  the I2C mode.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_`$INSTANCE_NAME`_H)
#define CY_SCB_I2C_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*   Initial Parameter Constants
****************************************/

#define `$INSTANCE_NAME`_I2C_MODE                   (`$I2cMode`u)
#define `$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW         (`$I2cOvsFactorLow`u)
#define `$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH        (`$I2cOvsFactorHigh`u)
#define `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE   (`$I2cMedianFilterEnable`u)
#define `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS          (`$I2cSlaveAddress`u)
#define `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS_MASK     (`$I2cSlaveAddressMask`u)
#define `$INSTANCE_NAME`_I2C_ACCEPT_ADDRESS         (`$I2cAcceptAddress`u)
#define `$INSTANCE_NAME`_I2C_ACCEPT_GENERAL_CALL    (`$I2cAcceptGeneralCall`u)
#define `$INSTANCE_NAME`_I2C_WAKE_ENABLE            (`$I2cWakeEnable`u)
#define `$INSTANCE_NAME`_I2C_DATA_RATE              (`$I2cDataRate`u)
#define `$INSTANCE_NAME`_I2C_DATA_RATE_ACTUAL       (`$ActualDataRate`u)
#define `$INSTANCE_NAME`_I2C_CLOCK_FROM_TERM        (`$I2cClockFromTerm`u)
#define `$INSTANCE_NAME`_I2C_EXTERN_INTR_HANDLER    (`$I2cExternIntrHandler`u)
#define `$INSTANCE_NAME`_I2C_BYTE_MODE_ENABLE       (`$I2cByteModeEnable`u)
#define `$INSTANCE_NAME`_I2C_MANUAL_OVS_CONTROL     (`$I2cManualOversampleControl`u)


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* I2C sub mode enum */
#define `$INSTANCE_NAME`_I2C_MODE_SLAVE              (0x01u)
#define `$INSTANCE_NAME`_I2C_MODE_MASTER             (0x02u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER       (0x06u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

#if (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Returns true if slave mode is enabled */
    #define `$INSTANCE_NAME`_I2C_SLAVE  (0u != (`$INSTANCE_NAME`_I2C_MODE_SLAVE & `$INSTANCE_NAME`_mode))

    /* Returns true if master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MASTER (0u != (`$INSTANCE_NAME`_I2C_MODE_MASTER & `$INSTANCE_NAME`_mode))

    /* Returns true if multi-master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER \
                            (0u != (`$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_MASK & `$INSTANCE_NAME`_mode))

    /* Returns true if mode is multi-master-slave */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE \
                            (`$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE == `$INSTANCE_NAME`_mode)

    /* Returns true if address accepts in RX FIFO */
    #define `$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS   (0u != `$INSTANCE_NAME`_acceptAddr)
    #define `$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL \
                (0u != (`$INSTANCE_NAME`_I2C_CTRL_REG & `$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE))

    #define `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST              (1u)
    #define `$INSTANCE_NAME`_I2C_SLAVE_CONST                    (1u)
    #define `$INSTANCE_NAME`_I2C_MASTER_CONST                   (1u)
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST       (1u)
    #define `$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS_CONST     (1u)
    #define `$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL_CONST       (1u)
    #define `$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST   (1u)

    /* Returns FIFO size */
    #if (`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1)
        #define `$INSTANCE_NAME`_I2C_FIFO_SIZE      (`$INSTANCE_NAME`_FIFO_SIZE)
    #else
        #define `$INSTANCE_NAME`_I2C_FIFO_SIZE      (`$INSTANCE_NAME`_GET_FIFO_SIZE(`$INSTANCE_NAME`_CTRL_REG & \
                                                                                    `$INSTANCE_NAME`_CTRL_BYTE_MODE))
    #endif /* (`$INSTANCE_NAME`_CY_SCBIP_V0 || `$INSTANCE_NAME`_CY_SCBIP_V1) */

#else

    /* Returns true if slave mode is enabled */
    #define `$INSTANCE_NAME`_I2C_SLAVE   (0u != (`$INSTANCE_NAME`_I2C_MODE_SLAVE & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MASTER  (0u != (`$INSTANCE_NAME`_I2C_MODE_MASTER & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if multi-master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER \
                                    (0u != (`$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_MASK & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if mode is multi-master-slave */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE \
                                    (`$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE == `$INSTANCE_NAME`_I2C_MODE)

    /* Returns true if address accepts in RX FIFO */
    #define `$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS   (0u != `$INSTANCE_NAME`_I2C_ACCEPT_ADDRESS)
    #define `$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL     (0u != `$INSTANCE_NAME`_I2C_ACCEPT_GENERAL_CALL)

    /* Returns true if wakeup on address match is enabled */
    #define `$INSTANCE_NAME`_I2C_WAKE_ENABLE_CONST  (0u != `$INSTANCE_NAME`_I2C_WAKE_ENABLE)

    #define `$INSTANCE_NAME`_I2C_SLAVE_CONST    (`$INSTANCE_NAME`_I2C_SLAVE)
    #define `$INSTANCE_NAME`_I2C_MASTER_CONST   (`$INSTANCE_NAME`_I2C_MASTER)
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE_CONST   (`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE)
    #define `$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS_CONST (`$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS)
    #define `$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL_CONST   (`$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL)
    #define `$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST   (`$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS_CONST || \
                                                                  `$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL_CONST)

    /* I2C: TX or RX FIFO size */
    #define `$INSTANCE_NAME`_I2C_FIFO_SIZE  `$INSTANCE_NAME`_GET_FIFO_SIZE(`$INSTANCE_NAME`_I2C_BYTE_MODE_ENABLE)

    /* Adjust AF and DF filter settings. Ticket ID#176179 */
    #if ((`$INSTANCE_NAME`_I2C_MODE_SLAVE == `$INSTANCE_NAME`_I2C_MODE) ||     \
            ((`$INSTANCE_NAME`_I2C_MODE_SLAVE != `$INSTANCE_NAME`_I2C_MODE) && \
             (`$INSTANCE_NAME`_I2C_DATA_RATE_ACTUAL <= `$INSTANCE_NAME`_I2C_DATA_RATE_FS_MODE_MAX)))

        #define `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE_ADJ       (0u)
        #define `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_ENABLE_ADJ    do{;}while(0)
    #else
        #define `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE_ADJ       (1u)
        #define `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_ENABLE_ADJ    `$INSTANCE_NAME`_I2C_CFG_ANALOG_FITER_DISABLE
    #endif

    /* Select oversampling factor low and high */
    #define `$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW_MIN     ((0u != `$INSTANCE_NAME`_I2C_MANUAL_OVS_CONTROL) ? \
                                                            (`$I2cOvsFactorLow`u) : (`$AutoI2cOvsFactorLow`u))

    #define `$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH_MIN    ((0u != `$INSTANCE_NAME`_I2C_MANUAL_OVS_CONTROL) ? \
                                                            (`$I2cOvsFactorHigh`u) : (`$AutoI2cOvsFactorHigh`u))

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */

#define `$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER (`$INSTANCE_NAME`_CHECK_I2C_GENERAL_CALL || \
                                                     `$INSTANCE_NAME`_CHECK_I2C_ACCEPT_ADDRESS)


/***************************************
*       Type Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
typedef struct
{
    /** Mode of operation for I2C. The following defines are available choices:
     *  - `$INSTANCE_NAME`_I2C_MODE_SLAVE
     *  - `$INSTANCE_NAME`_I2C_MODE_MASTER
     *  - `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER
     *  - `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE
    */
    uint32 mode;

    /** Oversampling factor for the low phase of the I2C clock. Ignored for
     *  Slave mode operation.  The oversampling factors need to be chosen in
     *  conjunction with the clock rate in order to generate the desired rate
     *  of I2C operation.
    */
    uint32 oversampleLow;

    /** Oversampling factor for the high phase of the I2C clock. Ignored for
     *  Slave mode operation.
    */
    uint32 oversampleHigh;

    /** This field is left for compatibility and its value is ignored.
     *  Median filter is enabled or disabled depends on the data rate and
     *  operation mode.
    */
    uint32 enableMedianFilter;

    /** 7-bit slave address. Ignored for non-slave modes.
    */
    uint32 slaveAddr;

    /** 8-bit slave address mask. Bit 0 must have a value of 0. Ignored for
     *  non-slave modes.
     *  - Bit value 0 – excludes bit from address comparison.
     *  - Bit value 1 – the bit needs to match with the corresponding bit
     *   of the device address.
    */
    uint32 slaveAddrMask;

    /** When enabled the matching address is received into the RX FIFO:
     *  0 – disable, 1 – enable.
     *
     *  The callback function has to be registered to handle the address
     *  accepted in the RX FIFO. Refer to section Accept matching address
     *  RX FIFO for more information.
    */
    uint32 acceptAddr;

    /** When enabled the matching address generates a wakeup request:
     *  0 – disable, 1 – enable. 1 – enable. Ignored for non-slave modes.
    */
    uint32 enableWake;

    /** When enabled the TX and RX FIFO depth is doubled and equal to
     *  16 bytes: 0 – disable, 1 – enable.
     *
     * Ignored for all devices other than PSoC 4100 BLE / PSoC 4200 BLE /
     * PSoC 4100M / PSoC 4200M / PSoC 4200L / PSoC 4000S / PSoC 4100S /
     * PSoC Analog Coprocessor.
    */
    uint8  enableByteMode;

    /** Data rate in kbps used while the of I2C is in operation. Valid values
      * are between 1 and 1000. Note that this filed must be initialized
      * for correct operation if Unconfigured SCB was utilized with previous
      * version of the component.
    */
    uint16 dataRate;

    /** When enabled the I2C general call address (0x00) will be accepted by
     *  the I2C hardware and trigger an interrupt: 0 – disable, 1 – enable.
     *
     *  The callback function has to be registered to handle a general call
     *  address. Refer to section Accept General Call for more information.
    */
    uint8  acceptGeneralAddr;
} `$INSTANCE_NAME`_I2C_INIT_STRUCT;
/** @} structures */

/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_i2c
* @{
*/
/* Common functions */
#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    void `$INSTANCE_NAME`_I2CInit(const `$INSTANCE_NAME`_I2C_INIT_STRUCT *config);
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */
/** @} i2c */

/**
* \addtogroup group_interrupt
* @{
*/
#if (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    void `$INSTANCE_NAME`_SetI2cAddressCustomInterruptHandler(uint32 (*func) (void));
#endif /* (`$INSTANCE_NAME`_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */
/** @} interrupt */

/**
* \addtogroup group_i2c
* @{
*/
/* I2C Master functions prototypes */
#if(`$INSTANCE_NAME`_I2C_MASTER_CONST)
    /* Read and Clear status functions */
    uint32 `$INSTANCE_NAME`_I2CMasterStatus(void);
    uint32 `$INSTANCE_NAME`_I2CMasterClearStatus(void);

    /* Interrupt based operation functions */
    uint32 `$INSTANCE_NAME`_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode);
    uint32 `$INSTANCE_NAME`_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode);
    uint32 `$INSTANCE_NAME`_I2CMasterGetReadBufSize(void);
    uint32 `$INSTANCE_NAME`_I2CMasterGetWriteBufSize(void);
    void   `$INSTANCE_NAME`_I2CMasterClearReadBuf(void);
    void   `$INSTANCE_NAME`_I2CMasterClearWriteBuf(void);

    /* Manual operation functions */
    uint32 `$INSTANCE_NAME`_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW);
    uint32 `$INSTANCE_NAME`_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW);
    uint32 `$INSTANCE_NAME`_I2CMasterSendStop(void);
    uint32 `$INSTANCE_NAME`_I2CMasterWriteByte(uint32 theByte);
    uint32 `$INSTANCE_NAME`_I2CMasterReadByte(uint32 ackNack);
#endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */

/* I2C Slave functions prototypes */
#if(`$INSTANCE_NAME`_I2C_SLAVE_CONST)
    /* Read and Clear status functions */
    uint32 `$INSTANCE_NAME`_I2CSlaveStatus(void);
    uint32 `$INSTANCE_NAME`_I2CSlaveClearReadStatus(void);
    uint32 `$INSTANCE_NAME`_I2CSlaveClearWriteStatus(void);

    /* Set Slave address and mask */
    void   `$INSTANCE_NAME`_I2CSlaveSetAddress(uint32 address);
    void   `$INSTANCE_NAME`_I2CSlaveSetAddressMask(uint32 addressMask);

    /* Interrupt based operation functions */
    void   `$INSTANCE_NAME`_I2CSlaveInitReadBuf(uint8 * rdBuf, uint32 bufSize);
    void   `$INSTANCE_NAME`_I2CSlaveInitWriteBuf(uint8 * wrBuf, uint32 bufSize);
    uint32 `$INSTANCE_NAME`_I2CSlaveGetReadBufSize(void);
    uint32 `$INSTANCE_NAME`_I2CSlaveGetWriteBufSize(void);
    void   `$INSTANCE_NAME`_I2CSlaveClearReadBuf(void);
    void   `$INSTANCE_NAME`_I2CSlaveClearWriteBuf(void);
#endif /* (`$INSTANCE_NAME`_I2C_SLAVE_CONST) */
/** @} i2c */

CY_ISR_PROTO(`$INSTANCE_NAME`_I2C_ISR);


/***************************************
*            API Constants
***************************************/

/* I2C sub mode enum */
#define `$INSTANCE_NAME`_I2C_MODE_SLAVE              (0x01u)
#define `$INSTANCE_NAME`_I2C_MODE_MASTER             (0x02u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER       (0x06u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

/* Master/Slave control constants */
#define `$INSTANCE_NAME`_I2C_WRITE_XFER_MODE    (0u)    /* Write    */
#define `$INSTANCE_NAME`_I2C_READ_XFER_MODE     (1u)    /* Read     */
#define `$INSTANCE_NAME`_I2C_ACK_ADDR           (0u)    /* Send ACK to address */
#define `$INSTANCE_NAME`_I2C_NAK_ADDR           (1u)    /* Send NAK to address */
#define `$INSTANCE_NAME`_I2C_ACK_DATA           (0u)    /* Send ACK to data */
#define `$INSTANCE_NAME`_I2C_NAK_DATA           (1u)    /* Send NAK to data */

/* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
#define `$INSTANCE_NAME`_I2C_MODE_COMPLETE_XFER     (0x00u)    /* Full transfer with Start and Stop       */
#define `$INSTANCE_NAME`_I2C_MODE_REPEAT_START      (0x01u)    /* Begin with a ReStart instead of a Start */
#define `$INSTANCE_NAME`_I2C_MODE_NO_STOP           (0x02u)    /* Complete the transfer without a Stop    */

/* Master status */
#define `$INSTANCE_NAME`_I2C_MSTAT_CLEAR            ((uint16) 0x00u)   /* Clear (init) status value */

#define `$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT         ((uint16) 0x01u)   /* Read complete               */
#define `$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT         ((uint16) 0x02u)   /* Write complete              */
#define `$INSTANCE_NAME`_I2C_MSTAT_XFER_INP         ((uint16) 0x04u)   /* Master transfer in progress */
#define `$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT        ((uint16) 0x08u)   /* Transfer is halted          */

#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_MASK         ((uint16) 0x3F0u) /* Mask for all errors                          */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_SHORT_XFER   ((uint16) 0x10u)  /* Master NAKed before end of packet            */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_ADDR_NAK     ((uint16) 0x20u)  /* Slave did not ACK                            */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_ARB_LOST     ((uint16) 0x40u)  /* Master lost arbitration during communication */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_ABORT_XFER   ((uint16) 0x80u)  /* The Slave was addressed before the Start gen */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_BUS_ERROR    ((uint16) 0x100u) /* The misplaced Start or Stop was occurred     */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER         ((uint16) 0x200u) /* Error during transfer                        */

/* Master API returns */
#define `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR          (0x00u)  /* Function complete without error                       */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST      (0x01u)  /* Master lost arbitration: INTR_MASTER_I2C_ARB_LOST     */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK        (0x02u)  /* Last Byte Naked: INTR_MASTER_I2C_NACK                 */
#define `$INSTANCE_NAME`_I2C_MSTR_NOT_READY         (0x04u)  /* Master on the bus or Slave operation is in progress   */
#define `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY          (0x08u)  /* Bus is busy, process not started                      */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_ABORT_START   (0x10u)  /* Slave was addressed before master begin Start gen     */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_BUS_ERR       (0x100u) /* Bus error has: INTR_MASTER_I2C_BUS_ERROR              */

/* Slave Status Constants */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_CMPLT         (0x01u)    /* Read transfer complete                        */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_BUSY          (0x02u)    /* Read transfer in progress                     */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_OVFL          (0x04u)    /* Read overflow: master reads above buffer size */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_ERR           (0x08u)    /* Read was interrupted by misplaced Start/Stop  */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_MASK          (0x0Fu)    /* Read Status Mask                              */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_NO_ERR        (0x00u)    /* Read no Error                                 */

#define `$INSTANCE_NAME`_I2C_SSTAT_WR_CMPLT         (0x10u)    /* Write transfer complete                         */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_BUSY          (0x20u)    /* Write transfer in progress                      */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_OVFL          (0x40u)    /* Write overflow: master writes above buffer size */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_ERR           (0x80u)    /* Write was interrupted by misplaced Start/Stop   */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_MASK          (0xF0u)    /* Write Status Mask                               */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_NO_ERR        (0x00u)    /* Write no Error                                  */

#define `$INSTANCE_NAME`_I2C_SSTAT_RD_CLEAR         (0x0Du)    /* Read Status clear: do not clear */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_CLEAR         (0xD0u)    /* Write Status Clear */

/* Internal I2C component constants */
#define `$INSTANCE_NAME`_I2C_READ_FLAG              (0x01u)     /* Read flag of the Address */
#define `$INSTANCE_NAME`_I2C_SLAVE_OVFL_RETURN      (0xFFu)     /* Return by slave when overflow */

#define `$INSTANCE_NAME`_I2C_RESET_ERROR            (0x01u)     /* Flag to re-enable SCB IP */

#define `$INSTANCE_NAME`_I2C_TX_OVERFLOW_COUNT      (`$INSTANCE_NAME`_I2C_FIFO_SIZE + 2u)


/***************************************
*     Vars with External Linkage
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const `$INSTANCE_NAME`_I2C_INIT_STRUCT `$INSTANCE_NAME`_configI2C;
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*           FSM states
***************************************/

#define `$INSTANCE_NAME`_I2C_FSM_EXIT_IDLE      (0x00u) /* Master and Slave are not active, need to exit to IDLE */

/* Slave mode FSM states */
#define `$INSTANCE_NAME`_I2C_FSM_IDLE           (0x10u) /* Idle I2C state                */
#define `$INSTANCE_NAME`_I2C_FSM_SLAVE          (0x10u) /* Slave mask for all its states */

#define `$INSTANCE_NAME`_I2C_FSM_SL_WR          (0x11u) /* Slave write states */
#define `$INSTANCE_NAME`_I2C_FSM_SL_RD          (0x12u) /* Slave read  states */

/* Master mode FSM states */
#define `$INSTANCE_NAME`_I2C_FSM_MASTER         (0x20u) /* Master mask for all its states */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_ADDR      (0x08u) /* Master address phase           */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_DATA      (0x04u) /* Master data phase              */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_RD        (0x01u) /* Master read phase              */

#define `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_ADDR   (0x28u) /* FSM master transmit address with write          */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_ADDR   (0x29u) /* FSM master transmit address with read           */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA   (0x24u) /* FSM master writes data into the slave           */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA   (0x25u) /* FSM master reads data from the slave            */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT      (0x60u) /* FSM master halt state: wait for Stop or ReStart */

/* Requests to complete any on-going transfer */
#define `$INSTANCE_NAME`_I2C_CMPLT_ANY_TRANSFER     (0x01u)

/* Returns true if FSM is in any Master state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER   (0u != (`$INSTANCE_NAME`_I2C_FSM_MASTER & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in any Slave state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_SLAVE    (0u != (`$INSTANCE_NAME`_I2C_FSM_SLAVE  & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in Master send address state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_ADDR (0u != (`$INSTANCE_NAME`_I2C_FSM_MSTR_ADDR & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in Master send or receive data state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_DATA (0u != (`$INSTANCE_NAME`_I2C_FSM_MSTR_DATA  & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in any of read states: applied for Slave and Master */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_RD   (0u != (`$INSTANCE_NAME`_I2C_FSM_MSTR_RD  & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in IDLE state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE (`$INSTANCE_NAME`_I2C_FSM_IDLE == `$INSTANCE_NAME`_state)

/* Returns true if FSM is HALT state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_HALT (`$INSTANCE_NAME`_I2C_FSM_MSTR_HALT == `$INSTANCE_NAME`_state)

/* Set Master read or write completion depends on state */
#define `$INSTANCE_NAME`_GET_I2C_MSTAT_CMPLT (`$INSTANCE_NAME`_CHECK_I2C_FSM_RD ?           \
                                                    (`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT) : \
                                                    (`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT))


/***************************************
*       Macro Definitions
***************************************/

/* Returns TRUE if sourceMask is set in `$INSTANCE_NAME`_I2C_MASTER_CMD_REG: used to check if Start was generated */
#define `$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(sourceMask)   (0u != (`$INSTANCE_NAME`_I2C_MASTER_CMD_REG & (sourceMask)))

/* Returns TRUE if `$INSTANCE_NAME`_MODE_NO_STOP is set in `$INSTANCE_NAME`_mstrControl: detects NoStop condition */
#define `$INSTANCE_NAME`_CHECK_I2C_MODE_NO_STOP(mode)   (0u != (`$INSTANCE_NAME`_I2C_MODE_NO_STOP & (mode)))

/* Returns TRUE if `$INSTANCE_NAME`_MODE_REPEAT_START is set: used to detect when generate ReStart condition */
#define `$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode)   (0u != (`$INSTANCE_NAME`_I2C_MODE_REPEAT_START  & (mode)))

/* Returns TRUE if `$INSTANCE_NAME`_state is in one of master states */
#define `$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE    (`$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER)


/***************************************
*      Common Register Settings
***************************************/

#define `$INSTANCE_NAME`_CTRL_I2C       (`$INSTANCE_NAME`_CTRL_MODE_I2C)

#define `$INSTANCE_NAME`_I2C_CTRL       (`$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE)

#define `$INSTANCE_NAME`_I2C_RX_CTRL    ((`$INSTANCE_NAME`_ONE_BYTE_WIDTH - 1u) | \
                                          `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST    | \
                                          `$INSTANCE_NAME`_RX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_I2C_TX_CTRL    ((`$INSTANCE_NAME`_ONE_BYTE_WIDTH - 1u) | \
                                         `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST     | \
                                         `$INSTANCE_NAME`_TX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_I2C_INTR_SLAVE_MASK    (`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK       | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR  | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST)

#define `$INSTANCE_NAME`_I2C_INTR_MASTER_MASK   (`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST | \
                                                 `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     | \
                                                 `$INSTANCE_NAME`_INTR_MASTER_I2C_STOP     | \
                                                 `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR)

/* Calculates tLOW in uS units */
#define `$INSTANCE_NAME`_I2C_TLOW_TIME  ((1000u / `$INSTANCE_NAME`_I2C_DATA_RATE) + \
                                            ((0u != (1000u % `$INSTANCE_NAME`_I2C_DATA_RATE)) ? (1u) : (0u)))
/* tHIGH = tLOW */
#define `$INSTANCE_NAME`_I2C_THIGH_TIME (`$INSTANCE_NAME`_I2C_TLOW_TIME)

#define `$INSTANCE_NAME`_I2C_SCL_LOW    (0u)
#define `$INSTANCE_NAME`_I2C_SCL_HIGH   (1u)

#define `$INSTANCE_NAME`_I2C_IGNORE_GENERAL_CALL    ((uint32) (0u == `$INSTANCE_NAME`_I2C_ACCEPT_GENERAL_CALL))


/***************************************
*    Initialization Register Settings
***************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)

    #if (!`$INSTANCE_NAME`_CY_SCBIP_V0)
        #define `$INSTANCE_NAME`_I2C_WAKE_ENABLE_ADJ    (`$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE ? \
                                                            (0u) : (`$INSTANCE_NAME`_I2C_WAKE_ENABLE))
    #else
        #define `$INSTANCE_NAME`_I2C_WAKE_ENABLE_ADJ    (`$INSTANCE_NAME`_I2C_WAKE_ENABLE)
    #endif /* (!`$INSTANCE_NAME`_CY_SCBIP_V0) */

    #define `$INSTANCE_NAME`_I2C_MODE_MASKED    (`$INSTANCE_NAME`_I2C_MODE & \
                                                (`$INSTANCE_NAME`_I2C_MODE_SLAVE | `$INSTANCE_NAME`_I2C_MODE_MASTER))

    #define `$INSTANCE_NAME`_I2C_DEFAULT_CTRL \
                                (`$INSTANCE_NAME`_GET_CTRL_BYTE_MODE  (`$INSTANCE_NAME`_I2C_BYTE_MODE_ENABLE) | \
                                 `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(`$INSTANCE_NAME`_I2C_ACCEPT_ADDRESS)   | \
                                 `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE (`$INSTANCE_NAME`_I2C_WAKE_ENABLE_ADJ))

    #define `$INSTANCE_NAME`_I2C_DEFAULT_I2C_CTRL \
                    (`$INSTANCE_NAME`_GET_I2C_CTRL_HIGH_PHASE_OVS(`$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH_MIN)   | \
                     `$INSTANCE_NAME`_GET_I2C_CTRL_LOW_PHASE_OVS (`$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW_MIN)    | \
                     `$INSTANCE_NAME`_GET_I2C_CTRL_S_GENERAL_IGNORE(`$INSTANCE_NAME`_I2C_IGNORE_GENERAL_CALL) | \
                     `$INSTANCE_NAME`_GET_I2C_CTRL_SL_MSTR_MODE  (`$INSTANCE_NAME`_I2C_MODE_MASKED))

    #define `$INSTANCE_NAME`_I2C_DEFAULT_RX_MATCH ((`$INSTANCE_NAME`_I2C_SLAVE) ? \
                                (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(`$INSTANCE_NAME`_I2C_SLAVE_ADDRESS) | \
                                 `$INSTANCE_NAME`_GET_RX_MATCH_MASK   (`$INSTANCE_NAME`_I2C_SLAVE_ADDRESS_MASK)) : (0u))

    #define `$INSTANCE_NAME`_I2C_DEFAULT_RX_CTRL \
                                (`$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(`$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE_ADJ) | \
                                 `$INSTANCE_NAME`_I2C_RX_CTRL)

    #define `$INSTANCE_NAME`_I2C_DEFAULT_TX_CTRL  (`$INSTANCE_NAME`_I2C_TX_CTRL)

    #define `$INSTANCE_NAME`_I2C_DEFAULT_RX_FIFO_CTRL (0u)
    #define `$INSTANCE_NAME`_I2C_DEFAULT_TX_FIFO_CTRL (0u)

    /* Interrupt sources */
    #define `$INSTANCE_NAME`_I2C_DEFAULT_INTR_I2C_EC_MASK   (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_I2C_DEFAULT_INTR_SPI_EC_MASK   (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_I2C_DEFAULT_INTR_RX_MASK       (`$INSTANCE_NAME`_NO_INTR_SOURCES)
    #define `$INSTANCE_NAME`_I2C_DEFAULT_INTR_TX_MASK       (`$INSTANCE_NAME`_NO_INTR_SOURCES)

    #define `$INSTANCE_NAME`_I2C_DEFAULT_INTR_SLAVE_MASK    ((`$INSTANCE_NAME`_I2C_SLAVE) ? \
                (`$INSTANCE_NAME`_I2C_INTR_SLAVE_MASK | \
                 `$INSTANCE_NAME`_GET_INTR_SLAVE_I2C_GENERAL(`$INSTANCE_NAME`_I2C_ACCEPT_GENERAL_CALL)) : (0u))

    #define `$INSTANCE_NAME`_I2C_DEFAULT_INTR_MASTER_MASK   ((`$INSTANCE_NAME`_I2C_MASTER) ? \
                                                                (`$INSTANCE_NAME`_I2C_INTR_MASTER_MASK) : (0u))

#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

#endif /* (CY_SCB_I2C_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
