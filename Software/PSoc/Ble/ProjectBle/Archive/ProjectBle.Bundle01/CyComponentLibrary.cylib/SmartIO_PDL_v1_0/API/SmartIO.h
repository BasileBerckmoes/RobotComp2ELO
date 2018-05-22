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

#include "syslib/cy_syslib.h"
#include "cyfitter.h"

/***************************************
*       Constants
***************************************/

/* Port location*/
#define `$INSTANCE_NAME`_PORT           `$INSTANCE_NAME`_cy_mxs40_smartio__HW

/* General constants */
#define `$INSTANCE_NAME`_DUTRIG_MAX     (10UL)
#define `$INSTANCE_NAME`_REGVAL_MAX     (0xffUL)
#define `$INSTANCE_NAME`_OPC_MAX        (11UL)
#define `$INSTANCE_NAME`_DUSIZE_MAX     (8UL)
 

/***************************************
*       Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t `$INSTANCE_NAME`_initVar; /**< Initialization state variable */
/** @} globals */


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
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void);
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void);
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetBypass(void);
void `$INSTANCE_NAME`_SetBypass(uint32_t portChannel);
void `$INSTANCE_NAME`_ClockSelect(uint32_t clockSrc);
void `$INSTANCE_NAME`_HoldOverride(uint32_t ovCtrl);
void `$INSTANCE_NAME`_IoSyncMode(uint32_t portTerm);
void `$INSTANCE_NAME`_ChipSyncMode(uint32_t portTerm);
cy_status `$INSTANCE_NAME`_LUT_SelectInputs(uint32_t lutNum, uint32_t inputNum, uint32_t inputSrc);
void `$INSTANCE_NAME`_LUT_ConfigureMode(uint32_t lutNum, uint32_t mapping, uint32_t mode);
cy_status `$INSTANCE_NAME`_DU_SelectTriggers(uint32_t tr0Sel, uint32_t tr1Sel, uint32_t tr2Sel);
cy_status `$INSTANCE_NAME`_DU_SelectData(uint32_t dataNum, uint32_t dataSel);
cy_status `$INSTANCE_NAME`_DU_RegValue(uint32_t dataValue);
cy_status `$INSTANCE_NAME`_DU_OpCode(uint32_t opCode, uint32_t dataSize);
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
#define `$INSTANCE_NAME`_SRC_DU          16UL /**< \brief Source is Data Unit output */
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

/** \addtogroup duTrConst Data Unit trigger input constants
 * \brief Constants to be passed as "tr0Sel", "tr1Sel", and "tr2Sel" parameters in `$INSTANCE_NAME`_DU_SelectTriggers() function.
 *  @{
 */
#define `$INSTANCE_NAME`_TR_CONST_ZERO   0UL /**< \brief Constant 0        */
#define `$INSTANCE_NAME`_TR_CONST_ONE    1UL /**< \brief Constant 1        */
#define `$INSTANCE_NAME`_TR_DU_OUT       2UL /**< \brief Data unit output  */
#define `$INSTANCE_NAME`_TR_LUT0         3UL /**< \brief LUT 0 output      */
#define `$INSTANCE_NAME`_TR_LUT1         4UL /**< \brief LUT 1 output      */
#define `$INSTANCE_NAME`_TR_LUT2         5UL /**< \brief LUT 2 output      */
#define `$INSTANCE_NAME`_TR_LUT3         6UL /**< \brief LUT 3 output      */
#define `$INSTANCE_NAME`_TR_LUT4         7UL /**< \brief LUT 4 output      */
#define `$INSTANCE_NAME`_TR_LUT5         8UL /**< \brief LUT 5 output      */
#define `$INSTANCE_NAME`_TR_LUT6         9UL /**< \brief LUT 6 output      */
#define `$INSTANCE_NAME`_TR_LUT7         10UL /**< \brief LUT 7 output     */
/** @} duTrConst */

/** \addtogroup duDataConst Data Unit data register constants
 * \brief Constants to be passed as "dataNum" parameter in `$INSTANCE_NAME`_DU_SelectData() function.
 *  @{
 */
#define `$INSTANCE_NAME`_DATA0             1UL /**< \brief DU DATA0 register                  */
#define `$INSTANCE_NAME`_DATA1             2UL /**< \brief DU DATA1 register                  */
#define `$INSTANCE_NAME`_DATA_BOTH         3UL /**< \brief Both DU DATA0 and DATA1 registers  */
/** @} duDataConst */

