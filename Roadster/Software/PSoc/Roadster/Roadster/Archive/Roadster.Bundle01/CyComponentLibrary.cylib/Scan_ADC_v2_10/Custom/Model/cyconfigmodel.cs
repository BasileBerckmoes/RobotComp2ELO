/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Xml;
using System.Xml.Serialization;

using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_10
{
    /// <summary>
    /// Holds customizer parameters for a configuration tab.
    /// Contains parameters for both the conversion and filter sub-tabs.
    /// </summary>
    [Serializable]
    public class CyConfigModel
    {
        // Events
        public event SideEffectHandler SideEffectChange;

        #region Conversion sub-tab properties
      
        /// <summary>
        /// True if sample rate editor is enabled.
        /// False if Clock frequency editor is enabled.
        /// </summary>
        public bool SampleRateEditor { get; set; }

        /// <summary>
        /// ADC sample rate in scans per second.
        /// </summary>
        public double SampleRate { get; set; }

        /// <summary>
        /// SAR IP information.
        /// </summary>
        [XmlIgnore]
        public CySar Sar { get; set; }

        /// <summary>
        /// True if SAR is configured for free running operation.
        /// False if SAR is configured for one-shot operation.
        /// </summary>
        public bool FreeRunning { get; set; }

        /// <summary>
        /// True iff SAR symbol has an SOC input terminal.
        /// </summary>
        public bool UseSoc { get; set; }

        /// <summary>
        /// True iff external vref pin has a bypass cap.
        /// </summary>
        public bool VrefBypass { get; set; }

        /// <summary>
        /// Vref source selection.
        /// Values from CyEnum of CyEVrefSource.
        /// </summary>
        public CyEVrefSource VrefSource { get; set; }
        
        /// <summary>
        /// Vref voltage level in volts.
        /// </summary>
        public double VrefVoltage { get; set; }

        /// <summary>
        /// Vneg source selection.
        /// Values from CyEnum of CyEVnegSource.
        /// </summary>
        public CyEVnegSource VnegSource { get; set; }

        /// <summary>
        /// Differential channel result format.
        /// Values from CyEnum CyENumberFormat.
        /// </summary>
        public CyENumberFormat DiffResultFormat { get; set; }

        /// <summary>
        /// Single ended channel result format.
        /// Values from CyEnum CyENumberFormat.
        /// </summary>
        public CyENumberFormat SingleEndedResultFormat { get; set; }

        /// <summary>
        /// Number of samples to average.
        /// Values from CyEnum CyESamplesAveraged.
        /// </summary>
        public CyESamplesAveraged SamplesAveraged { get; set; }

        /// <summary>
        /// Averaging mode selection.
        /// Values from CyEnum CyEAveragingMode.
        /// </summary>
        public CyEAveragingMode AveragingMode { get; set; }

        /// <summary>
        /// Alternate resolution selection.
        /// Values from CyEnum of CyEAlternateResolutions.
        /// </summary>
        public CyEAlternateResolution AlternateResolution { get; set; }

        /// <summary>
        /// Compare interrupt comparison mode selection.
        /// Values from CyEnum of CyELimitComparisonMode.
        /// </summary>
        public CyELimitComparisonMode CompareMode { get; set; }

        /// <summary>
        /// Compare interrupt low compare limit.
        /// </summary>
        public double LowLimit { get; set; }

        /// <summary>
        /// Compare interrupt high compare limit.
        /// </summary>
        public double HighLimit { get; set; }

        /// <summary>
        /// Number of channels in configuration.
        /// </summary>
        public int NumChannels { get; set; }

        /// <summary>
        /// Options for each channel in configuration.
        /// </summary>
        public List<CyChannelModel> ChannelList { get; set; }

        /// <summary>
        /// List of aperture times for SAR SAMPLE_TIME01 and SAMPLE_TIME23 registers.
        /// </summary>
        public List<int> ApertureTimers { get; set; }

        /// <summary>
        /// ADC clock divider for SAR internal clock source.
        /// </summary>
        public int AdcClockDivider { get; set; }

        #endregion Conversion sub-tab properties

        #region Filter tab properties

        /// <summary>
        /// Filter type selection.
        /// Values from CyEnum of CyEFilterType>.
        /// </summary>
        public CyEFilterType FilterType { get; set; }

        /// <summary>
        /// Either 3Db or center frequency, depending on filter type.
        /// Units are in kHz.
        /// </summary>
        public double FilterDown3OrCenter { get; set; }

        /// <summary>
        /// Either Notch frequency or bandwidth, depending on filter type.
        /// Units are in kHz.
        /// </summary>
        public double FilterWidthOrNotch { get; set; }

        /// <summary>
        /// Filter sample frequency.
        /// 
        /// For test/debug only.  Will be replaced with calculated value.
        /// </summary>
        public double FilterSample { get; set; }

        /// <summary>
        /// Filter's UAB startup delay in clk_cf.
        /// </summary>
        public long FilterUabStartDelay { get; set; }

        // Filter's UAB clock divider from clk_hf. 
        public long FilterUabClockDivider { get; set; }

        /// <summary>
        /// Calculated UAB cap values for filter.
        /// </summary>
        public GTCaps UabCaps { get; set; }

        public long ActualSampleRate { get; set; }

        public long ActualAdcClockHz { get; set; }

        /// <summary>
        /// Number of microseconds per complete scan.
        /// </summary>
        public double ActualScanUs { get; set; }

        /// <summary>
        /// Minimum scan rate in scans per second.
        /// </summary>
        [XmlIgnore]
        public long MinScanRate { get; set; }

        /// <summary>
        /// Maximum scan rate in scans per second.
        /// </summary>
        [XmlIgnore]
        public long MaxScanRate { get; set; }

        #endregion Filter tab properties

        #region CyConfigModel Constructors

        /// <summary>
        /// Default constructor.
        /// 
        /// Required for XML serialization.
        /// </summary>
        public CyConfigModel()
            : this(0)
        {
        }

        /// <summary>
        /// Construct configuration object with specified number of channels.
        /// </summary>
        /// <param name="numRows">Number of rows in channel table.</param>
        public CyConfigModel(int numRows)
        {
            if (numRows < 0)
            {
                numRows = 0;
            }
            if (numRows > CySarRanges.NUM_CHANNEL_MAX)
            {
                numRows = CySarRanges.NUM_CHANNEL_MAX;
            }

            // Conversion sub-tab parameters.
            this.SampleRateEditor = true;
            this.SampleRate = 100000;
            this.FreeRunning = true;
            this.UseSoc = false;
            this.VrefSource = CyEVrefSource.VREFSOURCE_VBGR;
            this.VrefVoltage = 1.2;
            this.VrefBypass = true;
            this.VnegSource = CyEVnegSource.VNEGSOURCE_VREFSHORT;
            this.DiffResultFormat = CyENumberFormat.SIGNED_FORMAT;
            this.SingleEndedResultFormat = CyENumberFormat.UNSIGNED_FORMAT;
            this.SamplesAveraged = CyESamplesAveraged.TWO_SAMPLES;
            this.AveragingMode = CyEAveragingMode.SEQUENTIAL_AVG;
            this.AlternateResolution = CyEAlternateResolution.EIGHT_BIT;
            this.CompareMode = CyELimitComparisonMode.LESS_THAN;
            this.LowLimit = 0x0200;
            this.HighLimit = 0x0e00;
            this.NumChannels = numRows;

            var channels = new List<CyChannelModel>();
            for (int chanIdx = 0; chanIdx < NumChannels; chanIdx++)
            {
                channels.Add(new CyChannelModel());
            }
            this.ChannelList = channels;

            this.ApertureTimers = new List<int>();

            // Filter sub-tab parameters.
            this.FilterType = CyEFilterType.LOW_PASS;
            this.FilterDown3OrCenter = (double)CyParamRanges.DEFAULT_LP_CUTOFF_KHZ;
            this.FilterWidthOrNotch = (double)CyParamRanges.DEFAULT_LP_NOTCH_KHZ;
            this.FilterSample = 1000;
        }

        #endregion CyConfigModelConstructors

        public virtual void OnSideEffectChange()
        {
            SideEffectHandler handler = SideEffectChange;
            if (handler != null)
            {
                handler();
            }
        }

        public List<CyDRCInfo_v1> UpdateScanSchedule(CyClockData clkDat, bool isClkExt, bool isDebug)
        {
            var scheduler = new CyScheduler();
            List<CyDRCInfo_v1> errList = new List<CyDRCInfo_v1>();

            // Get clock information. 
            CyClockData clockData;
            clockData = clkDat;
            scheduler.IsExternalAdcClock = isClkExt;

            if (clockData == null)
            {
                // Clock data not yet available.
                return errList;
            }

            Debug.Assert(clockData.IsAvailable(CyClockDataInfo.DIVIDER));
            Debug.Assert(clockData.IsAvailable(CyClockDataInfo.FREQ));
            Debug.Assert(clockData.Frequency > 0);

            LoadScheduler(scheduler, clockData);

            // Run scheduler.
            try
            {
                scheduler.RunSlowest();
            }
            catch (CapacitorMapperException capException)
            {
                var capDrc = new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    capException.Message);
                scheduler.Solution.Drcs.Add(capDrc);
            }

            DisplaySchedulerErrors(isDebug, scheduler);

            UnloadScheduler(scheduler);

            if (this.ChannelList[0].InputMode == CyEInputMode.FILTER_CHAN)
            {
                FilterDRC(scheduler);
            }

            return scheduler.Solution.Drcs;
        }

        public void UpdateScanRateLimits(CyClockData clkDat, bool isClkExt)
        {
            this.MinScanRate = this.ComputeLowScanRateLimit(clkDat, isClkExt);
            this.MaxScanRate = this.ComputeHighScanRateLimit(clkDat, isClkExt);
        }

        public long ComputeHighScanRateLimit(CyClockData clkDat, bool isClkExt)
        {
            var scheduler = new CyScheduler();
            List<CyDRCInfo_v1> errList = new List<CyDRCInfo_v1>();

            // Get clock information. 
            CyClockData clockData;
            clockData = clkDat;
            scheduler.IsExternalAdcClock = isClkExt;

            if (clockData == null)
            {
                // Clock data not yet available.
                return 0;
            }

            Debug.Assert(clockData.IsAvailable(CyClockDataInfo.DIVIDER));
            Debug.Assert(clockData.IsAvailable(CyClockDataInfo.FREQ));
            Debug.Assert(clockData.Frequency > 0);

            LoadScheduler(scheduler, clockData);

            // Choose target above achievable range.
            scheduler.TargetScanRate_sps = CySarRanges.SAR_UNACHIEVABLE_RATE;

            // Run scheduler.
            try
            {
                scheduler.Run();
            }
            catch (CapacitorMapperException)
            {
                return 0;
            }

            return scheduler.Solution.AchievedSampleRate;
        }

        public long ComputeLowScanRateLimit(CyClockData clkDat, bool isClkExt)
        {
            var scheduler = new CyScheduler();
            List<CyDRCInfo_v1> errList = new List<CyDRCInfo_v1>();

            // Get clock information. 
            CyClockData clockData;
            clockData = clkDat;
            scheduler.IsExternalAdcClock = isClkExt;

            if (clockData == null)
            {
                // Clock data not yet available.
                return 0;
            }

            Debug.Assert(clockData.IsAvailable(CyClockDataInfo.DIVIDER));
            Debug.Assert(clockData.IsAvailable(CyClockDataInfo.FREQ));
            Debug.Assert(clockData.Frequency > 0);

            LoadScheduler(scheduler, clockData);

            // Choose target below achievable range.
            scheduler.TargetScanRate_sps = 1;

            // Run scheduler.
            try
            {
                scheduler.RunSlowest();
            }
            catch (CapacitorMapperException)
            {
                return 0;
            }

            return scheduler.Solution.AchievedSampleRate;
        }

        private void FilterDRC(CyScheduler scheduler)
        {
            const double HZ_PER_KHZ = 1000.0;
            double FSampleMax_kHz
                = (CyScheduler.UAB_CLOCK_MAX_HZ / CyScheduler.UAB_FILTER_STEPS)
                / HZ_PER_KHZ;
            double FSampleActual_kHz = 0.0;
            const double BAND_PASS_CUTOFF_WARN_RATIO = 10.0;
            const double BAND_PASS_LOW_CUTOFF_WARN_RATIO = 500.0;
            const double BAND_STOP_LOW_CUTOFF_WARN_RATIO = 0.40;
            const double BAND_STOP_HIGH_CUTOFF_WARN_RATIO = 2.40;
            double bandPassLowCutoffWarnLimit_kHz = 0.0;

            if (scheduler.Solution.UabClockDivider > 0)
            {
                FSampleActual_kHz
                    = (scheduler.ClkHF_Hz
                    / (scheduler.Solution.UabClockDivider * CyScheduler.UAB_FILTER_STEPS))
                    / HZ_PER_KHZ;
                bandPassLowCutoffWarnLimit_kHz
                    = FSampleActual_kHz / BAND_PASS_LOW_CUTOFF_WARN_RATIO;
            }

            List<CyDRCInfo_v1> filterDRCs = new List<CyDRCInfo_v1>();

            if (this.AveragingMode != CyEAveragingMode.INTERLEAVED_AVG &&
                this.ChannelList[0].UseAveraging)
            {
                scheduler.Solution.Drcs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    "Filter requirement not met: averaging mode must be interleaved")); //E020
            }

            String filterTypeStr;
            if (FilterType == CyEFilterType.LOW_PASS)
            {
                filterTypeStr = "Low Pass Filter";
                if (!(FilterDown3OrCenter < FilterWidthOrNotch))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, 
                        String.Format( "{0} requirement not met: ", filterTypeStr )
                        + "-3dB cutoff point must be less than notch frequency")); //E021
                }
                if ((FSampleActual_kHz > 0) && !(FilterDown3OrCenter <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E022
                }
                if ((FSampleActual_kHz == 0) && !(FilterDown3OrCenter <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E022
                }
                if ((FSampleActual_kHz > 0) && !(FilterWidthOrNotch <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "notch frequency must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E023
                }
                if ((FSampleActual_kHz == 0) && !(FilterWidthOrNotch <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "notch frequency must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E023
                }
            }
            else if (FilterType == CyEFilterType.HIGH_PASS)
            {
                filterTypeStr = "High Pass Filter";
                if (!(FilterWidthOrNotch < FilterDown3OrCenter))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + "notch frequency must be less than -3dB cutoff point")); //E024
                }
                if ((FSampleActual_kHz > 0) && !(FilterDown3OrCenter <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E025
                }
                if ((FSampleActual_kHz == 0) && !(FilterDown3OrCenter <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E025
                }
                if ((FSampleActual_kHz > 0) && !(FilterWidthOrNotch <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "notch frequency must be less than half of the  sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E026
                }
                if ((FSampleActual_kHz == 0) && !(FilterWidthOrNotch <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "notch frequency must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E026
                }
            }
            else if (FilterType == CyEFilterType.BAND_PASS)
            {
                filterTypeStr = "Band Pass Filter";
                double lowCutoff = this.FilterDown3OrCenter;
                double highCutoff = this.FilterWidthOrNotch;
                if (!(lowCutoff < highCutoff))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + "lower -3dB point must be less than the upper -3dB point")); //E027
                }
                if ((FSampleActual_kHz > 0) && !(lowCutoff <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "lower -3dB point must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E028
                }
                if ((FSampleActual_kHz == 0) && !(lowCutoff <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "lower -3dB point must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E028
                }
                if ((FSampleActual_kHz > 0) && !(highCutoff <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "upper -3dB point must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E029
                }
                if ((FSampleActual_kHz == 0) && !(highCutoff <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "upper -3dB point must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E029
                }
                if ((bandPassLowCutoffWarnLimit_kHz > 0) && !(lowCutoff >= bandPassLowCutoffWarnLimit_kHz))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                        String.Format("{0} warning: ", filterTypeStr)
                        + String.Format(
                        "lower -3dB point should be at least 1/{0} the filter sample frequency",
                        BAND_PASS_LOW_CUTOFF_WARN_RATIO)));
                }
                if (!(highCutoff <= lowCutoff * BAND_PASS_CUTOFF_WARN_RATIO))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                        String.Format("{0} warning: ", filterTypeStr)
                        + String.Format(
                        "upper -3dB point should not be over {0} times the upper -3dB point",
                        BAND_PASS_CUTOFF_WARN_RATIO)));
                }
            }
            else if (FilterType == CyEFilterType.BAND_STOP)
            {
                filterTypeStr = "Notch Filter";
                double notch = FilterDown3OrCenter;
                double cutoff = FilterWidthOrNotch;
                const double freqSeparation_percent = 2.0;
                if (!(Math.Abs(notch - cutoff) >= (freqSeparation_percent / 100.0) * notch))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must at least {0}% away from notch frequency",
                        freqSeparation_percent))); //E030
                }
                if ((FSampleActual_kHz > 0) && !(cutoff <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E031
                }
                if ((FSampleActual_kHz == 0) && !(cutoff <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E031
                }
                if ((FSampleActual_kHz > 0) && !(notch <= FSampleActual_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "notch frequency must be less than half of the sampling frequency"
                        + " ({0} kHz)", FSampleActual_kHz.ToString("N2")))); //E032
                }
                if ((FSampleActual_kHz == 0) && !(notch <= FSampleMax_kHz / 2))
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                        String.Format("{0} requirement not met: ", filterTypeStr)
                        + String.Format(
                        "notch frequency must be less than half of the maximum sampling frequency"
                        + " ({0} kHz)", FSampleMax_kHz.ToString("N2")))); //E032
                }
                if (cutoff < BAND_STOP_LOW_CUTOFF_WARN_RATIO * notch)
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                        String.Format("{0} warning: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency should be at least {0:F0}% of notch frequency",
                        BAND_STOP_LOW_CUTOFF_WARN_RATIO * 100)));
                }
                if (cutoff > BAND_STOP_HIGH_CUTOFF_WARN_RATIO * notch)
                {
                    filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                        String.Format("{0} warning: ", filterTypeStr)
                        + String.Format(
                        "-3dB cutoff frequency should not be over {0:F0}% of notch frequency",
                        BAND_STOP_HIGH_CUTOFF_WARN_RATIO * 100)));
                }
            }

            if (this.FilterSample * 1000.0 < CyFilterUtils.GetFilterMinSampleFreq_Hz(this))
            {
                filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                    String.Format(
                    "Filter's oversampling ratio is under {0}.  Accuracy may be affected.",
                    CyFilterUtils.MIN_OSR))); //E033
            }

            // Calculate UAB biquad, reversing coefficients for poly in 1/z
            // See http://dsp.stackexchange.com/
            // question 24293 ensure-stability-against-coefficient-quantization
            var idealBiquad = CyFilterUtils.GetIdealFilterBiquad(this);
            var uabBiquad = GetUabFilterBiquad(this.UabCaps, idealBiquad);
            uabBiquad.Reverse();
            if ((Math.Abs(uabBiquad.Den1) >= 2)
                || (uabBiquad.Den2 < -uabBiquad.Den1 - 1.0)
                || (uabBiquad.Den2 < uabBiquad.Den1 - 1.0)
                || (uabBiquad.Den2 > 1.0))
            {
                filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    String.Format(
                    "UAB filter coefficient quantization has produced an unstable UAB filter."
                    ))); //E034
                filterDRCs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Info,
                    String.Format(
                    "UAB filter denominator 1/z and 1/z**2 coeffs are {0} and {1}.",
                    uabBiquad.Den1, uabBiquad.Den2))); //E035
            }

            scheduler.Solution.Drcs.AddRange(filterDRCs);
        }

        private void UnloadScheduler(CyScheduler scheduler)
        {
            this.AdcClockDivider = (int)scheduler.Solution.AdcClockDivider;

            var channels = scheduler.Solution.Channels;
            for (int chanNum = 0; chanNum < this.ChannelList.Count; chanNum++)
            {
                this.ChannelList[chanNum].ApertureTimer = channels[chanNum].Timer;
                this.ChannelList[chanNum].ActualAcqTime = channels[chanNum].AchievedAperture_Ns;
            }

            var timers = scheduler.Solution.Apertures_AdcClock;
            for (int timerNum = 0; timerNum < CySarRanges.APERTURE_TIMER_COUNT; timerNum++)
            {
                this.ApertureTimers[timerNum] = (timers[timerNum] > 0)
                    ? (int)timers[timerNum]
                    : CySarRanges.APERTURE_TIMER_MIN;
            }

            this.ActualSampleRate = scheduler.Solution.AchievedSampleRate;
            this.ActualAdcClockHz = scheduler.Solution.AchievedAdcClock_Hz;
            this.ActualScanUs = scheduler.Solution.AchievedScanPeriod_Us;

            this.FilterUabClockDivider = scheduler.Solution.UabClockDivider;
            this.FilterUabStartDelay = scheduler.Solution.UabStartDelay_HFClk;

            if (scheduler.Solution.UabClockDivider > 0)
            {
                var uabClock_kHz
                    = (double)scheduler.ClkHF_Hz / (1000.0 * scheduler.Solution.UabClockDivider);
                this.FilterSample
                    = uabClock_kHz / CyScheduler.UAB_FILTER_STEPS;
            }
            else
            {
                this.FilterSample = 1000.0;
            }

            if (this.ChannelList[0].InputMode == CyEInputMode.FILTER_CHAN)
            {
                var idealBiquad = CyFilterUtils.GetIdealFilterBiquad(this);
                try
                {
                    var uabCaps = this.GetUabFilterCaps(idealBiquad);
                    this.UabCaps = uabCaps;
                }
                catch (CapacitorMapperException capex)
                {
                    this.UabCaps = new GTCaps();
                    var capDrc = new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, capex.Message);
                    scheduler.Solution.Drcs.Add(capDrc);
                }
            }
            else if (this.UabCaps == null)
            {
                this.UabCaps = new GTCaps();
            }
        }

        private void DisplaySchedulerErrors(bool isDebug, CyScheduler scheduler)
        {
            // Add filter validation errors
            if (this.ChannelList[0].InputMode == CyEInputMode.FILTER_CHAN)
            {
                var schedErrs = CyScheduler.ValidateSchedule(scheduler);
                foreach (string msg in schedErrs)
                {
                    scheduler.Solution.Drcs.Add(new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, msg));
                }
            }
        }

        private void LoadScheduler(CyScheduler scheduler, CyClockData clockData)
        {
            int normalResolution = 12;
            int altResolution;
            switch (this.AlternateResolution)
            {
                case CyEAlternateResolution.EIGHT_BIT:
                    altResolution = 8;
                    break;
                case CyEAlternateResolution.TEN_BIT:
                    altResolution = 10;
                    break;
                default:
                    altResolution = 10;
                    break;
            }

            foreach (var chanConfig in this.ChannelList)
            {
                bool isBulk = chanConfig.UseAveraging &&
                    this.AveragingMode != CyEAveragingMode.INTERLEAVED_AVG;
                var schedChan = new CyScheduler.CySchedChan(
                    isEnabled: chanConfig.Enabled,
                    resolution:
                        (chanConfig.UseAltResolution) ? altResolution : normalResolution,
                    isFilter: (chanConfig.InputMode == CyEInputMode.FILTER_CHAN),
                    filterType: this.FilterType,
                    minSample_Ns: chanConfig.MinimumAcqTime,
                    isBulkAveraged: isBulk);
                scheduler.InitialChannels.Add(schedChan);
            }

            scheduler.InitialAdcClockDivider =
                (clockData.Divider > 0) ? clockData.Divider : 1;

            scheduler.AdcClockFreqMin_Hz = this.Sar.MinSarFrequency;
            scheduler.AdcClockFreqMax_Hz = this.Sar.MaxSarFrequency;
            

            double adcFrequency = clockData.Frequency * Math.Pow(10, clockData.UnitAsExponent);
            scheduler.ClkHF_Hz = (long)Math.Round(
                adcFrequency * scheduler.InitialAdcClockDivider);

            scheduler.IsOneShot = (this.FreeRunning == true) ? false : true;
            scheduler.TargetScanRate_sps = (long)Math.Round(this.SampleRate);

            switch (this.SamplesAveraged)
            {
                case CyESamplesAveraged.TWO_SAMPLES:
                    scheduler.AverageSamples = 2;
                    break;
                case CyESamplesAveraged.FOUR_SAMPLES:
                    scheduler.AverageSamples = 4;
                    break;
                case CyESamplesAveraged.EIGHT_SAMPLES:
                    scheduler.AverageSamples = 8;
                    break;
                case CyESamplesAveraged.SIXTEEN_SAMPLES:
                    scheduler.AverageSamples = 16;
                    break;
                case CyESamplesAveraged.THIRTYTWO_SAMPLES:
                    scheduler.AverageSamples = 32;
                    break;
                case CyESamplesAveraged.SIXTYFOUR_SAMPLES:
                    scheduler.AverageSamples = 64;
                    break;
                case CyESamplesAveraged.ONETWENTYEIGHT_SAMPLES:
                    scheduler.AverageSamples = 128;
                    break;
                case CyESamplesAveraged.TWOFIFTYSIX_SAMPLES:
                    scheduler.AverageSamples = 256;
                    break;
            }

            scheduler.UabFilterCharFreq_Hz = (long)CyFilterUtils.GetFilterCharFreq_Hz(this);
            scheduler.UabFilterMinSampleFreq_Hz = (long)CyFilterUtils.GetClippedFilterMinSampleFreq_Hz(this);
        }

        /// <summary>
        /// Compute signature for scan schedule.
        /// 
        /// Used to determine if rescheduling changes the schedule.
        /// </summary>
        /// <returns>list of doubles representing the scan schedule</returns>
        public List<double> ScanSignature()
        {
            var signature = new List<double>();

            for (int chanNum = 0; chanNum < this.ChannelList.Count; chanNum++)
            {
                signature.Add(this.ChannelList[chanNum].ApertureTimer);
            }

            for (int timerNum = 0; timerNum < this.ApertureTimers.Count; timerNum++)
            {
                signature.Add(this.ApertureTimers[timerNum]);
            }

            if (this.UabCaps != null)
            {
                signature.Add(this.UabCaps.C1);
                signature.Add(this.UabCaps.C2);
                signature.Add(this.UabCaps.C3);
                signature.Add(this.UabCaps.C4);
                signature.Add(this.UabCaps.CA);
                signature.Add(this.UabCaps.CB);
                signature.Add(this.UabCaps.CP);
                signature.Add(this.UabCaps.CPP);
                signature.Add(this.UabCaps.CPPP);
            }

            return signature;
        }

        /// <summary>
        /// Filter topology type for this configuration.
        /// </summary>
        public CyEFilterTopology FilterTopology(Biquad ideal)
        {
            if (this.FilterType == CyEFilterType.BAND_PASS)
            {
                // Band pass filters use high Q topology.
                return CyEFilterTopology.HIGH_Q;
            }
            else if (ideal.Den0 < 0.0)
            {
                // Transfer functions with Den0 negative
                // use high Q topology.
                return CyEFilterTopology.HIGH_Q;
            }
            else
            {
                // Other filters use low Q topology.
                return CyEFilterTopology.LOW_Q;
            }
        }


        /// <summary>
        /// Calculate G&T capacitor values for specified transfer function.
        /// 
        /// The transfer function depends on the filter topology.
        /// </summary>
        /// <param name="idealBiquad">Target transfer function</param>
        /// <returns>G&T capacitor values</returns>
        public GTCaps GetUabFilterCaps(Biquad idealBiquad)
        {
            switch (this.FilterTopology(idealBiquad))
            {
                case CyEFilterTopology.HIGH_Q:
                    return CyFilterUtils.GetUabFilterCapsHighQ(idealBiquad);
                case CyEFilterTopology.LOW_Q:
                    return CyFilterUtils.GetUabFilterCapsLowQ(idealBiquad);
                default:
                    return CyFilterUtils.GetUabFilterCapsLowQ(idealBiquad);
            }
        }

        /// <summary>
        /// Calculate transfer function for specified UAB capacitor values.
        /// 
        /// The transfer function depends on the filter topology.
        /// </summary>
        /// <param name="caps">G&T capacitor values</param>
        /// <returns>UAB filter transfer function</returns>
        public Biquad GetUabFilterBiquad(GTCaps caps, Biquad ideal)
        {
            switch (this.FilterTopology(ideal))
            {
                case CyEFilterTopology.HIGH_Q:
                    return CyFilterUtils.GetUabFilterBiquadHighQ(caps);
                case CyEFilterTopology.LOW_Q:
                    return CyFilterUtils.GetUabFilterBiquadLowQ(caps);
                default:
                    return CyFilterUtils.GetUabFilterBiquadLowQ(caps);
            }
        }
    }
}
