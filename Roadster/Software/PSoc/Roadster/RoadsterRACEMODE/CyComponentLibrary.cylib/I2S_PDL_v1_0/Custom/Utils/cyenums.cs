/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Diagnostics;

namespace I2S_PDL_v1_0.Utils
{
    public enum CyClkDiv
    {
        CY_I2S_MCLK_DIV_4 = 0,
        CY_I2S_MCLK_DIV_8 = 2,
    }

    public enum CyDataLength
    {
        CY_I2S_LEN8 = 0,
        CY_I2S_LEN16 = 1,
        CY_I2S_LEN18 = 2,
        CY_I2S_LEN20 = 3,
        CY_I2S_LEN24 = 4,
        CY_I2S_LEN32 = 5
    }

    public enum CyMode
    {
        slave = 0,
        master = 1,
        full_duplex = 2
    }

    public enum CyAlignment
    {
        CY_I2S_LEFT_JUSTIFIED = 0,
        CY_I2S_I2S_MODE = 1,
        CY_I2S_TDM_MODE_A = 2,
        CY_I2S_TDM_MODE_B = 3
    }

    public enum CyWsPulseWidth
    {
        oneSckPeriod = 0,
        oneChannelLength = 1
    }

    public enum CyEdge
    {
        falling = 0,
        rising = 1
    }

    public enum CyBitExtension
    {
        ext0 = 0,
        extMsb = 1
    }

    public enum CyOverheadValue
    {
        Overhead0 = 0,
        Overhead1 = 1
    }

    internal class CyEnums
    {
        #region Enum to display name
        public static string ToDisplayName(CyClkDiv enumItem)
        {
            switch (enumItem)
            {
                case CyClkDiv.CY_I2S_MCLK_DIV_4:
                    return "/4";
                case CyClkDiv.CY_I2S_MCLK_DIV_8:
                    return "/8";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "/8";
            }
        }

        public static int ToDisplayValue(CyClkDiv enumItem)
        {
            switch (enumItem)
            {
                case CyClkDiv.CY_I2S_MCLK_DIV_4:
                    return 2;
                case CyClkDiv.CY_I2S_MCLK_DIV_8:
                    return 4;
                default:
                    Debug.Fail("unhandled enum item.");
                    return 8;
            }
        }

        public static string ToDisplayName(CyDataLength enumItem)
        {
            switch (enumItem)
            {
                case CyDataLength.CY_I2S_LEN8:
                    return "8";
                case CyDataLength.CY_I2S_LEN16:
                    return "16";
                case CyDataLength.CY_I2S_LEN18:
                    return "18";
                case CyDataLength.CY_I2S_LEN20:
                    return "20";
                case CyDataLength.CY_I2S_LEN24:
                    return "24";
                case CyDataLength.CY_I2S_LEN32:
                    return "32";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "16";
            }
        }

        public static int ToDisplayValue(CyDataLength enumItem)
        {
            switch (enumItem)
            {
                case CyDataLength.CY_I2S_LEN8:
                    return 8;
                case CyDataLength.CY_I2S_LEN16:
                    return 16;
                case CyDataLength.CY_I2S_LEN18:
                    return 18;
                case CyDataLength.CY_I2S_LEN20:
                    return 20;
                case CyDataLength.CY_I2S_LEN24:
                    return 24;
                case CyDataLength.CY_I2S_LEN32:
                    return 32;
                default:
                    Debug.Fail("unhandled enum item.");
                    return 16;
            }
        }

        public static string ToDisplayName(CyMode enumItem)
        {
            switch (enumItem)
            {
                case CyMode.slave:
                    return "Slave";
                case CyMode.master:
                    return "Master";
                case CyMode.full_duplex:
                    return "Full duplex";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "Master";
            }
        }

        public static string ToDisplayName(CyAlignment enumItem)
        {
            switch (enumItem)
            {
                case CyAlignment.CY_I2S_LEFT_JUSTIFIED:
                    return "Left justified";
                case CyAlignment.CY_I2S_I2S_MODE:
                    return "I2S mode";
                case CyAlignment.CY_I2S_TDM_MODE_A:
                    return "TDM A";
                case CyAlignment.CY_I2S_TDM_MODE_B:
                    return "TDM B";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "I2S mode";
            }
        }

        public static string ToDisplayName(CyWsPulseWidth enumItem)
        {
            switch (enumItem)
            {
                case CyWsPulseWidth.oneSckPeriod:
                    return "1 SCK period";
                case CyWsPulseWidth.oneChannelLength:
                    return "1 channel length";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "1 channel length";
            }
        }

        public static string ToDisplayName(CyEdge enumItem)
        {
            switch (enumItem)
            {
                case CyEdge.falling:
                    return "Falling edge";
                case CyEdge.rising:
                    return "Rising edge";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "Falling edge";
            }
        }

        public static string ToDisplayName(CyBitExtension enumItem)
        {
            switch (enumItem)
            {
                case CyBitExtension.ext0:
                    return "0";
                case CyBitExtension.extMsb:
                    return "MSB";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "0";
            }
        }

        public static string ToDisplayName(CyOverheadValue enumItem)
        {
            switch (enumItem)
            {
                case CyOverheadValue.Overhead0:
                    return "0";
                case CyOverheadValue.Overhead1:
                    return "1";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "0";
            }
        }
        #endregion
    }
}