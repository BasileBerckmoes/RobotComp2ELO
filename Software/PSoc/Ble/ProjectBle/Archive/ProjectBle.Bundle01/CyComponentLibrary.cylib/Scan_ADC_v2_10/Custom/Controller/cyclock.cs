using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_10
{
    public static class CyClock
    {
        private const double FREQUENCY_UNKNOWN = -1.0;


        public static CyClockData GetExternalSarClockData(ICyTerminalQuery_v1 termQuery)
        {
            var clkData = termQuery.GetClockData(
                CySchematicNames.EXTERNAL_SAR_CLOCK_TERM,
                0);

            if (clkData.Count > 0 && clkData[0].IsFrequencyKnown)
            {
                return clkData[0];
            }

            return null;
        }

        public static CyClockData GetInternalSarClockData(ICyTerminalQuery_v1 termQuery)
        {
            var clkData = termQuery.GetClockData(
                CySchematicNames.INTERNAL_SAR_CLOCK_GATE,
                CySchematicNames.INTERNAL_SAR_CLOCK_TERM,
                0);

            if (clkData.Count > 0 && clkData[0].IsFrequencyKnown)
            {
                return clkData[0];
            }

            return null;
        }

        public static bool IsFrequencyKnown(double frequency)
        {
            return Math.Abs(frequency - FREQUENCY_UNKNOWN) > CyParamRanges.FREQUENCY_EPSILON;
        }
    }
}
