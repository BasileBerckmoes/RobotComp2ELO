/***************************************************************************//**
* \file     `$INSTANCE_NAME`_INIT.c
* \version  `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* \brief
* Provides the initialization data structure for the `$INSTANCE_NAME` Component.
*
********************************************************************************
* \copyright
* (c) 2017, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#include "`$INSTANCE_NAME`.h"

/* Array of configuration structures for the ScanADC PDL */
static const cy_stc_sar_config_t `$INSTANCE_NAME`_hwConfigs[`$INSTANCE_NAME`_TOTAL_CONFIGS] = {
    /*Configuration 0*/
    {
        .ctrl               = `$INSTANCE_NAME`_CFG0_CTRL_INIT,
        .sampleCtrl         = `$INSTANCE_NAME`_CFG0_SAMPLE_CTRL_INIT,
        .sampleTime01       = `$INSTANCE_NAME`_CFG0_SAMPLE_TIME01_INIT,
        .sampleTime23       = `$INSTANCE_NAME`_CFG0_SAMPLE_TIME23_INIT,
        .rangeThres         = `$INSTANCE_NAME`_CFG0_RANGE_THRES_INIT,
        .rangeCond          = `$INSTANCE_NAME`_CFG0_RANGE_COND_INIT,
        .chanEn             = `$INSTANCE_NAME`_CFG0_CHANNEL_EN,
        .chanConfig         = `$channelConfig0`
        .intrMask           = SAR_INTR_MASK_EOS_MASK_Msk,
        .satIntrMask        = `$INSTANCE_NAME`_CFG0_SATURATE_INTR_MASK,
        .rangeIntrMask      = `$INSTANCE_NAME`_CFG0_RANGE_INTR_MASK,
        .muxSwitch          = CY_SAR_DEINIT,
        .muxSwitchSqCtrl    = CY_SAR_DEINIT,
        .configRouting      = false,
        .vrefMvValue        = (uint32_t) `$INSTANCE_NAME`_CFG0_VREF_MV_VALUE,
    }
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 1)
    /*Configuration 1*/
    ,{
        .ctrl               = `$INSTANCE_NAME`_CFG1_CTRL_INIT,
        .sampleCtrl         = `$INSTANCE_NAME`_CFG1_SAMPLE_CTRL_INIT,
        .sampleTime01       = `$INSTANCE_NAME`_CFG1_SAMPLE_TIME01_INIT,
        .sampleTime23       = `$INSTANCE_NAME`_CFG1_SAMPLE_TIME23_INIT,
        .rangeThres         = `$INSTANCE_NAME`_CFG1_RANGE_THRES_INIT,
        .rangeCond          = `$INSTANCE_NAME`_CFG1_RANGE_COND_INIT,
        .chanEn             = `$INSTANCE_NAME`_CFG1_CHANNEL_EN,
        /* CHAN_CONFIG Settings */
        .chanConfig         = `$channelConfig1`
        .intrMask           = SAR_INTR_MASK_EOS_MASK_Msk,
        .satIntrMask        = `$INSTANCE_NAME`_CFG1_SATURATE_INTR_MASK,
        .rangeIntrMask      = `$INSTANCE_NAME`_CFG1_RANGE_INTR_MASK,
        .muxSwitch          = CY_SAR_DEINIT,
        .muxSwitchSqCtrl    = CY_SAR_DEINIT,
        .configRouting      = false, /* configRouting */
        .vrefMvValue        = (uint32_t) `$INSTANCE_NAME`_CFG1_VREF_MV_VALUE,
    }
#endif
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 2)
    /*Configuration 2*/
    ,{
        .ctrl               = `$INSTANCE_NAME`_CFG2_CTRL_INIT,
        .sampleCtrl         = `$INSTANCE_NAME`_CFG2_SAMPLE_CTRL_INIT,
        .sampleTime01       = `$INSTANCE_NAME`_CFG2_SAMPLE_TIME01_INIT,
        .sampleTime23       = `$INSTANCE_NAME`_CFG2_SAMPLE_TIME23_INIT,
        .rangeThres         = `$INSTANCE_NAME`_CFG2_RANGE_THRES_INIT,
        .rangeCond          = `$INSTANCE_NAME`_CFG2_RANGE_COND_INIT,
        .chanEn             = `$INSTANCE_NAME`_CFG2_CHANNEL_EN,
        /* CHAN_CONFIG Settings */
        .chanConfig         = `$channelConfig2`
        .intrMask           = SAR_INTR_MASK_EOS_MASK_Msk,
        .satIntrMask        = `$INSTANCE_NAME`_CFG2_SATURATE_INTR_MASK,
        .rangeIntrMask      = `$INSTANCE_NAME`_CFG2_RANGE_INTR_MASK,
        .muxSwitch          = CY_SAR_DEINIT,
        .muxSwitchSqCtrl    = CY_SAR_DEINIT,
        .configRouting      = false, /* configRouting */
        .vrefMvValue        = (uint32_t) `$INSTANCE_NAME`_CFG2_VREF_MV_VALUE,
    }
