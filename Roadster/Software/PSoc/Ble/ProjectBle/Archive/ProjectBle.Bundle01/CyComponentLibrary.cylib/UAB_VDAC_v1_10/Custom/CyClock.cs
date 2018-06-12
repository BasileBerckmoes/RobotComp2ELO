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
using CyDesigner.Extensions.Gde;

namespace UAB_VDAC_v1_10
{
    /// <summary>
    /// This class provides a quick way to get clock information from a component.
    /// Clocks are internal or external.  External clocks are set by users.
    /// Internal clocks must be set by inheriting parameters.
    /// </summary>
    public class CyClock
    {
        #region Clock data
        /// <summary>
        /// Virtual mux can't be queried, so it is common to also connect
        /// clocks to the first terminal of an OR gate and query the OR gate.
        /// This is the name of the terminal for use with CyClock methods.
        /// </summary>
        public const string OR_GATE_TERM_NAME = "term1";
        public const double UNKNOWN_FREQUENCY = -1;
        #endregion

        /// <summary>
        /// Returns the clock rate of the clock attached to the specified
        /// terminal.  If the frequency is not found, returns UNKNOWN_FREQUENCY.
        /// </summary>
        public static double GetClockRate_Hz(ICyTerminalQuery_v1 termQuery, string instPath, string termName)
        {
            List<CyClockData> clkdata  = termQuery.GetClockData(instPath, termName, 0);
            

            if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
            {
                return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
            }
            
            return UNKNOWN_FREQUENCY;
        }

        /// <summary>
        /// Returns the clock rate of the clock attached to the specified
        /// terminal.  If the frequency is not found, returns UNKNOWN_FREQUENCY.
        /// </summary>
        public static double GetClockRate_Hz(ICyTerminalQuery_v1 termQuery, string termName)
        {
            List<CyClockData> clkdata = termQuery.GetClockData(termName, 0);

            if (clkdata.Count > 0 && clkdata[0].IsFrequencyKnown)
            {
                return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent);
            }
            
            return UNKNOWN_FREQUENCY;
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
