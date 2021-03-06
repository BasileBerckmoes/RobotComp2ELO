/*******************************************************************************
* \file `$INSTANCE_NAME`.h
* \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
*  This file provides constants and parameter values for the SmartIO Component.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SMARTIO_`$INSTANCE_NAME`_H)
#define CY_SMARTIO_`$INSTANCE_NAME`_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_functions
* @{
*/
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);
void `$INSTANCE_NAME`_SetBypass(uint32 portChannel);
void `$INSTANCE_NAME`_ClockSelect(uint32 clockSrc);
void `$INSTANCE_NAME`_HoldOverride(uint32 ovCtrl);
void `$INSTANCE_NAME`_IoSyncMode(uint32 portTerm);
void `$INSTANCE_NAME`_ChipSyncMode(uint32 portTerm);
cystatus `$INSTANCE_NAME`_LUT_SelectInputs(uint32 lutNum, uint32 inputNum, uint32 inputSrc);
void `$INSTANCE_NAME`_LUT_ConfigureMode(uint32 lutNum, uint32 mapping, uint32 mode);
/** @} functions */


/***************************************
*        API Constants
***************************************/
/**
* \addtogroup group_constants
* @{
*/
/** \addtogroup channelConst Port channel selection constants
 * \brief Constants to be passed as "portChannel" parameter in `$INSTANCE_NAME`_SetBypass() function.
 *  @{
 */
#define `$INSTANCE_NAME`_CHANNEL_NONE    0x00UL /**< \brief Do not bypass any channels  */
#define `$INSTANCE_NAME`_CHANNEL0        0x01UL /**< \brief Channel 0 (data0 <-> gpio0) */
#define `$INSTANCE_NAME`_CHANNEL1        0x02UL /**< \brief Channel 1 (data1 <-> gpio1) */
#define `$INSTANCE_NAME`_CHANNEL2        0x04UL /**< \brief Channel 2 (data2 <-> gpio2) */
#define `$INSTANCE_NAME`_CHANNEL3        0x08UL /**< \brief Channel 3 (data3 <-> gpio3) */
#define `$INSTANCE_NAME`_CHANNEL4        0x10UL /**< \brief Channel 4 (data4 <-> gpio4) */
#define `$INSTANCE_NAME`_CHANNEL5        0x20UL /**< \brief Channel 5 (data5 <-> gpio5) */
#define `$INSTANCE_NAME`_CHANNEL6        0x40UL /**< \brief Channel 6 (data6 <-> gpio6) */
#define `$INSTANCE_NAME`_CHANNEL7        0x80UL /**< \brief Channel 7 (data7 <-> gpio7) */
#define `$INSTANCE_NAME`_CHANNEL_ALL     0xffUL /**< \brief Bypass all channels         */
/** @} channelConst */

/** \addtogroup clockConst Component clock selection constants
 * \brief Constants to be passed as "clockSrc" parameter in `$INSTANCE_NAME`_ClockSelect() function.
 *  @{
 */
#define `$INSTANCE_NAME`_CLK_GPIO0       0UL  /**< \brief Clock sourced from signal on gpio0 */
#define `$INSTANCE_NAME`_CLK_GPIO1       1UL  /**< \brief Clock sourced from signal on gpio1 */
#define `$INSTANCE_NAME`_CLK_GPIO2       2UL  /**< \brief Clock sourced from signal on gpio2 */
#define `$INSTANCE_NAME`_CLK_GPIO3       3UL  /**< \brief Clock sourced from signal on gpio3 */
#define `$INSTANCE_NAME`_CLK_GPIO4       4UL  /**< \brief Clock sourced from signal on gpio4 */
#define `$INSTANCE_NAME`_CLK_GPIO5       5UL  /**< \brief Clock sourced from signal on gpio5 */
#define `$INSTANCE_NAME`_CLK_GPIO6       6UL  /**< \brief Clock sourced from signal on gpio6 */
#define `$INSTANCE_NAME`_CLK_GPIO7       7UL  /**< \brief Clock sourced from signal on gpio7 */
#define `$INSTANCE_NAME`_CLK_DATA0       8UL  /**< \brief Clock sourced from signal on data0 */
#define `$INSTANCE_NAME`_CLK_DATA1       9UL  /**< \brief Clock sourced from signal on data1 */
#define `$INSTANCE_NAME`_CLK_DATA2       10UL /**< \brief Clock sourced from signal on data2 */
#define `$INSTANCE_NAME`_CLK_DATA3       11UL /**< \brief Clock sourced from signal on data3 */
#define `$INSTANCE_NAME`_CLK_DATA4       12UL /**< \brief Clock sourced from signal on data4 */
#define `$INSTANCE_NAME`_CLK_DATA5       13UL /**< \brief Clock sourced from signal on data5 */
#define `$INSTANCE_NAME`_CLK_DATA6       14UL /**< \brief Clock sourced from signal on data6 */
#define `$INSTANCE_NAME`_CLK_DATA7       15UL /**< \brief Clock sourced from signal on data7 */
#define `$INSTANCE_NAME`_DIV_CLK_ACT     16UL /**< \brief Clock sourced from a divided clock (Active) */
#define `$INSTANCE_NAME`_DIV_CLK_DS      17UL /**< \brief Clock sourced from a divided clock (Deep-Sleep) */
#define `$INSTANCE_NAME`_DIV_CLK_HIB     18UL /**< \brief Clock sourced from a divided clock (Hibernate) */
#define `$INSTANCE_NAME`_LFCLK           19UL /**< \brief Clock sourced from LFCLK */
#define `$INSTANCE_NAME`_CLK_GATED       20UL /**< \brief Disables the clock connection. Used when turning off the block */
#define `$INSTANCE_NAME`_ASYNC           31UL /**< \brief Asynchronous operation */
/** @} clockConst */