/** \addtogroup duDataSrcConst Data Unit data register source selection constants
 * \brief Constants to be passed as "dataSel" parameter in `$INSTANCE_NAME`_DU_SelectData() function.
 *  @{
 */
#define `$INSTANCE_NAME`_DATA_CONST_ZERO   0UL /**< \brief Constant 0          */
#define `$INSTANCE_NAME`_DATA_TERM_DATA    1UL /**< \brief Terminal data[7:0]  */
#define `$INSTANCE_NAME`_DATA_TERM_GPIO    2UL /**< \brief Terminal gpio[7:0]  */
#define `$INSTANCE_NAME`_DATA_DU_REG       3UL /**< \brief Data Unit register  */
/** @} duDataSrcConst */

/** \addtogroup duOpcConst Data Unit opcode constants
 * \brief Constants to be passed as "opCode" parameter in `$INSTANCE_NAME`_DU_OpCode() function.
 *  @{
 */
#define `$INSTANCE_NAME`_OPC_INCR           1UL /**< \brief Count Up                */
#define `$INSTANCE_NAME`_OPC_DECR           2UL /**< \brief Count Down              */
#define `$INSTANCE_NAME`_OPC_INCR_WRAP      3UL /**< \brief Count Up and wrap       */
#define `$INSTANCE_NAME`_OPC_DECR_WRAP      4UL /**< \brief Count Down and wrap     */
#define `$INSTANCE_NAME`_OPC_INCR_DECR      5UL /**< \brief Count Up/Down           */
#define `$INSTANCE_NAME`_OPC_INCR_DECR_WRAP 6UL /**< \brief Count Up/Down and wrap  */
#define `$INSTANCE_NAME`_OPC_ROR            7UL /**< \brief Rotate right            */
#define `$INSTANCE_NAME`_OPC_SHR            8UL /**< \brief Shift right             */
#define `$INSTANCE_NAME`_OPC_AND_OR         9UL /**< \brief DU Data0 AND DU Data1   */
#define `$INSTANCE_NAME`_OPC_SHR_MAJ3       10UL /**< \brief Majority 3              */
#define `$INSTANCE_NAME`_OPC_SHR_EQL        11UL /**< \brief Equal DU Data1         */
/** @} duOpcConst */

/** @} group_constants */


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

/* DU input selection */
#define `$INSTANCE_NAME`_DU_TR0          `$du_in0`UL
#define `$INSTANCE_NAME`_DU_TR1          `$du_in1`UL
#define `$INSTANCE_NAME`_DU_TR2          `$du_in2`UL

/* DU configuration */
#define `$INSTANCE_NAME`_DU_DATA0        `$du_data0`UL
#define `$INSTANCE_NAME`_DU_DATA1        `$du_data1`UL
#define `$INSTANCE_NAME`_DU_REG          `$du_reg`UL
#define `$INSTANCE_NAME`_DU_SIZE         `$du_size`UL
#define `$INSTANCE_NAME`_DU_OPCODE       `$du_opcode`UL


/***************************************
*        Register Constants
***************************************/

/* Channel number */
#define `$INSTANCE_NAME`_CH0                       (0U)
#define `$INSTANCE_NAME`_CH1                       (1U)
#define `$INSTANCE_NAME`_CH2                       (2U)
#define `$INSTANCE_NAME`_CH3                       (3U)
#define `$INSTANCE_NAME`_CH4                       (4U)
#define `$INSTANCE_NAME`_CH5                       (5U)
#define `$INSTANCE_NAME`_CH6                       (6U)
#define `$INSTANCE_NAME`_CH7                       (7U)

/* SmartIO Fabric Enable/Disable */
#define `$INSTANCE_NAME`_FABRIC_ENABLE             ((uint32_t)((uint32_t)0x01U << SMARTIO_PRT_CTL_ENABLED_Pos))
#define `$INSTANCE_NAME`_FABRIC_DISABLE            ((uint32_t)(~(uint32_t)((uint32_t)0x01U << SMARTIO_PRT_CTL_ENABLED_Pos)))

/* Bypass Mask */
#define `$INSTANCE_NAME`_BYPASS_CLEAR              ((uint32_t)(~(uint32_t)(SMARTIO_PRT_CTL_BYPASS_Msk)))

