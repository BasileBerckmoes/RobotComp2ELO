/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using TrimMargin_v3_0.DataStructures;

namespace TrimMargin_v3_0.Utils
{
    /// <summary>
    /// This class contains all math used in the component.
    /// </summary>
    internal class CyMath
    {
        #region Constants
        //
        // Not all E series are strict geometric progression (e.g. E24)
        // so used table method to calculate the closest value
        // Standard EIA Decade Values Table (100 to 1,000 Decade)
        //
        private static readonly int[] E24 = new int[] { 
            100, 110, 120, 130, 150, 160, 180, 200, 220, 240, 270, 300, 
            330, 360, 390, 430, 470, 510, 560, 620, 680, 750, 820, 910, 1000 };

        private static readonly int[] E48 = new int[] { 
            100, 105, 110, 115, 121, 127, 133, 140, 147, 154, 162, 169, 
            178, 187, 196, 205, 215, 226, 237, 249, 261, 274, 287, 301,
            316, 332, 348, 365, 383, 402, 422, 442, 464, 487, 511, 536,
            562, 590, 619, 649, 681, 715, 750, 787, 825, 866, 909, 953, 1000 };

        private static readonly int[] E96 = new int[] { 
            100, 102, 105, 107, 110, 113, 115, 118, 121, 124, 127, 130, 
            133, 137, 140, 143, 147, 150, 154, 158, 162, 165, 169, 174,
            178, 182, 187, 191, 196, 200, 205, 210, 215, 221, 226, 232,
            237, 243, 249, 255, 261, 267, 274, 280, 287, 294, 301, 309,
            316, 324, 332, 340, 348, 357, 365, 374, 383, 392, 402, 412,
            422, 432, 442, 453, 464, 475, 487, 499, 511, 523, 536, 549, 
            562, 576, 590, 604, 619, 634, 649, 665, 681, 698, 715, 732,
            750, 768, 787, 806, 825, 845, 866, 887, 909, 931, 953, 976, 1000 };

        private static readonly int[] E192 = new int[] { 
            100, 101, 102, 104, 105, 106, 107, 109, 110, 111, 113, 114,
            115, 117, 118, 120, 121, 123, 124, 126, 127, 129, 130, 132,
            133, 135, 137, 138, 140, 142, 143, 145, 147, 149, 150, 152, 
            154, 156, 158, 160, 162, 164, 165, 167, 169, 172, 174, 176,
            178, 180, 182, 184, 187, 189, 191, 193, 196, 198, 200, 203, 
            205, 208, 210, 213, 215, 218, 221, 223, 226, 229, 232, 234,
            237, 240, 243, 246, 249, 252, 255, 258, 261, 264, 267, 271, 
            274, 277, 280, 284, 287, 291, 294, 298, 301, 305, 309, 312,
            316, 320, 324, 328, 332, 336, 340, 344, 348, 352, 357, 361, 
            365, 370, 374, 379, 383, 388, 392, 397, 402, 407, 412, 417,
            422, 427, 432, 437, 442, 448, 453, 459, 464, 470, 475, 481, 
            487, 493, 499, 505, 511, 517, 523, 530, 536, 542, 549, 556,
            562, 569, 576, 583, 590, 597, 604, 612, 619, 626, 634, 642, 
            649, 657, 665, 673, 681, 690, 698, 706, 715, 723, 732, 741,
            750, 759, 768, 777, 787, 796, 806, 816, 825, 835, 845, 856, 
            866, 876, 887, 898, 909, 920, 931, 942, 953, 965, 976, 988, 1000 };
        #endregion

        #region Private members
        private CyParameters m_parameters;
        private byte PWMResolution { get { return m_parameters.PWMResolution; } }
        private List<CyVoltagesTableRow> VoltagesTable { get { return m_parameters.VoltagesTable; } }
        private List<CyHardwareTableRow> HardwareTable { get { return m_parameters.HardwareTable; } }
        #endregion

        #region Constructor(s)
        public CyMath(CyParameters parameters)
        {
            m_parameters = parameters;
        }
        #endregion

