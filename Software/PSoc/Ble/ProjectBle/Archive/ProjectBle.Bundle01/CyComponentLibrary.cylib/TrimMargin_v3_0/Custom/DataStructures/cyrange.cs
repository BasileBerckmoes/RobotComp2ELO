/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Diagnostics;

namespace TrimMargin_v3_0.DataStructures
{
    [DebuggerDisplay("Min = {Min}, Max = {Max}")]
    public struct CyRange
    {
        public CyRange(double min, double max)
            : this()
        {
            Min = min;
            Max = max;
        }

        public double Min { get; private set; }
        public double Max { get; private set; }
    }
}