/** \addtogroup hldOvrConst Component hold override selection constants
 * \brief Constants to be passed as "ovCtrl" parameter in `$INSTANCE_NAME`_HoldOverride() function.
 *  @{
 */
#define `$INSTANCE_NAME`_OVCTRL_DISABLE  0UL /**< \brief Controlled by HSIOM  */
#define `$INSTANCE_NAME`_OVCTRL_ENABLE   1UL /**< \brief Controlled by SmartIO */
/** @} hldOvrConst */

/** \addtogroup termConst Terminal selection constants
 * \brief Constants to be passed as "portTerm" parameter in `$INSTANCE_NAME`_IoSyncMode() and 
 *  `$INSTANCE_NAME`_ChipSyncMode() functions.
 *  @{
 */
#define `$INSTANCE_NAME`_TERM_NONE       0x00UL /**< \brief No synchronization for all data/gpio     */
#define `$INSTANCE_NAME`_TERM0           0x01UL /**< \brief Enable synchronization for data0/gpio0   */
#define `$INSTANCE_NAME`_TERM1           0x02UL /**< \brief Enable synchronization for data1/gpio1   */
#define `$INSTANCE_NAME`_TERM2           0x04UL /**< \brief Enable synchronization for data2/gpio2   */
#define `$INSTANCE_NAME`_TERM3           0x08UL /**< \brief Enable synchronization for data3/gpio3   */
#define `$INSTANCE_NAME`_TERM4           0x10UL /**< \brief Enable synchronization for data4/gpio4   */
#define `$INSTANCE_NAME`_TERM5           0x20UL /**< \brief Enable synchronization for data5/gpio5   */
#define `$INSTANCE_NAME`_TERM6           0x40UL /**< \brief Enable synchronization for data6/gpio6   */
#define `$INSTANCE_NAME`_TERM7           0x80UL /**< \brief Enable synchronization for data7/gpio7   */
#define `$INSTANCE_NAME`_TERM_ALL        0xffUL /**< \brief Enable sycnhronization for all data/gpio */
/** @} termConst */

/** \addtogroup lutNumConst Look-up table number constants
 * \brief Constants to be passed as "lutNum" parameter in `$INSTANCE_NAME`_LUT_SelectInputs() and `$INSTANCE_NAME`_LUT_ConfigureMode() functions.
 *  @{
 */
#define `$INSTANCE_NAME`_LUT0            0UL /**< \brief LUT number 0  */
#define `$INSTANCE_NAME`_LUT1            1UL /**< \brief LUT number 1  */
#define `$INSTANCE_NAME`_LUT2            2UL /**< \brief LUT number 2  */
#define `$INSTANCE_NAME`_LUT3            3UL /**< \brief LUT number 3  */
#define `$INSTANCE_NAME`_LUT4            4UL /**< \brief LUT number 4  */
#define `$INSTANCE_NAME`_LUT5            5UL /**< \brief LUT number 5  */
#define `$INSTANCE_NAME`_LUT6            6UL /**< \brief LUT number 6  */
#define `$INSTANCE_NAME`_LUT7            7UL /**< \brief LUT number 7  */
/** @} lutNumConst */

/** \addtogroup inputNumConst LUT input number constants
 * \brief Constants to be passed as "inputNum" parameter in `$INSTANCE_NAME`_LUT_SelectInputs() function.
 *  @{
 */
#define `$INSTANCE_NAME`_LUT_INPUT0      0x01UL /**< \brief LUT input terminal 0    */
#define `$INSTANCE_NAME`_LUT_INPUT1      0x02UL /**< \brief LUT input terminal 1    */
#define `$INSTANCE_NAME`_LUT_INPUT2      0x04UL /**< \brief LUT input terminal 2    */
#define `$INSTANCE_NAME`_LUT_INPUT_ALL   0x07UL /**< \brief All LUT input terminals */
/** @} inputNumConst */

