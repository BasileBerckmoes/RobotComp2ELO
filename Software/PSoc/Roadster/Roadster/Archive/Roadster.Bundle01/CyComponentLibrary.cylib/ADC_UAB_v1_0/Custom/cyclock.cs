/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

// The namespace is required to have the same name as the component for a customizer.
namespace ADC_UAB_v1_0
{
    public static class CyClock
    {
        const string SysClkID = "5A84F528-323D-4eda-8141-58D504D70A4B";
        public const double UNKNOWN_FREQUENCY = -1;

        public static double GetSysClk_MHz(ADC_UAB_Parameters parameters)
        {
            double SysClk_MHz = 0.0;

            ICyInstQuery_v1 instQuery = parameters.m_query;
            ICyDesignQuery_v1 designQuery = instQuery.DesignQuery;
            double freq;
            byte exp;

            if(designQuery.DesignInfoAvailable.Equals(true))
            {
                if (designQuery.GetClockActualFreq(SysClkID, out freq, out exp) == true)
                {
                    SysClk_MHz = freq * Math.Pow(10, exp);
                }
            }

            return SysClk_MHz;
        }

        /// <summary>
        /// Returns the clock rate of the clock attached to the specified
        /// terminal.  If the frequency is not found, returns UNKNOWN_FREQUENCY.
        /// </summary>
        public static double GetClockRate_Hz(ICyTerminalQuery_v1 termQuery, string instPath, string termName)
        {
            double freq = UNKNOWN_FREQUENCY;
            if (termQuery != null)
            {
                List<CyClockData> clkdata = termQuery.GetClockData(instPath, termName, 0);


                if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
                {
                    freq = clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                }
            }

            return freq;
        }

        /// <summary>
        /// Returns the clock rate of the clock attached to the specified
        /// terminal.  If the frequency is not found, returns UNKNOWN_FREQUENCY.
        /// </summary>
        public static double GetClockRate_Hz(ICyTerminalQuery_v1 termQuery, string termName)
        {
            double freq = UNKNOWN_FREQUENCY;

            if (termQuery != null)
            {
                List<CyClockData> clkdata = termQuery.GetClockData(termName, 0);

                if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
                {
                    freq = clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
                }
            }

            return freq;
        }
        /// <summary>
        /// Returns a CyClockData object corresponding to the clock attached
        /// to the specified component.  If the clock is not found, returns null.
        /// </summary>
        private static CyClockData GetClockData(ICyTerminalQuery_v1 termQuery, string instPath, string termName)
        {
            List<CyClockData> clkdata;
            if (instPath == null || instPath == "")
            {
                clkdata = termQuery.GetClockData(termName, 0);
            }
            else
            {
                clkdata = termQuery.GetClockData(instPath, termName, 0);
            }
            return (clkdata.Count > 0) ? clkdata[0] : null;
        }

        /// <summary>
        /// Tests whether a frequency, eg returned by GetClockRate_Hz(), is a
        /// known frequency.
        /// </summary>
        public static bool IsFrequencyKnown(double frequency)
        {
            return frequency > 0;
        }
    }
}

//[] END OF FILE
