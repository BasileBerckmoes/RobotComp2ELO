/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Scan_ADC_v1_30
{
    public static class CyFilterUtils
    {
        public const double MIN_OSR = 4; // CDT 243228 post 8

        public static Biquad GetIdealFilterBiquad(CyConfigModel config)
        {
            var biquad = new Biquad(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

            double f0_Hz;
            double f1_Hz;
            double f2_Hz;
            double f1or2_Hz;
            double fNotch_Hz;
            double fSample_Hz = 1000.0 * config.FilterSample;

            switch (config.FilterType)
            {
                case CyEFilterType.BAND_PASS:
                    f1_Hz = 1000.0 * config.FilterDown3OrCenter;
                    f2_Hz = 1000.0 * config.FilterWidthOrNotch;
                    try
                    {
                        biquad = BiquadMaker.MakeBandpass(f1_Hz, f2_Hz, fSample_Hz);
                    }
                    catch (CapacitorMapperException)
                    {
                    }
                    break;
                case CyEFilterType.BAND_STOP:
                    f0_Hz = 1000.0 * config.FilterDown3OrCenter;
                    f1or2_Hz = 1000.0 * config.FilterWidthOrNotch;
                    try
                    {
                        biquad = BiquadMaker.MakeBandstop(f0_Hz, f1or2_Hz, fSample_Hz);
                    }
                    catch (CapacitorMapperException)
                    {
                    }
                    break;
                case CyEFilterType.HIGH_PASS:
                    f0_Hz = 1000.0 * config.FilterDown3OrCenter;
                    fNotch_Hz = 1000.0 * config.FilterWidthOrNotch;
                    try
                    {
                        biquad = BiquadMaker.MakeHighpass(f0_Hz, fNotch_Hz, fSample_Hz);
                    }
                    catch (CapacitorMapperException)
                    {
                    }
                    break;
                case CyEFilterType.LOW_PASS:
                    f0_Hz = 1000.0 * config.FilterDown3OrCenter;
                    fNotch_Hz = 1000.0 * config.FilterWidthOrNotch;
                    try
                    {
                        biquad = BiquadMaker.MakeLowpass(f0_Hz, fNotch_Hz, fSample_Hz);
                    }
                    catch (CapacitorMapperException)
                    {
                    }
                    break;
            }

            biquad.Normalize();

            return biquad;
        }

        public static GTCaps GetUabFilterCapsHighQ(Biquad idealBiquad)
        {
            var biquad = new Biquad(idealBiquad);
            biquad.Reverse();

            // Biquad must be normalized as per KVCP.
            Debug.Assert(biquad.Den0 == 1.0);

            // Generate G&T capacitor values.
            List<double> normalizedXferCoeffs = new List<double> {
                biquad.Num0, biquad.Num1, biquad.Num2, biquad.Den1, biquad.Den2 };

            CapacitorMapper mapper = new CapacitorMapper();
            List<GTCaps> caps = mapper.MapCapacitorsHighQ(normalizedXferCoeffs);

            return caps[0];
        }

        public static GTCaps GetUabFilterCapsLowQ(Biquad idealBiquad)
        {
            var biquad = new Biquad(idealBiquad);
            biquad.Reverse();

            // Biquad must be normalized as per KVCP.
            Debug.Assert(biquad.Den0 == 1.0);

            // Generate G&T capacitor values.
            List<double> normalizedXferCoeffs = new List<double> {
                biquad.Num0, biquad.Num1, biquad.Num2, biquad.Den1, biquad.Den2 };

            CapacitorMapper mapper = new CapacitorMapper();
            List<GTCaps> caps = mapper.MapCapacitorsLowQ(normalizedXferCoeffs);

            return caps[0];
        }

        public static Biquad GetUabFilterBiquadHighQ(GTCaps caps)
        {
            // Calculate UAB capacitor transfer function.
            List<double> coeffs = caps.XferCoeffsHighQ();
            var uabBiquad = new Biquad(
                num0: coeffs[0], num1: coeffs[1], num2: coeffs[2],
                den0: 1.0, den1: coeffs[3], den2: coeffs[4]);
            uabBiquad.Reverse();

            return uabBiquad;
        }

        public static Biquad GetUabFilterBiquadLowQ(GTCaps caps)
        {
            // Calculate UAB capacitor transfer function.
            List<double> coeffs = caps.XferCoeffsLowQ();
            var uabBiquad = new Biquad(
                num0: coeffs[0], num1: coeffs[1], num2: coeffs[2],
                den0: 1.0, den1: coeffs[3], den2: coeffs[4]);
            uabBiquad.Reverse();

            return uabBiquad;
        }

        public static double GetFilterCharFreq_Hz(CyConfigModel config)
        {
            double f0_Hz;
            double f1_Hz;
            double f2_Hz;
            double fNotch_Hz;
            double fChar_Hz;

            switch (config.FilterType)
            {
                case CyEFilterType.BAND_PASS:
                    // High cutoff
                    f1_Hz = 1000.0 * config.FilterDown3OrCenter;
                    f2_Hz = 1000.0 * config.FilterWidthOrNotch;
                    fChar_Hz = Math.Max(f1_Hz, f2_Hz);
                    break;
                case CyEFilterType.BAND_STOP:
                    // High cutoff
                    fNotch_Hz = 1000.0 * config.FilterDown3OrCenter;
                    f1_Hz = 1000.0 * config.FilterWidthOrNotch;
                    fChar_Hz = (f1_Hz >= fNotch_Hz)
                        ? f1_Hz
                        : fNotch_Hz * fNotch_Hz / f1_Hz;
                    break;
                case CyEFilterType.HIGH_PASS:
                    // Cutoff
                    f0_Hz = 1000.0 * config.FilterDown3OrCenter;
                    fChar_Hz = f0_Hz;
                    break;
                case CyEFilterType.LOW_PASS:
                    // Max of cutoff or half notch (to avoid notch aliasing).
                    f0_Hz = 1000.0 * config.FilterDown3OrCenter;
                    fNotch_Hz = 1000.0 * config.FilterWidthOrNotch;
                    fChar_Hz = Math.Max(f0_Hz, fNotch_Hz / 2.0);
                    break;
                default:
                    fChar_Hz = CyScheduler.UAB_CLOCK_MIN_HZ
                        / CyScheduler.UAB_FILTER_STEPS;
                    break;
            }

            return fChar_Hz;
        }

        /// <summary>
        /// Return approximate value of filter's minimum sampling frequency.
        /// 
        /// Currently the estimate is 4 time the characteristic frequency parameter.
        /// </summary>
        /// <param name="config"></param>
        /// <returns>Approximate minimum sample frequency</returns>
        public static double GetFilterMinSampleFreq_Hz(CyConfigModel config)
        {
            double fChar_Hz = GetFilterCharFreq_Hz(config);
            double minSampleFreq = fChar_Hz * MIN_OSR;
            return minSampleFreq;
        }

        /// <summary>
        /// Return filter's minimum sampling frequency clipped to max UAB limit.
        /// 
        /// Currently the estimate is 4 time the characteristic frequency parameter.
        /// </summary>
        /// <param name="config"></param>
        /// <returns>Clipped minimum sample frequency</returns>
        public static double GetClippedFilterMinSampleFreq_Hz(CyConfigModel config)
        {
            double minSampleFreq_Hz = GetFilterMinSampleFreq_Hz(config);
            double maxUabFreq_Hz = CyScheduler.UAB_CLOCK_MAX_HZ
                        / CyScheduler.UAB_FILTER_STEPS;
            if (minSampleFreq_Hz > maxUabFreq_Hz)
            {
                minSampleFreq_Hz = maxUabFreq_Hz;
            }

            return minSampleFreq_Hz;
        }
    }
}