/** \addtogroup inputSrcConst LUT input source constants
 * \brief Constants to be passed as "inputSrc" parameter in `$INSTANCE_NAME`_LUT_SelectInputs() function.
 *  @{
 */
#define `$INSTANCE_NAME`_SRC_LUT0        0UL  /**< \brief Source is LUT0 output    */
#define `$INSTANCE_NAME`_SRC_LUT1        1UL  /**< \brief Source is LUT1 output    */
#define `$INSTANCE_NAME`_SRC_LUT2        2UL  /**< \brief Source is LUT2 output    */
#define `$INSTANCE_NAME`_SRC_LUT3        3UL  /**< \brief Source is LUT3 output    */
#define `$INSTANCE_NAME`_SRC_LUT4        4UL  /**< \brief Source is LUT4 output    */
#define `$INSTANCE_NAME`_SRC_LUT5        5UL  /**< \brief Source is LUT5 output    */
#define `$INSTANCE_NAME`_SRC_LUT6        6UL  /**< \brief Source is LUT6 output    */
#define `$INSTANCE_NAME`_SRC_LUT7        7UL  /**< \brief Source is LUT7 output    */
#define `$INSTANCE_NAME`_SRC_DATA_04     8UL  /**< \brief Source is data0/data4    */
#define `$INSTANCE_NAME`_SRC_DATA_15     9UL  /**< \brief Source is data1/data5    */
#define `$INSTANCE_NAME`_SRC_DATA_26     10UL /**< \brief Source is data2/data6    */
#define `$INSTANCE_NAME`_SRC_DATA_37     11UL /**< \brief Source is data3/data7    */
#define `$INSTANCE_NAME`_SRC_GPIO_04     12UL /**< \brief Source is gpio0/gpio4    */
#define `$INSTANCE_NAME`_SRC_GPIO_15     13UL /**< \brief Source is gpio1/gpio5    */
#define `$INSTANCE_NAME`_SRC_GPIO_26     14UL /**< \brief Source is gpio2/gpio6    */
#define `$INSTANCE_NAME`_SRC_GPIO_37     15UL /**< \brief Source is gpio3/gpio7    */
/** @} inputSrcConst */

/** \addtogroup modeConst LUT mode constants
 * \brief Constants to be passed as "mode" parameter in `$INSTANCE_NAME`_LUT_ConfigureMode() function.
 *  @{
 */
#define `$INSTANCE_NAME`_MODE_COMB       0UL /**< \brief Combinatorial mode      */
#define `$INSTANCE_NAME`_MODE_REGIN      1UL /**< \brief Registered input mode   */
#define `$INSTANCE_NAME`_MODE_REGOUT     2UL /**< \brief Registered output mode  */
#define `$INSTANCE_NAME`_MODE_SRFF       3UL /**< \brief S/R Flip-Flop mode      */
/** @} modeConst */

/** @} group_constants */


/***************************************
*       Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8 `$INSTANCE_NAME`_initVar; /**< Initialization state variable */
/** @} globals */


/***************************************
*    Enumerated Types and Parameters
***************************************/

/* Number of channels */
#define `$INSTANCE_NAME`_CHANNELS       (8u)

/**
* \addtogroup group_structs
* @{
*/
typedef struct
{
    uint32 lutSel[`$INSTANCE_NAME`_CHANNELS]; /**< LUT input selection configuration */
	uint32 lutCtl[`$INSTANCE_NAME`_CHANNELS]; /**< LUT mode and mapping configuration */
} `$INSTANCE_NAME`_lut_config_struct;
/** @} structs */


/***************************************
*    Initial Parameter Constants
***************************************/
    
/* Global control */
#define `$INSTANCE_NAME`_BYPASS0         `$Fabric_bypass0`UL
#define `$INSTANCE_NAME`_BYPASS1         `$Fabric_bypass1`UL
#define `$INSTANCE_NAME`_BYPASS2         `$Fabric_bypass2`UL
#define `$INSTANCE_NAME`_BYPASS3         `$Fabric_bypass3`UL
#define `$INSTANCE_NAME`_BYPASS4         `$Fabric_bypass4`UL
#define `$INSTANCE_NAME`_BYPASS5         `$Fabric_bypass5`UL
#define `$INSTANCE_NAME`_BYPASS6         `$Fabric_bypass6`UL
#define `$INSTANCE_NAME`_BYPASS7         `$Fabric_bypass7`UL
#define `$INSTANCE_NAME`_CLOCK_SELECT    `$Clock_select`UL
#define `$INSTANCE_NAME`_HLD_OVR         `$UseHldOvr`UL