/* Clock Source Const 0, clear, mask */
#define `$INSTANCE_NAME`_CLOCK_CONST_ZERO          ((uint32_t)((uint32_t)`$INSTANCE_NAME`_CLK_GATED << SMARTIO_PRT_CTL_CLOCK_SRC_Pos))
#define `$INSTANCE_NAME`_CLOCK_CLEAR               ((uint32_t)(~(uint32_t)(SMARTIO_PRT_CTL_CLOCK_SRC_Msk)))

/* Hold override HSIOM/SmartIO */
#define `$INSTANCE_NAME`_HLD_OVR_SMARTIO           ((uint32_t)((uint32_t)0x01U << SMARTIO_PRT_CTL_HLD_OVR_Pos))
#define `$INSTANCE_NAME`_HLD_OVR_HSIOM             ((uint32_t)(~(uint32_t)((uint32_t)0x01U << SMARTIO_PRT_CTL_HLD_OVR_Pos)))

/* Pipeline Enable/Disable */
#define `$INSTANCE_NAME`_PIPELINE_ENABLE           ((uint32_t)((uint32_t)0x01U << SMARTIO_PRT_CTL_PIPELINE_EN_Pos))
#define `$INSTANCE_NAME`_PIPELINE_DISABLE          ((uint32_t)(~(uint32_t)((uint32_t)0x01U << SMARTIO_PRT_CTL_PIPELINE_EN_Pos)))

/* Sync control clear */
#define `$INSTANCE_NAME`_IO_SYNC_CLEAR             ((uint32_t)(~(uint32_t)(SMARTIO_PRT_SYNC_CTL_IO_SYNC_EN_Msk)))
#define `$INSTANCE_NAME`_DATA_SYNC_CLEAR           ((uint32_t)(~(uint32_t)(SMARTIO_PRT_SYNC_CTL_CHIP_SYNC_EN_Msk)))

/* LUT inputs clear */
#define `$INSTANCE_NAME`_LUT_TR0_CLEAR             ((uint32_t)(~(uint32_t)(SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk)))
#define `$INSTANCE_NAME`_LUT_TR1_CLEAR             ((uint32_t)(~(uint32_t)(SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk)))
#define `$INSTANCE_NAME`_LUT_TR2_CLEAR             ((uint32_t)(~(uint32_t)(SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk)))
#define `$INSTANCE_NAME`_LUT_TR_CLEAR_ALL          (`$INSTANCE_NAME`_LUT_TR0_CLEAR & `$INSTANCE_NAME`_LUT_TR1_CLEAR & `$INSTANCE_NAME`_LUT_TR2_CLEAR)

/* LUT config clear */
#define `$INSTANCE_NAME`_LUT_MAP_CLEAR             ((uint32_t)(~(uint32_t)(SMARTIO_PRT_LUT_CTL_LUT_Msk)))
#define `$INSTANCE_NAME`_LUT_OPC_CLEAR             ((uint32_t)(~(uint32_t)(SMARTIO_PRT_LUT_CTL_LUT_OPC_Msk)))
#define `$INSTANCE_NAME`_LUT_CTL_CLEAR             ((uint32_t)(`$INSTANCE_NAME`_LUT_MAP_CLEAR & `$INSTANCE_NAME`_LUT_OPC_CLEAR))

/* DU inputs clear */
#define `$INSTANCE_NAME`_DU_TR0_CLEAR              ((uint32_t)(~(uint32_t)(SMARTIO_PRT_DU_SEL_DU_TR0_SEL_Msk)))
#define `$INSTANCE_NAME`_DU_TR1_CLEAR              ((uint32_t)(~(uint32_t)(SMARTIO_PRT_DU_SEL_DU_TR1_SEL_Msk)))
#define `$INSTANCE_NAME`_DU_TR2_CLEAR              ((uint32_t)(~(uint32_t)(SMARTIO_PRT_DU_SEL_DU_TR2_SEL_Msk)))
#define `$INSTANCE_NAME`_DU_TR_CLEAR_ALL           (`$INSTANCE_NAME`_DU_TR0_CLEAR & `$INSTANCE_NAME`_DU_TR1_CLEAR & `$INSTANCE_NAME`_DU_TR2_CLEAR)

/* DU DATA0 and DATA1 clear */
#define `$INSTANCE_NAME`_DU_DATA0_CLEAR            ((uint32_t)(~(uint32_t)(SMARTIO_PRT_DU_SEL_DU_DATA0_SEL_Msk)))
#define `$INSTANCE_NAME`_DU_DATA1_CLEAR            ((uint32_t)(~(uint32_t)(SMARTIO_PRT_DU_SEL_DU_DATA1_SEL_Msk)))
#define `$INSTANCE_NAME`_DU_DATA01_CLEAR_BOTH      (`$INSTANCE_NAME`_DU_DATA0_CLEAR & `$INSTANCE_NAME`_DU_DATA1_CLEAR)


