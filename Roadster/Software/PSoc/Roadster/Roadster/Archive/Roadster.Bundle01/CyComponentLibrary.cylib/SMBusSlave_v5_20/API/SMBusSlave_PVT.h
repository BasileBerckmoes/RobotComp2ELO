/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the SM/PM Bus
*  Slave component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SMBusSlave_PVT_`$INSTANCE_NAME`_H)
#define CY_SMBusSlave_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_cmd.h"
#include "`$INSTANCE_NAME`_I2C_TMOUT.h"


/***************************************
*         API Constants
***************************************/

#define `$INSTANCE_NAME`_TRANS_QUEUE_SIZE           (1u)
#define `$INSTANCE_NAME`_MAX_BUFFER_SIZE            (65u)
#define `$INSTANCE_NAME`_CRC8_LUT_SIZE              (256u)

/***************************************
*       Global variables
***************************************/
    
/* I2C Buffer */
extern uint8 `$INSTANCE_NAME`_buffer[`$INSTANCE_NAME`_MAX_BUFFER_SIZE];
extern uint8 `$INSTANCE_NAME`_bufferIndex;
extern uint8 `$INSTANCE_NAME`_bufferSize;

extern volatile uint8 `$INSTANCE_NAME`_I2C_state;

/* I2C Software Address */
#if (`$INSTANCE_NAME`_SW_ADDR_DECODE)
    extern uint8 `$INSTANCE_NAME`_address;
#endif  /* (`$INSTANCE_NAME`_I2C_SW_ADRR_DECODE) */

/* Number of active manual transaction records in Transaction Queue */
extern volatile uint8 `$INSTANCE_NAME`_trActiveCount;

/* Transaction Queue */
extern `$INSTANCE_NAME`_TRANSACTION_STRUCT `$INSTANCE_NAME`_transactionData[`$INSTANCE_NAME`_TRANS_QUEUE_SIZE];

/* SMB Alert mode and Alert Response */
#if (`$INSTANCE_NAME`_SMBALERT_PIN_EXISTS)
    extern uint8 `$INSTANCE_NAME`_smbAlertMode;
    extern uint8 `$INSTANCE_NAME`_alertResponseAddress;
#endif /* `$INSTANCE_NAME`_SMBALERT_PIN_EXISTS */

#if (defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN))
    extern uint8 `$INSTANCE_NAME`_btldrStatus;
#endif /* defined(`$INSTANCE_NAME`_BTLDR_READ_EN) || defined(`$INSTANCE_NAME`_BTLDR_WRITE_EN) */

#ifdef `$INSTANCE_NAME`_BTLDR_READ_EN
    extern uint8 `$INSTANCE_NAME`_btldrReadBuf[`$INSTANCE_NAME`_MAX_BUFFER_SIZE];
#endif /* `$INSTANCE_NAME`_BTLDR_READ_EN */

#ifdef `$INSTANCE_NAME`_BTLDR_WRITE_EN
    extern uint8 `$INSTANCE_NAME`_btldrWriteBuf[`$INSTANCE_NAME`_MAX_BUFFER_SIZE];
#endif /* `$INSTANCE_NAME`_BTLDR_WRITE_EN */

/* Pre-computed CRC-8 data */
#if (`$INSTANCE_NAME`_SUPPORT_PEC)
    extern const uint8 CYCODE `$INSTANCE_NAME`_crc_table[`$INSTANCE_NAME`_CRC8_LUT_SIZE];
#endif /* `$INSTANCE_NAME`_SUPPORT_PEC */


/***************************************
*           Local Macros
***************************************/

#define `$INSTANCE_NAME`_ISR_NUMBER                 (`$INSTANCE_NAME`_I2C_ISR_NUMBER)