/* IO Synchronization control */
#define `$INSTANCE_NAME`_IO_SYNC0        `$gpio0_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC1        `$gpio1_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC2        `$gpio2_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC3        `$gpio3_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC4        `$gpio4_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC5        `$gpio5_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC6        `$gpio6_sync`UL
#define `$INSTANCE_NAME`_IO_SYNC7        `$gpio7_sync`UL

/* Chip Data Synchronization control */
#define `$INSTANCE_NAME`_DATA_SYNC0      `$data0_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC1      `$data1_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC2      `$data2_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC3      `$data3_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC4      `$data4_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC5      `$data5_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC6      `$data6_sync`UL
#define `$INSTANCE_NAME`_DATA_SYNC7      `$data7_sync`UL

/* LUT input selection */
#define `$INSTANCE_NAME`_LUT0_TR0        `$lut0_in0`UL
#define `$INSTANCE_NAME`_LUT0_TR1        `$lut0_in1`UL
#define `$INSTANCE_NAME`_LUT0_TR2        `$lut0_in2`UL
#define `$INSTANCE_NAME`_LUT1_TR0        `$lut1_in0`UL
#define `$INSTANCE_NAME`_LUT1_TR1        `$lut1_in1`UL
#define `$INSTANCE_NAME`_LUT1_TR2        `$lut1_in2`UL
#define `$INSTANCE_NAME`_LUT2_TR0        `$lut2_in0`UL
#define `$INSTANCE_NAME`_LUT2_TR1        `$lut2_in1`UL
#define `$INSTANCE_NAME`_LUT2_TR2        `$lut2_in2`UL
#define `$INSTANCE_NAME`_LUT3_TR0        `$lut3_in0`UL
#define `$INSTANCE_NAME`_LUT3_TR1        `$lut3_in1`UL
#define `$INSTANCE_NAME`_LUT3_TR2        `$lut3_in2`UL
#define `$INSTANCE_NAME`_LUT4_TR0        `$lut4_in0`UL
#define `$INSTANCE_NAME`_LUT4_TR1        `$lut4_in1`UL
#define `$INSTANCE_NAME`_LUT4_TR2        `$lut4_in2`UL
#define `$INSTANCE_NAME`_LUT5_TR0        `$lut5_in0`UL
#define `$INSTANCE_NAME`_LUT5_TR1        `$lut5_in1`UL
#define `$INSTANCE_NAME`_LUT5_TR2        `$lut5_in2`UL
#define `$INSTANCE_NAME`_LUT6_TR0        `$lut6_in0`UL
#define `$INSTANCE_NAME`_LUT6_TR1        `$lut6_in1`UL
#define `$INSTANCE_NAME`_LUT6_TR2        `$lut6_in2`UL
#define `$INSTANCE_NAME`_LUT7_TR0        `$lut7_in0`UL
#define `$INSTANCE_NAME`_LUT7_TR1        `$lut7_in1`UL
#define `$INSTANCE_NAME`_LUT7_TR2        `$lut7_in2`UL

/* LUT truth table */
#define `$INSTANCE_NAME`_LUT0_MAP        `$lut0_map`UL
#define `$INSTANCE_NAME`_LUT1_MAP        `$lut1_map`UL
#define `$INSTANCE_NAME`_LUT2_MAP        `$lut2_map`UL
#define `$INSTANCE_NAME`_LUT3_MAP        `$lut3_map`UL
#define `$INSTANCE_NAME`_LUT4_MAP        `$lut4_map`UL
#define `$INSTANCE_NAME`_LUT5_MAP        `$lut5_map`UL
#define `$INSTANCE_NAME`_LUT6_MAP        `$lut6_map`UL
#define `$INSTANCE_NAME`_LUT7_MAP        `$lut7_map`UL

/* LUT mode */
#define `$INSTANCE_NAME`_LUT0_MODE       `$lut0_mode`UL
#define `$INSTANCE_NAME`_LUT1_MODE       `$lut1_mode`UL
#define `$INSTANCE_NAME`_LUT2_MODE       `$lut2_mode`UL
#define `$INSTANCE_NAME`_LUT3_MODE       `$lut3_mode`UL
#define `$INSTANCE_NAME`_LUT4_MODE       `$lut4_mode`UL
#define `$INSTANCE_NAME`_LUT5_MODE       `$lut5_mode`UL
#define `$INSTANCE_NAME`_LUT6_MODE       `$lut6_mode`UL
#define `$INSTANCE_NAME`_LUT7_MODE       `$lut7_mode`UL


/***************************************
*        Registers
***************************************/

