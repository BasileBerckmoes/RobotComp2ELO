/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using CyDesigner.Extensions.Gde;

namespace PowerMonitor_P4_v1_0
{
    public class CyClock
    {
        public struct AdcClkInfo
        {
            public int[] AdcClockApertures;
            public int[] ConverterAdcClockSelect;
            public int ScanTime;
            public int ResponseTime;
            public AdcClkInfo(int DefaultAdcClk, int NumConverters)
            {
                this.AdcClockApertures = new int[4] { DefaultAdcClk, DefaultAdcClk, DefaultAdcClk, DefaultAdcClk };
                this.ConverterAdcClockSelect = new int[NumConverters];//{ 0, 0, 0, 0, 0, 0, 0, 0 };
                this.ScanTime = 0;
                this.ResponseTime = 0;
            }
        }

        const int DEFAULT_ADC_CLOCK_DIVIDER = 3;
        const int ADC_CLOCK_FAST_HZ = 18000000;
        const int ADC_CLOCK_CY8C41_HZ = 14500000;
        const int ADC_CLOCK_SLOW_HZ = 1600000;
        const string HF_CLOCK_GUID = "413DE2EF-D9F2-4233-A808-DFAF137FD877";
        const string SYS_CLOCK_GUID = "5A84F528-323D-4eda-8141-58D504D70A4B";
        public static int GetHclk(ICyInstQuery_v1 instQuery)
        {
            return GetClk(instQuery, HF_CLOCK_GUID);
        }
        public static int GetSysClk(ICyInstQuery_v1 instQuery)
        {
            return GetClk(instQuery, SYS_CLOCK_GUID);
        }
        private static int GetClk(ICyInstQuery_v1 instQuery, string clkID)
        {
            var designQuery = instQuery.DesignQuery;
            double freq;
            byte exp;
            if (designQuery.GetClockActualFreq(clkID, out freq, out exp))
            {
                freq *= Math.Pow(10, exp);
                return (int)freq;
            }
            return (int)0;

        }
        public static int GetAdcClockDivider(CyParameters parameters)
        {
            if (parameters == null)
            {
                return DEFAULT_ADC_CLOCK_DIVIDER;
            }

            var instQuery = parameters.m_inst;
            if (instQuery == null)
            {
                return DEFAULT_ADC_CLOCK_DIVIDER;
            }

            var designQuery = instQuery.DesignQuery;
            if (designQuery == null)
            {
                return DEFAULT_ADC_CLOCK_DIVIDER;
            }

            double adcClockHz;
            switch (parameters.VrefSelect)
            {
                case CyEVrefSelect.Vref_1024mV:
                    adcClockHz = ADC_CLOCK_SLOW_HZ;
                    break;
                case CyEVrefSelect.Vref_1024mVBypass:
                    adcClockHz = ADC_CLOCK_FAST_HZ;
                    break;
                case CyEVrefSelect.Vref_Internal:
                    adcClockHz = ADC_CLOCK_SLOW_HZ;
                    break;
                case CyEVrefSelect.Vref_InternalBypass:
                    adcClockHz = ADC_CLOCK_FAST_HZ;
                    break;
                case CyEVrefSelect.Vref_External:
                    adcClockHz = ADC_CLOCK_FAST_HZ;
                    break;
                default:
                    adcClockHz = ADC_CLOCK_SLOW_HZ;
                    break;
            }

            /* Special case for PSoC4A-S2 */
            if ((adcClockHz == ADC_CLOCK_FAST_HZ) && (Additional.cyutils.IsPSoC4AS2(instQuery) || Additional.cyutils.IsCY8C41(instQuery)))
            {
                adcClockHz = ADC_CLOCK_CY8C41_HZ;
            }

            /* Get divider based on adcClockHz */
            const string HfClkID = "413DE2EF-D9F2-4233-A808-DFAF137FD877";
            double freq;
            int freq_div;
            byte exp;
            if (designQuery.GetClockActualFreq(HfClkID, out freq, out exp))
            {
                freq *= Math.Pow(10, exp);
                /* The ADC clock "cannot be used ifs frequency exceeds half the HFCLK frequency" */
                freq_div = (int)Math.Ceiling(Convert.ToInt32(freq) / adcClockHz);
                int adcClockDivider = Math.Max(2, freq_div);
                return adcClockDivider;
            }

            return DEFAULT_ADC_CLOCK_DIVIDER;
        }

