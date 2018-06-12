/****************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*   Provides an API for the Bootloader. The API includes functions for starting
*   bootloading operations, validating the application and jumping to the
*   application.
*
********************************************************************************
* \copyright
* Copyright 2008-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOTLOADER_`$INSTANCE_NAME`_H)
#define CY_BOOTLOADER_`$INSTANCE_NAME`_H

#include "cytypes.h"
#include "CyFlash.h"

#define `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER        (`$multiAppBootloader`u)
#define `$INSTANCE_NAME`_BOOTLOADER_APP_VERSION     (`$bootloaderAppVersion`u)
#define `$INSTANCE_NAME`_FAST_APP_VALIDATION        (`$fastAppValidation`u)
#define `$INSTANCE_NAME`_PACKET_CHECKSUM_CRC        (`$packetChecksumCrc`u)
#define `$INSTANCE_NAME`_WAIT_FOR_COMMAND           (`$waitForCommand`u)
#define `$INSTANCE_NAME`_WAIT_FOR_COMMAND_TIME      (`$waitForCommandTime`u)
#define `$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION  (`$bootloaderAppValidation`u)

#define `$INSTANCE_NAME`_CMD_GET_FLASH_SIZE_AVAIL   (`$cmdGetFlashSizeAvail`u)
#define `$INSTANCE_NAME`_CMD_ERASE_ROW_AVAIL        (`$cmdEraseRowAvail`u)
#define `$INSTANCE_NAME`_CMD_GET_ROW_CHKSUM_AVAIL   (`$cmdVerifyRowAvail`u)
#define `$INSTANCE_NAME`_CMD_SYNC_BOOTLOADER_AVAIL  (`$cmdSyncBootloaderAvail`u)
#define `$INSTANCE_NAME`_CMD_SEND_DATA_AVAIL        (`$cmdSendDataAvail`u)
#define `$INSTANCE_NAME`_CMD_VERIFY_APP_CHKSUM_AVAIL (`$cmdVerifyAppChksumAvail`u)
#define `$INSTANCE_NAME`_CMD_GET_METADATA           (`$cmdGetMetadataAvail`u)
#define `$INSTANCE_NAME`_CMD_VERIFY_FLS_ROW_AVAIL   (`$cmdVerifyRowInFlashAvail`u)
#define `$INSTANCE_NAME`_GOLDEN_IMAGE_AVAIL         (`$goldenImageSupportAvail`u)
#define `$INSTANCE_NAME`_SECURITY_KEY_AVAIL         (`$securityKeyAvail`u)
#define `$INSTANCE_NAME`_AUTO_SWITCHING_AVAIL       (`$autoAppSwitchingAvail`u)

#if ((0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)) 
    #define `$INSTANCE_NAME`_CMD_GET_APP_STATUS_AVAIL   (`$cmdGetAppStatusAvail`u)
#endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) ||
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/

#if (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER)
    #define `$INSTANCE_NAME`_COPIER_AVAIL           (`$copier`u)
#endif /*(CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER)*/

#if (0u != `$INSTANCE_NAME`_SECURITY_KEY_AVAIL) 
    #define `$INSTANCE_NAME`_SECURITY_KEY_LENGTH        (`$securityKeyLength`u)
#endif    /*(0u != `$INSTANCE_NAME`_SECURITY_KEY_AVAIL)*/

/*******************************************************************************
* Copier definitions
*******************************************************************************/
#if (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER)
    #if (0u != `$INSTANCE_NAME`_COPIER_AVAIL)
    /**************************************************************************** 
    * Defines how many times Copier will try to copy the new app#0 image from
    * the temporary location to app#0 flash space (if it was not successful 
    * the first time) before giving up.
    ****************************************************************************/    
    #define `$INSTANCE_NAME`_MAX_ATTEMPTS      (3u)
    #endif /* (0u != `$INSTANCE_NAME`_COPIER_AVAIL) */
#endif /* (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER) */

#if ((CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LAUNCHER) && (!CY_PSOC3))
/*******************************************************************************
* Callback definitions
*******************************************************************************/   
/**
 \defgroup structures_group Structures
 @{
*/           
typedef struct 
{
    uint8 command;
    uint16 packetLength;
    uint8* pInputBuffer;
} `$INSTANCE_NAME`_in_packet_type;