#endif
    /*Configuration 3*/
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 3)
    ,{
        .ctrl               = `$INSTANCE_NAME`_CFG3_CTRL_INIT,
        .sampleCtrl         = `$INSTANCE_NAME`_CFG3_SAMPLE_CTRL_INIT,
        .sampleTime01       = `$INSTANCE_NAME`_CFG3_SAMPLE_TIME01_INIT,
        .sampleTime23       = `$INSTANCE_NAME`_CFG3_SAMPLE_TIME23_INIT,
        .rangeThres         = `$INSTANCE_NAME`_CFG3_RANGE_THRES_INIT,
        .rangeCond          = `$INSTANCE_NAME`_CFG3_RANGE_COND_INIT,
        .chanEn             = `$INSTANCE_NAME`_CFG3_CHANNEL_EN,
        /* CHAN_CONFIG Settings */
        .chanConfig         = `$channelConfig3`
        .intrMask           = SAR_INTR_MASK_EOS_MASK_Msk,
        .satIntrMask        = `$INSTANCE_NAME`_CFG3_SATURATE_INTR_MASK,
        .rangeIntrMask      = `$INSTANCE_NAME`_CFG3_RANGE_INTR_MASK,
        .muxSwitch          = CY_SAR_DEINIT,
        .muxSwitchSqCtrl    = CY_SAR_DEINIT,
        .configRouting      = false, /* configRouting */
        .vrefMvValue        = (uint32_t) `$INSTANCE_NAME`_CFG3_VREF_MV_VALUE,
    }
#endif
};

/* Array of configuration structures used to set configurations */
const `$INSTANCE_NAME`_CONFIG_STRUCT `$INSTANCE_NAME`_allConfigs[`$INSTANCE_NAME`_TOTAL_CONFIGS] = {
    /*Configuration 0*/
    {
        .channelBase        = `$INSTANCE_NAME`_CFG0_CHANNEL_BASE,
        .numChannels        = `$INSTANCE_NAME`_CFG0_CHANNEL_COUNT,
        .hwConfigStc        = &`$INSTANCE_NAME`_hwConfigs[0],
        .miscConfig         = `$INSTANCE_NAME`_CFG0_MISC_CONFIG_INIT,
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        .clkDivider         = `$INSTANCE_NAME`_CFG0_CLOCKDIVIDER,
    #endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */
    }
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 1)
    /*Configuration 1*/
    ,{
        .channelBase        = `$INSTANCE_NAME`_CFG1_CHANNEL_BASE,
        .numChannels        = `$INSTANCE_NAME`_CFG1_CHANNEL_COUNT,
        .hwConfigStc        = &`$INSTANCE_NAME`_hwConfigs[1],
        .miscConfig         = `$INSTANCE_NAME`_CFG1_MISC_CONFIG_INIT,
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        .clkDivider         = `$INSTANCE_NAME`_CFG1_CLOCKDIVIDER,
    #endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */
    }
#endif
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 2)
    /*Configuration 2*/
    ,{
        .channelBase        = `$INSTANCE_NAME`_CFG2_CHANNEL_BASE,
        .numChannels        = `$INSTANCE_NAME`_CFG2_CHANNEL_COUNT,
        .hwConfigStc        = &`$INSTANCE_NAME`_hwConfigs[2],
        .miscConfig         = `$INSTANCE_NAME`_CFG2_MISC_CONFIG_INIT,
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        .clkDivider         = `$INSTANCE_NAME`_CFG2_CLOCKDIVIDER,
    #endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */
    }
#endif
    /*Configuration 3*/
#if(`$INSTANCE_NAME`_TOTAL_CONFIGS > 3)
    ,{
        .channelBase        = `$INSTANCE_NAME`_CFG3_CHANNEL_BASE,
        .numChannels        = `$INSTANCE_NAME`_CFG3_CHANNEL_COUNT,
        .hwConfigStc        = &`$INSTANCE_NAME`_hwConfigs[3],
        .miscConfig         = `$INSTANCE_NAME`_CFG3_MISC_CONFIG_INIT,
    #if (`$INSTANCE_NAME`_CLOCK_INTERNAL)
        .clkDivider         = `$INSTANCE_NAME`_CFG3_CLOCKDIVIDER,
    #endif /* `$INSTANCE_NAME`_CLOCK_INTERNAL */
    }
#endif
};

/* [] END OF FILE */