/***************************************
*        Initial configuration
***************************************/

/* Bypass configuration */
#define `$INSTANCE_NAME`_INIT_BYPASS              ((uint32_t)(((`$INSTANCE_NAME`_BYPASS0)       | \
                                                     (`$INSTANCE_NAME`_BYPASS1 << `$INSTANCE_NAME`_CH1) | \
                                                     (`$INSTANCE_NAME`_BYPASS2 << `$INSTANCE_NAME`_CH2) | \
                                                     (`$INSTANCE_NAME`_BYPASS3 << `$INSTANCE_NAME`_CH3) | \
                                                     (`$INSTANCE_NAME`_BYPASS4 << `$INSTANCE_NAME`_CH4) | \
                                                     (`$INSTANCE_NAME`_BYPASS5 << `$INSTANCE_NAME`_CH5) | \
                                                     (`$INSTANCE_NAME`_BYPASS6 << `$INSTANCE_NAME`_CH6) | \
                                                     (`$INSTANCE_NAME`_BYPASS7 << `$INSTANCE_NAME`_CH7))  \
                                                     << SMARTIO_PRT_CTL_BYPASS_Pos))

/* Clock configuration */
#define `$INSTANCE_NAME`_INIT_CLOCK_SRC           ((uint32_t)(`$INSTANCE_NAME`_CLOCK_SELECT << SMARTIO_PRT_CTL_CLOCK_SRC_Pos))

/* Hold override configuration */
#define `$INSTANCE_NAME`_INIT_HLD_OVR             ((uint32_t)(`$INSTANCE_NAME`_HLD_OVR << SMARTIO_PRT_CTL_HLD_OVR_Pos))

/* Disable the pipeline */
#define `$INSTANCE_NAME`_INIT_PIPELINE_EN         ((uint32_t)((uint32_t)0x00U << SMARTIO_PRT_CTL_PIPELINE_EN_Pos))

/* Initial general control configuration */
#define `$INSTANCE_NAME`_INIT_CTL_CONFIG          ((uint32_t)(`$INSTANCE_NAME`_INIT_PIPELINE_EN | \
                                                    `$INSTANCE_NAME`_INIT_HLD_OVR     | \
                                                    `$INSTANCE_NAME`_INIT_CLOCK_SRC   | \
                                                    `$INSTANCE_NAME`_INIT_BYPASS))

/* IO Sync configuration */
#define `$INSTANCE_NAME`_INIT_IO_SYNC             ((uint32_t)(((`$INSTANCE_NAME`_IO_SYNC0)       | \
                                                     (`$INSTANCE_NAME`_IO_SYNC1 << `$INSTANCE_NAME`_CH1) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC2 << `$INSTANCE_NAME`_CH2) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC3 << `$INSTANCE_NAME`_CH3) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC4 << `$INSTANCE_NAME`_CH4) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC5 << `$INSTANCE_NAME`_CH5) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC6 << `$INSTANCE_NAME`_CH6) | \
                                                     (`$INSTANCE_NAME`_IO_SYNC7 << `$INSTANCE_NAME`_CH7))  \
                                                     << SMARTIO_PRT_SYNC_CTL_IO_SYNC_EN_Pos))

/* Chip data Sync configuration */
#define `$INSTANCE_NAME`_INIT_DATA_SYNC           ((uint32_t)(((`$INSTANCE_NAME`_DATA_SYNC0)       | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC1 << `$INSTANCE_NAME`_CH1) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC2 << `$INSTANCE_NAME`_CH2) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC3 << `$INSTANCE_NAME`_CH3) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC4 << `$INSTANCE_NAME`_CH4) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC5 << `$INSTANCE_NAME`_CH5) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC6 << `$INSTANCE_NAME`_CH6) | \
                                                     (`$INSTANCE_NAME`_DATA_SYNC7 << `$INSTANCE_NAME`_CH7))  \
                                                     << SMARTIO_PRT_SYNC_CTL_CHIP_SYNC_EN_Pos))

/* Initial synchronization configuration */
#define `$INSTANCE_NAME`_INIT_SYNC_CONFIG         ((uint32_t)(`$INSTANCE_NAME`_INIT_DATA_SYNC | \
                                                     `$INSTANCE_NAME`_INIT_IO_SYNC))

