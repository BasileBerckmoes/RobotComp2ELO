using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using CyDesigner.Extensions.Gde;
namespace Scan_ADC_v2_0
{
    /// <summary>
    /// Scan_ADC scheduler
    /// </summary>
    public class CyScheduler
    {
        const int APERTURE_TIMERS_MAX = 4;
        const long APERTURE_MIN_ADC_CLOCK = 2;
        const long APERTURE_MAX_ADC_CLOCK = 1023;
        const double SAMPLE_FILTER_MIN_NS = CySarRanges.APERTURE_FILTER_MIN_NS;
        const long OVER_SAMPLE_LOW = 190;
        const long OVER_SAMPLE_TARGET = 200;    // From KVCP
        const long OVER_SAMPLE_HIGH = 400;
        const int DEFAULT_RESOLUTION = 12;

        public const int FILTER_SPS_MIN = 3000;
        public const int FILTER_MIN_FS_THRESHOLD_HZ = 160000;

        /// <summary>
        /// Upper bound for filter minimum achievable SPS
        /// to CyFilterUtils.GetFilterMinSampleFreq ratio.
        /// Max measured in test scenarios was 11.97, using 14 for margin.
        /// </summary>
        public const double FILTER_MIN_SPS_TO_MIN_FREQ_UPPER = 14;

        // ADC clock constants.  These are the outer hardware limits.
        // Actual limits depend on the configuration and may be tighter.
        // See AdcClockFreqMin_Hz and AdcClockFreqMax_Hz properties.
        public const long ADC_CLOCK_MAX_HZ = 60000000;
        public const long ADC_CLOCK_MIN_HZ = 1000000;

        // UAB filter clock constants
        public const long UAB_CLOCK_MAX_HZ = 4000000;
        public const long UAB_CLOCK_MIN_HZ = 20000;
        public const long UAB_FILTER_STEPS = 2;

        // From M0S8PASSTK BROS 001-90747 *F section 4.5.2.9.1
        // Scheduled UAB to SAR synchronization, this should be 1.
        // The SAS 001-56977 Rev.*Z Book3 Part II PA Perforce rev #6
        // section 14.3.10.1.1 "Scheduled UAB to SAR synchronization"
        // gives this number as 2.
        // Design states that the SAS will be updated to match the BROS.
        const long SAR_TRIG_DELAY_CLKHFCYCLES = 1;

        // SAR specific settings
        public static int AdcClockDividerMin;
        public static double SampleMin_ns = 194;
        public static int MaxSps;
        public static double AdcClocksNotSampling = 0.5;

        // Input design properties
        public long ClkHF_Hz { get; set; }
        public bool IsExternalAdcClock { get; set; }
        public long InitialAdcClockDivider { get; set; }
        public long AdcClockFreqMin_Hz { get; set; }
        public long AdcClockFreqMax_Hz { get; set; }
        public bool IsOneShot { get; set; }
        public long UabFilterCharFreq_Hz { get; set; }
        public long UabFilterMinSampleFreq_Hz { get; set; }
        public long TargetScanRate_sps { get; set; }
        public long AverageSamples { get; set; }
        public List<CySchedChan> InitialChannels = new List<CySchedChan>();

        // Input optimization parameter properties
        public double ScanDiffCost { get; set; }
        public double UabDiffFarCost { get; set; }
        public double UabDiffNearCost { get; set; }

        public CySchedule Solution { get; set; }

        // Scratchpad properties
        public long ScanPeriod_AdcClock { get; set; }

        /// <summary>
        /// CyScheduler constructor with default settings.
        /// 
        /// Apply new settings as needed after construction.
        /// </summary>
        public CyScheduler()
        {
            this.ClkHF_Hz = 100000000;        // Max IMO
            this.IsExternalAdcClock = false;
            this.AdcClockFreqMin_Hz = ADC_CLOCK_MIN_HZ;
            this.AdcClockFreqMax_Hz = ADC_CLOCK_MAX_HZ;
            this.IsOneShot = false;
            this.UabFilterCharFreq_Hz = 10000;
            this.TargetScanRate_sps = 10000;    // Default target scan rate is 10 kHz
            this.AverageSamples = 2;        // Averaging count reset value.

            this.ScanDiffCost = 100.0;
            this.UabDiffNearCost = 0.1;
            this.UabDiffFarCost = 1.0;
        }

        /// <summary>
        /// Run scheduling algorithm to find the longest possible duration.
        /// 
        /// Does a binary search to find the longest schedule duration
        /// for which scheduling succeeds.
        /// 
        /// Results are stored in channel's aperture timer selection,
        /// aperture timer counts, and for internal ADC clocks, in
        /// the AdcClockDivider property.
        /// </summary>
        public void RunSlowest()
        {
            if (this.InitialChannels[0].IsFilter == false)
            {
                this.Run();
            }
            else
            {
                this.Run();
                if (this.Solution.AchievedSampleRate == 0)
                {
                    long lowTarget_sps = this.TargetScanRate_sps;
                    long highTarget_sps = (long)(this.UabFilterMinSampleFreq_Hz
                        * CyScheduler.FILTER_MIN_SPS_TO_MIN_FREQ_UPPER);
                    if (highTarget_sps > MaxSps)
                    {
                        highTarget_sps = MaxSps;
                    }
                    while (lowTarget_sps < highTarget_sps)
                    {
                        long midTarget_sps = (lowTarget_sps + highTarget_sps + 1) / 2;
                        this.TargetScanRate_sps = midTarget_sps;
                        this.Run();
                        if (this.Solution.AchievedSampleRate == 0)
                        {
                            lowTarget_sps = midTarget_sps;
                        }
                        else
                        {
                            if (highTarget_sps == midTarget_sps)
                            {
                                break;
                            }
                            highTarget_sps = midTarget_sps;
                        }
                    }
                }
            }     
        }

