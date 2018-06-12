/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections;

namespace TrimMargin_v3_0
{
    internal static class CyHelper
    {
        public static bool IsValueInRange<T>(T val, double min, double max)
        {
            bool res;
            double dVal = Convert.ToDouble(val);

            res = dVal >= min && dVal <= max;

            return res;
        }

        public static bool GreaterThan(double? value, double? compareTo)
        {
            if (value.HasValue && compareTo.HasValue)
            {
                if (value > compareTo + CyConstants.EPS)
                    return true;
            }
            return false;
        }

        public static bool LessThan(double? value, double? compareTo)
        {
            if (value.HasValue && compareTo.HasValue)
            {
                value = Math.Round(value.Value, 3);
                compareTo = Math.Round(compareTo.Value, 3);

                if (value + CyConstants.EPS >= compareTo)
                    return true;
            }
            return false;
        }

        public static bool AreEqual(decimal val1, double? val2)
        {
            return (val2 != null) ? Math.Abs(Convert.ToDouble(val1) - (double)val2) < CyConstants.EPSILON : false;
        }

        public static double? ParseNullableDouble(string val)
        {
            double? res = null;
            double parsed = 0;
            if (double.TryParse(val, out parsed))
            {
                res = parsed;
            }
            return res;
        }

        public static ushort? ParseNullableUInt16(string val)
        {
            ushort? res = null;
            ushort parsed = 0;
            if (UInt16.TryParse(val, out parsed))
            {
                res = parsed;
            }
            return res;
        }

        public static bool IsNullOrInfinity(double? value)
        {
            return (value.HasValue == false || Double.IsInfinity(value.Value));
        }

        public static string NullableDoubleToString(double? val)
        {
            return NullableDoubleToString(val, 2);
        }

        public static string NullableDoubleToString(double? val, byte precision)
        {
            string res = String.Empty;
            string strPrecision = (precision > 0) ? "f" + precision.ToString() : String.Empty;
            if (val.HasValue)
            {
                res = val.Value.ToString(strPrecision);
            }
            return res;
        }

        public static string CellToString(object cellValue)
        {
            return (cellValue != null) ? cellValue.ToString() : String.Empty;
        }

        public static string ToHex(UInt32 value)
        {
            return String.Format("0x{0:X2}", value);
        }

        public static byte ConvertToByte(BitArray bits)
        {
            if (bits.Count != 8)
            {
                throw new ArgumentException("Number of bits must be 8.");
            }
            byte[] bytes = new byte[1];
            bits.CopyTo(bytes, 0);
            return bytes[0];
        }
    }
}