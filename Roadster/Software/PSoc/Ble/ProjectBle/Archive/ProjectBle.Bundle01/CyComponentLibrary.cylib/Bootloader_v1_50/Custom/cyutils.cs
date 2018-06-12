/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Globalization;
using System.Text.RegularExpressions;

namespace Bootloader_v1_50
{
    public static class CyUtils
    {
        public static char UNSIGNED_SUFFIX = 'u';
        public static string HEX_PREFIX = "0x";
        public static string HEX_REGEX = "^(0x)?[0-9a-fA-F]{1,}$";

        public static bool IsHex(string value)
        {
            Regex hexTemplate = new Regex(HEX_REGEX);
            return hexTemplate.IsMatch(value);
        }

        public static bool TryParseHex(string value, out uint res)
        {
            bool success;
            string input = value.Replace(HEX_PREFIX, String.Empty).TrimEnd(UNSIGNED_SUFFIX);
            res = 0;
            success = UInt32.TryParse(input, NumberStyles.HexNumber,
                CultureInfo.InvariantCulture, out res);
            return success;
        }

        public static bool TryParseHexByte(string value, out byte res)
        {
            bool success;
            value = value.Replace(HEX_PREFIX, String.Empty).TrimEnd(UNSIGNED_SUFFIX);
            res = 0;
            success = Byte.TryParse(value, NumberStyles.HexNumber,
                CultureInfo.InvariantCulture, out res);
            return success;
        }

        public static UInt16? ConvertStrToUInt16(string text)
        {
            UInt16? result;
            UInt16 value = 0;
            if (UInt16.TryParse(text, out value))
            {
                result = value;
            }
            else
            {
                result = null;
            }
            return result;
        }

        public static bool CheckRange(uint value, uint min, uint max)
        {
            return ((value >= min) && (value <= max));
        }
    }
}