/* Initial LUTs input select TR0 */
#define `$INSTANCE_NAME`_INIT_LUT0_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT0_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk))
#define `$INSTANCE_NAME`_INIT_LUT1_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT1_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT2_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT2_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT3_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT3_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT4_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT4_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT5_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT5_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT6_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT6_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT7_TR0            ((uint32_t)((`$INSTANCE_NAME`_LUT7_TR0 << SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR0_SEL_Msk ))

/* Initial LUTs input select TR1 */
#define `$INSTANCE_NAME`_INIT_LUT0_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT0_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT1_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT1_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT2_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT2_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT3_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT3_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT4_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT4_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT5_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT5_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT6_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT6_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT7_TR1            ((uint32_t)((`$INSTANCE_NAME`_LUT7_TR1 << SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR1_SEL_Msk ))

/* Initial LUTs input select TR2 */
#define `$INSTANCE_NAME`_INIT_LUT0_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT0_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk ))
#define `$INSTANCE_NAME`_INIT_LUT1_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT1_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))
#define `$INSTANCE_NAME`_INIT_LUT2_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT2_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))
#define `$INSTANCE_NAME`_INIT_LUT3_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT3_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))
#define `$INSTANCE_NAME`_INIT_LUT4_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT4_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))
#define `$INSTANCE_NAME`_INIT_LUT5_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT5_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))
#define `$INSTANCE_NAME`_INIT_LUT6_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT6_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))
#define `$INSTANCE_NAME`_INIT_LUT7_TR2            ((uint32_t)((`$INSTANCE_NAME`_LUT7_TR2 << SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Pos) & SMARTIO_PRT_LUT_SEL_LUT_TR2_SEL_Msk  ))

/* Initial LUTs input selections */
#define `$INSTANCE_NAME`_INIT_LUT0_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT0_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT0_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT0_TR2))
#define `$INSTANCE_NAME`_INIT_LUT1_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT1_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT1_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT1_TR2))
#define `$INSTANCE_NAME`_INIT_LUT2_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT2_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT2_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT2_TR2))
#define `$INSTANCE_NAME`_INIT_LUT3_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT3_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT3_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT3_TR2))
#define `$INSTANCE_NAME`_INIT_LUT4_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT4_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT4_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT4_TR2))
#define `$INSTANCE_NAME`_INIT_LUT5_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT5_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT5_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT5_TR2))
#define `$INSTANCE_NAME`_INIT_LUT6_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT6_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT6_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT6_TR2))
#define `$INSTANCE_NAME`_INIT_LUT7_SEL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT7_TR0 | \
                                                    `$INSTANCE_NAME`_INIT_LUT7_TR1 | \
                                                    `$INSTANCE_NAME`_INIT_LUT7_TR2))

/* Initial LUTs truth tables */
#define `$INSTANCE_NAME`_INIT_LUT0_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT0_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT1_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT1_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT2_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT2_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT3_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT3_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT4_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT4_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT5_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT5_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT6_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT6_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))
#define `$INSTANCE_NAME`_INIT_LUT7_MAP            ((uint32_t)(`$INSTANCE_NAME`_LUT7_MAP << SMARTIO_PRT_LUT_CTL_LUT_Pos))

/* Initial LUTs modes */
#define `$INSTANCE_NAME`_INIT_LUT0_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT0_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT1_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT1_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT2_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT2_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT3_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT3_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT4_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT4_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT5_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT5_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT6_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT6_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))
#define `$INSTANCE_NAME`_INIT_LUT7_MODE           ((uint32_t)(`$INSTANCE_NAME`_LUT7_MODE << SMARTIO_PRT_LUT_CTL_LUT_OPC_Pos))