#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_TMOUT_ISR_NUMBER       (`$INSTANCE_NAME`_TMOUT_INT__INTC_NUMBER)
    #define `$INSTANCE_NAME`_TMOUT_ISR_PRIORITY     (`$INSTANCE_NAME`_TMOUT_INT__INTC_PRIOR_NUM)
    
    /* Enables timeout hardware and interrupt */
    #define `$INSTANCE_NAME`_Timeout_Enable()    \
        do{ \
            `$INSTANCE_NAME`_I2C_TMOUT_Enable(); \
            CyIntEnable(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER); \
        }while(0)

    /* Initializes timeout hardware and interrupt */
    #define `$INSTANCE_NAME`_Timeout_Init() \
        do{ \
            `$INSTANCE_NAME`_I2C_TMOUT_Init(); \
            CyIntDisable(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER); \
            CyIntSetPriority(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER, `$INSTANCE_NAME`_TMOUT_ISR_PRIORITY); \
        }while(0)
    
    /* Disables timeout hardware and interrupt */
    #define `$INSTANCE_NAME`_Timeout_Stop() \
        do{ \
            `$INSTANCE_NAME`_I2C_TMOUT_Stop(); \
            CyIntDisable(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER); \
            CyIntClearPending(`$INSTANCE_NAME`_TMOUT_ISR_NUMBER); \
        }while(0)

    #define `$INSTANCE_NAME`_EnableGeneralCallAddress() \
        (`$INSTANCE_NAME`_I2C_I2C_CTRL_REG &= (uint32)~`$INSTANCE_NAME`_I2C_I2C_CTRL_S_GENERAL_IGNORE)
        
    #define `$INSTANCE_NAME`_I2C_SM_SL_RD_DATA      (`$INSTANCE_NAME`_I2C_I2C_FSM_SL_RD)
#else
    #define `$INSTANCE_NAME`_TMOUT_ISR_NUMBER       (`$INSTANCE_NAME`_I2C_TMOUT_ISR_NUMBER)
#endif /* CY_PSOC4 */


/* Format conversion macro helpers */
#define `$INSTANCE_NAME`_LIN11_TO_EXP(val)              ((uint8) ((val) >> 11u))
#define `$INSTANCE_NAME`_LIN11_TO_MAN(val)              ((uint16)((val) & 0x07FFu))
#define `$INSTANCE_NAME`_EXP_TO_LIN11(val)              ((uint16)((uint16)(val) << 11u))
#define `$INSTANCE_NAME`_MAN_TO_LIN11(val)              ((uint16)((val) & 0x07FFu))
#define `$INSTANCE_NAME`_EXP_LIN11_MASK                 (0x1Fu)
#define `$INSTANCE_NAME`_LIN11_TO_EXP_SIGN(val)         ((((val) & 0x10u) != 0u) ? 1u : 0u)
#define `$INSTANCE_NAME`_LIN11_TO_MAN_SIGN(val)         ((((val) & 0x0400u) != 0u) ? 1u : 0u)
#define `$INSTANCE_NAME`_11BIT_2S_COMPLEMENT(val)       (((val) ^ 0x07FFu) + 1u)
#define `$INSTANCE_NAME`_5BIT_2S_COMPLEMENT(val)        (((val) ^ 0x1Fu) + 1u)
#define `$INSTANCE_NAME`_FLOAT_10MSB_MAN(val)           ((uint16)(((val) >> 14u) & 0x03FFu) | 0x0200u)
#define `$INSTANCE_NAME`_FLOAT_16MSB_MAN(val)           ((uint16)((val) >> 8u) | 0x8000u)
#define `$INSTANCE_NAME`_FLOAT_EXP(val)                 ((uint8)((val) >> 23u))
#define `$INSTANCE_NAME`_MAX_5BIT_EXP                   (16u)
#define `$INSTANCE_NAME`_MAX_POWER                      (65536.0f)
#define `$INSTANCE_NAME`_IEEE754_IMPLICIT_MAGNITUDE     (127)
#define `$INSTANCE_NAME`_LIN11_EXP_SCALING_FACTOR       (9)
#define `$INSTANCE_NAME`_LIN16_EXP_SCALING_FACTOR       (15)
#define `$INSTANCE_NAME`_LIN16_MAN_MAX_VAL              (0xFFFFu)
#define `$INSTANCE_NAME`_SIGN_EXTEND(val)               ((((val) & 0x10u) != 0u) ? ((val) | 0xE0u) : (val))

/* The following defines are obsolete and are no longer recommended for use */
#define `$INSTANCE_NAME`_ERR_RD_TO_MANY_BYTES          `$INSTANCE_NAME`_ERR_RD_TOO_MANY_BYTES
#define `$INSTANCE_NAME`_ERR_WR_TO_MANY_BYTES          `$INSTANCE_NAME`_ERR_WR_TOO_MANY_BYTES
#define `$INSTANCE_NAME`_ERR_WR_TO_FEW_BYTES           `$INSTANCE_NAME`_ERR_WR_TOO_FEW_BYTES
#define `$INSTANCE_NAME`_FIRMWARE_MODE                 `$INSTANCE_NAME`_MANUAL_MODE

#endif /* CY_SMBusSlave_PVT_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