typedef struct 
{
    cystatus status;
    uint16 packetLength;
    uint8* pOutputBuffer;
} `$INSTANCE_NAME`_out_packet_type;

/** @}*/

typedef void (*`$INSTANCE_NAME`_callback_type)(`$INSTANCE_NAME`_in_packet_type* inputPacket, 
                                               `$INSTANCE_NAME`_out_packet_type* outputPacket);

void `$INSTANCE_NAME`_InitCallback(`$INSTANCE_NAME`_callback_type userCallback) \
           CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_InitCallback")`;
#endif /* (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LAUNCHER) && (!CY_PSOC3) */
           
/*******************************************************************************
* Bootloadable applications identification
*******************************************************************************/
#define `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_0          (0x00u)

#if ((0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_1      (0x01u)
    #define `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_NONE   (0x02u)

    #if (1u == `$INSTANCE_NAME`_GOLDEN_IMAGE_AVAIL)
        #define `$INSTANCE_NAME`_GOLDEN_IMAGE           (0x00u)
    #endif /*(1u == `$INSTANCE_NAME`_GOLDEN_IMAGE_AVAIL)*/
#endif  /* (0u != Bootloader_DUAL_APP_BOOTLOADER) || 
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) */


/* Mask used to indicate starting application */
#define `$INSTANCE_NAME`_SCHEDULE_BTLDB             (0x80u)
#define `$INSTANCE_NAME`_SCHEDULE_BTLDR             (0x40u)
#define `$INSTANCE_NAME`_SCHEDULE_MASK              (0xC0u)
#define `$INSTANCE_NAME`_SCHEDULE_BTLDR_INIT_STATE  (0x00u)

#if (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)
#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader")))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */
extern const uint8  CYCODE `$INSTANCE_NAME`_Checksum;
extern const uint8  CYCODE  *`$INSTANCE_NAME`_ChecksumAccess;


#if defined(__ARMCC_VERSION) || defined (__GNUC__)
    __attribute__((section (".bootloader")))
#elif defined (__ICCARM__)
    #pragma location=".bootloader"
#endif  /* defined(__ARMCC_VERSION) || defined (__GNUC__) */
extern const uint32 CYCODE `$INSTANCE_NAME`_SizeBytes;
extern const uint32 CYCODE *`$INSTANCE_NAME`_SizeBytesAccess;
#endif /*CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER*/

#if (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) 
extern uint8 `$INSTANCE_NAME`_initVar;
extern uint8 `$INSTANCE_NAME`_runningApp;
extern uint8 `$INSTANCE_NAME`_isBootloading;
#endif /*CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER*/

#if ((CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER) && (CY_PSOC4))
    extern void `$INSTANCE_NAME`_UserCopierCallback(void);
    #define `$INSTANCE_NAME`_USER_COPIER_CALLBACK `$INSTANCE_NAME`_UserCopierCallback()
#endif /* (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LAUNCHER) && (CY_PSOC4) */

/*******************************************************************************
* This variable is used by the Bootloader/Bootloadable components to schedule which
* application will be started after a software reset.
*******************************************************************************/
#if (CY_PSOC4)
    #if defined(__ARMCC_VERSION)
        __attribute__ ((section(".bootloaderruntype"), zero_init))
    #elif defined (__GNUC__)
        __attribute__ ((section(".bootloaderruntype")))
   #elif defined (__ICCARM__)
        #pragma location=".bootloaderruntype"
    #endif  /* defined(__ARMCC_VERSION) */
    extern volatile uint32 cyBtldrRunType;
#endif  /* (CY_PSOC4) */


#if ((0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    extern volatile uint8 `$INSTANCE_NAME`_activeApp;
#endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) ||
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/


#if(CY_PSOC4)
    /* Reset Cause Observation Register */
    #define `$INSTANCE_NAME`_RES_CAUSE_REG           (* (reg32 *) CYREG_RES_CAUSE)
    #define `$INSTANCE_NAME`_RES_CAUSE_PTR           (  (reg32 *) CYREG_RES_CAUSE)
#else
    #define `$INSTANCE_NAME`_RESET_SR0_REG           (* (reg8 *) CYREG_RESET_SR0)
    #define `$INSTANCE_NAME`_RESET_SR0_PTR           (  (reg8 *) CYREG_RESET_SR0)