        #region Methods
        public void CalculateTableValues(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow)
        {
            double? calcR3, calcR4;
            GetCalculatedR3R4(voltRow, hwRow, out calcR3, out calcR4);
            hwRow.m_calcR3 = calcR3;
            hwRow.m_calcR4 = calcR4;
            hwRow.m_calcC1 = GetCalculatedC1(hwRow);
            hwRow.m_calcVRipple = GetCalculatedVRipple(hwRow);
            hwRow.m_calcR2 = GetCalculatedR2real(voltRow, hwRow);
            hwRow.m_nominalPWM = (UInt16?)GetPwmDutyCycle(voltRow, hwRow, voltRow.m_nominalVoltage);
        }

        public void CalculateTableValues(int index)
        {
            CalculateTableValues(VoltagesTable[index], HardwareTable[index]);
        }

        private void GetCalculatedR3R4(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow,
            out double? calcR3, out double? calcR4)
        {
            try
            {
                calcR3 = GetCalculatedRSerial(voltRow, hwRow) * 10 / 11;
                calcR4 = GetCalculatedRSerial(voltRow, hwRow) - calcR3;
                calcR3 = GetClosestESeries((double)calcR3, (CyESeriesType)hwRow.m_resistorESeries);
                calcR4 = GetClosestESeries((double)calcR4, (CyESeriesType)hwRow.m_resistorESeries);
            }
            catch (InvalidOperationException)
            {
                calcR3 = null;
                calcR4 = null;
            }
        }

        private double? GetCalculatedC1(CyHardwareTableRow row)
        {
            double? calcC1 = null;
            double? fPWMOut = GetPWMFrequency();
            try
            {
                calcC1 = (row.m_vOh / (2 * Math.PI * row.m_r4 * fPWMOut * row.m_maxRipple)) * (row.m_r1 / row.m_r3);
                if (CyHelper.IsNullOrInfinity(calcC1) == false)
                {
                    calcC1 = GetClosestESeries(calcC1.Value, (CyESeriesType)row.m_resistorESeries) * 1000000;
                }
            }
            catch (DivideByZeroException)
            {
                calcC1 = null;
            }
            catch (InvalidOperationException)
            {
                calcC1 = null;
            }

            if (CyHelper.IsNullOrInfinity(calcC1))
                calcC1 = null;

            return calcC1;
        }

        private double? GetCalculatedVRipple(CyHardwareTableRow row)
        {
            double? calcVRipple = null;
            double? fPWMOut = GetPWMFrequency();
            try
            {
                calcVRipple = (double)((row.m_vOh / (2 * Math.PI * row.m_r4 * fPWMOut * row.m_c1 / 1000)) *
                    (row.m_r1 / row.m_r3)) * 1000;
                calcVRipple = Math.Round(calcVRipple.Value, 3);
            }
            catch (DivideByZeroException)
            {
                calcVRipple = null;
            }
            catch (InvalidOperationException)
            {
                calcVRipple = null;
            }

            if (CyHelper.IsNullOrInfinity(calcVRipple))
                calcVRipple = null;

            return calcVRipple;
        }

        private double? GetCalculatedR2real(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow)
        {
            // R2real = R1 * Vadj * Rserial / (R1 * (Voh - Vadj) + Rserial * (Vmin - Vadj))
            double? r2real = null;
            try
            {
                double r1 = hwRow.m_r1.Value;
                double vAdj = hwRow.m_vAdj.Value;
                double vRef = hwRow.m_vAdj.Value;
                double vOh = hwRow.m_vOh.Value;
                double vMin = voltRow.m_minVoltage.Value;
                double vMax = voltRow.m_maxVoltage.Value;
                double vOhvAdjSubtraction = vOh - vAdj;
                double minVoltvAdjSubtraction = vMin - vAdj;

                if (vOhvAdjSubtraction == 0 || minVoltvAdjSubtraction == 0)
                {
                    r2real = (double)hwRow.m_r2;
                }
                else
                {
                    double? rSerial = GetCalculatedRSerial(voltRow, hwRow);
                    switch (voltRow.Feedback)
                    {
                        case CyEFeedback.Positive:
                            r2real = (r1 * vOh * vMin) / (vOh * (vRef - vMin) - vRef * (vMax - vMin));
                            break;
                        case CyEFeedback.Negative:
                            r2real = (double)((r1 * vAdj * rSerial) /
                                              (r1 * vOhvAdjSubtraction + rSerial * minVoltvAdjSubtraction));
                            break;
                        default:
                            Debug.Fail("Unhandled feedback type.");
                            break;
                    }
                }
                if (CyHelper.IsNullOrInfinity(r2real) == false)
                {
                    r2real = GetClosestESeries(r2real.Value, (CyESeriesType)hwRow.m_resistorESeries);
                }
            }
            catch (DivideByZeroException)
            {
                r2real = null;
            }
            catch (InvalidOperationException)
            {
                r2real = null;
            }

            if (CyHelper.IsNullOrInfinity(r2real))
                r2real = null;

            return r2real;
        }