        /// <summary>
        /// Run scheduling algorithm on specified channels.
        /// 
        /// Results are stored in channel's aperture timer selection,
        /// aperture timer counts, and for internal ADC clocks, in
        /// the AdcClockDivider property.
        /// </summary>
        public void Run()
        {
            CySchedule solution;
            bool isScheduleOK = false;

            // Use maximum target filter sample frequency for highpass filters.
            if (this.InitialChannels[0].IsFilter
                && this.InitialChannels[0].FilterType == CyEFilterType.HIGH_PASS)
            {
                long minMax_Hz
                    = UAB_CLOCK_MAX_HZ / (UAB_FILTER_STEPS * OVER_SAMPLE_TARGET);
                if (this.UabFilterCharFreq_Hz < minMax_Hz)
                {
                    this.UabFilterCharFreq_Hz = minMax_Hz;
                }
            }

            // Select scheduling algorithm.
            if (this.IsOneShot == true)
            {
                isScheduleOK = ScheduleAdcOneShot(out solution);
            }
            else if ((this.InitialChannels[0].IsFilter == false)
                && (this.IsExternalAdcClock == true))
            {
                isScheduleOK = ScheduleAdcOnlyWithFixedAdcClock(
                    this.InitialAdcClockDivider, out solution);
            }
            else if ((this.InitialChannels[0].IsFilter == false)
                && (this.IsExternalAdcClock == false))
            {
                isScheduleOK = ScheduleAdcOnlyWithInternalAdcClock(out solution);
            }
            else if (this.IsExternalAdcClock == true)
            {
                isScheduleOK = ScheduleUabAdcWithFixedAdcClockV2(
                    this.InitialAdcClockDivider, out solution);
            }
            else
            {
                isScheduleOK = ScheduleUabAdcWithInternalAdcClock(out solution);
            }

            // If scan period <= 0, scheduling did not succeed.
            this.ScanPeriod_AdcClock = FindMappedScanAdcClocks(solution);
            if (this.ScanPeriod_AdcClock <= 0)
            {
                isScheduleOK = false;
            }

            // Calculate info for GUI displays.
            if (isScheduleOK)
            {
                solution.AchievedSampleRate = (long)Math.Round(
                    1.0 / (this.ScanPeriod_AdcClock * AdcClockPeriod_s(solution.AdcClockDivider)));
                solution.AchievedScanPeriod_Us = 1e6 / solution.AchievedSampleRate;
                solution.AchievedAdcClock_Hz = this.ClkHF_Hz / solution.AdcClockDivider;
                for (int chanNum = 0; chanNum < solution.Channels.Count; chanNum++)
                {
                    double adcClocks = solution.Channels[chanNum].MappedSample_AdcClock;
                    adcClocks -= AdcClocksNotSampling;
                    double achievedAperture_Ns
                        = Math.Round(1e9 * adcClocks * AdcClockPeriod_s(solution.AdcClockDivider));
                    solution.Channels[chanNum].AchievedAperture_Ns = achievedAperture_Ns;
                }
            }
            else
            {
                solution.AchievedSampleRate = 0;
                solution.AchievedScanPeriod_Us = 0;
                solution.AchievedAdcClock_Hz = 0;
                for (int chanNum = 0; chanNum < solution.Channels.Count; chanNum++)
                {
                    solution.Channels[chanNum].AchievedAperture_Ns = 0;
                }
            }

            this.Solution = solution;
        }
        
        /// <summary>
        /// Validates SAR/UAB scheduling.
        /// 
        /// </summary>
        /// <param name="channels">Channel information for scheduler</param>
        /// <param name="timers">Returns list of validation errors.</param>
        public static List<string> ValidateSchedule(CyScheduler scheduler)
        {
            List<string> validationResults = new List<string>();
           
            const long UAB_LAST_DEFINED_STEP = 1;
            const long UAB_NUMBER_OF_PHASES = UAB_LAST_DEFINED_STEP+1;
            const long UAB_LAST_VALID_STEP = 0;

            const int FILTER_CH_NUM = 0;
            var chan = scheduler.Solution.Channels[FILTER_CH_NUM];
            long sampleTime_clkSarCycles = chan.MappedSample_AdcClock;
            long autoZeroTime_clkSarCycles = chan.AutoZero_AdcClock;
            long OFFSET_CLKSARCYCLES = 0; //This is zero because FILTER_CH_NUM==0 

            if (scheduler.IsOneShot == true)
            {
                validationResults.Add("Filter is not supported in single shot mode.");
            }
            //from SAS Scheduled UAB to SAR synchronization dly equation
            const long AUTOZEROTIME_EXPECTED = 1;
            if( !(autoZeroTime_clkSarCycles==AUTOZEROTIME_EXPECTED) )
            {
                validationResults.Add(String.Format(
                    "Internal error: autoZeroTime ({0}) is different than expected {1}.",
                    autoZeroTime_clkSarCycles, AUTOZEROTIME_EXPECTED));
            }

            long clk_sar = scheduler.Solution.AdcClockDivider; // hf clock cycles per SAR clock
            long clk_uab = scheduler.Solution.UabClockDivider; // hf clock cycles per UAB clock

            if( !(clk_sar >= 2) )
            {
                validationResults.Add(String.Format(
                    "Internal error: SAR clock expressed in clk_hf cycles must be >=2; actual={0}",
                    clk_sar));  
            }
            if( !(clk_uab >= 2) )
            {
                validationResults.Add(String.Format(
                    "Internal error: UAB clock expressed in clk_hf cycles must be >=2; actual={0}",
                    clk_uab));
            }

            double clkHfFreq_Hz = scheduler.ClkHF_Hz;
            double clkSarFreq_Hz = clkHfFreq_Hz / scheduler.Solution.AdcClockDivider;
            double clkUabFreq_Hz = clkHfFreq_Hz / scheduler.Solution.UabClockDivider;

            long sarTriggerPeriod_clkHfCycles = scheduler.ScanPeriod_AdcClock * clk_sar;
            long uabPeriod_clkHfCycles = UAB_NUMBER_OF_PHASES * clk_uab;

            //=MOD((((offset+st+1)*clk_sar)-2-((lastValid+1)*clk_uab)),MIN(uabPeriod,sarTrigPeriod))
            var modVisor = Math.Min(uabPeriod_clkHfCycles, sarTriggerPeriod_clkHfCycles);
            if (clkSarFreq_Hz != 0 && modVisor != 0)
            {
                long dly_actual = scheduler.Solution.UabStartDelay_HFClk;
                long dly_expected =
                    (OFFSET_CLKSARCYCLES + sampleTime_clkSarCycles + autoZeroTime_clkSarCycles) * clk_sar
                    - SAR_TRIG_DELAY_CLKHFCYCLES
                    - (UAB_LAST_VALID_STEP + 1) * clk_uab;
                dly_expected %= modVisor;
                while (dly_expected < 0)
                {
                    dly_expected += modVisor;
                }



                if( !( dly_actual >= 1) )
                {
                    validationResults.Add(String.Format(
                        "Internal error: UAB STARTUP_DELAY must be >= 1 ; actual is {0}",
                        dly_actual) );  
                }

                /* Check the alignment of uab-valid and sar-sample. */
                if( !(dly_actual == dly_expected) )
                {
                    validationResults.Add(String.Format(
                        "Internal error: Scheduled StartDelay ({0}) is different from the expected {1}.",
                        dly_actual, dly_expected) );
                }

                /* Check that all uab periods sync with sar (integer multiples of each other) */
                if( !((sarTriggerPeriod_clkHfCycles % uabPeriod_clkHfCycles) == 0L) )
                {
                    validationResults.Add(String.Format(
                        "Internal error: SAR-to-UAB ratio is not an integer.({0}:{1})",
                        sarTriggerPeriod_clkHfCycles, uabPeriod_clkHfCycles));
                }
            }
            else
            {
                if (clkSarFreq_Hz == 0)
                {
                    validationResults.Add("Internal error: Sar frequency was 0 Hz during validation.");
                }
                if (uabPeriod_clkHfCycles == 0)
                {
                    validationResults.Add("Internal error: Uab period was 0 during validation.");
                }
                if (sarTriggerPeriod_clkHfCycles == 0)
                {
                    validationResults.Add("Internal error: Sar period was 0 during validation.");
                }
            }
            
            return validationResults;
        }