#endif /* (CY_PSOC4) */


/*******************************************************************************
* Get the reason for a device reset
*  Return cyBtldrRunType in the case if a software reset was the reset reason and
*  set cyBtldrRunType to zero (the Bootloader application is scheduled - that is
*  the initial clean state) and return zero.
*******************************************************************************/
#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_GET_RUN_TYPE           (cyBtldrRunType)
#else
    #define `$INSTANCE_NAME`_GET_RUN_TYPE       (`$INSTANCE_NAME`_RESET_SR0_REG & `$INSTANCE_NAME`_SCHEDULE_MASK)
#endif  /* (CY_PSOC4) */


/*******************************************************************************
* Schedule Bootloader/Bootloadable to be run after a software reset
*******************************************************************************/
#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)                (cyBtldrRunType = (x))
#else
    #define `$INSTANCE_NAME`_SET_RUN_TYPE(x)                (`$INSTANCE_NAME`_RESET_SR0_REG = (x))
#endif  /* (CY_PSOC4) */


/* Returns number of flash arrays available in device. */
#ifndef CY_FLASH_NUMBER_ARRAYS
    #define CY_FLASH_NUMBER_ARRAYS                  (CYDEV_FLASH_SIZE / CYDEV_FLS_SECTOR_SIZE)
#endif /* CY_FLASH_NUMBER_ARRAYS */


/*******************************************************************************
* External References
*******************************************************************************/
/**
 \defgroup functions_group Functions
 @{
*/
#if (CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)
    void CyBtldr_CheckLaunch(void)  CYSMALL `=ReentrantKeil("CyBtldr_CheckLaunch")`;
#endif /*CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER*/

void `$INSTANCE_NAME`_SetFlashByte(uint32 address, uint8 runType)`=ReentrantKeil("`$INSTANCE_NAME`_SetFlashByte")`;
void `$INSTANCE_NAME`_Start(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Start")`;
cystatus `$INSTANCE_NAME`_ValidateBootloadable(uint8 appId) \
            CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_ValidateBootloadable")`;
uint8 `$INSTANCE_NAME`_Calc8BitSum(uint32 baseAddr, uint32 start, uint32 size) CYSMALL \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_Calc8BitFlashSum")`;
uint32   `$INSTANCE_NAME`_GetMetadata(uint8 field, uint8 appId) \
                                    `=ReentrantKeil("`$INSTANCE_NAME`_GetMetadata")`;
void `$INSTANCE_NAME`_Exit(uint8 appId) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Exit")`;

#if (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)
    void `$INSTANCE_NAME`_HostLink(uint8 timeOut) CYLARGE `=ReentrantKeil("`$INSTANCE_NAME`_HostLink")`;    
    void `$INSTANCE_NAME`_Initialize(void)  CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_Initialize")`;
    uint8 `$INSTANCE_NAME`_GetRunningAppStatus(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_GetRunningAppStatus")`;
    uint8 `$INSTANCE_NAME`_GetActiveAppStatus(void) CYSMALL `=ReentrantKeil("`$INSTANCE_NAME`_GetActiveAppStatus")`;
#endif /*(CYDEV_PROJ_TYPE != CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/
/** @} */

#if(CY_PSOC3)
    /* Implementation for PSoC 3 resides in `$INSTANCE_NAME`_psoc3.a51 file.  */
    void     `$INSTANCE_NAME`_LaunchBootloadable(uint32 appAddr);
#endif  /* (CY_PSOC3) */

/* When using a custom interface as the IO Component, the user must provide these functions */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)
#if ((CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) || (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_BOOTLOADER) || \
     (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER)) 
    extern void CyBtldrCommStart(void);
    extern void CyBtldrCommStop (void);
    extern void CyBtldrCommReset(void);
    extern cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeOut);
    extern cystatus CyBtldrCommRead (uint8* buffer, uint16 size, uint16* count, uint8 timeOut);
#endif /*(CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER) || (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_BOOTLOADER) || \
         (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER)*/
#endif  /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface) */

/*******************************************************************************
* `$INSTANCE_NAME`_Initialize()
*******************************************************************************/
#define `$INSTANCE_NAME`_BOTH_ACTIVE                (0x03u)

