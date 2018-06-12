/*******************************************************************************
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  This file provides constants and parameter values for the SMIF component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(`$INSTANCE_NAME`_CY_SMIF_PDL_H)
#define `$INSTANCE_NAME`_CY_SMIF_PDL_H

#include "cyfitter.h"
#include "cyfitter_sysint.h"
#include "cyfitter_sysint_cfg.h"

#include "smif/cy_smif.h"
#include "smif/cy_smif_memslot.h"

#if defined(__cplusplus)
extern "C" {
#endif


/***************************************
*   Initial Parameter Constants
****************************************/

/* Interrupt cause group */
#define `$INSTANCE_NAME`_MEMORY_MODE_ALIGMENT_ERORR     (`$memoryModeAlignmentError`UL)
#define `$INSTANCE_NAME`_TX_COMMAND_FIFO_OVERFLOW       (`$txCommandFifoOverflow`UL)
#define `$INSTANCE_NAME`_TX_DATA_FIFO_OVERFLOW          (`$txDataFifoOverflow`UL)
#define `$INSTANCE_NAME`_RX_DATA_FIFO_UNDERFLOW         (`$rxDataFifoUnderflow`UL)

/* TX and RX FIFO trigger group */
#define `$INSTANCE_NAME`_RX_FIFO_TRIGEER_LEVEL          (`$rxFifoTriggerLevel`UL)
#define `$INSTANCE_NAME`_TX_FIFO_TRIGEER_LEVEL          (`$txFifoTriggerLevel`UL)

/* GPIO configuration group */
#define `$INSTANCE_NAME`_DATALINES0_1                   (`$datalines0_1`UL)
#define `$INSTANCE_NAME`_DATALINES2_3                   (`$datalines2_3`UL)
#define `$INSTANCE_NAME`_DATALINES4_5                   (`$datalines4_5`UL)
#define `$INSTANCE_NAME`_DATALINES6_7                   (`$datalines6_7`UL)
#define `$INSTANCE_NAME`_SS0                            (`$spiSelect0`UL)
#define `$INSTANCE_NAME`_SS1                            (`$spiSelect1`UL)
#define `$INSTANCE_NAME`_SS2                            (`$spiSelect2`UL)
#define `$INSTANCE_NAME`_SS3                            (`$spiSelect3`UL)

/* Advanced user: Build configuration*/
#define `$INSTANCE_NAME`_CYMEM_GEN                       (`$cymemGen`UL)

/* DMA Trigger Output */
#define `$INSTANCE_NAME`_EN_DMA_READ                       (`$enDmaRead`UL)
#define `$INSTANCE_NAME`_EN_DMA_WRITE                      (`$enDmaWrite`UL)    



/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* \{
*/

cy_en_smif_status_t `$INSTANCE_NAME`_Start(cy_stc_smif_block_config_t *blockConfig, uint32_t timeoutMs);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_Init(cy_stc_smif_block_config_t *blockConfig);
__STATIC_INLINE void                `$INSTANCE_NAME`_Mem_DeInit(void);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdWriteEnable(uint32_t slotNumber);
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdWriteDisable(uint32_t slotNumber);
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_QuadEnable(uint32_t slotNumber);
__STATIC_INLINE bool                `$INSTANCE_NAME`_Mem_IsBusy(uint32_t slotNumber);

__STATIC_INLINE bool                `$INSTANCE_NAME`_BusyCheck(void);
__STATIC_INLINE uint32_t            `$INSTANCE_NAME`_GetTxfrStatus(void);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdReadSts(uint32_t slotNumber, uint8_t *status, uint8_t command);
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdWriteSts(uint32_t slotNumber,  uint8_t command, uint8_t status);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdChipErase( uint32_t slotNumber);
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdSectorErase(uint32_t slotNumber, uint8_t const *sectorAddr);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdProgram(uint32_t slotNumber,uint8_t const *addr, 
                                                                    uint8_t *writeBuff, 
                                                                    uint32_t size, 
                                                                    cy_smif_event_cb_t CmdCmpltCb);
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdRead(uint32_t slotNumber, uint8_t const *addr, uint8_t *readBuff, 
                                                                    uint32_t size, 
                                                                    cy_smif_event_cb_t CmdCmpltCb);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Encrypt(uint32_t address, uint8_t *data, uint32_t size);

__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);

__STATIC_INLINE void              `$INSTANCE_NAME`_SetMode(cy_en_smif_mode_t mode);
__STATIC_INLINE cy_en_smif_mode_t `$INSTANCE_NAME`_GetMode(void);

__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_CacheInvalidate(cy_en_smif_cache_en_t cacheType);

__STATIC_INLINE void     `$INSTANCE_NAME`_Interrupt(void);