/* PRGIO global control register */
#define `$INSTANCE_NAME`_CTL                (* (reg32 *) `$INSTANCE_NAME`_cy_m0s8_prgio__CTL)

/* IO and chip data synchronization control */
#define `$INSTANCE_NAME`_SYNC_CTL           (* (reg32 *) `$INSTANCE_NAME`_cy_m0s8_prgio__SYNC_CTL)

/* LUT input selection and control registers */
#define `$INSTANCE_NAME`_LUT_CONGIG_BASE    (*(volatile `$INSTANCE_NAME`_lut_config_struct *) `$INSTANCE_NAME`_cy_m0s8_prgio__LUT_SEL0)

/* Data unit registers */
#define `$INSTANCE_NAME`_DU_SEL             (* (reg32 *) `$INSTANCE_NAME`_cy_m0s8_prgio__DU_SEL)
#define `$INSTANCE_NAME`_DU_CTL             (* (reg32 *) `$INSTANCE_NAME`_cy_m0s8_prgio__DU_CTL)
#define `$INSTANCE_NAME`_DATA               (* (reg32 *) `$INSTANCE_NAME`_cy_m0s8_prgio__DATA)


/***************************************
*        Register Constants
***************************************/

/* Channel number */
#define `$INSTANCE_NAME`_CH0                       (0u)
#define `$INSTANCE_NAME`_CH1                       (1u)
#define `$INSTANCE_NAME`_CH2                       (2u)
#define `$INSTANCE_NAME`_CH3                       (3u)
#define `$INSTANCE_NAME`_CH4                       (4u)
#define `$INSTANCE_NAME`_CH5                       (5u)
#define `$INSTANCE_NAME`_CH6                       (6u)
#define `$INSTANCE_NAME`_CH7                       (7u)

/* Register set to all zeros/ones */
#define `$INSTANCE_NAME`_REG_ZEROS                 ((uint32)0x00000000u)
#define `$INSTANCE_NAME`_REG_ONES                  ((uint32)0xffffffffu)

/* SmartIO Fabric Enable/Disable */
#define `$INSTANCE_NAME`_FABRIC_ENABLE             ((uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_ENABLED__OFFSET))
#define `$INSTANCE_NAME`_FABRIC_DISABLE            ((uint32)(~(uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_ENABLED__OFFSET)))
#define `$INSTANCE_NAME`_FABRIC_MASK               ((uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_ENABLED__OFFSET))

/* Bypass Mask */
#define `$INSTANCE_NAME`_BYPASS_MASK               ((uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_BYPASS__OFFSET))
#define `$INSTANCE_NAME`_BYPASS_CLEAR              ((uint32)(~(uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_BYPASS__OFFSET)))

/* Clock Source Const 0, clear, mask */
#define `$INSTANCE_NAME`_CLOCK_CONST_ZERO          ((uint32)((uint32)`$INSTANCE_NAME`_CLK_GATED << CYFLD_PRGIO_PRT_CLOCK_SRC__OFFSET))
#define `$INSTANCE_NAME`_CLOCK_CLEAR               ((uint32)(~(uint32)((uint32)0x1fu << CYFLD_PRGIO_PRT_CLOCK_SRC__OFFSET)))
#define `$INSTANCE_NAME`_CLOCK_MASK                ((uint32)((uint32)0x1fu << CYFLD_PRGIO_PRT_CLOCK_SRC__OFFSET))

/* Hold override HSIOM/SmartIO */
#define `$INSTANCE_NAME`_HLD_OVR_SMARTIO           ((uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_HLD_OVR__OFFSET))
#define `$INSTANCE_NAME`_HLD_OVR_HSIOM             ((uint32)(~(uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_HLD_OVR__OFFSET)))

/* Pipeline Enable/Disable */
#define `$INSTANCE_NAME`_PIPELINE_ENABLE           ((uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_PIPELINE_EN__OFFSET))
#define `$INSTANCE_NAME`_PIPELINE_DISABLE          ((uint32)(~(uint32)((uint32)0x01u << CYFLD_PRGIO_PRT_PIPELINE_EN__OFFSET)))

/* Sync control clear */
#define `$INSTANCE_NAME`_IO_SYNC_MASK              ((uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_IO_SYNC_EN__OFFSET))
#define `$INSTANCE_NAME`_DATA_SYNC_MASK            ((uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_CHIP_SYNC_EN__OFFSET))
#define `$INSTANCE_NAME`_IO_SYNC_CLEAR             ((uint32)(~(uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_IO_SYNC_EN__OFFSET)))
#define `$INSTANCE_NAME`_DATA_SYNC_CLEAR           ((uint32)(~(uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_CHIP_SYNC_EN__OFFSET)))