/**
 \defgroup constants_group Constants
 @{
*/

/** \addtogroup group_metadataFields Metadata Fields
 *  Metadata fields description 
 *  @{
 */
/*******************************************************************************
* `$INSTANCE_NAME`_GetMetadata()
*******************************************************************************/
#define `$INSTANCE_NAME`_GET_BTLDB_CHECKSUM         (1u)   /**< Bootloadable Application Checksum */
#define `$INSTANCE_NAME`_GET_BTLDB_ADDR             (2u)   /**< Bootloadable Application Start Routine Address */
#define `$INSTANCE_NAME`_GET_BTLDR_LAST_ROW         (3u)   /**< Bootloader Last Flash Row */
#define `$INSTANCE_NAME`_GET_BTLDB_LENGTH           (4u)   /**< Bootloadable Application Length */
#define `$INSTANCE_NAME`_GET_BTLDB_ACTIVE           (5u)   /**< Active Bootloadable Application */
#define `$INSTANCE_NAME`_GET_BTLDB_STATUS           (6u)   /**< Bootloadable Application Verification Status */
#define `$INSTANCE_NAME`_GET_BTLDR_APP_VERSION      (7u)   /**< Bootloader Application Version */
#define `$INSTANCE_NAME`_GET_BTLDB_APP_VERSION      (8u)   /**< Bootloadable Application Version */
#define `$INSTANCE_NAME`_GET_BTLDB_APP_ID           (9u)   /**< Bootloadable Application ID */
#define `$INSTANCE_NAME`_GET_BTLDB_APP_CUST_ID      (10u)  /**< Bootloadable Application Custom ID */
#define `$INSTANCE_NAME`_GET_BTLDB_COPY_FLAG        (11u)  /**< "need-to-copy flag */
#define `$INSTANCE_NAME`_GET_BTLDB_USER_DATA        (12u)  /**< User data */

/** @} group_metadataFields */
/** @} constants_group */

#define `$INSTANCE_NAME`_GET_METADATA_RESPONSE_SIZE (56u)  