        private double? GetCalculatedRSerial(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow)
        {
            double? res = null;

            try
            {
                double r1 = hwRow.m_r1.Value;
                double vOh = hwRow.m_vOh.Value;
                double vRef = hwRow.m_vAdj.Value;
                double vMin = voltRow.m_minVoltage.Value;
                double vMax = voltRow.m_maxVoltage.Value;

                if (voltRow.m_maxVoltage > voltRow.m_minVoltage)
                {
                    switch (voltRow.Feedback)
                    {
                        case CyEFeedback.Positive:
                            res = vOh * r1 / ((vMax / vMin - 1) * vRef);
                            break;
                        case CyEFeedback.Negative:
                            res = r1 * (vOh / (vMax - vMin));
                            break;
                        default:
                            Debug.Fail("Unhandled feedback type.");
                            break;
                    }
                }
            }
            catch (DivideByZeroException)
            {
                res = null;
            }
            catch (InvalidOperationException)
            {
                res = null;
            }

            if (CyHelper.IsNullOrInfinity(res))
                res = null;

            return res;
        }

        /// <summary>
        /// Gets output voltage to PWM duty cycle.
        /// </summary>
        private double? GetPwmDutyCycle(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow, double? voltage)
        {
            double? d = null;
            try
            {
                double calcVMin = GetCalculatedVMin(voltRow, hwRow).Value;
                double calcVMax = GetCalculatedVMax(voltRow, hwRow).Value;
                double twoPowResolution = Math.Pow(2, PWMResolution);

                switch (voltRow.Feedback)
                {
                    case CyEFeedback.Positive:
                        d = (voltage - calcVMin) / (calcVMax - calcVMin) * (twoPowResolution - 1);
                        break;
                    case CyEFeedback.Negative:
                        d = (calcVMax - voltage) / (calcVMax - calcVMin) * (twoPowResolution - 1);
                        break;
                    default:
                        Debug.Fail("Unhandled feedback type.");
                        break;
                }
            }
            catch (DivideByZeroException)
            {
                d = null;
            }
            catch (InvalidOperationException)
            {
                d = null;
            }

            if (CyHelper.IsNullOrInfinity(d))
                d = null;

            return d;
        }

        /// <summary>
        /// Gets output voltage to PWM duty cycle.
        /// </summary>
        public double? GetPwmDutyCycle(int rowIndex, double? voltage)
        {
            return GetPwmDutyCycle(VoltagesTable[rowIndex], HardwareTable[rowIndex], voltage);
        }