/* LUT inputs clear */
#define `$INSTANCE_NAME`_LUT_TR0_CLEAR             ((uint32)(~(uint32)((uint32)0x0fu << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET)))
#define `$INSTANCE_NAME`_LUT_TR1_CLEAR             ((uint32)(~(uint32)((uint32)0x0fu << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET)))
#define `$INSTANCE_NAME`_LUT_TR2_CLEAR             ((uint32)(~(uint32)((uint32)0x0fu << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET)))
#define `$INSTANCE_NAME`_LUT_TR_CLEAR_ALL          (`$INSTANCE_NAME`_LUT_TR0_CLEAR & `$INSTANCE_NAME`_LUT_TR1_CLEAR & `$INSTANCE_NAME`_LUT_TR2_CLEAR)
#define `$INSTANCE_NAME`_LUT_TR0_MASK              ((uint32)((uint32)0x0fu << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_LUT_TR1_MASK              ((uint32)((uint32)0x0fu << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_LUT_TR2_MASK              ((uint32)((uint32)0x0fu << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))

/* LUT config clear */
#define `$INSTANCE_NAME`_LUT_MAP_CLEAR             ((uint32)(~(uint32)((uint32)0xffu << CYFLD_PRGIO_PRT_LUT__OFFSET)))
#define `$INSTANCE_NAME`_LUT_OPC_CLEAR             ((uint32)(~(uint32)((uint32)0x03u << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET)))
#define `$INSTANCE_NAME`_LUT_CTL_CLEAR             ((uint32)(`$INSTANCE_NAME`_LUT_MAP_CLEAR & `$INSTANCE_NAME`_LUT_OPC_CLEAR))
#define `$INSTANCE_NAME`_LUT_MAP_MASK              (((uint32)0xffu << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_LUT_OPC_MASK              (((uint32)0x03u << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))


/***************************************
*        Initial configuration
***************************************/

/* Bypass configuration */
#define `$INSTANCE_NAME`_INIT_BYPASS              ((uint32)(((`$INSTANCE_NAME`_BYPASS0)       | \
                                                     (`$INSTANCE_NAME`_BYPASS1 << `$INSTANCE_NAME`_CH1) | \
                                                     (`$INSTANCE_NAME`_BYPASS2 << `$INSTANCE_NAME`_CH2) | \
                                                     (`$INSTANCE_NAME`_BYPASS3 << `$INSTANCE_NAME`_CH3) | \
                                                     (`$INSTANCE_NAME`_BYPASS4 << `$INSTANCE_NAME`_CH4) | \
                                                     (`$INSTANCE_NAME`_BYPASS5 << `$INSTANCE_NAME`_CH5) | \
                                                     (`$INSTANCE_NAME`_BYPASS6 << `$INSTANCE_NAME`_CH6) | \
                                                     (`$INSTANCE_NAME`_BYPASS7 << `$INSTANCE_NAME`_CH7))  \
                                                     << CYFLD_PRGIO_PRT_BYPASS__OFFSET))
/* Clock configuration */
#define `$INSTANCE_NAME`_INIT_CLOCK_SRC           ((uint32)(`$INSTANCE_NAME`_CLOCK_SELECT << CYFLD_PRGIO_PRT_CLOCK_SRC__OFFSET))
/* Hold override configuration */
#define `$INSTANCE_NAME`_INIT_HLD_OVR             ((uint32)(`$INSTANCE_NAME`_HLD_OVR << CYFLD_PRGIO_PRT_HLD_OVR__OFFSET))
/* Disable the pipeline */
#define `$INSTANCE_NAME`_INIT_PIPELINE_EN         ((uint32)((uint32)0x00u << CYFLD_PRGIO_PRT_PIPELINE_EN__OFFSET))
/* Initial general control configuration */
#define `$INSTANCE_NAME`_INIT_CTL_CONFIG          ((uint32)(`$INSTANCE_NAME`_INIT_PIPELINE_EN | \
                                                    `$INSTANCE_NAME`_INIT_HLD_OVR     | \
                                                    `$INSTANCE_NAME`_INIT_CLOCK_SRC   | \
                                                    `$INSTANCE_NAME`_INIT_BYPASS))

/* IO Sync configuration */
#define `$INSTANCE_NAME`_INIT_IO_SYNC             ((uint32)(((`$INSTANCE_NAME`_IO_SYNC0)       | \
                                                     (`$INSTANCE_NAME`_IO_SYNC1 << `$INSTANCE_NAME`_CH1) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC2 << `$INSTANCE_NAME`_CH2) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC3 << `$INSTANCE_NAME`_CH3) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC4 << `$INSTANCE_NAME`_CH4) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC5 << `$INSTANCE_NAME`_CH5) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC6 << `$INSTANCE_NAME`_CH6) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC7 << `$INSTANCE_NAME`_CH7))  \
                                                     << CYFLD_PRGIO_PRT_IO_SYNC_EN__OFFSET))