/*******************************************************************************
* `$INSTANCE_NAME`_Exit()
*******************************************************************************/
#define `$INSTANCE_NAME`_EXIT_TO_BTLDR              (2u)
#define `$INSTANCE_NAME`_EXIT_TO_BTLDB              (0u)
#if ((0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) || \
    (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define `$INSTANCE_NAME`_EXIT_TO_BTLDB_1        (0u)
    #define `$INSTANCE_NAME`_EXIT_TO_BTLDB_2        (1u)
#endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) ||
           (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/

#if (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)
/*******************************************************************************
* In-app Bootloader definitions
*******************************************************************************/
#define `$INSTANCE_NAME`_BOOTLOADING_IN_PROGRESS     (1u)
#define `$INSTANCE_NAME`_BOOTLOADING_COMPLETED       (0u)

#define `$INSTANCE_NAME`_BOOTLADING_INITIALIZED      (1u)
#define `$INSTANCE_NAME`_BOOTLOADING_NOT_INITIALIZED (0u)

#define `$INSTANCE_NAME`_RUNNING_APPLICATION_0       (0u)     
#define `$INSTANCE_NAME`_RUNNING_APPLICATION_1       (1u)     
#define `$INSTANCE_NAME`_RUNNING_APPLICATION_UNKNOWN (2u)     
#endif /*CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER*/    


/*******************************************************************************
* Input/output packet defines
*******************************************************************************/
#define `$INSTANCE_NAME`_MIN_PKT_SIZE             (7u)   /* The minimum number of bytes in a packet */
#define `$INSTANCE_NAME`_SIZEOF_COMMAND_BUFFER    (300u) /* Maximum number of bytes accepted in one packet plus some */

/*******************************************************************************
* Kept for backward compatibility.
*******************************************************************************/
#if ((0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) || (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER))
    #define `$INSTANCE_NAME`_ValidateApp(x)                 `$INSTANCE_NAME`_ValidateBootloadable((x))
    #define `$INSTANCE_NAME`_ValidateApplication()            \
                            `$INSTANCE_NAME`_ValidateBootloadable(`$INSTANCE_NAME`_MD_BTLDB_ACTIVE_0)
#else
    #define `$INSTANCE_NAME`_ValidateApplication()            \
                            `$INSTANCE_NAME`_ValidateBootloadable(`$INSTANCE_NAME`_MD_BTLDB_ACTIVE_0)
    #define `$INSTANCE_NAME`_ValidateApp(x)                 `$INSTANCE_NAME`_ValidateBootloadable((x))
#endif  /* (0u != `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) || (CYDEV_PROJ_TYPE == CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER)*/
#define `$INSTANCE_NAME`_Calc8BitFlashSum(start, size)      `$INSTANCE_NAME`_Calc8BitSum(CY_FLASH_BASE, (start), (size))


/*******************************************************************************
* The following code is DEPRECATED and must not be used.
*******************************************************************************/
#define `$INSTANCE_NAME`_CMD_VERIFY_ROW_AVAIL           `$INSTANCE_NAME`_CMD_GET_ROW_CHKSUM_AVAIL

#define `$INSTANCE_NAME`_BOOTLOADABLE_APP_VALID         (`$INSTANCE_NAME`_BOOTLOADER_APP_VALIDATION)
#define CyBtldr_Start                                    `$INSTANCE_NAME`_Start

#define `$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS            (CYDEV_FLASH_SIZE / CYDEV_FLS_SECTOR_SIZE)
#define `$INSTANCE_NAME`_META_BASE(x)                   (CYDEV_FLASH_BASE + \
                                                            (CYDEV_FLASH_SIZE - (( uint32 )(x) * CYDEV_FLS_ROW_SIZE) - \
                                                            `$INSTANCE_NAME`_META_DATA_SIZE))
#define `$INSTANCE_NAME`_META_ARRAY                     (`$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS - 1u)
#define `$INSTANCE_NAME`_META_APP_ENTRY_POINT_ADDR(x)   (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_ADDR_OFFSET)
#define `$INSTANCE_NAME`_META_APP_BYTE_LEN(x)           (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET)
#define `$INSTANCE_NAME`_META_APP_RUN_ADDR(x)           (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET)
#define `$INSTANCE_NAME`_META_APP_ACTIVE_ADDR(x)        (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_ACTIVE_OFFSET)
#define `$INSTANCE_NAME`_META_APP_VERIFIED_ADDR(x)      (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_VERIFIED_OFFSET)
#define `$INSTANCE_NAME`_META_APP_BLDBL_VER_ADDR(x)     (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_BL_BUILD_VER_OFFSET)
#define `$INSTANCE_NAME`_META_APP_VER_ADDR(x)           (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_VER_OFFSET)
#define `$INSTANCE_NAME`_META_APP_ID_ADDR(x)            (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_ID_OFFSET)
#define `$INSTANCE_NAME`_META_APP_CUST_ID_ADDR(x)       (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_CUST_ID_OFFSET)
#define `$INSTANCE_NAME`_META_LAST_BLDR_ROW_ADDR(x)     (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET)
#define `$INSTANCE_NAME`_META_CHECKSUM_ADDR(x)          (`$INSTANCE_NAME`_META_BASE(x) + \
                                                            `$INSTANCE_NAME`_META_APP_CHECKSUM_OFFSET)
#if(0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER)
    #define `$INSTANCE_NAME`_MD_BASE                    `$INSTANCE_NAME`_META_BASE(0u)

    #if(!CY_PSOC4)
        #define `$INSTANCE_NAME`_MD_ROW                 ((CY_FLASH_NUMBER_ROWS / `$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS) \
                                                        - 1u)
    #else
        #define `$INSTANCE_NAME`_MD_ROW                 (CY_FLASH_NUMBER_ROWS - 1u)
    #endif /* (CY_PSOC4) */

    #define `$INSTANCE_NAME`_MD_CHECKSUM_ADDR           `$INSTANCE_NAME`_META_CHECKSUM_ADDR(0u)
    #define `$INSTANCE_NAME`_MD_LAST_BLDR_ROW_ADDR      `$INSTANCE_NAME`_META_LAST_BLDR_ROW_ADDR(0u)
    #define `$INSTANCE_NAME`_MD_APP_BYTE_LEN            `$INSTANCE_NAME`_META_APP_BYTE_LEN(0u)
    #define `$INSTANCE_NAME`_MD_APP_VERIFIED_ADDR       `$INSTANCE_NAME`_META_APP_VERIFIED_ADDR(0u)
    #define `$INSTANCE_NAME`_MD_APP_ENTRY_POINT_ADDR    `$INSTANCE_NAME`_META_APP_ENTRY_POINT_ADDR(0u)
    #define `$INSTANCE_NAME`_MD_APP_RUN_ADDR            `$INSTANCE_NAME`_META_APP_RUN_ADDR(0u)