        bool ScheduleAdcOneShot(out CySchedule solution)
        {
            solution = new CySchedule(this.InitialChannels);

            if (this.IsExternalAdcClock == false)
            {
                solution.AdcClockDivider = AdcClockDividerMin;
            }
            else
            {
                solution.AdcClockDivider = this.InitialAdcClockDivider;
            }
            solution.AdcClockDivider = ClipAdcClockDividerToLimits(solution.AdcClockDivider);

            // This method must be called to initialize channel sample
            // and conversion ADC clock counts.
            long idealMinScanAdcClocks = FindMinScanAdcClocks(solution);

            // Set up data structures for optimization without padding.
            var chanTimesNoPad = GetChannelTimingInfo(solution);
            chanTimesNoPad.Sort();
            var apertureClocksNoPad = new List<long>(solution.Apertures_AdcClock);

            // Find solution with minimum ADC clocks without padding.
            OptimizeApertures(chanTimesNoPad, 0, chanTimesNoPad.Count,
                ref apertureClocksNoPad, 0, apertureClocksNoPad.Count);
            solution.Apertures_AdcClock = apertureClocksNoPad;
            SetChannelTimers(solution, 0, solution.Apertures_AdcClock.Count);

            // Don't need UAB clock divider or startup delay as there is no filter.
            solution.UabClockDivider = 0;
            solution.UabStartDelay_HFClk = 0;

            // Report success.
            return true;
        }

        public bool ScheduleAdcOnlyWithInternalAdcClock(out CySchedule solution)
        {
            long adcClockDivider = this.InitialAdcClockDivider;
            if (this.IsExternalAdcClock == false)
            {
                adcClockDivider = SelectAdcClockDivider();
            }

            bool isScheduleOK = ScheduleAdcOnlyWithFixedAdcClock(
                adcClockDivider, out solution);

            return isScheduleOK;
        }

        /// <summary>
        /// Run scheduling algorithm on specified channels.
        /// 
        /// This method requires that no channels use UAB filters.
        /// 
        /// Results are stored in channel's aperture timer selection,
        /// aperture timer counts, and for internal ADC clocks, in
        /// the AdcClockDivider property.
        /// </summary>
        /// <param name="channels">Channel information for scheduler</param>
        /// <param name="timers">Returns aperture timer settings.</param>
        public bool ScheduleAdcOnlyWithFixedAdcClock(
            long adcClockDivider, out CySchedule solution)
        {
            solution = new CySchedule(this.InitialChannels);
            solution.AdcClockDivider = adcClockDivider;

            // This method must be called to initialize channel sample
            // and conversion ADC clock counts.
            long idealMinScanAdcClocks = FindMinScanAdcClocks(solution);

            // Set up data structures for optimization without padding.
            var chanTimesNoPad = GetChannelTimingInfo(solution);
            chanTimesNoPad.Sort();
            var apertureClocksNoPad = new List<long>(solution.Apertures_AdcClock);

            // Set up data structures for optimization with padding.
            var chanTimesPad = new List<CyTimingInfo>(chanTimesNoPad);
            var apertureClocksPad = new List<long>(apertureClocksNoPad);
            int padIndex = FindPaddingChannel(chanTimesPad);
            if (padIndex != 0)
            {
                var padChan = chanTimesPad[padIndex];
                chanTimesPad.RemoveAt(padIndex);
                chanTimesPad.Insert(0, padChan);
            }

            // Find solution with minimum ADC clocks without padding.
            OptimizeApertures(chanTimesNoPad, 0, chanTimesNoPad.Count,
                ref apertureClocksNoPad, 0, apertureClocksNoPad.Count);
            solution.Apertures_AdcClock = apertureClocksNoPad;
            SetChannelTimers(solution, 0, solution.Apertures_AdcClock.Count);
            long mappedMinScanAdcClocksNoPad = FindMappedScanAdcClocks(solution);

            // Find solution with minimum ADC clocks,
            // reserving one aperture timer for padding.
            OptimizeApertures(chanTimesPad, 1, chanTimesPad.Count,
                ref apertureClocksPad, 1, apertureClocksPad.Count);
            apertureClocksPad[0] = chanTimesPad[0].IdealSample_AdcClock;
            solution.Apertures_AdcClock = apertureClocksPad;
            SetChannelTimers(solution, 1, solution.Apertures_AdcClock.Count);
            solution.Channels[chanTimesPad[0].ChannelNum].Timer = 0;
            long mappedMinScanAdcClocksPad = FindMappedScanAdcClocks(solution);

            long targetScanAdcClocks
                = AdcClocks(this.TargetScanRate_sps, solution.AdcClockDivider);

            if (mappedMinScanAdcClocksPad <= targetScanAdcClocks)
            {
                // TODO: What if more than one channel needs to be padded?
                long padAmount = targetScanAdcClocks - mappedMinScanAdcClocksPad;
                if (solution.Channels[chanTimesPad[0].ChannelNum].IsBulkAveraged)
                {
                    padAmount += this.AverageSamples / 2;
                    padAmount /= this.AverageSamples;
                }
                solution.Apertures_AdcClock[0] += padAmount;
                solution.Apertures_AdcClock[0]
                    = Math.Min(solution.Apertures_AdcClock[0], APERTURE_MAX_ADC_CLOCK);
            }
            else if (Math.Abs(mappedMinScanAdcClocksNoPad - targetScanAdcClocks)
                < Math.Abs(mappedMinScanAdcClocksPad - targetScanAdcClocks))
            {
                // If unpadded timers overshoot less than padded timers,
                // switch to unpadded timers.
                solution.Apertures_AdcClock = apertureClocksNoPad;
                SetChannelTimers(solution, 0, solution.Apertures_AdcClock.Count);
            }
            else
            {
                // Stick with padded timers without adding padding.
            }

            // Don't need UAB clock divider or startup delay as there is no filter.
            solution.UabClockDivider = 0;
            solution.UabStartDelay_HFClk = 0;

            // Report success.
            return true;
        }

        /// <summary>
        /// Run scheduling algorithm on specified channels.
        /// 
        /// This method requires that channel 0 uses a UAB filter and that
        /// the ADC clock divider is not specified.
        /// 
        /// Results are stored in channel's aperture timer selection,
        /// aperture timer counts, and for internal ADC clocks, in
        /// the AdcClockDivider property.
        /// </summary>
        public bool ScheduleUabAdcWithInternalAdcClock(out CySchedule solution)
        {
            // TODO: Optimize filter quality over a range of ADC clock dividers.
            long adcClockDivider = SelectAdcClockDivider();
            if (adcClockDivider % 2 != 0)
            {
                // ADC clock divider must be even to match two phase UAB filter.
                // TODO: IS THIS TRUE????
                adcClockDivider++;
            }

            bool isScheduleOK = ScheduleUabAdcWithFixedAdcClockV2(
                adcClockDivider, out solution);

            return isScheduleOK;
        }

