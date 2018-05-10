/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_10
{
    /// <summary>
    /// GUI parameter checks.
    /// </summary>
    public static class CyGuiChecks
    {
        /// <summary>
        /// Determine if channel uses both alternate resolution and averaging.
        /// </summary>
        /// <param name="config">Configuration parameters</param>
        /// <param name="chanNum">Channel number</param>
        /// <returns>True if channel uses alternate resolution and averaging,
        /// otherwise false</returns>
        public static bool IsAltResAverage(CyConfigModel config, int chanNum)
        {
            CyChannelModel channel = config.ChannelList[chanNum];
            return channel.UseAltResolution && channel.UseAveraging;
        }
        /// <summary>
        /// Determine if channel is enabled.
        /// </summary>
        /// <param name="config">Configuration parameters</param>
        /// <param name="chanNum">Channel number</param>
        /// <returns>True if channel is enabled,
        /// otherwise false</returns>
        public static bool IsChannelEnabled(CyConfigModel config, int chanNum)
        {
            CyChannelModel channel = config.ChannelList[chanNum];
            return channel.Enabled;
        }
        /// <summary>
        /// Determine if a config's averaging settings will cause the
        /// result to overflow.
        /// </summary>
        /// <param name="config">Configuration parameters</param>
        /// <returns>True if averaging is interleaved and more than 16
        /// samples are to be averaged, otherwise false.</returns>
        public static bool IsAverageOverflow(CyConfigModel config)
        {
            return config.AveragingMode == CyEAveragingMode.INTERLEAVED_AVG
                 &&  (config.SamplesAveraged > CyESamplesAveraged.SIXTEEN_SAMPLES);
        }
    }
}