/***************************************
*  Internal SMIF function declarations
****************************************/
/** \cond INTERNAL */
__STATIC_INLINE void `$INSTANCE_NAME`_MemSlotConfigsInit(cy_stc_smif_mem_config_t  * const memConfigs[], 
                                                            uint32_t memConfigsSize);
/** \endcond */

/** \} group_general */


/***************************************
*         Internal Constants
***************************************/

#define `$INSTANCE_NAME`_MAX_SLOT_NUMBER    ((uint8_t)SMIF_DEVICE_NR)
#define `$INSTANCE_NAME`_BAD_SLOT_NUMBER    ((uint8_t)(`$INSTANCE_NAME`_MAX_SLOT_NUMBER + 1U))

#define `$INSTANCE_NAME`_HW                 `$INSTANCE_NAME`_SMIF__HW

#define `$INSTANCE_NAME`_MEMORIES_NUM       (`$INSTANCE_NAME`_SS0 + `$INSTANCE_NAME`_SS1 + \
                                             `$INSTANCE_NAME`_SS2 + `$INSTANCE_NAME`_SS3)

#define `$INSTANCE_NAME`_TX_FIFO_TRIGGER    (0UL)
#define `$INSTANCE_NAME`_RX_FIFO_TRIGGER    (0UL)

/**
* \addtogroup group_globals
* \{
*/
/** Allocate space for context. */
extern cy_stc_smif_context_t `$INSTANCE_NAME`_context;

/** Allocate space memory configurations. */
extern cy_stc_smif_mem_config_t* `$INSTANCE_NAME`_memSlotConfigs[`$INSTANCE_NAME`_MAX_SLOT_NUMBER];

/** Allocate space device configuration. */
extern cy_stc_smif_config_t `=$CY_CONST_CONFIG ? "const" : ""` `$INSTANCE_NAME`_config;

extern uint8_t `$INSTANCE_NAME`_initVar;

/** \} group_globals */


/**
* \addtogroup group_constants
* \{
*/
#define `$INSTANCE_NAME`_DESELECT_DELAY          (7u)            /**< Minimum duration of SPI de-selection */ 

/** 
 *  What happens when there is a Read to an empty RX FIFO or a Write to a full TX 
 *  FIFO.
 */ 
#define `$INSTANCE_NAME`_AHB_BUS_ERROR           (0u)            

/** \} group_constants */