        /// <summary>
        /// Run scheduling algorithm on specified channels.
        /// 
        /// This method requires that channel 0 uses a UAB filter and that the
        /// ADC clock divider is specified.
        /// 
        /// A non-filter channel is used for padding, if one exists.
        /// 
        /// Results are stored in channel's aperture timer selection,
        /// aperture timer counts, and for internal ADC clocks, in
        /// the AdcClockDivider property.
        /// </summary>
        public bool ScheduleUabAdcWithFixedAdcClockV2(
            long adcClockDivider, out CySchedule solution)
        {
            solution = new CySchedule(this.InitialChannels);
            solution.AdcClockDivider = adcClockDivider;

            long idealScanMin_AdcClock = FindMinScanAdcClocks(solution);

            // Set up data structures for optimization with padding.
            var chanTimeInfo = GetChannelTimingInfo(solution);

            // Filter channel index is always 0.
            int filterIndex = 0;

            // If there is only the filter channel, use it for padding,
            // otherwise use another channel.
            int padIndex = FindPaddingChannel(chanTimeInfo, filterIndex, chanTimeInfo.Count);
            if (padIndex > filterIndex + 1)
            {
                var padChan = chanTimeInfo[padIndex];
                chanTimeInfo.RemoveAt(padIndex);
                chanTimeInfo.Insert(filterIndex + 1, padChan);
                padIndex = filterIndex + 1;
            }
            int afterPadCount = chanTimeInfo.Count - (padIndex + 1);
            if (afterPadCount > 0)
            {
                chanTimeInfo.Sort(padIndex + 1, afterPadCount, null);
            }
            long padSampleCount = chanTimeInfo[padIndex].SampleCount;

            var apertures_AdcClock = new List<long>(solution.Apertures_AdcClock);

            // Find solution with minimum ADC clocks,
            // reserving aperture timer(s) for filter and padding.
            OptimizeApertures(chanTimeInfo, padIndex + 1, chanTimeInfo.Count,
                ref apertures_AdcClock, padIndex + 1, apertures_AdcClock.Count);
            apertures_AdcClock[filterIndex] = chanTimeInfo[filterIndex].IdealSample_AdcClock;
            apertures_AdcClock[padIndex] = chanTimeInfo[padIndex].IdealSample_AdcClock;
            solution.Apertures_AdcClock = apertures_AdcClock;
            SetChannelTimers(solution, padIndex + 1, solution.Apertures_AdcClock.Count);
            solution.Channels[chanTimeInfo[filterIndex].ChannelNum].Timer = filterIndex;
            solution.Channels[chanTimeInfo[padIndex].ChannelNum].Timer = padIndex;

            // Find minimum number of ADC clocks per scan.
            long mappedScanMin_AdcClock = FindMappedScanAdcClocks(solution);

            // Express max UAB clock frequency as a min UAB clock period in HF clocks.
            long uabClkPeriodFloor_HFClks = (long)Math.Ceiling(
                (double)this.ClkHF_Hz / UAB_CLOCK_MAX_HZ);

            // Express min UAB clock frequency as a max UAB clock period in HF clocks.
            // sample freq must be greater than or equal to UAB_CLOCK_MIN_HZ
            // Incorrect way: round up period (round down frequency:
            // violates Nyquist-Shannon sampling theorem)
            // Correct way:   Round down period (round up frequency)
            long filterUabClockMin_Hz = Math.Max(
                UAB_CLOCK_MIN_HZ, this.UabFilterMinSampleFreq_Hz * UAB_FILTER_STEPS);
            long uabClkPeriodCeiling_HFClks = (long)Math.Floor(
                (double)this.ClkHF_Hz / filterUabClockMin_Hz);

            // Find minimum cost valid ADC scan padding and UAB sampling frequency.
            double bestCost = -1.0;
            long bestPad = 0;
            long bestUabPeriod_HFClks = 0;

            // UAB clock period must be longer than ADC's UAB channel minimum sample time.
            long adcSampleUabChan_AdcClks = apertures_AdcClock[filterIndex];

            // Loop over valid padding amounts.
            long padMax = APERTURE_MAX_ADC_CLOCK + 1 - apertures_AdcClock[padIndex];
            for (long pad = 0; pad < padMax; pad++)
            {
                // UAB clock period must be longer than ADC's UAB channel sample time.
                long uabClkPeriodMin_HFClks
                    = (adcSampleUabChan_AdcClks + 1) * solution.AdcClockDivider;

                if (uabClkPeriodMin_HFClks < uabClkPeriodFloor_HFClks)
                {
                    uabClkPeriodMin_HFClks = uabClkPeriodFloor_HFClks;
                }

                // UAB clock period must not be longer than half the total ADC scan period.
                long scanPeriod_AdcClks = mappedScanMin_AdcClock + pad * padSampleCount;
                long uabClkPeriodMax_HFClks = 1 + (scanPeriod_AdcClks * solution.AdcClockDivider) / 2;
                if (uabClkPeriodMax_HFClks > uabClkPeriodCeiling_HFClks)
                {
                    uabClkPeriodMax_HFClks = uabClkPeriodCeiling_HFClks;
                }

                // Loop over possible UAB clock periods.
                for (long uabClkPeriod_HFClks = uabClkPeriodMin_HFClks;
                    uabClkPeriod_HFClks <= uabClkPeriodMax_HFClks;
                    uabClkPeriod_HFClks++)
                {
                    // UAB filter sample period (twice UAB clock period)
                    // must divide evenly into total scan period.
                    if ((scanPeriod_AdcClks * solution.AdcClockDivider)
                        % (2 * uabClkPeriod_HFClks) == 0)
                    {
                        // Either ADC clock must be a multiple of UAB clock or vice versa
                        // so that the two clocks can be aligned.
                        if ((solution.AdcClockDivider % uabClkPeriod_HFClks == 0)
                            || (uabClkPeriod_HFClks % solution.AdcClockDivider == 0))
                        {
                            // Save least cost valid solution.
                            double cost = AdcUabCost(scanPeriod_AdcClks, uabClkPeriod_HFClks,
                                solution.AdcClockDivider);
                            if ((bestCost < 0)
                                || (cost < bestCost)
                                || ((cost == bestCost) && (bestUabPeriod_HFClks < uabClkPeriod_HFClks)))
                            {
                                bestCost = cost;
                                bestPad = pad;
                                bestUabPeriod_HFClks = uabClkPeriod_HFClks;
                            }
                        }
                    }
                }
            }

            // Report error if scheduling failed to find a solution.
            if (bestCost == -1)
            {
                solution.Drcs.Add(
                    new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    "Failed to synchronize ADC and UAB filter schedules.\n"
                    + "Adjust filter parameters or external aclk."));
            }

            bool isScheduleOK = (bestCost == -1) ? false : true;

            if (isScheduleOK)
            {
                UpdateSolutionUabParameters(solution, filterIndex, padIndex, padSampleCount,
                    mappedScanMin_AdcClock, bestPad, bestUabPeriod_HFClks);
            }