#else
    #if(!CY_PSOC4)
        #define `$INSTANCE_NAME`_MD_ROW(x)              ((CY_FLASH_NUMBER_ROWS / `$INSTANCE_NAME`_NUM_OF_FLASH_ARRAYS) \
                                                        - 1u - ( uint32 )(x))
    #else
        #define `$INSTANCE_NAME`_MD_ROW(x)              (CY_FLASH_NUMBER_ROWS - 1u - ( uint32 )(x))
    #endif /* (CY_PSOC4) */

    #define `$INSTANCE_NAME`_MD_CHECKSUM_ADDR           `$INSTANCE_NAME`_META_CHECKSUM_ADDR(appId)
    #define `$INSTANCE_NAME`_MD_LAST_BLDR_ROW_ADDR      `$INSTANCE_NAME`_META_LAST_BLDR_ROW_ADDR(appId)
    #define `$INSTANCE_NAME`_MD_APP_BYTE_LEN            `$INSTANCE_NAME`_META_APP_BYTE_LEN(appId)
    #define `$INSTANCE_NAME`_MD_APP_VERIFIED_ADDR       `$INSTANCE_NAME`_META_APP_VERIFIED_ADDR(appId)
    #define `$INSTANCE_NAME`_MD_APP_ENTRY_POINT_ADDR    \
                                                `$INSTANCE_NAME`_META_APP_ENTRY_POINT_ADDR(`$INSTANCE_NAME`_activeApp)
    #define `$INSTANCE_NAME`_MD_APP_RUN_ADDR            `$INSTANCE_NAME`_META_APP_RUN_ADDR(`$INSTANCE_NAME`_activeApp)
#endif  /* (0u == `$INSTANCE_NAME`_DUAL_APP_BOOTLOADER) */