#define `$INSTANCE_NAME`_SMIF_INTR_MASK   ( _VAL2FLD(SMIF_INTR_TR_TX_REQ, `$INSTANCE_NAME`_TX_FIFO_TRIGGER)                      |\
                                            _VAL2FLD(SMIF_INTR_TR_RX_REQ, `$INSTANCE_NAME`_RX_FIFO_TRIGGER)                      |\
                                            _VAL2FLD(SMIF_INTR_XIP_ALIGNMENT_ERROR, `$INSTANCE_NAME`_MEMORY_MODE_ALIGMENT_ERORR) |\
                                            _VAL2FLD(SMIF_INTR_TX_CMD_FIFO_OVERFLOW, `$INSTANCE_NAME`_TX_COMMAND_FIFO_OVERFLOW)  |\
                                            _VAL2FLD(SMIF_INTR_TX_DATA_FIFO_OVERFLOW, `$INSTANCE_NAME`_TX_DATA_FIFO_OVERFLOW)    |\
                                            _VAL2FLD(SMIF_INTR_RX_DATA_FIFO_UNDERFLOW, `$INSTANCE_NAME`_RX_DATA_FIFO_UNDERFLOW))     


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_Init
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_Init(cy_stc_smif_block_config_t *blockConfig)
{
    `$INSTANCE_NAME`_MemSlotConfigsInit(blockConfig->memConfig, blockConfig->memCount);
    return Cy_SMIF_Memslot_Init(`$INSTANCE_NAME`_HW , blockConfig, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_DeInit
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_DeInit() PDL driver function.
* 
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Mem_DeInit(void)
{
    Cy_SMIF_Memslot_DeInit(`$INSTANCE_NAME`_HW );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdWriteEnable
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdWriteEnable() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdWriteEnable()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdWriteEnable(uint32_t slotNumber)
{
    return Cy_SMIF_Memslot_CmdWriteEnable(`$INSTANCE_NAME`_HW, 
                `$INSTANCE_NAME`_memSlotConfigs[slotNumber], &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdWriteDisable
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdWriteDisable() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdWriteDisable()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdWriteDisable(uint32_t slotNumber)
{
    return Cy_SMIF_Memslot_CmdWriteDisable(`$INSTANCE_NAME`_HW, 
                `$INSTANCE_NAME`_memSlotConfigs[slotNumber], &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_IsBusy
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_IsBusy() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_IsBusy()  
* PDL driver function in PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_Mem_IsBusy(uint32_t slotNumber)
{
    return Cy_SMIF_Memslot_IsBusy( `$INSTANCE_NAME`_HW, 
            `$INSTANCE_NAME`_memSlotConfigs[slotNumber], &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_QuadEnable
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_QuadEnable() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_QuadEnable()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_QuadEnable(uint32_t slotNumber)
{
    return Cy_SMIF_Memslot_QuadEnable(`$INSTANCE_NAME`_HW, 
            `$INSTANCE_NAME`_memSlotConfigs[slotNumber], &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdReadSts
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdReadSts() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdReadSts()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdReadSts(uint32_t slotNumber,
                                                            uint8_t *status, 
                                                            uint8_t command)
{
    return Cy_SMIF_Memslot_CmdReadSts(`$INSTANCE_NAME`_HW, 
            `$INSTANCE_NAME`_memSlotConfigs[slotNumber], status, command, 
            &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdWriteSts
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdWriteSts() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
*  
* \note For details, see the description of the Cy_SMIF_Memslot_CmdWriteSts()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdWriteSts(uint32_t slotNumber,
                                                            uint8_t command, 
                                                            uint8_t status)
{
    return Cy_SMIF_Memslot_CmdWriteSts(`$INSTANCE_NAME`_HW,                                     
                                    `$INSTANCE_NAME`_memSlotConfigs[slotNumber], 
                                    &status,
                                    command,
                                    &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdChipErase
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdChipErase() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdChipErase()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdChipErase(uint32_t slotNumber)
{
    return Cy_SMIF_Memslot_CmdChipErase(`$INSTANCE_NAME`_HW ,
                                   `$INSTANCE_NAME`_memSlotConfigs[slotNumber],
                                    &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdSectorErase
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdSectorErase() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdSectorErase()  
* PDL driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdSectorErase(uint32_t slotNumber, 
                                                    uint8_t const *sectorAddr)
{
    return Cy_SMIF_Memslot_CmdSectorErase(`$INSTANCE_NAME`_HW ,
                                        `$INSTANCE_NAME`_memSlotConfigs[slotNumber], 
                                        sectorAddr,
                                        &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdProgram
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdProgram() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the 
* slave select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdProgram() PDL 
* driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdProgram(uint32_t slotNumber, 
                                                            uint8_t const *addr, 
                                                            uint8_t *writeBuff, 
                                                            uint32_t size, 
                                                            cy_smif_event_cb_t CmdCmpltCb)
{
    return Cy_SMIF_Memslot_CmdProgram(`$INSTANCE_NAME`_HW,                                    
                                    `$INSTANCE_NAME`_memSlotConfigs[slotNumber], 
                                    addr, 
                                    writeBuff, 
                                    size,
                                    CmdCmpltCb,
                                    &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mem_CmdRead
****************************************************************************//**
*
* Invokes the Cy_SMIF_Memslot_CmdRead() PDL driver function.
*
* \param slotNumber
* The slave device ID. This number is either 0, 1, 2, or 3. This is decided by the slave
* select line to be used while a transmit is happening.
* 
* \note For details, see the description of the Cy_SMIF_Memslot_CmdRead() PDL 
* driver function in the PDL API Reference Guide.
* 
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Mem_CmdRead(uint32_t slotNumber, 
                                                            uint8_t const *addr, 
                                                            uint8_t *readBuff, 
                                                            uint32_t size, 
                                                            cy_smif_event_cb_t CmdCmpltCb)
{
    return Cy_SMIF_Memslot_CmdRead(`$INSTANCE_NAME`_HW,                                    
                                    `$INSTANCE_NAME`_memSlotConfigs[slotNumber], 
                                    addr, 
                                    readBuff, 
                                    size,
                                    CmdCmpltCb,
                                    &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SMIF_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Interrupt(void)
{
    Cy_SMIF_Interrupt(`$INSTANCE_NAME`_HW , &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Encrypt
****************************************************************************//**
*
* Invokes the Cy_SMIF_Encrypt() PDL driver function.
* 
* \note For details, see the cryptography subsection in the Serial Memory Interface 
* (SMIF) section in the chip technical reference manual (TRM). 
*
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_Encrypt(uint32_t address,
                                                    uint8_t *data,
                                                    uint32_t size)
{
    return Cy_SMIF_Encrypt(`$INSTANCE_NAME`_HW, address, data, size,
                            &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* Invokes the Cy_SMIF_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    Cy_SMIF_Enable(`$INSTANCE_NAME`_HW, &`$INSTANCE_NAME`_context);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* Invokes the Cy_SMIF_Disable() PDL driver function. 
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    Cy_SMIF_Disable(`$INSTANCE_NAME`_HW);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetMode
****************************************************************************//**
*
* Invokes the Cy_SMIF_SetMode() PDL driver function. 
*
*******************************************************************************/
__STATIC_INLINE void     `$INSTANCE_NAME`_SetMode(cy_en_smif_mode_t mode)
{
    Cy_SMIF_SetMode(`$INSTANCE_NAME`_HW , mode);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetMode
****************************************************************************//**
*
* Invokes the SMIF_GetMode() PDL driver function. 
*
*******************************************************************************/
__STATIC_INLINE cy_en_smif_mode_t `$INSTANCE_NAME`_GetMode(void)
{
    return Cy_SMIF_GetMode(`$INSTANCE_NAME`_HW );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_BusyCheck
****************************************************************************//**
*
* Invokes the SMIF_BusyCheck() PDL driver function. 
*
*******************************************************************************/
__STATIC_INLINE bool `$INSTANCE_NAME`_BusyCheck(void)
{
    return Cy_SMIF_BusyCheck(`$INSTANCE_NAME`_HW );
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CacheInvalidate
****************************************************************************//**
*
* Invokes the SMIF_CacheInvalidate() PDL driver function. 
*
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t `$INSTANCE_NAME`_CacheInvalidate(cy_en_smif_cache_en_t cacheType)
{
    return Cy_SMIF_CacheInvalidate(`$INSTANCE_NAME`_HW , cacheType);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetTxfrStatus
****************************************************************************//**
*
* Invokes the SMIF_GetTxfrStatus() PDL driver function. 
*
*******************************************************************************/
__STATIC_INLINE uint32_t `$INSTANCE_NAME`_GetTxfrStatus(void)
{
    return Cy_SMIF_GetTxfrStatus(`$INSTANCE_NAME`_HW , &`$INSTANCE_NAME`_context);
}


/***************************************
*  Internal SMIF inline functions 
****************************************/

/** \cond INTERNAL */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_MemSlotConfigsInit
****************************************************************************//**
*
*  \internal
*  This function initializes the `$INSTANCE_NAME`_memSlotConfigs arrays with 
*  the pointers to the device memory configuration structure. The index of the 
*  `$INSTANCE_NAME`_memSlotConfigs array is equal to the device slotNumber number.     
*   
* \param memConfigs
* The configuration structure array that configures the SMIF memory device to be  
* mapped into the PSoC memory map. \ref cy_stc_smif_mem_config_t 
*
* \globalvars
*  `$INSTANCE_NAME`_memSlotConfigs The component array of the external memory 
*  configuration structures.
*
*******************************************************************************/
__STATIC_INLINE void `$INSTANCE_NAME`_MemSlotConfigsInit(cy_stc_smif_mem_config_t  * const memConfigs[], 
                                                            uint32_t memConfigsSize)
{
    uint8_t slotIndex;

    /* Initialization of _memSlotConfigs*/
    for(slotIndex = 0U; slotIndex < `$INSTANCE_NAME`_MAX_SLOT_NUMBER; slotIndex++)
    {
        `$INSTANCE_NAME`_memSlotConfigs[slotIndex] = NULL;
    }

    /* Filling of _memSlotConfigs */
    if (NULL != memConfigs)
    {
        uint8_t slotNumber = `$INSTANCE_NAME`_BAD_SLOT_NUMBER;
        for(slotIndex = 0U; slotIndex < memConfigsSize; slotIndex++)
        {
            if (NULL != memConfigs[slotIndex])
            {       
                switch ((cy_en_smif_slave_select_t)memConfigs[slotIndex]->slaveSelect)
                {
                    case CY_SMIF_SLAVE_SELECT_0:
                        slotNumber = 0U;            
                        break;
                    case CY_SMIF_SLAVE_SELECT_1:
                        slotNumber = 1U;         
                        break;
                    case CY_SMIF_SLAVE_SELECT_2:
                        slotNumber = 2U;           
                        break;
                    case CY_SMIF_SLAVE_SELECT_3:
                        slotNumber = 3U;         
                        break;
                    default:
                        /* User error: the slot number is not supported*/
                        slotNumber = `$INSTANCE_NAME`_BAD_SLOT_NUMBER;
                        break;
                }
                if (slotNumber < `$INSTANCE_NAME`_MAX_SLOT_NUMBER)
                {
                    `$INSTANCE_NAME`_memSlotConfigs[slotNumber] = memConfigs[slotIndex];
                }
            }  
        }
    }
}

/** \endcond */


#if defined(__cplusplus)
}
#endif

#endif /* `$INSTANCE_NAME`_CY_SMIF_PDL_H */


/* [] END OF FILE */