            return isScheduleOK;
        }

        private static void UpdateSolutionUabParameters(
            CySchedule solution, int filterIndex, int padIndex, long padSampleCount,
            long mappedScanMin_AdcClock, long bestPad, long bestUabPeriod_HFClks)
        {
            // Save UAB clock divider.
            solution.UabClockDivider = bestUabPeriod_HFClks;

            // Adjust padding channel timer by best pad found.
            solution.Apertures_AdcClock[padIndex] += bestPad;

            // Shift UAB start so that filter output is valid at the end of the SAR sample.
            // See 001-56977 Book3 Part II PA Scheduled UAB to SAR Synchronization
            long offset = 0;    // Filter uses SAR channel 0, which has offset 0.
            long totalScanPeriod_AdcClks = mappedScanMin_AdcClock + bestPad * padSampleCount;
            long totalScanPeriod_HFClks = totalScanPeriod_AdcClks * solution.AdcClockDivider;
            long totalUabPeriod_HFClks = UAB_FILTER_STEPS * solution.UabClockDivider;
            long lastValidStep = 0; // Valid is phi1 which is high during SRAM address 0.
            long period = Math.Min(totalUabPeriod_HFClks, totalScanPeriod_HFClks);
            solution.UabStartDelay_HFClk
                = (offset + solution.Apertures_AdcClock[filterIndex] + 1)
                * solution.AdcClockDivider
                - SAR_TRIG_DELAY_CLKHFCYCLES
                - (lastValidStep + 1) * solution.UabClockDivider;
            solution.UabStartDelay_HFClk %= period;
            while (solution.UabStartDelay_HFClk <= 0)
            {
                solution.UabStartDelay_HFClk += period;
            }
        }

        /// <summary>
        /// Calculate ADC clock divider for internal ADC clocks.
        /// 
        /// Results are stored in the AdcClockDivider property.
        /// </summary>
        public long SelectAdcClockDivider()
        {
            // Find minimum sample time and ADC conversion clock count for scan.
            double minScanSample_ns;
            double minScanConv_AdcClock;
            FindAdcClockParameters(out minScanSample_ns, out minScanConv_AdcClock);
            double minScanSampleTime_s = minScanSample_ns / 1e9;

            // Select a clock divider that will use about 512 padding clock
            // periods to hit the target clock rate.
            double targetScanPeriod_s = 1.0 / (double)this.TargetScanRate_sps;
            double allowedConversionTime_s = targetScanPeriod_s - minScanSampleTime_s;
            double adcClockHz = (minScanConv_AdcClock + 512) / allowedConversionTime_s;
            long adcClockDivider = (long)Math.Round(this.ClkHF_Hz / adcClockHz);

            adcClockDivider = ClipAdcClockDividerToLimits(adcClockDivider);

            return adcClockDivider;
        }

        private long ClipAdcClockDividerToLimits(long adcClockDivider)
        {
            // Convert min frequency limit to max divider limit.
            long minFreq_Hz = Math.Max(
                this.AdcClockFreqMin_Hz, CyScheduler.ADC_CLOCK_MIN_HZ);
            double maxDividerFrac= Math.Round((double)this.ClkHF_Hz / minFreq_Hz, 3);
            long maxDivider = (long)Math.Floor(maxDividerFrac);

            // Convert max frequency limit to min divider limit.
            long maxFreq_Hz = Math.Min(
                this.AdcClockFreqMax_Hz, CyScheduler.ADC_CLOCK_MAX_HZ);
            double minDividerFrac = Math.Round((double)this.ClkHF_Hz / maxFreq_Hz, 3);
            long minDivider = (long)Math.Ceiling(minDividerFrac);

            // Apply frequency divider limits.
            adcClockDivider = Math.Min(adcClockDivider, maxDivider);
            adcClockDivider = Math.Max(adcClockDivider, minDivider);

            // Aplly hardware divider limit.
            adcClockDivider = Math.Max(adcClockDivider, AdcClockDividerMin);

            return adcClockDivider;
        }

        /// <summary>
        /// Recursive min cost optimizer.
        ///
        /// "Cost" is the difference between the number of ADC clocks used
        /// by  aperture timers to cover the given channels and the number of ADC
        /// clocks that would be required if each channel had its own timer.
        /// 
        /// The channel timing info list must be sorted.
        /// 
        /// Each recursive call consumes one aperture timer and zero or more
        /// channels.  The recursion terminates when there are either no timers
        /// or no channels left.
        /// 
        /// Returns min cost timer settings in apertureClocks list.
        /// </summary>
        /// <param name="chanTimes">Channel timing info sorted by min acq time</param>
        /// <param name="chanBase">Lower channel limit</param>
        /// <param name="chanTop">Upper channel limit (half-open interval)</param>
        /// <param name="apertureClocks">Local min cost timer settings</param>
        /// <param name="apertureBase">Lower aperture timer limit</param>
        /// <param name="apertureTop">Upper aperture timer limit (half-open interval)</param>
        /// <returns>Min cost found</returns>
        public long OptimizeApertures(
            List<CyTimingInfo> chanTimes, int chanBase, int chanTop,
            ref List<long> apertureClocks, int apertureBase, int apertureTop)
        {
            Debug.Assert(chanBase <= chanTop,
                "OptimizeApertures chanBase > chanTop");
            Debug.Assert(apertureBase < apertureTop,
                "OptimizeApertures: apretureBase >= apertureTop");

            long cost = 0;

            /* Base case */
            if (chanTop == chanBase)
            {
                // All channels have been processed.  Zero out remainder of timer list.
                for (int index = apertureBase; index < apertureTop; index++)
                {
                    apertureClocks[index] = 0;
                }
            }
            else if (apertureBase + 1 == apertureTop)
            {
                // There is only one timer left.
                // Use it to cover all the remaining channels.
                long apertureTime = chanTimes[chanTop - 1].IdealSample_AdcClock;
                apertureClocks[apertureBase] = apertureTime;
                cost = CalcApertureCost(chanTimes, chanBase, chanTop, apertureTime);
            }
            else
            {
                // Loop over possible timer values making recursive calls.
                // Save the best found.
                long minCost = Int64.MaxValue;
                var minClocks = new List<long>(apertureClocks);

                int chanNum = chanBase;
                while (chanNum < chanTop)
                {
                    long apertureTime = chanTimes[chanNum].IdealSample_AdcClock;
                    int nextChanNum = chanNum;
                    while (nextChanNum < chanTop
                        && chanTimes[nextChanNum].IdealSample_AdcClock == apertureTime)
                    {
                        nextChanNum++;
                    }

                    var branchClocks = new List<long>(apertureClocks);
                    long branchCost
                        = CalcApertureCost(chanTimes, chanBase, nextChanNum, apertureTime)
                        + OptimizeApertures(chanTimes, nextChanNum, chanTop,
                            ref branchClocks, apertureBase + 1, apertureTop);
                    if (minCost > branchCost)
                    {
                        minCost = branchCost;
                        minClocks = branchClocks;
                        minClocks[apertureBase] = apertureTime;
                    }

                    chanNum = nextChanNum;
                }

                cost = minCost;
                for (int index = apertureBase; index < apertureTop; index++)
                {
                    apertureClocks[index] = minClocks[index];
                }
            }

            return cost;
        }