/* Chip data Sync configuration */
#define `$INSTANCE_NAME`_INIT_DATA_SYNC           ((uint32)(((`$INSTANCE_NAME`_DATA_SYNC0)       | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC1 << `$INSTANCE_NAME`_CH1) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC2 << `$INSTANCE_NAME`_CH2) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC3 << `$INSTANCE_NAME`_CH3) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC4 << `$INSTANCE_NAME`_CH4) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC5 << `$INSTANCE_NAME`_CH5) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC6 << `$INSTANCE_NAME`_CH6) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC7 << `$INSTANCE_NAME`_CH7))  \
                                                     << CYFLD_PRGIO_PRT_CHIP_SYNC_EN__OFFSET))
/* Initial synchronization configuration */
#define `$INSTANCE_NAME`_INIT_SYNC_CONFIG         ((uint32)(`$INSTANCE_NAME`_INIT_DATA_SYNC | \
                                                     `$INSTANCE_NAME`_INIT_IO_SYNC))

/* LUTs input select TR0 */
#define `$INSTANCE_NAME`_INIT_LUT0_TR0            ((uint32)(`$INSTANCE_NAME`_LUT0_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT1_TR0            ((uint32)(`$INSTANCE_NAME`_LUT1_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT2_TR0            ((uint32)(`$INSTANCE_NAME`_LUT2_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT3_TR0            ((uint32)(`$INSTANCE_NAME`_LUT3_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT4_TR0            ((uint32)(`$INSTANCE_NAME`_LUT4_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT5_TR0            ((uint32)(`$INSTANCE_NAME`_LUT5_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT6_TR0            ((uint32)(`$INSTANCE_NAME`_LUT6_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT7_TR0            ((uint32)(`$INSTANCE_NAME`_LUT7_TR0 << CYFLD_PRGIO_PRT_LUT_TR0_SEL__OFFSET))
/* LUTs input select TR1 */
#define `$INSTANCE_NAME`_INIT_LUT0_TR1            ((uint32)(`$INSTANCE_NAME`_LUT0_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT1_TR1            ((uint32)(`$INSTANCE_NAME`_LUT1_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT2_TR1            ((uint32)(`$INSTANCE_NAME`_LUT2_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT3_TR1            ((uint32)(`$INSTANCE_NAME`_LUT3_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT4_TR1            ((uint32)(`$INSTANCE_NAME`_LUT4_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT5_TR1            ((uint32)(`$INSTANCE_NAME`_LUT5_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT6_TR1            ((uint32)(`$INSTANCE_NAME`_LUT6_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT7_TR1            ((uint32)(`$INSTANCE_NAME`_LUT7_TR1 << CYFLD_PRGIO_PRT_LUT_TR1_SEL__OFFSET))
/* LUTs input select TR2 */
#define `$INSTANCE_NAME`_INIT_LUT0_TR2            ((uint32)(`$INSTANCE_NAME`_LUT0_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT1_TR2            ((uint32)(`$INSTANCE_NAME`_LUT1_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT2_TR2            ((uint32)(`$INSTANCE_NAME`_LUT2_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT3_TR2            ((uint32)(`$INSTANCE_NAME`_LUT3_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT4_TR2            ((uint32)(`$INSTANCE_NAME`_LUT4_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT5_TR2            ((uint32)(`$INSTANCE_NAME`_LUT5_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT6_TR2            ((uint32)(`$INSTANCE_NAME`_LUT6_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT7_TR2            ((uint32)(`$INSTANCE_NAME`_LUT7_TR2 << CYFLD_PRGIO_PRT_LUT_TR2_SEL__OFFSET))
/* Initial LUTs input selections */
#define `$INSTANCE_NAME`_INIT_LUT0_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT0_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT0_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT0_TR2))
#define `$INSTANCE_NAME`_INIT_LUT1_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT1_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT1_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT1_TR2))
#define `$INSTANCE_NAME`_INIT_LUT2_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT2_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT2_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT2_TR2))
#define `$INSTANCE_NAME`_INIT_LUT3_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT3_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT3_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT3_TR2))
#define `$INSTANCE_NAME`_INIT_LUT4_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT4_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT4_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT4_TR2))
#define `$INSTANCE_NAME`_INIT_LUT5_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT5_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT5_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT5_TR2))
#define `$INSTANCE_NAME`_INIT_LUT6_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT6_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT6_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT6_TR2))
#define `$INSTANCE_NAME`_INIT_LUT7_SEL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT7_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT7_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT7_TR2))

