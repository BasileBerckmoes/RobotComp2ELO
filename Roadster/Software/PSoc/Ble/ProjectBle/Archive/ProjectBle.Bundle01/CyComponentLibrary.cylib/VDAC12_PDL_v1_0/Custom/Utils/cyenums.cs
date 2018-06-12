/*******************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System.Diagnostics;

namespace VDAC12_PDL_v1_0.Utils
{
    internal class CyEnums
    {
        #region Enums
        public enum CyEVrefSource { VrefExternal = 0, VrefVdda = 1, VrefDWR = 2 }

        public enum CyEOutputType { Unbuffered = 0, UnbufferedInternal = 1, BufferedPin = 2, BufferedInternal = 3 }

        public enum CyESignMode { FormatUnsigned = 0, FormatSigned = 1 }

        public enum CyEStrobeTerminalType
        {
            STROBE_DISABLED = 1,
            STROBE_EDGE = 2,
            STROBE_LEVEL = 3
        }

        public enum CyEUpdateType
        {
            DirectWrite = 0,
            BufferedWrite = 1,
            StrobeEdgeSync = 2,
            StrobeEdgeImmediate = 3,
            StrobeLevel = 4
        }

        #endregion
    }
}

//[] END OF FILE