        /// <summary>
        /// Calculate cost of covering the specified channels with one timer setting.
        /// 
        /// Requires channel ideal sample times to have been calculated.
        /// </summary>
        /// <param name="chanTimes">Channel timing info sorted by min acq time</param>
        /// <param name="chanBase">Lower channel limit</param>
        /// <param name="chanTop">Upper channel limit (half-open interval)</param>
        /// <param name="aperture">Aperture timer setting in ns</param>
        /// <returns></returns>
        public long CalcApertureCost(
            List<CyTimingInfo> chanTimes, int chanBase, int chanTop,
            long aperture)
        {
            Debug.Assert(chanBase <= chanTop);

            long cost = 0;

            for (int chanNum = chanBase; chanNum < chanTop; chanNum++)
            {
                Debug.Assert(aperture >= chanTimes[chanNum].IdealSample_AdcClock);
                long chanExcess = aperture - chanTimes[chanNum].IdealSample_AdcClock;
                chanExcess *= chanTimes[chanNum].SampleCount;
                if (chanTimes[chanNum].IsEnabled == false)
                {
                    chanExcess = 0;
                }
                cost += chanExcess;
            }

            return cost;
        }

        /// <summary>
        /// Extract timing info for optimization from channel data.
        /// </summary>
        /// <param name="solution" Current scheduling solution </param>
        /// <returns>List of timing info corresponding to channels.</returns>
        private List<CyTimingInfo> GetChannelTimingInfo(CySchedule solution)
        {
            var chanTimings = new List<CyTimingInfo>();

            for (int chanNum = 0; chanNum < solution.Channels.Count; chanNum++)
            {
                var chan = solution.Channels[chanNum];
                var info = new CyTimingInfo(
                    chan.MinSample_AdcClock,
                    (chan.IsBulkAveraged) ? this.AverageSamples : 1,
                    chan.IsFilter,
                    chanNum,
                    chan.IsEnabled);
                chanTimings.Add(info);
            }

            return chanTimings;
        }

        /// <summary>
        /// Find the minimum number of ADC clocks required to scan all channels.
        /// 
        /// Also stores the minimum number of ADC clocks in the channel table.
        /// 
        /// Assumes each channel has its own aperture timer.
        /// </summary>
        /// <param name="solution" Current scheduling solution </param>
        /// <returns>Minimum number of ADC clocks to cover channels</returns>
        private long FindMinScanAdcClocks(CySchedule solution)
        {
            long minScanAdcClocks = 0;

            foreach (var chan in solution.Channels)
            {
                chan.MinSample_AdcClock = this.ApertureAdcClocks(
                    chan.ApertureMin_Ns, solution.AdcClockDivider);
                chan.MinChannel_AdcClock
                    = chan.AutoZero_AdcClock
                    + chan.MinSample_AdcClock
                    + chan.NonOverlap_AdcClock
                    + chan.Conversion_AdcClock;
                chan.MinTotal_AdcClock = chan.MinChannel_AdcClock;
                if (chan.IsBulkAveraged)
                {
                    chan.MinTotal_AdcClock *= this.AverageSamples;
                }
                if (chan.IsEnabled == false)
                {
                    chan.MinTotal_AdcClock = 0;
                }
                minScanAdcClocks += chan.MinTotal_AdcClock;
            }
            return minScanAdcClocks;
        }

        /// <summary>
        /// Find number of ADC clocks required for scan with specified aperture timers.
        /// </summary>
        /// <param name="solution" Current scheduling solution </param>
        /// <returns>Number of ADC clock</returns>
        private long FindMappedScanAdcClocks(CySchedule solution)
        {
            long mappedScanAdcClocks = 0;

            foreach (var chan in solution.Channels)
            {
                FindMappedChannelScanAdcClocks(chan, solution.Apertures_AdcClock);
                mappedScanAdcClocks += chan.MappedTotal_AdcClock;
            }
            return mappedScanAdcClocks;
        }

        private void FindMappedChannelScanAdcClocks(
            CySchedChan chan, List<long> apertures_AdcClock)
        {
            chan.MappedSample_AdcClock = apertures_AdcClock[chan.Timer];

            // See 001-63805 Rev AB section 4.2.4 
            // Timing Requirements and Diagrams
            // Note that auto zero is actually plus 0.5 clocks
            // and sample is minus 0.5 clocks.
            chan.MappedChannel_AdcClock
                = chan.AutoZero_AdcClock
                + chan.MappedSample_AdcClock
                + chan.NonOverlap_AdcClock
                + chan.Conversion_AdcClock;

            chan.MappedTotal_AdcClock = chan.MappedChannel_AdcClock;
            if (chan.IsBulkAveraged)
            {
                chan.MappedTotal_AdcClock *= this.AverageSamples;
            }
            if (chan.IsEnabled == false)
            {
                chan.MappedTotal_AdcClock = 0;
            }
        }

        /// <summary>
        /// Find minimum number of nanoseconds and ADC clocks required to scan all channels.
        /// 
        /// Assume each channel has its own aperture timer.
        /// </summary>
        /// <param name="minScanSampleNs">Minimum number of nanoseconds for scan</param>
        /// <param name="minScanConvAdcClocks">Minimum number of ADC clocks for scan</param>
        private void FindAdcClockParameters(
            out double minScanSampleNs, out double minScanConvAdcClocks)
        {
            minScanSampleNs = 0;
            minScanConvAdcClocks = 0;

            foreach (var chan in this.InitialChannels)
            {
                double minSampleNs = chan.ApertureMin_Ns;
                double minConvAdcClocks = 0.5;      // For extra half ADC clock in aperture timer.
                minConvAdcClocks += chan.Conversion_AdcClock;

                if (chan.IsBulkAveraged)
                {
                    minSampleNs *= this.AverageSamples;
                    minConvAdcClocks *= this.AverageSamples;
                }
                minScanSampleNs += minSampleNs;
                minScanConvAdcClocks += minConvAdcClocks;
            }
        }

        /// <summary>
        /// Assign best fit aperture timers to specified channels.
        /// </summary>
        /// <param name="solution" Current scheduling solution </param>
        /// <param name="timerBase">Lower timer limit</param>
        /// <param name="timerTop">Upper timer limit (half-open interval)</param>
        private void SetChannelTimers(CySchedule solution, int timerBase, int timerTop)
        {
            foreach (var chan in solution.Channels)
            {
                SetTimer(solution, chan, timerBase, timerTop);
            }
        }