/* LUTs truth tables */
#define `$INSTANCE_NAME`_INIT_LUT0_MAP            ((uint32)(`$INSTANCE_NAME`_LUT0_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT1_MAP            ((uint32)(`$INSTANCE_NAME`_LUT1_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT2_MAP            ((uint32)(`$INSTANCE_NAME`_LUT2_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT3_MAP            ((uint32)(`$INSTANCE_NAME`_LUT3_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT4_MAP            ((uint32)(`$INSTANCE_NAME`_LUT4_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT5_MAP            ((uint32)(`$INSTANCE_NAME`_LUT5_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT6_MAP            ((uint32)(`$INSTANCE_NAME`_LUT6_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT7_MAP            ((uint32)(`$INSTANCE_NAME`_LUT7_MAP << CYFLD_PRGIO_PRT_LUT__OFFSET))
/* LUTs modes */
#define `$INSTANCE_NAME`_INIT_LUT0_MODE           ((uint32)(`$INSTANCE_NAME`_LUT0_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT1_MODE           ((uint32)(`$INSTANCE_NAME`_LUT1_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT2_MODE           ((uint32)(`$INSTANCE_NAME`_LUT2_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT3_MODE           ((uint32)(`$INSTANCE_NAME`_LUT3_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT4_MODE           ((uint32)(`$INSTANCE_NAME`_LUT4_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT5_MODE           ((uint32)(`$INSTANCE_NAME`_LUT5_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT6_MODE           ((uint32)(`$INSTANCE_NAME`_LUT6_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
#define `$INSTANCE_NAME`_INIT_LUT7_MODE           ((uint32)(`$INSTANCE_NAME`_LUT7_MODE << CYFLD_PRGIO_PRT_LUT_OPC__OFFSET))
/* Initial LUTs control config */
#define `$INSTANCE_NAME`_INIT_LUT0_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT0_MAP  | `$INSTANCE_NAME`_INIT_LUT0_MODE))
#define `$INSTANCE_NAME`_INIT_LUT1_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT1_MAP  | `$INSTANCE_NAME`_INIT_LUT1_MODE))
#define `$INSTANCE_NAME`_INIT_LUT2_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT2_MAP  | `$INSTANCE_NAME`_INIT_LUT2_MODE))
#define `$INSTANCE_NAME`_INIT_LUT3_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT3_MAP  | `$INSTANCE_NAME`_INIT_LUT3_MODE))
#define `$INSTANCE_NAME`_INIT_LUT4_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT4_MAP  | `$INSTANCE_NAME`_INIT_LUT4_MODE))
#define `$INSTANCE_NAME`_INIT_LUT5_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT5_MAP  | `$INSTANCE_NAME`_INIT_LUT5_MODE))
#define `$INSTANCE_NAME`_INIT_LUT6_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT6_MAP  | `$INSTANCE_NAME`_INIT_LUT6_MODE))
#define `$INSTANCE_NAME`_INIT_LUT7_CTL_CONFIG     ((uint32)(`$INSTANCE_NAME`_INIT_LUT7_MAP  | `$INSTANCE_NAME`_INIT_LUT7_MODE))


/***************************************
*        Macro Functions
***************************************/

/**
* \addtogroup group_functions
* @{
*/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
****************************************************************************//**
*
* \brief Enables the component. 
*  
* Once enabled, it takes two component clock cycles for the fabric reset to
* deactivate and the fabric becomes operational. If the clock source is set to
* Asynchronous mode, it takes three SYSCLK cycles before becoming functional.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_Enable
*******************************************************************************/
#define `$INSTANCE_NAME`_Enable()           (`$INSTANCE_NAME`_CTL |= `$INSTANCE_NAME`_FABRIC_ENABLE)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable
****************************************************************************//**
*
* \brief Disables the component. 
*  
* The block is disabled, which places the channels into bypass mode and the
* sequential elements are reset based on the chosen clock selection.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_Disable
*******************************************************************************/
#define `$INSTANCE_NAME`_Disable()           (`$INSTANCE_NAME`_CTL &= `$INSTANCE_NAME`_FABRIC_DISABLE)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetBypass
****************************************************************************//**
*
* \brief Returns the bypass configuration of the channels on a bit by bit basis. 
*
* Bypassed channels behave like they would as if the SmartIO component was
* not present for those particular channels. 
*
* \return
*  uint8 Bypass state of the channels on the port.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_GetBypass
*******************************************************************************/
#define `$INSTANCE_NAME`_GetBypass()        ((uint8)(`$INSTANCE_NAME`_CTL \
                                            & ((uint32)`$INSTANCE_NAME`_CHANNEL_ALL << CYFLD_PRGIO_PRT_BYPASS__OFFSET)))
/** @} functions */

#endif /* (CY_SMARTIO_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
