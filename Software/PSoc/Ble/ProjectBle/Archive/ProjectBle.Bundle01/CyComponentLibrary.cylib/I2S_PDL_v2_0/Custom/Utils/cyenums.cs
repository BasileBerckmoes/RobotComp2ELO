/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Diagnostics; 

namespace I2S_PDL_v2_0.Utils
{
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
        master = 1
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
        CY_I2S_WS_ONE_SCK_CYCLE = 0,
        CY_I2S_WS_ONE_CHANNEL_LENGTH = 1
    }

    public enum CySdiLatchingTime
    {
        SDI_NORMAL = 0,
        SDI_DELAYED = 1
    }

    public enum CySdoLatchingTime
    {
        SDO_NORMAL = 0,
        SDO_ADVANCED = 1
    }

    public enum CySignExtension
    {
        ext0 = 0,
        extMsb = 1
    }

    public enum CyChannels
    {
        Channel1 = 1,
        Channel2 = 2,
        Channel3 = 3,
        Channel4 = 4,
        Channel5 = 5,
        Channel6 = 6,
        Channel7 = 7,
        Channel8 = 8
    }

    public enum CyOverheadValue
    {
        Overhead0 = 0,
        Overhead1 = 1
    }

    public enum CySckPolarity
    {
        SCK_NORMAL = 0,
        SCK_INVERTED = 1
    }

    internal class CyEnums
    {
        #region Enum to display name
      
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
                case CyWsPulseWidth.CY_I2S_WS_ONE_SCK_CYCLE:
                    return "1 SCK period";
                case CyWsPulseWidth.CY_I2S_WS_ONE_CHANNEL_LENGTH:
                    return "1 channel length";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "1 channel length";
            }
        }

        public static string ToDisplayName(CySdiLatchingTime enumItem)
        {
            switch (enumItem)
            {
                case CySdiLatchingTime.SDI_NORMAL:
                    return "Normal";
                case CySdiLatchingTime.SDI_DELAYED:
                    return "Half-clock delayed";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "Normal";
            }
        }

        public static string ToDisplayName(CySdoLatchingTime enumItem)
        {
            switch (enumItem)
            {
                case CySdoLatchingTime.SDO_NORMAL:
                    return "Normal";
                case CySdoLatchingTime.SDO_ADVANCED:
                    return "Half-clock advanced";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "Normal";
            }
        }

        public static string ToDisplayName(CySignExtension enumItem)
        {
            switch (enumItem)
            {
                case CySignExtension.ext0:
                    return "0";
                case CySignExtension.extMsb:
                    return "MSB";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "0";
            }
        }

        public static string ToDisplayName(CyChannels enumItem)
        {
            return ((int)enumItem).ToString();
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

        public static string ToDisplayName(CySckPolarity enumItem)
        {
            switch (enumItem)
            {
                case CySckPolarity.SCK_NORMAL:
                    return "Normal";
                case CySckPolarity.SCK_INVERTED:
                    return "Inverted";
                default:
                    Debug.Fail("unhandled enum item.");
                    return "0";
            }
        }
        #endregion
    }
}