        private double GetClosestESeries(double r, CyESeriesType eSeriesType)
        {
            if (Double.IsInfinity(r) || Double.IsNaN(r))
                return r;

            double result = 0;
            int eSeriesVal = CyConstants.E24_SERIES * (1 << (int)eSeriesType);

            int first = 0;
            int last = eSeriesVal;
            int mid;
            int i = 0;
            int[] lut = null;

            switch (eSeriesType)
            {
                case CyESeriesType.E24:
                    lut = E24;
                    break;
                case CyESeriesType.E48:
                    lut = E48;
                    break;
                case CyESeriesType.E96:
                    lut = E96;
                    break;
                case CyESeriesType.E192:
                    lut = E192;
                    break;
                default:
                    lut = E24;
                    break;
            }

            // Normalization of the input value           
            if (r < 0)
                r *= -1;

            if (r == 0)
            {
                r = CyConstants.RESISTOR_MIN;
                return r;
            }

            while (r < 100)
            {
                r *= 10;
                i++;
            }
            while (r > 1000)
            {
                r /= 10;
                i--;
            }

            // Search for closest value from E24 series
            while (first < last)
            {
                mid = first + (last - first) / 2;

                if (r <= lut[mid])
                {
                    last = mid;
                }
                else
                {
                    first = mid + 1;
                }
            }

            // Final fine tuning to closest entry
            if ((r > lut[last]) && (last < eSeriesVal) &&
                ((r - lut[last]) > (lut[last + 1] - r)))
            {
                last++;
            }
            else if ((r < lut[last]) && (last > 0u) && ((r - lut[last - 1]) < (lut[last] - r)))
            {
                last--;
            }

            // Normalizing backward to actual units
            result = lut[last] / Math.Pow(10, i);

            return result;
        }

        public double? GetCalculatedVMax(int converterIdx)
        {
            return GetCalculatedVMax(VoltagesTable[converterIdx], HardwareTable[converterIdx]);
        }

        public double? GetCalculatedVMax(CyVoltagesTableRow voltRow, CyHardwareTableRow row)
        {
            double? res = null;
            try
            {
                double r1 = row.m_r1.Value;
                double r2 = row.m_r2.Value;
                double vOh = row.m_vOh.Value;
                double vAdj = row.m_vAdj.Value;
                double vRef = row.m_vAdj.Value;
                double rSerial = row.m_r3.Value + row.m_r4.Value;

                switch (voltRow.Feedback)
                {
                    case CyEFeedback.Positive:
                        double twoPowResolution = Math.Pow(2, PWMResolution);
                        res = (vRef / r1 + (vOh / rSerial * ((twoPowResolution - 1) / twoPowResolution))) /
                              (1 / r1 + 1 / r2 + 1 / rSerial);
                        break;
                    case CyEFeedback.Negative:
                        res = vAdj * (1 + r1 / r2 + r1 / rSerial);
                        break;
                    default:
                        Debug.Fail("Unhandled feedback type.");
                        break;
                }
                res = Math.Round(res.Value, 3);
            }
            catch (DivideByZeroException)
            {
                res = null;
            }
            catch (InvalidOperationException)
            {
                res = null;
            }

            if (CyHelper.IsNullOrInfinity(res))
                res = null;

            return res;
        }

        public double? GetCalculatedVMin(int converterIdx)
        {
            return GetCalculatedVMin(VoltagesTable[converterIdx], HardwareTable[converterIdx]);
        }

        public double? GetCalculatedVMin(CyVoltagesTableRow voltRow, CyHardwareTableRow row)
        {
            double? res = null;
            try
            {
                double r1 = row.m_r1.Value;
                double r2 = row.m_r2.Value;
                double vOh = row.m_vOh.Value;
                double vAdj = row.m_vAdj.Value;
                double vRef = row.m_vAdj.Value;
                double rSerial = row.m_r3.Value + row.m_r4.Value;

                switch (voltRow.Feedback)
                {
                    case CyEFeedback.Positive:
                        res = vRef / r1 / (1 / r1 + 1 / r2 + 1 / rSerial);
                        break;
                    case CyEFeedback.Negative:
                        res = vAdj * (1 + r1 / r2 + r1 / rSerial) - vOh * (r1 / rSerial) *
                              ((Math.Pow(2, PWMResolution) - 1) / Math.Pow(2, PWMResolution));
                        break;
                    default:
                        Debug.Fail("Unhandled feedback type.");
                        break;
                }
                res = Math.Round(res.Value, 3);
                if (res < 0) res = 0;
            }
            catch (DivideByZeroException)
            {
                res = null;
            }
            catch (InvalidOperationException)
            {
                res = null;
            }

            if (CyHelper.IsNullOrInfinity(res))
                res = null;

            return res;
        }