        /// <summary>
        /// Assign best fit aperture timer to channel
        /// </summary>
        /// <param name="solution" Current scheduling solution </param>
        /// <param name="chan">Channel</param>
        /// <param name="timerBase">Lower timer limit</param>
        /// <param name="timerTop">Upper timer limit (half-open interval)</param>
        private void SetTimer(CySchedule solution, CySchedChan chan, int timerBase, int timerTop)
        {
            for (int timer = timerBase; timer < timerTop; timer++)
            {
                if (chan.MinSample_AdcClock <= solution.Apertures_AdcClock[timer])
                {
                    chan.Timer = timer;
                    break;
                }
            }
        }

        /// <summary>
        /// Find number of ADC clocks required for target scan frequency
        /// </summary>
        /// <param name="targetFrequency">Per-channel scan frequency</param>
        /// <param name="adcClockDivider" ADC clock divider for current schedule</param>
        /// <returns>Number of ADC clocks corresponding to target frequency</returns>
        public long AdcClocks(long targetFrequency, long adcClockDivider)
        {
            double adcFrequency = (double)this.ClkHF_Hz / adcClockDivider;
            double clocks = adcFrequency / targetFrequency;
            clocks = Math.Ceiling(clocks);
            return (long)clocks;
        }

        /// <summary>
        /// Calculate number of ADC clocks required for specified sample time.
        /// </summary>
        /// <param name="apertureNs">Sample time in nanoseconds</param>
        /// <param name="adcClockDivider" ADC clock divider for current schedule</param>
        /// <returns>Number of ADC clocks required to cover sample time</returns>
        public long ApertureAdcClocks(double apertureNs, long adcClockDivider)
        {
            // Convert to ns for easier debugging.
            double adcClockNs = 1e9 * AdcClockPeriod_s(adcClockDivider);
            // Find number of clocks required to cover aperture period.
            double apertureClocks = apertureNs / adcClockNs;
            // Actual sample time is 1/2 clock less than specified
            // See SAR_v2 SAMPLE_TIME01 register description.
            apertureClocks += 0.5;
            // Down 1/2 ns for rounding (the ceiling function below will adjust this)
            apertureClocks -= 0.5 / adcClockNs;
            // Convert to integral number of clocks.
            long clocks = (long)Math.Ceiling(apertureClocks);

            // Enforce SAR_v2 SAMPLE_TIME01 and SAMPLE_TIME02 bitfield limits.
            clocks = Math.Min(clocks, APERTURE_MAX_ADC_CLOCK);
            clocks = Math.Max(clocks, APERTURE_MIN_ADC_CLOCK);

            return clocks;
        }

        /// <summary>
        /// Calculate ADC clock period
        /// </summary>
        /// <param name="adcClockDivider" ADC clock divider for current schedule</param>
        /// <returns>ADC clock period</returns>
        private double AdcClockPeriod_s(long adcClockDivider)
        {
            double adcClockHz = (double)this.ClkHF_Hz / adcClockDivider;
            double adcClockPeriod = 1 / adcClockHz;
            return adcClockPeriod;
        }

        /// <summary>
        /// Find best channel to use for ADC clock padding.
        /// 
        /// Prefer channels with no averaging or minimum averaging
        /// and lowest ideal ADC clock count.
        /// The chanTimes list must be sorted.
        /// </summary>
        /// <param name="chanTimes">Channel ADC clock and sample count information</param>
        /// <returns>Index of best padding channel</returns>
        private int FindPaddingChannel(List<CyTimingInfo> chanTimes)
        {
            int bestPadIndex = 0;

            for (int padIndex = 1; padIndex < chanTimes.Count; padIndex++)
            {
                if (chanTimes[bestPadIndex].ComparePaddingMerit(chanTimes[padIndex]) > 0)
                {
                    bestPadIndex = padIndex;
                }
            }

            return bestPadIndex;
        }

        /// <summary>
        /// Find best channel in range to use for ADC clock padding.
        /// 
        /// Prefer channels with no averaging or minimum averaging
        /// and lowest ideal ADC clock count.
        /// The chanTimes list must be sorted.
        /// </summary>
        /// <param name="chanTimes">Channel ADC clock and sample count information</param>
        /// <param name="start">Starting index for search</param>
        /// <param name="stop">Stopping index for search</param>
        /// <returns>Index of best padding channel</returns>
        private int FindPaddingChannel(List<CyTimingInfo> chanTimes, int start, int stop)
        {
            int bestPadIndex = start;

            for (int padIndex = start + 1; padIndex < stop; padIndex++)
            {
                if (chanTimes[bestPadIndex].ComparePaddingMerit(chanTimes[padIndex]) > 0)
                {
                    bestPadIndex = padIndex;
                }
            }

            return bestPadIndex;
        }

        /// <summary>
        /// Compute cost based on closeness to target frequencies.
        /// 
        /// Cost is a sum of differences squared.  The ADC scan frequency difference
        /// is calculated directly.  The UAB sampling frequency difference is lower
        /// within a target band.
        /// </summary>
        /// <param name="scanAdcClocks">Number of ADC clocks per scan</param>
        /// <param name="uabPhaseAdcClocks">Number of ADC clocks per single UAB phase</param>
        /// <param name="adcClockDivider"ADC clock divider for current schedule</param>
        /// <returns>Non-negative cost</returns>
        public double AdcUabCost(
            long scanAdcClocks, long uabClkPeriod_HFClks, long adcClockDivider)
        {
            double scanRate_Hz = (double)this.ClkHF_Hz / (scanAdcClocks * adcClockDivider);
            double uabFilterSample_Hz
                = (double)this.ClkHF_Hz / (UAB_FILTER_STEPS * uabClkPeriod_HFClks);

            double uabFreqLow = OVER_SAMPLE_LOW * this.UabFilterCharFreq_Hz;
            double uabFreqTarget = OVER_SAMPLE_TARGET * this.UabFilterCharFreq_Hz;
            double uabFreqHigh = OVER_SAMPLE_HIGH * this.UabFilterCharFreq_Hz;

            double scanDiff = this.ScanDiffCost * (scanRate_Hz - this.TargetScanRate_sps);
            //scanDiff /= this.TargetScanRate_sps;

            double uabDiff;
            if (uabFilterSample_Hz < uabFreqLow)
            {
                uabDiff
                    = (uabFreqLow - uabFilterSample_Hz) * this.UabDiffNearCost
                    + (uabFreqTarget - uabFreqLow) * this.UabDiffFarCost;
            }
            else if (uabFilterSample_Hz < uabFreqHigh)
            {
                uabDiff = (uabFilterSample_Hz - uabFreqTarget) * this.UabDiffNearCost;
            }
            else
            {
                uabDiff
                    = (uabFilterSample_Hz - uabFreqHigh) * this.UabDiffNearCost
                    + (uabFreqHigh - uabFreqTarget) * this.UabDiffFarCost;
            }
            //uabDiff /= uabFreqTarget;

            double cost = scanDiff * scanDiff + uabDiff * uabDiff;

            return cost;
        }

        /// <summary>
        /// Channel timing information used by schedule optimizer.
        /// </summary>
        public class CyTimingInfo : IComparable
        {
            public bool IsEnabled { get; set; }
            public bool IsFilter { get; set; }
            public long SampleCount { get; set; }
            public long IdealSample_AdcClock { get; set; }
            public int ChannelNum { get; set; }

