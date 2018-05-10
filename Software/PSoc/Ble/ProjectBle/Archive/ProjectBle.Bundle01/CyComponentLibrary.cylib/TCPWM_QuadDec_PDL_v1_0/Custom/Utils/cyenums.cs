/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System.Diagnostics;

namespace TCPWM_QuadDec_PDL_v1_0.Utils
{
    internal class CyEnums
    {
        public const string ENUM_VALUE_INPUT_LEVEL = "Level";

        #region Enums
        public enum CyInputMode
        {
            INPUT_RISINGEDGE,
            INPUT_FALLINGEDGE,
            INPUT_EITHEREDGE,
            INPUT_DISABLED = 7
        }

        public enum CyCounterResolution
        {
            X1,
            X2,
            X4
        }
        #endregion

        public static byte ToDisplayValue(CyCounterResolution enumItem)
        {
            switch (enumItem)
            {
                case CyCounterResolution.X1:
                    return 1;
                case CyCounterResolution.X2:
                    return 2;
                case CyCounterResolution.X4:
                    return 4;
                default:
                    Debug.Fail("unhandled enum item.");
                    return 1;
            }
        }
    }
}