        public double? GetPWMFrequency()
        {
            double? pwmFreq = null;
            double? clockFr = m_parameters.GetInternalClock();
            try
            {
                pwmFreq = (double)clockFr / Math.Pow(2, (int)PWMResolution);
            }
            catch (DivideByZeroException)
            {
                pwmFreq = null;
            }
            catch (InvalidOperationException)
            {
                pwmFreq = null;
            }

            if (CyHelper.IsNullOrInfinity(pwmFreq))
                pwmFreq = null;

            return pwmFreq;
        }

        /// <summary>
        /// Gets output voltage to PWM pre-charge duty cycle.
        /// </summary>
        public double? GetPreCoef(CyHardwareTableRow row)
        {
            double? res = null;
            try
            {
                res = (double)(row.m_r4 / (row.m_r3 + (row.m_r1 * row.m_r2 / (row.m_r1 + row.m_r2))) + 1);
            }
            catch (DivideByZeroException)
            {
                res = null;
            }
            catch (InvalidOperationException)
            {
                res = null;
            }

            if (CyHelper.IsNullOrInfinity(res))
                res = null;

            return res;
        }

        private double? GetVDelta(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow)
        {
            double? res = null;
            try
            {
                double r1 = hwRow.m_r1.Value;
                double vOh = hwRow.m_vOh.Value;
                double rSerial = hwRow.m_r3.Value + hwRow.m_r4.Value;
                res = 0.5 * (r1 / rSerial) * ((vOh * 1000) / (Math.Pow(2, PWMResolution) - 1));
            }
            catch (DivideByZeroException)
            {
                res = null;
            }
            catch (InvalidOperationException)
            {
                res = null;
            }

            if (CyHelper.IsNullOrInfinity(res))
                res = null;

            return res;
        }

        public double? GetVDelta(int converterIndex)
        {
            return GetVDelta(VoltagesTable[converterIndex], HardwareTable[converterIndex]);
        }

        private double? GetKi(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow)
        {
            const ushort SAT_MIN = 1;
            const ushort SAT_MAX = 32767;
            const ushort KI_SCALING_FACTOR = 4096;

            double? k = null;
            try
            {
                double vRange = GetVRange(voltRow, hwRow).Value;
                double t = (hwRow.m_r4.Value * hwRow.m_c1.Value / 1000);
                double wcr1 = (double)(2 * Math.PI / (10 * voltRow.ControlSampleTime.Value / 1000.0));
                double wcr2 = Math.Tan(10 * Math.PI / 180) / (3 * t);
                double wcr = wcr1 < wcr2 ? wcr1 : wcr2;
                k = (double)(wcr * Math.Pow(2, PWMResolution) / vRange * t * Math.Pow(wcr * wcr + 1 / (t * t), 0.5));
                k *= KI_SCALING_FACTOR * voltRow.ControlSampleTime.Value / 1000;
                if (k < SAT_MIN)
                {
                    k = SAT_MIN;
                }
                else if (k > SAT_MAX)
                {
                    k = SAT_MAX;
                }
            }
            catch (DivideByZeroException)
            {
                k = null;
            }
            catch (InvalidOperationException)
            {
                k = null;
            }

            if (CyHelper.IsNullOrInfinity(k))
                k = null;

            return k;
        }

        public double? GetKi(int converterIndex)
        {
            return GetKi(VoltagesTable[converterIndex], HardwareTable[converterIndex]);
        }

        private double? GetVRange(CyVoltagesTableRow voltRow, CyHardwareTableRow hwRow)
        {
            double? res = null;
            try
            {
                double calcVmin = GetCalculatedVMin(voltRow, hwRow).Value;
                double calcVmax = GetCalculatedVMax(voltRow, hwRow).Value;
                res = calcVmax * 1000 - calcVmin * 1000;
            }
            catch (DivideByZeroException)
            {
                res = null;
            }
            catch (InvalidOperationException)
            {
                res = null;
            }

            if (CyHelper.IsNullOrInfinity(res))
                res = null;

            return res;
        }

        public double? GetVRange(int converterIndex)
        {
            return GetVRange(VoltagesTable[converterIndex], HardwareTable[converterIndex]);
        }
        #endregion
    }
}