        public static AdcClkInfo OptimizeClockApertures(CyParameters parameters)
        {
            if (parameters == null)
            {
                return new AdcClkInfo(2, 8);
            }
            AdcClkInfo AdcClockConfig = new AdcClkInfo(2, parameters.VoltagesTable.Count);

            #region AdcClk Optimization
            /* Set acquisition times to a minimum value if they are not set */
            var TableAcqTimes = new List<int>();
            for (int i = 0; i < parameters.VoltagesTable.Count; i++)
            {
                int acqTime = parameters.VoltagesTable[i].m_minAcqTime_ns != null ? (int)parameters.VoltagesTable[i].m_minAcqTime_ns : Convert.ToInt32(CyParamRanges.DEFAULT_SETTLING_TIME_NS); 
                TableAcqTimes.Add(acqTime);
            }

            //Convert acquisition times to number of aperture clocks
            var ApertureClocks = new List<int>();
            int apertureMin = 2;
            int apertureMax = 1023;
            int aperture;
            foreach (int acqTime in TableAcqTimes)
            {
                aperture = ConvertNsToAdcClocks(parameters, apertureMin, apertureMax, acqTime);
                ApertureClocks.Add(aperture);
            }

            int AdcClkPerSample = 14;
            double AdcConvOverheadHclks = 2;
            double refreshPeriod_seconds = 0;
            double secondsPerAdcClock = parameters.AdcClkDivider / (double)parameters.Hclk_Hz;

            // Find the most efficient selection of aperture clocks
            if (ApertureClocks.Count < 5) 
            {
                // 4 or fewer converters. Each converter gets its own aperture clock.
                for (int timerNum = 0; timerNum < ApertureClocks.Count; timerNum++)
                {
                    AdcClockConfig.AdcClockApertures[timerNum] = ApertureClocks[timerNum];
                    AdcClockConfig.ConverterAdcClockSelect[timerNum] = timerNum;

                    var channelClocks = ((AdcClkPerSample + AdcClockConfig.AdcClockApertures[timerNum]) * Convert.ToInt16(parameters.SamplesAveraged));
                    refreshPeriod_seconds += (channelClocks * secondsPerAdcClock);
                }
            }
            else
            {
                // Sort and reverse ApertureClocks
                ApertureClocks.Sort();
                ApertureClocks.Reverse();

                // This algorithm searches through the different selections of the four aperture timers of the SAR.
                // It does this by cycling through each clock selection and keeping the selection that uses
                // the fewest number of clocks.
                Int32 lowestCost = Int32.MaxValue; 
                int binStart1 = 0;
                for (int binStart2 = 1; binStart2 < ApertureClocks.Count - 2; binStart2++)
                {
                    for (int binStart3 = (binStart2 + 1); binStart3 < ApertureClocks.Count - 1; binStart3++)
                    {
                        for (int binStart4 = (binStart3 + 1); binStart4 < ApertureClocks.Count; binStart4++)
                        {
                            int clock1 = ApertureClocks[binStart1];   //First element is always the largest. 
                            int clock2 = ApertureClocks[binStart2];
                            int clock3 = ApertureClocks[binStart3];
                            int clock4 = ApertureClocks[binStart4];

                            int cost = clock1 * (binStart2 - binStart1);
                            cost += clock2 * (binStart3 - binStart2);
                            cost += clock3 * (binStart4 - binStart3);
                            cost += clock4 * (ApertureClocks.Count - binStart4);

                            if (cost < lowestCost)
                            {
                                lowestCost = cost;
                                AdcClockConfig.AdcClockApertures[0] = clock1;
                                AdcClockConfig.AdcClockApertures[1] = clock2;
                                AdcClockConfig.AdcClockApertures[2] = clock3;
                                AdcClockConfig.AdcClockApertures[3] = clock4;
                            }
                        }
                    }
                }

                /* Create the ConverterAdcClockSelect array and calculate the scan time */
                for (int chan = 0; chan < TableAcqTimes.Count; chan++)
                {
                    aperture = ConvertNsToAdcClocks(parameters, apertureMin, apertureMax, TableAcqTimes[chan]); 

                    /* Find the closest matching aperture clock that is greater than or equal to the required clock  */
                    int bestClockSelect = 0;
                    for (int timerNum = 1; timerNum < 4; timerNum++)
                    {
                        if (aperture <= AdcClockConfig.AdcClockApertures[timerNum])
                        {
                            bestClockSelect = timerNum;
                        }
                    }
                    AdcClockConfig.ConverterAdcClockSelect[chan] = bestClockSelect;

                    var channelClocks = ((AdcClkPerSample + AdcClockConfig.AdcClockApertures[bestClockSelect]) * Convert.ToInt16(parameters.SamplesAveraged));
                    refreshPeriod_seconds += (channelClocks * secondsPerAdcClock);
                }
            }

            #endregion
            
            /* Calculate the new scan and response times */
            refreshPeriod_seconds += AdcConvOverheadHclks * secondsPerAdcClock;
            AdcClockConfig.ScanTime = (int)(refreshPeriod_seconds * 1e9);

            int DmaSysClkCycles = 18;
            int NumDmaUsed = 5;
            if (parameters.EnableDMA)
            {
                double response_period;
                response_period = 
                      2 * refreshPeriod_seconds
                    + 2 * NumDmaUsed * (DmaSysClkCycles / (double)parameters.SysClk_Hz);
                AdcClockConfig.ResponseTime = (int)(response_period * 1e9);
            }
            else
            {
                AdcClockConfig.ResponseTime = 0;
            }

            return AdcClockConfig;
        }

        private static int ConvertNsToAdcClocks(CyParameters parameters, int apertureMin, int apertureMax, int acqTime)
        {
            int aperture;
            aperture = Math.Max(apertureMin, Math.Min(apertureMax,
                (int)Math.Ceiling((float)acqTime * parameters.Hclk_Hz * 1e-9 / parameters.AdcClkDivider)));
            return aperture;
        }
    }
}