#define `$INSTANCE_NAME`_P_APP_ACTIVE(x)                ((uint8 CYCODE *) `$INSTANCE_NAME`_META_APP_ACTIVE_ADDR(x))
#define `$INSTANCE_NAME`_MD_PTR_CHECKSUM                ((uint8  CYCODE *) `$INSTANCE_NAME`_MD_CHECKSUM_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_ENTRY_POINT         ((`$INSTANCE_NAME`_APP_ADDRESS CYCODE *) \
                                                                `$INSTANCE_NAME`_MD_APP_ENTRY_POINT_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_LAST_BLDR_ROW            ((uint16 CYCODE *) `$INSTANCE_NAME`_MD_LAST_BLDR_ROW_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_BYTE_LEN             ((`$INSTANCE_NAME`_APP_ADDRESS CYCODE *) \
                                                                `$INSTANCE_NAME`_MD_APP_BYTE_LEN)
#define `$INSTANCE_NAME`_MD_PTR_APP_RUN_ADDR             ((uint8  CYCODE *) `$INSTANCE_NAME`_MD_APP_RUN_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_VERIFIED             ((uint8  CYCODE *) `$INSTANCE_NAME`_MD_APP_VERIFIED_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_BLD_BL_VER           ((uint16 CYCODE *) `$INSTANCE_NAME`_MD_APP_BLDBL_VER_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_VER                  ((uint16 CYCODE *) `$INSTANCE_NAME`_MD_APP_VER_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_ID                   ((uint16 CYCODE *) `$INSTANCE_NAME`_MD_APP_ID_ADDR)
#define `$INSTANCE_NAME`_MD_PTR_APP_CUST_ID              ((uint32 CYCODE *) `$INSTANCE_NAME`_MD_APP_CUST_ID_ADDR)
#if(CY_PSOC3)
    #define `$INSTANCE_NAME`_APP_ADDRESS                    uint16
    #define `$INSTANCE_NAME`_GET_CODE_DATA(idx)             (*((uint8  CYCODE *) (idx)))
    #define `$INSTANCE_NAME`_GET_CODE_WORD(idx)             (*((uint32 CYCODE *) (idx)))
    #define `$INSTANCE_NAME`_META_APP_ADDR_OFFSET           (3u)
    #define `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET    (7u)
    #define `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET       (11u)
    #define `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET       (15u)
#else
    #define `$INSTANCE_NAME`_APP_ADDRESS                    uint32
    #define `$INSTANCE_NAME`_GET_CODE_DATA(idx)             (*((uint8  *)(CYDEV_FLASH_BASE + (idx))))
    #define `$INSTANCE_NAME`_GET_CODE_WORD(idx)             (*((uint32 *)(CYDEV_FLASH_BASE + (idx))))
    #define `$INSTANCE_NAME`_META_APP_ADDR_OFFSET           (1u)
    #define `$INSTANCE_NAME`_META_APP_BL_LAST_ROW_OFFSET    (5u)
    #define `$INSTANCE_NAME`_META_APP_BYTE_LEN_OFFSET       (9u)
    #define `$INSTANCE_NAME`_META_APP_RUN_TYPE_OFFSET       (13u)
#endif /* (CY_PSOC3) */

#define `$INSTANCE_NAME`_META_APP_ACTIVE_OFFSET             (16u)
#define `$INSTANCE_NAME`_META_APP_VERIFIED_OFFSET           (17u)
#define `$INSTANCE_NAME`_META_APP_BL_BUILD_VER_OFFSET       (18u)
#define `$INSTANCE_NAME`_META_APP_ID_OFFSET                 (20u)
#define `$INSTANCE_NAME`_META_APP_VER_OFFSET                (22u)
#define `$INSTANCE_NAME`_META_APP_CUST_ID_OFFSET            (24u)

#if (CY_PSOC4)
    #define `$INSTANCE_NAME`_GET_REG16(x)   ((uint16)(                                                          \
                                                (( uint16 )(( uint16 )CY_GET_XTND_REG8((x)     )       ))   |   \
                                                (( uint16 )(( uint16 )CY_GET_XTND_REG8((x) + 1u) <<  8u))       \
                                            ))

    #define `$INSTANCE_NAME`_GET_REG32(x)   (                                                                    \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x)     )       ))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 1u) <<  8u))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 2u) << 16u))   |   \
                                                (( uint32 )(( uint32 ) CY_GET_XTND_REG8((x) + 3u) << 24u))       \
                                            )
#endif  /* (CY_PSOC4) */
#define `$INSTANCE_NAME`_META_APP_CHECKSUM_OFFSET           (0u)
#define `$INSTANCE_NAME`_META_DATA_SIZE                     (64u)
#if(CY_PSOC4)
    extern uint8 appRunType;
#endif  /* (CY_PSOC4) */

#if(CY_PSOC4)
    #define `$INSTANCE_NAME`_SOFTWARE_RESET                 CY_SET_REG32(CYREG_CM0_AIRCR, 0x05FA0004u)
#else
    #define `$INSTANCE_NAME`_SOFTWARE_RESET                 CY_SET_REG8(CYREG_RESET_CR2, 0x01u)
#endif  /* (CY_PSOC4) */

#define `$INSTANCE_NAME`_SetFlashRunType(runType)        `$INSTANCE_NAME`_SetFlashByte( \
                                                            `$INSTANCE_NAME`_MD_APP_RUN_ADDR(0), (runType))

#define `$INSTANCE_NAME`_START_APP                  (`$INSTANCE_NAME`_SCHEDULE_BTLDB)
#define `$INSTANCE_NAME`_START_BTLDR                (`$INSTANCE_NAME`_SCHEDULE_BTLDR)

/* Some PSoC Creator versions are used to generate only one name types */
#if !defined (CYDEV_FLASH_BASE)
    #define CYDEV_FLASH_BASE                                (CYDEV_FLS_BASE)
#endif /* !defined (CYDEV_FLASH_BASE) */

#if !defined (CYDEV_FLASH_SIZE)
    #define CYDEV_FLASH_SIZE                                (CYDEV_FLS_SIZE)
#endif /* CYDEV_FLASH_SIZE */


#endif /* CY_BOOTLOADER_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