/* Initial LUTs control configuration */
#define `$INSTANCE_NAME`_INIT_LUT0_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT0_MAP  | `$INSTANCE_NAME`_INIT_LUT0_MODE))
#define `$INSTANCE_NAME`_INIT_LUT1_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT1_MAP  | `$INSTANCE_NAME`_INIT_LUT1_MODE))
#define `$INSTANCE_NAME`_INIT_LUT2_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT2_MAP  | `$INSTANCE_NAME`_INIT_LUT2_MODE))
#define `$INSTANCE_NAME`_INIT_LUT3_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT3_MAP  | `$INSTANCE_NAME`_INIT_LUT3_MODE))
#define `$INSTANCE_NAME`_INIT_LUT4_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT4_MAP  | `$INSTANCE_NAME`_INIT_LUT4_MODE))
#define `$INSTANCE_NAME`_INIT_LUT5_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT5_MAP  | `$INSTANCE_NAME`_INIT_LUT5_MODE))
#define `$INSTANCE_NAME`_INIT_LUT6_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT6_MAP  | `$INSTANCE_NAME`_INIT_LUT6_MODE))
#define `$INSTANCE_NAME`_INIT_LUT7_CTL_CONFIG     ((uint32_t)(`$INSTANCE_NAME`_INIT_LUT7_MAP  | `$INSTANCE_NAME`_INIT_LUT7_MODE))

/* Initial DU selection configuration */
#define `$INSTANCE_NAME`_INIT_DU_TR0_SEL          ((uint32_t)(`$INSTANCE_NAME`_DU_TR0 << SMARTIO_PRT_DU_SEL_DU_TR0_SEL_Pos))
#define `$INSTANCE_NAME`_INIT_DU_TR1_SEL          ((uint32_t)(`$INSTANCE_NAME`_DU_TR1 << SMARTIO_PRT_DU_SEL_DU_TR1_SEL_Pos))
#define `$INSTANCE_NAME`_INIT_DU_TR2_SEL          ((uint32_t)(`$INSTANCE_NAME`_DU_TR2 << SMARTIO_PRT_DU_SEL_DU_TR2_SEL_Pos))
#define `$INSTANCE_NAME`_INIT_DU_DATA0_SEL        ((uint32_t)(`$INSTANCE_NAME`_DU_DATA0 << SMARTIO_PRT_DU_SEL_DU_DATA0_SEL_Pos))
#define `$INSTANCE_NAME`_INIT_DU_DATA1_SEL        ((uint32_t)(`$INSTANCE_NAME`_DU_DATA1 << SMARTIO_PRT_DU_SEL_DU_DATA1_SEL_Pos))

#define `$INSTANCE_NAME`_INIT_DU_SEL              ((uint32_t)(`$INSTANCE_NAME`_INIT_DU_TR0_SEL | \
                                                    `$INSTANCE_NAME`_INIT_DU_TR1_SEL | \
                                                    `$INSTANCE_NAME`_INIT_DU_TR2_SEL | \
                                                    `$INSTANCE_NAME`_INIT_DU_DATA0_SEL | \
                                                    `$INSTANCE_NAME`_INIT_DU_DATA1_SEL ))

/* Initial DU control configuration */
#define `$INSTANCE_NAME`_INIT_DU_SIZE             ((uint32_t)(`$INSTANCE_NAME`_DU_SIZE << SMARTIO_PRT_DU_CTL_DU_SIZE_Pos))
#define `$INSTANCE_NAME`_INIT_DU_OPC              ((uint32_t)(`$INSTANCE_NAME`_DU_OPCODE << SMARTIO_PRT_DU_CTL_DU_OPC_Pos))

#define `$INSTANCE_NAME`_INIT_DU_CTL              ((uint32_t)(`$INSTANCE_NAME`_INIT_DU_SIZE | \
                                                    `$INSTANCE_NAME`_INIT_DU_OPC ))

/* Initial DU Data register */
#define `$INSTANCE_NAME`_INIT_DU_DATA_REG         `$INSTANCE_NAME`_DU_REG


/***************************************
*        Inline Functions
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
__STATIC_INLINE void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_PORT->CTL |= `$INSTANCE_NAME`_FABRIC_ENABLE;
}


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
__STATIC_INLINE void `$INSTANCE_NAME`_Disable(void)
{
    `$INSTANCE_NAME`_PORT->CTL &= `$INSTANCE_NAME`_FABRIC_DISABLE;
}


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
*  uint8_t Bypass state of the channels on the port.
*
* \funcusage
*  \snippet `$INSTANCE_NAME`_SUT.c usage_`$INSTANCE_NAME`_GetBypass
*******************************************************************************/
__STATIC_INLINE uint8_t `$INSTANCE_NAME`_GetBypass(void)
{
    return ((uint8_t)(`$INSTANCE_NAME`_PORT->CTL & ((uint32_t)`$INSTANCE_NAME`_CHANNEL_ALL << SMARTIO_PRT_CTL_BYPASS_Pos)));
}


/** @} functions */

#endif /* (CY_SMARTIO_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