            public CyTimingInfo(
                long idealSampleClocks, long sampleCount, bool isFilter, int chanNum,
                bool enabled)
            {
                this.IdealSample_AdcClock = idealSampleClocks;
                this.SampleCount = sampleCount;
                this.IsFilter = isFilter;
                this.ChannelNum = chanNum;
                this.IsEnabled = enabled;
            }

            public int CompareTo(object obj)
            {
                if (obj == null)
                {
                    return 1;
                }

                CyTimingInfo other = obj as CyTimingInfo;
                if (other == null)
                {
                    throw new ArgumentException("Object is not a CyChanTiming");
                }

                if (this.IdealSample_AdcClock < other.IdealSample_AdcClock)
                {
                    return -1;
                }
                else if (this.IdealSample_AdcClock > other.IdealSample_AdcClock)
                {
                    return 1;
                }
                else if (this.SampleCount < other.SampleCount)
                {
                    return -1;
                }
                else if (this.SampleCount > other.SampleCount)
                {
                    return 1;
                }
                else if ((this.IsEnabled == true) && (other.IsEnabled == false))
                {
                    return -1;
                }
                else if ((this.IsEnabled == false) && (other.IsEnabled == true))
                {
                    return 1;
                }
                else if (this.ChannelNum < other.ChannelNum)
                {
                    return -1;
                }
                else if (this.ChannelNum > other.ChannelNum)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }

            public int ComparePaddingMerit(CyTimingInfo other)
            {
                if ((this.IsEnabled == true) && (other.IsEnabled == false))
                {
                    return -1;
                }
                else if ((this.IsEnabled == false) && (other.IsEnabled == true))
                {
                    return 1;
                }
                else if ((this.IsFilter == true) && (other.IsFilter == false))
                {
                    return 1;
                }
                else if ((this.IsFilter == false) && (other.IsFilter == true))
                {
                    return -1;
                }
                else if (this.SampleCount < other.SampleCount)
                {
                    return -1;
                }
                else if (this.SampleCount > other.SampleCount)
                {
                    return 1;
                }
                else if (this.IdealSample_AdcClock < other.IdealSample_AdcClock)
                {
                    return -1;
                }
                else if (this.IdealSample_AdcClock > other.IdealSample_AdcClock)
                {
                    return 1;
                }
                else if (this.ChannelNum < other.ChannelNum)
                {
                    return -1;
                }
                else if (this.ChannelNum > other.ChannelNum)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }

        /// <summary>
        /// Input data and scratchpad area for a specific channel/
        /// </summary>
        public class CySchedChan
        {
            // Input properties
            public bool IsEnabled { get; set; }
            public int Resolution { get; set; }
            public bool IsFilter { get; set; }
            public CyEFilterType FilterType { get; set; }
            public double ApertureMin_Ns { get; set; }
            public bool IsBulkAveraged { get; set; }

            // Output properties
            public int Timer { get; set; }
            public double AchievedAperture_Ns { get; set; }

            // Scratchpad properties
            public long Conversion_AdcClock { get; set; }
            public long NonOverlap_AdcClock { get; private set; }
            public long AutoZero_AdcClock { get; private set; }
            public long MinSample_AdcClock { get; set; }
            public long MinChannel_AdcClock { get; set; }
            public long MinTotal_AdcClock { get; set; }
            public long MappedSample_AdcClock { get; set; }
            public long MappedChannel_AdcClock { get; set; }
            public long MappedTotal_AdcClock { get; set; }

            public CySchedChan(
                double minSample_Ns = 194.0,
                bool isFilter = false,
                CyEFilterType filterType = CyEFilterType.LOW_PASS,
                bool isBulkAveraged = false,
                int resolution = DEFAULT_RESOLUTION,
                bool isEnabled = true)
            {
                this.IsEnabled = isEnabled;
                this.Resolution = resolution;
                this.IsFilter = isFilter;
                this.FilterType = filterType;
                this.ApertureMin_Ns = Math.Max(minSample_Ns, SampleMin_ns);
                if (isFilter)
                {
                    this.ApertureMin_Ns = Math.Max(minSample_Ns, SAMPLE_FILTER_MIN_NS);
                }
                this.IsBulkAveraged = isBulkAveraged;
                this.Conversion_AdcClock = this.Resolution;
                this.NonOverlap_AdcClock = 1;
                this.AutoZero_AdcClock = 1;
                this.Timer = 0;
            }

            public CySchedChan(CySchedChan orig)
            {
                this.IsEnabled = orig.IsEnabled;
                this.Resolution = orig.Resolution;
                this.IsFilter = orig.IsFilter;
                this.ApertureMin_Ns = orig.ApertureMin_Ns;
                this.IsBulkAveraged = orig.IsBulkAveraged;

                // Output properties
                this.Timer = orig.Timer;
                this.AchievedAperture_Ns = orig.AchievedAperture_Ns;

                // Scratchpad properties
                this.Conversion_AdcClock = orig.Conversion_AdcClock;
                this.NonOverlap_AdcClock = orig.NonOverlap_AdcClock;
                this.AutoZero_AdcClock = orig.AutoZero_AdcClock;
                this.MinSample_AdcClock = orig.MinSample_AdcClock;
                this.MinChannel_AdcClock = orig.MinChannel_AdcClock;
                this.MinTotal_AdcClock = orig.MinTotal_AdcClock;
                this.MappedSample_AdcClock = orig.MappedSample_AdcClock;
                this.MappedChannel_AdcClock = orig.MappedChannel_AdcClock;
                this.MappedTotal_AdcClock = orig.MappedTotal_AdcClock;
            }
        }

        public class CySchedule
        {
            // Input/Output properties
            public List<CySchedChan> Channels { get; set; }
            public List<long> Apertures_AdcClock { get; set; }
            public long AdcClockDivider { get; set; }

            // Output properties
            public long UabClockDivider { get; set; }
            public long UabStartDelay_HFClk { get; set; }
            public long AchievedSampleRate { get; set; }
            public long AchievedAdcClock_Hz { get; set; }
            public double AchievedScanPeriod_Us { get; set; }
            public List<CyDRCInfo_v1> Drcs { get; set; }

            // Internal properties
            public long Cost { get; set; }

            public CySchedule(List<CySchedChan> channels)
            {
                this.Channels = new List<CySchedChan>();
                foreach (var chan in channels)
                {
                    this.Channels.Add(new CySchedChan(chan));
                }

                this.Apertures_AdcClock = new List<long>();
                for (int timerNum = 0; timerNum < CySarRanges.APERTURE_TIMER_COUNT; timerNum++)
                {
                    this.Apertures_AdcClock.Add(CySarRanges.APERTURE_TIMER_MIN);
                }

                this.Drcs = new List<CyDRCInfo_v1>();

                this.AdcClockDivider = AdcClockDividerMin;
            }
        }
    }
}
