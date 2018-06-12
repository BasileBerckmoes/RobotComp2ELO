/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;


namespace Scan_ADC_v1_30
{
    /// <summary>
    /// Holds customizer parameters for a single row in a configuration's channel table.
    /// </summary>
    [Serializable]
    public class CyChannelModel
    {
        /// <summary>
        /// True iff channel is enabled for conversion.
        /// </summary>
        public bool Enabled { get; set; }

        /// <summary>
        /// True iff channel used alternate resolution.
        /// </summary>
        public bool UseAltResolution { get; set; }

        /// <summary>
        /// Channel input mode.
        /// Values are DIFFERENTIAL_CHAN and so on from CyEnum of CyEInputMode
        /// </summary>
        public CyEInputMode InputMode { get; set; }

        /// <summary>
        /// True iff channel uses averaging.
        /// </summary>
        public bool UseAveraging { get; set; }

        /// <summary>
        /// Minimum acquisition time in ns.
        /// </summary>
        public double MinimumAcqTime { get; set; }

        /// <summary>
        /// True iff channel has limit comparison interrupts enabled.
        /// </summary>
        public bool UseLimitInterrupt { get; set; }

        public double ActualAcqTime { get; set; }

        /// <summary>
        /// True iff channel has saturation interrupts enabled.
        /// </summary>
        public bool UseSaturationInterrupt { get; set; }

        /// <summary>
        /// Index of sample aperture timer for this channel.
        /// </summary>
        public int ApertureTimer { get; set; }

        #region CyChannelModel Constructors

        /// <summary>
        /// Default constructor.
        /// 
        /// Required for XML deserialization.
        /// </summary>
        public CyChannelModel()
        {
            this.Enabled = true;
            this.UseAltResolution = false;
            this.InputMode = CyEInputMode.DIFFERENTIAL_CHAN;
            this.UseAveraging = false;
            this.MinimumAcqTime = CyParamRanges.APERTURE_MIN_NS;
            this.UseLimitInterrupt = false;
            this.UseSaturationInterrupt = false;
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="enabled">True iff channel is enabled.</param>
        /// <param name="useAltRes">True iff channel uses alternate resolution.</param>
        /// <param name="channelType">Differential, single-ended, or filter.</param>
        /// <param name="useAverage">True iff channel uses averaging.</param>
        /// <param name="minimumAcquisitionTime">Minumum aquisituin time for this channel.</param>
        /// <param name="useLimitInterrupt">True iff channel can generate limit interrupts.</param>
        /// <param name="useSaturationInterrupt">True iff channel can generate saturation interrupts.</param>
        public CyChannelModel(bool enabled, bool useAltRes, CyEInputMode channelType,
                              bool useAverage, double minimumAcquisitionTime,
                              bool useLimitInterrupt, bool useSaturationInterrupt)
        {
            this.Enabled = enabled;
            this.InputMode = channelType;
            this.UseAltResolution = useAltRes;
            this.UseAveraging = useAverage;
            this.MinimumAcqTime = minimumAcquisitionTime;
            this.UseLimitInterrupt = useLimitInterrupt;
            this.UseSaturationInterrupt = useSaturationInterrupt;

            double minAcqTime = (this.InputMode == CyEInputMode.FILTER_CHAN)
                ? CyParamRanges.APERTURE_FILTER_MIN_NS : CyParamRanges.APERTURE_MIN_NS;
            if (this.MinimumAcqTime < minAcqTime)
            {
                this.MinimumAcqTime = minAcqTime;
            }
        }

        #endregion CyChannelModel Constructors
    }
}
